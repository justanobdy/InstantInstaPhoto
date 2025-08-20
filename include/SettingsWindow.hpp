#pragma once

#include <Module.hpp>
#include <Settings.hpp>

class SettingsWindow : public ImGuiModule {
public:
    using ImGuiModule::ImGuiModule;

    void Update() override;
private:
    void ApplySettings();

    Settings newSettings;
};