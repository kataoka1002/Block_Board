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

	//効果音。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/piko.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/piko_kettei.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/piko_modoru.wav");
	g_soundEngine->ResistWaveFileBank(19, "Assets/sound/BGM/taitoru.wav");

	soundSource = NewGO<SoundSource>(0, "soundSource");
	soundSource->Init(19);
	soundSource->SetVolume(0.5f);
	//効果音はループ再生なのでtrue。
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
	//選択の処理
	if (selectState == 1)
	{
		yaziposi.y = -172;
		
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//効果音を再生
			SE(2);

			//矢印のサイズと場所を変える
			yaziposi.x = 190;
			yaziposi.y = -105;
			s_yazirusi.SetScale({ 0.05f, 0.05f, 1.0f });
			PadState = 0;
			selectState = 6;
		}

		//下ボタンで矢印移動
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			//矢印が下に移動
			selectState = 2;
			//効果音を再生
			SE(1);
		}

	}
	else if (selectState == 2)
	{
		yaziposi.y = -272;

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//説明画面の表示
			selectState = 3;
			//効果音を再生
			SE(2);
		}

		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			//矢印が上に移動
			selectState = 1;

			//効果音を再生
			SE(1);
		}
		else if (g_pad[0]->IsTrigger(enButtonDown))
		{
			//矢印が下に移動
			selectState = 4;

			//効果音を再生
			SE(1);
		}
	}
	else if (selectState == 3)
	{
		//YaziRot();

		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//タイトルに戻る
			selectState = 2;
			//効果音を再生
			SE(3);
		}
	}
	else if (selectState == 4)
	{
		yaziposi.y = -378;

		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			//矢印が上に移動
			selectState = 2;

			//効果音を再生
			SE(1);
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//説明画面の表示
			selectState = 5;
			//効果音を再生
			SE(2);
		}
	}
	else if (selectState == 5)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//タイトルに戻る
			selectState = 4;
			//効果音を再生
			SE(3);
		}
	}
	else if (selectState == 6)
	{
		if (PadState == 0)
		{
			if (m_isWaitFadeout) {//フェードアウト中ならこっち
				if (m_fade->IsFade() == false) {
					//フェードアウトが終わったらgameをNewGOする。
					Game* game = NewGO<Game>(0, "game");
					game->PAD_MODE = 0;
					DeleteGO(this);
				}
			}
			else //フェードアウト中じゃないならこっち
			{
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//コントローラー1個で遊ぶ
					m_isWaitFadeout = true;//フェードアウト中かどうかを判断するフラグをtrueにする。
					m_fade->StartFadeOut();//フェードアウト開始(ロード中の画面をゆっくり表示)

					//効果音を再生
					SE(2);
				}

				if (g_pad[0]->IsTrigger(enButtonB))
				{
					yaziposi.x = -150.0f;
					yaziposi.y = -172;
					s_yazirusi.SetScale({ 0.08f, 0.08, 1.0f });
					selectState = 1;

					//効果音を再生
					SE(3);
				}

				if (g_pad[0]->IsTrigger(enButtonDown))
				{
					//矢印を下に移動させる
					yaziposi.y = -214;
					PadState = 1;

					//効果音を再生
					SE(1);
				}
			}
		}
		else if (PadState == 1)
		{
			if (m_isWaitFadeout) {//フェードアウト中ならこっち
				if (m_fade->IsFade() == false) {
					//フェードアウトが終わったらgameをNewGOする。
					Game* game = NewGO<Game>(0, "game");
					game->PAD_MODE = 1;
					DeleteGO(this);
				}
			}
			else//フェードアウト中じゃないならこっち
			{
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//コントローラー2個で遊ぶ
					m_isWaitFadeout = true;//フェードアウト中かどうかを判断するフラグをtrueにする。
					m_fade->StartFadeOut();//フェードアウト開始(ロード中の画面をゆっくり表示)

					//効果音を再生
					SE(2);
				}

				if (g_pad[0]->IsTrigger(enButtonB))
				{
					yaziposi.x = -150.0f;
					yaziposi.y = -172;
					s_yazirusi.SetScale({ 0.08f, 0.08, 1.0f });
					selectState = 1;

					//効果音を再生
					SE(3);
				}

				if (g_pad[0]->IsTrigger(enButtonUp))
				{
					//矢印を上に移動させる
					yaziposi.y = -105;
					PadState = 0;

					//効果音を再生
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
		//矢印の動きの処理
		s_yazirusi.SetPosition(yaziposi);
		if (yazimove == 1)
		{
			//右に移動
			yaziposi.x += 0.4;
			if (yaziposi.x > -150)
			{
				yazimove = 2;
			}
		}
		else if (yazimove == 2)
		{
			//左に移動
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
		//矢印の動きの処理
		s_yazirusi.SetPosition(yaziposi);
		if (yazimove == 1)
		{
			//右に移動
			yaziposi.x += 0.3;
			if (yaziposi.x > 190)
			{
				yazimove = 2;
			}
		}
		else if (yazimove == 2)
		{
			//左に移動
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
	//効果音を鳴らす。
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	//効果音はワンショット再生(ループさせない)なのでfalse。
	soundSource->Play(false);
}

//void Title::YaziRot()
//{
//	//初期ポジ
//	s_yazirotL.SetPosition({ L,318.0f,0.0f });//右590左-585
//	s_yazirotL.Update();
//	s_yazirotR.SetPosition({ R,-330.0f,0.0f });//右590左-585
//	s_yazirotR.Update();
//	s_yazirotU.SetPosition({ 645.0f,U,0.0f });//下-290上280
//	s_yazirotU.Update();
//	s_yazirotD.SetPosition({ -638.0f,D,0.0f });//下-290上280
//	s_yazirotD.Update();
//
//	//矢印の動きの処理
//	if (yazirot == 1)
//	{
//		L -= 30.0;
//		R += 30.0;
//		if (L <= -585)
//		{
//			//初期ポジに戻す
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
//			//初期ポジに戻す
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
	//ボタンの説明を表示
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

	//遊び方を表示
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