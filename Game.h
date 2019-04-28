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


/* 전역 변수 */
int g_moveFlag = 0;
int g_gameMode = MM_CASTLEMAP;
int g_sightMode = 1;
int g_eventFlag = 0;


#pragma region FuncList
/************************* 초기화 *************************/
	
int Init(PPLAYER pPlayer, PECASTLE pECastle); // 플레이어 초기화
int CreatePlayerSoldier(PPLAYER pPlayer); // 플레이어의 병사 생성
PSOLDIER CreateSoldier(int nType, int nTeam, int ); // 병사 생성
int LoadWorldMap(); // World 맵을 불러옴
int LoadECastleMap(PECASTLE pECastle, const char* FileName); // 캐슬 맵 불러옴

/************************ 렌더링 **************************/

void MoveCursorTo(const int x, const int y); //  커서 위치
void DrawToBackBuffer(const int x, const int y, char image); // 백버퍼에 그리기
void DrawAll(); // 모두 백버퍼에 그리기
void RenderWorldMap(PPLAYER pPlayer); // 화면 출력
void TextColor(int foreground, int background); // 콘솔 색 조정

/************************* 업데이트 ***********************/

void Update(PPLAYER pPlayer); // 캐릭터 업데이트

/************************* 디버깅 *************************/

void DebugSoliderList(PPLAYER pPlayer); // 병사 목록 확인

/**********************************************************/
#pragma endregion

// 맵
char aWorldMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBattleMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };
char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

// 상태 창
char aStatusWindow[STATUS_WINDOW_LENGTH];

POINT tStartPos;