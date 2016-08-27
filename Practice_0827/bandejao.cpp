#include <iostream>
using namespace std;

int main(int argc, char** agrv) {
    int n, k; // k types of untensils and n friends
    cin >> n;
    cin >> k;
    if ((n+1) % k) cout << "no" << endl;
    else cout << "yes" << endl; 
return 0;
}
