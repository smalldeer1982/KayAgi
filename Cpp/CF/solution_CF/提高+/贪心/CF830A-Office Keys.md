# Office Keys

## 题目描述

There are $ n $ people and $ k $ keys on a straight line. Every person wants to get to the office which is located on the line as well. To do that, he needs to reach some point with a key, take the key and then go to the office. Once a key is taken by somebody, it couldn't be taken by anybody else.

You are to determine the minimum time needed for all $ n $ people to get to the office with keys. Assume that people move a unit distance per $ 1 $ second. If two people reach a key at the same time, only one of them can take the key. A person can pass through a point with a key without taking it.

## 说明/提示

In the first example the person located at point $ 20 $ should take the key located at point $ 40 $ and go with it to the office located at point $ 50 $ . He spends $ 30 $ seconds. The person located at point $ 100 $ can take the key located at point $ 80 $ and go to the office with it. He spends $ 50 $ seconds. Thus, after $ 50 $ seconds everybody is in office with keys.

## 样例 #1

### 输入

```
2 4 50
20 100
60 10 40 80
```

### 输出

```
50
```

## 样例 #2

### 输入

```
1 2 10
11
15 7
```

### 输出

```
7
```

# 题解

## 作者：IGA_Indigo (赞：7)

## 题目大意
有一条线，线上有 $n$ 个人， $k$ 个钥匙，这 $n$ 个人每个人都要拿一把钥匙到办公室，每个钥匙有且只有一把（拿完就消失了属于是），一个人一秒钟能走 $1$ 个单位，问最少多少时间所有人都能拿到钥匙到办公室。
### 输入输出格式
（翻译不太全我来补充一下）

第一行三个整数，人数 $n$，钥匙数 $k$，办公室坐标 $p$，

第二行 $n$ 个整数，每个人 $a_i$ 的坐标。

第三行 $k$ 个整数，每把钥匙 $b_i$ 的坐标。

（请注意，同一个点上不能有一个以上的人或一把以上的钥匙。一个人和一把钥匙可以位于同一个点。）

## 大体思路
就近原则，我们先对钥匙的坐标和人的坐标进行排序，这里运用了一点贪心技术。
### 状态设置
$f(i,j)$ 表示前 $i$ 个人，拿前 $j$ 把钥匙并到达办公室所需要的最短时间。
### 状态转移
#### 如果第 $i$ 个人拿了第 $j$ 把钥匙，则有

$f[i][j]=\max(f[i-1][j-1],abs(a[i]-b[j])+abs(b[j]-p))$

取 $f[i-1][j-1]$ 时最大的状态或这个人到钥匙的距离加上钥匙到办公室的距离（人拿了钥匙到办公室的距离），谁大取谁。
#### 如果第 $i$ 个人没有拿第 $j$ 把钥匙，则有
$f[i][j]=f[i][j-1];$
#### 两种情况都考虑到，合并一下就是
```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=k;j++){
		f[i][j]=max(f[i-1][j-1],abs(a[i]-b[j])+abs(b[j]-p));
		f[i][j]=min(f[i][j],f[i][j-1]);
	}
}
```
最后输出最后答案 $f[n][k]$ 即可，答案是最好情况下用时最慢的人，因为一个人走的时候其他人也在走。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],b[2005],f[1005][2005];//赋值到最大可能的情况
int main(){
	int n,k,p;
	//输入人和钥匙数量和各自坐标
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=k;i++){
		cin>>b[i];
	}
  
	sort(a+1,a+1+n);
	sort(b+1,b+1+k);//贪心对人和钥匙从大到小排序
  
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			f[i][j]=2e9;
		}
	}
  	//初始化，除了f[0][ ]之外全复制成可能的最大值
 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			f[i][j]=max(f[i-1][j-1],abs(a[i]-b[j])+abs(b[j]-p));
			f[i][j]=min(f[i][j],f[i][j-1]);
		}
	}//dp过程，详解在上面”大体思路“部分
  
	cout<<f[n][k];
  	//输出最好情况下最慢的那个人的用时，即最后答案
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：4)

二分贪心的话，可以做到 $O((k\log k+n)\log 2e9)$。

二分答案，即时间上限，然后把时间拆成两个部分：人拿钥匙的时间，钥匙到办公室的时间。

对于一把钥匙来说，其到办公室的时间是固定的，由于我们二分了时间上限，所以一把钥匙会对应着一个坐标区间，在这个区间内的人可以在时限内拿到该钥匙后再去办公室。

这样就变成了一个经典的区间贪心问题：有若干个区间和 $n$ 个点，能否使每个点都落到一个区间内，且一个区间至多包含一个点？

贪心策略是把区间按照右端点从小到大排序，右端点相同的按照左端点从小到大排序，然后从小到大遍历所有点，同时遍历区间找能否包含该点。

遍历区间的过程可以用一个下标记录，在包含了一个点后，下一个点对应的区间可以从上一个点之后开始。

附 AC 代码（Golang）:

```go
package main

import (
	. "fmt"
	"sort"
)

type pair struct{ l, r int }

func main() {
	var n, m, o int
	Scan(&n, &m, &o)
	a := make([]int, n)
	for i := range a {
		Scan(&a[i])
	}
	sort.Ints(a)
	k := make([]int, m)
	for i := range k {
		Scan(&k[i])
	}

	ans := sort.Search(2e9, func(t int) bool {
		ps := []pair{}
		for _, p := range k {
			q := p - o
			if q < 0 {
				q = -q
			}
			if d := t - q; d >= 0 {
				ps = append(ps, pair{p - d, p + d})
			}
		}
		sort.Slice(ps, func(i, j int) bool { a, b := ps[i], ps[j]; return a.r < b.r || a.r == b.r && a.l < b.l })
		i := -1
		for _, p := range a {
			for i++; i < len(ps) && ps[i].r < p; i++ {
			}
			if i == len(ps) || p < ps[i].l {
				return false
			}
		}
		return true
	})
	Print(ans)
}

```


---

## 作者：myyes (赞：3)

摘自我的博客文章：[钥匙题专项训练](https://www.luogu.com.cn/blog/666666new/keys-tm)。

### 题目描述

有 $n$ 个师傅忘撇钥匙，给出所有师傅的坐标 $a$，$k$ 串钥匙的坐标 $b$ 以及工地的坐标 $p$，可以让任意一个师傅跑去撇任意一串钥匙回工地来开锁，师傅都是一秒走一格，所有师傅同时移动，问最少多长时间才能都进工地。

### 题解

这道题还是相当基础的得咩。我们把师傅些跟钥匙排个**序**，设 $dp_{i,j}$ 表示考虑前 $i$ 个师傅和前 $j$ 串钥匙的最小总时间。考虑 $i$ 师傅去不去撇钥匙 $j$ 捏？如果去的话总共就会花费 $\max\{dp_{i-1,j-1},|a_i-b_j|+|b_j-p|\}$ 的时间。否则就是 $dp_{i,j-1}$。则有

$$dp_{i,j}=\min\{\max\{dp_{i-1,j-1},|a_i-b_j|+|b_j-p|\},dp_{i,j-1}\}$$

暴力 DP 就做完了得咩。时间复杂度 $\mathcal O(n^2)$，跑得风快！

参考代码：

```c
#include <bits/stdc++.h>
using namespace std;
const int N=2008,K=2009;
int n,k,p,a[N],b[K],dp[N][K];
int main()
 {
  scanf("%d%d%d",&n,&k,&p);
 for(int i=1;i<=n;++i)scanf("%d",&a[i]);
  for(int i=1;i<=k;++i)scanf("%d",&b[i]);
sort(a+1,a+n+1),sort(b+1,b+k+1);
 for(int i=1;i<2008;++i)
for(int j=0;j<2009;++j)
 {dp[i][j]=2147483647;}
 for(int i=1;i<=n;++i)
   for(int j=1;j<=k;++j)
  {
   dp[i][j]=min(max(dp[i-1][j-1],abs(a[i]-b[j])+abs(b[j]-p)),dp[i][j-1]);
   }
 cout<<dp[n][k];
return 0;
}
```

---

## 作者：ShwStone (赞：2)

## 能通过的网络流算法

似乎题解区还没有讲过可以通过的网络流算法。这里来一发线段树优化。

### 二分图最大匹配

既然是最小化最大值，考虑二分。在确定限制时间的情况下，每个人能够拿哪些钥匙是可以枚举确定的。

一个人必须且只能对应一个钥匙，相当于把人看成左部，钥匙看成右部，如果人能拿某个钥匙就连边，求人与钥匙的二分图最大匹配。

使用匈牙利算法可获得 50 pts。时间复杂度 $\mathcal{O}(nm\log W),m=\mathcal{O}(nk)$。

关于匈牙利算法，出门转 [OI-Wiki](https://oi-wiki.org/graph/graph-matching/bigraph-match/)。

```cpp
const int maxn = 2e3 + 5;
int n, k, p, mid;
int a[maxn], b[maxn];
int linkto[maxn];
bool vis[maxn];

bool dfs(int u) {
    for (int i = 1; i <= k; i++) {
        if (abs(b[i] - a[u]) + abs(b[i] - p) <= mid) {
            if (!vis[i]) {
                vis[i] = true;
                if (!linkto[i] || dfs(linkto[i])) {
                    return linkto[i] = u, true;
                }
            }
        }
    }
    return false;
}

bool check() {
    memset(linkto, 0, sizeof linkto);
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        if (!dfs(i)) return false;
    }
    return true;
}

int main() {
    // freopen("key.in", "r", stdin);
    // freopen("key.out", "w", stdout);
    read(n); read(k); read(p);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = 1; i <= k; i++) read(b[i]);
    int l = 0, r = 1e9;
    while (l < r) {
        mid = (l + r) >> 1;
        if (check()) r = mid;
        else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}
```

### 优化-网络流

我们可以使用最大流算法来优化二分图最大匹配。关于最大流，请再次出门。

如果你使用的是 dinic 算法，时间复杂度的上界是 $\mathcal{O}(\sqrt nm \log W)$。不过只是个上界，网络流的复杂度比较玄学。这里使用 ISAP 实现，会更优一点。

```cpp
const int maxn = 3e3 + 5, maxm = 4e6 + 5;
int n, k, p, mid;
int a[maxn], b[maxn];

struct node {
    int v, w, nxt;
} e[maxm];
int head[maxn], cnt = 1, cur[maxn], dep[maxn], gap[maxn];
int s, t;
queue<int> q;

void bfs() {
    memset(dep, -1, sizeof dep); memset(gap, 0, sizeof gap);
    gap[dep[t] = 0] = 1; q.emplace(t);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            if (dep[e[i].v] == -1 && !e[i].w) {
                gap[dep[e[i].v] = dep[u] + 1]++;
                q.emplace(e[i].v);
            }
        }
    }
}

void add(int u, int v, int w) {
    e[++cnt].nxt = head[u];
    head[u] = cnt; e[cnt].v = v, e[cnt].w = w;
}

int dfs(int u = s, int flow = 0x3f3f3f3f) {
    if (u == t) return flow;
    int rest = flow;
    for (int i = cur[u]; i; i = e[i].nxt) {
        cur[u] = i; 
        if (dep[e[i].v] + 1 == dep[u] && e[i].w) {
            int f = dfs(e[i].v, min(e[i].w, rest));
            rest -= f, e[i].w -= f, e[i ^ 1].w += f;
        }
        if (!rest) return flow;
    }
    if (!--gap[dep[u]++]) dep[s] = n + k + 2;
    gap[dep[u]]++;
    return flow - rest;
}

int ISAP() {
    bfs(); int res = 0;
    while (dep[s] < n + k + 2) {
        memcpy(cur, head, sizeof cur);
        res += dfs();
    }
    return res;
}

bool check() {
    cnt = 1; memset(head, 0, sizeof head);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (abs(a[i] - b[j]) + abs(b[j] - p) <= mid) {
                add(i, j + n, 1);
                add(j + n, i, 0);
            }
        }
    }
    s = n + k + 1, t = n + k + 2;
    for (int i = 1; i <= n; i++) add(s, i, 1), add(i, s, 0);
    for (int i = 1; i <= k; i++) add(i + n, t, 1), add(t, i + n, 0);
    return ISAP() == n;
}
```

### 再次优化-线段树优化建图

上述算法仍不能 AC。我们挖掘题目贪心性质。由于钥匙都在数轴上，所以在排序之后，一个人能取的钥匙一定是连续的。既然是向连续的点连边，我们就可以考虑用线段树优化建图。

大致思想是用像线段树一样的结构，建立起 $k-1$ 个辅助节点，使得一个辅助节点在树上能与一个区间相连。这样，只要拆成 $\log k$ 个区间（即和 $\log k$ 个辅助节点连边）即可表示一个连续区间。

详细可以看[洛谷日报](https://www.luogu.com.cn/blog/forever-captain/DS-optimize-graph)。

现在 $m = \mathcal{O}(n \log k)$，总时间复杂度上界是 $\mathcal{O}(\sqrt nm \log W)$。

```
const int maxn = 6e3 + 5, maxm = 2e6 + 5;
int n, k;
long long p, mid;
long long a[maxn], b[maxn];

namespace ISAP {
    struct node { int v, w, nxt; } e[maxm];
    int head[maxn], cnt = 1, cur[maxn], dep[maxn], gap[maxn], cntu;
    int s, t;
    queue<int> q;
    void bfs() {
        memset(dep, -1, sizeof dep); memset(gap, 0, sizeof gap);
        gap[dep[t] = 0] = 1; q.emplace(t);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = e[i].nxt) {
                if (dep[e[i].v] == -1 && !e[i].w) {
                    gap[dep[e[i].v] = dep[u] + 1]++;
                    q.emplace(e[i].v);
                }
            }
        }
    }
    void add(int u, int v, int w) { e[++cnt].nxt = head[u]; head[u] = cnt; e[cnt].v = v, e[cnt].w = w; }
    int dfs(int u = s, int flow = 0x3f3f3f3f) {
        if (u == t) return flow;
        int rest = flow;
        for (int i = cur[u]; i; i = e[i].nxt) {
            cur[u] = i; 
            if (dep[e[i].v] + 1 == dep[u] && e[i].w) {
                int f = dfs(e[i].v, min(e[i].w, rest));
                rest -= f, e[i].w -= f, e[i ^ 1].w += f;
            }
            if (!rest) return flow;
        }
        if (!--gap[dep[u]++]) dep[s] = cntu;
        gap[dep[u]]++;
        return flow - rest;
    }
    int solve() {
        bfs(); int res = 0;
        while (dep[s] < cntu) {
            memcpy(cur, head, sizeof cur);
            res += dfs();
        }
        return res;
    }
}

namespace segment_tree {
    struct node; typedef node* pos;
    struct node { pos ls, rs; int l, r, u; node() { ls = rs = this; }};
    node buf[maxn], *root = buf, *buf_pos = buf;
    pos new_node(int l, int r) { pos p = ++buf_pos; p -> ls = p -> rs = buf; p -> l = l, p -> r = r; p -> u = ++ISAP::cntu; return p; }
    void build(pos p) {
        if (p -> l == p -> r) return ISAP::add(p -> u, ISAP::t, 1), ISAP::add(ISAP::t, p -> u, 0);
        int mid = (p -> l + p -> r) >> 1;
        p -> ls = new_node(p -> l, mid), build(p -> ls);
        p -> rs = new_node(mid + 1, p -> r), build(p -> rs);
        ISAP::add(p -> u, p -> ls -> u, 0x3f3f3f3f), ISAP::add(p -> ls -> u, p -> u, 0);
        ISAP::add(p -> u, p -> rs -> u, 0x3f3f3f3f), ISAP::add(p -> rs -> u, p -> u, 0);
    }
    void update(pos p, int id, int l, int r) {
        if (l <= p -> l && p -> r <= r) return ISAP::add(id, p -> u, 0x3f3f3f3f), ISAP::add(p -> u, id, 0);
        if (l <= p -> ls -> r) update(p -> ls, id, l, r);
        if (p -> rs -> l <= r) update(p -> rs, id, l, r);
    }
}


//记得对 b 排序
bool check() {
    ISAP::cnt = 1; segment_tree::buf_pos = segment_tree::buf;
    ISAP::s = n + 1, ISAP::t = n + 2, ISAP::cntu = n + 2;
    memset(ISAP::head, 0, sizeof ISAP::head);

    for (int i = 1; i <= n; i++) ISAP::add(ISAP::s, i, 1), ISAP::add(i, ISAP::s, 0);
    segment_tree::root = segment_tree::new_node(1, k);
    segment_tree::build(segment_tree::root);

    for (int i = 1; i <= n; i++) {
        int l = k + 1, r = 0;
        for (int j = 1; j <= k; j++) {
            if (abs(a[i] - b[j]) + abs(b[j] - p) <= mid) {
                l = min(l, j), r = max(r, j);
            }
        }
        if (l <= r) segment_tree::update(segment_tree::root, i, l, r);
    }
    return ISAP::solve() == n;
}
```

---

## 作者：cqbzhyf (赞：2)

## 思路

先看题目：

在一条直线上有 $n$ 人和 $k$ 个钥匙。每个人都想到达位于线路上的办公室。要做到这一点，他需要到一个**有钥匙的点上**，**拿到钥匙**然后去办公室。

一旦有人拿走钥匙，**任何人都不能拿走钥匙**。

您需要确定所有人用钥匙到达办公室的最短时间。 如果两个人同时拿到钥匙，他们中**只有一个**可以拿钥匙。而一个人只能通过那个点而**不能获取钥匙**。

初看题目，贪心地将 $n$ 个人的起始位置**从小到大**排序，之后再将 $k$ 把钥匙的位置从小到大排序，方便之后的处理。（这里建议使用 `stable_sort`，因为它更稳定）

然后就可以开始暴力了，用 $n$ 个人且保证 $n \le k$，于是不需要取 $k-n+1$ 把钥匙，然后用 `abs` 处理一下距离（注意是这个人到钥匙的距离加上钥匙到办公室的距离）。

输出答案……

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,p,a[1005],b[2005],ans=LONG_LONG_MAX;
int main(){
	scanf("%lld %lld %lld",&n,&k,&p);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=k;i++)scanf("%lld",&b[i]);
	stable_sort(a+1,a+1+n),stable_sort(b+1,b+1+k);
	for(int i=1;i<=k-n+1;i++){
		ll sum=0;
		for(int j=1;j<=n;j++){
			sum=max(sum,abs(b[i+j-1]-a[j])+abs(b[i+j-1]-p));
		}
		ans=min(ans,sum);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：TulipeNoire (赞：1)

### 思路

首先看到此题，推一个结论：

$$\forall a_i\leq a_j\ ,\ c_i\leq c_j$$

$c_i$ 为对钥匙位置从小到大排序后第 $i$ 个人选择的钥匙编号。

怎么证明？

因为钥匙到办公室的距离一样，所以看人到办公室距离。

两者若交叉，都会变大时，自然不选；若有其中一个变小时，则不按上述选择，其中一个一定会大于上述选择（因为是计算最大值，其中一个小没有用)。

所以得到这个结论后，直接 dp。

定义 $dp_{i,j}$ 为前 $i$ 个人在前 $j$ 把钥匙选的最大值的最小值。

则选或不选：$dp_{i-1,j}$ 和 $\max\{dp_{i-1,j-1},|a_i-b_j|+|b_j-p|\}$。

**初始化时要 $dp_{0,j}$ 都置为 0 ,其他置为最大值。**

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long x[1005],y[2005],p;
long long dp[1005][2005];
int main() {
    scanf("%d %d %lld",&n,&m,&p);
    for (int i=1;i<=n;i++) {
        scanf("%lld",&x[i]);
    }
    for (int i=1;i<=m;i++) {
        scanf("%lld",&y[i]);
    }
    sort(x+1,x+n+1);
    sort(y+1,y+m+1);
    memset(dp,63,sizeof dp);
    for (int i=0;i<=m;i++) dp[0][i]=0;
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (i>j) continue;
            if (i==j) {
                dp[i][j]=max(dp[i-1][j-1],abs(x[i]-y[j])+abs(p-y[j]));
            }
            if (i<j) {
                dp[i][j]=min(dp[i][j-1],max(dp[i-1][j-1],abs(x[i]-y[j])+abs(p-y[j])));
            }
        }
    }
    printf("%lld",dp[n][m]);
    return 0;
}
```

---

## 作者：诚实的抱抱熊 (赞：0)

若两个人要去拿两把钥匙，则坐标小的人拿坐标小的钥匙，坐标大的人拿坐标大的钥匙最优。

那么考虑对人与钥匙的坐标进行排序，设第 $i$ 个人拿了第 $p_i$ 个钥匙，根据上文发现的结论容易发现 $p$ 单调递增。

容易想到用 dp 解决问题，设 $f_{i,j}$ 表示前 $i$ 个人在前 $j$ 把钥匙里选择了 $i$ 把钥匙的用时最小值， $\operatorname{dis}( i , j )$ 表示第 $i$ 个人拿第 $j$ 把钥匙再走到办公室的用时。

则转移方程式为：

$$f_{i,j} = \min(f_{i,j-1}, \max(f_{i-1,j-1}, \operatorname{dis}(i , j) ))$$

代码如下，其中使用了滚动数组优化了第一维：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e3 + 7, M = 2e3 + 7;
int n, m, p, a[N], b[M], f[M];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
  
	cin >> n >> m >> p;
	for(int i = 1; i <= n; ++ i)	cin >> a[i];
	for(int i = 1; i <= m; ++ i)	cin >> b[i];
  
	sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + m);
	for(int i = 1; i <= n; ++ i) {
		for(int j = m; j >= i; -- j)		f[j] = max(f[j - 1], abs(b[j] - a[i]) + abs(p - b[j]));
		for(int j = i + 1; j <= m; ++ j)	f[j] = min(f[j - 1], f[j]);
	}
	cout << f[m];
	return 0;
}
```

---

## 作者：Light_in_Dark (赞：0)

## 思路
第一眼看题，$n \le 1000, n \le k \le 2000$ ,感觉可以打一个 $O(nk)$ 的 $dp$ , 但每个人的取数都会影响后面所有人取数，那么，我们会很自然的想到贪心。

首先把人的位置和钥匙的位置排序，再把第 $i$ 个人拿第 $j$ 把钥匙再回去的时间用一个 $dis$ 数组来存一下，如下:( $a,b$ 为人的位置和车的位置 )

$$dis[i][j]=abs(a[i]-b[j])+abs(b[j]-p);$$

可以自然的想到定义一个 $dp[i][j]$（$i$ 表示前 $i$ 个人， $j$ 表示前 $j$ 把钥匙, $dp[i][j]$ 表示最少的时间）。

如果取第 $i$ 个人取第 $j$ 把钥匙，那么

$$dp[i][j]=max(dp[i-1][j-1],dis[i][j]);$$

如果第 $i$ 个人不取的 $j$ 把钥匙，那么

$$dp[i][j]=dp[i][j-1];$$

综上，递推式为

$$dp[i][j]=min(dp[i][j-1],max(dp[i-1][j-1],dis[i][j]));$$


大家可能会疑惑，为什么非要排序，~~因为不排序不`AC`啊~~，这是因为如果不排序，第 $i$ 个人不一定比第 $i-1$ 个人的坐标大，所以不一定 $i$ 可以比 $i-1$ 后取到，这样这个递推式就有很大的漏洞了。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int inf=1<<30;
int n,k,p,ans=inf;
int a[1005],b[2005],dis[1005][2005],dp[1005][2005];
int main(){
	cin>>n>>k>>p;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=k;i++)cin>>b[i];
	sort(a+1,a+n+1),sort(b+1,b+k+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			dis[i][j]=fabs(a[i]-b[j])+fabs(b[j]-p);
			dp[i][j]=inf;
		}
	}
	for(int i=0;i<=k;i++)dp[0][i]=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)dp[i][j]=min(dp[i][j-1],max(dp[i-1][j-1],dis[i][j]));
	for(int i=n;i<=k;i++)ans=min(ans,dp[n][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：0)

# 0x00 思路
先看题。
>在一条直线上有 $n$ 个人和 $k$ 个钥匙。每个人都想到达位于线路上的办公室。要做到这一点，他需要到一个**有钥匙的点**上，拿到钥匙**然后**去办公室。
>1. 一旦有人**拿走钥匙**，**任何人**都不能拿走钥匙。
>1. 人们每 $1$ 秒移动一个单位距离。 您需要确定**所有人**用钥匙到达办公室的**最短时间**。 如果两个人同时到达钥匙所在位置，他们中**只有一个**可以拿钥匙。而一个人只能通过那个点而不能获取钥匙。

即一个点只有一把钥匙，只有一个人可以拿到，且所有人都需要到达办公室，求最短时间。

由于 $k\ge n$，所以很自然的可以想到用 `dp` 解决。

# 0x02 定义状态
定义 `dp[i][j]` 为前 `i` 个人用前 `j` 把钥匙到达办公室的最短用时。

# 0x03 状态转移
- 首先算出当前最后一人到达办公室的最小时间(由于会有负数所以需要加上 `abs` )：`abs(people[i]-keys[j])+abs(keys[j]-m)`。

- 接着因为当前一人使用了一把钥匙，所以需和前 `i-1` 个人中最后到达办公室的时间取最大值：`max(dp[i-1][j-1],abs(people[i]-keys[j])+abs(keys[j]-m))`。

- 最后与不用这把钥匙的最短时间进行比较取较小值（其中与 `dp[i][j]` 比较是万一它比较小呢对吧，以防万一）：`min(min(dp[i][j],max(dp[i-1][j-1],abs(people[i]-keys[j])+abs(keys[j]-m))),dp[i][j-1])`。

所以最后的转移方程就出现了！（但很长）

`dp[i][j]=min(min(dp[i][j],max(dp[i-1][j-1],abs(people[i]-keys[j])+abs(keys[j]-m))),dp[i][j-1]);`

# 0x04 初始化

## 对于钥匙和人
由于只有最左边的人使用选择的最左边的钥匙才会使得时间最小，其余同理。所以我们应先分别对人的位置和钥匙的位置进行排序。

## 对于 dp
由于要求最小值，所以需先赋一个较大值。且当没有人的时候最短时间为 $0$。

## 注意
由于数据范围 
$1\le n\le 1000,n\le k\le 2000,1<=p<=10^{9}$ 较大，所以我们需要使用  `long long` 进行存储。

# code
```c
#include<bits/stdc++.h>
using namespace std;
long long people[1005],keys[2005],d[1005][2005];//人，钥匙，dp
int main()
{
	int n,k,m,i,j;
	scanf("%d %d %d",&n,&k,&m);
	for(i=1;i<=n;i++)
		scanf("%lld",&people[i]);
	sort(people+1,people+1+n);
	for(i=1;i<=k;i++)
		scanf("%lld",&keys[i]);
	sort(keys+1,keys+1+k);
   //初始化
	memset(d,0x3f,sizeof(d));
	for(i=0;i<=k;i++)
		d[0][i]=0;
   //dp-ing
	for(i=1;i<=n;i++)
		for(j=i;j<=k;j++)
			d[i][j]=min(min(d[i][j],max(d[i-1][j-1],abs(people[i]-keys[j])+abs(keys[j]-m))),d[i][j-1]);
	printf("%lld",d[n][k]);
	return 0;
}
```

---

## 作者：AC自动机 (赞：0)

### 思路
首先读入后，按照位置分别排序，然后处理一个dis数组，表示第i个人拿了第j把钥匙后去办公室的路程。
然后就是一个01背包，最开始的时候人是瓷的，写了三重循环，一直TLE，附上磁珠代码(不保证对哦)233333
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<math.h>
using namespace std;
int n,k,p;
int man[1005];
int key[2005];
int dis[1005][2005];
int dp[1005][2005];
inline int cmp(int a,int b){
	return a<b;
}
int minn(int a,int b){
	if(a>=b)return b;
	return a;
}
int maxx(int a,int b){
	if(a>=b)return a;
	return b;
}
int main(){
	//freopen("1.in","r",stdin);
	cin>>n>>k>>p;
	for(register int i=1;i<=n;i++){
		cin>>man[i];
	}
	for(register int i=1;i<=k;i++){
		cin>>key[i];
	}
	sort(man+1,man+n+1,cmp);
	sort(key+1,key+k+1,cmp);
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=k;j++){
			dis[i][j]=fabs(man[i]-key[j])+fabs(key[j]-p);
			dp[i][j]=999999999;
		}
	}
	dp[0][0]=0;
	//cout<<"fuck"<<endl;
	for(register int i=1;i<=n;i++){  //1-ige re 
		for(register int j=i;j<=k;j++){ //1-j zhongxuanze
			int xx=minn(j,n);
			for(register int kk=i;kk<=xx;kk++){
				if(kk<1)continue;
				dp[i][j]=minn(dp[i][j],maxx(dp[i-1][kk-1],dis[kk][j]));
//				cout<<i<<' '<<j<<' '<<kk<<endl;
//				cout<<dp[i][j]<<' '<<dp[i-1][kk]<<' '<<dis[kk][j]<<endl<<endl;
			}
		}
	}
	// while(1){
	// 	int x,y;
	// 	cin>>x>>y;
	// 	cout<<dp[x][y]<<endl;
	// }
	int ans=999999999;
	for(register int i=n;i<=k;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans<<endl;
}
```
当时用kk来表示i-1个人一共拿到第kk把钥匙是的最大步数的最小值，就是因为枚举这个kk然后挂了，后来发现不需要枚举kk，因为dp[i][j]只能从dp[i][j-1]和dp[i-1][j-1]两种情况转移过来，分别表示不选第j把钥匙和第i个人选了第j把钥匙的情况。

可以得到状态转移方程：

dp[i][j]=min(dp[i][j-1],max(dp[i-1][j-1],dis[i][j]));

还有，初始化很重要qwq，所有的dp[0][i]都等于0，剩下的所有都是2147483647。

#### 附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<math.h>
using namespace std;
int n,k,p;
int man[1005];
int key[2005];
int dis[1005][2005];
int dp[1005][2005];
inline int cmp(int a,int b){
	return a<b;
}
int minn(int a,int b){
	if(a>=b)return b;
	return a;
}
int maxx(int a,int b){
	if(a>=b)return a;
	return b;
}
int main(){
	//freopen("1.in","r",stdin);
	cin>>n>>k>>p;
	for(register int i=1;i<=n;i++){
		cin>>man[i];
	}
	for(register int i=1;i<=k;i++){
		cin>>key[i];
	}
	sort(man+1,man+n+1,cmp);
	sort(key+1,key+k+1,cmp);
	for(register int i=0;i<=n;i++){
		for(register int j=0;j<=k;j++){
			dis[i][j]=fabs(man[i]-key[j])+fabs(key[j]-p);
			dp[i][j]=2147483647;
		}
	}
	for(register int i=0;i<=k;i++){
		dp[0][i]=0;
	}
	//cout<<"fuck"<<endl;
	for(register int i=1;i<=n;i++){  //1-ige re 
		for(register int j=1;j<=k;j++){ //1-j zhongxuanze
			dp[i][j]=minn(dp[i][j-1],maxx(dp[i-1][j-1],dis[i][j]));
		}
	}
	// while(1){
	// 	int x,y;
	// 	cin>>x>>y;
	// 	cout<<dp[x][y]<<endl;
	// }
	int ans=2147483647;
	for(register int i=n;i<=k;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans<<endl;
}
```


---

## 作者：VenusM1nT (赞：0)

二分答案。

首先观察题面，有提到“一人对应一把钥匙”，容易想到二分图匹配，我们二分答案 $mid$，然后暴力找出所有满足 $|a[i]-b[j]|+|b[j]-p|\leq mid$ 的 $(i,j)$，在他们中间连边，可以得到一个二分图，对它跑最大匹配。

但是，由于建边的复杂度为 $\text{O}(nk)$，$\texttt{Dinic}$ 求最大匹配的复杂度为 $\text{O}(n\sqrt{m})$，而二分的复杂度为 $\text{O}(\log 2e9)$，最坏情况的运算次数高达 $2e8$，显然会 $\texttt{TLE}$，因此，我们要想一个更好的办法检验 $mid$。

那么这个办法，就是贪心。我们对数据排序，对所有 $\leq p$ 的 $a[i]$，从左向右找到第一个符合答案的 $b[j]$；对所有 $>p$ 的 $a[i]$，从右向左找到第一个符合答案的 $b[j]$，显然这就是最优的方案。而它的复杂度是 $\text{O}(nk)$，可以过此题。

（事实上在模拟赛的数据下，使用 $\texttt{Dinic}$ 也可以 AC，但由于 CF 数据太强，并不能 AC。）

网络流代码：

```cpp
#include<bits/stdc++.h>
#define MAXN 10005
#define MAXM 5000005
#define reg register
#define inl inline
#define inf 2147483647
#define int long long
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
queue <int> q;
int cnt,fst[MAXN],nxt[MAXM<<1],to[MAXM<<1],w[MAXM<<1],cur[MAXN];
int n,k,p,a[MAXN],b[MAXN],S,T,ans,dep[MAXN];
template <typename T> inl void Read(reg T &x)
{
    x=0;
    reg int fu=1;
    reg char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
    x*=fu;
}
inl void AddEdge(reg int u,reg int v,reg int c)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
}
inl bool Bfs()
{
    memset(dep,0,sizeof(dep));
    q.push(S);
    dep[S]=1;
    while(!q.empty())
    {
        reg int u=q.front();
        q.pop();
        for(reg int i=fst[u];i;i=nxt[i])
        {
            reg int v=to[i];
            if(!dep[v] && w[i])
            {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[T]!=0;
}
int Dfs(reg int u,reg int flow)
{
    if(u==T || !flow) return flow;
    reg int used=0;
    for(reg int &i=cur[u];i;i=nxt[i])
    {
        reg int v=to[i];
        if(w[i] && dep[v]==dep[u]+1)
        {
            reg int d=Dfs(v,min(w[i],flow));
            if(d)
            {
                used+=d;
                flow-=d;
                w[i]-=d;
                w[i^1]+=d;
                if(!flow) break;
            }
        }
    }
    return used;
}
inl int Dinic()
{
    reg int sum=0,val;
    while(Bfs())
    {
        memcpy(cur,fst,sizeof(fst));
        while(val=Dfs(S,inf)) sum+=val;
    }
    return sum;
}
inl bool Check(reg int mid)
{
    cnt=1;
    memset(fst,0,sizeof(fst));
    for(reg int i=1;i<=n;++i)
    {
        for(reg int j=1;j<=k;++j)
        {
            reg int d=abs(a[i]-b[j])+abs(b[j]-p);
            if(d<=mid)
            {
                AddEdge(i,j+n,1);
                AddEdge(j+n,i,0);
            }
        }
    }
    for(reg int i=1;i<=n;++i)
    {
        AddEdge(S,i,1);
        AddEdge(i,S,0);
    }
    for(reg int i=1;i<=k;++i)
    {
        AddEdge(i+n,T,1);
        AddEdge(T,i+n,0);
    }
    return Dinic()==n;
}
signed main()
{
    Read(n);
    Read(k);
    Read(p);
    S=0;
    T=n+k+1;
    for(reg int i=1;i<=n;++i) Read(a[i]);
    for(reg int i=1;i<=k;++i) Read(b[i]);
    reg int l=0,r=2e9;
    while(l<=r)
    {
        reg int mid=l+r>>1;
        if(Check(mid))
        {
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

贪心：

```cpp
#include<bits/stdc++.h>
#define MAXN 10005
#define MAXM 5000005
#define reg register
#define inl inline
#define inf 2147483647
#define int long long
using namespace std;
int n,k,p,a[MAXN],b[MAXN],ans;
bool fg[MAXN];
template <typename T> inl void Read(reg T &x)
{
	x=0;
	reg int fu=1;
	reg char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
	x*=fu;
}
inl bool Check(reg int mid)
{
	memset(fg,0,sizeof(fg));
	for(reg int i=1;i<=n;i++)
	{
		if(a[i]<=p)
		{
			reg int cnt=-1;
			for(reg int j=1;j<=k;j++)
			{
				if(!fg[j] && abs(a[i]-b[j])+abs(b[j]-p)<=mid)
				{
					cnt=j;
					break;
				}
			}
			if(cnt==-1) return 0;
			fg[cnt]=1;
		}
		else break;
	}
	for(reg int i=n;i>=1;i--)
	{
		if(a[i]>p)
		{
			reg int cnt=-1;
			for(reg int j=k;j>=1;j--)
			{
				if(!fg[j] && abs(a[i]-b[j])+abs(b[j]-p)<=mid)
				{
					cnt=j;
					break;
				}
			}
			if(cnt==-1) return 0;
			fg[cnt]=1;
		}
		else break;
	}
	return 1;
}
signed main()
{
	Read(n);
	Read(k);
	Read(p);
	for(reg int i=1;i<=n;++i) Read(a[i]);
	for(reg int i=1;i<=k;++i) Read(b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+k+1);
	reg int l=0,r=2e9;
	while(l<=r)
	{
		reg int mid=l+r>>1;
		if(Check(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

