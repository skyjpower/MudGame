#include "Game.h"

#pragma region Buffer
// ���� ����
void CreateBuffer()
{
	COORD size = { MAP_HEIGHT_MAX, MAP_WIDTH_MAX };

	CONSOLE_CURSOR_INFO cci;

	SMALL_RECT rect;
	rect.Bottom = 0;

	rect.Left = 0;

	rect.Right = MAP_HEIGHT_MAX - 1;;

	rect.Top = MAP_WIDTH_MAX - 1;

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleScreenBufferSize(hBuffer[1], size);

	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	cci.dwSize = 1;
	cci.bVisible = TRUE;

	SetConsoleCursorInfo(hBuffer[0], &cci);
	SetConsoleCursorInfo(hBuffer[1], &cci);
}
// ���� ���
void WriteBuffer(int x, int y, char str[])
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(hBuffer[nScreenIndex], CursorPosition);
	WriteFile(hBuffer[nScreenIndex], str, strlen(str), &dw, NULL);
}

// ���� Ŭ����
void ClearBuffer()
{
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', MAP_HEIGHT_MAX * MAP_WIDTH_MAX, Coor, &dw);
}

// ���� ��ȯ
void FlippingBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);
	nScreenIndex = !nScreenIndex;
}

void DeleteBuffers()
{
	CloseHandle(hBuffer[0]);    //���� ����
	CloseHandle(hBuffer[1]);    //���� ����
}
#pragma endregion

void Render()
{

}

int main()
{


	return 0;
}