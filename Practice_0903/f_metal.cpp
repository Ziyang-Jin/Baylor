#include <iostream>

using namespace std;
int solve_second(int people, int index);
int solve(int people, int index) {
    if(index % 2) { // index is odd
        return index / 2 + 1;
    } else {
        if(people % 2) // number of people is odd
            return people/2 + 1 + solve_second(people/2, index/2);
        else
            return people/2 + solve(people/2, index/2);    
    }
}

int solve_second(int people, int index) {
    if(people == 1)
        return 1;
    if(!(index % 2)) { // index is even
        return index / 2;
    } else { // index is odd
        if(people % 2) // number of people is odd
            return people/2 + solve(people/2+1, index/2+1);
        else 
            return people/2 + solve_second(people/2, index/2+1);
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int people, index;
        cin >> people;
        cin >> index;
        cout << solve(people, index) << endl;
    }
return 0;
}
