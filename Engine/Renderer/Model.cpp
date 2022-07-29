#include "Model.h"
#include "../Core/File.h"
#include <sstream>
#include <iostream>

namespace cool
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}


	void Model::Draw(Renderer& renderer, const Vector2& position,float angle, float scale)
	{
		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			cool::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			cool::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}

	}

	void Model::Load(const std::string& filename)
	{
		std::string buffer;

		cool::ReadFile(filename, buffer);

		//Read color
		std::istringstream stream(buffer);
		stream >> m_color;
		std::string line;
		std::getline(stream, line);

		//get number o points
		size_t numPoints = std::stoi(line);

		//read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		//finds the largest length (radius)
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}

}


