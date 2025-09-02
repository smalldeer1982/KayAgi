# [AGC028C] Min Cost Cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc028/tasks/agc028_c

$ N $ 頂点の重み付き有向グラフがあります。 各頂点には $ 2 $ つの整数が書かれており、頂点 $ i $ には $ A_i $ と $ B_i $ が書かれています。

このグラフには、任意の $ 1\ \leq\ x,y\ \leq\ N $ について 頂点 $ x $ から頂点 $ y $ へ向かう辺があり、その重みは $ {\rm\ min}(A_x,B_y) $ です。

このグラフの有向サイクルであって、すべての頂点をちょうど $ 1 $ 度ずつ通るものを考えます。 そのようなサイクルの辺の重みの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ B_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

頂点 $ 1→3→2→1 $ というサイクルを考えると、その辺の重みは、$ {\rm\ min}(A_1,B_3)=1 $, $ {\rm\ min}(A_3,B_2)=2 $, $ {\rm\ min}(A_2,B_1)=4 $ となり、 その総和は $ 7 $ になります。 辺の重みの総和を $ 7 $ より小さくすることは出来ないので、答えは $ 7 $ になります。

## 样例 #1

### 输入

```
3
1 5
4 2
6 3```

### 输出

```
7```

## 样例 #2

### 输入

```
4
1 5
2 6
3 7
4 8```

### 输出

```
10```

## 样例 #3

### 输入

```
6
19 92
64 64
78 48
57 33
73 6
95 73```

### 输出

```
227```

# 题解

## 作者：Kinandra (赞：11)

标签: 构造.

#### Part 1

显然每个 $a_i,b_i$ 对答案最多贡献一次. 

考虑判断一个大小为 $n$ 的 $a, b$ 的集合 $T$ 是否可作为答案. 我们从构造的角度入手, 一条有向边 $(u,v)$ 可能出现在回路中必须满足: $a_u,b_v$ 中恰好有一个在 $T$ 中, 将 $n$ 个**点**分成下述 $4$ 类:

- `00`: $a_i\notin T,b_i\notin T$ 
- `01`: $a_i\notin T,b_i\in T$
- `10`: $a_i\in T,b_i\notin T$ 
- `11`: $a_i\in T,b_i\in T$

显然所有的 `01` 可以首尾相连, 缩点后视为一个新的 `01` , `10` 同理.

若存在 `11` 的点, 则 `00` 的点与 `11` 的点数量相同, 我们构造一个这样的回路:  `01`  ->  `11`  -> `10` -> `00` 和`11` 交错相连, 集合 $T$ 合法.

此外, 若 $n$ 个点缩成一个点(全为 `01` 或全为`10` ) , 集合 $T$ 也合法.

可以证明其他情况均不合法.

#### Part 2 

既然知道如何判断某个 $T$ 是否合法, 本题就水到渠成了. 

考虑答案的一个下界: 将 $a,b$ 放入一个数组 $p$ 内排序, 前 $n$ 项的和. 判断是否合法, 合法即为答案.

若不合法(此时每个点的 $a,b$ 恰好有一个属于 $T$ ) , 则抬高下界, 去掉 $p_n$ , 加上 $p_{n+1}$ . 再次判断是否合法, 合法即为答案.

若仍然不合法(此时知 $p_n$ 和 $p_{n+1}$ 为同一个点的 $a,b$ ), 接下来有两种抬高下界的方式: 去掉 $p_{n-1}$ , 加上 $p_n$ , 去掉 $p_{n+1}$ , 加上 $p_{n+2}$ . 发现这两种方式都必定合法, 取最小值作为答案即可.

时间复杂度 $O(n\log n)$ .

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, top;
struct P {
    int v, p, t;
} p[200005];
bool cmp(P a, P b) { return a.v < b.v; }
int sum[2], vis[200005], flg;
int main() {
    n = read();
    for (int i = 1; i <= n; ++i)
        p[++top] = (P){read(), i, 0}, p[++top] = (P){read(), i, 1};
    sort(p + 1, p + 1 + top, cmp);
    long long res = 0;
    for (int i = 1; i <= n; ++i)
        sum[p[i].t]++, res += p[i].v, flg |= (++vis[p[i].p] > 1);
    if (flg || max(sum[0], sum[1]) == n) return printf("%lld\n", res), 0;
    res += p[n + 1].v - p[n].v, sum[p[n].t]--, sum[p[n + 1].t]++;
    if (p[n].p != p[n + 1].p || max(sum[0], sum[1]) == n)
        return printf("%lld\n", res), 0;
    printf("%lld\n", res + min(p[n + 2].v - p[n + 1].v, p[n].v - p[n - 1].v));
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}
```

---

## 作者：installb (赞：10)

## AGC028C

这题首先要切换角度，对着这个哈密顿回路瞪没啥用，我们考虑转化成**每一个点的贡献**。

我们任意挑选可行方案出来，发现每一个点 $u$ （假设 $from$ 连向它，它连向 $to$）的贡献只有四种情况：
- $a_u<b_{to},b_u<a_{from}$，这个点选取 $a_u$ 和 $b_u$ 都计入答案。
- $a_u<b_{to},b_u>a_{from}$，这个点选取 $a_u$ 都计入答案。
- $a_u>b_{to},b_u<a_{from}$，这个点选取 $b_u$ 都计入答案。
- $a_u>b_{to},b_u>a_{from}$，这个点 $a_u$ 和 $b_u$ 都不计入答案。

同时满足：
- 选取的数（$a$ 被选的数量与 $b$ 被选的数量之和）共计 $n$ 个。

接下来我们从一个选取方案回推构图（哈密顿回路）方案。第一个想法是选取最小的 $n$ 个数，但是这样是不对的，因为这样的选取方式不一定能对应一个方案。

我们看哈密顿回路中一条边的意义，为起点的 $a$ 和终点的 $b$ 选取较小的那个，这里我们可以采用一个技巧，把这个条件转化为**起点的 $a$ 和终点的 $b$ 中选取且仅选取一个**。

为什么这样正确？我们观察这样造成的多出来的一系列本应该不合法方案，发现如果这条边如果取另一个数答案一定更优，也就是说这些方案虽然不合法但是**一定不能成为答案**，所以，无所谓啦。

后面就简单了。

给出结论，只有这三种方案存在对应方案：
- 全选 $a$
- 全选 $b$
- 至少存在一个点 $a$ 和 $b$ 都被选择

前两种显然，不证了。

第三种口胡一下。  
我们把左边那列视为 $a$，右边那列视为 $b$，选取的数为正方形，未选取的数为圆形。  
我们要连 $n$ 条边，连成一个环，一条边必须连接一个取和一个不取。

如果一部分选 $a$，一部分选 $b$，那么任意一个选 $a$ 的点和任意一个选 $b$ 的点是连不起来的，这个图不可能连通，所以不行。

如果有 $k$ 个都选，必然也有 $k$ 个都不选，这里再分四种情况：  
- 全是都选或都不选

- 都选 + 只选 $a$
- 都选 + 只选 $b$ 
和上一种本质一样。
![](https://cdn.luogu.com.cn/upload/image_hosting/j5lz4nyi.png)  
- 都选 + 只选 $a$ + 只选 $b$
![](https://cdn.luogu.com.cn/upload/image_hosting/575grvxc.png)  

具体做法嘛。。前两个特判，后一种枚举一个强制两个都选，剩下所有数中的贪心选取最小的 $n-2$ 个，因为其它点的选择是无所谓的。

这里先最小的 $n$ 个全扔小根堆里，然后看每一个点强制双选的时候，它的 $a$ 和 $b$ 有几个数是在小根堆里，记为 $k$，$k$ 只能是 $0$ 或 $1$ 或 $2$，用 $a$ 和 $b$ 中不在小根堆里的数之和加上小根堆中最小的 $n-k$ 个数之和（这个可以预处理）更新答案。

代码写丑了，建议你们别看，我觉得前面思路已经讲清楚了。

```cpp
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;

struct node{
	LL id,lr,val;
	bool operator <(const node &nd)const{
		return nd.val > val;
	}
};
priority_queue <node> q;

node make_node(LL id,LL lr,LL val){
	node ret; ret.id = id; ret.lr = lr; ret.val = val; return ret;
}

LL n,l[500005],r[500005],sl = 0,sr = 0;
LL in[500005][2] = {0};
LL h[500005],hd[500005],sum = 0,ans = INF;

int main(){
    ios::sync_with_stdio(false);
	cin >> n;
	for(LL i = 1;i <= n;i ++){
		cin >> l[i] >> r[i]; sl += l[i]; sr += r[i];
		in[i][0] = 1; in[i][1] = 1;
		q.push(make_node(i,0,l[i]));
		if(q.size() > n){ in[q.top().id][q.top().lr] = 0; q.pop(); }
		q.push(make_node(i,1,r[i]));
		if(q.size() > n){ in[q.top().id][q.top().lr] = 0; q.pop(); }
	}
	for(LL i = 1;i <= n;i ++){
		h[i] = q.top().val; sum += h[i]; hd[i] = q.top().id;
		q.pop();
	}
	for(LL i = 1;i <= n;i ++){
		LL tmp = sum,tt = 0;
		if(!in[i][0] && !in[i][1]){
			tmp += l[i]; tmp += r[i];
			tmp -= h[1]; tmp -= h[2];
		}
		if(!in[i][0] && in[i][1]){
			tmp += l[i];
			tmp -= (hd[1] == i ? h[2] : h[1]);
		}
		if(!in[i][1] && in[i][0]){
			tmp += r[i];
			tmp -= (hd[1] == i ? h[2] : h[1]);
		}
		ans = min(ans,tmp);
	}
	ans = min(ans,min(sl,sr));
	cout << ans << endl;
	return 0;
}
```

这题挺有意思。

---

## 作者：空气树 (赞：4)

不是很难的题，但是挺有趣。提供一个比较清新的思路。

发现难以直接贪心。于是首先思考合法条件。

设 $(x,y)$ 表示一个点的 $a$ 和 $b$ 是否产生贡献。$x=1$ 则代表 $a$ 有贡献；$y$ 同理。显然 $1$ 的总数是 $n$。

手玩可以得到，$(1,0)$ 之间可以直接放一起，缩成一个 $(1,0)$；$(0,1)$ 也同理。剩下就需要 $(1,1)$ 来连接了。发现除了全 $(1,0)$ 或全 $(0,1)$ 的情况，至少要存在一个 $(1,1)$，且 $(1,1)$ 的个数需要不少于 $(0,0)$ 的个数。这就是合法的充要条件。

想构造证明的话，就只需要知道 $(0,1),(0,1),(0,0),(1,0),(1,0)$ 这样的结构等价于 $(0,0)$ 即可。

那么归纳整理一下：首先特殊做掉所有点都是 $(1,0)$ 和都是 $(0,1)$ 的情况。设 $u\ge 1$ 表示 $(1,1)$ 的个数。那么根据总共会选 $n$ 个 $1$ 可以得到 $(0,0)$ 的个数为 $n-u-(n-2\times u)=u$，换而言之，限制直接只剩下 $u\ge 1$ 了。

判掉特殊情况的问题就转换成了给你 $n$ 对 $(a,b)$。共选出 $n$ 个数，并且至少一对 $(a,b)$ 必须全选。求总和最小值。

这个问题可以考虑贪心。考虑按 $\max(a,b)$ 从排序。那么最小值一定优。

证明考虑两个点 $i,j$ 看谁钦定全选更优。如果是所有数都选那么无意义不考虑；如果只选 $3$ 个数，那么相当于比较 $-\max(a_i,b_i)$ 和 $-\max(a_j,b_j)$ 的大小，符合排序；如果只选 $2$ 个数，则可归于下面的特殊情况。

特殊情况：所有数对都有一个数在前一半小，一个数在后一半小。因为这样可能会让我们所排序的最小数对，两个数都可以不选（排名为 $n$ 和 $n+1$）。那么只需要再做一遍次小值即可。

实现代码时，可以直接枚举最小值，次小值，做两遍。

当然，利用一定选 $n$ 个数的鸽雀原理，能直接分讨特殊情况。


---

## 作者：_Cheems (赞：3)

转化 $+$ 鸽巢原理。

由于一条边价值是 $\min$，且答案求的也是 $\min$。考虑放开限制，计入一些非法情况但不影响答案，方便计算。
 
对此题而言，将 $x,y$ 取最小看成 $x,y$ 中选恰好一个即可。

那么问题得到简化。思考一个点 $a_i,b_i$ 是否被计入答案（对答案贡献），不妨用 $00,01,10,11$ 表示。

注意到一个关键性质，若不存在 $11$，则不可能同时出现 $01,10$。

理由如下：将 $x,y$ 的选择看成不同方向的有向边，由于这是一个环，所以必然存在一个 $01,10$ 的交界点，这个交界点就是 $11$ 了。同理，还能发现 $00$ 与 $11$ 成对出现（虽然没啥用）。

所以合法情况只有：只选 $a$、只选 $b$、选至少一对 $a,b$。前两种容易解决，考虑第三种。

可以利用鸽巢原理，具体如下：让所有 $a,b$ 一起升序排列，选取前 $n+1$ 个记为 $c_1\dots c_{n+1}$，此时必然存在一对 $a,b$。

然后依次枚举去掉 $c_{n-1},c_n,c_{n+1}$ 的方案是否满足条件，显然肯定有一种方案合法。

请注意，去掉 $c_{n-1}$ 不一定是第三小方案，需要再枚举去掉 $c_{n},c_{n+1}$ 然后加上 $c_{n+2}$ 的方案。我不幸被坑了。

会影响正确性吗？不会，因为这是前 $4$ 小的方案，而且根据先前讨论，其中必有一种合法，所以没毛病。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n, m, res, sa, sb, ans, a[N], b[N], buc[N];
pair<int, int> c[N];

inline void add(int p) {++buc[c[p].second], res += c[p].first;}
inline void del(int p) {--buc[c[p].second], res -= c[p].first;}
inline void check() {for(int i = 1; i <= n; ++i) if(buc[i] == 2) ans = min(ans, res);}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i){
		scanf("%lld%lld", &a[i], &b[i]);
		sa += a[i], sb += b[i];
		c[++m] = {a[i], i}, c[++m] = {b[i], i};
	}
	ans = min(sa, sb), sort(c + 1, c + 1 + m);
	for(int i = 1; i <= n + 1; ++i) add(i);
	for(int i = n - 1; i <= n + 1; ++i) del(i), check(), add(i);
	del(n), del(n + 1), add(n + 2), check();
	cout << ans;
	return 0;
}
```

---

## 作者：xht (赞：3)

## [Min Cost Cycle](https://atcoder.jp/contests/agc028/tasks/agc028_c)

### 题意

- 有一张 $n$ 个点的有向完全图。
- 每个点 $i$ 有两个权值 $a_i,b_i$，对于两个点 $x,y$，边 $x \to y$ 的长度为 $\min(a_x,b_y)$。
- 考虑图中经过每个点恰好一次的有向环，求出其中的最短路径长。
- $n \le 10^5$。

### 题解

换个角度考虑，相当于要从 $2n$ 个数中选择 $n$ 个数，使其可以连成一个环，环中每条边前一个 $a$ 和后一个 $b$ 中选择恰好一个。

可行的方案有三种：

1. 全选 $a$，合法性显然，不证。
2. 全选 $b$，合法性显然，不证。
3. 至少有一个 $i$ 满足 $a_i,b_i$ 都被选了。

第三种的合法性证明如下：

> 显然每个数只有四种状态，我们将其看成 $00,01,10,11$ 四种，那么条件就是至少有一个 $11$。
> 因为 $1$ 的总数为 $n$，所以 $11$ 和 $00$ 的数量相等，将它们交替放（$00 \sim 11 \sim 00 \sim 11 \sim\cdots$）。
> 将所有 $01$ 和 $10$ 首尾相连变成一个 $01$ 一个 $10$，然后随便插到 $00 \sim 11$ 的环中合法的位置即可。

而除了这三种方案，剩下的情况的不合法性也很显然。

于是用 `set` 维护前 $n$ 小的数，然后枚举 $a_i,b_i$ 都被选的 $i$，可以 $\mathcal O(\log n)$ 得到答案。

总时间复杂度 $\mathcal O(n \log n)$。

### 代码

```cpp
const int N = 1e5 + 7;
int n, a[N], b[N];
ll sa, sb, sum, ans;
set<pi> s;
bool v[N], w[N];

int main() {
	rd(n);
	for (int i = 1; i <= n; i++)
		rd(a[i], b[i]), sa += a[i], sb += b[i], 
		s.insert(mp(a[i], i)), s.insert(mp(b[i], -i));
	ans = min(sa, sb), sum = sa + sb;
	while ((int)s.size() > n)
		sum -= (--s.end()) -> fi, s.erase(--s.end());
	for (pi o : s)
		if (o.se > 0) v[o.se] = 1;
		else w[-o.se] = 1;
	for (int i = 1; i <= n; i++)
		if (v[i]) {
			if (w[i]) ans = min(ans, sum);
			else {
				auto it = --s.end();
				while (it -> se == i) --it;
				ans = min(ans, sum + b[i] - (it -> fi));
			}
		} else {
			if (w[i]) {
				auto it = --s.end();
				while (it -> se == -i) --it;
				ans = min(ans, sum + a[i] - (it -> fi));
			} else {
				auto it1 = --s.end(), it2 = --(--s.end());
				ans = min(ans, sum + a[i] + b[i] - (it1 -> fi) - (it2 -> fi));
			}
		}
	print(ans);
	return 0;
}
```

---

## 作者：ZillionX (赞：2)

# Description

给定一个 $n$ 条边的有向完全图，每个点 $i$ 有两个点权 $a_i,b_i$，边 $(u,v)$ 的边权为 $\min\{a_u,b_v\}$，求边权和最小的哈密顿回路边权和。

$n \le 10^5, V \le 10^9$，时限 2s。

# Solution

有意思的题目。

显然每个 $a_i$ 或 $b_i$ 只会对答案贡献一次。

不妨考虑一个常见套路，将不合法的且不会成为最终答案的一部分方案一齐统计，方便后面的计算。对于这道题，我们可以将题意变为从 $a_u$ 和 $b_v$ 中选一个出来作为边权，这样就把边权取 $\min$ 的条件去掉了。

考虑如何判断一个方案是否合法，不难发现方案成立当且仅当

- 选择的数全是 $a$ / 全是 $b$
- 至少存在一个点的 $a$ 和 $b$ 都被选入

第一种情况就很显然了，第二种情况是因为要把 $a$ 和 $b$ 串起来。

那么我们现在可以把 $a$ 和 $b$ 放在一起升序排序（下面记为 $x$），选取 $n$ 个数的前缀，这个就是答案的下界。

注意到下界不一定能达到，那么我们可以抬高一下下界，把 $x_n$ 换成 $x_{n+1}$，但是这样可能还是不合法。

那么此时 $x_n$ 和 $x_{n+1}$ 就必然是同一个点的点权，下面我们可以 $x_{n-1} \leftarrow x_n$ 或 $x_{n+1} \leftarrow x_{n+2}$，容易发现这两种方案都必然合法。（实际上，这种做法通过优先队列维护可以求出前 $k$ 小的方案（在问题必然合法时），这又是一种常见套路）

至此我们就在 $\mathcal O(n \log n)$ 的时间复杂度下完成了本题。

# Code

```cpp
typedef long long LL;
const int N=2e5+5;

int n,t[N];
LL Ans;

struct Node {
	int v,x; bool f;
	bool operator<(const Node &r) const {
		return v<r.v;
	}
}a[N];

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&a[i*2-1].v,&a[i*2].v);
		a[i*2-1].x=i,a[i*2].x=i;
		a[i*2-1].f=0,a[i*2].f=1;
	}
	sort(a+1,a+n*2+1);
	int c0=0,c1=0;
	bool Jdg=false;
	for (int i=1;i<=n;i++) {
		if (!a[i].f) c0++;
		else c1++;
		Ans+=a[i].v,t[a[i].x]++;
		if (t[a[i].x]==2) Jdg=true;
	}
	
	if (Jdg || c0==n || c1==n)
		printf("%lld",Ans);
	else {
		if (!a[n].f) c0--;
		else c1--;
		if (!a[n+1].f) c0++;
		else c1++;
		if (a[n].x!=a[n+1].x || c0==n || c1==n)
			printf("%lld",Ans-a[n].v+a[n+1].v);
		else
			printf("%lld",Ans-a[n].v+a[n+1].v+min(a[n+2].v-a[n+1].v,a[n].v-a[n-1].v));
	}
	return 0;
}
```


---

## 作者：aike_6yoshi9 (赞：1)

由于一个点的 $a$ 和 $b$ 可以经过两次，所以直接考虑贪心去取到 $2 \times n$ 个 $a$ 和 $b$ 的前 $n$ 小的值，但是不难发现这样做是不一定可行的，为了描述的简单，这里举出可行的三种方案：  
1. 取的前 $n$ 个数都是 $a$；
2. 取的前 $n$ 个数都是 $b$；
3. 取的前 $n$ 个数并没有把所有的点包含在内。

以上情况满足任一即可。  
考虑几种情况的调整，拿样例一为例：  
首先看到取 $1,2,3$ 是不行的，因为这种取法并不满足以上三种情况的任意一种 $($ 如果满足可以直接输出 $6)$，所以先调整为 $1,2,4$ 发现是满足的情况 $3$ 的，所以这里可以直接输出 $7$，但是如果不满足，就考虑继续调整为 $1,2,5$ 或者 $1,3,4$，经过简单证明可以发现这两种情况必定是都满足条件的，所以在其中取较小值输出即可。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=1e6+100;
bool vis[MAXN];
inline long long read(){
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1*f;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
struct Node{
	long long num,id,aorb;
}a[MAXN];
bool cmp(Node a,Node b){
	if(a.num<b.num) return true;
	else return false;
}
int main(){
	long long n=read();
	for(long long i=1;i<=n;i++){
		a[i*2-1].num=read();
		a[i*2-1].id=i;
		a[i*2-1].aorb=1;
		a[i*2].num=read();
		a[i*2].id=i;
		a[i*2].aorb=2;
	}
	sort(a+1,a+n*2+1,cmp);
	long long cta=0,ctb=0,ans=0,cnt=0;
	long long zans=1e18;
	for(long long i=1;i<=n;i++){
		if(!vis[a[i].id]){
			vis[a[i].id]=true;
			cnt++;
		}
		if(a[i].aorb==1) cta++;
		else ctb++;
		ans+=a[i].num;
	}
	if(!cta||!ctb||cnt!=n) printf("%lld",ans);
	else{
		memset(vis,0,sizeof(vis));
		cta=0,ctb=0,ans=0,cnt=0;
		for(long long i=1;i<=n+1;i++){
			if(i==n) continue;
			if(!vis[a[i].id]){
				vis[a[i].id]=true;
				cnt++;
			}
			if(a[i].aorb==1) cta++;
			else ctb++;
			ans+=a[i].num;
		}
		if(!cta||!ctb||cnt!=n) printf("%lld",ans);
		else{
			memset(vis,0,sizeof(vis));
			cta=0,ctb=0,ans=0,cnt=0;
			for(long long i=1;i<=n+1;i++){
				if(i==n-1) continue;
				if(!vis[a[i].id]){
					vis[a[i].id]=true;
					cnt++;
				}
				if(a[i].aorb==1) cta++;
				else ctb++;
				ans+=a[i].num;
			}
			zans=min(zans,ans);
			memset(vis,0,sizeof(vis));
			cta=0,ctb=0,ans=0,cnt=0;
			for(long long i=1;i<=n+2;i++){
				if(i==n||i==n+1) continue;
				if(!vis[a[i].id]){
					vis[a[i].id]=true;
					cnt++;
				}
				if(a[i].aorb==1) cta++;
				else ctb++;
				ans+=a[i].num;
			}
			zans=min(zans,ans);
			printf("%lld",zans);
		}
	}
	return 0;
}
```
由于不想去写单个数的调整，所以直接清空直接枚举，虽然常数大了亿点，但是还是很轻松就过了。

---

## 作者：Lvlinxi2010 (赞：1)

学长讲的 Ad-hoc，来写一篇题解。

考虑对于每个点的 $a_i$、$b_i$，有四种贡献情况，我们称没有贡献为 0，有贡献为 1，我们把每个点看作下面四个的一种：

1. 00：$a_i$、$b_i$ 都不贡献。
2. 01：$a_i$ 不贡献，$b_i$ 贡献。
3. 10：$a_i$ 贡献，$b_i$ 不贡献。
4. 11：$a_i$、$b_i$ 都贡献。

哈密顿回路是每个点恰好经过一次的回路，那么我们可以把它看作是首尾相连的一个环，10/00 $\rightarrow$ 10/11，每一条边都是 0 $\rightarrow$ 1。

我们可以证明一个结论，当有 00/11 时，这个回路一定合法。显然 00/11 的个数相等，那我们可以 00 $\rightarrow$ 10 $\rightarrow$ 10 $\cdots$ $\rightarrow$ 11 $\rightarrow$ 01 $\rightarrow$ 01 $\cdots$ $\rightarrow$ 00。显然形成一个回路，当 00/11 多于一个时可以 00 $\rightarrow$ 11 $\rightarrow$ 0。

还有当都选 01/10 的时候回路合法，这是显然的。

我们先选 $n$ 个数的 $\min(a_i,b_i)$，若合法则为答案，若不合法，一定是有 01 和 10，没有 00/11。

我们再考虑没选的数中最小的两个，设为 $x$ 和 $y$，选了的数中最大的两个，设为 $u$ 和 $v$。

不妨设 $x<y<u<v$，

若 $y,u$ 是同一个点的 $a_i$、$b_i$，用 $v$ 换 $y$ 和 用 $u$ 换 $x$ 必定合法，取最小值即可。

若不是同一个点，那么用 $u$ 换 $y$，因为可以有多个 00/11，继续尝试用没有选的替换选了的，当不能替换了记录答案。

最后对答案和 01/10 的情况取最小值即可。

附上代码：


```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(ll i=(a);i<=(b);i++)
#define FR(i,a,b) for(ll i=(a);i>=(b);i--)
#define ll long long
#define PII pair<ll,ll>
using namespace std;
const ll MAXN = 1e5 + 10;
ll a[MAXN],b[MAXN];
priority_queue<PII>p,q;
signed main(){
	ll n,ans=0,ans1=0,ans2=0;
	scanf("%lld",&n);
	FL(i,1,n){
		scanf("%lld%lld",&a[i],&b[i]);
		ans1+=a[i];
		ans2+=b[i];
		p.push({min(a[i],b[i]),i});
		q.push({-max(a[i],b[i]),i});
		ans+=min(a[i],b[i]);
	}
	ll x=p.top().first,y=-q.top().first;
	if(p.top().second==q.top().second){
		q.pop(),p.pop();
		ll u=p.top().first,v=-q.top().first;
		ans+=min(v-x,y-u);
	}
	else{
		q.pop(),p.pop();
		ans+=y-x;
		while(p.top().first>-q.top().first){
			ans+=-q.top().first-p.top().first;
			q.pop(),p.pop(); 
		}
	}
	printf("%lld\n",min({ans,ans1,ans2}));
}
```

---

## 作者：Graphcity (赞：1)

这种问题没有明确的转移顺序，考虑贪心。

对于每一组 $(a_i,b_i)$，我们用一个长度为 2 的 01 串来表示。第一位为 0/1 表示 $a_i$ 不计入/计入贡献，第二位同理。

由于答案取的是最小值，且边权为 $\min(a_u,b_v)$，所以我们只需要找到所有合法的 01 串集合，找到其中的最小贡献就是答案。

考虑怎么样才能构成一个合法集合。

- **性质**：`00` 和 `11` 的个数相等。  
**证明**：首先所有串中 0 和 1 的总个数必然相等且均为 $n$。如果 `00` 和 `11` 的个数不等，那么剩下的 `01` 和 `10` 并不能填补 0 和 1 个数的差距，最终必然不合法。

1. 不存在 `00` 和 `11` 串：最终一定全为 `01` 或者全为 `10`，因为 `01` 和 `10` 并不能拼在一起。
2. 存在 `00` 和 `11` 串：此时任何情况都合法。
   - 因为 `00->11->00->11->...=01`，此时情况化为仅有一个 `00` 和 `11` 串。
   - 因为 `01->01->...=01`，`10->10->...=10`，此时情况化为仅有至多一个 `01` 串和 `10` 串。
   - 因为 `00->11` 合法，`00->10->11` 合法，`11->01->00` 合法，`00->10->11->01` 且合法，这包含了所有的情况，所有任何情况都合法。

首先排除不存在 `00` 和 `11` 的情况。接下来利用贪心求出答案 $ans$：

1. 对每一对 $(a_i,b_i)$，让其中的较小值为 1，较大值为 0。将较小值存进大根堆 $s_1$，较大值存进小根堆 $s_2$。$ans$ 加上较小值。
2. 比较 $s_1$ 的堆顶 $x$ 和 $s_2$ 的堆顶 $y$。若 $x>y$，则 $ans\gets ans+y-x$，弹出两个堆的堆顶，并回到第 2 步。这一步的意义在于，将某一处的 `01` 或者 `10` 变成 `11`，另一处则变成 `00`。
3. 如果第二步一开始就有 $x\le y$，则强制让某一处变成 `11`，另一处变成 `00`，且让 $ans$ 的变化量尽量小。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;
const ll inf=1e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,a[Maxn+5],b[Maxn+5];
ll sum=0,ans=inf;
priority_queue<int> tp;
priority_queue<int,vector<int>,greater<int>> lw;

int main()
{
    n=read();
    For(i,1,n) a[i]=read(),b[i]=read();
    sum=0; For(i,1,n) sum+=a[i]; ans=min(ans,sum);
    sum=0; For(i,1,n) sum+=b[i]; ans=min(ans,sum);
    sum=0; For(i,1,n)
    {
        int x=min(a[i],b[i]),y=max(a[i],b[i]);
        lw.push(y),tp.push(x),sum+=x;
    }
    int flg=0;
    while(!lw.empty() && lw.top()<tp.top())
        sum=sum+lw.top()-tp.top(),lw.pop(),tp.pop(),flg++;
    if(!flg)
    {
        ll dlt=inf;
        for(ll i=1,mn=inf,mx=0;i<=n;++i)
        {
            int x=min(a[i],b[i]),y=max(a[i],b[i]);
            dlt=min(dlt,min(mn-x,y-mx));
            mn=min(mn,1ll*y),mx=max(mx,1ll*x);
        }
        sum+=dlt;
    }
    ans=min(ans,sum);
    cout<<ans<<endl;
    return 0;
}
```



---

## 作者：封禁用户 (赞：1)

## 题目大意

有 $n$ 个点的一张有向完全图，每个点有两个点权 $a,b$。连接 $x,y$ 两个点的边权为 $ \min  \left \{ a_x,b_y \right \} $，求一条权值和最小的哈密顿回路。

$1≤n≤10^5,1≤a,b≤10^9$。

## 解题思路

又是 $min$ 又是权值最小，我们可以把问题转换为从 $x$ 走到 $y$ 的权值可以选择 $a_x$ 或者 $b_y$，然后求最小的权值和。

一个暴力的想法是对于每个 $a_x$ 对应一个 $b_y$ 来匹配，但是这样很显然容易导致选出的是若干个小环。

我们可以考虑具体一个点的贡献，我们根据 $ a$ 和 $b$ 是否产生了贡献记为一个二进制位，那么每个点的贡献有 $00,01,10,11$, 考虑什么时候一个方案合法。

把每个 $a/b$ 视为一个二分图，并且 $a_i$ 向 $b_i$ 连边，然后我们之后连的边中要求两个端点恰好有一个 $1$，确立如下图所示规则：
![](https://cdn.luogu.com.cn/upload/image_hosting/ii9tfusp.png)


不难发现一个合法的构造只有两种情况

1. 全部都是 $01$ 或者 $10$
2. $00$ 和 $11$ 各有 $k(k \ge 1)$ 个，其余 $01/10$ 任意

第一种情况直接计算

第二种情况我们对于每一个默认为 $01/10$ 中权值最小的一个，然后一个 $01/10\to11(ans+\max\left \{ a_i,b_i \right \} )$，一个  $ 01/10\to 00(ans-\min\left \{ a_i,b_i \right \} )$，我们可以用两个堆分别维护 $\max\left \{ a_i,b_i \right \} $ 和 $\min\left \{ a_i,b_i \right \} $。

需要注意的是由于第二种情况至少需要一个 $00/11$ 所以就算第一次会让答案变大也得变，而且有可能出现第一次选择的 $\max \left \{ a_i,b_i \right \} $ 和 $\min \left \{ a_i,b_i \right \} $ 是同一个 $i$，需要特判。

时间复杂度：$O(n\log n)$

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define mp(x,y) make_pair(x,y)
#define ll long long
using namespace std;
const ll N=1e5+10;
ll n,a[N],b[N],ans1,ans2,ans;
priority_queue<pair<ll,ll> > q1,q2;
signed main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		ans1+=a[i];ans2+=b[i];
		q1.push(mp(min(a[i],b[i]),i));
		q2.push(mp(-max(a[i],b[i]),i));
		ans+=min(a[i],b[i]);
	}
	pair<ll,ll> x=q1.top(),y=q2.top();
	if(x.second==y.second){
		q1.pop();q2.pop();
		pair<ll,ll> l=q1.top(),r=q2.top();
		ans+=min(-r.first-x.first,-y.first-l.first);
	}
	else{
		q1.pop();q2.pop();
		ans+=-y.first-x.first;
		while(1){
			ll x=q1.top().first,y=-q2.top().first;
			q1.pop();q2.pop();
			if(x<=y)break;
			ans+=y-x;
		}
	}
	printf("%lld\n",min(ans,min(ans1,ans2)));
	return 0;
}

```


---

## 作者：WeLikeStudying (赞：0)

- 希望独立思考。
- 希望全力以赴。
- 希望不留遗憾。

### 题意

[题目](https://www.luogu.com.cn/problem/AT4437)。

给一个 $n$ 个点有向完全图，给出 $a_i$ 和 $b_i$，从 $u$ 到 $v$ 的边权为 $\min(a_u,b_v)$，求该有向图中最小权哈密顿回路。

### 题意

我当时一直想往匹配方向转换，但到头来还是需要这个判定。（不过如果有了这个判定就容易理解了）

简化题意：从 $u$ 到 $v$ 的边权可以是 $a_u$ 也可以是 $b_v$。

然后就变成了点权问题，然后我们还需要一个判定：哪些点权是可行的。

你可以发现这很好拆点变成一个二分图，选择一些关键点让它们可以向任何一个对方的非关键点连一条边，然后我们要求形成哈密顿回路。

首先至少要选 $n$ 个点（因为要连 $n$ 条边），然后你发现选边非常自由，手玩一下，似乎就有三种情况：左边全选，右边全选，（至少）存在一个两边都选。（否则左部和右部的置换永远不相交）

然后我们探讨第三种情况的最小值，这里记录的是较为简单的方法：抬高下界法，暴力找到前 $n$ 个数，若恰好没有重复，找到第  $n+1$ 个数：如果不能用它去掉最后一个的话，那第 $n$ 个数和第 $n+1$ 个数相等：需要考虑两种情况，去掉第 $n$ 个和再拿第 $n+1$ 个。

利用贪心可以证明它的正确性。

核心思想是使用方法简化为判定问题，然后这个贪心简化问题的思想值得学习。

同时我思路的不足之处也是不善于灵活转换，以为戒。
```cpp
#include<fstream>
#include<algorithm>
const int N=110000;
using namespace std;
int n,w[N<<1],id[N<<1];
long long cnt[2],ans,res;
bool vis[N];
bool cmp(int a,int b)
{
	return w[a]<w[b];
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<(n<<1);++i)
	{
		scanf("%d",&w[i]);
		cnt[i&1]+=w[i],id[i]=i;
	}
	ans=min(cnt[0],cnt[1]);
	sort(id,id+(n<<1),cmp);
	bool ok=0;
	for(int i=0;i<n;++i)
	{
		if(vis[id[i]>>1])ok=1;
		res+=w[id[i]];
		vis[id[i]>>1]=1;
	}
	if(!ok)
	{
		if((id[n]>>1)!=(id[n-1]>>1))
			ans=min(ans,res+w[id[n]]-w[id[n-1]]);
		else
			ans=min(ans,res+w[id[n]]-w[id[n-2]]),
			ans=min(ans,res+w[id[n+1]]-w[id[n-1]]);
	}
	else ans=min(ans,res);
	printf("%lld",ans);
	return 0;
} 
```

---

