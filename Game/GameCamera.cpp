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

	//近平面を設定する。
	g_camera3D->SetNear(1.0f);
	//遠平面を設定する。
	g_camera3D->SetFar(5000.0f);
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//最初の登場シーンのカメラ(ねずみ)
	if (player->PlayerState == 12)
	{
		//注視点を設定する
		Vector3 target = player->m_position;
		target.y += 10.0f;
		//視点を設定する。
		Vector3 cameraPos = { 30.0,25.0,0.0 };
		//視点の設定
		Vector3 pos = cameraPos;
		//メインカメラに注視点と視点を設定する。
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}
	//最初の登場シーンのカメラ(じじい)
	if (player2->PlayerState == 12)
	{
		//注視点を設定する
		Vector3 target = player2->m_position;
		target.y += 10.0f;
		//視点を設定する。
		Vector3 cameraPos = { -30.0,25.0,0.0 };
		//視点の設定
		Vector3 pos = cameraPos;
		//メインカメラに注視点と視点を設定する。
		g_camera3D->SetTarget(target);
		g_camera3D->SetPosition(pos);
	}

	if (junban->KoutaiState == 1 || junban->KoutaiState == 4)
	{
		//注視点を設定する
		Vector3 target=stage->m_position;
		target.x = stage->m_position.x - 30.0f;//注視点は中心より少し手前
		//視点を設定する。
		Vector3 cameraPos = target;
		cameraPos.x -= 140.0f;
		cameraPos.y += 100.0f;
	
		//最後の技のカメラ
		if (player->PlayerState == 9 || player->PlayerState == 10)
		{
			//注視点を設定する
			target = player->m_position;
			target.y = player->m_position.y + 5.0f;
			//視点を設定する。
			cameraPos = target;
			cameraPos.x = +90.0f;
			cameraPos.y = +80.0f;
			cameraPos.z = -50.0f;

			//視点の設定
			Vector3 pos = target + cameraPos;
			//メインカメラに注視点と視点を設定する。
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(pos);

			//カメラの更新
			g_camera3D->Update();
			return;
		}
		//リザルト画面のカメラ
		if (player->PlayerState == 11)
		{
			//注視点を設定する
			target = player->m_position;
			target.y = player->m_position.y + 25.0f;
			//視点を設定する。
			cameraPos = target;
			cameraPos.x = +180.0f;
			cameraPos.y = +60.0f;
			cameraPos.z = player->m_position.z;
			
			//メインカメラに注視点と視点を設定する。
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(cameraPos);

			//カメラの更新
			g_camera3D->Update();
			return;
		}

		if (player->PlayerState >= 0 && player->PlayerState <= 8)
		{
			if (junban->KoutaiState == 1)
			{
				//スティックを使った時の処理
				CameraMove(cameraPos, target, 0);
			}
			else if (junban->KoutaiState == 4)//ターンチェンジ中は初期ポジ
			{
				//視点の設定
				Vector3 pos = target + cameraPos;
				//メインカメラに注視点と視点を設定する。
				g_camera3D->SetTarget(target);
				g_camera3D->SetPosition(pos);

				//カメラの更新
				g_camera3D->Update();
				return;
			}
		}
	}

	if (junban->KoutaiState == 2 || junban->KoutaiState == 3)
	{
		//注視点を設定する
		Vector3 target = stage->m_position;
		target.x = stage->m_position.x + 30.0f;//注視点は中心より少し手前
		//視点を設定する。
		Vector3 cameraPos = target;
		cameraPos.x += 140.0f;
		cameraPos.y += 100.0f;

		//最後の技のカメラ
		if (player2->PlayerState == 9 || player2->PlayerState == 10)
		{
			//注視点を設定する
			target = player2->m_position;
			target.y = player2->m_position.y + 5.0f;
			//視点を設定する。
			cameraPos = target;
			cameraPos.x = -90.0f;
			cameraPos.y = +80.0f;
			cameraPos.z = -50.0f;

			//視点の設定
			Vector3 pos = target + cameraPos;
			//メインカメラに注視点と視点を設定する。
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(pos);

			//カメラの更新
			g_camera3D->Update();
			return;
		}
		//リザルト画面のカメラ
		if (player2->PlayerState == 11)
		{
			//注視点を設定する
			target = player2->m_position;
			target.y = player2->m_position.y + 25.0f;
			//視点を設定する。
			cameraPos = target;
			cameraPos.x = -180.0f;
			cameraPos.y = +60.0f;
			cameraPos.z = player2->m_position.z;

			//メインカメラに注視点と視点を設定する。
			g_camera3D->SetTarget(target);
			g_camera3D->SetPosition(cameraPos);

			//カメラの更新
			g_camera3D->Update();
			return;
		}

		if (player2->PlayerState >= 0 && player2->PlayerState <= 8)
		{
			if (junban->KoutaiState == 2)
			{
				//スティックを使った時の処理
				CameraMove(cameraPos, target, player2->PAD_MODE);
			}
			else if (junban->KoutaiState == 3)//ターンチェンジ中は初期ポジ
			{
				//視点の設定
				Vector3 pos = target + cameraPos;
				//メインカメラに注視点と視点を設定する。
				g_camera3D->SetTarget(target);
				g_camera3D->SetPosition(pos);

				//カメラの更新
				g_camera3D->Update();
				return;
			}
		}
	}
}

void GameCamera::CameraMove(Vector3 cam, Vector3 tar,int PAD_MODE)
{
	Vector3 cameraPosOld = cam;
	//スティックの入力を使ってカメラを回す。
	float x = g_pad[PAD_MODE]->GetRStickXF();
	float y = g_pad[PAD_MODE]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRotY;
	qRotY.SetRotationDeg(Vector3::AxisY, 100.0f * x);
	qRotY.Apply(cam);
	//X軸周りの回転
	Vector3 qRotX;
	qRotX.Cross(Vector3::AxisY, cam);
	qRotX.Normalize();
	qRotY.SetRotationDeg(qRotX, 30.0f * y);
	qRotY.Apply(cam);

	//カメラの回転の上限をチェックする。
	Vector3 toPosDer = cam;
	toPosDer.Normalize();
	if (toPosDer.y < -90.0f)
	{
		//上向きすぎ
		cam = cameraPosOld;
	}
	else if (toPosDer.y > 110.0f)
	{
		//下向きすぎ
		cam = cameraPosOld;
	}

	//視点の設定
	Vector3 pos = tar + cam;
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(tar);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();
}