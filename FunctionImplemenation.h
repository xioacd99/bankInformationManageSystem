#ifndef BANK_SYSTEM_FUNCITON_IMPLEMENTATION

#define BANK_SYSTEM_FUNC_IMPLEMENTATION

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Account.h"

#endif  // !BANK_SYSTEM_FUNCITON_IMPLEMENTATION

// ! non-member function

void welcome() {
    std::cout << "\n\n\n\t   Bank";
    std::cout << "\n\n\t  System";
    std::cout << "\n\n\n\nMade By : xioacd";
    std::cin.get();
}

void mainmenu() {
    system("cls");
    std::cout << "\n\n\n\tMain Menu";
    std::cout << "\n\n\t01. New Account";
    std::cout << "\n\n\t02. Deposit Amount";
    std::cout << "\n\n\t03. Withdraw Amount";
    std::cout << "\n\n\t04. Balance Enquiry";
    std::cout << "\n\n\t05. All Acount Holder List (Adminitsrator)";
    std::cout << "\n\n\t06. Close An Account";
    std::cout << "\n\n\t07. Modify An Account";
    std::cout << "\n\n\t08. Exit";
    std::cout << "\n\n\tSelect Your Option (1-8)";
}

void turnToOperation(char choice) {
    int acno = 0;
    switch (choice) {
        case '1':
            addRecordToDB();
            break;
        case '2':
            std::cout << "\n\n\tEnter the account No: ";
            std::cin >> acno;
            saveOrDrawMoney(acno, true);
            break;
        case '3':
            std::cout << "\n\n\tEnter the account No: ";
            std::cin >> acno;
            saveOrDrawMoney(acno, false);
            break;
        case '4':
            std::cout << "\n\n\tEnter the account No: ";
            std::cin >> acno;
            outputOneUserInformation(acno);
            break;
        case '5':
            outputDBInformation();
            break;
        case '6':
            std::cout << "\n\n\tEnter the account No: ";
            std::cin >> acno;
            deleteAccount(acno);
            break;
        case '7':
            std::cout << "\n\n\tEnter the account No: ";
            std::cin >> acno;
            modifyAccount(acno);
            break;
        case '8':
            std::cout << "\n\n\tThanks for using bank management system.";
            break;
        default:
            std::cout << "\n\n\tInvalid input, please Check it.";
            std::cout << "\a";
            break;
    }
}

void addRecordToDB() {
    Account ac;
    std::ofstream outFile;
    outFile.open("data.dat", std::ios::binary | std::ios::app);
    ac.createANewAccount();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
    outFile.close();
}

// true for save money and false for draw
void saveOrDrawMoney(int acno, bool choice) {
    int amount = 0;
    bool found = false;
    Account ac;
    std::fstream File;
    File.open("data.dat", std::ios::binary | std::ios::in | std::ios::out);
    if (!File) {
        std::cout << "File could not be open. Press any key...";
        return;
    }

    while (!File.eof() && false == found) {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
        if (ac.getAcno() == acno) {
            ac.showInformationNonFormat();
            if (true == choice) {
                std::cout << "\n\n\tTo Deposite Amount ";
                std::cout << "\n\nEnter the Amount to Be Deposited";
                std::cin >> amount;
                ac.saveMoney(amount);
            } else {
                std::cout << "\n\n\tTo Withdraw Amount";
                std::cout << "\n\nEnter the Amount to Be Withdraw";
                std::cin >> amount;
                int balance = ac.getDeposit() - amount;
                if ((balance < 500 && ac.getType() == 'S') ||
                    balance < 1000 && ac.getType() == 'C') {
                    std::cout << "Insufficience Balance";
                } else {
                    ac.drawMoney(amount);
                }
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, std::ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }

    File.close();
    if (false == found) {
        std::cout << "\n\n Record not found ";
    }
}

void outputOneUserInformation(int acno) {
    Account ac;
    bool found = false;
    std::ifstream inFile;
    inFile.open("data.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be open, press any key...";
        return;
    }

    std::cout << "\nBalance Details\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        if (ac.getAcno() == acno) {
            ac.showInformationNonFormat();
            found = true;
        }
    }

    inFile.close();
    if (false == found) {
        std::cout << "\n\nAccount number does not exist.";
    }
}

void outputDBInformation() {
    Account ac;
    std::ifstream inFile;
    inFile.open("data.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be open, press any key...";
        return;
    }
    std::cout << "\n\n\t\tAccount Holder List\n\n";
    std::cout << "====================================================\n";
    std::cout << "A/c no." << std::setw(9) << " "
              << "Name" << std::setw(8) << " "
              << "Type"
              << " " << std::setw(10) << "Balance\n";
    std::cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        ac.showInformationFormat();
    }
    inFile.close();
}

void deleteAccount(int acno) {
    Account ac;
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open("data.dat", std::ios::binary);
    if (!inFile) {
        std::cout << "File could not be open, press any key...";
        return;
    }
    outFile.open("Temp.dat", std::ios::binary);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Account))) {
        if (ac.getAcno() != acno) {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("data.dat");
    rename("Temp.dat", "data.dat");
    std::cout << "\n\n\tRecord Deleted ..";
}

void modifyAccount(int acno) {
    bool found = false;
    Account ac;
    std::fstream File;
    File.open("data.dat", std::ios::binary | std::ios::in | std::ios::out);
    if (!File) {
        std::cout << "File could not be open, press any key...";
        return;
    }
    while (!File.eof() && false == found) {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Account));
        if (ac.getAcno() == acno) {
            ac.showInformationNonFormat();
            std::cout << "\n\nEnter the New Details of Account\n";
            ac.modifyAccount();
            int pos = (-1) * static_cast<int>(sizeof(Account));
            File.seekp(pos, std::ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Account));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (false == found) {
        std::cout << "\n\n Record Not Found ";
    }
}

// ! member function

void Account::createANewAccount() {
    std::cout << "\nEnter the account No. : ";
    std::cin >> acno;
    std::cout << "\n\nEnter the name of the account holder: ";
    std::cin.ignore();
    std::cin.getline(name, NAME_SIZE);
    std::cout << "\nEnter type of the account (C/S): ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "\nEnter the initial amount (>=500 for saving and >=1000 for "
                 "current) : ";
    std::cin >> deposit;
    std::cout << "\n\n\nAccount Created..";
}

void Account::showInformationNonFormat() const {
    std::cout << "\nAccount no. : " << acno;
    std::cout << "\nAccount holder name: ";
    std::cout << name;
    std::cout << "\nType of account : " << type;
    std::cout << "\nBalance amount : " << deposit;
}

void Account::showInformationFormat() const {
    std::cout << acno << std::setw(10) << " " << name << std::setw(10) << " "
              << type << std::setw(6) << " " << deposit << std::endl;
}

void Account::modifyAccount() {
    std::cout << "\nAccount no. : " << acno;
    std::cout << "\nModify account holder name: ";
    std::cin.ignore();
    std::cin.getline(name, 15);
    std::cout << "\nModify type of account: ";
    std::cin >> type;
    type = toupper(type);
    std::cout << "\nModify balance amount: ";
    std::cin >> deposit;
}

void Account::saveMoney(int amount) { deposit += amount; }

void Account::drawMoney(int amount) { deposit -= amount; }

int Account::getAcno() const { return acno; }

int Account::getDeposit() const { return deposit; }

char Account::getType() const { return type; }