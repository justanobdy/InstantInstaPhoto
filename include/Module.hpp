#pragma once

#include <SFML/Graphics/Drawable.hpp>

#include <AppState.hpp>

class App;

class Module : public sf::Drawable {
public:
	Module(std::weak_ptr<App> app);

	int GetID() const;

	virtual void Update() = 0;

	void QueueFree();

	bool QueuedForDeletion() const;
protected:
	std::weak_ptr<App> app;

	int ID;
private:
	static int lastID;

	bool queuedForDeletion = false;
};

/// <summary>
/// Class for modules which use only ImGui, so no drawing required
/// </summary>
class ImGuiModule : public Module {
public:
	ImGuiModule(std::weak_ptr<App> app)
		:	Module(app)
	{ }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const final override {}
};