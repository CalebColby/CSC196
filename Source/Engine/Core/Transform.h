#pragma once
#include "Vector2.h"

namespace neu
{
	class Transform
	{
	public:
		Vector2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			position { position },
			rotation { rotation },
			scale { scale }
		{}
	};
}