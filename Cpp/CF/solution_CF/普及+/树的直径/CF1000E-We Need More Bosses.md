# We Need More Bosses

## 题目描述

**题目大意：**

给定一个 $n$ 个点 $m$ 条边的无向图，保证图连通。找到两个点$s,t$，使得$s$到$t$**必须**经过的边最多（一条边无论走哪条路线都经过ta，这条边就是必须经过的边），$2<=n<=3*10^5,1<=m<=3*10^5$

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 1
4 1
5 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
1 2
4 3
3 2
```

### 输出

```
3
```

# 题解

## 作者：小菜鸟 (赞：19)

膜你赛的时候开始看错题意，后来秒出。。。

---

前面有题解提到“强连通分量”？然而这是无向图QwQ

考虑“不是必须经过的边”如何求出。

我们知道同一个**边双连通分量**中，任意两点之间存在至少两条无重边的简单路径。

我们可以发现同一个边双内的点之间没有必须经过的边。。。

于是在此题中，同一边双内的点可以缩在一起，不影响答案。。。

---

由于是无向图，因此缩完边双之后就不存在环，变成了一棵树。

此时，任意两点间的路径都是唯一的了，必须经过的边数就是树上距离。

于是问题变成了求树的直径...

简单说一下求法：任选一个点，找到与它最远的一个点；

再从找到的点出发，找到与它最远的点；

两点距离就是直径。

---

代码供~~抄袭~~参考

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>

const int N=300005,M=600005;

int n,m,head[N],dis[N],from[N];
int cnt,cir_cnt,dfn[N],low[N],cir[N];
int _head[N],_dis[N];

struct Edge
{
    int from,next,to;
};
Edge E[M],_E[M];
bool vis[M];

void add(int u,int v)
{
    static int tot=0;
    E[++tot].next=head[u];
    E[tot].to=v;
    head[u]=tot;
}
void _add(int u,int v)
{
    static int tot=0;
    _E[++tot].next=_head[u];
    _E[tot].from=u;
    _E[tot].to=v;
    _head[u]=tot;
}

void tarjan(int u,int fa)
{
    static std::stack<int> s;
    low[u]=dfn[u]=++cnt;
    s.push(u);
    for(int i=head[u];i;i=E[i].next)
    {
    	int v=E[i].to;
        if(v==fa)continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=std::min(low[u],low[v]);
        }
        else
        {
            if(cir[v]==0)low[u]=std::min(low[u],dfn[v]);
        }
    }
    if(low[u]!=dfn[u])return;
    cir_cnt++;
    while(1)
    {
        int x=s.top();
        s.pop();
        cir[x]=cir_cnt;
        if (x==u)break;
    }
}

int bfs(int s)
{
    int res=s;
    memset(dis,0x3f,sizeof(dis));
    std::queue<int> q;
    q.push(s);
    dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(dis[v]!=0x3f3f3f3f)continue;
            dis[v]=dis[u]+1;
            q.push(v);
            if(dis[v]>dis[res])res=v;
        }
    }
    return res;
}

int _bfs(int s)
{
    int res=s;
    memset(_dis,0x3f,sizeof(_dis));
    std::queue<int> q;
    q.push(s);
    _dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=_head[u];i;i=_E[i].next)
        {
            int v=_E[i].to;
            if(_dis[v]!=0x3f3f3f3f)continue;
            _dis[v]=_dis[u]+1;
            q.push(v);
            if(_dis[v]>_dis[res])res=v;
        }
    }
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    tarjan(1,0);
    for(int u=1;u<=n;++u)
    {
        for(int i=head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(cir[u]!=cir[v])
            {
                _add(cir[u],cir[v]);
            }
        }
    }
    int s=_bfs(cir[1]);
    s=_bfs(s);
    printf("%d",_dis[s]);
}

```

---

交这题的时候大概碰上$system\;test$，断断续续跑了半个小时才出结果，真\*\*酸爽。。。

---

## 作者：TKXZ133 (赞：7)

[We Need More Bosses](https://www.luogu.com.cn/problem/CF1000E)

### 题目大意

给定一张图，找到两个点，使得这两个点之间的所有路径必须经过的边最多。

### 思路分析

我们先来思考一下如果已知两个点，怎么求两个点之间必须经过的边的数量。

在一般的无向连通图中，我们容易发现，其实答案就是两点所在的**边双连通分量之间的割边数量**。

- 显然这就是割边的定义之一。

而我们又知道另一个性质：如果把图缩点成一颗树，那么树上的边与原图中的割边一一对应。

- 还是很显然，想想我们缩点是怎么缩的。

因此，我们就可以轻松的得到做法：先把图缩点成一颗树，再求树的直径。

（这不就是板子套板子吗

### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=1200100;//300000*2*2（双向边，两张图

int n,m,idx=1,cnt,in1,in2,num,p,q;
int to[N],nxt[N],head[N],rhead[N];
int dfn[N],low[N],bridge[N],rid[N];
int dis[N];

void add(int h[],int u,int v){idx++;to[idx]=v;nxt[idx]=h[u];h[u]=idx;}

void tarjan(int s,int last){
    dfn[s]=low[s]=++cnt;
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(i==(last^1)) continue;
        if(!dfn[v]){
            tarjan(v,i);
            low[s]=min(low[s],low[v]);
            if(dfn[s]<=low[v]){bridge[i]=bridge[i^1]=1;}//找桥
        }
        else low[s]=min(low[s],dfn[v]);
    }
}

void dfs_0(int s){
    rid[s]=num;//记录点所在的连通分量
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(bridge[i]||rid[v]) continue;
        dfs_0(v);
    }
}

void dfs_1(int s,int fa,int &u){
    for(int i=rhead[s];i;i=nxt[i]){
        int v=to[i];
        if(v==fa) continue;
        dis[v]=dis[s]+1;
        if(dis[0]<dis[v]){dis[0]=dis[v];u=v;}//找树的直径
        dfs_1(v,s,u);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&in1,&in2);
        add(head,in1,in2);
        add(head,in2,in1);
    }
    tarjan(1,-1);
    for(int i=1;i<=n;i++)
        if(!rid[i]){num++;dfs_0(i);}
    for(int s=1;s<=n;s++)
        for(int i=head[s];i;i=nxt[i])
            if(rid[s]!=rid[to[i]]){
                add(rhead,rid[s],rid[to[i]]);//只用加一次，因为另一个点也会加一次
            }
    dis[1]=0;dfs_1(1,0,p);
    dis[0]=dis[p]=0;dfs_1(p,0,q);//两遍dfs求树的直径
    cout<<dis[0]<<'\n';
    return 0;
}
```

---

## 作者：Nero_Claudius (赞：7)

这道题绝不是紫题。。。

------------

题目的意思其实是让你求一个无向无重边图的直径。

对于求直径的问题我们以前研究过树的直径，可以两遍dfs或者两边bfs解决。

对于图显然不能这样解决，因为图上两点之间的简单路径不唯一。

那怎么解决这个问题呢？

能不能把环都搞掉呢？

于是乎，我们想到了强连通分量。

因此先用tarjan缩一下点，重新建图跑一个直径就可以解决这个问题了。

------------


AC代码如下：

`3053ms 23816kb`

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace StandardIO {

    template<typename T>inline void read (T &x) {
        x=0;T f=1;char c=getchar();
        for (; c<'0'||c>'9'; c=getchar()) if (c=='-') f=-1;
        for (; c>='0'&&c<='9'; c=getchar()) x=x*10+c-'0';
        x*=f;
    }

    template<typename T>inline void write (T x) {
        if (x<0) putchar('-'),x*=-1;
        if (x>=10) write(x/10);
        putchar(x%10+'0');
    }

}

using namespace StandardIO;

namespace Solve {
    
    const int N=300300;
    
    int n,m,bcnt,index;
    vector<int>graph[N],new_graph[N];
    int low[N],dfn[N],belong[N],instack[N],dis[N];
    stack<int>st;
    
    inline void tarjan (int now,int father) {
        low[now]=dfn[now]=++index;
        st.push(now),instack[now]=1;
        for (register int i=0; i<graph[now].size(); ++i) {
            int to=graph[now][i];
            if (to==father) continue;
            if (!dfn[to]) {
                tarjan(to,now);
                low[now]=min(low[now],low[to]);
            } else if (instack[to]) {
                low[now]=min(low[now],dfn[to]);
            }
        }
        if (low[now]==dfn[now]) {
            int v=-1;++bcnt;
            while(v!=now){
                v=st.top(),st.pop();
                instack[v]=0,belong[v]=bcnt;
            }
        }
    }
    
    inline void dfs (int now,int fa) {
        dis[now]=dis[fa]+1;
        for (register int i=0; i<new_graph[now].size(); ++i) {
            int to=new_graph[now][i];
            if (to!=fa) dfs(to,now);
        }
    }
    
    inline int diameter () {
        dfs(1,0);
        int fur=1;
        for (register int i=1; i<=bcnt; ++i) {
            if (dis[i]>dis[fur]) fur=i;
        }
        dfs(fur,0);
        int ans=0;
        for (register int i=1; i<=bcnt; ++i) {
            ans=max(ans,dis[i]);
        }
        return ans-1;
    }

    inline void solve () {
        read(n),read(m);
        for (register int i=1; i<=m; ++i) {
            int x,y;
            read(x),read(y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        for (register int i=1; i<=n; ++i) {
            if (!dfn[i]) tarjan(i,0);
        }
        for (register int i=1; i<=n; ++i) {
            for (register int j=0; j<graph[i].size(); ++j) {
                int to=graph[i][j];
                if (belong[i]!=belong[to]) {
                    new_graph[belong[i]].push_back(belong[to]);
                }
            }
        }
        write(diameter());
    }
}

using namespace Solve;

int main () {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    solve();
}

```

---

## 作者：2021fhm (赞：3)

~~第 521 个 A 掉此题的，来写一篇题解纪念下~~
### 题目大意：
给定一个无向图，要求选择两个点 $s$ 和 $t$，使从 $s$ 到 $t$ 必须经过的边数最多，输出最多经过的边数。

------------
### 解法：

tarjan 缩点后求直径。

------------

### 思路：
容易发现在同一强连通分量里的任意两个点，他们间至少有两条不重复的路线。

所以在强连通分量里的边是对答案没有贡献的。

那么我们就可以考虑忽略强连通分量，利用 tarjan 缩点，把每个强连通分量都看成一个点，这样我们就把图变成了一棵树。

因为树上两点间的路线唯一，那么问题就变成了求树上相距距离最长的两点，也就是树的直径。

树的直径相信大家应该都会了，两遍 dfs 就可以了。

------------

### AC 代码如下：
~~理解了再抄~~
```c
#include<bits/stdc++.h>
using namespace std;

struct edge
{
	int from,to;
}e[300005];
vector<int>a[300005],G[300005];
int n,m,dfn[300005],low[300005],st[300005],bj[300005],bel[300005],top,cnt,Cnt;
void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++cnt;
	st[++top]=x;
	bj[x]=1;
	int l=a[x].size();
	for(int i=0;i<l;i++)
	{
		int v=a[x][i];
		if(v==fa)	continue;
		if(!dfn[v])
		{
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
		}
		else
		{
			if(bj[v])	low[x]=min(low[x],low[v]);
		}
	}
	if(dfn[x]==low[x])
	{
		Cnt++;
		while(1)
		{
			int rnm=st[top];
			top--;
			bel[rnm]=Cnt;
			bj[rnm]=0;
			if(rnm==x)	break;
		}
	}
}
int dep[300005],mx,S;
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	if(dep[x]>mx)
	{
		mx=dep[x];
		S=x;
	}
	int l=G[x].size();
	for(int i=0;i<l;i++)
	{
		int v=G[x][i];
		if(v==fa)	continue;
		dfs(v,x); 
	}
}
int dep2[300005],ans;
void dfs2(int x,int fa)
{
	dep2[x]=dep2[fa]+1;
	ans=max(ans,dep2[x]-1);
	int l=G[x].size();
	for(int i=0;i<l;i++)
	{
		int v=G[x][i];
		if(v==fa)	continue;
		dfs2(v,x); 
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
		e[i].from=x,e[i].to=y;
	}
	tarjan(1,0);
	for(int i=1;i<=m;i++)
	{
		int X=bel[e[i].from],Y=bel[e[i].to];
		if(X==Y)	continue;
		G[X].push_back(Y);
		G[Y].push_back(X);
	}
	dfs(1,0);
	dfs2(S,0);
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：Aiopr_2378 (赞：3)

## 题意整理：

给定一张无向图，求任意两点间 **必须经过** 的路径条数最多为多少。

## 解题思路：

我们需要求出 **必须经过** 的边数，考虑什么情况下 **一条边对答案没有贡献**，即这条边在这个路径中可以用别的边代替掉。

能代替掉一条边，等价于：对于一条边 $(u,v)$，删去它，仍然可以通过别的路径，使得存在路径 $u\to x_1\to\cdots\to x_k\to v$。

仔细想想，这其实就是 **边双连通分量** 的定义嘛，在一个 E-DCC 中，所有的边都是可以替换掉的，剩下的边（也就是对答案有贡献的边）必定是 **割边**（仔细想想定义就可以得出）。

所以我们可以将每个 **极大的边双连通分量** 缩成一个点，也就是直接否定了这个边双中的边的贡献，然后保留的边就是 **割边**。去掉边双连通分量后，整个图就 **没有了环**，成为一颗 **树**。将问题转化为一棵树上，两点间距离的最大值。所以我们就在树上求 **直径** 便是答案。

## 参考代码：

```cpp
#include<iostream>
using namespace std;
#define MAXN 300005
int head1[MAXN],nxt1[MAXN<<1],to1[MAXN<<1],tot1=1;
int head2[MAXN],nxt2[MAXN<<1],to2[MAXN<<1],tot2=1;
int dfn[MAXN],low[MAXN],tick;
int s[MAXN],top,bel[MAXN],idx,n,m;
int ans,f[MAXN];
void add(int x,int y){
    to1[++tot1]=y,nxt1[tot1]=head1[x],head1[x]=tot1;
}
void add_(int x,int y){
    to2[++tot2]=y,nxt2[tot2]=head2[x],head2[x]=tot2;
}
void dfs(int u,int lst){//tarjan求边双连通分量
    dfn[u]=low[u]=++tick;
    s[++top]=u;
    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if((i^1)==lst) continue;
        if(!dfn[v]){
            dfs(v,i);
            low[u]=min(low[u],low[v]);
        }
        else if(!bel[v]) low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        int v;
        idx++;
        do{
            v=s[top--];
            bel[v]=idx;
        }while(v!=u);
    }
}
void DFS(int u,int fa){//树形dp求树的直径
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        if(v==fa) continue;
        DFS(v,u);
        ans=max(ans,f[u]+f[v]+1);
        f[u]=max(f[u],f[v]+1);
    }
}
int main(){
    cin>>n>>m;
    for(int x,y,i=1;i<=m;i++){
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) dfs(i,0);
    }
    for(int u=1;u<=n;u++){//缩点建树
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            if(bel[v]!=bel[u]) add_(bel[u],bel[v]);
        }
    }
    DFS(1,0);
    cout<<ans;
    return 0;
}
```


---

## 作者：RyexAwl (赞：3)

本题大多数题解均用到连通分量、缩点等科技，但其实本题随便建生成森林树上差分处理出边权跑生成森林直径即可。

具体地：我们发现一个边是“必经边”当且仅当是在该图的生成森林中的“极大生成树”连接两个生成森林的唯一边。

其充分性比较显然，在其连接的两棵生成树内各选一点即可确定一条必经该边的路径。

其必要性也比较好证明：对于不在生成树上的边一定不会是“必经边”，假定该边为$<u,v>$，那么任一经过$<u,v>$的路径一定可以用树上路径$(u,v)$替换$<u,v>$因此一定不是必经边。 且我们可以发现**任一“必经边”$<x,y>$在原图上删除后其点$x,y$一定属于两个不同的连通块**。同样可以反证其充分性与必要性在此不浪费篇章具体介绍。而满足如上条件当且仅当其在生成树上连接的两棵树间不存在任意一条非树边。

![](https://cdn.luogu.com.cn/upload/image_hosting/vgl3ts4j.png)

例如边$<3,4>$，其满足若将边$<3,4>$，断开之后一定会分裂成两个连通块。

上述结论的必要性与充分性证明也较为简单。

那么我们具体地要怎么处理呢？

我们发现如果一条边连接的两个部分有“非树边”，假定这条“非树边”连接的两个点是$u,v$，那么树上路径$(u,v)$一定会经过这条边。

我们称树边$<u,v>$被非树边$<x,y>$覆盖当且仅当树边$<u,v>$在点$x,y$的树上路径$(x,y)$上。

那么接下来的做法就比较套路了：

$1.$对于图的每个连通块建一棵生成树形成生成森林，分离出非树边。

$2.$用树上差分维护一条边被“覆盖”的次数。

$3.$对于被覆盖次数为$0$的边修改点权为$1$。

$4.$对于生成森林中的每棵生成树跑出一条直径将长度取$\max$。

时间复杂度$O(M\ \log (NM))$

这时候可能有和窝一样的小可爱会迷惑，难道任意一棵生成树的解都是最优解吗qwq？


首先，如果一条边在一棵生成树上是“非树边”那么他一定不是“必经边”，因为其一定可以被替换成一段树上路径。

而对于任一“必经边”在任一棵生成树上一定是“树边”。因为如果其不是树边，那么该连通块的生成树一定不连通。

而对于任一路径$(u,v)$其经过必经边必定只有一种，因为如果我们找出了两种不同的必经边方案意味着我们找到的“必经边”至少有一条可以不被“经过”与“必经边”的定义矛盾。


```cpp
#include <iostream>
#include <cstring>

namespace wxy{
	const int N = 3e5 + 5;
	#define x first
	#define y second
	typedef std::pair<int,int> PII;
	int head[N],fail[N << 1],edge[N << 1],fa[N][30],d[N],ff[N],tot;
	int n,m,ans,aw[N],w[N],df[N];
	bool vis[N],v[N],root[N];
	PII edg[N];
	inline void add(int x,int y){
        edge[++tot] = y;
        fail[tot] = head[x];
        head[x] = tot;
    }
    inline void dfs1(int x){
        for (int i = 1; (1 << i) <= d[x]; i++)
            fa[x][i] = fa[fa[x][i - 1]][i - 1];
        for (int i = head[x];i;i =fail[i]){
            int v = edge[i];
            if (d[v] == -1){
                d[v] = d[x] + 1;
                fa[v][0] = x;
                dfs1(v);
            }
        }
    }
    inline int lca(int x,int y){
        if (d[x] < d[y]) std::swap(x,y);
        int i,j;
        for (i = 0;(1 << i) <= d[x]; i++);
        for (j = i; j >= 0; j--)
            if (d[fa[x][j]] >= d[y]) x = fa[x][j];
        if (x == y) return x;
        for (j = i; j >= 0; j--){
            if (fa[x][j] != fa[y][j]){
                x = fa[x][j];
                y = fa[y][j];
            }
        }
        return fa[x][0];
    }
    inline void dfs2(int x){
    	for (int i = head[x];i;i = fail[i]){
    		int v = edge[i];
    		if (v == fa[x][0]) continue;
    		dfs2(v);
    		aw[x] += aw[v];
    	}
    	if (aw[x] == 0) w[x] = 1;
    }
    inline void dp(int x){
    	for (int i = head[x];i; i = fail[i]){
    		int v = edge[i];
    		if (v == fa[x][0]) continue;
    		dp(v);
    		ans = std::max(ans,df[x] + df[v] + w[v]);
    		df[x] = std::max(df[x],df[v] + w[v]);
    	}
    }
    inline int get(int x){
    	if (ff[x] == x) return x;
    	else return ff[x] = get(ff[x]);
    }
    inline void merge(int x,int y){ff[get(x)] = ff[get(y)];}
	inline void main(){
		memset(d,-1,sizeof d);ans = tot = 0;
		std::cin >> n >> m;
		for (int i = 1; i <= n; i++) ff[i] = i;
		for (int i = 0; i < m; i++){
			int a,b;std::cin >> a >> b;
			edg[i] = std::make_pair(a,b);
			if (get(a) == get(b)) continue;
			vis[i] = true;merge(a,b);add(a,b);add(b,a);
		}
		for (int i = 1; i <= n; i++){
			if (d[i] == -1){
				root[i] = true;
				d[i] = 0;
				dfs1(i);
			}
		}
		for (int i = 0; i < m; i++){
			if (!vis[i]){
				int a = edg[i].x,b = edg[i].y;
				aw[a]++;aw[b]++;
				aw[lca(a,b)] -= 2;
			}
		}
		for (int i = 1; i <= n; i++)
			if (root[i]) dfs2(i);
		for (int i = 1; i <= n; i++)
			if (root[i]) dp(i);
		std::cout << ans;
	}
}signed main(){wxy::main();return 0;}
```


---

## 作者：shame_djj (赞：3)

一遍 AC ，非常舒适，写篇题解，纪念一下

原题链接[【We Need More Bosses】](https://www.luogu.org/problem/CF1000E)

首先读题，重点应该放在一个地方，那就是**必须经过的边**

何为必须经过的边？

（~~楼主太懒，懒得画图~~）

例如

1 -- 2, 2 -- 3, 1 -- 3, 3 -- 4，这个图，

如果我们要从 1 号点走到 4 号点，

一共有两条路径，一条是 1 -> 2 -> 3 -> 4

另一条是 1 -> 3 -> 4

这就是非常明显的规律了：图中在“环”上的边都一定不是“必须经过的边”

因为在无向图上从环上一点到环上另外一点一定有至少两条路径

而所谓的环就是边双联通分量了

那么就只要求一个边双，然后缩下点，最后再求一个直径就好了

算法流程

		1、求边双：求出来桥，然后还连着的就属于同一个边双

		2、缩点：遍历一下原图，重建新图就好了

		3、求直径：任意找一个点，找到与这个点距离最远的点，再找到与这个点距离最远的点，这个距离就是直径

大家写代码时要~~像我一样~~有清晰的思路

代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxm = 1e6 + 10;
const int maxn = 3e5 + 10;

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
    for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

int ver[maxm], nxt[maxm], head[maxn], tot = 1;
int dfn[maxn], low[maxn], cnt_;
bool cut[maxm];

void add (int u, int v) {
    ver[++ tot] = v, nxt[tot] = head[u], head[u] = tot;
    ver[++ tot] = u, nxt[tot] = head[v], head[v] = tot;
}

void tarjan (int x, int in_edge) {
    dfn[x] = low[x] = ++ cnt_;
    for (register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan (y, i);
            low[x] = min (low[x], low[y]);
            if (low[y] > dfn[x])
                cut[i] = cut[i ^ 1] = 1;
        }
        else if (i != (in_edge ^ 1))
            low[x] = min (low[x], dfn[y]);
    }
}

int id[maxn], gg;
void dfs (int x) {
    id[x] = gg;
    for (register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (id[y] || cut[i]) continue;
        dfs (y);
    }
}

vector <int> h[maxn];
bool vis[maxn];
int s_, id_;

void dfs_ (int x, int s) {
    vis[x] = 1;
    if (s > s_)
        s_ = s, id_ = x;
    for (register int i = 0; i < h[x].size (); i ++)
        if (!vis[h[x][i]])
            dfs_ (h[x][i], s + 1);
}

void djj_lxy () {
    int n = read(), m = read();
    for (; m; m --)
        add (read (), read ());
    for (register int i = 1; i <= n; i ++)
        if (!dfn[i]) tarjan (i, 0);
    for (register int i = 1; i <= n; i ++)
        if (!id[i]) ++ gg, dfs (i);
    for (register int i = 1; i <= n; i ++)
        for (register int j = head[i]; j; j = nxt[j])
            if (id[i] != id[ver[j]])
                h[id[i]].push_back (id[ver[j]]);
    dfs_ (1, 1);
    memset (vis, 0, sizeof vis);
    dfs_ (id_, 1);
    printf ("%d\n", s_ - 1);
}

int main () {
    djj_lxy ();
}

```

那这道题就这样吧，大家注意在新 Noip 前要把知识好好的复习一遍

祝大家新 Noip rp ++

也希望自己能更努力一些，加油。

---

## 作者：qnqfff (赞：0)

思路：

先思考如果是个树怎么做,很显然就是树的直径,但如果是个图呢?

对于一个无向图中的两个点,如果两点路径上存在环,那么环上的边一定不是必须经过的边,即环上的边不对答案产生贡献,于是我们可以把所有环去掉。

把无向图中的环去掉,这不就是边双连通分量缩点吗,在缩点后图就变成了树,直接求树的直径即可。

整理一下：

1. 边双连通分量缩点

1. 求树的直径

代码

```cpp
#include<bits/stdc++.h>
#define N 300010
using namespace std;
inline int read(){
	char ch=getchar();int s=0,f=1;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') ch=getchar(),f=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return f*s;
}
inline void write(long long x) {
	if(x<0) putchar('-'),x=-x;
	char s[25];
	int n=0;
	while(x||!n){
		s[n++]='0'+x%10,x/=10;
	}
	while(n--) putchar(s[n]);
}
int n,m,s,scc,w[N],dfn[N],low[N],t,st[N],top,vis[N],belong[N],dp1[N],dp2[N],ans;
vector<int>e[N],ee[N];
void tarjan(int now,int fa){//tarjan求边双连通分量
	dfn[now]=low[now]=++t;st[++top]=now;vis[now]=1;
	for(int i=0;i<e[now].size();i++)
		if(!dfn[e[now][i]]&&e[now][i]!=fa)
			tarjan(e[now][i],now),low[now]=min(low[now],low[e[now][i]]);
		else if(vis[e[now][i]]&&e[now][i]!=fa)
			low[now]=min(low[now],dfn[e[now][i]]);
	if(dfn[now]==low[now]){
		scc++;
		do{
			vis[st[top]]=0;
			belong[st[top]]=scc;
		}while(st[top--]!=now);
	}
}
void dp(int now,int fa){//树形dp求树的直径
	for(int i=0;i<ee[now].size();i++)
		if(ee[now][i]!=fa){
			dp(ee[now][i],now);
			if(dp1[now]<dp1[ee[now][i]]+1)
				dp2[now]=dp1[now],dp1[now]=dp1[ee[now][i]]+1;
			else if(dp2[now]<dp1[ee[now][i]]+1)
				dp2[now]=dp1[ee[now][i]]+1;
			ans=max(ans,dp1[now]+dp2[now]);
		}
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	tarjan(1,0);
	for(int i=1;i<=n;i++)
		for(int j=0;j<e[i].size();j++)
			if(belong[i]!=belong[e[i][j]])
				ee[belong[i]].push_back(belong[e[i][j]]);//缩点
	dp(belong[1],0);
	write(ans);
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1000E)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/04/18/CF1000E%20We%20Need%20More%20Bosses/)

## 前言

这题本来是寒假听fls大佬讲课的时候课上讲的例题，但是当时由于太菜，没写出来，最近把这题给补了。

### 前置芝士

tarjan 算法，e-DCC 的缩点，树的直径

## 分析

看到题目中**必须经过**这几个字，就想起了 e-DCC 的一个重要性质: 同一个 e-DCC 中的任意两点都有两条及以上相离的路径(在[冗余路径](https://www.luogu.com.cn/problem/P2860)这一题中也有所体现)，我们来简单证明一下。

如果同一个 e-DCC 中的两个点 $u,v$ 不存在相离的路径，那么就意味着，它们之间必定存在着一些必经边，如果把边删去，那么 $u,v$ 两点就不连通，也就是说这些边是这个图中的割边，与 e-DCC 的性质相矛盾。

那么我们就可以考虑 e-DCC 缩点，缩完点后建一张新图。显然，新图是一个**森林**，同一个连通块中每一条边都是必经边，那么我们就直接找一下树的直径就可以了。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, M = N << 1;
int h[N], e[M], ne[M], idx;
int H[N], E[M], NE[M];
int dfn[N], low[N], id[N], stk[N];
bool vis[N];
int res;
int cnt, tt, t;
int d1[N], d2[N];

inline void add(int h[], int e[], int ne[], int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

inline void tarjan(int u, int p) // e-DCC 缩点板子
{
    dfn[u] = low[u] = ++t;
    stk[++tt] = u;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (!dfn[v])
        {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        }
        else if (i != (p ^ 1))
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        int v;
        cnt++;
        do {
            v = stk[tt--];
            id[v] = cnt;
        } while (u != v);
    }
}

inline void dfs(int u, int p) // 求一个连通块中树的直径
{
    vis[u] = true;
    for (int i = H[u]; ~i; i = NE[i])
    {
        int v = E[i];
        if (v == p) continue;
        dfs(v, u);
        int d = d1[v] + 1;
        if (d > d1[u]) d2[u] = d1[u], d1[u] = d;
        else if (d > d2[u]) d2[u] = d;
    }
    res = max(res, d1[u] + d2[u]);
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(H, -1, sizeof H);
    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(h, e, ne, x, y);
        add(h, e, ne, y, x);
    }
    for (int i = 1; i <= n; i++)
        if (!id[i])
            tarjan(i, -1);
    idx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            if (id[i] != id[k])
                add(H, E, NE, id[i], id[k]); // 建新图
        }
    for (int i = 1; i <= cnt; i++)
        if (!vis[i]) // 注意原图不一定连通
            dfs(i, -1);
    printf("%d\n", res);
    return 0;
}
```



---

## 作者：GIFBMP (赞：0)

我们阅读题目，很容易发现：当两个点处于同一个边双中时，这两个点一定不存在**必须经过的边**。

而当两个点处于不同的边双中时，**必须经过的边**的数量就是它们路径上的割边数量。

于是我们求出边双，缩点然后跑最长链即可。

Code：

```cpp
#include <cstdio>
#include <vector>
using namespace std ;
const int MAXN = 3e5 + 10 ;
int n , m , dfn[MAXN] , low[MAXN] , stack[MAXN] , top , cntc , col[MAXN] , cnt ;
int dis[MAXN] , dis2[MAXN] , maxx = -1 , p , ans = -1 ;
bool vis[MAXN] ;
vector <int> G[MAXN] , G2[MAXN] ;
int min (int a , int b) {
	return a < b ? a : b ;
}
void tarjan (int x , int fa) {
	dfn[x] = low[x] = ++cnt ;
	stack[++top] = x ;
	vis[x] = 1 ;
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i] ;
		if (v == fa) continue ;
		if (!dfn[v]) {
			tarjan (v , x) ;
			low[x] = min (low[x] , low[v]) ;
		}
		else if (vis[v])
			low[x] = min (low[x] , dfn[v]) ;
	}
	if (dfn[x] == low[x]) {
		cntc++ ;
		while (1) {
			col[stack[top]] = cntc ;
			//printf ("%d " , stack[top]) ; 
			vis[stack[top]] = 0 ;
			if (stack[top--] == x) break ;
		}
		//printf ("\n") ;
	}
} 
void dfs (int x , int fa) {
	if (dis[x] > maxx) {
		maxx = dis[x] ;
		p = x ;
	}
	for (int i = 0 ; i < G2[x].size () ; i++) {
		int v = G2[x][i] ;
		if (v == fa) continue ;
		dis[v] = dis[x] + 1 ;
		dfs (v , x) ;
	}
}
void dfs2 (int x , int fa) {
	if (dis2[x] > ans) ans = dis2[x] ;
	for (int i = 0 ; i < G2[x].size () ; i++) {
		int v = G2[x][i] ;
		if (v == fa) continue ;
		dis2[v] = dis2[x] + 1 ;
		dfs2 (v , x) ;
	}
}
int main () {
	scanf ("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= m ; i++) {
		int u , v ;
		scanf ("%d %d" , &u , &v) ;
		G[u].push_back (v) ;
		G[v].push_back (u) ;  
	} 
	tarjan (1 , 0) ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 0 ; j < G[i].size () ; j++) {
			int v = G[i][j] ;
			if (col[i] != col[v])
				G2[col[i]].push_back (col[v]) ; 
		}
	dfs (1 , 0) ;
	dfs2 (p , 0) ;
	printf ("%d" , ans) ;
	return 0 ;
}
```

---

## 作者：大菜鸡fks (赞：0)

缩点以后 求树直径

(代码去掉vis数组后会有问题，不知道为什么。错误找了好久都没找出来)

不去掉vis数组是可以过的。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=6e5+5;
struct edge{
	int link,next;
}e[N<<1],E[N<<1];
int tot,head[N],n,m,h[N];
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read(); m=read();
	for (int i=1;i<=m;i++){
		insert(read(),read());
	}
}
int dfn[N],low[N],scc,belong[N],tim,top,stack[N];
inline void pop(){
	belong[stack[top--]]=scc;
}
void tarjan(int u,int fa){
	dfn[u]=low[u]=++tim; stack[++top]=u;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v==fa) {
			fa=0;
			continue;
		}
		if (!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if (dfn[u]<low[v]){
				scc++;
				while (top&&stack[top]!=v) pop();
				pop();
			}
		}else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}
inline void Add_edge(int u,int v){
	E[++tot]=(edge){v,h[u]}; h[u]=tot;
}
inline void ins(int u,int v){
	Add_edge(u,v); Add_edge(v,u);
}
int dis[N];
bool vis[N];
void dfs(int u,int fa){
	dis[u]=dis[fa]+1; vis[u]=1;
	for (int i=h[u];i;i=E[i].next){
		int v=E[i].link;
		if (v!=fa&&!vis[v]){
			dfs(v,u);
		}
	}
}
inline void solve(){
	tot=0;
	tarjan(1,0);
	if (top) scc++;
	while (top) pop();
	for (int u=1;u<=n;u++){
		int p=belong[u];
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link; int q=belong[v];
			if (p!=q){
				ins(p,q);
			}
		}
	}
	dfs(1,0); int mx=1;
	for (int i=2;i<=scc;i++){
		if (dis[i]>dis[mx]){
			mx=i;
		}
	}
	memset(vis,0,sizeof(vis));
	dfs(mx,0); mx=0;
	for (int i=1;i<=scc;i++){
		mx=max(mx,dis[i]);
	}
	writeln(mx-1);
}
int main(){
	init(); 
	solve();
	return 0;
} 
```

---

