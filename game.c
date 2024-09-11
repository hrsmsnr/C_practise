#include <stdio.h>
#include <time.h>

#define REPEAT 2               /* �^�C�s���O���K�� */
#define TEHON_LINE_MAX_NUM 2   /* ��{������̌� */
#define GOOD_TIME 20           /* ���͎���(GOOD) */
#define NG_TIME 40             /* ���͎���(NG) */
#define MAX_INPUT_LENGTH 30    /* ���͂̍ő咷 */

#pragma execution_character_set("utf-8")

char line_array1[][30] = {
    "I have some good news",
    "Let's do something fun"
};

char line_array2[][30] = {
    "Have a good day",
    "Enter a string"
};

void correct_training(char line_array[][30]); // �֐��̈����ɔz���ǉ�

int main(void) {
    int choice;

    printf("���^�C�s���O�Q�[���J�n��\n");
    printf("0: line_array1 ���g��\n");
    printf("1: line_array2 ���g��\n");
    printf("�I�����Ă������� (0 �܂��� 1): ");
    scanf("%d", &choice);

    // ���̓o�b�t�@�Ɏc�������s�������N���A
    getchar();

    if (choice == 0) {
        correct_training(line_array1);
    } else if (choice == 1) {
        correct_training(line_array2);
    } else {
        printf("�����ȑI���ł��B�I�����܂��B\n");
    }

    return 0;
}

void correct_training(char line_array[][30]) {
    int input_char,   /* �L�[�{�[�h����̓��̓f�[�^�i�ꕶ���j */
        count,        /* �^�C�s���O�񐔂̌v�Z�p */
        line,         /* �g�p�����{������̔���p */
        begin_input,  /* ���͂̊J�n���� */
        end_input,    /* ���͂̏I������ */
        input_time,   /* ���͎��� */
        sum_input_time = 0,   /* ���v���͎��� */
        index,        /* �����z��̓Y�����p */
        error_cnt;    /* �G���[������ */
    time_t t;         /* time�֐��p */
    char user_input[MAX_INPUT_LENGTH]; /* ���[�U�[�̓��͂�ۑ�����z�� */
    
    for (count = 0; count < REPEAT; count++) {
        for (line = 0; line < TEHON_LINE_MAX_NUM; line++) {
            /* ��{������̏o�͂Ɠ��͏��� */
            printf("%s\n", line_array[line]);
            begin_input = time(&t);
            
            /* ���͂�z��ɕۑ� */
            index = 0;
            error_cnt = 0;

            while ((input_char = getchar()) != '\n' && index < MAX_INPUT_LENGTH - 1) {
                user_input[index] = input_char; // ���[�U�[�̓��͂�ۑ�
                if (line_array[line][index] != '\0') {
                    if (input_char != line_array[line][index]) {
                        error_cnt++;
                    }
                    index++;
                }
            }
            user_input[index] = '\0'; // ���͂̏I��������

            end_input = time(&t);
            /* ���͎��Ԃɂ��Y�����b�Z�[�W�̕\������ */
            input_time = end_input - begin_input;
            sum_input_time += input_time;
            printf("time=%d  ", input_time);
            printf("sum_time=%d  ", sum_input_time);
            printf("error count=%d\n", error_cnt);

            /* ���͂Ɛ������r���ĊԈႢ��\�� */
            printf("Correct: %s\n", line_array[line]);
            printf("Input:   %s\n", user_input);
            printf("         ");
            for (int i = 0; i < index; i++) {
                if (line_array[line][i] != user_input[i]) {
                    printf("^"); // �Ԉ���������̏ꏊ�� ^ ��\��
                } else {
                    printf(" "); // �������ꏊ�ɂ̓X�y�[�X
                }
            }
            printf("\n");

            if (error_cnt == 0) {
                if (input_time <= GOOD_TIME) {
                    printf("���΂炵���I\n");
                } else {
                    if (input_time >= NG_TIME) {
                        printf("����΂��āI\n");
                    } else {
                        printf("���̒��q�I\n");
                    }
                }
            } else {
                printf("�^�C�v�~�X������܂��B\n");
            }
        }
    }
}
