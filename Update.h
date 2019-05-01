#pragma once
#include "Game.h"

int CheckCanMoveInWorld(int nShip, int x, int y);
int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle);
void Update(PPLAYER pPlayer, PECASTLE* pECastle, PBATTLEMAP* ppBattleMaps);
void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle);
void ChangeCastleToWorld(PPLAYER pPlayer, int nWin);
void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
void CalcSoldierMoveRange(PSOLDIER pSoldier, PBATTLEMAP pBattleMap);
void PlayerSoldierMove(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
void ChangeWorldToBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
void SetMousePos(PPLAYER pPlayer);