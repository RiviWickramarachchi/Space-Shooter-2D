#include <string>
#include "components.h"
class Entity {

	friend class EntityManager;
	size_t id = 0;
	std::string tag = "Default";
	bool alive = true;
	bool isMovable = false;

	Entity(const size_t id, const std::string& tag);
	Entity(const size_t id, const std::string& tag, bool movable);
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CSprite> cSprite;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CHealth> cHealth;
	std::shared_ptr<CLifespan> cLifespan;
	std::shared_ptr<CDamage> cDamage;
	std::shared_ptr<CPoints> cPoints;

	int GetId() const;
	const std::string& GetTag() const;
	bool IsAlive() const;
	bool IsMovable() const;
	void Destroy();

};

