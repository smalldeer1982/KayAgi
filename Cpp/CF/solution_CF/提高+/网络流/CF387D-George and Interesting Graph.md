# George and Interesting Graph

## 题目描述

- 没有重边；
- 存在结点 $v$（称为中心），使得对于图中的任意结点 $u$，都有边 $(u,v)$ 和 $(v,u)$，注意自环 $(v,v)$ 也应该存在；
- 除去中心外，每个点的入度和出度都恰好为 $2$； 

显然很少有图有趣，但 George 可以把图变得有趣：每次他可以增加一条边或者删除一条已经存在的边。

现在给出图 $G$，George 想知道他最少做多少次操作可以使它变得有趣。

## 样例 #1

### 输入

```
3 7
1 1
2 2
3 1
1 3
3 2
2 3
3 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 6
1 1
2 2
3 1
3 2
2 3
3 3
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 1
2 2
```

### 输出

```
6
```

# 题解

## 作者：吾王美如画 (赞：9)

# 唔姆

一道十分因缺思厅的题

---------
- 首先，看数据范围这么小，想都不用想，直接暴力枚举中心点（滑稽）
- 然后，对于每个中心点，我们都要记录下有多少个点连向它（记为into），它又连向多少个个别的点（记为out）。因为题目说了莫得重边，所以就直接统计边的个数好了。（**有一点需要注意，如果是自环的话，只能算一次**）为了满足中心点的约束，对于每个中心点，我们都需要2*n-1-into-out操作。（**为什么-1？因为中心点也要连向自己，but只需要一次操作就可以完成**）
- 接着，在满足中心点的约束之后，剩下的点都只剩下一个入度和一个出度了。那么这些点无论如何都是处于一个环中（有可能是自环）。也就意味着，如果想要最少的改变次数，我们要在现有的边中，尽量找出符合条件的边。
- 既然每个点只能向别的点连一次，也只能被别人连一次，这不就是标准的二分图最大匹配鸭！每次枚举中心点重新建图就OK了（记得不要把连向中心点或者从中心点连出来的边给匹配了）
- 在求出二分图最大匹配p之后我们需要如下操作
  1. 把没被匹配的边删掉，需要m-into-out-p次操作
  2. 把要加的边加上，需要n-1-p次操作
- 综上所述,ans=2*n-1-into-out+m-into-out-p+n-1-p。在枚举中心点的时候保留最小的ans就好了。

放上我巨丑无比的代码

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define MAXN 11050
#define MAXM 150005
using namespace std;
int head[MAXN],nextt[MAXM*2],to[MAXM*2],w[MAXM*2];
int n,m,S,T;
int cnt=-1;
int deep[MAXN];
struct line{
       int from;
       int to;
}l[MAXM];
void link(int a,int b,int c){
     cnt++;
     w[cnt]=c;
     nextt[cnt]=head[a];
     to[cnt]=b;
     head[a]=cnt;
     cnt++;
     w[cnt]=0;
     nextt[cnt]=head[b];
     to[cnt]=a;
     head[b]=cnt;
}
bool bfs(){
     memset(deep,0,sizeof(deep));
     queue<int> q;
     while(!q.empty())q.pop();
     q.push(S);
     deep[S]=1;
     while(!q.empty()){
                       int now=q.front();
                       q.pop();
                       for(int i=head[now];i!=-1;i=nextt[i]){
                               if (w[i]&&!deep[to[i]]){
                                                       deep[to[i]]=deep[now]+1;
                                                       q.push(to[i]);
                               }
                       }
     }
     if (deep[T])return 1;else return 0;
}
int dinic(int now,int last){
    if (now==T||!last)return last;
    int ret=0;
    for(int i=head[now];i!=-1;i=nextt[i]){
            if(deep[to[i]]-1==deep[now]&&w[i]){
                                               int zgl=dinic(to[i],min(w[i],last-ret));
                                               if (zgl){
                                                        w[i]-=zgl;
                                                        w[i^1]+=zgl;     
                                                        ret+=zgl;
                                               }
            }
    }
    if (!ret)deep[now]=-1;
    return ret;
}
int into[MAXN],out[MAXN];
int main(){
    cin>>n>>m;
    S=0;T=MAXN-1;
    memset(into,0,sizeof(into));
    int a,b;
    for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);
            l[i].from=a;l[i].to=b;
            into[b]++;
            out[a]++;
            if (a==b)into[b]--;
    }
    int anss=MAXM;
    for(int i=1;i<=n;i++){
            memset(head,-1,sizeof(head));
            cnt=-1;
            int tmp=into[i]+out[i];
            for(int j=1;j<=n;j++){
                    link(S,j,1);
                    link(j+500,T,1);
            }
            for(int j=1;j<=m;j++){
                    if (l[j].to==i||l[j].from==i)continue;
                    link(l[j].from,l[j].to+500,1);
            }
            int ans=0;        
            while(bfs())
                        ans+=dinic(S,9999999);
            anss=min(anss,n-1-ans+m-ans+2*n-1-tmp*2);
    }
    cout<<anss<<endl;
    return 0;
}

```


---

## 作者：mcDinic (赞：4)

为什么大佬们都打网络流啊？匈牙利算法跑二分图最大匹配的码量比网络流小多了呢，蒟蒻就发个**匈牙利算法**的题解。

看数据范围可知时间复杂度大约是 $O(n^3)$，所以果断枚举中心点······

在前面预处理出每个点的度数（记为 $L_i$，自环的特判），则对于当前中心点，关于它的操作次数是 $2n-1-L_i$。

由于中心点自己的条件已满足，其余每个点出入度都只剩下一。于是，把每个点拆成两个（一个入，一个出），左右两边要每个点都被边连到且只连一次，边也不重复，由于边权均为一，这不就是最基础的二分图匹配吗？

到这里，很多大佬都用网络流做，不过我觉得匈牙利算法的代码要简洁很多。

证下跑二分图最大匹配的正确性吧：我们跑的是保留下来的最大边数，它越大，删的边就少，需要加的边数是固定的，所以加的边也会少，这样保留下的边取到最大，答案就会最小。（答案对应的表达式挺简单的，此处不加赘述，详见代码）

求出以上每个中点得出的答案后，取个最小值输出即可。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define v e[i].y
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
int na,n,m,L[505],o1,o2,ti,cnt,h[505],b[505],vis[505],Ans=inf,ans;
struct node{int y,nxt;}e[2000005];
void add(int noi,int ioi){e[cnt].nxt=h[noi],e[cnt].y=ioi,h[noi]=cnt++;}
bool dfs(int x){
    for(int i=h[x];i!=-1;i=e[i].nxt)
        if(b[v]<ti&&v!=na){
            b[v]=ti;
            if(!vis[v]||dfs(vis[v])){vis[v]=x;return 1;}
        }
    return 0;
}
signed main(){
    scanf("%lld%lld",&n,&m),memset(h,-1,sizeof(h));
    for(int i=1;i<=m;i++)scanf("%lld%lld",&o1,&o2),add(o1,o2),L[o1]++,L[o2]+=(o1!=o2);
    for(na=1;na<=n;na++,ans=0){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)if(i!=na)ti++,ans+=dfs(i);
        Ans=min(Ans,m-L[na]-ans+n-1-ans+2*n-1-L[na]);
    }
    printf("%lld",Ans);
    return 0;
}
```


---

## 作者：破忆 (赞：2)

## 【题意】

在有向图中，通过加边、删边满足两个条件。

确定一个中心点 $u$，对于任意点 $v$，存在 $(u,v)$ 与 $(v,u)$，包括 $(u,u)$。

除中心点外的点的出度、入度都要为2。

求最小操作数。

## 【分析】

首先枚举中心点 $u$。

与 $u$ 直接相连的边，直接统计可以保留的边数。

排除这类边后，要让非中心点 $v$ 的入度与出度均为1。

将点 $x$ 拆为入点 $x_{in}$ 和出点 $x_{out}$。

对于边 $(x,y)$，$x_{out}->y_{in}$

入点与出点的最大匹配就是最多能保留的边。

网络流求最大匹配。

设共能保留 $x$ 条边。

总共需要与中心点相连的 $2(n-1)+1$ 条边、与中心点不相连的 $n-1$ 条边，共 $3n-2$。

需要加入的边数为 $3n-2-x$，需要删除的边数为 $m-x$。

总代价是 $3n-2+m-2x$。

## 【代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=505,maxt=maxn*2,maxm=1005,maxe=maxm*2+maxt*2,INF=1<<30;
int n,m;
struct Dinic{
    int S,T;
    struct edge{
        int to,nxt,f;
    }e[maxe];
    int tot,lnk[maxt];
    void add_e(int x,int y,int f){
        e[++tot]=(edge){y,lnk[x],f};
        lnk[x]=tot;
    }
    void ADD(int x,int y,int f){
        add_e(x,y,f),add_e(y,x,0);
    }
    int que[maxt],cur[maxt],dep[maxt];
    bool BFS(){
        int hed=0,til=1;
        for(int i=1;i<=T;i++) cur[i]=lnk[i],dep[i]=INF;
        que[1]=S,dep[S]=0;
        while(hed!=til){
            int x=que[++hed];
            for(int j=lnk[x];j;j=e[j].nxt){
                int y=e[j].to;
                if(dep[y]==INF&&e[j].f){
                    dep[y]=dep[x]+1;
                    que[++til]=y;
                }
            }
        }
        return dep[T]!=INF;
    }
    int DFS(int x,int limit){
        if(!limit||x==T) return limit;
        int flow=0,f;
        for(int j=cur[x];j;j=e[j].nxt){
            cur[x]=j;
            int y=e[j].to;
            if(dep[y]==dep[x]+1&&(f=DFS(y,min(limit,e[j].f)))){
                e[j].f-=f;
                e[j^1].f+=f;
                flow+=f;
                limit-=f;
            }
            if(!limit) return flow;
        }
        return flow;
    }
    int calc(){
        int ans=0;
        while(BFS()) ans+=DFS(S,INF);
        return ans;
    }
}D;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
struct data{
	int x,y;
}a[maxm];
bool vis[maxn][2];
int ans=INF;
int main(){
	freopen("CF387D.in","r",stdin);
	freopen("CF387D.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;i++) a[i].x=read(),a[i].y=read();
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof vis);
		int cnt=0;
		D.S=2*n+1,D.T=D.S+1,D.tot=1;
		memset(D.lnk,0,sizeof D.lnk);
		for(int j=1;j<=m;j++){
			if(a[j].x==i&&!vis[a[j].y][0]) vis[a[j].y][0]=1,cnt++;else
			if(a[j].y==i&&!vis[a[j].x][1]) vis[a[j].x][1]=1,cnt++;else
			if(a[j].x!=i&&a[j].y!=i) D.ADD(a[j].x,a[j].y+n,1);
		}
		for(int j=1;j<=n;j++) D.ADD(D.S,j,1),D.ADD(j+n,D.T,1);
		cnt+=D.calc();
		ans=min(ans,3*n-2-cnt+m-cnt);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Reaepita (赞：1)

① 首先我们 $O(n)$ 枚举一个中心节点

② 然后我们此时如果搞定了中心点的约束之后，我们考虑剩下 $n-1$ 个点，

我们知道，最终要使得这 $n-1$ 个点的出入度都是 $2$ ，

然而这里已经用掉了一个出度连入中心点，

也用掉了一个入度，使得中心点连入，

那么我们剩下的任务就是将这 $n-1$ 个点的出入度都控制在 $1$ 即可。

③对于剩下的边我们进行二分图匹配

对于一个匹配一定有两个点的出度和入度满足条件，所以

求得的 n-1-最大匹配数 就是子问题的答案

④对于一个中心点还需要满足 $center\to u$ 和 $u\to center$

都有边，对于没有的边我们要加上

⑤最后的答案还要加上二分图匹配中的非匹配边

⑥问题的答案就是每个子问题答案的最小值

我是用网络流求的二分图匹配的最大匹配数

```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int maxn=100000*2+10,maxl=1000+111,inf=0x3f3f3f3f;
struct edge
{
	int v,next;
	int w;
}e[maxn];
int head[maxl],cnt=0,dep[maxl],n,m,ans=0,s,t;
inline void add(int u,int v,int w)
{
	e[cnt]=(edge){v,head[u],w};
	head[u]=cnt++;
	e[cnt]=(edge){u,head[v],0};
	head[v]=cnt++;
}
bool bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int>q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=e[i].next)
		{
			int v=e[i].v;
			if(dep[v]==-1&&e[i].w>0)
			{
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t]>-1;
}
int dfs(int u,int cap)
{
	
	if(u==t)return cap;
	int flow=0;
	for(int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].v;
		if(dep[v]==dep[u]+1&&e[i].w)
		{
			int temp=dfs(v,min(e[i].w,cap-flow));
			flow+=temp;
			e[i].w-=temp;
			e[i^1].w+=temp;
			if(flow==cap)return flow;
		}
	}
	if(!flow)dep[u]=-2;
	return flow;
}
int dinic()
{
	int solve=0,f;
	while(bfs())
	{
		while(f=dfs(s,inf))solve+=f;
	}
	return solve;
}
int u[maxn],v[maxn],M,uu,vv,map[maxl][maxl];
int main()
{
	scanf("%d%d",&n,&m);
	s=0,t=n*2+10;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&uu,&vv);
		map[uu][vv]=1;
		u[++M]=uu,v[M]=vv;	
	}
	int ans1=inf;
	for(int i=1;i<=n;i++)
	{
		memset(head,-1,sizeof(head));
		cnt=0;
		int temp=0,tp=0;
		for(int j=1;j<=n;j++)add(s,j,1);
		for(int j=1;j<=n;j++)add(j+n,t,1);
		for(int j=1;j<=M;j++)
		{
			if(u[j]==i||v[j]==i)continue;
			add(u[j],v[j]+n,1);
			tp++;
		}
		for(int j=1;j<=n;j++)
		{
			if(!map[i][j])tp++;
			if(!map[j][i])tp++;
		}
		if(!map[i][i])tp--;
		temp+=dinic();
		ans1=min(n-temp+tp-1-temp,ans1);
	}
	ans+=ans1;
	printf("%d\n",ans);
}
```

---

## 作者：nb_jzy (赞：0)

## 题意
给你一个图，让你任意添加或删除一些边。

使得修改后的图满足以下性质：

1. 存在一个中心点 $u$，使得 $u$ 到其余点均存在 $(u,v)$ 和 $(v,u)$ 两条路径。以及自环 $(u,u)$。

1. 余的点的出度与入度均为 $2$。

## 发现

读完题目之后，我们可以发现一个性质，如果我们确定这个图的**中心点**，那么**中心点**除了**自环**，与其他点一定会有 $2n$ 条相连的边，以及自环的 $1$ 条边，总共 $2n+1$ 条边，我们便可以预处理每个点满足要求的边数有多少条，假设有 $x$ 条，我们便需要添加 $2n+1-x$ 条边。

于是我们就可以先枚举中心点。接着处理其余的点，要满足入度和出度均为 $2$，已知每个点已经分别与中心点连了一条边，也被中心点连了一条边。排除这些边，我们就需要满足其余的点的**入度与出度**均为 $1$ 即可。

入度与出度均为 $1$，好**特殊**的图。不难发现，剩下的点一定会构成一个或者是多个**环**。

要让剩下的点形成多个环，可以将原图转换为**二分图**实现。

我们将每一个点设一个新点 $v'$，若存在 $(a,v)$ 这条路径，我们就将 $a$ 与 $v'$ 相连。显然，新图是一个**二分图**。我们求出这个图的**最大匹配**，然后需要删除最大匹配以外的边，我们设最大匹配数为 $k$，图上总共存在 $m$ 条边，与**中心点**相关的边数为 $z$，数量即为 $m-z-k$。

为了使图构成多个环，我们需要满足新建的二分图存在**完美匹配**，于是需要添加 $n-1-k$ 条新边。

需要修改的边数即为上述数量之和，答案即为每个点作为中心点该值的最小值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,cnt[505],link[505],flag,anss=0x3f3f3f3f,vis[505];
vector<int> g[505],e[505];
bool large(int u){//匈牙利算法求最大匹配
	for(int it=0;it<e[u].size();it++){
		int i=e[u][it];
		if(vis[i]<flag){
			vis[i]=flag;
			if(link[i]==0||large(link[i])){
				link[i]=u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		if(a!=b) cnt[a]++,cnt[b]++;	
		else cnt[a]++;
		g[a].push_back(b);
	}
	for(int i=1;i<=n;i++){
		int ans=0,ff=0;
		ans=2*n-1-cnt[i];
		for(int j=1;j<=n;j++){
			e[j].clear(),vis[j]=0,link[j]=0;
		} //记得初始化
		for(int j=1;j<=n;j++){
			if(j==i) continue;
			for(int it=0;it<g[j].size();it++){
				if(g[j][it]==i) continue;
				e[j].push_back(g[j][it]);//建二分图
			}
		}
		flag=0;
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			flag++;
			if(large(j)) ff++;
		}
		ans+=(m-cnt[i]-ff)+(n-1-ff);
		anss=min(anss,ans);
	}
	cout<<anss<<endl;
	return 0; 
}
```

---

## 作者：peterwuyihong (赞：0)

题意：给定一张无重边有可能有自环的图，操作一次可以加上一条边和去掉一条边，问你至少操作几次可以使得这张图存在一个中心点 $x$，$x$ 与所有点 $y$ 有边 $(x,y),(y,x)$，注意必须也要有 $(x,x)$，然后除了 $x$ 的其他点 $y$ 的出入度均为 $2$。$1\le n\le 500$

首先枚举中心点 $x$，然后把与中心点相连的边处理掉，然后剩下的问题就是

给定一車点集，存在有向边，可能有自环，问最小操作次数，使得除了 $x$ 的其他点 $y$ 的出入度均为 $1$。

显然留下最多的边是最好的，剩下的可以自行配合。

这个东西拆一下点跑网络流就行了。

剩了 $n-1$ 个点，他们之间相连的边为 $m'$，匹配了 $v$ 组，那么 $m'-v$ 的边是没用的，又要加上 $\dfrac{2(n-1)-2v}2=n-1-v$ 条边。

中心点的相关分讨可能有点恶心，我先写写。

现在是 $18:45$，看我什么时候写完。

现在是 $18:57$，我写完了。

```cpp
using _Tp = int;
using i64 = long long;
i64 liu(vector<vector<pair<int,int>>>g,int S,int T){
  vector<int>d(g.size());
  vector<int>head(g.size(),-1),Next,ver,edge;
  int tot=0;
  auto add=[&](int x,int y,int z){
    ver.push_back(y),edge.push_back(z);
    Next.push_back(head[x]),head[x]=tot++;
  };
  for(int i=0;i<(int)g.size();i++)
  for(int j=0;j<(int)g[i].size();j++)
    add(i,g[i][j].first,g[i][j].second),add(g[i][j].first,i,0);
  auto bfs=[&](){
    queue<int>q;q.push(S);
    for(int i=0;i<(int)g.size();i++)d[i]=0;d[S]=1;
    while(q.size()){
      int x=q.front();q.pop();
      for(int i=head[x];~i;i=Next[i])
      if(!d[ver[i]]&&edge[i]){
        d[ver[i]]=d[x]+1;q.push(ver[i]);
        if(ver[i]==T)return 1;
      }
    }
    return 0;
  };
  function<int(int x,int flow)>dinic;
  dinic=[&](int x,int flow){
    if(x==T)return flow;
    int rest=flow,k;
    for(int i=head[x],y;y=ver[i],~i&&rest;i=Next[i])
    if(edge[i]&&d[y]==d[x]+1){
      k=dinic(y,min(rest,edge[i]));
      if(!k)d[y]=0;
      edge[i]-=k;
      edge[i^1]+=k;
      rest-=k;
    }  
    return flow-rest;
  };
  i64 ans=0;int u;
  while(bfs())while(u=dinic(S,INT_MAX))ans+=u;
  return ans;
}
signed main(){
  int n,m,S,T;
  cin>>n>>m;
  set<pair<int,int> >M;
  while(m--){
    int x,y;
    cin>>x>>y,x--,y--;
    M.emplace(x,y);
  }
  int ans=INT_MAX;
  auto solve=[&](int mid){
    vector<vector<pair<int,_Tp>>>g(2*n+2);
    auto add=[&](int x,int y,_Tp z){g[x].push_back(make_pair(y,z));};
    S=2*n,T=2*n+1;
    int ans=2*(n-1)+1,m0=0;
    for(auto[x,y]:M){
      if(x==mid&&y==mid)ans--;
      else if(x==mid)ans--;
      else if(y==mid)ans--;
      else add(y,x+n,1),m0++;
    }
    rep(i,0,n-1)add(S,i,1);
    rep(i,n,2*n-1)add(i,T,1);
    int v=liu(g,S,T);
    return ans+n-1-v+m0-v;
  };
  rep(i,0,n-1)ans=min(ans,solve(i));
  cout<<ans<<endl;
}
```

---

## 作者：云浅知处 (赞：0)

首先可以发现实际上除了中心点之外，每个点的入度和出度如果不算它们和中心点的连边，其实应该是 $1$。

我们考虑先删掉一些边，留下尽可能多的边，使得每个点的入度和出度**至多**为 $1$；然后再加上少的边。

把每个点 $u$ 拆成 $2$ 个点 $u,u+n$。对于原图中一条边 $(u,v)$，我们连边 $(u,v+n)$。

那么枚举中心点，在新图上跑二分图最大匹配，就得到了最多能留下的边数。

设其为 $x$，则答案为 $n+m-2x$。其含义是先删 $m-x$ 条边，再加 $n-x$ 条边。

实现起来时需要注意，枚举到中心点 $x$ 时：

- 剩下的点数实际上是 $n-1$，边数是 $m-\text{deg}_x$。这里 $\text{deg}$ 包括入度和出度，自环的入度和出度算一次。
- 答案还需要加上 $2n-1-\text{deg}_x$，表示连上 $x$ 的那 $2n-1$ 条边。

复杂度大概是 $O(nm\sqrt{n})$，实际上应该快得多。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

int n,m;
const int MN=2e5+5;
int head[MN],ver[MN],nxt[MN],edge[MN],tot=1;
int u[MN],v[MN];

#define C(p) (memset(p,0,sizeof(p)))

void adde(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,nxt[tot]=head[x],head[x]=tot;
	ver[++tot]=x,edge[tot]=0,nxt[tot]=head[y],head[y]=tot;
}

queue<int>q;
int d[MN],now[MN],s,t;

bool bfs(){
	memset(d,0,sizeof(d));
	while(q.size())q.pop();
	q.push(s),d[s]=1,now[s]=head[s];
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=nxt[i]){
			if((!edge[i])||d[ver[i]])continue;
			d[ver[i]]=d[x]+1,now[ver[i]]=head[ver[i]],q.push(ver[i]);
			if(ver[i]==t)return 1;
		}
	}
	return 0;
}

int dinic(int x,int flow){
	if(x==t)return flow;
	int rest=flow;
	for(int i=now[x];i&&rest;i=nxt[i]){
		now[x]=i;int y=ver[i];
		if((!edge[i])||d[y]!=d[x]+1)continue;
		int k=dinic(y,min(rest,edge[i]));
		rest-=k,edge[i]-=k,edge[i^1]+=k;
	}
	return flow-rest;
}

int deg[MN],res;
const int INF=1e9;

void solve(int x){
	C(head),C(nxt),C(ver),C(edge),tot=1;

	int ans=2*n-1-deg[x]+n-1+m-deg[x];
	for(int i=1;i<=m;i++){
		if(u[i]==x||v[i]==x)continue;
		adde(u[i],v[i]+n,INF);
	}
	for(int i=1;i<=n;i++)if(i!=x)adde(s,i,1),adde(i+n,t,1);
	
	int flow=0;
	while(bfs()){
		while(flow=dinic(s,INF))ans-=2*flow;
	}
	res=min(res,ans);
}

signed main(void){

	n=read(),m=read();s=0,t=2*n+1,res=3*n-1+m;
	for(int i=1;i<=m;i++)u[i]=read(),v[i]=read();
	for(int i=1;i<=m;i++){deg[v[i]]++;if(u[i]!=v[i])deg[u[i]]++;}
	for(int i=1;i<=n;i++)solve(i);cout<<res<<endl;

	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

这道题大概应该是用二分图匹配吧

## 题意：
在有向图中，通过加边、删边满足两个条件。

确定一个中心点 $u$，对于任意点 $v$，存在 $(u,v)$ 与 $(v,u)$，存在自环。

除中心点外的点的出度、入度都要为2。

求最小操作数。

## 分析：
首先枚举中心点 $u$。

与 $u$ 相连的边，直接计入保留的边中。

此外，还有非中心点 $v$，满足入度与出度均为1。

不妨拆一个点 $x$ 为 $x_{in}$ 和 $x_{out}$，不难得到一个小性质，对于边 $(x,y)$，$x_{out}$ 指向 $y_{in}$。

那所以，入点和出点的最大匹配就是最多保留的边，考虑用可爱的网络流来求解。

如果总共保留 $p$ 条边，包括与中心相连的 $2n-1$，不相连的 $n-1$，于是得到总的操作数 $3n-2+m-2x$，其中 $x$ 包含入边、出边和最大流的值。

## CODE：
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 20005
#define maxm 200005
using namespace std;
namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace q_wr;
struct edge {
	int v, nxt, w;
}e[maxm];
struct ledge {
	int u, v;
}l[maxm];
int n, m, s, t = maxn - 1, dep[maxn], head[maxn], k = 1;
inline void add (int u, int v, int w) {
	e[++k] = (edge){v, head[u], w};
	head[u] = k;
}
inline bool bfs () {
	memset(dep, 0, sizeof dep);
	queue <int> q;
	q.push(s);
	dep[s] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v;
			if (e[i].w && !dep[v]) {
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return dep[t];
}
inline int dfs (int u, int in) {
	if (u == t) return in;
	int out = 0;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (e[i].w && dep[v] == dep[u] + 1) {
			int res = dfs(v, min(e[i].w, in));
			in -= res;
			out += res;
			e[i].w -= res;
			e[i ^ 1].w += res;
		}
	}
	if (!out) dep[u] = 0;
	return out;
}//最大流
int in[maxn], out[maxn];
signed main () {
	n = read(), m = read();
	for (int i = 0; i < m; i++) {
		int u = read(), v = read();
		l[i] = (ledge){u, v};
		in[v]++, out[u]++;
		if (u == v) 
			in[v]--;
	}
	int res = maxm;
	for (int i = 1; i <= n; i++) {
		memset(head, 0, sizeof head);
		k = 1;
		int p = in[i] + out[i];
		for (int j = 1; j <= n; j++) {
			add(s, j, 1);
			add(j, s, 0);
			add (j + n, t, 1);
			add (t, j + n, 0);
		}//拆点
		for (int j = 0; j < m; j++) {
			if (l[j].u == i || l[j].v == i) //中心点
				continue;
			add (l[j].u, n + l[j].v, 1);
			add (n + l[j].v, l[j].u, 0);	
		}
		int ans = 0;
		while (bfs()) 
			ans += dfs(s, 1e12);
		res = min(res, (n << 1) + n - 2 + m - (p << 1) - (ans << 1));
	}
	write(res);
}
```


---

## 作者：SerokSSR (赞：0)

### 题意分析

操作最少的次数，构成有趣图，注意无重边，有向边。

- 操作分为加边和删边。
- 有趣图定义
  - 有一个中心，满足此点有自环，且与其他结点有双向边。
  - 除中心点外的结点，满足出度 = 入度 = 2。

### 算法分析

1、仔细分析有趣图的定义，发现如下性质：

- 中心的边数为 $(n-1)\times 2+1$，也就是它与其他结点要有双向边再加自己的一个自环，无重边所以构造中心点时不可能做删除操作，只能加边或不操作。
- 其他结点的出入度为 2，排除掉与中心点连接的双向边，其点的度一定为一进一出。

2、如何判断结点的度满足一进一出。

![](https://cdn.jsdelivr.net/gh/SerokSSR/img/cf387d1.png)

图一，图二都是满足结点度一进一出。所以 $n$ 个结点需要 $n$ 条相连边（首尾）。

![](https://cdn.jsdelivr.net/gh/SerokSSR/img/cf387d2.png)

图三不满足，只有两条相连边 $(e_1,e_2)$ 或者选择 $(e_1,e_3)$ 即有用边,还需要添加 $n-2$ 边有用边，同时还要减掉 1 条边，即总边数减去有用边，也就是要删除的无用边。

> 方法1：拆点，一个点拆为进点和出点，建立二分图。
>
> ​	![](https://cdn.jsdelivr.net/gh/SerokSSR/img/cf387d3.png)
>
> 左边的点求匹配，最大匹配就是有用的边。
>
> 方法2：直接将图看成二分图，利用有向边每个点都求匹配。

3、枚举每个点做中心点。

- 中心点 V，计算维护中心需要的边 $(n-1)\times 2+1-\sum{V发出的边}$

- 删除 V 点，也就是包含相应的边

- 剩下的图，计算最大匹配，满足一进一出的边数需要的操作（添加边 + 删除边）。

```cpp
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>
#include <iostream>
using namespace std;

const int N = 550, INF = INT_MAX;
vector<int> g[N];
int c, n, m;

int tag = 0, vis[N], match[N];
bool mp[N][N];

bool dfs(int u) {
	for(int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if(v == c) continue;
		if(vis[v] == tag) continue;
		vis[v] = tag;
		if(match[v] == 0 or dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int best = INF;

int main() {
	
	scanf("%d%d", &n, &m);
	
	int sum0 = 0;
	for(int i=1, u, v; i<=m; ++i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		mp[u][v] = true;
		++sum0;
	}
	
	for(int i=1; i<=n; ++i) {
		memset(match, 0, sizeof match);
		c = i;
		int ans = 0;
		int sum1 = 0;
		for(int j=1; j<=n; ++j) {
			if(j == c) {
				if(mp[c][c]) ++sum1;
				continue;
			}
			if(mp[j][c]) ++sum1;
			if(mp[c][j]) ++sum1;
		}
		ans += 2*(n-1) + 1 - sum1;
		//printf("ans1 = %d\n", ans);
		//printf("sum1 = %d\n", sum1);
		int sum2 = 0;
		for(int j=1; j<=n; ++j) {
			++tag;
			if(j == c) continue;
			if(dfs(j)) ++sum2;
		}
		
		ans += sum0 - sum1 - sum2 + n-1 - sum2;
		
		best = min(best, ans);
		//printf("ans2 = %d\n", ans);
		//printf("sum2 = %d\n", sum2);
	}
	
	printf("%d\n", best);
	return 0;
}
```

---

## 作者：Wen_kr (赞：0)

考虑枚举每个点作为起始点，我们可以发现一个显然的性质：

当所有点都有到中点的边且中点有到所有点的边时，除中点以外所有点要么构成自环，要么在一个环里面。

考虑把每个点拆点，跑二分图匹配，看在原图上的边最多能满足几条，因为没有重边，所以处理很简单。

我们设二分图中的边数为 $n$ ，匹配的边数为 $n_1$， 点的个数为 $p$ ，从中点到其他点要加的边数为 $cur$

那么 $ans = min\{(n - n_1) + (p - 1 - n_1) + cur\}$

代码：
```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

bool conn[555][555];
int inv[555],ouv[555];
int link[555];
int n,m;
bool vis[555];

bool dfs(int pos,int rt)
{
	for(int i = 1;i <= n; ++ i)
	{
		if(conn[pos][i] && i != rt && !vis[i])
		{
			vis[i] = 1;
			if(link[i] == -1 || dfs(link[i],rt))
			{
				link[i] = pos;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m; ++ i)
	{
		int fr,to;
		scanf("%d%d",&fr,&to);
		conn[fr][to] = 1;
		inv[to]++,ouv[fr]++;
	}
	int ouvx[555],invx[555];
	int minn = 0x3f3f3f3f;
	for(int i = 1;i <= n; ++ i)
	{
		memset(link,-1,sizeof(link));
		int cur = 0,tot = 0;
		memcpy(invx,inv,sizeof(inv));
		memcpy(ouvx,ouv,sizeof(ouv));
		int cnt = 0;
		int tmpm = m;
		for(int j = 1;j <= n; ++ j)
		{
			if(j != i)
			{
				if(!conn[i][j])
					cur++;
				else
					tmpm--;
				if(!conn[j][i])
					cur++;
				else
					tmpm--;
			}
			else
				cur += conn[i][i] ^ 1,tmpm -= conn[i][i];	
			if(j != i)
			{
				memset(vis,0,sizeof(vis));
				if(dfs(j,i))
					cnt++;
			}
		}
		cur += tmpm - cnt,cur += (n - 1) - cnt;
		minn = min(minn,cur);
	}
	printf("%d\n",minn);
	return 0;
}

```

---

