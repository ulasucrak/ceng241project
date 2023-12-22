#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*void voice_message(string message) {
    string command = "espeak \"" + message + "\"";
    const char* charCommand = command.c_str();
    system(charCommand);

}*/

class User {
protected:
    string username;
    string password;

public:
    virtual void get_username() = 0;
    virtual void get_password() = 0;
    virtual bool login() = 0;
    virtual string getName();
    virtual ~User(){}

    void register_user(vector<User*>& users) {
        get_username();
        get_password();
        users.push_back(this);
        cout << "Registration successful!\n";
    }
};

string User::getName() {
    return username;
}

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
        //voice_message("Enter student username");
        cin >> username;
    }

    void get_password() override {
        cout << "Enter student password: ";
        //voice_message("Enter student password");
        cin >> password;
    }

    bool login() override {
        string inputPassword;

        cout << "Enter student password: ";
        //voice_message("Enter student password");
        cin >> inputPassword;

        return (inputPassword == password);
    }
};

void menu() {
    cout << "1. Register\n2. Login\n3. Exit" << endl;
   //voice_message("Enter 1 for registration, 2 for login, 3 for exit");
}

void user_type_menu() {
    cout << "1. Student Account\n2. Instructor Account" << endl;
    //voice_message("Enter 1 for student account, 2 for instructor account");
}

int main() {
    vector<User*> users;
    int choice, user_type;
    User* currentUser = nullptr;

    do {
        menu();
        cin >> choice;
        string inputUsername;
        if(choice == 1){
            user_type_menu();
            cin >> user_type;
            if (user_type == 1 || user_type == 2)
            {
                currentUser = new Student();
                currentUser->register_user(users);
            }else{
                cout << "Invalid Choice!"<<endl;
            }
        }
        else if(choice == 2)
        {
            cout << "Enter student username: ";
            //voice_message("Enter student username");
            cin >> inputUsername;
            int pos = -1;
            for (int i = 0; i < users.size(); ++i) {
                if (users.at(i)->getName() == inputUsername)
                {
                    pos = i;
                }
            }
            if (pos != -1)
            {
                bool success = users.at(pos)->login();
                if (success){
                    cout << "Successfully logged in"<<endl;
                }else{
                    cout << "Unable to login"<<endl;
                }
            }else{
                cout <<"Student does not exist"<<endl;
            }



        }else if(choice == 3)
        {
            cout << "Exit program"<<endl;
        }else
        {
            cout << "Invalid Choice!"<<endl;
        }



    } while (choice != 3);





    return 0;
}