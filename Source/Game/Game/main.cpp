#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>
#include <thread>

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
		m_pos += m_vel * neu::g_Time.GetDeltaTime();

		if (m_pos.x >= width) { m_pos.x = 0; }
		if (m_pos.y >= height) { m_pos.y = 0; }
	}

public:
	neu::Vector2 m_pos;
	neu::Vector2 m_vel;
};


int main(int argc, char* argv[])
{	
	//constexpr float a = neu::DegreesToRadians(180.0f);

	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("assets");
	

	neu::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800,600);

	neu::InputSystem inputSystem;
	inputSystem.Initialize();

	//std::vector<neu::Vector2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, {-10, 5} };
	neu::Model model;
	model.Load("Ship.txt");


	std::vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf(renderer.GetWidth()), neu::randomf(renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(100,400), neu::randomf(-200, 200));

		stars.push_back(Star(pos, vel));
	}

	neu::Transform transform{ { 400, 300 }, 0, 3 };

	//neu::Vector2 position{ 400, 300 };
	float speed = 500;
	float turnRate = neu::DegreesToRadians(180);


	//main game loop
	bool quit = false;
	while (!quit)
	{
		neu::g_Time.Tick();
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		float rotate = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnRate * neu::g_Time.GetDeltaTime();

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

		neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forward * speed * thrust * neu::g_Time.GetDeltaTime();
		transform.position.x = neu::Wrap(transform.position.x, renderer.GetWidth());
		transform.position.y = neu::Wrap(transform.position.y, renderer.GetHeight());

		//neu::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
		//position += direction * speed * neu::g_Time.GetDeltaTime();


		if (inputSystem.GetMouseButtonDown(0)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Left Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
		}

		if (inputSystem.GetMouseButtonDown(1)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Mid Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
		}

		if (inputSystem.GetMouseButtonDown(2)) {
			neu::Vector2 Mpos{inputSystem.GetMousePosition()};
			std::cout << "Right Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
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
		
		model.Draw(renderer, transform.position, transform.rotation, transform.scale );

		renderer.EndFrame();

		//std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}

	return 0;
}