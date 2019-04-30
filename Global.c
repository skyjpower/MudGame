#include "Global.h"

// ��
char aWorldMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBattleMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

// ���� â
char aStatusWindow[STATUS_WINDOW_LENGTH];

POINT tStartPos;

// ĳ�� �������� �̸�
const char* FileName[3] = { "CastleStage1.txt", "CastleStage2.txt", "CastleStage1.txt" };


/* ���� ���� */
int g_moveFlag = 0;
int g_gameMode = MM_WORLDMAP;
int g_sightMode = 1;
int g_eventFlag = 0;
int g_nEnableStage = 0;
int g_gameOver = 0;



/* ���� ���̺� */
/*	�ε����� ���� �������ͽ�
0 : MoveRange
1 : AttackMin
2 : AttackMax
3 : AttackRange
4 : ArmorMin
5 : ArmorMax
6 : nHp
*/

// ������ ���� �ɷ�ġ
int LevelStatusTable[3][3][7] = {
	{
		{ 2, 1, 2, 1, 3, 5, 100 },
		{ 2, 2, 3, 1, 5, 7, 120 },
		{ 3, 3, 4, 1, 7, 10, 140 }
	},
	{
		{ 3, 2, 5, 1, 1, 2, 80 },
		{ 4, 4, 7, 1, 2, 3, 100 },
		{ 5, 6, 9, 2, 4, 6, 120 }
	},
	{
		{ 1, 2, 4, 2, 0, 1, 50 },
		{ 1, 3, 5, 2, 1, 2, 60 },
		{ 2, 4, 6, 3, 2, 3, 70 }
	}
};

// ���׷��̵忡 ���� ĳ���� �̸�
char LevelCharacterNameTable[3][3][12] = {
	{
		{ "���ѱ��" },
		{ "���" },
		{ "���ѱ��" }
	},
	{
		{ "���ѱ⺴" },
		{ "�⺴" },
		{ "���ѱ⺴" }
	},
	{
		{ "���ѱú�" },
		{ "�ú�" },
		{ "���ѱú�" }
	}
};

// ���׷��̵忡 ���� ĳ���� ���
char LevelCharacterShapeTable[3][3][3] = {
	{
		{ "��" },
		{ "��" },
		{ "��" }
	},
	{
		{ "��" },
		{ "��" },
		{ "��" }
	},
	{
		{ "��" },
		{ "��" },
		{ "��" }
	}
};

// ���׷��̵� ���
int LevelCharacterUpgradeCost[3][3] = {
	{ 0, 80, 150 },
	{ 0, 80, 150 },
	{ 0, 80, 150 }
};

// ĳ���� Ŭ���� �̸�
char CharacterClassName[3][12] = { "���", "�⺴", "�ú�" };

const int MOVE = 0, ATMIN = 1, ATMAX = 2, RANGE = 3, ARMIN = 4, ARMAX = 5, HP = 6;

// fore, back color
int aMapTileColor[2][7] =
{
	{ BROWN, WHITE, BLUE, GREEN, LIGHTGREEN, RED, RED },
	{ BROWN, BLACK, BLUE, LIGHTGRAY, LIGHTGREEN, LIGHTGRAY, LIGHTRED }
};

// fore, back color
int aCastleTileColor[2][6] =
{
	{ BROWN, WHITE, BLUE, YELLOW, MAGENTA, RED },
	{ BROWN, BROWN, BLUE, BLACK, BROWN, BROWN }
};
