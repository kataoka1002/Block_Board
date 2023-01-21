#pragma once

class Junban : public IGameObject
{
public:
	Junban();
	~Junban();
	void Render(RenderContext& rc);
	void Update();
	
	int KoutaiState = 0;
	//0は初期値、１は１P操作、２は２P操作、３は赤色のチェンジ、４は青色のチェンジ
	
	//伸縮率
	float nobiR = 0.0;
	float nobiB = 0.0;
	int nobiStateR = 0;
	int nobiStateB = 0;

	//時間系
	float GameTimer = 0.7f;
	int TimeCount = 0;
	float GetGameTimer() {
		return GameTimer;
	}
	void AddGameTimer(float addtime) {
		GameTimer += addtime;
	}

	//盾の要素
	int mai = 0;
	int tateposi[30][3] = { 0,0 };	//tateposi[?][0]はx座標で、tateposi[?][1]はz座標、tateposi[?][2]はy座標(?は盾のナンバー)
	Vector2 m_pivotR = { 1.0f, 0.5f };
	Vector2 m_pivotB = { 0.0f, 0.5f };

	SpriteRender spred;
	SpriteRender spblue;
	SpriteRender spblack;
	
};

