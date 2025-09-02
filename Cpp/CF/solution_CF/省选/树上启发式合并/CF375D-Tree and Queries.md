# Tree and Queries

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Each vertex of the tree has some color. We will assume that the tree vertices are numbered by integers from 1 to $ n $ . Then we represent the color of vertex $ v $ as $ c_{v} $ . The tree root is a vertex with number 1.

In this problem you need to answer to $ m $ queries. Each query is described by two integers $ v_{j},k_{j} $ . The answer to query $ v_{j},k_{j} $ is the number of such colors of vertices $ x $ , that the subtree of vertex $ v_{j} $ contains at least $ k_{j} $ vertices of color $ x $ .

You can find the definition of a rooted tree by the following link: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 说明/提示

A subtree of vertex $ v $ in a rooted tree with root $ r $ is a set of vertices $ {u :dist(r,v)+dist(v,u)=dist(r,u)} $ . Where $ dist(x,y) $ is the length (in edges) of the shortest path between vertices $ x $ and $ y $ .

## 样例 #1

### 输入

```
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3
```

### 输出

```
2
2
1
0
1
```

## 样例 #2

### 输入

```
4 1
1 2 3 4
1 2
2 3
3 4
1 1
```

### 输出

```
4
```

# 题解

## 作者：dreagonm (赞：36)

这道题dsu on tree其实可以不用像楼上说的再套上一个线段树或者树状数组的

#### 思路

dsu on tree的板子，可惜人傻把

```cpp
for(int i=fir[u];i;i=nxt[i])
```

打成

```cpp
for(int i=fir[u];i<=n;i++)
```

调了两个小时2333

#### 简单且暴力的思路

这题要求维护>=k的颜色数量

所以和模板类似的考虑什么情况下会对答案产生贡献

显然是>=k的点数会产生贡献，所以用VAL记录每个颜色的出现次数，然后额外开一个d[k]数组表示>=k的颜色数量

然后就可以优雅的跑过去了

#### 厚颜无耻的广告

欢迎来我的博客转一转啊

[cnblogs](http://www.cnblogs.com/dreagonm)

[hexo博客](https://dreagonm.github.io/)

#### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int sz[100100],val[100100],heason[100100],u[100100<<1],v[100100<<1],w_p[100100],fir[100100],nxt[100100<<1],d[100100],vis[100100],cnt,n,m,ans[100100];
struct query{
    int num,ansid;
};
vector<query> Q[100100];
void addedge(int ui,int vi){
    ++cnt;
    u[cnt]=ui;
    v[cnt]=vi;
    nxt[cnt]=fir[ui];
    fir[ui]=cnt;
}
void dfs1(int u,int f){
    sz[u]=1;
    for(int i=fir[u];i;i=nxt[i]){
        if(v[i]==f)
            continue;
        dfs1(v[i],u);
        sz[u]+=sz[v[i]];
        if(heason[u]==0||sz[heason[u]]<sz[v[i]])
            heason[u]=v[i];
    }
}
void solve(int u,int f,int c){
    if(c==-1)
        d[val[w_p[u]]]+=c;
    val[w_p[u]]+=c;
    if(c==1)
        d[val[w_p[u]]]+=c;
    for(int i=fir[u];i;i=nxt[i]){
        if(v[i]==f||vis[v[i]])
            continue;
        solve(v[i],u,c);
    }
}
void dfs2(int u,int f,int islight){
    for(int i=fir[u];i;i=nxt[i]){
        if(v[i]==f||v[i]==heason[u])
            continue;
        dfs2(v[i],u,1);
    }
    if(heason[u])
        dfs2(heason[u],u,0),vis[heason[u]]=true;
    solve(u,f,1);
    for(int i=0;i<Q[u].size();i++)
        ans[Q[u][i].ansid]=d[Q[u][i].num];
    if(heason[u])
        vis[heason[u]]=false;
    if(islight)
        solve(u,f,-1);
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&w_p[i]);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    for(int i=1;i<=m;i++){
        query x;
        int u;
        scanf("%d %d",&u,&x.num);
        x.ansid=i;
        Q[u].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0,1);
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：little_sun (赞：27)

首先，子树上的查询问题可以通过$DFS$序转为序列问题

再一看，没有修改，可以离线，这不就是莫队吗？

我们用$sum_i$表示出现次数$\geq i$的个数

用$val_i$表示第$i$种颜色的出现次数

那么每次修改时只要$O(1)$修改$sum$和$val$即可

详见代码

```cpp
#include <bits/stdc++.h>
const int MaxN = 100010;
struct node
{
    int val, dfn, r, id;
};
struct query
{
    int l, r;
    int pos, id, k;
};
struct edge
{
    int next, to;
};
node a[MaxN];
query q[MaxN];
edge e[MaxN << 1];
int n, m, cnt, dfscnt, size;
int head[MaxN], ans[MaxN], sum[MaxN], val[MaxN];
inline int comp(node a, node b) { return a.dfn < b.dfn; }
inline int cmp(query a, query b)
{
    if (a.pos != b.pos)
        return a.pos < b.pos;
    return a.r < b.r;
}
inline void add_edge(int u, int v)
{
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
inline void dfs(int u)
{
    a[u].dfn = ++dfscnt;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (!a[v].dfn)
            dfs(v);
    }
    a[u].r = dfscnt;
}
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
inline void add(int x) { ++val[a[x].val], ++sum[val[a[x].val]]; }
inline void del(int x) { --sum[val[a[x].val]], --val[a[x].val]; }
inline void solve()
{
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++)
    {
        while (l > q[i].l)
            --l, add(l);
        while (r < q[i].r)
            ++r, add(r);
        while (l < q[i].l)
            del(l), ++l;
        while (r > q[i].r)
            del(r), --r;
        ans[q[i].id] = sum[q[i].k];
    }
}
int main()
{
    n = read(), m = read();
    size = pow(n, 0.55);
    for (int i = 1; i <= n; i++)
        a[i].val = read(), a[i].id = i;
    for (int i = 1; i <= n - 1; i++)
    {
        int u = read(), v = read();
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1);
    for (int i = 1; i <= m; i++)
    {
        int v, k;
        v = read(), k = read();
        q[i].l = a[v].dfn, q[i].r = a[v].r, q[i].k = k;
        q[i].id = i, q[i].pos = (q[i].l - 1) / size + 1;
    }
    std::sort(q, q + m + 1, cmp);
    std::sort(a + 1, a + n + 1, comp);
    solve();
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：chenxinyang2006 (赞：11)

题解里貌似写的都是 DSU on tree 或者莫队的做法，这里介绍一个线段树合并，时间复杂度为 $O(n \log n + m \log n)$ 的做法

对于 $u$ 节点的子树，维护两颗线段树 $T1_u,T2_u$，$T1_u$ 下标 $i$ 对应的值表示颜色为 $i$ 的点在子树 $u$ 内的个数，$T2_u$ 下标 $i$ 对应的值表示有多少颜色出现次数为 $i$

现在考虑如何从 $u$ 的子节点 $v_1,v_2...v_k$ 转移到 $u$

$T1_u$ 的值实际上就是将所有 $T1_{v_1},T1_{v_2}...T1_{v_k}$ 进行线段树合并后，再在 $c_u$ 的位置加上 $1$

$T2_u$ 似乎比较棘手了

对于一种颜色 $col$，我们可以进行两类分类

- 在子树 $u$ 中，颜色为 $col$ 的点都属于 $u$ 的一个儿子 $v$ 的子树

  对于这类情况，在子树 $u$ 中 $col$ 的出现次数与在子树 $v$ 中是相同的，对于这类情况，实际上我们可以对于 $T2$ 也进行线段树合并
  
- 在子树 $u$ 中，颜色为 $col$ 的点属于 $u$ 的多个儿子 $v_1,v_2..v_k$ 的子树

  对于这类情况，我们就只能暴力修改 $T2$ 了
  
那么实际上现在的问题就是如何快速找出哪些颜色是情况一，哪些颜色是情况二

实际上我们可以在 $T1$ 进行线段树合并时，找到所有被合并的叶子节点并记录它们对应的颜色，这样就找出了所有的情况二

由线段树合并的复杂度分析我们可以知道，情况二最多只会出现 $O(n)$ 次，所以暴力修改的复杂度是对的

那么该如何只对所有情况一的颜色进行线段树合并呢？

答案是把所有情况都装作是情况一，然后对于情况二的颜色，删去各个子树 $v$ 内颜色的出现次数，加入子树 $u$ 内颜色的出现次数

这里可能有一点细节问题，就是如何求出所有含有这种颜色的子树 $v$ 内的出现次数

也是在线段树合并到叶节点时特判一下，放到一个 `vector` 里

但是这些部分我们都没有讨论 $u$ 节点的颜色该如何处理

其实也比较简单，只要把 $u$ 节点的颜色当作是它自己一个特殊的子节点的颜色就行了

对于查询，其实就是在 $T2$ 上进行一下区间求和，如果追求在线算法的话可以选择可持久化线段树合并，但是我懒得写了，就写了离线算法

code：

```cpp
#include <cstdio>
#include <vector>
using namespace std;
int n,m;
int a[100005];

int cnt;
int head[100005];
struct eg{
	int to,nxt;
}edge[200005];

void make(int u,int v){
	edge[++cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

int T1[100005],T2[100005];
struct node{
	int val,l,r;
}tree[5000005];

int tag[100005];

#define ls(x) tree[x].l
#define rs(x) tree[x].r

void fx(int &x){
    if(x == 0){
     	x = ++cnt;
     	tree[x].val = ls(x) = rs(x) = 0;
    }
}

vector <int> S,T;

void upload(int rt,int l,int r,int id,int C){
	tree[rt].val += C;
	if(l == r) return;
	int mid = l + r >> 1;
	if(id <= mid){
		fx(ls(rt));
		upload(ls(rt),l,mid,id,C);
	}else{
		fx(rs(rt));
		upload(rs(rt),mid+1,r,id,C);
	}
}

int query(int rt,int l,int r,int L,int R){
	if(!rt) return 0;
	if(l == L && r == R) return tree[rt].val;
	int mid = l + r >> 1;
	if(R <= mid) return query(ls(rt),l,mid,L,R);
	else if(L > mid) return query(rs(rt),mid+1,r,L,R);
	else return query(ls(rt),l,mid,L,mid) + query(rs(rt),mid+1,r,mid+1,R);
}

int Merge(int x,int y,int l,int r){
	if(!x || !y) return x + y;
	if(l == r){
		if(!tag[l] && tree[x].val > 0){
			tag[l] = 1;
			S.push_back(l);
			T.push_back(tree[x].val);
		}
		if(tree[y].val > 0) T.push_back(tree[y].val);
	}
	tree[x].val += tree[y].val;
	int mid = l + r >> 1;
	ls(x) = Merge(ls(x),ls(y),l,mid);
	rs(x) = Merge(rs(x),rs(y),mid+1,r);
	return x;
}

int res[100005];
struct ask{
	int k,id;
};
vector <ask> Q[100005];

void dfs(int now,int fa){
	for(int i = head[now];i;i = edge[i].nxt){
		if(edge[i].to == fa) continue;
		dfs(edge[i].to,now);	
	}
	S.clear();
	T.clear();
	fx(T1[now]);
	upload(T1[now],1,100000,a[now],1);
	for(int i = head[now];i;i = edge[i].nxt){
		if(edge[i].to == fa) continue;
		T1[now] = Merge(T1[now],T1[edge[i].to],1,100000);	
	}
	fx(T2[now]);
	upload(T2[now],1,100000,1,1);
	for(int i = 0;i < T.size();i++) upload(T2[now],1,100000,T[i],-1);
	for(int i = 0;i < S.size();i++) upload(T2[now],1,100000,query(T1[now],1,100000,S[i],S[i]),1);
	for(int i = head[now];i;i = edge[i].nxt){
		if(edge[i].to == fa) continue;
		T2[now] = Merge(T2[now],T2[edge[i].to],1,100000);	
	}
	for(int i = 0;i < S.size();i++) tag[S[i]] = 0;
	for(int i = 0;i < Q[now].size();i++) res[Q[now][i].id] = query(T2[now],1,100000,Q[now][i].k,100000);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for(int i = 1;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		make(u,v);make(v,u);
	}
	for(int i = 1;i <= m;i++){
		int u,k;
		scanf("%d%d",&u,&k);
		Q[u].push_back({k,i});
	}
	cnt = 0;
	dfs(1,0);
	for(int i = 1;i <= m;i++) printf("%d\n",res[i]);
	return 0;
}
```


---

## 作者：EternalEpic (赞：9)

目前最优解，没开O2和fread。

可以想到用DSU on tree解决，但实际上不需要用其他数据结构来维护，只需要一个桶，所以我的复杂度是：$O(nlog_2n)$ 的。

联想到莫队的“数颜色”，我们可以用 $col[x]$ 表示这个颜色出现了几次，用 $sum[x]$ 表示有多少颜色数量大于等于 $ｘ$ 。

于是我们就有了如下，像莫队移指针一样的修改函数：

```cpp
inline void add(int u) { col[c[u]]++; sum[col[c[u]]]++; }
inline void del(int u) { sum[col[c[u]]]--; col[c[u]]--; }
```

随后就是常规两个操作：

1. 找重儿子，划分子树。

2. 寻找答案，进行启发式合并。

我的写法是离线的，把询问记录在 $vector$ 中。

code:

```cpp
// Program written by Liu Zhaozhou ~~~
#include <bits/stdc++.h>

using namespace std;

inline char gc(void) {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

#define gc() getchar()

template <class T> inline void read(T &x) {
	T f = 1; x = 0; static char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
	x *= f;
}

inline void readstr(char *s) {
	do *s = gc(); while ((*s == ' ') || (*s == '\n') || (*s == '\r'));
	do *(++s) = gc(); while ((~*s) && (*s != ' ') && (*s != '\n') && (*s != '\r'));
	*s = 0; return;
}

inline void readch(char&x) { while (isspace(x = gc())); }

char pf[100000], *o1 = pf, *o2 = pf + 100000;
#define ot(x) (o1 == o2 ? fwrite(pf, 1, 100000, stdout), *(o1 = pf) ++= x : *o1 ++= x)
template <class T>
inline void println(T x, char c = '\n') {
	if (x < 0) ot(45), x = -x;
	static char s[15], *b; b = s;
	if (!x) *b ++= 48;
	for (; x; * b ++= x % 10 + 48, x /= 10);
	for (; b-- != s; ot(*b)); ot(c);
}

template <class T> inline void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

template <class T> inline void writeln(T x, char c = '\n') { write(x); putchar(c); }
template <class T> inline void chkmax(T &x, const T y) { x > y ? x = x : x = y; }
template <class T> inline void chkmin(T &x, const T y) { x < y ? x = x : x = y; }

inline void file(string str) {
	freopen((str + ".in").c_str(), "r", stdin);
	freopen((str + ".out").c_str(), "w", stdout);
}

#define Ms(arr, opt) memset(arr, opt, sizeof(arr))
#define Mp(x, y) make_pair(x, y)

typedef long long ll;
typedef pair <int, int> pii;

const int Maxn = 1e5 + 5, Maxm = 2e5 + 5;
int n, m, cnt, c[Maxn], head[Maxn], ver[Maxm], nxt[Maxm];
inline void AddEdge(int u, int v) {
	ver[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt;
	ver[++cnt] = u, nxt[cnt] = head[v], head[v] = cnt;
}

int fat[Maxn], sze[Maxn], son[Maxn];
int L[Maxn], R[Maxn], rev[Maxn], tot;
inline void DfsFir(int u) {
	sze[u] = 1; L[u] = ++tot; rev[tot] = u;
	for (int i = head[u]; i; i = nxt[i]) {
		if (ver[i] == fat[u]) continue;
		fat[ver[i]] = u; DfsFir(ver[i]);
		sze[u] += sze[ver[i]];
		if (sze[son[u]] < sze[ver[i]]) son[u] = ver[i];
	} R[u] = tot;
}

vector <pii> vec[Maxn]; 
int col[Maxn], sum[Maxn], ans[Maxn];

inline void add(int u) { col[c[u]]++; sum[col[c[u]]]++; }
inline void del(int u) { sum[col[c[u]]]--; col[c[u]]--; }

inline void DfsSec(int u, bool iss) {
	for (int i = head[u]; i; i = nxt[i]) {
		if (ver[i] == fat[u] || ver[i] == son[u]) continue;
		DfsSec(ver[i], false);
	} if (son[u]) DfsSec(son[u], true); add(u);
	
	for (int i = head[u]; i; i = nxt[i]) {
		if (ver[i] == fat[u] || ver[i] == son[u]) continue;
		for (int j = L[ver[i]]; j <= R[ver[i]]; j++) {
			int x = rev[j]; add(x);
		}
	}
	
	for (int i = 0; i < (int) vec[u].size(); i++) {
		int idx = vec[u][i].first, k = vec[u][i].second;
		ans[idx] = sum[k];
	}
	
	if (!iss) for (int i = L[u]; i <= R[u]; i++) del(rev[i]);
}

signed main(void) {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(c[i]);
	for (int i = 1, u, v; i < n; i++)
		read(u), read(v), AddEdge(u, v);
	for (int i = 1, u, k; i <= m; i++)
		read(u), read(k), vec[u].push_back(Mp(i, k));
	DfsFir(1); DfsSec(1, true);
	for (int i = 1; i <= m; i++) writeln(ans[i]);
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}

/**/

```


---

## 作者：Farkas_W (赞：7)

$$\text{CF375D Tree and Queries}$$

$\quad$题目链接：[CF375D Tree and Queries](https://www.luogu.com.cn/problem/CF375D)(洛谷的链接)

### 思路

$\quad$标准做法是动态规划，但看到 $4.5s$ 的时限，似乎可以树上启发式合并水过去，只要用 $num_i$ 和 $cnt_k$ 的数组来记录出现颜色 $i$ 的数量及超过 $k$ 的颜色数量即可。

$\quad$下面就简单讲讲树上启发式合并 (Dsu on Tree)算法，如果有不懂的可以提出来，如果已经学过了的可以直接看最后的完整代码。

$$\text{前置知识}$$

$\quad$学这个之前需要对树上操作、 $dfs$ 序和轻重链剖分等知识有一定了解，最好已经掌握了树链剖分。

$$\text{算法思想}$$

$\quad$树上启发式合并 (Dsu on Tree)，是一个在 $O(n\log n)$ 时间内解决许多树上问题的有力算法，对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现。

$\quad$先想一下暴力算法，对于每一次询问都遍历整棵子树，然后统计答案，最后再清空 $cnt$ 数组，最坏情况是时间复杂度为 $O(n^2)$ ，对于 $10^5$ 的数据肯定是过不去的。

$\quad$现在考虑优化算法，暴力算法跑得慢的原因就是多次遍历，多次清空数组，一个显然的优化就是将询问同一个子树的询问放在一起处理，但这样还是没有处理到关键，最坏情况时间复杂度还是 $O(n^2)$，考虑到询问 $x$ 节点时，$x$ 的子树对答案有贡献，所以可以不用清空数组，先统计 $x$ 的子树中的答案，再统计 $x$ 的答案，这样就需要提前处理好 $dfs$ 序。

$\quad$然后我们可以考虑一个优化，遍历到最后一个子树时是不用清空的，因为它不会产生对其他节点影响了，根据贪心的思想我们当然要把节点数最多的子树（即重儿子形成的子树）放在最后，之后我们就有了一个看似比较快的算法，先遍历所有的轻儿子节点形成的子树，统计答案但是不保留数据，然后遍历重儿子，统计答案并且保留数据，最后再遍历轻儿子以及父节点，合并重儿子统计过的答案。

$\quad$关键代码
```cpp
il void add(int x){num[col[x]]++;cnt[num[col[x]]]++;}//单点增加贡献
il void raise(int x)//增加x的子树的贡献
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    add(rev[i]);
}
il void clear(int x)//清空子树
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    {
      int y=rev[i];
      cnt[num[col[y]]]--;num[col[y]]--;
    }
}
il void dfs1(int x,int fa)//预处理
{
  size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;father[x]=fa;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  for(re i=0;i<q[x].size();i++)//更新答案
    ans[q[x][i].id]=cnt[q[x][i].k];
  if(!flag)clear(x);//如果是轻儿子，就清空
}
```
$\quad$完整 $AC$ 代码，建议自己写出来。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,m,next[N<<1],go[N<<1],head[N],tot,seg[N],col[N];
int rev[N],size[N],son[N],father[N],cnt[N],ans[N],num[N];
struct node{int k,id;};
vector<node>q[N];
il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;go[tot]=y;
}
il void add(int x){num[col[x]]++;cnt[num[col[x]]]++;}
il void raise(int x)
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    add(rev[i]);
}
il void clear(int x)
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    {
      int y=rev[i];
      cnt[num[col[y]]]--;num[col[y]]--;
    }
}
il void dfs1(int x,int fa)
{
  size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;father[x]=fa;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==father[x]||y==son[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  for(re i=0;i<q[x].size();i++)//更新答案
    ans[q[x][i].id]=cnt[q[x][i].k];
  if(!flag)clear(x);//如果是轻儿子，就清空
}
signed main()
{
  n=read();m=read();
  for(re i=1;i<=n;i++)col[i]=read();
  for(re i=1,x,y;i<n;i++)x=read(),y=read(),Add(x,y),Add(y,x);
  for(re i=1,x,y;i<=m;i++)x=read(),y=read(),q[x].push_back((node){y,i});
  dfs1(1,0);dfs2(1,1);
  for(re i=1;i<=m;i++)print(ans[i]),putchar('\n');
  return 0;
}
```

---

## 作者：SIXIANG32 (赞：5)

第一个紫题题解，有点小激动 qwq  
~~刚好暴露出我的菜，害~~  
闲话少说，切入正题。  

---
看着 $n\le m\le 10^5$ 这样友好的数据范围，看着数颜色，看着没有修改的凉心操作，显然是用莫队嘛~  
但是这是在树上鸭，莫队是维护序列的，那该怎么办？~~用莫队维护树剖？~~  

首先我们要关注到一点，我们要求的是 **$u$ 的子树**的颜色。  
学过 dfs 的同学们都知道，dfs 序中**每个子树的序列必然连续**，这个是 dfs 的一大显著特点，因为它优先搜索子树。如果不理解的话可以画个图手动模拟一下 dfs 的过程。~~但是我懒所以我不想画图~~  
那么也就是说，我们可以根据 dfs 序，把一棵树的颜色映射到一个序列上！  
具体怎么做呢？我们把 $u$ 的子树转化成一个区间。左端点则是 $u$ 的 dfs 序，右端点则是遍历完 $u$ 的子树后的编号。

---
然后我们应该求解答案了。  
莫队嘛，考虑新增和删除的操作。我们以 $awa_i$ 作为 $i$ 这个颜色出现数量，$ovo_i$ 为出现次数 $\ge i$ 的颜色数。  
然后新增就是 $awa_{nc_v} +1,ovo_{awa_{nc_v}}+1$  
删除就是 $ovo_{awa_{nc_v}}-1,awa_{nc_v}-1$  
我们会很惊奇的发现新增和删除的顺序是反着的，这是因为删除的时候，失去的不是 $awa_{nc_v}-1$ 这个颜色数，而是 $awa_{nc_v}$，这应该也是有些人 WAon4 的原因。  

---
然后剩下的就是莫队板子了。~~如果你不会莫队你为什么要做这道题~~，上代码！

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath> 
using namespace std;
vector<int>gra[100010];
int dfn[100010],C,cl[100010];
int nc[100010],ans[100010];
int awa[100010],ovo[100010];
int l[100010],r[100010];
struct node{//查询
	int l,r,cl,ind,k;
}in[100010];
void dfs(int u,int fa)//dfs 一遍，树转化成序列
{
	l[u]=++C,nc[C]=cl[u];//l 是 u 的左端点，nc 是树上的颜色转化成序列后的颜色
	for(int p=0;p<gra[u].size();p++)
	{
		int v=gra[u][p];
		if(v!=fa)
			dfs(v,u);
	}
	r[u]=C;//r 是 u 的右端点
}
bool cmp(node &x,node &y)//排序，是奇偶块排序
{
	return ((x.cl!=y.cl)?(x.l<y.l):((x.cl&1)?(x.r<y.r):(x.r>y.r)));
}
void add(int v){++awa[nc[v]],++ovo[awa[nc[v]]];}//莫队新增
void del(int v){--ovo[awa[nc[v]]],--awa[nc[v]];}//莫队删除
int main()
{
	int n,m;
	cin>>n>>m;
	int len=sqrt(n);//块长
	for(int p=1;p<=n;p++)
		cin>>cl[p];
	for(int p=1,x,y;p<n;p++)
		cin>>x>>y,gra[x].push_back(y),gra[y].push_back(x);
	dfs(1,0);
	for(int p=1,qwq;p<=m;p++)
		cin>>qwq>>in[p].k,in[p].l=l[qwq],in[p].r=r[qwq],in[p].ind=p,in[p].cl=(l[qwq]-1)/len+1;
	sort(in+1,in+m+1,cmp);
	int l=1,r=0;
	for(int p=1;p<=m;p++)//莫队板子
	{
		while(l<in[p].l)del(l++);
		while(l>in[p].l)add(--l);
		while(r<in[p].r)add(++r);
		while(r>in[p].r)del(r--); 
		ans[in[p].ind]=ovo[in[p].k];
	}
	for(int p=1;p<=m;p++)
		cout<<ans[p]<<endl;
}
```

---

## 作者：_RainCappuccino_ (赞：4)

> $\mathtt{TAGS}$：根号分治，树上启发式合并，离线

首先，我们发现同一个点的查询只需知道子树中每种颜色的数量就能一起得到答案，所以我们不妨将询问离线，一起考虑。

设 $res_{u, col}$ 表示 $u$ 子树下每种颜色的数量，显然 $res_{u, col} = \sum res_{v, col}$，这个东西进行启发式合并可以做到 $\text{O}(n \log^{2} n)$ 实现。

由于是次数统计，我们不妨考虑根号分治。

对于出现次数 $\le \sqrt{n}$ 的颜色，维护 $cnt_{u, t}$ 表示 $u$ 子树中出现 $t$ 次的颜色数量。在合并过程中，该值也可以维护出来，维护复杂度 $\text{O}(n\log n)$。统计答案时，只需统计出现 $k \sim \sqrt{n}$ 次的点的数量即可，时间复杂度至多 $\text{O}(\sqrt{n})$。

对于出现次数 $> \sqrt{n}$ 的颜色，这样的颜色最多有 $\sqrt{n}$ 种，于是将所有这样的颜色存储进一个 set 中，统计答案时至多将所有这样的颜色扫一遍，时间复杂度 $\text{O}(\log n\times \sqrt{n})$。

最终答案即为两部分的和。

时间复杂度为 $\text{O}(n\log^2 n + n \sqrt{n})$。

PS：此题作者试了很多种方法，很多都因为 $10^5 \times 317$ 的空间爆炸，这种方法是目前唯一通过的方法，如果您有更好的实现方法，欢迎与我探讨。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
const int M = 317 + 1;
int n, m, b;
int c[N], ct[N], tot;
vector<int> g[N];
int a[N];
vector<int > q[N], pp[N];
set<int> p[N];
int ans[N], cnt[N][M];
 
map<int, int>  dfs (int u, int fa) {
	map<int, int> res;
	res[c[u]] ++;
	if(res[c[u]] <= b) cnt[u][res[c[u]]] ++;
	else p[u].insert(c[u]);
	for (auto v : g[u]) {
		if(v == fa)  continue;
		map<int, int> res2 = dfs(v, u);
		if(res.size() < res2.size()) swap(res, res2), swap(cnt[u], cnt[v]), swap(p[u], p[v]);
		for (auto x : res2) {
			if(res[x.first] <= b) cnt[u][res[x.first]] --;
			res[x.first] += x.second;
			if(res[x.first] <= b) cnt[u][res[x.first]] ++;
			else p[u].insert(x.first);
		}
		res2.clear();
	}
	for (auto x : q[u]) {
		int k = a[x], id = x, xx = 0;
		if(k <= b) for (int i = k; i <= b; i ++) xx += cnt[u][i];
		for (auto y : p[u]) xx += (res[y] >= k);
		ans[id] = xx;
	}
	return res;
}
 
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	b = sqrt(n);
	for (int i = 1; i <= n; i ++) cin >> c[i], ct[c[i]] ++;
	for (int i = 1; i < n; i ++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v), g[v].push_back(u);
	}
	for (int i = 1, u; i <= m; i ++) {
		cin >> u >> a[i];
		q[u].push_back(i);
	}
	dfs(1, 0);
	for (int i = 1; i <= m; i ++) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：moosssi (赞：3)

这道题是道树上莫队模板题

首先考虑把树转化为欧拉序，这样就把书上问题转化为了区间问题，然后直接套莫队。

对于答案的处理，我用了两个数组$cnt[i]$,表示区间里i这个数出现了多少次，的$dcnt[i]$表示出现次数 $≥i $的颜色有多少种,答案直接从后者中取得。


这里还要想一下每个询问的左右端点，对于节点$i$，$i$在欧拉序里第一次出现的位置到最后一次出现的位置之间的数,就是它所有的子树节点，（可以自己举例），这样左右端点就是$first[i]$和$last[i]$。

注意每个节点要在欧拉序里出现两次，那么对于问题询问的$k$次就要变为$2*k$次，还要注意每个数组都尽量开够.


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int head[N],ver[N],net[N],tot; 
int n,m,len,dt[N],w[N],cnt[N],dcnt[N],ans[N];
int seq[N],top,first[N],last[N];
struct nod{
	int id,l,r,k;
}q[N];
void add_edge(int a,int b){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
}
bool cmp(nod x,nod y){
	int i=dt[x.l],j=dt[y.l];
	if(i!=j)return i<j;
	return x.r<y.r;
}
void dfs(int x,int fa){//预处理欧拉序 
	seq[++top]=x;
	first[x]=top;
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs(v,x);
	}	
	seq[++top]=x;
	last[x]=top;
}
void add(int x){//维护序列 
	cnt[w[x]]++; 
	dcnt[cnt[w[x]]]++;
}
void del(int x){
	dcnt[cnt[w[x]]]--;
	cnt[w[x]]--;
}
int main(){
	scanf("%d%d",&n,&m);
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=top;i++){
		dt[i]=(i-1)/len+1;
	}
	for(int i=1;i<=m;i++){
		int u,k;
		scanf("%d%d",&u,&k);
		q[i].l=first[u],q[i].r=last[u];//处理左右端点 
		q[i].id=i,q[i].k=k;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){//莫队模板 
		int k=q[i].k;
		while(l>q[i].l)add(seq[--l]);
		while(l<q[i].l)del(seq[l++]);
		while(r>q[i].r)del(seq[r--]);
		while(r<q[i].r)add(seq[++r]);
		ans[q[i].id]=dcnt[k*2];//注意是k*2 
	}
	for(int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：Rorschachindark (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF375D)
# 题目大意
给出一个树，每个点有颜色，有 $m$ 次查询，每次查询以 $u$ 为根的子树内出现次数 $\ge k$ 的颜色有多少个。

$n,m\le 10^5$
# 思路
作为截止至 2020-09-07 的最优解，这里发一篇题解记录一下。

其实不是很难，就是一个 $\text{dsu on tree}$ 的板子，具体操作的时候需要自己想一下，然后你发现你其实可以记录当前子树内出现次数 $\ge k$ 的颜色个数，这个见代码。然后就是板子了。

不知道为什么自己这么短还这么快。。。
# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 100005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

struct node{int k,ind;};
vector <node> que[MAXN];
int n,m,rt,ind,toop = 1,tot[MAXN],dfn[MAXN],tur[MAXN],col[MAXN],siz[MAXN],son[MAXN],res[MAXN],ans[MAXN],to[MAXN << 1],nxt[MAXN << 1],head[MAXN];

void Add_Edge(int u,int v){
	to[++ toop] = v,nxt[toop] = head[u],head[u] = toop;
	to[++ toop] = u,nxt[toop] = head[v],head[v] = toop;
}

void dfs1 (int u,int fa){
	siz[u] = 1,dfn[u] = ++ ind,tur[ind] = u;
	for (Int i = head[u];i;i = nxt[i]){
		int v = to[i];
		if (v == fa) continue;
		dfs1 (v,u),siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

void Add (int u){++ res[++ tot[col[u]]];}

void dfs2 (int u,int fa,int k){
	for (Int i = head[u];i;i = nxt[i]){
		int v = to[i];
		if (v == fa || v == son[u]) continue;
		dfs2 (v,u,0);
	}
	if (son[u]) dfs2 (son[u],u,1);
	Add (u);
	for (Int i = head[u];i;i = nxt[i]){
		int v = to[i];
		if (v == fa || v == son[u]) continue;
		for (Int j = dfn[v];j <= dfn[v] + siz[v] - 1;++ j) Add (tur[j]); 
	}
	for (node q : que[u]) ans[q.ind] = res[q.k];
	if (!k){
		for (Int i = 1;i <= siz[u];++ i) res[i] = 0;
		for (Int i = dfn[u];i <= dfn[u] + siz[u] - 1;++ i) tot[col[tur[i]]] = 0;
	}
}

signed main(){
	read (n,m);
	for (Int i = 1;i <= n;++ i) read (col[i]);
	for (Int i = 2,u,v;i <= n;++ i) read (u,v),Add_Edge (u,v);
	for (Int i = 1,u,k;i <= m;++ i) read (u,k),que[u].push_back (node {k,i});
	dfs1 (1,0),dfs2 (1,0,1);
	for (Int i = 1;i <= m;++ i) write (ans[i]),putchar ('\n');
	return 0;
}
```

---

## 作者：Graphcity (赞：2)

首先是 TLE 解法。

### **TLE 解法**

这是一个离线算法。

我们可以用 `vector` 这个东西存储所有的询问。

我们设当前颜色 $x$ 的个数为 $cnt(x)$ 。另外，还可以假设有 $sum(x)$ 种颜色出现次数超过了 $x$ 。

当 $cnt(x)$ 增加 1 时，$sum(cnt(x)+1)$ 也会增加 1 。

处理结点 $x$ 子树内的所有询问可以用一次 `dfs` 来解决。

```cpp
#include<bits/stdc++.h>
#include<vector>
#define Maxn int(1e5)
using namespace std;
typedef pair<int,int> Pair;

struct Node
{
	int to,nxt;
} Edge[(Maxn<<1)+5];
int tot,Head[Maxn+5];

inline void Addedge(int x,int y)
{
	Edge[++tot].to=y;
	Edge[tot].nxt=Head[x];
	Head[x]=tot;
}

vector<Pair> q[Maxn+5];//用于存储询问 
int n,m,col[Maxn+5],ans[Maxn+5],fa[Maxn+5];
int cnt[Maxn+5],sum[Maxn+5];

inline void predfs(int x,int f)//先用一次dfs求出结点的父亲 
{
	fa[x]=f;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==f) continue;
		predfs(y,x);
	}
}

inline void dfs(int x)//这个dfs用于计算答案 
{
	sum[cnt[col[x]]+1]++;
	cnt[col[x]]++;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==fa[x]) continue;
		dfs(y);
	}
}

int main()
{
	scanf("%d%d",&n,&m);//输入 
	for(register int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	for(register int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Addedge(a,b);
		Addedge(b,a);
	}
	for(register int i=1;i<=m;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		q[a].push_back(make_pair(b,i));
	}
	predfs(1,0);
	for(register int i=1;i<=n;++i)//分别处理所有询问 
	{
		memset(cnt,0,sizeof(cnt));
		memset(sum,0,sizeof(sum));
		dfs(i);
		for(register int j=0;j<q[i].size();++j)//离线回答询问 
		{
			int a=q[i][j].first;
			ans[q[i][j].second]=sum[a];
		}
	}
	for(register int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
    return 0;
}
```

### **AC 解法**

这就需要用到 `dsu on tree` 的思想。

之前 `TLE` 解法中的许多东西很值得我们借鉴，比如：$sum(x)$ 和 $cnt(x)$ , 用 `vector` 离线处理询问，用 `dfs` 一遍处理某个结点子树中的所有询问。

把这些东西搬到 `dsu on tree` 的模板上，再稍微改动一点，这道题就可以过了。

```cpp
#include<bits/stdc++.h>
#include<vector>
#define Maxn int(1e5)
using namespace std;
typedef pair<int,int> Pair;

struct Node
{
	int to,nxt;
} Edge[(Maxn<<1)+5];
int tot,Head[Maxn+5];

inline void Addedge(int x,int y)
{
	Edge[++tot].to=y;
	Edge[tot].nxt=Head[x];
	Head[x]=tot;
}

vector<Pair> q[Maxn+5];//用于处理询问 
int n,m,col[Maxn+5],ans[Maxn+5];
int siz[Maxn+5],son[Maxn+5];
int cnt[Maxn+5],sum[Maxn+5];

inline void predfs(int x,int f)//之前的dfs用于求重儿子 
{
	siz[x]=1;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==f) continue;
		predfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])
			son[x]=y;
	}
}

int flag;
inline void Count(int x,int f,int k)
{
	if(k==1)//这里的分类讨论需要注意 
	{
		sum[cnt[col[x]]+k]++;
	}
	if(k==-1)
	{
		sum[cnt[col[x]]]--;
	}
	cnt[col[x]]+=k;
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==f || y==flag)
			continue;
		Count(y,x,k);
	}
}

inline void dfs(int x,int f,int typ)//dsu on tree
{
	for(register int i=Head[x];i;i=Edge[i].nxt)
	{
		int y=Edge[i].to;
		if(y==f || y==son[x])
			continue;
		dfs(y,x,0);
	}
	if(son[x])
	{
		dfs(son[x],x,1);
		flag=son[x];
	}
	Count(x,f,1);
	flag=0;
	for(register int i=0;i<q[x].size();++i)//离线回答询问 
	{
		int y=q[x][i].first;
		ans[q[x][i].second]=sum[y];
	}
	if(typ==0)
	{
		Count(x,f,-1);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
		scanf("%d",&col[i]);
	for(register int i=1;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		Addedge(a,b);
		Addedge(b,a);
	}
	for(register int i=1;i<=m;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		q[a].push_back(make_pair(b,i));
	}
	predfs(1,0);
	dfs(1,0,0);
	for(register int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：feecle6418 (赞：2)

这里有一种极其麻烦的方法……

首先看了题就知道是莫队。我太菜不知道怎么维护出现次数大于等于 $x$ 的值的个数，结果用了一种麻烦常数又大的方法，就是值域分块。

但是注意，分的块是针对“出现次数”而言的。具体地，我们每次更新的时候，先在分块结构上让 $cnt_{s_x}$ 减一，然后在分块结构上让 $cnt_{news_x}$ 加一。视情况，$news_x=s_x+1$ 或 $-1$。

然后莫队的时候又很 sb 地写错了这个地方导致 TLE，还以为是常数大了，调了很久：

```cpp
struct Query{
	int l,r,k,id;
	bool operator <(const Query yy) const {
		return bel[l]==bel[yy.l]?bel[l]>bel[yy.l]:r<yy.r;
	}
}q[100005];
```

极其丑陋、麻烦的代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring> 
using namespace std;
struct Edge{
	int to,next;
}e[200005];
int cnt,h[100005],n,m,val[100005],to[100005],ccnt[100005],fk[100005],st[100005],ed[100005];
int vp[100005],sign,ans[100005],L[100005],R[100005],bel[100005],cntt[100005],ALL;
struct Query{
	int l,r,k,id;
	bool operator <(const Query yy) const {
		return bel[l]==bel[yy.l]?bel[l]>bel[yy.l]:r<yy.r;
	}
}q[100005];
void Add_Edge(int x,int y) {
	e[++cnt].next=h[x];
	e[cnt].to=y;
	h[x]=cnt;
}
void DFS(int now,int fa){
	L[now]=++sign,vp[sign]=val[now];
	for(int i=h[now];i;i=e[i].next){
		int y=e[i].to;
		if(y^fa)DFS(y,now);
	}
	R[now]=sign;
}
void Add(int x){
	ccnt[cntt[vp[x]]]--;
	fk[bel[cntt[vp[x]]]]--;
	cntt[vp[x]]++;
	ccnt[cntt[vp[x]]]++;
	fk[bel[cntt[vp[x]]]]++;
}
void Del(int x){
	ccnt[cntt[vp[x]]]--;
	fk[bel[cntt[vp[x]]]]--;
	cntt[vp[x]]--;
	ccnt[cntt[vp[x]]]++;
	fk[bel[cntt[vp[x]]]]++;
}
int Query(int k){
	int ret=0;
	for(int i=k;i<=ed[bel[k]];i++)ret+=ccnt[i];
	for(int i=bel[k]+1;i<=ALL;i++)ret+=fk[i];
	return ret;
}
int main() {
	scanf("%d%d",&n,&m);
	int blk=sqrt(n);
	ALL=n/blk;
	for(int i=1;i<=ALL;i++){
		st[i]=(i-1)*blk+(i!=1),ed[i]=(i==ALL?n:i*blk);
		for(int j=st[i];j<=ed[i];j++)bel[j]=i;
	}
	for(int i=1,tot=0;i<=n;i++){
		scanf("%d",&val[i]);
		if(to[val[i]])val[i]=to[val[i]];
		else to[val[i]]=++tot,val[i]=to[val[i]];
	}
	
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y),Add_Edge(x,y),Add_Edge(y,x);
	}
	DFS(1,0);
	for(int i=1,x;i<=m;i++)scanf("%d%d",&x,&q[i].k),q[i].l=L[x],q[i].r=R[x],q[i].id=i;
	sort(q+1,q+m+1);
	int l=1,r=0;
	ccnt[0]=n;
	for(int i=1;i<=m;i++){
		while(l<q[i].l)Del(l++);
		while(r>q[i].r)Del(r--);
		while(l>q[i].l)Add(--l);
		while(r<q[i].r)Add(++r);
		ans[q[i].id]=Query(q[i].k);
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Erusel (赞：2)

每次查询子树内的信息，很容易想到用 $\text{DFS}$ 序把它转化成序列的问题。

我们考虑每次查询一个区间内出现次数 $\geq k$ 的颜色数，显然这个问题可以用莫队求解

我们用 $\text{cnt[k]}$ 表示出现次数 $\geq k$ 的颜色数，用 $v[i]$ 代表颜色 $i$ 出现的次数

显然我们在莫队移动一次指针时可以在 $O(1)$ 的时间内完成更新，

时间复杂度为 $O(n\sqrt{n})$

注意我们之后的更新都是在字典序上，要统计出在字典序上对应每个节点的颜色

**Code:**

```cpp
#include<bits/stdc++.h>
 
#define rd(x) x=read()
 
#define N 200005
 
using namespace std;

int n,m;
vector<int>e[N];
int l[N],r[N];
int c[N],d[N];
int bel[N],cnt[N],v[N],ans[N];

struct Q{
	int l,r,k,id;
	Q(int _l=0,int _r=0,int _k=0,int _id=0){l=_l,r=_r,k=_k,id=_id;}
}q[N];
int dfn;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
 
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

void dfs(int u,int fa)
{
	l[u]=++dfn,d[dfn]=c[u];
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u);
	}
	r[u]=dfn;
}

inline bool cmp(Q s,Q t){if(bel[s.l]!=bel[t.l])return bel[s.l]<bel[t.l];return s.r<t.r;}
 
inline void add(int i){++v[d[i]],++cnt[v[d[i]]];}
 
inline void del(int i){--cnt[v[d[i]]],--v[d[i]];}

inline void addEdge(int u,int v){e[u].push_back(v);}
 
int main()
{
	rd(n),rd(m);for(int i=1;i<=n;i++)rd(c[i]);
	int size=(int)sqrt(n);for(int i=1;i<=n;i++)bel[i]=(i-1)/size+1;
	for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);dfs(1,0);
	for(int i=1,x,k;i<=m;i++)rd(x),rd(k),q[i]=Q(l[x],r[x],k,i);sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l)del(l++);while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);while(r>q[i].r)del(r--);
		ans[q[i].id]=cnt[q[i].k];
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
 
 
    return 0;
}
```

---

## 作者：YellowBean_Elsa (赞：1)

有人说：我不会线段树合并

有人说：我不会树剖

~~（这种人全世界就我一个吧）~~

所以我
### 提供一种 dsu on tree 做法

不懂dsu on tree的请戳[这里](https://www.luogu.com.cn/blog/Feliks-YB/solution-cf600e)

这题求的是节点最值，类似dsu on tree

但dsu on tree适用于子树最值

于是我们考虑把节点最值转化为子树最值——**树上差分**！

即

把$i$到$j$路径上的点 $ + x$ 变成对 $i,j+x$,对 $lca(i,j)$ 和 $fa_{lca(i,j)}-x$

这样每个点最终的答案就是其**子树的和**（手动模拟即可理解）

然后就是裸的 dsu on tree 了

### 注意

维护最大值时要格外小心，因为树上差分可能为负，统计物资过程中某物资的子树和可能减小，减小时应进行特判，如果最大值减小，要 --mx 
直至存在个数为 mx 的物资

时间较宽裕，我 ~~（脑抽）~~ 用了一堆 STL，总复杂度  $O((n+m)log^2n)$

```cpp
//coder: Feliks a Hacker of IOI == GM-YB an AKer of IMO
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}int v[N],nex[N],first[N],tot;
queue<int> q;
int d[N],fa[21][N>>1],t;
inline void adde(int x,int y){
	v[++tot]=y;
	nex[tot]=first[x];
	first[x]=tot;
}namespace LCA{
	inline void bfs(){
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int i=first[x];i;i=nex[i]){
				int y=v[i];if(d[y])continue;
				d[y]=d[x]+1;q.push(y);fa[0][y]=x;
				for(int j=1;j<=t;j++)
					fa[j][y]=fa[j-1][fa[j-1][y]];
			}
		}
	}inline int lca(int x,int y){
		if(x==y)return x;
		if(d[x]<d[y])swap(x,y);
		//d[x] > d[y]
		for(int i=t;i>=0;i--)
			if(d[fa[i][x]]>=d[y])x=fa[i][x];
		if(x==y)return x;
		for(int i=t;i>=0;i--)
			if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
		return fa[0][x];
	}
}using namespace LCA;
bool gson[N];//重儿子标记 
int sz[N]; //子树大小 
void getg(int x,int f){//work out the great-sons
    int mxx=0,p=0;sz[x]=1;
    for(int i=first[x];i;i=nex[i]){
        int y=v[i];if(y==f)continue;
        getg(y,x);sz[x]+=sz[y];
        if(sz[y]>mxx)mxx=sz[y],p=y;
    }if(p)gson[p]=1;
}map<int,int> cf[N];//树上差分
map<int,int> mp;//hash the items
int num;//the number of the variety of the items (for hash)
int anti[N];//反映射
int cnt[N],ans[N],mx;
//cnt[i]: the current number of the i-th item during dfs
set<int> st[N];//st[i]记录所有cnt[j]=i的j 
inline void add(int x,int s){
	for(map<int,int>::iterator it=cf[x].begin();it!=cf[x].end();it++){
		int a=(*it).first,b=cnt[a];
		if(b>=0)st[b].erase(anti[a]);
		cnt[a]+=s*((*it).second);
		if(cnt[a]>=0)st[cnt[a]].insert(anti[a]);
		if(cnt[a]>=b)if(cnt[a]>mx)mx=cnt[a];
		if(cnt[a]<b && b==mx)while(mx && st[mx].empty())mx--;
	}
}void init(int x,int f){
    for(int i=first[x];i;i=nex[i]){
        int y=v[i];if(y==f)continue;
        init(y,x);
    }add(x,-1);
}inline void getans(int x,int f,int p){
    for(int i=first[x];i;i=nex[i]){
        int y=v[i];if(y==f || y==p)continue;
        getans(y,x,p);
    }add(x,1);
}void dfs(int x,int f){
    int p=0;
	for(int i=first[x];i;i=nex[i]){
        int y=v[i];if(y==f)continue;
        if(gson[y]){p=y;continue;}
        dfs(y,x);init(y,x);mx=0;
    }if(p)dfs(p,x);
    getans(x,f,p);
    if(mx>0)ans[x]=*st[mx].begin();
    else ans[x]=0;
}int main(){
	n=read(),m=read();
	t=(int)(log(n)/log(2.0))+1;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		adde(x,y),adde(y,x);
	}d[1]=1,q.push(1);bfs();getg(1,0);
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read(),f=lca(x,y);
		if(mp.find(z)==mp.end()){
			mp.insert(make_pair(z,++num));
			anti[num]=z;
		}z=mp[z];
		//树上差分 
		cf[x][z]++,cf[y][z]++,cf[f][z]--,cf[fa[0][f]][z]--;
	}for(int i=1;i<=num;i++)st[0].insert(anti[i]);
	dfs(1,0);
    //cout<<"ILOVEYUKIJZY"<<endl;
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：lhm_ (赞：1)

树上数颜色，因为是查询子树，所以用 $dfn$ 序将树上问题转化为序列问题，然后就是裸的莫队数颜色了。

统计答案时还需注意一些细节问题，实现就看代码。

时间复杂度为 $O(n\sqrt{n})$。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,block,l=1,r,tot;
int a[maxn],c[maxn],cnt[maxn],ans[maxn],num[maxn];
struct query
{
    int l,r,id,pos,ask;
}q[maxn];
bool cmp(query a,query b)
{   
    return a.pos==b.pos?(a.pos&1?a.r<b.r:a.r>b.r):a.pos<b.pos;
}
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
int dfn_cnt;
int siz[maxn],dfn[maxn];
void dfs(int x)
{
    siz[x]=1;
    dfn[x]=++dfn_cnt;
    c[dfn_cnt]=a[x];
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(dfn[y]) continue;
        dfs(y);
        siz[x]+=siz[y];
    }
}
void update(int x,int p)
{
    x=c[x];
    cnt[x]+=p;
    if(~p) num[cnt[x]]++;
    else num[cnt[x]+1]--;
}
int main()
{
	read(n),read(m);
    block=sqrt(n);
    for(int i=1;i<=n;++i) read(a[i]);
    for(int i=1;i<n;++i)
    {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        int root;
        read(root),read(q[i].ask);
        q[i].l=dfn[root],q[i].r=dfn[root]+siz[root]-1;
        q[i].id=i,q[i].pos=q[i].l/block;
    }
    sort(q+1,q+m+1,cmp);
    for(int i=1;i<=m;++i)
    {
        int ql=q[i].l,qr=q[i].r,id=q[i].id,ask=q[i].ask;
        while(l<ql) update(l++,-1);
        while(r>qr) update(r--,-1);
        while(l>ql) update(--l,1);
        while(r<qr) update(++r,1);
        ans[id]=num[ask];
    }
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}

```

---

## 作者：p_b_p_b (赞：1)

广告：我的[树上启发式合并总结](https://blog.csdn.net/pb122401/article/details/84648993)

连着两篇莫队题解，那我来发一篇树上启发式合并的

这题一看数颜色：无脑启发式合并搞上去！再一看：大于等于k的？？懵逼了

思考一下，发现这题只需要再套一个数据结构维护sum即可，树状数组或线段树均可

鄙人不才，脑子一抽，写了又长又慢的线段树

```cpp
#include<bits/stdc++.h>
#define sz 100020
#define mod 998244353
using namespace std;
typedef long long ll;
int n;
int col[sz];
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
	edge[++ecnt]=(hh){t,head[f]};
	head[f]=ecnt;
	edge[++ecnt]=(hh){f,head[t]};
	head[t]=ecnt;
}
#define go(x) for (int i=head[x];i;i=edge[i].nxt)
#define v edge[i].t
int tr[sz<<2];
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
void add(int k,int l,int r,int x,int w)
{
	tr[k]+=w;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) add(lson,x,w);
	else add(rson,x,w);
}
int query(int k,int l,int r,int x,int y)
{
	if (x<=l&&r<=y) return tr[k];
	int mid=(l+r)>>1,ret=0;
	if (x<=mid) ret+=query(lson,x,y);
	if (y>mid) ret+=query(rson,x,y);
	return ret;
}
int size[sz],son[sz];
void dfs1(int x,int fa)
{
	size[x]=1;
	go(x) if (v!=fa)
	{
		dfs1(v,x);
		size[x]+=size[v];
		if (size[v]>size[son[x]]) son[x]=v;
	}
}
#define pii pair<int,int>
#define MP make_pair
#define fir first
#define sec second
vector<pii>q[sz];
int ans[sz];
int cnt[sz];
int S;
void add(int x,int fa,int t)
{
	add(1,1,n,cnt[col[x]]+1,-1);
	cnt[col[x]]+=t;
	add(1,1,n,cnt[col[x]]+1,1);
	go(x) if (v!=fa&&v!=S) add(v,x,t);
}
void dfs2(int x,int fa,bool keep)
{
	go(x) if (v!=fa&&v!=son[x]) dfs2(v,x,0);
	if (son[x]) dfs2(son[x],x,1);
	S=son[x];
	add(x,fa,1);
	for (int i=0;i<(int)q[x].size();i++) ans[q[x][i].fir]=query(1,1,n,q[x][i].sec+1,n);
	S=0;
	if (!keep) add(x,fa,-1);
}
int main()
{
	ios::sync_with_stdio(0);
	int i,x,y,m;
	cin>>n>>m;
	for (i=1;i<=n;i++) cin>>col[i];
	for (i=1;i<n;i++) cin>>x>>y,make_edge(x,y);
	for (i=1;i<=m;i++) cin>>x>>y,q[x].push_back(MP(i,y));
	dfs1(1,0);dfs2(1,0,1);
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
}
```

附：致尊敬的管理员：另两篇都是莫队，这就给个通过呗

---

## 作者：一架飞机 (赞：0)

因为要处理子树信息，所以用[树上启发式合并](https://oi-wiki.org/graph/dsu-on-tree/)。

然后就和板子（求子树上出现最多的颜色）差不多。

因为树上启发式合并是离线，所以把询问放到点上，遍历到的时候把答案存下来。

记录两个值，一个是颜色$i$出现的次数（$vst[i]$），一个是出现次数$\geq i$的颜色的种数（$f[i]$）。

**如何求$f[i]$：** 因为我们不能遍历$vst[i]$，所以就考虑在每次修改$vst[c]$（c：当前节点颜色）时改，设修改后的值是k，所以$f[1]$~$f[k]$都应该包含c，但上一次修改$vst[c]$时已经让$f[1]$~$f[k-1]$包含c了，所以这次让$f[k]$包含c就行了。这样也可以保证不重复。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1e5+5;
int Head[M],Nxt[M*2],To[M*2],TOT,sz[M],son[M];ll c[M];
vector<pair<int,int> > ques[M];
int ADD(int x,int y){
	Nxt[++TOT]=Head[x];Head[x]=TOT;To[TOT]=y;
}
void dfs_basic(int x,int fa){//求出sz[x]和son[x]
	sz[x]=1;
	for(int i=Head[x];i;i=Nxt[i]){
		if(To[i]==fa)continue;
		dfs_basic(To[i],x);
		sz[x]+=sz[To[i]];
		if(sz[To[i]]>sz[son[x]])son[x]=To[i];
	}
}
int vst[M],ans[M],f[M];
void search(int x,int fa,int opt,int notto){//暴力地遍历轻儿子
	if(opt){
		vst[c[x]]++;f[vst[c[x]]]++;
   //}else vst[c[x]]=0,f[vst[c[x]]]=0;//f[]要一个一个删
	}else f[vst[c[x]]]=0,vst[c[x]]--;
	for(int i=Head[x];i;i=Nxt[i]){
		int y=To[i];if(y==fa||y==notto)continue;
		search(y,x,opt,notto);
	}
}
void dfs_main(int x,int fa,int opt){//遍历x，求答案
	for(int i=Head[x];i;i=Nxt[i]){
		int y=To[i];if(y==fa)continue;
		if(y!=son[x])dfs_main(y,x,0);
	}
	if(son[x])dfs_main(son[x],x,1);
	search(x,fa,1,son[x]);for(int i=0;i<ques[x].size();i++)ans[ques[x][i].second]=f[ques[x][i].first];
	if(!opt)search(x,fa,0,0);
}
ll cc[M];
void lsh(int n){//离散化
	for(int i=1;i<=n;i++)cc[i]=c[i];
	sort(cc+1,cc+n+1);int nn=unique(cc+1,cc+n+1)-cc-1;
	for(int i=1;i<=n;i++)c[i]=lower_bound(cc+1,cc+nn+1,c[i])-cc;
}
int main(){
	int n,m,a,b;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
	lsh(n);
	for(int i=1;i<=n-1;i++)scanf("%d%d",&a,&b),ADD(a,b),ADD(b,a);
	for(int i=1;i<=m;i++)scanf("%d%d",&a,&b),ques[a].push_back(make_pair(b,i));
	dfs_basic(1,0);
	dfs_main(1,0,1);
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
} 
```

---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF375D)

---

为什么这么多人写莫队~~根号万岁~~。

我们可以发现，题目不需要修改，可以离线处理。

很容易想到用 $\text{DSU on tree}$ 来维护颜色出现次数。

但题目要求要找出现次数比 $\text k$ 大的次数。

自然，你可以暴力，但这样会超时，所以我们可以用 $\text{BIT}$ 来维护出现次数~~貌似可以值域分块~~。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x & -x)
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

const int maxn = 1e5 + 5;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int u,int v) {
	nxt[++ tot] = head[u];ver[tot] = v;head[u] = tot;
}
vector<pair<int,int> > q[maxn];
int n,m,col[maxn],sz[maxn],son[maxn],cnt[maxn],ans[maxn],dep[maxn],tree[maxn],sum,maxx,Son;
void update(int x,int y) {
	for ( ; x <= n + 1 ; x += lowbit(x)) tree[x] += y;
}
int query(int x) {
	int res = 0;
	for ( ; x ; x -= lowbit(x)) res += tree[x];
	return res;
}
void dfs1(int u,int f) {
	sz[u] = 1;
	int maxson = -1;
	for(int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == f) continue;
		dfs1(v,u);
		sz[u] += sz[v];
		if(sz[v] > maxson) maxson = sz[v],son[u] = v;
	}
}
void change(int u,int fa,int val) {
	update(cnt[col[u]] + 1,-1);
	cnt[col[u]] += val;
	update(cnt[col[u]] + 1,1);
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == Son || v == fa) continue;
		change(v,u,val);
	}
}
void dfs2(int u,int fa,int op) {
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == son[u] || v == fa) continue;
		dfs2(v,u,0);
	}
	if (son[u]) dfs2(son[u],u,1),Son = son[u];
	change(u,fa,1);
	for (int i = 0 ; i < q[u].size() ; ++ i) ans[q[u][i].second] = query(n + 1) - query(q[u][i].first);
	Son = 0;
	if (!op) change(u,fa,-1);
}
signed main () {
	read(n);read(m);
	int u,v;
	for (int i = 1 ; i <= n ; ++ i) read(col[i]);
	for (int i = 1 ; i < n ; ++ i) {
		read(u);read(v);
		addEdge(u,v);
		addEdge(v,u);
	}
	for (int i = 1 ; i <= m ; ++ i) {
		read(u);read(v);
		q[u].push_back(make_pair(v,i));
	}
	dfs1(1,0);
	dfs2(1,0,0);
	for (int i = 1 ; i <= m ; ++ i) print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：qiyue7 (赞：0)

写点奇怪的题解......

由于这题允许离线，所以我们选用dsu on tree离线处理所有询问（如果需要强制在线那么我们需要两颗可持久化的线段树同步维护）

   我们知道在经典的dsu on tree中如果要合并一个数据出现的次数那么可以用hash_map来启发式合并进行计数，复杂度O(nlogn)。但是这题比较特殊，还要求个排名（求大于等于k的种类数即转化为求（k+1）的种类数的rank）（手写个平衡树似乎有点麻烦）
   不过pb_ds里面已经提供了高效的hash_map以及红黑树，那么我们直接暴力dsu on tree 同步维护就行了。

（不过这个东西虽然比手写数据结构省事而且还快，但是还是要看对STL的熟练程度才能说好不好写，代码细节比较多，而且包含了很多小技巧，1A了我个人还是比较惊讶的。）

AC代码：
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/exception.hpp>
#include<ext/pb_ds/list_update_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
const int N=220000;
gp_hash_table<int,int> *cnt[N];
tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> *tree2[N];
vector<int> edge[N];
array<int,N> ans;
array<bool,N> vis;
list<pair<int,int> > query[N];
int L=0;
void merge(int a,int b)
{
    int k=a;
    if(cnt[a]->size()<cnt[b]->size())
        swap(a,b);
        for(auto &s:*cnt[b])
        {
            if(cnt[a]->find(s.first)==cnt[a]->end())
            {
                tree2[a]->insert({-s.second,++L});
                (*cnt[a])[s.first]=s.second;
            }
            else
            {
                auto it=tree2[a]->lower_bound({-(*cnt[a])[s.first]+1,0});
                --it;
                tree2[a]->erase(it);
                (*cnt[a])[s.first]+=s.second;
                tree2[a]->insert({-(*cnt[a])[s.first],++L});
            }
        }
    tree2[b]->clear(),cnt[b]->clear();
    if(k==b)
        cnt[k]=cnt[a],tree2[k]=tree2[a];
}
void dfs(int a)
{
    vis[a]=true;
    for(auto &s:edge[a])
        if(vis[s]==false)
        {
            dfs(s);
            merge(a,s);
        }
    while(!query[a].empty())
        {
            ans[query[a].front().second]=tree2[a]->order_of_key({-query[a].front().first+1,0});
            query[a].pop_front();
        }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,m,u,v,q,k;
    cin>>n>>q;
    for(int i=1;i<=n;++i)
    {
        cnt[i]=new gp_hash_table<int,int>();
        tree2[i]=new tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>();
        cin>>k;
        (*cnt[i])[k]=1;
        tree2[i]->insert({-1,++L});
    }
    for(int i=0;i<n-1;++i)
        {
            cin>>u>>v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    for(int i=1;i<=q;++i)
    {
        cin>>u>>v;
        query[u].push_back({v,i});
    }
    dfs(1);
    for(int i=1;i<=q;++i)
        cout<<ans[i]<<'\n';
    return 0;
}

```


---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/9954741.html)

#### [原题传送门](https://www.luogu.org/problemnew/show/CF375D)

#### 莫队好题

我一上来想写线段树，随后觉得不好写并弃坑

我们可以看见没有修改操作，钦定莫队

但这是在树上，所以不能直接用莫队~~（废话）~~

我们要树链剖分，使得节点和节点的子树能在一个区间里（不会树链剖分的出门左转[洛咕树链剖分模板](https://www.luogu.org/problemnew/show/P3384)）

剩下的就是最基础的莫队，但是前置和后置++，--要注意qaq，我以前写莫队经常因为++，--的问题出锅qaq

#### 剩下一些细节见程序

```cpp
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define N 100005
using namespace std;
inline int read() //io优化
{
	register int x=0,f=1;register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
inline void write(register int x)
{
	if(!x)putchar('0');if(x<0)x=-x,putchar('-');
	static int sta[36];int tot=0;
	while(x)sta[tot++]=x%10,x/=10;
	while(tot)putchar(sta[--tot]+48);
}
struct edge{
	int to,next;
}e[N<<1];
int head[N],cnt;
struct query{
	int l,r,id,bl,k;
}q[N];
int n,m,blocksize;
int c[N];
int in[N],out[N],w[N];
inline void dfs(register int x,register int fa)
{
	in[x]=++cnt;
	w[cnt]=c[x];
    for (register int i=head[x];i;i=e[i].next)
	{
        int y=e[i].to;
		if (y==fa) 
			continue;
		dfs(y,x);
    }
	out[x]=cnt;
}
inline bool cmp(register query a,register query b)
{
	return a.bl==b.bl?a.r<b.r:a.bl<b.bl;
}
int ans[N],f[N],res[N]; //f[i]表示当前颜色为i的节点的个数，ans[i]表示当前出现次数大于等于i的颜色数量，res是最后的结果
bool inq[N];
inline void update(register int x)
{
	if(inq[x])
		--ans[f[w[x]]--];
	else
		++ans[++f[w[x]]];
	inq[x]^=1;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;++i)
		c[i]=read();
	for(register int i=1;i<n;++i)
	{
		int x=read(),y=read(); //链式前向星建图
		e[++cnt]=(edge){y,head[x]};
		head[x]=cnt;
		e[++cnt]=(edge){x,head[y]};
		head[y]=cnt;
	}
	cnt=0;
	dfs(1,1); //树剖
	blocksize=sqrt(n); //莫队块的大小
	for(register int i=1;i<=m;++i)
	{
		int v=read(),k=read();
		q[i]=(query){in[v],out[v],i,(in[v]-1)/blocksize+1,k};
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;
	for(register int i=1;i<=m;++i)
	{
		int ll=q[i].l,rr=q[i].r;
		while(l<ll)
			update(l++);
		while(l>ll)
			update(--l);
		while(r>rr)
			update(r--);
		while(r<rr)
			update(++r);
		res[q[i].id]=ans[q[i].k];
	}
	for(register int i=1;i<=m;++i)
	{
		write(res[i]);
		printf("\n");
	}
	return 0;
 } 
```

---

## 作者：elijahqi (赞：0)

 http://www.elijahqi.win/2018/03/01/codeforces-375d/ 
 http://blog.csdn.net/elijahqi/article/details/79408693
 题意翻译

给出一棵 n 个结点的树，每个结点有一个颜色 c i 。 询问 q 次，每次询问以 v 结点为根的子树中，出现次数 ≥k 的颜色有多少种。

考虑子树一定是dfs序列上一个连续的区间 那么每次对子树操作总相当于针对dfs序上的一段连续区间操作

就可以莫队了 设ans表示出现次数超过i次的颜色数 f[i]表示i号颜色出现的次数 Ans相对应的记录每个询问的答案 那么考虑每个颜色出现一定是从0~xx 那么我每出现一次 我即对ans进行修改即可 并不需要区间修改 然后相应的减去的时候 也是这时候的出现次数-1  然后对应的ans数组再减1即可
```
#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 110000
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0,f=1;char ch=gc();
    while(ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=gc();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x*f;
}
struct node1{
    int y,next;
}data[N<<1];
struct node{
    int l,r,id,bl,k;
}qr[N];bool visit[N];
int num,h[N],in[N],out[N],w[N],c[N],ans[N],Ans[N],f[N],nn,n,m;
inline bool cmp(const node &a,const node &b){
    return a.bl==b.bl?a.r<b.r:a.bl<b.bl;
}
inline void dfs(int x,int fa){
    in[x]=++num;w[num]=c[x];
    for (int i=h[x];i;i=data[i].next){
        int y=data[i].y;if (y==fa) continue;dfs(y,x);
    }out[x]=num;
}
inline void update(int x){
    if (visit[x]) --ans[f[w[x]]--];
    else ++ans[++f[w[x]]];
    visit[x]^=1;
}
int main(){
//	freopen("cf375d.in","r",stdin);
    n=read();m=read();for (int i=1;i<=n;++i) c[i]=read();
    for (int i=1;i<n;++i){
        int x=read(),y=read();
        data[++num].y=y;data[num].next=h[x];h[x]=num;
        data[++num].y=x;data[num].next=h[y];h[y]=num;
    }num=0;dfs(1,1);nn=sqrt(n);
    for (int i=1;i<=m;++i) {
        qr[i].id=i;int x=read();qr[i].l=in[x];qr[i].r=out[x];qr[i].k=read();
        qr[i].bl=(qr[i].l-1)/nn+1;
    }sort(qr+1,qr+m+1,cmp);
    int cl=1,cr=0;
    for (int i=1;i<=m;++i){
        int l=qr[i].l,r=qr[i].r;
        while(cl<l) update(cl++);
        while(cl>l) update(--cl);
        while(cr>r) update(cr--);
        while(cr<r) update(++cr);
        Ans[qr[i].id]=ans[qr[i].k];
    }
    for (int i=1;i<=m;++i) printf("%d\n",Ans[i]);
    return 0;
}
```

---

