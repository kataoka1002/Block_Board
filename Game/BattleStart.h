#pragma once
class Junban;
class Player2;

class BattleStart : public IGameObject
{
public:
	BattleStart();
	~BattleStart();
	void Render(RenderContext& rc);
	void Update();

	float ScaleX = 0.01, ScaleY = 0.01;
	bool gazoset = false;

	float kamiposiRX = 1700, kamiposiRY = 700;
	float kamiposiLX = -1700, kamiposiLY = 700;

	SpriteRender battlestart;
	SpriteRender kaminariR;
	SpriteRender kaminariL;

	Junban* junban = nullptr;
	Player2* player2 = nullptr;
};

