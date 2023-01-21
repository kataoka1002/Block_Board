#include "stdafx.h"
#include "Gauge.h"
#include "Player.h"
#include "Player2.h"

Gauge::Gauge()
{
	//ÉQÅ[ÉWÇÃíÜêgÇÃçÏê¨
	gauge1_1.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge1_1.SetPosition({ -820.0f,470.0f,0.0f });
	gauge1_2.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge1_2.SetPosition({ -640.0f,470.0f,0.0f });
	gauge1_3.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge1_3.SetPosition({ -460.0f,470.0f,0.0f });
	gauge1_4.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge1_4.SetPosition({ -280.0f,470.0f,0.0f });
	gauge2_1.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge2_1.SetPosition({ 820.0f,470.0f,0.0f });
	gauge2_2.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge2_2.SetPosition({ 640.0f,470.0f,0.0f });
	gauge2_3.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge2_3.SetPosition({ 460.0f,470.0f,0.0f });
	gauge2_4.Init("Assets/modelData/gauge.DDS", 1000.0f, 1000.0f);
	gauge2_4.SetPosition({ 280.0f,470.0f,0.0f });
	gaugewaku1_1.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku1_1.SetPosition({ -820.0f,470.0f,0.0f });
	gaugewaku1_1.SetScale(wakuscale);
	gaugewaku1_1.Update();
	gaugewaku1_2.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku1_2.SetPosition({ -640.0f,470.0f,0.0f });
	gaugewaku1_2.SetScale(wakuscale);
	gaugewaku1_2.Update();
	gaugewaku1_3.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku1_3.SetPosition({ -460.0f,470.0f,0.0f });
	gaugewaku1_3.SetScale(wakuscale);
	gaugewaku1_3.Update();
	gaugewaku1_4.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku1_4.SetPosition({ -280.0f,470.0f,0.0f });
	gaugewaku1_4.SetScale(wakuscale);
	gaugewaku1_4.Update();
	gaugewaku2_1.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku2_1.SetPosition({ 820.0f,470.0f,0.0f });
	gaugewaku2_1.SetScale(wakuscale);
	gaugewaku2_1.Update();
	gaugewaku2_2.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku2_2.SetPosition({ 640.0f,470.0f,0.0f });
	gaugewaku2_2.SetScale(wakuscale);
	gaugewaku2_2.Update();
	gaugewaku2_3.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku2_3.SetPosition({ 460.0f,470.0f,0.0f });
	gaugewaku2_3.SetScale(wakuscale);
	gaugewaku2_3.Update();
	gaugewaku2_4.Init("Assets/modelData/gaugewaku.DDS", 1000.0f, 1000.0f);
	gaugewaku2_4.SetPosition({ 280.0f,470.0f,0.0f });
	gaugewaku2_4.SetScale(wakuscale);
	gaugewaku2_4.Update();

	player = FindGO<Player>("player");
	player2 = FindGO<Player2>("player2");
}

Gauge::~Gauge()
{

}

void Gauge::Update()
{
	//ëÂÇ´Ç≥Çê›íËÇ∑ÇÈ
	gauge1_1.SetScale(scale1_1);
	gauge1_2.SetScale(scale1_2);
	gauge1_3.SetScale(scale1_3);
	gauge1_4.SetScale(scale1_4);
	gauge2_1.SetScale(scale2_1);
	gauge2_2.SetScale(scale2_2);
	gauge2_3.SetScale(scale2_3);
	gauge2_4.SetScale(scale2_4);

	//ÉlÉYÉ~ÇÃèÍçá
	if (player->nikaiaruki == 0 && saizu1 == 0)
	{
		//ÉXÉPÅ[ÉãÇÕÇO(å©Ç¶Ç»Ç¢)
		scale1_1 = { 0.0f,0.0f,1.0f };
		scale1_2 = { 0.0f,0.0f,1.0f };
		scale1_3 = { 0.0f,0.0f,1.0f };
		scale1_4 = { 0.0f,0.0f,1.0f };
	}
	else if (player->nikaiaruki == 1 && saizu1 == 0)
	{
		//ÉQÅ[ÉWÇ1Ç¬ÇæÇØå©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale1_1.x += 0.05;
		scale1_1.y += 0.05;
		if (scale1_1.x >= 0.5)
		{
			scale1_1 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player->nikaiaruki == 2 && saizu1 == 0)
	{
		//ÉQÅ[ÉWÇ2Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale1_2.x += 0.05;
		scale1_2.y += 0.05;
		if (scale1_2.x >= 0.5)
		{
			scale1_2 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player->nikaiaruki == 3 && saizu1 == 0)
	{
		//ÉQÅ[ÉWÇ3Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale1_3.x += 0.05;
		scale1_3.y += 0.05;
		if (scale1_3.x >= 0.5)
		{
			scale1_3 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player->nikaiaruki == 4 && saizu1 == 0)
	{
		//ÉQÅ[ÉWÇ4Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale1_4.x += 0.05;
		scale1_4.y += 0.05;
		if (scale1_4.x >= 0.5)
		{
			scale1_4 = { 0.5f,0.5f,0.0f };
			saizu1 = 1;//êUìÆÇäJénÇ≥ÇπÇÈ
		}
	}

	//ñÍÇÃèÍçá
	if (player2->nikaiwalk == 0 && saizu2 == 0)
	{
		//ÉXÉPÅ[ÉãÇÕÇO(å©Ç¶Ç»Ç¢)
		scale2_1 = { 0.0f,0.0f,1.0f };
		scale2_2 = { 0.0f,0.0f,1.0f };
		scale2_3 = { 0.0f,0.0f,1.0f };
		scale2_4 = { 0.0f,0.0f,1.0f };
	}
	else if (player2->nikaiwalk == 1 && saizu2 == 0)
	{
		//ÉQÅ[ÉWÇ1Ç¬ÇæÇØå©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale2_1.x += 0.05;
		scale2_1.y += 0.05;
		if (scale2_1.x >= 0.5)
		{
			scale2_1 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player2->nikaiwalk == 2 && saizu2 == 0)
	{
		//ÉQÅ[ÉWÇ2Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale2_2.x += 0.05;
		scale2_2.y += 0.05;
		if (scale2_2.x >= 0.5)
		{
			scale2_2 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player2->nikaiwalk == 3 && saizu2 == 0)
	{
		//ÉQÅ[ÉWÇ3Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale2_3.x += 0.05;
		scale2_3.y += 0.05;
		if (scale2_3.x >= 0.5)
		{
			scale2_3 = { 0.5f,0.5f,0.0f };
		}
	}
	else if (player2->nikaiwalk == 4 && saizu2 == 0)
	{
		//ÉQÅ[ÉWÇ4Ç¬å©Ç¶ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		scale2_4.x += 0.05;
		scale2_4.y += 0.05;

		if (scale2_4.x >= 0.5)
		{
			scale2_4 = { 0.5f,0.5f,0.0f };
			saizu2 = 1;//êUìÆÇäJénÇ≥ÇπÇÈ
		}
	}


	//ÇÀÇ∏Ç›ÇÃêUìÆÇÃèàóù
	if (player->nikaiaruki >= 4 || player->nikaiaruki == -1)
	{
		if (saizu1 == 1)//ägëÂ
		{
			scale1_1.x += 0.05;
			scale1_1.y += 0.05;
			scale1_2.x += 0.05;
			scale1_2.y += 0.05;
			scale1_3.x += 0.05;
			scale1_3.y += 0.05;
			scale1_4.x += 0.05;
			scale1_4.y += 0.05;

			if (scale1_1.x >= 0.7)
			{
				saizu1 = 2;
			}
		}
		else if (saizu1 == 2)//èkè¨
		{
			scale1_1.x -= 0.01;
			scale1_1.y -= 0.01;
			scale1_2.x -= 0.01;
			scale1_2.y -= 0.01;
			scale1_3.x -= 0.01;
			scale1_3.y -= 0.01;
			scale1_4.x -= 0.01;
			scale1_4.y -= 0.01;
			if (scale1_1.x <= 0.5)
			{
				saizu1 = 1;
			}
		}
	}
	//ìÒâÒï‡Ç´Çè¡îÔÇµÇΩÇÁÉQÅ[ÉWÇè¡ÇµÇƒêUìÆÇ‡è¡Ç∑
	if (saizu1 == 1 || saizu1 == 2)
	{
		if (player->nikaiaruki == 0)
		{
			saizu1 = 0;

			//ÉVÉÉÉLÅ[ÉìÇ™ñ¬ÇÈÇÊÇ§Ç…Ç∑ÇÈ
			player->syaki = 0;
		}
	}

	//ñÍÇÃêUìÆÇÃèàóù
	if (player2->nikaiwalk >= 4 || player2->nikaiwalk == -1)
	{
		if(saizu2 == 1)//ägëÂ
		{
			scale2_1.x += 0.05;
			scale2_1.y += 0.05;
			scale2_2.x += 0.05;
			scale2_2.y += 0.05;
			scale2_3.x += 0.05;
			scale2_3.y += 0.05;
			scale2_4.x += 0.05;
			scale2_4.y += 0.05;
			
			if (scale2_1.x >= 0.7)
			{
				saizu2 = 2;
			}
		}
		else if (saizu2 == 2)//èkè¨
		{
			scale2_1.x -= 0.01;
			scale2_1.y -= 0.01;
			scale2_2.x -= 0.01;
			scale2_2.y -= 0.01;
			scale2_3.x -= 0.01;
			scale2_3.y -= 0.01;
			scale2_4.x -= 0.01;
			scale2_4.y -= 0.01;
			if (scale2_1.x <= 0.5)
			{
				saizu2 = 1;
			}
		}
	}
	//ìÒâÒï‡Ç´Çè¡îÔÇµÇΩÇÁÉQÅ[ÉWÇè¡ÇµÇƒêUìÆÇ‡è¡Ç∑
	if (saizu2 == 1 || saizu2 == 2)
	{
		if (player2->nikaiwalk == 0)
		{
			saizu2 = 0;

			//ÉVÉÉÉLÅ[ÉìÇ™ñ¬ÇÈÇÊÇ§Ç…Ç∑ÇÈ
			player2->syaki = 0;
		}
	}

	gauge1_1.Update();
	gauge1_2.Update();
	gauge1_3.Update();
	gauge1_4.Update();
	gauge2_1.Update();
	gauge2_2.Update();
	gauge2_3.Update();
	gauge2_4.Update();
}

void Gauge::Render(RenderContext& rc)
{
	//ìoèÍÉVÅ[ÉìÇ∆ÉäÉUÉãÉgâÊñ Ç≈ÇÕï\é¶ÇµÇ»Ç¢ÅB
	if (player->PlayerState != 11 && player2->PlayerState != 11 && player->PlayerState != 12 && player2->PlayerState != 12)
	{
		//ògÇÇ∏Ç¡Ç∆ï\é¶
		gaugewaku1_1.Draw(rc);
		gaugewaku1_2.Draw(rc);
		gaugewaku1_3.Draw(rc);
		gaugewaku1_4.Draw(rc);
		gaugewaku2_1.Draw(rc);
		gaugewaku2_2.Draw(rc);
		gaugewaku2_3.Draw(rc);
		gaugewaku2_4.Draw(rc);
		//ÉQÅ[ÉWÇ‡Ç∏Ç¡Ç∆ï\é¶
		gauge1_1.Draw(rc);
		gauge1_2.Draw(rc);
		gauge1_3.Draw(rc);
		gauge1_4.Draw(rc);
		gauge2_1.Draw(rc);
		gauge2_2.Draw(rc);
		gauge2_3.Draw(rc);
		gauge2_4.Draw(rc);
	}
}