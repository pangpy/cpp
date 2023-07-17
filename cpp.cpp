#include <windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#define ID_BUTTON 1001

// 全局变量
HINSTANCE hInst;
HWND hWndButton;

// 班级同学名单
std::vector<std::wstring> classmates = {
    L"同学1",
    L"同学2",
    L"同学3",
    // 其他同学姓名...
};

// 函数声明
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonClickProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 主函数
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局变量
    hInst = hInstance;

    // 注册窗口类
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
        MessageBox(NULL, L"窗口类注册失败！", L"错误", MB_ICONERROR);
        return 0;
    }

    // 创建窗口
    HWND hWnd = CreateWindowW(L"RandomNameApp", L"随机点名", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        MessageBox(NULL, L"窗口创建失败！", L"错误", MB_ICONERROR);
        return 0;
    }

    // 创建按钮
    hWndButton = CreateWindowW(L"BUTTON", L"点名", WS_TABSTOP | WS_VISIBLE | WS_CHILD,
        10, 10, 80, 30, hWnd, (HMENU)ID_BUTTON, hInstance, NULL);
    if (!hWndButton)
    {
        MessageBox(NULL, L"按钮创建失败！", L"错误", MB_ICONERROR);
        return 0;
    }

    // 显示窗口
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BUTTON && HIWORD(wParam) == BN_CLICKED)
        {
            // 调用按钮点击事件处理函数
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

// 按钮点击事件处理函数
LRESULT CALLBACK ButtonClickProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_COMMAND && HIWORD(wParam) == BN_CLICKED && (HWND)lParam == hWndButton)
    {
        // 设置随机种子
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // 随机点名
        int randomIndex = std::rand() % classmates.size();
        std::wstring selectedStudent = classmates[randomIndex];

        // 显示点名结果的消息框
        std::wstring message = L"被点名的同学是：" + selectedStudent;
        MessageBoxW(hWnd, message.c_str(), L"点名结果", MB_OK);

        return 0;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
