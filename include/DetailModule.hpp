#pragma once

#include <SFML/Graphics.hpp>

#include <Module.hpp>

class DetailModule : public Module {
public:
	using Module::Module;

	void Update() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
};