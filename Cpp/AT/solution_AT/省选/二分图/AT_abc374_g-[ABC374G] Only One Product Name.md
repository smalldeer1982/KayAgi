# [ABC374G] Only One Product Name

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc374/tasks/abc374_g

キーエンスの商品名はすべて **英大文字 $ 2 $ 文字** からなります。  
 すでに $ N $ 個の商品名を使用しており、$ i $ 個目 $ (1\leq\ i\leq\ N) $ の商品名は $ S_i $ です。  
 一度使用した商品名は再び使うことができないので、過去に使用した商品名の一覧がすぐわかるように NG リストを作ることにしました。

NGリストは次の条件をみたす必要があります。

- $ 1 $ つ以上の文字列からなり、各文字列は英大文字のみからなる。
- すでに使用されている商品名それぞれについて、その商品名を（連続する）部分文字列として含む文字列が $ 1 $ つ以上存在する。
- リスト内のすべての文字列は、すでに使用されている商品名でない長さ $ 2 $ の文字列を（連続する）部分文字列として含まない。
 
NG リストの文字列の数としてあり得る最小の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 26^2 $
- $ N $ は整数
- $ S_i $ は英大文字のみからなる長さ $ 2 $ の文字列
- $ S_1,S_2,\ldots,S_N $ はすべて異なる。
 
### Sample Explanation 1

条件をみたす NG リストとしては例えば次の $ 3 $ つの文字列からなるようなものが考えられます。 - `CABCDE` - `DF` - `XX` これは $ 3 $ つの文字列からなり、$ 2 $ つ以下の文字列からなり条件をみたす NG リストは存在しないため、 $ 3 $ を出力します。

### Sample Explanation 2

条件をみたす NG リストとしては例えば次の $ 2 $ つの文字列からなるようなものが考えられます。 - `ACDE` - `BCDF` すでに使用されている商品名は NG リスト内の複数の文字列に登場したり、同一文字列に複数回含まれたりしていても良いことに注意してください。

### Sample Explanation 3

例えば、`ABACBADB` のみからなる NG リストが条件をみたしています。

## 样例 #1

### 输入

```
7
AB
BC
CA
CD
DE
DF
XX```

### 输出

```
3```

## 样例 #2

### 输入

```
5
AC
BC
CD
DE
DF```

### 输出

```
2```

## 样例 #3

### 输入

```
6
AB
AC
CB
AD
DB
BA```

### 输出

```
1```

# 题解

## 作者：Angraecum (赞：4)

纪念一下差点场切的 G，因为没写过最小路径覆盖，一开始还当成无向图了，这个时候来补发现很简单的。

----

容易想到要转化成图论问题考虑。

先 $O(n^2)$ 枚举 $i,j$ 如果 $i$ 第二个字符等于 $j$ 第一个字符就连一条有向边，最后会出来一个一般有向图，问题转化成有向图最小路径覆盖。

最小路径覆盖指在图中选取最少数量的路径，使得每个点都属于一条路径，我们做的最小路径覆盖一般都是 DAG 里的且路径是不可相交的。

结论：最小路径覆盖数 =DAG 中的点数 - 二分图最大匹配数。二分图建法是拆点，每条边 $(u,v)$ 表示左部的 $u$ 连向右部的 $v$。

证明：我们称选取的路径上的边为关键边，显然，路径数 = 点数 - 关键边数。每条关键边都是二分图上一条匹配边。

两个注意点，首先图有环，考虑把强连通分量缩点。根据题意路径可以相交，考虑在缩点后的图上再做一遍传递闭包，直接按上面说的做就行了。

写的匈牙利，代码非常短。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N=2005,M=1919810,inf=1e18,mod=998442353;
vector <ll> e[N],g[N];
ll n;
char ca[N],cb[N];
bool vis[N];
ll dfn[N],low[N],t_cnt;
ll col[N],c_cnt;
ll st[N],top;
void tarjan(ll u){
	dfn[u]=low[u]=++t_cnt;
	vis[u]=1,st[++top]=u;
	for(int v:e[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		ll x;
		col[u]=++c_cnt;
		do{
			x=st[top--];
			col[x]=c_cnt,vis[x]=0;
		}while(x!=u);	
	}
}
ll dis[N][N];
ll p[N],vi[N];
bool dfs(ll u,ll tag){
	if(vi[u]==tag) return 0;
	vi[u]=tag;
	for(int v:g[u]){
		if(!p[v]||dfs(p[v],tag)){
			p[v]=u;
			return 1;
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>ca[i]>>cb[i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(cb[i]==ca[j]) e[i].pb(j);
	for(int i=1;i<=n;++i)
		if(!dfn[i]) tarjan(i);
	for(int u=1;u<=n;++u)
		for(int v:e[u])
			if(col[u]!=col[v]) dis[col[u]][col[v]]=1;
	n=c_cnt;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				dis[i][j]|=dis[i][k]&dis[k][j];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(dis[i][j]) g[i].pb(j);
	ll ans=n;
	for(int i=1;i<=n;++i) ans-=dfs(i,i);
	cout<<ans;
	return 0;
}/*会了真不难*/
```

---

## 作者：Register_int (赞：3)

如果把每个长度为二的字符串视为一条边，那么就能转化为一个最小路径覆盖问题……但是覆盖的是边就很难受。

不过你可以在每条边上都塞个点进去，要求覆盖掉所有的点。这样最优方案必然会覆盖掉所有的边。

但是这个图有环啊？没有关系，显然一个 scc 内的所有边都能一次遍历完，跑个 tarjan 缩点即可。

但是覆盖的路径可以相交啊？还是没有关系，你跑个传递闭包，就不用考虑路径相交的问题了。

最后就是最小路径覆盖的经典模型，每条边 $(u,v)$ 从左部的 $u$ 连向右部的 $v$，割掉这条边表示将 $u,v$ 合并起来。跑二分图最大匹配即可，时间复杂度 $O(n^{2.5})$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e3 + 10;
const int MAXM = 1e5 + 10;
const int inf = INT_MAX;

struct node {
	int v, c, nxt;
	node(int v = 0, int c = 0, int nxt = 0) : v(v), c(c), nxt(nxt) {}
} e[MAXM << 1]; int head[MAXN], tot = 1;

inline 
void add(int u, int v, int c) {
	e[++tot] = node(v, c, head[u]), head[u] = tot;
	e[++tot] = node(u, 0, head[v]), head[v] = tot;
}

int lvl[MAXN], lst[MAXN];

inline 
bool bfs(int s, int t) {
	memset(lvl, 0xff, sizeof lvl);
	queue<int> q; q.emplace(0), lvl[0] = 0;
	for (int u; !q.empty(); ) {
		u = q.front(), q.pop(), lst[u] = head[u];
		for (int i = head[u], v; i; i = e[i].nxt) {
			if (!e[i].c) continue; v = e[i].v;
			if (!~lvl[v]) lvl[v] = lvl[u] + 1, q.push(v);
		}
	}
	return ~lvl[t];
}

inline 
int dfs(int u, int t, int f) {
	if (u == t || !f) return f; int res = 0;
	for (int &i = lst[u], v; i; i = e[i].nxt) {
		v = e[i].v; if (lvl[v] != lvl[u] + 1) continue;
		int x = dfs(v, t, min(f, e[i].c));
		e[i].c -= x, e[i ^ 1].c += x, f -= x, res += x;
	}
	return res;
}

inline 
ll dinic(int s, int t) {
	ll res = 0;
	for (; bfs(s, t); res += dfs(s, t, inf));
	return res;
}

vector<int> g[MAXN];

int dfn[MAXN], low[MAXN], id; bool ins[MAXN];

int st[MAXN], tp, scc[MAXN], cnt;

void tarjan(int u) {
	dfn[u] = low[u] = ++id, ins[u] = 1, st[++tp] = u;
	for (int v : g[u]) {
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		cnt++;
		for (int x = 0; x != u; x = st[tp--], ins[x] = 0, scc[x] = cnt);
	}
}

int n, m, s, t, ans; char p[MAXN][3];

bool dis[MAXN][MAXN], vis[26];

int main() {
	scanf("%d", &m), n = m + 26, t = n << 1 | 1;
	for (int i = 1; i <= m; i++) {
		scanf("%s", p[i]), vis[p[i][0] - 'A'] = vis[p[i][1] - 'A'] = 1;
		g[p[i][0] - 'A' + 1].emplace_back(i + 26), g[i + 26].emplace_back(p[i][1] - 'A' + 1);
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int u = 1; u <= n; u++) {
		for (int v : g[u]) if (scc[u] != scc[v]) dis[scc[u]][scc[v]] = 1;
	}
	n = cnt;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) dis[i][j] |= dis[i][k] & dis[k][j];
		}
	}
	for (int i = 1; i <= n; i++) add(s, i, 1), add(i + n, t, 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (dis[i][j]) add(i, j + n, 1);
		}
	}
	ans = n - dinic(s, t);
	for (int i = 0; i < 26; i++) if (!vis[i]) ans--;
	printf("%d", ans);
}
```

---

## 作者：dyc2022 (赞：2)

切完 E 发现读不懂 F 题面就摆了，没发现后面有这样一道套路板子，车俞！
***
首先，考虑什么样的字符串能连在一起。我们将能连在一起的字符串之间连有向边。

然后有一个显然的结论：一个 scc 内的字符串一定可以连在一起，因为存在一个环。

那么我们就将所有 scc 先缩点，然后注意到题目中的一个 NG List 其实就是形成的 DAG 上的一条路径。那么 NG List 的最小数目就是最后这个 DAG 上的最小可重叠路径覆盖（因为一个字符串可以在多个 NG List 中）。

这是一个很板的东西。于是建成这张图，然后在上面虚拟源点汇点网络流即可。

---

## 作者：shinzanmono (赞：2)

设第 $i$ 个给定字符串为 $s_i$，考虑有向图 $G=(V,E)$，$V=\{1,2,\ldots,N\}$，对于数对 $i,j$，若 $s_{i,1}=s_{j,0}$，则边 $i\rightarrow j\in E$。可以证明的是，原图中的任意一条路径已经是一个符合条件的字符串。我们需要找到最少的路径（不是简单路径）使得每条边至少包含在一条路径中。

对于这张图来说，直接求解很麻烦。我们考虑 DAG 的最小链覆盖是好求的，有向图可以 SCC 缩点转化为 DAG，可以证明的是一个 SCC 必然可以用一条路径覆盖。

所以将原图缩点成为 DAG，然后就成为了板子题。

```cpp
#include<iostream>
#include<algorithm>
#include<stack>
const int sz=710;
std::basic_string<int>graph[sz];
int dpp,num,belong[sz],dfn[sz],low[sz];
bool vis[sz];
std::stack<int>stack;
void tarjan(int u){
    dfn[u]=low[u]=++dpp;
    stack.push(u),vis[u]=true;
    for(int v:graph[u]){
        if(dfn[v]==0)tarjan(v),low[u]=std::min(low[u],low[v]);
        else if(vis[v])low[u]=std::min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        num++;
        while(!stack.empty()){
            int v=stack.top();
            stack.pop();
            belong[v]=num,vis[v]=false;
            if(u==v)break;
        }
    }
}
bool edge[sz][sz];
int pp[sz];
int dfs(int u){
    for(int v=1;v<=num;v++){
        if(!edge[u][v]||vis[v])continue;
        vis[v]=true;
        if(pp[v]==-1||dfs(pp[v])==1)return pp[v]=u,1;
    }
    return 0;
}
int solve(){
    int ans=0;
    std::fill(pp+1,pp+num+1,-1);
    for(int i=1;i<=num;i++){
        std::fill(vis+1,vis+num+1,0);
        ans+=dfs(i);
    }
    return num-ans;
}
std::string s[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    for(int i=1;i<=n;i++)std::cin>>s[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(s[i][1]==s[j][0])graph[i]+=j;
    for(int i=1;i<=n;i++) 
        if(dfn[i]==0)tarjan(i);
    for(int u=1;u<=n;u++) 
        for(int v:graph[u]) 
            if(belong[u]!=belong[v]) 
                edge[belong[u]][belong[v]]=1;
    for(int p=1;p<=num;p++)
        for(int u=1;u<=num;u++)
            for(int v=1;v<=num;v++)
                edge[u][v]|=edge[u][p]&edge[p][v];
    std::cout<<solve()<<"\n";
    return 0;
}
```

---

## 作者：RiceFruit (赞：2)

## 思路

首先显然的把每个字符串前面向后面连边，形成一个有向图，问题就是求这个图的最小可重路径边覆盖，考虑缩点，转换成有向无环图最小可重路径边覆盖，但还是不好做，于是对于一个点，在新图上把以这个点为结尾的边和以这个点为开头的边连边，注意特判一个孤立强连通分量的情况，现在这个问题变成了点覆盖，且新图的点数最多为 $26^2$，问题十分经典，考虑对于任意两个点 $u,v$，若 $u$ 能到达 $v$，则在 $u,v$ 之间连一条边，具体过程可以 `bitset` 优化传递闭包，然后变成有向无环图最小**不重**路径点覆盖，网络流即可，具体的看[这道题](https://www.luogu.com.cn/problem/P2764)即可，注意到新图的点数为 $26^2$，边数为 $26^4$，故复杂度：$\Theta(m\sqrt n)$，$2\cdot 10^6$ 左右，代码不放了。

---

## 作者：Xy_top (赞：1)

首次赛时做出 G，写篇题解庆祝一下。

对于每对能连在一起的名字将它们连边，然后我们发现这个问题就是求最少路径覆盖，只不过有环。

考虑对其进行强连通分量缩点，然后转化成了求最少可相交路径覆盖，我会的是最少不相交路径覆盖，怎么转换呢？显然可以使用 Floyd 传递闭包，将所有能直接间接到达的点全部连边然后缩点，最后跑一遍匈牙利算法即可。

感觉做麻烦了，但是还是过了，代码：


```cpp
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m, t;
int cnt, ccnt;
int row[10000];
bool f[1005][1005];
int dfn[100005], low[100005];
int id[100005], idx[100005];
bool vis[100005], inst[100005];
stack <int> st;
vector <int> G[100005], ans[100005];
vector <int> v[10000];
bool vv[1000][1000];
char s[10000][2];
int link[2000], is[2000], nt = 1;
bool Arg(int x) {
    for(int i = 0; i < v[x].size(); i++) {
        int to = v[x][i];
        if(is[to] == nt) continue; is[to] = nt;
        if(!link[to] || Arg(link[to]))
            {link[to] = x; link[x] = to; return 1;}
    }
    return 0;
}
int Hunary() {
    int ans = 0;
    for(int i = 1; i <= cnt; i++, nt++)
        if(Arg(i))
            ans++;
    return ans;
}
void tarjan (int u) {
	dfn[u] = low[u] = ++ cnt;
	st.push (u);
	inst[u] = true;
	for (int v : G[u]) {
		if (!dfn[v]) tarjan (v);
		if (inst[v]) low[u] = min (low[u], low[v]);
	}
	if (low[u] == dfn[u]) {
		while (!st.empty () && st.top () != u) {
			id[st.top () ] = u;
			ans[id[st.top () ] ].push_back (st.top () );
			inst[st.top () ] = false;
			st.pop ();
		}
		id[u] = u;
		ans[id[u] ].push_back (u);
		inst[u] = false;
		st.pop ();
		++ ccnt;
	}
}
int main () {
	scanf ("%d", &n);
	For (i, 1, n) cin >> s[i];
	For (i, 1, n) {
		For (j, 1, n) {
			if (i == j) continue;
			if (s[i][1] == s[j][0]) G[i].push_back (j);
		}
	}
	for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan (i);
	int ccccc = 0;
	For (i, 1, n) {
		if (!row[id[i] ]) row[id[i] ] = ++ ccccc;
	}
	For (i, 1, n) {
		For (j, 1, n) {
			if (i == j) continue;
			if (s[i][1] == s[j][0]) {
				if (id[i] != id[j] && !vv[id[i]][id[j] ]){
					f[row[id[i] ]][row[id[j]]] = 1;
					vv[id[i] ][id[j]] = 1;
				}
			}
		}
	}
	For (k, 1, ccccc) {
		For (i, 1, ccccc) {
			For (j, 1, ccccc) {
				f[i][j] = f[i][j] | (f[i][k] && f[k][j]);
			}
		}
	}
	For (i, 1, ccccc) {
		For (j, 1, ccccc) {
			if (f[i][j]) v[i].push_back (j + ccnt);
		}
	}
	cout << ccnt - Hunary ();
	return 0;
}
```

---

## 作者：TankYu (赞：1)

前置知识：最大流。

考虑转化成图论问题。

令 NG 列表的字符串为 $T_1,T_2,\cdots,T_m$。

对于 $s_i,s_j$，若 $\exist k$ 使 $s_i$ 和 $s_j$ 在 $T_k$ 中 **相邻**，则在图上建一条 $i$ 到 $j$ 的边。

这个相邻有两种情况：

1. $s_i$ 末位和 $s_j$ 首位相同，直接就可以连。
2. $s_i$ 末位和 $s_j$ 首位构成的字符串也在 $\{s\}$ 中出现，此时设其为 $s_k$，则这个东西等价于 $s_i,s_k$ 和 $s_k,s_j$ 分别按 $1$ 的方式相邻，所以不需要管。

现在建出来一张图，答案就是这张图的最小可相交链覆盖。

可相交与不可相交的区别仅在于需要先对图做一次转递闭包然后直接按闭包的连通性进行建边，此后转化为不可相交的最小链覆盖。

注意有环需要缩点。

~~非常神奇的是不缩点只会挂两个随机数据，我还以为我写假了。~~

```cpp
#define LL long long
#define fi first
#define se second
#define mp make_pair
using namespace std;
string s[1145];
map<string, bool> M;
namespace Dinic
{
    const int N = 1e5 + 7, M = 5e6 + 7;
    const LL inf = 1e18;
    int n, S, T, h[N], hi[N], e[M], t[M], tot, d[N];
    LL mxf, f[M];
    inline void add(int x, int y, LL z, int o = 1)
    {
        e[++tot] = y, f[tot] = z, t[tot] = h[x], h[x] = tot;
        if (o)
        {
            add(y, x, 0, 0);
        }
        return;
    }
    inline bool bfs()
    {
        for (int i = 1; i <= n; i++)
        {
            d[i] = 0;
        }
        queue<int> q;
        q.push(S), d[S] = 1;
        while (q.size())
        {
            int x = q.front();
            q.pop();
            for (int i = h[x]; i; i = t[i])
            {
                int y = e[i];
                LL z = f[i];
                if (d[y] || !z)
                {
                    continue;
                }
                q.push(y);
                d[y] = d[x] + 1;
                if (y == T)
                {
                    return 1;
                }
            }
        }
        return 0;
    }
    LL dinic(int x, LL nwf)
    {
        if (x == T)
        {
            return nwf;
        }
        LL rst = nwf;
        for (int &i = hi[x]; i; i = t[i])
        {
            int y = e[i];
            LL z = f[i];
            if (d[y] != d[x] + 1 || !z)
            {
                continue;
            }
            LL k = dinic(y, min(z, rst));
            if (!k)
            {
                d[y] = 0;
            }
            else
            {
                f[i] -= k;
                f[i ^ 1] += k;
                rst -= k;
            }
            if (!rst)
            {
                break;
            }
        }
        return nwf - rst;
    }
    inline void main()
    {
        while (bfs())
        {
            for (int i = 1; i <= n; i++)
            {
                hi[i] = h[i];
            }
            LL now;
            while ((now = dinic(S, inf)))
            {
                mxf += now;
            }
        }
        return;
    }
    inline void init(int _n, int _S, int _T)
    {
        n = _n, S = _S, T = _T, tot = 1, mxf = 0;
        for (int i = 1; i <= n; i++)
        {
            h[i] = 0;
        }
        return;
    }
}
bitset<10010> f[100110];
int r[200010];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        r[i] = 1;
        M[s[i]] = 1;
    }
    Dinic::init(2 * n + 2, 2 * n + 1, 2 * n + 2);
    for (int i = 1; i <= n; i++)
    {
        Dinic::add(2 * n + 1, i, 1);
        Dinic::add(i + n, 2 * n + 2, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        f[i][i] = 1;
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (s[i][1] == s[j][0])
            {
                f[i][j] = 1;
            }
        }
    }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (f[i][k])
            {
                f[i] |= f[k];
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (f[i][j] && f[j][i])
            {
                r[j] = false;
            }
        }
    }
    int m = 0;
    for (int i = 1; i <= n; i++)
    {
        m += r[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i != j && f[i][j] && r[i] && r[j])
            {
                Dinic::add(i, j + n, 1);
            }
        }
    }
    Dinic::main();
    cout << m - Dinic::mxf;
    return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

给 $n$ 个长度为 $2$，互不相同，且只由大写字母组成的字符串 $s$。

你需要构造出一个字符串数组 $t$，使得对于每一个 $s_i$，存在 $t_j$ 使得 $s_i$ 为 $t_j$ 的一个连续子串。并且对于每一个 $t_j$，它的任意一个连续长度为 $2$ 的子串都在 $s$ 中。

求出**数组** $t$ 大小的最小值。

## 分析

考虑把符合条件的串接起来，这就很像接龙。

一个比较明显的思路就是把尾和头相同的 $s$ 连边，然后去找最少需要几条路径可以覆盖全部点，就是网络流的最小**可相交**路径覆盖的板子。

因为原图可能有环，所以缩点之后重新连边，传递闭包后直接跑 dinic 就可以了。

赛时代码写的不可相交，赛后改了 10min 就过了。。。

## Code

```cpp
#include<bits/stdc++.h>
typedef int ll;
using namespace std;
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
    const ll maxn=1e3+5,maxt=2e6+5,mod=998244353;
    ll n,s,t,tot=1,head[maxn],lvl[maxn],now[maxn];
    string str[maxn];
    struct edge{
        ll to,nxt,val;
    }e[maxt];
    inline void add(ll u,ll v,ll w){
        e[++tot]=(edge){v,head[u],w};
        head[u]=tot;
        e[++tot]=(edge){u,head[v],0};
        head[v]=tot;
    }
    inline bool bfs(){
        memset(lvl,0,sizeof(lvl));lvl[s]=1;
        queue<ll>q;q.push(s);now[s]=head[s];
        while(!q.empty()){
            ll u=q.front();q.pop();
            for(ll i=head[u];i;i=e[i].nxt){
                ll v=e[i].to,w=e[i].val;
                if(w>0&&!lvl[v]){
                    lvl[v]=lvl[u]+1;
                    q.push(v);now[v]=head[v];
                    if(v==t)return 1;
                }
            }
        }
        return 0;
    }
    inline ll dfs(ll u,ll f){
        if(u==t)return f;
        ll tmp=f;
        for(ll i=now[u];i&&tmp;i=e[i].nxt){
            ll v=e[i].to,w=e[i].val;now[u]=i;
            if(w&&lvl[v]==lvl[u]+1){
                ll k=dfs(v,min(w,tmp));
                if(!k)lvl[v]=0;
                e[i].val-=k,e[i^1].val+=k;
                tmp-=k;
            }
        }
        return f-tmp;
    }
    ll dfn[maxn],low[maxn],tmp,cnt,col[maxn],siz[maxn];
    bool vis[maxn],f[maxn][maxn];
    vector<ll>son[maxn];
    stack<ll>st;
    inline void tarjan(ll u){
        dfn[u]=low[u]=++tmp,vis[u]=1;st.push(u);
        for(auto v:son[u]){
            if(!dfn[v]){
                tarjan(v);low[u]=min(low[u],low[v]);
            }
            else if(vis[v])low[u]=min(low[u],dfn[v]);
        }
        if(dfn[u]==low[u]){
            ++cnt;
            while(st.top()!=u)col[st.top()]=cnt,++siz[cnt],vis[st.top()]=0,st.pop();
            col[u]=cnt,vis[u]=0,st.pop();
        }
    }
    inline void mian(){
        n=read();
        for(ll i=1;i<=n;++i){
            cin>>str[i];
        }
        for(ll i=1;i<=n;++i){
            for(ll j=1;j<=n;++j){
                if(str[i][1]==str[j][0]){
                    son[i].push_back(j);
                }
            }
        }
        for(ll i=1;i<=n;++i)if(!dfn[i])tarjan(i);
        s=0,t=cnt*2+1;
        for(ll i=1;i<=n;++i){
            for(auto j:son[i]){
                if(col[i]!=col[j]){
                    f[col[i]][col[j]]=1;
                }
            }
        }
        for(ll k=1;k<=cnt;++k){
            for(ll i=1;i<=cnt;++i){
                for(ll j=1;j<=cnt;++j){
                    f[i][j]|=f[i][k]&f[k][j];
                }
            }
        }
        for(ll i=1;i<=cnt;++i){
            add(s,i,1),add(i+cnt,t,1);
            for(ll j=1;j<=cnt;++j){
                if(f[i][j])add(i,j+cnt,1);
            }
        }
        ll ans=0;
        while(bfs())ans+=dfs(s,INT_MAX);
        write(cnt-ans);
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--)tobe::mian();
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[ABC374G] Only One Product Name](https://www.luogu.com.cn/problem/AT_abc374_g)
把所有字符串看作一个点，对于任意两个字符串 $i$，$j$，如果 $i$ 的第二个字符和 $j$ 的第一个字符相同，则连一条 $i \to j$ 的有向边。

则原问题转化为了求图上的最小可交叉路径覆盖数。

不难发现，在一个 SCC 内，所有点都能被一条路径串起来，故可以进行缩点，则原图化为了一个 DAG。

此时，问题就被我们转化为了求一个 DAG 上的最小可交叉路径覆盖数。

但我们只会 DAG 上的最小不交叉路径覆盖数，交叉怎么办呢？

考虑对于 DAG 跑传递闭包，使其成为一个新图。对于原 DAG 上的两条交叉路径，在该图上都有一条不用经过交叉点的路径，故该问题转化为了求 DAG 上的最小不交叉路径覆盖数。

将该 DAG 中的有向边的两端点分别看作左部点和右部点建二分图，即每个点分别在左部和右部出现一次。

有结论：**DAG 上的最小不交叉路径覆盖数 $=$ DAG 的点数 $-$ 二分图上的最大匹配数**。

使用匈牙利算法，复杂度为 $O\left(n^3\right)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans, idx, vistime, dfn[705], ins[705], low[705], vis[705], num[705], match[705], d[705][705];

struct node
{
	string s;
} a[705];

stack < int > st;

vector < int > G[705];

void dfs(int u)
{
	dfn[u] = low[u] = ++vistime;
	st.push(u);
	ins[u] = 1;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (!dfn[v])
		{
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		int v;
		idx++;
		do
		{
			v = st.top();
			st.pop();
			ins[v] = 0;
			num[v] = idx;
		} while (v != u);
	}
}

bool search(int x)
{
	for (int i = 1; i <= idx; i++)
	{
		if (!d[x][i]) continue;
		if (vis[i]) continue;
		vis[i] = 1;
		if (!match[i] || search(match[i]))
		{
			match[i] = x;
			return 1;
		}
	}
	return 0;	
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].s;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[i].s[1] == a[j].s[0]) G[i].push_back(j);
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < G[i].size(); j++)
		{
			int v = G[i][j];
			if (num[i] != num[v]) d[num[i]][num[v]] = 1;
		}
	for (int i = 1; i <= idx; i++)
		for (int j = 1; j <= idx; j++)
			for (int k = 1; k <= idx; k++)
				d[j][k] |= (d[j][i] & d[i][k]);
	ans = idx;
	for (int i = 1; i <= idx; i++)
	{
		for (int j = 1; j <= idx; j++)
			vis[j] = 0;
		if (search(i)) ans--;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Filberte (赞：0)

循序渐进思考原问题的解法，先来看四个前置的经典问题。

**问题1**：给定一个有向无环图，选出一些路径，使得每个点恰好被覆盖一次，最少需要选多少条路径。

对原图每个点 $i$ 拆为 $u_i$ 和 $v_i$，若有一条边从 $i$ 连向 $j$，那么用一条无向边把 $u_i$ 和 $v_j$ 连接起来。最终会形成一个二分图，求这个二分图的最大匹配 $M$。最终答案就是 $n - |M|$。因为是最大匹配，所以每个左部点最多只会连接一个右部点，即每个点出度最多为 $1$；同理，每个点入度最多为 $1$。我们已经最大化匹配大小，所以路径覆盖数肯定是最少的。

**问题2**：给定一个有向无环图，选出一些路径，使得每个点最少被覆盖一次，最少需要选多少条路径。

对原图求出其传递闭包，在传递闭包上按解决问题 $1$ 的方式求解最少路径覆盖，因为传递闭包中每条边都对应原图中一条路径，所以传递中一条路径也对应原图中一条路径。

**问题3**：给定一个有向无环图，选出一些路径，使得每条边最少被覆盖一次，最少需要选多少条路径。

把 $u\rightarrow v$ 这条边看作是 $u\rightarrow p\rightarrow v$，转化为问题 $2$。

**问题4** ：给定一个有向图，选出一些路径，使得每条边最少被覆盖一次，最少需要选多少条路径。

对原图缩点，一个强连通分量内所有点必然可以在一次路径覆盖的过程中全部覆盖，因此可以转化为无环的情况，也就是问题 $3$。

会了以上 $4$ 个问题的解法，回到本题。把字母对应成 $26$ 个点，题目中给定的 $n$ 个出现过的名字可以转化为 $n$ 条形如 $u \rightarrow v$ 的有向边，原问题实质上等价于问题 $4$，按照上文所述的方法解决即可。

```c++
#include <bits/stdc++.h>
using namespace std;
namespace MF{
    #define int_64 int
    static const int maxn = 2000;
    static const int maxm = 1e6 + 1e5;
    const int_64 Mxf = 1e9;
    struct E{int to, nxt;int_64 f;}e[maxm];
    int hd[maxn], cur[maxn], _te = 1;
    void add_edge(int u, int v, int_64 w){
        e[++_te] = {v, hd[u], w};hd[u] = _te;  
        e[++_te] = {u, hd[v], 0};hd[v] = _te;
    }
    int nods, s, t;
    int_64 maxf = 0;
    int d[maxn];
    bool bfs(){
        for(int i = 0;i <= nods;i++) d[i] = 0, cur[i] = hd[i];
        queue<int> q;q.push(s);d[s] = 1;
        while(!q.empty()){
            int u = q.front();q.pop();
            for(int i = hd[u];i;i = e[i].nxt){
                int v = e[i].to;
                if(e[i].f && !d[v]){
                    d[v] = d[u] + 1;
                    q.push(v);
                    if(v == t) return 1;
                }
            }
        }
        return 0;
    }
    int_64 dfs(int u, int_64 flow){
        if(u == t) return flow;
        int_64 sum = 0;
        for(int &i = cur[u];i;i = e[i].nxt){
            int v = e[i].to;
            if(e[i].f && d[v] == d[u] + 1){
                int_64 gt = dfs(v, min(e[i].f, flow));
                e[i].f -= gt, e[i ^ 1].f += gt;
                sum += gt, flow -= gt;
            }
        }
        if(!sum) d[u] = 0;
        return sum;
    }
    void dinic(){while(bfs()) maxf += dfs(s, Mxf);}
}
using namespace MF;
int n, m;
const int mnod = 800;
vector<int> g[mnod];
int dfn[mnod], low[mnod], clk;
int st[mnod], tp;bool inst[mnod];
int col[mnod], cc;
void tarjan(int u){
    dfn[u] = low[u] = ++clk;
    st[++tp] = u, inst[u] = 1;
    for(int v : g[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inst[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        ++cc;
        do{
            col[st[tp]] = cc;
            inst[st[tp]] = 0;
        }
        while(st[tp--] != u);
    }
}
bitset<mnod> ed[mnod];
bool hve[30];
int main(){
    cin >> m;n = 26 + m;
    for(int i = 1;i <= m;i++){
        char c1, c2;cin >> c1 >> c2;
        int u = c1 - 'A' + 1, v = c2 - 'A' + 1;
        hve[u] = hve[v] = 1;
        g[u].push_back(i + 26);
        g[i + 26].push_back(v);
    }
    for(int i = 1;i <= 26;i++) if(!dfn[i] && hve[i]) tarjan(i);
    for(int i = 27;i <= n;i++) if(!dfn[i]) tarjan(i);
    for(int u = 1;u <= n;u++)
        for(int v : g[u])
            ed[col[u]][col[v]] = 1;
    for(int i = 1;i <= cc;i++) ed[i][i] = 1;
    for(int k = 1;k <= cc;k++)
        for(int i = 1;i <= cc;i++) if(ed[i][k])
            ed[i] |= ed[k];
    nods = 2 * cc + 1, s = 0, t = nods;
    for(int u = 1;u <= cc;u++){
        add_edge(s, u, 1);
        for(int v = 1;v <= cc;v++)
            if(u != v && ed[u][v]) add_edge(u, v + cc, 1);
        add_edge(u + cc, t, 1);
    }
    dinic();
    cout << cc - maxf << endl;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个长度为 $2$ 的，由大写英文字母构成的互不相同的字符串 $S_1,S_2,\cdots,S_n$。你需要构造一个字符串列表 $T$，使得对于任意的 $S_i$，都存在至少一个 $T_j$，使得 $S_i$ 是 $T_j$ 的子串，且对于任意的 $T_i$ 的任意一个长度为 $2$ 的子串 $T_i'$，$T_i'$ 包含在 $S$ 中。

求字符串列表 $T$ 的最小大小。

$1\leq n\leq 26^2$。

## 思路

首先对于每一个 $T_i$，必定是由若干个字符串拼接起来，而拼接起来的字符串必须首尾相同，要不然就可能会引入不在 $S$ 中的子串。

对于 $S_i,S_j$，如果 $S_i$ 的最后一个字符等于 $S_j$ 的第一个字符，那么就连接一条有向边 $(i,j)$。那么最终会得到一个 $n$ 个点若干条边的有向图，我们需要选出若干条路径，使得覆盖有向图上的每一个点。

考虑到同一个强连通分量的点一定是随便覆盖，于是我们先缩点变成一个 DAG。然后发现求有向图不相交覆盖很容易（拆点后就是二分图最小边覆盖），要求可相交覆盖，我们可以求这个有向图的传递闭包，对于两个点 $i,j$，若存在路径 $i\to j$，那么就连接一条边，这样一条边就对应了一条路径，可以使用不相交覆盖的方法求解。具体参考 P2764 最小路径覆盖问题。

时间复杂度 $O(n^2\sqrt{n})$ 可以通过本题。

## 代码

借助 [AtCoder Library](https://atcoder.github.io/ac-library/production/document_en/)，可以省略 tarjan 和 dinic 的细节，代码显得更加精简：

```cpp
// Problem: [ABC374G] Only One Product Name

#include <bits/stdc++.h>
#include <atcoder/scc>
#include <atcoder/maxflow>
//#define int long long
using namespace std;

const int N = 26 * 26 + 5;
int n, tag[N];
bool f[N][N];
string s[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> s[i];
    atcoder::scc_graph g(n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i != j && s[i][1] == s[j][0]) g.add_edge(i - 1, j - 1);
        }
    }
    auto scc = g.scc(); int cnt = scc.size();
    for(int i=0;i<cnt;i++){
        for(int j : scc[i]) tag[j + 1] = i + 1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][1] == s[j][0] && tag[i] != tag[j]) f[tag[i]][tag[j]] = 1;
        }
    }
    for(int i=1;i<=cnt;i++) f[i][i] = 1;
    for(int k=1;k<=cnt;k++){
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=cnt;j++) f[i][j] |= (f[i][k] && f[k][j]);
        }
    }
    atcoder::mf_graph<int> g2((cnt << 1) + 2);
    int s =0, t = (cnt << 1) + 1;
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=cnt;j++){
            if(f[i][j] && i != j) g2.add_edge(i, j + cnt, 1);
        }
    }
    for(int i=1;i<=cnt;i++) g2.add_edge(s, i, 1);
    for(int i=1;i<=cnt;i++) g2.add_edge(i + cnt, t, 1);
    cout << (cnt - g2.flow(s, t));
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Arghariza (赞：0)

疑似有点太典了。

把给定的字符对 $(s_{i,0},s_{i,1})$ 看成点 $i$，$i$ 向 $j$ 连边当且仅当 $s_{i,1}=s_{j,0}$。于是我们相当于求这个图的最小可交链覆盖。

由于不保证是 DAG，所以缩点后再传递闭包，根据连通性连边，然后相当于最小不交链覆盖，拆点跑二分图最大匹配即可。

```cpp
// Problem: G - Only One Product Name
// Contest: AtCoder - KEYENCE Programming Contest 2024（AtCoder Beginner Contest 374）
// URL: https://atcoder.jp/contests/abc374/tasks/abc374_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

struct Flow {
	int n, s, t, tot;
	struct edge { int to, nxt, w; };
	vector<int> hd, cr, d;
	vector<edge> e;
	Flow () { }
	Flow (int _n) : n(_n), tot(-1) { hd.resize(n + 5, -1), d.resize(n + 5, 0), e.clear(); }
	void add_edge(int u, int v, int w) { e.eb((edge) { v, hd[u], w }), hd[u] = ++tot; }
	void add_flow(int u, int v, int w) { add_edge(u, v, w), add_edge(v, u, 0); }
	bool bfs() {
		fill(d.begin(), d.end(), 0);
		queue<int> q; q.push(s), d[s] = 1;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = hd[u]; ~i; i = e[i].nxt) {
				int v = e[i].to;
				if (!e[i].w || d[v]) continue;
				d[v] = d[u] + 1, q.push(v);
			}
		}
		return d[t];
	}
	int dfs(int u, int in) {
		if (u == t) return in;
		int out = 0;
		for (int &i = cr[u]; ~i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && d[v] == d[u] + 1) {
				int res = dfs(v, min(in, e[i].w));
				in -= res, out += res;
				e[i].w -= res, e[i ^ 1].w += res;
			}
			if (!in) break;
		}
		if (!out) d[u] = 0;
		return out;
	}
	int dinic() {
		int mf = 0;
		while (bfs()) cr = hd, mf += dfs(s, 1e9);
		return mf;
	}
};

const int M = 700;

int n, m, ct, dfc, tp;
int st[M], vs[M], w[M][M], in[M], dfn[M], low[M];
bitset<M> S[M];

int id(string s) {
	return (s[0] - 'A') * 26 + (s[1] - 'A') + 1;
}

string rid(int id) {
	char c1 = (id - 1) % 26 + 'A';
	char c2 = (id - 1) / 26 + 'A';
	string res = "";
	res += c2, res += c1;
	return res;
}

void dfs(int u) {
	dfn[u] = low[u] = ++dfc, st[++tp] = u;
	for (int v = 1; v <= m; v++) {
		if (v == u || !vs[v] || !w[u][v]) continue;
		if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
		else if (!in[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		in[u] = ++ct;
		while (st[tp] != u) 
			in[st[tp]] = ct, tp--;
		tp--;
	}
}

void solve() {
	cin >> n, m = 26 * 26;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		vs[id(s)] = 1;
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			if (i != j && vs[i] && vs[j] && rid(i)[1] == rid(j)[0]) w[i][j] = 1;
	for (int i = 1; i <= m; i++)
		if (vs[i] && !dfn[i]) dfs(i);
	for (int i = 1; i <= m; i++)
		if (vs[i] && !in[i]) in[i] = ++ct;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			if (!w[i][j] || !in[i] || !in[j] || in[i] == in[j]) continue;
			S[in[i]][in[j]] = 1;
		}
	}
	for (int i = 1; i <= ct; i++) 
		for (int j = 1; j <= ct; j++)
			if (S[i][j]) S[i] |= S[j];
	Flow G((ct << 1) + 5); G.s = 2 * ct + 1, G.t = 2 * ct + 2;
	for (int i = 1; i <= ct; i++)
		for (int j = 1; j <= ct; j++)
			if (i != j && S[i][j]) G.add_flow(i, j + ct, 1);
	for (int i = 1; i <= ct; i++) G.add_flow(G.s, i, 1), G.add_flow(i + ct, G.t, 1);
	cout << ct - G.dinic() << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}



```

---

