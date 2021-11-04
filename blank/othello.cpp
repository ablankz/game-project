#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int game_mode_select(void);
void multi_mode(void);
int turn_select(char player[]);
void confirm(int* flag);
int game(char py1[],char py2[]);
void display(char py1[],char py2[]);
int whole_check(int check_board[][2],int turn);
int single_check(int i,int j,int turn,int signal);
int check_display(int turn,char turn_username[],int select_point[]);
void p_exe(int i,int j,int turn,int signal);

//othello board
int board[9][9]={
    {100,100,100,100,100,100,100,100},
    {100,0,0,0,0,0,0,0,0},
    {100,0,0,0,0,0,0,0,0},
    {100,0,0,0,0,0,0,0,0},
    {100,0,0,0,2,1,0,0,0},
    {100,0,0,0,1,2,0,0,0},
    {100,0,0,0,0,0,0,0,0},
    {100,0,0,0,0,0,0,0,0},
    {100,0,0,0,0,0,0,0,0},
};
//chane
int chane[8]={1,1,1,1,1,1,1,1};


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
    char confirm_key,buf[256];
    printf("If the above content are acceptable, please put 'y'. If you want to modify the above content, please put other key (other than 'y').\n>>> ");
    fgets(buf,256,stdin);
    sscanf(buf,"%c",&confirm_key);
    if(confirm_key=='y') *flag = 0;
    else printf("\n");
    return;
}

void display(char py1[],char py2[]){
    int i,j;
    printf("\n%s :: @\n%s :: *\nempty :: -\n\n",py1,py2);
    printf("    1  2  3  4  5  6  7  8 \n");
    for(i=1;i<=8;++i){
        printf(" %d ",i);
        for(int j=1;j<=8;++j){
            switch(board[i][j]){
                case 0:
                    printf(" - ");
                    break;
                case 1:
                    printf(" @ ");
                    break;
                case 2:
                    printf(" * ");
                    break;
                default:
                    exit(-1);
            }
        }
        printf("\n");
    }
    printf("\n");
    return;
}


/*
 * @return alone_mode >> 0 multi_mode >>1
 *
*/
int game_mode_select(void){
    char game_mode,buf[256];
    int flag=1;
    printf("===============Please select game mode===============\n\n");
    while(flag){
        printf("If you want to play alone, please put 'a'. If you want to play with two people, please put 'b'(if you select this mode, you cannot earn points.).\n>>> ");
        fgets(buf,256,stdin);
        sscanf(buf,"%c",&game_mode);
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
    char p1_name[256],p2_name[256],buf[512];
    //win player (0->draw)
    int winner,load,name_flag=1;
    printf("Plaese player1 name.\n>>> ");
    fgets(buf,512,stdin);
    sscanf(buf,"%255s",p1_name);
    while(name_flag){
        printf("\nPlaese player2 name.\n>>> ");
        fgets(buf,512,stdin);
        sscanf(buf,"%255s",p2_name);
        if(strcmp(p1_name,p2_name)){
            name_flag=0;
        }else{
            printf("Please use a different name from player1.\n");
        }
    }
    printf("\n");    //turn_select 0->first 1->second
    if(turn_select(p1_name)){
        printf("\n%s :: first turn(black:@)\n%s :: second turn(white:*)\n",p2_name,p1_name);
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
        printf("\n%s :: first turn(black:@)\n%s :: second turn(white:*)\n",p1_name,p2_name);
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
        printf("%s::winner!!\n",p1_name);
    }else{
        printf("%s::winner!!\n",p2_name);
    }

    return;
}

/*
 * @param py1 -> first atacker py2 -> second atacker
 * @return py1 win -> 0 py2 win ->1 draw -> 2
*/
int game(char py1[],char py2[]){
    int winner=0,select_point[2],i,turn;
    char turn_user[256];
    for(i=0;;++i){
        turn = i % 2 + 1;
        if(turn==1){
            strcpy(turn_user,py1);
        }else{
            strcpy(turn_user,py2);
        }
        printf("\nturn <%d>\n",i+1);
        //display
        display(py1,py2);
        if(check_display(turn,turn_user,select_point)){
            p_exe(select_point[0],select_point[1],turn,-1);
        }
    }
    return winner;
}

void p_exe(int i,int j,int turn,int signal){
    int a,b,min_a,max_a,min_b,max_b,para[8];// clockDirection
    int op_turn; 
    int num=0,a_key,b_key,t_b_key,p,tool[8][2],result=0;

    op_turn= (turn==1) ? 2:1;

    if(signal<0){
        board[i][j]=turn;
        if(i==1){
            min_a=i;
            a_key=1;
        }else{
            min_a=i-1;
            a_key=0;
        }
        if(j==1){
            min_b=j;
            b_key=1;
            t_b_key=1;
        }else{
            min_b=j-1;
            b_key=0;
            t_b_key=0;
        }

        max_a = (i==8) ? i : i+1;
        max_b = (j==8) ? j : j+1;

        for(a=min_a;a<=max_a;++a,++a_key){
            for(b=min_b;b<=max_b;++b,++b_key){
                if(board[a][b]==op_turn){
                    tool[num][0]=a;
                    tool[num][1]=b;
                    para[num++]=a_key*10+b_key;
                }
            }
            b_key=t_b_key;
        }
        for(p=0;p<num;++p){
            p_exe(i,j,turn,para[p]);
        }
    }else{
        switch(signal){
            case 0:
                //left-top
                if(i-chane[0]==1) return;
                if(j-chane[0]==1) return;
                if(board[i-chane[0]-1][j-chane[0]-1]==op_turn){
                    ++chane[0];
                    p_exe(i,j,turn,signal);
                    return;
                }else if(board[i-chane[0]-1][j-chane[0]-1]==turn){
                    for(int exe_i=1;exe_i<=chane[0];++exe_i){
                        board[i-exe_i][j-exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 1:
                //middle-top
                if(i-chane[1]==1) return;
                if(board[i-chane[1]-1][j]==op_turn){
                    ++chane[1];
                    p_exe(i,j,turn,signal);
                }else if(board[i-chane[1]-1][j]==turn){
                    for(int exe_i=1;exe_i<=chane[1];++exe_i){
                        board[i-exe_i][j]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 2:
                //right-top
                if(i-chane[2]==0) return;
                if(j+chane[2]==8) return;
                if(board[i-chane[2]-1][j+chane[2]+1]==op_turn){
                    ++chane[2];
                    p_exe(i,j,turn,signal);
                }else if(board[i-chane[2]-1][j+chane[2]+1]==turn){
                    for(int exe_i=1;exe_i<=chane[2];++exe_i){
                        board[i-exe_i][j+exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 10:
                //left-middle
                if(j-chane[3]==1) return;
                if(board[i][j-chane[3]-1]==op_turn){
                    ++chane[3];
                    p_exe(i,j,turn,signal);
                }else if(board[i][j-chane[3]-1]==turn){
                    for(int exe_i=1;exe_i<=chane[3];++exe_i){
                        board[i][j-exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 12:
                //right-middle
                if(j+chane[4]==8) return;
                if(board[i][j+chane[4]+1]==op_turn){
                    ++chane[4];
                    p_exe(i,j,turn,signal);
                }else if(board[i][j+chane[4]+1]==turn){
                    for(int exe_i=1;exe_i<=chane[4];++exe_i){
                        board[i][j+exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 20:
                //left-bottom
                if(i+chane[5]==8) return;
                if(j-chane[5]==1) return;
                if(board[i+chane[5]+1][j-chane[5]-1]==op_turn){
                    ++chane[5];
                    p_exe(i,j,turn,signal);
                }else if(board[i+chane[5]+1][j-chane[5]-1]==turn){
                    for(int exe_i=1;exe_i<=chane[5];++exe_i){
                        board[i+exe_i][j-exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 21:
                //middle-bottom
                if(i+chane[6]==8) return;
                if(board[i+chane[6]+1][j]==op_turn){
                    ++chane[6];
                    p_exe(i,j,turn,signal);
                }else if(board[i+chane[6]+1][j]==turn){
                    for(int exe_i=1;exe_i<=chane[6];++exe_i){
                        board[i+exe_i][j]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            case 22:
                //left-bottom
                if(i+chane[7]==8) return;
                if(j+chane[7]==8) return;
                if(board[i+chane[7]+1][j+chane[7]+1]==op_turn){
                    ++chane[7];
                    p_exe(i,j,turn,signal);
                }else if(board[i+chane[7]+1][j+chane[7]+1]==turn){
                    for(int exe_i=1;exe_i<=chane[7];++exe_i){
                        board[i+exe_i][j+exe_i]=turn;
                    }
                    return;
                }else{
                    return;
                }
                break;
            default:
                exit(-1);
        }
    }
    for(int df_chane=0;df_chane<8;++df_chane){
        chane[df_chane]=1;
    }
    return;
}

int check_display(int turn,char turn_username[],int select_point[]){
    int able_num,flag=1,key=0,check_board[64][2];
    char buf[256];
    printf("%s:: turn\n",turn_username);
    able_num=whole_check(check_board,turn);
    if(!able_num){
        printf("your_able_point >> 0\nPlease wait until the next turn.\n\n");
        return 0;
    }
    while(flag){
        printf("your_able_point >> %d\n",able_num);
        for(int i=0;i<able_num;++i){
                printf("(%d,%d) ",check_board[i][0],check_board[i][1]);
        }
        printf("\n\nPlease enter the position you want to place in the following format.\n");
        printf("verticalNumber horizontalNumber(Ex.3 4)\n >>>");
        fgets(buf,256,stdin);
        sscanf(buf,"%d %d",&select_point[0],&select_point[1]);
        printf("\nyour select ==>>>> (%d,%d)\n\n",select_point[0],select_point[1]);
        confirm(&flag);
        if(flag){
            break;
        }
        for(int i=0;i<able_num;++i){
            if(select_point[0]==check_board[i][0] && select_point[1]==check_board[i][1]) 
                ++key;
        }
        if(!key){
            printf("\nYou can't put it there!\nPlease select position again.\n");
            flag=1;
        }
    }
    return able_num;
}


int whole_check(int check_board[][2],int turn){
    int i,j,num=0;
    for(i=1;i<=8;++i){
        for(j=1;j<=8;++j){
            if(single_check(i,j,turn,-1)){
                check_board[num][0] = i;
                check_board[num++][1] = j;
            }
        }
    }
    check_board[num][0]='\0';
    check_board[num][1]='\0';
    return num;
}

/*
 * disable >> 0 : enable >> 1 
*/
int single_check(int i,int j,int turn,int signal){
    int a,b,min_a,max_a,min_b,max_b,para[8];// clockDirection
    int op_turn; 
    int num=0,a_key,b_key,t_b_key,p,tool[8][2],result=0;

    op_turn= (turn==1) ? 2:1;

    if(signal<0){
        if(board[i][j]){
            return 0;
        }

        if(i==1){
            min_a=i;
            a_key=1;
        }else{
            min_a=i-1;
            a_key=0;
        }
        if(j==1){
            min_b=j;
            b_key=1;
            t_b_key=1;
        }else{
            min_b=j-1;
            b_key=0;
            t_b_key=0;
        }

        max_a = (i==8) ? i : i+1;
        max_b = (j==8) ? j : j+1;

        for(a=min_a;a<=max_a;++a,++a_key){
            for(b=min_b;b<=max_b;++b,++b_key){
                if(board[a][b]==op_turn){
                    tool[num][0]=a;
                    tool[num][1]=b;
                    para[num++]=a_key*10+b_key;
                }
            }
            b_key=t_b_key;
        }
        for(p=0;p<num;++p){
            if(single_check(tool[p][0],tool[p][1],turn,para[p])){
                result=1;
                break;
            }
        }

    }else{
        switch(signal){
            case 0:
                //left-top
                if(i==1) return 0;
                if(j==1) return 0;
                if(board[i-1][j-1]==op_turn){
                    if(single_check(i-1,j-1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i-1][j-1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 1:
                //middle-top
                if(i==1) return 0;
                if(board[i-1][j]==op_turn){
                    if(single_check(i-1,j,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i-1][j]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 2:
                //right-top
                if(i==1) return 0;
                if(j==8) return 0;
                if(board[i-1][j+1]==op_turn){
                    if(single_check(i-1,j+1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i-1][j+1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 10:
                //left-middle
                if(j==1) return 0;
                if(board[i][j-1]==op_turn){
                    if(single_check(i,j-1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i][j-1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 12:
                //right-middle
                if(j==8) return 0;
                if(board[i][j+1]==op_turn){
                    if(single_check(i,j+1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i][j+1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 20:
                //left-bottom
                if(i==8) return 0;
                if(j==1) return 0;
                if(board[i+1][j-1]==op_turn){
                    if(single_check(i+1,j-1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i+1][j-1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 21:
                //middle-bottom
                if(i==8) return 0;
                if(board[i+1][j]==op_turn){
                    if(single_check(i+1,j,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i+1][j]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            case 22:
                //left-bottom
                if(i==8) return 0;
                if(j==8) return 0;
                if(board[i+1][j+1]==op_turn){
                    if(single_check(i+1,j+1,turn,signal)){
                        return 1;
                    }else{
                        return 0;
                    }
                }else if(board[i+1][j+1]==turn){
                    return 1;
                }else{
                    return 0;
                }
                break;
            default:
                exit(-1);
        }
    }
    return result;
}

/*
 * @return first ->0 second ->1 
*/
int turn_select(char player[]){
    char attack_turn,confirm_key,buf[256];
    int result,flag=1;
    printf("%s:: Please select attack turn.\n\n",player);
    while(flag){
        printf("If you want to select random, please put 'r'. If you want to select first attack, please select 'a'. If you want to select second attack, please select 'b'.\n>>> ");
        fgets(buf,256,stdin);
        sscanf(buf,"%c",&attack_turn);
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
