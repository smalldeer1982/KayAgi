# 【MX-X7-T4】[LSOT-3] 命运

## 题目背景

原题链接：<https://oier.team/problems/X7E>。

>「这里书写着世界的『命运』」$\\$
「当记载在此的未来成为真实之时」$\\$
「我的珍爱 就会变成『永远』了吧」

## 题目描述

我们在题目描述的最后提供了可以帮助理解题意的形式化题意。

Momoka 的一生中有 $n$ 个决定人生的事件，编号为 $1 \sim n$。命运的轨迹已经注定，会被第 $i$ 个事件影响的是第 $a_i$ 个事件，$a_i$ 互不相同。一个事件可能会影响过去，也可能会影响未来，甚至可以影响事件本身。

但是，因为 Momoka 的特殊能力，她的经历并不完全按照她的命运轨迹执行。有一些事件经历之后，原本应该被影响的事件不再被影响，转而影响命运轨迹中描述的会影响这个事件的事件。Momoka 的日记记录了她所经历的事件，日记可以看成是一个序列 $p$，$p_i$ 表示 Momoka 经历了第 $i$ 个事件后影响了事件 $p_i$。

Ringo 获得了日记本，她想要通过日记本来完成 M 计划。按照计划，她需要按照 Momoka 的命运轨迹来规划自己的人生。得到 Momoka 的日记之后，她想要知道 Momoka 原本的命运轨迹可能的方案数是多少。答案对 $998244353$ 取模。

**【形式化题意】**

给定一个长度为 $n$ 的序列 $p_1, \ldots, p_n$（未必为排列），保证 $1 \le p_i \le n$。求满足以下条件的**排列** $a_1, \ldots, a_n$ 的个数，对 $998244353$ 取模：

> 对每个 $1 \le i \le n$，都有 $a_i=p_i$ 或者 $a_{p_i}=i$ 成立。

## 说明/提示

**【样例解释 #1】**

有以下六种可能的命运轨迹：`2 3 1 5 4`、`2 3 4 5 1`、`2 3 5 1 4`、`3 1 2 5 4`、`4 1 2 5 3`、`5 1 2 3 4`。

**【数据范围】**

**本题采用捆绑测试。**

- 子任务 1（15 分）：$n\le 10$。
- 子任务 2（15 分）：序列 $p$ 中 $1$ 的个数 $\ge \frac{n}{5}$。
- 子任务 3（15 分）：序列 $p$ 是排列。
- 子任务 4（25 分）：对于所有 $i,j$ 满足 $i\ne j\wedge p_i=j\wedge p_j=i$，都存在至少一个 $k\ne i\wedge k\ne j$ 满足 $p_k=i \vee p_k=j$。
- 子任务 5（30 分）：无特殊性质。

对于全部的数据，$1\le n\le 10^6$，$1\le p_i\le n$。

## 样例 #1

### 输入

```
5
2 3 2 5 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
17 18 20 6 8 4 15 5 14 20 4 3 19 6 7 17 16 8 10 10
```

### 输出

```
3456
```

# 题解

## 作者：CarroT1212 (赞：9)

~~我擦，企鹅罐！生存战略！~~

挺好的性质题。写详细亿点。

排列可以看成有向环集合来计数。设在 $p$ 上对于每个 $i$，在图上连接 $i\leftrightarrow p_i$ 得到的无向图为 $G_1$，在 $a$ 上对于每个 $i$ 连接 $i\to a_i$ 得到的有向图为 $G_2$。那么 $a$ 合法仅当 **$G_1$ 的每条边的其中一个方向都在 $G_2$ 中出现**。$G_1$ 已知了，我们需要知道合法的 $G_2$ 数，考虑刻画。

首先由于 $a$ 是排列，$G_2$ 只包含有向环，那么 $G_1$ 出现一个度数 $\ge 3$ 的点就包没合法 $G_2$ 的。考虑到 $G_1$ 出来会是个基环森林，都不能有森林了，看起来 $G_1$ 也必须是一堆环构成的啊？

（观察样例）发现有个奇怪情况：$G_1$ 里有二元环。你会发现这里我们应该要**将这个二元环当作一条无向边**来看待，因为 $G_2$ 只需要有一条有向边就可以同时消灭二元环里的两条边。

于是把二元环换成无向边后 $G_1$ 里出现了链！现在看看怎么个事。

+ $G_1$ 中有点度数 $\ge 3$，无解。
+ 对于 $G_1$ 中的自环，不用管它，它在 $G_2$ 里还是自环。
+ $G_1$ 中点数 $\ge 3$ 的环，在 $G_2$ 中这些边都需要出现，每个环都有两种定向方法，统计环数 $k$ 最后乘上 $2^k$。
+ $G_1$ 中的链，我们在 $G_2$ 中需要给每条链定向，然后用若干条有向边把它们的两端连接起来，变成若干有向环集合。设链数为 $x$，要是把定向完的链看成一个大点，那这个连接过程其实就是**根据一个长度为 $x$ 的排列建 $G_2$ 的过程**，连接方案数为 $x!$（每条链定向完后只有一个点能接受入边，一个点输出出边，而外部新连的边的方向已经根据连接情况确定）。而每条链内部有两种定向方式，再乘上 $2^x$……

别急，还有高手！如果 $G_2$ 里又连出了二元环，这时**这个环的两种定向方式在 $G_2$ 里看起来是一样的**！算重到起飞！

这种情况要求 $G_1$ 里存在一个孤单的二元环被变成了一条无向边，然后我们在后期连接的时候直接将它的两端连了起来。设 $G_1$ 中这样单独的一条无向边作一条链的条数为 $y$。

没事还可以容斥，我们钦定其中 $i$ 条边在 $G_2$ 里被当成二元环的另一个方向算重的方案数为 $f_i$。有 $f_i=\binom{y}{i}2^{x-i}(x-i)!$。最后 $ans=2^k\sum\limits_{i=0}^y(-1)^if_i$。

实现就是看看 $G_1$ 里上面几种东西都有几种，算就完了。小心漏了什么阴间情况。

```cpp
const ll J=1e18,N=1e6+7,P=998244353;
ll qp(ll x,ll y=P-2) { return y?(y&1?x:1)*qp(x*x%P,y>>1)%P:1; }
ll fac[N],fnv[N];
struct init { init() {
	fac[0]=1; for (ll i=1;i<N;i++) fac[i]=fac[i-1]*i%P;
	fnv[N-1]=qp(fac[N-1]); for (ll i=N-1;i;i--) fnv[i-1]=fnv[i]*i%P;
} } A;
ll C(ll x,ll y) { return x<0||y<0||x<y?0:fac[x]*fnv[y]%P*fnv[x-y]%P; }
ll n,a[N],ans,vis[N];
ll c3,c21,c22;
vector<ll> e[N];
void no() { cout<<"0",exit(0); }
void get(ll p) {
	if (e[p].size()>1) no();
	vis[p]=1;
	if (e[p].size()==1&&!vis[e[p][0]]) get(e[p][0]);
}
void mian() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) scanf("%lld",&a[i]),e[a[i]].pb(i);
	for (ll i=1;i<=n;i++) if (!vis[i]) {
		if (a[i]==i) {
			if (e[i].size()>1) no();
			vis[i]=1;
		}
		else if (a[a[i]]==i) {
			ll x=i,y=a[i],flg=0;
			vis[x]=vis[y]=1;
			if (e[x].size()>2||e[y].size()>2) no();
			if (e[x].size()==2) flg=1,get(e[x][0]^e[x][1]^y);
			if (e[y].size()==2) flg=1,get(e[y][0]^e[y][1]^x);
			flg?c22++:c21++;
		}
	}
	for (ll i=1;i<=n;i++) if (!vis[i]) {
		if (!e[i].size()) no();
		c3++,get(i);
	}
	ll ans=0;
	for (ll i=0;i<=c21;i++) (ans+=(i&1?P-1:1)*C(c21,i)%P*qp(2,c21+c22-i)%P*fac[c21+c22-i])%=P;
	cout<<ans*qp(2,c3)%P;
}
```

---

## 作者：良心WA题人 (赞：5)

排列建有向图后是一些环，逆排列是这些环的边全部反向。对序列建基环树，相当于基环树上每条边定向，然后划分为两个图，最终两个图分别是同一个仅由环组成的图的正反向的一部分。

所以说不难注意到如果存在点在基环树里面度数 $\ge 3$ 时必须要通过重边消掉度数，否则就寄了。那么基环树上的环要么是一个纯环，要么是一个度数为 $2$ 的环拼上两条链，可以通过将环定向为重边并让两条链定相同的方向，让这个基环树变成一条链。

问题转化为让链拼起来成纯环的方案数（每个链可以是正向或者反向）。先钦定每条链的方向，是一个二的幂次，然后再把每一个尾接一个头，是排列的方案数。注意大小为 $1$ 的纯环不允许反向。

注意到，这样做序列有二元环会算重，因为二元环正向反向是相同的。考虑容斥钦定有多少个二元环发生了反向，剩下的随意即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=1e6+4,P=998244353;
int fac[NN],ifac[NN];
int qmi(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1ll*res*a%P;
		a=1ll*a*a%P;
		b>>=1;
	}
	return res;
}
int C(int a,int b)
{
	if(a<b||b<0)
		return 0;
	return 1ll*fac[a]*ifac[b]%P*ifac[a-b]%P;
}
int p[NN],cnt1,cnt2;
bool vis[NN];
set<int>g[NN];
void dfs(int u)
{
	vis[u]=true;
	cnt1++;
	cnt2+=g[u].size();
	for(auto v:g[u])
		if(!vis[v])
			dfs(v);
}
int main()
{
	fac[0]=1;
	for(int i=1;i<NN;i++)
		fac[i]=1ll*fac[i-1]*i%P;
	ifac[NN-1]=qmi(fac[NN-1],P-2);
	for(int i=NN-2;~i;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%P;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		g[x].insert(i);
		g[i].insert(x);
	}
	for(int i=1;i<=n;i++)
		if(g[i].size()>=3||g[i].size()==2&&(*g[i].begin()==i||*++g[i].begin()==i))
		{
			printf("0");
			return 0;
		}
	int w1=0,w2=0,w3=0;
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			cnt1=cnt2=0;
			dfs(i);
			if(cnt1==1);
			else if(cnt2==cnt1*2)
				w1++;
			else if(cnt1==2)
				w2++;
			else
				w3++;
		}
	int ans=0;
	for(int i=0,o=1;i<=w2;i++,o=1ll*o*(P-1)%P)
		ans=(ans+1ll*C(w2,i)*qmi(2,w3+w2-i)%P*fac[w3+w2-i]%P*o%P)%P;
	ans=1ll*ans*qmi(2,w1)%P;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Drifty (赞：3)

好厉害的题。

### Solution

首先把 $(i, a_i)$ 都连上无向边，造出来一个基环树森林。

注意到排列连完边了之后构成一个有向环的集合，那么把边看作等量关系，会发现问题等价于在无向图上每条边任选一条方向使得这个有向环集合能够包含这个无向图的有向图的方案数。

然后你会发现在无向图中，基环数的环有可能是二元环，这种情况我们直接把它看作一整条等价的链方便统计。

显然，如果图中存在度数大于 $2$ 的点就无解。

接下来图由环和链构成。

接下来分讨，把自环、环和链的个数求出来做掉。

但是这样做会发现对于二元环会寄，原因是二元环中正反是无所谓的，那么我们就钦定不变的二元环的个数，然后容斥就可以去重了，注意实际上是跟链一起做掉的。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int64_t P = 998244353;
constexpr size_t N = 1e6 + 7;
auto fpow = [](i64 a, int x) {
    i64 ans = 1;
    for (; x; x >>= 1, a = a * a % P)
        if (x & 1) ans = ans * a % P;
    return ans;
};
auto get_factorial = [](i64 *f, i64 *g, size_t n) -> void {
    f[0] = g[0] = 1;
    for (size_t i = 1; i <= n; i ++) f[i] = f[i - 1] * i % P;
    g[n] = fpow(f[n], P - 2);
    for (size_t i = n - 1; i; i --) g[i] = (i + 1) * g[i + 1] % P;
};
int n;
bool vis[N];
i64 fc[N], ifc[N], ans;
set <int> e[N];
auto C = [](i64 n, i64 m) {
    return n < 0 || m < 0 || n < m ? 
        0ll : fc[n] * ifc[m] % P * ifc[n - m] % P;
};
void dfs (int u, int &x, int &y) {
    vis[u] = 1; x ++; y += e[u].size();
    for (auto v : e[u]) if (!vis[v]) dfs (v, x, y);
}

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);
    cin >> n;
    for (int i = 1, w; i <= n; i ++) 
        cin >> w, e[i].insert(w), e[w].insert(i);
    get_factorial (fc, ifc, n);
    for (int i = 1; i <= n; i ++) if (e[i].size() > 2 || 
        (e[i].size() == 2 && find(e[i].begin(), e[i].end(), i) != 
        e[i].end())) return cout << 0 << '\n', 0; 
    int cyc = 0, lin = 0, cnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) {
            int x = 0, y = 0;
            dfs (i, x, y);
            if (x == 1) continue;
            if (x * 2 == y) /*环*/ cyc ++;
            else if (x == 2) /*二元环*/ cnt ++;
            else lin ++;
        }
    }
    for (int i = 0; i <= cnt; i ++) {
        ans = (ans + C(cnt, i) * fpow(2, lin + cnt - i) % P *
        fc[lin + cnt - i] % P * (i % 2 ? P - 1 : 1) % P) % P;
    }
    cout << ans * fpow(2, cyc) % P << '\n';
    return 0; 
}
```

---

## 作者：ty_mxzhn (赞：2)

题面差评，写得太糊了。

## 简要题意

有一个无向图，你要求出拿一些不交的有向环覆盖所有无向边的其中一个方向的方案数。

## 题解

显然无向图的度数不超过 $2$ 否则无解。这样图中只有链，环和孤立点这三种东西了。

环可以自己用两种方式覆盖，孤立点扔掉不管，链串在一起。这三种方案都是好算的。

但是我们还要考虑两个点组成的链，实际上这种情况链内部的两种定向再加上一个自环就会算重。

枚举这样的点的数量，然后直接容斥即可。

时间复杂度 $O(n)$。

---

