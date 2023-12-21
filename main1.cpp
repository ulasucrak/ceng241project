#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void voice_message(string message) {
    string command = "espeak \"" + message + "\"";
    const char* charCommand = command.c_str();
    system(charCommand);
    Sleep(1000);
}

class User {
protected:
    string username;
    string password;

public:
    virtual void get_username() = 0;
    virtual void get_password() = 0;
    virtual bool login() = 0;

    void register_user(vector<User*>& users) {
        get_username();
        get_password();
        users.push_back(this);
        cout << "Registration successful!\n";
    }
};

class Instructor : public User {
public:
    void get_username() override {
        cout << "Enter instructor username: " << endl;
        cin >> username;
        
    }

    void get_password() override {
        cout << "Enter instructor password: " << endl;
        cin >> password;
    }

    bool login() override {
        string inputUsername, inputPassword;
        cout << "Enter instructor username: ";
        cin >> inputUsername;
        cout << "Enter instructor password: ";
        cin >> inputPassword;

        return (inputUsername == username && inputPassword == password);
    }
};

class Student : public User {
public:
    void get_username() override {
        cout << "Enter student username: ";
        voice_message("Enter student username");
        cin >> username;
    }

    void get_password() override {
        cout << "Enter student password: ";
        voice_message("Enter student password");
        cin >> password;
    }

    bool login() override {
        string inputUsername, inputPassword;
        cout << "Enter student username: ";
        voice_message("Enter student username");
        cin >> inputUsername;
        cout << "Enter student password: ";
        voice_message("Enter student password");
        cin >> inputPassword;

        return (inputUsername == username && inputPassword == password);
    }
};

void menu() {
    cout << "1. Register\n2. Login\n3. Exit" << endl;
    voice_message("Enter 1 for registration, 2 for login, 3 for exit");
}

void user_type_menu() {
    cout << "1. Student Account\n2. Instructor Account" << endl;
    voice_message("Enter 1 for student account, 2 for instructor account");
}

int main() {
    vector<User*> users;
    int choice, user_type;
    User* currentUser = nullptr;

    do {
        menu();
        cin >> choice;

        switch (choice) {
        case 1:
            user_type_menu();
            cin >> user_type;

            switch (user_type) {
            case 1:
                currentUser = new Student();
                break;
            case 2:
                currentUser = new Instructor();
                break;
            default:
                cout << "Invalid value. Try again." << endl;
                voice_message("Invalid value. Try again.");
                continue;
            }

            currentUser->register_user(users);
            break;

        case 2:
        switch (user_type) {
        case 1:
            currentUser = new Student();
            break;
        case 2:
            currentUser = new Instructor();
            break;
        default:
            cout << "Invalid value. Try again." << endl;
            voice_message("Invalid value. Try again.");
            continue;
        }

        if (currentUser->login()) {
            cout << "Login successful!" << endl;
            voice_message("Login successful");
        } else {
            cout << "Login failed. Invalid username or password." << endl;
            voice_message("Login failed. Invalid username or password");
            delete currentUser;
            currentUser = nullptr;
        }
    break;


        case 3:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid value. Try again." << endl;
            voice_message("Invalid value. Try again.");
        }

    } while (choice != 3);

    if (currentUser != nullptr) {
        delete currentUser;
    }


    for (User* user : users) {
        delete user;
    }

    return 0;
}
