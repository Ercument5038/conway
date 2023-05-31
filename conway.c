 	#include <c64.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define P_SCREEN0 ((unsigned char *)0x2000)
#define P_COLOR0  ((unsigned char *)0x0400)

#define P_SCREEN1 ((unsigned char *)0x6000)
#define P_COLOR1  ((unsigned char *)0x4400)

//HighRes Mode 300x200px
#define XMAX 40
#define YMAX 25
#define BOXSIZE 3
#define ROUNDS 100

void findNachbarn(int x, int y, int spielfeld[][YMAX], int nachbarn[][BOXSIZE]);
//void initSpielfeld(int spielfeld [][YMAX]);
void printSpielfeld(int spielfeld [][YMAX]);
int zaehlLebende(int nachbarn[][BOXSIZE]);
void pruefeRegeln(int x, int y,  int lebende, int temp[][YMAX], int spielfeld[][YMAX]);

//static const char array[XMAX][YMAX] 
const static int spielfeld[XMAX][YMAX]= {
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
};

//static int spielfeld[XMAX][YMAX];
static int temp[XMAX][YMAX];
static int nachbarn[BOXSIZE][BOXSIZE];

int main(void)
{
  clock_t       t;
  unsigned long sec;
  unsigned      sec10;
  unsigned long fps;
  unsigned      fps10;
  unsigned char background;
  unsigned char text;
        
	char x;
	char y;
	int lebende;
	char round = 0;

  t = clock ();
	//initSpielfeld(spielfeld);
  clrscr(); // clears screen and moves the cursor to the upper left corner of the screen
	background = bgcolor(COLOR_BLACK);
	text = textcolor(COLOR_RED);
	printSpielfeld(spielfeld);
//	signal (int sig, __sigfunc func);

// kbhit = keyboard press
// here optimize important (4-errora 15 sec)
	while(round < ROUNDS && !kbhit()){
		for(y = 0; y< YMAX; y++){
			for(x = 0; x< XMAX; x++){
				//gotoxy(0,0);
				//cprintf("%2d %2d",x , y);
				findNachbarn(x,y,spielfeld,nachbarn);
				lebende = zaehlLebende(nachbarn);
				//gotoxy(x,y);
				//cprintf("%d",lebende);
				pruefeRegeln(x,y,lebende , temp, spielfeld);
			}// for x
		}// for y

		memcpy(spielfeld,temp,2000); // kopiert die neuen lebende auf das spielfeld array, XMAX * YMAX gibt die number of bytes to be copied an
	
		round++;
		printSpielfeld(spielfeld);	
	}
		t = clock() - t;
	
  /* Reset screen colors */
    bgcolor (background);
    textcolor (text);
    clrscr ();

    /* Calculate stats */
    sec   = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec  /= 10;
    fps   = (round * (CLK_TCK * 10)) / t;
    fps10 = fps % 10;
    fps  /= 10;

    /* Output stats */
    gotoxy (0, 0); cprintf ("time  : %lu.%us", sec, sec10);
    gotoxy (0, 1); cprintf ("frames: %lu", round);
    gotoxy (0, 2); cprintf ("fps   : %lu.%u", fps, fps10);

    /* Wait for a key, then end */
    cputsxy (0, 4, "Press any key when done...");
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;
}



void pruefeRegeln(int x, int y,  int lebende, int temp[][YMAX], int spielfeld[][YMAX]){
	//hier kommen meine regeln
	
	if(spielfeld[x][y] == 0 )
	{
		if(lebende == 3)
			temp[x][y] = 1;	
	}
	if(spielfeld[x][y] == 1)
	{
		if(lebende == 2)
			temp[x][y] = 1;
	
		if(lebende == 3)
			temp[x][y] = 1;

		if(lebende < 2)
			temp[x][y] = 0;	

		if(lebende > 3)				
			temp[x][y] = 0;
	}
}


int zaehlLebende(int nachbarn[][BOXSIZE]){
	
	
	/*
	char iy, ix, flag;
	for(iy= 0; iy < BOXSIZE ; iy++){
		for(ix = 0; ix < BOXSIZE; ix++){
			//prüfe dass wir nicht auf unserer eigneen position sind
			
		  flag = 21 ;
			
			if(ix != 1){
			flag += 7;
			}
			if(iy != 7){
			flag +=2;
			}
			if(flag > 21){
				lebende += nachbarn[ix][iy] * 7;
			}
		}//for ix
	}//for iy	
	*/
	char lebende = 0;

	lebende += nachbarn[0][0];
	lebende += nachbarn[1][0];
	lebende += nachbarn[2][0];
	lebende += nachbarn[0][1];
	lebende += nachbarn[1][1];
	lebende += nachbarn[2][1];
	lebende += nachbarn[0][2];
	lebende += nachbarn[1][2];
	lebende += nachbarn[2][2];

	return lebende;
}

void findNachbarn(int x, int y, int spielfeld[][YMAX], int nachbarn[][BOXSIZE]){
	//gehe über alle nachbarn
	/*
	signed char osx, ix;
	signed char osy, iy; 
	signed char ofy;
	signed char ofx;
	
	for(ofy = y-1, iy=0; ofy <= (signed char)y+1; ++ofy , ++iy){
		for(ofx = x-1,ix = 0; ofx <= (signed char)x+1; ++ofx , ++ix){
	
			if( ofy < 0)	
			{
				osy = YMAX-1;
			}
			else if( ofy > YMAX-1)	
			{
				osy = 0;
			}
			else 
			{
				osy = ofy;
			}
			
			if( ofx < 0)	
			{
				osx = XMAX-1;
			} 
			else if( ofx > XMAX-1)	
			{
				osx = 0;
			}
			else 
			{
				osx = ofx;
			}
		  
			nachbarn[ix][iy] = spielfeld[osx][osy];			
		}//for ofx
	}//for ofy
	*/
	unsigned char osx, ix, dx;
    unsigned char osy, iy, dy;

	signed char ofx, ofy;

    for (dy = 0; dy < BOXSIZE; ++dy) 
	{
        ofy = y - 1 + dy;
        osy = (ofy < 0) ? YMAX - 1 : (ofy >= YMAX) ? 0 : ofy;

        for (dx = 0; dx < BOXSIZE; ++dx) 
		{
            ofx = x - 1 + dx;
            osx = (ofx < 0) ? XMAX - 1 : (ofx >= XMAX) ? 0 : ofx;
            nachbarn[dx][dy] = spielfeld[osx][osy];
        }
    }
}

void printSpielfeld(int spielfeld [][YMAX]){
	char x,y;
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
			if(spielfeld[x][y] == 1){
				revers(1);
			} else{ // hier muss noch optimiert werden
				revers(0);
			}		
 			cputcxy (x, y, 32); // moves the cursor to the given x/y position on the screen and outputs one character.
		}
	}
}

//void initSpielfeld(int spielfeld [][YMAX]){
	//char x,y;
	//fülle das feld mit zufallswerten und gibs aus
	/*
	for(y = 0; y< YMAX; y++){
		for(x = 0; x< XMAX; x++){
				spielfeld[x][y] = array[x][y];
		}
	}
	
}
*/
