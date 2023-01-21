#pragma once
class Junban;
class Tate; 
class Player2;
class Tatekanri;
class Game;
class Title;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Render(RenderContext& rc);	//•`‰æˆ—B
	void Update();
	void Move();
	void Moving();
	void Rotation();
	void Attack();
	void SE(int bango, float volume = 1.0f);
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
		enAnimClip_Attack,
		enAnimClip_Jumatt,
		enAnimClip_Dansu,
		enAnimClip_Num,
	};
	AnimationClip animationClips[enAnimClip_Num];
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_targetPos;
	Vector3 m_move;
	Quaternion rotation;

	SpriteRender spriteRender;
	SpriteRender whitegazou;
	SpriteRender P1WIN;
	
	int PlayerState = 0;
	int sentakuState = 0;	//‚P‚È‚çˆÚ“®A2‚È‚ç‚
	int tatearu = 0;
	int tatenokori = 15;
	int Life1 = 5;
	int nikaiaruki = 0;
	int houkou = 0;
	int tuzu = 0;
	int bariaefe = 0;
	float toumeido = 0.0f;

	int syaki = 0;

	//ŠÔŒn
	float GameTimer = 5.0f;
	int TimeCount = 0;
	float GetGameTimer() {
		return GameTimer;
	}
	void AddGameTimer(float addtime) {
		GameTimer += addtime;
	}

	//‰Ô‰Î‚ÌŠÔŒn
	float GameTimer2 = 2.0f;
	int TimeCount2 = 0;
	float GetGameTimer2() {
		return GameTimer2;
	}
	void AddGameTimer2(float addtime2) {
		GameTimer2 += addtime2;
	}
	
	Game* game = nullptr;
	Junban* junban = nullptr;
	Tate* tate = nullptr;
	Player2* player2 = nullptr;
	Tatekanri* tatekanri = nullptr;
	Title* title = nullptr;
	EffectEmitter* effectEmitter = nullptr;
	EffectEmitter* effectEmitter0 = nullptr;
	EffectEmitter* effectEmitter1 = nullptr;
	SoundSource* foot_soundSource = nullptr;
};

