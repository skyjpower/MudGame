#pragma once
#include "Game.h"

// ��ü �ʱ�ȭ
int Init(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps);
// �⺻ �ʱ�ȭ
void BasicInit(PPLAYER pPlayer);
// �÷��̾� ���� ����
int CreatePlayerSoldier(PPLAYER pPlayer);
// ���� ����
SOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade);
// ����� �ҷ�����
int LoadWorldMap(PPLAYER pPlayer, PECASTLE* ppECastle);
// ĳ���� �ʱ�ȭ
int LoadECastleMap(PECASTLE pECastle, const char* FileName);
// ��Ʋ�� �ʱ�ȭ
int LoadBattleMap(PBATTLEMAP pBattleMap, int nCurFileIndex);
// ��Ʋ �� ���� �� �ʱ�ȭ
void InitBattleStage(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// �� ���� Ȯ��
void CheckEnemyCastleArea(PECASTLE pECastle);


// Save
void SavePlayer(PPLAYER pPlayer);
void SaveWorldMap();
void SaveECastleMap(PECASTLE* ppECastleMaps);
void SaveBattleMaps(PBATTLEMAP* ppBattleMaps);


// Load
int LoadMain();
int LoadPlayer(PPLAYER pPlayer);
int LoadWorld();
int LoadECastles(PECASTLE* ppECastleMaps);
int LoadBattleMaps(PBATTLEMAP* ppBattleMaps);


// �ܼ� �ʱ�ȭ
void ConsoleInit();
// ���� ȭ��
int MainMenuScene();
int LoadMain();