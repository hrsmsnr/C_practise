#include <windows.h>

#pragma execution_character_set("Shift JIS")

// ウィンドウプロシージャの宣言
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
    TCHAR szAppName[] = TEXT("TestApp");
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // ウィンドウクラスの属性を設定
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;  // WndProcに変更
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    // ウィンドウクラスを登録
    if (!RegisterClass(&wc)) return 0;

    // ウィンドウを作成
    hwnd = CreateWindow(
        szAppName, TEXT("Title"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    // ウィンドウを表示
    ShowWindow(hwnd, nCmdShow);

    // ウィンドウを再描画
    UpdateWindow(hwnd);

    // メッセージループ
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;  // テキストボックスのハンドル
    static HWND hButton;  // OKボタンのハンドル

    switch (message) {
    
    case WM_CREATE:
        // テキストボックス（エディットコントロール）を作成
        hEdit = CreateWindow(
            TEXT("EDIT"),            // クラス名
            TEXT(""),                // 初期テキスト
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, // スタイル
            10, 10, 200, 20,         // 位置とサイズ (x, y, width, height)
            hwnd,                    // 親ウィンドウのハンドル
            NULL,                    // コントロールID（メニューやコマンドで使う）
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // インスタンスハンドル
            NULL);                   // 拡張情報

        // OKボタンを作成
        hButton = CreateWindow(
            TEXT("BUTTON"),          // クラス名
            TEXT("OK"),              // ボタンのテキスト
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // スタイル
            10, 40, 80, 30,          // 位置とサイズ (x, y, width, height)
            hwnd,                    // 親ウィンドウのハンドル
            (HMENU)1,                // コントロールID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // インスタンスハンドル
            NULL);                   // 拡張情報
        break;

    case WM_COMMAND:
        // OKボタンが押された場合の処理
        if (LOWORD(wParam) == 1) {
            MessageBox(hwnd, TEXT("OKボタンが押されました！"), TEXT("通知"), MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
