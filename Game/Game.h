#pragma once
#include "Level3DRender/LevelRender.h"

//�G�t�F�N�g�̔z��
enum EnMahoustate {
	enKaminari,		//���̃G�t�F�N�g
	enBaria,		//�o���A�̃G�t�F�N�g
	enIkakougeki,	//�G��̍U���G�t�F�N�g
	enSyoumetu,		//�ǂ����ł���G�t�F�N�g
	enSonic,		//�˕��̃G�t�F�N�g
	enMgCircle,	    //�}�W�b�N�T�[�N���G�t�F�N�g
	enKamihubuki,	//������̃G�t�F�N�g
	enHanabi,		//�ԉ΃G�t�F�N�g
	enHarikae		//�e�N�X�`���̒��ւ����̃G�t�F�N�g
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
	//���֌W
	int zi_tyaku = 0;
	int nezu_rakka = 0;
	int zi_rakka = 0;
	int bat_suta = 0;
	bool syouri = false;
	

	FontRender fontRender;
	FontRender fontRender2;

	//���̎c��̘g
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

