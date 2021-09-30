double my_solve(int n, int k, vector<pair<double, double>> &d) {

    vector<pair<int, int>> v;

    v.reserve(d.size());
    for (auto &i : d)
        v.emplace_back(abs(i.first), abs(i.second));

    double ans = 1500.;
    double l = 0, r = ans, eps = 0.001;
    while (r - l >= 0.0001) {
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
            while (!yes.empty() && yes.rbegin()->second.second == 2) {
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

        if (in.size() >= k) {
            ans = min(c, ans);
            r = c - eps;
        } else
            l = c + eps;
    }

    return ans;
}
