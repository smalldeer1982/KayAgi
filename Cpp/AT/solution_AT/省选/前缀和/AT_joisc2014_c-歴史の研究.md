# 歴史の研究

## 题目描述

IOI 国历史研究的第一人——JOI 教授，最近获得了一份被认为是古代 IOI 国的住民写下的日记。JOI 教授为了通过这份日记来研究古代 IOI 国的生活，开始着手调查日记中记载的事件。

日记中记录了连续 $N$ 天发生的事件，大约每天发生一件。

事件有种类之分。第 $i$ 天发生的事件的种类用一个整数 $X_i$
表示，$X_i$ 越大，事件的规模就越大。

JOI 教授决定用如下的方法分析这些日记：

 - 选择日记中连续的几天 $[L,R]$ 作为分析的时间段；

 - 定义事件 $A$ 的重要度 $W_A$ 为 $A\times T_A$，其中 $T_A$ 为该事件在区间 $[L,R]$ 中出现的次数。

现在，您需要帮助教授求出所有事件中重要度最大的事件是哪个，**并输出其重要度**。

注意：教授有多组询问。

## 说明/提示

对于 $100\%$ 的数据，$1\le Q,N\le 10^5$，$1\le X\le 10^9$，$1\le L\le R\le N$。

## 样例 #1

### 输入

```
5 5
9 8 7 8 9
1 2
3 4
4 4
1 4
2 4```

### 输出

```
9
8
8
16
16```

## 样例 #2

### 输入

```
8 4
9 9 19 9 9 15 9 19
1 4
4 6
3 5
5 8```

### 输出

```
27
18
19
19```

## 样例 #3

### 输入

```
12 15
15 9 3 15 9 3 3 8 16 9 3 17
2 7
2 5
2 2
1 12
4 12
3 6
11 12
1 7
2 6
3 5
3 10
7 10
1 4
4 8
4 8```

### 输出

```
18
18
9
30
18
15
17
30
18
15
18
16
30
15
15```

# 题解

## 作者：_WA自动机 (赞：60)

## 回滚莫队
适用范围：
* 问题可以莫队。（询问可以离线，不带修改）
* 区间伸长的时候很好维护信息
* 区间缩短的时候不太好维护信息（如最大值，删除以后不知道次大值是多少)

怎么做呢？
* 首先，我们把询问按照莫队的顺序排序
* 这样询问被分成了若干个段落。每段内，询问的左端点在同一个块，右端点递增。
* 我们分段来处理：（设这一段的左端点为L[i],右端点是R[i]
* 每一段开始时，$l\leftarrow R[i]+1,r\leftarrow R[i]$，表示初始的空区间。
* 若左右端点都在这个块内的询问，我们直接暴力，显然$O(\sqrt n)$
* 现在，我们可以假定对于所有询问，均有$Q[j].r>R[i]$
* 每处理一个询问，我们先将r移动到该询问的右端点，保存下来此时的信息。
* 将l移动到询问的左端点，此时可以求出答案。
* $l\leftarrow R[i]+1$,用刚才保存的信息来恢复现场。
  
每段内，右端点单调递增，移动的时间复杂度$O(n)$,一共有$\sqrt n$段。左端点在同一块内，移动时间复杂度$O(\sqrt n)$，一共有n个左端点。暴力处理小段询问复杂度$O(\sqrt n)$。所以总的时间复杂度为$O(n\sqrt n)$，不变。而且可以看到，所有的操作都是在扩张区间，避免了收缩区间的麻烦，可以更方便地维护信息。

例题：[AtCoder 1219 历史研究](https://www.luogu.org/problemnew/show/AT1219)
代码在这里~
```cpp
#include <cstdio>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <algorithm>

using std::sort;
using std::unique;
using std::lower_bound;

const int maxn=2e5+100;

int a[maxn],b[maxn];
int L[maxn],R[maxn],blo[maxn];

struct Qry
{
    int l,r,id;
    bool operator< (const Qry& q){return blo[l]==blo[q.l]?r<q.r:l<q.l;}
}Q[maxn];

template<class T>inline T max(T a,T b){return a<b?b:a;}
template<class T>inline T min(T a,T b){return a<b?a:b;}

int cnt[maxn];
int64_t tmp;

inline void add(int x,int val=1)
{
    cnt[a[x]]+=val;
    tmp=max(tmp,(int64_t)cnt[a[x]]*b[a[x]]);
}

inline int64_t brute_force(int l,int r)
{
    static int c[maxn];
    int64_t ans=0;
    for (int i=l;i<=r;++i) ++c[a[i]];
    for (int i=l;i<=r;++i) ans=max(ans,(int64_t)c[a[i]]*b[a[i]]);
    for (int i=l;i<=r;++i) --c[a[i]];
    return ans;
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;++i)
        scanf("%d",a+i),b[i]=a[i];
    for (int i=1;i<=q;++i)
        scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    sort(b+1,b+n+1);
    int tot=unique(b+1,b+n+1)-b-1;
    // for (int i=1;i<=tot;++i) printf("%d ",b[i]);
    // putchar('\n');
    // printf("%d\n",tot);
    for (int i=1;i<=n;++i)
        a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
    int T=sqrt(n),bl=n/T;
    for (int i=1;i<=bl;++i)
        L[i]=R[i-1]+1,R[i]=L[i]+T-1;
    if (R[bl]<n) ++bl,L[bl]=R[bl-1]+1,R[bl]=n;
    for (int i=1;i<=n;++i)
        blo[i]=(i-1)/T+1;
    sort(Q+1,Q+q+1);
    static int64_t ans[maxn];
    for (int i=1,lp=1,r=0,l=0;i<=bl;++i)
    {
        memset(cnt,0,sizeof(cnt));
        r=R[i];
        tmp=0;
        // for (l=L[i];l<=R[i];++l) add(l,-1);
        while (blo[Q[lp].l]==i)
        {
            l=R[i]+1;
            if (Q[lp].r-Q[lp].l<=T)
            {
                ans[Q[lp].id]=brute_force(Q[lp].l,Q[lp].r);
                ++lp;
                continue;
            }
            while (Q[lp].r>r) add(++r);
            int64_t now=tmp;
            while (l>Q[lp].l) add(--l);
            ans[Q[lp].id]=tmp;
            tmp=now;
            while (l<=R[i]) --cnt[a[l++]];
            ++lp;
        }
    }
    for (int i=1;i<=q;++i) printf("%lld\n",ans[i]);
}
```


---

## 作者：PPL_ (赞：46)

# 前言

没错人手一份莫队，但我就是$TLE$

↑考场状态，$QAQ$

# 题目

[洛谷](https://www.luogu.com.cn/problem/AT1219)

[USOJ](http://222.180.160.110:1024/problem/4881)

# 前置知识

普通莫队

# 讲解

由于普通的莫队又要加，又要减，不好处理变小的最大值，处理的话就要带$\log$，然后就$TLE$了

所以要高级的：**回滚莫队**

望文生义：往回滚的莫队

首先分块，把询问区间先按左端点的块排序，相同按右端点从小到大排序

这样排序是为了方便我们就下来的操作

接下来依次处理排序后的询问

把莫队的$l,r$放到当前询问所属块的右端点，假设红色部分是询问区间：

![](https://cdn.luogu.com.cn/upload/image_hosting/qexw8m8f.png)

这样我们就只用扩张，最大值当然也很好求

到了第二个询问(绿色)：

![](https://cdn.luogu.com.cn/upload/image_hosting/0deopou8.png)

尽管$l$不知道在哪里，但它一定在这个块里面，所以我们直接~~退~~滚回右端点，但$r$由于我们是从小到大排序的，不需要回退

而上图的$l$到$r$的最大值我们是可以提前记录的

直接接着走就行了：

![](https://cdn.luogu.com.cn/upload/image_hosting/s4qy4nqv.png)

对于每次操作，$l$回到原点，$r$接着走就行了

如果我们当前这个询问的块是上一个询问的下一个块

即我们跨过了一个块

直接清空莫队用来计数的数组$($我的$tot$数组$)$

重新再来，重复上面的操作，只是块变成了下一个而已

就相当于我们对于每一个块做一次莫队(我的理解，但愿你不要。。。)

但这么打出来并不能过，要$\text{WA}$

我们考虑到还有这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/c2qiu633.png)

$\text{woc}$，$r$还要往左边走可咋整？

想想你的莫队会怎么走？

直接走啊！

先走$r$，把计数的数组先减，并不用更新答案

然后再走$l$，一定会把减成负数的计数的数组加回来(看图)，这个时候再更新答案就可以了

时间复杂度$O(n\sqrt{n})$

# 代码
```cpp
//12252024832524
#include <cmath> 
#include <cstdio>
#include <algorithm>
using namespace std; 

typedef long long LL;
const int MAXN = 100005;
int n,Q;
LL lsh[MAXN],lshtot;
int tot[MAXN];
int belong[MAXN];
LL ans[MAXN];
struct query
{
	int l,r,ID;
	bool operator < (const query &px) const{
		if(belong[l] != belong[px.l])
			return belong[l] < belong[px.l];
		return r < px.r;
	}
}q[MAXN];
struct node
{
	int x,ID;
}p[MAXN];

int Read()
{
	int x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(LL x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(LL x)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

bool cmp1(node x,node y)
{
	return x.x < y.x;
}
bool cmp2(node x,node y)
{
	return x.ID < y.ID;
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = Read();
	Q = Read();
	int sq = sqrt(n);
	for(int i = 1;i <= n;++ i)
	{
		p[i].x = Read();
		p[i].ID = i;
		belong[i] = (i-1) / sq + 1;
	}
	sort(p+1,p+n+1,cmp1); 
	for(int i = 1;i <= n;++ i)
	{
		if(p[i].x != lsh[lshtot])
			lsh[++lshtot] = p[i].x;
		p[i].x = lshtot;
	}
	sort(p+1,p+n+1,cmp2);
	for(int i = 1;i <= Q;++ i)
	{
		q[i].l = Read();
		q[i].r = Read();
		q[i].ID = i;
	}
	sort(q+1,q+Q+1);
	int l,r = 0;
	LL now = 0,lst = 0;
	for(int i = 1;i <= Q;++ i)
	{
		l = sq * belong[q[i].l];//该块右端点 
		if(belong[q[i].l] > belong[q[i-1].l])
		{
			for(int j = 1;j <= lshtot;++ j)
				tot[j] = 0;
			r = l - 1;
			lst = now = 0;
		}
		now = lst;
		while(r < q[i].r)
		{
			r++;
			tot[p[r].x]++;
			now = Max(now,tot[p[r].x] * lsh[p[r].x]);
		}
		while(r > q[i].r)
		{
			tot[p[r].x]--;
			r--;
		}
		lst = now;
		while(l > q[i].l)
		{
			l--;
			tot[p[l].x]++;
			now = Max(now,tot[p[l].x] * lsh[p[l].x]);
		}
		ans[q[i].ID] = now;
		for(int j = sq * belong[q[i].l]-1;j >= l;-- j)
			tot[p[j].x]--;
	}
	for(int i = 1;i <= Q;++ i)
	{
		Put(ans[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：42)

大家好，我不喜欢回滚莫队，所以我用普通莫队把这题给 A 掉了。复杂度 $O(n\sqrt m + m\sqrt n)$。

考虑普通莫队的问题在哪。对于一个莫队而言，本身可以看作是 $O(n\sqrt m)$ 组查询，$O(m)$ 组询问，同时本身每个数的「出现次数带权」这个东西本身可以线段树来维护，所以复杂度可以看作是 $O(n\sqrt m\log n+ m\log n+m\log m)$ （最后一个 $\log$ 是排序的，当然也可以写基排不过显然不是很有必要）。

考虑复杂度重心向查询偏移，于是本着根号平衡的思想，大概需要一个 $O(\sqrt n)$ 查询，$O(1)$ 修改的 ds 来维护这个信息。但是似乎普通的值域分块不可做。

考虑问题出在哪：无法在当前最大值被 `del` 之后，快速找出下一个最大值。所以可以想到要去借鉴带一个 $\log $ 的权值线段树的做法，即假设某个 $x$ 的出现次数是 $1,2,3\cdots cnt_x$ ，那么一开始把所有的 $x\cdot 1,x\cdot 2, x\cdot 3\cdots,x\cdot cnt_x$ 放在一起离散化，然后对这个离散化后的数组进行值域分块。因为 $\sum _xcnt_x=n$ 所以可以知道复杂度是对的。

于是最后复杂度是 $O(n\sqrt m+m\sqrt n)$ 。因为滥用 `vector` 以及 cache 十分不友好导致慢的一匹，用了扶苏的 `fastI/O` 也毛用没有/dk。

```cpp
typedef long long ll ;

#define il inline 

#define lwb lower_bound
#define upb upper_bound

#define vint vector <int>

#define mint map <int, int>

#define minttoll map <int, ll>

using IPT::qr;
using IPT::qra;
using IPT::qrs;
using IPT::qrdb;
using OPT::qw;
using OPT::qwa;
using OPT::qws;

il bool comp(const query &a, const query &b){
	return (bl[a.l] ^ bl[b.l]) ? bl[a.l] < bl[b.l] : 
		   ((bl[a.l] & 1) ? a.r < b.r : a.r > b.r) ;
}
il void add(const int &p){
	if (buc[tmp[p]] < 0){
		++ buc[tmp[p]] ; return ; 
	}
	int lval = base[tmp[p]][buc[tmp[p]]] ;
	int val = base[tmp[p]][++ buc[tmp[p]]] ; 
//	cout << val << " " << lval << endl ; 
	sump[val] ++ ; sumb[ blv[val] ] ++ ;
	sump[lval] -- ; sumb[ blv[lval] ] -- ;
}
il void del(const int &p){
	if (buc[tmp[p]] <= 0 ){
		-- buc[tmp[p]] ; return ; 
	}
//	if (buc[tmp[p]] + 1 >= base[tmp[p]].size()) cout << base <<buc[tmp[p]] << " " << p << ' ' << tmp[p] <<'\n', exit(0) ; 
	int lval = base[tmp[p]][buc[tmp[p]]] ;
	int val = base[tmp[p]][-- buc[tmp[p]]] ; 
	sump[val] ++ ; sumb[ blv[val] ] ++ ;
	sump[lval] -- ; sumb[ blv[lval] ] -- ;
}
il int ask(){
	int ob = 0 ; 
	for (int b = blv[V] ; b >= 0 ; -- b)
		if (sumb[b] > 0) { ob = b ; break ; } if (!ob) return 0 ; 
	for (int p = vr[ob] ; p >= vl[ob] ; -- p) if (sump[p]) return p ; 
}
int main(){
    qr(n) ; qr(m) ; B = n / sqrt(m) ;  
	for (int i = 1 ; i <= n ; ++ i) qr(g[i]) ; 
	for (int i = 1 ; i <= n ; ++ i) 
		bu[g[i]] ++, t[++ cnt] = 1ll * g[i] * bu[g[i]] ;
//	debug(t, 1, cnt, ' ', '\n') ;
	sort(t + 1, t + cnt + 1) ; bu.clear() ;
	for (int i = 1 ; i <= n ; ++ i){
		bl[i] = i / B ; bu[g[i]] ++ ; int w ; 
		w = upb(t + 1, t + cnt + 1, 1ll * g[i] * bu[g[i]]) - t - 1 ;
//		cout << g[i] << " " << w << '\n' ;
		if (bu[g[i]] == 1){
			base[w].push_back(0) ; 
			base[w].push_back(w) ; vu[g[i]] = w ; 
		}
		else base[vu[g[i]]].push_back(w) ; V = max(V, w) ;  
		su[w] = 1ll * g[i] * bu[g[i]] ; t[w] ++ ; 
	} 
	for (int i = 1 ; i <= m ; ++ i)
        qr(q[i].l), qr(q[i].r), q[i].id = i ;
    sort(q + 1, q + m + 1, comp) ; 
	for (int i = 1 ; i <= n ; ++ i) tmp[i] = vu[g[i]] ;
//	for (int i = 1 ; i <= n ; ++ i) if(buc[tmp[i]]) return 0 ; else buc[tmp[i]] ++ ; 
/*	for (int i = 1 ; i <= n ; ++ i){
		cout << g[i] << " " << tmp[i] << '\n' ;
		debug(base[tmp[i]], 0, base[tmp[i]].size() - 1, ' ', '\n') ;
	}return 0 ; */
//	debug(tmp, 1, n, ' ', '\n') ;
	B = sqrt(V) + 1 ; 
	for (int i = 1 ; i <= V ; ++ i){
		blv[i] = i / B + 1 ; 
		if (blv[i] != blv[i - 1])
			vr[blv[i - 1]] = i - 1, vl[blv[i]] = i ; 
	}
	int l = 1, r = 0 ; vr[blv[V]] = V ;
//	debug(blv, 1, V, ' ',  '\n') ;
//	debug(vl, 1, blv[V], ' ',  '\n') ;
//	debug(vr, 1, blv[V], ' ',  '\n') ;
//	while (l <= n) add(l ++) ;// cout << l << '\n' ;
    for (int i = 1 ; i <= m ; ++ i){
		while (l > q[i].l) add(-- l) ; 
		while (r < q[i].r) add(++ r) ;
		while (l < q[i].l) del(l ++) ; 
		while (r > q[i].r) del(r --) ;
		ans[q[i].id] = su[ ask() ] ; 
    }
    for (int i = 1 ; i <= m ; ++ i)
        qw(ans[i], '\n') ; return 0 ;
}

```

---

## 作者：Fido_Puppy (赞：12)

题目：[歴史の研究](https://www.luogu.com.cn/problem/AT1219)

OK，这题其实就是回滚莫队。

回滚莫队是啥？

其实就是一种莫队，可以只加不减（或只减不加）。

比如说 RMQ 问题就是典型的只加不减的回滚莫队。

至于普通莫队嘛，来个洛谷日报的[传送门](https://baijiahao.baidu.com/s?id=1611364100257622493&wfr=spider&for=pc)

首先定义如下的结构体：

```cpp
struct Q {
	int l,r,id;
};
```

回滚莫队分为以下几步：

+ 先按 l 所在的块从小到大排序，再按 r 从小到大排序。

```cpp
inline bool cmp(Q a,Q b) {
	if (belong[a.l]<belong[b.l]) return belong[a.l]<belong[b.l];
   else return a.r<b.r;
}
```

+ 一块一块的统计。

+ 每一块 r 是升序的，所以 r 只需要加就行了。

+ 再来考虑 l，只需要记录原先的值，每循环一次就赋值回去就行了。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],b[100001],g[100001],len=0,m,Ans[100001],belong[100001],Size,M;
long long B[100001],be[100001],d[100001];
struct Q {
	long long l,r,id;
}q[100001];
bool cmp(Q a,Q b) {
	if (belong[a.l]!=belong[b.l]) return belong[a.l]<belong[b.l];
	else return a.r<b.r;
}
long long query(long long x,long long y) {
	long long ans=0;
	for(long long i=x;i<=y;i++) {
		B[a[i]]++; ans=max(ans,be[a[i]]*B[a[i]]);
	}
	for(long long i=x;i<=y;i++) B[a[i]]--;
	return ans;
}
long long doit(long long Qnum,long long x) {
	for(long long i=1;i<=M;i++) b[i]=0;
	long long L=min(x*Size,n);
	long long i=Qnum,l=L+1,r=L;
	long long anss=0;
	for(;belong[q[i].l]==x;i++) {
		if (belong[q[i].l]==belong[q[i].r]) {
			Ans[q[i].id]=query(q[i].l,q[i].r);
			continue;
		}
		while (r<q[i].r) {
			++r;
			b[a[r]]++;
			anss=max(anss,b[a[r]]*be[a[r]]);
		}
		long long qwq=anss;
		while (l>q[i].l) {
			--l;
			b[a[l]]++;
			anss=max(anss,b[a[l]]*be[a[l]]);
			g[++len]=a[l];
		}
		Ans[q[i].id]=anss;
		anss=qwq;
		for(long long j=1;j<=len;j++) b[g[j]]--;
		len=0;
		l=L+1;
	}
	return i;
}
int main() {
	scanf("%lld%lld",&n,&m); Size=sqrt(n);
	for(long long i=1;i<=n;i++) scanf("%lld",a+i),d[i]=a[i],belong[i]=(i-1)/Size+1;
	sort(d+1,d+n+1);
	M=unique(d+1,d+n+1)-d-1;
	for(long long i=1;i<=n;i++) {
		long long T=lower_bound(d+1,d+M+1,a[i])-d;
		be[T]=a[i]; a[i]=T;
	}
	for(long long i=1;i<=m;i++) {
		scanf("%lld%lld",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	long long Qnum=1;
	for(long long i=1;i<=belong[n];i++) {
		Qnum=doit(Qnum,i);
	}
	for(long long i=1;i<=m;i++) printf("%lld\n",Ans[i]);
	return 0;
}
```

完结撒花！

---

## 作者：Acestar (赞：10)

## 分块

比回滚莫队简单，但时间复杂度为 $O(n\sqrt{n}logn)$，而回滚莫队是 $O(n\sqrt{n})$ 的。

- $f_{ij}$ 表示从第 $i$ 块的开头到 $j$ 的重要度的最大值。

- $cnt_{ij}$ 表示从第 $i$ 块的开头到序列末尾 $j$ 出现的次数。

- $cpy_{ij}$ 用来离散化

- $a_i$ 表示每种事件，离散化后是下角标。

- $b_i$ 表示事件 $a_i$ 的所在块。

可以预处理 $i$ 为每块开头的 $f_{ij}$ 和 $cnt_{ij}$。

对于每次询问的 $x,y$ ，只需要求出每个 $a_i$ 在这个区间中的重要度，然后取最大值即可。

重要度就是 $a_i×a_i$在 $[x,y]$ 中出现的次数。

如果 $x$ 是块的开头，就可以直接用 $cnt$，否则就把 $[x,y]$ 分成3段，

$1.$ $b_y$ 的开头到 $y$。

$2.$ $x$ 到 $b_x$的末尾。

$3.$ $b_x+1$ 到 $b_y-1$。

将 $1$ 和 $2$ 的和存进 $num_{a_i}$，$a_i$ 出现的个数就是 $cnt_{b_x+1,a_i}-cnt_{b_y,a_i}+num_{a_i}$

一个小容斥。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

const int N=1e5+10;
const int B=333;
typedef long long ll;

int n,q,Block,a[N],b[N];
ll f[B][N],ans,cpy[N],cnt[B][N],stk[N],num[N];

int main()
{
	scanf("%d%d",&n,&q);
	Block=sqrt(n);		//块的大小 
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]),b[i]=(i-1)/Block+1,cpy[i]=a[i];
	sort(cpy+1,cpy+1+n);				//排序 
	int u=unique(cpy+1,cpy+1+n)-cpy-1;	//去重 
	for(int i=1; i<=n; i++) a[i]=lower_bound(cpy+1,cpy+1+u,a[i])-cpy;
	for(int i=1; i<=b[n]; i++)
	{
		ll now=0;
		//预处理i为每块的开头的情况 
		for(int j=lower_bound(b+1,b+1+n,i)-b; j<=n; j++)
		{
			cnt[i][a[j]]++;
			now=max(now,cnt[i][a[j]]*cpy[a[j]]);
			f[i][j]=now;
		}
	}
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ans=f[b[x]+1][y];
		int top=0,tmp=lower_bound(b+1,b+1+n,b[y])-b;
		//y所在块的开头到y 
		for(int i=tmp; i<=y; i++)
			num[a[i]]++,stk[++top]=a[i];
		//x到x所在块的末尾 
		tmp=lower_bound(b+1,b+1+n,b[x]+1)-b;
		for(int i=x; i<tmp; i++)
		{
			num[a[i]]++;
			stk[++top]=a[i];
			ans=max(ans,(cnt[b[x]+1][a[i]]-cnt[b[y]][a[i]]+num[a[i]])*cpy[a[i]]);
		}
		//用栈记录下出现了哪些种类的事件，最后要清空 
		for(int i=1; i<=top; i++) num[stk[i]]=0;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：hyfhaha (赞：9)

# 莫队
简单分析：题面含有IOI（惊），可知此题是IOI（数字三角形）难度（逃）。

# 思路：回滚莫队
当然很多人都是抱着学回滚莫队的目标来看这道题的，所以这里介绍一下回滚莫队。

1、按莫队的思路讲询问排序。

2、查询时枚举每个区间，我们需要保证右端点是保持单调递增的，同时左端点每次在一个块中移动，以此来计算每个询问的值。

3、每一次到下一个块就讲左端点移回右端点，移的过程不需要再像莫队一样一个个移，只需要将莫队中改变的数据清0，然后将右端点赋值到左端点就可以了。

所以其实这道题是回滚莫队板子题。

# 代码

```cpp
#include<stdio.h>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
struct kkk{
    int x,y,id,flag,ans;
}a[1000001];
struct ggg{
    int a,b,p;
}a1[1000001];
int block,blo[1000001],v[1000001],vis[1000001],cnt[1000001],sum[1000001],aa[1000001];
int Vis[1000001],maxx,maxy,pos;
int n,C,m,l,r;
bool cmp1(ggg a,ggg b){
    return a.a<b.a||(a.a==b.a&&a.p<b.p);
}
bool comp(kkk a,kkk b){
    return a.id<b.id;
}
bool cmp(kkk a,kkk b){
    if(blo[a.x]!=blo[b.x])return a.x<b.x;
    return a.y<b.y;
}
void add(int x){
    vis[v[x]]++;maxx=max(maxx,vis[v[x]]*aa[x]);
}
void re(int x){vis[v[x]]--;}
int check(int l,int r){maxy=0;
    for(int i=l;i<=r;i++)Vis[v[i]]=0;
    for(int i=l;i<=r;i++){
        Vis[v[i]]++;
        maxy=max(maxy,Vis[v[i]]*aa[i]);
    }
    return maxy;
}
int Mo(int pos,int bl){
    maxx=0;int last=0,i=pos;
    for(int j=1;j<=n;j++)vis[j]=0;
    int L=min(block*bl,n);
    int l=L+1,r=L;
    for(;blo[a[i].x]==bl;i++){
        if(blo[a[i].x]==blo[a[i].y]){a[i].ans=check(a[i].x,a[i].y);continue;}
        while(r<a[i].y){add(++r);}
        last=maxx;
        while(l>a[i].x){add(--l);}
        a[i].ans=maxx;
        while(l<L+1)re(l++);
        maxx=last;
    }
    return i;
}
signed main(){
    int num;
    scanf("%lld%lld",&n,&m);block=sqrt(n);
    //离散化
    for(int i=1;i<=n;i++){scanf("%lld",&a1[i].a);aa[i]=a1[i].a;a1[i].p=i,blo[i]=(i-1)/block+1;num=blo[i];}
    sort(a1+1,a1+n+1,cmp1);
    for(int i=1,j=0;i<=n;i++)
    {
        if(i==1||a1[i].a!=a1[i-1].a)j++;
        v[a1[i].p]=j;
    }
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&a[i].x,&a[i].y);
        a[i].id=i;
    }
    pos=1;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=num;i++){
    	pos=Mo(pos,i);
    }
    sort(a+1,a+m+1,comp);
    for(int i=1;i<=m;i++){
        printf("%lld\n",a[i].ans);
    }
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：7)

## 前置知识
莫队（回滚莫队）
## 分析
其实这道题相当于回滚莫队的模板，甚至要比模板更模板。

那么，什么是回滚莫队呢？或者，什么时候可以使用回滚莫队呢？

### 回滚莫队使用条件

回滚莫队的使用条件通常有 $2$ 点：

+ 问题可以莫队~~废话~~

+ 插入容易维护，删除却很困难

### 回滚莫队食用方法

1. 使用莫队的预处理。我们把询问分成了若干块，每块之内左端点在一块之内，右端点递增。

2. 对于每一段询问，置开始的空区间为 $[R+1,R]$，其中 $R$ 指当前块右端点

3. 接下来对于每个询问进行处理：

$\space\space\space\space\space$ 1. 如果当前左右端点都在一块之内，暴力即可。

$\space\space\space\space\space$ 2. 否则，把当前区间右端点拓展到询问区间右端点，把结果存为变量 `last`。

$\space\space\space\space\space$ 3. 接下来，把当前区间左端点拓展到询问区间左端点，把结果存入答案。

$\space\space\space\space\space$ 4. 最后，移动左端点到原来位置，把当前答案设置为变量 `last`

### 回滚莫队复杂度

首先一共有 $\sqrt n$ 段询问。

如果在一个块则暴力拓展，复杂度 $O(\sqrt n)$

否则移动端点，总复杂度是 $O(n)$ 的。

于是，最后的复杂度是 $O(\sqrt n\times\sqrt n + n\times \sqrt n)=O(n\sqrt n)$ 的。

## 代码

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define lld long long
int N,M;
int B;
int idBlock[1000001];
lld ANS[1000001];
lld ans,last,cnt[1000001],cnt1[1000001];
lld len,a[1000001],v[1000001],srt[1000001];//离散化 
struct Req{
	int l,r,id;
}Q[1000001];
bool operator<(const Req &x,const Req &y){
	if(idBlock[x.l]==idBlock[y.l])return x.r<y.r;
	return idBlock[x.l]<idBlock[y.l];
}
void Insert(int id){
	++cnt[v[id]];
	ans=max(ans,cnt[v[id]]*a[id]);
}
void Remove(int id){
	--cnt[v[id]];
}
lld check(int l,int r){
	lld maxy=0;
	for(int i=l;i<=r;++i)cnt1[v[i]]=0;
	for(int i=l;i<=r;++i){
		++cnt1[v[i]];
		maxy=max(maxy,cnt1[v[i]]*a[i]);
	}
	return maxy;
}
int Move(int pos,int bl){
	ans=0;last=0;int i=pos;
	for(int j=1;j<=N;++j)cnt[j]=0;
	int L=min(B*bl,N);
	int l=L+1,r=L;
	for(;idBlock[Q[i].l]==bl;++i){
		if(idBlock[Q[i].l]==idBlock[Q[i].r]){
			ANS[Q[i].id]=check(Q[i].l,Q[i].r);
			continue;
		}
		while(r<Q[i].r)Insert(++r);
		last=ans;
		while(l>Q[i].l)Insert(--l);
		ANS[Q[i].id]=ans;
		while(l<=L)Remove(l++);
		ans=last;
	}
	return i;
}
int main(){
	scanf("%d%d",&N,&M);
	B=sqrt(N);
	for(int i=1;i<=N;++i)scanf("%lld",a+i),srt[i]=a[i],idBlock[i]=(i-1)/B+1;
	int num=idBlock[N];
	sort(srt+1,srt+N+1);
	len=unique(srt+1,srt+N+1)-srt-1;
	for(int i=1;i<=N;++i)v[i]=lower_bound(srt+1,srt+len+1,a[i])-srt;
	for(int i=1;i<=M;++i)scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	sort(Q+1,Q+M+1);
	int pos=1;
	for(int i=1;i<=num;++i)
		pos=Move(pos,i);
	for(int i=1;i<=M;++i)printf("%lld\n",ANS[i]);
	return 0;
}
```

---

## 作者：koishi_offical (赞：5)

嗯。。很明显的一道莫队题

当然我们会发现，对于这道题，添加元素很容易维护，但是删除的话。。。

所以我们需要一种可以更加强大的数据结构（算是吧） 

# 回滚莫队

首先我们按照块长为  $ \sqrt n$ 排序（但是要去掉奇偶优化）

这是我们就会惊奇的发现，你的询问的左端点所在的块的编号是单调递增的。 而对于左端点属于同一个块的询问，它们的右端点的编号也是单调递增的。

所以我们可以考虑将询问分成两大类

### 左端点和右端点位于同一块内

这个直接暴力解决就可以，因为一块最大 $ \sqrt n$ ，即使全部暴力时间复杂度也只是 $ O(n\sqrt n)$

暴力部分代码

```cpp
int force(int l,int r)
  {
      int res=0;
      int tcnt[N];
      for(int i=l;i<=r;i++) tcnt[typ[i]]=0;
      for(int i=l;i<=r;i++)
        {
            tcnt[typ[i]]++;
            res=max(tcnt[typ[i]]*a[i],res);
        }
      return res;
  }
```

### 左端点和右端点不位于同一块内

这个就有点麻烦了，考虑将区间分为两个部分，左块内和左块外。

对于左块内的部分：

每次询问前将操作指针 $ql$ 移至左端点所在块的下一个块的第一个元素处，然后我们就会惊奇的发现： 我们可以在左区间一直加元素而不必删除元素了（每次回复 $ql$ 的时候只需要保存一下就行了）

对于左块外的部分：

由于对于左端点属于同一个块的询问，它们的右端点是单调递增的。 所以我们只需要每次询问的左端点处于一个“新块” 的时候，将操作指针 $qr$ 移至左端点所在的块的最后一个元素。然后我们同样惊奇的发现，对于在左端点在同一个块内的所有操作，我们的 $qr$ 根本不需要往回走，也就是不需要删除


非暴力部分代码
```cpp
for(int k=1;k<=t;k++)//k代表左端点块的编号
    {
     l=br[k]+1,r=br[k];
     memset(cnt,0,sizeof(cnt));
     res=0;
     for(;belong[q[i].l]==k;i++)
       {
           if(belong[q[i].l]==belong[q[i].r])
             {
                 ans[q[i].id]=force(q[i].l,q[i].r);
                 continue;
             }
            while(r<q[i].r)
              {
                  r++;
                  cnt[typ[r]]++;
                  res=max(res,cnt[typ[r]]*a[r]);
              }
            int nowres=res;//每次对左块操作前先保存
            while(l>q[i].l)
              {
                 l--;
                 cnt[typ[l]]++;
                 res=max(res,cnt[typ[l]]*a[l]);
              }
            ans[q[i].id]=res;
            while(l<br[k]+1)
              {
                  cnt[typ[l]]--;
                  l++;
              }
            res=nowres;
       }
    }
```

时间复杂度为$ O(n\sqrt n)$

对了本题数据较大记得离散化


---

## 作者：__Hacheylight__ (赞：5)

题解中竟没有分块做法？ 本人来水一发~

这题分块挺显然的，一看就长着一副区间众数的脸

都是套路。。。

离散化是必须的，注意，查询请不要写成 $O(nlogn)$

没有修改，直接预处理

$f[i][j]$ 表示前 $i$ 个块数字 $j$ 出现了几次

$g[i][j]$ 表示块 $i$ 到块 $j$ 的答案

这两个数组显然都能在 $O(n\sqrt n)$ 的时间内完成

对于查询：

* 对于整块，那么答案已经在 $g$ 数组中预处理好
* 如果是零散元素，那么直接暴力加入桶中

就做完了，时间复杂度 $O(n\sqrt n)$

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
//#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int M = 320 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n, m, len, num ;
int f[M][N], a[N], tmp[N], bl[N], l[M], r[M], cnt[N] ;
ll g[M][M] ;
// f[i][j] 表示前 i 个块 j 出现的次数， g[i][j] 表示块 i 到 j 的答案

void lsh() {
	rep(i, 1, n) tmp[i] = a[i] ;
	sort(tmp + 1, tmp + n + 1) ;
	int nn = unique(tmp + 1, tmp + n + 1) - (tmp + 1) ;
	rep(i, 1, n) a[i] = lb(tmp + 1, tmp + nn + 1, a[i]) - tmp ;
}

void build() {
	len = sqrt(n) ; num = (n - 1) / len + 1 ;
	rep(i, 1, n) bl[i] = (i - 1) / len + 1 ;
	rep(i, 1, num) l[i] = (i - 1) * len + 1, r[i] = i * len ; r[num] = n ;
	lsh() ;
	rep(i, 1, num) {
		rep(j, l[i], r[i]) cnt[a[j]]++ ;
		rep(j, 1, n) f[i][j] = cnt[j] ;
	}
	ll ma ;
	rep(i, 1, num) {
		clr(cnt) ; ma = 0 ;
		rep(j, i, num) {
			rep(k, l[j], r[j]) {
				cnt[a[k]]++ ;
				ma = max(ma, (ll) cnt[a[k]] * tmp[a[k]]) ;
			}
			g[i][j] = ma ;
		}
	}
	clr(cnt) ;
}

ll query(int x, int y) {
	ll ma = 0 ;
	if (bl[x] == bl[y]) {
		rep(i, x, y) {
			cnt[a[i]]++ ;
			ma = max(ma, (ll) cnt[a[i]] * tmp[a[i]]) ;
		}
		rep(i, x, y) cnt[a[i]]-- ;
	} else {
		ma = g[bl[x] + 1][bl[y] - 1] ;
		rep(i, x, r[bl[x]]) {
			cnt[a[i]]++ ;
			ll sz = cnt[a[i]] + f[bl[y] - 1][a[i]] - f[bl[x]][a[i]] ;
			ma = max(ma, sz * tmp[a[i]]) ;
		}
		rep(i, l[bl[y]], y) {
			cnt[a[i]]++ ;
			ll sz = cnt[a[i]] + f[bl[y] - 1][a[i]] - f[bl[x]][a[i]] ;
			ma = max(ma, sz * tmp[a[i]]) ;
		}
		rep(i, x, r[bl[x]]) cnt[a[i]]-- ;
		rep(i, l[bl[y]], y) cnt[a[i]]-- ;
	}
	return ma ;
}

signed main(){
	scanf("%d%d", &n, &m) ;
	rep(i, 1, n) scanf("%d", &a[i]) ;
	build() ;
	while (m--) {
		int x, y ; scanf("%d%d", &x, &y) ;
		printf("%lld\n", query(x, y)) ;
	}
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
	6.逆向思维？
*/


```

---

## 作者：RemiliaScar1et (赞：4)

**2021-5-31 修改一处表述错误**

## 回滚莫队

回滚莫队适用于莫队解决问题时发现直接删除不好求答案的时候。

比如我们想用莫队维护一个集合最大值，插入一个数的时候只需要打擂台记录最大值即可，但是删除的时候就不容易直接寻找删除后的最大值。

当然例子中的这个具体问题也可以用个线段树啊堆啊什么的维护一下…… 。

### 歴史の研究

~~会滚的~~ 回滚莫队板子题。

观察其实可以知道，这题插入非常简单，而直接删除几乎是不可行的。

我们取块长 $\sqrt n$，仍然照着普通莫队的方法来对询问排序(去掉奇偶优化)。

排序后，询问左端点所在块的编号单调递增，左端点块编号相同的询问右端点单调递增。

此时我们考虑对每一个块内怎么去做。

![](https://pic.imgdb.cn/item/60ac557208f74bc1595a2e30.png)

我们考虑处理所有左端点在左边块内的所有询问。左边块内的询问有两种情况：

- 右端点在左块内

    ![](https://pic.imgdb.cn/item/60ac585e08f74bc15972c4f0.png)

    这个时候我们可以直接暴力求，由于块长最大 $\sqrt n$，所以处理单个这类询问的总复杂度最多 $O(\sqrt n)$。

- 右端点在左块外

    ![](https://pic.imgdb.cn/item/60ac58e108f74bc159780bfa.png)

    此时我们可以将询问分为两个部分：在左块内的部分，在右块内的部分。

    由于我们的排序策略，我们知道右块内部分是持续增加的。真正涉及到删除操作的是左端点。

    但是我们无法优秀地完成删除操作怎么办？

    此时，想想你在玩 galgame 玩出最坏的 BE 的时候，你是不是会选择回档？

    我们也可以让莫队“回档”，也就是我们的**回滚**操作：

    1. 在做块外的询问前，我们把莫队的两个指针 $l,r$ 设到右块的初始位置。
    1. 每遇到一个询问，我们先移动 $r$，这里只会涉及添加操作。移动完后，记录下当前的答案和状态数组(如记录数字出现次数之类的数组)。
    1. 移动左指针，记录这个询问答案。
    1. 最重要的一步：我们将**上一步涉及到所有的状态以及答案变量恢复到之前记录的状态**，然后继续做下一个询问。

    难度在回档的实现上。有可能直接撤销就完事了，也有可能复杂到要再整个数据结构什么的。

    当然，对于这个题，我们直接撤销即可。

总时间复杂度在块取 $\sqrt n$ 时 $O(n\sqrt n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;

int n,m;
struct Query
{
	int l,r,id;
} Q[N];
int poi[N],cnt[N];
vector<int> nums;
ll ans[N];
int block;

inline int get(int x)
{
	return x/block;
}

bool cmp(Query a,Query b)
{
	int al=get(a.l),bl=get(b.l);
	if(al!=bl) return al<bl;
	return a.r<b.r;
}

void add(int &x,ll &res)
{
	cnt[x]++;
	res=max(res,(ll)cnt[x]*nums[x]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&poi[i]),nums.push_back(poi[i]);
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(int i=1;i<=n;i++) poi[i]=lower_bound(nums.begin(),nums.end(),poi[i])-nums.begin();
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		Q[i]=(Query){l,r,i};
	}
	block=max(10,(int)sqrt(n));
	sort(Q+1,Q+1+m,cmp);

	for(int x=1;x<=m;)
	{
		int y=x;
		while(y<=m && get(Q[y].l)==get(Q[x].l)) y++;
		int right=get(Q[x].l)*block+block-1;

		/*处理块内询问*/
		while(x<y && Q[x].r<=right)
		{
			ll res=0;
			int id=Q[x].id,l=Q[x].l,r=Q[x].r;
			for(int k=l;k<=r;k++) add(poi[k],res);
			ans[id]=res;
			for(int k=l;k<=r;k++) --cnt[poi[k]];
			++x;
		}

		/*处理块外的询问*/
		ll res=0;
		int l=right+1,r=right;
		while(x<y)
		{
			int id=Q[x].id,ll=Q[x].l,rr=Q[x].r;
			while(r<rr) add(poi[++r],res);
			long long backup_=res;
			while(l>ll) add(poi[--l],res);
			ans[id]=res;
			while(l<right+1) --cnt[poi[l++]];
			res=backup_;
			++x;
		}
		memset(cnt,0,sizeof cnt);
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Prean (赞：3)

# 题意
设 $ a $ 的价值为 $ a \times cnt_a $（$ cnt_a $ 为 $ a $ 在区间中出现的次数），求区间种某种元素，使得这种元素的价值最大。

因为设计出现元素的次数，所以首先考虑莫队。

由于 Add 操作很好写，Del 操作不会写，所以我们考虑一种专门处理 Del 不容易处理的莫队：回滚莫队。

回滚莫队将询问区间分为两部分。设 $ [L,R] $ 的左端点 $ L $ 所在块的右端点为 $ p $，则讲区间分为 $ [L,p] $ 和 $ [p,R] $。

我们发现对于左端点所在块不变的情况，右端点 $ R $ 是单调递增的，可以直接 Add；而左端点的数量级在 $ O(\sqrt n) $ 级别，我们可以先只计算右边的区间的贡献，然后向左 Add，最后撤回向左的 Add。

因为向左的操作只有 $ O(\sqrt n) $ 个，所以撤回操作的复杂度也是 $ O(\sqrt n) $ 的。

不过这道题有一点儿细节，具体见代码。
```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
const int M=1e5+5;
int n,m,p,a[M],CB[M],lsh[M];long long cur,tmp,ans[M];
int len,v[M],mdf[M];bool vis[M];
inline long long max(const long long&a,const long long&b){
	return a>b?a:b;
}
struct Query{
	int L,R,p,id;
	inline bool operator<(const Query&it)const{
		return p==it.p?R<it.R:L<it.L;
	}
}q[M];
inline void AddR(const int&val){
	cur=max(cur,1ll*++CB[val]*lsh[val]);
}
inline void AddL(const int&val){
	if(!vis[val]){
		++len;mdf[len]=val;v[len]=CB[val];vis[val]=true;
	}
	tmp=max(tmp,1ll*++CB[val]*lsh[val]);
}
signed main(){
	register int i,j,id;
	scanf("%d%d",&n,&m);p=ceil(n/sqrt(2.0*m/3));
	for(i=1;i<=n;++i)scanf("%d",a+i),lsh[++len]=a[i];
	std::sort(lsh+1,lsh+len+1);len=std::unique(lsh+1,lsh+len+1)-lsh-1;
	for(i=1;i<=n;++i)a[i]=std::lower_bound(lsh+1,lsh+len+1,a[i])-lsh;len=0;
	for(i=1;i<=m;++i){
		scanf("%d%d",&q[i].L,&q[i].R);
		q[i].p=(q[i].L-1)/p+1;q[i].id=i;
	}
	std::sort(q+1,q+m+1);
	for(i=1;i<=m;++i){
		const int&QL=q[i].L,&QR=q[i].R;
		if(i==1||q[i].p!=q[i-1].p){
			for(j=1;j<=n;++j)CB[j]=0;
			id=q[i].p*p;cur=0;
		}
		if((QL-1)/p==(QR-1)/p){
			tmp=0;
			for(j=QL;j<=QR;++j)AddL(a[j]);
		}
		else{
			while(id<QR)AddR(a[++id]);tmp=cur;
			for(j=QL;j<=q[i].p*p;++j)AddL(a[j]);
		}
		for(j=1;j<=len;++j)CB[mdf[j]]=v[j],vis[mdf[j]]=false;
		ans[q[i].id]=tmp;len=0;
	}
	for(i=1;i<=m;++i)printf("%lld\n",ans[i]);
}
```

---

## 作者：Mars_Dingdang (赞：2)

一道回滚莫队的好题，刚学莫队，所以来发一篇题解巩固一下。

## 题目大意
给定区间 $[l,r]$，求区间中 $a \times T_a$ 最大的元素的出现次数 $T_a$。

$n,m\le 10^5$，$a_i\le 10^9$。

## 大体思路
首先看到区间中元素出现次数，发现这样的条件容易插入不容易删除，联想到区间众数的离线解法：回滚莫队。

以下是回滚莫队的大体思路：

首先，维护 $cnt$ 数组表示每个数的出现次数（同普通莫队），这样可以在 $O(1)$ 插入区间端点。本题中由于值域过大，因此要对序列 $a$ 进行离散化。

然后对询问分块。设块长为 $\sqrt n$，对于左右端点在一个块内的询问，直接暴力，复杂度 $O(\sqrt n)$。

对于其他的询问，对于左端点在同一个块中的，按照右端点排序，否则按照左端点排序，即将左端点在同一个块中的一起处理（注意此时奇偶性排序是错误的）。

具体操作如下：先将右指针 $R$ 移动到左端点所在块的最右端，然后 $R$ 向右移动插入，统计块外部份 $(ed, q_r]$ 区间，并将状态保存至 $lst,ans$。

然后令左指针 $L$ 移动到左端点所在块的最右端 $+1$ 位置，再向左插入，统计块内部分，更新状态 $ans$。然后将左端点的贡献撤回，即撤回对 $cnt$ 数组的更新，令 $ans \leftarrow lst$。

由于 $n, m$ 同阶，总复杂度 $O(n\sqrt n)$。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
const int B = 224;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, m, a[maxn], c[maxn], t[maxn];// 原数组，离散化后数组，离散化数组
int st[maxn], ed[maxn], id[maxn];// 分块
int ans, Ans[maxn], cnt[maxn], lst;// 离线莫队
int len, dlt;
struct node {
	int l, r, pos;
	bool operator <(const node &x)const{ // 排序 
		if(id[l] == id[x.l]) return r < x.r;
		return l < x.l;
	}
} q[maxn];
inline int work(int l, int r) { 
	//暴力处理左右端点在一个块里的区间 
	ans = 0;
	rep(i, l, r) {
		cnt[c[i]]++;
		ans = max(ans, cnt[c[i]] * a[i]);
	}
	rep(i, l, r) cnt[c[i]]--; // 撤销贡献 
	return ans;
}
signed main () {
	read(n); read(m);
	int num = 1; st[1] = 1;
	while(st[num] + B < n) {
		ed[num] = st[num] + B - 1;
		num++;
		st[num] = ed[num - 1] + 1;
	} ed[num] = n;
	rep(i, 1, num)
		rep(j, st[i], ed[i])
			id[j] = i;
	// 分块 预处理 
	rep(i, 1, n) {
		read(a[i]);
		c[i] = t[i] = a[i];
	}
	sort(t + 1, t + n + 1);
	len = unique(t + 1, t + n + 1) - t - 1;
	rep(i, 1, n)
		c[i] = lower_bound(t + 1, t + len + 1, c[i]) - t;
	//离散化
	rep(i, 1, m) {
		read(q[i].l); read(q[i].r);
		q[i].pos = i + dlt;
		if(id[q[i].l] == id[q[i].r]) { // 处理同一个块内 
			Ans[i + dlt] = work(q[i].l, q[i].r);
			i--; m--; dlt++;
		}
	} 
	sort(q + 1, q + m + 1);
	int L = 0, R = 0;
	rep(i, 1, m) {
		if(id[q[i].l] != id[q[i-1].l] || i == 1) {
			memset(cnt, 0, sizeof cnt);
			R = ed[id[q[i].l]];//右指针移动至块最右端 
			ans = lst = 0;
		}//若更新块，则清零 
		while(R < q[i].r) {
			++R; ++cnt[c[R]];
			ans = lst = max(lst, cnt[c[R]] * a[R]);
			// 插入块外部份 
		}
		L = ed[id[q[i].l]] + 1;//左指针移动至块右端加一 
		while(L > q[i].l) {
			L--; cnt[c[L]]++;
			ans = max(ans, cnt[c[L]] * a[L]);
			//向左插入块内部分 
		}
		Ans[q[i].pos] = ans;//记录答案 
		ans = lst;//撤销贡献 
		L = ed[id[q[i].l]] + 1;
		while(L > q[i].l) {
			L --;
			cnt[c[L]] --;//撤销贡献 
		}
	}
	rep(i, 1, m + dlt) writeln(Ans[i]);
	return 0;
}
```

---

## 作者：1saunoya (赞：2)

回滚莫队例题。

这题的意思大概是

设 $cnt_i$ 为 l ~ r 这个区间 $i$ 出现的次数

求$m$ 次询问 求 l~r 的 max {$a_i$ * $cnt_i$}

$n$ , $m$ 同阶 $1e5$

没有强制在线？ 我们考虑普通的莫队？如果最大值在某一段，当你把指针移到另一段，这个答案就失效了。

所以考虑回滚莫队。

回滚莫队的做法是

~~~
按左端点所在的块排序 如果相同 按右端点排序
然后对于每个块求解。弄个右指针在块的最右边。
分类讨论一下 如果左右指针共处一个块内 直接暴力 就是根号级别的
如果不在一个块内 由于右端点是递增的 考虑移动右端点
左边的贡献直接从 q[i].l ~ 块的最右边 暴力就行了
~~~

易证复杂度：
对于整块的询问 一共有 $\sqrt n$ 个块 右端点每次都是`当前块的右端点` 所以最多移动$n$的长度
对于每个询问 考虑左边的端点 由于按左端点排序 左端点和右端点最多相差 $\sqrt n$ 的长度
这样就可以做到 $O(n \sqrt n)$ 了

```cpp
// Isaunoya
#include<bits/stdc++.h>
using namespace std ;
using LL = long long ;
using uint = unsigned int ;
#define int long long
#define fir first
#define sec second
#define pb push_back
#define mp(x , y) make_pair(x , y)
template < typename T > inline void read(T & x) { x = 0 ; int f = 1 ; register char c = getchar() ;
  for( ; ! isdigit(c) ; c = getchar()) if(c == '-') f = -1 ;
  for( ; isdigit(c) ; c = getchar()) x = (x << 1) + (x << 3) + (c & 15) ;
  x *= f ;
}
template < typename T > inline void print(T x) {
  if(! x) { putchar('0') ; return ; }
  static int st[105] ;
  if(x < 0) putchar('-') , x = -x ;
  int tp = 0 ;
  while(x) st[++ tp] = x % 10 , x /= 10 ;
  while(tp) putchar(st[tp --] + '0') ;
}
template < typename T > inline void print(T x , char c) { print(x) ; putchar(c) ; }
template < typename T , typename ...Args > inline void read(T & x , Args & ...args) { read(x) ; read(args...) ; }
template < typename T > inline void sort( vector < T > & v) { sort(v.begin() , v.end()) ; return ; }
template < typename T > inline void unique( vector < T > & v) { sort(v) ; v.erase(unique(v.begin() , v.end()) , v.end()) ; }
template < typename T > inline void cmax(T & x , T y) { if(x < y) x = y ; return ; }
template < typename T > inline void cmin(T & x , T y) { if(x > y) x = y ; return ; }
const int N = 1e5 + 10 ;
int n , m ;
int a[N] , b[N] ;
struct node { int l , r , id ; } q[N] ;
int bl[N] ;
inline bool cmp(node x , node y) {
  if(bl[x.l] == bl[y.l]) return x.r < y.r ;
  return bl[x.l] <  bl[y.l] ;
}
int cnt[N] , cnt2[N] ;
inline int calc(int l , int r) { int ret = 0 ;
  for(register int i = l ; i <= r ; i ++) { cnt2[a[i]] = 0 ; }
  for(register int i = l ; i <= r ; i ++) { ++ cnt2[a[i]] ; cmax(ret , 1LL * (cnt2[a[i]]) * b[a[i]]) ; }
  return ret ;
} int unt ;
int ans , Ans[N] ;
inline void add(int x) {
  ++ cnt[a[x]] ;
  cmax(ans , 1LL * cnt[a[x]] * b[a[x]]) ;
} int now = 1 ;
inline void solve(int id) {
  int qr = min(id * unt , n) , pr = qr ; memset(cnt , 0 , sizeof(cnt)) ;
  ans = 0 ;
  for( ; bl[q[now].l] == id ; now ++) {
    if(bl[q[now].l] == bl[q[now].r]) { Ans[q[now].id] = calc(q[now].l , q[now].r) ; continue ; }
    while(pr < q[now].r) { add(++ pr) ; } int last = ans ;
    for(register int i = q[now].l ; i <= qr ; i ++) add(i) ;
    Ans[q[now].id] = ans ;
    for(register int i = q[now].l ; i <= qr ; i ++) -- cnt[a[i]] ;
    ans = last ;
  }
}
signed main() {
  read(n , m) ;
  for(register int i = 1 ; i <= n ; i ++) read(a[i]) , b[i] = a[i] ;
  sort(b + 1 , b + n + 1) ; int len = unique(b + 1 , b + n + 1) - b - 1 ;
  for(register int i = 1 ; i <= n ; i ++) a[i] = lower_bound(b + 1 , b + len + 1 , a[i]) - b ;
  unt = sqrt(n) ;
  for(register int i = 1 ; i <= n ; i ++) bl[i] = (i - 1) / unt + 1 ;
  for(register int i = 1 ; i <= m ; i ++) read(q[i].l , q[i].r) , q[i].id = i ;
  sort(q + 1 , q + m + 1 , cmp) ;
  for(register int i = 1 ; i <= bl[n] ; i ++) solve(i) ;
  for(register int i = 1 ; i <= m ;i ++) print(Ans[i] , '\n') ;
  return 0 ;
}


```

---

## 作者：FoXreign (赞：2)

题解里的dalao们基本都是用回滚莫队做的，但最近正好在复习分块，于是乎就用分块水了一发。

## 题目分析

典型的预处理无修改分块题，这类题目一般遵循这么个套路：

1 . 视情况离散化

2 . 预先处理出 $f[i][j]$ 表示第i块至第j块的答案， $cnt[i][j]$ 表示前 $i$ 块中 $j$ 出现的次数

3 . 对于每次询问 $[l,r]$ ，若在同一块内则暴力求取，否则我们令 $bl$ 、 $br$ 分别为 $l$ 、 $r$ 所在的区块，先取出中间整块的答案 $f[bl+1][br-1]$ ，再对两侧不完整块进行扫描更新答案

那么我们就可以轻松愉快的切掉这题了~

## AC代码
```
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = (x); i <= (y); i++)
#define down(i, x, y) for (int i = (x); i >= (y); i--)
#define full(x, y) memset(x, y, sizeof(x))
typedef long long ll;
const int maxn = 1e5 + 10;
const int maxb = 320;

int n, q;
ll mx, a[maxn], b[maxn], mp[maxn];
ll num, block, l[maxb], r[maxb], bel[maxn], f[maxb][maxb], cnt[maxb][maxn];

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

//预处理出每块间的最大重要度
//需要注意的是a是离散化后的数组，在计算重要度的时候要记得还原
void init()
{
    rep(i, 1, num)
    {
        mx = 0;
        rep(j, l[i], n)
        {
            mp[a[j]]++;
            mx = std::max(mx, mp[a[j]] * b[a[j]]);
            f[i][bel[j]] = mx;
        }
        full(mp, 0);
    }
}

void build()
{
    block = sqrt(n);
    num = (n - 1) / block + 1;
    rep(i, 1, n) bel[i] = (i - 1) / block + 1, cnt[bel[i]][a[i]]++;
    rep(i, 1, num) l[i] = (i - 1) * block + 1, r[i] = i * block;
    r[num] = n;
    //预处理出前i块中j的出现次数
    rep(i, 1, num) rep(j, 1, n) cnt[i][j] += cnt[i - 1][j];
}

ll query(int ql, int qr)
{
    int bl = bel[ql], br = bel[qr];
    ll res = 0;
    if (bl ^ br)
    {
        if (bl + 1 <= br - 1)
            res = f[bl + 1][br - 1];
        rep(i, ql, r[bl])
        {
            mp[a[i]]++;
            mx = (mp[a[i]] + cnt[br - 1][a[i]] - cnt[bl][a[i]]) * b[a[i]];
            res = std::max(res, mx);
        }
        rep(i, l[br], qr)
        {
            mp[a[i]]++;
            mx = (mp[a[i]] + cnt[br - 1][a[i]] - cnt[bl][a[i]]) * b[a[i]];
            res = std::max(res, mx);
        }
        full(mp, 0);
    }
    else
    {
        rep(i, ql, qr)
        {
            mp[a[i]]++;
            res = std::max(res, mp[a[i]] * b[a[i]]);
        }
        full(mp, 0);
    }
    return res;
}

int main(int argc, char const *argv[])
{
    n = read(), q = read();
    rep(i, 1, n) a[i] = b[i] = read();
    std::sort(b + 1, b + n + 1);
    int m = std::unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, n) a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b; //离散化
    build(), init();
    int ql, qr;
    rep(i, 1, q)
    {
        ql = read(), qr = read();
        printf("%lld\n", query(ql, qr));
    }
    return 0;
}

```


---

## 作者：zrzring (赞：1)

[更好的阅读体验](http://zrzring.cn/index.php/archives/579)

因为$max$运算无法撤销，所以我们的莫队不能有删点操作，如果只加点的话，考虑$r$是排过序的，可以直接扫过去，$l$在同一个块里，这样可以$l$所在的块外信息保留并随着$r$更新，块内信息暴力计算

记块大小为$B$，每次暴力计算$l$所在的块的复杂度贡献为$B$，$r$需要遍历块的数量次整个序列，块数量为$\displaystyle\frac{n}{B}$，取 $B = \sqrt{n}$，最优复杂度为$O(n\sqrt{n})$

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 2e6 + 10, inf = 0x3f3f3f3f;

const long long Linf = 0x3f3f3f3f3f3f3f3f;

inline int read() {
	bool sym = 0; int res = 0; char ch = getchar();
	while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
	return sym ? -res : res;
}

struct QRY {
	int l, r, id;
} qry[N];

int n, m, cnt[N], val[N], col[N], C, L[N], R[N], bel[N], b[N];

long long ans[N];

void init() {
	int B = sqrt(n);
	for (int i = 1; i <= n; i += B) {
		L[++C] = i; R[C] = i + B - 1;
	}
	for (int i = 1; i <= C; i++) {
		for (int j = L[i]; j <= R[i]; j++) bel[j] = i;
	}
}

bool cmp(QRY a, QRY b) {
	return bel[a.l] == bel[b.l] ? a.r < b.r : bel[a.l] < bel[b.l];
}

int main() {
	n = read(); m = read(); init();
	for (int i = 1; i <= n; i++) val[i] = read(), b[i] = val[i];
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) col[i] = lower_bound(b + 1, b + n + 1, val[i]) - b;
	for (int i = 1; i <= m; i++) qry[i] = (QRY){read(), read(), i};
	sort(qry + 1, qry + m + 1, cmp);
	for (int k = 1, i = 1; k <= C; k++) {
		int r = R[k]; long long res = 0, tmp = 0;
		while (bel[qry[i].l] == k) {
			while (r < qry[i].r) r++, cnt[col[r]]++, res = max(res, 1ll * cnt[col[r]] * val[r]);
			tmp = res;
			for (int j = qry[i].l; j <= min(R[k], qry[i].r); j++) cnt[col[j]]++, res = max(res, 1ll * cnt[col[j]] * val[j]);
			ans[qry[i].id] = res;
			for (int j = qry[i].l; j <= min(R[k], qry[i].r); j++) cnt[col[j]]--; res = tmp; i++;
		}
		for (int j = R[k] + 1; j <= r; j++) cnt[col[j]]--;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](http://222.180.160.110:1024/problem/4881)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~一眼莫队吧......~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难想到莫队。离线下来之后，用一个线段树维护区间中的数的个数，顺便维护一下答案，时间是$O(n\sqrt n\log_2n)$。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后发现上面的方法是无法再优化的了，我们得换个思路。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们发现，莫队的时候，最大的问题就是**加入一个新的元素很好维护，但是删除一个元素就很难**。于是，我们便想到，用**加法代替减法**。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑对于左端点在一个块$T$的询问$[l,r]$，我们将它分成两类：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.$l,r$在一个块里面，这个时候直接$O(\sqrt n)$暴力处理。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.$l,r$不在一个块里面。由于在排序的时候，$l$在同一个块的询问的$r$是升序的，所以直接移动$r$。而$l$可能是乱序的，我们又只能做加法，于是就可以缩小$l$移动的范围，转而用$r$来替换。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;具体来说，移动到一个新的块时，先将右指针置为$R(T)$，之后右指针就只会增大，中途处理**公共贡献**。每次处理一个$l,r$不在一个块的询问，就先正常移动右指针。然后将左指针重置为$R(T)+1$，并且移动到$l$，中途处理**单独贡献**。把两边的答案合到一起，得出当前询问的答案。之后就把左指针重新移回$R(T)+1$。当一个块的询问处理完之后，将左指针和右指针移到$R(T+1)+1$和$R(T+1)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这就是所谓的“回滚莫队”。具体可以再看[这篇博客](https://www.cnblogs.com/Parsnip/p/10969989.html)。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;可以证明时间复杂度时$O(n\sqrt n)$。  
# 代码
```cpp
#include <cmath>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> node;

#define xx first
#define yy second

const int MAXN = 1e5 + 5, MAXQ = 1e5 + 5, MAXSQRT = 320;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

int block;

struct query
{
	int l, r, i, b;
	query(){} query( const int L, const int R, const int I ) { l = L, r = R, i = I, b = l / block; }
	bool operator < ( const query & other ) const { return b == other.b ? r < other.r : l < other.l; }
}q[MAXQ];

node a[MAXN];

LL ans[MAXQ];
int right[MAXSQRT];
int X[MAXN], imp[MAXN], cnt[MAXN], ccnt[MAXN];
int N, Q, tot;

int main()
{
	read( N ), read( Q ); block = sqrt( N );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i].xx ), imp[i] = a[i].xx, a[i].yy = i, right[i / block] = i;
	for( int i = 1 ; i <= Q ; i ++ ) read( q[i].l ), read( q[i].r ), q[i].i = i, q[i].b = q[i].l / block;
	sort( a + 1, a + 1 + N ), sort( q + 1, q + 1 + Q );
	for( int i = 1 ; i <= N ; i ++ ) 
	{
		if( a[i].xx ^ a[i - 1].xx ) imp[++ tot] = a[i].xx;
		X[a[i].yy] = tot;
	}
	q[0].b = -1;
	LL tmp = 0;
	int ll = 1, rr = 0, segL, segR;
	for( int i = 1 ; i <= Q ; i ++ )
	{
		segL = q[i].l, segR = q[i].r;
		if( q[i].b ^ q[i - 1].b )
		{
			tmp = 0;
			while( rr > right[q[i].b] ) cnt[X[rr --]] --;
			while( ll < right[q[i].b] + 1 ) cnt[X[ll ++]] --;
            //重置指针
		}
		if( segL / block == segR / block )
		{
			for( int j = segL ; j <= segR ; j ++ ) ccnt[X[j]] = 0;
			for( int j = segL ; j <= segR ; j ++ ) ccnt[X[j]] ++;
			for( int j = segL ; j <= segR ; j ++ ) ans[q[i].i] = MAX( ans[q[i].i], 1ll * ccnt[X[j]] * imp[X[j]] );
		}
        //处理左右边界在同一个块里面的询问
		else
		{
			ll = right[q[i].b] + 1;
			while( rr < segR ) rr ++, tmp = MAX( tmp, 1ll * ( ++ cnt[X[rr]] ) * imp[X[rr]] );
			ans[q[i].i] = tmp;
			while( ll > segL ) ll --, ans[q[i].i] = MAX( ans[q[i].i], 1ll * ( ++ cnt[X[ll]] ) * imp[X[ll]] );
            //移动左指针
			while( ll < right[q[i].b] + 1 ) cnt[X[ll ++]] --;
            //回滚左指针
  		}
	}
	for( int i = 1 ; i <= Q ; i ++ ) write( ans[i] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：hl666 (赞：1)

附带权值的类区间众数问题？不是很好策啊

发现题目没有**强制在线**，而且也只有询问操作，那么可以考虑**莫队**

但是这里的莫队有一个很显著的特征，插入的时候很好维护答案，但是删除的时候不好回退

那么有没有什么办法可以让莫队避免删除呢，当然是有的，而且这可以解决一大类类似问题

考虑类似于一般莫队的分块操作，我们再排序时以左端点**所在块**为第一关键字，右端点为第二关键字

那么我们可以根据左端点所在块分别处理这些询问

首先如果左右端点在同一块内，那么很简单，直接暴力统计完了直接删光光就好了，这是$O(\sqrt n)$的

如果不是呢？由于此时的右端点是递增的，我们维护一个指针不停地往右边插入数即可，对于每一块的复杂度不会超过$O(n)$，由于一共只有$\sqrt n$块，所以总体还是$O(n\sqrt n)$的

可是这个时候左端点只是在同一块里并不是不变的。但是这部分的长度最多也是$\sqrt n$啊，再不济和暴力一样做了在删了就好了吗，一共$n$个询问所以最多也是$O(n\sqrt n)$的

所以这样的话复杂度就被压到了$O(n\sqrt n)$，顺便提一下这种神奇的莫队方法叫做**回滚莫队**，不过还是比较好理解的

CODE

```cpp
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstring>
#include<algorithm>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
typedef long long LL;
const int N=100005;
int blk[N]; struct ques
{
	int l,r,id;
	inline ques(CI L=0,CI R=0,CI Id=0)
	{
		l=L; r=R; id=Id;
	}
	inline friend bool operator <(const ques& A,const ques& B)
	{
		return blk[A.l]<blk[B.l]||(blk[A.l]==blk[B.l]&&A.r<B.r);
	}
}q[N]; int n,m,a[N],rst[N],num,now,size,bkt[N],tbkt[N]; LL ans[N],ret;
class FileInputOutput
{
	private:
		static const int S=1<<21;
		#define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
		#define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
		char Fin[S],Fout[S],*A,*B; int pt[25],Ftop;
	public:
		Tp inline void read(T& x)
		{
			x=0; char ch; while (!isdigit(ch=tc()));
			while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
		}
		Tp inline void write(T x)
		{
			if (!x) return (void)(pc('0'),pc('\n')); RI ptop=0;
			while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc('\n');
		}
		inline void Fend(void)
		{
			fwrite(Fout,1,Ftop,stdout);
		}
		#undef tc
		#undef pc
}F;
inline int min(CI a,CI b)
{
	return a<b?a:b;
}
Tp inline void maxer(T& x,const T& y)
{
	if (y>x) x=y;
}
inline LL calc(CI l,CI r,LL ret=0)
{
	RI i; for (i=l;i<=r;++i) tbkt[a[i]]=0; for (i=l;i<=r;++i)
	++tbkt[a[i]],maxer(ret,1LL*tbkt[a[i]]*rst[a[i]]); return ret;
}
inline void add(CI now)
{
	++bkt[a[now]]; maxer(ret,1LL*bkt[a[now]]*rst[a[now]]);
}
inline void solve(CI id)
{
	int qr=min(id*size,n),pr=qr; RI i; memset(bkt,0,sizeof(bkt));
	for (ret=0;blk[q[now].l]==id;++now)
	{
		if (blk[q[now].l]==blk[q[now].r]) { ans[q[now].id]=calc(q[now].l,q[now].r); continue; }
		while (pr<q[now].r) add(++pr); LL t=ret; for (i=q[now].l;i<=qr;++i) add(i);
		ans[q[now].id]=ret; for (i=q[now].l;i<=qr;++i) --bkt[a[i]]; ret=t;
	}
}
int main()
{
	//freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
	RI i; for (F.read(n),F.read(m),i=1;i<=n;++i) F.read(a[i]),rst[i]=a[i];
	sort(rst+1,rst+n+1); num=unique(rst+1,rst+n+1)-rst-1; size=(int)sqrt(n);
	for (i=1;i<=n;++i) blk[i]=(i-1)/size+1,a[i]=lower_bound(rst+1,rst+num+1,a[i])-rst;
	for (i=1;i<=m;++i) F.read(q[i].l),F.read(q[i].r),q[i].id=i;
	for (sort(q+1,q+m+1),now=i=1;i<=blk[n];++i) solve(i);
	for (i=1;i<=m;++i) F.write(ans[i]); return F.Fend(),0;
}
```



---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT1219)

谷 $\text{AT}$ 评测还没修好，跑到 $\text{LOJ}$ 上交了一发，[AC 记录](https://loj.ac/submission/913975)。

## 题意

- 给定一个序列，多次询问区间 $[l,r]$ 中 $A \times T_A$ 的最大值。（$T_A$ 表示 $A$ 在区间中出现的次数。）

## Sol

分析题目，可离线，插入方便删除难。

显然回滚莫队裸模板，甚至比模板题好写。

增量时每次维护 $T_A$，并不断更新。

每次增量复杂度 $O(1)$，整体复杂度 $O((n+m)\sqrt n)$。

对于本题，每次清空时只需最后将**右端点**滚回当前左端点块的右端点并沿途更新 $T_A$ 即可。

#### 注意点

全部开 $\text{int}$ 会爆 $0$。（例 $10^5$ 个 $10^9$ ）

全部开 $\text{long long}$ 即可。

不卡常，常数巨大选手可过。

---

代码。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+5;
ll n,m,a[N],b[N],len,l,r,sum,cnt[N],ans[N],lsh[N],qaq,qwq;
struct Question{ll l,r,id,pos;}q[N];
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
bool cmp(Question x,Question y){
	if(x.pos!=y.pos) return x.pos<y.pos;
	return x.r<y.r;
}
ll solve(ll l,ll r){
	ll awa[N]={0},tot=0;
	for(ll i=l;i<=r;++i){awa[a[i]]++;tot=max(tot,awa[a[i]]*b[a[i]]);}
	return tot;
}
void update(ll x){cnt[a[x]]++;sum=max(sum,cnt[a[x]]*b[a[x]]);}
void erase(ll x){cnt[a[x]]--;}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);len=(ll)sqrt(n);
	for(ll i=1;i<=n;++i) rd(a[i]),lsh[i]=a[i];
	for(ll i=1;i<=m;++i) rd(q[i].l),rd(q[i].r),q[i].id=i,q[i].pos=(q[i].l-1)/len+1;
	sort(lsh+1,lsh+n+1);
	qaq=unique(lsh+1,lsh+n+1)-lsh-1;
	for(ll i=1;i<=n;++i) b[lower_bound(lsh+1,lsh+qaq+1,a[i])-lsh]=a[i],a[i]=lower_bound(lsh+1,lsh+qaq+1,a[i])-lsh;
	sort(q+1,q+m+1,cmp);
	for(ll i=1,j=1;j<=(n-1)/len+1;++j){
		ll br=min(j*len,n);l=br+1,r=br,sum=0;
		while(q[i].pos==j){
			if(q[i].r<=br){
				ans[q[i].id]=solve(q[i].l,q[i].r);++i;
				continue;
			}
			while(r<q[i].r) ++r,update(r);
			qwq=sum;
			while(l>q[i].l) --l,update(l);
			ans[q[i].id]=sum;
			while(l<=br) erase(l),l++;
			sum=qwq;++i;
		}
		while(r>br) erase(r),r--;
	}
	for(ll i=1;i<=m;++i) wr(ans[i]),puts("");
	return 0;
}
```

---

## 作者：feicheng (赞：0)

## Description

给定长度为 $n$ 的序列 $a$，$m$ 次询问，求：

$$\max_{i\in[l,r]}cnt[a_i]\times a_i$$

即带权众数。

$1\le n,m\leq 10^5,1\le a_i \le 10^9$

## Solution

前置芝士：莫队（不会的可以戳[这里](https://www.cnblogs.com/hl-fc/p/14674384.html)）

我们考虑正常莫队的操作，可以发现加入一个数很舒服，但是删除操作就很……

所以我们考虑不删除，只加入。

接下来的内容比较抽象，建议画个图理解一下：

首先我们仍然将序列分成 $\frac n {\sqrt m}$ 段，对于每段的询问，我们分别处理。

首先我们先将莫队的左端点 $L$ 定位到该块的右端点 $+1$ 的位置，右端点 $R$ 定位到该块右端点的位置。

每段的询问无非分两种情况：

1. $[l,r]$ 在同一段内，此时我们直接暴力求答案，复杂度为块长。

2. $[l,r]$ 不在同一段内，我们先将 $R$ 移动到 $r$，记录下此时的答案 $A$，然后将 $L$ 移动到 $l$，此时的答案就是真正的答案。接着把 $L$ 定为该块的右端点 $+1$ 的位置，然后我们把 $L$ 左移带来的影响去除掉。就得出了答案，且删除操作对维护答案没有影响！由于块内右端点递增，所以复杂度可以保证。

## Code 

```cpp

constexpr int N = 1e5 + 10;
ll data[N],ans,Ans[N];
int n,m,a[N],cnt[N],bl[N],siz,tot,l,r,R;
struct Q{int l,r,id;}q[N];
inline int pos(const int x) {return (x-1)/siz + 1;}
inline void add(const int x) {++cnt[a[x]],ans = max(1ll*cnt[a[x]]*data[a[x]],ans);}
inline void del(const int x) {--cnt[a[x]];}
inline void Clear(const int x) {
    ans = 0,r = R = min(x*siz,n),l = r + 1;
    memset(cnt,0,sizeof cnt);
} //初始左右端点
inline ll Calc(const int l,const int r) {
    static int C[N];
   // std::cout <<"here "<< l << "  " << r << '\n';
    ll res = 0;
    for(int i = l;i <= r;++i) C[a[i]] = 0;
    for(int i = l;i <= r;++i) ++C[a[i]],res = max(res,1ll*C[a[i]]*data[a[i]]);
    return res;
}//同一块内爆算
inline void Init() {
    read(n,m),siz = sqrt(n),tot = pos(n);
    for(int i = 1;i <= n;++i) read(a[i]),data[i] = a[i],bl[i] = pos(i);
    std::sort(data+1,data+1+n);
    const int len = std::unique(data + 1,data + 1 + n) - data - 1;
    for(int i = 1;i <= n;++i) a[i] = std::lower_bound(data+1,data+1+len,a[i]) - data ;
    for(int i = 1;i <= m;++i)  read(q[i].l,q[i].r),q[i].id = i;
//    std::cout << "data[39] = " << data[a[39]] << '\n';
    std::sort(q + 1,q + 1 + m,[](Q a,Q b) {return bl[a.l]^bl[b.l] ? a.l < b.l : a.r < b.r;});
} //初始化
inline void Solve() {
    for(int i = 1,j = 1;i <= tot;++i) {
        Clear(i);ll tmp;
        for(;bl[q[j].l] == i;++j) {
            if(bl[q[j].r] == i) {
                Ans[q[j].id] =  Calc(q[j].l,q[j].r);
                continue;
            }//在同一块内
            while(r < q[j].r) add(++r);//先加入右端点
            tmp = ans;
            while(l > q[j].l) add(--l);//在加入左端点
            Ans[q[j].id] = ans;
            while(l <= R) del(l++);//去除影响
            ans = tmp;
        }
    }
}
int main(int argc,const char **argv) {
    Init(),Solve();
    for(int i = 1;i <= m;++i) print('\n',Ans[i]);
    return STD::flush(),0;
}
```

---

## 作者：qq734628996 (赞：0)

最近学回滚莫队，看的网上代码实在难受，打算自己写一篇题解

回滚莫队：在莫队的基础上，解决一类添加元素容易，删除元素难的问题，就本题来说，max操作添加容易复原难。但依然能使用莫队，方法是：对于每个块内的询问，右指针一直往右走，即添加元素，对于左边为添加的元素，改为枚举的方式。

这样复杂度仍是 $O(n\sqrt{n})$，因为右指针总耗时 $O(n\sqrt{n})$，跟普通莫队一样；左指针，每个元素最多需要 $O(\sqrt{n})$，移动 $n$ 次，复杂度也是 $O(n\sqrt{n})$.

具体实现跟普通莫队的模板稍有区别：1.需要维护多一个块区间的最右端点位置br数组；2.记录上一个块的bid，每次遍历到一个新的块，把cnt数组清空（这里复杂度 $O(n)$，共需清空 $\sqrt{n}$ 次），把左右指针指向当前块的最右端。3.如果右指针小于当前块最右端，添加元素，保存这时的答案（后面要恢复用），枚举左边部分的元素，逐个添加（注意右端点位置），更新答案，然后逐个删除，复原答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i++)
#define PER(i,n) for(int i = n-1; i >= 0; i--)
#define FOR(i,l,r) for(int i = l; i <= r; i++)
#define ROF(i,l,r) for(int i = r; i >= l; i--)
#define DEBUG(x) cout << #x << "=" << x << endl;
#define SHOW1(A,n) { REP(i,n) cout<<A[i]<<(i==n-1?'\n':' '); }
#define SHOW2(A,m,n) { REP(j,m) SHOW1(A[j],n) }
#define pb push_back
#define fi first
#define se second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (int)((x).size())
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int INF = 0x3f3f3f3f, MOD = 1000000007;
const double PI = acos(-1), EPS = 1e-6;
const int MAXN = 1e5+9, MAXM = 1e6+9;

int n,m,a[MAXN];
vector<LL> val;
struct query {
    int l,r,ind;
} q[MAXN];
int bsz,cnt[MAXN],belong[MAXN],br[MAXN];
LL ans,res[MAXN];
void prelude() {
    val.clear();
    unordered_map<int,int> mp;
    FOR(i,1,n) {
        if (!mp.count(a[i])) {
            val.pb(a[i]);
            mp[a[i]]=SZ(val)-1;
        }
        a[i]=mp[a[i]];
    }
    bsz=sqrt(n);
    FOR(i,1,n) {
        belong[i]=i/bsz;
        br[i/bsz]=i;
    }
}
bool cmp(query& a, query& b) {
    if (belong[a.l]!=belong[b.l]) return belong[a.l]<belong[b.l];
    return a.r<b.r;
}
void add(int x) {
    cnt[x]++;
    ans=max(ans,cnt[x]*val[x]);
}
void del(int x) {
    cnt[x]--;
}
void mt() {
    sort(q+1,q+1+m,cmp);
    int pre=-1;
    ans=0;
    int l,r;
    FOR(i,1,m) {
        int ql=q[i].l, qr=q[i].r, ind=q[i].ind;
        int bid=belong[ql];
        if (bid!=pre) {
            memset(cnt,0,sizeof(cnt[0])*SZ(val));
            ans=0;
            r=br[bid];
            l=br[bid];
            pre=bid;
        }
        while (r<qr) add(a[++r]);
        LL pans=ans;
        int ed=min(l,qr);
        FOR(j,ql,ed) add(a[j]);
        res[ind]=ans;
        FOR(j,ql,ed) del(a[j]);
        ans=pans;
    }
}

int main()
{
#ifdef LOCAL
    freopen("i.txt", "r", stdin);
    //freopen("o.txt", "w", stdout);
#endif //LOCAL

    while (scanf("%d%d", &n,&m)==2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        FOR(i,1,m) {
            int l,r; scanf("%d%d", &l,&r);
            q[i]={l,r,i};
        }
        prelude();
        mt();
        FOR(i,1,m) {
            printf("%lld\n", res[i]);
        }
    }

    return 0;
}
```


---

## 作者：WAMonster (赞：0)

## 回滚莫队板子题

核心思想就是：对于左端点所在的每个块，把当前区间缩到块尾+1的位置，然后当前右端点一直往右移，直到跑到查询区间右端点（由于左端点同块的右端点单调递增），记录好当前状态，左端点移完之后不用删除，只要把之前存的状态还原一下即可。

注意上取整是`ceil`（不管有没有用都要提醒一下，我在这里WA了十多遍）

work函数完全没必要，直接把莫队操作写在循环里也行qwq

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define maxn 100100
#define maxb 5050
#define ll long long
int aa[maxn], typ[maxn], cnt[maxn], cnt2[maxn], belong[maxn], lb[maxn], rb[maxn], inp[maxn];
ll ans[maxn];
struct query {
	int l, r, id;
} q[maxn];
int n, m, size, bnum;
#define isdigit(x) ((x) >= '0' && (x) <= '9')
inline int read() {
	int res = 0;
	char c = getchar();
	while(!isdigit(c)) c = getchar();
	while(isdigit(c)) res = (res << 1) + (res << 3) + (c ^ 48), c = getchar();
	return res;
}
int cmp(query a, query b) {
	return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : a.r < b.r; 
}
int main() {
	n = read(), m = read();
	size = sqrt(n);
	bnum = ceil((double) n / size);
	for(int i = 1; i <= bnum; ++i) {
		lb[i] = size * (i - 1) + 1;
		rb[i] = size * i;
		for(int j = lb[i]; j <= rb[i]; ++j) belong[j] = i;
	}
	rb[bnum] = n;
	for(int i = 1; i <= n; ++i) inp[i] = aa[i] = read();
	sort(inp + 1, inp + n + 1);
	int tot = unique(inp + 1, inp + n + 1) - inp - 1;
	for(int i = 1; i <= n; ++i) typ[i] = lower_bound(inp + 1, inp + tot + 1, aa[i]) - inp;
	for(int i = 1; i <= m; ++i) {
		q[i].l = read(), q[i].r = read();
		q[i].id = i;
	}
	sort(q + 1, q + m + 1, cmp);
	int i = 1;
	for(int k = 0; k <= bnum; ++k) {
		int l = rb[k] + 1, r = rb[k];
		ll now = 0;
		memset(cnt, 0, sizeof(cnt));
		for( ; belong[q[i].l] == k; ++i) {
			int ql = q[i].l, qr = q[i].r;
			ll tmp;
			if(belong[ql] == belong[qr]) {
				tmp = 0;
				for(int j = ql; j <= qr; ++j) cnt2[typ[j]] = 0;
				for(int j = ql; j <= qr; ++j) {
					++cnt2[typ[j]]; tmp = max(tmp, 1ll * cnt2[typ[j]] * aa[j]);
				}
				ans[q[i].id] = tmp;
				continue;
			}
			while(r < qr) {
				++r; ++cnt[typ[r]]; now = max(now, 1ll * cnt[typ[r]] * aa[r]);
			}
			tmp = now;
			while(l > ql){
				--l; ++cnt[typ[l]]; now = max(now, 1ll * cnt[typ[l]] * aa[l]);
			} 
			ans[q[i].id] = now;
			while(l < rb[k] + 1) {
				--cnt[typ[l]];
				l++;
			}
			now = tmp;
		}
	}
	for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
```

---

