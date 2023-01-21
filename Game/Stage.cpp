#include "stdafx.h"
#include "Stage.h"

Stage::Stage()
{
	m_modelRender.Init("Assets/modelData/stagenew.tkm");
	m_modelRender.Update();
}

Stage::~Stage()
{

}

void Stage::Render(RenderContext& rc)
{
	//•`‰æ‚·‚éB
	m_modelRender.Draw(rc);
}