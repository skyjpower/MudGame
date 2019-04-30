#pragma once
#include "Game.h"

// ��
extern char aWorldMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBattleMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

// ����
extern char aFrontBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aBackBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern char aClearBuffer[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

// ���� â
extern char aStatusWindow[STATUS_WINDOW_LENGTH];
extern POINT tStartPos;

extern const char* FileName[3];

/* ���� ���� */
extern int g_moveFlag;
extern int g_gameMode;
extern int g_sightMode;
extern int g_eventFlag;
extern int g_nEnableStage;
extern int g_gameOver;

// ���� ���̺�
extern int LevelStatusTable[3][3][7];
// �̸� ���̺�
extern char LevelCharacterNameTable[3][3][12];
// ������ ���� ��� ���̺�
extern char LevelCharacterShapeTable[3][3][3];
// ���׷��̵� �ڽ�Ʈ ���̺�
extern int LevelCharacterUpgradeCost[3][3];
// ������ ���̺�
extern char CharacterClassName[3][12];
// �� ���� ���̺�
extern int aMapTileColor[2][7];
// ĳ�� ���� ���̺�
extern int aCastleTileColor[2][6];
// �ε���
extern const int MOVE, ATMIN, ATMAX, RANGE, ARMIN, ARMAX, HP;