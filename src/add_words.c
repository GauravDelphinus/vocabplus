/*****************************************************************************
* 
* This file contains the routines for adding new words to the database.
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
   04-Aug-2006  Gaurav Jain      Increased max word size limit
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
* Main routine for adding words to the database
*
*****************************************************************************/
void add_words(void)
{
    char word[50];
    char word_meaning[700];
    char word_example[700];
    struct word_node *p_node = NULL;
    int word_type_array[WORD_TYPE_MAX];
    int i = 0, j = 0;
    int word_type_choice;
    char choice;
    int lastrow, lastcol;
    int row, col;
    char first_alpha;
    char *temp_str = NULL;

    for (i = 0; i < WORD_TYPE_MAX; i++)
    {
        word_type_array[i] = -1;
    }

    clear();
    print_title("ADD WORDS");
    attron(COLOR_PAIR(6));
    printw("\nEnter Word: ");
    attroff(COLOR_PAIR(6));
    scanw(" %[^\n]", word);
    if (strlen(word) > MAX_WORD_LENGTH)
    {
        attron(COLOR_PAIR(1));
        printw("\nWord too long.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    first_alpha = word_get_first_alpha(word);
    if (first_alpha == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nWord must have atleast one alphabet.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    temp_str = word_get_first_alpha_ptr(word);
    if (*(temp_str+1) == '\0')
    {
        attron(COLOR_PAIR(1));
        printw("\nWord must have atleast two alphanumeric characters.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    for (i = 0; i < WORD_TYPE_MAX; i++)
    {
        p_node = search_word(word, i);
        if (NULL == p_node)
        {
            /* Add this type to the list */
            word_type_array[j++] = i;
        }
    }
    if (j == 0)
    {
        /* All types already present */
        attron(COLOR_PAIR(1));
        printw("\nWord already entered\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }
    if (j < WORD_TYPE_MAX)
    {
        attron(COLOR_PAIR(6));
        printw("\nWord already present. Add as different type? (y/n)");
        attroff(COLOR_PAIR(6));
        choice = getch();
        if (choice == 'n')
        {
            return;
        }
        else if (choice != 'y')
        {
            attron(COLOR_PAIR(1));
            printw("\nInvalid choice.\n");
            attroff(COLOR_PAIR(1));
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
            return;
        }
        else
        {
            printw("\n");
        }
    }

    attron(COLOR_PAIR(6));
    printw("Word Type:\n");
    attroff(COLOR_PAIR(6));
    for (i = 0; i < WORD_TYPE_MAX; i++)
    {
        if (word_type_array[i] >= 0)
        {
            attron(COLOR_PAIR(6));
            printw("%d) ", i+1);
            attroff(COLOR_PAIR(6));
            switch (word_type_array[i])
            {
                case WORD_TYPE_ADJ:
                    printw("Adjective\n");
                    break;
                case WORD_TYPE_VERB:
                    printw("Verb\n");
                    break;
                case WORD_TYPE_NOUN:
                    printw("Noun\n");
                    break;
                case WORD_TYPE_ROOT:
                    printw("Root\n");
                    break;
                case WORD_TYPE_PERSON:
                    printw("Personality Type\n");
                    break;
                case WORD_TYPE_THING:
                    printw("Substance/Material Thing\n");
                    break;
                case WORD_TYPE_OTHER:
                    printw("Other\n");
                    break;
            }
        }
        else
        {
            break;
        }
    }

    attron(COLOR_PAIR(6));
    printw("Choice: ");
    attroff(COLOR_PAIR(6));
    word_type_choice = getch() - '0';
    if ((word_type_choice < 1) || (word_type_choice > i))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid choice.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    /* Get Meaning */
    getyx(stdscr, row, col);
    getmaxyx(stdscr, lastrow, lastcol);
    attron(COLOR_PAIR(1));
    mvprintw(row + 5, 0, "------------Meaning should not cross this line---------");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(6));
    mvprintw(row, col, "\nEnter Meaning:\n");
    attroff(COLOR_PAIR(6));
    scanw(" %[^\n]", word_meaning);
    mvprintw(row + 5, 0, "\n");
    if (strlen(word_meaning) > 300)
    {
        attron(COLOR_PAIR(1));
        printw("\nMeaning too long.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    /* Clear off part of screen for printing example */
    for (i = row; i <= row+4; i++)
    {
        mvprintw(i, 0, "\n");
    }

    /* Get Usage */
    attron(COLOR_PAIR(1));
    mvprintw(row + 5, 0, "------------Usage should not cross this line---------");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(6));
    mvprintw(row, col, "\nEnter Usage:\n");
    attroff(COLOR_PAIR(6));
    scanw(" %[^\n]", word_example);
    mvprintw(row + 5, 0, "\n");
    if (strlen(word_example) > 300)
    {
        attron(COLOR_PAIR(1));
        printw("\nUsage too long.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    /* Add to database */
    add_word(word, word_type_array[word_type_choice - 1], word_meaning, 0, 
		    	word_example);
    attron(COLOR_PAIR(4));
    mvprintw(lastrow - 3, 0, "Word added successfully!\n");
    attroff(COLOR_PAIR(4));
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}

/*****************************************************************************
* 
* Add a particular word to the database
*
*****************************************************************************/
void add_word(char *word_name, enum word_type word_type, char *word_meaning,
        int word_hits, char *word_example)
{
    struct word *p_word = NULL;
    struct word_node *p_node = NULL;
    struct word_node *p_temp_node = NULL, *prev_node = NULL;
    char first_alpha;

    /* Allocate word */
    p_word = (struct word *)malloc(sizeof(struct word));

    /* Allocate and fill word name */
    p_word->word_name = (char *)malloc(sizeof(char) * (strlen(word_name)+ 1));
    strncpy(p_word->word_name, word_name, strlen(word_name) + 1);
    p_word->word_name[strlen(word_name)] = '\0';

    /* Fill word type */
    p_word->word_type = word_type;

    /* Allocate and fill word meaning */
    p_word->word_meaning = (char *)malloc(sizeof(char) * (strlen(word_meaning) +
                1));
    strncpy(p_word->word_meaning, word_meaning, strlen(word_meaning) + 1);
    p_word->word_meaning[strlen(word_meaning)] = '\0';

    /* Allocate and fill word example */
    p_word->word_example = (char *)malloc(sizeof(char) * (strlen(word_example) +
                1));
    strncpy(p_word->word_example, word_example, strlen(word_example) + 1);
    p_word->word_example[strlen(word_example)] = '\0';

    /* Fill word difficulty */
    p_word->word_hits = word_hits;

    /* Fill the word age */
    p_word->word_age = 0;

    /* Allocate and fill word node */
    p_node = (struct word_node *)malloc(sizeof(struct word_node));
    p_node->p_word = p_word;
    p_node->p_next = NULL;
    p_node->p_prev = NULL;

    /* Now add this word to the database */
    first_alpha = word_get_first_alpha(word_name);
    p_temp_node = alphabet_array[first_alpha - 97]->p_head_word_node;
    if (NULL == p_temp_node)
    {
        alphabet_array[first_alpha - 97]->p_head_word_node = p_node;
        alphabet_array[first_alpha - 97]->p_tail_word_node = p_node;
    }
    else
    {
        if (word_strcmp(p_temp_node->p_word->word_name, word_name) >= 0)
        {
            /* Must add new node BEFORE this node */
            alphabet_array[first_alpha - 97]->p_head_word_node = p_node;
            p_node->p_next = p_temp_node;
            p_temp_node->p_prev = p_node;
        }
        else
        {
            prev_node = p_temp_node;
            while (word_strcmp(p_temp_node->p_word->word_name, word_name) < 0)
            {
                prev_node = p_temp_node;
                p_temp_node = p_temp_node->p_next;
                if (p_temp_node == NULL)
                {
                    break;
                }
            }
            /* New node must be added AFTER prev node */
            p_node->p_prev = prev_node;
            p_node->p_next = prev_node->p_next;
            prev_node->p_next = p_node;
            if (NULL != p_node->p_next)
            {
                p_node->p_next->p_prev = p_node;
            }
            else
            {
                /* Added at end of list */
                alphabet_array[first_alpha - 97]->p_tail_word_node = p_node;
            }
        }
    }
    /* Increment the word count */
    alphabet_array[first_alpha - 97]->word_count ++;
    word_count ++;
    switch (word_type)
    {
        case WORD_TYPE_ADJ:
            adjective_count ++;
            break;
        case WORD_TYPE_VERB:
            verb_count ++;
            break;
        case WORD_TYPE_NOUN:
            noun_count ++;
            break;
        case WORD_TYPE_ROOT:
            root_count ++;
            break;
        case WORD_TYPE_PERSON:
            person_count ++;
            break;
        case WORD_TYPE_THING:
            thing_count ++;
            break;
        default:
            break;
    }
}
