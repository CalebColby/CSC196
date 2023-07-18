#pragma once
#include "Actor.h"
#include <list>

namespace neu
{
	class Renderer;
	class Actor;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor>);
		void Remove(Actor* actor);
		void RemoveAll();

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};
}