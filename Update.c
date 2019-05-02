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

	// 관리자
	if (MANAGE_MODE)
	{
		// 바다 건너기
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pPlayer->m_nHaveShip = !pPlayer->m_nHaveShip;
		}

		// 아군 영역으로 만들기
		if (GetAsyncKeyState('B') & 0x8000)
		{
			if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLEAREA;
			else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_PCASTLEAREA)
				aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_ECASTLEAREA;
		}

		// 시야각
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


	// 적 성인 경우
	if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLE)
	{
		// 캐슬 맵 변화
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

		sprintf(aEventTmpMessage, "공성전 시작 !!");
		EventWindowRenewal();
		ChangeWorldToCastle(pPlayer, ppECastle[g_nEnableStage]);
	}
	// 적 영토인 경우
	else if (aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] == MWT_ECASTLEAREA)
	{
		g_battleMapIndex = rand() % TOTAL_BATTLEMAP_NUM;
		g_battleMapIndex = 2;
		ChangeWorldToBattleMap(pPlayer, ppBattleMaps[g_battleMapIndex]);

		sprintf(aEventTmpMessage, "적과 조우하였습니다.");
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

	// 관리자
	if (MANAGE_MODE)
	{
		// 시야각
		if (GetAsyncKeyState('N') & 0x8000)
		{
			g_sightMode = !g_sightMode;
			Sleep(100);
		}

		// 캐슬 바로 깨기
		if (GetAsyncKeyState('F') & 0x8000)
		{
			pPlayer->m_tPos.x = 1;
			pPlayer->m_tPos.y = 27;
		}
	}


	// 플레이어 위치
	int nPlayerX = pPlayer->m_tPos.x;
	int nPlayerY = pPlayer->m_tPos.y;

	// 장애물 밟음
	if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_OBSTACLE)
	{
		nLoseFlag = 1;
	}
	// 키 획득
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_KEY)
	{
		PDOOR pDoor = pECastle->m_tDoorPosList->m_pBegin->m_pNext;
		PDOOR pEnd = pECastle->m_tDoorPosList->m_pEnd;

		// 문 열기
		while (pDoor != pEnd)
		{
			pECastle->m_aECastleMap[pDoor->m_tPos.x][pDoor->m_tPos.y] = MCT_GROUND;
			pECastle->m_aECastleMap[pECastle->m_tKeyPos.x][pECastle->m_tKeyPos.y] = MCT_GROUND;
			pDoor->m_nClosed = 0;
			pDoor = pDoor->m_pNext;
		}
		EventWindowRenewal("키 획득 ! 성문이 열렸습니다.");
	}
	// 목적지에 다다른 경우 ( 클리어 )
	else if (pECastle->m_aECastleMap[nPlayerX][nPlayerY] == MCT_DEST)
	{
		// 성지 아군화
		aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLE;

		// 영토 아군화
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_PCASTLEAREA;
			free(pArea);
			pArea = pNext;
		}

		// 보상 획득
		pPlayer->m_nMoney += pECastle->m_nReward;

		EventWindowRenewal("공성전 클리어 !");
		// 월드맵으로 이동
		ChangeCastleToWorld(pPlayer, CASTLE_WIN);
	}

	// 패배 판정 시
	if (nLoseFlag)
	{
		// 시작 지점으로 되돌리기
		pPlayer->m_tWorldPos.x = tStartPos.x;
		pPlayer->m_tWorldPos.y = tStartPos.y;

		// 적 영토 회복
		PAREA pArea = pECastle->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastle->m_tAreaPosList->m_pEnd)
		{
			pArea->m_beOccupied = 0;
			aWorldMap[pArea->m_tPos.x][pArea->m_tPos.y] = MWT_ECASTLEAREA;
			pArea = pArea->m_pNext;
		}

		// 성에서 쫓아내기 및 적 영토 회복
		ChangeCastleToWorld(pPlayer, CASTLE_LOSE);
		EventWindowRenewal("패배하였습니다....");
	}
}

void ChangeWorldToCastle(PPLAYER pPlayer, PECASTLE pECastle)
{
	// 위치 조정
	pPlayer->m_tPos.x = pECastle->m_tStartPos.x;
	pPlayer->m_tPos.y = pECastle->m_tStartPos.y;

	// 모드 조정
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
	// 병사 초기화
	for (int i = 0; i < 3; ++i)
	{
		pBattleMap->m_tEnemy[i] = CreateSoldier(i, TT_ENEMY, 0);
		pBattleMap->m_tEnemy[i].m_tPos.x = pBattleMap->m_tEnemyStartPos[i].x;
		pBattleMap->m_tEnemy[i].m_tPos.y = pBattleMap->m_tEnemyStartPos[i].y;
	}
}

void ChangeBattleMapToWorld(PPLAYER pPlayer, PBATTLEMAP pBattleMap, int nWinTeam)
{
	// 플레이어의 승리
	if (nWinTeam == TT_PLAYER)
	{
		// 승리 메세지
		sprintf(aEventTmpMessage, "플레이어의 승리 !");
		EventWindowRenewal();
		DelayTime(1.f);
		// 보상
		int nReward = (rand() % (pBattleMap->m_nRewardMax - pBattleMap->m_nRewardMin)) + pBattleMap->m_nRewardMin;
		pPlayer->m_nMoney += nReward;
		// 보상 메세지
		sprintf(aEventTmpMessage, "%d 원을 획득하였습니다.", nReward);
		EventWindowRenewal();
		DelayTime(1.f);

		// 적 영토 아군화
		aWorldMap[pPlayer->m_tWorldPos.x][pPlayer->m_tWorldPos.y] = MWT_PCASTLEAREA;
	}
	// 적의 승리
	else if (nWinTeam == TT_ENEMY)
	{
		// 패배 메세지
		sprintf(aEventTmpMessage, "전투에서 패배하였습니다..");
		EventWindowRenewal();
		DelayTime(1.f);
		// 위치 초기화
		pPlayer->m_tWorldPos.x = tStartPos.x;
		pPlayer->m_tWorldPos.y = tStartPos.y;
	}

	// 리셋
	BattleMapReset(pBattleMap);

	// 월드맵으로 이동
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
		// 움직인 적이 있는 경우
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
	// 선택
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// 선택하기
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
	
	// 공격 모드
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
	// 공격 데미지 계산
	int nAttack = (rand() % (pAttacker->m_nAttackMax - pAttacker->m_nAttackMin)) + pAttacker->m_nAttackMin;
	// 방어 계산
	int nArmor = (rand() % (pDefender->m_nArmorMax - pDefender->m_nArmorMin)) + pDefender->m_nArmorMin;
	// 들어갈 데미지 계산
	int nDamage = nAttack - nArmor > 0 ? nAttack - nArmor : 0;

	// 데미지 적용
	pDefender->m_nCurHp -= nDamage;

	char AttackerTeam[20] = { 0 };
	char DefenderTeam[20] = { 0 };

	if (pAttacker->m_nTeam == TT_PLAYER)
		strcpy(AttackerTeam, "플레이어");
	else if (pAttacker->m_nTeam == TT_ENEMY)
		strcpy(AttackerTeam, "적");
	else if (pAttacker->m_nTeam == TT_ALLY)
		strcpy(AttackerTeam, "동맹");

	if (pDefender->m_nTeam == TT_PLAYER)
		strcpy(DefenderTeam, "플레이어");
	else if (pDefender->m_nTeam == TT_ENEMY)
		strcpy(DefenderTeam, "적");
	else if (pDefender->m_nTeam == TT_ALLY)
		strcpy(DefenderTeam, "동맹");

	// 메세지
	sprintf(aEventTmpMessage, "%s %s(이)가 %s %s에게 %d 데미지를 입혔습니다.",
		AttackerTeam, pAttacker->m_strName, DefenderTeam, pDefender->m_strName, nDamage);
	EventWindowRenewal();
	DelayTime(1.5f);

	// 방어자가 죽었는 지 확인하기
	if (pDefender->m_nCurHp <= 0)
	{
		sprintf(aEventTmpMessage, "%s %s(이)가 사망하였습니다.",
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
		// 턴이 존재하는 병사가 있는 경우
		if (pPlayer->m_tSoldiers[i].m_bTurn)
			return FALSE;
	}

	return TRUE;
}

void BattleMapEnemyAI(PPLAYER pPlayer, PBATTLEMAP pBattleMap)
{
	DelayTime(3.f);
	pBattleMap->m_nCurTurn = TT_PLAYER;

	sprintf(aEventTmpMessage, "플레이어 차례 !");
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
	// 움직임 가능
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
		// 무브 모드
		if (pPlayer->m_nBattleMapMode == BM_MOVE && !pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_bMoveFlag)
		{
			PSOLDIER pSeletSoldier = &pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier];

			// 이동 확정
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if (pPlayer->m_tMouse.x !=pSeletSoldier->m_tPos.x ||
					pPlayer->m_tMouse.y !=pSeletSoldier->m_tPos.y)
				{
					pSeletSoldier->m_tPos.x = pPlayer->m_tMouse.x;
					pSeletSoldier->m_tPos.y = pPlayer->m_tMouse.y;

					// 움직임 턴을 사용함을 알림
					pSeletSoldier->m_bMoveFlag = ON;

					// 이동한 후 주변에 공격할 수 있는 대상이 없는 경우
					if (!CheckEnemyAroundPlayerSoldier(pSeletSoldier, pBattleMap))
					{
						// 공격 플래그 ON
						pSeletSoldier->m_bAttackFlag = ON;
						// 턴 끝내기
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

			// 현재 내 마우스 커서에 적이 존재하는 지 확인
			for (int i = 0; i < pBattleMap->m_nEnemyCount; ++i)
			{
				// 적 존재
				if (!pBattleMap->m_tEnemy[i].m_nDie
					&& pBattleMap->m_tEnemy[i].m_tPos.x == pPlayer->m_tMouse.x
					&& pBattleMap->m_tEnemy[i].m_tPos.y == pPlayer->m_tMouse.y)
				{
					pSelectEnemy = &pBattleMap->m_tEnemy[i];
					break;
				}
			}

			// 적이 없는 경우
			if (pSelectEnemy == NULL)
			{
				// 메세지
				sprintf(aEventTmpMessage, "해당 지점에 적이 존재하지 않습니다.");
				EventWindowRenewal();
				return;
			}
			// 적이 존재하는 경우 공격!
			else
			{
				// 적이 죽은 경우
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
	// 기사 선택
	if (GetAsyncKeyState('1') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_KNIGHT].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_KNIGHT;

			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_tSoldiers[SC_KNIGHT].m_strName);
			EventWindowRenewal();
			
			// 커서 이동
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_KNIGHT].m_tPos.y;

			// 선택된 것을 표시
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;

			g_moveFlag = 1;
		}
		else
		{
			sprintf(aEventTmpMessage, "이미 턴을 마친 병사입니다.");
			EventWindowRenewal();
		}
	}
	// 기병 선택
	if (GetAsyncKeyState('2') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_CAVALRY].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_CAVALRY;
			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_tSoldiers[SC_CAVALRY].m_strName);
			EventWindowRenewal();

			// 커서 이동
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_CAVALRY].m_tPos.y;

			// 선택된 것을 표시
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;

			g_moveFlag = 1;
		}

		else
		{
			sprintf(aEventTmpMessage, "이미 턴을 마친 병사입니다.");
			EventWindowRenewal();
		}
	}
	// 궁수 선택
	if (GetAsyncKeyState('3') & 0x8000 && pPlayer->m_nMouseOn != ON)
	{
		if (pPlayer->m_tSoldiers[SC_ARCHER].m_bTurn)
		{
			pPlayer->m_nSelectSoldier = SC_ARCHER;
			sprintf(aEventTmpMessage, "[플레이어] %s", pPlayer->m_tSoldiers[SC_ARCHER].m_strName);
			EventWindowRenewal();

			
			// 커서 이동
			pPlayer->m_tMouse.x = pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.x;
			pPlayer->m_tMouse.y = pPlayer->m_tSoldiers[SC_ARCHER].m_tPos.y;

			// 선택된 것을 표시
			memset(aBattleMapRange, 0, sizeof(aBattleMapRange));
			aBattleMapRange[pPlayer->m_tMouse.x][pPlayer->m_tMouse.y] = 1;
			
			g_moveFlag = 1;
		}

		else
		{
			sprintf(aEventTmpMessage, "이미 턴을 마친 병사입니다.");
			EventWindowRenewal();
		}
	}
#pragma endregion

	// 캐릭터 선택
	if ( pPlayer->m_nSelectSoldier >= SC_KNIGHT && 
			pPlayer->m_nSelectSoldier < SC_END &&
			pPlayer->m_tSoldiers[pPlayer->m_nSelectSoldier].m_bTurn)
	{
		SetMousePos(pPlayer, pBattleMap);
	}

	// 병사 움직임
	PlayerSoldierUpdate(pPlayer, pBattleMap);
	
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		// 움직인 적이 있고 공격한 적이 없는 병사인 경우
		if (pPlayer->m_tSoldiers[i].m_bMoveFlag && !pPlayer->m_tSoldiers[i].m_bAttackFlag)
		{
			// 적이 없는 경우
			if (!CheckEnemyAroundPlayerSoldier(&(pPlayer->m_tSoldiers[i]), pBattleMap))
				pPlayer->m_tSoldiers[i].m_bAttackFlag = ON;
		}
	}

	// 플레이어 솔져 체크
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		if (pPlayer->m_tSoldiers[i].m_bTurn)
		{
			if (pPlayer->m_tSoldiers[i].m_bAttackFlag && pPlayer->m_tSoldiers[i].m_bMoveFlag)
				pPlayer->m_tSoldiers[i].m_bTurn = 0;
		}
	}

	// 턴 종료 체크
	if (CheckEndPlayerTurn(pPlayer))
	{
		// 초기화
		for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
		{
			pPlayer->m_tSoldiers[i].m_bAttackFlag = 0;
			pPlayer->m_tSoldiers[i].m_bMoveFlag = 0;
			pPlayer->m_tSoldiers[i].m_bTurn = 1;
		}

		pBattleMap->m_nCurTurn = TT_ENEMY;
		sprintf(aEventTmpMessage, "상대방 차례입니다...");
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
	// 적의 승리
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
	// 플레이어 승리
	if (endFlag) return TT_PLAYER;

	return TT_NONE;
}
