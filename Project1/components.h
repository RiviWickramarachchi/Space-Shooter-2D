#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class CTransform
{
public:
	sf::Vector2f pos = { 0.0f, 0.0f };
	sf::Vector2f velocity = { 0.0f, 0.0f };
	float rotSpeed = 0.0f;

	CTransform(const sf::Vector2f p, const sf::Vector2f vel, float speed)
	{
		this->pos = p;
		this->velocity = vel;
		this->rotSpeed = speed;
	}
};

class CShape
{
public:
	sf::CircleShape circle;
	
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)

	:circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
		
	}
};

class CSprite
{
public:
	sf::Sprite sprite;
	CSprite(const sf::Vector2f scaleVec, const sf::Sprite sprt)
	:sprite(sprt)
	{
		sprite.setOrigin(sprite.getTexture()->getSize().x * 0.5f, sprite.getTexture()->getSize().y * 0.5f);
		sprite.setScale(scaleVec);
	}
};

class CCollision
{
public:
	float collisionRadius = 0.0f;
	CCollision(float r)
	{
		this->collisionRadius = r;
	}
};

class CHealth
{
public:
	//implement health
	float health = 0.0f;
	CHealth(float h)
	{
		this->health = h;
	}
};

class CDamage
{
public:
	float damage = 0.0f;

	CDamage(float d)
	{
		this->damage = d;
	}
};

class CPoints
{
public:
	float points = 0.0f;

	CPoints(int p)
	{
		this->points = p;
	}
};

class CInput
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;

	CInput() {}
};

class CLifespan
{
public:
	int remaining = 0;
	int total = 0;

	CLifespan(int tot)
	{
		this->total = tot;
		this->remaining = tot;
	}

};
