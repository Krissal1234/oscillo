#include <ncurses.h>

#include <string.h>
using namespace std;

// g++ <program file> -lncurses -o <output file name>


int main(int argc, char ** argv)
{
    char mesg[7] = "string";
    int row, col;
    initscr();			/* Start curses mode 		  */

    getmaxyx(stdscr, row, col);
    // mvprintw(row/2, (col-3)/2, "%s", '#');
    char hash = '#';
    char* t = &hash;

    // mvprintw(row-2,0,"This screen has %d rows and %d columns \n", row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == row - 1 && j == col - 1) continue;
            mvaddch(i, j, '#');
        }
    }

        
    refresh();
    // getch();
    
	// endwin();			/* End curses mode		  */

	return 0; 
}
