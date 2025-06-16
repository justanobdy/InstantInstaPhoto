#pragma once

#include <Common.hpp>

#include <Object.hpp>

#include <vector>
#include <memory>
#include <optional>

#include <AppState.hpp>
#include <Module.hpp>

#include <Exporter.hpp>

class App : public std::enable_shared_from_this<App> {
public:
	static std::shared_ptr<App> Create() {
		return std::shared_ptr<App>(new App());
	}

	void run();

	template<typename T, typename... Args>
	std::weak_ptr<T> AddObject(Args... args) {
		objects.push_back(std::make_shared<T>(args...));

		return std::static_pointer_cast<T>(objects.back());
	}

	void AddObjectFromJson(const nlohmann::json& json);

	template<typename T, typename... Args>
	void AddModule(Args... args) {
		modules.push_back(std::make_shared<T>(weak_from_this(), args...));
	}

	void RemoveObjectByID(int ID);

	void RemoveModuleByID(int ID);

	void NewProject(const ProjectSettings& newSettings);

	void ApplySettings(const ProjectSettings& newSettings);

	AppState state;

	std::vector<std::shared_ptr<Object>>& GetObjects();
private:
	App();

	void SetupObjectMap();

	std::vector<std::shared_ptr<Object>> objects;

	std::vector<std::shared_ptr<Module>> modules;

	sf::View view;

	sf::RenderWindow window;

	bool isDraggingView = false;

	sf::Vector2i originalMousePosition;
	sf::Vector2f originalViewPosition;

	sf::RectangleShape previewRectangle;
	std::vector<sf::RectangleShape> slideOutlines;

	std::unordered_map<std::string, std::function<void(const nlohmann::json&)>> createMap;
};