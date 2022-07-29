#include "SpaceBlast.h"
#include "Player.h"
#include "Enemy.h"
#include "../Engine/Engine.h"
#include <memory>

void SpaceBlast::Initialize()
{
	m_scene = std::make_unique<cool::Scene>(this);

	//m_player = std::make_unique<cool::Player>(this);


	//create assests
	cool::g_audioSystem.AddAudio("laser", "laser.wav");
	cool::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	cool::g_audioSystem.AddAudio("Music", "SpaceBattle.mp3");

	m_font = std::make_unique<cool::Font>("pkmnrs.ttf", 25);
	m_scoreText = std::make_unique<cool::Text>(m_font.get());
	m_scoreText->Create(cool::g_renderer, "00000", { 255,255,255,255 });

	//transform
	cool::Transform transform;
	transform.position = cool::Vector2{ 400,300 };
	transform.rotation = 0;
	transform.scale = 4;


	//cool::Vector2 position{ 400, 300 };
	//float angle = 0;

	std::unique_ptr<Player> player = std::make_unique<Player>(cool::Model{ "player.txt" }, transform);
	m_scene->Add(std::move(player));

	cool::g_audioSystem.PlayAudio("Music");

	//model
	for (int i = 0; i < 3; i++)
	{
		transform.position.x = cool::random(800);
		transform.position.y = cool::random(600);
		transform.rotation = cool::randomf(math::TwoPi);
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cool::Model{ "enemy.txt" }, transform, 10.0f);
		m_scene->Add(std::move(enemy));
	}
}

void SpaceBlast::Shutdown()
{

}

void SpaceBlast::Update()
{

	//spawn enemies
	m_spawnTimer -= cool::g_time.deltaTime;
	if (m_spawnTimer <= 0)
	{
		m_enemyType = cool::random(1,2);
		m_spawnTimer = 3;

		cool::Transform transform;
		transform.position.x = cool::random(800);
		transform.position.y = cool::random(600);
		transform.rotation = cool::randomf(math::TwoPi);
		transform.scale = 4;
		if (m_enemyType == 1) 
		{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cool::Model{ "enemy.txt" }, transform, 10.0f);
		m_scene->Add(std::move(enemy));
		}
		else if (m_enemyType == 2)
		{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(cool::Model{ "SpearEnemy.txt" }, transform, 10.0f);
		m_scene->Add(std::move(enemy));
		}


	//update scene
	m_scene->Update();

	//update score text
	m_scoreText->Create(cool::g_renderer, std::to_string(m_score), { 0,255,255,255 });
	}


	m_scene->Update();
}

void SpaceBlast::Draw(cool::Renderer& renderer)
{
	//renderer game
	m_scene->Draw(renderer);
	m_scoreText->Draw(renderer, { 400,50 });
}
