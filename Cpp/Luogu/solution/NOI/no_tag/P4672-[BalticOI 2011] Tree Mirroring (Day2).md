# [BalticOI 2011] Tree Mirroring (Day2)

## 题目描述

对于一棵树 $T$，并复制一棵与 $T$ 同构的树 $S$。构造一个新的图 $T'$，新图 $T'$ 通过合并 $T$ 和 $S$ 中相应的非根叶节点得到。我们称这样的图为树之镜像图。

给定一个图 $G$，你需要判断 $G$ 是否是树之镜像图。

## 样例 #1

### 输入

```
7 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1```

### 输出

```
NO```

## 样例 #2

### 输入

```
6 6
1 2
2 3
2 4
3 5
4 5
5 6```

### 输出

```
YES```

## 样例 #3

### 输入

```
22 28
13 8
8 1
1 22
1 12
1 14
13 18
13 4
4 20
20 7
13 15
15 3
15 9
9 16
9 19
22 5
12 5
14 5
5 11
11 6
18 6
7 10
10 17
17 6
3 21
21 6
16 2
19 2
2 21```

### 输出

```
YES```

# 题解

## 作者：hezlik (赞：14)

**题目大意**：给定一张 $n$ 个点 $m$ 条边的无向图，判定这张无向图是否是一张树之镜像图。若一张图可以由两棵一模一样的树共用叶节点得到，则称之为树之镜像图。

注意除根外，所有叶节点即度数为 $1$ 的点必须全部合并。

**数据范围**：
* $3\leq n,m\leq 10^5$。

考虑将问题分成两步解决：
1. 找到被合并的叶节点。
2. 依靠叶节点对图进行判定。

我们先完成第一步。

考虑找到图上的某一个环，并去掉环上的所有边。那么剩下的图将会是这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/b96t0vag.png)

~~我绝对不会告诉你我贴的官方题解图。~~

我们发现现在图中的连通块最多只包含两个环上的点。如果有包含三个以上环点的连通块可以直接判掉。

再考虑一个包含两个环点的连通块。我们分别让这两个环点 $x,y$ 作为两棵树的根，那么对于任意一个叶节点，其到 $x,y$ 的距离必然相同。

那么我们只需要找到任意一个环并将其所有边删去，再找到删去后一个包含两个环点的连通块，并分别从这两个环点出发 bfs，即可完成第一步。

但是我们发现，图中不一定存在环，环上的边删去后也可能不存在包含两个环点的连通块。

对于图中不存在环的情况，则必然存在一个度为 $1$ 的点。而根据题意，显然度为 $1$ 的点只能有 $0$ 或 $2$ 个。如果是 $2$ 个点的话，则我们可以直接从这两个点出发进行 bfs。

而对于存在环但删去环边不存在一个连通块包含两个环点的情况，如果图中不存在两个度为 $1$ 的点，则图只能是一个单独的环。而图是一个环的情况下，我们直接按照点数的奇偶性判定即可。

再来完成第二步。

首先我们需要确保叶子两边都是树。虽然看起来有很多东西要判，但其实我们可以直接判断点数与边数的关系，应满足这样一个关系式：
$$
n-2+c=m
$$

其中 $c$ 为叶子的个数。

之后我们考虑从叶子往两个方向分别 bfs。容易发现此时叶子之间的对应关系已经被确定，所以上面的非叶节点之间的对应关系也必然确定，直接判断即可。

时间复杂度 $O(n+m)$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N=100000;

int n,m;
struct side{
  int y,next,tag;
}e[N*2+9];
int lin[N+9],cs;

void Ins(int x,int y){e[++cs].y=y;e[cs].next=lin[x];lin[x]=cs;}
void Ins2(int x,int y){Ins(x,y);Ins(y,x);}

int deg[N+9];

void into(){
  scanf("%d%d",&n,&m);
  cs=1;
  for (int i=1;i<=m;++i){
    int x,y;
    scanf("%d%d",&x,&y);
    Ins2(x,y);
    ++deg[x];++deg[y];
  }
}

int ans;

bool Check_ans_deg(){  //判断图中度数为 1 的点的数量是否合法
  int cnt=0;
  for (int i=1;i<=n;++i) cnt+=deg[i]==1;
  return !cnt||cnt==2;
}

int vis[N+9];

void Dfs_vis(int k){
  vis[k]=1;
  for (int i=lin[k];i;i=e[i].next)
    if (!vis[e[i].y]) Dfs_vis(e[i].y);
}

bool Check_ans_connect(){  //判断图是否连通，应该没必要
  int cnt=0;
  for (int i=1;i<=n;++i)
    if (!vis[i]) ++cnt,Dfs_vis(i);
  for (int i=1;i<=n;++i) vis[i]=0;
  return cnt==1;
}

bool Check_ans_circle(){  //判断图是一个单独的环的情况
  for (int i=1;i<=n;++i)
    if (deg[i]^2) return 1;
  ans=n&1^1;
  return 0;
}

int cir[N+9],cc;
int sta[N+9],cst;

bool Dfs_cir(int k,int fa){  //找到任意一个环
  int res=0;
  vis[k]=1;
  sta[++cst]=k;
  for (int i=lin[k];i;i=e[i].next){
    int y=e[i].y;
    if (y==fa) continue;
    if (vis[y]){
      for (int i=cst;i>=1;--i){
        cir[++cc]=sta[i];
        if (sta[i]==y) break;
      }
      res=1;
    }else if (Dfs_cir(y,k)) res=1;
    if (res) break;
  }
  --cst;
  return res;
}

int bel[N+9];

void Dfs_bel(int k,int b){
  bel[k]=b;
  for (int i=lin[k];i;i=e[i].next)
    if (!e[i].tag&&!bel[e[i].y]) Dfs_bel(e[i].y,b);
}

int rot[2];

void Get_rot(){  //找到可以作为根的两个点，放入 rot[0/1] 中
  //如果有两个度数为 1 的点，直接用它们作为根
  int cr=0;
  for (int i=1;i<=n;++i)
    if (deg[i]==1) rot[cr++]=i;
  if (cr) return;
  //否则考虑找到一个环，然后断掉所有环边，再找包含两个环点的连通块
  Dfs_cir(1,0);
  for (int i=1;i<=cc;++i){
    int x=cir[i],y=cir[i%cc+1];
    for (int i=lin[x];i;i=e[i].next)
      if (e[i].y==y) e[i].tag=e[i^1].tag=1;
  }
  for (int i=1;i<=cc;++i)
    if (!bel[cir[i]]) Dfs_bel(cir[i],cir[i]);
  for (int i=1;i<=cc;++i)
    if (cir[i]^bel[cir[i]]) rot[0]=cir[i],rot[1]=bel[cir[i]];
}

int dis[2][N+9];
queue<int>q;

void Bfs_dis(int id,int st){
  dis[id][st]=1;q.push(st);
  for (;!q.empty();){
    int t=q.front();q.pop();
    for (int i=lin[t];i;i=e[i].next)
      if (!dis[id][e[i].y]) dis[id][e[i].y]=dis[id][t]+1,q.push(e[i].y);
  }
}

int leaf[N+9],tag[N+9];

void Get_leaf(){  //找叶子
  Bfs_dis(0,rot[0]);
  Bfs_dis(1,rot[1]);
  for (int i=1;i<=n;++i)
    if (!(leaf[i]=dis[0][i]==dis[1][i])) tag[i]=dis[0][i]>dis[1][i];
  //将点分为三类
  //leaf[i]=1 表示 i 是叶子
  //tag[i] 表示 i 不是叶子的情况下，i 属于哪棵树
}

int Dfs_leaf_cnt(int k){
  int res=1;
  for (int i=lin[k];i;i=e[i].next)
    if (leaf[e[i].y]&&!vis[e[i].y]) res+=Dfs_leaf_cnt(e[i].y);
  return res;
}

bool Check_leaf_cnt(){  //根据点数与边数的关系判断图被叶子分开后，是不是两棵树
  int cnt=0;
  for (int i=1;i<=n;++i) cnt+=leaf[i];
  return n-2+cnt==m;
}

int ord[2][N+9],bfs[2][N+9],co[2];
int fa[2][N+9];

void Bfs_ord(){
  for (int i=1;i<=n;++i)
    if (leaf[i]) q.push(i);
  for (;!q.empty();){
    int t=q.front(),tt=tag[t];q.pop();
    if (leaf[t]) ord[0][bfs[0][t]=++co[0]]=t,ord[1][bfs[1][t]=++co[1]]=t;
    else ord[tt][bfs[tt][t]=++co[tt]]=t;
    for (int i=lin[t];i;i=e[i].next){
      int y=e[i].y;
      --deg[y];
      if (bfs[tag[y]][y]) continue;
      fa[tag[y]][t]=y;
      if (deg[y]<=1) q.push(y);
    }
  }
}

bool Check_ans(){  //最后的判断
  //先跑出一个bfs序，同时给两棵树上的点重新标号，再利用树上的父子关系判定
  Bfs_ord();
  for (int i=1;i<=co[0];++i)
    if (bfs[0][fa[0][ord[0][i]]]^bfs[1][fa[1][ord[1][i]]]) return 0;
  return 1;
}

void Get_ans(){
  if (!Check_ans_deg()) return;
  if (!Check_ans_connect()) return;
  if (!Check_ans_circle()) return;
  Get_rot();
  Get_leaf();
  if (!Check_leaf_cnt()) return;
  ans=Check_ans();
}

void work(){
  Get_ans();
}

void outo(){
  puts(ans?"YES":"NO");
}

int main(){
  into();
  work();
  outo();
  return 0;
}
```

---

## 作者：Monomial (赞：8)

有趣思维题。

找根判定看上去不太好做，我们考虑找叶子判定。

如果我们已经有了一个叶子，那么直接 01bfs，如果这个叶子到一个点有两条边不交的最短路（在 bfs 时表现为被松弛两次），那么在图合法的情况下，这个点必定也是一个叶子。接下来我们只需判定剩下的是否是两个连通块并且它们是否同构即可。这个条件是充要的。

稍微困难一点的是之前这个找叶子的过程，这个需要一点观察，下图是一个示例，其中 $3,4$ 是原树的叶子，假设点 $1,6$ 向外面有边。

![](https://cdn.luogu.com.cn/upload/image_hosting/6hw5aa84.png)

我们观察 $3,4$ 两个点的性质。容易发现其为一条其中点均满足 $deg=2$ 的极长链的中点。实际上对于所有合法图中的叶子节点，由对称性可得这个条件都是满足的。

那么我们直接找一条这样的链，就一定能找到叶子吗？并不是，考虑如下情形（原树的一部分）。

![](https://cdn.luogu.com.cn/upload/image_hosting/3meknf13.png)

其中 $2,3,4$ 这 $3$ 个点构成了一条 $deg=2$ 的极长链，其中 $3$ 为中点，但 $3$ 并不是一个叶子。所以我们需要更强的判定。

假设极长链的两个端点向外分别和 $u,v$ 有边，我们声称在合法情况下，至少有一个无序二元组 $(u,v)$ 出现了 $\geq 2$ 次，这时符合条件的极长链的中点均为叶子。

考虑反证。我们假设有 $e$ 条链，每条链对应的无序二元组为 $(u_{i},v_{i})$，在原树中简化为 $p_{i}$，其互不相同。由于 $p_{i}$ 不在链上，那么 $deg_{p_{i}} > 2$。所以除去这些叶子对 $p_{i}$ 的贡献 $1$，剩下的贡献和应当 $\geq 2e$。而我们考虑最优的造成贡献的方式只有每次合并两个 $p_{i}$ 的连通块，这里只会合并 $e-1$ 次，每次对合并的两个分别造成 $1$ 的贡献，总贡献就是 $2e-2 < 2e$，所以我们之前提出的结论是成立的。

我们刚刚的这个做法是基于第一个图中 $1,6$ 向外面有边，对于无边的情况，即原图为一个环，那么树的形态应当是一条链，直接特判即可。

那么我们整道题的做法即为，先拉出所有 $deg=2$ 的极长链，然后用 $(u,v)$ 判定找叶子，搜出所有叶子，树同构判定（注意不合法情况可能有环，要特殊处理）。代码很好写，实现优秀可以做到 $\mathcal{O}(n+m)$。

---

## 作者：_LPF_ (赞：6)

一个有趣的做法。

[Tree Mirroring](https://www.luogu.com.cn/problem/P4672)

> 给定一张无向图，判断它是否是“树镜像图”。
>
> “树镜像图”定义为：可以由一棵树复制一次，再将对应叶子节点合并得到的图。

如果确定了对称的两个树的树根，判断是否合法可以 $O(n)$ 解决。

具体方法为，找到对称轴上的节点（到两个根最短距离相等的点），不断对应到父亲（基于每个节点父亲唯一）。

如果能一直对应上去就合法。

如果枚举两个树根一次判定，复杂度为 $O(n^3)$。

稍加思考可以发现，如果有解，那么任意非对称轴上的**对应节点**都能作为一对根。

而且对称轴上的节点度数一定为 $2$，且一定连接两个**对应节点**，故可以只枚举某个在对称轴上的点，复杂度 $O(n^2)$。

之后的主要优化方向在于减少判定次数，而非加快判定速度。

不难发现，图中一定有环，且任意一个环都由对称的两部分构成，而且一定是偶环。

那就可以想到，利用度数做匹配，只有一个点**能把这个环剖成两个轴对称的部分**（Hash 判断）时，才进行判定。

具体代码可以[看这里](https://loj.ac/s/1491768)，但是实际上复杂度并不正确，但是个人认为也并不好卡，实际也跑的飞快。

当然也不能止步于此，因为还有更优秀的性质。

如果环的大小为 $n$，那么特判掉，只有 $n=m$ 时图合法。否则一定能找到任意一个环外一点 $o$。

如果图合法，不难发现 $o$ 到环一定有且只有两条路径，而且路径与环的交点恰好是对称的对应点！

这样就只需要找环&判定一次了，时间复杂度严格 $O(n)$。

注意在实现时要时刻 `return false`，因为给定的图是任意图，不能纯粹当成合法图想当然的进行一些统计。

还有就是虽然第二种方法才是严格复杂度，但是实际上完全打不过第一种，世事难料（

代码放的第二种：

```cpp
#include<bits/stdc++.h>
typedef long long LL;
#define rep(i, a, b) for(int i = (a); i <= (b); i ++)
#define per(i, a, b) for(int i = (a); i >= (b); i --)
#define Ede(i, u) for(int i = head[u]; i; i = e[i].nxt)
using namespace std;

int read() {
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? - 1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

#define eb emplace_back
typedef vector<int> vec;
const int N = 1e5 + 10;
int n, m; vec g[N];

int s, t, par[N]; bool vis[N], flag = false;

void dfs(int u, int fa) {
	vis[u] = true, par[u] = fa;
	for(int v : g[u]) if(v != fa) {
		if(vis[v]) {if(! flag) s = u, t = v, flag = true; continue;}
		dfs(v, u);
	}
}

int tot, cir[N];

void getcir() {
	dfs(1, 0);
	rep(i, 1, n) if(! vis[i]) {puts("NO"); exit(0);}
	if(!  flag) {puts("NO"); exit(0);}
	while(s != t) cir[++ tot] = s, s = par[s];
	cir[++ tot] = t;
	if(tot & 1) {puts("NO"); exit(0);}
	if(tot == n) {puts(n == m ? "YES" : "NO"); exit(0);}
}

int dis[2][N], fat[2][N], mat[N];

void dfs(int u, int fa, int o) {
	fat[o][u] = fa;
	if(dis[0][u] == dis[1][u]) return;
	for(int v : g[u]) if(v != fa) {
		if(fat[o][v]) {flag = false; return;}
		dfs(v, u, o);
		if(! flag) return;
	}
}

bool check(int s, int t) {
	rep(i, 1, n) dis[0][i] = dis[1][i] = mat[i] = fat[0][i] = fat[1][i] = 0;
	
	queue<int> q;
	dis[0][s] = 1, q.push(s);
	while(! q.empty()) {int u = q.front(); q.pop(); for(int v : g[u]) if(! dis[0][v]) dis[0][v] = dis[0][u] + 1, q.push(v);}
	dis[1][t] = 1, q.push(t);
	while(! q.empty()) {int u = q.front(); q.pop(); for(int v : g[u]) if(! dis[1][v]) dis[1][v] = dis[1][u] + 1, q.push(v);}
	flag = true, dfs(s, 0, 0); if(! flag) return false;
	flag = true, dfs(t, 0, 1); if(! flag) return false;
	rep(i, 1, n) if(dis[0][i] == dis[1][i]) mat[i] = i, q.push(i);
	while(! q.empty()) {
		int u = q.front(); q.pop();
		int v = mat[u];
		int nu = fat[0][u], nv = fat[1][v];
		if(! nu || ! nv) {
			if(! nu && nv) return false;
			if(! nv && nu) return false;
			continue;
		}
		if(g[nu].size() != g[nv].size()) return false;
		if(! mat[nu]) mat[nu] = nv, q.push(nu); else if(mat[nu] != nv) return false;
	}
	rep(i, 1, n) mat[mat[i]] = i;
	rep(i, 1, n) if(! mat[i]) return false;
	return true;
}

bool valid[N];

bool solve() {
	rep(i, 1, n) vis[i] = false;
	rep(i, 1, tot) vis[cir[i]] = true;
	int o = 0;
	rep(i, 1, n) if(! vis[i]) {o = i; break;}
	queue<int> q; q.push(o), valid[o] = true;
	while(! q.empty()) {
		int u = q.front(); q.pop();
		if(vis[u]) continue;
		for(int v : g[u]) if(! valid[v]) valid[v] = true, q.push(v);
	}
	int s = 0, t = 0, cnt = 0;
	rep(i, 1, n) if(vis[i] && valid[i]) {
		if(++ cnt > 2) return false;
		if(cnt == 1) s = i; else t = i;
	}
	if(cnt != 2) return false; else return check(s, t);
}

int main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read(), v = read();
		g[u].eb(v);
		g[v].eb(u);
	}
	int s = 0, t = 0, cnt = 0;
	rep(i, 1, n) if((int) g[i].size() == 1) {
		if(++ cnt > 2) return puts("NO"), 0;
		if(cnt == 1) s = i; else t = i;
	}
	if(cnt) {
		if(cnt != 2) return puts("NO"), 0;
		return puts(check(s, t) ? "YES" : "NO"), 0;
	}
	getcir(); if(solve()) puts("YES"); else puts("NO");
	return 0;
}
```



---

## 作者：basince (赞：2)

大家怎么写的这么长（

看到题我们很容易想到大概有两种方式去判断：

1. 找到两个根，然后一通操作。
2. 找到一个叶子，然后一通操作。

但这个根要找两个，时间上不是很允许。所以考虑用叶子判断。

先把链和环的特判了。

容易发现一个叶子肯定在一个环上，先找出一个环。这时我们发现，对于一棵树上两个点的路径是唯一的，而且从随便一个不在环上的点走到的第一个在环上的点一定是对称的！

那么观察一下合法图的形式，可以发现他就是一个点双。我们直接对他开耳分解，因为已经找到一对对称的点了，接下来随便搞搞就可以判断了。

具体的，分别从两个点 $bfs$ 出发找到所有点到他的距离，设为 $f_{0,i},f_{1,i}$。那么对一对对称点 $(i,j)$，必有 $f_{0,i}=f_{1,j}$，我们在开耳分解时判一下所有点的对称性即可。最后判一下对称的两边都是树就行了（依据树的点边数量关系）。

```cpp
inline void bfs(ri st,ri o){
	fo(i,1,n)vis[i]=0;
	vis[st]=1;
	ri h=0,t=1;q[1]=st;
	while(h<t){
		ri x=q[++h];
		for(auto y:G[x]){
			if(vis[y])continue;
			f[o][y]=f[o][x]+1;
			g[o][y]=x;vis[y]=1;
			q[++t]=y;
		}
	}
}
inline int chk(ri x,ri y){
	bfs(x,0);bfs(y,1);
	ri s=0,tt=0;
	fo(i,1,n)vis[i]=0;
	fo(i,1,n){
		if(f[0][i]==f[1][i]){
			ri u=g[0][i],v=g[1][i];
			while(u&&v&&!vis[u]&&!vis[v]){
				vis[u]=vis[v]=++tt;
				u=g[0][u];v=g[1][v];
			}
			if(vis[u]!=vis[v])return 0;
			++s;
		}
	}
	return n+s-2==m;
}
inline void dfs(ri x,ri fa){
	vis[x]=1;st[++st[0]]=x;
	for(auto y:G[x]){
		if(y==fa)continue;
		if(vis[y]){
			while(st[st[0]+1]!=y){
				bz[st[st[0]]]=1;
				--st[0];
			}
			pd=1;return;
		}
		dfs(y,x);
		if(pd)return;
	}
}
inline void dfs2(ri x,ri fa){
	if(bz[x]==1){
		a[++t]=x;
		return;
	}
	bz[x]=2;
	for(auto y:G[x]){
		if(y!=fa&&bz[y]!=2)dfs2(y,x);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	fo(i,1,m){
		ri x,y;scanf("%d%d",&x,&y);
		G[x].pb(y);G[y].pb(x);
		++du[x];++du[y];
	}
	fo(i,1,n)if(du[i]==1)a[++t]=i;
	if(t){
		if(t==2)puts(chk(a[1],a[2])?"YES":"NO");
		else puts("NO");return 0;
	}
	dfs(1,0);
	fo(i,1,n)if(!vis[i]){
		dfs2(i,0);
		if(chk(a[1],a[2]))puts("YES");
		else puts("NO");return 0;
	}
	puts(n&1?"NO":"YES");
}
```

---

## 作者：phigy (赞：1)

### 前言

一个可以直接把所有镜像关系找出来的方法。

### 正文

合法的图要么是链，要么有且仅有一个极大的点双。

容易发现一个点是叶子当且仅当它可以是这个点双的一个耳分解中的一个耳的中点，并且在图里面镜像对称的两点在耳上也是对称的，因为两个叶子在每棵树里面有且仅有一条简单路径。

因此我们直接对这个点双做耳分解就可以知道每个点的对应点，特别的初始的环的对应用第一个耳的头和尾去判一下，然后就没了，需要特判单个环和链的情况。

由于耳分解模板较少，以下给出一个模板供于参考：

```cpp
int n,m;
vector<int>E[MAXN];
int dfn[MAXN],id[MAXN],low[MAXN],fa[MAXN],son[MAXN],dfx;/// son 表示 dfs 树上和自己 low 相等的儿子
void Tarjan(int x)
{
    id[dfn[x]=low[x]=++dfx]=x;
    for(int v:E[x])
    {
        if(v==fa[x]) {continue;}
        if(!dfn[v]) {fa[v]=x;Tarjan(v);if(low[v]<=low[x]) {low[x]=low[v];son[x]=v;}}
        else                           {if(dfn[v]<low[x]) {low[x]=dfn[v];son[x]=0;}}
    }
}
vector<vector<int>>ans;
void Low_Chain(int x)
{
    vector<int>tmp,vec;
    if(x!=1) {tmp.push_back(fa[x]);}
    while(son[x])
    {
        tmp.push_back(x);
        for(int v:E[x]) {if(v!=son[x]&&fa[v]==x) {vec.push_back(v);}}
        x=son[x];
    }
    tmp.push_back(x);
    for(int v:E[x]) {if(fa[v]==x) {vec.push_back(v);}}
    tmp.push_back(id[low[x]]);
    if(ans.size()<=1) {ans.push_back(tmp);}
    for(int v:vec) {Low_Chain(v);}
}
void Ear_Decomposition()
{
    Tarjan(1);
    Low_Chain(1);
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言
细节很多的一道思维题。

# Part 2：正文
上来一个直观的感受是，如果我们能找到两个根，我们就能通过 bfs 算距离把树划分为两半，然后检查两边的树是否同构。更进一步的，我们发现如果能找到一对对应点，我们也能够把树划分成两半。

现在的问题是怎么找到这对对应点。考虑环的形成过程，我们发现，对于一个合法的图，当我们删去一个环的时候，整个图会断成若干个连通块，且每个连通块中最多包含两个环上的点，这两个点一定是对应点。原因是一个环环上的边一定是原树上的若干条对称树边，而父亲到儿子的路径唯一，若合法一定不会出现断开环后一对有父子关系且在环上的点出现在同一连通块中。

现在的问题有两个，一个是特殊的情况，另一个是如何判定树同构。

首先考虑后者，对两边 bfs 重标号，检查父子关系即可。

然后考虑前者，分情况考虑。

- 没有环。

  此时整个图是一条单链，我们判断点数奇偶性即可。

- 不存在有两个环上的点的连通块。

  考虑此时图的形态，一定是一个大环上套了一堆链。我们继续讨论。

  + 不存在两个度数为 $1$ 的点。

    意味着图是一个大环，直接判断点数奇偶性即可。

  + 存在两个度数为 $1$ 的点。

    把这两个点当根跑上面的判定即可。

当然还有一些情况，比如两边不是树，两边点数不同等等，也要一一判掉，前者可以判点数、叶子数和边数的关系，后者 bfs 的时候检查一下即可。

最后讲两个常见分数对应的错误，56 分的可以检查一下重标号部分最后判父亲节点是否有误，72 分的也是检查重标号部分（其实 72 分相当于是输出 NO 了）。


# Part 3：代码
代码写的很乱，将就着看一下，可能还有一些没考虑到的 case。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=1e5+7;
int n,m,ins[N],pre[N],mrk[N],col[N],inc[N],tag[N],dis[N],beg,lfc,deg[N];
int bfn[N][2],anc[N][2],ord[N][2];
vector<int>ver[N];
stack<int>stk;
vector<pair<int,int>>g[N];
pair<int,int>rt;
queue<int>q;
bool dfs(int u,int F){
	// Debug("===(%d,%d)===\n",u,F);
	if(ins[u])return stk.push(u),beg=u,1;
	stk.push(u);ins[u]=1;
	for(auto [v,i]:g[u]){
		if(v==F)continue;
		// Debug("%d %d\n",v,i);
		pre[v]=i;
		if(dfs(v,u))return 1;
	}
	stk.pop();
	return 0;
}
void label(int u,int c){
	col[u]=c;
	for(auto [v,i]:g[u])if(col[v]!=c&&!mrk[i])label(v,c);
}
void divide(){
	q.push(rt.first);q.push(rt.second);
	memset(dis,0x3f,sizeof(dis));
	tag[rt.first]=1,tag[rt.second]=2;
	dis[rt.first]=dis[rt.second]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(auto [v,i]:g[u])
			if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,tag[v]=tag[u],q.push(v);
			else if(dis[v]==dis[u]+1)tag[v]|=tag[u];
	}
}
void number(){
	for(int i=1;i<=n;i++)if(tag[i]==3)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		// printf("%d %d %d %d\n",u,tag[u],tag[u]&1,tag[u]&2);
		if(tag[u]&1){
			bfn[u][0]=++ord[0][0];
			ord[ord[0][0]][0]=u;
		}
		if(tag[u]&2){
			bfn[u][1]=++ord[0][1];
			ord[ord[0][1]][1]=u;
		}
		for(auto [v,i]:g[u]){
			deg[v]--;
			if(bfn[v][tag[v]-1]||tag[v]==3)continue;
			anc[u][tag[v]-1]=v;
			if(deg[v]<=1)q.push(v);
		}
	}
}
int main(){
	read(n,m);
	for(int i=1,u,v;i<=m;i++)read(u,v),g[u].eb(v,i),g[v].eb(u,i),deg[u]++,deg[v]++;
	bool flg=dfs(1,0);
	int all=0;
	if(!flg){
		if(n&1)printf("YES\n");
		else printf("NO\n");
		return 0;
	}
	for(int i=1;i<=n;i++)if(deg[i]==1)all++;
	if(all==1||all>=3){printf("NO\n");return 0;}
	if(all==0){
		do{int u=stk.top();stk.pop();mrk[pre[u]]=1;inc[u]=1;}while(stk.top()!=beg);
		for(int i=1;i<=n;i++)if(!col[i])col[0]++,label(i,col[0]);
		// for(int i=1;i<=n;i++)Debug("%d ",col[i]);
		for(int i=1;i<=n;i++)if(inc[i])ver[col[i]].eb(i);
		for(int i=1;i<=col[0];i++)if(ver[i].size()==2){rt=make_pair(ver[i][0],ver[i][1]);}
		if(rt==make_pair(0,0)){
			if((n&1)^1)printf("YES\n");
			else printf("NO\n");
			return 0;
		}
	}else{
		for(int i=1;i<=n;i++)if(deg[i]==1){if(rt.first)rt.second=i;else rt.first=i;}
	}
	divide();
	// for(int i=1;i<=n;i++)Debug("%d ",tag[i]);
	for(int i=1;i<=n;i++)lfc+=(tag[i]==3);
	if(n-2+lfc!=m){
		printf("NO\n");
		return 0;
	}
	number();
	if(ord[0][0]!=ord[0][1]){
		printf("NO\n");
		return 0;
	}
	for(int i=1;i<=ord[0][0];i++){
		if(bfn[anc[ord[i][0]][0]][0]!=bfn[anc[ord[i][1]][1]][1]){
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	return 0;
}
```

---

