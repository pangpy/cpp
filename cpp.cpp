#include <windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#define ID_BUTTON 1001

// ȫ�ֱ���
HINSTANCE hInst;
HWND hWndButton;

// �༶ͬѧ����
std::vector<std::wstring> classmates = {
    L"ͬѧ1",
    L"ͬѧ2",
    L"ͬѧ3",
    // ����ͬѧ����...
};

// ��������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonClickProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ������
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // ��ʼ��ȫ�ֱ���
    hInst = hInstance;

    // ע�ᴰ����
    WNDCLASSEXW wcex = { 0 };
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"RandomNameApp";
    if (!RegisterClassExW(&wcex))
    {
        MessageBox(NULL, L"������ע��ʧ�ܣ�", L"����", MB_ICONERROR);
        return 0;
    }

    // ��������
    HWND hWnd = CreateWindowW(L"RandomNameApp", L"�������", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        MessageBox(NULL, L"���ڴ���ʧ�ܣ�", L"����", MB_ICONERROR);
        return 0;
    }

    // ������ť
    hWndButton = CreateWindowW(L"BUTTON", L"����", WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hWnd, (HMENU)ID_BUTTON, hInstance, NULL);
    if (!hWndButton)
    {
        MessageBox(NULL, L"��ť����ʧ�ܣ�", L"����", MB_ICONERROR);
        return 0;
    }

    // ��ʾ����
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON && HIWORD(wParam) == BN_CLICKED)
        {
            // ���ð�ť����¼�������
            ButtonClickProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// ��ť����¼�������
LRESULT CALLBACK ButtonClickProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == hWndButton)
    {
        // �����������
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // �������
        int randomIndex = std::rand() % classmates.size();
        std::wstring selectedStudent = classmates[randomIndex];

        // ��ʾ�����������Ϣ��
        std::wstring message = L"��������ͬѧ�ǣ�" + selectedStudent;
        MessageBoxW(hWnd, message.c_str(), L"�������", MB_OK);

        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
