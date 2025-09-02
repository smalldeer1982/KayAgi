# Two Operations

## 题目背景

**本题时限较小，请采用较快的读入方式，以下是出题人提供的快读模板：**

```cpp
typedef long long LL;
inline LL read(){
	register LL x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
```

当然你也可以采用自己的读入方法。

## 题目描述

在一次聚会上，一共有 $n$ 名学生，他们的编号分别为 $1,2,3,\cdots,n$，他们被分成 $k$ 组，组的编号分别为 $1,2,3,\ldots,k$。

小 V 老师负责组织这场聚会，在聚会的开始，第 $i$ 名学生被分到了第 $a_i$ 组，并拿到了 $b_i$ 颗糖果。（小 V 既不属于任何组别，也没有任何糖果。在接下来的活动中，小 V 作为组织者的身份。） 

这一次聚会一共有 $m$ 轮活动，对于每一轮活动，可能发生以下两种情况之一：

1.  `Change X Y`，表示把所有组别为 $X$ 的学生的组别改为 $Y$（修改后 $X$ 即为空组），并把组 $X$ **删除**。
2.  `Query`，表示小 V 想要知道，如果把**剩下**的组合并（定义见下） 成一大组，那么这一大组内**拥有最多糖果的学生的糖果数最少可能是多少**。

定义一个组 $G_i$ 的大小就是这个组内含有学生的个数，记为 $S_i$。

**合并**：将大小为 $S_1(S_1>0)$ 的组 $G_1$ 合并到大小为 $S_2(S_2>0)$ 的组 $G_2$，其中 $G_1$ 组内所有学生拥有糖果数之和为 $f$，则：

1. 第一步，将原先 $G_1$ 中所有学生的糖果数都变为 $0$，并将他们的组别改为 $G_2$。
2. 第二步，将目前 $G_2$ 中每位学生（包括原先 $G_1$ 中的学生）的糖果数加上 $\dfrac{f}{S_1+S_2}$（糖果数不一定为整数块）。

**注意：**

1. $G_1$ 合并到 $G_2$ 的最后结果可能会与 $G_2$ 合并到 $G_1$ 的最后结果不同。
2. `Query` 中的合并不会真实发生。即在这一次情况过后，所有学生的糖果数与所在组与此次操作未发生前一致。

请将每次 `Query` 中的答案对 $10^9+7$ 取模。（可能是分数取模，如果不知道如何取模请见**提示说明**）

## 说明/提示

【样例解释】

第一次 `Query` 时，将第二组合并到第一组，此时三名学生的糖果数分别为 $\dfrac{14}{3},\dfrac{17}{3},\dfrac{5}{3}$，糖果数最多的同学有 $\dfrac{17}{3}$ 块糖果，取到了最小值，对 $10^9+7$ 取模后为 $666666677$。

第二次 `Query` 时，所有学生都在同一组，而糖果数最多的同学有 $5$ 块糖果。

---

【数据范围】

| 数据点 | $n$  | $m$  | $k$  | $a_i$ | $b_i$  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $1$ | $\le 10$ |无特殊限制 | $\le 10$ | $\le 10$ | $\le 100$ |
| $2$ | $\le 100$ | $\le 10$ | $\le 100$ | $\le 100$ | $\le 100$ |
| $3$ | $\le 10^5$ | $=1$ | $\le 10^5$ | $\le 10^5$ | $\le 10^5$ |
| $4$ | $\le 10^5$ | 无特殊限制 | $=1$ | $=1$ | $\le10^5$ |
| $5$ | $\le 10^3$ |无特殊限制 | $\le 5$ | $\le 5$ | $\le 100$ |
| $6$ | $\le 10^4$ | $\le 10^3$ | $\le 10^4$ | $\le 10^4$ | $\le 10^5$ |
| $7$ | $\le 10^4$ | $\le 5\times10^3$ | $\le 10^4$ | $\le 10^4$ | $\le 10^5$ |
| $8$ | $\le 10^5$ | 无特殊限制 | $\le 10^5$ | $\le 10^5$ | $\le 10^5$ |
| $9 $| $\le 5\times10^5$ | 无特殊限制 | $5\times10^5$ | $5\times10^5$ | $\le 10^5$ |
| $10$ | $\le 10^6$ | 无特殊限制 | $\le 10^6$ | $\le 10^6$ | $\le 10^5$ |

对于 $100\%$ 的数据，满足 $1 \leq n \leq 10^6,\ 1\leq m \leq 2\times k-1,\ 1 \leq a_i\leq k \leq n,\ 1 \leq b_i \leq 10^5$。**数据保证合法，初始时每组是非空的。**


不熟悉有理数取模的请看[此处](/problem/solution/P2613)。


## 样例 #1

### 输入

```
3 3 2
1 1 2
3 4 5
Query
Change 2 1
Query```

### 输出

```
666666677
5```

# 题解

## 作者：Anxiomgh (赞：5)

本蒟蒻不会写 multiset，于是写了一发优先队列（逃）。  如有谬误，大家敬请指正。
# Sol

首先考虑操作 `Query`。  

设 $g(G_{1},G_{2},...G_{n})$ 表示将 $G_{1},G_{2},...G_{n}$ 以任意方式合并，易得引理 1： 

合并方式 $g(G_{1},G_{2},...G_{i - 1},G_{i+1},...G_{n}) \to G_{i}$ 可以使 $G_{i}$ 中的合并后的最大值最小。

设 $w_{i}$ 为将所有组全部合并到组 $G_{i}$ 后的最大值的最小值，$v_{i}$ 为 $G_{i}$ 中原来的的最大值，$sum$ 为总糖果数，写成表达式为：    

$$w_{i} = v_{i} + \frac{sum - f_{i}}{\sum_{j = 1}^n{S_{j}}}$$

可以发现，$O(n)$ 的预处理即可求得序列 $w$。那么原问题就转化成了求 $w$ 中的最小值和多次 `Change` 后 $w$ 中的最小值。  

我们再来研究一下 `Change` 操作对序列 $w$ 的影响。  

设共有四个组 $G_{1},G_{2},G_{3},G_{4}$，将 $G_{2}$ 修改为 $G_{3}$。

* 对于 $G_{1}$ 和 $G_{4}$，修改操作并不影响它们的最大值，因此 $w_{1}$ 和 $w_{4}$ 的值不改变。即：  

	$w_{1}' = w_{1} = v_{1} + \frac{f_{2} + f_{3} + f_{4}}{S_{1} + S_{2}+ S_{3} + S_{4}},w_{4}' = w_{4} = v_{4} + \frac{f_{1} + f_{2} + f_{3}}{S_{1} + S_{2}+ S_{3} + S_{4}}$

* 对于 $G_{3}$，进行分类讨论：
	1. 如果 $v_{2} \leq v_{3}$，$w_{3}' = v_{3} + \frac{f_{1} + f_{4}}{S_{1} + S_{2}+ S_{3} + S_{4}}$，有 $w_{3}' < w_{3}$。  

	2. 如果 $v_{2} > v_{3}$，$w_{3}' = v_{2} + \frac{f_{1} + f_{4}}{S_{1} + S_{2}+ S_{3} + S_{4}}$，有 $w_{3}' < w_{2}$。  

综上所述，可得引理 2：当 $G_{i}$ 被修改成 $G_{j}$ 时，一定存在：  
$$w_{j}' < w_{j}(v_{i} \leq v_{j})$$ 
$$w_{j}' < w_{i}(v_{i} > v_{j})$$  

这样就可以用优先队列维护了。  

不难发现，对于每一次 `Change`，都会对应着一个组被删除，一个 $v_{x}$ 消失，这个 $v_{x}$ 是参与比较的两个最大值中较小的一个。因为在此后任意 $G_{i}$ 中的最大值一定不为 $v_{x}$，$v_{x}$ 就一定不会参与 $w$ 的计算。建一个数组记录被淘汰的 $v_{x}$ 的下标 $x$，在优先队列中访问到下标被记录的元素直接 pop 掉即可。  

而对于存留下来的另一个 $v_{y}$，它所对应的 `Change` 前的 $w$ 虽然在优先队列中也是不合法的，但将新生成的 $w'$ push 进优先队列，$w'$ 一定排在它前面，即 $w' < w$。所以它永远不会被访问到，这就保证了算法的正确性。 

开一个 $fa$ 数组记录最大值的来源，并不断更新 $v$，就可以轻松处理 `Change` 的问题了。  

具体实现请看代码 (QwQ)
# 代码
```cpp
ll n, m, k, sum = 0;
ll a[MAXN], b[MAXN];
ll f[MAXN], v[MAXN], S[MAXN], w[MAXN], fa[MAXN];
bool flag[MAXN];
struct item
{
	ll pos, val; // pos 表示 G_{i} 中最大值的原下标 
	bool operator<(const item& x)const
	{
		return x.val < val;
	}
};
priority_queue<item>q;

void init() // 读入并初始化 
{
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) b[i] = read();
	
	for (int i = 1; i <= n; i++)
		S[a[i]]++, f[a[i]] += b[i], v[a[i]] = max(v[a[i]], b[i]), sum += b[i];
		
	for (int i = 1; i <= n; i++) 
		w[i] = v[i] * n + sum - f[i]; // 计算 w（分子部分） 
		
	for (int i = 1; i <= k; i++) 
		q.push({i, w[i]}); // 将所有 w push 进队列里 
	for (int i = 1; i <= n; i++) fa[i] = i; // 初始化所有组中的最大值下标 
}

ll pow(ll x, ll temp)
{
	ll res = 1;
	for (; temp; temp >>= 1, x = x * x % p) 
		if (temp & 1) res = res * x % p;
	return res;
}
int main()
{
	init();
	while (m--)
	{
		string op;
		cin >> op;
		if (op == "Change")
		{
			int x, y;
			x = read(), y = read();
			f[y] += f[x];   //update
			S[y] += S[x];
			if (max(v[x], v[y]) == v[x])
				flag[fa[y]] = true, fa[y] = fa[x]; // 更新 G_{y} 中的最大值下标
			else
				flag[fa[x]] = true; // G_{x} 被删除，不用更新 fa_{x} 
			v[y] = max(v[x], v[y]); // 更新最大值 
			ll z = v[y] * n + sum - f[y]; // 计算 w'（分子部分） 
			q.push({fa[y], z}); // 将 G_{y} 中最大值的原下标和 w' push 进队列 
		}
		else if (op == "Query")
		{
			while (flag[q.top().pos] == true) // 如果队头元素中包含的最大值已被淘汰
			{
				q.pop(); 
			}
			ll ans = ((q.top().val % p) * pow(n, p - 2)) % p; // 有理数取余
			cout << (ans % p + p) % p << endl;
		}
	}
}

```


---

## 作者：gyc18 (赞：2)

本题解为官方题解

先只考虑 ```Query``` 的情况（下文中所有参与的集合都是非空集）。

我们定义 $G_1→G_2$ 代表将 $G_1$ 合并到 $G_2$，$\text{Sum}(G)$ 代表组 $G$ 内糖果数总和。

首先要证明出 $G_1→G_2→G_3$  优于 $G_1→(G_2→G_3)$。证明略，只要按照要求，就遍最大值进行比较即可。

那么最后的合并情况只有可能表示为： $G_{a_{1}}→G_{a_{2}}→...→G_{a_{n-1}}→G_{a_{n}}$。，其中 $a_1,a_2,...a_n$ 构成 $1,2,...,n$ 的一种排列。

**引理：若 $G_{a_{1}}→G_{a_{2}}→...→G_{a_{n-1}}→G_{a_{n}}$，$G_{b_{1}}→G_{b_{2}}→...→G_{b_{n-1}}→G_{b_{n}}$，$a_n=b_n$，那么这两个合并序列等价。（即合并后组内最大值一致）**

证明：不妨设 $G_{a_{1}}→G_{a_{2}}→...→G_{a_{n-1}}=S$，$G_{b_{1}}→G_{b_{2}}→...→G_{b_{n-1}}=T$。

可以发现 $|S|=|T|$，但 $\max(S)$ 不一定等于 $\max(T)$。

记 $\max(G_{a_{1}}→G_{a_{2}}→...→G_{a_{n-1}}→G_{a_{n}})=m_1,\max(G_{b_{1}}→G_{b_{2}}→...→G_{b_{n-1}}→G_{b_{n}})=m_2$，其中 $\max(P)$ 代表组 $P$ 内拥有糖果数最大值。

则 $m_1=\max(G_{a_{n}})+\frac{\sum_{i=1}^{n-1}\text{Sum}(G_{a_i})}{n},m_2=\max(G_{b_{n}})+\frac{\sum_{i=1}^{n-1}\text{Sum}(G_{b_i})}{n}$，又因为 $a_n=b_n$，所以 $m_1=m_2$。得证。

所以我们设 $M_i$ 代表 $G_{x_{1}}→G_{x_{2}}→...→G_{x_{n-1}}→G_{x_{n}}$ 中 $x_n=i$ 时 $\max(G_{x_{1}}→G_{x_{2}}→...→G_{x_{n-1}}→G_{x_{n}})$  的值。

有 $M_i=\max(G_{i})+\frac{\sum_{k=1}^{n-1}\text{Sum}(G_{x_k})}{n}=\max(G_{i})+\frac{\sum_{k=1}^{n}\text{Sum}(G_{k})-\text{Sum}(G_i)}{n}$。

显然 $\sum_{k=1}^{n}\text{Sum}(G_{k})$  可以预处理，如果没有 ```Change``` 操作，时间复杂度为 $O(n+k+m)$。

如果有 ```Change``` 操作，因为要屏蔽空集，所以用一个并查集维护上述元素即可。时间复杂度 $\text{O(nα(n))}$（视 $n,m$ 同阶）

---

## 作者：qiucr (赞：0)

这道题竟然没有人用**线段树**来写,感觉线段树写法还是~~比较简单~~的。
### 首先来看 **query** 操作：
推个式子，我们发现，对于一个组 $u$，其最后的贡献一定是：
$$v_u+\frac{tot-sum_u}{n}$$ 
其中，$v_u$ 表示第 $u$ 组成员的最大值，$tot$ 表示所有人的总和，$sum_u$ 表示第 $u$ 组所有人的总和。\
结论显然，在纸上模拟一下就发现了，和前面怎么合并的顺序是无关的。\
所以我们现在的问题就变成了**找区间最小值**，我们想到可以用线段树来维护区间最小值。
### 对于 **change** 操作：
假设现在要把 $x$ 合并到 $y$，那么我们只要进行维护操作：把 $x$ 和 $y$ 的状态进行更新，之后在线段树上把 $x$ 做**单点修改**为正无穷，把 $y$ **单点修改**为新的 $v_y+\frac{tot-sum_y}{n}$。\
最后我们在实际计算的时候是把上面的式子通分了的，也就是变成了 $v_u \times n+tot-sum_u$ 的。
#### 最后是代码：
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e6 + 100, mod = 1e9 + 7;
int n, m, k;
ll sum[N], v[N], id[N], w[N], tot;
struct node
{
  int l, r;
  ll minn;
} tr[N * 4];
void pushup(int u)
{
  tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
}
void build(int u, int l, int r)
{
  tr[u] = {l, r};
  tr[u].minn = 1e18;
  if (l == r)
  {
    tr[u].minn = w[l];
    return;
  }
  int mid = l + r >> 1;
  build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
  pushup(u);
}
void modify(int u, int x, ll k)
{
  if (tr[u].l == tr[u].r)
  {
    tr[u].minn = k;
    return;
  }
  int mid = tr[u].l + tr[u].r >> 1;
  if (x <= mid)
    modify(u << 1, x, k);
  else
    modify(u << 1 | 1, x, k);
  pushup(u);
}
ll qmi(int a, int b)
{
  ll res = 1;
  while (b)
  {
    if (b & 1)
      res = 1ll * res * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return res;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++)
  {
    cin >> id[i];
  }
  for (int i = 1; i <= n; i++)
  {
    ll x;
    cin >> x;
    v[id[i]] = max(v[id[i]], x);
    sum[id[i]] += x;
    tot += x;
  }
  for (int i = 1; i <= k; i++)
    w[i] = n * v[i] - sum[i] + tot;
  build(1, 1, k);
  ll inv = qmi(n, mod - 2) % mod;
  while (m--)
  {
    string s;
    cin >> s;
    if (s == "Query")
    {
      cout << tr[1].minn % mod * inv % mod << endl;
    }
    else
    {
      int x, y;
      cin >> x >> y;
      v[y] = max(v[x], v[y]), sum[y] = sum[x] + sum[y];
      v[x] = 0, sum[x] = 0;
      modify(1, x, 1e18);
      modify(1, y, n * v[y] - sum[y] + tot);
    }
  }
  return 0;
}


```

---

