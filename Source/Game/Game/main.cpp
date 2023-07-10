#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
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

	neu::InputSystem inputSystem;
	inputSystem.Initialize();

	std::vector<neu::Vector2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, {-10, 5} };
	neu::Model model(points);



	vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf(renderer.GetWidth()), neu::randomf(renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(1,4), neu::randomf(-2.0f, 2.0f));

		stars.push_back(Star(pos, vel));
	}

	bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (inputSystem.GetMouseButtonDown(0)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Left Click at X: " << Mpos.x << ", Y: " << Mpos.y << endl;
		}

		if (inputSystem.GetMouseButtonDown(1)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Mid Click at X: " << Mpos.x << ", Y: " << Mpos.y << endl;
		}

		if (inputSystem.GetMouseButtonDown(2)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Right Click at X: " << Mpos.x << ", Y: " << Mpos.y << endl;
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		//draw

		for (auto& star : stars) 
		{
			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		renderer.SetColor(255, 255, 255, 255);
		
		model.Draw(renderer, {500, 500}, 4.0f );

		renderer.EndFrame();
	}

	return 0;
}