/*
	0501 : 상태 창
	0502 : 배틀 맵
	0503 : 배틀 로직
	0504 : 상점
*/



#pragma once
#define _CRT_SECURE_NO_WARNINGS


#define MANAGE_MODE 1
#define DEBUG_MODE 0

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <memory.h>
#include <time.h>
#include <math.h>


#include "Type.h"
#include "Struct.h"
#include "Macro.h"


#define MAP_WIDTH_MAX 30
#define MAP_HEIGHT_MAX 30

#define TOTAL_SOLDIER_NUM 3
#define TOTAL_ECASTLE_NUM 3
#define TOTAL_BATTLEMAP_NUM 3

#define STATUS_WINDOW_HEIGHT 30
#define STATUS_WINDOW_WIDTH 15
#define STATUS_WINDOW_WIDTH_OFFSET (MAP_WIDTH_MAX * 2)

#define EVENT_WINDOW_HEIGHT 5
#define EVENT_WINDOW_WIDTH	45
#define EVENT_STRING_MAXLENGTH 50
#define EVENT_WINDOW_HEIGHT_OFFSET MAP_HEIGHT_MAX

#define SUBWINDOW_HEIGHT 27
#define SUBWINDOW_WIDTH 20
#define SUBWINDOW_HEIGHT_OFFSET 5
#define SUBWINDOW_WIDTH_OFFSET 99

#define CASTLE_WIN	1
#define CASTLE_LOSE	0

#define ON	1
#define OFF 0

#define DEAD 0
#define ALIVE 1

#define SHOP_ITEMS_COUNT 7

#define QUEUE_MAX_SIZE 1000