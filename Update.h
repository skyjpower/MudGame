#pragma once
#include "Game.h"

// ����ʿ��� ������ Ȯ��
int CheckCanMoveInWorld(int nShip, int x, int y);
// ĳ���ʿ��� ������ Ȯ��
int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle);


/* Update */

// ����� Update
void Update(PPLAYER pPlayer, PECASTLE* pECastle, PBATTLEMAP* ppBattleMaps);
// ĳ���� Update
void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle);
// ��Ʋ �� Update
void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);


/* ��� ��ȭ �� ȣ�� */

// ����� -> ĳ����
void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle);
// ĳ���� -> �����
void ChangeCastleToWorld(PPLAYER pPlayer, int nWin);
// ����� -> ��Ʋ��
void ChangeWorldToBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// ��Ʋ�� -> �����
void ChangeBattleMapToWorld(PPLAYER pPlayer, PBATTLEMAP pBattleMap, int nWinTeam);


/* ��Ʋ�� ���� �Լ� */

// ��Ʋ �� ������ �������� Ȯ��
int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// ������ ���� ����
void CalcSoldierRange(PPLAYER pPlayer, PSOLDIER pSoldier, PBATTLEMAP pBattleMap);
// �÷��̾� ���� ������
void PlayerSoldierUpdate(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// �÷��̾� ���� �ֺ��� ���� �ִ� �� Ȯ��
int CheckEnemyAroundPlayerSoldier(PSOLDIER pSoldier, PBATTLEMAP pBattleMap);
// ���� ���� Ŀ�� ��ġ
void SetMousePos(PPLAYER pPlayer, PBATTLEMAP pBattleMap);
// ���� ����
int AttackManager(PSOLDIER pAttacker, PSOLDIER pDefender);
// �÷��̾��� �������� Ȯ��
int CheckEndPlayerTurn(PPLAYER pPlayer);
// �� AI
void BattleMapEnemyAI(PPLAYER pPlayer, PBATTLEMAP pBattleMap);


/* �ð� ��� */

// ��Ÿ Ÿ�� ���
void CalcDeltaTime();
// �־��� �ð���ŭ ������
void DelayTime(float waitTime);