#include "functions.h"

int main(int argc, char** argv){
    int option;
    options(&option);
    switch(option){
        case 1:
            newGame(argc, argv);
            break;
        case 2:
            loadGame();
            break;
        case 3:
            fprintf(stdout, "Leaving...");
            exit(0);
            break;
        default:
            fprintf(stdout, "Wrong option! ");
            exit(1);
    }
    return 0;
}