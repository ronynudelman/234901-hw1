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
typedef set<int> si;


const int MAX = 1000 * 14;


void get_input(int& N, vi& v) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int next;
        cin >> next;
        v.push_back(next);
    }
}


si get_all_primes(int max) {
    si primes;
    primes.insert(2);
    for (int num = 2; num <= max; num++) {
        int div_counter = 0;
        for (int div = 2; div <= (int)sqrt(num) + 1; div++) {
            if (num % div == 0) div_counter++;
        }
        if (div_counter == 0) primes.insert(num);
    }
    return primes;
}


// return 2 ^ n
int power_two(int n) {
    int res = 1;
    while (n--) res *= 2;
    return res;
}


// check if the second arg is the subset of the first arg
bool is_subset(int set, int subset) {
    while (set != 0) {
        if ((set % 2 == 0) && (subset % 2 == 1)) {
            return false;
        }
        set /= 2;
        subset /= 2;
    }
    return true;
}


int get_num_of_distinct_primes_of_num(int t, si& primes) {
    int counter = 0;
    for (int div = 2; div <= t && t != 0; div++) {
        if (primes.find(div) != primes.end() && t % div == 0) {
            while (t % div == 0) t /= div;
            counter++;
        }
    }
    return counter;
}


int get_num_of_distinct_primes_of_vec(vi& vec, si& primes) {
    int sum = 0;
    for (auto& t : vec) {
        sum += t;
    }
    return get_num_of_distinct_primes_of_num(sum, primes);
}


vi calc_prices_per_subset(int N, vi& v, si& primes) {
    int total_subsets = power_two(N);
    vi prices_per_subset;
    for (int bits = 0; bits < total_subsets; bits++) {
        int curr_bits = bits;
        int curr_bit = 0;
        vi curr_subset;
        while (curr_bits) {
            if (curr_bits & 1) {
                curr_subset.push_back(v[curr_bit]);
            }
            curr_bits >>= 1;
            curr_bit++;
        }
        int curr_subset_price = get_num_of_distinct_primes_of_vec(curr_subset, primes);
        prices_per_subset.push_back(curr_subset_price);
    }
    return prices_per_subset;
}


void calc_dp(vi& v, vi& prices_per_subset, vi& dp, int n) {
    // dp[n] = max over all subsets of n {subset_price + dp[remaining]}
    int max = 0;
    for (int bits = 1; bits <= n; bits++) {
        if (!is_subset(n, bits)) continue;
        int curr_subset_price = prices_per_subset[bits];
        int remaining = n - bits;
        int best_of_remaining = dp[remaining];
        if (curr_subset_price + best_of_remaining > max) {
            max = curr_subset_price + best_of_remaining;
        }
    }
    dp[n] = max;
}


void wrapper_dp(int N, vi& v, vi& prices_per_subset) {
    int two_power_N = power_two(N);
    vi dp(two_power_N, 0);
    for (int i = 1; i < two_power_N; i++) {
        calc_dp(v, prices_per_subset, dp, i);
    }
    cout << dp.back() << endl;
}


int main() {
    int N;
    vi v;
    get_input(N, v);
    si primes = get_all_primes(MAX);
    vi prices_per_subset = calc_prices_per_subset(N, v, primes);
    wrapper_dp(N, v, prices_per_subset);
    return 0;
}
