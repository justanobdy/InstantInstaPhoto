#include <ErrorModule.hpp>

ErrorModule::ErrorModule(std::weak_ptr<App> app, const std::string& error)
	:	ImGuiModule(app), error(error)
{

}

void ErrorModule::Update()
{
	bool open = true;

	imgui::Begin(std::string("Error##" + std::to_string(GetID())).c_str(), &open, ImGuiWindowFlags_AlwaysAutoResize);

	if (!open)
		QueueFree();

	imgui::Text(error.c_str());

	if (imgui::Button("Ok"))
		QueueFree();

	imgui::End();
}