#pragma once
#include "Game.h"

// 맵
extern char aWorldMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBattleMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

// 버퍼
extern char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

// 상태 창
extern char aStatusWindow[STATUS_WINDOW_LENGTH];
extern POINT tStartPos;

extern const char* FileName[3];

/* 전역 변수 */
extern int g_moveFlag;
extern int g_gameMode;
extern int g_sightMode;
extern int g_eventFlag;
extern int g_nEnableStage;
extern int g_gameOver;

// 레벨 테이블
extern int LevelStatusTable[3][3][7];
// 이름 테이블
extern char LevelCharacterNameTable[3][3][12];
// 레벨에 따른 모양 테이블
extern char LevelCharacterShapeTable[3][3][3];
// 업그레이드 코스트 테이블
extern int LevelCharacterUpgradeCost[3][3];
// 직업명 테이블
extern char CharacterClassName[3][12];
// 맵 색깔 테이블
extern int aMapTileColor[2][7];
// 캐슬 색깔 테이블
extern int aCastleTileColor[2][6];
// 인덱스
extern const int MOVE, ATMIN, ATMAX, RANGE, ARMIN, ARMAX, HP;