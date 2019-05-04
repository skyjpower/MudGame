#pragma once

#include "Init.h"
#include "Global.h"

int Init(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps)
{
	// ĳ�� Init
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		ppECastle[i] = (PECASTLE)malloc(sizeof(ECASTLE));
		ppECastle[i]->m_nReward = 0;
		ppECastle[i]->m_tStartPos.x = 0;
		ppECastle[i]->m_tStartPos.y = 0;
		ppECastle[i]->m_tDestPos.x = 0;
		ppECastle[i]->m_tDestPos.y = 0;
		ppECastle[i]->m_tKeyPos.x = 0;
		ppECastle[i]->m_tKeyPos.y = 0;

		// �� ����Ʈ �ʱ�ȭ
		ppECastle[i]->m_tDoorPosList = (PDLIST)malloc(sizeof(DLIST));
		ppECastle[i]->m_tDoorPosList->m_pBegin = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pEnd = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pNext = ppECastle[i]->m_tDoorPosList->m_pEnd;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pPrev = ppECastle[i]->m_tDoorPosList->m_pBegin;
		ppECastle[i]->m_tDoorPosList->m_nSize = 0;
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pPrev = NULL;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pNext = NULL;

		// ���� ����Ʈ �ʱ�ȭ
		ppECastle[i]->m_tAreaPosList = (PALIST)malloc(sizeof(ALIST));
		ppECastle[i]->m_tAreaPosList->m_pBegin = (PAREA)malloc(sizeof(AREA));
		ppECastle[i]->m_tAreaPosList->m_pEnd = (PAREA)malloc(sizeof(AREA));
		ppECastle[i]->m_tAreaPosList->m_pBegin->m_pNext = ppECastle[i]->m_tAreaPosList->m_pEnd;
		ppECastle[i]->m_tAreaPosList->m_pEnd->m_pPrev = ppECastle[i]->m_tAreaPosList->m_pBegin;
		ppECastle[i]->m_tAreaPosList->m_nSize = 0;
		ppECastle[i]->m_tAreaPosList->m_pBegin->m_pPrev = NULL;
		ppECastle[i]->m_tAreaPosList->m_pEnd->m_pNext = NULL;

		memset(ppECastle[i]->m_aECastleMap, 0, sizeof(ppECastle[i]->m_aECastleMap));
	}
	// �÷��̾� Init
	pPlayer->m_tPos.x = 0;
	pPlayer->m_tPos.y = 0;
	pPlayer->m_nHaveShip = 0;
	pPlayer->m_nMoney = 100;
	pPlayer->m_nColor = YELLOW;
	pPlayer->m_nSelectSoldier = -1; // �ƹ��͵� ���� ���� ����
	pPlayer->m_nMouseOn = OFF;
	pPlayer->m_tMouse.x = 0;
	pPlayer->m_tMouse.y = 0;
	pPlayer->m_nBattleMapMode = BM_MOVE;
	pPlayer->m_nAreaCount = 0;
	pPlayer->m_tInventory.m_pBegin = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_pEnd = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_nSize = 0;
	pPlayer->m_tInventory.m_pBegin->m_pNext = pPlayer->m_tInventory.m_pEnd;
	pPlayer->m_tInventory.m_pBegin->m_pPrev = NULL;
	pPlayer->m_tInventory.m_pEnd->m_pPrev = pPlayer->m_tInventory.m_pBegin;
	pPlayer->m_tInventory.m_pEnd->m_pNext = NULL;

	strcpy(pPlayer->m_cShape, "��");
	
	// ����� Load
	if (!LoadWorldMap(pPlayer, ppECastle))
	{
		puts("���� �ҷ����� �� �����߽��ϴ�.");
		return 0;
	}

	// �� ���� ���並 ����Ʈ�� ����
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		CheckEnemyCastleArea(ppECastle[i]);

	
	// �÷��̾� ���� Init
	if (!CreatePlayerSoldier(pPlayer))
	{
		puts("�÷��̾��� ������� �ʱ�ȭ �� ������ �����ϴ�.");
		return 0;
	}

	
	// ��Ʋ �� Init
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		ppBattleMaps[i] = (PBATTLEMAP)malloc(sizeof(BATTLEMAP) + 1);

		for (int j = 0; j < TOTAL_SOLDIER_NUM; ++j)
		{
			ppBattleMaps[i]->m_tEnemyStartPos[j].x = 0;
			ppBattleMaps[i]->m_tEnemyStartPos[j].y = 0;
			ppBattleMaps[i]->m_tPlayerStartPos[j].x = 0;
			ppBattleMaps[i]->m_tPlayerStartPos[j].y = 0;
			ppBattleMaps[i]->m_nEnemyCount = 0;
			ppBattleMaps[i]->m_nRewardMin = 100;
			ppBattleMaps[i]->m_nRewardMax = 300;
			ppBattleMaps[i]->m_nCurTurn = TT_PLAYER;
		}
		LoadBattleMap(ppBattleMaps[i], i);
		InitBattleStage(ppBattleMaps[i]);
	}

	return 1;
}

void BasicInit(PPLAYER pPlayer)
{
	// ��Ÿ Ÿ�� ���
	QueryPerformanceCounter(&g_tTime);
	QueryPerformanceFrequency(&g_tSecond);

	// �̺�Ʈ â �ʱ�ȭ
	for (int i = 0; i < EVENT_WINDOW_HEIGHT; ++i)
	{
		for (int j = 0; j < EVENT_WINDOW_WIDTH; ++j)
			if (i == 0
				|| j == 0
				|| i == EVENT_WINDOW_HEIGHT - 1
				|| j == EVENT_WINDOW_WIDTH - 1)
				aEventWindow[i][j] = '1';
	}

	// �������ͽ� â �ʱ�ȭ
	for (int i = 0; i < STATUS_WINDOW_HEIGHT; ++i)
	{
		for (int j = 0; j < STATUS_WINDOW_WIDTH; ++j)
		{
			if (i == 0 || j == 0
				|| i == STATUS_WINDOW_HEIGHT - 1
				|| j == STATUS_WINDOW_WIDTH - 1)
				aStatusWindow[i][j] = '1';
		}
	}
	for (int i = 1; i < STATUS_WINDOW_WIDTH - 1; ++i)
		aStatusWindow[STATUS_WINDOW_HEIGHT - 1][i] = '0';

	// ���� â �ʱ�ȭ
	for (int i = 0; i < SUBWINDOW_HEIGHT; ++i)
	{
		for (int j = 0; j < SUBWINDOW_WIDTH; ++j)
		{
			if (i == 0 || j == 0
				|| i == SUBWINDOW_HEIGHT - 1
				|| j == SUBWINDOW_WIDTH - 1)
				aSubWindow[i][j] = '1';
		}
	}

	// �̺�Ʈ �� �������ͽ� â ���
	CreateStatusWindow();
	StatusWindowRefresh(pPlayer);
}

void CheckEnemyCastleArea(PECASTLE pECastle)
{
	int visit[MAP_HEIGHT_MAX][MAP_WIDTH_MAX] = { 0 };

	POINT queue[QUEUE_MAX_SIZE] = { 0 };
	int nFront = 0, nRear = 1;
	POINT tStart = { pECastle->m_tWorldPos.x, pECastle->m_tWorldPos.y };
	visit[pECastle->m_tWorldPos.x][pECastle->m_tWorldPos.y] = 1;

	queue[nFront] = tStart;

	while (nFront != nRear)
	{
		int qSize = nRear - nFront;
		for (int i = 0; i < qSize; ++i)
		{
			int cur_x = queue[nFront].x;
			int cur_y = queue[nFront].y;
			// pop
			nFront = (nFront + 1) % QUEUE_MAX_SIZE;
			for (int j = 0; j < 4; ++j)
			{
				int next_x = cur_x + xDir[j];
				int next_y = cur_y + yDir[j];

				if (next_x < 0 || next_y < 0 || next_x >= MAP_HEIGHT_MAX || next_y >= MAP_WIDTH_MAX) continue;
				if (aWorldMap[next_x][next_y] != MWT_ECASTLEAREA) continue;
				if (visit[next_x][next_y]) continue;

				POINT tmp = { next_x, next_y };
				visit[next_x][next_y] = 1;
				queue[nRear++] = tmp;
				pECastle->m_tAreaPosList->m_nSize++;

				PAREA pArea = (PAREA)malloc(sizeof(AREA));
				pArea->m_tPos.x = next_x;
				pArea->m_tPos.y = next_y;
				pArea->m_beOccupied = 0;
	
				PAREA pPrev = pECastle->m_tAreaPosList->m_pEnd->m_pPrev;

				pPrev->m_pNext = pArea;
				pArea->m_pPrev = pPrev;

				pArea->m_pNext = pECastle->m_tAreaPosList->m_pEnd;
				pECastle->m_tAreaPosList->m_pEnd->m_pPrev = pArea;

			}
		}
	}
}

int CreatePlayerSoldier(PPLAYER pPlayer)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		pPlayer->m_tSoldiers[i] = CreateSoldier(i, TT_PLAYER, 2);

	return 1;
}

SOLDIER CreateSoldier(int nType, int nTeam, int nUpgrade)
{
	SOLDIER tSoldier;

	tSoldier.m_tPos.x = 0;
	tSoldier.m_tPos.y = 0;

	tSoldier.m_nType = nType;
	tSoldier.m_nTeam = nTeam;
	tSoldier.m_nCurUpgrade = nUpgrade;
	tSoldier.m_bAttackFlag = 0;
	tSoldier.m_bMoveFlag = 0;
	tSoldier.m_bTurn = 1;
	tSoldier.m_nDie = 0;

	tSoldier.m_nMoveRange = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][MOVE];

	tSoldier.m_nAttackMin = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][ATMIN];
	tSoldier.m_nAttackMax = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][ATMAX];
	tSoldier.m_nAttackRange = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][RANGE];

	tSoldier.m_nArmorMin = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][ARMIN];
	tSoldier.m_nArmorMax = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][ARMAX];

	tSoldier.m_nHp = LevelStatusTable[nType][tSoldier.m_nCurUpgrade][HP];
	tSoldier.m_nCurHp = tSoldier.m_nHp;

	tSoldier.m_nUpgradeMax = 3;

	strcpy(tSoldier.m_strName, LevelCharacterNameTable[nType][tSoldier.m_nCurUpgrade]);
	if(nTeam == TT_ENEMY)
		strcpy(tSoldier.m_cShape, LevelEnemyShapeTable[nType][tSoldier.m_nCurUpgrade]);
	else
		strcpy(tSoldier.m_cShape, LevelCharacterShapeTable[nType][tSoldier.m_nCurUpgrade]);
	strcpy(tSoldier.m_strClass, CharacterClassName[nType]);

	if (tSoldier.m_nTeam == TT_PLAYER)
		tSoldier.m_nColor = BROWN;
	else if (tSoldier.m_nTeam == TT_ALLY)
		tSoldier.m_nColor = MAGENTA;
	else if (tSoldier.m_nTeam == TT_ENEMY)
		tSoldier.m_nColor = RED;

	return tSoldier;
}

PSOLDIER PCreateSoldier(int nType, int nTeam, int nUpgrade)
{
	PSOLDIER pSoldier = (PSOLDIER)malloc(sizeof(SOLDIER));

	pSoldier->m_tPos.x = 0;
	pSoldier->m_tPos.y = 0;

	pSoldier->m_nType = nType;
	pSoldier->m_nTeam = nTeam;
	pSoldier->m_nCurUpgrade = 0;

	pSoldier->m_nMoveRange = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][MOVE];

	pSoldier->m_nAttackMin = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ATMIN];
	pSoldier->m_nAttackMax = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ATMAX];
	pSoldier->m_nAttackRange = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][RANGE];

	pSoldier->m_nArmorMin = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ARMIN];
	pSoldier->m_nArmorMax = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][ARMAX];

	pSoldier->m_nHp = LevelStatusTable[nType][pSoldier->m_nCurUpgrade][HP];
	pSoldier->m_nCurHp = pSoldier->m_nHp;

	pSoldier->m_nUpgradeMax = 3;

	strcpy(pSoldier->m_strName, LevelCharacterNameTable[nType][pSoldier->m_nCurUpgrade]);
	strcpy(pSoldier->m_cShape, LevelCharacterShapeTable[nType][pSoldier->m_nCurUpgrade]);
	strcpy(pSoldier->m_strClass, CharacterClassName[nType]);

	if (pSoldier->m_nTeam == TT_PLAYER)
		pSoldier->m_nColor = BROWN;
	else if (pSoldier->m_nTeam == TT_ALLY)
		pSoldier->m_nColor = MAGENTA;
	else if (pSoldier->m_nTeam == TT_ENEMY)
		pSoldier->m_nColor = RED;

	return pSoldier;
}

int LoadWorldMap(PPLAYER pPlayer, PECASTLE* ppECastle)
{
	int nECastleIndex = 0;

	FILE* fp = NULL;

	fp = fopen("NationWide.txt", "rt");
	if (fp == NULL)
	{
		puts("���� ���¿� �����Ͽ����ϴ�.");
		return 0;
	}

	int nX = 0;
	int nY = 0;
	
	while (!feof(fp))
	{
		char cTmp = fgetc(fp);
		if (cTmp == '\n')
		{
			nX++;
			nY = 0;
			continue;
		}
		else if (cTmp == MWT_PLAYERPOS)
		{
			tStartPos.x = nX;
			tStartPos.y = nY;
			pPlayer->m_tWorldPos.x = nX;
			pPlayer->m_tWorldPos.y = nY;
			cTmp = MWT_PCASTLEAREA;
			pPlayer->m_nAreaCount++;
		}
		else if (cTmp == MWT_PCASTLEAREA)
			pPlayer->m_nAreaCount++;
		else if (cTmp == MWT_ECASTLE)
		{
			ppECastle[nECastleIndex]->m_tWorldPos.x = nX;
			ppECastle[nECastleIndex]->m_tWorldPos.y = nY;
		
			if (!LoadECastleMap(ppECastle[nECastleIndex], FileName[nECastleIndex]))
			{
				puts("ĳ�� �� �ҷ����� ����!!");
				return 0;
			}
			nECastleIndex++;
		}

		aWorldMap[nX][nY++] = cTmp;
	}

	fclose(fp);

	return 1;
}

int LoadECastleMap(PECASTLE pECastle, const char* FileName)
{
	FILE* fp = NULL;

	fp = fopen(FileName, "rt");
	if (fp == NULL)
	{
		puts("���� ���¿� �����Ͽ����ϴ�.");
		return 0;
	}

	int nX = 0;
	int nY = 0;

	while (!feof(fp))
	{
		char cTmp = fgetc(fp);
		if (cTmp == '\n')
		{
			nX++;
			nY = 0;
			continue;
		}
		// �����
		else if (cTmp == MCT_START)
		{
			pECastle->m_tStartPos.x = nX;
			pECastle->m_tStartPos.y = nY;
			cTmp = MCT_GROUND;
		}
		// ������
		else if (cTmp == MCT_DEST)
		{
			pECastle->m_tDestPos.x = nX;
			pECastle->m_tDestPos.y = nY;
		}
		else if (cTmp == MCT_KEY)
		{
			pECastle->m_tKeyPos.x = nX;
			pECastle->m_tKeyPos.y = nY;
		}
		else if (cTmp == MCT_DOOR)
		{
			PDOOR pDoor = (PDOOR)malloc(sizeof(DOOR));
			pDoor->m_tPos.x = nX;
			pDoor->m_tPos.y = nY;
			pDoor->m_nClosed = 1;
			pECastle->m_tDoorPosList->m_nSize++;

			PDOOR pPrev = pECastle->m_tDoorPosList->m_pEnd->m_pPrev;
			pDoor->m_pPrev = pPrev;
			pPrev->m_pNext = pDoor;

			pDoor->m_pNext = pECastle->m_tDoorPosList->m_pEnd;
			pECastle->m_tDoorPosList->m_pEnd->m_pPrev = pDoor;
		}

		pECastle->m_aECastleMap[nX][nY++] = cTmp;
	}

	fclose(fp);

	return 1;
}

int LoadBattleMap(PBATTLEMAP pBattleMap, int nCurFileIndex)
{
	FILE* fp = NULL;
	fp = fopen(BattleMapFileName[nCurFileIndex], "r");

	if (fp == NULL)
	{
		printf("%d�� ° ��Ʋ �� ���� ������ �����߽��ϴ�.\n", nCurFileIndex);
		return 0;
	}
	
	int nX = 0, nY = 0;

	while (!feof(fp))
	{
		char cTmp = fgetc(fp);
		if (cTmp == '\n')
		{
			nX++;
			nY = 0;
			continue;
		}

		if (cTmp == MBT_ESOLDIER_K)
		{
			pBattleMap->m_tEnemyStartPos[SC_KNIGHT].x = nX;
			pBattleMap->m_tEnemyStartPos[SC_KNIGHT].y = nY;
			pBattleMap->m_nEnemyCount++;
			cTmp = MBT_GROUND;
		}
		else if (cTmp == MBT_ESOLDIER_C)
		{
			pBattleMap->m_tEnemyStartPos[SC_CAVALRY].x = nX;
			pBattleMap->m_tEnemyStartPos[SC_CAVALRY].y = nY;
			pBattleMap->m_nEnemyCount++;
			cTmp = MBT_GROUND;
		}
		else if (cTmp == MBT_ESOLDIER_A)
		{
			pBattleMap->m_tEnemyStartPos[SC_ARCHER].x = nX;
			pBattleMap->m_tEnemyStartPos[SC_ARCHER].y = nY;
			pBattleMap->m_nEnemyCount++;
			cTmp = MBT_GROUND;
		}
		else if (cTmp == MBT_PSOLDIER_K)
		{
			pBattleMap->m_tPlayerStartPos[SC_KNIGHT].x = nX;
			pBattleMap->m_tPlayerStartPos[SC_KNIGHT].y = nY;
			cTmp = MBT_GROUND;
		}
		else if (cTmp == MBT_PSOLDIER_C)
		{
			pBattleMap->m_tPlayerStartPos[SC_CAVALRY].x = nX;
			pBattleMap->m_tPlayerStartPos[SC_CAVALRY].y = nY;
			cTmp = MBT_GROUND;
		}
		else if (cTmp == MBT_PSOLDIER_A)
		{
			pBattleMap->m_tPlayerStartPos[SC_ARCHER].x = nX;
			pBattleMap->m_tPlayerStartPos[SC_ARCHER].y = nY;
			cTmp = MBT_GROUND;
		}

		pBattleMap->m_aBattleMap[nX][nY++] = cTmp;
	}
}

void InitBattleStage(PBATTLEMAP pBattleMap)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		// �� �� �ʱ�ȭ
		pBattleMap->m_tEnemy[i] = CreateSoldier(i, TT_ENEMY, 0);
		pBattleMap->m_tEnemy[i].m_tPos.x = pBattleMap->m_tEnemyStartPos[i].x;
		pBattleMap->m_tEnemy[i].m_tPos.y = pBattleMap->m_tEnemyStartPos[i].y;
	}
}

void SavePlayer(PPLAYER pPlayer)
{
	FILE* fp = NULL;
	fp = fopen("Player.ply", "wb");

	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return;
	}

	// �÷��̾� ĳ���� ��ġ
	fwrite(&pPlayer->m_tPos, sizeof(POINT), 1, fp);
	// �÷��̾� ����� ��ġ
	fwrite(&pPlayer->m_tWorldPos, sizeof(POINT), 1, fp);
	// ���� �ݾ�
	fwrite(&pPlayer->m_nMoney, sizeof(int), 1, fp);
	// ����
	fwrite(&pPlayer->m_nColor, sizeof(int), 1, fp);
	// ���� ����� �� �ִ� �� ����
	fwrite(&pPlayer->m_nHaveShip, sizeof(int), 1, fp);
	// ���õ� ����
	fwrite(&pPlayer->m_nSelectSoldier, sizeof(int), 1, fp);
	// ��Ʋ�� ���
	fwrite(&pPlayer->m_nBattleMapMode, sizeof(int), 1, fp);
	// �÷��̾� ����
	fwrite(&pPlayer->m_nAreaCount, sizeof(int), 1, fp);
	// ���콺 Ŀ��
	fwrite(&pPlayer->m_tMouse, sizeof(MOUSE), 1, fp);
	// ���콺 �� ����
	fwrite(&pPlayer->m_nMouseOn, sizeof(int), 1, fp);
	// ���
	fwrite(pPlayer->m_cShape, sizeof(char), 3, fp);
	// �����
	fwrite(pPlayer->m_tSoldiers, sizeof(SOLDIER), 3, fp);
	// �κ��丮�� ������ ���� ����
	fwrite(&pPlayer->m_tInventory.m_nSize, sizeof(int), 1, fp);

	// �κ��丮�� �����۵� ����
	PITEM pItem = pPlayer->m_tInventory.m_pBegin->m_pNext;
	while (pItem != pPlayer->m_tInventory.m_pEnd)
	{
		PITEM pNext = pItem->m_pNext;
		fwrite(pItem, sizeof(ITEM), 1, fp);
		pItem = pItem->m_pNext;
	}
}

void SaveWorldMap()
{
	FILE *fp = NULL;
	fp = fopen("WorldMap.map", "wb");
	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return;
	}

	// ����� ����
	fwrite(aWorldMap, MAP_WIDTH_MAX * MAP_HEIGHT_MAX, 1, fp);
}


void SaveECastleMap(PECASTLE * ppECastleMaps)
{
	FILE* fp = NULL;
	fp = fopen("ECastleMaps.map", "wb");
	if(fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return;
	}

	// ĳ���� ����
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		// ����� ��ǥ
		fwrite(&ppECastleMaps[i]->m_tWorldPos, sizeof(POINT), 1, fp);
		// ���� ��ǥ
		fwrite(&ppECastleMaps[i]->m_tStartPos, sizeof(POINT), 1, fp);
		// ������ ��ǥ
		fwrite(&ppECastleMaps[i]->m_tDestPos, sizeof(POINT), 1, fp);
		// ���� ��ǥ
		fwrite(&ppECastleMaps[i]->m_tKeyPos, sizeof(POINT), 1, fp);
		// map
		fwrite(ppECastleMaps[i]->m_aECastleMap, sizeof(char) * CASTLE_HEIGHT_MAX * CASTLE_WIDTH_MAX, 1, fp);
		// ����
		fwrite(&ppECastleMaps[i]->m_nReward, sizeof(int), 1, fp);

		// ���� ����Ʈ ���� ����
		fwrite(&ppECastleMaps[i]->m_tDoorPosList->m_nSize, sizeof(int), 1, fp);
		// ���� ����
		PDOOR pDoor = ppECastleMaps[i]->m_tDoorPosList->m_pBegin->m_pNext;
		for (int j = 0; j < ppECastleMaps[i]->m_tDoorPosList->m_nSize; ++j)
		{
			fwrite(pDoor, sizeof(DOOR), 1, fp);
			pDoor = pDoor->m_pNext;
		}

		// ���� ���� ����
		fwrite(&ppECastleMaps[i]->m_tAreaPosList->m_nSize, sizeof(int), 1, fp);
		// ���� ����
		PAREA pArea = ppECastleMaps[i]->m_tAreaPosList->m_pBegin->m_pNext;
		for (int j = 0; j < ppECastleMaps[i]->m_tAreaPosList->m_nSize; ++j)
		{
			fwrite(pArea, sizeof(AREA), 1, fp);
			pArea = pArea->m_pNext;
		}
	}
}

void SaveBattleMaps(PBATTLEMAP * ppBattleMaps)
{
	FILE* fp = NULL;
	fp = fopen("BattleMaps.map", "wb");
	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return;
	}

	// ��Ʋ�� ����
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		// ���� ��
		fwrite(&ppBattleMaps[i]->m_nEnemyCount, sizeof(int), 1, fp);

		// ���� ��ŸƮ ������
		fwrite(ppBattleMaps[i]->m_tEnemyStartPos, sizeof(POINT), 3, fp);

		// �Ʊ� ��ŸƮ ������
		fwrite(ppBattleMaps[i]->m_tPlayerStartPos, sizeof(POINT), 3, fp);

		// ���� ����
		fwrite(ppBattleMaps[i]->m_tEnemy, sizeof(SOLDIER), 3, fp);

		// ���� ��
		fwrite(ppBattleMaps[i]->m_nCurTurn, sizeof(int), 1, fp);

		// ���� �ּ�
		fwrite(ppBattleMaps[i]->m_nRewardMin, sizeof(int), 1, fp);

		// ���� �ִ�
		fwrite(ppBattleMaps[i]->m_nRewardMax, sizeof(int), 1, fp);

		// ��
		fwrite(ppBattleMaps[i]->m_aBattleMap, sizeof(char) * BATTLE_HEGIHT_MAX * BATTLE_WIDTH_MAX, 1, fp);
	}		
}

int LoadPlayer(PPLAYER pPlayer)
{
	FILE* fp = NULL;
	fp = fopen("Player.ply", "rb");

	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return FALSE;
	}

	// �÷��̾� ĳ���� ��ġ
	fread(&pPlayer->m_tPos, sizeof(POINT), 1, fp);
	// �÷��̾� ����� ��ġ
	fread(&pPlayer->m_tWorldPos, sizeof(POINT), 1, fp);
	// ���� �ݾ�
	fread(&pPlayer->m_nMoney, sizeof(int), 1, fp);
	// ����
	fread(&pPlayer->m_nColor, sizeof(int), 1, fp);
	// ���� ����� �� �ִ� �� ����
	fread(&pPlayer->m_nHaveShip, sizeof(int), 1, fp);
	// ���õ� ����
	fread(&pPlayer->m_nSelectSoldier, sizeof(int), 1, fp);
	// ��Ʋ�� ���
	fread(&pPlayer->m_nBattleMapMode, sizeof(int), 1, fp);
	// �÷��̾� ����
	fread(&pPlayer->m_nAreaCount, sizeof(int), 1, fp);
	// ���콺 Ŀ��
	fread(&pPlayer->m_tMouse, sizeof(MOUSE), 1, fp);
	// ���콺 �� ����
	fread(&pPlayer->m_nMouseOn, sizeof(int), 1, fp);
	// ���
	fread(pPlayer->m_cShape, sizeof(char), 3, fp);
	// �����
	fread(pPlayer->m_tSoldiers, sizeof(SOLDIER), 3, fp);

	// �κ��丮 �ʱ�ȭ
	fread(&pPlayer->m_tInventory.m_nSize, sizeof(int), 1, fp);
	pPlayer->m_tInventory.m_pBegin = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_pEnd = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_pBegin->m_pPrev = NULL;
	pPlayer->m_tInventory.m_pBegin->m_pNext = pPlayer->m_tInventory.m_pEnd;
	pPlayer->m_tInventory.m_pEnd->m_pNext = NULL;
	pPlayer->m_tInventory.m_pEnd->m_pPrev = pPlayer->m_tInventory.m_pBegin;

	// �κ��丮�� �����۵� ����
	for (int i = 0; i < pPlayer->m_tInventory.m_nSize; ++i)
	{
		PITEM pItem = (PITEM)malloc(sizeof(ITEM));
		fread(pItem, sizeof(ITEM), 1, fp);

		PITEM pPrev = pPlayer->m_tInventory.m_pEnd->m_pPrev;
		pPlayer->m_tInventory.m_pEnd->m_pPrev = pItem;
		pItem->m_pNext = pPlayer->m_tInventory.m_pEnd;

		pItem->m_pPrev = pPrev;
		pPrev->m_pNext = pItem;
	}

	return TRUE;
}

int LoadWorld()
{
	FILE *fp = NULL;
	fp = fopen("WorldMap.map", "rb");
	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return;
	}

	// ����� �ε�
	fread(aWorldMap, MAP_WIDTH_MAX * MAP_HEIGHT_MAX, 1, fp);
}

int LoadECastles(PECASTLE* ppECastleMaps)
{
	FILE* fp = NULL;
	fp = fopen("ECastleMaps.map", "rb");
	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return FALSE;
	}

	// ĳ���� �о����
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		ppECastleMaps[i] = (PECASTLE)malloc(sizeof(ECASTLE));
		// ����� ��ǥ
		fread(&ppECastleMaps[i]->m_tWorldPos, sizeof(POINT), 1, fp);
		// ���� ��ǥ
		fread(&ppECastleMaps[i]->m_tStartPos, sizeof(POINT), 1, fp);
		// ������ ��ǥ
		fread(&ppECastleMaps[i]->m_tDestPos, sizeof(POINT), 1, fp);
		// ���� ��ǥ
		fread(&ppECastleMaps[i]->m_tKeyPos, sizeof(POINT), 1, fp);
		// map
		fread(ppECastleMaps[i]->m_aECastleMap, sizeof(char) * CASTLE_HEIGHT_MAX * CASTLE_WIDTH_MAX, 1, fp);
		// ����
		fread(&ppECastleMaps[i]->m_nReward, sizeof(int), 1, fp);

		// ���� ����Ʈ ���� ����
		ppECastleMaps[i]->m_tDoorPosList = (PDLIST)malloc(sizeof(DLIST));
		fread(&ppECastleMaps[i]->m_tDoorPosList->m_nSize, sizeof(int), 1, fp);

		// ���� �о����
		ppECastleMaps[i]->m_tDoorPosList->m_pBegin = (PDOOR)malloc(sizeof(DOOR));
		ppECastleMaps[i]->m_tDoorPosList->m_pEnd = (PDOOR)malloc(sizeof(DOOR));
		ppECastleMaps[i]->m_tDoorPosList->m_pBegin->m_pPrev = NULL;
		ppECastleMaps[i]->m_tDoorPosList->m_pBegin->m_pNext = ppECastleMaps[i]->m_tDoorPosList->m_pEnd;
		ppECastleMaps[i]->m_tDoorPosList->m_pEnd->m_pNext = NULL;
		ppECastleMaps[i]->m_tDoorPosList->m_pEnd->m_pPrev = ppECastleMaps[i]->m_tDoorPosList->m_pBegin;
		
		for (int j = 0; j < ppECastleMaps[i]->m_tDoorPosList->m_nSize; ++j)
		{
			PDOOR pDoor = (PDOOR)malloc(sizeof(DOOR));
			fread(pDoor, sizeof(DOOR), 1, fp);
			
			PDOOR pPrev = ppECastleMaps[i]->m_tDoorPosList->m_pEnd->m_pPrev;
			pDoor->m_pNext = ppECastleMaps[i]->m_tDoorPosList->m_pEnd;
			ppECastleMaps[i]->m_tDoorPosList->m_pEnd->m_pPrev = pDoor;

			pPrev->m_pNext = pDoor;
			pDoor->m_pPrev = pPrev;
		}

		// ���� ���� �о����
		ppECastleMaps[i]->m_tAreaPosList = (PAREA)malloc(sizeof(AREA));
		fread(&ppECastleMaps[i]->m_tAreaPosList->m_nSize, sizeof(int), 1, fp);

		// ���� �о����
		ppECastleMaps[i]->m_tAreaPosList->m_pBegin = (PAREA)malloc(sizeof(AREA));
		ppECastleMaps[i]->m_tAreaPosList->m_pEnd = (PAREA)malloc(sizeof(AREA));
		ppECastleMaps[i]->m_tAreaPosList->m_pBegin->m_pPrev = NULL;
		ppECastleMaps[i]->m_tAreaPosList->m_pBegin->m_pNext = ppECastleMaps[i]->m_tAreaPosList->m_pEnd;
		ppECastleMaps[i]->m_tAreaPosList->m_pEnd->m_pNext = NULL;
		ppECastleMaps[i]->m_tAreaPosList->m_pEnd->m_pPrev = ppECastleMaps[i]->m_tAreaPosList->m_pBegin;

		for (int j = 0; j < ppECastleMaps[i]->m_tAreaPosList->m_nSize; ++j)
		{
			PAREA pArea = (PAREA)malloc(sizeof(AREA));
			fread(pArea, sizeof(AREA), 1, fp);
			
			PAREA pPrev = ppECastleMaps[i]->m_tAreaPosList->m_pEnd->m_pPrev;
			pArea->m_pNext = ppECastleMaps[i]->m_tAreaPosList->m_pEnd;
			ppECastleMaps[i]->m_tAreaPosList->m_pEnd->m_pPrev = pArea;

			pArea->m_pPrev = pPrev;
			pPrev->m_pNext = pArea;
		}
	}
		
	return TRUE;
}

int LoadBattleMaps(PBATTLEMAP * ppBattleMaps)
{
	FILE* fp = NULL;
	fp = fopen("BattleMaps.map", "wb");
	if (fp == NULL)
	{
		puts("ERROR) ���̺� ���� ���� ����");
		return FALSE;
	}

	// ��Ʋ�� ����
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		ppBattleMaps[i] = (PBATTLEMAP)malloc(sizeof(BATTLEMAP));
		
		// ���� ��
		fread(&ppBattleMaps[i]->m_nEnemyCount, sizeof(int), 1, fp);

		// ���� ��ŸƮ ������
		fread(ppBattleMaps[i]->m_tEnemyStartPos, sizeof(POINT), 3, fp);

		// �Ʊ� ��ŸƮ ������
		fread(ppBattleMaps[i]->m_tPlayerStartPos, sizeof(POINT), 3, fp);

		// ���� ����
		fread(ppBattleMaps[i]->m_tEnemy, sizeof(SOLDIER), 3, fp);

		// ���� ��
		fread(ppBattleMaps[i]->m_nCurTurn, sizeof(int), 1, fp);

		// ���� �ּ�
		fread(ppBattleMaps[i]->m_nRewardMin, sizeof(int), 1, fp);

		// ���� �ִ�
		fread(ppBattleMaps[i]->m_nRewardMax, sizeof(int), 1, fp);

		// ��
		fread(ppBattleMaps[i]->m_aBattleMap, sizeof(char) * BATTLE_HEGIHT_MAX * BATTLE_WIDTH_MAX, 1, fp);
	}
	


	return TRUE;
}



void ConsoleInit()
{
	// �ܼ� â ũ��
	system("mode con cols=150 lines=45");

	// Ŀ�� ������ �����ִ� �ڵ�
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int MainMenuScene()
{
	int nMenu = MT_NEW;
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT);
	printf("1. �����ϱ�\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 2);
	printf("2. �̾��ϱ�\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 4);
	printf("3. ����\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 8);
	printf("���Ͻô� �޴��� ������ �� SPACE�� ��������...");
	
	MOUSE mouse;
	mouse.x = MAINMENU_HEIGHT;
	mouse.y = MAINMENU_WIDTH - 4;
	MoveCursorTo(mouse.y, mouse.x);

	// �޴� ����
	while (1)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (nMenu > MT_NEW)
			{
				nMenu--;
				mouse.x -= 2;
			}
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (nMenu < MT_EXIT)
			{
				nMenu++;
				mouse.x += 2;
			}
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			return nMenu;

		MoveCursorTo(mouse.y, mouse.x);
		printf("��");

		// Refresh
		for (int i = 0; i < MT_EXIT; ++i)
		{
			if (mouse.x != MAINMENU_HEIGHT + (i * 2) || mouse.y != MAINMENU_WIDTH - 4)
			{
				MoveCursorTo(MAINMENU_WIDTH - 4, MAINMENU_HEIGHT + (i * 2));
				printf("  ");
			}
		}
		Sleep(33);
	}
}
