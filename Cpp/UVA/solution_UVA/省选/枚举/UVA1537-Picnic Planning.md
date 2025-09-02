# Picnic Planning

## 题目描述

[PDF](https://onlinejudge.org/external/15/p1537.pdf)
# 题目背景
The Contortion Brothers是一组著名的马戏团小丑，以其令人难以置信的能力而闻名于世即使是最小的车辆，也能容纳无限的数量。在淡季期间，兄弟俩喜欢在当地公园聚在一起参加年度拳师大会。然而,兄弟俩不仅在狭小的空间里很紧张，而且在金钱上也很紧张，所以他们试图找到让每个人都参加聚会的方法，尽量**减少**每个人的汽车行驶里程（从而节省气体、磨损等）。为此，他们愿意在必要时把自己塞进少数几个车，尽量减少所有汽车的总里程。这经常导致许多兄弟开车去一个兄弟家，除了一辆车外，其他车都停在那里，然后挤进剩下的一个。然而，公园有一个限制：野餐地点的停车场可以只能容纳**有限数量**的汽车，因此必须将其纳入整体最小的计算中。同时，由于公园的入场费，一旦任何兄弟的车到达公园，它就会停在那里;他不会让乘客下车，然后去接其他兄弟。现在，对于你的普通马戏团来说，解决这个问题是一个挑战，所以留给你写一个程序来解决他们的最小化问题。

# 题解

## 作者：ANJHZ (赞：18)

题意：

求一颗生成树使"Park"顶点的度数不超过s，且其边权之和最小。

也就是所谓的K度限制最小生成树。

关于此类问题做法的证明请自行百度。~~我自己讲不清楚~~

做法：

1. 将限制了度数的"Park"顶点去除，图分成cnt个联通快。

2. 假如cnt>s 无解，但题目保证有解

3. 对于每个联通块，求最小生成树

4. 从每个联通块连一条最小的边到"Park"点，这样就构造出了度数为cnt的度限制最小生成树，其边权之和记作tree[cnt].

5. 用dfs预处理从"Park"点出发到所有点的路径上最大边的全值best[i]

6. 枚举从"Park"点出发的边e，设与之相连的点为v，得出e.val-best[v]最大的边。 若e1是e.val-best[v]最大的边，那么tree[i]=tree[i-1]+e1.val-best[v], 连接e1.

7. dfs更新best数组，重复4-7直到求出tree[s]

8. ans=min(tree[i])(i>=cnt&&i<=s)


贴代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int t;
int m;
map <string,int> name;
int n,k;
int head,tail;
int qu[31];
int root,cnt;
string pp="Park";
int vis[31];
int dist[31];
int link[31][31];
int g[31][31];
int minto[31];
int pre[31];
int used[31];
int in[31];
int tree[301];
int best[31];
int max(int p,int q){return p>q?p:q;}
int min(int p,int q){return p<q?p:q;}
void dfs(int now)
{
    if(now==root) return;
    vis[now]=cnt;
    for(int i=1;i<=n;i++) if(g[now][i]<1e8&&vis[i]==0) dfs(i);
}
void upd(int now,int fa)
{
    pre[now]=fa;
    if(now!=root)best[now]=max(best[fa],g[fa][now]);
    in[now]=1;
    int i;
    for(i=1;i<=n;i++) if(link[now][i]&&(!in[i])) upd(i,now);
}
void init()
{
    int i,j,dist;
    string name1,name2;
    n=0;
    scanf("%d",&m);
    memset(g,0x3f3f3f3f,sizeof g);
    memset(minto,-1,sizeof minto);
    memset(vis,0,sizeof vis);
    name.clear();
    for(i=1;i<=m;i++)
    {
        cin>>name1>>name2>>dist;
        if(name.count(name1)==0) name[name1]=++n;
        if(name.count(name2)==0) name[name2]=++n;
        g[name[name1]][name[name2]]=min(g[name[name1]][name[name2]],dist);
        g[name[name2]][name[name1]]=min(g[name[name2]][name[name1]],dist);
    }
    scanf("%d",&k);
    cnt=0;
    root=name[pp];
    for(i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            if(i!=root) cnt++;
            dfs(i);
        }
    }
    for(i=1;i<=n;i++)
    {
        if(i==root) continue;
        if(minto[vis[i]]==-1) minto[vis[i]]=i;
        else if(g[root][minto[vis[i]]]>g[root][i]) minto[vis[i]]=i;
    }
}
void work()
{
    int ans=0;
    int i,j,mi,now;
    memset(dist,0x3f3f3f3f,sizeof dist);
    memset(best,-0x3f3f3f3f,sizeof best);
    memset(used,0,sizeof used);
    memset(pre,0,sizeof pre);
    memset(in,0,sizeof in);
    memset(link,0,sizeof link);
    in[root]=1;
    dist[root]=0;
    for(i=1;i<=cnt;i++)
    {
        dist[minto[i]]=g[root][minto[i]];
        pre[minto[i]]=root;
        used[minto[i]]=1;
    }
    for(i=2;i<=n;i++)
    {
        mi=-1;
        for(j=1;j<=n;j++)
        {
            if(in[j]==0)
            {
              if(mi==-1) mi=j;
              else if(dist[mi]>dist[j]) mi=j;
            }
        }
        in[mi]=1;
        ans+=dist[mi];
        for(j=1;j<=n;j++) if(in[j]==0&&g[mi][j]<dist[j]) dist[j]=g[mi][j],pre[j]=mi;
    }
    for(i=1;i<=n;i++) link[pre[i]][i]=link[i][pre[i]]=1;
    memset(in,0,sizeof in);
    upd(root,0);
    tree[cnt]=ans;
    for(i=cnt+1;i<=k;i++)
    {
        mi=-1;
        for(j=1;j<=n;j++)
        {
            if(j==root||used[j]==1) continue;
            if(mi==-1) mi=j;
            else if(g[root][mi]-best[mi]>g[root][j]-best[j]) mi=j;
        }
        link[root][mi]=link[mi][root]=1;
        used[mi]=1;
        ans+=g[root][mi];
        now=mi;
        while(now!=root)
        {
            if(g[pre[now]][now]==best[mi])
            {
                link[pre[now]][now]=link[now][pre[now]]=0;
                ans-=best[mi];
                break;
            }
            now=pre[now];
        }
        memset(in,0,sizeof in);
        upd(root,0);
        tree[i]=ans;
    }
    ans=1e9;
    for(i=cnt;i<=k;i++) ans=min(ans,tree[i]);
    printf("Total miles driven: %d\n",ans);
    if(t)printf("\n");
}
int main()
{
    //freopen("data.txt","r",stdin);
    scanf("%d",&t);
    while(t--)
    {
        init();
        work();
    }
    return 0;
}

```

---

## 作者：OldDriverTree (赞：8)

rt，先考虑 $1$ 号节点的度数恰好为 $s$ 的做法，就和 [这题](https://www.luogu.com.cn/problem/P5633) 一样，做法参考 [这篇题解](https://www.luogu.com.cn/blog/tiw-air-oao/solution-p5633)。

但是可以发现 $1$ 到每个连通块的最短路加完后，再加边总边权和可能会更小，一边加边一边对当前生成树的总权值和取 $\min$ 即可，时间复杂度 $O(Tm\log m)$，喜提最优解 rk2。

```
#include<bits/stdc++.h>
using namespace std;
const int N=31,inf=1e9;

struct edge
{
    int x,y,z;
    bool operator <(edge b)const {
        return z<b.z;
    }
};
vector<int> a;
vector<edge> e;
int T,n,m,k,cnt,res,ans;
int fa[N],val[N],dis[N];
unordered_map<string,int> id;

int get() {
	string s; cin>>s;
    if (!id[s]) id[s]=++n,fa[n]=n,
    val[n]=inf; return id[s];
}
int find(int x) {
    if (fa[x]!=x) fa[x]=find(fa[x]);
    return fa[x];
}
bool merge(int x,int y,int z)
{
    x=find(x),y=find(y);
    if (x==y) return false;
    if (val[x]<val[y]) swap(x,y);
    dis[x]=z,fa[x]=y;
    return true;
}
void kruskal()
{
    sort(e.begin(),e.end() );

    for (edge now:e)
        if (merge(now.x,now.y,now.z) )
            res+=now.z;
}
int main()
{
	scanf("%d",&T);
	
    while (T--)
	{
		a.clear(),e.clear(),id.clear();
		scanf("%d",&m),id["Park"]=n=1;
		cnt=res=0;
		
		while (m--) 
		{
			int x,y,z;
			x=get(),y=get(); scanf("%d",&z);
			if (x==1) val[y]=min(val[y],z);
			else if (y==1) val[x]=min(val[x],z);
			else e.push_back( {x,y,z} );
		}
		scanf("%d",&k); kruskal();
		for (int i=2;i<=n;i++) if (fa[i]==i)
			cnt++,res+=val[i],val[i]=inf;
			
		for (int i=2;i<=n;i++) if (val[i]!=inf)
			a.push_back(val[i]-dis[i]);
		
		sort(a.begin(),a.end() ); ans=res;
		for (int x:a) if (cnt<k) res+=x,cnt++,ans=min(ans,res);
		printf("Total miles driven: %d\n",ans); if (T) puts("");
	}
	return 0;
}
```

---

## 作者：yzhang (赞：5)

[更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/14152300.html)

发篇带有较为严谨证明的题解

我们不妨设$Park$为$1$号点。将边按边权从小到大排序，考虑选出的边要满足什么条件：

1. 选出的边构成原图的一个生成树

2. $1$号点度数不超过$k$

答案就是选边权之和最小的边集，满足上述条件

-  引理1: $M=(S,I)$是拟阵，其中$S$为边集，$I$为所有形成生成森林的边集 

证明：

遗传性：显然

交换性：假设两个边集$S,T$，其中$|S|<|T|$，且$T$中任意一条边加入$S$都不能形成独立集，那么$T$中每条边的端点一定在$S$中的同一联通块上。对于一个$S$中的联通块$G$的边集$A$，设$T$中满足两端都在$G$中的边集为$B$，由于$T$也是独立集，所以$|B| \leq |G|-1 = |A|$。不难归纳出$|T| \leq |S|$，与假设矛盾

-  引理2：$M=(S,I)$是拟阵，其中$S$为边集，$I$为使得$1$号点度数小于等于$k$的边集 

证明：

遗传性：显然

交换性：假设两个边集$S,T$，其中$|S|<|T|$，且$T$中任意一条边加入$S$都不能形成独立集。若$S$中与$1$相连的边数小于$k$，则任意一条不在$S$的边加入都形成独立集，$|T| \leq |S|$，与假设矛盾；否则$S$中与$1$相连的边数为$k$，则任意一条不在$S$且不与$1$相连的边加入都形成独立集，设$T$中与$1$相邻的边数为$a,(0 \leq a \leq k)$，则$|T|-a \leq |S| -k$，即$|T| \leq |S| -k +a \leq |S|$，与假设矛盾

那么满足题意的合法边集就是两个拟阵的交，求拟阵交即可，时间复杂度为$O(Tnm^2)$

```cpp
//μ's forever
#include <bits/stdc++.h>
#define M 905
#define ll long long
using namespace std;
int T,n,m,xp[M],yp[M],wp[M],x[M],y[M],w[M],pk,k;
map<string,int> mp;
pair<int,int> ar[M];
int s,t,val[M],fa[M],pre[M];
vector<int> g[M];
bool usd[M],ins[M];
ll dis[M],ans;
int find(int x){ return x==fa[x]?x:fa[x]=find(fa[x]); }
bool merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y)return 0;
    fa[x]=y;return 1;
}
bool chk1(bool usd[]){
    for(int i=1;i<=n;++i) fa[i]=i;
    for(int i=1;i<=m;++i) if(usd[i]) 
	if(!merge(x[i],y[i])) return 0;
    return 1;
}
bool chk2(bool usd[]){
    int ct=0;
    for(int i=1;i<=m;++i)
        if(usd[i]&&(x[i]==pk||y[i]==pk))
        	++ct;
    return ct<=k;
}
void spfa(){
    for(int i=1;i<=t;++i) dis[i]=1e18;
    queue<int> q;dis[s]=0,q.push(s),ins[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop(),ins[u]=0;
        for(int i=0;i<(int)g[u].size();++i){
            int v=g[u][i];
            if(dis[v]>dis[u]+val[v]){
                dis[v]=dis[u]+val[v],pre[v]=u;
                if(!ins[v]) ins[v]=1,q.push(v);
            }
        }
    }
}
void matroid_inter(){
    memset(usd,0,sizeof(usd));s=m+1,t=m+2;
    while(1){
        for(int i=1;i<=t;++i) g[i].clear();
        for(int i=1;i<=t;++i) if(usd[i]) val[i]=-w[i]; else val[i]=w[i];
        for(int i=1;i<=m;++i){ if(!usd[i]) continue;
            for(int j=1;j<=m;++j){ if(usd[j]) continue;
                usd[i]=0,usd[j]=1;
                if(chk1(usd)) g[i].push_back(j);
                if(chk2(usd)) g[j].push_back(i);
                usd[i]=1,usd[j]=0;
            }
        }
        for(int i=1;i<=m;++i){ if(usd[i]) continue;
            usd[i]=1;
            if(chk1(usd)) g[s].push_back(i);
            if(chk2(usd)) g[i].push_back(t);
            usd[i]=0;
        }
        spfa();
        if(dis[t]>1e15) break;
        for(int i=pre[t];i!=s;i=pre[i])
            usd[i]^=1;
    }
}
int main()
{
    cin>>T;
    while(T--){
    	mp.clear();ans=n=0;
    	cin>>m;
    	for(int i=1;i<=m;++i){
    		string a,b;
    		cin>>a>>b>>wp[i];
    		ar[i]=make_pair(wp[i],i);
    		if(mp.find(a)!=mp.end()) xp[i]=mp[a];
    		else{ mp[a]=++n,xp[i]=n; if(a=="Park") pk=n;}
    		if(mp.find(b)!=mp.end()) yp[i]=mp[b];
    		else{ mp[b]=++n,yp[i]=n; if(b=="Park") pk=n;}
    	}
    	sort(ar+1,ar+1+m);
    	for(int i=1;i<=m;++i)
    		x[i]=xp[ar[i].second],y[i]=yp[ar[i].second],w[i]=wp[ar[i].second];
    	cin>>k;
    	matroid_inter();
    	for(int i=1;i<=m;++i) if(usd[i]) ans+=w[i];
    	cout<<"Total miles driven: "<<ans<<endl;
    	if(T) puts("");
    }
	return 0;
}


---

## 作者：reclusive (赞：4)

[my blog](https://www.cnblogs.com/reclusive2007/p/17719719.html)

这道题显然是最小生成树，但是很显然我是不会打最小生成树的。

---

## 题意描述

给定一张 $n$ 个点 $m$ 条边的无向图，求出无向图的一棵最小生成树，满足一号节点的度数不超过给定的整数 $s$。

## 具体思路

首先，看到这种度数最多为 $s$ 的题，显然想到 wqs 二分。但是 wqs 二分是恰好选 $s$ 条边是最优，因此考虑证明这一性质。

设平面直角坐标系上的点 $(x,f(x))$，其中 $x$ 代表选多少条边，$f(x)$ 代表选 $x$ 条边时的边权之和。 

设当前 $f(x)$ 最优的情况是选 $s$ 条边连着 $1$ 号节点，即此时的生成树边权之和最小。

- 若我们选多一条边连着 $1$ 号节点，那么就会多加一条边的权值，显然权值之和没有选 $s$ 条边优。

- 若我们选少一条边连着 $1$ 号节点，那么就会导致有的点要连到其它节点上来保证连通性。由于我们选 $s$ 条边的时候是最优的，因此我们现在选的点要连到更大的边上，因此权值之和没有选 $s$ 条边优。

因此 $f(x)$ 具有凸函数性质，即斜率具有单调性，故可以二分。

![image](https://cdn.luogu.com.cn/upload/image_hosting/02dxnz17.png)

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>PII;
const int N=1100;
unordered_map<string,int>Hash;
int n,m,k,s,fa[N];
struct node{int x,y,c;}a[N];
bool cmp(node n1,node n2){
    if(n1.c+k*(n1.x==1)==n2.c+k*(n2.x==1))return n1.x!=1;
    return n1.c+k*(n1.x==1)<n2.c+k*(n2.x==1);
}
int get(int x){
    if(fa[x]==x)return x;
    return fa[x]=get(fa[x]);
}
PII kruskal(){
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++)fa[i]=i;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++){
        int x=a[i].x,y=a[i].y,c=a[i].c;
        int tx=get(x),ty=get(y);
        if(tx!=ty){
            fa[tx]=ty;
            ans=ans+c;
            if(x==1){
                cnt++;
                ans=ans+k;
            }
        }
    }
    return {cnt,ans};
}
int solve(){
    int l=0,r=1000;
    while(l<=r){
        int mid=(l+r)>>1;k=mid;
        if(kruskal().first>s)l=mid+1;
        else r=mid-1;
    }
    return l;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d",&m);
		Hash.clear();n=0;
	    Hash["Park"]=++n;
	    for(int i=1;i<=m;i++){
	        string x,y;int c;
	        cin>>x>>y>>c;
	        if(!Hash[x])Hash[x]=++n;
	        if(!Hash[y])Hash[y]=++n;
	        a[i]=node{Hash[x],Hash[y],c};
	        if(a[i].x>a[i].y)swap(a[i].x,a[i].y);
	    }
	    scanf("%d",&s);
	    printf("Total miles driven: ");
	    k=0;
	    if(kruskal().first>s)k=solve();
	    printf("%d\n",kruskal().second-k*s);
	    if(t)puts("");
	}
    return 0;
}
```

---

## 作者：Llf0703 (赞：2)

推广博客：https://llf0703.com/p/uva-1537.html

## 题意

求 $N$ 点无向图的最小生成树，满足 $1$ 号节点度数 $\le s$ 。$N\le 30$ 。

## 题解

### 思想

考虑构造一个以 $1$ 号节点为根的树，则 $1$ 号节点必须与子树中所有连通块相连。记录去掉 $1$ 号节点后的连通块个数，即 $1$ 号节点的最小度数，为 $tcnt$ 。（题目保证有解即 $tcnt\le s$）

对每个连通块分别求出最小生成树，这样就得到了除 $1$ 号节点外的局部最优解，同时全局最优解**只与 $1$ 号结点的连法有关**。

先考虑度数为 $tcnt$ 的最优解，显然从每个连通块选择离 $1$ 最近的节点与之相连最优。

继续考虑度数为 $[tcnt+1,s]$ 时的最优解，可以用换边来解决。

用不在树上的边 $(1,x)$ 替换 $(u,v)$ ，其中 $(u,v)$ 是原树中 $1\rightarrow x$ 路径上的一条边，贪心找权值最大的 $(u,v)$ 替换掉是最优的。

枚举所有 $(1,x)$ 并得到 $(u,v)$ ，设两边的权值为 $z$ 和 $w$ ，显然找到 $w-z$ 最大的 $x_0$ 最优，这样答案就减少了 $w_0-z_0$ 。

这样的换边最多可以做 $s-(tcnt+1)+1=s-tcnt$ 次，不过当 $w_0-z_0\le 0$ 时就可以不用再做了。

### 实现

1. 用 `map` 建立人名和编号的映射，并建边。
2. `dfs1()` 划分连通块，并用 `v` 记录连通块内的所有边，每次搜索完后用 `kruskal()` 求最小生成树。
3. 用 `v` 记录与 $1$ 号节点相连的所有边，同样做一次 `kruskal()` 。（即从每个连通块选择离 $1$ 最近的节点与之相连，因为连通块都已经用并查集合并了起来，所以这样做是等价的）
4. 进行 $s-tcnt$ 次换边操作，枚举 $(1,x)$ 并得到边权最大的 $(u,v)$ 记录为 `e` 。在外层用 `mx` 保存 $w-z$ 的最大值，同时更新 `e0` 表示最大时的 $(u,v)$ ，`x0` 为最大时的 $(1,x)$ 。最后用 `x0` 替换 `e0` 即可。如果 $mx\le 0$ 就退出循环。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int next,from,to,w;
} edge[1805];
string a,b;
vector <int> v;
map <string,int> mp;
int t,n,m,s,c,cnt,head[35],fa[35];
bool vis[35],used[905],intree[905];

inline bool cmp(int x,int y); //对边进行排序
inline void add(int u,int v,int w); //加边
inline void init(); //多组数据初始化
inline int another(int x); //前向星中相反的边（从1开始）

// 并查集相关
inline void init2(); //初始化
int getfa(int x); //得到父亲
inline bool merge(int x,int y); //合并

void dfs1(int x); //求连通块
bool dfs2(int x,int f,int goal,int &now,int &e0); //求树上1->x
inline int kruskal(); //最小生成树

signed main()
{
    cin>>t;
    while (t--)
    {
        init();
        mp["Park"]=1;
        cin>>m;
        for (int i=1;i<=m;i++)
        {
            cin>>a>>b>>c;
            if (!mp.count(a)) mp[a]=++n;
            if (!mp.count(b)) mp[b]=++n;
            add(mp[a],mp[b],c);
            add(mp[b],mp[a],c); //建边
        }
        cin>>s;
        init2();
        vis[1]=1;
        int ans=0,tcnt=0;
        for (int i=head[1];i;i=edge[i].next) //步骤1
        {
            int y=edge[i].to;
            if (vis[y]) continue;
            tcnt++; //连通块个数
            v.clear();
            dfs1(y);
            ans+=kruskal(); //加上连通块内最小生成树的权值
        }
        v.clear();
        for (int i=head[1];i;i=edge[i].next) v.emplace_back(i); //步骤2
        ans+=kruskal();
        int tot=s-tcnt;
        while (tot--)
        {
            int mx=0,x0,e0; //e0=(u0,v0),x0=(1,x0)
            for (int i=head[1];i;i=edge[i].next)
            {
                if (intree[i] || intree[another(i)]) continue;
                int x=edge[i].to,z=edge[i].w,w=0,e;
                dfs2(1,0,x,w,e); //得到最大权值w和那条边e
                if (w-z>mx)
                {
                    mx=w-z;
                    x0=i;
                    e0=e;
                }
            }
            if (mx<=0) break;
            intree[e0]=intree[another(e0)]=0;
            intree[x0]=intree[another(x0)]=1; //换边
            ans-=mx; //更新答案
        }
        cout<<"Total miles driven: "<<ans<<"\n";
        if (t) puts(""); //注意最后一行不换行
    }
    return 0;
}

inline void add(int u,int v,int w)
{
    edge[++cnt].to=v;
    edge[cnt].from=u;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}

inline void init()
{
    n=1;
    cnt=0;
    mp.clear();
    memset(vis,0,sizeof(vis));
    memset(used,0,sizeof(used));
    memset(head,0,sizeof(head));
    memset(intree,0,sizeof(intree));
}

inline int another(int x) { return ((x-1)^1)+1; }

inline bool cmp(int x,int y) { return edge[x].w<edge[y].w; }

inline void init2() { for (int i=1;i<=n;i++) fa[i]=i; }

int getfa(int x) { return x==fa[x] ? x : fa[x]=getfa(fa[x]); }

inline bool merge(int x,int y)
{
    int gfx=getfa(x),gfy=getfa(y);
    if (gfx==gfy) return 0;
    fa[gfx]=gfy;
    return 1;
}

void dfs1(int x)
{
    vis[x]=1;
    for (int i=head[x];i;i=edge[i].next)
    {
        int y=edge[i].to;
        if (y!=1 && !used[i]) used[i]=used[another(i)]=1,v.emplace_back(i); //记录边
        if (!vis[y]) dfs1(y);
    }
}

inline int kruskal()
{
    int ans=0;
    sort(v.begin(),v.end(),cmp);
    for (auto i:v)
    {
        int x=edge[i].from,y=edge[i].to,w=edge[i].w;
        if (!merge(x,y)) continue;
        ans+=w;
        intree[i]=intree[another(i)]=1;
    }
    return ans;
}

bool dfs2(int x,int f,int goal,int &now,int &e0)
{
    if (x==goal) return 1; //能到达终点
    bool flag=0;
    for (int i=head[x];i;i=edge[i].next)
    {
        if (!intree[i]) continue;
        int y=edge[i].to,w=edge[i].w;
        if (y==f) continue;
        bool res=dfs2(y,x,goal,now,e0);
        if (res && w>now) now=w,e0=i; //能到达终点才更新
        flag|=res;
    }
    return flag;
}
```

---

## 作者：hfee (赞：1)

题意简明：求一个满足1号节点（" $Park$ "）度数小于等于$s$的最小生成树

首先将1号节点去掉，图会被分成若干个连通块，若连通块数量大于 $s$ ，则无解（显然）

对于每个连通块，求出它内部的最小生成树，再将1号节点分别与这些连通块相连，用最小的那条边连接。

到此为止我们已经得出了一颗原图的生成树，1号节点的数量为连通块的数量，设为 $x$ ，若 $x<s$ ，我们还可以向1号节点连一些边，用这些边替代本来连通块中更大的边，直到 $x=s$ 或者没有一条边更优为止。

即扫描所有1号节点相连的边 $(1,v)$ ，若还没有使用，则从1号节点出发出发到 $v$ 这条路径上寻找一个最大的边进行替换

具体实现来说，因为调了很久，写的略有一些麻烦

```
#include <bits/stdc++.h>
#define N 1005
#define M make_pair
using namespace std;
map<string, int> q;
int n, t = 1, cnt, lt, ans, head[N], fa[N], bl[N], fg[35][35], s, mx, tu, tv, su, T;
map<pair<int, int>, bool> p;
//p:这条边有没有被使用 
struct Edge{
	int u, v, nxt, w;
}e[N];
void add(int u, int v, int w){
	e[++cnt].v = v;
	e[cnt].w = w;
	e[cnt].u = u;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
struct Ke{
	int u, v, w;
}ed[N];
bool cmp(Ke r, Ke t){
	return r.w < t.w;
}
int get(int x){
	if(x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}
void kru(){
	for(int i = 1; i <= t; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i){
		int x = get(ed[i].u), y = get(ed[i].v);
		if(x == 1 || y == 1 || x == y) continue;
		p[M(ed[i].u, ed[i].v)] = 1;
		p[M(ed[i].v, ed[i].u)] = 1;
		ans += ed[i].w;
		fa[x] = y; 
	}
} 
//求每个连通块的最小生成树，标记边，累加ans 
void dfs(int u, int x){
	bl[u] = x;
	for(int i = head[u]; i; i = e[i].nxt){
		int to = e[i].v;
		if(!bl[to]) dfs(to, x);
	}
}
void lb(){
	for(int i = 2; i <= su; ++i){
		int minn = INT_MAX, at; 
		for(int j = 1; j <= t; ++j){
			if(bl[j] == i && fg[1][j]){
				if(fg[1][j] < minn){
					minn = fg[1][j];
					at = j;
				}
			}
		}
		ans += minn;
		p[M(1, at)] = p[M(at, 1)] = 1;
	}
}
//由1到每个连通块连边
void dfs2(int u, int mb, int fa, int ma, int ku, int kv){
	if(u == mb){
		tu = ku, tv = kv, mx = ma;
		return;
	}
	for(int i = head[u]; i; i = e[i].nxt){
		if(!p[M(e[i].u, e[i].v)] || e[i].v == fa) continue;
		if(e[i].w > ma) dfs2(e[i].v, mb, u, e[i].w, e[i].u, e[i].v);
		else dfs2(e[i].v, mb, u, ma, ku, kv);
	}
}//寻找1-v路径上最大的边 
int main(){
	scanf("%d", &T);
	while(T--){
		ans = cnt = 0; t = 1; memset(fg, 0, sizeof(fg)); q.clear(); p.clear();
		memset(head, 0, sizeof(head)); memset(e, 0, sizeof(e)); memset(bl, 0, sizeof(bl));
		scanf("%d", &n);
		q["Park"] = 1;
		for(int i = 1; i <= n; ++i){
			string u, v;
			int w;
			cin >> u >> v >> w; 
			if(!q[u]) q[u] = ++t;
			if(!q[v]) q[v] = ++t;
			add(q[u], q[v], w);	add(q[v], q[u], w);
			fg[q[u]][q[v]] = fg[q[v]][q[u]] = w;
			ed[i].u = q[u]; ed[i].v = q[v]; ed[i].w = w;
		}
		scanf("%d", &s);
		sort(ed + 1, ed + 1 + n, cmp);
		kru();
		su = 1; bl[1] = 1;
		for(int i = 2; i <= t; ++i) if(!bl[i]) dfs(i, ++su); lt = su - 1;
		lb();
		while(s > lt){
			int ng = 0, lu, lv, po;
			for(int i = head[1]; i; i = e[i].nxt){
				int to = e[i].v, g = e[i].w; mx = 0;
				if(p[M(1, to)]) continue;
				dfs2(1, to, -1, 0, 0, 0);
				if(ng < mx - g){
					lu = tu; lv = tv;
					ng = mx - g; po = to;
				}
			}
			if(ng <= 0) break;//ng<=0 没有更优的边 可以推出了 
			ans -= ng;
			p[M(lu, lv)] = p[M(lv, lu)] = 0;
			p[M(1, po)] = p[M(po, 1)] = 1;
			lt++;
		}
		printf("Total miles driven: %d\n", ans);
		if(T) puts("");
	}
	return 0;
}
```


---

## 作者：淸梣ling (赞：1)

~~还没有 WQS 二分的写法，这里水一篇。~~

# Soltion

**前置知识：WQS 二分。**

这题和 [P5633](https://www.luogu.com.cn/problem/P5633) 类似，假设和 `Park` 相连的称为“关键边”，考虑最优时刻我们选择了 $t$ 条关键边，那么增加或减少关键边的数量都会让权值和变大，显而易见是个凸函数。

本题要求不超过 $s$，我们可以先做一遍生成树，然后看选择的边是否不超过 $s$，不超过那么直接就是最小生成树，否则只需要 WQS 二分找**恰好等于 $s$** 的最优解。

WQS 二分经典操作，我们给关键边增加一个额外权值来控制选择的数量，然后二分斜率找到最优值。

**注意 UVA 格式。**

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

struct edge { int x,y,z; };

map<string,int> mp;
edge e[1000];
int fa[50];
int n,m,k,t;

int find(int x) { return x==fa[x] ? fa[x] : fa[x]=find(fa[x]); }
bool cmp(const edge& a, const edge& b)
{
    if(a.z+t*(a.x==1)==b.z+t*(b.x==1)) return a.x!=1;
    return a.z+t*(a.x==1)<b.z+t*(b.x==1);
}
pair<int,int> kruskal()
{
    int ans=0,cnt=0;
    for(int i=1; i<=n; i++) fa[i]=i;
    sort(e+1, e+1+m, cmp);
    for(int i=1; i<=m; i++)
    {
        int fx=find(e[i].x),fy=find(e[i].y);
        if(fx==fy) continue;
        fa[fx]=fy; ans+=e[i].z;
        if(e[i].x==1) ++cnt, ans+=t;
    }
    return make_pair(ans, cnt);
}
int erfen(int l, int r)
{
    while(l<r)
    {
        int mid=(l+r)>>1; t=mid;
        if(kruskal().second>k)
        l=mid+1;
        else
        r=mid;
    }
    return l;
}
void work(int T)
{
    mp.clear(); mp["Park"]=n=1;

    cin>>m;
    for(int i=1; i<=m; i++)
    {
        string x,y;
        int z;
        cin>>x>>y>>z;
        if(!mp[x]) mp[x]=++n;
        if(!mp[y]) mp[y]=++n;
        e[i].x=mp[x]; e[i].y=mp[y]; e[i].z=z;
        if(e[i].x>e[i].y) swap(e[i].x, e[i].y);
    }
    cin>>k;

    t=0;
    if(kruskal().second>k) t=erfen(0, 1000);
    printf("Total miles driven: %d\n", kruskal().first-k*t);
    if(T) putchar('\n');
}
int main()
{
    int t;
    cin>>t;
    while(t-->0) work(t);
    return 0;
}
```



---

## 作者：koreyoshi_lemon (赞：1)

------------
1. 首先，我们不妨去掉1号节点，无向图就会分成几个连通块，设  连通块个数为 $T$，显然如果 $T>S$  的话，本体就无解了 （要满足1号节点度数不超过 $S$，但这样的话就连不起来这张图了）



2. 然后考虑每个连通块内，**先求出每个连通块内的最小生成树**，然后从连通块中选取 $p$ 号节点与 $1$ 号节点相连，思考后就会发现应使边 $(1,p)$  的权值尽可能小。这时，我们就**得到了无向图的一棵生成树**，但这就是答案吗？



3. 其实是不对的。题目要求 $1$ 号节点度数不超过 $S$，但这样做的话**只考虑了 $1$ 号节点度数为 $T$ **的情况，我们**还应考虑改动 $S-T$ 条边**，使答案更优。



4. 考虑从无向图中从1号节点出发的边  $(1,x)$，边权为 $z$。可以得出以下贪心策略，如果 $(1,x)$ 还不在上述的生成树中，就寻找生成树中 $x$ 到 $1$ 号节点路径上最大的边 $(u,v)$，记边权为 $w$。每次求出能够最大化  $w-z$ 的点 $x$ （因为此时修改x能够对答案产生最大的贡献），若对应的 $w-z>0$，就删去 $(u,v)$，加上 $(1,x)$，那么答案就会减小 $w-z$。（这就是本题的关键，可能不大容易理解，自己画个图就明白了）




5. 然后重复4中的步骤 $S-T$ 次，或者 $\max(w-z)<0$（答案已经最小，无法更新）时停止，就求得了题目要求的最小生成树。


------------

贴上 XuHt 大佬的代码：

```cpp
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 37, INF = 0x3f3f3f3f;
struct E {
	int x, y, z;
	bool operator < (const E w) const {
		return z < w.z;
	}
} f[N];
int n, k, tot, ans, a[N][N], fa[N], d[N], v[N];
map<string, int> m;
vector<E> e;
bool b[N][N];

int get(int x) {
	if (x == fa[x]) return x;
	return fa[x] = get(fa[x]);
}

void dfs(int x, int o) {
	for (int i = 2; i <= tot; i++) {
		if (i == o || !b[x][i]) continue;
		if (f[i].z == -1) {
			if (f[x].z > a[x][i]) f[i] = f[x];
			else {
				f[i].x = x;
				f[i].y = i;
				f[i].z = a[x][i];
			}
		}
		dfs(i, x);
	}
}
inline void init()
{
	memset(a, 0x3f, sizeof(a));
	memset(d, 0x3f, sizeof(d));
	m.clear();
	e.clear();
	for (int i = 0; i < N; i++) fa[i] = i;
	memset(f,0,sizeof(f));
	memset(b,0,sizeof(b));
	memset(v,0,sizeof(v));
	n=k=ans=tot=0;
}
int main() {
	int T;
	cin>>T;
	while(T--)
	{
		init();
		cin >> n;
		m["Park"] = tot = 1;
		for (int i = 1; i <= n; i++) {
			E w;
			string s1, s2;
			cin >> s1 >> s2 >> w.z;
			w.x = m[s1] ? m[s1] : (m[s1] = ++tot);
			w.y = m[s2] ? m[s2] : (m[s2] = ++tot);
			e.push_back(w);
			a[w.x][w.y] = a[w.y][w.x] = min(a[w.x][w.y], w.z);
		}
		cin >> k;
		sort(e.begin(), e.end());
		for (unsigned int i = 0; i < e.size(); i++) {
			if (e[i].x == 1 || e[i].y == 1) continue;
			int rtx = get(e[i].x), rty = get(e[i].y);
			if (rtx != rty) {
				fa[rtx] = rty;
				b[e[i].x][e[i].y] = b[e[i].y][e[i].x] = 1;
				ans += e[i].z;
			}
		}
		for (int i = 2; i <= tot; i++)
			if (a[1][i] != INF) {
				int rt = get(i);
				if (d[rt] > a[1][i]) d[rt] = a[1][v[rt]=i];
			}
		for (int i = 1; i <= tot; i++)
			if (d[i] != INF) {
				--k;
				b[1][v[i]] = b[v[i]][1] = 1;
				ans += a[1][v[i]];
			}
		while (k--) {
			memset(f, -1, sizeof(f));
			f[1].z = -INF;
			for (int i = 2; i <= tot; i++)
				if (b[1][i]) f[i].z = -INF;
			dfs(1, -1);
			int o, w = -INF;
			for (int i = 2; i <= tot; i++)
				if (w < f[i].z - a[1][i])
					w = f[i].z - a[1][o=i];
			if (w <= 0) break;
				b[1][o] = b[o][1] = 1;
				b[f[o].x][f[o].y] = b[f[o].y][f[o].x] = 0;
				ans -= w;
		}
		printf("Total miles driven: %d\n", ans);
		if(T) putchar(10);   //可恶的 UVA 居然卡换行。。
	}
	return 0;
}
```

---

## 作者：heyuhhh (赞：0)

将1号点从图中去掉过后，图会形成几个连通块，那么我们首先可以在这些连通块内部求最小生成树。

假设有$tot$个连通块，那么我们会从1号点至少选$tot$个出边，使得图连通。这时我们贪心地选择最小的，这应该都很好懂。

因为题目中的要求是度数不超过$s$，那么也就是说我们可以从1号点出发，再加入$s-tot$条边，因为可能这些边的边权比连通块中的某些边边权小，那么替换过后答案肯定最优。

具体替换方法为：如果当前顶点度数为$k$，我们现在要向$k+1$的度数扩展，我们肯定要枚举所有没用到过的出边，因为只会添加一条边，那么就会形成一个环。单独考虑一条边$(1,x)$，肯定会选择将$1$到$x$路径上面边权最大的边给替换掉。那么我们可以枚举所有的情况，最后取min，就能得到$k+1$度的最优解。最后一次类推就行了。。。。如果向$k+1$度扩展得不到更优解时，直接break掉就行了。


具体思路就是这样。。。。但是代码细节稍微有点多。

因为求最小生成树时会利用到边的信息，以及最后会考虑1的每个出边，所以我先把边给标号，并且用了一个$v[i]$来保存$i$号结点所有的出边，这样就会方便一些。

细节见代码吧：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 35;
int t;
int n, s;
struct Edge{
    int u, v, w;
}e[N * N];
vector <int> v[N], vec;
bool vis[N], used[N * N], check[N * N];
int tot;
ll ans ;
void dfs(int x) {
    vis[x] = 1;
    for(auto i : v[x]) {
        int to = e[i].v, u = e[i].u;
        if(to == x) to = u ;
        if(to != 1 && !check[i]) {
            vec.push_back(i) ;
            check[i] = 1;
        }
        if(!vis[to] && to != 1) dfs(to) ;
    }
}
bool cmp(int a, int b) {
    return e[a].w < e[b].w;
}
int f[N], d[N], ee[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]) ;
}
int insert(int i) {
    int x = e[i].u, y = e[i].v;
    int fx = find(x), fy = find(y) ;
    if(fx != fy) {
        f[fx] = fy;
        ans += e[i].w;
        used[i] = 1;
        return 1;
    } else return 0;
}
void dfs2(int x) {
    vis[x] = 1;
    for(auto i : v[x]) {
        int u = e[i].u, to = e[i].v;
        if(to == x) to = u;
        if(!vis[to] && used[i]) {
            if(e[i].w > d[x]) {
                d[to] = e[i].w;
                ee[to] = i;
            } else {
                d[to] = d[x] ;
                ee[to] = ee[x] ;
            }
            dfs2(to) ;
        }
    }
}
int main() {
    cin >> t;
    while(t--) {
        ans = 0;
        //处理输入
        cin >> n;
        for(int i = 1; i < N; i++) v[i].clear() ;
        map <string ,int> mp;
        memset(check, 0, sizeof(check)) ;
        memset(used, 0, sizeof(used)) ;
        mp["Park"] = 1;
        int num = 1;
        tot = 0;
        string s1, s2;
        for(int i = 1; i <= n; i++) {
            int dis;
            cin >> s1 >> s2 >> dis;
            if(mp.find(s1) == mp.end()) mp[s1] = ++num;
            if(mp.find(s2) == mp.end()) mp[s2] = ++num;
            e[i] = Edge{mp[s1], mp[s2], dis} ;
            v[mp[s1]].push_back(i) ;
            v[mp[s2]].push_back(i) ;
        }
        cin >> s;
        //在每个连通块内求最小生成树
        for(int i = 1; i < N; i++) f[i] = i;
        memset(vis, 0, sizeof(vis)) ;
        for(int i = 2; i <= num; i++) {
            if(!vis[i]) {
                vec.clear() ;
                tot++;
                dfs(i);
                sort(vec.begin(), vec.end(), cmp) ;
                for(auto i : vec) insert(i) ;
            }
        }
        //选出最小的边让树连通
        vec.clear() ;
        for(auto i : v[1]) vec.push_back(i) ;
        sort(vec.begin(), vec.end(), cmp) ;
        int l = vec.size(), k;
        for(int i = 0; i < tot; i++) {
            for(k = 0; k < l; k++) {
                int ok = insert(vec[k]) ;
                if(ok) break ;
            }
        }
        //贪心换边
        int cnt = s - tot;
        while(cnt--) {
            memset(d, 0, sizeof(d)) ;
            memset(vis, 0, sizeof(vis)) ;
            dfs2(1);
            int mn = 0, f = -1;
            for(int j = 0; j < l; j++) {
                int i = vec[j] ;
                if(used[i]) continue ;
                int x = e[i].u, y = e[i].v, to;
                if(x == 1) to = y;
                else to = x;
                if(e[i].w - d[to] < mn) {
                    mn = e[i].w - d[to] ;
                    f = i;
                }
            }
            if(f == -1) break ;
            int i = f ;
            int x = e[i].u, y = e[i].v, to;
            if(x == 1) to = y;
            else to = x;
            used[i] = 1;
            used[ee[to]] = 0;
            ans += mn;
        }
        cout << "Total miles driven: ";
        cout << ans << '\n';
        if(t) cout << '\n' ;
    }
    return 0;
}
/*
13
Park 1 9
Park 2 10
Park 3 10
Park 4 10
Park 5 10
Park 6 10
Park 7 10
1 2 11
1 4 13
2 3 12
4 5 14
5 6 14
6 7 13
6
*/

```


---

