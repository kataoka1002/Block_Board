#pragma once
class Gazou2 : public IGameObject
{
public:
	Gazou2();
	~Gazou2();
	void Render(RenderContext& rc);	//�`�揈���B
	void Update();

	SpriteRender spriteRender;
	SpriteRender spriteRender2;
};

