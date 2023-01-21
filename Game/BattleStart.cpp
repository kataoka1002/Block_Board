#include "stdafx.h"
#include "BattleStart.h"
#include "Junban.h"
#include "Player2.h"

BattleStart::BattleStart()
{
	battlestart.Init("Assets/modelData/BattleStart.DDS", 1980.0f, 1080.0f);
	battlestart.SetPosition({ 0.0f,0.0f,0.0f });
	battlestart.SetScale({ ScaleX,ScaleY,1.0 });
	
	kaminariR.Init("Assets/modelData/kaminariR.DDS", 1980.0f, 1080.0f);
	kaminariR.SetScale({ 1.0f,1.0f,1.0f });
	kaminariR.SetPosition({ kamiposiRX,kamiposiRY,0.0f });

	kaminariL.Init("Assets/modelData/kaminariL.DDS", 1980.0f, 1080.0f);
	kaminariL.SetScale({ 1.0f,1.0f,1.0f });
	kaminariL.SetPosition({ kamiposiLX,kamiposiLY,0.0f });

	battlestart.Update();
	kaminariR.Update();
	kaminariL.Update();

	junban = FindGO<Junban>("junban");
	player2 = FindGO<Player2>("player2");
}

BattleStart::~BattleStart()
{

}

void BattleStart::Update()
{
	if (gazoset == true)
	{
		if (ScaleX >= 0.5)
		{
			//�o�g���X�^�[�g��ʂ��������g��
			battlestart.SetScale({ ScaleX,ScaleY,1.0 });

			ScaleX += 0.003;
			ScaleY += 0.003;
		}
		else
		{
			//�o�g���X�^�[�g��ʂ�f�����g��
			battlestart.SetScale({ ScaleX,ScaleY,1.0 });

			ScaleX += 0.1;
			ScaleY += 0.1;
		}

		battlestart.Update();
		
		//�����΂߂ɗ��Ƃ�
		kaminariR.SetPosition({ kamiposiRX,kamiposiRY,0.0f });
		kaminariL.SetPosition({ kamiposiLX,kamiposiLY,0.0f });

		kamiposiRX -= 100.0;
		kamiposiRY -= 50.0;
		kamiposiLX += 100.0;
		kamiposiLY -= 50.0;

		kaminariR.Update();
		kaminariL.Update();

		if (ScaleX >= 0.7)
		{
			//�o�g���X�^�[�g�����̑傫���ɂȂ�����UI��\�������ăQ�[���X�^�[�g
			player2->PlayerState = 0;
			junban->KoutaiState = 1;
			gazoset = false;
		}
	}
}

void BattleStart::Render(RenderContext& rc)
{
	if (gazoset == true)
	{
		kaminariR.Draw(rc);
		kaminariL.Draw(rc);
		battlestart.Draw(rc);
	}
}