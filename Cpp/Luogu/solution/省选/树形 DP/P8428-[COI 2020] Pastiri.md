# [COI 2020] Pastiri

## 题目描述

给定一棵 $N$ 点的树，点编号为 $1$ 到 $N$，现在在 $K$ 个点上有羊，你的任务是在树上分配一些牧羊人。

这些牧羊人很懒，只会看管离他最近的羊。当然如果有多个离他最近的羊，那么他会都看管。

当然，牧羊人可以和羊在同一个点上，但这样牧羊人只会看管这一个点上的那个羊。

求一种牧羊人的分配方案使得牧羊人总数最小。

## 说明/提示

#### 样例 3 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qwahnh8z.png)

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（8 pts）：$1 \le N \le 5 \times 10^5$，任意一个点 $i$ 都与 $i+1$ 相连（$1 \le i \le N-1$）。
- Subtask 2（18 pts）：$1 \le K \le 15$，$1 \le N \le 5 \times 10^5$。
- Subtask 3（23 pts）：$1 \le N \le 2000$。
- Subtask 4（51 pts）：$1 \le N \le 5 \times 10^5$。

对于 $100\%$ 的数据，$1 \le K \le N$，$1 \le a_i,b_i \le N$，$1 \le  o_i \le N$。

**本题使用 Special Judge，checker 提供者 @[Lynkcat](https://www.luogu.com.cn/user/120911)，感谢他的贡献。**

#### 说明

翻译自 [Croatian Olympiad in Informatics 2020 B Pastiri](https://hsin.hr/coci/archive/2019_2020/olympiad_tasks.pdf)。

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4
1 4```

### 输出

```
2
1 3```

## 样例 #2

### 输入

```
9 5
1 2
2 3
3 4
3 5
1 6
1 7
7 8
8 9
2 5 6 7 9```

### 输出

```
3
1 4 9```

## 样例 #3

### 输入

```
20 9
1 2
2 3
2 4
4 5
4 6
5 7
7 8
8 9
7 10
10 11
6 12
6 13
6 17
13 14
14 15
14 16
17 18
18 19
18 20
1 3 9 11 12 15 16 19 20```

### 输出

```
3
5 14 18```

# 题解

## 作者：cc0000 (赞：9)

树上贪心神题

首先是和 [这题](https://www.luogu.com.cn/problem/P3523) 有一个相同的贪心策略，就是对于一个深度最深的点，选择他的最高祖宗一定比选择他的某个兄弟子树优。（因为它是深度最深的点，那么没有比它深的点，所以在其它子树一定不优，最高的祖宗是因为能看守到更多的羊）

然后我们可以预处理每一个点到最近的羊的距离，然后对羊从小到大排序，对每只羊暴力跳到最浅的祖宗，然后对于每个祖宗能覆盖到的羊标记一下。

这样做复杂度是对的是因为在标记时可以用 dis 判断子树内有没有能看管到的羊，在此之后走过的点就不会重复走了。这样均摊复杂度是 $O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=500020;
const int maxm=1200000;
int to[maxm],nxt[maxm],head[maxn],num;
void add(int x,int y){num++;to[num]=y;nxt[num]=head[x];head[x]=num;}
int n,K;
int dep[maxn],fa[maxn];
void dfs_pre(int p,int F)
{
	dep[p]=dep[F]+1;fa[p]=F;
	for(int i=head[p];i;i=nxt[i])
	{
		if(to[i]==fa[p]) continue;
		dfs_pre(to[i],p);
	}
}
int dis[maxn],vis[maxn];
queue<int> Q;
int O[maxn];
void spfa()
{
	while(!Q.empty())
	{
		int p=Q.front();Q.pop();
		for(int i=head[p];i;i=nxt[i])
		{
			if(dis[to[i]]>dis[p]+1) 
			{
				dis[to[i]]=dis[p]+1;
				if(!vis[to[i]]) vis[to[i]]=1,Q.push(to[i]);
			}
		}
	}
}
int d[maxn];
void dfs(int p,int s)
{
	d[p]=1;
	for(int i=head[p];i;i=nxt[i])
	{
		int v=to[i];
		if(dis[v]!=s-1||d[v]) continue;
		dfs(v,s-1);
	}
}
bool cmp(int x,int y){return dep[x]>dep[y];}
int ans;
vector<int> Ans;
int main()
{
//	freopen("p.in","r",stdin);
//	freopen("p.out","w",stdout);
	scanf("%d%d",&n,&K);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs_pre(1,0);
	memset(dis,0x7f,sizeof(dis));
	for(int i=1;i<=K;i++)
	{
		scanf("%d",&O[i]);
		dis[O[i]]=0; vis[O[i]]=1;
		Q.push(O[i]);
	}
	spfa();
	sort(O+1,O+1+K,cmp);
	for(int i=1;i<=K;i++)
	{
		if(d[O[i]]) continue;
		int f=O[i],v=0;
		while(fa[f]&&dis[fa[f]]==dis[f]+1) f=fa[f];
		dfs(f,dep[O[i]]-dep[f]);
		ans++;
		Ans.push_back(f);
	}
	printf("%d\n",ans);
	for(auto x:Ans)
	{
		printf("%d ",x);
	}
    return (0-0);
}
```

---

## 作者：wYYSZLwSSY (赞：8)

## 题意
给定 $n$ 个点的树，树上有 $k$ 个关键点，你可以选取若干个点（可以是关键点），每个点可以覆盖离自己最近的关键点（如有多个则都可以覆盖）。最小化选取的点数，使得每个关键点都可以覆盖到，输出方案。

$1\le k \le n \le 5 \times 10^5$。

## 题解

### 基本思路

好题，比较巧妙。

首先它是树上覆盖问题，有一个[经典的贪心策略](https://www.luogu.com.cn/problem/P3942)。每次选取没有覆盖深度最深的点，选取可以覆盖它的最远祖先。

简单想一下这为什么是对的。

对于还没有任何点被覆盖的时候，你一定要覆盖最深的点，所以思考怎样覆盖最深的点使得利益最大。

一种策略是找祖先，另外一种是找祖先的兄弟子树中的一个点选取（找子树肯定不优，这个就不谈了）。显然，前一种策略是不劣于后一种的（而且这种优秀是“包含”的）。设想，你选取一个点，可能覆盖的是最深的点，最深的点的祖先，最深的祖先的子树中的点。假设另一种更优，一定是它还可以覆盖兄弟子树中的某个点（而前一种不能），或者可以兼顾兄弟的兄弟和祖先（而前一种不能），这与你要覆盖的点是最深的点是矛盾的。

稍微画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d7x80plv.png)

找祖先找最浅的也可以尽可能地覆盖更多的点，这不言而喻。

而对于有一些点被覆盖的情况，可以认为已被覆盖的点不存在，也可以用上面的贪心策略。这样，贪心策略就是正确的。

### $n \le 2000$ 的做法

根据上面的贪心策略，先计算出每个点到最近关键点的距离，称为 $dis_x$，这是多起点最短路，随便用说明方法都可以。然后将关键点根据深度从大到小排序，依次考虑。如果该点被覆盖过了，则跳过，否则选取最浅的可以覆盖它的祖先，并标记可以同时覆盖到的点。

时间复杂度 $O(nk)$，跳祖先是均摊的，瓶颈在于标记点。

### 正解

思考怎么优化这个过程。假设选取的祖先是 $x$，我们要标记的点是距离 $x$ 不超过 $dis_x$ 的点。这些点一部分是 $x$ 的子树，另一部分不是。对于前一种，暴力标记，中看到一个被标记的点就返回。这样不会遗漏，因为可能遗漏的一定是深度更深的点，而这不满足枚举覆盖的点是最深的点这一原则。

那么第二种能否这样做？然而并不能，例如：

![](https://cdn.luogu.com.cn/upload/image_hosting/ws2zaedq.png)

假设 $dis_x$ 为 $3$，$dis_y$ 为 $2$。我们首先选取了 $x$，将若干点标记后选取 $y$。当标记 $y$ 的祖先时，因为 $y$ 的父亲已经被标记，就不会再向上标记，这样就漏掉了 $y$ 的祖父节点。

正确的做法是，走第二类节点时，需要关注是否有 $dis_{to} \le last-1$ （这里等价于 $dis_{to} = last-1$，原因显然），其中 $last$ 表示走到某个节点 $dis_x$ 还剩下的（说的有点抽象，可以看代码）。如果没有，则不去 $to$。也就是说，当离 $to$ 最近的关键点不是 $x$ 所能覆盖的时候，就不去标点。这样一来，就避免了上述情况。其他部分处理和第一类节点一样。

这样时间复杂度为 $O(n+k\log k)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int num;
int hd[500005];
int dis[500005];
int deep[500005];
int bl[500005];
int vis[500005];
int x,n,k,u,v;
bool bll[500005];
int fat[500005];
vector<int>ans,xl;
struct P{int nxt,to;}line[1000006];
void add(int x,int y){
	++num;
	line[num]={hd[x],y};
	hd[x]=num;
	return ;
}
using pi=pair<int,int>;
priority_queue<pi,vector<pi>,greater<pi> >dl;
void dij(){
	while(dl.size()){
		int tp=dl.top().second;
		dl.pop();
		if(vis[tp])continue;
		vis[tp]=1;
		for(int i=hd[tp];i;i=line[i].nxt){
			int to=line[i].to;
			if(dis[to]>dis[tp]+1){
				dis[to]=dis[tp]+1;
				dl.push({dis[to],to});
			}
		}
	}
	return ;
}
void dfs(int x,int fa){
	fat[x]=fa;
	deep[x]=deep[fa]+1;
	for(int i=hd[x];i;i=line[i].nxt){
		int to=line[i].to;
		if(to==fa)continue;
		dfs(to,x);
	}
	return ;
}
void dfs1(int x,int fa,int last){
	bl[x]=1;
	if(!last)return ;
	for(int i=hd[x];i;i=line[i].nxt){
		int to=line[i].to;
		if(bl[to] or dis[to]>last-1)continue;//这里是关键
		dfs1(to,x,last-1);
	}
	return;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>k;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=k;++i){
		cin>>x;
		dis[x]=0;
		dl.push({0,x});
		xl.push_back(x);
	}
	dij();//这里用了 dij 不过没有必要
	dfs(1,0);
	auto cmp=[&](int x,int y)->bool{return deep[x]>deep[y];};
	sort(xl.begin(),xl.end(),cmp);
	for(auto x:xl){
		if(bl[x] or bll[x])continue;
		int tp=x;
		while(fat[tp] and dis[fat[tp]]==deep[x]-deep[fat[tp]])tp=fat[tp];
		dfs1(tp,fat[tp],dis[tp]);
		ans.push_back(tp);
	}
	cout<<ans.size()<<'\n';
	for(auto x:ans)cout<<x<<' ';
	return 0;
}
```

---

## 作者：MerlinLee (赞：4)

这题要用到一种贪心策略，每次找到剩余羊中深度最大的，然后在满足牧羊人能看守到它的情况下使牧羊人深度尽量小，再把当前牧羊人能看守到的羊都标记上，表示无需再为它们放置新的牧羊人。

感性考虑一下为什么是对的？

当前找到深度最大的羊，因为没有比它深度更大的了，所以牧羊人放在它子树内的话答案不会更优。同理，它到根的链上伸出的子树中也不存在比它深度大的点，那么放在这些子树内也不会更优。既然不会受到其它限制的话，为了能看守到更多的羊，则使牧羊人尽可能往上放。（默认结论正确后）那么可以先跑一遍最短路求出每个点到任意一只羊的最短距离， 再按深度从大到小枚举每只羊，不断跳父亲直到不合上述条件为止。找到牧羊人后，从他开始 DFS 一遍，把可行的羊标记上即可。
复杂度呢？暴力往上跳父亲的过程，每条边至多被跳一次；从牧羊人开始 DFS 的过程，最坏情况还是到 $O(n^2)$ 这种情况。
 
如何优化？其实有很多没必要 DFS 的地方，每次递归下去当且仅当该儿子子树内存在到牧羊人距离小于等于该次看守距离（指当前枚举到的羊和牧羊人之间的距离）的点，直接判断儿子节点的最短路 $dis$ 即可。在此条件下，一个点只会到达一次，再记录一下即可。

注意不能只记录一个点是否被经过，必须在满足前一个条件的基础上。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500010;
int last[N],nxt[N*2],to[N*2],len=1;
int dis[N],dp[N],Fa[N],vi[N];
int a[N],p[N],ans[N];
queue<int> q;
int read() 
{
	int s=0;
	char x=getchar();
	while(x<'0' or x>'9') 
	  x=getchar();
	while(x>='0' and x<='9') 
	  s=s*10+x-48,x=getchar();
	return s;
}
void add(int x,int y) 
{
	to[++len]=y;
	nxt[len]=last[x];
	last[x]=len;
}
void dfs(int k,int fa) 
{
	dp[k]=dp[fa]+1,Fa[k]=fa;
	for(int i=last[k];i;i=nxt[i]) 
	  if(to[i]!=fa) 
	    dfs(to[i],k);
}
void SPFA() 
{
	while(!q.empty()) 
	{
		int x=q.front();
		q.pop();
		for(int i=last[x];i;i=nxt[i]) 
		{
			int y=to[i];
			if(dis[x]+1<dis[y]) 
			{
				dis[y]=dis[x] + 1;
				if(!vi[y]) 
				  q.push(y),vi[y]=1;
			}
		}
		vi[x]=0;
	}
}
int cmp(int x,int y) 
{
	return dp[x]>dp[y];
}
void solve(int k,int fa,int s) 
{
	p[k]=0,vi[k]=1;
	if(!s) 
	  return;
	for(int i=last[k];i;i=nxt[i]) 
	  if(dis[to[i]]==s-1 and !vi[to[i]]) 
	    solve(to[i],k,s-1); 
}
int main() 
{
	int n,m,x,y;
	n=read(),m=read();
	for(int i=1;i<n;i++) 
	{
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	memset(dis,127,sizeof(dis));
	for(int i=1;i<=m;i++) 
	{
		a[i]=read();
		dis[a[i]]=0,vi[a[i]]=1;
		q.push(a[i]);
		p[a[i]]=1;
	}
	SPFA();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=m;i++) 
	  if(p[a[i]]) 
	  {
		  int x=a[i],t=x;
		  while(Fa[t] and dis[Fa[t]]==dis[t]+1) 
		    t=Fa[t];
		  ans[++ans[0]]=t;
		  solve(t,0,dp[x]-dp[t]);
	  }
	printf("%d\n",ans[0]);
	for(int i=1;i<=ans[0];i++) 
	  printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：是青白呀 (赞：2)

~~树的定向。~~

首先可以想到的一个贪心做法是，每次找到未被看管的、深度最大的某个羊，然后找到其深度最小的、放置后可以看管到这只羊的点，在这个点上放置一个牧羊人，并且更新可以被看管的羊。其正确性在于深度越小，可能可以看管到的羊就越多。基于此可以获得一个 $O(n^2)$ 的做法。

考虑对每个点求出 $dis_i$ 表示 $i$ 最近的羊的距离，不妨使用多源 BFS 求解。此时，对于边 $(u,v)$，若 $dis_v=dis_u+1$，则我们给边定向 $u\to v$，此时羊所在节点的入度为 $0$，以其为根 DFS 到的所有点都是放置牧羊人后可以看管到它的点。

于是对每个点维护 $anc_i$ 表示自己能遍历到的点中深度最小的点，从每个羊节点开始记忆化搜索即可求出。找到此次放置牧羊人的点后，以该节点为根在反图上进行 DFS，将所有 DFS 到的羊节点标记为已被看管。此过程中每个点最多只需要被遍历到 $1$ 次，其能走到的所有羊节点都会被标记过，因此开一个 $vis$ 表示该点是否走到过即可。

不难发现上述的记忆化搜索和反图上 DFS 的复杂度都是均摊线性的，每个点至多只会被遍历 1 次。于是我们就可以快速实现上述的贪心做法了。时间复杂度  $O(n+k\log k)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=5e5+5,M=1e6+5,S=(1<<15)+5,inf=(ll)1e18+7,mo=998244353;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,k;
struct node{
    int id,dep;
    friend bool operator<(node x,node y){
        if(x.dep!=y.dep)return x.dep>y.dep;
        return x.id<y.id;
    }
};
set<node>st;
vector<int>eg[N],e[N],eb[N],rt[N];
int dis[N],anc[N],dep[N];
void dfs1(int x,int f){
    dep[x]=dep[f]+1;
    for(auto j:eg[x])
        if(j!=f)dfs1(j,x);
}
void dfs2(int x){
    if(anc[x])return;
    anc[x]=x;
    for(auto j:e[x]){
        dfs2(j);
        if(dep[anc[x]]>dep[anc[j]])anc[x]=anc[j];
    }
}
bool vis[N];
void dfs3(int x){
    if(vis[x])return;
    vis[x]=1;
    if(!dis[x])st.erase((node){x,dep[x]});
    for(auto j:eb[x])
        dfs3(j);
}
vector<int>ans;
signed main(){
    read(n),read(k);
    rep(i,1,n-1){
        int x,y;
        read(x),read(y);
        eg[x].push_back(y),eg[y].push_back(x);
    }
    rep(i,1,n)
        dis[i]=inf;
    queue<int>q;
    rep(i,1,k){
        int x;
        read(x);
        dis[x]=0,q.push(x);
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(auto j:eg[x])
            if(dis[j]>dis[x]+1)dis[j]=dis[x]+1,q.push(j);
    }
    dfs1(1,0);
    rep(i,1,n){
        for(auto j:eg[i])
            if(dis[j]==dis[i]+1)e[i].push_back(j),eb[j].push_back(i);
    }
    rep(i,1,n)
        if(!dis[i])st.insert((node){i,dep[i]}),dfs2(i);
    while(!st.empty()){
        node x=*st.begin();
        int stp=anc[x.id];
        dfs3(stp);
        ans.push_back(stp);
    }
    printf("%lld\n",ans.size());
    for(auto j:ans)
        printf("%lld ",j);
    return 0;
}
```

---

## 作者：wrkwrkwrk (赞：0)

先考虑如何表示每个点能够处理的点。考虑以每只羊为起点的最短路到每个点的最短距离，处理后此时考虑 "深度"，即距离大的一定能够 "控制" 相邻距离小的点，如此反复到底部就是控制的羊。这一复杂度直接 bfs 就是 $O(n)$。

此时，考虑先求出答案。$dp_{i,???}$ 表示第 $i$ 个点的信息。我们还没有确定问号的内容，但应当是个 $O(1)$ 信息。

考虑转移。只考虑儿子的信息。儿子分为以下三类：
- dep 比他小的。
- dep 等于他的。
- dep 大于他的。

如图表示，箭头表示控制关系。

![](https://cdn.luogu.com.cn/upload/image_hosting/rt1rj3dq.png)

考虑二三类儿子节点。此时无论这个目前变化及其祖先变化如何，都不会改变状态，故应当在转移前局部满足。

再考虑一类儿子节点，此时这个儿子节点控制的地方应当至少局部合法，即可能通过祖父或其他转移达到满足。

这里还不够，再次考虑三类儿子节点，若从该儿子节点能够有牧羊人满足跳出子树控制这个节点，那么可能目前节点无需放牧羊人。

故定义 $dp_{i,0/1/2}$ 表示节点 $i$ 局部合法/局部满足/可跳出子树的答案。

特别的，如果这个节点不是要被控制的，那么让其局部满足可以是各个子树局部满足。

转移方程为

$$
dp_{i,0}\gets\sum _{v \in \text{childs},\text{dep}_v<\text{dep}_i}dp_{i,0}+\sum _{v \in \text{childs},\text{dep}_v\geq\text{dep}_i}dp_{i,1}\\
dp_{i,1},dp_{i,2}\gets\sum _{v \in \text{childs},\text{dep}_v<\text{dep}_i}dp_{i,0}+\sum _{v \in \text{childs},\text{dep}_v\geq\text{dep}_i}dp_{i,1}+\min(1,\min_{v \in \text{childs},\text{dep}_v>\text{dep}_i}(dp_{i,2}-dp_{i,1}))。

$$
当 $dep_i\neq 0$ 的时候，$dp_{i,1}$ 还可取 $\sum_{v \in \text{childs}}dp_{i,1}$。

考虑如何输出方案，只需要按照以上步骤再次 dfs，根据应当取得 $dp_{i,0/1/2}$ 进行操作，放入答案继续递归即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
vector<int>g[1000006];
bool u[1000006];
int dep[1000006];
bool vis[1000006];
int dp[1000006][3];
int cnt[1000006];
int q[1000006],w[1000006],e[1000006],t[1000006];
void dfs(int now,int fa){
	for(auto x:g[now])if(x!=fa){
		dfs(x,now);
	}
	t[now]=1;
	for(auto x:g[now])if(x!=fa){
		if(dep[x]<dep[now]){
			q[now]+=dp[x][0];
			w[now]+=dp[x][1];
		} else{
			e[now]+=dp[x][1];
		}
		if(dep[x]>dep[now]){
			t[now]=min(t[now],dp[x][2]-dp[x][1]);
		} 
	} 
	dp[now][0]=e[now]+q[now];
	dp[now][1]=e[now]+q[now]+t[now];
	if(dep[now])dp[now][1]=min(dp[now][1],e[now]+w[now]);
	dp[now][2]=e[now]+q[now]+t[now];
}
vector<int>ans;
void findsol(int now,int fa=0,int type=1){
	if(type==0){
		for(auto x:g[now])if(x!=fa){
			if(dep[x]<dep[now]){
				findsol(x,now,0);
			}else{
				findsol(x,now,1);
			}
		}
		
	}else if(type==1){
		if(dep[now]&&dp[now][1]==e[now]+w[now]){
			for(auto x:g[now])if(x!=fa){
				findsol(x,now,1);
			}
		}else{
			int p=now;
			for(auto x:g[now])if(x!=fa&&dep[x]>dep[now]&&dp[x][2]-dp[x][1]==t[now]){
				p=x;
				break;
			}
			if(p==now)ans.push_back(now);
			else findsol(p,now,2);
			for(auto x:g[now])if(x!=fa&&x!=p){
				if(dep[x]<dep[now]){
					findsol(x,now,0);
				}else{
					findsol(x,now,1);
				}
			}
			
		}
	}else if(type==2){
		int p=now;
		for(auto x:g[now])if(x!=fa&&dep[x]>dep[now]&&dp[x][2]-dp[x][1]==t[now]){
			p=x;
			break;
		}
		if(p==now)ans.push_back(now);
		else findsol(p,now,2);
		for(auto x:g[now])if(x!=fa&&x!=p){
			if(dep[x]<dep[now]){
				findsol(x,now,0);
			}else{
				findsol(x,now,1);
			}
		}
		
	}else{
		cout<<type<<endl;
		assert(0);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a); 
	} 
	queue<int>c;
	for(int i=1;i<=k;i++){
		int x;
		cin>>x;
		u[x]=1;
		c.push(x);
		vis[x]=1;
	}
	while(c.size()){
		auto u=c.front();c.pop();
		for(auto v:g[u]){
			if(!vis[v]){
				vis[v]=1;
				dep[v]=dep[u]+1;
				c.push(v); 
			}
		}
	}
	dfs(1,0);
	cout<<dp[1][1]<<'\n';
	findsol(1,0);
	for(auto x:ans)cout<<x<<' ';
	
	
	return 0;
}
}
signed main(){
	   return _wrk::main();
}
```
[AC](https://www.luogu.com.cn/record/178456780) 记录。

---

