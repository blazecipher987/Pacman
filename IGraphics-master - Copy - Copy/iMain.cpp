# include "iGraphics.h"
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>

clock_t start = clock(), diff;

//diff = clock() - start;

int msec = diff * 1000 / CLOCKS_PER_SEC;

//Screen
double Screen_H=600,Screen_W=1200;

//maze size
int maze_x=400,maze_y=100;

//maze layout
int total_cell=342;
int wall_h=20,wall_w=20;
int maze_row=18,maze_col=19;
int death_index=0;
int x=0;
double pacman_h=15;
double pacman_w=15;
//int fright_frame=0;
int target_cell=161;
int time_passed=0;
int time_passed2=0;
int g=0;
int p=0;
char str[50]="Enter your name and click done";
int index=0;
int data_numbers=11;

struct Fame{

char name[50];
int score;

}data[11];

struct Cell{

double x;
double y;
int type;

}cells[342];

struct Player{

int player_x;
int player_y;
int player_direction; // 0->uo, 1->right, 2->down, 3->up
int player_cell;
int frame;
int score;
int player_col;
int player_row;
int lives;
int collide=0;
int collide_x;
int collide_y;
int berry;
int pear;
int straw;
int chomp_sound;
int power;
int invisible;
int potion_red;
int invisible_count =1;
int invisible_time;
int stop_count;
int stop_timerl;
int stop_state;

}pacman;

char pac[3][10][20]= {{"pac_1_b.bmp"},{"pac_right1.bmp","pac_right2.bmp","pac_left1.bmp","pac_left2.bmp","pac_up1.bmp","pac_up2.bmp","pac_down1.bmp","pac_down2.bmp"}};
char wall[20][20]= {"wall_1.bmp","wall_2.bmp","wall_3.bmp","wall_4.bmp","wall_5.bmp","wall_6.bmp"};
char red_enemy[10][20]= {"red_up_1.bmp","red_up_2.bmp","red_down_1.bmp","red_down_2.bmp","red_left_1.bmp","red_left_2.bmp","red_right_1.bmp","red_right_2.bmp"};
char lime_enemy[10][20]= {"lime_up_1.bmp","lime_up_2.bmp","lime_down_1.bmp","lime_down_2.bmp","lime_left_1.bmp","lime_left_2.bmp","lime_right_1.bmp","lime_right_2.bmp"};
char pink_enemy[10][20]= {"pink_up_1.bmp","pink_up_2.bmp","pink_down_1.bmp","pink_down_2.bmp","pink_right_1.bmp","pink_right_2.bmp","pink_left_1.bmp","pink_left_2.bmp"};
char fire[20][20]={"f_u_1.bmp","f_u_2.bmp","f_d_1.bmp","f_d_2.bmp","f_l_1.bmp","f_l_2.bmp","f_r_1.bmp","f_r_2.bmp"};
char orange_enemy[10][20]= {"orange_up_1.bmp","orange_up_2.bmp","orange_down_1.bmp","orange_down_2.bmp","orange_right_1.bmp","orange_right_2.bmp","orange_left_1.bmp","orange_left_2.bmp"};
char fright_enemy[10][20]={"fright_1.bmp","fright_2.bmp","fright_3.bmp","fright_4.bmp"};
char background[10][20]= {"start_bg.bmp","bg_help_menu.bmp","bg_high_score.bmp","bg_customize.bmp","pacman.bmp","load_screen.bmp","bg_enter_name.bmp","bg_enter_name_1.bmp","wall_texture.bmp"}; //7
char bg_anim[10][20]= {"1pac_1.bmp","1pac_2.bmp","1pac_1.bmp","1pac_2.bmp","1pac_1.bmp","1pac_2.bmp","1pac_3.bmp"};
char UI[28][30]= {"play_button.bmp","help.bmp","help_button.bmp","load_button.bmp","high_score.bmp","back_button.bmp","custom.bmp","tick_mark.bmp","sound_gui.bmp","cross_gui.bmp","play.bmp","stop.bmp","play_text.bmp","pause_text.bmp","alert_1.bmp","alert_2.bmp","alert_3.bmp","difficulty_main.bmp","current_score_text.bmp","lives_text.bmp","save_text.bmp","edit_maze_text.bmp","maze_edit_icon.bmp"}; //22
char UI2[20][30]={"done_text.bmp","exit_button.bmp","clock.bmp","game_over_1.bmp","game_over_2.bmp","enter_name.bmp","game_over_3.bmp","game_over_4.bmp","texture.bmp"};
char scores[20][20]={"0.bmp","1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp"};
char death[20][20]={"death_1.bmp","death_2.bmp","death_3.bmp","death_4.bmp","death_5.bmp","death_6.bmp","death_7.bmp","death_8.bmp","death_9.bmp"};
char perks[20][20]={"potion_yellow.bmp","potion_red.bmp","potion_lime.bmp","potion_purple.bmp","cherry.bmp","power_pelate.bmp"};
char life[10][20]={"heart.bmp","eye_r.bmp","eye_l.bmp","eye_u.bmp","eye_d.bmp"};
char advanced[20][20]={"door.bmp","key.bmp","edit_maze_1.bmp","edit_maze_2.bmp"};
char numbers[20][20]={"num_100.bmp","num_300.bmp","num_500.bmp","num_700.bmp","num_1000.bmp"};
char animate[20][20]={"bg_anim_1.bmp","bg_anim_2.bmp","bg_anim_3.bmp","bg_anim_4.bmp","bg_anim_5.bmp","bg_anim_6.bmp","bg_anim_7.bmp"};
char foods[20][20]={"cherry.bmp","apple.bmp","straw.bmp"};

int maze[18][19]=
   {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,5,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,5,1},
    {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,1,0,1,0,1,1,0,0,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
    {2,2,2,6,0,0,0,0,0,9,0,0,0,0,0,6,2,2,2},
    {1,1,1,1,0,1,0,1,1,2,1,1,0,1,0,1,1,1,1},
    {1,0,0,0,0,1,0,1,2,2,2,1,0,1,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,0,1},
    {1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1},
    {1,5,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,5,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//ghost
struct Enemy{
int ghost_x;
int ghost_y;
double ghost_h;
double ghost_w;
int ghost_row;
int ghost_col;
int speed;
int ghost_direction;// 0->up, 1->right, 2->down, 3->left
int temp;
int ghost_cell;
int timer;
int frame;
int fright_frame;
int eaten_frame;
int retreat;
int fright;
int scoring;
}pinky,inky,clyde,blinky;

struct User
{
    int bg_music_state;
    int credits;
    int play;
    int load;
    int pause;
    int help_menu;
    int state;
    int game_sound;
    int difficulty;
    int wall_img_index;
    int player_img_index;
    int tick_mark_1;
    int tick_mark_2;
    int save;
    int maze_edit;
    int process;
    int backup;
    int clock_time;
    int popup_timer;
    int popup_timer_count;
    int popup_x;
    int popup_y;
    int short_off;
    int short_image;
    int short_off_timer;
    int dots;
    int anime_index;
    int collide_count;


    //int
} user_interface;

//Prototype Declare
void define_maze();
void pinky_move();
void inky_move();
void blinky_move();
void clyde_move();
void player_move();
void ghost_animation();
void score_display();
void pinky_short_move();
void inky_short_move();
void blinky_short_move();
void clyde_short_move();
void pinky_fright_mode();
void inky_fright_mode();
void blinky_fright_mode();
void clyde_fright_mode();

int determine_smallest(int a, int b, int c);
void collision();
void death_animation();
void gs();
void player_lives();

void time_pass();
void maze_edit();
void high_scores_save();
void high_scores_load();
void initialize();
void invisible_time();
void all_times();
void show_time();
void timer();

void iDraw()
{



    //place your drawing codes here
    iClear();

    printf("%d\n",user_interface.dots);
    if(user_interface.state==9)
    {
        iShowBMP(0,0,animate[user_interface.anime_index]);
    }


    if(user_interface.state==0)
    {


         iShowBMP(0,0,background[0]);
         iShowBMP2(850,500,background[4],0xFFFFFF);
        iShowBMP2(900,400,UI[0],0);
        iShowBMP2(900,290,UI[3],0);
        iShowBMP2(910,190,UI[4],0xFFFFFF);
        iShowBMP2(910,90,UI[6],0xFFFFFF);
        //iShowBMP2(10,500,UI[1],0xFFFFFF);
        iShowBMP2(10,520,UI[2],0xFFFFFF);
        iShowBMP2(10,420,UI[8],0xFFFFFF);

        //exit button
        iShowBMP2(10,10,UI2[1],0xFFFFFF);

        if(user_interface.bg_music_state==0)
            iShowBMP2(10,420,UI[9],0xFFFFFF);

        iShowBMP2(100,500,"credits_img.bmp",0);
        iShowBMP(820,500,"pax.bmp");



//        iShowBMP2(bgpac_x,bgpac_y,bg_anim[bgpac_index/20],0);
//
//        if(user_interface.help_menu==1)
//            iShowBMP(0,0,background[1]);
//
//
//
//        if(sound_state==0)
//            iShowBMP2(20,50,UI[9],0);

    }

    if(user_interface.state==15)
    {
        iShowBMP(0,0,"credits.bmp");
        iShowBMP2(10,30,UI[5],0xFFFFFF);
    }

    if(user_interface.state==10)
    {
        iShowBMP(0,0,"help_3.bmp");
        iShowBMP2(10,30,UI[5],0xFFFFFF);
        iShowBMP2(1100,30,"b_b_2.bmp",0xFFFFFF);
    }

    if(user_interface.state==11)
    {
        iShowBMP(0,0,"help_1.bmp");
        iShowBMP2(10,30,UI[5],0xFFFFFF);
        iShowBMP2(1100,130,"b_b_2.bmp",0xFFFFFF);
    }

    if(user_interface.state==12)
    {
        iShowBMP(0,0,"help_2.bmp");
        iShowBMP2(10,30,UI[5],0xFFFFFF);
        iShowBMP2(1100,230,"b_b_2.bmp",0xFFFFFF);
    }

     if(user_interface.state==13)
    {
        iShowBMP(0,0,"help_4.bmp");
        iShowBMP2(10,130,UI[5],0xFFFFFF);

    }

    //help
//    if(user_interface.state==5)
//        {
//            iShowBMP(0,0,background[1]);
//            iShowBMP2(10,30,UI[5],0xFFFFFF);
//        }

    //HAll OF FAME
    if(user_interface.state==3)
    {
        iShowBMP(0,0,background[2]);
        iShowBMP2(10,30,UI[5],0xFFFFFF);
        iShowBMP2(400,380,"high_score_img.bmp",0xFFFFFF);

        for(int h=0;h<5;h++)
        {
            char x[50],p[10];
            int t[5]={1,2,3,4,5};
            itoa(data[h].score,x,10);
            itoa(t[h],p,10);
            iSetColor(255,255,255);
            iText(10,500-(50*h),p,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(20,500-(50*h),".",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(40,500-(50*h),data[h].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(290,500-(50*h),x,GLUT_BITMAP_TIMES_ROMAN_24);
        }

        for(int h=5;h<10;h++)
        {
            char x[50],p[10];
            int t[10]={1,2,3,4,5,6,7,8,9,10};
            itoa(data[h].score,x,10);
            itoa(t[h],p,10);

            iSetColor(255,255,255);
            iText(850,500-(50*(-5+h)),p,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(860,500-(50*(-5+h)),".",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(880,500-(50*(-5+h)),data[h].name,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1130,500-(50*(-5+h)),x,GLUT_BITMAP_TIMES_ROMAN_24);

        }
    }

    if(user_interface.state==6)
        {
            maze_edit();
            iShowBMP2(30,500,advanced[2],0xFFFFFF);
            iShowBMP2(600,500,advanced[3],0xFFFFFF);
            iShowBMP2(30,30,"done_text.bmp",0xFFFFFF);
        }

//ENTER NAME FOR HIGHSCORE SELECTION SCREEN
    if(user_interface.state==7)
    {
        iShowBMP(0,0,background[7]); //280,200
        iShowBMP2(420,400,UI2[3],0xFFFFFF);
        iShowBMP2(300,230,UI2[5],0xFFFFFF);


        iSetColor(0,233,230);
        iFilledRectangle(400,300,400,80);
        //show name while entering

        iSetColor(0,0,0);
        iText(420,350,str,GLUT_BITMAP_HELVETICA_18);
        iShowBMP2(1000,10,UI2[0],0xFFFFFF);
    }

    if(user_interface.state==8)
    {
        iShowBMP(400,0,UI2[7]);
        iShowBMP2(350,500,UI2[4],0xFFFFFF);
        iShowBMP2(250,410,UI2[6],0xFFFFFF);
        iShowBMP2(1000,10,UI2[0],0xFFFFFF);

        iShowBMP(400,300,UI2[8]);
        iSetColor(255,255,255);
        iText(420,350,str,GLUT_BITMAP_HELVETICA_18);

    }


    if(user_interface.state==2)
    {

        if(user_interface.load==0)
            iShowBMP(0,0,background[5]);

        iShowBMP2(10,30,UI[5],0xFFFFFF);
    }

    //customize
    if(user_interface.state==4)
    {
        iShowBMP(0,0,background[3]);
        iShowBMP2(10,30,UI[5],0xFFFFFF);

        iShowBMP2(10,480,background[8],0xFFFFFF);
        iShowBMP(600,510,wall[0]);
        iShowBMP(670,510,wall[1]);
        iShowBMP(740,510,wall[2]);
        iShowBMP(810,510,wall[3]);
        iShowBMP(880,510,wall[4]);
        iShowBMP(950,510,wall[5]);
        iShowBMP2(580+user_interface.tick_mark_1,480,UI[7],0xFFFFFF);


        iShowBMP2(10,350,UI[17],0xFFFFFF);
        iShowBMP2(600,390,UI[16],0xFFFFFF);
        iShowBMP2(800,390,UI[15],0xFFFFFF);
        iShowBMP2(1000,390,UI[14],0xFFFFFF);
        iShowBMP2(600+user_interface.tick_mark_2,390,UI[7],0xFFFFFF);

        iShowBMP2(10,200,UI[21],0xFFFFFF);
        iShowBMP2(320,200,UI[22],0xFFFFFF);

    }

    //play
    if(user_interface.state==1 || user_interface.state==6)
    {
        iShowBMP2(cells[180].x,cells[180].y,"ghost_door.bmp",0xFFFFFF);

        iPoint(350+maze_x,180+maze_y,3);

        if(user_interface.popup_timer!=0)
                {
                    iShowBMP2(pacman.player_x+maze_x-10,pacman.player_y+maze_y-10,numbers[0],0);
                }


        for(int i=0; i<total_cell; i++)
        {
            //BLIT WALLS
            if(cells[i].type==1)
            {
                iShowBMP(cells[i].x,cells[i].y,wall[user_interface.wall_img_index]);

            }


            //BLIT DOORS
            if(cells[i].type==6)
            {
                iShowBMP2(cells[i].x,cells[i].y,"door.bmp",0xFFFFFF);
            }

            //BLIT BERRIES
            if(cells[i].type==4)
            {
                iShowBMP2(cells[i].x,cells[i].y,perks[4],0xFFFFFF);
            }

            //BLIT PELATES
            if(cells[i].type==5)
            {
                iShowBMP2(cells[i].x,cells[i].y,"power_pelate.bmp",0xFFFFFF);
            }

            if(cells[i].type==20)
            {
                iShowBMP2(cells[i].x,cells[i].y,foods[1],0);
            }

            if(cells[i].type==21)
            {
                iShowBMP2(cells[i].x,cells[i].y,foods[2],0);
            }

            //HEALTH POTION
            if(cells[i].type==7)
            {

                iShowBMP2(cells[i].x,cells[i].y,perks[1],0xFFFFFF);
//                iSetColor(231,35,13);
//                iPoint(cells[i].x,cells[i].y,3);
            }


            //invisibility potion
             if(cells[i].type==10)
            {

                iShowBMP2(cells[i].x,cells[i].y,perks[0],0xFFFFFF);
//                iSetColor(231,35,13);
//                iPoint(cells[i].x,cells[i].y,3);
            }

            if(cells[i].type==11)
            {

                iShowBMP2(cells[i].x,cells[i].y,"stopper.bmp",0xFFFFFF);
//                iSetColor(231,35,13);
//                iPoint(cells[i].x,cells[i].y,3);
            }

        }


        define_maze();


    //Draw Ghost


    if(pacman.power==0)
    {
        //iShowBMP2(maze_x+pinky.ghost_x+10,maze_y+pinky.ghost_y+2,fire[pinky.frame],0xFFFFFF);
        iShowBMP2(maze_x+pinky.ghost_x,maze_y+pinky.ghost_y,pink_enemy[pinky.frame],0);
        iShowBMP2(maze_x+blinky.ghost_x,maze_y+blinky.ghost_y,red_enemy[blinky.frame],0);
        iShowBMP2(maze_x+clyde.ghost_x,maze_y+clyde.ghost_y,orange_enemy[clyde.frame],0);
        iShowBMP2(maze_x+inky.ghost_x,maze_y+inky.ghost_y,lime_enemy[inky.frame],0);

        iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[1][pacman.frame],0);

        if(pacman.collide==1)
        {
            iShowBMP2(pacman.collide_x,pacman.collide_y,death[death_index],0);
        }
    }

    if(pacman.power==1)
    {


        //FOR PINKY
        if(pinky.fright==0)
        {
            iShowBMP2(maze_x+pinky.ghost_x,maze_y+pinky.ghost_y,pink_enemy[pinky.frame],0);
        }

        iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
        if(pinky.retreat==0 && pinky.fright==1)
        {
        iShowBMP2(maze_x+pinky.ghost_x,maze_y+pinky.ghost_y,fright_enemy[pinky.fright_frame],0);

        pinky.fright_frame++;
        if(pinky.fright_frame>3)
            pinky.fright_frame=0;
        }


        if(pinky.retreat==1)
        {
            //iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
            iShowBMP2(maze_x+pinky.ghost_x,maze_y+pinky.ghost_y,life[pinky.eaten_frame],0);
        }


        //FOR INKY
        if(inky.fright==0)
        {
            iShowBMP2(maze_x+inky.ghost_x,maze_y+inky.ghost_y,lime_enemy[inky.frame],0);

        }

        if(inky.retreat==0 && inky.fright==1)
        {
        iShowBMP2(maze_x+inky.ghost_x,maze_y+inky.ghost_y,fright_enemy[inky.fright_frame],0);

        inky.fright_frame++;
        if(inky.fright_frame>3)
            inky.fright_frame=0;
        }

        if(inky.retreat==1)
        {
            //iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
            iShowBMP2(maze_x+inky.ghost_x,maze_y+inky.ghost_y,life[inky.eaten_frame],0);
        }


        if(blinky.fright==0)
        {
            iShowBMP2(maze_x+blinky.ghost_x,maze_y+blinky.ghost_y,red_enemy[blinky.frame],0);
        }

        iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
        if(blinky.retreat==0 && blinky.fright==1)
        {
        iShowBMP2(maze_x+blinky.ghost_x,maze_y+blinky.ghost_y,fright_enemy[blinky.fright_frame],0);

        blinky.fright_frame++;
        if(blinky.fright_frame>3)
            blinky.fright_frame=0;
        }

        if(blinky.retreat==1)
        {
            //iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
            iShowBMP2(maze_x+blinky.ghost_x,maze_y+blinky.ghost_y,life[blinky.eaten_frame],0);
        }





        if(clyde.fright==0)
        {
            iShowBMP2(maze_x+clyde.ghost_x,maze_y+clyde.ghost_y,orange_enemy[clyde.frame],0);
        }

        iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
        if(clyde.retreat==0 && clyde.fright==1)
        {
        iShowBMP2(maze_x+clyde.ghost_x,maze_y+clyde.ghost_y,fright_enemy[clyde.fright_frame],0);

        clyde.fright_frame++;
        if(clyde.fright_frame>3)
            clyde.fright_frame=0;
        }

        if(clyde.retreat==1)
        {
            //iShowBMP2(maze_x+pacman.player_x,maze_y+pacman.player_y,pac[0][0],0);
            iShowBMP2(maze_x+clyde.ghost_x,maze_y+clyde.ghost_y,life[clyde.eaten_frame],0);
        }



    }



    show_time();
    score_display();

    if(user_interface.state==1)
        iShowBMP2(10,10,UI[20],0xFFFFFF);
    //iShowBMP2(800,400,UI2[2],0xFFFFFF);





//    pinky.ghost_cell=(int)(pinky.ghost_x/wall_w)+(maze_row-1-(int)(pinky.ghost_y/wall_h))*maze_col;
//    pacman.player_cell= (int)pacman.player_x/wall_h + ((maze_row-1-(int)pacman.player_y/wall_h)*maze_col);
    player_lives();

    //printf("%d %d\n",pinky.ghost_cell,pacman.player_cell);






    if(user_interface.pause==0)
    {
        iShowBMP2(200,400,UI[11],0xFFFFFF);
        iShowBMP2(150,300,UI[13],0xFFFFFF);
    }

    if(user_interface.pause==1)
    {
        iShowBMP2(200,400,UI[10],0xFFFFFF);
        iShowBMP2(150,300,UI[12],0xFFFFFF);
    }


    }






    //ghost_animation();


    //Draw Maze

}


void iMouseMove(int mx, int my)
{
    //place your codes here
}


void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //start playing and also turn off bg_music
        if(user_interface.state==0 && mx>=900 && mx<=1150 && my>=400 && my<=480)
        {
            user_interface.state=1;
            PlaySound("pacman_beginning.wav",NULL,SND_LOOP|SND_ASYNC);
            user_interface.game_sound=1;
            initialize();

            //PlaySound("pacman_chomp.wav",NULL,SND_LOOP|SND_ASYNC);
        }


        //sound switch off/on in starting page
        if(user_interface.state==0)
        {
            if(user_interface.bg_music_state==1 && mx>=10 && mx<=75 && my>=420 && my<=485)
            {
                user_interface.bg_music_state=0;
                PlaySound(0,0,0);
            }

            else if(user_interface.bg_music_state==0 && mx>=10 && mx<=75 && my>=420 && my<=485)
            {
                user_interface.bg_music_state=1;
                PlaySound("begin_theme.wav",NULL,SND_LOOP|SND_ASYNC);
            }
        }

        //show help
        if(user_interface.state==0 && mx>=10 && mx<=80 && my>520 && my<=580)
        {
            user_interface.state=10;
        }

        if(user_interface.state==10)
        {
            if(mx>=10 && mx<=70 && my>=30 && my<=100)
                user_interface.state=0;
            if(mx>=1100 && mx<=1170 && my>=30 && my<=100)
                user_interface.state=11;
        }

         if(user_interface.state==11)
        {
            if(mx>=10 && mx<=70 && my>=30 && my<=100)
                user_interface.state=10;
            if(mx>=1100 && mx<=1170 && my>=130 && my<=200)
                user_interface.state=12;
        }

         if(user_interface.state==12)
        {
            if(mx>=10 && mx<=70 && my>=30 && my<=100)
                user_interface.state=11;
            if(mx>=1100 && mx<=1170 && my>=230 && my<=300)
                user_interface.state=13;
        }

         if(user_interface.state==13)
        {
            if(mx>=10 && mx<=70 && my>=130 && my<=200)
                user_interface.state=0;
        }



        //exit game
        if(user_interface.state==0 && mx>=10 && mx<=75 && my>10 && my<=75)
        {
            exit(0);
        }

        //return from help page to menu
        if(user_interface.state==5 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
            //printf("YO\n");
        }

        if(user_interface.state==1)
        {
            if(user_interface.pause==0 && mx>=200 && mx<=270 && my>=400 && my<=470)
                user_interface.pause=1;

            else if(user_interface.pause==1 && mx>=200 && mx<=270 && my>=400 && my<=470)
                user_interface.pause=0;
        }

        //saving
        if(user_interface.state==1 && mx>=10 && mx<=360 && my>=10 && my<=80)
        {
            user_interface.state=0;
            user_interface.save=1;
            //printf("DONE 1\n");
        }

        //New game
        if(user_interface.state==1 && mx>=20 && mx<=120 && my>=400 && my<=550)
        {
            initialize();
            define_maze();
        }


        //credits
        if(user_interface.state==0 && mx>=110 && mx<=400 && my>=500 && my<=600)
        {
            user_interface.state=15;
        }

        //return from hall_of_fame
        if(user_interface.state==15 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
        }

        //game load trigger
        if(user_interface.state==0 && mx>=900 && mx<=1150 && my>=300 && my<=380 && user_interface.save==0)
        {
            user_interface.state=2;
            user_interface.load=1;
             //printf("DONE 2\n");


        }

         if(user_interface.state==0 && mx>=900 && mx<=1150 && my>=300 && my<=380 && user_interface.save==0)
        {
            user_interface.state=2;
            user_interface.load=0;
        }

        if(user_interface.state==2 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
        }

        if(user_interface.state==2 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
            //printf("YO\n");
        }


        //show hall of fame
        if(user_interface.state==0 && mx>=900 && mx<=1150 && my>=200 && my<=300)
        {
            user_interface.state=3;
        }

        //return from hall_of_fame
        if(user_interface.state==3 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
        }

        //highscore when dead
        if(user_interface.state==7 && mx>=1000 && mx<=1185 && my>=10 && my<=90)
        {
            user_interface.state=0;
            user_interface.process=1;
        }

        //highscore when prevail
        if(user_interface.state==8 && mx>=1000 && mx<=1185 && my>=10 && my<=90)
        {
            user_interface.state=0;
            user_interface.process=1;
        }


        //show customization
        if(user_interface.state==0 && mx>=910 && mx<=1150 && my>=90 && my<=150)
        {
            user_interface.state=4;
        }


        //wall-customization
        //difficulty selection
        //maze edit
        if(user_interface.state==4)
        {
            if(mx>=600 && mx<=625 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=0;
                user_interface.wall_img_index=0;
            }

            if(mx>=670 && mx<=685 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=70;
                user_interface.wall_img_index=1;
            }

            if(mx>=740 && mx<=765 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=140;
                user_interface.wall_img_index=2;
            }

            if(mx>=810 && mx<=835 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=210;
                user_interface.wall_img_index=3;
            }

            if(mx>=880 && mx<=905 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=280;
                user_interface.wall_img_index=4;
            }

            if(mx>=950 && mx<=975 && my>=510 && my<=535)
            {
                user_interface.tick_mark_1=350;
                user_interface.wall_img_index=5;
            }



            //return from customize page
            if(mx>=10 && mx<=70 && my>=30 && my<=100)
            {
                user_interface.state=0;
            }



            if(mx>600 && mx<=670 && my>=390 && my<=460)
            {
                user_interface.tick_mark_2=0;
                user_interface.difficulty=1;
            }


            if(mx>800 && mx<=870 && my>=390 && my<=460)
            {
                user_interface.tick_mark_2=200;
                user_interface.difficulty=2;
            }

            if(mx>1000 && mx<=1070 && my>=390 && my<=460)
            {
                user_interface.tick_mark_2=400;
                user_interface.difficulty=3;
            }

            if(mx>=10 && mx<=370 && my>=200 && my<=260)
            {
                user_interface.maze_edit=1;
                user_interface.state=6;

            }
        }



            if(user_interface.state==6 && mx>=10 && mx<=70 && my>=30 && my<=100)
        {
            user_interface.state=0;
            //printf("YO\n");
        }



            if(user_interface.state==6)
            {
                for(int i=0; i<maze_row; i++)
                {
                    for(int j=0; j<maze_col; j++)
                    {
                        cells[i*maze_col+j].x=maze_x+j*wall_w;
                        cells[i*maze_col+j].y=maze_y+maze_row*wall_h-(i+1)*wall_h;

                  if(maze[maze_row-1-((my-maze_y)/maze_col)][(mx-maze_x)/maze_col]==0)
                        {
                            printf("%d\n",((my-maze_y)/maze_col)*maze_col+((mx-maze_x)/maze_col));

                            cells[((maze_row-1-((my-maze_y)/maze_col))*maze_col+((mx-maze_x)/maze_col))].type=1;
                            iPoint(maze_row-1-((my-maze_y)/maze_col),(mx-maze_x)/maze_col,2);
                        }

                    }

                }

            }




    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

        if(user_interface.state==6)
            {
                for(int i=0; i<maze_row; i++)
                {
                    for(int j=0; j<maze_col; j++)
                    {
                        cells[i*maze_col+j].x=maze_x+j*wall_w;
                        cells[i*maze_col+j].y=maze_y+maze_row*wall_h-(i+1)*wall_h;

                  if(maze[maze_row-1-((my-maze_y)/maze_col)][(mx-maze_x)/maze_col]==0)
                        {
                            printf("%d\n",((my-maze_y)/maze_col)*maze_col+((mx-maze_x)/maze_col));

                            cells[((maze_row-1-((my-maze_y)/maze_col))*maze_col+((mx-maze_x)/maze_col))].type=0;
                            iPoint(maze_row-1-((my-maze_y)/maze_col),(mx-maze_x)/maze_col,2);
                        }

                    }

                }

            }
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
//    if(user_interface.state==0 && user_interface.bg_music_state==1 && key == 'q')
//    {
//        user_interface.bg_music_state=0;
//        PlaySound(0,0,0);
//    }
//
//    else if(user_interface.state==0 && user_interface.bg_music_state==0 && key=='q')
//    {
//        user_interface.bg_music_state=1;
//        PlaySound("begin_theme.wav",NULL,SND_LOOP|SND_ASYNC);
//    }

    if(user_interface.state==1 && key=='r')
    {
        if(user_interface.pause==1)
            user_interface.pause=0;

        else
            user_interface.pause=1;
    }

    if((user_interface.state==7 || user_interface.state==8) && key!='\b')
    {
        str[index]=key;
        index++;
        str[index]='\0';
    }

    else if(key=='\b')
    {


        str[--index]='\0';
        if(index<0)
            index=0;
    }


}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_UP)
    {
        pacman.player_direction=0;
    }

    if(key == GLUT_KEY_RIGHT)
    {
        pacman.player_direction=1;
    }

    if(key == GLUT_KEY_LEFT)
    {
        pacman.player_direction=3;
    }

    if(key == GLUT_KEY_DOWN)
    {
        pacman.player_direction=2;
    }

}

void food()
{
    if(user_interface.game_sound==1)
            PlaySound("begin_theme.wav",NULL,SND_LOOP|SND_ASYNC);
}

void define_maze()
{

//  0->open paths and food, 1->walls , 3->passed through, 4->berries, 5->power pelates, 9->pacman spawn
    int p,q,m,n,o,r,x,y,p1,p2,q1,q2;

    pacman.chomp_sound=0;
    for(int i=0;i<maze_row;i++)
    {
        for(int j=0;j<maze_col;j++)
        {
            cells[i*maze_col+j].x=maze_x+j*wall_w;
            cells[i*maze_col+j].y=maze_y+maze_row*wall_h-(i+1)*wall_h;
            pacman.player_cell=(int)((pacman.player_x+pacman_w/2)/wall_w)+(maze_row-1-(int)((pacman.player_y+pacman_h/2)/wall_h))*maze_col;

            srand(time(0));

            //for walls
            if(maze[i][j]==1)
            {
                cells[i*maze_col+j].type=1;
            }

            //for shortcuts
            if(maze[i][j]==2)
            {
                cells[i*maze_col+j].type=2;
            }

            //TO BLOCK SHORTCUTS
            if(maze[i][j]==6 && user_interface.short_off==1)
            {
                //printf("YES MAN\n");
                cells[i*maze_col+j].type=1;
            }
            if(maze[i][j]==6 && user_interface.short_off==0)
            {
                //printf("NO MAN\n");
                cells[i*maze_col+j].type=6;
            }




            //for pelates
            if(maze[i][j]==5)
            {
                cells[i*maze_col+j].type=5;
            }


            //for Health potion
            m=rand()%15;
            n=rand()%15;

            if(maze[m][n]==3 && user_interface.clock_time>5 && pacman.potion_red>0)
                {
                    cells[m*maze_col+n].type=7;
                    maze[m][n]=7;
                    pacman.potion_red--;
                }


            //invisible potion
            o=rand()%15;
            r=rand()%15;

            if(maze[o][r]==3 && user_interface.clock_time>20 && pacman.invisible_count>0)
                {
                    cells[o*maze_col+r].type=10;
                    maze[o][r]=10;
                    pacman.invisible_count--;
                }


            //stopper
            x=rand()%14;
            y=rand()%15;

            if(maze[x][y]==3 && user_interface.clock_time>10 && pacman.stop_count<1)
                {
                    cells[x*maze_col+y].type=11;
                    maze[x][y]=11;
                    pacman.stop_count++;
                }





            //for berry random spawning
            p=rand()%17;
            q=rand()%16;

            if(maze[p][q]==0 && pacman.berry>0)
            {

                cells[p*maze_col+q].type=4;
                maze[p][q]=4;
                pacman.berry--;
            }

            //for straw
            p1=rand()%16;
            q1=rand()%16;

            if(maze[p1][q1]==0 && pacman.straw>0)
            {

                cells[p1*maze_col+q1].type=20;
                maze[p1][q1]=20;
                pacman.straw--;
            }

            //for pear
            p2=rand()%16;
            q2=rand()%12;

            if(maze[p2][q2]==0 && pacman.pear>0)
            {

                cells[p2*maze_col+q2].type=21;
                maze[p2][q2]=21;
                pacman.pear--;
            }



            //drawing green dots
            if(maze[i][j]==0 && cells[i*maze_col+j].type==0)
            {
                iSetColor(2,255,2);
                iPoint(cells[i*maze_col+j].x+10,cells[i*maze_col+j].y+10,2);
            }

            //FOR INVISIBILITY POTION
//            p=rand()%17;
//            q=rand()%16;
//
//            if(maze[p][q]==2 && pacman.invisible_count!=1)
//            {
//                cells[p*maze_col+q].type=8;
//                maze[p][q]=8;
//                //pacman.invisible=1;
//               // pacman.invisible_count=1;
//            }




            //eat green dots
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==0)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;

                user_interface.dots++;
                if(user_interface.dots==151)
                {
                    user_interface.state=8;
                }


                pacman.score+=10;
                pacman.chomp_sound=1;

                if(pacman.chomp_sound==1)
                    PlaySound("pacman_chomp.wav",NULL,SND_ASYNC);



            }

            //eat fruit
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==4 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==4)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;

//                user_interface.popup_x=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].x;
//                user_interface.popup_y=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].y;

                //FOR POP-UP
                user_interface.popup_timer=1;
                user_interface.popup_x=pacman.player_x+maze_x-10;
                user_interface.popup_y=pacman.player_y+maze_y-10;


                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.score+=100;
            }

            //eat straw
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==20 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==20)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;

//                user_interface.popup_x=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].x;
//                user_interface.popup_y=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].y;

                //FOR POP-UP
                user_interface.popup_timer=1;
                user_interface.popup_x=pacman.player_x+maze_x-10;
                user_interface.popup_y=pacman.player_y+maze_y-10;


                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.score+=100;
            }

            //eat pear
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==21 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==21)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;

//                user_interface.popup_x=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].x;
//                user_interface.popup_y=cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].y;

                //FOR POP-UP
                user_interface.popup_timer=1;
                user_interface.popup_x=pacman.player_x+maze_x-10;
                user_interface.popup_y=pacman.player_y+maze_y-10;


                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.score+=100;
            }


            //eating paletes
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==5)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;

                //printf("YES son\n");
                pacman.power=1;
                pinky.fright=1;
                inky.fright=1;
                blinky.fright=1;
                clyde.fright=1;
            }

            //eating health potions
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==7 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==7)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;
                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.lives++;
            }

            //eating invisible potions
            if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==10 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==10)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;
                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.invisible=1;
            }

            //for stopper
             if(maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]==11 || cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type==11)
            {
                maze[maze_row-1-(pacman.player_y/19)][(pacman.player_x/19)]=3;
                cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].type=3;
                PlaySound("pacman_eatfruit.wav",NULL,SND_ASYNC);
                pacman.stop_state=1;
                pinky.speed=0;
                clyde.speed=0;
                blinky.speed=0;
                inky.speed=0;
            }



        }

    }
}

void pacman_move()
{
    //printf("%d\n",pacman.player_y);
    if(user_interface.state==1 && user_interface.pause==0)
    {


            if(pacman.player_direction==0)
            {
                pacman.player_y+=3;
                pacman.frame=(rand()%2)+4;
            }
            else if(pacman.player_direction==1)
            {
                pacman.player_x+=3;
                pacman.frame=(rand()%2);
            }
            else if(pacman.player_direction==2)
            {
                pacman.player_y-=3;
                pacman.frame=(rand()%2+6);
            }
            else if(pacman.player_direction==3)
            {
                pacman.player_x-=3;
                pacman.frame=(rand()%2)+2;
            }

            //printf("%d ago\n",pacman.player_x);


            pacman.player_cell=(int)((pacman.player_x+pacman_w/2)/wall_w)+(maze_row-1-(int)((pacman.player_y+pacman_h/2)/wall_h))*maze_col;

            if(((pacman.player_x>=14 && pacman.player_x<=23 && pacman.player_y>=180 && pacman.player_y<=185)&& pacman.player_direction==3) || ((pacman.player_x>=341 && pacman.player_x<=352 && pacman.player_y>=180 && pacman.player_y<=185) && pacman.player_direction==1)) //maze_col*(wall_h-1)
            {
                //printf("%d after\n",pacman.player_x);
//                printf("\nYES YES YES\n");

                if((pacman.player_x>=14 && pacman.player_x<=23 ))
                    pacman.player_x= 350; //maze_col+(wall_h+1);
                else if(pacman.player_x>=341 && pacman.player_x<=352)
                    pacman.player_x=13;

                //timer=4;

            }

            if(cells[pacman.player_cell-maze_col].type==1 && (pacman.player_y+pacman_h)>cells[pacman.player_cell-maze_col].y-maze_y)//up
            {
                pacman.player_y=cells[pacman.player_cell-maze_col].y-pacman_h-maze_y;
            }

            if(cells[pacman.player_cell+maze_col].type==1 && pacman.player_y<cells[pacman.player_cell].y-maze_y)//down
            {
                pacman.player_y=cells[pacman.player_cell].y-maze_y;
            }


            if(cells[pacman.player_cell-1].type==1 && pacman.player_x<cells[pacman.player_cell-1].x+wall_w-maze_x)//left
            {
                pacman.player_x=cells[pacman.player_cell-1].x+wall_w-maze_x;
            }


            if(cells[pacman.player_cell+1].type==1 && pacman.player_x+pacman_w>cells[pacman.player_cell+1].x-maze_x)//right
            {
                pacman.player_x=cells[pacman.player_cell+1].x-maze_x-pacman_w;
            }

}

}

void inky_move()
{
    if((user_interface.difficulty==1 && user_interface.state==1 && inky.retreat==0) || (pacman.score<=1000 && user_interface.difficulty==2 && user_interface.state==1))

    {
    // 0->up, 1->right, 2->down, 3->left

    if(user_interface.pause==0)
    {


   // printf("inky %d\n",pinky.ghost_x);
  // printf("inky %d\n",inky.ghost_y);

    if(((inky.ghost_x>=9 && inky.ghost_x<=15) && inky.ghost_y>=180 && inky.ghost_y<=185 && inky.ghost_direction==3)||((inky.ghost_x>=350 && inky.ghost_x<=360) && inky.ghost_y>=180 && inky.ghost_y<=185 && inky.ghost_direction==1))
    {
        if(user_interface.difficulty==2)
        {

         if(inky.ghost_x<=15)
            {
                inky.ghost_x= 360;
            }                   //maze_col*wall_w+1;
        else if(inky.ghost_x>=360)
            {
                inky.ghost_x=10;
            }

        pinky.timer=10;
    }
    else
    {
                    if(inky.ghost_direction==1)
                    {
                        inky.ghost_direction=3;
                    }
                    else if(inky.ghost_direction==3)
                    {
                        inky.ghost_direction=1;
                    }
                }
    }
    else
    {
        inky.ghost_cell=(int)(inky.ghost_x/wall_w)+(maze_row-1-(int)(inky.ghost_y/wall_h))*maze_col;


        if((cells[inky.ghost_cell+1].type!=1||cells[inky.ghost_cell-1].type!=1||
           cells[inky.ghost_cell+maze_col].type!=1||cells[inky.ghost_cell-maze_col].type!=1) && inky.timer<=0)
        {
            srand(time(0));
            inky.temp=rand()%4;

            while(true)
            {
                if(inky.temp==1 && cells[inky.ghost_cell+1].type!=1 && inky.ghost_direction!=3) break;
                else if(inky.temp==3 && cells[inky.ghost_cell-1].type!=1 && inky.ghost_direction!=1) break;
                else if(inky.temp==0 && cells[inky.ghost_cell-maze_col].type!=1 && inky.ghost_direction!=2) break;
                else if(inky.temp==2&&cells[inky.ghost_cell+maze_col].type!=1 && inky.ghost_direction!=0) break;

                inky.temp=(inky.temp+1)%4;
            }
            inky.ghost_direction=inky.temp;
            inky.timer=10;

        }
    }
        //printf("%d %d\n",ghost_cell,cells[ghost_cell].show);

        if(inky.ghost_direction==0)
        {
            inky.ghost_y+=inky.speed;
            inky.frame= (rand()%2);
        }
        else if(inky.ghost_direction==1)
        {
            inky.ghost_x+=inky.speed;
            inky.frame= (rand()%2)+6;
        }
        else if(inky.ghost_direction==2)
        {
            inky.ghost_y-=inky.speed;
            inky.frame= (rand()%2)+2;
        }
        else if(inky.ghost_direction==3)
        {
            inky.ghost_x-=inky.speed;
            inky.frame= (rand()%2)+4;
        }

        inky.timer--;

}

}

}


void pinky_move()
{
    if((user_interface.difficulty==1 && user_interface.state==1 && pinky.retreat==0) || (pacman.score<=1000 && user_interface.difficulty==2 && user_interface.state==1))

    {
    // 0->up, 1->right, 2->down, 3->left

    if(user_interface.pause==0)
    {


    //printf("pinky %d\n",pinky.ghost_x);
   // printf("pinky %d\n",pinky.ghost_y);

    if(((pinky.ghost_x>=9 && pinky.ghost_x<=15) && pinky.ghost_y>=180 && pinky.ghost_y<=185 && pinky.ghost_direction==3)||((pinky.ghost_x>=350 && pinky.ghost_x<=360) && pinky.ghost_y>=180 && pinky.ghost_y<=185 && pinky.ghost_direction==1))
    {

        //WILL BE BLE TO USE SHORTCUT WHEN DIFFULTY IS MORE
        if(user_interface.difficulty==2)
        {
            if(pinky.ghost_x<=15)
            {
                pinky.ghost_x= 365;
            }                    //maze_col*wall_w+1;
        else if(pinky.ghost_x>=360)
            {
                pinky.ghost_x=9;
            }

        pinky.timer=10;
        }

        //WILL RETREAT IF DIFFICULTY IS 1/3
        else
        {
            if(pinky.ghost_direction==1)
                {
                    pinky.ghost_direction=3;
                }
           else if(pinky.ghost_direction==3)
                {
                    pinky.ghost_direction=1;
                }

        }

    }
    else
    {
        pinky.ghost_cell=(int)(pinky.ghost_x/wall_w)+(maze_row-1-(int)(pinky.ghost_y/wall_h))*maze_col;


        if((cells[pinky.ghost_cell+1].type!=1||cells[pinky.ghost_cell-1].type!=1||
           (cells[pinky.ghost_cell+maze_col].type!=1 && pinky.ghost_cell+maze_col!=180)||cells[pinky.ghost_cell-maze_col].type!=1) && pinky.timer<=0)
        {
            srand(time(0));
            pinky.temp=rand()%4;

            while(true)
            {
                if(pinky.temp==1 && cells[pinky.ghost_cell+1].type!=1 && pinky.ghost_direction!=3) break;
                else if(pinky.temp==3 && cells[pinky.ghost_cell-1].type!=1 && pinky.ghost_direction!=1) break;
                else if(pinky.temp==0 && cells[pinky.ghost_cell-maze_col].type!=1 && pinky.ghost_direction!=2) break;
                else if(pinky.temp==2&&cells[pinky.ghost_cell+maze_col].type!=1 && pinky.ghost_direction!=0) break;

                pinky.temp=(pinky.temp+1)%4;
            }
            pinky.ghost_direction=pinky.temp;
            pinky.timer=10;

        }
    }
        //printf("%d %d\n",ghost_cell,cells[ghost_cell].show);

        if(pinky.ghost_direction==0)
        {
            pinky.ghost_y+=pinky.speed;
            pinky.frame= (rand()%2);
        }
        else if(pinky.ghost_direction==1)
        {
            pinky.ghost_x+=pinky.speed;
            pinky.frame= (rand()%2)+6;
        }
        else if(pinky.ghost_direction==2)
        {
            pinky.ghost_y-=pinky.speed;
            pinky.frame= (rand()%2)+2;
        }
        else if(pinky.ghost_direction==3)
        {
            pinky.ghost_x-=pinky.speed;
            pinky.frame= (rand()%2)+4;
        }

        pinky.timer--;

}

}

}


void blinky_move()
{
    if((user_interface.difficulty==1 && user_interface.state==1 && blinky.retreat==0) || (pacman.score<=1000 && user_interface.difficulty==2 && user_interface.state==1))

    {
    // 0->up, 1->right, 2->down, 3->left

    if(user_interface.pause==0)
    {


    //printf("blinky %d\n",blinky.ghost_x);
   // printf("blinky %d\n",blinky.ghost_y);


    if(((blinky.ghost_x>=9 && blinky.ghost_x<=15) && blinky.ghost_y>=180 && blinky.ghost_y<=185 && blinky.ghost_direction==3)||((blinky.ghost_x>=350 && blinky.ghost_x<=360) && blinky.ghost_y>=180 && blinky.ghost_y<=185 && blinky.ghost_direction==1))
    {
        printf("JOJO YES\n");

        //WILL BE BLE TO USE SHORTCUT WHEN DIFFULTY IS MORE
        if(user_interface.difficulty==2)
        {
            if(blinky.ghost_x<=15)
            {
                blinky.ghost_x= 365;
            }          //maze_col*wall_w+1;
        else if(blinky.ghost_x>=350)
            {
                blinky.ghost_x=9;
            }

        blinky.timer=10;
        }

        //WILL RETREAT IF DIFFICULTY IS 1/3
        else
        {
            printf("YES\n");
            if(blinky.ghost_direction==1)
               {
                    blinky.ghost_direction=3;
               }
            else if(blinky.ghost_direction==3)
                {
                    blinky.ghost_direction=1;
                }

        }

    }
    else
    {
        blinky.ghost_cell=(int)(blinky.ghost_x/wall_w)+(maze_row-1-(int)(blinky.ghost_y/wall_h))*maze_col;


        if((cells[blinky.ghost_cell+1].type!=1||cells[blinky.ghost_cell-1].type!=1||
           (cells[blinky.ghost_cell+maze_col].type!=1 && blinky.ghost_cell+maze_col!=180)||cells[blinky.ghost_cell-maze_col].type!=1) && blinky.timer<=0)
        {
            srand(time(0));
            blinky.temp=rand()%4;

            while(true)
            {
                if(blinky.temp==1 && cells[blinky.ghost_cell+1].type!=1 && blinky.ghost_direction!=3) break;
                else if(blinky.temp==3 && cells[blinky.ghost_cell-1].type!=1 && blinky.ghost_direction!=1) break;
                else if(blinky.temp==0 && cells[blinky.ghost_cell-maze_col].type!=1 && blinky.ghost_direction!=2) break;
                else if(blinky.temp==2&&cells[blinky.ghost_cell+maze_col].type!=1 && blinky.ghost_direction!=0) break;

                blinky.temp=(blinky.temp+1)%4;
            }
            blinky.ghost_direction=blinky.temp;
            blinky.timer=10;

        }
    }
        //printf("%d %d\n",ghost_cell,cells[ghost_cell].show);

        if(blinky.ghost_direction==0)
        {
            blinky.ghost_y+=blinky.speed;
            blinky.frame= (rand()%2);
        }
        else if(blinky.ghost_direction==1)
        {
            blinky.ghost_x+=blinky.speed;
            blinky.frame= (rand()%2)+6;
        }
        else if(blinky.ghost_direction==2)
        {
            blinky.ghost_y-=blinky.speed;
            blinky.frame= (rand()%2)+2;
        }
        else if(blinky.ghost_direction==3)
        {
            blinky.ghost_x-=blinky.speed;
            blinky.frame= (rand()%2)+4;
        }

        blinky.timer--;

}

}

}


void clyde_move()
{
    if((user_interface.difficulty==1 && user_interface.state==1 && clyde.retreat==0) || (pacman.score<=1000 && user_interface.difficulty==2 && user_interface.state==1))

    {
    // 0->up, 1->right, 2->down, 3->left

    if(user_interface.pause==0)
    {


   // printf("clyde %d\n",clyde.ghost_x);
    //printf("clyde %d\n",clyde.ghost_y);

    if(((clyde.ghost_x>=9 && clyde.ghost_x<=15) && clyde.ghost_y>=180 && clyde.ghost_y<=185 && clyde.ghost_direction==3)||((clyde.ghost_x>=350 && clyde.ghost_x<=360) && clyde.ghost_y>=180 && clyde.ghost_y<=185 && clyde.ghost_direction==1))
    {
        printf("JOJO YES\n");

        //WILL BE BLE TO USE SHORTCUT WHEN DIFFULTY IS MORE
        if(user_interface.difficulty==2)
        {
            if(clyde.ghost_x<=15)
            {
                clyde.ghost_x= 365;
            }                               //maze_col*wall_w+1;
        else if(clyde.ghost_x>=360)
            {
                clyde.ghost_x=9;
            }

        clyde.timer=10;
        }

        //WILL RETREAT IF DIFFICULTY IS 1/3
        else
        {printf("YES\n");
            if(clyde.ghost_direction==1)
                {
                    clyde.ghost_direction=3;
                }
            else if(clyde.ghost_direction==3)
                {
                    clyde.ghost_direction=1;
                }

        }

    }
    else
    {
        clyde.ghost_cell=(int)(clyde.ghost_x/wall_w)+(maze_row-1-(int)(clyde.ghost_y/wall_h))*maze_col;


        if((cells[clyde.ghost_cell+1].type!=1||cells[clyde.ghost_cell-1].type!=1||
           (cells[clyde.ghost_cell+maze_col].type!=1 && clyde.ghost_cell+maze_col!=180)||cells[clyde.ghost_cell-maze_col].type!=1) && clyde.timer<=0)
        {
            srand(time(0));
            clyde.temp=rand()%4;

            while(true)
            {
                if(clyde.temp==1 && cells[clyde.ghost_cell+1].type!=1 && clyde.ghost_direction!=3) break;
                else if(clyde.temp==3 && cells[clyde.ghost_cell-1].type!=1 && clyde.ghost_direction!=1) break;
                else if(clyde.temp==0 && cells[clyde.ghost_cell-maze_col].type!=1 && clyde.ghost_direction!=2) break;
                else if(clyde.temp==2&&cells[clyde.ghost_cell+maze_col].type!=1 && clyde.ghost_direction!=0) break;

                clyde.temp=(clyde.temp+1)%4;
            }
            clyde.ghost_direction=clyde.temp;
            clyde.timer=10;

        }
    }
        //printf("%d %d\n",ghost_cell,cells[ghost_cell].show);

        if(clyde.ghost_direction==0)
        {
            clyde.ghost_y+=clyde.speed;
            clyde.frame= (rand()%2);
        }
        else if(clyde.ghost_direction==1)
        {
            clyde.ghost_x+=clyde.speed;
            clyde.frame= (rand()%2)+6;
        }
        else if(clyde.ghost_direction==2)
        {
            clyde.ghost_y-=clyde.speed;
            clyde.frame= (rand()%2)+2;
        }
        else if(clyde.ghost_direction==3)
        {
            clyde.ghost_x-=clyde.speed;
            clyde.frame= (rand()%2)+4;
        }

        clyde.timer--;

}

}

}


void blinky_short_move()
{

    if((user_interface.difficulty==3 && user_interface.state==1 && blinky.retreat==0) || (pacman.score>1000 && user_interface.difficulty==2 && user_interface.state==1))
    {


    if(user_interface.pause==0)
    {

    int d_right,d_left,d_up,d_down;

    blinky.ghost_cell=(int)(blinky.ghost_x/wall_w)+(maze_row-1-(int)(blinky.ghost_y/wall_h))*maze_col;

    if(blinky.timer<=0)
    {
        d_right = abs(blinky.ghost_cell+1-pacman.player_cell);
        d_left = abs(blinky.ghost_cell-1-pacman.player_cell);
        d_up = abs(blinky.ghost_cell-maze_col-pacman.player_cell);
        d_down = abs(blinky.ghost_cell+maze_row-pacman.player_cell);



        if(blinky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[blinky.ghost_cell-maze_col].type==1 || cells[blinky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[blinky.ghost_cell+1].type==1 || cells[blinky.ghost_cell+1].type==6) d_right=1000;
            if(cells[blinky.ghost_cell-1].type==1 || cells[blinky.ghost_cell-1].type==6) d_left=1000;

        }
        if(blinky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1 || cells[blinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[blinky.ghost_cell-maze_col].type==1 || cells[blinky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[blinky.ghost_cell+1].type==1 || cells[blinky.ghost_cell+1].type==6) d_right=1000;

        }
        if(blinky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1 || cells[blinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[blinky.ghost_cell+1].type==1 || cells[blinky.ghost_cell+1].type==6) d_right=1000;
            if(cells[blinky.ghost_cell-1].type==1 || cells[blinky.ghost_cell-1].type==6) d_left=1000;

        }
        if(blinky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1 || cells[blinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[blinky.ghost_cell-1].type==1 || cells[blinky.ghost_cell-1].type==6) d_left=1000;
            if(cells[blinky.ghost_cell-maze_col].type==1 || cells[blinky.ghost_cell-maze_col].type==6) d_up=1000;

        }

        blinky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(blinky.temp==d_up)
        {
           blinky.ghost_direction=0;
        }
        else if(blinky.temp==d_down)
        {
            blinky.ghost_direction=2;
        }
        else if(blinky.temp==d_right)
        {
            blinky.ghost_direction=1;
        }
        else if(blinky.temp==d_left)
        {
            blinky.ghost_direction=3;
        }

        blinky.timer=10;
    }
        if(blinky.ghost_direction==0)
        {
            blinky.ghost_y+=blinky.speed;
            blinky.frame= (rand()%2);
        }
        else if(blinky.ghost_direction==1)
        {
            blinky.ghost_x+=blinky.speed;
            blinky.frame= (rand()%2)+6;
        }
        else if(blinky.ghost_direction==2)
        {
            blinky.ghost_y-=blinky.speed;
            blinky.frame= (rand()%2)+2;
        }
        else if(blinky.ghost_direction==3)
        {
            blinky.ghost_x-=blinky.speed;
            blinky.frame= (rand()%2)+4;
        }

        blinky.timer--;

        //printf("%d %d %d %d\n",d_up,d_down,d_right,d_left);
}

}

}


void clyde_short_move()
{

    if((user_interface.difficulty==3 && user_interface.state==1 && clyde.retreat==0) || (pacman.score>1000 && user_interface.difficulty==2 && user_interface.state==1))
    {


    if(user_interface.pause==0)
    {

    int d_right,d_left,d_up,d_down;

    clyde.ghost_cell=(int)(clyde.ghost_x/wall_w)+(maze_row-1-(int)(clyde.ghost_y/wall_h))*maze_col;

    if(clyde.timer<=0)
    {
        d_right = abs(clyde.ghost_cell+1-pacman.player_cell);
        d_left = abs(clyde.ghost_cell-1-pacman.player_cell);
        d_up = abs(clyde.ghost_cell-maze_col-pacman.player_cell);
        d_down = abs(clyde.ghost_cell+maze_row-pacman.player_cell);



        if(clyde.ghost_direction==0)
        {
            d_down=1000;

            if(cells[clyde.ghost_cell-maze_col].type==1 || cells[clyde.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[clyde.ghost_cell+1].type==1 || cells[clyde.ghost_cell+1].type==6) d_right=1000;
            if(cells[clyde.ghost_cell-1].type==1 || cells[clyde.ghost_cell-1].type==6) d_left=1000;

        }
        if(clyde.ghost_direction==1)
        {
            d_left=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1 || cells[clyde.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[clyde.ghost_cell-maze_col].type==1 || cells[clyde.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[clyde.ghost_cell+1].type==1 || cells[clyde.ghost_cell+1].type==6) d_right=1000;

        }
        if(clyde.ghost_direction==2)
        {
            d_up=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1 || cells[clyde.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[clyde.ghost_cell+1].type==1 || cells[clyde.ghost_cell+1].type==6) d_right=1000;
            if(cells[clyde.ghost_cell-1].type==1 || cells[clyde.ghost_cell-1].type==6) d_left=1000;

        }
        if(clyde.ghost_direction==3)
        {
            d_right=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1 || cells[clyde.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[clyde.ghost_cell-1].type==1 || cells[clyde.ghost_cell-1].type==6) d_left=1000;
            if(cells[clyde.ghost_cell-maze_col].type==1 || cells[clyde.ghost_cell-maze_col].type==6) d_up=1000;

        }

        clyde.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(clyde.temp==d_up)
        {
           clyde.ghost_direction=0;
        }
        else if(clyde.temp==d_down)
        {
            clyde.ghost_direction=2;
        }
        else if(clyde.temp==d_right)
        {
            clyde.ghost_direction=1;
        }
        else if(clyde.temp==d_left)
        {
            clyde.ghost_direction=3;
        }

        clyde.timer=10;
    }
        if(clyde.ghost_direction==0)
        {
            clyde.ghost_y+=clyde.speed;
            clyde.frame= (rand()%2);
        }
        else if(clyde.ghost_direction==1)
        {
            clyde.ghost_x+=clyde.speed;
            clyde.frame= (rand()%2)+6;
        }
        else if(clyde.ghost_direction==2)
        {
            clyde.ghost_y-=clyde.speed;
            clyde.frame= (rand()%2)+2;
        }
        else if(clyde.ghost_direction==3)
        {
            clyde.ghost_x-=clyde.speed;
            clyde.frame= (rand()%2)+4;
        }

        clyde.timer--;

        //printf("%d %d %d %d\n",d_up,d_down,d_right,d_left);
}

}

}


void inky_short_move()
{

    if((user_interface.difficulty==3 && user_interface.state==1 && inky.retreat==0) || (pacman.score>1000 && user_interface.difficulty==2 && user_interface.state==1))
    {


    if(user_interface.pause==0)
    {

    int d_right,d_left,d_up,d_down,destruct;
//        if(pacman.player_direction==0)
//            destruct=-maze_row*3;
//        if(pacman.player_direction==1)
//            destruct=3;
//        if(pacman.player_direction==2)
//        destruct=maze_row*3;
//        if(pacman.player_direction==3)
//        destruct=-3;

    inky.ghost_cell=(int)(inky.ghost_x/wall_w)+(maze_row-1-(int)(inky.ghost_y/wall_h))*maze_col;

    if(inky.timer<=0)
    {
        d_right = abs(inky.ghost_cell+1-(pacman.player_cell));
        d_left = abs(inky.ghost_cell-1-(pacman.player_cell));
        d_up = abs(inky.ghost_cell-maze_col-(pacman.player_cell));
        d_down = abs(inky.ghost_cell+maze_row-(pacman.player_cell));



        if(inky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[inky.ghost_cell-maze_col].type==1 && cells[inky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[inky.ghost_cell+1].type==1 || cells[inky.ghost_cell+1].type==6) d_right=1000;
            if(cells[inky.ghost_cell-1].type==1 || cells[inky.ghost_cell-1].type==6) d_left=1000;

        }
        if(inky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[inky.ghost_cell+maze_col].type==1 && cells[inky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[inky.ghost_cell-maze_col].type==1 && cells[inky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[inky.ghost_cell+1].type==1 && cells[inky.ghost_cell+1].type==6) d_right=1000;

        }
        if(inky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[inky.ghost_cell+maze_col].type==1 || cells[inky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[inky.ghost_cell+1].type==1 || cells[inky.ghost_cell+1].type==6) d_right=1000;
            if(cells[inky.ghost_cell-1].type==1 || cells[inky.ghost_cell-1].type==6) d_left=1000;

        }
        if(inky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[inky.ghost_cell+maze_col].type==1 || cells[inky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[inky.ghost_cell-1].type==1 || cells[inky.ghost_cell-1].type==6) d_left=1000;
            if(cells[inky.ghost_cell-maze_col].type==1 || cells[inky.ghost_cell-maze_col].type==6) d_up=1000;

        }

        inky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(inky.temp==d_up)
        {
           inky.ghost_direction=0;
        }
        else if(inky.temp==d_down)
        {
            inky.ghost_direction=2;
        }
        else if(inky.temp==d_right)
        {
            inky.ghost_direction=1;
        }
        else if(inky.temp==d_left)
        {
            inky.ghost_direction=3;
        }

        inky.timer=10;
    }
        if(inky.ghost_direction==0)
        {
            inky.ghost_y+=inky.speed;
            inky.frame= (rand()%2);
        }
        else if(inky.ghost_direction==1)
        {
            inky.ghost_x+=inky.speed;
            inky.frame= (rand()%2)+6;
        }
        else if(inky.ghost_direction==2)
        {
            inky.ghost_y-=inky.speed;
            inky.frame= (rand()%2)+2;
        }
        else if(inky.ghost_direction==3)
        {
            inky.ghost_x-=inky.speed;
            inky.frame= (rand()%2)+4;
        }

        inky.timer--;

        //printf("%d %d %d %d\n",d_up,d_down,d_right,d_left);
}

}

}


void pinky_short_move()
{

    if((user_interface.difficulty==3 && user_interface.state==1 && pinky.retreat==0) || (pacman.score>1000 && user_interface.difficulty==2 && user_interface.state==1))
    {


    if(user_interface.pause==0)
    {

    int d_right,d_left,d_up,d_down;

    pinky.ghost_cell=(int)(pinky.ghost_x/wall_w)+(maze_row-1-(int)(pinky.ghost_y/wall_h))*maze_col;

    if(pinky.timer<=0)
    {
        d_right = abs(pinky.ghost_cell+1-pacman.player_cell);
        d_left = abs(pinky.ghost_cell-1-pacman.player_cell);
        d_up = abs(pinky.ghost_cell-maze_col-pacman.player_cell);
        d_down = abs(pinky.ghost_cell+maze_row-pacman.player_cell);



        if(pinky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[pinky.ghost_cell-maze_col].type==1 || cells[pinky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[pinky.ghost_cell+1].type==1 || cells[pinky.ghost_cell+1].type==6) d_right=1000;
            if(cells[pinky.ghost_cell-1].type==1 || cells[pinky.ghost_cell-1].type==6) d_left=1000;

        }
        if(pinky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1 || cells[pinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[pinky.ghost_cell-maze_col].type==1 || cells[pinky.ghost_cell-maze_col].type==6) d_up=1000;
            if(cells[pinky.ghost_cell+1].type==1 || cells[pinky.ghost_cell+1].type==6) d_right=1000;

        }
        if(pinky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1 || cells[pinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[pinky.ghost_cell+1].type==1 || cells[pinky.ghost_cell+1].type==6) d_right=1000;
            if(cells[pinky.ghost_cell-1].type==1 || cells[pinky.ghost_cell-1].type==6) d_left=1000;

        }
        if(pinky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1 || cells[pinky.ghost_cell+maze_col].type==6) d_down=1000;
            if(cells[pinky.ghost_cell-1].type==1 || cells[pinky.ghost_cell-1].type==6) d_left=1000;
            if(cells[pinky.ghost_cell-maze_col].type==1 || cells[pinky.ghost_cell-maze_col].type==6) d_up=1000;

        }

        pinky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(pinky.temp==d_up)
        {
           pinky.ghost_direction=0;
        }
        else if(pinky.temp==d_down)
        {
            pinky.ghost_direction=2;
        }
        else if(pinky.temp==d_right)
        {
            pinky.ghost_direction=1;
        }
        else if(pinky.temp==d_left)
        {
            pinky.ghost_direction=3;
        }

        pinky.timer=10;
    }
        if(pinky.ghost_direction==0)
        {
            pinky.ghost_y+=pinky.speed;
            pinky.frame= (rand()%2);
        }
        else if(pinky.ghost_direction==1)
        {
            pinky.ghost_x+=pinky.speed;
            pinky.frame= (rand()%2)+6;
        }
        else if(pinky.ghost_direction==2)
        {
            pinky.ghost_y-=pinky.speed;
            pinky.frame= (rand()%2)+2;
        }
        else if(pinky.ghost_direction==3)
        {
            pinky.ghost_x-=pinky.speed;
            pinky.frame= (rand()%2)+4;
        }

        pinky.timer--;

        //printf("%d %d %d %d\n",d_up,d_down,d_right,d_left);
}

}

}


//USED FOR DETERMINING SHORT PATH OF GHOSTS
int determine_smallest(int a, int b, int c)
{
    int smal;

    if(a<b)
    {
        if(b<c)
            smal = a;
        else
        {
            if(a<c)
                smal = a;
            else
                smal = c;
        }
    }
    else
    {
        if(b<c)
            smal = b;
        else
            smal = c;
    }
    return smal;
}



//FOR FRIGHT MODE
void time_pass()
{
    if(pacman.power==1)
    {
        time_passed++;

        if(time_passed==10)
        {
            pacman.power=0;
            time_passed=0;
            user_interface.collide_count=0;
        }
    }



}

//FOR INVISIBILITY OF GHOST
//void invisible_time()
//{
//    if(pacman.invisible==1)
//        time_passed2++;
//
//        if(time_passed2==5)
//            {
//                time_passed2=0;
//                pacman.invisible=0;
//            }
//
//}

//FOR COUNTING TIMER ON SCREEN AND FOR SHORTCUT CLOSING
void timer()
{
    if(user_interface.state==1 && user_interface.pause==0)
    {
        user_interface.clock_time++;
        user_interface.short_off_timer++;
    }

    if(user_interface.popup_timer==1)
    {

        //cells[(maze_row-1-(pacman.player_y/19))*maze_col+(pacman.player_x/19)].x;


        user_interface.popup_timer_count++;
        if(user_interface.popup_timer_count<=1)
        {
            user_interface.popup_timer_count=0;
            user_interface.popup_timer=0;
            user_interface.popup_x=0;
            user_interface.popup_y=0;
        }
    }


    //FOR SHORTCUT BLOCK
    if((user_interface.short_off_timer%5)==0 && user_interface.difficulty==3 && user_interface.state==1)
    {

        user_interface.short_image=1;
        user_interface.short_off=1;
        //printf("%d\n",user_interface.short_off);

    }

    if((user_interface.short_off_timer%8)==0 && user_interface.state==1)
        {
            //printf("JOJO NO\n");
            user_interface.short_off_timer=0;
            user_interface.short_image=0;
            user_interface.short_off=0;
        }

    if(user_interface.state==9)
    {
        user_interface.anime_index++;
        if(user_interface.anime_index>6)
        {
            user_interface.state=0;
        }
    }

    if(pacman.invisible==1)
    {
        pacman.invisible_time++;
        if(pacman.invisible_time%5==0)
        {
            pacman.invisible=0;
            pacman.invisible_time=0;
        }
    }

    if(pacman.stop_state==1)
    {
        pacman.stop_timerl++;
        if(pacman.stop_timerl%5==0)
        {
            pacman.stop_state=0;
            pinky.speed=2;
            inky.speed=2;
            blinky.speed=2;
            clyde.speed=2;
        }
    }

}


void all_times()
{
    time_pass();
    timer();
}


//FOR SHOWING TIMER ON SCREEN
void show_time()
{

    if(user_interface.state==1)
    {
       int x=user_interface.clock_time;
        int i=0,n=1,a[20];

        iShowBMP2(560,460,UI2[2],0xFFFFFF);
        while(x!=0)
        {
            i++;
            a[i]=x%10;
            x=x/10;

        }

        while(n<=i)
        {
            iShowBMP2(780-(n*20),470,scores[a[n]],0);
            n++;
        }
    }

    //iShowBMP2(800,400,UI[18],0xFFFFFF);
//    while(x!=0)
//    {
//        i++;
//        a[i]=x%10;
//        x=x/10;
//
//    }
//
//    while(n<=i)
//    {
//        iShowBMP2(1180-(n*20),415,scores[a[n]],0);
//        n++;
//    }
}


void clyde_fright_mode()
{


//    while(g<1)
//    {
//        if(clyde.ghost_direction==1)
//            clyde.ghost_direction=3;
//
//        else if(clyde.ghost_direction==3)
//            clyde.ghost_direction=1;
//
//        else if(clyde.ghost_direction==0)
//            clyde.ghost_direction=2;
//
//        else if(clyde.ghost_direction==2)
//            clyde.ghost_direction=0;
//
//            g++;
//    }


    if(clyde.retreat==1 && clyde.fright==1)
    {
    int d_right,d_left,d_up,d_down;

    clyde.ghost_cell=(int)(clyde.ghost_x/wall_w)+(maze_row-1-(int)(clyde.ghost_y/wall_h))*maze_col;

    if(clyde.timer<=0)
    {
        d_right = abs(clyde.ghost_cell+1-target_cell);
        d_left = abs(clyde.ghost_cell-1-target_cell);
        d_up = abs(clyde.ghost_cell-maze_col-target_cell);
        d_down = abs(clyde.ghost_cell+maze_row-target_cell);



        if(clyde.ghost_direction==0)
        {
            d_down=1000;

            if(cells[clyde.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[clyde.ghost_cell+1].type==1) d_right=1000;
            if(cells[clyde.ghost_cell-1].type==1) d_left=1000;

        }
        if(clyde.ghost_direction==1)
        {
            d_left=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[clyde.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[clyde.ghost_cell+1].type==1) d_right=1000;

        }
        if(clyde.ghost_direction==2)
        {
            d_up=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[clyde.ghost_cell+1].type==1) d_right=1000;
            if(cells[clyde.ghost_cell-1].type==1) d_left=1000;

        }
        if(clyde.ghost_direction==3)
        {
            d_right=1000;

            if(cells[clyde.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[clyde.ghost_cell-1].type==1) d_left=1000;
            if(cells[clyde.ghost_cell-maze_col].type==1) d_up=1000;

        }

        clyde.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(clyde.temp==d_up)
        {
           clyde.ghost_direction=0;
        }
        else if(clyde.temp==d_down)
        {
            clyde.ghost_direction=2;
        }
        else if(clyde.temp==d_right)
        {
            clyde.ghost_direction=1;
        }
        else if(clyde.temp==d_left)
        {
            clyde.ghost_direction=3;
        }

        clyde.timer=10;
    }
        if(clyde.ghost_direction==0)
        {
            clyde.ghost_y+=clyde.speed;
            clyde.eaten_frame= 3;
        }
        else if(clyde.ghost_direction==1)
        {
            clyde.ghost_x+=clyde.speed;
            clyde.eaten_frame=1;
        }
        else if(clyde.ghost_direction==2)
        {
            clyde.ghost_y-=clyde.speed;
            clyde.eaten_frame= 4;
        }
        else if(clyde.ghost_direction==3)
        {
            clyde.ghost_x-=clyde.speed;
            clyde.eaten_frame= 2;
        }

        clyde.timer--;

        if(target_cell==clyde.ghost_cell)
            {
                clyde.retreat=0;
                clyde.fright=0;
                //pacman.power=0;
            }

    }
}


void blinky_fright_mode()
{


//    while(g<1)
//    {
//        if(blinky.ghost_direction==1)
//            blinky.ghost_direction=3;
//
//        else if(blinky.ghost_direction==3)
//            blinky.ghost_direction=1;
//
//        else if(blinky.ghost_direction==0)
//            blinky.ghost_direction=2;
//
//        else if(blinky.ghost_direction==2)
//            blinky.ghost_direction=0;
//
//            g++;
//    }


    if(blinky.retreat==1 && blinky.fright==1)
    {
    int d_right,d_left,d_up,d_down;

    blinky.ghost_cell=(int)(blinky.ghost_x/wall_w)+(maze_row-1-(int)(blinky.ghost_y/wall_h))*maze_col;

    if(blinky.timer<=0)
    {
        d_right = abs(blinky.ghost_cell+1-target_cell);
        d_left = abs(blinky.ghost_cell-1-target_cell);
        d_up = abs(blinky.ghost_cell-maze_col-target_cell);
        d_down = abs(blinky.ghost_cell+maze_row-target_cell);



        if(blinky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[blinky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[blinky.ghost_cell+1].type==1) d_right=1000;
            if(cells[blinky.ghost_cell-1].type==1) d_left=1000;

        }
        if(blinky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[blinky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[blinky.ghost_cell+1].type==1) d_right=1000;

        }
        if(blinky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[blinky.ghost_cell+1].type==1) d_right=1000;
            if(cells[blinky.ghost_cell-1].type==1) d_left=1000;

        }
        if(blinky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[blinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[blinky.ghost_cell-1].type==1) d_left=1000;
            if(cells[blinky.ghost_cell-maze_col].type==1) d_up=1000;

        }

        blinky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(blinky.temp==d_up)
        {
           blinky.ghost_direction=0;
        }
        else if(blinky.temp==d_down)
        {
            blinky.ghost_direction=2;
        }
        else if(blinky.temp==d_right)
        {
            blinky.ghost_direction=1;
        }
        else if(blinky.temp==d_left)
        {
            blinky.ghost_direction=3;
        }

        blinky.timer=10;
    }
        if(blinky.ghost_direction==0)
        {
            blinky.ghost_y+=blinky.speed;
            blinky.eaten_frame= 3;
        }
        else if(blinky.ghost_direction==1)
        {
            blinky.ghost_x+=blinky.speed;
            blinky.eaten_frame=1;
        }
        else if(blinky.ghost_direction==2)
        {
            blinky.ghost_y-=blinky.speed;
            blinky.eaten_frame= 4;
        }
        else if(blinky.ghost_direction==3)
        {
            blinky.ghost_x-=blinky.speed;
            blinky.eaten_frame= 2;
        }

        blinky.timer--;

        if(target_cell==blinky.ghost_cell)
            {
                blinky.retreat=0;
                blinky.fright=0;
                //pacman.power=0;
            }

    }
}


void inky_fright_mode()
{
//    if(inky.fright==1 && inky.retreat==0)
//    {
//        inky_move();
//    }


    if(inky.retreat==1 && inky.fright==1)
    {
    int d_right,d_left,d_up,d_down;

    inky.ghost_cell=(int)(inky.ghost_x/wall_w)+(maze_row-1-(int)(inky.ghost_y/wall_h))*maze_col;

    if(inky.timer<=0)
    {
        d_right = abs(inky.ghost_cell+1-target_cell);
        d_left = abs(inky.ghost_cell-1-target_cell);
        d_up = abs(inky.ghost_cell-maze_col-target_cell);
        d_down = abs(inky.ghost_cell+maze_row-target_cell);



        if(inky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[inky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[inky.ghost_cell+1].type==1) d_right=1000;
            if(cells[inky.ghost_cell-1].type==1) d_left=1000;

        }
        if(inky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[inky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[inky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[inky.ghost_cell+1].type==1) d_right=1000;

        }
        if(inky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[inky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[inky.ghost_cell+1].type==1) d_right=1000;
            if(cells[inky.ghost_cell-1].type==1) d_left=1000;

        }
        if(inky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[inky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[inky.ghost_cell-1].type==1) d_left=1000;
            if(cells[inky.ghost_cell-maze_col].type==1) d_up=1000;

        }

        inky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(inky.temp==d_up)
        {
           inky.ghost_direction=0;
        }
        else if(inky.temp==d_down)
        {
            inky.ghost_direction=2;
        }
        else if(inky.temp==d_right)
        {
            inky.ghost_direction=1;
        }
        else if(inky.temp==d_left)
        {
            inky.ghost_direction=3;
        }

        inky.timer=10;
    }
        if(inky.ghost_direction==0)
        {
            inky.ghost_y+=inky.speed;
            inky.eaten_frame= 3;
        }
        else if(inky.ghost_direction==1)
        {
            inky.ghost_x+=inky.speed;
            inky.eaten_frame=1;
        }
        else if(inky.ghost_direction==2)
        {
            inky.ghost_y-=inky.speed;
            inky.eaten_frame= 4;
        }
        else if(inky.ghost_direction==3)
        {
            inky.ghost_x-=inky.speed;
            inky.eaten_frame= 2;
        }

        inky.timer--;

        if(target_cell==inky.ghost_cell)
            {
                inky.retreat=0;
                inky.fright=0;
                //pacman.power=0;
            }

    }
}

void pinky_fright_mode()
{


//    while(g<1)
//    {
//        if(pinky.ghost_direction==1)
//            pinky.ghost_direction=3;
//
//        else if(pinky.ghost_direction==3)
//            pinky.ghost_direction=1;
//
//        else if(pinky.ghost_direction==0)
//            pinky.ghost_direction=2;
//
//        else if(pinky.ghost_direction==2)
//            pinky.ghost_direction=0;
//
//            g++;
//    }


    if(pinky.retreat==1 && pinky.fright==1)
    {
    int d_right,d_left,d_up,d_down;

    pinky.ghost_cell=(int)(pinky.ghost_x/wall_w)+(maze_row-1-(int)(pinky.ghost_y/wall_h))*maze_col;

    if(pinky.timer<=0)
    {
        d_right = abs(pinky.ghost_cell+1-target_cell);
        d_left = abs(pinky.ghost_cell-1-target_cell);
        d_up = abs(pinky.ghost_cell-maze_col-target_cell);
        d_down = abs(pinky.ghost_cell+maze_row-target_cell);



        if(pinky.ghost_direction==0)
        {
            d_down=1000;

            if(cells[pinky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[pinky.ghost_cell+1].type==1) d_right=1000;
            if(cells[pinky.ghost_cell-1].type==1) d_left=1000;

        }
        if(pinky.ghost_direction==1)
        {
            d_left=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[pinky.ghost_cell-maze_col].type==1) d_up=1000;
            if(cells[pinky.ghost_cell+1].type==1) d_right=1000;

        }
        if(pinky.ghost_direction==2)
        {
            d_up=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[pinky.ghost_cell+1].type==1) d_right=1000;
            if(cells[pinky.ghost_cell-1].type==1) d_left=1000;

        }
        if(pinky.ghost_direction==3)
        {
            d_right=1000;

            if(cells[pinky.ghost_cell+maze_col].type==1) d_down=1000;
            if(cells[pinky.ghost_cell-1].type==1) d_left=1000;
            if(cells[pinky.ghost_cell-maze_col].type==1) d_up=1000;

        }

        pinky.temp=(d_right<determine_smallest(d_left,d_up,d_down))?d_right:determine_smallest(d_left,d_up,d_down);

        if(pinky.temp==d_up)
        {
           pinky.ghost_direction=0;
        }
        else if(pinky.temp==d_down)
        {
            pinky.ghost_direction=2;
        }
        else if(pinky.temp==d_right)
        {
            pinky.ghost_direction=1;
        }
        else if(pinky.temp==d_left)
        {
            pinky.ghost_direction=3;
        }

        pinky.timer=10;
    }
        if(pinky.ghost_direction==0)
        {
            pinky.ghost_y+=pinky.speed;
            pinky.eaten_frame= 3;
        }
        else if(pinky.ghost_direction==1)
        {
            pinky.ghost_x+=pinky.speed;
            pinky.eaten_frame=1;
        }
        else if(pinky.ghost_direction==2)
        {
            pinky.ghost_y-=pinky.speed;
            pinky.eaten_frame= 4;
        }
        else if(pinky.ghost_direction==3)
        {
            pinky.ghost_x-=pinky.speed;
            pinky.eaten_frame= 2;
        }

        pinky.timer--;

        if(target_cell==pinky.ghost_cell)
            {
                pinky.retreat=0;
                pinky.fright=0;
                //pacman.power=0;
            }

    }
}


void collision()
{
    pinky.ghost_col= pinky.ghost_x/maze_row;
    pinky.ghost_row=pinky.ghost_y/maze_col;

    inky.ghost_col= inky.ghost_x/maze_row;
    inky.ghost_row= inky.ghost_y/maze_col;


    pacman.player_col = pacman.player_x/maze_row;
    pacman.player_row = pacman.player_y/maze_col;

    pinky.ghost_cell= (int)(pinky.ghost_x/wall_w)+(maze_row-(int)(pinky.ghost_y/wall_h))*maze_col;
    inky.ghost_cell= (int)(inky.ghost_x/wall_w)+(maze_row-(int)(inky.ghost_y/wall_h))*maze_col;
    pacman.player_cell= (int)pacman.player_x/wall_h + ((maze_row-(int)pacman.player_y/wall_h)*maze_col);

    //if(pacman.player_col==pinky.ghost_col && pacman.player_row==pinky.ghost_row)
    if((pinky.ghost_cell==pacman.player_cell || inky.ghost_cell==pacman.player_cell || blinky.ghost_cell==pacman.player_cell || clyde.ghost_cell==pacman.player_cell) && pacman.power==0 && pacman.invisible==0) //pacman.invisible==0
    {
        //printf("YO\n");
        pacman.collide=1;
        //user_interface.popup_timer=1;
        user_interface.pause=1;
        pacman.collide_x=pacman.player_x+maze_x;
        pacman.collide_y=pacman.player_y+maze_y;

        pacman.player_x=100;
        pacman.player_y=1000;
        PlaySound(0,0,0);
        PlaySound("pacman_death.wav",NULL,SND_ASYNC);
        pacman.lives--;
        iSetTimer(100,death_animation);



       //death_animation();

        if(pacman.lives==0)
            {
                user_interface.state=7;
            }
    }

    if(pacman.collide==2)
    {
        pacman.collide=0;
        pacman.player_x=21;
        pacman.player_y=20;
        user_interface.pause=0;
    }

    if(pinky.ghost_cell==pacman.player_cell && pacman.power==1 && pinky.fright==1)
    {

        pinky.retreat=1;
        pinky.scoring=1;
//         if(user_interface.collide_count==0)
//            pacman.score+=300;
//        if(user_interface.collide_count==1)
//            pacman.score+=500;
//            if(user_interface.collide_count==2)
//            pacman.score+=700;
//            if(user_interface.collide_count==3)
//            pacman.score+=1000;
        //pacman.score+=(200+((user_interface.collide_count+1)*100));
        user_interface.collide_count++;
        PlaySound(0,0,0);
        Sleep(1);
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);

        pinky_fright_mode();
        //printf("Yes\n");
    }

    if(inky.ghost_cell==pacman.player_cell && pacman.power==1 && inky.fright==1)
    {
        inky.retreat=1;
        inky.scoring=1;
//        if(user_interface.collide_count==0)
//            pacman.score+=300;
//        if(user_interface.collide_count==1)
//            pacman.score+=500;
//            if(user_interface.collide_count==2)
//            pacman.score+=700;
//            if(user_interface.collide_count==3)
//            pacman.score+=1000;

        PlaySound(0,0,0);
        Sleep(1);
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);

        inky_fright_mode();

        //printf("Yes\n");
    }

    if(blinky.ghost_cell==pacman.player_cell && pacman.power==1 && blinky.fright==1)
    {
        blinky.retreat=1;
        blinky.scoring=1;
//         if(user_interface.collide_count==0)
//            pacman.score+=300;
//        if(user_interface.collide_count==1)
//            pacman.score+=500;
//            if(user_interface.collide_count==2)
//            pacman.score+=700;
//            if(user_interface.collide_count==3)
//            pacman.score+=1000;
        //pacman.score+=(200+((user_interface.collide_count+1)*100));
        user_interface.collide_count++;
        PlaySound(0,0,0);
        Sleep(1);
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);

        blinky_fright_mode();

        //printf("Yes\n");
    }

    if(clyde.ghost_cell==pacman.player_cell && pacman.power==1 && clyde.fright==1)
    {
        clyde.retreat=1;
        clyde.scoring=1;
//         if(user_interface.collide_count==0)
//            pacman.score+=300;
//        if(user_interface.collide_count==1)
//            pacman.score+=500;
//            if(user_interface.collide_count==2)
//            pacman.score+=700;
//            if(user_interface.collide_count==3)
//            pacman.score+=1000;
        //pacman.score+=(200+((user_interface.collide_count+1)*100));
        user_interface.collide_count++;
        PlaySound(0,0,0);
        Sleep(1);
        PlaySound("pacman_eatghost.wav",NULL,SND_ASYNC);

        clyde_fright_mode();

        //printf("Yes\n");
    }

    if(pinky.scoring==1)
    {
        pacman.score+=200;
        pinky.scoring=0;
    }

    if(inky.scoring==1)
    {
        pacman.score+=200;
        inky.scoring=0;
    }

    if(blinky.scoring==1)
    {
        pacman.score+=200;
        blinky.scoring=0;
    }

    if(clyde.scoring==1)
    {
        pacman.score+=200;
        clyde.scoring=0;
    }



}

void ghost_all_moves()
{
    pacman_move();
    inky_move();
    pinky_move();
    blinky_move();
    clyde_move();
    pinky_short_move();
    inky_short_move();
    blinky_short_move();
    clyde_short_move();
    pinky_fright_mode();
    inky_fright_mode();
    blinky_fright_mode();
    high_scores_load();
    high_scores_save();
    collision();

}

void score_display()
{
    int x=pacman.score;
    int i=0,n=1,a[20];

    iShowBMP2(800,400,UI[18],0xFFFFFF);
    while(x!=0)
    {
        i++;
        a[i]=x%10;
        x=x/10;

    }

    while(n<=i)
    {
        iShowBMP2(1180-(n*20),415,scores[a[n]],0);
        n++;
    }
}

void player_lives()
{
    int y = pacman.lives;

    int i=0,p=1,highest=4;

    iShowBMP2(800,200,UI[19],0xFFFFFF);


    while(p<=y)
    {
        iShowBMP2(860+(p*70),200,life[0],0xFFFFFF);
        p++;
    }


}

void death_animation()
{
    if(pacman.collide==1)
    {
        death_index++;
    if(death_index>8)
        {
            death_index=0;
            pacman.collide=2;


        }
    //printf("%d",pacman.collide);
    }

}

void high_scores_save()
{
    int temp,i,j;
    char tump[50];
    if(user_interface.process==1)
    {
        strcpy(data[10].name,str);
        data[10].score=pacman.score;

        for(i=0;i<11-1;i++)
        {
            for(j=i+1;j<11;j++)
            {
                if(data[j].score>data[i].score)
                {
                    temp=data[j].score;
                    data[j].score=data[i].score;
                    data[i].score=temp;

                    strcpy(tump,data[j].name);
                    strcpy(data[j].name,data[i].name);
                    strcpy(data[i].name,tump);
                }
            }
        }



//    for(i=0;i<3;i++)
//    {
//        printf("%s\n",data[i].name);
//        printf("%d\n", data[i].score);
//

FILE *f_score_save;

f_score_save=fopen("high_scores.txt","rb+");
if(f_score_save==NULL)
    printf("NO NO NO\n");

    if(1!=fwrite(data,sizeof(struct Fame),10,f_score_save))
        printf("CONCUSION write\n");

    fclose(f_score_save);

        user_interface.process=0;
    }
}

void high_scores_load()
{
    if(user_interface.state==0 && user_interface.backup==1)
    {
        FILE *f_score_load;

f_score_load=fopen("high_scores.txt","rb+");
if(f_score_load==NULL)
    printf("NO NO NO\n");

    if(1!=fread(data,sizeof(struct Fame),10,f_score_load))
        printf("CONCUSION reading\n");

    fclose(f_score_load);


        for(int i=0;i<10;i++)
    {
        printf("%s  ",data[i].name);
        printf("%d\n", data[i].score);

    }

    user_interface.backup=0;
}
}

void save()
{
    FILE* f_pinky, *f_inky, *f_blinky,*f_clyde,*f_user, *f_player, *f_array;

    f_pinky=fopen("pinky.txt","rb+");
    f_inky=fopen("inky.txt","rb+");
    f_blinky=fopen("blinky.txt","rb+");
    f_clyde=fopen("clyde.txt","rb+");
    f_user=fopen("user.txt","rb+");
    f_player=fopen("player.txt","rb+");
    f_array=fopen("array.txt","rb+");


    //fout=fopen("status","rb");

    if(f_pinky==NULL)
        printf("Error\n");


    if(user_interface.load==1)
    {
        printf("YO r\n");

        if(1!=fread(&pinky,sizeof(struct Enemy),1,f_pinky))
    {
        printf("reading error\n");
    }
        if(1!=fread(&inky,sizeof(struct Enemy),1,f_inky))
    {
        printf("reading error\n");
    }
        if(1!=fread(&user_interface,sizeof(struct Enemy),1,f_user))
    {
        printf("reading error\n");
    }
         if(1!=fread(&pacman,sizeof(struct Enemy),1,f_user))
    {
        printf("reading error\n");
    }

    for(int i=0;i<maze_row;i++)
    {
        for(int j=0;j<maze_col;j++)
        {
            fread(&maze[i][j],sizeof(int),1,f_array);
        }
    }

//         if(1!=fread(&user_interface,sizeof(struct Enemy),1,f_user))
//    {
//        printf("reading error\n");
//    }
//         if(1!=fread(&user_interface,sizeof(struct Enemy),1,f_user))
//    {
//        printf("reading error\n");
//    }

    user_interface.state=1;
    }


     if(user_interface.save==1)
    {

        //printf("YO w\n");

        if(1!=fwrite(&pinky,sizeof(struct Enemy),1,f_pinky))
    {
        printf("writing error\n");
    }

        if(1!=fwrite(&inky,sizeof(struct Enemy),1,f_inky))
    {
        printf("writing error\n");
    }
        if(1!=fwrite(&user_interface,sizeof(struct Enemy),1,f_user))
    {
        printf("writing error\n");
    }
        if(1!=fwrite(&pacman,sizeof(struct Enemy),1,f_user))
    {
        printf("writing error\n");
    }

    for(int i=0;i<maze_row;i++)
    {
        for(int j=0;j<maze_col;j++)
        {
            fwrite(&maze[i][j],sizeof(int),1,f_array);
        }
    }

//        if(1!=fwrite(&user_interface,sizeof(struct Enemy),1,f_user))
//    {
//        printf("writing error\n");
//    }


    }


    fclose(f_pinky);
    fclose(f_inky);
    fclose(f_user);
    fclose(f_player);
    fclose(f_array);
}

void maze_edit()
{
    int i,j;
    if(user_interface.state==6 && user_interface.maze_edit==1)
    {
        iSetColor(12,52,200);
        iRectangle(maze_x,maze_y,maze_col*20,maze_row*20);


            //draw maze
            for(j=0;j<maze_col;j++)
            {
                iLine(maze_x+(j*20),maze_y,maze_x+(j*20),maze_y+(maze_row*20));
            }
            for(i=0;i<maze_row;i++)
            {
                iLine(maze_x,maze_y+(i*20),maze_x+(maze_col*20),maze_y+(i*20));
            }

            iSetColor(13,31,31);

        for(int i=0; i<maze_row; i++)
        {
            for(int j=0; j<maze_col; j++)
            {
                cells[i*maze_col+j].x=maze_x+j*wall_w;
                cells[i*maze_col+j].y=maze_y+maze_row*wall_h-(i+1)*wall_h;
                pacman.player_cell=(int)((pacman.player_x+pacman_w/2)/wall_w)+(maze_row-1-(int)((pacman.player_y+pacman_h/2)/wall_h))*maze_col;



                //for walls
                if(maze[i][j]==1)
                {
                    iPoint(cells[i*maze_col+j].x+10,cells[i*maze_col+j].y+10,2);
                    cells[i*maze_col+j].type=1;
                    iSetColor(230,0,0);
                    //iFilledRectangle(cells[i*maze_col+j].x,cells[i*maze_col+j].y,20,20);

                }

            }
        }


    }
}

void initialize()
{

    pacman.player_x=21+160;
    pacman.player_y=21+20*8;
    pacman.score=0;
    pacman.potion_red=1;
    pacman.lives=3;
    pacman.berry=1;
    pacman.straw=1;
    pacman.pear=1;

    pinky.ghost_x=81+(20*3)-120+30;
    pinky.ghost_y=21+20*8+100+40;
    pinky.ghost_h=18;
    pinky.ghost_w=18;
    pinky.speed=2;
    pinky.timer=4;
    pinky.ghost_direction=1;

    blinky.ghost_x=81+20*3-120+60+60+60+60+80;
    blinky.ghost_y=21+20*8+100+40;
    blinky.ghost_h=18;
    blinky.ghost_w=18;
    blinky.speed=2;
    blinky.timer=4;
    blinky.ghost_direction=1;

    clyde.ghost_x=121+120; //77+20*3+20;
    clyde.ghost_y=21;
    clyde.ghost_h=18;
    clyde.ghost_w=18;
    clyde.speed=2;
    clyde.timer=4;
    clyde.ghost_direction=1;

    inky.ghost_x=21;
    inky.ghost_y=21+60;
    inky.ghost_h=18;
    inky.ghost_w=18;
    inky.speed=2;
    inky.timer=4;
    inky.ghost_direction=1;


    user_interface.pause=1;
    //user_interface.wall_img_index=1;
    user_interface.backup=1;
    user_interface.dots=0;
    //user_interface.difficulty=1;
    user_interface.short_off_timer=1;
    user_interface.state=9;

}

int main()
{

//    for(int i=0;i<4;i++)
//    {
//        scanf("%s",data[i].name);
//        scanf("%d", &data[i].score);
//    }

//    iSetTimer(25,high_scores_load);
//    iSetTimer(25,high_scores_save);/


    initialize();
    user_interface.difficulty=1;
    user_interface.state=0;




    iSetTimer(25,save);






    if(user_interface.game_sound==1)
        //PlaySound("begin_theme.wav",NULL,SND_LOOP|SND_ASYNC);
        //Sleep(1);
    define_maze();


    //food();


    //if(user_interface.state==1)
    {
        //if(user_interface.pause==0)

        //if(user_interface.difficulty==3)
            //iSetTimer(25,pinky_short_move);
            //iSetTimer(25,inky_short_move);

//        if(user_interface.difficulty==1)
            //iSetTimer(25,pinky_move);
            //iSetTimer(25,inky_move);

            iSetTimer(25,ghost_all_moves);

        iSetTimer(150,death_animation);
        iSetTimer(1000,all_times);


    }
    //place your own initialization codes here.



    //iSetTimer(25,ghost_animation);


    iInitialize(Screen_W, Screen_H, "Pac-man!");
    return 0;
}


