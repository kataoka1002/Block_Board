#pragma once
class Fade;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);
	void YaziMove();
	bool Start();
	//void YaziRot();
	void SE(int bango);

	int selectState = 1;
	int yazimove = 1;
	//int yazirot = 1;
	float L = 590.0, R = -585.0, U = -290, D = 280;
	int PadState = 0;

	Vector3 yaziposi = { -150.0f,100.0f,0.0f };
	//Vector3 rotposi = { 0.0f,0.0f,0.0f };

	SpriteRender s_title;
	SpriteRender s_setumei;
	SpriteRender s_asobikata;
	SpriteRender s_usublack;
	SpriteRender s_yazirusi;
	SpriteRender s_padmode;
	/*SpriteRender s_yazirotL;
	SpriteRender s_yazirotR;
	SpriteRender s_yazirotU;
	SpriteRender s_yazirotD;*/
	bool m_isWaitFadeout = false;	//

	Fade* m_fade = nullptr;
	SoundSource* soundSource = nullptr;
};

