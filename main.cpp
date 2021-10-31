/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
# include<bits/stdc++.h>          // header file
using namespace std;

// using time_t to access present date month and year
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

// creating an Authentication class to store the id pass and authenticate() method
class Authentication
{
    private:
        string id_ = "triptisharma";
        string password_ = "tripti";
    
    public:
        bool authenticate(string id, string password)        // check id id password entered is wrong or correct
        {
            if(id == id_ && password == password_)
                return 1;                                    // return 1 if correct 
            else 
                return 0;
        }
};

// creating below class to store the customer specific information
class CustomerRecords
{
    private:
        string depositorName_;       // Name of the Customer
        string accountNumber_;       // Account Number of the Customer
        string accountType_;         // Type of Account : Savings/Current
        float balance_;              // Balance in the account
        
    public:
        // default constructor
        CustomerRecords(){}
        
	// parameterized constructor also to add a new customer
        CustomerRecords(string depositorName, string accountNumber, string accountType, float balance)
        {
            this->depositorName_ = depositorName;
            this->accountNumber_ = accountNumber;
            this->accountType_ = accountType;
            this->balance_ = balance;     
	    // write the information to the file
            writeToFile();                    
        }
        
	// function to write the information to the file
        void writeToFile()
        {
            fstream fileOut;                                       // file handler
            fileOut.open("Records.txt", ios::out | ios::app);      // opening the Records.txt file 
            fileOut<<accountNumber_<<",";                          
            fileOut<<depositorName_<<",";
            fileOut<<accountType_<<",";
            fileOut<<balance_<<"\n";
        }
        
	// setters
        void setName(string depositorName)
        {
            depositorName_ = depositorName;
        }
        
        void setAccountNo(string accountNumber)
        {
            accountNumber_ = accountNumber;
        }
        
        void setAccountType(string accountType)
        {
            accountType_ = accountType;
        }
        
        void setBalance(float balance)
        {
            balance_ = balance;
        }
        
	// getters
        string getName()
        {
            return depositorName_;
        }
        
        string getAccountNo()
        {
            return accountNumber_;
        }
        
        string getAccountType()
        {
            return accountType_;
        }
        
        float getBalance()
        {
            return balance_;
        }
        
};

// function to dread data form file
void readFromFile(vector<CustomerRecords>& records)
{
    fstream fileInput;
    fileInput.open("Records.txt", ios::in);
    string line, word;
    
    while (!fileInput.eof())               // Read each line until end of file is reached
    {
        CustomerRecords tempObject;
        fileInput>>line;
        stringstream s(line);
        
        getline(s, word, ',');
        tempObject.setAccountNo(word);
        getline(s, word, ',');
        tempObject.setName(word);
        getline(s, word, ',');
        tempObject.setAccountType(word);
        getline(s, word, ',');
        //float tempBalance = stof(word);
        tempObject.setBalance(0.00);
        
	// storing in a temporary object and pushing the object to teh vector so created 
        records.push_back(tempObject);
    }
}

// Function to display the extracted contents of the file 
void displayFile(vector<CustomerRecords>& records)
{
    cout<<"\n*********** LIST OF CUSTOMERS ***********\n";
    for(int i=0;i<records.size(); i++)
    {
        cout<<"Customer "<<i+1<<" Account Number : "<<records[i].getAccountNo()<<endl;
        cout<<"Customer "<<i+1<<" Name : "<<records[i].getName()<<endl;
        cout<<"Customer "<<i+1<<" Account Type : "<<records[i].getAccountType()<<endl;
        cout<<"Customer "<<i+1<<" Account Balance : "<<records[i].getBalance()<<endl;
        cout<<"____________________________________________________________________\n";
    }
}

// function to delete any Customer's record
/*
   Simple logic delete the previous file
   re-create the file
   insert the data except for the given account number
*/
void deleteRecord(vector<CustomerRecords>& records, string toBeDeletedAN)
{
    remove("Records.txt");
    for(int i=0;i<records.size(); i++)
    {
        if(records[i].getAccountNo() != toBeDeletedAN)
        {
            records[i].writeToFile();
        }
    }
}

// function to generate the transaction id using random
string  generateRandom(int len) {
    string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return s;
}

// Transaction class to store the transaction details of the customer
class Transaction
{
    private:
        string transactionID_ = generateRandom(6);
        string operation_;
        float amount_;
        float balance_;
        int dateOfTransaction_ = timePtr->tm_mday;
        int monthOfTransaction_ = timePtr->tm_mon;
        int yearOfTransaction_ = timePtr->tm_year;
        CustomerRecords customer_;
    
    public:
        Transaction(){}    // Default constructor
        
	// Credit function to perform the credit operation
        void credit()
        {
            cout<<"\nEnter Account Number : ";
            string temp;
            cin>>temp;
            customer_.setAccountNo(temp);
            string fileName = "TR" + customer_.getAccountNo() + ".txt";
            cout<<"\nEnter amount to be credited : ";
            cin>>amount_;
            balance_ += amount_;              // update the balance
            operation_ = "Credit";
            writeToFile(fileName);           // update the file
        }
        
	// Debit function to perform the debit operation
        void debit()
        {
            cout<<"\nEnter Account Number : ";
            string temp;
            cin>>temp;
            customer_.setAccountNo(temp);
            string fileName = "TR" + customer_.getAccountNo() + ".txt";
            cout<<"\nEnter amount (in the multiples of 100) to be debited : ";
            cin>>amount_;
            balance_ -= amount_;          // update the balance
            operation_ = "Debit";   
            writeToFile(fileName);        // update the file
        }
        
	// function to open the transaction file of the customer and write into it
        void writeToFile(string fileName)
        {
            fstream fileOut;
            fileOut.open(fileName, ios::out | ios::app);
            fileOut<<transactionID_<<",";
            fileOut<<customer_.getAccountNo()<<",";
            fileOut<<operation_<<",";
            fileOut<<amount_<<",";
            fileOut<<balance_<<",";
            fileOut<<dateOfTransaction_<<",";
            fileOut<<monthOfTransaction_<<",";
            fileOut<<yearOfTransaction_<<"\n";
        }
        
	// function to open the transaction file of the customer and read from it
        void readFromFile(string fileName)
        {
            fstream fileInput;
            fileInput.open(fileName, ios::in);
            string line, word;
            
            while (!fileInput.eof())
            {
                fileInput>>line;
                stringstream s(line);
                
                getline(s, word, ',');
                transactionID_ = word;
                getline(s, word, ',');
                customer_.setAccountNo(word);
                getline(s, word, ',');
                operation_ = word;
                getline(s, word, ',');
                amount_ = stof(word);
                getline(s, word, ',');
                balance_ = stof(word);
                getline(s, word, ',');
                dateOfTransaction_ = stoi(word);
                getline(s, word, ',');
                monthOfTransaction_ = stoi(word);
                getline(s, word, ',');
                yearOfTransaction_ = stoi(word);
                
                displayTransactions();             // display the information so extracted
            }
        }
        
	// function to display the transaction details 
        void displayTransactions()
        {
            cout<<"\nTransaction ID : "<<transactionID_;
            cout<<"\nAccount Number : "<<customer_.getAccountNo();
            cout<<"\nCredited/Debited : "<<operation_;
            cout<<"\nAmount : "<<amount_;
            cout<<"\nBalance after Operation : "<<balance_;
            cout<<"\nDate : "<<dateOfTransaction_<<"/"<<monthOfTransaction_<<"/"<<yearOfTransaction_<<endl;
            cout<<"____________________________________________________________________\n";
        }
        
	// function to check if any interest is generated by checking the last operation (if done one month before)
        float calculateInterest()
        {
            int pd = timePtr->tm_mday;   // present day
            int pm = timePtr->tm_mon;    // present month
            int py = timePtr->tm_year;   // present year
            
            int bd = dateOfTransaction_;   // transaction day
            int bm = monthOfTransaction_;  // transaction month
            int by = yearOfTransaction_;   // transaction year
            
            int d, m, y;    // variables to store the difference between the days months and years of last transaction
            int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            y = py - by;
            if (pm < bm)
            {
                y--;
                m = 12 - (bm - pm);       
            }
            else
            {
                m = pm - bm;
            }
            if (pd < bd)
            {
                m--;
                d = md[pm - 1] - (bd - pd);
            }
            else
            {
                d = pd - bd;
            }
            
            if(m>0 || y>0)
            {
                return balance_*(3.5)*m*(12*y);
            }
            else 
                return 0;
        }
};

//
void addToCustomerRecord()
{
    string name, accountNumber, accountType;
    cout<< "\n******* Add a new Customer ******* \n";
    cout<<"\nEnter New Customer's Name : ";
    cin>>name;
    cout<<"Enter Account Number : ";
    cin>>accountNumber;
    cout<<"Enter Account Type (Savings or Current) : ";
    cin>>accountType;
    CustomerRecords newCustomer(name, accountNumber, accountType, 0.00);
}

int main()
{
    cout<<"\n:::::::::::::::WELCOME TO THE BANKING SYSTEM :::::::::::::::::::\n";
    cout<<"\n                       COSMOS BANK                              \n";
    
    Authentication employee;
    string id, password;
    cout<<"\n\n\nEnter login id : ";
    cin>>id;
    cout<<"Enter Password : ";
    cin>>password;
    if(!employee.authenticate(id, password))
    {
        cout<<"\n OOPS  !!!!   Invalid credentials \n:-( Terminating program!!!!!!! :-( ";
        return 0;
    }
    START:
    int option;
    
    cout<<"\nChoose option number \n";
    cout<<"\n1. Add a new Customer";
    cout<<"\n2. Display Records file (i.e details of all the customers) ";
    cout<<"\n3. Delete any customer information ";
    cout<<"\n4. Credit money to any Customer's Account";
    cout<<"\n5. Debit money from any Customer's Account";
    cout<<"\n6. Display last entry to Records file";
    cout<<"\n7. Check if an account exists";
    cout<<"\n8. Display Customer name using Account Number";
    cout<<"\n9. Display Customer balance using Account Number";
    cout<<"\n10. Get transaction ID and Details using Account Number";
    cout<<"\n11. Display Customer Information using Account Number";
    cout<<"\n12. Check Interest if earned any\n\nOption : ";
    
    cin>>option;
    switch(option)
    {
        case 1:
        {
            addToCustomerRecord();
            cout<<"\n>>>>>>> New Customer added <<<<<<\n";
            break;
        }
        case 2:
        {
            vector<CustomerRecords> customer;
            readFromFile(customer);
            displayFile(customer);
            cout<<"\n>>>>>>> Information Displayed <<<<<<\n";
            break;
        }
        case 3:
        {
            vector<CustomerRecords> customer;
            readFromFile(customer);
            string accountNumber;
            cout<<"\nEnter account number : ";
            cin>>accountNumber;
            deleteRecord(customer, accountNumber);
            cout<<"\n>>>>>>> Record Deleted <<<<<<\n";
            break;
        }
        case 4:
        {
            Transaction trans;
            trans.credit();
            cout<<"\n>>>>>>> Amount credited <<<<<<\n";
            break;
        }
        case 5:
        {
            Transaction trans;
            trans.debit();
            cout<<"\n>>>>>>> Amount debited <<<<<<\n";
            break;
        }
        case 6:
        {
            cout<<"Last Record Details :- \n";
            vector<CustomerRecords> customer;
            readFromFile(customer);
            cout<<"Customer "<<" Account Number : "<<customer[customer.size()-1].getAccountNo()<<endl;
            cout<<"Customer "<<" Name : "<<customer[customer.size()-1].getName()<<endl;
            cout<<"Customer "<<" Account Type : "<<customer[customer.size()-1].getAccountType()<<endl;
            cout<<"Customer "<<" Account Balance : "<<customer[customer.size()-1].getBalance()<<endl;
            cout<<"____________________________________________________________________\n";
            cout<<"\n>>>>>>> Information Displayed <<<<<<\n";
            break;
        }
        case 7:
        {
            cout<<"\nEnter account number to check : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            int flag =0;
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    flag = 1;
            }
            if(flag ==0)
                cout<<"\n\n #####   No Account found  ####\n";
            else
                cout<<"\n\n #####   Account found  ####\n";
            break;
        }
        case 8:
        {
            cout<<"\nEnter Account number to extract the name : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    cout<<"\nAccount Holder Name : "<<customer[i].getName()<<endl;
            }
            cout<<"\n>>>>>>> Name Displayed <<<<<<\n";
            break;
        }
        case 9:
        {
            cout<<"\nEnter Account number to extract the balance : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                    cout<<"\nAccount Holder Balance : Rs."<<customer[i].getBalance()<<endl;
            }
            cout<<"\n>>>>>>> Balance Displayed <<<<<<\n";
            break;
        }
        case 10:
        {
            cout<<"\nEnter Account number to see the transaction details : ";
            string accountNumber;
            cin>>accountNumber;
            string fileName = "TR" + accountNumber + ".txt";
            Transaction trans;
            trans.readFromFile(fileName);
            cout<<"\n>>>>>>> Transaction file displayed <<<<<<\n";
            break;
        }
        case 11:
        {
            cout<<"\nEnter Account number whose information to be displayed : ";
            string accountNumber;
            cin>>accountNumber;
            vector<CustomerRecords> customer;
            readFromFile(customer);
            for(int i=0; i<customer.size(); i++)
            {
                if(customer[i].getAccountNo() == accountNumber)
                {
                    cout<<"Customer "<<" Account Number : "<<customer[i].getAccountNo()<<endl;
                    cout<<"Customer "<<" Name : "<<customer[i].getName()<<endl;
                    cout<<"Customer "<<" Account Type : "<<customer[i].getAccountType()<<endl;
                    cout<<"Customer "<<" Account Balance : "<<customer[i].getBalance()<<endl;
                    cout<<"____________________________________________________________________\n";
                }
            }
            break;
        }
        case 12:
        {
            cout<<"\nEnter Account number to check if interest earned : ";
            string accountNumber;
            cin>>accountNumber;
            string fileName = "TR" + accountNumber + ".txt";
            Transaction trans;
            trans.readFromFile(fileName);
            cout<<"\nTotal Interest : "<<trans.calculateInterest();
            break;
        }
        default:
        {
            cout<<"\nInvalid option";
        }
    }
    
    
    return 0;
}