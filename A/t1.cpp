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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;


#define MAX_UF_SIZE 200000


struct UnionFind {
    int next_index;
    map<string, int> string_to_int;
    vector<int> rank;
    vector<int> parent;

    UnionFind(int size) {
        next_index = 0;
        string_to_int = map<string, int>();
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    bool add_new_str(string s) {
        if (string_to_int.find(s) != string_to_int.end()) return false;
        string_to_int[s] = next_index;
        next_index++;
        return true;
    }

    int find(string s) {
        int x = string_to_int[s];
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    int find(int x) {
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) // for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void union_str(string q_str, string p_str) {
        int p = string_to_int[p_str];
        int q = string_to_int[q_str];
        p = find(p);
        q = find(q);
        if(q==p)
        {
            // alredy in the same group
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};


void reverse_str(string& s) {
    string rev_s("");
    for (string::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
        rev_s.push_back(*it);
    }
    s = rev_s;
}



bool is_exist(list<string>& l, string s) {
    for (auto& it : l) {
        if (it == s) {
            return true;
        }
    }
    return false;
}


void check_short_words_list(list<string>& short_words, struct UnionFind& uf) {
    short_words.sort();
    // curr_char holds the last word which is of the size 1, like 'a', 'b', ...
    string curr_char("0");
    for (auto& it : short_words) {
        if (it.size() == 1) {
            curr_char = it;
        }
        if (it.size() == 2 && it.substr(0, 1) == curr_char) {
            uf.union_str(curr_char, it);
        }
    }
}


void check_long_words_list(list<string>& short_words, list<string>& long_words, struct UnionFind& uf) {
    long_words.sort();
    for (list<string>::iterator it = long_words.begin(); it != long_words.end(); ) {
        if (is_exist(short_words, (*it).substr(0, 1))) {
            uf.union_str(*it, (*it).substr(0, 1));
        }
        if (is_exist(short_words, (*it).substr(0, 2))) {
            uf.union_str(*it, (*it).substr(0, 2));
        }
        string current = *it;
        it++;
        if (it == long_words.end()) break;
        string next = *it;
        if (current.substr(0, 3) == next.substr(0, 3)) {
            uf.union_str(current, next);
        }
    }
}


void check_forbidden_words_list(list<pair<string, string>>& forbidden_pairs, struct UnionFind& uf) {
    for (auto& it : forbidden_pairs) {
        if (uf.find(it.first) == uf.find(it.second)) {
            cout << "wait what?" << endl;
            exit(0);
        }
    }
    cout << "yes" << endl;
}


int main() {
    int N;
    cin >> N;
    // short_words is a list which will contain only words of the size 1 or 2
    list<string> short_words;
    // long_words is a list which will contain all the words of the size >=3
    list<string> long_words;
    // forbidden_pairs is a list of pairs of the form 'A not B'
    list<pair<string, string>> forbidden_pairs;
    struct UnionFind uf(MAX_UF_SIZE);
    string s1, s2, relation;
    while (N--) {
        cin >> s1;
        cin >> relation;
        cin >> s2;
        reverse_str(s1);
        reverse_str(s2);
        bool first_is_new = uf.add_new_str(s1);
        bool second_is_new = uf.add_new_str(s2);
        if (first_is_new) {
            if (s1.size() <= 2) {
                short_words.push_back(s1);
            } else {
                long_words.push_back(s1);
            }
        }
        if (second_is_new) {
            if (s2.size() <= 2) {
                short_words.push_back(s2);
            } else {
                long_words.push_back(s2);
            }
        }
        if (relation == "not") {
            forbidden_pairs.push_back({s1, s2});
        }
        else { // relation == "is"
            uf.union_str(s1, s2);
        }
    }
    check_short_words_list(short_words, uf);
    check_long_words_list(short_words, long_words, uf);
    check_forbidden_words_list(forbidden_pairs, uf);
    return 0;
}
