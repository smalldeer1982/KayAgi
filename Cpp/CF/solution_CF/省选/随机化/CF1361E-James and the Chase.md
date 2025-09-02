# James and the Chase

## 题目描述

詹姆斯·邦德有一个新的计划来抓捕他的敌人。有若干个城市以及它们之间的有向道路，使得可以通过这些道路在任意两个城市之间旅行。当敌人在某个城市出现时，邦德知道她的下一个目的地，但不知道她会选择哪条路径前往。

如果对于每一个城市 $b$，从城市 $a$ 到 $b$ 恰好存在一条简单路径，则称城市 $a$ 是有趣的。这里的简单路径指的是一条经过的城市各不相同的序列，且对于每一对相邻的城市，存在一条从前一个城市指向后一个城市的有向道路。

邦德的敌人擅长逃脱，因此只有从有趣的城市开始追捕才有可能抓住她。詹姆斯希望在这些有趣的城市安排自己的人手。然而，如果有趣的城市数量不足，整个行动就没有意义，因为邦德的人可能会等待太久。

你需要找出所有有趣的城市，或者说明有趣的城市数量不足。这里“不足”指的是有趣的城市数量严格小于所有城市数量的 $20\%$。

## 说明/提示

在所有示意图中，绿色的城市表示有趣城市，红色的城市表示非有趣城市。

在第一个样例中，每个城市都是有趣的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/ea02130aaa657158e02932dc79202b09c65411df.png)

在第二个样例中，没有城市是有趣的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/9f70c6807b725116da2e28994dd20c33629e3f31.png)

在第三个样例中，城市 $1$、$2$、$3$ 和 $5$ 是有趣的。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/f1d050ad3537d17cb3725772a1afecd8c2c46f32.png)

在最后一个样例中，只有城市 $1$ 是有趣的。这严格小于所有城市数量的 $20\%$，因此答案为 $-1$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361E/d74f523bcab5b0c943643c6309e1f1139462efcb.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
3 3
1 2
2 3
3 1
3 6
1 2
2 1
2 3
3 2
1 3
3 1
7 10
1 2
2 3
3 1
1 4
4 5
5 1
4 6
6 7
7 4
6 1
6 8
1 2
2 3
3 4
4 5
5 6
6 1
6 2
5 1```

### 输出

```
1 2 3 
-1
1 2 3 5 
-1```

# 题解

## 作者：Arghariza (赞：23)

upd 2024/7/25：修改了部分 typo。

#### Description 

给定一个有 $n$ 个点 $m$ 条边的**有向强连通图**。称一个点是**好的**当且仅当它到其他点都有且只有一条**简单路径**。如果好的点至少有 $20\%$ 则输出所有好的点，否则输出 `-1`。

$\sum n\leq 10^5,\sum m\leq 2\times 10^5$。

#### Solution

考虑给你一个点 $u$，如何判断其是否是好的。

那很简单是吧，只要以 $u$ 为根建出 `dfs` 树，没有**横叉边**或者**前向边**的话 $u$ 即为好节点。

那我们就可以 $O(n)$ 判断了。

如果我们现在知道一个点 $u$ 是好的，我们考虑如何求出所有的好节点。

还是以 $u$ 为根建出 `dfs tree`，考虑某个 $v$ 的子树，由于整个图的强连通性， $v$ 的子树中有连向其祖先的返祖边。我们不难发现这样的边有且仅有一条，否则 $v$ 有两条路径可以到达 $fa_v$ 即 $v$ 的父亲节点。

那我们先把所有子树 $v$ 内返祖到根的祖先的边的个数记下来，如果这个个数 $\ge 2$，排除 $v$ 是好点的可能，否则就顺便记下每个 $v$ 子树的那条返祖边指向的点。

假设 $v$ 的子树这条返祖边指向了 $w$，那么 $v$ 是好点，当且仅当 $w$ 是好点。考虑证明：

- 如果 $w$ 是好点，那么 $w$ 到所有点路径唯一，又由于 $v$ 过 $w$ 出子树的路径是唯一的，所以 $v$ 到所有点的简单路径是唯一的，即 $v$ 是好点。
- 如果 $v$ 是好点，那么 $v$ 到所有点路径唯一，由于 $v$ 出子树必须要经过 $w$，所以 $w$ 到 $v$ 子树外所有点的路径也是唯一的，然后 $w$ 到 $v$ 的子树内的简单路径也是唯一的（没有前向边与横叉边），所以 $w$ 是好点。

所以综合所有的结论：

一个点 $v$ 是好点，当且仅当 $v$ 的子树内有且仅有一条连向 $v$ 的祖先的返祖边，并且这条边所连向的点是好点。

第一个条件可以考虑所有返祖边 $(a,b)$，它对哪些 $v$ 的子树内返向 $v$ 祖先的边的数量的有贡献。显然这样的 $v$ 分布在 $a\to fa_a\to...\to son_b$ 上，这里的 $son_b$ 为 $b$ 的儿子节点中靠近 $a$ 侧的那个，树上差分即可和第二个条件一起解决。

以上前提为 `dfs tree` 的根节点为好点。

那我们只要找到一个好点，并将其作为根节点，我们就能在 $O(n)$ 的范围内求解。

由于题目只要求好点数量大于等于 $20\%$ 时输出，所以我们随机取 $100$ 个点跑 $O(n)$ 判断。

如果好点数量不小于 $20\%$，你判断不出来的概率为 $\Big(\dfrac{4}{5}\Big)^{100}$ 趋近于 $0$。

所以随机跑 $100$ 次之后得不到一个好点的话就直接输出 $-1$，如果错了就是宇宙射线影响。

否则以找到的好点为根 $O(n)$ 求答案即可。

[评测链接。](https://codeforces.com/contest/1361/submission/179062861)

---

## 作者：Alex_Wei (赞：7)

### *[CF1361E James and the Chase](https://www.luogu.com.cn/problem/CF1361E)

很好的强连通题，需要对有向图 DFS 树有一定理解。

因为题目保证图强连通，所以从任意一个点出发 DFS 可达图上所有点。

判定一个点是否合法：以该点为根的任意 DFS 树只有树边和返祖边：横叉边和前向边将导致大于一条简单路径。

首先找到任意合法点：随机 $100$ 个点判定是否合法。如果合法点的数量不少于 $0.2n$，那么单组测试点正确率不低于 $(1 - 0.8 ^ {100}) ^ {1000}\approx 1 - 2\times 10 ^ {-7}$。然后根据没有横插边和前向边的性质，求出其它每个点是否合法。

**性质**：点 $x$ 到它子树内的点有且仅有一条简单路径，因为一个点向下走的唯一途径是树边，向上走的唯一途径是返祖边。除了一定存在的一直向下走的简单路径，如果还有别的简单路径，则这条路径一定走了一条返祖边。这条返祖边一定指向 $x$ 的祖先，因为如果指向 $x$ 子树内的结点，那么由于走返祖边之前必须经过该结点，所以路径经过了重复点，不合法。而从 $x$ 的祖先回到目标点必须再次经过 $x$，也不合法，所以这样的简单路径不存在。这说明，如果 $x$ 到 $y$ 有大于一条简单路径，那么 $y$ 不在 $x$ 的子树内，且这样的简单路径一定有且仅有一步从 $x$ 的子树内跳了出去。

称一条返祖边 $u\to v$ 覆盖 $u, v$ 的树上简单路径的除了 $v$ 以外的所有点，一个点可以通过覆盖它的返祖边离开它的子树。

如果点 $x$ 被大于一条边覆盖，那么它就有两种方法离开子树，然后向下走到它的父亲，即 $x$ 到 $x$ 的父亲的简单路径数量大于 $1$，$x$ 不合法。

如果 $x$ 只有一种方法离开子树，设对应返祖边为 $u\to v$。因为不存在同时覆盖 $x$ 和 $v$ 的返祖边，也就是覆盖 $v$ 的返祖边的较深一端一定为 $x$ 的祖先，所以从 $x$ 经过 $u$ 走到 $v$ 之后，如果 $v$ 到其它点有大于一条简单路径，因为这样的路径一定会跳出 $v$ 的子树，所以一定不会经过 $x$ 以及它的子树，将 $x$ 到 $v$ 的路径接上这样的路径不会使得路径经过重复点。相反，如果 $v$ 到其它所有点有且仅有一条简单路径，那么容易通过反证法证明 $x$ 同样如此。

又因为一个非根节点必须能够离开子树（否则不满足原图强连通的性质），所以每个点被至少一条返祖边覆盖。因此，点 $x$ 合法的充要条件是：$x$ 为根，或者有且仅有一条返祖边 $u\to v$ 覆盖 $x$ 且 $v$ 合法。

用树上差分维护每个点被多少条边覆盖，再用树形 DP 求出每个点最浅能够跳到哪个祖先，最后从上往下 DP 求出每个点是否合法，时间复杂度 $\mathcal{O}(n + m)$。

总时间复杂度 $\mathcal{O}(c\cdot (n + m))$，其中 $c$ 是随机次数。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ui = unsigned int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using ull = unsigned long long;
using vint = vector<int>;
using vll = vector<ll>;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd(20060130);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + \
  fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
  int x = 0;
  char s = getc();
  while(!isdigit(s)) s = getc();
  while(isdigit(s)) x = x * 10 + s - '0', s = getc();
  return x;
}

#define putc(x) putchar(x)
inline void print(ui x) {
  if(x >= 10) print(x / 10);
  putc(x % 10 + '0');
}

// ---------- templates above ----------

constexpr int N = 1e5 + 5;

int n, m;
int dn, dfn[N], sz[N], fa[N];
vector<int> e[N];
void dfs1(int id) {
  dfn[id] = ++dn, sz[id] = 1;
  for(int it : e[id]) {
    if(dfn[it]) continue;
    dfs1(it), fa[it] = id, sz[id] += sz[it];
  }
}

int cov[N], g[N], f[N];
vector<int> ans;
void dfs2(int id) {
  g[id] = id;
  for(int it : e[id]) {
    if(fa[it] != id) {
      if(dfn[it] < dfn[g[id]]) g[id] = it;
      continue;
    }
    dfs2(it), cov[id] += cov[it];
    if(dfn[g[it]] < dfn[g[id]]) g[id] = g[it];
  }
}
void dfs3(int id) {
  f[id] = cov[id] >= 2 || f[g[id]];
  if(!f[id]) ans.push_back(id);
  for(int it : e[id]) {
    if(fa[it] == id) dfs3(it);
  } 
}

void mian() {
  cin >> n >> m;
  for(int i = 1; i <= n; i++) e[i].clear();
  for(int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
  }
  for(int _ = 1; _ <= 100; _++) {
    int u = rd(1, n);
    for(int i = 1; i <= n; i++) {
      dfn[i] = cov[i] = f[i] = fa[i] = 0;
    }
    dn = 0, dfs1(u);
    int flg = 0;
    for(int i = 1; i <= n; i++) {
      for(int it : e[i]) {
        if(fa[it] == i) continue;
        if(dfn[i] < dfn[it] || dfn[i] >= dfn[it] + sz[it]) flg = 1;
        else cov[i]++, cov[it]--;
      }
    }
    if(flg) continue;
    dfs2(u), ans.clear(), dfs3(u);
    if(ans.size() * 5 >= n) {
      sort(ans.begin(), ans.end());
      for(int it : ans) cout << it << " ";
      cout << "\n";
      return;
    }
    else break;
  }
  cout << "-1\n";
}


bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin); 
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T = 1;
  cin >> T;
  while(T--) mian();
  fprintf(stderr, "%d ms\n", int(1e3 * clock() / CLOCKS_PER_SEC));
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：_quasar_ (赞：7)

考试的时候有个部分分：保证 $1$ 一定合法。

我们可以思考一下这个东西有什么用。可以发现，对于这部分分，如果可以从合法的 $1$ 号点开始找到所有的合法点的话。那么满分做法就只需要找到一个合法点，然后得到其他的合法点即可。

$\frac{1}{5}$ 这个数字显然在暗示我们跑随机化，不妨考虑随机 $k$ 次，每次暴力判断这个点是否合法。如果 $k$ 次都不合法的话直接输出 $-1$ 即可。错误的概率为 $(\frac{4}{5})^{k}$ 。

首先考虑如何判断一个点是否合法。十分显而易见的是，当以这个点为根，跑出一个生成树后，必须满足剩下的非树边一定都是返祖边。

（这个判返祖边的时候写急了写了个带 $\log$ 的做法 /kk

然后接下来就是怎么着其他的合法点。

一个点 $u$ 合法必须满足，$u$ 的子树里没有两条以上连出去的边。显然如果有两条边的话，那么路径数必然大于 $1$ ，因此不合法。接着，$u$ 对于子树内部的点是满足条件的，那么子树外部的点怎么判呢？

显然是必须要满足，$u$ 子树内部的越过 $u$ 的边，跳出来后，是可以一路跳到根的。

令这条边跳到的点是 $v$ ，**那么这个 $v$ 必须合法**_（考场上栽这里了，得注意）_，不然的话，从 $u$ 开始，沿着这条唯一的跳出去的边，走到 $v$ 点后，要么到不了整棵树，要么将存在多条路径。

于是只需要维护一下每个点的这条跳出去的边即可，因为最多一条才是合法的，所以维护起来十分方便。

随机的话不建议直接 `rand` ，交了几次都没过去。建议直接对着 $id$ 数组 `random_shuffle` 。

```cpp
const int N=4e5+5;
const int LogN=19;

int n,m;

int cnt,head[N];
struct Edge {int nxt,to;} G[N];
inline void addedge(int u,int v) {
	if(u==v) return ;
	G[++cnt]=(Edge){head[u],v},head[u]=cnt;
}
inline void clear_edge() {
	memset(head,0,sizeof(head)),cnt=0;
}

bool tree_edge[N],vis[N];
int dep[N],fa[N][LogN];

void dfs(int u,int pre) {
	vis[u]=true,fa[u][0]=pre,dep[u]=dep[pre]+1;
	lep(i,1,18) fa[u][i]=fa[fa[u][i-1]][i-1];
	
	for(int i=head[u],v;i;i=G[i].nxt)
		if(v=G[i].to,!vis[v]) tree_edge[i]=true,dfs(v,u);
}

inline int kth(int u,int k) {
	lep(i,0,18) if((k>>i)&1) u=fa[u][i];
	return u;
}
inline bool check(int rt) {
	lep(i,1,m) tree_edge[i]=false;
	lep(i,1,n) vis[i]=false;
	dfs(rt,0);
	lep(i,1,n) if(!vis[i]) return false;

	lep(u,1,n) for(int i=head[u],v;i;i=G[i].nxt) if(!tree_edge[i]) {
		v=G[i].to;		
		if(dep[v]>=dep[u]) return false;
		if(kth(u,dep[u]-dep[v])!=v) return false; // 显然这里写的很丑 /wq
	}
	return true;
}

bool able[N];
int top,sta[N];
std::vector <int> god[N];

void init(int u) {
	god[u].clear(),able[u]=true;
	for(int i=head[u],v;i;i=G[i].nxt) if(v=G[i].to,tree_edge[i]) {
		if(dep[v]<dep[u]) continue;
		init(v);
		for(int t:god[v]) if(t!=u) god[u].pb(t);
	} else god[u].pb(v);
	if(god[u].size()>1) able[u]=false;
}
void solve(int u) {
	for(int t:god[u]) able[u]&=able[t];	
	for(int i=head[u],v;i;i=G[i].nxt) if(v=G[i].to,tree_edge[i]) {
		if(dep[v]<dep[u]) continue;
		solve(v);
	}
	if(able[u]) sta[++top]=u;
}

int u,v,id[N];
inline void solve() {
	clear_edge();
	
	IN(n),IN(m);
	lep(i,1,m) IN(u),IN(v),addedge(u,v);

	lep(i,1,n) id[i]=i;
	std::random_shuffle(id+1,id+1+n);

	lep(t,1,99) {
		int u=id[t];
		if(check(u)) {
			top=0,init(u),solve(u);
			std::sort(sta+1,sta+1+top);
			if(top*5>=n) {lep(i,1,top) printf("%d ",sta[i]); puts("");}
			else puts("-1");
			return ;
		}
	}
	return puts("-1"),void();
}

int main() {
	srand(time(0)),srand(rand());
	int T; IN(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：bzzltl (赞：5)

### 思路

首先考虑如何判断某点是否为好点，根据这个图是**有向强连通图**这一个性质，可以先想到如果该点处有一个横叉边或者前向边，则该点一定不是好点（这个地方比较好理解，可以自己画图理解）。

然后考虑以该点为根的子树内，其返祖边恰好满足**强连通**这一条件，否则的话这个子树内总会有点可以不同的返祖边到到达它的父亲结点。

找到好点之后考虑根据好点的性质来快速找到其他好点。

设 $x$ 为找到的好点，建立以 $x$ 结点为根的dfs树。

考虑一个非根结点 $y$，它可以是好点的条件是仍然是

- 没有的前向边和横叉边

- 以该点为根的子树内返祖边恰好满足**强连通**

可以发现，如果 $y$ 通过返祖边连向的点 $z$ 是好点，那么所有条件是一定满足的。

也就是说，如果 $z$ 是好点，那么 $y$ 一定为好点。

证明：

因为 $z$ 是好点。

所以在 $z$ 的子树内，$y$ 可以在 $z$ 遍历时的路径上，这个路径有且仅有 $1$ 条。

在 $z$ 的子树外，$y$ 只能通过 $z$ 向上遍历，而 $z$ 是个好点，所以 $y$ 在 $z$ 子树外的路径也是有且仅有一条。

这个题可以随机找点，判断其是否为好点，如果为好点，选为根结点，开始查找答案，如果不是好点就继续随机找点。

关于题目的细节见代码注释。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;
const int IM=2147483647;
const long long LLM=9223372036854775807;

inline int read()
{
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

int T,n,m,cnt,flag,pr[N],tot[N],dep[N],head[N];
bool in[N],vis[N];
vector<int>g[N],t[N],ans,tp;
//in[]表示当前节点是否在子树内,vis[]表示有没有遍历过,后面统计答案的部分作用为记录是否是好点
//t存树,pr存最高祖先,g[u]存所有祖先
//tot[u]是一个差分数组,具体作用写在下面

struct node{
	int v,nex;
}edge[N];

void add(int v,int u)
{
	edge[++cnt]=(node){v,head[u]};
	head[u]=cnt;
}

void init()
{
	cnt=0;
	for(int i=1;i<=n;i++) tot[i]=head[i]=0;
	ans.clear();
	tp.clear();
	for(int i=1;i<=n;i++) tp.push_back(i);
}

void dfs(int u)
{
	in[u]=vis[u]=true;
	for(int i=head[u];i;i=edge[i].nex)
	{
		int v=edge[i].v;
		if(vis[v]&&!in[v]) flag=1;//判断横叉边或者前向边(这个遍历过并且u在v上方或者u与v在不同子树)
		else if(!in[v]) dep[v]=dep[u]+1,dfs(v),t[u].push_back(v);//一般情况
		else g[u].push_back(v),pr[u]=(dep[v]>dep[pr[u]])?pr[u]:v;//返祖边,添加u的祖先并更新u节点的最高祖先
//		if(!vis[v]&&in[v])最后面这个else不能用这个条件代替,因为在一个子树里面也可以有返祖边,所以直接else
//		又想了想，这玩意不可能成立好吧
	}
	in[u]=false;
}

bool check(int u)
{
	for(int i=1;i<=n;i++) g[i].clear(),t[i].clear(),tot[i]=vis[i]=in[i]=pr[i]=0;
	flag=0;
	dep[u]=1;
	dep[0]=n+1;//因为后续有一步更新最高祖先的操作,可能有的人没祖先
	dfs(u);
	return !flag;
}

void calc(int u)
{
	for(int v:t[u])
	{
		calc(v);
		tot[u]+=tot[v];//差分数组的一般用法
		if(dep[pr[u]]>dep[pr[v]]) pr[u]=pr[v];//更新最高祖先
	}
}

void solve(int u)
{
	if(tot[u]==1&&vis[pr[u]]) vis[u]=true;
//	这里面条件的意思分别是:只有一条返祖边 返祖边连向的点是好点
	for(int v:t[u]) solve(v);
}

signed main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();
		init();//初始化
		for(int i=1;i<=m;i++) add(read(),read());
		int rot=-1;
		random_shuffle(tp.begin(),tp.end());//这个函数是用来打乱数组的
		for(int i=0;i<min(101,(int)tp.size());i++)
		{
			if(check(tp[i]))
			{
				rot=tp[i];
				break;
			}
		}
		if(rot==-1) {puts("-1");continue;}
		for(int u=1;u<=n;u++) for(int v:g[u]) tot[u]++,tot[v]--;
//		这里考虑为什么要tot[v]--
//		tot是一个差分数组,用来帮助维护u->v这一段路径中的所有点有几条路径可以回到顶点
		calc(rot);
		for(int i=1;i<=n;i++) vis[i]=false;//这里的vis[]数组要来维护哪个结点是好点了
		vis[rot]=true;
		solve(rot);
		for(int i=1;i<=n;i++) if(vis[i]) ans.push_back(i);
		if ((int)ans.size()*5<n){puts("-1");continue;}
		for(int i:ans) printf("%d ",i);
		puts("");
	}
	return 0;
}
```

---

## 作者：极寒神冰 (赞：5)

容易发现一个点是 interesting 的当且仅当以它为根的 dfs 树只有树边和返祖边，没有横叉边。于是就有一个 $O(n)$ 判断一个点是不是 interesting 的做法。

随机选择 $\min(n,100)$ 个点检查这些点是不是 interesting 的，如果没有 interesting 的点，那么可以直接输出 $-1$，正确率高达 $1-0.8^{100}$。否则我们找到了一个 interesting 的点 $x$，建出以 $x$ 为根的 dfs 树。

考虑判断一个非根节点 $y$ 是否 interesting，一个必要的条件是：它的子树内的点必须总共只引出一条到 $y$ 的祖先节点的返祖边（一定会有一条因为整张图是强连通的），因为如果有多条的话，就存在了两条从 $y$ 走向 $y$ 的父亲的路径。然后考虑只有一条的情况，设这条返祖边指向 $z$，那么 $y$ 是 interesting 的当且仅当 $z$ 是 interesting 的。

必要性：如果 $z$​ 不是 intersting 的话，假如 $z$ 到某一个点 $x$ 有两种路径，那么 $y$ 到 $x$ 也一定有两种路径。

充分性：$z$ 到所有点只有一种方法，而 $y$ 到它子树内只有一种方法，而 $y$ 出子树的途径都要通过 $z$ ，因此 $y$ 到所有点只有一种方法。

因为 $z$ 是 $y$ 的祖先，于是从根往叶子递推一下即可。

出边可以用 `multiset` 维护，合并直接启发式合并，注意每次合并完之后要把所有到 $y$ ​的出边删掉。


```cpp
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 rand_num(seed);  
uniform_int_distribution<long long> dist(0,1223344556616251);  // ¸ø¶¨·¶Î§
int n,m,rt;
vector<int>e[111111],g[111111],fz[111111],ans;
multiset<int>st[111111];
int fa[111111],bg[111111],en[111111],tim;
int dp[111111],ffa[111111];
int hson[111111];

void dfs1(int u)
{
    bg[u]=++tim;
    for(int v:e[u]) if(!bg[v]) fa[v]=u,dfs1(v);
    en[u]=tim;
}
int check(int rt)
{
    tim=fa[rt]=0;
    R(i,1,n) bg[i]=0;
    dfs1(rt);
    R(u,1,n) 
    {
        for(int v:e[u]) if(fa[v]^u) if(bg[v]>bg[u]||en[v]<en[u]) return 0;
    }
    return 1;
}
void dfs2(int u)
{
    hson[u]=-1;
    for(int v:g[u]) 
    {
        dfs2(v);
        if(!~hson[u]||st[v].size()>st[hson[u]].size()) hson[u]=v;
    }
    if(~hson[u]) swap(st[u],st[hson[u]]);
    for(int v:g[u]) if(v^hson[u])
    {
        for(auto it=st[v].begin();it!=st[v].end();it++) st[u].insert(*it);
    }
    for(int v:fz[u]) st[u].insert(v);
    while(st[u].find(u)!=st[u].end()) st[u].erase(st[u].find(u));
    if((int)st[u].size()>1) ffa[u]=0;
    else if((int)st[u].size()==1) ffa[u]=*st[u].begin();  
}
void dfs3(int u)
{
    if(ffa[u]==-1) dp[u]=1,ans.pb(u);
    else if(!ffa[u]) dp[u]=0;
    else {dp[u]=dp[ffa[u]];if(dp[u])ans.pb(u);}
    for(int v:g[u]) dfs3(v); 
}
signed main()
{
    for(int _=read();_;_--)
    {
        n=read(),m=read();
        R(i,1,n) e[i].clear();
        int u,v;
        R(i,1,m) u=read(),v=read(),e[u].pb(v);
        rt=0;
        for(int i=1;i<=100&&(!rt);i++) 
        {
            static int u;
            u=dist(rand_num)%n+1;
            if(check(u)) rt=u;
        }
        //printf("rt:%lld\n",rt);
        if(!rt) {puts("-1");continue;}
        ans.clear();
        R(i,1,n) g[i].clear(),fz[i].clear(),st[i].clear(),ffa[i]=-1,dp[i]=0;
        R(u,1,n) 
        {
            if(u^rt) g[fa[u]].pb(u);
            for(int v:e[u]) if(fa[v]^u) fz[u].pb(v); 
        }
        dfs2(rt);
        dfs3(rt);
        if((int)ans.size()*5<n) {puts("-1");continue;}
        sort(ans.begin(),ans.end());
        for(int x:ans) writesp(x);puts("");
    }
}
```



---

## 作者：nullqtr_pwp (赞：1)

省流：$20\%$ 的限制是没用的，存在找到任意一个好点的确定性做法。


- 图论问题经常需要转化为树上问题。

先考虑判定一个点是否是好的：我们找出任意一棵 $\text{dfs}$ 外向树，要求任意非树边均为返祖边。

然后考虑先找出来任意一个好点，或者宣称不存在好点。找一个好点 $u$ 的话，结合一下本题的性质，我们只需要先看是否有至少 $20\%$ 的点是好的，那么直接随机化 $c=100$ 次直到找到一个好点。如果找不到，我们宣称好点个数 $<20\%$，正确率是 $1-(4/5)^c$。联想一下 P9052 的 trick。事实上你可以确定性的找一个好点。注意到 $\text{dfs}$ 树的叶子必然有入度为 $1$，所以可以用一个队列维护所有入度 $1$ 的点，然后对于入度 $1$ 的点 $u$，考虑将 $v\to u$ 之中，所有 $u$ 的出边合并到 $v$ 上，不需要去除重边，但要删去自环。最终状态如果所有点入度 $\ge 2$ 就是不存在好点的，否则最终只剩下一个点，显然这就是其中一个好点。那么启发式合并维护所有入边即可，这样的复杂度是 $\mathcal O((n+m)\log n)$。搭配并查集维护你缩出来每个大点是好写的。

考虑如何由一个好点 $u$ 求得所有的好点，那么换根到 $v$ 的话，相当于保留 $u$ 的 $\text{dfs}$ 树中 $v$ 的子树。一个显然的必要条件是，对于 $v$ 子树跳出其子树的返祖边数量恰好为 $1$。$=0$ 会导致其无法离开该子树，$>1$ 会导致其路径不唯一。那么考虑该路径的终点为 $w$。那么我们继续判定，就要求 $w$ 子树跳出该子树的返祖边数量也恰好是 $1$，找出下一个是 $w'$，递归执行该过程，如果每一步都合法，最后停留到 $w=1$ 就说明 $v$ 是一个好点。这是一个递归定义，我们只需要判定 $w$ 是否为好点。找出 $(v,w)$ 的话，可以树上差分求出返祖边对于每条树边的覆盖次数，$cov_{e}=1$ 是一个必要条件。然后从下往上递推一个，返祖边中任意一个最浅的下端点在该子树，其对应的上端点即可。这一部分时间复杂度 $\mathcal O(n+m)$。结合第一部分找好点，时间复杂度 $\mathcal O((n+m)\log n)$。

写的时候注意一下，这个题一车细节。


[提交记录。](https://codeforces.com/contest/1361/submission/303191405)

---

## 作者：OtterZ (赞：0)

# 题意

给一个强连通有向图，定义当一个点到其他任意点只有一条无环路径时此点为特殊点，要求如果特殊点数小于总点数的 $20\%$ 则输出 $-1$，否则输出所有特殊点。

# 第一个特殊点

其实找第一个点只需要会判定，因为当我们需要输出特殊点时，特殊点数至少为所有点数的 $20\%$，这意味着随机选 $T$ 次时成功率至少为 $1 - (80\%)^T$，当 $T\ge 93$ 时 $1 - (80\%)^T > 1 - 10 ^ {-9}$，也就是几乎能过。这里请用靠谱的随机数生成器，详见[大佬的博客](https://codeforces.com/blog/entry/61587)。

判定时我们知道，当一个点为特殊点时，以这个点开始跑整张图，不会出现除树边和回边外的其他边，这么判定是 $\operatorname{O}(n + m)$ 的。

# 至于其他的特殊点

我们将第一个发现的特殊点作为起点，得到只有树边和回边得图，我们保留树边形成树形图，对于每个不是起点的点，设从起点通过树边到这个点之前需要经过的点为红点，这个点通过树边能到的点为蓝点，则：

1. 存在至少回边从蓝点到红点，则这个点不是特殊点。
2. 否则恰好有一条边，这条边指向的红点若为特殊点，则这个点为特殊点，否则这个点不是特殊点。

对每个点找到从蓝点到红点的边数和这些边指向的红点中从起点到它的边数最小的点，前者可以在树上做差分，后者为强连通分量算法的一部分，两者都是 $\operatorname{O}(n + m)$ 的，和前面的随机找第一个特殊点一起是 $\operatorname{O}(T(n + m))$ 的，可以轻松过。 

找出所有的特殊点后，把答案按要求输出即可。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rp(chrono :: steady_clock :: now().time_since_epoch().count());
int n,m,val[100009],back[100009],ans,r,dep[100009];
bool vis[100009],ins[100009],ing[100009];
vector<int>e[100009];
bool pd(int v){
	vis[v] = true,ins[v] = true;
	//printf("%d in\n",v);
	for(int i = 0; i < e[v].size(); i ++){
		if(!vis[e[v][i]]){
			if(!pd(e[v][i]))
				return false;
        }
		else if(!ins[e[v][i]]){
           // if(n == 7)
            //    printf(" %d %d\n",v,e[v][i]);
			return false;
        }
	}
	ins[v] = false;
//	printf("%d ot\n",v);
	return true;
}
void srh1(int v){
//	printf("%d in\n",v);
	ins[v] = true;
	back[v] = v;
	for(int i = 0; i < e[v].size(); i ++){
		if(!ins[e[v][i]]){
			dep[e[v][i]] = dep[v] + 1;
			srh1(e[v][i]);
			val[v] += val[e[v][i]];
			if(dep[back[e[v][i]]] < dep[back[v]])
				back[v] = back[e[v][i]];
		}
		else{
			if(dep[e[v][i]] < dep[back[v]])
			back[v] = e[v][i];
			val[v] ++,val[e[v][i]] --;
		}
	}
	//printf("%d ot\n",v);
	ins[v] = false;
}
void srh2(int v){
	//printf("%d %d %d\n",v,val[v],back[v]);
	ins[v] = true;
	ing[v] = (v == r || (val[v] == 1 && ing[back[v]]));
	ans += ing[v];
	for(int i = 0; i < e[v].size(); i ++){
		if(!ins[e[v][i]]){
			srh2(e[v][i]);
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		r = ans = 0;
		for(int i = 1; i <= n; i ++){
			ing[i] = vis[i] = ins[i] = false;
			dep[i] = val[i] = back[i] = 0;
			e[i] = vector<int>(0);
		}
		for(int i = 1; i <= m; i ++){
			int u,v;
			scanf("%d %d",&u,&v);
			e[u].emplace_back(v);
			//e[v].emplace_back(u);
		}
		for(int i = 1; i <= 97; i ++){
			int o = rp() % n + 1;
            //if(n == 7){
            //    printf("%d %d\n",o,pd(o));
           // }
            for(int j = 1; j <= n; j ++)
					vis[j] = ins[j] = false;
			if(pd(o) == true){
				r = o;
				break;
			}
            //for(int j = 1; j <= n; j ++)
			//		vis[j] = ins[j] = false;
		}
		if(!r){
			puts("-1");
			continue;
		}
		//r = 3;
		srh1(r);
		srh2(r);
		if(ans * 5 >= n){
			//printf("%d\n",ans);
			for(int i = 1; i <= n; i ++){
				if(ing[i])
					printf("%d ",i);
			}
			puts("");
		}
		else
			puts("-1");
	}
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/5gfv6od0.png)

---

## 作者：Purslane (赞：0)

# Solution

有向图的问题也可以考虑放到 DFS 树上做。

本题的“概率”，显然想要你通过若干次随机来确定一个点是否合法。

不过根据 nullptr 大神的题解，我们可以使用一个很神奇的技巧确定性的求：考虑一个入度为 $1$ 的点 $u$，其入点为 $v$。如果他就是我们钦定的根的话，那么它在一个大小至少为 $2$ 的环上，所以其出度也是 $1$，那么它和它的出点显然合法性相同，所以可以将其删掉；如果不是，那这个点本质是没用的，可以将其与 $v$ 合并（注意及时删掉自环）。很容易在单 $\log$ 的复杂度内完成这个过程。

求出一个合法的根之后，考虑建出一个 DFS 树（平时不用 DFS 树考虑有向图问题是因为其结构过于复杂。但是本题保证了根到每个点只有 $1$ 条简单路径，所以非树边只有返祖边）。

考虑一个点。如果有 $2$ 条以上或者没有返祖边跨过它（题目保证了强联通所以一定有），显然没救了；否则，他如果想走到子树外，必须经过唯一的边跳出去，然后转化为新的问题。随便 DP 一下就行，复杂度线性。

我最终还是实现了随机化。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int tc,n,m,flg=1,vis[MAXN],in[MAXN],dp[MAXN],dep[MAXN],pre[MAXN];
vector<int> G[MAXN],T[MAXN];
void dfs(int u) {
	vis[u]=in[u]=1;
	for(auto v:G[u]) {
		if(vis[v]) flg&=in[v];
		else T[u].push_back(v),dep[v]=dep[u]+1,dfs(v);	
	}
	return in[u]=0,void();
}
int check(int u) {
	ffor(i,1,n) T[i].clear(),vis[i]=0;
	flg=1,dfs(u);
	return flg;
}
pair<int,int> mn[MAXN];
void dfs2(int u) {
	mn[u]={n+1,0};
	for(auto v:G[u]) if(dep[v]<dep[u]) mn[u]=min(mn[u],{dep[v],v}),pre[u]++,pre[v]--;
	for(auto v:T[u]) dfs2(v),mn[u]=min(mn[u],mn[v]);
	return ;
}
void dfs3(int u) {
	for(auto v:T[u]) dfs3(v),pre[u]+=pre[v];
	return ;
}
void dfs4(int u) {
	if(!dp[u]&&pre[u]==1) dp[u]=dp[mn[u].second];
	for(auto v:T[u]) dfs4(v);
	return ;	
}
vector<int> solve(int rt) {
	ffor(i,1,n) T[i].clear(),vis[i]=dp[i]=pre[i]=0;
	dep[rt]=0,dfs(rt),dp[rt]=1;
	dfs2(rt),dfs3(rt),dfs4(rt);
	vector<int> ans;
	ffor(i,1,n) if(dp[i]) ans.push_back(i);
	return ans;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>tc;
	while(tc--) {
		cin>>n>>m;
		ffor(i,1,n) G[i].clear();
		ffor(i,1,m) {
			int u,v;
			cin>>u>>v,G[u].push_back(v);
		}
		mt19937 myrand(time(NULL));
		int ans=-1;
		ffor(tc,1,100) {
			int rt=myrand()%n+1;
			if(check(rt)) ans=rt;	
		}
		if(ans==-1) cout<<-1<<'\n';
		else {
			vector<int> res=solve(ans);	
			if(res.size()*5>=n) {
				for(auto id:res) cout<<id<<' ';
				cout<<'\n';
			}
			else cout<<-1<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：SegTree (赞：0)

第一次自己想出来 $3000$。但是我想出来的是一个 $O(c(n+m)+n\log^2 n)$ 的做法。

考虑一个 $O(n^2)$ 做法，只需要判断以 $u$ 为根时非树边都是返祖边即可。

首先 $20\%$ 说明这是一个随机化题，如果 $\ge20\%$ 说明随个 $100$ 来次随不出来基本上就是 $-1$，现在只需要考虑找到一个合法点之后怎么做。

那么就把以它为根的 dfs 树跑出来，那么如果一个节点为根的子树中往外连至少两条边，由于它们都是返祖边，其中较深的祖先一定存在两条路径到达，而如果一条等价于 check 它可到达的那个祖先是否合法。

那做法就显然了。跑一个 dsu on tree 求一下子树内有多少个往外连的，如果有 $1$ 个就记录连哪个，然后按照 dfn 序顺着推一遍就行。

代码：<https://codeforces.com/contest/1361/submission/293213725>。

---

