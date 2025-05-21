#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> first, follow;

void computeFirst(char nonTerminal) {
    if (first.find(nonTerminal) != first.end()) return;

    for (const string& production : productions[nonTerminal]) {
        for (char symbol : production) {
            if (isupper(symbol)) {
                computeFirst(symbol);
                bool hasEpsilon = false;
                for (char ch : first[symbol]) {
                    if (ch == '#') hasEpsilon = true;
                    else first[nonTerminal].insert(ch);
                }
                if (!hasEpsilon) break;
            } else {
                first[nonTerminal].insert(symbol);
                break;
            }
        }
    }
}

void computeFollow(char nonTerminal) {
    if (follow.find(nonTerminal) != follow.end()) return;

    for (auto& rule : productions) {
        char left = rule.first;
        for (const string& production : rule.second) {
            size_t pos = production.find(nonTerminal);
            while (pos != string::npos) {
                if (pos + 1 < production.size()) {
                    char next = production[pos + 1];
                    if (isupper(next)) {
                        computeFirst(next);
                        for (char ch : first[next]) {
                            if (ch != '#') follow[nonTerminal].insert(ch);
                        }
                        if (first[next].count('#')) {
                            computeFollow(left);
                            follow[nonTerminal].insert(follow[left].begin(), follow[left].end());
                        }
                    } else {
                        follow[nonTerminal].insert(next);
                    }
                } else {
                    computeFollow(left);
                    follow[nonTerminal].insert(follow[left].begin(), follow[left].end());
                }
                pos = production.find(nonTerminal, pos + 1);
            }
        }
    }
}

int main() {
    int numRules;
    cout << "Enter the number of production rules: ";
    cin >> numRules;
    cin.ignore();

    cout << "Enter the production rules (e.g., E->TR):" << endl;
    for (int i = 0; i < numRules; ++i) {
        string rule;
        getline(cin, rule);
        if (rule.size() < 4 || rule[1] != '-' || rule[2] != '>') {
            cerr << "Invalid format. Use NonTerminal->Production." << endl;
            return 1;
        }
        char nonTerminal = rule[0];
        string production = rule.substr(3);
        productions[nonTerminal].push_back(production);
    }

    if (!productions.empty()) {
        follow[productions.begin()->first].insert('$');  // Start symbol
    }

    for (auto& rule : productions) {
        computeFirst(rule.first);
        computeFollow(rule.first);
    }

    for (auto& rule : productions) {
        cout << "First(" << rule.first << ") = { ";
        for (char ch : first[rule.first]) {
            cout << ch << " ";
        }
        cout << "}" << endl;

        cout << "Follow(" << rule.first << ") = { ";
        for (char ch : follow[rule.first]) {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
