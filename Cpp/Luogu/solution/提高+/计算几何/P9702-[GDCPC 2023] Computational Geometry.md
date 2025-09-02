# [GDCPC 2023] Computational Geometry

## 题目描述

给定一个有 $n$ 个顶点的凸多边形 $P$，您需要选择 $P$ 的两个顶点，并用一条同时穿过这两个顶点的直线，将 $P$ 分成两个面积均为正数的小多边形 $Q$ 和 $R$。

记 $d(Q)$ 表示多边形 $Q$ 的直径，$d(R)$ 表示多边形 $R$ 的直径，求 $(d(Q))^2 + (d(R))^2$ 的最小值。

请回忆：一个多边形的直径，指的是该多边形内部或边界上任意两点之间的距离的最大值。

## 样例 #1

### 输入

```
2
4
1 0
2 0
1 1
0 0
6
10 4
9 7
5 7
4 5
6 4
9 3```

### 输出

```
4
44```

# 题解

## 作者：rui_er (赞：2)

这题一看就不是计算几何，考虑区间 DP。

设凸多边形的 $n$ 个顶点依次为 $P_1,P_2,\cdots,P_n$。

设 $f_{i,j}$ 在 $i < j$ 时表示 $P_i,P_{i+1},\cdots,P_{j-1},P_j$ 组成的多边形的直径的平方，在 $i > j$ 时表示 $P_i,P_{i+1},\cdots,P_n,P_1,\cdots,P_{j-1},P_j$ 组成的多边形的直径的平方。容易得到转移方程：

$$
f_{i,j}=\max\{f_{i+1,j},f_{i,j-1},dis^2(P_i,P_j)\}
$$

其中下标均为模 $n$ 意义下。

答案即为每一对能将多边形分为两个面积为正的部分的点 $(P_i,P_j)$ 中，$f_{i,j}+f_{j,i}$ 的最小值。其中，$(P_i,P_j)$ 能将多边形分为两个面积为正的部分，当且仅当 $P_{i-1},P_i,P_j$ 不共线，且 $P_i,P_{i+1},P_j$ 不共线，使用向量叉积计算即可。

时间复杂度 $O(n^2)$。

```cpp
// Problem: T368391 [GDCPC2023] M-Computational Geometry
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T368391?contestId=135929
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 5e3 + 5;

ll T, n, x[N], y[N], diam[N][N];

inline ll sq(ll x) {return x * x;}
inline bool line(ll i, ll j, ll k) {
    ll v1x = x[i] - x[j], v1y = y[i] - y[j];
    ll v2x = x[i] - x[k], v2y = y[i] - y[k];
    return v1x * v2y - v2x * v1y == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; --T) {
        cin >> n;
        rep(i, 0, n - 1) cin >> x[i] >> y[i];
        auto inc = [&](ll x) {return (x + 1) % n;};
        auto dec = [&](ll x) {return (x - 1 + n) % n;};
        rep(dt, 1, n - 1) {
            rep(L, 0, n - 1) {
                ll R = (L + dt) % n;
                diam[L][R] = max({diam[inc(L)][R], diam[L][dec(R)], sq(x[L] - x[R]) + sq(y[L] - y[R])});
            }
        }
        ll ans = numeric_limits<ll>::max();
        rep(i, 0, n - 1) {
            rep(j, 0, n - 1) {
                if(!line(dec(i), i, j) && !line(i, inc(i), j)) {
                    chkmin(ans, diam[i][j] + diam[j][i]);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 题目分析

看见这道题大概一看就是 DP。

状态：设 $f_{i,j}$ 表示逆时针顶点 $i$ 到顶点 $j$ 组成的多边形的直径的平方。

状态转移方程：$f_{i,j}=\max\{f_{i,j-1},f_{i+1,j},dis(i,j)^2\}$，区间 DP。

最终答案为 $ans=\min\{f_{i,j}+f_{j,i}\}$，注意 $i,j$ 不能共线，叉积判断即可。

时间复杂度为 $O(n^2)$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,f[5001][5001],ans;
int pow(int a){
	return a*a;
}
struct Point{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){}
	Point operator-(Point b){
		return Point(x-b.x,y-b.y);
	}
	int operator^(Point b){
		return llabs(x*b.y-y*b.x);
	}
}p[5001];
int dis(Point a,Point b){
	return pow(a.x-b.x)+pow(a.y-b.y);
}
void Main(){
	ans=0x3f3f3f3f3f3f3f3fll;
	cin>>n;
	for(int i=0,x,y;i<n;i++){
		cin>>x>>y;
		p[i]=Point(x,y);
	}
	for(int i=2,k;i<=n;i++)
		for(int j=0,k=i-1;j<n;j++,k++){
			k=(i+j-1)%n;
			f[j][k]=max({dis(p[j],p[k]),f[(j+1)%n][k],f[j][(k+n-1)%n]});
		}
	for(int i=0,pre,nxt;i<n;i++){
		nxt=(i+1)%n,pre=(n+i-1)%n;
		for(int j=i+1;j<n;j++)
			if(i!=j&&((p[nxt]-p[i])^(p[nxt]-p[j]))&&((p[pre]-p[i])^(p[pre]-p[j])))
				ans=min(ans,f[i][j]+f[j][i]);
	}
	cout<<ans<<'\n';
	return；
}
signed main(){
	ios::sync_with_stdio(0);
	for(cin>>T;T;--T)
		Main();
    return 0;
}
```

---

## 作者：NobodyThere (赞：0)

看似是计算几何，实际是简单 dp 的诈骗题。你被骗了吗？

由于 $n\leq 5\times10^3$，我们可以：

1. 直接求出每个能被割出来的多边形的直径；

2. 暴力枚举穿过顶点的直线，依次判断两边面积是否为正，若如此，统计到答案。

注意到前者的多边形的顶点对应到原多边形是一段环上的区间，其直径可以 dp 求得：

$$
f_{l,r}=\max\{f_{l,last(r)},f_{next(l),r},dist(l,r)\}.
$$

其中 $dist(l,r)$ 表示编号为 $l$ 的点到编号为 $r$ 的点的距离的平方。$last(x),next(x)$ 分别表示 $x$ 在环上的上一个点和下一个点。

至于后者的判断部分，可以通过判断直线上的两顶点与两个割出来的多边形上的其它点是否共线进行判断，叉积判一下就行了。

还是放一下代码吧。和上述内容相差不大，不用注释应该也能看懂。

```cpp
#include <cstdio>
#include <algorithm>
typedef long long ll;
const int N = 5e3;
const ll INF = 9e18;
int T, n;
ll x[N + 3], y[N + 3];
ll f[N + 3][N + 3], ans;
inline int lst(int idx) {return idx == 0 ? n - 1 : idx - 1;}
inline int nxt(int idx) {return idx == n - 1 ? 0 : idx + 1;}
inline ll dist(int a, int b) {
    return (x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]);
}
inline ll cross(ll x1, ll y1, ll x2, ll y2) {
    return x1 * y2 - x2 * y1;
}
bool check(int a, int b, int c) {
    return cross(x[b] - x[a], y[b] - y[a], x[c] - x[b], y[c] - y[b]) != 0;
}
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%lld %lld", &x[i], &y[i]);
        }
        for(int len = 2; len <= n; len++) {
            for(int i = 0, j = len - 1; i < n; i++, j = nxt(j)) {
                f[i][j] = std::max({f[i][lst(j)], f[nxt(i)][j], dist(i, j)});
            }
        }
        ans = INF;
        for(int i = 0; i < n; i++) {
            for(int j = nxt(i); j != i; j = nxt(j)) {
                if(check(i, nxt(i), j) && check(j, nxt(j), i)) {
                    ans = std::min(ans, f[i][j] + f[j][i]);
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

