#ifndef ACCOUNT

#define ACCOUNT

#endif  // !ACCOUNT

class Account {
public:
    Account() : acno(0), name(), deposit(0), type('\0') {}
    ~Account() {}

public:
    void createANewAccount();
    void showInformationNonFormat() const;  // check information(user)
    void showInformationFormat() const;     // check information(administrator)
    void modifyAccount();
    void saveMoney(int amount);
    void drawMoney(int amount);
    int getAcno() const;
    int getDeposit() const;
    char getType() const;

private:
    Account(const Account&);
    Account& operator=(const Account&);

private:
    static const int NAME_SIZE = 15;

private:
    int acno;
    char name[NAME_SIZE];
    int deposit;
    char type;
};

const int Account::NAME_SIZE;