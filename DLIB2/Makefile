NAME = DLIB2.so
SRC = RenderSFML.cpp ErrorException.cpp
OBJ = $(SRC:.cpp=.o)
GCC = clang++ -std=c++14 -Wall -Wextra -Werror
INC = -I ~/.brew/include -I ../inc/
LIBS = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -rpath ~/.brew/lib

all: $(NAME)

$(NAME):
	$(GCC) -shared -fPIC -o $(NAME) $(SRC) $(INC) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
