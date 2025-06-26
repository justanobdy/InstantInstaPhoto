#pragma once

#include <AppState.hpp>

#include <filesystem>

class App;

namespace Export {
	void ExportImage(const std::filesystem::path& path, const std::string& name, const std::string& filetype, const ProjectSettings& settings, const std::vector<std::shared_ptr<Object>>& objects);

	std::vector<std::string> GetPossibleOutputTypes();
};