# Rmq Problem / mex

## 题目描述

有一个长度为 $n$ 的数组 $\{a_1,a_2,\ldots,a_n\}$。

$m$ 次询问，每次询问一个区间内最小没有出现过的自然数。

## 说明/提示

对于 $30\%$ 的数据：$1\leq n,m\leq 1000$。  
对于 $100\%$ 的数据：$1\leq n,m\leq 2\times {10}^5$，$1\leq l\leq r\leq n$，$0\leq a_i\leq 2\times 10^5$。

## 样例 #1

### 输入

```
5 5
2 1 0 2 1
3 3
2 3
2 4
1 2
3 5```

### 输出

```
1
2
3
0
3```

# 题解

## 作者：RabbitHu (赞：139)

您们这个莫队……每次移动左右端点时找新的答案那部分……一会$O(1)$一会$O(n)$……复杂度我不会证啊……

于是……

## 一个不用莫队的题解！

从左往右扫一遍，在权值线段树（要可持久化一下）上修改当前权值对应的“最后一次出现的位置”为当前位置。

查询区间$[l, r]$时，答案就是第$r$棵线段树上，第一个“最后一次出现的位置”小于$l$的权值。

其实不可持久化也是可以的——只要把询问离线一下就好了。

（可是我觉得在线算法更可爱 =v=）

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#define space putchar(' ')
#define enter putchar('\n')
typedef long long ll;
using namespace std;
template <class T>
void read(T &x){
    char c;
    bool op = 0;
    while(c = getchar(), c < '0' || c > '9')
	if(c == '-') op = 1;
    x = c - '0';
    while(c = getchar(), c >= '0' && c <= '9')
	x = x * 10 + c - '0';
    if(op) x = -x;
}
template <class T>
void write(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

const int N = 400005, M = 5000005;
int n, m, a[N], lst[N], idx;
int tot, root[N], ls[M], rs[M], data[M];

void change(int old, int &k, int l, int r, int p, int x){
    k = ++tot;
    ls[k] = ls[old], rs[k] = rs[old];
    if(l == r) return (void)(data[k] = x);
    int mid = (l + r) >> 1;
    if(p <= mid) change(ls[old], ls[k], l, mid, p, x);
    else change(rs[old], rs[k], mid + 1, r, p, x);
    data[k] = min(data[ls[k]], data[rs[k]]);
}
int query(int k, int l, int r, int x){
    if(!k || l == r) return lst[l];
    int mid = (l + r) >> 1;
    if(data[ls[k]] >= x) return query(rs[k], mid + 1, r, x);
    return query(ls[k], l, mid, x);
}

int main(){

    read(n), read(m);
    lst[++idx] = 0;
    for(int i = 1; i <= n; i++)
	read(a[i]), lst[++idx] = a[i], lst[++idx] = a[i] + 1;
    sort(lst + 1, lst + idx + 1);
    idx = unique(lst + 1, lst + idx + 1) - lst - 1;
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(lst + 1, lst + idx + 1, a[i]) - lst;
        change(root[i - 1], root[i], 1, idx, a[i], i);
    }
    while(m--){
        int l, r;
        read(l), read(r);
        write(query(root[r], 1, idx, l)), enter;
    }

    return 0;
}
```


---

## 作者：龙神哈迪斯 (赞：37)

###先吐嘈一下

楼下大佬的方法貌似比较难啊，可惜我太cai了看不懂，就只好用了个分块，算是比较~~易懂的暴力~~吧
###题解

想必同学们都是刷莫队的时候不小心刷到这题的
主要考虑怎么**修改和查询**
类似值域线段树的思想，将值域$O(0,K)$ 进行分块，查询时先遍历所有的块，如果某个块非空那么查询该块，当查询到一个数字为空时，即可break输出答案，复杂度为O($\sqrt k$+$\sqrt k$)，修改时要注意判断块的信息

1.增加一个数时，如果该数为空，则要将该数所在块的元素个数和该数的个数都+1，否则只将该数的个数+1

2.删除一个数时，如果该数删除后为空，则要将该数所在块的元素个数和该数的个数都-1，否则只将该数的个数-1

细节：
考虑到最坏情况下的区间是$(0,1,2,3,......N-1)$ 因此最大答案也是N，所以A_i>=1e9是用来搞笑的，将所有大于等于N+1的数修改为N+1就可以了
###代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int _=200005;
const int K=448;
inline int read()
{
    char ch='!';int z=1,num=0;
    while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
    if(ch=='-')z=-1,ch=getchar();
    while(ch<='9'&&ch>='0')num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
    return z*num;
}
int n,m,kuai[_],a[_];
struct hand{int l,r,id;}ask[_];
bool cmp(hand A,hand B)
{
    if(kuai[A.l]==kuai[B.l])return A.r<B.r;
    return kuai[A.l]<kuai[B.l];
}
int num[500],cnt[_],ans[_];
void add(int x)
{
    if(!cnt[x])num[x/K]++;
    cnt[x]++;
}
void del(int x)
{
    if(cnt[x]==1)num[x/K]--;
    cnt[x]--;
}
void Query(int x)
{
    for(int i=1;i<=K;i++)
    {
        if(num[i-1]!=K)
        {
            for(int j=(i-1)*K;j<i*K;j++)
            {
                if(!cnt[j])
                {
                    ans[ask[x].id]=j;return;
                }
            }
        }
    }
}
int main()
{
    n=read();m=read();
    int len=sqrt(n);
    for(int i=1;i<=n;i++)
    {
        a[i]=min(read(),n+1);
        kuai[i]=(i-1)/len+1;
    }
    for(int i=1;i<=m;i++)
        ask[i].l=read(),ask[i].r=read(),ask[i].id=i;
    sort(ask+1,ask+1+m,cmp);
    int l=ask[1].l,r=ask[1].r;
    for(int i=l;i<=r;i++)
        add(a[i]);
    Query(1);
    for(int i=2;i<=m;i++)
    {
        while(l<ask[i].l)del(a[l++]);
        while(l>ask[i].l)add(a[--l]);
        while(r<ask[i].r)add(a[++r]);
        while(r>ask[i].r)del(a[r--]);
        Query(i);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}

```


---

## 作者：Great_Influence (赞：29)

我觉得在线算法不可爱，所以写了离线算法。

假如我们要求的区间左端点在1，则我们可以转换问题:

对于每个数字，给它附上它第一次出现的位置的权值。

那么，答案就是:

求最大的数$t$，使得$\max\limits_{i=0}^{t-1} p[i]\le r$

$p[i]$就是$i$这个数的权值。

这个可以用二分简单求出。

然后就是左端点不固定的情况。加入我们要将做短点右移一位，如果我们求出了这个位置上的数下一次出现的位置，我们可以将这个数第一次出现的位置改到下一次出现的位置。

那么，我们只需要预处理每个数初次出现位置和下一次出现位置，然后支持单点修改和区间查询最大值就可以了。我们选择了线段树。

如果每次二分后直接在线段树上查询，则该算法是$O(n+qlog^2n)$的。然而可以直接在线段树上二分，时间复杂度变为$O(n+qlogn)$。(所以也可以当作线段树二分的模板题)

代码:

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register uint32 i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register uint32 i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
#define pb push_back
using uint32=unsigned int;
using uint64=unsigned long long;
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}

template<typename T>inline void write(T x,char ed='\n')
{
    static int sta[111],tp;
    if(!x){putchar('0'),putchar(ed);return;}
    for(tp=0;x;x/=10)sta[++tp]=x%10;
    for(;tp;putchar(sta[tp--]^48));
    putchar(ed);
}

void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}
const uint32 MAXN=2e5+7;

static uint32 n,m,w[MAXN];

static uint32 fp[MAXN],nxt[MAXN];

namespace Segment_Tree
{
	static uint32 p[MAXN<<2];

	void modif(uint32 h,uint32 l,uint32 r,uint32 x,uint32 z)
	{
		if(l==r)
		{
			p[h]=z;
			return;
		}
		static uint32 mid;mid=(l+r)>>1;
		x<=mid?modif(h<<1,l,mid,x,z):modif(h<<1|1,mid+1,r,x,z);
		p[h]=max(p[h<<1],p[h<<1|1]);
	}

	inline uint32 query(int x,int y)
	{
		static uint32 h,l,r,mid,mx;mx=0;h=l=1;r=n;
		while(l<r)
		{
			mid=(l+r)>>1;
			if(y-x+1>=mid && max(p[h<<1],mx)<=y)
				Chkmax(mx,p[h<<1]),h=h<<1|1,l=mid+1;
			else h<<=1,r=mid;
		}
		return l-1;
	}
}
using namespace Segment_Tree;

static struct quer
{
	int l,r,id;
	friend bool operator<(quer a,quer b){return a.l<b.l;}
}q[MAXN];

inline void init()
{
	read(n);read(m);
	memset(p,0x3f,sizeof p);
	Rep(i,1,n)
	{
		read(w[i]);++w[i];
		if(w[i]<=n)
		{
			if(fp[w[i]])nxt[fp[w[i]]]=i;
			else modif(1,1,n,w[i],i);
			fp[w[i]]=i;
		}
	}
	Rep(i,1,m)read(q[i].l),read(q[i].r),q[i].id=i;
}

static uint32 ans[MAXN];

inline void solve()
{
	sort(q+1,q+m+1);
	static uint32 ps=0;
	w[0]=1e9;
	Rep(i,1,m)
	{
		for(;ps<q[i].l;++ps)if(w[ps]<=n)
			modif(1,1,n,w[ps],nxt[ps]?nxt[ps]:p[0]);
		ans[q[i].id]=query(q[i].l,q[i].r);
	}
	Rep(i,1,m)printf("%u\n",ans[i]);
}

int main(void)
{
    file();
    init();
    solve();
    return 0;
}
```

---

## 作者：火车司机 (赞：23)

## 简要分析

考虑莫队

可以发现删除操作十分简单，但是添加操作难以在 $O(1)$ 复杂度做到

考虑只减不加的回滚莫队

先遍历整一个序列，算出整个序列的mex

与只加不减的回滚莫队相似，将询问的左端点所在的块从小到大，右端点**从大到小**排序

这样的话，对于每一个不同的块，右指针会从整个序列的末尾不断向左删除，同时左指针不断地回滚到块的左端点

处理完一个块的询问之后，左指针必然会回滚到块的左端点

这时，类似只加不减的回滚莫队，先暴力地把右指针遍历到整个序列的最右端，然后左指针向右删除到下一个块的左端点

复杂度是 $O(n \sqrt n)$，不明白的读者可以用上述过程手玩一下样例

## 完整代码

随手卡了个常，可能比较丑陋

```cpp
#include <bits/stdc++.h>
#define ri register int
#define getchar() (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++
#define N 200005
#define B 448
using namespace std;
char ou[1 << 22], buf[1 << 22], *p1 = buf, *p2 = buf;
int n, m, s, a[N], bel[N], cnt[N], tmp[N], ans[N], L[N / B + 5], R[N / B + 5], p3 = -1;
struct query
{
	int l, r, id;
	inline bool operator<(const query &x) const
	{
		return bel[l] ^ bel[x.l] ? bel[l] < bel[x.l] : r > x.r;
	}
} q[N];
template <typename T>
inline void read(T &x)
{
	register T c = getchar();
	for (; c < 48 || 57 < c;)
		c = getchar();
	for (; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c ^ 48);
}
template <typename T>
inline void print(const T x)
{
	if (x > 9)
		print(x / 10);
	ou[++p3] = x % 10 | 48;
	if (p3 > (1 << 21))
		fwrite(ou, 1, p3 + 1, stdout), p3 = -1;
}
inline int mnn(const int a, const int b)
{
	return a < b ? a : b;
}
signed main()
{
	read(n), read(m);
	for (ri i = 1; i <= n; ++i)
	{
		read(a[i]), bel[i] = (i - 1) / B + 1;
		if (a[i] <= n + 1)
			++cnt[a[i]];
	}
	while (cnt[s])
		++s;
	for (ri i = 1; i <= m; ++i)
		read(q[i].l), read(q[i].r), q[i].id = i;
	for (ri i = 1; i < bel[n]; ++i)
		L[i] = R[i - 1] + 1, R[i] = i * B;
	L[bel[n]] = R[bel[n] - 1] + 1, R[bel[n]] = n, sort(q + 1, q + 1 + m);
	for (ri k = 1, i = 1, l, r, p; k <= bel[n]; ++k)
	{
		l = L[k], r = n, p = s;
		for (ri t; bel[q[i].l] == k; ++i)
		{
			if (bel[q[i].r] == k)
			{
				ri t = 0;
				for (ri j = q[i].l; j <= q[i].r; ++j)
					if (a[j] <= n + 1)
						++tmp[a[j]];
				while (tmp[t])
					++t;
				ans[q[i].id] = t;
				for (ri j = q[i].l; j <= q[i].r; ++j)
					if (a[j] <= n + 1)
						--tmp[a[j]];
				continue;
			}
			for (; r > q[i].r; --r)
				if (a[r] <= n + 1 && !--cnt[a[r]])
					p = mnn(p, a[r]);
			t = p;
			for (; l < q[i].l; ++l)
				if (a[l] <= n + 1 && !--cnt[a[l]])
					t = mnn(t, a[l]);
			ans[q[i].id] = t;
			while (l > L[k])
			{
				--l;
				if (a[l] <= n + 1)
					++cnt[a[l]];
			}
		}
		while (r < n)
		{
			++r;
			if (a[r] <= n + 1)
				++cnt[a[r]];
		}
		for (; l < L[k + 1]; ++l)
			if (a[l] <= n + 1 && !--cnt[a[l]])
				s = mnn(s, a[l]);
	}
	for (ri i = 1; i <= m; ++i)
		print(ans[i]), ou[++p3] = '\n';
	fwrite(ou, 1, p3 + 1, stdout);
	return 0;
}
```


---

## 作者：tth37 (赞：22)

考虑建权值线段树，维护每一个权值在原数组中最后一次出现的下标。对于查询操作 $[l,r]$ ，可以取出右端点所对应的主席树，并在树上二分查找下标小于 $l$ 的最小权值即为答案。

权值的值域很大，需要进行离散化。需要注意的是，如果只对 $\lbrace a_n \rbrace$ 数组进行离散化，而输出的答案（未出现的自然数）不一定是 $\lbrace a_n \rbrace$ 数组中的值。然而不难发现，未出现的最小自然数只有可能是 $0$ 或是 $a_i+1$，因此只需对元素 $0$ 、 $a_i$ 、 $a_i+1$ 进行离散化即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define id(x) (lower_bound(b + 1, b + L + 1, x) - b)
#define rid(x) (b[x])
using namespace std;
const int MAXN = 200005 * 2;

struct Node {
	int l, r, val;
}node[MAXN * 22];
int cnt, head[MAXN];

int N, M, L;
int a[MAXN];
int b[MAXN];

inline void build(Node& u, int l, int r) {
	u.val = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(node[u.l = ++cnt], l, mid);
	build(node[u.r = ++cnt], mid + 1, r);
}

inline void insert(Node& u, Node c, int l, int r, int p, int val) {
	if (l == r) {
		u.val = val;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) {
		insert(node[u.l = ++cnt], node[c.l], l, mid, p, val);
		u.r = c.r;
	}
	else {
		insert(node[u.r = ++cnt], node[c.r], mid + 1, r, p, val);
		u.l = c.l;
	}
	u.val = min(node[u.l].val, node[u.r].val);
}

inline int query(Node u, int l, int r, int val) {
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (node[u.l].val < val) return query(node[u.l], l, mid, val);
	return query(node[u.r], mid + 1, r, val);
}

int main() {
	scanf("%d%d", &N, &M);
	for (register int i = 1; i <= N; ++i)
		scanf("%d", &a[i]), b[++L] = a[i], b[++L] = a[i] + 1;
	b[++L] = 0;
	sort(b + 1, b + L + 1);
	L = unique(b + 1, b + L + 1) - b - 1;
	build(node[head[0] = ++cnt], 1, L);
	for (register int i = 1; i <= N; ++i) {
		insert(node[head[i] = ++cnt], node[head[i - 1]], 1, L, id(a[i]), i);
	}
	for (register int i = 1; i <= M; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", rid(query(node[head[r]], 1, L, l)));
	}
	return 0;
}
```

---

## 作者：jzwjx (赞：19)

## 题意简述

给定 $n$ 个数，$m$ 次询问，求区间最小未出现的自然数。

## 前置知识

### 莫队

一种分块后离线处理询问的算法，此处就不多说了，还不会的请自己查询。

### bitset

一种很神奇的数据结构，可参考[扶苏的 bitset 浅谈 - 洛谷专栏](https://www.luogu.com.cn/article/osrhh40p)。

## 分析

由于没有修改，所以我们可以想到用莫队，维护区间内数的个数，那么只需要考虑如何快速查找从小到大的第一个没有出现的数字就好。

此时我们发现 `bitset` 有一个非常神器的函数——`_Find_first()`,它可以直接返回 `bitset` 里第一个 $1$ 的下标，所以我们设 `bitset` 中 $1$ 表示这个数字没有出现过，$0$ 表示没有出现过，每回修改时维护当前数字 $a_i$ 的出现次数 $cnt_{a_i}$，如果从 $0$ 加为 $1$ 就在 `bitset` 里把这一位赋为 $0$，如果从 $1$ 减为 $0$ 就在 `bitset` 里把这一位赋为 $1$，最后直接查询就做完了。

但如果仅是上述做法不开 O2 是会 TLE 一个点，所以我们此处引入莫队的一种优化——奇偶性排序。

我们可以发现，每次变到下一个块时，$r$ 最劣会从最右边跑回当前块，所以我们可以在排序时根据所在块的奇偶性排序，若 $i \equiv 1 \pmod {2}$，则让 $r$ 从大到小排序，否则从小到大排序。这样就可以在不开 O2 的情况下 A 掉此题了。

复杂度是 $O(n\sqrt{n}+\dfrac{nq}{w})$，理论上是超了的，但由于每次查询到的值和区间移动范围无法同时达到最大值，所以复杂度变为 $O($能过$)$。

## 代码

### 莫队

```cpp
for(int i=1;i<=q;i++){//莫队
        while(st[i].l<L){
            L--;
            add(a[L],1);
        }
        while(st[i].l>L){
            add(a[L],-1);
            L++;
        }
        while(st[i].r<R){
            add(a[R],-1);
            R--;
        }
        while(st[i].r>R){
            R++;
            add(a[R],1);
        }
        anss[st[i].id]=bit._Find_first();
    }
```

### 添加或删点

```cpp
void add(int l,int x){
    if(x==1){
        if(cnt[l]==0) bit.set(l,0);//以前l没出现过
        cnt[l]++;
    }
    else {
        cnt[l]--;
        if(cnt[l]==0) bit.set(l,1);//当前区间内没有l了
    }
}
```

### AC代码

[这里](https://www.luogu.com.cn/paste/wpiot7xv)。

---

## 作者：lao_wang (赞：14)

## 前言

好久没用整体二分发电了。

## 正文

注意到实际上 mex 是可以二分的。

对于全局 mex 我们可以二分 mex 是哪个值。

check 为是否区间内比 $x$（假设当前二分答案为 $x$）小的个数是否等于 $x+1$ 是则记录答案为 $x+1$ 并 $l=mid+1$；不是则 $r=mid-1$。

~~这是显然正确的吧。~~

那么对于区间查询 mex，只需要更改 check，改为满足该条件下的 dp 的 $f_x$ 数值是否等于 $x+1$。

条件：

1. $a_i < a_j$
2. $L \leqslant i \leqslant R$
3. $L \leqslant j \leqslant R$
4. $a_j \leqslant x$

其中 $L$、$R$ 为查询区间。

注意到可以使用类似于扫描线的方法，询问和插入均按照右端点或下标从小到大排序，之后用整体二分二分 $x$ 每个能做贡献的数值只保留与其相同数值中下表最大的那一个放进树状数组，之后查询是否满足要求，就完了。

可能会有一些细节但不多。

## 代码

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
#define N 1000005
using namespace std ;
int n , q , tr[N] , last[N] , ans[N] , cnt=0 , num=0 ;
void change(int x,int k) {
	while(x<=n+1) {
		tr[x] += k ;
		x += lowbit(x) ;
	}
}
int ask(int x) {
	int ans=0 ;
	while(x) {
		ans += tr[x] ;
		x -= lowbit(x) ;
	}
	return ans ;
}
struct node {
	int x , i , l , r , opt , k , tm ;
	bool operator <(const node &a)const {
		return this->tm>a.tm ;
	}
} a[N],q1[N],q2[N];
void solve(int l,int r,int L,int R) {
	if(l>r||L>R) return ;
	int mid=(l+r)>>1 , tot1=0 , tot2=0 ;
	for(int i=L; i<=R; i++) {
		if(a[i].opt==1) {
			if(a[i].x<=mid){
				if(last[a[i].x]) change(last[a[i].x],-1) ;
				last[a[i].x] = a[i].i ;
				change(a[i].i,1) ;
				q1[++tot1] = a[i] ;
			} else q2[++tot2] = a[i] ;
		} else {
			int x=ask(a[i].r)-ask(a[i].l-1) ;
			if(a[i].k+x<=mid) q1[++tot1] = a[i] ;
			else if(x+a[i].k==mid+1) {
				ans[a[i].i] = mid+1 ;
				a[i].k += x ;
				q2[++tot2] = a[i] ;
			} else exit(114514) ;
		}
	}
	for(int i=1; i<=tot1; i++) {
		a[i+L-1] = q1[i] ;
		if(q1[i].opt==1) {
			if(last[q1[i].x]) {
				change(last[q1[i].x],-1) ;
				last[q1[i].x] = 0 ;
			}
		}
	}
	for(int i=1; i<=tot2; i++) a[i+L-1+tot1] = q2[i] ;
	if(l!=r) solve(l,mid,L,L+tot1-1) ;
	solve(mid+1,r,L+tot1,R) ;
}
int read() {
	int x=0 ;
	char a=getchar() ;
	while(!(a>='0'&&a<='9')) a = getchar() ;
	while(a>='0'&&a<='9') {
		x *= 10 ;
		x += a-'0' ;
		a = getchar() ;
	}
	return x ;
}
bool cmp(node a,node b) {
	return a.r==b.r?a.tm<b.tm:a.r<b.r ;
}
int t[N] ;
signed main(){
	n = read() , q = read() ;
	for(int i=1; i<=n; i++) {
		int temp=read() ;
		cnt++ ;
		a[cnt].opt = 1 , a[cnt].k = 1 , a[cnt].x = temp , a[cnt].r = a[cnt].i = i , a[cnt].tm = cnt ;
	}
	for(int i=1; i<=q; i++) {
		int x , y ;
		x = read() , y = read() ;
		cnt++ ;
		a[cnt].i = ++num , a[cnt].opt = 2 , a[cnt].l = x , a[cnt].r = y , a[cnt].tm=cnt ;
	}
	sort(a+1,a+1+cnt,cmp) ;
	solve(0,n+1,1,cnt) ;
	for(int i=1; i<=num; i++) printf("%d\n",ans[i]) ;
	return 0 ;
}
```

## 废话

本人模拟赛做该题的待修版（单点），把 check 推成了等于 $x$ 就行，实际上这道题的样例已经否定了这种写法，希望大家不要像我一样犯这种~~高级~~错误（实际上还有 multiset 用 end 查最大值这种发电操作）。

---

## 作者：灵乌路空 (赞：13)

## 简述

[原题面](https://www.luogu.org/problem/P4137)

>给定一长度为 $n$ 的序列 $a$ ,    
>给定 $m$ 次询问 ,  每次询问 给定区间，询问 "**区间内最小的 未出现的 自然数**"  
>$1\le n,m,a_i\le 2\times 10^5$。

## 分析 

线段树, 离线操作。

莫队太不优美 , 有一种 $O((n + m)\log n)$ 的优美做法   

- 对于区间 $[l, l] \sim [l, n]$ 中的答案 ,     
  左端点固定 ,  随着右端点 右移 , 会有更多的数加入到 区间中    
  显然 , 区间 $[l, l] \sim [l, n]$ 中 答案单调不递减     
	
- 假设已知 区间 $[l, r]$ 内的答案, 欲推得 $[l + 1, r]$ 区间内的答案 :   
  - 若 区间 $[l + 1, r]$ 内不存在 数 $a[l]$ ,  且原答案 $> a[l]$   
    则 区间 $[l + 1, r]$ 内答案可更新为 $a[l]$   
    
  - 由上可得  ,    
     将 左端点右移 $1$ 后, 会被影响的区间中 必然不存在 数 $a[l]$    
     显然, 被影响的区间为 : $[l + 1, l + 1] \sim [l + 1, l + next[l] - 1]$   
	  - 其中, $next[l]$ 代表 $a[l]$ 在$[l + 1, n]$ 中第一个 出现的位置    
    
  - 若已知 区间 $[l, l] \sim [l, n]$ 中的答案,    
    且预处理出 上述的 $next$ 数组,   
	即可 通过取最小值的方式 , 来获得 区间  $[l + 1, l + 1] \sim [l + 1, l + next[l] - 1]$ 中的答案    

- 若按照上述方法 , 通过左端点右移, 来求得 不同区间答案的方法   
  需要满足 询问左端点单调不降 .   
  则可 离线处理询问 ,  记录并排序后 , 再回答询问   
 
## 实现
 
由上,需要一种支持查询 动态区间最小值, 区间修改的数据结构   
可使用 线段树进行维护。   
  
 - 按照上述要求 ,  则线段树的叶节点 存储的答案 ,  表示以对应点作为右端点的答案.    
    即: [当前左端点 $\sim$ 叶节点维护点] 的答案 ,   
  
  - 对于全局左端点 左移, 获得 区间  $[l + 1, l + 1] \sim [l + 1, l + next[l] - 1]$ 中的答案    
    有两种处理方法 :   
	1.由于 区间 $[l + 1, l] \sim [l + 1, n]$ 中 答案单调不递减    
	  则可以进行线段树二分 , 求得第一个答案 $> a[l]$ 的位置   
	  并将之后的位置进行修改    
      
	2.个人的 $sb$ 做法:   
	  对每一个区间, 维护其中 最大的答案 及 最小的答案   
	  1. 若更新值 $<$ 最小答案时, 将整个区间进行更新    
	  2. 若不满足$1$ , 若更新值 $>$ 最大值 , 则整个区间都不需要更新 , 直接 `return;`   
	  3. 若不满足 $1,2$  , 继续向下深入    
   
  - 每次查询时 , 先将当前全局 左端点右移至查询左端点 ,   
    再直接查询 对应右端点储存的答案即可   
	 
单次左端点右移 与查询 复杂度都为 $O(\log n)$, 则总复杂度为 $O((n + m)\log n)$    


---


```cpp
#include <cstdio>
#include <algorithm>
#include <map>
#include <ctype.h>
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define ls (now << 1)
#define rs (now << 1 | 1)
const int MARX = 2e5 + 10;
//=============================================================
struct node
{
	int L, R;
	int ans;//记录区间答案(若区间答案不一致则为-1 
	int minn, maxx;//记录区间内 最小 / 最大 的答案 
}tree[MARX << 2];
struct Query
{
	int l, r, data;//询问的左右端点, 及询问编号 
}q[MARX];
int N, M, original[MARX], next[MARX], ans[MARX];
std :: map <int, int> last;//预处理使用, 记录某一个数 上一次出现的位置 
std:: map <int,bool> vis; //预处理使用 , 记录一个数是否出现过 
//=============================================================
inline int read()
{
    int s = 1, w = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') s = -1;
    for(; isdigit(ch); ch = getchar()) w = (w << 1) + (w << 3) + (ch ^ '0');
    return s * w;
}
bool cmp(Query fir, Query sec)//对查询排序的 比较函数 
{
	if(fir.l == sec.l) return fir.r < sec.r;
	return fir.l < sec.l;
}
void Pushdown(int now)//下传 懒标记
{
	tree[ls].ans = tree[rs].ans = tree[now].ans;
	tree[ls].minn = tree[rs].minn = tree[now].ans;
	tree[ls].maxx = tree[rs].maxx = tree[now].ans;
	tree[now].ans = -1;
}
void Pushup(int now)//更新 now点的信息 
{
	tree[now].minn = min(tree[ls].minn, tree[rs].minn);
	tree[now].maxx = max(tree[ls].maxx, tree[rs].maxx);
	tree[now].ans = tree[ls].ans == tree[rs].ans ? tree[ls].ans : -1;//更新懒标记 
}
void Build(int now, int L, int R)//建树 
{
	tree[now].L = L, tree[now].R = R, tree[now].ans = -1;//赋初值 
	if(L == R) //递归到叶节点 
	{
	  tree[now].ans = tree[now].minn = tree[now].maxx = ans[L]; 
	  return ;
	}
	int mid = (L + R) >> 1;
	Build(ls, L, mid), Build(rs, mid + 1, R);
	Pushup(now);
}
void Change(int now, int L, int R, int key)//将 [L,R]内 答案 > key的区间 更新为key 
{
	if(L <= tree[now].L && tree[now].R <= R)//区间被完全包括 
	  if(tree[now].minn >= key)//最小值大于key, 则区间需要全部被更新 
	  {
	  	tree[now].ans = tree[now].minn = tree[now].maxx = key; 
		return ;
	  }
	  else if(tree[now].maxx <= key) return ;//最大值 小于等于key, 则区间不需要被更新 
	 
	if(tree[now].ans != -1) Pushdown(now);//下传懒标记 
	int mid = (tree[now].L + tree[now].R) >> 1;
	if(L <= mid) Change(ls, L, R, key);//递归 修改左右区间 
	if(R > mid) Change(rs, L, R, key);
	Pushup(now);//更新 now点的信息 
}
int Query(int now, int pos)//单点查询 pos的答案 
{
	if(pos == tree[now].L && tree[now].R == pos) return tree[now].ans; //寻找到答案 
	
	if(tree[now].ans != -1) Pushdown(now);//下传懒标记 
	int mid = (tree[now].L + tree[now].R) >> 1; 
	if(pos <= mid) return Query(ls, pos);//查询 对应位置 
	else return Query(rs, pos);
}
void Prepare()//预处理 
{
	N = read(), M = read();
	for (int i = 1, minn = 0; i <= N; i ++) //读入原始数列, 预处理next值 
	{
	  original[i] = read(), next[i] = N + 1;  
	  next[last[original[i]]] = i, last[original[i]] = i; //更新 next, last值 
	  vis[original[i]] = 1; //更新 此数的出现情况 
	  while(vis[minn]) minn ++; //计算 [1,i] 的答案 
	  ans[i] = minn;
	}
	Build(1, 1, N); 
	for(int i = 1; i <= M; i ++) q[i].l = read(), q[i].r = read(), q[i].data = i;
	std :: sort(q + 1, q + M + 1, cmp);//将查询按照左端点 升序排序 
}
//=============================================================
signed main()
{
	Prepare();
	for(int i = 1, nowl = 1; i <= M; i ++)//枚举 询问 
	{
	  //将左端点右移至 当前询问的左端点 
	  for(;q[i].l > nowl; nowl ++) Change(1, nowl , next[nowl] - 1, original[nowl]);
	  ans[q[i].data] = Query(1, q[i].r);//回答询问 
	}
	
	for(int i = 1; i <= M; i ++) printf("%d\n", ans[i]);
}
```

---

## 作者：81179332_ (赞：13)

可持久化权值线段树。

对于读入的每个数，我们记录这个数最后一次出现的位置（要可持久化）。

查询的时候，我们在第 $r$ 棵线段树上二分，找到最小的、最后一次出现位置在 $l$ 左侧的数，这个数就是所求的答案。

注意代码中`minn`维护的是这个区间内最后一次出现位置的最小值，而不是第一次出现位置。

其他题解将值域设为 $10^9$或者进行了离散化，这样是没有必要的。对于序列中的任意一个数（读入数据加一后），如果它比 $n$ 要大，它一定对答案无贡献，所以我们直接忽略掉它即可。

另外，由于我在读入的时候将序列中的数加一，当查询到的数字应该是 $n+1$ 时（即询问区间覆盖了 $1$ 到 $n$ 所有数字时）,如果将值域区间定为 $1$ 到 $n$ 会出错，应该定为 $1$ 到 $n+1$。

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define pprint(x) ::print(x),putchar(' ')
#define fprint(x) ::print(x),putchar('\n')
using namespace std;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(long long x)
{
	if(x < 0)
		x = -x,putchar('-');
	if(x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 200010;

struct tree
{
	int ls,rs;
	int minn;
}t[N << 5];
int cnt,root[N];
void update(int &now,int pre,int l,int r,int pos,int val)
{
	now = ++cnt;
	t[now] = t[pre];
	if(l == r)
	{
		t[now].minn = val;
		return;
	}
	int mid = l + r >> 1;
	if(pos <= mid)
		update(t[now].ls,t[pre].ls,l,mid,pos,val);
	else
		update(t[now].rs,t[pre].rs,mid + 1,r,pos,val);
	t[now].minn = min(t[t[now].ls].minn,t[t[now].rs].minn);
}
int query(int now,int l,int r,int val)
{
	if(l == r)
		return l;
	int mid = l + r >> 1;
	if(t[t[now].ls].minn < val)
		return query(t[now].ls,l,mid,val);
	else
		return query(t[now].rs,mid + 1,r,val);
}

int n,m;

int main()
{
	n = read(),m = read();
 	for(int i = 1;i <= n;i++)
	{
		int a = read() + 1;
		if(a > n)
		{
			root[i] = root[i - 1];
			continue;
		}
		update(root[i],root[i - 1],1,n + 1,a,i);
	}
	while(m--)
	{
		int l = read(),r = read();
		fprint(query(root[r],1,n + 1,l) - 1);
	}
}
```

---

## 作者：orecic (赞：13)

### CDQ!!!

这道题显然有一个可持久化线段树的做法。

首先我们意识到这个极广的值域没有什么用处。

我们首先想到必然存在一个$\ x$使答案为$\ x$或者$\ [1,x-1]$中的最小的不存在的数字。

所以首先我们想到找到这个$\ x$然后把没有必要的数字全部删掉，这样剩下的数字必然再$\ [1,n]$中。

之后我们想到将$\ a_{i}$在$\ i$点存在转换为$\ a_{i}$在$\ [1,i-1],[i+1,n]$中不存在，设$\ i$的两个值为$\ q=i-1,w=i+1$，这样任意询问$\ [l,r]$就是$\ q \ge r$或者$\ w \le l$的数字中的最小值。这显然是一个一维偏序问题，那么我们显然可以将每个询问看做两个，直接桶排序即可。复杂度$\ O(n)$

实际上这种方法仅限于值的两两不同。

如果相同的值是存在的，那么我们依然可以将问题改变。显然如果同时存在两个值相同$\ a_{i}=a_{j},i<j$，那么显然为$\ a_{i}$在$\ [1,i-1],[i+1,j-1],[j+1,n]$不存在，我们将其拆为三个操作，$\ q_{1}=1，w_{1}=i-1,q_{2}=i+1,w_{2}=j-1,q_{3}=j+1,w_{3}=n$。对于每个询问$\ [l,r]$，即$\ q \le l$且$\ w \ge r$的最小值。那么我们先按照$\ q$或者$\ l$排序，cdq中按照$\ r$或者$\ w$，然后求解即可。$\ O(n \log_{2}{n})$

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch = getchar(); int x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)){ x = x*10+ch-'0'; ch = getchar(); }
    return x;
}
int n,a[300300],b[300300],m,xxx,tot=0,head,tail,ans[200200];
struct nobe
{
	int op,l,r,w,id;
}q[600600],tmp[600600];
inline bool cmp(nobe a,nobe b)
{
	return (a.l^b.l) ? (a.l<b.l) : (a.op<b.op);
}
inline void cdq(int l,int r)
{
	if(l==r) return ;
	int mid=(l+r)>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	int i=l,j=mid+1,ccnt=0,sum=999999999;
	while(j<=r)
	{
		while((q[i].r>=q[j].r)&&(i<=mid))
		{
			tmp[++ccnt]=q[i];
			if(q[i].op&1)
			{
				sum=min(sum,q[i].w);
			}
			++i;
		}
		tmp[++ccnt]=q[j];
		if(q[j].op^1)
		{
			ans[q[j].id]=min(ans[q[j].id],sum);
		}
		++j;
	}
	while(i<=mid)
	{
		tmp[++ccnt]=q[i];
		++i;
	}
	i=1;
	while(i<=ccnt)
	{
		q[l+i-1]=tmp[i];
		++i;
	}
}
int main()
{
	memset(b,0,sizeof(b));
	n=read();
	m=read();
	int i=1;
	while(i<=n)
	{
		a[i]=read();
		if(a[i]<=n) ++b[a[i]];
		++i;
	}
	i=-1;
	while(i<=n)
	{
		if(b[i+1]) ++i;
		else break;
	}
	xxx=i+1;
	i=0;
	while(i<xxx)
	{
		b[i]=0;
		++i;
	}
	i=1;
	while(i<=n)
	{
		if(a[i]<xxx)
		{
			if((i^1)&&(b[a[i]]^i-1))
			{
				q[++tot]=(nobe){1,b[a[i]]+1,i-1,a[i],0};
			}
			b[a[i]]=i;
		}
		++i;
	}
	i=0;
	while(i<xxx)
	{
		if(b[i]^n) q[++tot]=(nobe){1,b[i]+1,n,i,0};
		++i;
	}
	i=1;
	while(i<=m)
	{
		int l,r;
		l=read();
		r=read();
		ans[i]=xxx;
		q[++tot]=(nobe){2,l,r,0,i};
		++i; 
	}
	sort(q+1,q+tot+1,cmp);
	cdq(1,tot);
	i=1;
	while(i<=m)
	{
		printf("%d\n",ans[i]);
		++i;
	}
	return 0;
}
```



---

## 作者：一叶知秋。 (赞：13)

本题难是不难，只是~~有点~~非常卡常数啊啊啊

一不小心就一两版qwq（人丑常数大也有可能）

回滚莫队？不存在的，直接莫队+值域分块即可

快读写强点，块大小别用sqrt，用pow貌似快一些

还有块大小开成$n^{0.55}+1$貌似会快一些，~~不要问我怎么知道的~~

离散化当然不用了，答案最大就$n+1$，读者自证不难

贴代码：

```cpp
#include<cstdio>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

#define maxn 200022

inline int read(){
    int r=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return r;
}

inline int min(int a,int b){
    return a<b?a:b;
}

int n,m,l,r,size,a[maxn],lb[maxn],rb[maxn],pos[maxn],cnt[maxn],tot[maxn],ans[maxn];

struct Q{
    int l,r,num;
    bool operator <(const Q &q) const{
        return pos[l]^pos[q.l]?pos[l]<pos[q.l]:r<q.r;
    }
}q[maxn];

inline void add(int x){
    if(!cnt[a[x]])tot[pos[a[x]]]++;
    cnt[a[x]]++;
}

inline void del(int x){
    cnt[a[x]]--;
    if(!cnt[a[x]])tot[pos[a[x]]]--;
}

inline int query(){
    for(int i=1;i<=pos[n];i++){
        if(tot[i]==rb[i]-lb[i]+1)continue;
        for(int j=lb[i];j<=rb[i];j++)
            if(!cnt[j])return j;
    }
    return n;
}

int main(){
    n=read(),m=read();
    size=pow(n+2,0.5);
    for(int i=1;i<=n;i++){
        pos[i]=(i-1)/size+1;//值域反正是0~n+1，同时+1，用同一个块大小
        a[i]=min(read()+1,n+2);
    }
    pos[n+1]=n/size+1;
    pos[n+2]=(n+1)/size+1;
    n+=2;
    for(int i=1;i<=pos[n];i++){
        lb[i]=(i-1)*size+1;
        rb[i]=min(lb[i]+size-1,n);
    }
    for(int i=1;i<=m;i++){
        q[i].l=read(),q[i].r=read();
        q[i].num=i;
    }
    sort(q+1,q+m+1);
    l=q[1].l,r=q[1].l-1;
    for(int i=1;i<=m;i++){
        while(l>q[i].l)add(--l);
        while(r<q[i].r)add(++r);
        while(l<q[i].l)del(l++);
        while(r>q[i].r)del(r--);
        ans[q[i].num]=query()-1;
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Soulist (赞：11)

一种不太难想的做法？但可能码量大一些？？？

先把所有的询问按照 $l$ 排序。

现在考虑处理出一颗线段树维护一个区间，其中某一个叶子节点表示的含义，为：当前 $l$ 到 $(l \quad-\quad n )$这一区间内未出现的自然数是谁。

那么最初是的 $l$ 是 $1$，即每个叶子节点都表示从 $1$ 号点到 $x$ 点这一段区间内未出现的最小自然数。

那么我们要先处理出每个位置到 $1$ 号位置这一区间的最小未出现的自然数。

这个处理可以通过维护最小出现次数的权值线段树来做。

然后将处理出来的结果存入一个线段树内。

考虑对于 $l = 1 $ 的点，其答案直接通过这个线段树来作查询即可。

因为按照 $l$ 排序了，所以接下来的我们需要去更新线段树的其他节点。

然后考虑让 $l$ 向左移动，我们可以发现，删去一个数 $a[l]$ 其实就是让后面的点对其取 $min$。所以可以维护一个取 $min$ 标记。

但是考虑到某个元素可能重复出现，所以可以再开一个 $vector$ 维护每个点出现的位置，然后取 $min$ 操作就是对此点从当前位置到其下一个出现的位置这一段区间对 $x$ 取 $min$

具体实现上因为在 $vector$ 上二分找位置不太现实，然而我们已经按照 $l$排序，每个 $vector$ 内存的位置单调递增，所以可以维护一个 $fir[x]$ 表示当前的这个权值所对应的 $vector$ 到了那个点，每次更新完后$++ fir$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 2e5 + 5;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define ls(x) ( x * 2 )
#define rs(x) ( x * 2 + 1 )
#define Size 
#define inf 123456789
struct Tree { int l, r, mi, mark; }tr[N * 4], t[N * 4];
struct Q { int l, r, id, ans; }q[N];
vector< int> vec[N];
int a[N], n, m, fir[N], cnt;
bool cmp( Q x, Q y ) {
	return ( x.l == y.l ) ? x.r < y.r : x.l < y.l ;
} 
bool cmp2( Q x, Q y ) {
	return x.id < y.id;
}
// 权值线段树 
void insert1( int x, int l, int r, int wh ) {
	if( l == r ) { ++ tr[x].mi; return ; }; 
	int mid = ( l + r ) >> 1;
	if( mid >= wh ) insert1( ls(x), l, mid, wh );
	else insert1( rs(x), mid + 1, r, wh );
	tr[x].mi = min( tr[ls(x)].mi, tr[rs(x)].mi ); //用权值线段树维护区间最小出现次数 
}
int Query1( int x, int l, int r ) {
	if( l == r ) return l;
	int mid = ( l + r ) >> 1;
	if( !tr[ls(x)].mi ) return Query1( ls(x), l, mid ); // 如果左儿子内最小出现次数为0，往左儿子走 
	else return Query1( rs(x), mid + 1, r ); // 否则往右儿子走 
}
// 线段树 
void pushmark( int x ) { //区间取min的下传 
	if( t[x].mark != inf ) {
		t[ls(x)].mark = min( t[ls(x)].mark, t[x].mark );
		t[ls(x)].mi = min( t[ls(x)].mi, t[ls(x)].mark );
		t[rs(x)].mark = min( t[rs(x)].mark, t[x].mark );
		t[rs(x)].mi = min( t[rs(x)].mi, t[rs(x)].mark ); 
	}
}
void Ins( int x, int l, int r, int wh, int val ) {
	t[x].mark = inf ; //注意mark初始化为inf  
	if( l == r ) { t[x].mi = val; return ;}
	int mid = ( l + r ) >> 1 ;
	if( mid >= wh ) Ins( ls(x), l, mid, wh, val );
	else Ins( rs(x), mid + 1, r, wh, val );
	t[x].mi = min( t[ls(x)].mi, t[rs(x)].mi ); // 线段树同样维护区间最小值，方便取min操作 
}

void Cover( int x, int l, int r, int ll, int rr, int val ) {
	if( ll <= l && r <= rr ) { 
		t[x].mark = min( t[x].mark, val ) ; //取min 
		t[x].mi = min( t[x].mi, t[x].mark ) ;
		return ; 
	}
	if( l > rr || r < ll ) return ; //区间越界 
	pushmark(x) ; int mid = ( l + r ) >> 1 ; 
	Cover( ls(x), l, mid, ll, rr, val ) ;
	Cover( rs(x), mid + 1, r, ll, rr, val ) ;
	return ;
}

int Query2( int x, int l, int r, int wh ) { // 询问位置为wh的点的答案 
	if( l == r ) return t[x].mi; 
	pushmark(x); int mid = ( l + r ) >> 1;
	if( mid >= wh ) return Query2( ls(x), l, mid, wh ); 
	else return Query2( rs(x), mid + 1, r, wh );
}

void input() {
	n = read(), m = read();
	rep( i, 1, n ) {
		a[i] = read() + 1;  //加1，方便线段树处理 
		if( a[i] > n ) continue; // 如果a[i] 大于 n 就没有必要加入  
		vec[a[i]].push_back(i);
	}
	rep( i, 1, n ) vec[i].push_back(n + 1); //权值至多有n种，在每个点的vector最后面插入一个元素(n + 1)。 
}
void solve() {
	int x, ll = 1;
	rep( i, 1, n ) {
		if( a[i] <= n ) insert1( 1, 1, n, a[i] ); //如果比n小才插入权值线段树 
		x = Query1( 1, 1, n ), Ins( 1, 1, n, i, x );
		// x为询问 1-n 中未出现的权值，然后将作为位置i的答案插入线段树。 
	}
	rep( i, 1, m ) q[i].l = read(), q[i].r = read(), q[i].id = i;
	sort( q + 1, q + m + 1, cmp );
	rep( i, 1, m ) {
		while( ll < q[i].l ) {
			x = a[ll];
			if( x <= n ) Cover( 1, 1, n, ll + 1, vec[x][fir[x] + 1] - 1, x ), ++ fir[x]; 
			++ ll;
		}
		q[i].ans = Query2( 1, 1, n, q[i].r ) - 1;
	} 
} 
signed main()
{
	input() , solve() ;
	sort( q + 1, q + m + 1, cmp2 ); 
	rep( i, 1, m ) printf("%d\n", q[i].ans );
	return 0;
}
```

---

## 作者：miaow (赞：7)

听说正解是主席树，然而我只会莫队啊qwq

其他题解的莫队都是维护一个乱跳的指针指向答案，转移复杂度要算均摊……然而我也不会摊还分析啊qwq

### 思路

这题明显ai范围是搞笑的，极端情况就（0...n-1）答案是n，根本用不到1e9，所以把大于n的ai都改成n+1就行了

然后我们要找区间里第一个没出现过的自然数。“找第一个xxx”，你们还记得一个东西叫**lowbit**不

如果我们能弄一串二进制，每一位表示一个数字，把区间里没出现过的数字对应的那一位设为1，出现过的设为0，这样每次询问就可以一个lowbit解决了

然而数字要开到2e5啊。很简单，我们可以每31位压到一个int里，然后去找第一个不为0的位置算lowbit

怎么快速找第一个不为0的位置？我们再弄一个二进制串，不为0的设为1，为0的位设为0，这样我们又得到了一个二进制串，然后再往int里压，然后找第一个不为0的位置。这一层int数量是上一层的1/31，少了很多

我们可以多压几次，压到只有一个int，然后查询时一路lowbit下去就解决了。至于要压几层，log(31)2e5向上取整为4，所以弄四个int数组就行了。

至于莫队怎么转移，可以维护一个数组记录每个数字出现了几次，每次发现一个没出现过的数字进入区间时就在第一层int数组里找到对应的位设为1，然后如果这个int原来是0，那就把第二层对应的位也改为1，同理第三层第四层。一个数字退出区间的时候也类似这样。这样弄每一次转移需要做的事就是维护数字出现次数和修改那四层int，这是O(1)的……

于是这题就这样解决了

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int N=200000+5,N2=10000+5,N3=400+5,N4=20+5,Y=31;
int p2[32];
#define re register
void write(int x)
{
    if(x>9) write(x/10);
    putchar(x%10+48);
}
inline int read()
{
    re int sum;
    re char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    sum=c-'0';
    c=getchar();
    while(c>='0'&&c<='9')
    {
        sum=sum*10+c-'0';
        c=getchar();
    }
    return sum;
}
inline int imin(const int& qwe,const int& asd)
{
    return qwe<asd?qwe:asd;
}
int n,m,n2;
struct miaow
{
    int l,r;
    int zx;
    inline bool operator < (const miaow& qwe) const
    {
        return l/n2==qwe.l/n2?r<qwe.r:l<qwe.l;
    }
}q[N];
int a[N];
int sy[N]={0};
int ans[N];
int yw0[N2],yw1[N3],yw2[N4],yw3;  //四层压位int，最后一层只有一个所以不写成数组 
inline int lowb(int x)
{
    return x&(-x);
}
inline void csh()   //初始化全部位设为1 
{
    for(re int i=0;i<=n+1;++i)
    {
        yw0[i/Y]+=(1<<(i%Y));
    }
    for(re int i=0;i<=(n+1)/Y;++i)
    {
        yw1[i/Y]+=(1<<(i%Y));
    }
    for(re int i=0;i<=(n+1)/Y/Y;++i)
    {
        yw2[i/Y]+=(1<<(i%Y));
    }
    for(re int i=0;i<=(n+1)/Y/Y/Y;++i)
    {
        yw3+=(1<<(i%Y));
    }
    for(re int i=0;i<Y;++i)p2[i]=(1<<i);
}
inline int fia()  //四层lowbit查答案位置 
{
    re int ans,ans2,k;
    k=0;
    ans=lowb(yw3);ans2=lower_bound(p2,p2+Y,ans)-p2;
    k=k*Y+ans2;
    ans=lowb(yw2[k]);ans2=lower_bound(p2,p2+Y,ans)-p2;
    k=k*Y+ans2;
    ans=lowb(yw1[k]);ans2=lower_bound(p2,p2+Y,ans)-p2;
    k=k*Y+ans2;
    ans=lowb(yw0[k]);ans2=lower_bound(p2,p2+Y,ans)-p2;
    k=k*Y+ans2;
    return k;
}
inline void yw(re int x,int y)  //莫队转移
{
    x=a[x];
    sy[x]+=y;
    if(!sy[x]&&y<0)
    {
        if(!yw0[x/Y])
        {
            if(!yw1[x/Y/Y])
            {
                if(!yw2[x/Y/Y/Y])
                {
                    yw3+=(1<<(x/Y/Y/Y%Y));
                }
                yw2[x/Y/Y/Y]+=(1<<(x/Y/Y%Y));
            }
            yw1[x/Y/Y]+=(1<<(x/Y%Y));
        }
        yw0[x/Y]+=(1<<(x%Y));
    }
    if(sy[x]==1&&y>0)
    {
        yw0[x/Y]-=(1<<(x%Y));
        if(!yw0[x/Y])
        {
            yw1[x/Y/Y]-=(1<<(x/Y%Y));
            if(!yw1[x/Y/Y])
            {
                yw2[x/Y/Y/Y]-=(1<<(x/Y/Y%Y));
                if(!yw2[x/Y/Y/Y])
                {
                    yw3-=(1<<(x/Y/Y/Y%Y));
                }
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    n2=sqrt(n)+1;
    for(re int i=1;i<=n;++i)
    {
        int x=read();
        a[i]=imin(x,n+1);
    }
    csh();
    for(re int i=0;i<m;++i)
    {
        q[i].l=read(),q[i].r=read(),q[i].zx=i;
    }
    sort(q,q+m);
    re int x=1,y=1;
    yw(1,1);
    for(re int i=0;i<m;++i)
    {
        int l=q[i].l,r=q[i].r;
        while(y<r)++y,yw(y,1);
        while(x>l)--x,yw(x,1);
        while(y>r)yw(y,-1),--y;
        while(x<l)yw(x,-1),++x;
        ans[q[i].zx]=fia();
    }
    for(re int i=0;i<m;++i)
    {
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：姬小路秋子 (赞：6)

这道题不久前被牛客网搬过去做了f，然后一位神仙指点我们一个一只log的做法。

大概就是先把询问离线下来，然后线段树维护1--now这段的mex。然后考虑左端点向右移，我们发现当前位a[i]能影响的位置只有i——（a[i]下一次出现的位置-1）这段区间，所以我们在每次右移左端点时，只要将这段区间与原先的mex取个min，然后再询问答案即可。

代码：

```c
#include<bits/stdc++.h>
using namespace std;
struct aaa{
	int x,y,id;
}aa[1000001];
int la,n,m,nt[1000001],ans[1000001],a[1000001],f[1000001],g[1000001];
map<int,int>mp,mp1,hd;
bool cmp(aaa a,aaa b){
	return a.x<b.x;
}
void pushdown(int x,int l,int r){
	if(f[x]!=1e8){
		f[x*2]=min(f[x*2],f[x]);f[x*2+1]=min(f[x*2+1],f[x]);
		f[x]=1e8;
	}
}
void build(int x,int l,int r){
	f[x]=1e8;
	if(l==r){
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);build(x*2+1,mid+1,r);
}
void ins(int x,int l,int r,int t,int k,int s){
	if(t>k)return;
	if(l==t&&r==k){
		f[x]=min(f[x],s);
		return;
	}
	pushdown(x,l,r);
	int mid=(l+r)/2;
	if(mid>=k)ins(x*2,l,mid,t,k,s);
	 else if(t>mid)ins(x*2+1,mid+1,r,t,k,s);
	  else ins(x*2,l,mid,t,mid,s),ins(x*2+1,mid+1,r,mid+1,k,s);
}
int query(int x,int l,int r,int t){
	if(l==r)return f[x];
	pushdown(x,l,r);
	int mid=(l+r)/2;
	if(mid>=t)return query(x*2,l,mid,t);
	 else return query(x*2+1,mid+1,r,t);
}
int main(){
	int i;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		mp[a[i]]=1;
	}
	for(i=n;i;i--){
		nt[i]=hd[a[i]];
		if(!nt[i])nt[i]=n+1;
		hd[a[i]]=i;
	}
	for(i=1;i<=m;i++){
	 scanf("%d%d",&aa[i].x,&aa[i].y);
	 aa[i].id=i;
 }
    sort(aa+1,aa+m+1,cmp);
    la=0;
    for(i=1;i<=n;i++){
    	mp1[a[i]]=1;
    	while(mp1[la]>0)la++;
    	ins(1,1,n,i,i,la);
	}
	la=1;
	for(i=1;i<=m;i++){
		while(la<aa[i].x)ins(1,1,n,la+1,nt[la]-1,a[la]),la++;
		ans[aa[i].id]=query(1,1,n,aa[i].y);
	}
	for(i=1;i<=m;i++)printf("%d\n",ans[i]);
}
```

---

## 作者：_ctz (赞：5)

[安利波$blog$](https://ctz45562.github.io/2019/03/15/%E9%A2%98%E8%A7%A3-%E6%B4%9B%E8%B0%B7-P4137-%E3%80%90Rmq-Problem-mex%E3%80%91/)

[传送门](https://www.luogu.org/problemnew/show/P4137)

一道水题想了半天。。。

可以想到造棵权值线段树，查询时如果左儿子有这个区间内没有出现的数就走左儿子，否则走右儿子。如果用普通的主席树维护每个数出现的次数，就会发现这玩意不具有区间可减性，不是基于前缀和的主席树能维护的。

换个思路：对于第$i$棵权值线段树，维护一下**数列前$i$项中每个权值出现的最靠右的位置**。然后向上更新一下最小值。这样如果某个权值最靠右的位置都比查询区间左端点小的话，那它一定没有在这个区间里出现。维护最小值目的就是看最小的是否比左端点大，根据这个在线段树上二分。

权值范围是$10^9$的。题解里有说答案最大为$n$，直接把$>n$的$a[i]$处理为$n+1$就行。蒟蒻没有想到$QAQ$，说一下蒟蒻的处理：

用离散化，但是一个权值没有在数列里出现过的话就不会在离散化数组中，也不会出现在线段树中，查询会出锅。注意到一个询问的答案要么是$0$，要么是数列中某个数的值$+1$。这样离散化时把$0$和每个出现过的权值$+1$都丢进去就行了$QwQ$。

当然这道题不强制在线也不修改，可以把询问离线下来一边扫一边加，遇到询问右端点就查询左端点，不需要主席树（可持久化线段树），一棵权值线段树就可以了。

时间复杂度：$O(nlogn)$

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

#define maxn 400005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
int dis[maxn],ll[maxn],ans[maxn],len,a[maxn],n,m;
//dis是离散化数组，ll是每个询问的左端点，ans是答案
vector<int>line[maxn];
//line用来离线存每个询问
struct Segment_Tree{
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
	int dat[maxn<<2];
	inline void update(int node){
		dat[node]=min(dat[ls(node)],dat[rs(node)]);
	}
	void add(int poi,int l,int r,int node,int d){
		if(l==r){
			dat[node]=d;
            //因为是离线边扫边加，当前更新的位置一定是最靠右的，所以直接覆盖掉就行
			return;
		}
		int mid=l+r>>1;
		if(poi<=mid)add(poi,l,mid,ls(node),d);
		else add(poi,mid+1,r,rs(node),d);
		update(node);
	}
	int ask(int d){
		int l=1,r=len,node=1;
		while(l<r){
			int mid=l+r>>1;
			if(dat[ls(node)]<d)r=mid,node=ls(node);
            //左区间有最靠右的位置都比左端点小的，一定没出现过，向左走
			else l=mid+1,node=rs(node);
            //否则向右走
		}
		return dis[l];
	}
}st;
int main(){
	n=read(),m=read();
	for(register int i=1;i<=n;++i)
		dis[++len]=a[i]=read(),dis[++len]=a[i]+1;
    //把每个值+1添进去
	dis[++len]=0;
    //把0添进去
	sort(dis+1,dis+1+len);
	len=unique(dis+1,dis+1+len)-dis-1;
	for(register int i=1;i<=m;++i){
		ll[i]=read();
		line[read()].push_back(i);
	}
	for(register int i=1;i<=n;++i){
		a[i]=lower_bound(dis+1,dis+1+len,a[i])-dis;
		st.add(a[i],1,len,1,i);
		for(int j=0;j<line[i].size();++j){
			int k=line[i][j];
			ans[k]=st.ask(ll[k]);
		}
	}
	for(register int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
}

```



---

## 作者：hehelego (赞：4)

### 提供两种玩法,均可不开O2通过.  

## 声明:本题目 N,M,V(序列长度,查询次数,(有用的)值域)是同阶的.不做区分~~其实是我真的不会分析莫队复杂度~~

1. 莫队+分块 O(nsqrt(n))这样的复杂度(~~窝自己真的不会算啊~~)...我也不知道为什么能过...
2. 可持久化或者扫描线.O(nlogn)或者类似的复杂度...应该是本题的正解.  
```cpp
//PS代码在末尾
```
---

~~**注意到:大于n的数是没有贡献的,所以V和N同阶了**~~

---
先来说第一种...首先发现是个类似区间数颜色的问题....非常自然的想到用莫队维护区间内数的值域,然后最简单的是开个数组...**单次查询是O(N)的**.~~然后发现卡一卡.乱优化一下可以过....~~  
我们考虑上线段树维护值域信息.每个节点记录一下左边是不是有0(没出现过的数字).修改是单点加.pushup非常好做...直接继承左边的信息,叶子看自己的计数是不是0就好了.查询是类似线段树上二分的操作.考虑左边有0就深入左子树,否则进入右侧.到达叶子即可.这样单次修改和查询都是优秀的**O(logn)**,  ~~这个做法我没有实际写过.第一眼看到这个题目就想到这个做法....不知道能不能过~~  
**划重点**,分析第二种玩法的复杂度,考虑莫队算法的过程.我们有O(nsqrt(n))级别的修改,而只有O(n)的查询,**可以说修改和查询是很不平衡的**这时线段树的优势就体现不出来了...可以想象一个区间加区间和的题目如果只有一次区间加.那么我们显然不会使用线段树而是暴力.  
~~so what~~使用值域分块.**单点修改O(1),查询O(sqrtn),完美平衡了查询和修改的复杂度**,得到了O(nsqrt(n))的做法.可以通过.  
~~使用数据结构辅助莫队的时候,要注意到莫队的过程中修改与查询的不平衡,使用合适的数据结构来平衡这个复杂度,最常见的当然是值域分块了~~.

---

~~这不是数颜色的套路吗,开个pre记录同色前驱,然后就是矩形数点了.写KDT,或者上个扫描线或者可持久化降维,非常轻松啊~~  
这个MEX和数颜色其实有非常大的相似性.我们来考虑对于询问\[l,r],显然只有pos<=r的元素有用.我们再考虑没出现的数字有什么特征.
1. 他们在\[1,r]这个前缀里面根本没有...
2. 他们**最后一次出现**在pos<l的位置  

我们发现**每个颜色的最后一次出现位置**非常重要.我们令没有出现的数的最后一次出现位置为0,两种情况就可以被统一了.  
我们此时再考虑问题的本质:pos<=r,last<l的最小数.是一个二维偏序!两个都是前缀查询..可以随便用扫描线或者可持久化降维.

---


最后扔代码跑路.
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int N=200000+10;
const int V=200000+1;
const int BCNT=2000+10;
int n,m,a[N],ans[N];
int read(){
    int x=0;char ch;
    do{ch=getchar();}while(ch>'9'||ch<'0');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return x; 
}
int cnt[N],x[N],bel[N],bsz,bcnt,L[BCNT],R[BCNT],Sum[BCNT];
void init(){
    bsz=ceil(sqrt(V));
    bcnt=V/bsz;if(V%bsz) bcnt++;
    for(int i=0;i<=V;i++) bel[i]=1+i/bsz;
    for(int i=1;i<=bcnt;i++){
        L[i]=(i-1)*bsz;
        R[i]=i*bsz-1;
    }R[bcnt]=V;
}
inline void add(int p,int v){
    if(p>V) return ;
    cnt[p]+=v;
    if(v==1&&cnt[p]==1){x[p]=1;Sum[bel[p]]++;}
    if(v==-1&&cnt[p]==0){x[p]=0;Sum[bel[p]]--;}
}
int mex(){
    int blk=1;
    while(Sum[blk]==R[blk]-L[blk]+1) blk++;
    for(int i=L[blk];i<=R[blk];i++) if(x[i]==0) return i;
    return -1;
}
struct Q{
    int l,r,id;
    bool operator<(const Q &b)const{return bel[l]^bel[b.l]?l<b.l:r<b.r;}
}q[N];
int main(){
    init();
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=min(read(),V+1);
    for(int i=0;i<m;i++){
        q[i].id=i;
        q[i].l=read();q[i].r=read();
    }
    sort(q,q+m);
    int l=1,r=1;add(a[1],1);
    for(int i=0;i<m;i++){
        while(l<q[i].l) add(a[l++],-1);
        while(l>q[i].l) add(a[--l],1);
        while(r<q[i].r) add(a[++r],1);
        while(r>q[i].r) add(a[r--],-1);
        ans[q[i].id]=mex(); 
    }
    for(int i=0;i<m;i++) printf("%d\n",ans[i]);
    return 0;
}

```
上面是莫队,下面是扫描线...
```cpp
#include<iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
int read(){
    int x=0;char ch;
    do{ch=getchar();}while(ch>'9'||ch<'0');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return x;
}
const int N=200000+10;
const int M=N<<2;
int n,m,a[N],v,ans[N];
struct Q{ int l,r,id; bool operator<(const Q& b)const{return r<b.r;} }q[M];
int L[M],R[M],Min[M];
#define lc (o<<1)
#define rc ((o<<1)|1)
inline void pushup(int o){ Min[o]=min(Min[lc],Min[rc]); }
void build(int o,int l,int r){
    L[o]=l;R[o]=r;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(lc,l,mid); build(rc,mid+1,r);
}
void update(int o,int p,int v){
    if(L[o]==R[o]){Min[o]=v; return ; }
    if(p<=R[lc]) update(lc,p,v);
    else 				 update(rc,p,v);
    pushup(o);
}
int query(int o,int k){
    if(Min[o]>k) return n+1;
    if(L[o]==R[o]) return L[o];
    // 考虑是否有较小,出现位置<l的数...
    if(Min[lc]<k) return query(lc,k);
    return query(rc,k);
}
int main(){
    n=read();m=read();v=n+1;
    for(int i=1;i<=n;i++) a[i]=min(read(),v);
    for(int i=0;i<m;i++){
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q,q+m);
    build(1,0,v);
    int p=1;
    for(int i=0;i<m;i++){
        while(p<=q[i].r){ update(1,a[p],p); p++; }
        ans[q[i].id]=query(1,q[i].l);
    }
    for(int i=0;i<m;i++) printf("%d\n",ans[i]);
    return 0;
}

```






---

## 作者：木木！ (赞：3)

思路和一众大佬的思路差不多，先给询问按 $r$ 排序，就变成了扫描线问题，每次二分后查询 $[0,mid]$ 权值中出现位置最小的值。可以直接实现 $\Theta(q\log^2n)$ 或线段树上二分 $\Theta(q\log n)$。

但是注意到每次查询的最小值是权值数组上的前缀最小值，而前缀最小值可以考虑使用树状数组维护。树状数组维护前缀最小值的条件是每次修改只能往小改，那么只需要从后往前做就好了。

在树状数组上二分则类似于倍增，考虑一下询问前缀最小值的过程就可以很容易的理解这个二分方法了。

优点是码量和常数都很小，不易出错；缺点是有点难想。时间复杂度 $\Theta(n\log n+q\log n)$。

附 AC 代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

inline void chkmin(int& a,int b) { if(b<a) a=b; }

int getint()
{
	char ch;
	while((ch=getchar()) < '!') ;
	int x = ch^'0';
	while((ch=getchar()) > '!') x = (x*10)+(ch^'0');
	return x;
}

void putint(int x)
{
	if(x/10) putint(x/10);
	putchar((x%10)^'0');
}

int tx[200005];
const int trin = 200001;
const int logtn = 17;

int lowbit(int x) { return x&(-x); }

void init()
{
	memset(tx,0x7f,(trin+1)*sizeof(int));
}

void fix(int x,int v)
{
	while(x<=trin)
	{
		chkmin(tx[x],v);
		x += lowbit(x);
	}
}

int query(int l)  // 树状数组上二分
{
	int res = 0;
	for(int i=1<<logtn; i>=1; i>>=1)
	{
		if((res|i)<=trin && tx[res|i]>=l)
		{
			res |= i;
		}
	}
	return res;
}

struct qry
{
	int l;
	int r;
	int id;
};

bool cmp(qry a,qry b) { return a.r > b.r; }

int ai[200005];
int papx[200005];
int lapx[200005];

qry qi[200005];
int ansi[200005];

int main()
{
	const int n = getint();
	const int m = getint();
	for(int i=1; i<=n; ++i)
	{
		ai[i] = getint();
	}

	for(int i=1; i<=n; ++i)
	{
		papx[i] = lapx[ai[i]];
		lapx[ai[i]] = i;
	}

	init();
	for(int i=0; i<=trin; ++i)
	{
		fix(i+1,lapx[i]);
	}

	for(int i=1; i<=m; ++i)
	{
		qi[i].l = getint();
		qi[i].r = getint();
		qi[i].id = i;
	}
	sort(qi+1,qi+1+m,cmp);

	int qtop = 1;
	for(int i=n; i>=1; --i)
	{
		while(qi[qtop].r == i)
		{
			ansi[qi[qtop].id] = query(qi[qtop].l);
			++qtop;
		}
		fix(ai[i]+1,papx[i]);
	}

	for(int i=1; i<=m; ++i)
	{
		putint(ansi[i]);
		putchar('\n');
	}
}
```

---

## 作者：ustze (赞：1)

你们都会主席树，我只会莫队 \kel  
先说一下莫队的时间复杂度，在块大小为$\frac n{\sqrt m}$的情况下，是需要做$O(n\sqrt m)$次修改，$O(n)$次查询的，注意到修改和查询并不是平衡的，因此在莫队套数据结构是往往使用分块而非线段树这样的数据结构   
只能把莫队的方法汇总一下了  
另外此题中值域可以看作是$O(n)$的  
1 xjb跳，均摊复杂度未知（反正我不会算  
2 莫队时维护一个树状数组，单次修改$O(logn)$，查询时若暴力二分是$O(log^2n)$的，但利用树状数组的性质可以用倍增做到$O(logn)$（虽然实际上并没有多少影响），时间复杂度$O(mlogn+n\sqrt mlogn)$，不开o2过不了 （其实卡卡常应该也能过，代码如下 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m;
int block1,block2;
int a[N],bel[N];
inline int read(){
    int s=0;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
    return s;
}
struct node{
    int l,r,id;
}q[N];
inline int cmp(const node & a,const node & b){
    return bel[a.l]^bel[b.l] ? bel[a.l]<bel[b.l] : bel[a.l]&1 ? a.r<b.r : a.r>b.r;
}
int cnt[N],ans[N],c[N];
inline void modify(int x,int t){
    for(;x<=n+2;x+=x&-x) c[x]+=t;
}
inline void add(int x){
    if(!cnt[x]++) modify(x+1,1);
}
inline void del(int x){
    if(!--cnt[x]) modify(x+1,-1);
}

inline int query(){
    int ans=0,sum=0;
    for(int i=17;i>=0;i--){
        int t=(1<<i);
        if(ans+t>n+1) continue;
        if(sum+c[ans+t]==ans+t) ans+=t,sum+=c[ans];
    }
    return ans;
}
int main(){
    n=read(),m=read();
    block1=n/sqrt(m*2/3),block2=sqrt(n);
    for(int i=1;i<=n;i++){
        a[i]=min(read(),n+1);
        bel[i]=(i-1)/block1+1;
    }
    for(int i=1;i<=m;i++)
        q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        for(;r<q[i].r;r++) add(a[r+1]);
        for(;r>q[i].r;r--) del(a[r]);
        for(;l<q[i].l;l++) del(a[l]);
        for(;l>q[i].l;l--) add(a[l-1]);
        ans[q[i].id]=query();
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
```
3 值域分块，利用其$O(1)-O(\sqrt n)$的复杂度，可以将时间复杂度优秀的平衡为$O(n\sqrt m+n\sqrt n)$，因为有人写了，我就不贴代码了

---

## 作者：ferrum_cccp (赞：1)

我们考虑莫队的做法。如果我们删除一个数，那么用被删的数更新mex即可。如果加入一个数，似乎比较麻烦（至少本蒟蒻没想出来）。

于是我们借鉴回滚莫队的思想，写出只需删除不需插入的莫队。

大于n的数对答案无影响，在处理时可以直接忽略。

```CPP
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxn=2e+5+5;
int n,m,ksiz;
int aa[maxn];
int bb[maxn];
int bl[maxn];
//unordered_map<int,int> se;
//unordered_map<int,int> se2;
int se[maxn],se2[maxn];
int ans=0,ans2=0,ans3=0;
struct query{
    int l;
    int r;
    int ans;
    int id;
}qq[maxn];
bool operator <(query x,query y){
    return bl[x.l]==bl[y.l]?x.r>y.r:bl[x.l]<bl[y.l];
}
int cnt=0;
void add(int pos){
    cnt++;
    if(aa[pos]>n+1)return;
    se[aa[pos]]++;
}
void del(int pos,int &myans){
    cnt++;
    if(aa[pos]>n+1)return;
    se[aa[pos]]--;
    if(se[aa[pos]]==0)myans=min(myans,aa[pos]);
}
int res[maxn];
int main(){
    scanf("%d%d",&n,&m);
    rep(i,1,n)scanf("%d",aa+i),bb[i]=aa[i];
    sort(bb+1,bb+n+1);
    rep(i,1,n)if(bb[i]==ans)ans++;
    ksiz=sqrt(n);
    rep(i,1,n)bl[i]=(i-1)/ksiz*ksiz+1;
    rep(i,1,m)scanf("%d%d",&qq[i].l,&qq[i].r);
    rep(i,1,m)qq[i].id=i;
    sort(qq+1,qq+m+1);
    int l=1,r=n;
    rep(i,1,n)se[aa[i]]++;
    ans2=ans;
    rep(i,1,m){
        if(bl[qq[i].l]==bl[qq[i].r]){
            rep(j,qq[i].l,qq[i].r)if(aa[j]<=n+1)se2[aa[j]]++;
            qq[i].ans=0;
            while(se2[qq[i].ans])qq[i].ans++;
            rep(j,qq[i].l,qq[i].r)if(aa[j]<=n+1)se2[aa[j]]--;
            continue;
        }
        while(l<bl[qq[i].l]){
            while(r<n)add(++r); //restore right
            del(l++,ans); //move kuai
            ans2=ans;
        }
        while(r>qq[i].r)del(r--,ans2); //move right
        ans3=ans2;
        int lpie=l;
        while(lpie<qq[i].l)del(lpie++,ans3);
        while(lpie>l)add(--lpie);
        qq[i].ans=ans3;
    }
    rep(i,1,m)res[qq[i].id]=qq[i].ans;
    rep(i,1,m)printf("%d\n",res[i]);
    //cout<<cnt<<endl;
    return 0;
}

```

---

