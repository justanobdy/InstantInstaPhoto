#pragma once

#include <Object.hpp>
#include <filesystem>

class SpriteObject : public Object {
public:
	SpriteObject(std::weak_ptr<App> app);
	SpriteObject(std::weak_ptr<App> app, const std::filesystem::path& file);

	void Update() override;

	void SetPosition(sf::Vector2f position) override;
	void SetScale(sf::Vector2f scale) override;
	void SetRotation(sf::Angle rotation) override;

	sf::Vector2f GetPosition() const override;
	sf::Vector2f GetScale() const override;
	sf::Angle GetRotation() const override;

	ObjectRectInfo GetGlobalBounds() const override;

	void Deserialize(const nlohmann::json& json) override;
	nlohmann::json Serialize() const override;

	void Move(sf::Vector2f amount) override;

	void SetSize(sf::Vector2f amount) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void Draw(sf::RenderTarget& target) const override;

	int GetZLayer() const override;

	void SetZLayer(int layer) override;

	void DisplayCustomDetailComponents() override;

	void SetTexture(const std::filesystem::path& newTexture);
private:
	void initEmpty();

	sf::Sprite sprite;
	sf::Texture texture;

	std::filesystem::path filename;

	int zLayer = 0;
};

DEFINE_OBJECT(SpriteObject)