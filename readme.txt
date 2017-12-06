README FILE FOR VOCAB+
______________________

This file contains important information about the program 'Vocab+'. Please
go through this file before starting to use the program.

WARRANTY STATEMENT
__________________

Copyright (C) 2003  Gaurav Jain

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

CONTACT INFORMATION
___________________

For any queries regarding this program, the author can be contacted
by visiting the homepage of Vocab+.

Also, for latest updates to this software, you can visit the homepage
for Vocab+ at the following web address:
http://software.gauravjain.in/vocabplus

VOCAB+ 0.3
_______________________

NEW FEATURES:
1) Increased the maximum word length to 40 to accomodate larger length words.

BUG FIXES:

1) Fixed a segmentation fault that was occuring when the "Recall a word from
   its meaning" test was run, and an empty input was given.  Thanks to Mirko
(http://www.mabhods.de) for the bug report.

VOCAB+ 0.2
_______________________

NEW FEATURES:

1) Searching words by specifying a "Regular Expression" is now supported!
   For details on how to make use of this feature, refer to the help file.

BUG FIXES:

1) Corrected problem of last test not being included in the vocab
   test, and the floating point exception problem in case of single
   test taken.
2) Fixed the formatting of test screen title.

VOCAB+ 0.1 
(earlier called GJVocab)
_______________________

Following are listed the important features of this version of Vocab+:
1) Vocab+ is primarily a Vocabulary building tool for the English
   Language
2) It provides support for adding new words, editing words already
   present in the database, or deleting words easily.
3) Words can be viewed or selected from lists, given the choice of
   selecting a particular alphabet, or all words.
4) Vocab+ provides a robust support for Vocabulary testing tools,
   including recalling words from their meanings, selecting the 
   correct word given the meaning, and selecting the correct meaning
   given the word.
5) Vocab+ supports a "learning" Vocab Testing tool as well, which
   dynamically learns the difficulty levels of various words by
   constantly monitoring how the user fares in his tests.  Thus the
   more difficult words are asked more frequently, giving the 
   user more chances of mastering these words.
6) New words are marked with different color to give the user a 
   chance to revise these words easily.
7) A Comprehensive test summary is generated after the completion
   of a test by the user, which includes information such as the
   pass percentage, average difficulty level of words encountered,
   number of new words added to vocabulary, and number of known
   words lost from the vocabulary.  Thus the summary gives a fair
   idea to the user on how he/she is progressing in the vocabulary
   building process.
8) And many more :-)


COMPILATION AND INSTALLATION
____________________________

Normally Vocab+ is available in source code form, so the user 
must compile it for his environment.  The steps to be followed
for this are listed below.

1) Tar the "vocab+" folder to any suitable location in your unix
   system.  Let's say you tar all the files into the folder
   /user/gjain/vocab+
2) Make sure that the following files are present in the folder:
   ./word.db
   ./gpl.txt
   ./help.txt
   ./readme.txt
   ./Makefile
   ./src
   ./src/add_words.c
   ./src/delete_words.c
   ./src/edit_words.c
   ./src/flush_database.c
   ./src/load_database.c
   ./src/main.c
   ./src/main_loop.c
   ./src/screens.c
   ./src/search_words.c
   ./src/view_words.c
   ./src/vocab_test.c
   ./src/word_utils.c
   ./h
   ./h/word_externs.h
   ./h/word_prototypes.h
   ./h/word_types.h
   ./obj

   If any of the above files are missing, it means you have not got
   the correct archive, or your archive is corrupt.  Re-download the
   archive, and if you still face the same problem, contact me :-)
3) Set the environment variable below:
   export VOCAB_PLUS_BASE_DIR=/user/gjain/vocab+

   Note that the above is an example in case the shell is bash.  
   IMPORTANT: It is NECESSARY to have this path set even after 
   compilation, during execution of the program.  So it would be
   good to set this in your ".profile", or the like.
4) Now you are ready for compilation.  Just run make using the Makefile
   present.
   make               --> This would create the object files in ./obj
   make vocab+       --> This would create the executable ./vocab+
5) If everything has gone well, you have successfully created the 
   executable "vocab+" in the path VOCAB_PLUS_BASE_DIR.  You may add
   this path to the search path, generally "PATH" in your profile,
   so that you can run the program from any directory.
6) In case you face any problems that have not been answered, please
   contact me :-)
   
SYSTEM REQUIREMENTS
___________________

Any Unix Compatible operating system that supports X-Windows, and support
for screen based displays (that support the curses library).

BUG REPORTS
___________

If you find any bug in this software, please write with details of condition
in which to reproduce bug to me, and I will try my best to provide you with
a fix asap.  Thank you for your support.

REVISION HISTORY
________________

Revision    Date            Authors

0.3         04-Aug-2006     Gaurav Jain (gaurav@gauravjain.in)
0.2         05-Oct-2003     Gaurav Jain (gaurav@gauravjain.in)
0.1         07-Sep-2003     Gaurav Jain (gaurav@gauravjain.in)
