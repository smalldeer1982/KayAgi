# [ABC312G] Avoid Straight Line

## 题目描述

给定一棵有 $N$ 个顶点的树。顶点编号为 $1$ 到 $N$，第 $i$ 条边连接顶点 $A_i$ 和顶点 $B_i$。  
请计算满足以下条件的整数三元组 $(i, j, k)$ 的个数。

- $1 \leq i < j < k \leq N$
- 在给定的树中，不存在一条简单路径包含顶点 $i, j, k$。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq N$
- 给定的图是一棵树
- 输入的所有值均为整数

## 样例解释 1

满足条件的 $(i, j, k)$ 有 $(1,3,4)$ 和 $(3,4,5)$，共 $2$ 组。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
1 5```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
4 5
5 6```

### 输出

```
0```

## 样例 #3

### 输入

```
12
1 6
3 4
10 4
5 9
3 1
2 3
7 2
2 12
1 5
6 8
4 11```

### 输出

```
91```

# 题解

## 作者：truly_handsome (赞：16)

看了一下题解，好像只有我一个是直接算的。

随便取一个节点当做根，发现只有在他的三个不同子树中选三个点才能使他们不再同一条直线上，所以枚举根然后算随便选三个节点的方案数加起来就是答案。

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;

const int N = 200005;

int n, sz[N], ans = 0;

vector <int> g[N];

// 处理子树大小
void dfs1(int u, int fa){
	sz[u] = 1;
	for (int v : g[u]) if (v != fa){
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

void dfs2(int u, int fa){
	int a = 0, b = 0, c = 0;
   //a 代表所有数的和，b 代表任意两个数的积的和，c 代表仍以三个数的积的和
	for (int i = 0;i < g[u].size();i++){
		int v = g[u][i], k = 0;
		if (v != fa){
			dfs2(v, u);
			k = sz[v];
		}
		else k = n - sz[u];
		c += k * b;
		b += k * a;
		a += k;
	}
	ans += c;
}

signed main(){
	scanf("%lld", &n);
	for (int i = 1;i < n;i++){
		int u, v; scanf("%lld%lld", &u, &v);
		g[u].pb(v); g[v].pb(u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	printf("%lld", ans);
	return 0;
}


```


---

## 作者：lyingOvO (赞：14)

# 题意
有一棵节点编号 $1$ ~ $n$ 的树，求满足下列条件的三元组 $(i,j,k)$ 的个数。

$1 \le i<j<k \le n$。

$i,j,k$ 不存在一条简单路径。
# 思路
直接求不存在简单路径比较难求，我们考虑用容斥，先求出所有满足第一点的三元组个数，也就是 $C_{n}^{3}$ ，再减去所有其中的简单路径个数，对于每个有简单路径的三元组 $(i,j,k)$ ，我们可以看成是 $i$ 到 $j$ 的路径上经过了 $k$ ，我们把 $k$ 看为这棵树的根，那么显然 $i,j$ 不能在同一子树，否则就不会经过根，那么我们把每个节点都看成 $k$ 那么简单路径的总数就有 $\sum_{i=2}^{n}sz[i]\times(n-sz[i])$，其中 $sz[i]$ 为 $i$ 的子树和，我们考虑到每个简单路径会被 $i$ 枚举一次、 $j$ 枚举一次，总共会枚举到两次，所以最后的结果要减去 $C_{n}^{2}$ ，所以最后的式子为 $C_{n}^{3}-(\sum_{i=2}^{n}sz[i]\times(n-sz[i])-C_{n}^{2})$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
const int N=2e5+10;
ll n,sz[N],ans;
std::vector<int> e[N];
inline void dfs(int x,int fa){
	sz[x]=1;
	for(auto y:e[x]){
		if(y==fa) continue;
		dfs(y,x);
		sz[x]+=sz[y];
		ans+=sz[y]*(n-sz[y]);
	}
}
int main(){
	scanf("%lld",&n);
	rep(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].pb(v);
		e[v].pb(u);
	}
	dfs(1,0);
	printf("%lld",1ll*n*(n-1)*(n-2)/6-ans+(n-1)*n/2);
	return 0;
}
```


---

## 作者：igAC (赞：7)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc312_g)

[ATlink](https://atcoder.jp/contests/abc312/tasks/abc312_g)

简要题意：

给定一棵 $n$ 个节点的树。

统计三元组 $(i,j,k),1 \le i < j < k \le n$ 不在任何简单路径上的个数。

# $\text{Solution}$

比较妙的树论题。

我们发现非简单路径的数量很难统计，正难则反，考虑统计简单路径的数量。

我们钦定要选择一个节点 $u$，考虑如何选择其他两个节点，我们发现有两种情况。

1. 选择它的一个儿子 $v$ 的子树内的节点以及 $u$ 的子树内其他的节点。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/1buuoxfi.png)

我们钦定选择 $1$ 节点，我们发现选择 $2$ 的子树中的任意，再选择 $1$ 的子树内的其他节点都是简单路径。

对于最后的答案我们要 $\div 2$，因为我们会取到 $(1,2,3)$ 和 $(1,3,2)$。

2. 选择 $u$ 的子树内的任何节点，以及非 $u$ 子树的任何节点。

这是显然的。

而总共的三元组个数是 $C_{n}^{3}$，也就是 $\dfrac{n(n-1)(n-2)}{6}$。

我们令 $size_u$ 表示 $u$ 的子树大小。

那么最后的答案就是：

$$
C_{n}^{3}-\sum_{u=1}^{n} (\dfrac{\sum_{v \in son_u}size_v \times (size_u-size_v-1)}{2}+(size_u-1) \times (n-size_u))
$$

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,head[N],tot,Size[N];
int ans,sum;
vector<int>son[N];
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void dfs(int x,int f){
	Size[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==f) continue;
		son[x].push_back(y);
		dfs(y,x);
		Size[x]+=Size[y];
	}
}
signed main(){
	n=read(),ans=n*(n-1)*(n-2)/6;
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,0);
	for(int x=1;x<=n;++x){
		int res=0;
		for(int y:son[x]) res+=Size[y]*(Size[x]-Size[y]-1);
		sum+=res/2+(Size[x]-1)*(n-Size[x]);
	}
	printf("%lld",ans-sum);
	return 0;
}
```

---

## 作者：FFTotoro (赞：6)

## 前言

纪念自己第二次做出 ABC 的 G！

## 解法

显然的一个树形 DP。

令 $e_{r,i}$ 为在以 $r$ 为根的树中**以 $i$ 为根结点的子树大小**，$f_{r,i}$ 为在以 $r$ 为根的树中**结点 $i$ 的父亲**。先将这棵树视为以 $1$ 为根的有根树，维护出所有 $e_{1,i}$。

正难则反，考虑有多少个 $(i,j,k)$ 在同一条路径上。枚举三个点中间的那一个 $x$，剩下两个只可能在它的几个儿子管辖的子树内或在 $x$ 管辖的子树外（当然另外两个点不可能在同一棵子树内或都在 $x$ 管辖的子树外）。

为方便理解，我们将 $x$ 视为根，令以 $r$ 为根的子树中的 $x$ 儿子集合为 $\mathrm{son}_{r,x}$，这时以 $1$ 为根的树中 $x$ 的子树外的所有结点在以 $x$ 为根的情况下变成了以 $f_{1,x}$ 为根的一棵子树，其大小为 $n-e_{1,x}$。显然以 $x$ 为中点的路径数为：

$$
\begin{aligned}
\sum\limits_{u\in\mathrm{son}_{x,x}}\sum\limits_{v\in\mathrm{son}_{x,x}\land u\ne v}e_{x,u}e_{x,v}=\dfrac{\left(n-e_{1,x}+\sum\limits_{u\in\mathrm{son}_{1,x}} e_{1,u}\right)^2-\left(n-e_{1,x}\right)^2-\sum\limits_{u\in\mathrm{son}_{1,x}}e_{1,u}^2}{2}
\end{aligned}
$$

这里 $\land$ 表示[合取](https://baike.baidu.com/item/%E5%90%88%E5%8F%96/2841151)。

把所有点的贡献加起来，记为 $s$，再用 $\mathrm{C}_n^3=\dfrac{n(n-1)(n-2)}{6}$ 减去 $s$ 即为答案。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,s=0; cin>>n;
  vector<int> e(n),f(n);
  vector<vector<int> > g(n);
  for(int i=1;i<n;i++){
    int u,v; cin>>u>>v;
    g[--u].emplace_back(--v);
    g[v].emplace_back(u);
  }
  function<void(int,int)> dfs=[&](int u,int f){
    e[u]=1;
    for(int i:g[u])
      if(i!=f)dfs(i,u),e[u]+=e[i];
  };
  dfs(0,0);
  function<void(int,int)> dfs2=[&](int u,int f){
    int c=0,c2=0;
    for(int i:g[u])
      if(i==f)c+=n-e[u],c2+=(n-e[u])*(n-e[u]);
      else dfs2(i,u),c+=e[i],c2+=e[i]*e[i];
    s+=c*c-c2>>1;
  };
  dfs2(0,0);
  cout<<n*(n-1)*(n-2)/6-s<<endl;
  return 0;
}
```

---

## 作者：TernaryTree (赞：4)

容斥完转换成选三个点在一条链上。枚举中间点，剩下两个点在这个点为根的不同子树里。方案数是

$$\dfrac12\left(\left(\sum siz_v\right)^2-\sum siz_v^2\right)$$

换根，甚至都不算换根地算一下就行。

$\Theta(n)$。

---

## 作者：MYiFR (赞：2)

### 题目大意
给定一棵有 $n$ 个点的树，求无序三元组 $(i,j,k)$ 使得树中不存在经过 $i$，$j$，$k$ 的简单路径的数量。

### 解题思路
整体减空白的伟大思想仍在发光发热。

这题不方便直接算答案，我们选择用总方案数 $\displaystyle\frac{n(n-1)(n-2)}{6}$ 减去有经过 $i$，$j$，$k$ 的简单路径的三元组数量就是答案，后面那个显然好算得多。（虽然直接算也不是不行。）

看了一眼题解区，给一个可能更加直观的思路。

记录以 $i$ 为根的子树中数对 $(a,b)$ 使得 $a$ 是 $b$ 的祖先的数量 $dp_i$，以 $i$ 为根的子树的大小为 $siz_i$。那么对于一个以 $cur$ 为根的子树，它的负贡献分为三类。
1. $(i,cur,j)$，其中 $i$ 和 $j$ 是分别以 $cur$ 的两个不同儿子为根的两棵子树中的两个点。
2. $(i,j,k)$，其中 $j$ 和 $k$ 在以 $cur$ 的一个儿子为根的子树上且 $j$ 是 $i$ 的祖先，$k$ 在另一棵子树上。
3. $(i,j,cur)$，其中 $i$ 和 $j$ 在以 $cur$ 的一个儿子为根的子树上且 $j$ 是 $i$ 的祖先。

接下来就好求了，dfs 跑一遍就好了。

### AC 代码
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<db,db>
#define F first
#define S second
using namespace std;
const ll N=2e5+5;
ll n,a,b,siz[N],dp[N],ans;
vector<ll> e[N];
ll f(ll x){
	if(x<3) return 0;
	return x*(x-1)*(x-2)/6;
}
void dfs(int cur,int fa){
	ll sum1=0;
	for(int to:e[cur]){
		if(to!=fa){
			dfs(to,cur);
			sum1+=dp[to];
			ans-=siz[to]*siz[cur];
			siz[cur]+=siz[to];
		}
	}
	for(int to:e[cur]){
		if(to!=fa){
			ans-=(sum1-dp[to])*siz[to];
		}
	}
	ans-=sum1;
	dp[cur]=sum1+siz[cur];
	++siz[cur];
}
int main(){
	scanf("%d",&n);
	ans=f(n);
	for(int i=1;i<n;++i){
		scanf("%d%d",&a,&b);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
//Ltwcfm.
```

---

## 作者：zhanghao233 (赞：2)

# 题目大意

- 求三元组 $(i,j,k)$ 的个数且 $i,j,k$ 三个点不在同一条简单路径上。

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $

# 思路

我们直接求所有不在简单路径上的情况比较难，我们可以用所有路径减所有不符合题意的简单路径就等于要求的简单路径了，也就是整体减部分等于另外一部分我们要求的。

考虑直接枚举其他路径，很明显叶子节点的情况很难处理，会导致时间复杂度飙升。

考虑优化，我们把所要减的部分，分成两部分：一种是一条简单路径上有三个节点及以上的，另一种则是两个节点的。因为第二种可以直接用组合数学写出来，而第一种要用其他方法。

我们可以不用枚举简单路径，而是枚举它上面的节点，显然的我们 $i$ 到 $j$ 一定要经过 $k$ ，如果 $i$ 是 $k$ 的儿子，那么 $i$ 就可以与 $n-size_k$ 的点成为简单路径，其中 $size_k$ 表示以 $k$ 为根的子树大小，显而易见答案就是所有子树里所有节点乘以 $n-size_k$，记为 $sum$。

最后的答案就是 $C^3_n-sum+C^2_n$。

---

## 作者：Fire_flame (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc312_g)

## $\mathtt{Solution}$

发现正着算好像不是很可做，于是反向考虑：在树上选择 $i<j<k$ 使得他们在同一条路径上。

首先所有的情况就是 $\sum\limits_{i=2}^{n-1}(i-1)\times (n-i)$。

记 $siz_x$ 为 $x$ 的子树大小（包括自己），$son_{x,i}$ 表示 $x$ 的第 $i$ 个儿子，$p_x$ 表示 $x$ 儿子的个数。

那么，当我们深搜遍历到某个节点 $u$ 时，看看他能对答案贡献多少。

![](https://cdn.luogu.com.cn/upload/image_hosting/blnnhedh.png?x-oss-process=image/resize,m_lfit,h_3000,w_3000)

见上图，我们发现对于节点 $u$，会产生两种贡献：

1. 自己的一颗子树的节点到另外一颗子树的节点的路径，例如 $w$ 内的一个节点到 $y$ 内的一个节点就是一个典型的例子。

2. 自己的一颗子树的节点到不在自己子树内部的节点的路径。

此时我们发现，上面的贡献是 $(siz_u-1)\times (n-siz_u)$。

下面的贡献就是 $\sum\limits_{l=1}^{p_u-1}\sum\limits_{r=l+1}^{p_u}siz_{son_{x,l}}\times siz_{son_{x,r}}$。

对于这个式子，我们可以用两种方法计算：

1. 原式 $=\dfrac{\big(\sum\limits_{i=1}^{p_u}siz_{son_{u,i}}\big)^2-\sum\limits_{i=1}^{p_u}siz_{son_{u,i}}^2}{2}$

2. 在 `for` 循环遍历儿子的时候用一个变量 $tmp$ 记录前面所有儿子的 $siz$ 总和，每次答案加上 $tmp\times siz_{son_{u,i}}$，$tmp$ 加上 $siz_{son_{u,i}}$。

就可以使用 $O(n)$ 的时间计算答案了，题解使用的是后者。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 2e5 + 5;
int n, cnt, ans, head[MAXN], siz[MAXN];
struct edge{
	int from, to, nxt;
}e[MAXN * 2];
void add_edge(int u, int v){
	e[++ cnt] = {u, v, head[u]};
	head[u] = cnt;
}
void dfs(int x, int fa){
	siz[x] = 1;
	for(int i = head[x];i;i = e[i].nxt){
		int v = e[i].to;
		if(v == fa)continue;
		dfs(v, x);
		siz[x] += siz[v];
	}
}
void dfs2(int x, int fa){
	ans -= (siz[x] - 1) * (n - siz[x]);
	int res = 0;
	for(int i = head[x];i;i = e[i].nxt){
		int v = e[i].to;
		if(v == fa)continue;
		dfs2(v, x);
		ans -= siz[v] * res;
		res += siz[v];
	}
}
signed main(){
	n = read();
	for(int i = 1;i < n;i ++){
		int u = read(), v = read();
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
	for(int i = 1;i <= n;i ++)
		ans += (i - 1) * (n - i);
	dfs2(1, 0);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Sunflower_ac (赞：2)

# 【题解】[ABC312G] Avoid Straight Line

[博客园食用效果更佳](https://www.cnblogs.com/xrkforces/p/ABC312G.html)

## 题目链接

[[ABC312G] Avoid Straight Line](https://atcoder.jp/contests/abc312/tasks/abc312_g)

## 题意概述

给定一棵 $n$ 个节点的树，第 $i$ 条边连接节点 $a_i$ 和 $b_i$，要求找到满足以下条件的三元整数组 $(i,j,k)$ 的数量：

- $1\le i<j<k\le n$；
- 对于树上任意一条简单路径，都不同时经过 $i,j,k$。

## 数据范围

- $1 \le n \le 2\times 10^5$
- $1\le a_i,b_i \le n$

## 思路分析

 题目要求对于树上任意一条简单路径都不同时经过 $i,j,k$，这个条件直接思考不容易想出来有什么处理的办法，考虑正难则反，我们可以先求出**树上至少有一条路径同时经过 $i,j,k$ 时满足条件的三元组 $(i,j,k)$ 的数量**，然后再容斥。

即，问题可以转化为：

> 树上所有满足 $1\le i<j< k\le n$ 的三元组 $(i,j,k)$ 的数量减去**树上至少有一条路径同时经过 $i,j,k$ 时，满足条件的三元组 $(i,j,k)$ 的数量**。

树上所有满足 $1\le i <j<k \le n$ 的三元组 $(i,j,k)$ 的数量实际上就是在 $1-n$ 的所有数中找到三个数 $(i,j,k)$ 使得 $1 \le i<j<k \le n$ 的数量，也就是 $\mathrm{C}_n^3=\dfrac{n\times (n-1)\times (n-2)}{6}$。

---

现在问题就只剩下：树上至少有一条路径同时经过 $i,j,k$ 时满足条件的三元组 $(i,j,k)$ 的数量怎么求。

有一条路径同时经过 $i,j,k$ 实际上就相当于是 $i$ 在 $j$ 到 $k$ 的路径上，或 $j$ 在 $i$ 到 $k$ 的路径上，或 $k$ 在 $i$ 到 $j$ 的路径上。

这就给了我们一个思路：我们首先可以钦定一个**中间节点 $u$**，即对于每一个点 $u$，其中 $1 \le u \le n$，满足有多少个不同于 $u$ 的**无序**点对 $(v,w)$ 使得 $u$ 在点 $v$ 到 $w$ 的路径上。这也就是当 $u$ 作为中间节点时符合条件的三元组的数量。

那么树上所有的点作为中间节点时的答案之和，就是树上至少有一条路径同时经过 $i,j,k$ 时满足条件的三元组 $(i,j,k)$ 的数量。

现在考虑怎么求当固定点 $u$ 作为中间节点时，有多少个不同于 $u$ 的无序点对 $(v,w)$ 使得 $u$ 在 $v$ 到 $w$ 的路径上。

考虑当 $u$ 作为整棵树的根时，显然要使得 $u$ 成为中间节点，那么当它的一个子树内的节点 $t$ 作为 $v$ 时，与 $t$ 在同一个子树内的节点一定不能作为 $w$，只有与它不在同一个子树内非 $u$ 的节点才有可能成为 $w$，也就是说其它子树内任意一个节点都可以作为 $w$。

也就是说对于 $u$ 的一个子树的根 $t$，该子树的点作为 $v$ 的方案数是 $sz_t\times (n-sz_t-1)$，由于是**无序**点对（即 $(v,w)$ 和 $(w,v)$ 算同一个点对，为了防止计算重复，那么我们需要在枚举 $u$ 的儿子时，每次减去当前已经被算过的点的个数，即我们可以定义一个 $now$，初始化 $now=n-1$，每次计算完一个子树 $t$ 的答案，就让 $now$ 减去 $sz_t$（因为这个子树内的点与后面子树的点的组合成为点对算过答案了，之后就没有必要再计算了），那么当前这个子树 $t$ 的答案 $ans_t=sz_t\times now$（具体详见下面的代码）。那么 $u$ 作为中间节点的点答案就是它所有的儿子的答案之和，即 $\sum \limits_{t\in son_u} ans_t$。

那么对于最后满足条件的三元组的数量 $ans$，我们只需要从 $1$ 开始 dfs 一遍，跑出所有点作为中间节点的答案然后加起来就可以了。

最终的答案就是 $\mathrm{C_n^3}-ans$。

## 代码实现

```cpp
//G
//The Way to Terminal Station…
#include<cstdio>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int maxn=2e5+10;
int sz[maxn];
int ans,n;

basic_string<int>edge[maxn];

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void dfs(int x,int fa)
{
	int ret=0;
	for(int y:edge[x])
	{
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
	}
	sz[x]++;
	int now=n-1;
	for(int y:edge[x])
	{
		if(y==fa)continue;
		now-=sz[y];
		ret+=sz[y]*now;
	}
	if(edge[x].size()>1)ans+=ret;
	return ;
}

signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int a,b;
		a=read();b=read();
		edge[a]+=b;
		edge[b]+=a;
	}
	int tot=n*(n-1)*(n-2)/6;
	dfs(1,0);
	cout<<tot-ans<<'\n';
	return 0;
}
```





---

