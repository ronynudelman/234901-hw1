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
typedef vector<ll> vll;
typedef vector<vll> vvll;


const ll MAX_POWER = 32;


vll get_init_first_row(ll N, ll L, ll R) {
    vll init_first_row(N, 0);
    init_first_row[0] = 1;
    init_first_row[1] = R;
    init_first_row[init_first_row.size() - 1] = L;
    return init_first_row;
}


vvll get_matrix_from_first_row(vll& first_row, ll N) {
    vvll matrix(N, vll(N, 0));
    ll starting_column = 0;
    for (ll curr_row = 0; curr_row < N; curr_row++) {
        ll first_row_ptr = 0;
        for (ll curr_column = starting_column; first_row_ptr < N; (++curr_column) %= N) {
            matrix[curr_row][curr_column] = first_row[first_row_ptr];
            first_row_ptr++;
        }
        starting_column++;
    }
    return matrix;
}


void mod_X_on_vec(vll& vec, ll X) {
    ll ten_power_X = 1;
    while (X--) ten_power_X *= 10;
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i] = vec[i] % ten_power_X;
    }
}


vll get_next_row(vll& first_row, vvll& matrix, ll N) {
    vll new_row(N, 0);
    for (ll curr_column = 0; curr_column < N; curr_column++) {
        ll sum = 0;
        for (ll i = 0; i < N; i++) {
            sum += (first_row[i] * matrix[i][curr_column]);
        }
        new_row[curr_column] = sum;
    }
    return new_row;
}


vll calc_Ax(vvll& A, vll& x, ll N) {
    vll res_vec(N, 0);
    for (ll curr_row = 0; curr_row < N; curr_row++) {
        ll sum = 0;
        for (ll i = 0; i < N; i++) {
            sum += (A[curr_row][i] * x[i]);
        }
        res_vec[curr_row] = sum;
    }
    return res_vec;
}


void run(ll N, ll S, ll L, ll R, ll X, vll& nums) {
    vvll power_rows(MAX_POWER, vll());
    power_rows[0] = get_init_first_row(N, L, R);;
    for (ll i = 1; i < MAX_POWER; i++) {
        vll prev_row = power_rows[i - 1];
        vvll prev_matrix = get_matrix_from_first_row(prev_row, N);
        vll curr_row = get_next_row(prev_row, prev_matrix, N);
        mod_X_on_vec(curr_row, X);
        power_rows[i] = curr_row;
    }
    ll S_bits = S;
    // initial row is 1 0 0 0 ... 0 : identity matrix
    vll final_row(N, 0);
    final_row[0] = 1;
    ll curr_bit = 0;
    while (S_bits) {
        if (S_bits % 2 == 1) {
            vll curr_row = power_rows[curr_bit];
            vvll curr_matrix = get_matrix_from_first_row(curr_row, N);
            final_row = get_next_row(final_row, curr_matrix, N);
            mod_X_on_vec(final_row, X);
        }
        S_bits /= 2;
        curr_bit++;
    }
    vvll final_matrix = get_matrix_from_first_row(final_row, N);
    vll res_vec = calc_Ax(final_matrix, nums, N);
    mod_X_on_vec(res_vec, X);
    for (size_t i = 0; i < res_vec.size() - 1; i++) {
        cout << res_vec[i] << " ";
    }
    cout << res_vec.back() << endl;
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        ll N, S, L, R, X;
        cin >> N >> S >> L >> R >> X;
        vll nums;
        for (ll i = 0; i < N; i++) {
            ll next;
            cin >> next;
            nums.push_back(next);
        }
        run(N, S, L, R, X, nums);
    }
    return 0;
}
