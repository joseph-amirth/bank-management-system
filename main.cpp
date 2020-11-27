#include <conio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;

struct account {
	char name[20], password[20];
	long long account_no;
	double balance;
} a;

void create() {
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	char password1[20], password2[20];
	while (true) {
		cout << "Enter your name\n";
		gets(a.name);
		gets(a.name);
		cout << "Enter password\n";
		gets(password2);
		cout << "Confirm password\n";
		gets(password1);
		if (strcmp(password2, password1) != 0) {
			cout << "Error. Enter the details again";
			getch();
		} else {
			strcpy(a.password, password1);
			break;
		}
	}
	a.account_no = rng() % 10000000000ll;
	cout << "Your account has been created\nYour account number is " << a.account_no << '\n';
	cout << "Enter the amount to be deposited\n";
	cin >> a.balance;
	cout << "\nThe details of your account:\n";
	cout << "Name: " << a.name << "\nPassword: " << a.password << "\nAccount Number: " << a.account_no << "\nBalance: "
		 << a.balance;
}

void write() {
	ofstream ofile;
	ofile.open("account.bin", ios::out | ios::binary);
	ofile.write((char *) &a, sizeof(a));
	ofile.close();
}

double car_rate(double p) {
	double r;
	if (p > 250000)
		r = 5;
	else if (p > 500000)
		r = 5.7;
	else if (p > 1000000)
		r = 6.1;
	else
		r = 6.7;
	return r;
}

double house_rate(double p) {
	double r;
	if (p > 2000000)
		r = 9;
	else if (p > 3000000)
		r = 9.5;
	else if (p > 5000000)
		r = 10;
	else
		r = 11;
	return r;
}

double rate(double p) {
	double r;
	if (p > 10000)
		r = 5;
	else if (p > 50000)
		r = 7;
	else if (p > 100000)
		r = 10;
	else
		r = 12;
	return r;
}

void simple_interest(double p, double r) {
	double t;
	cout << "\nEnter the period of time for which you want to borrow the money (in years) ";
	cin >> t;
	double SI;
	SI = p * r * t / 100;
	cout << "The total amount to be paid at the end of the time period is " << p + SI << '\n';
	cout << "The money has been successfully deposited into your account\n";
	a.balance = a.balance + p;
}

void fixed_deposit() {
	cout << "\nEnter the amount of money you want to deposit\n";
	int d;
	cin >> d;
	if (d > a.balance) {
		cout << "You do not have enough balance in you account\n";
		cout << "Enter a different amount\n";
		fixed_deposit();
	} else {
		cout << "The percentage interest is " << house_rate(d) << '\n';
		cout << "Enter the time for which you want to deposit the money(in years)\n";
		int t;
		cin >> t;
		double si;
		si = d * house_rate(d) * t / 100;
		cout << "You will earn Rs. " << d + si << " at the end of your time period\n";
		cout << "The money you have deposited has successfully been deducted from you main balance\n";
		a.balance -= d;
	}
}

void change() {
	char name[20], password[20];
	while (true) {
		cout << "Enter Name\n";
		gets(name);
		gets(name);
		cout << "Enter Password\n";
		gets(password);
		if (strcmp(name, a.name) != 0 || strcmp(password, a.password) != 0) {
			cout << "The Username or Password is wrong\n";
			cout << "Please retype Username and Password\n";
		} else {
			cout << "You have accessed your account\n";
			break;
		}
	}
	getch();
	int c;
	while (true) {
		cout << "1 Deposit Money\n2 Withdraw Money\n3 Change Password\n4 Apply for Loan\n5 Check Balance\n6 Log Out\n";
		cout << "Enter your choice\n";
		cin >> c;
		switch (c) {
			case 1:
			d1:
				cout << "\n1. Fixed deposit\n2. Savings\nEnter your choice\n";
				int l;
				cin >> l;
				switch (l) {
					case 1:
						fixed_deposit();
						write();
						break;
					case 2:
						cout << "Enter the amount you want to deposit\n";
						int s;
						cin >> s;
						a.balance += s;
						write();
						break;
					default:
						cout << "Wrong choice please enter again";
						getch();
						goto d1;
				}
				getch();
				break;
			case 2:
				int amount;
				while (true) {
					cout << "Enter the amount you want to withdraw\n";
					cin >> amount;
					if (amount > a.balance) {
						cout << "You do not have enough money for transaction in your account\n";
						cout << "Please enter a different amount";
					} else {
						a.balance -= amount;
						cout << "Your new balance is " << a.balance << "\n\n";
						write();
						break;
					}
				}
				break;
			case 3:
				char password1[10], password2[10];
				while (true) {
					cout << "Enter the new password\n";
					gets(password1);
					gets(password1);
					cout << "Confirm new password\n";
					gets(password2);
					if (strcmp(password1, password2) != 0) {
						cout << "Passwords did not match, retype new password\n";
					} else {
						strcpy(password1, a.password);
						cout << "Your password has been changed\n\n";
						break;
					}
				}
				write();
				break;
			case 4:
			d2:
				cout << "1 Personal loan\n2 Car Loan\n3 Home Loan\nEnter the type of loan you require\n";
				int x;
				cin >> x;
				double loan;
				switch (x) {
					case 1:
						cout << "Enter the amount you want to borrow (minimum amount 10,000)\n";
						cin >> loan;
						cout << "The rate of interest per annum is " << rate(loan);
						simple_interest(loan, rate(loan));
						cout << "\nYour loan has been sanctioned,the amount has been transferred to your account\n";
						getch();
						break;
					case 2:
						cout << "Enter the amount of loan required to purchase your car\n";
						cin >> loan;
						simple_interest(loan, car_rate(loan));
						cout << "Your loan has been sanctioned,the amount has been transferred to your account\n";
						cout << "Your car will belong to the bank(as collateral) and will remain so till the loan has be paid off completely\n";
						getch();
						break;
					case 3:
						cout << "Enter the amount of loan required to purchase your house\n";
						cin >> loan;
						simple_interest(loan, house_rate(loan));
						cout << "Your loan has been sanctioned,the amount has been transferred to your account\n";
						cout << "Your house will belong to the bank (as collateral) and will remain so till the loan has be paid off completely\n";
						getch();
						break;
					default:
						cout << "Wrong choice. Enter again\n";
						getch();
						goto d2;
				}
				break;
			case 5:
				cout << "Your Balance is " << a.balance << '\n';
				getch();
				break;
			case 6:
				return;
			default:
				cout << "Error!! :(\n";
		}
	}
}

int main() {
	cout << "____________________________________________________\n";
	cout << "                    Cyber Bank\n";
	cout << "____________________________________________________";

	int b = 0;
	while (b != 3) {
		cout << "\n\n1 Create New Account\n2 Existing Account\n3 Exit\nEnter your choice\n";
		cin >> b;

		ofstream out;
		ifstream in;
		switch (b) {
			case 1:
				out.open("account.bin", ios::out | ios::binary);
				create();
				out.write((char *) &a, sizeof(a));
				out.close();
				break;
			case 2:
				in.open("account.bin", ios::in | ios::binary);
				in.read((char *) &a, sizeof(a));
				change();
				in.close();
				break;
			case 3:
				cout << "\nThank you for banking with us :)\n";
				break;
			default:
				cout << "Error";
		}
	}
	getch();
	return 0;
}
