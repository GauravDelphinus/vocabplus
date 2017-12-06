/*****************************************************************************
* 
* This file contains the routines for deleting existing words from the 
* database.
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
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Main routine for deleting words from the database
*
*****************************************************************************/
void delete_words(void)
{
    int choice;
    int lastrow, lastcol;

    clear();
    print_title("DELETE WORDS");
    printw("\n");
    attron(COLOR_PAIR(6));
    printw("1) ");
    attroff(COLOR_PAIR(6));
    printw("Delete a particular word\n");
    attron(COLOR_PAIR(6));
    printw("2) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a list of ALL words for deletion\n");
    attron(COLOR_PAIR(6));
    printw("3) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a single alphabet list of words for deletion\n");
    attron(COLOR_PAIR(6));
    printw("Choice: ");
    attroff(COLOR_PAIR(6));
    choice = getch() - '0';
    switch (choice)
    {
        case 1:
            delete_particular_word();
            break;
        case 2:
            delete_word_from_all_list();
            break;
        case 3:
            delete_word_from_alphabet_list();
            break;
        default:
            attron(COLOR_PAIR(1));
            printw("\nInvalid choice.\n");
            attroff(COLOR_PAIR(1));
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
            break;
    }
}

/*****************************************************************************
* 
* Routing to delete a particular word from the database
*
*****************************************************************************/
void delete_particular_word(void)
{
    char word[50];
    int choice;
    struct word_node *p_node_list[WORD_TYPE_MAX];
    struct word_node *p_node = NULL;
    int i = 0, j = 0;
    int morechoice;
    int lastrow, lastcol;


    for (i = 0; i < WORD_TYPE_MAX; i++)
    {
        p_node_list[i] = NULL;
    }

    attron(COLOR_PAIR(6));
    printw("\nEnter word: ");
    attroff(COLOR_PAIR(6));
    scanw(" %[^\n]", word);
    for (i = 0; i < WORD_TYPE_MAX; i++)
    {
        p_node = search_word(word, i);
        if (NULL != p_node)
        {
            p_node_list[j++] = p_node;
        }
    }
    if (j == 0)
    {
        /* Word not found */
        attron(COLOR_PAIR(1));
        printw("\nWord not found\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    /* Now print all the matches found */
    clear();
    print_subtitle("Delete Particular Word");
    attron(COLOR_PAIR(4));
    printw("\n%d Match%s found\n", (j), (j>1)?("es"):(""));
    attroff(COLOR_PAIR(4));
    print_wordtitle(PRINT_FORMAT_DETAILED);
    for (i = 0; i < j; i++)
    {
        if (print_word_detailed(i+1, p_node_list[i], TRUE) == FALSE)
        {
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--More-- (Press 'Q' to quit search)\n");
            morechoice = getch();
            if (morechoice == 'Q')
            {
                return;
            }
            else if ((morechoice >= 'a') && (morechoice <= i + 'a' - 1))
            {
                p_node = p_node_list[morechoice - 'a'];

                clear();
                print_subtitle("Delete Selected Word");
                delete_word(p_node);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;
            }
            clear();
            print_subtitle("Delete Particular Word");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }

    if (i > 1)
    {
        attron(COLOR_PAIR(6));
        printw("\nWhich word to delete? ");
        attroff(COLOR_PAIR(6));
        choice = getch() - 'a' + 1;
        if ((choice < 1) || (choice > j ))
        {
            attron(COLOR_PAIR(1));
            printw("\nInvalid Choice...\n");
            attroff(COLOR_PAIR(1));
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
            return;
        }
        /* Pick up the word to be edited */
        p_node = p_node_list[choice - 1];

        clear();
        print_subtitle("Delete Selected Word");
        delete_word(p_node);
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
    else if (i == 1)
    {
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        /* Single word found, so no need to ask */
        p_node = p_node_list[0];

        clear();
        print_subtitle("Delete Selected Word");
        delete_word(p_node);
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
}


/*****************************************************************************
* 
* Routine to select a word from all list for deletion
*
*****************************************************************************/
void delete_word_from_all_list(void)
{
    struct word_node *p_temp_node = NULL;
    struct word_node *node_array[20];
    char alpha = 'a';
    int choice;
    int i = 0;
    int more_choice;
    int lastrow, lastcol;

    clear();
    print_subtitle("Select a word from the list below for deletion:");
    print_wordtitle(PRINT_FORMAT_DETAILED);
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
        if (print_word_detailed(i+1, p_temp_node, TRUE) == TRUE)
        {
            node_array[i] = p_temp_node;
            i++;
            p_temp_node = p_temp_node->p_next;
        }
        else
        {
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--More-- (Press 'Q' to quit search)\n");
            more_choice = getch();
            if (more_choice == 'Q')
            {
                return;
            }
            else if ((more_choice >= 'a') && (more_choice <= (i + 'a' - 1)))
            {
                clear();
                print_subtitle("Delete Selected Word");
                delete_word(node_array[more_choice - 'a']);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;

            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for deletion:");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo Matches found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }
    else
    {
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "(End of List)\n");
        choice = getch() - 'a' + 1;
        if ((choice >= 1) && (choice <= i))
        {
            clear();
            print_subtitle("Delete Selected Word");
            delete_word(node_array[choice - 1]);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine for selecting a word from a single alphabet list for deletion
*
*****************************************************************************/
void delete_word_from_alphabet_list(void)
{
    struct word_node *p_temp_node = NULL;
    struct word_node *node_array[20];
    char alpha = 'a';
    int choice;
    int i = 0;
    int more_choice;
    int lastrow, lastcol;

    attron(COLOR_PAIR(6));
    printw("\nAlphabet: ");
    attroff(COLOR_PAIR(6));
    alpha = getch();
    if ((alpha < 'a') || (alpha > 'z'))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid Input.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    clear();
    print_subtitle("Select a word from the list below for deletion:");
    print_wordtitle(PRINT_FORMAT_DETAILED);
    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done all */
            break;
        }
        /* Something to print */
        if (print_word_detailed(i+1, p_temp_node, TRUE) == TRUE)
        {
            node_array[i] = p_temp_node;
            i++;
            p_temp_node = p_temp_node->p_next;
        }
        else
        {
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--More-- (Press 'Q' to quit search)\n");
            more_choice = getch();
            if (more_choice == 'Q')
            {
                return;
            }
            else if ((more_choice >= 'a') && (more_choice <= (i + 'a' - 1)))
            {
                clear();
                print_subtitle("Delete Selected Word");
                delete_word(node_array[more_choice - 'a']);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;

            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for deletion:");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo Matches found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }
    else
    {
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "(End of List)\n");
        choice = getch() - 'a' + 1;
        if ((choice >= 1) && (choice <= i))
        {
            clear();
            print_subtitle("Delete Selected Word");
            delete_word(node_array[choice - 1]);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine to delete a word from the database
*
*****************************************************************************/
void delete_word(struct word_node *p_node)
{
    char alpha;
    int choice;
    int lastrow, lastcol;

    attron(COLOR_PAIR(6));
    printw("\nAre you sure you want to permanently delete the word \'%s\'? (y/n)",
            p_node->p_word->word_name);
    attroff(COLOR_PAIR(6));
    choice = getch();
    if ((choice != 'y') && (choice != 'n'))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid Choice.\n");
        attroff(COLOR_PAIR(1));
        return;
    }
    if (choice == 'n')
    {
        /* Return without deleting the node */
        getmaxyx(stdscr, lastrow, lastcol);
        attron(COLOR_PAIR(4));
        mvprintw(lastrow - 3, 0, "Deletion cancelled.\n");
        attroff(COLOR_PAIR(4));
        return;
    }

    /* Find the alphabet */
#if 0 /* Removed, added support for capital letters and other symbols */
    alpha = p_node->p_word->word_name[0];
#endif
    alpha = word_get_first_alpha(p_node->p_word->word_name);

    /* if it is the head node */
    if (p_node == alphabet_array[alpha - 97]->p_head_word_node)
    {
        alphabet_array[alpha - 97]->p_head_word_node = p_node->p_next;
    }

    /* if this is the tail node, */
    if (p_node == alphabet_array[alpha - 97]->p_tail_word_node)
    {
        alphabet_array[alpha - 97]->p_tail_word_node = p_node->p_prev;
    }

    /* Now detach the node from the list */
    if (NULL != p_node->p_prev)
    {
        p_node->p_prev->p_next = p_node->p_next;
    }
    if (NULL != p_node->p_next)
    {
        p_node->p_next->p_prev = p_node->p_prev;
    }

    /* Decrement the count in the alphabet array list */
    alphabet_array[alpha - 97]->word_count --;
    word_count --;
    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            adjective_count --;
            break;
        case WORD_TYPE_VERB:
            verb_count --;
            break;
        case WORD_TYPE_NOUN:
            noun_count --;
            break;
        case WORD_TYPE_ROOT:
            root_count --;
            break;
        case WORD_TYPE_PERSON:
            person_count --;
            break;
        case WORD_TYPE_THING:
            thing_count --;
            break;
        default:
            break;
    }

    /* Now free the node itself */
    free(p_node->p_word->word_name);
    p_node->p_word->word_name = NULL;

    free(p_node->p_word->word_meaning);
    p_node->p_word->word_meaning = NULL;

    free(p_node->p_word);
    p_node->p_word = NULL;

    free(p_node);
    p_node = NULL;

    getmaxyx(stdscr, lastrow, lastcol);
    attron(COLOR_PAIR(4));
    mvprintw(lastrow - 3, 0, "Word deleted successfully!\n");
    attroff(COLOR_PAIR(4));

    return;
}


