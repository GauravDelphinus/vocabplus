/*****************************************************************************
* 
* This file contains the routines for viewing words from the database.
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
   04-Oct-2003  Gaurav Jain      Added support for searching based on 
                                 regular expressions.
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
* Routine to view words
*
*****************************************************************************/
void view_words(void)
{
    int choice;
    int lastrow, lastcol;

    clear();
    print_title("VIEW WORDS");
    printw("\n");
    attron(COLOR_PAIR(6));
    printw("1) ");
    attroff(COLOR_PAIR(6));
    printw("Search Words\n");
    attron(COLOR_PAIR(6));
    printw("2) ");
    attroff(COLOR_PAIR(6));
    printw("View a Particular Word\n");
    attron(COLOR_PAIR(6));
    printw("3) ");
    attroff(COLOR_PAIR(6));
    printw("View a list of ALL Words\n");
    attron(COLOR_PAIR(6));
    printw("4) ");
    attroff(COLOR_PAIR(6));
    printw("View a single alphabet list of words\n");
    attron(COLOR_PAIR(6));
    printw("5) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a list of ALL words\n");
    attron(COLOR_PAIR(6));
    printw("6) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a single alphabet list of words\n");
    attron(COLOR_PAIR(6));
    printw("Choice: ");
    attroff(COLOR_PAIR(6));
    choice = getch() - '0';
    switch (choice)
    {
        case 1:
            search_words();
            break;
        case 2:
            view_particular_word();
            break;
        case 3:
            view_all_list();
            break;
        case 4:
            view_alphabet_list();
            break;
        case 5:
            select_word_from_all_list();
            break;
        case 6:
            select_word_from_alphabet_list();
            break;
        default:
            attron(COLOR_PAIR(1));
            printw("\nInvalid Choice...\n");
            attroff(COLOR_PAIR(1));
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
            return;
    }
}

/*****************************************************************************
* 
* Routine to view a particular word from the database
*
*****************************************************************************/
void view_particular_word(void)
{
    char word[50];
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
    print_subtitle("View Particular Word");
    attron(COLOR_PAIR(4));
    printw("\n%d Match%s found\n", (j), (j>1)?("es"):(""));
    attroff(COLOR_PAIR(4));
    print_wordtitle(PRINT_FORMAT_DETAILED);
    if (j > 1)
    {
        i = 0;
        while (i < j)
        {
            if (print_word_detailed(i+1, p_node_list[i], FALSE) == FALSE)
            {
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "--More-- (Press 'Q' to quit search)\n");
                morechoice = getch();
                if (morechoice == 'Q')
                {
                    return;
                }
                clear();
                print_subtitle("View Particular Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        print_word_detailed(0, p_node_list[0], FALSE);
    }
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}

/*****************************************************************************
* 
* Routine to view all word list from the database
*
*****************************************************************************/
void view_all_list(void)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'a';
    int i = 0;
    char more_choice;
    int lastrow, lastcol;

    clear();
    print_subtitle("List of all words");
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
        if (print_word_detailed(i+1, p_temp_node, FALSE) == TRUE)
        {
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
            clear();
            print_subtitle("List of all words");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo Matches found.\n");
        attroff(COLOR_PAIR(1));
    }
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}

/*****************************************************************************
* 
* Routine to view a single alplhabet list from the database
*
*****************************************************************************/
void view_alphabet_list(void)
{
    char alpha;
    struct word_node *p_temp_node = NULL;
    int i = 0;
    char more_choice;
    int lastrow, lastcol;
    char subtitle[80];

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

    sprintf(subtitle, "List of all words beginning with alphabet \'%c\'", alpha);
    clear();
    print_subtitle(subtitle);
    print_wordtitle(PRINT_FORMAT_DETAILED);
    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done */
            break;
        }
        /* Something to print */
        if (print_word_detailed(i+1, p_temp_node, FALSE) == TRUE)
        {
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
            clear();
            print_subtitle(subtitle);
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo Matches found.\n");
        attroff(COLOR_PAIR(1));
    }
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}

/*****************************************************************************
* 
* Routine to select a word from all list for viewing
*
*****************************************************************************/
void select_word_from_all_list(void)
{
    struct word_node *p_temp_node = NULL;
    struct word_node *node_array[20];
    char alpha = 'a';
    int choice;
    int i = 0;
    int more_choice;
    int lastrow, lastcol;

    clear();
    print_subtitle("Select a word from the list below for viewing:");
    print_wordtitle(PRINT_FORMAT_SHORT);
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
        if (print_word_short(i+1, p_temp_node, TRUE) == TRUE)
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
                print_subtitle("View Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, node_array[more_choice - 'a'], FALSE);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;
            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for viewing:");
            print_wordtitle(PRINT_FORMAT_SHORT);
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
            print_subtitle("View Selected Word");
            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, node_array[choice - 1], FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine to select a word from a single alphabet list for viewing
*
*****************************************************************************/
void select_word_from_alphabet_list(void)
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
    print_subtitle("Select a word from the list below for viewing:");
    print_wordtitle(PRINT_FORMAT_SHORT);
    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done all */
            break;
        }
        /* Something to print */
        if (print_word_short(i+1, p_temp_node, TRUE) == TRUE)
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
                print_subtitle("View Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, node_array[more_choice - 'a'], FALSE);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;
            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for viewing:");
            print_wordtitle(PRINT_FORMAT_SHORT);
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
            print_subtitle("View Selected Word");
            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, node_array[choice - 1], FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine which checks if it is okay to print
*
*****************************************************************************/
int ok_to_print_detailed(int serial_no, struct word_node *p_node)
{
    static int count = 1;
    if ((count % 10) == 0)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
    count ++;
}

/*****************************************************************************
* 
* Routine that prints short format of the given word
*
*****************************************************************************/
int print_word_short(int serial_no, struct word_node *p_node, int choice_flag)
{
    char word_type[15];
    int row, col, maxrow, maxcol;
    int attributes = 0;

    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            strcpy(word_type, "(adj)");
            break;
        case WORD_TYPE_VERB:
            strcpy(word_type, "(verb)");
            break;
        case WORD_TYPE_NOUN:
            strcpy(word_type, "(noun)");
            break;
        case WORD_TYPE_ROOT:
            strcpy(word_type, "(root)");
            break;
        case WORD_TYPE_PERSON:
            strcpy(word_type, "(pers)");
            break;
        case WORD_TYPE_THING:
            strcpy(word_type, "(subs)");
            break;
        default:
            strcpy(word_type, "(?)");
            break;
    }

    /* Hight light if the word is new or is difficult */
    if (p_node->p_word->word_age < 5)
    {
        attributes = COLOR_PAIR(3) | A_BOLD;
    }
    else if ((p_node->p_word->word_hits >= 0) &&
            (p_node->p_word->word_hits < 5))
    {
        attributes = COLOR_PAIR(1) | A_BOLD;
    }
    else if (p_node->p_word->word_hits <= 8)
    {
        attributes = COLOR_PAIR(1);
    }
    else
    {
        attributes = COLOR_PAIR(2);
    }

    getyx(stdscr, row, col);
    getmaxyx(stdscr, maxrow, maxcol);
    if ((maxrow - row) > 2)
    {
        if (choice_flag == TRUE)
        {
            if (serial_no <= 26)
            {
                attron(COLOR_PAIR(6));
                printw("%4c) ", (serial_no - 1 + 'a'));
                attroff(COLOR_PAIR(6));
                attron(attributes);
                printw("%-20s ", p_node->p_word->word_name);
                attroff(attributes);
                attron(COLOR_PAIR(5));
                printw("%-6s\n", word_type);
                attroff(COLOR_PAIR(5));
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            if (serial_no > 0)
            {
                attron(COLOR_PAIR(6));
                printw("%4d) ", serial_no);
                attroff(COLOR_PAIR(6));
                attron(attributes);
                printw("%-20s ", p_node->p_word->word_name);
                attroff(attributes);
                attron(COLOR_PAIR(5));
                printw("%-6s\n", word_type);
                attroff(COLOR_PAIR(5));
            }
            else
            {
                attron(COLOR_PAIR(6));
                printw("----> ");
                attroff(COLOR_PAIR(6));
                attron(attributes);
                printw("%-20s ", p_node->p_word->word_name);
                attroff(attributes);
                attron(COLOR_PAIR(5));
                printw("%-6s\n", word_type);
                attroff(COLOR_PAIR(5));
            }
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
    return FALSE;
}

/*****************************************************************************
* 
* Routine that prints detailed format of the given word
*
*****************************************************************************/
int print_word_detailed(int serial_no, struct word_node *p_node, int choice_flag)
{
    char word_type[15];
    char *word_list[100];
    char word_meaning[1400];
    char *temp_ptr = NULL, *next_word = NULL;
    int i = 0, j = 0, space_left = 0, k = 0;
    int row, col, maxrow, maxcol, currow, curcol;
    int attributes = 0;

    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            strcpy(word_type, "(adj)");
            break;
        case WORD_TYPE_VERB:
            strcpy(word_type, "(verb)");
            break;
        case WORD_TYPE_NOUN:
            strcpy(word_type, "(noun)");
            break;
        case WORD_TYPE_ROOT:
            strcpy(word_type, "(root)");
            break;
        case WORD_TYPE_PERSON:
            strcpy(word_type, "(pers)");
            break;
        case WORD_TYPE_THING:
            strcpy(word_type, "(subs)");
            break;
        default:
            strcpy(word_type, "(?)");
            break;
    }
    strncpy(word_meaning, p_node->p_word->word_meaning,
            strlen(p_node->p_word->word_meaning) + 1);

    /* Append the Usage to the Word meaning */
    if (strlen(p_node->p_word->word_example) > 1)
    {
        strcat(word_meaning, " [usage] ");
        strcat(word_meaning, p_node->p_word->word_example);
    }
    temp_ptr = word_meaning;
    i = 0;
    while (1)
    {
        next_word = strchr(temp_ptr, ' ');
        if (NULL == next_word)
        {
            /* set last word */
            word_list[i++] = temp_ptr;
            break;
        }
        *next_word = '\0';
        word_list[i++] = temp_ptr;
        temp_ptr = next_word + 1;
    }

    /* Hight light if the word is new or is difficult */
    if (p_node->p_word->word_age < 5)
    {
        attributes = COLOR_PAIR(3) | A_BOLD;
    }
    else if ((p_node->p_word->word_hits >= 0) &&
            (p_node->p_word->word_hits < 5))
    {
        attributes = COLOR_PAIR(1) | A_BOLD;
    }
    else if (p_node->p_word->word_hits <= 8)
    {
        attributes = COLOR_PAIR(1);
    }
    else
    {
        attributes = COLOR_PAIR(2);
    }

    if (choice_flag == TRUE)
    {
        if (serial_no <= 26)
        {
            attron(COLOR_PAIR(6));
            printw("%4c) ", serial_no - 1 + 'a');
            attroff(COLOR_PAIR(6));
            attron(attributes);
            printw("%-20s ", p_node->p_word->word_name);
            attroff(attributes);
            attron(COLOR_PAIR(5));
            printw("%-6s ", word_type);
            attroff(COLOR_PAIR(5));
            if (p_node->p_word->word_hits > 0)
            {
                attron(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(4));
            }
            printw("%3d ", p_node->p_word->word_hits);
            if (p_node->p_word->word_hits > 0)
            {
                attroff(COLOR_PAIR(1));
            }
            else
            {
                attroff(COLOR_PAIR(4));
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (serial_no > 0)
        {
            attron(COLOR_PAIR(6));
            printw("%4d) ", serial_no);
            attroff(COLOR_PAIR(6));
            attron(attributes);
            printw("%-20s ", p_node->p_word->word_name);
            attroff(attributes);
            attron(COLOR_PAIR(5));
            printw("%-6s ", word_type);
            attroff(COLOR_PAIR(5));
            if (p_node->p_word->word_hits > 0)
            {
                attron(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(4));
            }
            printw("%3d ", p_node->p_word->word_hits);
            if (p_node->p_word->word_hits > 0)
            {
                attroff(COLOR_PAIR(1));
            }
            else
            {
                attroff(COLOR_PAIR(4));
            }
        }
        else
        {
            attron(COLOR_PAIR(6));
            printw("----> ");
            attroff(COLOR_PAIR(6));
            attron(attributes);
            printw("%-20s ", p_node->p_word->word_name);
            attroff(attributes);
            attron(COLOR_PAIR(5));
            printw("%-6s ", word_type);
            attroff(COLOR_PAIR(5));
            if (p_node->p_word->word_hits > 0)
            {
                attron(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(4));
            }
            printw("%3d ", p_node->p_word->word_hits);
            if (p_node->p_word->word_hits > 0)
            {
                attroff(COLOR_PAIR(1));
            }
            else
            {
                attroff(COLOR_PAIR(4));
            }
        }
    }
    /* Now print the complete meaning */
    /* Get current and max row and column */
    getyx(stdscr, row, col);
    getmaxyx(stdscr, maxrow, maxcol);
    space_left = maxcol - col - 2;
    for (j = 0; j < i; j++)
    {
        getyx(stdscr, currow, curcol);
        if ((maxrow - currow) > 2)
        {
            if (space_left > strlen(word_list[j]))
            {
                printw("%s ", word_list[j]);
            }
            else
            {
                printw("\n");
                for (k = 0; k < col; k++)
                {
                    printw(" ");
                }
                printw("%s ", word_list[j]);
                space_left = maxcol - col - 2;
            }
            space_left = space_left - strlen(word_list[j]) - 1;
        }
        else
        {
            /* Erase what has already been written */
            for (k = row; k < maxrow; k++)
            {
                mvprintw(k, 0, "\n");
            }
            return FALSE;
        }
    }
    printw("\n");
    return TRUE;
}

/*****************************************************************************
* 
* Routine to search word list from the database based on a regular expression
*
*****************************************************************************/
void search_words(void)
{
    struct word_node *p_temp_node = NULL, *p_next_node;
    int i = 0;
    char more_choice;
    int lastrow, lastcol;
    char regexp[50];
    struct word_node *p_match_list = NULL;

    attron(COLOR_PAIR(6));
    printw("\nEnter Regular Expression: ");
    attroff(COLOR_PAIR(6));
    scanw(" %[^\n]", regexp);

    /* Fetch the matching list */
    search_regexp(regexp, &p_match_list);

    clear();
    print_subtitle("List of matching words");
    print_wordtitle(PRINT_FORMAT_DETAILED);
    p_temp_node = p_match_list;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done all */
            break;
        }
        /* Something to print */
        if (print_word_detailed(i+1, p_temp_node, FALSE) == TRUE)
        {
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
            clear();
            print_subtitle("List of matching words");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo Matches found.\n");
        attroff(COLOR_PAIR(1));
    }

    /* Free the match list */
    p_temp_node = p_match_list;
    while (p_temp_node != NULL)
    {
        p_next_node = p_temp_node->p_next;
        free(p_temp_node);
        p_temp_node = p_next_node;
    }

    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}
