#pragma once
#include "Game.h"
#include "Type.h"
#include "LevelTable.h"

const int MOVE = 0, ATMIN = 1, ATMAX = 2, RANGE = 3, ARMIN = 4, ARMAX = 5, HP = 6;

typedef struct _tagSoldier
{
	int m_nMoveRange; // 움직임 가능

	int m_nAttackMin;	// 공격력 최소
	int m_nAttackMax;	// 공격력 최대
	int m_nAttackRange; // 공격 범위

	int m_nArmorMin; // 방어력 최소
	int m_nArmorMax; // 방어력 최대

	int m_nCurHp;	// 현재 체력
	int m_nHp;		// 최대 체력

	int m_nCurUpgrade;	// 현재 업그레이드 수준
	int m_nUpgradeMax;	// 업그레이드 최대 횟수

	int m_nDie;	// 죽었는 지 여부

	char	m_strName[12];		// 이름
	char	m_cShape[3];		// 모양

	int		m_nType;			// 타입 ( 기병, 보병, 궁병 )
	int		m_nColor;			// 색
	int		m_nTeam;			// 플레이어 / 적군 / 동맹 판별

	_tagSoldier(int nType, int nTeam, int nUpgrade) :
		m_nCurUpgrade(nUpgrade),
		m_nType(nType),
		m_nTeam(nTeam),
		m_nDie(false)
	{
		switch (nType)
		{
		case SC_KNIGHT:
			m_nMoveRange = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][MOVE];

			m_nAttackMin = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][ATMIN];
			m_nAttackMax = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][ATMAX];
			m_nAttackRange = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][RANGE];

			m_nArmorMin = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][ARMIN];
			m_nArmorMax = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][ARMAX];

			m_nHp = LevelStatusTable[SC_KNIGHT][m_nCurUpgrade][HP];
			m_nCurHp = m_nHp;
				
			m_nCurUpgrade = 0;
			m_nUpgradeMax = 3;

			strcpy(m_strName, LevelCharacterNameTable[SC_KNIGHT][m_nCurUpgrade]);

			if (m_nTeam == TT_PLAYER)
				m_nColor = BLUE;
			else if (m_nTeam == TT_ALLY)
				m_nColor = GREEN;
			else if (m_nTeam == TT_ENEMY)
				m_nColor = RED;

			strcpy(m_cShape, LevelCharacterShapeTable[SC_KNIGHT][m_nCurUpgrade]);

			break;
		case SC_CAVALRY:
			m_nMoveRange = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][MOVE];

			m_nAttackMin = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][ATMIN];
			m_nAttackMax = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][ATMAX];
			m_nAttackRange = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][RANGE];

			m_nArmorMin = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][ARMIN];
			m_nArmorMax = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][ARMAX];

			m_nHp = LevelStatusTable[SC_CAVALRY][m_nCurUpgrade][HP];
			m_nCurHp = m_nHp;

			m_nCurUpgrade = 0;
			m_nUpgradeMax = 3;

			strcpy(m_strName, LevelCharacterNameTable[SC_CAVALRY][m_nCurUpgrade]);

			if (m_nTeam == TT_PLAYER)
				m_nColor = BLUE;
			else if (m_nTeam == TT_ALLY)
				m_nColor = GREEN;
			else if (m_nTeam == TT_ENEMY)
				m_nColor = RED;

			strcpy(m_cShape, LevelCharacterShapeTable[SC_CAVALRY][m_nCurUpgrade]);
			break;
		case SC_ARCHER:
			m_nMoveRange = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][MOVE];

			m_nAttackMin = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][ATMIN];
			m_nAttackMax = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][ATMAX];
			m_nAttackRange = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][RANGE];

			m_nArmorMin = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][ARMIN];
			m_nArmorMax = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][ARMAX];

			m_nHp = LevelStatusTable[SC_ARCHER][m_nCurUpgrade][HP];
			m_nCurHp = m_nHp;

			m_nCurUpgrade = 0;
			m_nUpgradeMax = 3;

			strcpy(m_strName, LevelCharacterNameTable[SC_ARCHER][m_nCurUpgrade]);

			if (m_nTeam == TT_PLAYER)
				m_nColor = BLUE;
			else if (m_nTeam == TT_ALLY)
				m_nColor = GREEN;
			else if (m_nTeam == TT_ENEMY)
				m_nColor = RED;

			strcpy(m_cShape, LevelCharacterShapeTable[SC_ARCHER][m_nCurUpgrade]);
			break;
		default:
			puts("ERROR !!");
			break;
		}
	}

	// 공격하기
	void SoldierAttack(const SOLDIER* tEnemy)
	{
		
	}

	// 방어하기
	void SoldierDefence(const SOLDIER* tEnemy)
	{

	}

	// 업그레이드 함수
	int SoldierUpgrade()
	{
		// 업그레이드 불가능
		if (m_nCurUpgrade + 1 > m_nUpgradeMax)
		{
			// Cant Upgrade Message
			return 0;
		}

		// 업그레이드
		++m_nCurUpgrade;

		// 업그레이드 수치 적용
		switch (m_nType)
		{
		case SC_KNIGHT:

			break;
		case SC_CAVALRY:

			break;

		case SC_ARCHER:

			break;
		}

		m_nCurHp = m_nHp;
	}

}SOLDIER, *PSOLDIER;

typedef struct _tagList
{
	SOLDIER*	m_pBegin;
	SOLDIER*	m_pEnd;
	int			m_nSize;

}LIST, *PLIST;

typedef struct _tagPlayer
{
	POINT m_tPos; // 플레이어 위치
	int m_nMoney; // 소지 금액

	PLIST m_pSoldiers; // 리스트
};
