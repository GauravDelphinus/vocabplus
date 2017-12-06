/*****************************************************************************
* 
* This file contains the routines for editing existing words in the database.
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
* Main routine for editing words in the database
*
*****************************************************************************/
void edit_words(void)
{
    int choice;
    int lastrow, lastcol;

    clear();
    print_title("EDIT WORDS");
    printw("\n");
    attron(COLOR_PAIR(6));
    printw("1) ");
    attroff(COLOR_PAIR(6));
    printw("Edit a particular word\n");
    attron(COLOR_PAIR(6));
    printw("2) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a list of ALL words for editing\n");
    attron(COLOR_PAIR(6));
    printw("3) ");
    attroff(COLOR_PAIR(6));
    printw("Select a word from a single alphabet list of words for editing\n");
    attron(COLOR_PAIR(6));
    printw("Choice: ");
    attroff(COLOR_PAIR(6));
    choice = getch() - '0';
    switch (choice)
    {
        case 1:
            edit_particular_word();
            break;
        case 2:
            edit_word_from_all_list();
            break;
        case 3:
            edit_word_from_alphabet_list();
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
* Routing to edit a particular word in the database
*
*****************************************************************************/
void edit_particular_word(void)
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
    print_subtitle("Edit Particular Word");
    attron(COLOR_PAIR(4));
    printw("\n%d Match%s found\n", (j), (j>1)?("es"):(""));
    attroff(COLOR_PAIR(4));
    print_wordtitle(PRINT_FORMAT_DETAILED);
    i = 0;
    while (i < j)
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
                print_subtitle("Edit Selected Word");
                edit_word(p_node);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;
            }
            clear();
            print_subtitle("Edit Particular Word");
            print_wordtitle(PRINT_FORMAT_DETAILED);
        }
        else
        {
            i++;
        }
    }

    if (i > 1)
    {
        attron(COLOR_PAIR(6));
        printw("\nWhich word to edit? ");
        attroff(COLOR_PAIR(6));
        choice = getch() - 'a' + 1;
        if ((choice < 1) || (choice > j ))
        {
            attron(COLOR_PAIR(1));
            printw("\nInvalid Choice.\n");
            attroff(COLOR_PAIR(1));
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
            return;
        }
        /* Pick up the word to be edited */
        p_node = p_node_list[choice - 1];

        clear();
        print_subtitle("Edit Selected Word");
        edit_word(p_node);
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
        print_subtitle("Edit Selected Word");
        edit_word(p_node);
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
}


/*****************************************************************************
* 
* Routine to select a word from all list for editing
*
*****************************************************************************/
void edit_word_from_all_list(void)
{
    struct word_node *p_temp_node = NULL;
    struct word_node *node_array[20];
    char alpha = 'a';
    int choice;
    int i = 0;
    int more_choice;
    int lastrow, lastcol;

    clear();
    print_subtitle("Select a word from the list below for editing:");
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
            mvprintw(lastrow - 1, 0, "--More-- (Press 'Q' to quit search search)\n");
            more_choice = getch();
            if (more_choice == 'Q')
            {
                return;
            }
            else if ((more_choice >= 'a') && (more_choice <= (i + 'a' - 1)))
            {
                clear();
                print_subtitle("Edit Selected Word");
                edit_word(node_array[more_choice - 'a']);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;

            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for editing:");
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
            print_subtitle("Edit Selected Word");
            edit_word(node_array[choice - 1]);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine to select a word from a single alphabet list for editing
*
*****************************************************************************/
void edit_word_from_alphabet_list(void)
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
    print_subtitle("Select a word from the list below for editing:");
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
                print_subtitle("Edit Selected Word");
                edit_word(node_array[more_choice - 'a']);
                getmaxyx(stdscr, lastrow, lastcol);
                mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                getch();
                return;

            }
            /* Reset count */
            i = 0;
            clear();
            print_subtitle("Select a word from the list below for editing:");
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
            print_subtitle("Edit Selected Word");
            edit_word(node_array[choice - 1]);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
            getch();
        }
        return;
    }
}

/*****************************************************************************
* 
* Routine to edit a word in the database
*
*****************************************************************************/
void edit_word(struct word_node *p_node)
{
    char temp_word_name[50];
    enum word_type temp_word_type;
    char temp_word_meaning[700];
    char temp_word_example[700];
    int temp_word_hits;
    int done, choice;
    struct word_node *p_new_node = NULL;
    struct word_node *p_temp_node = NULL;
    int lastrow, lastcol;
    int row, col;
    int error = 0;
    char first_alpha;
    char *temp_str = NULL;

    /* Initially Set the temp variables to the node values */
    strncpy(temp_word_name, p_node->p_word->word_name,
            strlen(p_node->p_word->word_name) + 1);
    temp_word_type = p_node->p_word->word_type;
    temp_word_hits = p_node->p_word->word_hits;
    strncpy(temp_word_meaning, p_node->p_word->word_meaning,
            strlen(p_node->p_word->word_meaning) + 1);
    strncpy(temp_word_example, p_node->p_word->word_example,
            strlen(p_node->p_word->word_example) + 1);

    /* Create temporary node */
    p_temp_node = (struct word_node *)malloc(sizeof(struct word_node));
    p_temp_node->p_word = (struct word *)malloc(sizeof(struct word));
    p_temp_node->p_word->word_name = (char *)malloc(sizeof(char) *
            strlen(temp_word_name) + 1);
    strncpy(p_temp_node->p_word->word_name, temp_word_name,
            strlen(temp_word_name)+ 1);
    p_temp_node->p_word->word_meaning = (char *)malloc(sizeof(char) *
            strlen(temp_word_meaning) + 1);
    strncpy(p_temp_node->p_word->word_meaning, temp_word_meaning,
            strlen(temp_word_meaning)+ 1);
    p_temp_node->p_word->word_example = (char *)malloc(sizeof(char) *
            strlen(temp_word_example) + 1);
    strncpy(p_temp_node->p_word->word_example, temp_word_example,
            strlen(temp_word_example)+ 1);
    p_temp_node->p_word->word_type = temp_word_type;
    p_temp_node->p_word->word_hits = temp_word_hits;
    
    done = FALSE;
    while (1)
    {
        if (done == TRUE)
        {
            break;
        }

        clear();
        print_subtitle("Edit Selected Word");
        print_wordtitle(PRINT_FORMAT_DETAILED);
        print_word_detailed(0, p_temp_node, FALSE);

        attron(COLOR_PAIR(6));
        printw("\nEdit what?\n");
        printw("0) ");
        attroff(COLOR_PAIR(6));
        printw("Done\n");
        attron(COLOR_PAIR(6));
        printw("1) ");
        attroff(COLOR_PAIR(6));
        printw("Word name\n");
        attron(COLOR_PAIR(6));
        printw("2) ");
        attroff(COLOR_PAIR(6));
        printw("Word type\n");
        attron(COLOR_PAIR(6));
        printw("3) ");
        attroff(COLOR_PAIR(6));
        printw("Word Difficulty\n");
        attron(COLOR_PAIR(6));
        printw("4) ");
        attroff(COLOR_PAIR(6));
        printw("Word Meaning\n");
        attron(COLOR_PAIR(6));
        printw("5) ");
        attroff(COLOR_PAIR(6));
        printw("Word Usage\n");
        choice = getch() - '0';
        switch (choice)
        {
            case 0:
                done = TRUE;
                break;
            case 1:
                clear();
                print_subtitle("Edit Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, p_temp_node, FALSE);

                attron(COLOR_PAIR(6));
                printw("\nEnter word: ");
                attroff(COLOR_PAIR(6));
                scanw(" %[^\n]", temp_word_name);
                if (strlen(temp_word_name) > 20)
                {
                    done = TRUE;
                    error = 1;
                    break;
                }
                first_alpha = word_get_first_alpha(temp_word_name);
                if (first_alpha == 0)
                {
                    done = TRUE;
                    error = 2;
                    break;
                }

                temp_str = word_get_first_alpha_ptr(temp_word_name);
                if (*(temp_str+1) == '\0')
                {
                    done = TRUE;
                    error = 3;
                    break;
                }

                free(p_temp_node->p_word->word_name);
                p_temp_node->p_word->word_name = (char *)malloc(sizeof(char) *
                        strlen(temp_word_name) + 1);
                strncpy(p_temp_node->p_word->word_name, temp_word_name,
                        strlen(temp_word_name)+ 1);
                break;
            case 2:
                clear();
                print_subtitle("Edit Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, p_temp_node, FALSE);

                attron(COLOR_PAIR(6));
                printw("\nWord Type:\n");
                printw("1) ");
                attroff(COLOR_PAIR(6));
                printw("Adjective\n");
                attron(COLOR_PAIR(6));
                printw("2) ");
                attroff(COLOR_PAIR(6));
                printw("Verb\n");
                attron(COLOR_PAIR(6));
                printw("3) ");
                attroff(COLOR_PAIR(6));
                printw("Noun\n");
                attron(COLOR_PAIR(6));
                printw("4) ");
                attroff(COLOR_PAIR(6));
                printw("Root\n");
                attron(COLOR_PAIR(6));
                printw("5) ");
                attroff(COLOR_PAIR(6));
                printw("Personality Type\n");
                attron(COLOR_PAIR(6));
                printw("6) ");
                attroff(COLOR_PAIR(6));
                printw("Substance/Material Thing\n");
                attron(COLOR_PAIR(6));
                printw("7) ");
                attroff(COLOR_PAIR(6));
                printw("Other\n");
                choice = getch() - '0';
                if ((choice < 1) || (choice > 7))
                {
                    attron(COLOR_PAIR(1));
                    printw("\nInvalid choice...\n");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                    break;
                }
                temp_word_type = choice - 1;
                p_temp_node->p_word->word_type = temp_word_type;
                break;
            case 3:
                clear();
                print_subtitle("Edit Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, p_temp_node, FALSE);

                attron(COLOR_PAIR(6));
                printw("\nWord Difficulty: ");
                attroff(COLOR_PAIR(6));
                scanw("%d", &temp_word_hits);
                p_temp_node->p_word->word_hits = temp_word_hits;
                break;
            case 4:
                clear();
                print_subtitle("Edit Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, p_temp_node, FALSE);

                getyx(stdscr, row, col);
                getmaxyx(stdscr, lastrow, lastcol);
                attron(COLOR_PAIR(1));
                mvprintw(row + 5, 0, "------------Meaning should not cross this line---------");
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(6));
                mvprintw(row, col, "\nWord Meaning:\n");
                attroff(COLOR_PAIR(6));
                scanw(" %[^\n]", temp_word_meaning);
                mvprintw(row + 5, 0, "\n");
                if (strlen(temp_word_meaning) > 300)
                {
                    done = TRUE;
                    error = TRUE;
                    break;
                }
                free(p_temp_node->p_word->word_meaning);
                p_temp_node->p_word->word_meaning = 
                   (char *)malloc(sizeof(char) * strlen(temp_word_meaning) + 1);
                strncpy(p_temp_node->p_word->word_meaning, temp_word_meaning,
                        strlen(temp_word_meaning)+ 1);
                break;
            case 5:
                clear();
                print_subtitle("Edit Selected Word");
                print_wordtitle(PRINT_FORMAT_DETAILED);
                print_word_detailed(0, p_temp_node, FALSE);

                getyx(stdscr, row, col);
                getmaxyx(stdscr, lastrow, lastcol);
                attron(COLOR_PAIR(1));
                mvprintw(row + 5, 0, "------------Usage should not cross this line---------");
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(6));
                mvprintw(row, col, "\nWord Usage:\n");
                attroff(COLOR_PAIR(6));
                scanw(" %[^\n]", temp_word_example);
                mvprintw(row + 5, 0, "\n");
                if (strlen(temp_word_example) > 300)
                {
                    done = TRUE;
                    error = TRUE;
                    break;
                }
                free(p_temp_node->p_word->word_example);
                p_temp_node->p_word->word_example = 
                   (char *)malloc(sizeof(char) * strlen(temp_word_example) + 1);
                strncpy(p_temp_node->p_word->word_example, temp_word_example,
                        strlen(temp_word_example)+ 1);
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

    /* Free temporary node */
    free (p_temp_node->p_word->word_name);
    p_temp_node->p_word->word_name = NULL;

    free (p_temp_node->p_word->word_meaning);
    p_temp_node->p_word->word_meaning = NULL;

    free (p_temp_node->p_word->word_example);
    p_temp_node->p_word->word_example = NULL;

    free (p_temp_node->p_word);
    p_temp_node->p_word = NULL;

    free (p_temp_node);
    p_temp_node= NULL;

    if (error > 0)
    {
        attron(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        switch (error)
        {
            case 1:
                mvprintw(lastrow - 3, 0, "\nWord too long.\n");
                break;
            case 2:
                mvprintw(lastrow - 3, 0, "\nWord must have atleast one alphabet.\n");
                break;
            case 3:
                mvprintw(lastrow - 3, 0, "\nWord must have atleast two alphanumeric characters.\n");
                break;
        }
        attroff(COLOR_PAIR(1));
        return;
    }

    /* Lookup if the new values are fine, they should not conflict
       with any other existing word in the database */
    p_new_node = search_word(temp_word_name, temp_word_type);
    if (p_new_node == p_node)
    {
        /* Things are fine */
        strncpy(p_node->p_word->word_name, temp_word_name,
                strlen(temp_word_name) + 1);
        p_node->p_word->word_type = temp_word_type;
        p_node->p_word->word_hits = temp_word_hits;

        free(p_node->p_word->word_meaning);
        p_node->p_word->word_meaning = 
            (char *)malloc(sizeof(char) * strlen(temp_word_meaning) + 1);
        strncpy(p_node->p_word->word_meaning, temp_word_meaning,
                strlen(temp_word_meaning) + 1);

        free(p_node->p_word->word_example);
        p_node->p_word->word_example = 
            (char *)malloc(sizeof(char) * strlen(temp_word_example) + 1);
        strncpy(p_node->p_word->word_example, temp_word_example,
                strlen(temp_word_example) + 1);

        /* Done, so return */
        getmaxyx(stdscr, lastrow, lastcol);
        attron(COLOR_PAIR(4));
        mvprintw(lastrow - 3, 0, "Word updated successfully!\n");
        attroff(COLOR_PAIR(4));
        return;
    }
    else if (NULL == p_new_node)
    {
        /* This means that the name or type of the word has changed */
        if (word_strcmp(p_node->p_word->word_name, temp_word_name
                    ) != 0)
        {
            /* the word name has changed, so this requires that we
               reposition the node */

            /* Now delete the node from its current location */
            delete_word(p_node);

            /* Now insert the word at the new location */
            add_word(temp_word_name, temp_word_type, temp_word_meaning,
                    temp_word_hits, temp_word_example);

        }
        else
        {
            /* The word name is same, but other attributes may have
               changed, so simply copy new values */
            strncpy(p_node->p_word->word_name, temp_word_name,
                    strlen(temp_word_name) + 1);
            p_node->p_word->word_type = temp_word_type;
            p_node->p_word->word_hits = temp_word_hits;
            strncpy(p_node->p_word->word_meaning, temp_word_meaning,
                    strlen(temp_word_meaning) + 1);
            strncpy(p_node->p_word->word_example, temp_word_example,
                    strlen(temp_word_example) + 1);
        }
        attron(COLOR_PAIR(4));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 3, 0, "Word updated successfully!\n");
        attroff(COLOR_PAIR(4));
        return;
    }
    else
    {
        /* This means that such a word already exists, so return error */
        attron(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 3, 0, "Error: Such a word already exists.\n");
        attroff(COLOR_PAIR(1));
        return;
    }
}
