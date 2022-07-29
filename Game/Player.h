#pragma once
#include "../Engine/Framework/Actor.h"

class Player : public cool::Actor
{
public:
	Player() = default;
	Player(const cool::Model& model, const cool::Transform& transform)
		: Actor{ model, transform } {}
	
	void Update() override;

	void OnCollision(Actor* other) override;

	float GetHealth() { return m_health; }

private:
	float m_health = 50;

	float m_speed = 0;
	float m_maxSpeed = 300;

	float m_fireTimer = 0.2;
};