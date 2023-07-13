#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player(float speed, float turnRate, const neu::Transform& transform, const neu::Model& model) : 
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}


	void Update(float dt) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};