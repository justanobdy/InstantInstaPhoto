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
		requires std::is_base_of_v<Object, T>
	std::weak_ptr<T> AddObject(Args... args) {
		objects.push_back(std::make_shared<T>(weak_from_this(), args...));

		return std::static_pointer_cast<T>(objects.back());
	}

	void AddObjectFromJson(const nlohmann::json& json);

	template<typename T, typename... Args>
		requires std::is_base_of_v<Module, T>
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

	void HandleEvents(const std::optional<sf::Event>& event);

	void Init();

	void Update();

	void Draw();

	void CleanObjects();

	std::vector<std::shared_ptr<Object>> objects;

	std::vector<std::shared_ptr<Module>> modules;

	sf::View view;

	sf::RenderWindow window;

	bool isDraggingView = false;

	sf::Vector2i originalMousePosition;
	sf::Vector2f originalViewPosition;

	sf::Vector2f viewCenter;

	sf::RectangleShape previewRectangle;
	std::vector<sf::RectangleShape> slideOutlines;

	std::unordered_map<std::string, std::function<void(const nlohmann::json&)>> createMap;

	sf::Vector2f dragOffset = sf::Vector2f(0, 0);

	sf::Clock deltaClock;
};