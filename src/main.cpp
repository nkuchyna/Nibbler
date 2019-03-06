
#include "Game.h"
#include "ErrorException.h"
#include <stdexcept>
#include <dlfcn.h>
#include "DLibManager.h"

int main(int arc, char **argv) {

    if (arc == 3)
    {
        try
        {
            Game    newGame(argv[1], argv[2]);
            newGame.runGameLoop();
        }
        catch (ErrorException &e)
        {
            std::cout <<"Error: "<< e.getError()<<std::endl;
        }
        catch (std::exception &e)
        {
            if (dynamic_cast<std::out_of_range*>(&e) != NULL) {
                std::cout << "Error! Out of range!" << std::endl;
                return (1);
            }
            else if (dynamic_cast<ErrorException*>(&e) == NULL)
                std::cout << "Error! Inappropriate indicating of window's sizes!" << std::endl;
        }
    }
    else
        std::cout << "usage ./nibbler [width] [height]" << std::endl;
    return 0;
}
