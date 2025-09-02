# Break Up

## 题目描述

Again, there are hard times in Berland! Many towns have such tensions that even civil war is possible.

There are $ n $ towns in Reberland, some pairs of which connected by two-way roads. It is not guaranteed that it is possible to reach one town from any other town using these roads.

Towns $ s $ and $ t $ announce the final break of any relationship and intend to rule out the possibility of moving between them by the roads. Now possibly it is needed to close several roads so that moving from $ s $ to $ t $ using roads becomes impossible. Each town agrees to spend money on closing no more than one road, therefore, the total number of closed roads will be no more than two.

Help them find set of no more than two roads such that there will be no way between $ s $ and $ t $ after closing these roads. For each road the budget required for its closure was estimated. Among all sets find such that the total budget for the closure of a set of roads is minimum.

## 样例 #1

### 输入

```
6 7
1 6
2 1 6
2 3 5
3 4 9
4 6 4
4 6 5
4 5 1
3 1 3
```

### 输出

```
8
2
2 7
```

## 样例 #2

### 输入

```
6 7
1 6
2 3 1
1 2 2
1 3 3
4 5 4
3 6 5
4 6 6
1 5 7
```

### 输出

```
9
2
4 5
```

## 样例 #3

### 输入

```
5 4
1 5
2 1 3
3 2 1
3 4 4
4 5 2
```

### 输出

```
1
1
2
```

## 样例 #4

### 输入

```
2 3
1 2
1 2 734458840
1 2 817380027
1 2 304764803
```

### 输出

```
-1
```

# 题解

## 作者：FQ04gty (赞：5)

##### [原题链接](http://codeforces.com/problemset/problem/700/C)
---
对三种情况分别考虑。

删去 $0$ 和 $1$ 条边可以分别通过 dfs 和求连通分量来判断。

删去两条边的情况比较特殊：

首先考虑 $1$ 条边的情况中删去的显然是桥，那么应该将所有桥排除掉。

考虑网络流模型。将所有桥权值设为 $\inf$，其余边设置为边权加上一个大数 $W$，跑 $s$ 到 $t$ 的最大流求出最小割即可。

可以发现，排除了桥之后，至少需要割掉两条边才能使得 $s$ 和 $t$ 不连通，给边权加上 $W$ 就是为了选择尽可能少的边。

##### 实现细节

如果网络流跑出的结果大于 $3\cdot W$，则输出 $-1$。

否则从 $s$ 开始 dfs，只走满流边，输出所有一端能够走到，另一端走不到的边即可（这样的边一定只有两条）。

### Code
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define mset(arr,val) memset(arr,val,sizeof(arr))
using namespace std;
typedef long long ll;
typedef pair<ll,ll>pii;
const ll SIZE=6e4+10,inf=1e16,LARGE=1e15;
inline ll read()
{
    ll x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x*10)+(ch^48),ch=getchar();
    return x;
}
queue<ll>q;
vector<pair<ll,pii>>nxt[SIZE];
inline ll min(ll x,ll y){return x<y?x:y;}
ll n,m,s,t,head[SIZE],sizee,dpth[SIZE],ans=inf,fa[SIZE],fv[SIZE],fid[SIZE],sum[SIZE],din,ansid;
bool vst[SIZE],te[SIZE];
struct edge{ll u,v,w,nxt,id;}e[SIZE];
inline void add(ll u,ll v,ll w,ll id){e[sizee]={u,v,w,head[u],id},head[u]=sizee++;}
inline void add_edge(ll u,ll v,ll w,ll id){add(u,v,w,id),add(v,u,w,id);}
void dfs(ll thisp)
{
    vst[thisp]=true;
    for(ll i=head[thisp];~i;i=e[i].nxt)if(!vst[e[i].v])dpth[e[i].v]=dpth[thisp]+1,dfs(e[i].v),fv[e[i].v]=e[i].w,fid[e[i].v]=e[i].id,fa[e[i].v]=thisp,te[i]=te[i^1]=true;
}
void add(ll thisp)
{
    vst[thisp]=true;
    for(ll i=head[thisp];~i;i=e[i].nxt)if(!vst[e[i].v])add(e[i].v),sum[thisp]+=sum[e[i].v];
    for(ll i=head[thisp];~i;i=e[i].nxt)if(dpth[e[i].v]>dpth[thisp])
    {
        if(sum[e[i].v])nxt[thisp].push_back({e[i].v,{LARGE+e[i].w,e[i].id}});
        else nxt[thisp].push_back({e[i].v,{inf,e[i].id}});
    }
}
inline bool bfs()
{
    mset(dpth,0),dpth[s]=1,q.push(s);
    while(!q.empty())
    {
        ll thisp=q.front();q.pop();
        for(ll i=head[thisp];~i;i=e[i].nxt)if(!dpth[e[i].v]&&e[i].w)dpth[e[i].v]=dpth[thisp]+1,q.push(e[i].v);
    }
    return dpth[t];
}
ll dfs(ll thisp,ll rate)
{
    if(thisp==t)return rate;
    ll out=0;
    for(ll i=head[thisp],_rate;~i;i=e[i].nxt)if(dpth[e[i].v]==dpth[thisp]+1&&e[i].w)
    {
        _rate=dfs(e[i].v,min(rate,e[i].w));
        rate-=_rate,out+=_rate,e[i].w-=_rate,e[i^1].w+=_rate;
        if(!rate)return out;
    }
    if(!out)dpth[thisp]=0;
    return out;
}
ll prt[SIZE],top;
inline ll dinic(){ll res=0;while(bfs())res+=dfs(s,inf);return res;}
void get(int thisp)
{
    vst[thisp]=true;
    for(int i=head[thisp];~i;i=e[i].nxt)if(!vst[e[i].v]&&e[i].w!=0&&e[i^1].w!=0)get(e[i].v);
}
int main()
{
    mset(head,-1);
    n=read(),m=read(),s=read(),t=read();
    for(ll i=1,u,v,w;i<=m;i++)u=read(),v=read(),w=read(),add_edge(u,v,w,i);
    dfs(s);
    if(!vst[t])return printf("0\n0"),0;
    for(ll i=0;i<sizee;i++)if(!te[i]&&dpth[e[i].u]<dpth[e[i].v])sum[e[i].v]++,sum[e[i].u]--;
    mset(vst,0);
    add(s);
    for(ll thisp=t;thisp!=s;thisp=fa[thisp])if(!sum[thisp]&&fv[thisp]<ans)ans=fv[thisp],ansid=fid[thisp];
    mset(head,-1),sizee=0;
    for(ll i=1;i<=n;i++)for(pair<ll,pii> j:nxt[i])add_edge(i,j.first,j.second.first,j.second.second);
    din=dinic()-2*LARGE;
    if(ans>=LARGE&&din>LARGE)return printf("-1"),0;
    if(ans<din)printf("%lld\n1\n%lld",ans,ansid);
    else
    {
        printf("%lld\n2\n",din);
        mset(vst,0);
        get(s);
        for(int i=0;i<sizee;i+=2)if(vst[e[i].u]!=vst[e[i].v])prt[++top]=e[i].id;
        printf("%lld %lld",prt[1],prt[2]);
    }
    return 0;
}
```

---

## 作者：蒟蒻初音ミク (赞：4)

# 广告

[蒟蒻的blog](https://www.luogu.com.cn/blog/111990/)

# 正文

### 题目大意：有一个$n$个点$m$条边的无向图，要求最多删两条边，使$s$和$t$不连通，且删掉的边边权和最小。

数据范围：$n \leq 1000,m \leq 3000$

那么对于这种图论的连通性问题，要看这道题考察什么知识：

如果是想在图的联通块里面搞事情，那么一般就是什么并查集、$bfs$、$dfs$、$tarjan$之类的。

但是如果是基于不连通的一些问题，就要想到一些与“不连通”相关的知识点，比如：

## 割点&&割边（桥）

所以这道题就用割边的知识。

### step 1：

如果题目只要求我们删除一条边，使得$s$到$t$不连通，那么我们就先判断s能不能到$t$，如果不能到就直接输出；

如果能就求一遍割边，再在所有的割边里面找一个最小的。

### step 2：

现在有两条边，怎么办？？

其实我们可以分析，如果要让图不连通，肯定要至少断掉一条路径，那么我们就可以先求出一条$s$到$t$的合法路径，然后枚举这个路径上的所有边（**这个路径上一定有答案当中的两条边中的一个**，因为如果没有的话，说明这个路径没有被断开$s$也不能到$t$，就与路径的定义矛盾。）

那么我们就通过枚举的方式得到了第一条边，第二条边呢？？？

其实就是step 1的思路。我么把枚举到的这个边去掉，再判断原图是否联通。

如果不连通，说明一条边就可以了，然后用这条边更新答案；

否则就在砍掉边的图上面跑$tarjan$求割边，如果没有则无解，如果有则更新答案。

最后代码：

## code：

```cpp
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define re register
#define ll long long
#define N 1000
#define M 30000
#define inf 0x7f7f7f7f

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int n,m,s,t;

struct ed{
	int to,w,next;
}edge[M*2+10];int tot=1,head[N+10];
int dnf[N+10],low[N+10],dfstime=0;

inline void adde(int u,int v,int w)
{
	edge[++tot].to=v;
	edge[tot].w=w;
	edge[tot].next=head[u];
	head[u]=tot;
}

bool vis[N+10],bridge[M+10];

inline bool dfs(int x,int f,int ban,vector<int>&p)
{
	vis[x]=1;
	if(x==t)return 1;
	int v;
	for(re int i=head[x];i;i=edge[i].next)
	{
		v=edge[i].to;
		if(v==f||(i>>1)==ban)continue;
		if(!vis[v]&&dfs(v,x,ban,p))
		{
			p.push_back((i>>1));
			return 1;
		}
	}
	return 0;
}

inline void tarjan(int x,int f,int ban)
{
	dnf[x]=low[x]=++dfstime;
	int v,prenum=0;
	for(re int i=head[x];i;i=edge[i].next)
	{
		v=edge[i].to;
		if((i>>1)==ban)continue;
		if(v==f&&!prenum)//防重边 
		{
			++prenum;
			continue;
		}
		if(!dnf[v])
		{
			tarjan(v,x,ban);
			low[x]=min(low[x],low[v]);
			if(low[v]>dnf[x])bridge[(i>>1)]=1;
		}
		else low[x]=min(low[x],dnf[v]);
	}
}

int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		tot=1;
		scanf("%d%d",&s,&t);
		int a,b,c;
		for(re int i=1;i<=m;++i)
		{
			scanf("%d%d%d",&a,&b,&c);
			adde(a,b,c);adde(b,a,c);
		}
		vector<int>path;
		if(!dfs(s,-1,-1,path))
		{
			puts("0\n0");
			continue;
		}
		int len_path=path.size(),ans=inf;
		vector<int>tmp,bian;
		for(re int i=0;i<len_path;++i)
		{
			memset(dnf,0,sizeof(dnf));
			memset(low,0,sizeof(low));
			memset(vis,0,sizeof(vis));
			memset(bridge,0,sizeof(bridge));
			dfstime=0;
			int now=path[i];
			tmp.clear();
			if(!dfs(s,-1,now,tmp))
			{
				if(ans>edge[now*2].w)
				{
					ans=edge[now*2].w;
					bian.clear();
					bian.push_back(now);
				}
				continue;
			}
			for(re int j=1;j<=n;++j)if(!dnf[j])tarjan(j,-1,now);
			int len_tmp=tmp.size();
			for(re int j=0;j<len_tmp;++j)
			{
				if(bridge[tmp[j]])
				{
					if(ans>edge[now*2].w+edge[tmp[j]*2].w)
					{
						ans=edge[now*2].w+edge[tmp[j]*2].w;
						bian.clear();
						bian.push_back(now);
						bian.push_back(tmp[j]);
					}
				}
			}
			
		}if(ans>=inf)puts("-1");
		else
		{
			printf("%d\n%d\n",ans,bian.size());
			int len_bian=bian.size();
			for(re int j=0;j<len_bian;++j)
			{
				printf("%d",bian[j]);
				if(j==len_bian-1)puts("");
				else putchar(' ');
			}
		}
	}
	return 0;
}
```
如果还有什么不懂的话可以私信我哦~~~

---

## 作者：Garbage_fish (赞：3)

为什么写这篇题解？~~因为我感觉其他题解这个方法的写法都好抽象~~（其实是我太菜了）。

方法我用的是跑多遍 Tarjan。

- 如果 $s,t$ 本身就不连通，答案为 $0$，（注意要输出两行 $0$）。
- 跑一遍 Tarjan，找出 $s$ 到 $t$ 之间的最小边权的割边，这是一条边的答案。
- 当前仅当删去 Tarjan 的树边，Tarjan 的树形态可能改变，枚举删除哪一条，跑多次 Tarjan 进行找一条边的操作，这是两条边的答案。

接下来重点讲讲我的实现：

先从 $s$ 出发跑一遍 Tarjan 找割边，将 Tarjan 的树边加入到 $tree$ 里；将割边加入到 $cut$ 里，并将割边用一个布尔数组打上标记。同时，为了方便找 $s$ 到 $t$ 的路径，用 $fr_i$ 表示 $i$ 是从哪条边进入的。

- 小细节：因为有重边，所以需要使用**链式前向星**，边编号**从 $0$ 开始**，这样子 $i$ 和 $(i\operatorname{xor} 1)$ 就是一对边。

如果 $t$ 没有 dfs 序，说明不连通，输出两个 $0$。

否则可以写一个“找答案”函数，从 $t$ 开始按照 $fr$ 所给的路径往回递归，找这条路径上最小的割边。删一条边的答案完成。

接着枚举 $tree$ 里的树边，即枚举删除哪一条。给他们打上标记让 Tarjan 不能进入这些边。每次跑 Tarjan 之前要把 dfs 序全部清零，割边的标记也得全部删掉，但是 memset 会超时，这时候记录的 $cut$ 就派上用场了。

每次跑完 Tarjan 之后，运行“找答案”函数，比较找到两条边最优解即可。

- 还有个小细节，因为链式前向星中，$1$ 号边对应的编号是 $0/1$，$2$ 号边对应的是 $2/3$，所以链式前向星中的第 $i$ 条边对应的是输入中第 $i\div 2+1$ 条边。

```cpp
#include <bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 6e4 + 10, oo = 1e18;
int n, m, s, t;
int mn1 = oo, p1, mn2 = oo, p2;
vector<int> tree, cut;
bool iscut[N], pt;

int head[N], ide;
struct EDGE {
    int v, next, w;
} e[N * 2];
void add(int u, int v, int w) {
    e[ide] = {v, head[u], w};
    head[u] = ide++;
}

int dfn[N], low[N], idx, dis[N], fr[N];
void tarjan(int u, int from) {
    dfn[u] = low[u] = ++idx;
    fr[u] = from;
    for (int i = head[u]; i != -1; i = e[i].next) {
        if (e[i].w == -1)
            continue;
        int v = e[i].v;
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
            if (pt)
                tree.push_back(i);
            if (low[v] > dfn[u]) {
                iscut[i] = iscut[i ^ 1] = true;
                cut.push_back(i);
            }
        } else if (i != (from ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
}
void getans(int u, int &mn, int &p) {
    if (u == s)
        return;
    int from = fr[u] ^ 1;
    if (iscut[from] and mn > e[from].w) {
        mn = e[from].w;
        p = from / 2 + 1;
    }
    getans(e[from].v, mn, p);
}
signed main() {
    IOS;
    memset(head, -1, sizeof head);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    pt = true;
    tarjan(s, -1);
    pt = false;
    if (!dfn[t]) {
        cout << "0\n0";
        return 0;
    }
    getans(t, mn1, p1);
    int del = 0;
    for (int i : tree) {
        int tmp = e[i].w, mn = oo, p;
        e[i].w = e[i ^ 1].w = -1;
        idx = 0;
        for (int j = 1; j <= n; j++)
            dfn[j] = low[j] = 0;
        for (int i : cut)
            iscut[i] = iscut[i ^ 1] = false;
        cut.clear();
        tarjan(s, -1);
        getans(t, mn, p);
        if (mn2 > mn + tmp)
            mn2 = mn + tmp, del = i / 2 + 1, p2 = p;
        e[i].w = e[i ^ 1].w = tmp;
    }
    if (mn1 == mn2 and mn1 == oo)
        cout << -1;
    else if (mn1 < mn2)
        cout << mn1 << "\n1\n" << p1;
    else
        cout << mn2 << "\n2\n" << del << " " << p2;
    return 0;
}

---

## 作者：WIDA (赞：2)

## 700C（$\tt *2600$；图论-缩点、网络流-最小割）

> 一些废话：讲道理我本不该写这篇题解，但是看了一眼这道题的题解区感觉大家讲的都比较杂，百度了一下发现也是如此 ~~可能佬们都觉得这题太基础了所以不愿意多讲~~ 所以我作为一只菜鸟，来综合整理一下。

![image.png](https://s2.loli.net/2023/09/28/y5icJ7og4duIWKZ.png)

需要分类讨论：
- 不需要删边的情况可以很简单的维护搞定（即为判断 $s$ 和 $t$ 是否位于同一个连通块，方法很多，略）；
- 删去一条边的情况即为删去“有效”割边，这里的“有效”指的是位于 $s$ 到 $t$ 的路径上的割边（例如样例一中 $4-5$ 这一条边就不是“有效”的）；我们可以使用 Tarjan 找出全部割边，再使用 dfs 维护有效路径，综合两者即可搞定这一情况；
- 删去两条边的情况有两种做法，其一是暴力枚举，其二是使用网络流求解最小割，随后在残余网络寻找答案，需要较高技巧。下方我将分别讲解。

### 暴力枚举

容易发现最短路径不经过超过 $N$ 个点，所以我们依次枚举 $s$ 到 $t$ 最短路径上的每一条边，然后建立一张不包含这一条边的图，重复上述“删去一条边”的操作。

分析复杂度，我们至多将建立 $N$ 张不同的图，单次查找割边的复杂度为 $\mathcal O(N+M)$ ，所以可以在 $\mathcal O(NM)$ 级别的复杂度内完成。

需要注意的是，非最短路径理论上也可做，但是我的写法超时了，所以改成了最短路径。这一做法细节较多，需要谨慎书写。

### 优雅网络流

~~如果你没有学习过网络流，那么可以无视这一做法。~~ 考虑最小割模型。

首先，对于此前求解出的全部割边，我们显然不能将它们割掉，所以它们的边权置为 $\infty$；对于其他边，由于需要解决“删去**两条边**”最小割，所以我们将全部边的边权加上一个不小于总边权之和的基数 $B$，如此一来，求出的答案在 $[2B,3B)$ 这一范围内时即等价于“删去两条边”的最小割（这一步很巧妙）。

随后我们遍历残留网络获取答案。根据最大流的原理，如果某条边是合法的答案，那么这条边之前的残余流量一定非零，这条边和这条边之后的残余流量一定为零，所以我们只需要使用 dfs 沿着有残余流量的边一路搜索，很容易即可找到目标边。

### 代码环节

首先声明，我并不是 OI 出身，所以码风和正常 OI 不太一样，如果你熟悉 CodeForces 风格那会比较适应；同时我还是个封装怪和 STL 喜爱者，本题中 Tarjan 和网络流的算法细节都依赖于结构体封装实现，数据结构都依赖于 STL，请各位大佬谨慎参考！

对了，如果要在本地进行测试，您可能需要使用 C++17 或更高版本的编译器~

暴力枚举

```cpp
#include <bits/stdc++.h>
using namespace std;

struct E_DCC {
    int n;
    vector<int> h, ver, ne;
    vector<int> dfn, low, col, S;
    int now, cnt, tot;
    vector<bool> bridge; // 记录是否是割边

    E_DCC(int n, int m) : n(n) {
        m *= 2; // 注意链式前向星边的数量翻倍
        ver.resize(m + 1);
        ne.resize(m + 1);
        bridge.resize(m + 1);
        
        h.resize(n + 1, -1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        col.resize(n + 1);
        S.clear();
        tot = cnt = now = 0;
    }
    void add(int x, int y) { // 注意，这里的编号从 0 开始
        ver[tot] = y, ne[tot] = h[x], h[x] = tot++;
        ver[tot] = x, ne[tot] = h[y], h[y] = tot++;
    }
    void tarjan(int x, int fa) { // 这里是缩边双，不是缩点，不相同
        dfn[x] = low[x] = ++now;
        S.push_back(x);
        for (int i = h[x]; ~i; i = ne[i]) {
            int y = ver[i];
            if (!dfn[y]) {
                tarjan(y, i); // 这里储存的是父亲边的编号
                low[x] = min(low[x], low[y]);
                // y 不能到达 x 的任何一个祖先节点，(x - y) 即为一条割边
                // 但是在这里，我们不直接储存 (x - y) 这条边，而是储存边的编号
                // 这样做是为了处理重边的情况（点可能相同，但是边的编号绝对不相同）
                if (dfn[x] < low[y]) {
                    bridge[i] = bridge[i ^ 1] = true;
                }
            } else if (i != (fa ^ 1)) { // 这里同样的，使用边的编号来处理重边情况
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int pre = 0;
            cnt++;
            do {
                pre = S.back();
                S.pop_back();
                col[pre] = cnt;
            } while (pre != x);
        }
    }
    set<array<int, 2>> work() { // [新图的顶点数量, 新图]
        for (int i = 1; i <= n; i++) { // 避免图不连通
            if (dfn[i] == 0) {
                tarjan(i, -1);
            }
        }
        set<array<int, 2>> ans;
        for (int i = 0; i < tot; ++i) {
            if (bridge[i]) { // 如果 (i, i ^ 1) 是割边
                ans.insert({ver[i], ver[i ^ 1]});
            }
        }
        return ans;
    }
};

signed main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    E_DCC scc(n, m);
    vector<vector<array<int, 3>>> ver(n + 1);
    vector<array<int, 4>> edge;
    for (int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        scc.add(x, y);
        ver[x].push_back({y, w, i});
        ver[y].push_back({x, w, i});
        edge.push_back({x, y, w, i});
    }
    
    vector<int> vis(n + 1), type(n + 1);
    type[t] = 1;
    auto zero = [&](auto self, int x, int fa) -> void {
        vis[x] = 1;
        for (auto [y, w, id] : ver[x]) {
            if (y == fa) continue;
            type[x] |= type[y];
            if (vis[y]) continue;
            self(self, y, x);
            type[x] |= type[y];
        }
    };
    zero(zero, s, 0);
    if (!vis[t]) { // 特判不连通
        cout << 0 << '\n';
        cout << 0 << '\n';
        return 0;
    }
    
    int ans = 2E9 + 7;
    vector<int> Id;
    auto chk = scc.work();
    for (auto [x, y, w, id] : edge) {
        if (chk.count({x, y}) && w < ans && type[x] && type[y]) {
            ans = w;
            Id = {id};
        }
    }
    
    queue<int> q;
    q.push(s);
    vector<int> fa(n + 1);
    map<array<int, 2>, array<int, 2>> dic;
    fa[s] = -1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (auto [y, w, id] : ver[x]) {
            if (fa[y]) continue;
            fa[y] = x;
            dic[{x, y}] = {id, w};
            q.push(y);
        }
    }
    vector<array<int, 2>> path;
    int now = t;
    while (true) {
        path.push_back(dic[{fa[now], now}]);
        now = fa[now];
        if (now == s) break;
    }
    
    for (auto [id_, w_] : path) {
        E_DCC graph(n, m);
        for (auto [x, y, w, id] : edge) {
            if (id == id_) continue;
            graph.add(x, y);
        }
        
        vis.assign(n + 1, 0);
        type.assign(n + 1, 0);
        type[t] = 1;
        auto dfs = [&](auto self, int x, int fa) -> void {
            vis[x] = 1;
            for (auto [y, w, id] : ver[x]) {
                if (y == fa || id == id_) continue;
                type[x] |= type[y];
                if (vis[y]) continue;
                self(self, y, x);
                type[x] |= type[y];
            }
        };
        dfs(dfs, s, 0);
        
        auto chk = graph.work();
        for (auto [x, y, w, id] : edge) {
            if (id != id_ && chk.count({x, y}) && w + w_ < ans && type[x] && type[y]) {
                ans = w + w_;
                Id = {id, id_};
            }
        }
    }
    
    if (ans == 2E9 + 7) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
        cout << Id.size() << '\n';
        for (auto it : Id) {
            cout << it << ' ';
        }
    }
}

int __OI_INIT__ = []() {
    ios::sync_with_stdio(0), cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(12);
    return 0;
}();

```

网络流

```cpp
#define int long long

template <typename T> struct Flow_ {
    const int n;
    const T inf = numeric_limits<T>::max();
    struct Edge {
        int to;
        T w;
        Edge(int to, T w) : to(to), w(w) {}
    };
    vector<Edge> ver;
    vector<vector<int>> h;
    vector<int> cur, d;
    
    Flow_(int n) : n(n + 1), h(n + 1) {}
    void add(int u, int v, T c) {
        h[u].push_back(ver.size());
        ver.emplace_back(v, c);
        h[v].push_back(ver.size());
        ver.emplace_back(u, 0);
    }
    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto it : h[x]) {
                auto [y, w] = ver[it];
                if (w && d[y] == -1) {
                    d[y] = d[x] + 1;
                    if (y == t) return true;
                    q.push(y);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        auto r = f;
        for (int &i = cur[u]; i < h[u].size(); i++) {
            auto j = h[u][i];
            auto &[v, c] = ver[j];
            auto &[u, rc] = ver[j ^ 1];
            if (c && d[v] == d[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                c -= a;
                rc += a;
                r -= a;
                if (!r) return f;
            }
        }
        return f - r;
    }
    T work(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, inf);
        }
        return ans;
    }
    vector<int> get(int s) {
        vector<int> vis(n + 1);
        auto dfs = [&](auto self, int x) -> void {
            vis[x] = 1;
            for (auto it : h[x]) {
                auto [y, w] = ver[it];
                if (!vis[y] && w) {
                    self(self, y);
                }
            }
        };
        dfs(dfs, s);
        return vis;
    }
};
using Flow = Flow_<int>;

signed main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    E_DCC scc(n, m);
    vector<vector<array<int, 3>>> ver(n + 1);
    vector<array<int, 4>> edge;
    for (int i = 1; i <= m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        scc.add(x, y);
        ver[x].push_back({y, w, i});
        ver[y].push_back({x, w, i});
        edge.push_back({x, y, w, i});
    }
    
    vector<int> vis(n + 1), type(n + 1);
    type[t] = 1;
    auto zero = [&](auto self, int x, int fa) -> void {
        vis[x] = 1;
        for (auto [y, w, id] : ver[x]) {
            if (y == fa) continue;
            type[x] |= type[y];
            if (vis[y]) continue;
            self(self, y, x);
            type[x] |= type[y];
        }
    };
    zero(zero, s, 0);
    if (!vis[t]) { // 特判不连通
        cout << 0 << '\n';
        cout << 0 << '\n';
        return 0;
    }
    
    Flow flow(n);
    int ans = 1E18;
    vector<int> Id;
    auto chk = scc.work();
    for (auto [x, y, w, id] : edge) {
        if (chk.count({x, y}) && w < ans && type[x] && type[y]) {
            ans = w;
            Id = {id};
        } 
        if (chk.count({x, y})) {
            flow.add(x, y, 1E18);
            flow.add(y, x, 1E18);
        } else {
            flow.add(x, y, w + 1E14);
            flow.add(y, x, w + 1E14);
        }
    }
    
    int f = flow.work(s, t) - 2E14;
    if (0 <= f && f < 1E14 && ans > f) {
        ans = f;
        Id.clear();
        auto flag = flow.get(s);
        for (auto [x, y, w, id] : edge) {
            if (flag[x] ^ flag[y]) {
                Id.push_back(id);
            }
        }
    }
    
    if (ans == 1E18) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
        cout << Id.size() << '\n';
        for (auto it : Id) {
            cout << it << ' ';
        }
    }
}

int __OI_INIT__ = []() {
    ios::sync_with_stdio(0), cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(12);
    return 0;
}();
```

---

## 作者：ZLCT (赞：1)

# CF700C Break Up
## 题目大意
给定 $n$ 个点 $m$ 条边的无向图和两点 $s,t$，求最多割去两条边的 $s,t$ 的最小割。
## 一共割两条边？考虑暴力
- 首先割 $0$ 条边的情况十分容易判断，只需要利用并查集维护 $s,t$ 的连通性，若不连通则直接输出 $0$ 即可（注意题目此时要求输出两行 $0$）。\
但是我们这里不利用并查集，此处为下文做一个铺垫。
- 割一条边的情况我们可以利用 tarjan 把原图缩点，若 $s,t$ 被缩在同一点内，则不可能割一条边把 $s,t$ 割断。否则去找 $s,t$ 之间的最小瓶颈（边权最小）。\
这里需要注意题目可能有重边，需要判断。\
但是如果再写个 tarjan 码量又会增加许多，于是我们观察到 $n,m$ 的范围比较小，那我们直接去枚举删哪一条边，暴力 dfs 判断 $s,t$ 是否连通即可。\
注意此时埋下一个伏笔，我们这时候把有两条重边的情况也考虑进去，并且对所有割去能使 $s,t$ 断开的边权值都赋成正无穷（建议先向下阅读再回来看这一步的目的）。
- 重头戏来了。我们如何处理割两条边的情况呢？\
由于前面我们把 $<2$ 条的情况都处理完了，所以我们可以认为割边的数量一定要最少（必须是 $2$）。所以我们可以把每条边的边权都先加上一个极大值（比前面的正无穷要小，后面会讲），这样最终求出来的最小割一定是边数最小时的最小割。\
但是这样会使割零条边的情况变得最优啊？\
没有关系，我们这里与前面的铺垫相照应，如果最小割求出来为 $0$，那就代表原来的 $s,t$ 就不连通，此时答案就为 $0$。\
那割边为 $1$ 的边也会变得小啊？\
此处就回收了前面的伏笔，由于可以当作割边的边一定不需要再有一条边与它一起构成最小割集（边权非负），所以在找两条边的最小割集时一定不需要割去这些边。\
此时我们还需要注意一个细节，若两个点之间不止两条边，那么割这些边是完全没有意义的，这些边也要赋值为正无穷。\
最后算出的最小割如果在两倍极大值和三倍极大值之间则说明找到了割两条边的方案，减去两倍极大值与前面割边的方案比较即可。
- 输出方案。前两种方案没有什么好说的，开个 set+map 维护两两之间的边集即可。重点是第三种方案，我们在最小割求割集的时候通常直接找满流边或者是否能从 $s$ 走到，但是这个题因为有重边，所以需要判断这条边是否满流且两个端点一个属于 $s$ 集一个属于 $t$ 集（一个能从 $s$ 走到，一个不能）。
## code
这个题的代码细节十分之多，需要真正理解算法思想，一气呵成才能写出。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e10;
const int N=1010;
const int M=30030;
map<pair<int,int>,int>mp;
map<pair<int,int>,int>Get;
map<pair<int,int>,vector<int> >PI;
int n,m,S,T,ans=inf*10,cur[N],dep[N],minid;
bool vis[N],VIS[N];
pair<int,int>cant;
struct EDGE{
    int u,v,c,idu,idv;
}e[M];
struct edge{
    int to,flow,w,fxid,id;
};
vector<edge>G[N];
void add(int u,int v,int w,int id){
    int idu=G[u].size(),idv=G[v].size();
    G[u].push_back({v,0,w,idv,id});
    G[v].push_back({u,0,w,idu,id});
}
bool bfs(){
    queue<int>q;
    memset(vis,0,sizeof(vis));
    memset(dep,-1,sizeof(dep));
    q.push(S);
    dep[S]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto v:G[u]){
            if(v.flow>=v.w)continue;
            if(dep[v.to]!=-1)continue;
            dep[v.to]=dep[u]+1;
            q.push(v.to);
        }
    }
    if(dep[T]==-1)return 0;
    return 1;
}
int dfs(int u,int maxflow){
    if(u==T)return maxflow;
    int flowww=maxflow;
    for(int i=cur[u];i<G[u].size();i=cur[u]+1){
        cur[u]=i;
        auto v=G[u][i];
        if(v.flow>=v.w)continue;
        if(dep[v.to]!=dep[u]+1)continue;
        int nowflow=dfs(v.to,min(maxflow,v.w-v.flow));
        maxflow-=nowflow;
        G[u][i].flow+=nowflow;
        G[v.to][v.fxid].flow-=nowflow;
        if(!maxflow)break;
    }
    return flowww-maxflow;
}
int Dinic(){
    int res=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        res+=dfs(S,inf*100+7);
    }
    return res;
}
bool DFS(int u){
    VIS[u]=1;
    if(u==T)return 1;
    for(auto v:G[u]){
        if(VIS[v.to])continue;
        if(u==cant.first&&v.to==cant.second)continue;
        if(v.to==cant.first&&u==cant.second)continue;
        if(DFS(v.to))return 1;
    }
    return 0;
}
signed main(){
    cin>>n>>m;
    cin>>S>>T;
    for(int i=1;i<=m;++i){
        int u,v,c;cin>>u>>v>>c;
        mp[{u,v}]++;mp[{v,u}]++;
        Get[{u,v}]+=c;Get[{v,u}]+=c;
        PI[{u,v}].push_back(i);
        PI[{v,u}].push_back(i);
        e[i]={u,v,c,(long long)G[u].size(),(long long)(G[v].size())};
        add(u,v,inf+c,i);
    }
    for(int i=1;i<=m;++i){
        if(mp[{e[i].u,e[i].v}]>2){
            G[e[i].u][e[i].idu].w=inf*10;
            G[e[i].v][e[i].idv].w=inf*10;
            continue;
        }
        memset(VIS,0,sizeof(VIS));
        cant={e[i].u,e[i].v};
        if(!DFS(S)){
            if(Get[{e[i].u,e[i].v}]<ans){
                minid=i;
            }
            ans=min(ans,Get[{e[i].u,e[i].v}]);
            G[e[i].u][e[i].idu].w=inf*10;
            G[e[i].v][e[i].idv].w=inf*10;
        }
    }
    int now=Dinic();
    if(!now){
        cout<<"0\n0\n";
        return 0;
    }
    if(now>=inf*3&&ans>=inf*3){
        cout<<"-1\n";
        return 0;
    }
    now-=inf*2;
    if(now>=ans){
        cout<<ans<<'\n';
        cout<<PI[{e[minid].u,e[minid].v}].size()<<'\n';
        for(int p:PI[{e[minid].u,e[minid].v}]){
            cout<<p<<' ';
        }
        return 0;
    }
    cout<<now<<'\n';
    cout<<2<<'\n';
    for(int i=1;i<=n;++i){
        for(auto v:G[i]){
            if(dep[i]!=-1&&dep[v.to]==-1&&v.flow>=v.w){
                cout<<v.id<<' ';
            }
        }
    }
    return 0;
}
```

---

## 作者：Inui_Sana (赞：1)

图论基础题。但是想偏了想了半天。

考虑先对原图做一次 tarjan 求割边。处理 $c=1$ 的答案。

$c=2$ 最自然的想法是枚举所有边，断掉，再重新跑 tarjan。但是会超时。但是不难发现，只有 tarjan 建出的 dfs 树上的树边删去时，树的形态有可能改变。

这些边有 $O(n)$ 个，每个 $O(n+m)$ 暴力跑。否则拿一个可重集，维护每个点返祖边所指向的点的 dfn，每次删去 $(u,v)$ 边时修改此集合，再 $O(n)$ 对 dfs 树做一遍 dfs 处理出 tarjan 的 low 即可。

总时间复杂度 $O(nm)$ 轻松过。

code：

```cpp
int n,m,s,t;
int cur,dfn[N],low[N],fa[N];
bool pd[M],vis[M];
multiset<int> st[N];vector<int> g[N],cut;
int tot=1,head[N];
struct node{int to,nxt,cw;}e[M<<1];
il void add(int u,int v,int w){e[++tot]={v,head[u],w},head[u]=tot;}
void pretar(int u,int f){
	dfn[u]=low[u]=++cur,fa[u]=f;
	go(i,u){
		int v=e[i].to;
		if(!dfn[v]){
			pd[i/2]=1,g[u].eb(v);
			pretar(v,i),low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])cut.eb(i/2);
		}else if(i!=(f^1))low[u]=min(low[u],dfn[v]),st[u].insert(dfn[v]);
	}
}
void dfs(int u,int f){
	low[u]=++cur;
	for(int v:g[u]){
		dfs(v,u),low[u]=min(low[u],low[v]);
		if(low[v]>dfn[u])cut.eb(fa[v]/2);
	}
	low[u]=min(low[u],*st[u].begin());
}
void tarjan(int u,int f){
	dfn[u]=low[u]=++cur,fa[u]=f;
	go(i,u){
		int v=e[i].to;
		if(e[i].cw==-1)continue;
		if(!dfn[v]){
			tarjan(v,i),low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u])cut.eb(i/2);
		}else if(i!=(f^1))low[u]=min(low[u],dfn[v]);
	}
}
il void init(){mems(low,0),cur=0,cut.clear();}
void Yorushika(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	rep(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	pretar(s,0);
	if(!dfn[t])return puts("0\n0"),void();
	int u=t;
	while(u!=s){
		vis[fa[u]/2]=1;
		u=e[fa[u]^1].to;
	}
	int ans=(int)2e9+1,a=-1,b=-1;
	for(int i:cut)if(vis[i]&&e[i*2].cw<ans)ans=e[i*2].cw,a=i,b=0;
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to,v=e[i^1].to;
		if(pd[i/2])continue;
		st[u].erase(st[u].find(dfn[v])),st[v].erase(st[v].find(dfn[u]));
		init(),dfs(s,0);
		for(int j:cut)if(vis[j]&&e[i].cw+e[j*2].cw<ans)ans=e[i].cw+e[j*2].cw,a=i/2,b=j;
		st[u].insert(dfn[v]),st[v].insert(dfn[u]);
	}
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to,v=e[i^1].to;
		if(!pd[i/2])continue;
		int tmp=e[i].cw;
		e[i].cw=e[i^1].cw=-1;
		init(),mems(fa,0),mems(dfn,0);
		tarjan(s,0);
		mems(vis,0),e[i].cw=e[i^1].cw=tmp;
		if(!dfn[t])continue;
		int p=t;
		while(p!=s){
			vis[fa[p]/2]=1;
			p=e[fa[p]^1].to;
		}
		for(int j:cut)if(vis[j]&&e[i].cw+e[j*2].cw<ans)ans=e[i].cw+e[j*2].cw,a=i/2,b=j;
	}
	if(a==-1)puts("-1");
	else if(!b)printf("%d\n1\n%d\n",ans,a);
	else printf("%d\n2\n%d %d\n",ans,a,b);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：cmll02 (赞：1)

先特判掉删 $0$ 条和 $1$ 条边的情况。$0$ 随便乱判，$1$ 可以用 tarjan 跑一遍割边判掉。

接下来是删两条边的情形。

显然如果要删 $2$ 条的话割边肯定不会去删，把割边的代价改为 $\infty$。

否则就是求两条边的最小割，给每个条边加上 $10^{14}$ 的边权跑最小割，这样最小割仅会割 $2$ 条边（多割就会多 $10^{14}$ 的代价，显然不优，少的话必须割 $\infty$，也不优）。

跑最大流即可。

[code](https://codeforces.com/contest/700/submission/140712904)

---

