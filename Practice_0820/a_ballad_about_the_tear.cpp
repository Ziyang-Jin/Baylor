#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool check(string s, int i, int x);
int oneof(char c);

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int num_changes;
    cin >> num_changes;
    vector<pair<int, char>> pairs(num_changes);
    for(int i = 0; i < num_changes; i++) {
        cin >> pairs[i].first;
        cin >> pairs[i].second;
    }

    bool find = false;

    if(s.size() < 7) {
        cout << "Goodbye, my love!" << endl;
        return 0;
    }
    for(int i = 0; i < s.size() - 6; i++) {
        if(s[i] == 'd')
            find = check(s, i, 0);
        if(find) {
            cout << "I love you, Desmond!" << endl;
            cout << 0 << endl;
            return 0;
        }
    }

    for(int i = 0; i < num_changes; i++) {
        s[pairs[i].first-1] = pairs[i].second;
        int x = oneof(pairs[i].second);
        if(x != -1) {
            if(x != 0)
                find = check(s, pairs[i].first-1, x);
            else
                find = check(s, pairs[i].first-1, 0) || check(s, pairs[i].first-1, 6);

            if(find) {
                cout << "I love you, Desmond!" << endl;
                cout << i+1 << endl;
                return 0;
            }
        }
    }
    cout << "Goodbye, my love!" << endl;

return 0;
}

bool check(string s, int i, int x) {
    int a = i-x < 0 ? 0 : i-x;
    string cmp;
    if(i-x+6 < s.size())
        cmp = s.substr(a, 7);
    else 
        cmp = s.substr(a);
    return (cmp == "desmond");
}

int oneof(char c) {
    if(c == 'd') return 0;
    if(c == 'e') return 1;
    if(c == 's') return 2;
    if(c == 'm') return 3;
    if(c == 'o') return 4;
    if(c == 'n') return 5;
    return -1;
}
