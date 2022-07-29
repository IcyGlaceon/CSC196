#pragma once
#include "Renderer.h"
#include <string>
#include <vector>


namespace cool
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<cool::Vector2>& points, const cool::Color& color) :
			m_points{ points },
			m_color { color }
		{
		}
		Model(const std::string& filename);

		void Draw(Renderer& renderer,const Vector2& position, float angle, float scale = 1);

		void Load(const std::string& filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }

	private:
		std::vector<cool::Vector2> m_points;
		cool::Color m_color{ 0,0,0,0 };

		float m_radius = 0;
	};
}