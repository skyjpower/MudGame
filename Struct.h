﻿#pragma once
#include "Game.h"
#define CASTLE_HEIGHT_MAX 30
#define CASTLE_WIDTH_MAX 30

const int MOVE = 0, ATMIN = 1, ATMAX = 2, RANGE = 3, ARMIN = 4, ARMAX = 5, HP = 6;

// 병사
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
	char	m_strClass[12];		// 직업
	char	m_cShape[3];		// 모양

	int		m_nType;			// 타입 ( 기병, 보병, 궁병 )
	int		m_nColor;			// 색
	int		m_nTeam;			// 플레이어 / 적군 / 동맹 판별

}SOLDIER, *PSOLDIER;

// 병사 리스트
typedef struct _tagList
{
	SOLDIER*	m_pBegin;
	SOLDIER*	m_pEnd;
	int			m_nSize;

}LIST, *PLIST;

// 플레이어
typedef struct _tagPlayer
{
	POINT	m_tPos; // 플레이어 위치

	int		m_nMoney; // 소지 금액
	int		m_nColor; // 색상
	int		m_nHaveShip; // 물을 통과할 수 있는 지 여부

	char	m_cShape[3];

	PSOLDIER pSoldiers[3]; // 병사들
	
}PLAYER, *PPLAYER;





/* 적 성 */
// 문
typedef struct _tagDoor
{
	POINT m_tPos;
	int m_nClosed;

	struct _tagDoor* m_pPrev;
	struct _tagDoor* m_pNext;

}DOOR, *PDOOR;

// 지역
typedef struct _tagArea
{
	POINT m_tPos;
	int m_beOccupied;

	struct _tagArea* m_pPrev;
	struct _tagArea* m_pNext;

}AREA, *PAREA;

// 적 성문 리스트
typedef struct _tagDoorList
{
	PDOOR m_pBegin;
	PDOOR m_pEnd;

	int m_nSize;

}DLIST, *PDLIST;

// 적 성 지역 리스트
typedef struct _tagAreaList
{
	PAREA	m_pBegin;
	PAREA	m_pEnd;

	int		m_nSize;

}ALIST, *PALIST;

// 적 성
typedef struct _tagECastle
{
	PDLIST	m_tDoorPosList;
	PALIST	m_tAreaPosList;

	POINT	m_tStartPos;
	POINT	m_tDestPos;
	POINT	m_tKeyPos;

	char m_aECastleMap[CASTLE_HEIGHT_MAX][CASTLE_WIDTH_MAX]; // 맵
	int m_nReward; // 보상

}ECASTLE, *PECASTLE;