# ********************************************************************************** #
#                                                                                    #
#                                                      :::::::::: :::::::::   :::::: #
#   Makefile                                          :+:        :+:    :+: :+:    : #
#                                                    +:+        +:+    +:+ +:+       #
#   By: flaviobc <github.com/GitFlaviobc>           :#::+::#   +#++:++#+  +#+        #
#                                                  +#+        +#+    +#+ +#+         #
#   Created: 2026/05/06 20:22:01 by flaviobc      #+#        #+#    #+# #+#    #+#   #
#   Updated: 2026/05/06 20:22:01 by flaviobc     ###        #########   ########     #
#                                                                                    #
# ********************************************************************************** #

NAME = linearAlgebra

MAIN = main/
INCLUDE_DIR = includes/linear
SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = $(MAIN)main.cpp

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEADERS = $(INCLUDE_DIR)/linearAlgebra.hpp \
          $(INCLUDE_DIR)/Vector.hpp \
          $(INCLUDE_DIR)/Matrix.hpp

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors -g -O2 -I$(INCLUDE_DIR)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(MAIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re run
