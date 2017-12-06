/*****************************************************************************
* 
* This file contains the utility routines for words manipulations.
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
   04-Aug-2006  Gaurav Jain      Fixed segmentation fault in 
                                 word_cmp() occuring in case of 
                                 0-length words.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include <time.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Routine to compare two words
*
*****************************************************************************/
int word_strcmp(char *string1, char *string2)
{
    int alphalen1, alphalen2;
    int preflen1, preflen2;
    int retval;
    char *alphastr1 = NULL, *alphastr2 = NULL;

    alphastr1 = word_get_first_alpha_ptr(string1);
    alphastr2 = word_get_first_alpha_ptr(string2);

    if (alphastr1 == NULL || alphastr2 == NULL)
        return -1;

    alphalen1 = strlen(alphastr1);
    alphalen2 = strlen(alphastr2);

    preflen1 = alphastr1 - string1;
    preflen2 = alphastr2 - string2;

    retval = strncasecmp(alphastr1, alphastr2, strlen(alphastr2));
    if (retval == 0)
    {
        if (alphalen1 == alphalen2)
        {
            return (preflen2 - preflen1);
        }
        else
        {
            return (alphalen1 - alphalen2);
        }
    }

    return retval;
}

/*****************************************************************************
* 
* Routine to generate a random number
*
*****************************************************************************/
int word_random(int low, int high)
{
    int i, j;
    static int seed1 = 0;
    static int seed2 = 0;
    seed1 = (seed1 + 13)%231;
    seed2 = (seed2 + 7)%113;
    srand(time(NULL) + seed1 + seed2 );
    i = rand();

    j = (i%(high - low + 1)) + low;

    return j;
}

/*****************************************************************************
* 
* Routine to get a character from input
*
*****************************************************************************/
char word_getchar(void)
{
    char choice_str[20];
    char choice;
    while (1)
    {
        scanw(" %[^\n]", choice_str);
        if (strlen(choice_str) > 1)
        {
            printw("\nInvalid Input...Try again:");
        }
        else
        {
            choice = choice_str[0];
            return choice;
        }
    }
}

/*****************************************************************************
* 
* Routine to exit from an error condition
*
*****************************************************************************/
void error_exit(char *error_str)
{
    int lastrow, lastcol;
    char log_cmd[200];
    char log_file[100];

    clear();
    print_screen(ERROR_SCREEN);
    if (getenv("VOCAB_PLUS_BASE_DIR") != NULL)
    {
        strcpy(log_file, getenv("VOCAB_PLUS_BASE_DIR"));
        strcat(log_file, "/error_log");
    }
    else
    {
        strcpy(log_file, "error_log");
    }
    sprintf(log_cmd, "echo `date`: %s\n >> %s", error_str, log_file);
    getmaxyx(stdscr, lastrow, lastcol);
    attron(COLOR_PAIR(1));
    mvprintw(lastrow - 2, 0, "%s Aborting...\n", error_str);
    mvprintw(lastrow - 1, 0, "See Error log file '%s'\n", log_file);
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
    clear();
    exit(0);
}

/*****************************************************************************
* 
* Routine to return the first valid alphabet in the word
*
*****************************************************************************/
char word_get_first_alpha(char *word_name)
{
    char *temp_ptr = word_name;

    while (*temp_ptr)
    {
        if (isalpha(*temp_ptr))
        {
            return tolower(*temp_ptr);
        }
        temp_ptr ++;
    }
    return 0;
}

/*****************************************************************************
* 
* Routine to return the first valid alphabet ptr in the word
*
*****************************************************************************/
char *word_get_first_alpha_ptr(char *word_name)
{
    char *temp_ptr = word_name;

    while (*temp_ptr)
    {
        if (isalpha(*temp_ptr))
        {
            return temp_ptr;
        }
        temp_ptr ++;
    }
    return 0;
}
