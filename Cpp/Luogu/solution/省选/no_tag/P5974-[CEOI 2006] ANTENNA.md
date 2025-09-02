# [CEOI 2006] ANTENNA

## 题目描述

给出 $N$ 个点的坐标，要求能够覆盖其中至少 $K$ 个点的圆的最小半径及圆心位置。

## 说明/提示

对于 $100\%$ 的数据， $2\le K\le N\le 500$，$0\le X,Y\le 10^4$。

## 样例 #1

### 输入

```
10 5 
1 8 
2 6 
4 8 
2 2 
9 7 
8 5 
5 3 
3 3 
4 6 
4 1 ```

### 输出

```
2.236068 
3 4 ```

# 题解

## 作者：ottora (赞：0)

关键性质：至少有三个点在圆周上。

记所求半径为 $r$，圆心为 $O$。二分 $r$，枚举圆周上一点 $P$，则 $O$ 落在半径为 $r$ 的 $\odot P$ 上，并且每个点能被覆盖等价于 $O$ 落在 $\odot P$ 的某一段弧上。即，若有至少 $K - 1$ 段弧交于一点，则这个点能成为 $O$。

复杂度 $O\left(n^2 \log n \log V\right)$，代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 505; const double PI = acos(-1), eps = 1e-9;
int n, m, X[MAXN], Y[MAXN]; double R = INFINITY, Ox, Oy;
bool check(int id, double r){
  vector<pair<double, int>> A; int cnt = 1;
  for(int i = 1; i <= n; i++) if(i != id){
    double alpha = atan2(Y[i] - Y[id], X[i] - X[id]) + 2 * PI, d = hypot(X[i] - X[id], Y[i] - Y[id]);
    if(d > 2 * r + eps){continue;} double theta = acos(d / 2 / r) + eps; if(isnan(theta)) theta = eps;
    double u = fmod(alpha - theta + 2 * PI, 2 * PI), v = fmod(alpha + theta, 2 * PI);
    A.emplace_back(u, 1), A.emplace_back(v, -1); if(u > v) cnt++;
  } sort(A.begin(), A.end());
  for(auto [alpha, d]: A) if((cnt += d) >= m){
    if(r < R) R = r, Ox = X[id] + cos(alpha) * r, Oy = Y[id] + sin(alpha) * r;
    return 1;
  } return 0;
}
bool check(double r){
  for(int i = 1; i <= n; i++) if(check(i, r)) return 1;
  return 0;
}
int main(){
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> X[i] >> Y[i];
  double l = 0, r = 1e5; while(r - l > 1e-6){
    double mid = (l + r) / 2;
    if(check(mid)) r = mid; else l = mid;
  }
  cout << fixed << setprecision(9) << R << '\n' << Ox << ' ' << Oy << '\n';
  cerr << (double)clock() / CLOCKS_PER_SEC << endl;
  return 0;
}
```

---

