#include "entity.h"

Entity::Entity(const size_t id, const std::string& tag)
	: id(id), tag(tag)
{}

Entity::Entity(const size_t id, const std::string& tag, bool movable)
	: id(id), tag(tag), isMovable(movable)
{}

int Entity::GetId() const
{
	return id;
}

const std::string& Entity::GetTag() const
{
	return tag;
}

bool Entity::IsAlive() const
{
	return alive;
}

bool Entity::IsMovable() const
{
	return isMovable;
}

void Entity::Destroy()
{
	alive = false;
}
