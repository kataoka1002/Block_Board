#pragma once
#include "Level3DRender/LevelRender.h"

//エフェクトの配列
enum EnMahoustate {
	enKaminari,		//雷のエフェクト
	enBaria,		//バリアのエフェクト
	enIkakougeki,	//触手の攻撃エフェクト
	enSyoumetu,		//壁が消滅するエフェクト
	enSonic,		//突風のエフェクト
	enMgCircle,	    //マジックサークルエフェクト
	enKamihubuki,	//紙吹雪のエフェクト
	enHanabi,		//花火エフェクト
	enHarikae		//テクスチャの張替え時のエフェクト
};

class Stage;
class Player;
class Player2;
class Junban;
class GameCamera;
class Tate;
class Tatekanri;
class BattleStart;
class Gauge;
class Sousa;
class Fade;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Render(RenderContext& rc);
	bool Start();
	void UI_Update();
	void SE(int bango, float volume = 1.0f);
	
	int PAD_MODE = 0;

private:
	void InitSky();

	Stage* stage = nullptr;
	Player* player = nullptr;
	Player2* player2 = nullptr;
	Junban* junban = nullptr;
	GameCamera* gamecamera = nullptr;
	Tatekanri* tatekanri = nullptr;
	BattleStart* battlestart = nullptr;
	SkyCube* m_skyCube = nullptr;
	Gauge* gauge = nullptr;
	Sousa* sousa = nullptr;
	Fade* fade = nullptr;

	int Tatenokori = 0;
	int Tatenokori2 = 0;
	int gazoari = 0;
	int gazoari2 = 0;
	int jun = 1;
	int m_skyCubeType = enSkyCubeType_DayToon_4;
	//音関係
	int zi_tyaku = 0;
	int nezu_rakka = 0;
	int zi_rakka = 0;
	int bat_suta = 0;
	bool syouri = false;
	

	FontRender fontRender;
	FontRender fontRender2;

	//盾の残りの枠
	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	SpriteRender s_1p;
	SpriteRender s_2p;

	EffectEmitter* effectEmitter0 = nullptr;

	PointLight pointlight1;
	PointLight pointlight2;
	//SpotLight spotlight1;

	SoundSource* soundSource = nullptr;
	SoundSource* WinBGM = nullptr;
};

