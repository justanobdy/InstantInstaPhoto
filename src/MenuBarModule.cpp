#include <MenuBarModule.hpp>

#include <portable-file-dialogs.h>

#include <SpriteObject.hpp>

#include <NewProjectModule.hpp>
#include <EditProjectModule.hpp>
#include <ErrorModule.hpp>

#include <ExportModule.hpp>

MenuBarModule::MenuBarModule(std::weak_ptr<App> app)
	:	ImGuiModule(app), projectManager(app)
{

}

void MenuBarModule::Update()
{
	if (imgui::BeginMainMenuBar()) {
		if (imgui::BeginMenu("File")) {
			if (imgui::MenuItem("New Project")) {
				app.lock()->AddModule<NewProjectModule>();
			}

			if (imgui::MenuItem("Add Items")) {
				AddItems();
			}

			imgui::Separator();

			if (imgui::MenuItem("Open Project")) {
				OpenProject();
			}

			if (imgui::MenuItem("Save Project")) {
				SaveProject();
			}

			imgui::Separator();

			if (imgui::MenuItem("Export")) {
				app.lock()->AddModule<ExportModule>();
			}

			imgui::EndMenu();
		}

		if (imgui::BeginMenu("Image")) {
			if (imgui::MenuItem("Change Resolution")) {
				app.lock()->AddModule<EditProjectModule>(EditProjectModule::EditProjectModuleType::ChangeResolution);
			}

			if (imgui::MenuItem("Change Background Color")) {
				app.lock()->AddModule<EditProjectModule>(EditProjectModule::EditProjectModuleType::ChangeBackgroundColor);
			}

			imgui::EndMenu();
		}

		if (imgui::BeginMenu("View")) {
			imgui::EndMenu();
		}

		imgui::EndMainMenuBar();
	}
}

void MenuBarModule::AddItems() {
	auto selection = pfd::open_file("Open Images", ".", { "Image Files", "*.bmp *.png *.tga *.jpg *.gif *.psd *.hdr *.pic *.pnm" }, pfd::opt::multiselect);

	for (const auto& filename : selection.result()) {
		app.lock()->AddObject<SpriteObject>(filename);
	}
}

void MenuBarModule::SaveProject()
{
	auto result = pfd::save_file("Save Project", ".", { "Project Files (*.ipf)", "*.ipf" });

	if (!result.result().empty()) {
		projectManager.SerializeToFile(result.result());
	}
}

void MenuBarModule::OpenProject()
{
	auto result = pfd::open_file("Open Project", ".", { "Project Files (.ipf)", "*.ipf" });

	if (!result.result().empty()) {
		projectManager.DeserializeFromFile(result.result()[0]);
	}
}