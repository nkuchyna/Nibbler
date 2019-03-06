
NAME = nibbler
CLANG = clang++ -std=c++14 -Wall -Wextra -Werror
SRC_NAME = main.cpp Game.cpp DLibManager.cpp Snake.cpp Particle.cpp Menu.cpp Level.cpp RandomObjGenerator.cpp ErrorException.cpp
OBJ_NAME = $(SRC_NAME:.cpp=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./inc/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	make -C DLIB1
	make -C DLIB2
	make -C DLIB3
	make -C DLIB_SPlayer
	$(CLANG) $(OBJ) -o $(NAME)
$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	 mkdir -p $(OBJ_PATH)
	 $(CLANG) -c $< -o $@ $(INC)
clean:
	rm -f $(OBJ)
	make clean -C DLIB1
	make clean -C DLIB2
	make clean -C DLIB3
	make clean -C DLIB_SPlayer
fclean: clean
	rm -f $(NAME)
	make fclean -C DLIB1
	make fclean -C DLIB2
	make fclean -C DLIB3
	make fclean -C DLIB_SPlayer
re: fclean all
