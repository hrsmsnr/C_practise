#include <stdio.h>
#include <time.h>

#define REPEAT       2        /* タイピング練習回数 */
#define TEHON_LINE_MAX_NUM 2  /* 手本文字列の個数 */
#define GOOD_TIME    20       /* 入力時間(GOOD) */
#define NG_TIME      40       /* 入力時間(NG) */

char line_array[][30] = 
    {
        "I have some good news",
        "Let's do something fun"
    };

void correct_training(void);

int main(void)
{
    printf("＜タイピングゲーム開始＞\n");
    correct_training();
    return 0;
}
void correct_training(void)
{
  int    input_char,   /* キーボードからの入力データ（一文字） */
         count,        /* タイピング回数の計算用 */
         line,         /* 使用する手本文字列の判定用 */
         begin_input,  /* 入力の開始時刻 */
         end_input,    /* 入力の終了時刻 */
         input_time,   /* 入力時間 */
         sum_input_time = 0,   /* 合計入力時間 */
         index,        /* 文字配列の添え字用 */
         error_cnt;        /* エラー文字数 */
  time_t t;     /* time関数用 */

  for (count = 0; count < REPEAT; count++)
  {
    for (line = 0; line < TEHON_LINE_MAX_NUM; line++)
    {
    /* 手本文字列の出力と入力処理 */
      printf("%s\n", line_array[line]);
      begin_input = time (&t);
/* 入力エラー分析処理 */
      index = 0;
      error_cnt = 0;

      while ((input_char = getchar()) != '\n')
      {
        if (line_array[line][index] != '\0')
        {
          if (input_char != line_array[line][index])
          {
              error_cnt++;
          }
          index++;
        }
      }
      end_input = time (&t);
      /* 入力時間による該当メッセージの表示処理 */
      input_time = end_input - begin_input;
      sum_input_time += input_time;
      printf("time=%d  " , input_time);
      printf("sum_time=%d  " , sum_input_time);
      printf("error count =%d\n", error_cnt);
      if (error_cnt == 0) {
         if (input_time <= GOOD_TIME)
        {
          printf("すばらしい！\n");
        }else{
          if (input_time >= NG_TIME)
          {
              printf("がんばって！\n");
          }else{
              printf("その調子！\n");
          }
        }
      }else{
        printf("タイプミスがあります。\n");
      }
    }
  }
}