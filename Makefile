# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 11:24:45 by mgayout           #+#    #+#              #
#    Updated: 2024/08/19 11:24:45 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv
FLAG	= -Wall -Wextra -Werror -std=c++98 -g3

SRCDIR	= src
OBJDIR	= obj
HEADIR	= include

SRC		= $(shell find $(SRCDIR) -name '*.cpp')
OBJ		= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
HEADER	= $(shell find $(HEADIR) -name '*.hpp')

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@c++ $(FLAG) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@c++ $(FLAG) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)


fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re