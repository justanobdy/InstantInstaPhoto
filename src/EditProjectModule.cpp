#include <EditProjectModule.hpp>

#include <App.hpp>

EditProjectModule::EditProjectModule(std::weak_ptr<App> app, EditProjectModuleType type)
	: ImGuiModule(app), type(type)
{
	newSettings = app.lock()->state.projectSettings;
}

void EditProjectModule::Update() {
	switch (type) {
	case EditProjectModuleType::ChangeBackgroundColor:
		doBackgroundColor();
		break;
	case EditProjectModuleType::ChangeResolution:
		doResolution();
		break;
	default:
		break;
	}
}

void EditProjectModule::doResolution() {
	imgui::Begin("Change Resolution", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	imgui::Text("Please input a new resolution: ");

	sf::Vector2i temp = sf::Vector2i(newSettings.imageResolution);

	imgui::InputInt("Width", &temp.x);
	imgui::InputInt("Height", &temp.y);

	newSettings.imageResolution = sf::Vector2f(temp);

	imgui::InputInt("Total Slides", &newSettings.totalSlides);

	if (imgui::Button("Ok")) {
		app.lock()->ApplySettings(newSettings);

		QueueFree();
	}

	imgui::SameLine();

	if (imgui::Button("Cancel")) {
		QueueFree();
	}

	imgui::End();
}

void EditProjectModule::doBackgroundColor() {
	imgui::Begin("Change Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	const sf::Color color = newSettings.backgroundColor;

	float colors[3] = { float(color.r) / 255.f, float(color.g) / 255.f, float(color.b) / 255.f };

	imgui::ColorPicker3("New Background Color", colors);

	newSettings.backgroundColor = sf::Color(colors[0] * 255.f, colors[1] * 255.f, colors[2] * 255.f);

	if (imgui::Button("Ok")) {
		app.lock()->ApplySettings(newSettings);

		QueueFree();
	}
	
	imgui::SameLine();

	if (imgui::Button("Cancel")) {
		QueueFree();
	}

	imgui::End();
}