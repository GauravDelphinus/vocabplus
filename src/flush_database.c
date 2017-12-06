/*****************************************************************************
* 
* This file contains the routines for flushing the database to disk.
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
#include <signal.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Routine to flush the database to disk
*
*****************************************************************************/
void flush_database(void)
{
    FILE *p_output_file = NULL;
    struct word_node *p_temp_node = NULL;
    char word_type[20];
    char alpha = 'a';
    int i = 0;
    char output_file[100], ftp_put_script[100];
    char error_str[150];

    printw("Flushing database to disk...");
    strcpy(output_file, getenv("VOCAB_PLUS_BASE_DIR"));
    strcat(output_file, "/word.db");
    p_output_file = fopen(output_file, "w");
    if (NULL == p_output_file)
    {
        sprintf(error_str, "Could not open output file '%s' for writing.", output_file);
        error_exit(error_str);
    }

    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            if (alpha >= 'z')
            {
                /* Done all */
                break;
            }
            else
            {
                alpha ++;
                p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
                continue;
            }
        }
        /* Something to print */
        switch (p_temp_node->p_word->word_type)
        {
            case WORD_TYPE_ADJ:
                strcpy(word_type, "adjective");
                break;
            case WORD_TYPE_VERB:
                strcpy(word_type, "verb");
                break;
            case WORD_TYPE_NOUN:
                strcpy(word_type, "noun");
                break;
            case WORD_TYPE_ROOT:
                strcpy(word_type, "root");
                break;
            case WORD_TYPE_PERSON:
                strcpy(word_type, "person");
                break;
            case WORD_TYPE_THING:
                strcpy(word_type, "thing");
                break;
            default:
                strcpy(word_type, "other");
                break;
        }
        fprintf(p_output_file, "%s\t%s\t%d\t%d\t%s\t%s\n",
                p_temp_node->p_word->word_name,
                word_type, p_temp_node->p_word->word_hits,
                p_temp_node->p_word->word_age,
                p_temp_node->p_word->word_meaning,
		p_temp_node->p_word->word_example);
        i++;
        p_temp_node = p_temp_node->p_next;
    }
    fclose(p_output_file);
    printw("DONE\n");

    /* Check if the db needs to be written to a FTP location */
    printw("Uploading database to FTP site...");
    strcpy(ftp_put_script, getenv("VOCAB_PLUS_BASE_DIR"));
    strcat(ftp_put_script, "/ftp_put.sh");
    system(ftp_put_script);
    printw("DONE\n");
}

/*****************************************************************************
* 
* Routine to perform shutdown activities
*
*****************************************************************************/
void shut_down(void)
{
    int i;
    int lastrow, lastcol;
    struct word_node *p_temp_node = NULL;
    struct word_node *p_next_node = NULL;

    /* Flush database to disk */
    flush_database();

    printw("Freeing word databases from memory...");
    /* Free off the alphabet array */
    for (i = 0; i < 26; i++)
    {
        /* Free the list of nodes on this alphabet index */
        p_temp_node = alphabet_array[i]->p_head_word_node;
        while (p_temp_node != NULL)
        {
            free(p_temp_node->p_word->word_name);
            p_temp_node->p_word->word_name = NULL;

            free(p_temp_node->p_word->word_meaning);
            p_temp_node->p_word->word_meaning = NULL;

            free(p_temp_node->p_word->word_example);
            p_temp_node->p_word->word_example = NULL;

            free(p_temp_node->p_word);
            p_temp_node->p_word = NULL;

            p_next_node = p_temp_node->p_next;
            free(p_temp_node);
            p_temp_node = p_next_node;
        }
        /* Now free the alphabet array node itself */
        free(alphabet_array[i]);
        alphabet_array[i] = NULL;
    }
    printw("DONE\n");

    /* Set up to ignore the alarms time ticks any longer */
    signal(SIGALRM, SIG_IGN);

    clear();
    print_screen(GOODBYE_SCREEN);
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "");
    getch();
    endwin();
    clear();
    exit(0);
}
