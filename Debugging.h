#pragma once
#include "Game.h"

void DebugSoliderList(PPLAYER pPlayer)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		printf("=============================================================\n");
		printf("이름	: %s\n", pPlayer->pSoldiers[i]->m_strName);
		printf("클래스: %s\n", pPlayer->pSoldiers[i]->m_strClass);
		printf("모양 : %s\n", pPlayer->pSoldiers[i]->m_cShape);
		printf("이동 가능 범위 : %d\n", pPlayer->pSoldiers[i]->m_nMoveRange);
		printf("체력 : %d\n", pPlayer->pSoldiers[i]->m_nHp);
		printf("공격력 : %d ~ %d\n", pPlayer->pSoldiers[i]->m_nAttackMin, pPlayer->pSoldiers[i]->m_nAttackMax);
		printf("방어력 : %d ~ %d\n", pPlayer->pSoldiers[i]->m_nArmorMin, pPlayer->pSoldiers[i]->m_nArmorMax);
		printf("공격 범위 : %d\n", pPlayer->pSoldiers[i]->m_nAttackRange);
		printf("업그레이드 상태 : %d\n", pPlayer->pSoldiers[i]->m_nCurUpgrade);
	}
}
