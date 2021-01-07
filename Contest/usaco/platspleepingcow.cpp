#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int mod = 1e9 + 7, maxn = 3005;

void add(int & x, int y) {
  x += y;
  if (x >= mod) x -= mod;
  if (x < 0) x += mod;
}

int f[2][maxn][2];
/// available cow to match    all previous cow is match
vector<pair<int, int>> events;
int N, a[maxn], b[maxn];

signed main(void) {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL
  freopen("A.INP", "r", stdin);
  freopen("A.OUT", "w", stdout);
#endif // LOCAL
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> a[i];
    events.emplace_back(a[i], 0);
  }
  for (int i = 1; i <= N; ++i) {
    cin >> b[i];
    events.emplace_back(b[i], 1);
  }
  sort(events.begin(), events.end());
  f[0][0][0] = 1;
  for (auto & it : events) {
    if (it.second == 0) {
      for (int i = 0; i <= N; ++i) {
        for (int j = 0; j < 2; ++j) {
          add(f[1][i + 1][j], f[0][i][j]);
          add(f[1][i][1], f[0][i][j]);
        }
      }
    } else {
      for (int i = 0; i <= N; ++i) {
        if (i) {
          for (int j = 0; j < 2; ++j) {
            add(f[1][i - 1][j], 1ll * i * f[0][i][j] % mod);
          }
        }
        add(f[1][i][0], f[0][i][0]);
      }
    }
    memcpy(f[0], f[1], sizeof f[1]);
    fill_n(&f[1][0][0], maxn * 2, 0);
  }
  cout << (f[0][0][1] + f[0][0][0]) % mod;
}
