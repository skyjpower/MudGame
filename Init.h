#pragma once
#include "Game.h"

// 전체 맵 초기화 및 로드
int Init(PPLAYER pPlayer, PECASTLE* ppECastle);
// 플레이어 병사 생성
int CreatePlayerSoldier(PPLAYER pPlayer);
// 병사 생성
PSOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade);
// 월드맵, 성 맵 불러오기
int LoadWorldMap(PECASTLE* ppECastle);
int LoadECastleMap(PECASTLE pECastle, const char* FileName);
// 적 영토 확인
void CheckEnemyCastleArea(PECASTLE pECastle);
