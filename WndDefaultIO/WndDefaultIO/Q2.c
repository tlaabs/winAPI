#include <windows.h> //win32API ���̺귯��
#include <TCHAR.H>//��Ƽ����Ʈ, �����ڵ� ������� ó��
#include <stdlib.h>
#include <time.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//hwnd : ������ �ڵ鰪(CreateWindow �Լ��� ���� �������)
//������ �ڵ鿡�� ������ ���� ���� ũ��, ��Ÿ��, Ÿ��Ʋ �̸����� ������ �������.
//iMsg : �̺�Ʈ �� ex:(WM_KEYDOWN, WM_CHAR, WM_KEYUP)
//wParam: ����Ű�� ��(VK_TAB,VK_BACK)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
//hInstance[1] : Ŀ���� ���α׷��� �ο��ϴ� ID, �������α׷��� �����Ϸ����� 
//hInstance[2] : �˰ž���
//IpszCmdLine : �ܺο��� �Ѿ���� ���ڿ�, argv�� ����ϴ�
//nCmdShow : �����찡 ȭ�鿡 ��µ� �� ���¸� ����(�� �𸣰ڴ�)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass; //������ Ŭ���� ����ü
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//������ ũ�� �����ϸ� �ٽ� �׸���
	WndClass.lpfnWndProc = WndProc; //���ν��� �Լ� : �޽��� ó���� ���� �Լ�
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //�������α׷� �ν��Ͻ� ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����
	WndClass.lpszMenuName = NULL; //�޴��̸�
	WndClass.lpszClassName = _T("Window Class Name"); //Ŭ���� �̸�

	RegisterClass(&WndClass);//������ Ŭ������ Ŀ�ο� ���
							 //������ ��� ����
	hwnd = CreateWindow(_T("Window Class Name"), //������ Ŭ���� �̸�
		_T("Window Title Name"),//������ Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW, //������ ��Ÿ��
							 //Ÿ��Ʋ�ٿ� �ּ�ȭ, �ִ�ȭ, �ݱ� �׸��� ���콺 �����ʹ�ư�� ������ �� �ý��� �޴��� ��Ÿ��
							 //CW_USEDEFAULT - Ŀ�ο� ���� �⺻���� ���
		CW_USEDEFAULT,//������ ��ġ X
		CW_USEDEFAULT,//������ ��ġ Y
		CW_USEDEFAULT,//������ ���� ũ��
		CW_USEDEFAULT,//������ ���� ũ��
		NULL,//�θ� ������ �ڵ�
		NULL,//�޴� �ڵ�
		hInstance,//
		NULL//���� ������ ����
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
		//&msg : �޽����� ����� MSG����ü�� ���� ������
		//NULL : �޽����� �߻��� �������� �ڵ�
	{
		TranslateMessage(&msg);
		//�� �޽����� �ϳ��� ��ȯ - �߸𸣰ڴ�.
		DispatchMessage(&msg);
		//�޽����� ó���ϴ� �Լ��� �޽����� ������ -> WndProc
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[2];
	srand(time(NULL));
	int x, y;
	x = (rand() % 10)*50;
	y = (rand() % 10)*50;
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		hdc = GetDC(hwnd);
		TextOut(hdc,x,y, str, _tcslen(str));
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		str[0] = wParam;
		str[1] = NULL;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
	//�� ���� �⺻ �޽��� ó���� Ŀ���� ó���ϰ� ��
}