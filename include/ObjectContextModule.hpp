#pragma once

#include <Module.hpp>

class ObjectContextModule : public ImGuiModule {
public:
	using ImGuiModule::ImGuiModule;

	void Update() override;
private:
	nlohmann::json clipboard;
};