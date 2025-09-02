# [ONTAK2015] Stumilowy sad

## 题目背景

Subtask 0 为原数据，Subtask 1 为 hack 数据。

## 题目描述

在一条笔直的道路上从左到右一共有 $n$ 片区域，每一片区域一开始都种着一棵树，其中第 $i$ 片区域种着高度为 $h_i$ 的树。接下来你需要处理 $q$ 个操作：

- `1 l r c`：将第 $l$ 片区域到第 $r$ 片区域内的所有树的高度拔高 $c$ 个单位。
- `2 l r h`：将一把刀固定在高度为 $h$ 的空中，对第 $l$ 片区域到第 $r$ 片区域内的所有树进行砍伐。
- `3 l r h`：往第 $l$ 片区域到第 $r$ 片区域内的每个区域种上一棵高度为 $h$ 的树。
- `4 l r`：查询第 $l$ 片区域到第 $r$ 片区域内最高的树的高度。

注：本题中的高度为相对于某个水平面的高度，也就是说**可能会有负数的出现**。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n, q \leq 5 \times 10^5$，$1 \leq h_i \leq 10^9$，$1 \leq l \leq r \leq n$，$0 \leq |c| \leq 500$，$1 \leq h \leq 10^9$。

## 样例 #1

### 输入

```
2 5
3 7
4 1 2
1 1 2 1
4 1 2
3 1 1 5
4 1 2```

### 输出

```
7
8
8```

# 题解

## 作者：BigSmall_En (赞：15)

## [LG8024 [ONTAK2015] Stumilowy sad](https://www.luogu.com.cn/problem/P8024) 题解

因为不会势能分析，不知道大部分题解的方法的复杂度是多少，于是写了一个严格 $O(n\log n)$ 的做法。

此外，这题不区间加和维护区间最大值的话就是[这题](https://www.luogu.com.cn/problem/P4560)。

### 题意

> 一个长度为 $n$ 的序列 $a$。进行 $4$ 种操作
>
> - 操作 $1$ ：将 $[l,r]$ 的所有数 $+c$
> - 操作 $2$ ：将 $[l,r]$ 的所有数对 $h$ 取 $\min$
> - 操作 $3$ ：将 $[l,r]$ 的所有数对 $h$ 取 $\max$
> - 操作 $4$ ：查询 $[l,r]$ 内数的最大值
>
> $1\leq n\leq 5\times 10^5,1\leq a_i\leq 10^9,0\leq |c|\leq 500,1\leq h\leq 10^9$

### 题解

对于这种题目一般考虑使用线段树。

对于线段树上的每一个节点，维护以下四个信息：

- $maxv$：即线段树上该线段覆盖的所有数的最大值。
- $tag$：维护区间加的懒标记，表示这个节点内的每个数 $+c$，但子树并没有更新这一信息。
- $ctag$：维护区间取 $\min$ 的懒标记，表示这个节点内的每个数对 $h$ 取 $\min$，但子树暂无更新此信息。
- $btag$：维护区间取 $\max$ 的懒标记，表示这个节点内的每个数对 $h$ 取 $\max$，但子树暂无更新此信息。

#### 1.建树

初始时所有节点的 $ctag=+\infty,btag=-\infty$，比较好理解。

```cpp
void buildtree(int p,int l,int r){
	t[p].left=l,t[p].right=r;//我的习惯写法，维护线段两端的位置，比较常规
	t[p].ctag=INF,t[p].btag=-INF;
	if(l==r){t[p].maxv=a[l];return;}
	int mid=(l+r)>>1;
	buildtree(ls,l,mid);buildtree(rs,mid+1,r);
	pushup(p);
}
```

#### 2.区间加

因为每个数都加 $c$，所以即使之前所有的数都对 $h$ 取了最大值或最小值，现在这个最大值或最小值也变成了 $h+c$。对于下传标记，就相当于都 $+c$。

```cpp
inline void pushtag(int p,ll x){
    t[p].maxv+=x;t[p].tag+=x;
    if(t[p].ctag<INF)t[p].ctag+=x;
    if(t[p].btag>-INF)t[p].btag+=x;
}
void update_plus(int p,int l,int r,ll c){
    if(l<=t[p].left&&t[p].right<=r)
        return pushtag(p,c),void();
    pushdown(p);
    if(l<=t[ls].right)update_plus(ls,l,r,c);
    if(r>=t[rs].left)update_plus(rs,l,r,c);
    pushup(p);
}
```

#### 3.区间取 $\min$

$maxv\gets \min(maxv,h)$ 和 $ctag\gets \min(ctag,h)$ 比较好理解。

对于 $btag$ 而言，如果 $btag>h$，那么取 $\max$ 变大的值也会对 $h$ 取 $\min$。如果 $btag<h$ 那么取 $\max$ 变大的值也不会因为对 $h$ 取 $\min$ 收到影响。（感觉在说废话，其实也很好理解）

```cpp
inline void pushctag(int p,ll x){
    t[p].maxv=min(t[p].maxv,x);
    t[p].btag=min(t[p].btag,x);
    t[p].ctag=min(t[p].ctag,x);
}
void update_cut(int p,int l,int r,ll h){
    if(l<=t[p].left&&t[p].right<=r)
        return pushctag(p,h);
    pushdown(p);
    if(l<=t[ls].right)update_cut(ls,l,r,h);
    if(r>=t[rs].left)update_cut(rs,l,r,h);
    pushup(p);
}
```

#### 4.区间取 $\max$

原理和区间取 $\min$ 类似。

```cpp
inline void pushbtag(int p,ll x){
    t[p].maxv=max(t[p].maxv,x);
    t[p].btag=max(t[p].btag,x);
    t[p].ctag=max(t[p].ctag,x);
}
void update_build(int p,int l,int r,ll h){
    if(l<=t[p].left&&t[p].right<=r)
        return pushbtag(p,h);
    pushdown(p);
    if(l<=t[ls].right)update_build(ls,l,r,h);
    if(r>=t[rs].left)update_build(rs,l,r,h);
    pushup(p);
}
```

#### 5.上传信息

```cpp
inline void pushup(int p){
	t[p].maxv=max(t[ls].maxv,t[rs].maxv);
}
```

#### 6.下传标记

原理就是用父亲节点的标记对子节点的每种信息分别进行修改，和修改操作相同，所以子操作也可以用三个修改函数（分别对应更新 $tag,ctag,btag$）来写，这样子代码量会大大减少，也会清晰很多。

```cpp
inline void pushdown(int p){
    pushtag(ls,t[p].tag);pushtag(rs,t[p].tag);
    pushbtag(ls,t[p].btag);pushbtag(rs,t[p].btag);
    pushctag(ls,t[p].ctag);pushctag(rs,t[p].ctag);
    t[p].tag=0,t[p].btag=-INF,t[p].ctag=INF;
}
```

#### 7.查询最大值

```cpp
ll query_max(int p,int l,int r){
	if(l<=t[p].left&&t[p].right<=r)
		return t[p].maxv;
	pushdown(p);ll tmp=-INF;
	if(l<=t[ls].right)tmp=max(tmp,query_max(ls,l,r));
	if(r>=t[rs].left)tmp=max(tmp,query_max(rs,l,r));
	return tmp;
}
```

------

完整代码就不贴了。

### 后记

之前题解有些地方格式和内容写错了，现已修改。

同时把代码改成了使用函数完成对信息的修改，这样更加简洁。

---

## 作者：whhsteven (赞：8)

大概 Seg Beats 是可以做的。机房同学好像还胡了一个 $O(n\sqrt n\log n)$ 的序列分块 + 动态开点值域线段树的做法 ~~（你为什么比别人多只根号）~~。

这里讲线段树维护操作标记的 $O(n\log n)$ 做法。

至写这篇题解时，题解区共有三篇题解，其中两篇都是这种做法。这里，我们更详细地说明其原理。

&nbsp;

我们维护加法、取 $\min$、取 $\max$ 三种标记。

首先，我们需要知道：

- 加法对取 $\min$ 取 $\max$ 有分配律。

- 若干连续取 $\min$ 操作可以取 $\min$ 合并，若干连续取 $\max$ 操作可以取 $\max$ 合并。

- 取 $\min$ 和取 $\max$ 顺序先后有影响：

  - 对 $a$ 取 $\min$，再对 $b$ 取 $\max$，再对 $c$ 取 $\min$，等效于对 $\min(a, c)$ 取 $\min$，再对 $\min(b, c)$ 取 $\max$。
  
  - 对称地有，对 $a$ 取 $\max$，再对 $b$ 取 $\min$，再对 $c$ 取 $\max$，等效于对 $\max(a, c)$ 取 $\max$，再对 $\max(b, c)$ 取 $\min$。

- 一段操作序列，将其一段子段作等效转化，这段操作序列的效果是不变的。

由此，我们有：

- 应用上面第 1 条，可以将操作序列等效转化为只有取 $\min$ 和取 $\max$ 操作的序列。

- 应用上面第 2 条，可以将只有取 $\min$ 和取 $\max$ 的操作序列等效转化成取 $\min$ 与取 $\max$ 交替的序列。

- 再反复应用上面第 3.1 条和第 2 条，可以始终将操作序列维护成取一次 $\min$ 再取一次 $\max$（或应用第 3.2 条和第 2 条，维护成取一次 $\max$ 再取一次 $\min$，亦可）。

关于线段树，我们还知道：一个被下放的标记，其操作顺序一定在下放到的线段树结点的原有标记之后。

以上这些，是我们接下来维护操作标记方法的理论依据。

&nbsp;

不妨记区间最大值为 $\mathrm{mxv}$，并将加法、取 $\min$、取 $\max$ 的标记分别记为 $\mathrm{atg}, \mathrm{ntg}, \mathrm{xtg}$。

这里对每个区间维护的标记表示先与 $\mathrm{ntg}$ 取一次 $\min$，再与 $\mathrm{xtg}$ 取一次 $\max$。反过来也是可以的。

#### 区间加 $x$

$\mathrm{mxv}$ 和 $\mathrm{atg}$ 应当加上 $x$，同时 $\mathrm{ntg}$ 和 $\mathrm{xtg}$ 应被分配上加 $x$：

$$\begin{aligned}
\mathrm{mxv} &\gets \mathrm{mxv} + x \\
\mathrm{ntg} &\gets \mathrm{ntg} + x \\
\mathrm{xtg} &\gets \mathrm{xtg} + x
\end{aligned}$$

#### 区间对 $x$ 取 $\min$

$\mathrm{mxv}$ 应当对 $x$ 取 $\min$，$\mathrm{ntg}$ 和 $\mathrm{xtg}$ 应当按照上面第 3.1 条所述与 $x$ “加成”：

$$\begin{aligned}
\mathrm{mxv} &\gets \min(\mathrm{mxv}, x) \\
\mathrm{ntg} &\gets \min(\mathrm{ntg}, x) \\
\mathrm{xtg} &\gets \min(\mathrm{xtg}, x)
\end{aligned}$$

#### 区间对 $x$ 取 $\max$

$\mathrm{mxv}$ 应当对 $x$ 取 $\max$，$\mathrm{xtg}$ 应当与 $x$ 取 $\max$ 合并：

$$\begin{aligned}
\mathrm{mxv} &\gets \max(\mathrm{mxv}, x) \\
\mathrm{xtg} &\gets \max(\mathrm{xtg}, x)
\end{aligned}$$

另两篇采用维护操作标记方法的题解，在这里都还有如下一步更新：

$$\mathrm{ntg} \gets \max(\mathrm{ntg}, x)$$

事实上，可以发现，这一步是正确但不必要的。

如果能认识到这点，算是真正理解了以上这些操作正确性的来源：关键在于将有序的操作序列等效转化为前后两步操作，所以加入一个不能与前一步操作直接合并的操作时，其要对前面两步操作产生作用，使得这步操作的效果被正确“合并”进去。

#### 操作标记下放

可以看出，应当先下放 $\mathrm{atg}$，再下放 $\mathrm{ntg}$ 和 $\mathrm{xtg}$。这是因为，这步加法已经分配给了这个结点的 $\mathrm{ntg}$ 和 $\mathrm{xtg}$，需要分配到下放到的结点的 $\mathrm{ntg}$ 和 $\mathrm{xtg}$ 上。

下放 $\mathrm{ntg}$ 和 $\mathrm{xtg}$ 的顺序是显然的，因为我们上面就是自行选择了两种顺序之一，并按这种顺序维护的操作标记，下放时就应当按照我们选择的这种顺序下放。

#### 查询区间 $\max$

各线段树结点对应的区间 $\max$ 已经维护好，合并这些答案回答区间 $\max$ 是平凡的。

&nbsp;

这样，我们就解决了这个问题。

参考实现：[云剪贴板](/paste/0gyvtjc9)

---

## 作者：Zwb0106 (赞：5)

### [原题链接](https://www.luogu.com.cn/problem/P8024)

------------
## 题意

给定一个长度为 $n$ 的序列和 $m$ 次操作，你需要写一种数据结构，支持以下几种操作：

1. 区间加 $k$；
2. 区间对 $k$ 取 $\min$；
3. 区间对 $k$ 取 $\max$；
4. 询问区间最大值。

对于 $\text{100\%}$ 的数据，$1\le n,m\le 5\times 10^5$。

看到这题的第一反应是 [[P4560] Wall 砖墙](https://www.luogu.com.cn/problem/P4560)，但是多了一个区间加的操作。

感觉标记传递和一些具体细节还是挺需要注意的，写篇题解记录一下做法，方便之后回来看。

------------
## 思路

区间操作，考虑线段树。

------------
### 变量设计

除区间最大值以外，每个节点还要维护区间加标记、区间 $\min$ 标记和区间 $\max$ 标记。

```cpp
struct tree
{
	ll max,sum_tag,min_tag,max_tag;
}t[N<<2];
```

------------
### 建树

递归到叶子节点就直接赋值，不用多说。
但注意，由于有负数，还要把每个节点的 $\min$ 标记和 $\max$ 标记分别设为正无穷大和负无穷大，同时也代表该节点不存在 $\min$ 标记或不存在 $\max$ 标记。

```cpp
void build(int p,int l,int r)
{
	t[p].min_tag=inf;
	t[p].max_tag=-inf;
	if(l==r)
	{
		t[p].max=a[l];
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(p);
}
```

------------
### 信息合并

由于查询只求最大值，所以把该节点的最大值用两个儿子节点的最大值更新一下即可。

```cpp
void push_up(int p)
{
	t[p].max=max(t[ls].max,t[rs].max);
}
```

------------
### 区间加

在普通区间加的基础上对 $\min$ 和 $\max$ 标记进行修改，若存在赋值标记（即不为无穷大），加上 $k$ 即可。

```cpp
void update_add(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max+=k;
		t[p].sum_tag+=k;
		if(t[p].min_tag<inf)t[p].min_tag+=k;
		if(t[p].max_tag>-inf)t[p].max_tag+=k;
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_add(nl,nr,ls,l,mid,k);
	if(mid<nr)update_add(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
```

------------
### 区间取 $\min$

显然区间最大值要对 $k$ 取 $\min$，但除此之外，还要对两个赋值标记取 $\min$，可以想象一下或者手推一下是怎么更新的。

```cpp
void update_min(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max=min(t[p].max,k);
		t[p].min_tag=min(t[p].min_tag,k);
		t[p].max_tag=min(t[p].max_tag,k);
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_min(nl,nr,ls,l,mid,k);
	if(mid<nr)update_min(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
```

------------
### 区间取 $\max$

与取 $\min$ 同理，不再赘述。

```cpp
void update_max(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max=max(t[p].max,k);
		t[p].min_tag=max(t[p].min_tag,k);
		t[p].max_tag=max(t[p].max_tag,k);
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_max(nl,nr,ls,l,mid,k);
	if(mid<nr)update_max(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
```

------------
### 标记下传

对于左右儿子，首先要处理一下区间加标记和区间最大值，同时加上该节点的区间加标记。另外，类似修改函数，要对另外两个标记也进行修改。

然后是赋值标记，参考修改函数即可，先后无所谓。

最后，务必要把该节点的标记初始化。

`push_down` 函数写得有些长，但都是重复内容，并不难理解。

```cpp
void push_down(int p,int l,int r)
{
	t[ls].max+=t[p].sum_tag;
	t[rs].max+=t[p].sum_tag;
	t[ls].sum_tag+=t[p].sum_tag;
	t[rs].sum_tag+=t[p].sum_tag;
	if(t[ls].min_tag<inf)t[ls].min_tag+=t[p].sum_tag;
	if(t[rs].min_tag<inf)t[rs].min_tag+=t[p].sum_tag;
	if(t[ls].max_tag>-inf)t[ls].max_tag+=t[p].sum_tag;
	if(t[rs].max_tag>-inf)t[rs].max_tag+=t[p].sum_tag;
	t[p].sum_tag=0;
	
	t[ls].max=min(t[ls].max,t[p].min_tag);
	t[rs].max=min(t[rs].max,t[p].min_tag);
	t[ls].min_tag=min(t[ls].min_tag,t[p].min_tag);
	t[rs].min_tag=min(t[rs].min_tag,t[p].min_tag);
	t[ls].max_tag=min(t[ls].max_tag,t[p].min_tag);
	t[rs].max_tag=min(t[rs].max_tag,t[p].min_tag);
	t[p].min_tag=inf;
	
	t[ls].max=max(t[ls].max,t[p].max_tag);
	t[rs].max=max(t[rs].max,t[p].max_tag);
	t[ls].min_tag=max(t[ls].min_tag,t[p].max_tag);
	t[rs].min_tag=max(t[rs].min_tag,t[p].max_tag);
	t[ls].max_tag=max(t[ls].max_tag,t[p].max_tag);
	t[rs].max_tag=max(t[rs].max_tag,t[p].max_tag);
	t[p].max_tag=-inf;
}
```

------------

### 询问区间最大值

比较简单，说明略。

```cpp
ll query(int ql,int qr,int p,int l,int r)
{
	if(ql<=l&&r<=qr)return t[p].max;
	push_down(p,l,r);
	int mid=l+r>>1;
	ll ans=-inf;
	if(ql<=mid)ans=max(ans,query(ql,qr,ls,l,mid));
	if(mid<qr)ans=max(ans,query(ql,qr,rs,mid+1,r));
	return ans;
}
```

------------
### 完整代码

每次操作的时间复杂度为 $O(\log n)$，共 $m$ 次操作，故总的时间复杂度为 $O(m\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#define ls p<<1
#define rs p<<1|1
#define ll long long
using namespace std;
const int N=5e5+5;
const ll inf=9e18;
int n,m;
ll a[N];
struct tree
{
	ll max,sum_tag,min_tag,max_tag;
}t[N<<2];
void push_up(int p)
{
	t[p].max=max(t[ls].max,t[rs].max);
}
void push_down(int p,int l,int r)
{
	t[ls].max+=t[p].sum_tag;
	t[rs].max+=t[p].sum_tag;
	t[ls].sum_tag+=t[p].sum_tag;
	t[rs].sum_tag+=t[p].sum_tag;
	if(t[ls].min_tag<inf)t[ls].min_tag+=t[p].sum_tag;
	if(t[rs].min_tag<inf)t[rs].min_tag+=t[p].sum_tag;
	if(t[ls].max_tag>-inf)t[ls].max_tag+=t[p].sum_tag;
	if(t[rs].max_tag>-inf)t[rs].max_tag+=t[p].sum_tag;
	t[p].sum_tag=0;
	
	t[ls].max=min(t[ls].max,t[p].min_tag);
	t[rs].max=min(t[rs].max,t[p].min_tag);
	t[ls].min_tag=min(t[ls].min_tag,t[p].min_tag);
	t[rs].min_tag=min(t[rs].min_tag,t[p].min_tag);
	t[ls].max_tag=min(t[ls].max_tag,t[p].min_tag);
	t[rs].max_tag=min(t[rs].max_tag,t[p].min_tag);
	t[p].min_tag=inf;
	
	t[ls].max=max(t[ls].max,t[p].max_tag);
	t[rs].max=max(t[rs].max,t[p].max_tag);
	t[ls].min_tag=max(t[ls].min_tag,t[p].max_tag);
	t[rs].min_tag=max(t[rs].min_tag,t[p].max_tag);
	t[ls].max_tag=max(t[ls].max_tag,t[p].max_tag);
	t[rs].max_tag=max(t[rs].max_tag,t[p].max_tag);
	t[p].max_tag=-inf;
}
void build(int p,int l,int r)
{
	t[p].min_tag=inf;
	t[p].max_tag=-inf;
	if(l==r)
	{
		t[p].max=a[l];
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(p);
}
void update_add(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max+=k;
		t[p].sum_tag+=k;
		if(t[p].min_tag<inf)t[p].min_tag+=k;
		if(t[p].max_tag>-inf)t[p].max_tag+=k;
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_add(nl,nr,ls,l,mid,k);
	if(mid<nr)update_add(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
void update_min(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max=min(t[p].max,k);
		t[p].min_tag=min(t[p].min_tag,k);
		t[p].max_tag=min(t[p].max_tag,k);
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_min(nl,nr,ls,l,mid,k);
	if(mid<nr)update_min(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
void update_max(int nl,int nr,int p,int l,int r,ll k)
{
	if(nl<=l&&r<=nr)
	{
		t[p].max=max(t[p].max,k);
		t[p].min_tag=max(t[p].min_tag,k);
		t[p].max_tag=max(t[p].max_tag,k);
		return;
	}
	push_down(p,l,r);
	int mid=l+r>>1;
	if(nl<=mid)update_max(nl,nr,ls,l,mid,k);
	if(mid<nr)update_max(nl,nr,rs,mid+1,r,k);
	push_up(p);
}
ll query(int ql,int qr,int p,int l,int r)
{
	if(ql<=l&&r<=qr)return t[p].max;
	push_down(p,l,r);
	int mid=l+r>>1;
	ll ans=-inf;
	if(ql<=mid)ans=max(ans,query(ql,qr,ls,l,mid));
	if(mid<qr)ans=max(ans,query(ql,qr,rs,mid+1,r));
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	build(1,1,n);
	while(m--)
	{
		int q,l,r,k;
		scanf("%d%d%d",&q,&l,&r);
		if(q!=4)scanf("%lld",&k);
		if(q==1)update_add(l,r,1,1,n,k);
		if(q==2)update_min(l,r,1,1,n,k);
		if(q==3)update_max(l,r,1,1,n,k);
		if(q==4)printf("%lld\n",query(l,r,1,1,n));
	}
	return 0;
}
```

---

## 作者：千秋星辰 (赞：3)

**看到这么多区间操作，不是线段树就是分块**╮(╯▽╰)╭

### 思路

~~数据结构题要什么思路。~~

既然是线段树的话，就要考虑应当用线段树维护什么数，两个区间合并的时候有什么规律。

在这里，我选择用四个值描述一个区间：最大值，最小值，加法标记，覆盖标记。

加法标记和覆盖标记同时存在的情况可以从[这里](https://www.luogu.com.cn/problem/P1253)学。

### 实现

注意到这题和普通的区间覆盖不同，因此我们必须对不同的情况加以区分。

比如 $3$ 操作：
1. 如果当前区间的最小值已经大于等于给出的 $h$，那么再进行操作并没有影响，因此发现这样的区间直接返回，不再操作。
2. 如果当前区间的最大值小于等于给出的 $h$，那么这个区间无差别地都覆盖成 $h$，因此直接打上覆盖操作，然后返回。
3. 对于其他的情况，只能暴力递归，直到出现上述情况。

如下：
```cpp
void coverMIN(int k,int l,int r,int ll,int rr,int val)
{
	if(l>=ll&&r<=rr)
	{
		if(MAX[k]<=val)
		{
			MAX[k]=MIN[k]=val;
			co[k]=val,ad[k]=0;
			return ;
		}
		if(MIN[k]>=val) return ;
	}
	pushdown(k);
	if(ll<=mid) coverMIN(lson,ll,rr,val);
	if(rr>mid) coverMIN(rson,ll,rr,val);
	pushup(k);
}
```

$2$ 操作同理。

#### 一些小问题

关于**复杂度**，可以参考[分块板子](https://loj.ac/p/6281)，这个题如果数据水的话线段树可以通过，而稍微构造一下很容易卡掉线段树。

而本题，实测线段树吸氧后不到半秒，而复杂度至少是 $O(n\log n)$，上限并不清楚，还请大佬给出证明。

### AC code

~~细节都在注释里~~

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define forever() while(true)
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')

namespace IO // 快读快写
{
	#define gc getchar
	#define pc putchar
	inline int read()
	{
		int x=0,y=1;char c=gc();
		for(;!isdigit(c);c=gc()) if(c=='-') y=-y;
		for(;isdigit(c);c=gc()) x=x*10+c-'0';
		return x*y;
	}
	void write(int x)
	{
		if(x<0) x=-x,pc('-');
		if(x>9) write(x/10);
		pc('0'+x%10);
	}
	#undef gc
	#undef pc
}

using namespace std;
using namespace IO;

struct SegTree // 封装的线段树 
{
	#define lsx (k<<1)
	#define rsx (k<<1|1)
	#define mid ((l+r)>>1)
	#define lson lsx,l,mid
	#define rson rsx,mid+1,r
	#define size 8000005
	int MAX[size],MIN[size],co[size],ad[size];
	/*
	MAX -> 当前区间的最大值 
	MIN -> 当前区间的最小值 
	co -> 当前区间的区间覆盖lazytag 
	ad -> 当前区间的区间加lazytag 
	*/
	void pushup(int k)
	{
		MAX[k]=max(MAX[lsx],MAX[rsx]);
		MIN[k]=min(MIN[lsx],MIN[rsx]);
	}
	void build(int k,int l,int r)
	{
		if(l==r)
		{
			MAX[k]=MIN[k]=read();
			return ;
		}
		build(lson);
		build(rson);
		pushup(k);
	}
	void pushdown(int k) // 这里只是普通的区间覆盖和区间加pushdown 
	{
		if(co[k])
		{
			MAX[lsx]=MAX[rsx]=co[k];
			MIN[lsx]=MIN[rsx]=co[k];
			co[lsx]=co[rsx]=co[k];
			ad[lsx]=ad[rsx]=0;
			co[k]=0;
		}
		if(ad[k])
		{
			MAX[lsx]+=ad[k],MAX[rsx]+=ad[k];
			MIN[lsx]+=ad[k],MIN[rsx]+=ad[k];
			ad[lsx]+=ad[k],ad[rsx]+=ad[k];
			ad[k]=0;
		}
	}
	void add(int k,int l,int r,int ll,int rr,int val) // 普通的区间加 
	{
		if(l>=ll&&r<=rr)
		{
			MAX[k]+=val;
			MIN[k]+=val;
			ad[k]+=val;
			return ;
		}
		pushdown(k);
		if(ll<=mid) add(lson,ll,rr,val);
		if(rr>mid) add(rson,ll,rr,val);
		pushup(k);
	}
	void coverMAX(int k,int l,int r,int ll,int rr,int val)
	/*
	这个函数对应2操作，即砍树
	形象化地说，这就是把区间内大于等于val的数覆盖成val 
	*/
	{
		if(l>=ll&&r<=rr)
		{
			if(MIN[k]>=val)
			{
				MAX[k]=MIN[k]=val;
				co[k]=val,ad[k]=0;
				return ;
			}
			if(MAX[k]<=val) return ;
		}
		pushdown(k);
		if(ll<=mid) coverMAX(lson,ll,rr,val);
		if(rr>mid) coverMAX(rson,ll,rr,val);
		pushup(k);
	}
	void coverMIN(int k,int l,int r,int ll,int rr,int val)
	/*
	这个函数对应3操作，即种树
	形象化地说，这就是把区间内不足val的数都覆盖成val 
	*/
	{
		if(l>=ll&&r<=rr)
		{
			if(MAX[k]<=val)
			{
				MAX[k]=MIN[k]=val;
				co[k]=val,ad[k]=0;
				return ;
			}
			if(MIN[k]>=val) return ;
		}
		pushdown(k);
		if(ll<=mid) coverMIN(lson,ll,rr,val);
		if(rr>mid) coverMIN(rson,ll,rr,val);
		pushup(k);
	}
	int query(int k,int l,int r,int ll,int rr) // 普通的查询区间最大值(RMQ) 
	{
		if(l>=ll&&r<=rr) return MAX[k];
		pushdown(k);
		int res=INT_MIN;
		if(ll<=mid) res=max(res,query(lson,ll,rr));
		if(rr>mid) res=max(res,query(rson,ll,rr));
		return res;
	}
	#undef lsx
	#undef rsx
	#undef mid
	#undef lson
	#undef rson
	#undef size
}T;

signed main()
{
	int n=read(),Q=read(),opt,l,r,x;
	T.build(1,1,n);
	while(Q--)
	{
		opt=read(),l=read(),r=read();
		opt==4?114514:x=read(),0;
		if(opt==1) T.add(1,1,n,l,r,x);
		if(opt==2) T.coverMAX(1,1,n,l,r,x);
		if(opt==3) T.coverMIN(1,1,n,l,r,x);
		if(opt==4) writen(T.query(1,1,n,l,r));
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

# Solution

考慮線段樹。信息記錄區間中的最大值，標記記錄 $a,p,q$，表示對於區間中的 $x$，執行 $x\gets \min(\max(x+a,p),q)$。

信息的合併與標記對信息的作用是容易的，來考慮標記的複合。設後兩個標記是 $(a,p,q),(a',p',q')$。

$$
\begin{aligned}
x\gets& \min(\max(\min(\max(x+a,p),q)+a',p'),q') \\
=&\min(\max(\min(\max(x+a+a',p+a'),q+a'),p'),q')
\end{aligned}
$$

這步用了加法對 $\min/\max$ 的分配律。接下來我們來看：
$$
\begin{aligned}
&\max(\min(\max(A,B),C),D)\\
=&\min(\max(A,B,D),\max(C,D))
\end{aligned}
$$

這個不難理解，分討 $\min(\max(A,B),C)$ 和 $D$ 的大小關係容易證明。接下來：

$$
\begin{aligned}
x\gets&\min(\max(\min(\max(x+a+a',p+a'),q+a'),p'),q')\\
=&\min(\min(\max(x+a+a',p+a',p'),\max(q+a',p')),q')\\
=&\min(\max(x+a+a',p+a',p'),\max(q+a',p'),q')\\
=&\min(\max(x+a+a',\max(p+a',p')),\min(\max(q+a',p'),q'))
\end{aligned}
$$

可以發現，令 $a''=a+a'$，$p''=\max(p+a',p')$，$q''=\min(\max(q+a',p'),q')$，標記又變回了 $x\gets\min(\max(x+a'',p''),q'')$ 的形式。這樣就複合完了。

時間複雜度 $\mathcal{O}(n+q\log n)$。

# Code

給出主要部分。`ad`、`mx`、`mn` 分別表示上文的 $a,p,q$。

```cpp
struct info {
	LL mx; void set(int x) { mx = x; }
} s[N << 2];
struct tag {
	LL ad, mx, mn;
	void reset() { ad = 0, mx = -1e9, mn = 1e9; }
} tg[N << 2];
info merge(const info& x, const info& y) {
	return {max(x.mx, y.mx)};
}
info apply(const info& x, const tag& y) {
	return {min(max(x.mx + y.ad, y.mx), y.mn)};
}
tag compose(const tag& x, const tag& y) {	
	return {x.ad + y.ad, max(x.mx + y.ad, y.mx), min(max(x.mn + y.ad, y.mx), y.mn)};
}
```

---

## 作者：xs_siqi (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P8024)

代码 $50$ 行。小于 $2kb$。时间复杂度：$O(q\log n)$。

# 简述题意

>维护一个数列，有如下操作：

>- `1 l r k`：$\forall i\in[l,r],a_i←a_i+k$

>- `2 l r k`：$\forall i\in[l,r],a_i←\min\{a_i,k\}$

>- `3 l r k`：$\forall i\in[l,r],a_i←\max\{a_i,k\}$

>- `4 l r k`：$\forall i\in[l,r]$，输出 $\max\{a_i\}$

> $1\leq n,q\leq 5\times 10^5$，数据不超过 $2^{32}-1$。

很明显用线段树。

# 题解简述

### 变量设计

$v$ 表示当前值；$ag$ 即 $addtag$，操作一的标记；$ng$ 即 $minchangetag$，操作二的标记；$xg$ 即 $maxchangetag$，操作三的标记。

初始化部分后文会讲。

```
struct e{int v,ag,ng=2e9,xg=-2e9;}tr[2000005];
```

### 建树

首先我们先写 `pushup`。我们关注到输出只需让我们输出最大值，所以对于该节点只需要对左右儿子取最大值即可。
```cpp
void PU(int rt){tr[rt].v=tr[ls].v>tr[rs].v?tr[ls].v:tr[rs].v;}
```

然后再考虑建树。首先关注到题目中说明了数据可能为负数，那么 $xg$ 初始值需要定义在所有可能出现的值之外，操作中最大增加的值只有 $500$，操作只有 $5\times 10^5$ 次 ，所以 $-2\times 10^9$ 是一个不错的取值。最小值同理，取了 $2\times 10^9$。这个初始化我放在了开头定义里面。

其它建树的过程都比较模板。

```cpp
void B(int rt,int l,int r){
	if(l==r){tr[rt].v=a[l];return ;}
	int mid=l+r>>1;B(ls,l,mid),B(rs,mid+1,r),PU(rt);
}
```

### 标记下传

$v$ 的更新直接对两个标记分别更新即可。由题意得，$xg$ 更新 $\max$，$mg$ 更新 $\min$，$ag$ 直接加就行了。

$xg$ 更新可以进行分类讨论。

- 如果进行了操作 $2$，那么前面输入的 $k$ 会被覆盖，所以对于前面的 $xg$ 要更新。更新步骤即取 $\min$。

- 如果进行了操作 $3$，那么前面输入的 $k$ 也会被覆盖，所以对于前面的 $xg$ 要更新。更新步骤即取 $\max$。

- 如果进行了操作 $4$，那么前面输入的 $k$ 也会被增加，所以对于 $ag$ 需要更新。更新过程即直接加。


对于 $mg$ 跟上面同理。

$ag$ 的增加跟取 $\max$ 和取 $\min$ 就没有关系了。因为不管后面要不要更新，前面还是要加的，也就是没有达成覆盖的效果。但是后面的 $ag$ 的增加可以跟前面的合并，所以标记更新只需要管 $ag$ 即可。

下面代码中，`mn` 函数即对两者取 $\min$，取 $\min$ 的结果更新到前面的那个数。`mx` 函数即对两者取 $\max$，取 $\max$ 的结果更新到前面的那个数。

```cpp
void PD(int rt){
	tr[ls].v+=tr[rt].ag,tr[rs].v+=tr[rt].ag;tr[ls].ag+=tr[rt].ag,tr[rs].ag+=tr[rt].ag;
	tr[ls].ng+=(tr[ls].ng==2e9?0:tr[rt].ag),tr[rs].ng+=(tr[rs].ng==2e9?0:tr[rt].ag);
	tr[ls].xg+=(tr[ls].xg==2e9?0:tr[rt].ag),tr[rs].xg+=(tr[rs].xg==2e9?0:tr[rt].ag);
	mn(tr[ls].v,tr[rt].ng),mx(tr[ls].v,tr[rt].xg);mn(tr[rs].v,tr[rt].ng),mx(tr[rs].v,tr[rt].xg);
	mn(tr[ls].ng,tr[rt].ng),mx(tr[ls].ng,tr[rt].xg);mn(tr[rs].ng,tr[rt].ng),mx(tr[rs].ng,tr[rt].xg);
	mn(tr[ls].xg,tr[rt].ng),mx(tr[ls].xg,tr[rt].xg);mn(tr[rs].xg,tr[rt].ng),mx(tr[rs].xg,tr[rt].xg);
	tr[rt].ag=0;tr[rt].ng=2e9,tr[rt].xg=-2e9;
}
```
### 修改函数

其实没必要把三个修改分开写。主要过程是一致的，所以写到一个函数中即可。

$v$、$xg$、$ng$、$ag$ 的修改原理跟 `pushdown` 函数的逻辑是一样的。`change` 函数其实也比较模板。

$op$ 是操作编号。

```cpp
void C(int op,int rt,int l,int r,int ql,int qr,int v){
	if(ql<=l&&r<=qr){
		if(op==1)tr[rt].v+=v,tr[rt].ag+=v,tr[rt].ng+=(tr[rt].ng==2e9?0:v),tr[rt].xg+=(tr[rt].xg==-2e9?0:v);
		if(op==2)mn(tr[rt].v,v),mn(tr[rt].xg,v),mn(tr[rt].ng,v);
		if(op==3)mx(tr[rt].v,v),mx(tr[rt].xg,v),mx(tr[rt].ng,v);
		return ;
	}
	PD(rt);int mid=l+r>>1;
	if(ql<=mid)C(op,ls,l,mid,ql,qr,v);
	if(qr>mid)C(op,rs,mid+1,r,ql,qr,v);
	PU(rt);
}
```

### 询问函数

挺简单的，就不过多讲述了。

```cpp
int Q(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[rt].v;
	PD(rt);int mid=l+r>>1,ans=-2e9;
	if(ql<=mid)ans=Q(ls,l,mid,ql,qr);
	if(qr>mid)mx(ans,Q(ls|1,mid+1,r,ql,qr));
	return ans;
}
```

## 完整代码

```cpp
#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
int n,m,a[500005];
struct e{int v,ag,ng=2e9,xg=-2e9;}tr[2000005];
void mx(int &x,int y){x=x>y?x:y;}
void mn(int &x,int y){x=x<y?x:y;}
void PU(int rt){tr[rt].v=tr[ls].v>tr[rs].v?tr[ls].v:tr[rs].v;}
void PD(int rt){
	tr[ls].v+=tr[rt].ag,tr[rs].v+=tr[rt].ag;tr[ls].ag+=tr[rt].ag,tr[rs].ag+=tr[rt].ag;
	tr[ls].ng+=(tr[ls].ng==2e9?0:tr[rt].ag),tr[rs].ng+=(tr[rs].ng==2e9?0:tr[rt].ag);
	tr[ls].xg+=(tr[ls].xg==2e9?0:tr[rt].ag),tr[rs].xg+=(tr[rs].xg==2e9?0:tr[rt].ag);
	mn(tr[ls].v,tr[rt].ng),mx(tr[ls].v,tr[rt].xg);mn(tr[rs].v,tr[rt].ng),mx(tr[rs].v,tr[rt].xg);
	mn(tr[ls].ng,tr[rt].ng),mx(tr[ls].ng,tr[rt].xg);mn(tr[rs].ng,tr[rt].ng),mx(tr[rs].ng,tr[rt].xg);
	mn(tr[ls].xg,tr[rt].ng),mx(tr[ls].xg,tr[rt].xg);mn(tr[rs].xg,tr[rt].ng),mx(tr[rs].xg,tr[rt].xg);
	tr[rt].ag=0;tr[rt].ng=2e9,tr[rt].xg=-2e9;
}
void B(int rt,int l,int r){
	if(l==r){tr[rt].v=a[l];return ;}
	int mid=l+r>>1;B(ls,l,mid),B(rs,mid+1,r),PU(rt);
}
void C(int op,int rt,int l,int r,int ql,int qr,int v){
	if(ql<=l&&r<=qr){
		if(op==1)tr[rt].v+=v,tr[rt].ag+=v,tr[rt].ng+=(tr[rt].ng==2e9?0:v),tr[rt].xg+=(tr[rt].xg==-2e9?0:v);
		if(op==2)mn(tr[rt].v,v),mn(tr[rt].xg,v),mn(tr[rt].ng,v);
		if(op==3)mx(tr[rt].v,v),mx(tr[rt].xg,v),mx(tr[rt].ng,v);
		return ;
	}
	PD(rt);int mid=l+r>>1;
	if(ql<=mid)C(op,ls,l,mid,ql,qr,v);
	if(qr>mid)C(op,rs,mid+1,r,ql,qr,v);
	PU(rt);
}
int Q(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[rt].v;
	PD(rt);int mid=l+r>>1,ans=-2e9;
	if(ql<=mid)ans=Q(ls,l,mid,ql,qr);
	if(qr>mid)mx(ans,Q(ls|1,mid+1,r,ql,qr));
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);B(1,1,n);
	for(int o,x,y,z,i=1;i<=m;i++){
		scanf("%d%d%d",&o,&x,&y);
		if(o!=4)scanf("%d",&z),C(o,1,1,n,x,y,z);
		else printf("%d\n",Q(1,1,n,x,y));
	}
	return 0;
}

```


## 巩固：

[P2572 序列操作](https://www.luogu.com.cn/problem/P2572)

[P4560 [IOI2014] Wall 砖墙](https://www.luogu.com.cn/problem/P4560)


---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8024)

## 思路

线段树。

操作一：区间加。

操作二：区间中的每一个数更改为这个数和给定数的最小值。

操作三：区间中的每一个数更改为这个数和给定数的最大值（如果种的树更矮就露不出头）。

操作四：求区间最大值。

于是线段树中就维护了这些变量：

``l``：线段左端点。

``r``：线段右端点。

``ma``：线段最大值。

``tpl``：区间加的 lazytag。

``tma``：区间更改最大值的 lazytag。

``tmi``：区间更改最小值的 lazytag。

```cpp
#define ll long long
const int N=5e5+10;
const ll inf=1e18;//定义极大值，后面要用。
int n,q;
struct node{
	int l,r;
	ll tpl,tmi,tma,ma;
}tr[N<<2];//记得开 4 倍空间。
```

### 1. 建树

和普通线段树相差无几。注意 ``tma`` 和 ``tmi`` 分别取极小值、极大值，方便比大小。

```cpp
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	tr[i].tmi=inf;
	tr[i].tma=-inf;
	if(l==r){
		cin>>tr[i].ma;
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);//上传最大值。
	return ;
}
```

### 2. 区间加（拔高）操作

加的时候不仅要对 ``tpl`` 和 ``ma`` 进行增加，还要对 ``tma`` 和 ``tmi`` 进行增加。（树都长高了，砍或种的是不是会变化呢？）不过记得如果没有标记就不要增加了，避免出问题。

```cpp
void makep(int i,ll k){//5. 要用。
	tr[i].tpl+=k;
	if(tr[i].tmi!=inf)tr[i].tmi+=k;//有标记再加。
	if(tr[i].tma!=-inf)tr[i].tma+=k;
	tr[i].ma+=k;
	return ;
}
void pls(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		makep(i,k);
		return ;
	}
	pushdown(i);//见 5.
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)pls(i<<1,l,r,k);
	if(mid<r)pls(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);//更新最大值。
	return ;
}
```

### 3. 区间更改较小值（砍树）操作

这个也很容易，不过记得在对 ``ma`` 和 ``tmi`` 进行操作的同时也要更改 ``tma``。（树被砍了是不是种下后能看见的更多了呢？）这时不用分类讨论，因为如果没有标记，``tma`` 是极小值，不会受影响。

```cpp
void maked(int i,ll k){//5. 要用。
	tr[i].tmi=min(tr[i].tmi,k);
	tr[i].ma=min(tr[i].ma,k);
	tr[i].tma=min(tr[i].tma,k);
	return ;
}
void del(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		maked(i,k);
		return ;
	}
	pushdown(i);//见 5.
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)del(i<<1,l,r,k);
	if(mid<r)del(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);//更新最大值。
	return ;
}
```

### 4. 区间更改较大值（种树）操作

和上面一部分相似，也要同时更改三个变量。（种上更高的树了是不是砍的会更多呢？）

```cpp
void makea(int i,ll k){//5. 要用。
	tr[i].tma=max(tr[i].tma,k);
	tr[i].ma=max(tr[i].ma,k);
	tr[i].tmi=max(tr[i].tmi,k);
	return ;
}
void add(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		makea(i,k);
		return ;
	}
	pushdown(i);//见 5.
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)add(i<<1,l,r,k);
	if(mid<r)add(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);//更新最大值。
	return ;
}
```

### 5. ``pushdown`` 下传懒标记

只要在子线段上分别进行对应操作即可。传完别忘清零。

```cpp
void pushdown(int i){
	if(tr[i].tpl){
		makep(i<<1,tr[i].tpl);//见 2.
		makep(i<<1|1,tr[i].tpl);
		tr[i].tpl=0;
	}
	if(tr[i].tmi!=inf){
		maked(i<<1,tr[i].tmi);//见 3.
		maked(i<<1|1,tr[i].tmi);
		tr[i].tmi=inf;
	}
	if(tr[i].tma!=-inf){
		makea(i<<1,tr[i].tma);//见 4.
		makea(i<<1|1,tr[i].tma);
		tr[i].tma=-inf;
	}
	return ;
}
```

### 6. 区间查询最大值

没有任何坑点的一部分，直接放代码了。

```cpp
ll query(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].ma;
	pushdown(i);//见 5.
	int mid=tr[i].l+tr[i].r>>1;
	ll res=-inf;//找最大值，记得赋极小值为初值。
	if(l<=mid)res=max(res,query(i<<1,l,r));
	if(mid<r)res=max(res,query(i<<1|1,l,r));
	return res;
}
```

### 7. 主函数

也没任何坑点，直接放代码。

```cpp
signed main(){
	cin>>n>>q;
	build(1,1,n);//见 1.
	while(q--){
		int op,l,r;
        cin>>op>>l>>r;
		if(op==1){
			ll k;
            cin>>k;
			pls(1,l,r,k);//见 2.
		}
		if(op==2){
			ll k;
            cin>>k;
			del(1,l,r,k);//见 3.
		}
		if(op==3){
			ll k;
            cin>>k;
			add(1,l,r,k);//见 4.
		}
		if(op==4)cout<<query(1,l,r)<<"\n";//见 6.
	}
	return 0;
}
```

## 完整代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
const ll inf=1e18;
int n,q;
struct node{
	int l,r;
	ll tpl,tmi,tma,ma;
}tr[N<<2];
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	tr[i].tmi=inf;
	tr[i].tma=-inf;
	if(l==r){
		cin>>tr[i].ma;
		return ;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);
	return ;
}
void makep(int i,ll k){
	tr[i].tpl+=k;
	if(tr[i].tmi!=inf)tr[i].tmi+=k;
	if(tr[i].tma!=-inf)tr[i].tma+=k;
	tr[i].ma+=k;
	return ;
}
void maked(int i,ll k){
	tr[i].tmi=min(tr[i].tmi,k);
	tr[i].ma=min(tr[i].ma,k);
	tr[i].tma=min(tr[i].tma,k);
	return ;
}
void makea(int i,ll k){
	tr[i].tma=max(tr[i].tma,k);
	tr[i].ma=max(tr[i].ma,k);
	tr[i].tmi=max(tr[i].tmi,k);
	return ;
}
void pushdown(int i){
	if(tr[i].tpl){
		makep(i<<1,tr[i].tpl);
		makep(i<<1|1,tr[i].tpl);
		tr[i].tpl=0;
	}
	if(tr[i].tmi!=inf){
		maked(i<<1,tr[i].tmi);
		maked(i<<1|1,tr[i].tmi);
		tr[i].tmi=inf;
	}
	if(tr[i].tma!=-inf){
		makea(i<<1,tr[i].tma);
		makea(i<<1|1,tr[i].tma);
		tr[i].tma=-inf;
	}
	return ;
}
void pls(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		makep(i,k);
		return ;
	}
	pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)pls(i<<1,l,r,k);
	if(mid<r)pls(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);
	return ;
}
void del(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		maked(i,k);
		return ;
	}
	pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)del(i<<1,l,r,k);
	if(mid<r)del(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);
	return ;
}
void add(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		makea(i,k);
		return ;
	}
	pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)add(i<<1,l,r,k);
	if(mid<r)add(i<<1|1,l,r,k);
	tr[i].ma=max(tr[i<<1].ma,tr[i<<1|1].ma);
	return ;
}
ll query(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].ma;
	pushdown(i);
	int mid=tr[i].l+tr[i].r>>1;
	ll res=-inf;
	if(l<=mid)res=max(res,query(i<<1,l,r));
	if(mid<r)res=max(res,query(i<<1|1,l,r));
	return res;
}
signed main(){
	cin>>n>>q;
	build(1,1,n);
	while(q--){
		int op,l,r;
        cin>>op>>l>>r;
		if(op==1){
			ll k;
            cin>>k;
			pls(1,l,r,k);
		}
		if(op==2){
			ll k;
            cin>>k;
			del(1,l,r,k);
		}
		if(op==3){
			ll k;
            cin>>k;
			add(1,l,r,k);
		}
		if(op==4)cout<<query(1,l,r)<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/165253814)

---

## 作者：bluewindde (赞：0)

维护区间最大值（答案）、区间取最大 / 最小值标记、区间加标记。

答案的合并、答案与标记的合并都是平凡的，不赘述。

考虑标记与标记合并，类似乘加线段树，钦定取最值标记优先级更高。

对于取最大值操作，将取最大 / 最小值标记分别 chkmax。加标记优先级低所以不用考虑。取最小值操作同理。

对于加操作，将标记和值分别加即可，也是平凡的。

时间复杂度 $O(q \log n)$。

```cpp
#include <iostream>

using namespace std;

typedef long long i64;

const i64 inf = 1e18;

int n, q;
int a[500005];

struct node {
    i64 val, add, mx, mn;
} d[2000005];
static inline void pushup(int p) { d[p].val = max(d[p << 1].val, d[p << 1 | 1].val); }
static inline void pushdown(int p);
static inline void pushmax(int p, i64 c) {
    d[p].val = max(d[p].val, c);
    d[p].mx = max(d[p].mx, c);
    d[p].mn = max(d[p].mn, c);
}
static inline void pushmin(int p, i64 c) {
    d[p].val = min(d[p].val, c);
    d[p].mx = min(d[p].mx, c);
    d[p].mn = min(d[p].mn, c);
}
static inline void pushadd(int p, i64 c) {
    d[p].val += c;
    d[p].add += c;
    if (d[p].mx != -inf)
        d[p].mx += c;
    if (d[p].mn != inf)
        d[p].mn += c;
}
static inline void pushdown(int p) {
    if (d[p].add) {
        pushadd(p << 1, d[p].add);
        pushadd(p << 1 | 1, d[p].add);
    }
    if (d[p].mx != -inf) {
        pushmax(p << 1, d[p].mx);
        pushmax(p << 1 | 1, d[p].mx);
    }
    if (d[p].mn != inf) {
        pushmin(p << 1, d[p].mn);
        pushmin(p << 1 | 1, d[p].mn);
    }
    d[p].add = 0;
    d[p].mx = -inf;
    d[p].mn = inf;
}
static inline void build(int s, int t, int p) {
    d[p].mx = -inf;
    d[p].mn = inf;
    if (s == t) {
        d[p].val = a[s];
        return;
    }
    int mid = (s + t) >> 1;
    build(s, mid, p << 1);
    build(mid + 1, t, p << 1 | 1);
    pushup(p);
}
static inline void add(int l, int r, int s, int t, int c, int p) {
    if (l <= s && r >= t) {
        pushadd(p, c);
        return;
    }
    int mid = (s + t) >> 1;
    pushdown(p);
    if (l <= mid)
        add(l, r, s, mid, c, p << 1);
    if (r > mid)
        add(l, r, mid + 1, t, c, p << 1 | 1);
    pushup(p);
}
static inline void max(int l, int r, int s, int t, int c, int p) {
    if (l <= s && r >= t) {
        pushmax(p, c);
        return;
    }
    int mid = (s + t) >> 1;
    pushdown(p);
    if (l <= mid)
        max(l, r, s, mid, c, p << 1);
    if (r > mid)
        max(l, r, mid + 1, t, c, p << 1 | 1);
    pushup(p);
}
static inline void min(int l, int r, int s, int t, int c, int p) {
    if (l <= s && r >= t) {
        pushmin(p, c);
        return;
    }
    int mid = (s + t) >> 1;
    pushdown(p);
    if (l <= mid)
        min(l, r, s, mid, c, p << 1);
    if (r > mid)
        min(l, r, mid + 1, t, c, p << 1 | 1);
    pushup(p);
}
static inline i64 query(int l, int r, int s, int t, int p) {
    if (l <= s && r >= t)
        return d[p].val;
    int mid = (s + t) >> 1;
    pushdown(p);
    if (l <= mid && r > mid)
        return max(query(l, r, s, mid, p << 1), query(l, r, mid + 1, t, p << 1 | 1));
    else if (l <= mid)
        return query(l, r, s, mid, p << 1);
    else if (r > mid)
        return query(l, r, mid + 1, t, p << 1 | 1);
    return -inf;
}

static inline void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, n, 1);
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int x;
            cin >> x;
            add(l, r, 1, n, x, 1);
        } else if (op == 2) {
            int x;
            cin >> x;
            min(l, r, 1, n, x, 1);
        } else if (op == 3) {
            int x;
            cin >> x;
            max(l, r, 1, n, x, 1);
        } else
            cout << query(l, r, 1, n, 1) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    cout.flush();
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8024)

### 思路

看完本题，不难想到本题考察的是线段树。

#### 1. 变量

对于本题，我们需要存储一下变量：

- ``l`` 代表当前线段的左端点。

- ``r`` 代表当前线段的右端点。

- ``tmax`` 代表当前区间的最大值。

- ``mintag`` 代表对第二个操作中取 $\min$ 操作的懒标记，一开始将其赋值为**最大值**。

- ``maxtag`` 代表对第三个操作中取 $\max$ 操作的懒标记，一开始将其赋值为**最小值**。

- ``tag`` 代表对区间加和的懒标记，开始时，将其赋值为 $0$。

虽然这样存储的变量会很多，但却帮助了我们在接下来的处理中让我们方便了很多。

#### 2. 建树

```cpp
void build(int i, int l, int r){
	tree[i].l = l; tree[i].r = r; tree[i].maxtag = -2e9; tree[i].mintag = 2e9;//同上，将 maxtag 的值赋为最小值，将 mintag 的值赋为最大值。
	if(l == r){
		tree[i].tmax = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid); build(i << 1 | 1, mid + 1, r);
	pushup(i);
}
```
建树的过程中，我们只需要注意按上述维护的变量信息，对 ``maxtag`` 和 ``mintag`` 两个变量进行特殊的赋值即可。

最下面的 ``pushup`` 部分我们只需要按照常规操作，将每个区间的最大值都进行维护就可以了。

```cpp
void pushup(int i){
	tree[i].tmax = max(tree[i << 1].tmax, tree[i << 1 | 1].tmax);
}
```

#### 3. 区间加

对于区间加的操作，我们在增加的操作时，需要注意在更改区间内的时候，不仅要对 ``tag`` 和 ``tmax`` 进行更改，更要注意在执行这个操作的时候，如果此时 ``maxtag`` 或者 ``mintag`` 有值的话，那我们需要对 ``maxtag`` 和 `` mintag`` 的值**进行更改**，因为此时的砍伐和种树两个操作如果正常的话应该是**已经执行**完了的。相同的，在 ``pushdown`` 的时候，也需要按照上述操作对下面的子区间进行**相同的操作**。

```cpp
void add(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){//在范围内。
		tree[i].tmax += k;//最大值更新。
		tree[i].tag += k;//更新区间加和懒标记 tag。
		if(tree[i].maxtag != -2e9) tree[i].maxtag += k;//更新区间最大值操作懒标记 maxtag。
		if(tree[i].mintag != 2e9) tree[i].mintag += k;//更新区间最小值操作懒标记 mintag。
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) add(i << 1, l, r, k);
	if(r >= mid + 1) add(i << 1 | 1, l, r, k);
	pushup(i);
}
```

#### 4. 区间取最小值

对于第二个操作，我们仿照区间和的思路，不光对 ``tmax`` 取 $\min$，同时也对 ``mintag`` 和 ``maxtag`` 取 $\min$，同样，``pushdown`` 部分类似。

- 对 ``mintag`` 取 $\min$ 是因为如果我们当前的 ``h`` 是要大于当前的 ``mintag`` 的话，那么当前操作便**不会对树的高度产生任何影响**，因此这次操作是没有用的。

- 对于 ``maxtag`` 取 $\min$ 则是因为我们需要对刚刚种的树也执行操作，才能保证结果无误。

```cpp
void change(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){//在区间内
		tree[i].tmax = min(tree[i].tmax, k);//更新当前区间的信息。
		tree[i].maxtag = min(tree[i].maxtag, k);
		tree[i].mintag = min(tree[i].mintag, k);
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) change(i << 1, l, r, k);
	if(r >= mid + 1) change(i << 1 | 1, l, r, k);
	pushup(i);
}
```

#### 5. 区间取最大值

对于第三个操作，处理方式和第二个操作基本相同，可以看成是第二个操作的相反操作，在这里不再过多的赘述。

```cpp
void update(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){//在区间内。
		tree[i].tmax = max(tree[i].tmax, k);//对当前区间内的信息进行更新。
		tree[i].maxtag = max(tree[i].maxtag, k);
		tree[i].mintag = max(tree[i].mintag, k);
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) update(i << 1, l, r, k);
	if(r >= mid + 1) update(i << 1 | 1, l, r, k);
	pushup(i);
}
```

#### 6. 区间查询最大值

这是一个常规操作，代码如下：

```cpp
int findmax(int i, int l, int r){
	if(tree[i].l >= l && tree[i].r <= r) return tree[i].tmax;//在区间内直接返回。
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1, ans = -2e9;
	if(l <= mid) ans = max(ans, findmax(i << 1, l, r));//左子区间内有。
	if(r >= mid + 1) ans = max(ans, findmax(i << 1 | 1, l, r));//右子区间内右。
	return ans;
	pushup(i);
}
```

#### 7. 向下传递标记

仿照上述的三个操作，对下面的子区间进行更改。

```cpp
void pushdown(int i){
	if(tree[i].tag){//区间加下传标记。
		tree[i << 1].tmax += tree[i].tag;
		tree[i << 1 | 1].tmax += tree[i].tag;
		tree[i << 1].tag += tree[i].tag;
		tree[i << 1 | 1].tag += tree[i].tag;
		if(tree[i << 1].maxtag != -2e9) tree[i << 1].maxtag += tree[i].tag;
		if(tree[i << 1].mintag != 2e9) tree[i << 1].mintag += tree[i].tag;
		if(tree[i << 1 | 1].maxtag != -2e9) tree[i << 1 | 1].maxtag += tree[i].tag;
		if(tree[i << 1 | 1].mintag != 2e9) tree[i << 1 | 1].mintag += tree[i].tag;
		tree[i].tag = 0;
	}
	if(tree[i].mintag != 2e9){//区间取最小值下传标记。
		tree[i << 1].mintag = min(tree[i << 1].mintag, tree[i].mintag);
		tree[i << 1 | 1].mintag = min(tree[i << 1 | 1].mintag, tree[i].mintag);
		tree[i << 1].maxtag = min(tree[i << 1].maxtag, tree[i].mintag);
		tree[i << 1 | 1].maxtag = min(tree[i << 1 | 1].maxtag, tree[i].mintag);
		tree[i << 1].tmax = min(tree[i << 1].tmax, tree[i].mintag);
		tree[i << 1 | 1].tmax = min(tree[i << 1 | 1].tmax, tree[i].mintag);
		tree[i].mintag = 2e9;
	}
	if(tree[i].maxtag != -2e9){//区间取最大值下传标记。
		tree[i << 1].maxtag = max(tree[i << 1].maxtag, tree[i].maxtag);
		tree[i << 1 | 1].maxtag = max(tree[i << 1 | 1].maxtag, tree[i].maxtag);
		tree[i << 1].mintag = max(tree[i << 1].mintag, tree[i].maxtag);
		tree[i << 1 | 1].mintag = max(tree[i << 1 | 1].mintag, tree[i].maxtag);
		tree[i << 1].tmax = max(tree[i << 1].tmax, tree[i].maxtag);
		tree[i << 1 | 1].tmax = max(tree[i << 1 | 1].tmax, tree[i].maxtag);
		tree[i].maxtag = -2e9;
	}
}
```
### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int a[N];

struct node{
	int l, r, tmax, tag, maxtag, mintag;
}tree[N * 4];

void pushup(int i){
	tree[i].tmax = max(tree[i << 1].tmax, tree[i << 1 | 1].tmax);
}

void build(int i, int l, int r){
	tree[i].l = l; tree[i].r = r; tree[i].maxtag = -2e9; tree[i].mintag = 2e9;
	if(l == r){
		tree[i].tmax = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid); build(i << 1 | 1, mid + 1, r);
	pushup(i);
}

void pushdown(int i){
	if(tree[i].tag){
		tree[i << 1].tmax += tree[i].tag;
		tree[i << 1 | 1].tmax += tree[i].tag;
		tree[i << 1].tag += tree[i].tag;
		tree[i << 1 | 1].tag += tree[i].tag;
		if(tree[i << 1].maxtag != -2e9) tree[i << 1].maxtag += tree[i].tag;
		if(tree[i << 1].mintag != 2e9) tree[i << 1].mintag += tree[i].tag;
		if(tree[i << 1 | 1].maxtag != -2e9) tree[i << 1 | 1].maxtag += tree[i].tag;
		if(tree[i << 1 | 1].mintag != 2e9) tree[i << 1 | 1].mintag += tree[i].tag;
		tree[i].tag = 0;
	}
	if(tree[i].mintag != 2e9){
		tree[i << 1].mintag = min(tree[i << 1].mintag, tree[i].mintag);
		tree[i << 1 | 1].mintag = min(tree[i << 1 | 1].mintag, tree[i].mintag);
		tree[i << 1].maxtag = min(tree[i << 1].maxtag, tree[i].mintag);
		tree[i << 1 | 1].maxtag = min(tree[i << 1 | 1].maxtag, tree[i].mintag);
		tree[i << 1].tmax = min(tree[i << 1].tmax, tree[i].mintag);
		tree[i << 1 | 1].tmax = min(tree[i << 1 | 1].tmax, tree[i].mintag);
		tree[i].mintag = 2e9;
	}
	if(tree[i].maxtag != -2e9){
		tree[i << 1].maxtag = max(tree[i << 1].maxtag, tree[i].maxtag);
		tree[i << 1 | 1].maxtag = max(tree[i << 1 | 1].maxtag, tree[i].maxtag);
		tree[i << 1].mintag = max(tree[i << 1].mintag, tree[i].maxtag);
		tree[i << 1 | 1].mintag = max(tree[i << 1 | 1].mintag, tree[i].maxtag);
		tree[i << 1].tmax = max(tree[i << 1].tmax, tree[i].maxtag);
		tree[i << 1 | 1].tmax = max(tree[i << 1 | 1].tmax, tree[i].maxtag);
		tree[i].maxtag = -2e9;
	}
}

void add(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){
		tree[i].tmax += k;
		tree[i].tag += k;
		if(tree[i].maxtag != -2e9) tree[i].maxtag += k;
		if(tree[i].mintag != 2e9) tree[i].mintag += k;
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) add(i << 1, l, r, k);
	if(r >= mid + 1) add(i << 1 | 1, l, r, k);
	pushup(i);
}

void change(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){
		tree[i].tmax = min(tree[i].tmax, k);
		tree[i].maxtag = min(tree[i].maxtag, k);
		tree[i].mintag = min(tree[i].mintag, k);
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) change(i << 1, l, r, k);
	if(r >= mid + 1) change(i << 1 | 1, l, r, k);
	pushup(i);
}

void update(int i, int l, int r, int k){
	if(tree[i].l >= l && tree[i].r <= r){
		tree[i].tmax = max(tree[i].tmax, k);
		tree[i].maxtag = max(tree[i].maxtag, k);
		tree[i].mintag = max(tree[i].mintag, k);
		return ;
	}
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid) update(i << 1, l, r, k);
	if(r >= mid + 1) update(i << 1 | 1, l, r, k);
	pushup(i);
}

int findmax(int i, int l, int r){
	if(tree[i].l >= l && tree[i].r <= r) return tree[i].tmax;
	pushdown(i);
	int mid = tree[i].l + tree[i].r >> 1, ans = -2e9;
	if(l <= mid) ans = max(ans, findmax(i << 1, l, r));
	if(r >= mid + 1) ans = max(ans, findmax(i << 1 | 1, l, r));
	return ans;
	pushup(i);
}

int main(){
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++) cin >> a[i];
	build(1, 1, n);
	while(q--){
		int op, x, y, z;
		cin >> op >> x >> y;
		if(op == 1){
			cin >> z;
			add(1, x, y, z);
		}else if(op == 2){
			cin >> z;
			change(1, x, y, z);
		}else if(op == 3){
			cin >> z;
			update(1, x, y, z);
		}else {
			cout << findmax(1, x, y) << endl;
		}
	}
}
```

---

## 作者：liaiyang (赞：0)

一道线段树板子题。

题目要求支持区间加，区间对 $h$ 取 $\max$，区间对 $h$ 取 $\min$，区间求最大值。

我们维护 $maxx$，$add$，$minadd$，$maxadd$ 分别表示最大值，加法标记，取 $\min$ 标记，取 $\max$ 标记。

则对于区间和，我们有
```cpp
tr[now].maxx+=x;
tr[now].add+=x;
if(tr[now].maxadd>-inf) tr[now].maxadd+=x;
if(tr[now].minadd<inf) tr[now].minadd+=x;
```
对于区间对 $h$ 取 $\min$，我们有
```cpp
tr[now].maxx=min(tr[now].maxx,x);
tr[now].maxadd=min(tr[now].maxadd,x);
tr[now].minadd=min(tr[now].minadd,x);
```
对于区间对 $h$ 取 $\max$，我们有
```cpp
tr[now].maxx=max(tr[now].maxx,x);
tr[now].maxadd=max(tr[now].maxadd,x);
tr[now].minadd=max(tr[now].minadd,x);
```
最大值就是正常查询。

下传就把上面全部跑一边，上传就只需要传最大值。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))    
#define lc now<<1
#define rc now<<1|1
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353;
const int N=5e5+10;
struct node{
    int l,r,maxx,add,minadd,maxadd;
};
struct tree{
    node tr[N<<2];
        void pushup(int now){tr[now].maxx=max(tr[lc].maxx,tr[rc].maxx);}
        void pushdown_sum(int now,int x){
            tr[now].maxx+=x;
            tr[now].add+=x;
            if(tr[now].maxadd>-inf) tr[now].maxadd+=x;
            if(tr[now].minadd<inf) tr[now].minadd+=x;
        }
        void pushdown_max(int now,int x){
            tr[now].maxx=max(tr[now].maxx,x);
            tr[now].maxadd=max(tr[now].maxadd,x);
            tr[now].minadd=max(tr[now].minadd,x);
        }
        void pushdown_min(int now,int x){
            tr[now].maxx=min(tr[now].maxx,x);
            tr[now].maxadd=min(tr[now].maxadd,x);
            tr[now].minadd=min(tr[now].minadd,x);
        }
        void pushdown(int now){
            pushdown_sum(lc,tr[now].add),pushdown_sum(rc,tr[now].add);
            pushdown_min(lc,tr[now].minadd),pushdown_min(rc,tr[now].minadd);
            pushdown_max(lc,tr[now].maxadd),pushdown_max(rc,tr[now].maxadd);
            tr[now].add=0,tr[now].maxadd=-inf,tr[now].minadd=inf;
        }
        void build(int now,int l,int r){
            tr[now]={l,r,-inf,0,inf,-inf};
            if(l==r){
                tr[now].maxx=rd;
                return ;
            }
            int mid=l+r>>1;
            build(lc,l,mid);
            build(rc,mid+1,r);
            pushup(now);
        }
        void modify_sum(int now,int l,int r,int x){
            if(l<=tr[now].l&&tr[now].r<=r){
                pushdown_sum(now,x);
                return ;
            }
            int mid=tr[now].l+tr[now].r>>1;
            pushdown(now);
            if(l<=mid) modify_sum(lc,l,r,x);
            if(r>mid) modify_sum(rc,l,r,x);
            pushup(now);
        }
        void modify_max(int now,int l,int r,int x){
            if(l<=tr[now].l&&tr[now].r<=r){
                pushdown_max(now,x);
                return ;
            }
            int mid=tr[now].l+tr[now].r>>1;
            pushdown(now);
            if(l<=mid) modify_max(lc,l,r,x);
            if(r>mid) modify_max(rc,l,r,x);
            pushup(now);
        }
        void modify_min(int now,int l,int r,int x){
            if(l<=tr[now].l&&tr[now].r<=r){
                pushdown_min(now,x);
                return ;
            }
            int mid=tr[now].l+tr[now].r>>1;
            pushdown(now);
            if(l<=mid) modify_min(lc,l,r,x);
            if(r>mid) modify_min(rc,l,r,x);
            pushup(now);
        }
        int query(int now,int l,int r){
            if(l<=tr[now].l&&tr[now].r<=r) return tr[now].maxx;
            int mid=tr[now].l+tr[now].r>>1,ans=-inf,sum;
            pushdown(now);
            if(l<=mid) sum=query(lc,l,r),ans=max(ans,sum);
            if(r>mid) sum=query(rc,l,r),ans=max(ans,sum);
            return ans;
        }
}T;
int n,q;
main(){
    n=rd,q=rd;
    T.build(1,1,n);
    while(q--){
        int op=rd,l=rd,r=rd,x;
        if(op!=4) x=rd;
        if(op==1) T.modify_sum(1,l,r,x);
        if(op==2) T.modify_min(1,l,r,x);
        if(op==3) T.modify_max(1,l,r,x);
        if(op==4) wt(T.query(1,l,r),'\n');
    }
    return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

首先翻译一下这道题的题面。

- 操作 $1$：对 $[l,r]$ 区间加上 $c$。

- 操作 $2$：对 $[l,r]$ 区间和 $h$ 比较取 $\min$ 值。

- 操作 $3$：对 $[l,r]$ 区间和 $h$ 比较取 $\max$ 值。

- 操作 $4$：询问 $[l,r]$ 区间的最大值。

那么这道题就很明显是一道很板子的题了，就是线段树萌新可做题。

接下来我们分点进行讲述。

### 树的节点

我们给每个节点赋上区间 $[l,r]$，最大值 $maxx$，最大值懒标记 $maxTar$，最小值懒标记 $minTar$，和区间加和懒标记 $Tar$ 的值。对于区间修改问题，懒标记是万万不能缺少的。这里的变量名不要纠结，这只是对于我来说好看而已。

### 建树

建树是最简单的一个函数，我们通过分治法逐个给每个节点附上相应的值，就是区间和最大值的设置。当节点区间长度为 $1$ 时，最大值直接赋为 $a_l$。

```cpp
void build_tree(int now,int l,int r)
{
	tree[now].l=l,tree[now].r=r,tree[now].maxTar=-1e18,tree[now].minTar=1e18;
	if(l==r)
	{
		tree[now].maxx=a[l];
		return;
	}
	int mid=(l+r)/2;
	build_tree(now<<1,l,mid);
	build_tree(now<<1|1,mid+1,r);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx);
}
```

### 区间加法

这是线段树的懒标记模板，如果一个区间被需要加和的区间完全覆盖，那么我们就给这个区间节点加一个懒标记，每次需要用到这个区间的具体数据时，我们就直接将这个懒标记向下传播。同时，这个区间的最大值也会加上这个值。

但是，如果前面已经有了最小值懒标记和最大值懒标记，容易知道它们是在加和之前加上去的，所以我们考虑给这两个懒标记也加上区间加法的懒标记（通俗的说，就是这个值随着整体改变而产生改变）。

```cpp
void change_sum_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx+=v,tree[now].Tar+=v;
		if(tree[now].maxTar!=-1e18)	tree[now].maxTar+=v;
		if(tree[now].minTar!=1e18)	tree[now].minTar+=v;
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_sum_tree(now<<1,l,r,v);
	if(r>mid)	change_sum_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx);
}
```

### 区间取最大值

懒标记思路都是一样的，我们也可以改变这个被完全覆盖的区间的最大值，然后，然后就是上文提到的整体思想，一个区间被改变了，内部的其它为使用变量也应该随之进行相应的改变，这里就不用改变区间加和懒标记了，因为我们只会询问最大值，这个加和现在并不会影响实际的最大值。而取 $\min$ 和 $\max$ 的懒标记是需要改变的。

```cpp
void change_max_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx=max(tree[now].maxx,v*1ll);
		tree[now].maxTar=max(tree[now].maxTar,v*1ll);
		tree[now].minTar=max(tree[now].minTar,v*1ll);
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_max_tree(now<<1,l,r,v);
	if(r>mid)	change_max_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx); 
}
```

### 区间取最小值

和上述思路一致，这里不多赘述，原理都是一致的。

```cpp
void change_min_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx=min(tree[now].maxx,v*1ll);
		tree[now].minTar=min(tree[now].minTar,v*1ll);
		tree[now].maxTar=min(tree[now].maxTar,v*1ll);
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_min_tree(now<<1,l,r,v);
	if(r>mid)	change_min_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx); 
}
```

### 懒标记下传

最大工程环节，我们的懒标记只需要向自己的两个儿子节点进行传播，考虑到整体影响的因素，我们依然要按照上文的思路对两个儿子的懒标记进行相应的修改，而且下传完之后，这个懒标记是必须要清除的，不清除的话会对后面新的懒标记产生影响。具体的可以看代码，或者模板。

```cpp
void fixed_tree(int now)
{
	if(tree[now].Tar)
	{
		tree[now<<1].Tar+=tree[now].Tar,tree[now<<1|1].Tar+=tree[now].Tar;
		tree[now<<1].maxx+=tree[now].Tar,tree[now<<1|1].maxx+=tree[now].Tar;
		if(tree[now<<1].maxTar!=-1e18)	tree[now<<1].maxTar+=tree[now].Tar;
		if(tree[now<<1|1].maxTar!=-1e18)	tree[now<<1|1].maxTar+=tree[now].Tar;
		if(tree[now<<1].minTar!=1e18)	tree[now<<1].minTar+=tree[now].Tar;
		if(tree[now<<1|1].minTar!=1e18)	tree[now<<1|1].minTar+=tree[now].Tar;
		tree[now].Tar=0;
	}
	if(tree[now].maxTar!=-1e18)
	{
		tree[now<<1].maxTar=max(tree[now<<1].maxTar,tree[now].maxTar);
		tree[now<<1|1].maxTar=max(tree[now<<1|1].maxTar,tree[now].maxTar);
		tree[now<<1].maxx=max(tree[now<<1].maxx,tree[now].maxTar);
		tree[now<<1|1].maxx=max(tree[now<<1|1].maxx,tree[now].maxTar);
		tree[now<<1].minTar=max(tree[now<<1].minTar,tree[now].maxTar);
		tree[now<<1|1].minTar=max(tree[now<<1|1].minTar,tree[now].maxTar);
		tree[now].maxTar=-1e18;
	}
	if(tree[now].minTar!=1e18)
	{
		tree[now<<1].maxTar=min(tree[now<<1].maxTar,tree[now].minTar);
		tree[now<<1|1].maxTar=min(tree[now<<1|1].maxTar,tree[now].minTar);
		tree[now<<1].minTar=min(tree[now<<1].minTar,tree[now].minTar);
		tree[now<<1|1].minTar=min(tree[now<<1|1].minTar,tree[now].minTar);
		tree[now<<1].maxx=min(tree[now<<1].maxx,tree[now].minTar);
		tree[now<<1|1].maxx=min(tree[now<<1|1].maxx,tree[now].minTar);
		tree[now].minTar=1e18;
	}
}
```

### 区间询问最大值

这个由于我们以前已经统计了最大值了，所以我们进行分区间的最大值，然后所有的再取一个整体最大值。考虑到这里是可能需要将区间进行拆分的，所以我们需要下传懒标记。

```cpp
long long query(int now,int l,int r)
{
	if(l<=tree[now].l&&tree[now].r<=r)	return tree[now].maxx;
	fixed_tree(now);
	long long res=-1e18;
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	res=max(res,query(now<<1,l,r));
	if(r>mid)	res=max(res,query(now<<1|1,l,r));
	return res;
}
```

### 小小卡常

这样写貌似可能会很慢，又考虑到输入的数据类型可能不一样，所以我写了两个快读。

### 全部代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
int n,m;
long long a[MAXN];
struct node
{
	int l,r;
	long long maxx,Tar,maxTar,minTar;
}tree[MAXN<<2];
void build_tree(int now,int l,int r)
{
	tree[now].l=l,tree[now].r=r,tree[now].maxTar=-1e18,tree[now].minTar=1e18;
	if(l==r)
	{
		tree[now].maxx=a[l];
		return;
	}
	int mid=(l+r)/2;
	build_tree(now<<1,l,mid);
	build_tree(now<<1|1,mid+1,r);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx);
}
void fixed_tree(int now)
{
	if(tree[now].Tar)
	{
		tree[now<<1].Tar+=tree[now].Tar,tree[now<<1|1].Tar+=tree[now].Tar;
		tree[now<<1].maxx+=tree[now].Tar,tree[now<<1|1].maxx+=tree[now].Tar;
		if(tree[now<<1].maxTar!=-1e18)	tree[now<<1].maxTar+=tree[now].Tar;
		if(tree[now<<1|1].maxTar!=-1e18)	tree[now<<1|1].maxTar+=tree[now].Tar;
		if(tree[now<<1].minTar!=1e18)	tree[now<<1].minTar+=tree[now].Tar;
		if(tree[now<<1|1].minTar!=1e18)	tree[now<<1|1].minTar+=tree[now].Tar;
		tree[now].Tar=0;
	}
	if(tree[now].maxTar!=-1e18)
	{
		tree[now<<1].maxTar=max(tree[now<<1].maxTar,tree[now].maxTar);
		tree[now<<1|1].maxTar=max(tree[now<<1|1].maxTar,tree[now].maxTar);
		tree[now<<1].maxx=max(tree[now<<1].maxx,tree[now].maxTar);
		tree[now<<1|1].maxx=max(tree[now<<1|1].maxx,tree[now].maxTar);
		tree[now<<1].minTar=max(tree[now<<1].minTar,tree[now].maxTar);
		tree[now<<1|1].minTar=max(tree[now<<1|1].minTar,tree[now].maxTar);
		tree[now].maxTar=-1e18;
	}
	if(tree[now].minTar!=1e18)
	{
		tree[now<<1].maxTar=min(tree[now<<1].maxTar,tree[now].minTar);
		tree[now<<1|1].maxTar=min(tree[now<<1|1].maxTar,tree[now].minTar);
		tree[now<<1].minTar=min(tree[now<<1].minTar,tree[now].minTar);
		tree[now<<1|1].minTar=min(tree[now<<1|1].minTar,tree[now].minTar);
		tree[now<<1].maxx=min(tree[now<<1].maxx,tree[now].minTar);
		tree[now<<1|1].maxx=min(tree[now<<1|1].maxx,tree[now].minTar);
		tree[now].minTar=1e18;
	}
}
void change_sum_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx+=v,tree[now].Tar+=v;
		if(tree[now].maxTar!=-1e18)	tree[now].maxTar+=v;
		if(tree[now].minTar!=1e18)	tree[now].minTar+=v;
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_sum_tree(now<<1,l,r,v);
	if(r>mid)	change_sum_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx);
}
void change_max_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx=max(tree[now].maxx,v*1ll);
		tree[now].maxTar=max(tree[now].maxTar,v*1ll);
		tree[now].minTar=max(tree[now].minTar,v*1ll);
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_max_tree(now<<1,l,r,v);
	if(r>mid)	change_max_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx); 
}
void change_min_tree(int now,int l,int r,int v)
{
	if(l<=tree[now].l&&tree[now].r<=r)
	{
		tree[now].maxx=min(tree[now].maxx,v*1ll);
		tree[now].minTar=min(tree[now].minTar,v*1ll);
		tree[now].maxTar=min(tree[now].maxTar,v*1ll);
		return;
	}
	fixed_tree(now);
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	change_min_tree(now<<1,l,r,v);
	if(r>mid)	change_min_tree(now<<1|1,l,r,v);
	tree[now].maxx=max(tree[now<<1].maxx,tree[now<<1|1].maxx); 
}
long long query(int now,int l,int r)
{
	if(l<=tree[now].l&&tree[now].r<=r)	return tree[now].maxx;
	fixed_tree(now);
	long long res=-1e18;
	int mid=(tree[now].l+tree[now].r)/2;
	if(l<=mid)	res=max(res,query(now<<1,l,r));
	if(r>mid)	res=max(res,query(now<<1|1,l,r));
	return res;
}
void read(int &x)
{
	x=0;
	short flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')	flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=flag;
}
void rd(long long &x)
{
	x=0;
	short flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')	flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=flag;
}
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;i++)	rd(a[i]);
	build_tree(1,1,n);
	while(m--)
	{
		int opt;
		int x,y,z;
		read(opt),read(x),read(y);
		if(opt==1)
		{
			read(z);
			change_sum_tree(1,x,y,z);
		}
		if(opt==2)
		{
			read(z);
			change_min_tree(1,x,y,z);
		}
		if(opt==3)
		{
			read(z);
			change_max_tree(1,x,y,z);
		}
		if(opt==4)	printf("%lld\n",query(1,x,y));
	}
	return 0;
}
```

---

## 作者：Jusc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8024)

## 题外话

刚写完就由蓝变紫了

这题与[这个](https://www.luogu.com.cn/problem/P4560)貌似差不多？~~双倍紫色经验~~

## 正文

### 题意简化

对一个序列进行以下操作：

* 操作 1：$ l $ 到 $ r $ 之间的数加上 $ c $。

* 操作 2：$ l $ 到 $ r $ 之间的数与 $ h $ 取 $ \min $。

* 操作 3：$ l $ 到 $ r $ 之间的数与 $ h $ 取 $ \max $。

* 操作 4：询问 $ l $ 到 $ r $ 之间的最大值。

### 思路

显然的，本题应使用**线段树**。

1. 对于操作一，是基础的区间加操作，维护一个 $ addtag $ 即可。

1. 对于操作二和三，与其他操作有点不一样，请看下面分析。

1. 对于操作四，维护区间最值，很基础，维护 $ maxtree $ 即可。

### 分析

对于区间加的 $ addtag $ 这里不讲。

只详细讲解 $ mintag $ ——区间取 $ \min $ 与 $ maxtag $ ——区间取 $ \max $。

eg1: （这里对整体操作方便理解）

```
序列：
3 7 5 4 3 2 最大值：7
与 3 取 max 后：
3 7 5 4 3 3 最大值：7
与 5 取 max 后:
5 7 5 5 5 5 最大值：7
```

由上面的栗子可以看出：多个连续 $ max $ 操作只需要取最大的即可。

即 : $ maxtag \gets \max(maxtag,h) $，
	 $ maxtree \gets \max(maxtree,h) $。

同理 ： $ mintag \gets \min(mitag,h) $，
		$ maxtree \gets \min(maxtree,h) $。

但这里最麻烦的是取 $ \min $ 和取 $ \max $ 之间的互相影响。

eg2:(同上这里操作对整体)

```
序列：
2 3 7 6 5 1 9 
与 6 取 max 后：
6 6 7 6 6 6 9
与 4 取 min 后：
4 4 4 4 4 4 4
与 5 取 max 后：
5 5 5 5 5 5 5
```
如上面的栗子，可发现取 $ \max $ 的操作并**不影响**取 $ \min $。

以上的操作其实等同于：先与 $ 4 $ 取 $ \min $ 再与 $ 5 $ 取 $ \max $。

eg3:（…）

```
序列：
2 3 7 6 5 1 9
与 4 取 min 后：
2 3 4 4 4 1 4
与 6 取 max 后：
6 6 6 6 6 6 6
与 5 取 min 后：
5 5 5 5 5 5 5  
```
如上面的栗子，可发现取 $ \min $ 的操作**影响**取 $ \max $。

以上操作其实等同于：同时与 $ 5 $ 取 $ \max $ 与 $ \min $。 

所以，$ maxtag $ 是在第三个操作时与 $ h $ 即 $ 5 $ 取 $ \min $ 了。

#### 结论

综上所述：

* 区间加不叙述，具体看代码。

* 取 $ max $ 时只需两个操作：

1. $ maxtree \gets \max(maxtree,h) $

1. $ maxtag \gets \max(maxtag,h) $

* 取 $ min $ 时需三个操作：

1. $ mintree \gets \min(maxtree,h) $

1. $ mintag \gets \min(mintag,h) $

1. $ maxtag \gets \min(maxtag,h) $

## Code：

```cpp
#include<bits/stdc++.h>
	
using namespace std;
	
const int N=5*1e5+10;
const int INF=2e9;
struct Yan
{	
	int l,r;
	int maxt;
	int atg,ntg,xtg;
}tr[N*4];
int w[N];
int n,m;

void moveadd(Yan &u,int s)//简化代码
{
	u.maxt+=s;
	u.atg+=s;
	u.xtg+=s;
	u.ntg+=s;
}
void moven(Yan &u,int s)
{
	u.maxt=min(u.maxt,s);
	u.xtg=min(u.xtg,s);
	u.ntg=min(u.ntg,s);
}
void movex(Yan &u,int s)
{
	u.maxt=max(u.maxt,s);
	u.xtg=max(u.xtg,s);
}
void pushup(Yan &u,Yan &l,Yan &r)
{	
	u.maxt=max(l.maxt,r.maxt);
}	
void pushdown(Yan &u,Yan &l,Yan &r)
{
	moveadd(l,u.atg);moveadd(r,u.atg);
	u.atg=0;
	moven(l,u.ntg);moven(r,u.ntg);
	u.ntg=INF;
	movex(l,u.xtg);movex(r,u.xtg);
	u.xtg=-INF;
} 
void pushdown(int u)
{	
	pushdown(tr[u],tr[u<<1],tr[u<<1|1]);
}	
void pushup(int u)
{	
	pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}	
void build(int u,int l,int r)
{	
	tr[u].l=l,tr[u].r=r;
	tr[u].ntg=INF,tr[u].xtg=-INF;
	if(l==r) tr[u].maxt=w[r];
	else 
	{
		int mid=(l+r)>>1;
		build(u<<1,l,mid),build(u<<1|1,mid+1,r);
		pushup(u);
	}
}	
void modify_atg(int u,int l,int r,int v)
{
	if(tr[u].l>=l&&tr[u].r<=r) moveadd(tr[u],v);
	else 
	{
		pushdown(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		if(mid>=l) modify_atg(u<<1,l,r,v);
		if(mid<r) modify_atg(u<<1|1,l,r,v);
		pushup(u);
	}
}
void modify_ntg(int u,int l,int r,int v)
{
	if(tr[u].l>=l&&tr[u].r<=r) moven(tr[u],v);
	else 
	{
		pushdown(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		if(mid>=l) modify_ntg(u<<1,l,r,v);
		if(mid<r) modify_ntg(u<<1|1,l,r,v);
		pushup(u);
	}
}
void modify_xtg(int u,int l,int r,int v)
{
	if(tr[u].l>=l&&tr[u].r<=r) movex(tr[u],v);
	else 
	{
		pushdown(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		if(mid>=l) modify_xtg(u<<1,l,r,v);
		if(mid<r) modify_xtg(u<<1|1,l,r,v);
		pushup(u);
	}
}
Yan query(int u,int l,int r)
{
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u];
	else
	{
		pushdown(u);
		int mid=(tr[u].l+tr[u].r)>>1;
		if(mid>=r) return query(u<<1,l,r);
		else if(mid<l) return query(u<<1|1,l,r);
		else 
		{
			Yan res,res1,res2;
			res1=query(u<<1,l,r);
			res2=query(u<<1|1,l,r);
			pushup(res,res1,res2);
			return res;
		}
	}
}

int main()
{	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	build(1,1,n);
	while(m--)
	{
		int op,l,r,v;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&l,&r,&v);
			modify_atg(1,l,r,v); 
		}
		else if(op==2)
		{
			scanf("%d%d%d",&l,&r,&v);
			modify_ntg(1,l,r,v);
		}
		else if(op==3)
		{
			scanf("%d%d%d",&l,&r,&v);
			modify_xtg(1,l,r,v);
		}
		else
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",query(1,l,r).maxt);
		}
	}
	return 0;
}	
```
完结撒花ヾ(≧▽≦*)o

---

## 作者：Sternenlicht (赞：0)

思路：

$1$ 操作是区修和，$2$ 操作是区修 $\min$，$3$ 操作是区修 $\max$，$4$ 操作是区间查询 $\max$。

理解完操作后，思路就出来了。维护四个变量：当前值 $val$，和懒标记 $sumtag$，最小值懒标记 $mintag$，最大值懒标记 $maxtag$ 。

建树操作：对于 $mintag$ 赋值为 $+\infty$，$maxtag$ 赋值为 $-\infty$，同时记录区间左端点 $l$ 和右端点 $r$。

``pushdown`` 操作：将当前结点 $now$ 的左儿子与右儿子的懒标记和值分别更新，更新时是与 $now$ 的三个懒标记求值。

区修和操作：将三个懒标记和当前值 $val$ 都加上 $c$。

区修 $\min$ 操作：将三个懒标记和当前值 $val$ 都对 $h$ 取 $\min$。

区修 $\max$ 操作：将三个懒标记和当前值 $val$ 都对 $h$ 取 $\max$。

查询操作：在 $[l,r]$ 的区间内取最大值。


```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

#define int long long
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
const int N = 2e6+10;
const int INF = 2e18;
struct Sgt{int l,r,val,sumtag,mintag,maxtag;}tree[N<<2];
int a[N],n,q;
void pushup(int now)//更新当前结点信息 
{tree[now].val=max(tree[ls(now)].val,tree[rs(now)].val);}
void build(int now,int l,int r){//建树 
	tree[now].l=l,tree[now].r=r;
	tree[now].mintag=INF,tree[now].maxtag=-INF;
	if (l==r)return tree[now].val=a[l],void();
	int mid=(l+r)>>1;
	build(ls(now),l,mid);
	build(rs(now),mid+1,r);
	pushup(now);
}
void push_add(int now,int val){//更新sum懒标记 
	tree[now].val+=val;
	tree[now].sumtag+=val;
	if (tree[now].mintag<INF) tree[now].mintag+=val;
	if (tree[now].maxtag>-INF)tree[now].maxtag+=val;
}
void push_min(int now,int val){//更新min懒标记 
	tree[now].val=min(tree[now].val,val);
	tree[now].mintag=min(tree[now].mintag,val);
	tree[now].maxtag=min(tree[now].maxtag,val);
}
void push_max(int now,int val){//更新max懒标记 
	tree[now].val=max(tree[now].val,val);
	tree[now].mintag=max(tree[now].mintag,val);
	tree[now].maxtag=max(tree[now].maxtag,val);
}
void pushdown(int now){//pushdown下传标记 
	push_add(ls(now),tree[now].sumtag);
	push_add(rs(now),tree[now].sumtag);
	push_min(ls(now),tree[now].mintag);
	push_min(rs(now),tree[now].mintag);
	push_max(ls(now),tree[now].maxtag);
	push_max(rs(now),tree[now].maxtag);
	tree[now].sumtag=0;
	tree[now].mintag=INF;
	tree[now].maxtag=-INF;
}
void update_add(int now,int x,int y,int val){//区修加 
	int l=tree[now].l,r=tree[now].r;
	if (x<=l&&r<=y)return push_add(now,val),void();
	pushdown(now);int mid=(l+r)>>1;
	if (x<=mid)update_add(ls(now),x,y,val);
	if (mid<y) update_add(rs(now),x,y,val);
	pushup(now);
}
void update_min(int now,int x,int y,int val){//区修min 
	int l=tree[now].l,r=tree[now].r;
	if (x<=l&&r<=y)return push_min(now,val),void();
	pushdown(now);int mid=(l+r)>>1;
	if (x<=mid)update_min(ls(now),x,y,val);
	if (mid<y) update_min(rs(now),x,y,val);
	pushup(now);
}
void update_max(int now,int x,int y,int val){//区修max 
	int l=tree[now].l,r=tree[now].r;
	if (x<=l&&r<=y)return push_max(now,val),void();
	pushdown(now);int mid=(l+r)>>1;
	if (x<=mid)update_max(ls(now),x,y,val);
	if (mid<y) update_max(rs(now),x,y,val);
	pushup(now);
}
int query(int now,int x,int y){//区间查询最大值 
	int l=tree[now].l,r=tree[now].r;
	if (x<=l&&r<=y)return tree[now].val;
	pushdown(now);int mid=(l+r)>>1,ans=-INF;
	if (x<=mid)ans=max(ans,query(ls(now),x,y));
	if (mid<y) ans=max(ans,query(rs(now),x,y));
	return ans;
}
signed main(){
	n=read(),q=read();
	for (int i=1;i<=n;i++)a[i]=read();
	build(1,1,n);
	for (int i=1;i<=q;i++){
		int op=read(),l=read(),r=read(),val;
		if (op==1)val=read(),update_add(1,l,r,val);
		if (op==2)val=read(),update_min(1,l,r,val);
		if (op==3)val=read(),update_max(1,l,r,val);
		if (op==4)write(query(1,l,r));
	}
	return 0;
}
```

---

## 作者：newbeeglass (赞：0)

简化题意，给你一个序列，对其进行以下几种操作：

1.给 $l$ 到 $r$ 区间内的数据全部加上 $k$。

2.对于 $l$ 到 $r$ 区间内的数据，大于 $k$ 的变成 $k$。

3.对于 $l$ 到 $r$ 区间内的数据，小于 $k$ 的变成 $k$。

4.输出 $l$ 到 $r$ 区间内的最大值。

一步步来看，要实现 $1$ 操作很简单，线段树板子，主要看 $2$ 操作和 $3$ 操作。对于 $2$ 操作，假如一个序列中最小值大于 $k$，那么这个序列的所有数也一定大于 $k$，直接对其进行赋值操作即可，假如并不如此，那就继续往下二分，直到满足条件为止，当然直接这样找有点浪费时间，需要一点优化：假如一个序列的最大值小于 $k$，里面的所有数也必然小于 $k$，遇到这种情况直接 ```return``` 就好了，避免多余操作。操作 $3$ 也是如此。

也就是说，线段树的结构体中出了需要存储区间左右端点和最大值以外，还需要存储最小值、加法懒标记和赋值懒标记，由于我数据范围没仔细看，所以我还另外开了一个判断是否赋值的懒标记（防止出现赋值懒标记为 $0$ 却依然需要赋值的情况，但实际上并没有这种情况）。
```cpp
struct tree{
	int l,r;
	int maxn,minx,lazy1,lazy2,lazy3;//lazy1是加法标记，lazy2是赋值标记，lazy3判断是否赋值
}t[3000005];
```
$2$ 操作代码如下：
```cpp
void change1(int p,int x,int y,int z){
	if(x<=t[p].l && y>=t[p].r){
		if(t[p].minx>=z){
			t[p].maxn=z;
			t[p].minx=z;
			t[p].lazy2=z;
			t[p].lazy3=1;
			t[p].lazy1=0;//赋过值了，加法标记就没意义了
			return;
		}
		if(t[p].maxn<=z){
			return;
		}
		pushdown(p);
		change1(p*2,x,y,z);
		change1(p*2+1,x,y,z);
		pushup(p);
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid){
		change1(p*2,x,y,z);
	}
	if(y>mid){
		change1(p*2+1,x,y,z);
	}
	pushup(p);
}
```
理解了这些以后，```pushdown``` 函数就比较好写了，注意要先赋值，再增加：
```cpp
void pushdown(int p){
	if(t[p].lazy3){
		t[p*2].maxn=t[p].lazy2;
		t[p*2+1].maxn=t[p].lazy2;
		t[p*2].minx=t[p].lazy2;
		t[p*2+1].minx=t[p].lazy2;
		t[p*2].lazy2=t[p].lazy2;
		t[p*2+1].lazy2=t[p].lazy2;
		t[p*2].lazy1=0;
		t[p*2+1].lazy1=0;
		t[p*2].lazy3=1;
		t[p*2+1].lazy3=1;
		t[p].lazy2=0;
		t[p].lazy3=0;//不要把当前结点的lazy1变成0，因为会出现赋完值后继续增加的情况
	}
	if(t[p].lazy1){
		t[p*2].maxn+=t[p].lazy1;
		t[p*2].minx+=t[p].lazy1;
		t[p*2+1].maxn+=t[p].lazy1;
		t[p*2+1].minx+=t[p].lazy1;
		t[p*2].lazy1+=t[p].lazy1;
		t[p*2+1].lazy1+=t[p].lazy1;
		t[p].lazy1=0;
	}
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[1000001];
struct tree{
	int l,r;
	int maxn,minx,lazy1,lazy2,lazy3;
}t[3000005];
void pushup(int p){
	t[p].minx=min(t[p*2].minx,t[p*2+1].minx);
	t[p].maxn=max(t[p*2].maxn,t[p*2+1].maxn);
}
void build(int p,int x,int y){
	t[p].l=x;
	t[p].r=y;
	if(x==y){
		t[p].maxn=a[x];
		t[p].minx=a[x];
		return;
	}
	int mid=x+y>>1;
	build(p*2,x,mid);
	build(p*2+1,mid+1,y);
	pushup(p);
}
void pushdown(int p){
	if(t[p].lazy3){
		t[p*2].maxn=t[p].lazy2;
		t[p*2+1].maxn=t[p].lazy2;
		t[p*2].minx=t[p].lazy2;
		t[p*2+1].minx=t[p].lazy2;
		t[p*2].lazy2=t[p].lazy2;
		t[p*2+1].lazy2=t[p].lazy2;
		t[p*2].lazy1=0;
		t[p*2+1].lazy1=0;
		t[p*2].lazy3=1;
		t[p*2+1].lazy3=1;
		t[p].lazy2=0;
		t[p].lazy3=0;
	}
	if(t[p].lazy1){
		t[p*2].maxn+=t[p].lazy1;
		t[p*2].minx+=t[p].lazy1;
		t[p*2+1].maxn+=t[p].lazy1;
		t[p*2+1].minx+=t[p].lazy1;
		t[p*2].lazy1+=t[p].lazy1;
		t[p*2+1].lazy1+=t[p].lazy1;
		t[p].lazy1=0;
	}
}
void change1(int p,int x,int y,int z){
	if(x<=t[p].l && y>=t[p].r){
		if(t[p].minx>=z){
			t[p].maxn=z;
			t[p].minx=z;
			t[p].lazy2=z;
			t[p].lazy3=1;
			t[p].lazy1=0;
			return;
		}
		if(t[p].maxn<=z){
			return;
		}
		pushdown(p);
		change1(p*2,x,y,z);
		change1(p*2+1,x,y,z);
		pushup(p);
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid){
		change1(p*2,x,y,z);
	}
	if(y>mid){
		change1(p*2+1,x,y,z);
	}
	pushup(p);
}
void change2(int p,int x,int y,int z){
	if(x<=t[p].l && y>=t[p].r){
		if(t[p].maxn<=z){
			t[p].maxn=z;
			t[p].minx=z;
			t[p].lazy2=z;
			t[p].lazy3=1;
			t[p].lazy1=0;
			return;
		}
		if(t[p].minx>=z){
			return;
		}
		pushdown(p);
		change2(p*2,x,y,z);
		change2(p*2+1,x,y,z);
		pushup(p);
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid){
		change2(p*2,x,y,z);
	}
	if(y>mid){
		change2(p*2+1,x,y,z);
	}
	pushup(p);
}
void change3(int p,int x,int y,int z){
	if(x<=t[p].l && y>=t[p].r){
		t[p].maxn+=z;
		t[p].minx+=z;
		t[p].lazy1+=z;
		return;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if(x<=mid){
		change3(p*2,x,y,z);
	}
	if(y>mid){
		change3(p*2+1,x,y,z);
	}
	pushup(p);
}
int ask(int p,int x,int y){
	if(x<=t[p].l && y>=t[p].r){
		return t[p].maxn;
	}
	int mid=t[p].l+t[p].r>>1;
	int ans=-1e9;
	pushdown(p);
	if(x<=mid){
		ans=max(ans,ask(p*2,x,y));
	}
	if(y>mid){
		ans=max(ans,ask(p*2+1,x,y));
	}
	return ans;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	build(1,1,n);
	while(q--){
		int s,x,y,z;
		scanf("%d%d%d",&s,&x,&y);
		if(s==1){
			scanf("%d",&z);
			change3(1,x,y,z);
		}
		else if(s==2){
			scanf("%d",&z);
			change1(1,x,y,z);
		}
		else if(s==3){
			scanf("%d",&z);
			change2(1,x,y,z);
		}
		else{
			printf("%d\n",ask(1,x,y));
		}
	}
	return 0;
}

```


---

