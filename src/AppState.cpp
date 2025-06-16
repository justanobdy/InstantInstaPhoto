#include <AppState.hpp>

sf::Vector2f AppState::GetMousePosition() const
{
	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(*window));

	const sf::Vector2f calculuatedViewOffset = view->getCenter() - view->getSize().componentWiseDiv(sf::Vector2f(2, 2));

	position += calculuatedViewOffset;

	return position;
}