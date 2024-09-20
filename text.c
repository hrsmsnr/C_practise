// ************************************
// Ex 文字列を表示するプログラム
// ************************************
//必要なヘッダーファイルのインクルード
#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// シンボル定義及びマクロ
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//  インスタンス（グローバル変数）
HINSTANCE hInst;

//  ウィンドウプロシージャのコールバック関数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    static TCHAR szWindowClass[] = _T("Sample03");
    static TCHAR szTitle[] = _T("ウィンドウを使ったアプリのサンプル②");

    TCHAR szAppName[] = TEXT("TestApp");
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    WNDCLASSEX wcex = {0};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("RegisterClassExの処理に失敗しました"),
            _T("Sample03"),
            MB_OK);

        return 1;
    }

    hInst = hInstance; // グローバル変数に値を入れる

    // The parameters to CreateWindow explained:
    // szWindowClass                : アプリケーションの名前
    // szTitle                      : タイトルバーに現れる文字列
    // WS_OVERLAPPEDWINDOW          : 生成するウィンドウのタイプ
    // CW_USEDEFAULT, CW_USEDEFAULT : 最初に置くポジション (x, y)
    // WINDOW_WIDTH, WINDOW_HEIGHT  : 最初のサイズ (幅, 高さ)
    // NULL                         : このウィンドウの親ウィンドウのハンドル
    // NULL                         : メニューバー（このサンプルでは使用せず）
    // hInstance                    : WinMain関数の最初のパラメータ
    // NULL                         : WM_CREATE情報（このアプリケーションでは使用せず）
    hwnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
        );
    //  ウィンドウが生成できなかった場合
    if (!hwnd)
    {
        MessageBox(NULL,
            _T("ウィンドウ生成に失敗しました!"),
            _T("Sample03"),
            MB_OK);
        return 1;
    }

    // ウィンドウの表示に必要なパラメータ:
    // hwnd     : CreateWindowの戻り値
    // nCmdShow : WinMainの引数の4番目
    ShowWindow(hwnd,
        nCmdShow);
    UpdateWindow(hwnd);

    // メインのメッセージループ:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

//  ウィンドウプロシージャ（メッセージに対するコールバック関数）
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");
    static HWND hEdit;  // テキストボックスのハンドル
    static HWND hButton;  // OKボタンのハンドル
    switch (message)
    {
    case WM_PAINT:

hEdit = CreateWindow(
            TEXT("EDIT"),            // クラス名
            TEXT(""),                // 初期テキスト
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, // スタイル
            10, 50, 200, 20,         // 位置とサイズ (x, y, width, height)
            hwnd,                    // 親ウィンドウのハンドル
            NULL,                    // コントロールID（メニューやコマンドで使う）
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // インスタンスハンドル
            NULL);                   // 拡張情報

        // OKボタンを作成
        hButton = CreateWindow(
            TEXT("BUTTON"),          // クラス名
            TEXT("OK"),              // ボタンのテキスト
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // スタイル
            10, 80, 80, 30,          // 位置とサイズ (x, y, width, height)
            hwnd,                    // 親ウィンドウのハンドル
            (HMENU)1,                // コントロールID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // インスタンスハンドル
            NULL);                   // 拡張情報

        //  描画処理の開始
        hdc = BeginPaint(hwnd, &ps);
        // 文字列の出力。「Hello, World!」と出力する。
        TextOut(hdc,
            10, 10,
            greeting, _tcslen(greeting));
        //  ペイント処理の終了
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }


    

    return 0;
}