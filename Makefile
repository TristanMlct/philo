# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmilcent <tmilcent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 19:16:06 by tmilcent          #+#    #+#              #
#    Updated: 2023/09/18 02:13:34 by tmilcent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

GCC = gcc -Wall -Wextra -Werror

SRCS = 	src/main.c \
		src/input/check_input.c \
		src/init/init_structs.c \
		src/init/init_thread.c \
		src/utils/utils.c \
		src/utils/logs.c \
		src/utils/mutex.c \
		src/utils/mutex2.c \
		src/actions/actions.c \

OBJS = $(SRCS:.c=.o)

INC = inc/

all: $(NAME)

%.o: %.c
	@$(GCC) -c $< -o $@


$(NAME): $(OBJS)
	@$(GCC) -pthread -I $(INC) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re