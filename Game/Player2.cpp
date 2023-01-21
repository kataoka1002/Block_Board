#include "stdafx.h"
#include "Player2.h"
#include "Junban.h"
#include "Tate.h"
#include "Tatekanri.h"
#include "Game.h"
#include "Title.h"
#include "Syoumetu.h"

Player2::Player2()
{
	animationClips[enAnimClip_Idle].Load("Assets/animData/ziziiData/ziziitaiki.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);
	animationClips[enAnimClip_Walk].Load("Assets/animData/ziziiData/ziziiaruki.tka");
	animationClips[enAnimClip_Walk].SetLoopFlag(true);
	animationClips[enAnimClip_Jump].Load("Assets/animData/ziziiData/ziziiattack.tka");
	animationClips[enAnimClip_Jump].SetLoopFlag(true);
	animationClips[enAnimClip_Drop].Load("Assets/animData/ziziiData/ziziidrop.tka");
	animationClips[enAnimClip_Drop].SetLoopFlag(true);
	animationClips[enAnimClip_Dansu].Load("Assets/animData/ziziiData/ziziidansu.tka");
	animationClips[enAnimClip_Dansu].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/player2/player2zizii.tkm", animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(0.55f, 0.55f, 0.55f);

	whitegazou.Init("Assets/modelData/white.DDS", 1920.0f, 1080.0f);

	P2WIN.Init("Assets/modelData/P2WIN.DDS", 1920.0f, 1080.0f);
	P2WIN.SetScale({ 0.65f,0.65f,1.0f });
	P2WIN.SetPosition({ 0.0f,330.0f,0.0f });
	P2WIN.Update();

	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});

	//���ʉ��B
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/yawa_kettei.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/kyan.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/ikare-za-.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/asioto.wav");
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/baria.wav");

	

	junban = FindGO<Junban>("junban");
	tate = FindGO<Tate>("tate");
}

Player2::~Player2()
{
	DeleteGO(effectEmitter);
}

void Player2::Update()
{
	//tatekanri��NewGO���ꂽ�珈������
	if (tuzu2 == 1)
	{
		tatekanri = FindGO<Tatekanri>("tatekanri");
		tuzu2 = 2;
	}


	if (PlayerState == 0)
	{
		m_modelRender.PlayAnimation(enAnimClip_Idle,0.1f);	//�����A�j���[�V�����̍Đ�
	}
	if (PlayerState >= 1 && PlayerState <= 4)
	{
		m_modelRender.PlayAnimation(enAnimClip_Walk,0.1f);	//�����A�j���[�V�����̍Đ�
	}
	if (PlayerState == 5)
	{
		m_modelRender.PlayAnimation(enAnimClip_Jump,0.1f);	//�U���A�j���[�V�����̍Đ�
	}
	if (PlayerState == 9)
	{
		GameTimer -= g_gameTime->GetFrameDeltaTime();	//�J�E���g�������Ă���

		//�z���C�g�A�E�g����
		whitegazou.SetMulColor({ 1.0f,1.0f,1.0f,toumeido });
		toumeido += 0.005;
		if (toumeido >= 1.0)
		{
			toumeido = 1.0;
		}
		
		if (GameTimer <= 0)
		{
			//���Ԃ��o�߂���ƃA�j���[�V�����̍Đ�
			m_position.x = -100;
			m_position.y = 15;
			m_modelRender.SetAnimationSpeed(1);
		}
	}
	if (PlayerState == 10)
	{
		m_modelRender.PlayAnimation(enAnimClip_Drop,0.1f);	//�����A�j���[�V�����̍Đ�

		for (int i = 0; i < 30; i++)
		{
			tatekanri->tate[i]->Gameend = true;
		}
	}
	if (PlayerState == 11)
	{
		m_modelRender.PlayAnimation(enAnimClip_Dansu,0.1f);	//���U���g�A�j���[�V�����̍Đ�

		//�^�C�}�[�̃J�E���g�����炷�B
		GameTimer2 -= g_gameTime->GetFrameDeltaTime();

		if (GameTimer2 <= 0)
		{
			//�ԉ΂̃G�t�F�N�g���Đ�
			Syoumetu* hanabi1 = NewGO<Syoumetu>(0, "syoumetu");
			hanabi1->PlayEffect_Hanabi({ m_position.x + 50.0f,m_position.y + 40.0f,m_position.z + 80.0f });

			Syoumetu* hanabi2 = NewGO<Syoumetu>(0, "syoumetu");
			hanabi2->PlayEffect_Hanabi({ m_position.x + 50.0f,m_position.y + 40.0f,m_position.z - 80.0f });

			SE(20);

			GameTimer2 = 2.0;
		}

		//A�{�^���������ă^�C�g���ɖ߂�
		if (g_pad[PAD_MODE]->IsTrigger(enButtonA))
		{
			NewGO<Title>(0, "title");
			DeleteGO(game);
		}
	}

	//�V���L�[���͂P��̂ݍĐ�
	if (nikaiwalk == 4 && syaki == 0)
	{
		SE(18);
		syaki++;
	}

	Move();
	Moving();
	Rotation();

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(rotation);
	m_modelRender.Update();
}

void Player2::SE(int bango,float volume)
{
	//���ʉ���炷�B
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	soundSource->SetVolume(volume);
	//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
	soundSource->Play(false);
}

void Player2::AsiotoSE(int bango)
{
	if (foot_soundSource != nullptr) {
		DeleteGO(foot_soundSource);
	}

	//���ʉ���炷�B
	foot_soundSource = NewGO<SoundSource>(0);
	foot_soundSource->Init(bango);
	foot_soundSource->SetVolume(3.5f);
	//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
	foot_soundSource->Play(false);
}

void Player2::Move()
{
	if (PlayerState == 1) {
		return;
	}
	if (PlayerState == 2) {
		return;
	}
	if (PlayerState == 3) {
		return;
	}
	if (PlayerState == 4) {
		return;
	}
	if (PlayerState == 5){
		return;
	}
	if (PlayerState == 9) {
		return;
	}
	if (PlayerState == 10) {
		return;
	}
	if (PlayerState == 11) {
		return;
	}
	if (PlayerState == 12) {
		return;
	}


	if (junban->KoutaiState == 2)
	{
		//Y�������Ĉړ���I��
		if (g_pad[PAD_MODE]->IsTrigger(enButtonY) && tatearu == 0 && sentakuState == 0)
		{
			sentakuState = 1;			
			SE(7);
		}
		//X�������ď���I��
		else if (g_pad[PAD_MODE]->IsTrigger(enButtonX) && tatenokori2 > 0 && tatearu == 0 && sentakuState == 0)
		{
			sentakuState = 2;	
			SE(7);
		}
		//L2�������ď����󂷑I��
		else if (g_pad[PAD_MODE]->IsTrigger(enButtonLB2) && sentakuState == 0)
		{
			sentakuState = 3;
			SE(7);
		}

		//1�̈ړ���I�������ꍇ
		if (sentakuState == 1)
		{
			if (g_pad[PAD_MODE]->IsTrigger(enButtonRight))					//�E�{�^���������ꂽ��
			{
				for (int i = 0; i < 40; i++) //����1���ڂ��珇�Ƀ`�F�b�N
				{
					if (m_position.x == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] -10)
					{
						SE(22);
						return;		//�O�ɏ����u���Ă���Ɠ����Ȃ�
					}
				}

				//��������͏����O�ɖ����������̏���
				if (m_position.z == 80)
				{
					return;
				}
				else if (m_position.z < 80)
				{
					PlayerState = 1;
					Vector3 targetPos = m_position;		//�ڕW�n�_�̐ݒ�
					targetPos.z += 20.0f;				//20.0f�悪�ڕW
					m_targetPos = targetPos;

					//�ڕW�n�_���獡�̏ꏊ��������80�Ŋ�������������
					m_move = (m_targetPos - m_position) / 80.0f;

					AsiotoSE(14);
				}
			}

			if (g_pad[PAD_MODE]->IsTrigger(enButtonLeft))					//���{�^���������ꂽ��
			{
				for (int i = 0; i < 40; i++)//����1���ڂ��珇�Ƀ`�F�b�N
				{
					if (m_position.x == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] + 10)
					{
						SE(22);
						return;		//�O�ɏ����u���Ă���Ɠ����Ȃ�
					}
				}

				//��������͑O�ɏ����Ȃ��������̏���
				if (m_position.z == -80)
				{
					return;
				}
				else if (m_position.z > -80)
				{
					PlayerState = 2;
					Vector3 targetPos = m_position;		//�ڕW�n�_�̐ݒ�
					targetPos.z -= 20.0f;				//20.0f�悪�ڕW
					m_targetPos = targetPos;

					//�ڕW�n�_���獡�̏ꏊ��������80�Ŋ�������������
					m_move = (m_targetPos - m_position) / 80.0f;

					AsiotoSE(14);
				}
			}

			if (g_pad[PAD_MODE]->IsTrigger(enButtonUp))					//��{�^���������ꂽ��
			{
				for (int i = 0; i < 40; i++)//����1���ڂ��珇�Ƀ`�F�b�N
				{
					if (m_position.x == junban->tateposi[i][0] +10 && m_position.z == junban->tateposi[i][1])
					{
						SE(22);
						return;		//�O�ɏ����u���Ă���Ɠ����Ȃ�
					}
				}

				//��������͑O�ɏ����Ȃ��������̏���
				if (m_position.x == -80)
				{
					return;
				}
				else if (m_position.x > -80)
				{
					PlayerState = 3;
					Vector3 targetPos = m_position;		//�ڕW�n�_�̐ݒ�
					targetPos.x -= 20.0f;				//20.0f�悪�ڕW
					m_targetPos = targetPos;

					//�ڕW�n�_���獡�̏ꏊ��������80�Ŋ�������������
					m_move = (m_targetPos - m_position) / 80.0f;

					AsiotoSE(14);
				}
			}

			if (g_pad[PAD_MODE]->IsTrigger(enButtonDown))					//���{�^���������ꂽ��
			{
				for (int i = 0; i < 40; i++)//����1���ڂ��珇�Ƀ`�F�b�N
				{
					if (m_position.x == junban->tateposi[i][0] - 10 && m_position.z == junban->tateposi[i][1])
					{
						SE(22);
						return;		//�O�ɏ����u���Ă���Ɠ����Ȃ�
					}
				}

				//��������͑O�ɏ����Ȃ��������̏���
				if (m_position.x == 80)
				{
					return;
				}
				else if (m_position.x < 80)
				{
					PlayerState = 4;
					Vector3 targetPos = m_position;		//�ڕW�n�_�̐ݒ�
					targetPos.x += 20.0f;				//20.0f�悪�ڕW
					m_targetPos = targetPos;

					//�ڕW�n�_���獡�̏ꏊ��������80�Ŋ�������������
					m_move = (m_targetPos - m_position) / 50.0f;

					AsiotoSE(14);
				}
			}

			//R2�������ƑI����ʂɖ߂��
			if (g_pad[PAD_MODE]->IsTrigger(enButtonRB2) && nikaiwalk != -1)
			{
				sentakuState = 0;
				SE(8);
			}

		}

		//�Q�̏���I�������ꍇ
		if (sentakuState == 2)
		{
			if (tatearu == 0)
			{
				tatekanri->tatesaku = 1;

				tatearu = 1;
			}

		}

		//�R�̍U����I�������Ƃ�
		if (sentakuState == 3)
		{
			//�����̌���
			if (g_pad[PAD_MODE]->IsTrigger(enButtonUp))
			{
				rotation.SetRotationDegY(270.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 1;
			}
			else if (g_pad[PAD_MODE]->IsTrigger(enButtonDown))
			{
				rotation.SetRotationDegY(90.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 2;
			}
			else if (g_pad[PAD_MODE]->IsTrigger(enButtonLeft))
			{
				rotation.SetRotationDegY(180.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 3;
			}
			else if (g_pad[PAD_MODE]->IsTrigger(enButtonRight))
			{
				rotation.SetRotationDegY(0.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 4;
			}

			//A�{�^���������Č���
			if (g_pad[PAD_MODE]->IsTrigger(enButtonA))
			{
				Attack();
			}

			//R2�������ƑI����ʂɖ߂��
			if (g_pad[PAD_MODE]->IsTrigger(enButtonRB2))
			{
				sentakuState = 0;
			}
		}

		if (sentakuState == 4)
		{
			//�����ł��Ȃ�
		}
	}
}

void Player2::Moving()
{
	if (PlayerState == 0)
	{
		return;
	}
	if (PlayerState == 5) 
	{
		return;
	}
	if (PlayerState == 9)
	{
		return;
	}
	if (PlayerState == 10)
	{
		return;
	}
	if (PlayerState == 11)
	{
		return;
	}

	m_position += m_move;		//���炩�Ɉړ�

	Vector3 diff = m_targetPos - m_position;	//�ڕW�ꏊ�܂ł̋���
	float len = diff.Length();
	if (len < 0.2f && nikaiwalk < 4)		//�ڕW�ꏊ�܂ł̋������߂Â��Ă�����X�e�[�g���O�ɖ߂�
	{
		m_position = m_targetPos;
		StopAsioto();

		//�G�̐w�n�ɓ��荞�߂���
		if (m_position.x == -80)
		{
			PlayerState = 10;	//����
			SE(15);
			return;
		}
		
		//�Q�^�[���ڂ��炵���󂹂Ȃ�
		if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
		{
			tatekanri->tate[junban->mai - 1]->kowasu = true;

			//�摜�̍����ւ�
			tatekanri->tate[junban->mai - 1]->Harikae();
		}
		PlayerState = 0;
		nikaiwalk++;
		sentakuState = 0;
		bariaefe = 0;
		junban->nobiStateB = 1;
		junban->KoutaiState = 4;
	}
	else if (len < 0.2f && nikaiwalk >= 4)		//�ڕW�ꏊ�܂ł̋������߂Â��Ă�����X�e�[�g���O�ɖ߂�
	{											//�����̂��Q��ڂ̎�
		m_position = m_targetPos;
		StopAsioto();

		//�G�̐w�n�ɓ��荞�߂���
		if (m_position.x == -80)
		{
			PlayerState = 10;	//����
			SE(15);
			return;
		}

		PlayerState = 0;
		nikaiwalk = -1;
		return;
	}
}

void Player2::Attack()
{
	if (houkou == 1)
	{
		//�O�ɏ����u���Ă��邩�`�F�b�N
		for (int i = 0; i < 30; i++)
		{
			//�O�ɏ����u���Ă���Ɖ󂹂�B
			if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;		//�����ł��Ȃ�����
				PlayerState = 5;		//�A�j���[�V�����̍Đ�
				SE(12);
			}
			else if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//���͒u���Ă��邪�󂹂Ȃ��ꍇ
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x - 10.0f,m_position.y + 25.0f,m_position.z });
				effectEmitter1->Play();
				SE(16, 1.5f);
				bariaefe = 1;//�o���A�G�t�F�N�g��1�񂵂��o�Ȃ�
			}
			
		}
		return;
	}
	else if (houkou == 2)
	{
		for (int i = 0; i < 30; i++)
		{
			//�O�ɏ����u���Ă���Ɖ󂹂�B
			if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;		//�����ł��Ȃ�����
				PlayerState = 5;		//�A�j���[�V�����̍Đ�
				SE(12);
			}
			else if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//���͒u���Ă��邪�󂹂Ȃ��ꍇ
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x + 10.0f,m_position.y + 25.0f,m_position.z });
				effectEmitter1->Play();
				SE(16, 1.5f);
				bariaefe = 1;//�o���A�G�t�F�N�g��1�񂵂��o�Ȃ�
			}
			
		}
		return;
	}
	else if (houkou == 3)
	{
		for (int i = 0; i < 30; i++)
		{
			//�O�ɏ����u���Ă���Ɖ󂹂�B
			if (m_position.x == junban->tateposi[i][0] && m_position.z - 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;		//�����ł��Ȃ�����
				PlayerState = 5;		//�A�j���[�V�����̍Đ�
				SE(12);
			}
			else if (m_position.x == junban->tateposi[i][0] && m_position.z - 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//���͒u���Ă��邪�󂹂Ȃ��ꍇ
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x,m_position.y + 25.0f,m_position.z - 10 });
				effectEmitter1->Play();
				SE(16, 1.5f);
				bariaefe = 1;//�o���A�G�t�F�N�g��1�񂵂��o�Ȃ�
			}
			
		}
		return;
	}
	else if (houkou == 4)
	{
		for (int i = 0; i < 30; i++)
		{
			//�O�ɏ����u���Ă���Ɖ󂹂�B
			if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;		//�����ł��Ȃ�����
				PlayerState = 5;		//�A�j���[�V�����̍Đ�
				SE(12);
			}
			else if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//���͒u���Ă��邪�󂹂Ȃ��ꍇ
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x,m_position.y + 25.0f,m_position.z + 10 });
				effectEmitter1->Play();
				SE(16, 1.5f);
				bariaefe = 1;//�o���A�G�t�F�N�g��1�񂵂��o�Ȃ�
			}
			
		}
		return;
	}
}

void Player2::Rotation()
{
	if (PlayerState == 5)
	{
		return;
	}
	else if (PlayerState != 0 && PlayerState != 12)
	{
		//�L�����N�^�[�̕�����ς���B
		rotation.SetRotationYFromDirectionXZ(m_move);

		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(rotation);
	}
}

void Player2::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���uattack_start�v�̎�
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		if (houkou == 1)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enIkakougeki);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x - 9.0f,m_position.y,m_position.z });
			effectEmitter0->Play();
		}
		else if (houkou == 2)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enIkakougeki);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x + 9.0f,m_position.y,m_position.z });
			effectEmitter0->Play();
		}
		else if (houkou == 3)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enIkakougeki);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x,m_position.y,m_position.z - 9.0f });
			effectEmitter0->Play();
		}
		else if (houkou == 4)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enIkakougeki);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x,m_position.y,m_position.z + 9.0f });
			effectEmitter0->Play();
		}
	}
	//�L�[�̖��O���uattack_end�v�̎�
	if (wcscmp(eventName, L"attack_end") == 0)
	{
		if (houkou == 1)
		{
			//�O�ɏ����u���Ă��邩�`�F�b�N
			for (int i = 0; i < 30; i++)
			{
				//�O�ɏ����u���Ă���Ɖ󂹂�B
				if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//���j��G�t�F�N�g�𗬂�
					DeleteGO(tatekanri->tate[i]);

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

						//�摜�̍����ւ�
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiwalk++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateB = 1;
					junban->KoutaiState = 4;
				}
			}
			return;
		}
		else if (houkou == 2)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//���j��G�t�F�N�g�𗬂�
					DeleteGO(tatekanri->tate[i]);//�O�ɏ����u���Ă���Ɖ󂹂�B

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

						//�摜�̍����ւ�
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiwalk++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateB = 1;
					junban->KoutaiState = 4;
				}
			}
			return;
		}
		else if (houkou == 3)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x == junban->tateposi[i][0] && m_position.z - 10 == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//���j��G�t�F�N�g�𗬂�
					DeleteGO(tatekanri->tate[i]);//�O�ɏ����u���Ă���Ɖ󂹂�B

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

						//�摜�̍����ւ�
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiwalk++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateB = 1;
					junban->KoutaiState = 4;
				}
			}
			return;
		}
		else if (houkou == 4)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//���j��G�t�F�N�g�𗬂�
					DeleteGO(tatekanri->tate[i]);//�O�ɏ����u���Ă���Ɖ󂹂�B

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

						//�摜�̍����ւ�
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiwalk++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateB = 1;
					junban->KoutaiState = 4;
				}
			}
			return;
		}
	}

	//�L�[�̖��O���udrop_start�v�̎�
	if (wcscmp(eventName, L"drop_start") == 0)
	{
		
	}

	//�L�[�̖��O���udrop_stop�v�̎�
	if (wcscmp(eventName, L"drop_stop") == 0)
	{
		//�q�b�g�X�g�b�v
		m_modelRender.SetAnimationSpeed(0);
		PlayerState = 9;
		SE(6);
	}

	//�L�[�̖��O���udrop_end�v�̎�
	if (wcscmp(eventName, L"drop_end") == 0)
	{
		//���U���g��ʂɐ؂�ւ�
		PlayerState = 11;

		//������̃G�t�F�N�g���Đ�
		effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(enKamihubuki);
		effectEmitter->SetScale({ 4.0f,4.0f,4.0f });
		effectEmitter->SetRotation(rotation);
		effectEmitter->SetPosition({ m_position.x + 5.0f,m_position.y + 10.0f,m_position.z });
		effectEmitter->Play();
	}
}

void Player2::Render(RenderContext& rc)
{
	//�`�悷��B
	m_modelRender.Draw(rc);

	if (PlayerState == 9)
	{
		whitegazou.Draw(rc);
	}
	else if (PlayerState == 11)
	{
		P2WIN.Draw(rc);
	}
}
