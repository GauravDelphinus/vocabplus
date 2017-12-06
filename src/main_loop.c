/*****************************************************************************
* 
* This file contains the main loop for the program.
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
#include <fcntl.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Routine that runs in loop with the Main Menu
*
*****************************************************************************/
void main_loop(void)
{
    int choice;
    int lastrow, lastcol;
    int error = 0;
    int retval;
    char file_name[100];
    char cmd_str[150];
    struct stat file_stat;

    while (1)
    {
        clear();
        print_title("MAIN MENU");
        attron(COLOR_PAIR(6));
        printw("\n0) ");
        attroff(COLOR_PAIR(6));
        printw("Exit\n");
        attron(COLOR_PAIR(6));
        printw("1) ");
        attroff(COLOR_PAIR(6));
        printw("Add Words\n");
        attron(COLOR_PAIR(6));
        printw("2) ");
        attroff(COLOR_PAIR(6));
        printw("View Words\n");
        attron(COLOR_PAIR(6));
        printw("3) ");
        attroff(COLOR_PAIR(6));
        printw("Edit Words\n");
        attron(COLOR_PAIR(6));
        printw("4) ");
        attroff(COLOR_PAIR(6));
        printw("Delete Words\n");
        attron(COLOR_PAIR(6));
        printw("5) ");
        attroff(COLOR_PAIR(6));
        printw("Take Vocab Test\n");
        attron(COLOR_PAIR(6));
        printw("6) ");
        attroff(COLOR_PAIR(6));
        printw("Flush Current Data to Disk\n");
        attron(COLOR_PAIR(6));
        printw("7) ");
        attroff(COLOR_PAIR(6));
        printw("About\n");
        attron(COLOR_PAIR(6));
        printw("8) ");
        attroff(COLOR_PAIR(6));
        printw("Help\n");
        attron(COLOR_PAIR(6));
        printw("9) ");
        attroff(COLOR_PAIR(6));
        attroff(COLOR_PAIR(6));
        printw("Warranty\n");
        choice = getch() - '0';
        switch (choice)
        {
            case 0:
                shut_down();
                break;
            case 1:
                add_words();
                break;
            case 2:
                view_words();
                break;
            case 3:
                edit_words();
                break;
            case 4:
                delete_words();
                break;
            case 5:
                vocab_test();
                break;
            case 6:
                flush_database();
                break;
            case 7:
                clear();
                print_screen(ABOUT_SCREEN);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                error = 0;
                strcpy(file_name, getenv("VOCAB_PLUS_BASE_DIR"));
                sprintf(cmd_str, "vi %s/readme.txt 2> %s/.tmp", file_name,
                        file_name);
                retval = system(cmd_str);
                if (retval == -1)
                {
                    error = 1;
                }
                if (error == 1)
                {
                    clear();
                    print_screen(ABOUT_SCREEN);
                    getmaxyx(stdscr, lastrow, lastcol);
                    attron(COLOR_PAIR(1));
                    mvprintw(lastrow - 3, 0, "Error encountered while trying to read 'readme' file.\n");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                }
                else
                {
                    strcpy(cmd_str, file_name);
                    strcat(cmd_str, "/.tmp");
                    stat(cmd_str, &file_stat);
                    if (file_stat.st_size > 0)
                    {
                        sprintf(cmd_str, "echo `date` : `cat %s/.tmp` >> %s/error_log", file_name, file_name);
                        system(cmd_str);
                    }
                }
                break;
            case 8:
                clear();
                print_screen(HELP_SCREEN);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                error = 0;
                strcpy(file_name, getenv("VOCAB_PLUS_BASE_DIR"));
                sprintf(cmd_str, "vi %s/help.txt 2> %s/.tmp", file_name,
                        file_name);
                retval = system(cmd_str);
                if (retval == -1)
                {
                    error = 1;
                }
                if (error == 1)
                {
                    clear();
                    print_screen(HELP_SCREEN);
                    getmaxyx(stdscr, lastrow, lastcol);
                    attron(COLOR_PAIR(1));
                    mvprintw(lastrow - 3, 0, "Error encountered while trying to read 'help.txt' file.\n");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                }
                else
                {
                    strcpy(cmd_str, file_name);
                    strcat(cmd_str, "/.tmp");
                    stat(cmd_str, &file_stat);
                    if (file_stat.st_size > 0)
                    {
                        sprintf(cmd_str, "echo `date` : `cat %s/.tmp` >> %s/error_log", file_name, file_name);
                        system(cmd_str);
                    }
                }
                break;
            case 9:
                clear();
                print_screen(WARRANTY_SCREEN);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                error = 0;
                strcpy(file_name, getenv("VOCAB_PLUS_BASE_DIR"));
                sprintf(cmd_str, "vi %s/gpl.txt 2> %s/.tmp", file_name,
                        file_name);
                retval = system(cmd_str);
                if (retval == -1)
                {
                    error = 1;
                }
                if (error == 1)
                {
                    clear();
                    print_screen(WARRANTY_SCREEN);
                    getmaxyx(stdscr, lastrow, lastcol);
                    attron(COLOR_PAIR(1));
                    mvprintw(lastrow - 3, 0, "Error encountered while trying to read 'readme.txt' file.\n");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                }
                else
                {
                    strcpy(cmd_str, file_name);
                    strcat(cmd_str, "/.tmp");
                    stat(cmd_str, &file_stat);
                    if (file_stat.st_size > 0)
                    {
                        sprintf(cmd_str, "echo `date` : `cat %s/.tmp` >> %s/error_log", file_name, file_name);
                        system(cmd_str);
                    }
                }
                break;
            default:
                printw("Invalid Choice...\n");
                break;
        }
    }
}

/*****************************************************************************
* 
* Routine that catches the alarm after every second
*
*****************************************************************************/
void catch_time_tick()
{
    curr_time ++;

    print_time_spent();

    signal(SIGALRM, catch_time_tick);
    alarm(1);
}
