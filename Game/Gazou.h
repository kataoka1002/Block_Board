#pragma once
//class Player;
class Gazou : public IGameObject
{
public:
	Gazou();
	~Gazou();
	void Render(RenderContext& rc);	//�`�揈���B
	void Update();

	//Player* player;

	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	//SpriteRender spriteRender3;
};

