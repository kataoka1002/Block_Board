#pragma once

class Junban : public IGameObject
{
public:
	Junban();
	~Junban();
	void Render(RenderContext& rc);
	void Update();
	
	int KoutaiState = 0;
	//0�͏����l�A�P�͂PP����A�Q�͂QP����A�R�͐ԐF�̃`�F���W�A�S�͐F�̃`�F���W
	
	//�L�k��
	float nobiR = 0.0;
	float nobiB = 0.0;
	int nobiStateR = 0;
	int nobiStateB = 0;

	//���Ԍn
	float GameTimer = 0.7f;
	int TimeCount = 0;
	float GetGameTimer() {
		return GameTimer;
	}
	void AddGameTimer(float addtime) {
		GameTimer += addtime;
	}

	//���̗v�f
	int mai = 0;
	int tateposi[30][3] = { 0,0 };	//tateposi[?][0]��x���W�ŁAtateposi[?][1]��z���W�Atateposi[?][2]��y���W(?�͏��̃i���o�[)
	Vector2 m_pivotR = { 1.0f, 0.5f };
	Vector2 m_pivotB = { 0.0f, 0.5f };

	SpriteRender spred;
	SpriteRender spblue;
	SpriteRender spblack;
	
};

