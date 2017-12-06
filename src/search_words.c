/*****************************************************************************
* 
* This file contains the routines for searching words from the database.
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
#include <ctype.h>
#include "word_types.h"
#include "word_prototypes.h"
#include "word_externs.h"

/*****************************************************************************
* 
* Routine to search a particular word from the database
*
*****************************************************************************/
struct word_node *search_word(char *word_name, enum word_type word_type)
{
    struct word_node *p_temp_node = NULL;
    int ret_val;
    char first_alpha;

#if 0 /* Fix for support of upper case and other symbolic characters */
    if ((word_name[0] < 'a') || (word_name[0] > 'z'))
    {
        /* Invalid word */
        return NULL;
    }
#endif

    first_alpha = word_get_first_alpha(word_name);
    if (first_alpha == 0)
    {
        /* Invalid word */
        return NULL;
    }

    p_temp_node = alphabet_array[first_alpha - 97]->p_head_word_node;
    while (p_temp_node != NULL)
    {
        ret_val = word_strcmp(word_name, p_temp_node->p_word->word_name
                    );
        if ((ret_val == 0) && (word_type == p_temp_node->p_word->word_type))
        {
            /* Found ! */
            return p_temp_node;
        }
        else if (ret_val < 0)
        {
            /* Word cannot be found further */
            break;
        }
        p_temp_node = p_temp_node->p_next;
    }

    return NULL;
}

/*****************************************************************************
* 
* Routine to search words matching a regular expression
*
*****************************************************************************/
void search_regexp(char *regexp, struct word_node **p_match_list)
{
    struct word_node *p_temp_node = NULL;
    char alpha = 'a';
    int i = 0;
    struct word_node *p_new_node = NULL, *p_prev_node = NULL;

    p_temp_node = alphabet_array[alpha - 97]->p_head_word_node;

    while (1)
    {
        if (NULL != p_temp_node)
        {
            if (MATCH == match_regexp(p_temp_node->p_word->word_name, regexp))
            {
                p_new_node = (struct word_node *)
                            malloc(sizeof(struct word_node));
                p_new_node->p_word = p_temp_node->p_word;
                p_new_node->p_next = NULL;
                p_new_node->p_prev = NULL;
                if (i == 0)
                {
                    *p_match_list = p_new_node;
                }
                else
                {
                    p_prev_node->p_next = p_new_node;
                    p_new_node->p_prev = p_prev_node;
                }
                p_prev_node = p_new_node;
                i++;
            }
        }
        else
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
        p_temp_node = p_temp_node->p_next;
    }
}

/*****************************************************************************
* 
* Routine to match words with a regular expression
*
*****************************************************************************/
int match_regexp(char *word_name, char *regexp)
{
    int i = 0, j = 0, state = 0;
    int final_state = 0;
    int no_of_stars = 0;
    char *tempstr = NULL;
    int regexp_len = strlen(regexp);
    int last_star_state = -1;
    int last_regexp_index = -1;
    char last_regexp_char = '\0';
    int word_len = 0;

    char *word = word_get_first_alpha_ptr(word_name);

    if ((NULL == word) || (NULL == regexp))
    {
        return NOMATCH;
    }

    word_len = strlen(word);
    tempstr = regexp;
    while ((tempstr = strchr(tempstr, '*')) != NULL)
    {
        no_of_stars ++;
        tempstr = tempstr + 1;
    }

    tempstr = regexp;
    while ((tempstr = strstr(tempstr, "*?")) != NULL)
    {
        *(tempstr++) = '?';
        *(tempstr++) = '*';
    }

    final_state = strlen(regexp) - no_of_stars;

    while (i < word_len)
    {
        if ((tolower(regexp[j]) == tolower(word[i])) || (regexp[j] == '?'))
        {
            i++;
            j++;
            state ++;
        }
        else if (regexp[j] == '*')
        {
            j++;
            last_regexp_index = j;
            last_star_state = state;
            last_regexp_char = regexp[j];
            if (j == regexp_len)
            {
                return MATCH;
            }
        }
        else
        {
            if (last_star_state >= 0)
            {
                if (tolower(word[i]) == tolower(last_regexp_char))
                {
                    state = last_star_state + 1;
                    j = last_regexp_index + 1;
                }
                else
                {
                    state = last_star_state;
                    j = last_regexp_index;
                }
            }
            else
            {
                return NOMATCH;
            }
            i++;
        }
    }
    if (state == final_state)
    {
        return MATCH;
    }
    return NOMATCH;
}
