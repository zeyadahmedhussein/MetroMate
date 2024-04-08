#include "MyForm.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;




#define NumUser 100
using namespace System;
using namespace MetroMate;
using namespace System::Windows::Forms;
using namespace std;
struct account {
	string username;
	string password;
	string email;
}Input;
struct subscription {};
struct user {
	account UserAccount;
	subscription SubscriptionType;
	int id;
	float balance;
};
;
bool signup(user users[]);
bool findEmail(string email, user users[]);
bool findID(int id, user users[]);
void Change() {

}
int main()
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MetroMate::MyForm form;
	Application::Run(% form);
	user users[NumUser];
	user temp;
	
	temp.UserAccount.email = Input.email;
	
	if (findEmail(temp.UserAccount.email, users)) {
		cout << "This email already exists " << endl;
		return false;
	}

	if (temp.UserAccount.email.find("@user.metro") == string::npos)
	{
		cout << "invaled mail format" << endl;
		return false;
	}

	cout << "enter your balance " << endl;
	cin >> temp.balance;
	if (temp.balance < 50) {
		cout << "minimum balance is 50" << endl;
		return false;

	}

	cout << "enter your ID" << endl;
	cin >> temp.id;
	if (findID(temp.id, users)) {
		cout << "id in use" << endl;
		return false;
	}


	return 0;
}
void processText(string  &text) {
	Input.email = text;
};
bool findEmail(string email, user users[]) {
	for (int i = 0; i < NumUser; i++) {
		if (email == users[i].UserAccount.email)
			return true;
	}
	return false;

}
bool findID(int id, user users[]) {
	for (int i = 0; i < NumUser; i++) {
		if (id == users[i].id)
			return true;
	}
	return false;
}


