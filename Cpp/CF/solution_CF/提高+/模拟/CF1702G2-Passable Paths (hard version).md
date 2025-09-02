# Passable Paths (hard version)

## 题目描述

This is a hard version of the problem. The only difference between an easy and a hard version is in the number of queries.

Polycarp grew a tree from $ n $ vertices. We remind you that a tree of $ n $ vertices is an undirected connected graph of $ n $ vertices and $ n-1 $ edges that does not contain cycles.

He calls a set of vertices passable if there is such a path in the tree that passes through each vertex of this set without passing through any edge twice. The path can visit other vertices (not from this set).

In other words, a set of vertices is called passable if there is a simple path that passes through all the vertices of this set (and possibly some other).

For example, for a tree below sets $ \{3, 2, 5\} $ , $ \{1, 5, 4\} $ , $ \{1, 4\} $ are passable, and $ \{1, 3, 5\} $ , $ \{1, 2, 3, 4, 5\} $ are not.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1702G2/0977138472fa4ec56403c02976f275aa67a6c22b.png)Polycarp asks you to answer $ q $ queries. Each query is a set of vertices. For each query, you need to determine whether the corresponding set of vertices is passable.

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5
5
3
3 2 5
5
1 2 3 4 5
2
1 4
3
1 3 5
3
1 5 4```

### 输出

```
YES
NO
YES
NO
YES```

## 样例 #2

### 输入

```
5
1 2
3 2
2 4
5 2
4
2
3 1
3
3 4 5
3
2 3 5
1
1```

### 输出

```
YES
NO
YES
YES```

# 题解

## 作者：Semorius (赞：13)

## 思路

题意：判断是否存在一条链包含树上给定点集。

考虑把 $1$ 当做树的根，将无根树转化为有根树。

考虑这样一个性质：若存在满足条件的最短链，则点集中深度最深的点 $u$ 是该链的一个端点，点集中距离 $u$ 最远的点 $v$ 是该链的另一端点。

>证明：若点 $u$ 不是链的端点，则 $u$ 的子孙节点中还存在点集中的点，以保证 $u$ 被包含在可行最短链中，这与 $u$ 深度最深矛盾。若 $v$ 不是点集中距离 $u$ 最远的点，则对于 $u$ 与 $v$ 简单路径上的所有点（包含端点）到 $u$ 的距离均小于等于 $v$ 到 $u$ 的距离，此时链不能包含点集中距离 $u$ 最远的点，矛盾。

之后只要判断点集中其余 $k-2$ 个点是否均在 $u$ 和 $v$ 的简单路径上就可以了。

考虑分三类：

1. 如果点 $i$ 的深度小于 $u$ 与 $v$ 的 $\text{lca}$ 的深度，则不可行。

1. **否则**如果点 $i$ 在 $u$ 或 $v$ 任一点到 $1$ 的路径上，则可行。

1. 其余情况均不可行。

每个点利用倍增 $\text{LCA}$ 判断即可。

时间复杂度 $O(q \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int SIZE = 200005;
int n, tot, st;
vector<int> e[SIZE];
int a[SIZE], d[SIZE], f[SIZE][30];
 
inline int rd(){
	int f = 1, x = 0;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}
 
void dfs(int x, int fa){
	f[x][0] = fa; d[x] = d[fa] + 1;
	for(int i = 1; i <= 23; i++){
		f[x][i] = f[f[x][i-1]][i-1];
	}
	for(int i = 0; i < e[x].size(); i++){
		int y = e[x][i];
		if(y == fa) continue;
		dfs(y, x);
	}
}
 
int LCA(int x, int y){
	if(d[x] < d[y]) swap(x, y);
	for(int i = 23; i >= 0; i--){
		if(d[f[x][i]] >= d[y]) x = f[x][i];
		if(x == y) return x;	
	}
	for(int i = 23; i >= 0; i--){
		if(f[x][i] != f[y][i]){
			x = f[x][i], y = f[y][i];
		}
	}
	return f[x][0];
}
 
int main(){
	n = rd();
	for(int i = 1; i < n; i++){
		int x = rd(), y = rd();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1, 0);
	int q = rd();
	for(int i = 1; i <= q; i++){
		int tot = rd();
		st = 0; bool flag = true;
		for(int j = 1; j <= tot; j++){
			a[j] = rd();
			if(d[a[j]] > d[st]) st = a[j];
		}
		int z = 0, jl, lc;
		for(int j = 1; j <= tot; j++){
			if(a[j] == st) continue;
			if(z == 0){
				z = a[j];
				lc = LCA(a[j], st);
				jl = d[a[j]] + d[st] - 2*d[lc];
			}
			else{
				int xx = d[a[j]] + d[st] - 2*d[LCA(a[j], st)]; 
				if(xx > jl){
					jl = xx;
					z = a[j];
					lc = LCA(a[j], st);
				}
			}
		}
		for(int j = 1; j <= tot; j++){
			if(a[j] == z || a[j] == st) continue;
			if(d[a[j]] < d[lc]){
				flag = false;
				break;	
			} 
			else{
				int xx = LCA(a[j], st), yy = LCA(a[j], z);
				if(!(xx == a[j] || yy == a[j])){
					flag = false;
					break;	
				} 
			}
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：2018ljw (赞：4)

题意：给定一棵树，每次问一个点集是否均在某一条链上。数据范围 $2\times10^5$。

首先，任意点集按树上路径连边后肯定仍为一棵树，因此整个点集在某一条链上等价于连边后形成的树为一条链。我们考虑如何判断一棵树是一条链。

先证一个结论：若至少有三个点度数为 $1$，则原树必有一个点度数 $\ge3$。反之亦然。

> 任取一个度为 $1$ 的点为根，任取两个叶节点求 $lca$。根节点度为 $1$，故 $lca$ 不为根，故 $lca$ 到根、两个叶各有一条路径，即度数 $\ge3$。反过来任取度数 $\ge3$ 的点为根，则根节点的每个子树至少会有一个叶节点。

充要条件：所有节点度数 $\le2$ 且两两连通。必要性显然。

充分性：只有一个点显然成立；对于至少两个点的情况，先构造出有两个点的树，考虑每次新增点时必定向两个度为 $1$ 的点之一连边，然后自己成为新的叶子或根。显然最后是成链的。

直接对给定点集建立虚树，判断有无度数 $\ge 3$ 的点即可。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=1<<30;
int n,k;
int hed[500001],net[800001],ver[800001],d[500001],tot;
int fa[500001][20],lg[500001],dep[500001];
int cnt,pos[500001],a[500001];
bool cmp(int x,int y){
	return pos[x]<pos[y];
}
void add(int x,int y){
	ver[++tot]=y;
	net[tot]=hed[x];
	hed[x]=tot;
	d[x]++;
	d[y]++;
}
void swap(int &x,int &y){
	int z=x;
	x=y;
	y=z;
}
void dfs1(int x){
	int i;
	pos[x]=++cnt;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(fa[x][0]==y)continue;
		fa[y][0]=x;
		dep[y]=dep[x]+1;
		dfs1(y);
	}
}
void ycl(){
	int i,j;
	for(i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(i=1;i<=lg[n];i++)for(j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int i;
	for(i=lg[n];i>=0;i--){
		int p=fa[x][i];
		if(dep[p]<dep[y])continue;
		x=p;
	}
	if(x==y)return x;
	for(i=lg[n];i>=0;i--){
		int p=fa[x][i],q=fa[y][i];
		if(p==q)continue;
		x=p;
		y=q;
	}
	return fa[x][0];
}
int top,q[2000001];
int dfs(int x){
	int i,rs=d[x];
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(dep[y]<dep[x])continue;
		int res=dfs(y);
		if(res>rs)rs=res;
	}
	hed[x]=0;
	d[x]=0;
	return rs;
}
int build(){
	//构建虚树并返回根节点
	int i;
	tot=0;top=0;
	sort(a+1,a+k+1,cmp);
	q[++top]=a[1];
	for(i=2;i<=k;i++){
		int r=lca(q[top],a[i]);
		if(r==q[top]){
			q[++top]=a[i];
			continue;
		}
		while(top>1&&dep[r]<dep[q[top-1]]){
			add(q[top-1],q[top]);
			top--;
		}
		if(r!=q[top]){
			add(r,q[top]);
			top--;
			if(r!=q[top])q[++top]=r;
		}
		q[++top]=a[i];
	}
	while(top>1){
		add(q[top-1],q[top]);
		top--;
	}
	return q[1];
}
int main(){
	int i;
	scanf("%d",&n);
	for(i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dep[1]=1;
	dfs1(1);
	ycl();
	dfs(1);//清空原树信息
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&k);
		for(i=1;i<=k;i++)scanf("%d",&a[i]);
		int rt=build();
		int res=dfs(rt);
		if(res>=3)printf("NO\n");
		else printf("YES\n");
	}
}

```

---

## 作者：苏联小渣 (赞：3)

这题可以用树剖做，比较无脑。

考虑两个点 $x,y$，满足 $x,y$ 是这个点集里面的两个端点。端点的定义为，在 $x,y$ 各自的子树（不包含 $x,y$）中不存在点集中的点。

此时若从 $x$ 到 $y$ 的最短简单路径中，恰好包含了所有点集中的点，那这个点集就是合法的。原因很简单，因为如果合法，那么这条链一定会覆盖 $x,y$ 这两个点，而 $x,y$ 这两个点又可以唯一确定一条链，满足时即两者互为充要条件。

但是有一些特殊情况需要考虑：

- 存在 $>2$ 个端点，一定不合法。原因显然。

- 只有一个端点，一定合法。此时从端点往上即为深度单调递减的一条链。

我们把点集中的点设定一个权值 $1$，然后上树剖即可。记得每次询问完后要清空。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define lc(x) x<<1
#define rc(x) x<<1|1
int n, p, x, y, q, m, st, ed, a[200010], h[200010], f[200010], dep[200010], siz[200010];
int son[200010], dfn[200010], top[200010], seg[800010];
struct node{
	int x, y, next;
}d[400010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
void dfs1(int x, int fa){
	f[x] = fa, siz[x] = 1, dep[x] = dep[fa] + 1;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		dfs1(y, x);
		siz[x] += siz[y];
		if (siz[y] > siz[son[x]]) son[x] = y;
	}
}
void dfs2(int x, int tp){
	dfn[x] = ++dfn[0];
	top[x] = tp;
	if (!son[x]) return ;
	dfs2(son[x], tp);
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == f[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}
void pushup(int k){
	seg[k] = seg[lc(k)] + seg[rc(k)];
}
void modify(int k, int l, int r, int x, int p){
	if (l == r){
		seg[k] += p;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(lc(k), l, mid, x, p);
	else modify(rc(k), mid+1, r, x, p);
	pushup(k);
}
int query(int k, int l, int r, int x, int y){
	if (x <= l && r <= y) return seg[k];
	int mid = l + r >> 1, ret = 0;
	if (x <= mid) ret += query(lc(k), l, mid, x, y);
	if (y > mid) ret += query(rc(k), mid+1, r, x, y);
	return ret;
}
int queryQ(int x, int y){
	int ret = 0;
	while (top[x] != top[y]){
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ret += query(1, 1, n, dfn[top[x]], dfn[x]);
		x = f[top[x]];
	}
	if (dep[x] < dep[y]) swap(x, y);
	ret += query(1, 1, n, dfn[y], dfn[x]);
	return ret;
}
int main(){
	scanf ("%d", &n);
	for (int i=1; i<n; i++){
		scanf ("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	scanf ("%d", &q);
	while (q --){
		st = ed = 0;
		scanf ("%d", &m);
		for (int i=1; i<=m; i++){
			scanf ("%d", &a[i]);
			modify(1, 1, n, dfn[a[i]], 1);
		}
		for (int i=1; i<=m; i++){
			if (query(1, 1, n, dfn[a[i]], dfn[a[i]] + siz[a[i]] - 1) == 1){
				if (st){
					if (!ed) ed = a[i];
					else st = 1e9;
				}
				else st = a[i];
			}
		}
		//printf ("now : %d %d\n", st, ed);
		if (st == 1e9){
			puts ("NO");
		}
		else{
			if (!ed) puts ("YES");
			else{
				if (queryQ(st, ed) == m) puts ("YES");
				else puts ("NO");
			}
		}
		for (int i=1; i<=m; i++){
			modify(1, 1, n, dfn[a[i]], -1);
		}
	}
	return 0;
}
```

---

## 作者：Zeardoe (赞：3)

#### CF1702G

LCA 好题。
先理解题意：求给定的一个点集是否包含在一条链中。

考虑放在以 $1$ 为根的树中判断。分析性质：在给定的序列中如果能组成一条链，那么一定不存在一个节点的度为 $3$ 以上。

考虑放在有根树上。为了方便，下文说的“树”表示询问序列涉及到的树。

我们先求出这棵树的根，方法是先按照 DFS 序排序（这样的目的是同一个子树下的节点总是放在一起），再对每对相邻的两个节点求 LCA，对这些 LCA 取深度最大值就是这个链的根节点。
为什么这个是正确的呢？对于根节点，它的相邻子树间一定存在 DFS 序相邻的两个点，那么一定能找到这个根，不会算漏。

分析不能成链的性质：根有三个以上子树，或者不是根的节点有两个以上子树。我们还是用 DFS 序排序过的节点，对于相邻的两个求 LCA。结果有如下两种：
1. LCA 是这两个节点中的一个。说明一个节点是另一个节点的祖先。
2. LCA 不是这两个节点中的一个。说明这两个节点分别在 LCA 的两个分叉上。

第二种很重要，说明找到了一个分叉。判断如果这个 LCA 就是根，那么给它两次机会（因为根可以有两个分叉）。否则直接判 NO。

时间复杂度 $O(qlogq)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 1e9;
vector<int> g[200010];
int lg2[200010], dfn[200010];
int dep[200010], anc[200010][25];
int cnt = 0;
void dfs(int now, int fa) {
    dfn[now] = ++cnt;
    dep[now] = dep[fa] + 1; anc[now][0] = fa;
    f(i, 1, lg2[dep[now]]) {
        anc[now][i] = anc[anc[now][i - 1]][i - 1];
    }
    f(i, 0, (int)g[now].size() -1 ) {
        if(g[now][i] != fa) dfs(g[now][i], now);
    }
}
int lca(int qx, int qy) {
    if(dep[qx] < dep[qy]) swap(qx, qy);
    while(dep[qx] > dep[qy]) {
        qx = anc[qx][lg2[dep[qx]-dep[qy]]];
    }
    if(qx == qy) return qx;
    for(int k = lg2[dep[qx]]; k >= 0; k--) {
        if(anc[qx][k] != anc[qy][k]) {
            qx = anc[qx][k]; qy = anc[qy][k];
        }
    }
    return anc[qx][0];
}
int ask[200010];
bool cmp(int x, int y) {return dfn[x] < dfn[y];}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n; cin >> n;
    f(i, 1, n) lg2[i] = lg2[i - 1] + (1 << lg2[i - 1] == i);
    f(i, 1, n) lg2[i]--;
    f(i, 1, n - 1) {
        int x, y; cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1, 0);
    int q; cin >> q;
    f(i, 1, q) {
        int nn; cin >> nn;
        f(j, 1, nn) cin >> ask[j];
        if(nn == 1) {cout << "YES\n"; continue;}
        sort(ask + 1, ask + nn + 1, cmp);
        int root = lca(ask[1], ask[2]);
        f(j, 1, nn - 1) {
            int k = lca(ask[j], ask[j + 1]);
            if(dep[k] < dep[root]) root = k;
        }
        int mmm = 0;
        f(j, 1, nn - 1) {
            int k = lca(ask[j], ask[j + 1]);
            if(k != ask[j] && k != ask[j + 1]) {
                if(k != root) mmm += 2;
                else mmm++;
            }
        }
        if(mmm >= 2) {cout << "NO\n"; continue;}
        else cout << "YES\n";
    }
    return 0;
}
```

---

## 作者：UperFicial (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1702G2)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16668255.html)。

考虑建立虚树然后再上面搞树形 DP。

于是这道题就变成分讨题。

设 $f_i$ 表示 $i$ 子树内的答案。若 $f_i=1$，表示 $i$ 子树内的特殊点可以被一条链覆盖，且 $i$ 可以作为链的开头。若 $f_{i}=1$，表示 $i$ 子树内的点可以被一条链覆盖，但 $i$ 不能作为链的开头。$f_{i}=-1$ 表示 $i$ 子树内的点不能被一条链覆盖。

设 $x$ 表示 $i$ 儿子中 $f_{j}=1$ 的数量，$y$ 表示 $i$ 的儿子中 $f_{j}=0$ 的数量。如果存在一个孩子 $j$ 使得 $f_{j}=-1$，那么 $f_{i}=-1$。

- 如果 $x+y\ge 3$，不存在一条链同时跨过三个子树，$f_{i}=-1$。

- 如果 $x=1$ 且 $y=1$，同样 $f_{i}=-1$。

- 如果 $x=2$ 且 $y=0$，那么两个儿子可以拼在一起，但 $i$ 不能作为链头，$f_{i}=0$。

- 如果 $y=2$ 且 $y=0$，那么也不存在这样一条链，$f_i=0$。

- 如果 $x=1$ 且 $y=0$，那么 $i$ 可以作为链头，$f_i=1$。

- 如果 $x=0$ 且 $y=1$，那么如果 $i$ 是特殊点，显然不可能构成一条链，$f_{i}=0$；否则答案可以继承，$f_i=0$。

- 如果 $x=0$ 且 $y=0$，根据虚树的性质，$i$ 肯定是叶子节点且是特殊点。那么 $f_i=1$。

注意虚树写法的不同可能会导致空间需要多开一点。

代码：

```cpp
const int MAXN(4e5+10);

int n,m;
struct E{int to,nxt;};
E edge[MAXN<<1];
int head[MAXN],tot;
vector<int>G[MAXN];
int dep[MAXN],par[MAXN][23],dfn[MAXN],t,vir[MAXN],num,rt;
int q[MAXN],cnt,in[MAXN],f[MAXN];
bool flag[MAXN];
int b[MAXN];

inline void add_edge(int u,int v)
{
	edge[++tot].nxt=head[u];
	head[u]=tot;
	edge[tot].to=v;
	return;
}

inline void dfs1(int u,int fa)
{
	par[u][0]=fa,dep[u]=dep[fa]+1,dfn[u]=++t;
	rep(i,1,22) par[u][i]=par[par[u][i-1]][i-1];
	gra(i,u)
	{
		E e=edge[i];
		if(e.to!=fa) dfs1(e.to,u); 
	}
	return;
}

inline int LCA(int x,int y)
{
	if(dep[x]<dep[y]) Swap(x,y);
	rev(k,22,0) if(dep[par[x][k]]>=dep[y]) x=par[x][k];
	if(x==y) return x;
	rev(k,22,0) if(par[x][k]!=par[y][k]) x=par[x][k],y=par[y][k];
	return par[x][0];	
}

inline void init_()
{
	rep(i,1,cnt) flag[q[i]]=false,G[q[i]].clear(),f[q[i]]=0,in[q[i]]=0;
	cnt=0;
	return;
}

inline bool cmp(int x,int y){return dfn[x]<dfn[y];}

inline void build(int k)
{
	num=k;
	sort(vir+1,vir+1+k,cmp);
	rep(i,2,k)
	{
		int g=LCA(vir[i],vir[i-1]);
		if(g!=vir[i]&&g!=vir[i-1]) vir[++num]=g;
	}
	sort(vir+1,vir+1+num);
	num=unique(vir+1,vir+1+num)-vir-1;
	sort(vir+1,vir+1+num,cmp);
	q[++cnt]=vir[1];
	rep(i,2,num)
	{
		int g=LCA(vir[i],vir[i-1]);
		G[g].push_back(vir[i]);
		++in[vir[i]];
		q[++cnt]=g,q[++cnt]=vir[i];
	}
	rep(i,1,cnt)
	{
		int u=q[i];
		if(in[u]==0){rt=u;break;}
	}
	return;
}

inline void dfs(int u)
{
	int tot1=0,tot2=0;
	rep(i,0,(int)G[u].size()-1)
	{
		int v=G[u].at(i);
		dfs(v);
		if(f[v]==-1)
		{
			f[u]=-1;
			return;
		}
		if(f[v]) ++tot1;
		else ++tot2;
	}
	if(tot1==0&&tot2==0) f[u]=1;
	else if(tot1+tot2>=3) f[u]=-1;
	else if(tot1==2) f[u]=0;
	else if(tot2==2) f[u]=-1;
	else if(tot1==1&&tot2==1) f[u]=-1;
	else if(tot1==1) f[u]=1;
	else if(tot2==1)
	{
		if(flag[u]) f[u]=-1;
		else f[u]=0;
	}
	return; 
}

int main()
{
//	freopen("read.txt","r",stdin);
	n=read();
	rep(i,2,n)
	{
		int u=read(),v=read();
		add_edge(u,v),add_edge(v,u);
	}
	dfs1(1,0);
	m=read();
	while(m--)
	{
		int k=read();
		rep(i,1,k) vir[i]=read(),b[i]=vir[i],flag[vir[i]]=true;
		build(k);
		dfs(rt);
		if(f[rt]==-1) puts("NO");
		else puts("YES");
		init_();
		rep(i,1,k) flag[b[i]]=false;
	}
	return 0;
}
/*
Date : 2022/9/8
Author : UperFicial
Start coding at : 7:37
finish debugging at : 8:39
*/
```

---

## 作者：Gorenstein (赞：1)

## Problem

- $q$ 次询问，每次询问给出一个 $k$ 和在树上的 $k$ 个点 $p_i(1\leqslant i\leqslant k)$，问这 $k$ 个点是否在同一条链上。
- $n\leqslant 2\times 10^5$，所有 $k$ 的总和不超过 $2\times10^5$。

## Solution

我们假定 $1$ 是根。首先我们先来思考在同一条链上的情况。我们先取这些点中深度最深的节点，设它为 $x$，它显然是链的一个端点。设另一个端点为 $y$，那么 $y$ 要么是 $x$ 的祖先，要么是不为 $x$ 祖先的点中深度最大的点（这个点显然应当是唯一的）。这是因为当 $y$ 不是 $x$ 的祖先时，这条链可以分为 $y$ 到 $\rm lca$ 和 $x$ 到 $\rm lca$ 两部分，其中后者均为 $x$ 的祖先，前者均不为 $x$ 的祖先。显然 $y$ 在前者的最底端，即 $y$ 至 $\rm lca$ 的点中深度最大的点。

现在假设我们找到了这样的 $x$ 和 $y$，剩下的任务就是判断这 $k$ 个点是否在点 $x$ 和 $y$ 之间的路径上。由于 $\sum k\leqslant 2\times 10^5$，我们可以直接对 $x,y$ 之间的路径进行树上点差分，然后对于每个 $p_i$，查询该点是否被标记。由于是多次查询，故预处理出 $\rm dfs$ 序，用树状数组维护树上差分。

综上所述，我们得到如下解法：
- 对于每次询问，将点按深度排序，然后取出深度最大的点作为 $x$。
- 按深度由大至小判断，找到深度最大的一个点使该点不为 $x$ 的祖先，将该点作为 $y$。这一步可以通过树上倍增实现。
- 差分 $x,y$ 之间的链，并依次查询每一个 $p_i$，判断其是否在链上。

设 $K=\sum k$，该做法时间复杂度为 $O(K\log n)$，与 $q$ 无关，同样适用于 CF1702G1。

---

## 作者：蒟蒻君HJT (赞：1)

## 分享一下最不动脑子的虚树做法。

## 一、题意

给出一棵大小为 $n$ 的树，$q$ 次询问，每次给出一大小为 $m$ 的点集，判断是否存在一条链覆盖这些点，注意这条链可以经过其他点。$n,\sum m \leq 2\times 10^5$ ，$q \leq 10^5$。

## 二、解法

下文中把每次询问中给出的点称为关键点，在图中用红色标出。

先不考虑时间复杂度。怎么判断一个点集能否构成一条链？显然可以分为两种情况：

1.这条链跨过某一个点（显然是所有点的最近公共祖先），两边向下延伸。

2.这条链从某一个点往下不断延伸，这个点也是所有点的最近公共祖先 。

那么通过观察，我们可以发现满足链要求的充分必要条件是：至多有一个点，它的两个子树中存在关键点，且这个点是所有关键点的最近公共祖先；对于其他点，只能有一个子树中存在关键点。

根据这一点性质，我们考虑每次搜索整棵树，并记录 $f_x$ 表示以 $x$ 为根的子树的相关信息：如果整棵子树中不存在关键点，那么 $f_x=0$；如果整棵子树中关键点呈向下延伸的链状，那么 $f_x=1$；如果整棵子树中的关键点无法用向下延伸的一条链来覆盖（只能跨过某个点向两边延伸），那么 $f_x=2$。

转移的过程很简单：

计算 $t=\sum f_v$，$v$ 是 $x$ 的儿子结点；

如果 $t\geq 3$，直接返回 NO；

若 $x$ 是关键点，且存在一个 $f_v=2$，那么就返回 NO；

若 $x$ 是关键点，且 $t=0$，那么 $f_x=1$；

否则令 $f_x=t$。

最后做到根节点的时候如果还没有返回 NO 的话，就表明答案是 YES 了。

容易发现，只有关键点和关键点两两之间的最近公共祖先可能对 $f_x$ 的转移有贡献，其他结点对转移没有影响，符合虚树的应用条件，把虚树建出来就可以了，注意：如果关键点中没有给出 $1$ 号点，则需要手动加入 $1$ 号点。不会虚树的小朋友可以做一下 [P2495 [SDOI2011] 消耗战](https://www.luogu.com.cn/problem/P2495) 。

## 三、代码

```cpp
#include <bits/stdc++.h>
const int N = 250005;
int head[N], nxt[N << 1], ver[N << 1], tot = 0, n;
std::vector<int>VT[N];
int anc[20][N], dep[N], m, K;
int dfn[N], dsum = 0, key[N];
inline bool cmp(int x, int y){
	return dfn[x] < dfn[y];
}
inline int lca(int x, int y){
	if(dep[x] > dep[y]) std::swap(x, y);
	int D = dep[y] - dep[x];
	for(int i = 0; i <= 19; ++i) if(D & (1 << i)) y = anc[i][y];
	for(int i = 19; i >= 0; --i) if(anc[i][x] ^ anc[i][y]) 
		x = anc[i][x], y = anc[i][y];
	return x == y ? x : anc[0][x]; 
}
void dfs1(int x){
	dfn[x] = ++dsum;
	for(int i = 1; i <= 19; ++i) 
		anc[i][x] = anc[i - 1][anc[i - 1][x]];
	for(int i = head[x]; i; i = nxt[i]){
		if(ver[i] == anc[0][x]) continue;
		dep[ver[i]] = dep[x] + 1;
		anc[0][ver[i]] = x;
		dfs1(ver[i]);
	}
	return ;
}
int q[250005];
inline void adde(int x, int y){
	nxt[++tot] = head[x];
	head[x] = tot;
	ver[tot] = y;
	return ;
}
int tp, stk[N];
inline void addedge(int x, int y){
	VT[x].push_back(y);
	return ;
}
void build(){
	tp = 0;
	std::sort(q + 1, q + K + 1, cmp);
	if(!key[1])	stk[++tp] = 1;
	stk[0] = 0;
	VT[1].clear();
	for(int i = 1; i <= K; ++i){
		int Lca = lca(q[i], stk[tp]);
		if(Lca != stk[tp]){
			while(dfn[Lca] < dfn[stk[tp - 1]]){
				addedge(stk[tp - 1], stk[tp]);
				--tp;
			}
			if(dfn[Lca] != dfn[stk[tp - 1]]){
				VT[Lca].clear();
				addedge(Lca, stk[tp]);
				--tp;
				stk[++tp] = Lca;
			}
			else addedge(Lca, stk[tp]), --tp;
		}
		VT[q[i]].clear();
		stk[++tp] = q[i];
	}
	for(int i = 1; i <= tp - 1; ++i)
		addedge(stk[i], stk[i + 1]);
	return ;
}
int dp[200005], ff = 1;
void dfs2(int x){
	dp[x] = 0;
	int gg = 0;
	for(int i = 0; i < VT[x].size(); ++i){
		assert(x != VT[x][i]);
		dfs2(VT[x][i]);
		dp[x] += dp[VT[x][i]];
		if(dp[VT[x][i]] == 2) gg = 1;
	}
	if(key[x] && !dp[x]) dp[x] = 1;
	if(dp[x] > 2) ff = 0;
	if(gg && key[x]) ff = 0;
	return ;
}
int main(){
	scanf("%d", &n);
	int x, y;
	long long z;
	for(int i = 1; i <= n - 1; ++i){
		scanf("%d%d", &x, &y);
		adde(x, y);
		adde(y, x);
	}
	dep[1] = 1;
	dfs1(1);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i){
		scanf("%d", &K);
		for(int j = 1; j <= K; ++j) scanf("%d", &q[j]), key[q[j]] = 1;
		build();
		ff = 1;
		dfs2(1);
		for(int j = 1; j <= K; ++j) key[q[j]] = 0;
		if(ff) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```


---

## 作者：MSqwq (赞：0)

LCA 的题  
题意就是说给你一棵树，再给你一些点，问你这些点是否可以用一条线串起来  
很显然分两种情况进行讨论。  
第一种为链式结构：  
![](https://i.postimg.cc/WbDTzcjK/QQ-20220901034538.png)  

对于第一种情况，只需找到深度最小的点 $u$ 和当前深度最低的点 $v$  ，如果当前点 $x$ 如果 $ \operatorname{LCA}(x,u) = u$ 并且 $\operatorname{LCA}(x,v) = x$ 则  $x$ 在这条链上，注意需要特殊讨论一下 $x$ 为 $u$ 或者 为 $v$ 的情况。  
第二种为桥式结构：  
![](https://i.postimg.cc/v8xGHdGK/QQ-20220901034601.png)    
桥式结构的特征就是关键点为两边点的 LCA 那么我们发现桥式结构其实就是双倍的链式结构，只是他们有公共的 LCA，所以只需讨论，链式结构。如果给定的这些点，形成了大于等于三条链的情况，那么就是 No 反之则为 Yes 。 
这题其实方法很简单，主要在于实现，下面是我的~~又臭又长的~~代码：    
```
#include<cstdio>
#include<cstring>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<map>
#include<queue>
#include<stack>
#include<math.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;

inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0',c=getchar();}
    return x*f;
}
const int N=2e5+10;
int n,m;
int a[N],h[N],fa[21][N];
vector<int>g[N];
void dfs(int x)
{
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(fa[0][x]==v)continue;
		fa[0][v]=x;
		h[v]=h[x]+1;
		dfs(v);
	}
}
int lca(int x,int y)
{
	if(h[x]<h[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(h[x]-h[y]>>i)x=fa[i][x];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
	{
		if(fa[i][x]!=fa[i][y])
		{
			x=fa[i][x];
			y=fa[i][y];
		}
	}
	return fa[0][x];
}

void solve()
{
	bool v[N];
	n=read();
	for(int i=1;i<=n-1;i++)
	{
		int x=read(),y=read();
		g[x].push_back(y);
		g[y].push_back(x);
		v[y]=1;
	}
	int root;
	for(int i=1;i<=n;i++)if(!v[i])root=i;
	dfs(root);
	
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	
	int m=read();
	while(m--)
	{
		int cnt=read();
		bool ans=1;
		int t=0,u,v,lc;
		while(cnt--)
		{
			int x=read();
			if(t==0)
			{
				t=1;
				u=x;
			}
			else if(t==1)
			{
				if(lca(u,x)==u)
				{
					v=x;
					t=2;
				}
				else if(lca(u,x)==x)
				{
					v=u,u=x;
					t=2;
				}
				else 
				{
					v=x;
					t=3;
					lc=lca(u,v);
				}
			}
			else if(t==2)
			{
				if(lca(x,u)==x)u=x;
				else if(lca(x,v)==v)v=x;
				else if(lca(x,u)==u&&lca(x,v)==x){
				}
				else if(lca(u,lca(x,v))==lca(x,v))
				{
					u=x;
					lc=lca(u,v);
					t=3;
				}
				else
				{
					ans=0;
					//break;
				}
			}
			else if(t==3)
			{
				if(lca(x,u)==u)u=x;
				else if(lca(x,v)==v)v=x;
				else if(lca(lc,x)==lc&&lca(u,x)==x){
				}
				else if(lca(lc,x)==lc&&lca(v,x)==x){
				}
				else 
				{
					ans=0;
					//break;
				}
			}
		}	
		if(ans)printf("YES\n");
		else printf("NO\n");		
	}
}

int main()
{
	int T=1;
	while(T--){solve();}
	return 0;
}
```


---

## 作者：王熙文 (赞：0)

## 前言

推荐阅读[我的弱化版题解](https://www.luogu.com.cn/blog/wangxiwen/solution-cf1702g1)，这篇题解的思路基于弱化版题解。

## 思路

发现弱化版时间复杂度的瓶颈在判断 $ax1 \to ax2$ 这条路径是否覆盖集合中所有点。如果可以对于集合中的每个点快速地检查，而不需要预处理出来路径上的所有点，复杂度就降下来了。

一种暴力的方式是，暴力用树剖将 $ax1 \to ax2$ 路径上的点 $+1$，之后对于集合中的每个点单点查询是否为 $1$。但是这样太复杂了。

设 $lca(ax1,ax2)=l$。可以发现，一个点 $u$ 在路径上当且仅当 $l$ 是 $u$ 的祖先且 $u$ 是 $ax1$ 或 $ax2$ 的祖先。原理是，路径上的点都是从 $ax1$ 或 $ax2$ 一直往上跳（直到跳到 $l$）经过的点。通过这个结论，就可以用倍增检查了。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;

int tot=0,var[400010],nxt[400010],head[200010];

void add(int u,int v)
{
	var[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}

int dep[200010],fa[200010][20];

void dfs(int u,int fat)
{
	dep[u]=dep[fat]+1;
	fa[u][0]=fat;
	for(int i=1; i<=19; ++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int i=head[u]; i; i=nxt[i])
	{
		int v=var[i];
		if(v==fat) continue;
		dfs(v,u);
	}
}

int qs[200010];

bool cmp(int x,int y)
{
	return dep[x]>dep[y];
}

bool is_fa(int u,int v) // u 是否是 v 的祖先
{
	int cj=dep[v]-dep[u];
	for(int i=0; i<=19; ++i)
	{
		if(cj>>i&1) v=fa[v][i];
	}
	return u==v;
}

int get_lca(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v); // 默认 u 更深
	int cj=dep[u]-dep[v];
	for(int i=0; i<=19; ++i)
	{
		if(cj>>i&1) u=fa[u][i];
	}
	if(u==v) return u;
	for(int i=19; i>=0; --i)
	{
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i],v=fa[v][i];
		}
	}
	return fa[u][0];
}

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int u,v,k;
	cin>>n;
	for(int i=1; i<=n-1; ++i)
	{
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	cin>>q;
	while(q--)
	{
		cin>>k;
		for(int i=1; i<=k; ++i)
		{
			cin>>qs[i];
		}
		sort(qs+1,qs+k+1,cmp);
		int ax1=qs[1],ax2=0;
		for(int i=2; i<k; ++i)
		{
			if(!is_fa(qs[i],ax1))
			{
				ax2=qs[i];
				break;
			}
		}
		if(!ax2)
		{
			puts("Yes");
			continue;
		}
		int lca=get_lca(ax1,ax2);
		bool flag=1;
		for(int i=1; i<=k; ++i)
		{
			if(!is_fa(lca,qs[i]) || (!is_fa(qs[i],ax1) && !is_fa(qs[i],ax2)))
			{
				flag=0;
				break;
			}
		}
		puts(flag?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路

显然如果确定了路径的两个端点 $x,y$，就可以树剖将树上 $x$ 到 $y$ 的路径上的点权值 $+1$，再判断询问点是否在路径上。

于是钦定深度最大的点为其中一个端点 $x$，另一个端点 $y$ 为询问点中不为 $x$ 的祖先且深度最大的点。如果 $y$ 不存在说明路径为一条从祖先直接到儿子的链，否则按上面的方法判断即可。

注意特判 $m = 1$ 的情况。

## 代码

[code](https://codeforces.com/contest/1702/submission/164028924)

---

## 作者：jucason_xu (赞：0)

### 性质发现

对于一棵无根树而言，讨论它上面的简单路径是比较麻烦的。所以，我们考虑以 $1$ 为根，把它转换成一棵 __有根树__ 进行讨论。

一棵有根树上的简单路径满足什么性质呢？

由于它是一条链，如果向上（也就是前往它的祖先），那么有两种可能， __要么继续向上，要么前往它的另一个儿子__ 。如果向下，那么由于向上的路来的时候已经走过了，就只能选择它的某一个儿子。

不难看出，如果我们从一个点开始走，必然是向上走一些步数，然后选择 __和来时不一样的一个儿子__ ，一步步向下。也就是，它由两条单调上升或下降的链组成，两条链相交于一个点，也是这条路径上深度最小的点，路径上所有点的祖先。而如果询问有解，所有询问的点必然分布在这两条单调链上。

### 思路分析

“路径上所有点的祖先”，这句话提醒我们，LCA 在这里可能有用。我们发现，如果选取同一条链上的两个点，它们的 LCA 是它们中的一个， __如果是不同链上的点，它们的 LCA 就是这两条链的交点__ （也就是最高点）。我们设它为 $m$ 。

若不知道 LCA 是什么或 LCA 怎么求，请移步 [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)并完成和理解此模板题，下文对于 LCA 的应用应当在完全理解 LCA 之后再进行学习，这里不再赘述。

这样，我们可以先假设有解，然后把所有的点分成两类，一类是在第一条链上的，一类是在第二条链上的。

然后，我们对所有 $k$ 个需要查询的点的相邻两个跑 LCA ， __其中 $m$ 必然会在求出的所有 LCA 中出现一次__ 。

如何证明呢？很简单，就是，反证法，假如我们把第一条链上的点标 $1$，第二条链上的点标 $2$， __$m$ 同时属于两类__ ，那么如果标 $2$ 的不和任何标 $1$ 的相邻，标 $1$ 的不和任何标 $2$ 的相邻， __由于每个点都至少具有一个性质__ ，那么如果先在序列中安放所有只标 $1$ 的点，那么接下来我们不能往里面插入任何有 $2$ 的点。因为无论怎么插入都一定会与 $1$ 相邻。

得出结论，在所有需要途径的点中， __至少有一对相邻的点分别在不同的链上__ ，求出的就是 $m$。如何从所有的 LCA 中识别最高点就很简单了， __记录深度最小的 LCA 即可__ 。

那么，接下来就是给点分类了。 __只要有解，一定能把它们分成我们需要的两类__ 。我们可以记录当前两列的最深点，每次判定一个新的点 $q$ 是否在链上，只需要先和第一列的最深点 $p$ 跑 LCA，如果答案是 $p$， __那么更新 $p$ 为 $q$__ （因为 $p$ 是 $q$ 的祖先，$q$ 比 $p$ 更深）。如果答案是 $q$，那么不需操作。以上两种情况中，p都在本链上。如果答案是 $m$， __则到另一条链上进行相似的比对__ 。

但如果第一次比对的答案不是以上三种之一， __或者在另一条链上的答案不是前两种之一__ ，那么这个点不在任何链上，也就是 __不和其他点在同一条简单路径上__ 。则无解。

如果我们跑完以上的算法都没有发现冲突，则一定有解。

### 代码分享

对于 LCA 问题，这里使用的是[倍增算法](https://oiwiki.org/graph/lca/#_5)的板子。

顺带一提，如果不希望大段层次过深的缩进影响逻辑性，可以恰当使用 `continue` 代替 `else` 避免大量条件语句交错的情况出现。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define vt vector
#define pb push_back
typedef long long ll;
int n,q,a,b,k;
vt<int>vv[200005];
int dep[200005],fa[200005][25],lg[200005];
void init(int i,int prv){
	fa[i][0]=prv,dep[i]=dep[prv]+1;
	rp(j,lg[dep[i]])fa[i][j]=fa[fa[i][j-1]][j-1];
	for(auto j:vv[i])if(j!=prv)init(j,i);
}
int lca(int x, int y) {
	if(dep[x]<dep[y])swap(x,y);
	while(dep[x]>dep[y])x=fa[x][lg[dep[x]-dep[y]]-1];
	if(x==y)return x;
	per(k,0,lg[dep[x]]-1)if(fa[x][k]!=fa[y][k]){
		x=fa[x][k],y=fa[y][k];
	}
	return fa[x][0];
}
void solve(){
	cin>>k;
	vt<int>v;
	int m1=-1,m2=-1;
	rd(i,k){
		cin>>a;
		v.pb(a);
	}
	int m,mn=n+1;
	rd(i,k-1){
		int res=lca(v[i],v[i+1]);
		if(dep[res]<mn)mn=dep[res],m=res;//寻找深度最小的 LCA 
	}
	for(auto a:v){
		if(m1==-1){
			m1=a;
			continue;
		}
		int res=lca(a,m1);
		if(res==m1||res==a){
			if(res==m1)m1=a;
			continue;
		}else if(res!=m){
			cout<<"NO"<<endl;
			return;
		}
		if(m2==-1){
			m2=a;
			continue;
		}
		res=lca(a,m2);
		if(res==m2||res==a){
			if(res==m2)m2=a;
		}else{
			cout<<"NO"<<endl;
			return;
		}
	}
	cout<<"YES"<<endl;
	
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	rp(i,n-1){
		cin>>a>>b;
		vv[a].pb(b);
		vv[b].pb(a);
	}
	rp(i,n)lg[i]=lg[i-1]+((1<<lg[i-1])==i);
	init(1,0);
	cin>>q;
	rd(_,q){
		solve();
	}
	return 0;
}
//Accepted!
```



---

