#include <SettingsWindow.hpp>

#include <App.hpp>

void SettingsWindow::Update() {
    imgui::Begin("Settings");

    int scale = newSettings.fontScale * 100.f;

    imgui::InputInt("GUI Scale", &scale);

    if (scale < 25) {
        scale = 25;
    }if (scale > 400) {
        scale = 400;
    }

    newSettings.fontScale = float(scale) / 100.f;

    if (imgui::Button("Cancel")) {
        QueueFree();
    }
    imgui::SameLine();
    if (imgui::Button("Apply")) {
        ApplySettings();
        QueueFree();
    }

    imgui::End();
}

void SettingsWindow::ApplySettings() {
    app.lock()->state.settings = newSettings;
    app.lock()->ApplyAppSettings(newSettings);
}
