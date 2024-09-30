#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include "fileReader.cpp"
#include "signedOptions.cpp"
#include <termios.h>

using namespace std;

namespace user
{
    string username = "";
    string password ="";
}
namespace crossScripts
{
    bool passChange = false;
    bool check = false;
    int choice = 0;
}

void password_creation()
{
    termios oldt;
    tcgetattr(0, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;

    cout<<"\nPlease enter a password 5 characters long or more: "<<endl;
    tcsetattr(0, TCSANOW, &newt);
    cin>>user::password;
    tcsetattr(0, TCSANOW, &oldt);
    while (user::password.length() < 5)
    {
        cout<<"Please enter a password 5 characters or above: "<<endl;
        tcsetattr(0, TCSANOW, &newt);
        cin>>user::password;
        tcsetattr(0, TCSANOW, &oldt);
    }
    crossScripts::check = new_password(user::username, user::password, crossScripts::check);
    if(crossScripts::check == false)
    {
        password_creation();
    }
    else
    {
        return;
    }
}

void username_creation()
{
    cout<<"\nPlease enter a username 5 characters long or more: "<<endl;
    cin>>user::username;
    while (user::username.length() < 5)
    {
        cout<<"Please enter a username 5 characters or above: "<<endl;
        cin>>user::username;
    }
    crossScripts::check = new_User(user::username, crossScripts::check);
    if(crossScripts::check == false)
    {
        username_creation();
    }
    else
    {
        password_creation();
    }
    return;

}

//* Function to get password for sign in
void signin_password()
{   //* Setup for hiding password input
    string password;
    termios oldt;
    tcgetattr(0, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;

    while(password.length() < 5) //* Program asks user for password until it meets requirements
    {
        cout<<"Please enter a password 5 characters or above: "<<endl;
        tcsetattr(0, TCSANOW, &newt);//* Hides user input
        cin>>password;
        tcsetattr(0, TCSANOW, &oldt);//* Resets to visible input
    }
    crossScripts::check = false; //* Resets check to false
    crossScripts::check = check_password(password, crossScripts::check); //* Starts the function to check if the password matches
    if(crossScripts::check == false)
    {   //* If the password matches doesn't match the user is taken back to
        //* the user choice menu
        return;
    }
    else
    {   //* If the password matches, users are taken to their respective menus
        if(user::username == "admin")
        {   //* If the user is admin the admin_choices function is called
            admin_choices(user::username, password);
        }
        else
        {   //* If the user is not admin the signed_choices function is called
            signed_choices(user::username, password);
        }
    }
}

//* Function to get username for sign in
void signin_username()
{
    string username;
    cout<<"Enter your username: "<<endl;
    cin>>username;
    while(username.length() < 5) //* Program asks user for username until it meets requirements
    {
        cout<<"Please enter a username 5 characters or above: "<<endl;
        cin>>username;
    }
    crossScripts::check = false; //* Resets check to false
    crossScripts::check = check_username(username, crossScripts::check); //* Starts the function to check if the username already exists
    if (crossScripts::check == false)
    {   //* If username already exists or the username is the same as the signed in user
        //* the function is called again
        cout<<"Please try again!"<<endl;
        signin_username();
    }
    else
    {   //* If the username is accepted the signedUser::username is set to the new username
        //* and the signin_password function is called to check the password
        user::username = username;
        signin_password();
    }
}

//* Function to get user choice
int MenuChoice(int choice)
{
    if(choice == 1)
    {   //* Begins the process of creating a new user
        username_creation();
    }
    if(choice == 2)
    {   //* Begins the process of signing in
        signin_username();
    }
    if(choice == 3)
    {   //* Exits the program
        cout<<"Goodbye!"<<endl;
        return 0;
    }
    else
    {   //* If the user enters an invalid choice
        return 0;
    }
    return 0;
}

int main() //* Main function
{
    while(crossScripts::choice != 3) //* While loop to keep the program running
    {   //* Gives the user the options to choose from
        crossScripts::choice = user_Choice(); //* Stores user choice in crossScripts namespace
        MenuChoice(crossScripts::choice); //* Starts the menu function
    }
}