#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <vector>


using namespace std;

class Star
{
public:
	Star(const neu::Vector2 pos, const neu::Vector2 vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel;

		if (m_pos.x >= width) { m_pos.x = 0; }
		if (m_pos.y >= height) { m_pos.y = 0; }
	}

public:
	neu::Vector2 m_pos;
	neu::Vector2 m_vel;
};


int main(int argc, char* argv[])
{	
	neu::seedRandom((unsigned int)time(nullptr));

	

	neu::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800,600);

	vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf(renderer.GetWidth()), neu::randomf(renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(1,4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	
	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		//draw
		neu::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars) 
		{
			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}
		
		//renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
		//renderer.DrawLine(neu::random(renderer.GetWidth()), neu::random(renderer.GetHeight()),
		//neu::random(renderer.GetWidth()), neu::random(renderer.GetHeight()) );

		renderer.EndFrame();
	}



	return 0;
}