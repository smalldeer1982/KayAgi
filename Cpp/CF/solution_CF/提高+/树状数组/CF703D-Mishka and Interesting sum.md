# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5
```

### 输出

```
0
3
1
3
2
```

# 题解

## 作者：顾z (赞：13)

刚看到题的一瞬间,输出出现偶数次的数的异或和.

~~"不是0嘛？这不sb题？"~~

突然发现看错题.

原来是求**出现偶数次的单个数的异或和**。

通过一些推导可以发现,答案是**求区间内不同数的异或和与区间异或和的异或和**。

为什么？

我们假设当前查询的区间的数为：$1,3,4,2,5,4,1$

此时根据异或的性质$x$ ^$x=0$,我们再异或上区间内不同的数。

则这段异或起来就是：$1$^$4$。

稍作解释一下

> 我们区间中出现偶数次的数的异或和就是$0$，此时再异或上区间内不同的数。
>
> 此时这些出现偶数次的数的异或再次出现。
>
> 而那些出现单次的数就消失了.

那么现在问题就变为**维护区间内不同的数的异或和**

这题数据范围的话,需要**离散化**。

因为没有修改操作,所以考虑离线.我们对右端点进行排序(**从小到大**)

然后考虑用一种数据结构维护：线段树 or 树状数组。

这里用了**树状数组**。

**树状数组维护异或**。

记录一下这个数上一个出现的位置.

然后遇到某个位置再出现,我们再在树状数组删去这个数几个(即再异或一次.)

``代码``

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>
#define R register

using namespace std;

const int gz=3000008;

inline void in(R int &x)
{
	R int f=1;x=0;R char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}

int n,a[gz],sum[gz],pre[gz],b[gz],head[gz];

int new_n=1,q,ans[gz];

struct cod
{
	int l,r,idx;
	bool operator <(const cod&a)const
	{
		return r<a.r;
	}
}que[gz];

#define lowbit(x) x&-x

int tr[gz<<1];

inline void add(R int o,R int del)
{
	for(;o<=n;o+=lowbit(o))
		tr[o]^=del;
}

inline int query(R int o)
{
	R int res=0;
	for(;o;o-=lowbit(o))
		res^=tr[o];
	return res;
}

int main()
{
	in(n);
	for(R int i=1;i<=n;i++)in(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	for(R int i=2;i<=n;i++)
		if(b[new_n]!=b[i])b[++new_n]=b[i];
	for(R int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+new_n+1,a[i])-b;
	for(R int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]^b[a[i]];
		pre[i]=head[a[i]];
		head[a[i]]=i;
	}
	in(q);
	for(R int i=1;i<=q;i++)
		in(que[i].l),in(que[i].r),que[i].idx=i;
	sort(que+1,que+q+1);
	R int now=1;
	for(R int i=1;i<=q;i++)
	{
		R int r=que[i].r,l=que[i].l;
		while(now<=r)
		{
			if(pre[now])
				add(pre[now],b[a[now]]);
			add(now,b[a[now]]);
			now++;
		}
		ans[que[i].idx]=(query(r)^query(l-1))^(sum[r]^sum[l-1]);
	}
	for(R int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	
	
	return 0;
}

```



---

## 作者：RuntimeErr (赞：12)

区间查询，怎么标签能少得了莫队呢？

# 莫队+卡常

[题目传送门](https://www.luogu.com.cn/problem/CF703D)

这道题的查询求出现偶数次的数的异或和，我们维护一个  $XORsum$ 。

根据异或的可消去性，我们添加一个数，当它出现了偶数次时它在
$XORsum$ 中有贡献，当它只出现了奇数次时让 $XORsum$ 异或它自己将它消去，所以我们在 $add$ 和 $del$ 函数中可以这样写：

```cpp
inline void add(int x){
	if(++cnt[a[x]]>1)XORsum^=a[x];//这里为1是因为它一开始是没有贡献的，当它为2时才开始有贡献，不要算错了
}
inline void del(int x){
	if(--cnt[a[x]]>0)XORsum^=a[x];//这里为0是因为当它出现次数为1时要消去它自己
}
```

但由于 $1\leq n,m \leq 10^6$, $1 \leq a_i \leq 10^9$，我们需要卡卡常+离散化。

我们可以维护一个离散化数组 $b$ , 再将 $a_i$ 设为其在离散化数组 $b$ 中的位置，$cnt$ 数组改为记录 $a_i$ 离散化后的位置，这样能省下不少的空间。

再来说说莫队的优化，理论上块长取 $\frac{n}{\sqrt{m}}$ 时最优，再加上奇偶排序，总时间复杂度为 $O(n\sqrt{m})$。

### $Talk\ is \ cheap, show\ you\ the\ code:$

```cpp
#include<cstdio>
#include<iostream> 
#include<algorithm>
#include<cmath>
using namespace std;
#define N (int)(1e6+10)
#define fp(i,l,r) for(re int i=(l);i<=(r);++i)
#define il inline
#define re register
il int read(){//卡常快读当然是必不可少的啦
	re int x=0,f=1;re char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}

int n,m,bl,a[N],b[N],cnt[N],ans[N],XORsum;
struct query{
	int l,r,be,id;
}q[N];
bool cmp(query a,query b){
	return a.be^b.be?a.l<b.l:a.be&1?a.r<b.r:a.r>b.r;
}


il void add(int x){
	if(++cnt[a[x]]>1)XORsum^=b[a[x]];
}
il void del(int x){
	if(--cnt[a[x]]>0)XORsum^=b[a[x]];
}

int main(){
	n=read();
	fp(i,1,n)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);//离散化
	int tot=unique(b+1,b+n+1)-b-1;
	fp(i,1,n)a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	m=read();bl=n/pow(m,0.455);//灵魂取块长
	fp(i,1,m){
		q[i].l=read();q[i].r=read();
		q[i].id=i;q[i].be=q[i].l/bl;
	}
	sort(q+1,q+m+1,cmp);
	re int l=q[1].l,r=q[1].l-1;
	fp(i,1,m){
		while(l<q[i].l)del(l++);
		while(l>q[i].l)add(--l);
		while(r<q[i].r)add(++r);
		while(r>q[i].r)del(r--);
		ans[q[i].id]=XORsum;
	}
	fp(i,1,m)printf("%d\n",ans[i]);
	return 0;
}
```
### $Isn't\ it\ easy?$

---

## 作者：灰鹤在此 (赞：5)

## 线段树做法 $+$ 详解

看到题解里面都是用莫队或者树状数组来做的，那么我来提供一种线段树的做法（本质和树状数组一样）。

我们可以把题目条件推成我们熟悉的模样：出现偶数次的数的异或和 $=$ 出现奇数次的数的异或和 $^$ 出现奇数次的数的异或和 $^$ 出现偶数次的数的异或和 $=$ 区间异或和 $^$ 出现奇数次的数的异或和 $=$ 区间异或和 $^$ 区间内不同数的异或和。

区间异或和可以用前缀和的方法求，难就难在求区间内不同数的异或和。

我们要得到每一个数它前面和它相同的数的位置。这个我们可以通过先离散化再二分查找这个数在离散化序列里的位置，最后在线性记录每一个数它之前出现过的位置即可，达到 $\mathcal{O}(n\log n)$ 的预处理时间。

由于不用修改，所以我们可以将询问按照右端点排序。这样可以帮助我们处理区间内不同数的异或和更简单一点。

因为我们的 $r$ 是非递减的，所以我们只要按照 $r$ 来维护其前面的区间即可。如果我们维护到了 $x$，位置在 $tot$。但是 $x$ 之前没有出现，我们可以直接修改异或线段树。

因为如果 $l$ 在 $tot$ 的左边，那么维护的区间正好对答案有贡献。在右边也肯定没有贡献。

如果 $x$ 在之前出现过，万一 $l$ 大于之前的位置而小于现在的位置，按理说应该是没有贡献的。但是我们一开始维护的 $x$ 本意是对后面的所有序列都是有贡献的。所以根据异或的性质，我们先将之前的 $x$ 先修改异或一遍，再对于现在的 $x$ 异或修改一遍，那么就正确了。这也体现了之前为什么要得到每一个数它前面和它相同的数的位置的原因。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=1e6+5;
int n,m,a[MaxN],xorr[MaxN],lsh[MaxN],ans[MaxN],place[MaxN],last[MaxN],lastplace[MaxN],tree[MaxN<<2];
struct Question{
	int l,r,id;
	bool friend operator < (Question x,Question y){
		return x.r<y.r;
	}
}q[MaxN];
void update(int x,int l,int r,int p,int k){
	if(x==l&&x==r){
		tree[p]^=k;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		update(x,l,mid,p<<1,k);
	}else{
		update(x,mid+1,r,p<<1|1,k);
	}
	tree[p]=tree[p<<1]^tree[p<<1|1];
}
int query(int x,int y,int l,int r,int p){
	if(x<=l&&y>=r){
		return tree[p];
	}
	int mid=(l+r)>>1,ans=0;
	if(x<=mid){
		ans^=query(x,y,l,mid,p<<1);
	}
	if(y>mid){
		ans^=query(x,y,mid+1,r,p<<1|1);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		xorr[i]=xorr[i-1]^a[i];
		lsh[i]=a[i];
	}
	sort(lsh+1,lsh+n+1);
	int len=unique(lsh+1,lsh+n+1)-lsh-1;
	for(register int i=1;i<=n;i++){
		place[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	}
	for(register int i=1;i<=n;i++){
		lastplace[i]=last[place[i]];
		last[place[i]]=i;
	}
	scanf("%d",&m);
	for(register int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int tot=1;
	for(register int i=1;i<=m;i++){
		while(tot<=q[i].r){
			if(lastplace[tot]>0){
				update(lastplace[tot],1,n,1,lsh[place[tot]]);
			}
			update(tot,1,n,1,lsh[place[tot]]);
			tot++;
		}
		ans[q[i].id]=query(q[i].l,q[i].r,1,n,1)^xorr[q[i].r]^xorr[q[i].l-1];
	}
	for(register int i=1;i<=m;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：louhao088 (赞：5)



一眼看就是莫队，${10}^6$ 卡卡常就过了,然后 T 飞，不知道大佬是怎么卡过去的。


------------


因为题目是出现偶数次的异或和，我们把出现奇数次的异或和异或上出现数的异或和就是答案。

对于出现奇数次数的异或和，我们直接处理前缀和就可以了，因为异或 2 次等于没异或。

对于出现数的异或和，我们可以参考 [HH的项链](https://www.luogu.com.cn/problem/P1972) 。考虑树状数组，先对数列离散化，对询问按右端点排序，每次处理时，先把右端点之前的数全部放入树状数组。每次树状数组操作先把这个位置之前与这个值相等的点的值去掉，再在这个位置加上，算是一种贪心吧，后面有了前面就一定没用。

这样我们就可以查询一段数其之间出现数的异或和了。

注意，这个树状数组处理的不是加，而是异或了，但改动的位置还是不能为 0。



------------
代码如下
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define lowbit(x) (x&(-x))
const int maxn=1e6+5;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
struct node 
{
	int l,r,id;
}q[maxn];
int n,m,sum[maxn],a[maxn],b[maxn],ans[maxn],res,l,r,t,c[maxn],f[maxn];
bool cmp(node a,node b){return a.r<b.r;}
inline void add(int x,int num){if(!x)return;for(int i=x;i<=n;i+=lowbit(i))c[i]^=num;}
inline int query(int x){int res=0;for(int i=x;i;i-=lowbit(i))res^=c[i];return res;}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)b[i]=a[i]=read(),sum[i]=sum[i-1]^a[i];
	sort(b+1,b+n+1);m=read();
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
	for(int i=1;i<=m;i++)q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		while(r<q[i].r)r++,add(f[a[r]],b[a[r]]),f[a[r]]=r,add(f[a[r]],b[a[r]]);
		ans[q[i].id]=query(q[i].l-1)^query(q[i].r)^sum[q[i].r]^sum[q[i].l-1];
	}
	for(int i=1;i<=m;i++)print(ans[i]),puts("");
 	return 0;
}

```


---

## 作者：Cesare (赞：4)

开局被卡常，心情复杂，改成了题解的块大小才过。

这里给出一种奇怪的离散化方式：记一个数组 $c$ 来映射原数组，数组 $b$ 用来排序，数组 $a$ 存原来的值。

然后莫队时的 $del$ 与 $add$ 都在 $c$ 上操作， $res$ 异或上 $a$ 。

下面讲一下如何 $add$ 与 $del$ 。

考虑异或过偶数次的元素都要考虑贡献，但异或上奇数次的元素都是从偶数次上来的，所以也要靠考虑贡献。

~~也就是说无脑异或就完事了~~

注意 $add$ 时如果原来该元素出现次数为 $0$ ，不必考虑其贡献。

$Code:$

```cpp
#include <bits/stdc++.h>
//#include<tr1/unordered_map>
//#include"Bignum/bignum.h"
//#define lll bignum
#define ls(x) ( x << 1 )
#define rs(x) ( x << 1 | 1 )
//#define mid ( (l + r) >> 1 )
//#define Mid ( (l + r) / 2.0 )
#define lowbit(x) ( x & -x )
#define debug(x) (cout << "#x = " << (x) << endl)
#define Set(x, i) memset (x, i, sizeof(x))
#define re register
#define For(i, j, k) for(re int i = (j); i <= (k); ++i)
#define foR(i, j, k) for(re int i = (j); i >= (k); --i)
#define Cross(i, j, k) for(re int i = (j); i; i = (k))
using namespace std;
typedef double db;
typedef int ll;
typedef unsigned long long ull;
const db eps = 1e-8;
const ll N = 1000011;
const ll inf = 0x3f3f3f3f3f3f;

ll n, m, len, res = 0, a[N], b[N], c[N], cnt[N], Ans[N];

struct MoTeam {
    ll l, r, id;
} Q[N];

inline bool cmp ( MoTeam a, MoTeam b ) {
    return (a.l / len) ^ (b.l / len)? 
        a.l < b.l: ( (a.l / len & 1)? a.r < b.r: a.r > b.r );
}

namespace IO {

    inline char gc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return (p1 == p2) && (p2 = (p1 = buf) +
            fread (buf, 1, 100000, stdin), p1 == p2)? EOF: *p1++;
    }

    #define dd ch = getchar()
    inline ll read() {
        ll x = 0; bool f = 0; char dd;
        for (; !isdigit (ch); dd) f ^= (ch == '-');
        for (; isdigit (ch); dd)  x = (x << 3) + (x << 1) + (ch ^ 48);
        return f? -x: x;
    }
    #undef dd

    inline void write( ll x ) {
        if ( x < 0 ) putchar ('-'), x = -x;
        if ( x > 9 ) write ( x / 10 ); putchar ( x % 10 | 48 );
    }

    inline void wrn ( ll x ) { write (x); putchar (' '); }

    inline void wln ( ll x ) { write (x); putchar ('\n'); }

    inline void wlnn ( ll x, ll y ) { wrn (x), wln (y); }

}

using namespace IO;

inline void add ( ll x ) { if ( ++cnt[c[x]] ^ 1 ) res ^= a[x]; }

inline void del ( ll x ) { if ( --cnt[c[x]] ) res ^= a[x]; }

int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
    n = read();
    For ( i, 1, n ) a[i] = b[i] = c[i] = read();
    m = read();
    For ( i, 1, m ) 
        Q[i].l = read(), Q[i].r = read(), Q[i].id = i;

    sort (b + 1, b + n + 1);
    ll Len = unique (b + 1, b + n + 1) - b - 1;
    For ( i, 1, n ) c[i] = lower_bound (b + 1, b + n + 1, c[i]) - b;

    ll L = 1, R = 0;
    len = n / sqrt(m * 0.9);
    sort (Q + 1, Q + m + 1, cmp);
    For ( i, 1, m ) {
        while ( L > Q[i].l ) add (--L);
        while ( L < Q[i].l ) del (L++);
        while ( R > Q[i].r ) del (R--);
        while ( R < Q[i].r ) add (++R);
        Ans[Q[i].id] = res;
    }
    
    For ( i, 1, m ) wln (Ans[i]); return 0;
}

/*

*/

```
温馨提示：不要抄代码。

---

## 作者：Little09 (赞：3)

这题非常类似 [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)，这是数颜色的题目的常见套路。

首先，出现偶数次的数的异或和 转化为 所有数的异或和 与 所有不重复数的异或和 的异或和。

前者是前缀和可以搞定的，后者就是区间数颜色的做法。先处理出每个点的颜色上一次出现位置 $pre$。离线询问，按右端点排序，用树状数组维护每个点。加入某个点时删除它的 $pre$，实现方法同 [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1000006;
int n,m,tree[N];
int col[N],pre[N],s[N];
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int k)
{
	if (x==0) return;
	for (;x<=n;x+=lowbit(x)) tree[x]^=k;
}
int ask(int x)
{
	int res=0;
	for (;x;x-=lowbit(x)) res^=tree[x];
	return res;
}
struct ques
{
	int l,r,id;
}q[N];
inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
bool cmp(ques x,ques y)
{
	return x.r<y.r;
}
int ans[N];
map<int,int>a;
int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		col[i]=read();
		s[i]=s[i-1]^col[i];
		pre[i]=a[col[i]];
		a[col[i]]=i;
	}
	m=read();
	for (int i=1;i<=m;i++)
	{
		q[i].id=i,q[i].l=read(),q[i].r=read();
	}
	sort(q+1,q+m+1,cmp);
	int tot=0;
	for (int i=1;i<=m;i++)
	{
		while (tot<q[i].r)
		{
			tot++;
			add(tot,col[tot]),add(pre[tot],col[pre[tot]]);
		}
		ans[q[i].id]=ask(q[i].r)^ask(q[i].l-1)^s[q[i].r]^s[q[i].l-1];
	}
	for (int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}

```


---

## 作者：傅思维666 (赞：2)


## 题解：

解决本题的关键是牢记异或的一个性质：异或一个数两次相当于异或了个寂寞。

那么我们只需要想办法把一个区间出现奇数次的东西全搞没就好。就利用这个性质。

我们先尝试着把整个区间的数都异或上去。发现，偶数次的数已经都异或成寂寞了，而奇数次的数各自保留了一个作为异或和的贡献。

芜湖？那我们再把偶数次的数变成奇数次，奇数次的数还是奇数次，再异或上去，不就把奇数次的数都异或成寂寞，把偶数次的数都留下了一个么？

思路豁然开朗：答案就是**区间异或和异或上区间所含有的数（每个数只异或一次）的异或和**。

区间异或和可以用异或的可差分性，用异或前缀和先处理好。

那么区间所含有的数，每个数只异或一次，该怎么处理呢？

用树状数组维护。还是抓住”异或一个数两次相当于异或了个寂寞“这个性质。只需要把这个数之前重复出现的数再异或一次，就相当于只保留了一个。但是这样的修改是有后效性的，也就是说，如果我们先处理后面的询问区间，就会提前把前面的区间修改掉，导致之后处理前面的区间时出错。于是我们把所有询问离线处理。维护pre数组表示这个数前面第一个和这个数一样的数的位置，就可以完成这一任务了。

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e6+6;
int n,m;
int a[maxn],b[maxn],sum[maxn];
int head[maxn],pre[maxn];
int ans[maxn];
int tree[maxn];
struct node
{
	int l,r,id;
}q[maxn];
bool cmp(node a,node b)
{
	if(a.r==b.r)
		return a.l<b.l;
	return a.r<b.r;
}
void update(int x,int k)
{
	for(int i=x;i<=n;i+=i&-i)
		tree[i]^=k;
}
int query(int x)
{
	int ret=0;
	for(int i=x;i;i-=i&-i)
		ret^=tree[i];
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int size=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+size+1,a[i])-b;
	for(int i=1;i<=n;i++)
	{
		pre[i]=head[a[i]];
		head[a[i]]=i;
		sum[i]=sum[i-1]^b[a[i]];
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int pos=1;
	for(int i=1;i<=m;i++)
	{
		int l=q[i].l,r=q[i].r;
		while(pos<=r)
		{
			if(pre[pos])
				update(pre[pos],b[a[pos]]);
			update(pos,b[a[pos]]);
			pos++;
		}
		ans[q[i].id]=query(q[i].r)^query(q[i].l-1)^sum[r]^sum[l-1];
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Carbon (赞：2)

首先，题意就不多说了；

观察题目，我们发先要求的是出现偶数个数的数的亦或和，根据亦或的性质我们知道，一个数如果被亦或偶数次，那么就是它本身，
说以稍加思索~~（很容易）~~可以发现，
区间出现偶数次的数的异或和=区间异或和^区间所有不同数的异或和。所以我们只需用线段树维护区间内所有不同数的亦或和，而区间亦或和，具体可参见[sp3267](https://www.luogu.org/problemnew/show/SP3267)，只需在前者上做一些改动，，而区间亦或和，这可以用前缀和来完成。

ps:由于此题数据范围较大~~（我懒得写离散化）~~，于是用map来记录每个数上一次出现的位置

废话不多说，上代码：



```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N=4e6+5;//线段树的4倍空间 
map <int,int> pos;//用于记录每个数上一次出现的位置 
int L[N],R[N];
int letter[N]; 
int dp[N];//区间亦或和 
int sum[N];//线段树 
int ans[N];//记录答案- 
int n,m;

struct node
{
    int l,r;//区间 
    int cnt;//读入时的位置 
    bool operator <(const node &b)const
    {
        return r<b.r;
    }
}a[N];
//线段树裸模板 
void build(int l,int r,int now)
{
    L[now]=l;
    R[now]=r;
    sum[now]=0;
    if (l==r)return;
    int mid=(l+r)>>1;
    build(l,mid,now<<1);
    build(mid+1,r,now<<1|1);
    sum[now]=sum[now<<1]^sum[now<<1|1];
}

void update(int l,int r,int now,int d)
{
    if (L[now]==l&&R[now]==r)
    {
        sum[now]^=d;
        return;
    }
    int mid=(L[now]+R[now])>>1;
    if (r<=mid)update(l,r,now<<1,d);
    else if (l>mid)update(l,r,now<<1|1,d);
    sum[now]=sum[now<<1]^sum[now<<1|1];
}

int query(int l,int r,int now)
{
    if (L[now]==l&&r==R[now])return sum[now];
    int mid=(L[now]+R[now])>>1;
    if (r<=mid)return query(l,r,now<<1);
    else if (l>mid)return query(l,r,now<<1|1);
    else return query(l,mid,now<<1)^query(mid+1,r,now<<1|1);
    sum[now]=sum[now<<1]^sum[now<<1|1];
}

int main()
{
    scanf("%d",&n);
    build(1,n,1);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&letter[i]);
        dp[i]=dp[i-1]^letter[i];//区间亦或和 
    }	
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        a[i].cnt=i;//小trick 
    }
    sort(a+1,a+1+m);
    int last=0;
    for (int i=1;i<=m;i++)
    {
        while(last<a[i].r)
        {
            last++;
            if (pos[letter[last]])
                update(pos[letter[last]],pos[letter[last]],1,letter[last]);//其实是本质是单点加 
            update(last,last,1,letter[last]);
            pos[letter[last]]=last;
        }
        ans[a[i].cnt]=query(a[i].l,a[i].r,1)^dp[a[i].r]^dp[a[i].l-1]; 
    }
    for (int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：ChthollyTree (赞：1)

看到题目，区间数字出现偶数个数的数的xor

第一反应是莫队对吧

统计一下区间里每个数字出现几次就好了

裸的莫队模板？

但是一看数据范围  n <= $10^6$

好吧

但是我们可以卡常

方法：

1.使用读入优化

2.分奇偶排序

3.调节块的大小

然后就可以根号过百万了

```
#include<bits/stdc++.h>
using namespace std;


#define MAXN 1000005
struct wen {
	int l,r,i;
}c[MAXN];
int a[MAXN];
int d[MAXN];
int p[MAXN];
int pos[MAXN];
int n,m;

namespace lsh
{
	struct aa
	{
		int a,i,c;
	}p[MAXN];
	
	bool cmp(aa a,aa b) {
		return a.a < b.a;
	}
	
	void	main()
	{
		for(int i = 1; i <= n; i ++) {
			p[i].i = i;
			p[i].a = a[i];
		}
		sort(p+1,p+n+1,cmp);
		for(int i = 1; i <= n; i ++)
			if(p[i].a == p[i-1].a) d[p[i].i] = d[p[i-1].i];
			else d[p[i].i] = d[p[i-1].i]+1; 
	}
}

bool cmp(wen a,wen b){
	return pos[a.l]^pos[b.l]?pos[a.l]<pos[b.l]:pos[a.l]&1?a.r<b.r:a.r>b.r;
}

inline void read(int &x) {
    int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=x*10+s-'0';s=getchar();}
    x*=f;
}

void rd()
{
	read(n);
	for(int i = 1; i <= n; i ++)
		read(a[i]);
	
	read(m);
	for(int i = 1; i <= m; i ++) {
		read(c[i].l);
		read(c[i].r);
		c[i].i = i;
	}
	int nn = n/sqrt(m*0.9);
	for(int i = 1; i <= n; i ++)
		pos[i] = i/nn;
	lsh::main();
	sort(c+1,c+m+1,cmp);
}

int an;
int ans[MAXN];
void jia(int x)
{
	++ p[d[x]];
	if(p[d[x]] != 1) an ^= a[x];
}

void jian(int x)
{
	-- p[d[x]];
	if(p[d[x]] != 0) an ^= a[x];
}

int main()
{
	rd();
	int l = 1,r = 0;
	for(int i  = 1; i <= m; i ++)
	{
		while(r < c[i].r)
		{
			r ++;
			jia(r);
		}
		while(l > c[i].l)
		{
			-- l;
			jia(l);
		}
		while(r > c[i].r) {
			jian(r);
			r --;
		}
		while(l < c[i].l) {
			jian(l);
			l ++;
		}
		ans[c[i].i] = an; 
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：斜揽残箫 (赞：0)

## Solution

莫队做法。

显然可以用莫队解决，我们发现求偶数次的异或和可以直接维护，因为异或有个性质，一个数异或他自己是 0，具体可以看这个题 ：[Link](https://www.luogu.com.cn/problem/P1469)，便是用异或为 0 来判断。

对于这个题目，我们只需要不断异或，就可以使得偶数次的异或和。

$a_i$ 的范围是 $1 \leq a_i \leq 10 ^ 9$，别忘了离散化。

记着异或的时候要异或原数，不要异或离散化后的数。

由于莫队不是正解，这个题目需要卡常，其实你把块长换为 ```n / pow(m,0.455)``` 就能过了，玄学，不行的话就再来个奇偶排序。

## Code

```cpp
#pragma GCC optimize("Ofast")//手动吸氧
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
using namespace std;
const int Maxk = 1e6 + 10;
int n,T,len_,m;
int a[Maxk],b[Maxk];
int L[Maxk],R[Maxk],pos[Maxk];
int ans[Maxk],Ans,cnt[Maxk],c[Maxk];
struct Query{
  int l_;
  int r_;
  int pos_;
}s[Maxk];
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}
inline bool CMP(Query a,Query b) {
  return pos[a.l_] ^ pos[b.l_] ? pos[a.l_] < pos[b.l_] : a.r_ < b.r_;
}
void BLOCK()
{
  len_ = n / pow(m,0.455);//话说这块长太神奇了，我也是看的题解。。
  T = n / len_;
  sort(b + 1,b + n + 1);
  int tot = unique(b + 1,b + n + 1) - b - 1;
  for(int i = 1;i <= n;i ++) a[i] = lower_bound(b + 1,b + tot + 1,a[i]) - b;//离散化
  for(int i = 1;i <= T;i ++) {
    L[i] = (i - 1) * len_;
    R[i] = i * len_;
  } 
  if(R[T] < n) T ++,L[T] = R[T - 1] + 1,R[T] = n;
  for(int i = 1;i <= T;i ++) 
    for(int j = L[i];j <= R[i];j ++) 
      pos[j] = i;
  return; 
}
void Prepare()
{
  for(int i = 1;i <= m;i ++) {
    s[i].l_ = read(),s[i].r_ = read();
    s[i].pos_ = i;
  }
  return;
}
inline void del(int x)
{
  cnt[a[x]] --;
  if(cnt[a[x]] > 0) Ans ^= c[x];
}
inline void add(int x)
{
  cnt[a[x]] ++;
  if(cnt[a[x]] > 1) Ans ^= c[x];
  //添加的时候第一次不添加，因为我们要加上的是偶数次的。
}
void Solve()
{
  sort(s + 1,s + m + 1,CMP);
  int l = 1,r = 0;
  for(int i = 1;i <= m;i ++) {
    int ql = s[i].l_;
    int qr = s[i].r_;
    while(l < ql) del(l ++);
    while(l > ql) add(-- l);
    while(r < qr) add(++ r);
    while(r > qr) del(r --);
    ans[s[i].pos_] = Ans;
  }
  for(int i = 1;i <= m;i ++) printf("%d\n",ans[i]);
  return;
}
signed main()
{
  n = read();
  for(int i = 1;i <= n;i ++) a[i] = b[i] = c[i] = read();
  //记着储存一个原数的值。
  m = read();
  BLOCK();
  Prepare();
  Solve();
  return 0;
}

```


---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF703D)

[CF's link](https://codeforces.com/problemset/problem/703/D)

#### 题意：

给定 $n$ 个数的序列 $a$。有 $m$ 次查询，每次查询为一个区间出现偶数次的数的异或和。

数据范围：$1≤n,m≤10^6,1≤a_i≤10^9$。

#### Solution：

看到只有查询，不难想到复杂度为 $n \sqrt{n}$ 的莫队。才 $10^9$，卡一卡总能过的。卡常是信仰！！！

不难想到，当为 $add$ 时，只要不是新出现的，他们的异或和都会发生变化，同理，当为 $del$ 时，只要是删完后还有这个数，异或和都会发生变化。

因为要记录这个数，所以还要离散化一下。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-08 20:09:03 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-08 21:06:06
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
const int N=1e6+5;
int n,m,a[N],b[N],kc,kuai[N],ans,Ans[N],tong[N],c[N];
/*
b_i为离散化后的数组
*/
struct node{
	int l,r,id;
}cun[N];
bool cmp(node x,node y){
	return (kuai[x.l]^kuai[y.l])?kuai[x.l]<kuai[y.l]:kuai[x.l]&1?x.r<y.r:x.r>y.r;
}
/*
按奇偶性排序，卡常小技巧
*/
void del(int x){if(--tong[b[x]]!=0)ans^=c[x];}
void add(int x){if(++tong[b[x]]!=1)ans^=c[x];}
/*
上文有讲
*/
int main(){
	n=read();
	kc=sqrt(n);
	FOR(i,1,n){
		b[i]=a[i]=c[i]=read();
		kuai[i]=(i-1)/kc+1;
	}
	sort(a+1,a+1+n);
	int len=unique(a+1,a+1+n)-a-1;
	FOR(i,1,n) b[i]=lower_bound(a+1,a+1+n,b[i])-a;
	m=read();
	FOR(i,1,m){
		cun[i].l=read();
		cun[i].r=read();
		cun[i].id=i;
	}
	sort(cun+1,cun+1+m,cmp);
	int l=1,r=0;
	FOR(i,1,m){
		int L=cun[i].l,R=cun[i].r;
		while(l<L) del(l++);
		while(l>L) add(--l);
		while(r>R) del(r--);
		while(r<R) add(++r);
		Ans[cun[i].id]=ans;
	}
	FOR(i,1,m){
		write(Ans[i]);
		puts("");
	}
	return 0;
}
```





---

## 作者：云岁月书 (赞：0)

## 异或和

### 题目大意

- 给定 $n$ 个数的序列 $a$ ,$m$ 次操作。操作有一种：

  $1.$ 给定 $l,r$ : 求 $a_l,a_r$ 之间，出现偶数次的数的异或和。

- $1 \leqslant n \leqslant 3\times10^5,1 \leqslant a_i \leqslant 10^9$

### solution：

$\Large \mathcal{First:}$  异或和有一个美妙的性质，即：

$$\large x_i \text{ xor } x_i = 0 \text{  且其满足交换律}$$

所以对于求异或和的操作，若是求奇数次数的异或和，那我们直接将数 $xor$ 上去即可，对于询问偶数次，我们只需要在预处理时先将该区间不一样的数全加入一次即可（就是指所有不一样的数的异或和异或上当前序列的异或和等于序列中偶数个数字的异或和）。

对于题目所要求的操作，我们观察到无修改操作，只是区间查询，所以可以离线（~~迫真.jpg~~）。

$\Large \mathcal{Second:}$ 唯一的难点，假设我们已经通过对区间的乱搞使得更新操作可以连续，那么我们如何更新和查询呢?

第一次见可能有点难想，但其实很简单，我们插入新的数时，把原先与之相同的的数删掉即可。

举个栗子：

对于序列 $a$ ：$1,2,2,2,2,3$

更新到 $4$ 时，我们记录的序列与真实序列的对比其实是这样的：

$$\Large \begin{aligned}tr\text{}&:\text{1  0  0  0  2  3}\\a&:\text{1  2  2  2  2  3}\end{aligned}$$

此时不难发现，若询问的区间的 $r$ 大于 4 时有 $a_l-a_r$ 与 $tr_l-tr_r$ 异或之后恰好得到的是正确答案。

再仔细观察一下图中的数字，不难发现我们的更新必须是在后面询问的 $r$ 都大于等于当前序列的 $r$ 时才不会影响到正确答案。

$\Large \mathcal{Third:}$ $a_i\leqslant 10^9$ 太大，空间开销太大，但是 $1 \leqslant n \leqslant 3\times10^5$ ，所以我们可以离散化。

具体实现可以使用线段树或树状数组。

综上便有了代码的处理步骤：

离散化，预处理每一个数 $a_i$ 上一次在序列中出现的位置 $Last_j,j < i$。

将询问的区间按照右端点排序。

假设已经处理完了了 $r_{i-1}$ 以前的序列。

对于 $r_i$ ，将 $(r_{i-1},r_i]$ 区间中的数加入到树状数组中,需要注意的是若之前该数字出现过则要删去原来出现在树状数组中的那一次。

详细见代码中。

~~~c++
# include <cstdio>
# include <algorithm>
//# pragma GCC optimize (2)
# define N 300000
# define lowbit(x) (x&-x)
# define reg register
using namespace std;

inline int Read()
{
	int x = 0;char ch = getchar();
	
	while(ch < '0' || ch > '9') ch = getchar();
	
	while(ch <= '9' && ch >= '0'){x = x*10 + (ch^48);ch = getchar();}
	
	return x;
}

int tr[N + 42],n;

inline void Insert(reg int x,const int val)
{
	while(x <= n)
	{
		tr[x] ^= val;
		
		x += lowbit(x);
	}
}

inline int Query(reg int x)
{
	int res = 0;
	
	while(x)
	{
		res ^= tr[x];
		
		x -= lowbit(x);
	}
	
	return res;
}

struct Node
{
	int L,R,id;
	
	Node(const int b=0,const int a=0,const int id_=0):L(a),R(b),id(id_){}
};

bool operator < (const Node& a,const Node& b){return a.R < b.R;}

Node Q[N + 42];

int a[N + 42],m,b[N + 42],tot = 1,sum[N + 42],last[N + 42],Pre[N + 42],ans[N + 42];

inline int Find(const int x)
{
	reg int l = 1,r = tot,mid;
	
	while(l < r)
	{
		mid = (l+r)>>1;
		
		if(b[mid] < x) l = mid+1;
		else r = mid;
	}
	
	return l;
}

int main()
{
	n = Read();
	
	for(reg int i = 1; i <= n ; ++i) a[i] = b[i] = Read();
	
	sort(b+1,b+n+1);
	
	for(reg int i = 2; i <= n ; ++i) if(b[tot] != b[i]) b[++tot] = b[i];//去重
	
	for(reg int i = 1; i <= n ; ++i) a[i] = Find(a[i]);//离散化
	
	for(reg int i = 1; i <= n ; ++i)
	{
		sum[i] = sum[i-1]^b[a[i]];
		Pre[i] = last[a[i]];
		last[a[i]] = i;
	}//记录上一次出现位置 
	
	m = Read();
	
	for(reg int i = 1; i <= m ; ++i) Q[i] = Node(Read(),Read(),i);
	
	sort(Q+1,Q+m+1);//保证后面询问的 r 都大于前面询问的 r。
	
	for(reg int i = 1,cur=1; i <= m ; ++i)
	{
		while(cur <= Q[i].R)
		{
			if(Pre[cur]) Insert(Pre[cur],b[a[cur]]);//删除前面已出现过的数字。
			
			Insert(cur,b[a[cur]]);
			
			++cur;
		}
		
		ans[Q[i].id] = (Query(Q[i].R)^Query(Q[i].L-1))^(sum[Q[i].R]^sum[Q[i].L-1]);
	}
	
	for(reg int i = 1; i <= m ; ++i) printf("%d\n",ans[i]);
	
	return 0; 
}
~~~



---

## 作者：Lonely_NewYear (赞：0)

# CF703D 题解

## 题目分析

题目要求个数为偶数的数字的异或和，其实就是出现奇数次的数字的异或和 $\oplus$ 出现过的所有数字的异或和。

但是可以发现出现奇数次的数字异或和其实就是全部数字异或和，因为出现偶数次的相当于没异或（一个数异或自己等于 $0$），所以答案其实就是所有数字的异或和 $\oplus$ 出现过的数字的异或和。

所以可以分两个小问题讨论。

### Part 1

所有数字的异或和。

因为我们要区间查询，所以可以使用前缀异或，设 $sum_i$ 表示前 $i$ 个数字的异或和，则 $x-y$ 内的数字的异或和就是 $sum_y\oplus sum_{x-1}$。

### Part 2

出现过的数字的异或和。

如果把每个数字只留最后一个，其他都改为0，那么这段数字的异或和其实就是我们要求的。但是注意问题会给出多次询问，修改后不能保证其他询问的正确，所以考虑离线。

对所有查询区间，以右端点从小到大排序，之后对每个区间求解时把之前的全都改为 $0$，具体实现可以记录一个 $last_i$ 表示数字 $i$ 上一次出现的位置，设当前位置数字为 $a_i$，则将位置 $last_{a_i}$ 上的数改为 $0$，并把 $last_{a_i}$ 更新为 $i$。但是注意 $a_i$ 的范围为 $1\le a_i\le 10^9$，所以需要离散化。

最后考虑如何对修改后的数组求异或和，因为需要支持修改，所以要使用线段树或者树状数组，这里使用树状数组。

完结撒花！

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
int a[1000001],s[1000001],t[1000001];
int lowbit(int i)
{
	return i&-i;
}
int query(int i)
{
	int sum=0;
	while(i>0)
	{
		sum=sum^t[i];
		i-=lowbit(i);
	}
	return sum;
}
void change(int i,int x)
{
	int y=query(i)^query(i-1);
	while(i<=n)
	{
		t[i]=t[i]^y^x;
		i+=lowbit(i);
	}
}
struct node
{
	int l,r,id;
}c[1000001];
bool cmp(node i,node j)
{
	return i.r<j.r;
}
int book[1000001],last[1000001],ans[1000001],sum[1000001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=a[i]^sum[i-1];
		change(i,a[i]);
		book[i]=a[i];
	}
	sort(book+1,book+n+1);
	int cnt=unique(book+1,book+n+1)-book-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(book+1,book+n+1,a[i])-book;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&c[i].l,&c[i].r);
		c[i].id=i;
	}
	sort(c+1,c+m+1,cmp);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		if(last[a[i]])change(last[a[i]],0);
		last[a[i]]=i;
		while(c[now].r==i)
		{
			int l=c[now].l,r=c[now].r;
			ans[c[now].id]=sum[r]^sum[l-1]^query(r)^query(l-1);
			now++;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

谢谢观看！

---

