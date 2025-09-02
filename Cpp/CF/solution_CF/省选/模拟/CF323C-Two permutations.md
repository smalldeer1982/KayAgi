# Two permutations

## 题目描述

You are given two permutations $ p $ and $ q $ , consisting of $ n $ elements, and $ m $ queries of the form: $ l_{1},r_{1},l_{2},r_{2} $ $ (l_{1}<=r_{1}; l_{2}<=r_{2}) $ . The response for the query is the number of such integers from $ 1 $ to $ n $ , that their position in the first permutation is in segment $ [l_{1},r_{1}] $ (borders included), and position in the second permutation is in segment $ [l_{2},r_{2}] $ (borders included too).

A permutation of $ n $ elements is the sequence of $ n $ distinct integers, each not less than $ 1 $ and not greater than $ n $ .

Position of number $ v $ $ (1<=v<=n) $ in permutation $ g_{1},g_{2},...,g_{n} $ is such number $ i $ , that $ g_{i}=v $ .

## 样例 #1

### 输入

```
3
3 1 2
3 2 1
1
1 2 3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
4 3 2 1
2 3 4 1
3
1 2 3 4
1 3 2 1
1 4 2 3
```

### 输出

```
1
1
2
```

# 题解

## 作者：优秀的渣渣禹 (赞：8)

###### 蒟蒻渣渣禹小心翼翼发布题解qwq
英文题目欸。。。来我给大家简单粗暴的翻译一下题目：

给你两个长度为n的1−n排列，多次询问在第一个排列的[l1,r1]和第二个排列的[l2,r2]同时出现的数有多少个。

然而这题翻译过来一看。。。。好像有点水qwq

把第二个排列的数在第一个排列中对应的位置记一下，主席树跑一跑就行了。

然而事实确实如此qwq，下面附上主席树的代码qwq：

~~各位评分的时候记得评个黑题qwq。。。。我啊好不容易把它从暂无评定评成黑题qwq。。。。~~

各位大佬点个赞再走呗qwq
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define gc getchar()
#define mid (l + r >> 1)
#define N 2000005
#define M 40000005
using namespace std;
int ln[M],rn[M],sum[M],root[N];
int n,a[N],pos[N],q,ans,cnt;
int read()
{
    int x = 1;
    char ch;
    while (ch = gc,ch < '0' || ch > '9') 
		if (ch == '-') 
			x = -1;
    int s = ch-'0';
    while (ch = gc,ch >= '0' && ch <= '9') 
		s = s * 10 + ch - '0';
    return s * x;
}
void ins(int &cur,int l,int r,int x,int last)
{
    cur = ++cnt;
    ln[cur] = ln[last];
    rn[cur] = rn[last];
    sum[cur] = sum[last] + 1;
    if (l == r) 
		return;
    if (x <= mid) 
		ins(ln[cur],l,mid,x,ln[last]);
    else ins(rn[cur],mid + 1,r,x,rn[last]);
}
int qry(int cur,int l,int r,int L,int R)
{
    if (L <= l && R >= r) 
		return sum[cur];
    int ret = 0;
    if (L <= mid) 
		ret += qry(ln[cur],l,mid,L,R);
    if (R > mid) 
		ret += qry(rn[cur],mid + 1,r,L,R);
    return ret;
}
int f(int x)
{
    return (x - 1 + ans) % n + 1;
}
int main()
{
    n = read();
    for(int i = 1;i <= n;i++) 
		pos[read()] = i;
    for(int i = 1;i <= n;i++) 
		a[i] = pos[read()];
    for(int i = 1;i <= n;i++) 
		ins(root[i],1,n,a[i],root[i - 1]);
    q = read();
    while(q--)
    {
        int x = f(read()),y = f(read()),z = f(read()),w = f(read());
        if (x > y) 
			swap(x,y);
        if (z > w) 
			swap(z,w);
        printf("%d\n",ans = qry(root[w],1,n,x,y) - qry(root[z - 1],1,n,x,y));
        ans++;
    }
    return 0;
}

```

---

## 作者：henrytb (赞：4)

[**更好的阅读体验**](https://blog.henrytb.ml/2021/01/%E9%A2%98%E8%A7%A3-CF323C-Two-permutations/)

话说这题怎么评到黑的？？

我们可以把第二个排列中的数在第一个排列中出现的位置都处理出来。

然后对于每个询问，答案就变成了第二个序列中 $[l_2,r_2]$ 这个区间内，在第一个序列中位置处于 $[l_1,r_1]$ 的数的个数。

我们以第二个排列的下标为版本，以对应的第一个排列中的位置为下标建立一棵可持久化线段树。

具体就是扫一遍这个序列，对于序列中的每一个数都在前一个数的基础上新建一个版本，以这个数为下标在这个版本上 $+1$。然后答案就是版本 $r_2$ 与版本 $l_2-1$ 中询问 $[l_1,r_1]$ 这两个区间的区间和做差。

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=1e6+5;
int n,a[N],b[N],tmp[N],m;
struct Segment{
    int val,ls,rs;
}t[N*32];
int rt[N];
int lst=0;
int tot=0;
int f(int x) {
    return (x+lst-1)%n+1;
}
void modify(int &p,int q,int l,int r,int val) {
    p=++tot;
    t[p].ls=t[q].ls;
    t[p].rs=t[q].rs;
    t[p].val=t[q].val+1;
    if(l==r) return ;
    int mid=(l+r)>>1;
    if(val<=mid) modify(t[p].ls,t[q].ls,l,mid,val);
    else modify(t[p].rs,t[q].rs,mid+1,r,val);
}
int query(int p,int l,int r,int ql,int qr) {
    if(ql<=l&&r<=qr) return t[p].val;
    int mid=(l+r)>>1,ans=0;
    if(ql<=mid) ans+=query(t[p].ls,l,mid,ql,qr);
    if(mid<qr) ans+=query(t[p].rs,mid+1,r,ql,qr);
    return ans;
}
int main() {
    scanf("%d",&n);
    rep(i,1,n) {
        scanf("%d",&a[i]);
        tmp[a[i]]=i;
    }
    rep(i,1,n) {
        scanf("%d",&b[i]);
        a[i]=tmp[b[i]];
        modify(rt[i],rt[i-1],1,n,a[i]);
    }
    scanf("%d",&m);
    rep(i,1,m) {
        int l1,l2,r1,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        l1=f(l1),l2=f(l2),r1=f(r1),r2=f(r2);
        if(l1>r1) swap(l1,r1);
        if(l2>r2) swap(l2,r2);
        lst=query(rt[r2],1,n,l1,r1)-query(rt[l2-1],1,n,l1,r1);
        printf("%d\n",lst);
        ++lst;
    }
    return 0;
}
```

---

## 作者：L_M_ (赞：3)

题意：给你两个长度为n的排列，多次询问在第一个排列的[l1,r1]和第二个排列的[l2,r2]同时出现的数有多少个。

强制在线，具体在题里有

题解：
	我们考虑以下数组：记录b中第i个数在a中出现的位置，用主席树维护这个数组。那么问题便转化为：求l2-r2内有多少个数的值在[l1,r1]之间
    
这个问题就可以用主席树解决啦！具体的，我们用第r1次的答案减去第(l1 - 1)次的答案就ok了

```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read()
{
	int ans = 0,op = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') op = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		(ans *= 10) += ch - '0';
		 ch = getchar();
	}
	return ans * op;
}
const int maxn = 1e6 + 5;
int a[maxn],b[maxn];
int sum[maxn << 5],ls[maxn << 5],rs[maxn << 5],rt[maxn << 5];
int cnt;
void build(int &t,int l,int r)
{
	t = ++cnt;
	if(l == r) return;
	int mid = l + r >> 1;
	build(ls[t],l,mid);
	build(rs[t],mid + 1,r);
}
int modify(int t,int l,int r,int p)//返回新的根节点 
{
	int cur = ++cnt;
	ls[cur] = ls[t],rs[cur] = rs[t],sum[cur] = sum[t] + 1;
	if(l == r) return cur; 
	int mid = l + r >> 1;
	if(p <= mid) ls[cur] = modify(ls[cur],l,mid,p);
	else rs[cur] = modify(rs[cur],mid + 1,r,p);
	return cur;
}
int query(int i,int l,int r,int ql,int qr)
{
	if(l == ql && r == qr) return sum[i];
	int mid = l + r >> 1;
	if(qr <= mid) return query(ls[i],l,mid,ql,qr);
	else if(ql > mid) return query(rs[i],mid + 1,r,ql,qr);
	else return query(ls[i],l,mid,ql,mid) + query(rs[i],mid + 1,r,mid + 1,qr);
}
int lastans,n;
int f(int x)
{
	return (x - 1 + lastans) % n + 1;
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i++) b[read()] = i;
	for(int i = 1;i <= n;i++) a[i] = b[read()];
	build(rt[0],1,n);
	for(int i = 1;i <= n;i++) rt[i] = modify(rt[i - 1],1,n,a[i]);
	int m = read();
	while(m--)
	{
		int l1 = read(),r1 = read(),l2 = read(),r2 = read();
		l1 = f(l1),r1 = f(r1),l2 = f(l2),r2 = f(r2);
		if(l1 > r1) swap(l1,r1);
		if(l2 > r2) swap(l2,r2);
		printf("%d\n",lastans = query(rt[r2],1,n,l1,r1) - query(rt[l2 - 1],1,n,l1,r1));
		lastans++;
	}
}
		
	

```

---

## 作者：Dfkuaid (赞：2)

> [题目链接](https://www.luogu.com.cn/problem/CF323C)

## #0.0 简单翻译

给定两个长为 $n$ 的**排列** $a,b$，有 $m$ 次询问，每次询问包含 $4$ 个整数 $l_1,r_1,l_2,r_2$，问数组 $a$ 上在区间 $[l_1,r_1]$ 与数组 $b$ 上在区间 $[l_2,r_2]$ 中有多少个相同的数。

本题**强制在线**，设 $x$ 为上次询问的结果加一（若之前没有询问 $x=0$），定义函数 $f(z)$ 如下：

$$
f(z)=((z-1+x)\bmod n)+1,
$$

每次询问给出 $4$ 个整数 $a, b, c, d$，有

$$
\begin{aligned}
l_1&=\min\{f(a),f(b)\},\\
r_1&=\max\{f(a),f(b)\},\\
l_2&=\min\{f(c),f(d)\},\\
r_2&=\max\{f(c),f(d)\}.
\end{aligned}
$$

## #1.0 简单思路

题目告诉我们 $a$ 和 $b$ 是两个排列，所以对于 $i\in[1,n]$，每个 $i$ 在 $a$ 中出现一次，在 $b$ 中出现一次，考虑通过相同的数将 $a$ 与 $b$ 联系起来，同时需要保证联系起来后的不同的数在对应序列中的相对位置不改变，于是将 $i\in[1,n]$ 在 $a$ 中出现的位置 $x$ 作为第一维坐标，在 $b$ 中出现的位置 $y$ 作为第二位坐标，于是便将一个数 $i$ 转化为了平面直角坐标系上的一个点，横轴是 $a$ 数列的下标，纵轴是 $b$ 数组的下标，显然这样做原数列中的数的相对位置没有改变。

现在问题变为了给定 $l_1,r_1,l_2,r_2$，求在四点 $(l_1,l_2),(l_1,r_2),(l_2,r_2),(l_2,r_1)$ 围成的矩形中出现的点的数量。

这个问题是**主席树**的经典运用。我们将每一个 $x$ 看作一个版本，主席树每个叶节点对应一个 $y$，每次将对应 $x$ 上所有的点插入主席树，即主席树上对应 $y$ 上的计数加一，维护区间和。

那么，我们每次查询所要的答案的便是 $r_1$ 版本的 $[l_2,r_2]$ 的区间和减去 $l_1-1$ 版本的 $[l_2,r_2]$ 的区间和。

比如样例二转化后便如下图：

![](https://pic.imgdb.cn/item/60fe9ec75132923bf827aa68.png)

途中框出部分是第一次讯问的覆盖范围。

## #2.0 代码实现

``` cpp
const int M = 1000010;
const int N = 40000010;
const int INF = 0x3fffffff;

template <typename T>
inline T Max(const T a, const T b) {
    return a > b ? a : b;
}

template <typename T>
inline T Min(const T a, const T b) {
    return a < b ? a : b;
}

struct Point {
    int x, y;

    inline bool operator < (const Point b) const {
        /*重载运算符，保证按 x 自小向大插入主席树*/
        return (x == b.x) ? (y <= b.y) : (x < b.x);
    }
};
Point t[M];

struct Node {
    int ls, rs;
    int val;
};
Node p[N];

int n, m, a[M], b[M], cnt, rt[M], lst;

inline int f(int x) { //应对强制在线
    return ((x - 1 + lst) % n) + 1;
}

inline void pushup(int k) {
    p[k].val = p[p[k].ls].val + p[p[k].rs].val;
}

/*需要提前构建出 x=0 的版本，上面所有计数为 0*/
void build(int &k, int l, int r) {
    if (!k) k = ++ cnt;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(p[k].ls, l, mid);
    build(p[k].rs, mid + 1, r);
}

void insert(int &k, int pr, int l, int r, int x) {
    if (!k) k = ++ cnt; //建新点
    if (l == r) {
        p[k].val = p[pr].val + 1; return;
    } //注意要从原点复制
    int mid = (l + r) >> 1;
    if (x <= mid) {
        p[k].rs = p[pr].rs;
        insert(p[k].ls, p[pr].ls, l, mid, x);
    } else {
        p[k].ls = p[pr].ls;
        insert(p[k].rs, p[pr].rs, mid + 1, r, x);
    } //分别考虑递归修改左右子树
    pushup(k);
}

int query(int k1, int k2, int l, int r, int x, int y) {
    if (x <= l && r <= y) return p[k1].val - p[k2].val;
    int mid = (l + r) >> 1, res = 0;
    if (x <= mid) res += query(p[k1].ls, p[k2].ls, l, mid, x, y);
    if (y > mid) res += query(p[k1].rs, p[k2].rs, mid + 1, r, x, y);
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x);
        t[x].x = i;
    }
    for (int i = 1; i <= n; ++ i) {
        int x; scanf("%d", &x);
        t[x].y = i;
    }
    sort(t + 1, t + n + 1);
    build(rt[0], 1, n);
    /*先将所有的点插入主席树*/
    for (int i = 1; i <= n; ++ i)
      insert(rt[t[i].x], rt[t[i].x - 1], 1, n, t[i].y);
    scanf("%d", &m);
    while (m --) {
        int l1, l2, r1, r2, a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        l1 = Min(f(a), f(b)), r1 = Max(f(a), f(b));
        l2 = Min(f(c), f(d)), r2 = Max(f(c), f(d));
        int res = query(rt[r1], rt[l1 - 1], 1, n, l2, r2);
        printf("%d\n", res); lst = res + 1;
    }
    return 0;
}
```

---

## 作者：FriedrichC (赞：1)

[洛谷题面](https://www.luogu.com.cn/problem/CF323C)

[原题链接](https://codeforces.com/problemset/problem/323/C)

## 引入

从思路上从头开始讲这道题。

这道题目的本质是一个区间计数问题，并且要满足计数对象在两个序列的给定询问区间之中都**存在**。

一说到区间问题，并且要维护存在性的计数，我们首先想到的当然是权值线段树，若某个元素存在，则在它的位置上添加一个贡献。

但是仔细想一想，我们要维护的存在性必须在两个序列中同时满足，也就是有两个限制，但是我们要在一个维度上同时维护两个限制显然是不那么容易的。

这时我们就可以想到主席树，因为这是主席树的一个常用技巧，即把两个限制中的一个放到**时间轴**上来维护（也就是主席树的若干版本），另一个限制则利用线段树本身在另一维度来维护。

上述过程也可以理解为，在保证一个限制成立的前提下，计算满足另个限制的答案。

对于这道题来说，我们就有了一个初步的思路，我们可以以 $s_1$ 中的数字出现的顺序作为时间轴建立主席树，来维护 $s_2$ 中数字的存在性。

那么计算答案的过程实际上分为两步：**计数**和**差分**，

即利用线段树计算 $[l_2,r_2]$ 中的贡献，然后在 $r_1$ 和 $l_1-1$ 的版本之间差分。

想一想，我们既然要实现差分，那么我们在主席树上应该维护什么信息呢？

## 实现

先注意到关键的一点，$s_1$ 和 $s_2$ 都是**排列**，也就是说任意一个序列中的元素都是**互异**的，那么对于一个给定的 $s_1$ 来说，$s_2$ 就是 $s_1$ 的**重排**。

假如我们从左往右顺序插入与 $s_1$ 的当前位置的元素有关的信息，

对于在 $[l_1,r_1]$ 中存在这个限制，天然就得到了满足，我们想要知道满足第二个限制的答案有多少，我们实际上想知道原先在 $[l_1,r_1]$ 这段区间中的元素**偏移**到了什么地方（下文简称偏移值），如果偏移值在 $[l_2,r_2]$ 的范围之中，这个元素就可以对这次询问的答案产生贡献。

也就是说，对于 $s_1$，我们想要对每个 $i\in [1,n]$，按 $i$ 从小到大的顺序在**权值**主席树上插入 $s_{1,i}$ 的偏移值。

那么这个偏差值应该怎么计算呢？

首先我们要明确一点，我们在计数步骤时是在**下标区间**上查询，也就是说我们的权值主席树的值域所维护的是 $1$ 到 $n$ **下标位置**，

那么我们显然要把元素的值与其下标建立映射关系，

具体的，我们可以用 $pos$ 数组记录某个元素在 $s_1$ 中的下标，用一个数组 $a$ 记录偏差值。

对于每一个 $s_{1,i}$，我们有 $pos[s1[i]]=i$

那么对于每一个 $s_{2,i}$，我们就有 $a[pos[s2[i]]]=i$。

这个两重映射的操作的含义就是，原先在 $pos$ 位置的 $s_1$ 中的元素，在 $s_2$ 中的偏差值，即原先 $s_{2,i}$ 所代表的元素在 $s_1$ 中的位置是 $pos[s2[i]]$，现在偏移到了 $i$ 这个位置。

（始终要记得，$s_1$ 和 $s_2$ 的元素集合是相同的，只是 $s_2$ 是 $s_1$ 的重排。）

一定要分清 $pos$ 数组和 $a$ 数组的本质区别，前者是把值映射为下标，后者则把**下标映射为新的下标**。

那么在主席树的插入时，我们就这样：

`for(int i=1;i<=n;++i)rt[i]=insert(rt[i-1],1,n,a[i]);`

对于每一个 $i$，插入它对应的 $a[i]$。（其实就等效于对于每一个 $s_1[i]$，插入它对应的偏差值，因为 $s_1[i]$ 已经被映射到下标上了。）

## 代码

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
int n,m,a[maxn],s1[maxn],s2[maxn],pos[maxn],rt[maxn],tot,ans;
inline int f(int x)
{
    return ((x-1+ans)%n)+1;
}
struct seg_tree{
    int lc,rc,sum;
    #define lc(x) tree[x].lc
    #define rc(x) tree[x].rc
    #define sum(x) tree[x].sum
    #define tr(x) tree[x]
}tree[maxn<<5];
int build(int l,int r)
{
    int p=++tot;
    if(l==r){sum(p)=a[l];return p;}
    int mid=(l+r)>>1;
    lc(p)=build(l,mid);
    rc(p)=build(mid+1,r);
    return p;
}
int insert(int now,int l,int r,int pos)
{
    int p=++tot;
    tr(p)=tr(now);
    sum(p)=sum(now)+1;
    if(l==r)return p;
    int mid=(l+r)>>1;
    if(pos<=mid)lc(p)=insert(lc(now),l,mid,pos);
    else rc(p)=insert(rc(now),mid+1,r,pos);
    return p;
}
int ask(int now,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)return sum(now);
    int mid=(l+r)>>1;
    int val=0;
    if(L<=mid)val+=ask(lc(now),l,mid,L,R);
    if(R>mid)val+=ask(rc(now),mid+1,r,L,R);
    return val;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i)cin>>s1[i],pos[s1[i]]=i;
    for(int i=1;i<=n;++i)cin>>s2[i],a[pos[s2[i]]]=i;
    //for (int i=1;i<=n;++i) printf("i=%d a=%d\n",i,a[i]);
    rt[0]=build(1,n);
    for(int i=1;i<=n;++i)rt[i]=insert(rt[i-1],1,n,a[i]);
    cin>>m;
    while(m--)
    {
        int l1,r1,l2,r2;
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        l1=min(f(a),f(b));
        r1=max(f(a),f(b));
        l2=min(f(c),f(d));
        r2=max(f(c),f(d));
        ans=ask(rt[r1],1,n,l2,r2)-ask(rt[l1-1],1,n,l2,r2);
        cout<<ans<<'\n';
        ans++;
    }
	return 0;
}

```




































---

## 作者：__stick (赞：1)

# 题意

给出两个长度为 $n$ 的排列，给出 $m$ 个询问，问在第一个排列 $[l1,r1]$ 区间内，第二个排列 $[l2,r2]$ 区间内同时出现的数有多少个。

# 思路

没看到强制在线的我： 对 $[l1,r1]$ 和 $[l2,r2]$ 两个区间分别跑莫队，用 bitset 存一下每个数是否出现，然后取与，复杂度 $O(\frac{nm}{w})$，应该，应该能过。

然后就开码，中间发现 bitset 开不下，被迫分组处理询问，后来死活过不了第二个大样例，才发现是强制在线。

愤怒地删空了代码，开始想正解。

可以发现询问有两维，一般的数据结构很难应付，可以降维的且在线的有树套树，主席树， KD-tree 等，经过一番思考，会发现主席树是最合适的。

首先我们对第二个序列开主席树，记录出现在第一个排列对应区间内数的个数，随后对于每个询问，我们先在主席树上进行提取出对应区间，然后查第一个区间对应区间内出现数的个数，然后就做完了。

# 代码

暂时的 rank 1，[rt](https://www.luogu.com.cn/paste/r85416ai)。



---

## 作者：registerGen (赞：1)

[更好的阅读体验](https://registergen.github.io/post/solution-cf323c/)

半年没敲主席树却一遍写对，祭之。

# Solution

同时出现的数的 **个数**？主席树！

转化是比较巧妙的。

可以记录 $b_i$ 在 $a$ 中出现的位置，用主席树维护这个数组。

那么询问就是求 $l_2\sim r_2$ 内有多少个数在 $[l_1,r_1]$ 之间。用第 $r_2$ 个根的答案减一下第 $l_2-1$ 个根的答案就行了。

~~强制在线真鬼畜。~~ 注意 $lstans$ 在询问后一定要加 $1$。。。

# Code

```cpp
#include<cstdio>
#include<algorithm>

const int N=1e6;

struct Node
{
	int v,ls,rs;
};

Node t[N<<5];
int a[N+10],b[N+10],rt[N+10],cnt;
int n,m,lstans;

#define SIZ 1000000

inline char gc()
{
#ifndef ONLINE_JUDGE
	return char(getchar());
#else
	static char buf[SIZ],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;
#endif
}

#undef SIZ

inline int read()
{
	int x=0,f=0;char c=gc();
	while(c<'0'||c>'9')f|=c=='-',c=gc();
	while(c>='0'&&c<='9')x=x*10+c-48,c=gc();
	return f?-x:x;
}

inline int f(int x)
{
	return (x-1+lstans)%n+1;
}

#define ls(x) (t[x].ls)
#define rs(x) (t[x].rs)

void modify(int& i,int j,int l,int r,int pos)
{
	i=++cnt;
	ls(i)=ls(j),rs(i)=rs(j),t[i].v=t[j].v+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)modify(ls(i),ls(j),l,mid,pos);
	else modify(rs(i),rs(j),mid+1,r,pos);
}

int query(int i,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)return t[i].v;
	int mid=(l+r)>>1;
	int res=0;
	if(ql<=mid)res+=query(ls(i),l,mid,ql,qr);
	if(qr>mid) res+=query(rs(i),mid+1,r,ql,qr);
	return res;
}

#undef ls
#undef rs

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		b[read()]=i;
	for(int i=1;i<=n;i++)
		a[i]=b[read()];
	for(int i=1;i<=n;i++)
		modify(rt[i],rt[i-1],1,n,a[i]);
	m=read();
	while(m--)
	{
		int l1=f(read()),r1=f(read()),l2=f(read()),r2=f(read());
		if(l1>r1)std::swap(l1,r1);
		if(l2>r2)std::swap(l2,r2);
		printf("%d\n",lstans=query(rt[r2],1,n,l1,r1)-query(rt[l2-1],1,n,l1,r1));
		lstans++;
	}
	return 0;
}
```

---

## 作者：wz20201136 (赞：1)

### 题意：

给定两个长度均为 $n$ 的排列。
$m$ 次询问。每次询问您要求出在第一个排列的 $[l1,r1]$ 和第二个排列的 $[l2,r2]$ 同时出现的数有多少个。

$1\le n\le10^6$，$1\le m\le 2\times 10^5$
 。强制在线。
 
### 思路：

首先思考，如果不强制在线怎么做。如过将第一个数列中数出现的位置映射到数组 $wz$ 中，答案就转化为$\sum_{n=l2}^{r2}[l1≤wz_{a_n}≤r1]$。
我们可以发现，这个东西可以转化为$\sum_{n=1}^{r2}[l1≤wz_{a_n}≤r1]-\sum_{n=1}^{l2-1}[l1≤wz_{a_n}≤r1]$，于是可以维护一个线段树，按第一个排列中的下标顺序加点，线段树内的 $l$，$r$ 分别对应着第二个排列的下标 $l$，$r$。

由于此题要求强制在线，而上述做法需要通过查询历史版本（即加完第 $l-1$ 个元素 和 加完第 $l-1$ 个元素的版本），用普通线段树需要离线下来，于是用可持久化线段树就可以辣。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,wz[1000005],a[1000005],x,cnt,hd[1000005],m,A,B,C,D,l1,l2,r1,r2,lst;
int tr[1000005<<5],ls[1000005<<5],rs[1000005<<5];//空间加倍！
int bd(int l,int r)//建树
{
	int rt=++cnt;
	if(l==r) return rt;
	int mid=(l+r)/2;
	ls[rt]=bd(l,mid);
	rs[rt]=bd(mid+1,r);
	return rt;
}
int f(int x)
{
	return (x-1+lst)%n+1;
}
int add(int u,int l,int r,int k)
{
	int rt=++cnt;
	tr[rt]=tr[u]+1,ls[rt]=ls[u],rs[rt]=rs[u];
	if(l==r) return rt;
	int mid=(l+r)/2;
	if(mid>=k) ls[rt]=add(ls[rt],l,mid,k);
	else rs[rt]=add(rs[rt],mid+1,r,k);
	return rt;
}
inline int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}
int qr(int u,int l,int r,int  L,int R)
{
	if(L<=l&&r<=R) return tr[u];
	if(L>r||l>R) return 0;
	int mid=(l+r)/2;
	return qr(ls[u],l,mid,L,R)+qr(rs[u],mid+1,r,L,R); 
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		x=read();
		wz[x]=i;
	}
	hd[0]=bd(1,n);
	for(int i=1;i<=n;i++) hd[i]=add(hd[i-1],1,n,wz[a[i]]);//一次加点
	cin>>m;
	while(m--)
	{
		A=read(),B=read(),C=read(),D=read();
		l1=min(f(A),f(B)),r1=max(f(A),f(B)),l2=min(f(C),f(D)),r2=max(f(C),f(D));
//		cout<<l1<<" "<<r1<<' '<<l2<<' '<<r2<<endl;
		lst=qr(hd[r1],1,n,l2,r2)-qr(hd[l1-1],1,n,l2,r2);//查询历史版本
		printf("%d\n",lst++);
	}
	return 0;
}
```

---

## 作者：Fracture_Dream (赞：0)

# 简述题意
给定两个长度为 $n$ 的排列 $a,b$，以及 $q$ 次询问，每次询问给定 $l_1,r_1,l_2,r_2$，求出有多少个数 $x$ 满足 $x\in{a_{i}},i\in[l_1,r_1]$ 且 $x \in b_i, i \in[l_2,r_2]$，强制在线。

# 思路
~~这种板子题评紫~~ 

注意到每个数仅出现一次，所以不妨令 $a_i$ 在 $b$ 排列中出现的位置为 $to_i$，每次查询 $[l_1,r_1]$ 中有多少个 $to_i$ 满足 $l_2 \le to_i \le r_2$ 即可。特定区间值域查询，一眼主席树。

# 代码
注意这道题有点卡空间，不要乱开。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1.2e6 + 5;
int n , m , a[MAXN] , b[MAXN] , lastans = -1;
namespace Segement{
	static int tot , rt[MAXN] , root;
	struct tree{
		int l , r , sum , ls , rs;
	}tree[MAXN * 20];
	int build(int p , int l , int r) {
		p = ++ tot;
		tree[p].l = l , tree[p].r = r;
		if (l == r) return p;
		int mid = l + r >> 1;
		tree[p].ls = build(p , l , mid) , tree[p].rs = build(p , mid + 1 , r);
		return p;
	}
	int newnode(int p) {
		tree[++ tot] = tree[p];
		return tot;
	}
	int update(int p , int x) {
		int now = newnode(p);
		tree[now].sum ++;
		if (tree[now].l == tree[now].r) return now;
		int mid = tree[now].l + tree[p].r >> 1;
		if (x <= mid) tree[now].ls = update(tree[now].ls , x);
		else tree[now].rs = update(tree[now].rs , x);
		return now;
	}
	int query(int p , int p2 , int l , int r) {
		if (tree[p].l >= l && tree[p].r <= r) return tree[p2].sum - tree[p].sum;
		int mid = tree[p].l + tree[p].r >> 1 , tmp = 0;
		if (l <= mid) tmp += query(tree[p].ls , tree[p2].ls , l , r);
		if (r > mid) tmp += query(tree[p].rs , tree[p2].rs , l , r);
		return tmp;
	}
}
using namespace Segement;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) cin >> a[i];
	for (int i = 1 , x ; i <= n ; i ++) cin >> x , b[x] = i;
	rt[0] = build(1 , 1 , n);
	for (int i = 1 ; i <= n ; i ++) rt[i] = update(rt[i - 1] , b[a[i]]);
	cin >> m;
	while(m --) {
		int a , b , c , d;
		cin >> a >> b >> c >> d;
		int l1 = (a + lastans) % n + 1 , r1 = (b + lastans) % n + 1;
		int l2 = (c + lastans) % n + 1 , r2 = (d + lastans) % n + 1;
		if (l1 > r1) swap(l1 , r1);
		if (l2 > r2) swap(l2 , r2);
		cout << (lastans = query(rt[l1 - 1] , rt[r1] , l2 , r2)) << '\n';
	}
	return 0;
}
```

---

