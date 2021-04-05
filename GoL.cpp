#include <iostream>
//#include <windows.h> //for windows sistem 
#include <stdlib.h>
#include <unistd.h>
#include <chrono>

#include "checkpoint.h"
#include "countlive.h"

int Generation = 1;             // Кол-во генераций мир

void word_zero(int& hight, int& width, char** arr) {

    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            arr[i][j] = '#';
        }
    }
}

void PrintArrayWorld(int& hight, int& width, char** arr) {
    //system("cls");
    std::cout << '\n' << '\t' << "GENERATION: " << Generation << '\n';
    int i, j;

    for (i = 0; i < hight; i++) {
       
        for (j = 0; j < width - 1; j++) {
            std::cout << "     " << arr[i][j];
        }
        std::cout << "     " << arr[i][j] << "\n";
    }
    std::cout << '\n';
    
    /*Sleep(1000); for windiws*/ sleep(1);
}

int CheckInfinityArray(int& hight, int& width, char** arr, char** arr_copy) {
    int check = 0;
    
    for (int i = 0; i < hight; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] != arr_copy[i][j]) check++;
        }
    }

    if (check == 0) {
        std::cout << '\t' << "You ctreat infinity live" <<'\n';
        return 1;
    }
    else {
        return 0;
    }
}

// Инцилизация "живых клеток""
void Word_intilization(int& hight, int& width, char** arr) {
    int x, y; //Coordinat
    int i = 1;

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        std::cout << '\t' << i << " : ";
        std::cin >> x >> y;

        if((x >= 0) && (x < hight) && (y >= 0) && (y < width)) arr[x][y] = '*';

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;

        if (duration.count() >= 5) break;
        i++;
    }

    PrintArrayWorld(hight, width, arr);
}

void nextgeneration(int& hight, int& width, char** arr, char** arr_copy) {
    int count = 0;

    for (int i = 0; i < hight; ++i) {
        for (int j = 0; j < width; ++j) {
            count = countlive(i, j, hight, width, arr);
            if (arr[i][j] == '*') {
                if ((count == 3) || (count == 2)) {
                    continue;
                }
                else {
                    arr_copy[i][j] = '#';
                }
            }
            else if (arr[i][j] == '#') {
                if (count == 3) {
                    arr_copy[i][j] = '*';
                }
                else {
                    continue;
                }
            }
        }
    }

    if (CheckInfinityArray(hight, width, arr, arr_copy) != 0) exit(0);

    // Передача обновлённого поля для array_pole 
    for (int i = 0; i < hight; ++i) {
        for (int j = 0; j < width; ++j) {
            arr[i][j] = arr_copy[i][j];
        }
    }

    ++Generation;
    PrintArrayWorld(hight, width, arr);
} 

int Check_live(int& hight, int& width, char** arr) {
    int count = 0;

    for (int i = 0; i < hight; ++i) {
        for (int j = 0; j < width; ++j) {
            if (arr[i][j] == '*') {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    int hight, width;
    std::cout << "Enter the size of the playing field (hight width) " << '\t';
    std::cin >> hight >> width;

    char** array_pole = new char* [hight]; // Game fiald
    for (int count = 0; count < hight; ++count) array_pole[count] = new char[width];

    char** array_copy = new char* [hight]; // For Copt array
    for (int count = 0; count < hight; ++count) array_copy[count] = new char[width];

    word_zero(hight, width, array_pole); // First deadth
    Word_intilization(hight, width, array_pole); // New live

    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            array_copy[i][j] = array_pole[i][j];
        }
    }

    while (true) {
        int live = Check_live(hight, width, array_pole);

        if (live > 0) {
            nextgeneration(hight, width, array_pole, array_copy);
        }
        else {
            std::cout << "You dead" << '\n';
            break;
        }
    }

    delete[] array_pole;
    delete[] array_copy;
    return 0;
}
