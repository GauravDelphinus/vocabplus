/*****************************************************************************
* 
* This source file contains routines for loading the word databases from 
* disk to memory.
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

struct word_alphabet *alphabet_array[26];
struct word_node **test_word_list = NULL;
struct word_node **test_difficulty_list = NULL;
struct word_node **test_adjective_list = NULL;
struct word_node **test_verb_list = NULL;
struct word_node **test_noun_list = NULL;
struct word_node **test_root_list = NULL;
struct word_node **test_person_list = NULL;
struct word_node **test_thing_list = NULL;
int word_count = 0;
int adjective_count = 0;
int verb_count = 0;
int noun_count = 0;
int root_count = 0;
int person_count = 0;
int thing_count = 0;
long int curr_time = 0;

/*****************************************************************************
* 
* Routine to load database to memory from disk
*
*****************************************************************************/
void load_database(void)
{
    FILE *p_input_file = NULL;
    char alpha = 'a';
    struct word_node *p_node = NULL, *prev_node = NULL;
    int next_line_flag = TRUE;
    int ret_val;
    char line[700];
    int i;
    char input_file[100], ftp_get_script[100];
    char error_str[150];
    char first_alpha;

    /* First Load the alphabet array */
    for (i = 0; i < 26; i++)
    {
        alphabet_array[i] = (struct word_alphabet *)malloc(sizeof(struct
                    word_alphabet));
        alphabet_array[i]->word_count = 0;
        alphabet_array[i]->p_head_word_node = NULL;
        alphabet_array[i]->p_tail_word_node = NULL;
    }

    /* Open input file */
    if (getenv("VOCAB_PLUS_BASE_DIR") == NULL)
    {
        sprintf(error_str, "Environment Variable \"VOCAB_PLUS_BASE_DIR\" Not Set.");
        error_exit(error_str);
    }

    strcpy(input_file, getenv("VOCAB_PLUS_BASE_DIR"));
    strcat(input_file, "/word.db");
    p_input_file = fopen(input_file, "r");
    if (NULL == p_input_file)
    {
        sprintf(error_str, "Error opening input database '%s'.", input_file);
        error_exit(error_str);
    }

    while (1)
    {
        if (TRUE == next_line_flag)
        {
            ret_val = fscanf(p_input_file, " %[^\n]", line);
            if (ret_val == EOF)
            {
                /* Reached end of file, break from loop */
                break;
            }
            p_node = create_node(line);
            next_line_flag = FALSE;
        }

        first_alpha = word_get_first_alpha(p_node->p_word->word_name);
        if (first_alpha > alpha)
        {
            /* if alpha is less than the line word, move ahead in array */
            alpha ++;
            continue;
        }
        else if (first_alpha == alpha)
        {
            /* if alpha matches the line word, good */
            if (alphabet_array[alpha - 97]->p_head_word_node == NULL)
            {
                /* This is the first node for this alphabet */
                alphabet_array[alpha - 97]->p_head_word_node = p_node;

                p_node->p_prev = NULL;
            }
            else
            {
                if (NULL != prev_node)
                {
                    prev_node->p_next = p_node;
                }
                p_node->p_prev = prev_node;
            }

            prev_node = p_node;
            alphabet_array[alpha - 97]->word_count ++;
            word_count ++;
            switch (p_node->p_word->word_type)
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
            alphabet_array[alpha - 97]->p_tail_word_node = p_node;
            next_line_flag = TRUE;
        }
        else
        {
            /* Error - this should NOT happen !! */
            error_exit("Error encountered while parsing input database.");
        }
    }
}

/*****************************************************************************
* 
* Routine to create a new node from the read line of input
*
*****************************************************************************/
struct word_node *create_node(char *line)
{
    char *p_word_name = NULL, *p_word_type = NULL, *p_word_hits = NULL,
    *p_word_meaning = NULL, *p_word_age = NULL, *p_word_example = NULL;
    struct word_node *p_node = NULL;
    struct word *p_word = NULL;
    char temp_str[20];

    /* The line format is of this type */
    /* word<TAB>word-type<TAB>word-difficulty<TAB>word-age<TAB>word-meaning<TAB>word-example<CRLF> */

    p_word_name = line;
    p_word_type = strchr(line, '\t') + 1;
    p_word_hits = strchr(p_word_type, '\t') + 1;
    p_word_age = strchr(p_word_hits, '\t') + 1;
    p_word_meaning = strchr(p_word_age, '\t') + 1;
    p_word_example = strchr(p_word_meaning, '\t') + 1;

    /* Allocate word structure */
    p_word = (struct word *)malloc(sizeof(struct word));

    /* Allocate and Fill word name */
    p_word->word_name = (char *)malloc(sizeof(char) * 
            (p_word_type - p_word_name));
    strncpy(p_word->word_name, p_word_name, (p_word_type - p_word_name - 1));
    p_word->word_name[p_word_type - p_word_name - 1] = '\0';

    /* Fill word type */
    strncpy(temp_str, p_word_type, (p_word_hits - p_word_type - 1));
    temp_str[p_word_hits - p_word_type - 1] = '\0';
    if (word_strcmp(temp_str, "adjective") == 0)
    {
        p_word->word_type = WORD_TYPE_ADJ;
    }
    else if (word_strcmp(temp_str, "verb") == 0)
    {
        p_word->word_type = WORD_TYPE_VERB;
    }
    else if (word_strcmp(temp_str, "noun") == 0)
    {
        p_word->word_type = WORD_TYPE_NOUN;
    }
    else if (word_strcmp(temp_str, "root") == 0)
    {
        p_word->word_type = WORD_TYPE_ROOT;
    }
    else if (word_strcmp(temp_str, "person") == 0)
    {
        p_word->word_type = WORD_TYPE_PERSON;
    }
    else if (word_strcmp(temp_str, "thing") == 0)
    {
        p_word->word_type = WORD_TYPE_THING;
    }
    else if (word_strcmp(temp_str, "other") == 0)
    {
        p_word->word_type = WORD_TYPE_OTHER;
    }
    else
    {
        error_exit("Invalid Word Type found in database.");
    }
    
    /* Fill word difficulty */
    strncpy(temp_str, p_word_hits, (p_word_age - p_word_hits - 1));
    temp_str[p_word_age - p_word_hits - 1] = '\0';
    p_word->word_hits = atoi(temp_str);

    /* Fill word age */
    strncpy(temp_str, p_word_age, (p_word_meaning - p_word_age - 1));
    temp_str[p_word_meaning - p_word_age - 1] = '\0';
    p_word->word_age = atoi(temp_str);

    /* Allocate and Fill word meaning */
    p_word->word_meaning = (char *)malloc(sizeof(char) * 
            (p_word_example - p_word_meaning));
    strncpy(p_word->word_meaning, p_word_meaning, 
		    	p_word_example - p_word_meaning - 1);
    p_word->word_meaning[p_word_example - p_word_meaning - 1] = '\0';

    /* Allocate and Fill word example */
    p_word->word_example = (char *)malloc(sizeof(char) * 
            (strlen(p_word_example) + 1));
    strncpy(p_word->word_example, p_word_example, strlen(p_word_example));
    p_word->word_example[strlen(p_word_example)] = '\0';

    p_node = (struct word_node *)malloc(sizeof(struct word_node));
    p_node->p_word = p_word;
    p_node->p_next = NULL;

    return p_node;
}
