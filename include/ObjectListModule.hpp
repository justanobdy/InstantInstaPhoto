#pragma once

#include <Module.hpp>

class ObjectListModule : public ImGuiModule {
public:
	using ImGuiModule::ImGuiModule;

	void Update() override;
};