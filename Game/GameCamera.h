#pragma once
class Stage;
class Junban;
class Player;
class Player2;
class BattleStart;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void Update();
	void CameraMove(Vector3 cam,Vector3 tar,int PAD_MODE);

	Vector3 m_moveSpeed;

	Stage* stage = nullptr;
	Junban* junban = nullptr;
	Player* player = nullptr;
	Player2* player2 = nullptr;
	BattleStart* battlestart = nullptr;
};

