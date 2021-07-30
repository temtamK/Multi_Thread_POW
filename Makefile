# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taemkim <taemkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/31 16:04:02 by taemkim           #+#    #+#              #
#    Updated: 2021/07/30 18:43:48 by taemkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = POW
SRC_PATH = srcs
HDR_PATH = includes
OBJ_PATH = obj

SRC_CODE =	block.c \
			pow.c \
			sha256.c \
			utils.c

OBJ_PRE= $(SRC_CODE:.c=.o)
SRC= $(addprefix $(SRC_PATH)/,$(OBJ_PRE))
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_PRE))

HDR_NAME =	block.h \
			sha256.h

HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))
FLAGS= -Wall -Wextra -Werror
H_FLAG= -I $(HDR_PATH)

COMP= gcc -g

all: $(NAME)

$(NAME) :  $(OBJ)
	@rm -rf $(NAME)
	@$(COMP) $(H_FLAG) $(OBJ) -o $@
	@echo "	Compilation of  $(NAME):  \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR)
	@mkdir -p $(OBJ_PATH) $(SWAP_PATH)
	@$(COMP)  $(FLAGS) $(H_FLAG)  -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[1;33m>> all .o files are deleted.\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[0;31m>> $(NAME) all obbjects are deleted.\033[0m"

re : fclean all
