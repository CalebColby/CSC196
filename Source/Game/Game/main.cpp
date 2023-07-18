#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
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
	//Initialize Engine Systems
	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("assets");
	
	neu::g_renderer.Initialize();
	neu::g_renderer.CreateWindow("CSC196", 800,600);

	neu::g_inputSystem.Initialize();

	neu::g_audioSystem.Initialize();
	neu::g_audioSystem.AddAudio("hit", "Explosion.wav");

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

	neu::Scene scene;

	scene.Add(new Player{ 200, neu::Pi, { { 400, 300 }, 0, 3 }, model });

	for (size_t i = 0; i < 50; i++)
	{
		Enemy* enemy = new Enemy{ 300, neu::Pi, { { 400, 300 }, neu::randomf(neu::TwoPi), 3}, model };
		scene.Add(enemy);
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update Engine
		neu::g_Time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		//update Scene
		scene.Update(neu::g_Time.GetDeltaTime());

		//Detect Input
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			neu::g_audioSystem.PlayOneShot("hit");
		}
		
		//draw
		neu::g_renderer.SetColor(0, 0, 0, 0);
		neu::g_renderer.BeginFrame();
		for (auto& star : stars) 
		{
			star.Update(neu::g_renderer.GetWidth(), neu::g_renderer.GetHeight());

			neu::g_renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			neu::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		neu::g_renderer.SetColor(255, 255, 255, 255);
		scene.Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();
	}

	return 0;
}