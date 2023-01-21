#include "stdafx.h"
#include "Gazou2.h"

Gazou2::Gazou2()
{
	//‚‰ñ“]‚Ìà–¾‚Ì‰æ‘œì¬
	spriteRender.Init("Assets/modelData/kaiten.DDS", 75.0f, 75.0f);
	spriteRender.SetPosition({ 200.0f, -350.0f, 0.0f });
	spriteRender.SetScale({ 2.4f,2.4f,2.4f });

	spriteRender2.Init("Assets/modelData/tatebasyo.DDS", 75.0f, 75.0f);
	spriteRender2.SetPosition({ -200.0f, -350.0f, 0.0f });
	spriteRender2.SetScale({ 2.4f,2.4f,2.4f });
}

Gazou2::~Gazou2()
{

}

void Gazou2::Update()
{
	spriteRender.Update();
	spriteRender2.Update();
}

void Gazou2::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);
}