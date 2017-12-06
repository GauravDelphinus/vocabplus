/*****************************************************************************
* 
* This file contains the routines for testing vocabulary.
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
   03-Oct-2003  Gaurav Jain      Fixed last test not getting included in
                                 test summary problem
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
* Main vocab test routine
*
*****************************************************************************/
void vocab_test(void)
{
    int test_word_list, test_type;
    int lastrow, lastcol;

    /* Check if there are sufficient words for executing the test */
    if ((adjective_count < TEST_LIST_MAX) &&
            (verb_count < TEST_LIST_MAX) &&
            (noun_count < TEST_LIST_MAX) &&
            (root_count < TEST_LIST_MAX) &&
            (person_count < TEST_LIST_MAX) &&
            (thing_count < TEST_LIST_MAX))
    {
        attron(COLOR_PAIR(1));
        printw("\nNot enough words in database to execute test.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    clear();
    print_title("TEST VOCABULARY");
    attron(COLOR_PAIR(6));
    printw("\nSelect word list for test:\n");
    printw("1) ");
    attroff(COLOR_PAIR(6));
    printw("ALL words in alphabetical order\n");
    attron(COLOR_PAIR(6));
    printw("2) ");
    attroff(COLOR_PAIR(6));
    printw("ALL words in reverse alphabetical order\n");
    attron(COLOR_PAIR(6));
    printw("3) ");
    attroff(COLOR_PAIR(6));
    printw("ALL words in random order\n");
    attron(COLOR_PAIR(6));
    printw("4) ");
    attroff(COLOR_PAIR(6));
    printw("ALL words in random \'learning\' order of difficulty\n");
    attron(COLOR_PAIR(6));
    printw("5) ");
    attroff(COLOR_PAIR(6));
    printw("Single alphabet list in alphabetical order\n");
    attron(COLOR_PAIR(6));
    printw("6) ");
    attroff(COLOR_PAIR(6));
    printw("Single alphabet list in reverse alphabetical order\n");
    attron(COLOR_PAIR(6));
    printw("7) ");
    attroff(COLOR_PAIR(6));
    printw("Single alphabet list in random order\n");
    test_word_list = getch() - '0';
    if ((test_word_list < 1) || (test_word_list > 7))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid choice.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    clear();
    print_subtitle("Select type of test to take:");
    printw("\n");
    attron(COLOR_PAIR(6));
    printw("1) ");
    attroff(COLOR_PAIR(6));
    printw("Select meaning of given word from a list\n");
    attron(COLOR_PAIR(6));
    printw("2) ");
    attroff(COLOR_PAIR(6));
    printw("Select word name of given meaning from a list\n");
    attron(COLOR_PAIR(6));
    printw("3) ");
    attroff(COLOR_PAIR(6));
    printw("Recall a word from its meaning\n");
    attron(COLOR_PAIR(6));
    printw("4) ");
    attroff(COLOR_PAIR(6));
    printw("Randomly select a type of test from all three above\n");
    attron(COLOR_PAIR(6));
    printw("5) ");
    attroff(COLOR_PAIR(6));
    printw("Randomly select a type of test from first two above\n");
    test_type = getch() - '0';
    if ((test_type < 1) || (test_type > 5))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid choice.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    printw("\nGenerating test symbol tables...");
    generate_test_symbol_tables();
    printw("DONE\n");

    switch (test_word_list)
    {
        case 1:
            test_vocab_all_word_list_alphabetical(test_type);
            break;
        case 2:
            test_vocab_all_word_list_rev_alphabetical(test_type);
            break;
        case 3:
            test_vocab_all_word_list_random(test_type);
            break;
        case 4:
            test_vocab_all_word_list_random_learning(test_type);
            break;
        case 5:
            test_vocab_single_alphabet_list_alphabetical(test_type);
            break;
        case 6:
            test_vocab_single_alphabet_list_rev_alphabetical(test_type);
            break;
        case 7:
            test_vocab_single_alphabet_list_random(test_type);
            break;
    }

    printw("Freeing test symbol tables...");
    free_test_symbol_tables();
    printw("DONE\n");
}

/*****************************************************************************
* 
* Routine to generate the symbol tables required for vocab tests
*
*****************************************************************************/
void generate_test_symbol_tables(void)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'a';
    int i = 0, j = 0;
    int word_index = 0;
    int adjective_index = 0;
    int verb_index = 0;
    int noun_index = 0;
    int root_index = 0;
    int person_index = 0;
    int thing_index = 0;

    /* Allocate the test symbol tables */
    test_word_list = (struct word_node **)malloc(word_count *
            sizeof(struct word_node *));
    test_difficulty_list = (struct word_node **)malloc(word_count *
            sizeof(struct word_node *));
    test_adjective_list = (struct word_node **)malloc(adjective_count *
            sizeof(struct word_node *));
    test_verb_list = (struct word_node **)malloc(verb_count *
            sizeof(struct word_node *));
    test_noun_list = (struct word_node **)malloc(noun_count *
            sizeof(struct word_node *));
    test_root_list = (struct word_node **)malloc(root_count *
            sizeof(struct word_node *));
    test_person_list = (struct word_node **)malloc(person_count *
            sizeof(struct word_node *));
    test_thing_list = (struct word_node **)malloc(thing_count *
            sizeof(struct word_node *));
    /* Initialize the memory arrays to NULL */
    for (i = 0; i < word_count; i++)
    {
        test_word_list[i] = NULL;
    }
    for (i = 0; i < word_count; i++)
    {
        test_difficulty_list[i] = NULL;
    }
    for (i = 0; i < adjective_count; i++)
    {
        test_adjective_list[i] = NULL;
    }
    for (i = 0; i < verb_count; i++)
    {
        test_verb_list[i] = NULL;
    }
    for (i = 0; i < noun_count; i++)
    {
        test_noun_list[i] = NULL;
    }
    for (i = 0; i < root_count; i++)
    {
        test_root_list[i] = NULL;
    }
    for (i = 0; i < person_count; i++)
    {
        test_person_list[i] = NULL;
    }
    for (i = 0; i < thing_count; i++)
    {
        test_thing_list[i] = NULL;
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
        /* Found word */
        i = 0;
        while ((i < word_index) && 
                (test_difficulty_list[i]->p_word->word_hits <
                p_temp_node->p_word->word_hits))
        {
            i++;
        }
        for (j = word_index; j > i; j--)
        {
            test_difficulty_list[j] = test_difficulty_list[j - 1];
        }
        test_difficulty_list[i] = p_temp_node;
        test_word_list[word_index++] = p_temp_node;
        switch (p_temp_node->p_word->word_type)
        {
            case WORD_TYPE_ADJ:
                test_adjective_list[adjective_index++] = p_temp_node;
                break;
            case WORD_TYPE_VERB:
                test_verb_list[verb_index++] = p_temp_node;
                break;
            case WORD_TYPE_NOUN:
                test_noun_list[noun_index++] = p_temp_node;
                break;
            case WORD_TYPE_ROOT:
                test_root_list[root_index++] = p_temp_node;
                break;
            case WORD_TYPE_PERSON:
                test_person_list[person_index++] = p_temp_node;
                break;
            case WORD_TYPE_THING:
                test_thing_list[thing_index++] = p_temp_node;
                break;
            default:
                break;
        }
        p_temp_node = p_temp_node->p_next;
    }
}

/*****************************************************************************
* 
* Routine to free the symbols used during vocab tests
*
*****************************************************************************/
void free_test_symbol_tables(void)
{
    free(test_word_list);
    test_word_list = NULL;
    free(test_difficulty_list);
    test_difficulty_list = NULL;
    free(test_adjective_list);
    test_adjective_list = NULL;
    free(test_verb_list);
    test_verb_list = NULL;
    free(test_noun_list);
    test_noun_list = NULL;
    free(test_root_list);
    test_root_list = NULL;
    free(test_person_list);
    test_person_list = NULL;
    free(test_thing_list);
    test_thing_list = NULL;
}

/*****************************************************************************
* 
* Routine for all words alphabetical test 
*
*****************************************************************************/
void test_vocab_all_word_list_alphabetical(int test_type)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'a';
    int i = 0;
    char end;
    int result = FAIL;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int lastrow, lastcol;
    int cont_val = 1;

    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            if (alpha >= 'z')
            {
                /* Done all */
                if (i > 0)
                {
                    attron(COLOR_PAIR(6));
                    printw("\nReached end of word list.  Restart from beginning? (y/n)");
                    attroff(COLOR_PAIR(6));
                    end = getch();
                    if (end == 'y')
                    {
                        alpha = 'a';
                        p_temp_node = 
                            alphabet_array[alpha - 97]->p_head_word_node;
                        continue;
                    }
                    else if (end == 'n')
                    {
                        break;
                    }
                    else
                    {
                        attron(COLOR_PAIR(1));
                        printw("\nInvalid choice.\n");
                        attroff(COLOR_PAIR(1));
                        getmaxyx(stdscr, lastrow, lastcol);
                        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                        getch();
                        return;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                alpha ++;
                p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
                continue;
            }
        }

        clear();

        print_testtitle(i+1, pass, fail);
#if 0
        if (i > 0)
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
        p_temp_node = p_temp_node->p_next;
    }
    print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
}

/*****************************************************************************
* 
* Routine for all words reverse alphabetical test 
*
*****************************************************************************/
void test_vocab_all_word_list_rev_alphabetical(int test_type)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'z';
    int i = 0;
    char end;
    int result = FAIL;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int lastrow, lastcol;
    int cont_val = 1;

    p_temp_node = alphabet_array[alpha - 97]->p_tail_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            if (alpha <= 'a')
            {
                /* Done all */
                if (i > 0)
                {
                    attron(COLOR_PAIR(6));
                    printw("\nReached end of word list.  Restart from beginning? (y/n)");
                    attroff(COLOR_PAIR(6));
                    end = getch();
                    if (end == 'y')
                    {
                        alpha = 'z';
                        p_temp_node = 
                            alphabet_array[alpha - 97]->p_tail_word_node;
                        continue;
                    }
                    else if (end == 'n')
                    {
                        break;
                    }
                    else
                    {
                        attron(COLOR_PAIR(1));
                        printw("\nInvalid choice.\n");
                        attroff(COLOR_PAIR(1));
                        getmaxyx(stdscr, lastrow, lastcol);
                        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                        getch();
                        return;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                alpha --;
                p_temp_node = alphabet_array[alpha - 97]->p_tail_word_node;
                continue;
            }
        }
        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
        p_temp_node = p_temp_node->p_prev;
    }
    print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
}

/*****************************************************************************
* 
* Routine for all words random test 
*
*****************************************************************************/
void test_vocab_all_word_list_random(int test_type)
{
    int random_choice;
    struct word_node *p_temp_node = NULL;
    int i = 0;
    int result;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int cont_val = 1;

    while (1)
    {
        random_choice = word_random(1, word_count);
        p_temp_node = test_word_list[random_choice - 1];

        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
    }
    print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
}

/*****************************************************************************
* 
* Routine for all words random learning test 
*
*****************************************************************************/
void test_vocab_all_word_list_random_learning(int test_type)
{
    int random_choice;
    int random_list_choice;
    struct word_node *p_temp_node = NULL;
    struct word_node *temp_list_node = NULL;
    int i = 0;
    int result;
    int mid;
    int difficult = 0;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int cont_val = 1;

    mid = word_count/2;
    while (1)
    {
        random_list_choice = word_random(1, 
                (75 * (mid)) + (25 * (word_count - mid)));
        if (random_list_choice < (75 * (mid)))
        {
            /* Difficult word */
            random_choice = word_random(1, mid);
            difficult = 1;
        }
        else
        {
            /* Easy word */
            random_choice = word_random(mid + 1, word_count);
            difficult = 0;
        }

        p_temp_node = test_difficulty_list[random_choice - 1];

        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;

        if ((result == PASS) && (difficult == 1))
        {
            if (mid > 1)
            {
                /* Move the word to easy list */
                temp_list_node = test_difficulty_list[random_choice - 1];
                test_difficulty_list[random_choice - 1] = 
                    test_difficulty_list[mid - 1];
                test_difficulty_list[mid - 1] = temp_list_node;
                mid --;
            }
        }
        else if ((result == FAIL) && (difficult == 0))
        {
            if ((word_count - mid) > 1)
            {
                /* Move hte word to difficult list */
                temp_list_node = test_difficulty_list[random_choice - 1];
                test_difficulty_list[random_choice - 1] = 
                    test_difficulty_list[mid];
                test_difficulty_list[mid] = temp_list_node;
                mid ++;
            }
        }
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
    }
    print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
}

/*****************************************************************************
* 
* Routine for single alphabet words alphabetical test 
*
*****************************************************************************/
void test_vocab_single_alphabet_list_alphabetical(int test_type)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'a';
    int i = 0;
    char end;
    int result = FAIL;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int lastrow, lastcol;
    int cont_val = 1;

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

    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done all */
            if (i > 0)
            {
                attron(COLOR_PAIR(6));
                printw("\nReached end of word list.  Restart from beginning? (y/n)");
                attroff(COLOR_PAIR(6));
                end = getch();
                if (end == 'y')
                {
                    p_temp_node = 
                        alphabet_array[alpha - 97]->p_head_word_node;
                    continue;
                }
                else if (end == 'n')
                {
                    break;
                }
                else
                {
                    attron(COLOR_PAIR(1));
                    printw("\nInvalid choice.");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                    return;
                }
            }
            else
            {
                break;
            }
        }
        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
        p_temp_node = p_temp_node->p_next;
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo entry found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
    else
    {
        print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
    }
}

/*****************************************************************************
* 
* Routine for single alphabet words reverse alphabetical test 
*
*****************************************************************************/
void test_vocab_single_alphabet_list_rev_alphabetical(int test_type)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'z';
    int i = 0;
    char end;
    int result = FAIL;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int lastrow, lastcol;
    int cont_val = 1;

    attron(COLOR_PAIR(6));
    printw("\nAlphabet: ");
    attroff(COLOR_PAIR(6));
    alpha = getch();
    if ((alpha < 'a') || (alpha > 'z'))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid input.");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    p_temp_node = alphabet_array[alpha - 97]->p_tail_word_node;
    while (1)
    {
        if (p_temp_node == NULL)
        {
            /* Done all */
            if (i > 0)
            {
                attron(COLOR_PAIR(6));
                printw("\nReached end of word list.  Restart from beginning? (y/n)");
                attroff(COLOR_PAIR(6));
                end = getch();
                if (end == 'y')
                {
                    p_temp_node = 
                        alphabet_array[alpha - 97]->p_tail_word_node;
                    continue;
                }
                else if (end == 'n')
                {
                    break;
                }
                else
                {
                    attron(COLOR_PAIR(1));
                    printw("\nInvalid choice.\n");
                    attroff(COLOR_PAIR(1));
                    getmaxyx(stdscr, lastrow, lastcol);
                    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
                    getch();
                    return;
                }
            }
            else
            {
                break;
            }
        }
        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
        p_temp_node = p_temp_node->p_prev;
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo entry found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
    else
    {
        print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
    }
}

/*****************************************************************************
* 
* Routine for single alphabet words random test 
*
*****************************************************************************/
void test_vocab_single_alphabet_list_random(int test_type)
{
    int random_choice;
    struct word_node *p_temp_node = NULL;
    int i = 0;
    int result;
    int start_index = -1, end_index = -1;
    int start = FALSE;
    char alpha;
    int pass = 0, fail = 0;
    int difficulty_sum = 0;
    int words_added = 0;
    int words_lost = 0;
    int lastrow, lastcol;
    int cont_val = 1;

    attron(COLOR_PAIR(6));
    printw("\nAlphabet: ");
    attroff(COLOR_PAIR(6));
    alpha = getch();
    if ((alpha < 'a') || (alpha > 'z'))
    {
        attron(COLOR_PAIR(1));
        printw("\nInvalid input.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    /* Look for the location of the alphabet words in the list */
    start = FALSE;
    for (i = 0; i < word_count; i++)
    {
        if ((start == FALSE) && (test_word_list[i]->p_word->word_name[0] ==
                    alpha))
        {
            start_index = i;
            start = TRUE;
        }
        if ((start == TRUE) && 
                (test_word_list[i]->p_word->word_name[0] > alpha))
        {
            end_index = i-1;
            break;
        }
    }
    if ((start == TRUE) && (i == word_count))
    {
        /* Reached end of list, with last word of same alphabet */
        end_index = i-1;
    }

    if ((start_index == -1) || (end_index == -1))
    {
        attron(COLOR_PAIR(1));
        printw("\nNo matches found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
        return;
    }

    i = 0;
    while (1)
    {
        random_choice = word_random(start_index + 1, end_index + 1);
        p_temp_node = test_word_list[random_choice - 1];

        clear();
        print_testtitle(i+1, pass, fail);
#if 0
        if (i == 0)
        {
            printw("Start of Test - ALL THE BEST!\n");
        }
        else
        {
            printw("Current Score: %d/%d - %5.2f%\n", pass, (pass + fail), 
                    (pass * 100.0/(pass + fail)));
        }
#endif
        cont_val = test_vocab(i+1, p_temp_node, test_type, &result);
        i++;
        if (result == PASS)
        {
            pass ++;
            if (p_temp_node->p_word->word_hits < 10)
            {
                p_temp_node->p_word->word_hits ++;
            }
        }
        else if (result == FAIL)
        {
            fail ++;
            if (p_temp_node->p_word->word_hits > 0)
            {
                p_temp_node->p_word->word_hits --;
            }
        }
        difficulty_sum += p_temp_node->p_word->word_hits;
        if (cont_val == 0)
        {
            /* Exit Test */
            break;
        }
    }
    if (i == 0)
    {
        attron(COLOR_PAIR(1));
        printw("\nNo entry found.\n");
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
        getch();
    }
    else
    {
        print_test_summary(pass, fail, difficulty_sum, words_added, words_lost);
    }
}

/*****************************************************************************
* 
* Routine to test vocab for a given word
*
*****************************************************************************/
int test_vocab(int serial_number, struct word_node *p_node, int test_type,
        int *p_result)
{
    int retval = FAIL;
    int temp_test_type;

    if (test_type == 4)
    {
        temp_test_type = word_random(1, 3);
    }
    else if (test_type == 5)
    {
        /* Randomly select between first two types of tests */
        temp_test_type = word_random(1, 2);
    }
    else
    {
        temp_test_type = test_type;
    }
    switch (temp_test_type)
    {
        case 1:
            retval = test_vocab_select_meaning_from_list(serial_number, p_node,
                    p_result);
            break;
        case 2:
            retval = test_vocab_select_word_from_list(serial_number, p_node,
                    p_result);
            break;
        case 3:
            retval = test_vocab_recall_word(serial_number, p_node, p_result);
            break;
    }
    /* Increment the age of the word */
    p_node->p_word->word_age ++;

    return retval;
}

/*****************************************************************************
* 
* Routine to test vocab by selecting meaning from a list
*
*****************************************************************************/
int test_vocab_select_meaning_from_list(int serial_number, struct word_node
        *p_node, int *p_result)
{
    int answer;
    struct word_node **test_list = NULL;
    int test_list_size = 0;
    struct word_node *temp_test_list[TEST_LIST_MAX];
    int i = 0, j = 0, already_present = FALSE;
    int rand_choice, choice;
    int lastrow, lastcol;

    attron(COLOR_PAIR(6));
    printw("\nWord ");

    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            printw("(adj): ");
            test_list = test_adjective_list;
            test_list_size = adjective_count;
            break;
        case WORD_TYPE_VERB:
            printw("(verb): ");
            test_list = test_verb_list;
            test_list_size = verb_count;
            break;
        case WORD_TYPE_NOUN:
            printw("(noun): ");
            test_list = test_noun_list;
            test_list_size = noun_count;
            break;
        case WORD_TYPE_ROOT:
            printw("(root): ");
            test_list = test_root_list;
            test_list_size = root_count;
            break;
        case WORD_TYPE_PERSON:
            printw("(pers): ");
            test_list = test_person_list;
            test_list_size = person_count;
            break;
        case WORD_TYPE_THING:
            printw("(subs): ");
            test_list = test_thing_list;
            test_list_size = thing_count;
            break;
        default:
            printw(": ");
            test_list = test_word_list;
            test_list_size = word_count;
            break;
    }
    attron(A_BOLD);
    printw("%s\n", p_node->p_word->word_name);
    attroff(A_BOLD);
    printw("\nSelect the correct meaning:\n");
    attroff(COLOR_PAIR(6));

    if (test_list_size <= TEST_LIST_MAX)
    {
        test_list_size = get_bigger_test_list(&test_list);
    }

    answer = word_random(1, TEST_LIST_MAX);
    for (i = 0; i < TEST_LIST_MAX; i++)
    {
        if (answer == (i+1))
        {
            temp_test_list[i] = p_node;
        }
        else
        {
            while (1)
            {
                rand_choice = word_random(1, test_list_size);
                already_present = FALSE;
                if (test_list[rand_choice - 1] == p_node)
                {
                    already_present = TRUE;
                }
                else
                {
                    for (j = 0; j < i; j++)
                    {
                        /* check if the same word is already selected earlier,
                           or is the word being questioned itself */
                        if (temp_test_list[j] == test_list[rand_choice - 1])
                        {
                            already_present = TRUE;
                            break;
                        }
                    }
                }
                if (already_present == FALSE)
                {
                    temp_test_list[i] = test_list[rand_choice - 1];
                    break;
                }
            }
        }
        attron(COLOR_PAIR(6));
        printw("%c) ", (i+1)+'a'-1);
        attroff(COLOR_PAIR(6));
        print_meaning(temp_test_list[i]->p_word->word_meaning);
    }
    choice = getch();
    if ((choice - 'a' + 1) == answer)
    {
        /* Chose the correct answer ! */
        attron(COLOR_PAIR(4));
        printw("\nCorrect :-)  Well Done !\n");
        attroff(COLOR_PAIR(4));

        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = PASS;
        return 1;
    }
    else
    {
        /* Chose the wrong answer ! */
        attron(COLOR_PAIR(1));
        printw("\nIncorrect :-(  Correct answer is '%c'. Better luck next time!\n",
                (answer - 1 + 'a'));
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = FAIL;
        return 1;
    }
}

/*****************************************************************************
* 
* Routine to test vocab by selecting word from a list
*
*****************************************************************************/
int test_vocab_select_word_from_list(int serial_number, struct word_node
        *p_node, int *p_result)
{
    int answer;
    struct word_node **test_list = NULL;
    int test_list_size = 0;
    struct word_node *temp_test_list[TEST_LIST_MAX];
    int i = 0, j = 0, already_present = FALSE;
    int rand_choice, choice;
    int lastrow, lastcol;

    attron(COLOR_PAIR(6));
    printw("\nMeaning ");

    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            printw("(adj): ");
            test_list = test_adjective_list;
            test_list_size = adjective_count;
            break;
        case WORD_TYPE_VERB:
            printw("(verb): ");
            test_list = test_verb_list;
            test_list_size = verb_count;
            break;
        case WORD_TYPE_NOUN:
            printw("(noun): ");
            test_list = test_noun_list;
            test_list_size = noun_count;
            break;
        case WORD_TYPE_ROOT:
            printw("(root): ");
            test_list = test_root_list;
            test_list_size = root_count;
            break;
        case WORD_TYPE_PERSON:
            printw("(pers): ");
            test_list = test_person_list;
            test_list_size = person_count;
            break;
        case WORD_TYPE_THING:
            printw("(subs): ");
            test_list = test_thing_list;
            test_list_size = thing_count;
            break;
        default:
            printw(": ");
            test_list = test_word_list;
            test_list_size = word_count;
            break;
    }
    attron(A_BOLD);
    print_meaning(p_node->p_word->word_meaning);
    attroff(A_BOLD);
    printw("\nSelect the correct word:\n");
    attroff(COLOR_PAIR(6));

    if (test_list_size <= TEST_LIST_MAX)
    {
        test_list_size = get_bigger_test_list(&test_list);
    }

    answer = word_random(1, TEST_LIST_MAX);
    for (i = 0; i < TEST_LIST_MAX; i++)
    {
        if (answer == (i+1))
        {
            temp_test_list[i] = p_node;
        }
        else
        {
            while (1)
            {
                rand_choice = word_random(1, test_list_size);
                already_present = FALSE;
                if (test_list[rand_choice - 1] == p_node)
                {
                    already_present = TRUE;
                }
                else
                {
                    for (j = 0; j < i; j++)
                    {
                        /* check if the same word is already selected earlier,
                           or is the word being questioned itself */
                        if (temp_test_list[j] == test_list[rand_choice - 1])
                        {
                            already_present = TRUE;
                            break;
                        }
                    }
                }
                if (already_present == FALSE)
                {
                    temp_test_list[i] = test_list[rand_choice - 1];
                    break;
                }
            }
        }
        attron(COLOR_PAIR(6));
        printw("%c) ", (i+1) + 'a' - 1);
        attroff(COLOR_PAIR(6));
        printw("%s\n", temp_test_list[i]->p_word->word_name);
    }
    choice = getch();
    if ((choice - 'a' + 1) == answer)
    {
        /* Chose the correct answer ! */
        attron(COLOR_PAIR(4));
        printw("\nCorrect :-)  Well Done !\n");
        attroff(COLOR_PAIR(4));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = PASS;
        return 1;
    }
    else
    {
        /* Chose the wrong answer ! */
        attron(COLOR_PAIR(1));
        printw("\nIncorrect :-(  Correct answer is '%c'. Better luck next time!\n",
                (answer - 1 + 'a'));
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = FAIL;
        return 1;
    }
}

/*****************************************************************************
* 
* Routine to test vocab by recalling a word given the meaning
*
*****************************************************************************/
int test_vocab_recall_word(int serial_number, struct word_node *p_node,
        int *p_result)
{
    char word_name[50];
    char *temp_str;
    int choice;
    int lastrow, lastcol;
    char temp_word_name[50];
    char first_alpha;
    char *temp_ptr = NULL;

    attron(COLOR_PAIR(6));
    printw("\nComplete the word: (the starting alphabet is given)\n", serial_number);
    printw("Meaning ");

    switch (p_node->p_word->word_type)
    {
        case WORD_TYPE_ADJ:
            printw("(adj): ");
            break;
        case WORD_TYPE_VERB:
            printw("(verb): ");
            break;
        case WORD_TYPE_NOUN:
            printw("(noun): ");
            break;
        case WORD_TYPE_ROOT:
            printw("(root): ");
            break;
        case WORD_TYPE_PERSON:
            printw("(pers): ");
            break;
        case WORD_TYPE_THING:
            printw("(subs): ");
            break;
        default:
            printw(": ");
            break;
    }
    print_meaning(p_node->p_word->word_meaning);
    attroff(COLOR_PAIR(6));
    attron(A_BOLD);
    strcpy(temp_word_name, p_node->p_word->word_name);
    first_alpha = word_get_first_alpha(temp_word_name);
    temp_ptr = word_get_first_alpha_ptr(temp_word_name);
    *(temp_ptr+1) = '\0';
    printw("%s", temp_word_name);
    attroff(A_BOLD);
    scanw(" %[^\n]", word_name);
    temp_str = word_get_first_alpha_ptr(p_node->p_word->word_name);
    temp_str ++; /* Move to second character onwards */
    if (word_strcmp(word_name, temp_str) == 0)
    {
        /* Chose the correct answer ! */
        attron(COLOR_PAIR(4));
        printw("\nCorrect :-)  Well Done !\n");
        attroff(COLOR_PAIR(4));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = PASS;
        return 1;
    }
    else
    {
        /* Chose the wrong answer ! */
        attron(COLOR_PAIR(1));
        printw("\nIncorrect :-(  Correct answer is \'%s\'. Better luck next time!\n",
                p_node->p_word->word_name);
        attroff(COLOR_PAIR(1));
        getmaxyx(stdscr, lastrow, lastcol);
        mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test, 'R' to review word)\n");
        choice = getch();
        if (choice == 'Q')
        {
            /* Want to exit the test */
            return 0;
        }
        else if (choice == 'R')
        {
            clear();
            print_subtitle("Review Word");

            print_wordtitle(PRINT_FORMAT_DETAILED);
            print_word_detailed(0, p_node, FALSE);
            getmaxyx(stdscr, lastrow, lastcol);
            mvprintw(lastrow - 1, 0, "--Next-- (Press 'Q' to quit test)\n");
            choice = getch();
            if (choice == 'Q')
            {
                /* Want to exit the test */
                return 0;
            }
        }
        *p_result = FAIL;
        return 1;
    }
}

/*****************************************************************************
* 
* Routine to print the test summary
*
*****************************************************************************/
void print_test_summary(int pass, int fail, int difficulty_sum, 
        int words_added, int words_lost)
{
    int lastrow, lastcol;
    clear();
    print_subtitle("VOCAB TEST SUMMARY");
    attron(COLOR_PAIR(6));
    printw("\nNo. of Tests ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("Passed: ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    printw("%3d\n", pass);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(6));
    printw("No. of Tests ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    printw("Failed: ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(3));
    printw("%3d\n", fail);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(6));
    printw("Total No. of Tests : ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("%3d\n", pass+fail);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(6));
    printw("How you fared in the tests: ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("%d/%d - %5.2f%\n", pass, (pass+fail),
                    (pass * 100.0/(pass + fail)));
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(6));
    printw("Average no. of hits out of 10: ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("%5.2f\n", difficulty_sum*0.1/(pass+fail));
    attroff(COLOR_PAIR(3));
#if 0
    attron(COLOR_PAIR(6));
    printw("No. of new words ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("added ");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    printw("to your vocabulary     :-) ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("%d\n", words_added);
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(6));
    printw("No. of known words ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(1));
    printw("lost ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(6));
    printw("from your vocabulary  :-( ");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("%d\n", words_lost);
    attroff(COLOR_PAIR(3));
#endif
    getmaxyx(stdscr, lastrow, lastcol);
    mvprintw(lastrow - 1, 0, "Press any key to continue...\n");
    getch();
}

/*****************************************************************************
* 
* Routine to print the meaning of a word
*
*****************************************************************************/
void print_meaning(char *meaning)
{
    char *word_list[100];
    char word_meaning[700];
    char *temp_ptr = NULL, *next_word = NULL;
    int i = 0, j = 0, space_left = 0, k = 0;
    int row, col, maxrow, maxcol;

    strncpy(word_meaning, meaning, strlen(meaning) + 1);
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

    /* Now print the complete meaning */
    /* Get current and max row and column */
    getyx(stdscr, row, col);
    getmaxyx(stdscr, maxrow, maxcol);
    space_left = maxcol - col - 2;
    for (j = 0; j < i; j++)
    {
            if (space_left > strlen(word_list[j]))
            {
                printw("%s ", word_list[j]);
            }
            else
            {
                printw("\n");
                for (k = 0; k < col; k ++)
                {
                    printw(" ");
                }
                printw("%s ", word_list[j]);
                space_left = maxcol - col - 2;
            }
            space_left = space_left - strlen(word_list[j]) - 1;
    }
    printw("\n");
}

/*****************************************************************************
* 
* Routine to get a bigger test list
*
*****************************************************************************/
int get_bigger_test_list (struct word_node ***p_word_list)
{
    if (noun_count > TEST_LIST_MAX)
    {
        *p_word_list = test_noun_list;
	return noun_count;
    }   
    else if (adjective_count > TEST_LIST_MAX)
    {
        *p_word_list = test_adjective_list;
	return adjective_count;
    }
    else if (verb_count > TEST_LIST_MAX)
    {
        *p_word_list = test_verb_list;
	return verb_count;
    }
    else if (root_count > TEST_LIST_MAX)
    {
        *p_word_list = test_root_list;
	return root_count;
    }
    else if (person_count > TEST_LIST_MAX)
    {
        *p_word_list = test_person_list;
	return person_count;
    }
    else if (thing_count > TEST_LIST_MAX)
    {
        *p_word_list = test_thing_list;
	return thing_count;
    }
    return 0;
}
