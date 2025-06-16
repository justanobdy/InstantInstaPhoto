#include <ObjectContextModule.hpp>

#include <App.hpp>

void ObjectContextModule::Update()
{
	//app.lock()->state.currentSelectedObject.value().lock()->GetGlobalBounds().contains(app.lock()->state.GetMousePosition())

	if (imgui::IsMouseReleased(ImGuiMouseButton_Right)) {
		imgui::OpenPopup("##ObjectContextModule");
	}

	const bool hasObject = app.lock()->state.currentSelectedObject != std::nullopt;

	if (imgui::BeginPopup("##ObjectContextModule", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings)) {
		if (!hasObject) imgui::BeginDisabled();
		if (imgui::Selectable("Copy")) {
			clipboard = app.lock()->state.currentSelectedObject.value().lock()->Serialize();
		}
		if (!hasObject) imgui::EndDisabled();

		if (clipboard.empty()) imgui::BeginDisabled();
		if (imgui::Selectable("Paste")) {
			app.lock()->AddObjectFromJson(clipboard);
		}
		if (clipboard.empty()) imgui::EndDisabled();
		
		imgui::Separator();

		if (!hasObject) imgui::BeginDisabled();
		if (imgui::Selectable("Delete")) {
			app.lock()->state.currentSelectedObject.value().lock()->QueueDelete();

			imgui::CloseCurrentPopup();
		}
		if (!hasObject) imgui::EndDisabled();

		imgui::EndPopup();
	}
}