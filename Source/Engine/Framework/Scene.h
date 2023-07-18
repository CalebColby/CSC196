#pragma once
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

		void Add(Actor* actor);
		void Remove(Actor* actor);
		void RemoveAll();

		friend class Actor;

	private:
		std::list<Actor*> m_actors;
	};
}