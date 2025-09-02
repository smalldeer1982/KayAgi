# [传智杯 #4 决赛] 生活在树上（easy version）

## 题目背景

**本题是 P8201 的简单版本，两道题目的解法略有不同。本题和 P8201 在题意上的区别在于本题给定树上的边权，而不是点权。**

小智生活在「传智国」，这是一个有 $n$ 个城市的国家，各个城市由 $n-1$ 条道路相连。

每个道路都有长度 $w_i$ ，我们定义，小智从城市 $a$ 走到城市 $b$ 的代价是 $\mathrm{dis}_{a, b} = \bigoplus \limits_{e \in \mathrm{path}\left(a, b\right)} w_e$，其中 $\bigoplus$ 表示**按位异或**（如果你不知道什么是**按位异或**，请参见题目下方的提示/说明），$\mathrm{path}\left(a,b\right)$ 表示 $a$ 到 $b$ 的简单路径上的边集。也即 $\mathrm{dis}_{a, b}$ 表示将 $a$ 与 $b$ 的简单路径上所有边写作 $e_1, e_2, e_3, \dots$ 后，求 $w_{e_1} \bigoplus w_{e_2}\bigoplus w_{e_3} \dots$ 的结果。

有一天，小智获得了去参加传智杯的机会，他在前往比赛地的路上想到了一个问题，但他好像不会做，于是他把这个题告诉了你。聪明的同学，你可以帮帮他吗？

## 题目描述

小智说：「由于我们的国家只有 $n$ 个城市和 $n-1$ 条道路，那么我们的国家就相当于是一棵树。我在想，在我们的国家中，是否有城市满足『到城市 $a$ 的代价和到城市 $b$ 的代价的异或等于 $k$』。好难哦，我想不出来，你能帮帮我吗？」

也就是说，给定城市 $a, b$ 和整数 $k$，请你计算是否存在城市 $t$ 满足 $\mathrm{dis}_{t, a} \bigoplus \mathrm{dis}_{t, b} = k$。

## 说明/提示

### 相关概念解释
「树」：树是一个有 $n$ 个结点和 $n-1$ 条边的无向简单连通图。

「按位异或」：按位异或即 C++、python、java 语言中的 「^」 运算。它是一个二元运算，步骤是将两个数的二进制位按位比较，相同为 $0$，不同为 $1$。例如：$3 \bigoplus 5 = (011)_2 \bigoplus (101)_2 = (110)_2 = 6$。**请注意，这是一个按位运算，不是一个逻辑运算**。
### 样例 1 解释
下图为传智国的地图。

$\forall t \in \{1, 2, 3, 4, 5\}$，都不可能有 $\mathrm{dis} _{t,1} \bigoplus \mathrm{dis}_{t, 2} = 4$，$\mathrm{dis}_{t, 2} \bigoplus \mathrm{dis}_{t, 3} = 12$，于是输出 `No`；

而取 $t = 5$，有 $\mathrm{dis}_{t, 1} \bigoplus \mathrm{dis}_{t, 4} = 10$，于是输出 `Yes`。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ikzjfh3.png)
### 数据规模与约定
对于所有测试点，保证 $1 < n \leq 5 \times 10^5$，$1 \leq m \leq 5 \times 10^5$，$0 \leq w_i < 2^{64}$。

对于每次询问，保证 $1 \leq a, b \leq n$ 且 $a \neq b$，$0 \leq k < 2^{64}$。

## 样例 #1

### 输入

```
5 3
1 2 2
1 3 6 
2 4 8
2 5 1
1 2 4
2 3 12
1 4 10```

### 输出

```
nO
No
YeS```

## 样例 #2

### 输入

```
5 10
2 1 63
3 1 57
4 2 2
5 2 84
5 2 84
4 1 9977404983223574764
2 5 84
2 1 15996060349666123522
5 4 86
3 1 8428615422876116375
5 1 107
2 3 6
2 3 6
4 2 2```

### 输出

```
yeS
nO
YEs
No
YEs
nO
YEs
yeS
yeS
YEs```

# 题解

## 作者：MeowScore (赞：25)

[传送门 qwq](https://www.luogu.com.cn/problem/P8200)

这是一道黄题，显然出题人想让我们用很简单的办法秒掉这道题，所以我使用树剖套线段树。

考虑异或的性质，如果一条边的权值被异或两遍，就相当于没异或。

再来看这道题。对于一次询问 $(x,y,k)$，我们任取一个点 $t$，如果 $t$ 不在 $x$ 到 $y$ 的链上，设沿着 $t$ 向上或向下走，首次到达 $x$ 到 $y$ 的链上时处于点 $p$，则：

$$
dis_{x,t}\oplus dis_{y,t}=dis_{x,p}\oplus dis_{y,p}\oplus dis_{t,p}\oplus dis_{t,p}=dis_{x,y}
$$

如果 $t$ 在 $x$ 到 $y$ 的链上，显然：

$$
dis_{x,t}\oplus dis_{y,t}=dis_{x,y}
$$

发现柿子是一样的。

于是发现对于这个查询，我们只要判断 $x$ 到 $y$ 这条链上的异或和是否等于 $k$ 就好了。树剖套线段树，线段树维护区间异或和即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
unsigned long long read(){
	unsigned long long ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
int readi(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
int n,m;
const int N=500010;
int head[N],nex[N*2],to[N*2],cnt;
unsigned long long e[N*2];
void add(int x,int y,unsigned long long z){
	cnt++;
	nex[cnt]=head[x];
	to[cnt]=y;
	e[cnt]=z;
	head[x]=cnt;
}
unsigned long long a[N],t[N];
unsigned long long st[N*4];
int sz[N],son[N],tp[N],fa[N],dfn[N],dep[N],tot;
void dfs1(int x,int f){
	fa[x]=f;
	dep[x]=dep[fa[x]]+1;
	sz[x]=1;
	int maxn=-1;
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==f)
			continue;
		t[y]=e[i];
		dfs1(y,x);
		sz[x]+=sz[y];
		if(sz[y]>maxn){
			maxn=sz[y];
			son[x]=y;
		}
	}
}
void dfs2(int x,int top){
	tp[x]=top;
	tot++;
	dfn[x]=tot;
	a[tot]=t[x];
	if(son[x])
		dfs2(son[x],top);
	for(int i=head[x];i;i=nex[i]){
		int y=to[i];
		if(y==fa[x]||y==son[x])
			continue;
		dfs2(y,y);
	}
}
unsigned long long res;
void build(int root,int l,int r){
	if(l==r){
		st[root]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	st[root]=st[root*2]^st[root*2+1];
}
void ask(int root,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		res=(res^st[root]);
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)
		ask(root*2,l,mid,x,y);
	if(mid+1<=y)
		ask(root*2+1,mid+1,r,x,y);
}
int main(){
	n=readi();
	m=readi();
	for(int i=1;i<n;i++){
		int x,y;
		unsigned long long z;
		x=readi();
		y=readi();
		z=read();
		add(x,y,z);
		add(y,x,z);
	}
	dfs1(1,1);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x,y;
		unsigned long long k;
		x=readi();
		y=readi();
		k=read();
		res=0;
		while(tp[x]!=tp[y]){
			if(dep[tp[x]]<dep[tp[y]])
				swap(x,y);
			ask(1,1,n,dfn[tp[x]],dfn[x]);
			x=fa[tp[x]];
		}
		if(x!=y){
			if(dep[x]>dep[y])
				swap(x,y);
			ask(1,1,n,dfn[x]+1,dfn[y]);
		}
		if(res==k)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：17)

## F1. 生活在树上（easy version）

**题意**：给定一棵树，点数为 $n$，边有边权。定义树上两点间路径的权值是其简单路径上边权的异或和。有 $q$ 次询问，每次给定两个节点 $x, y$ 查询是否存在一个点 $u$，使 $u$ 到 $x$ 和 $u$ 到 $y$ 的路径的权值的异或为 $k$。

$1 \leq n,q \leq 5 \times 10^5$，$0 \leq w_i \lt 2^{64}$。

**关键词**：前缀和，构造。

**参考难度**：黄+/绿-。

**解析**：（如果您对抽象代数的相关概念完全不了解，可以直接去看第三段。前两段是对第三段所述的显然的性质的简单说明，您可以默认这个结论是正确的）注意到异或运算构成一个 Abel 群：即异或运算满足交换律、结合律，其零元为 0；对每个 $x$，存在其逆元 $x$，满足 $x \bigoplus x = 0$。

根据结合律，我们可以将题目中所求的式子拆开，直接写作 $u$ 到 $x$ 和 $u$ 到 $y$ 的路径上每一条边的异或和（而不用先求两条路径的权值再做异或）；再根据交换律，可以把相同的边交换到相邻然后括在一起计算；因为 $x$ 的逆元是自身（也就是一个数异或自身是 0），所以两条路径上相同的边的做异或的结果 0。

简单来说，如果 $u$ 到 $x$ 和 $u$ 到 $y$ 的路径上经过了某条相同的边，那么这条边对异或和的贡献为 0，于是我们只需要考虑路径上不同的边。

显然，$u$ 到 $x$ 的路径和 $u$ 到 $y$ 的路径总是先经过若干条相同的边，然后与 $(x, y)$ 所成的链有一个交点 $t$，接着在这个交点处分开，一个走向 $x$ 一个走向 $y$，如图：![](https://cdn.luogu.com.cn/upload/image_hosting/x024zkpa.png)

图中红色路径是 $u$ 到 $x$ 的路径，蓝色路径是 $u$ 到 $y$ 的路径，二者在 $(u, t)$ 部分是重复的。不难验证，无论 $u$ 在哪个位置，都满足这个性质。

于是我们发现，无论 $u$ 在哪里，$\mathrm{dis}_{x, u} \bigoplus \mathrm{dis}_{x, v}$ 总等于 $\mathrm{dis}_{x, y}$，也就是 $x$ 到 $y$ 路径上边的异或和。于是问题转化成了求 $\mathrm{dis}_{x, y}$。我们设 $s_x$ 表示 $x$ 到根的简单路径上边权的异或和，则 $s_x  \bigoplus s_y$ 即为 $\mathrm{dis}_{x, y}$（因为他们到根的路径上相同的部分做异或对异或和没有贡献，不相同的部分恰好就是 $x$ 到 $y$ 的链）。

显然 $s$ 是可以递推的：$s_u = s_{fa} \bigoplus w_u$，其中 $fa$ 表示 $u$ 的父节点。于是在树上做一次 dfs，求出 $s$ 数组即可。如果 $\mathrm{dis}_{x, y} = k$，则 `Yes`，否则输出 `No`。

时间复杂度为 $O(n)$。


(C++)

```cpp
#include <array>
#include <vector>
#include <iostream>

const int maxn = 1000005;

int n, q;
std::array<std::vector<std::pair<int, unsigned long long> >, maxn> e;
std::array<unsigned long long, maxn> b;

void dfs(const int u, const int f);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cin >> n >> q;
  unsigned long long k;
  for (int u, v, i = 1; i < n; ++i) {
    std::cin >> u >> v >> k;
    e[u].push_back({v, k}); e[v].push_back({u, k});
  }
  dfs(1, 0);
  
  std::array<std::string, 2> ans{"nO", "yEs"};
  for (int i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v >> k;
    std::cout << ans[(b[u] ^ b[v]) == k] << '\n';
  }
}

void dfs(const int u, const int f) {
  for (auto [v, w] : e[u]) if (v != f) {
    b[v] = b[u] ^ w;
    dfs(v, u);
  }
}
```


---

## 作者：苏联小渣 (赞：6)

**Upd：2022.3.13：修改了原多余做法**

题目描述不说了。设 $d_{a,b}$ 表示树上两点路径异或和。假设两个点为 $x,y$，题目所要求的就是是否存在一点 $p$ 使得 $d_{p,x} \oplus d_{p,y}=k$。

设 $z=\text{LCA}(x,y)$，则上面式子转化为 $d_{p,z} \oplus d_{z,x} \oplus d_{p,z} \oplus d_{z,y}$。

根据异或的性质，$a\oplus a=0$，上式即转化为 $d_{z,x} \oplus d_{z,y}$。我们 `dfs` 一遍，预处理出从根节点到每个节点的异或和。容易发现这个 `dfs` 是 $O(n)$ 的。所以上式可以继续简化为 $d_{1,x} \oplus d_{1,z} \oplus d_{1,y} \oplus d_{1,z}$，然后就会发现 $d_{1,z}$ 恰好被消掉了，于是这题就不用求 $\text{LCA}$ 了，直接算 $d_{1,x} \oplus d_{1,y}$ 是否等于 $k$ 就行了。

注意两点：

1、要开 `unsigned long long`。

2、注意异或运算的优先级（就是因为这个考场上一直没过样例）。

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
int n, m, p, x, y, z, k, h[1000010], s[500010];
struct node{
	int x, y, z, next;
}d[1000010];
void add(int x, int y, int z){
	d[++p].y = y, d[p].z = z, d[p].next = h[x], h[x] = p;
}
void dfs(int a, int b){
	for (int i=h[a]; i; i=d[i].next){
		int to = d[i].y;
		if (to == b) continue;
		s[to] = s[a] ^ d[i].z;
		dfs(to, a);
	}
}
signed main(){
	scanf ("%llu%llu", &n, &m);
	for (int i=1; i<n; i++){
		scanf ("%llu%llu%llu", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	dfs(1, 0);
	while (m --){
		scanf ("%llu%llu%llu", &x, &y, &k);
		if ((s[x] ^ s[y]) == k) puts ("Yes");
		else puts ("No");
	}
	return 0;
}

```

---

## 作者：lsj2009 (赞：4)


## 题目大意

给定一颗树，$\mathrm{dis}_{a, b}$ 表示点 $a$ 到 $b$ 的路径上的边权异或和。

进行 $m$ 次询问，每次询问对于点 $a$ 和点 $b$，是否有一个 $i$ 满足 $\mathrm{dis}_{i, a}\bigoplus\mathrm{dis}_{i, b}=k$。

## 思路

很明显可以看出来，解决本题的第一步是需要求出每一个 $\mathrm{dis}_{a, b}$（可以快速查询）。

根据异或性质，我们可以得到如下等式：

$\mathrm{dis}_{a, b}=\mathrm{dis}_{1,a}\bigoplus\mathrm{dis}_{1, b}$

对于每一个 $\mathrm{dis}_{1,a}$ 我们可以以 $O(n)$ 的时间复杂度全部预处理出来。

### 建树&预处理 code:

```cpp
int dis[N],head[N],tot,n,m;
struct node {
	int to,w,nxt;
}; node Edge[N];
void Add_Edge(int u,int v,int w) {
	++tot; Edge[tot]=node{v,w,head[u]}; head[u]=tot;
}
void Dfs(int u,int fa) {
	for(int i=head[u];i;i=Edge[i].nxt) {
		int v=Edge[i].to,w=Edge[i].w;
		if(v!=fa)
			dis[v]=(dis[u]^w),Dfs(v,u);
	}
}
```

那么接下来最直接的想法就只需要枚举 $i$ 然后判断是否有 $i$ 满足条件就行了。

但是这样的时间复杂度 $O(nm)$，针对 $n,m\le5\cdot10^5$ 的数据还是望而终止的。

接下来不妨让我们推一个结论：

$\quad\mathrm{dis}_{i, a}\bigoplus\mathrm{dis}_{i, b}$

$=(\mathrm{dis}_{1, i}\bigoplus\mathrm{dis}_{1, a})\bigoplus(\mathrm{dis}_{1, i}\bigoplus\mathrm{dis}_{1, b})$

$=\mathrm{dis}_{1, i}\bigoplus\mathrm{dis}_{1, a}\bigoplus\mathrm{dis}_{1, i}\bigoplus\mathrm{dis}_{1, b}$

$=(\mathrm{dis}_{1, i}\bigoplus\mathrm{dis}_{1, i})\bigoplus\mathrm{dis}_{1, a}\bigoplus\mathrm{dis}_{1, b}$

$=0\bigoplus\mathrm{dis}_{1, a}\bigoplus\mathrm{dis}_{1, b}$

$=\mathrm{dis}_{1, a}\bigoplus\mathrm{dis}_{1, b}$

怎么样，发现了什么？其实我们并不需要 $「$ 枚举 $i$ 然后判断是否有 $i$ 满足条件 $」$，其实我们只需要判断 $\mathrm{dis}_{1, a}\bigoplus\mathrm{dis}_{1, b}$ 是否 $=k$ 就行了！

### 查询 code:
```cpp
while(m--) {
		int a,b,k;
		read(a,b,k); //快读
		puts((dis[a]^dis[b])==k? "Yes":"No");
	}
```

剩下部分还请自行完成。

---

## 作者：Dusker (赞：4)

出题人表示这题挺白给的（

记 $Xor[i]$ 为从根节点到 $i$ 号节点的异或和，那么从节点 $a$ 到节点 $b$ 的异或和就是 $Xor[a] \bigoplus Xor[b]$，其中 $\bigoplus$ 表示按位异或。

由于 $1\sim a$ 到 $1\sim b$ 的路径在 $1\sim \text{LCA}(a, b)$ 处都是一致的，于是异或之后消去即得上式。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
#define ioclear std::ios::sync_with_stdio(false);std::cin.tie(nullptr);std::cout.tie(nullptr);
#define endl '\n'
#define pii std::pair<int, i64>

const int mmax = 5e5 + 10;
using i64 = unsigned long long;

int n, m;
i64 Xor[mmax];
std::vector<pii> edge[mmax];

void dfs(int cur, int fa)
{
	for(auto v : edge[cur])
		if(v.first != fa)
			Xor[v.first] = Xor[cur] ^ v.second, dfs(v.first, cur);
	return;
}

int main()
{
	srand(unsigned(time(NULL)));
	ioclear;
	std::cin >> n >> m;
	for(int i = 1;i < n;i++)
	{
		int x, y;
		i64 w;
		std::cin >> x >> y >> w;
		edge[x].push_back({y, w});
		edge[y].push_back({x, w});
	}
	dfs(1, 0);
	for(int i = 1;i <= m;i++)
	{
		int x, y;
		i64 k;
		std::cin >> x >> y >> k;
		if((Xor[x] ^ Xor[y]) == k)
			{
				if(rand() & 1)
					std::cout << "yeS\n";
				else
					std::cout << "YEs\n";
			}
		else
			{
				if(rand() & 1)
					std::cout << "No\n";
				else
					std::cout << "nO\n";
			}
	}
}

```


---

## 作者：stntn (赞：2)

吐槽：SPJ有什么实际作用吗......

### 简要题意

给你一棵树,边有边权,若干次询问,每次询问两点 $a$,$b$ ,求是否有点 $t$ 满足 $dis_{a,t} \oplus dis_{b,t}=k$。

### 观察&分析

显然枚举所有点是不行的,我们需要换一种思路。

分三种情况讨论：

- 当 $t$ 在 $a$，$b$ 路径上时，$dis_{a,t} \oplus dis_{b,t}=dis_{a,b}$

- 当 $t$ 在 $a$，$b$ 其中一点的子树内时。

![](https://cdn.luogu.com.cn/upload/image_hosting/avzy3m3x.png)

如上图，$3\leftrightarrow  4$ 这条边被重复计算了，由于 $a \oplus a=0$ 所以此时 $dis_{a,t} \oplus dis_{b,t}=dis_{a,b}$

- 当 $t$ 在 $a$，$b$ 路径的任意一点上或该点的祖先上或子树内时

![](https://cdn.luogu.com.cn/upload/image_hosting/h66wpn7u.png)

如上图，$1\leftrightarrow  2$ 这条边被重复计算了，所以此时 $dis_{a,t} \oplus dis_{b,t}=dis_{a,b}$

综上所述，对于任意树上点 $t$，$dis_{a,t} \oplus dis_{b,t}=dis_{a,b}$

若 $k=dis_{a,b}$ 则一定存在点 $t$ 使得 $dis_{a,t} \oplus dis_{b,t}=k$。

预处理出每个点 $i$ 到根的路径异或和 $deep_i$ 即可，无需求 lca 因为 $dis_{a,b}=deep_a \oplus deep_b$ 证明可见图二。

### CODE

### 一定要开 unsigned long long ！

```cpp
#include<bits/stdc++.h> 
#define N 500010
#define re register
#define int unsigned long long
#define DB double
using namespace std;
int n,m,head[N],cc;
struct EDGE{int v,w,nxt;}e[N<<1];
inline void add_edge(int u,int v,int w)
{
	e[++cc].v=v;e[cc].w=w;e[cc].nxt=head[u];head[u]=cc;
	e[++cc].v=u;e[cc].w=w;e[cc].nxt=head[v];head[v]=cc;
}
int dis[N]; 
inline void dfs(int u,int fa)
{
	for(re int i=head[u];~i;i=e[i].nxt)
	{
		int v=e[i].v;if(v==fa) continue;
		dis[v]=dis[u]^e[i].w;dfs(v,u);
	}
}
signed main()
{
	memset(head,-1,sizeof(head));
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(re int i=1,u,v,w;i<n;i++)
	{
		cin>>u>>v>>w;
		add_edge(u,v,w);
	}
	dfs(1,0);
	while(m--)
	{
		int a,b,k;cin>>a>>b>>k;
		if((dis[a]^dis[b])==k) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：3a51_ (赞：1)

建议评级：绿

首先观察性质。

对于节点 $x$ 到 $a$ 和 $x$ 到 $b$，假设 $x$ 到 $a$ 的路径比 $x$ 到 $b$ 的路径短，那么可以得到 $x$ 到 $b$ 的路径就是 $x$ 到 $a$ 然后再从 $a$ 到 $b$。又由于这道题是异或，$x⨁x=0$，所以 $x$ 到 $a$ 的路径就直接没了。接下来只要算 $a$ 到 $b$ 就行了。

那 $a$ 到 $b$ 的路径怎么算呢？其实很简单，搞一个 $len_i$ 表示根节点到 $i$ 的路径异或后的结果，最终可以得到结果就是 $len_a ⨁ len_b ⨁ len_{\text{LCA(a,b)}}⨁ len_{\text{LCA(a,b)}}$。记得开一个`unsigned long long`。

代码：

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
const int maxn = 5e5 + 5;
struct edge{
    int to,next,w;
}pool[maxn << 1];
int head[maxn]{0},cnt,fa[maxn][25],depth[maxn]{0},n,m,len[maxn]{0};
inline void addedge(int u,int v,int w){
    pool[++cnt].next = head[u];
    pool[cnt].to = v;
    pool[cnt].w = w;
    head[u] = cnt;
}
bool vis[maxn]{0};
void dfs(int now){
    vis[now] = 1;
    for(int i = head[now];i;i = pool[i].next){
        int to = pool[i].to;
        if(vis[to])    continue;
        depth[to] = depth[now] + 1;
        len[to] = len[now] ^ pool[i].w;
        fa[to][0] = now;
        dfs(to);
    }
}
int lca(int x,int y){
    if(depth[x] < depth[y])    swap(x,y);
    for(int i = 24;i>=0;--i){ 
        if(depth[fa[x][i]] >= depth[y])
            x = fa[x][i];
        if(i==0) break;
    } 
    if(x == y)    return x;
    for(int i = 24;i>=0;--i){
        if(fa[x][i] != fa[y][i])
            x = fa[x][i],y = fa[y][i];
        if(i==0) break;
	}
    return fa[x][0];
}
signed main(){
    read(n,m);
    for(int i = 1;i<=n - 1;++i){
        int a,b,c;
        read(a,b,c);
        addedge(a,b,c);
        addedge(b,a,c);
    }
    depth[1] = 1;
    dfs(1);
    for(int i = 1;i<=24;++i)
        for(int j = 1;j<=n;++j)
            fa[j][i] = fa[fa[j][i-1]][i-1];
    while(m--){
        int a,b,k;
        read(a,b,k);
        int p=lca(a,b);
        int x=len[a]^len[b]^(len[p]^len[p]);
        if(x==k){
        	cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
    }
    return 0;
}
```


---

