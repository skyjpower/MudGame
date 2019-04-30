#pragma once
#include "Update.h"
#include "Global.h"
#include "Render.h"

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

void Update(PPLAYER pPlayer, PECASTLE* ppECastle)
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

		// ���� â Ȯ��
		if (GetAsyncKeyState('P') & 0x8000)
		{
			sprintf(aStatusWindow, "�ȳ��ϼ���! �׽�Ʈ ���Դϴ�.");
			StatusWindow();
			sprintf(aStatusWindow, "");
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
		g_gameMode = MM_CASTLEMAP;
	}
}

void UpdateInCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
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

		// ���� â Ȯ��
		if (GetAsyncKeyState('P') & 0x8000)
		{
			sprintf(aStatusWindow, "�ȳ��ϼ���! �׽�Ʈ ���Դϴ�.");
			StatusWindow();
			sprintf(aStatusWindow, "");
		}
		// ĳ�� �ٷ� ����
		if (GetAsyncKeyState('F') & 0x8000)
		{
			pPlayer->m_tPos.x = 1;
			pPlayer->m_tPos.y = 27;
		}
	}


	// �� ����
	int nPlayerX = pPlayer->m_tPos.x;
	int nPlayerY = pPlayer->m_tPos.y;

	// ��ֹ� ����
	if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_OBSTACLE)
	{

		// ������ �ѾƳ��� �� �� ���� ȸ��
		ChangeCastleToWorld(pPlayer, CASTLE_LOSE);
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
	}
	// �������� �ٴٸ� ���
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

		// ��������� �̵�
		ChangeCastleToWorld(pPlayer, CASTLE_WIN);
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