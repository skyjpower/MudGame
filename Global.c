#include "Global.h"

// 맵
char aWorldMap[MAP_WIDTH_MAX][MAP_HEIGHT_MAX] = { 0 };
// 배틀 맵 캐릭터 움직임 범위 표시
int aBattleMapRange[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
// 배틀 맵 내에 이동가능한 타일 표시
int aBattleMapMoveFlag[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
// 버퍼
char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

// 이벤트 창
char aEventWindow[EVENT_WINDOW_HEIGHT][EVENT_WINDOW_WIDTH] = { 0 };
char aEventMessage[EVENT_STRING_MAXLENGTH] = { 0 };
char aEventTmpMessage[EVENT_STRING_MAXLENGTH] = { 0 };

// 룰 창
char aRuleWindow[RULE_WINDOW_HEIGHT][RULE_WINDOW_WIDTH] = { 0 };

// 상태 창 및 서브 창
char aStatusWindow[STATUS_WINDOW_HEIGHT][STATUS_WINDOW_WIDTH] = { 0 };
char aSubWindow[SUBWINDOW_HEIGHT][SUBWINDOW_WIDTH] = { 0 };

POINT tStartPos;

// 캐슬 스테이지 이름
const char* FileName[TOTAL_ECASTLE_NUM] = { "CastleStage1.txt", "CastleStage2.txt", "CastleStage3.txt", "CastleStage4.txt" };
const char* BattleMapFileName[3] = { "BattleMap1.txt", "BattleMap2.txt", "BattleMap3.txt" };

int g_moveFlag = 0;
int g_gameMode = MM_WORLDMAP;
int g_sightMode = 1;
int g_eventFlag = 0;
int g_nEnableStage = 0;
int g_gameOver = 0;
int g_battleMapIndex = 0;

/* 레벨 테이블 */

/* 인덱스에 따른 스테이터스
	0 : MoveRange
	1 : AttackMin
	2 : AttackMax
	3 : AttackRange
	4 : ArmorMin
	5 : ArmorMax
	6 : nHp
*/

// 레벨 테이블 ( 아군 )
int LevelStatusTable[3][3][7] = {
	{
		{ 3, 30, 40, 1, 10, 20, 100 },
		{ 3, 40, 50, 1, 20, 35, 240 },
		{ 3, 50, 60, 1, 50, 60, 480 }
	},
	{
		{ 4, 40, 70, 1, 5, 7, 80 },
		{ 4, 50, 80, 1, 10, 13, 160 },
		{ 5, 60, 90, 2, 15, 18, 290 }
	},
	{
		{ 3, 40, 50, 2, 3, 5, 50 },
		{ 3, 45, 60, 2, 4, 6, 100 },
		{ 4, 70, 80, 3, 5, 7, 160 }
	}
};

// 레벨 테이블 ( 적군 )
int EnemyLevelStatusTable[3][3][7] = {
	{
		{ 2, 5, 8, 1, 13, 18, 100 },
		{ 2, 10, 12, 1, 30, 35, 120 },
		{ 3, 15, 20, 1, 50, 60, 140 }
	},
	{
		{ 3, 20, 60, 1, 5, 7, 80 },
		{ 3, 50, 80, 1, 10, 13, 100 },
		{ 4, 80, 90, 2, 30, 40, 120 }
	},
	{
		{ 2, 40, 50, 2, 3, 5, 50 },
		{ 2, 45, 60, 2, 4, 6, 60 },
		{ 3, 50, 70, 3, 5, 7, 70 }
	}
};

// 이름 테이블
char LevelCharacterNameTable[3][3][12] = {
	{
		{ "약한기사" },
		{ "기사" },
		{ "강한기사" }
	},
	{
		{ "약한기병" },
		{ "기병" },
		{ "강한기병" }
	},
	{
		{ "약한궁병" },
		{ "궁병" },
		{ "강한궁병" }
	}
};

// 레벨에 따른 모양 테이블 ( 아군 )
char LevelCharacterShapeTable[3][3][3] = {
	{
		{ "■" },
		{ "▣" },
		{ "盾" }
	},
	{
		{ "％" },
		{ "⊆" },
		{ "馬" }
	},
	{
		{ "＆" },
		{ "♤" },
		{ "弓" }
	}
};

// 레벨에 따른 모양 테이블 ( 적군 )
char LevelEnemyShapeTable[3][3][3] = {
	{
		{ "●" },
		{ "◎" },
		{ "★" }
	},
	{
		{ "§" },
		{ "㏇" },
		{ "♬" }
	},
	{
		{ "＆" },
		{ "※" },
		{ "♂" }
	}
};

// 직업명 테이블
char CharacterClassName[3][12] = { "기사", "기병", "궁병" };

// 인덱스
const int MOVE = 0, ATMIN = 1, ATMAX = 2, RANGE = 3, ARMIN = 4, ARMAX = 5, HP = 6;

// 맵 색깔 테이블
int aMapTileColor[2][7] =
{
	{ BROWN, WHITE, BLUE, GREEN, LIGHTGREEN, RED, RED },
	{ BROWN, BLACK, BLUE, LIGHTGRAY, LIGHTGREEN, LIGHTGRAY, LIGHTRED }
};

// 캐슬 색깔 테이블
int aCastleTileColor[2][7] =
{
	{ BROWN, WHITE, BLUE, YELLOW, MAGENTA, RED, WHITE },
	{ BROWN, BROWN, BLUE, BLACK, BROWN, BROWN, BROWN }
};

// 배틀맵 색깔 테이블
int aBattleTileColor[2][10] =
{
	{ BLACK, WHITE, BLUE, GREEN, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY },
	{ BLACK, BLACK, BLUE, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK }
};

// 상점 물품 목록
char aShopItems[SHOP_ITEMS_COUNT][30] =
{
	{ "기사 체력(100) 회복약" },
	{ "기병 체력(100) 회복약" },
	{ "궁병 체력(100) 회복약" },
	{ "전체 체력(100) 회복약" },
	{ "병사 업그레이드" },
	{ "망원경" },
};

int aShopItemsPrice[SHOP_ITEMS_COUNT] = {150, 150, 150, 300, 10000, 10000};

// 방향 | 상 하 좌 우 우하 우상 좌하 좌상
int xDir[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };
int yDir[8] = { 0, 0, -1, 1, 1, 1, -1, -1 };

// 델타 타임
LARGE_INTEGER g_tSecond; // 초당 클록수
LARGE_INTEGER g_tTime;	// 이전 클록수
float g_fDeltaTime = 0.f;