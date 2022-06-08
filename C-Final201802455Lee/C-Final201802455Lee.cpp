#include <windows.h>
#include <stdio.h>
#include "resource.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMss, WPARAM wParam, LPARAM IParam);
HBITMAP hBmpAir, hBmpBack, hBmpBullet, hBmpEnemy, hBmpEnemy2, hBmpExplosion, hBmpExplosion2;

int nX = 0, nY = 50; //airplane
int nX_back = 0; // background
int nXb[10], nYb[10]; // bullet
bool bullet[10] = { false };
bool hit[10] = { false };
bool hit2[10] = { false };

int nXe, nYe, nXe2, nYe2;
bool enemy = false, enemy2 = false;

int max_no_of_bullet = 10, bn = 0;
int no_of_fire = 0, no_of_hit = 0;

bool game_start = false;
bool bullet_multi = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR IpCmdLine, int nCmdShow)
{

	//1. Declare window class


	char szTitle[] = "Leeyoonsun";
	char szClass[] = "Class";
	WNDCLASSEX WndEx;

	WndEx.cbSize = sizeof(WndEx);
	WndEx.style = NULL;
	WndEx.lpfnWndProc = WndProc;
	WndEx.cbClsExtra = 0;
	WndEx.cbWndExtra = 0;
	WndEx.hInstance = hInstance;
	WndEx.hIcon = LoadIcon(NULL, "");
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndEx.lpszMenuName = "IDR_MENU";
	WndEx.lpszClassName = szClass;
	WndEx.hIconSm = LoadIcon(hInstance, "");

	//2. Register window class
	RegisterClassEx(&WndEx);

	//3. create window class

	HWND hWnd;
	hWnd = CreateWindowEx(NULL,
		szClass, // name of window class
		szTitle, // window name appeared on the title bar
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // x-coordinate of the created window
		CW_USEDEFAULT, // y-coordinate of the created window
		320 * 2,  // width of the created window
		240 * 2, // height of the created window
		NULL, // parent window
		NULL, // menu
		hInstance,// instance handle
		NULL); // WM_CREATE parameter

	//4. Show window

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hBmpAir = LoadBitmap(hInstance, "IDB_AIR");
	hBmpBack = LoadBitmap(hInstance, "IDB_BACK");
	hBmpBullet = LoadBitmap(hInstance, "IDB_BULLET");
	hBmpEnemy = LoadBitmap(hInstance, "IDB_ENEMY");
	hBmpEnemy2 = LoadBitmap(hInstance, "IDB_ENEMY");
	hBmpExplosion = LoadBitmap(hInstance, "IDB_EX");
	hBmpExplosion2 = LoadBitmap(hInstance, "IDB_EX");



	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);


	//5. Message Loop
	MSG mSg;
	while (TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

void init_game(HWND hWnd, bool sw) {

	for (int n = 0; n < max_no_of_bullet; n++)
	{
		KillTimer(hWnd, n + 1);
		bullet[n] = false;
		hit[n] = false;

	}
	bn = 0;

	if (sw == true) {
		no_of_fire = 0;
		no_of_hit = 0;
		game_start = false;
		enemy = false;
		enemy2 = false;

		KillTimer(hWnd, max_no_of_bullet + 2);
	}

	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMss, WPARAM wParam, LPARAM IParam) {

	HDC hDC, hMemDC;
	PAINTSTRUCT pS;
	char szText[100];
	static HWND hButtPlay, hButtStop, hButtExit;

	switch (uMss)
	{

	case WM_CREATE:
		hButtPlay = CreateWindow("BUTTON", "Game Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 360, 90, 30, hWnd, (HMENU)1, NULL, NULL);
		hButtStop = CreateWindow("BUTTON", "Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 110, 360, 90, 30, hWnd, (HMENU)2, NULL, NULL);
		hButtExit = CreateWindow("BUTTON", "Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 360, 90, 30, hWnd, (HMENU)3, NULL, NULL);
		

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		/*
		case 1:
			init_game(hWnd, true);
			game_start = true;

			nXe = 600;
			nYe = 50;
			enemy = true;
			break;
		case 3:
			break;
		case 5:
			PostQuitMessage(0);
			break;
		*/
		case ID_PLAY_START:
		case 1:
			init_game(hWnd, true);
			game_start = true;

			nXe = 600;
			nYe = 50;
			enemy = true;
			SetTimer(hWnd, max_no_of_bullet + 2, 2000, NULL);
			break;

		case ID_PLAY_STOP:
		case 2:
			init_game(hWnd, true);
			break;
		
		case ID_PLAY_EXIT:
		case 3:
			PostQuitMessage(0);
			break;
			

		case ID_BULLET_MULTI40008:
			init_game(hWnd, false);
			bullet_multi = true;
			break;

		case ID_BULLET_SINGLE40007:
			init_game(hWnd, false);
			bullet_multi = false;
			break;

		case ID_ENEMY_ONE40009:
			init_game(hWnd, false);
			enemy2 = false;
			break;


		case ID_ENEMY_TWO40010:
			init_game(hWnd, false);
			enemy2 = true;
			nXe = 500;
			nYe = 400;
			SetTimer(hWnd, max_no_of_bullet + 2, 2000, NULL);
			break;
		}

		break;


	case WM_KEYDOWN:
		switch (LOWORD(wParam)) {


		case VK_UP:
			nY -= 5;
			break;

		case VK_DOWN:
			nY += 5;
			break;

		case VK_LEFT:
			nX -= 5;
			nX_back += 5;
			break;

		case VK_RIGHT:
			nX += 5;
			nX_back -= 5;
			break;

		case VK_RETURN:
			nXe = 600;
			nYe = 50;
			enemy = true;
			SetTimer(hWnd, max_no_of_bullet + 2, 2000, NULL);
			break;

		case VK_SPACE:
			if (game_start == true) {
				no_of_fire++;

				nXb[bn] = nX + 127;
				nYb[bn] = nY;

				if (bullet[bn] == false) {
					bullet[bn] = true;
					SetTimer(hWnd, bn + 1, 10, NULL);
				}
				if (bullet_multi == true) {
					bn++;
					if (bn >= max_no_of_bullet) bn = 0;
					break;
				}
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;


	


	case WM_TIMER:
		for (int n = 0; n < max_no_of_bullet; n++) {

			if (wParam == n + 1) {
				nXb[n] += 5;
				if (nXb[n] > 640) {
					KillTimer(hWnd, n + 1);
					bullet[n] = false;
				}
			}
		}
		if (wParam == max_no_of_bullet + 2) {
			nXe = (rand() % 300) + 300;
			nYe = (rand() % 250);
		}
		if (wParam == max_no_of_bullet + 2 && enemy2 == true) {
			nXe2 = (rand() % 300) + 300;
			nYe2 = (rand() % 250);
		}

		for (int n = 0; n < max_no_of_bullet; n++) {
			if (nXb[n] > nXe - 15 && nXb[n] < nXe + 5 && nYb[n] > nYe - 15 && nYb[n] < nYe + 15)
			{
				bullet[n] = false;
				//enemy = false;
				KillTimer(hWnd, n + 1);
				//KillTimer(hWnd, 2);
				hit[n] = true;
				no_of_hit++;

				/*
				hDC = GetDC(hWnd);
				hMemDC = CreateCompatibleDC(hDC);
				SelectObject(hMemDC, hBmpExplosion);
				BitBlt(hDC, nXe, nYe, 32, 28, hMemDC, 0, 0, SRCCOPY);
				DeleteDC(hMemDC);
				ReleaseDC(hWnd, hDC);
				DeleteDC(hMemDC);

				MessageBox(hWnd, "Hit", "EndGame", NULL);
				*/

			}
			if (enemy2 == true && nXb[n] > nXe2 - 15 && nXb[n] < nXe2 + 5 && nYb[n] > nYe2 - 15 && nYb[n] < nYe2 + 15) {
				bullet[n] = false;
				//enemy = false;
				KillTimer(hWnd, n + 1);
				//KillTimer(hWnd, 2);
				hit2[n] = true;
				no_of_hit++;
			}



		}

		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;

	case WM_PAINT:

		if (nX > 640) nX = 0;
		else if (nX < 0) nX = 640;
		if (nY > 300) nY = 0;
		else if (nY < 0) nY = 300;

		hDC = BeginPaint(hWnd, &pS);
		hMemDC = CreateCompatibleDC(hDC);
		SelectObject(hMemDC, hBmpAir);
		BitBlt(hDC, nX, nY, 127, 37, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hBmpBack);
		BitBlt(hDC, nX_back, 281, 640, 159, hMemDC, 0, 0, SRCCOPY);
		BitBlt(hDC, nX_back + 640, 281, 640, 159, hMemDC, 0, 0, SRCCOPY);

		for (int k = 0; k < max_no_of_bullet; k++) {
			if (bullet[k] == true) {
				SelectObject(hMemDC, hBmpBullet);
				BitBlt(hDC, nXb[k], nYb[k], 32, 30, hMemDC, 0, 0, SRCCOPY);
			}

			if (hit[k] == true) {
				SelectObject(hMemDC, hBmpExplosion);
				BitBlt(hDC, nXe, nYe, 32, 28, hMemDC, 0, 0, SRCCOPY);
				hit[k] = false;
				Sleep(300);
			}
			if (hit2[k] == true) {
				SelectObject(hMemDC, hBmpExplosion2);
				BitBlt(hDC, nXe2, nYe2, 32, 28, hMemDC, 0, 0, SRCCOPY);
				hit2[k] = false;
				Sleep(300);
			}
		}

		if (enemy == true) {
			SelectObject(hMemDC, hBmpEnemy);
			BitBlt(hDC, nXe, nYe, 32, 29, hMemDC, 0, 0, SRCCOPY);
		}

		if (enemy2 == true) {
			SelectObject(hMemDC, hBmpEnemy2);
			BitBlt(hDC, nXe2, nYe2, 32, 29, hMemDC, 0, 0, SRCCOPY);
		}

		if (game_start) {
			sprintf_s(szText, "Number of fire %d, Number of hit : %d", no_of_fire, no_of_hit);
			TextOut(hDC, 300, 10, szText, lstrlen(szText));
		}

		DeleteDC(hMemDC);
		ReleaseDC(hWnd, hDC);
		DeleteObject(hMemDC);
		EndPaint(hWnd, &pS);

		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMss, wParam, IParam);
}
