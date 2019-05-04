#pragma once

#include "Init.h"
#include "Global.h"

int Init(PPLAYER pPlayer, PECASTLE* ppECastle, PBATTLEMAP* ppBattleMaps)
{
	// 캐슬 Init
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

		// 문 리스트 초기화
		ppECastle[i]->m_tDoorPosList = (PDLIST)malloc(sizeof(DLIST));
		ppECastle[i]->m_tDoorPosList->m_pBegin = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pEnd = (PDOOR)malloc(sizeof(DOOR));
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pNext = ppECastle[i]->m_tDoorPosList->m_pEnd;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pPrev = ppECastle[i]->m_tDoorPosList->m_pBegin;
		ppECastle[i]->m_tDoorPosList->m_nSize = 0;
		ppECastle[i]->m_tDoorPosList->m_pBegin->m_pPrev = NULL;
		ppECastle[i]->m_tDoorPosList->m_pEnd->m_pNext = NULL;

		// 지역 리스트 초기화
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
	// 플레이어 Init
	pPlayer->m_tPos.x = 0;
	pPlayer->m_tPos.y = 0;
	pPlayer->m_nHaveShip = 0;
	pPlayer->m_nMoney = 100;
	pPlayer->m_nColor = YELLOW;
	pPlayer->m_nSelectSoldier = -1; // 아무것도 선택 안한 상태
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

	strcpy(pPlayer->m_cShape, "●");
	
	// 월드맵 Load
	if (!LoadWorldMap(pPlayer, ppECastle))
	{
		puts("맵을 불러오는 데 실패했습니다.");
		return 0;
	}

	// 적 성의 영토를 리스트에 저장
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		CheckEnemyCastleArea(ppECastle[i]);

	
	// 플레이어 병사 Init
	if (!CreatePlayerSoldier(pPlayer))
	{
		puts("플레이어의 병사들을 초기화 중 오류가 났습니다.");
		return 0;
	}

	
	// 배틀 맵 Init
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
	// 델타 타임 계산
	QueryPerformanceCounter(&g_tTime);
	QueryPerformanceFrequency(&g_tSecond);

	// 이벤트 창 초기화
	for (int i = 0; i < EVENT_WINDOW_HEIGHT; ++i)
	{
		for (int j = 0; j < EVENT_WINDOW_WIDTH; ++j)
			if (i == 0
				|| j == 0
				|| i == EVENT_WINDOW_HEIGHT - 1
				|| j == EVENT_WINDOW_WIDTH - 1)
				aEventWindow[i][j] = '1';
	}

	// 스테이터스 창 초기화
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

	// 서브 창 초기화
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

	// 이벤트 및 스테이터스 창 출력
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
		puts("파일 오픈에 실패하였습니다.");
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
				puts("캐슬 맵 불러오기 실패!!");
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
		puts("파일 오픈에 실패하였습니다.");
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
		// 출발지
		else if (cTmp == MCT_START)
		{
			pECastle->m_tStartPos.x = nX;
			pECastle->m_tStartPos.y = nY;
			cTmp = MCT_GROUND;
		}
		// 목적지
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
		printf("%d번 째 배틀 맵 파일 오픈을 실패했습니다.\n", nCurFileIndex);
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
		// 적 군 초기화
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
		puts("ERROR) 세이브 파일 오픈 실패");
		return;
	}

	// 플레이어 캐슬맵 위치
	fwrite(&pPlayer->m_tPos, sizeof(POINT), 1, fp);
	// 플레이어 월드맵 위치
	fwrite(&pPlayer->m_tWorldPos, sizeof(POINT), 1, fp);
	// 소지 금액
	fwrite(&pPlayer->m_nMoney, sizeof(int), 1, fp);
	// 색상
	fwrite(&pPlayer->m_nColor, sizeof(int), 1, fp);
	// 물을 통과할 수 있는 지 여부
	fwrite(&pPlayer->m_nHaveShip, sizeof(int), 1, fp);
	// 선택된 병사
	fwrite(&pPlayer->m_nSelectSoldier, sizeof(int), 1, fp);
	// 배틀맵 모드
	fwrite(&pPlayer->m_nBattleMapMode, sizeof(int), 1, fp);
	// 플레이어 영역
	fwrite(&pPlayer->m_nAreaCount, sizeof(int), 1, fp);
	// 마우스 커서
	fwrite(&pPlayer->m_tMouse, sizeof(MOUSE), 1, fp);
	// 마우스 온 여부
	fwrite(&pPlayer->m_nMouseOn, sizeof(int), 1, fp);
	// 모양
	fwrite(pPlayer->m_cShape, sizeof(char), 3, fp);
	// 병사들
	fwrite(pPlayer->m_tSoldiers, sizeof(SOLDIER), 3, fp);
	// 인벤토리의 아이템 개수 저장
	fwrite(&pPlayer->m_tInventory.m_nSize, sizeof(int), 1, fp);

	// 인벤토리의 아이템들 저장
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
		puts("ERROR) 세이브 파일 오픈 실패");
		return;
	}

	// 월드맵 저장
	fwrite(aWorldMap, MAP_WIDTH_MAX * MAP_HEIGHT_MAX, 1, fp);
}


void SaveECastleMap(PECASTLE * ppECastleMaps)
{
	FILE* fp = NULL;
	fp = fopen("ECastleMaps.map", "wb");
	if(fp == NULL)
	{
		puts("ERROR) 세이브 파일 오픈 실패");
		return;
	}

	// 캐슬맵 저장
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		// 월드맵 좌표
		fwrite(&ppECastleMaps[i]->m_tWorldPos, sizeof(POINT), 1, fp);
		// 시작 좌표
		fwrite(&ppECastleMaps[i]->m_tStartPos, sizeof(POINT), 1, fp);
		// 목적지 좌표
		fwrite(&ppECastleMaps[i]->m_tDestPos, sizeof(POINT), 1, fp);
		// 열쇠 좌표
		fwrite(&ppECastleMaps[i]->m_tKeyPos, sizeof(POINT), 1, fp);
		// map
		fwrite(ppECastleMaps[i]->m_aECastleMap, sizeof(char) * CASTLE_HEIGHT_MAX * CASTLE_WIDTH_MAX, 1, fp);
		// 보상
		fwrite(&ppECastleMaps[i]->m_nReward, sizeof(int), 1, fp);

		// 도어 리스트 개수 저장
		fwrite(&ppECastleMaps[i]->m_tDoorPosList->m_nSize, sizeof(int), 1, fp);
		// 도어 저장
		PDOOR pDoor = ppECastleMaps[i]->m_tDoorPosList->m_pBegin->m_pNext;
		for (int j = 0; j < ppECastleMaps[i]->m_tDoorPosList->m_nSize; ++j)
		{
			fwrite(pDoor, sizeof(DOOR), 1, fp);
			pDoor = pDoor->m_pNext;
		}

		// 영역 개수 저장
		fwrite(&ppECastleMaps[i]->m_tAreaPosList->m_nSize, sizeof(int), 1, fp);
		// 영역 저장
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
		puts("ERROR) 세이브 파일 오픈 실패");
		return;
	}

	// 배틀맵 저장
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		// 적군 수
		fwrite(&ppBattleMaps[i]->m_nEnemyCount, sizeof(int), 1, fp);

		// 적군 스타트 포지션
		fwrite(ppBattleMaps[i]->m_tEnemyStartPos, sizeof(POINT), 3, fp);

		// 아군 스타트 포지션
		fwrite(ppBattleMaps[i]->m_tPlayerStartPos, sizeof(POINT), 3, fp);

		// 적군 유닛
		fwrite(ppBattleMaps[i]->m_tEnemy, sizeof(SOLDIER), 3, fp);

		// 현재 턴
		fwrite(ppBattleMaps[i]->m_nCurTurn, sizeof(int), 1, fp);

		// 보상 최소
		fwrite(ppBattleMaps[i]->m_nRewardMin, sizeof(int), 1, fp);

		// 보상 최대
		fwrite(ppBattleMaps[i]->m_nRewardMax, sizeof(int), 1, fp);

		// 맵
		fwrite(ppBattleMaps[i]->m_aBattleMap, sizeof(char) * BATTLE_HEGIHT_MAX * BATTLE_WIDTH_MAX, 1, fp);
	}		
}

int LoadPlayer(PPLAYER pPlayer)
{
	FILE* fp = NULL;
	fp = fopen("Player.ply", "rb");

	if (fp == NULL)
	{
		puts("ERROR) 세이브 파일 오픈 실패");
		return FALSE;
	}

	// 플레이어 캐슬맵 위치
	fread(&pPlayer->m_tPos, sizeof(POINT), 1, fp);
	// 플레이어 월드맵 위치
	fread(&pPlayer->m_tWorldPos, sizeof(POINT), 1, fp);
	// 소지 금액
	fread(&pPlayer->m_nMoney, sizeof(int), 1, fp);
	// 색상
	fread(&pPlayer->m_nColor, sizeof(int), 1, fp);
	// 물을 통과할 수 있는 지 여부
	fread(&pPlayer->m_nHaveShip, sizeof(int), 1, fp);
	// 선택된 병사
	fread(&pPlayer->m_nSelectSoldier, sizeof(int), 1, fp);
	// 배틀맵 모드
	fread(&pPlayer->m_nBattleMapMode, sizeof(int), 1, fp);
	// 플레이어 영역
	fread(&pPlayer->m_nAreaCount, sizeof(int), 1, fp);
	// 마우스 커서
	fread(&pPlayer->m_tMouse, sizeof(MOUSE), 1, fp);
	// 마우스 온 여부
	fread(&pPlayer->m_nMouseOn, sizeof(int), 1, fp);
	// 모양
	fread(pPlayer->m_cShape, sizeof(char), 3, fp);
	// 병사들
	fread(pPlayer->m_tSoldiers, sizeof(SOLDIER), 3, fp);

	// 인벤토리 초기화
	fread(&pPlayer->m_tInventory.m_nSize, sizeof(int), 1, fp);
	pPlayer->m_tInventory.m_pBegin = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_pEnd = (PITEM)malloc(sizeof(ITEM));
	pPlayer->m_tInventory.m_pBegin->m_pPrev = NULL;
	pPlayer->m_tInventory.m_pBegin->m_pNext = pPlayer->m_tInventory.m_pEnd;
	pPlayer->m_tInventory.m_pEnd->m_pNext = NULL;
	pPlayer->m_tInventory.m_pEnd->m_pPrev = pPlayer->m_tInventory.m_pBegin;

	// 인벤토리의 아이템들 저장
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
		puts("ERROR) 세이브 파일 오픈 실패");
		return;
	}

	// 월드맵 로드
	fread(aWorldMap, MAP_WIDTH_MAX * MAP_HEIGHT_MAX, 1, fp);
}

int LoadECastles(PECASTLE* ppECastleMaps)
{
	FILE* fp = NULL;
	fp = fopen("ECastleMaps.map", "rb");
	if (fp == NULL)
	{
		puts("ERROR) 세이브 파일 오픈 실패");
		return FALSE;
	}

	// 캐슬맵 읽어오기
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		ppECastleMaps[i] = (PECASTLE)malloc(sizeof(ECASTLE));
		// 월드맵 좌표
		fread(&ppECastleMaps[i]->m_tWorldPos, sizeof(POINT), 1, fp);
		// 시작 좌표
		fread(&ppECastleMaps[i]->m_tStartPos, sizeof(POINT), 1, fp);
		// 목적지 좌표
		fread(&ppECastleMaps[i]->m_tDestPos, sizeof(POINT), 1, fp);
		// 열쇠 좌표
		fread(&ppECastleMaps[i]->m_tKeyPos, sizeof(POINT), 1, fp);
		// map
		fread(ppECastleMaps[i]->m_aECastleMap, sizeof(char) * CASTLE_HEIGHT_MAX * CASTLE_WIDTH_MAX, 1, fp);
		// 보상
		fread(&ppECastleMaps[i]->m_nReward, sizeof(int), 1, fp);

		// 도어 리스트 개수 저장
		ppECastleMaps[i]->m_tDoorPosList = (PDLIST)malloc(sizeof(DLIST));
		fread(&ppECastleMaps[i]->m_tDoorPosList->m_nSize, sizeof(int), 1, fp);

		// 도어 읽어오기
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

		// 영역 개수 읽어오기
		ppECastleMaps[i]->m_tAreaPosList = (PAREA)malloc(sizeof(AREA));
		fread(&ppECastleMaps[i]->m_tAreaPosList->m_nSize, sizeof(int), 1, fp);

		// 영역 읽어오기
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
		puts("ERROR) 세이브 파일 오픈 실패");
		return FALSE;
	}

	// 배틀맵 저장
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		ppBattleMaps[i] = (PBATTLEMAP)malloc(sizeof(BATTLEMAP));
		
		// 적군 수
		fread(&ppBattleMaps[i]->m_nEnemyCount, sizeof(int), 1, fp);

		// 적군 스타트 포지션
		fread(ppBattleMaps[i]->m_tEnemyStartPos, sizeof(POINT), 3, fp);

		// 아군 스타트 포지션
		fread(ppBattleMaps[i]->m_tPlayerStartPos, sizeof(POINT), 3, fp);

		// 적군 유닛
		fread(ppBattleMaps[i]->m_tEnemy, sizeof(SOLDIER), 3, fp);

		// 현재 턴
		fread(ppBattleMaps[i]->m_nCurTurn, sizeof(int), 1, fp);

		// 보상 최소
		fread(ppBattleMaps[i]->m_nRewardMin, sizeof(int), 1, fp);

		// 보상 최대
		fread(ppBattleMaps[i]->m_nRewardMax, sizeof(int), 1, fp);

		// 맵
		fread(ppBattleMaps[i]->m_aBattleMap, sizeof(char) * BATTLE_HEGIHT_MAX * BATTLE_WIDTH_MAX, 1, fp);
	}
	


	return TRUE;
}



void ConsoleInit()
{
	// 콘솔 창 크기
	system("mode con cols=150 lines=45");

	// 커서 깜빡임 없애주는 코드
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

int MainMenuScene()
{
	int nMenu = MT_NEW;
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT);
	printf("1. 새로하기\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 2);
	printf("2. 이어하기\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 4);
	printf("3. 종료\n");
	MoveCursorTo(MAINMENU_WIDTH, MAINMENU_HEIGHT + 8);
	printf("원하시는 메뉴를 선택한 후 SPACE를 누르세요...");
	
	MOUSE mouse;
	mouse.x = MAINMENU_HEIGHT;
	mouse.y = MAINMENU_WIDTH - 4;
	MoveCursorTo(mouse.y, mouse.x);

	// 메뉴 선택
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
		printf("▶");

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
