# [ABC014D] 閉路

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc014/tasks/abc014_4

$ n $ 個の頂点と $ n-1 $ 本の辺からなる連結な無向グラフが与えられます．それぞれの頂点には $ 1 $ から $ n $ までの番号が順番にふられています．

グラフ理論において，このような条件を満たすグラフは木と呼ばれ，閉路を含まないという性質があります． このグラフに対し，元のグラフに含まれない追加辺 $ (a,b) $ を1つ追加したグラフについて考えてみると，このグラフはちょうど1つの閉路を含みます． あなたの仕事は，そのようなグラフについて，閉路の長さ(閉路に含まれる辺の数)を出力することです．ただ，追加辺の候補はいくつかあり，$ Q $ 個与えられるので，それら全ての候補について答えを出力してください．

## 说明/提示

### 部分点

この問題には2つのデータセットがあり，データセット毎に部分点が設定されている．

- $ Q=1 $ を満たすデータセット 1 に正解した場合は $ 30 $ 点が与えられる．
- 追加制約のないデータセット 2 に正解した場合は，上記のデータセットとは別に $ 70 $ 点が与えられる．

### Sample Explanation 1

図は以下の通りです．
![](https://atcoder.jp/img/abc/014/d1.png)

## 样例 #1

### 输入

```
5
1 2
1 3
1 4
4 5
3
2 3
2 5
2 4```

### 输出

```
3
4
3```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
4 5
5 6
4
1 3
1 4
1 5
1 6```

### 输出

```
3
4
5
6```

## 样例 #3

### 输入

```
7
3 1
2 1
2 4
2 5
3 6
3 7
5
4 5
1 6
5 6
4 7
5 3```

### 输出

```
3
3
5
5
4```

# 题解

## 作者：scp020 (赞：4)

# [ABC014D] 閉路

几乎是一道模板题。

## 读本篇题解需要了解的知识

- 什么是最近公共祖先。

- 重链剖分求最近公共祖先。

这两个知识点下文不再解释，没有掌握的同学请自行上网学习。

## 解法

题中给出一颗 $n$ 个顶点的树，给出 $q$ 组询问，每次询问给定 $u$ 和 $v$，表示在顶点 $u$ 和顶点 $v$ 之间添加一条边，对于每次询问，输出包含顶点  $u$ 和顶点 $v$ 之间的边的环中边的个数。

关于树的性质：

- 一棵树上是没有环的。

- 在树上添加一条边肯定会生成一个环。

考虑我们在顶点 $u$ 和顶点 $v$ 之间添加一条边后生成的这个环，这个环由两部分构成，一部分是新添加的一条边，另一部分是在原来树上从 $u$ 到 $v$ 的简单路径。

再来看这个简单路径，这个路径包含了从 $u$ 到两顶点的最近公共祖先的距离（这里即指简单路径长度，下文同）和 $v$ 到两顶点的最近公共祖先的距离，举例如图所示，用 [graph_editor](https://csacademy.com/app/graph_editor/) 作图。

![](https://cdn.luogu.com.cn/upload/image_hosting/aclet1nb.png)

考虑 $u = 5,v = 3$ 的情况，在顶点 $5$ 和 $3$ 之间添加一条边，此时这个环的边的数量为 $4$。其中包括顶点 $1$（顶点 $5$ 和 $3$ 的最近公共祖先）到顶点 $5$ 的距离，顶点 $1$ 到顶点 $3$ 的距离和新添加的这条边。

我们可以钦定一个点为这棵树的树根，从这个点开始两次深搜后得到最近公共祖先，两个点到它们的最近公共祖先的距离分别是两个点和它们的最近公共祖先的深度的差，所以对于每次询问我们只要输出 $dep_u - dep_{LCA} + dep_v - dep_{LCA} + 1 = dep_u + dep_v - 2 \times dep_{LCA} +1$ 即可。

###   代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int n,q,cnt,head[100010],dep[100010],f[100010],siz[100010],hvson[100010],start[100010];
struct edge
{
	int to,next;
};
edge e[200010];
inline void add(const int &x,const int &y)
{
	e[++cnt].to=y,e[cnt].next=head[x],head[x]=cnt;
}
inline void dfs1(int pos,int fa,int depth,int maxi=-0x3f3f3f3f)
{
	dep[pos]=depth,f[pos]=fa,siz[pos]=1;
	for(int i=head[pos];i;i=e[i].next)
	{
		if(e[i].to!=fa)
		{
			dfs1(e[i].to,pos,depth+1),siz[pos]+=siz[e[i].to];
			if(siz[e[i].to]>maxi) hvson[pos]=e[i].to,maxi=siz[e[i].to];
		}
	}
}
inline void dfs2(int pos,int Start)
{
	start[pos]=Start;
	if(hvson[pos])
	{
		dfs2(hvson[pos],Start);
		for(int i=head[pos];i;i=e[i].next)
			if(e[i].to!=f[pos] && e[i].to!=hvson[pos]) dfs2(e[i].to,e[i].to);
	}
}
inline int lca(int x,int y)
{
	while(start[x]!=start[y])
		if(dep[start[x]]>=dep[start[y]]) x=f[start[x]];
		else y=f[start[y]];
	if(dep[x]>=dep[y]) return y;
	else return x;
}
int main()
{
	read(n);
	for(int i=1,x,y;i<n;i++) read(x),read(y),add(x,y),add(y,x);
	read(q),dfs1(1,0,1),dfs2(1,1);
	for(int i=1,x,y;i<=q;i++) read(x),read(y),write(dep[x]+dep[y]-2*dep[lca(x,y)]+1),Putchar('\n');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：Pengzt (赞：3)

[ABC014D](https://www.luogu.com.cn/problem/AT_abc014_4)

题意非常明确，不再赘述。

即求一棵树添加了一条 $u$ 到 $v$ 的边后，包含该边的环的长度。

令 $lca$ 表示 $u$ 和 $v$ 的最近公共祖先。

若添加了这条边，那么这个环肯定包含了 $u$ 到 $lca$ 的简单路径和 $lca$ 到 $v$ 的简单路径。
这个环还差的 $1$ 条边，就是新加的 $u$ 到 $v$ 的边。

设点 $i$ 的深度为 $dep_i$，则环的长度为 $dep_u+dep_v-2\times dep_{lca}+1$。

代码挺简单，不贴了。

---

## 作者：hjqhs (赞：1)

### 题目大意：
给定一个 $n$ 个结点的树，共 $q$ 次询问。  
每次询问给出两点 $x,y$，假设在 $x,y$ 两点之间连一条边，求包括这条边的环的长度。  
### 分析;
很显然，这条环的长度就是原本 $x,y$ 之间路径长度 $+1$（那条新加入的边）。如何求得 $x,y$ 之间的路径长度？暴力搜索显然会超时，考虑 lca。设两点 lca 为 $z$。则 $x,y$ 之间路径长度为 $dep_x+dep_y-2\times dep_z$。倍增求解 lca 即可。
### Code:
```cpp
//O((n+q)logn)
//预处理O(nlogn) 单次询问O(logn)
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,q,rt,dep[maxn],anc[maxn][22];
//anc[u][i]表示节点u的2^i级祖先
vector<int>g[maxn];
void dfs(int u,int f){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==f)continue;
		dep[v]=dep[u]+1;
		anc[v][0]=u;//一个节点的2^0=1级祖先就是它的父节点
		dfs(v,u);
	}
}
void init(){//统一处理出每个点的2^i级祖先
	for(int j=1;j<=21;j++)//这里的18指O(logn)
		for(int i=1;i<=n;i++)
			anc[i][j]=anc[anc[i][j-1]][j-1];
}
int queryLCA(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=21;i>=0;i--)
		if(dep[anc[u][i]]>=dep[v])
			u=anc[u][i];
	//从大到小枚举二进制位，将较深的结点往上提
	if(u==v)return u;
	for(int i=21;i>=0;i--)
		if(anc[u][i]!=anc[v][i])
			u=anc[u][i],v=anc[v][i];
	//然后用相同的办法提两个点
	//由于i只枚举到0，所以现在实际上是u v两点父节点相同
	return anc[u][0];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	rt=1;
	dep[rt]=1;
	dfs(rt,0);
	init();
	cin>>q;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		cout<<dep[x]+dep[y]-2*dep[queryLCA(x,y)]+1<<'\n';
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

前置知识：[最近公共祖先](/problem/P3379)，不懂的先看看那题。

可以用 st 表、tarjan 和树剖求 LCA，这里用较好理解的 st 表求。

设树上两点 $x,y$ 的 LCA 是 $p$，它们之间的距离就是 $x$ 到 $p$ 的距离加上 $y$ 到 $p$ 的距离。又是 $x$ 到根节点的距离加上 $y$ 到根节点的距离，再减去两倍的 $p$ 到根节点的距离，这个用差分很好证明。用式子表示就是 $dis(x,y)=dep_x+dep_y-2dep_p$。

因为树上任意两点的简单路径有且仅有一条，所以包含 $x,y$ 之间边的环也**有且仅有一个**，环上包含边数就是原来 $x,y$ 的距离加 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,id,to[N],ne[N],head[N],lg[N],dep[N],st[N][20];
void add(int x,int y) {to[++id]=y,ne[id]=head[x],head[x]=id;}
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1,st[u][0]=fa;
	for(int i=1;i<=lg[dep[u]];i++) st[u][i]=st[st[u][i-1]][i-1];
	for(int i=head[u];i;i=ne[i])
	{
		int v=to[i];if(v==fa) continue;
		dfs(v,u);
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]) x=st[x][lg[dep[x]-dep[y]]-1];
	if(x==y) return x;
	for(int i=lg[dep[x]];~i;i--)
		if(st[x][i]!=st[y][i]) x=st[x][i],y=st[y][i];
	return st[x][0];
}
void solve()
{
	n=read();
	for(int i=1,x,y;i<n;i++) x=read(),y=read(),add(x,y),add(y,x);
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	dfs(1,0),m=read();
	while(m--)
	{
		int x=read(),y=read(),p=LCA(x,y);
		write(dep[x]+dep[y]-(dep[p]<<1)+1,"\n");
	}
}
signed main()
{
	int T=1;
	while(T--) solve();
}

```

---

## 作者：taojinchen (赞：0)

# 思路
根据树的性质，我们知道当树上两个点之间没有直接的连边时，如果我们给两个点再连一条边，所构成的这一个环就是，现在树上两个点连的一条边和树上的另一条路径构成的。因为树上的不同两个点之间的路径是唯一的，所以我们只要求出简单路径的长度再加上一即可，而这一条路径就是这两个点分别到最近公共祖先的距离之和。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int kM=1e5+5;
ll n,q,i,j,x,y,u,v,cnt,to[kM<<1],ne[kM<<1],ed[kM],f[kM][20],dis[kM];
void add(){//链式前向星
  ne[++cnt]=ed[u],to[cnt]=v,ed[u]=cnt;
  swap(u,v);
  if(cnt&1)add();//个人习惯，仅限于双向边
  return;
}
void dfs(int rt,int fa){
  int i;
  f[rt][0]=fa;//记录自己的父亲
  dis[rt]=dis[fa]+1;//记录深度
  for(i=ed[rt];i;i=ne[i]){
    if(fa!=to[i]){
      dfs(to[i],rt);//递归处理
    }
  }
  return;
}
ll lca(ll x,ll y){//最近公共祖先
  if(dis[x]<dis[y])swap(x,y);//方便处理
  ll t=dis[x]-dis[y];//深度之差
  for(i=18;~i;i--){
    if(t-(1<<i)>=0){
      x=f[x][i];//不断的往上跳
      t-=(1<<i);
    }
  }
  if(x==y)return x;//y是x的祖先
  for(i=18;~i;i--){
    if(f[x][i]!=f[y][i]){//不相遇
      x=f[x][i];//同时向上跳
      y=f[y][i];
    }
  }
  return f[x][0];//相遇（LCA）
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(i=1;i<n;i++){
    cin>>u>>v;//输入
    add();//建边
  }
  dfs(1,1);//预处理
  for(j=1;j<=18;j++){//一定是外层枚举各级祖先
    for(i=1;i<=n;i++){//注意内层和外层循环的顺序
      f[i][j]=f[f[i][j-1]][j-1];//i的求出j级祖先
    }
  }
  cin>>q;
  while(q--){
    cin>>x>>y;//连边
    ll t=lca(x,y);//最近公共祖先
    cout<<abs(dis[t]-dis[x])+abs(dis[t]-dis[y])+1<<"\n";//计算
  }
  return 0;
}
```


---

## 作者：ruanwentao666 (赞：0)

# AT_abc014_4题解
[~~一个神奇的魔法~~](https://www.luogu.com.cn/problem/AT_abc014_4)

## 题目简化
题目说了那么多复杂的东西，其实就是求节点 $x$ 到节点 $y$ 最少经过的边数再加 $1$。

## 思路分析
我们可以尝试暴力，但你一定会被数据毒死。所以我们需要更高效的算法。

我们首先分析一下样例 $1$：如果求节点 $2$ 至节点 $3$ 最少经过的边数再加 $1$，我们必定会经过他们的最近公共祖先 $1$。那么问题就变成了节点 $2$ 至节点 $1$ 最少经过的边数加上节点 $1$ 至节点 $3$最少经过的边数再加 $1$。

求一个节点到其祖先节点最少经过的边数，只需将这两个节点中深度大的和深度小的相减即可。那么定义 $d_i$ 为节点 $i$ 的深度，$f_i$ 为节点 $i$ 的父亲节点，则有如下状态转移方程：

$$d_i \gets d_{f_i} + 1$$

边界即为：
$$d_1 \gets 1$$

我们假设节点 $x$ 和节点 $y$ 的最近公共祖先为 $s$，则最后的答案为:
$$d_x - d_s + d_y - d_s + 1$$

整理，得：
$$d_x + d_y - 2 \times d_s + 1$$

补充一句：如果对最近公共祖先算法不了解的话，建议做一下 3379。

[P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

好了，上代码。我这里使用倍增算法，感兴趣的同学也可以尝试离线算法 Tarjan。
```cpp
#include<iostream>
#include<vector>
using namespace std;
int n, m, root, x, y;
vector<int>g[500005];
int f[500005][21], lg[500005];
struct node {
    int deeps;//深度
    int fa;//直接父节点  
}t[500005];
bool vis[500005];
void init() {//时间复杂度：O(nlogn) 
    for (int i = 1; (1 << i) <= n; i++) {
        for (int j = 1; j <= n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }
}
void dfs(int u, int dep) {//处理出各个点的深度
    t[u].deeps = dep;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!vis[v]) f[v][0] = u, t[v].fa = u, vis[v] = true, dfs(v, dep + 1);
    }
}
int LCA(int u, int v) {
    if (t[u].deeps > t[v].deeps) {
        swap(u, v);
    }
    while (t[u].deeps < t[v].deeps) {
        v = f[v][lg[t[v].deeps - t[u].deeps] - 1];
    }
    if (u == v)return u;
    for (int k = lg[n] - 1; k >= 0; k--) {
        if (f[u][k] != f[v][k]) {
            u = f[u][k], v = f[v][k];
        }
    }
    return t[u].fa;
}
int main() {
    cin >> n;root=1;
    t[root].deeps = 1;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    vis[root] = true;
    dfs(root, 1);//计算每个节点的深度 
    init();//预处理st表 
    for (int i = 1; i <= n; i++) {
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y;
        int j=LCA(x, y);//j为节点x和节点y的最近公共祖先 
        cout<<t[x].deeps+t[y].deeps-2*t[j].deeps+1<<endl;
    }
    return 0;
}
```


---

## 作者：_AyachiNene (赞：0)

# 思路：
给出的是一棵树，所以两个点之间的路径是唯一的。所以在它们之间只用连一条边就能构成环。所以可以求他们的最近公共祖先，这个环所包含的边就是它们之间的路径长度加一。
# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int nxt,to;
}e[114514*2];
int head[114514],cnt;
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
int n,q;
int dep[114514],top[114514],f[114514],siz[114514],son[114514];
void dfs1(int u,int fa)
{
	siz[u]=1;
	dep[u]=dep[fa]+1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v!=fa)
		{
			f[v]=u;
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
}
void dfs2(int u,int t)
{
	top[u]=t;
	if(son[u])
		dfs2(son[u],t);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v!=f[u]&&v!=son[u])
			dfs2(v,v);
	}
}
int lca(int x,int y)                      //树剖求lca 
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=f[top[x]];
	}
	return dep[x]>dep[y]?y:x;
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)         //建树 
	{
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}	
	dfs1(1,0);               //树剖 
	dfs2(1,1);
	cin>>q;
	while(q--)
	{
		int x,y,Lca;
		cin>>x>>y;
		Lca=lca(x,y);
		cout<<dep[x]+dep[y]-2*dep[Lca]+1<<endl;             //算出答案 
	}
}
```


---

## 作者：CSPJ10pts (赞：0)

## 题意

有一棵 $N$ 个节点的树，求从点 $\texttt{x}$ 到点 $\texttt{y}$ 要经过多少个点。

## 分析

前置知识：[【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

乍一看，好像没什么思路，直接搜索速度会很慢。没事，我们模拟一下就好理解了。我们就拿样例一来举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/k9xkpc2u.png)

**第一问：求从点 $\tt2$ 到点 $\tt3$ 要经过多少个点。**

答案是 $\tt2$：$\tt2$ $\rightarrow$ $\tt1$ $\rightarrow$ $\tt3$，共三个点。

**第二问：求从点 $\tt2$ 到点 $\tt5$ 要经过多少个点。**

答案是 $\tt4$：$\tt2$ $\rightarrow$ $\tt1$ $\rightarrow$ $\tt4$ $\rightarrow$ $\tt5$，共四个点。

**第三问：求从点 $\tt2$ 到点 $\tt4$ 要经过多少个点。**

答案是 $\tt3$：$\tt2$ $\rightarrow$ $\tt1$ $\rightarrow$ $\tt4$，共三个点。

观察发现：从点 $\texttt{x}$ 到点 $\texttt{y}$ 一定会经过一个点：它们的最近公共祖先。比如在第一问中从点 $\tt2$ 到点 $\tt3$ 经过了它们的最近公共祖先点 $\tt1$。

我们令点 $\texttt{x}$ 与点 $\texttt{y}$ 的最近公共祖先为点 $\tt{z}$，点 $\texttt{x}$ 到点 $\texttt{y}$ 经过的点数就可以这么表示：点 $\texttt{x}$ 到点 $\texttt{z}$ 的距离 $\tt+$ 点 $\texttt{x}$ 到点 $\texttt{z}$ 的距离 $\tt{+1}$。虽然我们不知道这两者分别是多少，但不要忘了点 $\texttt{x}$ 和点 $\texttt{z}$ 是在同一条边上的，它们之间的距离很好求：点 $\tt{x}$ 的深度减点 $\tt{z}$ 的深度，点 $\tt{y}$ 同理。至于深度，我们在预处理最近公共祖先的时候就可以求出来。

最后，点 $\texttt{x}$ 到点 $\texttt{y}$ 经过的点数便是：$dep_x + dep_y - 2 \times dep_z + 1$，其中 $dep$ 代表深度。

## 代码
这里我选用了倍增求最近公共祖先，主要是因为个人喜好。

```
#include <iostream>
using namespace std;
#define N 100001
#define maxl 22
inline int n, m, x, y, cnt, dep[N], f[2 * N][maxl], head[N], to[2 * N], nxt[2 * N];
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - 48; ch = getchar();}
	return x * f;
} // 快读（其实可以不要）
void add(int x, int y) {
	to[++cnt] = y;
	nxt[cnt] = head[x];
	head[x] = cnt;
} // 链式前向星存图
void dfs(int x, int fa) {
	f[x][0] = fa, dep[x] = dep[fa] + 1; // 求深度 
	for (int i = 1; (1 << i) <= dep[x]; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for (int i = head[x]; i; i = nxt[i]) if (to[i] != fa) dfs(to[i], x);
} // 预处理
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = maxl - 1; i >= 0; i--) if (dep[x] - dep[y] >= (1 << i)) x = f[x][i];
	if (x == y) return x;
	for (int i = maxl - 1; i >= 0; i--) if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
} // 求两个节点的最近公共祖先
int main() {
	n = read();
	for (int i = 1; i < n; i++) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	m = read();
	while (m--) {
		x = read(), y = read();
		printf("%d\n", dep[x] + dep[y] - dep[lca(x, y)] * 2 + 1);
	}
	return 0;
}
```

[通过记录~](https://www.luogu.com.cn/record/102800196)

---

## 作者：AlicX (赞：0)

### 前言
前置知识：最近公共祖先，就是求两个点的最近的点且这个点是他们两个点的祖先。

## 思路
- 暴力：首先考虑暴力，每连一条边，我们就从这两个点开始搜索，使用双向广搜，最终会搜到一个点上，但这样时间复杂度还是不够优秀。

- 正解：观察到题目中说的这是一棵树，向没两个点连边后，两个点将在他们的最近公共祖先上形成环，假设当前点是 $1$ 和 $2$，并且他们的公共祖先为 $3$，那么最终形成的环里的数就是 $1,2,3$，记录第 $i$ 个点的深度为 $dep_i$，那么答案就是 $dep_u-dep_{LCA(u,v)}+dep_v-dep_{LCA(u,v)}+1$，其中 $LCA(u,v)$ 表示 $u$ 和 $v$ 的公共祖先。

## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+10,M=35;
int n,m;
int dep[N];
int f[N][M];
int h[N],idx=0;
struct Node{
	int to,ne;
}tr[N<<1];
void add(int u,int v){
	tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++;
}
void dfs(int u,int fa){
	f[u][0]=fa,dep[u]=dep[fa]+1;
	for(int i=h[u];i!=-1;i=tr[i].ne){
		int to=tr[i].to;
		if(to==fa) continue;
		dfs(to,u);
	}
}
void dp(){
	for(int j=1;j<M;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
}
int plc(int x,int k){
	int p=0;
	while(k){
		if(k&1) x=f[x][p];
		p++,k>>=1; 
	}
	return x;
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	x=plc(x,dep[x]-dep[y]);
	if(x==y) return x;
	for(int i=M-1;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
signed main(){
	memset(h,-1,sizeof h);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0),dp();
	cin>>m;
	while(m--){
		int u,v;
		cin>>u>>v;
		int root=LCA(u,v);
		cout<<dep[u]+dep[v]-2*dep[root]+1<<endl;
	}
	return 0;
} 
```

---

