#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#define MAP_WIDTH_MAX 30
#define MAP_HEIGHT_MAX 30

/* 전역 변수 */
HANDLE hBuffer[2];
int nScreenIndex;

// 맵
int aMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
int 