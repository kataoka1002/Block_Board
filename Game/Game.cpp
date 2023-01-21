#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Player2.h"
#include "GameCamera.h"
#include "Junban.h"
#include "Tate.h"
#include "Tatekanri.h"
#include "BattleStart.h"
#include "Gauge.h"
#include "Kanri.h"
#include "Sousa.h"
#include "Fade.h"
#include "graphics/RenderingEngine.h"
#include "nature/SkyCube.h";

Game::Game()
{
	//�N���X�̍쐬
	junban = NewGO<Junban>(0, "junban");

	player = NewGO<Player>(1, "player");
	player->game = this;
	player->m_position = { -80.0f,150.0f,0.0f };
	player->PlayerState = 12;
	player->rotation.SetRotationDegY(90.0f);

	player2 = NewGO<Player2>(1, "player2");
	player2->game = this;
	player2->m_position = { 80.0f,150.0f,0.0f };
	player2->rotation.SetRotationDegY(270.0f);

	tatekanri = NewGO<Tatekanri>(0, "tatekanri");
	tatekanri->game = this;//�������FindGO���Ă�̂Ɠ���

	stage = NewGO<Stage>(0, "stage");

	battlestart = NewGO<BattleStart>(0, "battlestart");

	gamecamera = NewGO<GameCamera>(0, "camera");

	m_skyCube = NewGO<SkyCube>(0, "m_skyCube");
	InitSky();

	gauge = NewGO<Gauge>(0, "gauge");
	sousa = NewGO<Sousa>(0, "sousa");

	//���c��̃t�H���g�̏ꏊ
	fontRender.SetPosition(Vector3(-820.0f, 380.0f, 0.0f));
	fontRender2.SetPosition(Vector3(790.0f, 380.0f, 0.0f));

	/*pointlight1.Init();
	pointlight1.SetPosition({ 0.0f,150.0f,0.0f });
	pointlight1.SetColor({ 5.0f,5.0f,5.0f });
	pointlight1.SetRange(1000);

	pointlight2.Init();
	pointlight2.SetPosition({ 600.0f,150.0f,0.0f });
	pointlight2.SetColor({ 20.0f,20.0f,20.0f });
	pointlight2.SetRange(600);*/

	/*spotlight1.Init();
	spotlight1.SetPosition({ 0.0f,20.0f,0.0f });
	spotlight1.SetDirection(0.0f, -1.0f, 0.0f);
	spotlight1.SetColor({ 50.0f,0.0f,0.0f });
	spotlight1.SetRange(1000);*/

	//�v���C���[�̃e�L�X�g�̐ݒ�
	s_1p.Init("Assets/modelData/1P.DDS", 1000.0f, 1000.0f);
	s_1p.SetPosition({ 0.0f,450.0f,0.0f });
	s_1p.SetScale({ 0.35,0.35,1.0 });
	s_1p.Update();
	s_2p.Init("Assets/modelData/2P.DDS", 1000.0f, 1000.0f);
	s_2p.SetPosition({ 0.0f,450.0f,0.0f });
	s_2p.SetScale({ 0.35,0.35,1.0 });
	s_2p.Update();

	//���̉摜�쐬
	spriteRender.Init("Assets/modelData/tategazo.DDS", 1000.0f, 1000.0f);
	spriteRender.SetPosition({ -870.0f,350.0f,0.0f });
	spriteRender.SetScale({ 0.15,0.15,1.0 });
	spriteRender.Update();
	spriteRender2.Init("Assets/modelData/tategazo.DDS", 1000.0f, 1000.0f);
	spriteRender2.SetPosition({ 740.0f,350.0f,0.0f });
	spriteRender2.SetScale({ 0.15,0.15,1.0 });
	spriteRender2.Update();

	UI_Update();

	//BGM
	g_soundEngine->ResistWaveFileBank(17,"Assets/sound/BGM/SEISEN.wav");
	soundSource = NewGO<SoundSource>(0,"soundSource");
	soundSource->Init(17);
	soundSource->SetVolume(0.3f);
	//���ʉ��̓��[�v�Đ��Ȃ̂�true�B
	soundSource->Play(true);

	

	//���ʉ��ꗗ
	//0.��, 1.�s�R(���ړ�), 2.����, 3.�߂�, 4.���n, 5.������, 6.�o�g���X�^�[�g
	//7.�v���C���[�̌���, 8.�L�����Z��, 9.���ړ�, 10.����], 11.�G���U��, 12.���L�b�N, 13.�j��
	//14.����, 15.�W�����v, 16.�o���A, 17.���C��BGM, 18.�V���L�[��, 19.�^�C�g��, 20.�ԉ�, 21.����BGM
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(player2);
	DeleteGO(tatekanri);
	DeleteGO(junban);
	DeleteGO(stage);
	DeleteGO(battlestart);
	DeleteGO(gamecamera);
	DeleteGO(m_skyCube);
	DeleteGO(gauge);
	DeleteGO(sousa);
	DeleteGO(soundSource);
	DeleteGO(WinBGM);
}

bool Game::Start()
{
	//�G�t�F�N�g�̓ǂݍ���
	EffectEngine::GetInstance()->ResistEffect(enKaminari, u"Assets/efe/kaminari.efk");
	EffectEngine::GetInstance()->ResistEffect(enBaria, u"Assets/efe/baria.efk");
	EffectEngine::GetInstance()->ResistEffect(enIkakougeki, u"Assets/efe/ikakougeki.efk");
	EffectEngine::GetInstance()->ResistEffect(enSyoumetu, u"Assets/efe/hanebakudan.efk");
	EffectEngine::GetInstance()->ResistEffect(enSonic, u"Assets/efe/sonicboom.efk");
	EffectEngine::GetInstance()->ResistEffect(enMgCircle, u"Assets/efe/magiccircle.efk");
	EffectEngine::GetInstance()->ResistEffect(enKamihubuki, u"Assets/efe/kamihubuki.efk");
	EffectEngine::GetInstance()->ResistEffect(enHanabi, u"Assets/efe/hanabi.efk");
	EffectEngine::GetInstance()->ResistEffect(enHarikae, u"Assets/efe/harikae.efk");

	//FindGO�܂Ƃ�
	fade = FindGO<Fade>("fade");
	fade->StartFadeIn();

	//���ʉ��B
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/tyakuti.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/hyu-.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/battle_start.wav");
	g_soundEngine->ResistWaveFileBank(21, "Assets/sound/BGM/syouriBGM.wav");
	g_soundEngine->ResistWaveFileBank(22, "Assets/sound/bu-.wav");

	//pad�f�[�^�n��
	player2->PAD_MODE = PAD_MODE;

	return true;
}

void Game::Update()
{
	if (player->PlayerState == 11 || player2->PlayerState == 11)
	{
		if (soundSource->IsPlaying() == false) {
			return;
		}

		soundSource->Stop();
	}

	if (player->PlayerState == 11 || player2->PlayerState == 11)
	{
		if (soundSource->IsPlaying() == false && syouri == false)
		{
			//����BGM�𗬂�
			WinBGM = NewGO<SoundSource>(0, "WinBGM");
			WinBGM->Init(21);
			WinBGM->SetVolume(0.3f);
			//���ʉ��̓��[�v�Đ��Ȃ̂�true�B
			WinBGM->Play(true);

			syouri = true;
		}
	}

	if (player->PlayerState == 12)
	{
		//�ォ��~��Ă���
		player->m_position.y -= 1.0f;
		if (nezu_rakka == 0)
		{
			//���ʉ�
			SE(5, 0.7f);
			nezu_rakka = 1;
		}

		if (player->m_position.y <= 4.0f)
		{
			//���ʉ�
			SE(4);
			player->m_position.y = 4.0f;
			player->PlayerState = 0;
			
			//�l�Y�~���~�肫�����玟�ɖꂪ����Ă���
			player2->PlayerState = 12;
		}
	}
	if (player2->PlayerState == 12)
	{
		//�ォ��~��Ă���
		player2->m_position.y -= 1.0f;
		if (zi_rakka == 0)
		{
			//���ʉ�
			SE(5, 0.7f);
			zi_rakka = 1;
		}

		if (player2->m_position.y <= 4.5f)
		{
			if(zi_tyaku==0){
			//���ʉ�
			SE(4);
			zi_tyaku = 1;
			}

			player2->m_position.y = 4.5f;
			//�ꂪ���肫������o�g���X�^�[�g��\��
			battlestart->gazoset = true;
			if (bat_suta == 0) {
				SE(6);
				bat_suta = 1;
			}
		}
	}

	/*pointlight1.Update();
	pointlight2.Update();*/
	//spotlight1.Update();
}

void Game::InitSky()
{
	// ���݂̋��j���B
	DeleteGO(m_skyCube);
	m_skyCube = NewGO<SkyCube>(0, "skycube");

	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	// �����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.6f);
	
	// �f�B���N�V�������C�g�̐ݒ�B
	g_renderingEngine->SetDirectionLight(0, g_vec3Naname1, g_vec3One * 3);
	//g_renderingEngine->SetCascadeNearAreaRates(0.03f, 0.5f, 1.0f);

	//�g�[���}�b�v�̊�ɂȂ�V�[���̒��Ԃ̖��邳�ݒ�
	g_renderingEngine->SetSceneMiddleGray(0.4);
	//�g�[���}�b�v��؂�
	//g_renderingEngine->DisableTonemap();

}

void Game::UI_Update() 
{
	//���̎c�薇���̕\��
	Tatenokori = player->tatenokori;
	wchar_t count1[255];
	swprintf_s(count1, 255, L"X%d", Tatenokori);
	fontRender.SetText(count1);
	fontRender.SetScale(1.6f);
	fontRender.SetColor({ 0.0f,1.0f,1.0f ,1.0f });
	fontRender.SetShadowParam(true, 1.3f, Vector3{ 0.0f,0.0f,0.0f });

	Tatenokori2 = player2->tatenokori2;
	wchar_t count2[255];
	swprintf_s(count2, 255, L"X%d", Tatenokori2);
	fontRender2.SetText(count2);
	fontRender2.SetScale(1.6f);
	fontRender2.SetColor({ 1.0f,0.0f,0.5f ,1.0f });
	fontRender2.SetShadowParam(true, 1.3f, Vector3{ 0.0f,0.0f,0.0f });
}

void Game::SE(int bango,float volume)
{
	//���ʉ���炷�B
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	soundSource->SetVolume(volume);
	//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
	soundSource->Play(false);
}

void Game::Render(RenderContext& rc)
{
	//�o��V�[���ƃ��U���g��ʂł͕\�����Ȃ��B
	if (player->PlayerState != 11 && player2->PlayerState != 11 && player->PlayerState != 12 && player2->PlayerState != 12)
	{
		fontRender.Draw(rc);
		fontRender2.Draw(rc);
		spriteRender.Draw(rc);
		spriteRender2.Draw(rc);
		if (junban->KoutaiState == 1)
		{
			s_1p.Draw(rc);
		}
		if (junban->KoutaiState == 2)
		{
			s_2p.Draw(rc);
		}
	}
}