#include "stdafx.h"
#include "Syoumetu.h"
#include "Game.h"

Syoumetu::Syoumetu()
{

}

Syoumetu::~Syoumetu()
{
	DeleteGO(effectEmitter);
}

void Syoumetu::Update()
{
	if (effectEmitter == nullptr) {
		return;
	}

	if (isPlay == true && effectEmitter->IsPlay() == false)
	{
		DeleteGO(this);
	}
}

void Syoumetu::PlayEffect(Vector3 position)
{
	//盾が消滅するエフェクト
	effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(enSyoumetu);
	effectEmitter->SetScale({ 6.0f,6.0f,6.0f });
	effectEmitter->SetPosition({ position.x,position.y + 25.0f,position.z });
	effectEmitter->Play();

	isPlay = true;
}

void Syoumetu::PlayEffect_Hanabi(Vector3 position)
{
	//花火エフェクト
	effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(enHanabi);
	effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();

	isPlay = true;
}

void Syoumetu::PlayEffect_Harikae(Vector3 position)
{
	//張替えエフェクト
	effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(enHarikae);
	effectEmitter->SetScale({ 13.0f,13.0f,13.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();

	isPlay = true;
}