#pragma once
#include "Game.h"


extern char aWorldMap[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
extern int aBattleMapRange[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

extern char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

extern char aEventWindow[EVENT_WINDOW_HEIGHT][EVENT_WINDOW_WIDTH];
extern char aEventMessage[STATUS_STRING_MAXLENGTH];
extern char aEventTmpMessage[STATUS_STRING_MAXLENGTH];

extern char aStatusWindow[STATUS_WINDOW_HEIGHT][STATUS_WINDOW_WIDTH];

extern POINT tStartPos;

extern const char* FileName[3];
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
extern int aCastleTileColor[2][6];
extern int aBattleTileColor[2][10];

extern int xDir[4];
extern int yDir[4];

extern char CharacterClassName[3][12];
extern char LevelCharacterNameTable[3][3][12];
extern char LevelCharacterShapeTable[3][3][3];

extern const int MOVE, ATMIN, ATMAX, RANGE, ARMIN, ARMAX, HP;