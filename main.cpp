#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>  // Для sleep() в Unix-системах; на Windows заменить на <windows.h> и Sleep()

using namespace std;

// Размеры экрана (упрощенно, для примера)
const int SCREEN_WIDTH = 20;
const int SCREEN_HEIGHT = 10;

// Создаем двумерный массив для хранения состояния экрана
vector<vector<char> > screenBuffer(SCREEN_HEIGHT, vector<char>(SCREEN_WIDTH, ' '));

void SaveScreen() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            // Считываем текущий символ с экрана
            screenBuffer[y][x] = ' '; // Упрощенно, сохраняем пробелы для примера
        }
    }
    cout << "Screen state saved." << endl;
}

void RestoreScreen() {
    // Очистка экрана (зависит от системы)
    cout << "\033[2J\033[H"; // ANSI-коды для очистки на UNIX, в Windows можно использовать system("cls");

    // Восстанавливаем данные из screenBuffer
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            cout << screenBuffer[y][x];
        }
        cout << endl;
    }
    cout << "Screen state restored." << endl;
}

void DrawExample() {
    // Пример рисования на экране
    cout << "\033[H"; // Переход к началу экрана
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            cout << (y % 2 == 0 ? '#' : '*');
        }
        cout << endl;
    }
}

int main() {
    cout << "Drawing initial screen..." << endl;
    DrawExample();

    // Сохранение текущего состояния
    SaveScreen();

    // Изменение экрана
    sleep(2); // Ждем 2 секунды
    cout << "Modifying the screen..." << endl;
    cout << "\033[H"; // Переход к началу экрана
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            cout << (y % 2 == 0 ? '*' : '#');
        }
        cout << endl;
    }

    // Восстановление состояния экрана
    sleep(2); // Ждем 2 секунды
    RestoreScreen();

    return 0;
}
