#include "Scene.h"
#include "Actor.h"

namespace neu
{
	void Scene::Update(float dt)
	{
		//for (auto& actor : m_actors) actor->Update(dt);

		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			(*iter)->Update(dt);
			//remove destroyed actors
			if ((*iter)->m_destroyed) iter = m_actors.erase(iter);
			else iter++;
		}
		
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
}