# Counting Points

## 题目描述

粉色士兵们在平面上绘制了 $n$ 个圆心位于 $x$ 轴上的圆。此外，他们告知这些圆的半径之和恰好为 $m$ $^{\text{∗}}$。

请计算至少位于一个圆内或边界上的整数点数量。形式化地说，问题定义如下：

给定一个整数序列 $x_1, x_2, \ldots, x_n$ 和一个正整数序列 $r_1, r_2, \ldots, r_n$，已知 $\sum_{i=1}^n r_i = m$。

你需要统计满足以下条件的整数对 $(x, y)$ 的数量：

- 存在一个下标 $i$ 使得 $(x - x_i)^2 + y^2 \le r_i^2$（$1 \le i \le n$）。

$^{\text{∗}}$ 这个信息真的有用吗？别问我，其实我也不知道。

## 说明/提示

在第一个测试用例中，半径为 $r_1=1$ 的圆完全包含在半径为 $r_2=2$ 的圆内部。因此只需统计后者内部的整数点数量。满足 $x^2 + y^2 \le 2^2$ 的整数点共有 $13$ 个，因此答案为 $13$。

在第二个测试用例中，半径为 $r_1=1$ 的圆未完全包含在半径为 $r_2=2$ 的圆内部。存在 $3$ 个额外整数点位于第一个圆内但不在第二个圆内，因此答案为 $3+13=16$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
2 3
0 0
1 2
2 3
0 2
1 2
3 3
0 2 5
1 1 1
4 8
0 5 10 15
2 2 2 2```

### 输出

```
13
16
14
52```

# 题解

## 作者：The_foolishest_OIer (赞：5)

注意到 $\sum m$ 很小，直接对每一列暴力计算。

用 `map` 存一下每一列的最大值，最大值就是 $\lfloor \sqrt{r^2 - (x - x_0)^2} \rfloor$，$x_0$ 表示当前横坐标。

每一列的贡献就是 $2 \times mx + 1$，不要把 $0$ 忘了。

核心代码：

```cpp
for (int i = 1 ; i <= n ; i++){
	int x = a[i].x,r = a[i].r;
	for (int j = x - r ; j <= x + r ; j++){
		int ret = r * r - (x - j) * (x - j);
		int s = sqrt(ret);
		mx[j] = max(mx[j],s);
	}
}
int ans = 0;
for (int i = 1 ; i <= n ; i++){
	int x = a[i].x,r = a[i].r;
	for (int j = x - r ; j <= x + r ; j++){
		if (vis[j]) continue; // 算过的就别再算了
		vis[j] = 1;
		ans += (2 * mx[j] + 1);
	}
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：2)

[Problem](https://www.luogu.com.cn/problem/CF2074D)

## Statement

给定 $n$ 个圆心在 $x$ 轴上圆和其半径，求包含在所有圆中整数点的个数。

即为求满足 $(x_i - x)^2 + y^2 \leq r_i^2$ 的 $(x,y)$ 的个数。

## Solution

$$
y^2 \leq r_i^2 - (x_i - x)^2
\\ \downarrow \\
-\sqrt{r_i^2 - (x_i - x)^2} \leq y \leq \sqrt{r_i^2 - (x_i - x)^2}
$$

记 $k = \lfloor{\sqrt{r_i^2 - (x_i - x)^2}}\rfloor$，$y$ 在这个范围内有 $2k + 1$ 个取值可能，这样就可以用 map 维护然后统计答案。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
int Test, n, m;
struct Point {
	int x, r;
	bool operator < (const Point &s) const { return r - x < s.r - s.x; }
} P[MAXN];
map<int, int> Pos;
inline int sqr (int x) { return x * x; }
inline int getPos (Point s, int x) { return sqrt (sqr (s.r) - sqr (s.x - x)); }

inline void Solve() {
	cin >> n >> m, Pos.clear();;
	for (int i = 1; i <= n; i ++) cin >> P[i].x;
	for (int i = 1; i <= n; i ++) cin >> P[i].r;
	sort (P + 1, P + n + 1);
	for (int i = 1; i <= n; i ++) {
		for (int p = P[i].x - P[i].r; p <= P[i].x + P[i].r; p ++)
			Pos[p] = max (Pos[p], getPos (P[i], p));
	}
	int Ans = 0;
	for (map<int,int>::iterator iter = Pos.begin(); iter != Pos.end(); iter ++) {
		int x = iter -> second;
		Ans += (x * 2 + 1);
	}
	cout << Ans << endl;
}

signed main() {
	cin >> Test;
	while (Test --) Solve();
	return 0;
}
```

---

## 作者：lw393 (赞：1)

先清题意，再看准数据范围，好了，这题有了。

题意：给 $n$ 个圆，其中圆心在 $(x_i,0)$ 处，半径为 $r$。求所有圆的并中的整点个数。

由于 $m \le 2 \times 10^5$ 所以 $x$ 轴上能被覆盖到的点，在所有的圆没有交点的情况下（取到最大值）为 $2m$ 个。所以直接暴力。

简单讲一下怎么求 $x$ 轴上的任意一个点对答案的贡献。其实本质上就是能覆盖到这个点的所有圆所能取到答案的最大值，即： 

$$ ans_x = \max_{i, x\in[x_i-r,x_i+r]} (2 \times \lfloor\sqrt{r_i^2-(x_i-x)^2}\rfloor + 1)$$

然后计算 $\sum ans_x$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;

int x[N], r[N];
map<int, int>mm;

int sqrt(int x){
    if(x == 1) return 1;
    int l = 0, r = 1e9 + 5;
    while(l + 1 < r){
        int mid = (l + r) >> 1;
        if(mid * mid < x) l = mid;
        else if(mid * mid > x) r = mid;
        else return mid;
    }
    return l;
}

void solve(){
    mm.clear();
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> x[i];
    for(int i = 1; i <= n; i++) cin >> r[i];
    for(int i = 1; i <= n; i++){
        for(int j = x[i] - r[i]; j <= x[i] + r[i]; j++){
            mm[j] = max(mm[j], 2 * sqrt(r[i] * r[i] - x[i] * x[i] - j * j + 2 * x[i] * j) + 1);
        }
    }
    int ans = 0;
    for(auto [a, b] : mm) ans += b;
    cout << ans << '\n';
}

signed main(){
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：wcy110614 (赞：0)

因为指定了 $m=\sum_{i=1}^n r_i \leq 2 \times10^5$，所以可以考虑枚举所有圆覆盖到的点。

记录 $h[p]$，表示 $p$ 位置的被覆盖的最大 $y$ 坐标，用题目中式子 $(x-x_i)^2+y^2\leq r_i^2$ 可以算出被圆 $i$ 覆盖的横坐标为 $x$ 的最大高 $y$，对于每一个圆更新 $y$ 就好了。

因为 $x_i\leq 10^9$，所以 $h$ 数组开不下，但是还是因为 $\sum_{i=1}^nr_i\leq2\times10^5$，所以 $h[p]\ge 1$ 的至多由 $4\times10^5$ 个位置 $p$，直接用 map 开 $h$ 就好了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=4e5+10;
int n,m,tt;
ll ans,x[N],r[N];
map<ll,ll>h;
inline void work(){
	cin>>n>>m,h.clear(),ans=0;
	for(int i=1;i<=n;++i)cin>>x[i];
	for(int i=1;i<=n;++i){
		cin>>r[i];
		for(ll p=x[i]-r[i];p<=x[i]+r[i];++p)h[p]=max(h[p],(ll)(sqrt(r[i]*r[i]-(p-x[i])*(p-x[i]))));
	}
	for(pair<ll,ll> hg:h)ans+=hg.second*2+1;
	return cout<<ans<<"\n",void();
}
int main(){
	cin>>tt;
	while(tt--)work();
	return 0;
}
```

---

