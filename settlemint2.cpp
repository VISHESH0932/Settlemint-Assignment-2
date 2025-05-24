#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<long long,int>> events;
    for(int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        events.emplace_back(a, +1);
        events.emplace_back(b, -1);
    }
    sort(events.begin(), events.end());
    long long occupancy = 0;
    long long switches = 0;
    for(auto &e : events) {
        if(e.second == +1) {
            if(occupancy == 0) switches++;
            occupancy++;
        } else {
            occupancy--;
        }
    }
    cout << switches;
    return 0;
}
