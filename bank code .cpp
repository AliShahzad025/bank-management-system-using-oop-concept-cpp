#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_USERS = 100;

class transaction {
public:
    transaction() {}

    void save(string name, int amount, string type) {
        ofstream file("transactions.txt", ios::app); // Open file in append mode
        if (file.is_open()) {
            file << name << "," << amount << "," << type << endl;
            file.close();
            cout << "Transaction details saved successfully!" << endl;
        }
        else {
            cout << "Unable to open file for saving transaction details!" << endl;
        }
    }
};

class user {
public:
    string pin;
    string name;
    string address;
    int limit;
    string accountid;
    string loginid;
    string phoneno;
    string password;
    string accountype;
    transaction t1;
    int amount;

    user() {}
    
    virtual void depositamount(int am) = 0;
    virtual void withdrawamount(int am) = 0;
    virtual void transferamount(int am, int id1, user* users) = 0;

};

class bankemployee {
public:
    bankemployee() {}

    bool approve() {
        string pass;
        cout << "Enter bank Employee Password : ";
        cin >> pass;
        if (pass == "password") {
            int c;
            cout << " Enter 1 to approve account " << endl;
            cout << " Enter 2 to reject account " << endl;
            cin >> c;
            if (c == 1) {
                cout << " Your account is approved" << endl;
                return true;
            }
            else {
                cout << " Your account is not approved " << endl;
                return false;
            }
        }
        else {
            cout << " Wrong password " << endl;
            return false;
        }
    }
    void card() {
        ifstream inFile("user.txt");
        ofstream outFile("card.txt");

        if (inFile.is_open() && outFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                istringstream iss(line);
                string name, address, card_num;

                getline(iss, name, ','); // Read name
                getline(iss, address, ','); // Read address

                // Generate 16-digit card number
                srand(time(nullptr));
                for (int i = 0; i < 16; ++i) {
                    int digit = rand() % 10; // Generate a random digit (0-9)
                    card_num += to_string(digit);
                }

                // Write name, address, and card number to card.txt
                outFile << "Name: " << name << ", Address: " << address << ", Card Number: " << card_num << endl;
            }

            inFile.close();
            outFile.close();
        }
        else {
            cerr << "Error: Unable to open file(s)." << endl;
        }
        ifstream inFile1("company.txt");
        ofstream outFile1("card.txt");

        if (inFile1.is_open() && outFile1.is_open()) {
            string line;
            while (getline(inFile1, line)) {
                istringstream iss(line);
                string name, address, card_num;

                getline(iss, name, ',');
                getline(iss, address, ','); // Read address

                // Generate 16-digit card number
                srand(time(nullptr));
                for (int i = 0; i < 16; ++i) {
                    int digit = rand() % 10; // Generate a random digit (0-9)
                    card_num += to_string(digit);
                }


                outFile1 << "Name: " << name << ", Address: " << address << ", Card Number: " << card_num << endl;
            }

            inFile1.close();
            outFile1.close();
        }
        else {
            cerr << "Error: Unable to open file(s)." << endl;
        }

    }
    void addcard(string name, string address, string cardno) {
        ofstream outFile1("card.txt", ios::app); // Open file in append mode
        if (outFile1.is_open()) {
            outFile1 << "Name: " << name << ", Address: " << address << ", Card Number: " << cardno << endl;
            outFile1.close();
        }
        else {
            cout << "Unable to open card file." << endl;
        }
    }

    void displayCard() {
        ifstream inFile("card.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        }
        else {
            cerr << "Error: Unable to open card file." << endl;
        }
    }



    void viewclient() {
        ifstream file("user.txt");
        if (file.is_open()) {
            string str;
            while (getline(file, str)) {
                cout << str << endl;
            }
            file.close();
        }
        else {
            cout << "Unable to open file for viewing user information!" << endl;
        }
    }

    void freeze() {
        cout << "Enter 1 to Freeze User's account\n";
        cout << "Enter 2 to Freeze Company Client's account\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        string name;
        if (choice == 1) {
            cout << "Enter User name: ";
            cin >> name;

            ifstream inFile("user.txt");
            ofstream tempFile("temp.txt");
            if (inFile.is_open() && tempFile.is_open()) {
                string line;
                bool found = false;
                while (getline(inFile, line)) {
                    if (line.find(name) == string::npos) {
                        tempFile << line << endl;
                    }
                    else {
                        found = true;
                        cout << "User's account with Name " << name << " is frozen\n";

                    }
                }
                inFile.close();
                tempFile.close();

                if (!found)
                    cout << "User with Name " << name << " not found\n";

                remove("user.txt");
                rename("temp.txt", "user.txt");
            }
            else {
                cerr << "Error: Unable to open file." << endl;
            }
        }
        else if (choice == 2) {
            cout << "Enter Company name: ";
            cin >> name;

            ifstream inFile("company.txt");
            ofstream tempFile("temp2.txt");
            if (inFile.is_open() && tempFile.is_open()) {
                string line;
                bool found = false;
                while (getline(inFile, line)) {
                    if (line.find(name) == string::npos) {
                        tempFile << line << endl;
                    }
                    else {
                        found = true;
                        cout << "Company's account with Name " << name << " is frozen\n";
                    }
                }
                inFile.close();
                tempFile.close();

                if (!found)
                    cout << "Company with Name " << name << " not found\n";

                remove("company.txt");
                rename("temp2.txt", "company.txt");
            }
            else {
                cerr << "Error: Unable to open file." << endl;
            }
        }
        else {
            cout << "Invalid choice!\n";
        }
    }


    void viewTransactionHistory() {
        ifstream inFile("transactions.txt");
        if (inFile.is_open()) {
            string name;
            cout << "Enter name: ";
            cin >> name;
            string line;
            bool found = false;
            while (getline(inFile, line)) {
                if (line.find(name) != string::npos) {
                    cout << line << endl;
                    found = true;
                }
            }
            if (found == false) {
                cout << "No Transaction History!\n";
            }
            inFile.close();
        }
        else {
            cerr << "Error: Unable to open transactions file." << endl;
        }
    }

};

class account : public user {
public:
    static int usercount;
    bankemployee* b1;
    string cnic;
    account() {
        usercount++;
        b1 = new bankemployee;
    }
    void depositamount(int am) {};
     void withdrawamount(int am) {};
     void  transferamount(int am, int id1, user* users) {};

   void create(bool person, string& filename) {
        if (limit <= 100000) {
            accountype = "Bronze";
        }
        else if (limit <= 500000) {
            accountype = "Gold";
        }
        if (limit > 500000 && person) {
            accountype = "Business";
        }

        cout << " Waiting for the bank Management to approve the system  " << endl;
        if (b1->approve()) {
            cout << "CONGRATULATIONS! YOUR ACCOUNT IS VERIFIED" << endl;
            cout << "Your account type is " << accountype << endl;
            accountid = generate_card_number();
            cout << "Your account no is :" << accountid << endl;
            cout << "Enter your 4 digit pin" << endl;
            cin >> pin;
            save(filename, pin);
            cout << "YOUR CARD NO IS " << accountid << endl;
            b1->addcard(name, address, accountid);

        }
        else if (!b1->approve()) {
            cout << "YOUR ACCOUNT IS NOT VERIFIED" << endl;
        }
    }

    string generate_card_number() {
        srand(time(nullptr));
        string card_num;
        for (int i = 0; i < 16; ++i) {
            int digit = rand() % 10; // Generate a random digit (0-9)
            card_num += to_string(digit);
        }
        return card_num;
    }

    void save(const string& filename, string password) {
        ofstream file(filename, ios::app); // Open file in append mode
        if (file.is_open()) {
            amount = 0;
            file << name << "," << address << "," << phoneno << "," << accountype << " ," << pin << "," << amount << endl;
            file.close();
            cout << "information saved successfully!" << endl;
        }
        else {
            cout << "Unable to open file for saving user information!" << endl;
        }
    }

    ~account() {
        delete b1;
    }
};

class userclient : public user {
public:
    userclient() {}
    int getAmount() const {
        string www = "23l-0719";
        return amount;
    }
    void display() {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneno << endl;
        cout << "Address: " << address << endl;
    }
    void displayamount() {
        cout << " Your available balance is: " << amount << endl;
    }
    void depositamount(int am) {


        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p) {
            amount += am;
            cout << " YOUR Amount " << am << " has been deposited" << endl;
            t1.save(name, amount, "deposit");

            updateAmountInFile();

        }
        else {
            cout << "Your amount can't be deposited " << endl;
        }
    }





    void withdrawamount(int am)override {

        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p) {
            if (am <= amount) {
                amount -= am;
                cout << " YOUR Amount " << am << " has been Withdrawn" << endl;
                t1.save(name, am, "Withdraw");

                updateAmountInFile();

            }
            else {
                cout << "Can't withdraw. Amount exceeds the available balance." << endl;
            }
        }
        else {
            cout << "Your amount can't be withdrawn" << endl;
        }
    }

    void updateAmountInFile() const {
        ifstream inFile("user.txt");
        ofstream tempFile("temp.txt");
        if (inFile.is_open() && tempFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Read name
                if (token == name) {
                    tempFile << name << "," << address << "," << phoneno << "," << accountype << "," << pin << "," << amount << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();
            remove("user.txt");
            rename("temp.txt", "user.txt");
        }
        else {
            cerr << "Error: Unable to open file." << endl;
        }
    }
    void transferamount(int am, int id1, user* users) {
        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p)
        {
            this->amount -= am;
            users[id1].amount += am;

            cout << " YOUR Amount " << am << " has been transfered to the account named" << users[id1].name << endl;
        }
        else cout << "Your amount cant be transfered" << endl;
    }
};

class companyclient : public user {
public:
    companyclient() {}
    int getAmount() const {
        return amount;
    }
    void display() {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneno << endl;
        cout << "Address: " << address << endl;
    }
    void displayamount() {
        cout << " Your available balance is: " << amount << endl;
    }
    bool loanapprove() {
        double amount;
        string pass;
        cout << "Enter bank Employee Password: ";
        cin >> pass;
        if (pass == "pass") {
            int c;
            cout << " Enter 1 to Approve Loan " << endl;
            cout << " Enter 2 to Reject Loan " << endl;
            cin >> c;
            if (c == 1)
            {
                cout << " Your Loan is Approved" << endl;
                cout << "Enter amount of loan: ";
                cin >> amount;

                depositamount(amount);
                return true;
            }
            else  cout << " Loan is not Approved " << endl;
            return false;
        }
        else {
            cout << " Wrong password " << endl;

        } return false;
    }

    void depositamount(int am)override {
      

        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p) {
            amount += am;
            cout << " YOUR Amount " << am << " has been deposited" << endl;
            t1.save(name, amount, "deposit");
           
                updateAmountInFile2();
            
        }
        else {
            cout << "Your amount can't be deposited " << endl;
        }
    }





    void withdrawamount(int am)override {
        cout << "Are you a 1.User Client or 2.Company Client?";
        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p) {
            if (am <= amount) {
                amount -= am;
                cout << " YOUR Amount " << am << " has been Withdrawn" << endl;
                t1.save(name, am, "Withdraw");
              
                    updateAmountInFile2();
             
            }
            else {
                cout << "Can't withdraw. Amount exceeds the available balance." << endl;
            }
        }
        else {
            cout << "Your amount can't be withdrawn" << endl;
        }
    }


    void updateAmountInFile2()const {
        ifstream inFile("company.txt");
        ofstream tempFile("temp.txt");
        if (inFile.is_open() && tempFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string token;
                getline(ss, token, ','); // Read name
                if (token == name) {
                    tempFile << name << "," << address << "," << accountype << "," << pin << "," << amount << endl;
                }
                else {
                    tempFile << line << endl;
                }
            }
            inFile.close();
            tempFile.close();
            remove("company.txt");
            rename("temp.txt", "company.txt");
        }
        else {
            cerr << "Error: Unable to open file." << endl;
        }
    }
    void transferamount(int am, int id1, user* users) {
        string p;
        cout << " Enter your pin :" << endl;
        cin >> p;
        if (pin == p)
        {
            this->amount -= am;
            users[id1].amount += am;

            cout << " YOUR Amount " << am << " has been transfered to the account named" << users[id1].name << endl;
        }
        else cout << "Your amount cant be transfered" << endl;
    }

};

int account::usercount = 0;

int loadUserData(const string& filename, userclient* users) {
    ifstream file(filename);
    int count = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line) && count < MAX_USERS) {
            istringstream iss(line);
            string field;
            getline(iss, field, ','); // Read name
            users[count].name = field;
            getline(iss, field, ','); // Read address
            users[count].address = field;
            getline(iss, field, ','); // Read phoneno
            users[count].phoneno = field;
            getline(iss, field, ','); // Read accountype
            users[count].accountype = field;
            getline(iss, field, ','); // Read pin 
            users[count].pin = field;
            iss >> users[count].amount; // Read amount
            count++;
        }
        file.close();
        cout << "User data loaded successfully!" << endl;
    }
    else {
        cout << "Unable to open file for loading user data!" << endl;
    }
    return count;
}

int loadCompanyData(const string& filename, companyclient* companies) {
    ifstream file(filename);
    int count = 0;
    //23l-0719
    if (file.is_open()) {
        string line;
        while (getline(file, line) && count < MAX_USERS) {
            istringstream iss(line);
            string field;
            getline(iss, field, ','); // Read company name
            companies[count].name = field;
            getline(iss, field, ','); // Read company address
            companies[count].address = field;
            getline(iss, field, ','); // Read company tax number

            companies[count].limit = stoi(field);
            getline(iss, field, ','); // Read account type
            companies[count].accountype = field;
            getline(iss, field, ','); // Read PIN 
            companies[count].pin = field;
            iss >> companies[count].amount; // Read amount

            count++;
        }
        file.close();
        cout << "Company data loaded successfully!" << endl;
    }
    else {
        cout << "Unable to open file for loading company data!" << endl;
    }
    return count;
}


userclient* searchById(userclient* users, int count, int searchId) {
    if (searchId >= 1 && searchId <= count) {
        return &users[searchId - 1]; // Adjust index to 0-based
    }
    else {
        cout << "Invalid search ID!" << endl;
        return nullptr;
    }
}

int main() {
    account* a1;
    userclient* users = new userclient[MAX_USERS];
    companyclient* companies = new companyclient[MAX_USERS];
    int numUsers = loadUserData("user.txt", users);
    int numCompanies = loadCompanyData("company.txt", companies);
    int searchId;
    bankemployee b5;
    b5.card();
start:
    
    cout << "Welcome to the Bank Management system" << endl;
    int choice;
    cout << "Enter 1 to login as a User" << endl;
    cout << "Enter 2 to login as a Company Employee" << endl;
    cout << "Enter 3 to login as a banking Employee" << endl;
    cout << "Enter 4 to create a Company Account" << endl;
    cout << "Enter 5 to create a User Account" << endl;
    cout << "Enter 6 to exit the system" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    if (choice == 1) {
        cout << "You are Entered as a User" << endl;

        cout << "Enter your search id: ";

        cin >> searchId;
        searchId -= 1;
        if (searchId <= numUsers && searchId >= 0) {
            users[searchId].display();

            cout << " Enter 1 to Deposit Amount " << endl;
            cout << " Enter 2 to Withdraw Amount " << endl;
            cout << " Enter 3 to view Available Amount " << endl;
            cout << " Enter 4 to transfer Amount " << endl;
            cout << " Enter 5 to Exit as a User  " << endl;
            int choice;
            int am1 = 0;
            cin >> choice;
            switch (choice) {

            case 1:

                cout << "Enter Amount to deposit :";
                cin >> am1;
                users[searchId].depositamount(am1);
                loadUserData("user.txt", users);
                break;
            case 2:

                cout << "Enter Amount to withdraw :";
                cin >> am1;
                users[searchId].withdrawamount(am1);
                loadUserData("user.txt", users);
                break;
            case 3:
                users[searchId].displayamount();
                break;
            case 4:

                cout << "Enter Amount to transfer :";
                cin >> am1;
                cout << "Enter Account id to transfer :";
                int id1;
                cin >> id1;
                users[searchId].transferamount(am1, id1, users);
                loadUserData("user.txt", users);

                break;
            case 6:
                break;
            }
            goto start;
        }
        else {
            cout << " Invalid search id " << endl;
            goto start;
        }
    }
    else if (choice == 2) {
        cout << "You are Entered as a Company Employee" << endl;

        cout << "Enter your search id: ";

        cin >> searchId;
        searchId -= 1;
        if (searchId <= numCompanies && searchId >= 0) {
            companies[searchId].display();

            cout << " Enter 1 to Deposit Amount " << endl;
            cout << " Enter 2 to Withdraw Amount " << endl;
            cout << " Enter 3 to view Available Amount " << endl;
            cout << " Enter 4 to transfer Amount " << endl;
            cout << " Enter 5 to propose a loan " << endl;
            cout << " Enter 6 to Exit as a Company Employee  " << endl;
            int choice;
            int am1 = 0;
            cin >> choice;
            switch (choice) {

            case 1:

                cout << "Enter Amount to deposit :";
                cin >> am1;
                companies[searchId].depositamount(am1);
                loadCompanyData("company.txt", companies);
                break;
            case 2:

                cout << "Enter Amount to withdraw :";
                cin >> am1;
                companies[searchId].withdrawamount(am1);
                loadCompanyData("company.txt", companies);
                break;
            case 3:
                companies[searchId].displayamount();
                break;
            case 4:

                cout << "Enter Amount to transfer :";
                cin >> am1;
                cout << "Enter Account id to transfer :";
                int id1;
                cin >> id1;
                companies[searchId].transferamount(am1, id1, companies);
                loadCompanyData("company.txt", companies);

                break;
            case 5:
                companies[searchId].loanapprove();
            case 6:
                break;
            }
            goto start;
        }
        else {
            cout << " Invalid search id " << endl;
            goto start;
        }
    }
    else if (choice == 3) {
        // Add your code here for banking employee login
        cout << "You have been logged in as Bank Employee!\n";
        int choice;
    label:
        cout << "\n Enter 1 to view Client's Accounts" << endl;
        cout << " Enter 2 to view Transactions" << endl;
        cout << " Enter 3 to Freeze an Account" << endl;
        cout << " Enter 4 to see Card details" << endl;
        cout << " Enter 5 to Exit as Bank Employee" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            bankemployee b2;
            b2.viewclient();
            goto label;
        }
        else if (choice == 2) {
            bankemployee b3;
            b3.viewTransactionHistory();
            goto label;
        }
        else if (choice == 3) {
            bankemployee b4;
            b4.freeze();
            goto label;
        }
        else if (choice == 4) {
           
            b5.displayCard();

            goto label;
        }
        else if (choice == 5) {

            goto start;
        }
        else {
            cout << "Invalid Choice!\n";
            goto start;
        }
    }
    else if (choice == 4) {

        a1 = new account;
        string file = "company.txt";
        cout << "Enter Company's Name: ";
        cin >> a1->name;
        cout << "Enter Company's Address: ";
        cin >> a1->address;
        cout << "Enter Company's Tax Number: ";
        cin >> a1->phoneno;
        cout << "Enter Estimated Daily Withdrawal Limit: ";
        cin >> a1->limit;
        a1->create(1, file);
        loadCompanyData("company.txt", companies);
        goto start;
    }
    else if (choice == 5) {

        a1 = new account;
        string file = "user.txt";
        cout << "Enter Full Name: ";
        cin >> a1->name;
        cout << "Enter Address: ";
        cin >> a1->address;
        cout << "Enter Phone no: ";
        cin >> a1->phoneno;
        cout << "Enter Cnic: ";
        cin >> a1->cnic;
        cout << "Enter Estimated daily limit: ";
        cin >> a1->limit;
        a1->create(0, file);
        loadUserData("user.txt", users);
        goto start;
    }
    else if (choice == 6) {
        return 0;
    }
    else {
        cout << "Enter a valid option" << endl;
        goto start;
    }
    delete[]users;
    delete[]companies;
    delete a1;

}
