#include <iostream>
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
	bool MarkForDelete = false;
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
bool FindClientByAccountNumber(string AccountNumber, sClient&Client)
{
	vector <sClient> vClients =
		LoadCleintsDataFromFile(ClientsFileName);
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
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client)
{
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
void AddNewClient(sClient Client)
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
void AddClients(sClient Client)
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
void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber,
				vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			//Refresh Clients
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
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
	cout << "Choose what do u want to do ? [1 to 6] ?  ";
	cin >> ChooseFromMenu;
	return ChooseFromMenu;
}
void GoBackToMainMenu()
{
	cout << "Press any key to back to main menu ...";
	system("pause>0");
	ChooseFromMenu();
}
void ResultOfMenuCoice( vector <sClient> &vClients, sClient Client)
{
	if (ChooseFromMenu() == enMenu::ShowClientListt)
	{
		system("cls");
		PrintAllClientsData(vClients);
		GoBackToMainMenu();
		ResultOfMenuCoice( vClients, Client);
	}
	else if (ChooseFromMenu() == enMenu::AddNewClientt)
	{
		system("cls");
		AddClients(Client);
		GoBackToMainMenu();
		ResultOfMenuCoice(vClients, Client);

	}
	else if (ChooseFromMenu() == enMenu::DeleteClientt)
	{
		system("cls");
		vector <sClient> vClients =LoadCleintsDataFromFile(ClientsFileName);
		string AccountNumber = ReadClientAccountNumber();
		DeleteClientByAccountNumber(AccountNumber, vClients);
		GoBackToMainMenu();
		ResultOfMenuCoice(vClients, Client);

	}
	else if (ChooseFromMenu() == enMenu::UpdateClientInfoo)
	{
		system("cls");
		vector <sClient> vClients =
		LoadCleintsDataFromFile(ClientsFileName);
		string AccountNumber = ReadClientAccountNumber();
		UpdateClientByAccountNumber(AccountNumber, vClients);
		GoBackToMainMenu();
		ResultOfMenuCoice(vClients, Client);

	}
	else if (ChooseFromMenu() == enMenu::FindClientt)
	{
		system("cls");
		sClient Client;
		string AccountNumber = ReadClientAccountNumber();
		if (FindClientByAccountNumber(AccountNumber, Client))
		{
			PrintClientCard(Client);
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber <<
				") is Not Found!";
		}
		GoBackToMainMenu();
		ResultOfMenuCoice(vClients, Client);

	}
	else if (ChooseFromMenu() == enMenu::Exitt)
	{
		system("cls");
		cout << "==================\n Program End :-) \n==================\n";
		system("pause>0");
	}
}


int main()
{
	
	sClient Client;
	vector <sClient> vClients =LoadCleintsDataFromFile(ClientsFileName);
	ResultOfMenuCoice(vClients,Client);
	system("pause>0");
	
	return 0;
}