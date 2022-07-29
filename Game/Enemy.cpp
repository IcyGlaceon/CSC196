#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "../Engine/Engine.h"

void Enemy::Initialize()
{
	m_fireTimer = cool::randomf(2, 6);
	m_speed = cool::randomf(20, 100);
}

void Enemy::Update()
{
	//fire
	m_fireTimer -= cool::g_time.deltaTime;
	if (m_fireTimer <= 0)
	{

		m_fireTimer = cool::randomf(2, 6);
		cool::Transform transform = m_transform;
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(cool::Model{ "enemy Bullet.txt" }, transform);
		bullet->GetTag() = "enemy";
		m_scene->Add(std::move(bullet));
	}

	//set rotaion to player
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		cool::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.GetAngle();
	}

	//velocity
	cool::Vector2 direction{ 1, 0 };
	direction = cool::Vector2::Rotate(direction, m_transform.rotation);
	cool::Vector2 velocity = direction * m_speed * cool::g_time.deltaTime;

	m_transform.position += (velocity);

	//wrap
	if (m_transform.position.x > cool::g_renderer.GetWidth()) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = (float)cool::g_renderer.GetWidth();

	if (m_transform.position.y > cool::g_renderer.GetHeight()) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = (float)cool::g_renderer.GetHeight();
}

void Enemy::OnCollision(Actor* other)
{
	if (dynamic_cast<Bullet*>(other) && other->GetTag() == "player")
	{
		//play explosion sound
		cool::g_audioSystem.PlayAudio("explosion");

		m_health -= dynamic_cast<Bullet*>(other)->GetDamage();

		if (m_health <= 0)
		{
			m_destroy = true;
			m_scene->GetGame()->AddPoints(100);

		}
	}
}
