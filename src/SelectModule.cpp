#include <SelectModule.hpp>

#include <cmath>

#include <numbers>

#include <iostream>

#include <App.hpp>

/*
	If you are looking through this code - prepare yourself!

	There is a bunch of random looking math, and some hacks to get everything to work. 
	
	But it works!

	Good Luck!
*/

const sf::Color defaultRectColor = sf::Color(137, 169, 176);
const sf::Color highlightedRectColor = sf::Color(107, 130, 135);
const sf::Color selectedRectColor = sf::Color(87, 133, 143);

SelectModule::SelectModule(std::weak_ptr<App> app)
	:	Module(app), vertices(sf::PrimitiveType::Triangles)

{
	
}

void RenderRect(sf::VertexArray& array, sf::Vector2f position, float vSize, float hSize) {
	
}

bool SelectModule::calculuteSingleRect(sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin, sf::Angle rotation, bool selected)
{
	bool mouseIn = rectContainsPoint(app.lock()->state.GetMousePosition(), sf::Vector2f(position.x, position.y), sf::Vector2f(abs(size.x), abs(size.y)), origin, rotation);

	sf::Color color = defaultRectColor;

	if (mouseIn)
		color = highlightedRectColor;
	if (selected)
		color = selectedRectColor;

	vertices.append(sf::Vertex{ rotatePoint(position, origin, rotation), color });
	vertices.append(sf::Vertex{ rotatePoint(sf::Vector2f(position.x + size.x, position.y), origin, rotation), color });
	vertices.append(sf::Vertex{ rotatePoint(sf::Vector2f(position.x, position.y + size.y), origin, rotation), color });

	vertices.append(sf::Vertex{ rotatePoint(sf::Vector2f(position.x + size.x, position.y + size.y), origin, rotation), color });
	vertices.append(sf::Vertex{ rotatePoint(sf::Vector2f(position.x, position.y + size.y), origin, rotation), color });
	vertices.append(sf::Vertex{ rotatePoint(sf::Vector2f(position.x + size.x, position.y), origin, rotation), color });

	sf::Vector2f actualTopLeft = position;

	if (size.x < 0) 
		actualTopLeft.x += size.x;
	if (size.y < 0)
		actualTopLeft.y += size.y;

	return mouseIn;
}

bool SelectModule::calculateRect(sf::Vector2f centerPosition, sf::Vector2f origin, sf::Angle angle, SelectRectPosition rectType, bool selected)
{
	sf::Color color = selected ? sf::Color::Green : sf::Color::White;

	if (rectType == SelectRectPosition::TopLeft) {
		bool value = calculuteSingleRect(sf::Vector2f(centerPosition.x - RECT_HEIGHT, centerPosition.y - RECT_HEIGHT), sf::Vector2f(RECT_LENGTH, RECT_HEIGHT), origin, angle, selected);
			
		value |= calculuteSingleRect(sf::Vector2f(centerPosition.x - RECT_HEIGHT, centerPosition.y - RECT_HEIGHT), sf::Vector2f(RECT_HEIGHT, RECT_LENGTH), origin, angle, selected);

		return value;
	}

	if (rectType == SelectRectPosition::TopRight) {
		bool value = calculuteSingleRect(sf::Vector2f(centerPosition.x + RECT_HEIGHT - RECT_LENGTH, centerPosition.y - RECT_HEIGHT), sf::Vector2f(RECT_LENGTH, RECT_HEIGHT), origin, angle, selected);
			
		value |= calculuteSingleRect(sf::Vector2f(centerPosition.x, centerPosition.y - RECT_HEIGHT), sf::Vector2f(RECT_HEIGHT, RECT_LENGTH), origin, angle, selected);

		return value;
	}

	if (rectType == SelectRectPosition::BottomLeft) {
		bool value = calculuteSingleRect(sf::Vector2f(centerPosition.x - RECT_HEIGHT, centerPosition.y), sf::Vector2f(RECT_LENGTH, RECT_HEIGHT), origin, angle, selected);
			
		value |= calculuteSingleRect(sf::Vector2f(centerPosition.x - RECT_HEIGHT, centerPosition.y + RECT_HEIGHT - RECT_LENGTH), sf::Vector2f(RECT_HEIGHT, RECT_LENGTH), origin, angle, selected);

		return value;
	}

	if (rectType == SelectRectPosition::BottomRight) {
		bool value = calculuteSingleRect(sf::Vector2f(centerPosition.x + RECT_HEIGHT - RECT_LENGTH, centerPosition.y), sf::Vector2f(RECT_LENGTH, RECT_HEIGHT), origin, angle, selected);
			
		value |= calculuteSingleRect(sf::Vector2f(centerPosition.x, centerPosition.y + RECT_HEIGHT - RECT_LENGTH), sf::Vector2f(RECT_HEIGHT, RECT_LENGTH), origin, angle, selected);

		return value;
	}

	return false;
}

void SelectModule::Update()
{
	if (dragging || draggingRotation)
		app.lock()->state.currentSelectedObject = currentObject;

	if (app.lock()->state.currentSelectedObject == std::nullopt)
		return;

	const sf::Vector2f origin = sf::Vector2f(150, 150);

	sf::Vector2f currentOrigin = sf::Vector2f(150, 150);
	sf::Vector2f currentSize = sf::Vector2f(100, 100);

	sf::Angle currentAngle = sf::radians(0);

	if (app.lock()->state.currentSelectedObject.has_value()) {
		auto object = app.lock()->state.currentSelectedObject.value().lock();

		currentOrigin = object->GetGlobalBounds().position;
		currentSize = object->GetGlobalBounds().size;
		currentAngle = object->GetRotation();
	}

	sf::Vector2f currentTopRight = sf::Vector2f(currentOrigin.x - (currentSize.x / 2), currentOrigin.y - (currentSize.y / 2));

	vertices.clear();

	SelectRectPosition newRect = SelectRectPosition::None;

	if (calculateRect(currentTopRight, currentOrigin, currentAngle, SelectRectPosition::TopLeft, currentSelectedRect == SelectRectPosition::TopLeft && dragging))
		newRect = SelectRectPosition::TopLeft;
	if (calculateRect(sf::Vector2f(currentTopRight.x + currentSize.x, currentTopRight.y), currentOrigin, currentAngle, SelectRectPosition::TopRight, currentSelectedRect == SelectRectPosition::TopRight && dragging))
		newRect = SelectRectPosition::TopRight;
	if (calculateRect(sf::Vector2f(currentTopRight.x, currentTopRight.y + currentSize.y), currentOrigin, currentAngle, SelectRectPosition::BottomLeft, currentSelectedRect == SelectRectPosition::BottomLeft && dragging))
		newRect = SelectRectPosition::BottomLeft;
	if (calculateRect(sf::Vector2f(currentTopRight.x + currentSize.x, currentTopRight.y + currentSize.y), currentOrigin, currentAngle, SelectRectPosition::BottomRight, currentSelectedRect == SelectRectPosition::BottomRight && dragging))
		newRect = SelectRectPosition::BottomRight;

	auto object = app.lock()->state.currentSelectedObject.value().lock();

	if (dragging && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && currentSelectedRect != SelectRectPosition::None) {
		if (!dragging) {
			dragging = true;

			dragStart = app.lock()->state.GetMousePosition();

			originalObjectSize = object->GetGlobalBounds().size;

			dragStartObjectPosition = object->GetPosition();
		}

		sf::Vector2f mousePos = app.lock()->state.GetMousePosition();

		sf::Vector2f rotatedMouse = rotatePoint(mousePos, currentOrigin, -currentAngle);

		auto pos = object->GetPosition();

		object->SetSize(sf::Vector2f(abs(rotatedMouse.x - dragStartObjectPosition.x) * 2, abs(rotatedMouse.y - dragStartObjectPosition.y) * 2));

		app.lock()->state.draggingObjectPosition = false;

		currentObject = app.lock()->state.currentSelectedObject.value();
	}
	else {
		dragging = false;
		currentSelectedRect = newRect;
	}

	bool draggingRotateRect = calculuteSingleRect(sf::Vector2f(object->GetPosition().x - RECT_LENGTH / 2, object->GetPosition().y - object->GetGlobalBounds().size.y / 2 - 50), sf::Vector2f(RECT_LENGTH, RECT_HEIGHT * 2), object->GetPosition(), object->GetRotation(), draggingRotation);

	if (draggingRotateRect && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) || draggingRotation && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2f mousePos = app.lock()->state.GetMousePosition();

		sf::Vector2f diff = sf::Vector2f(mousePos.x - object->GetPosition().x, mousePos.y - object->GetPosition().y);

		object->SetRotation(sf::radians(atan2(diff.y,  diff.x) + (std::numbers::pi / 2.f)));

		draggingRotation = true;
		dragging = false;
		app.lock()->state.draggingObjectPosition = false;

		currentObject = app.lock()->state.currentSelectedObject.value();
	}
	else {
		draggingRotation = false;
	}
}

void SelectModule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (app.lock()->state.currentSelectedObject == std::nullopt)
		return;

	target.draw(vertices, states);
}