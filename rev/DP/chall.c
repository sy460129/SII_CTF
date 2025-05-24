#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define len 46
const char* flag = "real_flag_is_here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
int dp[len + 1][len + 1], origin[len + 1][len + 1], ans[len + 1][len + 1];
void init(){
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);
}
int cmp(int a, int b){
    return a > b ? a : b;
}
int main(){
    init();
    srand(time(NULL));
    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            if(!(i ^ j)) dp[i][j] = flag[i-1];
            else dp[i][j] = (rand() % 256);
            origin[i][j] = dp[i][j];
        }
    }
    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            dp[i][j] = cmp(dp[i - 1][j], dp[i][j - 1]) ^ dp[i][j];
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    printf("Your input: \n");

    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            scanf("%d", &ans[i][j]);
            if(ans[i][j] != origin[i][j]){
                printf("Hmm..\n");
                exit(0);
            }
        }
    }
    puts("Correct!");
    printf("FLAG is SII{");
    for(int i = 1; i <= len; i++){
        printf("%c", ans[i][i]);
    }
    puts("}\n");
}