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


class Node {
public:
    int cost;
    int loc;
    int jump;
    Node(int cost, int loc, int jump) : cost(cost), loc(loc), jump(jump) {}
    bool operator>(const Node& other) const { return cost > other.cost; }
};


void run_sim(int N, vector<int>& fees, vector<vector<int>>& min_cost_vec,
             priority_queue<Node, vector<Node>, greater<Node>>& min_cost_queue) {
     min_cost_queue.push(Node(0, 1, 0));
     while (!min_cost_queue.empty()) {
         int cost = min_cost_queue.top().cost;
         int loc = min_cost_queue.top().loc;
         int jump = min_cost_queue.top().jump;
         min_cost_queue.pop();
         if (loc == N) {
             cout << cost << endl;
             return;
         }
         // jump up
         if (loc + jump + 1 <= N && !min_cost_vec[loc + jump + 1][jump + 1]) {
             min_cost_vec[loc + jump + 1][jump + 1] = min_cost_vec[loc][jump] + fees[loc + jump + 1];
             min_cost_queue.push(Node(min_cost_vec[loc + jump + 1][jump + 1], loc + jump + 1, jump + 1));
         }
         // jump down
         if (loc - jump > 0 && !min_cost_vec[loc - jump][jump]) {
             min_cost_vec[loc - jump][jump] = min_cost_vec[loc][jump] + fees[loc - jump];
             min_cost_queue.push(Node(min_cost_vec[loc - jump][jump], loc - jump, jump));
         }
     }
}


int main() {
    int N;
    vector<int> fees;
    get_input(N, fees);
    vector<vector<int>> min_cost_vec(N + 1, vector<int>(N, 0));
    priority_queue<Node, vector<Node>, greater<Node>> min_cost_queue;
    run_sim(N, fees, min_cost_vec, min_cost_queue);
    return 0;
}
