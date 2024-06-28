#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

class User {
private:
    string username;
    string password;
    bool hasVoted;

public:
    User() : hasVoted(false) {}

    User(const string& username, const string& password)
        : username(username), password(password), hasVoted(false) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    bool getHasVoted() const {
        return hasVoted;
    }

    void setHasVoted(bool hasVoted) {
        this->hasVoted = hasVoted;
    }
};

class VotingSystem {
private:
    unordered_map<string, User> users;
    unordered_map<string, int> candidates;

public:
    VotingSystem() {
        candidates["1. BJP"] = 0;
        candidates["2. Indian National Congress"] = 0;
        candidates["3. Aam Aadmi Party (AAP)"] = 0;
    }

    void registerUser(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            users[username] = User(username, password);
            cout << "User registered successfully." << endl;
        } else {
            cout << "Username already exists." << endl;
        }
    }

    User* loginUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.getPassword() == password) {
            cout << "Login successful." << endl;
            return &it->second;
        } else {
            cout << "Invalid username or password." << endl;
            return nullptr;
        }
    }

    void displayCandidates() const {
        cout << "Available Candidates:" << endl;
        for (const auto& candidate : candidates) {
            cout << candidate.first << endl;
        }
    }

    void vote(User* user, int candidateNumber) {
        string candidateKey;
        for (const auto& candidate : candidates) {
            if (candidate.first[0] - '0' == candidateNumber) {
                candidateKey = candidate.first;
                break;
            }
        }
        if (user->getHasVoted()) {
            cout << "You have already voted." << endl;
        } else if (!candidateKey.empty()) {
            candidates[candidateKey]++;
            user->setHasVoted(true);
            cout << "Vote cast successfully." << endl;
        } else {
            cout << "Invalid candidate number." << endl;
        }
    }

    void displayResults() const {
        cout << "Voting Results:" << endl;
        for (const auto& entry : candidates) {
            cout << entry.first << ": " << entry.second << " votes" << endl;
        }
    }
};

int main() {
    VotingSystem system;
    string username, password;
    int choice;

    while (true) {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Vote" << endl;
        cout << "4. Display Results" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline

        switch (choice) {
            case 1:
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                system.registerUser(username, password);
                break;
            case 2:
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                system.loginUser(username, password);
                break;
            case 3:
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                if (User* user = system.loginUser(username, password)) {
                    system.displayCandidates();
                    cout << "Enter candidate number to vote for: ";
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline
                    system.vote(user, choice);
                }
                break;
            case 4:
                system.displayResults();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
