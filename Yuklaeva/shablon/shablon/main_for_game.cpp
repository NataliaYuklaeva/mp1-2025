#include "game.h"
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Game game(10);
    game.start();
    return 0;
}