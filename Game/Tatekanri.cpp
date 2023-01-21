#include "stdafx.h"
#include "Tatekanri.h"
#include "Tate.h"
#include "Junban.h"
#include "Player.h"
#include "Player2.h"
#include "Game.h"

Tatekanri::Tatekanri()
{
	player = FindGO<Player>("player");
	player2 = FindGO<Player2>("player2");
	junban = FindGO<Junban>("junban");

	//���ʉ��B
	g_soundEngine->ResistWaveFileBank(0,"Assets/sound/kaminari.wav");
	
	for (int i = 0; i < 30; i++)
	{
		tate[i] = NewGO<Tate>(0, "tate");
		tate[i]->tatekanri = this;//���܂ꂽ�䂪�q�Ɏ�������������
		tate[i]->m_position = { 500.0f,500.0f,500.0f };
	}

	player->tuzu = 1;
	player2->tuzu2 = 1;
}

Tatekanri::~Tatekanri()
{
	DeleteGO(effectEmitter);
	for (int i = 0; i < 30; i++)
	{
		DeleteGO(tate[i]);
	}
}

void Tatekanri::Update()
{
	if (tatesaku == 1)
	{
		tate[junban->mai]->SetidouState(0);
		
		//�����X�e�[�W��Ɉړ�������
		tate[junban->mai]->m_position.x = -10.0f;
		tate[junban->mai]->m_position.y = 0.5f;
		tate[junban->mai]->m_position.z = 0.0f;

		tatesaku = 0;
	}

	//���̏ꏊ�����肵���Ƃ��̏���
	if (player->sentakuState == 2)
	{
		if (tate[junban->mai]->GetidouState() == 0)
		{
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				for (int i = 0; i < 30; i++)
				{
					if (tate[junban->mai]->m_position.x == junban->tateposi[i][0] && tate[junban->mai]->m_position.z == junban->tateposi[i][1])
					{
						//���ʉ���炷�B
						SoundSource* buu = NewGO<SoundSource>(0);
						buu->Init(22);
						buu->SetVolume(2.5f);
						//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
						buu->Play(false);
						return;		//�����ꏊ�ɏ����u���Ă���ƌ���ł��Ȃ��B
					}
				}

				//�ꏊ������Ă��Ȃ�������
				//���̃|�W�V�������o��������
				junban->tateposi[junban->mai][0] = tate[junban->mai]->m_position.x;
				junban->tateposi[junban->mai][1] = tate[junban->mai]->m_position.z;
				junban->tateposi[junban->mai][2] = tate[junban->mai]->m_position.y;

				//�ݒu����G�t�F�N�g�𗬂�
				effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(enKaminari);
				effectEmitter->SetScale({ 6.0f,6.0f,6.0f });
				effectEmitter->SetPosition({ tate[junban->mai]->m_position });
				effectEmitter->Play();

				//���ʉ���炷�B
				SoundSource* kaminari = NewGO<SoundSource>(0);
				kaminari->Init(0);
				kaminari->SetVolume(2.5f);
				//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
				kaminari->Play(false);


				tate[junban->mai]->SetidouState(1);
			}
		}
	}

	//���̏ꏊ�����肵���Ƃ��̏���
	if (player2->sentakuState == 2)
	{
		if (tate[junban->mai]->GetidouState() == 0)
		{
			if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonA))
			{
				for (int i = 0; i < 30; i++)
				{
					if (tate[junban->mai]->m_position.x == junban->tateposi[i][0] && tate[junban->mai]->m_position.z == junban->tateposi[i][1])
					{
						//���ʉ���炷�B
						SoundSource* buu = NewGO<SoundSource>(0);
						buu->Init(22);
						buu->SetVolume(2.5f);
						//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
						buu->Play(false);
						return;		//�����ꏊ�ɏ����u���Ă���ƌ���ł��Ȃ��B
					}
				}

				//�ꏊ������Ă��Ȃ�������
				//���̃|�W�V�������o��������
				junban->tateposi[junban->mai][0] = tate[junban->mai]->m_position.x;
				junban->tateposi[junban->mai][1] = tate[junban->mai]->m_position.z;
				junban->tateposi[junban->mai][2] = tate[junban->mai]->m_position.y;

				//�ݒu����G�t�F�N�g�𗬂�
				effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(enKaminari);
				effectEmitter->SetScale({ 6.0f,6.0f,6.0f });
				effectEmitter->SetPosition({ tate[junban->mai]->m_position });
				effectEmitter->Play();

				//���ʉ���炷�B
				SoundSource* kaminari = NewGO<SoundSource>(0);
				kaminari->Init(0);
				kaminari->SetVolume(2.5f);
				//���ʉ��̓����V���b�g�Đ�(���[�v�����Ȃ�)�Ȃ̂�false�B
				kaminari->Play(false);


				tate[junban->mai]->SetidouState(1);
			}
		}
	}

	if (junban->KoutaiState == 1)
	{
		if (player->sentakuState == 2)
		{
			//���̏ꏊ�����肵����
			if (tate[junban->mai]->GetidouState() == 1)
			{
				player->nikaiaruki++;
				player->tatenokori -= 1;
				game->UI_Update();
				junban->nobiStateR = 1;//�^�[���`�F���W��ʕ\��
				junban->KoutaiState = 3;
				player->tatearu = 0;
				player->sentakuState = 0;
				if (junban->mai >= 1 && tate[junban->mai - 1]->kowasu == false)
				{
					tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

					//�摜�̍����ւ�
					tate[junban->mai - 1]->Harikae();
				}
				junban->mai++;
				
			}
		}
	}

	if (junban->KoutaiState == 2)
	{
		if (player2->sentakuState == 2)
		{
			//���̏ꏊ�����肵����
			if (tate[junban->mai]->GetidouState() == 1)
			{
				player2->nikaiwalk++;
				player2->tatenokori2 -= 1;
				game->UI_Update();
				player2->bariaefe = 0;
				junban->nobiStateB = 1;//�^�[���`�F���W��ʕ\��
				junban->KoutaiState = 4;
				player2->tatearu = 0;
				player2->sentakuState = 0;
				if (junban->mai >= 1 && tate[junban->mai - 1]->kowasu == false)
				{
					tate[junban->mai - 1]->kowasu = true;//�Q�^�[���ڂ��炵���󂹂Ȃ�

					//�摜�̍����ւ�
					tate[junban->mai - 1]->Harikae();

				}
				junban->mai++;
				
			}
		}
	}
}

void Tatekanri::Kyanseru()
{
	if (junban->KoutaiState == 1)
	{
		//���̏ꏊ�Ɖ�]�����ɖ߂��B
		tate[junban->mai]->m_position = { 500.0f,500.0f,500.0f };
		tate[junban->mai]->rot.SetRotationDegY(0.0f);
		tate[junban->mai]->tatemawa = 0;
		tate[junban->mai]->SetidouState(1);
		player->tatearu = 0;
		player->sentakuState = 0;
	}
	else if (junban->KoutaiState == 2)
	{
		//���̏ꏊ�Ɖ�]�����ɖ߂��B
		tate[junban->mai]->m_position = { 500.0f,500.0f,500.0f };
		tate[junban->mai]->rot.SetRotationDegY(0.0f);
		tate[junban->mai]->tatemawa = 0;
		tate[junban->mai]->SetidouState(1);
		player2->tatearu = 0;
		player2->sentakuState = 0;
	}
}