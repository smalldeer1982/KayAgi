# [ARC111D] Orientation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_d

$ N $ 頂点 $ M $ 辺の単純な無向グラフが与えられます。頂点には $ 1,\ \cdots,\ N $ の番号がついています。$ i $ 番目の辺は頂点 $ a_i $, $ b_i $ を繋いでいます。 また、正整数列 $ c_1,\ c_2,\ \cdots,\ c_N $ も与えられます。

このグラフを、次の条件を満たすように有向グラフに変換してください。つまり、各 $ i $ について無向辺 $ (a_i,\ b_i) $ を削除し、有向辺 $ a_i\ \to\ b_i $、$ b_i\ \to\ a_i $ のどちらか $ 1 $ つを張ってください。

- 全ての $ i\ =\ 1,\ 2,\ \cdots,\ N $ について、頂点 $ i $ から(有向辺を好きな回数使うことで)到達可能な頂点数がちょうど $ c_i $ 個。なお、頂点 $ i $ 自身も $ 1 $ 個と数える。

なお、この問題では、**解が存在する**ような入力のみが与えられます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ M\ \leq\ \frac{N(N\ -\ 1)}{2} $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフに自己ループや多重辺は存在しない
- $ 1\ \leq\ c_i\ \leq\ N $
- **必ず題意を満たす解が存在する**

### Sample Explanation 1

長さ $ 3 $ のサイクルでは、どの頂点からも全ての頂点に到達できます。

### Sample Explanation 3

グラフは非連結のこともあります。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
3 3 3```

### 输出

```
->
->
->```

## 样例 #2

### 输入

```
3 2
1 2
2 3
1 2 3```

### 输出

```
<-
<-```

## 样例 #3

### 输入

```
6 3
1 2
4 3
5 6
1 2 1 2 2 1```

### 输出

```
<-
->
->```

# 题解

## 作者：MSqwq (赞：3)

简单构造，挺有趣的  
感觉 $n$ 还可以更大一点


------------
题意：  
给定 $n$ 个点 $m$ 条边的无向图，现在要求给每条边定向，使得最后第 $i$ 个点能够到达的点数量为 $c_i$，最后输出定向方案。  


------------
题解：  
首先对于每条边 $(x,y)$ 考虑，如果$c_x < c_y$ 那么一定是大的连向小的，不然肯定不满足关系，即是 $y$ 连向 $x$。反之如果 $c_x > c_y$ 那么一定是一条 $x$ 连向 $y$ 的边。本题重要讨论 $c_x = c_y$ 的情况。  
不难发现，我们把不等的边全部可以定向，剩下的肯定是若干堆 $c$ 相等的点，因为保证有解，所以没堆的 $c$ 相同，不难想到构造环，环上的元素 $c$ 值都相等。那么如果有 $c_x = c_y$ 我们就将 $x$ 和 $y$ 连一条边，然后把环上的边定向即可。  
拓展想一下，如果要判无解（本题不用），其实即使如果一个环上的 $c$ 出现了矛盾，那么就无解了。  
细节（如果你 WA1）：注意一下在 $dfs$ 的时候，因为最开始存的是双向边，那么在我们定向一条边后，回溯的时候就不要再更改这条边状态了。  

代码如下：  
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<functional>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0',c=getchar();}
	return x*f;
}
const int N=110,M=1e5+10;
struct qwq{
	int x,y;
	int ans;
}e[M];
int g[N][N];
vector<int>v[N];
int a[N],vis[N];

void dfs(int x)
{
	vis[x]=1;
	for(auto to:v[x])
	{
		if(g[to][x])continue;
		g[x][to]=1;
		if(!vis[to])dfs(to);
	}
}

int main()
{
	int n=read(),m=read();
	for(int i=1;i<=m;i++)e[i].x=read(),e[i].y=read();
	for(int i=1;i<=n;i++)a[i]=read();
	
	for(int i=1;i<=m;i++)
	{
		if(a[e[i].x]<a[e[i].y])e[i].ans=0;
		if(a[e[i].x]>a[e[i].y])e[i].ans=1;
		if(a[e[i].x]==a[e[i].y])v[e[i].x].push_back(e[i].y),v[e[i].y].push_back(e[i].x);
	}
	
	for(int i=1;i<=n;i++)
		if(!vis[i])dfs(i);
	
	for(int i=1;i<=m;i++)
	{
		if(a[e[i].x]==a[e[i].y])
		{
			if(g[e[i].x][e[i].y])e[i].ans=1;
			else e[i].ans=0;
		}
	}
	
	for(int i=1;i<=m;i++)
	{
		if(e[i].ans)cout<<"->"<<endl;
		else cout<<"<-"<<endl;
	}
    return 0;
}
```


---

## 作者：TLEWA (赞：1)

萌萌可爱构造题。

考虑给边定向对 $c_i$ 造成的影响。显然如果钦定一条有向边 $u \to v$，有 $c_u \ge c_v$。则对于任意 $c_u \ne c_v$，他们之间的直接连边方向一定确定。

接下来考虑 $c_u = c_v$ 的情况，显然 $u,v$ 可以到达的点集相同，则 $u,v$ 在一个强联通分量内，由于题目保证有解，所以我们通过一遍 dfs 确定边的方向即可。

## AC 代码


```cpp
#include<bits/stdc++.h>

using namespace std;

/*
考虑如何决策每一条边

首先考虑点权不等的情况

肯定是高点权联向低点权

然后点权相等的情况呢？

若他们之间有连边，则他们肯定在一个联通块内
dfs 即可
*/

const int N=10005;

int n,m;

struct Node {int v,Id,p;};
vector<Node> vec[N];
int id[N],val[N]; // -1 表示 <-，1 表示 -> 

bool vis[N];
void dfs(int u) {
	vis[u]=1;
	for(auto& [v,Id,p]:vec[u]) {
		if(id[Id] || val[v]>val[u]) continue;
		id[Id]=p;
		if(!vis[v]) dfs(v);
	}
}

int main() {
	cin >> n >> m;
	
	int u,v;
	for(int i=1;i<=m;++i) {
		cin >> u >> v;
		vec[u].push_back({v,i,1});
		vec[v].push_back({u,i,-1});
	}
	for(int i=1;i<=n;++i) cin >> val[i];
	
	for(int i=1;i<=n;++i) if(!vis[i]) dfs(i);
	
	for(int i=1;i<=m;++i) {
		if(id[i]==-1) cout << "<-";
		else cout << "->";
		cout << endl;
	}
	
	return 0;
}

```

时间复杂度 $O(n)$

---

## 作者：Liyunze123 (赞：0)

考虑 $c_{a_i}$ 和 $c_{b_i}$ 的大小。

如果小于，一定是从 $b_i$ 连到 $a_i$。证明很简单，反证，若不然，$b_i$ 能到达的点 $a_i$ 都能到达。与小于矛盾。大于同理。

对于等于的情况，将这些边连出来，显然有同一连通块内 $c_i$ 相等。对于不在环上的边，如果从 $a_i$ 连到 $b_i$，所有 $b_i$ 能到达的点，$a_i$ 都能到达；而 $b_i$ 不能到达 $a_i$，同理如果从 $b_i$ 连到 $a_i$，所有 $b_i$ 能到达的点，$a_i$ 都能到达；而 $b_i$ 不能到达 $a_i$，与同一连通块内 $c_i$ 相等矛盾。所以，新图只有环。对于环上的边，保持方向一致即可。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[10010],b[10010],c[110],e[20010],ne[20010],ans[10010],st[110],h[110],v[110][110],idx;
void add(int a,int b){e[++idx]=b,ne[idx]=h[a],h[a]=idx;}
void dfs(int i){
	if(st[i])return;
	st[i]=1;
	for(int w=h[i];w;w=ne[w])if(!v[e[w]][i])v[i][e[w]]=1,dfs(e[w]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int w=1;w<=m;w++)scanf("%d%d",&a[w],&b[w]);
	for(int w=1;w<=n;w++)scanf("%d",&c[w]);
	for(int w=1;w<=m;w++)if(c[a[w]]<c[b[w]])ans[w]=0;else if(c[a[w]]>c[b[w]])ans[w]=1;else add(a[w],b[w]),add(b[w],a[w]);
	for(int w=1;w<=n;w++)if(!st[w])dfs(w);
	for(int w=1;w<=m;w++){
		if(c[a[w]]==c[b[w]])ans[w]=v[a[w]][b[w]];
		if(ans[w])printf("->\n");
		else printf("<-\n");
	}
	return 0;
}
```

---

## 作者：Filberte (赞：0)

枚举每条边 $(u,v)$，对于 $a_u \not= a_v$ 的边，肯定是从大的往小的那边连边。因此只需要给 $a_u = a_v$ 的边定向，这说明 $u,v$ 在同一个强连通分量内。问题转化为给定一个无向图，给边定向，使得任意相邻的两点在同一个强连通分量内。对于每一个连通块考虑，构造其 dfs 树，任意钦定根，树边向叶节点方向连，非树边向根节点方向连即为方案。

补充一下如果不保证有解如何解决。需要判断原图中任意一个连通块能否通过定向变成强连通分量，这个的充要条件是原来的无向图没有桥。但其实你按本题构造，判断其是不是强连通分量即可。因为若原图无桥，则每条树边肯定对应至少 $1$ 条返祖边，肯定是一个强连通分量。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M = 5050, N = 105;
int n, m, a[N];
pair<int, int> e[M];
vector<int> g[N];
bool vis[N];
bool con[N][N];
void dfs(int u){
    vis[u] = 1;
    for(int v : g[u]){
        if(con[v][u]) continue;
        con[u][v] = 1;
        if(!vis[v]) dfs(v);
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1;i <= m;i++) cin >> e[i].first >> e[i].second;
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= m;i++){
        int u = e[i].first, v = e[i].second;
        if(a[u] == a[v]){
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    for(int i = 1;i <= n;i++) if(!vis[i]) dfs(i);
    for(int i = 1;i <= m;i++){
        int u = e[i].first, v = e[i].second;
        if(a[u] > a[v]) cout << "->" << endl;
        else if(a[u] < a[v]) cout << "<-" << endl;
        else if(con[u][v]) cout << "->" << endl;
        else cout << "<-" << endl;
    }
    return 0;
}
```

---

## 作者：Leaper_lyc (赞：0)

对于边 $(u,v)$。

假如 $c_u>c_v$，那么边的方向肯定是 $u\to v$ 的，因为 $v$ 能到达的点 $u$ 也能到达，否则 $v$ 能到达的点就比 $u$ 能到达的点数多了。

$c_u<c_v$，同理。

接下来考虑 $c_u=c_v$ 的情况。由于大家都相等，那么结构一定是等价的，容易想到环的结构，这样就只要确定一条边的方向，其他环上边的方向是一样的。

代码很简单：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
const int M = 1e5 + 10;
int n, m;
int a[N];
bool g[N][N], fl[M], vis[N];
vector <int> G[N];
struct edge { int x, y; } e[M];
void dfs(int u) {
	vis[u] = true;
	for (int v : G[u]) {
		if (g[v][u]) continue;
		g[u][v] = true;
		if (!vis[v]) dfs(v);
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> e[i].x >> e[i].y;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1, x, y; i <= m; i++) {
		x = e[i].x, y = e[i].y;
		fl[i] = (a[x] > a[y]);
		if (a[x] == a[y])
			G[x].push_back(y), G[y].push_back(x);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) dfs(i);
	for (int i = 1; i <= m; i++)
		if (a[e[i].x] == a[e[i].y])
			fl[i] = g[e[i].x][e[i].y];
	for (int i = 1; i <= m; i++)
		if (fl[i]) cout << "->\n";
		else cout << "<-\n";
}
```

---

## 作者：cyq32ent (赞：0)

考虑一条从 $u$ 连向 $v$ 的边。那么如果从 $v$ 可以到达 $w$，那么从 $u$ 也能通过 $u \rightarrow v \rightarrow w$ 的路径到达 $w$。所以 $c_u\geq c_v$。

考虑上述命题的逆命题。当 $c_u>c_v$，显然 $u$ 要连向 $v$；但是当 $c_u=c_v$，那么就不一定。进一步地，$u$ 和 $v$ 必定相互连通。

`dfs` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>G[111];//v id
int n,m,t,c[111],vis[111],d[5555];
map<pair<int,int>,int>M;
void dfs(int u){
	vis[u]=1;
	for(auto v:G[u])
		if((c[v.first]<=c[u])&&!d[v.second]){
			d[v.second]=M[make_pair(u,v.first)];
			if(!vis[v.first])dfs(v.first);
		}
}
signed main(){
	cin>>n>>m;t=m;
	for(int u,v;m--;){
		cin>>u>>v;
		G[u].push_back({v,m});
		G[v].push_back({u,m});
		M[make_pair(u,v)]=1;
		M[make_pair(v,u)]=-1;
	}for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
	for(int i=t;~(--i);)cout<<((~d[i])?"->\n":"<-\n");
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

显然对于两个相邻的点 $u,v$ 假若 $c_u \not = c_v$，那么 $c$ 大的连向小的 $c$ 即可，因为假若存在一条 $u \to v$ 则 $c_u > c_v$。

否则我们考虑为什么 $c$ 会相等，显然一个强联通分量内所有点 $c$ 相等，而假若不同强联通分量之间有边相连则两个强联通分量内的点的 $c$ 不同，所以我们找出无向图上所有 $c_i$ 相等的极大连通块，将其定向为强联通分量即可。

连通块定向为强联通分量考虑建立 dfs 生成树后，树边向下，返祖边向上，由于不存在割边（保证有解，即存在合法定向）所以一个点重复向下走，跳返祖边的操作一定会回到根，即到任意点均可达。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
vector<int> E[maxn];
int n,m,U[maxn],V[maxn];
int c[maxn];
map<int,int> id[maxn];
int vis[maxn];
void dfs(int u){
	vis[u]=1;
	for(int v:E[u]){
		if(vis[v]==0){
			id[u][v]=1;
			id[v][u]=0;
			dfs(v);
			//u \to v
		}else{
			id[u][v]=0;
			id[v][u]=1;
		}
	}
}
void work(int C){
	for(int i=1;i<=m;i++){
		if(c[U[i]]==C&&c[V[i]]==C){
			E[U[i]].push_back(V[i]);
			E[V[i]].push_back(U[i]); 
		}
	}
	for(int i=1;i<=n;i++){
		if(c[i]==C&&vis[i]==0){
			dfs(i);
		} 
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>U[i]>>V[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=n;i++) work(i);
	for(int i=1;i<=m;i++){
		cout<<(c[U[i]]==c[V[i]]?(id[U[i]][V[i]]==1?"->":"<-"):(c[U[i]]>c[V[i]]?"->":"<-"))<<'\n';
	}
	return 0;
}
```

---

