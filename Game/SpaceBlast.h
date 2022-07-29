#pragma once
#include "../Engine/Framework/Game.h"

namespace cool
{
	class Font;
	class Text;
}

class SpaceBlast : public cool::Game
{
public:
	SpaceBlast() = default;
	~SpaceBlast() = default;

	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(cool::Renderer& renderer) override;

private:
	float m_spawnTimer = 0;
	int m_enemyType = 0;
	std::unique_ptr<cool::Font> m_font;
	std::unique_ptr<cool::Text> m_scoreText;
	std::unique_ptr<cool::Text> m_healthText;
};