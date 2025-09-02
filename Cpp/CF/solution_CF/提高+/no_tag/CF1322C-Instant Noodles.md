# Instant Noodles

## 题目描述

Wu got hungry after an intense training session, and came to a nearby store to buy his favourite instant noodles. After Wu paid for his purchase, the cashier gave him an interesting task.

You are given a bipartite graph with positive integers in all vertices of the right half. For a subset $ S $ of vertices of the left half we define $ N(S) $ as the set of all vertices of the right half adjacent to at least one vertex in $ S $ , and $ f(S) $ as the sum of all numbers in vertices of $ N(S) $ . Find the greatest common divisor of $ f(S) $ for all possible non-empty subsets $ S $ (assume that GCD of empty set is $ 0 $ ).

Wu is too tired after his training to solve this problem. Help him!

## 说明/提示

The greatest common divisor of a set of integers is the largest integer $ g $ such that all elements of the set are divisible by $ g $ .

In the first sample case vertices of the left half and vertices of the right half are pairwise connected, and $ f(S) $ for any non-empty subset is $ 2 $ , thus the greatest common divisor of these values if also equal to $ 2 $ .

In the second sample case the subset $ \{1\} $ in the left half is connected to vertices $ \{1, 2\} $ of the right half, with the sum of numbers equal to $ 2 $ , and the subset $ \{1, 2\} $ in the left half is connected to vertices $ \{1, 2, 3\} $ of the right half, with the sum of numbers equal to $ 3 $ . Thus, $ f(\{1\}) = 2 $ , $ f(\{1, 2\}) = 3 $ , which means that the greatest common divisor of all values of $ f(S) $ is $ 1 $ .

## 样例 #1

### 输入

```
3
2 4
1 1
1 1
1 2
2 1
2 2

3 4
1 1 1
1 1
1 2
2 2
2 3

4 7
36 31 96 29
1 2
1 3
1 4
2 2
2 4
3 1
4 3```

### 输出

```
2
1
12```

# 题解

## 作者：QwQcOrZ (赞：26)

看了好久官方题解才看懂，感觉这个证明方法好牛啊。

我来搬运一下官方题解，顺带说明一下它讲得不是很清楚的地方。

------------

记 $H_i$ 表示与第 $i$ 个右部点有连边的左部点的集合。

考虑将右部图的点分成几组，使每组的店都具有相同的 $H_i$。

然后，答案等于每个组中 $c_i$ 之和的 $\gcd$，$H_i$ 为空集的组除外。

让我们证明一下这为什么是对的。

------------

如果某些右部点具有相同的 $H_i$，则对于每个集合 $S$ 它们都将在 $N(S)$ 中（$N(S)$ 的含义在原题中），或者都不在 $N(S)$ 中。

这意味着我们可以将同组的所有顶点替换为权值等于这些顶点的 $c_i$ 之和的一个顶点。

之后，所有顶点中的数字都可以被答案整除（这里的答案是指由上面的结论得出的答案，即替换后每个顶点权值的 $\gcd$，所以可以整除），因此选出某些 $c_i$ 后它们的总和也一定可以被答案整除。

所以可以将所有权值除以答案，然后证明答案为 $1$。显然这和原问题等价。

考虑对于某个整数 $k>1$，证明一定有方案能找到一个左部点集合 $S$，使得$f(S)$ 不能被 $k$ 整除（$f(S)$ 的含义依然在原题题面中）。

如果权值的总和不能被 $k$ 整除，显然可以直接选上所有左部点。

因此只需要证明权值的总和能被 $k$ 整除的情况。

考虑找到一个最小度数的右部点 $v$，使其权值不能被 $k$ 整除（存在该顶点是因为右部点权值的 $\gcd$ 现在为 $1$，如果找不到显然 $\gcd$ 都为 $1$）。

于是我们选择 $H_v$ 的补集，可以发现与它有连边的右部点的权值和一定不能被 $k$ 整除。

为什么？考虑哪些右部点与该集合没有连边，首先 $v$ 一定是，还有 $H_i\subset H_v$ 的所有 $i$（每个 $i$ 的权值都一定可被 $k$ 整除）。但是 $v$ 的权值不能被 $k$ 整除，而 $H_v$ 的补集的答案显然为总权值和减去这些没有连边的点的权值，得证。

至于为什么都可以每个 $i$ 的权值都一定可被 $k$ 整除，首先 $H_i=H_v,i\not=v$ 的情况是不存在的，因为这样他们一定会合并为一个点。考虑如果存在一个 $i$ 使得 $H_i\subset H_v$ 且 $i$ 的权值不能被 $k$ 整除，那么它的度数小于 $i$。由于我们选的是度数最小的点，所以这种情况不可能出现。

------------

直接按照结论计算，用哈希合并即可。

---

## 作者：Redshift_Shine (赞：0)

今天听 fsz 讲课，太难了听不懂，于是和队友 duel，抽到了这道题，我看到 tag 里面的 hashing 心生一计，于是直接过掉。

首先由更相减损术可得 $\gcd(x,y)=\gcd(y,x-y)$，条件是 $x\ge y$。

然后可以想到，如果令右半部分中某个点出现的方法和另一个点完全一致，这两个点的权值实际上可被当成一个点看待。

如何理解这一点？想象一个 $n=3$ 的情况，连 $4$ 条边，$(1,1),(1,2),(2,2),(2,3)$。选中 $1$ 后，权值为 $v_1+v_2$。接下来加上 $2$，权值变为 $v_1+v_2+v_3$，那么这两种情况的 $\gcd$ 就是 $\gcd(v_1+v_2,v_1+v_2+v_3)=\gcd(v_1+v_2,v_3)$。
调换顺序，先选 $2$ 再选 $1$，权值分别为 $v_2+v_3$ 和 $v_1+v_2+v_3$，$\gcd$ 为 $\gcd(v_2+v_3,v_1+v_2+v_3)=\gcd(v_2+v_3,v_1)$。由 $\gcd(\gcd(a,b),\gcd(c,d))=\gcd(a,b,c,d)$ 可得 $\gcd$ 具有交换律和结合律，将上面的结果结合可得 $\gcd(v_1,v_2,v_3)$。

问题转换为如何快速进行一致出现节点的结合。

考虑为**左**节点随机赋权。每次加边时给对应**右**节点加上**左**节点的权值。由于本题保证没有重边就不需要额外的 `set` 去重了。最终把所有权值相同的点的 $v$ 值加起来做 $\gcd$ 即可。**注意排除权值为 $0$ 的节点**，他们选不到，自然也不会对 $\gcd$ 做出贡献。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <map>
#include <numeric>
#include <random>
using namespace std;
const int N = 5e5 + 10;
using ull = unsigned long long;
int n, m;
ull v[N], res;
map<ull, ull> mp;
ull buc[N], hss[N];
random_device rd;
mt19937 mt(rd());
void init_global()
{
}
void init_local()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%llu", v + i);
		hss[i] = mt();
		buc[i] = 0;
	}
	for (int i = 1, x, y; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		buc[y] += hss[x];
	}
}
void run()
{
	mp.clear();
	for (int i = 1; i <= n; i++)
	{
		mp[buc[i]] += v[i];
	}
	res = 0;
	for (auto &[k, v] : mp)
		if (k)
			res = res ? gcd(res, v) : v;
	printf("%llu\n", res);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

**引理：在整数范围内，$\gcd(x,y,x+y)=\gcd(x,y)$**。

证明：可以找到一个整数 $b$ 使得 $b|x,b|y$，且记所有可行的 $b$ 中最大的数为 $c$，则有：

$$
x\equiv y\equiv0\pmod{c}
$$

因为有 $x\equiv0\pmod{c}$，所以：

$$
2x\equiv x+y\equiv x\equiv0\pmod{c}
$$

所以 $x+y\equiv0\pmod{c}$。

此时 $c=\gcd(x,y)$，因此得证 $\gcd(x,y,x+y)=\gcd(x,y)$。

有了这一点理论，我们发现本题可以看成是求 $c_i$ 张成的线性空间中的最大公约数。

不妨将右部点看成左部点的映射，能观察到在右部点选择一个点等价于在左部点选择点集。贡献也能相应的算出。

由于右部点 $c_i$ 可张成线性空间，所以求任取 $c_i$ 的最大公约数和求所有 $c_i$ 的最大公约数是等价的。

最后只要注意合并相同的集合，并合并贡献即可。

集合用 set，映射用 map，总时间复杂度 $O(n \log n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e6 + 10;

int T, n, m, ans, c[N];

set<int> e[N];

map<set<int>, int> mp;

void solve() {
  ans = 0;
  map<set<int>, int>().swap(mp);
  For(i,1,n) set<int>().swap(e[i]);
  cin >> n >> m;
  For(i,1,n) cin >> c[i];
  For(i,1,m) {
    int u, v;
    cin >> u >> v;
    e[v].insert(u);
  }
  For(i,1,n) {
    if(e[i].size()) mp[e[i]] += c[i];
  }
  for (auto x : mp) {
    ans = __gcd(ans, x.second);
  }
  cout << ans << '\n';
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：lfxxx (赞：0)

CF 定向卡哈希太厉害了！

考虑最简单的情况，每个右边的点都可以单独选出来，假若右边全体点权的 $\gcd$ 为 $1$，就存在一组互质，那在所有组合的 $\gcd$ 中就有一个 $1$ 故答案只能是 $1$。

假若 $\gcd$ 为 $x$ 那么答案肯定不会小于 $x$ 因为不管怎么选都是 $x$ 的倍数，由于除去 $x$ 还是存在互质所以答案也不会大于 $x$。综上，这种情况下答案就是所有点权的 $\gcd$。

考虑更一般的情况，首先假若所有的集合点权分别为 $x_i$，那么答案就是 $\gcd_{i=1}^{k} x_i$。

由于 $\gcd$ 的性质，所以可以让任意一个集合 $i$ 的 $x_i$ 减去 $\sum_{j \in S} x_j$ 当然这里 $i$ 不在集合 $S$ 之中。

假若能到达某两个右部点的左部点集合不同，那么就可以构造一个只包含这两个点中某一个点的集合。

好，现在你选出了多组集合 ${A_1,A_2,...,A_k}$ 与 ${B_1,B_2,...,B_l}$ 这些集合中包含除了只能通过可以同时到达 $A,B$ 的左部点抵达的点，即它们的并集相同，根据 $\gcd$ 可以线性组合的性质，可以构造出它们的 $\gcd$ 一定就是 $\gcd(c_A,c_B)$。

假若可以抵达的左部点集合相同，那么就一定要同时选，合并即可。

哈希判断集合相同的时候记得实现好点别被卡了。

另外注意特判入度为 $0$ 的情况。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000000000000007
using namespace std;
const int maxn = 5e5+114;
int c[maxn],a[maxn];
map<int,int> val;
map<int,int> cnt[maxn];
int Hash[maxn];
int D[maxn];
int n,m;
void work(){
    val.clear();
    cin>>n>>m;
    for(int i=1;i<=n;i++) D[i]=a[i]=0,cin>>c[i],cnt[i].clear(),Hash[i]=(rand()*rand()*rand())%mod;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(cnt[v][u]==0) a[v]=(a[v]+Hash[u])%mod,cnt[v][u]++,D[v]++;
    }
    for(int i=1;i<=n;i++){
        val[a[i]]+=c[i];
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(D[i]==0) continue;
        ans=(ans==0?val[a[i]]:__gcd(ans,val[a[i]]));
    }
    cout<<ans<<'\n';
    return ;
}
signed main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}
```






---

## 作者：hleternity (赞：0)

### 简单题意

给定一张点数为 $2n$ 的二分图，其中右侧的点有点权 $a_i$。从左侧选择一个非空点集 $S$，设 $f(S)$ 表示右侧点中至少于左侧点有连边的点的点权和。求对所有的集合 $S$，$f(S)$ 的 $\gcd$。

### 思路

- 由 **更相减损法** 可知，$\gcd(a,b)=\gcd(a-b,b)$。  
  证明：
  
  - 不妨设 $a \geq b$，若 $a=b$，则 $\gcd(a,b)=a=b$。否则，设 $\forall d \mid a,d\mid b$，都有 $d\mid a-b$。
  
  - 因此，$a$ 和 $b$ 的所有公因数都是 $a-b,a,b$ 的公约数，故 $\gcd(a,b)=\gcd(a-b,b)$。
  
- 那么我们不妨设右边的两个点 $i,j$，$S_i,S_j$ 分别表示与该点有连边的左侧点的集合。

- 当 $S_i\cap S_j=\varnothing$，$ans=\gcd(ans,a_i,a_j)$。

  当 $S_i=S_j$，$ans=\gcd(ans,a_i)$。

  当 $S_i \cap S_j \neq \varnothing $，$ans=\gcd(ans,a_i+a_j)=\gcd(ans,a_i,a_j)$。

- 因此，我们只用统计出每个右侧点 $i$ 和所有左侧的有连边的集合 $S_i$ 和对应的权值 $sum_i$。最后 $ans=\gcd(sum_i)$。


---

