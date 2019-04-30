#pragma once
#include "Game.h"

// ��ü �� �ʱ�ȭ �� �ε�
int Init(PPLAYER pPlayer, PECASTLE* ppECastle);
// �÷��̾� ���� ����
int CreatePlayerSoldier(PPLAYER pPlayer);
// ���� ����
PSOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade);
// �����, �� �� �ҷ�����
int LoadWorldMap(PECASTLE* ppECastle);
int LoadECastleMap(PECASTLE pECastle, const char* FileName);
// �� ���� Ȯ��
void CheckEnemyCastleArea(PECASTLE pECastle);
