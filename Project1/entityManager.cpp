#include "entityManager.h"

void EntityManager::Update()
{
	//add entities in the entitiesToAdd vector in the beginning of each frame
	for (auto entity : entitiesToAdd)
	{
		entitiesInGame.push_back(entity);
		gameEntityMap[entity->tag].push_back(entity);
	}
	entitiesToAdd.clear();

	//remove entities that are not alive
	RemoveDeadEntities(entitiesInGame);

	//remove dead entities from the map
	for (auto& pair : gameEntityMap)
	{
		RemoveDeadEntities(pair.second);
	}
}

EntityVector& EntityManager::GetEntities()
{
	return entitiesInGame;
}

EntityVector& EntityManager::GetEntities(const std::string& tag)
{
	return gameEntityMap[tag];
}


void EntityManager::RemoveDeadEntities(EntityVector& vec)
{
	//this lambda function checks if an entity is not alive
	auto isDead = [](std::shared_ptr<Entity>& entity) { return !entity->IsAlive();};
	//move all the dead entities to the end of the list and get the new end point
	auto newEnd = std::remove_if(vec.begin(), vec.end(), isDead);
	//remove all the entities that are beyond the new end point
	vec.erase(newEnd, vec.end());
}

std::shared_ptr<Entity> EntityManager::AddEntity(const std::string& tag, const bool movable)
{
	auto entity = std::shared_ptr<Entity>(new Entity(totalEntitiesMade++, tag,movable));
	entitiesToAdd.push_back(entity);
	return entity;
}
std::shared_ptr<Entity> EntityManager::AddEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(totalEntitiesMade++, tag));
	entitiesToAdd.push_back(entity);
	return entity;
}


