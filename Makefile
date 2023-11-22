# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 17:47:33 by jcoquard          #+#    #+#              #
#    Updated: 2023/11/20 13:27:39 by edecoste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $@ : NAME de la regle
# $^ : tous les OBJS
# $< : premiere dependance

GREY = \033[30m
RED = \033[31m
GREEN = \033[32m
ORANGE = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
LIGHTBLUE = \033[36m
WHITE = \033[37m

IRED=\033[41m
IWHITE=\033[47m
IBLUE=\033[44m
IPURPLE=\033[45m

END = \033[0m

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address 

SRCS = main.c \
		src/parsing/parsing.c \
		src/parsing/redirection.c \
		src/parsing/expand.c \
		src/tools/pars_utils.c \
		src/tools/redir_utils.c \
		src/tools/expand_utils.c \
		src/tools/error_utils.c \
		src/tools/splitcmds.c \
		src/tools/splitargs.c \
		src/tools/strcpy_neg.c \
		src/execution/execution.c \
		src/execution/exec_utils.c \
		src/environment/environment.c \
		src/signals/signals_handlers.c \
		src/signals/signals_hub.c \
		src/builtin/exit.c \
		src/builtin/env.c \
		src/builtin/export.c \
		src/heredoc.c

OBJS = ${SRCS:.c=.o}

HEADER = src/minishell.h

LEAKS = valgrind --suppressions=ignorerl.txt --leak-check=full --track-fds=yes

all:	 libs ${NAME}

${NAME}: ${OBJS}
		@ ${CC} ${FLAGS} ${OBJS} -o $@ -lreadline lib/libft/libft.a && echo "${GREEN}\n* ${NAME} compilation completed !!!\n${END}"

libs:
	${MAKE} -C lib/libft

%.o:	%.c ${HEADER}
		@ ${CC} ${FLAGS} -c $< -o $@  && echo "  $@"

clean:
		${MAKE} -C lib/libft clean
		@ ${RM} ${OBJS} && echo "${RED} * object cleared...${END}"

fclean: clean
		${MAKE} -C lib/libft fclean
		@ ${RM} ${NAME} && echo "${RED} * everything is cleared...${END}"

re: fclean
	${MAKE} all

leaks:
	clear
	$(MAKE) -j VALGRIND=yes
	$(LEAKS) ./minishell

sus:
		@echo "${BLUE}           ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀        ${END}"
		@echo "${BLUE}        ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀     ${END}"
		@echo "${BLUE}        ⣼⣿⠋       ${WHITE}⢀⣀⣀${BLUE}⠈⢻⣿⣿⡄    ${END}"
		@echo "${BLUE}       ⣸⣿⡏   ${WHITE}⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄   ${END}"
		@echo "${BLUE}       ⣿⣿⠁  ${WHITE}⢰⣿⣿⣯⠁       ⠈⠙⢿⣷⡄ ${END}"
		@echo "${BLUE}  ⣀⣤⣴⣶⣶⣿⡟   ${WHITE}⢸⣿⣿⣿⣆          ⣿⣷ ${END}"
		@echo "${BLUE} ⢰⣿⡟⠋⠉⣹⣿⡇   ${WHITE}⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿ ${END}"
		@echo "${BLUE} ⢸⣿⡇  ⣿⣿⡇    ${WHITE}⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃ ${END}"
		@echo "${BLUE} ⣸⣿⡇  ⣿⣿⡇     ${WHITE}⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛${BLUE}⢻⣿⡇  ${END}"
		@echo "${BLUE} ⠸⣿⣧⡀ ⣿⣿⡇                ⣿⣿⠃  ${END}"
		@echo "${BLUE}  ⠛⢿⣿⣿⣿⣿⣇     ⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿   ${END}"
		@echo "${BLUE}       ⣿⣿     ⣿⣿⡇ ⣽⣿⡏⠁  ⢸⣿⡇   ${END}"
		@echo "${BLUE}       ⣿⣿     ⣿⣿⡇ ⢹⣿⡆   ⣸⣿⠇   ${END}"
		@echo "${BLUE}       ⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁ ⠈⠻⣿⣿⣿⣿⡿⠏    ${END}"
		@echo "${BLUE}       ⠈⠛⠻⠿⠿⠿⠿⠋⠁              ${END}"
		@echo "$(IBLUE)         ░█▀▀░█░█░█▀▀         ${END}"
		@echo "$(IBLUE)         ░▀▀█░█░█░▀▀█         ${END}"
		@echo "$(IBLUE)         ░▀▀▀░▀▀▀░▀▀▀         ${END}"

.PHONY: all clean fclean re 
