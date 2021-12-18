#include "functions.h"

void options(int *option){
    fprintf(stdout, "\033[0;37m-----------------------------\n");
    fprintf(stdout, "| (1) -\033[0;31m New game\033[0;37m\t    |\n| (2) -\033[0;31m Load previous game\033[0;37m  |\n| (3) -\033[0;31m Exit\t\t    \033[0;37m|\n");
    fprintf(stdout, "-----------------------------\n");
    fprintf(stdout, "Option: ");
    fscanf(stdin, "%d", option);
}

void newGame(int argc, char** argv){
    int mines = NumofMines(argc, argv);
    int tipps = 100 - mines;
    //Create fields, and fill them with given characters
    char** field = (char**)malloc(sizeof(char*)*10);
    char** revealed = (char**)malloc(sizeof(char*)*10);
    if(field == NULL || revealed == NULL){
        fprintf(stderr, "Memory allocation failed!");
        exit(1);
    }
    for(int i = 0; i < 10; i++){
        field[i] = (char*)malloc(sizeof(char)*10);
        revealed[i] = (char*)malloc(sizeof(char)*10);
        if(field[i] == NULL || revealed[i] == NULL){
            fprintf(stderr, "Memory allocation failed!");
            exit(1);
        }
        for(int j = 0; j < 10; j++){
            field[i][j] = '0';
            revealed[i][j] = ' ';
        }
    }
    InsertMines(field, mines);
    FillField(field);
    Game(field,revealed,&tipps);
}

void loadGame(){
    char** field = (char**)malloc(sizeof(char*)*10);
    char** revealed = (char**)malloc(sizeof(char*)*10);
    if(field == NULL || revealed == NULL){
        fprintf(stderr, "Memory allocation failed!");
        exit(1);
    }
    for(int i = 0; i < 10; i++){
        field[i] = (char*)malloc(sizeof(char)*10);
        revealed[i] = (char*)malloc(sizeof(char)*10);
        if(field[i] == NULL || revealed[i] == NULL){
            fprintf(stderr, "Memory allocation failed!");
            exit(1);
        }
    }
    int tipps;
    loading(field, revealed, &tipps);
    PrintField(revealed);
    Game(field,revealed,&tipps);
}

void loading(char** field, char** revealed, int* tipps){
    FILE* f = fopen("save.txt", "r");
    if(f == NULL){
        fprintf(stderr, "File opening unsuccessful!");
        exit(1);
    }
    char a[102];
    char b[102];
    fgets(a, 102, f);
    fgets(b, 102, f);
    fscanf(f, "%d", tipps);
    fclose(f);
    for(int i = 0; i < 100; i++){
		revealed[i/10][i%10] = a[i];
		field[i/10][i%10] = b[i]-15-(i/10); // decrypting 
	}
}

int NumofMines(int argc, char** argv){
    if(argc > 1){
        //Command line argument
        int mine = atoi(argv[1]);
        if(mine < 3 || mine > 30){
			do{
				fprintf(stdout, "You have given a wrong number!\n");
				fscanf(stdin, "%d", &mine);
			}while(mine < 3 || mine > 30);
		}
		return mine;
    }
    else{
        //Input
        int mine = 0;
        do{
            fprintf(stdout, "Give me a number [3-30]! ");
            fscanf(stdin, "%d", &mine);
		}while(mine < 3 || mine > 30);
        return mine;
    }
}

void InsertMines(char** field, int mines){
    srand(time(NULL));
    int x, y;
    for(int i = 0; i < mines; i++){
		do{
			x = rand() % 10;
			y = rand() % 10;
		}while(field[x][y] == '*');
		field[x][y] = '*';
	}
}

void PrintField(char** field){
    fprintf(stdout, "  \033[0;35m0 1 2 3 4 5 6 7 8 9\033[0;37m\n");
    for(int i = 0; i < 10; i++){
        fprintf(stdout, "\033[0;35m%c\033[0;37m", 'A'+i);
        for(int j = 0; j < 10; j++){
            if(field[i][j] == '*'){
                fprintf(stdout, " \033[0;33m%c\033[0;37m", field[i][j]);
            }
            else{
                fprintf(stdout, " %c", field[i][j]);
            }
        }
        fprintf(stdout, "\n");
    }
}

void FillField(char** field){
    for(int i = 0; i < 10; i++){
        for(int k = 0; k < 10; k++){
            if(field[i][k] == '*'){
                continue;
            }
            int counter = 0;
            for(int j = -1; j <= 1; j++){
                for(int l = -1; l <= 1; l++){
                    int x = i + j;
                    int y = k + l;
                    if(x >= 0 && x <= 9 && y >= 0 && y <= 9 && field[x][y] == '*'){
                        counter++;
                    }
                }
            }
            field[i][k] = counter + '0';
        }
    }
}

void saving(char** field, char** revealed, int tipps){
    FILE* f = fopen("save.txt", "w+");
    for(int i = 0; i < 10; i++){
		for(int k = 0; k < 10; k++){
			fprintf(f, "%c", revealed[i][k]);
		}
	}
	fprintf(f, "\n");
	for(int i = 0; i < 10; i++){
		for(int k = 0; k < 10; k++){
            //Encrypting the field in order to be invisible for the player 
			fprintf(f, "%c", field[i][k]+15+i);
		}
	}
    fprintf(f, "\n");
    fprintf(f, "%d", tipps);
	fclose(f);
    fprintf(stdout, "Saving was successful");
}

int check(char** revealed, char* coordinate){
    if(strcmp(coordinate, "save") == 0){
        return 0;
    }
    if(strlen(coordinate) != 2){
        return 2;
    }
    char x = coordinate[0];
    char xx[] = "ABCDEFGHIJ";
    char y = coordinate[1];
    char yy[] = "0123456789";
    int counter = 0;
    int i = 0;
    //Check if a coordinates look like this: A0
    while(i < 10 && counter != 2){
        if(x == xx[i]){
            counter++;
        }
        if(y == yy[i]){
            counter++;
        }
        i++;
    }
    if(counter == 2){
        //Check if the coordinate is revealed
        if(revealed[x-65][y-48] == ' '){
            return 1;
        }
    }
    return 2;
}

void rev(char** field, char** revealed, int a, int b, int* tipps){
    for(int j = -1; j <= 1; j++){
        for(int l = -1; l <= 1; l++){
            if(!(j == 0 && l == 0)){
                int x = a + j;
                int y = b + l; 
                if(x >= 0 && x <= 9 && y >= 0 && y <= 9 && field[x][y] != '*' && revealed[x][y] == ' '){
                    --*tipps;
                    if(field[x][y] == '0'){
                        revealed[x][y] = field[x][y];
                        rev(field,revealed,x,y,tipps); 
                    }
                    else{
                        revealed[x][y] = field[x][y];
                    }
                }
            }
        }
    }
}

void freeMemory(char** field, char** revealed){
    for(int i = 0; i < 10; i++){
        free(field[i]);
        free(revealed[i]);
    }
    free(field);
    free(revealed);
}

void Game(char** field, char** revealed, int* tipps){
    if(*tipps == 0){
        fprintf(stdout, "-----------------------------\n");
        fprintf(stdout, "\033[0;31mYou won the game!\nYou won the game!\033[0;37m\n");
        PrintField(field);
        freeMemory(field, revealed);
        exit(0);
    }
    //Get the coordinate
    char coordinate[10];
    fprintf(stdout, "-----------------------------\n");
    fprintf(stdout, "\033[0;32mCoordinate:\033[0;34m ");
    fscanf(stdin, "%s", coordinate);
    fprintf(stdout, "\033[0;37m");
    int option;
    while((option = check(revealed, coordinate)) == 2){
        fprintf(stderr, "\033[0;31mWrong coordinate!\033[0;32m Coordinate:\033[0;34m ");
        fscanf(stdin, "%s", coordinate);
        fprintf(stdout, "\033[0;37m");
    }
    switch(option){
        case 0:
            //Saving current state
            saving(field, revealed, *tipps);
            freeMemory(field, revealed);
            exit(0);
        case 1:
            //Revealing appropriate coordinate
            --*tipps;
            int x = coordinate[0] - 65;
            int y = coordinate[1] - 48; 
            if(field[x][y] == '*'){
                fprintf(stdout, "\033[0;31mBOMB\nBOMB\nBOMB\nYou lost!\n\033[0;37m");
                PrintField(field);
                freeMemory(field, revealed);
                exit(0);
            }
            revealed[x][y] = field[x][y];
            if(field[x][y] == '0'){
                rev(field, revealed, x, y, tipps);
            }
            fprintf(stdout, "Correct guess!\nNumber of remained tipps:\033[0;34m %d\n\033[0;37m", *tipps);
            PrintField(revealed);
            Game(field, revealed, tipps);
            break;
        default:
            fprintf(stderr, "Impossible case :)");
            freeMemory(field, revealed);
            exit(1);
    }
}
