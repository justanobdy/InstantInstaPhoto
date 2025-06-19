#pragma once

#include <Module.hpp>

class ErrorModule : public ImGuiModule {
public:
	ErrorModule(std::weak_ptr<App> app, const std::string& error);

	void Update() override;
private:
	std::string error;
};