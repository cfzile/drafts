#include <bits/stdc++.h>

//#define int long long
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
#define sq(x) (x) * (x)
//#define double float
#define fi first
#define se second

using namespace std;

namespace nasty{
    struct event{
        double x;
        bool type;
        size_t id;
    };


    double get_cathet(const double &y, const double &rad) {
        return std::sqrt(rad * rad - y * y);
    }


    bool intersect_k(const std::vector<double> &x, const std::vector<double> &y,
                     const size_t &k_len, const double &rad) {

        std::vector<event> points;

        for (size_t iter = 0; iter < x.size(); iter++) {
            double cathet = get_cathet(y[iter], rad);
            points.push_back(event{x[iter] - cathet, true, iter});
            points.push_back(event{x[iter] + cathet, false, iter});
        }

        std::sort(points.begin(), points.end(), [](const event& e1, const event& e2) {
            return e1.x == e2.x ? e1.type < e2.type : e1.x < e2.x;
        });

        size_t finished = 0;
        size_t not_started = x.size();
        std::vector<size_t> count(x.size(), x.size());
        for (size_t iter = 0; iter < 2 * x.size(); iter++) {
            if (points[iter].type) {
                count[points[iter].id] -= finished;
                --not_started;
            } else {
                count[points[iter].id] -= not_started;
                ++finished;

                if (count[points[iter].id] >= k_len) {
                    return true;
                }
            }
        }
        return false;
    }


    int bin_search_rad(const std::vector<double> &x, const std::vector<double> &y, const size_t &k_len,
                       double left, double right, const double &eps, double &min_rad) {

        if (right - left < eps) {
            return 0;
        }
        double mid_rad = (left + right) / 2;
        bool move_left = intersect_k(x, y, k_len, mid_rad);
        if (move_left) {
            min_rad = mid_rad;
            bin_search_rad(x, y, k_len, left, mid_rad, eps, min_rad);
        } else {
            bin_search_rad(x, y, k_len, mid_rad, right, eps, min_rad);
        }
    }


    double smallest_circle_algo(size_t n_len, size_t k_len, std::vector<double> x, std::vector<double> y) {

        double ans = std::sqrt(2 * 1000 * 1000);
        bin_search_rad(x, y, k_len, 0, ans, 0.000001, ans);

        return ans;
    }
}

double solve_true(int n, int k, vector<pair<double, double> > v) {
    double ans = 1000000000;
    vector<int> pp;
    double last= 0;
    for (double x = -2000.; x <= 2000.;) {
        vector<double> q;
        for (int i = 0; i < v.size(); i++)
            q.push_back(sq(x - v[i].fi) + sq(v[i].se));
        sort(all(q));
        if (ans > q[k - 1]) {
            ans = q[k - 1];
            last = x;
        }
        x += 0.001;
    }
//    cout << last << "\n";
    return sqrt(ans);
}


double my_solve(int n, int k, vector<pair<double, double>> &d) {

    vector<pair<int, int>> v;

    v.reserve(d.size());
    for (auto &i : d)
        v.emplace_back(i.first + 1000, abs(i.second));

    double ans = 1500.;
    double l = 0, r = ans, eps = 0.0001;
    while (r - l >= 0.00001) {
        double c = (l + r) / 2;

        vector<pair<double, pii>> cnts;
        for (int i = 0; i < v.size(); i++) {
            if (sq(c) < sq(v[i].se))
                continue;
            double s = sqrt(sq(c) - sq(v[i].se));
            if (s != 0) {
                cnts.push_back({v[i].fi - s, {i, 1}});
                cnts.push_back({v[i].fi + s, {i, 0}});
            } else
                cnts.push_back({v[i].fi + s, {i, 2}});
        }

        sort(all(cnts));

        auto comp = [](pair<double, pii > a, pair<double, pii > b) {
            if (a.second.second != b.second.second)
                return a.second.second < b.second.second;
            if (a.first == b.first)
                return a.second.first < b.second.first;
            return a.first < b.first;
        };

        set<pair<double, pii >, decltype(comp)> yes(comp);

        map<int, int> in;
        int i = 0;
        while (i < cnts.size() && cnts[i].fi <= 0) {
            yes.insert(cnts[i]);
            in[cnts[i].second.first] += 1;
            i += 1;
        }

        for (; i < cnts.size(); i++) {
            if (in.size() >= k)
                break;
            while (!yes.empty() && yes.rbegin()->first != cnts[i].fi && yes.rbegin()->second.second == 2) {
                auto it = yes.end();
                it--;
                yes.erase(it);
            }
            in[cnts[i].se.first] += 1;
            yes.insert(cnts[i]);
            if (in[cnts[i].se.fi] == 2) {
                in[cnts[i].se.first] -= 1;
                yes.erase({cnts[i].fi, {cnts[i].se.fi, 1 - cnts[i].se.se}});
            }
            while (!yes.empty() && yes.begin()->se.se == 0 && yes.begin()->first < cnts[i].fi) {
                in[yes.begin()->se.fi] -= 1;
                if (in[yes.begin()->se.fi] == 0)
                    in.erase(yes.begin()->se.fi);
                yes.erase(yes.begin());
            }
        }

//        cout << "R: " << c << " " << in.size() << "\n";
        if (in.size() >= k) {
            ans = min(c, ans);
            r = c - eps;
        } else
            l = c + eps;
    }

    return ans;
}


double getDiff(chrono::_V2::system_clock::time_point time) {
    return (double) chrono::duration_cast<std::chrono::milliseconds>(chrono::system_clock::now() - time).count();
}

signed main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    srand(time(nullptr));

    double error = 0;


    for (int i = 0; i < 100; i++) {

        int n = 20, k = rand() % n + 1;

        vector<pair<double, double> > d;
        vector<double> x;
        vector<double> y;
        for (int i = 0; i < n; i++) {
            int xx, yy;
            xx = rand() % 2001 - 1000;
            yy = rand() % 2001 - 1000;
            d.push_back({xx, yy});
            x.push_back(xx);
            y.push_back(yy);
        }

        cout << n << " " << k << "\n";
        for (auto i : d) {
            cout << i.fi << " " << i.se << "\n";
        }
        cout << "\n";

        auto begin = chrono::system_clock::now();
        double g1 = my_solve(n, k, d);
        double g2 = solve_true(n, k, d);

        double g3 = nasty::smallest_circle_algo(n, k, x, y);

        cout << g1 << " " << g2 << " " << g3 << "\n";

        error += abs(g1 - g2);
        if (abs(g2 - g1) >= 0.001) {
            cout << "ERROR my";
            break;
        }

        if (abs(g2 - g3) >= 0.001) {
            cout << "ERROR nasty";
            break;
        }
//        cout << getDiff(begin) << ";\n";

        cout << g1 - g2 << "\n";
        cout << g3 - g2 << "\n";
//        if (abs(my_solve(n, k, d) - solve_true(n, k, d)) < 0.001){
//            cout << 1;
//        }else
//            cout << 0;
        cout << "\n";
    }

    cout << error << "\n";

}
