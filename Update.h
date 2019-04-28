#pragma once
#include "Game.h"

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

void Update(PPLAYER pPlayer, PECASTLE pECastle)
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (g_gameMode == MM_WORLDMAP)
		{
			if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tPos.x - 1, pPlayer->m_tPos.y))
			{
				pPlayer->m_tPos.x--;
				g_moveFlag = 1;
			}
				
		}
		else if (g_gameMode == MM_CASTLEMAP)
		{
			if (CheckCanMoveInECastle(pPlayer->m_tPos.x - 1, pPlayer->m_tPos.y, pECastle))
			{
				pPlayer->m_tPos.x--;
				g_moveFlag = 1;
			}
		}
		else if (g_gameMode == MM_BATTLEMAP)
		{
		}
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (g_gameMode == MM_WORLDMAP)
		{
			if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tPos.x, pPlayer->m_tPos.y - 1))
			{
				pPlayer->m_tPos.y--;
				g_moveFlag = 1;
			}
		}
		else if (g_gameMode == MM_CASTLEMAP)
		{
			if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y - 1, pECastle))
			{
				pPlayer->m_tPos.y--;
				g_moveFlag = 1;
			}
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		if (g_gameMode == MM_WORLDMAP)
		{
			if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tPos.x + 1, pPlayer->m_tPos.y))
			{
				pPlayer->m_tPos.x++;
				g_moveFlag = 1;
			}	
		}
		else if (g_gameMode == MM_CASTLEMAP)
		{
			if (CheckCanMoveInECastle(pPlayer->m_tPos.x + 1, pPlayer->m_tPos.y, pECastle))
			{
				pPlayer->m_tPos.x++;
				g_moveFlag = 1;
			}
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (g_gameMode == MM_WORLDMAP)
		{
			if (CheckCanMoveInWorld(pPlayer->m_nHaveShip, pPlayer->m_tPos.x, pPlayer->m_tPos.y + 1))
			{
				pPlayer->m_tPos.y++;
				g_moveFlag = 1;
			}	
		}
		else if (g_gameMode == MM_CASTLEMAP)
		{
			if (CheckCanMoveInECastle(pPlayer->m_tPos.x, pPlayer->m_tPos.y + 1, pECastle))
			{
				pPlayer->m_tPos.y++;
				g_moveFlag = 1;
			}
		}
	}

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
			if (aWorldMap[pPlayer->m_tPos.x][pPlayer->m_tPos.y] == MWT_ECASTLEAREA)
			{
				aWorldMap[pPlayer->m_tPos.x][pPlayer->m_tPos.y] = MWT_PCASTLEAREA;
			}
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
	}


	// ���� ����
	if (g_gameMode == MM_WORLDMAP)
	{

	}
	// �� ����
	else if (g_gameMode == MM_CASTLEMAP)
	{
		int nPlayerX = pPlayer->m_tPos.x;
		int nPlayerY = pPlayer->m_tPos.y;

		// ��ֹ� ����
		if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_OBSTACLE)
		{
			// ������ �ѾƳ��� �� �� ���� ȸ��
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
			// ���信�� ������ �� ���� �Ʊ�ȭ �� ����ޱ�
		}
	}

}