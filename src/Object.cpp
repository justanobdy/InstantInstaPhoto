#include <Object.hpp>

int Object::totalCreatedObjects = 0;

sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f origin, sf::Angle angle) {
	/*
	p'x = cos(theta) * (px-ox) - sin(theta) * (py-oy) + ox

	p'y = sin(theta) * (px-ox) + cos(theta) * (py-oy) + oy
	*/

	const float s = std::sin(angle.asRadians());
	const float c = std::cos(angle.asRadians());

	return sf::Vector2f(
		c * (point.x - origin.x) - s * (point.y - origin.y) + origin.x,
		s * (point.x - origin.x) + c * (point.y - origin.y) + origin.y
	);
}

std::array<sf::Vector2f, 4> getCorners(sf::Vector2f position, sf::Vector2f size, sf::Angle angle, sf::Vector2f origin)
{
	return {
		rotatePoint(position, origin, angle),
		rotatePoint(sf::Vector2f{position.x + size.x, position.y}, origin, angle),
		rotatePoint(sf::Vector2f{position.x, position.y + size.y}, origin, angle),
		rotatePoint(sf::Vector2f(position.x + size.x, position.y + size.y), origin, angle)
	};
}

bool ObjectRectInfo::contains(sf::Vector2f point) const
{
	return rectContainsPoint(point, position, size, angle);
}

std::array<sf::Vector2f, 4> ObjectRectInfo::getCorners() const
{
	/*const float c = cos(angle.asRadians());
	const float s = sin(angle.asRadians());

	const sf::Vector2f halfSize = size.componentWiseDiv(sf::Vector2f(2, 2));

	return {
		// Top Left
		sf::Vector2f {
			c * (-halfSize.x - position.x) - s * (-halfSize.y - position.y) + position.x,
			s * (-halfSize.x - position.x) + c * (-halfSize.y - position.y) + position.y
		},
		// Top Right
		sf::Vector2f {
			c * (halfSize.x - position.x) - s * (-halfSize.y - position.y) + position.x,
			s * (halfSize.x - position.x) + c * (-halfSize.y - position.y) + position.y
		},
		// Bottom left
		sf::Vector2f {
			c * (-halfSize.x - position.x) - s * (halfSize.y - position.y) + position.x,
			s * (-halfSize.x - position.x) + c * (halfSize.y - position.y) + position.y
		},
		// Bottom right
		sf::Vector2f {
			c * (halfSize.x - position.x) - s * (halfSize.y - position.y) + position.x,
			s * (halfSize.x - position.x) + c * (halfSize.y - position.y) + position.y
		},
	};*/

	return {
		rotatePoint(position, origin, angle),
		rotatePoint(sf::Vector2f{position.x + size.x, position.y}, origin, angle),
		rotatePoint(sf::Vector2f{position.x, position.y + size.y}, origin, angle),
		rotatePoint(sf::Vector2f(position.x + size.x, position.y + size.y), origin, angle)
	};
}

bool rectContainsPoint(sf::Vector2f point, sf::Vector2f rectPosition, sf::Vector2f rectSize, sf::Angle angle)
{
	// this is chatgpt

	const float c = cos(angle.asRadians());
	const float s = sin(angle.asRadians());

	sf::Vector2f xAxis(c, s);
	sf::Vector2f yAxis(-s, c);

	const sf::Vector2f halfSize = rectSize.componentWiseDiv(sf::Vector2f(2, 2));

	const sf::Vector2f local = point - rectPosition;

	float dx = local.dot(xAxis);  // How far along the width direction
	float dy = local.dot(yAxis);  // How far along the height direction

	return abs(dx) <= halfSize.x && abs(dy) <= halfSize.y;
}

float areaOfTriangle(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3) {
	return 0.5 * ((point2.x - point1.x) * (point3.y - point1.y) - (point3.x - point1.x) * (point2.y - point1.y));
}

bool rectContainsPoint(sf::Vector2f point, sf::Vector2f rectPosition, sf::Vector2f rectSize, sf::Vector2f origin, sf::Angle angle)
{
	/*sf::Vector2f xAxis = sf::Vector2f(cos(angle.asRadians()), sin(angle.asRadians()));
	sf::Vector2f yAxis = sf::Vector2f(-sin(angle.asRadians()), cos(angle.asRadians()));

	sf::Vector2f halfExtents = sf::Vector2f(rectSize.x * 0.5f, rectSize.y * 0.5f);

	// Compute rectangle center from world-space origin
	sf::Vector2f center = origin + xAxis * halfExtents.x + yAxis * halfExtents.y;

	// Convert point to rectangle-local coordinates
	sf::Vector2f toPoint = point - center;
	float dx = toPoint.dot(xAxis);
	float dy = toPoint.dot(yAxis);

	return abs(dx) <= halfExtents.x && abs(dy) <= halfExtents.y;*/

	auto corners = getCorners(rectPosition, rectSize, angle, origin);

	float normalArea = abs(rectSize.x * rectSize.y);

	// Let ABCD = rect
	// Let P = point (position)

	float areaOfTriangles =
		// calculate triangle APD
		abs(areaOfTriangle(corners[0], point, corners[3]))
		+
		// calculate triangle DPC
		abs(areaOfTriangle(corners[3], point, corners[2]))
		+
		// calculate triangle CPB
		abs(areaOfTriangle(corners[2], point, corners[1]))
		+
		// calculate triangle BPA
		abs(areaOfTriangle(corners[1], point, corners[0]));

	//return false;

	return normalArea >= areaOfTriangles;
}

void Object::SetName(const std::string& newName) {
	name = newName;
}

const std::string& Object::GetName() const {
	return name;
}

int Object::GetTotalCreatedObjects() {
	return totalCreatedObjects;
}

bool Object::QueuedForDeletion() const
{
	return queuedForDeletion;
}

void Object::QueueDelete()
{
	queuedForDeletion = true;
}