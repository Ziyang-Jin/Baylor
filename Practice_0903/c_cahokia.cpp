#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int H, W;
    cin >> H;
    cin >> W;
    int a[H], b[H], c[H];
    int min;
    for(int i = 0; i < H; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < H; i++) {
        cin >> b[i];
        c[i] = W - (a[i] + b[i]);
    }
    min = c[0];
    for(int i = 1; i < H; i++) {
        if(c[i] < min)
            min = c[i];
    }
    cout << (double) min / 2 << endl;
return 0;
}
