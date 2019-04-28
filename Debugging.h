#pragma once
#include "Game.h"

void DebugSoliderList(PPLAYER pPlayer)
{
	for (int i = 0; i < TOTAL_SOLDIER_NUM; ++i)
	{
		printf("=============================================================\n");
		printf("�̸�	: %s\n", pPlayer->pSoldiers[i]->m_strName);
		printf("Ŭ����: %s\n", pPlayer->pSoldiers[i]->m_strClass);
		printf("��� : %s\n", pPlayer->pSoldiers[i]->m_cShape);
		printf("�̵� ���� ���� : %d\n", pPlayer->pSoldiers[i]->m_nMoveRange);
		printf("ü�� : %d\n", pPlayer->pSoldiers[i]->m_nHp);
		printf("���ݷ� : %d ~ %d\n", pPlayer->pSoldiers[i]->m_nAttackMin, pPlayer->pSoldiers[i]->m_nAttackMax);
		printf("���� : %d ~ %d\n", pPlayer->pSoldiers[i]->m_nArmorMin, pPlayer->pSoldiers[i]->m_nArmorMax);
		printf("���� ���� : %d\n", pPlayer->pSoldiers[i]->m_nAttackRange);
		printf("���׷��̵� ���� : %d\n", pPlayer->pSoldiers[i]->m_nCurUpgrade);
	}
}
