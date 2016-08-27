#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    double p = 0;
    cin >> n;
    cin >> k;
    int x1, x2;
    cin >> x1;
    for(int i = 1; i < n; i++) {
        cin >> x2;
        if(x2 != x1) {
            x1 = x2;
            p += (double)(k-1) / (double)k;
        }
    }
    printf("%.9lf\n", p);
return 0;
}
