#pragma once

#include <filesystem>
#include <memory>

#include <nlohmann/json.hpp>

class App;

class ProjectManager {
public:
	ProjectManager(std::weak_ptr<App> app);

	void DeserializeFromFile(const std::filesystem::path& file);
	void SerializeToFile(const std::filesystem::path& file);
private:
	std::weak_ptr<App> app;
};