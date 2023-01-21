#include "stdafx.h"
#include "Junban.h"

Junban::Junban()
{
	spred.Init("Assets/modelData/Turnchange_red.DDS", 1980.0f, 1080.0f);
	spred.SetPosition({ 980.0f,0.0f,0.0f });
	spred.SetPivot(m_pivotR);
	
	spblue.Init("Assets/modelData/Turnchange_blue.DDS", 1980.0f, 1080.0f);
	spblue.SetPosition({ -980.0f,0.0f,0.0f });
	spblue.SetPivot(m_pivotB);

	spblack.Init("Assets/modelData/usublack.DDS", 1980.0f, 1080.0f);
	spblack.SetPosition({ 0.0f,0.0f,0.0f });
	spblack.Update();

	
}

Junban::~Junban()
{

}

void Junban::Update()
{
	spred.SetScale({ nobiR,1.0f,1.0f });
	spblue.SetScale({ nobiB,1.0f,1.0f });
	if (KoutaiState == 3)//�ԐF�̃`�F���W���o��
	{
		if (nobiStateR == 1)//�E�ɐL�΂�
		{
			nobiR += 0.25;
		}
		else if (nobiStateR == 2)//���ɏk�߂�
		{
			nobiR -= 0.25;
		}
		else if (nobiStateR == 3)//�L�т���Ԉێ�
		{
			//���Ԍo��
			GameTimer -= g_gameTime->GetFrameDeltaTime();	//�J�E���g�������Ă���

			if (GameTimer <= 0)
			{
				nobiStateR = 2;
			}
		}

		if (nobiR >= 1.0 && nobiStateR == 1)//�傫�������x�悭�Ȃ�����Œ�
		{
			nobiR = 1.0;
			nobiStateR = 3;
		}
		else if (nobiR <= 0.0 && nobiStateR == 2)//�k�ݏI�������^�[����ς���
		{
			nobiR = 0.0;
			KoutaiState = 2;
			GameTimer = 0.7f;//�^�C�}�[�̃��Z�b�g	
			nobiStateR = 0;		
		}
	}
	if (KoutaiState == 4)//�F�̃`�F���W���o��
	{
		if (nobiStateB == 1)//�E�ɐL�΂�
		{
			nobiB += 0.25;
		}
		else if (nobiStateB == 2)//���ɏk�߂�
		{
			nobiB -= 0.25;
		}
		else if (nobiStateB == 3)//�L�т���Ԉێ�
		{
			//���Ԍo��
			GameTimer -= g_gameTime->GetFrameDeltaTime();	//�J�E���g�������Ă���

			if (GameTimer <= 0)
			{
				nobiStateB = 2;
			}
		}

		if (nobiB >= 1.0 && nobiStateB == 1)//�傫�������x�悭�Ȃ�����Œ�
		{
			nobiB = 1.0;
			nobiStateB = 3;
		}
		else if (nobiB <= 0.0 && nobiStateB == 2)//�k�ݏI�������^�[����ς���
		{
			nobiB = 0.0;
			nobiStateB = 0;
			GameTimer = 0.7f;//�^�C�}�[�̃��Z�b�g
			KoutaiState = 1;
		}
	}

	spred.Update();
	spblue.Update();
}

void Junban::Render(RenderContext& rc)
{
	if (KoutaiState == 3 || KoutaiState == 4)
	{
		spblack.Draw(rc);
	}
	spred.Draw(rc);
	spblue.Draw(rc);
}

