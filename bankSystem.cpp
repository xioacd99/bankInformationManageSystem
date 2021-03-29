#include <iostream>

#include "FunctionImplemenation.h"

void welcome();
void mainmenu();
void turnToOperation(char choice);
void addRecordToDB();
void saveOrDrawMoney(int acno, bool choice);
void outputOneUserInformation(int acno);  // true for save money&false for draw
void outputDBInformation();
void deleteAccount(int acno);
void modifyAccount(int acno);

int main(int argc, const char** argv) {
    char choice = '\0';
    welcome();
    while (true) {
        mainmenu();
        std::cin >> choice;
        system("cls");
        turnToOperation(choice);
        std::cin.ignore();
        std::cin.get();
        if ('8' == choice) {
            break;
        }
    }
    return 0;
}