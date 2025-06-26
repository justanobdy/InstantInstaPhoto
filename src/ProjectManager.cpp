#include <ProjectManager.hpp>

#include <App.hpp>

#include <SpriteObject.hpp>

#include <fstream>

#include <JsonHelper.hpp>

ProjectManager::ProjectManager(std::weak_ptr<App> app)
	:	app(app)
{
	
}

void ProjectManager::DeserializeFromFile(const std::filesystem::path& file)
{
	/*
	{
		"data": {
			"resolution",
			"backgroundColor",
			"slides"
		}
		"objects": {}
	}
	*/

	std::ifstream data(file);

	nlohmann::json json = nlohmann::json::parse(data);

	data.close();

	ProjectSettings newSettings;

	try {
		if (!json.at("data").is_null()) {
			auto data = json["data"];

			newSettings.imageResolution = data.at("resolution").template get<sf::Vector2f>();

			newSettings.backgroundColor = data.at("backgroundColor").template get<sf::Color>();

			newSettings.totalSlides = data.at("slides");
		}

		app.lock()->NewProject(newSettings);

		if (!json.at("objects").is_null()) {
			for (const nlohmann::json& object : json.at("objects")) {
				app.lock()->AddObjectFromJson(object);
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void ProjectManager::SerializeToFile(const std::filesystem::path& file)
{
	nlohmann::json json, data, objects;

	std::shared_ptr<App> app = this->app.lock();

	data["resolution"] = app->state.projectSettings.imageResolution;

	data["backgroundColor"] = app->state.projectSettings.backgroundColor;

	data["slides"] = app->state.projectSettings.totalSlides;

	for (const auto& object : app->GetObjects()) {
		objects.push_back(object->Serialize());
	}

	json["data"] = data;
	json["objects"] = objects;

	std::ofstream write(file);

	write << json.dump();

	write.close();
}