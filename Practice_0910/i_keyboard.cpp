#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct letter {
    int x;
    int y;
};

struct bundle {
    string s;
    int distance;
};

struct letter giveCoordinate(char c) {
    struct letter l;
    switch(c) {
        case 'q': l = {0,0}; break;
        case 'w': l = {1,0}; break;
        case 'e': l = {2,0}; break;
        case 'r': l = {3,0}; break;
        case 't': l = {4,0}; break;
        case 'y': l = {5,0}; break;
        case 'u': l = {6,0}; break;
        case 'i': l = {7,0}; break;
        case 'o': l = {8,0}; break;
        case 'p': l = {9,0}; break;
        case 'a': l = {0,1}; break;
        case 's': l = {1,1}; break;
        case 'd': l = {2,1}; break;
        case 'f': l = {3,1}; break;
        case 'g': l = {4,1}; break;
        case 'h': l = {5,1}; break;
        case 'j': l = {6,1}; break;
        case 'k': l = {7,1}; break;
        case 'l': l = {8,1}; break;
        case 'z': l = {0,2}; break;
        case 'x': l = {1,2}; break;
        case 'c': l = {2,2}; break;
        case 'v': l = {3,2}; break;
        case 'b': l = {4,2}; break;
        case 'n': l = {5,2}; break;
        case 'm': l = {6,2}; break;
        default:  l = {-1,-1};
    }
    return l;
}

bool myfunction(struct bundle a, struct bundle b) {
    if(a.distance < b.distance) return true;
    if(a.distance > b.distance) return false;
    if(a.distance == b.distance) {
        return a.s < b.s;
    }
    return true;
}

int computeDis(struct letter a, struct letter b) {
    int xx = a.x - b.x;
    if(xx < 0) xx = -xx;
    int yy = a.y - b.y;
    if(yy < 0) yy = -yy;
    //cout << "distance between (" << a.x << ", " << a.y << ") and (" << b.x << ", " << b.y << ") is" << xx+yy << endl;
    return xx + yy;
}

void finalOutput(vector<struct bundle> entries) {
    for(int i = 0; i < entries.size(); i++) {
        cout << entries[i].s << " " << entries[i].distance << endl;
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n_tests;
    cin >> n_tests;
    for(int i = 0; i < n_tests; i++) {
        string origin;
        int n_entries;
        cin >> origin;
        cin >> n_entries;
        struct letter coor_origin[origin.size()];
        for(int ii = 0; ii < origin.size(); ii++) {
            coor_origin[ii] = giveCoordinate(origin[ii]);
        }
        vector<struct bundle> entries(n_entries);
        for(int ii = 0; ii < n_entries; ii++) {
            cin >> entries[ii].s;
            entries[ii].distance = 0;
            //cout << "computing Distance" << endl;
            for(int j = 0; j < origin.size(); j++) {
                struct letter l = giveCoordinate(entries[ii].s[j]);
                entries[ii].distance += computeDis(coor_origin[j],l);
                //cout << entries[ii].distance << endl;
            }
        }
        sort(entries.begin(), entries.end(), myfunction);
        finalOutput(entries);
    }
return 0;
}
