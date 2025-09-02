# [JOISC 2023] Tourism (Day3)

## 题目描述

JOI 王国是一个由 $N$ 个岛屿组成的岛国，编号从 $1$ 到 $N$。这些岛屿通过 $N - 1$ 座桥相连，编号从 $1$ 到 $N - 1$。桥 $i\ (1 \leq i \leq N - 1)$ 双向连接岛屿 $A_i$ 和岛屿 $B_i$。可以通过若干座桥从任意一个岛屿到达另一个岛屿。在 JOI 王国，有 $M$ 个观光景点，编号从 $1$ 到 $M$。观光景点 $j\ (1 \leq j \leq M)$ 位于岛屿 $C_j$。有 $Q$ 位旅行者，他们计划参观 JOI 王国的观光景点。旅行者编号从 $1$ 到 $Q$。每位旅行者按以下方式旅行。

1. 旅行者选择一个岛屿 $x\ (1 \leq x \leq N)$。乘坐飞机，旅行者到达岛屿 $x$。
2. 旅行者进行若干次以下动作。动作的顺序和种类是任意的。

    - 旅行者选择当前岛屿上的一个观光景点，并参观。
    - 旅行者通过桥梁移动到另一个岛屿。

3. 乘坐飞机，旅行者离开 JOI 王国。旅行者 $k\ (1 \leq k \leq Q)$ 想要参观所有的观光景点 $L_k, L_{k + 1}, \ldots, R_k$。然而，由于预算有限，旅行者 $k$ 希望最小化至少访问一次的岛屿数量。

## 说明/提示

**【样例解释 #1】**

旅行者 1 按以下方式旅行，并参观所有的观光景点 1, 2, 3。
1. 旅行者 1 到达岛屿 2。
2. 旅行者 1 参观岛屿 2 上的观光景点 1。
3. 旅行者 1 通过桥梁 1 从岛屿 2 移动到岛屿 1。
4. 旅行者 1 通过桥梁 2 从岛屿 1 移动到岛屿 3。
5. 旅行者 1 参观岛屿 3 上的观光景点 2。
6. 旅行者 1 通过桥梁 5 从岛屿 3 移动到岛屿 6。
7. 旅行者 1 参观岛屿 6 上的观光景点 3。
8. 旅行者 1 从岛屿 6 出发，离开 JOI 王国。

岛屿 1, 2, 3, 6 是旅行者 1 至少访问一次的四个岛屿。如果旅行者 1 至少访问一次的岛屿数量小于或等于 3，则不可能参观所有的观光景点 1, 2, 3。因此，第一行输出 4。旅行者 2 按以下方式旅行，并参观所有的观光景点 4, 5, 6。
1. 旅行者 2 到达岛屿 3。
2. 旅行者 2 通过桥梁 6 从岛屿 3 移动到岛屿 7。
3. 旅行者 2 参观岛屿 7 上的观光景点 6。
4. 旅行者 2 通过桥梁 6 从岛屿 7 移动到岛屿 3。
5. 旅行者 2 通过桥梁 2 从岛屿 3 移动到岛屿 1。
6. 旅行者 2 通过桥梁 1 从岛屿 1 移动到岛屿 2。
7. 旅行者 2 通过桥梁 3 从岛屿 2 移动到岛屿 4。
8. 旅行者 2 参观岛屿 4 上的观光景点 4。
9. 旅行者 2 通过桥梁 3 从岛屿 4 移动到岛屿 2。
10. 旅行者 2 通过桥梁 4 从岛屿 2 移动到岛屿 5。
11. 旅行者 2 参观岛屿 5 上的观光景点 5。
12. 旅行者 2 从岛屿 5 出发，离开 JOI 王国。

岛屿 1, 2, 3, 4, 5, 7 是旅行者 2 至少访问一次的六个岛屿。如果旅行者 2 至少访问一次的岛屿数量小于或等于 5，则不可能参观所有的观光景点 4, 5, 6。因此，第二行输出 6。此样例输入满足子任务 1, 2, 4, 5, 6 的约束。

岛屿 1, 2, 3, 4, 5, 7 是旅行者 2 至少访问一次的六个岛屿。如果旅行者 2 至少访问一次的岛屿数量小于或等于 5，则不可能参观所有的观光景点 4, 5, 6。因此，第二行输出 6。

此样例输入满足子任务 1, 2, 4, 5, 6 的约束。

**【样例解释 #2】**

此样例输入满足子任务 1, 2, 3, 6 的约束。

**【样例解释 #3】**

此样例输入满足子任务 1, 2, 6 的约束。

**【数据范围】**

- $1 \leq N \leq 100 000$。
- $1 \leq M \leq 100 000$。
- $1 \leq Q \leq 100 000$。
- $1 \leq A_i \leq N\ (1 \leq i \leq N - 1)$。
- $1 \leq B_i \leq N\ (1 \leq i \leq N - 1)$。
- 可以通过若干座桥从任意一个岛屿到达另一个岛屿。
- $1 \leq C_j \leq N\ (1 \leq j \leq M)$。
- $1 \leq L_k \leq R_k \leq M\ (1 \leq k \leq Q)$。
- 给定的值都是整数。

**【子任务】**

1. (5 分) $N \leq 300, M \leq 300, Q \leq 300$。
2. (5 分) $N \leq 2 000, M \leq 2 000, Q \leq 2 000$。
3. (7 分) $A_i = i, B_i = i + 1\ (1 \leq i \leq N - 1)$。
4. (18 分) $L_1 = 1, R_{k} + 1 = L_{k+1}\ (1 \leq k \leq Q - 1), R_Q = M$。
5. (24 分) $A_i = \lfloor\frac{i+1}2\rfloor, B_i = i + 1\ (1 \leq i \leq N-1)$。这里，$\lfloor x\rfloor$ 是不超过 x 的最大整数。
6. (41 分) 无额外约束。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
7 6 2
1 2
1 3
2 4
2 5
3 6
3 7
2 3 6 4 5 7
1 3
4 6```

### 输出

```
4
6```

## 样例 #2

### 输入

```
8 8 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 6 4 3 5 2 4 7
3 5
4 6
6 8
1 4
2 3
6 8
5 5
2 8
1 2```

### 输出

```
3
4
6
6
3
6
1
6
3```

## 样例 #3

### 输入

```
10 7 9
6 5
3 6
9 3
8 3
7 8
7 1
2 5
7 10
8 4
9 4 10 1 10 7 6
4 4
1 3
1 3
6 7
3 6
3 3
1 5
2 5
1 2```

### 输出

```
1
6
6
4
3
1
7
5
4```

# 题解

## 作者：Mikefeng (赞：18)


### 前言：看到杨老师的 $O(n\log^2 n)$ 做法，所以来写一个 $O(n\sqrt n)$ 做法。

## 题意

多次查询包含区间中所有点的连通块最小大小。

## 做法

区间查询，可以离线，一眼鉴定为莫队。

包含所有关键点的连通块最小大小是经典问题，虚树中边的数量等于按 dfs 排序后两两相邻的点的距离之和。（第一个和最后一个也相邻）

这样就获得了 $O(n\sqrt n\log n)$ 的做法，直接莫队，记录每个点的出现数量，如果删到了 $0$ 就从点集中去掉，用 set 动态维护前驱后继，同时维护虚树大小。

因为懒得写回滚莫队，先写了 set，有 $28$ 分的高分。

发现只删的前驱后继可以用链表维护，套一个只删不加的回滚莫队，右端点从右到左排序，同时用 $O(1)$ lca 求两个点间的距离，用的是 dfs 序 lca，这样常数小，还不用多记一个欧拉序。

时间复杂度 $O(n\sqrt n)$。

## 代码

```cpp
const int N=1e5+5;
int n,m,k,len,res;
int a[N],ans[N];
int num[N],lg[N];
vector<int> e[N];
int id[N],rk[N],dep[N];
int st[20][N],cnt;
inline void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	id[u]=++cnt;rk[cnt]=u;
	st[0][cnt]=fa;
	for(int v:e[u]) if(v!=fa) dfs(v,u);
}
inline int Min(int x,int y){return dep[x]<dep[y]?x:y;}
inline void init(){
	F(i,2,n) lg[i]=lg[i>>1]+1;
	F(j,1,19) F(i,1,cnt-(1<<j)+1) st[j][i]=Min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
}
inline int lca(int l,int r){
	if(l==r) return rk[l];
	if(l>r) swap(l,r);
	++l;int k=lg[r-l+1];
	return Min(st[k][l],st[k][r-(1<<k)+1]);
}
inline int dis(int x,int y){return dep[rk[x]]+dep[rk[y]]-2*dep[lca(x,y)];}
struct md{
	int l,r,bid,id;
	inline bool operator < (const md &x)const{return bid!=x.bid?l<x.l:r>x.r;}
}q[N];
int pre[N],nxt[N];
struct node{
	int pre,nxt,id;
	node(){}
	node(int pre,int nxt,int id):pre(pre),nxt(nxt),id(id){}
};
vector<node> s;
inline void Del(int x){
	--num[x];
	if(!num[x]){
		res-=dis(pre[x],x)+dis(x,nxt[x]);
		res+=dis(pre[x],nxt[x]);
		pre[nxt[x]]=pre[x];nxt[pre[x]]=nxt[x];
	}
}
inline void del(int x){
	s.emplace_back(pre[x],nxt[x],x);
	--num[x];
	if(!num[x]){
		res-=dis(pre[x],x)+dis(x,nxt[x]);
		res+=dis(pre[x],nxt[x]);
		pre[nxt[x]]=pre[x];nxt[pre[x]]=nxt[x];
	}
}
inline void solve(){
	int l=1,r=0;
	F(i,1,m){
		if(q[i].bid!=q[i-1].bid){
			memset(num,0,sizeof num);
			F(j,(q[i].bid-1)*len+1,k) ++num[id[a[j]]];
			int lst=0;F(j,1,n){
				pre[j]=lst;
				if(num[j]) lst=j;
			}
			F(j,1,n) if(!pre[j]) pre[j]=lst;
			lst=0;UF(j,n,1){
				nxt[j]=lst;
				if(num[j]) lst=j;
			}
			UF(j,n,1) if(!nxt[j]) nxt[j]=lst;
			res=0;
			F(j,1,n) if(num[j]) res+=dis(pre[j],j);
			r=k;
		}
		l=(q[i].bid-1)*len+1;
		while(r>q[i].r) Del(id[a[r--]]);
		int now=res;
		while(l<q[i].l) del(id[a[l++]]);
		ans[q[i].id]=res/2+1;
		res=now;
		while(!s.empty()){
			node tmp=s.back();s.pop_back();
			if(!num[tmp.id]) nxt[tmp.pre]=tmp.id,pre[tmp.nxt]=tmp.id;
			++num[tmp.id];
		}
	}
}
bool M2;
int main(){
	int Time=clock();
	look_memory;
	n=read();k=read();m=read();
	len=sqrt(k);
	F(i,1,n-1){
		int u=read(),v=read();
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,0);init();
	F(i,1,k) a[i]=read();
	F(i,1,m) q[i].l=read(),q[i].r=read(),q[i].bid=(q[i].l-1)/len+1,q[i].id=i;
	sort(q+1,q+m+1);
	solve();
	F(i,1,m) cout<<ans[i]<<'\n';
	look_time;
	return 0;
}
```

---

## 作者：Un1quAIoid (赞：13)

**传送门：[P9340](https://www.luogu.com.cn/problem/P9340)**

----------------------

**题目大意：**

给定一棵 $n$ 个点的树以及一个序列 $a_{1,\dots,m}$，$q$ 次询问包含 $a_{l,\dots,r}$ 中所有点的最小连通块大小。

----------------------

回滚莫队一点也不优美，所以这里是 $O(n \log^2 n)$ 解法。

**step1**

不妨将树的根定为 $1$ 号结点。

不难看出题目就是求区间所有点构成的虚树大小，将在区间 $[l,r]$ 中出现过的点染黑，其它点染白，可以将虚树大小转化成两部分：

1. 加上所有点 $u$ 的个数，满足 $u$ 的子树中存在**至少**一个黑点
2. 减去所有点 $u$ 的个数，满足 $u$ 的子树之外（包括 $u$）**全部**为白点

第二部分实际上就是虚树的根的深度，这是好算的，虚树的根就是区间 $[l,r]$ 中 dfn 最小的结点和 dfn 最大的结点的 lca。

**step2**

难点在于第一部分。

现在来分析右端点固定为 $r$ 时，对于一个结点 $u$，左端点 $l$ 取到何值会让 $u$ 对第一部分有贡献。记 $mx_u$ 表示 $u$ 的子树中在前缀 $[1,r]$ 中**最后一次出现时间最大**的点的最后一次出现位置，容易发现当 $l \in [1,mx_u]$ 时，$u$ 子树中的点 $a_{mx_u}$ 必然为黑点，当 $l \in [mx_u + 1, r]$ 时，$u$ 子树中必然不存在黑点；所以 $u$ 会且仅会对区间 $[1,mx_u]$ 有 $+1$ 的贡献。

考虑扫描线：枚举 $r$，动态维护 $mx_u$ 以及所有左端点的答案，初始有 $mx_u = 0$。观察从 $r-1$ 枚举到 $r$ 时 $a_r$ 会对 $mx_u$ 造成什么影响：就是**将 $a_r$ 到 $1$ 的路径上的所有点的 $mx_u$ 赋值为 $i$** 。这很容易联想到 LCT 的 access 操作，也就是说，如果暴力对于从 $a_r$ 到 $1$ 的路径上的 $mx_u$ 相同的连续段分别修改的话，根据 access 的复杂度分析，这是**均摊单次 $O(\log n)$ 的**（可以看作每次操作都是在 $O(\log n)$ 条重链上做颜色段均摊）。而在整条链 $mx_u$ 相同的情况下，我们只需要知道这条链的点数即可用 BIT 快速修改。

这个过程用 LCT 即可非常方便地模拟，总复杂度 $O(n \log^2 n)$。

代码：
```cpp
//区间虚树
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

inline int read() {
	int x = 0; char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

typedef long long ll;
const int N = 1e5+5;

int n, m, q, c[N], ans[N];
int siz[N], dep[N], hs[N], f[N];
int ct[N], dfn[N], nfd[N];
int mn[N][17], mx[N][17], lg2[N];

vector<int> T[N];
vector<pair<int, int> > Q[N];

void dfs1(int x, int fa) {
	f[x] = fa;
	dep[x] = dep[fa] + 1;
	siz[x] = 1;
	for (auto son : T[x]) {
		if (son == fa) continue;
		dfs1(son, x);
		siz[x] += siz[son];
		if (siz[son] > siz[hs[x]]) hs[x] = son;
	}
}

void dfs2(int x, int ctop) {
	ct[x] = ctop;
	nfd[dfn[x] = ++dfn[0]] = x;
	if (hs[x]) dfs2(hs[x], ctop);
	for (auto son : T[x]) {
		if (son == f[x] || son == hs[x]) continue;
		dfs2(son, son);
	}
}

inline int LCA(int x, int y) {
	while (ct[x] != ct[y]) {
		if (dep[ct[x]] < dep[ct[y]]) swap(x, y);
		x = f[ct[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

int BIT[N];
inline void upd(int x, int k) { for (; x <= m; x += lowbit(x)) BIT[x] += k; }
inline void upd(int l, int r, int k) { upd(l, k), upd(r + 1, -k); }
inline int qry(int x) { int ret = 0; for (; x; x -= lowbit(x)) ret += BIT[x]; return ret; } 

namespace LCT {
	struct node {
		int son[2], fa;
		int cov, col;
	} T[N];

	#define son(x, s) T[x].son[s]
	#define f(x) T[x].fa

	inline void cov(int x, int k) { if (x) T[x].cov = T[x].col = k; }
	inline void push_down(int x) { if (int &t = T[x].cov) cov(son(x, 0), t), cov(son(x, 1), t), t = 0; }
	inline void cct(int x, int y, bool loc) { son(x, loc) = y, f(y) = x; }
	inline bool get_son(int x) { return son(f(x), 1) == x; }
	inline bool isRt(int x) { return son(f(x), 0) != x && son(f(x), 1) != x; }

	inline void rotate(int x) {
		int y = f(x);
		bool loc = get_son(x);
		f(x) = f(y);
		if (!isRt(y)) {
			son(f(y), get_son(y)) = x;
		}
		cct(y, son(x, loc ^ 1), loc);
		cct(x, y, loc ^ 1);
	}

	int stk[N], top;

	inline void splay(int x) {
		int y = x;
		stk[top = 1] = y;
		while (!isRt(y)) stk[++top] = y = f(y);
		while (top) push_down(stk[top--]);
		for (y = f(x); !isRt(x); rotate(x), y = f(x))
			if (!isRt(y))
				rotate(get_son(x) == get_son(y) ? y : x);
	}

	inline void access(int x, int t) {
		int y = 0;
		for (; x; x = f(y = x)) {
			if (y) upd(T[y].col + 1, t, dep[y] - dep[x]);
			splay(x), son(x, 1) = y;
		}
		upd(T[y].col + 1, t, dep[y]);
		cov(y, t);
	}

	#undef son
	#undef f
}

int main() {
	n = read(), m = read(), q = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		T[u].pb(v);
		T[v].pb(u);
	}

	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 2; i <= n; i++) LCT::T[i].fa = f[i];
	
	lg2[0] = -1;
	for (int i = 1; i <= m; i++) {
		c[i] = read();
		lg2[i] = lg2[i >> 1] + 1;
		mn[i][0] = mx[i][0] = dfn[c[i]];
		for (int j = 1; j <= lg2[i]; j++) {
			mn[i][j] = min(mn[i][j - 1], mn[i - (1 << j - 1)][j - 1]);
			mx[i][j] = max(mx[i][j - 1], mx[i - (1 << j - 1)][j - 1]);
		}
	}

	for (int i = 1; i <= q; i++) {
		int l = read(), r = read();
		Q[r].eb(l, i);
	}
	
	for (int i = 1; i <= m; i++) {
		LCT::access(c[i], i);
		for (auto j : Q[i]) {
			int L = j.first, R = i, len = lg2[R - L + 1];
			ans[j.second] = qry(L);
			int mnd = min(mn[R][len], mn[L + (1 << len) - 1][len]);
			int mxd = max(mx[R][len], mx[L + (1 << len) - 1][len]);
			ans[j.second] -= dep[LCA(nfd[mnd], nfd[mxd])] - 1;
		}
	}

	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：Pekac (赞：12)

[P9340](https://www.luogu.com.cn/problem/P9340)

记一下。称 $\forall j\in[l,r]$ 的 $c_j$ 为关键点。

### 法一：

最好想的。

有个显然的结论，将所有关键点按 DFS 序排序，走过的边的数量为排序后相邻的点之间的距离。记走过的边的数量为 $cnt_e$，则此时这些关键点所构成的虚树的大小为 $\frac{cnt_e}{2}+1$。这时候可以直接暴力莫队，用 set 维护 DFS 序的前驱后继即可做到 $n\sqrt{m}\log n$。但这样是跑不过去的。发现只需要维护前驱后继，删除用链表可以做到 $\mathcal{O}(1)$，但不好执行加入操作。于是用一个只删不加的回滚莫队即可。

### 法二：

可以用 bitset 按 $\log n$ 分块，类似于由乃救爷爷。但我不会 。

### 法三：

还有一种计算点集大小的方法，用数据结构维护一下，直接标记所有关键点走到某一个节点所经过的边，然后查询被标记的边的数量，这样配合回滚莫队也可以做到 $\mathcal{O}(n\sqrt{m}\log^2n)$。$2\log$ 是因为用的是树链剖分。是不能通过的。

想一下为什么会这么麻烦。发现是因为必须要钦定某一个特定的点与其它点的路径标记。考虑能否将这个点固定下来。钦定这个点为 $1$，并让 $1$ 作为根，看看会有什么变化。令 $anc=\text{lca}\{c_j\}(j\in [l,r])$，发现多出的答案就是 $dep_{anc}-dep_1$，其中 $\text{lca}\{S\}$ 可以用 ST 表处理出。这样就可以不用回滚了。现在已经简单了不少，考虑如何去掉根号。

考虑离线后按 $r$ 排序，以时间为值进行覆盖，则此时 $anc$ 内值 $\ge l$ 的边就一定会被统计。这时 $anc$ 的子树外的边不会统计，但是这些边被被赋的值一定是当前最大的，直接减去即可。这是转化为了路径赋值 $(1,u)$，全局查询值在某个区间的数的个数。

暴力的维护是简单的，直接上分块即可。

但这样的时间复杂度依然很高。想想区间赋值，可以直接用 ODT。这里 ODT 的复杂度显然是可以保证的，但是每次查询暴力扫一遍 $1\sim m$ 的话会炸，再用一棵 BIT 维护值域即可。

有更优的实现方式：参考 Leasier 的思路，发现是对每条重链前缀赋值，可以使用 vector 替代 ODT。

时间复杂度：$\mathcal{O}((n+q)\log^2n)$，这里认为 $n,m$ 同阶。

空间复杂度：$\mathcal{O}(n\log n)$

代码：
```cpp
const int N=1e5+10;
int n,m,Q;
int a[N],st[18][N],log_2[N],ans[N];
struct BIT{
	int v[N];
	void add(int x,int y){assert(x);for(;x<=m;x+=x&-x)v[x]+=y;}
	int ask(int x){
		int res=0;
		for(;x;x-=x&-x)res+=v[x];
		return res;
	}
} T;
int head[N],cnt_e=1;
struct edge{int v,nxt;} e[N<<1];
void adde(int u,int v){
	e[++cnt_e]=(edge){v,head[u]};
	head[u]=cnt_e;
}
int dfc,dfn[N],rdfn[N],sz[N],hv[N],d[N],fa[N],top[N];
void dfs1(int u,int fath){
	sz[u]=1,d[u]=d[fath]+1,fa[u]=fath;
	for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].v)!=fath){
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[hv[u]])hv[u]=v;
	}
}
void dfs2(int u,int tp){
	rdfn[dfn[u]=++dfc]=u,top[u]=tp;
	if(!hv[u])return;
	dfs2(hv[u],tp);
	for(int i=head[u],v;i;i=e[i].nxt)if((v=e[i].v)!=hv[u]&&v!=fa[u])dfs2(v,v);
}
int glca(int u,int v){
	while(top[u]!=top[v]){
		if(d[top[u]]<d[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	if(d[u]<d[v])swap(u,v);
	return v;
}
int qlca(int l,int r){
	int k=log_2[r-l+1];
	return glca(st[k][l],st[k][r-(1<<k)+1]);
}
vector<int> vec[N];pii q[N];
struct ODT{
	int l,r;mutable int v;
	ODT(const int &tl,const int &tr,const int &tv){l=tl;r=tr;v=tv;}
	friend bool operator<(ODT a,ODT b){return a.l<b.l;}
};
set<ODT> odt;
typedef set<ODT>::iterator iter;
iter split(int x){
	iter it=--odt.upper_bound((ODT){x,0,0});
	if(it->l==x)return it;
	assert(it!=odt.end());
	int l=it->l,r=it->r,v=it->v;
	odt.erase(it);
	odt.insert((ODT){l,x-1,v});
	return odt.insert((ODT){x,r,v}).first;
}
void assign(int l,int r,int tim){
	iter itr=split(r+1),itl=split(l);
	for(iter it=itl;it!=itr;it++)T.add(m-it->v+1,-(it->r-it->l+1));
	odt.erase(itl,itr);
	odt.insert((ODT){l,r,tim});
	T.add(m-tim+1,r-l+1);
}
void upd(int u,int tim){
	while(u){
		assign(dfn[top[u]],dfn[u],tim);
		u=fa[top[u]];
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&Q);odt.insert((ODT){1,n,0});
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	for(int i=1;i<=m;i++)scanf("%d",&a[i]),st[0][i]=a[i];
	dfs1(1,0),dfs2(1,1);
	for(int i=2;i<=m;i++)log_2[i]=log_2[i>>1]+1;
	for(int i=1;i<=17;i++)for(int j=1;j+(1<<i)-1<=m;j++)st[i][j]=glca(st[i-1][j],st[i-1][j+(1<<i-1)]);
	for(int i=1;i<=Q;i++)cin>>q[i].first>>q[i].second,vec[q[i].second].eb(i),ans[i]=-d[qlca(q[i].first,q[i].second)]+d[1];
	for(int i=1;i<=m;i++){
		upd(a[i],i);
		for(int j:vec[i])ans[j]+=T.ask(m-q[j].first+1);
	}
	for(int i=1;i<=Q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Leasier (赞：10)

简单题，记录一下这个套路。

------------

考虑离线下来扫描线，按 $l$ 从大到小排序，则我们需要查询有多少个点满足在 $r$ 处可以取到。

不妨进行一个容斥：$\forall l \leq i \leq r$，将 $c_i$ 到根的链染色，则答案为被染色的点数减去 $\operatorname{depth}_{\operatorname{LCA}_{i = l}^r c_i} - 1$。

考虑在扫到 $i$ 时通过树链剖分 + ODT 对 $c_i$ 到根染成 $i$ 这种颜色并用一棵 BIT 维护每种颜色的出现次数，则前者我们可以在 BIT 上查询被染成的颜色 $\leq r$ 的点数；后者上线段树处理区间 LCA 即可。

时间复杂度为 $O(n + m \log^2 n + q \log n \log m)$。

------------

注意到我们事实上并不需要真的去实现一个 ODT：在每条重链上的操作相当于一次前缀赋值，于是我们可以用 vector 从深到浅地维护连续段。这样会更好写，常数也会小很多。

------------

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

namespace BIT {
	int tree[100007];
	
	inline int lowbit(int x){
		return x & (-x);
	}
	
	inline void add(int n, int x, int k){
		while (x <= n){
			tree[x] += k;
			x += lowbit(x);
		}
	}
	
	inline int get_sum(int x){
		int ans = 0;
		while (x > 0){
			ans += tree[x];
			x -= lowbit(x);
		}
		return ans;
	}
}

int fa[100007], depth[100007], top[100007], c[100007];

inline int lca(int u, int v){
	if (u == 0) return v;
	if (v == 0) return u;
	while (top[u] != top[v]){
		if (depth[top[u]] < depth[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return depth[u] < depth[v] ? u : v;
}

namespace SegmentTree {
	typedef struct {
		int l;
		int r;
		int lca;
	} Node;
	
	Node tree[400007];
	
	inline void update(int x){
		tree[x].lca = lca(tree[x * 2].lca, tree[x * 2 + 1].lca);
	}
	
	void build(int x, int l, int r){
		tree[x].l = l;
		tree[x].r = r;
		if (l == r){
			tree[x].lca = c[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(x * 2, l, mid);
		build(x * 2 + 1, mid + 1, r);
		update(x);
	}
	
	int get_lca(int x, int l, int r){
		if (l <= tree[x].l && tree[x].r <= r) return tree[x].lca;
		int mid = (tree[x].l + tree[x].r) >> 1, ans = 0;
		if (l <= mid) ans = get_lca(x * 2, l, r);
		if (r > mid) ans = lca(ans, get_lca(x * 2 + 1, l, r));
		return ans;
	}
}

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct {
	int id;
	int l;
	int r;
} Query;

typedef struct Segment_tag {
	int down;
	int color;
	Segment_tag(){}
	Segment_tag(int down_, int color_){
		down = down_;
		color = color_;
	}
} Segment;

int cnt = 0;
int head[100007], size[100007], hs[100007], in[100007], bottom[100007], out[100007], ans[100007];
Edge edge[200007];
Query query[100007];
vector<Segment> v[100007];

bool operator <(const Query a, const Query b){
	return a.l > b.l;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father){
	fa[u] = father;
	depth[u] = depth[father] + 1;
	size[u] = 1;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (x != father){
			dfs1(x, u);
			size[u] += size[x];
			if (hs[u] == 0 || size[hs[u]] < size[x]) hs[u] = x;
		}
	}
}

void dfs2(int u, int cur_top, int &id){
	in[u] = ++id;
	top[u] = cur_top;
	if (hs[u] == 0){
		bottom[cur_top] = u;
	} else {
		dfs2(hs[u], cur_top, id);
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != fa[u] && x != hs[u]) dfs2(x, x, id);
		}
	}
	out[u] = id;
}

inline void update(int u, int color, int n){
	while (u != 0){
		int pre = depth[top[u]] - 1;
		Segment cur;
		while (true){
			cur = v[top[u]].back();
			if (depth[u] <= depth[cur.down]) break;
			v[top[u]].pop_back();
			if (cur.color != 0) BIT::add(n, cur.color, -(depth[cur.down] - pre));
			pre = depth[cur.down];
		}
		if (cur.color != 0) BIT::add(n, cur.color, -(depth[u] - pre));
		if (cur.down == u) v[top[u]].pop_back();
		BIT::add(n, color, depth[u] - depth[top[u]] + 1);
		v[top[u]].push_back(Segment(u, color));
		u = fa[top[u]];
	}
}

int main(){
	int n, m, q, id = 0;
	scanf("%d %d %d", &n, &m, &q);
	for (register int i = 1; i < n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		add_edge(a, b);
		add_edge(b, a);
	}
	dfs1(1, 0);
	dfs2(1, 1, id);
	for (register int i = 1; i <= n; i++){
		if (top[i] == i) v[i].push_back(Segment(bottom[i], 0));
	}
	for (register int i = 1; i <= m; i++){
		scanf("%d", &c[i]);
	}
	SegmentTree::build(1, 1, m);
	for (register int i = 1; i <= q; i++){
		scanf("%d %d", &query[i].l, &query[i].r);
		query[i].id = i;
	}
	sort(query + 1, query + q + 1);
	for (register int i = m, j = 1; i >= 1; i--){
		update(c[i], i, m);
		while (j <= q && query[j].l == i){
			ans[query[j].id] = BIT::get_sum(query[j].r) - (depth[SegmentTree::get_lca(1, i, query[j].r)] - 1);
			j++;
		}
	}
	for (register int i = 1; i <= q; i++){
		cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：Maverik (赞：8)

### statement

给出一颗 $n$ 个节点的树，和一个长度为 $m$ 的序列 $a$，$q$ 次询问包含 $a_{l\cdots r}$ 中所有节点的最小联通块大小。 $n,m,q\le 10^5$

### solution

经过一些转化，加入一个点的贡献仅与以 dfs 序为关键字的前驱后继有关，考虑莫队，和秃子酋长一样拿链表回滚一下就好了，有点细节，代码只有不几行。

时间复杂度 $O(n\sqrt n)$。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m,Q,a[maxn],ans[maxn],st[maxn][20],dep[maxn],dfn[maxn],mp[maxn],POS,key[maxn],Pos,unk[maxn];
vector<int>e[maxn];
inline void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1,dfn[++POS]=x,mp[x]=POS,key[x]=++Pos,unk[Pos]=x;
    for(auto y:e[x]) if(y!=fa) dfs(y,x),dfn[++POS]=x;
}
inline int lca(int l,int r)
{
    l=mp[l],r=mp[r]; if(l>r) swap(l,r); int t=__lg(r-l+1);
    return (dep[st[l][t]]<dep[st[r-(1<<t)+1][t]])?st[l][t]:st[r-(1<<t)+1][t];
}
inline int dis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}
int buc[maxn],Cur,recbuc[maxn],bl[maxn],L[maxn],R[maxn],blen,bnum;
struct Ques{int l,r,id;}q[maxn];
struct List
{
    int nxt[maxn],pre[maxn],head,tail;
    inline void init()
    {
        for(int i=1,prev=0;i<=n;i++) if(buc[i])
        { 
            if(!head) {head=tail=i,prev=i;continue;}
            pre[i]=prev,nxt[prev]=i,tail=i,Cur+=dis(unk[prev],unk[i]),prev=i;
        }
        Cur+=dis(unk[head],unk[tail]);
    }
    inline void del(int x)
    {
        int Pre=pre[x],Nxt=nxt[x]; if(!Pre && !Nxt) head=tail=0,Cur=0;
        if(Pre && Nxt) Cur+=dis(unk[Pre],unk[Nxt])-dis(unk[Nxt],unk[x])-dis(unk[Pre],unk[x]);
        if(!Pre&& Nxt) Cur+=dis(unk[Nxt],unk[tail])-dis(unk[x],unk[Nxt])-dis(unk[x],unk[tail]),head=Nxt;
        if(Pre &&!Nxt) Cur+=dis(unk[Pre],unk[head])-dis(unk[x],unk[Pre])-dis(unk[x],unk[head]),tail=Pre;
        nxt[Pre]=Nxt,pre[Nxt]=Pre;
    }
    inline void add(int x)
    {if(!head)head=tail=x;if(pre[x]==tail)tail=x;if(nxt[x]==head)head=x;nxt[pre[x]]=pre[nxt[x]]=x;}
}lst,tmp;
inline void solve()
{
    cin>>n>>m>>Q;
    for(int i=1,x,y;i<n;i++) cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=1,l,r;i<=Q;i++) cin>>l>>r,q[i]={l,r,i};
    dfs(1,0);for(int i=1;i<=POS;i++) st[i][0]=dfn[i];
    for(int j=1;j<=__lg(POS);j++) for(int i=1;i+(1<<j)-1<=POS;i++)
        st[i][j]=(dep[st[i][j-1]]<dep[st[i+(1<<(j-1))][j-1]])?st[i][j-1]:st[i+(1<<(j-1))][j-1];
    blen=sqrt(m),bnum=ceil(1.0*m/blen);
    for(int i=1;i<=bnum;i++) L[i]=R[i-1]+1,R[i]=min(L[i]+blen-1,m);
    for(int i=1;i<=bnum;i++) for(int j=L[i];j<=R[i];j++) bl[j]=i;
    sort(q+1,q+Q+1,[](const Ques&A,const Ques&B){return bl[A.l]==bl[B.l]?A.r>B.r:A.l<B.l;});
    for(int i=1;i<=m;i++) buc[key[a[i]]]++; lst.init();
    for(int i=1,l=1,r=m,pos=1,rec,old;i<=bnum && pos<=Q;i++)
    {
        while(l<L[i]){buc[key[a[l]]]--;if(!buc[key[a[l]]])lst.del(key[a[l]]);l++;}
        rec=Cur,tmp=lst; for(int i=1;i<=n;i++) recbuc[i]=buc[i];
        while(bl[q[pos].l]==i)
        {
            while(r>q[pos].r){buc[key[a[r]]]--;if(!buc[key[a[r]]])lst.del(key[a[r]]);r--;} old=Cur;
            while(l<q[pos].l){buc[key[a[l]]]--;if(!buc[key[a[l]]])lst.del(key[a[l]]);l++;} ans[q[pos].id]=Cur;
            while(L[i]<l){l--;if(!buc[key[a[l]]]) lst.add(key[a[l]]);buc[key[a[l]]]++;} Cur=old,pos++;
        } Cur=rec,lst=tmp,r=m; for(int i=1;i<=n;i++) buc[i]=recbuc[i];
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]/2+1<<'\n';
}
signed main(){ios::sync_with_stdio(false);cin.tie(NULL);solve();}
```



---

## 作者：Mobius127 (赞：7)

[题传](https://www.luogu.com.cn/problem/P9340)

连通块大小 = 边数 + 连通块个数

那么边数珂以转化为虚树上的边权和（边权为 $dep_{y}-dep_{x}$），连通块个数就是 1。

静态区间询问，设分治区间为 $[l,r]$，待处理询问 $[x, y]$。

考虑一条边 $e$ 什么时候有贡献，在其的两侧的点集 $In, Out$ 中，对于某个询问 $[x, y]$，都至少有一个点在 $[x, y]$ 中。

不妨标记 $[l, mid]$ 的点为黑点，$(mid, r]$ 的点为白点，一侧最大的黑点编号 $\ge x$，另一侧最小白点编号 $\le y$，如果直接用 $In, Out$ 的两侧限制进行四维数点珂以~~轻松~~做到 $O(n\log^4 n)$。

考虑剪枝，两侧同时限制太过于麻烦，若 $e$ 两侧分别存在一个黑点 $b$ 和白点 $w$，当询问包含 $b, w$ 时 $e$ 就必然会被选上，注意到我们猫树分治时处理的询问必然是跨过了 $mid, mid+1$ 的，而这两个点正好又是一黑一白，于是对于 $e$ 只需要考察 $mid, mid+1$ 是否在同一侧，若异侧则 $e$ 一定会被选择，否则只需要考察另一侧是否满足 $\max_{p\in black}id_{p}\ge x \vee \min_{p\in white} id_{p}\le y$，这个容斥后是珂以用二维数点解决的。

复杂度 $T(n)=2T(n/2)+O(n\log n) \Longrightarrow  T(n)=O(n\log^2 n)$。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <vector>
#include <queue>
#include <bitset>
#include <cmath>
#include <set>
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define st first
#define nd second
using namespace std;
typedef long long ll;
typedef pair <int, int> Pii;
const int INF=0x3f3f3f3f;
const int cp=998244353;
inline int mod(int x){if(x>=cp) x-=cp;if(x<0) x+=cp;return x;}
inline void plust(int &x, int y){x=mod(x+y);return ;}
inline void minut(int &x, int y){x=mod(x-y);return ;}
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a, int b=cp-2){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%cp)
		if(b&1) ret=1ll*ret*a%cp;
	return ret;
}
const int N=1e5+5;
int n, m, cnt, Q, a[N], ST[20][N], dfn[N], ed[N], fa[N], dep[N];
struct Ask{int ans, l, r;}q[N];vi G[N];
void dfs(int x){ST[0][dfn[x]=++cnt]=x;for(auto v:G[x]) if(!dep[v]) dep[v]=dep[fa[v]=x]+1, dfs(v);ed[x]=cnt;}
bool cmp(int x, int y){return dep[x]<dep[y];}
int chk(int x, int y){return cmp(x, y)?x:y;}
bool cmb(int x, int y){return dfn[x]<dfn[y];}
int LCA(int x, int y){
	if(!x||!y) return x+y;
	if(x==y) return x;x=dfn[x], y=dfn[y];if(x>y) swap(x, y);
	int k=__lg(y-x);return fa[chk(ST[k][x+1], ST[k][y-(1<<k)+1])];
}
int tot, top, sta[N<<1], els, b[N], w[N], B[N], W[N];vi T[N];
struct node{int x, y, v;bool operator < (const node &X){return x<X.x;}}pt[N<<1];
void pre(int x){for(auto v:T[x]) pre(v), els+=dep[v]-dep[x], B[x]=max(B[x], B[v]), W[x]=min(W[x], W[v]);}
void calc(int x, int mid, int Bb=0, int Ww=m+1){
	vi bpr, bsf, wpr, wsf;int Ts=T[x].size();
	bpr.resize(Ts, 0), bsf.resize(Ts, 0);
	wpr.resize(Ts, m+1), wsf.resize(Ts, m+1);
	for(int i=1; i<=Ts-1; ++i) bpr[i]=max(bpr[i-1], B[T[x][i-1]]);
	for(int i=Ts-2; i>=0; --i) bsf[i]=max(bsf[i+1], B[T[x][i+1]]);
	for(int i=1; i<=Ts-1; ++i) wpr[i]=min(wpr[i-1], W[T[x][i-1]]);
	for(int i=Ts-2; i>=0; --i) wsf[i]=min(wsf[i+1], W[T[x][i+1]]);
	for(int i=0; i<Ts; ++i){
		int v=T[x][i];
		int bb=max(max(Bb, b[x]), max(bpr[i], bsf[i]));
		int ww=min(min(Ww, w[x]), min(wpr[i], wsf[i]));
		calc(v, mid, bb, ww);
		int m0=(dfn[v]<=dfn[a[mid]]&&dfn[a[mid]]<=ed[v]);
		int m1=(dfn[v]<=dfn[a[mid+1]]&&dfn[a[mid+1]]<=ed[v]);
		if(m0==m1) pt[++tot]=(node){m0?bb:B[v], m1?ww:W[v], dep[v]-dep[x]};
	}
	vi ().swap(T[x]);
}
#define lowbit(x) (x&(-x))
int bit[N];
void add(int x, int t){for(++x; x<=m+2; x+=lowbit(x)) bit[x]+=t;return  ;}
int query(int x, int r=0){for(++x; x; x-=lowbit(x)) r+=bit[x];return r;}
#undef lowbit
void work(int l, int r, vi &qe){
	int mid=l+r>>1;els=top=tot=0;
	for(int i=l; i<=r; ++i) sta[++top]=a[i];sort(sta+1, sta+top+1, cmb);
	for(int i=1; i<r-l+1; ++i) sta[++top]=LCA(sta[i], sta[i+1]);
	sort(sta+1, sta+top+1, cmb);top=unique(sta+1, sta+top+1)-sta-1;
	for(int i=1; i<top; ++i) T[LCA(sta[i], sta[i+1])].pb(sta[i+1]);
	for(int i=l; i<=mid; ++i) B[a[i]]=b[a[i]]=i;
	for(int i=r; i>mid; --i) W[a[i]]=w[a[i]]=i;
	pre(sta[1]), calc(sta[1], mid);sort(pt+1, pt+tot+1);int x=1;
	for(auto v:qe){
		while(x<=tot&&pt[x].x<q[v].l) add(pt[x].y, pt[x].v), ++x;
		q[v].ans=els-query(m+1)+query(q[v].r);
	}
	for(int i=1; i<x; ++i) add(pt[i].y, -pt[i].v);
	for(int i=1; i<=top; ++i) b[sta[i]]=B[sta[i]]=0, w[sta[i]]=W[sta[i]]=m+1;
}
void solve(int l, int r, vi &qe){
	if(l==r) return ;int mid=l+r>>1;vi L, M, R;
	for(auto v:qe) if(q[v].r<=mid) L.pb(v);
	else if(q[v].l>mid) R.pb(v);else M.pb(v);
	solve(l, mid, L);solve(mid+1, r, R);
	if(M.size()) work(l, r, M);
}
bool cmd(int x, int y){return q[x].l<q[y].l;}
signed main(){
	n=read(), m=read(), Q=read();vi tmp;
	for(int i=2, a, b; i<=n; ++i)
		a=read(), b=read(), G[a].pb(b), G[b].pb(a);
	for(int i=1; i<=m; ++i) a[i]=read();
	for(int i=1; i<=n; ++i) b[i]=B[i]=0, w[i]=W[i]=m+1;
	for(int i=1; i<=Q; ++i) q[i].l=read(), q[i].r=read(), tmp.pb(i);
	dfs(dep[1]=1);
	for(int i=1; i<=__lg(n); ++i) 
		for(int x=1; x+(1<<i)-1<=n; ++x) 
			ST[i][x]=chk(ST[i-1][x], ST[i-1][x+(1<<i-1)]);
	sort(tmp.begin(), tmp.end(), cmd);
	solve(1, m, tmp);
	for(int i=1; i<=Q; ++i) printf("%d\n", q[i].ans+1);
	return 0;
}
```



---

## 作者：Sanyueyetu (赞：3)

大家怎么都用这么复杂的数据结构呀，机房大佬 AVENGER_M 对此表示不服。
### 分析
容易发现询问即为求给定点集到这个点集的最近公共祖先的链并包含的点数。考虑容斥，转化为求给定点集到根的链并包含的点数减去这个点集的最近公共祖先的深度。后者等于这个点集两两最近公共祖先深度的最小值，可以用 st 表求，考虑如何求前者。

考虑求每一个点对哪些询问有贡献。发现一个点对询问有贡献当且仅当询问的点集里有这个点子树里的点，因此可以使用 dsu on tree。建一个 set，每次访问到一个点 $u$ 时加入每一个轻儿子子树里的点 $v$ 对应的所有“景点”的位置 $pos$。记这个位置的前驱为 $l$，后继为 $r$，则 $pos$ 被所有左端点在 $[l+1,pos]$，右端点在 $[pos,r-1]$ 内的询问包含，即 $u$ 对它们有贡献。这样避免了算重复。对于重儿子，我们考虑直接让重儿子给询问加上它在这条重链上的祖先的贡献，这样就不会超时了。

询问时考虑扫描线，把询问按照左端点从大到小排序，动态的加入或删除每个点的贡献

时间复杂度 $O(n \log^2 n)$，细节见代码
### Code
```
#include<iostream>
#include<vector>
#include<set>
using namespace std;
#define lowbit(x) x&-x
int tree[100010];
int n,m,q,a[100010],a1,a2;
int siz[100010],son[100010];
int top[100010],dep[100010];
struct node{
	int nowl,nowr,cnt;
};
int ans[100010],f[100010];
vector<node>ad[100010],del[100010];
vector<pair<int,int>>v[100010];
vector<int>pos[100010],g[100010];
int L[100010],R[100010],id[100010],tot;
int st[100010][20],lg[100010];
set<int>s;
set<int>::iterator it;
void addbit(int x,int num){
	while(x<=m){
		tree[x]+=num;
		x+=lowbit(x);
	}
}
int querybit(int x){
	int res=0;
	while(x>0){
		res+=tree[x];
		x-=lowbit(x);
	}
	return res;
}
void dfs(int x,int fa){
	f[x]=fa;
	siz[x]=1;
	dep[x]=dep[fa]+1;
	L[x]=++tot;
	id[tot]=x;
	for(int y:g[x]){
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
	R[x]=tot;
}
void dfs2(int x,int fa,int tp){
	top[x]=tp;
	if(son[x]) dfs2(son[x],x,tp);
	for(int y:g[x]){
		if(y==fa||y==son[x]) continue;
		dfs2(y,x,y);
	}
}
void add(int x,int num){
	int templ,tempr;
	for(int i=L[x];i<=R[x];i++){
		for(int j:pos[id[i]]){
			it=s.lower_bound(j);
			if(it==s.end()){
				tempr=m;
			}else{
				tempr=(*it)-1;
			}
			if(it==s.begin()) templ=1;
			else{
				it--;
				templ=(*it)+1;
			}
			del[templ-1].push_back({j,tempr,num});
			ad[j].push_back({j,tempr,num});
			s.insert(j);
		}
	}
}
void dsu(int x,int fa,bool keep){
	for(int y:g[x]){
		if(y==fa||y==son[x]) continue;
		dsu(y,x,0);
	}
	if(son[x]) dsu(son[x],x,1);
	int templ,tempr;
	for(int j:pos[x]){
		it=s.lower_bound(j);
		if(it==s.end()){
			tempr=m;
		}else{
			tempr=(*it)-1;
		}
		if(it==s.begin()) templ=1;
		else{
			it--;
			templ=(*it)+1;
		}
		if(!keep){
			del[templ-1].push_back({j,tempr,1});
			ad[j].push_back({j,tempr,1});
		}else{
			del[templ-1].push_back({j,tempr,dep[x]-dep[top[x]]+1});
			ad[j].push_back({j,tempr,dep[x]-dep[top[x]]+1});
		}
		s.insert(j);
	}
	for(int y:g[x]){
		if(y==fa||y==son[x]) continue;
		if(!keep) add(y,1);
		else add(y,dep[x]-dep[top[x]]+1);
	}
	if(!keep) s.clear();
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=f[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	return y;
}
void init(){
	for(int i=2;i<=m;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<m;i++){
		st[i][0]=dep[lca(a[i],a[i+1])];
	}
	for(int i=1;i<=lg[m];i++){
		for(int j=1;j<=m;j++){
			st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
		}
	}
}
int queryst(int x,int y){
	return min(st[x][lg[y-x+1]],st[y-(1<<lg[y-x+1])+1][lg[y-x+1]]);
}
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<n;i++){
		scanf("%d%d",&a1,&a2);
		g[a1].push_back(a2);
		g[a2].push_back(a1);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
		pos[a[i]].push_back(i);
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a1,&a2);
		v[a1].push_back({a2,i});
	}
	dfs(1,0);
	dfs2(1,0,1);
	dsu(1,0,1);
	init();
	for(int i=m;i>0;i--){
		for(auto j:del[i]){
			addbit(j.nowl,-j.cnt);
			addbit(j.nowr+1,j.cnt);
		}
		for(auto j:ad[i]){
			addbit(j.nowl,j.cnt);
			addbit(j.nowr+1,-j.cnt);
		}
		for(auto j:v[i]){
			if(j.first==i){
				ans[j.second]=1;
				continue;
			}
			ans[j.second]=querybit(j.first)-queryst(i,j.first-1)+1;
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]);
	}
}
```

---

## 作者：_lbw_ (赞：3)

大家好，我喜欢暴力数据结构，于是我就用 bitset（Au jzp 的最爱） 在 luogu 上过了这题。

观察得知求的是区间虚树点数，我们考虑将相邻点的路径上的**边**全部点亮，虚树大小就是边数加一。

考虑 bitset，我们先求出根到每个点的 bitset，然后将两点异或就得到了路径的 bitset。

接下来就是区间查询 bitset 或的 popcount。

首先，我们发现空间寄了，于是每次只算一个值域区间的 popcount。

其次，如果用分治/线段树等算法，我们发现时间寄了

这与区间最小值是类似的，可以使用 由乃救爷爷 那题的做法。

每 $\log n$ 个数分一块，块间 st 表，块内暴力，前缀后缀预处理。

两个点在一块是 $\mathcal{O}(\dfrac{n\log n}w)$ 的，但是此时区间长极小，我们可以暴力建虚树。

总时间复杂度 $\mathcal{O}(n\log n+\dfrac{n^2}w)$。

我的实现没写区间长极小的情况，直接暴力。

同时记得手写 bitset。

```cpp
mt19937 rnd(her1);
const int Lim = 10000;
const int maxn = 1e5+5;
const int MAX = Lim/64+2;
// ll B[65536];IV init(){F(i,0,65535)B[i]=B[i>>1]+(i&1);}
ll n,m,q,ans[maxn],l[maxn],r[maxn],c[maxn];vector<ll>g[maxn];
const int B = 30;
struct Bitset{
	ull w[Lim/64+5];
	IV reset(){mem(w,0);}
	IV reset(ll x){w[x>>6]|=(1ull<<(x&63ull));}
	I count(){
		ll cnt=0;
		F(i,0,MAX)cnt+=__builtin_popcountll(w[i]);
		//B[w[i]&65535]+B[w[i]>>16ull&65535]+B[w[i]>>32ull&65535]+B[w[i]>>48ull&65535];
		return cnt;
	}
}bit[maxn],tmp[maxn],pre[maxn],suf[maxn],st[maxn/B+5][17],orz;
Bitset operator|(const Bitset&A,const Bitset&B){
	Bitset nw;nw.reset();
	F(i,0,MAX)nw.w[i]=A.w[i]|B.w[i];
	return nw;
}
Bitset operator^(const Bitset&A,const Bitset&B){
	Bitset nw;nw.reset();
	F(i,0,MAX)nw.w[i]=A.w[i]^B.w[i];
	return nw;
}

struct node{ll l,r,id;};vector<node>V;
ll wl[maxn],wr[maxn],w[maxn];
IV dfs(ll u,ll F,ll l,ll r){
	for(ll v:g[u])if(v^F){
		bit[v]=bit[u];
		if(l<=v&&v<=r)bit[v].reset(v-l);dfs(v,u,l,r);
	}
}
ll lg[maxn];IV init(ll n){lg[0]=-1;F(i,1,n)lg[i]=lg[i>>1]+1;}
Bitset Q(ll l,ll r){if(l>r)return orz;ll k=lg[r-l+1];return st[l][k]|st[r-(1<<k)+1][k];}
IV solve(ll n){
	// F(i,1,q){
	// 	orz.reset();
	// 	F(j,l[i],r[i])orz=orz|tmp[j];
	// 	ans[i]+=orz.count();
	// }
	init(n);
	ll cB=(n-1)/B+1;F(i,1,n)w[i]=(i-1)/B+1;
	F(i,1,cB)wl[i]=wr[i-1]+1,wr[i]=i*B;wr[cB]=n;
	F(i,1,cB){
		st[i][0].reset();F(j,wl[i],wr[i])st[i][0]=st[i][0]|tmp[j];
		pre[wl[i]]=tmp[wl[i]];F(j,wl[i]+1,wr[i])pre[j]=pre[j-1]|tmp[j];
		suf[wr[i]]=tmp[wr[i]];D(j,wr[i]-1,wl[i])suf[j]=suf[j+1]|tmp[j];
	}
	F(j,1,16)F(i,1,cB-(1<<j)+1)st[i][j]=st[i][j-1]|st[i+(1<<j-1)][j-1];

	F(i,1,q)if(l[i]<=r[i]){
		ll x=l[i],y=r[i],wx=w[x],wy=w[y];orz.reset();
		if(wx==wy){F(j,x,y)orz=orz|tmp[j];ans[i]+=orz.count();}
		else ans[i]+=(Q(wx+1,wy-1)|suf[x]|pre[y]).count();
	}
}
IV calc(ll l,ll r){
	F(i,1,m)bit[i].reset();dfs(1,0,l,r);
	F(i,1,m-1)tmp[i]=bit[c[i]]^bit[c[i+1]];solve(m-1);
}
int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	n=read();m=read();q=read();//init();
	F(i,1,n-1){
		ll u=read(),v=read();
		g[u].push_back(v);g[v].push_back(u);
	}
	F(i,1,m)c[i]=read();
	F(i,1,q)l[i]=read(),r[i]=read()-1;
	for(ll l=1,r=0;l<=n;l=r+1)r=min(r+Lim,n),calc(l,r);
	F(i,1,q)printf("%d\n",ans[i]+1);return 0;
}
```


---

## 作者：Dantal10n (赞：2)

鉴于本题已有的树剖题解全都求了区间 LCA，下面记录一个更为简明的做法。

包含 ${a_l,a_{l+1},\cdots,a_r}$ 中所有节点的最小联通块 $=\bigcup_{i=l}^{r-1} \text{PATH}(a_i,a_{i+1})$。

直接将相邻两点间路径树剖拆成 $\log_2n$ 个 dfs 序上区间。

题目变为有 $m\log_2n$ 个值域为 $[1,n]$ 的区间 $[cl_i,cr_i]$，每次给出 $l,r$ 询问 $\bigcup_{i=l}^{r} [cl_i,cr_i]$（$l,r+1$ 总共只有 $m$ 种取值，但好像没啥用）。

扫描线一下变成区间覆盖和全局 $\ge v$ 的数个数查询，可以简单用颜色段均摊和树状数组维护。

时间复杂度 $O(m\log_2n\log_2m)$。

超短 1.5KB 代码：
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,q,a[N],ql[N],qr[N],p[N],bit[N];
int son[N],sz[N],timer,tI[N],id[N],tp[N],ans[N],d[N];
vector<int> to[N],qq[N];
void add(int u,int v){to[u].push_back(v);}
void dfs(int u){
	sz[u]=1;
	for(int v:to[u])if(v^p[u]){
		d[v]=d[u]+1,p[v]=u,dfs(v),sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
void sfd(int u){
	id[tI[u]=++timer]=u;
	if(son[u])tp[son[u]]=tp[u],sfd(son[u]);
	for(int v:to[u])if(v^p[u])if(v^son[u])tp[v]=v,sfd(v);
}
void upd(int x,int val){while(x<=m)bit[x]+=val,x+=x&-x;}
int qry(int x){int r=0;while(x)r+=bit[x],x-=x&-x;return r;}
map<int,int> mp;
void spt(int x){auto it=prev(mp.upper_bound(x));mp[x]=it->second;}
void asn(int l,int r,int v){
	spt(l),spt(r+1);
	auto it=mp.find(l);
	while(it->first<=r){
		int len=next(it)->first-it->first;
		upd(it->second,-len);
		it=mp.erase(it);
	}
	mp[l]=v,upd(v,r-l+1);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>q;
	for(int i=1,u,v;i<n;i++)
		cin>>u>>v,add(u,v),add(v,u);
	dfs(1),tp[1]=1,sfd(1);
	for(int i=1;i<=m;i++)cin>>a[i];
	for(int i=1;i<=q;i++){
		cin>>ql[i]>>qr[i];
		if(ql[i]==qr[i])ans[i]=1;
		else qq[qr[i]].push_back(i);
	}
	mp[1]=1,upd(1,n),mp[n+1]=-1;
	for(int i=2;i<=m;i++){
		int u=a[i-1],v=a[i];
		while(tp[u]^tp[v]){
			if(d[tp[u]]<d[tp[v]])swap(u,v);
			asn(tI[tp[u]],tI[u],i),u=p[tp[u]];
		}
		if(d[u]<d[v])swap(u,v);
		asn(tI[v],tI[u],i);
		for(int j:qq[i])
			ans[j]=n-qry(ql[j]);
	}
	for(int i=1;i<=q;i++)
		cout<<ans[i]<<'\n';
	return 0;
}
```

附：“将相邻两点间路径树剖拆成 $\log_2n$ 个区间”时，用正常的 LCA 做法非常不牛。来自 @[0x3b800001](https://www.luogu.com.cn/user/306090) 的牛气冲天拆法：
```cpp
map<int,bool>D;
for(int i=u;i;i=fa[top[i]])
	D[dfn[top[i]]]^=1,D[dfn[i]+1]^=1;
for(int i=v;i;i=fa[top[i]])
	D[dfn[top[i]]]^=1,D[dfn[i]+1]^=1;
int l=1;
bool sd=0;
for(auto[i,d]:D){
	if(sd)intervals.push_back(make_pair(l,i-1));
	l=i,sd^=d;
}
```

---

## 作者：cwfxlh (赞：2)

# [P9340](https://www.luogu.com.cn/problem/P9340)      

题目相当于询问区间内的点构成的虚树大小，以 $1$ 为根建树，则答案为 $\sum_{u}v_u-(dep_{root}-1)$，对于一个点 $u$，$v_u=1$ 当且仅当其子树内存在一个点被选中。     

这个式子后半部分是好算的，对于区间 dfs 序最大和最小的点取 lca 即可得到根，于是考虑前半部分。     

对于一个固定的 $l$，$v_u=1$ 当且仅当 $r\ge mn_u$，这里的 $mn_u$ 是一个未知的，与 $l$ 相关的一个阈值。我们发现，对于每个点，它的贡献相当于一个 $\ge mn_u$ 的后缀加。于是我们更新 $mn_u$ 的时候可以使用树状数组维护。       

至于 $mn_u$ 应该怎么维护，可以考虑从后往前扫描 $l$，每新加入一个 $a_l$，则根节点到 $a_l$ 上的所有点的 $mn$ 均会变成 $l$，于是问题变成了一个链染色问题，我们用树剖将其放到区间上，就变成了 $O(n\log n)$ 次区间染色，使用 set 维护一下连续段即可，染色的时候如果颜色发生改变就 BIT 修改，复杂度 $O(n\log^2n)$。   

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,k1,k2,k3,k4,k5,k6,k7,k8,k9,dep[100003],F[100003][23],dfn[100003],k[100003],ndf[100003],dfnmk;
int STmn[23][100003],STmx[23][100003];
int sz[100003],mxson[100003],idx,mk[100003],tp[100003],num[100003],wz[100003];
vector<int>chn[100003];
int ans[100003],lg[100003],fsp[100003];
vector<pair<int,int> >lst[100003];
vector<int>E[100003];
int TreeAr[100003];
int QueryMin(int l,int r){return min(STmn[lg[r-l+1]][l],STmn[lg[r-l+1]][r-fsp[lg[r-l+1]]+1]);}
int QueryMax(int l,int r){return max(STmx[lg[r-l+1]][l],STmx[lg[r-l+1]][r-fsp[lg[r-l+1]]+1]);}
void dfs(int now,int p){
	dfn[now]=++dfnmk;
	ndf[dfnmk]=now;
	for(int i=1;;i++){
		if(F[F[now][i-1]][i-1]==0)break;
		F[now][i]=F[F[now][i-1]][i-1];
	}
	sz[now]=1;
	for(auto i:E[now]){
		if(i==p)continue;
		dep[i]=dep[now]+1;
		F[i][0]=now;
		dfs(i,now);
		if(sz[i]>sz[mxson[now]])mxson[now]=i;
		sz[now]+=sz[i];
	}
	return;
}
void dfs2(int now,int p,int col){
	if(!now)return;
	mk[now]=col;
	chn[col].emplace_back(now);
	dfs2(mxson[now],now,col);
	for(auto i:E[now]){
		if(i==p||i==mxson[now])continue;
		idx++;
		tp[idx]=i;
		dfs2(i,now,idx);
	}
	return;
}
int _lca(int X,int Y){
	if(dep[X]<dep[Y])swap(X,Y);
	int c=20;
	while(c--)if(dep[F[X][c]]>=dep[Y])X=F[X][c];
	c=20;
	while(c--)if(F[X][c]!=F[Y][c])X=F[X][c],Y=F[Y][c];
	if(X!=Y)return F[X][0];
	return X;
}
int lowbit(int X){return (X&(-X));}
void modify(int wz,int v){for(int i=wz;i<=m+1;i+=lowbit(i))TreeAr[i]+=v;return;}
int Query(int wz){int ret=0;for(int i=wz;i;i-=lowbit(i))ret+=TreeAr[i];return ret;}
struct Seg{
	int l;
	int r;
	int col;
}instzz;
set<Seg>R;
bool operator<(Seg X,Seg Y){
	if(X.l!=Y.l)return X.l<Y.l;
	return X.r<Y.r;
}
Seg mkpr(int l,int r,int col){
	instzz.l=l;
	instzz.r=r;
	instzz.col=col;
	return instzz;
}
int stk[100003][3],tot;
void ODTModify(int l,int r,int v){
	auto p1=R.lower_bound(mkpr(l,-1,-1));
	if(p1==R.end()||(*p1).l>l)p1--;
	int lft=-1,lc,rgt=-1,rc;
	tot=0;
	while(p1!=R.end()&&(*p1).l<=r){
		if((*p1).l<l){
			lft=(*p1).l;
			lc=(*p1).col;
		}
		if((*p1).r>r){
			rgt=(*p1).r;
			rc=(*p1).col;
		}
		stk[++tot][0]=(*p1).l;
		stk[tot][1]=(*p1).r;
		stk[tot][2]=(*p1).col;
		p1++;
	}
	for(int i=1;i<=tot;i++){
		R.erase(mkpr(stk[i][0],stk[i][1],stk[i][2]));
		modify(stk[i][2],-(stk[i][1]-stk[i][0]+1));
	}
	if(lft!=-1){
		R.insert(mkpr(lft,l-1,lc));
		modify(lc,(l-1)-lft+1);
	}
	if(rgt!=-1){
		R.insert(mkpr(r+1,rgt,rc));
		modify(rc,rgt-(r+1)+1);
	}
	R.insert(mkpr(l,r,v));
	modify(v,r-l+1);
	return;
}
void ChnModify(int now,int v){
	ODTModify(wz[tp[mk[now]]],wz[now],v);
	if(tp[mk[now]]!=1)ChnModify(F[tp[mk[now]]][0],v);
	return;
}
int main(){
	ios::sync_with_stdio(false);
	for(int i=2;i<=100000;i++)lg[i]=lg[i>>1]+1;
	for(int i=0;i<=30;i++)fsp[i]=(1<<i);
	cin>>n>>m>>q;
	for(int i=1;i<n;i++){
		cin>>k1>>k2;
		E[k1].emplace_back(k2);
		E[k2].emplace_back(k1);
	}
	dep[1]=1;
	dfs(1,0);
	tp[idx=1]=1;
	dfs2(1,0,1); 
	for(int i=1,j=0;i<=idx;i++){
		for(auto u:chn[i]){
			j++;
			num[j]=u;
			wz[u]=j;
		}
	}
	for(int i=1;i<=m;i++)cin>>k[i];
	for(int i=1;i<=m;i++)STmn[0][i]=STmx[0][i]=dfn[k[i]];
	for(int i=1;fsp[i]<=m;i++){
		for(int j=1;j+fsp[i]-1<=m;j++){
			STmn[i][j]=min(STmn[i-1][j],STmn[i-1][j+fsp[i-1]]);
			STmx[i][j]=max(STmx[i-1][j],STmx[i-1][j+fsp[i-1]]);
		}
	}
	for(int i=1;i<=q;i++){
		cin>>k1>>k2;
		ans[i]=-(dep[_lca(ndf[QueryMin(k1,k2)],ndf[QueryMax(k1,k2)])]-1);
		lst[k1].emplace_back(make_pair(i,k2));
	}
	modify(m+1,n);
	R.insert(mkpr(1,n,m+1));
	for(int i=m;i;i--){
		ChnModify(k[i],i);
		for(auto j:lst[i])ans[j.first]+=Query(j.second);
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<endl;
	return 0;
}
```


---

## 作者：AVENGER_M (赞：2)

## 前言

什么大炮轰蚊子算法展览会，LCT ODT 回滚莫队什么的都上了，这种板题写这些东西真的有意义吗。

做这道题的起因是模拟赛中因为类似题目活该被同学击败。于是我要写一个启发式合并的题解。

## 正文

每个询问答案是每个询问区间内节点到根的路径并、不浅于这些节点的 LCA 的点个数，因为每个节点为了抵达别的其他点，需要且仅需要这些点（必须先爬到 LCA，然后就没必要继续往上爬了）。

观察到满足前面条件、且比 LCA 还靠上的节点数量极易计算（用 RMQ+LCA 即可），这里就直接讲求满足前者的点数好了。

处理好每个节点对应的**景点**下标。

接下来我们计算一个节点 $x$ 对答案的贡献。一个**询问**区间中的点经过 $x$ 当且仅当这个区间的景点包含至少一个 $x$ 的后代。

假设我们的节点 $x$ 子树内已经加入了下标集合 $S$。我们新加入一个下标 $k$ 时，假设 $k$ 在集合中的前驱是 $L$（不存在为 $0$），后继是 $R$（不存在为 $m+1$），那么询问区间 $[l,r]$ 被加贡献，也即没跨过原先 $S$ 中的下标，但是跨过了 $k$ 当且仅当 $L<l\le k,k\le r<R$。

我们处理好所有这样的信息后即可离线扫描线。看上去这样就可以启发式合并加入后代所有下标碾平了，但是这还不够。

观察到一个节点把**重儿子**的集合 $O(1)$ 抢走后，还需要再模拟一遍上面的加下标操作。这样等于启发式合并了个寂寞。由于这里模拟的操作与重儿子进行的操作全等，我们把这里的权值推给重儿子就行了。

例如说，如果一个节点和它轻儿子子树的下标是 $\{1,4,5\}$，重儿子子树是 $\{2,7\}$，那么我们程序只用把重儿子所进行的操作多加一遍，然后 $2,7$ 直接交给父亲，最后把 $1,4,5$ 照常插入即可。具体实现看代码。

时间复杂度 $O((n+m)\log^2n+q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
int fat[100005],dep[100005],amt[100005],gson[100005],lkr[100005],flog[100005],rmq[100005][17];
int q,tr[100005],ans[100005];
vector<int>mp[100005],V[100005];
vector<pair<int,int> >W[100005],Q[100005];

set<int>s[100005];

void dfs(int x,int fa){
	fat[x]=fa;dep[x]=dep[fa]+1;amt[x]=1;
	for(auto y:mp[x]){
		if(y==fa)continue;
		dfs(y,x);amt[x]+=amt[y];
		if(amt[y]>amt[gson[x]])gson[x]=y;
	}
}

void adddsu(int x,int ky,int v){
	set<int>::iterator itr=s[x].upper_bound(ky);
	int L=0,R=m+1;
	if(itr!=s[x].end())R=*itr;if(itr!=s[x].begin())L=*--itr;
	W[L+1].push_back(make_pair(ky,v));W[L+1].push_back(make_pair(R,-v));
	W[ky+1].push_back(make_pair(ky,-v));W[ky+1].push_back(make_pair(R,v));
	s[x].insert(ky);
}

void dfsEX(int x,int fa,int cr){
	lkr[x]=cr;
	if(gson[x])dfsEX(gson[x],x,cr);
	for(auto uu:V[x])adddsu(cr,uu,dep[x]-dep[cr]+1);
	for(auto y:mp[x]){
		if(y==fa||y==gson[x])continue;
		dfsEX(y,x,y);for(auto uu:s[y])adddsu(cr,uu,dep[x]-dep[cr]+1);
	}
}

int LCA(int x,int y){
	while(1){
		if(lkr[x]==lkr[y])return dep[x]<dep[y]?x:y;
		if(dep[lkr[x]]>dep[lkr[y]])x=fat[lkr[x]];
		else y=fat[lkr[y]];
	}
}

void addbit(int x,int v){
	for(;x<=m;x+=(x&-x))tr[x]+=v;
}

int querybit(int x){
	int ca=0;for(;x;x&=(x-1))ca+=tr[x];
	return ca;
}

int main(){
	cin.tie()->sync_with_stdio(0);
	cin>>n>>m>>q;
	for(int i=2;i<=m;i++)flog[i]=flog[i>>1]+1;
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		mp[x].push_back(y);
		mp[y].push_back(x);
	}
	for(int i=1;i<=m;i++){
		int x;cin>>x;rmq[i][0]=x;
		V[x].push_back(i);
	}
	dfs(1,1);dfsEX(1,1,1);
	for(int o=1;o<17;o++)for(int i=1;i+(1<<o)-1<=m;i++){
		rmq[i][o]=LCA(rmq[i][o-1],rmq[i+(1<<o-1)][o-1]);
	}
	for(int i=1;i<=q;i++){
		int x,y,len;cin>>x>>y;len=flog[y-x+1];
		ans[i]=1-dep[LCA(rmq[x][len],rmq[y-(1<<len)+1][len])];
		Q[x].push_back(make_pair(y,i));
	}
	for(int i=1;i<=m;i++){
		for(auto uu:W[i])addbit(uu.first,uu.second);
		for(auto uu:Q[i])ans[uu.second]+=querybit(uu.first);
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

## 实现技巧/警示

1. 一个点的操作权值其实就是它在自己的重链上的深度。

2. 插入一个点时，`upper_bound` 完后不要忘了插入！！！

---

## 作者：Eznibuil (赞：1)

记录一下这种套路：回滚。

答案实际上是每个点到根的链并在一起，最后抠掉所有点的 LCA 到根的链。后者是可以用两个 ST 做到 $O(1)$ 的，不再赘述，重点看前者。

类似 HH 的项链，固定右端点，考虑这个前缀的所有链，称经过这个点的最后一个链的不是根的端点的编号为最后时间，这样就可以把所有最后时间在区间中的相加得到答案。

现在的问题是假如加入一个新的链该怎么办。显然只需要把链上所有点的最后时间都赋为新链的编号即可。这个拉到根的操作特别像 LCT 的 access，所以直接维护每种最后时间的个数，然后 access 中进行单点修改，最后查答案用区间查询，树状数组就行。

来观察一下这个和 HH 的项链的联系：固定右端点，算出每一次把左端点向左拉产生的贡献。这种题都可以看作“回滚”套路题，其特点就是右端点向右移动时修改的时间复杂度很低。

时间复杂度 $O((n+q)\log n+m(\log^2n+\log m))$。
```cpp
#include<algorithm>
#include<iostream>
#include<vector>
const int N=100001;
struct Fenwick
{
	int c[N];
	void add(int x,int d)
	{
		for(x++;x<N;x+=x&-x)
			c[x]+=d;
		return;
	}
	int pre(int x)
	{
		int r=0;
		for(;x;x^=x&-x)
			r+=c[x];
		return r;
	}
	int sum(int x,int y){return pre(y)-pre(x);}
}f;
struct LCT
{
	struct node
	{
		int col,siz;
		node*fa,*son[2];
	}e[N];
	LCT(){for(int i=0;i<N;i++)e[i].fa=e[i].son[0]=e[i].son[1]=nullptr;}
	node*get(int x){return &e[x];}
	void rotate(node*p)
	{
		if(p==nullptr||p->fa==nullptr||p->fa->son[0]!=p&&p->fa->son[1]!=p)
			return;
		node*q=p->fa;
		q->siz-=p->siz,p->siz+=q->siz,p->col=q->col;
		if(q->son[0]==p)
			q->son[0]=p->son[1],q->son[0]!=nullptr?q->son[0]->fa=q,q->siz+=q->son[0]->siz:0,p->son[1]=q;
		else
			q->son[1]=p->son[0],q->son[1]!=nullptr?q->son[1]->fa=q,q->siz+=q->son[1]->siz:0,p->son[0]=q;
		if(q->fa!=nullptr&&(q->fa->son[0]==q||q->fa->son[1]==q))
			q->fa->son[q->fa->son[0]!=q]=p;
		p->fa=q->fa,q->fa=p;
		return;
	}
	void splay(node*x)
	{
		if(x==nullptr)
			return;
		for(node*f;f=x->fa,f!=nullptr&&(f->son[0]==x||f->son[1]==x);rotate(x))
			if(f->fa!=nullptr&&(f->fa->son[0]==f||f->fa->son[1]==f))
				rotate((f->fa->son[0]!=f)==(x->fa->son[0]!=x)?f:x);
		return;
	}
	node*access(node*x,int col)
	{
		if(x==nullptr)
			return nullptr;
		splay(x);
		int s=0,y=(x->son[0]!=nullptr?x->son[0]->siz:0)+1;
		if(~x->col)
			f.add(x->col,-y);
		s+=y,x->son[1]=nullptr,x->siz=y,x->col=col;
		node*p=x;
		for(x=x->fa;x!=nullptr;p=x,x=x->fa)
		{
			splay(x),s+=y=(x->son[0]!=nullptr?x->son[0]->siz:0)+1;
			if(~x->col)
				f.add(x->col,-y);
			x->son[1]=p,x->siz=y+p->siz,x->col=col;
		}
		f.add(col,s);
		return p;
	}
}lct;
std::vector<int>G[N];
int fa[N],ti,dfn[N],eu[21][N<<2|1],c[N],mac[21][N],mic[21][N],ans[N];
std::vector<std::pair<int,int>>qu[N];
void dfs(int x,int d=0)
{
	dfn[x]=ti,eu[0][ti++]=d,lct.get(x)->col=-1,lct.get(x)->siz=1;
	for(int y:G[x])
		if(fa[x]!=y)
			fa[y]=x,lct.get(y)->fa=lct.get(x),dfs(y,d+1),eu[0][ti++]=d;
	return;
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(nullptr);
	int n,m,q;
	std::cin>>n>>m>>q;
	for(int i=1;i<n;i++)
	{
		int a,b;
		std::cin>>a>>b,G[a].emplace_back(b),G[b].emplace_back(a);
	}
	dfs(1);
	for(int i=0;i<20;i++)
		for(int j=0;j<=ti-(1<<i+1);j++)
			eu[i+1][j]=std::min(eu[i][j],eu[i][j+(1<<i)]);
	for(int i=0;i<m;i++)
		std::cin>>c[i],mic[0][i]=mac[0][i]=dfn[c[i]];
	for(int i=0;i<20;i++)
		for(int j=0;j<=m-(1<<i+1);j++)
			mic[i+1][j]=std::min(mic[i][j],mic[i][j+(1<<i)]),mac[i+1][j]=std::max(mac[i][j],mac[i][j+(1<<i)]);
	for(int i=0;i<q;i++)
	{
		int l,r;
		std::cin>>l>>r,qu[r].emplace_back(--l,i);
		int t=__builtin_log2(r-l),x=std::min(mic[t][l],mic[t][r-(1<<t)]),y=std::max(mac[t][l],mac[t][r-(1<<t)])+1;
		t=__builtin_log2(y-x),ans[i]-=std::min(eu[t][x],eu[t][y-(1<<t)]);
	}
	for(int i=0;i<=m;i++)
	{
		for(std::pair<int,int>j:qu[i])
			ans[j.second]+=f.sum(j.first,i);
		lct.access(lct.get(c[i]),i);
	}
	for(int i=0;i<q;i++)
		std::cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9340)

# 前置知识

[珂朵莉树/颜色段均摊](https://oi-wiki.org/misc/odt/) | [树状数组](https://oi-wiki.org/ds/fenwick/) | [扫描线](https://oi-wiki.org/geometry/scanning/)

# 解法

考虑对 $a_{i}$ 扫描线后柯朵莉树在链上进行区间覆盖，然后转化为查询颜色 $\in [l,r]$ 内的点的个数，可以使用树状数组维护。

当然，也可以无脑直接覆盖到根节点，然后对区间 $\operatorname{LCA}$ 的根链进行容斥，求一遍区间内 DFS 序最小和最大的两个点的 $\operatorname{LCA}$ 即可。

代码中写的是对 $(a_{i-1},a_{i})$ 这条链进行覆盖的写法。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int nxt,to;
}e[200010];
int head[200010],fa[200010],siz[200010],dep[200010],son[200010],top[200010],dfn[200010],ans[200010],a[200010],tot=0,cnt=0;
vector<pair<int,int> >q[200010];
void add(int u,int v)
{
	cnt++;  e[cnt]=(node){head[u],v};  head[u]=cnt;
}
void dfs1(int x,int father)
{
	siz[x]=1;
	fa[x]=father;
	dep[x]=dep[father]+1;
	for(int i=head[x];i!=0;i=e[i].nxt)  if(e[i].to!=father)
	{
		dfs1(e[i].to,x);
		siz[x]+=siz[e[i].to];
		son[x]=(siz[e[i].to]>siz[son[x]])?e[i].to:son[x];
	}
}
void dfs2(int x,int id)
{
	top[x]=id;
	tot++;  dfn[x]=tot;
	if(son[x]!=0)
	{
		dfs2(son[x],id);
		for(int i=head[x];i!=0;i=e[i].nxt)  
		{
			if(e[i].to!=fa[x]&&e[i].to!=son[x])  dfs2(e[i].to,e[i].to);
		}	
	}
}
struct BIT
{
	int c[200010];
	int lowbit(int x)
	{
		return (x&(-x));
	}
	void add(int n,int x,int val)
	{
		if(x==0)  return;
		for(int i=x;i<=n;i+=lowbit(i))  c[i]+=val;
	}
	int getsum(int x)
	{
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))  ans+=c[i];
		return ans;
	}
}T;
struct ODT
{
	struct node
	{
		int l,r;
		mutable int col;
		bool operator < (const node &another) const
		{
			return l<another.l;
		}
	};
	set<node>s;
	void init(int n)
	{
		s.insert((node){1,n,0});
	}
	set<node>::iterator split(int pos)
	{
		set<node>::iterator it=s.lower_bound((node){pos,0,0});
		if(it!=s.end()&&it->l==pos)  return it;
		it--;
		if(it->r<pos)  return s.end();
		int l=it->l,r=it->r,col=it->col;
		s.erase(it);
		s.insert((node){l,pos-1,col});
		return s.insert((node){pos,r,col}).first;
	}
	void assign(int l,int r,int col,int n)
	{
		set<node>::iterator itr=split(r+1),itl=split(l);
		for(set<node>::iterator it=itl;it!=itr;it++)  T.add(n,it->col,-(it->r-it->l+1));
		T.add(n,col,r-l+1);
		s.erase(itl,itr);
		s.insert((node){l,r,col});
	}
}O;
void update(int u,int v,int col,int n)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
		{
			O.assign(dfn[top[u]],dfn[u],col,n);
			u=fa[top[u]];
		}
		else
		{
			O.assign(dfn[top[v]],dfn[v],col,n);
			v=fa[top[v]];
		}
	}
	if(dep[u]<dep[v])  O.assign(dfn[u],dfn[v],col,n);
	else  O.assign(dfn[v],dfn[u],col,n);
}
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,m,k,u,v,i,j;
	cin>>n>>m>>k;
	for(i=1;i<=n-1;i++)
	{
		cin>>u>>v;
		add(u,v);  add(v,u);
	}
	for(i=1;i<=m;i++)  cin>>a[i];
	for(i=1;i<=k;i++)
	{
		cin>>u>>v;
		if(u==v)  ans[i]=1;
		else  q[v].push_back(make_pair(u,i));
	}
	dfs1(1,0);  dfs2(1,1);  O.init(n);
	for(i=2;i<=m;i++)
	{
		update(a[i-1],a[i],i,m);
		for(j=0;j<q[i].size();j++)  ans[q[i][j].second]=T.getsum(i)-T.getsum(q[i][j].first);
	}
	for(i=1;i<=k;i++)   cout<<ans[i]<<endl;
	return 0;
}
```

---

