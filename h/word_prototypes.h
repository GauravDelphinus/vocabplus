/*****************************************************************************
* 
* This header file contains prototypes for all the functions.
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

void load_database(void);
struct word_node *create_node(char *line);
void main_loop(void);
void add_words(void);
void view_words(void);
void edit_words(void);
void delete_words(void);
void flush_database(void);
void vocab_test(void);
void shut_down(void);
struct word_node *search_word(char *word_name, enum word_type word_type);
void add_word(char *word_name, enum word_type word_type, char *word_meaning,
        int word_hits, char *word_example);
void view_particular_word(void);
void view_all_list(void);
void view_alphabet_list(void);
void select_word_from_all_list(void);
void select_word_from_alphabet_list(void);
int ok_to_print_detailed(int serial_no, struct word_node *p_node);
int print_word_short(int serial_no, struct word_node *p_node, int choice_flag);
int print_word_detailed(int serial_no, struct word_node *p_node, int choice_flag);
void edit_particular_word(void);
void edit_word_from_all_list(void);
void edit_word_from_alphabet_list(void);
void edit_word(struct word_node *p_node);
void delete_word(struct word_node *p_node);
void delete_particular_word(void);
void delete_word_from_all_list(void);
void delete_word_from_alphabet_list(void);
int word_strcmp(char *string1, char *string2);
void test_vocab_all_word_list_alphabetical(int test_type);
void test_vocab_all_word_list_rev_alphabetical(int test_type);
void test_vocab_all_word_list_random(int test_type);
void test_vocab_single_alphabet_list_alphabetical(int test_type);
void test_vocab_single_alphabet_list_rev_alphabetical(int test_type);
void test_vocab_single_alphabet_list_random(int test_type);
void test_vocab_all_word_list_random_learning(int test_type);
int test_vocab(int serial_number, struct word_node *p_node, int test_type,
        int *p_result);
int word_random(int low, int high);
int test_vocab_select_meaning_from_list(int serial_number, struct word_node
        *p_node, int *p_result);
int test_vocab_select_word_from_list(int serial_number, struct word_node
        *p_node, int *p_result);
int test_vocab_recall_word(int serial_number, struct word_node *p_node, int
        *p_result);
void generate_test_symbol_tables(void);
void free_test_symbol_tables(void);
char word_getchar(void);
void print_test_summary(int pass, int fail, int difficulty_sum, 
        int words_added, int words_lost);
void print_title(char *title);
void print_subtitle(char *title);
void print_wordtitle(int type);
void print_testtitle(int serial_no, int pass, int fail);
void print_meaning(char *meaning);
int get_bigger_test_list (struct word_node ***p_word_list);
void print_screen(int screen_type);
void error_exit(char *error_str);
char word_get_first_alpha(char *word_name);
char *word_get_first_alpha_ptr(char *word_name);
void search_words(void);
void search_regexp(char *regexp, struct word_node **p_match_list);
int match_regexp(char *word, char *regexp);
void catch_time_tick();
void print_time_spent();


