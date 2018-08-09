#include <Windows.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;


int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    RECT myRect;
    HWND gameWindowHandle;
    gameWindowHandle = FindWindowA(0, "Call of Duty®");
    GetWindowRect(gameWindowHandle, &myRect);

    WNDCLASSEX w;
    w.cbSize = sizeof(WNDCLASSEX);
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = WndProc;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;
    w.hInstance = hInstance;
    w.hIcon = NULL;
    w.hCursor = NULL;
    w.hbrBackground = (HBRUSH)0;
    w.lpszMenuName = NULL;
    w.lpszClassName = "ClassName";
    w.hIconSm = NULL;

    if (!RegisterClassEx(&w))
    {
        MessageBox(NULL, "Could not Register Class", "Window Title", NULL);
        return -1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, "ClassName", "Window",
        WS_CAPTION,
        myRect.left,   //x 
        myRect.top,   // y
        myRect.right - myRect.left,   // width
        myRect.bottom - myRect.top,   // height
        NULL, NULL,
        hInstance, NULL);

    if (!hWnd)
    {
        MessageBox(NULL, "Call to create window failed", "Win32 Guided tour", NULL);

        return -1;
    }

    // Remove Borders around window
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~(WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_BORDER));
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) & ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

    // Make the Background Transparent
    SetLayeredWindowAttributes(hWnd, RGB(255,255,255), 255, LWA_COLORKEY); // Replaces color white with transparancey
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HDC myHDC = GetDC(hWnd);

    // Drawing Stuff
    HPEN myPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN originalPen;
    originalPen = (HPEN)SelectObject(myHDC, myPen);
   

    //main loop waits for messages
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        Rectangle(myHDC, 200, 200, 300, 400);

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (uMsg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    }
    return 0;
}
