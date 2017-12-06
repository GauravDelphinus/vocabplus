/*****************************************************************************
* 
* This header file contains data structures definitions used by the C source
* files.
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

#define TRUE    1
#define FALSE   0
#define PASS    1
#define FAIL    2

#define MATCH       0
#define NOMATCH    -1
/* IMPORANT: This test list max SHOUD NOT be more than 26 */
#define TEST_LIST_MAX   4

#define NULL ((void *)0)

#define MAX_WORD_LENGTH 40

#define PRINT_FORMAT_SHORT      1
#define PRINT_FORMAT_DETAILED   2

#define WELCOME_SCREEN          1
#define ABOUT_SCREEN            2
#define HELP_SCREEN             3
#define GOODBYE_SCREEN          4
#define ERROR_SCREEN            5
#define WARRANTY_SCREEN         6 

enum word_type
{
    WORD_TYPE_ADJ,                      /* Adjective */
    WORD_TYPE_VERB,                     /* Verb */
    WORD_TYPE_NOUN,                     /* Noun */
    WORD_TYPE_ROOT,                     /* Root */
    WORD_TYPE_PERSON,                   /* Person */
    WORD_TYPE_THING,                    /* Thing */
    WORD_TYPE_OTHER,                    /* Other type */
    WORD_TYPE_MAX                       /* Max Types */
};

struct word
{
    char *word_name;                    /* Word Name */
    enum word_type word_type;           /* Word Type */
    char *word_meaning;                 /* Word Meaning */
    char *word_example;                 /* Word Example */
    int word_hits;                      /* Word Difficulty Level */
    int word_age;                       /* Age of the word */
};

struct word_node
{
    struct word *p_word;                /* Pointer to word structure */
    struct word_node *p_next;           /* Next pointer */
    struct word_node *p_prev;           /* Next pointer */
};

struct word_alphabet
{
    int word_count;                         /* No. of words of this alphabet */
    struct word_node *p_head_word_node;     /* Pointer to head word node */
    struct word_node *p_tail_word_node;     /* Pointer to tail word node */
};
