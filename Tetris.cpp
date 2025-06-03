#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <string>
#include <chrono>
using namespace std;

struct Player
{
    string name;
    int score;
    double time;
    int difficulty;
};

int Play;
char Board [1000][1000];
const char* unicode = "\u2588";
Player newPlayer[1000];

//Pieces Definition
char Pieces[7][4][5][5] =
{
    //Square
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'S', 's', '0'},
            {'0', '0', 's', 's', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'S', 's', '0'},
            {'0', '0', 's', 's', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'S', 's', '0'},
            {'0', '0', 's', 's', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'S', 's', '0'},
            {'0', '0', 's', 's', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //I-Shape
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', 'i', 'I', 'i', 'i'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'i', '0', '0'},
            {'0', '0', 'I', '0', '0'},
            {'0', '0', 'i', '0', '0'},
            {'0', '0', 'i', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'i', 'i', 'I', 'i', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', 'i', '0', '0'},
            {'0', '0', 'i', '0', '0'},
            {'0', '0', 'I', '0', '0'},
            {'0', '0', 'i', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //L-Shape
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'l', '0', '0'},
            {'0', '0', 'L', '0', '0'},
            {'0', '0', 'l', 'l', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', 'l', 'L', 'l', '0'},
            {'0', 'l', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', 'l', 'l', '0', '0'},
            {'0', '0', 'L', '0', '0'},
            {'0', '0', 'l', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', 'l', '0'},
            {'0', 'l', 'L', 'l', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //L-Mirror
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'j', '0', '0'},
            {'0', '0', 'J', '0', '0'},
            {'0', 'j', 'j', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', 'j', '0', '0', '0'},
            {'0', 'j', 'J', 'j', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'j', 'j', '0'},
            {'0', '0', 'J', '0', '0'},
            {'0', '0', 'j', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', 'j', 'J', 'j', '0'},
            {'0', '0', '0', 'j', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //N-Shape
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', 'n', '0'},
            {'0', '0', 'N', 'n', '0'},
            {'0', '0', 'n', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', 'n', 'N', '0', '0'},
            {'0', '0', 'n', 'n', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'n', '0', '0'},
            {'0', 'n', 'N', '0', '0'},
            {'0', 'n', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },

        {
            {'0', '0', '0', '0', '0'},
            {'0', 'n', 'n', '0', '0'},
            {'0', '0', 'N', 'n', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //N-Mirror
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'm', '0', '0'},
            {'0', '0', 'M', 'm', '0'},
            {'0', '0', '0', 'm', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'M', 'm', '0'},
            {'0', 'm', 'm', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', 'm', '0', '0', '0'},
            {'0', 'm', 'M', '0', '0'},
            {'0', '0', 'm', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 'm', 'm', '0'},
            {'0', 'm', 'M', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }
    },
    //T-Shape
    {
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', '0', 'T', 't', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', 't', 'T', 't', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', 't', 'T', '0', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', '0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0', '0'},
            {'0', '0', 't', '0', '0'},
            {'0', 't', 'T', 't', '0'},
            {'0', '0', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
        }
    }
};

void ClearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hConsole == INVALID_HANDLE_VALUE) return;

    //Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    //Fill the entire buffer with spaces
    FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', cellCount, homeCoords, &count);

    //Fill the buffer with the current colors and attributes
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);

    //Move the cursor back to the home position
    SetConsoleCursorPosition(hConsole, homeCoords);
}

void SetCursorPosition(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, pos);
}

void InputName()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m  Please Enter Your Name: \033[0m\033[0m";
    getline(cin, newPlayer[Play].name);
    for (int i = 0; i < 1000; i++){
        while (newPlayer[Play].name == newPlayer[i].name && i != Play){
            ClearScreen();
            cout << "\n\n\n\n\t\t\t\033[38;5;29m\033[38;5;15m  This Username has been used, Enter Another Name: \033[0m\033[0m";
            getline(cin, newPlayer[Play].name);
        }
    }
}

int CheckPlayTime() {
    string PlayT;
    fstream PlayTimes("PlayTimes.txt");

    if (!PlayTimes.is_open()) {
        cerr << "Failed to open PlayTimes.txt" << endl;
        return -1;
    }

    if (!(PlayTimes >> PlayT)) {
        cerr << "Failed to read from PlayTimes.txt or file empty" << endl;
        return -1;
    }

    int Play = 0;
    try {
        Play = stoi(PlayT);
    } catch (const invalid_argument& e) {
        cerr << "Invalid input for stoi: " << PlayT << endl;
        return -1;
    } catch (const out_of_range& e) {
        cerr << "Number out of range: " << PlayT << endl;
        return -1;
    }

    return Play;
}

void InputLeaderBoard()
{
    string str;
    fstream LeaderBoard ("LeaderBoard.txt");
    int i = 1;
    string name;
    int score;
    double time;
    while (LeaderBoard >> name >> str >> str >> score >> str >> str >> str >> str >> time >> str)
    {
        newPlayer[i].name = name;
        newPlayer[i].score = score;
        newPlayer[i].time = time;
        i++;
    }
    LeaderBoard.close();
}

void SortLeaderBoard()
{
    int n = Play;
    bool Swapped;
    for (int i = 1; i <= n; i++) {
        Swapped = false;
        for (int j = 1; j <= n - i; j++)
        {
            if (newPlayer[j].score > newPlayer[j + 1].score)
            {
                swap(newPlayer[j], newPlayer[j + 1]);
                Swapped = true;
            }
            else if (newPlayer[j].score == newPlayer[j + 1].score)
            {
                if (newPlayer[j].time < newPlayer[j + 1].time)
                {
                    swap(newPlayer[j], newPlayer[j + 1]);
                    Swapped = true;
                }
            }
        }
        if (Swapped == false)
        {
            break;
        }
    }
}

void FinalLeaderBoard()
{
    SortLeaderBoard();
    string LeaderBoard;
    fstream File ("LeaderBoard.txt");
    for (int i = 1; i <= Play; i++){
        LeaderBoard += newPlayer[i].name;
        LeaderBoard += " Score is: ";
        LeaderBoard += to_string(newPlayer[i].score);
        LeaderBoard += " And Their Time is: ";
        LeaderBoard += to_string(newPlayer[i].time);
        LeaderBoard += "\n";
    }
    File << LeaderBoard;
}

void ClearBoard()
{
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            Board[i][j] = '0';
        }
    }
}

void ClearPlayers()
{
    for (int i = Play + 1; i < 1000; i++){
        newPlayer[i].time = 0;
        newPlayer[i].score = 0;
    }
}

void DisplayStart()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\t\033[38;5;29m\033[38;5;196mT\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;202mE\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;226mT\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;118mR\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;14mI\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;135mS\033[0m\033[0m";
    cout << "\033[38;5;15m\033[38;5;15m GAME\033[0m\033[0m" <<endl;
    cout << "\n\n\n\t\t\t\t Press any key to continue";
    getch();
}

void DisplayHowToPlay()
{
    ClearScreen();
    cout << "\n\n\tUse Left and Right Arrows or A and D Keys to Move Pieces Left and Right";
    cout << "\n\n\tUse Down Arrow or S Key to Move Pieces Downwards Faster";
    cout << "\n\n\tThe Goal is to Form the Pieces Into Solid Lines. When the Pieces Form a Solid Line, They Then Disappear.";
    cout << "\n\n\tIf the Uncleared Pieces Reach the Top of the Screen, the Game Ends.";
    cout << "\n\n\n\t\t\t\t\t Press any key to continue";
    getch();
}

void UpdatePlayTimes()
{
    fstream File ("PlayTimes.txt");
    File << to_string(Play);
}

void DisplayLeaderboard()
{
    SortLeaderBoard();
    ClearScreen();
    for (int i = 1; i <= Play; i++){
        cout << newPlayer[i].name;
        cout << " Score is: ";
        cout << to_string(newPlayer[i].score);
        cout << " And Their Time is: ";
        cout << to_string(newPlayer[i].time);
        cout << "\n";
    }
    getch();
}

int Menu()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\t\033[38;5;29m\033[38;5;196mT\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;202mE\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;226mT\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;118mR\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;14mI\033[0m\033[0m";
    cout << "\033[38;5;29m\033[38;5;135mS\033[0m\033[0m";
    cout << "\033[38;5;15m\033[38;5;15m GAME\033[0m\033[0m" <<endl;
    cout << "\n\n\t\t\t\t\t1) New Game";
    cout << "\n\n\t\t\t\t\t2) How to Play";
    cout << "\n\n\t\t\t\t\t3) Leaderboard";
    cout << "\n\n\t\t\t\t\t4) Exit";
    return getch();
}

int SelectDifficulty()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m     Select Difficulty\033[0m\033[0m\n";
    cout << "\n\n\t\t\t\t\t1) \033[38;5;29m\033[38;5;82mEasy\033[0m\033[0m";
    cout << "\n\n\t\t\t\t\t2) \033[38;5;29m\033[38;5;196mHard\033[0m\033[0m";
    return getch();
}

int SelectTheme()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m       Select Theme\033[0m\033[0m\n";
    cout << "\n\n\t\t\t\t\t1) \033[38;5;29m\033[38;5;15mDefault\033[0m\033[0m";
    cout << "\n\n\t\t\t\t\t2) \033[38;5;29m\033[38;5;196mRed\033[0m\033[0m";
    cout << "\n\n\t\t\t\t\t3) \033[38;5;29m\033[38;5;82mGreen\033[0m\033[0m";
    cout << "\n\n\t\t\t\t\t4) \033[38;5;29m\033[38;5;39mBlue\033[0m\033[0m";
    return getch();
}

int SelectBoardSize()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m     Enter Board Size: \033[0m\033[0m";

    int BoardSize;
    cin >> BoardSize;
    while (BoardSize < 5)
    {
        ClearScreen();
        cout << "\n\n\t\t\t\033[38;5;29m\033[38;5;15m       Board Size Must Be 5 At Least\033[0m\033[0m";
        cout << "\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m     Enter Board Size: \033[0m\033[0m";
        cin >> BoardSize;
    }
    return BoardSize;
}

int CheckOver(int size)
{
    if (size == 0)
    {
        return 0;
    }
    for (int j = 0; j < size * 2 + 1; j++){
        if (Board[3][j] != '0'){
            return 0;
        }
    }
    return 1;
}

int SelectPiece(int size, int piece)
{
    int Piece;
    if (piece == 7){
        srand(time(0));
        Piece = rand() % 7;
    }
    else{
        Piece = piece;
    }

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (Board[i][size-2+j] != '0'){
                return 7;
            }
        }
    }

    if (Piece == 0){ //Square
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[0][1][i][j];
            }
        }
    }
    if (Piece == 1){ //I-Shape
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[1][1][i][j];
            }
        }
    }
    if (Piece == 2){ //L-Shape
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[2][1][i][j];
            }
        }
    }
    if (Piece == 3){ //L-Mirror
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[3][3][i][j];
            }
        }
    }
    if (Piece == 4){ //N-Shape
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[4][1][i][j];
            }
        }
    }
    if (Piece == 5){ //N-Mirror
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[5][1][i][j];
            }
        }
    }
    if (Piece == 6){ //T-Shape
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                Board[i][size-2+j] = Pieces[6][1][i][j];
            }
        }
    }

    return Piece;
}

void DisplayBoardDefault(int size, int nextpiece)
{
    ClearScreen();
    SetCursorPosition(0, 0);

    for (int i = 3; i < size * 2 + 1; i++)
    {
        for (int j = 0; j < size * 2 + 1; j++)
        {
            if (Board[i][j] == '0'){
                cout << "\u2591";
            }
            else
            {
                if(Board[i][j] == 's'  || Board[i][j] == 'S' || Board[i][j] == 'q')
                    cout << "\033[38;5;226m\u2588\033[37m";

                else if(Board[i][j] == 'n'  || Board[i][j] == 'N' || Board[i][j] == 'o')
                    cout << "\033[38;5;46m\u2588\033[37m";

                else if(Board[i][j] == 'j'  || Board[i][j] == 'J' || Board[i][j] == 'g')
                    cout << "\033[38;5;21m\u2588\033[37m";

                else if(Board[i][j] == 'm'  || Board[i][j] == 'M' || Board[i][j] == 'p')
                    cout << "\033[38;5;196m\u2588\033[37m";

                else if(Board[i][j] == 't'  || Board[i][j] == 'T' || Board[i][j] == 'x')
                    cout << "\033[38;5;129m\u2588\033[37m";

                else if(Board[i][j] == 'i'  || Board[i][j] == 'I' || Board[i][j] == 'e')
                    cout << "\033[38;5;51m\u2588\033[37m";

                else if(Board[i][j] == 'l'  || Board[i][j] == 'L' || Board[i][j] == 'k')
                    cout << "\033[38;5;208m\u2588\033[37m";
            }
        }
        if (nextpiece == 0){
            if (i == size){
                cout << "\t\t\033[38;5;226m\u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t\t\033[38;5;226m\u2588\u2588\033[37m";
            }
        }
        else if (nextpiece == 1){
            if (i == size - 1){
                cout << "\t\t\033[38;5;51m\u2588\033[37m";
            }
            if (i == size){
                cout << "\t\t\033[38;5;51m\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t\t\033[38;5;51m\u2588\033[37m";
            }
            if (i == size + 2){
                cout << "\t\t\033[38;5;51m\u2588\033[37m";
            }
        }
        else if (nextpiece == 2){
            if (i == size){
                cout << "\t\t\033[38;5;208m\u2588\u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t\t\033[38;5;208m\u2588\033[37m";
            }
        }
        else if (nextpiece == 3){
            if (i == size){
                cout << "\t\t\033[38;5;21m\u2588\u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t\t\033[38;5;21m  \u2588\033[37m";
            }
        }
        else if (nextpiece == 4){
            if (i == size){
                cout << "\t     \033[38;5;46m\u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t     \033[38;5;46m \u2588\u2588\033[37m";
            }
        }
        else if (nextpiece == 5){
            if (i == size){
                cout << "\t     \033[38;5;196m \u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t     \033[38;5;196m\u2588\u2588\033[37m";
            }
        }
        else if (nextpiece == 6){
            if (i == size){
                cout << "\t     \033[38;5;129m\u2588\u2588\u2588\033[37m";
            }
            if (i == size + 1){
                cout << "\t     \033[38;5;129m \u2588\033[37m";
            }
        }
        cout << endl;
    }

    cout << "\t\n\n\n\nscore: " << newPlayer[Play].score;
    cout << "\t\n\n\n\ntimer: " << newPlayer[Play].time << "seconds";
    cout << "\t\n\n\n\nplay: " << Play;
}

void DisplayBoardRed(int size)
{
    ClearScreen();
    SetCursorPosition(0, 0);

    for (int i = 3; i < size * 2 + 1; i++)
    {
        for (int j = 0; j < size * 2 + 1; j++)
        {
            if (Board[i][j] == '0'){
                cout << "\u2591";
            }
            else
            {
                if(Board[i][j] == 's'  || Board[i][j] == 'S' || Board[i][j] == 'q')
                    cout << "\033[38;5;124m\u2588\033[37m";

                else if(Board[i][j] == 'n'  || Board[i][j] == 'N' || Board[i][j] == 'o')
                    cout << "\033[38;5;160m\u2588\033[37m";

                else if(Board[i][j] == 'j'  || Board[i][j] == 'J' || Board[i][j] == 'g')
                    cout << "\033[38;5;9m\u2588\033[37m";

                else if(Board[i][j] == 'm'  || Board[i][j] == 'M' || Board[i][j] == 'p')
                    cout << "\033[38;5;196m\u2588\033[37m";

                else if(Board[i][j] == 't'  || Board[i][j] == 'T' || Board[i][j] == 'x')
                    cout << "\033[38;5;161m\u2588\033[37m";

                else if(Board[i][j] == 'i'  || Board[i][j] == 'I' || Board[i][j] == 'e')
                    cout << "\033[38;5;197m\u2588\033[37m";

                else if(Board[i][j] == 'l'  || Board[i][j] == 'L' || Board[i][j] == 'k')
                    cout << "\033[38;5;202m\u2588\033[37m";
            }
        }
        cout << endl;
    }

    cout << "\t\n\n\n\nscore: " << newPlayer[Play].score;
    cout << "\t\n\n\n\ntimer: " << newPlayer[Play].time << "seconds";
    cout << "\t\n\n\n\nplay: " << Play;
}

void DisplayBoardGreen(int size)
{
    ClearScreen();
    SetCursorPosition(0, 0);

    for (int i = 3; i < size * 2 + 1; i++)
    {
        for (int j = 0; j < size * 2 + 1; j++)
        {
            if (Board[i][j] == '0'){
                cout << "\u2591";
            }
            else
            {
                if(Board[i][j] == 's'  || Board[i][j] == 'S' || Board[i][j] == 'q')
                    cout << "\033[38;5;40m\u2588\033[37m";

                else if(Board[i][j] == 'n'  || Board[i][j] == 'N' || Board[i][j] == 'o')
                    cout << "\033[38;5;148m\u2588\033[37m";

                else if(Board[i][j] == 'j'  || Board[i][j] == 'J' || Board[i][j] == 'g')
                    cout << "\033[38;5;118m\u2588\033[37m";

                else if(Board[i][j] == 'm'  || Board[i][j] == 'M' || Board[i][j] == 'p')
                    cout << "\033[38;5;46m\u2588\033[37m";

                else if(Board[i][j] == 't'  || Board[i][j] == 'T' || Board[i][j] == 'x')
                    cout << "\033[38;5;106m\u2588\033[37m";

                else if(Board[i][j] == 'i'  || Board[i][j] == 'I' || Board[i][j] == 'e')
                    cout << "\033[38;5;82m\u2588\033[37m";

                else if(Board[i][j] == 'l'  || Board[i][j] == 'L' || Board[i][j] == 'k')
                    cout << "\033[38;5;76m\u2588\033[37m";
            }
        }
        cout << endl;
    }

    cout << "\t\n\n\n\nscore: " << newPlayer[Play].score;
    cout << "\t\n\n\n\ntimer: " << newPlayer[Play].time << "seconds";
    cout << "\t\n\n\n\nplay: " << Play;
}

void DisplayBoardBlue(int size)
{
    ClearScreen();
    SetCursorPosition(0, 0);

    for (int i = 3; i < size * 2 + 1; i++)
    {
        for (int j = 0; j < size * 2 + 1; j++)
        {
            if (Board[i][j] == '0'){
                cout << "\u2591";
            }
            else
            {
                if(Board[i][j] == 's'  || Board[i][j] == 'S' || Board[i][j] == 'q')
                    cout << "\033[38;5;27m\u2588\033[37m";

                else if(Board[i][j] == 'n'  || Board[i][j] == 'N' || Board[i][j] == 'o')
                    cout << "\033[38;5;33m\u2588\033[37m";

                else if(Board[i][j] == 'j'  || Board[i][j] == 'J' || Board[i][j] == 'g')
                    cout << "\033[38;5;39m\u2588\033[37m";

                else if(Board[i][j] == 'm'  || Board[i][j] == 'M' || Board[i][j] == 'p')
                    cout << "\033[38;5;45m\u2588\033[37m";

                else if(Board[i][j] == 't'  || Board[i][j] == 'T' || Board[i][j] == 'x')
                    cout << "\033[38;5;63m\u2588\033[37m";

                else if(Board[i][j] == 'i'  || Board[i][j] == 'I' || Board[i][j] == 'e')
                    cout << "\033[38;5;81m\u2588\033[37m";

                else if(Board[i][j] == 'l'  || Board[i][j] == 'L' || Board[i][j] == 'k')
                    cout << "\033[38;5;21m\u2588\033[37m";
            }
        }
        cout << endl;
    }

    cout << "\t\n\n\n\nscore: " << newPlayer[Play].score;
    cout << "\t\n\n\n\ntimer: " << newPlayer[Play].time << "seconds";
    cout << "\t\n\n\n\nplay: " << Play;
}

int Falling(int size, int piece)
{
    if (piece == 0){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 's' || Board[i][j] == 'S'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 's' && Board[i+1][j] != 'S'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 1){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 'i' && Board[i+1][j] != 'I'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 2){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 'l' && Board[i+1][j] != 'L'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 3){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 'j' && Board[i+1][j] != 'J'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 4){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 'n' && Board[i+1][j] != 'N'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 5){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 'm' && Board[i+1][j] != 'M'){
                        return 0;
                    }
                }
            }
        }
    }
    else if (piece == 6){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 't' || Board[i][j] == 'T'){
                    if (i == size * 2){
                        return 0;
                    }
                    if (Board[i+1][j] != '0' && Board[i+1][j] != 't' && Board[i+1][j] != 'T'){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void Tick(int size, int piece)
{
    if (piece == 0){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 's' || Board[i][j] == 'S'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 1){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 2){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 3){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 4){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 5){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 6){
        for (int i = size * 2; i >= 0; i--)
        {
            for (int j = size * 2; j >= 0 ; j--)
            {
                if (Board[i][j] == 't' || Board[i][j] == 'T'){
                    if (Board[i+1][j] == '0'){
                        Board[i+1][j] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
}

int Rotate(int size, int piece, int rotation)
{
    if (piece == 0){
        return rotation;
    }
    else if (piece == 1)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'I'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2 || x == size * 2 - 1){
                return rotation;
            }
            if (Board[x+1][y] != '0' || Board[x+2][y] != '0' || Board[x-1][y] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'i' && Board[i][j] != 'I'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y] = 'i';
            Board[x+2][y] = 'i';
            Board[x-1][y] = 'i';

            Board[x][y-1] = '0';
            Board[x][y+1] = '0';
            Board[x][y+2] = '0';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'I'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0 || y == 1 || y == size * 2){
                return rotation;
            }
            if (Board[x][y-1] != '0' || Board[x][y-2] != '0' || Board[x][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'i' && Board[i][j] != 'I'){
                        return rotation;
                    }
                }
            }

            Board[x][y-1] = 'i';
            Board[x][y+1] = 'i';
            Board[x][y-2] = 'i';

            Board[x+1][y] = '0';
            Board[x+2][y] = '0';
            Board[x-1][y] = '0';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'I'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return rotation;
            }
            if (Board[x+1][y] != '0' || Board[x-1][y] != '0' || Board[x-2][y] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'i' && Board[i][j] != 'I'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y] = 'i';
            Board[x-2][y] = 'i';
            Board[x-1][y] = 'i';

            Board[x][y-1] = '0';
            Board[x][y+1] = '0';
            Board[x][y-2] = '0';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'I'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0 || y == size * 2 - 1|| y == size * 2){
                return rotation;
            }
            if (Board[x][y-1] != '0' || Board[x][y+2] != '0' || Board[x][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'i' && Board[i][j] != 'I'){
                        return rotation;
                    }
                }
            }

            Board[x][y-1] = 'i';
            Board[x][y+1] = 'i';
            Board[x][y+2] = 'i';

            Board[x+1][y] = '0';
            Board[x-2][y] = '0';
            Board[x-1][y] = '0';

            rotation = 0;
            return rotation;
        }
    }
    else if (piece == 2)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'L'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0){
                return rotation;
            }
            if (Board[x][y-1] != '0' || Board[x][y+1] != '0' || Board[x+1][y-1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'l' && Board[i][j] != 'L'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y] = '0';
            Board[x+1][y] = '0';
            Board[x+1][y+1] = '0';

            Board[x][y-1] = 'l';
            Board[x][y+1] = 'l';
            Board[x+1][y-1] = 'l';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'L'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (Board[x+1][y] != '0' || Board[x+2][y] != '0' || Board[x-1][y-1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'l' && Board[i][j] != 'L'){
                        return rotation;
                    }
                }
            }

            Board[x][y+1] = '0';
            Board[x][y-1] = '0';
            Board[x+1][y-1] = '0';

            Board[x+1][y] = 'l';
            Board[x-1][y] = 'l';
            Board[x-1][y-1] = 'l';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'L'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == size * 2){
                return rotation;
            }
            if (Board[x][y-1] != '0' || Board[x][y+1] != '0' || Board[x-1][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'l' && Board[i][j] != 'L'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y] = '0';
            Board[x-1][y] = '0';
            Board[x-1][y-1] = '0';

            Board[x][y-1] = 'l';
            Board[x][y+1] = 'l';
            Board[x-1][y+1] = 'l';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'L'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return rotation;
            }
            if (Board[x+1][y] != '0' || Board[x-1][y] != '0' || Board[x+1][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'l' && Board[i][j] != 'L'){
                        return rotation;
                    }
                }
            }

            Board[x][y+1] = '0';
            Board[x][y-1] = '0';
            Board[x-1][y+1] = '0';

            Board[x+1][y] = 'l';
            Board[x-1][y] = 'l';
            Board[x+1][y+1] = 'l';

            rotation = 0;
            return rotation;
        }
    }
    else if (piece == 3)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'J'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (Board[x][y-1] != '0' || Board[x][y+1] != '0' || Board[x-1][y-1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'j' && Board[i][j] != 'J'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y] = '0';
            Board[x+1][y] = '0';
            Board[x+1][y-1] = '0';

            Board[x][y-1] = 'j';
            Board[x][y+1] = 'j';
            Board[x-1][y-1] = 'j';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'J'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return rotation;
            }
            if (Board[x+1][y] != '0' || Board[x+2][y] != '0' || Board[x-1][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'j' && Board[i][j] != 'J'){
                        return rotation;
                    }
                }
            }

            Board[x][y+1] = '0';
            Board[x][y-1] = '0';
            Board[x-1][y-1] = '0';

            Board[x+1][y] = 'j';
            Board[x-1][y] = 'j';
            Board[x-1][y+1] = 'j';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'J'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0){
                return rotation;
            }
            if (Board[x][y-1] != '0' || Board[x][y+1] != '0' || Board[x+1][y+1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'j' && Board[i][j] != 'J'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y] = '0';
            Board[x-1][y] = '0';
            Board[x-1][y+1] = '0';

            Board[x][y-1] = 'j';
            Board[x][y+1] = 'j';
            Board[x+1][y+1] = 'j';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'J'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (Board[x+1][y] != '0' || Board[x-1][y] != '0' || Board[x+1][y-1] != '0'){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'j' && Board[i][j] != 'J'){
                        return rotation;
                    }
                }
            }

            Board[x][y+1] = '0';
            Board[x][y-1] = '0';
            Board[x+1][y+1] = '0';

            Board[x+1][y] = 'j';
            Board[x-1][y] = 'j';
            Board[x+1][y-1] = 'j';

            rotation = 0;
            return rotation;
        }
    }
    else if (piece == 4)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'N'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'n' && Board[i][j] != 'N'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y+1] = '0';
            Board[x][y+1] = '0';

            Board[x+1][y+1] = 'n';
            Board[x][y-1] = 'n';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'N'){
                        x = i;
                        y = j;
                    }
                }
            }

            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'n' && Board[i][j] != 'N'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y+1] = '0';
            Board[x+1][y] = '0';

            Board[x+1][y-1] = 'n';
            Board[x-1][y] = 'n';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'N'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == size * 2){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'n' && Board[i][j] != 'N'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y-1] = '0';
            Board[x][y-1] = '0';

            Board[x-1][y-1] = 'n';
            Board[x][y+1] = 'n';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'N'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'n' && Board[i][j] != 'N'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y-1] = '0';
            Board[x-1][y] = '0';

            Board[x-1][y+1] = 'n';
            Board[x+1][y] = 'n';

            rotation = 0;
            return rotation;
        }
    }
    else if (piece == 5)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'M'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'm' && Board[i][j] != 'M'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y+1] = '0';
            Board[x-1][y] = '0';

            Board[x+1][y-1] = 'm';
            Board[x+1][y] = 'm';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'M'){
                        x = i;
                        y = j;
                    }
                }
            }

            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'm' && Board[i][j] != 'M'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y-1] = '0';
            Board[x][y+1] = '0';

            Board[x-1][y-1] = 'm';
            Board[x][y-1] = 'm';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'M'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == size * 2){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'm' && Board[i][j] != 'M'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y-1] = '0';
            Board[x+1][y] = '0';

            Board[x-1][y+1] = 'm';
            Board[x-1][y] = 'm';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'M'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 'm' && Board[i][j] != 'M'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y+1] = '0';
            Board[x][y-1] = '0';

            Board[x+1][y+1] = 'm';
            Board[x][y+1] = 'm';

            rotation = 0;
            return rotation;
        }
    }
    else if (piece == 6)
    {
        if (rotation == 0)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'T'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == 0){
                return rotation;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 't' && Board[i][j] != 'T'){
                        return rotation;
                    }
                }
            }

            Board[x-1][y] = '0';
            Board[x][y-1] = 't';

            rotation = 1;
            return rotation;
        }

        if (rotation == 1)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'T'){
                        x = i;
                        y = j;
                    }
                }
            }

            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 't' && Board[i][j] != 'T'){
                        return rotation;
                    }
                }
            }

            Board[x][y+1] = '0';
            Board[x-1][y] = 't';

            rotation = 2;
            return rotation;
        }

        if (rotation == 2)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'T'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (y == size * 2){
                return 0;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 't' && Board[i][j] != 'T'){
                        return rotation;
                    }
                }
            }

            Board[x+1][y] = '0';
            Board[x][y+1] = 't';

            rotation = 3;
            return rotation;
        }

        if (rotation == 3)
        {
            int x, y;
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'T'){
                        x = i;
                        y = j;
                    }
                }
            }

            if (x == size * 2){
                return 0;
            }
            for (int i = x-2; i < x+3; i++){
                for (int j = y-2; j < y+3; j++){
                    if (Board[i][j] != '0' && Board[i][j] != 't' && Board[i][j] != 'T'){
                        return rotation;
                    }
                }
            }

            Board[x][y-1] = '0';
            Board[x+1][y] = 't';

            rotation = 0;
            return rotation;
        }
    }
    return rotation;
}

void TurnSolid(int size, int piece)
{
    for (int i = 0; i < size * 2 + 1; i++){
        for (int j = 0; j < size * 2 + 1; j++){
            if (piece == 0){
                if (Board[i][j] == 's' || Board[i][j] == 'S'){
                    Board[i][j] = 'q';
                }
            }
            if (piece == 1){
                if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                    Board[i][j] = 'e';
                }
            }
            if (piece == 2){
                if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                    Board[i][j] = 'k';
                }
            }
            if (piece == 3){
                if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                    Board[i][j] = 'g';
                }
            }
            if (piece == 4){
                if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                    Board[i][j] = 'o';
                }
            }
            if (piece == 5){
                if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                    Board[i][j] = 'p';
                }
            }
            if (piece == 6){
                if (Board[i][j] == 't' || Board[i][j] == 'T'){
                    Board[i][j] = 'x';
                }
            }
        }
    }
}

void MoveToRight(int size, int piece, int Theme, int nextpiece)
{
    int counter = 0;
    if (piece == 0){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 's' || Board[i][j] == 'S'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 's' || Board[i][j + 1] == 'S'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 's' || Board[i][j] == 'S'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 1){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 'i' || Board[i][j + 1] == 'I'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 2){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 'l' || Board[i][j + 1] == 'L'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 3){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 'j' || Board[i][j + 1] == 'J'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 4){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 'n' || Board[i][j + 1] == 'N'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 5){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 'm' || Board[i][j + 1] == 'M'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 6){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 't' || Board[i][j] == 'T'){
                    if (j == size * 2){
                        return;
                    }
                    if (Board[i][j + 1] == '0' || Board[i][j + 1] == 't' || Board[i][j + 1] == 'T'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = size * 2 - 1; j >= 0; j--){
                    if (Board[i][j] == 't' || Board[i][j] == 'T'){
                        Board[i][j + 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (Theme == 1)
        DisplayBoardDefault(size, nextpiece);
    else if (Theme == 2)
        DisplayBoardRed(size);
    else if (Theme == 3)
        DisplayBoardGreen(size);
    else if (Theme == 4)
        DisplayBoardBlue(size);
}

void MoveToLeft(int size, int piece, int Theme, int nextpiece)
{
    int counter = 0;
    if (piece == 0){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 's' || Board[i][j] == 'S'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 's' || Board[i][j - 1] == 'S'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 's' || Board[i][j] == 'S'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 1){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 'i' || Board[i][j - 1] == 'I'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'i' || Board[i][j] == 'I'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 2){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 'l' || Board[i][j - 1] == 'L'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'l' || Board[i][j] == 'L'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 3){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 'j' || Board[i][j - 1] == 'J'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'j' || Board[i][j] == 'J'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 4){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 'n' || Board[i][j - 1] == 'N'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'n' || Board[i][j] == 'N'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 5){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 'm' || Board[i][j - 1] == 'M'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 'm' || Board[i][j] == 'M'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (piece == 6){
        for (int i = 0; i < size * 2 + 1; i++){
            for (int j = 0; j < size * 2 + 1; j++){
                if (Board[i][j] == 't' || Board[i][j] == 'T'){
                    if (j == 0){
                        return;
                    }
                    if (Board[i][j - 1] == '0' || Board[i][j - 1] == 't' || Board[i][j - 1] == 'T'){
                        counter++;
                    }
                }
            }
        }
        if (counter == 4){
            for (int i = 0; i < size * 2 + 1; i++){
                for (int j = 0; j < size * 2 + 1; j++){
                    if (Board[i][j] == 't' || Board[i][j] == 'T'){
                        Board[i][j - 1] = Board[i][j];
                        Board[i][j] = '0';
                    }
                }
            }
        }
    }
    if (Theme == 1)
        DisplayBoardDefault(size, nextpiece);
    else if (Theme == 2)
        DisplayBoardRed(size);
    else if (Theme == 3)
        DisplayBoardGreen(size);
    else if (Theme == 4)
        DisplayBoardBlue(size);
}

void RemoveLine(int size, int line)
{
    for (int j = 0; j < size * 2 + 1; j++){
        Board[line][j] = '0';
    }
    for (int i = line - 1; i >=0; i--){
        for (int j = 0; j < size * 2 + 1; j++){
            Board[i+1][j] = Board[i][j];
            Board[i][j] = '0';
        }
    }
}

void FilledLine(int size)
{
    for (int i = 0; i < size * 2 + 1; i++){
        int count = 0;
        for (int j = 0; j < size * 2 + 1; j++){
            if (Board[i][j] != '0'){
                count++;
            }
        }
        if (count > size * 2){
            RemoveLine(size, i);
            newPlayer[Play].score += size * 100 * newPlayer[Play].difficulty;
        }
    }
}

int Pause()
{
    ClearScreen();
    cout << "\n\n\n\n\t\t\t\t\033[38;5;29m\033[38;5;15m   Paused\033[0m\033[0m";
    cout << "\n\n\t\t\t\033[38;5;29m\033[38;5;15m Press ESC to Quit to Menu\033[0m\033[0m";
    cout << "\n\n\t\t\t\033[38;5;29m\033[38;5;15m Press Any key to Continue\033[0m\033[0m";
    int input = getch();
    if (input == 27){
        ClearScreen();
        return 0;
    }
    else{
        return 1;
    }
}

void FlushInputBuffer() {
    while (_kbhit()) _getch();
}

int main()
{
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            Board[i][j] = '0';
        }
    }
    cout << "\n\n\n\n\t\t\t\t\t\tLoading...";
    ClearScreen();

    CheckPlayTime();
    ClearPlayers();
    InputLeaderBoard();

    DisplayStart();

    Menu:
    ClearBoard();
    int MenuInput = Menu();
    while (MenuInput == 50 || MenuInput == 51 || MenuInput == 52)
    {
        if (MenuInput == 50){
            DisplayHowToPlay();
        }
        if (MenuInput == 51){
            DisplayLeaderboard();
        }
        if (MenuInput == 52){
            ClearScreen();
            FinalLeaderBoard();
            return 0;
        }
        MenuInput = Menu();
    }

    Play++;
    UpdatePlayTimes();
    ClearScreen();

    InputName();
    FinalLeaderBoard();

    int Difficulty = 1;
    int DifficultyInput = SelectDifficulty();

    if (DifficultyInput == 50){
        Difficulty = 2;
    }
    newPlayer[Play].difficulty = Difficulty;
    newPlayer[Play].score = 0;

    int Theme = 1;
    int ThemeInput = SelectTheme();

    if (ThemeInput == 50){
        Theme = 2;
    }
    else if (ThemeInput == 51){
        Theme = 3;
    }
    if (ThemeInput == 52){
        Theme = 4;
    }

    int Size = SelectBoardSize();

    auto start_time = chrono::high_resolution_clock::now();
    int TickTime = 500;
    if (Difficulty == 2){
        TickTime = 300;
    }

    bool Downed = false;
    int tempTime;

    int Piece = SelectPiece(Size, 7);
    while (true)
    {
        if (Downed == true){
            Downed = false;
        }

        ClearScreen();
        srand(time(0));
        int NextPiece = rand() % 7;

        if (Piece == 7){
            ClearScreen();
            cout << "Game Over!";
            getch();
            goto Menu;
        }

        int Rotation;
        if (Piece == 3){
            Rotation = 3;
        }
        else {
            Rotation = 1;
        }

        if (Theme == 1)
            DisplayBoardDefault(Size, NextPiece);
        else if (Theme == 2)
            DisplayBoardRed(Size);
        else if (Theme == 3)
            DisplayBoardGreen(Size);
        else if (Theme == 4)
            DisplayBoardBlue(Size);

        while (Falling(Size, Piece)){

            if (_kbhit()){
                int Input = _getch();
                if (Input == 100){
                    MoveToRight(Size, Piece, Theme, NextPiece);
                }
                else if (Input == 97){
                    MoveToLeft(Size, Piece, Theme, NextPiece);
                }
                else if (Input == 122){
                    Rotation = Rotate(Size, Piece, Rotation);
                }
                else if (Input == 115){
                    Downed = true;
                }
                else if (Input == 27){
                    int pause = Pause();
                    if (pause == 0){
                        ClearScreen();
                        goto Menu;
                    }
                }

                FlushInputBuffer();
            }

            Tick(Size, Piece);

            FinalLeaderBoard();
            if (Theme == 1)
                DisplayBoardDefault(Size, NextPiece);
            else if (Theme == 2)
                DisplayBoardRed(Size);
            else if (Theme == 3)
                DisplayBoardGreen(Size);
            else if (Theme == 4)
                DisplayBoardBlue(Size);

            auto current_time = chrono::high_resolution_clock::now();
            newPlayer[Play].time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();

            if (Downed == false){
                Sleep(TickTime);
                if (TickTime > 10)
                    TickTime--;
            }
        }

        TurnSolid(Size, Piece);

        if (!CheckOver(Size)){
            ClearScreen();
            cout << "Game Over!";
            getch();
            goto Menu;
        }

        FilledLine(Size);

        Piece = SelectPiece(Size, NextPiece);
    }
    return 0;
}
