# Underground Lab

## 题目描述

邪恶的 Bumbershoot 公司在一个巨大的地下实验室里制造克隆人来进行可怕的实验。有一次，该公司克隆了一个比他的同伴更聪明的男孩安德里沙。安德里沙很快意识到，这个实验室发生了一些蹊跷的事情。他召集了克隆人同伴们去与邪恶的守卫兵团斗争。于是他们开始寻找实验室的出口。守护兵团不得不摧毁实验室的建筑群。

实验室可以看作是一个有 $n$ 个顶点和 $m$ 条边的无向图，$k$ 个安德里沙的克隆人同伴开始在一些顶点中寻找出口。每个克隆人每秒可以在任何顶点之间穿越一次，并且允许在任意一个顶点存在任何数量的克隆人。这些克隆人可以在任何时候停止寻找，但他在他的起始顶点必须寻找。出口可以位于实验室的任何一顶点，因此每个顶点必须至少有一个克隆人访问。

在实验室爆炸之前，每个克隆人最多只能访问 $\left\lceil\dfrac{2n}{k}\right\rceil$ 个顶点。

你的任务是选择起始顶点和克隆人的搜索路线。

每条路线可以有最多 $\left\lceil\dfrac{2n}{k}\right\rceil$ 个顶点。

## 样例 #1

### 输入

```
3 2 1
2 1
3 1
```

### 输出

```
3 2 1 3
```

## 样例 #2

### 输入

```
5 4 2
1 2
1 3
1 4
1 5
```

### 输出

```
3 2 1 3
3 4 1 5```

# 题解

## 作者：Provicy (赞：3)

$\text{Problem}:$[Underground Lab](https://codeforces.com/problemset/problem/780/E)

$\text{Solution}:$

观察到 $\lceil \frac{2n}{k} \rceil \times k \geq 2n$，而我们对于一个无向连通图进行 $DFS$，将第一次遍历和回溯到的点都加入路径中，这条路径长度 $len \leq 2n$，原因是每条边被经过 $2$ 次，而对于这条边的两个端点，如果其中一个点的度为 $1$，那么它有可能只被加入路径 $1$ 次。

所以我们无论如何都可以经过所有点，只需要给每个人分配小于等于 $\lceil \frac{2n}{k} \rceil$ 个点即可。特殊的，如果这条路径已经被分配完了却还有人剩余，这说明所有点都已经被遍历过了，那么让这个人站在 $1$ 节点就行了，特判一下即可。

$\text{Code}:$
```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=400010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,m,K,book[N];
int g[N*10+5]; int cnt;
int head[N],maxE; struct Edge { int nxt,to; }e[N<<1];
inline void Add(int u,int v) { e[++maxE].nxt=head[u]; head[u]=maxE; e[maxE].to=v; }
void DFS(int x)
{
	book[x]=1;
	g[++cnt]=x;
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(book[v]) continue;
		DFS(v), g[++cnt]=x;
	}
}
signed main()
{
	n=read(), m=read(), K=read();
	for(ri int i=1;i<=m;i++)
	{
		int u,v;
		u=read(), v=read();
		Add(u,v), Add(v,u);
	}
	int Mx=(n*2-1)/K+1;
	DFS(1);
	for(ri int i=1;i<=K;i++)
	{
		int now=min(cnt,Mx);
		if(!now) { puts("1 1"); continue; }
		printf("%lld",now);
		for(ri int j=1;j<=now;j++)
		{
			printf(" %lld",g[cnt--]);
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：xzggzh1 (赞：1)

题意：

给出一个图，有 $n$ 个点, $m$ 条边，$k$ 个人，每个人至多只能走$\lceil \frac{2n}{k} \rceil$ 步,要求每个点都被走到过，输出可行的方案即输出每个人所走的步数和所走点。

---

题解：

看到 $\lceil \frac{2n}{k} \rceil$ 可以想到答案也许和 $2n$ 有关。

其实这里的 $k$ 个人和 $1$ 个人是没有区别的，我们只要先考虑一个人怎么走过这 $n$ 个点。

只要 `dfs` 一下，纪录一下 `dfs` 时候的顺序即可，注意回溯的也要加入。

这样每个点最多会被到达两次（第一次到达和回溯到这个点）。

最后把这个 `dfs` 出来的序列分成 $k$ 段输出就好了。

---

核心代码（这里考虑直接搞成树，就不用多余的边）：

```cpp
int pre[N];vector<int> ans;vector<int> c[N];vector<int> vc[N];
int Find(int x){return pre[x] == x?x:pre[x] = Find(pre[x]);}
void dfs(int o, int u){
    ans.push_back(u);
    for(int v : vc[u]){
        if(v == o) continue;
        dfs(u, v);
        ans.push_back(u);
    }
}
int main(){
    int n, m, k, u, v;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; ++i) pre[i] = i;
    for(int i = 1; i <= m; ++i){
        scanf("%d%d", &u, &v);
        int fu = Find(u), fv = Find(v);
        if(fu == fv) continue;
        pre[fu] = fv;
        vc[u].push_back(v); vc[v].push_back(u);
    }
    dfs(0, 1);
    int can = (2*n  + k-1)/k;
    for(int i = 0; i < ans.size(); ++i)c[i/can].push_back(ans[i]);
    for(int i = 0; i < k; ++i){
        if(c[i].size() == 0) c[i].push_back(1);
        printf("%d", c[i].size());
        for(int v : c[i])printf(" %d", v);
        puts("");
    }
}

```

---

## 作者：lfxxx (赞：0)

为什么是 $2 \times n$ 除以 $k$ 呢？

直接对生成树欧拉序分为 $k$ 块即可！

显然欧拉序上相邻两点间有边相连，且长度满足条件。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
int stk[maxn],tp;
int vis[maxn];
vector<int> E[maxn];
int n,m,k;
void dfs(int u){
    stk[++tp]=u;
    int ct=0;
    vis[u]=1;
    for(int v:E[u]){
        if(vis[v]==0) dfs(v),stk[++tp]=u;
    }
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1);
    for(int i=1;i<=k;i++){
        vector<int> c;
        for(int j=1;j<=(2*n+k-1)/k;j++){
            if(tp==0) break;
            c.push_back(stk[tp]);
            tp--;
        }
        if(c.size()==0) c.push_back(1);
        cout<<c.size()<<' ';
        for(int x:c) cout<<x<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Ryder00 (赞：0)

题意清晰，不再阐述。

## 思路
注意到题目给出的限制是 $\lceil \frac{2n}{k} \rceil$，可以发现，一来一回进出一个点刚好是 $2$ 次。可以想到类似欧拉序的方法。于是，只要对这张图跑一遍 DFS 生成树即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=2e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,k,lim,cnt,js=1,vis[N];
map<int,map<int,int> >mp;
vector<int> e[N],ans[N];
void add(int x){
    cnt++,ans[js].pb(x);
    if(cnt==lim){
        js++;
        cnt=0;
    }
}
void dfs(int x){
    vis[x]=1;
    add(x);
    for(int y:e[x]){
        if(vis[y]) continue;
        dfs(y);
        add(x);
    }
} 
void solve(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u>v) swap(u,v);
        if(mp[u].count(v)) continue;
        mp[u][v]=1;
        e[u].pb(v),e[v].pb(u);
    }
    lim=(2*n+k-1)/k;
    dfs(1);
    if(ans[js].size()==0) ans[js].pb(1);
    while(js<k) js++,ans[js].pb(1);
    for(int i=1;i<=k;i++){
        cout<<ans[i].size()<<" ";
        for(int x:ans[i]) cout<<x<<" ";
        cout<<endl;
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：lndjy (赞：0)

看到图论的路径构造题，可以尝试 DFS 树。

建完树，就变成了 $k$ 条路径覆盖树的问题。

我们注意到 $\frac{2n}{k}$ 这个限制很奇怪，$\frac{2n}{k}\times k=2n$，也就是说我们要树上的每条边走两次，两次自然是一次进去子树一次回来。

如何用点表示子树？自然是 DFS 序。但是因为要往回走，所以回来的时候还要再记录一下，也就是欧拉序。把欧拉序均匀的分成 $k$ 段给每个人就行了。

为了实现方便，代码中没有均分，而是尽量先让一个人走满上界然后再给下一个人走。

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int N=2e5+5;
struct edge
{
	int to,nxt;
}e[N*2];
int n,m,k,cnt,tot,dfn[N*2],v[N],head[N];
vector<int> ans[N];
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void dfs(int now)
{
	dfn[++tot]=now;
	v[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	{
		if(!v[e[i].to]) dfs(e[i].to),dfn[++tot]=now;
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);add(y,x);
	}
	dfs(1);
	int len=2*n/k+((2*n)%k!=0);
	for(int i=1;i<=tot;i++)
	ans[i/len+1].push_back(dfn[i]);
	for(int i=1;i<=k;i++)
	{
		if(ans[i].empty())
		ans[i].push_back(1);
		cout<<ans[i].size()<<" ";
		for(int j=0;j<ans[i].size();j++)
		cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}
```


---

