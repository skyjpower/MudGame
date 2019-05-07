#pragma once
#include "Game.h"

extern char* pMainText;

extern char aWorldMap[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
extern int aBattleMapRange[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern int aBattleMapMoveFlag[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

extern char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

extern char aEventWindow[EVENT_WINDOW_HEIGHT][EVENT_WINDOW_WIDTH];
extern char aEventMessage[EVENT_STRING_MAXLENGTH];
extern char aEventTmpMessage[EVENT_STRING_MAXLENGTH];

extern char aStatusWindow[STATUS_WINDOW_HEIGHT][STATUS_WINDOW_WIDTH];
extern char aSubWindow[SUBWINDOW_HEIGHT][SUBWINDOW_WIDTH];

extern char aRuleWindow[RULE_WINDOW_HEIGHT][RULE_WINDOW_WIDTH];

extern POINT tStartPos;

extern const char* FileName[TOTAL_ECASTLE_NUM];
extern const char* BattleMapFileName[3];

extern int g_moveFlag;
extern int g_gameMode;
extern int g_sightMode;
extern int g_eventFlag;
extern int g_nEnableStage;
extern int g_gameOver;
extern int g_battleMapIndex;


extern int LevelStatusTable[3][3][7];
extern int LevelCharacterUpgradeCost[3][3];

extern int aMapTileColor[2][7];
extern int aCastleTileColor[2][7];
extern int aBattleTileColor[2][10];

extern int xDir[8];
extern int yDir[8];

extern char CharacterClassName[3][12];
extern char LevelCharacterNameTable[3][3][12];
extern char LevelCharacterShapeTable[3][3][3];
extern char LevelEnemyShapeTable[3][3][3];
extern char aShopItems[SHOP_ITEMS_COUNT][30];
extern int aShopItemsPrice[SHOP_ITEMS_COUNT];

extern const int MOVE, ATMIN, ATMAX, RANGE, ARMIN, ARMAX, HP;

extern float g_fDeltaTime;
extern LARGE_INTEGER g_tSecond;
extern LARGE_INTEGER g_tTime;