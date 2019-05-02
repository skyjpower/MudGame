#pragma once
#include "Game.h"

// 월드맵에서 움직임 확인
int CheckCanMoveInWorld(int nShip, int x, int y);
// 캐슬맵에서 움직임 확인
int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle);


/* Update */

// 월드맵 Update
void Update(PPLAYER pPlayer, PECASTLE* pECastle, PBATTLEMAP* ppBattleMaps);
// 캐슬맵 Update
void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle);
// 배틀 맵 Update
void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);


/* 모드 변화 시 호출 */

// 월드맵 -> 캐슬맵
void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle);
// 캐슬맵 -> 월드맵
void ChangeCastleToWorld(PPLAYER pPlayer, int nWin);
// 월드맵 -> 배틀맵
void ChangeWorldToBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 배틀맵 -> 월드맵
void ChangeBattleMapToWorld(PPLAYER pPlayer, PBATTLEMAP pBattleMap, int nWinTeam);


/* 배틀맵 관련 함수 */

// 배틀 맵 전투가 끝났는지 확인
int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 병사의 범위 조사
void CalcSoldierRange(PPLAYER pPlayer, PSOLDIER pSoldier, PBATTLEMAP pBattleMap);
// 플레이어 병사 움직임
void PlayerSoldierUpdate(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 플레이어 병사 주변에 적이 있는 지 확인
int CheckEnemyAroundPlayerSoldier(PSOLDIER pSoldier, PBATTLEMAP pBattleMap);
// 병사 조정 커서 위치
void SetMousePos(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// 공격 판정
int AttackManager(PSOLDIER pAttacker, PSOLDIER pDefender);
// 플레이어의 차례인지 확인
int CheckEndPlayerTurn(PPLAYER pPlayer);
// 적 AI
void BattleMapEnemyAI(PPLAYER pPlayer, PBATTLEMAP pBattleMap);


/* 시간 계산 */

// 델타 타임 계산
void CalcDeltaTime();
// 주어진 시간만큼 딜레이
void DelayTime(float waitTime);