#pragma once
#include "Game.h"

// 전체 초기화
int Init(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps);
// 기본 초기화
void BasicInit(PPLAYER pPlayer);
// 플레이어 병사 생성
int CreatePlayerSoldier(PPLAYER pPlayer);
// 병사 생성
SOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade);
// 월드맵 불러오기
int LoadWorldMap(PPLAYER pPlayer, PECASTLE* ppECastle);
// 캐슬맵 초기화
int LoadECastleMap(PECASTLE pECastle, const char* FileName);
// 배틀맵 초기화
int LoadBattleMap(PBATTLEMAP pBattleMap, int nCurFileIndex);
// 배틀 맵 시작 전 초기화
void InitBattleStage(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 적 영토 확인
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


// 콘솔 초기화
void ConsoleInit();
// 메인 화면
int MainMenuScene();
int LoadMain();