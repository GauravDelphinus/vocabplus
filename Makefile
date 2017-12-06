##############################################################################
# MAKEFILE FOR MAIN FILES
##############################################################################
##############################################################################
#    Copyright (C) 2003 Gaurav Jain
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##############################################################################
##############################################################################
#   Revision History
#
#   Date         Updater          Comment
#   06-Sep-2003  Gaurav Jain      Initial Version
##############################################################################

CC=gcc
LD=ld

INCLUDE=-I. \
    -I$(VOCAB_PLUS_BASE_DIR)/h

#CFLAGS=  -c -DLOCAL_DEBUG -DMM_KER -DSIPALG_UT -g -Wall
CFLAGS=  -c -g -Wall 
LIBFLAGS= -lcurses

LDFLAGS= -r
TOTAL = $(CFLAGS) $(INCLUDE)

OBJ_DIR=$(VOCAB_PLUS_BASE_DIR)/obj
SRC_DIR=$(VOCAB_PLUS_BASE_DIR)/src

TARGET=$(OBJ_DIR)/vocab+.o

OBJ=$(OBJ_DIR)/main.o                       \
	$(OBJ_DIR)/screens.o  \
	$(OBJ_DIR)/main_loop.o  \
	$(OBJ_DIR)/add_words.o  \
	$(OBJ_DIR)/view_words.o  \
	$(OBJ_DIR)/edit_words.o  \
	$(OBJ_DIR)/search_words.o  \
	$(OBJ_DIR)/delete_words.o  \
	$(OBJ_DIR)/vocab_test.o  \
	$(OBJ_DIR)/flush_database.o  \
	$(OBJ_DIR)/load_database.o   \
	$(OBJ_DIR)/word_utils.o 

#top level rule

all:$(TARGET)
$(TARGET):	$(OBJ)
	$(LD)  -o $(OBJ_DIR)/vocab+.o $(LDFLAGS) $(OBJ)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(TOTAL) $< -o $@

vocab+:$(OBJ)
	$(CC)  $(LIBFLAGS) -o $@  $^

cleanall:clean
clean:
	rm -f $(OBJ_DIR)/*.o
	rm vocab+

