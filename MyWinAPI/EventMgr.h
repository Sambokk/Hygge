#pragma once

struct Event
{
	EVENT_TYPE	eventType;
	DWORD_PTR	lParam;		// Object �� �ּ�
	DWORD_PTR	wParam;		// Group Type
};

class Object;

class EventMgr
{
/// �ɹ� ���� ����
private:
	vector<Event> m_event;		// �̺�Ʈ�� �����ϴ� ����
	vector<Object*> m_remove;	// ���� �����ӿ��� �����ؾ� �� ��ü�� �����ϴ� ����

	int m_eventOrderIndex;

	const wstring BLUE_EVENT_ORDER[32] = {
	
		L"id_Fish_IG",				//0 OBJ_REACT
		L"id_Cloud_IG_005",			//1 OBJ_REACT
		L"id_Seagull002_IG",		//2 OBJ_REACT
		L"id_Wave_IG",				//3 OBJ_REACT
		L"id_Sail_Pattern_IG",		//4 OBJ_REACT
		L"id_Fish_Anchovy_IG",		//5 OBJ_REACT
		L"id_Seaweed_IG",			//6 OBJ_REACT1
		L"id_Fish_Ribbon_eel_IG",	//7 OBJ_REACT1
		L"id_Coral_Singleton002_IG",//8 OBJ_REACT
		L"id_Coral_Singleton001_IG",//9 OBJ_REACT
		L"id_Starfish_IG",			//10 OBJ_REACT
		L"id_Clam_Common002_IG",	//11 OBJ_REACT
		L"id_Clam_Common001_IG",	//12 OBJ_REACT
		L"id_Pearl_Oyster_Closed_IG",//13 OBJ_REACT
		L"id_Pearl_IG",				//14 OBJ_REACT
		L"id_Coral_Leef_IG",		//15 OBJ_REACT
		L"id_Fish_Bluetang_IG",		//16 OBJ_REACT
		L"Cave",					//17 OBJ_REACT1
		L"id_Figurehead_IG",		//18 OBJ_REACT
		L"id_Moon",					//19 OBJ_REACT
		L"id_Moonshine_IG",			//20 OBJ_REACT
		L"id_Witch_IG",				//21 OBJ_REACT1
		L"id_Magic_Potion_IG",		//22 OBJ_REACT
		L"id_Mermaid_Legs_IG"		//23 OBJ_REACT
	};

	bool m_isRedBookClear;
	bool m_isBlueBookClear; 
	bool m_isGreenBookClear;

/// �̱��� ���� ��ũ��
public:
	SINGLE(EventMgr);


/// �ɹ� �Լ� ����
public:
	void update();
	void addEvent(const Event& _event) { m_event.push_back(_event); }

	int getEventOrderIndex() { return m_eventOrderIndex; }

	void nextSceneEventOrder() { m_eventOrderIndex += 1; }
	wstring getBlueEventOrder() { return BLUE_EVENT_ORDER[m_eventOrderIndex]; }
	void setBlueEventOrderInitial() { m_eventOrderIndex = 0; }

	bool getIsRedBookClear() { return m_isRedBookClear; }
	bool getIsBlueBookClear() { return m_isBlueBookClear; }
	bool getIsGreenBookClear() { return m_isGreenBookClear; }

	void SetRedBookClear() { m_isRedBookClear = true; }
	void SetBlueBookClear() { m_isBlueBookClear = true; }
	void SetGreenBookClear() { m_isGreenBookClear = true; }

private:
	void excute(const Event& _event);
};

