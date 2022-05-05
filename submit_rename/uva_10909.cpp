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


// return the minimal power of 2 which is above m
int get_power_of_two_above_s(int s) {
    int power_two = 1;
    while (power_two <= s) {
        power_two <<= 1;
    }
    return power_two;
}


class Tree {

public:
    vector<int> vec;
    int size;

    Tree(int s) : vec(vector<int>()), size(get_power_of_two_above_s(s)) {
        // turn on all the odd bits and turn off all the even bits
        vec = vector<int>(size * 2, 1);
        for (int bit = 0; bit < size; bit += 2) {
            modify(bit, 0);
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
                if (lucky_nums[next_num - i] && lucky_nums[i]) {
                    printf("%d is the sum of %d and %d.\n", next_num, i, next_num - i);
                    break;
                }
            }
        }
    }
}


int main() {
    // if some index is true then it's a lucky number
    // otherwise, it's not a lucky number
    vector<bool> lucky_nums(MAX_SIZE, false);
    // calculate all the lucky numbers
    calc_lucky_nums(lucky_nums);
    // print the output sums according to the input
    calc_sums(lucky_nums);
    return 0;
}
