# Sergey and Subway

## 题目描述

Sergey Semyonovich is a mayor of a county city N and he used to spend his days and nights in thoughts of further improvements of Nkers' lives. Unfortunately for him, anything and everything has been done already, and there are no more possible improvements he can think of during the day (he now prefers to sleep at night). However, his assistants have found a solution and they now draw an imaginary city on a paper sheet and suggest the mayor can propose its improvements.

Right now he has a map of some imaginary city with $ n $ subway stations. Some stations are directly connected with tunnels in such a way that the whole map is a tree (assistants were short on time and enthusiasm). It means that there exists exactly one simple path between each pair of station. We call a path simple if it uses each tunnel no more than once.

One of Sergey Semyonovich's favorite quality objectives is the sum of all pairwise distances between every pair of stations. The distance between two stations is the minimum possible number of tunnels on a path between them.

Sergey Semyonovich decided to add new tunnels to the subway map. In particular, he connected any two stations $ u $ and $ v $ that were not connected with a direct tunnel but share a common neighbor, i.e. there exists such a station $ w $ that the original map has a tunnel between $ u $ and $ w $ and a tunnel between $ w $ and $ v $ . You are given a task to compute the sum of pairwise distances between all pairs of stations in the new map.

## 说明/提示

In the first sample, in the new map all pairs of stations share a direct connection, so the sum of distances is $ 6 $ .

In the second sample, the new map has a direct tunnel between all pairs of stations except for the pair $ (1, 4) $ . For these two stations the distance is $ 2 $ .

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
6
```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
```

### 输出

```
7
```

# 题解

## 作者：福州周圣力 (赞：14)

[更好的阅读体验](https://blog.csdn.net/fz_zsl/article/details/89035987)

**题目大意：**  
给出一棵树，每条边的长度为$1$，对于原图中每一对距离为$2$的点，连一条长度为$1$的边。  
求出$ans=\sum_{i=1}^n\sum_{j=i}^n\texttt{dist}(i,j)$的值。

---

考虑对于每一组的点对，其最短路一定是尽量走新增的边（即加边之前距离为$2$的点对之间的边），当到达距离目标点的长度为$1$时，直接走加边之前的边。这样的话，设在加边之前两个点的距离为$\texttt{dis}$，那么最终这两个点之间的距离就是（以下$\lceil\rceil$表示向上取整，$[]$表示当里面的表达式为真时为$1$，否则为$0$）: $\texttt{dist}(i,j)=\lceil\frac{\texttt{dis}}{2}\rceil=\frac{\texttt{dis}+[\texttt{dis}\bmod2==1]}{2}$。  
令$\texttt{d}(i,j)$表示加边前从$i$到$j$的路径长度，将上式带入题目中的式子，得到：$ans=\frac{\sum_{i=1}^n\sum_{j=i}^n(\texttt{d}(i,j)+[\texttt{d}(i,j)\bmod2==1])}{2}$，也就是原图上所有点对之间的距离加上长度为奇数的路径的个数的和除以$2$的结果。前者我们可以考虑每条边的边权对最终答案的贡献即可（即路径两端点集大小之积）。  
对于后者，我们考虑求路径长度的方法：令$\texttt{dep}$表示从根节点到当前节点的路径长度，那么$\texttt{dis}=\texttt{dep}_i+\texttt{dep}_j-2\times\texttt{dep}_{LCA(i,j)}$，其中$-2\times\texttt{dep}_{LCA(i,j)}$不会对路径长度的奇偶性产生影响，也就是说我们只需要统计$\texttt{dep}_i$与$\texttt{dep}_j$奇偶性不同的点对数量就可以得到答案，这部分可以在树形DP的时候顺便记录一下即可。

参考代码：（码风不喜勿喷，建议自行展开代码`0^_^0`）

```cpp
#include<cstdio>
#define ot e[i].to
struct edge{int to,next;}e[400005];int n,tot=0,last[200005],cnt[2],sz[200005];long long ans=0;
inline void adde(int u,int v) {e[++tot]=(edge){v,last[u]},last[u]=tot;return;}
inline void inse(int u,int v) {adde(u,v),adde(v,u);return;}
void dfs(int root,int fa,int dep) {++cnt[dep^=1],sz[root]=1;//记录下子树大小以及深度奇偶性
	for (register int i=last[root];i;i=e[i].next) if (ot^fa) dfs(ot,root,dep),sz[root]+=sz[ot];//更新子树大小
	return (void)(ans+=1LL*(n-sz[root])*sz[root]);//更新答案
}
int main() {int u,v;
	scanf("%d",&n);for (register int i=1;i<n;++i) scanf("%d%d",&u,&v),inse(u,v);
	dfs(1,0,0);return 0*printf("%lld",ans+1LL*cnt[0]*cnt[1]>>1);//计算答案
}
```

---

## 作者：_lcy_ (赞：11)

首先，我们可以考虑一个简化的问题  
>有一个树，要求求出每个点对 $(i,j)$ $(1 \leq i \leq j \leq N)$ 经过的边数和  

这个问题可以这样解  
我们考虑每一条边，这条边会把树分成两半  
我们维护子树大小 $size_{i}$ 就可以得到其中一半  
不妨设它是左边的，叫做 $left$  
这条边对答案贡献就是 $left \times (N-left)$  

然后我们回到原题  
我们可以知道，一个点对的距离是在原图中的距离除二再上取整  
我们可以把原距离分成两类  
- 偶数长度(这里可以直接除二)  
- 奇数长度(这里需要加一除二)  

所以我们只需要求出有几条奇数长度的边了  
这时，我们可以把树的深度求出来  
![tN6eW6.gif](https://s1.ax1x.com/2020/06/02/tN6eW6.gif)  
把奇数层的节点个数乘上偶数层的节点个数就是奇数长度的个数了  
那么为什么呢？  
把点对分成两类  
- 父子关系(如图中 $(2,5)$ )
- 没有关系(如图中 $(7,16)$ )

如果是父子关系的话那么一定一个点在奇数层一个在偶数层  
如果没有关系的话，那么上面的边(下图红边)的个数一定是二的倍数(以 $(7,16)$ 为例)  
![tNg3Gt.png](https://s1.ax1x.com/2020/06/02/tNg3Gt.png)
所以需要考虑的只有绿边,而绿边的个数正好是层数差，所以肯定也是一个奇数层一个偶数层  

所以最后的答案就是  
$$Ans=\frac{\text{简化问题的答案}+\text{奇数长度的边数}}{2}$$

**注意long long**

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;

int N;
const int MAX_N=200010,MAX_M=200010;
int head[MAX_N],to[MAX_M<<1],nxt[MAX_M<<1],tot;
long long cnt[2],depth[MAX_N],sze[MAX_N];
void add_edge(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
long long ans=0;
void dfs(int now,int fa){
	depth[now]=depth[fa]+1;
	cnt[depth[now]%2]++;
	sze[now]=1ll;
	for(int i=head[now];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],now);
		sze[now]+=sze[to[i]];
		ans+=sze[to[i]]*(N-sze[to[i]]);
	}
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<N;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,0);
	ans+=cnt[0]*cnt[1];
	printf("%lld\n",ans/2ll);
	return 0;
}
```





---

## 作者：_Lemon_ (赞：11)


[欢迎踩博客](https://www.cnblogs.com/Le-mon/p/9745627.html)


### Solution ###

本来看见是黑题有点怕，但仔细一想也没有那么难。

先处理出每个点的深度(dep)和子树大小(size)，我们把原树上的边称为老边，新建的边是新边。

首先因为隔了一个点有一条新边，假设新边跨过的点为 u ，那么这条新边产生的价值就是size[i]*(n-size[i])/2，也就是两边点对数量。那么老边会不会产生价值呢？如果原树上两点之间的距离为奇数，那么新图上肯定需要经过一条老边。所以答案还需要加上 (深度为奇的点数×深度为偶的点数)/2。

~~其实还是比较好写的~~

### coding ###
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct Tree
{
    int to,next;
}e[N*2];
int n,head[N],cnt,dep[N],size[N];
long long ans,num;
void add(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].next=head[x];
    head[x]=cnt;
}
void DFS(int x,int last)
{
    size[x]=1;
    for(int i=head[x];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==last) continue ;
        dep[v]=dep[x]+1;
        DFS(v,x);
        size[x]+=size[v];
    }
}
int main()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    DFS(1,0);
    for(int i=1;i<=n;i++)
    {
        ans+=size[i]*(long long)(n-size[i]);
        if(dep[i]%2==1) num++;
    }
    ans+=num*(long long)(n-num);
    cout<<ans/2;
    return 0;
}
```


---

## 作者：eee_hoho (赞：5)

说个和别的题解不一样的换根dp方法。

首先分析题目发现可以把长度为$2$的路径走成$1$步，所以我们考虑设$f_{u,0/1}$表示以$u$为根的子树，$u$到所有距离自己为偶数$/$奇数的儿子的答案和，$size_{u,0/1}$表示以$u$为根的子树，距离$u$为偶数$/$奇数的儿子个数，于是有转移方程：

$$\begin{cases}f_{u,0}=\sum_{v\in son(u)}f_{v,1}\\f_{u,1}=\sum_{v\in son(u)}f_{v,0}+size_{v,0}\\size_{u,0}=1+\sum_{v\in son(u)}size_{v,1}\\size_{u,1}=\sum_{v\in son(u)}size_{v,0}\end{cases}$$

具体来说就是从儿子和自己奇偶性相反的转移过来。

如果儿子是偶数，那么从$u$走到儿子需要多走一步；而如果儿子是奇数，那么儿子一定是走了一个长度为$1$的边，所以我们直接走长度为$2$的边，不会产生多的步数。

$size_u,0$里的$+1$是要算上自己。

然后我们再通过一遍换根可以算出来$g_{u,0/1}$表示以$u$为根的树，$u$到所有距离自己为偶数$/$奇数的儿子的答案和。

然后$ans$显然就是$\frac{\sum_{i=1}^ng_{i,1}+g_{i,0}}{2}$。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 2e5;
using namespace std;
int n,edge[N * 2 + 5],nxt[N * 2 + 5],head[N + 5],edge_cnt,size[N + 5][2],dep[N + 5],ss[N + 5][2];
long long f[N + 5][2],ans,g[N + 5][2];
void add_edge(int u,int v)
{
    edge[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}
void dfs1(int u,int fa)
{
    size[u][0] = 1;
    dep[u] = dep[fa] + 1;
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i];
        if (v == fa)
            continue;
        dfs1(v,u);
        f[u][0] += f[v][1];
        f[u][1] += f[v][0] + size[v][0];
        size[u][0] += size[v][1];
        size[u][1] += size[v][0];
    }
}
void dfs2(int u,int fa)
{
    g[u][0] = f[u][0];
    g[u][1] = f[u][1];
    ss[u][1] = size[u][1];
    ss[u][0] = size[u][0];
    if (fa)
    {
        g[u][0] += g[fa][1] - (f[u][0] + size[u][0]);
        g[u][1] += g[fa][0] - (f[u][1]) + ss[fa][0] - size[u][1];
        ss[u][0] += ss[fa][1] - size[u][0];
        ss[u][1] += ss[fa][0] - size[u][1];
    }
    ans += g[u][0] + g[u][1];
    for (int i = head[u];i;i = nxt[i])
    {
        int v = edge[i];
        if (v == fa)
            continue;
        dfs2(v,u);
    }
}
int main()
{
    scanf("%d",&n);
    int u,v;
    for (int i = 1;i < n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs1(1,0);
    dfs2(1,0);
    cout<<ans / 2<<endl;
    return 0;
}
```

---

## 作者：happy_zero (赞：3)

记现在树中 $i,j$ 的距离为 $dist(i,j)$，原来为 $dis(i,j)$，其实答案就是 $\sum_{i=1}^n\sum_{j=i+1}^ndist(i,j)=\sum_{i=1}^n\sum_{j=i+1}^n\lceil\frac{d_i+d_j-2\times d_{lca(i,j)}}{2}\rceil=\sum_{i=1}^n\sum_{j=i+1}^n\lceil\frac{d_i+d_j}{2}\rceil-d_{lca(i,j)}$，分别对每个点统计对答案的贡献。

先抛开向上取整，记 $i$ 作为了 $lca(x,y)$ $cnt_i$ 次每个点对答案的贡献分为两部分：$\lfloor\frac{d_i}{2}\rfloor$ 和 $d_i\times cnt_i$，其中后一部分的贡献还是可以分两种情况：$i$ 和其子树内一点（子树大小）和 $i$ 的子树中选不在同一子树的两点（$k$ 为 $i$ 的儿子，$\binom{\sum siz_{k}}{2}-\sum \binom{2}{siz_{k}}$），这个用一个 dfs 就能解决。

最后加上向上取整。前面统计的是下取整，简单思考一下发现 $d_i$ 和 $d_j$ 中有任意一个为奇数时答案会少 $1$，于是加上 $i,j$ 为一奇一偶或两奇的情况即可。

注意要开 long long！

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int d[N], siz[N], cnt[N];
vector <int> p[N]; 
inline int C(int k) {//从 k 个数中选两个数的方案数
	if (k == 0) return 0;
	return k * (k - 1) / 2;
}
void dfs(int k, int fa) {
	d[k] = d[fa] + 1, siz[k] = 1;
	for (auto i : p[k]) {
		if (i == fa) continue;
		dfs(i, k), siz[k] += siz[i];
		cnt[k] -= C(siz[i]);
	}
	cnt[k] += C(siz[k]);//注意这里要最后再加
}
signed main() {
	int n; cin >> n;
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, p[u].pb(v), p[v].pb(u);
	dfs(1, 0);
	int s1 = 0, s2 = 0;
	for (int i = 1; i <= n; i++) {//统计奇/偶深度的点各有多少个
		if (d[i] % 2 == 0) s1++;
		else s2++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += d[i] / 2 * (n - 1) - d[i] * cnt[i];//每个 d[i]/2 都需要加 n-1 次 
	cout << ans + s1 * s2 + s2 * (s2 - 1) / 2;
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1060E)  
[我的Blog](https://blog.csdn.net/Brian_Pan_/article/details/114385217)

两百年前看题解做过的一道题，自己还写了个题解，现在回来看感觉当时的做法极其不严谨。

设 $\operatorname{dis}(i,j)$ 表示 $i,j$ 的距离。  
我们可以发现，对于每一个点对 $(i,j)$：
- 如果原来 $\operatorname{dis}(i,j)$ 为偶数，那么加上新边后就变成了 $\frac{\operatorname{dis}(i,j)}{2}$。
- 如果原来 $\operatorname{dis}(i,j)$ 为奇数，那么加边后就变成了 $\frac{\operatorname{dis}(i,j)+1}{2}$。

那么，最终的答案就是 $\frac{\sum\limits_{1 \le i \le j \le n} \{ \operatorname{dis}(i,j)+(\operatorname{dis}(i,j) \mod 2) \}}{2}$。

设 $s_x$ 为 $x$ 的子树大小，$d_x$ 为 $x$ 的深度；$u,v$ 分别为深度为奇数和偶数的点个数。

那么答案就可以化简为 $\frac{\sum\limits_{1 \le i \le j \le n}\{s_x\cdot(n-s_x)\}+(u\times v)}{2}$。

总时间复杂度 $\mathcal O(n)$。

为了方便理解，本代码未开 `long long`。
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int Maxn=200000+20,inf=0x3f3f3f3f;
vector <int> e[Maxn];
int s[Maxn],d[Maxn];
int n,cnt,ans;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*w;
}
void dfs(int x,int fa)
{
    s[x]=1,d[x]=d[fa]+1;
    for(int i=0;i<e[x].size();++i)
    {
        int y=e[x][i];
        if(y==fa)continue;
        dfs(y,x);
        s[x]+=s[y];
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    n=read();
    for(int i=1;i<n;++i)
    {
        int x=read(),y=read();
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i)
    {
        ans+=(s[i]*(n-s[i]));
        if(d[i] & 1)cnt++;
    }
    ans+=(cnt*(n-cnt));
    ans>>=1; 
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：CarroT1212 (赞：2)

### 题目大意

给定一棵 $n$ 个点的树，然后给原树中每一对距离为 $2$ 的点都连一条边，得到一张新图。问新图中每对点的最短距离之和是多少。（$1 \le n \le 2\times 10^5$）

### 解法分析

首先有个非常重要的题意转化：设 $dis_{i,j}$ 为原树中 $i,j$ 两点间的距离，则答案就是 $\sum\limits^{n}_{i=1}\sum\limits^{n}_{j=i+1}[\left\lfloor\frac{dis_{i,j}}{2}\right\rfloor+(dis_{i,j}\bmod 2)]$。因为从 $i$ 到 $j$ 的最短距离显然是尽量多走新连的边，这样就把路程削了一半。

一对点一对点求显然不现实，考虑对于每个 $i$ 把它对答案的贡献打包算出来。当时切完看了眼题解发现不少人写了一种奇妙性质做法，做的时候没发现，于是写了一个暴力换根 DP。

拎 $1$ 作根，第一次 dfs 先求出只考虑每个点子树上的值时的答案。

设 $cnt_{i,0/1}$ 为以 $i$ 为根的子树中与 $i$ 的距离为偶数/奇数的点的个数，$sum_{i,0/1}$ 为在以 $i$ 为根的子树中与 $i$ 的距离为偶数/奇数的点与 $i$ 的距离之和，好绕……这些很好预处理，从下往上转移，每往上转移一层就把奇偶点的个数互换一下，并把深度和都加上个数（因为根节点往上移了一层）。

第二次 dfs 再把每个点子树之外的答案加上。设 $tot_{i,0/1}$ 为整棵树中与 $i$ 的距离为偶数/奇数的点的个数，$dp_{i,0/1}$ 为在整棵树中与 $i$ 的距离为偶数/奇数的点与 $i$ 的距离之和，此时搜到第 $p$ 个点，正在遍历它的儿子 $i$。显然 $tot_1$ 和 $dp_1$ 跟之前的 $cnt_1$ 和 $sum_1$ 一模一样。往下遍历一层只会使整棵树上的点到 $i$ 的距离的奇偶性互换一下，所以 $tot_i$ 就是 $tot_p$ 反过来。

以求 $dp_{i,0}$ 为例，将 $dp_{p,1}$ 的值先减去 $i$ 的子树中占的部分 $cnt_{i,0}+sum_{i,0}$，加 $sum_{i,0}$ 是因为 $i$ 与 $p$ 差了一层，消掉误差，得到 $p$ 中 $i$ 子树以外的答案，又因为这时的答案是以 $p$ 作根的，所以要将这些值的深度再都加个 $1$，也就是总体加 $tot_{p,1}-cnt_{i,0}$。最后把原本子树上的答案补回去，就是加上 $sum_{i,0}$。总之可以得到 $dp_{i,0}=dp_{p,1}-(cnt_{i,0}+sum_{i,0})+(tot_{p,1}-cnt_{i,0})+sum_{i,0}$。把第二维的下标反一下就是 $dp_{i,1}$ 了。答案就是 $dp_{i,0/1}$ 的总和。

没完呢，还记得我们求的是什么吗！对于每个 $i$，$dp_{i,0}$ 好办，除以 $2$ 就是它对答案的贡献了；$dp_{i,1}$ 不太一样，因为它还要再除以 $2$ 取整的基础上再外包个点数和，于是它对答案的贡献是 $(dp_{i,1}-tot_{i,1})\div2+tot_{i,1}$。加起来之后除以个 $2$ 就是最终的答案了。

看着其它题解扫一扫算一算直接出答案，感觉血亏。

代码实现跟讲的略有差别，本质上一样。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define vo void()
using namespace std;
const ll N=2e5+7;
ll n,cnt[N][2],sum[N][2],tot[N][2],dp[N][2],dep[N],ans;
vector<ll> v[N];
void dfs1(ll p,ll f) {
	cnt[p][0]=1,dep[p]=dep[f]+1;
	for (ll i:v[p]) if (i!=f) {
		dfs1(i,p),cnt[p][0]+=cnt[i][1],cnt[p][1]+=cnt[i][0];
		sum[p][0]+=sum[i][1]+cnt[i][1],sum[p][1]+=sum[i][0]+cnt[i][0];
	}
}
void dfs2(ll p,ll f) {
	dp[p][0]+=sum[p][0],dp[p][1]+=sum[p][1];
	for (ll i:v[p]) if (i!=f) {
		dp[i][0]=dp[p][1]-(sum[i][0]+cnt[i][0])+(tot[p][1]-cnt[i][0]);
		dp[i][1]=dp[p][0]-(sum[i][1]+cnt[i][1])+(tot[p][0]-cnt[i][1]);
		dfs2(i,p);
	}
}
int main() {
	scanf("%lld",&n);
	for (ll i=1,x,y;i<n;i++) scanf("%lld%lld",&x,&y),v[x].pb(y),v[y].pb(x);
	dfs1(1,0);
	for (ll i=1;i<=n;i++) tot[i][0]=cnt[1][dep[i]&1^1],tot[i][1]=cnt[1][dep[i]&1];
	dfs2(1,0);
	for (ll i=1;i<=n;i++) ans+=dp[i][0]/2+(dp[i][1]-tot[i][1])/2+tot[i][1];
	printf("%lld",ans/2);
	return 0;
}
```

---

## 作者：bztMinamoto (赞：2)

因为实在太菜了不会树形dp的只好用点分了……

（点分是个好东西所有树的题目都可以暴力艹过去）

首先，设原点对之间距离为$dis$，如果$dis$是奇数，那么新的距离为$(dis>>1)+1$，否则为$dis>>1$

我们考虑如何计算经过当前根节点的路径对答案的贡献

我们设已经dfs过的子树中有$cnt0$条长度为偶数的链，$dis0$这些链的每一条的长度除以二之和，同理$cnt1$和$dis1$表示长度为奇数的链的条数和每一条链的长度除以二加一的和

简单来讲$dis1$和$dis0$分别表示将原$dis$按上面的方法转化后的答案

然后考虑当前子树$v$，设$v$中的以上信息分别为，$cnt[0],cnt[1],dis[0],dis[1]$

然后就是路径的两两组合分别计入答案就是了

顺便注意因为两条奇数路径合起来变为偶数，所以相当于每一条路径的长度都要减一

然后别忘了加上子树单独的贡献
```
//minamoto
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=2e5+5;
int head[N],Next[N<<1],ver[N<<1],tot;
int cnt[2];ll dis[2],ans=0;
inline void add(int u,int v){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
}
int sz[N],son[N],size,vis[N],rt,n;
void findrt(int u,int fa){
	sz[u]=1,son[u]=0;
	for(int i=head[u];i;i=Next[i]){
		int v=ver[i];
		if(vis[v]||v==fa) continue;
		findrt(v,u),sz[u]+=sz[v],cmax(son[u],sz[v]);
	}
	cmax(son[u],size-sz[u]);
	if(son[u]<son[rt]) rt=u;
}
void dfs(int u,int fa,int d){
	d&1?(++cnt[1],dis[1]+=((d>>1)+1)):(++cnt[0],dis[0]+=(d>>1));
	for(int i=head[u];i;i=Next[i]){
		int v=ver[i];
		if(v!=fa&&!vis[v]) dfs(v,u,d+1);
	}
}
void getans(int u){
	int cnt0=0,cnt1=0;ll dis0=0,dis1=0;
	for(int i=head[u];i;i=Next[i]){
		int v=ver[i];
		if(vis[v]) continue;
		cnt[0]=cnt[1]=0,dis[0]=dis[1]=0;
		dfs(v,u,1);
//		ans+=dis[1]*dis1-cnt[1]*cnt1;
//		ans+=dis[1]*dis0;
//		ans+=dis[0]*dis1;
//		ans+=dis[0]*dis0;
		ans+=dis[1]*cnt1+dis1*cnt[1]-1ll*cnt1*cnt[1];
		ans+=dis[1]*cnt0+dis0*cnt[1];
		ans+=dis[0]*cnt1+dis1*cnt[0];
		ans+=dis[0]*cnt0+dis0*cnt[0];
		ans+=dis[1]+dis[0];
		cnt0+=cnt[0],cnt1+=cnt[1];
		dis0+=dis[0],dis1+=dis[1];
	}
}
void solve(int u){
	vis[u]=1,getans(u);
	for(int i=head[u];i;i=Next[i]){
		int v=ver[i];
		if(vis[v]) continue;
		size=sz[v],rt=0,findrt(v,u);
		solve(rt);
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read();
	for(int i=1,u,v;i<n;++i)
	u=read(),v=read(),add(u,v),add(v,u);
	son[rt=0]=n+1,size=n,findrt(1,0);
	solve(rt);
	printf("%I64d\n",ans);
	return 0;
}
```

---

## 作者：Itst (赞：2)

### [传送门](http://codeforces.com/problemset/problem/1060/D)

### 树形$DP$好题被我点分治乱搞过了QAQ

### 点分治中唯一需要注意的是：统计答案时因为长度为奇数的路线除二后要向上取整，所以要在计算时加上路径长度为奇数的路径数量

### 点分治都是模板题，会一个就全会了qwq

```
#include<bits/stdc++.h>
#define MAXN 200010
#define int long long
using namespace std;

struct Edge{
	int end , upEd;
}Ed[MAXN << 1];
long long head[MAXN] , size[MAXN] , N , minSize , minDir , nowSize , cntEd;
long long ans;
bool vis[MAXN];

inline void addEd(int a , int b){
	Ed[++cntEd].end = b;
 	Ed[cntEd].upEd = head[a];
 	head[a] = cntEd;
}

//求当前子树大小
void getNowSize(int dir){
 	vis[dir] = 1;
 	nowSize++;
 	for(int i = head[dir] ; i ; i = Ed[i].upEd)
 		if(!vis[Ed[i].end])
			getNowSize(Ed[i].end);
	vis[dir] = 0;
}

//求重心
void getZX(int dir){
	vis[dir] = size[dir] = 1;
	int maxSize = 0;
	for(int i = head[dir] ; i ; i = Ed[i].upEd)
		if(!vis[Ed[i].end]){
			getZX(Ed[i].end);
			size[dir] += size[Ed[i].end];
			maxSize = max(maxSize , size[Ed[i].end]);
		}
	maxSize = max(maxSize , nowSize - size[dir]);
	if(maxSize < minSize){
		minSize = maxSize;
		minDir = dir;
	}
	vis[dir] = 0;
}

//算答案
pair < long long , long long > calAns(int dir , int dep){
	vis[dir] = 1;
	ans += dep + 1 >> 1;
	nowSize++;
	pair < long long , long long > q = make_pair(dep , dep & 1);
	for(int i = head[dir] ; i ; i = Ed[i].upEd)
		if(!vis[Ed[i].end]){
			pair < long long , long long > t = calAns(Ed[i].end , dep + 1);
			q.first += t.first;
			q.second += t.second;
		}
	vis[dir] = 0;
	return q;
}

void work(int dir){
	nowSize = 0;
	getNowSize(dir);
	minSize = nowSize;
	getZX(dir);
	long long t = minDir , sum = 0 , culJi = 0 , culOu = 0;
	vis[t] = 1;
	nowSize = 0;
	for(int i = head[t] ; i ; i = Ed[i].upEd)
		if(!vis[Ed[i].end]){
			int k = nowSize;
            //注意答案统计！
			pair < long long , long long > t = calAns(Ed[i].end , 1);
			ans += (sum * (nowSize - k) + t.first * k + t.second * culOu + culJi * (nowSize - k - t.second)) >> 1;
			sum += t.first;
			culJi += t.second;
			culOu += nowSize - k - t.second;
		}
	for(int i = head[t] ; i ; i = Ed[i].upEd)
		if(!vis[Ed[i].end])
			work(Ed[i].end);
}

signed main(){
  ios::sync_with_stdio(0);
	cin >> N;
	for(int i = 1 ; i < N ; i++){
		int a , b;
		cin >> a >> b;
		addEd(a , b);
		addEd(b , a);
	}
	work(1);
	cout << ans;
	return 0;
}
```

---

## 作者：liangbowen (赞：1)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1060E)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17233918.html)

提供一种更加麻烦的换根 DP 写法。

## 思路

手玩样例。发现一个性质：原图上距离为 $w$ 的两个点，在新图上的距离是 $\lfloor\dfrac{w}{2}\rfloor$。

于是题目就是求 $\sum\limits_{u=1}^n\sum\limits_{v=1}^n\lfloor\dfrac{dis(u, v)}{2}\rfloor$，很容易想到求出每一个 $\sum\limits_{v=1}^n\lfloor\dfrac{dis(u, v)}{2}\rfloor$ 后求和即为答案。

这种形式就是换根 DP。

维护 $siz_{u, i}$（$i \in \{0, 1\}$）表示 $u$ 的子树到 $u$ 的**原距离**为奇数（或偶数）的点的数量。

同样地，$sum_u$ 统计 $u$ 的子树到 $u$ 的**新距离**的点的数量。

于是就有：

$$siz_{u, 0} = 1 + \sum\limits_{v \in son_u} siz_{v, 1}$$

$$siz_{u, 1} = \sum\limits_{v \in son_u} siz_{v, 0}$$

$$sum_u = 1 + \sum\limits_{v \in son_u} (sum_v + siz_{v, 0})$$

状态很套路所以就不解释了。

然后就是换根。不妨设当前以 $1$ 为根，于是 $ans_u$ 表示以 $u$ 为根的时候的答案。

接下来就是换根：

$$ans_u = \begin{cases}
1  &  u = 1 \\
ans_{fa} + siz_{1, k} - siz_{u, 1} - siz_{u, 0}  &  \text{otherwise}
\end{cases}$$

其中 $k$ 表示 $dep_u \mod 2$。

解释一下。对于 $u$：

+ 所有到 $u$ 为奇数的点的距离都要加 $1$，一共有 $(siz_{1, k} - siz_{u, 1})$ 个这种点。
+ 所有到 $u$ 为偶数的点的距离都要减 $1$，一共有 $siz_{u, 0}$ 个这种点。

答案即为 $\lfloor\dfrac{\scriptsize\sum\limits_{i=1}^n ans_i}{2}\rfloor$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
struct Edge {int now, nxt;} e[N << 1];
int head[N], cur;
void add(int u, int v)
{
	e[++cur].now = v, e[cur].nxt = head[u];
	head[u] = cur;
}
ll sum[N], siz[N][2];
void dfs(int u, int fa)
{
	siz[u][0] = 1;
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (v == fa) continue;
		dfs(v, u);
		siz[u][0] += siz[v][1], siz[u][1] += siz[v][0];
		sum[u] += (sum[v] + siz[v][0]);
	}
}
ll ans[N];
void DFS(int u, int fa, int dep)
{
	for (int i = head[u]; i; i = e[i].nxt)
	{
		int v = e[i].now;
		if (v == fa) continue;
		ans[v] = ans[u] + siz[1][dep & 1] - siz[v][1] - siz[v][0];
		DFS(v, u, dep + 1);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1, 0), ans[1] = sum[1], DFS(1, 0, 0);
	ll zlt = 0;
	for (int i = 1; i <= n; i++) zlt += ans[i];
	cout << zlt / 2;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Little09 (赞：1)

~~YLWang 讲的题。~~

容易发现答案是 $\sum_{i=1}^n\sum_{j=i+1}^n\lceil\dfrac{dist_{i,j}}{2}\rceil$。

如果我们要计算 $w=\sum_{i=1}^n\sum_{j=i+1}^ndist_{i,j}$，可以选择换根 DP 或计算贡献的方式（计算每条边被算了几次）

所以我们计算出 $dist_{i,j}$ 为奇数的次数记为 $t$，则答案为 $\frac{w+t}{2}$。

如何计算 $t$ 的值？容易发现对树黑白染色，只有黑点和白点的点对会对 $t$ 产生贡献。所以 $t$ 的值应当是黑点个数 $\times$ 白点个数。

---

## 作者：yijan (赞：1)

首先%一下楼下的@Itst 大佬树分治碾压 跨上紫名

原本自己也快了结果B&D FST*2.。。。。。。   
自己不会树分治就只会用简单一点的方法了～

这道题看似很麻烦，但是仔细分析一下，首先预处理出所有两点间的距离和(算个贡献一次dfs搞定)，顺便记录深度。

这里啰嗦一下怎么算亮点间的距离和，考虑每个边的贡献，首先下面这个点的两边的点肯定分别要与另一边的点跑一次，所以说就是$siz[u]*(n-siz[u])$
更新一下就好了

然后考虑奇偶性判定，如果两点间是奇数那么显然最短距离就是这两点间的距离除以二（向下取整）+1，如果是偶数就是两点间的距离除以二。

所以我们给处理出来的距离和先除以二，然后就是判断奇数路径的个数。

两点间的距离是 $dep(u) + dep(v) - 2dep(lca(u,v))$ 由于2lca(u,v)显然不影响奇偶性，答案就很显然了，就直接记录深度为奇数的个数。

%%%

ACCode
```cpp
/*Heroes Never Die!*/
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long ll;
#define MAXN 200006
ll dep[MAXN],tot = 0,siz[MAXN];
struct edge{
    ll u;edge* next;
    edge(ll u=0,edge* next=NULL):u(u),next(next) {}
    void insert(ll u){
        if(this->next == NULL) this->next = new edge(u,NULL);
        else this->next = new edge(u,this->next);
    }
}e[MAXN];
ll n,ji;
void dfs(ll u,ll fa){
    if(dep[u] & 1) ++ ji;
    siz[u] = 1;
    for(edge* n=e[u].next;n!=NULL;n=n->next){
        ll v = n->u;
        if(v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs(v,u);
        siz[u] += siz[v];
    }
    tot += siz[u] * (n-siz[u]);
}
int main(){
    cin >> n;
    for(ll i=0;i<n-1;++i){
        static ll u,v;scanf("%lld%lld",&u,&v);
        e[u].insert(v),e[v].insert(u);
    }
    dep[1] = 1;
    dfs(1,1);
    tot += ji*(n-ji);
    cout << tot/2;
}
```

---

## 作者：FLORIZ (赞：0)

鉴于连边只是让一些需要走两条边到达的位置能走一条边到达，所以首先考虑不连新边，只去想原先边的情况下总和的个数。

考虑每条边对答案贡献：每条边对应的子树的每个节点都与该子树外每个节点有路径，所以原答案是 $\sum^{n}_{i=1} (size_i \times (n-size_i))$。

新边建完一次能走两格，所以考虑直接把答案除以二向上取整，可惜向上取整没有结合律，只能继续找规律。发现只有从深度奇数到偶数向上取整有影响。因为每个奇数深度到所有偶数深度都有连边，所以在原答案加上奇数深度乘偶数深度再除以二。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
	{long long f(1),x(0);
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return f*x;
	}
void write(long long x)
	{if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	}
#define debug(x) cout<<"###"<<x<<endl;

#define maxn 200010
long long n,ans;

long long ji,ou;
long long head[maxn],tot;
struct bian
	{long long to,nx;
	} bian[maxn<<1];
inline void add(long long from,long long to)
	{bian[++tot].to=to;
	bian[tot].nx=head[from];
	head[from]=tot;
	}

long long size[maxn],dep[maxn];
void dfs(long long x,long long fa)
	{size[x]=1;
	dep[x]=dep[fa]+1;
	for(long long i=head[x];i;i=bian[i].nx)	
		{long long y=bian[i].to;
		if(y==fa) continue;
		dfs(y,x);
		size[x]+=size[y];
		}
	}

int main()
	{n=read();
	for(long long i=1;i<=n-1;i++)
		{long long b=read(),c=read();
		add(b,c),add(c,b);
		}
	dfs(1,0);
	for(long long i=2;i<=n;i++)
		{ans+=(n-size[i])*size[i];
		}
	for(long long i=1;i<=n;i++)
		{if(dep[i]&1)
			{ji++; 
			}
		else
			{ou++;
			}
		}
	ans+=ou*ji;
	ans>>=1;
	write(ans);
	return 0;
	}
```

---

## 作者：Really (赞：0)

给出一个和点分治很像的想法。

分析题目可以发现，目标求得其实就是对于所有的点对 $u$，$v$ 求和 $\left\lceil\dfrac{dis_{i,j}}{2} \right\rceil$ ，很明显，直接枚举会超时，所以我们可以规定每一个点对 $u$,$v$ 都在 $lca_{u,v}$ 上计算。

那么我们一遍 dfs，对于每个节点 $u$，维护子树内到 $u$ 距离为奇数和偶数的数量，奇数和偶数的 $\sum \left\lceil\dfrac{dis_{i,j}}{2} \right\rceil$，在一个 $v$ 递归回到$u$时，统计答案，然后合并 $u$ 信息。

我考场上降智维护的是 $\sum \left\lfloor\dfrac{dis_{i,j}}{2} \right\rfloor$ ，统计的时候麻烦了一点。


code:

```cpp
//Really luogu
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 200005
inline int read(){
	int x=0,f=1; char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
	while(c<='9'&&c>='0'){x=(x<<3)+(x<<1)+(c^'0'); c=getchar();}
	return x*f;
}struct Edge{
	int to,nex;
}e[N<<2];int tot,h[N],n;
int s1[N],s0[N],n0[N],n1[N],ans;
void add(int w1,int w2){e[++tot]=(Edge){w2,h[w1]}; h[w1]=tot;}
#define v e[i].to
void dfs(int u,int fa){
	n0[u]=1; s0[u]=0;
	for(int i=h[u];i;i=e[i].nex){
		if(v==fa) continue;
		dfs(v,u);
		int tmp1=s0[v],tmp2=s1[v];
		s0[v]=tmp2+n1[v];
		s1[v]=tmp1;
		swap(n1[v],n0[v]);
		int tmp=ans;
		ans+=n0[v]*s1[u]+s0[v]*n1[u]+n1[u]*n0[v];
		ans+=n1[v]*s0[u]+s1[v]*n0[u]+n0[u]*n1[v];
		ans+=n0[v]*s0[u]+s0[v]*n0[u];
		ans+=n1[v]*s1[u]+s1[v]*n1[u]+n1[u]*n1[v];
		s1[u]+=s1[v]; s0[u]+=s0[v];
		n1[u]+=n1[v]; n0[u]+=n0[v];
		
	}
}
signed main(){
//	freopen("date.txt","r",stdin);
	n=read();
	for(int i=1;i<n;i++){
		int w1=read(),w2=read();
		add(w1,w2); add(w2,w1);
	}dfs(1,0);
	printf("%lld\n",ans);
}
```


---

## 作者：5k_sync_closer (赞：0)

令 $\text{subtree}(x)$ 表示 $x$ 子树，$\text{fa}(x)$ 表示 $x$ 的父亲，$d(i,j)$ 表示 $i$ 到 $j$ 的距离。

答案等于 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\left\lceil\dfrac{d(i,j)}2\right\rceil$，于是随便怎么求一下，比如换根 DP。

设 $f_i=\sum\limits_{j\in\text{subtree}(i)}\left\lceil\dfrac{d(i,j)}2\right\rceil,s_i=\sum\limits_{j\in\text{subtree}(i)}[d(i,j)\equiv 0\pmod 2]$，

则有 $f_u=\sum\limits_{v\in\text{son}(u)}f_v+s_v$（所有到 $v$ 距离为偶数的点到 $u$ 距离为奇数，贡献加一），

$s_u=1+\sum\limits_{v\in\text{son}(u)}\text{size}_v-s_v$（所有到 $v$ 距离为奇数的点到 $u$ 距离为偶数）。

设 $g_i=\sum\limits_{j=1}^n\left\lceil\dfrac{d(i,j)}2\right\rceil,t_i=\sum\limits_{j=1}^n[d(i,j)\equiv 0\pmod 2]$，

则有 $g_v=f_v+(g_{\text{fa}(v)}-f_v-s_v)+(t_{\text{fa}(v)}-\text{size}_v+s_v)=g_{\text{fa}(v)}+t_{\text{fa}(v)}-\text{size}_v,t_v=n-t_{\text{fa}(v)}$。

```cpp
#include <cstdio>
#define int long long
struct E
{
    int v, t;
} e[1000050];
int n, c, q, S[1000050], f[1000050], s[1000050], g[1000050], t[1000050], h[1000050];
void A(int u, int v)
{
    e[++c] = {v, h[u]};
    h[u] = c;
}
void F(int u, int k)
{
    S[u] = s[u] = 1;
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            F(v, u), S[u] += S[v], s[u] += S[v] - s[v], f[u] += f[v] + s[v];
}
void G(int u, int k)
{
    for (int i = h[u], v; i; i = e[i].t)
        if ((v = e[i].v) != k)
            t[v] = n - t[u], g[v] = g[u] + t[u] - S[v], G(v, u);
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1, u, v; i < n; ++i)
        scanf("%lld%lld", &u, &v), A(u, v), A(v, u);
    F(1, 0);
    g[1] = f[1];
    t[1] = s[1];
    G(1, 0);
    for (int i = 1; i <= n; ++i)
        q += g[i];
    printf("%lld", q >> 1);
    return 0;
}
```


---

## 作者：Aewrxuk (赞：0)

题目链接：[Sergey and Subway](https://www.luogu.com.cn/problem/CF1060E)

因为题目说每隔着一个点的两个点之间都是可以建一条新边的，所以我们会发现最终的距离 $ans$ 其实就是最开始全部的距离除以二并向上取整。

为什么会向上取整呢？

我们知道原先的距离和有所有奇数长的边的总和和所有偶数边的长的总和得来，而每一条奇数长的边在建完新边后，还是无法避免走一条旧边，那么就不可以直接除以二下取整。那这些上去整的部分我们也可以看做就是奇数长的边的个数。所以，我们最后可以得出结论：$ans=(tot +odd) \div2$。

我们接下来考虑如何计算原先的总距离，我们可以转化为求每一条边的贡献之和，也就是每一条边的两边点对之和，我们在遍历树的时候可以将一条边的两边的点对求出：$siz_i \times(n -siz_i)$ 就是求 $i$ 节点与他父亲节点间的边的贡献。奇数边的个数自己观察一下可以找出规律。

代码实现：
```cpp
struct node
{
	int next,to;
}
edge[400010];

int n,a,b,num,ans,odd;

int head[200010],dep[200010],siz[200010];

inline void add(int u,int v)
{
	edge[++num].to=v;
	edge[num].next=head[u];
	head[u]=num;
}

void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;siz[x]=1;
	if(dep[x]%2) odd++;
	for(int i=head[x];i;i=edge[i].next)
	{
		int y=edge[i].to;
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
		ans+=siz[y]*(n-siz[y]);
	}
}

signed main()
{
	cin >> n;
	for(int i=1;i<n;i++)
	{
		cin >> a >> b;
		add(a,b);add(b,a);
	}
	dfs(1,0);
	ans+=(odd)*(n-odd);
	cout << ans/2 << '\n';
	return 0;
}
```

---

## 作者：Tastoya (赞：0)

[更好的阅读体验](https://www.cnblogs.com/baijian0212/p/CF1060E.html)

### 题目大意

给定一棵树，每两个有边直接相连的点之间距离为 $1$。现在我们要给所有原来距离为 $2$ 的城市之间修一条长度为 $1$ 的道路。

记 $dis(a,b)$ 表示 $a,b$ 之间的最短距离，求

$$
\sum_{i=1}^n\sum^{n}_{j=i+1}dis(i,j)
$$

### 思路

考虑修改后的树任意两点间距离与修改前的关系。

![](https://cdn.luogu.com.cn/upload/image_hosting/1fx6gzip.png)

例如，$1$ 和 $3$ 原本距离为 $2$，现在距离为 $1$；$3$ 和 $4$ 原本距离为 $3$，现在距离为 $2$。

我们发现，对于原树中两点间的距离 $dis$，现在的距离为 $\lfloor \frac{dis + 1}{2} \rfloor$。

考虑把这个式子转化一下，变成

$$
\left\lfloor \frac{dis + 1}{2} \right\rfloor=\dfrac{dis+\left[ dis\equiv1(\!\!\!\!\mod 2 ) \right]}{2}
$$

那么我们代入题目给出的式子，得到

$$
\sum^{n}_{i=1}\sum^{n}_{j=i+1}(\dfrac{dis(i,j)+\left[ dis(i,j)\equiv1(\!\!\!\!\mod 2 ) \right]}{2})
$$

很显然，我们发现，最终答案与边权的奇偶性和原树边权和有关。

考虑如何求路径长度？两点间距离为

$$
dis(i,j)=dep_i+dep_j-2\times \operatorname{dep_{\operatorname{lca}(i,j)}}
$$

其中后面 $-2\times \operatorname{dep_{\operatorname{lca}(i,j)}}$ 的部分与路径长度的奇偶性无关，那么直接统计 $dep_i$ 和 $dep_j$ 奇偶性不同的点对数量就可以求出路径长度为奇数的路径数量。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200500;

int n;

struct Edge{
    int next,to;
}e[N << 1];

int h[N],cnt;

void Add(int u,int v) {
    cnt ++;
    e[cnt].next = h[u];
    h[u] = cnt;
    e[cnt].to = v;
}

namespace SOL{
    long long ans = 0;
    int size[N],cnt[N];

    void dfs(int x,int fa,int dep) {
        cnt[dep ^ 1] ++;
        size[x] = 1;

        for(int i = h[x];i;i = e[i].next) {
            int to = e[i].to;

            if(to == fa) 
                continue;
        
            dfs(to,x,dep ^ 1);
            size[x] += size[to];
        }

        ans += 1ll * (n - size[x]) * size[x];
    }
  
    void Work() {
        memset(cnt,0,sizeof(cnt));
        memset(size,0,sizeof(size));

        dfs(1,1,0);

        ans = ans + 1ll * cnt[0] * cnt[1];
        ans /= 2;

        cout << ans << "\n";
        return ;
    }
}

int main() {
#ifdef ONLINE_JUDGE == 1
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
#endif
    scanf("%d",&n);

    for(int i = 1,u,v;i < n; i++) {
        scanf("%d%d",&u,&v);
        Add(u,v);
        Add(v,u);
    }

    SOL::Work();

    fclose(stdin);
    fclose(stdout);
    return 0;
}
```


---

## 作者：int_R (赞：0)

模拟赛 T1，树形 DP。给出一种很麻烦的做法。

考虑一个简单问题，给一棵树，求：

$$\sum\limits_{i=1}^n \sum\limits_{j=i+1}^{n} \operatorname{dis}(i,j)$$

定义 $cnt_x$ 表示 $x$ 的子树大小；$sum_x$ 表示 $x$ 的子树中每个点距离 $x$ 的距离和。

使用常规思路统计一个点的一颗子树与其他子树之间的贡献。设当前点为 $x$，依次枚举 $x$ 的儿子 $y$，统计 $y$ 这颗子树与之前枚举过的其他子树之间的贡献。应为：

$$sum'_x\times cnt_y + (sum_y+cnt_y)\times cnt'_x$$

$sum_y+cnt_y$ 是因为你要计算从 $y\to x$ 那条边的贡献，即距离和加上 $cnt_y\times 1$。

之后计算完后 $cnt'_x=cnt'_x+cnt_y,sum'_x=sum'_x+(sum_y+cnt_y)$。

对于每个点赋初值 $cnt_x=1$ 表示自身这个点。

------------

原树上距离为 $2$ 的点连一条边，可以发现 $\operatorname{dis}(i,j)$ 变成了 $\lceil \dfrac{\operatorname{dis}(i,j)}{2}\rceil$，问题即求原树上

$$\sum\limits_{i=1}^n \sum\limits_{j=i+1}^{n} \lceil \dfrac{\operatorname{dis}(i,j)}{2}\rceil$$

发现向上取整不好处理，考虑对奇数距离和偶数距离进行分讨，算出答案的二倍。

定义 $cnt_{x,0/1}$ 表示 $x$ 的子树中距离 $x$ 的距离为偶数/奇数的点的个数；$sum_{x,0/1}$ 表示 $x$ 的子树中距离 $x$ 的距离为偶数/奇数的距离和。

发现距离 $x$ 的奇偶性和距离 $y$ 的奇偶性相同的话，这条路径的长度是奇数（因为还要加上从 $y\to x$）的那一条边。

则依旧设当前点为 $x$，依次枚举 $x$ 的儿子 $y$，统计 $y$ 这颗子树与之前枚举过的其他子树之间的贡献。应为：

$$\sum\limits_{i=0}^{1}\sum\limits_{j=0}^{1} sum'_{x,i}\times cnt_{y,j} + (sum_{y,j}+cnt_{y,j})\times cnt'_{x,i} +(i=j)\times (cnt'_{x,i}\times cnt_{y,j})$$

之后计算完后 $cnt'_{x,i}=cnt'_{x,i}+cnt_{y,!i},sum'_{x,i}=sum'_{x,i}+(sum_{y,!i}+cnt_{y,!i})$。

对于每个点赋初值 $cnt_{x,0}=1$ 表示自身这个点。

最后答案除以 $2$，显然时间复杂度为 $O(n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=2e5+10;
int n;vector <int> v[MAXN];
long long ans=0,cnt[MAXN][2],sum[MAXN][2];
void dfs(int x,int fa=0)
{
    cnt[x][0]=1;
    for(int y:v[x])
    {
        if(y==fa) continue;dfs(y,x);
        for(register int i=0;i<=1;++i)
            for(register int j=0;j<=1;++j)
                ans+=sum[x][i]*cnt[y][j]+(sum[y][j]+cnt[y][j])*cnt[x][i]+(i^j)*(cnt[x][i]*cnt[y][i]);
        for(register int i=0;i<=1;++i)
            cnt[x][i]+=cnt[y][i^1],sum[x][i]+=sum[y][i^1]+cnt[y][i^1];
    }
    return ;
}
int main()
{
    cin>>n;
    for(register int i=1;i<n;++i)
    {
        int x,y;cin>>x>>y;
        v[x].push_back(y),v[y].push_back(x);
    }
    dfs(1);cout<<(ans>>1)<<'\n';
    return 0;
}
```


---

## 作者：redegg (赞：0)

本月第二篇换根题解。

这题题意转化就是，我们把任意两点间最短路除以二向上取整求和。

那么$n$如此之大，我们先枚举特定点$i$，我们肯定考虑快速求出特定点$i$到所有点的最短路，但是求最短路的方式就是遍历，我们要求出$i$点到其他所有点的最短路最快就是$O(n)$，还要一层枚举，那么为了降下复杂度，我们考虑在枚举$i$时，直接转移答案，而不是重新跑一遍。

那么可以先看看这题：$P1395$。转移最短路思路一样。

设计$l[i]$表示所有点到$i$的最短路之和，$v[i]$表示包括$i$点的子树里面的点数，$a[i]$表示子树里面与$i$距离为偶数个数（$i$也是一个），$b[i]$表示奇数，$son[i]$表示$i$的子节点。

这题与$P1395$不同之处在于最短路要除$2$，然后向上取整，$i$点的答案就是$l[i]/2+b[i]-b[i]/2$，此处的$/$指向下取整的除。

那么我们把$i$换根到$son[i]$的时候，先将$i$和$son[i]$分离，然后将$i$当成子树接到$son[i]$上就可以了。

具体细节需要自己想一下。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
long long a[400006];
long long b[400006];
long long l[400005];
long long v[400005];

vector<int> q[400005];

void dfs(int x,int father)
{
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(nx==father)continue;
        dfs(nx,x);
        v[x]+=v[nx];
        l[x]+=(v[nx]+l[nx]);
        a[x]+=b[nx];
        b[x]+=a[nx];
    }
    a[x]+=1;
    v[x]+=1;
}

int change(int x,int nx)
{
    v[x]-=v[nx];
    l[x]-=(l[nx]+v[nx]);
    a[x]-=b[nx];
    b[x]-=a[nx];
    swap(x,nx);
    v[x]+=v[nx];
    l[x]+=(v[nx]+l[nx]);
    a[x]+=b[nx];
    b[x]+=a[nx];
}

long long ans;

void dd(int x,int father)
{
    ans+=l[x]/2;
    ans+=b[x];
    ans-=b[x]/2;
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(nx==father)continue;
        change(x,nx);
        dd(nx,x);
        change(nx,x);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        q[x].push_back(y);
        q[y].push_back(x);
    }
    dfs(1,1);
    dd(1,1);
    printf("%lld\n",ans/2);
    return 0;
}

```

---

## 作者：asuldb (赞：0)

好像就我写的非常鬼畜了

首先，在原图上新加了一些边，原来的$u$,$v$两点之间的距离就会变成$\left \lceil \frac{dis(u,v)}{2} \right \rceil$

于是我们可以用换根$dp$来做

设$f[x][0]$表示到$x$点有多少条路径为偶，$f[x][1]$表示有多少条路径为奇

$dp[x][0]$表示所有偶路径的长度和是多少，$dp[x][1]$表示所有奇路径的长度和是多少

于是我们就可以换根$dp$了

在第一遍$dfs$里，我们先求出$x$的子树内的信息，往上合并到根

之后第二遍$dfs$，我们在将父亲的信息合并给儿子

之后我们就可以统计答案了

由于我们对于每一个点都求出了所有点到它的距离，于是求出来的路径总长度得先除以$2$

偶路径直接除以$2$就好了，奇路径要根据奇路径的条数的奇偶性再做个判断


代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define re register
#define maxn 200005
#define LL long long
int deep[maxn],sum[maxn];
LL dp[maxn][2],f[maxn][2];
struct E
{
	int v,nxt;
}e[maxn<<1];
int head[maxn],n,num;
inline void add_edge(int x,int y)
{
	e[++num].v=y;
	e[num].nxt=head[x];
	head[x]=num;
}
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
void dfs(int x)
{
	f[x][0]=1;
	for(re int i=head[x];i;i=e[i].nxt)
	if(!deep[e[i].v])
	{
		deep[e[i].v]=deep[x]+1;
		dfs(e[i].v);
		f[x][0]+=f[e[i].v][1];
		f[x][1]+=f[e[i].v][0];
		dp[x][0]+=dp[e[i].v][1]+f[e[i].v][1];
		dp[x][1]+=dp[e[i].v][0]+f[e[i].v][0];
	}
}
void Redfs(int x)
{
	for(re int i=head[x];i;i=e[i].nxt)
	if(deep[e[i].v]>deep[x])
	{
		dp[e[i].v][0]+=dp[x][1]-dp[e[i].v][0]-f[e[i].v][0]+f[x][1]-f[e[i].v][0];
		dp[e[i].v][1]+=dp[x][0]-dp[e[i].v][1]-f[e[i].v][1]+f[x][0]-f[e[i].v][1];
		f[e[i].v][0]+=f[x][1]-f[e[i].v][0];
		f[e[i].v][1]+=f[x][0]-f[e[i].v][1];
        //得先排除掉e[i].v子树内部的信息
		Redfs(e[i].v);
	}
}
int main()
{
	n=read();
	int x,y;
	for(re int i=1;i<n;i++)
		x=read(),y=read(),add_edge(x,y),add_edge(y,x);
	deep[1]=1;
	dfs(1);
	Redfs(1);
	LL f0=0,f1=0,d0=0,d1=0;
	for(re int i=1;i<=n;i++)
		f0+=f[i][0],f1+=f[i][1],d0+=dp[i][0],d1+=dp[i][1];
	f0>>=1ll;
	f1>>=1ll;
	d0>>=1ll;
	d1>>=1ll;
	LL ans=d0/2;
	if(f1&1) ans+=d1/2+f1/2+1;
	else ans+=d1/2+f1/2;
	std::cout<<ans;
	return 0;
}
```

---

## 作者：npqenqpve (赞：0)

### 思路：

定义 $d(i,j)$ 表示两点在树上的距离。

由于尽量要两个边两个边地走，所以答案实际上是 $$\sum\limits_{1\leq i\leq j\leq n} \lceil \frac{d(i,j)}{2} \rceil$$，但直接求解这个东西不容易，考虑分讨奇偶。由于 $d(i,j)=dep_i+dep_j-2\times dep_{lca(i,j)}$，所以对奇偶性有关系只有 $dep_i$ 和 $dep_j$，那么答案就是 $$\frac{\sum\limits_{1\leq i\leq j\leq n} d(i,j)+[dep_i+dep_j \bmod 2=1]}{2}$$，直接拆开，$$\sum\limits_{1\leq i\leq j\leq n} d(i,j)$$ 可以直接考虑边的贡献，也就是连接 $u$，$v$ 的边把图分成了两个以 $u$，$v$ 为根的联通块，设大小分别为 $x$，$y$，则对答案有 $x\times y$ 这么多的贡献，枚举 $v$ 即可。记有 $x$ 个深度为奇数的点，$y$ 个深度为偶数的点，则答案就是  $$\frac{\sum\limits_{i=1}^n sz_x\times (n-sz_x)}{2}+\frac{x\times y}{2}$$



---

