#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <list>
#include <sstream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

void print_win(double diff, double r, double k) {
    diff *= 3600.0;
    // printf("The cheater can win by %d seconds with r = %.2fkm and k = %.2fkm.\n", (int)diff, r, k);
    printf("The cheater can win by %d seconds with r = %.2fkm and k = %.2fkm.\n", int(round(diff)), r, k);

}

int main() {
    double t;
    while (cin >> t) {
        int n;
        cin >> n;
        vector<pair<double, double>> speed;
        for (int i = 0; i < n; i++) {
            double running, cycling;
            cin >> running >> cycling;
            speed.push_back({running, cycling});
        }
        bool found = false;
        double best = 0.0;
        double best_r = 0.0;
        double best_k = 0.0;
        for (double r = 0.0; r <= t; r += 0.001) {
            double k = t - r;
            vector<double> time;
            for (size_t i = 0; i < speed.size(); i++) {
                double curr_time = 0;
                curr_time += r / speed[i].first;
                curr_time += k / speed[i].second;
                time.push_back(curr_time);
            }
            double bribe_time = time.back();
            time.pop_back();
            sort(time.begin(), time.end());
            double diff = time[0] - bribe_time;
            if (diff >= best) {
                found = true;
                best = diff;
                best_r = r;
                best_k = k;
            }
        }
        if (found) {
            print_win(best, best_r, best_k);
        }
        if (!found) {
            cout << "The cheater cannot win." << endl;
        }
    }

    return 0;
}
