#pragma once

#include <Module.hpp>

class ExportModule : public ImGuiModule {
public:
	using ImGuiModule::ImGuiModule;

	void Update() override;
private:
	std::string exportName;
	
	int currentFiletype = 0;

	std::string exportDirectory;
};