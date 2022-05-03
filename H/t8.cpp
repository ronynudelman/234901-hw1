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
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;


const int INF = 1e9;


// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source node (s).
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle.
// time: O(VE).
bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (int u = 0; u < g.size(); ++u) for (ii e : g[u]) {
            int v = e.first;
            int w = e.second;
            // relax the edge
            if (d[u] < INF && d[u]+w < d[v]) {
                d[v] = d[u]+w;
                changed = true;
            }
        }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}


// a mapping from {x,y} in the grid to some index in 1-dimensional vector
int cordinates_to_index(ii cords, int W) {
    return cords.second * W + cords.first;
}


void fill_graph(vvii& g, si& stones, si& portals, int W, int H) {
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < H; y++) {
            // we don't add edges which their source is the exit cell
            if (x == W - 1 && y == H - 1) {
                continue;
            }
            int curr_cords = cordinates_to_index({x, y}, W);
            // we don't add edges to gravestone cells
            if (stones.find(curr_cords) != stones.end()) {
                continue;
            }
            // if current cell is a haunted hole then we don't need to
            // add edges to its neighbor cells
            if (portals.find(curr_cords) != portals.end()) {
                continue;
            }
            ii left = {x - 1, y};
            ii right = {x + 1, y};
            ii down = {x, y - 1};
            ii up = {x, y + 1};
            int left_cords = cordinates_to_index(left, W);
            int right_cords = cordinates_to_index(right, W);
            int down_cords = cordinates_to_index(down, W);
            int up_cords = cordinates_to_index(up, W);
            if (left.first >= 0 && stones.find(left_cords) == stones.end()) {
                g[curr_cords].push_back({left_cords, 1});
            }
            if (right.first < W && stones.find(right_cords) == stones.end()) {
                g[curr_cords].push_back({right_cords, 1});
            }
            if (down.second >= 0 && stones.find(down_cords) == stones.end()) {
                g[curr_cords].push_back({down_cords, 1});
            }
            if (up.second < H && stones.find(up_cords) == stones.end()) {
                g[curr_cords].push_back({up_cords, 1});
            }
        }
    }
}


int main() {
    int W, H;
    while (cin >> W >> H && W * H > 0) {
        vvii g(W * H, vii());
        int G;
        cin >> G;
        si stones;
        for (int i = 0; i < G; i++) {
            int x, y;
            cin >> x >> y;
            stones.insert(cordinates_to_index({x, y}, W));
        }
        si portals;
        int E;
        cin >> E;
        for (int i = 0; i < E; i++) {
            int X1, Y1, X2, Y2, T;
            cin >> X1 >> Y1 >> X2 >> Y2 >> T;
            int src = cordinates_to_index({X1, Y1}, W);
            int dst = cordinates_to_index({X2, Y2}, W);
            g[src].push_back({dst, T});
            portals.insert(src);
        }
        fill_graph(g, stones, portals, W, H);
        vi d;
        bool is_negative_cycle = BellmanFord(g, 0, d);
        if (is_negative_cycle) {
            cout << "Never" << endl;
        }
        else if (d.back() == INF){
            cout << "Impossible" << endl;
        }
        else {
            cout << d.back() << endl;
        }
    }

    return 0;
}
