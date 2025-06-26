#pragma once

#include <Module.hpp>

#include <App.hpp>
#include <Exporter.hpp>
#include <ProjectManager.hpp>

class MenuBarModule : public ImGuiModule {
public:
	MenuBarModule(std::weak_ptr<App> app);

	void Update() override;
private:
	void AddItems();

	void SaveProject();

	void OpenProject();

	ProjectManager projectManager;
};