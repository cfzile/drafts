#include <bits/stdc++.h>

#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define sq(x) (x) * (x)
#define double long double
#define fi first
#define se second

using namespace std;

double solve_true(int n, int k, vector<pii > v) {
    double ans = 100000000;
    for (double x = -1000.; x <= 1000.; x += 0.001) {
        vector<double> q;
        for (int i = 0; i < v.size(); i++)
            q.push_back(sqrt((double) (sq(x - v[i].fi) + sq(v[i].se))));
        sort(all(q));
        if (ans > q[k - 1]) {
            ans = q[k - 1];
        }
    }
    return ans;
}

double my_solve(size_t n_len, size_t k_len, vector<double> x, vector<double> y){
    return 0.;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    srand(time(nullptr));

    int n = 5, k = rand() % n + 1;


    vector<pii > d;
    vector<double> x;
    vector<double> y;
    for (int i = 0; i < n; i++) {
        int xx, yy;
        xx = rand() % 2000 - 1000;
        yy = rand() % 2000 - 1000;
        d.push_back({xx, yy});
        x.push_back(xx);
        y.push_back(yy);
    }

    cout << n << " " << k << "\n";
    for (auto i : d)
        cout << "{" << i.fi << ", " << i.se << "}," << "\n";


    cout << n << " " << k << "\n";
    for (auto i : d)
        cout << "" << i.fi << " " << i.se << " " << "\n";

    cout << solve_true(n, k, d) << "\n";
    cout << my_solve(n, k, x, y) << "\n";
}
