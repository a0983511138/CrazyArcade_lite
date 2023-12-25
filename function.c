#include "myheader.h"

mapstruct **create_matrix2(int row, int col){
// input rows and cols
// output a pointer to 2D mat[rows][cols]

    mapstruct **mat = (mapstruct **) malloc(sizeof(mapstruct *)*row);
    int i=0,j=0;
    for(i=0; i<row; i++)
    // Allocate array, store pointer
        mat[i] = (mapstruct *) malloc(sizeof(mapstruct)*col);

    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            mat[i][j].basic=0;
            mat[i][j].character=0;
            mat[i][j].movetrap=0;
       }
    }
    return mat;
}
struct bomb *create_matrix1(int row){
// input rows and cols
// output a pointer to 2D mat[rows][cols]

    struct bomb *mat = (struct bomb*) malloc(sizeof(struct bomb)*row);
    int i=0;

    for(i=0; i<row; i++){

            mat[i].count=0;
            mat[i].delay=0;
            mat[i].power=0;
            mat[i].x=0;
            mat[i].y=0;
    }
    return mat;
}

void readfile_array(mapstruct **mat,int row,int col,int n){
    FILE *fptr;
    int i,j;

    if (n == 1)         fptr=fopen("array.txt","r");
    else if (n == 2)    fptr=fopen("array2.txt","r");
    else if (n == 3)    fptr=fopen("array3.txt","r");
    for(i=1;i<row-1;i++){
        for(j=0;j<col;j++){
            fscanf(fptr,"%d\t",&mat[i][j].basic);
        }
    }
    for(i=1;i<row-1;i++){
        for(j=0;j<col;j++){
            fscanf(fptr,"%d\t",&mat[i][j].item);
        }
    }
    fclose(fptr);
}
int movecharacter( ALLEGRO_EVENT events,mapstruct **map,struct bomb *bomb,struct boss *boss,int i,int j,int *wave){

    if (events.keyboard.keycode==ALLEGRO_KEY_LEFT) {
        if(map[i][j-1].basic==2 || (map[i][j-1].item==1 && map[i][j-1].basic==13)|| map[i][j-1].basic==13){
            map[i][j].character=0;
            map[i][j-1].character=1;
            *wave=*wave*-1;
            if( map[i][j-1].item==1)
            {
                 map[i][j-1].item=0;
                 map[i][j-1].basic=2;
                 if(bomb[0].count < 4)   bomb[0].count++;
            }
            if( map[i][j-1].item==2)    return 0;
        }
        if((i == boss->bombX || i == boss->bombX + 1) && (j - 1 == boss->bombY + 1)) return 0;
    }
    else if (events.keyboard.keycode==ALLEGRO_KEY_RIGHT) {
        if(map[i][j+1].basic==2 || (map[i][j+1].item==1 && map[i][j+1].basic==13) || map[i][j+1].basic==13){
            map[i][j].character=0;
            map[i][j+1].character=2;
            *wave=*wave*-1;
            if( map[i][j+1].item==1)
            {
                 map[i][j+1].item=0;
                 map[i][j+1].basic=2;
                 if(bomb[0].count < 4)   bomb[0].count++;
            }
            if( map[i][j+1].item==2) return 0;
        }
        if((i == boss->bombX || i == boss->bombX + 1) && (j + 1 == boss->bombY )) return 0;
    }

    else if (events.keyboard.keycode==ALLEGRO_KEY_UP){
        if(map[i-1][j].basic==2 || (map[i-1][j].item==1 && map[i-1][j].basic==13) || map[i-1][j].basic==13){
            map[i][j].character=0;
            map[i-1][j].character=3;
            *wave=*wave*-1;
            if( map[i-1][j].item==1)
            {
                 map[i-1][j].item=0;
                 map[i-1][j].basic=2;
                 if(bomb[0].count < 4)   bomb[0].count++;
            }
            if( map[i-1][j].item==2) return 0;
        }
        if((i - 1 == boss->bombX + 1) && (j == boss->bombY + 1 || j == boss->bombY)) return 0;
    }
    else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN) {
        if(map[i+1][j].basic==2 || (map[i+1][j].item==1 && map[i+1][j].basic==13) || map[i+1][j].basic==13){
            map[i][j].character=0;
            map[i+1][j].character=4;
            *wave=*wave*-1;
            if( map[i+1][j].item==1)
            {
                 map[i+1][j].item=0;
                 map[i+1][j].basic=2;
                 if(bomb[0].count < 4)   bomb[0].count++;
            }
            if( map[i+1][j].item==2) return 0;
        }
        if((i + 1 == boss->bombX) && (j == boss->bombY + 1 || j == boss->bombY)) return 0;
    }
    return 1;
    /* make sure the paddles don go off screen */

}
void init1(struct bomb *bomb)
{
    int i;
    //system("pause");
    bomb[0].count = 1;

    for(i = 0 ;i < 3 ;i++)
    {
        bomb[i+1].judge = 0;
    }
    bomb[0].delay = 12;
    bomb[0].power = 2;
}
void initial1(struct bomb *bomb,int count,int i,int j)
{
    bomb[count].delay = bomb[0].delay;
    bomb[count].judge = 1;
    bomb[count].power = bomb[0].power;
    bomb[count].x = i;
    bomb[count].y = j;
}

int explosion( ALLEGRO_EVENT events,mapstruct **map,struct bomb *bomb,struct boss *boss,int i,int j,int level)
{
    int count,z,a,b,q,w;

    if (events.keyboard.keycode==ALLEGRO_KEY_LCTRL)
    {
        for(count = 1 ;count < bomb[0].count + 1 ;count++)
        {
            if(bomb[count].judge == 0)
            {
                map[i][j].basic = 4;
                initial1(bomb,count,i,j);
                a=i;
                b=j;
                break;
            }
        }
    }

    for(count = 1 ;count < bomb[0].count + 1 ;count++)
    {
        if(bomb[count].judge == 1)
        {
            bomb[count].delay -=1 ;

            if(bomb[count].delay == 2)
            {
                map[bomb[count].x][bomb[count].y].basic = 5;

                for (q=0;q<=bomb[count].power;q++){
                    if((map[bomb[count].x+q][bomb[count].y].basic==2||map[bomb[count].x+q][bomb[count].y].basic==12)&& q<bomb[count].power){
                        if(map[bomb[count].x+q][bomb[count].y].basic==12){
                            map[bomb[count].x+q][bomb[count].y].basic=6;
                            break;
                        }
                        map[bomb[count].x+q][bomb[count].y].basic=6;
                    }else if((map[bomb[count].x+q][bomb[count].y].basic==2||map[bomb[count].x+q][bomb[count].y].basic==12)&& q==bomb[count].power&&map[bomb[count].x+q-1][bomb[count].y].basic==6){
                        map[bomb[count].x+q][bomb[count].y].basic=9;
                    }
                }
                for (q=0;q<=bomb[count].power;q++){
                    if((map[bomb[count].x-q][bomb[count].y].basic==2||map[bomb[count].x-q][bomb[count].y].basic==12)&& q<bomb[count].power){
                        if(map[bomb[count].x-q][bomb[count].y].basic==12){
                            map[bomb[count].x-q][bomb[count].y].basic=6;
                            break;
                        }
                        map[bomb[count].x-q][bomb[count].y].basic=6;
                    }else if((map[bomb[count].x-q][bomb[count].y].basic==2||map[bomb[count].x-q][bomb[count].y].basic==12)&& q==bomb[count].power&&map[bomb[count].x-q+1][bomb[count].y].basic==6){
                        map[bomb[count].x-q][bomb[count].y].basic=8;
                    }
                }
                for (q=0;q<=bomb[count].power;q++){
                    if((map[bomb[count].x][bomb[count].y+q].basic==2||map[bomb[count].x][bomb[count].y+q].basic==12)&& q<bomb[count].power){
                        if(map[bomb[count].x][bomb[count].y+q].basic==12){
                            map[bomb[count].x][bomb[count].y+q].basic=7;
                            break;
                        }
                        map[bomb[count].x][bomb[count].y+q].basic=7;
                    }else if((map[bomb[count].x][bomb[count].y+q].basic==2||map[bomb[count].x][bomb[count].y+q].basic==12)&& q==bomb[count].power&&map[bomb[count].x][bomb[count].y+q-1].basic==7){
                        map[bomb[count].x][bomb[count].y+q].basic=11;
                    }
                }
                for (q=0;q<=bomb[count].power;q++){
                    if((map[bomb[count].x][bomb[count].y-q].basic==2||map[bomb[count].x][bomb[count].y-q].basic==12)&& q<bomb[count].power){
                        if(map[bomb[count].x][bomb[count].y-q].basic==12){
                            map[bomb[count].x][bomb[count].y-q].basic=7;
                            break;
                        }
                        map[bomb[count].x][bomb[count].y-q].basic=7;
                    }else if((map[bomb[count].x][bomb[count].y-q].basic==2||map[bomb[count].x][bomb[count].y-q].basic==12)&& q==bomb[count].power&&map[bomb[count].x][bomb[count].y-q+1].basic==7){
                        map[bomb[count].x][bomb[count].y-q].basic=10;
                    }
                }
                if(map[i][j].basic >= 5 && map[i][j].basic <= 11){
                    map[i][j].character = 0;
                    return 0;
                }
                if(level == 3){
                    if((map[boss->X][boss->Y].basic         >= 5 && map[boss->X][boss->Y].basic         <= 11) ||
                       (map[boss->X + 1][boss->Y + 1].basic >= 5 && map[boss->X + 1][boss->Y + 1].basic <= 11) ||
                       (map[boss->X + 1][boss->Y].basic     >= 5 && map[boss->X + 1][boss->Y].basic     <= 11) ||
                       (map[boss->X][boss->Y + 1].basic     >= 5 && map[boss->X][boss->Y + 1].basic     <= 11))
                        boss->life --;
            }
            }
            if(bomb[count].delay == 0){
                        if(map[bomb[count].x][bomb[count].y].basic==5){
                            if(map[bomb[count].x][bomb[count].y].item == 1)
                                map[bomb[count].x][bomb[count].y].basic=13;
                            else
                                map[bomb[count].x][bomb[count].y].basic=2;
                        }
                        judgeexplosion(map,bomb[count].x,bomb[count].y,1,1,bomb[count].power);
                        judgeexplosion(map,bomb[count].x,bomb[count].y,1,-1,bomb[count].power);
                        judgeexplosion(map,bomb[count].x,bomb[count].y,2,1,bomb[count].power);
                        judgeexplosion(map,bomb[count].x,bomb[count].y,2,-1,bomb[count].power);

                    bomb[count].judge = 0;
            }
        }
    }
    return 1;
}
void moveboss(struct boss *boss,int *bossbombwave){
    int mode;


    mode = rand()%8;
    switch (mode){
        case 0:
            if(boss->Y != 1)
                boss->Y--;
            break;
        case 1:
            if(boss->Y != 10)
                boss->Y++;
            break;
        case 2:
            if(boss->X != 2)
                boss->X--;
            break;
        case 3:
            if(boss->X != 9)
                boss->X++;
            break;
        case 4:
            if(boss->bombX == -2 && boss->bombY == -2){
                boss->bombX = boss->X;
                boss->bombY = boss->Y;
                boss->direction = 1;
            }
            break;
        case 5:
            if(boss->bombX  == -2 && boss->bombY == -2){
                boss->bombX = boss->X;
                boss->bombY = boss->Y + 1;
                boss->direction = 2;
            }
            break;
        case 6:
            if(boss->bombX == -2 && boss->bombY == -2){
                boss->bombX = boss->X;
                boss->bombY = boss->Y;
                boss->direction = 3;
            }
            break;
        case 7:
            if(boss->bombX == -2 && boss->bombY == -2){
                boss->bombX = boss->X + 1;
                boss->bombY = boss->Y;
                boss->direction = 4;
            }
            break;
    }
    if(boss->direction == 1)  {boss->bombY--;*bossbombwave=*bossbombwave*(-1);}
    else if(boss->direction == 2)  {boss->bombY++;*bossbombwave=*bossbombwave*(-1);}
    else if(boss->direction == 3)  {boss->bombX--;*bossbombwave=*bossbombwave*(-1);}
    else if(boss->direction == 4)  {boss->bombX++;*bossbombwave=*bossbombwave*(-1);}

    if(boss->bombX <= 1 || boss->bombX >= 10 || boss->bombY <= 0 || boss->bombY >= 11) {boss->bombX = -2;boss->bombY = -2;}
}
void judgeexplosion(mapstruct **map,int x,int y,int way,int q,int power)
{
    if(way == 1){
        if(q == power || q == -power){
            if(q>1){
                if(map[x+q][y].basic==9){
                    if(map[x+q][y].item == 1)
                        map[x+q][y].basic=13;
                    else
                        map[x+q][y].basic=2;
                }
            }
            else{
                if(map[x+q][y].basic==8){
                    if(map[x+q][y].item == 1)
                        map[x+q][y].basic=13;
                    else
                        map[x+q][y].basic=2;
                }
            }
        }
        else{
            if(map[x+q][y].basic==6){
                if(map[x+q][y].item == 1)
                    map[x+q][y].basic=13;
                else
                    map[x+q][y].basic=2;
                if(q > 0)   judgeexplosion(map,x,y,1,q+1,power);
                else    judgeexplosion(map,x,y,1,q-1,power);
            }
        }
    }
    else if (way == 2){
        if(q == power || q == -power){
            if(q>1){
                if(map[x][y+q].basic==11){
                    if(map[x][y+q].item == 1)
                        map[x][y+q].basic=13;
                    else
                        map[x][y+q].basic=2;
                }
            }
            else{
                if(map[x][y+q].basic==10){
                    if(map[x][y+q].item == 1)
                        map[x][y+q].basic=13;
                    else
                        map[x][y+q].basic=2;
                }
            }
        }
        else{
            if(map[x][y+q].basic==7){
                if(map[x][y+q].item == 1)
                    map[x][y+q].basic=13;
                else
                    map[x][y+q].basic=2;
                if(q > 0)   judgeexplosion(map,x,y,2,q+1,power);
                else    judgeexplosion(map,x,y,2,q-1,power);
            }
        }
    }
}

int List_choose( ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap,int List,int *Listrun,int *menu){
    while(*Listrun){
            al_get_keyboard_state(&KBstate);
            if (!al_is_event_queue_empty(event_queue)) {
                while (al_get_next_event(event_queue, &events)) {
                    switch (events.type) {
                    case ALLEGRO_EVENT_KEY_DOWN:
                        if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ *Listrun = 0; menu = 0;List = 4;}
                            if (events.keyboard.keycode==ALLEGRO_KEY_UP){
                                List-=1;
                                if(List<1) List=4;
                            }
                            else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN){
                                List+=1;
                                if(List>4) List=1;
                            }

                            if(List==1) bitmap=al_load_bitmap("./start.png");
                            else if(List==2) bitmap=al_load_bitmap("./select.png");
                            else if(List==3) bitmap=al_load_bitmap("./leaderboard.png");
                            else if(List==4) bitmap=al_load_bitmap("./end.png");
                            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                            al_flip_display();

                            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                                *Listrun=0;
                                if(List==1) return 1;
                                else if(List==2) return 2;
                                else if(List==3) return 3;
                                else if(List==4) return 4;
                            }

                        break;
                    }
                }
            }
        }
}
int Level_choose( ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap,int Level,int *Levelrun,int *menu){
    while(*Levelrun){
            al_get_keyboard_state(&KBstate);
            if (!al_is_event_queue_empty(event_queue)) {
                while (al_get_next_event(event_queue, &events)) {
                    switch (events.type) {
                    case ALLEGRO_EVENT_KEY_DOWN:
                        if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ *Levelrun=0;Level=4; }
                            if (events.keyboard.keycode==ALLEGRO_KEY_UP){
                                Level-=1;
                                if(Level<1) Level=4;
                            }
                            else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN){
                                Level+=1;
                                if(Level>4) Level=1;
                            }
                            if(Level==1) bitmap=al_load_bitmap("./selectlv1.png");
                                else if(Level==2) bitmap=al_load_bitmap("./selectlv2.png");
                                else if(Level==3) bitmap=al_load_bitmap("./selectlv3.png");
                                else if(Level==4) bitmap=al_load_bitmap("./selectback.png");
                                al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                                al_flip_display();

                            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                                *Levelrun=0;
                                if(Level==1) return 1;
                                else if(Level==2) return 2;
                                else if(Level==3) return 3;
                                else if(Level==4) return 4;
                            }
                        break;
                    }
                }
            }
        }
}
int move_trapx(mapstruct **map,int location,int traps,int trape,int *trapjudge,int *snakewave,int charcaterx,int charcatery){
    if(location==traps){
        *trapjudge=2;
    }else if(location==trape){
        *trapjudge=1;
    }
    if(*trapjudge==2){
        map[10][location].movetrap=0;
        map[10][location+1].movetrap=1;
        *snakewave=*snakewave*(-1);
    }
    if(*trapjudge==1){
        map[10][location].movetrap=0;
        map[10][location-1].movetrap=1;
        *snakewave=*snakewave*(-1);
    }
    if(map[charcaterx][charcatery].movetrap==1){
        map[charcaterx][charcatery].character=0;
        return 0;
    }
    return 1;
}
int fixed_trap(mapstruct **map,int charcaterx,int charcatery){
    if(map[charcaterx][charcatery].item==3){
        map[charcaterx][charcatery].character=0;
        return 0;
    }
    return 1;
}
void leaderborad(struct user *userfile){
    FILE *fptr;
    int i,j;
    struct user temp;


    fptr=fopen("user.txt","r");


            fgets(userfile[5].name,4,fptr);

    fclose(fptr);


    fptr=fopen("leaderbord.txt","r");

        for(i=0;i<5;i++){
            fscanf(fptr,"%s\t%d\t",&userfile[i].name,&userfile[i].score);
        }
    fclose(fptr);
    for(j=0;j<=25;j++){
            for(i=0;i<5;i++){
              if(userfile[i].score>userfile[i+1].score){
                temp=userfile[i];
                userfile[i]=userfile[i+1];
                userfile[i+1]=temp;
                }
            }
        }
        for(i=0;i<5;i++){
              printf("%s\t%d\n",userfile[i].name,userfile[i].score);
            }
    fptr=fopen("leaderbord.txt","w");

        for(i=0;i<=4;i++){
            fprintf(fptr,"%s\t%d\t",userfile[i].name,userfile[i].score);
        }
    fclose(fptr);
}
int judgedie(mapstruct **map ,struct bomb *bomb,struct boss *boss,int i,int j){
    if(((boss->X == i     || boss->X + 1 == i    ) && (boss->Y  == j    || boss->Y + 1 == j    ))||
       ((boss->bombX == i || boss->bombX + 1 == i) && (boss->bombY == j || boss->bombY + 1 == j))){
        return 0;
    }
    else
        return 1;
}

int round1(int run,int run2,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue){
    int i,j;

    while (run)
    {
        al_get_keyboard_state(&KBstate);
        if (!al_is_event_queue_empty(event_queue)) {
            while (al_get_next_event(event_queue, &events)) {
                switch (events.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                   run = 0;
                   break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode == ALLEGRO_KEY_F12) run = 0;
                    if(events.keyboard.keycode == ALLEGRO_KEY_P){
                        Pauserun=1;
                        bitmap=al_load_bitmap("./pause_1.jpg");
                        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                        al_flip_display();
                        while(Pauserun){
                            al_get_keyboard_state(&KBstate);
                            if (!al_is_event_queue_empty(event_queue)) {
                            while (al_get_next_event(event_queue, &events)) {
                            switch (events.type) {
                            case ALLEGRO_EVENT_KEY_DOWN:
                            if (events.keyboard.keycode==ALLEGRO_KEY_UP){
                                Pause-=1;
                                if(Pause<1) Pause=2;
                            }
                            else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN){
                                Pause+=1;
                                if(Pause>2) Pause=1;
                            }
                            printf("%d",Pause);
                            if(Pause==1) bitmap=al_load_bitmap("./pause_1.jpg");
                            else if(Pause==2) bitmap=al_load_bitmap("./pause_2.jpg");
                            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                            al_flip_display();

                            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                                Pauserun=0;
                            }
                            break;
                            }
                            }
                            }
                        }
                    }
                    if(run) run = movecharacter(events,map,bomb,boss,a,b,wave); // move the character
                    break;
                }
            }
        }
        if(Pause==2){run=0,run2=0;}
        if(run)
        {
            run = explosion(events,map,bomb,boss,a,b,1);
            run2 = run;
        }
        for(i=1;i<ROW-1;i++){
            for(j=0;j<COL;j++){
                if (map[i][j].item == 2){
                    bitmap = al_load_bitmap("./gate.jpg");
                }
                else if (map[i][j].character!=0){
                    if(map[i][j].character==1){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./left 2.jpg");
                        }
                        else {
                            bitmap = al_load_bitmap("./left 1.jpg");
                        }
                    }
                    else if(map[i][j].character==2){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./right 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./right 2.jpg");
                        }
                    }else if(map[i][j].character==3){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./back 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./back 2.jpg");
                        }
                    }else if(map[i][j].character==4){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./face 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./face 2.jpg");
                        }
                    }
                    a=i;
                    b=j;
                }
                else{
                    if(map[i][j].basic==1){
                        bitmap = al_load_bitmap("./wall.jpg");
                    }
                    else if(map[i][j].basic==2){
                        bitmap = al_load_bitmap("./path.jpg");
                    }
                    else if(map[i][j].basic==3){
                        bitmap = al_load_bitmap("./rock.jpg");
                    }
                    else if(map[i][j].basic==4){
                        bitmap = al_load_bitmap("./bomb.jpg");
                    }
                    else if(map[i][j].basic==5){
                        bitmap = al_load_bitmap("./explosion1 center.png");
                    }
                    else if(map[i][j].basic==6){
                        bitmap = al_load_bitmap("./explosion2 col.png");
                    }
                    else if(map[i][j].basic==7){
                        bitmap = al_load_bitmap("./explosion2 row.jpg");
                    }
                    else if(map[i][j].basic==8){
                        bitmap = al_load_bitmap("./explosion3 top.png");
                    }
                    else if(map[i][j].basic==9){
                        bitmap = al_load_bitmap("./explosion3 down.png");
                    }
                    else if(map[i][j].basic==10){
                        bitmap = al_load_bitmap("./explosion3 left.png");
                    }
                    else if(map[i][j].basic==11){
                        bitmap = al_load_bitmap("./explosion3 right.jpg");
                    }
                    else if(map[i][j].basic==12){
                        bitmap = al_load_bitmap("./botten.jpg");
                    }
                    else if(map[i][j].basic==13){
                        bitmap = al_load_bitmap("./ability_up.jpg");
                    }
                }
                al_register_event_source(alEventQueue, al_get_keyboard_event_source());

                al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),j*60, -60+i*60,60, 60,0);

                al_destroy_bitmap(bitmap);
            }
        }
        al_rest(0.000000001);
        al_flip_display();
    }


    return run2;
}
int round2(int run2,int run3,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue,int *snakewave,int *trapjudge){
    int i ,j,location;

    while (run2)
    {
        al_get_keyboard_state(&KBstate);

        if (!al_is_event_queue_empty(event_queue)) {
          while (al_get_next_event(event_queue, &events)) {
             switch (events.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                   run2 = 0;
                   break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode == ALLEGRO_KEY_F12)  run2 = 0;
                    if(events.keyboard.keycode == ALLEGRO_KEY_P){
                        Pauserun=1;
                        bitmap=al_load_bitmap("./pause_1.jpg");
                        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                        al_flip_display();
                        while(Pauserun){
                            al_get_keyboard_state(&KBstate);
                            if (!al_is_event_queue_empty(event_queue)) {
                            while (al_get_next_event(event_queue, &events)) {
                            switch (events.type) {
                            case ALLEGRO_EVENT_KEY_DOWN:
                            if (events.keyboard.keycode==ALLEGRO_KEY_UP){
                                Pause-=1;
                                if(Pause<1) Pause=2;
                            }
                            else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN){
                                Pause+=1;
                                if(Pause>2) Pause=1;
                            }
                            printf("%d",Pause);
                            if(Pause==1) bitmap=al_load_bitmap("./pause_1.jpg");
                            else if(Pause==2) bitmap=al_load_bitmap("./pause_2.jpg");
                            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                            al_flip_display();

                            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                                Pauserun=0;
                            }
                            break;
                            }
                            }
                            }
                        }
                    }
                    if(run2) run2 = movecharacter(events,map,bomb,boss,a,b,wave); /* move the character */
                    break;
                }
            }
        }
        if(Pause==2){run2=0,run3=0;}
        if(run2)
        {
            run2 = explosion(events,map,bomb,boss,a,b,2);
            run3 = run2;
        }
        for(i=1;i<ROW-1;i++){
            for(j=0;j<COL;j++){
                if(map[i][j].movetrap==1){
                    if(*snakewave==1){
                        bitmap = al_load_bitmap("./snake1.jpg");
                    }else{
                        bitmap = al_load_bitmap("./snake2.jpg");
                    }
                    location=j;
                }
                else if (map[i][j].item == 2){
                    bitmap = al_load_bitmap("./gate.jpg");
                }

                else if (map[i][j].character!=0){
                    if(map[i][j].character==1){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./left 2.jpg");
                        }else {
                            bitmap = al_load_bitmap("./left 1.jpg");
                        }
                    }else if(map[i][j].character==2){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./right 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./right 2.jpg");
                        }
                    }else if(map[i][j].character==3){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./back 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./back 2.jpg");
                        }
                    }else if(map[i][j].character==4){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./face 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./face 2.jpg");
                        }
                    }
                    a=i;
                    b=j;
                }
                else if(map[i][j].item == 3){
                    bitmap = al_load_bitmap("./spider.jpg");
                }
                else{
                    if(map[i][j].basic==1){
                        bitmap = al_load_bitmap("./wall.jpg");
                    }
                    else if(map[i][j].basic==2){
                        bitmap = al_load_bitmap("./path.jpg");
                    }
                    else if(map[i][j].basic==3){
                        bitmap = al_load_bitmap("./rock.jpg");
                    }
                    else if(map[i][j].basic==4){
                        bitmap = al_load_bitmap("./bomb.jpg");
                    }
                    else if(map[i][j].basic==5){
                        bitmap = al_load_bitmap("./explosion1 center.png");
                    }
                    else if(map[i][j].basic==6){
                        bitmap = al_load_bitmap("./explosion2 col.png");
                    }
                    else if(map[i][j].basic==7){
                        bitmap = al_load_bitmap("./explosion2 row.jpg");
                    }
                    else if(map[i][j].basic==8){
                        bitmap = al_load_bitmap("./explosion3 top.png");
                    }
                    else if(map[i][j].basic==9){
                        bitmap = al_load_bitmap("./explosion3 down.png");
                    }
                    else if(map[i][j].basic==10){
                        bitmap = al_load_bitmap("./explosion3 left.png");
                    }
                    else if(map[i][j].basic==11){
                        bitmap = al_load_bitmap("./explosion3 right.jpg");
                    }
                    else if(map[i][j].basic==12){
                        bitmap = al_load_bitmap("./botten.jpg");
                    }
                    else if(map[i][j].basic==13){
                        bitmap = al_load_bitmap("./ability_up.jpg");
                    }
                }
                al_register_event_source(alEventQueue, al_get_keyboard_event_source());

                al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),j*60, -60+i*60,60, 60,0);

                al_destroy_bitmap(bitmap);
            }
        }
        if(run2){
            run2=move_trapx(map,location,1,10,trapjudge,snakewave,a,b);
            run3 = run2;
        }
        if(run2){
            run2=fixed_trap(map,a,b);
            run3 = run2;
        }

        al_rest(0.000000001);
        al_flip_display();
    }
    return run3;
}
int round3(int run2,int run3,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue,int *snakewave,int *trapjudge,int *bossbombwave,int pass){
    int speed = 1,i,j;
    while (run3==1)
    {
        al_get_keyboard_state(&KBstate);
        if (!al_is_event_queue_empty(event_queue)) {
            while (al_get_next_event(event_queue, &events)) {
                switch (events.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                   run3 = 0;
                   break;
                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode == ALLEGRO_KEY_F12){ boss->life = 0;}
                    if(events.keyboard.keycode == ALLEGRO_KEY_P){
                        Pauserun=1;
                        bitmap=al_load_bitmap("./pause_1.jpg");
                        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                        al_flip_display();
                        while(Pauserun){
                            al_get_keyboard_state(&KBstate);
                            if (!al_is_event_queue_empty(event_queue)) {
                            while (al_get_next_event(event_queue, &events)) {
                            switch (events.type) {
                            case ALLEGRO_EVENT_KEY_DOWN:
                            if (events.keyboard.keycode==ALLEGRO_KEY_UP){
                                Pause-=1;
                                if(Pause<1) Pause=2;
                            }
                            else if (events.keyboard.keycode==ALLEGRO_KEY_DOWN){
                                Pause+=1;
                                if(Pause>2) Pause=1;
                            }
                            printf("%d",Pause);
                            if(Pause==1) bitmap=al_load_bitmap("./pause_1.jpg");
                            else if(Pause==2) bitmap=al_load_bitmap("./pause_2.jpg");
                            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
                            al_flip_display();

                            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                                Pauserun=0;
                            }
                            break;
                            }
                            }
                            }
                        }
                    }
                    if(run3) run3 = movecharacter(events,map,bomb,boss,a,b,wave);
                    break;
                }
            }
        }
        if(speed%3 == 0){
            moveboss(boss,bossbombwave);
            speed = 1;
        }if(run3){
        run3=judgedie(map,bomb,boss,a,b);
        }
        if(Pause==2){run3=0;}
        if(run3)
        {
            run3 = explosion(events,map,bomb,boss,a,b,3);
        }
        for(i=1;i<ROW-1;i++){
            for(j=0;j<COL;j++){
                if((i == boss->X || i == boss->X + 1) && (j == boss->Y || j == boss->Y + 1)){
                    if(i==boss->X&&j==boss->Y)bitmap = al_load_bitmap("./boss1.png");
                    if(i==boss->X&&j==boss->Y+1)bitmap = al_load_bitmap("./boss2.png");
                    if(i==boss->X+1&&j==boss->Y)bitmap = al_load_bitmap("./boss3.png");
                    if(i==boss->X+1&&j==boss->Y+1)bitmap = al_load_bitmap("./boss4.png");
                }

                else if ((i == boss->bombX || i == boss->bombX + 1) && (j == boss->bombY || j == boss->bombY + 1)){
                    if(i==boss->bombX&&j==boss->bombY&&*bossbombwave==1)bitmap = al_load_bitmap("./boss_bomb 1-1.png");
                    else if(i==boss->bombX&&j==boss->bombY&&*bossbombwave==(-1))bitmap = al_load_bitmap("./boss_bomb 2-1.png");

                    if(i==boss->bombX&&j==boss->bombY+1&&*bossbombwave==1)bitmap = al_load_bitmap("./boss_bomb 1-2.png");
                    else if(i==boss->bombX&&j==boss->bombY+1&&*bossbombwave==(-1))bitmap = al_load_bitmap("./boss_bomb 2-2.png");

                    if(i==boss->bombX+1&&j==boss->bombY&&*bossbombwave==1)bitmap = al_load_bitmap("./boss_bomb 1-3.png");
                    else if(i==boss->bombX+1&&j==boss->bombY&&*bossbombwave==(-1))bitmap = al_load_bitmap("./boss_bomb 2-3.png");

                    if(i==boss->bombX+1&&j==boss->bombY+1&&*bossbombwave==1)bitmap = al_load_bitmap("./boss_bomb 1-4.png");
                    else if(i==boss->bombX+1&&j==boss->bombY+1&&*bossbombwave==(-1))bitmap = al_load_bitmap("./boss_bomb 2-4.png");
                }

                else if (map[i][j].item == 2){
                    bitmap = al_load_bitmap("./gate.jpg");
                }
                else if (map[i][j].character!=0){
                    if(map[i][j].character==1){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./left 2.jpg");
                        }else {
                            bitmap = al_load_bitmap("./left 1.jpg");
                        }
                    }
                    else if(map[i][j].character==2){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./right 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./right 2.jpg");
                        }
                    }else if(map[i][j].character==3){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./back 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./back 2.jpg");
                        }
                    }else if(map[i][j].character==4){
                        if(*wave==1){
                            bitmap = al_load_bitmap("./face 1.jpg");
                        }else {
                            bitmap = al_load_bitmap("./face 2.jpg");
                        }
                    }
                    a=i;
                    b=j;
                }
                else{
                    if(map[i][j].basic==1){
                        bitmap = al_load_bitmap("./wall.jpg");
                    }
                    else if(map[i][j].basic==2){
                        bitmap = al_load_bitmap("./path.jpg");
                    }
                    else if(map[i][j].basic==3){
                        bitmap = al_load_bitmap("./rock.jpg");
                    }
                    else if(map[i][j].basic==4){
                        bitmap = al_load_bitmap("./bomb.jpg");
                    }
                    else if(map[i][j].basic==5){
                        bitmap = al_load_bitmap("./explosion1 center.png");
                    }
                    else if(map[i][j].basic==6){
                        bitmap = al_load_bitmap("./explosion2 col.png");
                    }
                    else if(map[i][j].basic==7){
                        bitmap = al_load_bitmap("./explosion2 row.jpg");
                    }
                    else if(map[i][j].basic==8){
                        bitmap = al_load_bitmap("./explosion3 top.png");
                    }
                    else if(map[i][j].basic==9){
                        bitmap = al_load_bitmap("./explosion3 down.png");
                    }
                    else if(map[i][j].basic==10){
                        bitmap = al_load_bitmap("./explosion3 left.png");
                    }
                    else if(map[i][j].basic==11){
                        bitmap = al_load_bitmap("./explosion3 right.jpg");
                    }
                    else if(map[i][j].basic==12){
                        bitmap = al_load_bitmap("./botten.jpg");
                    }
                    else if(map[i][j].basic==13){
                        bitmap = al_load_bitmap("./ability_up.jpg");
                    }
                }
                al_register_event_source(alEventQueue, al_get_keyboard_event_source());

                al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),j*60, -60+i*60,60, 60,0);

                al_destroy_bitmap(bitmap);
            }
        }
        if(boss->life <= 0) {run3 = 0;pass=1;}
        speed++;
        al_rest(0.000000001);
        al_flip_display();
    }

    return pass;
}
void inputname(ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_FONT *name){

    char word;
    char str[20];
    int run=1,i=-1;
    int judge=0;
    int lseqence=0;

    while(run){
            al_get_keyboard_state(&KBstate);
            if (!al_is_event_queue_empty(event_queue)) {
                while (al_get_next_event(event_queue, &events)) {
                    switch (events.keyboard.keycode) {
                    case 157:
                        judge=1;
                        lseqence++;
                        i=i+1;
                        al_rest(0.1);



                        break;
                    }
                }

            }
            if (events.keyboard.keycode==ALLEGRO_KEY_ENTER){
                            run=0;
                            judge=0;
                        }
            if(judge==1){
                i=i-1;
                word=events.keyboard.keycode+64;
                str[i]=word;
                al_draw_textf( name, al_map_rgb(0, 0, 0), 250+(15*lseqence), 100, -1, "%c",word);
                al_flip_display();


                judge=0;

            }

    }

    FILE *fptr;
    int j;


    fptr=fopen("user.txt","w");


            fprintf(fptr,"%s\t",str);

    fclose(fptr);

}
//void round3()
