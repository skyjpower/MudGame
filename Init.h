#pragma once
#include "Game.h"

// ��ü �� �ʱ�ȭ �� �ε�
int Init(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps);
// �÷��̾� ���� ����
int CreatePlayerSoldier(PPLAYER pPlayer);
// ���� ����
SOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade);
// ����� �ҷ�����
int LoadWorldMap(PPLAYER pPlayer, PECASTLE* ppECastle);
// ĳ���� �ҷ�����
int LoadECastleMap(PECASTLE pECastle, const char* FileName);
// �� ���� Ȯ��
void CheckEnemyCastleArea(PECASTLE pECastle);
// ��Ʋ �� ���� �� �ʱ�ȭ
void InitBattleStage(PBATTLEMAP pBattleMap);