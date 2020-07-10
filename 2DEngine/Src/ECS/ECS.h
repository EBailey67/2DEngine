#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;


using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};

	virtual ~Component() {};

};

class Entity
{
private:
	bool isActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void Update()
	{
		for (auto& c : components)
			c->Update();
	}

	void Draw()
	{
		for (auto& c : components)
			c->Draw();
	}

	bool IsActive()
	{
		return isActive;
	}

	void Destroy()
	{
		isActive = false;
	}

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);

		return *static_cast<T*>(ptr);
	}
};


class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void Update()
	{
		for (auto& e : entities)
			e->Update();
	}

	void Draw()
	{
		for (auto& e : entities)
			e->Draw();
	}

	void Refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(entities));

	}

	Entity& AddEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
class ECS
{
};

