# [ABC257D] Jumping Takahashi 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc257/tasks/abc257_d

高橋君が住んでいる二次元平面上の街には $ N $ 個のジャンプ台があります。$ i $ 番目のジャンプ台は点 $ (x_i,\ y_i) $ にあり、ジャンプ台のパワーは $ P_i $ です。また高橋君のジャンプ力は $ S $ で表され、はじめ $ S=0 $ です。高橋君が訓練を $ 1 $ 回行う度に $ S $ は $ 1 $ 増えます。

高橋君は以下の条件を満たす場合に限り、$ i $ 番目のジャンプ台から $ j $ 番目のジャンプ台にジャンプすることができます。

- $ P_iS\geq\ |x_i\ -\ x_j|\ +|y_i\ -\ y_j| $

高橋君の目的は、適切に始点とするジャンプ台を決めることで、そのジャンプ台からどのジャンプ台にも何回かのジャンプで移動できるようにすることです。

目的を達成するためには高橋君は最低で何回訓練を行う必要があるでしょうか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200 $
- $ -10^9\ \leq\ x_i,y_i\ \leq\ 10^9 $
- $ 1\ \leq\ P_i\ \leq\ 10^9 $
- $ (x_i,\ y_i)\ \neq\ (x_j,y_j)\ (i\neq\ j) $
- 入力は全て整数

### Sample Explanation 1

高橋君が $ 2 $ 回訓練したとすると、 $ S=2 $ です。 このとき、$ 2 $ 番目のジャンプ台から全てのジャンプ台に移動することができます。 例えば、$ 4 $ 番目のジャンプ台へは以下の方法で移動ができます。 - $ 2 $ 番目のジャンプ台から $ 3 $ 番目のジャンプ台へジャンプする。（ $ P_2\ S\ =\ 10,\ |x_2-x_3|\ +\ |y_2-y_3|\ =\ 10 $ であり、 $ P_2\ S\ \geq\ |x_2-x_3|\ +\ |y_2-y_3| $ を満たす。） - $ 3 $ 番目のジャンプ台から $ 4 $ 番目のジャンプ台へジャンプする。（ $ P_3\ S\ =\ 2,\ |x_3-x_4|\ +\ |y_3-y_4|\ =\ 1 $ であり、 $ P_3\ S\ \geq\ |x_3-x_4|\ +\ |y_3-y_4| $ を満たす。）

## 样例 #1

### 输入

```
4
-10 0 1
0 0 5
10 0 1
11 0 1```

### 输出

```
2```

## 样例 #2

### 输入

```
7
20 31 1
13 4 3
-10 -15 2
34 26 5
-2 39 4
0 -50 1
5 -20 2```

### 输出

```
18```

# 题解

## 作者：hjyowl (赞：5)

### 题目大意：

你需要求出一个最小的 $s$ ，使得能从某一个点开始，经历所有点至少一次，$i$ 能到达 $j$ 当且仅当 $i$ 到 $j$ 的曼哈顿距离 $\le p_i\times s$ 。

### 思路：

想到二分。

一般来讲，要求在满足某个条件 $p$ 的情况下求出某个值的最大/最小一般都是想二分。

那么本题可以考虑二分 $s$ 的值，现在问题是怎么判断一个数 $x$ 是否可行。

由于 $n$ 的范围挺小的，所以说我们可以对于两点之间，更具给定的 $x$ 先把能到达的点对全部预处理出来。

接下来，对于第 $i$ 个点，每次对点 $i$ 进行 dfs 求联通快，如果存在某个点，他的联通快大小为 $n$ ，返回 $1$ ，否则返回 $0$。

### 实现细节：

需要开 ```long long```。

在计算 $p_i\times s$ 时，需要使用 ```unsigned long long```。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long  N = 510;
long long  x[N],y[N],p[N];
long long  f[N][N];
long long  n;
bool st[N];
long long  cnt =0;
void dfs(long long  u){
	st[u] = 1;
	cnt ++ ;
	for (long long  i = 1; i <= n; i ++ ){
		if (f[u][i] && !st[i]){
			dfs(i);
		}
	}
}
bool check(long long  s){
	memset(f, 0,sizeof f);
	for (long long  i = 1; i <= n; i ++ ){
		for (long long  j = 1; j <= n; j ++ ){
			if ((unsigned long long)p[i] * s >= abs(x[i] - x[j]) + abs(y[i] - y[j])){
				f[i][j] = 1;
			}
		}
	}
	for (long long  i = 1; i <= n; i ++ ){
		memset(st,0,sizeof st);
		cnt = 0;
		dfs(i);
		if (cnt == n){
			return 1;
		}
	}
	return 0;
}
int  main(){
	cin >> n;
	for (long long  i = 1; i <= n ; i++ ){
		cin >> x[i] >> y[i] >> p[i];
	}
	long long  l = 1,r = 1e18,res;//这里不需要管这么多，只需要去1e18就完了，反正二分时间复杂度极低。
	while (l < r){
		long long  mid = l + r >> 1;
		if (check(mid)){
			r = mid;
		}
		else{
			l = mid + 1;
		}
	}
	cout << r;
	return 0;
}
```

---

## 作者：returnzheng (赞：4)

~~一眼题，肯定没思路~~

$ n \le 200$

初步判断时间复杂度是 $ n^3 $

$ n^3 $ 的算法有哪些呢？
当然是 **弗洛伊德** 

首先可以求出任意一个蹦床到另一个蹦床在不借助其他蹦床的情况下最小的 $S$ ，然后可以使用弗洛伊德来求出可以借助其他蹦床时任意一个蹦床到另一个蹦床最小的 $ S $ 。

如果 $i$ 是出发蹦床，$j$ 是终点蹦床，$k$ 是中转蹦床，则

$f_{i,j} = \min(f_{i,j}, \max(f_{i, k}, f_{k, j}))$ 

接下来枚举起点蹦床，然后求出这个蹦床到其它蹦床最小的 $S$ 。
最后是代码实现，一定注意弗洛伊德最外层循环枚举的是中转点，作者因此被此题硬控 30 分钟

> 不开 long long 见祖宗

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
long long xx[300];
long long yy[300];
long long p[300];
long long f[300][300];
long long n;
long long dist(long long a, long long b){
	return abs(xx[a] - xx[b]) + abs(yy[a] - yy[b]);
}
int main(){
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	cin >> n;
	for (long long i = 1; i <= n; i++){
		cin >> xx[i];
		cin >> yy[i];
		cin >> p[i];
	}
	for (long long i = 1; i <= n; i++){
		for (long long j = 1; j <= n; j++){
			f[i][j] =  ceil(1.0 * dist(i, j) / p[i]);
		}
	}
	for (long long k = 1; k <= n; k++){
		for (long long i = 1; i <= n; i++){
			for (long long j = 1; j <= n; j++){
				f[i][j] = min(f[i][j], max(f[i][k], f[k][j]));
			}
		}
	}
	long long ans = 2e18;
	for (long long i = 1; i <= n; i++){
		long long num = 0;
		for (long long j = 1; j <= n; j++){
			num = max(num, f[i][j]);
		}
		ans = min(ans, num);
	}
	cout << ans << endl;
	return 0;
}
/*
4
-10 0 1
0 0 5
10 0 1
11 0 1


7
20 31 1
13 4 3
-10 -15 2
34 26 5
-2 39 4
0 -50 1
5 -20 2

*/
```

---

## 作者：Sparse_Table (赞：2)

# [[ABC257D] Jumping Takahashi 2](https://www.luogu.com.cn/problem/AT_abc257_d)
博客食用更佳：[My blog](https://www.cnblogs.com/0x3f3f3f3f3f3f/p/18391215)。
## 大体思路
这题是一道二分题，因为 $S$ 越大，就越容易满足题目要求，$S$ 越小，就越难满足题目要求，符合二分的特点。

下面先贴上二分代码。
```cpp
LL l = 0, r = 1e10;
while (l < r) {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
}
cout << r;// 二分板子。
```
## check 函数怎么写
因为这题 $n$ 比较小，所以我们可以在每次 check 时，枚举起点，每次从那个点深搜一遍，然后判断搜索到的点数量是否为 $n$，若搜到了 $n$ 个点，直接返回 $1$，若所有点都没有搜到 $n$ 个点，返回 $0$。

下面是 check 函数代码。
```cpp
bool check(LL mid) {
	for (LL i = 1; i <= n; i++) {
		memset(vis, 0, sizeof vis);// vis 用来标记是否已访问过。
		cnt = 0;// 用来记录访问了几个点，cnt 和 vis 数组每次都要清空。
		dfs(i, mid);// 搜索。
		if (cnt == n) return 1;
	}
	return 0;
}
```
## dfs 函数怎么写
dfs 传参要传两个参数：当前点和训练次数。每次判断每个点是否之前被访问过，访问过就结束掉，没访问过就把这个点标记为 $1$，接着枚举下一个点，继续搜索。

下面就是代码。
```cpp
void dfs(LL u, LL mid) {
	if (vis[u]) return; // 查看是否访问过。
	vis[u] = 1, cnt++;
	for (LL v = 1; v <= n; v++) { // 枚举每个点。
		if (p[u] * mid < abs(x[u] - x[v]) + abs(y[u] - y[v])) continue; // 到不了就 continue。
		dfs(v, mid);
	}
}
```
## Code
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;

const LL N = 205;
LL n, x[N], y[N], p[N],  cnt, vis[N];
void dfs(LL u, LL mid) {
	if (vis[u]) return;
	vis[u] = 1, cnt++;
	for (LL v = 1; v <= n; v++) {
		if (p[u] * mid < abs(x[u] - x[v]) + abs(y[u] - y[v])) continue;
		dfs(v, mid);
	}
}

bool check(LL mid) {
	for (LL i = 1; i <= n; i++) {
		memset(vis, 0, sizeof vis);
		cnt = 0;
		dfs(i, mid);
		if (cnt == n) return 1;
	}
	return 0;
}

signed main() {
	cin >> n;
	for (LL i = 1; i <= n; i++) cin >> x[i] >> y[i] >> p[i];
	LL l = 0, r = 1e10;
	while (l < r) {
		LL mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << r;
	return 0;
}
```
## 谨记
一定要开 long long。

题解结束了，有问题大家可以私信我。

---

## 作者：_qingshu_ (赞：2)

# 题意：

有 $n$ 个点，如果两点之间满足 $p_i \times S \ge \mid x_i - x_j \mid+\mid y_i -y_j\mid$，那么这两个点是可以到达的，询问从你钦定的一个起点开始到达所有蹦床（可以分为多步），并使 $S$ 最小，输出最小值。

# 思路：

首先，这个 $S$ 是一个不定的值，且随着 $S$ 的变化，判断结果满足单调性，那么考虑二分答案。

再看到数据范围 $n\le 200$，我们完全可以全遍历一遍所有点作为起点，在用 $O(n^2)$ 去一次查找是否可以完成到达所有蹦床。总时间复杂度 $O(n^2\log{n})$。

# code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
struct edge{
	long long x,y,p;
}a[5200010];
bool vist[5200010],flag;
vector<long long>e[5200010];
void dfs(long long x){
	vist[x]=1;
	for(long long i : e[x]){
		if(!vist[i])dfs(i); 
	}
} 
bool check(long long s){
	for(long long i=1;i<=n;i++)e[i].clear();
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=n;j++){
			if(i!=j&&a[i].p*s>=abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y)){
				e[i].emplace_back(j);
			}
		}
	}
	for(long long i=1;i<=n;i++){
		for(long long j=1;j<=n;j++){
			vist[j]=0;
		}
		dfs(i);
		flag=0;
		for(long long j=1;j<=n;j++){
			if(!vist[j]){
				flag=1;
				break;
			}
		}
		if(!flag){
			return true;
		}
	}
	return false;
}
signed main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].p;
	} 
	long long lef=0,rig=4000000001;
	while(lef<rig){
		long long mid=lef+rig>>1;
		if(check(mid)){
			rig=mid;
		}
		else{
			lef=mid+1; 
		}
	}
	cout<<rig<<endl;
}
```

---

## 作者：_cbw (赞：1)

提供一种 $\Theta \left (\frac{n^3 \log V}{\omega} \right ) \left  (V=4 \times 10^9, \omega=64 \right )$ 的传递闭包做法。

- 前置知识：[传递闭包](https://www.luogu.com.cn/problem/B3611)

不难发现答案具有单调性。考虑二分。

具体的，在 $[1, 4 \times 10^9]$ 的范围内二分 $S$，$\Theta(n^2)$ 枚举两个满足条件的点并标记可达。

然后跑传递闭包，若存在一个点能到达所有点，则当前答案合法。使用 bitset 即可优化至 $\Theta \left (\frac{n^3 \log V}{\omega} \right )$（虽然不用 bitset 也能过。）

Q：为什么二分范围在 $[1, 4 \times 10^9]$？

A：考虑 $n=2,(x_1, y_1) = (-10^9,10^9), (x_2, y_2) = (10^9, -10^9), P_1 = P_2 = 1$。

PS：记得开 long long！

Code（截至 2024.11.10 最优解）：
```cpp
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXN 203
#define BSN 256
using namespace std;
using lli = long long;

struct Node
{
    lli x, y, p;
} nodes[MAXN];

int n;
bitset<BSN> g[MAXN];

inline bool check(const lli &x)
{
    for (int i = 1; i <= n; ++i)
        g[i].reset();  // 清空
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (nodes[i].p * x >= abs(nodes[i].x - nodes[j].x) + abs(nodes[i].y - nodes[j].y))
                g[i].set(j); // 标记可达
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            if (g[i][k])
                g[i] |= g[k];  // 传递闭包
    for (int i = 1; i <= n; ++i)
        if (g[i].count() == n)  // 可以到达所有点
            return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].p;
    lli l = 1, r = 4000000000LL, mid, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1LL;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：2023gdgz01 (赞：1)

根据题意，我们希望 $p_i\times S$ 能最小化，所以考虑二分 $S$。

检查当前 $S$ 是否可行：遍历蹦床起点 $1$ 至 $n$，以此起点进行 dfs ~~（我是不会告诉你 bfs 会超时的！）~~，若能抵达所有蹦床，则当前 $S$ 可行。若所有起点都不能单独抵达所有蹦床，则当前 $S$ 不可行。

最后考虑二分 $S$ 的范围，$S$ 最大的情况为 $1\times S\ge|10^9-(-10^9)|+|10^9-(-10^9)|$，此时，$S$ 最小可为 $4\times10^9$；而易知 $S$ 最小值为 $0$。

代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>

bool vis[205]; //vis[i] 表示抵达 i 号蹦床的标记
int n;
long long l, r = 4e9, mid; //注意 long long
long long x[205], y[205], p[205]; //与 S 计算相关的量都要开 long long

void dfs(int u) { //dfs 遍历蹦床并打标记
	vis[u] = true;
	for (register int i = 1; i <= n; ++i)
		if (!vis[i] && p[u] * mid >= llabs(x[i] - x[u]) + llabs(y[i] - y[u])) //如果没有使用命名空间 std 就一定要写 llabs
			dfs(i);
}

inline bool check() { //检查当前 S 是否可行
	bool flag;
	for (register int i = 1; i <= n; ++i) { //i 为起点
		memset(vis, false, sizeof(vis));
		dfs(i);
		flag = true;
		for (register int j = 1; j <= n; ++j)
			if (!vis[j]) { //j 号蹦床没有抵达过
				flag = false;
				break;
			}
		if (flag)
			return true; //只要有一个起点满足要求就说明当前 S 可行
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%lld%lld%lld", x + i, y + i, p + i);
	while (l < r) {
		mid = l + r >> 1;
		if (check())
			r = mid;
		else
			l = mid + 1;
	}
	printf("%lld", l);
	return 0;
}
```
时间复杂度为 $O(n^3)$，而常数 $\log_2(4\times10^9)<31.9$，可忽略不计。[AC 链接](https://www.luogu.com.cn/record/155910459)

---

## 作者：Tsawke (赞：1)

# [[ABC257D] Jumping Takahashi 2](https://www.luogu.com.cn/problem/AT_abc257_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC257D)

## 题面

给定 $ n $ 个不共点的蹦床，第 $ i $ 个蹦床的位置为 $ (x_i, y_i) $，反弹力为 $ p_i $。存在整数 $ S $。定义能从第 $ i $ 个蹦床跳到第 $ j $ 个蹦床当且仅当 $ p_i \times S \ge \lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert $。你需要钦定一个起点，使得可以从该蹦床抵达所有蹦床（可以多步），并最小化 $ S $，输出最小值。

## Solution

不难发现问题可以转化为，我们要选择一个点，求使得这个点能够到达其它所有点的最大代价，然后求所有起点最大代价的最小值，这东西有点像全源最短路，且数据范围很小。于是不难想到一步转化，可以将原不等式转化为 $ S \ge \dfrac{\lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert}{p_i} $，显然 $ S $ 存在单调性，所以自然可以令 $ S = \left\lceil \dfrac{\lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert}{p_i} \right\rceil $。于是可以认为 $ i \rightarrow j $ 的边权即为这个，然后跑一遍 FLoyd，维护每个源点的最大值，最后取个最小值即可，复杂度 $ O(n^3) $。当然不用 Floyd，或者改用 bfs + 二分答案，都是可以做到 $ O(n^2 \log n) $ 的，不过意义不大。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
struct Node{ll x, y, p;}nod[300];
ll dis[300][300];
ll ans(LONG_LONG_MAX);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i)nod[i].x = read(), nod[i].y = read(), nod[i].p = read();
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
            if(i == j)dis[i][j] = 0;
            else
                dis[i][j] = (ll)ceil((ld)(abs(nod[i].x - nod[j].x) + abs(nod[i].y - nod[j].y)) / (ld)nod[i].p),
                dis[j][i] = (ll)ceil((ld)(abs(nod[i].x - nod[j].x) + abs(nod[i].y - nod[j].y)) / (ld)nod[j].p);
    for(int k = 1; k <= N; ++k)
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                dis[i][j] = min(dis[i][j], max(dis[i][k], dis[k][j]));
    for(int s = 1; s <= N; ++s){
        ll mx(-1);
        for(int t = 1; t <= N; ++t)mx = max(mx, dis[s][t]);
        ans = min(ans, mx);
    }printf("%lld\n", ans);
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

update-2022_12_09 初稿

---

## 作者：xmy201315 (赞：0)

这道题目的答案可以**二分**，那为什么呢？

因为我们假设找到一个 $S$ 满足答案，那么我们让 $S$ 继续变大，那么 $ p_i \times S \ge \lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert $ 这个公式依旧成立。

但是我们让 $S$ 继续变小，那么公式就不一定成立了，这个时候我们一定能找到一个分界线，左边都不满足要求，右边都满足要求。

我们假设二分后 $S = M$，那么怎么判断 $M$ 这个点能不能跳呢？

因为我们不知道起点，所以我们要枚举每个点把它作为起点看一看能否跳到其他点。

那么怎么看这个点是否能走到另外一个点呢？

可以用 **dfs** 或者 **bfs** 。这里就用 dfs 了。在 dfs 时，我们要记两个参数，第一个 $i$ 表示我们走到了第 $i$ 个点，第二个参数就是 $S$（可以不记第二个参数，把它当作全局变量也行）。

如果这个起点能走到所有的点，那么这个 $S$ 就可以，否则我们再看其他点行不行，还不行的话，那二分出来的 $M$ 就不行，还要想其他的办法（详见代码）

**再整理一下思路：**

- $1$、二分。
- $2$、枚举起点，然后用 dfs 或 bfs。

那时间复杂度是什么呢？

二分是 $\mathcal O(\log S)$ 的时间复杂度。

$S$ 最小是 $1$，最大可以是 $4\times 10^9$，为什么呢？

因为假设一个点在左下角，一个点在右上角，那么后面 $\lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert$ 最大是有 $4\times 10^9$ ，$p_i$ 最小是 $1$，那么 $S$ 就得等于 $4\times 10^9$ 才能让等式成立，**注意：这边会爆 int**。

枚举所有点是 $\mathcal O(n)$，dfs 遍历所有边是 $\mathcal O(n^2)$，因为边一共有 $n^2$ 条。所有时间复杂度都乘起来是 $\mathcal O(n^3\times \log S)$。

文字不好理解，来看看代码吧!

[AC记录](https://www.luogu.com.cn/paste/jbnlnkmy)

**AC code:**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,cnt;			//cnt记录从当前这个点出发，能跳到多少个点
ll a[205][2],p[205];
bool b[205];		//记录dfs遍历过了哪些点，true为走过,false为没走过

inline void dfs(int i, ll S){
	b[i] = true;
	++cnt;
	for (int j = 1; j <= n; j++)
		if(!b[j] && p[i]*S >= abs(a[i][0] - a[j][0]) + abs(a[i][1] - a[j][1]))
			dfs(j, S);
}
bool check (ll S){
	for (int i = 1; i <= n; i++) {
		memset(b, false, sizeof(b));
		cnt = 0;
		dfs(i, S);
		if(cnt == n)
			return true;
	}
	return false;
}

int main(){
	scanf ("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf ("%lld%lld%lld", &a[i][0], &a[i][1], &p[i]);
	ll L = 0, R = 4e9;
	while (L + 1 < R) {
		ll M = (L + R) / 2;
		if (check(M))
			R = M;
		else
			L = M;
	}
	printf ("%lld\n", R);
}
```

---

## 作者：_RainCappuccino_ (赞：0)

# [ABC257D] Jumping Takahashi 2

## 主要算法

全源最短路（改版）。

## 题意

此题要求从某一个点到其他任意的点的路径上的最大边权的最小值。

## 思路

### 第一步

计算边权，用两点的曼哈顿距离 $dis$ 去除以出发蹦床的系数 $P_i$，为了满足跳得过去且 $S$ 为整数，所以边权为 $\left \lceil \frac{dis}{P_i} \right \rceil $。

### 第二步

计算从 $u$ 到 $v$ 点路径上的最小的最大的边权，可以用修改的 Floyd 算法，用 $O(n^3)$ 的时间复杂度解决此步骤。

转移方程为：$need_{i,j} = \min(need_{i,j}, \max(need_{i,k}, need_{k,j}))$。

就是把从 $i$ 到 $j$ 的路径分为 $i$ 到 $k$ 的与 $k$ 到 $j$ 的路径，取其路径上的最大值，并与原来的值比较以找到最小边权。

### 第三步

枚举每一个点，从所有点中暴力找出到其他点路径上最大边权最小的点，输出它到其他点路径上最大边权即可。

### 注意事项

一定要全部开 long long！

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define endl '\n'

typedef long long ll;
typedef double db;
const int M = 200 + 10;
const int mod = 1e9 + 7;

int n;
ll x[M], y[M], s[M];
ll need[M][M];//路径上的最大边权

signed main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> x[i] >> y[i] >> s[i];
	memset(need, 0x3f, sizeof need);//初始化
	for (int i = 1; i <= n; i ++){
		for (int j = 1; j <= n; j ++){
			ll dis = abs(x[i] - x[j]) + abs(y[i] - y[j]);
			need[i][j] = ceil((db)dis / (db)s[i]);
			need[j][i] = ceil((db)dis / (db)s[j]);//计算初始边权
		}
	}
	for (int k = 1; k <= n; k ++){
		for(int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				need[i][j] = min(need[i][j], max(need[i][k], need[k][j]));//Floyd 求两点之间的最小路径上的边
	}
	ll ans = LINF;
	for (ll i = 1, maxn; i <= n; i ++){//找最大权最小的点
		maxn = -1;
		for (int j = 1; j <= n; j ++)
			maxn = max(maxn, need[i][j]);
		ans = min(ans, maxn);
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc257-d)

[洛谷原题](/problem/at_abc257_d)

[AtCoder 原题](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc257_d)


给定 $n$ 个不共点的蹦床，其坐标为 $(x_i,y_i)$，弹跳力为 $p_i$。如果从第 $i$ 个蹦床能跳到第 $j$ 个蹦床，那么一定有 $p_i\times S\ge |x_i-x_j|+|y_i-y_j|$。

现在请你最小化 $S$，使得可以从一个蹦床出发可以到达每个蹦床。输出答案 $S$。

# 分析
因为要最小化 $S$，所以不难想到直接二分 $S$。

每次判断预处理出从每个蹦床能到达的蹦床，然后跑一遍 DFS 即可。

时间复杂度：$O(n^3\log n)$（你没看错，是可以 AC 的。）。

空间复杂度：$O(n^2)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
int n;
vector<int> b[205];
bool vis[205], flag;
struct Node{
  int x, y, p;
} a[205];
void dfs(int x){
  if (vis[x]){
    return ;
  }
  vis[x] = 1;
  for (auto v : b[x]){
    dfs(v);
  }
}
bool check(int S){
  for (int i = 1; i <= n; i++){
    b[i].clear();
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= n; j++){
      if (i == j){
        continue;
      }
      if (a[i].p * S >= abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y)){
        b[i].push_back(j);
      }
    }
  }
  flag = 0;
  for (int i = 1; i <= n && !flag; i++){
    for (int j = 1; j <= n; j++){
      vis[j] = 0;
    }
    dfs(i);
    bool f = 1;
    for (int j = 1; j <= n && f; j++){
      if (!vis[j]){
        f = 0;
      }
    }
    flag = f;
  }
  return flag;
}
signed main(){
  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y >> a[i].p;
  }
  int l = 1, r = 1e10;
  while (l < r){
    int mid = (l + r) >> 1;
    if (check(mid)){
      r = mid;
    }else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}
```

---

## 作者：LionBlaze (赞：0)

根据题意可知，答案满足单调性，即如果弹跳力为 $S$ 可以跳遍所有蹦床，则任何一个 $> S$ 的数都可以。

通俗来讲，设 $f(x)$ 为弹跳力为 $x$ 时可不可以跳遍所有蹦床，可以是 $1$，不可以是 $0$，则此函数的取值当 $x$ 从小到大时为 `0000...000111...1111`。

所以考虑**二分答案**。

那么，我们需要考虑答案的上下界：
- 下界：答案显然不可能为负数，所以为 $0$（其实如果 $0$ 是无法跳到任何其他蹦床的，所以至少为 $1$ 也可以）。
- 上界：这个就比较复杂了。考虑极端情况，即 $p_i$ 最小，$\lvert x_i-x_j \rvert + \lvert y_i - y_j \rvert$ 最大，根据数据范围可得前者为 $1$，后者为 $2 \times [10^9 - (-10^9)]$ 即 $4 \times 10^9$，需要使用 `long long` 存储（Python：哈哈哈）。

想好了之后，我们思考判定函数需要怎么写。

一个很显然的做法：枚举每个蹦床作为起点，判断是否可以到达所有蹦床，如果有任何一个点满足条件，则整体满足条件。

如何判断从一个蹦床开始，是否可以到达所有蹦床呢？这就要涉及到一点点图论的知识了，不过不用怕。

我们把每个蹦床看做是图论里的节点，而两个结点中有可能有边（无权的有向边），当且仅当两个可以从蹦床 $i$ 到达蹦床 $j$，也就是 $i$ 和 $j$ 满足题目中所说的 $ p_i \times S \ge \lvert x_i - x_j \rvert + \lvert y_i - y_j \rvert $，则有一条从节点 $i$ 连向节点 $j$ 的边。

判断在跳跃力为 $S$ 时，两个节点 $i,j$ 之间是否可以到达：
```cpp
inline bool available(long long S, int i, int j)
{
	return p[i] * S >= 0ll + abs(x[i] - x[j]) + abs(y[i] - y[j]);
}
```
很简单，就是题目总所给的判断条件。

然后，如何统计从一个节点开始，最多可以到达几个节点呢？很简单，一个 DFS 搞定。
```cpp
bool vis[205];

int dfs(long long S, int u, int n) //使用前先清空 vis 数组
{
	vis[u] = true;
	int sum = 1;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i] && available(S, u, i)) sum += dfs(S, i, n);
	}
	return sum;
}
```
使用了一个 `vis` 数组标记是否访问过，避免重复访问造成的无限递归。

而最后判断函数 `check` 的代码也就呼之欲出了：
```cpp
bool check(long long S, int n)
{
	for(int i=1;i<=n;i++)
	{
		memset(vis, 0, sizeof vis);
		if(dfs(S, i, n) == n) return true;
	}
	return false;
}
```
最后是二分答案的代码：
```cpp
long long l = 1, r = 4e9;
while(l < r)
{
	long long mid = (l+r)/2;
	if(check(mid, n)) r = mid;
	else l = mid + 1;
}
```
提交，能过。但是我们不能说时间复杂度是 $O(\text{能过})$，我们要具体分析时间复杂度：

- 二分答案：~~上下界均已确定所以是常数。~~ $O(\log A)$，其中 $A$ 代表数据范围。
- DFS 求到达的点数：当 $S$ 很大时图是一个完全图，每次要枚举每条边，时间复杂度是 $O(n^2)$。
- 判断：$n$ 次 DFS，时间复杂度为 $O(n^3)$。
- 总时间复杂度：$O(n^3 \log n)$，虽然比较大，但是对于此题的 $2 \le n \le 200$ 且时间限制为 $3$ 秒是可以解决的。

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc257_d)

### 题意

有 $n$ 个点，第 $i$ 个点位置为 $(x_i,y_i)$。对于另外一个点 $j$，若 $p_i\times S\ge |x_i-x_j|+|y_i-y_j|$，则 $i$ 可以到达 $j$。你需要输出最小的 $S$，使得从一个点能够间接或直接到达其他的点。

### 解法

很明显，答案具有单调性，因此我们可以二分 $S$，使用 Floyd 算法检查答案是否合法。这样做的复杂度为 $\Theta(n^3\log (4\times 10^9))$，可以通过。

事实上，用 bfs 进行检验可以使时间复杂度变为 $\Theta(n^2\log (4\times 10^9))$，但使用 Floyd 编码更为容易。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 210;
int n, x[N], y[N], p[N], f[N][N];
ll dis(int i, int j) { return (ll)abs(x[i] - x[j]) + abs(y[i] - y[j]); } //计算两点间的距离
bool check(ll s)
{
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (p[i] * s >= dis(i, j)) f[i][j] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) f[i][j] |= f[i][k] & f[k][j]; //Floyd
    for (int i = 1; i <= n; i++)
	{
        int flag = 1;
        for (int j = 1; j <= n; j++) flag &= f[i][j];
        if (flag) return true;
    } return false;
}


int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &x[i], &y[i], &p[i]);
	ll l = 1, r = (ll)4e9;
	while (l < r)
	{
		ll mid = (l + r) / 2;
		if (check(mid)) r = mid;
		else l = mid + 1;
	} printf("%lld\n", l);
	return 0;
}
```

---

