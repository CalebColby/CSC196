#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"
#include <iostream>


using namespace std;


int main(int argc, char* argv[])
{
	auto renderer = new neu::Renderer();

	renderer->CreateWindow("Test", 800,600);
	
	while (true)
	{
		renderer->BeginFrame();

		renderer->DrawLine(neu::random(renderer->GetWidth()), neu::random(renderer->GetHeight()),
			neu::random(renderer->GetWidth()), neu::random(renderer->GetHeight()) );

		renderer->EndFrame();
	}



	return 0;
}