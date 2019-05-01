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
	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x - 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x, pPlayer->m_tWorldPos.y - 1))
		{
			pPlayer->m_tWorldPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tWorldPos.x + 1, pPlayer->m_tWorldPos.y))
		{
			pPlayer->m_tWorldPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
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
		EventWindowRenewal("������ ���� !!");
		ChangeWorldToCastle(pPlayer, ppECastle[g_nEnableStage]);
	}
	// �� ������ ���
	else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
	{
		ChangeWorldToBattleMap(pPlayer, ppBattleMaps[g_battleMapIndex]);

		EventWindowRenewal("���� �����Ͽ����ϴ�. ���� ����.");
	}
}

void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	int nLoseFlag = 0;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x - 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y - 1, pECastle))
		{
			pPlayer->m_tPos.y--;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (CheckCanMoveInECastle(pPlayer->m_tPos.x + 1, pPlayer->m_tPos.y, pECastle))
		{
			pPlayer->m_tPos.x++;
			g_moveFlag = 1;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
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
	g_battleMapIndex = rand() % TOTAL_BATTLEMAP_NUM;
	g_gameMode = MM_BATTLEMAP;
	memset(aBackBuffer, 0, sizeof(aBackBuffer));

	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		pPlayer->m_pSoldiers[i]->m_tPos.x = pBattleMap->m_tPlayerStartPos[i].x;
		pPlayer->m_pSoldiers[i]->m_tPos.y = pBattleMap->m_tPlayerStartPos[i].y;
	}

	g_moveFlag = 1;
}

void CalcSoldierMoveRange(PSOLDIER pSoldier, PBATTLEMAP pBattleMap)
{
	if (pSoldier == NULL)
	{
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
	}
	else
	{
		memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
		POINT queue[QUEUE_MAX_SIZE] = { 0 };
		int front = 0, rear = 1;
		int nPath = 0;

		POINT curPos = { pSoldier->m_tPos.x, pSoldier->m_tPos.y };
		queue[front] = curPos;
		aBattleMapRange[curPos.x][curPos.y] = 1;

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
			if (++nPath >= pSoldier->m_nMoveRange) return;
		}
	}
}

void SetMousePos(PPLAYER pPlayer)
{
	pPlayer->m_nMouseOn = !pPlayer->m_nMouseOn;
	if (pPlayer->m_nMouseOn)
	{
		pPlayer->m_tMouse.x = pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x;
		pPlayer->m_tMouse.y = pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y;
	}
	g_moveFlag = 1;
}

void PlayerSoldierMove(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// ������ ����
	if (pPlayer->m_nMouseOn == ON)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x - 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x--;
				g_moveFlag = 1;
			}

		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y - 1])
			{
				pPlayer->m_tMouse.y--;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x + 1][pPlayer->m_tMouse.y])
			{
				pPlayer->m_tMouse.x++;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			if (aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y + 1])
			{
				pPlayer->m_tMouse.y++;
				g_moveFlag = 1;
			}
		}

		if (GetAsyncKeyState('K') & 0x8000)
		{
			if (pPlayer->m_tMouse.x != pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x ||
				pPlayer->m_tMouse.y != pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y)
			{
				pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.x = pPlayer->m_tMouse.x;
				pPlayer->m_pSoldiers[pPlayer->m_nSelectSoldier]->m_tPos.y = pPlayer->m_tMouse.y;

				// ���� ������� �˸�
				pPlayer->m_nSoldierTurn[pPlayer->m_nSelectSoldier] = 1;

				// ���� ���� ���� ���簡 �ִ� �� Ȯ��
				pPlayer->m_nSelectSoldier = -1;
				for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
				{
					if (!pPlayer->m_nSoldierTurn[i])
					{
						// �������� ���� ���
						pPlayer->m_nSelectSoldier = i;
						pPlayer->m_tMouse.x = pPlayer->m_pSoldiers[i]->m_tPos.x;
						pPlayer->m_tMouse.y = pPlayer->m_pSoldiers[i]->m_tPos.y;
						CalcSoldierMoveRange(pPlayer->m_pSoldiers[i], pBattleMap);
						break;
					}
				}

				// ���� ��� ������ ���
				if (pPlayer->m_nSelectSoldier == -1)
				{
					// ��� ��
					pPlayer->m_nMouseOn = OFF;
					pBattleMap->m_nCurTurn = TT_ENEMY;
					CalcSoldierMoveRange(NULL, pBattleMap);
					EventWindowRenewal("���� �� �Դϴ�.");
				}

				g_moveFlag = 1;
			}
		}
	}
}

void UpdateInBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// ��� ����
	if (GetAsyncKeyState('1') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_KNIGHT])
		{
			pPlayer->m_nSelectSoldier = SC_KNIGHT;
			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_pSoldiers[SC_KNIGHT]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// ���� ���
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_KNIGHT], pBattleMap);
			g_moveFlag = 1;
		}
		else
			EventWindowRenewal("�̹� ���� ��ģ �����Դϴ�.");
	}
	// �⺴ ����
	if (GetAsyncKeyState('2') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_CAVALRY])
		{
			pPlayer->m_nSelectSoldier = SC_CAVALRY;
			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_pSoldiers[SC_CAVALRY]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// ���� ���
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_CAVALRY], pBattleMap);
			g_moveFlag = 1;
		}

		else
			EventWindowRenewal("�̹� ���� ��ģ �����Դϴ�.");
	}
	// �ü� ����
	if (GetAsyncKeyState('3') & 0x8000)
	{
		if (!pPlayer->m_nSoldierTurn[SC_ARCHER])
		{
			pPlayer->m_nSelectSoldier = SC_ARCHER;
			sprintf(aEventTmpMessage, "[�÷��̾�] %s", pPlayer->m_pSoldiers[SC_ARCHER]->m_strName);
			EventWindowRenewal(aEventTmpMessage);
			memset(aEventTmpMessage, 0, sizeof(aEventMessage));

			// ���� ���
			CalcSoldierMoveRange(pPlayer->m_pSoldiers[SC_ARCHER], pBattleMap);
			g_moveFlag = 1;
		}

		else
			EventWindowRenewal("�̹� ���� ��ģ �����Դϴ�.");
	}

	// ĳ���� ����
	if (!pPlayer->m_nSoldierTurn[pPlayer->m_nSelectSoldier] && 
		pPlayer->m_nSelectSoldier >= 0 && 
		pPlayer->m_nSelectSoldier < TOTAL_SOLDIER_NUM && 
		GetAsyncKeyState('T') & 0x8000)
	{
		SetMousePos(pPlayer);
	}

	// ���� Move
	PlayerSoldierMove(pPlayer, pBattleMap);
}

int CheckEndBattleGame(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	return 0;
}
