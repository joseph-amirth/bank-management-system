#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;

class account {
public:
	char name[20], pass[20];
	long long account_no;
	double balance;
} a;

double car(double p) {
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

double house(double p) {
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

void create() {
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	char password1[20], password2[20];
	while (true) {
		cout << "Enter your name ";
		gets(a.name);
		cout << "Enter password ";
		gets(password2);
		cout << "Confirm password ";
		gets(password1);
		if (strcmp(password2, password1) != 0) {
			cout << "\nError. Enter the details again ";
			getch();
		} else {
			strcpy(a.pass, password1);
			break;
		}
	}
	a.account_no = rng() % 10000000000;
	cout << "Your account has been created\nYour Account Number is " << a.account_no;
	cout << "\nEnter the amount to be deposited ";
	cin >> a.balance;
	cout << "The details of your account are ";
	cout << "\nName: " << a.name << "\nPassword: " << a.pass << "\nAccount Number: " << a.account_no << "\nBalance: "
		 << a.balance;
}

void write() {
	ofstream ofile;
	ofile.open("account.dat", ios::out | ios::binary);
	ofile.write((char *) &a, sizeof(a));
	ofile.close();
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

void simple_interest(double p, int r) {
	double t;
	cout << "\nEnter the period of time for which you want to borrow the money (in years) ";
	cin >> t;
	double SI;
	SI = p * r * t / 100;
	cout << "The total amount to be paid at the end of the time period is " << p + SI;
	cout << "The money has been successfully deposited into your account";
	a.balance = a.balance + p;
}

void fd() {
	cout << "\nEnter the amount of money you want to deposit";
	unsigned int d;
	cin >> d;
	if (d > a.balance) {
		cout << "You do not have enough balance in you account\n";
		cout << "Enter a different amount";
		fd();
	} else {
		cout << "The percentage interest is " << house(d);
		cout << "Enter the time for which you want to deposit the money(in years) ";
		int t;
		cin >> t;
		double si;
		si = d * house(d) * t / 100;
		cout << "You will earn Rs. " << d + si << " at the end of your time period\n";
		cout << "The money you have deposited has successfully been deducted from you main balance";
		a.balance -= d;
		getch();
	}
}

void change() {
	char nam[20], pas[20];
	while (true) {
		cout << "Enter Name ";
		gets(nam);
		cout << "Enter Password ";
		gets(pas);
		if (strcmp(nam, a.name) != 0 || strcmp(pas, a.pass) != 0) {
			cout << "The Username or Password is wrong\n";
			cout << "Please retype Username and Password\n";
		} else {
			cout << "You have accessed your account";
			break;
		}
	}
	getch();
	int c;
	g:
	cout << "1 Deposit Money\n2 Withdraw Money\n3 Change Password\n4 Apply for Loan\n5 Check Balance\n6 Log Out\n";
	cout << "Enter your choice ";
	cin >> c;
	switch (c) {
		case 1:
		d1:
			cout << "\n1. Fixed deposit\n2. Savings\nEnter your choice ";
			int l;
			cin >> l;
			switch (l) {
				case 1:
					fd();
					write();
					break;
				case 2:
					cout << "Enter the amount you want to deposit ";
					unsigned int s;
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
			int with;
			while (true) {
				cout << "Enter the amount you want to withdraw ";
				cin >> with;
				if (with > a.balance) {
					cout << "You do not have enough money for transaction in your account";
					cout << "\nPlease enter a different amount";
				} else {
					a.balance -= with;
					cout << "Your new balance is " << a.balance;
					write();
					exit(0);
				}
			}
		case 3:
			char password1[10], password2[10];
			while (true) {
				cout << "Enter the new password ";
				gets(password1);
				cout << "Confirm new password ";
				gets(password2);
				if (strcmp(password1, password2) != 0) {
					cout << "Password did not match, retype new password\n";
				} else {
					strcpy(password1, a.pass);
					cout << "Your password has been changed";
					break;
				}
			}
			write();
			break;
		case 4:
		d2:
			cout << "1.Personal loan\n2.Car Loan\n3.Home Loan\nEnter the type of loan you require";
			int x;
			cin >> x;
			double loan;
			switch (x) {
				case 1:
					cout << "Enter the amount you want to borrow (minimum amount 10,000) ";
					cin >> loan;
					cout << "The rate of interest per annum is " << rate(loan);
					simple_interest(loan, rate(loan));
					cout << "\n Your loan has been sanctioned,the amount has been transferred to your account ";
					getch();
					break;
				case 2:
					cout << "Enter the amount of loan required to purchase your car";
					cin >> loan;
					simple_interest(loan, car(loan));
					cout << "Your loan has been sanctioned,the amount has been transferred to your account";
					cout << "\nYour car will belong to the bank(as collateral) and will remain so till the loan has be paid off completely";
					getch();
					break;
				case 3:
					cout << "Enter the amount of loan required to purchase your house";
					cin >> loan;
					simple_interest(loan, house(loan));
					cout << "Your loan has been sanctioned,the amount has been transferred to your account";
					cout << "\nYour house will belong to the bank(as collateral) and will remain so till the loan has be paid off completely";
					getch();
					break;
				default:
					cout << "Wrong choice.Enter again";
					getch();
					goto d2;
			}
			break;
		case 5:
			cout << "Your Balance is " << a.balance;
			getch();
			break;
		case 6:
			return;
		default:
			cout << "Error!! :(";
	}
	goto g;
}

int main() {
	cout << "____________________________________________________\n";
	cout << "                    Cyber Bank\n";
	cout << "____________________________________________________\n";

	int b = 0;
	while (b != 3) {
		cout << "\n1 Create New Account\n2 Existing Account\n3.Exit\nEnter your choice ";
		cin >> b;

		ofstream ofile, ofile1;
		ifstream ifile;
		switch (b) {
			case 1:
				ofile.open("account.dat", ios::out | ios::binary);
				create();
				ofile.write((char *) &a, sizeof(a));
				ofile.close();
				break;
			case 2:
				ifile.open("account.dat", ios::in | ios::binary);
				cout << "1";
				ifile.read((char *) &a, sizeof(a));
				change();
				ifile.close();
				break;
			case 3:
				cout << "\nThank you for banking with us :)";
				break;
			default:
				cout << "Error";
		}
	}
	getch();
	return 0;
}
