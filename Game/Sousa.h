#pragma once
class Player;
class Player2;
class Junban;

class Sousa:public IGameObject
{
public:
	Sousa();
	~Sousa();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender A_botan;
	SpriteRender X_botan;
	SpriteRender Y_botan;
	SpriteRender R2_botan;
	SpriteRender L2_botan;
	SpriteRender Jyu_botan;
	SpriteRender R1L1_botan;
	SpriteRender huti_pinku;
	SpriteRender huti_ki;
	SpriteRender huti_ao;
	SpriteRender Title_modoru;
	SpriteRender B_botan;

	Player* player = nullptr;
	Player2* player2 = nullptr;
	Junban* junban = nullptr;
};

