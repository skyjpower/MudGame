#pragma once
#include "Game.h"

int CheckCanMoveInWorld(int nShip, int x, int y);
int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle);
void Update(PPLAYER pPlayer, PECASTLE* pECastle);
void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle);
void ChangeCastleToWorld(PPLAYER pPlayer, int nWin);