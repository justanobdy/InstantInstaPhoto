#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

#include <Object.hpp>

struct ProjectSettings {
	sf::Vector2f imageResolution = sf::Vector2f(1080, 1080);

	sf::Color backgroundColor = sf::Color::Black;

	int totalSlides = 3;
};

struct AppState {
	using ObjectMetadata = std::unordered_map<std::string, int>;

	std::unordered_map<int, ObjectMetadata> objectMetadata = {};

	std::optional<std::weak_ptr<Object>> currentSelectedObject = std::nullopt;

	sf::RenderWindow* window;

	sf::View* view;

	bool draggingObjectPosition = false;

	sf::Vector2f GetMousePosition() const;

	ProjectSettings projectSettings;

	sf::Vector2f zoomFactor = sf::Vector2f(1, 1);
};