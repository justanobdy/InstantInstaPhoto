#pragma once

#include <Common.hpp>

#include <nlohmann/json.hpp>

#define STRINGIFY(x) #x
#define DEFINE_OBJECT(c) \
template<> \
struct ObjectName<c> { \
	std::string GetName() { \
		return STRINGIFY(c); \
	} \
};

bool rectContainsPoint(sf::Vector2f point, sf::Vector2f rectPosition, sf::Vector2f rectSize, sf::Angle angle);
bool rectContainsPoint(sf::Vector2f point, sf::Vector2f rectPosition, sf::Vector2f rectSize, sf::Vector2f origin, sf::Angle angle);

sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f origin, sf::Angle angle);

std::array<sf::Vector2f, 4> getCorners(sf::Vector2f position, sf::Vector2f size, sf::Angle angle, sf::Vector2f origin);

struct ObjectRectInfo {
	// Center of position
	sf::Vector2f position;

	sf::Vector2f size;

	// Rotation (in radians)
	sf::Angle angle;

	sf::Vector2f origin;

	ObjectRectInfo()
	{ }

	ObjectRectInfo(sf::Vector2f position, sf::Vector2f size, sf::Angle angle)
		: position(position), size(size), angle(angle)
	{ }

	bool contains(sf::Vector2f position) const;
	std::array<sf::Vector2f, 4> getCorners() const;
};

class Object : public sf::Drawable {
public:
	//virtual void OnClick() = 0;

	Object() 
		:	ID(lastID++)
	{
		totalCreatedObjects++;
	}

	virtual void Update() = 0;

	virtual void SetPosition(sf::Vector2f position) = 0;
	virtual void SetScale(sf::Vector2f scale) = 0;
	virtual void SetRotation(sf::Angle rotation) = 0;

	virtual sf::Vector2f GetPosition() const = 0;
	virtual sf::Vector2f GetScale() const = 0;
	virtual sf::Angle GetRotation() const = 0;

	virtual void SetSize(sf::Vector2f size) = 0;

	virtual ObjectRectInfo GetGlobalBounds() const = 0;

	virtual void Move(sf::Vector2f amount) = 0;

	virtual void Draw(sf::RenderTarget& target) const = 0;

	virtual void Deserialize(const nlohmann::json& json) = 0;

	virtual nlohmann::json Serialize() const = 0;

	virtual int GetZLayer() const = 0;

	virtual void SetZLayer(int newLayer) = 0;

	virtual void DisplayCustomDetailComponents() {};

	void SetName(const std::string& newName);

	const std::string& GetName() const;

	std::unordered_map<std::string, int> metadata;

	static int GetTotalCreatedObjects();

	bool QueuedForDeletion() const;

	void QueueDelete();

	const int ID;
private:
	static int totalCreatedObjects;

	static int lastID;

	std::string name;

	bool queuedForDeletion = false;
};

template <typename T>
struct ObjectName {
	std::string GetName() {
		return "Default Implementation";
	}
};