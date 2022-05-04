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


/********** Strongly Connected Components **********/


const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi& g, int u, vi& S, vi& colorMap, int color) {
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(),vi());
    for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int)g.size()-1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: strongly connected components graph of g (sccg).
// time: O(V+E).
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
        if (component[u] != component[v])
            sccg[component[u]].insert(component[v]);
}

// return the number of vertexes with zero in-degree
int get_num_of_zero_indegree(vsi& sccg) {
    vector<bool> zero_indegree(sccg.size(), true);
    // for every edge v -> u
    for (auto& v : sccg) {
        for (auto& u : v) {
            zero_indegree[u] = false;
        }
    }
    int counter = 0;
    for (auto n : zero_indegree) {
        if (n) {
            counter++;
        }
    }
    return counter;
}

// return the number of vertexes with zero out-degree
int get_num_of_zero_outdegree(vsi& sccg) {
    int counter = 0;
    for (auto& v : sccg) {
        if (v.empty()) {
            counter++;
        }
    }
    return counter;
}


int main() {
    int test_cases;
    cin >> test_cases;
    while (test_cases--) {
        int n, m;
        cin >> n >> m;
        vvi g(n, vi());
        while (m--) {
            int s1, s2;
            cin >> s1 >> s2;
            g[s1 - 1].push_back(s2 - 1);
        }
        vsi sccg;
        findSCCgraph(g, sccg);
        if (sccg.size() == 1) {
            cout << "0" << endl;
            continue;
        }
        int zero_indegree = get_num_of_zero_indegree(sccg);
        int zero_outdegree = get_num_of_zero_outdegree(sccg);
        cout << max(zero_indegree, zero_outdegree) << endl;
    }
    return 0;
}
