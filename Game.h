/*
	0501 : ���� â
	0502 : ��Ʋ ��
	0503 : ��Ʋ ����
	0504 : ����
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

#include "Type.h"
#include "Struct.h"


#define MAP_WIDTH_MAX 30
#define MAP_HEIGHT_MAX 30

#define TOTAL_SOLDIER_NUM 3
#define TOTAL_ECASTLE_NUM 3
#define TOTAL_BATTLEMAP_NUM 3

#define STATUS_WINDOW_HEIGHT 30
#define STATUS_WINDOW_WIDTH 15
#define STATUS_STRING_MAXLENGTH 24

#define EVENT_WINDOW_HEIGHT 6
#define EVENT_WINDOW_WIDTH	30

#define CASTLE_WIN	1
#define CASTLE_LOSE	0

#define ON	1
#define OFF 0

#define QUEUE_MAX_SIZE 1000