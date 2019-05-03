#include "Init.h"
#include "Debugging.h"
#include "Render.h"
#include "Update.h"
#include "Global.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc();
	
	srand((unsigned int)time(0)); // ����

	// �÷��̾�
	PLAYER tPlayer;
	// ĳ��
	PECASTLE pECastles[TOTAL_ECASTLE_NUM];
	// ��Ʋ��
	PBATTLEMAP pBattleMaps[TOTAL_BATTLEMAP_NUM];
	// ��Ʋ�� ���� �÷���
	int nBattleEnd = 0;

	if (!Init(&tPlayer, pECastles, pBattleMaps))
	{
		puts("ERROR) �ʱ�ȭ ����");
		return 0;
	}

	if(DEBUG_MODE)
		DebugSoliderList(&tPlayer);

	StatusWindowRefresh(&tPlayer);

	// PLAY
	while (!g_gameOver)
	{
		// ��ŸŸ�� ���
		CalcDeltaTime();

		// �����
		if (g_gameMode == MM_WORLDMAP)
		{
			DrawAll(&tPlayer);

			// Update
			Update(&tPlayer, &pECastles, pBattleMaps);

			// �׸���
			RenderWorldMap(&tPlayer);

			// ���� ¡��
			CollectionTaxFromCastle(&tPlayer);
		}

		// ��(�̷�)
		else if (g_gameMode == MM_CASTLEMAP)
		{
			DrawECastle(&tPlayer, pECastles[g_nEnableStage]);

			// Update
			UpdateInCastle(&tPlayer, pECastles[g_nEnableStage]);

			// �׸���
			RenderECastleMap(&tPlayer, pECastles[g_nEnableStage]);
		}

		// ��Ʋ��
		else if (g_gameMode == MM_BATTLEMAP)
		{
			DrawBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// ������� ��
			if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_PLAYER)
				UpdateInBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// �� ���� ��� AI
			else if (pBattleMaps[g_battleMapIndex]->m_nCurTurn == TT_ENEMY)
				BattleMapEnemyAI(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// �׸���
			RenderBattleMap(&tPlayer, pBattleMaps[g_battleMapIndex]);

			// ��Ʋ�� ���� ���
			if ((nBattleEnd = CheckEndBattleGame(&tPlayer, pBattleMaps[g_battleMapIndex])))
				ChangeBattleMapToWorld(&tPlayer, pBattleMaps[g_battleMapIndex], nBattleEnd);
		}
	}
	
	// ĳ�� free
	for (int i = 0; i < TOTAL_ECASTLE_NUM; ++i)
	{
		PAREA pArea = pECastles[i]->m_tAreaPosList->m_pBegin->m_pNext;
		while (pArea != pECastles[i]->m_tAreaPosList->m_pEnd)
		{
			PAREA pNext = pArea->m_pNext;
			SAFE_DELETE(pArea)
			pArea = pNext;
		}
		SAFE_DELETE(pECastles[i]->m_tAreaPosList->m_pBegin)
		SAFE_DELETE(pECastles[i]->m_tAreaPosList->m_pEnd)
		SAFE_DELETE(pECastles[i]->m_tAreaPosList)

		PDOOR pDoor = pECastles[i]->m_tDoorPosList->m_pBegin->m_pNext;
		while (pDoor != pECastles[i]->m_tDoorPosList->m_pEnd)
		{
			PDOOR pNext = pDoor->m_pNext;
			SAFE_DELETE(pDoor)
			pDoor = pNext;
		}

		SAFE_DELETE(pECastles[i]->m_tDoorPosList->m_pBegin)
		SAFE_DELETE(pECastles[i]->m_tDoorPosList->m_pEnd)
		SAFE_DELETE(pECastles[i]->m_tDoorPosList)

		SAFE_DELETE(pECastles[i])
	}
	
	// ��Ʋ�� free
	for (int i = 0; i < TOTAL_BATTLEMAP_NUM; ++i)
		SAFE_DELETE(pBattleMaps[i])

	// �÷��̾� �κ��丮 free
	PITEM pItem = tPlayer.m_tInventory.m_pBegin->m_pNext;
	while (pItem != tPlayer.m_tInventory.m_pEnd)
	{
		PITEM pNext = pItem->m_pNext;
		SAFE_DELETE(pItem)
		pItem = pNext;
	}
	SAFE_DELETE(tPlayer.m_tInventory.m_pBegin)
	SAFE_DELETE(tPlayer.m_tInventory.m_pEnd)

	_CrtDumpMemoryLeaks();
	return 0;
}