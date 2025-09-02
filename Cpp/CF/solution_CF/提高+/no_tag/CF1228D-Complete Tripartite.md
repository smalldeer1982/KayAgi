# Complete Tripartite

## 题目描述

给定一个包含 $n$ 个顶点和 $m$ 条边的简单无向图。该图不包含自环，任意一对顶点之间至多有一条边。该图可以是不连通的。

我们定义如下：

设 $v_1$ 和 $v_2$ 是两个不相交的非空顶点集合。若且仅若满足以下所有条件，称 $f(v_1, v_2)$ 成立：

1. 在顶点集合 $v_1$ 内没有两端都在 $v_1$ 的边。
2. 在顶点集合 $v_2$ 内没有两端都在 $v_2$ 的边。
3. 对于任意 $x \in v_1$ 和 $y \in v_2$，$x$ 和 $y$ 之间有一条边。

请将所有顶点划分为三个集合（$v_1$，$v_2$，$v_3$），使得满足以下条件：

1. 每个集合都非空。
2. 每个顶点恰好属于一个集合。
3. $f(v_1, v_2)$、$f(v_2, v_3)$、$f(v_3, v_1)$ 都成立。

是否存在这样的划分？如果存在，请输出每个顶点所属的集合编号。

## 说明/提示

在第一个样例中，如果 $v_1 = \{1\}$，$v_2 = \{2, 3\}$，$v_3 = \{4, 5, 6\}$，则所有条件都满足。但你也可以用不同的方式划分顶点集合；例如 “2 3 3 1 1 1” 也是合法答案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1228D/c2c365eaf8464b0509392f3446fceb5e5d58fe78.png)

在第二个样例中，不可能划分出满足条件的顶点集合。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 11
1 2
1 3
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
```

### 输出

```
1 2 2 3 3 3 ```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
-1
```

# 题解

## 作者：HenryHuang (赞：7)

**「CF1228D Complete Tripartite」题解**

我觉得我的做法简直就是一股清流~

题意就不说了，大概就是将整个点分为三个点集，使得任意两个直接相连的点不在同一个点集，且任意两个点集中的点，点集间的点相互连通

求是否存在这样的方案

其实很简单，如果两个点能够被分到同一个点集，那么它们能够到达的点的集合一定是一模一样的

我们将可到达点集集合相同的点分为同一组

因为这些点之间一定没有直接连接（否则集合应该包含对方）,自然满足题目要求

那么这个我们应该如何判断呢？

其实利用一个 $ \texttt{basic string}$ 就可以了

加边就像 $\texttt{vector}$ 那样加，然后将每个点的点集排一个序，再把整体排一个序，最后看有多少种不同的点集集合就好了

代码超短，超好理解！

而且还可以轻松扩展至 $k$ 分图！

Upd：在大多数**不连通图**中，该算法都是正确的。但是在存在孤立点的图中，该算法会有一定问题，所以只需要特判一下就好了！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int fa[maxn];
struct cc{
    int id;
    basic_string<int> d;
    friend bool operator<(cc x,cc y){
        return x.d<y.d;
    }
}s[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0); 
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        s[i].id=i;
    }
    for(int i=1;i<=m;++i){
        int x,y;
        cin>>x>>y;
        s[x].d+=y;
        s[y].d+=x;//加边
    }
    for(int i=1;i<=n;++i){
        sort(s[i].d.begin(),s[i].d.end());//内部排序
    }
    sort(s+1,s+n+1);//总体排序
    if(!s[1].d.length()) cout<<-1<<endl,exit(0);//特判 
    int cnt=1;
    fa[s[1].id]=1;
    for(int i=2;i<=n;++i){
        if(s[i].d==s[i-1].d) fa[s[i].id]=fa[s[i-1].id];
        else fa[s[i].id]=++cnt;
    }//判断有多少个不同的集合
    if(cnt!=3) cout<<-1<<endl;//不是三个就不存在
    else{
        for(int i=1;i<=n;++i){
            cout<<fa[i]<<' ';
        }
    }
} 
```

---

## 作者：End1essSummer (赞：4)

提供一种时间复杂度 $O(m)$ 的做法。

首先观察题面，它本质上是让我们看看这个图是不是个完全三分图。

然后我们发现：一个点必定和不在它集合里的点有边，必定和在这个集合里的点没有边。

我们直接找到某个节点，所有不和它相连的点一定和它在同一个集合里。然后随便找到和它相连的另外一个端点，所有不和它相连的点一定也和它在另外一个集合中，剩下的点肯定隶属于最后一个集合。

最后，再枚举每一条边，判断两端点隶属集合是否不同。

其中无解的情况无非就是在找第一个集合和第二个集合的时候发现有节点出现冲突，还有这些集合之间应该连的边不等于 $m$，以及枚举边时两端点集合相同。中间判断一下就好。

---

## 作者：MoyunAllgorithm (赞：3)

这道题很有趣，有很多种做法，给出一个不需要 bfs 染色等算法的方法。

### 题意

给出 $N$ 个点 $M$ 条边的图。将点分为 $3$ 个互不相交的集合，使得任意两个集合满足：

- 一个集合的所有点都和另一集合的所有点连边；

- 集合内部没有边。

$N \le 10^5$。

### 分析

这种对边有严格限制的题，可以试试建立**反图**，这时可能会出现某些性质。

什么是反图？就是原图中如果两点有边那反图中无边，反之亦然。

在反图中，这 $3$ 个集合要满足：

- 集合内部是完全图；

- 集合之间不连边。

也就是说，一个图能被分为 $3$ 个集合，当且仅当它的反图是 $3$ 个完全图连通块组成的。

需要注意的是，**不能直接建反图**，否则会超内存。我们用 `vector` 作为原图的邻接表，并额外用 `map<pair<int,int>,bool` 作为原图的邻接矩阵。他们都会起作用。

维护三个 `vector`，作为三个集合。（下面不做说明都代表原图的信息而不是反图的）

- 首先，将 $1$ 加入集合 $1$。

- 之后，对与点 $i$，它必须 **与恰好一个集合无边**。之后它加入该集合。

为什么要与恰好一个集合无边？如果它和 $2$ 个集合无边，那在反图中，它就连通了两个本不连通的完全图，让这两个完全图变成一个连通块。但是，这新的连通块不是完全图，无解。

这么做是正确的，我们可以成功将图分为 $3$ 个集合。但是如何判断与一个集合是否有边？不能暴力扫每一个集合内的点判断。我们结合并查集的思想：

- 假如一个点加入了集合，则该集合的**第一个点**向所有新点所连边的点连边。

这样我们可以快速知道点和集合是否有边。

最后如何判断是否是完全图？由于**没有重边和自环**，所有一张图是完全图当且仅当每个点的度数是图的点数 $-1$。当然这里的度数是反图的度数。

我们在 $O(M \log M)$ 的时间内解决该问题，其中 $ \log$ 是 `map` 的复杂度。

### 代码与注释


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=1e5+5;
map<pair<int,int>,int>mp;
int N,M;
int deg[MAXN];
vector<int>q1,q2,q3;
int ans[MAXN];
vector<int>gra[MAXN];
void Merge(int x,int u)
{
	for(int i=0;i<gra[u].size();i++)
	{
		mp[{x,gra[u][i]}]=mp[{gra[u][i],x}]=1;
	}
   //集合的第一个点向新点所连边的点连边。可以证明，新产生的边的数量不超过 3M 条。
	return;
}
int main()
{
//	freopen("dis.in","r",stdin);
	//freopen("dis.out","w",stdout);
	scanf("%d %d",&N,&M);
	//printf("%d %d\n",N,M);
	for(int i=1;i<=M;i++)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		mp[{u,v}]=1;
		mp[{v,u}]=1;
		gra[u].push_back(v);
		gra[v].push_back(u);
		deg[u]++;deg[v]++;
	//	puts("...");
	}
	for(int i=1;i<=N;i++) deg[i]=N-1-deg[i];//反图中度数
	bool flag=1;
	q1.push_back(1);
	for(int i=2;i<=N;i++)
	{
		if(!q2.size()&&!q3.size())
		{
			if(mp[{q1[0],i}]) q2.push_back(i);
			else 
			{
				q1.push_back(i);
				Merge(q1[0],i);
			}
		}
		else if(!q3.size())
		{
			if(mp[{q1[0],i}]&&mp[{q2[0],i}]) q3.push_back(i);
			else if(mp[{q2[0],i}])
			{
				q1.push_back(i);
				Merge(q1[0],i);
			}
			else if(mp[{q1[0],i}])
			{
				q2.push_back(i);
				Merge(q2[0],i);
			}
			else flag=0;
		}
		else
		{
			if(mp[{q1[0],i}]&&mp[{q2[0],i}]&&mp[{q3[0],i}]) flag=0;
			else if(mp[{q2[0],i}]&&mp[{q3[0],i}])
			{
				q1.push_back(i);
				Merge(q1[0],i);
			}
			else if(mp[{q2[0],i}]&&mp[{q1[0],i}])
			{
				q3.push_back(i);
				Merge(q3[0],i);
			}
			else if(mp[{q1[0],i}]&&mp[{q3[0],i}])
			{
				q2.push_back(i);
				Merge(q2[0],i);
			}
			else flag=0;
		}
	}
	if(flag==0||!q3.size())
	{
		puts("-1");
		return 0;
	}
	int Q1=q1.size(),Q2=q2.size(),Q3=q3.size();
//	printf("%d\n",flag);
	for(int i=0;i<q1.size();i++)
	{
		int f=q1[i];
		ans[f]=1;
	//	printf("%d %d %d\n",f,deg[f],Q1);
		if(deg[f]!=Q1-1) flag=0; 
	}
//	printf("%d\n",flag);
	for(int i=0;i<q2.size();i++)
	{
		int f=q2[i];
		ans[f]=2;
		if(deg[f]!=Q2-1) flag=0; 
	}
//	printf("%d\n",flag);
	for(int i=0;i<q3.size();i++)
	{
		int f=q3[i];
		ans[f]=3;
		if(deg[f]!=Q3-1) flag=0; 
	}
//	for(int i=1;i<=N;i++) printf("%d ",deg[i]);
//	for(int i=1;i<=N;i++) printf("%d ",ans[i]);
//	puts("");
	if(!flag) 
	{
		puts("-1");
		return 0;
	}
	for(int i=1;i<=N;i++) printf("%d ",ans[i]);
	puts("");
	return 0;
}

```


---

## 作者：BLX32M_10 (赞：2)

### 题意

给定点和边，求能否将所有点划为三个点集，满足：

- 任意点集中任意两点之间没有边连接

- 任意一个点集中的每一个点与另外两个点集中的点均有连边

### 题解

这里介绍一种简单的哈希做法。（因为蒟蒻在练哈希，看到了这题第一时间就想到了哈希）

我们不难发现在同一点集中所有点的连边情况相同，

于是我们使用**哈希连边情况**的方式来快速判断连边情况，注意要使用有序的连边点集。

判断是否有三种不同的哈希值即可。

这种做法可能第一眼看起来不太对，第一眼口胡一个样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/69jql9a8.png)

但是这个可以被判断出来，有四个哈希值，因为 $4$ 的连接点集不同。

如果把连接 $1$ 和 $4$ 的边去掉呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/bpkaz7i8.png)

这也会判断出来，因为 $1$ 会与 $4$ 和 $5$ 划在同一个点集，只有两个点集。

如果你这时候信心满满地直接写，你会发现一个惊人的事实：`WA on test 48`。

原因不是它卡哈希，而是这题很阴，它不保证连通。

再使用并查集判连通即可。

时间复杂度 $\mathcal O\left(m \log n\right)$。（因为本蒟蒻写的是用 `set` 存邻接表，其实也可以输入完之后排序达到 $\mathcal O\left(n \log n\right)$ 复杂度）

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int base = 131, mod = 998244853, mod1 = 1011451423;
int n, m, u, v, fa[100005], sz[100005], has[100005];
set <int> ed[100005], as;
int hs(int x) //哈希
{
    int bs = base;
    for (int i : ed[x])
        has[x] = (has[x] + i * bs) % mod, bs = bs * base % mod1;
    return has[x];
}
int fd(int x) //并查集查找
{
    return fa[x] == x ? x : (fa[x] = fd(fa[x]));
}
void mg(int x, int y) //并查集合并
{
    if (sz[fd(x)] > sz[fd(y)])
    {
        sz[fd(x)] += sz[fd(y)];
        fa[fd(y)] = fd(x);
    }
    else
    {
        sz[fd(y)] += sz[fd(x)];
        fa[fd(x)] = fd(y);
    }
}
signed main()
{
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= n; i++)
        fa[i] = i, sz[i] = 1;
    while (m--)
    {
        scanf("%lld %lld", &u, &v);
        ed[u].insert(v);
        ed[v].insert(u);
        mg(u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        as.insert(hs(i));
        if (as.size() > 3)
            break;
    }
    if (as.size() != 3) //不能划分为三个点集
        puts("-1");
    else
    {
        int l = fd(1);
        bool b = 0;
        for (int i = 2; i <= n; i++) //判连通
        {
            if (fd(i) != l)
            {
                b = 1;
                break;
            }
        }
        if (b)
            puts("-1");
        else
        {
            unordered_map <int, int> ans;
            int cnt = 1;
            for (int i : as)
                ans[i] = cnt, cnt++;
            for (int i = 1; i <= n; i++)
                printf("%lld ", ans[has[i]]);
        }
    }
    return 0;
}
```

---

## 作者：Steven_Meng (赞：1)

## 广告
想要更佳的食用体验，请前往[蒟蒻のBlog](https://stevenmhy.tk/archives/9b983113.html)

## $Pro4$

[传送门](https://codeforces.com/contest/1228/problem/C)

称两个点集$v_1,v_2$是好的，当且仅当$v_1,v_2$之间没有连边，而且任意$x \in v_1,y \in v_2$，$x,y$都有边相连。

要你把$1 \dots n$的点分成$3$个集合$v_1,v_2,v_3$，满足$v_1 ∪ v_2 ∪ v_3 = \{1 \dots n\}$，而且$v_1,v_2$是好的，$v_2,v_3$是好的，$v_3,v_1$是好的。

如下图$\{1\},\{2,3\},\{4,5,6\}$就是一个合法的解。

![](https://cdn.jsdelivr.net/gh/GaisaiYuno/imghost/8f2b8fba1ab8461f6fac8f47e03c5c2483ebb678.png)

## $Sol4$

首先，这个图如果不联通，就无解。

仔细观察上图，发现每个点会和所有不是和它在一个集合的点连边，我们可以利用这个性质。

首先，令点$1$所在的集合编号为$1$，显然，将$1$连出的边遍历一遍，就可以找到不在$1$中的点，剩下的点在集合$1$。

```cpp
for (register int i=0;i<G[1].size();++i){
	vis[G[1][i]]=true;//标记2,3组
}
```

在从标记到的点集中随便抽出一个点$u$，钦定它在集合$2$中，那么它能够到达的点肯定是在集合$1,3$中，此时$1$集合中的点我们已经知道了，于是$3$集合我们也可以知道是那些。

```cpp
bool flag=true;
for (register int i=1;i<=n;++i){
	if (!vis[i]){
		ans[i]=1;//标记1集合
	}
	else if (vis[i]&&flag){
		for (register int j=0;j<G[i].size();++j){//这次到达的是1,3组
			int v=G[i][j];
			if (vis[v]) ans[v]=3;//到达的是3
		}
		flag=false;
	}
}
```

下面是麻烦的验证过程：

首先，计算出在集合$1$，$2$，$3$中的点数$cnt1,cnt2,cnt3$

注意到$cnt1 !=0,cnt2!=0,cnt3!=0$且$cnt1*cnt2+cnt2*cnt3+cnt1*cnt3=m$。

而且和每个点相邻的所有点都在另外两个集合中，可以根据这个性质进一步验证。

```cpp
int cnt1=0,cnt2=0,cnt3=0;
for (register int i=1;i<=n;++i){
	if (ans[i]==0) ans[i]=2;
	if (ans[i]==1) cnt1++;
	if (ans[i]==2) cnt2++;
	if (ans[i]==3) cnt3++;	
}
if (cnt1==0||cnt2==0||cnt3==0) return puts("-1"),0;
if (cnt1*cnt2+cnt2*cnt3+cnt3*cnt1!=m) return puts("-1"),0;

int c[4];
for (register int i=1;i<=n;++i){
	memset(c,0,sizeof(c));
	for (register int j=0;j<G[i].size();++j){
		c[ans[G[i][j]]]++;
	}
	if (c[ans[i]]!=0) return puts("-1"),0;//两个点在同一个集合
	if (ans[i]==1) if (c[2]!=cnt2||c[3]!=cnt3) return puts("-1"),0;//和不相等
	if (ans[i]==2) if (c[1]!=cnt1||c[3]!=cnt3) return puts("-1"),0;
	if (ans[i]==3) if (c[1]!=cnt1||c[2]!=cnt2) return puts("-1"),0;
}
```

## $Code4$
全部的code
```cpp
#include <bits/stdc++.h>
#define MAXN 300005
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
int deg[MAXN],vis[MAXN];
int vised[MAXN];
vector<int>G[MAXN];
inline void dfs(int u){
	vised[u]=true;
	for (register int i=0;i<G[u].size();++i){
		if (!vised[G[u][i]]) dfs(G[u][i]);
	}
}
int ans[MAXN];
int main(){
	int n=read(),m=read();
	for (register int i=1;i<=m;++i){
		int u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
		deg[u]++,deg[v]++;
	}
	dfs(1);
	for (register int i=1;i<=n;++i){
		if (!vised[i]) return puts("-1"),0;//判断联通
	}
	for (register int i=0;i<G[1].size();++i){
		vis[G[1][i]]=true;//标记2,3组
	}
	bool flag=true;
	for (register int i=1;i<=n;++i){
		if (!vis[i]){
			ans[i]=1;
		}
		else if (vis[i]&&flag){
			for (register int j=0;j<G[i].size();++j){//这次到达的是1,3组
				int v=G[i][j];
				if (vis[v]) ans[v]=3;
			}
			flag=false;
		}
	}
	int cnt1=0,cnt2=0,cnt3=0;
	for (register int i=1;i<=n;++i){
		if (ans[i]==0) ans[i]=2;
		if (ans[i]==1) cnt1++;
		if (ans[i]==2) cnt2++;
		if (ans[i]==3) cnt3++;
	}
	if (cnt1==0||cnt2==0||cnt3==0) return puts("-1"),0;
	if (cnt1*cnt2+cnt2*cnt3+cnt3*cnt1!=m) return puts("-1"),0;
	int c[4];
	for (register int i=1;i<=n;++i){
		memset(c,0,sizeof(c));
		for (register int j=0;j<G[i].size();++j){
			c[ans[G[i][j]]]++;
		}
		if (c[ans[i]]!=0) return puts("-1"),0;
		if (ans[i]==1) if (c[2]!=cnt2||c[3]!=cnt3) return puts("-1"),0;
		if (ans[i]==2) if (c[1]!=cnt1||c[3]!=cnt3) return puts("-1"),0;
		if (ans[i]==3) if (c[1]!=cnt1||c[2]!=cnt2) return puts("-1"),0;
	}
	for (register int i=1;i<=n;++i){
		printf("%d ",ans[i]);
	}
}
```



---

## 作者：k1saki (赞：1)

### 题意：用三种颜色染各个顶点，且相同颜色的点间不能有连线，不同颜色的点之间必须有连线  
#### 初看觉得是个bfs  
### 但经过指点后发现  
# ~~其实是个乱搞~~
# 正解
 

```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge
{
	int from,to;
}edg[300005];
int cnt12,cnt23,cnt31,n,m,pnt[600005],nxt[600005],head[100005],E,a[100005],cnt1,cnt2,cnt3;
bool vis1[100005],vis2[100005],vis3[100005];
void add_edge(int u,int v)
{
	pnt[E]=v;
	nxt[E]=head[u];
	head[u]=E++;
}
int main() {
	cin>>n>>m;
	memset(head,-1,sizeof(head));
	int u=0,v=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
		edg[i]=(edge){u,v};//先钦定两个有连线的点，一个染为1，另一个染为2,并记录一下连线
	}
	int w=0;
	for (int i=head[u];i!=-1;i=nxt[i])
	{
		int vv=pnt[i];
		vis1[vv]=1;
	}
	for (int i=head[v];i!=-1;i=nxt[i])
	{
		int vv=pnt[i];
		vis2[vv]=1;
		if (vis1[vv]&&vis2[vv])
		{
			w=vv;
		}//将所有与他们连接的点标记为不能染1/2/1和2
	}
   //那么两者都不能染的点就只能变为3
	if (w==0)
	{
		cout<<-1;
		return 0;
	}//如果没有就说明只有两种颜色，不合法
	for (int i=head[w];i!=-1;i=nxt[i])
	{
		int vv=pnt[i];
		vis3[vv]=1;
	}//与其连接的点标记为不能染为3
	for (int i=1;i<=n;i++)
	{
		if (vis1[i]+vis2[i]+vis3[i]!=2)
		{
			cout<<-1;
			return 0;
		}//如果不能染的颜色不是2种，就说明出问题了
		if (!vis1[i])
		{
			a[i]=1,++cnt1;
		}
		if (!vis2[i])
		{
			a[i]=2,++cnt2;
		}
		if (!vis3[i])
		{
			a[i]=3,++cnt3;
		}//记录各个点的颜色和各颜色点的个数
	}
	for (int i=1;i<=m;i++)
	{
		if (a[edg[i].from]==a[edg[i].to])
		{
			cout<<-1;
			return 0;
		}//连接的点染了同一种颜色，不合法
		if (a[edg[i].from]+a[edg[i].to]==3) cnt12++;
		if (a[edg[i].from]+a[edg[i].to]==4) cnt31++;
		if (a[edg[i].from]+a[edg[i].to]==5) cnt23++;//记录两种颜色连线的数量
	}
	if (cnt12!=cnt1*cnt2||cnt23!=cnt2*cnt3||cnt31!=cnt3*cnt1)
	{
		cout<<-1;
		return 0;
	}//如果连线数!=两种颜色点数之积则说明没有两两连线，不合法
	for (int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：Llf0703 (赞：1)

[更好的阅读体验](https://llf0703.com/p/cf-1228.html#dcompletetripartite)

可以发现不与 $x$ 直接相连的点一定和 $x$ 在同一集合。

那么就可以先把 $1$ 归到集合 ① ，然后遍历所有与 $1$ 相连的点，把他们标为集合 ② 。剩下的没有被标成 ② 的就一定在 ① 里。

再随便选一个 ② 中的节点，把与它相连且不在 ① 中的节点标成 ③ 。

至此集合就划分完了，接下来只需要验证是否满足题意。

1. 如果三种集合有一种的节点个数 $cnt[i]$ 为 $0$ ，那么无解。（~~我就是因为这个炸掉了~~）
2. 对于节点 $x$ ，遍历所有与它相连的节点 ，并记录三种集合的个数 $cur[i]$。如果 $x$ 所属的集合个数不为 $0$ ，或者其它集合的 $cnt[i]\neq cur[i]$ ，那么无解。

```cpp
#include<bits/stdc++.h>
#define ha 1000000007

using namespace std;

inline int read()
{
    char ch=getchar(); int f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

struct Edge {
    int next,to;
} edge[600005];
bool vis[100005];
int cnt,head[100005],n,m,a,b,col[100005],cnt2[4],cur[4];

inline void add(int u,int v)
{
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}

signed main()
{
    n=read(); m=read();
    for (int i=1;i<=m;i++)
    {
        a=read(); b=read();
        add(a,b);
        add(b,a);
    }
    col[1]=1; cnt2[1]=1;
    for (int i=head[1];i;i=edge[i].next) //从 1 开始，标记集合 ②
    {
        int y=edge[i].to;
        col[y]=2;
    }
    for (int i=1;i<=n;i++) if (!col[i]) col[i]=1,cnt2[1]++; //剩下的在 ①
    int st=2;
    for (;st<=n && col[st]!=2;st++); //找到一个 ② 中的节点
    for (int i=head[st];i;i=edge[i].next) //标记集合 ③
    {
        int y=edge[i].to;
        if (col[y]==1) continue;
        col[y]=3;
        cnt2[3]++;
    }
    cnt2[2]=n-cnt2[1]-cnt2[3];
    if (!cnt2[1] || !cnt2[2] || !cnt2[3]) return 0&puts("-1"); //无解情况 1
    for (int x=1;x<=n;x++)
    {
        memset(cur,0,sizeof(cur));
        for (int i=head[x];i;i=edge[i].next)
        {
            int y=edge[i].to;
            cur[col[y]]++;
        }
        for (int i=1;i<=3;i++)
        {
            if (col[x]==i && cur[i]) return 0&puts("-1");
            else if (col[x]!=i && cnt2[i]!=cur[i]) return 0&puts("-1"); //无解情况 2
        }
    }
    for (int i=1;i<=n;i++) printf("%d ",col[i]);
    return 0;
}
```

---

## 作者：Soulist (赞：1)

我的做法可能有点麻烦了，但它可以处理允许任意分集合(不止$3$个)的情况

考虑一个弱于原问题的问题

对于一个点$u$与其没有边的点必须在同一个集合内（同一集合内允许有边），你需要求出每个点所在的集合.

这个东西可以开链表维护没被使用的点然后$\rm bfs$在$O(n+m)$做掉

于是显然的是原问题一样是如果两个点之间没有边就必须要在一个集合内

可以发现最后的集合一定是固定的．

这和这个弱于原问题的问题有什么关系呢？

可以发现原问题的集合与弱于原问题的问题只多了一个判是否有解

所以我们额外搞个并查集维护联通性，那么有解当且仅当：

$1.$对于任意一条边其连接的两点不在同一集合

$2.$做完问题$1$后恰好分成了$3$个集合

复杂度$O(n+m)$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 1e5 + 5 ; 
const int M = 3e5 + 5 ; 
int n, m, cnt, head[N], vis[N], Fr[M], Ed[M], Can[N], L[N], R[N], flag, idnex ; 
struct E {
	int to, next ; 
} e[M * 2] ;  
void add( int x, int y ) {
	e[++ cnt] = (E){ y, head[x] }, head[x] = cnt ,
	e[++ cnt] = (E){ x, head[y] }, head[y] = cnt ; 
}
struct node {
	int u, v ; 
};
int fa[N] ;
int fd( int x ) {
	return ( fa[x] == x ) ? x : fa[x] = fd(fa[x]) ; 
}
void del( int x ) {
	R[L[x]] = R[x], L[R[x]] = L[x] ; 
}
queue<int> q ;
void merge( int x, int y ) {
	int u = fd(x), v = fd(y) ; 
	if( u == v ) return ; 
	fa[u] = v ; 
}
void solve( int x ) {
	++ idnex, q.push(x), del(x), vis[x] = idnex ;
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ; 
		Next( i, u ) {
			int v = e[i].to ; Can[v] = 1 ; 
		}
		for( re int i = 0; i != n + 1; i = R[i] ) {
			if( !i || Can[i] ) continue ; 
			del(i), q.push(i), merge( x, i ), vis[i] = idnex ;
		}
		Next( i, u ) {
			int v = e[i].to ; Can[v] = 0 ;
		}
	}
}
signed main()
{
	n = gi(), m = gi() ; 
	rep( i, 1, n ) fa[i] = i, L[i] = i - 1, R[i] = i + 1 ;
	rep( i, 1, m ) Fr[i] = gi(), Ed[i] = gi(), add( Fr[i], Ed[i] ) ; R[0] = 1 ;
	rep( i, 1, n ) {
		if( !vis[i] ) solve(i) ;
	}
	if( idnex != 3 ) puts("-1") ;
	else {
		rep( i, 1, m ) if( fd(Fr[i]) == fd(Ed[i]) ) flag = 1 ; 
		if( flag ) puts("-1") ; 
		else {
			rep( i, 1, n ) printf("%d ", vis[i] ) ;
		}
	}
	return 0 ;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1228D)

&nbsp;

### 题目大意：
给定一个有 $n$ 个点和 $m$ 条无向边的图，将所有点分配进三个点集，使得点集均非空，且每个点集中的点互相都没有连边，且点集两两之间每个点都有连边。

&nbsp;

### 解题思路：
注意到题目要求每个点和属于同一子集的点都没有连边，和不属于同一子集的点一定有连边，于是考虑对于每一个未分配子集的点，遍历所有以它为端点的边，将记录与之相连的点，将其它所有点都和它一同划入一个新的点集。

然后我们只需要判断有没有将点重复划入点集或者点集内是否有两点间有连边，以及是否有点集为空即可。

代码如下：
```
int main(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!dot[i]){
			if(cnt==3){
				printf("-1");
				return 0;
			}
			cnt++;
			
			int siz=q[i].size();
			for(int j=0;j<siz;j++){
				int x=q[i][j];
				a[x]=cnt;
			}
			for(int j=1;j<=n;j++){
			    if(a[j]!=cnt&&dot[j]){
			        printf("-1");
			        return 0;
			    }
				if(a[j]!=cnt) dot[j]=cnt,num[cnt]++;
			}
		}
		else{
			int siz=q[i].size();
			for(int j=0;j<siz;j++){
				int x=q[i][j];
				if(dot[x]==dot[i]){
					printf("-1");
					return 0;
				}
			}
			if(n-siz!=num[dot[i]]){
				printf("-1");
				return 0;
			}
		}
	}
	
	if(cnt<3){
		printf("-1");
		return 0;
	}
	return 0;
}
```
完结撒花 OvO！！！

---

## 作者：Benzenesir (赞：0)

有些题解够了，这题和三分图的判定没有什么关系……

这里主要是一个转化，一个点会和所以不与自己相连的点处于相同的集合中。

换句话说，如果两个点在同一个集合内，那与这两个点相连的点的集合是完全相同的。

这里使用了哈希来判定，另外，如果有孤立的点存在，则要特判。

```
// Problem: Complete Tripartite
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1228D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <bitset>
#include <stack>
#include <tuple>
#include <bitset>
#define ll long long
#define ull unsigned long long
#define fp(a,b,c) for(ll a=b;a<=c;a++)
#define fd(a,b,c) for(ll a=b;a>=c;a--)
#define pii pair<int,int>
#define pll pair<ll,ll>
#define inf 0x3f3f3f3f
#define base 127
#define mod 1000000007
#define eb emplace_back


using namespace std;

inline int rd(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch = getchar();
	return x * f;}
inline ll lrd(){
	ll x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch = getchar();
	return x * f;}
const int maxN=1e5+10;
vector<int> g[maxN];
int n,m;
pll hsh[maxN];
int col[maxN];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	n=rd(),m=rd();
	fp(i,1,m){
		int u=rd(),v=rd();
		g[u].eb(v),g[v].eb(u);
	}
	fp(i,1,n){
		if(g[i].empty()){
			cout << "-1" << endl;
			return 0;
		}
	}
	fp(i,1,n)
		sort(g[i].begin(),g[i].end());
	fp(i,1,n){
		hsh[i].second=i;
		for(int x:g[i])
			hsh[i].first=(hsh[i].first*base+x)%mod;
	}
	sort(hsh+1,hsh+n+1);
	vector<int> v;
	fp(i,2,n)
		if(hsh[i].first!=hsh[i-1].first) v.eb(i);
	if(v.size()!=2){
		cout << "-1" << endl;
		return 0;
	}
	fp(i,1,v[0]-1)
		col[hsh[i].second]=1;
	fp(i,v[0],v[1]-1)
		col[hsh[i].second]=2;
	fp(i,v[1],n)
		col[hsh[i].second]=3;
	fp(i,1,n) cout << col[i] << ' ';
	cout << endl;
	
	return 0;
} 

```

---

## 作者：弦巻こころ (赞：0)

考的时候死活没打出来.然后看了题解发现,一个重要的性质:对于在v1v2中的每一对顶点，x在v1中，y在v2中，xy之间有边

所以 类似于 3 0 这种是输出-1的,考的时候就被这个卡了.

这道这个性质我们可以干嘛呢?

我们发现不同的集合中必有连边.那么我们就在处理一个数的时候,把与这个数不连接的点扔进集合不就好了.

那么我们重复之前的操作.我们记三个vis 每次将数扔进集合中的时候.我们就将其连接的数全部设为不可扔进此集合. 所以我们就扫三遍,每次判断能不能加进去,如果能加就直接加就行了.

至于-1的情况,我们可以知道$m=cnt[1]*cnt[2]+cnt[2]*cnt[3]+cnt[3]*cnt[1]$才是合法的情况.所以如果$m!=cnt[1]*cnt[2]+cnt[2]*cnt[3]+cnt[3]*cnt[1]$就不合法.

需要注意的一个点是. 三个集合不为空. 所以如果你得出有个(些)集合为空的话,你必须要将一些数扔到那个(些)空集合中.(不然就会挂在3 0上.)

我的转换写的贼烂,见谅.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
vector<int> v[300005];
long long col[300005];
long long cnt[10];
long long n,m;
bool er[5][300005];
void ch();
void check(int now)//打标记.
{
	for(int j=0;j<v[now].size();j++)
	{
		er[col[now]][v[now][j]]=1;
	}
}
void find_ans(int x)
{
	for(int i=1;i<=n;i++)
	{
		if(!col[i])//如果这个数没被染过色
		{
			if(!er[x][i])//如果它可以被染成这个颜色
			{
				col[i]=x;
				check(i);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);	
	}
 
	find_ans(1);//跑三遍,也不用判连通.
	find_ans(2);
	find_ans(3);
	ch();
	if(m!=cnt[1]*cnt[2]+cnt[2]*cnt[3]+cnt[3]*cnt[1])
	{
		cout<<-1;
		return 0;
	}//判断是否合法.
	for(int i=1;i<=n;i++)
	{
		printf("%d ",col[i]);
	}
	return 0;
}
void ch()//稀烂的转换...
{
	for(int i=1;i<=n;i++)
	{
		cnt[col[i]]++;
	}
	int need1=0,need2=0;
	for(int i=1;i<=3;i++)
	{
		if(cnt[i]==0)
		{
			if(need1==0)
			{
				need1=i;
			}
			else need2=i;
		}
	}	
 
	if(need1)
	{
		for(int i=1;i<=3;i++)
		{
			if(cnt[i]>1)
			{
				for(int j=1;j<=n;j++)
				{
					if(col[j]==i)
					{
						col[j]=need1;
						cnt[i]--;
						break;
					}
				}
			}
		}
		cnt[need1]=1;
	}
	if(need2)
	{
		for(int i=1;i<=3;i++)
		{
			if(cnt[i]>1)
			{
				for(int j=1;j<=n;j++)
				{
					if(col[j]==i)
					{
						col[j]=need2;
						cnt[i]--;
						break;
					}
				}
			}
		}
		cnt[need2]=1;
	}
}
```




---

## 作者：Erina (赞：0)

## 玄学乱搞

注意: 细节很多.

首先发现如果存在一个合法的区分, 那么对于每个元素, 它会向每一个和它不同集合的元素连边. 然后不会向其他的点连边. 那么不难发现只会有一种可能.

那么我们可以试着求出一个, 然后检验它的可能性.

检验可能性的原理:

1. 如果有一个点和两个属于不同集合的元素都没有连边, 那么不行.
2. 如果有一条边两边的点属于同一个集合, 那么不行.
3. 如果总边数不匹配那么不行.
4. 如果图不连通那么不行.
5. 如果有一个集合的大小是0那么不行.

反正这几条够用了......

然后放一下代码......

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[1000000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
long long n, m;
typedef pair<int, int>mp;
mp arr[300005];
vector<int>road[300005];
int huaji[300005];
bool ax[300005];
long long full;
int diff(mp a, int x) {
	if (a.first == x)return a.second;
	else if (a.second == x) return a.first;
	else return -1;
}
long long siz[3];
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++)arr[i] = { read(),read() }, road[arr[i].first].push_back(arr[i].second), road[arr[i].second].push_back(arr[i].first);// 连边
	for (int i = 1; i <= m; i++)if (min(arr[i].first, arr[i].second) == 1)ax[max(arr[i].first, arr[i].second)] = 1;
	for (int i = 1; i <= n; i++)if (!ax[i])huaji[i] = 1;// 集合1
	memset(ax, 0, sizeof(ax));
	if (!road[1].size())cout << -1, exit(0);// 假的规则4
	int nex = road[1][0];
	for (int i = 1; i <= m; i++)if (diff(arr[i], nex) != -1)ax[diff(arr[i], nex)] = 1;
	for (int i = 1; i <= n; i++)if (!ax[i])if (!huaji[i])huaji[i] = 2; else cout << -1, exit(0);// 集合2, 规则1
	for (int i = 1; i <= n; i++)siz[huaji[i]]++;
	for (int i = 1; i <= m; i++)if (huaji[arr[i].first] == huaji[arr[i].second])cout << -1, exit(0);// 规则2
	full = n * (n - 1) / 2 - siz[0] * (siz[0] - 1) / 2 - siz[1] * (siz[1] - 1) / 2 - siz[2] * (siz[2] - 1) / 2;
	if (!siz[0] || !siz[1] || !siz[2])cout << -1, exit(0);// 规则5
	if (full != m)cout << -1, exit(0);// 规则3
	for (int i = 1; i <= n; i++)cout << huaji[i] + 1 << ' ';
}
```

码风有点毒瘤, 敬请见谅


---

