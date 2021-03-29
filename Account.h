#ifndef ACCOUNT

#define ACCOUNT
#include <string>

#endif  // !ACCOUNT

const int NAME_SIZE = 15;

class Account {
public:
    void createANewAccount();
    void showInformationNonFormat() const;
    void showInformationFormat() const;
    void modifyAccount();
    void saveMoney(int amount);
    void drawMoney(int amount);
    int getAcno() const;
    int getDeposit() const;
    char getType() const;

private:
    int acno;
    char name[NAME_SIZE];
    int deposit;
    char type;
};