#pragma once

#include <SFML/Graphics.hpp>

#include <Module.hpp>

class EditProjectModule : public ImGuiModule {
public:
	enum EditProjectModuleType {
		ChangeResolution,
		ChangeBackgroundColor
	};

	EditProjectModule(std::weak_ptr<App> app, EditProjectModuleType type);

	void Update() override;
private:
	const EditProjectModuleType type;

	void doResolution();
	void doBackgroundColor();

	ProjectSettings newSettings;
};