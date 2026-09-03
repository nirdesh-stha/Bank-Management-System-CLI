#include<iostream>
#include<string>
#include<fstream>
#include<limits>
#include<iomanip>
using namespace std;

//Bank Management System CLI

class Account{
    public:
      string name;
      string lname;
      int citizen;
      int accountno;
      string password;
      int pin;
      double balance;

      void create(){
        cout<<"enter the firstname to open a Bank Account:"<<endl;
        cin>>name;
        cout<<"enter the lastname to open a Bank Account:"<<endl;
        cin>>lname;
        cout<<"enter the valid citizenship number:"<<endl;
        cin>>citizen;
        cout<<"set a password for your account:"<<endl;
        cin>>password;
        cout<<"set a pin for your account:"<<endl;
        cin>>pin;
        cout<<"enter your initial deposit amount:"<<endl;
        cin>>balance;
        while(cin.fail() || balance < 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid amount. Enter a valid initial deposit:"<<endl;
            cin>>balance;
        }
      }

      void save(){
        ofstream outFile("accounts.dat", ios::app);
        if(!outFile){
            cout<<"Error: could not open accounts.dat\n";
            return;
        }
        outFile << endl << name << " " << lname << "|" << citizen << "|" << accountno << "|" << password << "|" << pin << "|" << balance << "\n";
        outFile.close();
      }
};

class Welcome{
    public:
        Welcome(){
            cout << "\n";
            cout << "=========================================\n";
            cout << "        WELCOME TO Narayush BANK         \n";
            cout << "         Bank Management System          \n";
            cout << "=========================================\n";
            cout << "\n";
        }
};

double getBalance(int accno){
    ifstream inFile("accounts.dat");
    if(!inFile) return -1;

    string line;
    while(getline(inFile, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
        size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);
        size_t pos4 = (pos3 == string::npos) ? string::npos : line.find('|', pos3+1);
        size_t pos5 = (pos4 == string::npos) ? string::npos : line.find('|', pos4+1);

        if(pos1==string::npos || pos2==string::npos || pos3==string::npos || pos4==string::npos || pos5==string::npos) continue;

        string fileAccNo = line.substr(pos2+1, pos3-pos2-1);
        string fileBalance = line.substr(pos5+1);

        try{
            if(stoi(fileAccNo) == accno){
                return stod(fileBalance);
            }
        } catch(const exception&){
            continue;
        }
    }
    return -1;
}

bool updateBalance(int accno, double newBalance){
    ifstream inFile("accounts.dat");
    if(!inFile) return false;

    string allLines = "";
    string line;
    bool found = false;

    while(getline(inFile, line)){
        if(!line.empty()){
            size_t pos1 = line.find('|');
            size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
            size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);
            size_t pos4 = (pos3 == string::npos) ? string::npos : line.find('|', pos3+1);
            size_t pos5 = (pos4 == string::npos) ? string::npos : line.find('|', pos4+1);

            if(pos1!=string::npos && pos2!=string::npos && pos3!=string::npos && pos4!=string::npos && pos5!=string::npos){
                string fileAccNo = line.substr(pos2+1, pos3-pos2-1);
                try{
                    if(stoi(fileAccNo) == accno){
                        line = line.substr(0, pos5+1) + to_string(newBalance);
                        found = true;
                    }
                } catch(const exception&){
                }
            }
        }
        allLines += line + "\n";
    }
    inFile.close();

    if(!found) return false;

    ofstream outFile("accounts.dat", ios::trunc);
    if(!outFile) return false;
    outFile << allLines;
    outFile.close();

    return true;
}

string getAccountName(int accno){
    ifstream inFile("accounts.dat");
    if(!inFile) return "";

    string line;
    while(getline(inFile, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
        size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);

        if(pos1==string::npos || pos2==string::npos || pos3==string::npos) continue;

        string fileAccNo = line.substr(pos2+1, pos3-pos2-1);
        try{
            if(stoi(fileAccNo) == accno){
                return line.substr(0, pos1); 
            }
        } catch(const exception&){
            continue;
        }
    }
    return "";
}

int getAccountPin(int accno){
    ifstream inFile("accounts.dat");
    if(!inFile) return -1;

    string line;
    while(getline(inFile, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
        size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);
        size_t pos4 = (pos3 == string::npos) ? string::npos : line.find('|', pos3+1);
        size_t pos5 = (pos4 == string::npos) ? string::npos : line.find('|', pos4+1);

        if(pos1==string::npos || pos2==string::npos || pos3==string::npos || pos4==string::npos || pos5==string::npos) continue;

        string fileAccNo = line.substr(pos2+1, pos3-pos2-1);
        string filePin = line.substr(pos4+1, pos5-pos4-1);

        try{
            if(stoi(fileAccNo) == accno){
                return stoi(filePin);
            }
        } catch(const exception&){
            continue;
        }
    }
    return -1;
}

void saveTransaction(int fromAcc, int toAcc, double amount){
    ofstream outFile("transactions.dat", ios::app);
    if(!outFile){
        cout<<"Warning: could not open transactions.dat to record transaction history.\n";
        return;
    }
    outFile << "TRANSFER" << "|" << fromAcc << "|" << toAcc << "|" << amount << "\n";
    outFile.close();
}
// END ADDED


class GenerateA: public Account{
  public:
    int no=1000;
    void accno(){
      accountno = no;      
      no++;                
      cout<<"your account number is "<<accountno<<endl;
      cout<<"Your Account has been successfully created"<< endl;
    }

    bool login(){
      int loginAccNo;
      string loginPass;
      int loginPin; 

      cout << "Enter your account number: ";
      cin >> loginAccNo;
      cout << "Enter your password: ";
      cin >> loginPass;
      cout << "Enter your PIN: ";
      cin >> loginPin;
      if(cin.fail()){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid PIN input.\n";
          return false;
      }

      ifstream inFile("accounts.dat");
      if(!inFile){
          cout << "Error: could not open accounts.dat\n";
          return false;
      }

      string line;
      bool found = false;

      while(getline(inFile, line)){
          if(line.empty()) continue;

          size_t pos1 = line.find('|');
          size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
          size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);
          size_t pos4 = (pos3 == string::npos) ? string::npos : line.find('|', pos3+1);

          if(pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;

          string fileAccNo = line.substr(pos2+1, pos3-pos2-1);
          string filePass  = line.substr(pos3+1, pos4-pos3-1);

          try{
              if(stoi(fileAccNo) == loginAccNo && filePass == loginPass){
                  found = true;
                  break;
              }
          } catch(const exception&){
              continue;
          }
      }
      inFile.close();

      if(!found){
          cout << "Invalid account number or password.\n";
          return false;
      }

   
      int storedPin = getAccountPin(loginAccNo);
      if(storedPin < 0 || storedPin != loginPin){
          cout << "Invalid PIN.\n";
          return false;
      }

      accountno = loginAccNo;
      balance = getBalance(accountno);
      cout << "Login Successful\n";
      return true;
    }

    void checkBalance(){
        double bal = getBalance(accountno);
        if(bal < 0){
            cout << "Could not retrieve balance.\n";
            return;
        }
        balance = bal;
        cout << "Your current balance is: " << balance << endl;
    }

    void deposit(){
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        if(cin.fail() || amount <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount.\n";
            return;
        }

        double current = getBalance(accountno);
        if(current < 0){
            cout << "Could not retrieve balance.\n";
            return;
        }

        double updated = current + amount;
        if(updateBalance(accountno, updated)){
            balance = updated;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Deposit failed.\n";
        }
    }

    void withdraw(){
        int enteredPin;
        cout << "Enter your PIN to authorize withdrawal: ";
        cin >> enteredPin;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid PIN input.\n";
            return;
        }
        int storedPin = getAccountPin(accountno);
        if(storedPin < 0 || enteredPin != storedPin){
            cout << "Incorrect PIN. Withdrawal cancelled.\n";
            return;
        }

        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if(cin.fail() || amount <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount.\n";
            return;
        }

        double current = getBalance(accountno);
        if(current < 0){
            cout << "Could not retrieve balance.\n";
            return;
        }

        if(amount > current){
            cout << "Insufficient balance. Current balance: " << current << endl;
            return;
        }

        double updated = current - amount;
        if(updateBalance(accountno, updated)){
            balance = updated;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Withdrawal failed.\n";
        }
    }

    void transfer(){
        

        int receiverAcc;
        cout << "Enter receiver's account number: ";
        cin >> receiverAcc;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid account number.\n";
            return;
        }

        if(receiverAcc == accountno){
            cout << "You cannot transfer money to your own account.\n";
            return;
        }

        double receiverBalance = getBalance(receiverAcc);
        if(receiverBalance < 0){
            cout << "Transfer failed: receiver account does not exist.\n";
            return;
        }

        double senderBalance = getBalance(accountno);
        if(senderBalance < 0){
            cout << "Transfer failed: could not retrieve your account details.\n";
            return;
        }

        double amount;
        cout << "Enter amount to transfer: ";
        cin >> amount;
        if(cin.fail() || amount <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount.\n";
            return;
        }
    
        int enteredPin;
        cout << "Enter your PIN to authorize transfer: ";
        cin >> enteredPin;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid PIN input.\n";
            return;
        }
        int storedPin = getAccountPin(accountno);
        if(storedPin < 0 || enteredPin != storedPin){
            cout << "Incorrect PIN. Transfer cancelled.\n";
            return;
        }
    
        if(amount > senderBalance){
            cout << "Transfer failed: insufficient balance. Current balance: " << senderBalance << endl;
            return;
        }

        double newSenderBalance = senderBalance - amount;
        double newReceiverBalance = receiverBalance + amount;

        if(!updateBalance(accountno, newSenderBalance)){
            cout << "Transfer failed: could not update your account. No changes were made.\n";
            return;
        }

        if(!updateBalance(receiverAcc, newReceiverBalance)){
            updateBalance(accountno, senderBalance); 
            cout << "Transfer failed: could not update receiver account. Your balance has been restored.\n";
            return;
        }

        balance = newSenderBalance;
        saveTransaction(accountno, receiverAcc, amount);

        cout << "Transfer successful! Rs. " << amount << " sent to account " << receiverAcc << ".\n";
        cout << "Your new balance: " << balance << endl;
    }
    
    void statement(){
        double bal = getBalance(accountno);
        if(bal < 0){
            cout << "Could not retrieve account details.\n";
            return;
        }
        balance = bal;
        string holderName = getAccountName(accountno);

        cout << "\n========== ACCOUNT STATEMENT ==========\n";
        cout << "Account Number  : " << accountno << endl;
        cout << "Account Holder  : " << holderName << endl;
        cout << "Current Balance : " << balance << endl;
        cout << "----------------------------------------\n";
        cout << "Transaction History (Transfers):\n";

        ifstream inFile("transactions.dat");
        if(!inFile){
            cout << "No transactions found.\n";
            cout << "========================================\n";
            return;
        }

        string line;
        bool any = false;

        while(getline(inFile, line)){
            if(line.empty()) continue;

            size_t pos1 = line.find('|');
            size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
            size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);

            if(pos1==string::npos || pos2==string::npos || pos3==string::npos) continue;

            string type   = line.substr(0, pos1);
            string fromStr = line.substr(pos1+1, pos2-pos1-1);
            string toStr   = line.substr(pos2+1, pos3-pos2-1);
            string amtStr  = line.substr(pos3+1);

            try{
                int fromAcc = stoi(fromStr);
                int toAcc   = stoi(toStr);
                double amt  = stod(amtStr);

                if(fromAcc == accountno){
                    cout << "[" << type << "] Sent Rs. " << amt << " to Account " << toAcc << endl;
                    any = true;
                } else if(toAcc == accountno){
                    cout << "[" << type << "] Received Rs. " << amt << " from Account " << fromAcc << endl;
                    any = true;
                }
            } catch(const exception&){
                continue;
            }
        }
        inFile.close();

        if(!any){
            cout << "No transactions found.\n";
        }
        cout << "========================================\n";
    }
};

bool readChoice(int &value); 

struct AdminView{
    int accountno;
    string holderName;
    string citizen;
    double balance;
};

bool parseAdminView(const string &line, AdminView &out){
    if(line.empty()) return false;
 
    size_t pos1 = line.find('|');
    size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
    size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);
    size_t pos4 = (pos3 == string::npos) ? string::npos : line.find('|', pos3+1);
    size_t pos5 = (pos4 == string::npos) ? string::npos : line.find('|', pos4+1);
 
    if(pos1==string::npos || pos2==string::npos || pos3==string::npos || pos4==string::npos || pos5==string::npos) return false;
 
    string name    = line.substr(0, pos1);
    string citizen = line.substr(pos1+1, pos2-pos1-1);
    string accStr  = line.substr(pos2+1, pos3-pos2-1);
    string balStr  = line.substr(pos5+1);
 
    try{
        out.accountno  = stoi(accStr);
        out.holderName = name;
        out.citizen    = citizen;
        out.balance    = stod(balStr);
    } catch(const exception&){
        return false;
    }
    return true;
}
 
void printAdminHeader(){
    cout << left
         << setw(12) << "Acc No"
         << setw(24) << "Holder Name"
         << setw(18) << "Citizenship No"
         << right << setw(14) << "Balance" << "\n";
    cout << string(68, '-') << "\n";
}
 
void printAdminRow(const AdminView &v){
    cout << left
         << setw(12) << v.accountno
         << setw(24) << v.holderName
         << setw(18) << v.citizen
         << right << setw(14) << fixed << setprecision(2) << v.balance << "\n";
}
 
void adminViewAll(){
    ifstream inFile("accounts.dat");
    if(!inFile){
        cout << "Error: could not open accounts.dat\n";
        return;
    }
 
    cout << "\n================= CLIENT ACCOUNTS =================\n";
    printAdminHeader();
 
    string line;
    bool any = false;
    while(getline(inFile, line)){
        AdminView v;
        if(parseAdminView(line, v)){
            printAdminRow(v);
            any = true;
        }
    }
    inFile.close();
 
    if(!any){
        cout << "No accounts found.\n";
    }
    cout << "=====================================================\n";
}
 
void adminSearch(){
    int accno;
    cout << "Enter account number to find: ";
    cin >> accno;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid account number.\n";
        return;
    }
 
    ifstream inFile("accounts.dat");
    if(!inFile){
        cout << "Error: could not open accounts.dat\n";
        return;
    }
 
    string line;
    bool found = false;
    while(getline(inFile, line)){
        AdminView v;
        if(parseAdminView(line, v) && v.accountno == accno){
            cout << "\n---------------- CLIENT FOUND ----------------\n";
            printAdminHeader();
            printAdminRow(v);
            cout << "------------------------------------------------\n";
            found = true;
            break;
        }
    }
    inFile.close();
 
    if(!found){
        cout << "No account found with number " << accno << ".\n";
    }
}

bool adminLogin(){
    const string ADMIN_USER = "admin";
    const string ADMIN_PASS = "admin123";
 
    string user, pass;
    cout << "Enter admin username: ";
    cin >> user;
    cout << "Enter admin password: ";
    cin >> pass;
 
    if(user == ADMIN_USER && pass == ADMIN_PASS){
        cout << "Admin login successful.\n";
        return true;
    }
    cout << "Invalid admin credentials.\n";
    return false;
}
 
void adminMenu(){
    if(!adminLogin()) return;
 
    int achoice = 0;
    do{
        cout << "\n--- ADMIN PANEL ---\n";
        cout << "1. View all client accounts\n";
        cout << "2. Search a client by account number\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
 
        if(!readChoice(achoice)){
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
 
        switch(achoice){
            case 1:
                adminViewAll();
                break;
            case 2:
                adminSearch();
                break;
            case 3:
                cout << "Admin logged out.\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while(achoice != 3);
}

bool readChoice(int &value){
    cin >> value;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int loadNextAccountNo(){
    ifstream inFile("accounts.dat");
    int maxNo = 999;
    string line;
    while(getline(inFile, line)){
        if(line.empty()) continue;

        size_t pos1 = line.find('|');
        size_t pos2 = (pos1 == string::npos) ? string::npos : line.find('|', pos1+1);
        size_t pos3 = (pos2 == string::npos) ? string::npos : line.find('|', pos2+1);

        if(pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;

        string accNoStr = line.substr(pos2+1, pos3-pos2-1);
        try{
            int accNo = stoi(accNoStr);
            if(accNo > maxNo) maxNo = accNo;
        } catch(const exception&){
            continue;
        }
    }
    return maxNo + 1;
}

int main(){
    Welcome w;
    GenerateA c;
    c.no = loadNextAccountNo();
    int choice = 0;
    do{
        cout<< "1. Create a Bank Account\n";
        cout<< "2. Login\n";
        cout<< "3. Admin Login\n";
        cout<< "4. Close\n";
        cout<< "Enter your choice: ";

        if(!readChoice(choice)){
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: 
                c.create();
                c.accno();
                c.save();
                break;
            case 2: {
                if(!c.login()){
                    break;
                }
                int choic = 0;
                do{
                    cout<< "1. Check Balance\n";
                    cout<< "2. Deposit Money\n";
                    cout<< "3. Withdraw Money\n";
                    cout<< "4. Transfer Money\n";
                    cout<< "5. Statement\n";
                    cout<< "6. Logout\n";
                    cout<< "Enter your choice: ";

                    if(!readChoice(choic)){
                        cout << "Invalid input! Please enter a number.\n";
                        continue;
                    }

                    switch (choic) {
                        case 1: 
                            c.checkBalance();
                            break;
                        case 2:
                            c.deposit();
                            break;
                        case 3:
                            c.withdraw();
                            break;
                        case 4:
                            c.transfer(); 
                            break;
                        case 5:
                            c.statement(); 
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Invalid choice!\n";
                    }
                }while(choic!=6);
                break;
            }
            case 3:
                adminMenu();
                break;
            case 4:
                cout << "Logged out"<<endl;
                break;
            default:
                cout << "Invalid choice!\n";
        }
        }while(choice!=4);
        
        return 0;
}