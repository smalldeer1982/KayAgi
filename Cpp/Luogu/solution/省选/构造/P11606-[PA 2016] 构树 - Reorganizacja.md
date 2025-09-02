# [PA 2016] 构树 / Reorganizacja

## 题目背景

译自 [Potyczki Algorytmiczne 2016](https://sio2.mimuw.edu.pl/c/pa-2016-1/p/) R2 Reorganizacja [A] (REO)。$\texttt{1s,256M}$。


## 题目描述

构造一棵 $n$ 个节点的有根树，满足 $m$ 条限制，形如「$x$ 必须是 $y$ 的祖先」或者「$x$ 必须不是 $y$ 的祖先」。


## 说明/提示



- $1\le n\le 10^3$；
- $0\le m\le \min(n(n-1), 10^4)$；
- $1\le x,y\le n$，$x\neq y$。

保证不会重复给出同一条信息。

## 样例 #1

### 输入

```
4 4
4 1 T
4 2 T
3 2 N
4 3 N```

### 输出

```
0
1
1
2```

## 样例 #2

### 输入

```
2 2
1 2 N
2 1 N```

### 输出

```
NIE```

# 题解

## 作者：Purslane (赞：2)

# Solution

赛时把这道题想复杂了。。。

设函数 $\text{solve}(S)$ 表示，考虑所有两个点都在 $S$ 中的限制，构造出一棵合法的树。

显然，我们要确定根。显然它会成为 $S$ 中所有节点的祖先，如果它被限制有一个祖先或者被限制不能是其他人的祖先，就倒闭了。如果我们确定根，把祖孙关系弱连通的点划分为同一个集合，继续做。

这样的点可能有很多，是不是随便选一个就行了呢？也就是很容易让人担心，每一步随便选是否有影响。

我们建立一张图，只保存限制 $1$。最后一步肯定存在一个 $S$，使得其导出子图所有入度为 $0$ 的点，都会被限制 $2$ 干趴下。

发现 $S$ 中任何一个节点都不可能被选做根。那么 $S$ 就永远不会被分为两个集合。所以如果出现了无解的情况，不必自责你选错点了——因为无论如何都是无解。

暴力做就行了，复杂度 $O(nm)$。

写的比较丑陋，多了个 $\log$，但是速度还行。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,m,fa[MAXN],flg[MAXN],res[MAXN];
struct Edge {int x,y,tp;};
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void merge(int u,int v) {return fa[find(v)]=find(u),void();}
int solve(vector<int> S,vector<Edge> lim) {
	if(S.size()==1) return S[0];
	for(auto id:S) fa[id]=id,flg[id]=0;
	for(auto e:lim) if(e.tp==0) flg[e.x]=1; else flg[e.y]=1;
	int rt=0;
	for(auto id:S) if(!flg[id]) rt=id;
	if(!rt) {cout<<"NIE";exit(0);}
	for(auto e:lim) if(e.tp==0&&e.x!=rt&&e.y!=rt) merge(e.x,e.y);
	map<int,vector<int>> mp;
	map<int,vector<Edge>> ed;
	for(auto id:S) if(id!=rt) mp[find(id)].push_back(id);
	for(auto e:lim) if(find(e.x)==find(e.y)) ed[find(e.x)].push_back(e);
	for(auto pr:mp) {
		auto ss=pr.second;
		int id=pr.first;	
		res[solve(ss,ed[id])]=rt;
	}
	return rt;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	vector<Edge> lim;
	ffor(i,1,m) {
		int x,y;
		char c;
		cin>>x>>y>>c;
		lim.push_back({x,y,c=='N'});	
	}
	vector<int> al;
	ffor(i,1,n) al.push_back(i);
	int rt=solve(al,lim);
	ffor(i,1,n) cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：happybob (赞：1)

题意：

给定 $n$ 和 $m$ 条限制，每条限制给定限制类型以及参数 $u,v$，要求 $u$ 是 $v$ 的祖先或者 $u$ 不是 $v$ 的祖先，试构造一棵 $n$ 个点有根树符合此要求，你可以自行确定根节点的位置。

$1 \leq n \leq 10^3$，$0 \leq m \leq 10^4$。

解法：

首先我们可以确定每个点是否可以成为根。如果所有点都不能称为根显然无解，否则随便选一个点为根均可。

我们称限制类型 $1$ 是 $u$ 是 $v$ 的祖先，限制类型 $2$ 是 $u$ 不为 $v$ 祖先。首先对类型 $1$，连边 $u \rightarrow v$，则有解必要条件是这个图为一个 DAG，我们考虑对着这个图构造。

假设我们确定了树根为 $r$，我们预先连边 $r \rightarrow i(i \neq r)$，然后递归构造，每次从当前根节点所在的弱连通块中选一个入度为 $0$ 的点，如果有多个入度为 $0$ 的点我们应该选择一个不存在不满足 $2$ 类型的限制的点。若不存在这样的点显然无解，否则找到这个点后挂在当前根的儿子中，将当前根删去并递归构造即可。

时间复杂度 $O(nm)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <array>
using namespace std;

constexpr int N = 1e3 + 5;

array<vector<int>, N> G1, G2, G;
int n, m;
array<int, N> fa;
array<bool, N> del;
array<int, N> bel, in;
int idx;

void dfs(int u)
{
	if (bel[u] || del[u]) return;
	bel[u] = idx;
	for (auto& j : G[u])
	{
		dfs(j);
	}
}
array<int, N> cnt;
array<array<bool, N>, N> vs;
array<bool, N> vv;

void solve(int u, int f)
{
	if (del[u]) return;
	idx = 0;
	for (int i = 1; i <= n; i++)
	{
		bel[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		if (bel[i]) continue;
		idx++;
		dfs(i);
	}
	int c = count(bel.begin() + 1, bel.begin() + n + 1, bel[u]);
	if (c == 1)
	{
		fa[u] = f;
		del[u] = 1;
		return;
	}
	else
	{
		vv.fill(0);
		vector<int> pos;
		for (int i = 1; i <= n; i++)
		{
			if (bel[i] == bel[u] && in[i] == 0) pos.emplace_back(i);
			if (bel[i] == bel[u])
			{
				for (auto& x : G2[i]) vv[x] = 1;
			}
		}
		if (pos.size())
		{
			cnt.fill(0);
			for (auto& i : pos)
			{
				for (auto& j : G2[i]) cnt[j]++;
			}
			int retpos = -1;
			for (auto& i : pos)
			{
				if (!cnt[i] && !vv[i])
				{
					retpos = i;
					break;
				}
			}
			u = retpos;
			if (retpos == -1)
			{
				cout << "NIE\n";
				exit(0);
			}
			else
			{
				del[u] = 1;
				for (auto& j : G1[u]) in[j]--;
				fa[u] = f;
				for (auto& j : G1[u])
				{
					solve(j, u);
				}
			}
		}
		else
		{
			cout << "NIE\n";
			exit(0);
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		char op;
		cin >> x >> y >> op;
		if (op == 'T')
		{
			G1[y].emplace_back(x);
			G[x].emplace_back(y), G[y].emplace_back(x);
			in[x]++;
		}
		else
		{
			G2[x].emplace_back(y);
			vs[x][y] = 1;
		}
	}
	int rt = -1;
	for (int i = 1; i <= n; i++)
	{
		bool tag = 1;
		for (int j = 1; j <= n; j++)
		{
			for (auto& k : G2[j]) tag &= (k != i);
			for (auto& k : G1[j]) tag &= (k != i);
			if (!tag) break;
		}
		if (tag)
		{
			rt = i;
			break;
		}
	}
	if (rt == -1) cout << "NIE\n";
	else
	{
		for (int i = 1; i <= n; i++)
		{
			if (i == rt || find(G[rt].begin(), G[rt].end(), i) != G[rt].end()) continue;
			G1[rt].emplace_back(i);
			G[rt].emplace_back(i);
			G[i].emplace_back(rt);
			in[i]++;
		}
		solve(rt, 0);
		for (int i = 1; i <= n; i++)
		{
			int j = fa[i];
			while (j)
			{
				if (vs[i][j])
				{
					cout << "NIE\n";
					exit(0);
				}
				j = fa[j];
			}
		}
		for (int i = 1; i <= n; i++) cout << fa[i] << "\n";
	}
	return 0;
}
```

---

## 作者：Register_int (赞：1)

先试着把根找出来。显然根要满足：

- 他没有被钦定任何一个祖先。
- 他没有被钦定不是任何一个点的祖先。

没有就直接 NIE 了。可以感性理解一下，这俩都没有就说明他放根一定是不劣的，随便挑一个就好。

接下来尝试往根上挂点。同样的，在满足 T 条件的前提下，挂的深度也是越浅越好，这样可以避开尽可能多的 N 条件。可以直接处理出来每个点最浅挂在哪个点上。考虑什么点能挂上去。用并查集维护 **如果 $u$ 被挂在 $x$ 的子树下，那么 $v$ 也必须被挂在 $x$ 的子树下** 的关系，那么只要这个点在其所在的子树内满足：

- 他没有被钦定任何一个祖先。
- 他没有被钦定不是任何一个点的祖先。

那么他就能挂，并且一定不劣。之后将和他属于同一个并查集的点全扔到到这个点下面去即可。没得挂也直接 NIE 掉。

每次一定能挂一个点，判断的复杂度是 $O(\alpha(n)(n+m))$，综复杂度 $O(n\alpha(n)(n+m))$，可以通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e4 + 10;

int n, m, k, x[MAXN], y[MAXN]; char opt[MAXN][2];

int p[MAXN], fa[MAXN], bel[MAXN]; bool ban[MAXN];

inline int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) fa[i] = -1;
	for (int i = 1; i <= m; i++) scanf("%d%d%s", &x[i], &y[i], opt[i]);
	for (int i = 1; i <= m; i++) {
		if (*opt[i] == 'T') ban[x[i]] = 1;
		else ban[y[i]] = 1;
	}
	for (int i = 1; i <= n; i++) if (!ban[i]) { k = i; break; }
	if (!k) return puts("NIE"), 0; fa[k] = 0;
	for (int i = 1; i <= n; i++) bel[i] = k;
	for (int _ = 1; _ < n; _++) {
		for (int i = 1; i <= n; i++) ban[i] = ~fa[i], p[i] = i;
		for (int i = 1; i <= m; i++) {
			if (*opt[i] == 'T' && !~fa[x[i]] && !~fa[y[i]]) p[find(x[i])] = find(y[i]);
		}
		for (int i = 1; i <= m; i++) {
			if (*opt[i] == 'T' && !~fa[y[i]]) ban[x[i]] = 1;
			if (*opt[i] == 'N' && find(x[i]) == find(y[i])) ban[y[i]] = 1;
		}
		k = 0;
		for (int i = 1; i <= n; i++) if (!ban[i]) { k = i; break; }
		if (!k) return puts("NIE"), 0; fa[k] = bel[k];
		for (int i = 1; i <= n; i++) if (find(i) == find(k)) bel[i] = k;
	}
	for (int i = 1; i <= n; i++) printf("%d\n", fa[i]);
}
```

---

## 作者：Take_A_Single_6 (赞：0)

很好的一道构造题。  
看到题目让我们构造一棵树，首先就应该考虑怎么选根：  
- 显然根不能为某个点的后代
- 显然根一定是所有点的祖先  

选不到直接 `NIE`。  
接下来考虑如何往下构造，似乎并没有什么新的性质，那就直接推广选根的操作，把其他一坨节点全挂在根下面。考虑确定了根影响了什么，也就是如果某一节点的祖先一定是根，这个关系就没用了。删掉这些关系，重复选根的操作，注意我们有根了所以以后只需要建森林即可：  
- 如果这个节点想成为一棵树的根显然不能为某个节点的后代。
- 如果这个节点想成为一棵树的根显然不能既为某个节点的祖先又不能为该节点的祖先。注意前者关系可能要递推，所以要用并查集维护。  

显然建不出森林了也要 `NIE`。  
代码如下，一些细节见注释：
```cpp
#include<bits/stdc++.h>
//#define int long long
#define db double
#define maxn 3000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
struct con
{
	int x,y;char c;
}e[maxn];
int n,m,rt,fa[maxn],pa[maxn],q[maxn];
bool no[maxn];
int find(int f)
{
	return q[f]==f?f:q[f]=find(q[f]);
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=m;i++)e[i].x=read(),e[i].y=read(),cin>>e[i].c,e[i].c=='T'?no[e[i].x]=1:no[e[i].y]=1;
	for(int i=1;i<=n;i++)if(!no[i])rt=i;//整棵树的根
	if(!rt)puts("NIE"),exit(0);
	for(int i=1;i<=n;i++)pa[i]=rt,fa[i]=-1;//全挂在根下面，注意fa=0是有意义的要初始化为-1
	fa[rt]=0;
	for(int T=1;T<n;T++)
	{
		for(int i=1;i<=n;i++)q[i]=i,no[i]=(fa[i]==-1?0:1);//在剩余节点中建树
		for(int i=1;i<=m;i++)
			if(fa[e[i].y]==-1&&e[i].c=='T')
			{
				no[e[i].x]=1;//不能为后代
				if(fa[e[i].x]==-1)q[find(e[i].x)]=find(e[i].y);//并查集维护祖先关系
			}
		for(int i=1;i<=m;i++)
			if(e[i].c=='N'&&find(e[i].x)==find(e[i].y))no[e[i].y]=1;//y不能既为x祖先又不能为x祖先
		rt=0;
		for(int i=1;i<=n;i++)if(!no[i])rt=i;//找森林中的某棵树的根
		if(!rt)puts("NIE"),exit(0);//找不到了
		fa[rt]=pa[rt];//与挂上的那个节点确认父子关系
		for(int i=1;i<=n;i++)if(find(i)==find(rt))pa[i]=rt;//与这个根有祖先关系就挂在这个根下面
	}
	for(int i=1;i<=n;i++)write(fa[i]),puts("");
	return 0;
}
```

---

