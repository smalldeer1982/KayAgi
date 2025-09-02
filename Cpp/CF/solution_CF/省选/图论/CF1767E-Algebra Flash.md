# Algebra Flash

## 题目描述

### 题目背景

Algebra Flash 2.2 刚刚发布！

更新日志：

- 全新游戏模式！

感谢您一直以来对游戏的支持！

就这？你略带失望地启动游戏，点进新的游戏模式，上面写着 "彩色平台"。


有 $n$ 个平台排成一列，编号从 $1$ 到 $n$。平台有 $m$ 种颜色，编号从 $1$ 到 $m$。第 $i$ 个平台的颜色是 $c_i$。

你从 $1$ 号平台开始，想要跳到 $n$ 号平台。在一次移动中，你可以从某个平台 $i$ 跳到平台 $i + 1$ 或 $i + 2$。

所有平台最初都未激活（包括平台 $1$ 和 $n$）。对于每种颜色 $j$，你可以支付 $x_j$ 枚金币来激活所有颜色为 $j$ 的平台。

你希望激活一些平台，然后从已激活的平台 $1$ 开始，跳过一些已激活的平台，到达已激活的平台 $n$。

要实现这个目标，你最少花费多少金币？

## 样例 #1

### 输入

```
5 3
1 3 2 3 1
1 10 100```

### 输出

```
11```

## 样例 #2

### 输入

```
5 3
1 3 2 3 1
1 200 20```

### 输出

```
21```

## 样例 #3

### 输入

```
4 2
2 2 1 1
5 5```

### 输出

```
10```

## 样例 #4

### 输入

```
10 10
3 8 6 2 10 5 2 3 7 3
9 7 4 2 1 8 2 6 2 2```

### 输出

```
15```

# 题解

## 作者：Alex_Wei (赞：19)

如果存在两个连续的平台未被激活，则不合法。

因此，存在相邻的颜色分别为 $i$ 和 $j$ 的平台，则在 $(i, j)$ 之间连边。在 $c_1$ 和 $c_n$ 连自环，则问题转化为选择点权和最小的点集，使得每条边至少被一个点覆盖。根据经典结论，它等价于点权和减去最大权独立集。

最大权独立集有一个非常经典的做法：枚举前 $n / 2$ 个点是否选择，对剩余 $n / 2$ 个点的状态记忆化搜索即可。

相关资料：[《浅谈信息学竞赛中的独立集问题》 - 学习笔记 - p_b_p_b](https://www.cnblogs.com/p-b-p-b/p/14200616.html)。

时间复杂度 $\mathcal{O}(n + 2 ^ {m / 2})$，**注意自环**。[代码](https://codeforces.com/contest/1767/submission/185594623)。

---

## 作者：Cxny (赞：15)

不用动脑子的做法。

$m$ 很小，尝试从颜色的角度来处理。

首先，$a_1$ 与 $a_n$ 必须选。

由于一次只能跳一步或两步，因此若 $a_i=a_{i-1}$，则 $a_i$ 必须选。

如果我们不选 $a_i$，则同样由于距离限制，$a_{i-1}$ 和 $a_{i+1}$ 必须选。

可以直接维护当前待确定的集合，枚举选或不选就行了。

最坏复杂度 $T(n)=T(n-1)+T(n-2)$，也就是 $O(Fib(m))$。其中 $Fib(m)$ 表示斐波那契数列第 $m$ 项，$m=40$ 时在 $10^8$ 左右。不开 $\text{O2}$ 最大点用时 $\text{889ms}$ ，足以通过本题。

vp 的时候用 `set` 维护集合多一只 $\log$，喜提 $\text{Hacked}$。

```cpp
const int maxn = 3e5 + 10;
int n, m, a[maxn], cost[maxn], ans = 1e9;
vector<int> qwq[50];
ll st, qaq[50];
void dfs(int res, int dep){
    if(res >= ans) return;
    if(!st) return ans = res, void();
    int u = __lg(lowbit(st)); qaq[dep] = st;
    st ^= (1ll << u), dfs(res + cost[u], dep + 1);
    for(int v : qwq[u]) if(st & (1ll << v)) res += cost[v], st ^= (1ll << v);
    dfs(res, dep + 1);
    st = qaq[dep], qaq[dep] = 0;
}
signed main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), st |= (1ll << a[i]);
    for(int i = 2; i <= n; i++) if(a[i] != a[i - 1]) qwq[a[i]].pb(a[i - 1]), qwq[a[i - 1]].pb(a[i]);
    for(int i = 1; i <= m; i++) sort(qwq[i].begin(), qwq[i].end()), qwq[i].erase(unique(qwq[i].begin(), qwq[i].end()), qwq[i].end());
    for(int i = 1; i <= m; i++) scanf("%d", &cost[i]);
    int www = 0;
    st ^= (1ll << a[1]), www += cost[a[1]];
    if(a[n] != a[1]) st ^= (1ll << a[n]), www += cost[a[n]];
    for(int i = 2; i < n; i++) if(a[i] == a[i - 1] && (st & (1ll << a[i]))) st ^= (1ll << a[i]), www += cost[a[i]];
    dfs(www, 0);
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Leasier (赞：4)

注意到当相邻两个都没选时一定不能从 $1$ 跳到 $n$。

转化一下，则有：

- $a_1, a_n$ 必须选。
- $\forall 2 \leq i \leq n$，$a_i, a_{i - 1}$ 至少选一个。

“至少选一个”的关系让我们联想到**最小点覆盖**。

将 $x$ 必须选转化为一条边 $(x, x)$，$x, y$ 至少选一个转化为一条边 $(x, y)$，则我们要求的就是这张 $m$ 个点的图的带权最小点覆盖，其中点 $i$ 的权值即为 $x_i$。

这是一张一般的图，但最小点覆盖等于权值和减去最大独立集仍然成立，现在我们希望求最大独立集。

考虑状压 dp。设 $dp_S$ 表示 $S$ 集合的最大独立集权值和。

初值：$dp_{\emptyset} = 0$。

转移：$dp_S = \max(dp_{S - \{\min(S)\}}, [\min(S) \not\in edge_{\min(S)}](dp_{S - \{\min(S)\} - edge_{\min(S)}} + x_{\min(S)}))$，其中 $edge_x$ 表示 $x$ 的出边集合。

答案：$dp_{\{1, 2, \cdots, m\}}$。

用 map 记忆化搜索可以得到一个时间复杂度为 $O(n + m 2^{\frac{m}{2}})$ 的做法。

证明：设有 $n$ 个点，$\min(S) \leq \frac{n}{2}$ 时只有 $2^{\frac{n}{2}}$ 种情况，$\min(S) > \frac{n}{2}$ 时只包含后 $\frac{n}{2}$ 个点，则也只有 $2^{\frac{n}{2}}$ 种情况。

代码：
```cpp
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;

int c[300007], x[47];
ll edge[300007];
map<ll, ll> mp;

inline void add_edge(int start, int end){
	edge[start] |= 1ll << (end - 1);
	edge[end] |= 1ll << (start - 1);
}

inline ll lowbit(ll x){
	return x & (-x);
}

ll dfs(ll s){
	if (s == 0) return 0;
	if (mp.count(s)) return mp[s];
	int small = log2(lowbit(s)) + 1;
	ll ans = dfs(s ^ (1ll << (small - 1)));
	if (!(edge[small] >> (small - 1) & 1)) ans = max(ans, dfs(s ^ (1ll << (small - 1)) ^ (s & edge[small])) + x[small]);
	return mp[s] = ans;
}

int main(){
	int n, m;
	ll sum = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> c[i];
	}
	add_edge(c[1], c[1]);
	add_edge(c[n], c[n]);
	for (int i = 2; i <= n; i++){
		add_edge(c[i], c[i - 1]);
	}
	for (int i = 1; i <= m; i++){
		cin >> x[i];
		sum += x[i];
	}
	cout << sum - dfs((1ll << m) - 1);
	return 0;
}
```

---

## 作者：xianggl (赞：4)

题意：

有一个长度为 $n$ 的平台，你需要从 $1$ 开始走到 $n$。

每一次可以向前 $1$ 或 $2$ 步。

每个格子有个颜色 $a_i$，共 $m$ 种，每一种有花费 $x_i$，你需要买下你经过的所有颜色。

求最小花费。

$1 \leq n \leq 3 \times 10 ^ 5, 1 \leq m \leq 40$

题解：

先考虑什么样的方案可以满足条件。

容易发现，相邻两个格子至少要有一个被买。

注意到 $m \leq 40$，考虑折半，枚举前 $m / 2$ 种颜色被买的情况，找到后 $m / 2$ 种颜色最小花费。

对于前面每一种颜色，预处理与它相邻的前/后半的颜色，记为 $s1/s2$。

对于一个前半部分状态 $i$，若 $j (\leq m / 2)$ 没有被买，则 $s1[j]$ 必须出现在 $i$ 中，据此可以判定 $i$ 是否合法。（仅考虑相邻颜色都 $\leq m / 2$）

同样，若 $j (\leq m / 2)$ 没有被买，$s2[j]$ 必须出现在后半部分的状态中，据此可以得到后半部分至少要哪些颜色。

会发现此时只有相邻颜色都 $> m / 2$ 的情况没有判，那么类似的，我们预处理出所有后半部分的合法状态，然后高维后缀 $\min$。

时间复杂度 $O(2 ^ {m / 2} \times (m / 2))$。

注意细节， $1$ 和 $n$ 都必须要买。

Code：

```
#include <bits/stdc++.h>
#define ri register int
#define i64 long long
using namespace std;
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector<int>a(n);
	for(ri i=0;i<n;i++)scanf("%d",&a[i]),--a[i];
	vector<int>cost(m);
	for(ri i=0;i<m;i++)scanf("%d",&cost[i]);
	if(m==1)return !printf("%d\n",cost[0]);
	int mid=m/2,left=m-mid;
	vector<int>s1(m),s2(m);
	for(ri i=0;i<n;i++) {
		if(i>0) {
			int x=a[i-1];
			if(x<mid)s1[a[i]]|=1<<x;
			else s2[a[i]]|=1<<(x-mid);
		}
		if(i<n-1) {
			int x=a[i+1];
			if(x<mid)s1[a[i]]|=1<<x;
			else s2[a[i]]|=1<<(x-mid);
		}
	}
	const i64 Inf=1e18;
	vector<i64>suf(1<<left);
	for(ri i=0;i<(1<<left);i++) {
		i64 cnt=0;
		int ok=1;
		for(ri j=0;j<left;j++) {
			if(!(i>>j&1))ok&=(i&s2[j+mid])==s2[j+mid];
			else cnt+=cost[j+mid];
		}
		suf[i]=ok?cnt:Inf;
	}
	for(ri i=0;i<left;i++)
		for(ri j=0;j<(1<<left);j++)
			if(!(j>>i&1))suf[j]=min(suf[j],suf[j^(1<<i)]);
	i64 ans=Inf;
	for(ri i=0;i<(1<<mid);i++) {
		i64 cnt=0;
		int ok=1;
		for(ri j=0;j<mid;j++) {
			if(!(i>>j&1))ok&=(i&s1[j])==s1[j];
			else cnt+=cost[j];
		}
		if(a[0]<mid)ok&=(i>>a[0])&1;
		if(a[n-1]<mid)ok&=(i>>a[n-1])&1;
		if(!ok)continue;
		int base=0;
		for(ri j=0;j<mid;j++)
			if(!(i>>j&1))base|=s2[j];
		if(a[n-1]>=mid)base|=1<<(a[n-1]-mid);
		if(a[0]>=mid)base|=1<<(a[0]-mid);
		ans=min(ans,suf[base]+cnt);
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：tai_chi (赞：3)

可以在 [cnblogs](https://www.cnblogs.com/tai-chi/p/18411625) 中阅读。

$m \le 40$ 的数据范围提示让我们往颜色种类上考虑。

由题每次可以跳 $1$ 或 $2$ 格，即存在一条从 $1$ 到 $n$ 的路径的充要条件是**不存在两个相邻的未激活格**。换句话说，对任意两个相邻的格子都必须选择至少一个激活。

任意两个，至少一个，这样的条件使我们联想到最小权点覆盖，我们在 $1$ 号和 $n$ 号连自环，其他点相邻的颜色连边，问题转化为求这个图的最小点覆盖。

一个经典结论是最大权独立集 + 最小权点覆盖 = 点权和。最大权独立集可以用记忆化搜索的方式实现。

具体地，设 $f_S$ 表示集合 $S$ 的最大权独立集，则有转移：

$$f_S = \max \left\{ f_{S- \left\{ p \right\} },f_{S- \left\{ p \right\} -edge(p)}  \right\}$$

其中 $p$ 表示集合中一个点，$edge(p)$ 表示与 $p$ 有连边的点集。

但是 $m \le 40$，怎么开的下？用 `std::map` 等工具可以动态开记忆化数组，而状态数的转移满足 $G(m) \le G(m-1)+G(m-2)$，最劣情况下是一个斐波那契数列，也就是说 $G(m) \le O(1.618^m)$，$m=40$ 时在 $2 \times 10^8$ 的级别，而实际上远远跑不满，时间空间都可以接受。

[code](https://codeforces.com/contest/1767/submission/280870269)，使用 `__pbds::gp_hash_table` 可以跑得更快。

实际上还有一种做法，就是对高 $20$ 位爆搜，低 $20$ 位记忆化，这样做保证了复杂度是 $O(n+2^ \frac{m}{2})$，而且避免了开 `map` 等时空消耗大的操作，实测也跑得更快。

[code](https://codeforces.com/contest/1767/submission/280922823)

---

## 作者：arundo (赞：3)

CF1767E Algebra Flash 题解。

因为 $m\le 40$ 而想到 meet in the middle。

首先发现，合法条件即为 $\forall i\in [2,n]$，$c_{i-1}$ 和 $c_i$ 中至少有一个被选择。

将颜色拆成前一半和后一半各 $m\over 2$ 种。对于每一半，枚举每个颜色的选择与否，判断是否与合法条件矛盾。得到两个合法选择集合 $S$ 与 $T$。

枚举 $S$ 中每个方案，再枚举后一半中的颜色。可以根据前一半的选择与否，判断出该颜色此时是否必须被选择。

如果此时将后一半颜色的选择与否看成二进制位，那么此时可用的 $T$ 集合的方案构成后缀 $\min$ 形式。只需要提前对 $T$ 做预处理即可。

时间复杂度 $O(n+2^{m\over 2}m)$。实现难度低。

---

## 作者：Lgx_Q (赞：2)

$m=40$，这种数据范围，怎么可能不是折半算法？

把 $m$ 种颜色分成两半，左边 $k$ 种颜色，右边 $m-k$ 种。

先独立考虑左边和右边的答案。怎么算就是直接二进制枚举，常数小。

如何判断一个状态 $i$ 是否合法，我们不需要跑一遍所有平台，而是可以建图。发现，对于原来 $n$ 个平台，相邻两个平台中不能全部不买，我们可以把相邻两个平台的颜色连边，然后可以算最多可以留下不买的颜色的最大价值，总代价减一下就是答案。

这其实就是算一张图的带权最大独立集，设 $p_u$ 为颜色 $u$ 连向的点集合。对于状态 $i$，枚举 $i$ 中的每一个颜色 $u$，判断 $p_u$ 和 $i$ 是否有交集即可。

既然左右两边的独立答案都算完了，那么接下来要合并两边的答案。

枚举一遍的颜色状态 $i$，那么我们不难算出另一边不能选择的颜色集合 $j$，把 $j$ 一取反就是另一边可选的颜色集合。我们需要快速知道在这个可选的颜色集合中的最大独立集，可以直接 $sos\space dp$。

---

## 作者：Rem_CandleFire (赞：1)

题意比较显然，我们注意到每一次只能从 $i$ 移动到 $i+1$ 或 $i+2$ 这两个位置的其中一个。所以当这两个位置同时没有激活时一定不可能到达位置 $n$。若记数组 $col$ 表示颜色，则 **$col_{i+1},col_{i+2}$ 一定会激活其中一个，且 $col_1,col_n$ 一定会激活**。

一般的，对于相邻的两个位置 $i,i+1$，我们连边 $(col_i,col_{i+1})$。那么对于整个图，每条边至少要选一个点，则是经典的最小点覆盖问题。特殊的，建立自环 $(col_1,col_1)$ 和 $(col_n,col_n)$ 表示必选。

最小点覆盖可以转化为最大权独立集问题，且因为颜色数 $m\le 40$，所以虽然这是一个一般图，但是可以通过 DP 解决问题。

套路地，设当前考虑的点集为 $S$，对于一个点 $u$，以 $64$ 位整数的方式存储连边情况（类似于邻接表），设为 $E_u$。设 $f_S$ 表示当前考虑点集 $S$ 的最大权独立集。

定义一个点 $u$ 的邻域 $N(u)$ 为跟该点有连边的点的集合，形式化地，$N(u)=\{v\in V|(u,v)\in E\}$，此处 $E$ 为边集，$V$ 为点集。

于是对于一个 $S$，我们不妨从低到高考虑每一位是 $1$ 的情况，保证不重不漏。

对于取出来的点 $u$，我们分别考虑这个点选不选，若不选直接除去，若选则除去这个点和它的邻域。

$$f_S=\max\{f_{S-u},f_{S-u-N(u)}+cost_u\}$$

其中 $cost_u$ 表示选择颜色 $u$ 的代价，符号 $-$ 表示在某个集合中除去某个集合或元素。

我们可以通过 STL 里的 map 进行记忆化搜索，最终的答案就是 $\sum cost_i-f_V$，$V$ 为点集，在本题中可以用整数表示为 $(1<<m)-1$。

注意：左移时要写 `1ll<<`，否则会 WA。 

[AC code](https://www.luogu.com.cn/paste/701znqmb)

---

## 作者：SmileMask (赞：0)

考虑给定集合如何判断是否合法，发现合法条件为当且仅当无连续的未激活点，本质为将相邻颜色连边，答案等于权值总和减去最大权独立集，考虑如何求最大权独立集。

因为 ~~一般图最大独立集是NPC~~ $m\le 40$，不妨考虑分别枚举前 $\frac{m}{2}$ 个选择的集合，后 $\frac{m}{2}$ 个选择的集合，然后合并。

记 $G_i$ 为颜色 $i$ 相邻的集合，不妨预处理前 $\frac{m}{2}$ 个，记 $S$ 为选择的集合，若该集合合法条件为所选点的 $G$ 与 $S$ 无交，记 $f_S$ 为该集合的权值

对于后 $\frac{m}{2}$ 个，记 $T$ 为选择的集合，合法条件同上，同时记录 $P$ 为所有 $G$ 补集的交集，即和所选点不相邻的集合，将答案与权值和加 $P$ 的子集 $Q$ $\max f_Q$，后者可以 SOSDP 预处理，总复杂度为 $O(\frac{m}{2}\times 2^{\frac{m}{2}})$。

---

## 作者：chroneZ (赞：0)

将序列视为一条链，链的两端连自环边，则题目所求即为选择一个代价最小的颜色集，使得这一颜色集覆盖了图的所有边。

最小点覆盖的补集为最大独立集，故考虑最大独立集。具体地，我们对颜色建立一张 $m$ 个点的图，点 $i, j$ 连边当且仅当存在 $c_k = i$ 且 $c_{k + 1} = j$（特别地，颜色 $c_1, c_n$ 连自环）。

如何求 $m(m \leq 40)$ 个点的图的最大权独立集呢？有[经典做法](https://www.cnblogs.com/p-b-p-b/p/14200616.html)如下：对只含前 $\frac m 2$ 个点的状态记忆化，剩余状态直接枚举后 $\frac m 2$ 的点是否被选。前后部分都有至多 $2 ^ {\frac m 2}$ 种可能，故复杂度为 $\Theta(2 ^ {\frac m 2})$。

总复杂度 $\Theta(n + 2 ^ {\frac m 2})$，注意自环。

```cpp
// Such a destiny was not desired.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int N = 3e5 + 5, M = 40 + 5;
int n, m, c[N], w[M];
ll adj[M]; bool ban[M];
int f[1 << 20];

int dfs(ll S) {
  if(!S) return 0;
  if(S < (1 << (m / 2)) && ~f[S]) return f[S];
  int t = __lg(S);
  ll T = S ^ (1ll << t);
  int res = dfs(T);
  if(!ban[t + 1]) res = max(res, w[t + 1] + dfs(T ^ (adj[t + 1] & T)));
  if(S < (1 << (m / 2))) f[S] = res;
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  memset(f, -1, sizeof(f));
  cin >> n >> m;
  for(int i = 1; i <= n; i++) cin >> c[i];
  for(int i = 1; i <= m; i++) cin >> w[i];

  for(int i = 1; i < n; i++) {
    adj[c[i]] |= 1ll << (c[i + 1] - 1);
    adj[c[i + 1]] |= 1ll << (c[i] - 1);
  }
  for(int i = 1; i <= m; i++) {
    if(adj[i] >> (i - 1) & 1) {
      ban[i] = true;
    }
  }
  ban[c[1]] = ban[c[n]] = true;

  cout << accumulate(w + 1, w + m + 1, 0) - dfs((1ll << m) - 1) << "\n";
}
```

---

## 作者：lfxxx (赞：0)

限制等价于第一个颜色与最后一个必选，且相邻两个颜色至少选一个，考虑相邻颜色连边后问题变为一般图上最小点覆盖。

因为 $\frac{40}{2} = 20$ 刚好是可以状压的范围，考虑将颜色划分为两半，令前一半选出的颜色集合为 $S$ 后一半则为 $T$，显然对于集合内的限制暴力枚举并判断是否合法即可，这一个部分时间复杂度是 $O(m^2 \times 2^{\frac{m}{2}})$ 的，常数小的逆天。接下里考虑横跨两个集合的限制，对于 $u \not \in S$，显然对于任意 $(u,v) \in E$ 的 $v$ 而言，其必须要被选择，我们定义 $e_u = \cup_{(u,v) \in E} v$，则有 $e_u \in T$，将所有选出的 $e_u$ 取并之后，对 $T$ 的限制变变为 $T' \in T$，这个部分简单的子集 dp 即可。

最后总复杂度是 $O(n + m^2 \times 2^{\frac{m}{2}})$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int Min[1<<20];
int n,m;
int a[maxn];
int vis[maxn],x[maxn];
pair<int,int> e[maxn][2];//内部边
int tot[2];
int E[maxn];
int S[1<<20],T[1<<20];
int use[40][40];
int ex;
//[0 m/2) [m/2 m)
int main(){
    memset(S,0x3f3f3f3f,sizeof(S));
    memset(T,0x3f3f3f3f,sizeof(T));
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]--;
    for(int i=0;i<m;i++) cin>>x[i];
    vis[a[1]]=1;
    vis[a[n]]=1;
    if(m==1){
        cout<<x[0]<<'\n';
        return 0;
    }
    for(int i=1;i<n;i++){
        int u=a[i];
        int v=a[i+1];
        if(use[u][v]==1) continue;
        use[u][v]=use[v][u]=1;
        if(u==v){
            vis[u]=1;
            continue;
        }
        if(u<m/2&&v<m/2){
            e[++tot[0]][0]=make_pair(u,v);
        }else if(u>=m/2&&v>=m/2){
            e[++tot[1]][1]=make_pair(u-m/2,v-m/2);
        }else{
            if(u>v) swap(u,v);
            //u<=v
            E[u]|=(1<<(v-m/2));
        }
    }
    for(int i=0;i<m;i++){
        if(vis[i]==1){
            ex+=x[i];
            x[i]=0;
        }
    }
    for(int v=0;v<(1<<(m/2));v++){
        bool flag=true;
        for(int i=1;i<=tot[0];i++){
            if((!((1<<e[i][0].first)&v))&&(!((1<<e[i][0].second)&v))){
                flag=false;
                break;
            }
        }
        if(flag==false) continue;
        S[v]=0;
        for(int i=0;i<m/2;i++)
            if((1<<i)&v) S[v]+=x[i];
    }
    for(int v=0;v<(1<<(m-m/2));v++){
        bool flag=true;
        for(int i=1;i<=tot[1];i++){
            if((!((1<<e[i][1].first)&v))&&(!((1<<e[i][1].second)&v))){
                flag=false;
                break;
            }
        }
        if(flag==false) continue;
        T[v]=0;
        for(int i=0;i<m-m/2;i++)
            if((1<<i)&v) T[v]+=x[i+m/2];
    }
    //T 的信息向子集传递
    for(int i=0;i<(m-m/2);i++){
        for(int v=(1<<(m-m/2))-1;v>=0;v--){
            if((1<<i)&v) T[v^(1<<i)]=min(T[v^(1<<i)],T[v]);
        }
    }
    int ans=0x3f3f3f3f;
    for(int v=0;v<(1<<m/2);v++){
        int v1=0;
        for(int i=0;i<(m/2);i++)
            if(!((1<<i)&v)) v1|=E[i];
        ans=min(ans,S[v]+T[v1]+ex);
    }
    cout<<ans<<'\n';
    return 0;
}

```

---

