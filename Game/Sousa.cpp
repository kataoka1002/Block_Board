#include "stdafx.h"
#include "Sousa.h"
#include "Player.h"
#include "Player2.h"
#include "Junban.h"

Sousa::Sousa()
{
	A_botan.Init("Assets/modelData/UI/A_kettei.DDS", 1000.0f, 1000.0f);
	A_botan.SetPosition({ -170.0f,-460.0f,0.0f });
	A_botan.SetScale({ 0.2f, 0.2f, 1.0f });
	A_botan.Update();

	X_botan.Init("Assets/modelData/UI/X_tate.DDS", 1000.0f, 1000.0f);
	X_botan.SetPosition({ -170.0f,-460.0f,0.0f });
	X_botan.SetScale({ 0.19f,0.19f,1.0f });
	X_botan.Update();

	Y_botan.Init("Assets/modelData/UI/Y_idou.DDS", 1000.0f, 1000.0f);
	Y_botan.SetPosition({ 165.0f,-460.0f,0.0f });
	Y_botan.SetScale({ 0.2f,0.2f,1.0f });
	Y_botan.Update();

	R2_botan.Init("Assets/modelData/UI/R2_kyanseru2.DDS", 1000.0f, 1000.0f);
	R2_botan.SetPosition({ 0.0f,-370.0f,0.0f });
	R2_botan.SetScale({0.25f,0.25f,1.0f});
	R2_botan.Update();

	L2_botan.Init("Assets/modelData/UI/L2_kougeki.DDS", 1000.0f, 1000.0f);
	L2_botan.SetPosition({ 0.0f,-363.0f,0.0f });
	L2_botan.SetScale({ 0.18f,0.18f,1.0f });
	L2_botan.Update();

	R1L1_botan.Init("Assets/modelData/UI/R1L1_kaiten.DDS", 1000.0f, 1000.0f);
	R1L1_botan.SetPosition({ 0.0f,-365.0f,0.0f });
	R1L1_botan.SetScale({ 0.21f,0.21f,1.0f });
	R1L1_botan.Update();

	Jyu_botan.Init("Assets/modelData/UI/jyu_sentaku.DDS", 1000.0f, 1000.0f);
	Jyu_botan.SetPosition({ 160.0f,-460.0f,0.0f });
	Jyu_botan.SetScale({0.2f,0.2f,1.0f});
	Jyu_botan.Update();

	huti_pinku.Init("Assets/modelData/UI/huti_pinku.DDS", 1000.0f, 1000.0f);
	huti_pinku.SetPosition({ 0.0f,-360.0f,0.0f });
	huti_pinku.SetScale({ 0.24f,0.24f,1.0f });
	huti_pinku.Update();

	huti_ki.Init("Assets/modelData/UI/huti_ki.DDS", 1000.0f, 1000.0f);
	huti_ki.SetPosition({ 160.0f,-445.0f,0.0f });
	huti_ki.SetScale({ 0.24f,0.24f,1.0f });
	huti_ki.Update();

	huti_ao.Init("Assets/modelData/UI/huti_ao.DDS", 1000.0f, 1000.0f);
	huti_ao.SetPosition({ -170.0f,-445.0f,0.0f });
	huti_ao.SetScale({ 0.24f,0.24f,1.0f });
	huti_ao.Update();

	Title_modoru.Init("Assets/modelData/UI/A_title_modoru.DDS", 1000.0f, 1000.0f);
	Title_modoru.SetPosition({ 700.0f,-500.0f,0.0f });
	Title_modoru.SetScale({ 0.3f,0.3f,1.0f });
	Title_modoru.Update();

	B_botan.Init("Assets/modelData/UI/B_kyanseru.DDS", 1000.0f, 1000.0f);
	B_botan.SetPosition({ 340.0f,-380.0f,0.0f });
	B_botan.SetScale({ 0.225f,0.225f,1.0f });
	B_botan.Update();

	player = FindGO<Player>("player");
	player2 = FindGO<Player2>("player2");
	junban = FindGO<Junban>("junban");
}

Sousa::~Sousa()
{

}

void Sousa::Update()
{

}

void Sousa::Render(RenderContext& rc)
{
	if (junban->KoutaiState != 3 && junban->KoutaiState != 4 &&
		player->PlayerState != 11 && player2->PlayerState != 11 &&
		player->PlayerState != 12 && player2->PlayerState != 12)
	{
		//攻撃中は再生しない
		if (player->PlayerState != 5 && player2->PlayerState != 5)
		{
			huti_pinku.Draw(rc);
			huti_ki.Draw(rc);
			//移動選択中は表示しない
			if (player->sentakuState != 1 && player2->sentakuState != 1)
			{
				huti_ao.Draw(rc);
			}
		}
		
		//ネズミの場合
		if (player->sentakuState == 0 && player2->sentakuState == 0)
		{
			//選択画面
			X_botan.Draw(rc);
			Y_botan.Draw(rc);
			L2_botan.Draw(rc);
		}

		if (player->sentakuState == 1 && player2->sentakuState == 0)
		{
			//移動選択画面
			Jyu_botan.Draw(rc);
			R2_botan.Draw(rc);
		}

		if (player->sentakuState == 2 && player2->sentakuState == 0)
		{
			//盾選択画面
			A_botan.Draw(rc);
			Jyu_botan.Draw(rc);
			R1L1_botan.Draw(rc);
			B_botan.Draw(rc);
		}

		if (player->sentakuState == 3 && player2->sentakuState == 0)
		{
			//攻撃選択画面
			A_botan.Draw(rc);
			Jyu_botan.Draw(rc);
			R2_botan.Draw(rc);
		}

		//爺の場合
		if (player->sentakuState == 0 && player2->sentakuState == 0)
		{
			//選択画面
			X_botan.Draw(rc);
			Y_botan.Draw(rc);
			L2_botan.Draw(rc);
		}

		if (player->sentakuState == 0 && player2->sentakuState == 1)
		{
			//移動選択画面
			Jyu_botan.Draw(rc);
			R2_botan.Draw(rc);
		}

		if (player->sentakuState == 0 && player2->sentakuState == 2)
		{
			//盾選択画面
			A_botan.Draw(rc);
			Jyu_botan.Draw(rc);
			R1L1_botan.Draw(rc);
			B_botan.Draw(rc);
		}

		if (player->sentakuState == 0 && player2->sentakuState == 3)
		{
			//攻撃選択画面
			A_botan.Draw(rc);
			Jyu_botan.Draw(rc);
			R2_botan.Draw(rc);
		}
	}

	if (player->PlayerState == 11 || player2->PlayerState == 11)
	{
		Title_modoru.Draw(rc);
	}
}