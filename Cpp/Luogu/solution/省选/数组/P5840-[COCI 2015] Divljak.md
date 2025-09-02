# [COCI 2015] Divljak

## 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。
2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。


## 样例 #1

### 输入

```
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3
```

### 输出

```
1
2
1
```

# 题解

## 作者：Calculatelove (赞：28)

# Description

有 $n$ 个字符串 $S_1, S_2, \cdots, S_n$。以及一个字典 $T$，一开始字典 $T$ 为空。

接下来有 $q$ 个操作，操作包含以下两种：

- `1 P`：向字典 $T$ 中插入一个字符串 $P$。
- `2 x`：请你求出 $S_x$ 是字典 $T$ 中多少个串的子串。

数据范围：$1 \leq n, q \leq 10^5$，字符集为小写字母集，字符串总长 $\leq 2 \times 10^6$。   
时空限制：$4000 \ \text{ms} / 500 \ \text{MiB}$。

# Solution

操作 2 是一个多模匹配问题。

考虑将 $S_1, S_2, \cdots, S_n$ 建出 AC 自动机。  
对 AC 自动机上的每一个点 $u$，求出它的失配指针 $fail_u$，将 $fail_u \to u$ 连边，即可得到一棵 $fail$ 树。

对于字典 $T$ 中新插入的一个字符串 $P$，考虑求 $P$ 对 $S_1, S_2, \cdots, S_n$ 中的哪些字符串造成贡献。

考虑文本串 $P$ 匹配的过程：$P$ 在 AC 自动机上一个字符一个字符走的过程，相当于枚举了一个前缀，任意时刻在 AC 自动机（trie 图）上走到的节点 $u$ 代表的字符串，即为该前缀与自动机匹配的最长后缀。那么，我们考虑在 $u$ 节点这个位置向上跳 $fail$ 指针，根据 $fail$ 指针的定义，路径上经过的每一个节点代表的字符串都是 $P$ 的子串。

设 $P$ 在 AC 自动机上依次走到了节点 $u_1, u_2, \cdots, u_k$。  
那么 $P$ 在 AC 自动机上能匹配到的子串位于 $u_1, u_2, \cdots, u_k$ 在 $fail$ 树上到根节点上的链的点集并。  
那么现在要做的是将该点集内的所有点的答案加上 $1$，本质上是一个树链求并。

注意到根节点是固定的，可以考虑将 $u_1, u_2, \cdots, u_k$ 按照在 $fail$ 树中的 dfs 序排序后，做下面的事情：

- 对于每个 $1 \leq i \leq k$，将 $u_i$ 在 $fail$ 树上到根节点上的链的所有点的答案加上 $1$。
- 对于每个 $1 \leq i < k$，将 $\text{lca}(u_i, u_{i + 1})$ 在 $fail$ 树上到根节点上的链的所有点的答案减去 $-1$。

现在问题转化为了：" 路径加 " & " 单点求值 "。  
可以使用**树上差分**将问题转化为：" 单点加 " & " 子树求和 "。

利用在 dfs 序上维护一个树状数组即可实现上述操作。

时间复杂度即为线性对数（线性函数乘上对数函数）。

# Code

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue> 

using namespace std;

const int N = 100100, SIZE = 2001000;

int n, m;

char S[N]; 

int cT = 1;
struct AC {
	int trans[26];
	int fail;
} t[SIZE];

int End[N];

void insert(char *S, int id) {
	int p = 1, len = strlen(S + 1);
	for (int i = 1; i <= len; i ++) {
		int v = S[i] - 'a';
		if (!t[p].trans[v]) t[p].trans[v] = ++ cT;
		p = t[p].trans[v];
	}
	End[id] = p;
}

void GetFail() {
	for (int i = 0; i < 26; i ++)
		t[0].trans[i] = 1;

	queue<int> q;
	q.push(1), t[1].fail = 0;

	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < 26; i ++) {
			if (t[u].trans[i])
				t[t[u].trans[i]].fail = t[t[u].fail].trans[i], q.push(t[u].trans[i]);
			else
				t[u].trans[i] = t[t[u].fail].trans[i];
		}
	}
}

int tot, head[SIZE], ver[SIZE], Next[SIZE];

void addedge(int u, int v) {
	ver[++ tot] = v;    Next[tot] = head[u];    head[u] = tot;
}

int d[SIZE];
int size[SIZE];
int son[SIZE];

void dfs1(int u) {
	size[u] = 1;

	for (int i = head[u]; i; i = Next[i]) {
		int v = ver[i];
		d[v] = d[u] + 1;
		dfs1(v);
		size[u] += size[v];
		if (size[v] > size[son[u]]) son[u] = v;
	}
}

int ovo, dfn[SIZE];
int top[SIZE];

void dfs2(int u) {
	dfn[u] = ++ ovo;

	if (son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
	}

	for (int i = head[u]; i; i = Next[i]) {
		int v = ver[i];
		if (v == son[u]) continue; 
		top[v] = v;
		dfs2(v);
	}
}

int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (d[top[x]] > d[top[y]]) swap(x, y);
		y = t[top[y]].fail;
	}
	if (d[x] > d[y]) swap(x, y);
	return x;
}

int c[SIZE];

void add(int x, int val) {
	for (; x <= cT; x += x & -x) c[x] += val;
}

int ask(int x) {
	int ans = 0;
	for (; x; x -= x & -x) ans += c[x];
	return ans;
}

int seq[SIZE];

bool cmp(int i, int j) {
	return dfn[i] < dfn[j];
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i ++) {
		scanf("%s", S + 1);
		insert(S, i);
	}

	scanf("%d", &m);

	GetFail();

	for (int i = 2; i <= cT; i ++)
		addedge(t[i].fail, i); 

	d[1] = 1, dfs1(1);
	top[1] = 1, dfs2(1);

	while (m --) {
		int opt, x;
		scanf("%d", &opt);

		switch (opt) {
			case 1: {
				scanf("%s", S + 1);

				int p = 1, len = strlen(S + 1);
				for (int i = 1; i <= len; i ++) {
					int v = S[i] - 'a';
					p = t[p].trans[v];
					seq[i] = p;
				}

				sort(seq + 1, seq + 1 + len, cmp);

				for (int i = 1; i <= len; i ++) {
					int p = seq[i];
					add(dfn[p], 1);
				} 

				for (int i = 1; i < len; i ++) {
					int p = seq[i], q = seq[i + 1];
					add(dfn[lca(p, q)], -1);
				} 

				break;
			}

			case 2: {
				scanf("%d", &x);
				int p = End[x];
				printf("%d\n", ask(dfn[p] + size[p] - 1) - ask(dfn[p] - 1));

				break;
			} 
		}
	} 

	return 0;
}
```

---

## 作者：皎月半洒花 (赞：13)

~~首先给烈士搬题人上香~~

大概是考虑，反正是匹配问题——那么是对着 $\rm T$ 建自动机呢，还是对 $\rm \{S_n\}$ 建。 考虑 AC 自动机更适合做这种匹配题，于是大概想到要拿 AC 自动机做；考虑如果对着 $\rm T$ 建自动机，树的形态会变，$\rm S$ 的信息需要动态维护，并不很好做，于是考虑对 $\rm S$ 建自动机 $\rm AC_s$。

考虑这样做，就需要在已经建好的自动机上，对于每个新加进来的 $P$ 计算贡献。那么会被 $P$ 包含的字符串，一定是 $P$ 在 $\rm AC_s$ 里匹配的 $endpos$ 到根的路径上每个点，到根的链上的点集并。暴力是 $n^2$ 的，考虑如何快速计算这个贡献，发现能做到最快的，也就是通过维护 dfs 序的方式求出点集并。对于每一个这样的链的并打一个标记。询问的时候只需要回答一下子树内有多少个点被打了不同的标记。

发现「维护树链标记」+「子树求和」，最快速的方法是维护差分。同时由于是动态的，可以想到用线段树或者 BIT 快速维护。

考虑修改如何进行。发现为了保证 $\and$ 形态的链只会被计数一次，需要在 $lca$ 处差分。此处需要注意的是，要对 $dfs$ 序排序之后，再逐个差分，方法是 $(i,+1),(i+1,+1),(lca_{i,i+1},-1)$ 。

想了半天才大约明白为什么要按 dfs 序排一遍序。大概是如果不按 dfs 序的顺序枚举，可能会出现某个子树未被成功打上标记的情况。

最终复杂度是 $O(\rm |S|\log |S|)$ 的，跑的不是很快。

哦，对，`_end`是关键字，千万别忘了。

```cpp
#define Sigma 27
#define il inline
#define MAXN 2000010

using namespace std ;

char S[MAXN] ;
int T, M, N, L[MAXN] ;
struct Edge{
    int to, next ;
    #define to(k) E[k].to
    #define next(k) E[k].next
}E[MAXN] ; int head[MAXN], base[MAXN], cnt, tot ;
int _ed[MAXN], dfn[MAXN], rgl[MAXN], rgr[MAXN], tp ;
int sz[MAXN], dep[MAXN], fa[MAXN], top[MAXN], son[MAXN], val[MAXN] ;

void add(int u, int v){
    E[++ cnt].to = v, E[cnt].next = head[u], head[u] = cnt ;
}
void dfs(int u){
    sz[u] = 1, dep[u] = dep[fa[u]] + 1 ;
    for (int k = head[u] ; k ; k = next(k)){
        fa[to(k)] = u, dfs(to(k)), sz[u] += sz[to(k)] ;
        if (!son[u] || sz[to(k)] > sz[son[u]]) son[u] = to(k) ;
    }
}
void dfs2(int u, int tp){
    top[u] = tp,
    dfn[u] = rgl[u] = ++ tot ;
    if (son[u]) dfs2(son[u], tp) ;
    for (int k = head[u] ; k ; k = next(k))
        if (to(k) != son[u]) dfs2(to(k), to(k)) ;
    rgr[u] = tot ;
}
il bool comp(int x, int y){ return dfn[x] < dfn[y] ; }
int lca(int u, int v){
    while (top[u] != top[v]){
        if (dep[top[u]] >= dep[top[v]]) u = fa[top[u]] ;
        else v = fa[top[v]] ;
    }
    return dep[u] < dep[v] ? u : v ;
}

void _up(int rt){
    val[rt] = val[rt << 1] + val[rt << 1 | 1] ;
}
void update(int rt, int l, int r, int p, int v){
    if (l == r)
        return val[rt] += v, void() ;
    int mid = (l + r) >> 1 ;
    if (mid >= p)
        update(rt << 1, l, mid, p, v) ;
    else update(rt << 1 | 1, mid + 1, r, p, v) ;
    _up(rt) ;
}
int query(int rt, int l, int r, int pl, int pr){
	if (pl > pr) return 0 ; 
    if (l >= pl && pr >= r) return val[rt] ;
    int mid = (l + r) >> 1, res = 0 ;
    if (pl <= mid) res += query(rt << 1, l, mid, pl, pr) ;
    if (pr > mid) res += query(rt << 1 | 1, mid + 1, r, pl, pr) ;
    return res ;
}
struct ACAM{
    queue <int> q ;
    int _size, fail[MAXN] ;
    int trie[MAXN][Sigma] ;
    void insert(char *s, int n){
        int rt = 0, x ;
        for (int i = 1 ; i <= L[n] ; ++ i){
            x = s[i] - 'a' ;
            if (!trie[rt][x])
                trie[rt][x] = ++ _size ;
            rt = trie[rt][x] ;
        }
        _ed[n] = rt ;
    }
    void build(){
        for (int i = 0 ; i < Sigma ; ++ i)
            if (trie[0][i]) q.push(trie[0][i]) ;
        while (!q.empty()){
            int n = q.front() ; add(fail[n], n), q.pop() ;
            for (int i = 0 ; i < 26 ; ++ i){
                if (!trie[n][i]) trie[n][i] = trie[fail[n]][i] ;
                else fail[trie[n][i]] = trie[fail[n]][i], q.push(trie[n][i]) ;
            }
        }
    }
    void solve(char *S){
        int x, rt = 0 ; tp = 0 ;
        for (int i = 1 ; i <= N ; ++ i)
            x = S[i] - 'a', rt = trie[rt][x], base[++ tp] = rt ;
        sort(base + 1, base + tp + 1, comp),
        tp = unique(base + 1, base + tp + 1) - base - 1 ;
        for (int i = 1 ; i <= tp ; ++ i){
            update(1, 1, tot, dfn[base[i]], 1) ;
            if (i > 1) update(1, 1, tot, dfn[lca(base[i], base[i - 1])], -1) ;
        }
    }
}AC ;

int qr(){
    int r = 0 ; char c = getchar() ;
    while (!isdigit(c)) c = getchar() ;
    while (isdigit(c)) r = (r << 1) + (r << 3) + c - 48, c = getchar() ;
    return r ;
}
int main(){
    // freopen("1.in", "r", stdin) ;
    // freopen("1.ans", "w", stdout) ;
    cin >> T ; int m, q ;
    for (int i = 1 ; i <= T ; ++ i)
        scanf("%s", S + 1), L[i] = strlen(S + 1), AC.insert(S, i) ;
    AC.build() ; cin >> M ; dfs(0), dfs2(0, 0) ;
//    for (int i = 1 ; i <= T ; ++ i) cout << rgl[i] << " " << rgr[i] << endl ;
    while (M --){
        m = qr() ;
        if (m == 1) scanf("%s", S + 1), N = strlen(S + 1), AC.solve(S) ;
        else q = qr(),
            printf("%d\n", query(1, 1, tot, 1, rgr[_ed[q]]) - query(1, 1, tot, 1, rgl[_ed[q]] - 1)) ;
    }
    return 0 ; 
}

```

吐槽

* 为啥`lxl`常数这么小啊（

* `_end`这东西一调一上午啊qaq


---

## 作者：QwQ蒟蒻wjr (赞：9)

[我的blog](https://www.cnblogs.com/wangjunrui/p/12321083.html)
> > 题目链接：[洛谷P5840 [COCI2015]Divljak](https://www.luogu.com.cn/problem/P5840)


$$preface$$

一道AC自动机+LCA+树链剖分+树上差分+树状数组维护的恶心题

$$description$$

首先理解trie，树上任意一个节点到跟节点是插入串的前缀，而$nxt$指针是指向这个前缀的后缀。

我们建一棵关于这样的树，一个节点的子树上的所有节点到根都是把其这个节点当做后缀，那我们就建一棵树。

先将$S$串集合建一个AC自动机

然后将$(nxt[u],u)$插入这条树(是另建一棵树，不是AC自动机的Trie树)的边，显然如果$nxt[u]=0$连向的是根节点
(我的代码根节点是$0$，所以不做判断)。

接着再将建好的那棵树求出每个节点的$dfs$序。

我们用到树上差分的思想，然后把要插入的$T$集合在$Trie$树中统计走过的节点，记录下来，再按$dfn$排序，将相邻两个节点的在树上的位置$+1$，表示多一个串匹配，但是他们的$LCA$和$LCA$的祖先很明显是$+2$串匹配，不符合我们此串在$T$集合中的出现次数，所以将两个节点的$LCA$的位置标记$-1$。

对于此过程，我们可以用树状数组统计答案，将此树树链剖分后，按每个节点的dfs序维护，同时也可以跑$LCA$，则$S$串在$T$集合中的出现次数为其节点和其子树的之和。
$$code$$
```cpp
#include <cstdio>
#include <queue>
#include <cassert>
#include <algorithm>
#define re register
using namespace std;
const int N=2e6+5,M=1e5+5;
int ch[N][26],nxt[N],tot;
int pos[M];
inline void insert(char *s,int id)
{
	int u=0;
	for(re int i=0; s[i]; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	pos[id]=u;
}
struct Edge
{
	int next,to;
} edge[N];
int head[N],num_edge;
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
inline void build()
{
	queue<int>q;
	for(re int i=0; i<26; ++i)
		if(ch[0][i])
			q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(re int i=0; i<26; ++i)
			if(!ch[u][i])
				ch[u][i]=ch[nxt[u]][i];
			else
			{
				q.push(ch[u][i]);
				nxt[ch[u][i]]=ch[nxt[u]][i];
			}
	}
}
int fa[N],top[N],dep[N],size[N],son[N];
inline void dfs1(int u,int fa_)
{
	fa[u]=fa_;
	size[u]=1;
	dep[u]=dep[fa_]+1;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		dfs1(v,u);
		size[u]+=size[v];
		if(!son[u]||size[v]>size[son[u]])
			son[u]=v;
	}
}
int dfn[N],dfstime;
inline void dfs2(int u,int topf)
{
	top[u]=topf;
	dfn[u]=++dfstime;
//	printf("%d ",u);
	if(!son[u])return;
	dfs2(son[u],topf);
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(v==son[u])
			continue;
		dfs2(v,v);
	}
}
inline int LCA(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return x;
}
int n,q;
char str[N];
int a[N];
int lowbitsum[N];
#define lowbit(x) (x&(-x))
inline void update(int x,int y)
{
//	assert(x>=1);
	for(; x<=dfstime; x+=lowbit(x))
		lowbitsum[x]+=y;
}
inline int query(int x)
{
//	assert(x>=1);
	int res=0;
	for(; x; x-=lowbit(x))
		res+=lowbitsum[x];
	return res;
}
inline bool cmp(const int &x,const int &y)
{
	return dfn[x]<dfn[y];
}
inline void solve1()
{
	int u=0,tp=0;
	for(re int i=0; str[i]; ++i)
	{
		u=ch[u][str[i]-'a'];
		a[++tp]=u;
	}
//	for(re int i=1; i<=tp; ++i)
//		printf("%d ",a[i]);
	sort(a+1,a+1+tp,cmp);
	bool flag=false;
	for(re int i=1; i<=tp; ++i)
	{
		update(dfn[a[i]],1);
		if(flag)
			update(dfn[LCA(a[i],a[i-1])],-1);
		else
			flag=true;
	}
}
inline void solve2()
{
	int x;
	scanf("%d",&x);
	printf("%d\n",query(dfn[pos[x]]+size[pos[x]]-1)-query(dfn[pos[x]]-1));
}
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str);
		insert(str,i);
	}
	build();
//	for(re int i=1; i<=tot; ++i)
//		printf("%d %d\n",nxt[i],i);
	for(re int i=1; i<=tot; ++i)
		add_edge(nxt[i],i);
//	printf("%d\n",num_edge);
	dfs1(0,tot+1);
	dfs2(0,0);
//	printf("%d\n",dfstime);
//	for(re int i=0; i<=tot; ++i)
//		printf("%d ",dfn[i]);
	scanf("%d",&q);
	while(q--)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%s",str);
			solve1();
		}
		else if(opt==2)
			solve2();
	}
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：5)

AC 自动机太 hard 了，提供一个无脑 SA 做法。

----

考虑问题的弱化版本：所有查询在修改之后。我们把所有 $s_i$ 和 $t_i$ 用分隔符隔开，拼在一起得到串 $S$。查询时找到 $S$ 串中以 $t_i$ 开头的后缀的排名 $rk$ 和长度 $len$，以 $rk$ 为中心二分得到 $\operatorname{LCP} \ge len$ 的极长区间，在这个区间内数有多少种不同的 $t_i$ 即可。区间数颜色问题可以离线树状数组一只 $\log$ 解决。

考虑一边插入一边查询，相当于增加了时间维度。离线所有操作，做和上面一样的操作，只不过查询变成了 $[l,r]$ 区间内出现了多少个不同的 $t_i$ 满足 $time_i \le now$。我们知道区间数颜色的本质是二维数点（$i \in [l,r],lst_i \in [1,l-1]$，$lst_i$ 指元素 $a_i$ 上一次出现的位置），那么增加时间维度后问题就变成了三维数点，CDQ 分治即可。

采用 $\log^2$ 的 SA，记 $m = \sum |t_i|,n = \sum |s_i|$，时间复杂度 $\mathcal O((m+q) \log^2(m+q) +(m+n) \log^2 (m+n))$，其中前半部分是 CDQ 分治，后半部分是后缀数组。

但是你 TLE 啦！经过测试发现跑完 SA 就已经 TLE 了。复制 atcoder 头文件里线性 SA 就好了，可以 AC。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.01.2024 11:00:42
**/
#include<bits/stdc++.h>
// #ifdef DEBUG_LOCAL
// #include <mydebug/debug.h>
// debug_helper deg;
// #endif
using ll = long long;
const int N = 4e6+3e5+5;
using namespace std;string s,t;vector<tuple<int,int,int>> qq;
int T,n,al[N],ar[N],q,op,p,m,sa[N],ok[N],rk[N],h[N],st[N][25],len[N],lst[N],mp[N],tr[N],re;
namespace atcoder {
//篇幅原因省略这一部分，见 https://atcoder.github.io/ac-library/production/document_en/string.html
}using namespace atcoder;
void upd(int x,int p){for(;x <= n;x += x & -x) tr[x] += p;}
int qry(int x){for(re = 0;x;x -= x & -x) re += tr[x];return re;}
struct fk{int a,b,c,id;}a[N*3]; 
struct count{
    int cnt,ans[N];
    void add(int x,int y,int z,int id){a[++cnt] = {x,y,z,id};}
    void cdq(int l,int r){
        if(l == r) return ;
        int mid = (l + r) / 2,i = mid + 1,j = l;
        auto cmp = [&](fk a,fk b){return a.b < b.b || a.b == b.b && a.c < b.c;};
        cdq(l,mid),cdq(mid+1,r);
        sort(a+l,a+mid+1,cmp),sort(a+mid+1,a+r+1,cmp);
        for(;i <= r;i ++){
            for(;a[i].b >= a[j].b && j <= mid;j ++) if(!a[j].id) upd(a[j].c,1);
            if(a[i].id != 0) ans[abs(a[i].id)] += (a[i].id > 0 ? 1 : -1) * qry(a[i].c);
        }for(int k = l;k < j;k ++) if(!a[k].id) upd(a[k].c,-1);
    }void sol(int n){for(int i = 1;i <= n;i ++) ans[i] = 0;cnt = 0;}
}hh;
void SA(string &s,int &n){
    n = s.size();
    vector<int> _sa = suffix_array(s);s = " " + s;
    for(int i = 1;i <= n;i ++) sa[i] = _sa[i-1]+1,rk[sa[i]] = i;
}void grgh(int n){
    for(int i = 1,k = 0;i <= n;h[rk[i ++]] = k) 
        for(k --,k = max(k,0);s[i + k] != '#' && s[i + k] == s[sa[rk[i] - 1] + k];k ++); 
    for(int i = 1;i <= n;i ++) st[i][0] = h[i];
    for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
        st[i][j] = min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}void los(){
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> t,al[i] = s.size() + 1,s += t + '#',ar[i] = s.size() - 1,len[i] = t.size();
    cin >> q;int ed = n;
    for(int i = 1;i <= q;i ++){
        cin >> op;
        if(op == 1) cin >> t,al[++n] = s.size() + 1,s += t + '#',ar[n] = s.size() - 1;
        else cin >> p,qq.emplace_back(p,n,i);
    }SA(s,m),grgh(m);
    auto lcp = [&](int i,int j){
        if(i == j) return m - sa[i] + 1;
        int k = __lg(j - i);
        return min(st[i+1][k],st[j-(1<<k)+1][k]);
    };hh.sol(q);
    for(auto [k,id,di] : qq){
        int l,r,ql,qr,le = len[k]; k = rk[al[k]]; 
        for(l = 1,r = k;l <= r;){
            int mid = (l + r) / 2;
            if(lcp(mid,k) >= le) r = mid - 1; else l = mid + 1; 
        }ql = r + 1;
        for(l = k,r = m;l <= r;){
            int mid = (l + r) / 2;
            if(lcp(k,mid) >= le) l = mid + 1; else r = mid - 1;
        }qr = l - 1;
        hh.add(ql-1,ql-1,id,-di),hh.add(qr,ql-1,id,di);
    }for(int i = 1;i <= n;i ++) for(int j = al[i];j <= ar[i];j ++) mp[rk[j]] = i;
    for(int i = 1;i <= m;i ++){
        if(mp[i] <= ed) continue;
        hh.add(i,lst[mp[i]],mp[i],0),lst[mp[i]] = i;
    }//cout << hh.cnt << "\n";
    sort(a+1,a+hh.cnt+1,[&](fk a,fk b){return a.a < b.a || a.a == b.a && a.b < b.b || a.a == b.a && a.b == b.b && a.c < b.c;});
    hh.cdq(1,hh.cnt);
    for(auto [k,id,di] : qq) cout << hh.ans[di] << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：tzc_wk (赞：5)

~~咦？退役选手诈尸了？~~

一道与 AC 自动机与树论结合的题。

我一开始的想法是将 $s_i$ 和所有新加进来的字符串一起搞出一个 AC 自动机出来，然后发现不太行。

不妨换一个角度，只对 $s_i$ 建 AC 自动机，并对于每一个新加进来的字符串 $t$，求出它的贡献。

当我们插入一个 $t$，就用它在 AC 自动机上匹配，假设匹配经过的节点为 $p_1,p_2,\dots,p_{|t|}$。

和上题类似，这些点在 fail 树上的祖先都在 $t$ 中出现过了，将它们对应的值 $+1$。

比较麻烦的一个地方是，本题同一个字符串最多只计算一次贡献，也就是我们要令 $\cup_{i=1}^{|t|}P(p_i)$ 加 $1$，其中 $P(i)$ 为 $i$ 到根节点路径上节点的集合。

此时就要用到一点树论的技巧了，借鉴 [Gym 102082](https://codeforces.ml/gym/102082) J Colorful Tree 的技巧，我们将这 $|t|$ 个节点按 dfs 序排个序，然后在 $p_i$ 打上标记 $1$，并在 $\operatorname{lca}(p_i,p_{i+1})$ 上打上 $-1$。

树状数组计算答案，复杂度线性对数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e5;
const int MAXL=2e6;
const int ALPHA=26;
const int LOG_L=25;
int n,q,ch[MAXL+5][ALPHA+2],ncnt=0,fail[MAXL+5],ed[MAXN+5];
char buf[MAXL+5];
void insert(char *s,int id){
	int len=strlen(s+1),cur=0;
	for(int i=1;i<=len;i++){
		if(!ch[cur][s[i]-'a']) ch[cur][s[i]-'a']=++ncnt;
		cur=ch[cur][s[i]-'a'];
	} ed[id]=cur;
}
void getfail(){
	queue<int> q;
	for(int i=0;i<ALPHA;i++) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<ALPHA;i++){
			if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]);
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}
int to[MAXL+5],nxt[MAXL+5],hd[MAXL+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int bgt[MAXL+5],edt[MAXL+5],tim=0,fa[MAXL+5][LOG_L+2],dep[MAXL+5];
void dfs(int x){bgt[x]=++tim;for(int e=hd[x];e;e=nxt[e]) dep[to[e]]=dep[x]+1,dfs(to[e]);edt[x]=tim;}
int getlca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=LOG_L;~i;i--) if(dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if(x==y) return x;
	for(int i=LOG_L;~i;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
struct fenwick_tree{
	int t[MAXL+5];
	void add(int x,int v){for(int i=x;i<=ncnt+1;i+=(i&(-i))) t[i]+=v;}
	int query(int x){int ret=0;for(int i=x;i;i-=(i&(-i))) ret+=t[i];return ret;}
	int query(int l,int r){return query(r)-query(l-1);} 
} w;
int pt[MAXL+5],ptn=0;
bool cmp(int x,int y){return bgt[x]<bgt[y];}
int main(){
	read(n);
	for(int i=1;i<=n;i++) scanf("%s",buf+1),insert(buf,i);
	read(q);getfail();
	for(int i=1;i<=ncnt;i++) adde(fail[i],i),fa[i][0]=fail[i];dfs(0);
	fa[0][0]=-1;
//	for(int i=0;i<=ncnt;i++) printf("%d %d\n",bgt[i],edt[i]);
	for(int i=1;i<=LOG_L;i++) for(int j=0;j<=ncnt;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
	while(q--){
		int opt;scanf("%d",&opt);
		if(opt==1){
			scanf("%s",buf+1);int len=strlen(buf+1);
			ptn=0;for(int i=1;i<=len;i++) ptn++,pt[ptn]=ch[pt[ptn-1]][buf[i]-'a'];
			sort(pt+1,pt+ptn+1,cmp);ptn=unique(pt+1,pt+ptn+1)-pt-1;
			for(int i=1;i<=ptn;i++) w.add(bgt[pt[i]],1);
			for(int i=1;i<ptn;i++) w.add(bgt[getlca(pt[i],pt[i+1])],-1);
			for(int i=1;i<=ptn;i++) pt[i]=0;
		} else {
			int x;scanf("%d",&x);printf("%d\n",w.query(bgt[ed[x]],edt[ed[x]]));
		}
	}
	return 0;
}
/*
3
a
b
ab
7
1 abc
1 ba
1 aa
1 bb
2 1
2 2
2 3
*/
```

---

## 作者：orz_z (赞：2)

# 题目大意
有 $n$ 个字符串 $S_1, S_2, \cdots, S_n$ 和一个字符串集合 $T$，一开始 $T$ 为空。

然后有两个操作：

1. `1 P` 往 $T$ 里加一个字符串 $P$。
2. `2 x` 询问集合 $T$ 中有多少个字符串包含串 $S_x$ （我们称串 $A$ 包含串 $B$，当且仅当 $B$ 是 $A$ 的子串）。

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，所有字符串的总长 $\le 2 \times 10^6$。

# 解题思路

前置知识：[`AC` 自动机](https://blog.csdn.net/qq_46258139/article/details/119918655)，[树链剖分](https://blog.csdn.net/qq_46258139/article/details/118554607)，树上差分的思想。

~~显然，看到数据范围可以想到肯定不能暴力。~~

首先考虑对 $S_1, S_2, \cdots, S_n$ 建 `AC` 自动机。

~~然后就没思路了。。。~~

但是，往往模拟一遍就会有思路了。

于是，模拟暴力时是怎样对答案进行求和的。

显然，做过模板题的都知道，将串放在 `AC` 自动机上一位一位跑，每跑一位将 `fail` 链上的所有贡献加起来，等等，这是不是似曾相识？？


考虑建 `fail` 树，`fail` 链即是一个点到根节点的简单路径。

现在就要用到树链剖分了。

那树上差分的身影又在哪呢？

可以想到，对串的每一位都求路径和，肯定会炸。

考虑优化，将串的每一位根据 `dfn` 序进行排序。

然后，将每个点贡献加 $1$，相邻两点的 `lca` 贡献减 $1$。

树上差分就有了。

对于每个询问，对串在 `trie` 上结束的节点求一遍子树和就行了。

# AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 2e6 + 7;

int n, m;

int cnt = 1, tr[_][27], fail[_], tag[_];

char c[_];

void insert(char *s, int id)
{
	int p = 1;
	for(int i = 1, len = strlen(s + 1); i <= len; ++i)
	{
		int v = s[i] - 'a';
		if(!tr[p][v]) tr[p][v] = ++cnt;
		p = tr[p][v];
	}
	tag[id] = p;
}

void getfail()
{
	for (int i = 0; i < 26; i ++)
		tr[0][i] = 1;
	queue<int> q;
	q.push(1);
	fail[1] = 0;
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		for(int i = 0; i < 26; ++i)
		{
			if(tr[now][i])
			{
				q.push(tr[now][i]);
				fail[tr[now][i]] = tr[fail[now]][i];
			}
			else
			{
				tr[now][i] = tr[fail[now]][i];
			}
		}
	}
}

int tot, head[_], to[_ << 1], nxt[_ << 1];

void add(int u, int v)
{
	to[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}

int cnt_node, dep[_], siz[_], hson[_], top[_], fa[_], dfn[_];

void dfs1(int u, int d = 1)
{
	dep[u] = d;
	siz[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(dep[v]) continue;
		fa[v] = u;
		dfs1(v, d + 1);
		siz[u] += siz[v];
		if(siz[v] > siz[hson[u]]) hson[u] = v;
	}
}

void dfs2(int u, int topf)
{
	dfn[u] = ++cnt_node;
	top[u] = topf;
	if(!hson[u]) return;
	dfs2(hson[u], topf);
	for(int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if(top[v]) continue;
		dfs2(v, v);
	}
}

int LCA(int u, int v)
{
	while(top[u] != top[v])
	{
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] > dep[v] ? v : u;
}

int k[_];

int lowbit(int x)
{
	return x & -x;
}

void update(int x, int val)
{
	for(int i = x; i <= cnt; i += lowbit(i))
	{
		k[i] += val;
	}
}

int query(int x)
{
	int res = 0;
	for(int i = x; i; i -= lowbit(i))
	{
		res += k[i];
	}
	return res;
}

bool cmp(int x, int y)
{
	return dfn[x] < dfn[y];
}

int q[_];

signed main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", c + 1);
		insert(c, i);
	}
	getfail();
	for(int i = 2; i <= cnt; ++i)
		add(fail[i], i);
	dfs1(1);
	dfs2(1, 1);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i)
	{	
		int op, kkk;
		scanf("%d", &op);
		if(op == 1)
		{
			scanf("%s", c + 1);
			int len = strlen(c + 1);
			for(int j = 1, p = 1; j <= len; ++j)
			{
				int v = c[j] - 'a';
				p = tr[p][v];
				q[j] = p;
			}
			sort(q + 1, q + len + 1, cmp);
			for(int j = 1; j <= len; ++j)
				update(dfn[q[j]], 1);
			for(int j = 1; j < len; ++j) 
				update(dfn[LCA(q[j], q[j + 1])], -1);
		}
		else
		{
			scanf("%d", &kkk);
			int x = tag[kkk];
			printf("%d\n", query(dfn[x] + siz[x] - 1) - query(dfn[x] - 1));
		}
	}
	return 0;
}
```


---

## 作者：Infiltrator (赞：2)

[$\Large\color{#FFBBFF}\textit{Tian-Xing's blog}$](https://Tian-Xing.github.io)

------------

# Description

[传送门](https://www.luogu.com.cn/problem/P5840)

------------

# Solution

~~首先看到这题就想SAM对吧，然后qwaszx写了一发常数太大过不了就果断改AC自动机对吧。~~

考虑对$S$建立$AC$自动机，因为字符串的所有前缀的所有后缀是字符串的所有子串，而$fail$指针指的状态就是该状态的最长可识别后缀，所以在对$S$建好$AC$自动机之后就把插入的字符串扔到$AC$自动机上跑，它能到达的所有状态就是所有的前缀。这样再对每个状态跳所有的$fail$指针就能把该字符串的所有可识别子串在$AC$自动机上找出来了。

所以每次新插入字符串的时候只要在$fail$树上把所有经过的状态到$root$的链都加一，查询的时候查该字符串在$AC$自动机上的位置的值就行了。

直接这样做不大好做，所以考虑树上差分，先把所有的经过的状态都找出来，然后按$dfs$序排序，每次对每个状态单点加，对相邻状态的$lca$单点减。最后查询某个点的时候只需要查询子树和即可。

考虑为什么按照$dfs$序排序，原来的这些点是杂乱无章的，在按$dfs$序排序后就会按照从左往右的顺序依次修改，这样可以保证不重不漏。如果学过虚树的话应该很容易就能理解。

------------

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm> 
#include <queue> 

using namespace std;

const int N = 100000;
const int M = 2000000;

int head[M + 50], num, id[N + 50], tree[M + 50], trie[M + 50][26], cnt, root, top[M + 50], maxson[M + 50], siz[M + 50], dfx[M + 50], dfxx, f[M + 50], dep[M + 50], n, tmp[M + 50], len, fail[M + 50]; 

char st[M + 50];

struct Node
{
	int next, to;
} edge[M + 50];

void Addedge(int u, int v)
{
	edge[++num] = (Node){head[u], v};
	head[u] = num;
	return;
}

void Insert(char st[M + 50], int bh)
{
	int l = strlen(st + 1), now = root;
	for (int i = 1; i <= l; i++)
	{
		int c = st[i] - 'a';
		if (!trie[now][c]) trie[now][c] = ++cnt;
		now = trie[now][c]; 	
	} 
	id[bh] = now;
	return;
}

void Build_AC_auto()
{
	queue<int> q;
	for (int i = 0; i <= 25; i++) if (trie[root][i]) q.push(trie[root][i]);
	while (!q.empty())	
	{
		int u = q.front(); q.pop();
		for (int i = 0; i <= 25; i++)
			if (trie[u][i]) fail[trie[u][i]] = trie[fail[u]][i], q.push(trie[u][i]);
			else trie[u][i] = trie[fail[u]][i];
	}
	return;
}

void Build_Fail_tree()
{
	for (int i = 1; i <= cnt; i++) Addedge(fail[i], i);
	return;
}

void Dfs1(int x)
{
	dfx[x] = ++dfxx; siz[x] = 1;	
	int maxx = 0;
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to; f[v] = x; dep[v] = dep[x] + 1;
		Dfs1(v);
		siz[x] += siz[v];
		if (siz[v] > maxx) maxx = siz[v], maxson[x] = v;
	}
	return;
} 

void Dfs2(int x, int topf)
{
	top[x] = topf;
	if (!maxson[x]) return;
	Dfs2(maxson[x], topf);
	for (int i = head[x]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == maxson[x]) continue;
		Dfs2(v, v);
	} 
	return;
 } 

int Lca(int a, int b)
{
	while (top[a] != top[b])
	{
	//	cout << a << " " << b << endl;
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		a = f[top[a]];	
	}
	return dep[a] < dep[b] ? a : b; 
}

int Lowbit(int x)
{
	return x & (-x);
}

void Add(int pos, int val)
{
	for (int i = pos; i <= cnt + 1; i += Lowbit(i)) tree[i] += val;
	return;
}

int Query(int pos)
{
	int ans = 0;
	for (int i = pos; i; i -= Lowbit(i)) ans += tree[i];
	return ans;
}

int Cmp(int a, int b)
{
	return dfx[a] < dfx[b];
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%s", st + 1), Insert(st, i);
	Build_AC_auto(); Build_Fail_tree(); dep[0] = 1; Dfs1(0); Dfs2(0, 0);
	int q;
	scanf("%d", &q); 
	int opt, ask;
	while (q--)
	{
		scanf("%d", &opt); 
		if (opt == 1)
		{
			scanf("%s", st + 1); len = 0; 
			int now = root, l = strlen(st + 1);
			for (int i = 1; i <= l; i++)
			{
				int c = st[i] - 'a';
				now = trie[now][c];
				tmp[++len] = now;
			}
			sort(tmp + 1, tmp + len + 1, Cmp);
			len = unique(tmp + 1, tmp + len + 1) - tmp - 1;
			for (int i = 1; i <= len; i++)
			{
				Add(dfx[tmp[i]], 1);
				if (i > 1) Add(dfx[Lca(tmp[i], tmp[i - 1])], -1);
			} 
		}
		else
		{
			scanf("%d", &ask);
			printf("%d\n", Query(dfx[id[ask]] + siz[id[ask]] - 1) - Query(dfx[id[ask]] - 1));
		}
	}
	return 0;
} 
```

---

## 作者：蒟蒻君HJT (赞：1)

## 一.题意简述

- 给定 $n$ 个字符串 $S_i,i\in [1,n]$。

- 初始有一个空集 $T$，$q$ 次询问，每次往集合 $T$ 中添加一个字符串 $P_i$，或者给定 $x$，询问当前 $T$ 中有多少个串包含串 $S_x$。

- $n,q\leq 10^5,\sum S_i\leq 2\cdot 10^6,\sum P_i\leq 2\cdot 10^6$。

## 二.解题方法

字符串的多模式匹配问题，一般用 AC 自动机解决。熟悉 AC 自动机的童鞋应该知道，我们可以对所有的 $S$ 串和 $T$ 串建立 AC 自动机。

1. 对于每次新加入 $P_i$ 串，我们就对其在 trie 图上对应的所有节点上都加上（不是染上）一个颜色编号为 $i$。
2. 对于每次询问 $S_x$，即为查询在 fail 树上，以串 $S_x$ 的终止节点为根的子树内部有多少种不同的颜色。

那么问题来了：因为一个串 $S_x$ 若在某个串 $P_i$ 中出现了多次，那么应该只统计一次，而树状数组是无法维护“若出现多次则只统计一次”的操作的。

怎么解决呢？需要换一个思路，我们在每个 fail 树的节点上开一棵线段树来维护子树的信息。具体来说，对于一个线段树的一个底层节点，若它的下标为 $i$，那么他就表示在这棵子树中是否存在串 $P_i$ 在 trie 图上对应的某个节点，存在即为 $1$，不存在即为 $0$。那么对于每个询问，就是在某一个节点对应的线段树上求前缀和。

如何维护这么多棵线段树？可以用线段树合并。首先，在每个节点对应的线段树上加上经过这个节点的所有字符串 $P_i$ 所对应的编号，然后递归计算儿子节点，最后将儿子节点的线段树合并上来。底层节点合并的逻辑运算符应该是“或”而不是运算符“加”，这样就能保证出现多次的串只统计一次了。

merge 函数的代码：( val 数组维护区间和，bin 收集废弃节点） 

```cpp
int merge(int x,int y,int l,int r){
	if(!x || !y) return x|y;
	if(l==r){
    	val[x]=val[x]|val[y];
        bin.push_back(y);
        ls[y]=val[y]=rs[y]=0;
        return x;
    }
	int mid=l+r>>1;
	ls[x]=merge(ls[x],ls[y],l,mid);
	rs[x]=merge(rs[x],rs[y],mid+1,r);
	bin.push_back(y);ls[y]=rs[y]=val[y]=0;
	val[x]=val[ls[x]]+val[rs[x]];
	return x;
}
```
时间复杂度和空间复杂度均为线性对数。但是本题卡线段树合并做法的空间卡的很厉害，所以下面写一下本人使用的常数优化技巧：

1.把所有 STL 容器都删了，尽量手写，实测 vector 额外占用极多空间，当时间卡的不紧的时候用链式前向星代替 vector 存图；

2.**注意，线段树合并有两大类型，需要区分。** 

第一种，无需对每棵线段树都正确维护它的信息，最终的答案在树形结构的根节点上查询就可以了，那么这种情况下，当我们合并线段树节点 $x$ 和 $y$ 时，直接修改 $x$ 的信息（区间和，左儿子，右儿子）即可。

第二种，需要对每棵线段树都正确维护它的信息，查询时每棵线段树都可能用到，那么在每次合并的时候必须新开一个节点 $z$ 表示合并之后的节点，若是直接用 $x$ 的话会造成信息的混乱。

这道题看上去是第二种线段树合并，而这种线段树合并显然是更浪费空间的，那么怎么把它转化成第一种呢？我们可以先读入所有询问，在每个询问所对应的 $S_x$ 终止节点上挂上这个询问，然后在递归进行线段树合并的时候顺便回答掉挂在这个节点上的所有询问，这样的话，这个节点的信息在之后被莫名修改掉也就是一件可以接受的事情了。实际上去掉每次新开节点 $z$ 的空间消耗，可以减小近一半的空间常数。

另外，对于第一种线段树合并，容易发现节点 $y$ 实际上已经没有任何作用，我们可以在废弃它之后将它扔到垃圾桶里**并清空它保存的信息**。以后需要新开节点的时候，先检查有没有废弃掉的节点，没有的话再新申请。实测这也可以大大减小空间消耗量。

在加上以上种种常数优化之后，我们终于可以通过本题了。~~感谢毒瘤出题人。~~

## 三.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e6+5,M=3.2e7+5;
int tr[N][26];
int n,q,fail[N],tot=0,R=0,root[N];
int sum=0,ls[M],rs[M],val[M],ed[100005],Ans[100005];
int head[N],nxt[N],ver[N],gg=0;
int vhead[N],vnxt[N],vver[N],gv=0;
int ghead[N],gnxt[100005],gver[100005],gk=0;
vector<int>bin;
char s[N/2];
int New(){
	int u=bin.size(),v;
	if(u){
		v=bin[u-1];
		bin.pop_back();
		return v;
	}
	return ++sum;
}
void add(int x,int y){
	++gg,nxt[gg]=head[x],head[x]=gg;
	ver[gg]=y;
	return ;
}
void addv(int x,int y){
	++gv,vnxt[gv]=vhead[x],vhead[x]=gv;
	vver[gv]=y;
	return ;
}
void addg(int x,int y){
	++gk,gnxt[gk]=ghead[x],ghead[x]=gk;
	gver[gk]=y;
	return ;
}
void insert(int id){
	int now=0,r=0,l=strlen(s),u;
	while(r<l){
		u=(int)(s[r]-'a');
		if(!tr[now][u]) tr[now][u]=++tot;
		now=tr[now][u],++r;
		if(id>0) addv(now,id);
	}
	if(id<0) ed[-id]=now;
	return ;
}
void build(){
	queue<int>q;
	for(int i=0;i<26;++i) if(tr[0][i]) q.push(tr[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;++i){
			if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
			else tr[u][i]=tr[fail[u]][i];
		}
	}
	return ;
}
int modify(int x,int l,int r,int y){
	if(!x) x=New();
	if(l==r){val[x]=1;return x;}
	int mid=l+r>>1;
	if(y<=mid) ls[x]=modify(ls[x],l,mid,y);
	else rs[x]=modify(rs[x],mid+1,r,y);
	val[x]=val[ls[x]]+val[rs[x]];
	return x;
}
int merge(int x,int y,int l,int r){
	if(!x || !y) return x|y;
	if(l==r){val[x]=val[x]|val[y];bin.push_back(y);ls[y]=val[y]=rs[y]=0;return x;}
	int mid=l+r>>1;
	ls[x]=merge(ls[x],ls[y],l,mid);
	rs[x]=merge(rs[x],rs[y],mid+1,r);
	bin.push_back(y);ls[y]=rs[y]=val[y]=0;
	val[x]=val[ls[x]]+val[rs[x]];
	return x;
}
int ask(int x,int l,int r,int L,int R){
	if(L>R || !x) return 0;
	if(l==L && r==R) return val[x];
	int mid=l+r>>1;
	if(R<=mid) return ask(ls[x],l,mid,L,R);
	else if(L>=mid+1) return ask(rs[x],mid+1,r,L,R);
	return ask(ls[x],l,mid,L,mid)+ask(rs[x],mid+1,r,mid+1,R);
}
int q2[100005];
void dfs(int x){
	for(int i=vhead[x];i;i=vnxt[i]) root[x]=modify(root[x],1,R,vver[i]);
	for(int i=head[x];i;i=nxt[i]) dfs(ver[i]),root[x]=merge(root[x],root[ver[i]],1,R);
	for(int i=ghead[x];i;i=gnxt[i]) Ans[gver[i]]=ask(root[x],1,R,1,q2[gver[i]]);
	return ;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%s",s),insert(-i);
	scanf("%d",&q);
	int x,y;
	for(int i=1;i<=q;++i){
		scanf("%d",&x);
		if(x==1) scanf("%s",s),++R,insert(R);
		else scanf("%d",&y),q2[i-R]=R,addg(ed[y],i-R);
	}
	build();
	for(int i=1;i<=tot;++i) add(fail[i],i);
	dfs(0);
	for(int i=1;i<=q-R;++i) printf("%d\n",Ans[i]);
	return 0;
}
```
写的比较丑陋（卡空间卡的心态崩了），见谅~

---

## 作者：MoYuFang (赞：1)

显然，要将 $S$ 集中的单词插入 Trie 树，这样方便查询编号为 $i$ 的单词的出现次数。

定义失配树上每个节点 $u$ 一个域 $cnt(u)$，为目前 $T$ 中包含该节点对应字符串的个数，这样查询 $T$ 中包含 $S$ 中某单词的字符串的个数就相当于在失配树上单点查询。

然后考虑往 $T$ 集加入字符串 $str$ 时对失配树的影响，这相当于在 AC 自动机上匹配 $str$。在普通 AC 自动机的匹配过程中，每到达一个节点就将该节点到根节点的链上每个节点的 $cnt$ 加 $1$ （指失配树上的路径），相当于前缀链的加操作，这样每个节点可能同时在若干点的前缀链上，它的 $cnt$ 会也被加若干次。

但本题稍微有点不一样，在一次匹配当中，每个 $cnt$ 被加的节点只能加一次。于是，先把匹配中所有经过的点放在 $stk$ （栈）里，栈大小 $top$ 就等于字符串 $str$ 的长度，然后以节点对应的 dfn 序为关键字，对 $stk$ 排序并去重（用 sort 和 unique），去重后 $top$ 可能会减小。

然后

$\forall$ $0 \leq i \leq top - 1$，让 $stk_i$ 到 $rt$ 的前缀链上每个节点的 $cnt$ 加 $1$。

$\forall$ $1 \leq i \leq top - 1$，让 $LCA(stk_i,stk_{i-1})$ 到 $rt$ 的前缀链上每个节点的 $cnt$ 减 $1$。

这样就能保证 $stk_i$ 与 $stk_{i-1}$ 的前缀链的公共链上的每个节点的只被加一次。

代码实现上不是直接前缀链修改和单点查询，这样得用树剖，较慢。

更快的是方法是树上差分，将前缀链修改和单点查询变为单点加与子树和查询，然后用 dfn 序和树状数组维护。

此外，因为算法中求 LCA 的部分仅仅只是求 LCA，可以用欧拉序与 st 表实现 $O(N \log N)$ 预处理，$O(1)$ 查询。

总时间复杂度为 $O(N \log N + M \log M)$，$N$ 为 $S$ 集中字符串总长，$M$ 为 $T$ 集中字符串总长。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ms(x, val) memset(x, val, sizeof(x))
#define _for(i, a, b) for(re int (i) = (a); (i) < (b); ++(i))
#define _rfor(i, a, b) for(re int (i) = (a); (i) <= (b); ++(i))
#define _fev(p, u) for(re int (p) = head[(u)]; (p); (p) = nex[(p)])
#define maxn 2001000
#define lbmaxn 26
#define maxm 2001000
#define maxc 26

template <class T>
void print(string name, T arr[], int n, int flag = 1){
	cout<<name<<":";
	if (flag) _rfor(i, 1, n)cout<<" "<<arr[i];
	else _for(i, 0, n)cout<<" "<<arr[i];
	cout<<endl;
}

char str[maxn];

int 
	//AC 自动机相关 
	ncnt = 1, //Trie 节点数 
	mp[maxn], //S 集中编号为 i 的字符串在 Trie 上对应的节点 
	fail[maxn],
	nxt[maxn][maxc],
	que[maxn],
	
	//失配树图 
	ecnt = 0, 
	head[maxn],  
	to[maxn],
	nex[maxn],
	deep[maxn], 
	
	//dfn 序相关 
	dfn_clock = 0,
	pre[maxn], //dfn 序首 
	pst[maxn], //dfn 序尾 
	ori[maxn], //dfn 序首对应的节点编号 
	
	//树状数组(Fenwick 树) 
	fwk[maxn],
	
	//欧拉序相关 
	euler_clock = 0,
	fir[maxn], //欧拉序首 
	lst[maxn], //欧拉序尾 
	id[2*maxn], //欧拉序首对应的节点 
	
	//st 表相关 
	lb[2*maxn], //以 2 为底的对数 
	st[lbmaxn+2][2*maxn],
	
	//往 T 集中加入字符串时用的 stk 
	stk[maxn];

//在失配树中加边 
inline void add_edge(re int u, re int v){ to[++ecnt] = v, nex[ecnt] = head[u], head[u] = ecnt; }

//在 Trie 中插入 S 集中编号为 i 的字符串 str 
void ins(re char *str, re int i){
	re int u = 1, c;
	while(c = *str++){
		c -= 'a';
		if (!nxt[u][c]) nxt[u][c] = ++ncnt;
		u = nxt[u][c];
	}
	mp[i] = u;
}

//建 fail 
void build(){
	re int fro = 0, bac = 0, u, v;
	fail[1] = 1;
	_for(i, 0, maxc){
		v = nxt[1][i];
		if (v) que[bac++] = v, fail[v] = 1, add_edge(1, v);
		else nxt[1][i] = 1;
	}
	
	while(bac > fro){
		u = que[fro++];
		_for(i, 0, maxc){
			v = nxt[u][i];
			if (v) que[bac++] = v, fail[v] = nxt[fail[u]][i], add_edge(fail[v], v);
			else nxt[u][i] = nxt[fail[u]][i];
		}
	}
}

//求出 dfn 序和欧拉序 
void dfs(int u){
	ori[pre[u] = ++dfn_clock] = u;
	id[fir[u] = ++euler_clock] = u;
	int v;
	_fev(p, u){
		v = to[p];
		deep[v] = deep[u] + 1;
		dfs(v);
		id[++euler_clock] = u;
	}
	pst[u] = dfn_clock;
	lst[u] = euler_clock;
}

//st 表预处理 
void prepare(){
	lb[0] = -1;
	_rfor(i, 1, euler_clock) lb[i] = lb[i>>1]+1;
	_rfor(i, 1, euler_clock) st[0][i] = id[i];
	re int tmp = lb[euler_clock], x, y;
	_rfor(j, 1, tmp){
		_rfor(i, 1, euler_clock + 1 - (1<<j)){
			x = st[j-1][i]; y = st[j-1][i+(1<<(j-1))];
			if (deep[x] <= deep[y]) st[j][i] = x;
			else st[j][i] = y;
		}
	}
	
}

//st 表中查询 
int query(re int l, re int r){
	re int lbl = lb[r-l+1], len = 1<<lbl, x, y;
	x = st[lbl][l]; y = st[lbl][r-len+1];
	if (deep[x] <= deep[y]) return x;
	else return y;
}

int lca(re int x, re int y){
	if (x == y) return x;
	if (fir[x] > fir[y]) x^=y^=x^=y;
	if (lst[x] < fir[y]) return query(lst[x], fir[y]);
	else if (lst[x] > lst[y]) return x;
	else pf("Wrong in lst[x] <= lst[y]\n");
}

//树状数组加与树状数组查询 
void add(re int x, re int val){ for(; x <= dfn_clock; fwk[x] += val, x += (x&(-x))); }
int qry(re int x){ re int val = 0; for(; x; val += fwk[x], x -= (x&(-x))); return val; }

//往 T 集中加入 str
//注意实际上 stk 里装的是节点的 dfn 序首
//ori[dfn 序首] 是对应的节点 
void handle(re char *str){
	re int u = 1, top = 0; stk[top++] = u;
	while(*str) stk[top++] = pre[u = nxt[u][(*str++)-'a']];
	sort(stk, stk+top);
	top = unique(stk, stk+top) - stk;
	re int x, y;
	add(stk[0], 1);
	_for(i, 1, top){
		x = ori[stk[i-1]], y = ori[stk[i]];
		int z = lca(x,y);
		add(pre[y], 1);
		add(pre[lca(x, y)], -1);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	#endif
	
	re int n, m, opt, x;
	sf("%d", &n);
	_rfor(i, 1, n){
		sf("%s", str);
		ins(str, i);
	}
	build();
	deep[1] = 0;
	dfs(1);
	prepare();
	
	sf("%d", &m);
	_rfor(i, 1, m){
		sf("%d", &opt);
		if (opt == 1){
			sf("%s", str);
			handle(str);
		}
		else{
			sf("%d", &x);
			pf("%d\n", qry(pst[mp[x]]) - qry(pre[mp[x]]-1));
		}
	}
	
	return 0;
}


```






---

## 作者：cryozwq (赞：0)

主流做法是虚树思想+树上差分，但事实上，此题的维护可以使用全局平衡二叉树来解决。[不会左转](https://www.luogu.com.cn/blog/nederland/globalbst)。

首先建 fail 树部分不再赘述，考虑我们此时要干什么，对于每个新加入的串在 AC 自动机上匹配，对于每个匹配到的点，把它到 fail 树上的根都加 $1$，但是对于每个串，每个节点最多加 $1$。

树剖直接做是两个 $\log$，但是 GBT 是一个 $\log$。我们考虑 GBT 怎么做。注意到每次修改的链一定会到根，记录每条重链当前这个串被覆盖的最深的点，每次跳重链，就对从最深的点到本来需要覆盖最深的点加 $1$。然后更新被覆盖的最深的点。

区间加 $1$，单点查询，这东西并不难做，区间修打 lazy，查询就一直 push_down，不过由于每个点都真实对应了一个节点，所以并不需要 push_up，修改的时候就跟正常的线段树差不多，唯一需要注意的是如果 GBT 上一个节点管辖范围是 $[l,r]$，但它有且仅有一个儿子，那它其实还有一个儿子 $[l,l]$ 或者 $[r,r]$。要特判。（具体细节可以看代码）

[注意实现细节。](https://www.luogu.com.cn/discuss/418248)

代码：
```cpp
#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int maxn=3.5e6+5; 
char s[maxn];
const int inf=1e8;
bool ff=0;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
template<typename item>
inline void read(register item &x)
{
	ff=1;
    x=0;register char c=getchar();
    while(c<'0'||c>'9'){                               
		if(c=='-')ff=0;
		c=getchar();
	}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(!ff)x=-x;  
}
static char cc[10000];
template<typename item>
inline void print(register item x)
{
	if(x==0){putchar('0');return ;}
	register long long len=0;
	while(x)cc[len++]=x%10+'0',x/=10;
	while(len--)putchar(cc[len]);
}
int mymax(int a,int b){
	return a<b?b:a;
}
struct ACM{
	const int mc=26;
	int pos[maxn];
	struct Edge{
		int v,nxt;
	}e[maxn];
	int h[maxn],cntt=0;
	inline void add(int u,int v){
		e[++cntt].v=v;
		e[cntt].nxt=h[u];
		h[u]=cntt;
	}
	int vc=0;
	int t[maxn];
	int tl[maxn],tr[maxn];
	int CH[maxn][26];
	int sz[maxn],fath[maxn],son[maxn];
	int dfn[maxn],dc=0,ed[maxn],tp[maxn],val[maxn],RT[maxn];
	bool istp[maxn]; 
	int ls[maxn],rs[maxn];
	int bl[maxn];
	void dfs1(int u,int fa){
		sz[u]=1;
		fath[u]=fa;
		for(ri i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa)continue;
			dfs1(v,u);
			sz[u]+=sz[v]; 
			if(sz[son[u]]<sz[v]){
				son[u]=v;
			}
		}
	}
	void dfs2(int u,int fa,int as){ 
		dfn[u]=++dc; 
		bl[dc]=u;
		tp[u]=as;   
		if(u==as){
			istp[u]=1;
		}
		ed[as]=u;
		if(son[u]){
			dfs2(son[u],u,as);  
		} 
		val[u]=1;
		for(ri i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(v==fa||v==son[u])continue;
			val[u]+=sz[v];
			dfs2(v,u,v);		  		
		}
	} 
	int build_SBT(int l,int r,int root){
		if(l>r)return 0;
		int mx=inf,Sum=0,pre=0,rt=l;
		for(int i=l;i<=r;i++){
			Sum+=val[bl[i]];
		}
		for(int i=l;i<=r;i++){
			pre+=val[bl[i]];
			if(mx>mymax(pre,Sum-pre)){
				mx=mymax(pre,Sum-pre);
				rt=i;
			}
		}  
		if(!root){
 			RT[rt]=rt;
			root=rt;
		}
		else{
			RT[rt]=root;
		}
		tl[rt]=l;
		tr[rt]=r; 
		if(l==r)return rt;
		ls[rt]=build_SBT(l,rt-1,root),rs[rt]=build_SBT(rt+1,r,root); 
		return rt;
	}
	int lz[maxn];
	void push_down(int i){
		t[ls[i]]+=lz[i];
		t[rs[i]]+=lz[i]; 
		lz[ls[i]]+=lz[i];
		lz[rs[i]]+=lz[i];
		lz[i]=0;
	}
	void update(int i,int u,int v,int k){
		if(u<=tl[i]&&tr[i]<=v){
			t[i]+=k;
			lz[i]+=k;
			return ;
		}
		push_down(i);
		if(!ls[i]&&!rs[i])return ;
		if(u<=i&&i<=v){
			t[i]+=k;  
		}
		if(u<=tr[ls[i]])update(ls[i],u,v,k);
		if(tl[rs[i]]<=v)update(rs[i],u,v,k);
	}
	int query(int i,int x){
		if(i==x)return t[i];
		push_down(i);
		if(x<=tr[ls[i]])return query(ls[i],x);
		else return query(rs[i],x);
	}
	int fail[maxn],nxt[maxn][26],tot,cnt[maxn],sum[maxn];
	ACM(){
		tot=1;
	}
	void ins(int id,int n){ 
		int u=1; 
		for(ri i=1;i<=n;i++){
			int ch=s[i]-'a';
			if(!nxt[u][ch]){nxt[u][ch]=++tot;CH[u][ch]=tot;}
			u=nxt[u][ch]; 
 		}  
		pos[id]=u;
	} 
	int lstv[maxn],lt[maxn];
	inline void upd(int u){
 		while(u){
			if(lstv[tp[u]]!=vc){
				lstv[tp[u]]=vc;
				lt[tp[u]]=dfn[tp[u]];	
			}
			if(lt[tp[u]]<=dfn[u]){ 
				update(RT[dfn[u]],lt[tp[u]],dfn[u],1);
				lt[tp[u]]=dfn[u]+1;			
			}
			u=fath[tp[u]]; 
		}
		return ;
	}
	inline void solve(int n){  
		++vc; 
		int u=1; 
		for(int i=1;i<=n;i++){
			int ch=s[i]-'a';
			u=nxt[u][ch];
			if(u)upd(u); 
		}   
	}
	queue<int>q;
	void build_GBT(){ 	
		for(ri i=1;i<=tot;i++){
			if(istp[i]){
 				build_SBT(dfn[tp[i]],dfn[ed[i]],0);
			}
		}
	}
	inline void build(){ 
		for(ri i=0;i<mc;i++){
		 	if(!nxt[1][i]){
		 		nxt[1][i]=1;
			}
			else{
			 	q.push(nxt[1][i]);
			 	fail[nxt[1][i]]=1;
			} 
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(ri i=0;i<mc;i++){
				if(nxt[u][i]){
					int v=nxt[u][i];
					if(u==1)fail[v]=1;
					else fail[v]=nxt[fail[u]][i];
					q.push(v);
				} 
				else nxt[u][i]=nxt[fail[u]][i];
			}
		}
		for(ri i=2;i<=tot;i++){  
			add(fail[i],i); 
		}
		dfs1(1,0);
		dfs2(1,0,1);
		build_GBT();
	}  
	inline int qry(int x){ 
		return query(RT[dfn[pos[x]]],dfn[pos[x]]);
	}
}A;
int n,q;
int main(){
 	read(n); 
	int tot2=1;
	for(int i=1;i<=n;i++){
		tot2=1;
		s[tot2]=getchar();
		while(s[tot2]<'a'||s[tot2]>'z')s[tot2]=getchar();
		while(s[tot2]>='a'&&s[tot2]<='z')s[++tot2]=getchar(); 
		A.ins(i,tot2-1);
	}
	A.build();
	read(q); 
	while(q--){
		int op,x;
		read(op);
		if(op==1){
			tot2=1;
			s[tot2]=getchar();
			while(s[tot2]<'a'||s[tot2]>'z')s[tot2]=getchar();
			while(s[tot2]>='a'&&s[tot2]<='z')s[++tot2]=getchar();
			A.solve(tot2-1);
		}
		else{
			read(x);
			print(A.qry(x));
			putchar('\n'); 
		}
	}	
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}

```

---

