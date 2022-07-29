#pragma once
#include "../Engine/Framework/Actor.h"

class Enemy : public cool::Actor
{
public:
	Enemy() = default;
	Enemy(const cool::Model& model, const cool::Transform& transform, float health = 1)
		: Actor{ model, transform },
		m_health{ health } {
		Initialize();
	}

	void Initialize();

	void Update() override;

	void OnCollision(Actor* other) override;

private:
	float m_health = 1;

	float m_speed = 10;
	float m_fireTimer = 0;
};