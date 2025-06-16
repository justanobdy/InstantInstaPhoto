#include <ProjectManager.hpp>

#include <App.hpp>

#include <SpriteObject.hpp>

#include <fstream>

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

	newSettings.imageResolution = sf::Vector2f(json["data"]["resolution"]["x"], json["data"]["resolution"]["y"]);
	newSettings.backgroundColor = sf::Color(json["data"]["backgroundColor"]["r"], json["data"]["backgroundColor"]["g"], json["data"]["backgroundColor"]["b"]);
	newSettings.totalSlides = json["data"]["slides"];

	app.lock()->NewProject(newSettings);

	for (const nlohmann::json& object : json["objects"]) {
		app.lock()->AddObjectFromJson(object);
	}
}

void ProjectManager::SerializeToFile(const std::filesystem::path& file)
{
	nlohmann::json json, data, objects;

	std::shared_ptr<App> app = this->app.lock();

	data["resolution"] = {
		{"x", app->state.projectSettings.imageResolution.x},
		{"y", app->state.projectSettings.imageResolution.y}
	};

	data["backgroundColor"] = {
		{"r", app->state.projectSettings.backgroundColor.r},
		{"g", app->state.projectSettings.backgroundColor.g},
		{"b", app->state.projectSettings.backgroundColor.b}
	};

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