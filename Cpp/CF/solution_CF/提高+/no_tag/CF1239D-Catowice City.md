# Catowice City

## 题目描述

In the Catowice city next weekend the cat contest will be held. However, the jury members and the contestants haven't been selected yet. There are $ n $ residents and $ n $ cats in the Catowice, and each resident has exactly one cat living in his house. The residents and cats are numbered with integers from $ 1 $ to $ n $ , where the $ i $ -th cat is living in the house of $ i $ -th resident.

Each Catowice resident is in friendship with several cats, including the one living in his house. In order to conduct a contest, at least one jury member is needed and at least one cat contestant is needed. Of course, every jury member should know none of the contestants. For the contest to be successful, it's also needed that the number of jury members plus the number of contestants is equal to $ n $ .

Please help Catowice residents to select the jury and the contestants for the upcoming competition, or determine that it's impossible to do.

## 说明/提示

In the first test case, we can select the first and the third resident as a jury. Both of them are not acquaintances with a second cat, so we can select it as a contestant.

In the second test case, we can select the second resident as a jury. He is not an acquaintances with a first and a third cat, so they can be selected as contestants.

In the third test case, the only resident is acquaintances with the only cat, so they can't be in the contest together. So it's not possible to make a contest with at least one jury and at least one cat.

In the fourth test case, each resident is acquaintances with every cat, so it's again not possible to make a contest with at least one jury and at least one cat.

## 样例 #1

### 输入

```
4
3 4
1 1
2 2
3 3
1 3

3 7
1 1
1 2
1 3
2 2
3 1
3 2
3 3

1 1
1 1

2 4
1 1
1 2
2 1
2 2
```

### 输出

```
Yes
2 1
1 3 
2 
Yes
1 2
2 
1 3 
No
No
```

# 题解

## 作者：yuzhechuan (赞：18)

### 首先要说的：

其实本题在答案的统计上并没有另两篇题解讲的那么麻烦

如果你真正搞懂了tarjan，你会明白如果一个强连通分量有出边，由于它dfs的性质，一定会继续向下遍历，直到找到一个没有出度的强连通分量

**因此，第一个被找到的强联通分量一定是没有出度的！**

这样其余两篇题解的做法在过程上还可以被大幅简化

---

### 题解

首先，一个很简单的问题：为什么n个不可以都是猫呢？

因为必须至少有一个人

那么我们就必须把这个人放到无法产生任何影响的地方去

即一个人群（或仅一个人）

这个人群必须满足不会再对后续产生影响（因为连猫不合法，连人不如换个部分做人群）

即无出度

同时人群中也要保持强联通，因为如果有人不强联通，他就可以被分离出看成猫

因此问题转化为在一个有向图中找一个没有出度的强连通分量

在这个没有出度的强联通分量里的都是人，否则是猫

而我之前又说过**第一个被找到的强联通分量一定是没有出度的**，因此编号为1的强连通分量就是我们要找的

---

另外，显然的，如果只有一个强连通分量就是不合法的

---

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}
const int N=1e6+5;
int h[N],st[N],lim,dfn[N],low[N],cnt,en,scc[N],sn,n,m,t,sz[N];
bool v[N];
struct edge{int n,v;}e[N];
inline void add(int x,int y){e[++en]=(edge){h[x],y};h[x]=en;}
void tarjan(int x){ //tarjan模板
	v[x]=1;
	st[++lim]=x;
	dfn[x]=low[x]=++cnt;
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int top;
		sn++;
		for(;;){
			top=st[lim--];
			v[top]=0;
			scc[top]=sn;
			sz[sn]++; //sz[]是强连通分量的大小
			if(top==x) break;
		}
	}
}
void doit(){
	read(n);read(m);
	sn=cnt=en=lim=0;
	for(int i=1;i<=n;i++) h[i]=sz[i]=dfn[i]=0;
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		if(x==y) continue; //自己和自己的猫可忽略
		add(x,y);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	if(sn==1){ //只有一个强连通分量，不合法
		puts("No");
		return ;
	}
	printf("Yes\n%d %d\n",sz[1],n-sz[1]); //sz[1]是人的个数，减一减得到猫数
	for(int i=1;i<=n;i++) if(scc[i]==1) write(i),putchar(' ');puts(""); //第一个的都是人
	for(int i=1;i<=n;i++) if(scc[i]!=1) write(i),putchar(' ');puts(""); //否则是猫
}
signed main(){
	read(t);
	while(t--) doit();
}
```

---

**(ps.本题清零初始化用memset会T在第三个点，要改用for)**

---

## 作者：81179332_ (赞：8)

这是一个二分图，由于第 $i$ 只猫和第 $i$ 个人不能都选，所以我们可以将第 $i$ 个人和第 $i$ 只猫缩成一个点

对于一条从 $u$ 连向 $v$ 的边，表示如果 $u$ 选了人，则 $v$ 不能选猫

容易发现，对于一个强连通分量中的点，要么全选人，要么全选猫

对于出度为 $0$ 的强连通分量（即编号为 $1$），由于没有出边，它不可能影响任何点，所以我们不妨令其选人，其它所有点都选猫（选猫也不会影响其他点）

如果只有一个强连通分量，则无解

```cpp
//timeuse:20min
const int N = 1000010,M = N;
int n,m;EE(1);
int dfn[N],low[N],idx;
int st[N],top,col[N],num,siz[N];
bool vis[N];
void init()
{
	n = read(),m = read();
	for(int i = 1;i <= n;i++) head[i] = dfn[i] = low[i] = siz[i] = 0;
	ecnt = 1,num = idx = 0;
}
void Tarjan(int u)
{
	dfn[u] = low[u] = ++idx,vis[u] = 1,st[++top] = u;
	for(int i = head[u];i;i = e[i].nxt)
	{
		int v = e[i].to;
		if(!dfn[v]) Tarjan(v),low[u] = min(low[u],low[v]);
		else if(vis[v]) low[u] = min(low[u],dfn[v]);
	}
	if(dfn[u] == low[u])
	{
		num++;
		int v = st[top--];
		col[v] = num,vis[v] = 0,siz[num]++;
		while(st[top + 1] != u)
		{
			int v = st[top--];
			col[v] = num,vis[v] = 0,siz[num]++;
		}
	}
}
void solve()
{
	for(int i = 1;i <= m;i++)
	{
		int x = read(),y = read();
		if(x != y) add(x,y);
	}
	for(int i = 1;i <= n;i++) if(!dfn[i]) Tarjan(i);
	if(num == 1) { puts("No");return; }
	puts("Yes");pprint(siz[1]),fprint(n - siz[1]);
	for(int i = 1;i <= n;i++) if(col[i] == 1) pprint(i);putchar('\n');
	for(int i = 1;i <= n;i++) if(col[i] != 1) pprint(i);putchar('\n');
}
int main()
{
	int T = read();
	while(T--) init(),solve();
}
```

---

## 作者：SIGSEGV (赞：3)

大致题意：有$n$个人和$n$只猫，每个人都认识编号与他相同的猫和另外一些猫，现在需要从人和猫中选出共$n$个，使得其中既有人，也有猫，并且所有选出的人都不认识任何选出的猫。

思路：

首先，同一个编号的人和猫，必须选且仅选一个。为什么？感性证明一下（可能有误）：假设选了$r$个人，$n-r$个猫，如果选中的人和猫的编号的集合有交集，那么这种方案肯定不合法。而所有人和所有猫的集合大小都是$n$且人和猫的编号一一对应，所以没有被选中的人，他对应的猫一定会被选中。

简而言之，选出的人的集合与选出的猫的集合互为补集。

那么考虑人认识猫的情况。假设人$R$认识猫$C$,套用2-SAT的思想，那么选了人$R$就不能选猫$C$，则根据上面的结论，一旦选了$R$就必须选编号为$C$的人。

因此，对于所有的关系，从$R$向编号为$C$的人连一条有向边，缩点后如果所有点在一个强连通分量里则无解，否则选择一个**出度为0**的强连通分量即可。

代码是考场上写的，稍微有点丑:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
int n,m;
vector<int> e[N];
int dfn[N],scc_idx[N],low[N],tim,idx,sz[N],deg[N];
bool vis[N];stack<int> stk;
void tarjan(int pos) //Tarjan
{
    dfn[pos] = low[pos] = ++tim;vis[pos] = 1;stk.push(pos);
    for (auto &i : e[pos])
        if (!dfn[i]) tarjan(i),low[pos] = min(low[pos],low[i]);
        else if (vis[i]) low[pos] = min(low[pos],dfn[i]);
    if (dfn[pos] == low[pos])
    {
        ++idx;
        while (!stk.empty())
        {
            int nd = stk.top();stk.pop();
            vis[nd] = 0;scc_idx[nd] = idx;++sz[idx];
            if (nd == pos) break;
        }
    }
}
int main ()
{
    ios::sync_with_stdio(false);
    int T;cin >> T;
    while (T--)
    {
        cin >> n >> m;
        tim = idx = 0;
        int t1,t2;
        for (int i = 1;i <= n;i++) e[i].clear();
        for (int i = 1;i <= m;i++)
        {
            cin >> t1 >> t2;
            if (t1 != t2) e[t1].push_back(t2);//连边
        }
        for (int i = 1;i <= n;i++)
            scc_idx[i] = sz[i] = dfn[i] = low[i] = deg[i] = vis[i] = 0;//记得多组数据的题的初始化
        for (int i = 1;i <= n;i++)
            if (!dfn[i]) tarjan(i);
        for (int i = 1;i <= n;i++)
            for (auto &j : e[i])
                if (scc_idx[i] != scc_idx[j]) ++deg[scc_idx[i]]; //计算出度
        if (sz[scc_idx[1]] == n) { puts("NO");continue; }//无解情况
        bool fl = 0;
        for (int i = 1;i <= idx;i++)
            if (!deg[i] && sz[i]) //有解
            {
                puts("YES");fl = 1;
                vector<int> ans[2];
                for (int j = 1;j <= n;j++)
                    ans[scc_idx[j] == i].push_back(j);
                printf("%d %d\n",ans[1].size(),ans[0].size());
                for (auto &i : ans[1]) printf("%d ",i);
                puts("");
                for (auto &i : ans[0]) printf("%d ",i);
                puts("");
                break;
            }
        if (!fl) puts("NO");
    }
    return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

重点观察：对于编号 $i$，要么选第 $i$ 人，要么选第 $i$ 猫；不能一个都不选，不能两个都选。

证明：不能两个同时选是显然的。如果两个都不选会发生什么问题？后面就只剩下 $n-1$ 对（人，猫），其中必须选 $n$ 个东西；由于鸽子定理一个对必须存在人和猫都选，这样不合法。

现在，可以构造一个 $n$ 个节点的有向图。我们想把这些节点染色；第 $i$ 个节点染了 0 号色表示选了人，染了 1 号色表示选了猫。

根据题目要求，一个节点 $u$ 的颜色会影响节点 $v$ 可以染什么颜色当且仅当人 $u$ 认识猫 $v$。在这个时候就在有向图里面加入一个 $u$ 到 $v$ 的边。

显然如果一个节点染了 $0$（选人），它相邻的节点必须染 $0$，也就是它可以到达的所有节点都需要染 $0$。

考虑这个问题怎么在无环图里面做。如果图仅仅有一个节点，则不可能。（注意题目要求人的集合和猫的集合非空！）否则，选择任意一个没有进入的边的一个节点，这个节点染 $1$；所有别的节点染 $0$。

根据套路把有向图退化成 DAG；用 tarjan 缩强联通分量。这个可以因为在一个强联通分量里面明显**可以**把所有节点染一样颜色：如果染 $0$ 则全染 $0$，如果染 $1$ 全染 $1$ 一点问题都没有。如果缩完的图仅仅有一个联通分量，则没有解；否则选一个没有入边的强联通分量全染 $1$（选猫），剩下节点全染 $0$（选人）。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
#define endl '\n'
//#define int ll
const int MOD = 1000000007;

namespace Tarjan {
	const int maxn = 1000006;
	struct graph {
		int n; vector<int> inc; vector<int> e[maxn];
		void ae(int u, int v) { e[u].pb(v); }
		void clr(int _n) {
			inc.clear();
			rep(i,_n+2) e[i].clear();
			n = _n;
		}
	};
    int tot, color, l[maxn], t[maxn], findSCC[maxn];
    bool r[maxn]; stack<int> S; graph pre, shr;
    
    void DFS(int u) {
        l[u] = t[u] = ++tot; S.push(u); r[u] = true;
        for(int& v:pre.e[u]) {
            if(r[v] && t[v]) l[u] = min(l[u], t[v]);
            if(!r[v] && !t[v]) { DFS(v); l[u] = min(l[u], l[v]); }
        }
        if(l[u] != t[u]) return;
        color++;
        while(1) {
            int c = S.top(); S.pop(); r[c] = false;
            findSCC[c] = color; if(c == u) return;
        }
    }
    void shrinkSCC() {
    	rep(i, pre.n+2) { l[i] = t[i] = r[i] = 0; }
    	color = 0; tot = 0;
        tot = color = 0; rep1(u, pre.n) { if(t[u]) { continue; } DFS(u); }
        shr.clr(color+1);
        shr.n = color; shr.inc.resize(color+1);
        rep1(u, pre.n) {
            for(int& v:pre.e[u]) if(findSCC[u] != findSCC[v]) {
            	shr.ae(findSCC[u], findSCC[v]);
            	shr.inc[findSCC[v]]++;
            }
        }
    }
}

// using namespace Tarjan;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
    	int n, m; cin >> n >> m;
    	Tarjan::pre.clr(n);
    	rep(i, m) {
    		int u, v; cin >> u >> v;
    		if(u == v) continue;
    		Tarjan::pre.ae(u, v);
    	}
    	Tarjan::shrinkSCC();
    	if(Tarjan::color == 1) cout << "No" << endl;
    	else {
    		cout << "Yes" << endl;
    		vector<int> a, b;
    		int start = 0;
    		rep1(i, Tarjan::color) if(!Tarjan::shr.inc[i]) start = i;
    		rep1(i, n) {
    			if(Tarjan::findSCC[i] == start) a.pb(i);
    			else b.pb(i);
    		}
    		swap(a, b);
    		cout << a.size() << ' ' << b.size() << endl;
    		for(int& k:a) cout << k << ' ';
    		cout << endl; for(int& k:b) cout << k << ' ';
    		cout << endl;
    	}
    }
}

```

---

## 作者：George1123 (赞：2)

[$\Huge\color{#50a1a0}{\texttt{My Cnblogs}}$](https://www.cnblogs.com/Wendigo/p/12916838.html)

---
> [CF1239D Catowice City](https://www.luogu.com.cn/problem/CF1239D)

> 有 $n$ 个人和 $n$ 只猫。有 $m$ 对人猫友谊，即第 $u_i$ 个人认识第 $v_i$ 只猫，**保证第 $i$ 个人和第 $i$ 只猫认识**。求 $j$ 个人和 $p$ 只猫使 $j+p=n(1\le j,p<n)$，并且这些人和猫互不认识。$t$ 组测试数据。

> 数据范围： $1\le n\le m\le 10^6$，$1\le \sum n,\sum m\le 10^6$。

---
首先这是个二分图，人一块，猫一块。

将第 $i$ 个人和第 $i$ 只猫合并成一点，因为他们不能都选。

从 $u_i$ 向 $v_i$ 连一条有向边，表示**如果第 $u_i$ 点选人，$v_i$ 点也必须选人**。

如果出现环，则这些点**要么全选人要么全选猫**，不妨令选人。

所以 $\texttt{Tarjan}$ 把**强联通分量**分出来。

如果只有**一个**强联通分量，则必须全选人，与 $(1\le j,p<n)$ 不符，输出 $\texttt{No}$。

否则选出**拓扑序最后的强联通分量全选人，其他全选猫**。

> $\texttt{Tarjan}$ 有个性质：编号为 $1$ 的强联通分量拓扑序最后。

**时间复杂度 $\Theta(n+m)$，空间复杂度 $\Theta(n+m)$。**

---
- **代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x(a) a.first
#define y(a) a.second
#define b(a) a.begin()
#define e(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e6;
int n,m;
vector<int> e[N+7];

//Tarjan
int ic,in[N+7],low[N+7],dfn[N+7],sc,st[N+7],cc,co[N+7],sm[N+7];
void Tarjan(int u){
	low[u]=dfn[u]=++ic,in[u]=1,st[++sc]=u;
	for(int v:e[u])
		if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u]) for(int v=0,t=++cc;v!=u;) v=st[sc--],co[v]=t,in[v]=0,sm[t]++;
}

//KonnyWen
void KonnyWen(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=m;i++){
		int u,v; scanf("%d%d",&u,&v);
		if(u!=v) e[u].pb(v);
	}
	fill(dfn+1,dfn+n+1,0),fill(sm+1,sm+n+1,0),ic=sc=cc=0;
	for(int i=1;i<=n;i++)if(!dfn[i]) Tarjan(i);
	if(cc==1) return void(puts("No"));
	printf("Yes\n%d %d\n",sm[1],n-sm[1]);
	for(int i=1;i<=n;i++)if(co[i]==1) printf("%d ",i); puts("");
	for(int i=1;i<=n;i++)if(co[i]!=1) printf("%d ",i); puts("");
}

//Main
int main(){
	int t; scanf("%d",&t);
	for(int ti=1;ti<=t;ti++) KonnyWen();
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：xukuan (赞：1)

**算法**

tarjan/2-SAT

**建模**

用人与猫的关系建模。第$u$个人认识第$v$只猫$\rightarrow$连一条$u \rightarrow v$的单向边.

**一个重要的结论**

信息：选了人之后就不能选与他相连的猫

首先我们来证明一个结论：假设几个点在同一个环内，要么都选人，要么都选猫。

这里可以参考2-SAT算法的思想

选了人$i\rightarrow$

不能选猫$j \rightarrow$

选人$j \rightarrow$

$\dots \dots$

因为这个图是一个环，所以总是可以传递回来的

所以结论成立

**统计答案**

这题的统计答案并不烦。

首先，tarjan找到的第一个环是没有出边的

这样，我们可以让第一个环里的选人，别的选猫

PS：如果只有一个环就输出NO

**代码**

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=1000010;
ll n,m,deep,color,dfn[N],low[N],v[N],colour[N],size[N],indegree[N];
ll ver[N<<1],Next[N<<1],head[N],tot;
stack<ll> st;
vector<ll> ans[2];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

inline void addEdge(ll x,ll y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(ll x){
	dfn[x]=low[x]=++deep;
	v[x]=1; st.push(x);
	for(ll i=head[x]; i; i=Next[i]){
		ll y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		colour[x]=++color;
		v[x]=0;
		while(st.top()!=x){
			colour[st.top()]=color;
			v[st.top()]=0;
			st.pop();
			size[color]++;
		}
		st.pop(); size[color]++;
	}
}

inline void clean(){
	for(ll i=1; i<=n; i++) head[i]=0;
	for(ll i=1; i<=tot; i++) ver[i]=Next[i]=0;
	while(!st.empty()) st.pop();
	for(ll i=1; i<=n; i++) dfn[i]=low[i]=v[i]=colour[i]=size[i]=0;
	for(ll i=1; i<=color; i++) indegree[i]=0;
	tot=deep=color=0;
	ans[0].clear(); ans[1].clear();
}

int main(){
	for(ll T=read(); T; T--){
		clean();
		n=read(); m=read();
		while(m--){
			ll x=read(),y=read();
			addEdge(x,y);
		}
		for(ll i=1; i<=n; i++){
			if(!dfn[i]) tarjan(i);
		}
		for(ll i=1; i<=n; i++){
			for(ll j=head[i]; j; j=Next[j]){
				ll x=ver[j];
				if(colour[i]!=colour[x]) indegree[colour[x]]++;
			}
		}
		if(size[colour[1]]==n){
			printf("NO\n");
			continue;
		}
		bool flag=0;
		for(ll i=1; i<=color; i++){
			if(!indegree[i]&&size[i]){
				printf("YES\n"); flag=1;
				for(ll j=1; j<=n; j++) ans[colour[j]==i].push_back(j);
				write(ans[0].size()); putchar(' ');
				write(ans[1].size()); putchar('\n');
				for(ll i=0; i<(ll)ans[0].size(); i++){
					write(ans[0][i]); putchar(' ');
				}
				putchar('\n');
				for(ll i=0; i<(ll)ans[1].size(); i++){
					write(ans[1][i]); putchar(' ');
				}
				putchar('\n');
				break;	
			}
		}
		if(!flag) printf("NO\n");
	}
	return 0;
}
```

---

## 作者：mraymes (赞：1)

## 题意
有 $n$ 个人, 每个人都有一只猫. 有 $m$ 条人猫关系, 表示某一个人认识某一只猫. 要从中选出至少一个人和一只猫, 总和为 $n$, 使得没有一个人认识任何选出的猫.

## 建图
可以将 $m$ 条关系转换成图上的边. 第 $u$ 个人认识第 $v$ 只猫 $\rightarrow$ 连一条 $u \rightarrow v$ 的有向边.  
如果图中出现了环 (强连通分量), 那么该环中必须全部选人或者全部选猫, 不然就会出现人指向猫的边, 不满足题意.

如果能找到符合题意的答案, 那么必须有一个强连通分量的入度为 0. 该强连通分量中所有的点都选猫, 因为入度为 0 所以无需担心强连通分量外的点连向里面从而导致最终出现人指向猫的边.

强联通分量可以用 Tarjan 求出来, 缩点后再求出入度.  
具体见代码.

```cpp
#include <bits/stdc++.h>

using namespace std;

int ntest;
int n, m;
vector<int> adj[1000001];
int disc[1000001], low[1000001];
int cnt_v = 0;
stack<int> stk;
bool is_in_stack[1000001];
int scc[1000001], sz[1000001];
int cnt_scc = 0;
int in_deg[1000001];
vector<int> ans[2];

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

void tarjan(int u) { // Tarjan 算法
    disc[u] = low[u] = ++cnt_v;
    stk.push(u);
    is_in_stack[u] = true;

    for (auto v : adj[u]) {
        if (!disc[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (is_in_stack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (disc[u] == low[u]) { // 找到了一个强连通分量
        cnt_scc++;
        int x = 0;
        while (x ^ u) {
            x = stk.top();
            stk.pop();
            is_in_stack[x] = false;
            scc[x] = cnt_scc;
            sz[cnt_scc]++;
        }
    }
}

int main() {
    ntest = read<int>();

    while (ntest--) {
        n = read<int>(), m = read<int>();

        // 初始化
        cnt_v = cnt_scc = 0;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            disc[i] = 0, low[i] = 0;
            is_in_stack[i] = false;
            scc[i] = 0, sz[i] = 0;
            in_deg[i] = 0;
        }
        while (!stk.empty()) {
            stk.pop();
        }
        ans[0].clear(), ans[1].clear();

        for (int i = 1; i <= m; i++) {
            int u = read<int>(), v = read<int>();
            if (u ^ v) { // 去掉自环
                adj[u].push_back(v);
            }
        }

        for (int i = 1; i <= n; i++) {
            if (!disc[i]) {
                tarjan(i);
            }
        }

        // 缩点
        for (int u = 1; u <= n; u++) {
            for (auto v : adj[u]) {
                if (scc[u] ^ scc[v]) {
                    // 求入度
                    ++in_deg[scc[v]];
                }
            }
        }

        // 如果整个图就是一个强连通分量则退出
        if (sz[scc[1]] == n) {
            puts("NO");
            continue;
        }

        for (int i = 1; i <= cnt_scc; i++) {
            // 找到符合条件的非空强连通分量
            if (!in_deg[i] && sz[i]) {
                puts("YES");

                // 属于该强连通分量的全选猫 (1), 否则选人 (0)
                for (int j = 1; j <= n; j++) {
                    ans[scc[j] == i].push_back(j);
                }

                printf("%d %d\n", ans[0].size(), ans[1].size());
                for (auto x : ans[0]) {
                    printf("%d ", x);
                }
                puts("");
                for (auto x : ans[1]) {
                    printf("%d ", x);
                }
                puts("");

                // 跳到 puts("NO") 语句后面
                goto ans_found;
            }
        }
        puts("NO");
    ans_found:;
    }

    return 0;
}
```


---

