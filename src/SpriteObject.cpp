#include <SpriteObject.hpp>

#include <iostream>

#include <imgui_stdlib.h>

#include <portable-file-dialogs.h>

SpriteObject::SpriteObject()
	: Object(), texture(sf::Vector2u(1, 1)), sprite(texture)
{
	sprite.setTexture(texture, true);

	sprite.setOrigin(sf::Vector2f(texture.getSize().componentWiseDiv(sf::Vector2u(2, 2))));

	sprite.setPosition(sf::Vector2f(0, 0));

	SetName("Image " + std::to_string(GetTotalCreatedObjects()));
}

SpriteObject::SpriteObject(const std::filesystem::path& file)
	:	Object(), texture(file), sprite(texture), filename(file)
{
	// Needed to fix an issue with SFML, even if it is redundant
	SetTexture(file);

	SetName(file.generic_string());
}

void SpriteObject::Update()
{
	//sprite.setRotation(sf::degrees(sprite.getRotation().asDegrees()+1));
}

void SpriteObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void SpriteObject::SetPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

void SpriteObject::SetScale(sf::Vector2f scale)
{
	sprite.setScale(scale);
}

void SpriteObject::SetRotation(sf::Angle rotation)
{
	sprite.setRotation(rotation);
}

ObjectRectInfo SpriteObject::GetGlobalBounds() const
{
	return ObjectRectInfo {
		sprite.getPosition(),
		sprite.getScale().componentWiseMul(sf::Vector2f(texture.getSize())),
		sprite.getRotation()
	};
}

sf::Vector2f SpriteObject::GetPosition() const
{
	return sprite.getPosition();
}

sf::Vector2f SpriteObject::GetScale() const
{
	return sprite.getScale();
}

sf::Angle SpriteObject::GetRotation() const
{
	return sprite.getRotation();
}

void SpriteObject::Draw(sf::RenderTarget& target) const
{
	target.draw(sprite);
}

void SpriteObject::Move(sf::Vector2f amount)
{
	sprite.move(amount);
}

void SpriteObject::SetSize(sf::Vector2f size)
{
	const sf::Vector2f scaleAmount = size.componentWiseDiv(sf::Vector2f(texture.getSize()));

	SetScale(scaleAmount);
}

int SpriteObject::GetZLayer() const
{
	return zLayer;
}

void SpriteObject::SetZLayer(int layer)
{
	zLayer = layer;
}

void SpriteObject::Deserialize(const nlohmann::json& json)
{
	/*
	{
		"type": "SpriteObject",
		"filename": "image.png",
		"position": {
			"x": 100,
			"y": 100
		},
		"scale": {
			"x": 1,
			"y": 1
		},
		"angle": 0
	}
	*/

	SetTexture(json["filename"]);

	sprite.setPosition(sf::Vector2f(json["position"]["x"], json["position"]["y"]));
	sprite.setScale(sf::Vector2f(json["scale"]["x"], json["scale"]["y"]));
	sprite.setRotation(sf::radians(json["angle"]));

	SetName(json["name"]);

	filename = std::string(json["filename"]);
}

nlohmann::json SpriteObject::Serialize() const
{
	nlohmann::json json;

	json["type"] = "SpriteObject";
	json["filename"] = filename.generic_string();
	json["name"] = GetName();

	json["position"] = {
		{"x", sprite.getPosition().x},
		{"y", sprite.getPosition().y}
	};

	json["scale"] = {
		{"x", sprite.getScale().x},
		{"y", sprite.getScale().y}
	};

	json["angle"] = sprite.getRotation().asRadians();

	return json;
}

void SpriteObject::DisplayCustomDetailComponents()
{
	std::string filenameStr = filename.generic_string();

	imgui::Text("Filename: ");

	imgui::SameLine();

	imgui::BeginDisabled();
	imgui::InputText("##filename", &filenameStr);
	imgui::EndDisabled();

	imgui::SameLine();

	if (imgui::Button("...")) {
		auto result = pfd::open_file("Select a new image", ".", { "Image Files", "*.bmp *.png *.tga *.jpg *.gif *.psd *.hdr *.pic *.pnm" });

		if (!result.result().empty()) {
			std::string file = result.result()[0];

			SetTexture(file);
		}
	}
}

void SpriteObject::SetTexture(const std::filesystem::path& newTexture)
{
	texture.loadFromFile(newTexture);

	filename = newTexture;

	sprite.setTexture(texture, true);

	sprite.setOrigin(sf::Vector2f(texture.getSize().componentWiseDiv(sf::Vector2u(2, 2))));

	SetName(newTexture.generic_string());
}