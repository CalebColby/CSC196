#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
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
	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("assets");
	
	neu::g_renderer.Initialize();
	neu::g_renderer.CreateWindow("CSC196", 800,600);

	neu::g_inputSystem.Initialize();

	//std::vector<neu::Vector2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, {-10, 5} };
	neu::Model model;
	model.Load("Ship.txt");


	std::vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf((float)neu::g_renderer.GetWidth()), neu::randomf((float)neu::g_renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(100,400), neu::randomf(-200, 200));

		stars.push_back(Star(pos, vel));
	}

	neu::Transform transform{ { 400, 300 }, 0, 3 };
	float speed = 500;
	constexpr float turnRate = neu::DegreesToRadians(180);

	Player player{ 200, neu::Pi, { { 400, 300 }, 0, 3 }, model };

	std::vector<Enemy> enemies;
	for (size_t i = 0; i < 200; i++)
	{
		Enemy enemy{ 300, neu::Pi, { { 400, 300 }, neu::randomf(neu::TwoPi), 3}, model };
		enemies.push_back(enemy);
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update Engine
		neu::g_Time.Tick();
		neu::g_inputSystem.Update();
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//update Player
		player.Update(neu::g_Time.GetDeltaTime());
		for(auto& enemy : enemies) enemy.Update(neu::g_Time.GetDeltaTime());
		

		//neu::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
		//position += direction * speed * neu::g_Time.GetDeltaTime();


		if (neu::g_inputSystem.GetMouseButtonDown(0)) {
			neu::Vector2 Mpos{neu::g_inputSystem.GetMousePosition()};
			std::cout << "Left Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
		}

		if (neu::g_inputSystem.GetMouseButtonDown(1)) {
			neu::Vector2 Mpos{neu::g_inputSystem.GetMousePosition()};
			std::cout << "Mid Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
		}

		if (neu::g_inputSystem.GetMouseButtonDown(2)) {
			neu::Vector2 Mpos{neu::g_inputSystem.GetMousePosition()};
			std::cout << "Right Click at X: " << Mpos.x << ", Y: " << Mpos.y << std::endl;
		}

		neu::g_renderer.SetColor(0, 0, 0, 0);
		neu::g_renderer.BeginFrame();
		
		//draw

		for (auto& star : stars) 
		{
			star.Update(neu::g_renderer.GetWidth(), neu::g_renderer.GetHeight());

			neu::g_renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			neu::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		neu::g_renderer.SetColor(255, 255, 255, 255);

		player.Draw(neu::g_renderer);
		for (auto& enemy : enemies) enemy.Draw(neu::g_renderer);
		
		//model.Draw(renderer, transform.position, transform.rotation, transform.scale );

		neu::g_renderer.EndFrame();
	}

	return 0;
}