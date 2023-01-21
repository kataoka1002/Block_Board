#pragma once
class Junban;
class Tate;
class Tatekanri;
class Game;
class Title;

class Player2 : public IGameObject
{
public:
	Player2();
	~Player2();
	void Render(RenderContext& rc);	//•`‰æˆ—B
	void Update();
	void Move();
	void Moving();
	void Rotation();
	void Attack();
	void SE(int bango,float volume=1.0f);
	void AsiotoSE(int bango);
	void StopAsioto() {
		if (foot_soundSource != nullptr) {
			foot_soundSource->Stop();
		}
	}

	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Walk,
		enAnimClip_Jump,
		enAnimClip_Drop,
		enAnimClip_Dansu,
		enAnimClip_Num,
	};
	AnimationClip animationClips[enAnimClip_Num];

	SpriteRender spriteRender;
	SpriteRender whitegazou;
	SpriteRender P2WIN;
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_targetPos;
	Vector3 m_move;
	Quaternion rotation;
	int PlayerState = 0;
	int sentakuState = 0;
	int tatearu = 0;
	int tatenokori2 = 15;
	int Life2 = 5;
	int nikaiwalk = 0;
	int tuzu2 = 0;
	int houkou = 0;
	int bariaefe = 0;
	float toumeido = 0.0f;
	int syaki = 0;
	int PAD_MODE = 0;

	//ŽžŠÔŒn
	float GameTimer = 5.0f;
	int TimeCount = 0;
	float GetGameTimer() {
		return GameTimer;
	}
	void AddGameTimer(float addtime) {
		GameTimer += addtime;
	}

	//‰Ô‰Î‚ÌŽžŠÔŒn
	float GameTimer2 = 2.0f;
	int TimeCount2 = 0;
	float GetGameTimer2() {
		return GameTimer2;
	}
	void AddGameTimer2(float addtime2) {
		GameTimer2 += addtime2;
	}

	Junban* junban = nullptr;
	Tate* tate = nullptr;
	Tatekanri* tatekanri = nullptr;
	Game* game = nullptr;
	Title* title = nullptr;
	EffectEmitter* effectEmitter = nullptr;
	EffectEmitter* effectEmitter0 = nullptr;
	EffectEmitter* effectEmitter1 = nullptr;
	SoundSource* foot_soundSource = nullptr;
};

