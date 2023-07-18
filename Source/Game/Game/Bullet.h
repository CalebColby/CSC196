#pragma once
#include "Framework/Actor.h"

class Bullet : public neu::Actor
{
public:
	Bullet(float speed, const neu::Transform& transform, const neu::Model& model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}


	void Update(float dt) override;

private:
	float m_speed = 0;
};