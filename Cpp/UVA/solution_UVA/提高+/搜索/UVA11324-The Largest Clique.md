# The Largest Clique

## 题目描述

给你一张有向图 $G$，求一个结点数最大的结点集，使得该结点集中的任意两个结点 $u$ 和 $v$ 满足：要么 $u$ 可以达 $v$，要么 $v$ 可以达 $u$ （$u,v$ 相互可达也行）。

## 样例 #1

### 输入

```
1
5 5
1 2
2 3
3 1
4 1
5 2```

### 输出

```
4```

# 题解

## 作者：ZAGER (赞：5)

## 题解

传送门：[透彻](https://www.cnblogs.com/ZAGER/p/9921720.html)

首先，我们会想到$Tarjan$缩点，将缩成的点的$siz$大小当做点权。

因为缩完点之后就会是一个$DAG$，所以可以跑DP。

这种题型有两种实现方式，$topsort$和记忆化搜索，代码中已注明。

转移就是$dp[v]=max(dp[v],dp[u]+siz[v])$.

## code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<queue>
#define R register
#define ll long long
#define N 1005
#define M 50005
using namespace std;
template<typename T>inline void read(T &a){
	char c=getchar();T x=0,f=1;
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	a=f*x;
}
int T,n,m,u[M],v[M],ru[N],siz[N],h[N],sta[N],low[N],dfn[N];
int top,num,tot,col[M],vis[N],dp[N],ans,cnt;
struct node{
	int nex,to;
}edge[M];
inline void add(R int u,R int v){
	edge[++tot].nex=h[u];
	edge[tot].to=v;
	h[u]=tot;
}
inline void Tarjan(R int x){
	dfn[x]=low[x]=++num;
	sta[++top]=x;vis[x]=1;
	for(R int i=h[x];i;i=edge[i].nex){
		R int xx=edge[i].to;
		if(!dfn[xx]){
			Tarjan(xx);
			low[x]=min(low[x],low[xx]);
		}
		else if(vis[xx])low[x]=min(low[x],dfn[xx]);
	}
	if(dfn[x]==low[x]){
		R int now=-1;
		cnt++;
		while(now!=x){
			now=sta[top];
			top--;
			col[now]=cnt;
			siz[cnt]++;
			vis[now]=0;
		}
	}
}
inline void init(){
	tot=num=top=ans=cnt=0;
	memset(h,0,sizeof(h));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(vis,0,sizeof(vis));
	memset(siz,0,sizeof(siz));
	memset(sta,0,sizeof(sta));
	memset(col,0,sizeof(col));
	memset(ru,0,sizeof(ru));
	memset(dp,-1,sizeof(dp));
}
inline void topsort(){
	queue<int> q;
	while(!q.empty())q.pop();
	for(R int i=1;i<=cnt;i++)
		if(!ru[i])q.push(i),dp[i]=siz[i];
	while(!q.empty()){
		R int x=q.front();q.pop();
		for(R int i=h[x];i;i=edge[i].nex){
			R int xx=edge[i].to;
			dp[xx]=max(dp[x]+siz[xx],dp[xx]);
			--ru[xx];
			if(!ru[xx])q.push(xx);
		}
	}
}
inline int search(R int x){
	if(dp[x]!=-1)return dp[x];
	R int res=siz[x];
	for(R int i=h[x];i;i=edge[i].nex){
		R int xx=edge[i].to;
		res=max(search(xx)+siz[x],res);
	}
	return dp[x]=res;
}
int main(){
	read(T);
	while(T--){
		read(n);read(m);init();
		for(R int i=1;i<=m;i++)
			read(u[i]),read(v[i]),add(u[i],v[i]);
		for(R int i=1;i<=n;i++)	
			if(!dfn[i])Tarjan(i);
		tot=0;memset(h,0,sizeof(h));
		for(R int i=1;i<=m;i++)
			if(col[u[i]]!=col[v[i]])
				add(col[u[i]],col[v[i]]),ru[col[v[i]]]++;
		//记忆化搜索 
		for(R int i=1;i<=cnt;i++)
			ans=max(ans,search(i));
		//拓扑排序 
		topsort();
		for(R int i=1;i<=cnt;i++)
			ans=max(ans,dp[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：封禁用户 (赞：5)

这道题目本人一开始用并查集做，结果。。。$WA$了。

后来，仔细一读题，图是有向边，且一个集合的任意两个点$u$和$v$只需要$u$可以到$v$,或者$v$可以到$u$即可。

于是，就想到了伟大的$Tarjan$算法。。。

我们先用$Tarjan$算出所有点各自属于哪个集合，然后用记忆化搜索：判断如果两个点$u$和$v$处于不同的集合，就进行记忆化搜索。

由于$Tarjan$算法以及记忆化搜索都比较基础，在此就不多解释啦。。。

好了，废话不多说，上代码吧。。。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 50080
#define maxm 200080
int T,first[maxn],nxt[maxm],vv[maxm],dfn[maxn],low[maxn],vis[maxn],st[maxn],belong[maxn],sum[maxn];
int n,m,e,cnt,p,t,ans,maxsum[maxn];
struct EDGE{
    int next,to;
}edge[maxm];
using namespace std;
void add(int u,int v)
{
    edge[e].to=v;
    edge[e].next=first[u];
    first[u]=e++;
}
void init()//初始化
{
    e=cnt=p=t=ans=0;
    memset(first,-1,sizeof(first));
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    memset(sum,0,sizeof(sum));
    memset(maxsum,-1,sizeof(maxsum));
}
void Tarjan(int u)//标准tarjan,求强连通分量 
{
    vis[u]=1;
    st[++p]=u;
    dfn[u]=low[u]=++cnt;
    for(int i = first[u]; i != -1; i = edge[i].next)
    {
        int v=edge[i].to;
        if (!dfn[v])
        {
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(vis[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++t;
        while(st[p]!=u)
        {
            vis[st[p]]=0;
            belong[st[p]]=t;
            sum[t]++;
            p--;
        }
        vis[st[p]]=0;
        belong[st[p]]=t;
        p--;
        sum[t]++;
    }
}
int dfs(int u)
{
    if(maxsum[u]!=-1) return maxsum[u];//如果当前这个点已有最优值，则返回 
    maxsum[u]=sum[u];
    int add=0;
    for(int i = 1; i <= n; i++)
    {
        if(belong[i]==u)//如果当前这个点处于要找的集合 
        {
            for(int j=first[i]; j!= -1; j = edge[j].next)
            {
                int v=edge[j].to;
                int belongv=belong[v];
                if(u==belongv) continue;//如果当前的目标点属于这个集合,就跳过 
                add=max(add,dfs(belongv));//记忆化搜索 
            }
        }
    }
    maxsum[u]+=add; 
    return maxsum[u];//返回最优解 
}
int read()//读入优化
{
    int f=1,x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9')
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return f*x;
}
int main()
{
    T=read();//组数 
    while (T--)
    {
        n=read(),m=read();
        init();//初始化 
        for (int i = 1; i <= m; i++)
        {
            int u,v;
            u=read(),v=read();
            add(u,v);//建边 
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) Tarjan(i);//tarjan模板 
        for (int i = 1; i <= t; i++) ans=max(ans,dfs(i));//记忆化搜索 
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Cylete (赞：2)

### tarjan缩点+topsort

同一个强连通分量里的点对题目无影响

所以对其缩点

储存在size里面，表示有x有size[x]个节点

再进行拓扑排序计算即可

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define next net
#define N 222222
int t,n,m,ans,x,y;
int cut,head[N],from[N],ver[N],next[N];
int tot,dfn[N],low[N],book[N],hh[N],top,all,belong[N],size[N],dp[N],ru[N];
void into(){
	cut=tot=top=all=ans=0;
	memset(head,0,sizeof(head));
	memset(ver,0,sizeof(ver));
	memset(from,0,sizeof(from));
	memset(next,0,sizeof(next));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(book,0,sizeof(book));
	memset(hh,0,sizeof(hh));
	memset(belong,0,sizeof(belong));
	memset(size,0,sizeof(size));
	memset(dp,0,sizeof(dp));
	memset(ru,0,sizeof(ru));
}
void add(int x,int y){
	ver[++cut]=y;from[cut]=x;next[cut]=head[x];head[x]=cut;
}
void tarjian(int x){
	dfn[x]=low[x]=++tot;
	hh[++top]=x;
	book[x]=1;
	for(int j=head[x];j;j=next[j]){
		int y=ver[j];
		if(!dfn[y]){
			tarjian(y);
			low[x]=min(low[x],low[y]);
		}
		else if(book[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		all++;
		int qwq;
		do{
			qwq=hh[top--];
			book[qwq]=0;
			belong[qwq]=all;
			size[all]++;//储存节点数 
		}while(hh[top+1]!=x);
	}
}
void topsort(){
	queue<int>q;
	for(int i=1;i<=all;i++)if(ru[i]==0)q.push(i),dp[i]=size[i];
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i]){
			int y=ver[i];
			ru[y]--;
			dp[y]=size[y]+dp[x];
			if(ru[y]==0)q.push(y);
		}
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		into();//初始化 
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		for(int i=1;i<=n;i++)if(!dfn[i])tarjian(i);//tarjan缩点 
		memset(head,0,sizeof(head));
		cut=0;
		for(int i=1;i<=m;i++){//重构图 
			x=belong[from[i]],y=belong[ver[i]];
			if(x!=y){
				add(x,y);
				ru[y]++;
			}
		} 
		topsort();//拓扑 
		for(int i=1;i<=all;i++)ans=max(ans,dp[i]);
		printf("%d\n",ans);
	}
    return 0;
}
```


---

## 作者：AKA_刀枪不入 (赞：2)

给一张有向图G，求一个结点数最大的结点集，使得该结点集中任意两个结点u和v满足：要么u可以到达v，要么v可以到达u（u和v相互可达也可以）。
 
输入第一行为测试数据组数T。每组数据第一行为结点数n和边数m(0<=n<=1000,0<=m<=50000)。以下m行每行两个整数u和v，表示一条有向边u—>v。结点编号1~n。
 
对于每组数据，输出最大结点集的结点个数。

分析： 
不强制双向到达，求最大团 
显然一个强连通分量中的点要么都选，要么都不选 
我们可以用Tarjan把强连通分量缩点得到SCC图 
SCC图中每一个点的权值就是这个SCC中点的数量 
问题就转化成， 
在图中选择若干个点使得权值和最大 
求SCC图中的最大权路径

由于SCC图是一个DAG，我们可以用dp来解决这个问题 
dp转移方程为# f[x] = size[x] + max(f[y])
```
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

const int N=1002;
int n,m,scc[N],tot,low[N],pre[N],cnt,size[N];
int f[N],in[N],st[N],tt;
struct node{
    int y,nxt;
};
node way[50010];
vector<int> G[N];
stack<int> S;

void add(int u,int w)
{
    tt++;
    way[tt].y=w;way[tt].nxt=st[u];st[u]=tt;
}

void dfs(int now)
{
    pre[now]=low[now]=++tot;
    S.push(now);   //
    for (int i=st[now];i;i=way[i].nxt)
    {
        int v=way[i].y;
        if (!pre[v])
        {
            dfs(v);
            low[now]=min(low[now],low[v]);
        }
        else if (!scc[v])
        {
            low[now]=min(low[now],pre[v]);
        }
    }

    if (low[now]==pre[now])
    {
        cnt++;
        int tt=0;
        for (;;)
        {
            int x=S.top();
            S.pop();
            scc[x]=cnt;
            tt++;
            if (x==now) break;
        }
        size[cnt]=tt;   //SCC的大小 
    }
}

void find()
{
    memset(pre,0,sizeof(pre));
    memset(scc,0,sizeof(scc));
    while (!S.empty()) S.pop();
    tot=0; cnt=0;
    for (int i=1;i<=n;i++)
        if (!pre[i])
            dfs(i);
}

int dp(int now)
{
    if (f[now]) return f[now];   //记忆化
    int ans=0;
    for (int i=0;i<G[now].size();i++)
    {
        int v=G[now][i];
        ans=max(ans,dp(v));
    } 
    f[now]=ans+size[now];
    return f[now];
}

void solve()
{
    memset(in,0,sizeof(in));
    memset(f,0,sizeof(f));
    for (int i=1;i<=n;i++) G[i].clear(); 

    for (int i=1;i<=n;i++)
        for (int j=st[i];j;j=way[j].nxt)
        {
            int v=way[j].y;       //i--->v
            if (scc[i]!=scc[v])   //不在一个SCC中
            {
                G[scc[i]].push_back(scc[v]);
                in[scc[v]]++;
            } 
        }

    int ans=0;
    for (int i=1;i<=cnt;i++)
        if (!in[i])   //入度为0
           ans=max(ans,dp(i));
    printf("%d\n",ans);
}

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        memset(st,0,sizeof(st));
        tt=0;

        scanf("%d%d",&n,&m);
        for (int i=1;i<=m;i++)
        {
            int u,w;
            scanf("%d%d",&u,&w);
            add(u,w);
        }

        find();

        solve();
    }
    return 0;   
}
```

---

## 作者：地表最强男人 (赞：1)

- 这题首先可以想到是先缩点，因为一个强连通分量里面的点都不会产生影响，因为如果有一个点可以到强连通分量的点，那么一定可以到达强连通分量的其他点，而一个强连通分量的点能够到达的点，其他强连通分量中的点也可以通过这个点到达这个点能够到达的点。
- 然后缩点完就是一个有向无环图，问题就变成了找到一个最大的点集，使得这个点集中的点任意两个点中，有一个点能够到达另一个点。其实就变成了最长链。一条链上的点都能够一条走下去，所以就是找最长链的大小。这个通过记忆化搜索来解决。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=10100,M=500010;
int n,m;
int head[N],ver[M],Next[M],tot;
int dfn[N],low[N],stack[N<<1],num,cnt,top,c[N],ru[N],ans,f[N];//num是编号,cnt是几个强连通分量 
int head1[N],ver1[M],Next1[M],tot1,anss;
bool ins[N],vis[N];
vector<int> scc[N];
queue<int> q;
int t;
void pre()
{
        memset(head,0,sizeof(head));
        memset(head1,0,sizeof(head1));
        memset(dfn,0,sizeof(dfn));
        memset(stack,0,sizeof(stack));
        memset(ins,0,sizeof(ins));
        memset(ru,0,sizeof(ru));
        memset(c,0,sizeof(c));
        for(int i=1;i<=N;i++)
            scc[i].clear();
        tot=tot1=ans=top=cnt=num=anss=0;
}
void add(int x,int y)
{
        ver[++tot]=y;
        Next[tot]=head[x],head[x]=tot;
} 
void Add(int x,int y)
{
        ver1[++tot1]=y;
        Next1[tot1]=head1[x],head1[x]=tot1;
}
void tarjan(int x)
{
        dfn[x]=low[x]=++num;
        stack[++top]=x;
        ins[x]=1;
        for(int i=head[x];i;i=Next[i])
        {
            int y=ver[i];
            if(!dfn[y])
            {
                tarjan(y);
                low[x]=min(low[x],low[y]);
            }
            else if(ins[y])
                low[x]=min(low[x],low[y]);
        }
        if(dfn[x]==low[x])
        {
            int y;
            cnt++;
            do
            {
                y=stack[top--];
                scc[cnt].push_back(y);
                c[y]=cnt;
                ins[y]=0;
            }while(y!=x);
        }
}
int dfs(int x)
{
        if(f[x])
            return f[x];
        vis[x]=1;
        int anss=0;
        for(int i=head1[x];i;i=Next1[i])
        {
            int y=ver1[i];
                anss=max(anss,dfs(y));
        }
        f[x]=anss+scc[x].size();
        return f[x];
}
int main()
{
        cin>>t;
        while(t--)
        {
            pre();
            cin>>n>>m;
            for(int i=1;i<=m;i++)
            {
                int x,y;
                cin>>x>>y;
                add(x,y);
            }
            for(int i=1;i<=n;i++)
                if(!dfn[i])
                    tarjan(i);
            for(int x=1;x<=n;x++)
            {
                for(int i=head[x];i;i=Next[i])
                {
                    int y=ver[i];
                    if(c[x]==c[y])	continue;
                    Add(c[x],c[y]);
                    ru[c[y]]++;
                }
            }
            for(int i=1;i<=cnt;i++)
                if(!ru[i])
                {
                    memset(vis,0,sizeof(vis));
                    memset(f,0,sizeof(f));
                    ans=max(ans,dfs(i));
                }
            cout<<ans<<endl;
        }
        return 0;
}
```



---

## 作者：Yeji_ (赞：1)

## 前言
这道题目，属于一道比较难的题，所以来写一下题解

## 思路
题目中既然有说可以成环，所以说可以用tarjan

而之后可以用DAGdp来做

所以整体思路是缩点+dp

而状态转移方程可以直接套DAGdp的模板。

代码如下
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int T,st[200080],dfn[200080],dis[2000],low[200080],vis[200080],u,v,is[200080],sum[200080];
int t,ans,tot,msum[200080],summ,n,m,cnt;
struct Edge
{
    int next,to;
}edge[200080];
void add(int u,int v)
{
    edge[tot].to=v;
    edge[tot].next=st[u];
    st[u]=tot++;
}
void tarjan(int u)
{
    vis[u]=1;
    dis[++summ]=u;
    dfn[u]=low[u]=++cnt;
    for (int i=st[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else 
            if (vis[v]) 
                low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u])
    {
        ++t;
        while(dis[summ]!=u)
        {
            vis[dis[summ]]=0;
            is[dis[summ]]=t;
            sum[t]++;
            summ--;
        }
        vis[dis[summ]]=0;
        is[dis[summ]]=t;
        summ--;
        sum[t]++;
    }
}
int dfs(int u)
{
    if (msum[u]!=-1) 
        return msum[u];
    msum[u]=sum[u];
    int add=0;
    for (int i=1;i<=n;i++)
    {
        if (is[i]==u)
        {
            for (int j=st[i];j!=-1;j=edge[j].next)
            {
                int v=edge[j].to;
                int belongv=is[v];
                if (u==belongv) 
                    continue;
                add=max(add,dfs(belongv)); 
            }
        }
    }
    msum[u]+=add; 
    return msum[u];
}
int main()
{
	cin>>T;
    while (T--)
    {
    	cin>>n>>m;
        tot=cnt=summ=t=ans=0;
        memset(st,-1,sizeof st);memset(dfn,0,sizeof dfn);
        memset(vis,0,sizeof vis);memset(sum,0,sizeof sum);
        memset(msum,-1,sizeof msum);
        for (int i=1;i<=m;i++)
        {
            cin>>u>>v;
            add(u,v); 
        }
        for (int i=1;i<=n;i++)
            if (!dfn[i]) 
                tarjan(i);
        for (int i=1;i<=t;i++) 
            ans=max(ans,dfs(i));
        printf("%d\n",ans);
    }
}
```


---

## 作者：Gauss0320 (赞：0)

Given a directed graph $G$, consider the following transformation.
First, create a new graph $T(G)$ to have the same vertex set as G. Create a directed edge between two vertices u and v in $T(G)$ if and only if there is a path between u and v in $G$ that follows the directed edges only in the forward direction. This
graph $T(G)$ is often called the transitive closure of $G$.

We define a clique in a directed graph as a set of vertices $U$ such that for any two vertices u and v in $U$, there is a directed edge either from u to v or from v to u (or both).
The size of a clique is the number of vertices in the clique.
## Input
The number of cases is given on the first line of input. Each test case describes a graph $G$4. It begins with
a line of two integers n and m, where 0 ≤ n ≤ 1000 is the number of vertices of $G$ and $0 ≤ m ≤ 50, 000$
is the number of directed edges of $G$. The vertices of G are numbered from 1 to n. The following m
lines contain two distinct integers u and v between 1 and n which define a directed edge from u to v in
$G$.
## Output
For each test case, output a single integer that is the size of the largest clique in $T(G)$
## Solution
由于题目要求的二元组要求至少单向连通，所以我们可以用Tarjan求出强连通分量缩点为DAG

对于一个SCC，它对答案的贡献即为他所包含的原图的结点数，令它为点的权值

那么结论就很显然了，我们在所求的DAG上跑DP,求一遍最长路即可。

代码如下
```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;
const int N = 10001;
int T, n, m, x, y, scc, dfs_clk, top, ans;
int sccno[N], dfn[N], low[N], stack[N], val[N], f[N];
bool instack[N];
vector<int> G[N];
vector<int> newmap[N];

void Tarjan(int x)
{
	dfn[x] = low[x] = ++dfs_clk;
	stack[++top] = x;
	instack[x] = 1;
	for(int i = 0; i < G[x].size(); i++)
	{
		int y = G[x][i];
		if(!dfn[y])
		{
			Tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if(instack[y])
		{
			low[x] = min(low[x], dfn[y]);
		}
	}
	if(dfn[x] == low[x])
	{
		scc++;
		do
		{
			instack[stack[top]] = 0;
			sccno[stack[top]] = scc; 
		}while(stack[top--] != x);
	}
}
int dfs(int x)
{
	if(f[x])
	{
		return f[x];
	}
	for(int i = 0; i < newmap[x].size(); i++)
	{
		int y = newmap[x][i];
		f[x] = max(f[x], dfs(y));
	}
	return f[x] = f[x] + val[x];
}
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d %d", &n, &m);
		dfs_clk = scc = top = ans = 0;
		memset(sccno, 0, sizeof sccno);
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		memset(instack, 0, sizeof instack);
		memset(val, 0, sizeof val);
		memset(f, 0, sizeof f);
		for(int i = 1; i <= n; i++)
		{
			G[i].clear();
			newmap[i].clear();
		}
		for(int i = 1; i <= m; i++)
		{
			scanf("%d %d", &x, &y);
			G[x].push_back(y); 
		}
		for(int i = 1; i <= n; i++)
		{
			if(!dfn[i])
			{
				Tarjan(i);
			}
		}
		for(int i = 1; i <= n; i++)
		{
			val[sccno[i]]++;
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j < G[i].size(); j++)
			{
				int v = G[i][j];
				if(sccno[i] != sccno[v])
				{
					newmap[sccno[i]].push_back(sccno[v]);
				}
			}
		}
		for(int i = 1; i <= scc; i++)
		{
			ans = max(ans, dfs(i));
		}
		printf("%d\n", ans);
	}
	return 0;
} 
```


---

## 作者：RainFestival (赞：0)

给你一张有向图G，求一个结点数最大的结点集，使得该结点集中的任意两个结点u和v满足：要么u可以达v，要么v可以达u

这道题先一看，觉得是个搜索，但是我们发现可能图中可能有自环，这怎么办呢

搜索不容易处理

于是我们再看题目，题目中的定义很像强连通分量？？？

只不过只要求一个（u->v或v->u有路径）就可以了

我们可以先用tarjan缩点，

此时图中已不存在自环

然后重新连边，这是每个点（强连通分量）的价值（点权）
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int kkk[1005],ll[1005],mmax[1005],aa[1005],dfn[1005],low[1005],a[1005],vis[1005],l[1005],sum[1005];
int num,top,s,n,m,ans;
bool v[1005];
int t;
int b[1005][1005],scc[1005][1005],c[1005][1005];
void tarjan(int u)
{
    num++;
    low[u]=dfn[u]=num;
    top++;
    a[top]=u;
    vis[u]=true;
    for (int i=1;i<=l[u];i++)
    {
        int v=b[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if (vis[v]) low[u]=min(low[u],low[v]);
    }
    if (dfn[u]==low[u])
    {
        s++;
        sum[s]=1;
        scc[s][sum[s]]=u;
        kkk[u]=s;
        vis[u]=false;
        while (a[top]!=u)
        {
        	sum[s]++;
        	vis[a[top]]=false;
        	scc[s][sum[s]]=a[top];
        	kkk[a[top]]=s;
        	a[top]=0;
        	top--;
        }
        a[top]=0;
        top--;
    }
}



void dfs(int u)
{
    int p=0;
    v[u]=1;
    for (int i=1;i<=s;i++) 
        if (c[u][i])
        {
        	if (!v[i]) dfs(i);
        	p=max(p,mmax[i]);;
        }
    mmax[u]=sum[u]+p;
    return;   
}



int main()
{
    scanf("%d",&t);
    while (t--)
    {
        num=0;
        for (int i=1;i<=s;i++)
        {
            for (int j=1;j<=sum[i];j++)
                scc[i][j]=false;
            sum[i]=ll[i]=0;
        }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=l[i];j++)
                b[i][j]=0;
        for (int i=0;i<=s;i++)
            for (int j=0;j<=s;j++)   
                c[i][j]=0;  
        for (int i=1;i<=n;i++)   
            low[i]=dfn[i]=l[i]=ll[i]=mmax[i]=v[i]=kkk[i]=0; 
        s=0;
        scanf("%d%d",&n,&m);
        for (int i=1;i<=m;i++)
        {
        	int x,y;
            scanf("%d%d",&x,&y);
            l[x]++;
            b[x][l[x]]=y;
        }
        for (int i=1;i<=n;i++) if (!dfn[i]) tarjan(i);
        for (int i=1;i<=s;i++) 
        {
            for (int j=1;j<=sum[i];j++)
            {
                int u=scc[i][j];
                for (int k=1;k<=l[u];k++)
                    c[i][kkk[b[u][k]]]=1;
            }
        }
        int ans=0;
        for (int i=1;i<=s;i++) if (!v[i]) dfs(i);
        for (int i=1;i<=s;i++) ans=max(ans,mmax[i]);
        printf("%d\n",ans);
    }
    return 0;
} 
```

时间60ms，空间0KB，代码长度2.21kb（删调试语句之前）

谢谢观赏

---

## 作者：Maktub (赞：0)

这个题看起来和[缩点](https://www.luogu.org/problemnew/show/P3387)很像，后来发现就是多组数据的缩点，按着那个题的思路做就行。

首先缩点是必须的，在同一个强联通分量中点可以两两互相达到，我们把缩点后强联通分量中点的个数作为新点的权值，然后用新点建新图，新图是个有向无环图，新图中任意一点，都存在以这个点为起点所达到的点的权值和的最大值，最优解为这些最大值中的最大值。这个问题可以用DP来解决。

简单来说，缩点，建新图，跑DAG dp，就可以过这个题了。

注意初始化。

代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();
    }
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();
    }return x*f;
}
const int mxn=1050;const int mxm=1e6+5;
int h[mxn],dfn[mxn],low[mxn],st[mxn],co[mxn],s[mxn],f[mxn];
int n,m,p,ans,col,t,top,num;
struct node{
    int next,v;
}e[mxm],e1[mxm];
inline void add(int a,int b){
    p++;e[p].next=h[a];h[a]=p;e[p].v=b;
}
int h1[mxn],p1;
inline void add1(int a,int b){
    p1++;e1[p1].next=h1[a];h1[a]=p1;e1[p1].v=b;
}
//-------
inline void tarjan(int u){
    dfn[u]=low[u]=++num;
    st[++top]=u;
    for(int i=h[u];i;i=e[i].next){
        int v=e[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!co[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(dfn[u]==low[u]){
        ++col;
        while(st[top+1]!=u){
            co[st[top]]=col;
            s[col]++;
            top--;
        }
    }
}
inline void dp(int x,int fa){
    if(f[x])return ;
    f[x]=s[x];int maxx=0;
    for(int i=h1[x];i;i=e1[i].next){
        int v=e1[i].v;
        if(v==fa)continue;
        dp(v,x);
        maxx=max(f[v],maxx);
    }
    f[x]+=maxx;
}
int main(){
    t=read();
    while(t--){
        ans=0;p=0;p1=0;top=0;num=0;col=0;
        for(int i=0;i<mxn;i++){
            h[i]=h1[i]=co[i]=dfn[i]=low[i]=st[i]=s[i]=f[i]=0;
        }
        n=read();m=read();
        if(n==0){
            printf("0\n");continue;
        }
        if(m==0){
            printf("1\n");continue;
        }
        for(int i=1,u,v;i<=m;i++){
            u=read();v=read();
            add(u,v);
        }
        for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
        for(int i=1;i<=n;i++){
            for(int j=h[i];j;j=e[j].next){
                int v=e[j].v;
                if(co[i]!=co[v])add1(co[i],co[v]);
            }
        }
        for(int i=1;i<=col;i++){
            if(!f[i])dp(i,0);
            ans=max(ans,f[i]);
        }
        printf("%d\n",ans);
        
    }
    
    
}
```

---

## 作者：封禁用户 (赞：0)

## Ad
个人博客高清重制版同步：http://www.cinema000.xyz/1557.ruby
## 分析

其实这里简化后就是在SCC缩点后的DAG上跑最长路就好了，点权为每个SCC的结点个数。

SCC缩点这里采用Kosaraju算法，DAG最长路用的是一个记忆化的DP来搞。

## 代码

Kosaraju部分其实没啥好看的，故缩行

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
const int INF = 0x3f3f3f3f;
const int MAXN = 1000 + 600;
struct Edge{int v,d;Edge(int v,int d){this -> v = v;this -> d = d;}};
int TG[MAXN][MAXN];
class SCC{
public:
	std::vector<Edge> G[MAXN],G2[MAXN];std::vector<int> S;
	int SCCNo[MAXN],SCCCnt,size[MAXN],d[MAXN];
	bool hash[MAXN];
	void addEdge(int u,int v,int d){G[u].push_back(Edge(v,d));G2[v].push_back(Edge(u,d));}
    void dfs1(int u){if(hash[u]) return;hash[u] = true;for(int i = 0;i < G[u].size();i++) dfs1(G[u][i].v);S.push_back(u);}
    void dfs2(int u){if(SCCNo[u]) return;SCCNo[u] = SCCCnt;for(int i = 0;i < G2[u].size();i++) dfs2(G2[u][i].v);}
    void findSCC(int n){SCCCnt = 0;for(int i = 0;i < n;i++) dfs1(i);for(int i = n - 1;i >= 0;i--) if(!SCCNo[S[i]]){SCCCnt++;dfs2(S[i]);}}
	void build(int n){
		for(int i = 0;i < n;i++){
			size[SCCNo[i]]++;
			for(int j = 0;j < G[i].size();j++){
				TG[SCCNo[i]][SCCNo[G[i][j].v]] = 1;
			}
		}
	}
	int dp(int u){
		int &ans = d[u];
		if(ans >= 0) return ans;
		ans = size[u];
		for(int v = 1;v <= SCCCnt;v++)
			if(u != v && TG[u][v]) ans = std::max(ans,dp(v) + size[u]);
		return ans;
	}
	void rebuild(){
	    for(int i = 0;i < MAXN;i++) G[i].clear(),G2[i].clear();
	    std::fill(size,size + MAXN,0);std::fill(d,d + MAXN,-1);memset(TG,0,sizeof(TG));
	    std::fill(hash,hash + MAXN,false);std::fill(SCCNo,SCCNo + MAXN,0);S.clear();
	}
};

int main(){
	SCC s;
	int T;scanf("%d",&T);
	while(T--){
	    s.rebuild();
		int n,m,u,v,d = 666,ans = 0;scanf("%d %d",&n,&m);
		while(m--){scanf("%d %d",&u,&v);u--;v--;s.addEdge(u,v,d);}
		s.findSCC(n);s.build(n);
		for(int i = 1;i <= s.SCCCnt;i++) ans = std::max(ans,s.dp(i));
		printf("%d\n",ans);
	}
	
	return 0;
}
```



---

