#include "stdafx.h"
#include "Gazou.h"
//#include "Player.h"

Gazou::Gazou()
{
	//player = FindGO<Player>("player");

	//�ړ��I���̉摜�쐬
	spriteRender.Init("Assets/modelData/idou.DDS", 75.0f, 75.0f);
	spriteRender.SetPosition({ -200.0f, -350.0f, 0.0f });
	spriteRender.SetScale({ 2.4f,2.4f,2.4f });

	//���I���̉摜�쐬
	spriteRender2.Init("Assets/modelData/tatesentaku.DDS", 75.0f, 75.0f);
	spriteRender2.SetPosition({ 200.0f, -350.0f, 0.0f });
	spriteRender2.SetScale({ 2.4f,2.4f,2.4f });

	//�U���ł���^�C�~���O�̂ݍU���I���̉摜�쐬
	/*if (player->m_position.x == 140)
	{
		spriteRender3.Init("Assets/modelData/tate.DDS", 75.0f, 75.0f);
		spriteRender3.SetPosition({ 0.0f, -350.0f, 0.0f });
		spriteRender3.SetScale({ 2.4f,2.4f,2.4f });
	}
	*/
}

Gazou::~Gazou()
{

}

void Gazou::Update()
{
	spriteRender.Update();
	spriteRender2.Update();
	//spriteRender3.Update();
}

void Gazou::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);
	//spriteRender3.Draw(rc);
}