# Lenient Vertex Cover

## 题目描述

You are given a simple connected undirected graph, consisting of $ n $ vertices and $ m $ edges. The vertices are numbered from $ 1 $ to $ n $ .

A vertex cover of a graph is a set of vertices such that each edge has at least one of its endpoints in the set.

Let's call a lenient vertex cover such a vertex cover that at most one edge in it has both endpoints in the set.

Find a lenient vertex cover of a graph or report that there is none. If there are multiple answers, then print any of them.

## 说明/提示

Here are the graphs from the first example. The vertices in the lenient vertex covers are marked red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1680F/04fc7cc460e4db0f5f28c20a639501c9ca608abf.png)

## 样例 #1

### 输入

```
4
6 5
1 3
2 4
3 4
3 5
4 6
4 6
1 2
2 3
3 4
1 4
1 3
2 4
8 11
1 3
2 4
3 5
4 6
5 7
6 8
1 2
3 4
5 6
7 8
7 2
4 5
1 2
2 3
3 4
1 3
2 4```

### 输出

```
YES
001100
NO
YES
01100110
YES
0110```

## 样例 #2

### 输入

```
1
10 15
9 4
3 4
6 4
1 2
8 2
8 3
7 2
9 5
7 8
5 10
1 4
2 10
5 3
5 7
2 9```

### 输出

```
YES
0101100100```

## 样例 #3

### 输入

```
1
10 19
7 9
5 3
3 4
1 6
9 4
1 4
10 5
7 1
9 2
8 3
7 3
10 9
2 10
9 8
3 2
1 5
10 7
9 5
1 2```

### 输出

```
YES
1010000011```

# 题解

## 作者：Yasuraoka_Hanabi (赞：6)

- 前言

目前这个做法的灵感是来自 CF1555F 的，但我还没有能够严谨说明其正确性，目前我也没有了解到和我一样的做法。所以希望把它先放出来，如果有神仙可以说明该算法的正确性（或者 hack 了它），欢迎指教。

------------

显然，当原图为二分图的时候，我们直接染色即可。

否则，问题变为能否去掉一条边使其变为二分图。

去掉一条边实质上是说把这条边的两端点都框选进，并不是真的删除。因此，偶环上的边，是不允许被删除的。

对于奇环，则必须删除其一条边，所以删除的这条边，应该在所有奇环的边的交集里。

到这里的分析都是严谨的。接下来的做法是我自己想到、实现并通过的，但我确实还不明白其正确性：

首先对于原图建生成树，考虑加入非树边。

加入一条非树边 $(u,v)$ 的时候，如果 $u\rightarrow v$ 的树上路径有偶数个点，则 $u\rightarrow v$ 的树上路径的边都是不能选的，打一个标记；否则，把 $u\rightarrow v$ 的树上路径的边的权值都加上 $1$，并且 $cnt\leftarrow cnt+1$。

最后，找到一条未被打标记，且边权等于 $cnt$ 的树边，删除它，即为答案。

注意到这个做法过不去样例 $1$，分析一下后发现有一种 corner case：即当 $cnt=1$ 的时候，找到那条非树边，直接删去那条非树边即可。

算上这种情况，确实可以通过本题。

鉴于代码太长就直接放 CF 提交记录了：[记录](https://codeforces.com/contest/1680/submission/157385348)

---

## 作者：I_am_Accepted (赞：5)

来自 [我发的帖](https://www.luogu.com.cn/discuss/439117) [王学逸](https://www.luogu.com.cn/user/317459) 的做法，在此鸣谢。

当然是双 $\log$ 的做法 /qd。

### Analysis

首先，如果原图就是二分图，那直接黑白间隔染色即可。

否则，我们需要找到一条边使得删掉后就是二分图，或者判断没有这样的边。

我们把 $m$ 条边（按任意顺序）排成一行，并构建线段树（实际实现中不用）。

递归判断删掉区间 $[l,r]$ 内的边后剩下的图是否是二分图，这里使用可撤销并查集判断二分图。

具体递归时在进左区间前将右区间的边加进去（记得做完后撤销），如果当前图不是二分图直接 `return`，同理递归右区间。

递归到 $[l,r](l=r)$ 时就找到了删掉一条边是二分图的方案了，下标为 $l(=r)$ 的这条边就是被删的边。

由于可撤销并查集的时间复杂度带 $\log$，线段树每一层的边都会被加入并删除一次，所以最终时间复杂度为 $O(n\log^2 n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0) 
#define For(i,j,k) for(int i=j;i<=k;i++)
#define pi pair<int,int>
#define N 1000010
#define mkp make_pair
#define fir first
#define sec second
#define pb emplace_back
int n,m,ans,col[N],f[N],sz[N],g[N];
pi a[N];
vector<int> E[N];
void dfs(int x,int c){col[x]=c; for(int i:E[x]) if(!col[i]) dfs(i,3-c);}
inline pi gf(int x){//return mkp(id,val)
	if(x==f[x]) return mkp(x,0);
	pi res=gf(f[x]);
	res.sec^=g[x];
	return res;
}
int del[N],tot=0;
inline bool merge(int x,int y){
	int op=1;pi res;
	res=gf(x);op^=res.sec;x=res.fir;
	res=gf(y);op^=res.sec;y=res.fir;
	if(x==y) return op==0;
	if(sz[x]<sz[y]) swap(x,y);
	sz[x]+=sz[y];
	f[y]=x;g[y]=op;
	del[++tot]=y;
	return true;
}
inline void antimerge(){
	int x=del[tot--];
	sz[f[x]]-=sz[x];f[x]=x;
}
void solve(int l,int r){
	if(ans!=-1) return ;
	if(l==r){
		ans=l;
		return ;
	}
	//left
	int re=tot,mid=(l+r)>>1;
	bool flag=1;
	For(i,mid+1,r) if(!merge(a[i].fir,a[i].sec)){flag=0; break;}
	if(flag) solve(l,mid);
	while(re!=tot) antimerge();
	if(ans!=-1) return ;
	//right
	flag=1;
	For(i,l,mid)   if(!merge(a[i].fir,a[i].sec)){flag=0; break;}
	if(flag) solve(mid+1,r);
	while(re!=tot) antimerge();
}
void work(){
	cin>>n>>m;
	For(i,1,m) cin>>a[i].fir>>a[i].sec;
	For(i,1,n) E[i].clear();
	For(i,1,m) E[a[i].fir].pb(a[i].sec),E[a[i].sec].pb(a[i].fir);
	For(i,1,n) col[i]=0;
	dfs(1,1);
	bool flag=1;
	For(i,1,m) if(col[a[i].fir]==col[a[i].sec]) flag=0;
	if(flag){
		cout<<"YES"<<endl; For(i,1,n) cout<<col[i]-1; cout<<endl;
		return ;
	}
	ans=-1;
	For(i,1,n) f[i]=i;
	For(i,1,n) sz[i]=1;
	solve(1,m);
	if(ans==-1){
		cout<<"NO"<<endl;
		return ;
	}
	cout<<"YES"<<endl;
	For(i,1,n) E[i].clear();
	For(i,1,m) if(ans!=i) E[a[i].fir].pb(a[i].sec),E[a[i].sec].pb(a[i].fir);
	For(i,1,n) col[i]=0;
	dfs(1,1);
	if(col[a[ans].fir]==1) For(i,1,n) col[i]=3-col[i];
	For(i,1,n) cout<<col[i]-1; cout<<endl;
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：FelFa_1414666 (赞：4)

## 题意

给定一张 $n$ 个节点，$m$ 条边的无向连通图。求输出一组节点覆盖，使得最多有一条边的两端节点都被选择。

- $2\le n\le 10^6$
- $n-1\le m\le\min(10^6,\frac{n\times(n-1)}2)$

---

## 思路

考虑所有边都只有一个端点被选的覆盖。如果存在这样一组覆盖，那么原图一定是**二分图**。

接下来，考虑有一个边的两个端点都被选的情况。我们发现如果原图不是二分图，那么一定存在**奇环**。我们希望找到一条边，将这条边两个端点合并后，能使得原图变成二分图，就满足了题目。

所以这条边一定要存在于所有奇环上，且不能存在于任意偶环上（合并后要让奇环消失且不能产生新的奇环）。这样就想到在 **dfs** 进行二分图染色的同时统计所有的环，对每个边记录它存在的奇环和偶环数量。

统计时需要用到一个**树上差分**的小技巧。我们知道无向图 dfs 中除了树边就是回边，所以所有的环都由若干个树边和一个回边组成，只要在发现环时，对回边记一次数，再对树边路径差分统计一下。最后总的 dfs 一次统计子树和，就能统计出每条边的奇环偶环个数。

然后我们就找到一条存在于所有奇环上的边，将其删除就能得到二分图。如果这条边不存在，输出 NO。最后进行一次二分图染色，注意要让被删边的端点染为 1。

实现时有一些细节要注意，例如要处理一下每个点在 dfs 上的父边。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
inline int read(){//快读快写
	int x=0,f=0;char ch=getchar();while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return f?-x:x;
}
template<typename T>inline void write(T x){
    if(x<0)x=-x,putchar('-');if(x>9)write(x/10);putchar(x%10^48);
}
int n,m,odd,cnt0[1000005],cnt1[1000005],c[1000005],fe[1000005];//cnt0偶环个数，cnt1奇环个数，c节点颜色，fe父边
bool vis[1000005];
pii e[1000005];
vector<pii> G[1000005];
void dfs(int u,int p,int cl)//二分图染色同时找环
{
	c[u]=cl;
	vis[u]=1;
	fe[u]=p;
	for(auto pp:G[u])
		if (pp.S!=p)
		{
			int to=pp.F,id=pp.S;
			if (c[to]==-1)
				dfs(to,id,cl^1);
			else if (c[to]==cl^1&&vis[to])//偶环
				cnt0[id]++,cnt0[p]++,cnt0[fe[to]]--;
			else if (c[to]==cl&&vis[to])//奇环
				odd++,cnt1[id]++,cnt1[p]++,cnt1[fe[to]]--;
		}
	vis[u]=0;//回溯时撤销访问标记
}
void dfs2(int u)//整理差分数组，得到每条边的计数
{
	vis[u]=1;
	for(auto pp:G[u])
		if (!vis[pp.F])
		{
			int to=pp.F;
			dfs2(to);
			if (fe[u]!=-1&&fe[to]!=-1);
			cnt0[fe[u]]+=cnt0[fe[to]],cnt1[fe[u]]+=cnt1[fe[to]];
		}
}
void dfs3(int u,int cl)//二分图染色
{
	c[u]=cl;
	for(auto pp:G[u])
		if (c[pp.F]==-1)
		{
			int to=pp.F;
			dfs3(to,cl^1);
		}
}
void run()
{
	odd=0;//一系列初始化
	n=read(),m=read();
	for(int i=0;i<n;i++)
		G[i].clear();
	fill(cnt0,cnt0+m+3,0);
	fill(cnt1,cnt1+m+3,0);
	fill(c,c+n+3,-1);
	fill(vis,vis+n+3,0);
	for(int i=0;i<m;i++)
	{
		e[i]=mp(read()-1,read()-1); 
		G[e[i].F].pb(mp(e[i].S,i));
		G[e[i].S].pb(mp(e[i].F,i));
	}
	dfs(0,-1,0);
	fill(vis,vis+n+3,0);
	dfs2(0);
	int x=-1,y=-1;
	if (odd)//存在奇环
	{
		for(int i=0;i<m&&x==-1;i++)
			if (cnt1[i]==odd&&cnt0[i]==0)
				x=i;
		if (x==-1)
		{
			puts("NO");
			return;
		}
		y=e[x].F,x=e[x].S;
		sort(G[x].begin(),G[x].end());
		sort(G[y].begin(),G[y].end());
		G[y].erase(lower_bound(G[y].begin(),G[y].end(),mp(x,-1)));//删边
		G[x].erase(lower_bound(G[x].begin(),G[x].end(),mp(y,-1)));
	}
	fill(c,c+n+3,-1);
	dfs3(0,1);
	int f=(x==-1?0:c[x]^1);//保证被删边的端点颜色为1
	puts("YES");
	for(int i=0;i<n;i++)
		write(c[i]^f);
	putchar('\n');
}
int main()
{
	int TT=read();
	while(TT--)
		run();
	return 0;
}
```

- 时间复杂度：$\operatorname O(n+m)$
- 空间复杂度：$\operatorname O(n+m)$

~~我的程序又臭又长（~~

---

## 作者：do_it_tomorrow (赞：3)

如果原图是二分图，那么直接进行染色即可，下面考虑不是二分图的情况。

因为一个图是二分图的充要条件不存在奇环，所以为了将一个不是二分图的东西进行染色，需要找到一条边满足所有的奇环都经过这条边而且没有偶环经过。

之所以需要没有偶环，是因为选择的这条边两侧的颜色是一样会的。

这样就相当于经过这条边不改变颜色，所以原本的偶环就只会经过奇数条改变颜色的边，也就相当于是奇环了。

现在需要找到一条被所有的奇环经过且没有被偶环经过的边，或者报告无解。

容易想到给所有的奇环和偶环分别染色，最后遍历每一条边，如果满足条件那么就有解。

考虑对图进行一个类似于 Tarjan 的操作，跑出一个 dfs 树。

因为所有的环肯定是经过了若干条树边和一条非树边，所以就可以在遍历树的同时处理非树边即可。

具体的，可以通过树链剖分的方式处理树边，对于非树边直接暴力修改即可。

对于只有一个奇环的情况并不需要特判，因为这个情况非树边必然满足被所有的奇环经过而且没有偶环经过。

时间复杂度为 $O(m+n\log n)$。

---

## 作者：Rushroom (赞：2)

DFS 树的性质。

首先注意到题面中的这一句话：

> 最多只能有一条边，满足两个顶点都在这个点集中。

显然，“最多只能有一条边”意思就是有 $0$ 条或 $1$ 条。

### 0 条

所以每条边都恰好只有一个顶点在点集中。

很自然想到二分图染色，每条边两个顶点颜色不同。

所以只要这个图是二分图，就一定有解。

### 1 条

有一条边的两个点同色，那么去掉这个边后，剩下的图一定就是一个二分图，就转化成了上一个情况。

先 DFS 一遍。一个~~显然的~~重要的性质是：对于原图中的每条边，要么是 DFS 树中的一条边，要么是一条返祖边（即一个点连向它祖先的边）。

因为二分图中没有奇环，所以这条去掉的边一定在所有奇环上，而不能在任何一个偶环上（这样去掉之后就全是偶环了）。

考虑去掉什么边。

#### 返祖边

因为一个环在 DFS 树中一定是一条链加上一条返祖边，所以在 DFS 遇到返祖边时判断这个环是奇环还是偶环，就能统计出奇环数量了。如果奇环数量为 $1$，那么直接去掉那条返祖边即可。

#### 树边

在统计环时把环上的所有树边都标记 $+1$，最后看是否有一个树边满足：

- 所在的奇环数 $=$ 奇环总数
- 所在的偶环数 $=0$

即可。

标记时用树上差分即可，不会的同学可以左转 OI Wiki。

最后判断答案时只需要再 DFS 一遍，按照深度奇偶性染色即可。

**注意**：有可能结果是：一条边满足两个顶点都不在点集中，其他每条边都有一个顶点在点集中。这时候只需要把所有颜色反转即可。

[Code](https://www.luogu.com.cn/paste/ih3ur3wt)

---

## 作者：WTR2007 (赞：1)

[CF1680F Lenient Vertex Cover](https://www.luogu.com.cn/problem/CF1680F)

下面用 $G$ 表示一个环的边集，记作环 $G$。

我们令一个环 $G$ 的价值为它经过的**返祖边**数量，记作 $Z(G)$，下面给出核心结论：

> 若存在一条边 $e_0$ 经过所有 $Z(G) = 1$ 的奇环，且不经过任意一个 $Z(G) = 1$ 的偶环，那么 $e_0$ 经过所有奇环，且不经过任意一个偶环

---

下面给出简单的证明：

定义两个环的异或值 $G = G_1 \otimes G_2$ 满足：

$$G = \{ e \, \vert \, (e \in G_1 \land e \not\in G_2) \lor (e \in G_2 \land e \not\in G_1)\}$$

该运算显然满足交换律和结合律。

> 引理：对于任意环 $G$，均可以被唯一分解为 $G = G_1 \otimes G_2 \dots \otimes G_m$，其中 $Z(G) = m$，满足 $\forall 1 \le i \le m$，都有 $Z(G_i) = 1$。
> 
> 证明：考虑数学归纳法，当 $m = 1$ 时显然成立。下面假定当 $m = k$ 时成立，则当 $m = k + 1$ 时，容易发现 $G_{k + 1}$ 和 $G \otimes G_1 \otimes G_2 \dots \otimes G_k$ 显然相等，若不等，则通过 $G_1, G_2, \dots, G_{k + 1}$ 中的返祖边显然不能成环，与环 $G$ 矛盾。（具体的严谨证明笔者也不太会，只能感性理解）

若对于一个环 $G = G_1 \otimes G_2 \dots \otimes G_m$，容易发现原环上的边由所有小环的边之和减去重合的边，即 $|G| = \sum\limits_{i = 1}^{m} |G_i| - \Delta$， 且 $2 \mid \Delta$，那么环 $G$ 的奇偶性只和 $G_1, G_2 \dots G_m$ 中的奇环数目 $x$ 有关，具体的：

- 若 $2 \mid x$，那么环 $G$ 为偶环，若存在一条边 $e_0$ 经过所有的奇环，那么 $e_0$ 必然不经过 $G$。

- 若 $2 \nmid x$，那么环 $G$ 为奇环，若存在一条边 $e_0$ 经过所有的奇环，那么 $e_0$ 必然经过 $G$。

综上所述，原结论显然成立。

---

接下来的处理就很简单，只需要用树上差分统计每条边经过几个奇环和偶环，最后寻找是否存在一条 $e_0 = (u_0, v_0)$ 满足经过所有奇环，且不经过一个偶环的边。

输出方案的话，若原图为二分图，直接染色即可，否则删掉 $e_0$ 后，钦定 $col_{u_0} = 1$ 染色即可，注意多测要清空。

时间复杂度为 $\mathcal{O}(n + m)$，代码如下：

```cpp
#include<bits/stdc++.h>
#define MULT_TEST 1
using namespace std;
inline int read() {
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        w = (w << 1) + (w << 3) + ch - 48;
        ch = getchar();
    }
    return w * f;
}
inline void Solve() {
    int n, m, sum = 0, t = 0, opt = -1;
    n = read(); m = read();
    vector<int> dep(n + 1), ans(n + 1), vis(n + 1), tag(n + 1), h(m + 1);
    vector<vector<pair<int, int>>> e(n + 1), E(n + 1);
    for (int i = 1; i <= m; i++) {
        int u = read(), v = read();
        e[u].push_back({v, i});
        e[v].push_back({u, i});
    }
    function<void(int, int)> DFS1 = [&](int x, int fa) {
        vis[x] = 1;
        dep[x] = dep[fa] + 1;
        for (auto [u, id] : e[x]) {
            if (u == fa) continue;
            if (vis[u]) {
                if (dep[u] > dep[x]) continue;
                if ((dep[x] - dep[u]) & 1) tag[u]++, tag[x]--, h[id]--;
                else sum++, tag[u]--, tag[x]++, h[id]++;
            }
            else {
                E[x].push_back({u, id});
                DFS1(u, x);
            }
        }
    };
    function<void(int, int)> DFS2 = [&](int x, int id2) {
        for (auto [u, id] : E[x]) {
            DFS2(u, id);
            tag[x] += tag[u];
        }
        if (id2 > 0) h[id2] = tag[x];
    };
    bool flag = 1;
    function<void(int, int)> DFS3 = [&](int x, int col) {
        vis[x] = 1;
        ans[x] = col;
        for (auto [u, id] : e[x]) {
            if (vis[u]) {
                if (ans[u] == col) flag = 0;
                continue;
            }
            if (id == opt) continue;
            DFS3(u, col ^ 1);
        }
    };
    DFS3(1, 1);
    if (flag) {
        printf("YES\n");
        for (int i = 1; i <= n; i++) printf("%d", ans[i]);
        puts("");
        return ;
    }
    vis.clear(); vis.resize(n + 1);
    DFS1(1, 1); DFS2(1, -1);
    for (int i = 1; i <= n; i++)
        for (auto [u, id] : e[i]) 
            if (h[id] == sum) opt = id, t = i;
    if (opt == -1) printf("NO\n");
    else {
        vis.clear(); vis.resize(n + 1);
        DFS3(1, 1);
        printf("YES\n");
        for (int i = 1; i <= n; i++) printf("%d", ans[i] ^ (ans[t] == 0));
        puts("");
    }
}
signed main() {
    int T = 1;
#if MULT_TEST
    T = read();
#endif 
    while (T--) Solve();
    return 0;
}
```

---

## 作者：TernaryTree (赞：0)

简单题，细节有点多。

我们拉出来一棵生成树，初始形态是按深度黑白染色，需要额外考虑一些非树边。

显然我们要把非树边分成两类：与两端点在树上的路径构成奇环的，和构成偶环的。

对于前者的条件是，特殊边一定在这个环上。

对于后者的条件是，特殊边一定不在这个环上。

不考虑特殊边在第一类非树边上的情况。那么我们可以每次链加，使用两个树上差分表示，这条边被多少两类非树边覆盖。如果一条边被所有第一类非树边覆盖并且不被第二类非树边覆盖，那么这条边是可以当特殊边的。将这条边深度较大的端点的子树全部反色即可。

有一些特殊情况，比如说只有一条第一类非树边，是这时特殊边可以选这条边。以及没有第一类非树边直接输出初始形态即可。

使用 $\Theta(n)-\Theta(1)$ LCA 可以做到线性。

---

## 作者：Register_int (赞：0)

相当于是删去一条边后进行二分图染色。于是我们可以先找出这条删去后能使原图变成二分图的边。

这部分其实就是 [这题](/problem/CF19E)。一个图是二分图的充要条件是该图没有奇环，也就是说，我们删除的这条边必须满足其经过所有奇环。

显然可以选择考虑不包含其他环的环，感性理解就是，小环被删了，大环也没了。我们将这种环称为 **本原环**。考虑奇环与偶环有公共边的情况，此时两个环拼成的大环也必定为奇环。因此公共边并没有经过所有奇环，所以不能删去。

于是我们得到了两个新的条件：

- 经过所有奇本原环。
- 若经过奇本原环，则不经过所有偶本原环。

对原图建出 dfs 树，则一条返祖边恰好对应一个本原环。树上差分维护即可，复杂度 $O(n+m)$。若没有这种边直接判无解，否则以删去的边为起点进行二分图染色，总时间复杂度 $O(n+m)$。

# AC 代码

```cpp
// LUOGU_RID: 148704735
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

struct node { int v, id; }; vector<node> g[MAXN];

int a[MAXN], b[MAXN], t, dep[MAXN], dfn[MAXN], id, cnt;

void init(int u, int f) {
	dfn[u] = ++id, dep[u] = dep[f] + 1;
	for (node p : g[u]) {
		if (p.v == f) continue;
		if (!dfn[p.v]) a[p.v] = p.id, init(p.v, u), b[u] += b[p.v];
		else if (dfn[p.v] < dfn[u]) {
			if (dep[u] - dep[p.v] & 1) b[u]--, b[p.v]++;
			else cnt++, b[u]++, b[p.v]--, t = p.id;
		}
	}
}

int col[MAXN], p;

inline 
int solve(int n) {
	for (int i = 1; i <= n; i++) if (!dfn[i]) init(i, 0);
	if (!cnt) return p = 1, 2; if (cnt == 1) return p = t, 1;
	for (int i = 1; i <= n; i++) if (a[i] && b[i] == cnt) return p = a[i], 1;
	return 0;
}

void dfs(int u, int f) {
	col[u] = col[f] ^ 1;
	for (node x : g[u]) if (x.id != p && !~col[x.v]) dfs(x.v, u);
}

int T, n, m, opt, ans[MAXN], tot;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%d%d", &n, &m), t = id = cnt = 0;
		for (int i = 1; i <= n; i++) col[i] = -1, a[i] = b[i] = 0;
		for (int i = 1; i <= n; i++) g[i].clear(), dfn[i] = dep[i] = 0;
		for (int i = 1, u, v; i <= m; i++) {
			scanf("%d%d", &u, &v);
			g[u].push_back({ v, i }), g[v].push_back({ u, i });
		}
		opt = solve(n);
		if (!opt) { puts("NO"); continue; } puts("YES");
		if (opt & 1) {
			for (int u = 1; u <= n; u++) {
				for (node x : g[u]) if (x.id == p) { dfs(u, 0); break; }
			}
		}
		p = 0;
		for (int i = 1; i <= n; i++) if (!~col[i]) dfs(i, 0);
		for (int i = 1; i <= n; i++) printf("%d", col[i]); puts("");
	}
}
```

---

## 作者：shuangmu (赞：0)

[广告](https://www.cnblogs.com/frostwood/p/17769151.html)

这道题和[「JOISC 2014 Day3」电压](https://loj.ac/p/2881)非常类似，或者说就是一道题。

题意就是给你一个图，问能否对所有点黑白染色，允许最多一条边的两个顶点都染成黑色。

黑白染色后其实就是一个二分图，那如果有一条边的两个顶点染成黑色，就是说去掉该边后，剩下的图为二分图，注意这里要保证两个顶点的颜色相同，否则无法同时染成黑色。

那么我们考虑线段树分治来做。具体地，对于第 $i$ 条边，我们让它的存在时间为 $[0, i-1]$ 和 $[i+1, m+1]$，表示在第 $i$ 个时刻，只有第 $i$ 条边没有加上，利用可撤销并查集即可维护是否为二分图。而在 $m+1$ 时刻，所有边都被加上，用来判断原图是否为二分图。

时间复杂度 $O(n \log^2 n)$，时限开得很大，可以过。~~但是其他方法可以做到线性，我太菜力~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;

int read() {
	int x = 0; char ch = getchar();
	while(ch<'0' || ch>'9') ch = getchar();
	while(ch>='0'&&ch<='9') x = x*10+(ch-48), ch = getchar();
	return x;
}
struct Edge {
	int u, v;
} e[N];
int T;
int n, m;


int fa[N<<1], siz[N<<1], top;
struct xwx {
	int x, y, del;
}stk[N<<1];

int find(int x) {
	if(x == fa[x]) return x;
	return find(fa[x]);
}

bool found;
bool vis[N<<1];
struct SegmentTree {
	vector<int> tree[N<<2];
	#define ls tr<<1
	#define rs tr<<1 | 1
	void insert(int tr, int L, int R, int lq, int rq, int id) {
		if(lq == L && R == rq) {
			tree[tr].push_back(id);
			return;
		}
		int mid = (L+R)>>1;
		if(lq<=mid) insert(ls, L, mid, lq, min(mid, rq), id);
		if(mid < rq) insert(rs, mid+1, R, max(mid+1, lq), rq, id);
	}
	void init(int tr, int L, int R) {
		tree[tr].clear();
		if(L == R) {
			return;
		}
		int mid = (L+R)>>1;
		init(ls, L, mid);
		init(rs, mid+1, R);
	}
	void solve(int tr, int L, int R, bool flag) {
		int now = top;
		for(int i:tree[tr]) {
			int fx = find(e[i].u), fy = find(e[i].v);
			if(fx == fy) {
				flag = 0;
			} else {
				int f2x = find(e[i].u+n), f2y = find(e[i].v+n);
				if(fx != f2y) {
					if(siz[fx] > siz[f2y]) swap(fx, f2y);
					fa[fx] = f2y;
					siz[f2y]+=siz[fx];
					stk[++top] = (xwx) {fx, f2y, siz[fx]};
				}
				if(fy != f2x) {
					if(siz[fy] > siz[f2x]) swap(fy, f2x);
					fa[fy] = f2x;
					siz[f2x]+=siz[fy];
					stk[++top] = (xwx) {fy, f2x, siz[fy]};
				}
			}
		}
		if(L == R) {
			if(flag) {
				if(L <= m) {
					int tx = find(e[L].u), ty = find(e[L].v);
					if(tx!=ty) return;//如果去掉一条边，必须保证两个顶点同色。
					vis[tx] = 1;//都染成黑色。
					vis[ty] = 1;
				}
				
				found = 1;
				puts("YES");
				
				for(int i = 1; i<=n; ++i) {
					int fi = find(i), f2i = find(i+n);
					if(!vis[fi] && !vis[f2i]) {
						vis[fi] = 1;//如果这个连通块还没有染色，则让初始节点为黑色。
						putchar('1');
					} else {
						putchar('0'+vis[fi]);
					}
				}
				putchar('\n');
				return;
			}
			return;
		}
		int mid = (L+R)>>1;
		solve(ls, L, mid, flag);
		if(found) return;
		solve(rs, mid+1, R, flag);
		if(found) return;
		while(top > now) {
			xwx tmp = stk[top--];
			fa[tmp.x] = tmp.x;
			siz[tmp.y]-=tmp.del;
		}
	}
}seg;

void init() {
	for(int i = 1; i<=n*2; ++i) {
		fa[i] = i;
		siz[i] = 1;
		vis[i] = 0;
	}
	top = 0;
	found = 0;
	seg.init(1, 1, m+1);
}
int main() {
	T = read();
	while(T--) {
		n = read(), m = read();
		init();
		for(int i = 1;i<=m; ++i) {
			e[i] = (Edge) {read(), read()};
			if(i > 1) seg.insert(1, 1, m+1, 1, i-1, i);
			if(i <=m) seg.insert(1, 1, m+1, i+1 ,m+1, i);
		}
		seg.solve(1, 1, m+1, 1);
		if(!found) {
			puts("NO");
		}
	}
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：0)

先建出生成树，黑白染色。考虑符合要求和不符合要求的边。

对于所有建完之后不符合要求的边，如果只有一个直接输出即可。否则考虑如何才能让这条边合法，显然可以让生成树上的这条边端点之间路径上的一条边变得不符合要求。同时，影响的这条边不应当被符合要求的边端点之间的路径包含。树上差分并寻找一个符合要求的树边即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[1000005],tr[1000005];
bool vis[1000005];
int col[1000005],f[1000005][21],dep[1000005],tag[1000005];
vector<pair<int,int>> bd,gd;
void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=1;i<=20;i++) f[now][i]=f[f[now][i-1]][i-1];
	col[now]=col[fa]^1;
	vis[now]=1;
	if(fa) tr[now].push_back(fa),tr[fa].push_back(now); 
	for(auto v:vc[now]){
		if(!vis[v]){
			dfs(v,now);
		}
		else if(v!=fa){
			if(v>now) continue;
			if(col[now]==col[v]) bd.push_back(make_pair(v,now));
			else gd.push_back(make_pair(v,now));
		}
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=20;i>=0;i--) if(dep[f[u][i]]>=dep[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=20;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
void dfs2(int now,int fa){
	for(auto v:tr[now]){
		if(v==fa) continue;
		dfs2(v,now);
		tag[now]+=tag[v];
	}
}
void dfs3(int now,int fa){
	col[now]^=1;
	for(auto v:tr[now]){
		if(v==fa) continue;
		dfs3(v,now);
	}
}
signed main(){
	int t; cin>>t;
	while(t--){
		int n,m; cin>>n>>m;
		bd.clear();
		gd.clear();
		for(int i=1;i<=n;i++) vc[i].clear(),tr[i].clear(),vis[i]=0,col[i]=0,dep[i]=0,tag[i]=0;
		for(int i=1;i<=m;i++){
			int u,v; cin>>u>>v;
			vc[u].push_back(v);
			vc[v].push_back(u);
		}
		dfs(1,0);
//		cout<<bd.size()<<" ";
		if(bd.size()<=1){
			if(bd.size()) if(col[bd[0].first]==0) for(int i=1;i<=n;i++) col[i]^=1;
			cout<<"YES\n";
			for(int i=1;i<=n;i++) cout<<col[i];
			cout<<"\n";
			continue;
		}
		for(auto v:gd){
//			cout<<v.first<<" "<<v.second<<"\n"; 
			tag[lca(v.first,v.second)]+=2;
			tag[v.first]--;
			tag[v.second]--;
		}
		for(auto v:bd){
//			cout<<v.first<<" "<<v.second<<"\n"; 
			tag[lca(v.first,v.second)]-=2;
			tag[v.first]++;
			tag[v.second]++;
		}
		dfs2(1,0);
		int ok=0;
		for(int i=1;i<=n;i++){
			if(i!=1&&tag[i]==bd.size()){
				ok=i;
				break;
			}
		}
		if(!ok){
			cout<<"NO\n";
			continue;
		}
		dfs3(ok,f[ok][0]);
		if(col[ok]==0) for(int i=1;i<=n;i++) col[i]^=1;
		cout<<"YES\n";
		for(int i=1;i<=n;i++) cout<<col[i];
		cout<<"\n";
	} 
	return 0;
}

```

---

