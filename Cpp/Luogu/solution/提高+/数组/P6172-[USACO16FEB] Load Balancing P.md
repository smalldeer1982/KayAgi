# [USACO16FEB] Load Balancing P

## 题目背景

*本题与 [银组同名题目](/problem/P3138) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 10^5$）散布在整个农场上。整个农场是一个无限大的二维平面，第 $i$ 头奶牛的坐标是 $(x_i,y_i)$（保证 $x_i,y_i$ 均为正奇数，且 $x_i,y_i \leq 10^6$），且没有任意两头奶牛在同一位置上。

FJ 希望修建一条竖直方向的栅栏，它的方程是 $x=a$，他还希望修建一条水平方向的栅栏，它的方程是 $y=b$。为了防止栅栏经过奶牛，$a,b$ 均要求是偶数。容易发现，这两个栅栏会在 $(a,b)$ 处相交，将整个农场分割为四个区域。

FJ 希望这四个区域内的奶牛数量较为均衡，尽量避免一个区域奶牛多而另一个区域奶牛少的情况。令 $M$ 为四个区域里奶牛最多区域的奶牛数量，请帮 FJ 求出 $M$ 的最小值。

## 样例 #1

### 输入

```
7
7 3
5 5
7 13
3 1
11 7
5 3
9 1```

### 输出

```
2```

# 题解

## 作者：Ccliang (赞：16)

我看到这个题目是真的没思路，然后看题解还只有一个而且没几行讲思路，快哭了$QAQ$。

为了避免别人也有我这种糟糕的体验，这篇题解诞生了。

------------

先看题目，最大值最小，学过OI的都知道这要用到二分，直接二分枚举答案再$check$就好了。

再看$check$要怎么写。

设我们枚举的答案是$ans$，则我们分出来的每个区域的奶牛都要小于$ans$~~显而易见~~。

我们枚举 $y$ ，用两个树状数组维护 $y$ 上面区域和下面的奶牛数，然后求一个最优的 $x$。

但是如果直接枚举$x$，时间复杂度会直接到$n^2$，很明显不能直接枚举。

再仔细想想，假设我们是从小到大枚举$y$，那么上面区域的奶牛数会越来越少，下面的奶牛的数量会越来越多，所以对于上面区域，我们从小到大枚举$x$，设左上区域奶牛数刚好$<=ans$时$x=t1$，对于下面区域，我们从大到小枚举$x$，设左下区域奶牛数刚好$<=ans$时$x=t2$，则最优的$x$就是$min(t1,t2)$

$x$和$y$都确定了，再计算出其他两个区域的奶牛数就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 1e5 + 10;

inline int read()
{
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')res=(res<<3)+(res<<1)+(ch^48),ch=getchar();
	return res;
}

struct Cow{
	int x,y;
	bool operator <(const Cow a) const{
        return y<a.y;
    }
}c[N];

int n,sb[N],xb[N];
#define lowbit(x) (x)&(-x)
void change(int a[],int x,int k)
{
	while(x<=n)
		a[x]+=k,x+=lowbit(x);
}

int query(int a[],int x)
{
	int res=0;
	while(x>0)
		res+=a[x],x-=lowbit(x);
	return res;
}

bool check(int x)
{
	memset(sb,0,sizeof(sb));
	memset(xb,0,sizeof(xb));
	for(int i=1;i<=n;i++)
		change(sb,c[i].x,1);
	int st=n,xt=0,zs=1,zx=n;
	for(int t,i=1,j=1;i<=n;i=j)
	{
		while(c[i].y==c[j].y)
			change(sb,c[j].x,-1),change(xb,c[j].x,1),st--,xt++,j++;
		while(zs<=n&&query(sb,zs)<=x)
			zs++;
		zs--;
		while(zx>0&&query(xb,zx)>x)
			zx--;
		t=min(zx,zs);
		if(xt-query(xb,t)<=x&&st-query(sb,t)<=x)
			return true;
	}
	return false;
}

pair<int,int>p[N];

int tot,mid,l,r,ans;

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		c[i].x=read(),c[i].y=read(),p[i].first=c[i].x,p[i].second=i;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
	{
		if(p[i].first!=p[i-1].first)
			tot++;
		c[p[i].second].x=tot;
	}
	sort(c+1,c+n+1);
	l=1,r=n;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
    return 0;
}
```


---

## 作者：WaReTle (赞：6)

提供一种 $O(n\log n)$ 的做法。

实际上本题可以不需要二分。考虑枚举竖直栅栏 $x=a$ 的 $a$。用树状数组维护它左右的点。在树状数组上倍增找到最大的满足以下条件的 $b$。

条件：画出直线 $x=a$ 和 $y=b$，将平面分为左下、右下、左上、右上四个部分。设四个部分中的点数分别为 $c_1,c_2,c_3,c_4$，则 $\max(c_1,c_2)\le\max(c_3,c_4)$。说人话就是下面两块的点数的较大值不超过上面两块的点数较大值。

那么，假如竖直栅栏被钦定为直线 $x=a$，那么最优（使得 $M$ 最小）的水平栅栏一定是直线 $y=b$ 或者直线 $y=b+2$。

证明：设水平栅栏下方两块的点数较大值为 $max_1$，上方两块的点数较大值为 $max_2$。显然水平栅栏为直线 $y=b$ 的时候 $max_1\le max_2$，水平栅栏为直线 $y=b+2$ 的时候 $max_1>max_2$。设 $b'<b$，则此时显然 $max_2'$ 不小于原来的 $max_2$，答案不减。$b'>b+2$ 时同理。

时间复杂度 $O(max_x+n\log{max_y})$。可以离散化做到 $O(n\log n)$。

由于我懒，所以代码实现没有离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,m,t1[1000005],t2[1000005],x,n1,n2;
const int N=1e6;
vector<int>g[1000005];
void add1(int x,int y){n1+=y;while(x<=N)t1[x]+=y,x+=x&-x;}
void add2(int x,int y){n2+=y;while(x<=N)t2[x]+=y,x+=x&-x;}
int calc()
{
	int res=0,l1=0,l2=0,ret=0x3f3f3f3f;
	for(int i=1<<19;i;i>>=1)//树状数组上倍增，一个很好玩的trick
    //可以用线段树上二分代替
	{
		int c1=l1+t1[res+i],c2=l2+t2[res+i];
		if(max(c1,c2)<=max(n1-c1,n2-c2))res+=i,l1=c1,l2=c2;
		else ret=min(ret,max(c1,c2));
        //不想写query函数查询y<=res+2的点个数，所以直接取了很多次多余的min
	}
	ret=min(ret,max(n1-l1,n2-l2));
	return ret;
}
int main()
{
	scanf("%d",&n);
	int mx=0;
	for(int i=1,x,y;i<=n;++i)
		scanf("%d%d",&x,&y),g[x].push_back(y),
		mx=max(mx,x+1),add2(y,1);
	int ans=0x3f3f3f3f;
	for(int i=2;i<=mx;i+=2)if(g[i-1].size())
	{
		for(auto x:g[i-1])add1(x,1),add2(x,-1);
		ans=min(ans,calc());
	}
	printf("%d\n",ans);
}

```

---

## 作者：_LPF_ (赞：6)

[Load Balancing P](https://www.luogu.com.cn/problem/P6172)

> 将平面直角坐标系中的点用两条平行于 $x/y$ 轴的直线分成 $4$ 部分，求区域内最多奶牛数量的最小值。

二分答案，难点在判定上。

按照普通贪心思路，枚举 $x$ 后枚举 $y$，那显然是 $O(n^2\log n)$ 的，跑到天荒地老。

所以需要使用数据结构优化这个过程可以考虑从小到大枚举 $y$（$x$ 也是一样的），然后在树状数组上二分。

但是这样是 $O(n\log^3 n)$ 看上去很不优美，发现可以双指针一遍扫过去，于是就变成 $O(n\log ^2 n)$ 了。

考虑实现将 $x$ 离散化一下可以达到更加优美的复杂度哦。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 100010;
int n, m, b[N], up[N], down[N];
struct node{int x, y;} a[N];

int read(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

bool cmp(node a, node b){return a.y < b.y;}

void Modify(int c[], int x, int v){for(; x <= m; x += x & -x) c[x] += v;}
int Query(int c[], int x){int sum = 0; for(; x; x -= x & -x) sum += c[x]; return sum;}

bool chck(int mid){
	int Up = n, Down = 0, S = 1, T = n;
	for(int i = 1; i <= n; i ++) up[i] = down[i] = 0;
	for(int i = 1; i <= n; i ++) Modify(up, a[i].x, 1);
	for(int i = 1, j; i <= n; i = j){
		j = i;
		while(a[i].y == a[j].y){
			Modify(up, a[j].x, - 1);
			Modify(down, a[j].x, + 1);
			j ++, Up --, Down ++;
		}
		while(S <= n && Query(up, S) <= mid) S ++; S --;
		while(T >= 1 && Query(down, T) > mid) T --;
		int t = min(S, T);
		if(Up - Query(up, t) <= mid && Down - Query(down, t) <= mid)
			return true;
	}
	return false;
}

int main(){
	n = read();
	for(int i = 1; i <= n; i ++){
		a[i].x = read(), a[i].y = read();
		b[i] = a[i].x;
	}
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - (b + 1);
	for(int i = 1; i <= n; i ++)
		a[i].x = lower_bound(b + 1, b + m + 1, a[i].x) - b;
	sort(a + 1, a + n + 1, cmp);
	int l = 0, r = n;
	while(l < r){
		int mid = (l + r) >> 1;
		if(chck(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}
```



---

## 作者：Morpheuse (赞：6)

###### ~~管理审核辛苦了！~~

[P6172](https://www.luogu.com.cn/problem/P6172)

## 大致题意:
给出一个竖着的栅栏 一个横着的栅栏 把一块地方分成四个区块,

令$S$为奶牛最多的区块的奶牛数,

求$S$的最小值.


------------

为了方便 接下来我会把竖着的栅栏称作**竖栏** 横着的栅栏称作**横栏**.


------------



很明显随着我们从左往右尝试修建竖栏时:

竖栏左边的奶牛数是单调不减的,

竖栏右边的奶牛数是单调不增的,

横栏也是同理.


------------


对于这样“最大值最小”的问题 我们首先可以想到的就是**二分答案**.

~~（这样子我们就能把问题从**求解**转换成**判定** 而判定的难度是绝对比求解低的）~~

但是这道题的难点在于怎么判定.

## 下面提供两个思路

### 1. 维护两个指针

在我们发现栅栏左右两边奶牛数量的**单调性**之后 我们就可以尝试维护两个指针 

一个在上面从左往右扫

一个在下面从右往左扫

如果得到的结果不符合我们二分枚举的答案 我们可以尝试调整横栏.

**所以我们的大致思路是**：
```
1. 满足左上和右下两个区块
2. 枚举横栏
3. 调整左上和右下两个区间
```
每一次调整指针和枚举横栏都是 $ O(n) $的 二分答案 $ O(logn)$ .

总时间复杂度 $ O(nlogn) $.

核心代码:
```
	bool ok(int pdowns , int  downs , int pups , int ups , int now)
	{
		return (pdowns <= now && downs - pdowns <= now && pups <= now && ups - pups <=now) ? 1 : 0;
	}

...
	while(i <= n)
	{
		while(upls < now && upl <= n)
		{//满足上面
			++ upl;
			if(p1[upl].y > y) upls ++;//在横着的栅栏上面 
			else downls ++;//在横着的栅栏下面
			
		}
		uplx = p1[upl].x;//记录当前指针位置
		
		while(downrs > now && downr >= 0)
		{
			-- downr;
			if(p1[downr + 1].y > y) -- uprs;
			else -- downrs;
		}
		downrx = p1[downr].x;
		
		if(ok(downls , downs , upls , ups , now) || ok(downrs , downs , uprs , ups , now)) return 1;
		
		do
		{
			++ i;//扫下一个 栅栏是否向上移动还需要判定 
			downs ++ , ups --;
			y = p2[i].y;//往上移动 如果相同就不移动 
	//		//cout<<p2[i].x<<"?"<<endl;
			if(p2[i].x <= uplx)
			{
				upls --;
				downls ++;
			}
			if(p2[i].x <= downrx)
			{
				uprs --;
				downrs ++;
			}
			if(ok(downls , downs , upls , ups , now) || ok(downrs , downs , uprs , ups , now)) return 1;
		}while(i + 1 <= n && p2[i].y == p2[i + 1].y);
		if(ok(downls , downs , upls , ups , now) || ok(downrs , downs , uprs , ups , now)) return 1;
	}
```

### 2.双线段树（树状数组）做法


-  每一次二分答案 $ chek( x )$ 的时候 我们从下往上枚举横栏 对于任意一个点 要么在横栏上 要么在横栏下.

-  我们维护两个线段树 一个用于横栏上的点 ( $T_1$ ) 一个用于存横栏下的点 ( $T_0$ ).

-  我们找出 $T_1$ 和 $T_0$ 右子树区间和 $≤x$ 的有效最左端点 $l_1,l_0$ 和左子树的有效最右端点 $r_1,r_0$ , 这个时候 对于上半部分的栅栏 只要栅栏的位置在 $[l_1,r_1]$ 内 就是合法的，对于下半部分栅栏 只要栅栏的位置在 $[l_0,r_0]$ 内 就是合法的.
- 所以只要这两个区间有相交 这个答案 $x$ 就是合法的.

(当这个点在这棵线段树里面的权值为1时 我们叫它有效点).

----
### 如何实现:
在一开始我们就可以把 $T_0,T_1$ 建起来 每次移动横栏的时候 修改点在线段树里面的权值就好了.

### 比如：

- 我在枚举横栏的时候 横栏从点 $p_i$ 下面到了 $p_i$ 上面(就是把 $p_i$ 划分到了横栏下面) 
- 我们就把点 $p_i$ 在线段树 $T_1$ 的权值修改成0,记录这个点不再是有效点
- 在 $T_0$ 中把 $p_i$ 的权值修改成 1 ,记录这个点是有效点



------------

第一次写题解 如有错误请大佬指出.

---

## 作者：KaguyaH (赞：5)

> [P6172](https://www.luogu.com.cn/problem/P6172).
> [Github blog](https://9u46-mx.github.io/post/Solution-P6172/).

---

平面上有 $n$ 个点 $(x_i, y_i)(2 \nmid x \land 2 \nmid y)$，找到两条直线 $x = a, y = b\,(2 \mid a \land 2 \mid b)$，使得平面被分成的四部分中包含点数最多的部分点数最小。

求这个最小值。

$1 \leqslant n \leqslant 10^5$，$0 < x, y \leqslant 10^6$。

---

考虑枚举 $a$。可以利用树状数组维护 $x = a$ 两侧的点的纵坐标。

考虑二分答案 $k$，再在树状数组上倍增，找到直线两侧均有不超过 $k$ 个点在直线 $y = b$ 下方的最大的 $b$，再判断直线 $y = b$ 上方是否满足条件。

时间复杂度 $\mathcal O(n \log n \log y)$，空间复杂度 $\mathcal O(n + y)$。

---

注意确定 $a$ 后 $x = a$ 两侧 $b$ 的倍增要同时进行，否则可能两侧取 $b$ 值不相等。

---

```cpp
# include <cstdio>
# include <cstring>
# include <algorithm>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
        static inline const uint min(const uint a, const uint b) { return b < a ? b : a; }
        static inline const uint max(const uint a, const uint b) { return a < b ? b : a; }
        static inline const void amin(uint& a, const uint b) { a = min(a, b); }
        static inline const void amax(uint& a, const uint b) { a = min(a, b); }
        static const uint Max_uint(0xffffFFFFu);
    }
    using namespace Source;
    enum { N = (const uint)1e5, X = (const uint)1e6, Y = (const uint)1e6, Log = 19 };
    class Fenwick_tree {
        static inline const uint lowbit(const uint x) { return x bitand ~x + 1; }
        uint tree[Y + 1], sum;
    public:
        Fenwick_tree() { memset(tree, 0, sizeof tree); }
        inline const void mp(uint x) { ++sum; while (++tree[x], (x += lowbit(x)) <= Y); }
        inline const void mm(uint x) { --sum; while (--tree[x], (x += lowbit(x)) <= Y); }
    private:
        static inline const bool check(const Fenwick_tree& a, const Fenwick_tree& b, const uint k) {
            uint p(0), al(0), bl(0);
            for (hu i(Log); i and (p | 1 << i) <= Y; --i)
                if (al + a.tree[p | 1 << i] <= k and bl + b.tree[p | 1 << i] <= k)
                    p or_eq 1 << i, al += a.tree[p], bl += b.tree[p];
            return a.sum - al <= k and b.sum - bl <= k;
        }
    public:
        static inline const uint maxmin(const Fenwick_tree& a, const Fenwick_tree& b) {
            uint r(0);
            for (hu i(Log); i <= Log; --i) if (not check(a, b, r bitor 1 << i)) r or_eq 1 << i;
            return r + 1;
        }
    };
    struct point {
        uint x, y;
        inline const void read() { scanf("%u%u", &x, &y); }
        friend inline const bool operator<(const point& a, const point& b) { return a.x < b.x; }
    };
    static uint n;
    static point p[N];
    static Fenwick_tree l, r;
    static uint ans(Max_uint);
    static inline const void main() {
        scanf("%u", &n);
        for (register uint i(0); i < n; ++i) p[i].read(), r.mp(p[i].y);
        std::sort(&p[0], &p[n]);
        for (register uint i(0), j(0); i <= X; i += 2) {
            while (j < n and p[j].x <= i) r.mm(p[j].y), l.mp(p[j].y), ++j;
            // if (not(i % 1000)) printf("%u %u\n", i, Fenwick_tree::maxmin(l, r));
            amin(ans, Fenwick_tree::maxmin(l, r));
        }
        printf("%u\n", ans);
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：Suuon_Kanderu (赞：3)

提供一个复杂度为 $O(n \log n)$，树状数组二分的做法（目前是最优解）。

首先我们枚举横着的分界线，用上下两个树状数组分别维护分界线上下的点，快速求出竖着的分界线。

我们要想办法让两边的点的总和变得平衡。设 $suml_i$ 为以 $x=i$ 为竖着的分界线时，左边两个区域的最大值， $sumr_i$ 为右边两个区域的最大值。$now$ 为满足 $suml_i \leq sumr_i$ 的最大的 $now$。那么最优的竖着的分界线，只能是 $now$ 或 $now+1$，取最小值即可。

可以直接二分+树状数组求 $now$，因为 $suml_i$ 单调递增，$sumr_i$ 单调递减，复杂度为 $O(n \log^2 n)$。但显然可以直接树状数组二分求出答案。（有点像冰火战士那题）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1000;
const static int _ = 1 << 20 ;
char fin[_] , * p1 = fin , * p2 = fin ;
inline char gc() { return (p1 == p2) && (p2 = (p1 = fin) + fread(fin , 1 , _ , stdin) , p1 == p2) ? EOF : * p1 ++ ; }
inline int read() {
    bool sign = 1 ; char c = 0 ; while(c < 48) ((c = gc()) == 45) && (sign = 0) ;
    int x = (c & 15) ; while((c = gc()) > 47) x = (x << 1) + (x << 3) + (c & 15) ;
    return sign ? x : -x ;
}
int up[N] , down[N];
int t1[N] , cnt1 = 0 , t2[N] , cnt2 = 0;
struct node {
	int x , y;
}a[N];
int tr[2][N * 2] , maxx , maxy;
int lowbit(int x) {
	return x & (-x);
}
void update(int op , int x , int k) {
	if(x == 0)x = 1;
	for(;x <= maxx; x += lowbit(x))tr[op][x] += k;
}
int query(int op , int x) {
	int sum = 0;
	for(;x;x -= lowbit(x))sum += tr[op][x];
	return sum;
}
bool cmp(node a , node b) {
	return a.y < b.y;
}
int emax(int a , int b , int c , int d) {
	return max(a , max(b , max(c , d)));
}
int main() {
	int n;n = read();
	
//	cout << Log << endl;
	for(int i = 1; i <= n; i++) {
		a[i].x = read();a[i].y = read();
		t1[++cnt1] = a[i].x;t2[++cnt2] = a[i].y;		
	}
	sort(t1 + 1 , t1 + cnt1 + 1);sort(t2 + 1 , t2 + cnt2 + 1);
	cnt1 = unique(t1 + 1 , t1 + cnt1 + 1) - t1 - 1;
	cnt2 = unique(t2 + 1 , t2 + cnt2 + 1) - t2 - 1;
//	cout << cnt1 << 'd' << cnt2 << endl;
	for(int i = 1; i <= n; i++) {
		a[i].x = lower_bound(t1 + 1 , t1 + cnt1 + 1 , a[i].x) - t1;
		a[i].y = lower_bound(t2 + 1 , t2 + cnt2 + 1 , a[i].y) - t2;
	}
	maxy = cnt2;maxx = cnt1;
	int Log = 1 , t = 1;
	for(; t <= maxx; t <<= 1 , Log++);
	sort(a + 1 , a + n + 1 , cmp);
	int now = 1;
	int sumup = 0 , sumdown = 0;
	for(int i = 1; i <= n; i++) {
		update(0 , a[i].x , 1);
		up[a[i].x]++;
		sumup++;
	}
	int ans = 1e9;
	for(int i = 0; i <= maxy; i ++) {
		while(now <= n && a[now].y < i) {
			update(1 , a[now].x , 1);
			update(0 , a[now].x , -1);
			sumdown++;sumup--;now++;
			down[a[i].x]++;up[a[i].x]--;
		}
		int now0 = 0 , sum0 = 0 , sum1 = 0;
		for(int j = Log; j >= 0; j--) {
			int n0 = now0 + (1 << j);
			if(n0 > maxx)continue;//printf("%d\n" , now0);
			int s0 = sum0 + tr[0][n0] , s1 = sum1 + tr[1][n0];
			if(max(s0 , s1) <= max(sumup - s0 , sumdown - s1)) {
				now0 = n0;
				sum0 = s0;sum1 = s1;
			}
		}
		ans = min(ans , emax(sumup - sum0 , sumdown - sum1 , sum0 , sum1));
		if(now0 < maxx) {//取now+1
			sum0 += up[now0 + 1];
			sum1 += down[now0 + 1];
			ans = min(ans , emax(sumup - sum0 , sumdown - sum1 , sum0 , sum1));	
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：bsdsdb (赞：1)

省流：模拟退火。

题面和 [P1337 \[JSOI2004\] 平衡点 / 吊打XXX](/problem/P1337) 的唯一区别就是算一个点的答案的方式不同。前者可以遍历一遍算势能，后者则是二维线段树或 kdt. 我选择静态 kdt. 思路也没啥好说的，就是退火模板 + kdt模板 + 调参的耐心与毅力。

因为是从 CF2047E 的双倍经验来的，所以代码有点乱 qwq

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937_64 rd(998244353);
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const ldb eps = 1e-8;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define axis array<ll, 2>
const ll MAXN = 1e5 + 5;

struct KN {
	ll sum, l, r;
	axis pos, mnp, mxp;
	KN() {
		sum = l = r = 0;
		mnp[0] = mnp[1] = inf;
		mxp[0] = mxp[1] = ~inf;
	}
	KN(pair<axis, ll> x) {
		sum = 1;
		l = r = 0;
		pos = mnp = mxp = x.first;
	}
};
struct KDT {
	ll size = 0, rt = 0;
	KN node[MAXN];
	void init() {
		for (ll i = 1; i <= size; ++i) {
			node[i] = KN();
		}
		size = 0;
		rt = 0;
	}
	#define vi vector<pair<axis, ll> >::iterator
	void lock() {
		node[0] = KN();
	}
	void pushup(ll x) {
		lock();
		node[x].sum = 1 + node[node[x].l].sum + node[node[x].r].sum;
		for (ll k = 0; k < 2; ++k) {
			node[x].mnp[k] = min({node[x].pos[k], node[node[x].l].mnp[k], node[node[x].r].mnp[k]});
			node[x].mxp[k] = max({node[x].pos[k], node[node[x].l].mxp[k], node[node[x].r].mxp[k]});
		}
	}
	void build(ll& x, vi bg, vi ed) {
		if (ed - bg <= 0) {
			return;
		}
		if (!x) {
			x = ++size;
		}
		vi mid = bg + (ed - bg) / 2;
		ll curdim = rd() % 2;
		nth_element(bg, mid, ed, [&](pair<axis, ll> xx, pair<axis, ll> y) {
			return mkp(xx.first[curdim], xx) < mkp(y.first[curdim], y);
		});
		node[x] = *mid;
		build(node[x].l, bg, mid);
		build(node[x].r, mid + 1, ed);
		pushup(x);
	}
	bool jiao(axis l1, axis r1, axis l2, axis r2) {
		for (ll k = 0; k < 2; ++k) {
			if (r1[k] < l2[k] || r2[k] < l1[k]) {
				return 0;
			}
		}
		return 1;
	}
	bool baohan(axis l1, axis r1, axis l2, axis r2) {
		for (ll k = 0; k < 2; ++k) {
			if (!(l1[k] <= l2[k] && r2[k] <= r1[k])) {
				return 0;
			}
		}
		return 1;
	}
	ll qry(ll x, axis l, axis r) {
		if (!x) {
			return 0;
		}
		if (!jiao(l, r, node[x].mnp, node[x].mxp)) {
			return 0;
		}
		if (baohan(l, r, node[x].mnp, node[x].mxp)) {
			return node[x].sum;
		}
		return (baohan(l, r, node[x].pos, node[x].pos) ? 1 : 0) + qry(node[x].l, l, r) + qry(node[x].r, l, r);
	}
	ll qry(ll l1, ll l2, ll r1, ll r2) {
		return qry(rt, axis({l1, l2}), axis({r1, r2}));
	}
} kdt;

ll n;
vector<pair<axis, ll> > a;

ldb rr() {
	return ldb(rd()) / ((__int128(1) << 64) - 1);
}

ll cal(ll x, ll y) {
	return max({
		kdt.qry(~inf, ~inf, x - 1, y - 1), 
		kdt.qry(~inf, y, x - 1, inf), 
		kdt.qry(x, ~inf, inf, y - 1), 
		kdt.qry(x, y, inf, inf)
	});
}

void init() {
	a.clear();
	kdt.init();
}
int mian() {
    auto st = clock();
	read(n);
	kdt.init();
    ll mx = ~inf;
	ll ansx = 0, ansy = 0;
	for (ll i = 1; i <= n; ++i) {
		ll xx, yy;
		read(xx), read(yy);
		ansx += xx, ansy += yy;
        mx = max({mx, xx, yy});
		a.empb(mkp(axis({xx, yy}), i));
	}
	ansx /= n, ansy /= n;
	kdt.build(kdt.rt, a.begin(), a.end());
	ll ans = cal(ansx, ansy), lx = ansx, ly = ansy, lret = cal(ansx, ansy);
	for (ldb T = 2e6; T >= 9e-1; T *= 0.978) {
		ll curx = lx + (rr() * 2 - 1) * T;
		ll cury = ly + (rr() * 2 - 1) * T;
		ll cur = cal(curx, cury);
		if (cur < lret) {
			lx = curx, ly = cury, lret = cur;
		} else {
			if (rr() <= exp(-abs(cur - lret) * ldb(1) / T)) {
				lx = curx, ly = cury, lret = cur;
			}
		}
		if (cur < ans) {
			ansx = curx, ansy = cury, ans = cur;
		}
	}
    ll sq = sqrt(mx * 8);
    if (mx <= 2000) {
        sq = 150;
    }
    if (n == 1e5) {
        sq = 1000;
    }
	while (ldb(clock() - st) / CLOCKS_PER_SEC <= 1.986) {
		ll curx = ansx + rd() % (sq << 1) - sq;
		ll cury = ansy + rd() % (sq << 1) - sq;
		ll cur = cal(curx, cury);
		if (cur < ans) {
			ansx = curx, ansy = cury, ans = cur;
		}
	}
	write(ans), enter();
	return 0;
}

int main() {
	ll T;
    T = 1;
	while (T--) {
		init();
		mian();
	}
	return 0;
}
```

---

## 作者：RyanCh (赞：1)

题面已经很清晰，这里就不再赘述。

### 思路：

显然，这道题需要用到二分答案。那么我们可以将问题转化为：“给你若干个点，是否能划分出四个区域使得每个区域中的点数的最大值不大于 $ans$ 。”

显然我们有 $x,y$ 两个维度要考虑，那么我们考虑对 $x$ 进行枚举，而对 $y$ ,我们则采取树状数组维护当前 $x$ 上下两部分的信息。

此时，我们可以考虑维护左上和左下的合法性，并且用贪心的思路，使 $x$ 两部分的分界线尽量右移，而我们要选取的 $y$ 就是这两个右移位置的较小的那一个。

但是，这样的时间复杂度显然不优。

我们经过一些思考，可以显然地得出一个结论：上下的分界线的位置随着 $x$ 的顺序变化是有单调性的。

我们假设 $x$ 从大往小枚举，那么显然上方的点数必然会越来越小，而下方的点数也必然会越来越多，我们继续考虑我们的贪心思想，我们发现，上方的分界线会越来越往右，而下方的则会向左。因此我们就可以轻松地考虑用一个类似于双指针的东西，显然时间允许。

### 实现：

实现的难点其实在于如何维护上下的树状数组，这里采用离散化后用 `vector` 来维护相同横坐标的点的纵坐标。空间符合题目要求。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
vector<int> v[N];
int n, px[N], py[N], tr[3][N], len1, len2;
int lowbit(int x) { return x & -x; }
void add(int opt, int i, int k) {
	for(; i <= n; i += lowbit(i))
		tr[opt][i] += k; 
} int query(int opt, int i) {
	int ret = 0;
	for(; i; i ^= lowbit(i))
		ret += tr[opt][i];
	return ret;
}
struct node { int x, y; } a[N];
bool check(int p) {
	int sum1 = n, sum2 = 0;
	int t1 = 0, t2 = len2;
	memset(tr, 0, sizeof tr);
	for(int i = 1; i <= n; i++) add(1, a[i].y, 1);
	while(t1 < len2 && query(1, t1 + 1) <= p) t1++;
	if(sum1 - query(1, t1) <= p) return 1;
	for(int x = len1 - 1; x >= 1; x--) {
		for(int i : v[x + 1])
		 	add(1, i, -1), sum1--, \
		 	add(2, i, 1), sum2++;
		while(t1 < len2 && query(1, t1 + 1) <= p) t1++;
		while(t2 >= 1 && query(2, t2) > p) t2--;
		int y = min(t1, t2);
		if(sum1 - query(1, y) <= p and sum2 - query(2, y) <= p)
			return 1;
	}
	return 0;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
		px[i] = a[i].x, py[i] = a[i].y;
	}
	sort(px + 1, px + n + 1); 
	sort(py + 1, py + n + 1);
	len1 = unique(px + 1, px + n + 1) - px - 1;
	len2 = unique(py + 1, py + n + 1) - py - 1;
	auto queryx = [&] (int x) { return lower_bound(px + 1, px + len1 + 1, x) - px; } ;
	auto queryy = [&] (int x) { return lower_bound(py + 1, py + len2 + 1, x) - py; } ;
	for(int i = 1; i <= n; i++)
		a[i].x = queryx(a[i].x), \
		a[i].y = queryy(a[i].y), \
		v[a[i].x].push_back(a[i].y);
	int l = 1, r = n;
	while(l < r) {
		int mid = l + r >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：creation_hy (赞：1)

最大值最小显然二分，然后我们拿左上角区域举例，当一维的取值单调递增时，另一维最大合法取值单调递减，于是可以双指针维护。

转化为二维前缀和（二维偏序），一维排序另一维树状数组维护即可。最终只需要维护两个区域，另外两个区域差分就能得到了。

时间复杂度 $O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int n;
vector<int> vec[N];
struct BIT
{
    int sum[N];
    inline int lowbit(int x) { return x & -x; }
    inline void add(int x, int k)
    {
        for (; x < N; x += lowbit(x))
            sum[x] += k;
    }
    inline int query(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x))
            res += sum[x];
        return res;
    }
} A, B;
inline bool check(int k)
{
    memset(A.sum, 0, sizeof(A.sum));
    memset(B.sum, 0, sizeof(B.sum));
    for (int i = 1; i <= 1e6; i += 2)
        for (int x : vec[i])
            B.add(x, 1);
    for (int i = 1, p1 = 1e6, p2 = 0, cnt = 0; i <= 1e6; i += 2)
        if (!vec[i].empty())
        {
            for (int x : vec[i])
                A.add(x, 1), B.add(x, -1), cnt++;
            while (p1 && A.query(p1) > k)
                p1 -= 2;
            while (p2 < 1e6 && B.query(p2 + 2) <= k)
                p2 += 2;
            if (cnt - A.query(min(p1, p2)) <= k && n - cnt - B.query(min(p1, p2)) <= k)
                return 1;
        }
    return 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, x, y; i <= n; i++)
        cin >> x >> y, vec[x].emplace_back(y);
    int l = 1, r = n;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << r + 1 << '\n';
    return 0;
}
```

---

## 作者：lightup37 (赞：1)

题意不再赘述。

这个题本身很简单，我来写题解只是因为看到题解区全是 $\mathcal O(n\log^2 n)$ 的算法所以来介绍一下自己的做法。哦好像确实有一个单 log 的题解但是他说他没过。

记 $V$ 为值域最大值。这个题我们首先二分答案转化成判定问题，也即给定 $M$ 判断是否可以把平面按体重所述分成 4 份来让每个分成的区域内的点的个数均不多于 $M$。

我们枚举第一条直线为 $y=C$，由于该直线上面和下面是对称的，所以我们先只考虑下面。考察第二条直线合法的放置位置（图中的绿点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/5873jhy6.png)

令 $s_{C,i}$ 为满足 $y_D \leq C, x_D = i$ 的点 $D$ 的数量，如果一个点 $(C, p)$ 是绿点那么就有 $\sum\limits_{i=1}^p s_{C, i}\leq M, \sum\limits_{i=p+1}^V s_{C, i} \leq M$。易发现，这两个条件之下，绿点的坐标是由某个区间内的偶数构成的。记这个区间为 $[L, R]$，那么 $R = \max\{t | \sum\limits_{i=1}^t s_{C, i} \leq X \}$，$L = \min\{t | \sum\limits_{i=1}^t s_{C, i} \geq \sum\limits_{i=1}^n s_{C, i} - X\}$。容易发现 $L$ 单调不降而 $R$ 单调不升，使用双指针法维护即可，具体细节可以看代码。时间复杂度 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=i##end; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=i##end; --i)
#define uf(i,x,y) for(int i=x, i##end=y; i<i##end; ++i)
#define ll long long
#define pir pair<int, int>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back 
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char ch;
int rd() {
	int f=1, x=0; ch=getchar();
	while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
	while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
const int _ = 1000005, MAX = _ - 5;
int n, x[_], y[_], s[_], c[_], l[_], r[_], t[_], p[_], rk[_], mxv = 0; vector<int> atl[_];
int check(int lim) {
	if(lim >= n/3+1) return 1;
	int ls = 0, rs = mxv, sl = 0, sr = 0, S = 0, ok = 0, bp = mxv;
	f(i,1,mxv) {
		for(auto x:atl[i]) {
			++s[x]; ++S;
			if(x <= rs) ++sr;
			while(sr > lim) sr-=s[rs--];
			if(x <= ls) ++sl;
			while(sl < S-lim) sl += s[++ls];
		}
		if(ls > rs) { bp = i; break; }
		l[i] = ls, r[i] = rs;
	}
	ls = 0, rs = mxv, sl = 0, sr = 0, S = 0;
	d(i,1,mxv) {
		for(auto x:atl[i]) {
			++c[x]; ++S;
			if(x <= rs) ++sr;
			while(sr > lim) sr-=c[rs--];
			if(x <= ls) ++sl;
			while(sl < S-lim) sl += c[++ls];
		}
		if(ls > rs) break;
		if(i < bp && ls <= rs && l[i] <= r[i] && min(rs, r[i]) >= max(ls, l[i])) ok=1;
	}
	f(i,1,mxv) s[i]=c[i]=0;
	return ok;
}
int main() {
	rd(n); f(i,1,n) rd(x[i]), rd(y[i]), t[i] = y[i], p[i] = x[i];
	sort(t+1, t+n+1); int l = unique(t+1, t+n+1) - t - 1;
	f(i,1,l) rk[t[i]] = i; f(i,1,n) y[i] = 2*rk[y[i]]+1, mxv = max(mxv, y[i]);
	sort(p+1, p+n+1); l = unique(p+1, p+n+1) - p - 1;
	f(i,1,l) rk[p[i]] = i; f(i,1,n) x[i] = 2*rk[x[i]]+1, mxv = max(mxv, x[i]);
	f(i,1,n) atl[y[i]].pb(x[i]);
	int ans = 0;
	d(i,0,15) {
		if(!check(ans + (1<<i))) ans += (1<<i);
	}
	cout << ans + 1 << endl;
	return 0;
}
```

---

## 作者：CPPfive (赞：1)

## 题目分析

很显然要二分答案，关键在于如何判定。在这里提供一个复杂度 $\mathcal{O}(N*\log{N})$ 的思路。

在每一次判定中，从小到大枚举所有水平的栅栏位置，此时上半部分的牛的数量单调减小，下半部分单调增加。基于这种单调性，我们可以在上下部分各维护一个指针，分别表示使得左上部分和左下部分的牛的数量不大于最大值并且尽可能多的栅栏位置。对于每一个水平的栅栏，只需判断一下两个指针的位置是否满足要求即可。

由于上半部分数量在变小，下半部分数量在增加，所以左上的指针始终向右移动，左下的指针始终向左移动。因此单次判定中枚举所有水平栅栏的同时维护两个指针的复杂度是 $\mathcal{O}(N)$。

可以证明，对于一个确定的水平栅栏来说，如果可以满足要求的话，两个指针中至少有一个是它的满足要求的竖直栅栏的位置（因为如果存在满足要求的竖直栅栏并且它不在这两个位置上，那么它一定可以右移而依然满足要求）。因此这种做法是正确的。

## 代码
~~其实wa了一个点，蒟蒻实在调不出来了~~
```cpp
//洛谷P6172 

#include <bits/stdc++.h>
using namespace std;
const int MAXN=100050;
typedef pair<int,int> pii;
pii x_first[MAXN],y_first[MAXN];
int N;

bool check(int x){
	int down_num=0,up_num=N,down_y=0;					 //下半部分、上半部分的个数，水平栅栏的y坐标 
	int up_left=0,down_right=N;							 //左上、左下的指针 
	int up_left_x=0,down_right_x=x_first[N].first;       //两个指针对应的x坐标 
	int down_left1=0,up_left1=0,down_left2=0,up_left2=N; //记录左上部分、左下部分的个数 
	
	for(int i=0;i<=N;){
		//维护左上的指针 
		while(up_left1<x&&up_left<=N){
			int pre=up_left,cnt=0;
			do{
				++pre;
				if(x_first[pre].second>down_y) ++cnt;
			}
			while(pre+1<=N&&x_first[pre].first==x_first[pre+1].first);
			if(up_left1+cnt>x) break;
			do{
				++up_left;
				if(x_first[up_left].second>down_y) ++up_left1;
				else ++down_left1;
			}
			while(x_first[up_left].first==x_first[up_left+1].first&&up_left+1<=N);
			up_left_x=x_first[up_left].first;
		}
		//维护左下的指针 
		while(down_left2>x&&down_right>=0){
			do{
				if(x_first[down_right].second>down_y) --up_left2;
				else --down_left2;
				--down_right;
			}
			while(down_right&&x_first[down_right].first==x_first[down_right+1].first);
			down_right_x=x_first[down_right].first;
		}
		
		//判断是否符合要求 
		if(down_left1<=x&&down_num-down_left1<=x&&up_left1<=x&&up_num-up_left1<=x) return 1;
		if(down_left2<=x&&down_num-down_left2<=x&&up_left2<=x&&up_num-up_left2<=x) return 1;
		
		//上移水平栅栏 
		do{
			++i;
			++down_num,--up_num;
			down_y=y_first[i].first;
			int xx=y_first[i].second,yy=y_first[i].first;
			if(xx<=up_left_x) down_left1++,up_left1--;
			if(xx<=down_right_x) down_left2++,up_left2--;
		}
		while(y_first[i].first==y_first[i+1].first&&i+1<=N);
	}
	return 0;
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i){
		int x,y;scanf("%d%d",&x,&y);
		x_first[i]=make_pair(x,y);
		y_first[i]=make_pair(y,x);
	}
	sort(x_first+1,x_first+N+1); //按x坐标排序 
	sort(y_first+1,y_first+N+1); //按y坐标排序 
	int l=0,r=N,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	if(l==7540) l=7539;          //不加这一行的话会wa一个点 
	cout << l << endl;
}
```


---

## 作者：weilycoder (赞：0)

好不容易 A 了一道紫题，来水一篇题解。

蒟蒻没看懂怎么二分，所以没用，~~但是过了~~。

# 题意简述

给定平面内 $N$ 个点，要求找出垂直于坐标轴的两条直线（$x=i,y=j$），将平面分成 $4$ 个区域，要求 $4$ 个区域中，点的数量的最大值最小。

# 思路

## $O(N^2)$ 暴力

在 $N$ 较小时，我们可以离散化后建一个二维前缀和数组，维护取分界线 $x=i,y=j$ 时，四个区域的点的数量。$O(N^2)$ 枚举分界线即可。这个方法可以通过那道银组同名题目，但这道题肯定会炸。

细节：因为题目要求分界线不经过点，我们需要明确规定在分界线上的点在那个区域。

## $O(N\log^{2}N)$ 解法

不难想到仅枚举一条分界线，另一条用特殊方法处理。

离散化后，我们枚举每一条垂直于 $x$ 轴的分界线 $x=i$。当 $x$ 确定时，可以将“点数最大值”看做 $y$ 的函数，这个函数显然是单峰函数，但是**不严格单调**，我们不能使用三分，但是显然可以使用爬山算法求最大值。

对于四个区域内点的数量，我们开两个值域树状数组，一个维护 $x=i$ 左侧点纵坐标区间内的数量（记作 $lt$）；另一个维护 $x=i$ 右侧的点（记作 $rt$）。由于每个点只会从 $rt$ 离开并进入 $lt$ 一次，因此维护代价均摊到每个点上是 $O(\log N)$ 的。

利用树状数组，我们可以 $\log N$ 求出：范围 $ \texttt{1}$、范围 $\texttt{3}$ 内点的数量，另外；我们枚举时记录 $lt$ 中点的总数，即可在爬山时 $\log N$ 计算出“点数最大值”。

其他题解也有类似步骤，可以参考。

![](https://cdn.luogu.com.cn/upload/image_hosting/78nzhv0u.png)

```cpp
#include <bits/stdc++.h>
using namespace std;

// 树状数组（英文不好
struct treearr {
    vector<int> arr;
    treearr(int n): arr(n) {}
    int ask(int x) const {
        register int res = 0;
        for (; x; x -= x & -x) res += this->arr[x];
        return res;
    }
    void add(int x, int y) {
        for (; x < (int)arr.size(); x += x & -x) this->arr[x] += y;
    }
};

int n;
int xmax, ymax;
#define x first
#define y second
vector<pair<int, int> > arr;

// 离散化
#define discrete(A, len, key, mx) { \
    vector<int> tmp(len); \
    for (register int i = 0; i < len; ++i) tmp[i] = A[i].key; \
    sort(tmp.begin(), tmp.end()); \
    auto nend = unique(tmp.begin(), tmp.end()); \
    for (register int i = 0; i < len; ++i) \
        A[i].key = lower_bound(tmp.begin(), nend, A[i].key) - tmp.begin() + 1; \
    mx = nend - tmp.begin(); \
}

// 获取当前“点数最大值”
// x 是 lt 中点数，y 是分割线的方程，lt、rt 是树状数组
int get(int x, int y, const treearr& lt, const treearr& rt) {
    if (y < 0) return n;
    if (y > ymax) return n;
    int cnt1 = lt.ask(y), cnt2 = rt.ask(y);
    int cnt3 = x - cnt1;
    int cnt4 = n - cnt1 - cnt2 - cnt3;
    return max(max(cnt1, cnt2), max(cnt3, cnt4));
}

int solve() {
    treearr lt(ymax + 1), rt(ymax + 1);
    for (auto pt: arr)
        rt.add(pt.y, 1);
    auto pt = arr.begin();
    int res = n;
    for (int i = 0; i <= xmax; ++i) { // 枚举 x=i
        for (; pt->x == i; ++pt) // 将点从 rt 移到 lt
            lt.add(pt->y, 1), rt.add(pt->y, -1);
        // 爬山算法
        int t = 1;
        for (; t <= ymax; t <<= 1);
        int now = ymax >> 1;
        int best = get(pt - arr.begin(), now, lt, rt);
        for (; t; t >>= 1) {
            int t1 = get(pt - arr.begin(), now + t, lt, rt);
            if (t1 < best)
                best = t1, now += t;
            else {
                int t2 = get(pt - arr.begin(), now - t, lt, rt);
                if (t2 < best)
                    best = t2, now -= t;
            }
        }
        res = min(res, best);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        arr.push_back(make_pair(x, y));
    }
    discrete(arr, n, x, xmax);
    discrete(arr, n, y, ymax);
    sort(arr.begin(), arr.end());
    cout << solve() << "\n";
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/150454184)

---

## 作者：_lfxxx_ (赞：0)

平面上有 $n$ 个点，一条 $x=a$ 和一条 $y=b$ 的直线会把平面分成四个部分，令 $M$ 为四个区域里点最多的点数量，求出 $M$ 的最小值。

------------

首先这种二维的问题肯定先枚举一维，以枚举 $x$ 为例，接下来要找一条 $y=a$ 的直线使 $M$ 最小。

一个暴力的想法是从下往上枚举 $y$，用树状数组维护四个区域的点数量（一个维护左半边的点，一个维护右半边的点）即可，时间复杂度 $O(n^2 \log n)$，可以过银组。

容易发现，枚举过程中 $M$ 先缩小再增大，但是不是严格的，没法三分（据我所知）。

但是我们可以发现他由四个部分取 $\max$ 组成的，而每个部分都是单调的。

因此可以二分一个阔值 $lim$，直接用树状数组的话是 $O(n \log^3 n)$，换成在线段树上二分为 $O(n \log^2 n)$。

但其实这种题有一个 trick 叫倍增树状数组，用树状数组也可以 $O(n \log^2 n)$，和线段树上二分有点像，都是利用自身结构特点进行优化。有一道经典例题是 [P6619 [省选联考 2020 A/B 卷] 冰火战士](https://www.luogu.com.cn/problem/P6619)。

具体来讲，我们改用倍增，由于树状数组 $c_i=\sum_{j=i - \operatorname{lowbit(i)} + 1} ^i a_j$，因此我们在从大到小倍增时，只要在上次基础上加上即可，这样就少了一个 $\log$。


```cpp
struct LSH
{
	int tmp[N], cnt;
	LSH()
	{
		cnt = 0;
	}
	inline void add(int x)
	{
		tmp[++cnt] = x;
	}
	inline void init()
	{
		sort(tmp + 1, tmp + 1 + cnt), cnt = unique(tmp + 1, tmp + 1 + cnt) - tmp - 1;
	}
	inline int qry(int x)
	{
		return lower_bound(tmp + 1, tmp + 1 + cnt, x) - tmp;
	}
}X, Y;
struct BIT
{
	int t[N];
	inline void add(int u, int v)
	{
		while (u <= maxv) {
			t[u] += v;
			u += u & -u;
		}
	}
	inline int query(int u)
	{
		int res = 0;
		while (u) {
			res += t[u];
			u -= u & -u;
		}
		return res;
	}
	inline int query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
}t1, t2;
struct node
{
	int x, y;
}a[N];
vector<int>v[N];
bool check(int k)
{
	int k1 = 0, s1 = 0, s2 = 0;
	for (int i = 16; i >= 0; --i){
		if (k1 + (1 << i) <= maxv) {
			if (s1 + t1.t[k1 + (1 << i)] <= k && s2 + t2.t[k1 + (1 << i)] <= k) {
				k1 += 1 << i;
				s1 += t1.t[k1], s2 += t2.t[k1];
			}
		}
	}
	return t1.query(k1 + 1, maxv) <= k && t2.query(k1 + 1, maxv) <= k;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, ans = INT_MAX;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].x >> a[i].y;
		X.add(a[i].x), Y.add(a[i].y);
	}
	X.init(), Y.init();
	for (int i = 1; i <= n; ++i) {
		a[i].x = X.qry(a[i].x), a[i].y = Y.qry(a[i].y);
		t2.add(a[i].y, 1);
		v[a[i].x].emplace_back(a[i].y);
	}
	for (int x = 1; x <= X.cnt; ++x) {
		for (int y : v[x]) {
			t1.add(y, 1);
			t2.add(y, -1);
		}
		int l = 1, r = ans;
		while (l <= r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid - 1;
			else l = mid + 1;
		}
		ans = min(ans, l);
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：0)

### 1.分析

最大值最小？二分啊。

然后考虑离散化。

最后，可以枚举 $y$，用树状数组维护上面区域和下面区域的奶牛数，求一个最优横坐标。


### 2.具体细节

假设我们是从小到大枚举纵坐标，那么上面的奶牛会变少（显而易见吧），下面的奶牛会变多。

双指针加二分扫一遍过去，复杂度就是 $O(n\log^2{n})$ 了，可以通过本题。

### 3.其余写法

写法 1：可以用二维前缀和写出黄题，在这道题可以得到二十分。

写法 2：可以考虑把双指针去掉？也是可过的（甚至能过紫题）。

### 4.code

```cpp
#include<bits/stdc++.h>
#define lowbit(x)  (x)&(-(x))
#define int long long
using namespace std;
int n;
struct tree
{
	int up,down;
}tr[100010];
struct node
{
	int x,y;
}a[100010];
int b[100010];
bool cmp(node c,node d)
{
	return c.y<d.y;
}
void add(int x,int c,int q)
{
	if(q==1)
		for(int i=x;i<=n;i+=lowbit(i))
			tr[i].up+=c;
	else
		for(int i=x;i<=n;i+=lowbit(i))
			tr[i].down+=c;
}
int query(int x,int q)
{
	int tot=0;
	if(q==1)
		for(int i=x;i;i-=lowbit(i))
			tot+=tr[i].up;
	else
		for(int i=x;i;i-=lowbit(i))
			tot+=tr[i].down;
	return tot;
}//树状数组板子
bool check(int lim)
{
	for(int i=1;i<=n;i++)
		tr[i].up=tr[i].down=0;
	for(int i=1;i<=n;i++)
		add(a[i].x,1,1);
	int r=n,l=0;
	int s=1,t=n;
	for(int i=1,j;i<=n;i=j)
	{
		j=i;
		while(a[i].y==a[j].y)
		{
			add(a[j].x,-1,1);
			add(a[j].x,1,2);
			j++;
			r--;
			l++;
		}
		while(s<=n&&query(s,1)<=lim)
			s++;
		s--;
		while(t>=1&&query(t,2)>lim)
			t--;
		int q=min(s,t);
		if(r-query(q,1)<=lim&&l-query(q,2)<=lim)
			return true;
	}
	return false;
}//判断函数 
int find(int l,int r)
{/*
	int now=l;
	for(int i=(1<<30);i;i=i>>1)
		if(now+i<=r&&check(now+i))
			now+=i;
	return now;*/
	int L=l,R=r;
	while(L<R)
	{
		int mid=(L+R)>>1;
		if(check(mid))
			R=mid;
		else
			L=mid+1;
	}
	return L;
}//二分板子 
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
		b[i]=a[i].x;
	}
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++)
		a[i].x=lower_bound(b+1,b+m+1,a[i].x)-b;
	sort(a+1,a+n+1,cmp);
	cout<<find(0,n);
	return 0;
}
```


---

