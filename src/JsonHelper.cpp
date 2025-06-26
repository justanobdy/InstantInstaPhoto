#include <JsonHelper.hpp>

namespace sf {
	void to_json(nlohmann::json& json, const Vector2f& vec) {
		json = nlohmann::json{ {"x", vec.x}, {"y", vec.y} };
	}

	void from_json(const nlohmann::json& json, Vector2f& vec) {
		json.at("x").get_to(vec.x);
		json.at("y").get_to(vec.y);
	}

	void to_json(nlohmann::json& json, const Color& color) {
		json = nlohmann::json{ {"r", color.r}, {"g", color.g}, {"b", color.b}, {"a", color.a} };
	}

	void from_json(const nlohmann::json& json, Color& color) {
		json.at("r").get_to(color.r);
		json.at("g").get_to(color.g);
		json.at("b").get_to(color.b);
		json.at("a").get_to(color.a);
	}
}