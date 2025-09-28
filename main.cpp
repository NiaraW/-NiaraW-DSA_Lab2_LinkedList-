#include <iostream>
using namespace std; 
#include<vector>


struct User {
    string username;
    string password;
    vector<string> permissions;   // Authorization role:"admin", "editor", "viewer"
    User* next;

    User(const string& u, const string& p, const vector<string>& r = {"view"}) {
        username = u;
        password = p;
        permissions = r;
        next = nullptr;
    }
};
bool insertUser(User*& head, const string& username, const string& password, const vector<string>& r = {"view"});
// only put default value in function declaration not definition
User* findUser(User* head, const string& username);
bool authorize(User* head, const string& username, const string& action);

int main() {

	User * head = nullptr;
	insertUser(head, "Jas", "5478", {"edit"});
	insertUser(head, "Sally", "6767");
	insertUser(head, "Hen","8292", {"create", "delete"});
	bool result = findUser(head, "Sam");
	bool author = authorize(head, "Jas", "delete");
	bool another = authorize(head, "Hen", "create");
	cout << boolalpha << result << endl << boolalpha << author << endl << another << endl;



	return 0;

}

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& permissions) {
	  //Insert at end: O(n)
    User * newUser = new User(username, password, permissions);
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
	if(user->permissions.empty()) {
		return false;
	}
	for(int i = 0; i < user->permissions.size(); i++ ) {
		if(action == user->permissions[i]) {
			return true;
		}
	}
	return false;
}

