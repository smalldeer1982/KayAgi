# Disjoint Triangles

## 题目描述

一个点属于一个三角形，当且仅当它在三角形内部或在三角形的某一条边上。如果平面上不存在任何一个点同时属于两个三角形，则称这两个三角形是互不相交的。

给定平面上的 $n$ 个点。任意两点不重合，且任意三点不共线。

请你计算，从这些点中选出两个互不相交的三角形的不同方案数。仅三角形的顺序不同或三角形内部顶点的顺序不同的两种方案视为相同。

## 说明/提示

在第一个样例中，有六对互不相交的三角形，如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025F/224e0d337ca1a48a9a97b8b70748690fd742ec0c.png)

所有其他的三角形对都不是互不相交的，例如下图中的三角形对：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025F/a7bbe9d71b8b533533e508febc08cb4b5450a512.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 1
2 2
4 6
4 5
7 2
5 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
7
0 -1000000000
-5 -5
5 -5
-5 0
5 0
-2 2
2 2
```

### 输出

```
21
```

# 题解

## 作者：fighter (赞：5)

## 题意

[传送门](https://www.luogu.org/problemnew/show/CF1025F)。

给出平面上的一些点，从其中选出6个点，组成两个三角形，求使两个三角形不相交（即平面上不存在一个点同时属于两个三角形）的方案数，如果选的点相同但组成的三角形不同则算不同的方案。

## 分析

首先有一个结论：如果两个三角形不相交，那么一定存在两条内公切线。如下图（感性理解一下）：

![VJur90.png](https://s2.ax1x.com/2019/06/03/VJur90.png)

那么我们就可以枚举内公切线了。

对于输入的每一个点，我们让它和其他$n-1$个点组成直线，并进行极角排序，然后逆时针方向枚举这些直线，同时维护在直线右侧的点的数量，对于每一条直线，利用乘法原理计算方案。

还有一些小细节：每一条直线实际上可以组成两个三角形。如上图中，直线$CE$既可以组成$\triangle ABC$和$\triangle DEF$，也可以组成$\triangle ABE$和$\triangle CDF$。所以每次计算的时候要乘$2$。但是每一个三角形又会被两条直线同时计算，所以最后答案又要减半，那么实际上就完全抵消了。

同时，我们只枚举极角小于$0$的直线，防止共线的情况算重。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define MAX 2005
using namespace std;

const double PI = acos(-1.0);

struct vec{
    double x, y;
}a[MAX];

int n;
double b[MAX];
ll ans;

ll C2(ll x){
    return (x-1)*x/2;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf", &a[i].x, &a[i].y);
    }
    
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= n; ++j) {
            if(i != j){
                b[++cnt] = atan2(a[j].y-a[i].y, a[j].x-a[i].x);
            }
        }
        sort(b+1, b+cnt+1);
        for (int j = 1, k = 1; j <= cnt && b[j] <= 0; ++j) {
            while(k <= cnt && b[k]-b[j] < PI){		//在直线右侧。
                k++;
            }
            ll l = k-j-1, r = cnt-l-1;		//注意一下点的个数细节：当前点和当前k不能算
            ans += C2(l)*C2(r);		//乘法原理
        }
    }
    
    cout << ans << endl;

    return 0;
}
```



---

## 作者：Arghariza (赞：1)

考虑两个互不相交的三角形，寻找一个方式能够不重不漏地统计它们。

容易发现两条不交的线段 $A_1A_2,B_1B_2$ 之间，必然存在一条直线将 $A_1A_2,B_1B_2$ 分在直线两端，且与 $A_1A_2,B_1B_2$ 无交。证明的话，随意将 $A_1A_2$ 或者 $B_1B_2$ 线段向对方平移一小段即可。我们发现三角形也存在这样的性质，也就是两个不交的三角形之间必然存在一条直线把它们分到直线两侧，证明同理。

事实上这样的直线有无限条，拎出任意一条这样的直线 $l$ 进行旋转，发现最后这条直线 $l'$ 会过两个三角形**至少 $2$ 个顶点**，且这样的直线 $l'$ 只有 $2$ 条（一条顺时针旋转，一条逆时针旋转），如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wusr42q0.png)

我们可以找到一条两个三角形之间的蓝色直线 $l$，顺时针旋转得到直线 $l_1:BD$，逆时针旋转得到直线 $l_2:CD$。

于是我们就可以枚举 $l_1,l_2$ 了，具体地：

- 枚举直线 $l$ 的一个端点 $P_x$，将 $P_x$ 当作坐标原点，对所有向量 $\overrightarrow{P_xP_y}(y\in \{1,2,\cdots ,x-1,x+1,\cdots ,n\})$ 进行极角排序。
- 对于一条直线 $P_xP_y$，考虑统计以 $P_xP_y$ 作为 $l_1/l_2$ 的三角形对。设在 $P_xP_y$ 上方的点的个数为 $c$，那么合法的三角形对数为 $2\dbinom{c}{2}\dbinom{n-2-c}{2}$（乘 $2$ 是因为同一边的两个点既可以连 $P_x$ 也可以连 $P_y$）。
- 由于已经进行极角排序，所以顺序枚举所有 $P_xP_y$，然后双指针就可以动态维护 $c$，统计答案即可。

最后每个三角形对被 $l_1$ 算了一遍，被 $l_2$ 也算了一遍。所以答案要除以 $2$。

复杂度 $O(n^2\log n)$。

```cpp
// Problem: F. Disjoint Triangles
// Contest: Codeforces - Codeforces Round 505 (rated, Div. 1 + Div. 2, based on VK Cup 2018 Final)
// URL: https://codeforces.com/problemset/problem/1025/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int N = 2e3 + 200;
const db Pi = acos(-1);

struct vec {
	int x, y;
	vec () { }
	vec (int _x, int _y) : x(_x), y(_y) { }
	vec operator + (const vec &rh) const { return vec(x + rh.x, y + rh.y); }
	vec operator - (const vec &rh) const { return vec(x - rh.x, y - rh.y); }
	vec operator - () const { return vec(-x, -y); }
	db arc() { return atan2(y, x); }
} a[N], b[N];
int n;
db d[N];

int f(int x) { return x * (x - 1) / 2; }
ll calc(int x) {
	vector<int> dn, up;
	for (int i = 1; i <= n; i++) {
		if (i == x) continue;
		b[i] = a[i] - a[x], d[i] = b[i].arc();
		if (d[i] <= 0) dn.pb(i);
		else up.pb(i);
	}
	ll res = 0;
	sort(dn.begin(), dn.end(), [](int &x, int &y) { return d[x] < d[y]; });
	sort(up.begin(), up.end(), [](int &x, int &y) { return d[x] < d[y]; });
	for (int i = 0, j = 0, ct = up.size(); i < dn.size(); i++) {
		while (j < up.size() && d[up[j]] <= Pi + d[dn[i]]) j++, ct--;
		if (i) ct++; res += 1ll * f(ct) * f(n - 2 - ct);
	}
	return res;
}

void solve() {
	cin >> n;
	for (int i = 1, x, y; i <= n; i++)
		cin >> x >> y, a[i] = vec(x, y);
	ll res = 0;
	for (int i = 1; i <= n; i++) res += calc(i);
	cout << res << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：yyy爱编程 (赞：0)

@fighter 大佬讲的已经很好了

我再来发一篇自己的见解吧

给定$n$个点，求能找到几对三角形，满足它们的顶点是 $n$ 个点中的若干个，且不相交。

两个三角形没有相交，则必然存在两条内公切线，并且两个三角形分别在公切线两端。

我们枚举这条公切线上的两个顶点，令它们分别为两个三角形的顶点。然后求出两边分别有多少个点，再计数即可。

具体计算时，先枚举一个点，然后以这个点为原点对其他点极角排序，然后按照极角序枚举每一条公切线即可。可以通过二分或者双指针的方式得到两边分别有多少个点。

时间复杂度 $O(n^2\log n)$。

---

