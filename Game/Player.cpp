#include "Player.h"
#include "Bullet.h"
#include "../Engine/Engine.h"

void Player::Update()
{
	cool::g_inputSystem.Update();
	//rotation movement
	if (cool::g_inputSystem.GetKeyDown(cool::key_left))
	{
		m_transform.rotation -= math::Pi * cool::g_time.deltaTime;
	}

	if (cool::g_inputSystem.GetKeyDown(cool::key_right))
	{
		m_transform.rotation += math::Pi * cool::g_time.deltaTime;
	}

	//thrust
	m_speed = cool::random(1,10);
	if (cool::g_inputSystem.GetKeyDown(cool::key_up))
	{
		m_speed = m_maxSpeed;
	}

	//directional movement
	cool::Vector2 direction{ 1, 0 };
	direction = cool::Vector2::Rotate(direction, m_transform.rotation);
	cool::Vector2 force = direction * m_speed *  cool::g_time.deltaTime;

	//apply force to velocity
	m_velocity += force;

	//apply drag
	m_velocity *= 1.0f / (1.0f + m_damping * cool::g_time.deltaTime);
	//move entity
	m_transform.position += m_velocity * cool::g_time.deltaTime;

	//wrap
	if (m_transform.position.x > cool::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)cool::g_renderer.GetWidth();

	if (m_transform.position.y > cool::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)cool::g_renderer.GetHeight();

	m_fireTimer -= cool::g_time.deltaTime;
//shoot
	if (cool::g_inputSystem.GetKeyState(cool::key_space)==(cool::InputSystem::State::Held) && m_fireTimer <=0)
	{
		//play sound
		m_fireTimer = 0.2;
		cool::g_audioSystem.PlayAudio("laser");
		//fire
		cool::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(cool::Model{ "bullet.txt" }, transform, 5);
		bullet->GetTag() = "player";
		m_scene->Add(std::move(bullet));
	}
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "enemy")
	{
		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0) {
			cool::g_audioSystem.PlayAudio("explosion");
			
			m_destroy = true;
		}
	}
}
