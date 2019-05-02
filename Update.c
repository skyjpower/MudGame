#pragma once
#include "Update.h"
#include "Global.h"
#include "Render.h"
#include "Init.h"

int CheckCanMoveInWorld(int nShip, int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_HEIGHT_MAX || y >= MAP_WIDTH_MAX) return 0;

	if (aWorldMap[x][y] == MWT_WALL) return 0;
	if (!nShip && aWorldMap[x][y] == MWT_WATER) return 0;
	if (aWorldMap[x][y] == MWT_SHOP) return 0;

	return 1;
}

int CheckCanMoveInECastle(int x, int y, PECASTLE pECastle)
{
	if (x < 0 || y < 0 || x >= CASTLE_HEIGHT_MAX || y >= CASTLE_WIDTH_MAX) return 0;

	if (pECastle->m_aECastleMap[x][y] == MCT_WALL ||
		pECastle->m_aECastleMap[x][y] == MCT_WATER ||
		pECastle->m_aECastleMap[x][y] == MCT_DOOR)
		return 0;

	return 1;
}

void Update(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps)
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x - 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x, pPlayer->m_tWorldPos.y - 1))
		{
			pPlayer->m_tWorldPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x + 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x, pPlayer->m_tWorldPos.y + 1))
		{
			pPlayer->m_tWorldPos.y++;
			g_moveFlag = 1;
		}
	}

	// ������
	if (MANAGE_MODE)
	{
		// �ٴ� �ǳʱ�
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pPlayer->m_nHaveShip = !pPlayer->m_nHaveShip;
		}

		// �Ʊ� �������� �����
		if (GetAsyncKeyState('B') & 0x8000)
		{
			if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLEAREA;
			else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_PCASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_ECASTLEAREA;
		}

		// �þ߰�
		if (GetAsyncKeyState('N') & 0x8000)
		{
			g_sightMode = !g_sightMode;
			Sleep(100);
		}

		if (GetAsyncKeyState('L') & 0x8000)
		{
			g_gameOver = 1;
		}
	}


	// �� ���� ���
	if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLE)
	{
		// ĳ�� �� ��ȭ
		for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
		{
			if (ppECastle[i]->m_tWorldPos.x == pPlayer->m_tWorldPos.x
				&& ppECastle[i]->m_tWorldPos.y == pPlayer->m_tWorldPos.y)
			{
				g_nEnableStage = i;
				pPlayer->m_tPos.x = ppECastle[i]->m_tStartPos.x;
				pPlayer->m_tPos.y = ppECastle[i]->m_tStartPos.y;
				break;
			}
		}

		sprintf(aEventTmpMessage, "������ ���� !!");
		EventWindowRenewal();
		ChangeWorldToCastle(pPlayer, ppECastle[g_nEnableStage]);
	}
	// �� ������ ���
	else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
	{
		g_battleMapIndex = rand() % TOTAL_BATTLEMAP_NUM;
		g_battleMapIndex = 2;
		ChangeWorldToBattleMap(pPlayer, ppBattleMaps[g_battleMapIndex]);

		sprintf(aEventTmpMessage, "���� �����Ͽ����ϴ�.");
		EventWindowRenewal();
	}
}

void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	int nLoseFlag = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x - 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y - 1, pECastle))
		{
			pPlayer->m_tPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x + 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y + 1, pECastle))
		{
			pPlayer->m_tPos.y++;
			g_moveFlag = 1;
		}
	}

	// ������
	if (MANAGE_MODE)
	{
		// �þ߰�
		if (GetAsyncKeyState('N') & 0x8000)
		{
			g_sightMode = !g_sightMode;
			Sleep(100);
		}

		// ĳ�� �ٷ� ����
		if (GetAsyncKeyState('F') & 0x8000)
		{
			pPlayer->m_tPos.x = 1;
			pPlayer->m_tPos.y = 27;
		}
	}


	// �÷��̾� ��ġ
	int nPlayerX = pPlayer->m_tPos.x;
	int nPlayerY = pPlayer->m_tPos.y;

	// ��ֹ� ����
	if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_OBSTACLE)
	{
		nLoseFlag = 1;
	}
	// Ű ȹ��
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_KEY)
	{
		PDOOR pDoor = pECastle->m_tDoorPosList->m_pBegin->m_pNext;
		PDOOR pEnd = pECastle->m_tDoorPosList->m_pEnd;

		// �� ����
		while (pDoor != pEnd)
		{
			pECastle->m_aECastleMap[pDoor->m_tPos.x][pDoor->m_tPos.y] = MCT_GROUND;
			pECastle->m_aECastleMap[pECastle->m_tKeyPos.x][pECastle->m_tKeyPos.y] = MCT_GROUND;
			pDoor->m_nClosed = 0;
			pDoor = pDoor->m_pNext;
		}
		EventWindowRenewal("Ű ȹ�� ! ������ ���Ƚ��ϴ�.");
	}
	// �������� �ٴٸ� ��� ( Ŭ���� )
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_DEST)
	{
		// ���� �Ʊ�ȭ
		aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLE;

		// ���� �Ʊ�ȭ
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_PCASTLEAREA;
			free(pArea);
			pArea = pNext;
		}

		// ���� ȹ��
		pPlayer->m_nMoney += pECastle->m_nReward;

		EventWindowRenewal("������ Ŭ���� !");
		// ��������� �̵�
		ChangeCastleToWorld(pPlayer, CASTLE_WIN);
	}

	// �й� ���� ��
	if (nLoseFlag)
	{
		// ���� �������� �ǵ�����
		pPlayer->m_tWorldPos.x = tStartPos.x;
		pPlayer->m_tWorldPos.y = tStartPos.y;

		// �� ���� ȸ��
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			pArea->m_beOccupied = 0;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_ECASTLEAREA;
			pArea = pArea->m_pNext;
		}

		// ������ �ѾƳ��� �� �� ���� ȸ��
		ChangeCastleToWorld(pPlayer, CASTLE_LOSE);
		EventWindowRenewal("�й��Ͽ����ϴ�....");
	}
}

void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	// ��ġ ����
	pPlayer->m_tPos.x = pECastle->m_tStartPos.x;
	pPlayer->m_tPos.y = pECastle->m_tStartPos.y;

	// ��� ����
	g_gameMode = MM_CASTLEMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));

	g_moveFlag = 1;
}

void ChangeCastleToWorld(PPLAYER pPlayer, int nWin)
{
	g_gameMode = MM_WORLDMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));
	g_moveFlag = 1;
}

void ChangeWorldToBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	g_gameMode = MM_BATTLEMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));

	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		pPlayer->m_tSoldiers[i].m_tPos.x = pBattleMap->m_tPlayerStartPos[i].x;
		pPlayer->m_tSoldiers[i].m_tPos.y = pBattleMap->m_tPlayerStartPos[i].y;
	}

	g_moveFlag = 1;
}

void BattleMapReset(PBATTLEMAP pBattleMap)
{
	pBattleMap->m_nCurTurn = TT_PLAYER;
	// ���� �ʱ�ȭ
	for (int i = 0; i < 3; ++i)
	{
		pBattleMap->m_tEnemy[i] = CreateSoldier(i, TT_ENEMY, 0);
		pBattleMap->m_tEnemy[i].m_tPos.x = pBattleMap->m_tEnemyStartPos[i].x;
		pBattleMap->m_tEnemy[i].m_tPos.y = pBattleMap->m_tEnemyStartPos[i].y;
	}
}

void ChangeBattleMapToWorld(PPLAYER pPlayer, PBATTLEMAP pBattleMap, int nWinTeam)
{
	// �÷��̾��� �¸�
	if (nWinTeam == TT_PLAYER)
	{
		// �¸� �޼���
		sprintf(aEventTmpMessage, "�÷��̾��� �¸� !");
		EventWindowRenewal();
		DelayTime(1.f);
		// ����
		int nReward = (rand() % (pBattleMap->m_nRewardMax - pBattleMap->m_nRewardMin)) + pBattleMap->m_nRewardMin;
		pPlayer->m_nMoney += nReward;
		// ���� �޼���
		sprintf(aEventTmpMessage, "%d ���� ȹ���Ͽ����ϴ�.", nReward);
		EventWindowRenewal();
		DelayTime(1.f);

		// �� ���� �Ʊ�ȭ
		aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLEAREA;
	}
	// ���� �¸�
	else if (nWinTeam == TT_ENEMY)
	{
		// �й� �޼���
		sprintf(aEventTmpMessage, "�������� �й��Ͽ����ϴ�..");
		EventWindowRenewal();
		DelayTime(1.f);
		// ��ġ �ʱ�ȭ
		pPlayer->m_tWorldPos.x = tStartPos.x;
		pPlayer->m_tWorldPos.y = tStartPos.y;
	}

	// ����
	BattleMapReset(pBattleMap);

	// ��������� �̵�
	g_gameMode = MM_WORLDMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));	
	g_moveFlag = 1;
}

void CalcSoldierRange(PPLAYER pPlayer, PSOLDIER pSoldier, PBATTLEMAP pBattleMap)
{
	if (pSoldier == NULL)
	{
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
		return;
	}

	memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
	POINT queue[QUEUE_MAX_SIZE] = { 0 };
	int front = 0, rear = 1;
	int nPath = 0;

	POINT curPos = { pSoldier->m_tPos.x, pSoldier->m_tPos.y };
	queue[front] = curPos;
	aBattleMapRange[curPos.x][curPos.y] = 1;

	if (pPlayer->m_nBattleMapMode == BM_MOVE)
	{
		// ������ ���� �ִ� ���
		if (pSoldier->m_bMoveFlag)
		{
			aBattleMapRange[pSoldier->m_tPos.x][pSoldier->m_tPos.y] = 1;
			return;
		}

		while (front != rear)
		{
			int qSize = rear - front;
			for (int i = 0; i < qSize; ++i)
			{
				int cur_x = queue[front].x;
				int cur_y = queue[front].y;
				front = (front + 1) % QUEUE_MAX_SIZE;

				for (int j = 0; j < 4; ++j)
				{
					int next_x = cur_x + xDir[j];
					int next_y = cur_y + yDir[j];

					if (aBattleMapRange[next_x][next_y]) continue;
					if (pBattleMap->m_aBattleMap[next_x][next_y] != MBT_GROUND &&
						pBattleMap->m_aBattleMap[next_x][next_y] != MBT_MOUNTAIN)
						continue;

					POINT tmp = { next_x, next_y };
					queue[rear++] = tmp;
					aBattleMapRange[next_x][next_y] = 1;
				}
			}
			if (++nPath >= pSoldier->m_nMoveRange) return;
		}
	}
	else if (pPlayer->m_nBattleMapMode == BM_BATTLE)
	{
		while (front != rear)
		{
			int qSize = rear - front;
			for (int i = 0; i < qSize; ++i)
			{
				int cur_x = queue[front].x;
				int cur_y = queue[front].y;
				front = (front + 1) % QUEUE_MAX_SIZE;

				for (int j = 0; j < 4; ++j)
				{
					int next_x = cur_x + xDir[j];
					int next_y = cur_y + yDir[j];

					if (aBattleMapRange[next_x][next_y]) continue;
					if (pBattleMap->m_aBattleMap[next_x][next_y] == MBT_WATER ||
						pBattleMap->m_aBattleMap[next_x][next_y] == MBT_WALL)
						continue;

					POINT tmp = { next_x, next_y };
					queue[rear++] = tmp;
					aBattleMapRange[next_x][next_y] = 1;
				}
			}
			if (++nPath >= pSoldier->m_nAttackRange) return;
		}
	}
	
}

void SetMousePos(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// ����
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// �����ϱ�
		if (pPlayer->m_nMouseOn != ON)
		{
			pPlayer->m_nBattleMapMode = BM_MOVE;
			pPlayer->m_nMouseOn = ON;
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.y;
			CalcSoldierRange(pPlayer, &(pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier]), pBattleMap);
			g_moveFlag = 1;
		}
		else if (pPlayer->m_nMouseOn && pPlayer->m_nBattleMapMode == BM_BATTLE)
		{
			pPlayer->m_nBattleMapMode = BM_MOVE;
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.y;
			CalcSoldierRange(pPlayer, &(pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier]), pBattleMap);
			g_moveFlag = 1;
		}
		Sleep(100);
	}
	
	// ���� ���
	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (pPlayer->m_nMouseOn != ON)
		{
			pPlayer->m_nBattleMapMode = BM_BATTLE;
			pPlayer->m_nMouseOn = ON;
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.y;
			CalcSoldierRange(pPlayer, &(pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier]), pBattleMap);
			g_moveFlag = 1;
		}
		else if (pPlayer->m_nMouseOn && pPlayer->m_nBattleMapMode == BM_MOVE)
		{
			pPlayer->m_nBattleMapMode = BM_BATTLE;
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_tPos.y;
			CalcSoldierRange(pPlayer, &(pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier]), pBattleMap);
			g_moveFlag = 1;
		}
		Sleep(100);
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		pPlayer->m_nMouseOn = OFF;
		pPlayer->m_nBattleMapMode = BM_MOVE;
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
		g_moveFlag = 1;
	}
}

int AttackManager(PSOLDIER pAttacker, PSOLDIER pDefender)
{
	// ���� ������ ���
	int nAttack = (rand() % (pAttacker->m_nAttackMax - pAttacker->m_nAttackMin)) + pAttacker->m_nAttackMin;
	// ��� ���
	int nArmor = (rand() % (pDefender->m_nArmorMax - pDefender->m_nArmorMin)) + pDefender->m_nArmorMin;
	// �� ������ ���
	int nDamage = nAttack - nArmor > 0 ? nAttack - nArmor : 0;

	// ������ ����
	pDefender->m_nCurHp -= nDamage;

	char AttackerTeam[20] = { 0 };
	char DefenderTeam[20] = { 0 };

	if (pAttacker->m_nTeam == TT_PLAYER)
		strcpy(AttackerTeam, "�÷��̾�");
	else if (pAttacker->m_nTeam == TT_ENEMY)
		strcpy(AttackerTeam, "��");
	else if (pAttacker->m_nTeam == TT_ALLY)
		strcpy(AttackerTeam, "����");

	if (pDefender->m_nTeam == TT_PLAYER)
		strcpy(DefenderTeam, "�÷��̾�");
	else if (pDefender->m_nTeam == TT_ENEMY)
		strcpy(DefenderTeam, "��");
	else if (pDefender->m_nTeam == TT_ALLY)
		strcpy(DefenderTeam, "����");

	// �޼���
	sprintf(aEventTmpMessage, "%s %s(��)�� %s %s���� %d �������� �������ϴ�.",
		AttackerTeam, pAttacker->m_strName, DefenderTeam, pDefender->m_strName, nDamage);
	EventWindowRenewal();
	DelayTime(1.5f);

	// ����ڰ� �׾��� �� Ȯ���ϱ�
	if (pDefender->m_nCurHp <= 0)
	{
		sprintf(aEventTmpMessage, "%s %s(��)�� ����Ͽ����ϴ�.",
			DefenderTeam, pDefender->m_strName, nDamage);
		EventWindowRenewal();
		DelayTime(1.5f);
		return DEAD;
	}

	return ALIVE;
}

void CalcDeltaTime()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);
	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)(g_tSecond.QuadPart);
	g_tTime = tTime;
}

void DelayTime(float waitTime)
{
	float nWait = 0;

	while (nWait <= waitTime)
	{
		nWait += g_fDeltaTime;
		CalcDeltaTime();
	}
}

int CheckEndPlayerTurn(PPLAYER pPlayer)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		// ���� �����ϴ� ���簡 �ִ� ���
		if (pPlayer->m_tSoldiers[i].m_bTurn)
			return FALSE;
	}

	return TRUE;
}

void BattleMapEnemyAI(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	DelayTime(3.f);
	pBattleMap->m_nCurTurn = TT_PLAYER;

	sprintf(aEventTmpMessage, "�÷��̾� ���� !");
	EventWindowRenewal();
}

int CheckEnemyAroundPlayerSoldier(PSOLDIER pSoldier, PBATTLEMAP pBattleMap)
{
	int cur_x = pSoldier->m_tPos.x;
	int cur_y = pSoldier->m_tPos.y;
	int range = pSoldier->m_nAttackRange;

	int nLeft = (cur_y - range < 0) ? 0 : cur_y - range;
	int nTop = (cur_x - range < 0) ? 0 : cur_x - range;
	int nRight = (cur_y + range < MAP_HEIGHT_MAX) ? cur_y + range : MAP_HEIGHT_MAX - 1;
	int nBottom = (cur_x + range < MAP_WIDTH_MAX) ? cur_x + range : MAP_WIDTH_MAX - 1;

	for (int i = nTop; i <= nBottom; ++i)
	{
		for (int j = nLeft; j <= nRight; ++j)
		{
			if ((abs(cur_x - i) + abs(cur_y - j) <= range))
			{
				for (int k = 0; k < pBattleMap->m_nEnemyCount; ++k)
					if (!pBattleMap->m_tEnemy[k].m_nDie && pBattleMap->m_tEnemy[k].m_tPos.x == i && pBattleMap->m_tEnemy[k].m_tPos.y == j)
						return TRUE;
			}
		}
	}

	return FALSE;
}

void PlayerSoldierUpdate(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
#pragma region Move
	// ������ ����
	if (pPlayer->m_nMouseOn == ON)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x - 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x--;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y - 1])
			{
				pPlayer->m_tMouse.y--;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x + 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x++;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y + 1])
			{
				pPlayer->m_tMouse.y++;
				g_moveFlag = 1;
			}
		}
#pragma endregion
		

#pragma region ModeIsMove
		// ���� ���
		if (pPlayer->m_nBattleMapMode == BM_MOVE && !pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_bMoveFlag)
		{
			PSOLDIER pSeletSoldier = &pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier];

			// �̵� Ȯ��
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if (pPlayer->m_tMouse.x !=pSeletSoldier->m_tPos.x ||
					pPlayer->m_tMouse.y !=pSeletSoldier->m_tPos.y)
				{
					pSeletSoldier->m_tPos.x = pPlayer->m_tMouse.x;
					pSeletSoldier->m_tPos.y = pPlayer->m_tMouse.y;

					// ������ ���� ������� �˸�
					pSeletSoldier->m_bMoveFlag = ON;

					// �̵��� �� �ֺ��� ������ �� �ִ� ����� ���� ���
					if (!CheckEnemyAroundPlayerSoldier(pSeletSoldier, pBattleMap))
					{
						// ���� �÷��� ON
						pSeletSoldier->m_bAttackFlag = ON;
						// �� ������
						pSeletSoldier->m_bTurn = OFF;
					}

					memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
					pPlayer->m_nMouseOn = OFF;
					g_moveFlag = 1;
				}
			}
		}
#pragma endregion
#pragma region ModeIsBattle
		else if ( !pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_bAttackFlag &&
					pPlayer->m_nMouseOn && 
					GetAsyncKeyState('A') & 0x8000 && 
					pPlayer->m_nBattleMapMode == BM_BATTLE)
		{
			PSOLDIER pSelectSoldier = &pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier];
			PSOLDIER pSelectEnemy = NULL;

			// ���� �� ���콺 Ŀ���� ���� �����ϴ� �� Ȯ��
			for (int i = 0; i < pBattleMap->m_nEnemyCount; ++i)
			{
				// �� ����
				if (!pBattleMap->m_tEnemy[i].m_nDie
					&& pBattleMap->m_tEnemy[i].m_tPos.x == pPlayer->m_tMouse.x
					&& pBattleMap->m_tEnemy[i].m_tPos.y == pPlayer->m_tMouse.y)
				{
					pSelectEnemy = &pBattleMap->m_tEnemy[i];
					break;
				}
			}

			// ���� ���� ���
			if (pSelectEnemy == NULL)
			{
				// �޼���
				sprintf(aEventTmpMessage, "�ش� ������ ���� �������� �ʽ��ϴ�.");
				EventWindowRenewal();
				return;
			}
			// ���� �����ϴ� ��� ����!
			else
			{
				// ���� ���� ���
				if (AttackManager(pSelectSoldier, pSelectEnemy) == DEAD)
					pSelectEnemy->m_nDie = 1;

				pSelectSoldier->m_bAttackFlag = ON;
				pSelectSoldier->m_bTurn = 0;
			}

			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			pPlayer->m_nMouseOn = OFF;
			g_moveFlag = 1;
		}
#pragma endregion

	}
}

void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
#pragma region ChoiceSoldier
	// ��� ����
	if (GetAsyncKeyState('1') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_KNIGHT].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_KNIGHT;

			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_tSoldiers[SC_KNIGHT].m_strName);
			EventWindowRenewal();
			
			// Ŀ�� �̵�
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.y;

			// ���õ� ���� ǥ��
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;

			g_moveFlag = 1;
		}
		else
		{
			sprintf(aEventTmpMessage, "�̹� ���� ��ģ �����Դϴ�.");
			EventWindowRenewal();
		}
	}
	// �⺴ ����
	if (GetAsyncKeyState('2') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_CAVALRY].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_CAVALRY;
			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_tSoldiers[SC_CAVALRY].m_strName);
			EventWindowRenewal();

			// Ŀ�� �̵�
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.y;

			// ���õ� ���� ǥ��
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;

			g_moveFlag = 1;
		}

		else
		{
			sprintf(aEventTmpMessage, "�̹� ���� ��ģ �����Դϴ�.");
			EventWindowRenewal();
		}
	}
	// �ü� ����
	if (GetAsyncKeyState('3') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_ARCHER].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_ARCHER;
			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_tSoldiers[SC_ARCHER].m_strName);
			EventWindowRenewal();

			
			// Ŀ�� �̵�
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.y;

			// ���õ� ���� ǥ��
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;
			
			g_moveFlag = 1;
		}

		else
		{
			sprintf(aEventTmpMessage, "�̹� ���� ��ģ �����Դϴ�.");
			EventWindowRenewal();
		}
	}
#pragma endregion

	// ĳ���� ����
	if ( pPlayer->m_nSelectSoldier >= SC_KNIGHT && 
			pPlayer->m_nSelectSoldier < SC_END &&
			pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_bTurn)
	{
		SetMousePos(pPlayer, pBattleMap);
	}

	// ���� ������
	PlayerSoldierUpdate(pPlayer, pBattleMap);
	
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		// ������ ���� �ְ� ������ ���� ���� ������ ���
		if (pPlayer->m_tSoldiers[i].m_bMoveFlag && !pPlayer->m_tSoldiers[i].m_bAttackFlag)
		{
			// ���� ���� ���
			if (!CheckEnemyAroundPlayerSoldier(&(pPlayer->m_tSoldiers[i]), pBattleMap))
				pPlayer->m_tSoldiers[i].m_bAttackFlag = ON;
		}
	}

	// �÷��̾� ���� üũ
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		if (pPlayer->m_tSoldiers[i].m_bTurn)
		{
			if (pPlayer->m_tSoldiers[i].m_bAttackFlag && pPlayer->m_tSoldiers[i].m_bMoveFlag)
				pPlayer->m_tSoldiers[i].m_bTurn = 0;
		}
	}

	// �� ���� üũ
	if (CheckEndPlayerTurn(pPlayer))
	{
		// �ʱ�ȭ
		for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		{
			pPlayer->m_tSoldiers[i].m_bAttackFlag = 0;
			pPlayer->m_tSoldiers[i].m_bMoveFlag = 0;
			pPlayer->m_tSoldiers[i].m_bTurn = 1;
		}

		pBattleMap->m_nCurTurn = TT_ENEMY;
		sprintf(aEventTmpMessage, "���� �����Դϴ�...");
		EventWindowRenewal();
	}
}

int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	if (MANAGE_MODE)
	{
		if (GetAsyncKeyState('P') & 0x8000)
		{
			return TT_PLAYER;
		}

		if (GetAsyncKeyState('E') & 0x8000)
		{
			return TT_ENEMY;
		}
	}
	
	int endFlag = 1;
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		if (!pPlayer->m_tSoldiers[i].m_nDie)
		{
			endFlag = 0;
			break;
		}
	}
	// ���� �¸�
	if (endFlag) return TT_ENEMY;

	endFlag = 1;
	for (int i = 0; i < pBattleMap->m_nEnemyCount; ++i)
	{
		if (!pBattleMap->m_tEnemy[i].m_nDie)
		{
			endFlag = 0;
			break;
		}
	}
	// �÷��̾� �¸�
	if (endFlag) return TT_PLAYER;

	return TT_NONE;
}
