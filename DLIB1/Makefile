NAME = DLIB1.so
SRC = RenderSDL.cpp ErrorException.cpp
OBJ = $(SRC:.cpp=.o)
FRM = -F ../SDL/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer
GCC = clang++ -std=c++14 -c -Wall -Wextra -Werror
INC = -I ../SDL/SDL2.framework/Headers -I ../SDL/SDL2_ttf.framework/Headers -I ../SDL/SDL2_image.framework/Headers -I ../inc/

all: $(NAME)

$(NAME): $(OBJ)
	clang++ -shared  $(INC) $(OBJ) $(FRM) -o $(NAME)

$(OBJ):
	$(GCC) $(SRC) -fPIC $(INC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
