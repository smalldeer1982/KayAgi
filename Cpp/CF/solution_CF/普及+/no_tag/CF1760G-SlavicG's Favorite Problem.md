# SlavicG's Favorite Problem

## 题目描述

You are given a weighted tree with $ n $ vertices. Recall that a tree is a connected graph without any cycles. A weighted tree is a tree in which each edge has a certain weight. The tree is undirected, it doesn't have a root.

Since trees bore you, you decided to challenge yourself and play a game on the given tree.

In a move, you can travel from a node to one of its neighbors (another node it has a direct edge with).

You start with a variable $ x $ which is initially equal to $ 0 $ . When you pass through edge $ i $ , $ x $ changes its value to $ x ~\mathsf{XOR}~ w_i $ (where $ w_i $ is the weight of the $ i $ -th edge).

Your task is to go from vertex $ a $ to vertex $ b $ , but you are allowed to enter node $ b $ if and only if after traveling to it, the value of $ x $ will become $ 0 $ . In other words, you can travel to node $ b $ only by using an edge $ i $ such that $ x ~\mathsf{XOR}~ w_i = 0 $ . Once you enter node $ b $ the game ends and you win.

Additionally, you can teleport at most once at any point in time to any vertex except vertex $ b $ . You can teleport from any vertex, even from $ a $ .

Answer with "YES" if you can reach vertex $ b $ from $ a $ , and "NO" otherwise.

Note that $ \mathsf{XOR} $ represents the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 说明/提示

For the first test case, we can travel from node $ 1 $ to node $ 3 $ , $ x $ changing from $ 0 $ to $ 1 $ , then we travel from node $ 3 $ to node $ 2 $ , $ x $ becoming equal to $ 3 $ . Now, we can teleport to node $ 3 $ and travel from node $ 3 $ to node $ 4 $ , reaching node $ b $ , since $ x $ became equal to $ 0 $ in the end, so we should answer "YES".

For the second test case, we have no moves, since we can't teleport to node $ b $ and the only move we have is to travel to node $ 2 $ which is impossible since $ x $ wouldn't be equal to $ 0 $ when reaching it, so we should answer "NO".

## 样例 #1

### 输入

```
3
5 1 4
1 3 1
2 3 2
4 3 3
3 5 1
2 1 2
1 2 2
6 2 3
1 2 1
2 3 1
3 4 1
4 5 3
5 6 5```

### 输出

```
YES
NO
YES```

# 题解

## 作者：Phartial (赞：5)

## 题意

给你一棵树和两个点 $a,b$，边有边权。你可以在任意时刻从当前所在的点跳到任意除了 $b$ 以外的点。求有没有方案使得从 $a$ 出发，到达 $b$ 时边权 $\operatorname{xor}$ 和为 $0$。

$1\le n\le 10^5$。

## 思路

由于 $\operatorname{xor}$ 的性质，最终走出来的路径一定是一条从 $a$ 出发的简单路径和一条由 $b$ 结束的简单路径拼起来得到的，由于要求 $\operatorname{xor}$ 和为 $0$，所以这两条简单路径的 $\operatorname{xor}$ 和应该相等。

预处理从 $a$ 出发的 $n$ 条简单路径，丢进一个 `set` 里，接着从 $b$ 出发遍历每条简单路径，查一下有没有就行了。

时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using Pii = pair<int, int>;

const int kN = 1e5 + 1;

int t, n, a, b;
set<int> m;
vector<Pii> e[kN];

bool D(int x, int f, int v) {
  if (x == b) {
    return !v;
  }
  m.insert(v);
  for (Pii &i : e[x]) {
    if (i.first != f) {
      if (D(i.first, x, v ^ i.second)) {
        return 1;
      }
    }
  }
  return 0;
}
bool C(int x, int f, int v) {
  if (x != b && m.find(v) != m.end()) {
    return 1;
  }
  for (Pii &i : e[x]) {
    if (i.first != f) {
      if (C(i.first, x, v ^ i.second)) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; ) {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) {
      e[i].clear();
    }
    for (int i = 1, x, y, w; i < n; ++i) {
      cin >> x >> y >> w;
      e[x].emplace_back(y, w), e[y].emplace_back(x, w);
    }
    m.clear();
    cout << (D(a, 0, 0) || C(b, 0, 0) ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

---

## 作者：promise_ (赞：3)

给定一颗树，每条边带有一个边权。从 $a$ 点出发，到达点 $b$，使得当中经过的边权异或和为 $0$

首先，我们可以观察到在一个节点上，我们只能选择那些通过边的权值进行异或后结果为 $0$ 的边进行转移，否则我们无法将异或和变为 $0$。所以我们可以将问题转化为是否存在一条路径，从起点 $a$ 到终点 $b$，使得路径上所有边的权值异或结果为 $0$。这可以通过搜索算法来实现。

但是，在这个问题中，我们还可以从任意节点跳到任意非 $b$ 节点。我们可以想成在图中添加了一条虚拟的边，连接了所有节点，权值为跳的过程中的异或结果。因此，我们需要判断从起点 $a$ 到终点 $b$，经过这条虚拟边的路径的异或结果是否为 $0$。

---

## 作者：_Remake_ (赞：3)

## 题目分析
给定一颗无向无根树，边带权，给出 $a$，$b$ 点，你有一个初始数值为 $0$ 每次经过一条边，你的数值就异或上这条边的边权，你最多能够传送一次，你可以从任意一个顶点传送到任意一个除 $b$ 之外的顶点，你不能通过与 $b$ 直接相连的边，除非你的数值等于这条边的边权。求能否从 $a$ 点到达 $b$ 点。
可以使用 `dfs` 求出从 $a$ 点出发，在不经过 $b$ 点的情况下自己可以取到的值，可以用 `map` 记录，之后从 $b$ 点开始 `dfs`，$b$ 点开始的移动不受限制，如果出现某个值既可以从 $a$ 出发取到，又可以从 $b$ 出发取到，则可以从 $a$ 点到达 $b$ 点。
## 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
    int n=0,k=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m,T,a,b;
struct edge
{
	int v,ne,w;
}E[200101];
int Ecnt=0;
int head[100101];
void addedge(int u,int v,int w)
{
	Ecnt++;
	E[Ecnt].v=v;
	E[Ecnt].ne=head[u];
	head[u]=Ecnt;
	E[Ecnt].w=w;
}
bool exist=0;
std::map<int,bool>M;
void dfs1(int u,int fa,int Xor)
{
	for(int r=head[u];r;r=E[r].ne)
	{
		int v=E[r].v;
		if(v==fa||v==b)
		{
			continue;
		}
		M[Xor^E[r].w]=1;
		dfs1(v,u,Xor^E[r].w);
	}
}
void dfs2(int u,int fa,int Xor)
{
	for(int r=head[u];r;r=E[r].ne)
	{
		int v=E[r].v;
		if(v==fa)
		{
			continue;
		}
		if(M[Xor^E[r].w]!=0)
		{
			exist=1;
		}
		dfs2(v,u,Xor^E[r].w);
	}
}
signed main()
{
	n=0;
	T=read();
	while(T--)
	{
		M.clear();
		exist=0;
		for(int r=1;r<=Ecnt;r++)
		{
			E[r]={0,0,0};
		}
		Ecnt=0;
		n=read();
		for(int r=1;r<=n;r++)
		{
			head[r]=0;
		}
		assert(n<=100000&&n>1);
		a=read();
		b=read();
		int u,v,w;
		for(int r=1;r<n;r++)
		{
			u=read();
			v=read();
			w=read();
			addedge(u,v,w);
			addedge(v,u,w);
		}
		M[0]=1;
		dfs1(a,0,0);
		dfs2(b,0,0);
		if(!exist)
		{
			puts("NO");
		}
		else
		{
			puts("YES");
		}
	}
    return 0;
}

```


---

## 作者：hjqhs (赞：2)

标题里的“返回题目和提交题解”是保留节目（  
问题就是问是否有一条从 $a$ 开始的路径和一条以 $b$ 结束的路径的异或为 $0$。那预处理出从 $a$ 的路径，再从 $b$ 也跑一次，看看有没有相等的即可。
```cpp
// Problem: G. SlavicG's Favorite Problem
// Contest: Codeforces - Codeforces Round 835 (Div. 4)
// URL: https://codeforces.com/problemset/problem/1760/G
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-19 19:35:09
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

// #define int long long
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 100005;
const int INF = 0x3f3f3f3f;

int T;
int n, a, b, ans;
map<int, bool> vis;

struct node {int to, w; };
vector<node> g[N];

void dfs (int u, int fa, int k, int t) {
	if (!t && u == b) return;
	if (!t) vis[k] = 1;
	else ans |= (u != b && vis[k]);
	
	for (node i : g[u]) {
		if (i.to != fa) {
			dfs (i.to, u, k ^ i.w, t);
		}
	}
}

void solve () {
	cin >> n >> a >> b;
	vis.clear(), ans = 0;
	rep (i, 1, n) g[i].clear();
	rep (i, 1, n - 1) {
		int x, y, z; cin >> x >> y >> z;
		g[x].emplace_back( (node){y, z} );
		g[y].emplace_back( (node){x, z} );
	}
	
	dfs (a, 0, 0, 0), dfs (b, 0, 0, 1);
	
	cout << (ans ? "YES" : "NO") << '\n';
	
	return;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	cin >> T;
	while (T --) {solve(); }
	
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1760G)

气人啊，没打过 CF 不知道不能用 `unordered_map`，调了我 $1$ 个小时，还好看了讨论区。

给你一棵树和两个点 $a,b$，边有边权。你可以在任意时刻从当前所在的点跳到任意除了 $b$ 以外的点。求有没有方案使得从 $a$ 出发，到达 $b$ 时边权 $\operatorname{xor}$ 和为 $0$。

$1\le n\le 10^5$。

最终从 $a$ 到 $b$ 的路径其实就是从 $a$ 到某个点 $x$ 的路径与从 $b$ 到点某个点 $y$ 这两条路径拼起来的。

DFS 预处理从点 $a$ 出发到每个点的异或和，如果存在一个异或和为 $w$，则用 `map` 标记 $w$ 为 $1$。

DFS 从点 $b$ 出发，设当前到达的点为 $k$，从点 $b$ 到点 $k$ 的异或和为 $sum$，如果 $mp_{sum}$ 为 $1$，则说明从点 $b$ 到点 $k$ 这一条路径与从点 $a$ 出发的一条简单路径的异或和相同，即存在从点 $a$ 到点 $b$ 的异或和为 $0$ 的路径，将 $flag$ 标记为 $1$。

如果 $flag$ 为 $1$，输出 `YES`，否则输出 `NO`。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int T,n,a,b;
struct Edge{
	int y,v;
};
vector<Edge>G[N];
map<ll,bool>mp;
void dfs1(int k,int fa,ll sum)
{
	for(auto i:G[k])
	{
		int y=i.y,v=i.v;
		if(y==fa||y==b) continue;
		mp[sum^v]=1;
		dfs1(y,k,sum^v);
	}
}
bool flag=0;
void dfs2(int k,int fa,ll sum)
{
	for(auto i:G[k])
	{
		int y=i.y,v=i.v;
		if(y==fa) continue;
		if(mp[sum^v]) flag=1;
		dfs2(y,k,sum^v);
	}
}
void solve()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) G[i].clear();
	mp.clear();
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	flag=0;
	mp[0]=1;
	dfs1(a,0,0);
	dfs2(b,0,0);
	if(flag) cout<<"YES\n";
	else cout<<"NO\n";
}
int main()
{
//    freopen("input.in","r",stdin);
//    freopen("output.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) solve();
    return 0;
}
```

---

## 作者：114514xxx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1760G)
## 题意
摘自[这里](https://www.luogu.com.cn/discuss/553025)。

给你一个 $n$ 点的带边权无根树，节点编号 $1\dots n$。你初始在节点 $a$，要走到 $b$。你还有一个变量 $x$，初值为 $0$。每一秒你可以：

- 走向这个点任意一个相邻的点，设你经过这条边的边权是 $w$，那么这个变量 $x\gets x\text{ xor } w$。
- 传送到任意一个不是 $b$ 的节点，$x$ 不变。**这个操作只能做至多一次。**

问是否存在一个路径从 $a$ 到 $b$ 满足最后的 $x=0$。

## 思路

如果没有传送这个操作是很简单的，因此我们主要处理传送这个操作。

手搓几组样例玩一下我们可以发现传送等价于将一条从 $a$ 出发的简单路径和一条由 $b$ 结束的简单路径拼起来。

假设从 $a$ 出发的简单路径的权值异或和与由 $b$ 结束的简单路径的异或和相等，那么就存在方案使得从 $a$ 出发，到达 $b$ 时边权异或和为 $0$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 25;
const int inf = 2e9;
int a, b, n, p[N], t[N];
bool flag;
struct Edge{
    int to, next, w;
} edge[N];
map<int, int> mp;
int head[N], cnt;
void add(int x, int y, int z){
    edge[++cnt].to = y;
    edge[cnt].next = head[x];
    edge[cnt].w = z;
    head[x] = cnt;
}
inline void dfs1(int u, int fa){
    for (int i = head[u]; i; i = edge[i].next){
        int v = edge[i].to;
        if (v == fa || v == b)
            continue;
        p[v] = p[u] ^ edge[i].w;
        mp[p[v]]++;
        dfs1(v, u);
    }
}
inline void dfs2(int u, int fa){
    for (int i = head[u]; i; i = edge[i].next){
        int v = edge[i].to;
        if (v == fa)
            continue;
        t[v] = t[u] ^ edge[i].w;
        if (mp[t[v]])
            flag = 1;
        dfs2(v, u);
    }
}
inline void solve(){
    cin >> n >> a >> b;
    int x, y, z;
    mp.clear(), flag = 0;
    for (int i = 0; i <= cnt; i++)
        edge[i].w = 0, edge[i].to = 0, edge[i].next = 0, head[i] = 0;
    cnt = 0;
    for (int i = 1; i < n; i++){
        cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }
    p[a] = 0;
    t[b] = 0;
    mp[0] = 1;
    dfs1(a, 0);
    dfs2(b, 0);
    if (flag)
        cout << "YES\n";
    else
        cout << "NO\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}

```

---

## 作者：CarroT5656 (赞：0)

**题意**

给你一颗树，每条边带有一个边权。

你要从 $a$ 点出发，到达点 $b$，使得当中经过的边权异或和为 $0$。

另外，你可以从任意点跳到除 $b$ 点外的任意一点最多一次。

**思路**

考虑如果经过一条边两次，那么对最终异或值的贡献不变。

所以走过的路径一定是一条链。

因为可以跳到任意点，可以把它看成两条链，一条链的端点为 $a$，另一条的端点为 $b$。

题目要让这两条链的异或值为 $0$，即这两条链的异或值相等。

所以可以考虑从 $a$ 点和 $b$ 点为起始点，遍历整一张图并记录当前的异或值。最后看两次遍历中记录的异或值是否存在相同的数。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define F first
#define S second
#define N 150005
typedef pair<ll,ll> pll;
ll t,n,a,b,v[N][2];
vector<pll> e[N];
void dfs(ll x,ll fa,ll xo,ll f){
	if(f==0&&x==b) return;
	v[x][f]=xo;
	for(pll i:e[x]) if(i.F!=fa)
		dfs(i.F,x,xo^i.S,f);
}
void solve(){
	scanf("%lld%lld%lld",&n,&a,&b);
	for(ll i=0;i<N;i++) v[i][0]=v[i][1]=1e9,e[i].clear();
	for(ll i=1,u,v,w;i<n;i++) scanf("%lld%lld%lld",&u,&v,&w),
		e[u].pb({v,w}),e[v].pb({u,w});
	dfs(a,0,0,0),dfs(b,0,0,1);
	map<ll,ll> f;
	for(ll i=1;i<=n;i++) f[v[i][0]]=1;
	bool fl=0;
	for(ll i=1;i<=n;i++) if(i!=b&&f[v[i][1]]){
		fl=1;
		printf("YES\n");
		break;
	}
	if(!fl) printf("NO\n");
}
int main(){
	scanf("%lld",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：C_Cong (赞：0)

#### 题目大意

给出起点、终点以及树的边权，判断是否存在一条路径使得从起点到终点经过的边的边权异或值为0，允许从任一点跳跃至除终点外的任一点一次。

#### 解题思路

异或的一个重要性质：$ a \operatorname{xor} a = 0 $

首先考虑不跳跃的情况：

即找到一条从起点到终点的路径使得各边边权异或值为0，直接dfs即可。

再考虑跳跃的情况：

假设一条从起点出发的路径各边边权异或值为 $ x $，一条从终点出发的路径各边边权异或值为 $ y $，若存在 $ x = y $ 则存在满足题意的路径。

设起点为 $ S $，终点为 $ T $。

分别以 $ S , T $ 为起点dfs记录到达任一点所有可能路径的各边边权的异或值（这里可以直接用set维护异或值）。

若两种dfs中存在相同的异或值，则存在满足题目要求的路径。

#### 代码实现：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

struct edge
{
    long long v, w;
};

struct node
{
    long long u, v, w;
} num[100010];

vector<edge> G[100010];
set<long long> se;
set<long long>::iterator iter;

long long tl, t, n, m, s;
bool pd[100010], pl;

long long read()
{
    char c = getchar();
    long long k = 0;
    while (c < '0' || c > '9')
    {
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        k = k * 10 + c - 48;
        c = getchar();
    }
    return k;
}

bool cmp(node x, node y)
{
    return x.w < y.w;
};

void dfs(long long p, long long ws, int mods) // mods=0 第一种情况 mods=2 第二种情况
{
    if (pl)
    {
        return;
    }

    if (p == t && mods == 0) // 存在直达终点的合法路径
    {
        if (ws == 0 && !pl)
        {
            printf("YES\n");
            pl = true;
        }
        return;
    }
    if (p != t && mods == 0)
    {
        se.insert(ws);
    }
    for (long long i = 0; i < G[p].size(); ++i)
    {
        long long V = G[p][i].v, W = G[p][i].w;
        if (pl)
        {
            return;
        }
        if (!pd[V])
        {
            pd[V] = true;
            if (mods == 1)
            {
                iter = se.find(ws ^ W);
                if (iter != se.end() && !pl) // 存在跳跃后能到达终点的路径
                {
                    printf("YES\n");
                    pl = true;
                    return;
                }
            }
            dfs(G[p][i].v, ws ^ W, mods);
        }
    }
}

int main()
{
    scanf("%lld", &tl);
    while (tl--)
    {
        memset(pd, 0, sizeof(pd));
        memset(G, 0, sizeof(G));
        se.clear();
        n = read();
        s = read();
        t = read();
        pl = false;
        for (long long a = 1; a <= n - 1; ++a)
        {
            edge tmp;
            num[a].u = read();
            num[a].v = read();
            num[a].w = read();
            tmp.v = num[a].v;
            tmp.w = num[a].w;
            G[num[a].u].push_back(tmp);
            tmp.v = num[a].u;
            G[num[a].v].push_back(tmp);
        }
        pd[s] = true;
        dfs(s, 0, 0);
        if (pl) // 若存在
        {
            continue;
        }
        memset(pd, 0, sizeof(pd));
        if (!pl) //若不存在
        {
            pd[t] = true;
            dfs(t, 0, 1);
        }
        if (!pl) // 若不存在
        {
            printf("NO\n");
            continue;
        }
    }
    return 0;
}
```



---

## 作者：Deft_t (赞：0)

## 思路
需要进入 $b$ 时的边权异或和为 $0$，且可以使用一次传送。因为传送可以从任意点出发，传送到除 $b$ 以外的任意点，因此可以视为固定使用一次传送。  
设从 $a$ 出发遍历到点 $i$ 时的边权异或和为 $w_i$，现在就需要传送到一个点，且这个点走到 $b$ 的边权异或和也为 $w_i$，这样走到 $b$ 时的边权异或和就为 $0$ 了。  
可以反向把 $b$ 作为起点，预处理出每个点到 $b$ 的边权异或和。再使用 map 记录是否存在该异或和的结果。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
struct Edge{
	int v,w;
};
vector<Edge> e[100005];
int wa[100005],wb[100005];
map<int,bool> Map;
int n,a,b;
bool ok;
void dfsa(int u,int fa){
	if(u == b && wa[u]==0) ok = true;
	if(Map[wa[u]]) ok = true;
	for(int i = 0;i < e[u].size();i++){
		int v = e[u][i].v;
		if(v==fa || v==b) continue;
		wa[v] = (wa[u]^e[u][i].w);
		dfsa(v,u);
	}
}
void dfsb(int u,int fa){
	for(int i = 0;i < e[u].size();i++){
		int v = e[u][i].v;
		if(v == fa) continue;
		wb[v] = (wb[u]^e[u][i].w);
		if(v != a) Map[wb[v]] = true;
		dfsb(v,u);
	}
}
int main()
{
	ios::sync_with_stdio(NULL);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n>>a>>b;
		int u,v,w;
		for(int i = 1;i <= n;i++) e[i].clear(),wa[i]=wb[i]=0;
		for(int i = 1;i <= n-1;i++){
			cin>>u>>v>>w;
			e[u].pb(Edge{v,w});
			e[v].pb(Edge{u,w});
		}
		Map.clear();
		ok = false;
		dfsb(b,0);
		dfsa(a,0);
		if(ok) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

