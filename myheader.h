#ifndef MYHEADER_H_INCLUDED
#define MYHEADER_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define DISPLAY_WIDTH   780
#define DISPLAY_HEIGHT 660
#define ROW 13
#define COL 13

typedef struct MY{
    int basic;
    int item;
    int character;
    int movetrap;
} mapstruct;
typedef struct bomb{
    int judge;
    int x;
    int y;
    int delay;
    int power;
    int count;
}bomb;
typedef struct boss{
    int X;
    int Y;
    int bombX;
    int bombY;
    int direction;
    int life;
}boss;
typedef struct user{
    char name[20];
    int score;
}user;

void allegrodraw(int**mat,int x ,int y,int row,int col);
mapstruct **create_matrix2(int row, int col);
struct bomb *create_matrix1(int row);
void readfile_array(mapstruct **mat,int row,int col,int n);
int movecharacter( ALLEGRO_EVENT events,mapstruct **map,struct bomb *bomb,struct boss *boss,int i,int j,int *wave);
void init1(struct bomb *bomb);
int explosion( ALLEGRO_EVENT events,mapstruct **map,struct bomb *bomb,struct boss *boss,int i,int j,int level);
void initial1(struct bomb *bomb,int count,int i,int j);
void moveboss(struct boss *boss,int *bossbombwave);
int List_choose( ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap,int List,int *Listrun,int *menu);
int Level_choose( ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap,int Level,int *Levelrun,int *menu);
int Pause_choose( ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap,int Pause,int *Pauserun);
int move_trapx(mapstruct **map,int location,int traps,int trape,int *trapjudge,int *snakewave,int charcaterx,int charcatery);
int fixed_trap(mapstruct **map,int charcaterx,int charcatery);
void inputname(ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_FONT *name);
int judgedie(mapstruct **map ,struct bomb *bomb,struct boss *boss,int i,int j);
int round1(int run,int run2,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue);
int round2(int run2,int run3,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue,int *snakewave,int *trapjudge);
int round3(int run2,int run3,ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_BITMAP* bitmap
           ,int *Pauserun,int Pause,mapstruct** map,struct boss *boss ,struct bomb *bomb,int a,int b,int *wave,
           ALLEGRO_EVENT_QUEUE* alEventQueue,int *snakewave,int *trapjudge,int *bossbombwave,int pass);
void inputname(ALLEGRO_KEYBOARD_STATE KBstate,ALLEGRO_EVENT events,ALLEGRO_EVENT_QUEUE* event_queue,ALLEGRO_FONT *name);
void leaderborad(struct user *userfile);

#endif // MYHEADER_H_INCLUDED
