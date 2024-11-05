#include "pch.h"
#include "Scene_Blue.h"

// 오브젝트
#include "Object.h"
#include "Item.h"

#include "Core.h"
#include "Book.h"
#include "KeyMgr.h"

#include "CameraDownButton.h"
#include "CameraUpButton.h"
#include "BlueBG.h"
#include "Fade_InOut.h"
#include "Inventory.h"
#include "BlueBG_BitBlt.h"
#include "Item.h"
#include "MouseBubble.h"
#include "UI.h"
#include "Moon.h"
#include "ItemOnlyCollider.h"

//매니저
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "MouseMgr.h"
#include "EventMgr.h"

Scene_Blue::Scene_Blue()
{

}

Scene_Blue::~Scene_Blue()
{

}

void Scene_Blue::update(KeyMgr* _keyManager)
{
	Scene::update(_keyManager);

	// ESC 키 입력
	if (_keyManager->getKeyState(KEY::ESC) == KEY_STATE::DOWN)
	{
		changeScene((SCENE_TYPE::TITLE)); // SceneMgr 에서 가져온 함수
	}

	/// 벡터 배열 안 오브젝트의 함수를 실행 시킵니다
	// TODO : 이제 이벤트 조껀에 맞는 오브젝트만 실행시키기
	if (_keyManager->getKeyState(KEY::OEM_3) == KEY_STATE::DOWN)
	{
		// 특정 그룹 타입에 해당하는 객체들에 대해 함수 실행
		executeFunctionOnGroupObjects(GROUP_TYPE::OBJ_REACT, [](Object* object)
			{
				// 오브젝트에 대해 실행할 동작 정의
				object->onMouseClicked();
			});
		executeFunctionOnGroupObjects(GROUP_TYPE::OBJ_REACT1, [](Object* object)
			{
				// 오브젝트에 대해 실행할 동작 정의
				object->onMouseClicked();
			});
	}

	// 마우스 입력
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::DOWN)
	{
		Object* bubble = new(MouseBubble);
		Vector2 pos = Core::GetInstance()->getCursorPosC();
		pos.x -= 25.f; pos.y -= 25.f;
		bubble->setPosition(pos);
		instantiate(bubble, GROUP_TYPE::UI_BG);
	}
}

void Scene_Blue::exit()
{
	SoundMgr::GetInstance()->stopBGM();
	deleteAll(); // 모든 오브젝트를 지운다 (부모에게 상속 받은 함수)


	SoundMgr::GetInstance()->setBlueNight(false);
	SoundMgr::GetInstance()->setBlueUpSide(true);
	Core::GetInstance()->setCameraOffset(0);
	MouseMgr::GetInstance()->setOffsetNormalState();
	EventMgr::GetInstance()->setBlueEventOrderInitial();
}

void Scene_Blue::enter()
{
	SoundMgr::GetInstance()->playBGM((UINT)SOUND_BGM::DAY_SKY); // 배경음

	//우측 UI 화면
	Object* rightUIBG = new UI(L"rightUI_BG", Vector2(1050.f, 0.f), L"mrightUI_BG", L"texture\\ui_side_right.png", 0);
	addObject(rightUIBG, GROUP_TYPE::UI_BG);

	Object* settingButton = new UI(L"settingButton", Vector2(1158.f, 31.f), L"settingButton", L"texture\\ui_setting3.png", 0);
	addObject(settingButton, GROUP_TYPE::UI);

	//인벤토리
	Inventory* inventory = new Inventory();
	addObject(inventory, GROUP_TYPE::INVENTORY_BG);

	//좌측 인벤토리 아이템 실루엣
	Object* silhouette = new UI(L"silhouette", Vector2 (-10.f, 30.f ), L"silhouette", L"texture\\Total_OG.png", 0);
	addObject(silhouette, GROUP_TYPE::INVENTORY_BG);


	Object* f = new Fade_InOut(true); // 화면 전환
	addObject(f, GROUP_TYPE::UI_SETTING_BG);

	Object* switch_button_down = new CameraDownButton; // 카메라 다운 버튼
	switch_button_down->initialize(Vector2(640.f, 640.f), L"CameraDownButton", L"texture\\switch_button_down.png");
	addObject(switch_button_down, GROUP_TYPE::OBJ_REACT);

	Object* switch_button_up = new CameraUpButton; // 카메라 업 버튼
	switch_button_up->initialize(Vector2(640.f, 760.f), L"CameraUpButton", L"texture\\switch_button_up.png");
	addObject(switch_button_up, GROUP_TYPE::OBJ_REACT);

	Object* BO_sky_day = new BlueBG; // 배경
	BO_sky_day->initialize(Vector2(100.f, 0.f), L"BO_sky_day", L"texture\\BO_sky_day.bmp");
	addObject(BO_sky_day, GROUP_TYPE::OBJ_BG);

	Object* id_Seagull002_IG = new Item(L"id_Seagull002_IG", L"id_Seagull002_IG", Vector2(562.f, 65.f), Vector2(-10.f, 207.f),
		L"texture\\id_Seagull002_IG.png", "content/texture/id_Seagull002_IG.png"
		, L"texture\\id_Seagull002_OG.png", "content/texture/id_Seagull002_OG.png", 0.1f);
	addObject(id_Seagull002_IG, GROUP_TYPE::OBJ_REACT); // 갈매기 002

	Object* id_Cloud_IG_005 = new Item(L"id_Cloud_IG_005", L"id_Cloud_IG_005", Vector2(390.f, 31.f), Vector2(8.f, 130.f),
		L"texture\\id_Cloud_IG_005.png", "content/texture/id_Cloud_IG_005.png"
		, L"texture\\id_Cloud_OG.png", "content/texture/id_Cloud_OG.png", 0.2f);
	addObject(id_Cloud_IG_005, GROUP_TYPE::OBJ_REACT); // 구름 005

	Object* BO_cloud004_day = new BlueBG; // 구름 004
	BO_cloud004_day->initialize(Vector2(765.f, 23.f), L"BO_cloud004_day", L"texture\\BO_cloud004_day.png");
	BO_cloud004_day->setDepth(0.05f);
	addObject(BO_cloud004_day, GROUP_TYPE::OBJ_BG);

	Object* BO_cloud003_day = new BlueBG; // 구름 003
	BO_cloud003_day->initialize(Vector2(0.f, 65.f), L"BO_cloud003_day", L"texture\\BO_cloud003_day.png");
	BO_cloud003_day->setDepth(0.08f);
	addObject(BO_cloud003_day, GROUP_TYPE::OBJ_BG);

	Object* BO_cloud002_day = new BlueBG; // 구름 002
	BO_cloud002_day->initialize(Vector2(587.f, 175.f), L"BO_cloud002_day", L"texture\\BO_cloud002_day.png");
	BO_cloud002_day->setDepth(0.2f);
	addObject(BO_cloud002_day, GROUP_TYPE::OBJ_BG);

	Object* BO_cloud001_day = new BlueBG; // 구름 001
	BO_cloud001_day->initialize(Vector2(-178.f, 179.f), L"BO_cloud001_day", L"texture\\BO_cloud001_day.png");
	BO_cloud001_day->setDepth(0.15f);
	addObject(BO_cloud001_day, GROUP_TYPE::OBJ_BG);


	///수정 중인 곳
	//Object* BO_sky_day003 = new BlueBG; // 낮바다 002
	//BO_sky_day003->initialize(Vector2(0.f, 500.f), L"BO_sky_day003", L"texture\\Background_Ocean_Day_003.png");
	//addObject(BO_sky_day003, GROUP_TYPE::OBJ_BG);

	Object* BO_sky_day002 = new BlueBG; // 낮바다002
	BO_sky_day002->initialize(Vector2(0.f, 430.f), L"BO_sky_day002", L"texture\\Background_Ocean_Day_002.png");
	BO_sky_day002->setDepth(0.03f);
	addObject(BO_sky_day002, GROUP_TYPE::OBJ_BG);

	Object* BO_sky_day003 = new BlueBG; // 낮바다003
	BO_sky_day003->initialize(Vector2(0.f, 490.f), L"BO_sky_day003", L"texture\\Background_Ocean_Day_003.png");
	BO_sky_day003->setDepth(0.15f);
	addObject(BO_sky_day003, GROUP_TYPE::OBJ_BG);

	Object* id_Reef_IG = new BlueBG;
	id_Reef_IG->initialize(Vector2(903.f, 490.f), L"id_Reef_IG", L"texture\\id_Reef_IG.png");
	id_Reef_IG->setDepth(0.10f); ///이 밑은 전부 값 조정 필요!
	addObject(id_Reef_IG, GROUP_TYPE::OBJ_REACT1);

	Object* BO_ocean_day001 = new BlueBG; // 낮바다001
	BO_ocean_day001->initialize(Vector2(0.f, 520.f), L"BO_ocean_day001", L"texture\\Background_Ocean_Day_001.png");
	BO_ocean_day001->setDepth(0.4f);
	addObject(BO_ocean_day001, GROUP_TYPE::OBJ_BG);

	
	///여기부터 바다 부분
	Object* BO_fishes = new BlueBG; // 멸치 무리
	BO_fishes->initialize(Vector2(445.f, 817.f), L"BO_fishes", L"texture\\BO_fishes.png");
	BO_fishes->setDepth(0.15f);
	addObject(BO_fishes, GROUP_TYPE::OBJ_REACT1);

	Object* id_Fish_Anchovy_IG = new Item(L"id_Fish_Anchovy_IG", L"id_Fish_Anchovy_IG", Vector2(708.f, 942.f), Vector2(38.f, 536.f),
		L"texture\\id_Fish_Anchovy_IG.png", "content/texture/id_Fish_Anchovy_IG.png"
		, L"texture\\id_Fish_Anchovy_OG.png", "content/texture/id_Fish_Anchovy_OG.png", 0.16f);
	addObject(id_Fish_Anchovy_IG, GROUP_TYPE::OBJ_REACT); // 멸치

	Object* BO_seaweed003 = new BlueBG;  //해초 003 : 오른쪽  줄기
	BO_seaweed003->initialize(Vector2(643.f, 718.f), L"BO_seaweed003", L"texture\\BO_seaweed003.png");
	BO_seaweed003->setDepth(0.2f);
	addObject(BO_seaweed003, GROUP_TYPE::OBJ_REACT1);

	Object* BO_ground003 = new BlueBG; // 바닥 003
	BO_ground003->initialize(Vector2(0.f, 1270.f), L"BO_ground003", L"texture\\BO_ground003.png");
	BO_ground003->setDepth(0.2f);
	addObject(BO_ground003, GROUP_TYPE::OBJ_REACT1);

	Object* BO_ocean_stone003 = new BlueBG; //맨 오른쪽 스톤 003
	BO_ocean_stone003->initialize(Vector2(832.f, 795.f), L"BO_ocean_stone003", L"texture\\BO_ocean_stone003.png");
	BO_ocean_stone003->setDepth(0.25f);
	addObject(BO_ocean_stone003, GROUP_TYPE::OBJ_REACT1);


	/// 클릭을 여러 번 하면 없어지는 오브젝트입니다.
	Object* id_Pearl_Oyster_Closed001_IG = new Moon(
		L"id_Pearl_Oyster_Closed_IG", L"id_Pearl_Oyster_Closed_IG"
		, Vector2(501.f, 1167.f)
		, L"texture\\id_Pearl_Oyster_Closed001_IG.png", "content/texture/id_Pearl_Oyster_Closed001_IG.png"
	
		// 이 아이템이 생성하는 아이템
		, L"id_Pearl_Oyster_Opened001_IG", L"id_Pearl_Oyster_Opened001_IG", Vector2(501.f, 440.f), Vector2(501.f, 440.f)//, Vector2(551.f, 1147.f), Vector2(551.f, 1147.f)
		, L"texture\\id_Pearl_Oyster_Opened001_IG.png", "content/texture/id_Pearl_Oyster_Opened001_IG.png"	
		, L"texture\\id_Pearl_Oyster_Opened001_IG.png", "content/texture/id_Pearl_Oyster_Opened001_IG.png"
		, 0.25f, 3, true);
	addObject(id_Pearl_Oyster_Closed001_IG, GROUP_TYPE::OBJ_REACT); // 진주 조개 C
	
	/// 이거는 위의 오브젝트가 사라지면 나타나는 오브젝트입니다.
	//Object* id_Pearl_Oyster_Opened001_IG = new BlueBG; //진주 조개 O
	//id_Pearl_Oyster_Opened001_IG->initialize(Vector2(551.f, 1147.f), L"id_Pearl_Oyster_Opened001_IG", L"texture\\id_Pearl_Oyster_Opened001_IG.png");
	//id_Pearl_Oyster_Opened001_IG->setDepth(0.25f);
	//addObject(id_Pearl_Oyster_Opened001_IG, GROUP_TYPE::OBJ_REACT1);

	//Object* id_Pearl_IG = new Item(L"id_Pearl_IG", L"id_Pearl_IG", Vector2(604.f, 1216.f), Vector2(28.f, 1640.f),
	//	L"texture\\id_Pearl_IG.png", "content/texture/id_Pearl_IG.png"
	//	, L"texture\\id_Pearl_OG.png", "content/texture/id_Pearl_OG.png", 0.25);
	//addObject(id_Pearl_IG, GROUP_TYPE::OBJ_REACT); // 진주
	
	Object* id_Fish_Ribbon_eel_IG = new Item(L"id_Fish_Ribbon_eel_IG", L"id_Fish_Ribbon_eel_IG", Vector2(225.f, 1024.f), Vector2(7.f, 812.f),
		L"texture\\id_Fish_Ribbon_eel_IG.png", "content/texture/id_Fish_Ribbon_eel_IG.png"
		, L"texture\\id_Fish_Ribbon_eel_OG.png", "content/texture/id_Fish_Ribbon_eel_OG.png", 0.25);
	addObject(id_Fish_Ribbon_eel_IG, GROUP_TYPE::OBJ_REACT1); // 리본 장어

	Object* id_Seaweed_IG = new Item(L"id_Seaweed_IG", L"id_Seaweed_IG", Vector2(248.f, 1051.f), Vector2(13.f, 648.f),
		L"texture\\id_Seaweed_IG.png", "content/texture/id_Seaweed_IG.png"
		, L"texture\\id_Seaweed_OG.png", "content/texture/id_Seaweed_OG.png", 0.35f);
	addObject(id_Seaweed_IG, GROUP_TYPE::OBJ_REACT1); // 해초 다발

	/// 이 오브젝트는 클릭되면 밤이 됩니다.
	Object* Cave = new ItemOnlyCollider(L"Cave", L"Cave", Vector2(249.f, 1188.f)
		, L"texture\\Cave.png", "content/texture/Cave.png", 0.35f);
	addObject(Cave, GROUP_TYPE::OBJ_REACT1);

	/// 동굴에 달조각을 드래그하면 마녀가 등장합니다. 


	/// 말풍선 3에 오브젝트 4개를 드래그하면 마법 포션이 나타납니다.
	//Object* id_Magic_Potion_IG = new Item(L"id_Magic_Potion_IG", L"id_Magic_Potion_IG", Vector2(494.f, 1079.f), Vector2(28.f, 2267.f),
	//	L"texture\\id_Magic_Potion_IG.png", "content/texture/id_Magic_Potion_IG.png"
	//	, L"texture\\id_Magic_Potion_OG.png", "content/texture/id_Magic_Potion_OG.png", 0.38);
	//addObject(id_Magic_Potion_IG, GROUP_TYPE::OBJ_REACT); // 마법 포션
	

	Object* id_Coral_Singleton002_IG = new Item(L"id_Coral_Singleton002_IG", L"id_Coral_Singleton002_IG"
		, Vector2(347.f, 1225.f), Vector2(7.f, 989.f)
		, L"texture\\id_Coral_Singleton002_IG.png", "content/texture/id_Coral_Singleton002_IG.png"
		, L"texture\\id_Coral_Singleton_002_OG.png", "content/texture/id_Coral_Singleton_002_OG.png", 0.4f);
	addObject(id_Coral_Singleton002_IG, GROUP_TYPE::OBJ_REACT); // 산호 002


	Object* BO_ground002 = new BlueBG; // 바닥2
	BO_ground002->initialize(Vector2(380.f, 1250.f), L"BO_ground002", L"texture\\BO_ground002.png");
	BO_ground002->setDepth(0.65f);
	addObject(BO_ground002, GROUP_TYPE::OBJ_REACT1);

	Object* BO_ocean_stone002 = new BlueBG; // 오른쪽 스톤 002
	BO_ocean_stone002->initialize(Vector2(657.f, 895.f), L"BO_ocean_stone002", L"texture\\BO_ocean_stone_002.png");
	BO_ocean_stone002->setDepth(0.65f);
	addObject(BO_ocean_stone002, GROUP_TYPE::OBJ_REACT);

	Object* id_Starfish_IG = new Item(L"id_Starfish_IG", L"id_Starfish_IG", Vector2(782.f, 1089.f), Vector2(43.f, 1343.f),
		L"texture\\id_Starfish_IG.png", "content/texture/id_Starfish_IG.png"
		, L"texture\\id_Starfish_OG.png", "content/texture/id_Starfish_OG.png", 0.65f);
	addObject(id_Starfish_IG, GROUP_TYPE::OBJ_REACT); // 불가사리

	Object* id_Fish_Bluetang_IG = new Item(L"id_Fish_Bluetang_IG", L"id_Fish_Bluetang_IG", Vector2(765.f, 1178.f), Vector2(-8.f, 1896.f),
		L"texture\\id_Fish_Bluetang_IG.png", "content/texture/id_Fish_Bluetang_IG.png"
		, L"texture\\id_Fish_Bluetang_OG.png", "content/texture/id_Fish_Bluetang_OG.png", 0.55f);
	addObject(id_Fish_Bluetang_IG, GROUP_TYPE::OBJ_REACT); // 블루탱


	///산호1과 2를 획득하면 인벤토리 창에는 체크 표시 후, 이 이미지(id_Coral_Leef_IG)를 없앤 후, 새 이미지(id_Coral_Leef_OG)를 배치합니다.
	Object* id_Coral_Leef_IG = new Item(L"id_Coral_Leef_IG_BG", L"id_Coral_Leef_IG_BG"
		, Vector2(813.f, 1172.f), Vector2(9.f, 1773.f + 500.)
		, L"texture\\id_Coral_Leef_IG_BG.png", "content/texture/id_Coral_Leef_IG_BG.png"
		, L"texture\\id_Coral_Leef_OG.png", "content/texture/id_Coral_Leef_OG.png", 0.65f);
	addObject(id_Coral_Leef_IG, GROUP_TYPE::OBJ_REACT); // 산호군락

	Object* id_Coral_Singleton001_IG = new Item(L"id_Coral_Singleton001_IG", L"id_Coral_Singleton001_IG"
		, Vector2(888.f, 1222.f), Vector2(7.f, 1166.f),
		L"texture\\id_Coral_Singleton001_IG.png", "content/texture/id_Coral_Singleton001_IG.png"
		, L"texture\\id_Coral_Singleton_001_OG.png", "content/texture/id_Coral_Singleton_001_OG.png", 0.65f);
	addObject(id_Coral_Singleton001_IG, GROUP_TYPE::OBJ_REACT); // 산호 001
	


	///산호 군락의 원래 위치입니다. 테스트 하기 위해 위치 옮겨 둠.

	Object* id_Clam_Common001_IG = new Item(L"id_Clam_Common001_IG", L"id_Clam_Common001_IG", Vector2(765.f, 1345.f), Vector2(43.f, 1539.f), //Vector2(0.f, 1539.f),//
		L"texture\\id_Clam_Common001_IG.png", "content/texture/id_Clam_Common001_IG.png"
		, L"texture\\id_Clam_Common001_OG.png", "content/texture/id_Clam_Common001_OG.png", 0.65f);
	addObject(id_Clam_Common001_IG, GROUP_TYPE::OBJ_REACT); // 일반조개 001

	Object* BO_ground001 = new BlueBG; // 바닥 1
	BO_ground001->initialize(Vector2(0.f, 1370.f), L"BO_ground001", L"texture\\BO_ground001.png");
	BO_ground001->setDepth(0.7f);
	addObject(BO_ground001, GROUP_TYPE::OBJ_REACT1);

	Object* id_Clam_Common002_IG = new Item(L"id_Clam_Common002_IG", L"id_Clam_Common002_IG"
		, Vector2(700.f, 1333.f), Vector2(8.f, 1438.f)
		, L"texture\\id_Clam_Common002_IG.png", "content/texture/id_Clam_Common002_IG.png"
		, L"texture\\id_Clam_Common002_OG.png", "content/texture/id_Clam_Common002_OG.png", 0.65f);
	addObject(id_Clam_Common002_IG, GROUP_TYPE::OBJ_REACT); // 일반조개 002

	Object* BO_seaweed002 = new BlueBG; // 해초 002 : 위로 뻗은 거
	BO_seaweed002->initialize(Vector2(143.f, 718.f), L"BO_seaweed002", L"texture\\BO_seaweed002.png");
	BO_seaweed002->setDepth(0.9f);
	addObject(BO_seaweed002, GROUP_TYPE::OBJ_REACT);

	Object* BO_seaweed001 = new BlueBG;  // 해초 001 : 왼쪽 두 줄기
	BO_seaweed001->initialize(Vector2(115.f, 719.f), L"BO_seaweed001", L"texture\\BO_seaweed001.png");
	BO_seaweed001->setDepth(0.9f);
	addObject(BO_seaweed001, GROUP_TYPE::OBJ_REACT);

	Object* BO_ocean_stone001 = new BlueBG; // 스톤 001 : 왼쪽 스톤
	BO_ocean_stone001->initialize(Vector2(0.f, 660.f), L"BO_ocean_stone001", L"texture\\BO_ocean_stone_001.png");
	BO_ocean_stone001->setDepth(1.1f);
	addObject(BO_ocean_stone001, GROUP_TYPE::OBJ_REACT); ///REACT1로 바꾸지 마세요.


	Object* id_Ship = new ItemOnlyCollider(L"id_Ship", L"id_Ship", Vector2(237.f, 263.f), //배
		L"texture\\id_Ship.png", "content/texture/id_Ship.png", 0.1f);  // 인어 꼬리
	addObject(id_Ship, GROUP_TYPE::OBJ_REACT1);


	/// 밤이 된 후 클릭하면 획득할 수 있습니다.(동굴을 클릭하면 밤이 된다.)
	Object* id_Figurehead_IG = new Item(L"id_Figurehead_IG", L"id_Figurehead_IG", Vector2(427.f, 468.f), Vector2(30.f, 2013.f),
		L"texture\\id_Figurehead_IG.png", "content/texture/id_Figurehead_IG.png"
		, L"texture\\id_Figurehead_OG.png", "content/texture/id_Figurehead_OG.png", 0.1f);
	addObject(id_Figurehead_IG, GROUP_TYPE::OBJ_REACT); //뱃머리

	Object* id_Sail_Pattern_IG = new Item(L"id_Sail_Pattern_IG", L"id_Sail_Pattern_IG", Vector2(381.f,379.f), Vector2(43.f, 435.f),
		L"texture\\id_Sail_Pattern_IG.png", "content/texture/id_Sail_Pattern_IG.png"
		, L"texture\\id_Sail_Pattern_OG.png", "content/texture/id_Sail_Pattern_OG.png", 0.1f);
	addObject(id_Sail_Pattern_IG, GROUP_TYPE::OBJ_REACT); //돛문양

	Object* id_Wave_IG = new Item(L"id_Wave_IG", L"id_Wave_IG", Vector2(412.f, 469.f), Vector2(8.f, 297.f),
		L"texture\\id_Wave_IG.png", "content/texture/id_Wave_IG.png"
		, L"texture\\id_Wave_OG.png", "content/texture/id_Wave_OG.png", 0.1f);
	addObject(id_Wave_IG, GROUP_TYPE::OBJ_REACT); //파도

	Object* id_Fish_IG = new Item(L"id_Fish_IG", L"id_Fish_IG", Vector2(710.f, 500.f), Vector2(17.f, 30.f),
		L"texture\\id_Fish_IG.png", "content/texture/id_Fish_IG.png"
		, L"texture\\id_Fish_OG.png", "content/texture/id_Fish_OG.png", 0.15f);
	addObject(id_Fish_IG, GROUP_TYPE::OBJ_REACT); // 물고기



	Object* id_Mermaid_Tail_IG = new ItemOnlyCollider(L"id_Mermaid_Tail_IG", L"id_Mermaid_Tail_IG", Vector2(890.f, 340.f), 
		L"texture\\id_Mermaid_Tail_IG.png", "content/texture/id_Mermaid_Tail_IG.png", 0.1f);  // 인어 꼬리
	addObject(id_Mermaid_Tail_IG, GROUP_TYPE::OBJ_REACT1);

	///꼬리달린 인어 -> 물약 -> 다리달린 인어

	Object* id_Mermaid_Legs_OG = new ItemOnlyCollider(L"id_Mermaid_Legs_OG", L"id_Mermaid_Legs_OG", Vector2(1129.f, 503.f)
		, L"texture\\id_Mermaid_Legs_OG.png", "content/texture/id_Mermaid_Legs_OG.png", 0.1f);
	instantiate(id_Mermaid_Legs_OG, GROUP_TYPE::UI); // 인어 다리(OG)
}


