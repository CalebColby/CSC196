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
			((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;
		}
		
		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{	
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				float combinedRadius = (*iter1)->GetRadius() + (*iter2)->GetRadius();

				if (distance <= combinedRadius) 
				{
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
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