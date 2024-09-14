#include <windows.h>

#pragma execution_character_set("Shift JIS")

// �E�B���h�E�v���V�[�W���̐錾
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
    TCHAR szAppName[] = TEXT("TestApp");
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // �E�B���h�E�N���X�̑�����ݒ�
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;  // WndProc�ɕύX
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    // �E�B���h�E�N���X��o�^
    if (!RegisterClass(&wc)) return 0;

    // �E�B���h�E���쐬
    hwnd = CreateWindow(
        szAppName, TEXT("Title"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    // �E�B���h�E��\��
    ShowWindow(hwnd, nCmdShow);

    // �E�B���h�E���ĕ`��
    UpdateWindow(hwnd);

    // ���b�Z�[�W���[�v
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;  // �e�L�X�g�{�b�N�X�̃n���h��
    static HWND hButton;  // OK�{�^���̃n���h��

    switch (message) {
    
    case WM_CREATE:
        // �e�L�X�g�{�b�N�X�i�G�f�B�b�g�R���g���[���j���쐬
        hEdit = CreateWindow(
            TEXT("EDIT"),            // �N���X��
            TEXT(""),                // �����e�L�X�g
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, // �X�^�C��
            10, 10, 200, 20,         // �ʒu�ƃT�C�Y (x, y, width, height)
            hwnd,                    // �e�E�B���h�E�̃n���h��
            NULL,                    // �R���g���[��ID�i���j���[��R�}���h�Ŏg���j
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // �C���X�^���X�n���h��
            NULL);                   // �g�����

        // OK�{�^�����쐬
        hButton = CreateWindow(
            TEXT("BUTTON"),          // �N���X��
            TEXT("OK"),              // �{�^���̃e�L�X�g
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // �X�^�C��
            10, 40, 80, 30,          // �ʒu�ƃT�C�Y (x, y, width, height)
            hwnd,                    // �e�E�B���h�E�̃n���h��
            (HMENU)1,                // �R���g���[��ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // �C���X�^���X�n���h��
            NULL);                   // �g�����
        break;

    case WM_COMMAND:
        // OK�{�^���������ꂽ�ꍇ�̏���
        if (LOWORD(wParam) == 1) {
            MessageBox(hwnd, TEXT("OK�{�^����������܂����I"), TEXT("�ʒm"), MB_OK);
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
