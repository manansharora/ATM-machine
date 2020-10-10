#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <unistd.h>
//#include<windows.h>

using namespace std;

class ATM
{
private:
    long int acc_num;
    char username[20];
    int pin;
    double balance, amount;

    long int acc_num1;
    char username1[20];
    int pin1;
    double balance1;

public:
    void create_account()
    {
        ofstream fs("ATM.txt", ios::app);

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> pin;
        cout << "Enter account number: ";
        cin >> acc_num;
        balance = 0;

        // Save credentials in a file
        fs << acc_num << " " << username << " " << pin << " " << balance << " ";
        fs.close();
    }

    int login(char un[], int pw)
    {
        ifstream fs("ATM.txt", ios::in);
        while (!fs.eof())
        {
            fs >> acc_num >> username >> pin >> balance;

            // Check if login credentials are valid
            if (strcmp(un, this->username) == 0 && pw == pin)
            {
                cout << "\nLogin Successful!!\n";
                fs.close();
                return 1; // Return True if login successful and can proceed to withdraw/deposit
            }
        }
        fs.close();
        cout << "\nInvalid credentials";
        return 0; // Return False if login unsuccessful
    }

    void display_account()
    {

        cout << "\n\n\t------------------------------------------------------------------------------\n";
        cout << "\t|" << setw(18) << "ACC NUMBER |" << setw(18) << "NAME |" << setw(18) << "PIN |" << setw(18) << "BALANCE |";
        cout << "\n\n\t------------------------------------------------------------------------------\n";
        cout << "\t|" << setw(18) << " |" << setw(18) << " |" << setw(18) << " |" << setw(18) << "|" << endl;

        cout << "\t|" << setw(15) << acc_num << "  |" << setw(15) << username << "  |" << setw(15) << pin << "  |" << setw(15) << balance << "  |";
        cout << endl;

        //cout << "\t\t|" << setw(18) << " |" << setw(18) << " |" << setw(18) << " |" << setw(18) << "|" << endl;
        cout << "\n\t------------------------------------------------------------------------------\n";
    }

    void withdraw_deposit()
    {
        int choice;
        cout << "\nPress 1 to withdraw \nPress 2 to deposit\n";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nCurrent balance: " << balance << endl;
            cout << "\nEnter the amount to be withdrawn: ";
            cin >> amount;
            balance = balance - amount;
            cout << "\nCurrent balance: " << balance << endl;
        }
        else
        {
            cout << "\nCurrent balance: " << balance << endl;
            cout << "\nEnter the amount to be deposited: ";
            cin >> amount;
            balance = balance + amount;
            cout << "\nCurrent balance: " << balance << endl;
        }

        ifstream file1("ATM.txt:", ios::in);
        ofstream file2("temp.txt", ios::app);

        while (file1 >> acc_num1 >> username1 >> pin1 >> balance1)
        {
            if (acc_num1 != acc_num)
                file2 << acc_num1 << username1 << pin1 << balance1;
        }
        file1.close();
        file2.close();
        remove("ATM.txt");
        rename("temp.txt", "ATM.txt");

        ofstream fs("ATM.txt", ios::app);
        fs << acc_num << " " << username << " " << pin << " " << balance << " ";
        fs.close();
    }

    void modify_account()
    {
        cout << "\nEnter new Username: ";
        cin >> username;

        cout << "\nEnter new PIN: ";
        cin >> pin;
        
        ifstream file1("ATM.txt:", ios::in);
        ofstream file2("temp.txt", ios::app);

        while (file1 >> acc_num1 >> username1 >> pin1 >> balance1)
        {
            if (acc_num1 != acc_num)
                file2 << acc_num1 << username1 << pin1 << balance1;
        }
        file1.close();
        file2.close();
        remove("ATM.txt");
        rename("temp.txt", "ATM.txt");

        ofstream fs("ATM.txt", ios::app);
        fs << acc_num << " " << username << " " << pin << " " << balance << " ";
        fs.close();
    }
};


/*void loading()
{
    system("cls");
    //system("COLOR 8f");
    int i=0;
    system("COLOR 70");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<<setw(50);
    cout<<"Loading...\n";
    cout<<setw(40);
    for(i=0;i<10;i++)
    {
        if(i<5)
        {
            cout<<"|";
            Sleep(1000);
        }
        else
        {
            cout<<"|";
            Sleep(150);
        }
        
    }
    system("cls");
    system("COLOR 8f");
    cout<<"\t\t\t\t\t\t\tSuper Market Billing System\n\n\n";
    cout<<"\n";
    system("pause");
}*/

int main()
{
    //loading();
    ATM user;
    while (1)
    {
        char username[50];
        int pin, ch, logged_in = 0;
        cout << "\t\t****  Welcome to ATM ***";
        cout << "\n1. Login \n2. Create a New Account\n3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << " Username : ";
            cin >> username;
            cout << " Password : ";
            cin >> pin;
            logged_in = user.login(username, pin);
            break;
        case 2:
            user.create_account();
            break;
        case 3:
            exit(1);
        }

        if (logged_in)
        {
            cout << " \n------------ Menu ------------ \n";
            cout << "1. Display Account Info\n";
            cout << "2. Modify Account\n";
            cout << "3. Deposit/Withdraw cash\n";
            cout << "4. Logout\n";
            cout << "\nEnter your choice from menu: ";
            cin >> ch;

            switch (ch)
            {
            case 1:
                user.display_account();
                break;
            case 2:
                user.modify_account();
                break;
            case 3:
                user.withdraw_deposit();
                break;
            case 4:
                logged_in = 0;
            }
        }
    }
    return 0;
}
