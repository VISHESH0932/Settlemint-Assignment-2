#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countLightSwitches(int n, const vector<pair<int, int>>& intervals) {
    vector<pair<int, int>> events;

    for (const auto& interval : intervals) {
        events.emplace_back(interval.first, 1);   
        events.emplace_back(interval.second, -1); 
    }

    sort(events.begin(), events.end());

    int inside = 0;
    int switchCount = 0;

    for (const auto& event : events) {
        int time = event.first;
        int delta = event.second;

        if (delta == 1 && inside == 0) {
            switchCount++; 
        }

        inside += delta;
    }

    return switchCount;
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    cout << countLightSwitches(n, intervals) << endl;

    return 0;
}
