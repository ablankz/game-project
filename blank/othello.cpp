#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game_mode_select(void);
void multi_mode(void);
int turn_select(char player[]);
void confirm(int* flag);
int game(char py1[],char py2[]);

int main(void){
    if(game_mode_select()){
        // multi_mode
        multi_mode();
    }else{
        //alone_mode
    }

    return 0;
}

void confirm(int* flag){
    char confirm_key;
    printf("If the above content are acceptable, please put 'y'. If you want to modify the above content, please put other key (other than 'y').\n>>> ");
    scanf(" %c",&confirm_key);
    if(confirm_key=='y') *flag = 0;
    else printf("\n");
    return;
}

/*
 * @return alone_mode >> 0 multi_mode >>1
 *
*/
int game_mode_select(void){
    char game_mode;
    int flag=1;
    printf("===============Please select game mode===============\n\n");
    while(flag){
        printf("If you want to play alone, please put 'a'. If you want to play with two people, please put 'b'(if you select this mode, you cannot earn points.).\n>>> ");
        scanf(" %c",&game_mode);
        if(game_mode=='a'){
            printf("\nyour select ==>>>> alone mode\n\n");
            confirm(&flag); 
        }else if(game_mode=='b'){
            printf("\nyour select ==>>>> multi mode (user-to-user)\n\n");
            confirm(&flag);
        }else{
            printf("There is a mistake in your key. Please check again.\n\n");
        }
    }
    printf("\n");
    return (game_mode=='a') ? 0 : 1 ;  
}

void multi_mode(void){
    char p1_name[128],p2_name[128];
    //win player (0->draw)
    int winner,load;
    printf("Plaese player1 name.\n>>> ");
    scanf("%127s",p1_name);
    printf("\nPlaese player2 name.\n>>> ");
    scanf("%127s",p2_name);
    printf("\n");
    //turn_select 0->first 1->second
    if(turn_select(p1_name)){
        printf("\n%s :: first turn\n%s :: second turn\n",p2_name,p1_name);
        //return 0 -> p2 win:1 -> p1 win draw -> 2
        load = game(p2_name,p1_name);
        if(!load){
            winner=2;
        }else if(load==1){
            winner=1;
        }else{
            winner=0;
        }
    }else{
        printf("\n%s :: first turn\n%s :: second turn\n",p1_name,p2_name);
        //return 0 -> p1 win:1 -> p2 win draw -> 2
        load = game(p1_name,p2_name);
        if(!load){
            winner=1;
        }else if(load==1){
            winner=2;
        }else{
            winner=0;
        } 
    }
    if(!winner){
        printf("draw!!\n");
    }else if(winner==1){
        printf("%s::winner!!",p1_name);
    }else{
        printf("%s::winner!!",p2_name);
    }

    return;
}

/*
 * @param py1 -> first atacker py2 -> second atacker
 * @return py1 win -> 0 py2 win ->1 draw -> 2
*/
int game(char py1[],char py2[]){
    int winner=0;

    return winner;
}

/*
 * @return first ->0 second ->1 
*/
int turn_select(char player[]){
    char attack_turn,confirm_key;
    int result,flag=1;
    printf("%s:: Please select attack turn.\n\n",player);
    while(flag){
        printf("If you want to select random, please put 'r'. If you want to select first attack, please select 'a'. If you want to select second attack, please select 'b'.\n>>> ");
        scanf(" %c",&attack_turn);
        if(attack_turn=='a'){
            printf("\nyour select ==>>>> first attack\n\n");           
            confirm(&flag);
        }else if(attack_turn=='b'){
            printf("\nyour select ==>>>> second attack\n\n");           
            confirm(&flag);
        }else if(attack_turn=='r'){
            printf("\nyour select ==>>>> attack turn random\n\n");           
            confirm(&flag);
        }else{
            printf("There is a mistake in your key. Please check again.\n\n");
        }
    }
    if(attack_turn=='a'){
        return 0;
    }else if(attack_turn=='b'){
        return 1;
    }else{
        srand((unsigned int)time(NULL));
        return (rand()%2) ? 1 : 0;
    }
}