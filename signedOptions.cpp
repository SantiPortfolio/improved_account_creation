#include <iostream>
#include <string>
#include <termios.h>

using namespace std;

namespace signedUser
{
    //* Stores the username and password of the signed in user
    //* Helps keep the right username and password for all functions
    //* without having to pass them through each function
    string username = "";
    string password = "";
}

void wipe_users()
{
    while(true) //* Ensures admin is sure they want to wipe all users
    {
        cout<<"Are you sure you want to wipe all users? (y/n): ";
        string choice;
        cin>>choice;
        if(choice == "y")
        {
            break;
        }
        else if(choice == "n")
        {
            return;
        }
        else
        {
            cout<<"Please enter a valid choice!"<<endl;
        }
    }
    //* delete accounts.csv file
    remove("accounts.csv");

    //* create a new one
    ofstream new_accounts("accounts.csv");

    //* add the admin account back
    new_accounts<<'"'<<"admin"<<'"'<<','<<'"'<<"455"<<'"'<<endl;
}

//* Function to createa new username
bool new_Users(string username, bool check)
{
    string user_usernames;
    cout<<"Checking username..."<<endl;
    ifstream usernames_check("accounts.csv"); //* Opens accounts.csv as read only.
    while(getline(usernames_check, user_usernames)) //* Loops through accounts.csv 
    {
        if(user_usernames == username)
        {   //* If the given username already exists the loop ends and check bool is set to false
            //* to indicate it failed the check
            cout<<"Username already exists!"<<endl;
            check = false;
            break;
        }
        else
        {   //* If the username doesn't exist the loop ends and check bool is set to true
            cout<<"Username is accepted!"<<endl;
            check = true;
            break;
        }
    }
    usernames_check.close(); //* Closes accounts.csv
    return check;
}

//* Function to change username
void userName_creation()
{
    string username;
    bool check = false;
    bool signed_in = true;
    while (username.length() < 5) //* Program asks user for username until it meets requirements
    {
        cout<<"Please enter a username 5 characters long or more: ";
        cin>>username;
    }
    check = new_Users(username, check); //* Starts the function to check if the username already exists
    if(check == false || username == signedUser::username)
    {   //* If username already exists or the username is the same as the signed in user
        //* the function is called again
        cout<<"Please try again!"<<endl;
        userName_creation();
    }
    else
    {   //* If the username is accepted the signedUser::username is set to the new username
        //* and the replace_username function is called to change the username in accounts.csv
        signedUser::username = username;
        replace_username(signedUser::username);
        cout<<"Username changed!"<<endl;
    }
    return;
}

//* Function to change password
void Password_creation()
{   //* Setup for hiding password input
    termios oldt;
    tcgetattr(0, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;

    string password;
    bool check = false;
    while (password.length() < 5) //*  Program asks user for password until it meets requirements
    {
        cout<<"Please enter a password 5 characters long or more: ";
        tcsetattr(0, TCSANOW, &newt); //*  Hides user input
        cin>>password;
        tcsetattr(0, TCSANOW, &oldt); //* Resets to visible input
    }
    check = new_password(signedUser::username, password, check); //* Starts the function to check if the password already exists
    if(check == false || password == signedUser::password)
    {   //* If the password already exists or the password is the same as the signed in user
        //* the function is called again
        cout<<"Please try again!"<<endl;
        Password_creation();
    }
    else
    {   //* If the password is accepted the signedUser::password is set to the new password
        //* and the password_Change function is called to change the password in accounts.csv
        signedUser::password = password;
        password_Change(signedUser::username);
        cout<<"Password changed!"<<endl;
    }
    return;
}

//* Function to sign out
void signout()
{
    cout<<"You have been signed out!"<<endl;
    signedUser::username = ""; //* Resets the signedUser::username
    return;
}

//* Fuction to give users options on their account
void signed_choices(string username, string password)
{   //* Takes the username and password and saves it to the signedUser namespace
    signedUser::username = username;
    signedUser::password = password;
    int choice;
    while(choice != 4)
    {   //* Selection for users
        cout<<"Welcome to your account, "<<signedUser::username<<".\n";
        cout<<"What would you like to do?\n";
        cout<<"1. Change password\n";
        cout<<"2. Change username (coming soon)\n";
        cout<<"3. Sign out\n";
        cout<<"4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
        {
            cout<<"Please enter a valid choice: ";
            cin>>choice;
        }
        if (choice == 1)
        {   //* Allows the user to change password
            bool passChange = true;
            Password_creation();
        }
        else if (choice == 2)
        {
            cout<<"This feature is coming soon!"<<endl;
            //*  bool userChange = true;
            //*  userName_creation();
        }
        else if (choice == 3)
        {   //* Signs out the user
            signout();
            return;
        }
        else if (choice == 4)
        {   //* Exits the program
            exit(0);
        }
    }
    return;
}

void admin_choices(string username, string password)
{
    //* Takes the username and password and saves it to the signedUser namespace
    signedUser::username = username;
    signedUser::password = password;
    int choice;
    while(choice != 4)
    { 
        //* Selection for admin
        cout<<"Welcome to your account, "<<signedUser::username<<".\n";
        cout<<"What would you like to do?\n";
        cout<<"1. Change password\n";
        cout<<"2. Change username (coming soon)\n";
        cout<<"3. Sign out\n";
        cout<<"4. Wipe users\n";
        cout<<"5. Display users\n";
        cout<<"6. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6)
        {
            cout<<"Please enter a valid choice: ";
            cin>>choice;
        }
        if (choice == 1)
        {
            //* Allows the user to change password
            bool passChange = true;
            Password_creation();
        }
        else if (choice == 2)
        {
            cout<<"This feature is coming soon!"<<endl;
            //*  bool userChange = true;
            //*  userName_creation();
        }
        else if (choice == 3)
        {
            //* Signs out the user
            signout();
            return;
        }
        else if (choice == 4)
        {
            //* Wipes the users
            wipe_users();
            cout<<"Users wiped!"<<endl;
        }
        else if (choice == 5)
        {
            //* Displays usernames and changed passwords
            display_users();
        }
        else if (choice == 6)
        {
            //* Exits the program
            exit(0);
        }
    }
    return;
}