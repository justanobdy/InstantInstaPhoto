#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

namespace sf {
	void to_json(nlohmann::json& json, const Vector2f& vec);
	void from_json(const nlohmann::json& json, Vector2f& vec);

	void to_json(nlohmann::json& json, const Color& color);
	void from_json(const nlohmann::json& json, Color& color);
}