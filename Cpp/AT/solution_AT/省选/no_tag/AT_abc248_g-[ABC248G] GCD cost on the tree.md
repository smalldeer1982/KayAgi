# [ABC248G] GCD cost on the tree

## 题目描述

给定一颗树有 $n$ 个结点，每个结点上有一个权值 $a_i$, 对于每条**至少包含两个点**的**简单路径**，它的贡献为 路径上点的数量(包括端点)$\times$路径上所有点的 $a_i$ 
的最大公约数(gcd)。  
求所有简单路径的贡献之和，对 $998244353$ 取模。

## 说明/提示

$2 \le n \le 10^5$  
$1 \le a_i \le 10^5$

## 样例 #1

### 输入

```
4
24 30 28 7
1 2
1 3
3 4```

### 输出

```
47```

## 样例 #2

### 输入

```
10
180 168 120 144 192 200 198 160 156 150
1 2
2 3
2 4
2 5
5 6
4 7
7 8
7 9
9 10```

### 输出

```
1184```

# 题解

## 作者：Miraik (赞：10)

考虑枚举 GCD 的值为 $t$，求出每个 $t$ 对应的方案数 $f_t$。

直接求出有多少路径的 GCD 等于它不好求，我们考虑先求出满足 GCD 的值为 $t$ 的倍数的方案数 $g_t$，则 $f_t=g_t-\sum{f_{it}} (i>1)$。

对于 $g_t$，我们先把所有满足 $t \space | \space a_i$ 的 $i$ 拉出来建出一个森林，在每一棵树上做树形 dp：

$cnt_i$ 表示 $i$ 的子树内，有一端点为 $i$ 的链的个数。

$len_i$ 表示 $i$ 的子树内，有一端点为 $i$ 的链的链长之和（准确的说应该是包括的点个数，没啥差别）。

$res_i$ 表示 $i$ 的子树内，经过 $i$ 的所有长度大于 $1$ 的链的长度之和。

那么 $g_t=\sum{res_i}$。

对于边 $(u,v)$，有转移：

$res_u=res_u+cnt_u \times len_v + cnt_v \times len_u$

前面的 $res_u$ 是因为 $v$ 子树内可以不选（但是 $u$ 必须选），后面是计算两棵子树合并，子树根处两条链拼起来的总长度。

$len_u=len_u+len_v+cnt_v$

$v$ 子树内的链会和 $u$ 接起来，长度加 $1$。

$cnt_u=cnt_u+cnt_v$

与 $len_u$ 同理。

然后就做完了，时间复杂度 $O(V \log V +n \sqrt V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void dfs(int u,int tt){
    cnt[u]=1; len[u]=1; res[u]=0; col[u]=0;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(!col[v]) continue;
        dfs(v,tt);
        res[u]=(res[u]+(1ll*cnt[u]*len[v]%mod+1ll*cnt[v]*len[u]%mod)%mod)%mod;
        len[u]=(len[u]+len[v]+cnt[v])%mod;
        cnt[u]=cnt[u]+cnt[v];
    }
    (ans[tt]+=res[u])%=mod;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        int x=read(); m=max(m,x);
        for(int j=1;j*j<=x;j++)
            if(x%j==0){
                g[j].emplace_back(i);
                if(j*j<x) g[x/j].emplace_back(i);
            }
    }
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v); add(v,u);
    }
    for(int i=m;i;i--){
        if(g[i].empty()) continue;
        for(int j=0;j<g[i].size();j++) col[g[i][j]]=1;
        for(int j=0;j<g[i].size();j++) if(col[g[i][j]]) dfs(g[i][j],i);
        for(int j=i+i;j<=m;j+=i) (ans[i]+=mod-ans[j])%=mod;
    }
    for(int i=1;i<=m;i++) (sum+=1ll*ans[i]*i%mod)%=mod;
    printf("%d\n",sum);
    return 0;
}
```


---

## 作者：lzyqwq (赞：4)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17736146.html)**

**[AT](https://atcoder.jp/contests/abc248/tasks/abc248_g) [洛谷](https://www.luogu.com.cn/problem/AT_abc248_g)**

> - 给出一棵 $n$ 个点的树，点 $i$ 有点权 $a_i$。定义 $u,v$ 间的路径的权值 $C(u,v)$ 为，这条路径上的点数乘上路径上所有点的 $\gcd$。
>
> - 形式化的，若点 $u$ 到点 $v$ 的路径为 $p_1,p_2,\dots,p_k\,(p_1=u,p_k=v)$，则 $C(u,v)=\gcd(a_{p_1},a_{p_2},\dots,a_{p_k})$。
>
> - 求 $\left(\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n C(i,j)\right)\bmod \color{red}\boldsymbol{998244353}$。某个【数据删除】把模数看成了 $10^9+7$，是谁我不说。
>
> - $n,\max\limits_{i=1}^n a_i\le 10^5$。

约定：记 $d(n)$ 为 $n$ 的正因子个数。形式化的，$d(n)=\sum\limits_{i=1}^n[i\,|\,n]$。

直接大力点分治好吧，类似题 [CF1101D](https://www.luogu.com.cn/problem/CF1101D)，[CF990G](https://www.luogu.com.cn/problem/CF990G)。

考虑如何计算经过当前分治中心 $rt$ 的路径的贡献。我们用从 $rt$ 不同子树内的点到分治中心的链，拼接起来（$rt$ 拼接的时候去重），得到一条路径。也可以单链成为一条路径。这都是套路。为了不重不漏地拼接，考虑用后面的子树的链匹配之前的子树的链。

$\gcd$ 有一个众所周知的性质，即 $\gcd(a,b,c)=\gcd(\gcd(a,b),\gcd(b,c))$。我们用 $val_u$ 表示 $rt$ 到 $u$ 的链上的点的 $\gcd$，$dep_u$ 表示 $rt$ 到 $u$ 的边数。则对于 $rt$ 子树内的点 $u,v$，$C(u,v)=\gcd(val_u,val_v)\times (dep_u+dep_v\boldsymbol{+1})$。考虑如何快速计算，用 `std::unordered_map` 或 `__gnu_pbds::gp_hash_table` 维护桶 $mp_{1_x}$ 表示之前子树内，$val$ 值为 $x$ 的链的 $dep$ 值和；桶 $mp_{2_x}$ 表示之前子树内，$val$ 值为 $x$ 的链的数量。我们枚举当前子树内的点 $u$，再枚举之前的链的 $\gcd$ 值，它们一定在同理。即遍历桶内的元素，设遍历到的下标为 $x$，则该种下标产生的贡献为 $[(dep_u+1)\times mp_{2_x}+mp_{1_x}]\times \gcd(x,val_u)$。统计完右链在当前子树内的路径后，更新桶。

单链的情况类似求，然后继续分治下去。看似很暴力，但是你注意到桶内的元素一定是 $a_{rt}$  的因数，我们一共分治 $\mathcal{O}(\log n)$ 层，每层每个点被遍历 $\mathcal{O}(1)$ 次，遍历的时间为 $\mathcal{O}(d(a_{rt}))$。这样一来时间复杂度为 $\mathcal{O}(n\log n \cdot \max\limits_{i=1}^nd(a_i))$。

首先一个数 $x$ 的正因子个数不超过 $\mathcal{O}(\sqrt{x})$。设值域为 $V$，我们可以认为时间复杂度为 $\mathcal{O}(n\log n\cdot \sqrt{|V|})$。由于值域只有 $10^5$，配合 $8$ 秒的时限，可以通过。~~确实很暴力~~。

进一步思考，我们发现在这个值域内，$\max\limits_{i=1}^nd(a_i)$ 不超过 $128$。你可以自己验证一下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int ans = 0;
    for (int i = 1; i <= 100000; ++i) {
        int tot = 0;
        for (int j = 1; j * j <= i; ++j) {
            if (!(i % j)) tot += 2;
            if (j * j == i) --tot;
        }
        ans = max(ans, tot);
    }
    cout << ans;
}
```
所以我们把 $\max\limits_{i=1}^nd(a_i)$ 看作 $128$ 的话，会比 $\mathcal{O}(\sqrt{|V|})$ 优秀一点。好好好，${128}$ 倍大常数~~优秀~~ $\text{polylog}$ 做法。

不过为了保证复杂度正确，切记 **$\boldsymbol{val}$ 数组指的是某个点到分治中心 $\boldsymbol{rt}$ 的链上的点权值的最大公约数，若定义成到该子树根的链上的点权值的最大公约数，那么每个点在一次分治中枚举之前链的实际次数会变成，所有 $\boldsymbol{rt}$ 的儿子的权值的约数集合的并集的大小，枚举次数就无法得到保证了**。

总结一下，时间复杂度为 $\mathcal{O}(n\log n \cdot \max\limits_{i=1}^{|V|} d(i))$，空间复杂度为 $\mathcal{O}(n+|V|)$，可以接受。~~[直接喜提你谷最劣解](https://www.luogu.com.cn/record/list?pid=AT_abc248_g&orderBy=1&status=&page=2)~~。

**[提交记录](https://atcoder.jp/contests/abc248/submissions/46004995)**

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define fi first 
#define se second 
using namespace std; typedef long long ll; const int N = 1e5 + 5, M = 998244353;
int n, a[N], dep[N], val[N], siz[N], maxn[N], rt, tot, stk[N], top, p[N], cnt; 
vector<int> g[N]; bool vis[N]; ll ans; unordered_map<int, ll> mp1, mp2;
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
void gravity(int u, int fa) {
    siz[u] = 1; maxn[u] = 0;
    for (int v : g[u]) {
        if (v == fa || vis[v]) continue; gravity(v, u);
        siz[u] += siz[v]; maxn[u] = max(maxn[u], siz[v]);
    }
    maxn[u] = max(maxn[u], tot - siz[u]); if (maxn[u] < maxn[rt]) rt = u;
}
void get(int u, int fa) {
    p[++cnt] = u;
    for (int v : g[u]) {
        if (v == fa || vis[v]) continue;
        val[v] = __gcd(val[u], a[v]); dep[v] = dep[u] + 1; get(v, u);
    }
}
void divide(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (vis[v]) continue; dep[v] = 1, val[v] = __gcd(a[u], a[v]); cnt = 0; get(v, u);
        for (int i = 1; i <= cnt; ++i) {
            int x = p[i];
            for (auto j : mp1) {
                ll w = __gcd(val[x], j.fi);
                ans += (1ll * (dep[x] + 1) * mp2[j.fi] + j.se) * w; ans %= M;
            }
        }
        for (int i = 1; i <= cnt; ++i) {
            int x = p[i]; ++mp2[val[x]]; mp1[val[x]] += dep[x]; 
            stk[++top] = val[x];
        }
    }
    for (auto j : mp1) {
        ll w = j.fi; ans += (j.se + mp2[j.fi]) * w; ans %= M;
    }
    for (; top; --top) mp1[stk[top]] = mp2[stk[top]] = 0;
    for (int v : g[u]) {
        if (vis[v]) continue; 
        tot = siz[v]; rt = 0; gravity(v, 0); gravity(rt, 0); divide(rt);
    }
}
signed main() {
    read(n); for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1, u, v; i < n; ++i)
        read(u), read(v), g[u].emplace_back(v), g[v].emplace_back(u);
    tot = n; maxn[0] = M; gravity(1, 0); gravity(rt, 0);
    divide(rt); print(ans); return 0;
}
```


---

## 作者：Cx114514 (赞：3)

### 题目链接：[[ABC248G] GCD cost on the tree](https://www.luogu.com.cn/problem/AT_abc248_g)
**注：下文 $V$ 代表值域最大值。**

考虑从 $1\sim V$ 枚举因数，设 $f_{i}$ 表示 $\gcd$ 是 $i$ 的倍数的路径总长度，$g_{i}$ 表示 $\gcd$ 恰好为 $i$ 的路径总长度。

由容斥原理可得：

$g_{i}=f_{i} - \sum\limits_{j=2}^{\left \lfloor  \frac{V}{i}\right \rfloor }g_{ij}$

则最终答案为 $\sum\limits_{i=1}^{V} i\times g_{i}$。

实现如下：

从 $1\sim V$ 枚举因数，每次保留是权值当前值的倍数的点，此时原图被分成了若干个森林，在每棵树上利用 DP 求解最终答案。

该做法的时间复杂度关键在于 DFS 的总规模，很多题解并没有提到。（我一开始想到这个做法，但以为复杂度是假的）

对于树中的每条边，只有枚举的因数是该边的两端点中任一的权值因数，该边才会被遍历到。故总规模为 $O\left(\sum\limits_{i=1}^{V}d\left(i\right)\right)$，可以通过本题。

接下来考虑 DP 的具体过程：

设 $ans_{i}$ 表示以 $i$ 为根的子树中经过 $i$ 的链的总长度。

设 $cnt_{i}$ 表示以 $i$ 为根的子树中一端点为 $i$ 的链的个数。

设 $len_{i}$ 表示以 $i$ 为根的子树中一端点为 $i$ 的链的总长度。

对于一条边 $\left(u,v\right)$，有转移如下：

 $$ans_{u}=ans_{u}+cnt_{v}\times len_{u}+cnt_{u}\times len_{v}$$ 

 $$len_{u}=len_{u}+len_{v}+cnt_{v}$$ 

 $$cnt_{u}=cnt_{u}+cnt_{v}$$

时间复杂度为 $O\left(V\ln V+n\sqrt V+\sum\limits_{i=1}^{V}d\left(i\right)\right)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;

int n, res, a[100005], f[100005], cnt[100005], len[100005], ans[100005], vis[100005];

vector < int > G[100005], p[100005];

void dfs(int u)
{
	cnt[u] = 1;
	len[u] = 1;
	ans[u] = 0;
	vis[u] = 0;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (!vis[v]) continue;
		dfs(v);
		ans[u] = (ans[u] + cnt[u] * len[v] + cnt[v] * len[u]) % mod;
		len[u] = (len[u] + len[v] + cnt[v]) % mod;
		cnt[u] = (cnt[u] + cnt[v]) % mod;
	}
}

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
	{
		int t = sqrt(a[i]);
		for (int j = 1; j <= t; j++)
		{
			if (a[i] % j == 0)
			{
				p[j].push_back(i);
				if (a[i] / j != j) p[a[i] / j].push_back(i);
			} 
		}	
	}
	for (int i = 1; i <= 100000; i++)
	{
		for (int j = 0; j < p[i].size(); j++)
			vis[p[i][j]] = 1;
		for (int j = 0; j < p[i].size(); j++)
		{
			int u = p[i][j];
			if (vis[u] == 0) continue;
			dfs(u);
		}
		int sum = 0;
		for (int j = 0; j < p[i].size(); j++)
			sum = (sum + ans[p[i][j]]) % mod;
		f[i] = sum;
	}
	for (int i = 100000; i >= 1; i--)
		for (int j = 2 * i; j <= 100000; j += i)
			f[i] = (f[i] - f[j] + mod) % mod; 
	for (int i = 1; i <= 100000; i++)
		res = (res + i * f[i]) % mod;
	cout << res << endl;
    return 0;
}
```

---

## 作者：ran_qwq (赞：3)

枚举 $d=\gcd(\{A_{p_k}\})$，即求

$$\sum\limits_d\sum\limits_{i=1}^n\sum\limits_{j=i+1}^nk\cdot[\gcd(\{A_{p_k}\})=d]$$

gcd 等于 $d$ 不好求，考虑容斥一下，转化为 gcd 是 $d$ 的倍数，设 $f(d)$ 为 gcd 是 $d$ 的倍数的 $k$ 之和，$g(d)$ 为 gcd 恰好等于 $d$ 的 $k$ 之和，原式转化为

$$\sum\limits_dg(d)\cdot d$$

且有关系式

$$g(d)=f(d)-\sum\limits_{d\mid i}g(i)$$

现在我们的问题是如何求出 $f(d)$。把所有 $d\mid A_i$ 的点拿出来，形成森林。对于森林中的每棵树答案是独立的。考虑对于每个点计算贡献，设 $h(i)$ 为经过 $i$ 的路径总长度，则

$$g(d)=\sum\limits_{i=1}^n h(i)$$

考虑如何计算 $h(i)$。设 $t$ 为当前森林大小，$s(i)$ 为以该森林任一点为根，$i$ 子树大小。

为了方便，以下钦定当 $x\ne y$ 时，$x\rightarrow y$ 和 $y\rightarrow x$ 是不同的路径，计算答案时除个 $2$，即一棵树路径有 $t^2$ 条。对于一个点 $i$，不合法路径要么起点终点都在 $i$ 的儿子 $j$ 子树内，要么都在 $i$ 的子树外，要么起点终点都是 $i$。所以

$$h(i)=t^2-\sum\limits_{j\in son_i}s(j)^2-(t-s(i))^2-1$$

$t$ 和 $s(i)$ 都可以用 dfs 求。先求 $h(i)$，再求 $g(d)$，最后求 $f(d)$，一步一步倒推回去求出答案。

```cpp
int n,id,cnt,ans,a[N],f[N],hd[N],vis[N],siz[N],to[N*2],ne[N*2]; vi tmp,t[N];
void add(int x,int y) {to[++id]=y,ne[id]=hd[x],hd[x]=id;}
void dfs1(int u,int fa,int d) {cnt++,vis[u]=1; for(int i=hd[u],v;i;i=ne[i]) cw((v=to[i])!=fa&&a[v]%d==0,dfs1(v,u,d));}
void dfs2(int u,int fa,int d) {
	siz[u]=1; for(int i=hd[u],v;i;i=ne[i]) cw((v=to[i])!=fa&&a[v]%d==0,(dfs2(v,u,d),siz[u]+=siz[v],csub(f[d],vmul(siz[v],siz[v]))));
	cadd(f[d],vsub(vmul(cnt,cnt),vadd(vmul(cnt-siz[u],cnt-siz[u]),1)));
}
void QwQ() {
	n=rd(); for(int i=1;i<=n;i++) {a[i]=rd(); for(int j=1;j*j<=a[i];j++) if(a[i]%j==0) t[j].pb(i),cw(j*j!=a[i],t[a[i]/j].pb(i));}
	for(int i=1,x,y;i<n;i++) x=rd(),y=rd(),add(x,y),add(y,x);
	for(int i=1;i<=N-10;i++) {
		for(int j:t[i]) if(!vis[j]) cnt=0,dfs1(j,0,i),dfs2(j,0,i);
		for(int j:t[i]) vis[j]=siz[j]=0;
	}
	for(int i=N-10;i;i--) {for(int j=i*2;j<=N-10;j+=i) csub(f[i],f[j]); cadd(ans,vmul(f[i],i));}
	wr(vmul(ans,(MOD+1)/2),"\n");
}
```

---

## 作者：sunkuangzheng (赞：3)

$\textbf{ABC248G}$

> - 给定 $n$ 个点的树，定义 $f(u,v)$ 为路径 $u,v$ 上所有点的 $\gcd$，$g(u,v)$ 为路径 $u,v$ 的长度，求：
>  $$\sum \limits_{i=1}^n \sum \limits_{j=i+1}^n f(i,j) \cdot g(i,j)$$
> - $1 \le n,a_i \le 2 \cdot 10^5$，时间限制 $8.0$ 秒。

路径问题直接点分治，注意到贡献为和式，允许我们容斥。对于分治中心 $rt$，设有 $m$ 个点，定义 $f_u$ 为 $rt \to u$ 路径上的 $\gcd$，$g_u$ 为点 $u$ 的深度，则等价于求：

$$\sum \limits_{i=1}^m \sum \limits_{j=1}^{i-1} \gcd(f_i,f_j) \cdot (g_i+g_j)$$

直接大力推式子：

$$\begin{aligned}&\sum \limits_{j=1}^{i-1} \gcd(f_i,f_j) \cdot (g_i+g_j)\\=&\sum \limits_{j=1}^{i-1}\sum\limits_{d|f_i}[d|f_j] \cdot\varphi(d) \cdot (g_i+g_j)\\=&\sum\limits_{d|f_i}(sm_d+ct_d \cdot g_i) \cdot\varphi(d) \end{aligned}$$

其中 $sm_d$ 指 $a_j$ 是 $d$ 倍数的 $g_j$ 之和，$ct_d$ 指 $a_j$ 是 $d$ 倍数的数字数量。

那么我们预处理 $\varphi(d)$ 的值就可以在 $\mathcal O(m \cdot d(V))$ 的时间复杂度内求解单个分治中心的询问。总复杂度为 $\mathcal O(n \cdot d(V)\log n )$。

~~我也不知道这个极高的复杂度配上点分治极大的常数到底能不能过。~~

事实上它跑得非常快，~~比一些不带 $\log$ 的题解还快~~。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 15.04.2024 17:10:21
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5,mod = 998244353;
using namespace std;
int T,n,a[N],u,v,vis[N],tt,rt,siz[N],f,phi[N]; vector<int> g[N],dr[N],pr; vector<tuple<int,int>> tp; ll sm[N],ct[N];
__int128 ans;
#define ff for(int v : g[u]) if(v != f && !vis[v]) 
void dfs1(int u,int f,int sz){
    siz[u] = 1; int mx = 0;
    ff dfs1(v,u,sz),siz[u] += siz[v],mx = max(mx,siz[v]);
    if(mx = max(mx,sz - siz[u]),mx < tt) tt = mx,rt = u; 
}void dfs3(int u,int f,int gd,int d){gd = gcd(gd,a[u]),tp.emplace_back(gd,d); ff dfs3(v,u,gd,d+1);}
void slv(int u,int g,int op){
    tp.clear(),dfs3(u,0,g,(op == -1 ? 1 : 0));
    for(auto [a,b] : tp) for(int d : dr[a])
        ans += op * phi[d] * (sm[d] + ct[d] * (b + 1)),sm[d] += b,ct[d] ++;
    for(auto [a,b] : tp) for(int d : dr[a]) sm[d] = ct[d] = 0;
}void dfs2(int u){slv(u,0,1),vis[u] = 1; ff slv(v,a[u],-1),tt = 1e9,dfs1(v,u,siz[v]),dfs2(rt);}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n,phi[1] = 1;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    int d = *max_element(a+1,a+n+1);
    for(int i = 2;i <= d;i ++){
        if(!vis[i]) pr.push_back(i),phi[i] = i - 1;
        for(int j : pr){
            if(i * j > d) break;
            vis[i * j] = 1,phi[i * j] = phi[i] * phi[j];
            if(i % j == 0){phi[i*j] = j * phi[i]; break;}
        }
    }for(int i = 1;i <= d;i ++)
        for(int j = i;j <= d;j += i) dr[j].push_back(i);
    memset(vis,0,sizeof(vis));
    tt = 1e9,dfs1(1,0,n),dfs2(rt),cout << (ll)(ans % mod);
}
```

---

## 作者：BreakPlus (赞：2)

退役幼稚选手闲暇时间来贡献社会了。

首先我们要知道这样一个性质：$ x = \sum \limits_{d|x} \varphi(d)$

这里我们说一些别的事情：本质上，大力容斥和我们用的 $\varphi(x)$ 和 $\varepsilon(x) = \sum \limits_{d|x} \mu(x)$ 本质上干的都是一件事情。

那么我们在具体问题的时候可能会被容斥绕晕

那么不妨使用上面的两个式子，只需要纯纯的代数运算。

话说回来，我们用这个式子一套原式（定义 $\text{g}(x,y)$ 表示两点路径之间的 $\gcd$）：

$\sum \limits_{k=1}^{10^5} \varphi(k) \sum \limits_{\text{g}(u,v)|k}1$

那么思考后面这个 sigma 的自身含义，是不是看着挺好求的？

我们考虑抠出所有 $k | a_i$ 的点 $i$，再抠出它们之间的连通块分别计算。

那么我们全局分析复杂度，其实这样已经可以做到 $\mathcal{O}(n\text{d}(n))$了。

然后提一句，这个抠联通块的过程看似要枚举很多无用边，实际上总的来说是每个点的所有出边都被访问 $O(d(n))$ 次，所以总的复杂度仍然正确。

具体的连通块内计数，是非常经典的问题，考虑每个点对答案的贡献即可。

```cpp

bool visp[200005];
ll cnt, prim[200005],phi[200005];
void init(){
    phi[1]=1;
    for(ll i=2;i<=2e5;i++){
        if(!visp[i]) prim[++cnt]=i, phi[i]=i-1;
        for(ll j=1;j<=cnt && i*prim[j]<=2e5;j++){
            visp[i*prim[j]]=1;
            if(i%prim[j]==0) {phi[i*prim[j]] = phi[i] * prim[j]; break;}
            phi[i*prim[j]] = phi[i] * phi[prim[j]];
        }
    }
}
ll n,a[100005],has[100005],vis[100005];
vector<ll>E[100005];
vector<ll>lst[100005]; // 枚举因数的列表
ll cnts=0; vector<ll>temp;
void dfs1(ll x){
    vis[x]=1; temp.push_back(x);
    for(auto y: E[x]){
        if(!has[y]) continue;
        if(vis[y]) continue;
        dfs1(y);  
    }
}
ll dfs(ll x){
    vis[x]=1;
    ll sz=1;
    ll n = temp.size();
    ll all = (n-1)*(n-1), ans= 0;
    for(auto y: E[x]){
        if(!has[y]) continue;
        if(vis[y]) continue;
        ll tsz = dfs(y);
        sz += tsz;
        all -= tsz * tsz;
    }
    all -= (n-sz) * (n-sz);
    all /= 2; all %= mod;
    cnts = (cnts + all + (n-1)) % mod;
    return sz;
}
void solve(){
    n=read();
    for(ll i=1;i<=n;i++){
        a[i]=read();
        for(ll j=1;j*j<=a[i];j++){
            if(a[i]%j) continue;
            lst[j].push_back(i);
            if(j*j!=a[i]) lst[a[i]/j].push_back(i);
        }
    }
    for(ll i=1;i<n;i++){
        ll u=read(), v=read();
        E[u].push_back(v);
        E[v].push_back(u);
    }
    ll ans=0;
    for(ll i=1;i<=1e5;i++){
        ll anst = 0;
        for(auto x: lst[i]){
            has[x]=1; vis[x]=0;
        }
        for(auto x: lst[i]){
            if(!vis[x]){
                temp.clear();
                dfs1(x);
                for(auto y: temp) vis[y]=0;
                cnts=0;
                dfs(x);
                anst = (anst + cnts) % mod;
            }
        }
        ans = (ans + anst * phi[i]) % mod;
        for(auto x: lst[i]){
            has[x]=0; vis[x]=0;
        }
    }
    printf("%lld\n", ans);
}
int main(){
    #ifdef OIcontest
        freopen(".in","r",stdin);
        freopen(".out","w",stdout);
    #endif
    #ifdef FastIO
        ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    #endif
    init();
    ll T=1;
    while(T--) solve();
    return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：1)

# 题目翻译

给定 $n$ 个点的树，每个点有点权 $a_i$。定义 $D(u,v)$ 表示 $u\to v$ 的简单路径的长度（即经过的点的个数）。定义 $G(u,v)$ 表示 $u\to v$ 的简单路径经过的所有点的 $\gcd$。定义 $F(u,v)$ 表示 $D(u,v)G(u,v)$。

求 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n F(i,j)$。

$1\leq n\leq 10^5$，$1\leq a_i\leq 10^5$。

# 题目思路

对于每个 $\gcd$ 直接找他的路径不是很好做。我们不妨枚举 $\gcd$ 找 $G(u,v)$ 为 $\gcd$ 倍数的路径，然后容斥一下。

设 $f_i$ 表示 $G(u,v)$ 恰好等于 $i$ 的 $\sum\limits_{u=1}^n\sum\limits_{v=u+1}^n D(u,v)$。

设 $g_i$ 表示 $i\mid G(u,v)$ 的 $\sum\limits_{u=1}^n\sum\limits_{v=u+1}^n D(u,v)$。

则有 $f_i\gets g_i-\sum\limits_{i\mid j\land j\gt i} f_j$。

设 $N=10^5$ 即本题中的 $\max a_i$，那么显然有 $\forall 2i\gt N,f_i=g_i$。

我们现在只要求出这个 $g_i$ 就可以倒着推出所有 $f_i$。$\sum i\times f_i$ 即为答案。

我们把所有的 $i\mid a_j$ 的点 $j$ 拎出来。他们形成一片森林。我们对其中的每棵树 $T$ 求出 $\sum\limits_{u\in T}\sum\limits_{v\in T \land u\neq v} D(u,v)$ 即可。

这是个经典问题。考虑每条边的贡献。预处理出所有点的子树大小然后再搜一遍就行。由于本题的距离定义不太一样最后加上一个 $\binom{|T|}{2}$。

这样子做完之后照着上面的容斥重推一遍就好了。

时间复杂度计算考虑一个点会被哪些 $\gcd$ 用到。显然是因子个数。找 $i\mid a_j$ 的点可以调和级数地预处理因子。

# 部分代码

[AT submission 61987219](https://atcoder.jp/contests/abc248/submissions/61987219)

```cpp
using Z = mod_int<998244353>;
typedef long long ll;
const int N = 1e5;
int n;
Z f[100020];
int a[100020];
int sz[100020];
bool ok[100020];
vector<int> g[100020];
vector<int> d[100020];
vector<int> vec[100020];
Z tot;
Z ans;
void dfs(int u, int fa)
{
    sz[u] = 1;
    for (int v : g[u])
    {
        if (!ok[v] || v == fa)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
void calc(int u, int fa, int rt)
{
    ok[u] = 0;
    for (int v : g[u])
    {
        if (!ok[v] || v == fa)
            continue;
        calc(v, u, rt);
        tot += 1LL * sz[v] * (sz[rt] - sz[v]);
    }
}
int main()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = i; j <= N; j += i)
            d[j].emplace_back(i);
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        for (int j : d[a[i]])
            vec[j].push_back(i);
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= N; i++)
    {
        tot = 0;
        for (int j : vec[i])
            ok[j] = 1;
        for (int j : vec[i])
        {
            if (!ok[j])
                continue;
            dfs(j, 0);
            calc(j, 0, j);
            tot += 1LL * sz[j] * (sz[j] - 1) / 2;
        }
        f[i] = tot;
    }
    for (int i = N; i >= 1; i--)
    {
        for (int j = i + i; j <= N; j += i)
            f[i] -= f[j];
    }
    for (int i = 1; i <= N; i++)
        ans += i * f[i];
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：yukimianyan (赞：1)

- posted on 2022-10-13 First version
- updated on 2022-11-22 修正了方法二的代码实现。

## problem
$n$ 个点的树有点权 $a$，求

$$\sum_{\text{路径 P 在树上}}{\gcd(a_{P_1},a_{P_2},\cdots,a_{P_{|P|}})\cdot |P|}.$$

（原题要求路径 $P$ 的长度至少为 $2$，请注意）

## solution 1
考虑枚举 $\operatorname{lca}=k$ 怎么做。

在 $k$ 的子树中，爆搜所有路径，存到一个 `std::map` 里。

考虑对于子树 $k$ 有多少种不同的 $\gcd$？由于这些路径中含有 $a_k$，意味着 $\gcd|a_k$，那么一共应该有 $O(\sigma(a_k))$ 种 $\gcd$；$10^5$ 中最大的 $\sigma$ 大概是 $90$ 左右（$2\times 3\times 5\times 7\times 11\times 13\times 17=510510$）。

于是有这么一种想法：维护一个子树的路径的前缀和，每次对于一个子树算出的 `std::map` 中的值和这个前缀和卷起来（$O(90^2)$），然后扔进去前缀和（$O(90)$）。

点分治会凭空多出一只 $\log$，这道题直接一遍 dfs，每次像上面这样暴力算一下即可。复杂度 $O(90^2n\log n)$，包含 $\gcd$ 的 $\log$ 和 `std::map` 的 $\log\log$。

## code
没有讲完。这样写的细节很多。

考虑怎么把两个 `std::map` 卷起来？你需要记录，当 $\gcd=d$ 时，有多少条路径，它们的路径总长度是多少。然后使用乘法原理。

在继承到父亲时，还需要注意路径总长度应该加上路径条数。

```cpp
#include <map>
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long LL;
const int P=998244353;
typedef pair<int,int> node;
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
template<int N,int M,class T=int> struct graph{
    int head[N+10],nxt[M*2+10],cnt;
    struct edge{
        int u,v;T w;
        edge(int u=0,int v=0,T w=0):u(u),v(v),w(w){}
    } e[M*2+10];
    graph(){memset(head,cnt=0,sizeof head);}
    edge operator[](int i){return e[i];}
    void add(int u,int v,T w=0){e[++cnt]=edge(u,v,w),nxt[cnt]=head[u],head[u]=cnt;}
    void link(int u,int v,T w=0){add(u,v,w),add(v,u,w);}
};
int n,a[100010],ans;
graph<100010,100010> g;
node o(node a,node b){return node((a.first+b.first)%P,(a.second+b.second)%P);}
LL calc(map<int,node> &a,map<int,node> &b){
	LL res=0; 
//	printf("a:");for(pair<int,node> x: a) printf("(%d,{%d,%d}),",x.first,x.second.first,x.second.second);puts("");
//	printf("b:");for(pair<int,node> x: b) printf("(%d,{%d,%d}),",x.first,x.second.first,x.second.second);puts("");
	for(pair<int,node> x: a){
		for(pair<int,node> y: b){
			res=(res+1ll*gcd(x.first,y.first)*(1ll*x.second.second*y.second.first%P+1ll*x.second.first*y.second.second%P+1ll*x.second.second*y.second.second%P)%P)%P;
		}
	}
	return res;
}
void merge(map<int,node> &a,map<int,node> &b){for(pair<int,node> y: b) a[y.first]=o(a[y.first],y.second);}
map<int,node> add(map<int,node> a,int w){
	map<int,node> r;
	for(pair<int,node> x: a){
		r[gcd(x.first,w)]=o(r[gcd(x.first,w)],node(x.second.first+x.second.second,x.second.second));
	}
	return r;
}
map<int,node> dfs(int u,int fa=0){
	map<int,node> tot={{a[u],{0,1}}};
	for(int i=g.head[u];i;i=g.nxt[i]){
		int v=g[i].v; if(v==fa) continue;
		map<int,node> res=add(dfs(v,u),a[u]);
//		printf(">u=%d,v=%d\n",u,v);
		ans=(ans+calc(tot,res))%P;
//		printf("%lld\n",ans);
		merge(tot,res);
	}
	return tot;
}
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g.link(u,v);
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```
## solution 2
枚举 $\gcd=d$。

考虑求出 $g_i$ 表示路径 $\gcd$ 为 $i$ **的倍数**的路径长度和。

考虑经过一条边，若要保证 $\gcd$ 为 $i$ 的倍数，必有 $i|\gcd(a_u,a_v)$。

对每个因数建一棵树，在因数 $d$ 的树中放入 $d|\gcd(a_u,a_v)$ 的所有边，对每个因数的树单独 dfs，求出其路径长度和。

现在有 $g_i$，考虑容斥：

$$f_i=g_i-\sum_{i|j,i\neq j}f_j.$$

倒序算出 $f_i$ 即为 $\gcd$ 恰好为 $i$ 的路径长度和。

复杂度：时间 $O(nd+n\log n)$，空间 $O(nd)$，其中 $d=\max_{i\leq 10^5}\sigma(i)=128$。枚举因子部分可以预处理，或者根号也行。
## code
```cpp
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <utility>
#include <cassert>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr,##__VA_ARGS__)
#else
#define debug(...) void(0)
#endif
typedef long long LL;
const int P=998244353;
template<int N> struct siever{
	vector<int> d[N+10];
	siever(){
		for(int i=1;i<=N;i++){
			for(int j=i;j<=N;j+=i) d[j].push_back(i);
		}
	}
};
template<int N,int M,class T=int> struct graph{
    int head[N+10],nxt[M*2+10],cnt;
    int vis[N+10],tag; 
    struct edge{
        int u,v;T w;
        edge(int u=0,int v=0,T w=0):u(u),v(v),w(w){}
    } e[M*2+10];
    graph(){memset(head,cnt=0,sizeof head),memset(vis,tag=0,sizeof vis);}
    edge&operator[](int i){return e[i];}
    void add(int u,int v,T w=0){
		if(vis[u]!=tag) vis[u]=tag,head[u]=0;
		e[++cnt]=edge(u,v,w),nxt[cnt]=head[u],head[u]=cnt;
	}
    void link(int u,int v,T w=0){add(u,v,w),add(v,u,w);}
};
int gcd(int x,int y){return !y?x:gcd(y,x%y);}
int n,a[100010];
LL ans,cnt,f[100010];
int vis[100010];
graph<100010,100010> t,g;
vector<int> e[100010];
siever<100010> s; 
LL calc(pair<LL,LL> a,pair<LL,LL> b){
	return ((a.first*b.second+b.first*a.second-a.second*b.second%P+P))%P;
}
pair<LL,LL> dfs(int u,int fa,LL &ans){
	vis[u]=g.tag;
	pair<LL,LL> tot={1,1};
	for(int i=g.head[u];i;i=g.nxt[i]){
		int v=g[i].v; if(v==fa) continue;
		pair<LL,LL> res=dfs(v,u,ans);
		res={(res.first+res.second)%P,res.second};
		ans=(ans+calc(tot,res))%P;
		tot={(tot.first+res.first)%P,(tot.second+res.second)%P};
	}
	return tot;
}
void dp(int d){
	g.tag++,g.cnt=0;
	for(int i:e[d]) g.link(t[i].u,t[i].v),debug("link (%d,%d)\n",t[i].u,t[i].v);
	for(int i:e[d]) if(vis[t[i].u]!=g.tag) dfs(t[i].u,0,f[d]);
	for(int i:e[d]) if(vis[t[i].v]!=g.tag) dfs(t[i].v,0,f[d]);
	if(f[d]) debug("f[%d]=%lld\n",d,f[d]);
}
int main(){
//	#ifdef LOCAL
//	 	freopen("input.in","r",stdin);
//	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		t.add(u,v);
		for(int d:s.d[gcd(a[u],a[v])]) e[d].push_back(i),debug("(%d,%d) belongs to tree %d\n",u,v,d); 
	}
	for(int i=1;i<=1e5;i++) dp(i);
	for(int i=1e5;i>=1;i--){
		for(int j=i+i;j<=1e5;j+=i) f[i]=(f[i]-f[j]+P)%P;
		ans=(ans+f[i]*i)%P;
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：SegTree (赞：0)

考虑枚举 $\gcd a_i$ 的值。设这个值为 $x$，则只需要计算把 $x|a_i$ 的每个 $i$ 保留下来求路径长度和就行。这个东西可以对每棵树都做一遍换根 dp 求出。

但是你发现这样只能保证它们 $\gcd$ 是 $x$ 的倍数。这个问题的处理方法也是简单的。记 $res_i$ 表示 $\gcd$ 为 $i$ 时的路径长度和，那么只需要将答案减去 $\sum res_{ij}$ 即可。最后按照题目统计贡献 $\sum i\times res_i$ 即可。

时间复杂度 $\mathcal{O}(n(\max d(a_i)+\sqrt{\max a_i}))$，其中 $d(a_i)$ 为 $a_i$ 因子个数，可通过本题。

提交记录：<https://atcoder.jp/contests/abc248/submissions/45328505>。

---

## 作者：MuelsyseU (赞：0)

考虑如何求出所有满足 $\gcd(i,j)=t$ 的路径 $(i,j)$ 贡献。显然可以预处理出包含因子 $t$ 的节点，在形成的若干连通块中执行 DP 计算总长度。

但是这样做并不能保证路径 $t=\gcd(i,j)$，仅能保证 $t|\gcd(i,j)$。由于我们的目的是对所有不同的 $t$ 的贡献求和，因此可以考虑

$$t=\sum_{d|t}\phi(d)$$

这时如果枚举 $d$，统计路径 $(i,j)$ 的贡献时，所需满足的条件就仅为 $d|\gcd(i,j)$，符合上述做法，即统计满足这一条件的所有路径的总长度再乘上 $\phi(d)$之和。

利用调和级数思想预处理，可以达到 $O(nd(n))$ 时空复杂度，其中 $d(n)$ 表示 $[1,n]$ 内因数最多的数的因数个数，满足 $d(10^5)=128$。

```cpp
#include <bits/stdc++.h>
#define maxn 200005
using namespace std;

const int mod = 998244353;
int n, m, d, x, y, j, a[maxn], b[maxn], c[maxn];
vector<int> e[maxn], v[maxn];
long long ans, s, f[maxn], g[maxn], h[maxn];
// f: 经过i的总长度
// g: （前若干个子树中）一端为i的总长度
// h: （前若干个子树中）一端为i的总数
void dfs(int u) {
    c[u] = 0, f[u] = 0, h[u] = g[u] = 1;
    // 注意此题路径长度为结点数而非边数
    for (int v : e[u]) {
        if (!c[v]) continue;
        dfs(v);
        f[u] = (f[u] + g[u] * h[v] % mod + g[v] * h[u] % mod) % mod;
        g[u] = (g[u] + g[v] + h[v]) % mod;
        h[u] = h[u] + h[v];
    }
    (s += f[u]) %= mod;
}
int phi[maxn];
inline void init() {
    // 埃氏筛
    for (int i = 1; i <= m; i++) phi[i] = i;
    for (int i = 2; i <= m; i++)
        if (phi[i] == i)
            for (int j = i; j <= m; j += i) phi[j] = phi[j] / i * (i - 1);
}
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i), m = max(m, a[i]), v[a[i]].push_back(i);
    }
    init();
    // 预处理
    for (int i = 1; i <= m; ++i) {
        for (int j = 2; i * j <= m; ++j) {
            for (int k : v[i * j]) v[i].push_back(k);
        }
    }
    for (int i = 1; i <= n; ++i) scanf("%d%d", &x, &y), e[x].push_back(y), e[y].push_back(x);
    for (d = 1; d <= m; ++d) {
        s = 0;
        for (int x : v[d]) c[x] = 1;
        // 对连通块内 DP 求总长度
        for (int x : v[d])
            if (!b[x]) dfs(x);
        (ans += s * phi[d]) %= mod;
    }
    printf("%lld", ans);
    return 0;
}
```

---

