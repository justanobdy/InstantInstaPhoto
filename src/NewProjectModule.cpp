#include "NewProjectModule.hpp"

void NewProjectModule::Update()
{
	imgui::Begin("New Project", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	sf::Vector2i tempRes = sf::Vector2i(settings.imageResolution);

	imgui::InputInt("Width", &tempRes.x);

	if (tempRes.x < 0) {
		tempRes.x = 0;
	}

	imgui::InputInt("Height", &tempRes.y);

	if (tempRes.y < 0) {
		tempRes.y = 0;
	}

	settings.imageResolution = sf::Vector2f(tempRes);

	imgui::InputInt("Total Slides", &settings.totalSlides);

	if (settings.totalSlides < 1) {
		settings.totalSlides = 1;
	}

	imgui::NewLine();
	imgui::Separator();
	imgui::NewLine();

	const sf::Color color = settings.backgroundColor;

	float colors[3] = { float(color.r) / 255.f, float(color.g) / 255.f, float(color.b) / 255.f };

	imgui::ColorPicker3("New Background Color", colors);

	settings.backgroundColor = sf::Color(colors[0] * 255.f, colors[1] * 255.f, colors[2] * 255.f);

	imgui::NewLine();
	imgui::Separator();
	imgui::NewLine();

	if (imgui::Button("Cancel")) {
		QueueFree();
	}

	imgui::SameLine();

	if (imgui::Button("Create")) {
		app.lock()->NewProject(settings);

		QueueFree();
	}

	imgui::End();
}
