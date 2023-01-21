#include "stdafx.h"
#include "GameCamera.h"
#include "Stage.h"
#include "Junban.h"
#include "Player.h"
#include "Player2.h"
#include "BattleStart.h"

GameCamera::GameCamera()
{
	stage = FindGO<Stage>("stage");
	junban = FindGO<Junban>("junban");
	player = FindGO<Player>("player");
	player2 = FindGO<Player2>("player2");
	battlestart = FindGO<BattleStart>("battlestart");

	//�ߕ��ʂ�ݒ肷��B
	g_camera3D->SetNear(1.0f);
	//�����ʂ�ݒ肷��B
	g_camera3D->SetFar(5000.0f);
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//�ŏ��̓o��V�[���̃J����(�˂���)
	if (player->PlayerState == 12)
	{
		//�����_��ݒ肷��
		Vector3 target = player->m_position;
		target.y += 10.0f;
		//���_��ݒ肷��B
		Vector3 cameraPos = { 30.0,25.0,0.0 };
		//���_�̐ݒ�
		Vector3 pos = cameraPos;
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}
	//�ŏ��̓o��V�[���̃J����(������)
	if (player2->PlayerState == 12)
	{
		//�����_��ݒ肷��
		Vector3 target = player2->m_position;
		target.y += 10.0f;
		//���_��ݒ肷��B
		Vector3 cameraPos = { -30.0,25.0,0.0 };
		//���_�̐ݒ�
		Vector3 pos = cameraPos;
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}

	if (junban->KoutaiState == 1 || junban->KoutaiState == 4)
	{
		//�����_��ݒ肷��
		Vector3 target=stage->m_position;
		target.x = stage->m_position.x - 30.0f;//�����_�͒��S��菭����O
		//���_��ݒ肷��B
		Vector3 cameraPos = target;
		cameraPos.x -= 140.0f;
		cameraPos.y += 100.0f;
	
		//�Ō�̋Z�̃J����
		if (player->PlayerState == 9 || player->PlayerState == 10)
		{
			//�����_��ݒ肷��
			target = player->m_position;
			target.y = player->m_position.y + 5.0f;
			//���_��ݒ肷��B
			cameraPos = target;
			cameraPos.x = +90.0f;
			cameraPos.y = +80.0f;
			cameraPos.z = -50.0f;

			//���_�̐ݒ�
			Vector3 pos = target + cameraPos;
			//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(pos);

			//�J�����̍X�V
			g_camera3D->Update();
			return;
		}
		//���U���g��ʂ̃J����
		if (player->PlayerState == 11)
		{
			//�����_��ݒ肷��
			target = player->m_position;
			target.y = player->m_position.y + 25.0f;
			//���_��ݒ肷��B
			cameraPos = target;
			cameraPos.x = +180.0f;
			cameraPos.y = +60.0f;
			cameraPos.z = player->m_position.z;
			
			//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(cameraPos);

			//�J�����̍X�V
			g_camera3D->Update();
			return;
		}

		if (player->PlayerState >= 0 && player->PlayerState <= 8)
		{
			if (junban->KoutaiState == 1)
			{
				//�X�e�B�b�N���g�������̏���
				CameraMove(cameraPos, target, 0);
			}
			else if (junban->KoutaiState == 4)//�^�[���`�F���W���͏����|�W
			{
				//���_�̐ݒ�
				Vector3 pos = target + cameraPos;
				//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
				g_camera3D->SetTarget(target);
				g_camera3D->SetPosition(pos);

				//�J�����̍X�V
				g_camera3D->Update();
				return;
			}
		}
	}

	if (junban->KoutaiState == 2 || junban->KoutaiState == 3)
	{
		//�����_��ݒ肷��
		Vector3 target = stage->m_position;
		target.x = stage->m_position.x + 30.0f;//�����_�͒��S��菭����O
		//���_��ݒ肷��B
		Vector3 cameraPos = target;
		cameraPos.x += 140.0f;
		cameraPos.y += 100.0f;

		//�Ō�̋Z�̃J����
		if (player2->PlayerState == 9 || player2->PlayerState == 10)
		{
			//�����_��ݒ肷��
			target = player2->m_position;
			target.y = player2->m_position.y + 5.0f;
			//���_��ݒ肷��B
			cameraPos = target;
			cameraPos.x = -90.0f;
			cameraPos.y = +80.0f;
			cameraPos.z = -50.0f;

			//���_�̐ݒ�
			Vector3 pos = target + cameraPos;
			//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(pos);

			//�J�����̍X�V
			g_camera3D->Update();
			return;
		}
		//���U���g��ʂ̃J����
		if (player2->PlayerState == 11)
		{
			//�����_��ݒ肷��
			target = player2->m_position;
			target.y = player2->m_position.y + 25.0f;
			//���_��ݒ肷��B
			cameraPos = target;
			cameraPos.x = -180.0f;
			cameraPos.y = +60.0f;
			cameraPos.z = player2->m_position.z;

			//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(cameraPos);

			//�J�����̍X�V
			g_camera3D->Update();
			return;
		}

		if (player2->PlayerState >= 0 && player2->PlayerState <= 8)
		{
			if (junban->KoutaiState == 2)
			{
				//�X�e�B�b�N���g�������̏���
				CameraMove(cameraPos, target, player2->PAD_MODE);
			}
			else if (junban->KoutaiState == 3)//�^�[���`�F���W���͏����|�W
			{
				//���_�̐ݒ�
				Vector3 pos = target + cameraPos;
				//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
				g_camera3D->SetTarget(target);
				g_camera3D->SetPosition(pos);

				//�J�����̍X�V
				g_camera3D->Update();
				return;
			}
		}
	}
}

void GameCamera::CameraMove(Vector3 cam, Vector3 tar,int PAD_MODE)
{
	Vector3 cameraPosOld = cam;
	//�X�e�B�b�N�̓��͂��g���ăJ�������񂷁B
	float x = g_pad[PAD_MODE]->GetRStickXF();
	float y = g_pad[PAD_MODE]->GetRStickYF();
	//Y������̉�]
	Quaternion qRotY;
	qRotY.SetRotationDeg(Vector3::AxisY, 100.0f * x);
	qRotY.Apply(cam);
	//X������̉�]
	Vector3 qRotX;
	qRotX.Cross(Vector3::AxisY, cam);
	qRotX.Normalize();
	qRotY.SetRotationDeg(qRotX, 30.0f * y);
	qRotY.Apply(cam);

	//�J�����̉�]�̏�����`�F�b�N����B
	Vector3 toPosDer = cam;
	toPosDer.Normalize();
	if (toPosDer.y < -90.0f)
	{
		//���������
		cam = cameraPosOld;
	}
	else if (toPosDer.y > 110.0f)
	{
		//����������
		cam = cameraPosOld;
	}

	//���_�̐ݒ�
	Vector3 pos = tar + cam;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(tar);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V
	g_camera3D->Update();
}