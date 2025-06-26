#include <Common.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <SpriteObject.hpp>
#include <App.hpp>
#include <SelectModule.hpp>
#include <DetailModule.hpp>
#include <ObjectListModule.hpp>
#include <ObjectContextModule.hpp>
#include <MenuBarModule.hpp>

//TODO:
// Add settings window
// Allow multiple items to be selected

int Object::lastID = 0;

int main() {
    std::shared_ptr<App> app = App::Create();

    // This must always be first
    app->AddModule<MenuBarModule>();

    app->AddModule<SelectModule>();
    app->AddModule<DetailModule>();
    app->AddModule<ObjectListModule>();
    app->AddModule<ObjectContextModule>();

    app->run();

    return 0;
}