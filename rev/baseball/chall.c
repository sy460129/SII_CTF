// gcc -o chall chall.c -no-pie -Wl,-z,relro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long 
struct team{
    char* name;
    char* member[9];
} teams[11];
char* team_name[] = {
    "KOREA", "TIGERS", "LIONS", "TWINS", "BEARS", "WIZ", "LANDERS", "GIANTS", "EAGLES", "DINOS", "HEROES"
};

char* name[][9] = {
    {"KBO", "FIGHTING!"},
    {"Yang Hyeon-jong", "Kim Do-Yeong"},
    {"Won Tae-In", "Koo Ja-Wook"},
    {"Im Chan-Kyu", "Oh Ji-hwan"},
    {"Gwak Been", "Yang Eui-Ji"},
    {"Ko Young-pyo", "Kang Baek-Ho"},
    {"Kim Kwang-hyun", "Choi Jeong"},
    {"Park Se-woong", "Jeon Jun-woo"},
    {"Ryu Hyeon-jin", "Roh Si-hwan"},
    {"Koo Chang-Mo", "Park Min-Woo"},
    {"An Woo-jin",  "SONG Sung-mun"}
};
void init(){
    setvbuf(stdin, 0, 2, 0);
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stderr, 0, 2, 0);

    for(int i = 0; i <= 10; i++){
        teams[i].name = team_name[i];
        for(int j = 0; j < 2; j++){
            teams[i].member[j] = name[i][j];
        }
    }
}

void menu(){
    printf("/bin/sh"); // what is /bin/sh??
    puts("\n");
    printf("1. Trade\n");
    printf("2. Add Players\n");
    printf("3. Print\n");
    printf("4. Exit\n");
    printf("> ");
}

void print_members(int idx){
    printf("%s: ", teams[idx].name);
    for(int i = 0; i < 10 && teams[idx].member[i] != NULL; i++){
        printf("%s", teams[idx].member[i]);
        if(i != 9 && teams[idx].member[i + 1] != NULL) printf(", ");
    }
    printf("\n");
}

void trade_subplayer(){
    int idx;
    char* player;
    printf("select team: ");
    scanf("%d", &idx);

    printf("player: ");
    scanf("%llx", &player);

    teams[idx].name = player;
    printf("trade succeed\n");
    
    return;
}
void add_players(){
    printf("which team? ");
    int idx;
    scanf("%d", &idx);
    printf("selected team: %s\n", &teams[idx].name);

    char player[5];
    for(int i = 0; i < 10; i++){
        if(teams[idx].member[i] == NULL){
            printf("Who? ");
            scanf("%4s", &player);

            teams[idx].member[i] = strdup(player);
            printf("%s is now team %s", player, teams[idx].name);
            return;
        }
    }
    printf("Full\n");
    return;
}

void print(){
    printf("which team? ");
    int idx;
    scanf("%d", &idx);

    if(idx > 10 || idx < 0) idx = 0;
    print_members(idx);
    return;
}
int main(){

    init();
    

    while(1){
        menu();
        int idx;
        scanf("%d", &idx);
        
        switch(idx){
            case 1:
                trade_subplayer();
                break;
            case 2:
                add_players();
                break;
            case 3:
                print();
                break;
            case 4:
                printf("Good Luck..\n");
                exit(0);
            default:
                printf("retry\n");
                break;            
        }
    }
}