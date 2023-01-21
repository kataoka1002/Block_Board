#include "stdafx.h"
#include "Kanri.h"
#include "Title.h"

Kanri::Kanri()
{

}

Kanri::~Kanri()
{

}

void Kanri::Update()
{
	if (game_now == 1)
	{
		NewGO<Title>(0, "title");

		game_now = 0;
	}
}