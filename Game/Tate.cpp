#include "stdafx.h"
#include "Tate.h"
#include "Player.h"
#include "Player2.h"
#include "Junban.h"
#include "Tatekanri.h"
#include "Game.h"
#include "Syoumetu.h"

Tate::Tate()
{
	m_modelRender = new ModelRender;
	m_modelRender->SetRaytracingWorld(false);
	m_modelRender->Init("Assets/modelData/stone.tkm");
	m_modelRender->Update();

	//効果音。
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/tateidou.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/tatekaiten.wav");
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/haretu.wav");

	junban = FindGO<Junban>("junban");
	player = FindGO<Player>("player");
	player2 = FindGO<Player2>("player2");
}

Tate::~Tate()
{

}

void Tate::SE(int bango,float volume)
{
	//効果音を鳴らす。
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	soundSource->SetVolume(volume);
	//効果音はワンショット再生(ループさせない)なのでfalse。
	soundSource->Play(false);
}

void Tate::Update()
{
	if (Gameend == true) {
		return;
	}

	if (player->sentakuState == 2 || player2->sentakuState == 2)
	{
		if (idouState == 0)
		{
			//キャラクター１の場合
			if (junban->KoutaiState == 1)
			{
				if (m_position.z > -70)
				{
					if (g_pad[0]->IsTrigger(enButtonRight) && junban->KoutaiState == 1)		//移動の処理
					{
						m_position.z -= 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.z < 70)
				{
					if (g_pad[0]->IsTrigger(enButtonLeft) && junban->KoutaiState == 1)
					{
						m_position.z += 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.x < 70)
				{
					if (g_pad[0]->IsTrigger(enButtonUp) && junban->KoutaiState == 1)
					{
						m_position.x += 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.x > -70)
				{
					if (g_pad[0]->IsTrigger(enButtonDown) && junban->KoutaiState == 1)
					{
						m_position.x -= 20;
						SE(9, 1.5f);
					}
				}

				//回転処理
				if (tatemawa == 0 && g_pad[0]->IsTrigger(enButtonRB1) && m_position.z > -70)
				{
					m_position.x -= 10;
					m_position.z -= 10;
					rot.SetRotationDegY(90.0f);
					SE(10, 1.5f);

					tatemawa = 1;
				}

				if (tatemawa == 1 && g_pad[0]->IsTrigger(enButtonLB1) && m_position.x < 70)
				{
					m_position.x += 10;
					m_position.z += 10;
					rot.SetRotationDegY(180.0f);
					SE(10, 1.5f);

					tatemawa = 0;
				}

				//盾のキャンセル
				if (g_pad[0]->IsTrigger(enButtonB))
				{
					tatekanri->Kyanseru();
					SE(8);
				}
			}

			//キャラクター2の場合
			if (junban->KoutaiState == 2)
			{
				if (m_position.z < 70)
				{
					if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonRight))
					{
						m_position.z += 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.z > -70)
				{
					if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonLeft))
					{
						m_position.z -= 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.x > -70)
				{
					if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonUp))
					{
						m_position.x -= 20;
						SE(9, 1.5f);
					}
				}

				if (m_position.x < 70)
				{
					if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonDown))
					{
						m_position.x += 20;
						SE(9, 1.5f);
					}
				}

				//回転処理
				if (tatemawa == 0 && g_pad[player2->PAD_MODE]->IsTrigger(enButtonLB1) && m_position.z > -70)
				{
					m_position.x -= 10;
					m_position.z -= 10;
					rot.SetRotationDegY(90.0f);
					SE(10, 1.5f);

					tatemawa = 1;
				}

				if (tatemawa == 1 && g_pad[player2->PAD_MODE]->IsTrigger(enButtonRB1) && m_position.x < 70)
				{
					m_position.x += 10;
					m_position.z += 10;
					rot.SetRotationDegY(180.0f);
					SE(10, 1.5f);

					tatemawa = 0;
				}

				//盾のキャンセル
				if (g_pad[player2->PAD_MODE]->IsTrigger(enButtonB))
				{
					tatekanri->Kyanseru();
					SE(8);
				}
			}
		}
	}

	m_modelRender->SetPosition(m_position);
	m_modelRender->Update();
	m_modelRender->SetRotation(rot);
}

void Tate::Sinuefe()
{
	//盾が消滅するエフェクト
	Syoumetu* syo = NewGO<Syoumetu>(0, "syoumetu");
	syo->PlayEffect(m_position);

	SE(13);
}

void Tate::Harikae()
{
	//画像の差し替え
	delete m_modelRender;
	m_modelRender = new ModelRender;
	m_modelRender->SetRaytracingWorld(false);
	m_modelRender->Init("Assets/modelData/Tate.tkm");

	//盾が張り替えられるエフェクト
	Syoumetu* syo = NewGO<Syoumetu>(0, "syoumetu");
	syo->PlayEffect_Harikae({ m_position.x,m_position.y + 10.0f,m_position.z });
}

void Tate::Render(RenderContext& rc)
{
	//描画する。
	m_modelRender->Draw(rc);
}