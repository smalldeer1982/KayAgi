# 「CGOI-2」No cost too great

## 题目背景

光芒浸透圣巢，她正犯下弥天之错。

所剩寥寥无几的信仰，为什么始终执着。

我将作灯塔，照耀王国。

但在那之前有更重要的事去做，

无论什么代价都在所不惜，尽管我所剩无多……

## 题目描述

白王正在最后一次参观他建造的宏伟宫殿。现在假设宫殿由 $n$ 个房间构成，房间之间有若干个**单向**通道。出于白王奇怪的装修癖好（不是指到处安电锯），对于第 $i$ 个房间，它向编号在区间 $[l_i,r_i]$ 中的所有房间都连有一条单向通道。例如，$4$ 号房间向 $[2,5]$ 连有单向通道，就意味着从 $4$ 号房间到 $2,3,4,5$ 号房间各有一条单向通道（一个房间可以向自己连有通道）。当一个房间向 $[0,0]$ 连有通道时，表示没有从这个房间出发的通道。

白王提出了 $q$ 个问题，每次询问从 $a$ 号房间，通过恰好 $m$ 条单向通道且不经过 $c$ 号房间到达 $b$ 号房间的方案数（两方案不同，当且仅当存在 $i$ 使得两方案通过的第 $i$ 条通道不同）。因为这个数字可能会很大，所以白王让你将答案模 $998244353$ 后再回答。

## 说明/提示

### 样例说明

在样例一中，$1$ 号房间能到达 $2,3$ 号房间，$2$ 号房间能到达 $1$ 号房间，$3$ 号房间能到达 $2,3,4$ 号房间，$4$ 号房间不能到达任何房间。

对于第一个询问，从 $1$ 号房间经过 $5$ 条通道且不经过 $4$ 号房间到达 $3$ 号房间的方案有 `121213`，`121333`，`133213`，`132133`，`133333` 共五种。

---

### 数据范围

**本题采用捆绑测试。**

| 编号| 特殊性质 | 空间限制 |分数 |
| :-: | :-: | :-: | :-: |
| 0 | $n\le10$，$q\le10$，$m\le4$ | 256MB | 10pts |
| 1 | $n\le100$，$q\le10^4$，$m\le40$ | 256MB | 15pts |
| 2 | 对于所有询问，$l_c=r_c=0$ | 256MB | 15pts |
| 3 | 无 | 256MB | 30pts |
| 4 | 无 | 128MB | 30pts |

对于 $100\%$ 的数据，$1\le n \le 500$，$1\le q \le 10^5$，$1\le m \le 100$，$0 \le l_i \le r_i \le n$，$1 \le a,b,c \le n$。当且仅当 $l_i=0$ 时 $r_i=0$。时间限制均为 1s。

---

### 提示

**注意空间常数。**

## 样例 #1

### 输入

```
4 5
2 3
1 1
2 4
0 0
1 3 4 5
1 4 2 4
2 3 1 2
4 4 3 0
1 3 2 5```

### 输出

```
5
1
0
1
1```

## 样例 #2

### 输入

```
10 10
6 6
4 10
2 5
1 7
3 4
5 7
4 10
1 7
1 3
2 5
8 8 5 1
4 7 5 3
5 9 4 4
1 5 5 2
6 2 10 2
3 3 7 4
1 10 1 2
6 2 4 4
9 2 1 4
9 10 3 2```

### 输出

```
0
17
2
0
0
46
0
12
23
1```

## 样例 #3

### 输入

```
10 10
2 6
6 9
5 7
3 9
0 0
0 0
3 5
5 5
3 6
1 10
5 9 6 3
10 8 6 4
10 8 5 1
8 6 5 4
7 2 5 4
6 1 5 3
10 4 5 1
5 5 6 0
7 9 6 4
4 9 6 2```

### 输出

```
0
17
1
0
0
0
1
1
4
1```

# 题解

## 作者：子丑 (赞：11)

[传送门](https://www.luogu.com.cn/problem/T257300)

#### 前置知识：

差分，容斥。

#### 题意：

- 给出一张有向图，对房间 $i$ 有若干条边连向区间 $[l_i,r_i]$ 中的所有点。
- $q$ 次询问，每次问从点 $a$ 出发，恰通过 $m$ 条边且不经过点 $c$ 到达点 $b$ 的方案数。

#### 分析：

是一道容斥+dp+小幅度卡空间题。

##### Subtask0：

dfs 暴力搜索。

##### Subtask2:

先来看看没有容斥、不卡空间的 dp 该怎么做。

考虑一个 dp 数组 $f_{k,s,t}$，表示从 $s$ 经过 $k$ 条边到达 $t$ 的方案数。转移方程是 $f_{k,s,t}\gets\sum_{(v,t)\in E}$ $f_{k-1,s,v}$，时间复杂度为 $O(n^3m)$。将这个方程反过来，就是 $f_{k-1,s,v}\to f_{k,s,t}\quad((v,t)\in E)$。关注到每个点所到达的点都在一个区间中，也就是说这个式子是一个区间加法。区间加法可以通过前缀和或者差分实现。这里我选择差分，那么转移就变成了如下：

```cpp
for(int k=1; k<=M; ++k) {
	for(int s=1; s<=n; ++s) {
		for(int t=1; t<=n; ++t) {
			f[k][s][L[t]]+=f[k-1][s][t];
			f[k][s][R[t]+1]-=f[k-1][s][t];
		}
		for(int t=1; t<=n; ++t) {
			f[k][s][t]+=f[k][s][t-1];
		}
	}
}
```

询问可以在线回答：

```cpp
while(q--) {
	int a=read(), b=read(), c=read(), m=read();//这里的c暂时没用
	printf("%d\n", f[m][a][b]);
}
```



##### Subtask3:

加入容斥，显然不经过点 $c$ 的方案等价于所有方案减去经过点 $c$ 的方案。一种很符合直觉的计算经过点 $c$ 方案数的方法是 $\sum_{i=0}^kf_{i,s,c}\cdot f_{k-i,c,t}$，但是很显然，这样会有重复的方案。当两个方案中最后一次经过 $c$ 点的时间不同时，这两个方案一定不同，并且我们知道单个 $f$ 数组中并没有重复的方案，那么就可以通过枚举最后一次经过 $c$ 点的时间来进行计算。现在再增加一个 dp 数组 $g_{k,s,t}$，表示从 $s$ 出发，经过 $k$ 条边且不再经过 $s$ 到达 $t$ 的方案数，这样就可以通过 $\sum_{i=0}^kf_{i,s,c}\cdot g_{k-i,c,t}$ 来计算不重复的经过点 $c$ 的方案数了。在转移数组 $g$  时，只需要令 $g_{k,s,s}$ 的值始终为 $0$，就可以保证所有 $g_{k,s,t}$ 方案都没有再次经过点 $s$。转移如下：

```cpp
for(int k=1; k<=M; ++k) {
	for(int s=1; s<=n; ++s) {
		for(int t=1; t<=n; ++t) {
			f[k][s][L[t]]+=f[k-1][s][t], f[k][s][R[t]+1]-=f[k-1][s][t];
			g[k][s][L[t]]+=g[k-1][s][t], g[k][s][R[t]+1]-=g[k-1][s][t];
		}
 		for(int t=1; t<=n; ++t) {
			f[k][s][t]+=f[k][s][t-1];
			g[k][s][t]+=g[k][s][t-1];
		}
		g[k][s][s]=0;
	}
}
```

询问仍然是在线回答：

```cpp
while(q--) {
	int a=read(), b=read(), c=read(), m=read(), ans=f[m][a][b];
	for(int i=0; i<=m; ++i) ans-=f[i][a][c]*g[m-i][c][b];
	printf("%d\n", ans);
}
```

##### Subtask4:

不出意外的话，此时的数组大小在 200MB 上下，完全无法通过 128MB 的限制。但是询问是可以离线的，意味着我们并不需要将 $f$ 和 $g$ 两个数组都完全存下来。这里选择滚动 $g$ 数组，所以先把 $f$ 数组计算出来，然后在滚动计算数组 $g$ 的同时计算答案。主题代码如下（未进行取模）：

```cpp
#define rep(i, a, b) ...
inline int read(){...};
const int N=502, M=100, Q=1e5+1;

int n, q, L[N], R[N], f[M+2][N][N], g[2][N][N];
struct Que {
	int a, b, c, m, ans;
	inline void sol(int k) {
		if(k<=m) ans-=f[m-k][a][c]*g[k&1][c][b];
	}
} que[Q];
inline Que get() {
	int a=read(), b=read(), c=read(), m=read();
	return Que(a, b, c, m, f[m][a][b]);
}

int main() {
	//输入 
	n=read(), q=read();
	rep(i, 1, n) {
		L[i]=read(), R[i]=read();
		f[0][i][i]=g[0][i][i]=1;
		if(!L[i]) L[i]=1;
	}
	//计算数组 f 
	rep(k, 1, M) {
		rep(s, 1, n) {
			rep(t, 1, n) {
				f[k][s][L[t]]+=f[k-1][s][t]);
				f[k][s][R[t]+1]-=f[k-1][s][t];
			}
			rep(t, 1, n) {
				f[k][s][t]+=f[k][s][t-1];
			}
		}
	}
	//输入与预处理询问 
	rep(i, 1, q) {
		que[i]=get();
		que[i].sol(0);
	}
	//计算数组 g 与答案 
	rep(k, 1, M) {
		bool kk=k&1, tk=kk^1;
		memset(g[kk], 0, sizeof(g[kk]));
		rep(s, 1, n) {
			rep(t, 1, n) {
				g[kk][s][L[t]]+=g[tk][s][t];
				g[kk][s][R[t]+1]-=g[tk][s][t];
			}
			rep(t, 1, n) {
				g[kk][s][t]+=g[kk][s][t-1];
			}
			g[kk][s][s]=0;
		}
		rep(i, 1, q) que[i].sol(k);
	}
	//输出答案 
	rep(i, 1, q) printf("%d\n", que[i].ans);
}
```

时间复杂度为 $O(n^2m+mq)$，空间大概在 100MB 上下。

#### 其他的话

本题可以进一步对空间进行常数级别的优化，最后将空间控制在 54MB 上下，是通过只存储奇数步的 $f$ 数组来完成的，在计算答案的时候对 $f$ 进行一次转移。但是这种方案是用时间换空间，本质上并无区别，（并且肯定会被骂）所以就没有作为本题正解。

---

## 作者：喵仔牛奶 (赞：4)

没有打这场比赛，赛后写了 1h+ 写了[ N 多页测评记录](https://www.luogu.com.cn/record/list?pid=P8502&user=560516)的萌新来写一发题解。

设 $f_{i,j,k}$ 是 $i\to j$ 经过 $k$ 条路径的方案数，初始化 $f_{i,i,0}=1$。

有转移方程：

$$f_{i,j,k}=\sum_{j\in G_{t}}f_{i,t,k-1}$$

这个好像不太好优化，反一下：

相当于 $\forall_{t\in G_j}f_{i,t,k}+=f_{i,j,k-1}$，这个显然差分可以 $\mathcal{O}(1)$ 做。

然而题目要求不经过 $c$ 点，根据容斥原理，不经过 $c$ 点的路径等于所有路径数减去经过的路径数。

所有路径当然是 $f_{s,c,k}$。那从 $s$ 到 $t$ 经过 $c$ 点的路径怎么求呢？可以是 $\sum_{i=1}^{k}f_{s,c,i}\times f_{c,t,k-i}$ 吗？

不可以。因为 $f$ 会重复经过 $c$ 点，导致路径重复。我们发现问题在于重复上。所以设 $g_{i,j,k}$ 为 $i\to j$ 经过 $k$ 条边且不重复经过 $i$ 点的路径数。

这样，从 $s$ 到 $t$ 经过 $c$ 点的路径就是 $\sum_{i=1}^{k}f_{s,c,k-i}\times g_{c,t,i}$。不经过的路径就是：

$$f_{s,c,k}-\sum_{i=1}^{k}f_{s,c,k-i}\times g_{c,t,i}$$

那么 $g$ 怎么转移呢？同 $f$，只要每次转移完使 $g_{i,i,k}=0$ 即可。

这样 $10\text{pts}$ 就有了。

接下来要注意取模+空间+卡常。

首先这里 $f_{s,c,k-i}\times g_{c,t,i}$ 用龟速乘肯定直接爆炸，转 `long long` 乘再模就可以了。

然后注意差分有减的过程，也就是说有负数，模要 `(a%mod+mod)%mod`。

然后您发现您空间炸了，约是 $200\text{MB}$ 上下。

怎么办？只能用滚动数组。

但是这个 $f$ 和 $g$ 不能滚，询问要用。

那我们就把询问离线下来，滚完一层就更新。

但是 $f$ 和 $g$ 不能同时滚。因为一个是 $i$ 一个是 $k-i$，$k$ 每个询问还不一样。

但是 $200\text{MB}$ 滚一个剩 $100\text{MB}$ 好像够了，那就滚 $g$。

把 $g$ 滚一下，$k$ 是经过边的条数，$x$ 是 $k\operatorname{bitand}1$（即滚动数组本次的结果，$x\operatorname{xor}1$ 是上次），有：

$$g_{i,j,x}=\sum_{j\in G_{t}}g_{i,t,x\operatorname{xor}1}$$

然后再差分优化。

做 $100$ 次，因为 $M\leq100$。每次做完枚举 $Q$，将 $k_i\leq k$ 的更新。

然后注意，做 $g_{i,j,x}$ 的时候要清空 $g_{i,j,x\operatorname{xor}1}$。但是手动清空会 T，要用 `memset`。

但是还是炸了。因为取模常数太大。

我们发现如果 $a,b< p$，那么 $a+b-p<p$，可以把加法取模换成 `(x>mod)&&(x-=mod)` 的形式。

然后就可以 AC 了。

时间复杂度 $\mathcal{O}(n^2m+qm)$，空间复杂度 $O(n^2m+q)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 505, M = 105, Q = 1e5 + 5, mod = 998244353;
int f[M][N][N], g[2][N][N], L[N], R[N], n, m, now, q;
inline int upd(int x) {
	(x >= mod) && (x -= mod);
	return x;
} // 取模
struct node {
	int s, t, c, k, id, ans;
	inline void upd(int qwq) {
		ans -= 1LL * f[k - qwq][s][c] * g[qwq & 1][c][t] % mod; // 转 long long 乘
		ans = ::upd(ans + mod); // ::upd 是取模
	} // 减去一次经过 c 的路径
} s[Q];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i ++)
		cin >> L[i] >> R[i], f[0][i][i] = g[0][i][i] = 1; // 初始化
	for (int k = 1; k <= 100; k ++)
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				f[k][i][L[j]] = upd((f[k][i][L[j]] + f[k - 1][i][j]) % mod + mod);
				f[k][i][R[j] + 1] = upd(f[k][i][R[j] + 1] - f[k - 1][i][j] + mod);
			}
			for (int j = 1; j <= n; j ++)
				f[k][i][j] = upd(upd(f[k][i][j] + f[k][i][j - 1]) + mod);
		}
	for (int i = 1; i <= q; i ++) {
		cin >> s[i].s >> s[i].t >> s[i].c >> s[i].k, s[i].id = i;
		s[i].ans = f[s[i].k][s[i].s][s[i].t], s[i].upd(0);
	}
	for (int k = 1; k <= 100; k ++) {
		int now = k & 1, last = (k & 1) ^ 1; // now 是当前，last 的之前
		memset(g[now], 0, sizeof g[now]); // memset 常数小，暴力清空 TLE
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				g[now][i][L[j]] = upd(upd(g[now][i][L[j]] + g[last][i][j]) + mod);
				g[now][i][R[j] + 1] = upd(g[now][i][R[j] + 1] - g[last][i][j] + mod); // 记得取模
			}
			for (int j = 1; j <= n; j ++)
				g[now][i][j] = upd(upd(g[now][i][j] + g[now][i][j - 1]) + mod);
			g[now][i][i] = 0;
		}
		for (int i = 1; i <= q; i ++)
			if (k <= s[i].k) s[i].upd(k); // 更新答案
	}
	for (int i = 1; i <= q; i ++)
		cout << s[i].ans << '\n';
	return 0;
}
```

UPD：

其实如果把每个询问都保存一个 $f_1\sim f_m,g_1\sim g_m$ 空间复杂度可以做到 $\mathcal{O}(n^2+qm)$，但是好像差不多（？），这里懒得写了。

---

## 作者：Claire0918 (赞：0)

我们注意到恰经过 $m$ 条通道是具有阶段性的，这启示我们考虑 dp。

设 $f_{i, s, t}$ 表示恰经过 $i$ 条通道从 $s$ 走到 $t$ 的方案数。对于与 $t$ 直接相连的 $t'$，我们有刷表法的转移 $f_{i, s, t} \to f_{i + 1, s, t'}$，单次转移是 $\mathcal{O}(n)$ 的，总时间复杂度是 $\mathcal{O}(n^3m)$，需要优化。

我们注意到 $t'$ 的范围是一段区间，于是这转化为了序列区间加，全局查询的问题，考虑使用差分进行优化。

具体来说，我们记 $\{\Delta f_{i, s}\}$ 为 $\{f_{i, s}\}$ 的差分，即 $\Delta f_{i, s, t} = f_{i, s, t} - f_{i, s, t - 1}$。如果我们要将 $t' \in [l_t, r_t]$ 的 $f_{i + 1, s, t'}$ 都加上 $f_{i, s, t}$，等价于将 $\Delta f_{i + 1, s, l_t}$ 加上 $f_{i, s, t}$，将 $\Delta f_{i + 1, s, r_t + 1}$ 减去 $f_{i, s, t}$。我们在转移中只维护 $\{\Delta f_{i, s}\}$，可以做到单次 $\mathcal{O}(1)$，整体转移完成后再求$\{f_{i, s}\}$，做到了 $\mathcal{O}(n^2m)$ 的复杂度。

注意初始化为 $f_{0, s, s} = 1$。

综上，我们完整地解决了不考虑不能经过某个点的问题。

我们考虑解决整个问题，不难想到减去经过 $c$ 点的路径数量。直观地，我们枚举一个 $i \in [0, m]$，要求在 $i$ 步后其在 $c$ 点上。但是，这样会导致重复。如果一条路径多次经过 $c$ 点，那么在每一次经过时均被计算一次。

我们修改要求，要求路径最后一次经过 $c$ 在 $i$ 步后。我们需要维护 $g_{i, s, t}$ 表示在经过 $i$ 步后从 $s$ 到 $t$ 且不重复经过 $s$ 的方案数。这转移与 $f_{i, s, t}$ 是类似的，但是我们特别要求 $g_{i, s, s} = [i = 0]$，这是因为从 $s$ 经过若干步到 $s$ 但又不能重复经过 $s$ 显然是不可能的。

如果一条路径重复经过 $s$，我们记 $i$ 为其某一次重复经过 $s$ 时的移动距离，显然该路径的答案要从 $g_{i, s, s}$ 转移而来，但是我们总使得当 $i \neq 0$ 时 $g_{i, s, s} = 0$，所以一切希望重复经过 $s$ 的路径方案数都将在通过 $g_{i, s, s}$ 转移时被置为 $0$ 了，从而只保留了不重复经过 $s$ 的路径，转移是正确的。

这样，我们得出结论：经过 $m$ 条路径，从 $a$ 到 $b$ 且不经过 $c$ 的方案数为 $\displaystyle f_{m, a, b} - \sum_{i = 0}^{m} f_{i, a, c} \times g_{m - i, c, b} = f_{m, a, b} - \sum_{i = 0}^{m} f_{m - i, a, c} \times g_{i, c, b}$。

这时，我们开了 $2$ 个 $\mathcal{O}(n^2m) = 4\text{byte} \times 500^2 \times 100 = 1 \times 10^8\text{byte} \approx 100 \text{MB}$ 的数组，总共使用了至少 $200\text{MB}$ 的空间，不能通过 $128\text{MB}$ 空间限制的子任务。

我们希望可以对于 $f$ 或 $g$ 使用滚动数组，考虑对 $g$ 滚动，$f$ 不变。先处理 $f$，然后将所有询问离线下来，置它们的答案为 $f_{m, a, b} - f_{m, a, c} \times g_{0, c, b}$。随后处理 $g$，对于当前转移到的 $i$，一切满足 $m \geq i$ 的询问都需要减去 $f_{m - i, a, c} \times g_{i, c, b}$。显然这样完整计算了式子每一部分的贡献，并且我们只需要当前 $i$ 的 $g_{i, s, t}$，去掉了 $\mathcal{O}(m)$ 的一维，只需要一个 $100\text{MB}$ 的 $f$ 数组和一个大约只有 $1\text{MB}$ 的 $g$ 数组，可以通过 $128\text{MB}$ 限制。

时间复杂度 $\mathcal{O}(n^2m + qm)$，可以通过。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 500 + 10, maxm = 100, maxq = 1e5 + 10, mod = 998244353;

struct query_type{
    int a, b, c, m, res;
    query_type(){}
} query[maxq];

int n, q;
int l[maxn], r[maxn], f[maxm + 10][maxn][maxn], g[2][maxn][maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++){
        scanf("%d %d", &l[i], &r[i]);
        f[0][i][i] = g[0][i][i] = 1;
    }
    for (int i = 1; i <= maxm; i++){
        for (int s = 1; s <= n; s++){
            for (int t = 1; t <= n; t++){
                f[i][s][l[t]] = mod_add(f[i][s][l[t]], f[i - 1][s][t]);
                f[i][s][r[t] + 1] = mod_add(f[i][s][r[t] + 1], mod - f[i - 1][s][t]);
            }
            for (int t = 1; t <= n; t++){
                f[i][s][t] = mod_add(f[i][s][t], f[i][s][t - 1]);
            }
        }
    }
    for (int i = 1; i <= q; i++){
        scanf("%d %d %d %d", &query[i].a, &query[i].b, &query[i].c, &query[i].m);
        query[i].res = mod_add(f[query[i].m][query[i].a][query[i].b], mod - f[query[i].m][query[i].a][query[i].c] * g[0][query[i].c][query[i].b]);
    }
    for (int i = 1; i <= maxm; i++){
        mem(g[i & 1], 0);
        for (int s = 1; s <= n; s++){
            for (int t = 1; t <= n; t++){
                g[i & 1][s][l[t]] = mod_add(g[i & 1][s][l[t]], g[i & 1 ^ 1][s][t]);
                g[i & 1][s][r[t] + 1] = mod_add(g[i & 1][s][r[t] + 1], mod - g[i & 1 ^ 1][s][t]);
            }
            for (int t = 1; t <= n; t++){
                g[i & 1][s][t] = mod_add(g[i & 1][s][t], g[i & 1][s][t - 1]);
            }
            g[i & 1][s][s] = 0;
        }
        for (int j = 1; j <= q; j++){
            if (query[j].m >= i){
                query[j].res = mod_add(query[j].res, mod - (long long)f[query[j].m - i][query[j].a][query[j].c] * g[i & 1][query[j].c][query[j].b] % mod);
            }
        }
    }
    for (int i = 1; i <= q; i++){
        printf("%d\n", query[i].res);
    }

return 0;
}
```

---

## 作者：HPXXZYY (赞：0)

$\color{blue}{\texttt{[Solution]}}$

**这题最恶心的地方是卡空间**。

我们先考虑不卡空间时怎么做。

直接并不好做，我们考虑**正难则反**，即利用**容斥原理**。答案应为从 $a$ 没有任何限制经过 $m$ 条边到 $b$ 的方案数减去从 $a$ 经过 $m$ 条边到 $b$ 且必须经过 $c$ 的方案数。

自然地，我们会想到用 $f_{m,i,j}$ 表示从 $i$ 经过 $m$ 到 $j$ 的方案数。显然其初始条件 $f_{0,i,i}=1$。

不难得到，$f$ 的转移方程为：

$$f_{m,i,j}=\sum\limits_{k \to j}f_{m-1,i,k}$$

其中 $k \to j$ 表示节点 $k$ 可以到达节点 $j$。

很显然，由于每个节点可以到达的节点是一段连续的区间，我们可以用**差分**来优化我们的 $\text{dp}$。

表面上看，最终答案似乎就是

$$f_{m,a,b}-\sum\limits_{k=0}^{m} \left (f_{k,a,c} \times f_{m-k,c,b} \right )$$

但是，这样的计数是错误的。因为我们可以多次经过 $c$ 这个节点，而每一次经过节点 $c$ 都会被重复计数。比如在一条途径中，我们在 $3,7,9$ 次经过节点 $c$，那么我们在 $k=3,7,9$  时都会把这条途径计入。

怎样避免重复？我们可以强制从 $c$ 到 $b$ 的路径不能再经过 $c$。那这样会不会导致计数遗漏？不会，因为从 $a$ 到 $c$ 的路径还是可以重复经过 $c$ 的。

于是，我们可以新开一个数组 $g_{m,i,j}$ 表示从 $i$ 经过 $m$ 条边到 $j$ 但不能经过 $i$ 的方案数。$g$ 的转移和 $f$ 相似，只是 $g_{l,i,i}=0(l=1,2,\dots,m)$。

这样，最终答案应该为

$$f_{m,a,b}-\sum\limits_{k=0}^{m} \left (f_{k,a,c} \times g_{m-k,c,b} \right )$$

但是这题卡空间。

我们发现，$f$ 和 $g$ 在 $m$ 时的转移都只和 $(m-1)$ 有关。于是 $f$ 和 $g$ 完全可以重复利用，只需要开二维即可。这样是可以满足空间要求的。但是有个问题，就是我们不能随时询问随时回答，因为我们并没有保留任意的 $m$ 的状态信息。

怎么办？不能在线回答询问，那就**离线**！于是主体思路完成。

就**离线**这一点，这题的难度上了一个台阶。

$\color{blue}{\text{Code}}$

```cpp
const int mod=998244353;
inline void add(int &a,int b){
	a=(a+b>mod?a+b-mod:a+b);
}

const int N=510,M=105;
int l[N],r[N],n,q,m;
int f[2][N][N],g[2][N][N];

struct Query{
	int a,b,c,m,ans,f[M],g[M];
}Q[100010];

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&l[i],&r[i]);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&Q[i].a,&Q[i].b);
		scanf("%d%d",&Q[i].c,&Q[i].m);
		m=max(m,Q[i].m);
	}
	
	for(int i=1;i<=n;i++)
		f[0][i][i]=g[0][i][i]=1;//init
	
	for(int k=0;k<=m;k++){
		bool s=(k&1),t=(s^1);//s 表示这一维的信息，t 表示下一维
		
		for(int i=1;i<=q;i++){
			int a=Q[i].a,b=Q[i].b,c=Q[i].c;
			Q[i].f[k]=f[s][a][c];Q[i].g[k]=g[s][c][b];
			if (k==Q[i].m) Q[i].ans=f[s][a][b];
		}
		
		memset(f[t],0,sizeof(f[t]));
		memset(g[t],0,sizeof(g[t]));
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if (r[j]){//可转移 
					add(f[t][i][l[j]],f[s][i][j]);
					add(f[t][i][r[j]+1],mod-f[s][i][j]);
					add(g[t][i][l[j]],g[s][i][j]);
					add(g[t][i][r[j]+1],mod-g[s][i][j]);
				}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				add(f[t][i][j],f[t][i][j-1]);
				add(g[t][i][j],g[t][i][j-1]);
			}
			g[t][i][i]=0;
		}
	}
	
	for(int i=1;i<=q;i++)
		for(int j=0;j<=Q[i].m;j++)
			Q[i].ans=(Q[i].ans-1ll*Q[i].f[j]*Q[i].g[Q[i].m-j]%mod)%mod;
	
	for(int i=1;i<=q;i++){
		Q[i].ans=(Q[i].ans+mod)%mod;
		printf("%d\n",Q[i].ans);
	}
	
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

设出 $f_{i,j,k}$ 表示从 $i$ 到 $j$ 经过 $k$ 条边的方案数，列出方程
$$f_{i,j,k}= \sum\limits_{(l,j)}f_{i,l,k-1}$$

如何快速求和？观察到一个点所到达的点序号为一个区间，故可用刷表法，并用差分代替树状数组，以此去掉一个 $\log$ 的复杂度。

至于约束条件可以运用正难则反，去掉经过 $c$ 的情况。

注意 $f_{i,j,k}$ 并不代表只经过一次 $j$，因为可能从 $j$ 出发又回到 $j$ 再去 $k$。如果去掉经过 $c$ 的情况用 $f$ 减去 $f$ 相乘求和这样子算的话肯定会有重复。一般解决办法是选取一个基准点，这里选择最后一次经过 $c$ 的状态为基准点，只要最后一次经过 $c$ 的时候状态不一样那么总的状态就不一样，这样就不会减去重复的了。此时做法都是再开一个辅助数组，设 $g_{i,j,k}$ 约束其为最后一次经过 $j$ 的方案数，而且一般这种辅助数组的递推要用到原数组，本题中即为在 $f$ 的基础上将 $g_{i,j,j}$ 设置为 $0$ 即可。

于是在计算 $f$ 数组的基础上修改一次即可，得到

$f_{i,j,k}-= \sum\limits_{i=1}^k f_{i,c,i} \times g_{c,j,k-i}$

---

## 作者：littlez_meow (赞：0)

# 卡空间萌新也能看懂的题解TWT
玄学空间

[题目指路](https://www.luogu.com.cn/problem/P8502)

以下为避免下标看不清，用 $a[i][j][k]$ 等来表示 $a_{i,j,k}$。

## subtask 0~1
#### 分析
记 $dp[i][j]$ 表示现在在节点 $i$ 恰好走了 $j$ 步的方案数。

对于每次询问，初始状态为 $dp[a][0]=1$。

状态转移方程为 $\forall l_i\le t\le r_i,dp[t][k+1]+dp[i][k]\to dp[t][k+1]$。

把 $dp[t]$ 看作一个数列，上述状态转移方程可看作区间加，用差分优化掉一个线性。

另外，在每次转移时，保证 $\forall t,dp[c][t]=0$，即可求出不经过节点 $c$ 的路径数。

对于每次询问都计算一遍，在线回答，答案为 $dp[b][m]$。

时间复杂度 $O(Qmn)$；滚动数组滚掉第二维，空间复杂度为 $O(n)$。

#### 核心代码部分

```cpp
for(;Q;--Q){
	a=input(),b=input(),c=input(),m=input();
	F(i,1,n) dp[i][0]=0;
	dp[a][0]=1;
	F(i,0,m-1){
		F(j,1,n) dp[j][(i+1)&1]=0;
		F(j,1,n){
			if(j==c||!l[j]) continue;
			dp[l[j]][(i+1)&1]=(dp[l[j]][(i+1)&1]+dp[j][i&1])%MOD;
			dp[r[j]+1][(i+1)&1]=((dp[r[j]+1][(i+1)&1]-dp[j][i&1])%MOD+MOD)%MOD;
		}
		F(j,1,n) dp[j][(i+1)&1]=(dp[j][(i+1)&1]+dp[j-1][(i+1)&1])%MOD;
		dp[c][(i+1)&1]=0;
	}
	printf("%d",dp[b][m&1]),putchar('\n');
}
```

喜提[75分的TLE](https://www.luogu.com.cn/record/85281284)。

## subtask 2~3
为什么呢？对于每次询问，我们都重复计算了很多 $dp$ 值。如果能够一次算完，每次查询，就能过了。

既然这样，我们就再加一维。

记 $dp[i][j][k]$ 表示从节点 $i$ 到节点 $j$ 恰好走了 $k$ 步的方案数。

初始状态为 $dp[i][i][0]=1$。

状态转移方程为 $\forall l_j\le t\le r_j,dp[i][t][k+1]+dp[i][j][k]\to dp[i][t][k+1]$。

依然可以差分优化。

但是每次询问 $c$ 都不一样，我们怎么统计不经过 $c$ 的方案数呢？

正难则反，考虑容斥，答案为总数减必须经过 $c$ 的方案数。

根据乘法原理，必须经过 $c$ 的方案数为 $\sum_{i=0}^m dp[a][c][i]\times dp[c][b][m-i]$。

……吗？

很显然，我们重复算了几条路径。具体来说，如下图：

![重复路径](https://cdn.luogu.com.cn/upload/image_hosting/3cf4t72u.png)

这条路径被当成 $BCEDF+CA$ 和 $BC+CEDFA$ 等，被算了多次。

究其根本原因，就是我们在起点 $c$ 处走了一个环。

为此，记 $dp'[i][j][k]$ 表示从节点 $i$ 到节点 $j$ 恰好走了 $k$ 步且不重复经过 $i$ 的方案数。

其初始值和转移方程均与 $dp$ 一样，除了我们要保证 $dp'[i][i][k]=[k=1]$。

最后，答案为 $dp[a][b][m]-\sum_{i=0}^m dp[a][c][i]\times dp[c][b][m-i]$。

时间复杂度 $O(n^2m)$。

## subtask 4
上面的方法空间复杂度为 $O(n^2m)$，完，$200MB$。

每次询问都要查询以前的值，不能滚动数组。

既然要查询以前的值，那不如把询问离线，把每个询问所需的值存下来，再滚掉 $dp$ 和 $dp'$ 的第三维，此时空间复杂度为 $O(Qm)$。

虽然但是，这个看着区别不大的优化竟然能过。

也可以加上一些玄学优化：用 vector 存储所需值，当一个询问记录完时，马上算出答案，并释放 vector 的内存。

总之，本题通过。

## 附上代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(int i(a);i<=b;++i)
#define R(i,a,b) for(int i(a);i>=b;--i)
#define _ 0
using namespace std;
const int MOD=998244353;
short n,l[501],r[501],maxm;
int Q,dp[2][2][501][502];
inline int input(){
	int x;char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar());
	for(x=0;isdigit(ch);ch=getchar()) x=x*10+(ch^48);
	return x;
}
struct Meow{
	short a,b,c,m;
	int need0[101],need1[101],ans;
}ask[100001];
int main(){
	n=input(),Q=input();
	F(i,1,n) l[i]=input(),r[i]=input(),dp[0][0][i][i]=dp[1][0][i][i]=1;
	F(i,1,Q) ask[i].a=input(),ask[i].b=input(),ask[i].c=input(),ask[i].m=input(),maxm=max(ask[i].m,maxm);
	F(I,0,maxm){
		bool i=I&1;
		F(j,1,Q){
			ask[j].need0[I]=dp[0][i][ask[j].a][ask[j].c],
			ask[j].need1[I]=dp[1][i][ask[j].c][ask[j].b];
			if(ask[j].m==I){
				ask[j].ans=dp[0][i][ask[j].a][ask[j].b];
				F(k,0,ask[j].m) ask[j].ans=((ask[j].ans-(ll)ask[j].need0[k]*ask[j].need1[ask[j].m-k])%MOD+MOD)%MOD;
			}
		}
		memset(dp[0][i^1],0,sizeof(dp[0][i^1]));
		memset(dp[1][i^1],0,sizeof(dp[1][i^1]));
		F(k,1,n) if(l[k]) F(j,1,n){
			dp[0][i^1][j][l[k]]=(dp[0][i^1][j][l[k]]+dp[0][i][j][k])%MOD;
			dp[0][i^1][j][r[k]+1]=((dp[0][i^1][j][r[k]+1]-dp[0][i][j][k])%MOD+MOD)%MOD;
			dp[1][i^1][j][l[k]]=(dp[1][i^1][j][l[k]]+dp[1][i][j][k])%MOD;
			dp[1][i^1][j][r[k]+1]=((dp[1][i^1][j][r[k]+1]-dp[1][i][j][k])%MOD+MOD)%MOD;
		}
		F(j,1,n) F(k,1,n) dp[0][i^1][j][k]=(dp[0][i^1][j][k-1]+dp[0][i^1][j][k])%MOD,dp[1][i^1][j][k]=(dp[1][i^1][j][k-1]+dp[1][i^1][j][k])%MOD;
		F(j,1,n) dp[1][i^1][j][j]=0;
	}
	F(i,1,Q) printf("%d",ask[i].ans),putchar('\n');
    return ~~(0^_^0);//每日卖萌(1/1)
}
```

最后，临界数组万分注意，否则就会[这样](https://www.luogu.com.cn/record/85846991)……

完结撒花 OwO

---

