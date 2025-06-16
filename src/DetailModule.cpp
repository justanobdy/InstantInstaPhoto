#include <DetailModule.hpp>

#include <App.hpp>

#include <imgui_stdlib.h>

void DetailModule::Update() {
    if (app.lock()->state.currentSelectedObject != std::nullopt) {
        std::shared_ptr<Object> object = app.lock()->state.currentSelectedObject.value().lock();

        imgui::Begin("Object Options");

        {
            std::string name = object->GetName();

            imgui::InputText("Name", &name);

            object->SetName(name);

            imgui::Separator();

            sf::Vector2f newScale = object->GetScale();

            if (object->metadata.find("linkScale") == object->metadata.end()) {
                object->metadata["linkScale"] = false;
            }

            bool linkScale = object->metadata["linkScale"];

            // Change it to slider float and add context menu with input

            imgui::Text("Position:");

            sf::Vector2f newPosition = object->GetPosition();
            
            imgui::InputFloat("x##position", &newPosition.x);
            imgui::InputFloat("y##position", &newPosition.y);

            object->SetPosition(newPosition);

            imgui::Separator();

            imgui::Text("Scale:");

            imgui::SameLine();
            imgui::Checkbox("Link", reinterpret_cast<bool*>(&object->metadata["linkScale"]));

            if (!linkScale) {
                imgui::InputFloat("x", &newScale.x, 0.1f, 0.5f);
                imgui::InputFloat("y", &newScale.y, 0.1f, 0.5f);
            }
            else {
                //imgui::SliderFloat("##scaleslider", &newScale.x, 0.1f, 10);

                imgui::InputFloat("##scaleinput", &newScale.x, 0.1f, 0.5f);

                newScale.y = newScale.x;
            }

            object->SetScale(newScale);

            imgui::Separator();

            float rotation = object->GetRotation().asDegrees();

            imgui::InputFloat("Rotation", &rotation, 1.f, 1.f);

            object->SetRotation(sf::degrees(rotation));

            imgui::Separator();

            int zLayer = object->GetZLayer();

            imgui::InputInt("Z Layer", &zLayer);

            object->SetZLayer(zLayer);
        }

        imgui::End();
    }
    else {
        // else create a fake replica

        float tempFloat = 0;
        bool tempBool = false;
        int tempInt = 0;

        imgui::Begin("Object Options");

        imgui::BeginDisabled();

        imgui::InputText("Name", (char*)"", 0, 0, (ImGuiInputTextCallback)0, nullptr);

        imgui::Separator();

        imgui::Text("Position:");

        imgui::InputFloat("x##position", &tempFloat);
        imgui::InputFloat("y##position", &tempFloat);

        imgui::Separator();

        imgui::Text("Scale: ");

        imgui::SameLine();
        imgui::Checkbox("Link", &tempBool);

        imgui::InputFloat("x", &tempFloat);
        imgui::InputFloat("y", &tempFloat);

        imgui::Separator();

        imgui::InputFloat("Rotation", &tempFloat);

        imgui::Separator();

        imgui::InputInt("Z Layer", &tempInt);

        imgui::EndDisabled();

        imgui::End();
    }
}