#pragma once
class Tate;
class Junban;
class Player;
class Player2;
class Game;
class Tatekanri: public IGameObject
{
public:
	Tatekanri();
	~Tatekanri();

	void Update();
	void Kyanseru();
	

	int tatesaku = 0;
	Tate* tate[30];
	Junban* junban = nullptr;
	Player* player = nullptr;
	Player2* player2 = nullptr;
	Game* game = nullptr;
	EffectEmitter* effectEmitter = nullptr;
};

