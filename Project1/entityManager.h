#include "entity.h"
#include <iostream>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager {

	EntityVector entitiesInGame;
	EntityVector entitiesToAdd;
	EntityMap gameEntityMap;
	size_t totalEntitiesMade = 0;

public:
	std::shared_ptr<Entity> AddEntity(const std::string& tag, bool movable);
	std::shared_ptr<Entity> AddEntity(const std::string& tag);
	void RemoveDeadEntities(EntityVector& vec);
	void Update();
	EntityVector& GetEntities();
	EntityVector& GetEntities(const std::string& tag);
};