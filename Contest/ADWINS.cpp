#include <bits/stdc++.h>

using namespace std;

class fenwick_tree {
public:
  vector<int> bit;
  void init(int n) {
    bit.assign(n + 5, 0);
  }
  void upd(int i, int v) {
    for ( ; i < bit.size(); i += i & -i) {
      bit[i] += v;
    }
  }
  int query(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
      ret += bit[i];
    return ret;
  }
  int sum(int l, int r) {
    if (l > r) return 0;
    return query(r) - query(l - 1);
  }
};

void solve(void) {
  using ll = long long;
  using rectype = tuple<int, int, int, int>;
  using seg = pair<int, int>;

  int n; cin >> n;
  vector<int> coorx, coory;
  vector<rectype> rects;
  for (int i = 0; i < n; ++i) {
    int u, l; cin >> u >> l;
    int v, r; cin >> v >> r;
    if (u > v) swap(u, v);
    if (l > r) swap(l, r);
    coorx.push_back(u);
    coorx.push_back(v);
    coory.push_back(l);
    coory.push_back(r);
    rects.emplace_back(u, v, l, r);
  }
  sort(coorx.begin(), coorx.end()); coorx.erase(unique(coorx.begin(), coorx.end()), coorx.end());
  sort(coory.begin(), coory.end()); coory.erase(unique(coory.begin(), coory.end()), coory.end());
  auto comp = [&](const vector<int> & ar, int v) {
    return lower_bound(ar.begin(), ar.end(), v) - ar.begin();
  };

  for (auto & [x, y, l, r] : rects) {
    x = comp(coorx, x);
    y = comp(coorx, y);
    l = comp(coory, l);
    r = comp(coory, r);
  }

  ll res = (ll)n * (n - 1) / 2;

  int sz = max(coorx.size(), coory.size());
  fenwick_tree ft;

  auto delseg = [&](const vector<seg> & segs) {
    ft.init(sz);
    for (auto & all : segs)
      ft.upd(all.second + 1, 1);
    for (auto & all : segs) {
      res -= ft.sum(1, all.first);
    }
  };

  vector<seg> ox, oy;
  for (auto & rect : rects) {
    int u, v, l, r; tie(u, v, l, r) = rect;
    ox.emplace_back(u, v);
    oy.emplace_back(l, r);
  }
  delseg(ox); delseg(oy);
  vector<pair<int, int>> updl, queryl, updr,queryr;
  for (auto & rect : rects) {
    int u, v, l, r; tie(u, v, l, r) = rect;
    ++u; ++v; ++l; ++r;
    updl.emplace_back(v, l);
    queryl.emplace_back(u - 1, r + 1);
    updr.emplace_back(u, l);
    queryr.emplace_back(v + 1, r + 1);
  }
  sort(updl.begin(), updl.end());
  sort(queryl.begin(), queryl.end());

  ft.init(sz);
  int ptr = 0;
  for (auto & all : queryl) {
    while (ptr < updl.size() && updl[ptr].first <= all.first) {
      ft.upd(updl[ptr].second, 1);
      ++ptr;
    }
    res += ft.sum(all.second, sz);
  }

  sort(updr.rbegin(), updr.rend());
  sort(queryr.rbegin(), queryr.rend());
  ft.init(sz);
  ptr = 0;
  for (auto & all : queryr) {
    while (ptr < updr.size() && updr[ptr].first >= all.first) {
      ft.upd(updr[ptr].second, 1);
      ++ptr;
    }
    res += ft.sum(all.second, sz);
  }

  cout << res << '\n';
}

signed main(void) {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
  freopen("A.INP", "r", stdin);
  freopen("A.OUT", "w", stdout);
#endif // LOCAL
#define task "ADWINS"
  if (fopen(task".inp", "r")) {
    freopen(task".INP", "r", stdin);
    freopen(task".OUT", "w", stdout);
  }

  int tc; cin >> tc;
  while (tc--) {
    solve();
  }
}
