﻿#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients Data.txt";
enum enMenu{ShowClientListt=1,AddNewClientt=2,DeleteClientt=3,UpdateClientInfoo=4,FindClientt=5,Exitt=6};
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator ="#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumber( sClient&Client)
{
	string AccountNumber = ReadClientAccountNumber();
	vector <sClient> vClients =LoadCleintsDataFromFile(ClientsFileName);
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator ="#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewClient(sClient& Client)
{	
	
	if (FindClientByAccountNumber(Client)==false)
	{
		sClient Client;
		Client = ReadNewClient();
		AddDataLineToFile(ClientsFileName,
		ConvertRecordToLine(Client));
	}
	else
	{
		cout << "Client already Exist , Enter another account number? \n";
		AddNewClient(Client);
	}
}
void AddClients(sClient& Client)
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient( Client);
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
		cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void PrintMainMenu()
{
	system("cls");
	cout << "==============================================\n";
	cout << "\t\t Main Menu Screen\n";
	cout << "==============================================\n";
	cout << setw(10) <<left << "\t[1] Show Client List. \n";
	cout << setw(10) <<left << "\t[2] Add New Client.\n";
	cout << setw(10) <<left << "\t[3] Delete Client. \n";
	cout << setw(10) <<left << "\t[4] Update Client Info. \n";
	cout << setw(10) <<left << "\t[5] Find Client. \n";
	cout << setw(10) <<left << "\t[6] Exit. \n";
	


}
int ChooseFromMenu()
{
	PrintMainMenu();
	int ChooseFromMenu = 0;
	cout << "Choose what do u want to do ? [1 => 6] :) ?  ";
	cin >> ChooseFromMenu;
	return ChooseFromMenu;
}
void GoBackToMainMenu()
{
	cout << "Press any key to back to main menu ...";
	system("pause>0");
	ChooseFromMenu();
}
void ResultOfMenuCoice(int ChooseFromMenu, vector <sClient> &vClients, sClient& Client)
{
	if (ChooseFromMenu == enMenu::ShowClientListt)
	{
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenu();
	}
	else if (ChooseFromMenu == enMenu::AddNewClientt)
	{
		system("cls");
		AddClients(Client);
		GoBackToMainMenu();
	}
	else if (ChooseFromMenu == enMenu::DeleteClientt)
	{
		system("cls");

		GoBackToMainMenu();
	}
	else if (ChooseFromMenu == enMenu::UpdateClientInfoo)
	{
		system("cls");

		GoBackToMainMenu();
	}
	else if (ChooseFromMenu == enMenu::FindClientt)
	{
		system("cls");

		GoBackToMainMenu();
	}
	else if (ChooseFromMenu == enMenu::Exitt)
	{
		system("cls");

		GoBackToMainMenu();
	}
}

int main()
{
	
	sClient Client;
	int ChooseFromMeny = ChooseFromMenu();
	vector <sClient> vClients =LoadCleintsDataFromFile(ClientsFileName);
	ResultOfMenuCoice(ChooseFromMeny,vClients,Client);
	system("pause>0");
	return 0;
}