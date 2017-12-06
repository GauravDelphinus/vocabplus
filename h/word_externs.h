/*****************************************************************************
* 
* This header file contains extern declarations for global variables
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

extern struct word_alphabet *alphabet_array[26];
extern struct word_node **test_word_list;
extern struct word_node **test_difficulty_list;
extern struct word_node **test_adjective_list;
extern struct word_node **test_verb_list;
extern struct word_node **test_noun_list;
extern struct word_node **test_root_list;
extern struct word_node **test_person_list;
extern struct word_node **test_thing_list;
extern int word_count;
extern int adjective_count;
extern int verb_count;
extern int noun_count;
extern int root_count;
extern int person_count;
extern int thing_count;
extern long int curr_time;
