# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2```

### 输出

```
2```

# 题解

## 作者：fletmer (赞：45)

# 需要合并子区间查询线段树，难点在于PushUp和Query~~
### 先扯点没用的
1. 注意代码风格，大佬说好的码风能够更快的进步
2. 快读是个好习惯

### 下面讲正经的 
1. 线段树用结构体存，需要维护很多东西
2. 关于PushUp：类似于ST表的查询，我们在合并两区间的时候，需要先求出紧靠左端点的最大子段和与最靠近右端点的，要求两个字段必须要有公共区间以完全覆盖查询区间，具体看代码理解
3. 重点在于查询，这里使用了结构体类型定义函数，这样写更加简洁，分情况查询，查询区间左端点在mid右，右端点在mid左，查询区间覆盖节点，查询区间被节点左右区间包含，合并查询类似于PushUp的操作，还是看代码理解
4. 注意输出的时候当然是输出Query（1,1,n,ql,qr).dat，因为是结构体类型，记记操作，当模板题写
5. dalao说一个算法学不会就写一遍，还学不会就再写两遍，三遍.....


```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#define SIZE 50010
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
int n,m,x,y;
struct SegmentTree{
    int sum,lmax,rmax,dat;
}tr[SIZE<<2];

inline int rin(){
    int f=1,x=0; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=getchar();
    return f*x;
}
inline void Update(int p){
    tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
    tr[p].lmax=max(tr[p<<1].lmax,tr[p<<1].sum+tr[p<<1|1].lmax);
    tr[p].rmax=max(tr[p<<1|1].rmax,tr[p<<1|1].sum+tr[p<<1].rmax);
    tr[p].dat=max(max(tr[p<<1].dat,tr[p<<1|1].dat),tr[p<<1].rmax+tr[p<<1|1].lmax);
}
inline void Build(int p,int l,int r){
    if(l==r){tr[p].dat=tr[p].sum=tr[p].lmax=tr[p].rmax=rin(); return;}
    int mid=(l+r)>>1;
    Build(lson); Build(rson);
    Update(p);
}
inline SegmentTree Query(int p,int l,int r,int ql,int qr){
    if(ql<=l&&qr>=r) return tr[p];
    int mid=(l+r)>>1;
    if(ql>mid) return Query(rson,ql,qr);
    if(qr<=mid) return Query(lson,ql,qr);
    else{
        SegmentTree ans,a,b;
        a=Query(lson,ql,qr); b=Query(rson,ql,qr);
        ans.sum=a.sum+b.sum;
        ans.dat=max(a.dat,a.rmax+b.lmax),ans.dat=max(ans.dat,b.dat);
        ans.lmax=max(a.lmax,a.sum+b.lmax);
        ans.rmax=max(b.rmax,b.sum+a.rmax);
        return ans;
    }
}

int main(){
    n=rin();
    Build(1,1,n);
    m=rin();
    for(int i=1;i<=m;i++){
        x=rin(),y=rin();
        printf("%d\n",Query(1,1,n,x,y).dat);
    }
    
    return 0;
}
```

---

## 作者：subarude (赞：36)

##### 在blog里康或许体验更好哦 $\ \ \ \ $因为有可爱的$miku$的壁纸$qwqwq$

## $\texttt {线段树}$




大体思路就是用线段树维护**区间最大子段和**、**区间和**、**区间最大前缀和**、**区间最大后缀和**

下面是原因



------------


- **最大子段和**


就是题目的查询



------------


- **区间最大前缀和&区间最大后缀和**


线段树合并时有两种更新答案的方式

一种是当前区间的某个儿子的最大子段和直接成为了他的最大子段和

另一种是当前区间的最大子段和在左右儿子中各有一部分

第一种情况可以直接取$max(ans[lc], ans[rc])$

第二种情况显然是他左儿子的最大后缀和加右儿子的最大前缀和




------------


- **区间和**


因为要维护最大前缀和&最大后缀和

合并的时候这两个东西的更新也是分为两种情况

以区间最大前缀和为例

与最大子段和很相似

第一种是当前区间最大前缀和就是他左儿子的最大前缀和

还有一种是他的前缀和是从他的左端点到他的右儿子的某个位置

前一种很好更新

后一种就是他的左儿子的区间和加他右儿子的最大前缀和

















------------




- 再来说一个小细节（因为我太弱所以错了的细节）$QwQ$


如果一段区间全部都是负数，那么最大子段和就是这个区间的最大值

（所以在赋初始值时不要因为它是负数就让区间最大前缀和，后缀和，子段和为0）


~~不然就会像我一样WA的hin惨~~$qwqwq$





------------



- 再说一下代码里的实现和细节




- 用$arr$存原数组

- 用$sum$存区间和

- 用$data$存区间最大子段和

- 用$prefix$存区间最大前缀和

- 用$suffix$存区间最大后缀和

- 开一个结构体在重载一下加号可以方便地$update$



------------

------------

~~丑陋的代码~~$qwqwq$


```cpp
#include <cstdio>
#include <iostream>

#define maxn 50005

using namespace std;

inline int read() {
	int op = 1, a = 0; char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') op = -1;
	for (; c >= '0' && c <= '9'; c = getchar()) a = a * 10 + c - '0';
	return op * a;
}

int n, m;
int arr[maxn];

#define lc (u << 1)
#define rc (u << 1 | 1)
#define Seg SegmentTree

struct SegmentTree {
	int l, r, sum, maxi, data, prefix, suffix;
	SegmentTree() { l = r = 0; sum = data = prefix = suffix = 0; }
	void init(int x) {
		l = r = x;
		sum = data = prefix = suffix = arr[x];
	}
	SegmentTree operator + (const Seg& b) const {
		Seg c; c.l = l, c.r = b.r;
		c.sum = sum + b.sum;
		c.data = max(data, b.data);
		c.data = max(c.data, suffix + b.prefix);
		c.prefix = max(prefix, sum + b.prefix);
		c.suffix = max(b.suffix, b.sum + suffix);
		return c;
	}
} tr[maxn << 2];

inline void update(int u) { tr[u] = tr[lc] + tr[rc]; }

void build(int u, int l, int r) {
	if (l == r) { tr[u].init(l); return; }
	int mid = l + r >> 1;
	build(lc, l, mid), build(rc, mid + 1, r);
	update(u);
}

Seg query(int u, int l, int r) {
	if (l <= tr[u].l && r >= tr[u].r) return tr[u];
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid && r > mid) return query(lc, l, r) + query(rc, l, r);
	else {
		if (l <= mid) return query(lc, l, r);
		if (r > mid) return query(rc, l, r);
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; i++) arr[i] = read();
	build(1, 1, n);
	m = read();
	for (; m; m--) {
		int x = read(), y = read();
		cout << query(1, x, y).data << '\n';
	}
	return 0;
}
```



------------


如发现问题或认为哪里表述不当欢迎指出

（主页有QQ）~~强烈明示~~



---

## 作者：Great_Influence (赞：31)

猫树模板题。

在一般的数据下，本题可以直接在$O((n+q)\log n)$通过。

但是如果$q$特别大(如$10^6\to10^7$)，那么这种做法显然不够优秀。

我们需要一种支持$O(1)$查询的数据结构。

那么，有没有一种数据结构支持$O(1)$查询呢?

[猫树](http://immortalco.blog.uoj.ac/blog/2102)。

本题就是猫锟举的第一个例子。

为了解决问题，我们需要预处理区间最大子段和和区间最大中心和(指从当前节点到达区间中心的连续和)。这个可以简单做到$O(1)$转移。该部分时间复杂度为$O(n\log n)$。然后询问时，直接从2个最大子段和和2个最大中心和之和中间取最大值即可。这部分是$O(1)$的。

因此，总时间复杂度为$O(n\log n+q)$。

经过测试，下面的题解(借用一下)在$n=5\times 10^4,q=10^6$情况下需要$3.247s$，而利用猫树只需要$0.715s$（然而猫锟的只要$0.122s$）。

代码:

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define Chkmin(a,b) a=a<b?a:b
using namespace std;

template<typename T>inline void read(T &x)
{
    T f=1;x=0;char c;
    for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=x*10+(c^48);
    x*=f;
}

inline void write(int x)
{
	if(x<0)putchar('-'),x*=-1;
	if(!x)putchar(48);
	static int sta[45],tp;
	for(tp=0;x;x/=10)sta[++tp]=x%10;
	for(;tp;putchar(sta[tp--]^48));
	putchar('\n');
}

void file()
{
    #ifndef ONLINE_JUDGE
        freopen("a.in","r",stdin);
        freopen("a.out","w",stdout);
    #endif
}
const int MAXN=(1<<19)+7;

static int n,m,a[MAXN],len,Log2[MAXN],pos[MAXN];

namespace Meow_Tree
{
	static int p[21][MAXN],s[21][MAXN];//区间最大子段和，区间最大前缀和
	void build_tree(int h,int l,int r,int dps)
	{
		if(l==r){pos[l]=h;return;}
		int mid=(l+r)>>1,prep,sm;
		p[dps][mid]=s[dps][mid]=sm=a[mid];
		prep=a[mid];
		if(sm<0)sm=0;
		Repe(i,mid-1,l)
		{
			prep+=a[i];sm+=a[i];
			s[dps][i]=max(s[dps][i+1],prep);
			p[dps][i]=max(p[dps][i+1],sm);
			if(sm<0)sm=0;
		}

		p[dps][mid+1]=s[dps][mid+1]=sm=a[mid+1];
		prep=a[mid+1];
		if(sm<0)sm=0;
		Rep(i,mid+2,r)
		{
			prep+=a[i];sm+=a[i];
			s[dps][i]=max(s[dps][i-1],prep);
			p[dps][i]=max(p[dps][i-1],sm);
			if(sm<0)sm=0;
		}
		build_tree(h<<1,l,mid,dps+1);
		build_tree(h<<1|1,mid+1,r,dps+1);
	}

	inline int query(int l,int r)
	{
		if(l==r)return a[l];
		static int dps;dps=Log2[pos[l]]-Log2[pos[l]^pos[r]];
		return max(max(p[dps][l],p[dps][r]),s[dps][l]+s[dps][r]);
	}
}

using namespace Meow_Tree;

inline void init()
{
	read(n);
	Rep(i,1,n)read(a[i]);
	len=2;while(len<n)len<<=1;
	Rep(i,2,len<<1)Log2[i]=Log2[i>>1]+1;
	build_tree(1,1,len,1);
}

inline void solve()
{
	read(m);
	static int l,r;
	Rep(i,1,m)read(l),read(r),write(query(l,r));
}

int main()
{
    file();
    init();
    solve();
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
```

附猫锟的代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RG register
#define IL __inline__ __attribute__((always_inline))
#define For(i, a, b) for(RG int i = a, ___u = b; i <= ___u; ++i)
#define Dor(i, a, b) for(RG int i = b, ___d = a; i >= ___d; --i)
#define Rep(i, a, b) for(RG int i = a, ___u = b; i != ___u; ++i)
#define dmin(a, b) ((a) < (b) ? (a) : (b))
#define dmax(a, b) ((a) > (b) ? (a) : (b))
#define cmin(a, b) ((a) > (b) ? (a) = (b) : 1)
#define cmax(a, b) ((a) < (b) ? (a) = (b) : 1)
#define ddel(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
#define dabs(i) ((i) > 0 ? (i) : -(i))
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef long double ld;

#include <queue>
#include <vector>

namespace pb_ds
{   
    // 输入输出优化模板从此开始
    namespace io
    {
        const int MaxBuff = 1 << 15;
        const int Output = 1 << 23;
        char B[MaxBuff], *S = B, *T = B;
        //#define getc() getchar()
        #define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
        char Out[Output], *iter = Out;
        IL void flush()
        {
            fwrite(Out, 1, iter - Out, stdout);
            iter = Out;
        }
    }

    template<class Type> IL Type read()
    {
        using namespace io;
        RG char ch; RG Type ans = 0; RG bool neg = 0;
        while(ch = getc(), (ch < '0' || ch > '9') && ch != '-')     ;
        ch == '-' ? neg = 1 : ans = ch - '0';
        while(ch = getc(), '0' <= ch && ch <= '9') ans = ans * 10 + ch - '0';
        return neg ? -ans : ans;
    }
    template<class Type> IL void Print(RG Type x, RG char ch = '\n')
    {
        using namespace io;
        if(!x) *iter++ = '0';
        else
        {
            if(x < 0) *iter++ = '-', x = -x;
            static int s[100]; RG int t = 0;
            while(x) s[++t] = x % 10, x /= 10;
            while(t) *iter++ = '0' + s[t--];
        }
        *iter++ = ch;
    }
    // 输入输出优化模板到此结束

    const int MaxN = 200010;
    const ll inf = 1000000000000000000ll;
    int val[MaxN], pos[MaxN];
    struct Node
    {
        struct Data {ll pre, sum;} *dl, *dr;
        int mov_l, mov_r;
        IL ll query(RG int l, RG int r)
        {
            return dl[l -= mov_l].sum > dr[r -= mov_r].sum 
                ? dmax(dl[l].sum, dl[l].pre + dr[r].pre)
                : dmax(dr[r].sum, dl[l].pre + dr[r].pre);
        }
    } T[524288];
    int N;
    void build(RG int i, RG int l, RG int r)
    {
        if(l + 1 == r || N <= l) return;
        RG int m = (l + r) >> 1;
        build(i << 1, l, m);
        build(i << 1 | 1, m, r);

        RG Node *o = T + i;
        o->dl = new Node::Data[m - l], o->mov_l = l;
        o->dr = new Node::Data[r - m], o->mov_r = m;
        RG ll pre, max_pre, sum, max_sum;
        pre = sum = 0, max_pre = max_sum = -inf;
        for(RG int k = m - 1; k >= l; --k)
        {
            pre += val[k],                     cmax(max_pre, pre);
            sum = dmax(sum, 0) + val[k],    cmax(max_sum, sum);
            o->dl[k - l] = (Node::Data) {max_pre, max_sum};
        }
        pre = sum = 0, max_pre = max_sum = -inf;
        for(RG int k = m; k <= r - 1; ++k)
        {
            pre += val[k],                     cmax(max_pre, pre);
            sum = dmax(sum, 0) + val[k],    cmax(max_sum, sum);
            o->dr[k - m] = (Node::Data) {max_pre, max_sum};
        }
    }
    int pre[1024];

    IL void main()
    {
        RG int (*F)() = read<int>;
        RG int n = N = F();
        Rep(i, 0, n) val[i] = F();
        RG int D = 1; while(D < n) D <<= 1;
        build(1, 0, D);
        RG int l, r, d, v;
        pre[0] = 0;
        Rep(i, 1, 1024) pre[i] = pre[i >> 1] + 1;
        Rep(_, 0, F())
        {
            l = F() - 1, r = F() - 1;
            if(l == r) Print(val[l]);
            else
            {
                l += D, r += D;
                v = l ^ r;
                d = (v < 1024 ? pre[v] : 10 + pre[v >> 10]);
                Print(T[l >> d].query(l - D, r - D));
            }
        }
        io::flush();
    }
}

int main()
{
	pb_ds::main();
    fclose(stdin), fclose(stdout);  
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
}
```

---

## 作者：Karry5307 (赞：15)



### 题意

给一段序列（不一定是正整数），支持查询最大子段和。
### 题解
因为$\text{GSS}$系列基本上都是数据结构题，所以还是考虑线段树。

但是这个线段树可不好想，主要是最大子段和不好维护……

考虑采用分治的思想来维护最大子段和，那么一个大的序列的最大子段和是怎么表示的呢？

想到用区间的左右端点表示这个最大子段和所在的区间，于是我们对这个区间的端点位置进行讨论。

![](https://cdn.luogu.com.cn/upload/pic/40495.png)

这个图表示所有端点都在左边的区间上的情况，于是把左子区间的最大子段和计入候选值。

![](https://cdn.luogu.com.cn/upload/pic/40531.png)

这个图表示所有端点都在右边的区间上的情况，于是把右子区间的最大子段和计入候选值。

![](https://cdn.luogu.com.cn/upload/pic/40532.png)

这个图表示区间左端点在左边，右端点在右边的情况，这个可以拆分成左子区间的最大后缀和加上右子区间的最大前缀和，将这个值计入候选值。

将这三个最大子段和的候选值去$\max$即得该区间的最大子段和。

为了维护最大子段和，引进了最大前缀和和最大后缀和，所以接下来解决区间的最大前缀和和最大后缀和。

还是使用分治的思想，把要求的区间分成两个子区间，对前缀和的右端点进行讨论。

![](https://cdn.luogu.com.cn/upload/pic/40535.png)

这个图表示右端点在左边的情况，此时将左区间的最大前缀和计入候选值。

![](https://cdn.luogu.com.cn/upload/pic/40536.png)

这个图表示右端点在右边的情况，此时可拆分成左子区间和和右子区间的最大前缀和，将这个值计入候选值。

以上两个候选值取$\max$即得到该区间的最大前缀和，最大后缀和同理。

维护最大前缀和与后缀和是，引入了区间和，而这个是很好完成的。

在查询的时候分类讨论一下，如果这个区间要拆分，那么将两个部分算出来后在合并一下就好了，所以建议大家在这一天写**结构体式线段树**，返回结构体就好归并啦。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51;
struct SegmentTree{
    ll l,r,prefix,suffix,sum,maxn;  
};
SegmentTree tree[MAXN];
ll cnt,qcnt,l,r;
ll num[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void update(ll node)
{
    ll res;
    tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
    tree[node].maxn=max(tree[node<<1].maxn,tree[(node<<1)|1].maxn);
    res=tree[node<<1].suffix+tree[(node<<1)|1].prefix;
    tree[node].maxn=max(tree[node].maxn,res);
    res=tree[node<<1].sum+tree[(node<<1)|1].prefix;
    tree[node].prefix=max(tree[node<<1].prefix,res);
    res=tree[node<<1].suffix+tree[(node<<1)|1].sum;
    tree[node].suffix=max(tree[(node<<1)|1].suffix,res);
}
inline SegmentTree merge(SegmentTree x,SegmentTree y)
{
    SegmentTree res;
    res.sum=x.sum+y.sum;
    res.maxn=max(x.maxn,max(y.maxn,x.suffix+y.prefix));
    res.prefix=max(x.prefix,x.sum+y.prefix);
    res.suffix=max(y.suffix,x.suffix+y.sum);
    return res;
}
inline void create(ll l,ll r,ll node)
{
    tree[node].l=l,tree[node].r=r;
    if(l==r)
    {
        tree[node].sum=tree[node].maxn=num[l];
        tree[node].prefix=tree[node].suffix=num[l];
        return;
    }
    ll mid=(l+r)>>1;
    create(l,mid,node<<1);
    create(mid+1,r,(node<<1)|1);
    update(node);
}
inline SegmentTree queryMax(ll l,ll r,ll node)
{
    if(l<=tree[node].l&&r>=tree[node].r)
    {
        return tree[node];
    }
    ll mid=(tree[node].l+tree[node].r)>>1;
    SegmentTree res;
    if(l>mid)
    {
        return queryMax(l,r,(node<<1)|1);
    }
    if(r<=mid)
    {
        return queryMax(l,r,node<<1);
    }
    else
    {
        SegmentTree x=queryMax(l,r,node<<1),y=queryMax(l,r,(node<<1)|1);
        return merge(x,y);
    }
}
int main()
{
    cnt=read();
    for(register int i=1;i<=cnt;i++)
    {
        num[i]=read();
    }
    create(1,cnt,1);
    qcnt=read();
    for(register int i=0;i<qcnt;i++)
    {
    	l=read(),r=read();
    	printf("%d\n",queryMax(l,r,1).maxn);
    }
}
```

---

## 作者：UnyieldingTrilobite (赞：11)

一个 paper 提供了一个线性时间预处理常数时间查询的算法，这里是它的学习笔记。阅读之前请先确认你有一份标准 RMQ 的板子。

首先我们现在有一个数组 $A$，要对它跑静态最大子段和问题。

比如我们现在有这样的数组：`1 1 -4 5 -1 1`。本来想凑数字的但那个序列性质不太好，改了一下。

我们先累一遍前缀和存进数组 $C$：`1 2 -2 3 2 3`。特别的，我们认 $C_0=0$。

我们考虑维护这样一个数组 $L$，作为 $C$ 数组每个位置前最后一个不小于自己的下标，不存在则记为 0：`0 0 2 0 4 4`。这个单调栈扫一遍就可以求出来，但实际上下面的东西用悬线法维护会更有优势，不在此赘述。

我们再考虑维护这样一个数组 $P$，作为 $C$ 数组对应下标 $L_i$ 到 $i-1$ 之间最小值的下标（如果有多个，取最右的），再加一：`1 1 3 4 5 6`。

我们接下来维护一个序列 $M$ 满足 $M_i=C_i-C_{P_i-1}$：`1 2 -4 5 -1 1`。换而言之这个东西维护了 $[P_i,i]$ 的区间和。

我们考虑一个子段 $[i,j]$。这个子段的和是 $S_j-S_{i-1}$。如果 $i\le L_j$，那么把 $j$ 改成 $L_j$ 一定更优；反之，把 $i$ 改成 $P_j$ 一定更优。根据 $L$ 和 $P$ 的性质，这是显然的。换而言之，我们所有可能成为**全局**最大子段和答案的数，已经全都存在 $M$ 里了。

我们再考虑两个子段 $[P_i,i]$ 和 $[P_j,j]$，不妨 $i\lt j$。我们考虑如果有 $P_j\in(P_i,i]$，那么一旦同时有 $L_j\le P_i$，则同时可以推出 $C_{P_i-1}\lt C_{P_j-1}$ 和 $C_{P_i-1}\ge C_{P_j-1}$，原理是这俩 $P$ 互相落入了对方的辖区内。但若反之，则 $(P_i,i)$ 中存在超过 $C_j$ 的 $C_k$。由于 $k>P_i$ ，可以推得 $C_i\gt C_k$。由于 $i\ge P_j$，可以推得 $C_j\gt C_i$，矛盾。这个事情告诉我们，对于每个 $[P_i,i]$，其两两之间要么包含要么无交。

一些基本性质已经推完了，接下来我们考虑这个事情怎么上区间了。在最大性的证明中，我们发现 $j$ 改成 $L_j$ 的最优性是不变的，区别仅仅是把 $i$ 改成 $P_j$ 时可能会翻车。根据 $P$ 的定义和前缀和的性质，我们会发现如果把区间当成原序列来看并重新建 $P$，那么如果 $P_i\ge l$，则重建的 $P_i$ 与原来相同。

我们考虑无视 $P$ 的限制，只考虑 $i\in[l,r]$ 把 $M_i$ 的最大值给求出来。我们不妨求出来的区间是 $[P_i,i]$，如果 $P_i\ge l$ 那么问题已经结束了。我们只考虑 $P_i\lt l$，那么我们注意到对于 $j\in[l,i)$ 一定有 $C_j\lt C_i$，完全不用考虑；对于 $j\in(i,r]$，考虑 $[P_i,i]$ 和 $[P_j,j]$ 要么不交要么包含。对于不交，一定有 $P_j\gt i\ge l$；对于包含，有 $P_j\le P_i\lt i\lt j$，那么有 $C_{P_j-1}\le C_{P_i-1}\le C_i\lt C_j$，$[P_j,j]$ 优于 $[P_i,i]$，矛盾。换而言之，$\forall j\in(i,r]$，$P_j\ge l$。也就是说，我们的答案，要么是 $M_{i+1}$ 到 $M_r$ 之间的最大值，要么是 $C_i-C_j$ 其中 $j\in[l-1,i)$ 的最大值。两个标准 RMQ 就能把这玩意做掉。

于是我们就做完了，复杂度 $O(n)$ 预处理，$O(1)$ 单次查询，代码其实还挺短的。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e4 + 9;
template <class cmp>
struct RMQ {
  const static int L = 10, W = 6;
  typedef unsigned long long ull;
  int dat[N], st[L][(N >> W) + 1];
  ull stk[N];
  int qib(int l, int r, int b) const {
    ull v = stk[r] >> (l - (b << W));
    return __lg(v & -v) + l;
  }
  int xmin(int x, int y) const { return cmp()(dat[x], dat[y]) ? x : y; }
  RMQ() {}
  RMQ(int* a, int n) {
    memcpy(dat, a, n * sizeof(int));
    int m = ((n - 1) >> W) + 1;
    for (int i = 0; i < n; ++i) {
      int& s = st[0][i >> W];
      if (!(i & ((1 << W) - 1)))
        s = i;
      else
        s = xmin(s, i);
    }
    for (int i = 0; i + 1 < L; ++i)
      for (int j = 0; j + (1 << (i + 1)) <= m; ++j)
        st[i + 1][j] = xmin(st[i][j], st[i][j + (1 << i)]);
    for (int i = 0; i < m; ++i) {
      int l = i << W, r = min(l + (1 << W), n);
      stk[l] = 1;
      for (int j = l + 1; j < r; ++j) {
        ull t = stk[j - 1];
        while (t) {
          int h = __lg(t);
          if (!cmp()(a[j], a[h + l])) break;
          t ^= 1ull << h;
        }
        stk[j] = t | 1ull << (j - l);
      }
    }
  }
  int operator()(int l, int r) const {
    int lb = l >> W, rb = r >> W;
    if (lb == rb) return qib(l, r, lb);
    int ans = xmin(qib(l, ((lb + 1) << W) - 1, lb), qib(rb << W, r, rb));
    if (++lb != rb) {
      int h = __lg(rb - lb);
      ans = xmin(ans, xmin(st[h][lb], st[h][rb - (1 << h)]));
    }
    return ans;
  }
};
RMQ<less<int>> Cmin;
RMQ<greater<int>> Mmax;
int n, m, A[N], C[N], L[N], P[N], M[N];
void build() {
  for (int i = 1; i <= n; ++i) {
    C[i] = C[i - 1] + A[i], P[i] = i, L[i] = i - 1;
    while (L[i] && C[L[i]] < C[i]) {
      if (C[P[L[i]] - 1] < C[P[i] - 1]) P[i] = P[L[i]];
      L[i] = L[L[i]];
    }
    M[i] = C[i] - C[P[i] - 1];
  }
  Cmin = RMQ<less<int>>(C, n + 1);
  Mmax = RMQ<greater<int>>(M, n + 1);
}
int query(int l, int r) {
  int i = Mmax(l, r);
  if (P[i] >= l) return M[i];
  int ans = C[i] - C[Cmin(l - 1, i)];
  if (i != r) ans = max(ans, M[Mmax(i + 1, r)]);
  return ans;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> A[i];
  build(), cin >> m;
  for (int l, r; m; --m) cin >> l >> r, cout << query(l, r) << '\n';
  return cout << flush, 0;
}
```

---

## 作者：潜翎 (赞：11)

[SP1043 GSS1](https://www.luogu.org/problemnew/show/SP1043)

好像没有人详细讲猫树该如何处理区间最大子段和？我就来详细的讲一下处理方法吧qwq

这里并没有关于猫树的原理及实现，如果你没接触过猫树，请参阅[咕咕日报](https://www.luogu.org/blog/yestoday/mao-shu)

我们发现咕咕日报中的例子并没有告诉我们为什么这样做就是最大子段和了嗷……

其实是这样的qwq

我们建树的时候从**当前区间的中心出发**维护两个值，一个是普通的从中心到两端的最大子段和，一个是**包含中心节点的子段中的最大子段和**。

比如说mid是3吧，那么左侧的**包含中心节点的最大子段和**只可能在**区间3-3,2-3,1-3取到**，而普通最大子段和还可能在1-1,1-2之类的区间取到。

根据猫树的性质，我们询问区间一定会被分成两个已处理区间。

那么最大子段和可以在哪取到呢？可以在**mid的左侧，mid的右侧，和跨过mid**取到。

左右侧就是我们维护的最大子段和的最大值。

跨过mid的取值被mid分成两段，这两段都是**包含中心节点的子段中的最大子段和**，所以我们把这两段加起来，再和前面取一个最大值。

我的代码取掉了咕咕日报上的有点难懂的快读，可能对新手友好一点吧，可以看看我的代码哦qwq

```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
const int N=100010;
int n,len,l,m;
int lg[N<<2],a[N],pos[N],p[21][N],s[21][N];//他们都代表考虑到当前位置的最大子段和，p强制端点，s非强制端点
//其实非强制端点就是普通最大子段和qwq 
int read()
{
    int x=0,w=1;
    char ch; ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*w;
}
int max(int a,int b){return a>b?a:b;}
void build(int l,int r,int k,int d)
{
	if(l==r)
	{
		pos[l]=k;//记录这个位置的编号
		return; 
	}
	int f1,f2;//端点，非端点 
	int mid=(l+r)>>1;
	p[d][mid]=s[d][mid]=f1=f2=a[mid];
	f2=max(f2,0);
	for(int i=mid-1;i>=l;i--)
	{
		f1+=a[i],f2+=a[i];
		p[d][i]=max(p[d][i+1],f1);
		s[d][i]=max(s[d][i+1],f2);
		f2=max(f2,0);
	}
	p[d][mid+1]=s[d][mid+1]=f1=f2=a[mid+1];
	f2=max(f2,0);
	for(int i=mid+2;i<=r;i++)
	{
		f1+=a[i],f2+=a[i];
		p[d][i]=max(p[d][i-1],f1);
		s[d][i]=max(s[d][i-1],f2);
		f2=max(f2,0);
	}
	build(l,mid,k<<1,d+1);
	build(mid+1,r,k<<1|1,d+1);
	return;
}
int query(int x,int y)
{
	if(x==y) return a[x];
	int d=lg[pos[x]]-lg[pos[x]^pos[y]];
	return max(max(s[d][x],s[d][y]),p[d][x]+p[d][y]);
}
int main()
{
	int x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	 a[i]=read();
	for(len=2;len<n;len<<=1);//是取区间长度喵
	l=len<<1;//是节点个数喵
	for(int i=2;i<=l;i++)
	 lg[i]=lg[i>>1]+1;
	build(1,len,1,1);
	m=read();
	while(m--)
	{
		x=read();y=read();
		printf("%d\n",query(x,y));
	}
	return 0;
}
```


------------
后记：

不知道是谁给这个数据结构命名的，不过真是太可爱了。

---

## 作者：Azazеl (赞：7)

>题目传送门: [$SP1043$](https://www.luogu.com.cn/problem/SP1043)    

题意:给出了序列以及$m$组询问，求每组询问区间内的最大子段和.  

首先，$GSS$全是数据结构题，因此我们不会去用之前$O(n)$的方法查询，因为这样在最坏情况下时间会退化为$O(nm)$  

否决了$O(nm)$的做法之后，再考虑数据结构的话，线段树就是一个不错的选择了.  

但是这颗线段树需要维护些什么呢，我们来具体分析一下。  

目标是最大子段和，我们以根节点与左右子节点的$push\_up$关系来加以阐明,查询也就没什么区别了  

对于一个大区间的最大子段和(记为$dat$),它无非有三种情况:  
1. 它就是左区间的最大子段和(一定在左区间)  
2. 它就是右区间的最大子段和(一定在右区间)  
3. 它横跨左右两个区间  

这三种情况取最大值即可。对于前两种情况,我们很好维护，但第三种呢?  
举个例子:
```
2 -4 3 1    -2 4 3 1
```  
这个区间的最大子段和是$[3,8]$,对于横跨两边的最大子段和，毋庸置疑的是它一定包括:**左区间的右端点和右区间的左端点**。此后的一切都是它根据这个延伸出来的。比如在上面的例子中，我们将左区间的$1$再扩展到$3\ 1$,将右区间的$-2$扩展到$-2\ 4\ 3\ 1$

再继续观察，我们可以发现:  
*  对于左区间,它的延伸区间一定是以右端点为终止点的最大子段和.($lmaxn$)  
*  对于右区间,它的延伸区间一定是以左端点为起始点的最大子段和.($rmaxn$)  

所以我们的线段树再维护一个$lmaxn$和$rmaxn$,那我们又怎么求出每个区间的$lmaxn$和$rmaxn$呢.还是举两个例子  

```
2 4 -3 5  2 -3 1 2
```  
对于这一个区间,它的$lmaxn$是$[1,5]$  

```
2 4 -9 5 2 -3 1 2
```  
对于这一个区间,它的$lmaxn$是$[1,2]$  

多举几个例子，很容易看出:  
* $lmaxn$要么就是左区间的$lmaxn$,要么就是整个左区间加上右区间的$lmaxn$  
* $rmaxn$要么就是右区间的$rmaxn$,要么就是整个右区间加上左区间的$rmaxn$  
至于这个结论为什么成立，读者自证.  

到这里，我们就能够明确地看到，这个线段树要维护$4$个信息:$dat,lmaxn,rmaxn,sum$ ，更新方式为:  
$$\texttt{tr[p].dat=max\{tr[p<<1].dat,tr[p<<1|1].dat,tr[p<<1].rmaxn+tr[p<<1|1].lmaxn\}}$$

$$\texttt{tr[p].lmaxn=max\{tr[p<<1].lmaxn,tr[p<<1].sum+tr[p<<1|1].lmaxn\}}$$  

$$\texttt{tr[p].rmaxn=max\{tr[p<<1|1].rmaxn,tr[p<<1|1].sum+tr[p<<1].rmaxn\}}$$  

$$\texttt{tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum}$$  

查询时也以此类推，即可求出最大子段和。  

[$\mathcal{CODE}$](https://www.luogu.com.cn/paste/bl26t9vc)

---

## 作者：xsI666 (赞：5)

### 题意翻译

给出了序列 $A[1],A[2],…,A[n](a[i]≤15007,1≤N≤50000)$。

查询定义如下： 查询 $(x,y)=\max\{a[i]+a[i+1]+...+a[j];x≤i≤j≤y\}$。 

给定$M$个查询，程序必须输出这些查询的结果，每行一个查询。

### 题解

$SPOJ$的$GSS$系列一共有$8$题，这$8$道题目都是有关数据结构的，与$Ynoi$类似。

这是$SPOJ$的$GSS$系列的**第一题**，考察的是用线段树求区间最大子段和 ~~(本蒟蒻不会猫树)~~ 。

众所周知，线段树有以下基本的$3$个操作：$pushup$、$bulid$和$getans$，这$3$个操作分别对应合并区间、建树的求答案。

我们尝试用这三种操作解决这道题：

首先，我们定义一个结构体：
```cpp
struct Node
{
	int sum, lans, rans, ans;
} t[50005 << 2];
```

其中，$sum$表示区间和，$lans$表示最大前缀和，$rans$表示最大后缀和，$ans$表示区间内的最大子段和，我们的目标是求出$x$~$y$区间内的$ans$。

然后，我们分析，如何进行$pushup$操作。

易知，这个区间内的区间和就是它子区间的和加上它右子区间的和。

区间最大前缀和是它左子区间最大子段和,与左子区间和加上右子区间的最大前缀和的最大值，最大后缀和同理。

考虑如何合并区间最大子段和？

经过分析，我们得出：区间最大子段和就是$max($左子区间的最大子段和,右子区间的最大子段和,
左子区间的最大后缀+右子区间的最大前缀和$)$。

综上，我们就得出了$pushup$的代码：
```cpp
inline void pushup(int x)
{
	t[x].sum = t[x << 1].sum + t[(x << 1) | 1].sum;//求出区间和
	t[x].lans = max(t[x << 1].lans, t[x << 1].sum + t[(x << 1) | 1].lans);//区间最大前缀和
	t[x].rans = max(t[(x << 1) | 1].rans, t[(x << 1) | 1].sum + t[x << 1].rans);//区间最大后缀和
	t[x].ans = max(max(t[x << 1].ans, t[(x << 1) | 1].ans), t[x << 1].rans + t[(x << 1) | 1].lans);//区间最大子段和
}
```

$build$操作与普通线段树的$build$操作一模一样。

下面放出$build$操作的代码：
```cpp
void bulid(int s, int o, int p)
{
	if (s == o)//已经是叶子节点
	{
		t[p].sum = t[p].lans = t[p].rans = t[p].ans = gi();//输入并初始化叶子节点的成员
		return;
	}
	int mid = (s + o) >> 1;//找出区间中点
	bulid(s, mid, p << 1);//递归左子区间
	bulid(mid + 1, o, (p << 1) | 1);//递归右子区间
	pushup(p);//合并区间
}
```

$getans$操作同理。

下面放出$AC$代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

inline int gi()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

int n, m;
struct Node
{
	int sum, lans, rans, ans;
} t[50005 << 2];

inline void pushup(int x)//合并操作
{
	t[x].sum = t[x << 1].sum + t[(x << 1) | 1].sum;
	t[x].lans = max(t[x << 1].lans, t[x << 1].sum + t[(x << 1) | 1].lans);
	t[x].rans = max(t[(x << 1) | 1].rans, t[(x << 1) | 1].sum + t[x << 1].rans);
	t[x].ans = max(max(t[x << 1].ans, t[(x << 1) | 1].ans), t[x << 1].rans + t[(x << 1) | 1].lans);
}

void bulid(int s, int o, int p)//建树
{
	if (s == o)
	{
		t[p].sum = t[p].lans = t[p].rans = t[p].ans = gi();
		return;
	}
	int mid = (s + o) >> 1;
	bulid(s, mid, p << 1);
	bulid(mid + 1, o, (p << 1) | 1);
	pushup(p);
}

Node getans(int l, int r, int s, int o, int p)//求答案
{
	if (l <= s && r >= o)//如果包含区间
	{
		return t[p];//就直接返回
	}
	int mid = (s + o) >> 1;//求出中点
	if (l > mid) return getans(l, r, mid + 1, o, (p << 1) | 1);//如果左端点在中点右边，就递归右区间
	if (r <= mid) return getans(l, r, s, mid, p << 1);//如果右端点在中点左边，就递归左区间
	else 
	{
		Node ans, a, b;
		a = getans(l, r, s, mid, p << 1), b = getans(l, r, mid + 1, o, (p << 1) | 1);//求出左区间和右区间的各项参数
		ans.sum = a.sum + b.sum;
		ans.ans = max(max(a.ans, a.rans + b.lans), b.ans);
		ans.lans = max(a.lans, a.sum + b.lans);
		ans.rans = max(b.rans, b.sum + a.rans);//合并答案
		return ans;//最后返回答案
	}
}

int main()//进入主函数
{
	n = gi();//输入节点个数
	bulid(1, n, 1);//建树
	m = gi();//输入询问个数
	for (int i = 1; i <= m; i++)
	{
		int x = gi(), y = gi();
		printf("%d\n", getans(x, y, 1, n, 1).ans);//求出答案
	}
	return 0;//结束
}
```

---

## 作者：xiezheyuan (赞：4)

## 简要题意

给你一个长度为 $n$ 的序列 $a$，$q$ 次询问，每次询问给出一个区间 $[l,r]$，求区间的最大子段和。

$1\leq n,q\leq 5\times10^4$

## 思路

翻了翻题解区没有动态 dp 的做法，所以在此给一个动态 dp 的做法供参考，这也是我做的第一道动态 dp 题。

首先考虑一个朴素的问题：

> 给出一个序列 $a$，求出它的最大子段和。

对于这个问题，我们可以朴素的 dp，设 $f_i$ 表示以 $i$ 结尾的最大子段和，$g_i$ 表示 $f_i$ 的前缀最大值，则答案就是 $g_i$。

转移是容易的：$f_i=\max(f_{i-1}+a_i,a_i),g_i=\max(f_i,g_{i-1})$。

然后我们考虑构造转移矩阵，大概长这样：

$$
F_i=\begin{bmatrix}
F_{11}&F_{12}&F_{13}\\
F_{21}&F_{22}&F_{23}\\
F_{31}&F_{32}&F_{33}
\end{bmatrix}
$$

需要满足

$$
F_i\times\begin{bmatrix}
f_{i-1}\\
g_{i-1}\\
0 
\end{bmatrix}=\begin{bmatrix}
f_{i}\\
g_{i}\\
0 
\end{bmatrix}
$$

注意这里的乘法是指 $(\max,+)$ 的广义矩阵乘法。

然后我们考虑构造，首先构造第一行：

- 由于需要有 $f_{i-1}+a_i$ 一项，所以 $F_{11} = a_i$。
- 由于需要有 $a_i$ 一项，所以 $F_{13}=a_i$。

然后考虑第二行，发现 $g_i$ 是一个前缀最大值的形式不便和 $f$ 一起转移。将 $g_i$ 中的 $f_i$ 拆掉，得 $\max(f_{i-1}+a_i,a_i,g_{i-1})$：

- 由于需要有 $f_{i-1}+a_i$ 一项，所以 $F_{21}=a_i$。
- 由于需要有 $g_{i-1}$ 一项，所以 $F_{22}=0$。
- 由于需要有 $a_i$ 一项，所以 $F_{23}=a_i$。

最后考虑第三行，只需要令 $F_{33}=0$ 即可。

其余的位置不参与转移，填 $-\infty$ 即可。

所以得到：

$$
F_i=\begin{bmatrix}
a_i&-\infty&a_i\\
a_i&0&a_i\\
-\infty&-\infty&0
\end{bmatrix}
$$

我们考虑如何递推，考察 $F_i$ 定义式发现后面是一个尾递归（这个词可能不太严谨，理解即可）的形式，边界在 $F_l$，所以答案就是：

$$
\left(\prod_{k=l+1}^{r}F_k\right)\begin{bmatrix}
a_l\\0
\end{bmatrix}
$$

由于广义矩阵乘法具有结合律，所以我们可以用线段树来维护上面那个求积式。

时间复杂度 $O(n+q\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (i<<1)
#define rs (i<<1|1)
#define mid ((l+r)>>1)
using namespace std;

const int N = 1e5+5;
int n,q,a[N];

struct matrix{
    int n,m,a[4][4];
    int* operator[](int x){return this->a[x];}
    explicit matrix(int N = 0, int M = 0) : n(N), m(M) {};
    void clear(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) a[i][j] = INT_MIN;
        }
    }
    void output(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) cout<<a[i][j]<<' ';
            cout<<'\n';
        }
    }
};

matrix bdmtx(int i){
    matrix ans(3, 3);
    ans[1][1] = ans[1][3] = ans[2][1] = ans[2][3] = a[i];
    ans[1][2] = ans[3][1] = ans[3][2] = INT_MIN;
    ans[2][2] = ans[3][3] = 0;
    return ans;
}

matrix operator*(matrix a,matrix b){
    matrix c(a.n, b.m);
    assert(a.m == b.n);
    c.clear();
    for(int k=1;k<=a.m;k++){
        for(int i=1;i<=a.n;i++){
            for(int j=1;j<=b.m;j++) c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
        }
    }
    return c;
}

matrix t[N<<2];

void build(int i, int l, int r){
    if(l == r){
        cin>>a[l];
        t[i] = bdmtx(l);
        return; 
    }
    build(ls, l, mid);build(rs, mid + 1, r);
    t[i] = t[rs] * t[ls];
}

matrix query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr){
        // cout<<"Range: "<<l<<' '<<r<<'\n';
        // t[i].output();
        return t[i];
    }
    if(ql <= mid && !(qr > mid)) return query(ql, qr, ls, l, mid);
    if(qr > mid && !(ql <= mid)) return query(ql, qr, rs, mid + 1, r);
    return query(ql, qr, rs, mid + 1, r) * query(ql, qr, ls, l, mid);
}

int bf(int l, int r){
    if(l == r) return a[l];
    matrix ans(3, 1);
    ans.clear();
    ans[1][1] = ans[2][1] = a[l], ans[3][1] = 0;
    for(int i=l+1;i<=r;i++) ans = bdmtx(i) * ans;
    return (ans)[2][1];
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    build(1, 1, n);
    cin>>q;
    while(q--){
        int l,r;
        cin>>l>>r;
        if(l == r){
            cout<<a[l]<<'\n';
            continue;
        }
        matrix ans;
        ans.n = 3, ans.m = 1;
        ans[1][1] = ans[2][1] = a[l], ans[3][1] = 0;
        ans = query(l + 1, r, 1, 1, n) * ans;
        cout<<ans[2][1]<<'\n';
    }
    return 0;
}
```

---

## 作者：hyfhaha (赞：3)

# 开坑啦！
2019 3/28 以前一直不知道怎么搞最大子段和，如今终于可以学习，其实真的很简单啊。

## 前置技能：线段树
题目大意：询问区间[l,r]的最大字段和

定义：
```cpp
struct kkk{
    int val;	//表示该区间的权值和
    int left;	//表示该区间的前缀最大和
    int right;	//表示该区间的后缀最大和
    int middle;	//表示该区间的最大子段和
    kkk(){val=left=right=middle=0;} //清0
}tree[maxn];
```
大家都应知道，线段树基本原理，那么最大子段和放在线段树上，其实就是两个区间的合并时怎么将区间关系，pushup区间的问题。

下面给出两个区间合并的方式：合并的区间为res

合并保证x是左区间，y是右区间，x，y相邻。

首先是val的合并，很简单，区间x的val+区间y的val
```cpp
res.val=x.val+y.val;
```
然后是left的合并，前缀最大和只有两种情况，要么是x区间的前缀最大和，要么是x的权值和+y的前缀最大和。结果是这两种情况的max值。证明：贪心。

那么right的合并也差不多，要么是y区间的后缀最大和，要么是y的权值+x的后缀最大和。

至于middle就分几种情况：
```cpp
1.x区间的middle
2.y区间的middle
3.x区间的后缀最大和+y区间的前缀最大和
```

代码实现合并操作：
```cpp
kkk merge(kkk x,kkk y){
    kkk res;
    res.val=x.val+y.val;
    res.middle=max(
    		   max(x.middle,y.middle),
    		   x.right+y.left
    		   );
    res.left=max(x.left,x.val+y.left);
    res.right=max(y.right,y.val+x.right);
    return res;
}
```
那么pushup操作即是将左儿子和右儿子合并。

### 查询操作
我们查询时返回一个区间，这个区间在查询时会合并成我们想要查询的那个区间，那么那个区间的middle就是我们要求的答案。

```cpp
kkk query(int node,int begin,int end,int x,int y){
    if(begin>=x&&end<=y)return tree[node];		//包含该区间，直接返回
    int mid=(begin+end)>>1;
    kkk Left,Right,res;
    if(x<=mid) Left=query(L(node),begin,mid,x,y);	//查询左区间
    if(y>mid) Right=query(R(node),mid+1,end,x,y);	//查询右区间
    return merge(Left,Right);				//合并成一个区间
}
```
经过思考，我们会发现Left和Right决不是返回整个区间，而是我们要求的区间在Left或Right区间的部分。所以我们可以直接将Left和Right区间合并。

最后输出的就是查询到区间的middle
```cpp
printf("%d\n",query(1,1,n,x,y).middle);
```

下面放完整代码：
```cpp
#include<bits/stdc++.h>
#define maxn 1000001
#define L(node) (node<<1)
#define R(node) ((node<<1)|1)
using namespace std;
struct kkk{
    int val,left,right,middle;
    kkk(){val=left=right=middle=0;}
}tree[maxn];
int n,m,x,y,a[maxn];
kkk merge(kkk x,kkk y){
    kkk res;
    res.val=x.val+y.val;
    res.middle=max(max(x.middle,y.middle),x.right+y.left);
    res.left=max(x.left,x.val+y.left);
    res.right=max(y.right,y.val+x.right);
    return res;
}
void build(int node,int begin,int end){
    if(begin==end){
        tree[node].val=tree[node].left=tree[node].right=tree[node].middle=a[begin];
        return ;
    }else{
        int mid=(begin+end)>>1;
        build(L(node),begin,mid);
        build(R(node),mid+1,end);
        tree[node]=merge(tree[L(node)],tree[R(node)]);
    }
}
kkk query(int node,int begin,int end,int x,int y){
    if(begin>=x&&end<=y)return tree[node];		//包含该区间，直接返回
    int mid=(begin+end)>>1;
    if(y<=mid) return query(L(node),begin,mid,x,y);
    if(x>mid)return query(R(node),mid+1,end,x,y);
    kkk Left,Right;
    if(x<=mid) Left=query(L(node),begin,mid,x,y);	//查询左区间
    if(y>mid) Right=query(R(node),mid+1,end,x,y);	//查询右区间
    return merge(Left,Right);				//合并成一个区间
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        printf("%d\n",query(1,1,n,x,y).middle);
    }
}
```

# 谢谢观赏

---

## 作者：VenusM1nT (赞：3)

平衡树。和 `P2710 数列` 做法相似，但是少了很多操作，正解线段树，不过平衡树也可以做，速度慢了一截，但是借这份代码轻松地通过 `GSS3` 和 `GSS6`。

依然选用 $\text{FHQ Treap}$。其中的 $cov$ 和 $rev$ 是区间覆盖和反转的标记，这题用不到，$cov$ 在之后有用到，但 $rev$ 就完全没用了，忽略即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2e9
#define MAXN 500005
using namespace std;
struct FHQTreap
{
	int son[2],siz,key;
	ll val,maxn,lmax,rmax,rev,sum,cov;
}t[MAXN];
queue <int> q;
int n,m,root,a[MAXN],siz,stk[MAXN],top;
template <typename T> void Read(T &x)
{
    int fu=1;
    x=0;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
    for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
    x*=fu;
}
int NewNode(ll val)
{
	int x;
	if(!q.empty())
	{
		x=q.front();
		q.pop();
	}
	else x=++siz;
	t[x].son[0]=t[x].son[1]=t[x].rev=0;
	t[x].cov=inf;
	t[x].key=rand();
	t[x].siz=1;
	t[x].val=t[x].sum=t[x].maxn=val;
	t[x].lmax=t[x].rmax=max(val,1ll*0);
	return x;
}
void Update(int x)
{
	if(t[x].son[0] && t[x].son[1])
	{
		t[x].siz=t[t[x].son[0]].siz+t[t[x].son[1]].siz+1;
		t[x].sum=t[t[x].son[0]].sum+t[t[x].son[1]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[0]].maxn,t[t[x].son[1]].maxn);
		t[x].maxn=max(t[x].maxn,t[t[x].son[0]].rmax+t[t[x].son[1]].lmax+t[x].val);	
		t[x].lmax=max(t[t[x].son[0]].lmax,t[t[x].son[0]].sum+t[t[x].son[1]].lmax+t[x].val);
		t[x].rmax=max(t[t[x].son[1]].rmax,t[t[x].son[1]].sum+t[t[x].son[0]].rmax+t[x].val);
	}
	else if(t[x].son[0])
	{
		t[x].siz=t[t[x].son[0]].siz+1;
		t[x].sum=t[t[x].son[0]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[0]].maxn,t[t[x].son[0]].rmax+t[x].val);
		t[x].lmax=max(t[t[x].son[0]].lmax,t[t[x].son[0]].sum+t[x].val);
		t[x].lmax=max(t[x].lmax,1ll*0);
		t[x].rmax=max(t[t[x].son[0]].rmax+t[x].val,1ll*0);
	}
	else if(t[x].son[1])
	{
		t[x].siz=t[t[x].son[1]].siz+1;
		t[x].sum=t[t[x].son[1]].sum+t[x].val;
		t[x].maxn=max(t[t[x].son[1]].maxn,t[t[x].son[1]].lmax+t[x].val);
		t[x].rmax=max(t[t[x].son[1]].rmax,t[t[x].son[1]].sum+t[x].val);
		t[x].rmax=max(t[x].rmax,1ll*0);
		t[x].lmax=max(t[t[x].son[1]].lmax+t[x].val,1ll*0);
	}
	else
	{
		t[x].siz=1;
		t[x].sum=t[x].maxn=t[x].val;
		t[x].lmax=t[x].rmax=max(t[x].val,1ll*0);
	}
}
void reverse(int x)
{
	swap(t[x].son[0],t[x].son[1]);
	swap(t[x].lmax,t[x].rmax);
	t[x].rev^=1;
}
void Change(int x,int val)
{
	t[x].val=val;
	t[x].sum=t[x].siz*val;
	t[x].lmax=t[x].rmax=max(t[x].sum,1ll*0);
	t[x].maxn=max(t[x].sum,t[x].val);
	t[x].cov=val;
}
void PushDown(int x)
{
	if(t[x].rev)
	{
		if(t[x].son[0]) reverse(t[x].son[0]);
		if(t[x].son[1]) reverse(t[x].son[1]);
	}
	if(t[x].cov!=inf)
	{
		if(t[x].son[0]) Change(t[x].son[0],t[x].cov);
		if(t[x].son[1]) Change(t[x].son[1],t[x].cov);
	}
	t[x].rev=0;
	t[x].cov=inf;
}
int BuildFHQTreap(int sum)
{
	memset(stk,0,sizeof(stk));
	top=0;
	int x,lat;
	for(int i=1;i<=sum;i++)
	{
		x=NewNode(a[i]);
		lat=0;
		while(top && t[stk[top]].key>t[x].key)
		{
			Update(stk[top]);
			lat=stk[top];
			stk[top--]=0;
		}
		if(top) t[stk[top]].son[1]=x;
		t[x].son[0]=lat;
		stk[++top]=x;
	}
	while(top) Update(stk[top--]);
	return stk[1];
}
int Merge(int x,int y)
{
	if(x) PushDown(x);
	if(y) PushDown(y);
	if(!x || !y) return x+y;
	if(t[x].key<t[y].key)
	{
		t[x].son[1]=Merge(t[x].son[1],y);
		Update(x);
		return x;
	}
	else
	{
		t[y].son[0]=Merge(x,t[y].son[0]);
		Update(y);
		return y;
	}
}
void Split(int rt,int pos,int &x,int &y)
{
	if(!rt) x=y=0;
	else
	{
		PushDown(rt);
		if(t[t[rt].son[0]].siz>=pos)
		{
			y=rt;
			Split(t[rt].son[0],pos,x,t[rt].son[0]);
		}
		else
		{
			x=rt;
			Split(t[rt].son[1],pos-t[t[rt].son[0]].siz-1,t[rt].son[1],y);
		}
		Update(rt);
	}
}
void GetMax()
{
	int x,y,pos,sum,ax,ay,bx,by;
	Read(x);
	Read(y);
	pos=x;
	sum=y-x+1;
	Split(root,pos-1,ax,bx);
	Split(bx,sum,ay,by);
	printf("%lld\n",t[ay].maxn);
	root=Merge(ax,Merge(ay,by));
}
int main()
{
	Read(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	root=BuildFHQTreap(n);
	Read(m);
	while(m--) GetMax();
	return 0;
}
```

---

## 作者：顾z (赞：3)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

### 前言

线段树维护最大子段和裸题.

~~直接把我的另一篇博客粘过来~~

### 定义数组

$lsum[ ]$代表 该区间左端点开始的最大连续和.

$rsum[ ]$代表 该区间右端点开始的最大连续和.

$ssum[ ]$代表 区间内最大连续和.

$sum[ ]$ 代表区间和.

### Que and A

#### Q:已知一个区间的左右区间的最大连续和,如何合并?

#### A:这个区间的最大连续和要么是左子区间的最大连续和,要么是右子区间的最大连续和.

#### 要么是左子区间的最大右起子段和+右子区间的最大左起字段和.

 ``code``：$ssum[o]=max(max(ssum[lson],ssum[rson]),rsum[lson]+lsum[rson])$

#### Q:如何更新区间最大左起子段和.

#### A:新区间的最大左起子段和.要么是其左子区间最大连续和,要么是其左子区间和+右子区间的左起子段和.

**最大右起子段和同理**

``code``：$lsum[o]=max(lsum[lson],sum[lson]+lsum[rson])$

　　　　  $rsum[o]=max(rsum[rson],sum[rson]+rsum[lson])$

更新操作类似单点修改

代码中是结构体写法.

当两端不在左子节点或者右子节点的话,需要考虑合并的

``代码``

```c++
#include<cstdio>
#include<iostream>
#include<cctype>
#define ls o<<1
#define rs o<<1|1
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
struct cod{int l,r,lsum,rsum,sum,ssum;}tr[50008*40];
inline void up(int o)
{
	tr[o].sum=tr[ls].sum+tr[rs].sum;
	tr[o].ssum=max(max(tr[ls].ssum,tr[rs].ssum),tr[ls].rsum+tr[rs].lsum);
	tr[o].lsum=max(tr[ls].lsum,tr[ls].sum+tr[rs].lsum);
	tr[o].rsum=max(tr[rs].rsum,tr[ls].rsum+tr[rs].sum);
}
void build(int o,int l,int r)
{
	tr[o].l=l;tr[o].r=r;
	if(l==r)
	{
		in(tr[o].sum);
		tr[o].lsum=tr[o].rsum=tr[o].ssum=tr[o].sum;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(o);
}
cod query(int o,int x,int y)
{
	if(tr[o].l>=x and y>=tr[o].r) return tr[o];
	int mid=(tr[o].l+tr[o].r)>>1;
	if(y<=mid) return query(ls,x,y);
	if(x>mid) return query(rs,x,y);
	else
	{
		cod t,t1=query(ls,x,y),t2=query(rs,x,y);
		t.lsum=max(t1.lsum,t1.sum+t2.lsum);
		t.rsum=max(t2.rsum,t2.sum+t1.rsum);
		t.ssum=max(max(t1.ssum,t2.ssum),t1.rsum+t2.lsum);
		return t;
	}
}
int n,m;
int main()
{
	in(n);
	build(1,1,n);
	in(m);
	for(R int l,r;m;m--)
	{
		in(l),in(r);
		if(l>r)swap(l,r);
		printf("%d\n",query(1,l,r).ssum);
	}
}
```



---

## 作者：封禁用户 (赞：2)

# 思路

首先思考一下如何扩展 $l$ 与 $r$ 指针。

* 对于扩展 $l$，发现新的 $l$ 指针 $l_{new}$ 可以贡献的答案为 $\max\limits_{j=l_{new}}^{r} \sum\limits ^{j}_{k=l_{new}} a_k$，形象化一下就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/vgn1eobt.png)

* 对于扩展 $r$，发现新的 $r$ 指针 $r_{new}$ 可以贡献的答案为 $\max\limits _{j=l}^{r_{new}}\sum\limits_{k=j}^{r_{new}} a_k $，形象化一下就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/t8n4744s.png)

~~（画的有点抽象，一点也不形象。）~~

仅仅这样显然无法通过，我们令 $s(l,r) = \sum\limits _{i=l}^r a_i$，然后将扩展 $l$ 指针的式子提出来看一看：

$$\max\limits_{j=l_{new}}^{r} s(l_{new},j)$$

用前缀和思想简化式子：

$$\max\limits_{j=l_{new}}^{r} (s(1,j)-s(1,l_{new}-1))$$

然后发现这个 $s(1,l_{new}-1)$ 可以提到外面去，即：

$$(\max\limits_{j=l_{new}}^{r} s(1,j))-s(1,l_{new}-1)$$

对于这个问题，显然可以用 ST 表预处理前缀和数组的区间最大值，然后就 $O(1)$ 了。

对于 $r$ 同理，再处理一个后缀和数组的区间最大值。

使用回滚莫队，时间复杂度为 $O(n\log n+n\sqrt m)$。

# Code

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define inf 0x3f3f3f3f
#define linf 1e18
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define umap(x,y) sd unordered_map<x,y>
#define pque(x) sd priority_queue<x>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=2e5+10,M=25;
int n,q,t,siz,lg[N],las_ma[N][M],fir_ma[N][M],a[N],las[N],fir[N],L[N],R[N],pos[N],ans[N];
struct query
{
	int l,r;
	int id;
}Q[N];
int cmp(query A,query B)
{
	return pos[A.l]==pos[B.l]?A.r<B.r:pos[A.l]<pos[B.l];
}
il void init()//预处理ST表 
{
	f(i,n,1) las[i]=las[i+1]+a[i];
	me(las_ma,-inf),me(fir_ma,-inf);
	F(i,1,n) las_ma[i][0]=las[i],fir_ma[i][0]=fir[i];
	F(i,2,n) lg[i]=lg[i/2]+1;
	F(i,1,20) for(int j=1;j+(1<<i)-1<=n;j++) las_ma[j][i]=MAX(las_ma[j][i-1],las_ma[j+(1<<(i-1))][i-1]),fir_ma[j][i]=MAX(fir_ma[j][i-1],fir_ma[j+(1<<(i-1))][i-1]);
}
int que(int l,int r,int flag)//flag=1:fir,else las
{
	int s=lg[r-l+1];
	return flag?MAX(fir_ma[l][s],fir_ma[r-(1<<s)+1][s]):MAX(las_ma[l][s],las_ma[r-(1<<s)+1][s]);
}
int Ans=-inf,tmp=-inf;
il void add_l(int x,int r){if(x<=r) tmp=MAX(tmp,que(x,r,1)-fir[x-1]);}//伸展左端点 
il void add_r(int x,int l){if(l<=x) Ans=MAX(Ans,que(l,x,0)-las[x+1]);}//伸展右端点 
int main()
{
	n=read();
	F(i,1,n) a[i]=read(),fir[i]=fir[i-1]+a[i];
	init();
	
	q=read();
	F(i,1,q) Q[i].l=read(),Q[i].r=read(),Q[i].id=i;
	t=sqrt(n);
	siz=n/t;
	F(i,1,siz) L[i]=(i-1)*t+1,R[i]=i*t;
	if(R[siz]<n)
	{
		++siz;
		L[siz]=R[siz-1]+1;
		R[siz]=n;
	}
	F(i,1,siz) F(j,L[i],R[i]) pos[j]=i;
	sd sort(Q+1,Q+1+q,cmp);
	int l=1,r=0,lb=0,tmpl;
	F(i,1,q)
	{
		if(pos[Q[i].l]==pos[Q[i].r])//一个块，直接处理，用线性做法 
		{
			int ANS=-inf,b=-inf;
			F(j,Q[i].l,Q[i].r)
			{
				if(j==Q[i].l) b=a[j];
				else b=MAX(a[j],a[j]+b);
				ANS=MAX(ANS,b);
			}
			ans[Q[i].id]=ANS;
			continue;
		}
		if(pos[Q[i].l]!=lb)
		{
			while(r>R[pos[Q[i].l]]) --r;
			while(l<R[pos[Q[i].l]]+1) ++l;
			Ans=-inf;
			lb=pos[Q[i].l];
		}
		while(r<Q[i].r) ++r,add_r(r,l);
		tmpl=l;
		tmp=Ans;
		while(tmpl>Q[i].l) --tmpl,add_l(tmpl,r);
		ans[Q[i].id]=tmp;
	}
	F(i,1,q) put(ans[i]);
    return 0;
}
```

---

## 作者：juicyyou (赞：2)

# GSS1 - Can you answer these queries I

## 题目大意

>给定长度为 n 的一个序列 $ $ $ a_{1} $, $ a_{2} $ ... $ a_{n} $
和 q 次询问。
>
>每次询问输入一对 $ (l, r) $ , 求 $ a_{l} $, $ a_{l + 1} $ ... $ a_{r} $的最大子段和。
>
> $ n \le 50000 $ , $ a_{i} \le 15007 $

## 解题方法

看到这样的题，首先想到的是DP暴力处理每一次询问，复杂度 $ O(nq) $，显然会TLE，考虑其他做法。

既然是区间查询，考虑使用线段树来维护。

设线段树上的一个节点 $ p $ 表示区间 $ [l, r] $，我们考虑维护这几个值：

> $ l_{p} $，表示区间最大前缀和。
>
> $ r_{p} $，表示区间最大后缀和。
>
> $ s_{p} $，表示区间最大子段和。
>
> $ f_{p} $，表示区间和。

接着考虑如何维护。

首先，若 $ l = r $，则 $ l_{p} = r_{p} = s_{p} = f_{p} = a_{l} $。

其次，若 $ l \neq r $，则 ：

$ l_{p} = max( $ $ l_{lc(p)},$  $ $ $  f_{lc(p)} + l_{rc(p)} $ $) $

$ r_{p} = max( $ $ r_{rc(p)},$  $ $ $  f_{rc(p)} + r_{lc(p)} $ $) $

$ s_{p} = max( $ $ s_{lc(p)} $ $ , $ $ s_{rc(p)} $ $,$ $ r_{lc(p)} + 
l_{rc(p)}$ $ ) $

$ f_{p} = f_{lc(p)} + f_{rc(p)}$

其中 $ lc(p) $ 表示 $ p $ 的左子节点，$ rc(p) $ 表示 $ p $ 的右子节点。

有了上述公式，相信大家一定会写这道题了。下面放出本蒟蒻的代码：

```cpp
#include<iostream>
#include<cctype>
#include<cstdio>
using namespace std;
typedef long long LL;
LL a[50005];
LL f[50005];   // 前缀和
LL s1[150005]; // 最大前缀和 
LL s2[150005]; // 最大后缀和 
LL s3[150005]; // 最大子段和 
inline LL qread(){ // 快读 
    LL x = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-'){
            f = -f;
        }
        ch = getchar();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
inline LL lc(LL p){ // p的左子节点 
    return (p << 1);
}
inline LL rc(LL p){ // p的右子节点 
    return (p << 1 ^ 1);
}
inline void pushup(LL p, LL l, LL r){ // 维护 
    LL m = ((l + r) >> 1);
    s1[p] = max(f[m] - f[l - 1] + s1[rc(p)], s1[lc(p)]);
    s2[p] = max(f[r] - f[m] + s2[lc(p)], s2[rc(p)]);
    s3[p] = max(s3[lc(p)], max(s3[rc(p)], s2[lc(p)] + s1[rc(p)]));
    return ;
}
inline void build(LL p, LL l, LL r){ // 建树 
    if(l == r){
        s1[p] = a[l];
        s2[p] = a[l];
        s3[p] = a[l];
        return ;
    }
    LL m = ((l + r) >> 1);
    build(lc(p), l, m);
    build(rc(p), m + 1, r);
    pushup(p, l, r);
    return ;
}
inline LL query1(LL pl, LL pr, LL l, LL r, LL p){ // 查询区间最大前缀和 
    LL ress;
    if(pl <= l && r <= pr){
        return s1[p];
    }
    LL m = ((l + r) >> 1);
    if(pl <= m && pr > m){
        ress = max(f[m] - f[pl - 1] + query1(m + 1, pr, m + 1, r, rc(p)), 
                   query1(pl, m, l, m, lc(p)));
        return ress;
    }
    if(pl <= m){
        ress = query1(pl, pr, l, m, lc(p));
    }
    if(pr > m){
        ress = query1(pl, pr, m + 1, r, rc(p));
    }
    return ress;
}
inline LL query2(LL pl, LL pr, LL l, LL r, LL p){ // 查询区间最大后缀和 
    LL ress;
    if(pl <= l && r <= pr){
        return s2[p];
    }
    LL m = ((l + r) >> 1);
    if(pl <= m && pr > m){
        ress = max(f[r] - f[m] + query2(pl, m, l, m, lc(p)), 
                   query2(m + 1, pr, m + 1, r, rc(p)));
        return ress;
    }
    if(pl <= m){
        ress = query2(pl, pr, l, m, lc(p));
    }
    if(pr > m){
        ress = query2(pl, pr, m + 1, r, rc(p));
    }
    return ress;
}
inline LL query3(LL pl, LL pr, LL l, LL r, LL p){ // 查询区间最大子段和 
    LL ress;
    if(pl <= l && r <= pr){
        return s3[p];
    }
    LL m = ((l + r) >> 1);
    if(pl <= m && pr > m){
        ress = max(query3(pl, m, l, m, lc(p)), 
                   max(query3(m + 1, pr, m + 1, r, rc(p)), 
                   query2(pl, m, l, m, lc(p)) + query1(m + 1, pr, m + 1, r, rc(p))));
        return ress;
    }
    if(pl <= m){
        ress = query3(pl, pr, l, m, lc(p));
    }
    if(pr > m){
        ress = query3(pl, pr, m + 1, r, rc(p));
    }
    return ress;
}
int main(){
    LL n;
    n = qread();
    for(int i = 1;i <= n;i++){
        a[i] = qread();
    }
    for(int i = 1;i <= n;i++){ // 预处理前缀和 
        f[i] = a[i] + f[i - 1];
    }
    build(1, 1, n);
    LL m;
    m = qread();
    while(m--){
        LL x, y;
        cin >> x >> y;
        cout << query3(x, y, 1, n, 1) << endl;
    }
    return 0;
}
```

此算法复杂度 $ O(q log n) $，足以通过此题。

感谢大家的支持。

---

## 作者：晨曦_ (赞：2)

```cpp
#include<bits/stdc++.h>
#define maxn 50001
using namespace std;
inline int read()//M大佬的快读
{
    int res,f=1;
    char c;
    while((c=getchar())<'0'||c>'9')
        if(c=='-')f=-1;
    res=c-48;
    while((c=getchar())>='0'&&c<='9')
        res=res*10+c-48;
    return res*f;   
}
int n,m;
int a[maxn];
struct node{
	int l,r;
	int sum,la,ra,ans;//区间和，左起连续最大值，右起连续最大值和区间连续最大值
}t[maxn*4];//大树
void push(int x)
{
	t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
	t[x].la=max(t[x<<1].la,t[x<<1].sum+t[x<<1|1].la);
	t[x].ra=max(t[x<<1|1].ra,t[x<<1|1].sum+t[x<<1].ra);
	t[x].ans=max(max(t[x<<1].ans,t[x<<1|1].ans),t[x<<1].ra+t[x<<1|1].la);
}//偷懒函数  每次操作后进行 用来建树
void build(int x,int l,int r)
{
	t[x].l=l;t[x].r=r;//lyd大佬的格式
	if(l==r)
	{
		t[x].la=t[x].ra=t[x].ans=t[x].sum=a[l];//初始化
		return ;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	push(x);
}
node chaxun1(int x,int s,int e)//全程序最重要的地方！！
{
	int l=t[x].l;
	int r=t[x].r;
	if(l==s&&e==r) return t[x];//如果为所要查找的区间 那么返回
	int mid=(l+r)>>1;
	if(e<=mid) return chaxun(x<<1,s,e);//如果左子树区间的和目标区间有交集 那么搜索
	else if(s>mid) return chaxun(x<<1|1,s,e);//同上
	else{
		node left,right,re;
		left=chaxun(x<<1,s,mid);//分割区间
		right=chaxun(x<<1|1,mid+1,e);
		re.sum=left.sum+right.sum;
		re.la=max(left.la,left.sum+right.la);
		re.ra=max(right.ra,right.sum+left.ra);
		re.ans=max(max(left.ans,right.ans),left.ra+right.la);
		return re;
        //如果没有 那么 进行秘制操作
        //建立 一个答案 一个向左 一个向右的类似物
        //结束后就合并区间
        //最后返回 答案 
        //这里要思考！
	}
}
//其实总共有2种写法 下面是第2种
node chaxun2(int x,int s,int e)
{
 	int l=t[x].l;
	int r=t[x].r;
	if(l>=s&&r<=e) return t[x];//如果为所要查找的区间 那么返回
	int mid=(l+r)>>1;
	if(e<=mid) return chaxun(x<<1,s,e);
	else if(s>mid) return chaxun(x<<1|1,s,e);
	else{
		node left,right,re;
		left=chaxun(x<<1,s,e);
		right=chaxun(x<<1|1,s,e);
		re.sum=left.sum+right.sum;
		re.la=max(left.la,left.sum+right.la);
		re.ra=max(right.ra,right.sum+left.ra);
		re.ans=max(max(left.ans,right.ans),left.ra+right.la);
		return re;
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	build(1,1,n);
	m=read();
	for(int i=1,q,w;i<=m;i++)
	{
		q=read();w=read();
		printf("%d\n",chaxun1(1,q,w).ans);
	}
	return 0;
}
```
想了好长时间 然后被**大犇蹂躏** 懵逼 然后过来写一个博客
其实这题是一个动态查询，要维护的主要有左边连续的最大值和右边连续的最大值以及整个区间的连续最大值和正常的区间和（区间和用来合并区间和建树用）
~~只要维护好这几个就可以无脑了~~但实际上并不是这样——这个程序最最主要的是查询——你需要定义的不是一个简单的返回答案，而是返回一个结构体的最终答案！

------------
ps：还是有好几个地方不明白 还是想问一下connect和Meatherm两个神仙 我还是太菜了 线段树复杂度的证明都一知半解 希望自己可以再努力一点.......加油....嗯！


---

## 作者：唔啊唔 (赞：2)

此篇为本人第一篇紫题题解（有一点小紧张,怕讲不太好）

此题查询最大子段和是有一点难想到的。

在建树时，需要存的不只是sum(和)，l，r

还有data(最大子段和)，pre（以l为起点的，终点小于等于r的最大子段和）,suf(以r为终点的，起点大于等于l的最大子段和)

剩下的在代码中好好解释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5000000];
struct HZY{         
    int l,r;
    int pre,suf,data,sum;
}t[5000000],s;
inline void build(int l,int r,int k){
    t[k].l=l;
    t[k].r=r;
    if(l==r){   
        t[k].sum=a[l];
        t[k].pre=a[l];
        t[k].suf=a[l];
        t[k].data=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,2*k);
    build(mid+1,r,2*k+1);
//  data等于两个子节点的最长子段和与前一个子节点的后缀子段和(suf)+后一个子节点的前缀子段和(pre)中的最大值 
    t[k].data=max(t[2*k].data,t[2*k+1].data);    
    t[k].data=max(t[k].data,t[2*k].suf+t[2*k+1].pre);
//  pre等于前一个子节点的前缀子段和与前一个子节点的sum(和)+后一个子节点的前缀子段和中的最大值   
    t[k].pre=max(t[2*k].pre,t[2*k].sum+t[2*k+1].pre);
//  suf等于后一个子节点的后缀子段和与后一个子节点的sum(和)+前一个子节点的后缀子段和中的最大值 
    t[k].suf=max(t[2*k].suf+t[2*k+1].sum,t[2*k+1].suf);
    t[k].sum=t[2*k].sum+t[2*k+1].sum; 
}
int cnt;
inline void ask(int l,int r,int k){//用s将整个数列连起来(保证从前到后一次找完数列) 
    if(l<=t[k].l&&r>=t[k].r){
        if(cnt==0){ //注意特判，找到最前端的部分 
            cnt=1;
            s=t[k];
        }
        else{   //类似先前建树时的判断 
        	s.pre=max(s.pre,s.sum+t[k].pre);
            s.sum=s.sum+t[k].sum;
            s.data=max(s.data,t[k].data);
            s.data=max(s.data,s.suf+t[k].pre);
            s.suf=max(t[k].suf,s.suf+t[k].sum);
        }
        return;
    }
    int mid=(t[k].l+t[k].r)/2;
    if(l<=mid) ask(l,r,2*k);
    if(r>mid) ask(l,r,2*k+1);
}
int main(){
    cin>>n;
    for(register int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    build(1,n,1);
    cin>>m;
    int x,y;
    for(register int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        cnt=0;
        ask(x,y,1);
        printf("%d\n",s.data);
    }
    return 0;
}
```

就到这里了


谢谢大佬们的观看！！！


---

## 作者：Paranoid丶离殇 (赞：1)

题目传送门：[SP1043 GSS1 - Can you answer these queries I](https://www.luogu.org/problem/SP1043)

[更好的阅读体验](https://www.cnblogs.com/Paranoid-LS/p/11592810.html)

### 静态维护子段和最大值

提供结构体指针线段树写法：

设$l$为区间左端点， $r$为区间右端点；

$ls$为以$l$为左端点的最大子段和, $rs$为以$r$为右端点的最大子段和;

$sum$为区间和, $val$为区间子段和最大和。

$ch[0]$为左儿子, $ch[1]$为右儿子.

考虑维护：

> o->sum = ch[0]->sum + ch[1]->sum;
>
> o->ls = max(ch[0]->ls, ch[0]->sum + ch[1]->ls);
>
> o->rs = max(ch[1]->rs, ch[1]->sum + ch[0]->rs);
>
> o->val = max(max(ch[0]->val, ch[1]->val), max(max(o->ls, o->rs), ch[0]->rs + ch[1]->ls);

 这样可以考虑到所有的转移情况；

在询问时, 若询问区间跨过左右两个子区间, 则我们利用$ls, rs, sum$来更新出当前区间的$val$;

所以我们返回结构体指针。

### code：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 5e4 + 5;
int read() {
	int x = 0, f = 1; char ch;
	while(! isdigit(ch = getchar())) (ch == '-') && (f = -f);
	for(x = ch^48; isdigit(ch = getchar()); x = (x<<3) + (x<<1) + (ch^48));
	return x * f;
}
int n, m;
template <class T> T Max(T a, T b) { return a > b ? a : b; }
struct Segment {
	struct node {
		int l, r, ls, rs, sum, val;
		node *ch[2];
		node(int l, int r, int ls, int rs, int sum, int val) : l(l), r(r), ls(ls), rs(rs), sum(sum), val(val) {
			ch[0] = ch[1] = NULL;
		}
		inline int mid() { return (l + r) >> 1; }
		inline void up() {
			sum = ch[0]->sum + ch[1]->sum;
			ls = Max(ch[0]->ls, ch[0]->sum + ch[1]->ls);
			rs = Max(ch[1]->rs, ch[1]->sum + ch[0]->rs);
			val = Max(Max(ch[0]->val, ch[1]->val), Max(Max(ls, rs), ch[0]->rs + ch[1]->ls));
		}
	} *root;
	void build(node *&o, int l, int r) {
		o = new node(l, r, 0, 0, 0, 0);
		if(l == r) {
			o->ls = o->rs = o->sum = o->val = read();
			return;
		}
		build(o->ch[0], l, o->mid());
		build(o->ch[1], o->mid() + 1, r);
		o->up();
	}
	node *query(node *o, int l, int r) {
		if(l <= o->l && o->r <= r) return o;
		if(r <= o->mid()) return query(o->ch[0], l, r);
		if(l > o->mid()) return query(o->ch[1], l, r);
		node *res = new node(l, r, 0, 0, 0, 0);
		node *t1 = query(o->ch[0], l, r), *t2 = query(o->ch[1], l, r);
		res->sum = t1->sum + t2->sum;
		res->ls = Max(t1->ls, t1->sum + t2->ls);
		res->rs = Max(t2->rs, t2->sum + t1->rs);
		res->val = Max(Max(t1->val, t2->val), Max(Max(res->ls, res->rs), t1->rs + t2->ls));
		return res;
	}
} tr;
int main() {
	n = read();
	tr.build(tr.root, 1, n);
	m = read();
	for(int i = 1, l, r; i <= m; ++ i) {
		l = read(); r = read();
		printf("%d\n", tr.query(tr.root, l, r)->val);
	}
	return 0;
}
```

---

## 作者：xzlhxc_ed (赞：1)


**[博客中食用更佳](https://www.luogu.org/blog/xzlhxc/solution-sp1043)**  
 _给读者：标题大字体是我的习惯，如果觉得不美观及有更好的建议请私信作者！_ 
 
------------

[题目链接（洛谷）](https://www.luogu.org/problemnew/show/SP1043)    

读懂这篇文章你可能要会：~~基础动归~~，[线段树0](https://www.luogu.org/problemnew/show/P3374)（单点修改区间求值），[最大子段和](https://www.luogu.org/problemnew/show/P1115) 的 $O(NlogN)$ 解法。
# ①题意简述
动态最大子段和。即询问一个序列的子序列的最大子段和。    
# ②维护信息
本题的数据范围为1e4级别，又只有230ms的~~毒瘤~~时限，明显暴力dp的$O(nm)$算法不够优秀，所以我们要考虑更优的算法。

根据**分治**的思想，我们把一段序列分成若干个子序列，**如果答案能从子序列中合并而得，就能得到$O(mlogn)$的优秀算法**。然而，如果仅根据子序列的最大子段和，是没办法合并的，因为**两个子序列的最大子段和不一定是整个序列的最大子段和**，即这个信息不满足结合律。  
 _这里举一个简单的例子：100 -1 | -2 100 （|为分界点）_ 

那要维护什么呢？

~~233~~从原本的静态最大子段和的$O(nlogn)$算法中，我们知道，一段序列的最大子段和，**要么在中点左侧，要么在中点右侧，要么横跨中点**（易证，请读者思考）。所以我们在每一个子序列中维护这样的信息：
```
struct node//暂时不用管这个名字
{
	int sum,maxx,lmax,rmax;
};
```
其中，maxx为该序列的最大子段和，lmax为以最左端为开头的最大子段和（后称为：前缀最大子段和），rmax为以最右端为结尾的最大子段和（后称为：后缀最大子段和）。于是，在计算时，我们可以这么做：
```
int lc=k<<1,rc=k<<1|1; //lc为左子序列，rc为右子序列
maxx[k]=max(max(maxx[lc],maxx[rc]),rmax[lc]+lmax[rc]);
```
![](https://cdn.luogu.com.cn/upload/pic/62280.png)
怎么理解呢？

这里用了一点**贪心**的思想。再次看一遍有着~~233~~标记的那段话，如果最大子段和横跨中点，那么就等于中点及为左的最大子段和（rmax[lc]，左子序列的后缀最大子段和）加上中点为右的最大子段和（lmax[rc]，右子序列的前缀最大子段和）。在横跨中点的情况下，没有比这样更优的最大子段和（易证，请读者思考）。

否则，如果不跨越中点，那就在左右子序列的最大子段和中找最大值就行。

等等，那sum是什么？有什么用？  

前面我们解决了maxx的计算，那lmax和rmax要怎么计算呢？  
假设求出了左右子序列的lmax与rmax值，**此时它们都没跨越中点**。到了父序列（与子序列相对）中，**如果跨越中点得到的lmax与rmax比原先的更大，那就跨越中点**！以lmax为例，现在求出了左子序列的lmax值，如果跨过中点，就更新为左子序列的区间和加上右子序列的rmax。rmax的更新类似。所以，**sum就是子序列的区间和**。
```
lmax[lc]=max(lmax[lc],sum[lc]+lmax[rc]);
rmax[rc]=max(rmax[rc],sum[rc]+rmax[lc]);
```
![](https://cdn.luogu.com.cn/upload/pic/62283.png)

**最后，用一个支持单点修改区间求和的数据结构（如线段树）来维护这些信息就可以啦！**
# ③AC!
做完这题可以做这题的进阶版：["Ray, Pass me the dishes!"](https://www.luogu.org/problemnew/show/UVA1400)，类似题：[好一个一中腰鼓！](https://www.luogu.org/problemnew/show/P2253)。  
# ④小结
做类似的线段树题，要从哪些内容开始考虑呢？  
1. 线段树每个节点代表的区间维护的信息；
1. 信息的更新（update函数，用于建树、修改及查询）。   
 _例如如果只是区间求和，那么父节点的信息就是2个子节点的和。当维护的信息较多，最好封装到一个函数中。_ 
1. 各个信息更新的顺序。
1. 修改时要修改的内容。
1. 需要用到的某些信息的$lazy$ $tag$（懒标记）。（区间修改）
1. $lazy$ $tag$ 之间的优先级。（区间修改）
1. $lazy$ $tag$ 下传及下传后信息的更新。（区间修改）

------------

“我想做一篇详略得当，清晰明了的题解。”   
喜欢就点个赞吧！

---

## 作者：hepan (赞：0)

### 题目大意
多次查询最大字段和。

$n,m\le5\cdot10^4$

### 思路

别人都没怎么将如何合并，我来讲一下吧。

维护一颗 $sum,la,ra,ans$ 表示区间 $[l,r]$ 的和、最大前缀和、最大后缀和、最大子段和。

+ $sum$ 很好合并。

+ $la$ 可以是左区间的 $la$ ，或者左区间的 $sum$ 加右区间的 $la$。

+ $ra$ 与 $la$ 差不多

+ $ans$ 可以是左区间的 $ans$ 或右区间的 $ans$ ,或者是左区间的 $ra$ 加右区间的 $la$，就是把两个区间拼起来。

询问答案是维护一个 $Ans$ 也按照与上面差不多的规则合并，注意顺序。

时间复杂度：$\Theta(n+q\log n)$


---

## 作者：Steven_Meng (赞：0)

**线段树每个节点中存的值：**

$val[]$ ——区间所有数之和

$lmax[]$ ——选的$a[i]$在区间内，且包括$a[l]$，连续$a[i]$之和的最大值

$rmax[]$ ——选的$a[i]$在区间内，且包括$a[r]$，连续$a[i]$之和的最大值

$maxn[]$ ——选的$a[i]$在区间内，连续$a[i]$之和的最大值（即本题答案）

之所以要计算$lmax$，$rmax$，$val$，是为了合并节点时，能计算出$maxn$的值

------------------------------------

这里介绍一种比较简洁的写法

这道题中线段树的重点是节点合并，即$pushup$的过程

不妨**将节点合并的操作定义为+**

这样Query时就不用再敲一遍相同的代码，直接将查询结果相"+"即可
```cpp
#include <bits/stdc++.h>
#define MAXN 50005
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
int a[MAXN];
namespace SegmentTree{
    struct node{
        int l,r;
        int lmax,rmax,maxn;
        //从左端开始最大值，从右端开始最大值，整段最大值
        int val;//这段的和
    }tree[MAXN<<2];
    #define lc i<<1
    #define rc i<<1|1
    node operator + (node A,node B){//定义合并操作+
        node temp;
        temp.lmax=max(B.lmax+A.val,A.lmax);
        //可以左区间全部选，加上右区间lmax,也可以直接用左区间lmax
        temp.rmax=max(A.rmax+B.val,B.rmax);
        //同理
        temp.maxn=max(max(A.maxn,B.maxn),A.rmax+B.lmax);
        //可以直接用左右区间maxn,也可以将左右区间rmax,lmax合并
        temp.val=A.val+B.val;
        temp.l=A.l,temp.r=B.r;
        return temp;
    }
    void pushup(int i){
        tree[i]=tree[lc]+tree[rc];
    }
    void Build(int l,int r,int i){//建树
        if (l==r){
            tree[i].lmax=tree[i].rmax=tree[i].maxn=tree[i].val=a[l];
            tree[i].l=tree[i].r=l;
            return ;
        }
        int mid=(l+r)>>1;
        Build(l,mid,lc);
        Build(mid+1,r,rc);
        pushup(i);
    }
    node Query(int L,int R,int i){
        if (L<=tree[i].l&&tree[i].r<=R){
            return tree[i];
        }
        int mid=(tree[i].l+tree[i].r)>>1;
        if (L>mid) return Query(L,R,rc);
        else if (R<=mid) return Query(L,R,lc);
        else return Query(L,R,lc)+Query(L,R,rc);
        //这里就不用再重复一遍节点合并的过程
    }
};
using namespace SegmentTree;
int main(){
    int n=read();
    for (register int i=1;i<=n;++i){
        a[i]=read();
    }
    Build(1,n,1);
    int q=read();
    while (q--){
        int L=read(),R=read();
        node temp=Query(L,R,1);
        printf("%d\n",temp.maxn);
    }
}
```


---

## 作者：eros1on (赞：0)

~~[博客](https://tle666.github.io/2019/03/17/[SPOJ1043]%20GSS1/)食用更佳~~

# **Description**

给一段可能有负数的序列，查询最大子段和。

对于$100 \%$的数据，序列长度$N \leq 50000$，$a[i] \leq 15007$

[题目链接戳这里](<https://www.luogu.org/problemnew/show/SP1043>)

# **Solution**

线段树查询最大子段和。

这里需要维护四个信息：

- $s$ 区间和
- $mx$ 区间最大子段和
- $lmx$ 区间前缀和最大值
- $rmx$ 区间后缀和最大值

则维护的时候就像这样

```cpp
s = ls->s + rs->s,
mx = max(ls->rmx + rs->lmx, max(ls->mx, rs->mx)), // 注意有三种情况
lmx = max(ls->lmx, ls->s + rs->lmx),
rmx = max(rs->rmx, rs->s + ls->rmx);
```

其中$ls$，$rs$分别是左子，右子。

还有一个注意事项：$query$（查询）的时候返回值要是$node*$！只有这样才能够维护四个信息。

# **Code**

~~码风在这种题里很重要~~

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
const int MAXN = 1001000;
int n, m, a[MAXN];
struct node {
    int left, right, mx, lmx, rmx, s;
    node *ls, *rs;
    inline void upd() {
        s = ls->s + rs->s,
        mx = max(ls->rmx + rs->lmx, max(ls->mx, rs->mx)),
        lmx = max(ls->lmx, ls->s + rs->lmx),
        rmx = max(rs->rmx, rs->s + ls->rmx);
    }
} pool[MAXN << 5], *root, *cnt = pool;
inline void build(node *r, int left, int right) {
    r->left = left, r->right = right;
    if(left == right) {
        r->s = r->mx = r->lmx = r->rmx = a[left];
        return ;
    } int mid = (left + right) >> 1;
    node *ls = ++cnt, *rs = ++cnt;
    r->ls = ls, r->rs = rs;
    build(ls, left, mid), build(rs, mid + 1, right);
    r->upd();
}
inline node *query(node *r, int left, int right) {
    if(r->left == left && r->right == right) return r;
    if(r->ls->right >= right) return query(r->ls, left, right);
    else if(r->rs->left <= left) return query(r->rs, left, right);
    else {
        node *L, *R, *res;
        L = query(r->ls, left, r->ls->right),
        R = query(r->rs, r->rs->left, right),
        res = ++cnt,
        res->s = L->s + R->s,
        res->left = L->left, res->right = R->right,
        res->mx = max(L->rmx + R->lmx, max(L->mx, R->mx)),
        res->lmx = max(L->s + R->lmx, L->lmx),
        res->rmx = max(R->s + L->rmx, R->rmx);
        return res;
    }
}
int main() {
    int left, right;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(root = cnt, 1, n);
    scanf("%d", &m);
    while(m--) {
        scanf("%d%d", &left, &right);
        printf("%d\n", query(root, left, right)->mx);
    }
    return 0;
}
```



---

