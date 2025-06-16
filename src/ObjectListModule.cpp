#include <ObjectListModule.hpp>

#include <App.hpp>

void ObjectListModule::Update() {
	imgui::Begin("Object List");

	for (int i = 0; i < app.lock()->GetObjects().size(); i++) {
		auto& object = app.lock()->GetObjects()[i];

		if (imgui::Selectable(std::string(object->GetName() + "##DetailWindow" + std::to_string(i)).c_str())) {
			app.lock()->state.currentSelectedObject = object;
		}
	}

	imgui::End();
}