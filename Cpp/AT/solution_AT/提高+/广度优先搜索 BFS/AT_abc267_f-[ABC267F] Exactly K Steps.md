# [ABC267F] Exactly K Steps

## 题目描述

给定一棵有 $N$ 个点的树，每个点的编号分别为 $1,2,\cdots,N$；给定的第 $i(1\leq i\leq N-1)$ 条边连接编号为 $A_i,B_i$ 的点。

定义两点 $u,v$ 间的距离为这两个点之间的最短路径所包含的边数。

现有 $Q$ 组询问，对于第 $i$ 组询问，给定 $U_i,K_i$，找到任意一个离结点 $U_i$ 的距离恰好为 $K_i$ 的点，或报告无解。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
3 5
3
2 2
5 3
3 3```

### 输出

```
4
1
-1```

## 样例 #2

### 输入

```
10
1 2
2 3
3 5
2 8
3 4
4 6
4 9
5 7
9 10
5
1 1
2 2
3 3
4 4
5 5```

### 输出

```
2
4
10
-1
-1```

# 题解

## 作者：DaiRuiChen007 (赞：14)

# ABC267F 题解

## 思路分析

考虑对于每个点 $u$ 选择一个距离 $u$ 最远的节点 $p$，然后将 $p$ 作为根节点，求出 $u$ 的 $k$ 级祖先即可。

注意到对于 $1\sim n$ 的每个节点，这样的 $p$ 只可能是某个直径的两个端点，因此求出直径端点 dfs 即可。

求 $k$ 级祖先的时候不用倍增，直接在树上记录上一个深度为 $x$ 的点 $d_x$，由于 dfs 序的特征，对于某个点 $u$ 其 $k$ 级祖先就是 $d_{dep_u-k}$。

时间复杂度 $\Theta(n+q)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
vector <int> edge[MAXN],query[MAXN];
int ans[MAXN],node[MAXN],dis[MAXN],len;
inline void dfs(int p,int f,int dep) {
	node[dep]=p;
	for(int q:query[p]) if(dep>=dis[q]) ans[q]=node[dep-dis[q]];
	len=max(len,dep);
	for(int v:edge[p]) if(v!=f) dfs(v,p,dep+1);
}
signed main() {
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;++i) {
		int u;
		scanf("%d%d",&u,&dis[i]);
		query[u].push_back(i);
	}
	for(int turn:{0,1,2}) {
		int pos=node[len]; len=0;
		if(!turn) pos=1;
		dfs(pos,0,0);
	}
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]?ans[i]:-1);
	return 0;
}
```

---

## 作者：K8He (赞：4)

题目链接：[[ABC267F] Exactly K Steps](https://www.luogu.com.cn/problem/AT_abc267_f)。

~~大家好，我是个毒瘤，我非常喜欢没脑子做法，于是我就用点分治过了这个题。~~

离线在每个点存下与其相关的询问。考虑如何计算跨重心的答案。

记录下每个点在当前重心下的深度，同时开一个桶 $t_{k, 0/1}$ 存下当前深度为 $k$ 的，来自重心的不同子树的两个点。

把记录深度的搜索过程中遇到的询问拿出来，在记录完桶之后处理。具体的，对于一个询问 $(u, k)$，查找桶 $t_{k - dep_u,0/1}$ 内是否有与 $u$ 不在同一棵子树的点。需要特殊处理一下 $k-dep_u = 0$ 的询问。

具体实现细节可以看代码。

询问虽然不是一次性全能处理完的，但是由于点分治最多递归 $\log n$ 层，每个询问也最多只会被取出 $\log n$ 次，时间复杂度是 $O((n+q)\log n)$。

Code：

```cpp
const int N = 2e5 + 10, P = 998244353;
namespace SOLVE {
	int n, q, ans[N];
	std::vector <int> tu[N];
	std::vector <pii> qu[N];
	inline int rnt () {
		int x = 0, w = 1; char c = getchar ();
		while (!isdigit (c)) { if (c == '-') w = -1; c = getchar (); }
		while (isdigit (c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar ();
		return x * w;
	}
	int root, sz[N], tmp[N][2][2], mx[N];
	bool vis[N];
	class T {
	public:
		int u, d, r;
		T () = default;
		T (int _u, int _d, int _r): u(_u), d(_d), r(_r) {}
	};
	std::queue <T> qa;
	void DFS_Find (int u, int fa, int dep, int r) {
		if (!qu[u].empty ()) qa.push (T (u, dep, r));
		if (!tmp[dep][0][0]) tmp[dep][0][0] = u, tmp[dep][0][1] = r;
		else if (!tmp[dep][1][0] && tmp[dep][0][1] != r) tmp[dep][1][0] = u, tmp[dep][1][1] = r;
		far (v, tu[u]) {
			if (vis[v] || v == fa) continue;
			DFS_Find (v, u, dep + 1, r);
		}
		return;
	}
	int DFS_MaxDep (int u, int fa, int dep) {
		int mx = dep;
		far (v, tu[u]) if (!vis[v] && v != fa)
			mx = std::max (mx, DFS_MaxDep (v, u, dep + 1));
		return mx;
	}
	inline void Calc (int u) {
		far (v, tu[u]) {
			if (vis[v]) continue;
			DFS_Find (v, u, 1, v);
		}
		if (!qu[u].empty ()) qa.push (T (u, 0, u));
		while (!qa.empty ()) {
			T f = qa.front (); qa.pop ();
			far (p, qu[f.u]) {
				if (ans[p.second]) continue;
				int d = p.first - f.d;
				if (d < 0) continue;
				else if (d == 0) ans[p.second] = u;
				else {
					if (f.r == tmp[d][0][1]) ans[p.second] = tmp[d][1][0];
					else ans[p.second] = tmp[d][0][0];
				}
			}
		}
		int mxd = DFS_MaxDep (u, 0, 0);
		_for (i, 0, mxd) tmp[i][0][0] = tmp[i][0][1] = tmp[i][1][0] = tmp[i][1][1] = 0;
		return;
	}
	void GetRoot (int u, int fa) {
		mx[u] = 0, sz[u] = 1;
		far (v, tu[u]) {
			if (vis[v] || v == fa) continue;
			GetRoot (v, u), sz[u] += sz[v];
			mx[u] = std::max (mx[u], sz[v]);
		}
		mx[u] = std::max (mx[u], sz[0] - sz[u]);
		if (mx[root] > mx[u]) root = u;
		return;
	}
	void GetSize (int u, int fa) {
		sz[u] = 1;
		far (v, tu[u]) {
			if (vis[v] || v == fa) continue;
			GetSize (v, u), sz[u] += sz[v];
		}
		return;
	}
	void Divide (int u) {
		Calc (u), vis[u] = true;
		far (v, tu[u]) {
			if (vis[v]) continue;
			sz[0] = sz[v], mx[root = 0] = N;
			GetRoot (v, u), GetSize (root, u);
			Divide (root);
		}
		return;
	}
	inline void In () {
		n = rnt ();
		_for (i, 1, n - 1) {
			int u = rnt (), v = rnt ();
			tu[u].emplace_back (v);
			tu[v].emplace_back (u);
		}
		q = rnt ();
		_for (i, 1, q) {
			int u = rnt (), d = rnt ();
			qu[u].emplace_back (d, i);
		}
		return;
	}
	inline void Solve () {
		root = 0, sz[0] = n, mx[0] = N;
		GetRoot (1, 0), GetSize (root, 0);
		Divide (root);
		return;
	}
	inline void Out () {
		_for (i, 1, q) printf ("%d\n", ans[i] ? ans[i] : -1);
		return;
	}
}
```


---

## 作者：Elairin176 (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT_abc267_f)    
很好想的图论。    
## 题意
给你一棵树和 $q$ 组询问，每组询问要求求出距离某个结点距离正好为 $k$ 的任意一个结点。   
## 解法
先给出一个结论：离任何一个点最远的任意一个点都是某个直径上的端点。    
那么有了这个结论，我们可以先求出这棵树的直径并记下左右端点。     
那么我们考虑询问。我们可以先用 LCA 求出指定端点和直径左右端点的距离，我们取最大值。    
显然地，如果这个最大值比指定的距离还小，那么一定无解。     
我们设选定的直径端点为 $u$，询问的结点为 $x$。    
那么我们接下来就是跳跃了。   
我们先求出选定直径端点和指定端点的 LCA，设为 $l$，那么我们再设 $\operatorname{dis}(x,y)$ 为 $x,y$ 两点的距离，指定距离我们仍然称为 $k$。   
如果 $k\le\operatorname{dis}(l,x)$，那么答案显然是在 $l$ 到 $x$ 的路径上的。我们只需要从 $x$ 开始向上跳 $k$ 个距离就可以了。   
如果 $k>\operatorname{dis}(l,x)$，那么我们就要从 $l$ 向下跳。但是向下跳显然不好维护，我们可以将其转化为向上跳：   
显然，在 $l$ 到 $u$ 的路径上总是会向下跳 $k-\operatorname{dis}(l,x)$ 次。如果从 $u$ 向上跳，只需要用 $\operatorname{dis}(l,u)$ 减掉刚刚的数值即可（正好反过来）。即 $\operatorname{dis}(l,u)-(k-\operatorname{dis}(l,x))$。     
## 细节
- 跳的时候要倍增跳。      

[CODE](https://www.luogu.com.cn/paste/pv8gcezr)

---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/T238762)
## 题意
给你一颗 $n$ 个结点的树，有 $q$ 次询问，每次给出 $x,k$，求任意一个与 $x$ 距离为 $k$ 的点，或者返回无解。

$1\le n,q\le2\times 10^6$。
## 思路
真的想不到撞了题。[$\text{Link}$](https://www.luogu.com.cn/problem/AT_abc267_f)。

先定 $1$ 为根，求出每个结点深度 $d_i$，子树里深度的最大值 $f_i$ 和取到最大值的结点 $g_i$。

对于一次询问分一下类：
1. $d_x\ge k$，直接输出 $k$ 级祖先即可。
2. $f_x-d_x\ge k$，此时要输出一个 $x$ 结点的 $k$ 级儿子。我们可以知道，最深的链上一定有这种结点，于是转化为 $g_x$ 的 $f_x-d_x-k$ 级祖先。
3. 其他情况。

考虑这一类，$x$ 与答案 $y$ 的路径必定由 $x$ 到 $x$ 的一个祖先 $z$，再到 $z$ 的其它子树中的 $y$。

我们考虑找到最可能成为答案转折点的 $z$ 结点，此时需要 $x$ 到 $z$ 其它子树中的深度最大的结点的距离最大。

给每个结点的子树标号，设为 $1,\dots,k$，则令 $\displaystyle f'_{i,j}$ 为除了 $i$ 结点的第 $j$ 个子树，子树中其它部分的深度最大值，$g'_{i,j}$ 为对应的结点。预处理每个结点的前后缀算出。

令 $x$ 为 $z$ 的第 $j$ 个子树，则 $x$ 到 $z$ 其它子树中的深度最大的结点的距离为 $d_x+f'_{z,j}-2d_z$。考虑对每个 $x$ 预处理出最优的 $z_x$。这个可以开始的时候 $\text{dfs}$ 一遍求出。

找到 $z$ 之后，我们还要求出它除了子树 $j$ 以外的一个 $k-d_x+d_z$ 级儿子，也转化为 $g'_{z,j}$ 的 $f'_{z,j}-k+d_x-2d_z$ 级祖先。注意判断无解。

关于线性求出 $k$ 级祖先：考虑 $\text{dfs}$ 过程中用栈记录所有的祖先，在找到询问时标答案为倒数第 $k$ 位即可。

时间复杂度 $\Theta(n+q)$。

带上小常数的 $\log$ 应该都放过了吧？

std：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=2e6+10;
struct Edge{
	int to,nxt;
}a[N<<1];
int n,q,cnt,head[N];
inline void add(int u,int v){
	cnt++;
	a[cnt]={v,head[u]};
	head[u]=cnt; 
}
int d[N],f[N],g[N],*fp[N],*gp[N],son[N],pool[N<<2],*now=pool;
int pf[N],pg[N],sf[N],sg[N],stc[N];
inline void dfs1(int x,int fa){
	d[x]=d[fa]+1,f[x]=d[x],g[x]=x;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		dfs1(t,x);
		son[x]++;
		if(f[t]>f[x]) f[x]=f[t],g[x]=g[t];
	}
}
int y[N],z[N];
inline void dfs2(int x,int fa,int py,int pz,int mx){
	int sz=son[x],cnt=0;
	fp[x]=now,now+=sz+1;
	gp[x]=now,now+=sz+1;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		stc[++cnt]=t;
	}
	assert(cnt==sz);
	pf[0]=sf[sz+1]=0;
	for(int i=1;i<=sz;i++)
		pf[i]=sf[i]=f[stc[i]];
	for(int i=1;i<=sz;i++){
		if(pf[i]<=pf[i-1])
			pf[i]=pf[i-1],pg[i]=pg[i-1];
		else
			pg[i]=g[stc[i]];
	}
	for(int i=sz;i>=1;i--){
		if(sf[i]<=sf[i+1])
			sf[i]=sf[i+1],sg[i]=sg[i+1];
		else
			sg[i]=g[stc[i]];
	}
	for(int i=1;i<=sz;i++){
		if(pf[i-1]<=sf[i+1])
			fp[x][i]=sf[i+1],gp[x][i]=sg[i+1];
		else
			fp[x][i]=pf[i-1],gp[x][i]=pg[i-1];
	}
	if(sz==1){
		fp[x][1]=d[x],gp[x][1]=x;
	}
	y[x]=py,z[x]=pz,cnt=0;
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		cnt++;
		if(fp[x][cnt]-2*d[x]>mx)
			dfs2(t,x,gp[x][cnt],x,fp[x][cnt]-2*d[x]);
		else
			dfs2(t,x,py,pz,mx);
	}
}
int ans[N],stk[N],top,cnt2,head2[N],nxt[N],ed[N];
struct Query{
	int k,id;
}w[N];
inline void add2(int x,Query t){
	cnt2++;
	if(!head2[x]) head2[x]=cnt2;
	nxt[ed[x]]=cnt2;
	ed[x]=cnt2,w[cnt2]=t;
}
inline void dfs3(int x,int fa){
	stk[++top]=x;
	for(int i=head2[x];i;i=nxt[i]){
		Query tmp=w[i];
		if(top<=tmp.k) ans[tmp.id]=-1;
		else ans[tmp.id]=stk[top-tmp.k];
	}
	for(int i=head[x];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa) continue;
		dfs3(t,x);
	}
	top--;
}
int main(){
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0,1,1,-1e9);
	for(int i=1;i<=q;i++){
		int x=read(),k=read();
		if(d[x]>k) add2(x,{k,i});
		else if(f[x]-d[x]>=k) add2(g[x],{f[x]-d[x]-k,i});
		else{
			int py=y[x],pz=z[x];
			if(d[x]+d[py]-2*d[pz]<k) ans[i]=-1;
			else add2(py,{d[py]-k+d[x]-2*d[pz],i});
		}
	} 
	dfs3(1,0);
	for(int i=1;i<=q;i++)
		write(ans[i]),putc('\n');
	flush();
}
```
****
好的，被验题人薄纱了。

有一个结论：树上距离点 $x$ 最远的点一定是直径两端点之一，所以把直径提出来讨论一下就好了。

时间复杂度 $\Theta(n+q)$。

再见 qwq~

---

## 作者：WaterSun (赞：3)

~~大家好，我是毒瘤，喜欢用玄学算法过题。~~

发现题解区没有这个做法，于是来发一篇。

# 思路

不难发现如果一个点对 $(u,v)$ 的距离为 $d$，那么在这棵树以 $u$ 为根时，$v$ 的深度为 $d$。于是考虑换根 DP。

首先思考如何计算答案。显然我们可以将查询离线下来，然后当换根到以 $u$ 为根时，将有关 $u$ 的所有查询全部解决即可。

其次，发现当一个 $v$ 转化成根时，它会在其父节点 $u$ 为根时的形态的基础上，所在 $v$ 子树中的节点深度减 $1$，其余节点加 $1$。

然而，我们需要求的是深度为 $d$ 的节点，于是单单想大多数的换根 DP 维护深度的极值是不行的，所以需要更新出所有的深度。

于是这个东西需要使用数据结构维护。明确这个数据结构所需的功能：

1. 区间加减。

2. 区间查询权值为 $k$ 的编号。

于是你就想到了[这道题](https://loj.ac/p/6278)。即用分块实现，一个 `vector` 维护块内的元素，每一次每一次修改都需要一次排序，查询都需要一次二分，单次操作是 $\Theta(\sqrt n \log \sqrt n)$ 的。配合上巨大常数，你得到了 [TLE 15](https://atcoder.jp/contests/abc267/submissions/47573423) 的代码。

然后你可以发现此题是维护深度，所以值域很小，所以可以开桶维护。你在查询的时候每次都先看一下在这块中有没有出现 $k$，如果出现了就直接暴力找；否则就继续向前面的块判断。这样实现即可单次操作做到 $\Theta(\sqrt n)$。

于是你就得到了理论时间复杂度为 $\Theta(q \sqrt n)$ 的代码，但是常数有点小大，但是发现每一次的桶都不需要清空完，只需将原本的 $val$ 删掉，然后加上新的 $val$ 即可。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10,M = 4e5 + 10,K = 1010;
int n,q;
int idx,h[N],ne[M],e[M],ans[N];
int num,id[N],pid[N],sz[N],d[N],val[N];
vector<pii> Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void add(int a,int b){
    ne[idx] = h[a];
    e[idx] = b;
    h[a] = idx++;
}

struct block{
    int len,num;
    int pos[N],L[K],R[K],tag[K],vis[K][N];

    inline void init(){
        len = num = sqrt(n);
        for (re int i = 1;i <= n;i++) val[id[i]] = d[i];
        for (re int i = 1;i <= num;i++){
            L[i] = (i - 1) * len + 1;
            R[i] = i * len;
        }
        if (R[num] != n){
            num++;
            L[num] = (num - 1) * len + 1;
            R[num] = n;
        }
        for (re int i = 1;i <= num;i++){
            for (re int j = L[i];j <= R[i];j++){
                pos[j] = i;
                vis[i][val[j]]++;
            }
        }
    }

    inline void modify(int l,int r,int k){
        int p = pos[l],q = pos[r];
        if (p == q){
            for (re int i = l;i <= r;i++){
                vis[p][val[i]]--;
                val[i] += k;
                vis[p][val[i]]++;
            }
        }
        else{
            for (re int i = l;i <= R[p];i++){
                vis[p][val[i]]--;
                val[i] += k;
                vis[p][val[i]]++;
            }
            for (re int i = p + 1;i < q;i++) tag[i] += k;
            for (re int i = L[q];i <= r;i++){
                vis[q][val[i]]--;
                val[i] += k;
                vis[q][val[i]]++;
            }
        }
    }

    inline int query(int l,int r,int k){
        int p = pos[l],q = pos[r];
        if (p == q){
            for (re int i = l;i <= r;i++){
                if (val[i] + tag[p] == k) return pid[i];
            }
        }
        else{
            for (re int i = l;i <= R[p];i++){
                if (val[i] + tag[p] == k) return pid[i];
            }
            for (re int i = p + 1;i < q;i++){
                if (vis[i][k - tag[i]]){
                    for (re int j = L[i];j <= R[i];j++){
                        if (val[j] + tag[i] == k) return pid[j];
                    }
                }
            }
            for (re int i = L[q];i <= r;i++){
                if (val[i] + tag[q] == k) return pid[i];
            }
        }
        return -1;
    }
}bl;

inline void calc(int u){
    for (auto x:Q[u]) ans[x.snd] = bl.query(1,n,x.fst + 1);
}

inline void dfs1(int u,int fa){
    num++;
    sz[u] = 1;
    id[u] = num;
    pid[num] = u;
    d[u] = d[fa] + 1;
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        dfs1(j,u);
        sz[u] += sz[j];
    }
}

inline void dfs2(int u,int fa){
    for (re int i = h[u];~i;i = ne[i]){
        int j = e[i];
        if (j == fa) continue;
        bl.modify(1,n,1);
        bl.modify(id[j],id[j] + sz[j] - 1,-2);
        calc(j);
        dfs2(j,u);
        bl.modify(1,n,-1);
        bl.modify(id[j],id[j] + sz[j] - 1,2);
    }
}

int main(){
    memset(h,-1,sizeof(h));
    n = read();
    for (re int i = 1;i < n;i++){
        int a,b;
        a = read();
        b = read();
        add(a,b);
        add(b,a);
    }
    q = read();
    for (re int i = 1;i <= q;i++){
        int a,b;
        a = read();
        b = read();
        Q[a].push_back({b,i});
    }
    for (re int i = 1;i <= n;i++) sort(Q[i].begin(),Q[i].end());
    dfs1(1,0);
    bl.init();
    calc(1);
    dfs2(1,0);
    for (re int i = 1;i <= q;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：NobodyThere (赞：1)

这里提供一种复杂度为 $\mathcal O((n+q)\log n)$ 的做法。

对于被询问的点 $u$ 与距离 $k$，如果 $\exists v\text{ s.t. }dis(u,v)=k$（其中 $dis(u,v)$ 表示 $u,v$ 间的距离），那么一定存在这样的 $v$，使得 $v$ 在 $u$ 到离其最远的点的路径上。

而离 $u$ 最远的点一定是直径的一端。于是我们首先求出一条直径，记录其端点。

关于直径的知识，可参见 [OI-wiki-树的直径](http://oi-wiki.com/graph/tree-diameter/)。
 
设直径两端端点为 $a,b$，考虑分别以 $a,b$ 作根，倍增求每个点的 $2^k(k=0,1,2,\cdots)$ 级祖先。这么一来，我们就得到了每一个点分别往 $a,b$ 走 $k(1\leq k\leq n)$ 步所能到达的点，或者得知 $k>dis(u,a)$。利用这个信息就可以回答询问了。

预处理复杂度 $\mathcal O(n\log n)$，在线询问复杂度 $\mathcal O(q\log n)$，总复杂度 $\mathcal O((n+q)\log n)$。

Code:

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
const int N = 20;
int n, q, h[200007], tmp, rt[2], nxt[2][200007][N + 3];
struct edge{int v, ne;}l[400007];
inline void add(int u, int v){l[++tmp].v = v, l[tmp].ne = h[u], h[u] = tmp;}
bool vis[200007];
void find_root(int u, int num, int &mx, int &res) { // 找根，也就是找直径的端点
	vis[u] = 1;
	if(num > mx)
		mx = num, res = u;
	for(int i = h[u]; i; i = l[i].ne)
		if(!vis[l[i].v])
			find_root(l[i].v, num + 1, mx, res);
	vis[u] = 0;
}
void dfs1(int u, int opt) { // 记录以直径端点为根时的父亲
	vis[u] = 1;
	for(int i = h[u]; i; i = l[i].ne) {
		const int v = l[i].v;
		if(!vis[v]) {
			nxt[opt][v][0] = u, dfs1(v, opt);
		}
	}
	vis[u] = 0;
}
void dfs2(int u, int opt) { // 倍增预处理 2^k 级祖先
	vis[u] = 1;
	for(int i = 1, j = nxt[opt][u][0]; i <= N; j = nxt[opt][u][i], i++)
		nxt[opt][u][i] = nxt[opt][j][i - 1];
	for(int i = h[u]; i; i = l[i].ne) {
		const int v = l[i].v;
		if(!vis[v]) dfs2(v, opt);
	}
	vis[u] = 0;
}
int cal(int u, int k, int opt) { // 在线回答到直径端点路径上，距离为 k 的点的编号
	for(int i = 0; k; k >>= 1, i++) {
		if(k & 1)
			u = nxt[opt][u][i];
	}
	return u;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v), add(v, u);
	}
	find_root(1, 0, tmp = 0, rt[0]);
	find_root(rt[0], 0, tmp = 0, rt[1]);
	dfs1(rt[0], 0), dfs1(rt[1], 1);
	dfs2(rt[0], 0), dfs2(rt[1], 1);
	scanf("%d", &q);
	while(q--) {
		int u, k;
		scanf("%d %d", &u, &k);
		int res0 = cal(u, k, 0), res1 = cal(u, k, 1);
		if(res0) printf("%d\n", res0); // 记得判断哪条路可行
		else if(res1) printf("%d\n", res1);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：chengning0909 (赞：0)

# abc 267 f

## 题意

给定一个有 $N$ 个结点的树，结点分别编号为 $1, 2, \dots, N$，第 $i$ 条边 $(1 \le i \le N - 1)$ 连接点 $A_i, B_i$。

树上的两个结点 $u, v$ 之间的距离定义为从 $u$ 到 $v$ 的最短路径所经过的边的数量。

给定 $Q$ 次询问，第 $i$ 次询问给出 $U_i, K_i$，请你输出任意一个与 $U_i$ 距离为 $K_i$ 的点的编号。如果不存在，输出 `-1`。

## 思路

### 在线

首先，我们先思考这样一个问题，在什么情况下，不存在与点 $u$ 距离为 $k$ 的点？

当从 $u$ 出发的最长路小于 $k$ 时，就说明不存在这样的点。

而我们可以想到最长路这件事，就可以联想到树的直径。

令从 $u$ 出发的最长路所到达的点为 $v$。

可以证明，$v$ 肯定是某一条树的直径的某一个端点，因为有一条直径的某个端点本身就是从点 $u$ 开始的能走到的最远的点，所以 $v$ 一定是这个搜到的点。我们设这条直径的两个端点为 $s, t$。

所以，我们可以画一个这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/j93zvuoc.png)

也就是说，如果我们要求与 $u$ 距离为 $k$ 的点，就相当于在以 $s$ 为根的树和以 $t$ 为根的树上找 $u$ 的 $k$ 级祖先。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, q, d, id[2], fa[2][20][N];
vector<int> g[N];

void dfs(int t, int f, int dis, int p) {
  if (dis > d) {
    d = dis, id[p] = t;
  }
  if (p >= 2) {
    fa[p % 2][0][t] = f;
  }
  for (int i : g[t]) {
    if (i != f) {
      dfs(i, t, dis + 1, p);
    }
  }
}

void get_fa() {
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < 20; j++) {
      for (int k = 1; k <= n; k++) {
        fa[i][j][k] = fa[i][j - 1][fa[i][j - 1][k]];
      }
    }
  }
}

int Find(int u, int k, bool p) {
  for (int i = 0; i < 20; i++, k >>= 1) {
    if (k & 1) {
      u = fa[p][i][u];
    }
  }
  return u;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, a, b; i < n; i++) {
    cin >> a >> b;
    g[a].push_back(b), g[b].push_back(a);
  }
  dfs(1, 0, 0, 0), d = 0, dfs(id[0], 0, 0, 1);
  dfs(id[0], 0, 0, 2), dfs(id[1], 0, 0, 3), get_fa();
  cin >> q;
  while (q--) {
    int u, k;
    cin >> u >> k;
    int s = max(Find(u, k, 0), Find(u, k, 1));
    cout << (!s ? -1 : s) << '\n';
  }
  return 0;
}
```

-------------

### 离线

我们可以把每个点 $u$ 需要查询的每个 $k$ 都记录下来，然后对树做一遍深搜，用栈来维护每一条树链的元素，记录每次询问的答案。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int N = 2e5 + 10;

int n, q, d, id[2], ans[N];
vector<int> g[N];
vector<pii> pos[N];
int top, stk[N];

void dfs(int t, int f, int dis, int p) {
  if (dis > d) {
    d = dis, id[p] = t;
  }
  for (int i : g[t]) {
    if (i != f) {
      dfs(i, t, dis + 1, p);
    }
  }
}

void _dfs(int t, int fa) {
  stk[++top] = t;
  for (int i : g[t]) {
    if (i != fa) {
      _dfs(i, t);
    }
  }
  for (auto [i, j] : pos[t]) {
    if (top > i) {
      ans[j] = stk[top - i];
    }
  }
  top--;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, a, b; i < n; i++) {
    cin >> a >> b;
    g[a].push_back(b), g[b].push_back(a);
  }
  dfs(1, 0, 0, 0), d = 0, dfs(id[0], 0, 0, 1);
  cin >> q;
  for (int i = 1, u, k; i <= q; i++) {
    cin >> u >> k, ans[i] = -1;
    pos[u].push_back({k, i});
  }
  _dfs(id[0], 0), _dfs(id[1], 1);
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
```

---

## 作者：__yabnto__ (赞：0)

### [ABC267F] Exactly K Steps
### 题意
有一颗 $n$ 个点，$n - 1$ 条边的树，找到任意一个离结点 $u$ 的距离恰好为 $k$ 的点，或报告无解。

定义两点 $u, v$ 间的距离为这两个点之间的最短路径所包含的边数。
### 思路
考虑无解，显然如果从 $u$ 走出来的最长简单路径的长度都没有 $k$ 大，那么肯定无解，我们还知道树中任意一个点的最长路径的终点肯定是这棵树的直径的端点中的一个，那么可以推出来这么一个图，表示任意一个点的答案可能出现的地方（用红色圈起来）：

![](https://cdn.luogu.com.cn/upload/image_hosting/nose581w.png)

于是可以离线处理，记录从点 $u$ 搜到直径两端的路径，再记录答案，一个一个的搜肯定会 TLE，所以可以从直径两端开始搜。
#### 代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MaxN = 2e5 + 10;

struct S {
  int x, y;

  bool operator<(const S &j) const {
    return y < j.y;
  }
};

int u[MaxN], k[MaxN], ans[MaxN], n, q;
vector<int> g[MaxN], c;
vector<S> l[MaxN];

S dfs(int x, int fa) {
  S res = {x, 0};
  for (int i : g[x]) {
    if (i == fa) {
      continue;
    }
    res = max(res, dfs(i, x));
  }
  return {res.x, res.y + 1};
}

void DFS(int x, int fa) {
  c.push_back(x);
  for (int i : g[x]) {
    if (i == fa) {
      continue;
    }
    DFS(i, x);
  }
  int len = c.size();
  for (S i : l[x]) {
    (len > i.x) && (ans[i.y] = c[len - i.x - 1]);
  }
  c.pop_back();
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  cin >> q;
  for (int i = 1; i <= q; i++) {
    cin >> u[i] >> k[i];
    l[u[i]].push_back({k[i], i}), ans[i] = -1;
  }
  int lres = dfs(1, -1).x, rres = dfs(lres, -1).x;
  DFS(lres, -1), DFS(rres, -1);
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
```


---

## 作者：Augen_stern (赞：0)

### Part 1 算法分析

题目的意思就是说，给你一棵 $n$ 个点的树，有 $Q$ 次询问，称每次询问给出 $u,k$，求任意一个与 $u$ 距离为 $k$ 的点，如果无解则输出 ```-1```。

**结论**：很显然，为了使一个点走到离它更远的点，他总会经过这一棵树的直径的点；

证明与 $dfs$ 求树的直径的证明类似，便不过多赘述。

所以我们可以把这棵树的直径拿出来，将他们当作根，具体意思就是将直径之间的边断开，使之成为一个森林，森林中每一棵树的根即为直径上的点（任意一个直径都可以），便于区分，我们称森林中的树为直径子树。

那么，一个点走到距离它为 $k$ 的点，就只能先走向它所在直径子树的祖先，然后再向直径的左或右走（哪边节点多走哪边）。

### Part 2 代码实现：

- 找出原树的直径。
- 找出每一棵直径子树的直径。
- 倍增预处理树上 $k$ 级祖先。
- 查询则分类讨论：

1. 若它是直径上的点，则往直径的左，或右走 $k$ 步；
2. 否则，先往祖先走，然后或作第一种情况。

若走不了了，就是无解。

### Part 3 CODE

```cpp
//#pragma GCC optimize(3)
#include<iostream>
#include<climits>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<vector>
//#include<random>
//#include<chrono>
#define int long long
#define double long double
using namespace std;
const int INF=LLONG_MAX/2;
const long long mod=1000000007;
const double Pai=acos(-1);
vector<int> v[1000005],v2;
int n,ans=0,Q;
int d[1000005],prt[1000005],vst[1000005],pos[1000005],be[1000005];
void dfs(int s,int fa,int dep) {
	d[s]=dep;
	for(int i=0;i<v[s].size();i++) {
		int y=v[s][i];
		if(y==fa) continue;
		prt[y]=s;
		dfs(y,s,dep+1);
	}
}
pair<int,int> find(int x) {
	dfs(x,0,0);
	int maxx=0,s=0;
	for(int i=1;i<=n;i++) {
		if(d[i]>maxx) maxx=d[i],s=i;
	}
	dfs(s,0,0);
	maxx=0;int t=0;
	for(int i=1;i<=n;i++) {
		if(d[i]>maxx) maxx=d[i],t=i;
	}
	return make_pair(s,t);
}
int f[1000005][22];
void dfs2(int u,int father,int dep,int fg) {
    d[u]=dep;be[u]=fg;
    f[u][0]=father;
    for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=0;i<v[u].size();i++) {
        int y=v[u][i];
        if(y!=father&&vst[y]!=1) dfs2(y,u,dep+1,fg);
    }
}
int get_fa(int x,int k) {
    int t=d[x]-k;
    for(int i=20;i>=0;i--) if(d[f[x][i]]>t)x=f[x][i];
    return f[x][0];
}
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<n;i++) {
		int x,y;
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y);v[y].push_back(x);
	}
	pair<int,int> p=find(1);
	for(int i=1;i<=n;i++) prt[i]=0;
	dfs(p.first,0,0);
	int g=p.second;
	while(g!=0) {
		v2.push_back(g);
		g=prt[g];
	}
	for(int i=0;i<v2.size();i++) vst[v2[i]]=1,pos[v2[i]]=i;
	for(int i=1;i<=n;i++) prt[i]=d[i]=0;
	for(int i=0;i<v2.size();i++) {
		dfs2(v2[i],0,0,i);
	}
	scanf("%lld",&Q);
	while(Q--) {
		int x,y;
		scanf("%lld%lld",&x,&y);
		if(vst[x]==1) {
			int ps=pos[x];
			int ans=-1;
			if(ps-y>=0) ans=v2[ps-y];
			else if(ps+y<v2.size()) ans=v2[ps+y];
			printf("%lld\n",ans);
		}
		else {
			if(d[x]==y) {
				printf("%lld\n",v2[be[x]]);
				continue;
			}
			if(d[x]<y) {
				y-=d[x];
				int ps=be[x];
				int ans=-1;
				if(ps-y>=0) ans=v2[ps-y];
				else if(ps+y<v2.size()) ans=v2[ps+y];
				printf("%lld\n",ans);
				continue;
			}
			printf("%lld\n",get_fa(x,y));
		}
	}
 	return 0;
}
```


---

## 作者：StudyingFather (赞：0)

如果距离点 $u$ 距离最远的点，与 $U$ 的距离为 $d_{\max}$，则与 $u$ 的距离为 $0 \ldots d_{\max}$ 的点显然都是存在的。因此先思考给定点 $u$ 的情况下，求出距离 $u$ 最远的点 $v$，然后尝试在 $u \to v$ 的这条路径上找我们所求的点。

容易想到往树的直径方向上靠：对于每个点，距离这个点最远的点一定在直径的两个端点之一取得，设这个点为 $v$。

如果 $d(u, v) > k$，则所求点不存在。否则，考虑 $u \to v$ 这条路径上的第 $k$ 个点，即为所求点。我们先求出直径这条链，然后倍增：我们从直径上的每个点出发，预处理出所有非直径上点的 $2^k$ 级祖先。

设 $u$ 到直径上的点的最小距离为 $d_u$。

1. $k \leq d_u$，直接倍增即可。
2. $k > d_u$，先倍增跳到直径上的点，然后直接找到 $v$ 方向的后 $k - d_u$ 个点即可。

时间复杂度 $O((n + m) \log n)$。

```cpp
// Problem: F - Exactly K Steps
// Contest: AtCoder - NEC Programming Contest 2022 (AtCoder Beginner Contest
// 267)
// URL: https://atcoder.jp/contests/abc267/tasks/abc267_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
vector<int> e[200005], dia;
int dep[200005], fa[200005][25], s;
int ind[200005];
void dfs(int u, int f) {
  fa[u][0] = f;
  dep[u] = dep[f] + 1;
  if (dep[u] > dep[s]) s = u;
  for (auto v : e[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
}
void calcfa(int u, int f) {
  for (int i = 1; i <= 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (auto v : e[u]) {
    if (v == f) continue;
    calcfa(v, u);
  }
}
int solve(int u, int k) {
  for (int i = 20; i >= 0; i--) {
    if (k < (1 << i) || fa[u][i] == 0 || ind[fa[u][i]] != -1) continue;
    k -= 1 << i;
    u = fa[u][i];
  }
  if (k == 0) return u;
  if (ind[u] == -1) u = fa[u][0], k--;
  int siz = dia.size();
  if (ind[u] >= k)
    return dia[ind[u] - k];
  else if (ind[u] + k < siz)
    return dia[ind[u] + k];
  else
    return -1;
}
int main() {
  ios::sync_with_stdio(false);
  memset(ind, -1, sizeof(ind));
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1, 0);
  dfs(s, 0);
  for (int i = 1, u = s; u; i++, u = fa[u][0]) dia.push_back(u);
  reverse(dia.begin(), dia.end());
  int siz = dia.size();
  for (int i = 0; i < siz; i++) ind[dia[i]] = i;
  calcfa(dia[0], 0);
  int q;
  cin >> q;
  while (q--) {
    int u, k;
    cin >> u >> k;
    cout << solve(u, k) << endl;
  }
  return 0;
}
```

---

## 作者：Register_int (赞：0)

首先，离树上任意点最远的点一定为直径端点的其中一条。因为如果不是，那么这个点才应该成为直径的端点。那么求出树的任意一条直径，对于每次询问，求出 $u$ 与直径端点 $x,y$ 的距离。如果都小于 $k$，那么就~~不可以，总司令~~。否则，设距离 $u$ 距离较远的的端点为 $x$，那么一定存在一个点位于 $u\rightarrow x$ 的路径上。对于 $\operatorname{lca}(u,x)$ 的两边分类讨论即可。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct edge {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int maxd;

void find(int u, int d, int fa, int &p) {
	if (d >= maxd) p = u, maxd = d;
	for (int i = head[u]; i; i = e[i].nxt) {
		if (e[i].v != fa) find(e[i].v, d + 1, u, p);
	}
}

int fa[MAXN][20], dep[MAXN], lg[MAXN];

void init(int u, int f) {
	fa[u][0] = f, dep[u] = dep[f] + 1;
	for (int i = 1; i <= lg[dep[u]]; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = head[u]; i; i = e[i].nxt) {
		if (e[i].v != f) init(e[i].v, u);
	}
}

inline 
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	while (dep[u] > dep[v]) u = fa[u][lg[dep[u] - dep[v]]];
	if (u == v) return u;
	for (int i = lg[dep[u]]; ~i; i--) {
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	}
	return fa[u][0];
}

inline 
int jump(int u, int k) {
	for (int i = lg[k]; ~i; i--) {
		if (k >> i & 1) u = fa[u][i];
	}
	return u;
}

inline 
int dis(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

int n, q;

int x, y, u, k, d;

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), add(x, y), add(y, x);
    find(1, 0, 0, x), find(x, 0, 0, y), init(1, 0);
    for (scanf("%d", &q); q--;) {
    	scanf("%d%d", &u, &k);
    	if (dis(x, u) < dis(y, u)) swap(x, y);
    	d = dis(x, u);
    	if (d < k) puts("-1");
    	else printf("%d\n", k <= dep[u] - dep[lca(u, x)] ? jump(u, k) : jump(x, d - k));
	}
}
```

---

