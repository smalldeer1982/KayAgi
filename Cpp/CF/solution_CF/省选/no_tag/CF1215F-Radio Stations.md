# Radio Stations

## 题目描述

除了关于照明的投诉外，Bertown 市政厅最近还收到了大量关于无线电信号覆盖不足的投诉。市长收到了 $n$ 份投诉，这些投诉内容惊人地相似：在第 $i$ 份投诉中，一位无线电爱好者提到，两个无线电台 $x_i$ 和 $y_i$ 的信号未能覆盖城市的某些区域，并要求至少有一个电台的信号能够覆盖整个城市。

当然，Bertown 的市长正在努力解决这些投诉。市里新安装了一座无线电塔，可以发射任意整数功率 $1$ 到 $M$（我们用 $f$ 表示信号功率）。市长决定选择一些无线电台，并与每个被选中的电台签订合同。要与第 $i$ 个电台签订合同，需满足以下条件：

- 信号功率 $f$ 不小于 $l_i$，否则第 $i$ 个电台的信号无法覆盖全城；
- 信号功率 $f$ 不大于 $r_i$，否则信号会被未与第 $i$ 个电台签约的其他城镇居民接收到。

这些信息已经让市长意识到选择电台的难度。但在咨询专家后，他得知有些电台之间的信号会互相干扰：有 $m$ 对电台（$u_i$，$v_i$）使用相同的信号频率，对于每一对，无法同时与这两台电台签订合同。如果电台 $x$ 和 $y$ 使用相同频率，$y$ 和 $z$ 也使用相同频率，并不意味着 $x$ 和 $z$ 也使用相同频率。

市长觉得分析这个问题非常困难，于是雇佣了你来帮忙。你需要选择一个信号功率 $f$ 和一组电台签约，使得：

- 所有投诉都被满足（即对于每个 $i \in [1, n]$，城市至少与电台 $x_i$ 或 $y_i$ 中的一个签约）；
- 选中的电台之间没有互相干扰（即对于每个 $i \in [1, m]$，城市不会同时与 $u_i$ 和 $v_i$ 签约）；
- 对于每个被选中的电台，信号功率 $f$ 满足其要求（即对于每个被选中的电台 $i$，有 $l_i \leq f \leq r_i$）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4 4 2
1 3
2 3
1 4
1 2
3 4
1 4
1 2
3 4
```

### 输出

```
2 3
1 3 ```

## 样例 #2

### 输入

```
2 4 4 2
1 3
2 4
1 2
1 2
3 4
3 4
1 2
3 4
```

### 输出

```
-1
```

# 题解

## 作者：Sooke (赞：38)

### 简要题意

有 $n$ 个电台，第 $i$ 个电台频段在 $[l_i,\,r_i]$ 。由你在 $[1,\,m]$ 中选择主频 $f$ ，如果 $f \in [l_i,\,r_i]$ ，第 $i$ 个电台你可选择是否启用，否则无法启用。

有若干组限制形如 $u$ 和 $v$ 必须启用至少一个，或不可同时启用。请给出 $f$ 并构造电台的启用方案。无解输出 $-1$ 。

---

### 前置知识

$\text{2 - SAT}$ 。[模板题链接](https://www.luogu.org/problem/P4782) 。至于这道题，虽然明显地指示出了这类问题，但是建模是前所未有的神仙！

---

### 解题思路

按照 $\text{2 - SAT}$ 的套路，我们把一个对象拆成两个点分别表示选和不选。

于是我们掏出 $2n$ 个点，来描述 $n$ 个电台的启用方案。

但最重要的考点，还是建模。

下文用 $\text{yes}(u)$ 表示表示对象 $u$ 选的点，$\text{no}(u)$ 表示对象 $u$ 不选的点。

首先来热一热身，“若干组限制形如电台 $u$ 和电台 $v$ 必须启用至少一个”怎么在 $\text{2 - SAT}$ 中表示呢？

回忆一下，既然点表示选或不选，那么条件 $u$ 往条件 $v$ 连一条有向边表示只要条件 $u$ 满足，条件 $v$ 就必须满足。

因此，我们只要像下面一样连边：

![](https://i.loli.net/2019/09/16/6wek2Vd3sMmDFJH.png)

即：$\text{no}(u) \rightarrow \text{yes}(v),\ \text{no}(v) \rightarrow \text{yes}(u)$ 。

理由很简单。当 $u$ 不选时，如果 $v$ 还不选的话，就不满足限制了，这意味着 $v$ 不得不选。反过来亦然。

下一个热身任务：若干组限制形如电台 $u$ 和电台 $v$ 不可同时启用。

连边方式异曲同工：

![](https://i.loli.net/2019/09/16/vR9NFuSekpByOAd.png)

即：$\text{yes}(u) \rightarrow \text{no}(v),\ \text{yes}(v) \rightarrow \text{no}(u)$ 。

理由也类似。当 $u$ 选，$v$ 必须不能选，否则违反限制。反过来亦然。

热身结束。真正振奋人心的建模这才到来：如何制定唯一的 $f$ ，并表示出因为 $f \notin [l_i,\,r_i]$ ，$i$ 号电台不允许启用？

线段树优化建边？太慢！太繁琐！我们需要**前缀和的思想**！试试把区间 $[l,\,r]$ 拆成 $[1,\,l-1]$ 和 $[1,\,r]$ 来讨论。

列出以下表格：

||||
|:-:|:-:|:-:|
|$\quad f\in [1,\,l_i - 1]\quad $|$\quad f\in [1,\,r_i]\quad $|$\quad $电台 $i$ 能否启用$\quad $|
|$\text{no}$|$\text{no}$|$\text{no}$ ，此时 $f > r_i$|
|$\text{no}$|$\text{yes}$|没有限制，此时 $f \in [l_i,\,r_i]$|
|$\text{yes}$|$\text{yes}$|$\text{no}$ ，此时 $f < l_i$|
|$\text{yes}$|$\text{no}$|不存在 ，$f \in \varnothing$|

据此，提取出三个重要限制：

- 若电台 $i$ 启用，$f \in [l_i,\,r_i]$ 。

- 若 $f \in [1,\,l_i-1]$ 满足，电台 $i$ 无法启用。

- 若 $f \in [1,\,r_i]$ 不满足，电台 $i$ 无法启用。


与此同时，我们发现仅凭目前的 $2n$ 个点，不足以表示出上面的限制。

于是我们再掏出 $2(m+1)$ 个点，分别表示对于 $i = 0 \dots m$ ，$[f \le i]$ 满足或不满足。例如，用 $\text{yes}(n + i + 1)$ 表示 $f \le i$ ，用 $\text{no}(n + i + 1)$ 表示 $f > i$ 。

它们之间的连边如下：

![](https://i.loli.net/2019/09/16/b4kYHJQa1t2938n.png)

即：$\text{yes}(n+i+1) \rightarrow \text{yes}(n+i+2),\ \text{no}(n+i+2) \rightarrow \text{no}(n+i+1)$ 。

解释：$f \le i$ 满足时，$f \le i + 1$ 必然满足。$f \le i + 1$ 不满足时，即 $f \ge i + 1$ 满足时，$f \le i$ 必然不满足。

至此，我们终于准备在两类对象之间连边了！

复读一遍那三个限制：

- 若电台 $i$ 启用，$f \in [l_i,\,r_i]$ 。

- 若 $f \in [1,\,l_i-1]$ 满足，电台 $i$ 无法启用。

- 若 $f \in [1,\,r_i]$ 不满足，电台 $i$ 无法启用。


转换成连边关系就是：

- $\text{yes}(i) \rightarrow \text{no}(n+l_i),\ \text{yes}(i) \rightarrow \text{yes}(n+r_i+1)$

- $\text{yes}(n+l_i) \rightarrow \text{no}(i)$ 

- $\text{no}(n+r_i+1) \rightarrow \text{no}(i)$


![](https://i.loli.net/2019/09/16/IYdKv7AZx3TyRoC.png)

还有一个小细节，$f$ 不能等于 $0$ ！有个巧妙的连边是 $\text{yes}(n+1) \rightarrow \text{no}(n+1)$ ，这样 $\text{yes}(n+1)$ 成立时会造成矛盾，$\text{no}(n+1)$ 成立时刚好不会有问题。

建完图后，跑一跑 $\text{2 - SAT}$ 就行啦！判断无解的方法跟模板题一样，而有解时的 $f$ ，满足 $\text{yes}(n+f+1)$ ，$\text{no}(n+f)$ 成立 ，跑完 $\text{2 - SAT}$ 后枚举找到这个分界点即可。

---

### 代码实现

注意我的代码实现里 $n$ 个电台是从 $0$ 到 $n - 1$ 标号的。

```cpp
#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 2e6 + 5, E = 4e6 + 5;

struct List {
    int tot, fst[N], nxt[E], to[E];

    List() { memset(fst, -1, sizeof(fst)); }
    inline void insert(int u, int v) {
        nxt[tot] = fst[u]; to[tot] = v; fst[u] = tot++;
    }
    inline void link(int u, int v) {
        insert(u, v); insert(v ^ 1, u ^ 1);
    }
} e;

int n, m, m0, m1, k, c, tms, vol, dfn[N], low[N], stc[N], col[N];
bool ins[N];

inline int yes(int u) { return u << 1; }
inline int no(int u) { return u << 1 | 1; }

void tarjan(int u) {
    dfn[u] = low[u] = tms++;
    int pos = vol; stc[vol++] = u; ins[u] = true;
    for (int i = e.fst[u]; ~i; i = e.nxt[i]) {
        int v = e.to[i];
        if (dfn[v] == -1) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        while (vol > pos) {
            int v = stc[--vol];
            col[v] = c; ins[v] = false;
        } c++;
    }
}

bool solve() {
    for (int i = 0; i <= no(n + m); i++) { dfn[i] = -1; }
    for (int i = 0; i <= no(n + m); i++) {
        if (dfn[i] == -1) { tarjan(i); }
    }
    for (int i = 0; i <= n + m; i++) {
        if (col[yes(i)] == col[no(i)]) { return false; }
    } return true;
}

int main() {
    m0 = read(); n = read(); m = read(); m1 = read();
    for (int i = 0; i < m0; i++) {
        int u = read(), v = read(); u--; v--;
        e.link(no(u), yes(v));
    }
    for (int i = 0; i < m; i++) {
        e.link(yes(n + i), yes(n + i + 1));
    } e.link(yes(n), no(n));
    for (int i = 0; i < n; i++) {
        int l = read(), r = read();
        e.link(yes(i), no(n + l - 1));
        e.link(yes(i), yes(n + r));
    }
    for (int i = 0; i < m1; i++) {
        int u = read(), v = read(); u--; v--;
        e.link(yes(u), no(v));
    }
    if (solve()) {
        for (int i = 0; i < n; i++) {
            if (col[yes(i)] < col[no(i)]) { k++; }
        }
        for (int i = 1; i <= m; i++) {
            if (col[yes(n + i)] < col[no(n + i)]) {
                printf("%d %d\n", k, i); break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (col[yes(i)] < col[no(i)]) { printf("%d ", i + 1); }
        }
    } else {
        puts("-1");
    }
    return 0;
}
```

---

## 作者：GIFBMP (赞：2)

第一次想出 2-SAT 题，写发题解纪念一下。

记区间数为 $n$，首先我们发现“至多选择一个”和“至少选择一个”是经典的 2-SAT 限制。然后对于所有选择的区间的交集不能为空的条件，我们可以把它转化成：若两个区间交集为空，那么这两个区间至多选择一个。那么就可以 2-SAT 了，但是使用这种做法，边数是 $\Theta(n^2)$ 的，显然过不去。

我们考虑优化，我们把区间按左端点从小到大排序，然后就可以发现，对于一个区间，在它之后与它不交的区间必然是一个后缀（在之前的因为在处理前面的区间时已经连过边了，所以不用管）。于是考虑前缀和优化建图，然后就做完了，具体实现可以参考代码。

时间复杂度 $\Theta(n\log n)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 2e6 + 10 , INF = 0x3f3f3f3f ;
int n , m1 , m2 , L , fir[MAXN] , tot , b[MAXN] , ans[MAXN] ;
struct node {
	int l , r , id ;
	bool operator < (node x) const {return l < x.l ;}
} a[MAXN] ;
struct edge {int to , nxt ;} e[MAXN << 1] ;
void add (int u , int v) {e[++tot].to = v ; e[tot].nxt = fir[u] ; fir[u] = tot ;}
int dfn[MAXN] , low[MAXN] , st[MAXN] , tp , vis[MAXN] , col[MAXN] , cnt , cc ;
void tarjan (int x) {
	dfn[x] = low[x] = ++cnt ; st[++tp] = x ; vis[x] = 1 ;
	for (int i = fir[x] , v = e[i].to ; i ; i = e[i].nxt , v = e[i].to) {
		if (!dfn[v]) tarjan (v) , low[x] = min (low[x] , low[v]) ;
		else if (vis[v]) low[x] = min (low[x] , dfn[v]) ;
	}
	if (dfn[x] == low[x]) {
		col[x] = ++cc ; vis[x] = 0 ;
		for (; st[tp] != x ; tp--) vis[st[tp]] = 0 , col[st[tp]] = cc ;
		tp-- ;
	}
}
int U[MAXN] , V[MAXN] , p[MAXN] ;
int main () {
	scanf ("%d%d%d%d" , &m1 , &n , &L , &m2) ;
	for (int i = 1 ; i <= m1 ; i++) scanf ("%d%d" , &U[i] , &V[i]) ;
	for (int i = 1 ; i <= n ; i++) scanf ("%d%d" , &a[i].l , &a[i].r) , a[i].id = i ;
	sort (a + 1 , a + n + 1) ;
	for (int i = 1 ; i <= n ; i++) p[a[i].id] = i ; 
	for (int i = 1 ; i <= m1 ; i++) add (p[U[i]] + n , p[V[i]]) , add (p[V[i]] + n , p[U[i]]) ;
	for (int i = 1 , u , v ; i <= m2 ; i++)
		scanf ("%d%d" , &u , &v) , add (p[u] , p[v] + n) , add (p[v] , p[u] + n) ;
	for (int i = 1 ; i <= n ; i++) {
		if (i < n) add (2 * n + i , 2 * n + i + 1) , add (3 * n + i + 1 , 3 * n + i) ;
		add (2 * n + i , i + n) , add (i , 3 * n + i) ;
	}
	
	for (int i = 1 ; i <= n ; i++) b[i] = a[i].l ;
	for (int i = 1 ; i <= n ; i++) {
		int x = lower_bound (b + 1 , b + n + 1 , a[i].r + 1) - b ;
		if (x > n) continue ;
		add (i , 2 * n + x) , add (3 * n + x , i + n) ;
	}
	for (int i = 1 ; i <= 4 * n ; i++)
		if (!dfn[i]) tarjan (i) ;
	for (int i = 1 ; i <= n ; i++)
		if (col[i] == col[i + n]) return !printf ("-1") ;
	int L = -INF , R = INF , tt = 0 ;
	for (int i = 1 ; i <= n ; i++)
		if (col[i] < col[i + n]) L = max (L , a[i].l) , R = min (R , a[i].r) , ans[++tt] = a[i].id ;
	printf ("%d %d\n" , tt , L) ;
	sort (ans + 1 , ans + tt + 1) ;
	for (int i = 1 ; i <= tt ; i++) printf ("%d " , ans[i]) ;
	return 0 ;
}
```

---

## 作者：Pelom (赞：2)

[更好的阅读体验](https://pelom.top/archives/14/)
### 题意

有$n$个要求，要求电台$x_i$与$y_i$中至少选择$1$个

共$p$个电台，满足一个电台的信号功率范围为$[l_i,r_i]$

在$[1,M]$选择一个信号功率，要求满足选择的所有电台

有$m$对电台不能同时选择

判断是否能够满足，如果是，输出方案

**数据范围：**$2 \le n,p,M,m \le 4 \cdot 10^5$

### 题解

对于至少选择一个和不能同时选择的要求，我们容易看出这是一个$2-SAT$问题

用节点$x_i$表示选择电台$x_i$，用节点$x_i+p$表示不选择$x_i$

则要求**从$x_i$与$y_i$中至少选择$1$个**可以拆解为**不选择$y_i \rightarrow$选择$x_i$** 与 **不选择$x_i \rightarrow$选择$y_i$**

建边

$$y_i+p \rightarrow x_i$$

$$x_i+p \rightarrow y_i$$

相似的，**不能同时选择**可以拆解为**选择$x_i \rightarrow$不选择$y_i$** 与 **选择$y_i \rightarrow$不选择$x_i$**

建边

$$x_i \rightarrow y_i+p$$

$$y_i \rightarrow x_i+p$$

现在还需要解决信号功率的限制，选择一个电台后我们无法得知一个确定的信号功率来约束它，但我们知道哪些信号功率不能选，因此由$i$向$[1,l_i-1] \cup [r_i+1,M]$对应的节点建边，并且由$[l_i,r_i]$对应的节点向$i+p$建边，意为不选择此段范围中的信号功率便不能选择$i$

但是如果这样建边的话空间时间都承受不了，考虑将建边的对象转化为区间，能不能向区间的两端建边表示对这段区间的选择与否呢？这样是可以的，由$i$向信号频率为$x$对应的节点建边，表示**不能选择小于$x$的信号频率**，可是如果我们要表示**不能选择大于$x$的信号频率**呢？再额外使用$M$个节点保存大于的信息就好了

而要保存区间连续的关系，还需在区间中向相邻的值建边，如下

```cpp
tot=p<<1;
pre[1]=++tot;
suc[1]=tot+M;
for(int i=2;i<=M;i++){
    pre[i]=++tot;
    suc[i]=tot+M;
    add(pre[i],pre[i-1]);
    add(suc[i-1],suc[i]);
}
```

至此，约束条件已经被全部写入图中，跑一次$Tarjan$即可得知是否存在方案，而输出答案，只需取满足条件的$max(l_i)$作为最后选定的信号功率（因为题目未作额外要求）

**代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
const int N=4e5+10;
stack<int> S;
int n,p,M,m,x,y;
int l[N],r[N];
int cnt,tot,dep,cc,ans;
int head[N<<2],pre[N],suc[N],dfn[N<<2],low[N<<2],clr[N<<2],a[N];
struct edge{
    int nxt,to;
} e[N*10];
template <typename T>
inline T Max(T a,T b){
    return a>b?a:b;
}
template <typename T>
inline T Min(T a,T b){
    return a<b?a:b;
}
inline void add(int u,int v){
    e[++cnt]=(edge){head[u],v};
    head[u]=cnt;
}
void Tarjan(int u){
    dfn[u]=low[u]=++dep;
    S.push(u);
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(!dfn[v]){
            Tarjan(v);
            low[u]=Min(low[u],low[v]);
        }
        else if(!clr[v])
            low[u]=Min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        cc++;
        for(int t;t!=u;){
            t=S.top();
            S.pop();
            clr[t]=cc;
        }
    }
}
int main(){
    scanf("%d%d%d%d",&n,&p,&M,&m);
    tot=p<<1;
    pre[1]=++tot;
    suc[1]=tot+M;
    for(int i=2;i<=M;i++){
        pre[i]=++tot;
        suc[i]=tot+M;
        add(pre[i],pre[i-1]);
        add(suc[i-1],suc[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&y);
        add(x+p,y);
        add(y+p,x);
    }
    for(int i=1;i<=p;i++){
        scanf("%d%d",&l[i],&r[i]);
        if(l[i]-1>=1)
            add(i,pre[l[i]-1]);
        if(r[i]+1<=M)
            add(i,suc[r[i]+1]);
        add(suc[l[i]],i+p);
        add(pre[r[i]],i+p);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y+p);
        add(y,x+p);
    }
    for(int i=1;i<=(p<<1);i++)
        if(!dfn[i])
            Tarjan(i);
    for(int i=1;i<=p;i++)
        if(clr[i]==clr[i+p]){
            puts("-1");
            return 0;
        }
    for(int i=1;i<=p;i++)
        if(clr[i]<clr[i+p]){
            ans=Max(ans,l[i]);
            a[++*a]=i;
        }
    printf("%d %d\n",*a,ans);
    for(int i=1;i<=*a;i++)
        printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：Owen_codeisking (赞：2)

一道需要前缀优化建图的 2-SAT 的题。

先不考虑 $l\le f\le r$ 的限制，剩下的限制就是：

1. 两个至少选一个

2. 两个最多选一个

根据 2-SAT 的套路，先把每个点拆成选和不选。第一种情况让 $N\rightarrow Y$，第二种情况让 $Y\rightarrow N$。

因为 $M$ 很小，所以我们直接把每个形如 $f\le i$ 的限制都建出来。

我们知道，$f\le i\Rightarrow f\le i+1,f\ge i+1\Rightarrow f\ge i$，所以 $Y_i\rightarrow Y_{i+1},N_{i+1}\rightarrow N_i$。

若选点 $i$，需要满足 $f\le r_i$，不满足 $f\le l_i-1$，那么直接连边即可。

另外，我们要保留 $f\le 0$ 的限制。因为 $0$ 不能选，$Y_0\rightarrow N_0,N_0\rightarrow Y_0$。

然后粘个 2-SAT 板子这题就做完了。

代码就不贴了，反正大家写的方法都一样。

---

## 作者：do_it_tomorrow (赞：1)

考虑回忆 2-sat 连边的意义，如果 $x\to y$ 那么就表示如果 $x$ 满足那么 $y$ 就必须满足。

所以根据 2-sat 的经典套路，把一个操作 $x$ 拆分成为 $x_1$ 和 $x_2$。其中 $x_1$ 代表满足该操作，而 $x_2$ 代表不满足该操作。

那么对于题目的不能同时启用 $x,y$ 的限制就显然应该是这样连边：

$$x_1\to y_2,y_1\to x_1$$

根据我们对连边的定义，上面的连边就是如果 $x$ 被启用那么 $y$ 就一定不会被启用，如果 $y$ 被启用 $x$ 就一定不会被启用。

同样的，对于 $x,y$ 至少有一个启用的连边就应该是：

$$x_2\to y_1,y_1\to x_1$$

同理，这个的意思就是如果 $x$ 不启用那么 $y$ 就必须启用，同样的如果 $y$ 不启用那么 $x$ 就必须启用。

接下来考虑选择的区间重复怎么处理。

对于主频 $f$，因为所有的范围都需要包含它，所以需要存在一个位置被所有的覆盖被所有选择的 $[l,r]$ 所覆盖。

那么显然我们只需要给 $x_1$ 连向所有没有与 $x$ 的范围相交的位置即可，也几乎是需要给一个区间内全部连边，所以考虑线段树优化建图（不想动脑子写前缀和）。

首先介绍一下线段树优化建图的思想，假设我们需要给 $[l,r]$ 中所有的节点全部连边，那么我们可以建出类似于下面的树形结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/31etrmsn.png?x-oss-process=image/resize,m_lfit,h_400)

接下来进行类似于线段树区间操作，在应该打上懒标记的时候直接把出边连向这个节点。

对于书上的所有边都是由父亲连向儿子的有向边，对于每一个叶子节点把叶子节点连向对应的节点。

对于上面的例子，如果如果要连接 $[3,7]$ 这个区间的所有点，那么就应该连接 $[3,4]$，$[5,6]$ 和 $[7,7]$。

对于这样的操作，时间复杂度的证明类似于线段树的证明，显然新建的边的数量和时间复杂度都是 $O(\log n)$ 的。

上面的例子是把点连向区间连边，同样的区间向点连边可以直接把边的方向反向。

考虑把所有的点按照 $l$ 排序，然后对于第 $x$ 个位置，找到第 $1$ 个比 $r_x$ 大的 $l_j$，把 $x_1$ 连向 $[j,n]$ 的所有的点的 $2$ 连边，同样的把这个区间中所有的 $1$ 连向 $x_2$。

根据套路，假设 $x$ 属于的强连通分量的编号为 $col_x$，那么：

- 如果 $col_{x1}=col_{x2}$，那么无解。
- 如果 $col_{x1}\lt col_{x2}$，那么选择启用 $x$，反之不启用。

方案都有了，显然求解其交集就不困难了。

虽然码量较大而且时空复杂度都不优秀，但是重要的是不用动脑，时间复杂度为 $O(n\log n)$。

---

## 作者：cmrhhh (赞：1)

# 思路来源：
先看看这个题目描述：**满足……**  
我们是否可以尝试 2-SAT？试试看。
# 思路
难点在建边。~~先 `#define` 一下~~
```cpp
#define T(x) (2*(x)-1)
#define F(x) (2*(x))
#define LE(x) T(x+p+1) //hz <=x
#define GT(x) F(x+p+1) //hz >x
#define YES(x) (belong[T(x)]<belong[F(x)])
```
1. 对于这个条件：
- $n$ 对 $(x,y)$，$x$ 电站或 $y$ 电站中至少有一个 

这是表示**或**的句子，我们可以让**不选 $x$** 向**选 $y$** 连边，还有其逆否命题。
```cpp
	for(int i=0;i<n;++i){
		int x,y;
		cin>>x>>y;
		g[F(x)].push_back(T(y));
		g[F(y)].push_back(T(x));
	}
```
2. 对于这个条件：
- $m$ 对 $(x,y)$，$x$ 电站或 $y$ 电站中最多有一个

我们可以让**选 $x$** 指向**不选 $y$**，还有其逆否命题。
```cpp
	for(int i=0;i<m;++i){
		int x,y;
		cin>>x>>y;
		g[T(x)].push_back(F(y));
		g[T(y)].push_back(F(x));
	}
```
3. 对于这个条件：
- 第 $i$ 种电站有两个参数 $l_i$ 和 $r_i(1\le l_i\le r_i\le M)$，表示其覆盖的区间为$[l_i,r_i]$。若选定一个电站序列，序列中所有电站覆盖区间的交集不能为空。我们把区间转化为 $\le x$ 和 $>x$：
```cpp
	for(int i=1;i<=p;++i){
		int l,r;
		cin>>l>>r;
		g[T(i)].push_back(GT(l-1));
		g[LE(l-1)].push_back(F(i));
		g[T(i)].push_back(LE(r));
		g[GT(r)].push_back(F(i));
	}
```
并且要注意如 $>1$ 一定 $>0$ 这类的传递关系：
```cpp
	for(int i=1;i<=M;++i){
		g[LE(i-1)].push_back(LE(i));
		g[GT(i)].push_back(GT(i-1));
	}	
```
最后注意偏移量等细节，tarjan 就是最简单的板子。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=16e5+10;
vector<int>g[maxn];
int dfn[maxn],low[maxn],cnt,belong[maxn],scc;
stack<int>st;
bool instack[maxn];
void tarjan(int u){
	low[u]=dfn[u]=++cnt;
	st.push(u);instack[u]=1;
	for(int v:g[u]){
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(instack[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		++scc;
		while(1){
			int v=st.top();
			st.pop();
			instack[v]=0;
			belong[v]=scc;
			if(v==u)break;
		}
	}
}
#define T(x) (2*(x)-1)
#define F(x) (2*(x))
#define LE(x) T(x+p+1) //hz <=x
#define GT(x) F(x+p+1) //hz >x
#define YES(x) (belong[T(x)]<belong[F(x)])
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,p,M,m;
	cin>>n>>p>>M>>m;
	for(int i=0;i<n;++i){
		int x,y;
		cin>>x>>y;
		g[F(x)].push_back(T(y));
		g[F(y)].push_back(T(x));
	}
	for(int i=1;i<=p;++i){
		int l,r;
		cin>>l>>r;
		g[T(i)].push_back(GT(l-1));
		g[LE(l-1)].push_back(F(i));
		g[T(i)].push_back(LE(r));
		g[GT(r)].push_back(F(i));
	}
	for(int i=0;i<m;++i){
		int x,y;
		cin>>x>>y;
		g[T(x)].push_back(F(y));
		g[T(y)].push_back(F(x));
	}
	int N=M+1+p;
	for(int i=1;i<=M;++i){
		g[LE(i-1)].push_back(LE(i));
		g[GT(i)].push_back(GT(i-1));
	}	
	for(int i=1;i<=N*2;++i)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=N;++i)
		if(belong[T(i)]==belong[F(i)]){cout<<-1;return 0;}
	int hz;
	for(int i=1;i<=M;++i)
		if(belong[LE(i)]<belong[GT(i)]){
			hz=i;
			break;
		}
	vector<int>ans;
	for(int i=1;i<=p;++i)
		if(YES(i))ans.push_back(i);
	cout<<ans.size()<<" "<<hz<<"\n";
	for(auto i:ans)cout<<i<<" ";	
	
	return 0;
} 
```

---

## 作者：CQ_Bab (赞：1)

# 前言

看见这道题是 2-SAT 就点进来做了，发现题解都写的前缀优化建边可是明明线段树优化建边也可以为什么没人写呢？

# 思路

当看到前两个限制时就可以确定这是一个 2-SAT 了，前两个操作不讲，如果不会就去看一下 [模板](https://www.luogu.com.cn/problem/P4782)。然后我们需要思考的就是对于区间的限制，通过观察可以发现如果要选第 $i$ 个区间，那么与第 $i$ 个区间没有交集的一定都不会选，同时与 $i$ 没有交集的选了那么 $i$ 就不能选然后我们的重点就是想到一种算法能支持一个区间向一个点连边以及一个点向一个区间连边了，这不就是裸的线段树优化建边吗？不会的去看一下 [Legacy](https://www.luogu.com.cn/problem/CF786B) 。

然后现在我们就只需要去找那些与 $i$ 没有交集的区间了，并且还要是一段连续的，不难想到按左端点排序，那么对于 $i$ 与他没有交集的就是那些 $l_j>r_i$ 或者是 $l_i>r_j$ 的可以发现对于后一种情况当 $j=i$ 的时候会筛到 $i$ 所以只需要考虑前一种，这就是一个二分了，而分出之后对于区间 $id\sim n$ 如果选那么 $i$ 不选，如果 $i$ 选 $id\sim n$ 就不能选，最后跑一遍模板 2-SAT 即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%d",&x)
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
const int N=4e5+10;
int n,pid,Max,m;
int u[N],V[N];
struct node{
	int l,r;
	int id;
}s[N];
bool cmp(node a,node b) {
	return a.l<b.l;
}
struct xds{
	int l,r;
}tr[N<<2];
vector<int>v[N*10];
#define id(x) x+2*pid
void add(int x,int y) {
	v[x].push_back(y);
}//tr为线段树连向选
void build(int u,int l,int r) {
	tr[u]={l,r};
	if(l==r) {
		add(u+2*pid,l+pid);//一棵有点亮相区间的树
		add(l,u+6*pid);//一棵由区间连向点的树
		return ;
	}
	int mid=l+r>>1;
	add(u+2*pid,id(u*2));
	add(u+2*pid,id(u*2+1));
	add(u*2+6*pid,u+6*pid);
	add(u*2+1+6*pid,u+6*pid);
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void modify(int u,int l,int r,int k) {
	if(tr[u].l>=l&&tr[u].r<=r) {
		add(k,id(u));//点向区间连边
		add(u+6*pid,k+pid);//区间向点连边
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=l) modify(u<<1,l,r,k);
	if(mid<r) modify(u<<1|1,l,r,k);
}
int ri[N];
int low[N*10],dfn[N*10],val[N*10];
stack<int>st;
int is[N*10],tot,ip;
int p[N];
void tarjan(int x) {//模板
	st.push(x);
	is[x]=1;
	dfn[x]=low[x]=++tot;
	for(auto to:v[x]) {
		if(!dfn[to]) tarjan(to),low[x]=min(low[x],low[to]);
		else if(is[to]) low[x]=min(low[x],dfn[to]);
	}
	if(low[x]==dfn[x]) {
		ip++;
		int pp;
		do{
			pp=st.top();
			st.pop();
			val[pp]=ip;
			is[pp]=false;
		}while(pp!=x);
	}
}
vector<pair<int,int>>ve;
void solve() {
	in(n),in(pid),in(Max),in(m);
	rep(i,1,n) in(u[i]),in(V[i]);
	rep(i,1,pid) in(s[i].l),in(s[i].r),s[i].id=i;
	sort(s+1,s+1+pid,cmp);
	rep(i,1,pid) p[s[i].id]=i;//存储现在的编号
	build(1,1,pid);//建出线段树
	rep(i,1,n) {
		add(p[u[i]]+pid,p[V[i]]);//将两种模板操作连边（注意这里要为排完序之后的编号
		add(p[V[i]]+pid,p[u[i]]);
	}
	rep(i,1,m) {
		int x,y;
		in(x),in(y);
		add(p[x],p[y]+pid);
		add(p[y],p[x]+pid);
	}
	rep(i,1,pid) ri[i]=s[i].l;
	rep(i,1,pid) {
		int id=upper_bound(ri+1,ri+1+pid,s[i].r)-ri;//二分
		if(id<=pid) modify(1,id,pid,i);
	}
	rep(i,1,10*pid) if(!dfn[i]) tarjan(i);
	rep(i,1,pid) {
		if(val[i]==val[i+pid]) {
			cout<<"-1\n";//无解
			return ;
		}
	}
	rep(i,1,pid) if(val[i]<val[i+pid]) ve.push_back({s[i].l,s[i].r});
	int ll=0,rr=INT_MAX;
	for(auto to:ve) {
		ll=max(ll,to.first);
		rr=min(rr,to.second);
	}
	cout<<ve.size()<<' '<<rr<<endl;
	rep(i,1,pid) if(val[i]<val[i+pid]) cout<<s[i].id<<' ';
	return;
}
fire main() {
	while(T--) solve();
	return false;
}
```

# 提示

这种算法除了空间大一点没什么劣处，而且还挺好写的都是模板。

---

## 作者：快乐的大童 (赞：1)

一种~~自认为~~比较好想、好理解、好写的做法。

~~貌似这个做法和题解区的两种做法还不是很一样。~~

[cnblogs](https://www.cnblogs.com/dcytrl/p/18012910)
### 题意简述
有 $n$ 个电站，频率范围是 $l_i,r_i(1\le l_i\le r_i\le m)$，有 $m1$ 条限制形如 $x,y$，表示 $x,y$ 电站至少选一个；同时有 $m2$ 条限制形如 $x,y$，表示 $x,y$ 电站至多选一个；同时要满足选出的电站的频率范围有交。求解的存在性。

**输入格式**：第一行四个整数 $m1,n,m,m2$，接下来 $m1$ 行描述限制，接下来 $n$ 行描述频率范围，接下来 $m2$ 行描述限制。

**输出格式**：若无解输出 `-1`，若有解，第一行分别输出选出电站数量 $k$ 和选出的电站的频率范围的交集中的任意一个整数元素 $f$，第二行以任意顺序输出选出的电站编号。

$n,m,m1,m2\le 4\times10^5$。

**备注：本文中的 $n,m,m1,m2$ 分别代表了原题的 $p,M,n,m$。**
### 分析
看到这种限制立即想到 2-SAT。

那 $m1+m2$ 条限制就是纯 2-SAT 板子，不再赘述。

考虑怎么处理区间有交的问题，发现这个限制相当于我们不能选两个无交的区间，但是暴力两两之间连边是 $O(n^2)$ 的。

发现区间 $[l_i,r_i]$ 与区间 $[l_j,r_j]$ 无交当且仅当 $r_i<l_j$ 或 $r_j<l_i$。而我们发现 $l_j>r_i$ 的 $j$ 是一段后缀，$r_j<l_i$ 的 $j$ 是一段前缀。

那么做法就呼之欲出了。使用前缀和优化建图（不会前缀和优化建图见 [Riddle](https://www.luogu.com.cn/problem/P6378)），每个前缀点 $pre_i$ 连向以该点为右端点的电站的反点，每个后缀点 $sec_i$ 连向以该点为左端点的电站的反点。根据定义有连边 $pre_i\rightarrow pre_{i-1},sec_i\rightarrow sec_{i+1}$。其次，对于每个点 $i$，有连边 $i\rightarrow pre_{l_i-1},i\rightarrow sec_{r_i+1}$，注意此时的 $i$ 为 $i$ 的正点。

[code](https://codeforces.com/contest/1215/submission/245564852)

---

## 作者：chihik (赞：1)

令 $u$ 表示选择电站 $u$ , $u'$ 表示不选择电站 $u$。

首先可以简单的处理出电站之间的要求：

- $u,v$ 至少选一个，连边 $(u',v),(v',u)$

- $u,v$ 至多选一个，连边 $(u,v'),(v,u')$

可以枚举 $f$ ,电站区间不包含 $f$ 的强制不选 ( 连边$(u,u')$ )，然后用 $\text{2-SAT}$ 求解。

考虑优化上述过程，$f$ 对每个电站的要求可以看作两个：

- $f$ 必须在 $[1,r_i]$ 之间
- $f$ 必须不在 $[1,l_i)$ 之间

那么可以利用前缀优化建图，注意 $f$ 不能为 $0$ ，强制不选即可。

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 2e6 , MAXM = 2e6;

int n , k , m1 , m2 , l[ MAXN + 5 ] , r[ MAXN + 5 ];

int Enum , tmp[ MAXN + 5 ] , Head[ MAXN + 5 ];
struct Edge { int v , nxt; } Graph[ 2 * MAXM + 5 ];
void Add_Edge( int u , int v ) { Graph[ ++ Enum ] = { v , Head[ u ] }; Head[ u ] = Enum; }

int tim , cnt , dfn[ MAXN + 5 ] , low[ MAXN + 5 ] , bel[ MAXN + 5 ];
int Top , Stack[ MAXN + 5 ];
void Clear( ) {
	tim = cnt = 0;
	memset( dfn , 0 , sizeof( dfn ) );
	memset( low , 0 , sizeof( low ) );
	memset( bel , 0 , sizeof( bel ) );
}
void Tarjan( int u , int fa ) {
	dfn[ u ] = low[ u ] = ++ tim;
	Stack[ ++ Top ] = u;
	for( int i = Head[ u ] ; i ; i = Graph[ i ].nxt ) {
		int v = Graph[ i ].v; if( v == fa ) continue;
		if( !dfn[ v ] ) {
			Tarjan( v , u );
			low[ u ] = min( low[ u ] , low[ v ] );
		}
		else if( !bel[ v ] )
			low[ u ] = min( low[ u ] , dfn[ v ] );
	}
	if( dfn[ u ] == low[ u ] ) {
        ++ cnt;
        for( ; Stack[ Top ] != u ; Top -- ) bel[ Stack[ Top ] ] = cnt;
        bel[ Stack[ Top -- ] ] = cnt;
	}
}

int main( ) {
	scanf("%d %d %d %d",&m1,&n,&k,&m2);
	for( int i = 1 , u , v ; i <= m1 ; i ++ ) {
		scanf("%d %d",&u,&v);
		Add_Edge( u + n , v ) , Add_Edge( v + n , u );
	}
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d %d",&l[ i ],&r[ i ]);
	for( int i = 1 , u , v ; i <= m2 ; i ++ ) {
		scanf("%d %d",&u,&v);
		Add_Edge( u , v + n ) , Add_Edge( v , u + n );
	}
	
	//2*n + 2*k
	for( int i = 1 ; i <= k ; i ++ ) Add_Edge( 2 * n + i + 1 , 2 * n + i ); // >  f
	for( int i = k + 1 ; i >= 2 ; i -- ) Add_Edge( 2 * n + i - 1 + ( k + 1 ) , 2 * n + i + ( k + 1 ) ); // <= f
	Add_Edge( 2 * n + 1 + ( k + 1 ) , 2 * n + 1 );  // f 不为 0 
	for( int i = 1 ; i <= n ; i ++ ) { //与 f 的限制 
		Add_Edge( i , 2 * n + r[ i ] + 1 + ( k + 1 ) ); Add_Edge( i , 2 * n + l[ i ] );
		Add_Edge( 2 * n + r[ i ] + 1 , i + n ); Add_Edge( 2 * n + l[ i ] + ( k + 1 ) , i + n );
	}
	
	for( int i = 1 ; i <= 2 * n + 2 * ( k + 1 ) ; i ++ ) if( !dfn[ i ] ) Tarjan( i , 0 );
	
	int num = 0 , f;
	for( int i = 1 ; i <= n ; i ++ ) {
		if( bel[ i ] == bel[ i + n ] ) { printf("-1\n"); return 0; }
		if( bel[ i ] < bel[ i + n ] ) num ++;
	}
	for( int i = 1 ; i <= k ; i ++ ) if( ( bel[ 2 * n + i ] < bel[ 2 * n + i + ( k + 1 ) ] ) && ( bel[ 2 * n + i + 1 ] > bel[ 2 * n + i + 1 + ( k + 1 ) ] ) ) { f = i; break; }
	
	printf("%d %d\n", num , f );
	for( int i = 1 ; i <= n ; i ++ ) if( bel[ i ] < bel[ i + n ] ) printf("%d ", i );
	return 0;
}
```

---

## 作者：xukuan (赞：1)

算法：2-sat

重点显然是建模

我们把一个对象拆成两个点分别表示选和不选。(接下来用$yes(x)$表示表示对象$x$选的点，$no(x)$表示对象$x$不选的点)

1. 电台x和电台y必须用至少一个

我们发现这样的一个性质：

- 只要x不选，y一定选
- 只要y不选，x一定选

连边方式：$no(x)->yes(y),no(y)->yes(x)$

2. 电台x和电台y不可同时用

我们又发现这样的性质：

- 只要x选，y一定不选
- 只要y选，x一定不选

连边方式：$yes(x)->no(y),yes(y)->no(x)$

3. 如何制定唯一的f，并表示出i号电台不允许启用的情况

可以考虑前缀和的优化：

|$[1,l-1]$|$[1,r]$|$i$能否启用|
| -----------: | -----------: | -----------: |
|0|0|0|
|0|1|1|
|1|1|0|
|1|0|不存在|

**接下来我有点懵逼，去看了Sooke的题解**

其实可以再开一些点表示$f \leq i$的情况是否满足

注意：当$f \leq i$时，一定有$f \leq i+1$。当$f > i+1$时，一定有$f > i$

连边方式：$yes(n+i+1)->yes(n+i+2), no(n+i+2)->no(n+i+1)$

最后总结三种连边方式：
- $no(x)->yes(y),no(y)->yes(x)$
- $yes(x)->no(y),yes(y)->no(x)$
- $yes(n+i+1)->yes(n+i+2), no(n+i+2)->no(n+i+1)$

代码：

其实2-sat的题看懂了之后基本不要注释，重点就是**建模！！！**

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
using namespace std;

const int N=2000010;
int n,p,M,m,sum,deep,colour,v[N],dfn[N],low[N],color[N];
int ver[N<<1],Next[N<<1],head[N],tot;
stack<int> st;

inline int read(){
	int x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	int y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

inline void addEdge(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

void tarjan(int x){
	low[x]=dfn[x]=++deep;
	v[x]=1; st.push(x);
	for(int i=head[x]; i; i=Next[i]){
		int y=ver[i];
		if(dfn[y]==-1){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		color[x]=++colour;
		v[x]=0;
		while(st.top()!=x){
			color[st.top()]=colour;
			v[st.top()]=0;
			st.pop();
		}
		st.pop();
	}
}

inline int yes(int p){return p<<1;}
inline int no(int p){return p<<1|1;}

int main(){
	n=read(); p=read(); M=read(); m=read();
	for(int i=1; i<=n; i++){
		int x=read()-1,y=read()-1;
		addEdge(no(x),yes(y));
		addEdge(yes(y)^1,no(x)^1);
	}
	for(int i=0; i<M; i++){
		addEdge(yes(p+i),yes(p+i+1));
		addEdge(yes(p+i+1)^1,yes(p+i)^1);
	}
	addEdge(yes(p),no(p));
	addEdge(no(p)^1,yes(p)^1);
	for(int i=0; i<p; i++){
		int l=read(),r=read();
		addEdge(yes(i),no(p+l-1));
		addEdge(no(p+l-1)^1,yes(i)^1);
		addEdge(yes(i),yes(p+r));
		addEdge(yes(p+r)^1,yes(i)^1);
	}
	for(int i=0; i<m; i++){
		int x=read()-1,y=read()-1;
		addEdge(yes(x),no(y));
		addEdge(no(y)^1,yes(x)^1);
	}
	memset(dfn,-1,sizeof(dfn));
	for(int i=0; i<=no(p+M); i++){
		if(dfn[i]==-1) tarjan(i);
	}
	for(int i=0; i<=p+M; i++){
		if(color[yes(i)]==color[no(i)]) return printf("-1")&0;
	}
	for(int i=0; i<p; i++){
        if(color[yes(i)]<color[no(i)]) sum++;
    }
    for(int i=1; i<=M; i++){
        if(color[yes(p+i)]<color[no(p+i)]){
        	write(sum); putchar(' ');
        	write(i); putchar('\n');
			break;
        }
    }
    for(int i=0; i<p; i++){
        if(color[yes(i)]<color[no(i)]){
			write(i+1);
			putchar(' ');
		}
    }
	return 0;
}
```

---

## 作者：Piwry (赞：0)

突然发现自己的思路不太一样，于是写下题解

## 解析

首先设 $p$ 个 01 变量 $x_i$ 表示第 $i$ 个电站是否选择

对于那 $n$ 个 $(x, y)$ 的限制以及那 $m$ 个 $(u, v)$ 的限制都是 2-SAT 板子，这里略过

题目要求选择一个 $f$，并且仅能选择包含该 $f$ 的电站。我们转化一下这个限制，其就相当于限制选择出的所有电站的区间的交（这组集合的交）必须不为空，这样才存在合法的 $f$

于是能想到，若我们选择了某个特定的电站，其它所有与该电站区间无交的电站都不能被选择。若我们对两两每对的电站检查并添加限制（这个限制算是 2-SAT 板子部分的），通过反证不难发现，这样跑 2-SAT 得到的答案方案的所有电站的区间的交一定不为空。于是我们再模拟一遍即可得到该方案下 $f$ 合法的取值范围，随便取一点作为最终答案即可

关于两两检查添加限制部分若暴力做复杂度无法承受。对于电站 $i$ 有区间 $[l_i, r_i]$，我们发现要与它添加限制的任意电站 $j$ 有区间 $[l_j, r_j]$ 需要满足 $r_j < l_i$ 或 $l_j > r_i$。考虑将电站分别按 $l_i$ 或 $r_i$ 排序，共两次（两轮）添加限制，每次做的时候需要添加限制的电站就总是一个前缀或后缀（具体断点可用二分找到），这样就可以用前缀建图优化连边了

另外关于（2-SAT 的）前缀建图优化可参考 [PA2010 Riddle](https://www.luogu.com.cn/problem/P6378)

## CODE

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using std::vector;
using std::sort;

const int MAXN =4e5+20;

/* -------------------------------- IO -------------------------------- */

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const int &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

/* -------------------------------- 2-SAT -------------------------------- */

namespace _2SAT{
	namespace Graph{
		struct edge{
			int to, nxt;
		};
		int tote;
		vector<int> first;
		vector<edge> e;
		
		inline void addedge(const int &u, const int &v){
			++tote, e[tote].to =v, e[tote].nxt =first[u], first[u] =tote;
		}
		
		inline void init(const int &_V, const int &_E){
			tote =0;
			first =vector<int>(_V+1, 0);
			e =vector<edge>(_E+1);
		}
	}
	using Graph::first;
	using Graph::e;
	using Graph::addedge;
	
	int Scc_id;
	vector<int> scc_id;
	
	namespace Tarjan{
		vector<int> dfn, low;
		int Dfn;
		vector<int> stk;
		int stk_top;
		vector<bool> instk;
		
		inline int min(const int &x, const int &y){
			return (x < y) ? x : y;
		}
		
		void tarjan(const int &u){
			low[u] =dfn[u] =++Dfn;
			stk[stk_top++] =u;
			instk[u] =1;
			for(int l =first[u]; l; l =e[l].nxt){
				if(!dfn[e[l].to]){
					tarjan(e[l].to);
					low[u] =min(low[u], low[e[l].to]);
				}
				else if(instk[e[l].to])
					low[u] =min(low[u], dfn[e[l].to]);
			}
			if(low[u] == dfn[u]){
				++Scc_id;
//				stk[stk_top] =0;
				while(stk[stk_top] != u){
					scc_id[stk[stk_top-1]] =Scc_id;
					instk[stk[stk_top-1]] =0;
					--stk_top;
				}
			}
		}
		
		inline void init(const int &_V){
			Scc_id =0;
			scc_id =vector<int>(_V+1);
			dfn =vector<int>(_V+1, 0), low =vector<int>(_V+1);
			Dfn =0;
			stk =vector<int>(_V);
			stk_top =0;
			instk =vector<bool>(_V+1, 0);
		}
	}
	using Tarjan::tarjan;
	
	int n;
	bool Illegal;
	vector<bool> val;
	
	inline void init(const int &_n, const int &_V, const int &_E){
		n =_n;
		val =vector<bool>(2*_n+1, 0);
		Graph::init(_V, _E);
		Tarjan::init(_V);
	}
	
	// `void addlimit(x1, b1, x2, b2)` -> ( x1 == b1 || x2 == b2 ) //
	inline void addlimit(const int &x1, const bool &b1, const int &x2, const bool &b2){
		/* [1, n] -> false, [n+1, 2n] -> true */
		addedge(x1+(b1^1)*n, x2+b2*n);
		addedge(x2+(b2^1)*n, x1+b1*n);
	}
	
	void work(){
		for(int i =1; i <= 2*n; ++i){
			if(!Tarjan::dfn[i])
				tarjan(i);
			if(i > n && scc_id[i] == scc_id[i-n])
				return Illegal =1, void();
		}
		for(int i =1; i <= n; ++i)
			val[i] =(scc_id[i+n] < scc_id[i]);
	}
}

/* -------------------------------- Main -------------------------------- */

int main(){
	const int n =read(), p =read(), M =read(), m =read();
	struct node{
		int l, r, number;
		
		node(){}
		node(const int &_l, const int &_r, const int &_number)
			:l(_l), r(_r), number(_number){}
	};
	vector<node> arr(p);
	_2SAT::init(p, p*6, n*2+m*2+(2+(p-1)*4+p*2)*2);
	for(int i =0; i < n; ++i)
		_2SAT::addlimit(read(), 1, read(), 1);
	for(int i =0; i < p; ++i)
		arr[i].l =read(), arr[i].r =read(), arr[i].number =i+1;
	for(int i =0; i < m; ++i)
		_2SAT::addlimit(read(), 0, read(), 0);
	
	auto cmp1 =[&](const node &A, const node &B){
		return A.r < B.r;
	};
	auto cmp2 =[&](const node &A, const node &B){
		return A.l > B.l;
	};
	for(int _t =0; _t < 2; ++_t){
		vector<int> prefix_in(p), prefix_out(p);
		sort(arr.begin(), arr.end(), (_t == 0) ? cmp1 : cmp2);
		prefix_in[0] =(_t == 0) ? (2*p+1) : (4*p+1);
		prefix_out[0] =(_t == 0) ? (2*p+1+p) : (4*p+1+p);
		_2SAT::addedge(prefix_in[0], arr[0].number), _2SAT::addedge(arr[0].number+p, prefix_out[0]);
		for(int i =1; i < (int)arr.size(); ++i){
			// [2*p+1, 3*p]/[4*p+1, 5*p] -> in, [3*p+1, 4*p]/[5*p+1, 6*p] -> out //
			prefix_in[i] =prefix_in[i-1]+1;
			prefix_out[i] =prefix_out[i-1]+1;
			_2SAT::addedge(prefix_in[i], prefix_in[i-1]), _2SAT::addedge(prefix_out[i-1], prefix_out[i]);
			_2SAT::addedge(prefix_in[i], arr[i].number), _2SAT::addedge(arr[i].number+p, prefix_out[i]);
		}
		for(const node &i:arr){
			// addlimit ( arr_[1, pos] == 0 || arr_i == 0 ) //
			int pos;
			if(_t == 0)
				pos =lower_bound(arr.begin(), arr.end(), node(-1, i.l, -1), cmp1)-arr.begin()-1;
			else
				pos =lower_bound(arr.begin(), arr.end(), node(i.r, -1, -1), cmp2)-arr.begin()-1;
			if(pos >= 0){
				_2SAT::addedge(i.number+p, prefix_in[pos]);
				_2SAT::addedge(prefix_out[pos], i.number);
			}
		}
	}
	
	_2SAT::work();
	if(_2SAT::Illegal)
		puts("-1");
	else{
		int l =1, r =M;
		auto modify =[&](const int &_l, const int &_r){
			r =std::min(_r, r);
			l =std::max(_l, l);
		};
		auto cmp3 =[&](const node &A, const node &B){
			return A.number < B.number;
		};
		int cnt =0;
		
		sort(arr.begin(), arr.end(), cmp3);
		for(int i =1; i <= p; ++i)
			if(_2SAT::val[i])
				modify(arr[i-1].l, arr[i-1].r), ++cnt;
		write(cnt), putchar(' '), write(l), putchar('\n');
		for(int i =1; i <= p; ++i)
			if(_2SAT::val[i])
				write(i), putchar(' ');
	}
}
```

---

