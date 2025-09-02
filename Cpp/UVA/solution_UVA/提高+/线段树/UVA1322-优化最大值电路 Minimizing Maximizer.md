# 优化最大值电路 Minimizing Maximizer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4068

[PDF](https://uva.onlinejudge.org/external/13/p1322.pdf)

## 样例 #1

### 输入

```
1
40 6
20 30
1 10
10 20
20 30
15 25
30 40```

### 输出

```
4```

# 题解

## 作者：Buried_Dream (赞：3)

## Solution

我们考虑朴素的 dp。

设 $dp[i]$ 表示右端点为 $i$ 时所用的最小区间数。

转移很显然，对于每一个 $[l,r]$。

$$dp_r=\min(dp_i)+1(l\le i \le r)$$

但是朴素做复杂度是不能接受的。

我们考虑优化转移过程。

找 $\min(dp_i)$ 也就是找区间的最小值，然后转移，区间最小值我们想到了线段树。

于是用线段树来维护 dp 数组。

注意除最后一组数据外都多输出一个回车。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.8.10
**/
#include<cmath>
#include<queue>
#include<cstdio>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar 
using namespace std;
typedef long long ll;
//#define int long long
const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;
const int mod = 998244353;
const int INF = 0x3f3f3f3f;
const ll inf = 0x3f3f3f3f3f3f3f3f;
inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline int ksm(int a, int b) {int base = a % mod, res = 1; while(b){if(b & 1) res = (res * base) % mod; base = (base * base) % mod, b >>= 1;}return res % mod;}
inline int mul(int a, int b) {int base = a % mod, res = 0; while(b){if(b & 1) res = (res + base) % mod; base = (base + base) % mod, b >>= 1;}return res % mod;}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

namespace Seg {
	#define lson rt << 1
	#define rson rt << 1 | 1
	int Min[MAXN << 2];
	void update(int rt, int l, int r, int x, int k) {
		if(l > x || r < x) return;
		if(l == r) return Min[rt] = min(Min[rt], k), void();
		int mid = (l + r) >> 1;
		update(lson, l, mid, x, k);
		update(rson, mid + 1, r, x, k);
		Min[rt] = min(Min[lson], Min[rson]);
	}
	int Query(int rt, int l, int r, int L, int R) {
		if(l > R || r < L) return 0x3f3f3f3f;
		if(l >= L && r <= R) return Min[rt];
		int mid = (l + r) >> 1;
		return min(Query(lson, l, mid, L, R), Query(rson, mid + 1, r, L, R));
	}
}
using namespace Seg;

signed main() 
{
	int T = read();
	while(T--) {
		int M = read(), n = read();
		for(int i = 1; i <= (M << 2); i++) Min[i] = 0x3f3f3f3f;
		update(1, 1, M, 1, 0);
		for(int i = 1; i <= n; i++) {
			int l = read(), r = read();
			update(1, 1, M, r, Query(1, 1, M, l, r) + 1);
		}
		printf("%d\n", Query(1, 1, M, M, M));
		if(T) putchar('\n');
	}
	return 0;
}
```

---

## 作者：Zarinopl (赞：3)

入门经典习题9-23，线段树优化dp

找到覆盖区间的左端点ll然后进行dp寻找到达左端点所需的最小覆盖数，朴素方法O(n*m)

对一个Sorter，设dp[n]为左端点到达n所需的最小覆盖数；

方程为dp[Left]=min(dp[Left->Right]+1)，答案为dp[ll]

用线段树优化时间，滚动数组优化空间，时间复杂度O(m*log(n))，空间复杂度O(n)

上代码

```cpp
//#pragma GCC optimize("O2")
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 50529027
#define lop(c,m) for(int c=1;c<=(m);++c)
#define loop(c,m) for(int c=0;c<(m);++c)
#define down(c,m,s) for(int c=m;c>=(s);--c)
using namespace std;

int t,n,m,ll;
int seq[500001][2],dp[200001];
void buildtree(const int& l,const int& r,const int& now){
	if(l==r){
		dp[now]=inf;
		return;
	}
	buildtree(l,(l+r)>>1,now<<1),buildtree(((l+r)>>1)+1,r,now<<1|1);
	dp[now]=min(dp[now<<1],dp[now<<1|1]);
}
void updatetree(const int& tar,const int& val,const int& l,const int& r,const int& now){
	if(r<tar||tar<l) return;
	if(l==tar&&l==r){
		dp[now]=min(dp[now],val);
		return;
	}
	updatetree(tar,val,l,(l+r)>>1,now<<1),updatetree(tar,val,((l+r)>>1)+1,r,now<<1|1);
	dp[now]=min(dp[now<<1],dp[now<<1|1]);
}
int querytree(const int& lb,const int& rb,const int& l,const int& r,const int& now){
	if(r<lb||rb<l) return inf;
	if(lb<=l&&r<=rb) return dp[now];
	return min(querytree(lb,rb,l,(l+r)>>1,now<<1),querytree(lb,rb,((l+r)>>1)+1,r,now<<1|1));
}
inline int occu(int left){
	down(i,m,1) if(seq[i][1]>=left) left=min(left,seq[i][0]);
	return left;
}
signed main(signed,char**,char**){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		lop(i,m) scanf("%d%d",&seq[i][0],&seq[i][1]);
		ll=occu(n);
		buildtree(1,n,1);
		updatetree(n,0,1,n,1);//dp初始化，使dp[n]=0 
		down(i,m,1) updatetree(seq[i][0],querytree(seq[i][0],seq[i][1],1,n,1)+1,1,n,1);//寻找区间最小值并覆盖到区间左端点 
		printf("%d\n",querytree(ll,ll,1,n,1));
		if(t) putchar('\n');
	}
    exit(0);
}
```

---

## 作者：COsm0s (赞：2)

## $\mathcal{Solution}$

先思考朴素 dp。

我们设 $dp_i$ 为将最大值转移到 $i$ 时所用的价值。

则对于任意排序器 $[l,r]$，都有以下转移方程：

$f_r=\max\limits_{i=l}\limits^{r}{f_i}+1$。

上述算法复杂度 $O(n^2)$。

继续观察方程，发现转移量只和区间最小值有关。我们知道这是典型的 RMQ 问题，所以想到用线段树进行维护。

线段树维护 $dp$ 数组的最小值。在 dp 过程中，每次更新 $dp_r$，用线段树就是 $O(\log n)$，所以每次转移复杂度也为 $O(\log n)$。

所以总复杂度为 $O(n\log n)$。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 10;
int minn[N << 2];
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
namespace tree {
	inline void PushUp(int x) {
		minn[x] = min(minn[x << 1], minn[x << 1 | 1]);
	}
	inline void UpDate(int l, int r, int x, int aim, int C) {
		if(l == r) {
			minn[x] = min(minn[x], C);
			return ;
		}
		int mid = l + r >> 1;
		if(mid >= aim) UpDate(l, mid, x << 1, aim, C);
		else UpDate(mid + 1, r, x << 1 | 1, aim, C);
		PushUp(x);
	}
	inline int Query(int rt, int l, int r, int L, int R) {
		if(l >= L && r <= R) return minn[rt];
		int mid = (l + r) >> 1, ans = INT_MAX;
		if(L <= mid) ans = min(Query(rt << 1, l, mid, L, R), ans);
		if(R > mid) ans = min(ans, Query(rt << 1 | 1, mid + 1, r, L, R));
		return ans;
	}
}
namespace slove {
	int m, n;
	int main() {
		m = read(), n = read();
		memset(minn, 0x7f, sizeof minn);
		tree::UpDate(1, m, 1, 1, 0);
		for(int i = 1; i <= n; i ++) {
			int l = read(), r = read();
			tree::UpDate(1, m, 1, r, tree::Query(1, 1, m, l, r) + 1);
		}
		write(tree::Query(1, 1, m, m, m));
		putchar('\n');
		return 0;
	}
}
signed main() {
	int T = read();
	while(T --) {
		slove::main();
	}
	return 0;
}

---

## 作者：KSToki (赞：2)

# 题目大意
从 $m$ 个区间中选出尽量少的闭区间，使之完全覆盖闭区间 $[1,n]$，可以有重叠。
# 题目分析
首先设 $f[i]$ 为某个右端点覆盖到 $i$ 时最少选的数量，那么显然对所有 $l[i]\le j\le r[i]$ 有转移：$f[r[i]]=(\operatorname{min}{f[j]})+1$。这是标准的区间最小值，且值域仅为 $50000$，可以直接用线段树单点修改，维护区间最小值即可。

注意 UVA 的特性空行。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,minn[200001],l,r;
I void pushup(int k)
{
	minn[k]=min(minn[k<<1],minn[(k<<1)|1]);
}
I void update(int k,int l,int r,int x,int v)
{
	if(l==r)
	{
		minn[k]=min(minn[k],v);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=x)
		update(k<<1,l,mid,x,v);
	else
		update((k<<1)|1,mid+1,r,x,v);
	pushup(k);
}
I int query(int k,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
		return minn[k];
	if(l>y||r<x)
		return inf;
	int mid=(l+r)>>1;
	return min(query(k<<1,l,mid,x,y),query((k<<1)|1,mid+1,r,x,y));
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		memset(minn,127,sizeof(minn));
		update(1,1,n,1,0);
		for(R int i=1;i<=m;++i)
		{
			l=read();
			r=read();
			update(1,1,n,r,query(1,1,n,l,r)+1);
		}
		putint(query(1,1,n,n,n));
		if(T)
			cout<<endl;
	}
	return 0;
}
```

---

## 作者：☯☯枫☯☯ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA1322)

[欢迎踩博客 and 更好的阅读体验](https://www.cnblogs.com/lbh2021/p/15024700.html)

**算法分析：线段树优化 dp**

先提醒一下**坑点：**

- 题中 Sorter 的顺序不可改变。

**一些约定：**

- 记第 $k$ 个 Sorter 的左右端点为 $l_k$，$r_k$，长度为 $len_k$。

首先分析 dp。我们关心的是能对目标序列全部排序的最少 Sorter 个数，但与第几个无关，因此我们设计状态 $dp_i$ 表示**将目标序列前 $i$ 个数进行排序的最少 Sorter 个数**（即右端点为 $i$）。对于第 $k$ 个 Sorter，有：

$$dp_{r_k}=\min(dp_j+1),j\in (l_k,r_k)$$

初始值为 $dp_1=0,dp_i=+\infty,(i\ne1)$，边界为 $dp_n$。

此时，对于每一个 Sorter，都要进行 $r_k-l_k+1$ 次检查，时间复杂度为 $\mathcal{O}(m\times \sum\limits_{k=1}^nlen_k)$。显然超时。

考虑优化转移。

在暴力转移时，我们是从一段连续区间内取一个最小值。需要区间修改，区间查询最小值的操作。显然，线段树可以完成这个任务。于是我们用线段树代替循环进行查找和转移。我们可以直接查询 $l_k\to r_k$ 这一段 $dp$ 的最小值 $x$，然后再把 $x+1$ 作为新的 $dp$ 值储存到对应的区间上。最后答案就是 $1\to n$ 的最小值。

具体见代码：

```cpp
#include<cstdio>
#include<ctype.h>
#include<algorithm>
#include<iostream>
#include<cstring>
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);++i)
using namespace std;
inline int read();
const int N=5e5+5,inf=1e9;
int n,m,dp[N],ans;
struct P {
	int l,r;
} a[N];
namespace tree {
#define ls (x<<1)
#define rs (x<<1|1)
	const int P=5e4+10;
	struct P {
		int l,r,val,lz;
	} f[P<<2];
	void build(int x,int l,int r) {
		f[x]= {l,r,inf,inf};
		if(l==r) {
			f[x].val=inf;//赋极大值 
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	inline void push_down(int x) {
		if(f[x].lz==inf)return;
		//区间修改，取最小值 
		f[ls].val=min(f[ls].val,f[x].lz);
		f[ls].lz=min(f[ls].lz,f[x].lz);
		
		f[rs].val=min(f[rs].val,f[x].lz);
		f[rs].lz=min(f[rs].lz,f[x].lz);
		
		f[x].lz=inf;
	}
	int query(int x,int l,int r) {//查找最小值 
		if(l<=f[x].l and f[x].r<=r)return f[x].val;
		push_down(x);
		int mid=f[x].l+f[x].r>>1,ans=m;
		if(l<=mid)ans=min(ans,query(ls,l,r));
		if(r>mid)ans=min(ans,query(rs,l,r));
		return ans;
	}
	void modify(int x,int l,int r,int val) {
		if(l<=f[x].l and f[x].r<=r) {
			f[x].val=min(f[x].val,val);
			f[x].lz=min(f[x].lz,val);
			return;
		}
		push_down(x);
		int mid=f[x].l+f[x].r>>1;
		if(l<=mid)modify(ls,l,r,val);
		if(r>mid)modify(rs,l,r,val);
		f[x].val=min(f[ls].val,f[rs].val);
	}
}
int main() {
	int T=read();
	while(T--) {
		n=read(),m=read();
		tree::build(1,1,n);//建树并赋极大值 
		tree::modify(1,1,1,0);//赋值 dp[1]=0
		F(i,1,m) {
			a[i].l=read(),a[i].r=read();
			int x=tree::query(1,a[i].l,a[i].r);//查找最小值 
			tree::modify(1,a[i].l,a[i].r,x+1);//转移 
		}
		ans=tree::query(1,n,n);//最终答案 
		printf("%d\n",ans);
		if(T)putchar('\n');
	}
	return 0;
}
inline int read() {
	reg int x=0;
	reg char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
```

线段树部分就是一个模板，还是十分容易写的。

[AC](https://www.luogu.com.cn/record/53424154)

欢迎交流讨论，请点个赞哦~

---

## 作者：清烛 (赞：0)

宣传[博客](https://blog.imyangty.com/sol-uva1322/)

## Description

现要寻找某数组中的最大值。某机器由若干个 Sorter 组成，第 $k$ 个可以把 $[l_k, r_k]$ 中的数字排序。该机器依次运行每个 Sorter，则正常情况下，最后一个数字将成为我们需要的最大值。

求最少保留多少个 Sorter 能使得该机器仍正常工作。注意 Sorter 的顺序不能改变。

$2 \le n \le 5 \times 10 ^4$，$1 \le m \le 5 \times 10 ^ 5$，$1 \le i_k \le j_k \le n$。

## Solution

注意到每一个 Sorter 相当于就是把区间中最大的数移到最右边。

假设当前的最大值在 $m$ 处，那么一个能把他拖到 $r_k$ 的 Sorter 必须满足 $l_k\le m\le r_k$。所以假设第一个数为最大的，如果这个 Maximizer 能把它拖到最后，那么其必然是合法的。所以问题现在转化成了一个区间覆盖问题。

考虑 dp：设 $f_{i, j}$ 为考虑前 $i$ 个 Sorter，第一个数现在在 $j$，选择的最少的 Sorter 数量。

则有转移：
$$
f_{k, r_k} = \min_{l_k\le j'\le r_k}\{f_{k - 1, j'} + 1\}
$$
朴素的来做是 $O(nm)$ 的，不太行。

但是这个东西每次相当于就是查询一下区间最小值，然后更新一个单点的值。所以可以使用线段树来维护最小值。

## Implementation

需要注意 UVa 的最后一行行末不能换行，每组数据之间要空一行。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

const int maxn = 5e4 + 5;

il int min(int a, int b) {return a < b ? a : b;}

int f[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int v) {
    if (i == j) {
        f[k] = min(f[k], v);
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    f[k] = min(f[L], f[R]);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return f[k];
    int ret = 1e9;
    if (x <= M) ret = min(ret, query(i, M, L, x, y));
    if (y > M) ret = min(ret, query(M + 1, j, R, x, y));
    return ret;
}

int n, m;

int main() {
    int T; read(T);
    FOR(kase, 1, T) {
        read(n), read(m);
        memset(f, 0x7f, sizeof f);
        modify(1, n, 1, 1, 0);
        FOR(i, 1, m) {
            int l, r; read(l), read(r);
            modify(1, n, 1, r, query(1, n, 1, l, r) + 1);
        }
        print(query(1, n, 1, n, n)), putchar('\n');
        if (kase < T) putchar('\n');
    }
    return output(), 0;
}
```



---

