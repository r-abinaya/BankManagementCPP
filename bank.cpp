#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class Bank_Account
{
private:
    int accno;
    char type;
    char name[50];
    int balance;
public:
    void getinfo();
    void putinfo();
    void dep(int);
    void with(int);
    int bal();
    char acctyp();
    int retaccnum();
    void report();
};
void Bank_Account::getinfo()
{
        cout<<"Enter bank account number:";
        cin>>accno;
        cout<<"Enter account holder name:";
        cin.ignore();
	    cin.getline(name,50);
        cout<<"Enter the type of account(S/C):";
        cin>>type;
        type=toupper(type);
        cout<<"Enter initial balance for your account:";
        cin>>balance;
}
void Bank_Account::putinfo()
{
        cout<<"\n\tAccount Number:"<<accno;
        cout<<"\n\tAccount Holder:"<<name;
        cout<<"\n\tType of Account:"<<type;
        cout<<"\n\tCurrent Balance:"<<balance;
}
void Bank_Account::dep(int amt)
{
    balance+=amt;
}
void Bank_Account::with(int amt)
{
    balance-=amt;
}
int Bank_Account::bal()
{
    return balance;
}
int Bank_Account::retaccnum()
{
    return accno;
}
char Bank_Account::acctyp()
{
    return type;
}
void Bank_Account::report()
{
	cout<<accno<<setw(10)<<" "<<name<<setw(15)<<" "<<type<<setw(12)<<balance<<endl;
}

void create_account();
void deposit(int);
void withdraw(int);
void delete_account(int);
void balance_enquiry(int);
void acc_holders();
void update_ac(int);


int main()
{
    char ch;
    int num;
    do{

    cout<<endl<<endl<<endl;
    cout<<"-------BANK MANAGEMENT SYSTEM--------"<<endl;
    cout<<"\t 1.Create new account"<<endl;
    cout<<"\t 2.Deposit amount"<<endl;
    cout<<"\t 3.Withdraw amount"<<endl;
    cout<<"\t 4.Delete my account"<<endl;
    cout<<"\t 5.Balance enquiry"<<endl;
    cout<<"\t 6.All Account Holders of bank"<<endl;
    cout<<"\t 7.Updating Account"<<endl;
    cout<<"\t 8.Exit"<<endl;
    cout<<endl;
    cout<<"Enter your choice:";
    cin>>ch;
    switch(ch)
    {
    case '1':
        create_account();
        break;
    case '2':
        cout<<"\tPlease Enter The Bank_Account No. : ";
        cin>>num;
        deposit(num);
        break;
    case '3':
        cout<<"\tPlease Enter The Bank_Account No. : ";
        cin>>num;
        withdraw(num);
        break;
    case '4':
        cout<<"\tPlease Enter Your Bank_Account No. : ";
        cin>>num;
        delete_account(num);
        break;
    case '5':
        cout<<"\tPlease Enter Your Bank_Account No. : ";
        cin>>num;
        balance_enquiry(num);
        break;
    case '6':
        acc_holders();
        break;
    case '7':
        cout<<"\tPlease Enter Your Bank_Account No. : ";
        cin>>num;
        update_ac(num);
        break;
    case '8':
        system("CLS");
        cout<<"\n\n\tTQ...";
        break;
    default:
         cout<<"Invalid option";
    }
    cin.ignore();
    cin.get();
    }while(ch!=8);

    return 0;
}


void create_account()
{
    Bank_Account ac;
    ofstream outf;
    outf.open("details.dat",ios::binary|ios::app);
    ac.getinfo();
    outf.write(reinterpret_cast<char *> (&ac),sizeof(Bank_Account));
    outf.close();
}
void deposit(int accnum)
{
    int amt;
	bool found=false;
	Bank_Account ac;
	fstream File;
    File.open("details.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		if(ac.retaccnum()==accnum)
		{
			ac.putinfo();
				cout<<"\n\n\tPlease Enter The Money to be Deposited: ";
				cin>>amt;
				ac.dep(amt);
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\tRecord Not Found ";
}
void withdraw(int accnum)
{
    int amt;
	bool found=false;
	Bank_Account ac;
	fstream File;
    File.open("details.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
		if(ac.retaccnum()==accnum)
		{
			ac.putinfo();
				cout<<"\n\n\tPlease Enter The Money to be Deposited: ";
				cin>>amt;
				ac.with(amt);
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\tRecord Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\tRecord Not Found ";

}
void delete_account(int n)
{
     Bank_Account ac;
     ifstream inpf;
     ofstream outf;
     inpf.open("details.dat",ios::binary);
     if(!inpf)
     {
         cout<<"File could not be open !! Press any key...";
         return;
     }
     outf.write("temp.dat",ios::binary);
     inpf.seekg(0,ios::beg);
     while(inpf.read(reinterpret_cast<char*> (&ac),sizeof(Bank_Account)))
     {
         if(ac.retaccnum()!=n)
         {
             outf.write(reinterpret_cast<char*> (&ac),sizeof(Bank_Account));
         }
     }
    inpf.close();
	outf.close();
	remove("details.dat");
	rename("temp.dat","details.dat");
	cout<<"\n\nRecord Deleted ..";
}
void balance_enquiry(int n)
{
    Bank_Account ac;
    ifstream inpf;
    inpf.open("details.dat",ios::binary);
    if(!inpf)
    {
        cout<<"File could not be open\n";
        return;
    }
    bool found=false;
    while( inpf.read(reinterpret_cast<char*> (&ac),sizeof(Bank_Account))){
        if(ac.retaccnum()==n)
        {
            int balance=ac.bal();
            cout<<"\tYour account balance:"<<balance;
            found=true;
        }
    }
    inpf.close();
    if(found==false)
        cout<<"\n Record not found\n";
}
void acc_holders()
{
    Bank_Account ac;
	ifstream inFile;
	inFile.open("details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tBank_Account HOLDER LIST\n\n";
	cout<<"-----------------------------------------------------------------\n";
	cout<<"A/c no.      NAME           Type       Balance\n";
	cout<<"-----------------------------------------------------------------\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
	{
		ac.report();
	}
	inFile.close();

}
void update_ac(int n)
{
     Bank_Account ac;
    fstream inpf;
    inpf.open("details.dat",ios::binary|ios::in|ios::out);
    if(!inpf){
        cout<<"File could not be open!!";
        return;
    }
    bool found=false;
    while(found==false && !inpf.eof())
    {
        inpf.read(reinterpret_cast<char*> (&ac),sizeof(Bank_Account));
        if(ac.retaccnum()==n)
        {
            cout<<"Enter your details for Updation\n";
            ac.getinfo();
            int pos=(-1)*static_cast<int>(sizeof(ac));
            inpf.seekp(pos,ios::cur);
            inpf.write(reinterpret_cast<char*> (&ac),sizeof(Bank_Account));
            cout<<"Record has been updated..."<<endl;
            found=true;
        }
        inpf.close();
        if(found==false)
            cout<<"\nReccord not found";
    }
}
