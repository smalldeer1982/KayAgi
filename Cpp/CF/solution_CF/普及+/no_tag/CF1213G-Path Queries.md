# Path Queries

## 题目描述

$\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 有一棵 $n$ 个点的树，每条边都带权。  

她会问你 $m$ 个问题，每次给你一个正整数 $q$，求最大权值不大于 $q$ 的简单路径数量。  

需要注意的是，对于一个点对 $(u,v)$ 只记一次，单独一个点不算路径。

接下来 $n-1$ 行，每行三个正整数 $u,v,w$，表示 $u,v$ 之间有一条权为 $w$ 的无向边。  
最后一行 $m$ 个正整数，表示询问。

## 说明/提示

$1\le n,m \le 2\times10^5$  
$1\le u,v \le n$  
$1\le w,q \le 2\times 10^5$

## 样例 #1

### 输入

```
7 5
1 2 1
3 2 3
2 4 1
4 5 2
5 7 4
3 6 2
5 2 3 4 1
```

### 输出

```
21 7 15 21 3 
```

## 样例 #2

### 输入

```
1 2
1 2
```

### 输出

```
0 0 
```

## 样例 #3

### 输入

```
3 3
1 2 1
2 3 2
1 3 2
```

### 输出

```
1 3 3 
```

# 题解

## 作者：lottle1212 (赞：23)

# [原题传送门](https://www.luogu.com.cn/problem/CF1213G)
## 题目描述

- 给出一棵 $n (1 \leq n \leq 2 \times 10 ^ 5)$ 个节点的带权树。
- 请求出最大边权不超过 $q (1 \leq q \leq 2 \times 10 ^ 5)$ 的简单路径数量。


## 分析
这是一道 **并查集** 好题。

首先，我们需要明白当第 $i$ 条边的边权作为简单路径中最大的边权时，此路径上的所有边权都应不大于此第 $i$ 条边的边权。由此，我们容易想到先将每一条边按边权升序排序，再从小到大枚举每一条边。做第 $i$ 条边时，设 $sz[u]$ 表示节点 $u$ 所在集合的大小，则它对权值 $w_i$ 的贡献为 $sz_{u_i} \times sz_{v_i}$，然后用 **并查集** 合并左右区块。时间复杂度 $O(n \log n)$。

题目中让我们求最大权值不大于 $q$ 的简单路径数量，于是，我们可以先用数组 $ans$ 保存对于每一个权值的数量，再对其进行前缀和，得出题目所求。时间复杂度为 $O(m)$。

总时间复杂度为 $O(n \log n + m)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mxn = 2e5;
const int N = mxn + 10;
ll ans[N]; int n, m, fx, fy, sz[N], f[N], x;
struct node { int u, v, w; } e[N];//邻接表
int get_fa(int x) { if(x == f[x]) return x; return f[x] = get_fa(f[x]); }//邻接表建边
bool cmp(node pre, node nxt) { return pre.w < nxt.w; }
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i < n; ++ i) cin >> e[i].u >> e[i].v >> e[i].w;
	sort(e + 1, e + n, cmp);//对边按权值进行升序排序
	for(int i = 1; i <= n; ++ i) f[i] = i, sz[i] = 1;//并查集初始化
	for(int i = 1; i < n; ++ i) {
		fx = get_fa(e[i].u), fy = get_fa(e[i].v);//求得祖先
		ans[e[i].w] += (ll) sz[fx] * sz[fy];//计算贡献
		f[fx] = fy, sz[fy] += sz[fx];//合并区块
	}
	for(int i = 1; i <= mxn; ++ i) ans[i] += ans[i - 1];//前缀求答案
	while(m --) cin >> x, cout << ans[x] << ' ';
	return 0;
}
```


---

## 作者：xuyiyang (赞：10)

#### 简化题意
给你一棵带边权树，每次询问路径最大值不大于 $q$ 的路径条数。

$ 1 \le n,m,w,q \le 2 \times 10^5$

#### 分析
CF 还是有很多思维题的。

本题就是并查集维护树上路径的经典应用。

先把边从小到大排序，枚举每一条边，统计当前边为最大值的路径条数，因为之前的边一定小于当前边，所以当前边的路径条数就是 $a \sim b$ 的过这条边联通的点对，可以用并查集来维护，那么对于当前边为最大值的贡献就是 $Size \text{ }a \times Size \text{ }b$，然后将两个联通块合并。
由于要求的是路径最大值小于 $q$ 的，所以用前缀和加起来就是答案。

时间复杂度： $\Theta(m \log n)$ 或 $\Theta ( \alpha(n) m)$，区别在于并查集的时间复杂度。

#### 代码
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;

typedef long long LL;

struct Edge
{
	int a, b, w;
	
	bool operator < (const Edge& t) const
	{
		return w < t.w; //边权从小到大排序来用并查集维护
	}
}e[N];

int n, m;
LL cnt[N]; //别忘记开 long long
int p[N], Size[N]; //祖先数组和联通块大小

int find(int x) //并查集基本操作
{
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i ++ )
		scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
	sort(e + 1, e + n); //排序
	
	for (int i = 1; i <= n; i ++ ) p[i] = i, Size[i] = 1;
        //初始化
	for (int i = 1; i < n; i ++ )
	{
		int pa = find(e[i].a), pb = find(e[i].b);
		cnt[e[i].w] += (LL)Size[pa] * Size[pb]; //见分析
		p[pa] = pb; //合并连通块
		Size[pb] += Size[pa];
	}
	
        //前缀和计算答案
	for (int i = 1; i < N; i ++ ) cnt[i] += cnt[i - 1];
	
	while (m -- )
	{
		int x;
		scanf("%d", &x);
		printf("%lld ", cnt[x]);
	}
	
	return 0;
}
```

---

## 作者：xcxcli (赞：8)

本题可以直接用点分治做，但较慢且代码复杂。

实际上本题可以将询问和边权从小到大排序，枚举第$i$个询问，每次连接边权不大于$l_i$的，每个连通块对于答案的贡献为(联通块大小-1)*联通块大小/2。

可以用带权并查集维护连通块,时间复杂度$O(n\log n+m\log m+n\alpha(n))$

```cpp
#include<stdio.h>
#include<algorithm>
#define ll long long
int rd(){
	int k=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k;
}
const int N=200001;
struct E{int u,v,w;}e[N];
struct P{int w,p;}p[N];
bool Cmp(E x,E y){return x.w<y.w;}
bool cmp(P x,P y){return x.w<y.w;}
int n,m,l,f[N],sz[N];ll ans[N],S;
int F(int x){
	while(x!=f[x])x=f[x]=f[f[x]];
	return x;
}
ll g(int x){return(ll)x*(x-1)>>1;}
void Merge(int x,int y){x=F(x),y=F(y),f[x]=y,S-=g(sz[x])+g(sz[y]),sz[y]+=sz[x],S+=g(sz[y]);}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<n;++i)e[i]=(E){rd(),rd(),rd()};
	for(int i=1;i<=n;++i)f[i]=i,sz[i]=1;
	for(int i=1;i<=m;++i)p[i]=(P){rd(),i};
	std::sort(p+1,p+m+1,cmp),std::sort(e+1,e+n,Cmp);
	for(int i=1,j=1;i<=m;++i){
		while(j<n&&e[j].w<=p[i].w)Merge(e[j].u,e[j].v),++j;
		ans[p[i].p]=S;
	}
	for(int i=1;i<=m;++i)printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：6)

一看这个题，统计树上满足某种条件的路径数量，首先想到大力点分治。

计算过程中，对于 $i\in[1,2\times10^5]$，记录路径 $\max$ **恰好**为 $i$ 的路径数量。

处理起来还是很简单的，把每个子树内找到的路径长度排个序，就很好算了。

时间复杂度 $\Theta(n\log^2 n+q)$，如果使用基数排序可以优化到 $\Theta(n\log n +q)$。

ps：使用并查集的做法是离线的，此做法是在线的。

代码： 
```cpp
#include<cstdio> 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define ll long long
#define N 200003
#define reg register
using namespace std;

struct edge{
    int v,w;
    edge(int v=0,int w=0):v(v),w(w){}
};

vector<edge> adj[N];
int son[N],size[N],dis[N],node[N];
ll ans[N];
bool vis[N];
int n,q,sum,rt,cnt;

inline void read(int &x);
void print(ll x);
void getrt(int u,int fa);
void divide(int u);
inline void solve(int u,int len,int w);
void getdis(int u,int fa);

int main(){
    int u,v,w;
    read(n),read(q);
    for(reg int i=1;i<n;++i){
        read(u),read(v),read(w);
        adj[u].push_back(edge(v,w));
        adj[v].push_back(edge(u,w));
    }
    sum = son[rt] = n;
    getrt(1,0);
    divide(rt);
    for(reg int i=2;i<N;++i) ans[i] += ans[i-1];
    while(q--){
        read(w);
        print(ans[w]); //O(1)回答询问
        putchar('\n');
    }
    return 0;
}

void getdis(int u,int fa){
    node[++cnt] = dis[u];
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(v==fa||vis[v]) continue;
        dis[v] = max(dis[u],adj[u][i].w); //路径上要取max的
        getdis(v,u);
    }
}

inline void solve(int u,int len,int w){
    dis[u] = len;
    cnt = 0;
    getdis(u,0);
    sort(node+1,node+1+cnt);
    for(reg int i=1;i<=cnt;++i){
        if(w==1) ans[node[i]] += i-1;
        else ans[node[i]] -= i-1;
    }
}

int getsiz(int u,int fa){
    int res = 1;
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(vis[v]||v==fa) continue;
        res += getsiz(v,u);
    }
    return res;
}

void divide(int u){
    vis[u] = true;
    solve(u,0,1);
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(vis[v]) continue;
        solve(v,adj[u][i].w,-1);
        sum = getsiz(v,u);
        rt = 0,son[rt] = n;
        getrt(v,u);
        divide(rt);
    }
}

void getrt(int u,int fa){
    size[u] = 1;
    son[u] = 0; //非常重要的一行
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i].v;
        if(vis[v]||v==fa) continue;
        getrt(v,u);
        size[u] += size[v];
        son[u] = max(son[u],size[v]);
    }
    son[u] = max(son[u],sum-size[u]);
    if(son[u]<son[rt]) rt = u;
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(ll x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
```


---

## 作者：ssSSSss_sunhaojia (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/CF1213G)
# 题目大意：
给定一棵 $n$ 个节点树，有 $m$ 个询问，对于每一个询问，输出最大权值不大于 $q$ 的简单路径数量。
# 解题思路：
读完题目，我们可以发现当一条简单路径符合要求时，在它里面的所有路径也都会是符合要求的。

根据这一特点，我们考虑用并查集做。首先将边按权值从小到大排序，然后枚举过来。对于每一条边，先我们找出它两个端点的祖先，然后给最大权值是这条边权值的简单路径数量加上两个端点的祖先的所在集合大小之积。原因是两个端点的祖先所在的集合各取一点后所连成的路径的最大权值一定是当前枚举到的这条边的权值。最后我们只需要合并两点的集合。

因为题目要求求出最大权值不大于 $q$ 的简单路径数量，而不是等于 $q$ 的数量，所以还得用一个前缀和。

# Code: 
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
LL n, m, fa[220000], sum[220000], x, y, w, fx, fy, res[220000], q[220000], ma; 
struct no {
	LL u, v, w; 
}e[220000];
bool cmp(no x, no y) {return x.w < y.w; }
in LL find(LL x) {return (x == fa[x] ? x : (fa[x] = find(fa[x]))); }
in void merge(LL x, LL y) {
	LL fx = find(x), fy = find(y); 
	fa[fx] = fy; sum[fy] += sum[fx]; sum[fx] = 0; 
}
int main(){
	IOS;
	cin >> n >> m; 
	for(re int i = 1; i < n; i ++) cin >> e[i].u >> e[i].v >> e[i].w; 
	sort(e + 1, e + n, cmp); //排序
	for(re int i = 1; i <= n; i ++) fa[i] = i, sum[i] = 1; //初始化
	for(re int i = 1; i < n; i ++) { //枚举每一条边
		x = e[i].u; y = e[i].v; w = e[i].w; 
		fx = find(x); fy = find(y); //找祖先
		res[w] += sum[fx] * sum[fy]; //增加数量
		merge(x, y);  //合并两点
	} 
	for(re int i = 1; i <= m; i ++) cin >> q[i], ma = max(ma, q[i]); 
	for(re int i = 1; i <= ma; i ++) res[i] += res[i - 1]; //前缀和
	for(re int i = 1; i <= m; i ++) cout << res[q[i]] << " "; 
	return 0;
}
```

---

## 作者：Vanilla_chan (赞：2)

## Problem

给一棵$n$点边带权的树，有$m$个询问，每次询问树上有多少最大权值不大于$q$的简单路径。单独一个点不算路径。

$1≤n,m≤2\times10^5$

$1\le u,v\le n$

$1\le w,q \le 2\times 10^5$

## Solution

第一眼是一个裸的点分治。

将所有询问离线并排序。对于每一个询问$q$，都跑一遍点分治，这样的时间复杂度是$O(nm\log n)$，完全过不去。

发现权值$w,q\le 2\times 10^5$，这里是一个重要的突破口。

不如只跑一遍点分治但是用一个桶来统计**最大权值等于$x$的路径的数量**。

最后求一个前缀和即可，注意排除路径长度为$0$的情况即可。

时间复杂度$O(n\log n)$，空间复杂度$O(n)$。

---

但是这里给出一种更简单但是思维难度更高（？）的算法。

先将所有操作离线。类比Kruskal算法，将所有的边按边权排序并用并查集维护一个连通块大小。假如有一个连通块的大小是$size$，那么这个连通块中就有$\dfrac {size\times(size-1)}{2}$条简单路径。

那么我们按照排好序的询问从小到大加边，加完所有边权小于当前询问的$q$的边。此时，
$$
ans=\sum \dfrac {size\times(size-1)}{2}
$$
使用并查集动态维护这个$ans$即可。

这是离线做法。仿照上面的点分治，由于权值范围小的可怜，我们只需要把所有的点权都当作一个询问，就变成所谓的**在线做法**了。

**注意答案是$n^2$级别的，需要开$\text{long long}$。**

## Code

### 离线

```c++
/**************************************************************
 * Problem: CF1213G Path Queries-bcj-no-online
 * Author: Vanilla_chan
 * Date: 20210309
**************************************************************/
//预编译部分已略去
#define N 200010
struct Ask
{
	int id,q;
	bool operator<(const Ask& z)const
	{
		return q<z.q;
	}
}ask[N];
int f[N],sze[N];
LL S;
int getf(int x)
{
	if(f[x]==x) return x;
	return f[x]=getf(f[x]);
}
LL calc(LL x)
{
	return x*(x-1)/2;
}
void merge(int x,int y)
{
	x=getf(x);
	y=getf(y);
	if(x==y) return;
	S-=calc(sze[x])+calc(sze[y]);
	if(sze[x]<sze[y])
	{
		f[x]=y;
		sze[y]+=sze[x];
		sze[x]=0;
	}
	else
	{
		f[y]=x;
		sze[x]+=sze[y];
		sze[y]=0;
	}
	S+=calc(sze[f[x]]);
	
}
int n,m;
struct edge
{
	int x,y,z;
	bool operator<(const edge& b)const
	{
		return z<b.z;
	}
}e[N];
LL ans[N];
int main()
{
	n=read();
	m=read();
	for(int i=1;i<n;i++)
	{
		e[i].x=read();
		e[i].y=read();
		e[i].z=read();
	}
	sort(e+1,e+n);
	for(int i=1;i<=m;i++)
	{
		ask[i].q=read();
		ask[i].id=i;
	}
	sort(ask+1,ask+m+1);
	for(int i=1;i<=n;i++) f[i]=i,sze[i]=1;
	int top=1;
	for(int i=1;i<=m;i++)//对于每一个询问
	{
		while(top<n&&e[top].z<=ask[i].q) merge(e[top].x,e[top].y),top++;//一直加边直到不超过当前询问的q
		ans[ask[i].id]=S;//将答案放回去
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
	return 0;
}
```

### 在线

```c++
/**************************************************************
 * Problem: CF1213G Path Queries-bcj-online
 * Author: Vanilla_chan
 * Date: 20210309
**************************************************************/
//预编译部分已略去
#define N 200010
int f[N],sze[N];
LL S;
int getf(int x)
{
	if(f[x]==x) return x;
	return f[x]=getf(f[x]);
}
LL calc(LL x)
{
	return x*(x-1)/2;
}
void merge(int x,int y)
{
	x=getf(x);
	y=getf(y);
	if(x==y) return;
	S-=calc(sze[x])+calc(sze[y]);
	if(sze[x]<sze[y])
	{
		f[x]=y;
		sze[y]+=sze[x];
		sze[x]=0;
	}
	else
	{
		f[y]=x;
		sze[x]+=sze[y];
		sze[y]=0;
	}
	S+=calc(sze[f[x]]);
	
}
int n,m;
struct edge
{
	int x,y,z;
	bool operator<(const edge& b)const
	{
		return z<b.z;
	}
}e[N];
LL ans[N];
int main()
{
	n=read();
	m=read();
	for(int i=1;i<n;i++)
	{
		e[i].x=read();
		e[i].y=read();
		e[i].z=read();
	}
	sort(e+1,e+n);
	for(int i=1;i<=n;i++) f[i]=i,sze[i]=1;
	int top=1;
	for(int i=1;i<=200000;i++)
	{
		while(top<n&&e[top].z<=i) merge(e[top].x,e[top].y),top++;
		ans[i]=S;
	}
	while(m--)
	{
		write(ans[read()]); 
	}
	return 0;
}
```

## 说在后面

（还是那句话）若有任何问题，恳请管理员斧正，感激不尽！



---

## 作者：qiyue7 (赞：2)

并查集水题  按边从小到大的顺序合并联通块并计算所有可能的答案即可

AC代码：

```cpp
using namespace std;
const int N = 220000;
struct unionfind
{
	array<int, N> fa, rank;
	array<long long, N> Size;
	void init()
	{
		for (int i = 0; i < N; ++i)
			fa[i] = i;
		rank.fill(0);
		Size.fill(1);
	}
	void link(int x, int y)
	{
		if (rank[x] > rank[y])
			fa[y] = x, Size[x] += Size[y];
		else
		{
			fa[x] = y;
			if (rank[x] == rank[y])
				rank[y]++;
			Size[y] += Size[x];
		}
	}
	int find(int x)
	{
		if (fa[x] != x)
			fa[x] = find(fa[x]);
		return fa[x];
	}
	void union_(int x, int y)
	{
		link(find(x), find(y));
	}
};
unionfind un;
vector<pair<int, int> > edge[N];
long long ans[N];
int main()
{
	int u, v, w;
	int n, q;
	cin >> n>>q;
	un.init();
	long long cur_ans = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> u >> v >> w;
		edge[w].emplace_back(u, v);
	}
	for (int i = 0; i < N; ++i)
	{
		if (!edge[i].empty())
			for (auto &p : edge[i])
			{
				cur_ans += un.Size[un.find(p.first)] * un.Size[un.find(p.second)];
				un.union_(p.first, p.second);
			}
		ans[i] = cur_ans;
	}
	int k;
	while (q--)
	{
		cin >> k;
		cout << ans[k] << " ";
	}
	cout << endl;
	return 0;
}
```


---

## 作者：youngk (赞：2)

这道题考察的内容更多的是并查集，这道题我们不需要完全的建成树，只需要从最小的边开始缩点，这里可以用到并查集的知识，将两个一条边上的两个点u，v看作一个点x，并且这个新缩成的点x就是原本两个点所代表的个数的和num[x]=num[u]+num[v]，同时，缩掉这两个点可以为这条边所代表的权值w的答案增加ans[w]+=num[x]*num[y].

注意答案需要开long long

代码:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
const int MAXN = 200005;
long long a[MAXN], num[MAXN];
int n, m, fa[MAXN];
struct edge {
	int x, y, w;
	void read() {
		cin >> x >> y >> w;
	}
	bool operator < (const edge& rhs) const {
		return w > rhs.w;
	}
}e[MAXN];
int findfa(int x) {
	return fa[x] != x ? fa[x] = findfa(fa[x]) : x;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int mx = 0;
	for (int i = n - 2; i >= 0; i--) {
		e[i].read();
		mx = max(mx, e[i].w);
	}
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		num[i] = 1;
	}
	sort(e, e + n - 1);
	for (int i = n - 2; i >= 0; i--) {
		int p = e[i].w, x = findfa(e[i].x), y = findfa(e[i].y);
		long long add;
		add = num[x] * num[y];
		fa[x] = y;
		num[y] += num[x];
		a[p] += add;
	}
	for (int i = 1; i <= mx; i++)
		a[i] += a[i - 1];
	while (m--) {
		int q;
		cin >> q;
		if (q > mx) q = mx;
		cout << a[q] << ' ';
	}
}
```


---

## 作者：Bpds1110 (赞：1)

[$\mathcal{Link}$](https://www.luogu.com.cn/problem/CF1213G)
## $\mathcal{Describe}$:
> 给定一棵 $n$ 个节点的带权树，给出 $m$ 个询问，对于每个询问，求出最大边权不超过 $q$ 的简单路径的数量。

## $\mathcal{Solution}$:
#### 前置知识：
![](https://cdn.luogu.com.cn/upload/image_hosting/scxt8zzz.png)

这样一张图，发现经过 $(1,2)$ 这条边的方案总数为 $6 \times 2 = 12$ 条，因为每条终点为 $1$ 的路径，都可以选择每条起点为 $2$ 的路径，构成一种方案。
#### 正文：
我们考虑用并查集维护路径，先设每个点都不连通。$size_u$ 为目前 $u$ 所在的连通块的大小，初始 $size_u \gets 1$。我们先按边权由小到大将边排序，接着 $i$ 枚举 $n - 1$ 条遍，假设 $i$ 的边权为某一条路径的边权最大值，因为边按权由小到大排序，而且初始 $size_u = 1$，保证两边的边权小于 $w_i$，所以对最大边权为 $w_i$ 的贡献为 $size_{u_i} \times size_{v_i}$，接着连上 $(u_i,v_i)$ 的一条边，即用并查集合并两个区块，并且将当前连通块的大小变为它们的和，$size_u \gets size_u + size_v$。我们用 $ans_i$ 记录最大边权为 $i$ 的路径总数，题目中要求最大边权不超过 $q$，所以要对 $ans$ 数组进行前缀和操作。最后对于每次询问，输出 $ans_q$ 即可。

## $\mathcal{Code}$:
```cpp
#include <bits/stdc++.h>
#define int long long

const int max = 2e5 + 10;

struct edge
{
	int u, v, w;
}E[max];

bool operator < (const edge h, const edge t)
{
	return h.w < t.w;
}//按边权由小到大

int fa[max], ans[max], size[max];

int find(int now)
{
	return (fa[now] ^ now) ? (fa[now] = find(fa[now])) : now;//寻找祖先
}

signed main()
{
	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i < n; ++ i)
		std::cin >> E[i].u >> E[i].v >> E[i].w;
	std::sort(E + 1, E + n);
	for (int i = 1; i <= n; ++ i)
		size[i] = 1, fa[i] = i;

	for (int i = 1; i < n; ++ i)
	{
		int Fa_u = find(E[i].u), Fa_v = find(E[i].v);
		ans[E[i].w] += size[Fa_u] * size[Fa_v];//计算贡献
		size[Fa_u] += size[Fa_v];
		size[Fa_v] = 0;
		fa[Fa_v] = Fa_u;//合并区块
	}
	
	for (int i = 1; i <= 2e5; ++ i)
		ans[i] += ans[i - 1];
	
	while (m --> 0)
	{
		int q;
		std::cin >> q;
		std::cout << ans[q] << " ";
	}
	
	return 0;
}

```


---

## 作者：Strelitzia_ (赞：1)

这是目前题解区里还没有的 Kruskal 重构树做法。

------------
## 题目大意

给定一棵 $n$ 个节点的带边权的树，$m$ 次询，问给定 $q$ 问最大权值不大于 $q$ 的简单路径数量。

------------
## 思路

看到“问最大权值不大于 $q$ 的简单路径”，我们可以想到 Kruskal 重构树。

显然，对于每一个重构树上新建的节点 $i$，设其权值为 $v_i$，子树的大小（除去所有新建节点）为 $s_i$，父节点为 $f_i$，那么他对于权值大于等于 $v_i$ 的询问的贡献为 $\dfrac{s_i(s_i-1)}{2}$。

当然，如果我们在统计某个新建节点的贡献时也统计了其子节点的贡献就会算重。我们可以让第 $i$ 个点只对 $v_i\le q\le v_{f_i}-1$ 做出贡献，就可以保证答案正确了。

这个贡献如何维护？把所有询问看成数列，我们需要实现：区间加，以及所有区间加之后单点查询。显然，我们可以用差分实现，最后再做个前缀和就可以知道每个询问的答案了。

这个做法本质是离线的，不过也可以应对在线查询。总时间复杂度 $\mathcal{O}(n\log n)$，可以通过。代码如下：

```cpp
void dfs(int to, int fa) {
	sz[to] = (to <= n), f[to] = fa;
	for (int i = head[to]; i; i = e[i].nxt) if (e[i].to != fa) dfs(e[i].to, to), sz[to] += sz[e[i].to];
}

signed main() {

	n = idx = read(), m = read();
	for (int i = 1; i < n; i++) fe[i].to = read(), fe[i].nxt = read(), fe[i].val = read();
	for (int i = 1; i <= n; i++) blg[i] = i, blg[i + n] = i + n, fas[i].id = i;
	std::sort(fe + 1, fe + n, cmpe);
	for (int i = 1; i < n; i++) {
		int to = find(fe[i].to), nxt = find(fe[i].nxt);
		if (to == nxt) continue;
		fas[++idx].val = fe[i].val, blg[to] = blg[nxt] = idx;
		add_edge(idx, to), add_edge(to, idx), add_edge(idx, nxt), add_edge(nxt, idx);
	}
	dfs(idx, 0), std::sort(fas + n + 1, fas + idx + 1, cmpf);
	for (int i = n + 1; i <= idx; i++) {
		if (fas[f[i]].val == fas[i].val) continue;
		ans[fas[i].val] += sz[i] * (sz[i] - 1) / 2;
		if (f[i]) ans[fas[f[i]].val] -= sz[i] * (sz[i] - 1) / 2;
	}
	for (int i = 1; i < N; i++) ans[i] += ans[i - 1];
	while (m--) {
		int x = read();
		printf("%lld ", ans[x]);
	}
	return Strelitzia_;

}
```

---

## 作者：KSToki (赞：1)

题意翻译已经说得很清楚了，这里就不复述了。

从数据范围下手，复杂度应该是 $O(mlogn)$ 或 $O(m)$ 的。对于 $O(mlogn)$ 可以直接点分治，~~但由于我太菜不会~~，所以思考 $O(m)$，显然应该考虑预处理。将所有的边按边权排序，以最大边权为上限扫，用并查集合并，同时合并大小($siz$)即可。对每个 $q$，答案即为在任意联通块的两个点，可以在合并的时候直接处理掉。

注意当 $q$ 大于最大边权的时候需要特判（当然其实可以预处理直接到 $200000$），并且要开 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int flag=1;
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
		if(ch=='-')
			flag=-1;
	}
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
struct edge
{
	int x,y;
	int w;
	bool operator <(edge e2)
	{
		return w<e2.w;
	}
}e[200001];
int n,m,father[200001],siz[200001];
ll res[200001],ans[200001];
int find(int x)
{
	return x==father[x]?x:father[x]=find(father[x]);
}
inline ll c2(int x)
{
	return (ll)x*(x-1)/2;
}
int main()
{
	n=read();
	m=read();
	for(int i=1;i<n;++i)
	{
		e[i].x=read();
		e[i].y=read();
		e[i].w=read();
	}
	sort(e+1,e+n);
	for(int i=1;i<=n;++i)
	{
		father[i]=i;
		siz[i]=1;
	}
	int j=1;
	for(int i=1;i<=e[n-1].w;++i)
	{
		res[i]=res[i-1];
		while(e[j].w==i&&j<n)
		{
			int xx=find(e[j].x),yy=find(e[j].y);
			if(xx!=yy)
			{
				res[i]+=c2(siz[xx]+siz[yy])-c2(siz[xx])-c2(siz[yy]);
				siz[xx]+=siz[yy];
				father[yy]=xx;
			}
			++j;
		}
	}
	int a;
	for(int i=1;i<=m;++i)
	{
		a=read();
		if(a>=e[n-1].w)
			ans[i]=res[e[n-1].w];
		else
			ans[i]=res[a];
	}
	for(int i=1;i<=m;++i)
		printf("%lld ",ans[i]);
	return 0; 
}
```


---

## 作者：GalwayGirl (赞：1)

看到题面，大家应该首先想到的是点分治吧？？但是代码又长又不好理解，~~其实就是本蒟蒻不会。~~

## Solution
先考虑一下该怎么计算路径，一开始想的时候以为又要用什么高深算法，其实可以将计算路径转换一下，因为是树上的简单路径，所以不同的路径取决于不同的起点和终点，所以只要考虑乘法原理即可。

我们可以考虑离线算法，将询问和边权进行排序，然后将符合条件的边加入，这里可以使用并查集来维护连通块，根据上面所说，将两个连通块并起来的贡献就是两个连通块的节点个数相乘。

## Detail
两个连通块节点相乘时会溢出，要转成 long long，WA了四五次才发现，我真的是又蒟又蒻。

见此处代码。
```cpp
    for(int i=1;i<=q;i++){
        while(last<n&&edge[last].w<=ask[i].val){
            int r1=find(edge[last].u),r2=find(edge[last].v);
            if(r1!=r2){
                fa[r1]=r2;
                sum+=1ll*size[r2]*size[r1];
                size[r2]+=size[r1];
            }
            last++;
        }
        ans[ask[i].id]=sum;
    }
```
贴上完整代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int n,q,fa[N],size[N];
long long ans[N],sum;
struct xzh{
    int u,v,w;
}edge[2*N];
struct hh{
    int val,id;
}ask[N];
bool cmp(xzh x,xzh y){
    return x.w<y.w;
}
bool cmp1(hh x,hh y){
    return x.val<y.val;
}
int find(int x){
    if(fa[x]!=x)fa[x]=find(fa[x]);
    return fa[x];
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)size[i]=1,fa[i]=i;
    for(int i=1;i<n;i++)scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
    sort(edge+1,edge+n,cmp);
    for(int i=1;i<=q;i++)scanf("%d",&ask[i].val),ask[i].id=i;
    sort(ask+1,ask+1+q,cmp1);
    int last=1;
    for(int i=1;i<=q;i++){
        while(last<n&&edge[last].w<=ask[i].val){
            int r1=find(edge[last].u),r2=find(edge[last].v);
            if(r1!=r2){
                fa[r1]=r2;
                sum+=1ll*size[r2]*size[r1];
                size[r2]+=size[r1];
            }
            last++;
        }
        ans[ask[i].id]=sum;
    }
    for(int i=1;i<=q;i++)printf("%lld ",ans[i]);
    return 0;
}
```
看别人的题解都比我简洁，觉得我写的麻烦的也可以参考一下其他大佬的题解。

最后推荐一个类似的题：[P4185 [USACO18JAN]MooTube G](https://www.luogu.com.cn/problem/P4185)

---

