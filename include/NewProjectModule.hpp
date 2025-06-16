#pragma once

#include <Module.hpp>
#include <SFML/Graphics.hpp>

#include <App.hpp>

class NewProjectModule : public ImGuiModule {
public:
	using ImGuiModule::ImGuiModule;

	void Update() override;
private:
	ProjectSettings settings;
};