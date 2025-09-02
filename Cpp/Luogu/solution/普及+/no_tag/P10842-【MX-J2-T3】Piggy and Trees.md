# 【MX-J2-T3】Piggy and Trees

## 题目背景

原题链接：<https://oier.team/problems/J2D>。

## 题目描述

给你一棵 $n$ 个结点的树。

定义 $f(u, v, i)$ 为，在所有满足 $^\dagger\text{dis}(u, x) + \text{dis}(v, x) = \text{dis}(u, v)$ 的点 $x$ 中，$\text{dis}(x, i)$ 的最小值。

求 $\sum\limits_{u = 1}^n \sum\limits_{v = u + 1}^n \sum\limits_{i = 1}^n f(u, v, i)$ 对 $10^9 + 7$ 取模的值。

$^\dagger\text{dis}(u, v)$ 为树上 $u, v$ 两点的路径长度。特别地，$\text{dis}(u, u) = 0$。

## 说明/提示

#### 【样例解释】

在样例 $1$ 中，所有非 $0$ 的 $f(u, v, i)$ 的值为：

- $f(1, 2, 3) = 1$；
- $f(1, 2, 4) = 1$；
- $f(1, 3, 2) = 1$；
- $f(1, 3, 4) = 1$；
- $f(1, 4, 2) = 1$；
- $f(1, 4, 3) = 1$；
- $f(2, 3, 4) = 1$；
- $f(2, 4, 3) = 1$；
- $f(3, 4, 2) = 1$。

#### 【数据范围】

**本题采用捆绑测试且开启子任务依赖。**

| 子任务编号 | 分值 | $n \le$ | 特殊性质 | 子任务依赖 | 
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $8$ | $50$ | 无 | 无 |
| $2$ | $15$ | $400$ | 无 | $1$ |
| $3$ | $24$ | $3000$ | 无 | $1, 2$ |
| $4$ | $17$ | $2 \cdot 10^5$ | $u_i = i, v_i = i + 1$ | 无 |
| $5$ | $36$ | $2 \cdot 10^5$ | 无 | $1, 2, 3, 4$ |

对于所有数据，满足 $2 \le n \le 2 \cdot 10^5$，输入的图是一棵树。

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
4 5
5 6
```

### 输出

```
70
```

## 样例 #3

### 输入

```
10
1 2
1 3
1 4
2 5
3 6
2 7
4 8
8 9
9 10
```

### 输出

```
536
```

# 题解

## 作者：EuphoricStar (赞：26)

若每条边 $(a, b)$ 维护一个计数器 $c_{(a, b)}$，每次枚举 $u, v, i$ 时，把 $x \to i$ 路径上的边的 $c$ 值全部加 $1$，那么答案就是 $\sum\limits_{(a, b) \in E} c_{(a, b)}$。

考虑直接计算 $c_{(a, b)}$。设断开 $(a, b)$ 这条边后形成的两棵子树大小分别为 $x, y$。那么当 $u \to v$ 的路径不跨过 $(a, b)$ 这条边且 $i$ 点在另外一棵子树内，$c_{(a, b)}$ 会加 $1$。所以实际上只用计算在一棵子树内选两个点，在另一棵子树选一个点的方案数。所以 $c_{(a, b)} = y \cdot \frac{x(x - 1)}{2} + x \cdot \frac{y(y - 1)}{2}$。枚举每条边直接求和即可。

时间复杂度 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 200100;
const ll mod = 1000000007;

ll n, sz[maxn], ans;
vector<int> G[maxn];

void dfs(int u, int fa) {
	sz[u] = 1;
	for (int v : G[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		sz[u] += sz[v];
		ans = (ans + sz[v] * (sz[v] - 1) / 2 * (n - sz[v]) + (n - sz[v]) * (n - sz[v] - 1) / 2 * sz[v]) % mod;
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1, -1);
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Wei_Han (赞：15)

还是写一下赛时的麻烦做法，纪念一下。

先分析一下 $f$ 函数的意义，其实就是求 $i$ 到 $u$，$v$ 路径的最近距离，而且如果要令这个式子不为 $0$，路径是不能经过 $i$ 的，发现我们要求所有点到所有路径的距离，不如依照每一个点讨论。

我们钦定一个 $x$ 为点到某些路径最近的交点，如果我们令 $x$ 为根的话，每次选择一个点 $i$，也就是 $dis(x,i)$，那么这个 $dis(x,i)$ 被加的次数就是不经过 $i$ 且以 $x$ 为 $i$ 的最近点的路径条数，能发现，这个路径也一定不会经过 $x$ 那个含有 $i$ 的子树，我们此时选择一个子树 $u$，，那么从子树 $u$ 出发的路径条数就是 $siz_u\times (n - siz_i - siz_u)$，此处令 $siz_i$ 表示 $i$ 那一整棵子树的大小，因为要去除重复路径，所以所有路径条数就是 $\frac{\sum_{v \in son_u} siz_v\times (n - siz_i -siz_v)}{2}$，点 $i$ 的贡献就是再乘上一个距离。此时可以发现，对于 $i$ 这个子树，他们对应 $x$ 点的路径条数是一致的，那么我们只需要算出 $i$ 子树内所有节点到 $x$ 的距离，然后乘上路径条数，就是 $i$ 子树的对 $x$ 贡献，以此类推，每个点都可以这样计算。

可是这样做是 $O(n^2)$ 的，因为每次计算路径是需要遍历所有子节点，假设没有选择子树，要求路径条数，我们不如换一个角度，我们找所有满足条件的路径，我们也可以找所有非法路径，然后取个补集就是答案，那么我们知道，路径总数一共有 $n^2$ 条，非法的就是子树内互相连，那么就是 $\sum_{v \in son_x} siz_v^2$ 条，还包括一条 $x$ 自己，还要去除重复，所以对于 $x$，路径总数就是 $\frac{n^2-\sum_{v\in x}siz_v^2-1}{2}$。现在还要考虑选择一个子树，那么删去这个子树内的合法路径即可，也就是减掉 $siz_i \times (n-siz_i)$。这样就可以 $O(n)$ 的计算出结果了，对于 $x$ 的贡献是 $dis_i \times(\frac{n^2-\sum_{v\in x}siz_v^2-1}{2}-siz_i \times (n-siz_i))$，其中 $dis_x$ 是 $i$ 子树内所有点到 $x$ 的距离和。

这是我们固定 $x$ 为根的情况，考虑当 $x$ 不为根，那么他的父亲及其往上也是需要当做一个子树计算的，子树的节点数好计算，子树内距离不好算，我们需要用所有点到 $x$ 的距离和，减去 $x$ 子节点到 $x$ 的距离和，所以这里还需要提前换根求一下所有点到 $x$ 的距离和，可以参照 [P3478](https://www.luogu.com.cn/problem/P3478)，就是减加一个子树个数，然后就结束了，记得不需要对路径条数取模，不然结果是不对的。

时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
//#pragma GCC optimize(2)
using namespace std;
typedef __int128 ll;
const int N=2e6+5,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(long long x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll head[N],tot,sum[N],n,siz[N],dfn[N],mod=1e9+7,ans,f[N];
struct Graph{ll ver,nxt;}g[N<<1];
inline void add(ll x,ll y){g[++tot].ver=y,g[tot].nxt=head[x];head[x]=tot;}
inline void dfs(ll x,ll fa){
	siz[x]=1;
	for(int i=head[x];i;i=g[i].nxt)
	{
		ll y=g[i].ver;if(y==fa) continue;
		dfs(y,x);siz[x]+=siz[y];dfn[x]=dfn[x]-siz[y]*siz[y];
		sum[x]+=sum[y]+siz[y];
	}
	dfn[x]=dfn[x]-(n-siz[x])*(n-siz[x])+n*n-1;
	dfn[x]/=2;
}
inline void GetDp(ll x,ll fa){
	for(int i=head[x];i;i=g[i].nxt){
		ll y=g[i].ver;if(y==fa) continue;
		f[y]=f[x]+(n-siz[y])-siz[y]+mod;GetDp(y,x);
	}
}
inline void dfs1(ll x,ll fa){
	vector<ll> v,dis;v.push_back(n-siz[x]);dis.push_back(f[x]-sum[x]);
	for(int i=head[x];i;i=g[i].nxt){
		ll y=g[i].ver;if(y==fa) continue;
		v.push_back(siz[y]);dis.push_back(sum[y]+siz[y]);
	}
	for(int i=0;i<v.size();i++){
		ll cnt=dfn[x];
		cnt-=v[i]*(n-v[i]);
		ans=(ans+cnt*dis[i]%mod)%mod;
	}
	for(int i=head[x];i;i=g[i].nxt){
		ll y=g[i].ver;if(y==fa) continue;
		dfs1(y,x);
	}
}
signed main(){
	read(n);fo(1,i,n-1){ll u,v;read(u),read(v);add(u,v),add(v,u);}
	dfs(1,0);f[1]=sum[1];GetDp(1,0);dfs1(1,0);wr((ans+mod*mod)%mod);pr;
	return 0;
}	
``````

---

## 作者：_ZML_ (赞：10)

# 题意
将题目的求和顺序变一下，也就是求：$\sum\limits_{i = 1}^n \left[ \sum\limits_{u = 1}^n \sum\limits_{v = u + 1}^n f(u, v, i) \right ]$。

通俗来讲，就是枚举树上所有点 $i$，找到树上所有路径离点 $i$ 的距离的和的和。
# 思路
考虑计算一条边会被计算多少次。

在一条路径经过边 $(x,y)$ 的时候，它会被计算。所以 $u,v$ 和 $i$ 一定会在 $(x,y)$ 的两边，可以对照图看一下。

![QwQ](https://cdn.luogu.com.cn/upload/image_hosting/nsjywyxf.png)

假设 $sum_x$ 是朝“下”子树的大小，$sum_y$ 是朝“上”子树的大小。则边 $(x,y)$ 对答案的贡献就是 $C_{sum_x}^2\times sum_y+C_{sum_y}^2\times sum_x$。

这道题也就做完了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;
vector<int> edge[200010];
int sz[200010];
int n, ans = 0;
void dfs(int u, int fa)
{
    sz[u] = 1;
    for (auto v : edge[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    if (u == 1)
        return;
    int sum = n - sz[u];// 朝“上”子树大小
    ans += sum * (sum - 1) / 2 * sz[u] + sz[u] * (sz[u] - 1) / 2 * sum;
    ans %= mod;
}
signed main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}
```

---

## 作者：VitrelosTia (赞：4)

首先手玩一下式子可以发现 $f(u, v, i)$ 在图上其实意味着 $i$ 到 $u \to v$ 这条路径上最近的距离。思考如何对 $i$ 算贡献，发现如果按照换根等一些思路来做很难做到 $O(n^2)$ 以下，那就可以考虑对边算贡献。

一条边什么时候会有贡献？是能被 $u \to i$ 和 $v \to i$ 同时经过的时候。具体可以看这个情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/mw4d9kfj.png)

对于 $(5, 3)$ 这条边，可以在 $5$ 的子树中选两个点作为 $u$ 和 $v$，与此同时在 $3$ 的子树中选一个点作为 $i$，当然也可以换一下。显然只有这样是能给边作贡献的。实现就很简单了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;

const int N = 2e5 + 5, mod = 1e9 + 7;
int n;

struct Edge { int to, nxt; } e[N << 1];
int cur, head[N];
void Add(int u, int v) { e[++cur] = {v, head[u]}; head[u] = cur; }
#define GoEdge(i, u, v) for (int i = head[u], v; v = e[i].to, i; i = e[i].nxt)

int C(int n) { return n * (n - 1) / 2 % mod; } // C(n, 2)
int ans, siz[N];
void dfs(int u, int fa) {
    siz[u] = 1;
    GoEdge(i, u, v) if (v != fa) {
        dfs(v, u); siz[u] += siz[v];
        int x = siz[v], y = n - siz[v];
        ans = (ans + C(x) * y % mod + C(y) * x % mod) % mod;
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        Add(u, v); Add(v, u);
    }
    dfs(1, 0); cout << ans;
    return 0;
}
```

---

## 作者：arrowpoint (赞：4)

这里提供一种与官方题解不同的思路。

### 简要题意

计算一棵树上所有路径到所有点的距离之和。

### 题目分析

这是一个树上统计问题，而树上统计问题的一个经典思想就是对于每个点，先计算子树中的答案，再根据题目性质将答案合并。

我们设 $ans_i$ 表示点 $i$ 的子树内所有路径到所有点距离之和。首先 $i$ 的所有子节点的子树已经被计算，直接加上它们的答案即可。然后分为两种情况，即 $i$ 为端点和 $i$ 不为端点。

对于第一种情况，我们先考虑任意一条路径。设路径深度较大的端点为 $a$，深度较小的端点为 $b$。显然，这条路径上的点到这条路径距离为 $0$，$a$ 子树中点到这条路径距离为到 $a$ 的距离，$b$ 子树外的点到这条路径距离为到 $b$ 的距离。对于其它点，若它属于路径中某个点的子树，则它到这条路径的距离就为到这个点的距离。

我们枚举 $i$ 的每个子节点 $j$，考虑另一路径端点 $k$ 在 $j$ 子树内的情况，显然一共新增 $size_j$ 条路径。（$size_j$ 为 $j$ 子树的大小）对于每条路径，由上文得 $j$ 子树外的所有点的贡献均为到 $i$ 的距离，即 $alldis_i-dis_j-size_j$。（$alldis_i$ 为所有点到 $i$ 的距离之和，$dis_j$ 为 $j$ 子树内点到 $j$ 距离之和，再减去 $size_j$ 是因为 $j$ 子树内点到 $i$ 的距离都要大 $1$，加起来就是它）而 $j$ 子树内点的贡献又分为 $k$ 子树中的点的贡献 $dis_k$ 和路径上其它点的贡献。显然路径上每个点的贡献为它的子树中排除 $k$ 所在子树的点到它的距离和。

现在考虑 $O(1)$ 得到以上信息：显然 $j$ 子树内每个点只会被计算 $1$ 次，即只会有 $size_j$ 条新路径。于是 $size_j \times (alldis_i-dis_j-size_j)$ 即为第一种贡献，预处理 $predis_i$（即每个点子树内 $dis$ 之和）表示第二种贡献。对于第三种，发现对于每个点 $l$ 只有以 $l$ 子树内（不包括 $l$）的点为路径端点，且所求点为 $k$ 其他子树中的点时才会产生贡献，且这个贡献值与 $i$ 无关，于是预处理 $add_l$ 为这个值，$preadd_l$ 为 $l$ 子树的 $add_l$ 的和。$add_l$ 的计算方式为：枚举 $l$ 的每个子节点 $v$，求出 $\sum size_v \times (dis_l-dis_v-size_v)$。原因可以参考上面的解释。

对于第二种情况，我们发现路径两端点必为 $i$ 的两个不同子节点子树中的点。每个子节点子树中的点都能与其他子节点子树中的点自由组合，一共有 $d=\sum size_v \times (size_i-size_v-1) / 2$ 种情况。每种情况的贡献又分为三种：第一种为 $i$ 子树外的点的贡献，第二种为路径两端点子树中点的贡献，第三种为 $i$ 子树内其它点的贡献。

对于这种情况的第一种贡献，每条路径是等价的，为 $d \times (alldis_i-dis_i)$ 种。对于第二种贡献，发现实际上就是把第一种情况的第二和第三中贡献再与 $i$ 其它子节点中子树 $(size_i-size_v-1)$ 个点自由组合了，将这两种贡献乘上 $(size_i-size_v-1)$ 的系数即可。对于第三种贡献，考虑路径两端点在 $i$ 的某两个子节点 $n$，$m$ 的子树，设 $i$ 的子节点数量为 $son_i$，则贡献为（注：为了方便表示，以下 $n$，$m$ 表示 $i$ 的第 $n$，$m$ 个子节点）：
$$\begin{aligned} \sum_{n=1}^{son_i} \sum_{m=n+1}^{son_i} size_n \times size_m \times (dis_i-dis_n-size_n-dis_m-size_m) \end{aligned}$$

上式最坏会卡到 $O(n^2)$。因此设 $powsize_i=\sum size_j \times (dis_j+size_j)$，$rest=dis_i-dis_j-size_j$（$j$ 为 $i$ 的子节点），则上式转化为：

$$\begin{aligned} (\sum_{n=1}^{son_i} size_n \times (rest\times(size_i-size_n-1)-powsize_i+size_n\times(dis_n+size_n)))/2\end{aligned}$$

将所有贡献全部加起来，即为答案。时间复杂度 $O(n)$。关于贡献除以二后不为整数，$alldis$，$size$，$dis$ 怎么求等细节请看代码。


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

const int N = 3e5+10;
const int M = 1e9+7;
int n,m,a[N];
int size[N],dis[N],pred[N]; // pred：题解中的 predis 
int powsz[N]; // 题解中的 powsize 
int addd[N],preadd[N]; //题解中的 add,preadd 
int alld[N],ans[N]; //题解中的 alldis 
vector<int> vec[N];

inline void dfs(int x,int fa){
	size[x] = 1;
	dis[x] = 0;
	for(auto v:vec[x]){
		if(v==fa) continue;
		dfs(v,x); 
		dis[x] += dis[v]+size[v]; 
		pred[x] += pred[v];
		size[x] += size[v];
		powsz[x] += size[v]*(dis[v]+size[v]);
		dis[x] %= M;
		pred[x] %= M;
		powsz[x] %= M;
	} 
	pred[x] += dis[x];
	pred[x] %= M;
}
inline void dfs2(int x,int fa){
	for(auto v:vec[x]){
		if(v==fa) continue;
		alld[v] = alld[x]-size[v]+(n-size[v])+M; // 从父节点开始往下推，考虑当点从父节点移到子节点时，子节点子树所有点到它距离-1，其它点距离+1 
		alld[v] %= M;
		dfs2(v,x);
	}
}
inline void dfs3(int x,int fa){
	for(auto v:vec[x]){
		if(v==fa) continue;
		dfs3(v,x);
		addd[x] += (size[v])*(dis[x]-dis[v]-size[v]+M+M)%M;
		preadd[x] += preadd[v];
		addd[x] %= M;
		preadd[x] %= M;
	}
	preadd[x] += addd[x];
	preadd[x] %= M;
}
inline void dfs4(int x,int fa){
	int temp = 0;
	for(auto v:vec[x]){
		if(v==fa) continue;
		dfs4(v,x);
		ans[x] += ans[v];
		ans[x] += (alld[x]-dis[v]-size[v]+M+M)*size[v]%M;
		ans[x] += pred[v];
		ans[x] += preadd[v];
		ans[x] += (pred[v]*(size[x]-size[v]-1+M))%M;
		ans[x] += preadd[v]*(size[x]-size[v]-1+M)%M;
		temp += (alld[x]-dis[x]+M)*(size[v]*(size[x]-size[v]-1)%M)%M; // temp是真实贡献的2倍，防止出现除以二后不为整数等问题 
		int rest = (dis[x]-dis[v]-size[v]+M+M)%M;
		temp += size[v]*((rest*(size[x]-size[v]-1+M)%M-powsz[x]+size[v]*(dis[v]+size[v])%M+M)%M)%M;
		ans[x] %= M;
		temp %= M;
	}
	temp = (temp*500000004)%M; // 注意temp是真实贡献的2倍，因此乘以2在模1e9+7意义下的逆元 
	ans[x] += temp;
	ans[x] %= M;
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	int q1,q2;
	for(int i=1;i<=n-1;i++){
		cin>>q1>>q2;
		vec[q1].push_back(q2);
		vec[q2].push_back(q1);
	}
	dfs(1,0);
	alld[1] = dis[1];
	dfs2(1,0);
	dfs3(1,0);
	dfs4(1,0);
	cout<<ans[1]; 
	
	return 0;
}
```

---

## 作者：2020luke (赞：2)

# [P10842 【MX-J2-T3】Piggy and Trees](https://www.luogu.com.cn/problem/P10842) 题解

## solution

首先我们发现 $f(u,v,i)$ 函数很难讨论，把它转换成 $i$ 到路径 $u \to v$ 的距离。这样在我们以 $i$ 为根时就有 $f(u,v,i)=dis(i,lca(u,v))$。到了这里可以想到换根。我们定换根时初始的根为 $root$，统计当前点的子树中有多少个 $lca(u,v)$ 以及对应的贡献 $dis(i,lca(u,v))$ 的总和，我们设 $x$ 的子树中 $lca(u,v)$ 的个数为 $d_x$，子树中的贡献和为 $s_x$。这样对于每一个 $s_x$ 我们都从 $x$ 的子节点转移来，再因为转移时子节点的子树的根节点往上移了一层（也就是从 $x$ 的子节点转移到了 $x$），所以每一个 $lca(u,v)$ 的贡献都加上了 $1$，所以加上子树中 $lca(u,v)$ 的个数。这样就能够算出换根的初始值，也就是 $s_{root}$。

接下来考虑如何转移。发现从 $fa_x$ 转移至 $x$ 会将 $x$ 的子树内的贡献都减一，将 $x$ 子树外的贡献都加一，于是我们直接转移。但是我们发现会算重，因为有 $f(a,b,root)$ （其中 $a$ 为 $x$ 的子树内节点，$b$ 为 $x$ 的子树外节点）没有被减掉，这些部分我们单独计算即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, s[N], d[N], r[N], siz[N], f[N], ans = 0;
vector<int> g[N];
void dfs(int u, int fa) {
	siz[u] = 1;
	int res = 0, sum = 0;
	for(auto v : g[u]) {
		if(v != fa) {
			dfs(v, u);
			s[u] += s[v] + d[v];
			d[u] += d[v];
			siz[u] += siz[v];
			res += siz[v] * sum;
			sum += siz[v];
		}
	}
	d[u] += res + siz[u] - 1;
	r[u] = (n - siz[u]) * siz[u];
}
void dp(int u, int fa) {
	f[u] = f[fa] - d[u] - r[u] + d[1] - d[u];
	if(!fa) f[u] = s[u];
	ans += f[u]; ans %= mod;
	for(auto v : g[u]) {
		if(v != fa) dp(v, u);
	}
}
signed main() {
	cin >> n;
	for(int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v); g[v].push_back(u);
	}
	dfs(1, 0);
	dp(1, 0);
	cout << ans;
	return 0;
}
```

---

## 作者：Cure_Wing (赞：2)

[P10842 【MX-J2-T3】Piggy and Trees](https://www.luogu.com.cn/problem/P10842)

### 解析

> 求 $\sum\limits_{u = 1}^n \sum\limits_{v = u + 1}^n \sum\limits_{i = 1}^n f(u, v, i)$ 对 $10^9 + 7$ 取模的值。

亲爱的同学们，对于这种求和的代数式，如果不能暴力求，怎么办呢？

对于这种求和的代数式，一般有且两种转换方式：

1. 根据代数意义化简；
2. 根据几何意义转化。


首先挖掘 $\text{dis}(u, x) + \text{dis}(v, x) = \text{dis}(u, v)$ 的等价条件：$x$ 在简单路径 $(u,v)$ 上。结论很容易证明。

$\text{dis}(x, i)$ 的最小值也就变成了 $i$ 到树上简单路径 $(u,v)$ 的最小距离。

此时我们枚举 $(u,v)$，对于路径上的每一个点，容易暴力求出此时的最小距离和，时间复杂度 $O(n^4)$，期望得分 $8$ 分。

枚举一条边的时间复杂度已经达到了 $O(n^2)$，于是继续拆和式，枚举每一个在路径上的点。考虑根据这个点延申出去的路径，一定可以视作在其一棵或两棵子树内各选择个点连接而成的路径。对于未选择的儿子 $v$，如果其未被计入路径，那么它的儿子和它的最近距离就是当前节点 $u$，否则一定不是 $u$。于是枚举儿子 $v$，计算有多少条经过 $u$ 但不经过 $v$ 的路径，同时计算 $v$ 的子树内到 $u$ 的距离和，二者的乘积的总和即为答案。注意 $u$ 的父亲在此时也应当视作儿子处理。

时间复杂度 $O(n)$，期望得分 $100$，没有悬念的伐。

实现细节略微有点多，具体可以参考代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=200005,p=1e9+7;
int n,u,v,siz[N],sum[N],ans;
std::vector<int>edge[N];
inline void down(int u,int fa){
	siz[u]=1;//sum是子树距离和
	for(int i:edge[u]){
		if(i==fa) continue;
		down(i,u);sum[u]=(1ll*sum[u]+sum[i]+siz[i])%p;
		siz[u]+=siz[i];
	}
}
inline void dfs(int u,int fa,int dad){
  //dad计算父亲的距离和
	int tot=(n-1ll)*n/2%p,num=n-1;
	for(int i:edge[u])
		if(i!=fa){tot=(tot-siz[i]*(siz[i]-1ll)/2+p)%p;num-=siz[i];}
	tot=(tot-num*(num-1ll)/2+p)%p;
	for(int i:edge[u])
		if(i!=fa) ans=(ans+(tot-1ll*siz[i]*(n-siz[i])%p+p)*(sum[i]+siz[i])%p)%p;//距离总和=字数距离和*路径条数
	ans=(ans+(tot-1ll*num*(n-num)%p+p)*dad%p)%p;
	for(int i:edge[u]) if(i!=fa) dad=(1ll*dad+sum[i]+siz[i])%p;
	for(int i:edge[u]){
		if(i==fa) continue;
		dfs(i,u,((1ll*dad+n-siz[i]-siz[i]-sum[i])%p+p)%p);//下一个儿子的父亲和=现有父亲和+兄弟距离和
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;for(int i=1;i<n;++i){cin>>u>>v;edge[u].push_back(v);edge[v].push_back(u);}
	down(1,0);dfs(1,0,0);cout<<ans;
	return 0;
}//第二十四回 醉金刚轻财尚义侠 痴女儿遗帕惹相思
```

---

## 作者：kkxacj (赞：1)

#### 前言

赛时一眼出思路，但调了很久...

#### 思路

由于题目给出的限制，$x$ 必须是 $u$ 到 $v$ 的**简单路径**上的点，然后对于求 $dis\left(x,i\right)$，我们可以分类讨论一下：

1. $i$ 等于 $u,v$ 简单路径上的一个点，贡献显然为 $0$，不用管。

2. 定义 $lca$ 为 $u,v$ 的最近公共祖先，若 $i$ 为 $lca$ 的祖先，则 $x$ 取 $lca$ 最优。

3. $i$ 在 $u,v$ 简单路径上的一个点 $j$ 的子树内，显然 $x$ 取 $j$ 最优。

现在的问题就转化成求每种情况的贡献了，我们来看看需要求什么。

由于 $i$ 是我们枚举的，所以每个满足要求的 $i$ 都会被算进贡献，考虑记 $f_i$ 表示 $i$ 子树内的每一个点到 $i$ 的距离和，$g_i$ 表示所有不是 $i$ 子树内的每一个点到 $i$ 的距离和。

除此之外，我们还需要枚举 $j$ 表示 $u,v$ 的最近公共祖先，只要我们取得两个点都在 $j$ 的子树里，那么它们的最近公共祖先就是 $j$，我们记 $d_i$ 来表示。

**注意：对于第三种情况，$i$ 的儿子也会对当 $i$ 作为最近公共祖先时造成贡献，因为我每次至多选择两个在 $i$ 的子树里的点，除了这条路经上的点，其它的点也会造成贡献，不要忘记计算。**

然后这题就做完了。

**code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 4e5+10,mod = 1e9+7;
int n,head[N],cnt,x,y,siz[N],f[N],g[N],d[N],sum[N],ans;
struct w
{
	int to,nxt;
}a[N<<1];
inline void add(int x,int y) 
{
	a[++cnt].nxt = head[x];
	a[cnt].to = y;
	head[x] = cnt;
}
inline void dfs(int x,int fa)
{
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa)
		{
			dfs(a[i].to,x);
			d[x] = (d[x]+siz[x]*siz[a[i].to])%mod;
			siz[x] += siz[a[i].to],f[x] = (f[x]+f[a[i].to]+siz[a[i].to])%mod;
			//f为子树所有点到它的距离 
		}
	siz[x]++;
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa)
			ans = (ans+(f[x]-f[a[i].to]-siz[a[i].to])*(siz[a[i].to]*(n-siz[x])%mod)%mod)%mod;
	ans = (ans+f[x]*(n-siz[x])%mod)%mod;
}
inline void dfs1(int x,int fa)
{
	g[x] = g[fa]+(n-siz[x]);
	//g为非自己子树的其它点到它的距离
	ans = (ans+g[x]%mod*(d[x]+siz[x]-1))%mod;
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa)
		{
			ans = (ans+(d[x]-(siz[x]-1-siz[a[i].to])*siz[a[i].to]+siz[x]-1-siz[a[i].to])%mod*(f[a[i].to]+siz[a[i].to])%mod)%mod;
 			//计算子树贡献
			g[x] += f[a[i].to]+siz[a[i].to];
		}
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa)
		{
			g[x] = g[x]-f[a[i].to]-siz[a[i].to];
		 	dfs1(a[i].to,x);
			g[x] = g[x]+f[a[i].to]+siz[a[i].to];
		}
}
signed main()
{
	read(n);
	for(int i = 1;i < n;i++) read(x),read(y),add(x,y),add(y,x);
	dfs(1,0); dfs1(1,0);
	print(ans); flush(); 
	return 0;
}
/*
x为u,v路径上的点
1。若i为u,v的lca或lca的祖先，x为lca取到最小值
2.i为路径上的点贡献为0
3.否则为u到v路径上某个点的子树，直接取 

2不用管，3直接预处理，lca直接枚举，完了 
*/
```

---

## 作者：hjqhs (赞：1)

赛时的思路跟 @wei_han_ 先生一样，很可惜没能调出来。看到 @zltqwq 的题解后，顿时惊为天人，遂补一发以学习。  
考虑 $f(u, v, i)$ 的意义，即 $i$ 到 $u,v$ 路径的最短距离。设最短距离两边的点为 $(x, i)$，则每次计算 $f(u, v, i)$ 将 $(x, i)$ 路径上的边权自增 $1$, 问题就转化成了求树的边权和。  
考虑对于一条边，它的边权是怎么来的。将这条边断开后，形成左右两个子树，以下是边权和增加的情况：  
- $u, v$ 在左边子树，$i$ 在右边子树。  
- $u, v$ 在右边子树，$i$ 在左边子树。


问题就转化成了排列组合问题。  
然后就是处理的非常有趣的一点，在 dfs 过程中直接统计 $(u, v)$ 的边权和。  
深感 zlt 的强大。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;
const int N = 200005;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int n, siz[N], ans;
vector<int> g[N];
void dfs(int u, int fa) {
	siz[u] = 1;
	for(int i = 0; i < g[u].size(); ++ i) {
		int v = g[u][i];
		if(v != fa) {
			dfs(v, u);
			siz[u] += siz[v];
			int lsiz = siz[v], rsiz = n - siz[v];
			ans += lsiz * rsiz * (rsiz - 1) / 2;
			ans %= MOD;
			ans += rsiz * lsiz * (lsiz - 1) / 2;
			ans %= MOD;
		}
	}
}
void solve() {
	cin >> n;
	rep(i, 1, n - 1) {
		int u, v; cin >> u >> v;
		g[u].emplace_back(v), g[v].emplace_back(u);
	}
	dfs(1, 0); cout << ans;
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1;
	// cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：HHC883 (赞：1)

# 题目分析
一个重要的变形如下：
$$\sum_{u=1}^n \sum_{v=u+1}^n \sum_{i=1}^n f(u,v,i)=\frac {\sum_{u=1}^n \sum_{v=1}^n \sum_{i=1}^n f(u,v,i)-\sum_{u=1}^n \sum_{i=1}^n f(u,u,i)}{2}$$
其实就是改变 $v$ 的下标以简化计算。

现在考虑如何计算。首先，$\sum_{u=1}^n \sum_{i=1}^n f(u,u,i)$ 很好计算，$\sum_{i=1}^n f(u,u,i)$ 其实就是以 $u$ 为根时书上节点深度之和，可以利用动态规划来解决，具体参见 [P3478](https://www.luogu.com.cn/problem/P3478)。接下来考虑如何计算 $\sum_{u=1}^n \sum_{v=1}^n \sum_{i=1}^n f(u,v,i)$。这个式子看起来很复杂，实际上并不难。假设点 $u$ 固定，那么在计算 $\sum_{v=1}^n \sum_{i=1}^n f(u,v,i)$ 时，就以 $u$ 为树根，则 $u$ 到 $v$ 的路径变为根到 $v$ 的路径，再利用动态规划的思路（与求 $\sum_{u=1}^n \sum_{i=1}^n f(u,u,i)$ 的方法类似），即可求出答案。但是，若对每个 $u$ 都计算一次，复杂度为 $O(n^2)$，明显不行。这时，我们再次利用动态规划的思路，就会发现对于点 $u$ 的某个儿子 $u_1$，$\sum_{v=1}^n \sum_{i=1}^n f(u_1,v,i)$ 是可以由 $\sum_{v=1}^n \sum_{i=1}^n f(u,v,i)$ 推算而来的。接着，你列出状态转移方程，发现，一加一减，抵消了！于是，我们得到如下结论：对于任意的点 $u$，$\sum_{v=1}^n \sum_{i=1}^n f(u,v,i)$ 都相等，即
$$\sum_{u=1}^n \sum_{v=1}^n \sum_{i=1}^n f(u,v,i)=n \times \sum_{v=1}^n \sum_{i=1}^n f(1,v,i)$$
于是，我们以 $O(n)$ 的时间复杂度完成了计算。
# 参考代码
下面的代码中，数组 $dis_1$ 的第 $u$ 项记录 $\sum_{i=1}^n f(1,u,i)$，数组 $dis_2$ 的第 $u$ 项记录 $\sum_{i=1}^n f(u,u,i)$，常量 $inv$ 是 $2$ 在模 $10^9+7$ 意义下的逆元。

当然，逆元是提高组内容，如果不想用逆元，只需判断 $(\sum_{u=1}^n \sum_{v=1}^n \sum_{i=1}^n f(u,v,i)-\sum_{u=1}^n \sum_{i=1}^n f(u,u,i)) \bmod 10^9+7$ 的奇偶，若为偶，直接除以二；若为奇，加上模数再除以二即可，具体方法在代码注释里。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int mod=1e9+7,inv=5e8+4;
int n,es[(int)4e5+5],nxt[(int)4e5+5],head[(int)2e5+5],cnt,son[(int)2e5+5],sum,dis1[(int)2e5+5],dis2[(int)2e5+5],tot1,tot2;
void link(int u,int v){
	es[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs1(int now,int fath,int stp){
	sum=(sum+stp)%mod;
	son[now]=1;
	for(int i=head[now];i;i=nxt[i]){
		if(es[i]==fath) continue;
		dfs1(es[i],now,stp+1);
		son[now]+=son[es[i]];
	}
}
void dfs2(int now,int fath){
	for(int i=head[now];i;i=nxt[i]){
		if(es[i]==fath) continue;
		dis1[es[i]]=(dis1[now]-son[es[i]]+mod)%mod;
		dis2[es[i]]=((dis2[now]-son[es[i]]+mod)%mod+(n-son[es[i]]))%mod;
		dfs2(es[i],now);
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	int u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		link(u,v),link(v,u);
	}
	dfs1(1,0,0);
	dis1[1]=dis2[1]=sum;
	dfs2(1,0);
	for(int i=1;i<=n;i++) tot1=(tot1+dis1[i])%mod,tot2=(tot2+dis2[i])%mod;
	cout<<((n*tot1%mod-tot2+mod)%mod*inv)%mod;
        /*不用逆元的方法：
        int ans=(n*tot1%mod-tot2+mod)%mod;
	if(ans&1) cout<<(ans+mod)/2%mod;
	else cout<<ans/2%mod;
        */
	return 0;
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

对于一棵含有 $n$ 个结点的树，定义 $f(u,v,i)$ 为点 $i$ 到 $u\rightarrow v$ 路径上所有点距离的最小值，求 $\sum\limits_{u = 1}^n \sum\limits_{v = u + 1}^n \sum\limits_{i = 1}^n f(u, v, i)$ 对 $10^9 + 7$ 取模的值。

## 解题思路

$\sum\limits_{u = 1}^n \sum\limits_{v = u + 1}^n \sum\limits_{i = 1}^n f(u, v, i)$ 实际上就是对于每条路径，每个节点到其的距离之和。

我们很难考虑每一个点对答案的贡献，而每一条边对答案的贡献则好算得多。考虑边 $x\rightarrow y$（其中 $x$ 的深度小于 $y$），不难发现只有 $u,v$ 都在 $y$ 的子树中或都不在 $y$ 的子树中时才会对答案做出贡献。

以 $u,v$ 都不在在 $y$ 的子树中举例，这时 $y$ 的子树中的每个点都要经过边 $x\rightarrow y$ 到达路径 $u\rightarrow v$，因此对于每条路径 $u\rightarrow v$，贡献的大小为 $y$ 的子树的大小；而路径 $u\rightarrow v$ 的个数可以由组合数计算而来。$u,v$ 都在 $y$ 的子树的情况同理。

具体地，我们先用 DFS 以任意节点 $r$ 为根节点，处理出以 $i$ 为根节点的子树大小 $s_i$，再对于每条边 $x\rightarrow y$，将答案加上：

$$\frac{(s_r-s_y)(s_r-s_y-1)}{2}\times s_y+\frac{s_y(s_y-1)}{2}\times (s_r-s_y)$$

最后对 $10^9+7$ 取模即可求得最终答案。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 200100, P = 1e9+7;
vector<ll> g[N];
ll n, u, v, ans, fa[N], sz[N];
void dfs(int p) {
    sz[p] = 1;
    for (ll ed : g[p]) {
        if (ed != fa[p]) {
            fa[ed] = p;
            dfs(ed);
            sz[p] += sz[ed];
        }
    }
}
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i < n; i++) {
        scanf("%lld%lld", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    for (ll i = 1; i <= n; i++)
        for (ll ed : g[i])
            if (ed != fa[i])
                ans = (ans + ((sz[1] - sz[ed]) * (sz[1] - sz[ed] - 1) / 2 * sz[ed]) % P + (sz[ed] * (sz[ed] - 1) / 2 * (sz[1] - sz[ed])) % P) % P;
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：SamHJD (赞：0)

> 求树上每个点到每条路径的最短距离之和。

考虑每条边 $(u,v)$ 的贡献，即其作为某点到某路径的最短路上的边的次数。

由于是一棵树，只要点和路径分别在 $(u,v)$ 的两侧那么最短路一定经过 $(u,v)$。设 $(u,v)$ 两侧的点数（包括 $u,v$）分别为 $cnt_u,cnt_v$，则 $u$ 一侧选出一个点的方案为 $cnt_u$，选出一条路径的方案为 $cnt_u\times (cnt_u-1)\times \dfrac{1}{2}$，贡献为 $(cnt_u\times cnt_v\times (cnt_v-1)+cnt_v\times cnt_u\times(cnt_u))\times \dfrac{1}{2}$。

处理出每个结点的子树大小即可，注意每条边不要重复计算。

```cpp
#include "bits/stdc++.h"
#define int long long
#define rep(i,s,t) for(int i=s;i<=t;++i)
#define per(i,t,s) for(int i=t;i>=s;--i)
using namespace std;
template<typename T>
inline void read(T &x) {
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+c-'0';
	x*=f;
}
const int N=2e5+10,MOD=1e9+7;
int n,m,f[N],siz[N],ans;
vector<int> g[N];
void dfs(int u,int fa){
	f[u]=fa;siz[u]=1;
	for(auto v:g[u]){
		if(v==fa) continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
void calc(int u,int v){
	if(f[v]==u) swap(u,v);
	ans=(ans+siz[u]*(siz[u]-1)/2%MOD*(n-siz[u])%MOD)%MOD;
	ans=(ans+(n-siz[u])*(n-siz[u]-1)/2%MOD*siz[u]%MOD)%MOD;
}
signed main(){
	read(n);
	rep(i,1,n-1){
		int u,v;read(u);read(v);
		g[u].push_back(v);g[v].push_back(u);
	}
	dfs(1,0);
	rep(i,1,n) for(auto v:g[i]) if(v>i) calc(i,v);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：junee (赞：0)

# P10842 题解

## 题目分析

对于 $dis(u, x) + dis(v, x) = dis(u, v)$ 这个条件，本质上就是说 $x$ 在 $u$ 和 $v$ 之间的路径上。

考虑直接在边上维护，每次枚举到 $u,v,i$ 时，把 $x$ 到 $i$ 路径上的边加 1，那么 $ans = \sum\limits_{edge \in E} cnt$，$cnt$ 为每条边被覆盖的次数。

现在枚举每条边，记两个端点为 $a,b$，如果 $u,v$ 不经过 $a,b$ 并且 $i$ 不在这颗子树内部，那么边 $a,b$ 就会被覆盖一次，这本质上就是一个选点问题，两个点在以 $a$ 的子树内，一个点在 $b$ 的子树内，反过来一样的。

所以 $cnt_{a,b} = sz_a \times \frac{sz_b\times (sz_b-1)}{2} + sz_b \times \frac{sz_a\times (sz_a-1)}{2}$。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=2e5+10,p=1e9+7;
LL h[N],e[N*2],ne[N*2],idx,n,sz[N];
LL ans=0,inv;
LL qmi(LL a,LL k){
	LL res=1;
	while(k){
		if(k&1)res=res*a%p;
		k>>=1;
		a=a*a%p;
	}
	return res;
}
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
void dfs(int u,int fa){
	sz[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa)continue;
		dfs(j,u);
		sz[u]+=sz[j];
		ans=(ans+sz[j]*((n-sz[j])*(n-sz[j]-1)%p*inv%p)%p+(n-sz[j])*(sz[j]*(sz[j]-1)%p*inv%p)%p)%p;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	memset(h,-1,sizeof h);
	cin>>n;
	inv=qmi(2,p-2);
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		add(a,b),add(b,a);
	}
	dfs(1,-1);
	cout<<ans;
	return 0;
}

```

---

