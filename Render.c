#pragma once
#include "Render.h"
#include "Global.h"

void TextColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MoveCursorTo(const int x, const int y)
{
	const COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawToBackBuffer(const int x, const int y, char image)
{
	aBackBuffer[x][y] = image;
}

int CheckPlayerArea(int x, int y)
{

	int nLeft = y - 1 >= 0 ? y - 1 : 0;
	int nTop = x - 1 >= 0 ? x - 1 : 0;
	int nRight = y + 1 < MAP_WIDTH_MAX ? y + 1 : MAP_WIDTH_MAX - 1;
	int nBottom = x + 1 < MAP_HEIGHT_MAX ? x + 1 : MAP_HEIGHT_MAX - 1;

	for (int i = nTop; i <= nBottom; ++i)
	{
		for (int j = nLeft; j <= nRight; ++j)
			aBackBuffer[i][j] = aWorldMap[i][j];
	}


	/*
	�þ� ������ 1ĭ��

	if (aWorldMap[x][y] == MWT_PCASTLE || aWorldMap[x][y] == MWT_PCASTLEAREA) return TRUE;
	// ���� �˻�
	if (x - 1 >= 0 && (aWorldMap[x - 1][y] == MWT_PCASTLE || aWorldMap[x - 1][y] == MWT_PCASTLEAREA)) return 1;
	// �Ʒ��� �˻�
	if (x + 1 < MAP_HEIGHT_MAX && (aWorldMap[x + 1][y] == MWT_PCASTLE || aWorldMap[x + 1][y] == MWT_PCASTLEAREA)) return 1;
	// ���� �˻�
	if (y - 1 >= 0 && (aWorldMap[x][y - 1] == MWT_PCASTLE || aWorldMap[x][y - 1] == MWT_PCASTLEAREA)) return 1;
	// ������ �˻�
	if (y + 1 < MAP_WIDTH_MAX && (aWorldMap[x][y + 1] == MWT_PCASTLE || aWorldMap[x][y + 1] == MWT_PCASTLEAREA)) return 1;
	*/

	return FALSE;
}

void StatusWindowRefresh(PPLAYER pPlayer)
{
	int nHeight = 1;
	int nWidth = (MAP_WIDTH_MAX * 2 + 3);

	/* ���� ��� ��� */
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		MoveCursorTo(nWidth, nHeight++);
		TextColor(YELLOW, BLACK);
		printf("�̸� : %s", pPlayer->m_tSoldiers[i].m_strName);
		MoveCursorTo(nWidth, nHeight++);
		TextColor(LIGHTGRAY, BLACK);
		printf("��� : %s\n", pPlayer->m_tSoldiers[i].m_cShape);
		MoveCursorTo(nWidth, nHeight++);
		printf("���� : %d ~ %d", pPlayer->m_tSoldiers[i].m_nAttackMin, pPlayer->m_tSoldiers[i].m_nAttackMax);
		MoveCursorTo(nWidth, nHeight++);
		printf("��� : %d ~ %d", pPlayer->m_tSoldiers[i].m_nArmorMin, pPlayer->m_tSoldiers[i].m_nArmorMax);
		MoveCursorTo(nWidth, nHeight++);
		if (pPlayer->m_tSoldiers[i].m_nDie)
			TextColor(RED, BLACK);
		printf("ü�� : %d / %d", pPlayer->m_tSoldiers[i].m_nCurHp, pPlayer->m_tSoldiers[i].m_nHp);
		TextColor(LIGHTGRAY, BLACK);
		MoveCursorTo(nWidth, nHeight++);
		printf("�̵����� : %d", pPlayer->m_tSoldiers[i].m_nMoveRange);
		MoveCursorTo(nWidth, nHeight);
		printf("���ݹ��� : %d", pPlayer->m_tSoldiers[i].m_nAttackRange);

		nHeight += 2;
	}

	// �÷��̾� ����
	MoveCursorTo(nWidth, nHeight);
	printf("                      ");
	MoveCursorTo(nWidth, nHeight);
	printf("������ : %d", pPlayer->m_nMoney);
	nHeight += 2;
	MoveCursorTo(nWidth, nHeight);
	printf("�� ���� ���� : %s", pPlayer->m_nHaveShip == 1 ? "O" : "X");
	nHeight += 2;
}

void DrawAll(PPLAYER pPlayer)
{
	int nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;

	if (g_sightMode)
	{
		int sightRange = 2;
		nLeft = pPlayer->m_tWorldPos.y - sightRange > 0 ? pPlayer->m_tWorldPos.y - sightRange : 0;
		nTop = pPlayer->m_tWorldPos.x - sightRange > 0 ? pPlayer->m_tWorldPos.x - sightRange : 0;
		nRight = pPlayer->m_tWorldPos.y + sightRange < MAP_WIDTH_MAX ? pPlayer->m_tWorldPos.y + sightRange : MAP_WIDTH_MAX - 1;
		nBottom = pPlayer->m_tWorldPos.x + sightRange < MAP_WIDTH_MAX ? pPlayer->m_tWorldPos.x + sightRange : MAP_HEIGHT_MAX - 1;
	}

	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			// �þ߰� ���
			if (!g_sightMode)
			{
				aBackBuffer[i][j] = aWorldMap[i][j];
			}
			// ��ü ���
			else
			{
				if (aWorldMap[i][j] == MWT_PCASTLEAREA || aWorldMap[i][j] == MWT_PCASTLE)
					CheckPlayerArea(i, j);
				else if (nLeft <= j && j <= nRight && nTop <= i && i <= nBottom)
					aBackBuffer[i][j] = aWorldMap[i][j];
			}
		}
	}
}

void RenderECastleMap(PPLAYER pPlayer, PECASTLE pECastle)
{
	// Draw
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			int nForeColor = aCastleTileColor[0][pECastle->m_aECastleMap[i][j] - '0'];
			int nBackColor = aCastleTileColor[1][pECastle->m_aECastleMap[i][j] - '0'];

			if (aBackBuffer[i][j] != aFrontBuffer[i][j] || g_moveFlag)
			{
				MoveCursorTo(nTmp, i);

				// �÷��̾��� ���
				if (i == pPlayer->m_tPos.x && j == pPlayer->m_tPos.y)
				{
					MoveCursorTo(nTmp, i);
					TextColor(pPlayer->m_nColor, nBackColor);
					printf(pPlayer->m_cShape);
				}
				// ��
				else if (aBackBuffer[i][j] == MCT_GROUND)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// ��
				else if (aBackBuffer[i][j] == MCT_WALL)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// ��
				else if (aBackBuffer[i][j] == MCT_WATER)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// ��
				else if (aBackBuffer[i][j] == MCT_DOOR)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// Ű
				else if (aBackBuffer[i][j] == MCT_KEY)
				{
					TextColor(nForeColor, BLACK);
					printf("��");
				}
				// ������
				else if (pECastle->m_tDestPos.x == i && pECastle->m_tDestPos.y == j)
				{
					if (aBackBuffer[i][j] == '\0')
						TextColor(GREEN, BLACK);
					else
						TextColor(GREEN, BLACK);
					printf("��");
				}
				// ��ֹ�
				else if (aBackBuffer[i][j] == MCT_OBSTACLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				else if (aBackBuffer[i][j] == '\0')
				{
					TextColor(BLACK, BLACK);
					printf("  ");
				}
			}
			nTmp += 2;
		}
	}

	// Move �÷��� ����
	g_moveFlag = 0;
	// ���� �������
	TextColor(LIGHTGRAY, BLACK);

	// ����Ʈ ���� ������Ʈ
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			aFrontBuffer[i][j] = aBackBuffer[i][j];
			aBackBuffer[i][j] = '\0';
		}
	}
}

void RenderWorldMap(PPLAYER pPlayer)
{
	// Draw
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			int nForeColor = aMapTileColor[0][aWorldMap[i][j] - '0'];
			int nBackColor = aMapTileColor[1][aWorldMap[i][j] - '0'];

			if (aBackBuffer[i][j] != aFrontBuffer[i][j] || g_moveFlag)
			{
				MoveCursorTo(nTmp, i);

				// �÷��̾��� ���
				if (i == pPlayer->m_tWorldPos.x && j == pPlayer->m_tWorldPos.y)
				{
					MoveCursorTo(nTmp, i);
					TextColor(pPlayer->m_nColor, nBackColor);
					printf(pPlayer->m_cShape);
				}
				// ��
				else if (aBackBuffer[i][j] == MWT_GROUND)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// ��
				else if (aBackBuffer[i][j] == MWT_WALL)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// ��
				else if (aBackBuffer[i][j] == MWT_WATER)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// �÷��̾� ��
				else if (aBackBuffer[i][j] == MWT_PCASTLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// �÷��̾� ����
				else if (aBackBuffer[i][j] == MWT_PCASTLEAREA)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// �� ��
				else if (aBackBuffer[i][j] == MWT_ECASTLE)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				// �� �� ����
				else if (aBackBuffer[i][j] == MWT_ECASTLEAREA)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// ����
				else if (aBackBuffer[i][j] == MWT_SHOP)
				{
					TextColor(RED, BROWN);
					printf("��");
				}
				else if (aBackBuffer[i][j] == '\0')
				{
					TextColor(BLACK, BLACK);
					printf("  ");
				}
			}
			nTmp += 2;
		}
	}

	// Move �÷��� ����
	g_moveFlag = 0;
	// ���� �������
	TextColor(LIGHTGRAY, BLACK);


	// ����Ʈ ���� ������Ʈ
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			aFrontBuffer[i][j] = aBackBuffer[i][j];
			aBackBuffer[i][j] = '\0';
		}
	}
}

void EventWindowRenewal()
{
	int nHeight = MAP_HEIGHT_MAX + (EVENT_WINDOW_HEIGHT / 2);
	int nWidth = 4;
	
	MoveCursorTo(2, nHeight);
	for (int i = 0; i < EVENT_WINDOW_WIDTH - 2; ++i)
		printf("  ");
	/*for (int i = 0; i < EVENT_STRING_MAXLENGTH; ++i) aEventMessage[i] = ' ';
	printf(aEventMessage);
	memset(aEventMessage, 0, sizeof(aEventMessage));*/

	strcpy(aEventMessage, aEventTmpMessage);
	memset(aEventTmpMessage, 0, sizeof(aEventTmpMessage));
	MoveCursorTo(nWidth, nHeight);
	printf(aEventMessage);
}

void DrawECastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	int nLeft = 0, nTop = 0, nRight = 0, nBottom = 0;

	if (g_sightMode)
	{
		int sightRange = 3;
		nLeft = pPlayer->m_tPos.y - sightRange > 0 ? pPlayer->m_tPos.y - sightRange : 0;
		nTop = pPlayer->m_tPos.x - sightRange > 0 ? pPlayer->m_tPos.x - sightRange : 0;
		nRight = pPlayer->m_tPos.y + sightRange < CASTLE_WIDTH_MAX ? pPlayer->m_tPos.y + sightRange : CASTLE_WIDTH_MAX - 1;
		nBottom = pPlayer->m_tPos.x + sightRange < CASTLE_HEIGHT_MAX ? pPlayer->m_tPos.x + sightRange : CASTLE_HEIGHT_MAX - 1;
	}

	for (int i = 0; i < CASTLE_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < CASTLE_WIDTH_MAX; ++j)
		{
			if (!g_sightMode)
			{
				aBackBuffer[i][j] = pECastle->m_aECastleMap[i][j];
			}
			else
			{
				if (nLeft <= j && j <= nRight && nTop <= i && i <= nBottom || pECastle->m_aECastleMap[i][j] == MCT_DEST)
					aBackBuffer[i][j] = pECastle->m_aECastleMap[i][j];
				else
					aBackBuffer[i][j] = '\0';
			}
		}
	}
}

void DrawBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	for (int i = 0; i < BATTLE_HEGIHT_MAX; ++i)
	{
		for (int j = 0; j < BATTLE_WIDTH_MAX; ++j)
			aBackBuffer[i][j] = pBattleMap->m_aBattleMap[i][j];
	}
}

void RenderBattleMap(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	// Draw
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		int nTmp = 0;
		int nForeColor = 0;
		int nBackColor = 0;

		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			nForeColor = aBattleTileColor[0][pBattleMap->m_aBattleMap[i][j] - '0'];
			nBackColor = aBattleTileColor[1][pBattleMap->m_aBattleMap[i][j] - '0'];
			if (pPlayer->m_nMouseOn == ON && pPlayer->m_tMouse.x == i && pPlayer->m_tMouse.y == j)
			{
				if (pPlayer->m_nBattleMapMode == BM_MOVE)
					nBackColor = GREEN;
				else if (pPlayer->m_nBattleMapMode == BM_BATTLE)
					nBackColor = RED;
			}
				
			else if (aBattleMapRange[i][j])
				nBackColor = LIGHTGRAY;

			if (aBackBuffer[i][j] != aFrontBuffer[i][j] || g_moveFlag)
			{
				MoveCursorTo(nTmp, i);

				// �÷��̾� ���
				if (!pPlayer->m_tSoldiers[SC_KNIGHT].m_nDie && 
					i == pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.x &&
					j == pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.y)
				{
					TextColor(pPlayer->m_tSoldiers[SC_KNIGHT].m_nColor, nBackColor);
					printf(pPlayer->m_tSoldiers[SC_KNIGHT].m_cShape);
				}
				// �÷��̾� �⺴
				else if (!pPlayer->m_tSoldiers[SC_CAVALRY].m_nDie &&
					i == pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.x && 
					j == pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.y)
				{
					TextColor(pPlayer->m_tSoldiers[SC_CAVALRY].m_nColor, nBackColor);
					printf(pPlayer->m_tSoldiers[SC_CAVALRY].m_cShape);
				}
				// �÷��̾� �û�
				else if (!pPlayer->m_tSoldiers[SC_ARCHER].m_nDie &&
					i == pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.x && 
					j == pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.y)
				{
					TextColor(pPlayer->m_tSoldiers[SC_ARCHER].m_nColor, nBackColor);
					printf(pPlayer->m_tSoldiers[SC_ARCHER].m_cShape);
				}
				// �� ����
				else if (!pBattleMap->m_tEnemy[SC_KNIGHT].m_nDie && 
					i == pBattleMap->m_tEnemy[SC_KNIGHT].m_tPos.x && 
					j == pBattleMap->m_tEnemy[SC_KNIGHT].m_tPos.y)
				{
					TextColor(pBattleMap->m_tEnemy[SC_KNIGHT].m_nColor, nBackColor);
					printf(pBattleMap->m_tEnemy[SC_KNIGHT].m_cShape);
				}
				// �� �⺴
				else if (!pBattleMap->m_tEnemy[SC_CAVALRY].m_nDie &&
					i == pBattleMap->m_tEnemy[SC_CAVALRY].m_tPos.x && 
					j == pBattleMap->m_tEnemy[SC_CAVALRY].m_tPos.y)
				{
					TextColor(pBattleMap->m_tEnemy[SC_CAVALRY].m_nColor, nBackColor);
					printf(pBattleMap->m_tEnemy[SC_CAVALRY].m_cShape);
				}
				// �� �ú�
				else if (!pBattleMap->m_tEnemy[SC_ARCHER].m_nDie &&
					i == pBattleMap->m_tEnemy[SC_ARCHER].m_tPos.x && 
					j == pBattleMap->m_tEnemy[SC_ARCHER].m_tPos.y)
				{
					TextColor(pBattleMap->m_tEnemy[SC_ARCHER].m_nColor, nBackColor);
					printf(pBattleMap->m_tEnemy[SC_ARCHER].m_cShape);
				}
				// ��
				else if (aBackBuffer[i][j] == MBT_GROUND)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// ��
				else if (aBackBuffer[i][j] == MBT_WALL)
				{
					TextColor(nForeColor, nBackColor);
					printf("��");
				}
				//��
				else if (aBackBuffer[i][j] == MBT_WATER)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
				// ��
				else if (aBackBuffer[i][j] == MBT_MOUNTAIN)
				{
					TextColor(nForeColor, nBackColor);
					printf("  ");
				}
			}
			nTmp += 2;
		}
	}

	// Move �÷��� ����
	g_moveFlag = 0;
	// ���� �������
	TextColor(LIGHTGRAY, BLACK);

	// ����Ʈ ���� ������Ʈ
	for (int i = 0; i < MAP_HEIGHT_MAX; ++i)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; ++j)
		{
			aFrontBuffer[i][j] = aBackBuffer[i][j];
			aBackBuffer[i][j] = '\0';
		}
	}
}

void CreateStatusWindow()
{
	// �̺�Ʈ â ����
	for (int i = 0; i < EVENT_WINDOW_HEIGHT; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < EVENT_WINDOW_WIDTH; ++j)
		{
			if (aEventWindow[i][j] == '1')
			{
				MoveCursorTo(nTmp, i + EVENT_WINDOW_HEIGHT_OFFSET);
				printf("��");
			}
			else
			{
				MoveCursorTo(nTmp, i + EVENT_WINDOW_HEIGHT_OFFSET);
				printf("  ");
			}
			nTmp += 2;
		}
	}

	// �������ͽ� â ����
	for (int i = 0; i < STATUS_WINDOW_HEIGHT; ++i)
	{
		int nTmp = 0;

		for (int j = 0; j < STATUS_WINDOW_WIDTH; ++j)
		{
			if (aStatusWindow[i][j] == '1')
			{
				MoveCursorTo(nTmp + STATUS_WINDOW_WIDTH_OFFSET, i);
				printf("��");
			}
			else
			{
				MoveCursorTo(nTmp + STATUS_WINDOW_WIDTH_OFFSET, i);
				printf("  ");
			}
			nTmp += 2;
		}
	}
}

void OnOffSubWindow(int nFlag)
{
	if (nFlag == ON)
	{
		// ���� â ���
		for(int i = 0; i < SUBWINDOW_HEIGHT; ++i)
		{
			int nTmp = 0;

			for (int j = 0; j < SUBWINDOW_WIDTH; ++j)
			{
				if (aSubWindow[i][j] == '1')
				{
					MoveCursorTo(nTmp + SUBWINDOW_WIDTH_OFFSET, SUBWINDOW_HEIGHT_OFFSET + i);
					printf("��");
				}
				else
				{
					MoveCursorTo(nTmp + SUBWINDOW_WIDTH_OFFSET, SUBWINDOW_HEIGHT_OFFSET + i);
					printf("  ");
				}
				nTmp += 2;
			}
		}
	}
	else
	{
		TextColor(LIGHTGRAY, BLACK);
		// ���� â �����
		for (int i = 0; i < SUBWINDOW_HEIGHT; ++i)
		{
			int nTmp = 0;

			for (int j = 0; j < SUBWINDOW_WIDTH; ++j)
			{
				MoveCursorTo(nTmp + SUBWINDOW_WIDTH_OFFSET, SUBWINDOW_HEIGHT_OFFSET + i);
				printf("  ");

				nTmp += 2;
			}
		}
	}
}

void SubWindowRefresh()
{
	TextColor(LIGHTGRAY, BLACK);
	// ���� â �����
	for (int i = 2; i < SUBWINDOW_HEIGHT - 2; ++i)
	{
		int nTmp = 2;

		for (int j = 2; j < SUBWINDOW_WIDTH - 2; ++j)
		{
			MoveCursorTo(nTmp + SUBWINDOW_WIDTH_OFFSET, SUBWINDOW_HEIGHT_OFFSET + i);
			printf("  ");

			nTmp += 2;
		}
	}
}