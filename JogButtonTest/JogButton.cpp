#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Check";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND c1,c2,c3,c4;
	static BOOL ELLIPSE = FALSE;
	static BOOL bnowDraw=FALSE;

	static int x;
	static int y;

	switch(iMessage) {
	case WM_CREATE:
		c1=CreateWindow("button","Draw Ellipse?",WS_CHILD | WS_VISIBLE | 
			BS_CHECKBOX,20,20,160,25,hWnd,(HMENU)0,g_hInst,NULL);
		c2=CreateWindow("button","Good bye Message?",WS_CHILD | WS_VISIBLE | 
			BS_AUTOCHECKBOX,20,50,160,25,hWnd,(HMENU)1,g_hInst,NULL);
		c3=CreateWindow("button","3State",WS_CHILD | WS_VISIBLE | BS_3STATE,
			20,80,160,25,hWnd,(HMENU)2,g_hInst,NULL);
		c4=CreateWindow("button","Auto 3State",WS_CHILD | WS_VISIBLE | 
			BS_AUTO3STATE,20,110,160,25,hWnd,(HMENU)3,g_hInst,NULL);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case 0:
			if (SendMessage(c1,BM_GETCHECK,0,0)==BST_UNCHECKED) {
				/*SendMessage(c1,BM_SETCHECK,BST_CHECKED,0);
				ELLIPSE = TRUE;*/
			}
			else {
				/*SendMessage(c1,BM_SETCHECK,BST_UNCHECKED,0);
				ELLIPSE = FALSE;*/
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			if (SendMessage(c3,BM_GETCHECK,0,0)==BST_UNCHECKED)
				SendMessage(c3,BM_SETCHECK,BST_CHECKED,0);
			else
			if (SendMessage(c3,BM_GETCHECK,0,0)==BST_INDETERMINATE)
				SendMessage(c3,BM_SETCHECK,BST_UNCHECKED,0);
			else
				SendMessage(c3,BM_SETCHECK,BST_INDETERMINATE,0);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:

		x=LOWORD(lParam);
		y=HIWORD(lParam);
		if ( x >=200 && x<= 200 + 400 && y >= 100 && y<= 100 +200)
		{
				SendMessage(c1,BM_SETCHECK,BST_CHECKED,0);
				ELLIPSE = TRUE;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_LBUTTONUP:
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		if ( x >=200 && x<= 200 + 400 && y >= 100 && y<= 100 +200)
		{
				SendMessage(c1,BM_SETCHECK,BST_UNCHECKED,0);
				ELLIPSE = FALSE;
		}
		InvalidateRect(hWnd, NULL, TRUE);

		return 0;		
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		if (ELLIPSE == TRUE)
			Ellipse(hdc,200,100,400,200);
		else 
			Rectangle(hdc,200,100,400,200);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (SendMessage(c2,BM_GETCHECK,0,0)==BST_CHECKED)
			MessageBox(hWnd,"Good bye","Check",MB_OK);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
