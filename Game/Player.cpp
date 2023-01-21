#include "stdafx.h"
#include "Player.h"
#include "Junban.h"
#include "Tate.h"
#include "Player2.h"
#include "Tatekanri.h"
#include "Game.h"
#include "Title.h"
#include "Syoumetu.h"

Player::Player()
{
	animationClips[enAnimClip_Idle].Load("Assets/animData/nezumiData/nezumitaiki.tka");
	animationClips[enAnimClip_Idle].SetLoopFlag(true);
	animationClips[enAnimClip_Walk].Load("Assets/animData/nezumiData/nezumiaruki.tka");
	animationClips[enAnimClip_Walk].SetLoopFlag(true);
	animationClips[enAnimClip_Attack].Load("Assets/animData/nezumiData/nezumiattack.tka");
	animationClips[enAnimClip_Attack].SetLoopFlag(true);
	animationClips[enAnimClip_Jumatt].Load("Assets/animData/nezumiData/nezumijumatt.tka");
	animationClips[enAnimClip_Jumatt].SetLoopFlag(true);
	animationClips[enAnimClip_Dansu].Load("Assets/animData/nezumiData/nezumidansu.tka");
	animationClips[enAnimClip_Dansu].SetLoopFlag(true);

	m_modelRender.Init("Assets/modelData/player1/player1nezumi_new.tkm", animationClips, enAnimClip_Num, enModelUpAxisZ);
	m_modelRender.SetScale(0.65f, 0.65f, 0.65f);

	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
	});

	whitegazou.Init("Assets/modelData/white.DDS", 1920.0f, 1080.0f);

	P1WIN.Init("Assets/modelData/P1WIN.DDS", 1920.0f, 1080.0f);
	P1WIN.SetScale({ 0.65f,0.65f,1.0f });
	P1WIN.SetPosition({ 0.0f,330.0f,0.0f });
	P1WIN.Update();

	//効果音。
	
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/yawa_kettei.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/kyan.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/kazekikku.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/asioto.wav");
	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/jump.wav");
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/baria.wav");
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/syaki-n.wav");
	g_soundEngine->ResistWaveFileBank(20, "Assets/sound/hanabi.wav");

	
	
	junban = FindGO<Junban>("junban");
	tate = FindGO<Tate>("tate");
	player2 = FindGO<Player2>("player");
}

Player::~Player()
{
	DeleteGO(foot_soundSource);
	DeleteGO(effectEmitter);
}

void Player::Update()
{
	//TatekanriがNewGOされたら処理する
	if (tuzu == 1)
	{
		tatekanri = FindGO<Tatekanri>("tatekanri");
		tuzu = 2;
	}
		
	if (PlayerState == 0 || PlayerState == 12)
	{
		m_modelRender.SetAnimationSpeed(1.0f);
		m_modelRender.PlayAnimation(enAnimClip_Idle,0.1f);	//立ちアニメーションの再生
	}
	if (PlayerState >= 1 && PlayerState <= 4)
	{
		m_modelRender.SetAnimationSpeed(1.5f);
		m_modelRender.PlayAnimation(enAnimClip_Walk,0.1f);	//歩きアニメーションの再生
	}
	if (PlayerState == 5)
	{
		m_modelRender.SetAnimationSpeed(1.0f);
		m_modelRender.PlayAnimation(enAnimClip_Attack,0.1f);	//攻撃アニメーションの再生
	}
	if (PlayerState == 9)
	{
		GameTimer -= g_gameTime->GetFrameDeltaTime();	//カウントが減っていく

		//ホワイトアウトする
		whitegazou.SetMulColor({ 1.0f,1.0f,1.0f,toumeido });
		toumeido += 0.005;
		if (toumeido >= 1.0)
		{
			toumeido = 1.0;
		}
		
		if (GameTimer <= 0)
		{
			//時間が経過するとアニメーションの再生
			m_position.x = 100;
			m_modelRender.SetAnimationSpeed(1);
		}
	}
	if (PlayerState == 10)
	{
		m_position.y = 13;
		m_modelRender.SetAnimationSpeed(1.0f);
		m_modelRender.PlayAnimation(enAnimClip_Jumatt,0.1f);	//勝利アニメーション

		for (int i = 0; i < 30; i++)
		{
			tatekanri->tate[i]->Gameend = true;
		}
	}
	if (PlayerState == 11)
	{
		m_modelRender.SetAnimationSpeed(1.0f);
		m_modelRender.PlayAnimation(enAnimClip_Dansu);     //リザルトアニメーション

		
		//タイマーのカウントを減らす。
		GameTimer2 -= g_gameTime->GetFrameDeltaTime();

		if (GameTimer2 <= 0)
		{
			//花火のエフェクトを再生
			Syoumetu* hanabi1 = NewGO<Syoumetu>(0,"syoumetu");
			hanabi1->PlayEffect_Hanabi({ m_position.x - 50.0f,m_position.y + 40.0f,m_position.z + 80.0f });

			Syoumetu* hanabi2 = NewGO<Syoumetu>(0, "syoumetu");
			hanabi2->PlayEffect_Hanabi({ m_position.x - 50.0f,m_position.y + 40.0f,m_position.z - 80.0f });

			SE(20);

			GameTimer2 = 2.0;
		}

		//Aボタンを押してタイトルに戻る
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			NewGO<Title>(0, "title");
			DeleteGO(game);
		}
	}

	//シャキーンは１回のみ再生
	if (nikaiaruki == 4 && syaki == 0)
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

void Player::SE(int bango,float volume)
{
	//効果音を鳴らす。
	SoundSource* soundSource = NewGO<SoundSource>(0);
	soundSource->Init(bango);
	soundSource->SetVolume(volume);
	//効果音はワンショット再生(ループさせない)なのでfalse。
	soundSource->Play(false);
}

void Player::AsiotoSE(int bango)
{
	if (foot_soundSource != nullptr) {
		DeleteGO(foot_soundSource);
	}

	//効果音を鳴らす。
	foot_soundSource = NewGO<SoundSource>(0);
	foot_soundSource->Init(bango);
	foot_soundSource->SetVolume(3.5f);
	//効果音はワンショット再生(ループさせない)なのでfalse。
	foot_soundSource->Play(false);
}

void Player::Move()
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
	if (PlayerState == 5) {
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
	if (PlayerState == 12){
		return;
	}


	if (junban->KoutaiState == 1)
	{
		//Yを押して移動を選択
		if (g_pad[0]->IsTrigger(enButtonY) && tatearu == 0 && sentakuState == 0)
		{
			sentakuState = 1;
			SE(7);
		}
		//Xを押して盾を選択
		else if (g_pad[0]->IsTrigger(enButtonX) && tatenokori > 0 && tatearu == 0 && sentakuState == 0)
		{
			sentakuState = 2;
			SE(7);
		}
		//L2を押して盾を壊す選択
		else if (g_pad[0]->IsTrigger(enButtonLB2) && sentakuState == 0)
		{
			sentakuState = 3;
			SE(7);
		}
		

		//１の移動を選択した場合
		if (sentakuState == 1)
		{
			if (g_pad[0]->IsTrigger(enButtonRight))				//右ボタンが押されたら
			{
				for (int i = 0; i < 40; i++) //盾を1枚目から順にチェック
				{
					if (m_position.x == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] + 10)
					{
						SE(22);
						return;		//前に盾が置いてあると動けない
					}
				}

				//ここからは盾が前に無かった時の処理
				if (m_position.z == -80)
				{
					return;
				}
				else if (m_position.z > -80)
				{
					PlayerState = 1;
					Vector3 targetPos = m_position;		//目標地点の設定
					targetPos.z -= 20.0f;				//20.0f先が目標
					m_targetPos = targetPos;

					//目標地点から今の場所を引いて80で割った数が速さ
					m_move = (m_targetPos - m_position) / 60.0f;

					AsiotoSE(14);
				}

			}

			if (g_pad[0]->IsTrigger(enButtonLeft))					//左ボタンが押されたら
			{
				for (int i = 0; i < 40; i++)
				{
					if (m_position.x == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] - 10)
					{
						SE(22);
						return;		//前に盾が置いてあると動けない
					}
				}

				//ここからは前に盾がなかった時の処理
				if (m_position.z == 80)
				{
					return;
				}
				else if (m_position.z < 80)
				{
					PlayerState = 2;
					Vector3 targetPos = m_position;		//目標地点の設定
					targetPos.z += 20.0f;				//20.0f先が目標
					m_targetPos = targetPos;

					//目標地点から今の場所を引いて80で割った数が速さ
					m_move = (m_targetPos - m_position) / 60.0f;

					AsiotoSE(14);
				}
			}

			if (g_pad[0]->IsTrigger(enButtonUp))					//上ボタンが押されたら
			{
				for (int i = 0; i < 40; i++)
				{
					if (m_position.x == junban->tateposi[i][0] - 10 && m_position.z == junban->tateposi[i][1])
					{
						SE(22);
						return;		//前に盾が置いてあると動けない
					}
				}

				//ここからは前に盾がなかった時の処理
				if (m_position.x == 80)
				{
					return;
				}
				else if (m_position.x < 80)
				{
					PlayerState = 3;
					Vector3 targetPos = m_position;		//目標地点の設定
					targetPos.x += 20.0f;				//20.0f先が目標
					m_targetPos = targetPos;

					//目標地点から今の場所を引いて80で割った数が速さ
					m_move = (m_targetPos - m_position) / 60.0f;

					AsiotoSE(14);
				}
			}

			if (g_pad[0]->IsTrigger(enButtonDown))					//下ボタンが押されたら
			{
				for (int i = 0; i < 40; i++)
				{
					if (m_position.x == junban->tateposi[i][0] + 10 && m_position.z == junban->tateposi[i][1])
					{
						SE(22);
						return;		//前に盾が置いてあると動けない
					}
				}

				//ここからは前に盾がなかった時の処理
				if (m_position.x == -80)
				{
					return;
				}
				else if (m_position.x > -80)
				{
					PlayerState = 4;
					Vector3 targetPos = m_position;		//目標地点の設定
					targetPos.x -= 20.0f;				//20.0f先が目標
					m_targetPos = targetPos;

					//目標地点から今の場所を引いて割った数が速さ
					m_move = (m_targetPos - m_position) / 60.0f;

					AsiotoSE(14);
				}
			}

			//R2を押すと選択画面に戻れる
			if (g_pad[0]->IsTrigger(enButtonRB2) && nikaiaruki != -1)		
			{
				sentakuState = 0;
				SE(8);
			}
		}

		//２の盾を選択した場合
		if (sentakuState == 2)
		{
			//盾を作り出す
			if (tatearu == 0)
			{
				tatekanri->tatesaku = 1;

				tatearu = 1;
			}

		}

		//３の攻撃を選択したとき
		if (sentakuState == 3)
		{		
			//方向の決定
			if (g_pad[0]->IsTrigger(enButtonUp))
			{
				rotation.SetRotationDegY(90.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 1;
			}
			else if (g_pad[0]->IsTrigger(enButtonDown))
			{
				rotation.SetRotationDegY(270.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 2;
			}
			else if (g_pad[0]->IsTrigger(enButtonLeft))
			{
				rotation.SetRotationDegY(0.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 3;
			}
			else if (g_pad[0]->IsTrigger(enButtonRight))
			{
				rotation.SetRotationDegY(180.0f);
				m_modelRender.SetRotation(rotation);
				SE(9);
				houkou = 4;
			}

			//Aボタンを押して決定
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				Attack();
			}
			
			//R2を押すと選択画面に戻れる
			if (g_pad[0]->IsTrigger(enButtonRB2))		
			{
				sentakuState = 0;
				SE(8);
			}
		}

		if (sentakuState == 4)
		{
			//何もできない
		}
	}
}

void Player::Moving() 
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
	if (PlayerState == 12)
	{
		return;
	}

	m_position += m_move;		//滑らかに移動

	Vector3 diff = m_targetPos - m_position;	//目標場所までのベクトルと距離
	float len = diff.Length();

	if (len < 0.2f && nikaiaruki < 4)		//目標場所までの距離が近づいてきたらステートを０に戻す
	{
		m_position = m_targetPos;
		StopAsioto();

		//敵の陣地に入り込めたら
		if (m_position.x == 80)
		{
			PlayerState = 10;	//勝利
			SE(15);
			return;
		}
		
		//２ターン目からしか壊せない
		if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
		{
			tatekanri->tate[junban->mai - 1]->kowasu = true;

			//画像の差し替え
			tatekanri->tate[junban->mai - 1]->Harikae();
		}
		PlayerState = 0;
		nikaiaruki++;
		sentakuState = 0;
		bariaefe = 0;
		junban->nobiStateR = 1;
		junban->KoutaiState = 3;
	}
	else if (len < 0.2f && nikaiaruki >= 4)		//目標場所までの距離が近づいてきたらステートを０に戻す
	{										//歩くのが２回目の時
		m_position = m_targetPos;
		StopAsioto();

		//敵の陣地に入り込めたら
		if (m_position.x == 80)
		{
			PlayerState = 10;	//勝利
			SE(15);
			return;
		}

		PlayerState = 0;
		nikaiaruki = -1;
		return;
	}
}

void Player::Attack()
{
	if (houkou == 1)
	{
		//前に盾が置いてあるかチェック
		for (int i = 0; i < 30; i++)
		{
			if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;
				PlayerState = 5;
				SE(11);
			}
			else if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//盾は置いてあるが壊せない場合
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x + 10.0f,m_position.y + 25.0f,m_position.z });
				effectEmitter1->Play();
				SE(16, 1.2f);
				bariaefe = 1;//バリアエフェクトは1回しか出ない
			}
			
		}
		return;
	}
	else if (houkou == 2)
	{
		for (int i = 0; i < 30; i++)
		{
			if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;
				PlayerState = 5;
				SE(11);
			}
			else if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//盾は置いてあるが壊せない場合
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x - 10.0f,m_position.y + 25.0f,m_position.z });
				effectEmitter1->Play();
				SE(16, 1.2f);
				bariaefe = 1;//バリアエフェクトは1回しか出ない
			}
			
		}
		return;
	}
	else if (houkou == 3)
	{
		for (int i = 0; i < 30; i++)
		{
			if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;
				PlayerState = 5;
				SE(11);
			}
			else if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//盾は置いてあるが壊せない場合
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x,m_position.y + 25.0f,m_position.z + 10.0f });
				effectEmitter1->Play();
				SE(16, 1.2f);
				bariaefe = 1;//バリアエフェクトは1回しか出ない
			}
			
		}
		return;
	}
	else if (houkou == 4)
	{
		for (int i = 0; i < 30; i++)
		{
			if (m_position.x == junban->tateposi[i][0] && m_position.z -10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == true)
			{
				sentakuState = 4;
				PlayerState = 5;
				SE(11);
			}
			else if (m_position.x == junban->tateposi[i][0] && m_position.z - 10 == junban->tateposi[i][1] && tatekanri->tate[i]->kowasu == false && bariaefe == 0)
			{//盾は置いてあるが壊せない場合
				effectEmitter1 = NewGO<EffectEmitter>(0);
				effectEmitter1->Init(enBaria);
				effectEmitter1->SetScale({ 4.0f,4.0f,4.0f });
				effectEmitter1->SetRotation(rotation);
				effectEmitter1->SetPosition({ m_position.x,m_position.y + 25.0f,m_position.z - 10.0f });
				effectEmitter1->Play();
				SE(16, 1.2f);
				bariaefe = 1;//バリアエフェクトは1回しか出ない
			}
			
		}
		return;
	}
}

void Player::Rotation()
{
	if (PlayerState == 5)
	{
		return;
	}
	else if (PlayerState != 0 && PlayerState != 12)
	{
		//キャラクターの方向を変える。
		rotation.SetRotationYFromDirectionXZ(m_move);

		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(rotation);
	}
}

void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「attack_start」の時
	if (wcscmp(eventName, L"attack_start1") == 0)
	{
		if (houkou == 1)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enSonic);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x + 10.0f,m_position.y +10.0f,m_position.z });
			effectEmitter0->Play();
		}
		if (houkou == 2)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enSonic);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x - 10.0f,m_position.y + 10.0f,m_position.z });
			effectEmitter0->Play();
		}
		if (houkou == 3)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enSonic);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z + 10.0f });
			effectEmitter0->Play();
		}
		if (houkou == 4)
		{
			EffectEmitter* effectEmitter0 = NewGO<EffectEmitter>(0);
			effectEmitter0->Init(enSonic);
			effectEmitter0->SetScale({ 6.0f,6.0f,6.0f });
			effectEmitter0->SetRotation(rotation);
			effectEmitter0->SetPosition({ m_position.x,m_position.y + 10.0f,m_position.z - 10.0f });
			effectEmitter0->Play();
		}
	}
	//キーの名前が「attack_end」の時
	if (wcscmp(eventName, L"attack_end1") == 0)
	{
		if (houkou == 1)
		{
			//前に盾が置いてあるかチェック
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x + 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//盾破壊エフェクトを流す
					DeleteGO(tatekanri->tate[i]);//前に盾が置いてあると壊せる。

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//２ターン目からしか壊せない

						//画像の差し替え
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiaruki++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateR = 1;
					junban->KoutaiState = 3;
				}
			}
			return;
		}
		else if (houkou == 2)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x - 10 == junban->tateposi[i][0] && m_position.z == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//盾破壊エフェクトを流す
					DeleteGO(tatekanri->tate[i]);//前に盾が置いてあると壊せる。

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//２ターン目からしか壊せない

						//画像の差し替え
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiaruki++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateR = 1;
					junban->KoutaiState = 3;
				}
			}
			return;
		}
		else if (houkou == 3)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x == junban->tateposi[i][0] && m_position.z + 10 == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//盾破壊エフェクトを流す
					DeleteGO(tatekanri->tate[i]);//前に盾が置いてあると壊せる。

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//２ターン目からしか壊せない

						//画像の差し替え
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiaruki++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateR = 1;
					junban->KoutaiState = 3;
				}
			}
			return;
		}
		else if (houkou == 4)
		{
			for (int i = 0; i < 30; i++)
			{
				if (m_position.x == junban->tateposi[i][0] && m_position.z - 10 == junban->tateposi[i][1])
				{
					junban->tateposi[i][0] = -500;
					junban->tateposi[i][1] = -500;
					junban->tateposi[i][2] = -500;

					tatekanri->tate[i]->Sinuefe();//盾破壊エフェクトを流す
					DeleteGO(tatekanri->tate[i]);//前に盾が置いてあると壊せる。

					if (junban->mai >= 1 && tatekanri->tate[junban->mai - 1]->kowasu == false)
					{
						tatekanri->tate[junban->mai - 1]->kowasu = true;//２ターン目からしか壊せない

						//画像の差し替え
						tatekanri->tate[junban->mai - 1]->Harikae();
					}
					nikaiaruki++;
					PlayerState = 0;
					sentakuState = 0;
					bariaefe = 0;
					junban->nobiStateR = 1;
					junban->KoutaiState = 3;
				}
			}
			return;
		}
	}

	//キーの名前が「jumatt_start」の時
	if (wcscmp(eventName, L"jumatt_start") == 0)
	{
		//ヒットストップ
		m_modelRender.SetAnimationSpeed(0);
		PlayerState = 9;
		SE(6);
	}

	//キーの名前が「jumatt_stop」の時
	if (wcscmp(eventName, L"jumatt_stop") == 0)
	{
		
	}

	//キーの名前が「jumatt_end」の時
	if (wcscmp(eventName, L"jumatt_end") == 0)
	{
		//リザルト画面に移動
		PlayerState = 11;

		//紙吹雪のエフェクトを再生
		effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(enKamihubuki);
		effectEmitter->SetScale({ 4.0f,4.0f,4.0f });
		effectEmitter->SetRotation(rotation);
		effectEmitter->SetPosition({ m_position.x - 5.0f,m_position.y + 10.0f,m_position.z });
		effectEmitter->Play();
	}
}

void Player::Render(RenderContext& rc)
{
	//描画する。
	m_modelRender.Draw(rc);

	if (PlayerState == 9)
	{
		whitegazou.Draw(rc);
	}
	else if (PlayerState == 11)
	{
		P1WIN.Draw(rc);
	}
}
