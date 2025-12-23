#include <ncurses.h>
using namespace std;

// g++ <program file> -lncurses -o <output file name>


void boxAround(int y, int x, int h, int w) {
    move (y, x);
    addch(ACS_ULCORNER);
  //   int j;
  //   for (j = 0; j < w; ++j) {
  //       addch(ACS_URCORNER);
  //   }
  // for( j = 0; j < h; ++j ) {
  //           move(  y+1+j, x );
  //           addch (ACS_VLINE);
  //           move( y+1+j, x+w+1 );
  //           addch (ACS_VLINE);
  //   }
  //
  //   move( y+h+1,x );
  //   addch (ACS_LLCORNER);   // lower left corner
  //
  //   for (j = 0;  j < w;  ++j)
  //       addch (ACS_HLINE);
  //   addch (ACS_LRCORNER);   // lower right

}
int main(int argc, char ** argv)
{
    initscr();			/* Start curses mode 		  */
    while (1) {

    boxAround(0,0 , 10, 10);

	refresh();			/* Print it on to the real screen */
    //refresh, so when we write printw, the data is actyally writetten to an imaginary window, which is not updated on the screen yet, the job of printw is to update a few flags and data structures and write the data to a buffer corresponding to stdscr
    //in order to show it on screen we need to call refresh()
    }
    //initscr
	endwin();			/* End curses mode		  */

	return 0; 
}
