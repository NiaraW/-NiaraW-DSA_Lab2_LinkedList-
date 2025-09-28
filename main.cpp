#include <iostream>
using namespace std; 


struct User {
    string username;
    string password;
    string role;      // Authorization role:"admin", "editor", "viewer"
    User* next;

    User(const string& u, const string& p, const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};
bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer");
// only put default value in function declaration not definition
User* findUser(User* head, const string& username);
bool authorize(User* head, const string& username, const string& action);

int main() {

	User * head = nullptr;
	insertUser(head, "Jas", "5478", "editor");
	insertUser(head, "Sally", "6767");
	insertUser(head, "Hen", "8292", "admin");
	bool result = findUser(head, "Sally");
	bool author = authorize(head, "Jas", "delete");
	cout << boolalpha << result << endl << boolalpha << author << endl;


	return 0;

}

bool insertUser(User*& head, const string& username, const string& password, const string& role) {
	  //Insert at end: O(n)
    User * newUser = new User(username, password, role);
    if(head == nullptr) { 
        head = newUser; 
        return true; 
    } 
    User * temp = head;
    while(temp->next!= nullptr) {
        if(username == temp->username ) { 
            return false;
        }
        temp = temp->next;

    }
    if(username == temp->username) {
        return false;
    } 
    else { 
        temp->next = newUser;
        return true;
        }
}

// Returns pointer to the node with matching username; otherwise nullptr.
User* findUser(User* head, const string& username) {
    //Find: O(n)
    // Need to search
    User * temp = head;
    while(temp != nullptr) {
        if(temp->username == username) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
// passwords not necessary because we have roles 

bool authorize(User* head, const string& username, const string& action) {
	User*user = findUser(head, username);
	if(user == nullptr) {
		return false;
	}
	if(user->role == "admin") {
		return true;
	}
	if(action == "view"|| action == "edit"|| action == "create" && user->role == "editor") {
		return true;
	} else {
		return false;
	}
	if(action == "view" && user->role == "viewer") {
		return true;
	} else {
		return false;
	}
	return false;
}
