/*****************************************************************************
* 
* This source file is the main file of the system, and the entry point.
*
*****************************************************************************/
/*****************************************************************************
    Copyright (C) 2003 Gaurav Jain

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*****************************************************************************/
/*****************************************************************************
   Revision History

   Date         Updater          Comment
   06-Sep-2003  Gaurav Jain      Initial Version
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Main routine for the software (entry point)
*
*****************************************************************************/
int main()
{
    int i;
    int lastrow, lastcol;
    /* Initialize curses screen */
    initscr();
    start_color();

    /* Initialize color pairs */
    for (i = 1; i < COLORS; i++)
    {
        init_pair(i, i, COLOR_BLACK);
    }

    /* Welcome screen */
    print_screen(WELCOME_SCREEN);
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();

    clear();
    /* Going to load data base to memory */
//    printw("Loading word databases to memory...");

    /* Load database */
    load_database();
 //   printw("DONE\n");

    /* Start an alarm to timeout after 1 second */
    signal(SIGALRM, catch_time_tick);
    alarm(1);

    /* Execute main loop */
    main_loop();

    return 0;
}
