NAME = DLIB3.so
SRC = RenderOpenGL.cpp Shader.cpp Texture.cpp SpriteRenderer.cpp ErrorException.cpp
OBJ = $(SRC:.cpp=.o)
GCC = clang++ -Wall -Wextra -Werror -std=c++14
GLM = -L ../glm/
INC = -I ./stb_truetype.h -I ~/.brew/include -I$(HOME)/.brew/include/freetype2/ -I ../inc/
LIBS = -L ~/.brew/lib -lglfw -lglew -lfreetype -lftgl

all: $(NAME)

$(NAME):
	$(GCC) -shared -fPIC -o $(NAME) $(SRC) $(INC) $(LIBS) $(GLM) -framework OpenGL

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
