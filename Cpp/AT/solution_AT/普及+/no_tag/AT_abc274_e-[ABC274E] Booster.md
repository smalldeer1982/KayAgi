# [ABC274E] Booster

## 题目描述

在平面直角坐标系中，有 $n$ 个城镇和 $m$ 个箱子。

你现在在 $(0,0)$，速度为 $1$，你需要走遍所有城镇后回到 $(0,0)$。

你可以选择走到箱子所处的位置，如果你第一次走到这个箱子，你可以吞下箱子里仅剩的一颗能量球，然后你的速度就翻倍了。

求从 $(0,0)$ 走遍所有城镇后回到 $(0,0)$ 所需的最短时间。

## 说明/提示

样例一：路径为 $O-Chest_1-Town_1-Town_2-O$。  
样例二：路径为 $O-Town_1-Town_2-O$。


对于所有数据，$1\leq n\leq 12,0\leq m\leq 5,0\leq |x_i|,|y_i|,|p_i|,|q_i|\leq 10^9$。

Translate by Zek3L.

## 样例 #1

### 输入

```
2 1
1 1
0 1
1 0```

### 输出

```
2.5000000000```

## 样例 #2

### 输入

```
2 1
1 1
0 1
100 0```

### 输出

```
3.4142135624```

## 样例 #3

### 输入

```
1 2
4 4
1 0
0 1```

### 输出

```
4.3713203436```

# 题解

## 作者：蒟蒻炒扇贝 (赞：4)

看到数据范围，考虑状压 dp。

我们设 $f_{i,S}$ 为要走到第 $i$ 个地点，还没有拿到第 $i$ 个地点的增益时，目前所经过城市的状态为 $S$ 的前 $n$ 位，目前所经过宝箱的状态为 $S$ 的后 $m$ 位的最小时间。

为了方便，我们把所有城市的编号设为 $[1,n]$，将所有宝箱的编号设为 $[n+1,n+m]$。

这个 dp 的边界条件怎么设？先将 $f$ 的所有量都初始化为正无穷，然后设 
```cpp
f[i][1<<(i-1)]=dis[0][i];
```
表示之前没有途径任何其他的地点的情况下，我们要去第 $i$ 号地点的最短长度。其中 $dis_{0,i}$ 表示从 $(0,0)$ 到第 $i$ 号地点的最短距离。

由于边界条件是只考虑一个地点的，那么之后的状态转移就要从途径多于一个地点的情况开始考虑（从小范围推大范围）。我们可以枚举目前的状态 $S$，对于每一种状态，我们可以枚举起点 $i$，枚举终点 $j$。

这样，我们有状态转移方程如下：

```cpp
f[j][s|(1<<(j-1))]=min(f[j][s|(1<<(j-1))],f[i][s]+dis[i][j]/v);
```

其中 $v$ 是目前的速度，可以用 ```__builtin_popcount``` 求得。$dis_{i,j}$ 为从 $i$ 号地点到 $j$ 号地点的距离。

然而这一道题所求的答案是走过所有 $n$ 个城市之后还要返回 $(0,0)$ 的最短时间，我们可以枚举所有合法的状态（也就是 $S$ 的前 $n$ 位均为 $1$），然后在原先的 dp 值上加个从 $(0,0)$ 走到第 $i$ 号地点的最短时间即可。统计所有合法答案的最小值即可。

时间复杂度为 $\mathop{O(2^{n+m}(n+m)^2)}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
ld f[22][1<<17],ans=1e18;
int n,m,x[22],y[22];
ld dis(int x1,int y1,int x2,int y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n+m;i++)cin>>x[i]>>y[i];
	for(int i=1;i<=n+m;i++)for(int s=0;s<=(1<<(n+m))-1;s++)f[i][s]=1e18;
	for(int i=1;i<=n+m;i++)f[i][1<<(i-1)]=dis(0,0,x[i],y[i]);
	for(int s=1;s<=(1<<(n+m))-1;s++)
	{
		ld v=(1ll<<(__builtin_popcount(s>>n)));
		for(int i=1;i<=n+m;i++)
		{
			if(!(s&(1<<(i-1))))continue;
			for(int j=1;j<=n+m;j++)if(!(s&(1<<(j-1))))f[j][s|(1<<(j-1))]=min(f[j][s|(1<<(j-1))],f[i][s]+dis(x[i],y[i],x[j],y[j])/v);
		}
	}
	for(int i=1;i<=n+m;i++)for(int s=(1<<n)-1;s<=(1<<(n+m))-1;s+=(1<<n))
	{
		ld v=(1ll<<(__builtin_popcount(s>>n)));
		ans=min(ans,f[i][s]+dis(0,0,x[i],y[i])/v);
	}
	printf("%.7Lf",ans);
}
```


---

## 作者：Register_int (赞：4)

~~赛时迟到一小时而没做完的屑~~  
~~模拟赛 T4 比 T3 还简单，这很合理~~  
就非常套路的状压 dp，首先在普通[旅行商](/problem/P1433)上面做些改动，直接把加速点给压进状态里，转移速度求个 $\text{popcount}$ 就完事了。最后统计答案要遍历所有加速点的通过情况，再加上回到原点用的时间。  
时间复杂度 $O((n+m)^22^{n+m})$。
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

struct node {
	db x, y;
} a[17];

db dp[17][1 << 17];

inline 
db dist(int u, int v) {
	return sqrt((a[u].x - a[v].x) * (a[u].x - a[v].x) + (a[u].y - a[v].y) * (a[u].y - a[v].y));
} 

inline 
db dist(int k) {
	return sqrt(a[k].x * a[k].x + a[k].y * a[k].y);
}

inline 
int popcnt(int k) {
	int cnt = 0;
	while (k) k &= k - 1, cnt++;
	return cnt;
}

int n, m, t, nst, mst;

db ans = 1e18;

int main() {
	scanf("%d%d", &n, &m), t = n + m, nst = (1 << n) - 1 << m, mst = (1 << m) - 1;
	for (int i = m; i < t; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
	for (int i = 0; i < m; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
	memset(dp, 0x44, sizeof dp);
	for (int i = 0; i < t; i++) dp[i][1 << i] = dist(i);
	for (int s = 1; s < 1 << t; s++) {
		for (int i = 0; i < t; i++) {
			if (~s & 1 << i) continue;
			for (int j = 0, x; j < t; j++) {
				if (~s & 1 << j || i == j) continue;
				x = s ^ (1 << i);
				dp[i][s] = min(dp[i][s], dp[j][x] + dist(i, j) / (1 << popcnt(x & mst)));
			}
		}
	}
	for (int i = 0; i < t; i++) {
		for (int j = nst; j < 1 << t; j++) ans = min(ans, dp[i][j] + dist(i) / (1 << popcnt(j & mst)));
	}
	printf("%.8lf", ans);
}
```

---

## 作者：Iratis (赞：2)

upd on 12.9 : 更新了题解中的解释部分。

题目的数据范围提醒我们想到状压，我们可以将箱子与地点看作同类，于是定义 $ f[i][j] $ 表示遍历完的集合为 $ i $，停留在了位置 $ j $。而对于速度改变的问题，只需要使用 $ \operatorname{popcount} $ 快速计算当前经过多少箱子即可。

对于答案的统计，只需要枚举每一个状态 $ f[i][j] $，判断是否遍历完必须走的点，然后计算 $ j $ 走到 $ 1 $ 的时间，取出最小值。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
int n,m,S;
double f[18][140000],nu[140000],P[10];vector<int>v[20];
struct num{double x,y;}a[20],Q;
double dis(num a,num b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
signed main()
{
	scanf("%lld%lld",&n,&m),P[0]=1.0;for(int i=1;i<=m;i++)P[i]=P[i-1]*2;
	for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	for(int i=1;i<=m;i++)scanf("%lf%lf",&a[n+i].x,&a[n+i].y);S=(1<<(n+m))-1;
	for(int i=0;i<=S;i++)for(int x=1;x<=n+m;x++)f[x][i]=1e12;
	for(int i=0;i<=S;i++)v[__builtin_popcount(i)].push_back(i);
	for(int i=0;i<=S;i++)nu[i]=P[__builtin_popcount(i>>n)];
	for(int i=1;i<=n+m;i++)f[i][1<<(i-1)]=dis(Q,a[i]);
	for(int w=1;w<=n+m-1;w++)
	{
		for(int mask:v[w])
		{
			for(int x=1;x<=n+m;x++)
			{
				if(!((mask>>(x-1))&1))continue;
				for(int y=1;y<=n+m;y++)
				{
					if((mask>>(y-1))&1)continue; 
					int no=mask|(1<<(y-1));
					f[y][no]=min(f[y][no],f[x][mask]+dis(a[x],a[y])/nu[mask]);
				}
			}
		}
	}
	double ans=1e12;int mask=(1<<n)-1;
	for(int i=0;i<=(1<<m)-1;i++)
	{
		for(int x=1;x<=n+m;x++)
		{
			int no=mask|(i<<n);
			if(!((no>>(x-1))&1))continue;
			ans=min(ans,f[x][no]+dis(Q,a[x])/nu[no]);
		}
	}
	printf("%.10lf",ans);
	return 0;
}
```


---

## 作者：Mingrui_Yang (赞：1)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc274_e)

## 思路

观察到数据 $n, m$ 的范围较小，考虑状压 DP。

令 $f_{i, j}$ 表示在第 $i$ 个地点，状态为 $j$ 的最短时间。   
我们将城镇与箱子集中存储，状态 $j$ 的前 $n$ 位为经过的城镇，后 $m$ 位为经过的箱子，存储 $x, y$ 时也如此。
 
考虑状态转移。   
我们应该从一个地点移动到另一个地点，本次移动的时间为距离与速度的比值。   
即
```cpp
f[k][j | (1 << k - 1)] = min(f[k][j | (1 << k - 1)], f[i][j] + dist(x[i], y[i], x[k], y[k]) / v);
```
其中的 `dist(x1, y1, x2, y2)` 表示从 $(x1, y1)$ 到 $(x2, y2)$ 的距离。     
`i` 和 `j` 为当前的点及状态，`k` 和 `j|(1<<k-1)` 表示本次转移的目标点及目标状态。   
对于速度 $v$，可以计算出后 $m$ 位中的 $1$ 的个数，有几个 $1$ 速度就会翻几倍，如果有 $x$ 个 $1$，则 $v = 2 ^ x$。

DP 的边界可以先将所有点初始化为正无穷，对于 $f_{i, j}$ 中的 $j$ 只有一个 $1$ 的情况（只到达过一个点），将 $f_{i, j}$ 初始化为原点到这个点的距离。
```cpp
for (int i = 1; i <= n + m; i ++ ) 
	for (int j = 0; j < (1 << n + m); j ++ )
		f[i][j] = 1e18;
for (int i = 1; i <= n + m; i ++ ) f[i][1 << (i - 1)] = dist(0, 0, x[i], y[i]);
```

对于答案，可以将走完了所有城镇的情况的最短时间再加上一个回到原点的时间。

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
#define dist(x1, y1, x2, y2) (sqrt(double((x1) - (x2)) * ((x1) - (x2)) + double((y1) - (y2)) * ((y1) - (y2))))
#define lowbit(x) ((x) & (-(x))) 	// 二进制下最后一个1所代表的值 
using namespace std;
const int N = 20, M = 1 << N;
int n, m;
int x[N], y[N];
long double f[N][M];
inline int numof1(int x) { 	// 计算二进制下1的个数 
	int res = 0; 
	while (x) {
		x -= lowbit(x);
		res ++ ;
	}
	return res;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ) cin >> x[i] >> y[i];
	for (int i = 1; i <= m; i ++ ) cin >> x[i + n] >> y[i + n];
//	puts("-1");
	for (int i = 1; i <= n + m; i ++ ) 
		for (int j = 0; j < (1 << n + m); j ++ )
			f[i][j] = 1e18;
//	puts("1");
	for (int i = 1; i <= n + m; i ++ ) f[i][1 << (i - 1)] = dist(0, 0, x[i], y[i]);
//	puts("1");
	for (int j = 1; j < (1 << n + m); j ++ ) {
		long double v = 1ll << numof1(j >> n);
		for (int i = 1; i <= n + m; i ++ ) {
			if (!(j & (1 << i - 1))) continue;
			for (int k = 1; k <= n + m; k ++ )
				if (!(j & (1 << k - 1)))
					f[k][j | (1 << k - 1)] = min(f[k][j | (1 << k - 1)], f[i][j] + dist(x[i], y[i], x[k], y[k]) / v);
		}
	}
//	cout << 1;
	long double ans = 1e18;
	for (int i = 1; i <= n + m; i ++ )
		for (int j = (1 << n) - 1; j < (1 << n + m); j += (1 << n))
			ans = min(ans, f[i][j] + dist(0, 0, x[i], y[i]) / (1ll << numof1(j >> n)));
	printf("%.10Lf", ans);
	return 0;
}
```

---

## 作者：Tsawke (赞：1)

#  [[ABC274E] Booster](https://www.luogu.com.cn/problem/AT_abc274_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC274E)

## 题面

在经典的 TSP 问题基础上存在初始速度 $ 1 $，增加 $ m $ 个补给点，经过后会使速度变为原来的 $ 2 $ 倍，最小化时间，求最小值。

## Solution

提供一个不太需要动脑但码量略大的思路。

考虑令 $ dp(i, j, k) $ 表示二进制下城镇状态为 $ i $，补给点状态为 $ j $，最后位于点 $ k $ 的最小时间，转移的时候枚举 $ i, j, k $ 再枚举从哪个点而来即可，需要分类讨论从普通点转移还是补给点，以及转移到了普通点还是补给点，对于速率直接使用 `__builtin_popcount(j)` 计算即可。

同时需要注意计算过程中最多只能使用 `long double`，使用 `__float128` 的话会存在约 $ 40 $ 倍常数导致 $ \texttt{TLE} $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define INFLD (ld)(1e12)

template < typename T = int >
inline T read(void);

int N, M;
pair < ll, ll > town[15], sup[8];
ld dp[4500][40][18];
ld ans(INFLD);

ld CalDis(pair < ll, ll > A, pair < ll, ll > B){
    return sqrt((ld)((A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second)));
}

int main(){
    for(int i = 0; i <= 4400; ++i)for(int j = 0; j <= 38; ++j)for(int k = 0; k <= 17; ++k)dp[i][j][k] = INFLD;
    N = read(), M = read();
    for(int i = 1; i <= N; ++i)town[i].first = read(), town[i].second = read();
    for(int i = 1; i <= M; ++i)sup[i].first = read(), sup[i].second = read();
    dp[0][0][0] = 0;
    int SmxN = (1 << N) - 1, SmxM = (1 << M) - 1;
    for(int i = 0; i <= SmxN; ++i)
        for(int j = 0; j <= SmxM; ++j){
            ll rate = 1 << __builtin_popcount(j);
            for(int k = 1; k <= N; ++k)
                if(!(i & (1 << (k - 1)))){
                    for(int pos = 0; pos <= N; ++pos)
                        if(dp[i][j][pos] < INFLD)
                            dp[i | (1 << (k - 1))][j][k] = min(dp[i | (1 << (k - 1))][j][k], dp[i][j][pos] + CalDis(town[pos], town[k]) / (ld)rate);
                    for(int pos = N + 1; pos <= N + M; ++pos)
                        if(dp[i][j][pos] < INFLD)
                            dp[i | (1 << (k - 1))][j][k] = min(dp[i | (1 << (k - 1))][j][k], dp[i][j][pos] + CalDis(sup[pos - N], town[k]) / (ld)rate);
                }
            for(int k = 1; k <= M; ++k)
                if(!(j & (1 << (k - 1)))){
                    for(int pos = 0; pos <= N; ++pos)
                        if(dp[i][j][pos] < INFLD)
                            dp[i][j | (1 << (k - 1))][N + k] = min(dp[i][j | (1 << (k - 1))][N + k], dp[i][j][pos] + CalDis(town[pos], sup[k]) / (ld)rate);
                    for(int pos = N + 1; pos <= N + M; ++pos)
                        if(dp[i][j][pos] < INFLD)
                            dp[i][j | (1 << (k - 1))][N + k] = min(dp[i][j | (1 << (k - 1))][N + k], dp[i][j][pos] + CalDis(sup[pos - N], sup[k]) / (ld)rate);
                }
        }
    for(int j = 0; j <= SmxM; ++j){
        ll rate = 1 << __builtin_popcount(j);
        for(int k = 1; k <= N + M; ++k)
            if(dp[SmxN][j][k] < INFLD)
                ans = min(ans, dp[SmxN][j][k] + CalDis(k <= N ? town[k] : sup[k - N], town[0]) / (ld)rate);
    }printf("%.8Lf\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_02_28 初稿

---

## 作者：Erica_N_Contina (赞：0)

# [ABC274E] Booster

## 思路

明确：我们可以多次加速。箱子和城镇在点的意义上是平等的（即箱子和城镇各自为点，没有依存关系）。然后我们注意到，$1\leq n\leq 12,0\leq m\leq 5$。

由于本题的图建立在平面直角坐标系上，所以默认每两个点之间均有连边，所以我们不可能访问一个点超过 $1$ 次（路过的除外，即从 $u$ 到 $v$ 的直线上有一个已经访问过的城市 $c$）。

因为我们要走遍整个图然后回到起点，很容易就可以想到我们应该用某种方法来**记录当前走过了哪些点**，以及**目前处于哪个点**，并且还要记录经过了几次新箱子（新箱子定义为以前没有经过的有箱子的点）。

事实上，只要我们知道了我们走过了哪些点，我们就可以很快计算出经过了几次新箱子，于是我们不需要记录经过了几次新箱子。

我们惊奇的发现 $n$ 是如此的小，小到我们可以直接使用一个 int 类型整数的二进制表达来表示我们经过了哪些点（很庆幸我们不需要知道每个点经过了几次），所以我们考虑**状态压缩 dp。**

## 函数学习

`__builtin_popcount(n)` 函数，可以返回 $n$ 在二进制下有多少位为 $1$，返回一个数值。


## dp定义

我们记录 $dp_{s,j}$，其中 $s$ 的二进制表达记录了当前经过了哪些点，$j$ 表示当前处于哪个点，$dp_{s,j}$ 记录最小花费。

至于如何计算出经过了几次新箱子，我们可以考虑以下方法：

```C++
int box[N];
//...

int cnt=0;
for(int k=1;k<=cntbox;k++){
    if(s&(1<<(box[k]-1) ) )cnt++;
}
```


对于状态转移方程，我们这样转移，想必是不特别难的。

```C++
dp[s|(1<<(j-1))][j]=min(dp[s|(1<<(j-1))][j],dp[s][i]+dis[i][j]/speed);
```


其中 `s|(1<<(j-1)) ` 可以快速将数字 $s$ 二进制下的第 $ j-i$ 位变成 $1$。如果其本来就为 $1$，则不会改变。因为点的编号是从 $1$ 开始的，而二进制数的最低位为 $0$，所以这里写 $j-1$。

以及其中的 speed 为速度倍率，初始值为 $1$，加速一次为 $2$，两次为 $4$，$k$ 次为 $2^k$。

**枚举 $s$**

我们考虑怎么枚举状态 $s$。我们发现，用来更新 $s$ 的旧 $s$（我们记录为 $t$）在二进制下的 $1$ 的数量一定比 $s$ 少 $1$，且其他 $1$ 的位置都一一对应。即 $t$ 即为 $s$ 在二进制下随便将任意一个 $1$ 翻转为 $0$ 得到的数。于是我们知道在从小到大遍历到 $s$ 时， $t$ 一定被遍历了。

**箱子与城镇状态记录**

既然城镇和箱子的经过状态我们都要记录，那么我们肯定用一个二进制下位数为 $n+m$ 的数字来记录。但是我们如果将箱子和城镇对于的位置打乱了记录肯定很麻烦，所以我们规定 $s$ 的前 $n$ 位（低位）标记经过的城镇状态，后面 $m$ 位记录经过的箱子。

这样的话，我们统计经过的箱子数的方法就更加简单了。

```C++
__builtin_popcount(s>>n);//即把s的前n位删掉，只留下记录箱子的m位
```


**其他**

特别地，对于从 $(0,0) $ 到第一个访问的点，以及从最后一个访问的点到 $(0,0)$ 要特别更新。对于前者，我们为所有 $dp_{s,j}$ 满足 `__builtin_popcount(s)==1` 赋初始值 `diss(0,0,x[i],y[i])`。

## 代码

注意精度 $10^{-6}$。

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=20;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,m,a,b,c,x[N],y[N],p[N],q[N],res,tmp,cnt;
long double dis[20][20],dp[20][1<<17],ans=1e18;

long double diss(int x,int y,int xx,int yy){
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}

void init(){
    for(int i=1;i<=n+m;i++){
        for(int j=i+1;j<=n+m;j++){
            dis[i][j]=dis[j][i]=diss(x[i],y[i],x[j],y[j]);
        }
    }
    for(int i=1;i<=n+m;i++)for(int s=0;s<=(1<<(n+m))-1;s++)dp[i][s]=1e18;
	for(int i=1;i<=n+m;i++)dp[i][1<<(i-1)]=diss(0,0,x[i],y[i]);//初始化数组

}

signed main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    for(int i=1;i<=m;i++){
        cin>>p[i]>>q[i];
        x[i+n]=p[i];y[i+n]=q[i];//将箱子也作为点加入城镇当中
    }
    init();//计算两点之间距离

	for(int s=1;s<=(1<<(n+m))-1;s++){//枚举状态
		int speed=(1ll<<(__builtin_popcount(s>>n)));
		for(int i=1;i<=n+m;i++){
			if(s&(1<<(i-1))){
                for(int j=1;j<=n+m;j++){
                    if(!(s&(1<<(j-1))))dp[j][s|(1<<(j-1))]=min(dp[j][s|(1<<(j-1))],dp[i][s]+dis[i][j]/speed);
		        }
            }
		}
	}
	for(int i=1;i<=n+m;i++)for(int s=(1<<n)-1;s<=(1<<(n+m))-1;s+=(1<<n))
	{
		int speed=(1ll<<(__builtin_popcount(s>>n)));
		ans=min(ans,dp[i][s]+diss(0,0,x[i],y[i])/speed);
	}
    printf("%.8Lf\n",ans);
#ifdef PAUSE_ON_EXIT
    system("pause");
#endif
    return 0;
}
```




---

## 作者：翼德天尊 (赞：0)

状压 dp 确实不好调……

思路很好想，将已经走过的小镇集合压进一个二进制数，已经走过的箱子集合压进一个二进制数，除此之外我们还关心当前到达了哪个节点（注意到我们不会漫无目的地前进，所以我们只关心当前所在位置为小镇或是箱子的状态，我们可以称它们为**关键点**）。

所以不妨设 $dp_{S,T,x}$ 表示已经走过的小镇集合为 $S$，箱子集合为 $T$，且当前位于关键点 $x$ 时的最小步数，转移时枚举下一步要走到哪个关键点，用刷表法转移即可，当前的速度可以通过箱子集合反映。

最后统计答案的时候，小镇的集合必须是满的，箱子的集合随意，记得要加上从最后的终点返程到起点的时间，将所有合法答案取一个 min 即可。

时间复杂度 $O(2^{n+m}(n+m)^2)$.

场上因为少开了个 double，浪费了大把时间和四个罚时。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define double long double
const int N=13;
const int M=6;
const ll INF=1e12;
const int A=1<<N;
const int B=1<<M;
int n,m,a,b,js[N];
double dp[A][B][N+M+2];
struct node{
	double x,y;
}p[N+M+5];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
int count(int x){
	int sum=0;
	while (x){
		if (x&1) ++sum;
		x>>=1;
	}
	return sum;
}
double dis(int x,int y){
	return sqrt((p[x].x-p[y].x)*(p[x].x-p[y].x)+(p[x].y-p[y].y)*(p[x].y-p[y].y));
}
int main(){
	n=read(),m=read(),a=(1<<n),b=(1<<m);
	for (int i=0;i<n+m;i++){
		p[i].x=read(),p[i].y=read();
	}
	js[0]=1;
	for (int i=1;i<=m;i++) js[i]=js[i-1]*2;
	for (int i=0;i<a;i++)
		for (int j=0;j<b;j++)
			for (int k=0;k<n+m;k++)
				dp[i][j][k]=INF;
	for (int i=0;i<n;i++)
		dp[1<<i][0][i]=dis(n+m,i);
	for (int i=n;i<n+m;i++)
		dp[0][1<<(i-n)][i]=dis(n+m,i);
	for (int i=0;i<a;i++){
		for (int j=0;j<b;j++){
			if (i==0&&j==0) continue;
			double speed=js[count(j)];
			for (int k=0;k<n+m;k++){
				if (k<n&&((i&(1<<k))==0)||k>=n&&((j&(1<<(k-n)))==0)) continue;
				for (int s=0;s<n+m;s++){
					if (s<n&&(i&(1<<s))||s>=n&&(j&(1<<(s-n)))) continue;
					if (s<n){
						dp[i|(1<<s)][j][s]=min(dp[i|(1<<s)][j][s],dp[i][j][k]+dis(k,s)/speed);
					}else{
						dp[i][j|(1<<(s-n))][s]=min(dp[i][j|(1<<(s-n))][s],dp[i][j][k]+dis(k,s)/speed);
					}
				}
			}
		}
	}
	double ans=INF;
	for (int i=0;i<b;i++){
		double x=js[count(i)];
		for (int j=0;j<n+m;j++){
			ans=min(ans,dp[a-1][i][j]+dis(n+m,j)/x);
		}
	}
	printf("%.10Lf\n",ans);
	return 0;
} 

```

---

## 作者：Laffey (赞：0)

## 前言

&emsp;&emsp;[无耻地推销博客](https://laffey.fun/abc274e-booster)

&emsp;&emsp;当时比赛的时候看这道题可做，但是没打出来，现在过了，写篇题解补偿下（不是

## Solution

&emsp;&emsp;很明显是一道状压题目，相当于吃奶酪的加强版。

&emsp;&emsp;我们考虑将经过的路径压缩成为一个二进制数，在这里我们为了方便进行 dp，将小镇与宝箱都压到一个状态里。也就是说，我们用一个 $n + m$ 位二进制数表示当前所经过的路径。

&emsp;&emsp;这样，我们不难设计出状态 $f[state, i]$ 表示当前走的路径状态为 $state$，当前处于点 $i$ 时走过的最短时间。

&emsp;&emsp;在这里就有一个问题：题目中还有「速度」这个相关量，我们是否需要再开一维，将速度也记录在状态中进行转移呢？

&emsp;&emsp;答案是否定的。仔细挖掘速度的性质可以发现，速度只和当前走过的路径有关，和当前所处的点、当前的最短时间都没有关系。因此我们只需要预处理一个数组 $g[state]$ 表示当前路径状态为 $state$ 时的速度大小，在转移时直接使用即可。

&emsp;&emsp;综合以上讨论，我们不难得到状态转移方程。设一个二进制数 $state$ 将某一位 $1$ 变成 $0$ 后得到的数为 $prev(state)$，则状态转移方程如下：

$$
f[now, i] = \min_{pre \in prev(state)} \lbrace f[pre, j] + dist(i, j) / g[pre] \rbrace
$$

&emsp;&emsp;其中 $j$ 表示 $pre$ 是由 $now$ 将第 $j - 1$ 位变成 $0$ 得到的（这里设最低位为第 $0$ 位）。初始化 $f[0, 0] = 0$，其余为无穷大。

&emsp;&emsp;有了状态转移方程就不难 dp 了。最后一个要注意的地方是，答案应为所有**经过所有城镇但不一定经过所有宝箱**的状态的最小值。

## Code

&emsp;&emsp;在写代码的时候如果用 `cout` 输出，要注意控制精度。默认保留 $5$ 位会挂掉。

```cpp
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAXN = 18, SIZE = 1 << (MAXN - 1);

double f[SIZE][MAXN];
double g[SIZE];
double dist[MAXN][MAXN];
int x[MAXN], y[MAXN];
int n, m, all;

inline int popcnt(int x)
{
    int ans = 0;
    x >>= n;
    while (x) {
        ans++;
        x -= x & -x;
    }
    return ans;
}

inline void dp()
{
    for (int i = 0; i <= all; i++) {
        for (int j = 0; j < i; j++) {
            dist[i][j] = dist[j][i] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
        }
    }

    for (int i = 0; i < (1 << all); i++) {
        g[i] = 1 << popcnt(i);
    }

    memset(f, 0x7f, sizeof f);
    f[0][0] = 0;
    for (int now = 1; now < (1 << all); now++) {
        for (int i = 1; i <= all; i++) {
            if (!((now >> (i - 1)) & 1)) continue;
            int pre = now & (~(1 << (i - 1)));
            for (int j = 0; j <= all; j++) {
                if (i == j || (j && !((pre >> (j - 1)) & 1))) continue;
                f[now][i] = min(f[now][i], f[pre][j] + dist[i][j] / g[pre]);
            }
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    all = n + m;
    for (int i = 1; i <= all; i++) {
        cin >> x[i] >> y[i];
    }

    dp();

    double ans = INFINITY;
    for (int end = 0; end < (1 << m); end++) {
        int st = ((1 << n) - 1) | (end << n);
        for (int i = 1; i <= all; i++) {
            if (!((st >> (i - 1)) & 1)) continue;
            ans = min(ans, f[st][i] + dist[i][0] / g[st]);
        }
    }

    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}
```

---

## 作者：dbxxx (赞：0)

[您可以在我的博客中查看本文，谢谢支持！](https://www.cnblogs.com/crab-in-the-northeast/p/abc274e.html)

比较板的状压 dp，建议难度评为蓝色，因为本题非常类似，而稍难于难度同为蓝色的 P1171。

本题中我们把城市和加速器都看成点，编号 $0 \sim n + m - 1$，其中 $< n$ 的点代表城市，$\ge n$ 的点代表加速器。

设 $f(S, T, u)$ 表示经过的城市集合为 $S$，经过的加速器集合为 $T$，现在在点 $u$ 的目前最小总时间花费。

枚举时需保证 $u \in S \cup T$。

刷表转移，枚举点 $v$，如果 $v$ 是城市且 $v \not \in S$，那么有转移方程：

$f(S \cup \{v\}, T, v) = f(S, T, u) + \dfrac{d(u, v)}{2^{\operatorname{popcnt}(T)}}$

如果点 $v$ 是加速器且 $v \not \in T$ 那么有转移方程：

$f(S, T \cup \{v\}, v) = f(S, T, u) + \dfrac{d(u, v)}{2^{\operatorname{popcnt}(T)}}$

其中 $d(u, v)$ 表示 $u, v$ 两点之间的距离。

边界条件：

如果 $u$ 是城市： $f(\{u\}, \varnothing, u) = d(-1, u)$；

如果 $u$ 是加速器：$f(\varnothing, \{u\}, u) = d(-1, u)$。

其中 $d(-1, u)$ 表示点 $u$ 到原点的距离。

最后统计答案时，只需统计：

$$
\min[f(\{0, 1, \cdots, n - 1\}, T, u) + \dfrac{d(-1, u)}{2^{\operatorname{popcnt}(T)}},T \subseteq \{n, \cdots ,n + m - 1\},(u < n \lor u \in T)]
$$


不要忘记从 $v$ 回到原点时可能有加速器加速。

另外：实际代码 $u < n \lor u \in T$ 其实是不用检验的，因为终点作为加速器，但没有出现在加速器集合的这种 $f$ 是不合法的，在代码中我们保证它的值是 $+\infty$，不会被统计入 $\min$ 中。

代码中 $S$ 和 $T$ 需要状压，$T$ 状压时，点 $u \ge n$ 在 $T$ 中的位数是 $u - n$。这样可以存储下。

如果预处理 $\operatorname{popcnt}$，时间复杂度可以达到 $\mathcal{O}(2^{n + m}(n+m)^2)$。我没有预处理，所以时间复杂度会再乘一个 $m$，也可以接受。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-22 20:46:15 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-22 21:55:05
 */
#include <bits/stdc++.h>
#define int long long
inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

const int maxn = 13, maxm = 7;
const int maxs = (1 << 12) + 5, maxt = (1 << 5) + 5;

double f[maxs][maxt][maxn + maxm];

double px[maxn + maxm], py[maxn + maxm];
double dis[maxn + maxm][maxn + maxm];

inline int popcnt(int x) {
    int ans = 0;
    for (; x; x >>= 1)
        if (x & 1)
            ++ans;
    return ans;
}

inline bool gmi(double &a, double b) {
    return b < a ? a = b, true : false;
}

signed main() {
    int n = read(), m = read();

    for (int i = 0; i < n + m; ++i) {
        px[i] = (double)read();
        py[i] = (double)read();
        for (int j = 0; j < i; ++j) {
            dis[i][j] = dis[j][i] = 
            hypot(px[i] - px[j], py[i] - py[j]);
        }
    }

    std :: memset(f, 0x42, sizeof(f));
    
    for (int u = 0; u < n; ++u)
        f[1 << u][0][u] = hypot(px[u], py[u]);
    
    for (int u = 0; u < m; ++u)
        f[0][1 << u][u + n] = hypot(px[u + n], py[u + n]);
    
    for (int S = 0; S < (1 << n); ++S) {
        for (int T = 0; T < (1 << m); ++T) {
            for (int u = 0; u < n + m; ++u) {
                if (u >= n) {
                    if ((T & (1 << (u - n))) == 0)
                        continue;
                } else if ((S & (1 << u)) == 0)
                    continue;

                double now = f[S][T][u];
                double sp = (1 << (popcnt(T)));
                // std :: cout << popcnt(T) << std :: endl;
                for (int v = 0; v < n; ++v) {
                    if (S & (1 << v))
                        continue;
                    gmi(f[S | (1 << v)][T][v], 
                    now + dis[u][v] / (sp * 1.0));
                }
                for (int v = 0; v < m; ++v) {
                    if (T & (1 << v))
                        continue;
                    gmi(f[S][T | (1 << v)][v + n], 
                    now + dis[u][v + n] / (sp * 1.0));
                }
            }
        }
    }

    double ans = DBL_MAX;
    int S = (1 << n) - 1;
    for (int T = 0; T < (1 << m); ++T)
        for (int u = 0; u < n + m; ++u)
            gmi(ans, f[S][T][u] + hypot(px[u], py[u]) / (1 << popcnt(T)));

    printf("%.8lf\n", ans);
    return 0;
}
```

如果觉得本篇题解写得好，请不要忘记点赞，谢谢！

---

