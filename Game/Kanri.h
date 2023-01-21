#pragma once
class Kanri:public IGameObject
{
public:
	Kanri();
	~Kanri();

	void Update();

	int game_now = 0;
};

