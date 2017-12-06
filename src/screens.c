/*****************************************************************************
* 
* This file contains the screens used by the program.
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
   03-Oct-2003  Gaurav Jain      Fixed screen alignment for vocab test
   06-Sep-2003  Gaurav Jain      Initial Version
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Print the different screens
*
*****************************************************************************/
void print_screen(int screen_type)
{
    int lastrow, lastcol, startrow, startcol;
    getmaxyx(stdscr, lastrow, lastcol);
    startcol = (lastcol - 63)/2;
    startrow = (lastrow - 19)/2 - 1;

    attron(A_BOLD);
    attron(COLOR_PAIR(7));
    mvprintw(startrow++, startcol, "_________________________________________________________________\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attron(COLOR_PAIR(6));
    if (screen_type == WELCOME_SCREEN)
    {
        printw("                          Welcome To                           ");
    }
    else if (screen_type == ABOUT_SCREEN)
    {
        printw("                         You are using                         ");
    }
    else if (screen_type == GOODBYE_SCREEN)
    {
        printw("                         Good Bye from                         ");
    }
    else if (screen_type == HELP_SCREEN)
    {
        printw("                           Need Help?                          ");
    }
    else if (screen_type == ERROR_SCREEN)
    {
        printw("                       Error encountered                       ");
    }
    else if (screen_type == WARRANTY_SCREEN)
    {
        printw("                       Warranty Statement                      ");
    }
    attroff(COLOR_PAIR(6));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("         _    _                        _                       ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("         |    |   ___     ___    ____  |___        |           ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("         |    |  /   \\   /   \\  /   |  |   \\       |           ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(1));
    printw("         \\    / |     | |      |    |  |    |  ----+----       ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(4));
    printw("          \\  /  |     | |      |    |  |    |      |           ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(4));
    printw("           \\/    \\___/   \\___/  \\__/ \\ |___/       |           ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(7));
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(3));
    attroff(A_BOLD);
    printw("                          Revision 0.3                         ");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(5));
    attroff(A_BOLD);
    printw("            COPYRIGHT (c) 2003 - 2006,  GAURAV JAIN            ");
    attron(A_BOLD);
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");
    mvprintw(startrow++, startcol, "|                                                               |\n");
    if (screen_type == HELP_SCREEN)
    {
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(6));
    attroff(A_BOLD);
    printw("              http://software.gauravjain.in/vocabplus          ");
    attron(A_BOLD);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(7));
    printw("|\n");
    }
    else if ((screen_type == WARRANTY_SCREEN) || (screen_type ==
                WELCOME_SCREEN))
    {
    mvprintw(startrow++, startcol, "|");
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);
    attron(COLOR_PAIR(2));
    printw(" Vocab+ is protected under the ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(3));
    attron(A_BOLD);
    printw(" GNU General Public License     ");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" and comes with ABSOLUTELY NO WARRANTY. This is free software  ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" and you are free to redistribute it under certain conditions. ");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    attron(A_BOLD);
    printw("|\n");

    mvprintw(startrow++, startcol, "|");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(2));
    printw(" See the GNU General Public License for more details.          ");
    attron(A_BOLD);
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(7));
    printw("|\n");
    }
#if 0
    mvprintw(startrow++, startcol, "|                                                             |\n");
#endif
    mvprintw(startrow++, startcol, "|_______________________________________________________________|\n");
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);
}

/*****************************************************************************
* 
* Routine to print the title at each screen
*
*****************************************************************************/
void print_title(char *title)
{
    print_time_spent();

    move(1, 0);
    attron(COLOR_PAIR(6));
    printw("________________________________");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("  ____________________________________________\n");
    attroff(COLOR_PAIR(4));
    printw("    ");
    attron(COLOR_PAIR(7));
    printw("%-20s        ", title);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(6));
    printw("\\ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("\\___________________________________________\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("________________________________/ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("/___________________________________________\n");
    attroff(COLOR_PAIR(4));
}

/*****************************************************************************
* 
* Routine to print the subtitle at each screen
*
*****************************************************************************/
void print_subtitle(char *title)
{
    print_time_spent();

    move(1, 0);
    attron(COLOR_PAIR(6));
    printw("____________________________________________________");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("  ________________________\n");
    attroff(COLOR_PAIR(4));
    printw("    ");
    attron(COLOR_PAIR(7));
    printw("%-48s", title);
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(6));
    printw("\\ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("\\_______________________\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("____________________________________________________/ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("/_______________________\n");
    attroff(COLOR_PAIR(4));
}

/*****************************************************************************
* 
* Routine to print the title for word being displayed
*
*****************************************************************************/
void print_wordtitle(int type)
{
    if (PRINT_FORMAT_SHORT == type)
    {
        attron(COLOR_PAIR(6));
        printw("\nNo. ");
        attroff(COLOR_PAIR(6));
        printw("Word                 ");
        attron(COLOR_PAIR(5));
        printw("Type\n");
        attroff(COLOR_PAIR(5));

        attron(COLOR_PAIR(6));
        printw("____");
        attroff(COLOR_PAIR(6));
        printw("_____________________");
        attron(COLOR_PAIR(5));
        printw("_______\n\n");
        attroff(COLOR_PAIR(5));
    }
    else
    {
        attron(COLOR_PAIR(6));
        printw("\n No.  ");
        attroff(COLOR_PAIR(6));
        printw("Word                 ");
        attron(COLOR_PAIR(5));
        printw("Type  ");
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(4));
        printw("Level ");
        attroff(COLOR_PAIR(4));
        printw("Meaning\n");

        attron(COLOR_PAIR(6));
        printw("______");
        attroff(COLOR_PAIR(6));
        printw("_____________________");
        attron(COLOR_PAIR(5));
        printw("______");
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(4));
        printw("_____");
        attroff(COLOR_PAIR(4));
        printw("________________________________________\n\n");
    }
}

/*****************************************************************************
* 
* Routine to print title for the test screens
*
*****************************************************************************/
void print_testtitle(int serial_no, int pass, int fail)
{
    char score_str[15];

    print_time_spent();

    move(1, 0);
    attron(COLOR_PAIR(6));
    printw("______________________________________________________________");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("  _________\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("                                                              \\ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("\\  \n");
    printw("    ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    printw("Test No.");
    printw("%-5d", serial_no);
    sprintf(score_str, "%d/%d", pass, (pass + fail));
    attroff(COLOR_PAIR(3));
    if (serial_no > 1)
    {
        attron(COLOR_PAIR(5));
        printw("      Current Score: %-9s   ", score_str);
        attroff(COLOR_PAIR(5));
        attron(COLOR_PAIR(2));
        printw(" %7.2f%%    ", (pass * 100.0/(pass + fail)));
        attroff(COLOR_PAIR(2));
    }
    else
    {
        attron(COLOR_PAIR(5));
        printw("      Current Score: 0/0                      ");
        attroff(COLOR_PAIR(5));
    }
    attron(COLOR_PAIR(6));
    printw("\\ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("\\_______\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("                                                               / ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("/ \n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("______________________________________________________________/ ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("/________\n");
    attroff(COLOR_PAIR(4));
}

/*****************************************************************************
* 
* Routine to print the time spend using Vocab+
*
*****************************************************************************/
void print_time_spent()
{
    int prev_x = 0, prev_y = 0;  /* saved coordinates */

    int curr_hrs = 0;
    int curr_mins = 0;
    int curr_secs = 0;
    int temp_mod = 0;

    /* Calculate the current hrs, mins and secs */
    curr_hrs = curr_time/3600;
    temp_mod = curr_time % 3600;
    curr_mins = (temp_mod)/60;
    curr_secs = (temp_mod)%60;

    getyx(stdscr, prev_y, prev_x);
    move(0, 0);
    attron(COLOR_PAIR(2));
    printw("[");
    attroff(COLOR_PAIR(2));
    printw("Time Spent:");
    printw(" %.2d:%.2d:%.2d", curr_hrs, curr_mins, curr_secs);
    attron(COLOR_PAIR(2));
    printw("]");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(2));
    mvprintw(0, 65, "[");
    attroff(COLOR_PAIR(2));
    printw("Vocab+ ");
    printw("0.3");
    attron(COLOR_PAIR(2));
    printw("]");
    attroff(COLOR_PAIR(2));
    move(prev_y, prev_x);

    refresh();
}
