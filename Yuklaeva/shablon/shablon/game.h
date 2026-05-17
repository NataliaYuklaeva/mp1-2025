#ifndef GAME_H
#define GAME_H

#include "shablon.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

using namespace std;

const char eMptY = '.';
const char ship = 'Ô';
const char boom = 'X';
const char miss = 'Î';

class Player {
protected:
    Matrix<char> field;
    Matrix<char> evilField;
    size_t shipsAlive;
    string name;

public:
    Player(const string& playerName, size_t boardSize = 10)
        : field(boardSize, boardSize, eMptY),
        evilField(boardSize, boardSize, eMptY),
        shipsAlive(0),
        name(playerName) {
    }

    virtual ~Player() {}

    virtual void placeShips() {
        vector<int> shipLengths = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
        for (int length : shipLengths) {
            bool placed = false;
            while (!placed) {
                int row = rand() % field.getRows();
                int col = rand() % field.getCols();
                bool hrztl = rand() % 2;

                if (canPlace(row, col, length, hrztl)) {
                    for (int i = 0; i < length; i++) {
                        if (hrztl)
                            field(row, col + i) = ship;
                        else
                            field(row + i, col) = ship;
                    }
                    placed = true;
                }
            }
        }
        shipsAlive = countShips();
    }

    virtual pair<int, int> getBoom() = 0;

    virtual bool receiveShot(int row, int col) {
        if (field(row, col) == ship) {
            field(row, col) = boom;
            shipsAlive--;
            return true;
        }
        if (field(row, col) == eMptY) {
            field(row, col) = miss;
        }
        return false;
    }

    bool alive() const {
        return shipsAlive > 0;
    }

    Matrix<char>& getEvilField() {
        return evilField;
    }

    const string& getName() const {
        return name;
    }

    void showOwnField() const {
        printField(field);
    }

    void showEvilField() const {
        cout << "\n" << "ïîëå ïðîòèâíèêà:\n";
        printField(evilField);
    }

protected:
    bool canPlace(int row, int col, int length, bool hrztl) {
        if (hrztl) {
            if (col + length > (int)field.getCols()) return false;
            for (int i = 0; i < length; ++i) {
                if (field(row, col + i) != eMptY) return false;
            }
        }
        else {
            if (row + length > (int)field.getRows()) return false;
            for (int i = 0; i < length; ++i) {
                if (field(row + i, col) != eMptY) return false;
            }
        }
        return true;
    }

    int countShips() const {
        int count = 0;
        for (size_t i = 0; i < field.getRows(); ++i)
            for (size_t j = 0; j < field.getCols(); ++j)
                if (field(i, j) == ship)
                    count++;
        return count;
    }

    void printField(const Matrix<char>& mat) const {
        cout << "   ";
        for (size_t j = 0; j < mat.getCols(); ++j) {
            cout << " " << j;
        }
        cout << "\n";

        for (size_t i = 0; i < mat.getRows(); ++i) {
            cout << " " << i << " ";
            for (size_t j = 0; j < mat.getCols(); ++j) {
                cout << " " << mat(i, j);
            }
            cout << "\n";
        }
        cout << endl;
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const string& playerName, size_t boardSize = 10)
        : Player(playerName, boardSize) {
    }

    pair<int, int> getBoom() {
        int row, col;
        cout << name << ", ââåäèòå êîîðäèíàòû (ñòðîêà ñòîëáåö, íàïðèìåð: 3 5): ";
        cin >> row >> col;
        return pair<int, int>(row, col);
    }

    void placeShips() {
        cout << name << ", ðàññòàíîâêà êîðàáëåé:\n";
        Player::placeShips();
        showOwnField();
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(const string& playerName, size_t boardSize = 10)
        : Player(playerName, boardSize) {
    }

    pair<int, int> getBoom() {
        int row = rand() % field.getRows();
        int col = rand() % field.getCols();
        cout << "Êîìïüþòåð ñòðåëÿåò ïî (" << row << ", " << col << ")\n";
        return pair<int, int>(row, col);
    }
};

class Game {
private:
    HumanPlayer* human;
    ComputerPlayer* computer;
    size_t boardSize;
    bool gameOver;

public:
    Game(size_t size = 10) : boardSize(size), gameOver(false) {
        srand(time(0));
        human = new HumanPlayer("Èãðîê", boardSize);
        computer = new ComputerPlayer("Êîìïüþòåð", boardSize);
    }

    ~Game() {
        delete human;
        delete computer;
    }

    void start() {
        cout << "\n!!! ÌÎÐÑÊÎÉ ÁÎÉ !!!\n\n";

        human->placeShips();
        computer->placeShips();
        cout << "\nÐÀÑÑÒÀÍÎÂÊÀ ÊÎÐÀÁËÅÉ ÊÎÌÏÜÞÒÅÐÀ (äëÿ ïðîâåðêè):\n";
        computer->showOwnField();

        cout << "\nÈãðà íà÷àëàñü!\n";

        while (!gameOver) {
            humanTurn();
            if (!computer->alive()) {
                cout << "\n ÂÛ ÏÎÁÅÄÈËÈ! \n";
                gameOver = true;
                break;
            }

            computerTurn();
            if (!human->alive()) {
                cout << "\n ÊÎÌÏÜÞÒÅÐ ÏÎÁÅÄÈË! \n";
                gameOver = true;
                break;
            }
        }

        showResults();
    }

private:
    void humanTurn() {
        cout << "\nÂÀØ ÕÎÄ\n";
        human->showEvilField();

        bool repeat = true;
        while (repeat) {
            pair<int, int> shot = human->getBoom();
            int row = shot.first;
            int col = shot.second;

            if (row < 0 || row >= (int)boardSize || col < 0 || col >= (int)boardSize) {
                cout << "Íåâåðíûå êîîðäèíàòû! Ïîïðîáóéòå ñíîâà.\n";
                continue;
            }

            if (human->getEvilField()(row, col) != eMptY) {
                cout << "Âû óæå ñòðåëÿëè ñþäà! Ïîïðîáóéòå äðóãèå êîîðäèíàòû.\n";
                continue;
            }

            bool hit = computer->receiveShot(row, col);
            if (hit) {
                human->getEvilField()(row, col) = boom;
            }
            else {
                human->getEvilField()(row, col) = miss;
            }

            if (hit) {
                cout << "ÏÎÏÀÄÀÍÈÅ!\n";
                if (!computer->alive()) {
                    repeat = false;
                }
                else {
                    cout << "Ñòðåëÿéòå åù¸ ðàç!\n";
                    human->showEvilField();
                }
            }
            else {
                cout << "ÏÐÎÌÀÕ!\n";
                repeat = false;
            }
        }
    }

    void computerTurn() {
        cout << "\nÕÎÄ ÊÎÌÏÜÞÒÅÐÀ\n";

        bool repeat = true;
        while (repeat) {
            pair<int, int> shot = computer->getBoom();
            int row = shot.first;
            int col = shot.second;

            bool hit = human->receiveShot(row, col);

            if (hit) {
                cout << "ÊÎÌÏÜÞÒÅÐ ÏÎÏÀË Â (" << row << ", " << col << ")!\n";
                if (!human->alive()) {
                    repeat = false;
                }
                else {
                    cout << "Êîìïüþòåð ñòðåëÿåò åù¸ ðàç!\n";
                }
            }
            else {
                cout << "ÊÎÌÏÜÞÒÅÐ ÏÐÎÌÀÕÍÓËÑß!\n";
                repeat = false;
            }
        }
    }

    void showResults() {
        cout << "\n!!! ÈÒÎÃÎÂÛÉ ÐÅÇÓËÜÒÀÒ !!!\n";
        cout << "\nÂàøå ïîëå:\n";
        human->showOwnField();

        cout << "\nÏîëå êîìïüþòåðà (ðåçóëüòàò âàøèõ âûñòðåëîâ):\n";
        human->showEvilField();
    }
};

#endif