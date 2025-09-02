# Cashback

## 题目描述

Since you are the best Wraith King, Nizhniy Magazin «Mir» at the centre of Vinnytsia is offering you a discount.

You are given an array $ a $ of length $ n $ and an integer $ c $ .

The value of some array $ b $ of length $ k $ is the sum of its elements except for the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF940E/7767e68a87566f0732f029bd691b100b0a741ae2.png) smallest. For example, the value of the array $ [3,1,6,5,2] $ with $ c=2 $ is $ 3+6+5=14 $ .

Among all possible partitions of $ a $ into contiguous subarrays output the smallest possible sum of the values of these subarrays.

## 说明/提示

In the first example any partition yields 6 as the sum.

In the second example one of the optimal partitions is $ [1,1],[10,10,10,10,10,10,9,10,10,10] $ with the values 2 and 90 respectively.

In the third example one of the optimal partitions is $ [2,3],[6,4,5,7],[1] $ with the values 3, 13 and 1 respectively.

In the fourth example one of the optimal partitions is $ [1],[3,4,5,5,3,4],[1] $ with the values 1, 21 and 1 respectively.

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
12 10
1 1 10 10 10 10 10 10 9 10 10 10
```

### 输出

```
92
```

## 样例 #3

### 输入

```
7 2
2 3 6 4 5 7 1
```

### 输出

```
17
```

## 样例 #4

### 输入

```
8 4
1 3 4 5 5 3 4 1
```

### 输出

```
23
```

# 题解

## 作者：Alarm5854 (赞：16)

这道题目乍一看好像没有办法做，因为无法用较低的时间复杂度来统计一段长度为 $k$ 在区间中前 $k/c$ 小的数的和。

不过，仔细想一下，发现有这样的结论：
- 如果一段区间的长度 $k$ 满足 $1\le k<c$，那么等效于 $k$ 个长度为 $1$ 的区间（答案就是区间和）。
- 如果一段区间的长度 $k$ 满足 $k=c$，那么答案就是区间和减去最小值。
- 如果一段区间的长度 $k$ 满足 $c<k<2c$，那么等效于一段长度为 $k$ 在区间加上 $k-c$ 段长度为 $1$ 的区间（$k/c=1$）。
- 如果一段区间的长度 $k$ 满足 $k\ge 2c$，那么这段区间肯定不会优于一段长度为 $k$ 的区间加上一段长度为 $k-c$ 在区间。证明：如果有连续两段长度为 $c$ 的区间，第一段的最小值和次小值分别为 $a_1,b_1$，第二段的最小值和次小值分别为 $a_2,b_2$。如果 $b_1<a_2$，那么如果合并区间，那么减少的值就是 $a_1+b_1<a_1+c_1$；如果 $b_1>a_2$，那么不管是合并还是不合并，减少的值都是 $a_1+a_2$。所以，不拆肯定不比拆开优。

这样，只需要分两种情况了：区间长度为 $1$ 和区间长度为 $c$，可以用动态规划实现了。

记 $f_i$ 为序列长度为 $i$ 的答案，$g_i$ 为以 $i$ 为最后一个元素，区间长度为 $c$ 的最小元素值，$s_i$ 为以 $i$ 结尾在前缀和，则转移方程为 $f_i=\min(f_{i-1}+a_i,f_{i-c}+(s_i-s_{i-c})-g_i)$。$g_i$ 用单调队列预处理，时间复杂度为 $O(n)$。
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<algorithm>
#define ll long long
const ll N = 1e5 + 10; 
using namespace std;
inline ll read() {
	ll x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
ll n, c, h, t, q[N], a[N], s[N], dp[N], minn[N];
int main() {
	n = read(), c = read(), h = 1, t = 0;
	for (ll i = 1; i <= n; ++i) a[i] = read(), s[i] = s[i - 1] + a[i];
	for (ll i = 1; i <= n; ++i) {
		while (h <= t && q[h] + c <= i) q[h++] = 0;
		while (h <= t && a[q[t]] >= a[i]) q[t--] = 0;
		q[++t] = i, minn[i] = a[q[h]];
	}
	for (ll i = 1; i < c; ++i) dp[i] = dp[i - 1] + a[i];
	for (ll i = c; i <= n; ++i)
	dp[i] = min(dp[i - c] + s[i] - s[i - c] - minn[i], dp[i - 1] + a[i]);
	printf("%I64d", dp[n]);//答案可能会炸int，而codeforces上的long long要用%I64d输出
	return 0;
}
```

---

## 作者：wwlw (赞：7)

[Link](https://www.luogu.com.cn/problem/CF940E)
-----------------

### 题目描述
把一个序列分成若干段，若一段的长度为 $k$，则把那段中前 $\lfloor\frac{k}{c}\rfloor$ 小的数删去， $c$ 为给定常数，最小化每段和。

### 解法

显然每段越短越好，因为如果把一个段增大的话，段内的最小值可能减小，而删去的数的总数也可能减少。还有一个例子也可以说明，即两个小区间分别的最小值之和显然比这两个区间的并的大区间的前两个最小值之和大，从而使得最后的答案更小。

而对于长度小于 $c$ 的区间对答案是没有正向贡献的，于是每次取长度为 $c$ 的一段是最优的，那么有
$$dp_i=max\{dp_{i-1},dp_{i-c}+min\{a_j|\ j\in(i-c,i]\  \}\}\quad i\in[c,n]$$

$dp_i$ 表示把前 $i$ 个数分成若干段，每段的最小值之和的最大值。那么方程的两项分别对应断开区间和不断。

而 $i$ 的值是连续的，后面那一堆显然可以用单调队列优化掉，那么最后的复杂度就是 $\Theta(n)$

```cpp
#include<stdio.h>
#define N 100007
#define ll long long

template<class T>
inline void read(T &x){
	x=0; bool flag=0; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') flag=1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	x=flag? -x:x;
}

inline ll max(ll x,ll y){return x>y? x:y;}

int n,c,Q[N];
ll sum=0,a[N],dp[N];
int main(){
	read(n),read(c);
	for(int i=1;i<=n;i++)
		read(a[i]),sum+=a[i];
	int l=1,r=0;
	for(int i=1;i<=n;i++){
		while(l<=r&&a[Q[r]]>=a[i]) r--;
		Q[++r]=i;
		while(l<=r&&Q[l]<=i-c) l++;
		if(i>=c) dp[i]=max(dp[i-1],dp[i-c]+a[Q[l]]);
	}
	printf("%lld",sum-dp[n]);
}
```

---

## 作者：installb (赞：5)

一个就像贪心一样的DP  
思路还是挺巧妙的  

首先由于可以任意分段 对于任何一个长度$len<k$的段 这一段是不能够去掉任何一个数的 也就是每一个数都要被统计到答案里 所以要是弄出来这样一个分段就把它拆成$len$个长度为$1$的段是等价的  
果断拆啊 拆了处理更方便  

其次对于长度$len\geq k$的段 这里先看长度不为k的整数倍的段  
我们可以把它分成 一个(长度为$mk$(m为满足$mk<len$的最大整数))的段和几个长度为1的段  
其中长度为$mk$的段取所有情况中最优情况 其它用长度为1的段填满  
与上面同理

现在我们只剩下长度为1的段和长度为$mk$的段了  
接下来 观察后者 如果把它分成$m$个长度为$k$的段 结果一定不会更劣  
因为去掉的数不会减小 但可能增大  

所以分啊  

然后这题就变成把一些数任意分成长度为1和k的段 其中每个长度为k的段的贡献(就是和)为这段的和减去它的最小值 长度为1的段就是加上这个数本身了  

然后可以dp了 这里大家应该就都会了  
$dp[i] = min(dp[i - 1] + w[i],dp[i - c] + sum(i - c + 1,i) - min\{w[i-c+1],...,w[i]\}) $

最小值用线段树实现了  

**code:**
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define mid ((l + r) >> 1)
#define lson (x << 1)
#define rson ((x << 1) | 1)
using namespace std;
typedef long long LL;

LL a[500005] = {0};
LL val[2000005] = {0};

void build(LL x,LL l,LL r){
	if(l == r){ val[x] = a[l]; return; }
	build(lson,l,mid);
	build(rson,mid + 1,r);
	val[x] = min(val[lson],val[rson]);
}

LL query(LL x,LL l,LL r,LL L,LL R){
	if(L <= l && r <= R) return val[x];
	LL ret = 0x3f3f3f3f3f3f3f3f;
	if(L <= mid) ret = min(ret,query(lson,l,mid,L,R));
	if(R > mid) ret = min(ret,query(rson,mid + 1,r,L,R));
	return ret;
}

LL n,c;
LL dp[500005] = {0};
LL pre[500005] = {0};

int main(){
	memset(dp,0x3f,sizeof(dp));
	cin >> n >> c;
	for(LL i = 1;i <= n;i ++) cin >> a[i];
	for(LL i = 1;i <= n;i ++) pre[i] = pre[i - 1] + a[i];
	// 前缀和求一段的和
    build(1,1,n); // 线段树别忘了build
	dp[0] = 0;
	for(LL i = 1;i <= n;i ++){
		if(i >= c) dp[i] = min(dp[i],dp[i - c] + pre[i] - pre[i - c] - query(1,1,n,i - c + 1,i));
		dp[i] = min(dp[i],dp[i - 1] + a[i]);
        // dp转移
	}
	cout << dp[n] << endl;
	return 0;
}
```

所以啊 有些时候 样例解释不能信啊

---

## 作者：RainFestival (赞：3)

这道题先贪心一下，只分成长度为1或c两种区间

下面内容可以跳过（step 0）：

------------


如果分为长度为n

1、1<n<c 情况

反正不能去掉，与分成n个1区间没有任何区别

2、c<n<总数(n%c=0) 情况

设n%c=2,其他情况类似

设1~c中最小为a1,次小为a2

c+1~2×c中最小为b1,次小为b2

不妨设a1<b1,不然a1与b1交换,a2与b2交换

原来：分一个长度为n×2

现在：分二个长度为n

设a1<a2<b1<b2 则原来删除a1,a2,现在删除a1,b1,现在优

设a1<b1<a2<b2 则原来删除a1,b1,现在删除a1,b1,同样优

3、c<n<总数(n%c=0),则总可以分成n/c个c长区间，n%c个1长区间，结果不会不优

------------

step1:

如果你会单调队列，就用单调队列；

如果你会st表，就用st表；

如果你会线段树，就用线段树；

如果你会其他方法，就用其他方法：

维护长度为c区间里的最小值！！！

step2:

然后完美推出dp（转移）方程

设dp i为从1~i中最多能删掉数的总和

dp i=max(dp i-1, //分长度为1的区间

            dp i-c -(i-c+1到i的长度为c区间最小值//分长度为c区间
            
边界条件dp 0=0

step3: 输出dp 所有数总和-dp 数列长度

step4:提交&&accepted

下面是代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long a[200005],q[200005],qu[200005],mmax[200005],dp[200005],s;
int n,c;
int main()
{
    scanf("%d%d",&n,&c);
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        s=s+a[i];
    }  
    if (c>n)
    {
        printf("%lld\n",s);
        return 0;
    } 
    //printf("%d-%d\n",n,c);
    
    int h=1,t=0;
    for (int i=1;i<c&&i<=n;i++)
    {
        t++;
        qu[t]=a[i];
        q[t]=i;
        while (qu[t]<qu[t-1]&&h<t)
        {
            qu[t-1]=qu[t];
            q[t-1]=q[t];
            qu[t]=q[t]=0;
            t--;
        }
        mmax[i]=0;
    }
    for (int i=c;i<=n;i++)
    {
        if (i>n) break;
        t++;
        qu[t]=a[i];
        q[t]=i;
        while (q[h]<=i-c)
        {
            q[h]=qu[h]=0;
            h++;
        }
        while (qu[t]<qu[t-1]&&h<t)
        {
            qu[t-1]=qu[t];
            q[t-1]=q[t];
            qu[t]=q[t]=0;
            t--;
        }
        mmax[i]=qu[h];
    }
    for (int i=1;i<=n;i++)
    {
        dp[i]=dp[i-1];
        if (i>=c) dp[i]=max(dp[i],dp[i-c]+mmax[i]);
    }   
    printf("%lld",s-dp[n]);
    return 0;
} 
```
温馨提示：共计56个（测试）点

时间988ms，空间7.66MB，代码长度0.92KB

谢谢大佬们的观赏



---

## 作者：DEADFISH7 (赞：2)

开始看到题确实没什么思路 感觉突然冒出来的向下取整的除法很突兀

但是这就是一个突破点

所以每一段的长度要么是1，要么是c

所以就从 -1的和-c转移

维护一个最小值，使其最大
```cpp
// by DEADFISH
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define p 1e6+7
#define N 150000
#define maxn 999999999
#define mc(a,b) memset(a,b,sizeof(a))
#define int long long 
#define close std::ios::sync_with_stdio
using namespace std;
int n,c;
int sum=0;
int a[N];
int val[N],mi[N];
int f[N];
int ask(int a,int b,int c,int d,int e);
void build(int rt,int s,int t);
signed main()
{
	close;
	cin>>n>>c;
	build(1,1,n);
	for(int i=c;i<=n;i++)
	{
		int x=ask(1,1,n,i-c+1,i);
		f[i]=max(f[i-1],f[i-c]+x);
	}
	cout<<sum-f[n];
	return 0;
}
void build(int rt,int s,int t)
{
	if(s==t)
	{
		int x;
		cin>>x;
		mi[rt]=x;
		sum+=x;
		return ;
	}
	int mid=s+t>>1;
	build(rt<<1,s,mid);
	build(rt<<1|1,mid+1,t);
	mi[rt]=min(mi[rt<<1],mi[rt<<1|1]);
}
int ask(int rt,int s,int t,int l,int r)
{
	if(l<=s&&t<=r) return mi[rt];
	int mid=s+t>>1;
	int ans=maxn;
	if(l<=mid) ans=min(ans,ask(rt<<1,s,mid,l,r));
	if(r>mid) ans=min(ans,ask(rt<<1|1,mid+1,t,l,r));
	return ans;
}
```

---

## 作者：字如其人 (赞：2)

前缀和+单调队列+dp

显然每个被分开的段长不超过c时最优（不然会有其他更小的局部最小值来替代不够优）。

如果这段长度不超过c,把它当做len个长度为1的段显然是等效的（不会删数）。

所以只要可以能分一段就分一段，可以想到这样的dp。
```cpp
for(int i=1;i<=n;i++){
		if(i>=c)f[i]=min(f[i],f[i-c]+s[i]-s[i-c]-minn[i]);
		f[i]=min(f[i],f[i-1]+a[i]);
	}
```

使用单调队列预处理出每个长度为c的数列最小值。
使用前缀和预处理出一段的和。
```cpp
head=1,tail=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
		while(head<=tail&&q[tail]>=a[i])tail--;
		q[++tail]=a[i];
		p[tail]=i;
		while(p[head]<=i-c)head++;
		if(i>=c)minn[i]=q[head];
        //连输入也拼一起了
	}
```
贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,a[100005],p[100005],q[100005],minn[100005],head,tail;
long long f[100005],s[100005];
int main(){
	scanf("%d%d",&n,&c);
	head=1,tail=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
		while(head<=tail&&q[tail]>=a[i])tail--;
		q[++tail]=a[i];
		p[tail]=i;
		while(p[head]<=i-c)head++;
		if(i>=c)minn[i]=q[head];
	}
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		if(i>=c)f[i]=min(f[i],f[i-c]+s[i]-s[i-c]-minn[i]);
		f[i]=min(f[i],f[i-1]+a[i]);
	}
	printf("%lld",f[n]);
	return 0;
}
```






---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15940481.html)

# 题目大意

给你一个长度为 $n$ 的数列 $a$ 和整数 $m$，你需要把它任意分段。每一段假设长度为 $k$，就去掉前 $\lfloor\frac{k}{m}\rfloor$ 小的数。

最小化剩下的数的和。

# 题目分析

**因为要让剩下数的和最小，所以我们要让去掉的数的和最大。**

观察 $\left\lfloor\frac{k}{m}\right\rfloor$，可知分段对答案有贡献当且仅当 $k\ge m$。那么我们 $k$ 满足什么条件时答案最优呢？

首先，$k$ 当然要大于等于 $m$~~（废话上面说过了）~~，其次，容易发现一个性质：一段子串长度为 $k\times m+s$ 时答案不会比一段子串长度为 $k\times m$ 更优，其中 $s$ 为常数且 $1\le s\le m$。并且我们一定尽量将序列分割为数个长度为 $k$ 的子串，$k$ 应尽量小。综上，$k$ 取 $m$。

举个例子：$k=3$ 且数列为 `7 9 8 1 1 1` 时，分成 `7 9 8` 和 `1 1 1` 贡献为 $7+1=8$；但分成 `7 9 8 1 1 1` 贡献为 $1+1=2$。

所以问题转化为：将序列分为数个长度为 $m$ 的子串（不要求序列长度为 $m$ 的倍数，即不要求分割的子串连续），每个子串取一个最小值使得取出数之和最大。

令 $dp_i$ 表示前 $i$ 个数分割后取出数的和的最大值，于是有：

$$dp_i=\max\{dp_{i-1},dp_{i-m}+\min(i-m+1,i)\}$$

恍然大悟，随便抽一个数据结构来维护即可，我这里用的是 ~~树套树~~ 线段树。

# 代码

```cpp
//2022/2/26
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 1e5 + 5;
int a[ma],dp[ma];
int n,m,sum;
struct Segment_Tree {
	struct Node {
		int l,r;
		int Min;
	} node[ma << 2];
	#define lson (p << 1)
	#define rson (p << 1 | 1)
	inline void pushup(int p) {
		node[p].Min = min(node[lson].Min,node[rson].Min);
	}
	inline void build(int p,int l,int r) {
		node[p].l = l,node[p].r = r;
		if (l == r) {
			node[p].Min = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(lson,l,mid),build(rson,mid + 1,r);
		pushup(p);
	}
	inline int query(int x,int y,int p) {
		if (x <= node[p].l && node[p].r <= y) {
			return node[p].Min;
		}
		int mid = node[p].l + node[p].r >> 1,res = INT_MAX;
		if (x <= mid) res = min(res,query(x,y,lson));
		if (y > mid) res = min(res,query(x,y,rson));
		return res;
	}
	#undef lson
	#undef rson
} seg;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
		sum += a[i];
	}
	seg.build(1,1,n);
	for (register int i = m;i <= n; ++ i) {
		dp[i] = max(dp[i - 1],dp[i - m] + seg.query(i - m + 1,i,1));
	}
	printf("%lld\n",sum - dp[n]);

	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：1)

## 分析
首先，因为要最小化剩下的数的和，那么我们肯定要使取走的数的总和尽可能大

我们还可以发现，因为要去掉前$\lfloor\frac{k}{c}\rfloor$ 小的数
因此只有一段区间的长度大于等于$c$时才会对结果产生贡献

而且我们划分出长度为$k\times c + m (1\leq m < c)$的区间一定不如划分出长度为$k\times c$的区间更优

因为这两种情况选出的数字的数量相同，但是在第二种情况中选出数的最小值一定不会比前一种情况更小

但是这样写还是不太好处理，因为要涉及到前$k$小的数，所以似乎要用到某些高级数据结构

而这样显然是不好处理的

我们进一步推导会发现，将一个长度为$k\times c$的区间划分为$k$个长度为$c$的区间所产生的结果只会更优

比如下面一个长度为$8$的序列，$c=4$

$1、 1 、2 、5 、3 、7、 8、 9$

如果我们把它划分为长度为$8$的序列，那么产生的贡献为$1+1=2$

但是如果我们把它分成两个长度为$4$的序列

$1、1、2、5$和$3、7 、8、9$

那么产生的贡献为$1+3=4$

显然后一种更优

因此，我们将原题进一步转换成将一个长度为$n$的序列划分为若干长度为$c$的序列，使每一个序列的最小值之和最大

其中区间最值可以用线段树去维护

那么我们可以写出如下的状态转移方程
``` cpp
    for(int i=1;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
        if(i>=c) f[i]=max(f[i],f[i-c]+(long long)jl[i]);
    }
```
其中$f[i]$表示以遍历到下标为$i$的元素所选出的最大价值

$jl[i]$表示以$a[i]$结尾的长度为$c$的区间中的最小值

如果我们选取以$a[i]$结尾的长度为$c$的区间，那么$f[i]=max(f[i],f[i-c]+(long long)jl[i]$

否则$f[i]=max(f[i],f[i-1])$
## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn];
struct trr{
    int l,r,mmin;
}tr[maxn<<2];
void push_up(int da){
    tr[da].mmin=min(tr[da<<1].mmin,tr[da<<1|1].mmin);
}
void build(int da,int l,int r){
    tr[da].l=l,tr[da].r=r;
    if(l==r){
        tr[da].mmin=a[l];
        return;
    }
    int mids=(l+r)>>1;
    build(da<<1,l,mids);
    build(da<<1|1,mids+1,r);
    push_up(da);
}
int cx(int da,int l,int r){
    if(tr[da].l>=l && tr[da].r<=r){
        return tr[da].mmin;
    }
    int ans=0x3f3f3f3f,mids=(tr[da].l+tr[da].r)>>1;
    if(l<=mids) ans=min(ans,cx(da<<1,l,r));
    if(r>mids) ans=min(ans,cx(da<<1|1,l,r));
    return ans;
}
int jl[maxn];
long long f[maxn];
int main(){
    long long tot=0;
    int n,c;
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        tot+=(long long)a[i];
    }
    build(1,1,n);
    long long ans=0;
    for(int i=1;i<=n-c+1;i++){
        jl[i+c-1]=cx(1,i,i+c-1);
    }
    for(int i=1;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
        if(i>=c) f[i]=max(f[i],f[i-c]+(long long)jl[i]);
    }
    printf("%lld\n",tot-f[n]);
    return 0;
}
```

---

## 作者：Mickey_snow (赞：1)

动态规划。

这题的题意可以转换为在数组上选择若干个没有交集的区间，去掉区间内最小的数，且每一个区间的长度都为 $c$ 的倍数。如果不为 $c$ 的倍数，去掉的数只可能更劣，这很好想，也很好证明。

所以，我们先预处理出一个数组 $que_i$ 代表如果一个区间的右端点恰好在 $i$ 这个位置，那么能够去掉的数字是多少，这项预处理如果使用单调队列优化，可以在 $O(N)$ 的时间复杂度内解决。

接下来动态规划部分求出一个数组 $Dp_i$ 代表序列前 $i$ 个数中去掉的数字之和最大是多少。这样一来转移就很好想了。这是一个线性动态规划，时间复杂度也是 $O(N)$, 答案在 $Dp_n$ 处。

代码如下：

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ConsoleApp1 
{
	class Program 
	{
		public class Node {
			public Int64 Num { get; set; }
			public Int64 Pos { get; set; }
		}

		static void Main(string[] args) 
		{
			string inp;string[] div;

			int totNums, k, frnt = 0, tail = 0;
			Int64[] num, D, que;Int64 tot = 0;

			inp = Console.ReadLine();div = inp.Split(' ');
			totNums = Convert.ToInt32(div[0]);k = Convert.ToInt32(div[1]);

			inp = Console.ReadLine();div = inp.Split(' ');
			num = new Int64[totNums];D = new Int64[totNums];que = new Int64[totNums];
			for(int i = 0; i < totNums; i++) { num[i] = Convert.ToInt64(div[i]); tot += num[i]; }

			Node[] arr = new Node[totNums];Node inIt;
			for(int i = 0; i < k - 1 && i < totNums; i++) {
				inIt = new Node { };
				inIt.Pos = i; inIt.Num = num[i];
				while(frnt < tail && arr[tail - 1].Num >= inIt.Num) tail--;
				arr[tail++] = inIt;
			}
			for(int i = k - 1; i < totNums; i++) {
				inIt = new Node { };
				inIt.Pos = i;inIt.Num = num[i];
				while(frnt < tail && arr[frnt].Pos <= i - k) frnt++;
				while(frnt < tail && arr[tail - 1].Num >= inIt.Num) tail--;
				arr[tail++] = inIt;
				que[i] = arr[frnt].Num;
			}

			D[0] = que[0];
			for(int i = Math.Max(k - 1, 1); i < totNums; i++) {
				D[i] = Math.Max(D[i - 1], que[i]);
				if(i - k >= 0)
					D[i] = Math.Max(D[i], D[i - k] + que[i]);
			}

			Console.WriteLine((tot - D[totNums - 1]).ToString());
		}
	}
}

```

---

## 作者：Arghariza (赞：0)

首先我们发现在删的数的数量相等的情况下，尽量细分是不劣的。

所以我们可以假设每一段长度至多为 $c$，同时长度严格 $<c$ 的段都不会删数。

然后略加转换，最小化剩下的数的和相当于计算最大化删去的数的和。

由于长度严格 $<c$ 的段都没有贡献，我们可以尽量分长度为 $c$ 的段。

于是我们可以用单调队列预处理出 $b_i$ 表示 $a_i$ 到 $a_{i+c-1}$ 中的最小值，问题就变成了在 $b$ 数组中取出若干个数，任意两个的距离不能 $\le c$，求取出的数的和的最大值。

那就做完了，令 $f_i$ 表示取到 $i$ 的最大值，转移分几种取/不取几种情况讨论一下就好了。

- 如果不取 $i$，$f_i\gets f_{i-1}$。
- 如果取 $i$，$f_i\gets b_i+f_{i-c}[i>c]$。

复杂度 $O(n)$。

[评测记录。](https://codeforces.com/contest/940/submission/189160602)

---

## 作者：JWRuixi (赞：0)

思路很巧妙的题。

- 题意

给定长度为 $n$ 的序列 $a$，和常数 $c$。

将序列分为任意多段，对于一段长度为 $len$ 的子段，删去盖子段中前 $\lfloor\frac{len}{c}\rfloor$ 小的数。

最小化最后的序列和。

- 分析

考虑一种很简单的 dp，设 $f_i$ 表示 $[1,i]$ 的最小和，显然有：

$$f_i=\min\limits_{j<i}f_j+w(j+1,i)$$

思考怎样计算 $w(j+1,i)$，我们可以从后往前扫，动态的维护需要删除的最小值，这样做可以 $O(n^2)$。

仔细想一下，发现最小值是单调不增的，所以显然能分段的就分段更优，具体的对于一段长度为 $k$ 的子段：

1. $k<c$，那就相当于没删，直接等价于 $f_{i-1}$。
2. $c\le k<2\times c$，相当于一段长度为 $c$ 的部分再加上长度 $k-c$ 的部分。
3. $2\times c \le k$，可以截出一段长为 $c$ 的，在考虑剩下的 $k - c$ 部分。

综上，我们得到了新的状态转移方程：

$$f_i \leftarrow f_{i-1}+a_i$$
$$f_i \leftarrow f_{i-c}+\sum\limits_{j=i-c+1}^{i} a_j-\min\limits_{j=i-c+1}^{c} a_j$$

那直接用前缀和优化区间和，用滑动窗口优化最小值就可以 $O(n)$ 了。

PS：不知道为什么我的代码 c++17(64) 会 IDE？

- code

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
int n, c, a[maxn], f[maxn], s[maxn];

struct MinMultiset {
	int q[maxn], h = 1, r = 0;
	inline int qry (int x) {
		while (h <= r && q[h] <= x - c) h++;
		return a[q[h]];
	}
	inline int insert (int x) {
		while (h <= r && a[q[r]] >= a[x]) r--;
		q[++r] = x;
	}
} st;

signed main () {
	n = read(), c = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1] + a[i];
		st.insert(i);
		if (i >= c) f[i] = min(f[i], f[i - c] + s[i] - s[i - c] - st.qry(i));
	}
	write(f[n]);
}
```

---

## 作者：Milmon (赞：0)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF940E) & [Problem](//www.luogu.com.cn/problem/CF940E)

## 题目大意

- 给定长度为 $n$ 的序列 $a$ 和一个整数 $c$。

- 将其分成若干段，若该段长度为 $k$，就删除该段中前 $\left\lfloor\dfrac kc\right\rfloor$ 小的数。

- 求剩余数总和最小值。

- $1\leq n,\ c\leq 10^5$，$1\leq a_i\leq 10^9$

## 解题思路

对于一段长度为 $k$ 的数：

- 若 $\left\lfloor\dfrac kc\right\rfloor=0$ 即 $k<c$，则该段不会被删除数，将该段任意分割也是如此。

- 若 $k=ct+p$（$t,\ p$ 为整数且 $t\geq 1,\ p<c$），则将这一段分成 $t$ 段有 $c$ 个数的段和一段有 $p$ 个数的段后，有 $c$ 个数的段各删除一个最小值，共删除 $t$ 个数。而原先删除的是该段中最小的 $t$ 个数，必定不比分割后删除的数总和。

接下来还有若干长度 $<c$ 的段，其中不会删除数，为了方便，不妨将它们全部拆成长度为 $1$ 的段。

此时序列被分为若干长度为 $1$ 的段和若干长度为 $c$ 的段，故最优解必定由长度为 $1$ 或 $c$ 的段组成。

考虑动态规划。设 $dp_i$ 表示前 $i$ 个数分割成长度为 $1$ 或 $c$ 的段，删除数总和的最大值。显然 $dp_0=0$。

计算 $dp_i$ 时，对第 $i$ 个数所在段的长度分类，易得

$$
dp_i=
\begin{cases} 
dp_{i-1}, &\text{if }n\text{ is even} \\
\min\left\{dp_{i-1},dp_{i-c}+\min\limits_{j=i-c+1}^{i}a_j\right\},&\text{if }n\text{ is odd}
\end{cases}.
$$

而答案要求的是剩下数的总和，即 $\sum\limits_{i=1}^na_i-dp_n$。

时间复杂度 $\Theta(n\log n)$（ST 表预处理或线段树查询 $n$ 次产生的时间复杂度）。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,c,a[100001];
int minn[100001][18];
long long sum,dp[100001];

inline int Min(int l,int r){
    int t=log2(r-l+1);
    return min(minn[l][t],minn[r-(1<<t)+1][t]);
}

int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),minn[i][0]=a[i],sum+=a[i];
    for(int i=1,t=log2(n);i<=t;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            minn[j][i]=min(minn[j][i-1],minn[j+(1<<i-1)][i-1]);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        if(i>=c)dp[i]=max(dp[i],dp[i-c]+Min(i-c+1,i));
    }
    printf("%lld\n",sum-dp[n]);
    return 0;
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/112280299)

这道题好像很烦，我第一眼看过去确实没有任何思路。

但是仔细分析题目后，我们会发现：

- $c=1$ 时，答案为 0，但是好像没有这个点？
- $c > n$ 时，答案为序列总和。
- $c = n$ 时，答案为序列总和减去最小值。
- $1 < c < n$ 且 $n < 2 \times c$ 时，此时序列只能分为一段，而别的序列我们可以看成是长度为 1 的区间。
- $1 < c < n$ 且 $2 \times c \leq n$ 时，我们可以将序列分为多段，而此时别的序列仍然可以分割成长度为 1 的区间。

因此只有两种区间：长度为 1 和长度为 $c$。

接下来主要考虑 $1 < c < n$ 的情况。

我们发现，此时问题就变成了一个 dp 问题。

设 $f_i$ 表示到 $a_i$ 截止时的答案，那么：

- $1 \leq i < c$ 时：$f_i = \sum_{j = 1}^{i}a_j$
- $c \leq i \leq n$ 时：$f_i = \min{(f_{i - c} + sum_i - sum_{i - c} - minn_i,f_{i - 1} +a_i)}$

其中 $sum$ 是前缀和数组，$minn_i$ 表示 $[i - c + 1,i]$ 这一段区间中的 $a_i$ 的最小值。

然后发现 $c$ 是确定的，于是对 $minn_i$ 直接单调队列优化即可，总复杂度 $O(n)$。

Code：

```cpp
/*
======== Plozia =========
	Author:Plozia
	Problem:CF940E Cashback
	Date:2021/1/6
========= Plozia =========
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, c, q[MAXN], l = 1, r = 0;
LL a[MAXN], f[MAXN], minn[MAXN], sum[MAXN];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	n = read(), c = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
	{
		while (l <= r && q[l] + c <= i) l++;
		while (l <= r && a[i] <= a[q[r]]) r--;
		q[++r] = i; minn[i] = a[q[l]]; sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i < c; ++i) f[i] = f[i - 1] + a[i];
	for (int i = c; i <= n; ++i) f[i] = min(f[i - c] + sum[i] - sum[i - c] - minn[i], f[i - 1] + a[i]);
	printf("%lld\n", f[n]);
	return 0;
}
```

---

## 作者：Vocanda (赞：0)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF940E)

# 分析
思想其实是贪心，但是不能硬贪$qwq$

题目的意思就是让我们把这些数分成任意段，每一段都要去掉前$\lfloor\frac{k}{c}\rfloor$的数字，那么开始贪心：

首先想一下，如果长度不足$c$，那么肯定是一个都去不了的，也就是全部保留，但是与其把所有小于$c$的情况都算出来，还不如每一次都从上一个长度直接加一转移而来，这样还更方便转移，只需要每一次加上当前的值就行，简单的状态转移方程如下：
$$f[i]=min(f[i],f[i-1]+w[i])$$
这里$f[i]$表示前$i$个数的最小价值，分组是每次取最小值而达到最优，下边分析一下长度大于$c$的情况（比较复杂）。

首先如果长度大于$c$，那么我们肯定能把这个长度拆开，为了便于转移和理解，我们就可以把每个超过$c$的区间都拆分成$K\times c+S$其中$K$和$S$都为常量，那么在状态转移的时候就可以发现，一旦枚举的$i$，也就前$i$个数，长度大于$c$的时候，就可以直接从长度为$i-c$转移来，所以也就是分成了$K$个$c$和许多个不能删除的长度为$1$的数。这时候只需要从$f[i-c]$加上这一段的和再减去其中的最小值，那么与当前的取一个最小值，就是前$i$的最小值。所以我们得到了第二个状态转移方程：
$$f[i]=min(f[i],f[i-c]+sum[i]-sum[i-c]-min\{i-c\to i\})$$
这种情况只有$i\ge c$的时候才成立，那么最后的答案就是$f[n]$

区间最小值可以用任何你喜欢的来维护。我用的是线段树。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5+10;
int f[maxn];
int sum[maxn];
int a[maxn];
struct Node{
	int l,r,val;
}t[maxn];
void Build(int rt,int l,int r){//建树
	t[rt].l = l;
	t[rt].r = r;
	if(l == r){
		t[rt].val = a[l];
		return;
	}
	int mid = (l+r)>>1;
	Build(rt<<1,l,mid);
	Build(rt<<1|1,mid+1,r);
	t[rt].val = min(t[rt<<1].val,t[rt<<1|1].val);
}
int check(int rt,int l,int r){//查询区间最小值
	if(t[rt].l >= l && t[rt].r <= r){
		return t[rt].val;
	}
	int ans = 0x3f3f3f3f3f3f3f3f;
	int mid = (t[rt].l + t[rt].r)>>1;
	if(l <= mid) ans = min(ans,check(rt<<1,l,r));
	if(r > mid) ans = min(ans,check(rt<<1|1,l,r));
	return ans;
}
signed main(){
	int n,c;
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		sum[i] = sum[i-1] + a[i];//记录前缀和求区间和
	}
	Build(1,1,n);
	memset(f,0x3f,sizeof(f));
	f[0] = 0;
	for(int i=1;i<=n;++i){
		if(i >= c)f[i] = min(f[i],f[i-c] + sum[i]-sum[i-c]-check(1,i-c+1,i));//分成刚好能删除一个的最小值
		f[i] = min(f[i],f[i-1]+a[i]);//不删除直接加上的最小值
	}
	printf("%lld\n",f[n]);
	return 0;
}

```

---

