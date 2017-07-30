#include <windows.h> //win32API 라이브러리
#include <TCHAR.H>//멀티바이트, 유니코드 상관없이 처리
#define LINE_MAX 5
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
//hwnd : 윈도우 핸들값(CreateWindow 함수를 통해 만들어짐)
//윈도우 핸들에는 윈도우 가로 세로 크기, 스타일, 타이틀 이름등의 정보가 담겨있음.
//iMsg : 이벤트 값 ex:(WM_KEYDOWN, WM_CHAR, WM_KEYUP)
//wParam: 가상키의 값(VK_TAB,VK_BACK)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
//hInstance[1] : 커널이 프로그램에 부여하는 ID, 응용프로그램을 구분하려고사용 
//hInstance[2] : 알거없음
//IpszCmdLine : 외부에서 넘어오는 문자열, argv와 비슷하다
//nCmdShow : 윈도우가 화면에 출력될 때 형태를 정의(잘 모르겠다)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass; //윈도우 클래스 구조체
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우 크기 변경하면 다시 그리기
	WndClass.lpfnWndProc = WndProc; //프로시저 함수 : 메시지 처리에 사용될 함수
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance; //응용프로그램 인스턴스 값
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색
	WndClass.lpszMenuName = NULL; //메뉴이름
	WndClass.lpszClassName = _T("Window Class Name"); //클래스 이름

	RegisterClass(&WndClass);//윈도우 클래스를 커널에 등록
							 //여러개 등록 가능
	hwnd = CreateWindow(_T("Window Class Name"), //윈도우 클래스 이름
		_T("Window Title Name"),//윈도우 타이틀 이름
		WS_OVERLAPPEDWINDOW, //윈도우 스타일
							 //타이틀바에 최소화, 최대화, 닫기 그리고 마우스 오른쪽버튼을 눌렀을 때 시스템 메뉴가 나타남
							 //CW_USEDEFAULT - 커널에 의해 기본값을 사용
		CW_USEDEFAULT,//윈도우 위치 X
		CW_USEDEFAULT,//윈도우 위치 Y
		CW_USEDEFAULT,//윈도우 가로 크기
		CW_USEDEFAULT,//윈도우 세로 크기
		NULL,//부모 윈도우 핸들
		NULL,//메뉴 핸들
		hInstance,//
		NULL//생성 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
		//&msg : 메시지가 저장된 MSG구조체에 대한 포인터
		//NULL : 메시지가 발생한 윈도우의 핸들
	{
		TranslateMessage(&msg);
		//두 메시지를 하나로 변환 - 잘모르겠다.
		DispatchMessage(&msg);
		//메시지를 처리하는 함수에 메시지를 보낸다 -> WndProc
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[10][100];
	static int count = 0;
	static int lines = 0;
	int i = 0;
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		while (i <= lines)
		{
			TextOut(hdc, 0, i * 20, str[i], _tcslen(str[i]));
			i++;
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			lines++;
			count = 0;
		}
		else
		{
			if (count >= LINE_MAX)
			{
				lines++;
				count = 0;
			}
			str[lines][count++] = wParam;
		}
		str[lines][count] = NULL;
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
	//그 밖의 기본 메시지 처리는 커널이 처리하게 함
}