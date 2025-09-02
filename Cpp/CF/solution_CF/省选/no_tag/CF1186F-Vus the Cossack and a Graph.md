# Vus the Cossack and a Graph

## 题目描述

哥萨克 Vus 有一个简单图，包含 $n$ 个顶点和 $m$ 条边。设 $d_i$ 表示第 $i$ 个顶点的度数。回忆一下，第 $i$ 个顶点的度数是与第 $i$ 个顶点相连的边的数量。

他需要保留不超过 $\lceil \frac{n+m}{2} \rceil$ 条边。设 $f_i$ 表示删除后第 $i$ 个顶点的度数。他需要以这样的方式删除边，使得对于每个 $i$，都有 $\lceil \frac{d_i}{2} \rceil \leq f_i$。换句话说，每个顶点的度数不能减少超过一半。

请帮助 Vus 保留所需的边！

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 4
4 5
5 3
6 5
```

### 输出

```
5
2 1
3 2
5 3
5 4
6 5
```

## 样例 #2

### 输入

```
10 20
4 3
6 5
4 5
10 8
4 8
5 8
10 4
9 5
5 1
3 8
1 2
4 7
1 4
10 7
1 7
6 1
9 6
3 9
7 9
6 2
```

### 输出

```
12
2 1
4 1
5 4
6 5
7 1
7 4
8 3
8 5
9 3
9 6
10 4
10 7
```

# 题解

## 作者：YLWang (赞：3)

好题。

我们首先观察一下题目。

要求至多保留$(n + m + 1) / 2$条边，即删除不少于$m - (n + m + 1) / 2$，我们就尽量多删

每个节点的度数不能少于$(deg[i] + 1) / 2$,，即最多删去$deg[i] - (deg[i] + 1) / 2$这么多。定义一个节点的$g$值为其还可以删多少。

我们贪心的选取边删除。

首先，我们选取一个目前$g$值最小的节点。

为什么？

因为我们尽量多删。感性理解一下，如果一个$g$小的点和一个$g$大的点同样连着一些点，那么如果这些点的$g$均因删去而变成了0，$g$小的点可能就没有其它出边可以删，$g$大的点一定会有其他的出边。这样会使得$g$小的点的删的机会浪费。所以要先选取$g$小的点。

然后，我们把其邻接的边对应的点的$g$从大到小的删除。

因为如果选择$g$小的先删，那可能删完它们的$g$都变为0，不能删了。只能删一条边。
但是可能存在这两个点都邻接一个$g$大的点，这样就可以删两条边。

所以这样贪心是最优的。

实现需要一定的技巧。建议自行练习。

代码：
```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 1000005
bool del[MAXN];
int u[MAXN], v[MAXN];
int deg[MAXN];
struct Node {
	int val, id;
	bool operator < (Node b) const {return val > b.val;}
};
struct Vertex {
	int v, id;
	bool operator < (Vertex b) const {return deg[v] > deg[b.v];}
};
vector < Vertex > g[MAXN];
priority_queue < Node > Q;
signed main()
{
	memset(del, 0, sizeof(del));
	int n = read(), m = read();
	for(int i = 1; i <= m; i++) {
		u[i] = read(), v[i] = read();
		g[u[i]].push_back((Vertex) {v[i], i});
		g[v[i]].push_back((Vertex) {u[i], i});
		deg[u[i]]++, deg[v[i]]++;
	}
	int delnum = m - (n + m + 1) / 2;
	if(delnum <= 0) {
		printf("%d\n", m);
		for(int i = 1; i <= m; i++)
			printf("%d %d\n", u[i], v[i]);
		return 0;
	}
		
	for(int i = 1; i <= n; i++) {
		deg[i] = deg[i] - (deg[i] + 1) / 2;
		Q.push((Node) {deg[i], i});
	}
//	cout << Q.top().val << endl;
	while(delnum > 0) {
		int U = Q.top().id;
		if(deg[U] <= 0) { Q.pop(); continue; }
		Q.pop();
		sort(g[U].begin(), g[U].end());
		for(int i = 0; i < g[U].size(); i++) {
			if(del[g[U][i].id]) continue;
			int V = g[U][i].v;
			if(deg[V] <= 0) break;//
			del[g[U][i].id] = 1;
			deg[U]--, deg[V]--, delnum--;
			if(deg[V] > 0) {
				Q.push((Node) {deg[V], V});
			}
			if(deg[U] <= 0 || delnum <= 0) break; 
		}
	}
	printf("%d\n", (n + m + 1) / 2);
	For(i, 1, m) {
		if(del[i] == 0) {
			printf("%d %d\n", u[i], v[i]);
		}
	}
    return 0;
}

```



---

## 作者：Inui_Sana (赞：2)

被诈骗了一个上午啊！但是想到了还是很妙的！

每个点至少要保留 $\left\lceil\dfrac{deg_i}{2}\right\rceil$ 条边，也就是一半左右。如果我们直接分配每个点，哪些边选哪些不选，发现这会影响很多东西，无法保证正确。

于是展开联想，选一半，如果有一条路径经过，入边和出边不同，是否就能满足条件了呢？

于是有一个初步的做法，每次 dfs 这个图，将路径上的边黑白交替染色。最后黑色边为答案。

但是有一个问题：如果有奇数度点怎么办？

再想想：一进一出，想到欧拉路。每次从一个奇数度点开始 dfs，一定会在另一个奇数度点结束。每次强制使第一条和最后一条边为黑，这样最多会比原来多 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 条黑边，最后在对只有偶数度的点的图 dfs 一遍。原来最多会有 $\left\lceil\dfrac{m}{2}\right\rceil$，加起来正好是 $\le \left\lceil\dfrac{n+m}{2}\right\rceil$ 的！

在写这篇题解的时候突然产生了一个疑问：如果奇数度点数量顶满会不会出问题？事实上如果顶满了，最后那一遍 dfs 就不会进行，所以是没问题的。

非常巧（zha）妙（pian）的构造！非常好写。

code：

```cpp
int n,m,deg[N];
bool vis[N],ans[N],pd[N];
vector<pii> g;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
void dfs(int u,int fl,int s,int lst){
	for(int &i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[(i+1)/2]){
			continue;
		}
		vis[(i+1)/2]=1;
		ans[(i+1)/2]=fl;
		dfs(v,fl^1,s,(i+1)/2);
		return;
	}
	pd[u]=1;
	if(u!=s){
		ans[lst]=1;
	}
}
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
		deg[u]++,deg[v]++;
	}
	rep(i,1,n){
		if((deg[i]&1)&&!pd[i]){
			dfs(i,1,i,0);
		}
	}
	rep(i,1,n){
		while(head[i]){
			dfs(i,1,i,0);
		}
	}
	rep(i,1,m){
		if(ans[i]){
			g.eb(e[i+i-1].to,e[i+i].to);
		}
	}
	printf("%d\n",g.size());
	for(auto [u,v]:g){
		printf("%d %d\n",u,v);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：封禁用户 (赞：2)

一个神秘的做法。

流程：每次随机一条边，如果这条边可以被选（未被选且选完后满足度数限制），就选这条边。

下面说明为什么这是对的：

1. 当你选择了一条边 $(u,v)$，那么对于度数大于一半这个限制，等效于将 $u$ 练=连出的另一条边 $(u,u')$ 封禁，将 $v$ 连出的另一条边 $(v,v')$ 封禁。

2. 如果下次选到了封禁的这条边，就把那条边解禁，换一个边封禁。很明显，这样是不会冲突的。

3. 在 $1$ 中，当你把 $(u,u')$ 这条边封禁了，下次选择 $u'$ 连出的一条边时就可以利用这个封禁限制。

4. 极端情况，$u'$ 与 $v'$ 是相连的，那么这两个封禁限制只能一共贡献一次。一种极端情况是这个图被分成了若干个大小为四的环，有重边。

5. 这样看来，这 $m$ 条边能选 $\frac{m}{2}$ 次。我们要凑到题目要求，大概是 $\frac{m}{2} \geq m-\frac{n+m}{2}$。等价于 $n \geq 0$。虽然我们估计得不精确，但是这个等价形式非常宽松。

6. 复杂度分析：根据我们所分析的，取 $x$ 条边时有 $x$ 级别的条边被封禁，所以复杂度是一个调和级数。但是这里的 $x$ 级别我不会卡，再配合上它的随机性，跑到很快，比绝大多数线性的都要快。

代码如下：
```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define per(i, j, k) for (int i = j; i >= k; i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;

int read() {
    int s = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
    return f ? s : -s;
}
mt19937 rnd(time(0));
int n, m, cnt, d[1000005], dnow[1000005], is[1000005], u[1000005], v[1000005];
void solve() {
	rep(i, 1, n) d[i] = dnow[i] = 0;
    rep(i, 1, m) {
        d[u[i]]++, d[v[i]]++;
        dnow[u[i]]++, dnow[v[i]]++;
        is[i] = 1;
    }
    rep(i, 1, m - (m + n + 1) / 2) {
        int tmp = rnd() % m + 1, tt = 0;
        while (!is[tmp] || !(dnow[u[tmp]] - 1 >= (d[u[tmp]] + 1) / 2 && dnow[v[tmp]] - 1 >= (d[v[tmp]] + 1) / 2)) {
            tmp = rnd() % m + 1;
            if (++tt == 10000000) return solve();
		}
        is[tmp] = 0;
        dnow[u[tmp]]--, dnow[v[tmp]]--;
    }
    printf("%d\n", (m + n + 1) / 2);
    rep(i, 1, m) if (is[i]) printf("%d %d\n", u[i], v[i]);
}

signed main() {
    n = read(), m = read();
    rep(i, 1, m) {
        u[i] = read(), v[i] = read();
    }
    if (m <= n) {
        printf("%d\n", m);
        rep(i, 1, m) printf("%d %d\n", u[i], v[i]);
        return 0;
    }
    solve();
    return 0;
}
```

至此，这份代码可以在 $1s$ 内通过此题。

不过，这份代码正确性基于随机，准确性没有绝对的保证。事实上，用这份代码，跑若干个由 $12$ 个点构成的完全图时，有一定的概率出错。我们需要对于每一个连通块内跑这份代码，再将答案合并，就可以避免这个问题。对正确性有需要的同学可以按我说的写一写，不是很难写，代码就不放了。

---

## 作者：Semsue (赞：1)

模拟赛的数据范围更有提示性。其中有一个 Sub 是度数全为偶数。那这就提示我们找一条欧拉回路。那么我们在欧拉回路上每隔一条边删一条即可。

接下来思考度数有为奇数的情况，由于总度数和一定是偶数，那么一定有偶数个奇度数的点，我们新建一个虚点，向每个奇数点连边。这样就所有点的度数就是偶数了。然后我们考虑删边，由于虚边不能删，与虚边相邻的边其实也不能删（删了那个奇数点就不满足了），也就是说只有两边都是实边的实边才可以删。然后继续隔一个删一个即可。

```cpp
int n,m,deg[maxn],zz[maxn],cur[maxn];
vector<int>vec,stk;
vector<pii>G[maxn],ans;
bool vis[maxn<<2];
int id=1,pos[maxn],top;
bool dfn[maxn];
pii edge[maxn<<2];
void add_edge(int u,int v){
	edge[++id]=MP(u,v);
	G[u].pb(MP(v,id));
}
void dfs(int u){
	if(!dfn[u])pos[++top]=u;
	dfn[u]=1;
	for(int i=cur[u];i<(int)G[u].size();i=cur[u]){
		cur[u]=i+1;
		if(!vis[G[u][i].second])vis[G[u][i].second]=vis[G[u][i].second^1]=true,dfs(G[u][i].first),vec.pb(G[u][i].second);
	}
}
int main(){
	read(n);read(m);
	for(int i=1,u,v;i<=m;i++){
		read(u);read(v);
		deg[u]++;deg[v]++;
		add_edge(u,v);add_edge(v,u);
	}
	for(int i=1;i<=n;i++)if(deg[i]&1)stk.pb(i);
	for(int i:stk){
		add_edge(i,n+1);add_edge(n+1,i);
	}
	for(int r=1;r<=n;r++)if(!dfn[r]){
		vec.clear();
		top=0;
		dfs(r);
		reverse(vec.begin(),vec.end());
		int len=vec.size()-1;
		for(int i=0,flg=1;i<(int)vec.size();i++){
			if(vec[i]/2>m)continue;
			if(vec[i==0?len-1:i-1]/2<=m&&vec[i==len-1?0:i+1]/2<=m&&!flg){
				flg=1;
				continue;
			}
			flg=0;
			ans.emplace_back(edge[vec[i]].first,edge[vec[i]].second);
		}
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",(int)ans.size());
	for(auto x:ans){
		printf("%d %d\n",x.first,x.second);
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1186F Vus the Cossack and a Graph](https://www.luogu.com.cn/problem/CF1186F)

# 解题思路

大家好，我不会欧拉路径，所以讲一下其他做法。

首先我们要有惊人的注意力。

发现若 $n \ge m$ 时，取所有边即可。

否则首先按照初始度数从小到大开始连边，尽量连成有贡献的边即可，因为这样若每次都达成贡献，则**一定最优**。

注意到这样过不了，我们将边随机打乱后做即可，这样次数由于比较宽松，可以证明最终边数一定在规定次数内。

# 参考代码

```cpp
ll n,m;
ll x,y;
pii D[1000010];
ll need[1000010];
map<ll,map<ll,ll>>mp;
vector<ll>G[1000010];
ll now[1000010];
pii E[1000010];
ll id[1000010];
ll find(ll x)
{
    if(id[x]==x)
        return x;
    return id[x]=find(id[x]);
}
vector<pii>ans;
void _clear(){}
void solve()
{
    _clear();
    cin>>n>>m;
    if((n+m+1)/2>=m)
    {
        cout<<m<<endl;
        forl(i,1,m)
            cout<<rd()<<' '<<rd()<<endl;
        return ;
    }
    forl(i,1,n)
        id[i]=i;
    forl(i,1,m)
        cin>>x>>y,
        D[x].x++,D[y].x++,
        E[i]={x,y},
        G[x].pb(y),G[y].pb(x);
    forl(i,1,n)
        random_shuffle(G[i].begin(),G[i].end());
    forl(i,1,n)
        need[i]=(D[i].x+1)/2,
        D[i].y=i;
    sort(D+1,D+1+n);
    forl(i,1,n)
    {
        for(auto j:G[D[i].y])
            if(now[D[i].y]<need[D[i].y] && now[j]<need[j] && !mp[D[i].y][j])
                mp[D[i].y][j]=mp[j][D[i].y]=1,
                now[D[i].y]++,
                now[j]++,
                ans.pb({D[i].y,j});
        for(auto j:G[D[i].y])
            if(now[D[i].y]<need[D[i].y] && !mp[D[i].y][j])
                mp[D[i].y][j]=mp[j][D[i].y]=1,
                now[D[i].y]++,
                now[j]++,
                ans.pb({D[i].y,j});
    }
    for(auto i:ans)
        id[find(i.x)]=find(i.y);
    forl(i,1,m)
        if(find(E[i].x)!=find(E[i].y))
            id[find(E[i].x)]=find(E[i].y),
            ans.pb({E[i].x,E[i].y});
    cout<<ans.size()<<endl;
    for(auto i:ans)
        cout<<i.x<<' '<<i.y<<endl;
}
```

---

## 作者：fade_away (赞：0)

## Solution

不会贪心，只会麻烦构造。

构造的基本思路是：如果给定一个所有点的度数都是偶数的无向连通图，那么我们直接做一遍欧拉回路，设求出的欧拉回路为 $e_1e_2e_3\dots e_m$ ，那么我们保留所有的 $e_{2k-1},k\in\mathbb{Z_+}$ 就能保证每个点的度数至少为 $\lceil\frac{d}{2}\rceil$ ，需要保留的边数为 $\lceil\frac{m}{2}\rceil$。

那么现在有些点的度数为奇数怎么办？我们考虑给奇数点之间连“假边”，把原图 $G$ 补成一个度数都是偶数的图 $G'$。然后再对每个连通块做上面的过程，唯一不同的只是排在“假边”两边的边必须保留，然后“假边”不选。

此时显然每个点的度数至少为 $\lceil\frac{d}{2}\rceil$，现在我们来证明这张图最多只会保留 $\lceil\frac{n+m}{2}\rceil$ 条边。

对于 $G'$ 中的一个边数至少为 $1$ 的连通块，设它的边数为 $m$，“假边”数为 $x$，分类讨论：
- 当 $x=0$ 时，最多保留 $\lceil\frac{m}{2}\rceil$ 条边。
- 当 $x>0$ 时，最多保留 $\lfloor \frac{m}{2}\rfloor+x$ 条边。

乍一看似乎两种情况加起来会超过限制，但实际上第一种情况产生时，$\sum x$ 的上限会减少至少 $1$，所以我们将第一种的花费放缩为 $\lfloor \frac{m}{2}\rfloor+1$ ，即 $x=1$ 时的花费。

由于假边最多 $\lfloor\frac{n}{2}\rfloor$ 条，因此总花费为 $\sum{\lfloor \frac{m}{2}\rfloor+x}\leq \lceil\frac{m+n}{2}\rceil$，满足限制。

时间复杂度 $O(n+m)$ ，个人感觉细节不少，WA/TLE 了好多发。

## Code

```cpp
vector<PR> Ans;
int a[MAXN << 1], b[MAXN << 1], d[MAXN], head[MAXN], vis[MAXN << 1], id[MAXN << 2], n, m, Num, M, edgenum = 0;
struct enode{ int to, nxt; } e[MAXN << 2];

void addedge(int u, int v) {
	e[++ edgenum] = (enode){v, head[u]}, head[u] = edgenum;
}
void rebuild() {
	vector<int> O; O.clear();
	for (int i = 1; i <= n ; ++ i) if (d[i] & 1) O.PB(i);
	while ((int)O.size()) { 
		int x = O.back(); O.pop_back(); 
		int y = O.back(); O.pop_back(); 
		++ M, a[M] = x, b[M] = y; 
	}
	for (int i = 1; i <= M ; ++ i) addedge(a[i], i), addedge(b[i], i);
}

inline void Dfs(int x) {
	for (int &i = head[x]; i ; i = e[i].nxt) {
		int t = e[i].to;
		if (vis[t]) continue;
		int v = (a[t] == x ? b[t] : a[t]);
		vis[t] = 1, Dfs(v), id[++ Num] = t;
	}
}
void solve() {
	for (int i = 1; i <= n ; ++ i) {
		Num = 0;
		Dfs(i);
		int t = 1;
		for (int j = 1; j <= Num ; ++ j) if (id[j] > m) { t = j; break; }
		for (int j = 1; j <= t - 1 ; ++ j) id[j + Num] = id[j];
		for (int j = 1; j <= Num ; ++ j) id[j] = id[j + t - 1];

		for (int j = 1, flag = 1; j <= Num ; ++ j) { 
			if (id[j] > m) continue;
			if ((j == 1 ? id[Num] : id[j - 1]) > m || (j == Num ? id[1] : id[j + 1]) > m || flag) Ans.PB(MP(a[id[j]], b[id[j]])), flag = 0;
			else flag = 1;
		}
	}
	print((int)Ans.size()), putc('\n');
	for (auto v : Ans) print(v.fi), putc(' '), print(v.se), putc('\n');
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	read(n), read(m), M = m;
	for (int i = 1; i <= m ; ++ i) read(a[i]), read(b[i]), ++ d[a[i]], ++ d[b[i]];

	rebuild();
	solve();

	return 0;
}
```


---

