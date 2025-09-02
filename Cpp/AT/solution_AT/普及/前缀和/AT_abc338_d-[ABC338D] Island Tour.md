# [ABC338D] Island Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_d

AtCoder 諸島は $ N $ 個の島からなり、これらの島々は $ N $ 本の橋によって結ばれています。 島には $ 1 $ から $ N $ までの番号が付けられていて、$ i\ (1\leq\ i\leq\ N-1) $ 本目の橋は島 $ i $ と島 $ i+1 $ を、$ N $ 本目の橋は島 $ N $ と島 $ 1 $ を双方向に結んでいます。 橋を渡る以外に島の間を行き来する方法は存在しません。

AtCoder 諸島では、島 $ X_1 $ から始めて島 $ X_2,X_3,\dots,X_M $ を順に訪れる**ツアー**が定期的に催行されています。 移動の過程で訪れる島とは別の島を経由することもあり、ツアー中に橋を通る回数の合計がツアーの**長さ**と定義されます。

厳密には、**ツアー**とは以下の条件を全て満たす $ l+1 $ 個の島の列 $ a_0,a_1,\dots,a_l $ のことであり、その**長さ** は $ l $ として定義されます。

- 全ての $ j\ (0\leq\ j\leq\ l-1) $ について、島 $ a_j $ と島 $ a_{j+1} $ は橋で直接結ばれている
- ある $ 0\ ＝\ y_1\ <\ y_2\ <\ \dots\ <\ y_M\ =\ l $ が存在して、全ての $ k\ (1\leq\ k\leq\ M) $ について $ a_{y_k}\ =\ X_k $

財政難に苦しむ AtCoder 諸島では、維持費削減のため橋を $ 1 $ 本封鎖することになりました。 封鎖する橋をうまく選んだとき、ツアーの長さの最小値がいくつになるか求めてください。

## 说明/提示

### 制約

- $ 3\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 2\leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ X_k\leq\ N $
- $ X_k\neq\ X_{k+1}\ (1\leq\ k\leq\ M-1) $
- 入力は全て整数

### Sample Explanation 1

\- $ 1 $ 本目の橋を封鎖した場合：通る島の列として $ (a_0,a_1,a_2)=(1,3,2) $ を取ることで島 $ 1,3,2 $ を順に訪れることができ、長さ $ 2 $ のツアーが催行できます。これより短いツアーは存在しません。 - $ 2 $ 本目の橋を封鎖した場合：通る島の列として $ (a_0,a_1,a_2,a_3)=(1,3,1,2) $ を取ることで島 $ 1,3,2 $ を順に訪れることができ、長さ $ 3 $ のツアーが催行できます。これより短いツアーは存在しません。 - $ 3 $ 本目の橋を封鎖した場合：通る島の列として $ (a_0,a_1,a_2,a_3)=(1,2,3,2) $ を取ることで島 $ 1,3,2 $ を順に訪れることができ、長さ $ 3 $ のツアーが催行できます。これより短いツアーは存在しません。 よって、封鎖する橋をうまく選んだときのツアーの長さの最小値は $ 2 $ です。 以下の図は左から順に橋 $ 1,2,3 $ を封鎖した場合を表し、数字の書かれた丸が島、丸同士を結ぶ線が橋、青い矢印が最短のツアーの経路を表します。 !\[\](https://img.atcoder.jp/abc338/ad4a27665d9da939ab495acd3d05181a.png)

### Sample Explanation 2

$ X_1,X_2,\dots,X_M $ の中に同じ島が複数回現れることもあります。

## 样例 #1

### 输入

```
3 3
1 3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 5
2 4 2 4 2```

### 输出

```
8```

## 样例 #3

### 输入

```
163054 10
62874 19143 77750 111403 29327 56303 6659 18896 64175 26369```

### 输出

```
390009```

# 题解

## 作者：Running_a_way (赞：13)

[cnblogs](https://www.cnblogs.com/Running-a-way/p/17993522/sol-abc338d)

赛时怎么连这题都不会。再不练练思维真的就连普及题都不会做了啊。
### Solution

题目来源：ABC338D（[in Atcoder](https://atcoder.jp/contests/abc338/tasks/abc338_d) | [in 洛谷](https://www.luogu.com.cn/problem/AT_abc338_d)）。

不妨先考虑应该断掉哪条边。首先我们发现，仅断掉一条边并不会让两个结点不可达，只会让我们从一个结点**绕更远的路**到达目标结点。

如果我们要从结点 $u$ 前往结点 $v$（假设 $u < v$），无非就两条路径（**重复走过某条边无意义**）：沿着 $u$ 走过若干个 $\ge u$ 且 $\le v$ 的结点；从 $u$ 走到 $1$，绕到 $n$ 再走到 $u$。这两条路径经过的边数都很好算。前者为 $(v - u)$ 条，后者为 $[(u - 1) + (n - v) + 1] = (u + n - v)$ 条。

记两路径的边数差为 $r = \left | (v - u) - (u + n - v) \right | = \left | -2u + 2v - n \right |$。我们钦定走边数少的路径，如果断掉该路径上的任意一条边，我们都会绕另一条路，多走 $r$ 条边。所以我们可以认为 **该路径上的边被断掉的代价为 $r$**。那么对于每组路径要求，我们可以直接离线地在环上差分，让该路径上所有边代价整体 $+ r$，再在最后用前缀和求出每条边被断掉的总代价。

最后只需断掉总代价最小的边即可。答案即为 **所走过的最短路径之和** 加上 **最小代价 $r_{\min}$**。

断环为链地实现差分和前缀和即可。实现时注意以下几点：

- 开 `long long`。打擂台取 $\min$ 时上界不要开小。
- 不要混淆边的编号和点的编号。

[code](https://atcoder.jp/contests/abc338/submissions/49747617)

---

## 作者：spfa_ (赞：13)

[[ABC338D] Island Tour](https://www.luogu.com.cn/problem/AT_abc338_d)

[更好的阅读体验？](https://www.cnblogs.com/123wwm/articles/17993556)

### 题意简述

$n$ 个岛形成一个用桥连接的环，拆除一座桥后旅行团的最小路径长。

### 题目分析

设 $v_i$ 为拆除 $(i,i\bmod n+1)$ 之间的桥的答案。接下来依次考虑每两个起点和终点 $x,y$。

$x,y$ 之间可以有两条路径可以走，一条为 $x,x+1,x+2,\dots,y$，一条为 $x,x-1,x-2,\dots,y$，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/52i8uoeb.png)

若选了蓝色路径，那么红色路径的桥均可以拆除，所以 $v_{x-1},v_{x-2},\dots,v_y$ 加上蓝色路径的长度。同理，若选了红色路径，那么蓝色路径的桥均可以拆除，所以 $v_{x},v_{x+1},v_{x+1},\dots,v_{y-1}$ 加上红色路径的长度，这样我们就可以得到拆除每个桥的答案了。

但是这样子做的复杂度太高了，我们可以差分优化，例如我们当前需要再 $[l,r]$ 加上 $x$，那么我们只需在差分数组中 $l$ 处加上 $x$，在 $r$ 处加上 $-x$，最后求前缀和即为原本的答案了，最后统计最小值即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = c == '-' ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = (x<<3)+(x<<1)+(c^48), c = getchar();
    return x*f;
}

inline void write(int x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x/10);
    putchar('0'+x%10);
}

const int N = 2e5+5;
int n, m, ans = 1e18, a[N], c[N];

void add(int l, int r, int k) { c[l] += k, c[r+1] -= k; }

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    for (int i = 1; i < m; ++i) {
        int x = a[i], y = a[i+1];
        if (x > y) swap(x, y);
        int d = y-x;
        add(1, x-1, d);
        add(x, y-1, n-d);
        add(y, n, d);
    }
    for (int i = 1; i <= n; ++i) c[i] += c[i-1], ans = min(ans, c[i]);
    cout << ans;
    return 0;
}
```

---

## 作者：yyrwlj (赞：9)

## 题意简述

有一个环，要按给定的顺序经过环上的一些节点，任选环上的一条边删除，最少需要经过几条边走完。

## 思路

先考虑如果不用删边，最短的路径应该怎么求。

一个点到下一个点，要么顺时针走，要么逆时针走，统计两者的较小值即可。

我们不去想删除一条边后的路径该怎么求，而要去想删哪条边的代价最小。

我们假设不删边时，顺时针走总是比逆时针走更优。

那么我们如果改成走逆时针，那么就会多出这两者之差的代价。

我们删掉顺时针走的路径上的任意一条边，都会导致我们只能转而去走逆时针。

显而易见的，我们可以使用差分，将更优的路径上的所有边都加上两个选择的差。

最后被加的数最小的边就是最优解，答案就是不删边的答案加上那条边被加的数。

## Code

```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int N = 200005;
typedef long long LL;
int x[N], d1[N], d2[N];
LL d[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i=1;i<=m;i++)
        scanf("%d", &x[i]);
    LL ans = 0;
    for (int i=1;i<m;i++)
    {
        d1[i] = x[i + 1] - x[i];
        if (d1[i] <= 0)
            d1[i] += n;
        d2[i] = x[i] - x[i + 1];
        if (d2[i] <= 0)
            d2[i] += n;
        ans += min(d1[i], d2[i]);
        const int tmp = abs(d1[i] - d2[i]);
        if (d1[i] < d2[i])
        {
            d[x[i]] += tmp;
            if (x[i] < x[i + 1])
                d[x[i + 1]] -= tmp;
            else
            {
                d[1] += tmp;
                d[x[i + 1]] -= tmp;
            }
        }
        else if (d1[i] > d2[i])
        {
            d[x[i + 1]] += tmp;
            if (x[i + 1] < x[i])
                d[x[i]] -= tmp;
            else
            {
                d[1] += tmp;
                d[x[i]] -= tmp;
            }
        }
    }
    for (int i=2;i<=n;i++)
        d[i] += d[i - 1];
    LL mn = 9e18;
    for (int i=1;i<=n;i++)
        mn = min(mn, d[i]);
    cout << ans + mn;
    return 0;
}
```

---

## 作者：__Dist__ (赞：3)

### 题目大意

给定一张 $n$ 个点的无向图，第 $i$ 个点和第 $i \bmod n + 1$ 个点之间有一条边。

现在要断掉一条边，然后按照给定顺序遍历全部点，求最小代价。

### 思路讲解

设 $v_i$ 为断掉第 $i$ 座桥之后所花费的代价。

考虑从 $a$ 城市到 $b$ 城市的代价。有两种情况：

1. 走 $a,a+1,a+2,\cdots,b$，代价为 $b-a$；

2. 走 $a,a-1,a-2,\cdots,b$，代价为 $n+a-b$。

如果断掉的桥在 $1$ 号路线上，我们只能走 $2$ 号路线；反之只能走 $1$ 号路线。我们显然可以通过 $m-1$ 次暴力操作求出 $v_i$，总复杂度 $\Theta (nm)$，但是数据范围太大，不可行。

考虑优化。我们不难发现，我们每次对一段的区间的加法操作总是一段连续区间（因为 $1$ 和 $n$ 之间也有一条边），而且加的数还是定值，显然可以差分。直接套差分板子，最后求一遍前缀和，答案即为 $\min_{i=1}^{n}v_i$。

### 代码环节

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n, m;
int x[MAXN];
long long v[MAXN];
long long ans = LONG_LONG_MAX;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m ;i++) {
		scanf("%d", &x[i]);
	}
	auto dist = [&] (int from, int to) {
		if(from <= to) return to - from;
		else return n + to - from;
	};
	auto add = [&] (int from, int to, int num) {
		if(from <= to) {
			v[from + 1] += num;
			v[to + 1] -= num;
		}
		else {
			v[from + 1] += num;
			v[n + 1] -= num;
			v[1] += num;
			v[to + 1] -= num;
		}
	};
	for (int i = 1; i < m; i++) {
		add(x[i], x[i + 1], dist(x[i + 1], x[i]));
		add(x[i + 1], x[i], dist(x[i], x[i + 1]));
	}
	for (int i = 1; i <= n; i++) {
		v[i] += v[i - 1];
		ans = min(ans, v[i]);
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：fcy20180201 (赞：3)

## 思路
首先直接暴力是 $\mathcal O(NM)$ 的，肯定 TLE。

所以可以考虑变化量，我们一开始拆掉 $1$ 和 $N$ 之间的路。设两个要连续去的地方为 $x_{i-1}$ 和 $x_i$，则此时这两个地方之间的距离一定是 $|x_i-x_{i-1}|$。

当我们把拆掉的路移到 $1$ 和 $2$ 之间时，$x_i$ 或 $x_{i-1}$ 为 $1$ 时，两点之间要通过 $1$ 和 $N$ 之间的路才能到达，即距离为 $n-|x_i-x_{i-1}|$。当拆了 $2$ 和 $3$ 之间的路时，我们发现 $1$ 和 $2$ 之间的距离又变成了 $|1-2|$。

以此类推，我们发现，对于 $x_i$ 和 $x_{i-1}$，我们钦定 $x_i \gt x_{i-1}$，则当拆了 $1$ 和 $N$ 之间的路是，它们之间的距离是 $x_i-x_{i-1}$。当拆的路变成 $x_{i-1}$ 和 $x_{i-1}+1$ 之间的时，它们之间的距离变成 $n-(x_i-x_{i-1})$；当拆的路变成 $x_i$ 和 $x_i+1$ 之间的时，距离又变回去了。

因此我们将变化的位置放进 vector 里，然后枚举拆掉的路，每次把当前的答案取最小值，然后加上 vector 里的变化量，得到下一个答案。时间复杂度 $\mathcal O(N)$。

## 代码
代码中 $a$ 就是 $x$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m,a[200005],fst[200005],scd[200005];
vector<int>cg[200005],cg2[200005];
ll cnt,ans=1e18;//不开 long long 见祖宗
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
		if(i>1){
			int x=a[i-1],y=a[i];
			if(x>y)swap(x,y);//钦定 a_i>a_i-1
			fst[i]=y-x,scd[i]=n-fst[i];//两种距离
			cnt+=fst[i];//一开始是第一种
			cg[x].push_back(i),cg2[y].push_back(i);
			//记录变化位置
		}
	}
	for(int i=1;i<=n;i++){
		ans=min(ans,cnt);
		for(int j:cg[i])cnt=cnt-fst[j]+scd[j];
		for(int j:cg2[i])cnt=cnt-scd[j]+fst[j];
		//加上变化量
	}
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：Shunpower (赞：3)

线段树弱智做法。

考虑先算出来不断边的最短路，可以发现由于始终在环上走，那么从一个点走到另一个点无非只有两条路径，选择较短一条走就行了。

考虑断边。发现影响是所有经过这条边的路径都只能走另一半边。于是维护两件事：走过一条边的次数 $c_i$，走过这条边的那些路径的长度和 $s_i$。那么断掉一条边，首先要清掉走这条边的那些路径，也就是答案减掉 $s_i$，再加上走另一半边的贡献，也就是 $(n-s_i)\times c_i$。

枚举断边更新答案即可。

维护 $c_i,s_i$ 并在枚举断边时计算新答案等价于区间加、单点询问操作，使用差分、树状数组、线段树均可解决本题。我用了最唐的线段树，怎么会是呢？

[我的代码](https://atcoder.jp/contests/abc338/submissions/49734188)。

---

## 作者：CQ_Bob (赞：3)

## 分析

考虑删掉每条边后的最短路增长量。

对于 $x_{i-1}$ 到 $x_{i}$ 的最短路，在不删边的情况下有两种：

1. 直接从 $\min(x_{i-1},x_i)$ 到 $\max(x_{i-1},x_i)$。

2. 从 $\max(x_{i-1},x_i)$ 顺时针经过点 $1$ 走到 $\min(x_{i-1},x_i)$。

对于第一种，删掉某条边会影响它的最短路的边为点 $x_{i-1}$ 与点 $x_i$ 之间的边。且都会使最短路增长 $n-2\times(\max(x_{i-1},x_i)-\min(x_{i-1},x_i))$。

对于第二种，删掉某条边会影响它的最短路的边为点 $1$ 与 $\min(x_{i-1},x_i)$ 之间的边和点 $\max(x_{i-1},x_i)$ 与点 $1$ 之间的边。且都会使最短路增长 $2 \times (\max(x_{i-1},x_i)-\min(x_{i-1},x_i))-n$。

然后随便用个什么东西维护就行。可以做到 $O(n)$ 复杂度。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}

const int N=4e5+10;
int n,m,x[N];
int Min[N];
vector<int> in[N],out[N];
int ans;

il void solve(){
	n=read(),m=read();
	for(re int i=1;i<=m;++i) x[i]=read();
	for(re int i=2;i<=m;++i){
		if(x[i]>x[i-1]){
			Min[i]=min(x[i]-x[i-1],x[i-1]+n-x[i]);	
			if(Min[i]==x[i]-x[i-1]){
				in[x[i-1]].push_back(i);
				out[x[i]].push_back(i);
			}
			else{
				if(x[i-1]>1) in[1].push_back(i),out[x[i-1]].push_back(i);
				in[x[i]].push_back(i);
			}
		}
		else{
			Min[i]=min(x[i]+n-x[i-1],x[i-1]-x[i]);	
			if(Min[i]==x[i-1]-x[i]){
				in[x[i]].push_back(i);
				out[x[i-1]].push_back(i);
			}
			else{
				if(x[i]>1) in[1].push_back(i),out[x[i]].push_back(i);
				in[x[i-1]].push_back(i);
			}
		}
		ans+=Min[i];
	}
	int minn=1e18,now=0;
	for(re int i=1;i<=n;++i){
		for(re int j=0;j<out[i].size();++j) now-=n-2*Min[out[i][j]];
		for(re int j=0;j<in[i].size();++j) now+=n-2*Min[in[i][j]];
		minn=min(minn,now);
	}
	printf("%lld\n",ans+minn);
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：2huk (赞：2)

### Problem Statement

The AtCoder Archipelago consists of $N$ islands connected by $N$ bridges. The islands are numbered from $1$ to $N$, and the $i$\-th bridge ($1\leq i\leq N-1$) connects islands $i$ and $i+1$ bidirectionally, while the $N$\-th bridge connects islands $N$ and $1$ bidirectionally. There is no way to travel between islands other than crossing the bridges.

On the islands, a **tour** that starts from island $X_1$ and visits islands $X_2, X_3, \dots, X_M$ in order is regularly conducted. The tour may pass through islands other than those being visited, and the total number of times bridges are crossed during the tour is defined as the **length** of the tour.

More precisely, a **tour** is a sequence of $l+1$ islands $a_0, a_1, \dots, a_l$ that satisfies all the following conditions, and its **length** is defined as $l$:

-   For all $j\ (0\leq j\leq l-1)$, islands $a_j$ and $a_{j+1}$ are directly connected by a bridge.
-   There are some $0 = y_1 < y_2 < \dots < y_M = l$ such that for all $k\ (1\leq k\leq M)$, $a_{y_k} = X_k$.

Due to financial difficulties, the islands will close one bridge to reduce maintenance costs. Determine the minimum possible length of the tour when the bridge to be closed is chosen optimally.

### Solution

我们令 $v_i$ 表示在第 $i$ 座桥爆炸时，完成旅行的最短路程。我们希望在线性或线性对数的复杂度下求出所有的 $v_i$，那么 $\min v_i$ 即为答案。

可以发现，在整个旅程 $x_1 \to x_2 \to \dots \to x_m$ 中，我们可以把它看成若干个小旅途 $x_1 \to x_2, x_2 \to x_2, \dots, x_{m - 1} \to x_m$，因为它们之间是相互独立的。

那么最终 $v_i = \sum v_i'$，表示每个小旅程的长度之和。

因此考虑对于一个小旅程 $x_j \to x_{j + 1}$。如果不爆炸的话会有两条路径，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/lwcnlejd.png)

在 $x_j = 2$，$x_{j + 1} = $4 时，有两条路径：

- $S_1$：$2 \to 1 \to 5 \to 4$，长度为 $4$；
- $S_2$：$2 \to 3 \to 4$，长度为 $3$。

那么如果把 $2 \to 1$ 或 $1 \to 5$ 或 $5 \to 4$ 炸了，这个小旅程的长度为 $3$。剩下的情况，如果把 $2 \to 3$ 或 $3 \to 4$ 炸了，这个小旅程的长度为 $4$。

也就是 $v_1' = v_4' = v_5' = 3$，$v_2' = v_3' = 4$。

那么如果暴力计算每个小旅程和每个爆炸的桥，时间复杂度是不优的。可以发现每次修改 $v$ 都是连续的一段，所以可以在差分数组上单点修改，最后求差分数组的前缀和即可。

### Code

注意区间修改时可能会出现 $\dots, v_{n - 1}, v_n, v_1, v_2, \dots$ 的情况。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m, a[N];
long long s[N];

int dis(int l, int r) {
	if (l <= r) return r - l;
	return r - l + n;
}

void add(int l, int r, int d) {
	if (l <= r) {
		s[l] += d;
		s[r] -= d;
	}
	else {
		s[l] += d;
		s[n + 1] -= d;
		s[0] += d;
		s[r] -= d;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i ) cin >> a[i];
	
	for (int i = 1; i < m; ++ i )
		add(a[i], a[i + 1], dis(a[i + 1], a[i])),
		add(a[i + 1], a[i], dis(a[i], a[i + 1]));
	
	long long res = 1e18;
	for (int i = 1; i <= n; ++ i )
		res = min(res, s[i] += s[i - 1]);
	cout << res;
	
	return 0;
}
```

---

## 作者：mango2011 (赞：1)

既然题目让我们考虑断掉某一座桥之后，总的长度最小，那也可以认为是求断掉某一座桥影响最小。

于是我们记录原本的最短路径 $W$，考虑断掉某一座桥对总路程造成的影响：

我们从每一条条路的角度出发，搬出我们的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/c1l4zz5d.png)

如图，如果我们想要从 $A$ 到达 $F$，那么有两条路可以走：

$A\to H\to G\to F$ 或 $A\to B\to C\to D\to E\to F$，两种路径的长度分别是 $3$ 和 $5$。所以，如果 $AB,BC,CD,DE,EF$ 中的某一座桥断掉了，对这条路径是没有影响的；但是，如果 $AH,HG,GF$ 中的某一座桥断掉了，就需要多花费 $5-3=2$ 的长度。有了这一个分析，我们就得到了：

从 $u$ 到 $v$（由于路径无向，所以不妨设 $u<v$）：

记 $S_1=v-u+1$，$S_2=n-S_1$，若 $S_1>S_2$，则 $(v,v+1),(v+1,v+2),...,(n-1,n),(n,1),(1,2),(2,3),...,(u-1,u)$ 这些桥的权值全部要加上 $S_1-S_2$；若 $S_1=S_2$，则没有变化；若 $S_1<S_2$，则 $(x,x+1),(x+1,x+2),(x+2,x+3),...,(y-1,y)$ 这些桥的权值全部要加上 $S_2-S_1$。$W$ 也要加上 $\min\{S_1,S_2\}$。

于是，就想到了用线段树维护。

最后，我们以原本的最短路径 $W$ 为基准，找到影响最小的值 $W_1$，得到的 $W+W_1$ 就是所求答案。

具体实现其实一点也不复杂，~~所以代码这种想必大家也不稀罕了~~，场上五分钟就写完了（真的很简单）。

---

## 作者：cjh20090318 (赞：1)

被降智的一道简单题。

## 题意

$n$ 个岛屿，第 $i$ 座桥连接 $i$ 和 $i+1$（第 $N$ 座桥连接着 $1$ 和 $N$）。

有一条长度为 $M$ 的旅游序列 $X$，你需要按照顺序依次经过这些点，选择断掉一座桥使得旅游经过的桥最少。

## 分析

设断掉第 $i$ 座桥会因为绕行增加旅行长度的值为 $s_i$。

从 $p$ 点到 $q$ 点的最短距离是 $\min(\vert p-q \vert , n - \vert p - q \vert )$，那么分类讨论。

不妨设 $p<q$。

设多绕行的距离为 $d = \left\vert n - 2(q - p) \right\vert$。

分类讨论三种情况。

### 当 $q-p < n-(q-p)$ 时

如果断掉了 $p \sim q-1$ 之间任意一座桥，总的旅程就会增加 $d$，所以 $\forall i \in [p,q), s_i \gets s_i+d$。

### 当 $q-p > n-(q-p)$ 时

如果断掉了 $1 \sim p-1$ 或 $q \sim n$ 之间任意一座桥，总的旅程就会增加 $d$，所以 $\forall i \in [1,p) \cup [q,n], s_i \gets s_i+d$。

### 当 $q-p = n-(q-p)$ 时

无论怎么走路程都是一样的，所以不处理。

然后这就是一个区间修改单点查询的问题，~~可以使用线段树~~，但是因为只在最后查询，所以可以使用差分。

线段树修改查询为 $O(n \log n)$，差分修改查询为 $O(n)$。

## 代码

### ~~赛时的~~线段树做法

```cpp
//the code is from chenjh
#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAXN 200002
using namespace std;
typedef long long LL;
int n,m;
int x[MAXN];
LL mn[MAXN<<2],lazy[MAXN<<2];//线段树区间修改维护最小值。
#define lson (rt<<1)
#define rson (rt<<1|1)
using ci=const int;
void pd(ci rt,ci l,ci r){
	mn[lson]+=lazy[rt],lazy[lson]+=lazy[rt];
	mn[rson]+=lazy[rt],lazy[rson]+=lazy[rt];
	lazy[rt]=0;
}
void update(ci rt,ci l,ci r,ci L,ci R,ci val){
	if(L<=l && r<=R){mn[rt]+=val,lazy[rt]+=val;return;}
	pd(rt,l,r);
	int mid=(l+r)>>1;
	if(L<=mid) update(lson,l,mid,L,R,val);
	if(mid<R) update(rson,mid+1,r,L,R,val);
	mn[rt]=min(mn[lson],mn[rson]);
}
LL query(ci rt,ci l,ci r,ci L,ci R){
	if(L<=l && r<=R) return mn[rt];
	pd(rt,l,r);
	int mid=(l+r)>>1;
	LL ret=0x3f3f3f3f3f3f3f3fll;
	if(L<=mid) ret=min(ret,query(lson,l,mid,L,R));
	if(mid<R) ret=min(ret,query(rson,mid+1,r,L,R));
	return ret;
}
int main(){
	cin>>n>>m;
	LL ans=0;
	for(int i=1;i<=m;i++) cin>>x[i];
	for(int i=2;i<=m;i++) ans+=min(abs(x[i]-x[i-1]),n-abs(x[i]-x[i-1]));//不断桥的最小距离。
	for(int i=2;i<=m;i++){
		int p=x[i-1],q=x[i];
		if(p>q) swap(p,q);
		if(((q-p)<<1)<n) update(1,1,n,p,q-1,n-((q-p)<<1));
		else if(((q-p)<<1)>n){
			if(p>1) update(1,1,n,1,p-1,((q-p)<<1)-n);
			update(1,1,n,q,n,((q-p)<<1)-n);
		}//线段树修改。
	}
	LL mn=0x3f3f3f3f3f3f3f3fll;
	for(int i=1;i<=n;i++) mn=min(mn,query(1,1,n,i,i));//线段树单点查询。
	printf("%lld\n",ans+mn);
	return 0;
}
```


### ~~复杂度更优秀的~~差分做法

```cpp
//the code is from chenjh
#include<cstdio>
#include<algorithm>
#define MAXN 200002
using namespace std;
typedef long long LL;
int n,m;
int x[MAXN];
LL s[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	LL ans=0;
	for(int i=1;i<=m;i++) scanf("%d",&x[i]);
	for(int i=2;i<=m;i++){
		int p=x[i-1],q=x[i];
		if(p>q) swap(p,q);
		ans+=min(q-p,n-q+p);//不断桥的最小距离。
		if(((q-p)<<1)<n) s[p]+=n-((q-p)<<1),s[q]-=n-((q-p)<<1);
		else if(((q-p)<<1)>n){
			s[1]+=((q-p)<<1)-n,s[p]-=((q-p)<<1)-n;
			s[q]+=((q-p)<<1)-n;
		}//差分修改。
	}
	LL mn=0x3f3f3f3f3f3f3f3fll;
	for(int i=1;i<=n;i++) mn=min(mn,s[i]+=s[i-1]);//差分还原的同时取增加的最小值。
	printf("%lld\n",ans+mn);
	return 0;
}
```

---

## 作者：CodingOIer (赞：1)

## [ABC338D] Island Tour 题解

### 思路分析

考虑枚举每一对相邻的路径中的点，计算对答案的贡献。

考虑下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/3bfrvb1o.png)

显而易见，断开 $a$ 中的任意点的贡献为 $b$ 的长度，$b$ 亦然。

考虑使用线段树维护区间最小值，需要用到边权转点权，本文使边 $x$ 到 $x + 1$ 边的权值放在 $x$ 上。

写出修改代码。

```cpp
void change(int l, int r, long long val)
{
    if (l <= r)
    {
        tree_change(1, 1, n, l, r - 1, val);
    }
    else
    {
        tree_change(1, 1, n, l, n, val);
        tree_change(1, 1, n, 1, r - 1, val);
    }
}
```

请读者自行思考 `if` 语句的含义。

### 代码实现

Tips: 本题的答案可能不适用于 $32$ 位有符号整数。

```cpp
/**
 * @file AtCoder\ABC338\D.cpp
 * @author CodingOIer (redefinition0726@163.com)
 * @brief AtCoder
 * @version 1.0
 * @date 2024-01-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, m;
int p[MaxN];
long long tree[MaxN * 4];
long long lazy[MaxN * 4];
void downstream(int cur, int s, int t)
{
    if (lazy[cur] != 0)
    {
        tree[cur * 2] += lazy[cur];
        tree[cur * 2 + 1] += lazy[cur];
        lazy[cur * 2] += lazy[cur];
        lazy[cur * 2 + 1] += lazy[cur];
        lazy[cur] = 0;
    }
}
void tree_change(int cur, int s, int t, int l, int r, long long val)
{
    if (l > r)
    {
        return;
    }
    if (l <= s && t <= r)
    {
        tree[cur] += val;
        lazy[cur] += val;
        return;
    }
    downstream(cur, s, t);
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        tree_change(cur * 2, s, mid, l, r, val);
    }
    if (r > mid)
    {
        tree_change(cur * 2 + 1, mid + 1, t, l, r, val);
    }
    tree[cur] = std::min(tree[cur * 2], tree[cur * 2 + 1]);
}
long long query(int cur, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return tree[cur];
    }
    downstream(cur, s, t);
    int mid = (s + t) / 2;
    long long res = 0x3f3f3f3f3f3f3f3f;
    if (l <= mid)
    {
        res = std::min(res, query(cur * 2, s, mid, l, r));
    }
    if (r > mid)
    {
        res = std::min(res, query(cur * 2 + 1, mid + 1, t, l, r));
    }
    return res;
}
void change(int l, int r, long long val)
{
    if (l <= r)
    {
        tree_change(1, 1, n, l, r - 1, val);
    }
    else
    {
        tree_change(1, 1, n, l, n, val);
        tree_change(1, 1, n, 1, r - 1, val);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 2; i <= m; i++)
    {
        int x, y;
        x = p[i - 1];
        y = p[i];
        if (x > y)
        {
            std::swap(x, y);
        }
        change(y, x, y - x);
        change(x, y, n - (y - x));
    }
    printf("%lld\n", query(1, 1, n, 1, n));
    return 0;
}
```

---

## 作者：WilliamFranklin (赞：1)

### 主要思路

遇到这种题，我们首先就是要考虑，如果删掉某一条边，那么代价是多少。只要解决了这个问题，那么整个问题就基本完成了。那么下面，我将着重来讲解如何解决这个问题的。

我们可以从最简单的情况入手。假如说这个旅游线就只有两个点，我们如果删掉这两个点之间最短路径上一条边，那么，这个条边带来的代价是多少？

我们举一个例子：如图，旅游线为 $1$ 到 $3$，此时删掉 $2$ 与 $3$ 之间的这条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/re7moqaq.png)

我们发现，原本，最短距离为 $2$，但现在最短距离为 $3$，其实就是 $5 - 2$，这条边带来的代价就是 $5 - 2 - 2$，为 $1$。那么我们就可以由它推向所有旅游线上就只有两个点的情况：如果删掉这两个点之间最短路径上一条边，原本的最短距离为 $x$，那么此时这条边带来的代价就是 $n - x - x$，即 $n - 2x$，同样，如果删掉 $1$ 与 $2$ 之间这条边，带来的代价也是一样，那么我们就可以将这两点间的边都加上这个代价，这就变成了一个类似区间加的问题。

然后我们又可以由此推向旅游线不止两个点的情况。我们可以将旅游线看作一个个只有两个点的旅游线拼凑起来的，所以整个问题就迎刃而解了。

有些地方说的不是很详细，具体看代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2e5 + 5;
int x[N];
long long tr[N];
long long tr1[N];
int n, m;
int lowbit(int x) {
	return x & -x;
}
void add(int x, long long y ) {
	for (int i = x; i <= n; i += lowbit(i)) tr[i] += y, tr1[i] += (y > 0 ? 1 : -1);
}
long long summ(int x) {
	long long res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tr[i];
	return res; 
}
long long sum1(int x) {
	long long res = 0;
	for (int i = x; i; i -= lowbit(i)) res += tr1[i];
	return res; 
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x[i];
	}
	long long sum = 0;
	for (int i = 2; i <= m; i++) {
		long long a = abs(x[i] - x[i - 1]);
		long long c = n - x[i] + x[i - 1];
		long long b = x[i] + n - x[i - 1];
		if (a < b && a < c) {
			sum += a;
			add(min(x[i], x[i - 1]), a);
			add(max(x[i], x[i - 1]), -a);
		} else if (b < a && b < c) {
			sum += b;
			add(x[i - 1], b);
			add(1, b);
			add(x[i], -b);
		} else if (c < b && c < a) {
			sum += c;
			add(1, c);
			add(x[i - 1], -c);
			add(x[i], c);
		} else {
			sum += a;
		}
		//cout << a << ' ' << b << ' ' << c << '\n';
	}
	long long minn = 1e18;
	for (int i = 1; i <= n; i++) {
		long long x = summ(i), y = sum1(i);
		//cout << x << ' ' << y << '\n';
		minn = min(minn, sum - x + y * n - x);
	}
	cout << minn;
	return 0;
} 
```

### 谢谢观看

---

## 作者：cppcppcpp3 (赞：0)

[AtCoder Link](https://atcoder.jp/contests/abc338/tasks/abc338_d)

考虑计算出所有删边方案的最短路径长度，再取 $\min$ 就是最后的答案。

记第 $i(i<n)$ 条边表示边 $(i,i+1)$，第 $n$ 条边为 $(1,n)$。考虑 $u,v(u<v)$ 两点距离的两种情况：

- 删掉的边属于区间 $[u,v-1]$，$n-|u-v|$。

- 否则 $|u-v|$。

那么 $(X_i,X_{i+1})$，对边 $[\min(X_i,X_{i+1}),\max(X_i,X_{i+1})-1]$ 的贡献为 $n-|X_i-X_{i+1}|$，对其它边的贡献为 $|X_i-X_{i+1}|$。这就是区间加，线段树维护或直接差分即可。

实现写得不太一样，先计算了删 $(1,n)$ 的答案 $t$，上面的 $n-|X_i-X_{i+1}|$ 相对于 $t$ 就是加上 $n-2|X_i-X_{i+1}|$。

时间复杂度 $O(n\log n)$，用差分可做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,a[N],as;
int s[N<<2],lz[N<<2];

#define ls (t<<1)
#define rs (t<<1|1)
#define md ((l+r)>>1)

void pushup(int t){
	s[t]=s[ls]+s[rs];
}

void pd(int l,int r,int t){
	if(!lz[t]) return;
	s[ls]+=(md-l+1)*lz[t],s[rs]+=(r-md)*lz[t];
	lz[ls]+=lz[t],lz[rs]+=lz[t];
	lz[t]=0;
}

void upd(int l,int r,int t,int x,int y,int k){
	if(l>y || r<x) return;
	if(l>=x&&r<=y){
		s[t]+=(r-l+1)*k,lz[t]+=k;
		return;
	}
	pd(l,r,t);
	upd(l,md,ls,x,y,k),upd(md+1,r,rs,x,y,k);
	pushup(t);
}

int qry(int l,int r,int t,int x){
	if(l==r) return s[t];
	pd(l,r,t);
	return x<=md ? qry(l,md,ls,x) : qry(md+1,r,rs,x);
}

int dis(int i,int j){
	return abs(i-j);
}

signed main(){
	cin >> n >> m;
	for(int i=1;i<=m;++i) cin >> a[i];
	for(int i=1;i<m;++i) as+=dis(a[i+1],a[i]);
	for(int i=1;i<m;++i){
		int u=min(a[i+1],a[i]),v=max(a[i+1],a[i]);
		upd(1,n,1,u,v-1,n-2*dis(a[i+1],a[i]));
	}
	int tt=as;
	for(int i=1;i<n;++i) as=min(as,tt+qry(1,n,1,i));
	return printf("%lld",as),0;
}
```

---

## 作者：xz001 (赞：0)

我们先扫一遍旅游路线，我们知道若没有删除一条路，那么从一个点走向另一个点有两条路，一条短一条长，我们肯定是选择更短的，因此更短的路上的任何一条边被删除，都会使得旅程长度增加较长路长度减去较短路长度，因为路线下标是连续的，所以直接用差分数组维护每条路被删后会增加的旅程长度，然后我们求删除后增加的旅程长度最短的路，删除然后统计行程长度即可。

代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, mod = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, m, x[N], d[N], at, minn = 1e18, ans;

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++ i) scanf("%lld", x + i);
    for (int i = 1; i < m; ++ i) {
    	int l = x[i], r = x[i + 1], cnt;
    	if (l > r) swap(l, r);
    	cnt = min(r - l, n - r + l);
    	if (cnt == r - l) {
    		d[l] -= (r - l) - (n - r + l);
    		d[r] += (r - l) - (n - r + l);
		} else {
			d[1] -= (n - r + l) - (r - l);
			d[l] += (n - r + l) - (r - l);
			d[r] -= (n - r + l) - (r - l);
		}
	}
	for (int i = 1; i <= n; ++ i) d[i] += d[i - 1];
	for (int i = 1; i <= n; ++ i) {
		if (d[i] < minn) {
			minn = d[i];
			at = i;
		}
	}
	for (int i = 1; i < m; ++ i) {
		int l = x[i], r = x[i + 1];
		if (l > r) swap(l, r);
		if (at >= l && at < r) ans += n - r + l;
		else ans += r - l;
	}
	printf("%lld\n", ans);
    return 0;
}


````

---

## 作者：Loser_Syx (赞：0)

因为它原图是一个长度为 $n$ 的大环，故 $i \rightarrow j$ 的路径只有 $2$ 条是可接受的，分别为经过 $(n,1)$ 这个边和不经过来讨论。

初始时我们默认选择上述边中较短的那条边，因为是一个大环，所以这两条路径一定是包含了所有的 $n$ 条边，如果我们在 $x_i \rightarrow x_{i+1}$ 路径较短的路径上删除任意一条边的话，就会导致 $len_{\text{长}}-len_{\text{短}}$ 的影响，但是由于题中图的特殊性，所影响的边一定是一段连续的区间，或是 $b \rightarrow n$，$n \rightarrow 1$，最后 $1 \rightarrow a$ 的这个路径。

无论是上述哪种情况，我们都可以差分解决，最后在计算前缀和后找出影响最小的边即可。复杂度 $O(n)$。

```cpp
int q[201010];
signed main() {
	int n=read(),m=read();
	int lst=read(),ans=0;
	for (int i=2,x;i<=m;++i) {
		read(x);
		int a=lst,b=x;
		if (a>b) swap(a,b);
		int c=a+n;
		if (b-a<c-b) {
			int cha=(c-b)-(b-a);
			ans+=b-a;
			q[a]+=cha;
			q[b]-=cha;
		} else {
			int cha=(b-a)-(c-b);
			ans+=c-b;
			q[b]+=cha; q[n+1]-=cha;
			q[1]+=cha; q[a]-=cha;
		}
		lst=x;
	}
	int mn=1e18;
	for (int i=1;i<=n;++i) {
		//cout<<q[i]<<' ';
		q[i]+=q[i-1];
		mn=min(mn, q[i]);
	}
	write(ans+mn,'\n');
	return 0;
} 
```

---

## 作者：KSCD_ (赞：0)

# 题意
$n$ 个点顺序连接的环，边长为 $1$，去掉其中一条边，使顺序访问 $m$ 个点的路程最短，求最短路程。
# 思路
暴力求解复杂度必炸，
考虑优化。

显然可以把**计算每条路径**转化成**记录每条路径的贡献**。

------------
## 1.路径计算
若求两点 $l,r$ 间距离，可以先令 $r \gt l$，方便处理。

我们发现在环上从 $r$ 走到 $l$ 只有两种路径，

且断掉一条边以后为一条链，即只有唯一的路径，

那么我们就可以先求出两种路径分别的长度：

- 其中直接从 $1$ - $n$ 内部走（即 $l,l+1 \cdots r-1,r$）的路程即 $(r-l)$

- 而另一种为经过 $n$ 和 $1$ 连接的这条边（即 $r,r+1 \cdots 1,2 \cdots l-1,l$）

通过分析可知两种的路径长度和为环的总长度 $n$

则第二种的路径长为 $(n-(r-l))$
## 2.记录求解
因为最终要求的是 $(m-1)$ 段路程的和最小，

考虑把每一段路程分别计算，最后再一起求和。

设 $a_i$ 表示断掉连接 $i$ 和 $i+1$ 之间这条边后的总路程，

$a_n$ 即为断开 $n$ 和 $n-1$ 之间边时的总路程，

注意到 $l$ 和 $r$ 将 $a$ 数组分成三部分，

第一部分是 $1$ 至 $l-1$ ，贡献为第一种；

第二部分是 $l$ 至 $r-1$ ，贡献为第二种；

第三部分是 $r$ 至 $n$ ，贡献仍为第一种。

特别地，当 $l=1$ 时，第一部分不存在，需要特殊处理。

因此这三部分的区间加操作可以使用差分数组 $s$ 记录。

最后用前缀和恢复 $a$ 数组，输出最小值即可。

具体看代码实现吧。

# 代码
[我的赛时代码](https://atcoder.jp/contests/abc338/submissions/49723789)~~（写得有点啰嗦）~~

以下是我重写的~~对新手友好的~~代码。
```cpp
#include<iostream>
using namespace std;
const int N=2e5+10;
int n,m,x[N];
long long ans=1e18,s[N];//初始化，记得开longlong 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>x[i];
	for(int i=1;i<m;i++)//处理(m-1)段距离的贡献
	{
		int l=x[i];
		int r=x[i+1];
		if(l>r) 
			swap(l,r);//使r>l 
		int sn=r-l;//第一种的距离
		int sw=n-sn;//第二种的距离
		if(l==1)
			s[l]+=sw;//s[l]即s[1]，断掉1和2之间的边时只能先到n，即第二种
		else
		{
			s[1]+=sn;
			s[l]+=(sw-sn);
		}
		s[r]+=(sn-sw);
	}
	for(int i=1;i<=n;i++)
	{
		s[i]+=s[i-1];
		ans=min(ans,s[i]);
	}//求前缀和及最小值答案 
	cout<<ans;
	return 0;
} 
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题意
给你一个有 $n$ 个点的环，点的编号为 $1$ 到 $n$，一段路径序列 $X_1,X_2,X_3...X_m$ 表示从 $X_1$ 走到 $X_2$ 到 $X_3$ 一直到 $X_m$，现在去掉一条边，问走完路径经过的边的数量最小是多少？

## 题解
差分。

不难发现一个点到另一个点的路径一开始有两种，设起始点为 $X_a$，终点为 $X_b$
其路径长度为 $n-|X_a-X_b|$ 或 $|X_a-X_b|$。

当我们将边断在 $X_a,X_b$ 之间，长度为 $n-|X_a-X_b|$，不在该区间同理为 $|X_a-X_b|$。

一开始默认为路径长度为 $|X_a-X_b|$，求出总和，考虑差分，其含义指在 $X_a$ 到 $X_b$ 断边所路径增加或减少的值，即 $|n-2|X_a-X_b||$，求出枚举取和时的最小值再与先前总和相加就是答案。

详细看实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[500005],cnt,ans,sum[500005],res=1e18;
int main()
{
    long long n,m;
    cin>>n>>m;
    for(long long i=1;i<=m;i++)cin>>a[i];
    for(long long i=2;i<=m;i++)
    {
        ans+=abs(a[i]-a[i-1]);
        sum[min(a[i-1],a[i])]+=(abs(n-abs(a[i]-a[i-1]))-abs(a[i]-a[i-1]));//差分
        sum[max(a[i-1],a[i])]+=-(abs(n-abs(a[i]-a[i-1]))-abs(a[i]-a[i-1]));//差分
    }
    long long tmp=0;
    for(long long i=1;i<=n;i++)
    {
        tmp+=sum[i];//求和
        res=min(ans+tmp,res);//取最小
    }
    cout<<res;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定一个长为 $n$ 环以及 $m$ 个点的遍历顺序。问当有一条边不能通行时，遍历 $m$ 个点时最短路径的长度。起点可以为环上任意一点且边的长均为 $1$。
# 思路
思考一下，如果在遍历过程中，有点 $m_i,m_{i+1}(1\le i\le m-1)$ 它们经过边 $edge_i$，设原本环上 $m_i,m_{i+1}$ 间最短路径长为 $x$，那么此时若 $edge_i$ 不能通行则最短径长为 $n-x$，也就是 $edge_i$ 的不能通行单单对于 $m_i,m_{i+1}$ 两点间的遍历就增加了 $n-2\times x$ 的总路径长度。

易得，对于每一个 $m_i,m_{i+1}(1\le i\le m-1)$ 路径上的边，如果其不能通行，就会使最终的总路径长度增多 $n-2\times x$。

所以，不妨对于遍历中的每相邻两点最短路径上的边增加 $n-2\times x$，最后遍历环上择其对答案贡献最小者加上原本的遍历最短路径长，即为答案。

这里 $n\le10^5$，如果直接对需要加值的区间里的边加值是不现实的，这里使用了环上差分，具体的细节请看代码。
# 实现
```cpp
#include<bits/stdc++.h>
#define lb(x) (-x&x)
using namespace std;
long long n,m,ans,a[200005],cf[200005];
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld",&a[i]);//读入须遍历点
		if(i>1){//如果可以遍历
			long long l=min(a[i],a[i-1]),r=max(a[i],a[i-1]);//分出需要加值的区间的左右边界
			long long dis=r-l;//不经过点n的距离
			if(dis<=n-dis){//若不经过点n的路径更短
				cf[l]+=n-dis-dis;
				cf[r]-=n-dis-dis;//普通的差分，只不过因为维护的是边有略微差别
                //用一个点的编号记其右边的点，那么最右边的点的序号所代表的边不在该区间，差分时是r而不是r+1
				ans+=dis;
			}	
			else{//若经过n的路径更短
				cf[r]+=dis+dis-n;
				cf[0]+=dis+dis-n;//因为经过n，边r差分对边1也应该有贡献，所以此处做特殊处理。
				cf[l]-=dis+dis-n;与“若不经过点n的路径更短”情况下维护右边界同样的道理
				ans+=n-dis;处理出所有边都通行时的最短路径总和
			}
		}
	}
	long long res=1e18;
	for(int i=1;i<=n;i++){//用res取出所有边中贡献最小的边的贡献
		cf[i]+=cf[i-1];
		res=min(res,cf[i]);
	}
	printf("%lld",ans+res);
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：0)

题意：给定连接 $(1,2)$，$(2,3)$，$(3,4)$，......，$(n,1)$ 的一个环。任选环上的一条边删除，最少需要经过几条边才可以遍历 $x_1,x_2,...,x_m$ 中的所有节点。

做法：首先可以确定在不删边时的最小代价。考虑计算删去由 $x_i$ 走向 $x_{i+1}$ 的边中任意一条边增加的代价，使用线段树等数据结构维护每一条边删去所付出的代价。时间复杂度 $O(m \log n)$。虽然有点慢，但是好想。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long INF=1145141919810;
long long n,m,x[200010],cost1[200010],cost2[200010],add[200010],tree[800010],lazy[800010];
void push_down(long long now)
{
	lazy[now<<1]+=lazy[now];
	tree[now<<1]+=lazy[now];
	lazy[now<<1|1]+=lazy[now];
	tree[now<<1|1]+=lazy[now];
	lazy[now]=0;
}
void change_add(long long now,long long l,long long r,long long x,long long y,long long k)
{
	if(r<x||l>y) return;
	if(x<=l&&r<=y)
	{
		tree[now]+=k;
		lazy[now]+=k;
		return;
	}
	push_down(now);
	long long mid=(l+r)>>1;
	if(x<=mid) change_add(now<<1,l,mid,x,y,k);
	if(y>mid) change_add(now<<1|1,mid+1,r,x,y,k);
	tree[now]=tree[now<<1]+tree[now<<1|1];
}
long long find(long long now,long long l,long long r,long long x)
{
	if(r<x||l>x) return 0;
	if(l==r&&l==x) return tree[now];
	push_down(now);
	long long mid=(l+r)>>1;
	if(x<=mid) return find(now<<1,l,mid,x);
	else return find(now<<1|1,mid+1,r,x);
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=m;i++) scanf("%lld",&x[i]);
	long long total=0;
	for(long long i=1;i<m;i++)
	{
		if(x[i]<x[i+1])
			cost1[i]=x[i+1]-x[i];
		else
			cost1[i]=x[i]-x[i+1];
		cost2[i]=n-cost1[i];
		total+=min(cost1[i],cost2[i]);
		if(x[i]<x[i+1])
		{
			if(cost1[i]<cost2[i])
				change_add(1,1,n,x[i],x[i+1]-1,cost2[i]-cost1[i]);
			else
			{
				change_add(1,1,n,x[i+1],n,cost1[i]-cost2[i]);
				change_add(1,1,n,1,x[i]-1,cost1[i]-cost2[i]);
			}
		}
		else
		{
			if(cost1[i]<cost2[i])
				change_add(1,1,n,x[i+1],x[i]-1,cost2[i]-cost1[i]);
			else
			{
				change_add(1,1,n,x[i],n,cost1[i]-cost2[i]);
				change_add(1,1,n,1,x[i+1]-1,cost1[i]-cost2[i]);
			}
		}
	}
	long long ans=INF;
	for(long long i=1;i<=n;i++)
		ans=min(ans,total+find(1,1,n,i));
	printf("%lld\n",ans);
}
```

---

## 作者：Milthm (赞：0)

这题思路其实挺好想的，首先如果没有这个去一条边的限制，你肯定是怎么走近就怎么走，所以每次只要绕近的一条路就可以了。

但是你去掉这一条边之后，所有走过这条边的路径都要绕一个圈，如果原来答案是 $x$，答案就会增加 $n-2x$。

所以你直接给这个最短路径上所有的点都加上这个 $n-2x$，到时候查询这个位置的值即可。最小值加上不去边的答案就是最终答案。

然后本来可以用差分的，因为我喜欢 DS，所以我还是写了个线段树。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int n,m,a[N],yhb,ans=1e12,b[N],z[N];
void update(int x,int l,int r,int ql,int qr,int c){
	if(ql<=l&&r<=qr){
		a[x]+=(r-l+1)*c;z[x]+=c;
		return;
	}
	int mid=(l+r)>>1;
	if(z[x]){
		a[x*2]+=(mid-l+1)*z[x];a[x*2+1]+=(r-mid)*z[x];
		z[x*2]+=z[x];z[x*2+1]+=z[x];
		z[x]=0;
	}
	if(ql<=mid)update(x*2,l,mid,ql,qr,c);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,c);
	a[x]=a[x*2]+a[x*2+1];
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return a[x];
	}
	int mid=(l+r)>>1,sum=0;
	if(z[x]){
		a[x*2]+=(mid-l+1)*z[x];a[x*2+1]+=(r-mid)*z[x];
		z[x*2]+=z[x];z[x*2+1]+=z[x];
		z[x]=0;
	}
	if(ql<=mid)sum+=query(x*2,l,mid,ql,qr);
	if(qr>mid)sum+=query(x*2+1,mid+1,r,ql,qr);
	return sum;
}
int qwq(int x,int y,int f){
	if(x>y)swap(x,y);
	if(f){
		if(y-x<n+x-y)update(1,1,n,x,y-1,n+x-y+x-y);
		else{
			if(x>1)update(1,1,n,1,x-1,y-x-n+y-x);
			update(1,1,n,y,n,y-x-n+y-x);
		}
	}
	return min(y-x,n+x-y);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		cin>>b[i];
		if(i>1)yhb+=qwq(b[i-1],b[i],1);
	}
	for(int i=1;i<=n;++i)ans=min(ans,query(1,1,n,i,i)+yhb);
	cout<<ans;
	return 0;
}

```


---

## 作者：OldDriverTree (赞：0)

# Solution

考虑相邻两个点对游览次数的贡献。

令 $l=X_{i-1},r=X_i(i>1)$。

如果 $l>r$，把 $l$ 和 $r$ 交换。

对于删掉 $l$ 到 $r-1$ 开始的桥，游览次数都会加上 $n-(r-l)$。

对于删掉 $1$ 到 $l-1$ 和 $r$ 到 $n$ 开始的桥，游览次数都会加上 $r-l$。

答案就为每个桥游览次数的最小值。

由于是对于所有区间加完后进行单点查询。

差分即可，时间复杂度 $O(n+m)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,m,a[N],s[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
main()
{
	m=read(),n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=2;i<=n;i++) {
		int l=a[i-1],r=a[i]; if (l>r) swap(l,r);
		s[1]+=r-l,s[l]+=m-r+l-r+l,s[r]+=r-l-m+r-l;
	}
	int ans=LONG_LONG_MAX;
	for (int i=1;i<=m;i++) s[i]+=s[i-1];
	for (int i=1;i<=m;i++) ans=min(ans,s[i]);
	return !printf("%lld",ans);
}
```

---

## 作者：yshpdyt (赞：0)


## 题意
一个有 $n$ 个点的环，编号从 $1$ 到 $n$ 依次相连。同时选中 $m$ 个点，你需要按顺序依次经过这 $m$ 个点。求把环上某一条边删去后，走过的最少边数。
 
## Sol
先不考虑删去那条边，直接求最小花费。$x \rightarrow y$ 的方案有两种，钦定 $x \le y$，那么方案为:
 $$ x \rightarrow x+1 \rightarrow ...\rightarrow y-1\rightarrow y$$ 
 或者: 
 $$y \rightarrow y+1 \rightarrow ... \rightarrow n \rightarrow 1 \rightarrow x-1 \rightarrow x$$

统计答案时先取最小值，也就是 $\min(y-x,n-y+x)$，得到 $res=\sum_{i=2}^n \min(\lvert a_i-a_{i-1} \rvert,n-\lvert a_i-a_{i-1} \rvert )$。然后考虑可以删边的情况，简单分类讨论一下，令第一种为 ①，第二种为 ②。

$1.$   $y-x \le n-y+x$，走 ① 合适。
   
$(1)$ 删去 $[x,y]$ 之间的边，不能选择 ①，走过的边数会变成 $n-y+x$，对答案的影响是增加 $(n-y+x)-(y-x)$。

$(2)$ 删去 $[y,x]$ 之间的边，可以选择 ①，对答案无影响，答案不变。

$2.$   $y-x > n-y+x$，走 ② 合适。

$(1)$ 删去 $[x,y]$ 之间的边，可以选择 ②，对答案无影响，答案不变。

$(2)$ 删去 $[y,x]$ 之间的边，不能选择 ②，走过的边数会变成 $y-x$，对答案的影响是增加 $(y-x)-(n-y+x)$。

注意到选择代价较小的一方，如果途径的路不能走，答案会增加两方案代价差，不妨给代价较小的方案的途径路径都增加上这个差值，表示删去这条边，会导致答案增加该差值。最后查询删除某一条边的最小代价即可。

任意方式维护区间加，单点查询即可，这里用了差分。

复杂度 $O(m+n)$。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,a[N],m;
ll c[N];
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    for(int i=1;i<=m;i++)cin>>a[i];
    ll res=0,ans=inf;
    for(int i=2;i<=m;i++){
        ll t1=a[i],t2=a[i-1];
        if(t1<t2)swap(t1,t2);
        if(t1-t2>=n-t1+t2){
            ll t=t1-t2-(n-t1+t2);
            c[1]+=t;
            c[t2]-=t;
            c[t1]+=t;
            res+=n-t1+t2;
        }else{
            ll t=(n-t1+t2)-(t1-t2);
            c[t2]+=t,c[t1]-=t;
            res+=t1-t2;;
        }
    }
    ll now=0;
    for(int i=1;i<=n;i++){
        now+=c[i];
        ans=min(ans,now);
    }
    cout<<res+ans<<endl;
    return 0;
}


---

## 作者：sgl654321 (赞：0)

### 题目大意
- 给定一个 $n$ 点 $n$ 边的环，和一个旅游路线 $a_1,a_2,a_3,\cdots,a_m$，表示这个人将顺次到达这些点。
- 每次你将会删掉 $n$ 条边中的一条，当你删掉这一条边之后，你的旅游路线就变成唯一的了，有一个路径长度 $l$。
- 问你删掉哪一条边之后，路径长度 $l$ 有最小值，输出这个最小值。

### 解题思路

首先，假设一条边都没有删除，那么显然对于 $a_i\rightarrow a_{i+1}$ 的这一次旅游，有两种走法，分别是顺时针走和逆时针走。

其长度分别为：$|a_{i+1}-a_i|$ 和 $n-|a_{i+1}-a_i|$。那你肯定会选择短的一条走，我们把每一次旅游的较短走法长度加起来，就是一条边也不删的最短路线长度了，我们把它记作 $l_0$。

现在你要删除其中的第 $i$ 条边，怎么办呢？我们考虑一下哪几次旅游要经过第 $i$ 条边，把删掉它的影响算出来，这样我们就有新的路径长度了。

对于 $a_{i}\rightarrow a_{i+1}$ 的这次旅游，较短走法长度为 $num1$，较长走法长度为 $num2$。对于较短走法上的每一条边，假设删掉了它，那么这次旅游的长度就会加上 $num2-num1$。

较短走法上的每一条边构成的数列，要么是连续的，要么是跨过 $n$  的两端连续的。对于连续区间的区间加法，我们可以用**差分**来维护。

最后由于差分的前缀和就是原数组，我们就可以知道删掉每一条边的影响是多少了，影响肯定是越小越好了，我们输出 $l_0$ 加上最小影响就是最后的答案了。


### 参考代码
注意边和点的转化，我这里第 $i$ 条边连接着 $i$ 和 $i+1$ 两个点。
```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
typedef long long ll;
ll n,m,a[maxn],num1,num2,x,y,ans;
ll f[maxn],s[maxn]; 
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>a[i];
	//define: the ith bridge connect i and i+1 island 
	for(int i=1;i<m;i++){
		//travel from ai to ai+1
		x=a[i];y=a[i+1];
		if(x>y)swap(x,y);
		num1=y-x;num2=n-num1;
		if(num1<num2){
			ans+=num1;
			//then add num1 to all bridges that appear in num2
			//you can use "chafen" algorithm 
			f[x]+=num2-num1;f[y]-=num2-num1;
		}else{
			ans+=num2;
			f[y]+=num1-num2;f[1]+=num1-num2;f[x]-=num1-num2;
		}
	}
	for(int i=1;i<=n;i++)s[i]=s[i-1]+f[i];
	sort(s+1,s+1+n);
	cout<<ans+s[1]<<endl;
	return 0;
}
```


---

