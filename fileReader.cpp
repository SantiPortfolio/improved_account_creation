#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace accountline
{
    int lines = 0;
}

int HashPassword(string const &Combine) { 
	unsigned int hash = 0;

	const unsigned int VALUE = Combine.length();
	for (auto Letter : Combine)
	{
		srand(VALUE*Letter);
		hash += 33 + rand() % 92;
	}
	return hash;
}

//* Fuction to split username and password in csv file
string split_user(string line)
{
    string user = line.substr(0, line.find(","));
    user.erase(remove(user.begin(), user.end(), '"'), user.end());
    return user;
}

string split_pass(string line) 
{
    string password = line.substr(line.find(",")+1);
    password.erase(remove(password.begin(), password.end(), '"'), password.end());
    return password;
}

bool new_User(string username, bool check)
{
    check = true;
    string used_usernames;
    cout<<"Checking username..."<<endl;
    fstream usernamesText("accounts.csv", ios::app);
    ifstream usernames_check("accounts.csv");
    while(getline(usernames_check, used_usernames))
    {
        string user = split_user(used_usernames);
        if(user == username)
        {
            cout<<"Username already exists!"<<endl;
            check = false;
            break;
        }
    }
    if(check == true)
    {
        cout<<"Username is accepted!"<<endl;
    }
    usernamesText.close();
    usernames_check.close();
    return check;
}

bool new_password(string username, string password, bool check)
{
    check = true;
    string used_passwords;
    cout<<"Checking password..."<<endl;
    fstream passwordsText("accounts.csv", ios::app);
    ifstream passwords_check("accounts.csv");
    unsigned int HashPass = HashPassword(password);
    while(getline(passwords_check, used_passwords))
    {
        string pass = split_pass(used_passwords);
        if(HashPassword(pass) == HashPass)
        {
            cout<<"Password already exists!\nPlease use a different password!"<<endl;
            check = false;
            break;
        }
    }
    if(check == true)
    {
        cout<<"Password is accepted!"<<endl;
        passwordsText<<'"'<<username<<'"'<<','<<'"'<<HashPass<<'"'<<endl;
    }
    passwordsText.close();
    passwords_check.close();
    return check;
}

bool check_username(string username, bool check)
{
    string used_usernames;
    fstream usernames_check("accounts.csv", ios::app);
    ifstream read("accounts.csv");
    while(getline(read, used_usernames))
    {
        string user = split_user(used_usernames);
        accountline::lines +=1;
        if(user == username)
        {
            cout<<"Username found!"<<endl;
            check = true;
            break;
        }
    }
    if(check == false)
    {
        cout<<"Username does not exist!"<<endl;
        accountline::lines = 0;
    }
    usernames_check.close();
    read.close();
    return check;
}

bool check_password(string password, bool check)
{

    unsigned int HashPass = HashPassword(password);
    string pass;
    string used_passwords;
    ifstream passwords_check("accounts.csv");

    for(int i=0; i<accountline::lines; i++)
    {
        getline(passwords_check, used_passwords);
        pass = split_pass(used_passwords);
    }
    if(stoi(pass) == HashPass)
    {
        cout<<"Password accepted!"<<endl;
        check = true;
    }
    if(check == false)
    {
        cout<<"Incorrect password!"<<endl;
    }
    passwords_check.close();
    accountline::lines = 0; //* Reset the lines variable
    return check;
}

void password_Change(string username)
{
    string user;
    int lines = 0;
    string used_names;
    ifstream read("accounts.csv");
    while(getline(read, used_names))
    {
        user = split_user(used_names);
        if(user==username)
        {
            break;
        }
        else lines++;
    }
    read.close();
    int integer = 0;
    string temp;
    read.open("accounts.csv");
    while(getline(read,temp))
    {
        integer++;
    }
    read.close();
    ifstream password_FileRead;
    password_FileRead.open("accounts.csv");
    string passwordtxt_Contents[50];
    if(password_FileRead.is_open())
    {
        for (int i=0; i<=integer;i++)
        {
            password_FileRead>>passwordtxt_Contents[i];
        }
    }
    integer = integer + 1;
    password_FileRead.close();
    remove("accounts.csv");
    fstream password_FileWrite("accounts.csv", ios::app);
    for(int i = 0;i<lines;i++)
    {
        password_FileWrite<<passwordtxt_Contents[i]<< endl;
    }
    for(int i=0;i<=integer;i++)
    {
        if(i<lines)
        {

        }
        else password_FileWrite<<passwordtxt_Contents[i+1]<<endl;
    }
    password_FileWrite.close();
    ifstream in("accounts.csv");
    string line, text;
    while (getline(in, line))
        if (!line.empty() || !line.find_first_not_of(' ') == std::string::npos)
            text += line + "\n";
    in.close();
    remove("accounts.csv");
    ofstream out("accounts.csv");
    out << text;
    return;
}

//* Function to replace the username in accounts.csv
void replace_username(string username)
{
    string user, used_names, pass;
    int lines = 0;
    ifstream read("accounts.csv"); //* Opens accounts.csv as read only.
    while(getline(read, used_names)) //* Loops through accounts.csv
    {   //* Splits the username and password into seperate strings
        user = split_user(used_names);
        pass = split_pass(used_names);
        if(user==username) //* If the username matches the given username the loop ends
        {
            break;
        }
        else lines++; //* Increases for each line the loop goes through
    }
    read.close();
    int integer = 0;
    string temp;
    read.open("accounts.csv"); //* Reopens accounts.csv as read only.
    while(getline(read,temp))
    {   //* Reads through all the lines on accounts.csv and increases integer
        integer++;
    }
    read.close(); //* closes read only
    ifstream usernames_FileRead;
    usernames_FileRead.open("accounts.csv"); //* Opens accounts.csv as read only.
    string usernamestxt_Contents[50];
    if(usernames_FileRead.is_open()) //* If accounts.csv is open
    {   
        if(integer > 1)
        {
            for (int i=0; i<=integer;i++) //* For each line in accounts.csv the users are stored in an array
            {
                usernames_FileRead>>usernamestxt_Contents[i];
            }
        }
    }
    usernames_FileRead.close(); //* Closes read only
    remove("accounts.csv");
    ofstream usernames_FileWrite("accounts.csv", ios::app); //* Deletes and creates a new accounts.csv
    for(int i = 0;i<lines;i++) //* Loops through array and writes users into new accounts.csv
    {
        usernames_FileWrite<<usernamestxt_Contents[i]<< endl;
    }
    usernames_FileWrite<<'"'<<username<<'"'<<','<<'"'<<pass<<'"'<<endl; //* Writes the new username and password into accounts.csv
    for(int i=0;i<=integer;i++) //! Honestly no clue have to check if it's needed
    {
        if(i<lines)
        {

        }
        else usernames_FileWrite<<usernamestxt_Contents[i+1]<<endl;
    }
    usernames_FileWrite.close(); //* Closes accounts.csv
    ifstream in("accounts.csv"); //* Opens accounts.csv as read only.
    string line, text;
    //* Checks if accounts.csv has empty lines and removes them
    //* via creating a new file and only copying the lines that aren't empty
    while (getline(in, line))
        if (!line.empty() || !line.find_first_not_of(' ') == std::string::npos)
            text += line + "\n";
    in.close();
    remove("accounts.csv");
    ofstream out("accounts.csv");
    out << text;
    return;
}

//* Functions that gets called at the start of the program
//* returns the user choice
int user_Choice()
{
    int choice = 0;
    cout<<"Would you like to create an account, sign into an account, or exit? (1/2/3): "<<endl;
    cin>>choice;
    return choice;
}

//* Admin function to show the usersnames and passwords in accounts.csv
void display_users()
{
    ifstream read("accounts.csv");
    string users;
    while(getline(read, users))
    {
        cout<<users<<"\n";
    }
}