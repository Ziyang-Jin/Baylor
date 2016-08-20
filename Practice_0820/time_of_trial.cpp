#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int num_spell;
    cin >> num_spell;
    int irdis[num_spell];
    int deimos[num_spell];
    for(int i = 0; i < num_spell; i++)
        cin >> irdis[i];
    for(int i = 0; i < num_spell; i++)
        cin >> deimos[i];
    vector<pair<int,int>> v_pairs(num_spell);
    for(int i = 0; i < num_spell; i++) {
        v_pairs[i].first = irdis[i];
        v_pairs[i].second = deimos[i];
    }
    sort(v_pairs.begin(), v_pairs.begin() + num_spell);
    /*
    for(int i = 0; i < num_spell; i++) {
        cout << "(" << v_pairs[i].first << ", " << v_pairs[i].second << ") ";
    }
    cout << endl;
    */
    int sum = 0;
    for(int i = 0; i < num_spell; i++) {
        sum += v_pairs[i].second;
        if(sum >= v_pairs[i].first) {
            cout << "Redemption" << endl;
            return 0;
        }
    }
    cout << "Dire victory" << endl;
return 0;
}
