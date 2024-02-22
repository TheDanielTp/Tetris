#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <thread>
#include <iomanip>


using namespace std;

// -----------------------------------global variables:
// struct
struct scoreboards {
    string name;
    int score;
    int time;
};
scoreboards scoreboard[200];
int struct_counter = 0;


// main Array
int **mainArr;

// shapes
int shape_one[3][3] = {{0, 0, 0}, {1, 1, 0}, {0, 1, 1}}; 
int shape_two[3][3] = {{0, 0, 0}, {0, 2, 2}, {2, 2, 0}};
int shape_three[3][3] = {{0, 0, 0}, {0, 3, 0}, {3, 3, 3}};
int shape_four[3][3] = {{4, 4, 0}, {4, 0, 0}, {4, 0, 0}};
int shape_five[3][3] = {{0, 5, 5}, {0, 0, 5}, {0, 0, 5}};
int shape_six[2][2] = {{6, 6}, {6, 6}};
int shape_seven[4][4] = {{0, 7, 0, 0}, {0, 7, 0, 0}, {0, 7, 0, 0}, {0, 7, 0, 0}};
int shape_size_list[7] = {3, 3, 3, 3, 3, 2, 4}; 
int temp_shape[4][4];


// in game
int length = 25;
int width = 10; 
int score = 0;
chrono::high_resolution_clock::time_point startTime;
chrono::high_resolution_clock::time_point currentTime;
int Time = 0;
int Pausetime;
string name = "name";
int speed = 1;


// shape_selection
int current_shape;
int next_shape;
int hold_shape;

// ----------shape's location
int i_current_shape;
int j_current_shape;

// shadow:
int i_shadow;
int j_shadow;

//bools:
bool quit = false;
bool restart = false;
bool gameover = false;


// -------------------------------------functions:
void menu();
void cration_new_game();
int fileLineCounter();
void cearateArray();
void rotate_clockwise();
void rotate_counterclockwise();
int random();
void show_game();
void locating_shape();
void running_game();
void crating_temp_shape();
bool check_down();
bool check_right();
bool check_left();
bool check_rotation();
void shift_down(int i);
void pause();
void do_down();
void gotoxy(int x, int y);
void get_info();
// void update();
// void update_right();
// void update_left();
// void update_rotation();
// void update_Cdowm();
void delete_Arr();
void check_gameover();
void find_shadow_loc();
void do_hold();
bool check_hold();
void get_info_advansed();
void write_score();
void read_score();
void sort();
void leaderboard();
void save_to_struct();
void howToPlay(string txt);


// main code:
int main(){
    read_score();
    menu(); 
}


// function definitions:
void gotoxy(int x, int y){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {(short)x, (short)y};
    SetConsoleCursorPosition(hStdout, position);
}

void menu(){
    system("cls");
    int menu_counter = 1;
    while (true){
        cout << endl;
        cout << "\t" << "\u250C";
        for(int i = 0; i < 45; i++)
            cout << "\u2500";
        cout << "\u2510" << endl;
        cout << "\t" << "\u2502";
        for(int i = 0; i < 45; i++)
            cout << " ";
        cout << "\u2502" << endl;
        cout << "\t" << "\u2502";
        cout << "                 Tetris Game                 ";
        cout << "\u2502" << endl;
        cout << "\t" << "\u2502";
        for(int j = 0; j < 45; j++)
            cout << " ";
        cout << "\u2502" << endl;
		//------------------------------------------ new game: 
        if(menu_counter == 1){
            cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "New Game  ";
            for (int i = 0; i < 30; i++)
                cout << " ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;                                                                                                      
        }
        else{
            cout << "\t" << "\u2502";
            cout << "  " << "New Game  ";
            for (int i = 0; i < 33; i++)
                cout << " ";
            cout << "\u2502" << endl;
            if (menu_counter != 2 && menu_counter != 3 && menu_counter != 4){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        //------------------------------------------ scoreboard: 
        if(menu_counter == 2){
        	cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "Leaderboard";
            for (int i = 0; i < 29; i++)
                cout << " ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;  
        }
        else{
            if (menu_counter != 1 && menu_counter != 3 && menu_counter != 4){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t" << "\u2502";
            cout << "  " << "Leaderboard";
            for (int i = 0; i < 32; i++)
                cout << " ";
            cout << "\u2502" << endl;
            if (menu_counter != 3 && menu_counter != 1 && menu_counter != 4){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        //------------------------------------------ how to play: 
        if(menu_counter == 3){
        	cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "How To Play";
            for (int i = 0; i < 29; i++)
                cout << " ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;  
        }
        else{
            if (menu_counter != 2 && menu_counter != 1 && menu_counter != 4){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t" << "\u2502";
            cout << "  " << "How To Play";
            for (int i = 0; i < 32; i++)
                cout << " ";
            cout << "\u2502" << endl;
            if (menu_counter != 2 && menu_counter != 1 && menu_counter != 4){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
		//------------------------------------------ exit: 
        if(menu_counter == 4){
        	cout << "\t" << "\u2502" << " ";
            cout << "\033[0;31m";
            cout << "\u250C";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " " << "\033[0;31m" << "\u2502" << " ";
            cout << "Exit      ";
            for (int i = 0; i < 30; i++)
                cout << " ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t" << "\u2502" << " ";
            cout << "\033[0;31m";
            cout << "\u2514";
            for (int i = 0; i < 41; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;  
        }
        else{
            if (menu_counter != 2 && menu_counter != 1 && menu_counter != 3){
                cout << "\t" << "\u2502";
                for(int i = 0; i < 45; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t" << "\u2502";
            cout << "  " << "Exit      ";
            for (int i = 0; i < 33; i++)
                cout << " ";
            cout << "\u2502" << endl;
        }
        
        // ---------------------------------------------------
        for(int i = 0; i < 20; i++){
            cout << "\t" << "\u2502";
            for(int j = 0; j < 45; j++)
                cout << " ";
            cout << "\u2502" << endl;
        }
        cout << "\t" << "\u2514";
        for(int i = 0; i < 45; i++)
            cout << "\u2500";
        cout << "\u2518" << endl;

        char chr = getch();
        while (chr != 72 && chr != 80 && chr != 13)
            chr = getch();
        if( chr == 72 && menu_counter > 1)
            menu_counter--;
        else if( chr == 80 && menu_counter < 4)
            menu_counter++;
        else if(chr == 13)
        	break;
		
        system("cls");
    }
    if(menu_counter == 4){
        system("cls");
        write_score();
        exit(0);
    }
    else if (menu_counter == 1){
        system("cls");
        cration_new_game();
	}
	else if (menu_counter == 2){
        leaderboard();
        getch();
        menu();
	}
	else if (menu_counter == 3){
        system("cls");
        string txt = {"Tetris is an interesting puzzle game in which you have to put blocks of different shapes together to form solid lines without gaps.\nTo start the game, you need to familiarize yourself with the game screen.\nThe game usually consists of a well from which blocks of different known as tetriminos, fall.\nYou can use the arrow keys on your keyboard left(A) or right(D) to move the blocks.\nBy ppressing the key:\n1- Downward arrow: Blocks descend one by one.\n2- space: Blockssuddenly come down completely.\n3- x: Blocks rotate clockwise.\n4- z: Blocks rotate counter-clockwise.\n5- esc: The interrupt menu opens.\n6- h(hold): The current shape is replaced by the new shape.\nTo clear lines, you need to fill a complete horizontal line with blocks to make the line disapear and earn points.\nTo return to menu, press any key."};
        howToPlay(txt);
        getch();
        menu();
	}
}

void cration_new_game(){
    int cng_counter = 1;
    while (true){
        for(int i = 0; i < 6; i++)
            cout << endl;
        cout << "\t\t" << "\u250C";
        for(int i = 0; i < 20; i++)
            cout << "\u2500";
        cout << "\u2510" << endl;
        cout << "\t\t" << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502" << endl;

        //----------------------------------------- beginner
        if (cng_counter == 1){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "   Beginner    ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            cout << "\t\t" << "\u2502";
            cout << "      Beginner      ";
            cout << "\u2502" << endl;
            if (cng_counter != 2 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        //----------------------------------------- Advanced
        if (cng_counter == 2){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "   Advanced    ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            if (cng_counter != 1 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t\t" << "\u2502";
            cout << "      Advanced      ";
            cout << "\u2502" << endl;
            if (cng_counter != 1 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        if (cng_counter == 3){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "     Back      ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            if (cng_counter != 2 && cng_counter != 1){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t\t" << "\u2502";
            cout << "        Back        ";
            cout << "\u2502" << endl;
            if (cng_counter != 2 && cng_counter != 1){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        cout << "\t\t" << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502" << endl;
        cout << "\t\t" << "\u2514";
        for(int i = 0; i < 20; i++)
            cout << "\u2500";
        cout << "\u2518" << endl;

        char chr = getch();
        while (chr != 72 && chr != 80 && chr != 13)
            chr = getch();
        if( chr == 72 && cng_counter > 1)
            cng_counter--;
        else if( chr == 80 && cng_counter < 3)
            cng_counter++;
        else if(chr == 13)
            break;
        system("cls");
    }
    if(cng_counter == 3){
        menu();
    }
    else if (cng_counter == 1){
        get_info();
        cearateArray();
        running_game();
        while (restart){
            restart = false;
            delete_Arr();
            cearateArray();
            running_game();
        }
	}
	else if (cng_counter == 2){
        get_info_advansed();
        cearateArray();
        running_game();
        while (restart){
            restart = false;
            delete_Arr();
            cearateArray();
            running_game();
        }
	}
}

int fileLineCounter(){
    ifstream file("scores.txt");
    int count = 0;
    if (file.is_open()){
        string line;
        while (getline(file, line))
            count++;
        file.close();
        return count;
    }
    else
        return 0;
}

void cearateArray(){
    mainArr = new int*[length];
    for (int i = 0; i < length; i++)
        mainArr[i] = new int[width];
    for (int i = 0; i < length; i++)
        for (int j = 0; j < width; j++)
            if (j == 0 || j == width - 1 || i == length - 1)
                mainArr[i][j] = -1;
            else
                mainArr[i][j] = 0;
}

void show_game(){ 
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    //--------------------- first line
    gotoxy(8, 4);
    cout << "\u250C";
    for(int i= 0; i < 2 * (width - 2); i++)
        cout << "\u2500";
    cout << "\u2510";
    //--------------------

    //-------------------- arr body
    for(int i = 3; i < length - 1; i++){
        gotoxy(8, 5 - 3 + i);
        cout << "\u2502";
        for (int j = 1; j < width - 1; j++){
            if (mainArr[i][j] == 0){
                SetConsoleTextAttribute(console, 15);
                cout << "  ";
            }
            else if (mainArr[i][j] == 1 || mainArr[i][j] == -1){
                SetConsoleTextAttribute(console, 32);
                cout << "  ";
            }
            else if (mainArr[i][j] == 2 || mainArr[i][j] == -2){
                SetConsoleTextAttribute(console, 48);
                cout << "  ";
            }
            else if (mainArr[i][j] == 3 || mainArr[i][j] == -3){
                SetConsoleTextAttribute(console, 64);
                cout << "  ";
            }
            else if (mainArr[i][j] == 4 || mainArr[i][j] == -4){
                SetConsoleTextAttribute(console, 96);
                cout << "  ";
            }
            else if (mainArr[i][j] == 5 || mainArr[i][j] == -5){
                SetConsoleTextAttribute(console, 80);
                cout << "  ";
            }
            else if (mainArr[i][j] == 6 || mainArr[i][j] == -6){
                SetConsoleTextAttribute(console, 240);
                cout << "  ";
            }
            else if (mainArr[i][j] == 7 || mainArr[i][j] == -7){
                SetConsoleTextAttribute(console, 16);
                cout << "  ";
            }
        }
        SetConsoleTextAttribute(console, 15);
        cout << "\u2502";
    }
    // ----------------------------------

    // ----------------------------------final line
    gotoxy(8, length + 1);
    cout << "\u2514";
    for(int j = 0; j < 2 * (width - 2); j++)
        cout << "\u2500";
    cout << "\u2518";
    // ---------------------------------- 

    // ---------------------------------- name
    gotoxy(8 + width * 2, 5);
    cout << "Name: " << name;
    // ----------------------------------

    // ---------------------------------- hold
    gotoxy(8 + width * 2, 7);
    cout << " Hold: ";
    gotoxy(8 + width * 2, 8);
    cout << "\u250C"; 
    for (int i = 0; i < 8; i++){
        cout << "\u2500";
    }
    cout << "\u2510";
    for (int i = 0; i < 4; i++){
        gotoxy(8 + width * 2, 9 + i);
        cout << "\u2502" << "        " << "\u2502";
    }
    gotoxy(8 + width * 2, 13);
    cout << "\u2514";
    for(int i = 0; i < 8; i++)
        cout << "\u2500";
    cout << "\u2518";
    for(int i = 0; i < shape_size_list[hold_shape]; i++){
        gotoxy(8 + width * 2 + 1, 9 + i);
        for (int j = 0; j < shape_size_list[hold_shape]; j++){
            if (hold_shape == 0){
                if (shape_one[i][j] > 0){
                    SetConsoleTextAttribute(console, 32);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 1){
                if (shape_two[i][j] > 0){
                    SetConsoleTextAttribute(console, 48);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 2){
                if (shape_three[i][j] > 0){
                    SetConsoleTextAttribute(console, 64);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 3){
                if (shape_four[i][j] > 0){
                    SetConsoleTextAttribute(console, 96);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 4){
                if (shape_five[i][j] > 0){
                    SetConsoleTextAttribute(console, 80);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 5){
                if (shape_six[i][j] > 0){
                    SetConsoleTextAttribute(console, 240);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (hold_shape == 6){
                if (shape_seven[i][j] > 0){
                    SetConsoleTextAttribute(console, 16);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            SetConsoleTextAttribute(console, 15);
        }
    }
    //-------------------------------------------

    // ----------------------------------------- next
    gotoxy(8 + width * 2, 14);
    cout << " Next: ";
    gotoxy(8 + width * 2, 15);
    cout << "\u250C"; 
    for (int i = 0; i < 8; i++){
        cout << "\u2500";
    }
    cout << "\u2510";
    for (int i = 0; i < 4; i++){
        gotoxy(8 + width * 2, 16 + i);
        cout << "\u2502" << "        " << "\u2502";
    }
    gotoxy(8 + width * 2, 20);
    cout << "\u2514";
    for(int i = 0; i < 8; i++)
        cout << "\u2500";
    cout << "\u2518";
    for(int i = 0; i < shape_size_list[next_shape]; i++){
        gotoxy(8 + width * 2 + 1, 16 + i);
        for (int j = 0; j < shape_size_list[next_shape]; j++){
            if (next_shape == 0){
                if (shape_one[i][j] > 0){
                    SetConsoleTextAttribute(console, 32);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 1){
                if (shape_two[i][j] > 0){
                    SetConsoleTextAttribute(console, 48);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 2){
                if (shape_three[i][j] > 0){
                    SetConsoleTextAttribute(console, 64);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 3){
                if (shape_four[i][j] > 0){
                    SetConsoleTextAttribute(console, 96);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 4){
                if (shape_five[i][j] > 0){
                    SetConsoleTextAttribute(console, 80);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 5){
                if (shape_six[i][j] > 0){
                    SetConsoleTextAttribute(console, 240);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            else if (next_shape == 6){
                if (shape_seven[i][j] > 0){
                    SetConsoleTextAttribute(console, 16);
                    cout << "  ";
                }
                else
                    cout << "  ";
            }
            SetConsoleTextAttribute(console, 15);
        }
    }
    // -----------------------------------------------

    //---------------------------------------------- score
    gotoxy(8 + width * 2, 22);
    cout << "Score: " << score;
    //----------------------------------------------

    //---------------------------------------------- time
    gotoxy(8 + width * 2, 24);
    if (Time / 60 > 9 && Time % 60 > 9)
        cout <<"Time: " << Time / 60 << ":" << Time % 60;
    else if (Time / 60 <= 9 && Time % 60 > 9)
        cout <<"Time: 0" << Time / 60 << ":" << Time % 60;
    else if (Time / 60 > 9 && Time % 60 <= 9)
        cout <<"Time: " << Time / 60 << ":0" << Time % 60;
    else if (Time / 60 <= 9 && Time % 60 <= 9)
        cout <<"Time: 0" << Time / 60 << ":0" << Time % 60;
    
    //----------------------------------------------
    // cout << endl << endl << endl << endl << endl;
    // for (int i = 3; i < length; i++){
    //     cout << "        ";
    //     for (int j = 0; j < width; j++){
    //         if (j == 0 || j == width - 1){
    //             cout << "*";
    //         }
    //         else if (mainArr[i][j] >= 0)
    //             cout << " " << mainArr[i][j];
    //         else if ( i == length - 1 )
    //             cout << " *";
    //     }
    //     cout << endl;
    // }
    // cout << "i = " << i_current_shape << endl;
    // cout << " j = " << j_current_shape;
}

void update(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0; i < shape_size_list[current_shape] + 1; i++){
        for(int j = -1; j < shape_size_list[current_shape] + 1; j++){
            gotoxy(7 + (j_current_shape  + j) * 2, 1 + i + i_current_shape);
            if (i + i_current_shape > 3 && i + i_current_shape < length && (j + j_current_shape) > 0 && (j + j_current_shape) < width - 1){
                // cout << " "<<mainArr[i + i_current_shape - 1][j + j_current_shape];
                if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 0){
                    SetConsoleTextAttribute(console, 15);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 1 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -1){
                    SetConsoleTextAttribute(console, 32);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 2 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -2){
                    SetConsoleTextAttribute(console, 48);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 3 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -3){
                    SetConsoleTextAttribute(console, 64);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 4 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -4){
                    SetConsoleTextAttribute(console, 96);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 5 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -5){
                    SetConsoleTextAttribute(console, 80);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 6 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -6){
                    SetConsoleTextAttribute(console, 240);
                    cout << "  ";
                }
                else if (mainArr[i + i_current_shape - 1][j + j_current_shape] == 7 || mainArr[i + i_current_shape - 1][j + j_current_shape] == -7){
                    SetConsoleTextAttribute(console, 16);
                    cout << "  ";
                }
            }
            SetConsoleTextAttribute(console, 15);
            
        }
    }
}

void update_right(){
    
}

void update_left(){

}

void update_rotation(){

}

void update_Cdowm(){

}

int random(){
    srand(time(nullptr));
    int rndm = rand() % 7;
    return rndm;
}

void rotate_clockwise(){
    int cnt = shape_size_list[current_shape];
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if (current_shape == 0)
                temp_shape[j][cnt - i - 1] = shape_one[i][j];
            else if (current_shape == 1)
                temp_shape[j][cnt - i - 1] = shape_two[i][j];
            else if (current_shape == 2)
                temp_shape[j][cnt - i - 1] = shape_three[i][j];
            else if (current_shape == 3)
                temp_shape[j][cnt - i - 1] = shape_four[i][j];
            else if (current_shape == 4)
                temp_shape[j][cnt - i - 1] = shape_five[i][j];
            else if (current_shape == 5)
                temp_shape[j][cnt - i - 1] = shape_six[i][j];
            else if (current_shape == 6)
                temp_shape[j][cnt - i - 1] = shape_seven[i][j];
        }
    }
}

void rotate_counterclockwise(){
    int cnt = shape_size_list[current_shape];
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if (current_shape == 0)
                temp_shape[cnt -1 - j][i] = shape_one[i][j];
            else if (current_shape == 1)
                temp_shape[cnt -1 - j][i] = shape_two[i][j];
            else if (current_shape == 2)
                temp_shape[cnt -1 - j][i] = shape_three[i][j];
            else if (current_shape == 3)
                temp_shape[cnt -1 - j][i] = shape_four[i][j];
            else if (current_shape == 4)
                temp_shape[cnt -1 - j][i] = shape_five[i][j];
            else if (current_shape == 5)
                temp_shape[cnt -1 - j][i] = shape_six[i][j];
            else if (current_shape == 6)
                temp_shape[cnt -1 - j][i] = shape_seven[i][j];
        }
    }
}
 
void locating_shape(){
    int jc = width / 2 - 1;
    if (current_shape == 0){
        for(int i = 0; i < shape_size_list[0]; i++){
            for(int j = jc; j < jc + shape_size_list[0]; j++){
                mainArr[i][j] = shape_one[i][j - jc];
            }
        }  
    }
    else if (current_shape == 1){
        int rndm = rand() % (width - shape_size_list[1] + 1);
        for(int i = 0; i < shape_size_list[1]; i++){
            for(int j = jc; j <jc + shape_size_list[1]; j++){
                mainArr[i][j] = shape_two[i][j - jc];
            }
        }  
    }
    else if (current_shape == 2){
        int rndm = rand() % (width - shape_size_list[2] + 1);
        for(int i = 0; i < shape_size_list[2]; i++){
            for(int j = jc; j <jc + shape_size_list[2]; j++){
                mainArr[i][j] = shape_three[i][j - jc];
            }
        }  
    }
    else if (current_shape == 3){
        int rndm = rand() % (width - shape_size_list[3] + 1);
        for(int i = 0; i < shape_size_list[3]; i++){
            for(int j = jc; j <jc + shape_size_list[3]; j++){
                mainArr[i][j] = shape_four[i][j - jc];
            }
        }  
    }
    else if (current_shape == 4){
        int rndm = rand() % (width - shape_size_list[4] + 1);
        for(int i = 0; i < shape_size_list[4]; i++){
            for(int j = jc; j <jc + shape_size_list[4]; j++){
                mainArr[i][j] = shape_five[i][j - jc];
            }
        }  
    }
    else if (current_shape == 5){
        int rndm = rand() % (width - shape_size_list[5] + 1);
        for(int i = 0; i < shape_size_list[5]; i++){
            for(int j = jc; j <jc + shape_size_list[5]; j++){
                mainArr[i][j] = shape_six[i][j - jc];
            }
        }  
    }
    else if (current_shape == 6){
        int rndm = rand() % (width - shape_size_list[6] + 1);
        for(int i = 0; i < shape_size_list[6]; i++){
            for(int j = jc; j <jc + shape_size_list[6]; j++){
                mainArr[i][j] = shape_seven[i][j - jc];
            }
        }  
    }
    i_current_shape = 0;
    j_current_shape = jc;
}

bool check_down(){
    // -----------------------------------------------------------------------------------------------checking move_down:
    for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
        for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
            if (mainArr[i][j] > 0 && mainArr[i + 1][j] < 0)
                return false;
        }
    }
    return true;
    // ------------------------------------------------------------------------------------------------
}

bool check_right(){
    // -----------------------------------------------------------------------------------------------checking move_right:
    for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
        for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
            if (mainArr[i][j] > 0 && mainArr[i][j + 1] < 0)
                return false;
        }
    }
    return true;
    // ---------------------------------------------------------------------------------------------------
}

bool check_left(){
    // -----------------------------------------------------------------------------------------------checking move_left:
    for (int j = j_current_shape + shape_size_list[current_shape] - 1; j >= j_current_shape; j--){
        for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
            if (mainArr[i][j] > 0 && mainArr[i][j - 1] < 0)
                return false;
        }
    }
    return true;
    // ---------------------------------------------------------------------------------------------------
}

void do_hold(){
    int cnt = shape_size_list[hold_shape];
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            if (hold_shape == 0)
                temp_shape[i][j] = shape_one[i][j];
            else if (hold_shape == 1)
                temp_shape[i][j] = shape_two[i][j];
            else if (hold_shape == 2)
                temp_shape[i][j] = shape_three[i][j];
            else if (hold_shape == 3)
                temp_shape[i][j] = shape_four[i][j];
            else if (hold_shape == 4)
                temp_shape[i][j] = shape_five[i][j];
            else if (hold_shape == 5)
                temp_shape[i][j] = shape_six[i][j];
            else if (hold_shape == 6)
                temp_shape[i][j] = shape_seven[i][j];
        }
    }
}

bool check_hold(){
    for (int i = i_current_shape; i < i_current_shape + shape_size_list[hold_shape]; i++){
        for (int j = j_current_shape; j < j_current_shape + shape_size_list[hold_shape]; j++){
            if (temp_shape[i - i_current_shape][j - j_current_shape] > 0 && mainArr[i][j] < 0)
                return false;
        }
    }
    return true;
}

bool check_rotation(){
    for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
        for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
            if (temp_shape[i - i_current_shape][j - j_current_shape] > 0 && mainArr[i][j] < 0)
                return false;
        }
    }
    return true;
}

void do_down(){
    for (int i = i_current_shape + shape_size_list[current_shape] - 1; i >= i_current_shape; i--){
        for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
            if (i < length - 1 && mainArr[i][j] > 0)
                 swap(mainArr[i][j], mainArr[i + 1][j]);
        }
    } // these loops, doing down shift
    i_current_shape++; // i location update
}

void running_game(){
    startTime = chrono::high_resolution_clock::now();
    current_shape = random();
    next_shape = random();
    while (current_shape == next_shape)
        next_shape = random();
    hold_shape = random();
    while (current_shape == hold_shape)
        hold_shape = random();
    while(true && !restart){
        bool hold_flag = false;
        locating_shape();
        system("cls");
        show_game();
        // --------------
        int break_counter = 0;
        while (true && !restart){
            check_gameover();
            while(true){
                Sleep(10);
                break_counter++;
                if (break_counter < 100 / speed ){
                    break;
                }
                if (check_down){
                    do_down();
                    currentTime = chrono::high_resolution_clock::now();
                    chrono::duration<float> timeSpan = currentTime - startTime;
                    Time = timeSpan.count();
                    system("cls");
                    show_game();
                    // update();
                    break_counter = 0;
                }   
            }
            

            if (!check_down()){
                check_gameover();
                for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
                    for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
                        if (i < length - 1 && mainArr[i][j] > 0 && j >= 0 && j < width)
                            mainArr[i][j] *= -1;
                    }
                }
                int i_counter = i_current_shape;
                while (i_counter < i_current_shape + 4 && i_counter < length - 1){
                    int j = 0;
                    while (j < width){
                        if (mainArr[i_counter][j] >= 0)
                            break;
                        j++;
                    }
                    if (j == width){
                        score += 100;
                        shift_down(i_counter);
                    }
                    i_counter++;
                }
                break;
            }
            if (gameover){
                gameover = false;
                delete_Arr();
                gotoxy(30 + width * 2,5);
                cout << "\033[0;31m" << "Game Over!!!";
                gotoxy(30 + width * 2,6);
                cout <<  "\033[0m" <<"you got " << score << " score";
                gotoxy(30 + width * 2,7);
                cout << "Press any key to return to the menu...";
                getch();
                menu();
            }

            if (kbhit()){
                currentTime = chrono::high_resolution_clock::now();
                chrono::duration<float> timeSpan = currentTime - startTime;
                Time = timeSpan.count();
                char chr = getch();
                if (chr == 77 && check_right()){ // right
                    for (int i = i_current_shape + shape_size_list[current_shape] - 1; i >= i_current_shape; i--){
                        for (int j = j_current_shape + shape_size_list[current_shape] - 1; j >= j_current_shape ; j--){
                            if (mainArr[i][j] > 0)
                                swap(mainArr[i][j], mainArr[i][j + 1]);
                        }
                    }
                    j_current_shape++;
                    system("cls");
                    show_game();
                    // update();
                }
                else if (chr == 75 && check_left()){ // left
                    for (int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
                        for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape] ; j++){
                            if (mainArr[i][j] > 0)
                                swap(mainArr[i][j - 1], mainArr[i][j]);
                        }
                    }
                    j_current_shape--;
                    system("cls");
                    show_game();
                    // update();
                }
                else if (chr == 80){ // down
                    if(check_down()){
                        do_down();
                        score++;
                        system("cls");
                        show_game();
                        // update();
                    }
                    //score
                }
                else if (chr == 'x' || chr == 'X' || chr == 'ط'){ // rotate ck
                    rotate_clockwise();
                    int cnt = shape_size_list[current_shape];
                    if (check_rotation()){
                        for (int i = i_current_shape; i < i_current_shape + cnt; i++)
                            for (int j = j_current_shape; j < j_current_shape + cnt; j++){
                                mainArr[i][j] = temp_shape[i - i_current_shape][j - j_current_shape];
                                if (current_shape == 0)
                                    shape_one[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 1)
                                    shape_two[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 2)
                                    shape_three[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 3)
                                    shape_four[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 4)
                                    shape_five[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 5)
                                    shape_six[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 6)
                                    shape_seven[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                            }
                    }
                    system("cls");
                    show_game();
                    // update();
                }
                else if (chr == 'z' || chr == 'Z' || chr == 'ظ'){ // rotate cck
                    rotate_counterclockwise();
                    int cnt = shape_size_list[current_shape];
                    if (check_rotation()){
                        for (int i = i_current_shape; i < i_current_shape + cnt; i++)
                            for (int j = j_current_shape; j < j_current_shape + cnt; j++){
                                mainArr[i][j] = temp_shape[i - i_current_shape][j - j_current_shape];
                                if (current_shape == 0)
                                    shape_one[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 1)
                                    shape_two[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 2)
                                    shape_three[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 3)
                                    shape_four[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 4)
                                    shape_five[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 5)
                                    shape_six[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                                else if (current_shape == 6)
                                    shape_seven[i - i_current_shape][j - j_current_shape] = temp_shape[i - i_current_shape][j - j_current_shape];
                            }
                    }
                    system("cls");
                    show_game();
                    // update();
                }
                else if(chr == ' '){ // c down
                    find_shadow_loc();
                    system("cls");
                    show_game();
                //     for(int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
                //         for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
                //             if (mainArr[i][j] > 0){
                //                 mainArr[i][j] = 0;
                //                 mainArr[i - i_current_shape + i_shadow][j] = current_shape + 1;
                //             }
                //         }
                //     }
                //     score += i_shadow - i_current_shape;
                //     i_current_shape = i_shadow;
                }
                else if (chr == 'h' || chr == 'H' || chr == 'ا'){ //hold
                    do_hold();
                    if (check_hold() && !hold_flag){
                        hold_flag = true;
                        for(int i = i_current_shape; i < i_current_shape + shape_size_list[current_shape]; i++){
                            for (int j = j_current_shape; j < j_current_shape + shape_size_list[current_shape]; j++){
                                if (mainArr[i][j] > 0)
                                    mainArr[i][j] = 0;
                            }
                        }
                        for(int i = i_current_shape; i < i_current_shape + shape_size_list[hold_shape]; i++){
                            for (int j = j_current_shape; j < j_current_shape + shape_size_list[hold_shape]; j++){
                                if (temp_shape[i - i_current_shape][j - j_current_shape] > 0)
                                    mainArr[i][j] = temp_shape[i - i_current_shape][j - j_current_shape];
                            }
                        }
                        current_shape = hold_shape;
                        hold_shape = random();
                        score-=10;
                    }
                }
                else if(chr == 27){
                    system("cls");
                    pause();
                }
            }
        }
        current_shape = next_shape;
        score += 10;
        next_shape = random();
        while (current_shape == hold_shape)
            hold_shape = random();
        while (next_shape == hold_shape)
            next_shape = random();
        
        
    }
}

void crating_temp_shape(){
    for (int i = 0; i < shape_size_list[current_shape]; i++){
        for (int j = 0; j < shape_size_list[current_shape]; j++){
            if (current_shape == 0)
                temp_shape[i][j] = shape_one[i][j];
            else if (current_shape == 1)
                temp_shape[i][j] = shape_two[i][j];
            else if (current_shape == 2)
                temp_shape[i][j] = shape_three[i][j];
            else if (current_shape == 3)
                temp_shape[i][j] = shape_four[i][j];                        
            else if (current_shape == 4)
                temp_shape[i][j] = shape_five[i][j];
            else if (current_shape == 5)
                temp_shape[i][j] = shape_six[i][j];
            else if (current_shape == 6)
                temp_shape[i][j] = shape_seven[i][j];
        }
    }
}

void shift_down(int i_counter){
    for (int j = 1; j < width - 1; j++)
        mainArr[i_counter][j] = 0;
    for (int i = i_counter; i > 0; i--){
        for (int j = 1; j < width - 1; j++){
            swap(mainArr[i][j], mainArr[i- 1][j]);
        }
    }
    for (int j = 1; j < width - 1; j++)
        mainArr[0][j] = 0;
}

void pause(){
    chrono::high_resolution_clock::time_point startpause;
    startpause = chrono::high_resolution_clock::now();
    int cng_counter = 1;
    while (true){
        for(int i = 0; i < 6; i++)
            cout << endl;
        cout << "\t\t" << "\u250C";
        for(int i = 0; i < 20; i++)
            cout << "\u2500";
        cout << "\u2510" << endl;
        cout << "\t\t" << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502" << endl;

        //----------------------------------------- resume
        if (cng_counter == 1){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "    resume     "; //resume
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            cout << "\t\t" << "\u2502";
            cout << "       resume       ";
            cout << "\u2502" << endl;
            if (cng_counter != 2 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        //----------------------------------------- restart  --------------------------------
        if (cng_counter == 2){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "    restart    ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            if (cng_counter != 1 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t\t" << "\u2502";
            cout << "       restart      ";
            cout << "\u2502" << endl;
            if (cng_counter != 1 && cng_counter != 3){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        if (cng_counter == 3){
            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u250C";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2510" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " " << "\033[0;36m" << "\u2502" << " ";
            cout << "     quit      ";
            cout << "\u2502" << " " << "\033[0m" << "\u2502" << endl;

            cout << "\t\t" << "\u2502" << " ";
            cout << "\033[0;36m";
            cout << "\u2514";
            for (int i = 0; i < 16; i++)
                cout << "\u2500";
            cout << "\u2518" << " " << "\033[0m" << "\u2502" << endl;
        }
        else{
            if (cng_counter != 2 && cng_counter != 1){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
            cout << "\t\t" << "\u2502";
            cout << "        quit        ";
            cout << "\u2502" << endl;
            if (cng_counter != 2 && cng_counter != 1){
                cout << "\t\t" << "\u2502";
                for(int i = 0; i < 20; i++)
                    cout << " ";
                cout << "\u2502" << endl;
            }
        }
        cout << "\t\t" << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502" << endl;
        cout << "\t\t" << "\u2514";
        for(int i = 0; i < 20; i++)
            cout << "\u2500";
        cout << "\u2518" << endl;

        char chr = getch();
        while (chr != 72 && chr != 80 && chr != 13)
            chr = getch();
        if( chr == 72 && cng_counter > 1)
            cng_counter--;
        else if( chr == 80 && cng_counter < 3)
            cng_counter++;
        else if(chr == 13)
            break;
        system("cls");
    }
    chrono::high_resolution_clock::time_point endpause;
    endpause = chrono::high_resolution_clock::now();
    startTime += (endpause - startpause);
    if(cng_counter == 3){
        delete_Arr();
        save_to_struct();
        score = 0;
        menu();
    }
    else if (cng_counter == 1){
    
	}
	else if (cng_counter == 2){
        restart = true;
        save_to_struct();
	}
}

void get_info(){
    system("cls");
    gotoxy(16, 4);
    speed = 1;
    cout << "\u250C";
    for(int i = 0; i < 20; i++)
        cout << "\u2500";
    cout << "\u2510";
    for(int i = 5; i < 18; i++){
        gotoxy(16, i);
        cout << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502";
    }
    gotoxy(16, 18);
    cout << "\u2514";
    for(int i = 0; i < 20; i++)
        cout << "\u2500";
    cout << "\u2518";
    gotoxy(18, 6);
    cout << "Name: ";
    cin >> name;
    gotoxy(18, 8);
    cout << "Length: ";
    cin >> length;
    length += 4;
    gotoxy(18, 10);
    cout << "width: ";
    cin >> width;
    width += 2;
    gotoxy(18, 12);
    cout << "speed:(<>)  ";
    while(true){
        gotoxy(28, 12);
        for(int i = 0; i < speed; i++){
            cout << "\033[0;31m" << "|";
        }
        cout << "\033[0m";
        char chr = getch();
        while (chr != 77 && chr != 75 && chr != 13)
            chr = getch();
        if (chr == 77 && speed < 8){
            speed++;
            gotoxy(28, 12);
            for(int i = 0; i < 8; i++){
                cout << " ";
            }
        }
        else if (chr == 75 && speed > 1){
            speed--;
            gotoxy(28, 12);
            for(int i = 0; i < 8; i++){
                cout << " ";
            }
        }
        else if (chr == 13)
            break;
    }

    gotoxy(18, 14);
    cout << "Do you confirm?";
    int i_confirm_cnt = 0;
    while (true){
        if (i_confirm_cnt == 0){
            gotoxy(28, 15);
            cout << "\033[0;36m" << "\u250C";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2510";
            gotoxy(21, 16);
            cout << "\033[0m" << "NO";
            gotoxy(28, 16);
            cout << "\033[0;36m" << "\u2502" << " YES " << "\u2502";
            gotoxy(28, 17);
            cout << "\u2514";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2518" << "\033[0m";
        }
        else{
            gotoxy(19, 15);
            cout << "\033[0;31m" << "\u250C";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2510";
            gotoxy(30, 16);
            cout << "\033[0m" << "YES";
            gotoxy(19, 16);
            cout << "\033[0;31m" << "\u2502" << " NO  " << "\u2502";
            gotoxy(19, 17);
            cout << "\u2514";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2518" << "\033[0m";
        }
        char chr = getch();
        while (chr != 77 && chr != 75 && chr != 13)
            chr = getch();
        if(chr == 77 && i_confirm_cnt > 0)
            i_confirm_cnt--;
        else if( chr == 75 && i_confirm_cnt < 1)
            i_confirm_cnt++;
        else if(chr == 13)
            break;
        gotoxy(19, 15);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
        gotoxy(19, 16);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
        gotoxy(19, 17);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
    }
    if(i_confirm_cnt == 1){
        get_info();
    }
    else if (i_confirm_cnt == 0){
        if (length - 4 < 5 || width - 2 < 5){
            gotoxy(12, 19);
            cout << "You have to choose length/width,";
            gotoxy(21, 20);
            cout << "more than 5!";
            gotoxy(19, 21);
            cout << "please try again.";
            getch();
            get_info();
        }
        // else if (){
            // tekrar esm
        // }

    }
}

void delete_Arr(){
    for(int i = 0; i < length; i++)
        delete[] mainArr[i];
    delete mainArr;
}

void check_gameover(){
    for (int j = 1; j < width - 1; j++){
        if (mainArr[4][j] < 0){
            gameover = true;
            break;
        }
    }
}

void find_shadow_loc(){
    while(check_down()){
        do_down();
        score++;
    }
}

void get_info_advansed(){
    system("cls");
    gotoxy(16, 4);
    speed = 1;
    cout << "\u250C";
    for(int i = 0; i < 20; i++)
        cout << "\u2500";
    cout << "\u2510";
    for(int i = 5; i < 12; i++){
        gotoxy(16, i);
        cout << "\u2502";
        for(int i = 0; i < 20; i++)
            cout << " ";
        cout << "\u2502";
    }
    gotoxy(16, 12);
    cout << "\u2514";
    for(int i = 0; i < 20; i++)
        cout << "\u2500";
    cout << "\u2518";
    gotoxy(18, 6);
    cout << "Name: ";
    cin >> name;
    
    length = 16;
    
    width = 8;
    
    speed = 15;
    gotoxy(18, 8);
    cout << "Do you confirm?";
    int i_confirm_cnt = 0;
    while (true){
        if (i_confirm_cnt == 0){
            gotoxy(28, 9);
            cout << "\033[0;36m" << "\u250C";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2510";
            gotoxy(21, 10);
            cout << "\033[0m" << "NO";
            gotoxy(28, 10);
            cout << "\033[0;36m" << "\u2502" << " YES " << "\u2502";
            gotoxy(28, 11);
            cout << "\u2514";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2518" << "\033[0m";
        }
        else{
            gotoxy(19, 9);
            cout << "\033[0;31m" << "\u250C";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2510";
            gotoxy(30, 10);
            cout << "\033[0m" << "YES";
            gotoxy(19, 10);
            cout << "\033[0;31m" << "\u2502" << " NO  " << "\u2502";
            gotoxy(19, 11);
            cout << "\u2514";
            for(int i = 0; i < 5; i++)
                cout << "\u2500";
            cout << "\u2518" << "\033[0m";
        }
        char chr = getch();
        while (chr != 77 && chr != 75 && chr != 13)
            chr = getch();
        if(chr == 77 && i_confirm_cnt > 0)
            i_confirm_cnt--;
        else if( chr == 75 && i_confirm_cnt < 1)
            i_confirm_cnt++;
        else if(chr == 13)
            break;
        gotoxy(19, 9);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
        gotoxy(19, 10);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
        gotoxy(19, 11);
        for(int i = 0; i < 18; i++){
            cout << " ";
        }
    }
    if(i_confirm_cnt == 1){
        get_info();
    }
    else if (i_confirm_cnt == 0){
        
        

    }
}

void write_score(){
    ofstream file("scores.txt");
    if (file.is_open()){
        int cnt = struct_counter - 1;
        while (cnt >= 0){
            file << scoreboard[cnt].name << ' ' << scoreboard[cnt].score << ' ' << scoreboard[cnt].time <<"\n";
            cnt--;
        }
        file.close();
    }
    else{
        cerr << "opening file error";
        getch();
    }
}

void read_score(){
    ifstream file("scores.txt");
    if (file.is_open()){
        int s, t;
        string n;
        struct_counter = 0;
        while (file >> n >> s >> t){
            scoreboard[struct_counter].name = n;
            scoreboard[struct_counter].score = s;
            scoreboard[struct_counter].time = t;
            struct_counter++;
        }
    }

    else{
        cerr << "opening file error" << endl;
        getch();
    }
}

void sort(){
    for (int i = 0; i < struct_counter; i++) {
        for (int j = i + 1; j < struct_counter; j++){
            if ((scoreboard[j].score > scoreboard[i].score) || ((scoreboard[j].score == scoreboard[i].score) && (scoreboard[j].time < scoreboard[i].time))) {
                int temp = scoreboard[j].score;
                scoreboard[j].score = scoreboard[i].score;
                scoreboard[i].score = temp;

                temp = scoreboard[j].time;
                scoreboard[j].time = scoreboard[i].time;
                scoreboard[i].time = temp;

                string tempp = scoreboard[j].name;
                scoreboard[j].name = scoreboard[i].name;
                scoreboard[i].name = tempp;
            }
        }
    }
}

void save_to_struct(){
    bool mulname = false;
    if (name != "name"){
        for (int i = 0; i < struct_counter; i++){
            if (scoreboard[i].name == name){
                if (scoreboard[i].score < score){
                    scoreboard[i].score = score;
                    scoreboard[i].time = Time;
                }
                mulname = true;
                break;
            }
        }
        if (!mulname){
            scoreboard[struct_counter].name = name;
            scoreboard[struct_counter].score = score;
            scoreboard[struct_counter].time = Time;
            struct_counter++;
        }
    }
}

void leaderboard(){
    save_to_struct();
    sort();
    system("cls");
    cout << "\tname\tscore\ttime" << endl;
    for (int i = 0; i < struct_counter; i++){
        cout << i + 1 << "-\t" << scoreboard[i].name << "\t" << scoreboard[i].score << "\t" << scoreboard[i].time << endl;
    }

}

void howToPlay(string txt){
	for(int i = 0; i < txt.length(); i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // To print the text verbatim.
		cout << txt[i];
		
	}
}


