NAME = DLIB_SPlayer.so
SRC = SPLayerSDL.cpp ErrorException.cpp
OBJ = $(SRC:.cpp=.o)
FRM = -F ../SDL/ -framework SDL2 -framework SDL2_mixer
GCC = clang++ -std=c++14 -c -Wall -Wextra -Werror
INC = -I ../SDL/SDL2.framework/Headers -I ../SDL/SDL2_mixer.framework/Headers -I ../inc/

all: $(NAME)

$(NAME):
	$(GCC) $(SRC) -fPIC $(INC)
	clang++ -shared  $(INC) $(OBJ) $(FRM) -rpath @loader_path/SDL  -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all