// ************************************
// Ex �������\������v���O����
// ************************************
//�K�v�ȃw�b�_�[�t�@�C���̃C���N���[�h
#define STRICT

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// �V���{����`�y�у}�N��
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

//  �C���X�^���X�i�O���[�o���ϐ��j
HINSTANCE hInst;

//  �E�B���h�E�v���V�[�W���̃R�[���o�b�N�֐�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    static TCHAR szWindowClass[] = _T("Sample03");
    static TCHAR szTitle[] = _T("�E�B���h�E���g�����A�v���̃T���v���A");

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
            _T("RegisterClassEx�̏����Ɏ��s���܂���"),
            _T("Sample03"),
            MB_OK);

        return 1;
    }

    hInst = hInstance; // �O���[�o���ϐ��ɒl������

    // The parameters to CreateWindow explained:
    // szWindowClass                : �A�v���P�[�V�����̖��O
    // szTitle                      : �^�C�g���o�[�Ɍ���镶����
    // WS_OVERLAPPEDWINDOW          : ��������E�B���h�E�̃^�C�v
    // CW_USEDEFAULT, CW_USEDEFAULT : �ŏ��ɒu���|�W�V���� (x, y)
    // WINDOW_WIDTH, WINDOW_HEIGHT  : �ŏ��̃T�C�Y (��, ����)
    // NULL                         : ���̃E�B���h�E�̐e�E�B���h�E�̃n���h��
    // NULL                         : ���j���[�o�[�i���̃T���v���ł͎g�p�����j
    // hInstance                    : WinMain�֐��̍ŏ��̃p�����[�^
    // NULL                         : WM_CREATE���i���̃A�v���P�[�V�����ł͎g�p�����j
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
    //  �E�B���h�E�������ł��Ȃ������ꍇ
    if (!hwnd)
    {
        MessageBox(NULL,
            _T("�E�B���h�E�����Ɏ��s���܂���!"),
            _T("Sample03"),
            MB_OK);
        return 1;
    }

    // �E�B���h�E�̕\���ɕK�v�ȃp�����[�^:
    // hwnd     : CreateWindow�̖߂�l
    // nCmdShow : WinMain�̈�����4�Ԗ�
    ShowWindow(hwnd,
        nCmdShow);
    UpdateWindow(hwnd);

    // ���C���̃��b�Z�[�W���[�v:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

//  �E�B���h�E�v���V�[�W���i���b�Z�[�W�ɑ΂���R�[���o�b�N�֐��j
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");
    static HWND hEdit;  // �e�L�X�g�{�b�N�X�̃n���h��
    static HWND hButton;  // OK�{�^���̃n���h��
    switch (message)
    {
    case WM_PAINT:

hEdit = CreateWindow(
            TEXT("EDIT"),            // �N���X��
            TEXT(""),                // �����e�L�X�g
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, // �X�^�C��
            10, 50, 200, 20,         // �ʒu�ƃT�C�Y (x, y, width, height)
            hwnd,                    // �e�E�B���h�E�̃n���h��
            NULL,                    // �R���g���[��ID�i���j���[��R�}���h�Ŏg���j
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // �C���X�^���X�n���h��
            NULL);                   // �g�����

        // OK�{�^�����쐬
        hButton = CreateWindow(
            TEXT("BUTTON"),          // �N���X��
            TEXT("OK"),              // �{�^���̃e�L�X�g
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // �X�^�C��
            10, 80, 80, 30,          // �ʒu�ƃT�C�Y (x, y, width, height)
            hwnd,                    // �e�E�B���h�E�̃n���h��
            (HMENU)1,                // �R���g���[��ID
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), // �C���X�^���X�n���h��
            NULL);                   // �g�����

        //  �`�揈���̊J�n
        hdc = BeginPaint(hwnd, &ps);
        // ������̏o�́B�uHello, World!�v�Əo�͂���B
        TextOut(hdc,
            10, 10,
            greeting, _tcslen(greeting));
        //  �y�C���g�����̏I��
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