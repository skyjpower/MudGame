#pragma once
#define _CRT_SECURE_NO_WARNINGS


#define MANAGE_MODE 1
#define DEBUG_MODE 0


#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <memory.h>

#include "Type.h"
#include "LevelTable.h"
#include "Struct.h"


#define MAP_WIDTH_MAX 30
#define MAP_HEIGHT_MAX 30

#define TOTAL_SOLDIER_NUM 3
#define TOTAL_ECASTLE_NUM 3

#define STATUS_WINDOW_LENGTH 128
#define STATUS_WINDOW_HEIGHT 40


/* ���� ���� */
int g_moveFlag = 0;
int g_gameMode = MM_CASTLEMAP;
int g_sightMode = 1;
int g_eventFlag = 0;


#pragma region FuncList
/************************* �ʱ�ȭ *************************/
	
int Init(PPLAYER pPlayer, PECASTLE pECastle); // �÷��̾� �ʱ�ȭ
int CreatePlayerSoldier(PPLAYER pPlayer); // �÷��̾��� ���� ����
PSOLDIER CreateSoldier(int nType, int nTeam, int ); // ���� ����
int LoadWorldMap(); // World ���� �ҷ���
int LoadECastleMap(PECASTLE pECastle, const char* FileName); // ĳ�� �� �ҷ���

/************************ ������ **************************/

void MoveCursorTo(const int x, const int y); //  Ŀ�� ��ġ
void DrawToBackBuffer(const int x, const int y, char image); // ����ۿ� �׸���
void DrawAll(); // ��� ����ۿ� �׸���
void RenderWorldMap(PPLAYER pPlayer); // ȭ�� ���
void TextColor(int foreground, int background); // �ܼ� �� ����

/************************* ������Ʈ ***********************/

void Update(PPLAYER pPlayer); // ĳ���� ������Ʈ

/************************* ����� *************************/

void DebugSoliderList(PPLAYER pPlayer); // ���� ��� Ȯ��

/**********************************************************/
#pragma endregion

// ��
char aWorldMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBattleMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

// ���� â
char aStatusWindow[STATUS_WINDOW_LENGTH];

POINT tStartPos;