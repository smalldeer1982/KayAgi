# [POI 2010] KOL-Railway

## 题目描述

**译自 POI 2010 Stage 1.「[Kolej](https://szkopul.edu.pl/problemset/problem/TJVrS_hRC8W5Q6ZBW6mETAIm/site/?key=statement)」**

一个铁路包含两个侧线 $1$ 和 $2$ ，左边由 $A$ 进入，右边由 $B$ 出去（如下图所示）。  

![](https://cdn.luogu.com.cn/upload/image_hosting/bdq72qy0.png)

有 $n$ 个车厢在通道 $A$ 上，编号为 $1$ 到 $n$ ，它们按照 $a_1,a_2,\cdots ,a_n$ 的顺序进入侧线，想要按照 $1,2,\cdots ,n$ 的顺序从通道 $B$ 出去。    
他们可以从 $A$ 到 $1$ 或 $2$ ，然后经过一系列转移从 $B$ 出去（不用考虑容量问题）。求是否能够做到，如果可以，请找出一种方案。

## 样例 #1

### 输入

```
4
1 3 4 2```

### 输出

```
TAK
1 1 2 1```

# 题解

## 作者：kczno1 (赞：9)

noip双栈排序加强版。

如果存在k使得ak<ai<aj且k>j>i，那么i,j不能入一个栈。

i<->j连一条边，之后跑二分图染色，优先给小的染黑色，表示进第一个栈。

我们可以预处理m[i]=min{a[i+1..n]}

对每个j，找ai<aj且ai>m[j]的。

然而我们不能把边都连出来，因为会是n^2。

我们想办法只连出一些生成树，染色之后模拟判断一下行不行。

方法就是每连了两个块就并成一个块，并且用可并堆维护块内最小ai。

因为m是单调增的，如果最小ai<=m，就弹出。

之后我们再用一个堆维护所有块里面最小ai最小的块，每次取出，如果满足ai<aj就连边，合并。

时间nlogn。

(好久没打堆了233)

```cpp
#include<cstdio>
#include<algorithm> 
using std::swap;

#define ch_top 10000000
char ch[ch_top],*now_w=ch-1;
#define print(x) *++now_w=x;
#define chmin(x,y) {if(x>y)x=y;}
#define N 101000
int a[N],m[N];//m[i]=i->n min 
int t[N];
struct edge
{
    int to,next;
}l[10000000];int e;
#define add_e(x,y) l[++e]=(edge){y,t[x]};t[x]=e;
bool vis[N],col[N];//col[i]=1 第一个栈 
int q1[N],t1,q2[N],t2;

int n;
int head[N],next[N];
int h[N<<1],top;

void dfs(int x,bool now)
{
    if (vis[x])
    {
     if (col[x]!=now) {puts("NIE");exit(0);}
    }
    else
    {
        vis[x]=1;col[x]=now;
    for (int i=t[x];i;i=l[i].next) dfs(l[i].to,now^1);
    }
}

void move()
{
    for (int i=1,j;(j=i<<1)<=top;)
    {
        if (j<top&&a[h[j]]>a[h[j+1]]) ++j;
        if (a[h[i]]<a[h[j]]) break ;
        swap(h[i],h[j]);i=j;
    }
}

void push(int x)
{
    h[++top]=x;
    for (int i=top,j;i>1;)
    {
      if (a[h[i]]>=a[h[j=i>>1]])  break;
      swap(h[i],h[j]);i=j;
    }
}

void merge(int &x,int y)
{
    if (a[x]<a[y])
    {
        next[y]=head[x];head[x]=y;
    }
    else
    {
        next[x]=head[y];head[y]=x;
        x=y;
    }
}

void merges(int &x)
{
    int y=next[x],r;
    while (y)
    {
        r=next[y];
        merge(x,y);
        y=r;
    }
    next[x]=0;
}

int main()
{
    freopen("1.in","r",stdin);
    int i,j;
    scanf("%d",&n);
    for (i=1;i<=n;++i) {scanf("%d",a+i);m[i]=a[i];}
    for (i=n;--i;) chmin(m[i],m[i+1])
    h[top=1]=1;
    a[0]=N+1;
    m[n+1]=N;
    int p;
    for (i=2;i<=n;++i)
    {
        int rt=i;
        for (;a[p=h[1]]<a[i];)
        {
          while (a[p]<=m[i+1]) 
            merges(p=head[p]);
          if(a[p]<a[i]) {add_e(i,p);add_e(p,i);merge(rt,p);h[1]=h[top--]; }
          else h[1]=p;
          move();
        }
        push(rt);
    }
    int now=1;
    print('T') print('A') print('K') print('\n')
    for (i=1;i<=n;++i)
    {
        if (!vis[i]) dfs(i,1);
        if (col[i]) {q1[++t1]=i;print('1') }
        else {q2[++t2]=i;print('2') }
        print(' ')
        while (a[q1[t1]]==now||a[q2[t2]]==now)
        {
            if (a[q1[t1]]==now++) {  --t1; }
            else {  --t2; }
        }
    }
    if (now<=n) puts("NIE");
    else fwrite(ch,1,now_w-ch,stdout);
}
```

---

## 作者：Ameiyo (赞：4)




# 神题。。。

从各处都可以看到 __双栈排序__ 这个名词

总而言之就是两个栈，给出入栈序列，要求出栈序列有序。

---

### 挖掘性质

首先能发现两个性质

（在下面我称第 $ i $  辆入栈的车的编号为第 $ i $ 个下标上的值，即第 $ i $ 个元素）

>一个元素入栈的时候，他所进入的栈的栈顶元素必大于他。

否则那个元素就不能在他出栈前出栈，也就不满足出栈序列有序。

还有

>一个元素会被比他小的元素“卡”住不出栈，因为要有序。

那么在一个元素入栈之后，出栈之前，所有比他大的元素都不能和他在一个栈中。

同样的，对于某个元素 $ Ele[i] $ 来说，在他入栈的时候，设已经出栈的元素中最大值为 $ Mx $  ，那么 $ Ele[i] $ 肯定不能与 $ [Mx + 1, Ele[i] - 1] $ 中已经入栈的元素处于同一个栈中，也就是对于满足 $ v | v \in [Mx + 1, Ele[i] - 1] $ 且 $ v $ 的入栈时间小于 $ i $ 的 $ v $ 来说，$ ans[v] \ne ans[Ele[i]] $ 。

---

### 深入思考

我们发现得到的关系是答案的不同，于是就变成了一个染色问题（其实也是二分图，但并没有什么关系），同一条边连接着的两个元素的答案必不同。

上述两种关系其实是完全对应的，只不过一种是从前往后连，一种是从后往前连。

而染色关系事实上是无向边，既然两种关系都是对应的，那么每次只连有向边就可以满足了。

因为在一个元素的答案对前面没有影响时，可能对后面的元素有影响，反之亦然，所以只连一种边会导致答案的判断出现问题。

---

### 如何实现？

在连了无向边之后，不在同一个连通块的点之间没有任何关系，所以如果用深搜来染色，那么循环时每碰到一个空白点就直接随便染就行了。

但是如果直接暴力深搜，那么复杂度就变成了边的数量（很显然怎么卡都可以 TLE )，是不可取的。

（所以存边也成为了不可能）

---

### 进一步优化

对于我们构建出的边来说，这些关系是必须满足的，那么每个连通块中颜色的对应性也就是确定的。

我们用 $ ans[i] $ 表示每个点第一次被搜到时所染的颜色，因为对应关系已经确定，所以对于某些边来说，$ i $ 只能是 $ ans[i] $ 这个颜色。

那么只要在最后判断一下按照 $ ans[i] $ 入栈是否可行即可。因为不可行就做不到全部满足了。

这样每个点就之会被染一次。

---

### 还有最重要的一部分

接着考虑连边。

我们再次审视一下要连的两种边。

> 1. 在值域 [L, R] 中查询入栈时间小于 i 的元素，与其连边
>
> 2. 在下标 [L, R] 中查询值大于 Ele[i]  的元素，与其连边

所以我们可以维护两颗线段树，一颗值域，一颗下标，在 $ O(n) $ 的复杂度处理完两种边（询问）之后，直接深搜，搜一个点之前把他在两颗线段树中删掉，然后在对应的线段树上处理两种边，继续染色。

这样就保证了每个点值搜了一次，并且删了一次，查询与删除的复杂度都是 $ O(\log n) $ ，而预处理与最后判断的复杂度都是 $ O(n) $ ，所以最终的时间复杂度就是 $ O(n \log n) $ 。

---

因为有两种线段树，所以代码就会特别繁琐。。。而且查询是特殊的区间查询，所以有很多细节要注意。

```cpp
#define ll long long
#define reg register
#define rep(i, a, b) for (reg int i = (a), i##end = (b); i <= i##end; ++i)
#define dep(i, a, b) for (reg int i = (a), i##end = (b); i >= i##end; --i)

template <typename _typer> inline _typer read() {
	_typer init = 0;
	char ch = getchar(), k = 0;
	for ( ; !isdigit(ch); ch = getchar()) k = (ch == '-');
	for ( ; isdigit(ch); ch = getchar())
		init = (init << 3) + (init << 1) + (ch ^ 48);
	return k ? -init : init;
}
const ll N = 100005, INF = 1e9;

/*******************************************************************************
 *
 * 每个点只染一次，最后判断按照这样染行不行，只要保证染了的边是必须满足的即可
 * （或者说用来更新别的点的那些点不是随便的点）
 *
 * 有两种边，一种连向 i 前面，这种边连向所有在栈里而且值小于 A[i] 的点
 * （在值域中找下标）
 * 另一种边连向 i 后面，这种边连向所有在 i 这个点走之前入栈而且值大于 A[i] 的点
 * （在下标中找值）
 *
 * 这样对于每个点就有了两组边，我们可以用两颗线段树查询（类型见上）
 *
 * 然后直接深搜来染色，下个要找的点由线段树上查询得到，在线段树上找到了就直接删
 * 掉 （两棵都要删），这样就保证了每个点只会找一次，找点的复杂度是 logn ， 所以
 * 总复杂度就是 O(nlogn)
 *
 * 最后直接按照染下来的一个个入栈，判断是否可行，因为此时没染色的点都是不影响任
 * 何一个点的，所以这时的情况是必须满足的（否则如果一个点会影响别的点，就会有别
 * 的点来染他，因为边是双向的）
 *
 * （最后的情况可以粗略的理解为没有联通在一起的点就是不同的联通块，属于不同联通
 * 块的点之间没有任何关系，所以可以随便放在任何一个栈中）
 *
 * ps:本来想封装的，结果发现封装也没有特别好打，就放弃了
 *
 ******************************************************************************/

int n;
// 序列及答案
int Element[N], ans[N];
// 入栈时间、出栈时间及已经出栈的最大的点
int IntoStackTime[N], OutStackTime[N], HaveOutMx;
int Valque[2][N], Timque[2][N];

// Val 值域线段树：支持 [L, R] 查询出栈时间小于 id  的点
// Tim 下标线段树：支持 [L, R] 查询值(编号)大于 val 的点

int Mx[N << 2], Mi[N << 2], Cntmx[N << 2], Cntmi[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)
void Up_mx(int p) {
	Mx[p] = 0;
	if (Cntmx[ls]) Mx[p] = Mx[ls];
	if (Cntmx[rs] && Mx[rs] > Mx[p]) Mx[p] = Mx[rs];
	Cntmx[p] = Cntmx[ls] + Cntmx[rs];
}
void Up_mi(int p) {
	Mi[p] = INF;
	if (Cntmi[ls]) Mi[p] = Mi[ls];
	if (Cntmi[rs] && Mi[rs] < Mi[p]) Mi[p] = Mi[rs];
	Cntmi[p] = Cntmi[ls] + Cntmi[rs];
}
void Built(int p, int l, int r) {
	if (l == r) {
		Mx[p] = Element[l];       // l 这个下标的元素
		Mi[p] = IntoStackTime[l]; // l 这个值的出栈时间
		Cntmx[p] = Cntmi[p] = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	Built(ls, l, mid); Built(rs, mid + 1, r);
	Up_mi(p), Up_mx(p);
}

void Dfs(int, int) ;
void EraseVal(int p, int l, int r, int id) {
	if (l == r) {
		--Cntmi[p];
		return ;
	}
	int mid = (l + r) >> 1;
	if (id <= mid) EraseVal(ls, l, mid, id);
	if (id >  mid) EraseVal(rs, mid + 1, r, id);
	Up_mi(p);
}
void EraseTim(int p, int l, int r, int id) {
	if (l == r) {
		--Cntmx[p];
		return ;
	}
	int mid = (l + r) >> 1;
	if (id <= mid) EraseTim(ls, l, mid, id);
	if (id >  mid) EraseTim(rs, mid + 1, r, id);
	Up_mx(p);
}
void ValQuery(int p, int l, int r, int L, int R, int mi, int k) {
	if (!Cntmi[p] || Mi[p] > mi) return ;
	// 因为有可能是从第一种情况（递归时上两个 if ）递归下来的，所以不一定满足
	// 查询条件，如果这时候 l == r 就会查询到错误的点
	// （其实一开始在 if 时判了，但感觉没用又删掉了，结果就一直过不了。。。）
	if (l == r) {
		EraseTim(1, 1, n, IntoStackTime[l]);
		EraseVal(1, 1, n, l);
		return Dfs(l, k);
	}
	int mid = (l + r) >> 1;
	if (R <= mid) return ValQuery(ls, l, mid, L, R, mi, k);
	if (L >  mid) return ValQuery(rs, mid + 1, r, L, R, mi, k);
	if (Mi[ls] < mi && Cntmi[ls]) ValQuery(ls, l, mid, L, R, mi, k);
	if (Mi[rs] < mi && Cntmi[rs]) ValQuery(rs, mid + 1, r, L, R, mi, k);
}
void TimQuery(int p, int l, int r, int L, int R, int mx, int k) {
	if (!Cntmx[p] || Mx[p] < mx) return ;
	if (l == r) {
		EraseTim(1, 1, n, l);
		EraseVal(1, 1, n, Element[l]);
		return Dfs(Element[l], k);
	}
	int mid = (l + r) >> 1;
	if (R <= mid) return TimQuery(ls, l, mid, L, R, mx, k);
	if (L >  mid) return TimQuery(rs, mid + 1, r, L, R, mx, k);
	if (Mx[ls] > mx && Cntmx[ls]) TimQuery(ls, l, mid, L, R, mx, k);
	if (Mx[rs] > mx && Cntmx[rs]) TimQuery(rs, mid + 1, r, L, R, mx, k);
}

void Dfs(int u, int k) {
	ans[u] = k;
	if (Valque[0][u] <= Valque[1][u])
		ValQuery(1, 1, n, Valque[0][u], Valque[1][u], IntoStackTime[u], k ^ 1);
	if (Timque[0][u] <= Timque[1][u])
		TimQuery(1, 1, n, Timque[0][u], Timque[1][u], u, k ^ 1);
}

int Stk[2][N], Top[2];
bool Check() {
	Stk[0][0] = Stk[1][0] = INF;
	rep (i, 1, n) {
		rep (d, 0, 1)
			while (Top[d] && OutStackTime[Stk[d][Top[d]]] <= i) --Top[d];
		int id = ans[Element[i]];
		if (Stk[id][Top[id]] < Element[i]) return false;
		Stk[id][++Top[id]] = Element[i];
	}
	return true;
}

int main() {
	n = read<int>();
	rep (i, 1, n) {
		Element[i] = read<int>();
		OutStackTime [Element[i]] = i;
		IntoStackTime[Element[i]] = i;
	}
	rep (i, 1, n)
		OutStackTime[i] = max(OutStackTime[i - 1], OutStackTime[i]);

	rep (i, 1, n) {
		while (HaveOutMx <= n && OutStackTime[HaveOutMx] <= i) ++HaveOutMx;
		Valque[0][Element[i]] = HaveOutMx + 1;
		Valque[1][Element[i]] = Element[i] - 1;
		Timque[0][Element[i]] = i + 1;
		Timque[1][Element[i]] = OutStackTime[Element[i]] - 1;
	}

	Built(1, 1, n);

	memset(ans, -1, sizeof ans);
	rep (i, 1, n) if (ans[Element[i]] == -1) {
		EraseVal(1, 1, n, Element[i]);
		EraseTim(1, 1, n, i);
		Dfs(Element[i], 0);
	}

	if (!Check()) puts("NIE");
	else {
		puts("TAK");
		rep (i, 1, n) printf("%d%c", ans[Element[i]] + 1, " \n"[i == n]);
	}
	return 0;
}
```

(补题的时候就会喜欢用长变量名（因为用的是 nvim 所以不怎么麻烦），应该没有很难看吧。。。）

最后膜拜 [机房巨佬](https://www.luogu.org/space/show?uid=130740) 的思想 orzorzorz



---

## 作者：mRXxy0o0 (赞：3)

# 题目

双栈排序 $O(n\log n)$ 版，$O(n^2)$ 可过弱化版[P1155](https://www.luogu.com.cn/problem/P1155)。

# 分析

经过长时间的手玩数据，可以发现某些点不可能在同一个栈中，考虑总结一个规律。

对于下标 $i,j(1\le i<j\le n)$，若 $a_i>a_j$，由于栈是后进先出，$i,j$ 之间没有任何限制；若 $a_i<a_j$，则必然要在 $j$ 进入之前弹出 $i$，如果此时 $j$ 后面有 $a_k<a_i<a_j(i<j<k)$，$i$ 和 $j$ 的进出栈顺序发生了矛盾，那么 $i$ 和 $j$ 一定不能放在一个栈中。

形式化地，对于 $i<j<k$，若 $a_k<a_i<a_j$，则 $i$ 和 $j$ 在不同的栈内。

这一限制可以通过二分图体现出来，结合染色法判定，给未确定的点赋予较小的栈号即可在 $O(n^2+n+m)$ 时间内得出答案。

很明显无法通过，于是考虑优化。

## 优化建图

倒序枚举每个 $j$，维护后缀最小值 $mn$，值域在 $[mn+1,j-1]$ 之间且还没有枚举到的点与 $j$ 连边。

区间连边可以使用线段树优化建图，分为入树和出树彼此连边即可。

重点考虑如何只连未枚举到的点。每枚举到一个点，就把线段树上连接对应叶子节点的边删去。实现上，由于之前连的边使用了旧节点，所以应当把根到该叶子节点上的所有点更换成新的点。

关于最终的图上的结点个数，可以简单算出应为 $6.8\times10^6$ 左右，可能会稍卡空间，应当避免使用邻接表存图，链式前向星消耗更少。

建图上可以如图示建法，可以方便判断叶节点且减少点数。

![graph](https://cdn.acwing.com/media/article/image/2023/08/15/155587_0fb64d703b-屏幕截图-2023-08-15-222726.png)

## DFS 的细节

与一般的染色法判定不同，对于线段树上的辅助点，是不能有一个具体的颜色的，因为可能有很多路径需要经过它。

最初的想法是记录当前访问的点 $u$、上一个经过的叶子节点 $last$，是否访问的数组 $vis$。对于下一步要走的点 $v$，如果是叶子节点，就用 $last$ 和 $v$ 比较。反之，由于不知道 $v$ 之后会走到哪里，所以**不管有没有访问过**，都继续搜索 $v$。

很明显，时间直接爆炸，考虑对非叶节点 $v$ 做出限制。

可以发现，如果搜完了点 $v$，那么对于当前的 $last$，经过点 $v$ 可以访问的所有叶节点的颜色都与 $last$ 不同，那么相当于只有颜色与 $last$ 相同的可以满足二分图，不同的一定不行。可以把这个颜色记录在 $v$ 上。就可以保证每个点只经过一次。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int N(1e5+10),M(6e6+8e5+10);
int n,a[N],tot,h[M],ne[M<<1],e[M<<1],idx;
bitset<M>vis,co,fg;
struct node{
	int l,r,ii,oo;
}tr[N<<2];
inline void add(int u,int v){
	ne[++idx]=h[u],h[u]=idx,e[idx]=v;
}
inline void pushup(int u){
	add(tr[u].ii,tr[u<<1].ii),add(tr[u].ii,tr[u<<1|1].ii);
	add(tr[u<<1].oo,tr[u].oo),add(tr[u<<1|1].oo,tr[u].oo);
}
inline void build(int u,int l,int r){
	tr[u]=/**/{l,r};
	if(l==r){
		tr[u].ii=tr[u].oo=l;
		return ;
	}
	tr[u].ii=++tot;tr[u].oo=++tot;
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
inline void mdf(int u,int l,int r,int x){
	if(l<=tr[u].l&&tr[u].r<=r){
		if(tr[u].l!=tr[u].r||!fg[tr[u].l])
			add(x,tr[u].ii),add(tr[u].oo,x);
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) mdf(u<<1,l,r,x);
	if(r>mid) mdf(u<<1|1,l,r,x);
}
inline void upd(int u,int x){
	if(tr[u].l==tr[u].r) return ;
	int mid=tr[u].l+tr[u].r>>1;
	tr[u].ii=++tot;tr[u].oo=++tot;
	upd(x<=mid?u<<1:u<<1|1,x);
	if(tr[u<<1].l!=tr[u<<1].r||!fg[tr[u<<1].l])
		add(tr[u].ii,tr[u<<1].ii),add(tr[u<<1].oo,tr[u].oo);
	if(tr[u<<1|1].l!=tr[u<<1|1].r||!fg[tr[u<<1|1].l])
		add(tr[u].ii,tr[u<<1|1].ii),add(tr[u<<1|1].oo,tr[u].oo);
}
inline void dfs(int u,int la){
	vis[u]=1;
	if(u>n) co[u]=co[la];
	for(int i=h[u],v;i;i=ne[i]){
		v=e[i];
		if(v<=n){
			if(!vis[v]){
				co[v]=co[la]^1;
				dfs(v,v);
			}
			else if(la!=v&&co[v]==co[la]){
				puts("NIE");
				exit(0);
			}
		}
		else{
			if(!vis[v]){
				co[v]=co[la];
				dfs(v,la);
			}
			else if(fg[v]&&co[u]!=co[v]){
				puts("NIE");
				exit(0);
			}
		}
		if(u>n) fg[u]=fg[u]|fg[v];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	tot=n;
	build(1,1,n);
	for(int i=n,mn=2e9;i>=1;--i){
		if(a[i]<mn) mn=a[i];
		else if(mn<a[i]-1) mdf(1,mn+1,a[i]-1,a[i]);
		fg[a[i]]=1;
		upd(1,a[i]);
	}
	for(int i=1;i<=n;++i)
		if(!vis[a[i]]) dfs(a[i],a[i]);
	puts("TAK");
	for(int i=1;i<=n;++i) printf("%d ",co[a[i]]+1);
	return 0;
}
```


---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://www.luogu.com.cn/problem/P3497)

NOIP2008提高T4加强版。

只有一个栈的情况是初学的时候就都学过的。考虑当时我们学习的时候，是怎么做的：

- 如果当前元素小于栈顶，直接加入
- 否则，如果栈顶是待输出序列里最小的，出栈；否则无解

可以抽象“无解”的情况：存在 $i<j<k$ 满足 $a_k<a_i<a_j$. 此时，由于要先出栈 $a_k$ 的缘故，$a_i$ 和 $a_j$ 在 $a_k$ 出栈前都应该在栈中，而 $a_j$ 又更靠近栈顶，无法让 $a_i$ 先出栈。

显然这是单栈的情况。我们将其推广到双栈，发现一样成立。只不过变成了 $i,j$ 不能进入一个栈中。

那我们显然可以暴力连边判断其是否是二分图。

简单说明如果是二分图则一定有解这个事实。

容易发现必要性比较好说明。充分性不是很好说明，（一般情况下感性理解一下就行了），考虑栈排序的这样一个事实：一个栈排序合法等价于任意时刻两栈都是单调（递减）栈。 容易说明其充要性。所以我们只需要能构造出一个方案使得两个栈始终为单调栈即可。容易构造出一个过程：

- 如果当前加入元素是待输出序列里最小的，随便加一个栈出栈
- 否则一定存在一个栈中的末尾元素 $a_i$，当前加入元素 $a_j$，待输出序列里最小的（一定在 $j$ 之后）元素 $a_k(i<j<k)$，一定有 $a_i>a_j,a_j<a_k$。直接推入 $a_j$ 即可。如果不存在这样的 $a_i$，则说明 $a_j$ 在二分图染色的过程中就已经失败了，矛盾。

~~根据个人理解口胡的构造方法，假了轻喷。~~

好，这样就可以 $O(n^2)$ 暴力连边，$O(n^2)$ dfs 判断是否是二分图。就可以通过 NOIP 的那道题。至于构造答案，首先染色的时候，优先把小的点尽可能放进第一个栈。最后模拟的时候，依次检查四种操作是否能做即可。

看上去，这已经无法再优化了。毕竟建图的 $O(n^2)$ 是摆脱不掉的。

这个时候，就有一个很妙的 trick：考虑到我们只关注最后的染色方案。那么对于图中的每个连通块，我们从中只要都抽出一颗生成树，就已经可以知道所有点的染色方案，最后模拟的时候判断其是否合法即可。而如果我们保留原（二分？）图的生成森林。则边数立马降到 $O(n)$ 级别。

考虑每次从待选点集中找到一个 $v$ 使得和当前点 $(u,v)$ 有连边，然后 dfs $v$ 点，同时从待选点集中删除 $v$。 这样一个过程就实现了上面的算法。发现瓶颈主要在从待选点集中删除 $v$，还有从待选点集中寻找 $v$。 由于从待选点集中删除这个要求，我们大胆猜想其是 polylog 的（就算现在猜不中也没关系（雾））。

考虑 $i-j$ 连边是这样的：
$$
\begin{cases}
i<j<lim(i) \\
a_i<a_j
\end{cases}
$$
其中 $lim(i)$ 是 $max\{j | a_j<a_i\}$.

但是这还不够，如果我们不暴力找到所有 $(i,j)$. 就必须考虑 $i$ 向后连和向前连两个方向，考虑把上面的东西逆过来：
$$
\begin{cases}
low(i) \lt a_j \lt a_i 
\\
j<i
\end{cases}
$$
其中 $low(i)$ 是 $\min\{j|a_j<a_i,i<j\}$.

容易发现一个下标内查值，一个值域内查下标，两颗线段树维护即可。

同时发现删除也很好维护。

至于查值，对于第一类边，在下标区间内不断查最大值即可；对于第二类边，在值域区间内不断查最小的下标即可。不满足就 break 掉。

时间复杂度：$O(n \log n)$.

```C++
//POI,2010
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,INF=1e9;
int n,a[MAXN],color[MAXN];
int st1[MAXN],st2[MAXN],top1,top2,cnt,cur,flag;
pi lim[MAXN]; //lim[i]=max{j|aj<=ai} 
struct Tree{
	pi minn[MAXN<<2],maxn[MAXN<<2];
	void pushup(int x){
		minn[x]=min(minn[lc(x)],minn[rc(x)]);
		maxn[x]=max(maxn[lc(x)],maxn[rc(x)]);
	}
	void build(int x,int l,int r){
		if(l==r){
			minn[x]=mp(INF,l);
			maxn[x]=mp(-INF,l);
			return;
		}
		int mid=(l+r)>>1;
		build(lc(x),l,mid);build(rc(x),mid+1,r);
		pushup(x);
	}
	void update(int x,int l,int r,int pos,int val){
		if(l==r){minn[x]=maxn[x]=mp(val,pos);return;}
		int mid=(l+r)>>1;
		if(pos<=mid)update(lc(x),l,mid,pos,val);
		else update(rc(x),mid+1,r,pos,val);
		pushup(x);
	}
	void modify(int x,int l,int r,int pos){
		if(l==r){minn[x]=mp(INF,0);maxn[x]=mp(-INF,0);return;}
		int mid=(l+r)>>1;
		if(pos<=mid)modify(lc(x),l,mid,pos); 
		else modify(rc(x),mid+1,r,pos);
		pushup(x);
	}
	void del(int x){modify(1,1,n,x);}
	pi minquery(int x,int l,int r,int ql,int qr){
		if(ql>qr)return mp(INF,0);
		if(ql<=l && qr>=r)return minn[x];
		pi ret=mp(INF,0);
		int mid=(l+r)>>1;
		if(ql<=mid)ret=min(ret,minquery(lc(x),l,mid,ql,qr));
		if(qr>mid)ret=min(ret,minquery(rc(x),mid+1,r,ql,qr));
		return ret;
	}
	pi maxquery(int x,int l,int r,int ql,int qr){
		if(ql>qr)return mp(-INF,0);
		if(ql<=l && qr>=r)return maxn[x];
		pi ret=mp(-INF,0);
		int mid=(l+r)>>1;
		if(ql<=mid)ret=max(ret,maxquery(lc(x),l,mid,ql,qr));
		if(qr>mid)ret=max(ret,maxquery(rc(x),mid+1,r,ql,qr));
		return ret;
	}
}bucket,tree1,tree2;
void dfs(int u,int c){
	color[u]=c;
	//del u
	tree1.del(u);
	tree2.del(a[u]);
	//front edge 
	int L=u,R=lim[u].fr; 
	while(1){
		int v=tree1.maxquery(1,1,n,L+1,R-1).se;
		if(v==0 || a[u]>=a[v])break;
		dfs(v,-c);
	}
	//back edge
	L=lim[u].se,R=a[u];
	while(1){
		int v=tree2.minquery(1,1,n,L+1,R-1).fr;
		if(v==INF || v>=u)break;
		dfs(v,-c);
	}
}
int main(){
	cin>>n;
	rep(i,1,n){
		cin>>a[i];
	}
	bucket.build(1,1,n);
	tree1.build(1,1,n);
	tree2.build(1,1,n);
	per(i,n,1){
		bucket.update(1,1,n,a[i],i);
		lim[i].fr=bucket.maxquery(1,1,n,1,a[i]).fr;
		lim[i].se=((i==n)?a[i]:min(lim[i+1].se,a[i]));
	}
	rep(i,1,n){
		tree1.update(1,1,n,i,a[i]);
		tree2.update(1,1,n,a[i],i);
	}
	rep(i,1,n){
		if(color[i])continue;
		dfs(i,1);
	}
	rep(i,1,n)if(color[i]==-1)color[i]=2;
	//模拟过程，判断是否合法
	cur=flag=1;
	while(cnt!=n){
		if(color[cur]==1 && cur<=n){
			if(top1==0 || a[cur]<st1[top1]){
				st1[++top1]=a[cur];
				cur++;
				continue;
			}
		}
		if(top1 && st1[top1]==cnt+1){
			top1--;
			cnt++;
			continue;
		}
		if(color[cur]==2 && cur<=n){
			if(top2==0 || a[cur]<st2[top2]){
				st2[++top2]=a[cur];
				cur++;
				continue;
			}
		}
		if(top2 && st2[top2]==cnt+1){
			top2--;
			cnt++;
			continue;
		}
		flag=0;break;
	}
	if(!flag)return printf("NIE\n"),0;
	printf("TAK\n");
	rep(i,1,n)printf("%d ",color[i]);
	return 0;
}

```



---

## 作者：qzhwlzy (赞：2)

### 题目大意

给定一个 $1\sim n$ 的排列 $p$。现在要对其进行双栈排序，即，有两个栈 $s_1$ 和 $s_2$，有四种操作：将原序列头入栈 $s1$、栈 $s1$ 顶弹出到最终序列、将原序列头入栈 $s2$、栈 $s2$ 顶弹出到最终序列，使得最终序列升序排列。求字典序最小的入栈方案（弱化版在 [P1155 [NOIP2008 提高组] 双栈排序](https://www.luogu.com.cn/problem/P1155)）。

### 思路

首先我们先考虑只有一个栈时的情况。此时要想完成排序，必须满足在任意数 $x$ 进栈时，栈顶都大于 $x$，或者小于 $x$ 的那些数刚好可以弹出进入最终序列。换句话说，若 $\exists i<j<k,p_k<p_i<p_j$，那么原序列无法排序，因为 $p_j$ 进栈时，一定要把 $p_i$ 弹出，但是此时小于 $p_i$ 的 $p_k$ 尚未入栈，所以最终序列无法有序（下称这样的 $i$ 和 $j$ 是冲突的）。不难证明此为原序列能排序的充要条件。

那么，在双栈的前提下，原来不能进同一个栈的 $p_i$ 和 $p_j$ 可以进入两个栈分别操作，使得排序成为可能。于是假设我们可以将 $p$ 划分为两个子序列，且子序列内部没有冲突，那么原序列有解。所以，发现我们可以将冲突的 $i$ 和 $j$ 连边，然后判断其是否是一张二分图。若是，则可以进行这样的划分，也就说明原序列有解；否则无法划分，一定会产生冲突，原序列也就无解。

此时，连边操作是 $\mathcal{O}(n^2)$ 的（处理后缀最小值 $min_x = \min\limits_{i=x}^n p_i$，若有 $i,j$ 满足 $min_{j+1} < p_i < p_j$ 且 $i<j$ 则 $i,j$ 冲突），染色也是 $\mathcal{O}(n^2)$ 的，最后的模拟过程~~应该~~是 $\mathcal{O}(n)$ 的，所以总复杂度 $\mathcal{O}(n^2)$，能过弱化版（染色方法见后文）。

---

接下来考虑优化。我们发现瓶颈主要在建边和染色上，而 $\mathcal{O}(n^2)$ 的算法中，我们用二重循环枚举点对 $(i,j)$，~~效率极高~~。接下来考虑如何优化掉。

首先，我们发现，可以把判断无解的情况交给 $\mathcal{O}(n)$ 的模拟来判断，也就是说，开始染色时可以不管矛盾的地方，最后在模拟排序过程时遇到矛盾再判断无解，这样也能顺利判断原序列是否有解。这样，我们染色时就不用遍历每一条边，只用找出原图的一棵生成森林即可（因为此时每个点都已经被染了色），此时遍历的复杂度就到了 $\mathcal{O}(n)$ 的级别。

但是如何找出这样一棵生成森林呢？发现只要能处理出每个点要连向的所有点，就可以 BFS 解决。而一个点 $i$ 连的边有两种，一种连向前面的点（前向边），一种连向后面的（后向边）。即若 $i$ 要连向 $j$，当且仅当满足 $\exists k$，使得 $\begin{cases}j<i<k\\p_k<p_j<p_i\end{cases}$ 或 $\begin{cases}i<j<k\\p_k<p_i<p_j\end{cases}$。

先考虑前向边，即满足 $\begin{cases}j<\color{red}i\color{defalt}<k\\p_k<p_j<\color{red}p_i\end{cases}$ 的 $j$。发现在下标上，$j$ 和 $k$ 不互相限制，而值域上 $p_j$ 受 $p_k$ 限制。那么，对这个 $i$，我们不妨找出最小的 $p_k$（令 $le_i$ 等于此时的 $k$），那么所有满足 $p_j\in(p_k,p_i)$（即 $p_j\in(p_{le[i]},p_i)$）且 $j<i$ 的 $j$ 都是 $i$ 的连边对象。因此我们可以开一棵维护权值的线段树，不断找 $(p_k,p_i)$ 之间最小的 $j$ 并向其连边，同时在线段树上删了 $j$ 点以防止建不必要的边，直至 $j\ge i$。

同理考虑后向边，即满足 $\begin{cases}\color{red}i\color{defalt}<j<k\\p_k<\color{red}p_i\color{defalt}<p_j\end{cases}$ 的 $j$。同理，此处 $j$ 的限制在下标，所以处理出最大的 $k$ 满足 $p_k<p_i$（令 $ri_i$ 等于此时的 $p_k$），那么所有满足 $j\in(i,k)$ 且 $p_j>p_i$ 的 $j$ 也都是 $i$ 的连边对象。因此再开一棵维护下标的线段树，不断找 $(i,k)$ 内最大的 $p_j$，向对应的 $j$ 连边，并删除 $j$ 对应的点，直至 $p_j\le p_i$。

因为每找到一个点都会删掉，所以找到的边集就是原图的生成森林（找的时候顺便染色），此时复杂度是 $\mathcal{O}(n\log n)$，可以过此题。

---

最后考虑一下模拟过程，以 NOIP 那题为例，优先级为 $push1>pop1>push2>pop2$。所以从前往后遍历 $p$，若遍历到的 $p_i$ 不能入栈（栈顶小于 $p_i$），则不断弹出直至可以入栈。之后如果是栈 $s_1$ 则直接入栈，否则由于 $pop1>push2$，先判断 $s_1$ 能否继续弹出再入栈。在过程中一旦有矛盾就报告原序列无解。

---

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define maxn 100005
#define inf 2100000000
using namespace std;
int n,p[maxn],col[maxn],pos[maxn],s[3][maxn],ppos=1,len,le[maxn],ri[maxn]; bool flag=1; char ans[maxn*2]; queue<int> q;
// le[i] <- k : maximum k satisfying p[k]<i   ri[i] <- p[k] : minimum p[k] satisfying k>i
struct seg_tree{int l,r,val;}a[3][maxn*8]; // a1 : position--maximum value   a2 : value--minimum position
int cmp(int p1,int p2,int typ){return (typ==1?max(p1,p2):min(p1,p2));}
void update(int typ,int p,int l,int r,int pos,int val){
	a[typ][p].l=l; a[typ][p].r=r; if(l==r){a[typ][p].val=val; return;}
	if(pos<=(l+r)/2) update(typ,p*2,l,(l+r)/2,pos,val); else update(typ,p*2+1,(l+r)/2+1,r,pos,val);
	a[typ][p].val=cmp(a[typ][p*2].val,a[typ][p*2+1].val,typ);
}
int query(int typ,int p,int l,int r){
	if(l>r) return (typ-1)*inf; if(l<=a[typ][p].l&&r>=a[typ][p].r) return a[typ][p].val; int res=(typ-1)*inf;
	if(l<=a[typ][p*2].r) res=query(typ,p*2,l,r); if(r>=a[typ][p*2+1].l) res=cmp(res,query(typ,p*2+1,l,r),typ); return res;
}
void bfs(int x){
	q.push(x); col[x]=1; update(1,1,1,n,x,-inf); update(2,1,1,n,p[x],inf); /*delete x*/ while(!q.empty()){
		int top=q.front(); q.pop(); while(1){
			int res=query(2,1,le[top]+1,p[top]); if(res>=top) break; q.push(res);
			col[res]=3-col[top]; update(1,1,1,n,res,-inf); update(2,1,1,n,p[res],inf);
		} while(1){
			int res=query(1,1,top,ri[top]-1); if(res<=p[top]) break; q.push(pos[res]);
			col[pos[res]]=3-col[top]; update(1,1,1,n,pos[res],-inf); update(2,1,1,n,res,inf);
		}
	}
}
int main(){
	scanf("%d",&n); for(int i=1;i<=n;i++){scanf("%d",&p[i]); pos[p[i]]=i; update(1,1,1,n,i,p[i]); update(2,1,1,n,p[i],i);}
	le[n]=inf; for(int i=n-1;i>=1;i--) le[i]=min(le[i+1],p[i+1]);
	ri[pos[1]]=-inf; for(int i=2;i<=n;i++) ri[pos[i]]=max(ri[pos[i-1]],pos[i-1]);
	for(int i=1;i<=n;i++) if(!col[i]) bfs(i);
	for(int i=1;i<=n;i++){
		int id=col[i]; while(s[id][0]&&s[id][s[id][0]]<p[i])
			if(s[1][s[1][0]]==ppos){ans[++len]='b'; s[1][0]--; ppos++;}
			else if(s[2][s[2][0]]==ppos){ans[++len]='d'; s[2][0]--; ppos++;}else{printf(/*"0"*/"NIE"); return 0;}
		if(id==2) while(s[1][0]&&s[1][s[1][0]]==ppos){ans[++len]='b'; s[1][0]--; ppos++;}
		ans[++len]=(id==1?'a':'c'); s[id][++s[id][0]]=p[i];
	} while(s[1][0]||s[2][0]) if(s[1][s[1][0]]==ppos){ans[++len]='b'; s[1][0]--; ppos++;}
		else if(s[2][s[2][0]]==ppos){ans[++len]='d'; s[2][0]--; ppos++;}else{printf(/*"0"*/"NIE"); return 0;}
	/*for(int i=1;i<=len;i++) printf("%c ",ans[i]);*/ printf("TAK\n"); for(int i=1;i<=n;i++) printf("%d ",col[i]); return 0;
}

```

---

## 作者：chroneZ (赞：1)

很显然的一件事情是，两个栈在任意时刻都需要从底到顶单调递减。简单推广一下，如果一个顺序对的第一个元素在第二个元素准备入栈前未弹出，那么这两个元素不能进入同一个栈。第一个元素能出栈的必要条件是所有小于它的元素都已出栈，因此，对于一对 $i < j, a_i < a_j$，如果存在 $k$ 使得 $j < k \land a_k < a_i$，那么 $i, j$ 一定不会进入同一个栈。

因此对这样的 $i, j$ 连一条边，则可行的一个必要条件为，最后形成的图是二分图。

关于充分性，考虑构造证明。

> 首先根据二分图对所有的点进行染色，每个点的颜色决定其对应的元素应该进入哪个栈。
>
> 如果一个元素进栈时栈顶元素大于它，那么直接进栈。否则，不断弹出栈顶直至栈空或栈顶元素小于它。
>
> 在弹出一个元素之前，如果另一个栈的栈顶更小，那么先弹出另一个栈的栈顶。
>
> 最终如果有元素仍未弹出，按照递增的顺序弹出即可。接下来我们要证明这种方案下弹出的排列是递增的。
>
> 由于任意时刻栈都应从底向顶递减，因此只需证明弹出一个元素时所有小于它的元素都已入栈。
>
> 由于两个元素能入同一个栈且满足 $i < j, a_i < a_j$，因此未入栈元素一定都大于 $a_i$。如果有其它栈顶的元素因为 $a_i$ 出栈被弹出，显然未入栈元素也都大于它们。$\square$

因此，若最终形成的图是二分图，则这个序列可被双栈排序。

判定二分图可以用染色实现，对于字典序最小的入栈序列，只需在二分图染色时将每个连通块的最小下标染成 $1$ 即可。

但是直接做的话边数是 $\Theta(n ^ 2)$ 的，考虑优化。

考虑记 $S_i = \min \limits_{j > i} a_j, f_i = \max \limits_{S_j < a_i} (j)$，那么对于每个 $i$，能与之连边的 $j$ 在区间 $[i + 1, f_i]$ 中。也就是说，$(i, j)$ 连边当且仅当 $j \in [i + 1, f_i], a_i < a_j$。（直接做貌似有主席树建图的做法，但不是我的做法。）

考虑如果最终的图是二分图，那么它的染色方案是固定的。因此我们可以只取该图的一个生成森林，染完色后判定是否合法。

判定是否合法是容易的，可以按 $a_i$ 从小到大考虑，支持查询区间颜色是否相同，单点去掉一个颜色。

求生成森林反而有点麻烦。暴力是简单的，遍历区间，若 $a_i < a_j$ 且 $i$ 与 $j$ 非同一连通块则连边。考虑 $a_i < a_j$ 这个限制，可以通过从小到大考虑 $a_i$，并在处理完一个数后去掉这个数，那么就可以忽略 $a_i < a_j$ 的限制。这可以简单地用链表 / 并查集实现，作者用了并查集，称此为并查集一。

观察到这样做之后每个区间都会位于同一个连通块，因此我们再用一个并查集维护每个连续段的最右端点即可，称此为并查集二。细节大概就是从 $i + 1$ 开始，每次先跳到并查集一的最右端点，判断是否加边，然后跳到并查集二的最右端点，合并该点与下一个位置，具体可见代码。

总时间复杂度 $\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e5 + 10;
int n, a[N], s[N], f[N];

struct DSU {
  int f[N];
  inline void init(int n) {
    for(int i = 1; i <= n; i++) {
      f[i] = i;
    }
  }
  inline int find(int x) {
    while(x != f[x]) {
      x = f[x] = f[f[x]]; 
    }
    return x;
  }
  inline void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) {
      return;
    }
    f[fy] = fx;
  }
  inline bool same(int x, int y) {
    return find(x) == find(y);
  }
} d1, d2, d3;

vector<int> T[N];
int col[N]; 

inline void dfs(int u, int father) {
  for(auto v : T[u]) {
    if(v == father) {
      continue;
    }
    col[v] = col[u] ^ 1;
    dfs(v, u);
  }
}

struct Info {
  int C; bool S; bool Sp;
  inline friend Info operator + (Info x, Info y) {
    if(x.Sp && y.Sp) {
      return {-1, 1, 1};
    }
    if(x.Sp) {
      return y;
    }
    if(y.Sp) {
      return x;
    }
    if(x.C == y.C && x.S && y.S) {
      return {x.C, 1};
    } else {
      return {-1, 0};
    }
  }
};
struct SegmentTree {
  Info t[N << 2];
  inline void modify(int k, int l, int r, int x, int v) {
    if(l == r) {
      t[k] = {v, 1, 0};
      return;
    }
    int mid = l + r >> 1;
    if(x <= mid) {
      modify(k << 1, l, mid, x, v);
    } else {
      modify(k << 1 | 1, mid + 1, r, x, v);
    }
    t[k] = t[k << 1] + t[k << 1 | 1];
  }
  inline void block(int k, int l, int r, int x) {
    if(l == r) {
      t[k] = {-1, 1, 1};
      return;
    }
    int mid = l + r >> 1;
    if(x <= mid) {
      block(k << 1, l, mid, x);
    } else {
      block(k << 1 | 1, mid + 1, r, x);
    }
    t[k] = t[k << 1] + t[k << 1 | 1];
  }
  inline Info query(int k, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
      return t[k];
    }
    int mid = l + r >> 1;
    if(y <= mid) {
      return query(k << 1, l, mid, x, y);
    } else if(mid < x) {
      return query(k << 1 | 1, mid + 1, r, x, y);
    } else {
      return query(k << 1, l, mid, x, y) + query(k << 1 | 1, mid + 1, r, x, y);
    }
  }
} tr;

int p[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  s[n] = 1e9;
  for(int i = n - 1; i >= 1; i--) {
    s[i] = min(s[i + 1], a[i + 1]);
  }
  iota(p + 1, p + n + 1, 1);
  sort(p + 1, p + n + 1, [&](int x, int y) {
    return a[x] < a[y];
  });
  for(int i = 1; i <= n - 2; i++) {
    int it = lower_bound(s + 1, s + n + 1, a[i]) - s; 
    f[i] = it - 1;
  }
  d1.init(n), d2.init(n + 1), d3.init(n + 1);
  for(int i = 1; i <= n; i++) {
    int it = p[i];
    for(int j = d2.find(it + 1); j <= f[it]; j = d2.find(j)) {
      if(!d1.same(it, j)) {
        d1.merge(it, j);
        T[it].push_back(j), T[j].push_back(it);
        // cout << it << " " << j << "\n";
      }
      if(j == f[it]) {
        break;
      }
      j = d3.find(j);
      if(j >= f[it]) {
        continue;
      }
      d3.merge(j + 1, j);
    }
    d2.merge(it + 1, it);
  }
  for(int i = 1; i <= n; i++) {
    col[i] = -1;
  }
  for(int i = 1; i <= n; i++) {
    if(col[i] == -1) {
      col[i] = 0;
      dfs(i, -1);
    }
    tr.modify(1, 1, n, i, col[i]);
  }
  bool fl = 1;
  for(int i = 1; i <= n; i++) {
    int it = p[i];
    if(it + 1 <= f[it]) {
      Info t = tr.query(1, 1, n, it + 1, f[it]);
      fl &= t.Sp || (t.S && t.C == (col[it] ^ 1));
    }
    tr.block(1, 1, n, it);
  }
  if(!fl) {
    cout << "NIE\n";
    return 0;
  }
  cout << "TAK\n";
  for(int i = 1; i <= n; i++) {
    cout << col[i] + 1 << " \n"[i == n];
  }
}
```

---

## 作者：langligelang (赞：0)

[传送门](https://www.luogu.com.cn/problem/P3497)

（前人之述备矣，只是提供一种题解区没有的建图方式，如果我这个前半部分看不懂可以看看前面佬的）

---

**analysis：**

单栈排序，会有栈内元素递减的性质；如果 $i < j, a_i > a_j$  ，并且还有 $j < k, a_k < a_i$ 让 $a_i$ 无法出栈，那么会NIE。

双栈排序也有上述性质，考虑相同的 $i, j, k$ 满足上述条件，则会导致 $a_i, a_j$ 不能同时放到一个栈中。

考虑直接连边，记 $f_i = \max \limits_{j = i, a_j < a_i} ^ {n} {j}, i \rightarrow \{ j | j \in[i + 1, f_i], j > i\}$ ，可以过掉 [NOIP2008双栈排序](https://www.luogu.com.cn/problem/P1155) ，然后考虑优化建边。

---

发现连边的条件是对”区间的值域后缀“连边，二维信息且一维为后缀形式，考虑建主席树，将下标放在线段树下标上，值放在版本上。

考虑二分图染色贪心（照搬），会发现一个问题，因为建单向边存在 $x$ 和 $y$ 的闭合子图中都有 $z$，但是可能在 $x < y$ 时染到 $x,z$，我们希望同时染上 $y$。

考虑建双向边，但边不太好建双向（本来 $O(n\log n)$ 空间就快炸了，两棵主席树可能不行）。

考虑其他办法，先不同时染 $y$，每次尝试染色，如果能够染较小的就染较小的颜色，如果都不行就判断NIE。

最后输出方案即可。

[code](https://www.luogu.com.cn/paste/18b436ks)

---

## 作者：Acoipp (赞：0)

给一种比较新颖且暴力的做法。

# **分析**



题面同 NOIP 双栈排序，即给定两个栈，你需要对每个元素依次选择它添加到哪个栈里面，最后存在一种出栈方式使得出栈元素依次为 $1 \sim n$。数据范围：$1 \le n \le 10^5$。

首先我们得知道对于两个元素在什么情况下不能放在一起，若这两个元素的下标为 $i,j$，那么若存在 $k$ 使得满足 $i<j<k$ 且 $a_k < a_i < a_j$，那么 $a_i,a_j$ 不能在一个栈里面。

证明很简单：如果它们放在一个栈，因为 $a_i<a_j$，那么 $a_i$ 一定在 $a_j$ 前出栈，又因为 $a_k < a_i$，那么 $a_k$ 一定在 $a_i$ 前出栈，又因为 $i<j<k$，所以 $a_i$ 在 $a_j$ 前入栈，$a_k$ 在 $a_j$ 后入栈，故在 $a_k$ 出栈前 $a_i$ 不能出栈，导致 $a_i$ 和 $a_j$ 不能按顺序出栈。

且其余情况肯定有解。

考虑在所有不能放在同一个栈的 $i,j$ 连一条边，那么最后二分图染色判定一下即可。

确保字典序最小则可以对于当前 $a_i$，如果没有染色，那么就优先加入到第一个栈，然后对于它所在连通块的二分图分类染色即可。

时间复杂度是：$O(n^2)$；空间复杂度是：$O(n^2)$。

接下来考虑优化：

我们发现对于每个 $i$，合法的 $j$ 一定在 $[i+1,k-1]$ 这个区间内，$k$ 是最大的不超过 $n$ 的满足 $\min_{l=k}^n a_l < i$ 的数字。如果不存在 $k$，那么 $j$ 也不存在。

这个区间可以通过二分求出来，然后我们需要将 $i$ 和 $j \in [i+1,k-1],a_i<a_j $ 连边。

因为这是一个区间，自然地想到了线段树优化建图。

因为同时满足两个信息，考虑通过排序减少一个信息，那么我们按 $a_i$ 的大小排序，大的在前面，小的在后面，每个线段树上的节点都连向它的儿子节点，如果是叶子节点就不用连。（叶子节点 $[s,s]$ 的编号就是 $s$）

这样的话对于每个 $a_i$ 找到与之对应的 $k$ 然后区间连边，再把 $a_i$ 加入进线段树就可以了。（线段树最开始是一棵空树）

下面是一些细节：

- 区间连边的时候从一个点向区间连边边权是 $1$，线段树上的区间向节点连边边权是 $0$。
- 最后需要统计二分图的时候判定会有所不同，边权为 $1$ 表示端点的值不同，否则相同。
- 因为线段树区间向点连边会默认所有边的边权都为 $0$，且所有点的所属栈都相同，我们就需要在某个点向线段树区间连边时候，将线段树所代表的区间设为“可经过”，最后跑二分图染色的时候只经过“可经过”的点就会保证答案没有问题。
- 一个线段树上的点一旦可经过，那么它的儿子节点肯定都可以经过，所以还要像区间赋值一样用 $lazy$ 标记来存一下。
- 最后因为线段树每个节点在不同时刻代表的区间不一样，所以要对每个节点重新编号，连边的时候就连重新编号的节点，每次添加进一个元素都要重新编号。

这样的话时间复杂度和空间复杂度就降为 $O(n \log n)$ 了。

# **代码**

```cpp
#include<bits/stdc++.h>
#define ll int
#define N 100005
using namespace std;
ll n,a[N],i,j,k,temp,vis[N<<7],vis2[N<<7],pos[N<<7],b[N],p[N],mid,l,r,tr[N<<7],lazy[N<<7],tr_tot;
ll la[N<<7],ne[N<<7],z[N<<7],tot,to[N<<7];
string s1,s2;
inline void merge(ll a,ll b,ll c){
	tot++;
	ne[tot] = la[a],la[a] = tot,to[tot] = b,z[tot] = c;
	tot++;
	ne[tot] = la[b],la[b] = tot,to[tot] = a,z[tot] = c;
}
void dfs(ll x){
	for(ll i=la[x];i;i=ne[i]){
		if(!pos[to[i]]) continue;
		if(vis[to[i]]){
			if(z[i]==0&&vis[to[i]]!=vis[x]) temp=1;
			if(z[i]==1&&vis[to[i]]==vis[x]) temp=1;
		}
		else{
        //对边权分类讨论
			if(z[i]==0) vis[to[i]]=vis[x];
			if(z[i]==1) vis[to[i]]=-vis[x];
			dfs(to[i]);
		}
	}
}
void dfs2(ll x){
	for(ll i=la[x];i;i=ne[i]){
		if(!pos[to[i]]) continue;
		if(vis2[to[i]]) continue;
		else{
			if(z[i]==0) vis2[to[i]]=vis2[x];
			if(z[i]==1) vis2[to[i]]=-vis2[x];
			dfs2(to[i]);
		}
	}
}
inline void pushdown(ll p){
	//lazy标记下传
	if(tr[2*p]) lazy[2*p] |= lazy[p],pos[tr[2*p]] |= lazy[p];
	if(tr[2*p+1]) lazy[2*p+1] |= lazy[p],pos[tr[2*p+1]] |= lazy[p];
	lazy[p] = 0;
}
void add(ll x,ll s,ll t,ll p){
	if(s==t){
		tr[p] = x;
		return ;
	}
	pushdown(p);
	if(x<=(s+t)/2) add(x,s,(s+t)/2,2*p);
	else add(x,(s+t)/2+1,t,2*p+1);
	tr[p] = ++tr_tot;   //重编号
   //树上连边权为0的边
	if(tr[2*p]) merge(tr[p],tr[2*p],0);
	if(tr[2*p+1]) merge(tr[p],tr[2*p+1],0);
}
void query(ll l,ll r,ll s,ll t,ll p,ll c){
	if(!tr[p]) return ;
	if(l<=s&&t<=r){
		lazy[p] = 1;
		pos[tr[p]] = 1;
		merge(tr[p],c,1);  //连边权为1的边。
		return ;
	}
	pushdown(p);
	if(l<=(s+t)/2) query(l,r,s,(s+t)/2,2*p,c);
	if(r>(s+t)/2) query(l,r,(s+t)/2+1,t,2*p+1,c);
}
void solve(ll l,ll r,ll c){
	if(l>r) return ;
	query(l,r,1,n,1,c);
   //此处是直接连边，但是如果l>r就不连。
}
void dfstr(ll s,ll t,ll p){
	pushdown(p);
	if(s==t) return ;
	dfstr(s,(s+t)/2,2*p),dfstr((s+t)/2+1,t,2*p+1);
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	tr_tot = n;
	for(i=1;i<=n;i++) cin>>a[i],b[a[i]]=i,pos[i]=1;
	p[n] = a[n];
	for(i=n-1;i>=1;i--) p[i]=min(p[i+1],a[i]);
	for(i=n;i>=1;i--){
		if(p[b[i]]<i){
			l=b[i],r=n;
			while(l<r){
				mid = (l+r+1)/2;
				if(p[mid]<i) l=mid;
				else r=mid-1;
			}
			solve(b[i]+1,l-1,b[i]);
		}
		add(b[i],1,n,1);
	}
	dfstr(1,n,1);
	for(i=1;i<=n;i++){
		if(!vis[i]){
			vis[i] = 1;
			dfs(i);
		}
	}
   //二分图判定
	if(temp){
		cout<<"NIE\n";
		return 0;
	}
	cout<<"TAK\n";
	for(i=1;i<=n;i++){
		if(!vis2[i]) vis2[i]=1,dfs2(i);
		if(vis2[i]==1) cout<<1<<" ";
		else cout<<2<<" ";
	}
	cout<<endl;
	return 0;
}
```

---

