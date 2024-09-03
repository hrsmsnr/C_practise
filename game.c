#include <stdio.h>
#include <time.h>

#define REPEAT 2               /* タイピング練習回数 */
#define TEHON_LINE_MAX_NUM 2   /* 手本文字列の個数 */
#define GOOD_TIME 20           /* 入力時間(GOOD) */
#define NG_TIME 40             /* 入力時間(NG) */
#define MAX_INPUT_LENGTH 30    /* 入力の最大長 */

char line_array1[][30] = {
    "I have some good news",
    "Let's do something fun"
};

char line_array2[][30] = {
    "Have a good day",
    "Enter a string"
};

void correct_training(char line_array[][30]); // 関数の引数に配列を追加

int main(void) {
    int choice;

    printf("＜タイピングゲーム開始＞\n");
    printf("0: line_array1 を使う\n");
    printf("1: line_array2 を使う\n");
    printf("選択してください (0 または 1): ");
    scanf("%d", &choice);

    // 入力バッファに残った改行文字をクリア
    getchar();

    if (choice == 0) {
        correct_training(line_array1);
    } else if (choice == 1) {
        correct_training(line_array2);
    } else {
        printf("無効な選択です。終了します。\n");
    }

    return 0;
}

void correct_training(char line_array[][30]) {
    int input_char,   /* キーボードからの入力データ（一文字） */
        count,        /* タイピング回数の計算用 */
        line,         /* 使用する手本文字列の判定用 */
        begin_input,  /* 入力の開始時刻 */
        end_input,    /* 入力の終了時刻 */
        input_time,   /* 入力時間 */
        sum_input_time = 0,   /* 合計入力時間 */
        index,        /* 文字配列の添え字用 */
        error_cnt;    /* エラー文字数 */
    time_t t;         /* time関数用 */
    char user_input[MAX_INPUT_LENGTH]; /* ユーザーの入力を保存する配列 */
    
    for (count = 0; count < REPEAT; count++) {
        for (line = 0; line < TEHON_LINE_MAX_NUM; line++) {
            /* 手本文字列の出力と入力処理 */
            printf("%s\n", line_array[line]);
            begin_input = time(&t);
            
            /* 入力を配列に保存 */
            index = 0;
            error_cnt = 0;

            while ((input_char = getchar()) != '\n' && index < MAX_INPUT_LENGTH - 1) {
                user_input[index] = input_char; // ユーザーの入力を保存
                if (line_array[line][index] != '\0') {
                    if (input_char != line_array[line][index]) {
                        error_cnt++;
                    }
                    index++;
                }
            }
            user_input[index] = '\0'; // 入力の終了を示す

            end_input = time(&t);
            /* 入力時間による該当メッセージの表示処理 */
            input_time = end_input - begin_input;
            sum_input_time += input_time;
            printf("time=%d  ", input_time);
            printf("sum_time=%d  ", sum_input_time);
            printf("error count=%d\n", error_cnt);

            /* 入力と正解を比較して間違いを表示 */
            printf("Correct: %s\n", line_array[line]);
            printf("Input:   %s\n", user_input);
            printf("         ");
            for (int i = 0; i < index; i++) {
                if (line_array[line][i] != user_input[i]) {
                    printf("^"); // 間違った文字の場所に ^ を表示
                } else {
                    printf(" "); // 正しい場所にはスペース
                }
            }
            printf("\n");

            if (error_cnt == 0) {
                if (input_time <= GOOD_TIME) {
                    printf("すばらしい！\n");
                } else {
                    if (input_time >= NG_TIME) {
                        printf("がんばって！\n");
                    } else {
                        printf("その調子！\n");
                    }
                }
            } else {
                printf("タイプミスがあります。\n");
            }
        }
    }
}
