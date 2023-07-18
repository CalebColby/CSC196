#pragma once
#include "Framework/Actor.h"
#include <Audio/AudioSystem.h>

class Bullet : public neu::Actor
{
public:
	Bullet(float speed, const neu::Transform& transform, const neu::Model& model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
	}


	void Update(float dt) override;

private:
	float m_speed = 0;
};