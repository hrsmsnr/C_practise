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
     
    WNDCLASSEX wcex;
 
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
            NULL);
 
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
    HWND hWnd = CreateWindow(
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
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("�E�B���h�E�����Ɏ��s���܂���!"),
            _T("Sample03"),
            NULL);
        return 1;
    }
 
    // �E�B���h�E�̕\���ɕK�v�ȃp�����[�^:
    // hWnd     : CreateWindow�̖߂�l
    // nCmdShow : WinMain�̈�����4�Ԗ�
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);
 
    // ���C���̃��b�Z�[�W���[�v:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
 
//  �E�B���h�E�v���V�[�W���i���b�Z�[�W�ɑ΂���R�[���o�b�N�֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, World!");
    switch (message)
    {
    case WM_PAINT:
        //  �`�揈���̊J�n
        hdc = BeginPaint(hWnd, &ps);
        // ������̏o�́B�uHello, World!�v�Əo�͂���B
        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));
        //  �y�C���g�����̏I��
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
 
    return 0;
}