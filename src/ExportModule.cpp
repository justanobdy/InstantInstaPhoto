#include <ExportModule.hpp>

#include <imgui_stdlib.h>

#include <portable-file-dialogs.h>

#include <Exporter.hpp>

#include <App.hpp>

#include <ErrorModule.hpp>

void ExportModule::Update()
{
	const char* const types[] = {
		".bmp",
		".png",
		".tga",
		".jpg"
	};

	bool open = true;

	imgui::Begin("Export", &open);

	if (!open) {
		QueueFree();
	}

	imgui::InputText("Output Name", &exportName);

	imgui::Combo("Filetype", &currentFiletype, types, 4);

	if (imgui::Button("...")) {
		auto result = pfd::select_folder("Select Output Folder");

		if (!result.result().empty()) {
			exportDirectory = result.result();
		}
	}

	imgui::SameLine();

	imgui::BeginDisabled();
	imgui::InputText("Output Directory", &exportDirectory);
	imgui::EndDisabled();

	if (imgui::Button("Export")) {
		if (exportName.empty()) {
			app.lock()->AddModule<ErrorModule>("Please enter a filename!");
		}
		else if (exportDirectory.empty()) {
			app.lock()->AddModule<ErrorModule>("Please select an output directory!");
		}
		else {

			Export::ExportImage(exportDirectory, exportName, types[currentFiletype], app.lock()->state.projectSettings, app.lock()->GetObjects());

			QueueFree();
		}
	}

	imgui::End();
}
