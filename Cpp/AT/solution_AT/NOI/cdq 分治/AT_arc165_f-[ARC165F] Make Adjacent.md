# [ARC165F] Make Adjacent

## 题目描述

我们称长度为 $2n$ 的整数序列 $X=(X_1,X_2,\dots,X_{2n})$，如果对于所有 $i=1,2,\dots,n$ 都满足 $X_{2i-1}=X_{2i}$，则称 $X$ 为**良好数列**。

给定一个长度为 $2N$ 的整数序列 $A=(A_1,A_2,\dots,A_{2N})$。该序列包含每个整数 $i=1,2,\dots,N$ 恰好各 $2$ 个。

你可以对 $A$ 进行若干次“交换相邻的两个元素”的操作（可以为 $0$ 次），希望将 $A$ 变为**良好数列**。

设将 $A$ 变为**良好数列**所需的最小操作次数为 $K$。请你输出对 $A$ 进行 $K$ 次操作后，能够得到的**良好数列**中字典序最小的一个，元素之间用空格分隔。

数列的字典序定义如下：设 $S=(S_1,S_2,\ldots,S_{|S|})$，$T=(T_1,T_2,\ldots,T_{|T|})$，则 $S$ 的字典序小于 $T$ 当且仅当满足以下两条之一。这里 $|S|,|T|$ 分别表示 $S,T$ 的长度。

1. $|S|<|T|$ 且 $(S_1,S_2,\ldots,S_{|S|})=(T_1,T_2,\ldots,T_{|S|})$。
2. 存在整数 $1\leq i\leq \min\lbrace |S|,|T| \rbrace$，使得同时满足：
   - $(S_1,S_2,\ldots,S_{i-1})=(T_1,T_2,\ldots,T_{i-1})$；
   - $S_i$ 比 $T_i$ 小（按数值比较）。

## 说明/提示

### 限制条件

- $1\leq N\leq 2\times 10^5$
- $1\leq A_i\leq N$
- 每个整数 $i=1,2,\dots,N$ 在 $A$ 中恰好出现 $2$ 次
- 输入的所有值均为整数

### 样例解释 1

例如，$(3,2,1,2,3,1)\rightarrow (3,2,1,3,2,1)\rightarrow (3,2,3,1,2,1)\rightarrow (3,3,2,1,2,1)\rightarrow (3,3,2,2,1,1)$，这样经过 $4$ 次操作可以将 $A$ 变为**良好数列**，这是所需的最小操作次数。在 $4$ 次操作下，也可以得到 $A=(2,2,3,3,1,1)$，因此答案为 $(2,2,3,3,1,1)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 2 1 2 3 1```

### 输出

```
2 2 3 3 1 1```

## 样例 #2

### 输入

```
3
1 1 2 2 3 3```

### 输出

```
1 1 2 2 3 3```

## 样例 #3

### 输入

```
15
15 12 11 10 5 11 13 2 6 14 3 6 5 14 10 15 1 2 13 9 7 4 9 1 3 8 12 4 8 7```

### 输出

```
11 11 5 5 6 6 10 10 14 14 15 15 2 2 12 12 13 13 1 1 3 3 9 9 4 4 7 7 8 8```

# 题解

## 作者：Arghariza (赞：9)

<https://www.cnblogs.com/Ender32k/p/17712749.html>

记录 $x(1\le x\le n)$ 出现位置分别为 $l_x,r_x(l_x< r_x)$，讨论一下发现当两个数 $x,y$ 满足 $l_x<l_y,r_x<r_y$ 时操作后 $x$ 一定出现在 $y$ 前面，不然可以交换位置以达到更优步数。否则发现无论怎么操作发现都不影响答案。

所以我们将 $x$ 描述为平面上的点 $(l_x,r_x)$，操作为依次在平面上选择一个点删去，且需要满足删去的点左下角没有还没被删的点。直接建图，将 $(l_x,r_x)$ 向所有 $(l_y,r_y),l_x<l_y,r_x<r_y$ 连边，跑字典序最小拓扑序就是最优解。

但是这样边数是 $O(n^2)$ 的，注意到点数 $O(n)$，考虑优化建图。

按照 $l_x$ 从大到小扫描线，每次相当于对于一个 $r_i$ 排序后的后缀连边。这样的连边是一段区间，可以线段树优化建图，线段树建立在 $r$ 序列上。

但是 $l_x$ 向左移动时会插入新的 $r_x$，为了让上一时刻的连边不包含新插入的 $r_x$，需要可持久化。

复杂度 $O(n\log n)$。

```cpp
// Problem: F - Make Adjacent
// Contest: AtCoder - AtCoder Regular Contest 165
// URL: https://atcoder.jp/contests/arc165/tasks/arc165_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 4e5 + 400;

pi p[N];
int n, tot, rt, a[N], in[N << 5], rp[N];
vector<int> g[N << 5], ans;

struct seg { int lc, rc; } tr[N << 5];

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)

void add_edge(int u, int v) { if (u && v) g[u].pb(v), in[v]++; }
void add(int l, int r, int p, int q, int y, int &x) {
	tr[x = ++tot] = tr[y];
//	wr(tot), pc('\n');
	if (l == r) return add_edge(x, q);
	if (p <= mid) add(l, mid, p, q, tr[y].lc, ls);
	else add(mid + 1, r, p, q, tr[y].rc, rs);
	add_edge(x, ls), add_edge(x, rs);
}

void upd(int l, int r, int s, int t, int p, int x) {
	if (!x) return;
	if (s <= l && r <= t) return add_edge(p, x);
	if (s <= mid) upd(l, mid, s, t, p, ls);
	if (t > mid) upd(mid + 1, r, s, t, p, rs);
}

priority_queue<pi, vector<pi>, greater<pi> > q;

void topo() {
	for (int i = 1; i <= tot; i++)
		if (!in[i]) q.push(mp((i <= n ? i : 0), i));
	while (!q.empty()) {
		pi p = q.top(); q.pop();
		int u = p.se;
		if (u <= n) ans.pb(u);
		for (int v : g[u]) {
			in[v]--;
			if (!in[v]) q.push(mp((v <= n ? v : 0), v));
		}
	}
}

int main() {
//	freopen("A.in", "r", stdin);
//	freopen("A.out", "w", stdout);
	n = tot = rd();
	for (int i = 1; i <= (n << 1); i++) {
		a[i] = rd();
		if (!p[a[i]].fi) p[a[i]].fi = i;
		else p[a[i]].se = i;
	}
	for (int i = 1; i <= n; i++) rp[p[i].fi] = p[i].se;
	for (int i = (n << 1); i; i--) {
		if (!rp[i]) continue;
		upd(1, (n << 1), rp[i], (n << 1), a[i], rt);
		add(1, (n << 1), rp[i], a[i], rt, rt);
	}
	topo();
	for (int i : ans) 
		wr(i), pc(' '), wr(i), pc(' ');
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：6)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc165_f)

**题目大意**

> 给定 $a_1\sim a_{2n}$，其中 $1\sim n$ 每个出现 $2$ 次，交换尽可能少的相邻元素使得所有 $a_{2i}=a_{2i-1}$，在这个基础上求出字典序最小的 $a_i$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

考虑 $n=2$ 的情况，那么本质不同的初始序列只可能是 $0011,0101,0110$，其中前两种都必须变成 $0011$，第三种可以变成 $0011/1100$。

类似推广，$a_{l_i}=a_{r_i}=i(l_i<r_i)$，那么最终排列 $i$ 必须在 $j$ 前面当且仅当 $l_i<l_j,r_i<r_j$。

那么我们可以 CDQ 分治优化建图，原问题变成求最小拓扑序（带虚点）。

那么把 $1\sim n$ 用优先队列维护，每次取出最小的点，对于其他虚点用一个普通队列维护，每次优先处理虚点即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
vector <int> G[MAXN*18];
int deg[MAXN*18];
void link(int x,int y) { G[x].push_back(y),++deg[y]; }
int n,tot,L[MAXN],R[MAXN],a[MAXN];
void solve(int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	int hd=tot-mid;
	link(hd+r,a[r]);
	for(int i=r-1;i>mid;--i) link(hd+i,hd+i+1),link(hd+i,a[i]);
	for(int i=l,j=mid+1;i<=mid;++i) {
		while(j<=r&&R[a[i]]>R[a[j]]) ++j;
		if(j<=r) link(a[i],hd+j);
	}
	tot=hd+r;
	inplace_merge(a+l,a+mid+1,a+r+1,[&](int x,int y){ return R[x]<R[y]; });
}
signed main() {
	scanf("%d",&n),tot=n;
	for(int i=1,x;i<=2*n;++i) {
		scanf("%d",&x),(L[x]?R:L)[x]=i;
	}
	iota(a+1,a+n+1,1);
	sort(a+1,a+n+1,[&](int x,int y){ return L[x]<L[y]; });
	solve(1,n);
	priority_queue <int,vector<int>,greater<int>> q;
	queue <int> q0;
	vector <int> ans;
	for(int i=1;i<=tot;++i) if(!deg[i]) {
	    if(i<=n) q.push(i);
	    else q0.push(i);
	}
	while(q.size()||q0.size()) {
		int u;
		if(q0.size()) u=q0.front(),q0.pop();
		else u=q.top(),q.pop(),printf("%d %d",u,u);
		for(int v:G[u]) if(!--deg[v]) {
		    if(v<=n) q.push(v);
		    else q0.push(v);
		}
	}
	puts("");
	return 0;
}
```

---

## 作者：Lyrella (赞：5)

# 前言

$2024.10.19$ 日校测 $T4$，思维太庙，被薄纱了，遂哭弱，写题解以记之。

# 简要题意

给你一个长度为 $2n$ 的序列满足 $\forall a_i\in[1,n]$，其中 $1$ 到 $n$ 每个数都出现了两次，现在需要把相同的两个数排到一起，每次操作只能交换相邻两个数，在**保证操作次数最小**的情况下求出现在序列的**最小字典序**。

数据范围：$1\le n\le2\times10^5$。

# 思路

做题的时候首先应该考虑题目性质，可以从手玩样例开始。因为最后并没有让你求最少操作次数，所以我们只用讨论**数与数之间的关系**。我们考虑最简单的情况：假设现在序列中只有 $1$ 和 $2$ 各两个，一共存在六种可能的情况。我们先将他们列出来：

1. $1122$
2. $1212$
3. $1221$
4. $2112$
5. $2121$
6. $2211$

对于第一种和第六种情况我们可以不用考虑，因为需要保证操作数最小。然后这四种情况实际只有两种**本质不同**，我们将他们抓出来。假设有两数 $A,B$ 位置关系如下：

- $ABAB$
- $ABBA$

对于第一个情况，我们只需将中间两数交换即可。而第二种，我们既可以将第一个数交换到第三个位置，也可以将最后一个数交换到第二个位置。也就是说：第一种情况下数的位置决定最后顺序；而第二种情况下数的大小决定了最后顺序。

现在考虑扩展这两种情况，对于数列中任意的两数 $A,B$，如果满足 $A\dots B\dots A\dots B$ 的形式，我**一定**会让 $A$ 排在 $B$ 前面；如果满足 $A\dots B\dots B\dots A$ 的形式，我就会去考虑两个数之间的大小关系。

总结一下：

$\forall x\in[1,n]$，设 $a_x$ 表示其第一次出现的位置，$b_x$ 表示第二次出现的位置，如满足偏序：$a_i\le a_j,b_i\le b_j$ 则 $i$ 在 $j$ 之前。所以把这些偏序抽象成一张图跑拓扑排序，拓扑时让数字小的点尽量先跑就能满足第二种情况。

可是直接建图跑是 $O(n^2)$ 的，考虑优化。我们把每一个关于 $i$ 的二元组 $(a_i,b_i)$ 看成平面内的点，若 $i,j$ 之间连边则需要满足上述偏序。我们可以考虑分治建图，也就是类似 $\text{cdq}$ 的过程，具体见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8v5imgob.png)

我们横着切一刀把平面分成两部分，在分割线上建一些虚点。对于下面的实点垂直向上连边，上面的实点从下面虚点往上连边，然后虚点之间从左往右连。若每次在中间切最多切出 $\log n$ 层，所以只有 $n\log n$ 个点和边。但是拓扑的时候如果用优先队列是两只 $\log$ 的，考虑继续优化。

其实我们只需要对实点用优先队列，对于虚点我们不关心他们的具体顺序，所以开一个普通队列存虚点，另一个优先队列存实点，每次先把所有普通队列的点拓扑完再去拓扑优先队列就行。时间复杂度是 $O(n\log n)$ 的，因为实点只有 $n$ 个。

# 代码

```cpp
void cdq(int l, int r){
	if(l == r)return; int mid = l + r >> 1, lim = a[mid].l;
	cdq(l, mid), cdq(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while(i <= mid and j <= r)a[i].r < a[j].r ? b[k++] = a[i++] : b[k++] = a[j++];
	while(i <= mid)b[k++] = a[i++]; while(j <= r)b[k++] = a[j++];
	for(int i = l; i <= r; ++i){
		a[i] = b[i], ++nd; if(i ^ l)e[nd - 1].pb(nd), ++in[nd];
		if(a[i].l <= lim)e[a[i].id].pb(nd), ++in[nd];
		else e[nd].pb(a[i].id), ++in[a[i].id];
	}
}
void upd(int x){
	if(in[x])return;
	x <= n ? q.push(x) : qc.push(x);
}

signed main(){
	freopen("swap.in", "r", stdin);
	freopen("swap.out", "w", stdout);
	n = rd(), nd = n << 1;
	for(int i = 1; i <= nd; ++i){
		int x = rd();
		if(a[x].l)a[x].r = i; else a[x].l = i, a[x].id = x;
	}
	sort(a + 1, a + 1 + n); nd = n;
	cdq(1, n);
	for(int i = 1; i <= nd; ++i)upd(i);
	while(! q.empty() or ! qc.empty()){
		while(! qc.empty()){
			int u = qc.front(); qc.pop();
			for(int v : e[u])--in[v], upd(v);
		}
		if(q.empty())return 0;
		int u = q.top(); q.pop();
		pc(u), putchar(' '), pc(u), putchar(' ');
		for(int v : e[u])--in[v], upd(v);
	}
	return 0;
}
```

---

## 作者：K_srh (赞：4)

**“调整”思想好题！**

题目大意：要求将给定的序列通过邻项交换用最小的操作数量使两两相同这样排列，第二关键字是字典序。

我们可以讨论一下两对数的相互位置关系，看看什么情况下把哪个放在前面更优。

举个例子：两对数 $1,2$ 一共有三种相对关系。

$1,1,2,2$

$1,2,1,2$

$1,2,2,1$

考虑第一种和第二种，此时把 $1,1$ 放在 $2,2$ 前面交换次数一定比把 $2,2$ 放在 $1,1$ 前面所使用交换次数更少，所以我们最终也一定会如此操作，而对于第三种情况 $2,2$ 放在前面和 $1,1$ 放在前面用到次数相同，也就是说我们可以任意选一个放在前面，此时若无其他条件影响就优先考虑字典序，我们设 $l_i,r_i$ 分别为每个数字第一个出现的位置和第二个出现的位置，第一二种情况可用 $l_i \le l_j,r_i \le r_j$ 的条件描述，也就是说遇到这样的一对数，$i$ 纵使放在 $j$ 前面，不然一定可以调整策略 $i$ 放在 $j$ 来优化次数。

对于这样的选一个之前先选其他一些东西的问题不难想到拓扑，我们建好图跑字典序最小拓扑序即可。

但是这样建图边数是 $O(n^2)$,偏序结构我们可以使用 cdq 分治优化建图，先按照 $l$ 排序，每次相当于向一个 $r$ 排序后的后缀连边，我们新建一条链把右边点串起来，然后由左边向右边第一个位置连边即可优化边数。

边数点数都是 $O(n\log n)$，直接跑拓扑排序是两个 $\log$，实上我们并不在乎 cdq 过程中新建的虚点的顺序，所以可以用一个队列维护虚点，每次优先取队列内元素，再取优先队列内元素，即可做到 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+9,M=8e6+9;
int n,a[N],ll[N],rr[N];
struct Node
{
    int l,r,id;
}b[N];
bool cmp(Node x,Node y){return x.l<y.l;}
int deg[M];
struct Edge{
    int nxt,to;
}edge[M<<1];
int head[M],edge_cnt=0;
void Add_edge(int u,int v)
{
	edge[++edge_cnt].to=v;
	edge[edge_cnt].nxt=head[u];
    head[u]=edge_cnt;
    deg[v]++;
}
int ncnt;
int qwq[N];
Node fz[N];
void work(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)/2;
    work(l,mid);
    work(mid+1,r);
    for(int i=mid+1;i<=r;i++)
    {
        ncnt++;
        qwq[i]=ncnt;
        Add_edge(ncnt,b[i].id);
    }
    for(int i=mid+1;i<r;i++) Add_edge(qwq[i],qwq[i+1]);
    for(int i=l,j=mid+1;i<=mid;i++)
    {
        while(j<r&&b[i].r>b[j].r) j++;
        if(b[i].r<b[j].r)Add_edge(b[i].id,qwq[j]);
    }
    int pos1=l,pos2=mid+1;
    for(int i=l;i<=r;i++)
    {
        int pd=0;
        if(pos2==r+1) pd=1;
        else if(pos1==mid+1) pd=2;
        else pd=(b[pos1].r<b[pos2].r?1:2);
        if(pd==1) fz[i]=b[pos1++];
        else fz[i]=b[pos2++];
    }
    for(int i=l;i<=r;i++) b[i]=fz[i];
}
int ans[N],p[N];
priority_queue<int> pq;
queue<int> q;
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*2;i++)
    {
        scanf("%d",&a[i]);
        if(ll[a[i]]==0) ll[a[i]]=i;
        else rr[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
    {
        b[i].l=ll[i];
        b[i].r=rr[i];
        b[i].id=i;
    }
    ncnt=n;
    sort(b+1,b+n+1,cmp);
    work(1,n);
    for(int i=1;i<=ncnt;i++)
    {
		if(deg[i]==0)
		{
		    if(i<=n) pq.push(-i);
		    else q.push(i);
		}    	
	}
    while(!pq.empty()||!q.empty())
    {
        int nw;
        if(q.empty()) nw=pq.top(),pq.pop();
        else nw=q.front(),q.pop();
        if(nw<0) nw=-nw,ans[++ans[0]]=nw;
        for(int i=head[nw];i;i=edge[i].nxt)
        {
            int v=edge[i].to;
            deg[v]--;
            if(deg[v]==0)
            {
                if(v<=n) pq.push(-v);
                else q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++) printf("%d %d ",ans[i],ans[i]);
    return 0;
}
```

---

## 作者：tobie (赞：3)

场切铜牌题，纪念一下。

首先根据经典结论，操作数等于逆序对数。

考虑两种数对逆序对造成的贡献：两种数的位置关系有三种情况：

```
1. AABB
2. ABAB
3. ABBA
```

我们发现，这三种情况里，前两种情况中 AB 顺序如果是正序，则逆序对数量较小；而第三种情况逆序对数量和 AB 顺序无关。

那假如我们能让所有前两种情况的 AB 都满足顺序关系，那就能让最终答案取到最小值。

刻画一下条件，以下记 $L_i$ 表示 $i$ 出现位置中靠左的位置，$R_i$ 表示靠右的：

> 若 $L_i<L_j$ 并且 $R_i<R_j$，则 $i$ 要在 $j$ 之前出现。

发现这是一个二维偏序关系，所以如果我们能把拓扑图建出来，使用优先队列维护就能得到答案。

但是直接建图是 $O(n^2)$ 的，所以我们可以使用 CDQ 分治优化，取分治中心后，左边的点要往右边点的一个后缀连边，所以新建一条链把右边点串起来然后双指针优化即可。这样边数和点数都是 $O(n\log n)$。

直接跑最小字典拓扑序即可做到 $O(n\log^2 n)$。但是我们发现，事实上我们并不在乎 CDQ 过程中新建的虚点的顺序，所以可以用一个队列维护虚点，每次优先取队列内元素就能做到 $O(n\log n)$。

[submission](https://atcoder.jp/contests/arc165/submissions/57468106)

---

## 作者：BINYU (赞：3)

## 题意

给定一个长度为 $2n$ 的数组 $a$，$1$ 至 $n$ 分别出现两次，我们每次操作可以交换一次相邻两个位置的数，最后使得对于 $\forall i \in [1,n]$，有 $a_{2i} = a_{2i+1}$。求在满足操作数最小的情况下，字典序最小的结束序列。

## 思路

先考虑 $n = 2$ 的情况，共有一下 $3$ 种本质不同初始数组：

$a,a,b,b$ 

$a,b,a,b$ 

$a,b,b,a$

对于第一种情况，不换肯定最优。

对于第二种情况，交换第二个 $a$ 和第一个 $b$ 最优。

对于第三种情况，可以把第二个 $b$ 换到最前，也可以把第一个 $b$ 换到最后。

推广到 $n$ 任意的情况，可以发现，定义长度为 $n$ 的两个数组 $L$ 和 $R$ 表示第 $i$ 个数第 $1$ 次和第 $2$ 次出现的位置，若对于 $i$ 和 $j$ 有 $L_i < L_j$ 且 $R_i < R_j$，则在最终数组中，$i$ 一定在 $j$ 前面。

证明：

把操作分为两步：
1. 把 $L_i$，$L_j$，$R_i$，$R_j$ 挪到目标位置（可以乱序）
2. 换他们之间的顺序

第一步一定是不在上述四个数之间作交换最优，第二步的策略和 $n = 2$ 时的策略没有差别。

得证。

考虑建图，对于每一对 $(i,j)$，如果满足 $L_i < L_j$ 且 $R_i < R_j$，则从 $i$ 向 $j$ 连接一条边，最后求整个图的最小拓扑序即可。

但是边数最高可以达到 $O(n^2)$ 的级别，时空上都不能接受。

考虑优化，发现有很多边是对整个拓扑序是没有贡献的，如 $i$ 连了 $j$，$j$ 又连了 $k$，则 $i$ 和 $k$ 之间的边就是多余的。

发现本问题是一个类似于二维偏序的问题，在处理该类问题的算法中，能够最好的获取实时信息（因为需要建边）的算法无疑是归并排序，考虑往这方面去想。

考虑先以 $L$ 为关键字进行一次排序，之后以 $R$ 为关键字进行排序，在每次归并中，需要加的边实际上就是在后半段有数加入新数组时，前半段的所有加入了的点都要向它连一条边，时空还是 $O(n^2)$ 级别的，考虑继续优化。

发现对于每一条限制，如果现在排序的区域为 $l$ 至 $r$，前半段的下标为 $i$ 的点对后半段的下标为 $j$ 的点连边，那么下表在 $l$ 至 $i$ 中的的所有点都将对下表在 $j$ 至 $r$ 中的的所有点连边，因为前半段的点的 $L$ 一定小于后半段的点，先加入新数组的点的 $R$ 一定小于后加入的点，两个条件同时满足，就一定会有连边，考虑用更少的边去代表这些边。

我们可以在每次归并的过程中，用 $r - l + 1$ 个新点来表示原来的点。

对于前半段的点，我们让旧点连向新点，代表只有旧点已经放入答案中了，新点所代表的限制才能解除，同时对每一个点代表的新点连向后一个个新点，代表如果后一个点限制其他的点，前一个点也必然会产生同样的限制。

对于后半段的点，我们让新点连向旧点，代表只有新点所代表的限制已经解除，旧点点才能放入答案中，同时对每一个点代表的新点连向后一个个新点，代表如果前一个点被限制，后一个点也必然被限制。

此时新点之间的限制并不会影响旧点，因为如果前一个新点的限制解除了，后一个新点没有额外限制，它的限制也会相应的解除，旧点之间将存在一个同时入度为 $0$ 的时刻，不会产生额外的错误限制。

这样总点数和总边数都是 $O(n \log n)$ 量级的，时间复杂度 $O(n\log n)$

在进行拓扑排序的时候，优先考虑新点，将最初的 $n$ 个点“解放”出来，如果没有新点入度为 $0$，再考虑旧点。

我们可以对新点建一个队列（不用考虑字典序），旧点建一个优先队列（要考虑字典序），时间复杂度 $O(n\log n)$。

总时间复杂度 $O(n\log n)$，可过。

---

## 作者：鲤鱼江 (赞：2)

看了题解感觉比较简单但不看就是不会，这也许就是思维题的魅力吧？

设 $v$ 出现位置为 $l_v,r_v(l_v<r_v)$。

对于 $x,y$，若 $l_x<l_y,r_x<r_y$，则 $x$ 在 $y$ 前面一定更优，否则 $x,y$ 不论怎样都不影响答案，手摸一下发现显然。

那么我们现在就得到了若干偏序关系，如果直接把图建出来，跑一遍优先队列拓扑排序就做完了，但是偏序关系有 $O(n^2)$ 所以不能这么干！

可以使用 CDQ 分治+建虚点，再跑优先队列拓扑排序。

建了 $O(n\log n)$ 边，所以复杂度不会高于 $O(n\log^2 n)$。

具体地，我们发现虚点的顺序我们是不关心的，所以存一个普通队列装虚点，一个优先队列来存真实点，每次普通队列空了之后再从优先队列里取点。

话说其实该用 set 而不是优先队列？

```cpp
#include<bits/stdc++.h>

using namespace std;

bool st;
const int N=5e5+10;
struct node{int id,pos,y;}a[N];
int val[N],L[N],n,ins[N<<5],tot,id[N],idx;
vector < int > v[N<<5],ans;
queue < int > Q;set < int > S;
bool ed;

inline void add(int x,int y){v[x].emplace_back(y);++ins[y];}
inline void Push(int x){
	if(x<=n) S.emplace(x);
	else Q.push(x);
}

void CDQ(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;CDQ(l,mid);CDQ(mid+1,r);
	inplace_merge(a+l,a+mid+1,a+r+1,[](const node x,const node y){return x.y<y.y;});
	++tot;
	for(int i=r;i>=l;--i){
		if(a[i].pos>mid){++tot;add(tot,tot-1);add(tot,a[i].id);}
		else add(a[i].id,tot);
	}
}

inline void Sort(){
//	cerr<<"AT\n";
//	cout<<tot<<endl;
	for(int i=1;i<=tot;++i) if(!ins[i]) Push(i);
	while(!S.empty()||!Q.empty()){
		int x;
		if(!Q.empty()){x=Q.front();Q.pop();}
		else {x=*S.begin();S.erase(x);ans.emplace_back(x);}
//		cout<<x<<endl;
		for(int i:v[x]) if(!--ins[i]) Push(i);
	}
	for(int i:ans) cout<<i<<' '<<i<<' ';
}

int main(){
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;tot=n+1;
	for(int i=1;i<=(n<<1);++i){
		cin>>val[i];
		if(!L[val[i]]) L[val[i]]=i,id[i]=++idx;
		else{
			int to=id[L[val[i]]];
			a[to].id=val[i];a[to].y=i;a[to].pos=to;
		}
	}
//	cerr<<"-----\n";
//	for(int i=1;i<=n;++i) cout<<a[i].id<<' '<<a[i].y<<endl; 
//	cerr<<"-----\n";
	CDQ(1,n);Sort();
//	cerr<<endl<<(&st-&ed)/1048576.0<<endl;
	return 0;
}
```

---

## 作者：taozhiming (赞：1)

## arc165F

### 题目描述：

给定 $n$ 和一个长度为 $2n$ 的序列 $a$，满足 $[1,n]$ 每个数恰好出现两次。

每一次操作可以交换相邻的两个数，询问最少多少次操作可以使得序列 $a$ 满足 $\forall i\in[1,n]\ a_{2\times i}=a_{2\times i+1}$。

在保证为最小操作次数的前提下，输出所有可以得到序列中字典序最小的那一个。

对于 $100\%$ 的数据，满足：$1≤n≤2×10^5$。

### 题目分析：

先不考虑字典序最小，考虑操作数最小怎么得到。

若只有两个数，那么可能出现的情况只有两种：$1221$ 和 $1212$。

显然第一个变成 $1122$ 和 $2211$ 的操作数最小，第二个变成 $1122$ 的操作数最小。

扩展一下，对于一个数 $i$，第一次出现的位置记为 $l_i$，第二次出现的位置记为 $r_i$。

那么对于任意的 $i,j$，满足 $l_i<l_j$ 并且 $r_i<r_j$，那么就让 $i$ 向 $j$ 连边，最后求一个最小拓扑序即可。

发现边的个数是 $n^2$ 的，考虑怎么优化建图：

如果只有一维，即只有 $l_i<l_j$，可以直接排序后前缀优化建图。

但是现在有两维，分治把第一维给去掉，这样就可以 $O(n\log n)$ 建图并且求解了。

### 代码：

[代码在这里](https://www.cnblogs.com/taozhiming/p/17719173.html)

---

## 作者：ChickyHas (赞：0)

很考验图论建模能力的题，不愧是铜牌题！

我们仅仅考虑两种数 $i$ 和 $j$ 的相对顺序，设他们的位置为 $i_1,i_2,j_1,j_2$ 如果 $i_2 < j_1$，那么我们肯定不会交换，且 $i$ 一定会在 $j$ 前面，如果 $i_1<j_1<i_2<j_2$ 那么肯定是会交换一次，然后还是 $i$ 一定在 $j$ 前面，那如果是包含关系，即 $i_1 < j_1 < j_2 < i_2$ 那么我们这个怎么搞都需要两次操作，但是我们可以任意调换 $i$ 和 $j$ 的顺序。

我们可以把所有这样的限制在图上建出来，那么我们只需要找最小的拓扑序即可。

然而这样的限制枚举有 $O(n^2)$，我们怎么优化呢？

用 cdq 分治就可以了！

具体而言，就是记录一个数出现的两个位置，按第二次出现的位置进行 cdq 分治，每次从后往前扫，发现第一次也在右边的，就可以建一个虚点连着表示偏序关系了，具体而言就是后面来的点都要在他前面。

复杂度应该是 $O(n\log^2 n)$

---

