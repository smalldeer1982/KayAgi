# Digital Village (Easy Version)

## 题目描述

**这是问题的简单版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0```

# 题解

## 作者：linjunye (赞：4)

### 题目描述
有一个 $n$ 个点、$m$ 条边的无向图，其中第 $i$ 条边连接着 $u_i$ 和 $v_i$，权值为 $w_i$。

现在有 $p$ 个关键点，分别为 $s_1,s_2,\cdots,s_n$。

现在可以选择 $k$ 个点，所有关键点都要一个点，代价为它们之间的最大边权。当然，它们之间可能有多条路径，那么就取一条路径，使得这条路径的最大边权是最小的。

对于 $k=1,2,\cdots,n$，请计算最小总代价。

保证 $n^3+m^3\le 10^8$。
### 解题思路
考虑如何暴力。

首先，枚举 $k$ 是无法避免的。其次，假设我们已经知道 $k-1$ 时的最小总代价，那么，我们需要改变前几个点的选择吗？

答案是否定的。如果要修改，那为什么不在之前就改掉呢？

那么，我们就只用考虑第 $k$ 个点的选择了，直接循环即可。

最后，我们还需要从新计算最小总代价。那就定义一个 $dis$ 数组，$dis_i$ 表示第 $i$ 个关键点的最小代价。假设我们已经知道第 $i$ 个关键点与枚举的点之间最小的最大边权，那么就更新 $dis_i$，具体是求 $dis_i$ 和这个边权的最小值。

现在，我们需要考虑如何确定两个点之间最小的最大边权？

我们可以借鉴 Floyd 的思路来思考。

我们定义 $dp_{i,j}$ 表示 $i$ 和 $j$ 之间最小的最大边权。

我们先抓住“最小的”，说明转移方程为：$dp_{i,j}=\min\{\dots\}$。

然后抓住“最大的边权”，结合前面的转移方程，最终的转移方程为：$dp_i=\min\limits_{k=1}
^{n}\{\max\{dp_{i,k},dp_{k,j}\}\}$。

dp 的总体复杂度为 $O(n^3)$，里面暴力枚举的复杂度为 $O(n^2p)$。最差情况下（$n=p$），总体复杂度为 $O(n^3)$，发现可以通过。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=410;
const int INF=1e18;
int T;
int n,m,p;
int u,v,w;
int G[N][N];//文中提到的dp
int a[N];
int vis[N];
int dis[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>p;
		for(int i=1;i<=n;i++)vis[i]=0,dis[i]=INF;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(i==j)G[i][j]=0;
				else G[i][j]=INF;
			}
		for(int i=1;i<=p;i++)cin>>a[i];
		for(int i=1;i<=m;i++){
			cin>>u>>v>>w;
			G[u][v]=w;
			G[v][u]=w;
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					G[i][j]=min(G[i][j],max(G[i][k],G[k][j]));
		for(int i=1;i<=n;i++){
			int mn=INF,id=0;
			for(int j=1;j<=n;j++){
				if(vis[j])continue;//不重复不劣（好证明的），减少运行次数
				int sum=0;
				for(int k=1;k<=p;k++)
					sum+=min(dis[a[k]],G[a[k]][j]);
				if(mn>sum){
					mn=sum;
					id=j;//最优点
				}
			}
			vis[id]=1;
			cout<<mn<<" ";
			int sum=0;
			for(int j=1;j<=p;j++)
				dis[a[j]]=min(dis[a[j]],G[a[j]][id]);
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：harmis_yz (赞：4)

E3 太难了，只能秒 E2。

## 分析

要使得路径最大值最小，优先考虑建一棵重构树出来。那么问题转化为树形 DP。定义状态函数 $f_{i,j}$ 表示 $i$ 为根的子树中选择 $j$ 的点的最小路径长度和。因为重构树是一棵二叉树，且点权表示了两个子树中任意两个点的路径长度最小最大值。所以有：$f_{v0,0}=cnt_{v0}\times val_u,f_{v1,0}=cnt_{v1}\times val_u$。其它的 $f_{v,j}$ 都已经求出来了，暴力枚举即可。转移方程为：$f_{u,i+j}=\min\{f_{v0,i}+f_{v1,j}|0 \le i \le siz_{v0} \land 0 \le j \le siz_{v1}\}$。这里 $cnt_i$ 表示 $i$ 为根的子树中关键点的数量，$siz_i$ 表示 $i$ 为根的子树中原本图上的点的数量。复杂度 $O(n^2)$。

然后 E1 和 E2 就能一起过了。但是如果你直接开这样一个二维数组可能会爆空间，开动态数组即可（每个点开到 $siz$ 就够了）。

## 代码

```cpp
il int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
il void dfs(int u){
	siz[u]=0,Siz[u]=0;
	v[u].clear();
	if(!tr[u].ch[2]){
		v[u].push_back(0),v[u].push_back(0);
		siz[u]=vis[u],Siz[u]=1;
		return ;
	}
	dfs(tr[u].ch[0]),dfs(tr[u].ch[1]);
	for(re int i=0;i<=n;++i) dp[i]=1e18;
	v[tr[u].ch[0]][0]=(siz[tr[u].ch[0]]?siz[tr[u].ch[0]]*tr[u].val:0ll);
	v[tr[u].ch[1]][0]=(siz[tr[u].ch[1]]?siz[tr[u].ch[1]]*tr[u].val:0ll);
	for(re int i=0;i<=Siz[tr[u].ch[0]];++i)
	for(re int j=0;j<=Siz[tr[u].ch[1]];++j)
		if(i==0&&j==0) dp[i+j]=0;
		else dp[i+j]=min(dp[i+j],v[tr[u].ch[0]][i]+v[tr[u].ch[1]][j]);	
	siz[u]=siz[tr[u].ch[0]]+siz[tr[u].ch[1]];
	Siz[u]=Siz[tr[u].ch[0]]+Siz[tr[u].ch[1]];
	for(re int i=0;i<=Siz[u];++i) v[u].push_back(dp[i]);
	return ;
}

il void solve(){
	n=rd,m=rd,p=rd,idx=0,cnt=0;
	for(re int i=1;i<=2*n;++i) h[i]=0,tr[i]={0,0,0},f[i]=i,vis[i]=0;
	for(re int i=1;i<=p;++i) vis[rd]=1;
	for(re int i=1;i<=m;++i) E[i]={rd,rd,rd};
	sort(E+1,E+m+1),cnt=n;
	for(re int i=1;i<=m;++i){
		int x=E[i].x,y=E[i].y;
		if(find(x)==find(y)) continue;
		++cnt;
		tr[cnt].ch[0]=find(x),tr[cnt].ch[1]=find(y);
		tr[cnt].val=E[i].z;
		f[find(x)]=f[find(y)]=find(cnt);
	}
	dfs(cnt);
	for(re int i=1;i<=n;++i) printf("%lld ",v[cnt][i]);
    return ;
}
```

---

## 作者：xiaofu15191 (赞：1)

将“需要网络的房子”命名为关键点。

我们发现一个比较显然的性质：把服务器建在关键点是优的。因此，考虑对于关键点，假如只在这个房子建服务器，处理出此时它到另外的每一个关键点的延迟。这个用 Floyd 都可以处理。

然后开始 DP。设 $F_{i,k}$ 表示当前已经建了 $i$ 台服务器，第 $k$ 个关键点的延迟。对于每一个 $i$，设 $g_k$ 表示从 $F_{i-1,k}$ 转移过来的关键点 $k$ 的最小延迟，枚举第 $i$ 个要建的服务器 $j$ 来转移。然后，如果 $ \displaystyle \sum_{k=1}^{p} g_k < \sum_{k=1}^{p} F_{i-1,k}$，那么就用 $g$ 来更新 $F_{i-1}$。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
struct edge
{
	long long to,v;
};
vector<edge>graph[410];
long long n,m,p,need[410],dis[410][410],f[410][410],g[410];
bool bz[410];
struct status
{
	long long now,v;
};
bool operator < (const status&a,const status&b)
{
	return a.v>b.v;
}
void search(long long s)
{
	memset(dis[s],0x3f,sizeof(dis[s]));
	memset(bz,false,sizeof(bz));
	priority_queue<status>q;
	q.push((status){s,0});
	dis[s][s]=0;
	while(!q.empty())
	{
		status now=q.top();q.pop();
		if(bz[now.now]) continue;
		bz[now.now]=true;
		for(auto e:graph[now.now])
		{
			long long to=e.to,w=e.v;
			if(dis[s][to]>max(dis[s][now.now],w))
			{
				dis[s][to]=max(dis[s][now.now],w);
				q.push((status){to,max(w,now.v)});
			}
		}
	}	
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&m,&p);
		for(long long i=1;i<=n;i++)
		{
			graph[i].clear();
			need[i]=0;
		}
		for(long long i=1;i<=p;i++) scanf("%lld",&need[i]);
		for(long long i=1;i<=m;i++)
		{
			long long u,v,w;
			scanf("%lld%lld%lld",&u,&v,&w);
			graph[u].push_back((edge){v,w});
			graph[v].push_back((edge){u,w});
		}
		for(long long i=1;i<=p;i++)
		{
			long long start=need[i];
			search(start);
		}
		memset(f,0x3f,sizeof(f));
		for(long long i=1;i<=n;i++)
		{
			for(long long j=1;j<=p;j++)
			{
				memset(g,0x3f,sizeof(g));
				for(long long k=1;k<=p;k++)
				{
					long long from=need[j],to=need[k];
					g[k]=min(g[k],min(f[i-1][k],dis[from][to]));
				}
				long long sum=0;
				for(long long k=1;k<=p;k++) sum+=g[k];
				if(sum<f[i][0])
				{
					f[i][0]=sum;
					for(long long j=1;j<=p;j++) f[i][j]=g[j];
				}
			}
			printf("%lld ",f[i][0]);
		}
		printf("\n");
	}
}
```

---

## 作者：lfxxx (赞：0)

首先建出 kruskal 重构树。

房屋到一个服务器的代价就是两点在重构树上的 LCA 所代表的边的边权。

然后我们观察一下，对于一个子树而言，假若子树中存在至少一个服务器，那么子树内的所有点与这个服务器匹配，代价为子树根的权值，是优于与子树外任意服务器匹配的，因为重构树上一个点的权值小于等于其所有祖先的权值。

因此一个子树对子树外而言只有两种状态，子树内存在至少一台服务器使得子树内所有需要联网的房屋全部满足要求，或者子树内一台服务器都不存在。

因此设计状态 $f_{u,i}$ 表示子树 $u$ 内有 $i$ 台服务器时子树 $u$ 内需要联网的房屋的最小花费之和，再令 $sz_u$ 表示 $u$ 子树内需要联网的房屋数量，有 $f_{u,i} = \min(\min(f_{ls,i} + sz_{rs} \times w_u,f_{rs,i} + sz_{ls} \times w_u),\min_{1 \leq j < i}(f_{ls,j} + f_{rs,i-j}))$。

这个形式有点丑，但是不妨令 $f_{u,0} = sz_u \times w_{fa}$，那么你发现 $f_{u,i}$ 就是由 $f_{ls,i}$ 与 $f_{rs,i}$ 先做闵可夫斯基和再将 $f_{u,0}$ 增加一个非负数得到。

dp 的边界条件是 $f_{u,0} = sz_u \times w_{fa},f_{u,1} = 0$，此时 $f_{u,i}$ 是凸的，因此在经过上述合并操作后依然是凸的，所以直接用可并堆维护差分数组即可做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int ls[maxn<<1],rs[maxn<<1];
int w[maxn<<1];
int fa[maxn<<1];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int n,m,p,tot;
pair<int,pair<int,int> > e[maxn];
const int inf = 1e9+114;
int root[maxn<<1];
int g[maxn<<1];
struct node{
    int v,ls,rs,dist;
    node(){
        v=ls=rs=dist=0;
    }
}tr[maxn];//大根堆
int cnt;
void pushup(int cur){
    if(tr[tr[cur].ls].dist<tr[tr[cur].rs].dist) swap(tr[cur].ls,tr[cur].rs);
    tr[cur].dist=tr[tr[cur].rs].dist+1;
}
int merge(int a,int b){
    if(a==0||b==0) return a+b;
    if(tr[a].v>tr[b].v){
        tr[a].rs=merge(tr[a].rs,b);
        pushup(a);
        return a;
    }
    tr[b].rs=merge(tr[b].rs,a);
    pushup(b);
    return b;
}
int sz[maxn<<1];
void dp(int u,int fa){
    if(u<=n){
        g[u]=sz[u]*w[fa];
        cnt++;
        tr[cnt].v=g[u];
        root[u]=cnt;
        return ;
    }
    dp(ls[u],u),dp(rs[u],u);
    root[u]=merge(root[ls[u]],root[rs[u]]);
    g[u]=g[ls[u]]+g[rs[u]];
    sz[u]=sz[ls[u]]+sz[rs[u]];
    tr[root[u]].v+=sz[u]*w[fa]-g[u];
    g[u]=sz[u]*w[fa];
    return ;
}
void work(){
    cin>>n>>m>>p;
    tot=n;
    for(int i=1;i<=p;i++){
        int x;
        cin>>x;
        sz[x]=1;
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) cin>>e[i].second.first>>e[i].second.second>>e[i].first;
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++){
        int u=found(e[i].second.first),v=found(e[i].second.second);
        if(u!=v){
            tot++;
            ls[tot]=u,rs[tot]=v;
            fa[tot]=fa[u]=fa[v]=tot;
            w[tot]=e[i].first;
        }
    }
    w[0]=inf;
    dp(tot,0);
    for(int i=1;i<=n;i++){
        g[tot]-=tr[root[tot]].v;
        root[tot]=merge(tr[root[tot]].ls,tr[root[tot]].rs);
        cout<<g[tot]<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=cnt;i++) tr[i]=node();
    for(int i=1;i<=tot;i++) sz[i]=g[i]=root[i]=ls[i]=rs[i]=w[i]=fa[i]=0;
    cnt=tot=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

