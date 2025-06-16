#pragma once

#include <AppState.hpp>

#include <filesystem>

class App;

// TODO: Exporter should not require App

class Exporter {
public:
	Exporter(std::weak_ptr<App> state);

	void ExportImage(const std::filesystem::path& path, sf::Vector2u resolution);
private:
	std::weak_ptr<App> app;
};