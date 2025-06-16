#pragma once

#include <SFML/Graphics.hpp>

#include <Module.hpp>

class SelectModule : public Module {
public:
	SelectModule(std::weak_ptr<App> state);

	void Update() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	enum SelectRectPosition {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		None
	};

	bool calculateRect(sf::Vector2f centerPosition, sf::Vector2f origin, sf::Angle angle, SelectRectPosition rectType, bool selected);

	bool calculuteSingleRect(sf::Vector2f position, sf::Vector2f size, sf::Vector2f origin, sf::Angle rotation, bool selected);

	sf::VertexArray vertices;

	static constexpr int RECT_LENGTH = 30;
	static constexpr int RECT_HEIGHT = 7;

	SelectRectPosition currentSelectedRect = None;

	sf::Vector2f dragStart = sf::Vector2f(0, 0);
	sf::Vector2f dragStartObjectPosition = sf::Vector2f(0, 0);
	sf::Vector2f originalObjectSize = sf::Vector2f(0, 0);
	bool dragging = false;

	bool draggingRotation = false;

	std::weak_ptr<Object> currentObject;
};