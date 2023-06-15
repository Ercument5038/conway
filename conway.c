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
#define ROUNDS 120

//Void findNachbarn(unsigned char x, unsigned char y);
//void initSpielfeld(int spielfeld [][YMAX]);
//void printSpielfeld();
//unsigned char zaehlLebende();
//void pruefeRegeln(unsigned char x, unsigned char y, unsigned char lebende);

//static const char array[XMAX][YMAX] 
const static unsigned short spielfeld[XMAX][YMAX]= {
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
static unsigned short temp[XMAX][YMAX];
//static unsigned char nachbarn[BOXSIZE][BOXSIZE];

int main(void)
{
	clock_t       t;
	unsigned long sec;
	unsigned      sec10;
	unsigned long fps;
	unsigned      fps10;
	unsigned char background;
	unsigned char text;
	
	unsigned char lebende;
	signed char up;
	signed char down;
	signed char right;
	signed char left;
	unsigned char x;
	unsigned char y;
	unsigned char round = 0;
	unsigned char i, j;

  
	//initSpielfeld(spielfeld);
  clrscr(); // clears screen and moves the cursor to the upper left corner of the screen
	background = bgcolor(COLOR_WHITE);
	text = textcolor(COLOR_RED);
	t = clock ();
	//printSpielfeld();
	for (i = 0; i < YMAX; i++) 
	{
        for (j = 0; j < XMAX; j++) 
		{
            revers(spielfeld[j][i]); // Use the value directly as the argument for revers()
            cputcxy(j, i, 32);
        }
    }

	while(round < ROUNDS && !kbhit())
	{
		
		for(y = 0; y< YMAX; y++){
			for(x = 0; x< XMAX; x++){
				//findNachbarn(x,y);

				up = y - 1;
				down = y + 1;
				right = x + 1;
				left = x - 1;

				if (up < 0)
				{
					up = 24;
				}
				else if (down > 24)
				{
					down = 0;
				}

				if (left < 0)
				{
					left = 39;
				}
				else if (right > 39)
				{
					right = 0;
				}



				//lebende = zaehlLebende();
				lebende = 0;
				lebende += spielfeld[left][up];
				lebende += spielfeld[x][up];
				lebende += spielfeld[right][up];
				
				lebende += spielfeld[left][y];
				lebende += spielfeld[right][y];
				
				lebende += spielfeld[left][down];
				lebende += spielfeld[x][down];
				lebende += spielfeld[right][down];
				

				//pruefeRegeln(x,y,lebende);
				
				
				switch(lebende)
				{
					case 2: temp[x][y] = spielfeld[x][y];
					break;
					case 3: temp[x][y] = 1;
					break;
					default: temp[x][y] = 0;
					break;
				}
			}// for x
		}// for y

		memmove(spielfeld,temp,2000); // kopiert die neuen lebende auf das spielfeld array, XMAX * YMAX gibt die number of bytes to be copied an
	
		round++;
		//printSpielfeld();
		
		for (i = 0; i < YMAX; i++) 
		{
			for (j = 0; j < XMAX; j++) 
			{
				revers(spielfeld[j][i]); // Use the value directly as the argument for revers()
				cputcxy(j, i, 32);
			}	
	    }
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


/*
void pruefeRegeln(unsigned char x, unsigned char y, unsigned char lebende){
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
*/
/*
unsigned char zaehlLebende(){
	unsigned char lebende = 0;
	// lebende global machen
	lebende += nachbarn[0][0];
	lebende += nachbarn[1][0];
	lebende += nachbarn[2][0];
	lebende += nachbarn[0][1];
	//lebende += nachbarn[1][1];
	lebende += nachbarn[2][1];
	lebende += nachbarn[0][2];
	lebende += nachbarn[1][2];
	lebende += nachbarn[2][2];

	return lebende;
}
*//*
void findNachbarn(unsigned char x, unsigned char y)
{
	if( y - 1 < 0){
		y = YMAX-1;
    }
    else if( y > YMAX-1){
		y = 0;
    }
    else{
        y = y;
    }    
    if( x - 1 < 0){
		x = XMAX-1;
    } 
    else if( x > XMAX-1){
        x = 0;
    }
    else{
        x = x;
    }
	
	if (y-1 < 0)
	{
		y =	YMAX - 1;
	}
	if(y+1 > YMAX -1)
	{
		y = 0;
	}
	if(x-1<0){
		x = XMAX -1;
	}
	if(x+1 > XMAX -1)
	{
		x = 0;
	}

	nachbarn[0][0] = spielfeld[x - 1][y - 1];
    nachbarn[0][1] = spielfeld[x][y - 1];
    nachbarn[0][2] = spielfeld[x + 1][y - 1];

    nachbarn[1][0] = spielfeld[x - 1][y];
    nachbarn[1][2] = spielfeld[x + 1][y];

    nachbarn[2][0] = spielfeld[x - 1][y + 1];
    nachbarn[2][1] = spielfeld[x][y + 1];
    nachbarn[2][2] = spielfeld[x + 1][y + 1];

}
*//*
void printSpielfeld() {
    
    
}
*/