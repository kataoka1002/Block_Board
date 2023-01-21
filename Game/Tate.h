#pragma once
class Junban;
class Player;
class Player2;
class Tatekanri;

class Tate : public IGameObject
{
public:
	Tate();
	~Tate();
	void Render(RenderContext& rc);	//•`‰æˆ—B
	void Update();
	void SetidouState(int state) {
		idouState = state;
	}
	int GetidouState() {
		return idouState;
	}
	

	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void Sinuefe();
	void Harikae();
	
	int tatemawa = 0;		
	bool kowasu = false;
	bool Gameend = false;

	ModelRender* m_modelRender = nullptr;
	Vector3 m_position;
	Quaternion rot;

	Junban* junban = nullptr;
	Player* player = nullptr;
	Player2* player2 = nullptr;
	Tatekanri* tatekanri = nullptr;
private:
	int idouState = 1;
	void SE(int bango, float volume = 1.0f);
};

