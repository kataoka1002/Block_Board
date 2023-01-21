#pragma once
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Render(RenderContext& rc);	//•`‰æˆ—B

	ModelRender m_modelRender;
	Vector3 m_position;
};

