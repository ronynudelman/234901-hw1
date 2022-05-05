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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;


void get_input(int& N, vector<int>& fees) {
    cin >> N;
    fees.push_back(0);
    for (int i = 0; i < N; i++) {
        int next;
        cin >> next;
        fees.push_back(next);
    }
}


class QueueNode {
public:
    int cost;
    int loc;
    int jump;
    QueueNode(int cost, int loc, int jump) : cost(cost), loc(loc), jump(jump) {}
    bool operator>(const QueueNode& other) const { return cost > other.cost; }
};


class MapNode {
public:
    int loc;
    int jump;
    MapNode(int loc, int jump) : loc(loc), jump(jump) {}
    bool operator<(const MapNode& other) const {
        if (loc == other.loc) {
            return jump < other.jump;
        }
        return loc < other.loc;
    }
};


// check if new minimal cost was found for some {loc, jump}
void check_jump(vector<int>& fees, map<MapNode, int>& min_cost_map,
                priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>>& min_cost_queue,
                int loc, int jump, int next_loc, int next_jump) {
    MapNode curr_state(loc, jump);
    MapNode next_state(next_loc, next_jump);
    int next_loc_fee = fees[next_loc];
    bool to_update = false;
    if (min_cost_map.find(next_state) != min_cost_map.end()) {
        if (min_cost_map[curr_state] + next_loc_fee < min_cost_map[next_state]) {
            to_update = true;
        }
    }
    else {
        to_update = true;
    }
    if (to_update) {
        min_cost_map[next_state] = min_cost_map[curr_state] + next_loc_fee;
        min_cost_queue.push(QueueNode(min_cost_map[next_state], next_loc, next_jump));
    }
}


// find the minimal cost by simulating the game and always checking the minimal cost of some {loc, jump}
void run_sim(int N, vector<int>& fees, map<MapNode, int>& min_cost_map,
             priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>>& min_cost_queue) {
     min_cost_map[MapNode(1, 0)] = 0;
     min_cost_queue.push(QueueNode(0, 1, 0));
     int cost = min_cost_queue.top().cost;
     int loc = min_cost_queue.top().loc;
     int jump = min_cost_queue.top().jump;
     min_cost_queue.pop();
     while (loc != N) {
         // jump down
         if (loc - jump > 0) {
             int next_loc = loc - jump;
             int next_jump = jump;
             check_jump(fees, min_cost_map, min_cost_queue, loc, jump, next_loc, next_jump);
         }
         // jump up
         if (loc + jump + 1 <= N) {
             int next_loc = loc + jump + 1;
             int next_jump = jump + 1;
             check_jump(fees, min_cost_map, min_cost_queue, loc, jump, next_loc, next_jump);
         }
         cost = min_cost_queue.top().cost;
         loc = min_cost_queue.top().loc;
         jump = min_cost_queue.top().jump;
         min_cost_queue.pop();
     }
     cout << cost << endl;
}


int main() {
    int N;
    vector<int> fees;
    get_input(N, fees);
    map<MapNode, int> min_cost_map; // maps {location, jump} -> cost
    priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>> min_cost_queue; // sorted by min cost
    run_sim(N, fees, min_cost_map, min_cost_queue);
    return 0;
}
