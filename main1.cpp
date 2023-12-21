#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class User{
    protected:
        string username;
        string password;
    public:
        virtual void get_username() = 0;
        virtual void get_password() = 0;
};

class Instructor : public User{
    public:
        void get_username(){
            cout << "Enter username: " << endl;
            cin >> username;                
            cout << "Enter password: " << endl;
            cin >> password;
        }
};

int main(){
    string phrase="hello world";
    string command = "espeak \""+phrase+"\"";
    const char* charCommand =command.c_str();
    system(charCommand);
    cout<<"hello world";
    return 0;
}