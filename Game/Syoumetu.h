#pragma once
class Syoumetu:public IGameObject
{
public:
	Syoumetu();
	~Syoumetu();

	void Update();
	void PlayEffect(Vector3 position);
	void PlayEffect_Hanabi(Vector3 position);
	void PlayEffect_Harikae(Vector3 position);

	EffectEmitter* effectEmitter = nullptr;
	bool isPlay = false;
};

