![Welcome Screen](/vocabplus/images/screenshot_vocabplus_welcome.jpg?raw=true "Welcome Screen")

# Summary of Features

Following are listed the important features of this version of Vocab+:

1. Vocab+ is primarily a Vocabulary building tool for the English Language.
2. It provides support for adding new words, editing words already present in the database, or deleting words easily.
3. Words can be viewed or selected from lists, given the choice of selecting a particular alphabet, or all words.
4. Vocab+ provides a robust support for Vocabulary testing tools, including recalling words from their meanings, selecting the correct word given the meaning, and selecting the correct meaning given the word.
5. Vocab+ supports a "learning" Vocab Testing tool as well, which dynamically learns the difficulty levels of various words by constantly monitoring how the user fares in his tests. Thus the more difficult words are asked more frequently, giving the user more chances of mastering these words.
6. New words are marked with different color to give the user a chance to revise these words easily.
7. A Comprehensive test summary is generated after the completion of a test by the user, which includes information such as the pass percentage, average difficulty level of words encountered, number of new words added to vocabulary, and number of known words lost from the vocabulary. Thus the summary gives a fair idea to the user on how he/she is progressing in the vocabulary building process.
8. Searching words by specifying a "Regular Expression" is now supported!
9. And many more :-)

![Main Menu](/vocabplus/images/screenshot_main_menu.jpg?raw=true "Main Menu")

## Adding New Words

1. If you want to add new words to the word database of Vocab+, you can use the "Add Words" option in the Main Menu.
2. You will be asked for the word name, type and meaning. Make sure that both the word name and type do not already exist in the database, as it is not allowed to keep two words of the same name and type. If you attempt to do this, you will be warned against it.
3. In the "word type" field, you must select one of the options. In case you are not sure about the "type" of the word you are trying to add, it is advisable to select "other".
4. While entering the meaning, make sure that you do not enter beyong the red line cautioning against the same.
5. If all the entries are successfully entered, a message saying the same will be displayed. This added word can be viewed and verified using the "view words" option (see below).

![Add Words](/vocabplus/images/screenshot_add_words.jpg?raw=true "Add Words")

## Viewing Words

1. To view a particular word, which you are sure of the name and spelling, it is faster to select this option. Just enter the name of the word, and any matching entries will be displayed. There could be multiple matches (this will happen if the same word exists in the database under different types).
2. If you are interested in doing a sort of revision of ALL words, it is best to select the "view all words" option. All the words in the database will be displayed in alphabetical sequence. If it is not possible to display all words in a single screen, the "More" line will be displayed at the bottom. In that case, you can press any key to move to the next screen. Press 'Q' to quit the search, and go back to Main Menu.
3. If you are interested in viewing all words starting from a particular alphabet, it is best to select the "view single alphabet list" option. You will be asked to enter the desired alphabet, and all matches for the alphabet will be displayed as in the previous case.

![View Words](/vocabplus/images/screenshot_view_words.jpg?raw=true "View Words")

![View All Words](/vocabplus/images/screenshot_view_all_words.jpg?raw=true "View All Words")

## Searching Words

1. If you are searching for a particular word, but do not know the exact name, you can select the "select word from all list" option. This allows you to quickly browse through the list of all words, and displays only the word name and type. You can select a particular word for viewing by pressing the alphabet that is written in the "No" column next to the word, or scroll to next screen if the desired word is not found. If you select a word, a new screen displaying the detailed word with meaning, etc., will be displayed.
2. If you are searching for a particular word, but only know the alphabet that it starts with, but do not remember the exact name, you can select the "select word from single alphabet list" option. This will ask for the desired alphabet, and will allow you make a selection as in previous case.
3. You can search for matching words by specifying a regular expression. This feature is very useful if you remember only part of a word. The two special symbols you can use are '*' and '?'. '*' matches zero or more characters (any value), and '?' matches a single character. So, for example, if you can recall a word that starts with 'a' and ends with 't', you can specify the regular expression "a*t". The search will return all words starting with 'a' and ending with 't' and help you in locating your word. Another example is that if you know that the first character is 's' and third is 'o', you can specify the regular expression "s?o*", which will fetch you the desired matches.

![Search Words](/vocabplus/images/screenshot_search_words.jpg?raw=true "Search Words")

![Search Words](/vocabplus/images/screenshot_search_words_2.jpg?raw=true "Search Words")

## Editing Words

1. If you wish to edit the attributes of words, you can do so by selecting the "edit words" option from Main Menu.
2. If you want to edit a particular word that you know the exact name of, it is best to choose the "edit particular word" option. You will be asked to enter the name of the word, and if matches are found, you will select one of them (if > 1 matches are found). Once the word for editing is specified, you will be asked which attribute you would like to edit. It is possible to edit any of the attributes, including name, type, difficulty level and meaning.
3. It is important to note that if the word name and/or type are changed, and it is found that the new values clash with an already existing word in the database, the editing will be aborted. This is because of reasons mentioned in previous section.
4. In case you are not very sure of the word name that you would like to edit, you can choose the "select word from all list" option or "select word from single alphabet list" option, if you do not know or know the starting alphabet respectively.
5. Once the desired changes are made, the "done" option must be selected to bring the changes into effect. If successfully done, a message will be diplayed indicating the same.

![Edit Words](/vocabplus/images/screenshot_edit_words.jpg?raw=true "Edit Words")

![Edit Words](/vocabplus/images/screenshot_edit_words_2.jpg?raw=true "Edit Words")

## Deleting Words

1. If you wish to delete words from the word database, you can do so by selecting the "delete words" option from the Main Menu.
2. If you want to delete a particular word that you know the exact name of, it is best to choose the "delete particular word" option. You will be asked the name of the word, and if matches are found, you will select one of them (if > 1 matches are found). One the word for deletion is specified, Vocab+ will prompt you for confirmation if you are really sure you would like to delete the word :-)
3. In case you are not very sure of the word name that you would like to delete, you can choose the "select word from all list" option or "select word from single alphabet list" option, if you do not know or know the starting alphabet respectively.
4. Once the word is successfully deleted, a message will be displayed confirming the same.

## Vocabulary Tests

1. You can take vocabulary tests by selecting the "vocab test" option in the Main Menu.
2. Vocab+ provides a comprehensive set of vocabulary tests that you can take to enhance your vocabulary. You can select the list of words that you would like to be tested by giving a particular alphabet, or choose to be tested with ALL words.
3. Also, you can decide whether the ordering of the tests should be alphabetical, reverse-alphabetical or random in order.
4. The random "learning" test type is one of the smart features of Vocab+. This test dynamically learns how you are faring with various words during the test taking process, and tries to ask difficult words (which you have failed in earlier) more frequently than easier words.
5. The kind of test can be selected among the choices available. You can be asked to select the meaning from a list for a given word, or to select a word from a list, given the meaning. Also, to go one step further, you can choose to be asked to recall the word itself, given just the first alphabet of the word and its meaning.
6. A smart feature provided by Vocab+ is to allow you to select any of the tests above 'randomly', dynamically as the test is in progress.
7. In case of the tests for selecting a meaning or selecting a word from a list, you must enter the correct serial alphabet for the answer, and in case of the recalling the word type of test, you must complete the word after the first alphabet.
8. If you select the right answer or enter the right answer, your score is incremented, otherwise, it is not. The current score is printed at the top of the screen, as well as the test number and the current pass percentage.
9. You can review a word after taking a test for that word by pressing 'R'. You can quit the test any time, by pressing 'Q'.
10. After you quit the test, your complete test summary that is prepared by Vocab+ is displayed, with complete information about how you fared. This includes the total number of tests taken, the total number of tests passed and failed, and the pass percentage. Also, the average difficulty of the words taken is printed, giving you a fair idea on how well you fared vis-a-vis the difficulty. Also, and exciting information printed is the number of new words added to your vocabulary based on the results of the test, or those that you knew earlier but have now forgotted :-(. Do take this feedback seriously, and you will be able to track your progress effectively!

![Vocabulary Test](/vocabplus/images/screenshot_vocab_test.jpg?raw=true "Vocabulary Test")

![Vocabulary Test](/vocabplus/images/screenshot_vocab_test_2.jpg?raw=true "Vocabulary Test")

![Vocabulary Test](/vocabplus/images/screenshot_test_select_meaning.jpg?raw=true "Vocabulary Test")

![Vocabulary Test](/vocabplus/images/screenshot_test_select_word.jpg?raw=true "Vocabulary Test")

![Vocabulary Test](/vocabplus/images/screenshot_test_recall_word.jpg?raw=true "Vocabulary Test")

![Vocabulary Test](/vocabplus/images/screenshot_vocab_test_summary.jpg?raw=true "Vocabulary Test")

## Flushing Current Data to Disk

1. Vocab+ does not automatically synchronize the data that is changed during runtime (for example, when you add, edit or delete a word). Rather, it keeps the updated database in memory for performance, and does not keep writing to disk unnecessarily.
2. When you exit Vocab+ gracefully, it does write back the complete current database back to disk.
3. However, if you want to synchronize the disk with the current database (for example, after making several important changes that you want to get written immediately to disk, to obviate the risk of power failure, etc.), you can select the option "flush current data to disk" from Main Menu. This option does exactly what you want - it synchronizes the current data in memory to the one in the disk. (Thus the disk is updated with latest data).

## FAQs

Q) I'm not able to run Vocab+ on my system. When I run it, it doesn't display anything on the screen!
A) Probably your system does not support the screen based displays. Vocab+ requires screen based display support. This is present in most modern X-window based unix systems.

Q) When I try to take the vocab test, it says "Not enough words in the database". What does that mean?
A) This means that you do not have sufficient words in your word database. You must have atleast TEST_LIST_MAX number of words of each type in your database, as this is required for generating sufficient choices for selection during the tests. This macro is defined in word_types.h, and can be changed by you for your needs.

Q) I have observed a crash in the program. What do I do?
A) That is not surprising, since I have written this in such a hurry. If you can give me the exact situation in which you observed the fault, please do contact me with the details, and I will try to provide a fix asap.

Q) I have a few suggestions for improvement of Vocab+.
A) Please mail me those valuable suggestions and I will try to analyze them. Thanks.

Q) I would like to modify some part of Vocab+. Can I do that?
A) Vocab+ is free software, so you can modify and redistribute it. But it is protected by GNU General Public License, so you MUST comply to the license agreements before doing any modifications. Please go through the license (it is available with Vocab+ as well) carefully, and contact me if you still have any queries.
