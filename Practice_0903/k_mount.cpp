#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int n;
    cin >> n;
    int count = 1;
    double p_diff = 1;
    while(p_diff >= 0.5) {
        p_diff = p_diff * (n-count++) / n;
    }
    cout << count << endl;
return 0;
}
