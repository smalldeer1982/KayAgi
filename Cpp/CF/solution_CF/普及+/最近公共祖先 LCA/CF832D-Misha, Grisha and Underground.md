# Misha, Grisha and Underground

## 题目描述

Misha and Grisha are funny boys, so they like to use new underground. The underground has $ n $ stations connected with $ n-1 $ routes so that each route connects two stations, and it is possible to reach every station from any other.

The boys decided to have fun and came up with a plan. Namely, in some day in the morning Misha will ride the underground from station $ s $ to station $ f $ by the shortest path, and will draw with aerosol an ugly text "Misha was here" on every station he will pass through (including $ s $ and $ f $ ). After that on the same day at evening Grisha will ride from station $ t $ to station $ f $ by the shortest path and will count stations with Misha's text. After that at night the underground workers will wash the texts out, because the underground should be clean.

The boys have already chosen three stations $ a $ , $ b $ and $ c $ for each of several following days, one of them should be station $ s $ on that day, another should be station $ f $ , and the remaining should be station $ t $ . They became interested how they should choose these stations $ s $ , $ f $ , $ t $ so that the number Grisha will count is as large as possible. They asked you for help.

## 说明/提示

In the first example on the first day if $ s $ = $ 1 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ , and Grisha would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . He would see the text at the stations $ 1 $ and $ 2 $ . On the second day, if $ s $ = $ 3 $ , $ f $ = $ 2 $ , $ t $ = $ 3 $ , both boys would go on the route $ 3 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ . Grisha would see the text at $ 3 $ stations.

In the second examle if $ s $ = $ 1 $ , $ f $ = $ 3 $ , $ t $ = $ 2 $ , Misha would go on the route $ 1 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ , and Grisha would go on the route $ 2 $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF832D/355fee5161a1808ee95ea5dc6d815d4071657131.png) $ 3 $ and would see the text at both stations.

## 样例 #1

### 输入

```
3 2
1 1
1 2 3
2 3 3
```

### 输出

```
2
3
```

## 样例 #2

### 输入

```
4 1
1 2 3
1 2 3
```

### 输出

```
2
```

# 题解

## 作者：Little_x_starTYJ (赞：9)

### 解题思路
首先我们先思考如何求出两个点的最多公共节点个数。

不难想到，我们在走这两个点的简单路径统计经过的节点个数就可以得到答案，但是我们只需要稍微瞅一眼数据范围，就知道过不了。但是我们发现我们走到的点与我们在求最近公共祖先时走到的点完全一样。

于是一个新的思路诞生了：先枚举起点与终点，再求出它们的最近公共祖先，最后统计它们走到最近公共祖先时所经过的点的数量。

我们再注意到数据范围，很明显暴力最近公共祖先是过不了的，于是我们可以采用倍增法求最近公共祖先。

那怎么求它们走到最近公共祖先时所经过的点的数量呢？考虑到这两个点一定是向上走的，那么在每次查找中，每个点一定只会经过同一层的点一次，所以我们只需要求最近公共祖先与两点的深度差即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
vector<int> v[N];
int fa[N];
int f[N][20], dep[N];
void dfs(int u) {
	f[u][0] = fa[u], dep[u] = dep[fa[u]] + 1;
	for (int i = 0; i < v[u].size(); i++)
		if (v[u][i] != fa[u])
			dfs(v[u][i]);
}
int lca(int a, int b) {
	if (dep[a] < dep[b])
		swap(a, b);
	int x = a;
	for (int i = log2(dep[a] - dep[b]); i >= 0; i--)
		if ((1 << i) <= dep[a] - dep[b])
			a = f[a][i];
	if (a == b)
		return a;
	for (int i = log2(dep[a]); i >= 0; i--)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}
int dist(int u, int v) {
	int ans = lca(u, v);
	ans = dep[u] - dep[ans] + dep[v] - dep[ans];
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		int k;
		scanf("%d", &k);
		fa[i + 1] = k;
		v[k].push_back(i + 1);
		v[i + 1].push_back(k);
	}
	dfs(1);
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= n; j++)
			f[j][i] = f[f[j][i - 1]][i - 1];
	while (m--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		int ans1 = (dist(a, c) + dist(b, c) - dist(a, b)) / 2;
		int ans2 = (dist(a, b) + dist(c, b) - dist(a, c)) / 2;
		int ans3 = (dist(b, a) + dist(c, a) - dist(b, c)) / 2;
		printf("%d\n", max(ans1, max(ans2, ans3)) + 1);
	}
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：6)

一看这题，可以枚举两条路径的三种情况，分别计算路径交的长度取 $\max$。  

求两条路径的交，可以先在树上把一条链权值变为 $1$，另一条链上直接查询和，之后再变回去，简单暴力。

然后随便用树剖什么的维护一下就行了，，这里写的是 LCT。

时间复杂度 $\text O(q\log n)$。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define reg register
#define N 100003
#define ls son[u][0]
#define rs son[u][1]
using namespace std;

inline void read(int &x){
	x = 0;
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
}

int fa[N],son[N][2],st[N],a[N],sum[N],size[N],tag[N];
bool rev[N];
int n,q;

inline void pushup(int u){
    sum[u] = sum[ls]+sum[rs]+a[u];
    size[u] = size[ls]+size[rs]+1;
}

inline bool notrt(const int& u){
    return son[fa[u]][0]==u||son[fa[u]][1]==u;
}

inline void pushr(const int& u){
    swap(ls,rs);
    rev[u] ^= 1;
}

inline void pushc(const int& u,const int& k){
    a[u] = tag[u] = k;
    sum[u] = k==0?0:size[u];
}

inline void pushdown(const int& u){
    if(tag[u]!=-1){
        if(ls) pushc(ls,tag[u]);
        if(rs) pushc(rs,tag[u]);
        tag[u] = -1;
    }
    if(!rev[u]) return;
    if(ls) pushr(ls);
    if(rs) pushr(rs);
    rev[u] = 0;
}

inline void rotate(const int& x){
    int y = fa[x],z = fa[y];
    int k = son[y][1]==x,w = son[x][k^1];
    if(notrt(y)) son[z][son[z][1]==y] = x;
    son[x][k^1] = y;
    son[y][k] = w;
    if(w) fa[w] = y;
    fa[y] = x,fa[x] = z;
    pushup(y);
}

inline void splay(const int& x){
    reg int y = x,z = 0;
    st[++z] = y;
    while(notrt(y)) st[++z] = y = fa[y];
    while(z) pushdown(st[z--]);
    while(notrt(x)){
        y = fa[x],z = fa[y];
        if(notrt(y)) rotate((son[z][1]==y)==(son[y][1]==x)?y:x);
        rotate(x);
    }
    pushup(x);
}

inline void access(int u){
    for(reg int v=0;u;u=fa[u]){
        splay(u),rs = v;
        pushup(u),v = u;
    }
}

inline void makeroot(int u){
    access(u),splay(u);
    pushr(u);
}

inline void link(int u,int v){
    makeroot(u);
    fa[u] = v;
}

inline void split(int u,int v){
    makeroot(u);
    access(v),splay(v);
}

inline int check(int u1,int v1,int u2,int v2){
    split(u1,v1),pushc(v1,1);
    split(u2,v2);
    int res = sum[v2];
    split(u1,v1),pushc(v1,0);
    return res;
}

int main(){
    int x,y,z,ans;
    read(n),read(q);
    for(reg int i=1;i<=n;++i) tag[i] = -1;
    for(reg int i=2;i<=n;++i){
        read(x);
        link(x,i);
    }
    while(q--){
        read(x),read(y),read(z);
        ans = check(x,y,x,z);
        ans = max(ans,check(x,y,y,z));
        ans = max(ans,check(x,z,y,z));
        printf("%d\n",ans);
    }
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：4)

#### Description

> 给定一棵大小为 $n$ 的树，并给定 $q$ 次询问，每次询问给出点 $a,b,c$，可以以两个点为起点，一个点为终点，引出两条路径，求这两条路径的最大交点个数。

#### Solution

LCA 水题。下文定义 $p(a,b)$ 为点 $a$ 到点 $b$ 的路径，$len(p)$ 为路径 $p$ 的长度。

首先假设我们以点 $a,b$ 为起点，点 $c$ 为终点，计算答案，不难发现会存在一个交点 $d$，即 $p(a,c)$ 与 $p(b,c)$ 的交点。我们需要计算的东西即为 $len(p(d,c))$。

求 $d$ 并不好求，他有的时候是 LCA，有的时候是别的，所以我们需要转化答案为 $a,b,c$ 三个点的路径长度相加减，因为求路径长度很好求，用 LCA 作为桥梁求即可。

因为 $p(d,c)$ 是 $p(a,c)$ 与 $p(b,c)$ 的重叠部分，所以我们可以让这两条路径长度相加，即 $len(p(a,c))+len(p(b,c))$，但这样会做出来两部分：

1. $p(a,d)$，$p(b,d)$
2. $p(d,c)$

我们发现，第一部分刚好就是 $p(a,b)$，$d$ 只是一个中介点的作用。

第二部分刚好就是答案，所以要求的话直接除以 $2$ 即可。

注意题目要求的是 **点数**，我们求的是 **路径长度**，把答案加 $1$ 即可。

所以最终答案就是：

$$\dfrac{len(p(a,c))+len(p(b,c))-len(p(a,b))}{2}+1$$

除了 $a,b$ 为起点，$c$ 为终点外，还有两种情况：

- $a,c$ 为起点，$b$ 为终点。
- $b,c$ 为起点，$a$ 为终点。

所以算出来答案取个 $\max$ 即可。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

//

struct node {
	int u, v;
} e[N];

int cnt;
int head[N];

void AddEdge (int u, int v) {
	e[++cnt].u = v;
	e[cnt].v = head[u];
	head[u] = cnt;
}

//

struct to {
	int id; // 节点编号 
	int dep; // 节点深度 
	bool operator < (const to &oth) const {
		return dep < oth.dep;
	} // 重载运算符 '<'
} dfn[N], dp[N][20]; // dfs 序 & ST 

int dep[N], id[N]; // 节点深度 & 第一次出现在 dfs 序的位置
int len; // dfs 序长度

void dfs (int cur, int fa) {
	dep[cur] = dep[fa] + 1;
	dfn[++len] = (to){cur, dep[cur]};
	id[cur] = len;
//	printf("dfs 外层，cur = %d，fa = %d，len = %d\n", cur, fa, len);
	for (int p = head[cur]; p; p = e[p].v) {
		if (e[p].u == fa) continue;
//		printf("dfs 内层 1，cur = %d，fa = %d，len = %d\n", cur, fa, len);
		dfs(e[p].u, cur);
//		printf("dfs 内层 2，cur = %d，fa = %d，len = %d\n", cur, fa, len);
		dfn[++len] = (to){cur, dep[cur]};
	}
} 

//

int LCA (int u, int v) {
	int l = id[u], r = id[v];
	if (l > r) swap(l, r);
	int k = log2(r - l + 1);
	to tmp = min(dp[l][k], dp[r - (1 << k) + 1][k]);
	int ans = tmp.id;
	return ans;
}

int dist (int u, int v) {
	int ans = LCA(u, v);
	ans = dep[u] - dep[ans] + dep[v] - dep[ans];
	return ans;
}

int main () {
	int n, q;
	scanf("%d%d", &n, &q);
	int s = 1;
	for (int i = 2, p; i <= n; i++) {
		scanf("%d", &p);
		AddEdge(i, p);
		AddEdge(p, i);
	}
	dfs(s, 0);
	for (int i = 1; i <= len; i++) dp[i][0] = dfn[i];
	for (int k = 1; (1 << k) <= len; k++)
		for (int i = 1; i + (1 << k) - 1 <= len; i++)
			dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
	while (q--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		int ans1 = (dist(a, c) + dist(b, c) - dist(a, b)) / 2;
		int ans2 = (dist(a, b) + dist(c, b) - dist(a, c)) / 2;
		int ans3 = (dist(b, a) + dist(c, a) - dist(b, c)) / 2;
		printf("%d\n", max(ans1, max(ans2, ans3)) + 1);
	}
	return 0;
}
```

代码写的是 ST 表求 LCA。

---

## 作者：codecode (赞：2)

#### 题解：

我们考虑分类讨论：分三种情况，依次枚举三个点分别为公共点时，路径的公共节点数。

不妨先求从 $a$ 到 $b$ 的路径与从 $a$ 到 $c$ 的路径的公共节点数。

由于这是一棵树，那么这两条路径的公共部分必定为 $a$ 到 $\operatorname{lca}(b,c)$ 的路径。

路径长度即为 $\operatorname{dep}a-\operatorname{dep}\operatorname{lca}(b,c)$。

[求 lca](https://www.luogu.com.cn/problem/P3379)

把板子套一下就可以啦。

~~可是lca是黄题~~

稍微注意的地方：

- 倍增求 lca 的话，预处理出 $\log$ 值数组会快很多。

- ~~这道题怎么可能是紫的~~



~~高清无码~~的代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+233;
struct Edge{int to,nxt;}e[2*maxn];
struct Point{int dep,fa[20];}v[maxn];
int n,m,x,y,z,cnt,head[maxn],lg[maxn];
void add(int i,int j){
	e[++cnt].to=j;
	e[cnt].nxt=head[i];
	head[i]=cnt;
}
void dfs(int u,int fa){
	v[u].fa[0]=fa,v[u].dep=v[fa].dep+1;
    
	for(int i=1;(1<<i)<v[u].dep;i++)
		v[u].fa[i]=v[v[u].fa[i-1]].fa[i-1];
    
	for(int i=head[u];i!=-1;i=e[i].nxt)
		if(e[i].to!=fa)
			dfs(e[i].to,u);
}
int lca(int x,int y){
	if(v[x].dep<v[y].dep)
		swap(x,y);
    
	while(v[x].dep!=v[y].dep)
		x=v[x].fa[lg[v[x].dep-v[y].dep]];
    
	for(int i=lg[v[x].dep-1];i>=0;i--)
		if(v[x].fa[i]!=v[y].fa[i])
			x=v[x].fa[i],y=v[y].fa[i];
    
	return x==y?x:v[x].fa[0];
}
int solve(){
	int i=lca(x,y),j=lca(x,z),k=lca(y,z);
    
	int res1=v[z].dep-max(v[j].dep,v[k].dep);
	if(j==k)res1+=(v[i].dep-v[k].dep);
		
	int res2=v[y].dep-max(v[i].dep,v[k].dep);
	if(k==i)res2+=(v[j].dep-v[i].dep);
		
	int res3=v[x].dep-max(v[j].dep,v[i].dep);
	if(i==j)res3+=(v[k].dep-v[j].dep);
    
	return max(res1,max(res2,res3))+1;
}
int main(){
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	for(int i=2;i<=n;i++){
		cin>>x;
		add(x,i);
		add(i,x);
	}
	lg[0]=-1;
		for(int i=1;i<=n;i++)
			lg[i]=lg[i/2]+1;
	v[0].dep=0;
	dfs(1,0);
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		cout<<solve()<<endl;
	}
	return 0;
}
```


---

## 作者：泠小毒 (赞：2)

# Misha, Grisha and Underground
有一棵n个节点的树，一共q次询问

每次询问给定3个点，求两条起点终点在这三个点上且不完全重合的路径的最多公共节点数
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190512/)
## 解法
lca板子题，求出三个点的lca之后，枚举每一个点作为公共点的可能性，推一下式子，公共节点有两种情况：(公共点为a，其他两点为b、c，i=lca(a,b)，j=lca(a,c)，k=lca(b,c))

1、min(a->i,a->j)产生一段贡献

2、如果i=j，k->i产生一段贡献

至于贡献的算法，就是深度的差
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p{int to,next;}a[200010];
struct point{int dep,fa[20];}po[100010];
int n,m,head[100010],x,y,z,l=0,lg[100010];
void add(int i,int j){a[++l].to=j,a[l].next=head[i],head[i]=l;}
void dfs(int u,int f)
{
    po[u].fa[0]=f,po[u].dep=po[f].dep+1;
    for(int i=1;(1<<i)<po[u].dep;i++)po[u].fa[i]=po[po[u].fa[i-1]].fa[i-1];
    for(int i=head[u];i!=-1;i=a[i].next)if(a[i].to!=f)dfs(a[i].to,u);
}
int f(int xx,int yy)
{
    if(po[xx].dep<po[yy].dep)swap(xx,yy);
    while(po[xx].dep!=po[yy].dep)xx=po[xx].fa[lg[po[xx].dep-po[yy].dep]];
    for(int i=lg[po[xx].dep-1];i>=0;i--)if(po[xx].fa[i]!=po[yy].fa[i])xx=po[xx].fa[i],yy=po[yy].fa[i];
    return xx==yy?xx:po[xx].fa[0];
}
int calc()
{
	int i=f(x,y),j=f(x,z),k=f(y,z),ans=0;
	ans=max(ans,po[z].dep-max(po[j].dep,po[k].dep)+(j==k?po[i].dep-po[j].dep:0));
	ans=max(ans,po[y].dep-max(po[i].dep,po[k].dep)+(i==k?po[j].dep-po[i].dep:0));
	ans=max(ans,po[x].dep-max(po[j].dep,po[i].dep)+(j==i?po[k].dep-po[j].dep:0));
	return ans+1;
}
int main()
{
    memset(head,-1,sizeof(head)),scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)scanf("%d",&x),add(x,i),add(i,x),lg[i]=log2(i);
    lg[1]=log2(1),po[0].dep=0,dfs(1,0);
    for(int i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),printf("%d\n",calc());
}
```

---

## 作者：jiangxinyang2012 (赞：2)

我们设 $x$ 为起点，$z$ 为终点，$y$ 为中间的点。

枚举哪个点作为 $y$，那么公共节点数就是 $\frac{\operatorname{dis}(x,y)+\operatorname{dis}(y,z)-\operatorname{dis}(x,z)+1}2$，其中 $\operatorname{dis}(x,y)$ 表示树上两点间的距离，用 LCA 求解。
当然也可以分类讨论 $a,b,c$ 的位置关系，不过比较麻烦。

---

## 作者：chenyilai (赞：1)

前置知识：[LCA](https://www.luogu.com.cn/problem/P3379)。

## 思路

画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hk3igeyb.png)

$2$ 个路径，三个点，必定有 $1$ 个点是重复的（红色的 $6$）。我们可以分类讨论一下哪个点是重复的，最后取三种答案中的最大值即可。假设这个点为 $a$，另两个点为 $b,c$。

首先，两条路径会从 $a$ 开始向上，后向下（也有可能只向上或只向下，但不影响），中间“转向”的拐点分别是 $\operatorname{lca}(a,b)$ 和 $\operatorname{lca}(a,c)$。向上走的共同点(节点 $2$)的深度为 $\max(dep_{\operatorname{lca}(a,b)}
,dep_{\operatorname{lca}(a,c)})$。向下走的部分可能有共同点（比如深蓝和浅蓝的路径），也有可能没有（比如说蓝色和红色）。向下走的部分在 $\operatorname{lca}(b,c)$ 处分离。如果 $dep_{\operatorname{lca}(c,b)}
\leq \max(dep_{\operatorname{lca}(a,b)}
,dep_{\operatorname{lca}(a,c)})$，说明两条路径没有向下走的共同部分，为 $0$。

## CODE：

```cpp
int n,_,a,b,c,fa[N][20],tot,edge[N<<1],head[N],nxt[N<<1],dep[N];
void add(int x,int y){edge[++tot]=y,nxt[tot]=head[x],head[x]=tot;return;}
void dfs(int x){
    dep[x]=dep[fa[x][0]]+1;
    for(int i=1;i<=19;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int i=head[x];i;i=nxt[i])dfs(edge[i]);
    return;
}
int lca(int x,int y){/*为节省空间略去*/}
int solve(int a,int b,int c){
    return dep[a]-max(dep[lca(a,b)],dep[lca(a,c)])+1+max(dep[lca(b,c)]-max(dep[lca(a,b)],dep[lca(a,c)]),0);
}
int main(){
    scanf("%d%d",&n,&_);
    for(int i=2;i<=n;i++)scanf("%d",fa[i]),add(fa[i][0],i);
    dfs(1);
    while(_--)scanf("%d%d%d",&a,&b,&c),printf("%d\n",max(solve(a,b,c),max(solve(b,a,c),solve(c,a,b))));
    return 0;
}
```

---

## 作者：Fairicle (赞：1)

提供了一种分类讨论之后得到的通解，不用在代码里分类讨论了。

首先我们知道三个点两两求 LCA，至多有两个不同的LCA。板子题[P4281](https://www.luogu.com.cn/problem/P4281).

如果LCA全相同，那么答案就是三个点到LCA的距离取最大值，这个画个图很好理解。

如果有两个不同LCA，那么答案就是三个点到**深度更大**的那个LCA的距离取最大值。

感性理解就是，两个点必然要在那个LCA交汇然后一起走向另一个点，要证明的话，分类讨论也是很容易的。

所以取深度最深的那个 LCA 来计算答案就行了。

code：

```cpp
#define N 100010
#define ri register int
int n,q,x,y,head[N],wl,dep[N],f[N][18],a,b,c;
struct node{
    int nxt,to;
}star[N<<1];
inline void add(int from,int to){
    wl++;
    star[wl].to=to;
    star[wl].nxt=head[from];
    head[from]=wl;
}
inline void dfs(int x,int fa){
    dep[x]=dep[fa]+1;f[x][0]=fa;
    for(ri j=1;j<=17;++j) f[x][j]=f[f[x][j-1]][j-1];
    for(ri i=head[x];i;i=star[i].nxt){
        int u=star[i].to;if(u==fa) continue;
        dfs(u,x);
    }
}
inline int get_lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    int t=dep[x]-dep[y];
    for(ri i=0;i<=17;++i) if(t&(1<<i)) x=f[x][i];if(x==y) return x;
    for(ri i=17;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
inline int get_dis(int x,int y){return dep[x]+dep[y]-2*dep[get_lca(x,y)];}
int main(){
    cin>>n>>q;
    for(ri i=2;i<=n;++i) cin>>x,add(x,i),add(i,x);
    dfs(1,0);
    while(q--){
        cin>>a>>b>>c;
        int lca1=get_lca(a,b),lca2=get_lca(b,c),lca3=get_lca(a,c),tar;
        if(lca1==lca2){
            if(dep[lca1]<dep[lca3]) tar=lca3;
            else tar=lca1;
        }
        else{
            if(dep[lca1]<dep[lca2]) tar=lca2;
            else tar=lca1;
        }
        cout<<max(get_dis(tar,a),max(get_dis(tar,b),get_dis(tar,c)))+1<<endl;//求经过点数，所以+1
    }
    return 0;
}
```


---

## 作者：duanyll (赞：1)

简单LCA求距离，令a为汇合点，那么答案就是`(dis(a,b) + dis(a,c) - dis(b,c)) / 2 + 1`，dis用lca求出，枚举a就好。

当然也可以一一讨论abc的位置关系，不过容易出错。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

class LFS {
   public:
    LFS() {
        memset(head, -1, sizeof head);
        ecnt = 0;
        n = 0;
    }
    LFS(int N) {
        memset(head, -1, sizeof head);
        ecnt = 0;
        n = N;
    }
    void adde(int from, int to, int w) {
        e[ecnt].to = to;
        e[ecnt].w = w;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }
    void addde(int a, int b, int w) {
        adde(a, b, w);
        adde(b, a, w);
    }

   protected:
    struct Edge {
        int to, next, w;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt;
    int n;

   private:
    virtual void dfs(int u, int fa) {
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != fa) {
                dfs(v, u);
            }
        }
    }
};

class LCA : public LFS{
   public:
   	int dep[MAXN];
    LCA(int n) : LFS(n) {
        memset(dep, -1, sizeof dep);
    }
    void pre(int rt = 1) { dfs(rt, 1, 0); }
    int querylca(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        int h = dep[b] - dep[a];
        for (int i = 20; i >= 0; i--) {
            if(h & (1 << i)) {
				b = f[b][i];
			}
        }
        if (a == b) return a;
        for (int i = 20; i >= 0; i--) {
            if (f[a][i] == f[b][i]) continue;
            a = f[a][i];
            b = f[b][i];
        }
        return f[a][0];
    }
    
    int querydis(int a,int b){
    	int lca = querylca(a,b);
    	return dep[a] + dep[b] - dep[lca]*2;
    }

   protected:
    int f[MAXN][22];

   private:
    void dfs(int u, int d, int fa) {
        dep[u] = d;
        f[u][0] = fa;
        for (int i = 1; i < 21; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dep[v] == -1) {
                dfs(v, d + 1, u);
            }
        }
    }
};

#include <cctype>
#include <cstdio>

inline int read() {
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        X = (X << 3) + (X << 1) + (ch ^ 48);
        ch = getchar();
    }
    return w ? -X : X;
}

int solve(LCA* tree,int a,int b,int c){
	int disab = tree->querydis(a,b);
	int disac = tree->querydis(a,c);
	int disbc = tree->querydis(b,c);
	return (disab + disac - disbc) / 2 + 1;
}

int main(){
	int n,q;
	cin >> n >> q;
	LCA* tree = new LCA(n);
	for(int i = 2;i<=n;i++){
		int a;
		cin >> a;
		tree->addde(i,a,1);
	}
	tree->pre();
	for(int i = 1;i<=q;i++){
		int a,b,c;
		cin >> a >> b >> c;
		int ans = 0;
		ans = max(solve(tree,a,b,c),max(solve(tree,b,a,c),solve(tree,c,a,b)));
		cout << ans << endl;
	}
}
```

---

## 作者：Laisira (赞：1)

## 提供一种 12 倍常数的做法
### 题目大意
给出一棵 $n$ 个节点的树，$q$ 次询问每次给出三个点，问选择两点使得他们到另一点的公共路程最大。

### 思路
先考虑如果我们已经确定选的两个点 $x,y$ 该如何求到 $z$ 公共路径长度。很容易发现，我们要求的其实就是 $x$ 到 $z$ 的距离加上 $y$ 到 $z$ 的距离，再减去 $x$ 到 $y$ 的距离加一除以二。显然可以用树链剖分简单维护一下，选择的事直接枚举。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 600001 
using namespace std;
namespace IO {
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch() {
		return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;
	}
	template<typename T>
	void read(T &x) {
		char ch=getch();
		int fl=1;
		x=0;
		while(ch>'9'||ch<'0') {
			if(ch=='-')fl=-1;
			ch=getch();
		}
		while(ch<='9'&&ch>='0') {
			x=x*10+ch-48;
			ch=getch();
		}
		x*=fl;
	}
	template<typename T,typename ...Args>
	void read(T &x,Args& ...args) {
		read(x);
		read(args...);
	}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {
		if(p3-obuf<(1<<21))*p3++=ch;
		else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
	}
	char ch[100];
	template<typename T>
	void write(T x) {
		if(!x)return putch('0');
		if(x<0)putch('-'),x*=-1;
		int top=0;
		while(x)ch[++top]=x%10+48,x/=10;
		while(top)putch(ch[top]),top--;
	}
	template<typename T,typename ...Args>
	void write(T x,Args ...args) {
		write(x);
		write(args...);
	}
	void flush() {
		fwrite(obuf,p3-obuf,1,stdout);
	}
}
using namespace IO;
int top[Maxn],fa[Maxn],son[Maxn],sz[Maxn],dep[Maxn];
vector<int> q[Maxn];
void dfs1(int x,int fs)
{
	fa[x]=fs;
	sz[x]=1;
	dep[x]=dep[fs]+1;
	for(int u:q[x])
	{
		if(u==fs)continue;
		dfs1(u,x);
		if(sz[son[x]]<sz[u])
			son[x]=u;
		sz[x]+=sz[u];
	}
}
void dfs2(int x,int tp)
{
	top[x]=tp;
	if(son[x])dfs2(son[x],tp);
	for(int u:q[x])
	{
		if(u==fa[x]||u==son[x])
			continue;
		dfs2(u,u);
	}
}
int LCA(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
			swap(u,v);
		v=fa[top[v]];
	}
	return dep[u]<dep[v]?u:v;
}
signed main()
{
	//freopen("tree.in","r",stdin);
	//freopen("tree.out","w",stdout);
	int n,t;
	read(n,t);
	for(int i=1;i<n;i++)
	{
		int u;
		read(u);
		q[u].push_back(i+1);
		q[i+1].push_back(u);
	}
	dfs1(1,1);
	dfs2(1,1);
	while(t--)
	{
		int u,v,w;
		read(u,v,w);
		int ans=0,lca1,lca2,lca3,len1,len2,len3;
		lca1=LCA(u,v);
		lca2=LCA(u,w);
		lca3=LCA(w,v);
		len1=dep[u]+dep[v]-dep[lca1]*2+1;//u-v 
		len2=dep[u]+dep[w]-dep[lca2]*2+1;//u-w
		len3=dep[v]+dep[w]-dep[lca3]*2+1;//v-w
		ans=max(ans,(len2+len3-(dep[u]-dep[lca1]+dep[v]-dep[lca1]))/2);//w
		ans=max(ans,(len1+len3-(dep[u]-dep[lca2]+dep[w]-dep[lca2]))/2);//v
		ans=max(ans,(len1+len2-(dep[v]-dep[lca3]+dep[w]-dep[lca3]))/2);//u
		write(ans);putch('\n');
	}flush();
	return 0;
 } 
```

---

## 作者：f_hxr_ (赞：0)

给定一颗树和若干询问，每次给出 $3$ 个点。选择一个点作为终点，剩下两点作为起点。我们想这两个点**分别**到终点的路径的**重合部分的结点点数**最大。求最大能是多少。

### 分析

~~啸内模拟嗮不仅出圆题，还卡倍增 LCA……~~

很自然地想到，依次枚举三个点作为终点，然后对其求出路径的重合部分，最后求最大值即可。

问题转化成如何求这个公共部分。

不幸的是，由于有 $3$ 个点，在树上的情况特别复杂，包括但不限于三点共线，共 LCA，终点在路径上等鸡肋的情况。此时我们有两种选择：

+ 暴力大分讨。

+ 寻找其他比分讨强的做法。

这篇题解讲的是第二种。~~因为我考场上死磕大分讨导致挂大分。~~

考虑如下容斥：

![](https://cdn.luogu.com.cn/upload/image_hosting/kazw80h4.png)

如图，我们将结点 A 到结点 C 的距离，加上结点 B 到结点 C 的距离，减去结点 A 到结点 B 的距离，就得到了公共部分长度的的两倍，只是还差一个结点。

将这个结点补上，再除以 $2$，就可以了。

幸运的是，这种方法在**任何情况**下都适用。

直接计算即可。这里用到了树链剖分求 LCA。

上 [AC](https://www.luogu.com.cn/record/154575969) 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch()
	{return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>
	void read(T &x) {
		char ch=getch();int fl=1;x=0;
		while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}
		while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;
	}
	template<typename T,typename ...Args>
	void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch){
		if(p3-obuf<(1<<21))*p3++=ch;
		else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
	}
	char ch[100];
	template<typename T>
	void write(T x){
		if(!x)return putch('0');
		if(x<0)putch('-'),x*=-1;
		int top=0;
		while(x)ch[++top]=x%10+48,x/=10;
		while(top)putch(ch[top]),top--;
	}
	template<typename T,typename ...Args>
	void write(T x,Args ...args){write(x);write(args...);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int maxn=500005;
int N,Q;
int head[maxn<<1],nxt[maxn<<1],to[maxn<<1],cnt_edge;
int SZ[maxn],dep[maxn],Hd[maxn],Hson[maxn],fa[maxn];
void AddEdge(int u,int v)
{nxt[++cnt_edge]=head[u];to[cnt_edge]=v;head[u]=cnt_edge;}
void dfs1(int u,int f){
	SZ[u]=1;fa[u]=f;dep[u]=dep[f]+1;
	for(int i=head[u];i;i=nxt[i]){
		if(to[i]==f)continue;
		dfs1(to[i],u);SZ[u]+=SZ[to[i]];
		if(SZ[to[i]]>SZ[Hson[u]])Hson[u]=to[i];
	}
}
void dfs2(int u,int top){
	Hd[u]=top;
	if(!Hson[u])return;dfs2(Hson[u],top);
	for(int i=head[u];i;i=nxt[i]){
		if(to[i]==fa[u]||to[i]==Hson[u])continue;
		dfs2(to[i],to[i]);
	}
}
int LCA(int u,int v){
	while(Hd[u]!=Hd[v]){if(dep[Hd[u]]>dep[Hd[v]])swap(u,v);v=fa[Hd[v]];}
	return dep[u]>dep[v]?v:u;
}
int dist(int u,int v){int lca=LCA(u,v);return dep[u]+dep[v]-dep[lca]-dep[fa[lca]];}
int solve(int end,int sa,int sb){return(dist(sa,end)+dist(sb,end)-dist(sa,sb)+1)>>1;} 
int main(){
	read(N,Q);  
	for(int i=2;i<=N;i++){int t;read(t);AddEdge(i,t);AddEdge(t,i);}
	dfs1(1,0);dfs2(1,1);
	while(Q--){
		int __zaa__,Adchory,__Chx__,ans=-1;
		read(__zaa__,Adchory,__Chx__);
		if(__zaa__==Adchory&&Adchory==__Chx__){putch('1');putch('\n');continue;}
		if(__zaa__==Adchory){write(dist(Adchory,__Chx__));putch('\n');continue;}
		if(__zaa__==__Chx__){write(dist(__zaa__,Adchory));putch('\n');continue;}
		if(Adchory==__Chx__){write(dist(__zaa__,__Chx__));putch('\n');continue;}
		ans=max(ans,solve(__zaa__,__Chx__,Adchory));
		ans=max(ans,solve(Adchory,__zaa__,__Chx__));
		ans=max(ans,solve(__Chx__,Adchory,__zaa__));
		write(ans);putch('\n');
	}
	flush();
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

$^*1900$ 的紫题……不管怎么样这题都应该蓝吧。

题目大意：给定一棵树和 $q$ 组询问，每组询问给出三个点 $a,b,c$，你可以任意重排 $a,b,c$，使得 $a \to c$ 的路径和 $b \to c$ 的路径的交集的点数最大。

因为只有三个点，我们可以暴力重排计算答案，问题转化为对于确定的 $a,b,c$ 计算答案。好像有很多巧妙做法，这里给出一种理解简单的分类讨论做法：

- 情况一：$a,b$ 都在 $c$ 的子树内。

此时答案显然为 $dep_c - dep_{\operatorname{lca}(a,b)}+1$。

- 情况二：$a,b$ 一个在 $c$ 的子树内，另一个不在。

此时答案显然为 $1$。

- 情况三：$a,b$ 都在 $c$ 的子树外。

这种情况还需要继续分类：

1. $\operatorname{lca}(a,c) = \operatorname{lca}(b,c)$。

画图理解一下，发现这种情况 $a,b$ 在 $c$ 子树外的同一棵子树，答案是 $\operatorname{dis}(c,\operatorname{lca}(a,b))$。

2. $\operatorname{lca}(a,c) \ne \operatorname{lca}(b,c)$。

此时两条路径一定只在 $1 \to c$ 的链上有交，那么答案应该是两个 $\operatorname{lca}$ 之间较深的和 $c$ 的距离。

到这里代码就很好写了，分析一下复杂度，瓶颈在求 $\operatorname{lca}$。这里采用朴素的倍增实现，时间复杂度 $\mathcal O((n+q) \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 01.11.2023 23:27:00
**/
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
vector<int> g[N];
int t,n,q,dfn[N],siz[N],dep[N],fa[N][22],tot,u,v,a,b,c;
void dfs(int u,int f){
    fa[u][0] = f,dep[u] = dep[f] + 1,siz[u] = 1,dfn[u] = ++tot;
    for(int i = 1;i <= 20;i ++) fa[u][i] = fa[fa[u][i-1]][i-1];
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}int lca(int u,int v){
    if(dep[u] < dep[v]) swap(u,v);
    while(dep[u] > dep[v]) u = fa[u][__lg(dep[u] - dep[v])];
    for(int i = 20;i >= 0;i --) if(fa[u][i] != fa[v][i]) u = fa[u][i],v = fa[v][i];
    return (u == v ? u : fa[u][0]);
}int calc(int u,int v,int x){
    bool f1 = (dfn[x] <= dfn[u] && dfn[u] <= dfn[x] + siz[x] - 1),
         f2 = (dfn[x] <= dfn[v] && dfn[v] <= dfn[x] + siz[x] - 1);
    if(f1 && f2) return dep[lca(u,v)] - dep[x] + 1;
    if(!f1 && f2 || f1 && !f2) return 1;
    int a = lca(x,u),b = lca(x,v),c = lca(u,v);
    if(a != b) return dep[x] - max(dep[a],dep[b]) + 1;
    return dep[c] + dep[x] - 2 * dep[lca(c,x)] + 1;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q;
    for(int i = 2;i <= n;i ++) cin >> u,g[i].push_back(u),g[u].push_back(i);
    for(dfs(1,0);q --;)
        cin >> a >> b >> c,cout << max(calc(a,b,c),max(calc(b,c,a),calc(c,a,b))) << "\n";
}
```

---

## 作者：迟暮天复明 (赞：0)

[题目传送门](https://codeforces.com/contest/832/problem/D)

[可能更好的阅读体验](https://www.cnblogs.com/1358id/p/14725896.html)
# Description
给定一棵树上的三个点 $a,b,c$，你要制定两条起点和终点都在这三个点中的路径，使得两条路径重叠的节点最多。
# Solution
~~感觉我的方法和大众不同，显然是珂以Hack的~~

考虑分类讨论，分三类：
1. $a$ 点在这两条路径的起止点中出现 $2$ 次。
1. $b$ 点在这两条路径的起止点中出现 $2$ 次。
1. $c$ 点在这两条路径的起止点中出现 $2$ 次。

下面只分析一类，即 $a$ 出现两次（其实都一样的）。
![](https://cdn.luogu.com.cn/upload/image_hosting/rl0g2fwv.png)
如图，这时 $\operatorname{LCA}(b,c)$ **不在** $a$ 到 $b$ 的简单路径上或$\operatorname{LCA}(b,c)$ **不在** $a$ 到 $c$ 的简单路径上。

这就是说， $\operatorname{LCA}(b,c)$ 不会被重复走过。

那么答案就是 $\operatorname{dis}(a,\operatorname{LCA}(a,c))$ 和 $\operatorname{dis}(a,\operatorname{LCA}(a,b))$ 中的最小值。（这个理解起来不难）
![](https://cdn.luogu.com.cn/upload/image_hosting/rb474e11.png)
如图，这时 $\operatorname{LCA}(b,c)$ **在** $a$ 到 $b$ 的简单路径上且$\operatorname{LCA}(b,c)$ **在** $a$ 到 $c$ 的简单路径上。
这就是说， $\operatorname{LCA}(b,c)$ 会被重复走过。

那么答案就是 $\operatorname{dis}(a,\operatorname{LCA}(b,c))$ 。（这个理解起来更不难）

然后这题就愉快地做完了。
# Code
```cpp
struct Edge {
  int to, nxt, val;
} e[1000010];
int n, q, cnt, head[1000010], fath[1000010][22], dep[1000010], s, lg[500010];
void add(int u, int v, int val) {
  e[++cnt].to = v;
  e[cnt].nxt = head[u];
  e[cnt].val = val;
  head[u] = cnt;
}
void dfs(int now, int fa) {
  dep[now] = dep[fa] + 1;
  fath[now][0] = fa;
  rep(i, 1, lg[dep[now]]) fath[now][i] = fath[fath[now][i - 1]][i - 1];
  for(int i = head[now]; i; i = e[i].nxt) if(e[i].to != fa) dfs(e[i].to, now);
}
int lca(int x, int y) {
  if(dep[x] < dep[y]) swap(x, y);
  while(dep[x] > dep[y]) x = fath[x][lg[dep[x] - dep[y]] - 1];
  if(x == y) return x;
  nrep(i, lg[dep[x]] - 1, 0) if(fath[x][i] != fath[y][i]) x = fath[x][i], y = fath[y][i];
  return fath[x][0];
}
int abs(int x) { return x < 0 ? -x : x; }
int dis(int x, int y) {
	int l = lca(x, y);
	return abs(dep[l] - dep[x]) + abs(dep[l] - dep[y]);
}
int check(int a, int b, int c) {
	if(dis(a, c) + dis(b, c) == dis(a, b)) return 1;
	return 0;
}
int solve(int a, int b, int c) {
  if(check(a, b, lca(b, c)) && check(a, c, lca(b, c))) return dis(a, lca(b, c));
  return min(dis(a, lca(a, b)), dis(a, lca(a, c))); 
}
int main() {
  read(n), read(q);
  rep(i, 2, n) {
    int x;
    read(x);
    add(x, i, 1), add(i, x, 1);
  }
  rep(i, 1, n) lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  dfs(1, 0);
  rep(i, 1, q) {
    int x, y, z;
    read(x), read(y), read(z);
    int ans = max(solve(x, y, z), max(solve(y, x, z), solve(z, x, y)));
    printf("%d\n", ans);
  }
  return 0;
}
```

---

