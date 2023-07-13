#pragma once
#include <vector>
#include "Renderer.h"
#include <Core/Vector2.h>
#include <Core/Transform.h>

namespace neu
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& fileName);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

	private:
		std::vector<vec2> m_points;
	};
}