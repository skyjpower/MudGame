#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"
#include "Global.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc();
	
	srand((unsigned int)time(0)); // 씨앗

	// 플레이어
	PLAYER tPlayer;
	// 캐슬
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];
	// 배틀맵
	PBATTLEMAP pBattleMaps[TOTAL_BATTLEMAP_NUM];
	// 배틀맵 종료 플래스
	int nBattleEnd = 0;

	if (!Init(&tPlayer, pECastles, pBattleMaps))
	{
		puts("ERROR) 초기화 실패");
		return 0;
	}

	if(DEBUG_MODE)
		DebugSoliderList(&tPlayer);

	// PLAY
	while (!g_gameOver)
	{
		CalcDeltaTime();
		// 일반
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);
			Update(&tPlayer, &pECastles, pBattleMaps);
			RenderWorldMap(&tPlayer);
		}
		// 성(미로)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[g_nEnableStage]);
			UpdateInCastle(&tPlayer, pECastles[g_nEnableStage]);
			RenderECastleMap(&tPlayer, pECastles[g_nEnableStage]);
		}
		// 배틀
		else if (g_gameMode == MM_BATTLEMAP)
		{
			DrawBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 사용자의 턴
			if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_PLAYER)
				UpdateInBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);
			// 적 턴인 경우 AI
			else if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_ENEMY)
				BattleMapEnemyAI(&tPlayer, pBattleMaps[g_battleMapIndex]);

			RenderBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// 배틀이 끝난 경우
			if ((nBattleEnd = CheckEndBattleGame(&tPlayer, pBattleMaps[g_battleMapIndex])))
			{
				// 플레이어의 승리
				if (nBattleEnd == TT_PLAYER)
					ChangeBattleMapToWorld(&tPlayer, pBattleMaps[g_battleMapIndex], TT_PLAYER);
				// 적군의 승리
				else
					ChangeBattleMapToWorld(&tPlayer, pBattleMaps[g_battleMapIndex], TT_ENEMY);
			}
		}
	}
	
	// 캐슬 free
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		PAREA pArea = pECastles[i]->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastles[i]->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			free(pArea);
			pArea = pNext;
		}
		free(pECastles[i]->m_tAreaPosList->m_pBegin);
		free(pECastles[i]->m_tAreaPosList->m_pEnd);
		free(pECastles[i]->m_tAreaPosList);

		PDOOR pDoor = pECastles[i]->m_tDoorPosList->m_pBegin->m_pNext;
		while (pDoor != pECastles[i]->m_tDoorPosList->m_pEnd)
		{
			PDOOR pNext = pDoor->m_pNext;
			free(pDoor);
			pDoor = pNext;
		}

		free(pECastles[i]->m_tDoorPosList->m_pBegin);
		free(pECastles[i]->m_tDoorPosList->m_pEnd);
		free(pECastles[i]->m_tDoorPosList);

		free(pECastles[i]);
	}
	
	// 배틀맵 free
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
	{
		free(pBattleMaps);
	}

	_CrtDumpMemoryLeaks();
	return 0;
}