#include <iostream>
#include <cmath>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>

#define Screen_Width 90
#define Screen_Height 26
#define Win_Width 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int EnemyA[3];
int EnemyB[3];
int EnemyFlag[3];
char Car[4][4] = {' ','=','=',' ',
                  '=','=','=','=',
                  ' ','=','=',' ',
                  '=','=','=','='};

int CarPos = Win_Width/2;
int Score = 0;

void GoToxy(int x,int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console,CursorPosition);
}

void SetCursor(bool visible, DWORD size){
    if(size == 0){
        size = 20;
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}

void DrawBorder(){
    for(int i = 0; i<Screen_Height;i++){
        for(int j = 0; j<17;j++){
            GoToxy(0+j,i);
            cout << "~";
            GoToxy(Win_Width-j,i);
            cout << "~";
        }
    }
    for(int i=0;i<Screen_Height;i++){
        GoToxy(Screen_Width,i);
        cout << "~";
    }
}

void GenEnemy(int ind){
    EnemyA[ind] = 17 + rand() % (33);
}

void DrawEnemy(int ind){
    if(EnemyFlag[ind] == true){
        GoToxy(EnemyA[ind],EnemyB[ind]);
        cout << "----";
        GoToxy(EnemyA[ind],EnemyB[ind]+1);
        cout << " -- ";
        GoToxy(EnemyA[ind],EnemyB[ind]+2);
        cout << "----";
        GoToxy(EnemyA[ind],EnemyB[ind]+3);
        cout << " -- ";
    }
}

void EraseEnemy(int ind){
    if(EnemyFlag[ind] == true){
        GoToxy(EnemyA[ind],EnemyB[ind]);
        cout << "    ";
        GoToxy(EnemyA[ind],EnemyB[ind]+1);
        cout << "    ";
        GoToxy(EnemyA[ind],EnemyB[ind]+2);
        cout << "    ";
        GoToxy(EnemyA[ind],EnemyB[ind]+3);
        cout << "    ";
    }
}

void ResetEnemy(int ind){
    EraseEnemy(ind);
    EnemyB[ind] = 1;
    GenEnemy(ind);
}

void DrawCar(){
    for(int i=0; i<4; i++){
        for(int j=0;j<4;j++){
            GoToxy(j+CarPos,i+22);
            cout << Car[i][j];
        }
    }
}

void EraseCar(){
    for(int i=0; i<4; i++){
        for(int j=0;j<4;j++){
            GoToxy(j+CarPos,i+22);
            cout <<" ";
        }
    }
}

int Collision(){
    if(EnemyB[0] + 4 >= 23){
        if(EnemyA[0] + 4 - CarPos >= 0 && EnemyA[0] + 4 - CarPos < 9){
            return 1;
        }
    }
    return 0;
}

void GameOver(){
    system("cls");
    cout << endl;
    cout << "\t\t-----------------------------" << endl;
    cout << "\t\t--------- Game Over ---------" << endl;
    cout << "\t\t-----------------------------" << endl << endl;
    cout << "\t\tPress any key to go back to Menu.";
    getch();
}

void UpdateScore(){
    GoToxy(Win_Width + 7 , 5);
    cout << "Score : "<< Score << endl;
}

void Instructions(){
    system("cls");
    cout << "Instructions";
    cout << "\n-----------------------------";
    cout << "\n Avoid Cars by moving left or right. ";
    cout << "\n\n Press 'A' to move left";
    cout << "\n Press 'D' to move right";
    cout << "\n Press 'ESC' to exit";
    cout << "\n\n Press any key to go back to Menu";
    getch();
}

void Play(){
    CarPos = -1 + Win_Width/2;
    Score = 0;
    EnemyFlag[0] = 1;
    EnemyFlag[1] = 0;
    EnemyB[0] = EnemyB[1] = 1;

    system("cls");
    DrawBorder();
    UpdateScore();
    GenEnemy(0);
    GenEnemy(1);

    GoToxy(Win_Width + 7 , 2);
    cout << "CAR GAME";
    GoToxy(Win_Width + 6 , 4);
    cout << "--------";
    GoToxy(Win_Width + 6 , 6);
    cout << "--------";
    GoToxy(Win_Width + 7 , 12);
    cout << "CONTROLS";
    GoToxy(Win_Width + 7 , 13);
    cout << "--------";
    GoToxy(Win_Width + 2 , 14);
    cout << "Key A -> Left";
    GoToxy(Win_Width + 2 , 15);
    cout << "Key D -> Right";

    GoToxy(18,5);
    cout << "Press any key to Start";
    getch();
    GoToxy(18,5);
    cout << "                      ";

    while(1){
        if(kbhit()){
            char ch = getch();
            if(ch == 'a' || ch == 'A'){
                if(CarPos > 18){
                    CarPos -= 4;
                }
            }
            if(ch == 'd' || ch == 'D'){
                if(CarPos < 50){
                    CarPos += 4;
                }
            }
            if(ch == 27){
                break;
            }
        }

        DrawCar();
        DrawEnemy(0);
        DrawEnemy(1);
        if(Collision() == 1){
            GameOver();
            return;
        }
        Sleep(50);
        EraseCar();
        EraseEnemy(0);
        EraseEnemy(1);

        if(EnemyB[0] == 10){
            if(EnemyFlag[1] == 0){
                EnemyFlag[1] = 1;
            }
        }
        
        if(EnemyFlag[0] == 1){
            EnemyB[0] += 1;
        }
        
        if(EnemyFlag[1] == 1){
            EnemyB[1] += 1;
        }
        if(EnemyB[0] > Screen_Height - 4){
            ResetEnemy(0);
            Score++;
            UpdateScore();
        }
        if(EnemyB[1] > Screen_Height - 4){
            ResetEnemy(1);
            Score++;
            UpdateScore();
        }
    }
}

int main(){
    SetCursor(0,0);
    srand((unsigned)time(NULL));

    do{
        system("cls");
        GoToxy(10,5);
        cout << "----------------------";
        GoToxy(10,6);
        cout << "|      CAR GAME      |";
        GoToxy(10,7);
        cout << "----------------------";
        GoToxy(10,9);
        cout << "1.Start Game";
        GoToxy(10,10);
        cout << "2.Instructions";
        GoToxy(10,11);
        cout << "3.Quit";
        GoToxy(10,14);
        cout << "|   Select Option    |";
        char km = getche();

        if(km == '1'){
            Play();
        }
        else if(km == '2'){
            Instructions();
        }
        else if(km == '3'){
            exit(0);
        }
    }
    while (1);
    return 0;
}