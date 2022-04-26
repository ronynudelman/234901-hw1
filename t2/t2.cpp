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


const int MAX_SIZE = 2000001;


class Tree {

public:
    vector<int> vec;
    int size;

    Tree(int s) : vec(vector<int>()), size(1) {
        while (size < s) {
            size *= 2;
        }
        // turn on all the odd bits and turn off all the even bits
        vec = vector<int>(size * 2, 0);
        for (int bit = 1; bit < size; bit += 2) {
            modify(bit, 1);
        }
    }

    void modify(int p, int value) {
        for (vec[p += size] = value; p > 1; p >>= 1) {
            vec[p>>1] = vec[p] + vec[p^1];
        }
    }

    // find the n'th number which its bit is on where n == index
    int find_num_by_index(int index) {
        int left_subtree_sum = 0;
        int current_node = 1;
        while (current_node < size) {
            if (vec[current_node * 2] + left_subtree_sum >= index) {
                current_node *= 2;
            }
            else {
                left_subtree_sum += vec[current_node * 2];
                (current_node *= 2)++;
            }
        }
        return current_node - size;
    }

    int get_num_of_bits_on() {
        return vec[1];
    }

};


void calc_lucky_nums(vector<bool>& lucky_nums) {
    lucky_nums[1] = true;
    Tree tree(MAX_SIZE);
    for (int next_lucky_index = 2;\
        next_lucky_index <= tree.get_num_of_bits_on();\
        next_lucky_index++) {

        int next_lucky = tree.find_num_by_index(next_lucky_index);
        if (next_lucky >= lucky_nums.size()) {
            continue;
        }
        lucky_nums[next_lucky] = true;
        for (int next_index_to_remove = next_lucky;\
            next_index_to_remove < tree.get_num_of_bits_on();\
            next_index_to_remove += (next_lucky - 1)) {

            int next_to_remove = tree.find_num_by_index(next_index_to_remove);
            tree.modify(next_to_remove, 0);
        }
    }
}


void calc_sums(vector<bool>& lucky_nums) {
    int next_num;
    while (cin >> next_num) {
        if (next_num % 2 == 1) {
            printf("%d is not the sum of two luckies!\n", next_num);
        }
        else {
            for (int i = next_num / 2; i > 0; i--) {
                if (lucky_nums[i] && lucky_nums[next_num - i]) {
                    printf("%d is the sum of %d and %d.\n", next_num, i, next_num - i);
                    break;
                }
            }
        }
    }
}


int main() {
    vector<bool> lucky_nums(MAX_SIZE, false);
    calc_lucky_nums(lucky_nums);
    calc_sums(lucky_nums);
    return 0;
}
