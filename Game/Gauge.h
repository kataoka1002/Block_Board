#pragma once
class Player;
class Player2;
class Gauge : public IGameObject
{
public:
	Gauge();
	~Gauge();
	void Update();
	void Render(RenderContext& rc);

	//ゲージの大きさ(zの大きさは固定)
	Vector3 scale1_1 = { 0.0f,0.0f,1.0f };
	Vector3 scale1_2 = { 0.0f,0.0f,1.0f };
	Vector3 scale1_3 = { 0.0f,0.0f,1.0f };
	Vector3 scale1_4 = { 0.0f,0.0f,1.0f };
	Vector3 scale2_1 = { 0.0f,0.0f,1.0f };
	Vector3 scale2_2 = { 0.0f,0.0f,1.0f };
	Vector3 scale2_3 = { 0.0f,0.0f,1.0f };
	Vector3 scale2_4 = { 0.0f,0.0f,1.0f };

	Vector3 wakuscale = { 0.5f,0.5f,1.0f };
	int saizu1 = 0, saizu2 = 0;

	//ゲージの中身
	SpriteRender gauge1_1;
	SpriteRender gauge1_2;
	SpriteRender gauge1_3;
	SpriteRender gauge1_4;
	SpriteRender gauge2_1;
	SpriteRender gauge2_2;
	SpriteRender gauge2_3;
	SpriteRender gauge2_4;
	//ゲージの枠
	SpriteRender gaugewaku1_1;
	SpriteRender gaugewaku1_2;
	SpriteRender gaugewaku1_3;
	SpriteRender gaugewaku1_4;
	SpriteRender gaugewaku2_1;
	SpriteRender gaugewaku2_2;
	SpriteRender gaugewaku2_3;
	SpriteRender gaugewaku2_4;

	Player* player = nullptr;
	Player2* player2 = nullptr;
};

