#include "myheader.h"

int main()
{
    struct bomb *bomb ;
    bomb = create_matrix1(5);
    init1(bomb);

    mapstruct **map=NULL;
    map=create_matrix2(ROW,COL);
    readfile_array(map,ROW,COL,1);
    int i,j,a,b;

    struct boss *boss;
    boss = create_matrix1(1);
    boss->X=7;
    boss->Y=7;
    boss->bombX=-2;
    boss->bombY=-2;
    boss->life=5;
    srand(time(NULL));

    int *wave;
    wave = malloc(sizeof(int ));
    *wave=1;

    struct user *userfile;
    userfile=create_matrix1(6);

    ALLEGRO_EVENT alEvent;
    ALLEGRO_EVENT events;
    ALLEGRO_EVENT_QUEUE* alEventQueue = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL; /* create event queue */
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_BITMAP* bitmap = NULL;
    ALLEGRO_KEYBOARD_STATE KBstate;
    ALLEGRO_FONT *pongFont = NULL; /* pointer to Font file */
    ALLEGRO_FONT *gameover = NULL;
    ALLEGRO_FONT *name = NULL;
    ALLEGRO_FONT *score = NULL;

    // Initialize Allegro
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();  // install font addons
    al_init_ttf_addon();

    ALLEGRO_SAMPLE *background = NULL;

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(9);

    background = al_load_sample("background.wav");

    // Create allegro display
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    // Create Event Queue
    alEventQueue = al_create_event_queue();
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());    /* register keyboard to event queue */
    al_register_event_source(event_queue, al_get_display_event_source(display));
    gameover = al_load_ttf_font("ARCHRISTY.ttf", 60, 0);
    name = al_load_ttf_font("ARCHRISTY.ttf", 60, 0);
    score = al_load_ttf_font("ARCHRISTY.ttf", 60, 0);



    map[2][1].character=1;
    a=1;
    b=1;
    int ex;
    int run=0;
    int run2=0;
    int run3=0;

    time_t t1,t2;
    int timelv1,timelv2,timelv3;

    bitmap=al_load_bitmap("./book1.png");
    al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
    al_flip_display();
    while (ex){
        al_get_keyboard_state(&KBstate);
        if (!al_is_event_queue_empty(event_queue)) {
            while (al_get_next_event(event_queue, &events)) {
                switch (events.type) {
                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode == ALLEGRO_KEY_ENTER) ex=0;
    }
            }
        }
    }
    ex=1;
    bitmap=al_load_bitmap("./explain.jpg");
    al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
    al_flip_display();
    while (ex){
        al_get_keyboard_state(&KBstate);
        if (!al_is_event_queue_empty(event_queue)) {
            while (al_get_next_event(event_queue, &events)) {
                switch (events.type) {
                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode == ALLEGRO_KEY_ENTER) ex=0;
    }
            }
        }
    }

    bitmap=al_load_bitmap("./start.png");
    al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
    al_flip_display();

    int *menu;
    menu = malloc(sizeof(int ));
    *menu=1;
    int List=1;
    int Level=1;
    int *Listrun;
    int *Levelrun;
    Listrun = malloc(sizeof(int ));
    Levelrun = malloc(sizeof(int ));
    int Pause=1;
    int *Pauserun;
    *Listrun=1;
    *Levelrun=1;
    int *trapjudge;
    trapjudge = malloc(sizeof(int ));
    *trapjudge = 1;
    int *snakewave;
    snakewave = malloc(sizeof(int ));
    *snakewave=1;
    int *bossbombwave;
    bossbombwave=malloc(sizeof(int ));
    *bossbombwave=1;
    int pass=0;

    al_play_sample(background, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

    while(*menu==1){
            List=List_choose( KBstate,events,event_queue,bitmap,List,Listrun,menu);
    if(List==1) {*menu=0;run=1;}
    if(List==2) {
        *Levelrun=1;
        Level=1;
        bitmap=al_load_bitmap("./selectlv1.png");
        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
        al_flip_display();

        Level=Level_choose(KBstate,events,event_queue,bitmap,Level,Levelrun,menu);

        if(Level==1) {run=1;*menu=0;}
        else if(Level==2) {run2=1;*menu=0;}
        else if(Level==3) {run3=1;*menu=0;}
        else if(Level==4) {
            *Listrun=1;
            List=1;
            bitmap=al_load_bitmap("./start.png");
            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
            al_flip_display();
        }
    }
    if(List==3) {
        userfile[5].score=999;
        leaderborad(userfile);
        bitmap=al_load_bitmap("./leaderboard1.png");
        while(1){
            al_get_keyboard_state(&KBstate);
            if (al_key_down(&KBstate, ALLEGRO_KEY_SPACE)) break;
            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0, 0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);


            al_draw_textf( score, al_map_rgb(255, 255, 255), 500, 260, -1, "%s%d",userfile[0].name,userfile[0].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 350, 390, -1, "%s%d",userfile[1].name,userfile[1].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 650, 390, -1, "%s%d",userfile[2].name,userfile[2].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 380, 500, -1, "%s%d",userfile[3].name,userfile[3].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 620, 500, -1, "%s%d",userfile[4].name,userfile[4].score);
            al_draw_textf( gameover, al_map_rgb(255, 255, 255), 500, 580, -1, "Press SPACE");
            al_flip_display();
            }
            *Listrun=1;
            List=1;
            bitmap=al_load_bitmap("./start.png");
            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
            al_flip_display();
        }

    if(List==4) {*Listrun = 0; *menu = 0;run = 0; run2 = 0; run3=0;}
    }

    t1 = time(NULL);
 /***********************************************************************************/
    run2 = round1(run,run2,KBstate,events,event_queue,bitmap,Pauserun,Pause,map,boss,bomb,a,b,wave,alEventQueue);

    t2 = time(NULL);
    timelv1=t2-t1;

    if(List==2 && Level==1) run2=0;

    al_clear_to_color(al_map_rgb(255,0,0));

    if(run2==1){
        bitmap=al_load_bitmap("./level2.png");
        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
        al_flip_display();
        al_rest(0.5);
    }

    /**********************LEVEL 2*************************/
    map=create_matrix2(ROW,COL);
    readfile_array(map,ROW,COL,2);

    map[2][1].character=1;
    int location=3;
    map[10][location].movetrap=1;
    a=1;
    b=1;

    t1 = time(NULL);
    run3 = round2(run2,run3,KBstate,events,event_queue,bitmap,Pauserun,Pause,map,boss,bomb,a,b,wave,alEventQueue,snakewave,trapjudge);

    t2 = time(NULL);
    timelv2=t2-t1;

    if(List==2 && Level==2) run3=0;

    /******************************************************/
    al_clear_to_color(al_map_rgb(255,0,0));

    if(run3==1){
        bitmap=al_load_bitmap("./level3.png");
        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
        al_flip_display();
        al_rest(0.5);
    }
    al_destroy_display(display);
    /***********************LEVEL 3************************/
    map=create_matrix2(ROW,COL);
    readfile_array(map,ROW,COL,3);
    display = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);

    map[2][1].character=1;
    a=1;
    b=1;

    bomb[0].power = 4;

    t1 = time(NULL);
    pass = round3(run2,run3,KBstate,events,event_queue,bitmap,Pauserun,Pause,map,boss,bomb,a,b,wave,alEventQueue,snakewave,
                  trapjudge,bossbombwave,pass);

    t2 = time(NULL);
    timelv3=t2-t1;
    al_destroy_display(display);
 display = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);
    if(pass==1 && List!=2){
        bitmap=al_load_bitmap("./win.png");
        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
        al_flip_display();
        al_rest(0.5);
        inputname(KBstate,events,event_queue,name);
        userfile[5].score=timelv1+timelv2+timelv3;

        leaderborad(userfile);

        bitmap=al_load_bitmap("./leaderboard1.png");
        while(1){
            al_get_keyboard_state(&KBstate);
            if (al_key_down(&KBstate, ALLEGRO_KEY_SPACE)) break;
            al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0, 0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);


            al_draw_textf( score, al_map_rgb(255, 255, 255), 500, 260, -1, "%s%d",userfile[0].name,userfile[0].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 350, 390, -1, "%s%d",userfile[1].name,userfile[1].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 650, 390, -1, "%s%d",userfile[2].name,userfile[2].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 380, 500, -1, "%s%d",userfile[3].name,userfile[3].score);
            al_draw_textf( score, al_map_rgb(255, 255, 255), 620, 500, -1, "%s%d",userfile[4].name,userfile[4].score);
            al_draw_textf( gameover, al_map_rgb(255, 255, 255), 500, 580, -1, "Press SPACE");
            al_flip_display();
            }

        }
    if(List!=4){
        bitmap=al_load_bitmap("./game_over.png");
        al_draw_scaled_bitmap(bitmap, 0, 0,al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
        /*al_clear_to_color(al_map_rgb(255,0,0));
        al_draw_textf( gameover, al_map_rgb(255, 255, 255), 320, 200, -1, "Game Over!");*/
        al_flip_display();
        al_rest(0.5);
    }

    //al_destroy_bitmap(bitmap);
    al_destroy_display(display);
    free(bomb);
    free(map);
    free(wave);

    return 0;
}

