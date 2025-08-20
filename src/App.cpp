#include <App.hpp>

#include <SpriteObject.hpp>

App::App()
{
    ApplySettings(state.projectSettings);

    SetupObjectMap();
}

void App::SetupObjectMap()
{
    createMap["SpriteObject"] = [this](const nlohmann::json& json) {
        AddObject<SpriteObject>().lock()->Deserialize(json);
        };
}

void App::AddObjectFromJson(const nlohmann::json& json) {
    createMap[json["type"]](json);
}

void theme(ImGuiStyle* style) {
    style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style->Colors[ImGuiCol_Separator] = style->Colors[ImGuiCol_Border];
    style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    style->Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    style->Colors[ImGuiCol_DockingPreview] = ImVec4(0.667f, 0.727f, 0.797f, 0.7f);
    style->GrabRounding = style->FrameRounding = 4;
    style->WindowRounding = 5;

    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
    colors[ImGuiCol_Button] = ImVec4(0.11f, 0.11f, 0.12f, 1.00f);

    colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.058f, 1.f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.17f, 0.17f, 0.18f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.18f, 1.00f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.13f, 0.14f, 1.00f);

    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.15f, 0.16f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.39f, 0.39f, 0.40f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.35f, 0.36f, 1.00f);

    style->PopupRounding = 4;

    style->WindowBorderSize = 0;
}

void App::run()
{
    Init();

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            HandleEvents(event);
        }

        viewCenter = view.getCenter();
        window.setView(view);

        //TODO:
        // Add keyboard shortcuts
        // add better error handling everywhere

        Update();

        Draw();

        CleanObjects();
    }

    ImGui::SFML::Shutdown();
}

void App::RemoveObjectByID(int ID)
{
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->ID == ID) {
            if (state.currentSelectedObject.has_value() && state.currentSelectedObject.value().lock()->ID == objects[i]->ID) {
                state.currentSelectedObject = std::nullopt;
            }

            objects.erase(objects.begin() + i);

            return;
        }
    }
}

void App::NewProject(const ProjectSettings& settings)
{
    state.currentSelectedObject = std::nullopt;

    objects.clear();

    ApplySettings(settings);
}

std::vector<std::shared_ptr<Object>>& App::GetObjects()
{
    return objects;
}

void App::ApplySettings(const ProjectSettings& newSettings)
{
    state.projectSettings = newSettings;

    previewRectangle.setSize(sf::Vector2f(state.projectSettings.imageResolution.x * state.projectSettings.totalSlides, state.projectSettings.imageResolution.y));
    previewRectangle.setFillColor(state.projectSettings.backgroundColor);

    slideOutlines.clear();

    for (int i = 0; i < state.projectSettings.totalSlides; i++) {
        sf::Vector2f position = sf::Vector2f(state.projectSettings.imageResolution.x * i, 0);
        
        sf::RectangleShape newShape;

        newShape.setSize(state.projectSettings.imageResolution);
        newShape.setPosition(position);
        newShape.setFillColor(sf::Color::Transparent);
        newShape.setOutlineColor(sf::Color(50, 50, 50));
        newShape.setOutlineThickness(2);

        slideOutlines.push_back(newShape);
    }
}

void App::ApplyAppSettings(const Settings &newSettings) {
    // shouldApply = true

    imgui::GetIO().Fonts->AddFontFromFileTTF("fnt/InterVariable.ttf", newSettings.fontScale);
}

void App::HandleEvents(const std::optional<sf::Event>& event)
{
    if (event->is<sf::Event::Closed>()) {
        window.close();
    }

    if (const auto* resized = event->getIf<sf::Event::Resized>())
    {
        sf::FloatRect visibleArea({ 0, 0 }, sf::Vector2f(resized->size).componentWiseDiv(state.zoomFactor));

        view = sf::View(visibleArea);

        view.setCenter(viewCenter);
    }

    if (const auto* mouse = event->getIf<sf::Event::MouseMoved>()) {
        if (!state.draggingObjectPosition && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && state.currentSelectedObject != std::nullopt && state.currentSelectedObject.value().lock()->GetGlobalBounds().contains(state.GetMousePosition()) && !imgui::GetIO().WantCaptureMouse) {
            //selectedObject->lock()->SetPosition(sf::Vector2f(currentMousePosition));
            dragOffset = state.GetMousePosition() - state.currentSelectedObject->lock()->GetPosition();
            state.draggingObjectPosition = true;
        }
    }

    if (const auto dropped = event->getIf<sf::Event::FilesDropped>()) {
        for (const auto& item : dropped->filenames) {
            AddObject<SpriteObject>(std::filesystem::path(item));
        }
    }

    if (const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
        state.zoomFactor += sf::Vector2f(scroll->delta / 10, scroll->delta / 10);

        if (state.zoomFactor.x < 0.05f)
            state.zoomFactor.x = 0.05f;
        if (state.zoomFactor.y < 0.05f)
            state.zoomFactor.y = 0.05f;

        sf::FloatRect visibleArea(viewCenter, sf::Vector2f(window.getSize()).componentWiseDiv(state.zoomFactor));

        view = sf::View(visibleArea);

        view.setCenter(viewCenter);
    }
}

void App::Init()
{
    state.window = &window;

    const sf::Vector2u windowSize = sf::Vector2u(640, 480);

    window.create(sf::VideoMode(windowSize), "Instant Insta Photo");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window, false);

    theme(&imgui::GetStyle());

    view = sf::View(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(windowSize)));

    //imgui::GetIO().FontGlobalScale = 1.5f;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    imgui::GetIO().Fonts->ClearFonts();
    imgui::GetIO().Fonts->AddFontFromFileTTF("fnt/InterVariable.ttf", 16); // TODO: this should be in a settings window, not hardcoded

    imgui::SFML::UpdateFontTexture();

    window.setFileDroppingEnabled(true);

    state.view = &view;
}

void App::Update() {
    // Update ImGui

    ImGui::SFML::Update(window, deltaClock.restart());

    imgui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

    // Handle panning view

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) || (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && state.currentSelectedObject == std::nullopt)) && (window.hasFocus() && !imgui::GetIO().WantCaptureMouse)) {
        if (!isDraggingView) {
            isDraggingView = true;

            originalMousePosition = sf::Mouse::getPosition();
            originalViewPosition = view.getCenter();
        }

        auto mousePos = sf::Mouse::getPosition();

        // TODO: look into why this is messed up on mac
        sf::Vector2f delta = sf::Vector2f(mousePos - originalMousePosition);

        view.setCenter(originalViewPosition - delta.componentWiseDiv(state.zoomFactor));
    }
    else {
        isDraggingView = false;
    }

    // Update modules and objects

    for (const auto& item : objects) {
        item->Update();
    }

    for (const auto& module : modules) {
        module->Update();
    }

    // Handle dragging objects

    // This needs to be after updating objects and modules, due to weirdness with SelectModule
    // TODO (if you dare): fix this ^^^^

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        state.draggingObjectPosition = false;
    }

    if (state.draggingObjectPosition) {
        state.currentSelectedObject->lock()->SetPosition(state.GetMousePosition() - dragOffset);
    }

    if (imgui::IsMouseClicked(ImGuiMouseButton_Left)) {
        auto mousePos = state.GetMousePosition();

        if (!imgui::GetIO().WantCaptureMouse)
            state.currentSelectedObject = std::nullopt;

        for (int i = objects.size() - 1; i >= 0; i--) {
            auto& item = objects[i];

            if (item->GetGlobalBounds().contains(mousePos)) {
                state.currentSelectedObject = item;

                break;
            }
        }
    }
}

void App::Draw()
{
    std::sort(objects.begin(), objects.end(), [](std::shared_ptr<Object>& first, std::shared_ptr<Object>& second) {
        return first->GetZLayer() < second->GetZLayer();
        });

    window.clear();

    window.draw(previewRectangle);

    for (const auto& shape : slideOutlines) {
        window.draw(shape);
    }

    for (const auto& item : objects) {
        item->Draw(window);
    }

    for (const auto& module : modules) {
        window.draw(*module);
    }

    ImGui::SFML::Render(window);
    window.display();
}

void App::CleanObjects()
{
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->QueuedForDeletion()) {
            if (state.currentSelectedObject.has_value() && state.currentSelectedObject.value().lock()->ID == objects[i]->ID) {
                state.currentSelectedObject = std::nullopt;
            }

            objects.erase(objects.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < modules.size(); i++) {
        if (modules[i]->QueuedForDeletion()) {
            modules.erase(modules.begin() + i);
            i--;
        }
    }
}