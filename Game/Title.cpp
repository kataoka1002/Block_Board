#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"

Title::Title()
{
	s_title.Init("Assets/modelData/title.DDS", 1920.0f, 1080.0f);

	s_usublack.Init("Assets/modelData/usublack.DDS", 1920.0f, 1080.0f);

	s_setumei.Init("Assets/modelData/sousabo-do.DDS", 1920.0f, 1080.0f);
	s_setumei.SetScale({ 0.9f,0.9f,1.0f });
	s_setumei.Update();

	s_asobikata.Init("Assets/modelData/asobikata.DDS", 1920.0f, 1080.0f);
	s_asobikata.SetScale({ 0.9f,0.9f,1.0f });
	s_asobikata.Update();

	s_yazirusi.Init("Assets/modelData/yazirusiR.DDS", 1920.0f, 1080.0f);
	s_yazirusi.SetScale({ 0.08f, 0.08, 1.0f });

	s_padmode.Init("Assets/modelData/PadMode.DDS", 1000.0f, 1000.0f);
	s_padmode.SetScale({ 0.3f, 0.3, 1.0f });
	s_padmode.SetPosition({ 330.0f,-150.0f,0.0f });
	s_padmode.Update();

	//���ʉ��B
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/piko.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/piko_kettei.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/piko_modoru.wav");
	g_soundEngine->ResistWaveFileBank(19, "Assets/sound/BGM/taitoru.wav");

	soundSource = NewGO<SoundSource>(0, "soundSource");
	soundSource->Init(19);
	soundSource->SetVolume(0.5f);
	//���ʉ��̓��[�v�Đ��Ȃ̂�true�B
	soundSource->Play(true);

	/*s_yazirotL.Init("Assets/modelData/yazikaitenL.DDS", 1920.0f, 1080.0f);
	s_yazirotL.SetScale({ 0.07f, 0.1, 1.0f });
	
	s_yazirotR.Init("Assets/modelData/yazikaitenR.DDS", 1920.0f, 1080.0f);
	s_yazirotR.SetScale({ 0.07f, 0.1, 1.0f });
	
	s_yazirotU.Init("Assets/modelData/yazikaitenUP.DDS", 1920.0f, 1080.0f);
	s_yazirotU.SetScale({ 0.07f, 0.1, 1.0f });
	
	s_yazirotD.Init("Assets/modelData/yazikaitenDown.DDS", 1920.0f, 1080.0f);
	s_yazirotD.SetScale({ 0.07f, 0.1, 1.0f });*/
}

Title::~Title()
{
	DeleteGO(soundSource);
}

bool Title::Start()
{
	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();

	return true;
}

void Title::Update()
{
	//�I���̏���
	if (selectState == 1)
	{
		yaziposi.y = -172;
		
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//���ʉ����Đ�
			SE(2);

			//���̃T�C�Y�Əꏊ��ς���
			yaziposi.x = 190;
			yaziposi.y = -105;
			s_yazirusi.SetScale({ 0.05f, 0.05f, 1.0f });
			PadState = 0;
			selectState = 6;
		}

		//���{�^���Ŗ��ړ�
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			//��󂪉��Ɉړ�
			selectState = 2;
			//���ʉ����Đ�
			SE(1);
		}

	}
	else if (selectState == 2)
	{
		yaziposi.y = -272;

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//������ʂ̕\��
			selectState = 3;
			//���ʉ����Đ�
			SE(2);
		}

		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			//��󂪏�Ɉړ�
			selectState = 1;

			//���ʉ����Đ�
			SE(1);
		}
		else if (g_pad[0]->IsTrigger(enButtonDown))
		{
			//��󂪉��Ɉړ�
			selectState = 4;

			//���ʉ����Đ�
			SE(1);
		}
	}
	else if (selectState == 3)
	{
		//YaziRot();

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//�^�C�g���ɖ߂�
			selectState = 2;
			//���ʉ����Đ�
			SE(3);
		}
	}
	else if (selectState == 4)
	{
		yaziposi.y = -378;

		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			//��󂪏�Ɉړ�
			selectState = 2;

			//���ʉ����Đ�
			SE(1);
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//������ʂ̕\��
			selectState = 5;
			//���ʉ����Đ�
			SE(2);
		}
	}
	else if (selectState == 5)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//�^�C�g���ɖ߂�
			selectState = 4;
			//���ʉ����Đ�
			SE(3);
		}
	}
	else if (selectState == 6)
	{
		if (PadState == 0)
		{
			if (m_isWaitFadeout) {//�t�F�[�h�A�E�g���Ȃ炱����
				if (m_fade->IsFade() == false) {
					//�t�F�[�h�A�E�g���I�������game��NewGO����B
					Game* game = NewGO<Game>(0, "game");
					game->PAD_MODE = 0;
					DeleteGO(this);
				}
			}
			else //�t�F�[�h�A�E�g������Ȃ��Ȃ炱����
			{
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//�R���g���[���[1�ŗV��
					m_isWaitFadeout = true;//�t�F�[�h�A�E�g�����ǂ����𔻒f����t���O��true�ɂ���B
					m_fade->StartFadeOut();//�t�F�[�h�A�E�g�J�n(���[�h���̉�ʂ��������\��)

					//���ʉ����Đ�
					SE(2);
				}

				if (g_pad[0]->IsTrigger(enButtonB))
				{
					yaziposi.x = -150.0f;
					yaziposi.y = -172;
					s_yazirusi.SetScale({ 0.08f, 0.08, 1.0f });
					selectState = 1;

					//���ʉ����Đ�
					SE(3);
				}

				if (g_pad[0]->IsTrigger(enButtonDown))
				{
					//�������Ɉړ�������
					yaziposi.y = -214;
					PadState = 1;

					//���ʉ����Đ�
					SE(1);
				}
			}
		}
		else if (PadState == 1)
		{
			if (m_isWaitFadeout) {//�t�F�[�h�A�E�g���Ȃ炱����
				if (m_fade->IsFade() == false) {
					//�t�F�[�h�A�E�g���I�������game��NewGO����B
					Game* game = NewGO<Game>(0, "game");
					game->PAD_MODE = 1;
					DeleteGO(this);
				}
			}
			else//�t�F�[�h�A�E�g������Ȃ��Ȃ炱����
			{
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//�R���g���[���[2�ŗV��
					m_isWaitFadeout = true;//�t�F�[�h�A�E�g�����ǂ����𔻒f����t���O��true�ɂ���B
					m_fade->StartFadeOut();//�t�F�[�h�A�E�g�J�n(���[�h���̉�ʂ��������\��)

					//���ʉ����Đ�
					SE(2);
				}

				if (g_pad[0]->IsTrigger(enButtonB))
				{
					yaziposi.x = -150.0f;
					yaziposi.y = -172;
					s_yazirusi.SetScale({ 0.08f, 0.08, 1.0f });
					selectState = 1;

					//���ʉ����Đ�
					SE(3);
				}

				if (g_pad[0]->IsTrigger(enButtonUp))
				{
					//������Ɉړ�������
					yaziposi.y = -105;
					PadState = 0;

					//���ʉ����Đ�
					SE(1);
				}
			}
		}
		YaziMove();
	}
	
	if (selectState != 6)
	{
		YaziMove();
	}
}

void Title::YaziMove()
{
	if (selectState != 6)
	{
		//���̓����̏���
		s_yazirusi.SetPosition(yaziposi);
		if (yazimove == 1)
		{
			//�E�Ɉړ�
			yaziposi.x += 0.4;
			if (yaziposi.x > -150)
			{
				yazimove = 2;
			}
		}
		else if (yazimove == 2)
		{
			//���Ɉړ�
			yaziposi.x -= 0.4;
			if (yaziposi.x < -165)
			{
				yazimove = 1;
			}
		}

		s_yazirusi.Update();
	}

	if (selectState == 6)
	{
		//���̓����̏���
		s_yazirusi.SetPosition(yaziposi);
		if (yazimove == 1)
		{
			//�E�Ɉړ�
			yaziposi.x += 0.3;
			if (yaziposi.x > 190)
			{
				yazimove = 2;
			}
		}
		else if (yazimove == 2)
		{
			//���Ɉړ�
			yaziposi.x -= 0.3;
			if (yaziposi.x < 180)
			{
				yazimove = 1;
			}
		}

		s_yazirusi.Update();
	}
}

void Title::SE(int bango)
{
	//���ʉ���炷�B
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
	soundSource->Play(false);
}

//void Title::YaziRot()
//{
//	//�����|�W
//	s_yazirotL.SetPosition({ L,318.0f,0.0f });//�E590��-585
//	s_yazirotL.Update();
//	s_yazirotR.SetPosition({ R,-330.0f,0.0f });//�E590��-585
//	s_yazirotR.Update();
//	s_yazirotU.SetPosition({ 645.0f,U,0.0f });//��-290��280
//	s_yazirotU.Update();
//	s_yazirotD.SetPosition({ -638.0f,D,0.0f });//��-290��280
//	s_yazirotD.Update();
//
//	//���̓����̏���
//	if (yazirot == 1)
//	{
//		L -= 30.0;
//		R += 30.0;
//		if (L <= -585)
//		{
//			//�����|�W�ɖ߂�
//			L = 590;
//			R = -585;
//			yazirot = 2;
//		}
//	}
//	else if (yazirot == 2)
//	{
//		U += 30.0;
//		D -= 30.0;
//		if (U >= 280)
//		{
//			//�����|�W�ɖ߂�
//			U = -290;
//			D = 280;
//			yazirot = 1;
//		}
//	}
//}

void Title::Render(RenderContext& rc)
{
	s_title.Draw(rc);
	s_yazirusi.Draw(rc);
	//�{�^���̐�����\��
	if (selectState == 3)
	{
		s_usublack.Draw(rc);
		s_setumei.Draw(rc);

		/*if (yazirot == 1)
		{
			s_yazirotL.Draw(rc);
			s_yazirotR.Draw(rc);
		}
		else if (yazirot == 2)
		{
			s_yazirotU.Draw(rc);
			s_yazirotD.Draw(rc);
		}*/
	}

	//�V�ѕ���\��
	if (selectState == 5)
	{
		s_usublack.Draw(rc);
		s_asobikata.Draw(rc);
	}

	if (selectState == 6)
	{
		s_padmode.Draw(rc);
	}
}