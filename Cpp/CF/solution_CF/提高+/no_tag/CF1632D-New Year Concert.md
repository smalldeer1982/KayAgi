# New Year Concert

## 题目描述

New Year is just around the corner, which means that in School 179, preparations for the concert are in full swing.

There are $ n $ classes in the school, numbered from $ 1 $ to $ n $ , the $ i $ -th class has prepared a scene of length $ a_i $ minutes.

As the main one responsible for holding the concert, Idnar knows that if a concert has $ k $ scenes of lengths $ b_1 $ , $ b_2 $ , $ \ldots $ , $ b_k $ minutes, then the audience will get bored if there exist two integers $ l $ and $ r $ such that $ 1 \le l \le r \le k $ and $ \gcd(b_l, b_{l + 1}, \ldots, b_{r - 1}, b_r) = r - l + 1 $ , where $ \gcd(b_l, b_{l + 1}, \ldots, b_{r - 1}, b_r) $ is equal to the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of the numbers $ b_l $ , $ b_{l + 1} $ , $ \ldots $ , $ b_{r - 1} $ , $ b_r $ .

To avoid boring the audience, Idnar can ask any number of times (possibly zero) for the $ t $ -th class ( $ 1 \le t \le k $ ) to make a new scene $ d $ minutes in length, where $ d $ can be any positive integer. Thus, after this operation, $ b_t $ is equal to $ d $ . Note that $ t $ and $ d $ can be different for each operation.

For a sequence of scene lengths $ b_1 $ , $ b_2 $ , $ \ldots $ , $ b_{k} $ , let $ f(b) $ be the minimum number of classes Idnar has to ask to change their scene if he wants to avoid boring the audience.

Idnar hasn't decided which scenes will be allowed for the concert, so he wants to know the value of $ f $ for each non-empty prefix of $ a $ . In other words, Idnar wants to know the values of $ f(a_1) $ , $ f(a_1 $ , $ a_2) $ , $ \ldots $ , $ f(a_1 $ , $ a_2 $ , $ \ldots $ , $ a_n) $ .

## 说明/提示

In the first test we can change $ 1 $ to $ 2 $ , so the answer is $ 1 $ .

In the second test:

- $ [1] $ can be changed into $ [2] $ ,
- $ [1, 4] $ can be changed into $ [3, 4] $ ,
- $ [1, 4, 2] $ can be changed into $ [2, 3, 2] $ .

## 样例 #1

### 输入

```
1
1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 4 2```

### 输出

```
1 1 2```

## 样例 #3

### 输入

```
7
2 12 4 8 18 3 6```

### 输出

```
0 1 1 1 2 2 2```

# 题解

## 作者：meyi (赞：16)

考虑 $\gcd(b_l,b_{l+1},\dots,b_{r-1},b_r)$ 和 $r-l+1$ 在右端点 $r$ 固定时的情况，显然 $\gcd(b_l,b_{l+1},\dots,b_{r-1},b_r)$ 随 $l$ 减小而减小，$r-l+1$ 随 $l$ 减小而严格增大。故对于固定的 $r$，满足 $\gcd(b_l,b_{l+1},\dots,b_{r-1},b_r)=r-l+1$ 的 $l$ 至多只有一个。

令 $f_i$ 表示前缀 $i$ 满足题目要求所需的最少修改次数，显然有 $f_i$ 单调增且 $f_{i+1}\in\{f_i,f_i+1\}$（结合上面的结论理解）。若不存在 $l$ 使得 $\gcd(b_l,b_{l+1},\dots,b_{i-1},b_i)=i-l+1$，则 $f_i=f_{i-1}$，即不需要做任何修改；否则则需要进行一次修改，由于 $f_i$ 单调增，显然修改 $b_l$ 最优，故有 $f_i=f_{l-1}+1$。

考虑如何找出符合条件的 $l$，具体看 “$\gcd(b_l,b_{l+1},\dots,b_{r-1},b_r)$ 随 $l$ 减小而减小” 这个结论，它的本质是 $\gcd$ 每次减少一些因子，而因子只有 $O(\log V)$ 个，故不同的 $\gcd$ 只有 $O(\log V)$ 种，在每一种对应段内二分即可。

时间复杂度 $O(n \log V \log n)$。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=2e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
int a[maxn],f[maxn],n;
int lg,lg2[maxn],st[(int)log2(maxn)+1][maxn];
inline void build_st(){
	for(ri i=1;i<=n;++i)lg2[i]=lg2[i-1]+((2<<lg2[i-1])==i),st[0][i]=a[i];
	lg=lg2[n];
	for(ri i=1;i<=lg;++i)
		for(ri j=1;j+(1<<i)-1<=n;++j)
			st[i][j]=__gcd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
inline int query(int l,int r){
	ri k=lg2[r-l+1];
	return __gcd(st[k][l],st[k][r-(1<<k)+1]);
}
int main(){
	scanf("%d",&n);
	for(ri i=1;i<=n;++i)scanf("%d",a+i);
	build_st();
	for(ri i=1;i<=n;++i){
		f[i]=f[i-1];
		for(ri j=i;j>0;){
			ri g=query(j,i),now=j;
			for(ri k=lg;~k;--k)
				if(j>(1<<k)&&query(j-(1<<k),i)==g)
					j-=(1<<k);
			if(g<=i-j+1&&g>=i-now+1){
				f[i]=f[i-g]+1;
				break;
			}
			--j;
		}
		printf("%d ",f[i]);
	}
	return 0;
}
```

---

## 作者：Iratis (赞：10)

这道题在比赛的时候是没想到的，下来补上了，决定写篇题解加深理解。

本题解 RMQ 做法。

首先我们定义一个区间 $ [l,r] $ 满足 $ (b_l,b_{l+1},…,b_{r-1},b_r)=r-l+1 $ 为一个非法区间。

### 引理证明：

（当然，倘若你觉得它显然成立可以跳过这部分）

1. $ d \mid a,d \mid b $ 则 $ d \mid (a,b) $ 

2. $ (a,b,c)=((a,b),c) $ 

3. $ (b_1,b_2,…,b_{k-1},b_k) \geq (b_1,b_2,…,b_{k-1},b_k,a) (a \in N^+) $ 

假设 $ e=(a,b) $ ，则存在整数 $ x,y $ 满足 $ e=xa+yb $ 。因为 $ d \mid a,d \mid b $ ，则 $ d \mid (xa+yb) $ ，即 $ d \mid e=(a,b) $ .

令 $ d_1=(a,b,c),d_2=((a,b),c) $ ，所以 $ d_1 \mid a,d_1 \mid b,d_1 \mid c $ ，由引理 1 ，$ d1 \mid (a,b) $ ，所以 $ d_1 \mid ((a,b),c)=d_2 $ ，同理证得 $ d_2 \mid d_1 $ ，即证得 $ (a,b,c)=((a,b),c) $ .

令左式 $ =x $ ，右式 $ =((b_1,b_2,…,b_{k-1},b_k),a)=(x,a) $ ，即证 $ x \geq (x,a) $ ，假设 $ d=(x,a) $ ，则 $ d \mid x $ ，即 $ d \leq x $ .

### 题目分析：

我们可以观察到对于一个固定的位置 $ r $ ，以位置 $ r $ 作为结尾的非法区间的个数一定为 $ 0 $ 或 $ 1 $ ，证明如下：

若存在 $ l_1 $ 使得 $ [l_1,r] $ 为非法区间，假设存在 $ l_2(l_1 \neq l_2) $ 满足上述条件。

1. $ l_1>l_2 $ ，则 $ r-l_1+1<r-l_2+1,(b_{l_1},b_{l_1+1},…,b_{r-1},b_r) \geq (b_{l_2},b_{l_2+1},…,b_{r-1},b_r) $ ，所以 $ (b_{l_2},b_{l_2+1},…,b_{r-1},b_r) \neq r-l_2+1 $ ，与定义不符

2. $ l_1=l_2 $ ，与假设不符。

3. $ l_1<l_2 $ ，则 $ r-l_1+1>r-l_2+1,(b_{l_1},b_{l_1+1},…,b_{r-1},b_r) \leq (b_{l_2},b_{l_2+1},…,b_{r-1},b_r) $ ，所以 $ (b_{l_2},b_{l_2+1},…,b_{r-1},b_r) \neq r-l_2+1 $ ，与定义不符

即得证。

所以非法区间与端点是一一对应的，而我们倘若将一个位置更改为一个很大的质数，那么以它作为结尾的非法区间将消失，同时不会产生新的非法区间。

对于第 $ i $ 位置，修改的次数一定小于等于 $ i-1 $ 位置的次数加一，我们只需要尽量使它等于上一个位置的代价。

我们将每个非法区间按照右端点从小到大排列，那么修改次数至多为非法区间的个数，在此基础上尽量降低代价，满足贪心性质，修改的位置尽量靠后。

所以就有了成型的思路：枚举 $ 1 $ 到 $ n $ 中的每一个位置，利用 RMQ 求出以该位置作为结尾的非法区间的左端点，倘若没有，则直接继承上一个位置的代价，倘若可以求出，则判断之前修改到的最右的端点是否在现在的区间内，不是则将答案加一。

代码如下：
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n;
int a[200001],st[200001][21];
void _st()
{
	for(int i=1;i<=n;i++)st[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int rmq(int l,int r)
{
	int maxn=log2(r-l+1);
	return __gcd(st[l][maxn],st[r-(1<<maxn)+1][maxn]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	_st();
	int ans=0,nl=1,nr=-1;
	for(int i=1;i<=n;i++)
	{
		while(nl<i&&rmq(nl,i)<i-nl+1)nl++;
		if(rmq(nl,i)==i-nl+1)
		{
			if(nl>nr)
			{
				ans++;
				nr=i;
			}
		}
		printf("%d ",ans);
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：4)

## 前言

作为 CF Div2 的题目，这题还是很有分量的。

主要难点在于发现答案的单调性。

注：下文用 $\gcd(a, b)$ 表示两者最大公约数，$\operatorname{gcdval}(l, r)$ 表示区间 $[l, r]$ 的最大公约数，$a$ 表示原数组。

## 思路

首先，我们让 $r$ 固定，然后考虑不同的 $l$。

显然，如果 $l$ 不断减小，$r-l+1$ 单调递增，$\operatorname{gcdval}(l,r)$ 单调不上升，那么两者的图像一定只有一个交点。

那么我们最多只要进行一次修改，显然修改 $a_l$ 最优，原因是 $\operatorname{gcdval}(l,r)$ 单调不上升。那么具体是否修改，就要看能否找出一个 $l$ 使得 $\operatorname{gcdval}(l,r)=r-l+1$，如果有，就需要修改，否则不需要修改。

那么如何找出符合条件的 $l$ 呢？由 $\operatorname{gcdval}(l,r)$ 单调不上升和 $r-l+1$ 单调递增可以得到，对于一个 $r$，令最小满足条件的数为 $l$，对于每一个 $i < j$ 显然有 $l_i<l_j$，因此可以双指针来维护 $l, r$。

考虑如何维护 $\operatorname{gcdval}(l,r)$，显然，线段树和 ST 表都可以维护这个东西，不过 ST 表相对简单所以我用的是 ST 表。

再考虑时间复杂度，ST 表预处理是 $n\log n$，双指针时间 $O(n)$，求 $\gcd(a,b)$ 是 $O(\log V)$，综合时间复杂度 $O(n\log n\log V+n\log V)\approx O(n\log n\log V)$（要乘上求 $\gcd$ 的时间）。

## 代码

### 预处理：

```cpp
for (int i = 2; i <= n; ++i)
	lg[i] = lg[i >> 1] + 1;
for (int i = 1; i <= lg[n]; ++i)
	for (int j = 1; j + (1 << i) - 1 <= n; ++j)
		st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
```

### 双指针：

```cpp
for (int r = 1; r <= n; ++r)
{
	while (l <= r && gcdval(l, r) < r - l + 1)
		++l;
	if (gcdval(l, r) == r - l + 1 && l > lst)
		lst = r, ++ans;
	write(ans), putchar(32);
}
```

## 后记

由于 ST 表，线段树，树状数组等数据结构有时会带有常数~~虽然ST表常数小~~，而且输入数据巨大，建议习惯性加上快读快写，**尤其不能用不加优化的 `cin`**！当然有些库函数也是很慢的，所以你可以尝试 $\min,\max$ 等，不过 $\gcd$ 重写必要性不大，因为编译器会将 $\log$ 级的时间复杂度往死里优化。

由于本人实力有限，如果有误，可以在评论区指出。

---

## 作者：Troubadour (赞：3)

### 分析：

首先考虑修改操作如何做：对于需要修改的数 $a_k$，只需要把它改成一个较大的质数，这样所有包含 $k$ 的区间全部都是符合条件的，因为除了$l=r$ 的情况以外，它们的 $\gcd$ 一定为 $1$。

然后发现一个显而易见的结论，答案序列 $f$ 一定是单调不降的，且相邻两数之差不会超过 $1$。

证明一下：设当前计算到第 $k$ 个元素，则 $f_{k-1}$ 是使前 $k-1$ 个数满足条件的最少操作次数，新加进 $a_k$ 的时候只需要考虑这个数是否会造成 $\gcd(a_l,a_{l+1},\cdots,a_k)=k-l+1(l\leq k)$。会造成则修改，否则不管它，这样一定是最优的。

考虑如何判断是否会出现这种情况。容易发现，设当前算到第 $k$ 个元素，$g_i=\gcd(a_i,a_{i+1},\cdots,a_k)$，那么 $g_i$ 也是单调不降的。然后显而易见，$k-i+1$ 是严格降的。感性理解一下，我们要求的是单调性如此的两个函数的交点，那么我们只需要找出最小的使 $k-i+1\leq g_i$ 的这个 $i$，对其进行检验即可。如果出现了使 $k-i+1= g_i$ 的点，我们就修改 $a_k$，否则我们就不管它。

因为上文所说的单调性，我们可以用二分来找这个点。为了快速算出区间 $\gcd$，这里用线段树来存储这些值。

### Code:

```cpp
#include<bits/stdc++.h>
namespace GGMZ
{
	const int N = 2e5 + 5;
	int a[N], n, ans;
	inline int gcd(int a, int b)
	{
		return b == 0 ? a : gcd(b, a%b);
	}
	struct seg
	{
		int l, r, val;
	}f[N << 2];
	void update(int p)
	{
		f[p].val = gcd(f[p << 1].val, f[p << 1 | 1].val);
	}
	void build(int p, int l, int r)
	{
		f[p].l = l, f[p].r = r;
		if (l == r)
		{
			f[p].val = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		update(p);
	}
	void modify(int p, int t, int k)
	{
		if (f[p].l == f[p].r)
		{
			f[p].val = k;
			return;
		}
		int mid = (f[p].l + f[p].r) >> 1;
		if (mid >= t)modify(p << 1, t, k);
		else modify(p << 1 | 1, t, k);
		update(p);
	}
	int query(int p, int l, int r)
	{
		if (l <= f[p].l&&f[p].r <= r)
		{
			return f[p].val;
		}
		int mid = (f[p].l + f[p].r) >> 1, res = 0;
		if (mid >= l)res = gcd(res, query(p << 1, l, r));
		if (mid < r)res = gcd(res, query(p << 1 | 1, l, r));
		return res;
	}
	void work()
	{
		using std::cin;
		using std::cout;
		cin >> n;
		for (int i = 1;i <= n;i++)
		{
			cin >> a[i];
		}
		build(1, 1, n);
		for (int i = 1;i <= n;i++)
		{
			int l = 1, r = i, res = 0;
			while (l <= r)
			{
				int mid = (l + r) >> 1;
				if (query(1, mid, i) >= (i - mid + 1))res = mid, r = mid - 1;
				else l = mid + 1;
			}
			if (res != 0 && query(1, res, i) == i - res + 1)
			{
				ans++;
				modify(1, i, 1);//方便起见，把这个位置改成 1，在后续的计算中与改成别的大质数等价。
			}
			cout << ans << ' ';
		}
	}
}
int main()
{
	return GGMZ::work(), 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：2)

约定与前置知识：

1. $(x,y)$ 表示 $x,y$ 的最大公约数。
2. $p(l,r)$ 表示 $(a_l,(a_{l+1},,(...,(a_{r-1},a_{r}))))$，即 $[l,r]$ 内的最大公约数。
3. $x\ge (x,y)$。

题意要求不能出现 $p(l,r)=r-l+1$，我们现在钦定一下右端点 $r$。

那么，$l$ 在 $r\to 1$ 时，由于 $p(l+1,r)\ge(p(l+1,r),a_{l})$，$p(l,r)$ 越来越小，$r-l+1$ 则越来越大。

那么对于一个钦定的 $r$，满足 $p(l,r)=r-l+1$ 最多只有一个。

设对于 $r$，最小的满足 $p(l,r)\ge r-l+1$ 的 $l$ 是 $q_l$，那么显然的，对于 $j>i$，$q_{j}>q_{i}$（和上面类似）。

那么就只要有一个 $q$ 的指针一直往后移即可。

对于维护 $p$，可以使用 ST 表进行区间 $\gcd$ 查询操作。

显然，我们一定可以把当前不合法的 $a_i$ 改成某个值使得任意包含 $a_i$ 的区间都合法。那么我们其实不需要对 $a_i$ 进行任何的改动。记录上一次找到 $l$ 的 $r$，如果当前找到的 $l$ 有 $l\le r$，则不做任何处理。

```cpp
#include <stdio.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
const int N=200005,lgN=25;
int lg[N],g[lgN][N],v[N];
int i,j,q,lstq,ret;
inline int gcd(int x,int y){return !y?x:gcd(y,x%y);}
inline void init(int n)
{
	rep(i,2,n)
		lg[i]=lg[i>>1]+1;
	rep(i,1,lg[n])
		rep(j,1,n-(1<<i)+1)
			g[i][j]=gcd(g[i-1][j],g[i-1][j+(1<<i-1)]);
}
inline int p(int l,int r){return gcd(g[lg[r-l+1]][l],g[lg[r-l+1]][r-(1<<lg[r-l+1])+1]);}
int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n)
		scanf("%d",v+i);
	rep(i,1,n)
		g[0][i]=v[i];
	init(n);
	q=1;
	rep(i,1,n)
	{
		while(q<=i && p(q,i)<i-q+1)
			++q;
		//此时 q 即为 q[i]。
		if(p(q,i)==i-q+1 && q>lstq)
		{
			lstq=i;
			++ret;
		}
		printf("%d ",ret);
	}
	return 0;
}
```

---

## 作者：Rubidium_Chloride (赞：2)

不鸽子了。

令 $\gcd(a_i,a_2\dots a_j)=x_{i,j}$

---

性质 $1$：改完第 $i$ 个位置上的数之后，可以将 $i+1$ 位以后的当作独立的计算。

证明：感性理解地说就是你把 $a_i$ 改成一个之前没有作为 $a_j(1\le j\le n)$ 的质因子出现过的素数。

---

性质 $2$：对于固定的 $r$，如果存在使得 $x_{l,r}=r-l+1$ 的 $l$，那么这样的 $l$ 有且仅有一个。

证明：$1\le x_{1,r}\le x_{2,r}\le \cdots x_{r,r}=a_r$，且 $r=r-1+1>r-2+1>\cdots>r-r+1=1$。

因此前一个序列 $\left\{x_{i,r}\right\}$ 是单调不减的，后一个序列是单调递减的，因此如果存在公共项，有且仅有一个公共项。

因此如果能够快速求出 $x_{i,j}$，可以二分快速求出一个数是否需要被修改。

---

设对于一个前缀 $a_1,a_2\cdots a_r$ 的答案为 $f_r$。

性质 $3$：如果存在性质 $2$ 中的 $l$，$f_r=\max(f_{l-1}+1,f_{r-1})$。

通过性质 $1$ 可以证明这个。

---

考虑到我们不会有真正的对 $a_i$ 的修改，那么可以用 $\text{ST}$ 表预处理，快速查询 $x_{i,j}$。

然后复杂度是 $\mathcal{O}(n\log n\log \text{V})$，$\text{V}$ 是值域。

---

代码，有些 $\text{ST}$ 表之类的基本处理就不放了：

```cpp
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    t=1;
    while(t--){
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        build();
        for(int i=1;i<=n;i++){
            if(i==1){f[1]=((a[1]==1)?1:0);continue;}
            ll l=1,r=i,ans=0;
            while(l<=r){
                ll mid=(l+r)>>1;
                if(query(mid,i)==(i-mid+1)){ans=mid;break;}
                if(query(mid,i)<(i-mid+1)) l=mid+1;
                else r=mid-1;
            }
            if(ans!=0) f[i]=max(f[i-1],f[ans-1]+1);
            else f[i]=f[i-1];
        }
        for(int i=1;i<=n;i++) printf("%lld ",f[i]);
    }
    return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

注意到一个重要性质：每次修改显然改为一个大质数是最优的。

我们固定 $r$，观察 $ f(l)=\gcd(a_i,a_{i+1}\cdots a_j) $ 和 $g(l)=r-l+1$ 的单调性。

显然随着 $l$ 的减小，$f(l)$ 单调不增，$g(l)$ 单调递增，所以这两个函数的交点至多只有一个。

因为答案也是单调不减的，所以我们可以考虑递推答案。

令 $f_i$ 表示当前考虑到第 $i$ 个发动机的答案。

可以发现，当存在 $l$ 使得 $\gcd(a_l,a_{l+1} \cdots a_i)=i-l+1$ 时，需要修改一次，反之则不需要修改。

我们预处理出 gcd 的 ST表，每次二分 $l$。

如果存在 $\gcd(a_l,a_{l+1} \cdots a_i)=i-l+1$，那么只需要修改一次，且修改在 $a_l$ 处是最优的，因为 $f_i$ 是递增的，所以我们要让 $f_i$ 最小，即 $i$ 最靠左，即 $f_i=f_{l-1}+1$。

复杂度 $O(n\log n \log V)$，其中 $V$ 为值域。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n;
int a[N],g[N];
int f[N][18],Log[N];
int gcd(int a,int b){
	return !b?a:gcd(b,a%b);
} 
void init(){
	for(int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=gcd(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
}
int rmq(int l,int r){
	int Lg=Log[r-l+1];
	return gcd(f[l][Lg],f[r-(1<<Lg)+1][Lg]);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f[i][0]=a[i];
	}
	init();
	if(a[1]==1) g[1]=1;
	printf("%d ",g[1]);
	for(int i=2;i<=n;i++){
		int l=1,r=i,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(rmq(mid,i)==i-mid+1){
				ans=mid;
				break;
			}
			if(rmq(mid,i)<i-mid+1) l=mid+1;
			else r=mid-1;
		}
		if(ans) g[i]=max(g[i-1],g[ans-1]+1);
		else g[i]=g[i-1];
		printf("%d ",g[i]);
	}
	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16226368.html)  
[题目传送门](https://codeforces.com/problemset/problem/1632/D)  

这道题目很妙，~~而且可以写题解~~，所以就写了一片题解。
### 题目大意
定义一次操作位修改一个数组任意一位。  
给定一个函数 $f(b_1,b_2,\dots,b_n)$ 为对数组进行修改使得 $\forall l,r\in[1,n]$ 使得 $\gcd(a_l,a_{l+1},\dots,a_r)\not= r-l+1$ 的操作数次数。  
现在给定一个长度为 $n$ 的整数序列 $a$，现在需要求 $f(a_1)+f(a_1+a_2)+\dots+f(a_1,a_2,\dots,a_n)$ 的值。  
数据范围： $1\le n\le 2\times10^5,1\le a_i\le 10^9$。
### 题目解析
对于任意一个区间，如果左端点不变，右端点右移，那么这个区间内数字的最大公约数显然不增，这个区间的长度（也就是 $r-l+1$） 增大。所以确定一个左端点之后，如果保证左端点 $l$ 为定值，那么满足 $\gcd(a_l,a_{l+1},\dots,a_r)= r-l+1$ 最多只有 $1$ 个。  
我们可以用 ST 表求出满足 $\gcd(a_l,a_{l+1},\dots,a_r)= r-l+1$ 的所以有序整数对 $(l,r)$。  

然后不难发现一个引理：如果 $l,r$ 满足 $\gcd(a_l,a_{l+1},\dots,a_r)= r-l+1$，那么我们只需要在 $l,r$ 之间任意修改一个数字就可以满足题目的条件了。  
这样就成了线段覆盖问题，只需要按左端点从小到大排序（其实求出来的时候就是按照左端点从小大的所以不需要排序），然后每个区间尽量选择最右边的点即可。  

核心代码：
```cpp
int gcd(int x,int y){ if(!x) return y; if(!y) return x; return gcd(y,x%y); }
int n,ln,a[maxn],st[20][maxn];
int l[maxn],r[maxn],cnt,nowgcd,nowr,ans[maxn],las,lasans;
int main(){
	n=read(); ln=log2(n); int i,j; for(i=1;i<=n;i++) a[i]=read(),st[0][i]=a[i];
	for(j=1;j<=ln;j++) for(i=1;i<=n;i++) if(i+(1<<j)-1<=n) st[j][i]=gcd(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	for(i=1;i<=n;i++){
		nowgcd=a[i]; nowr=i; if(a[i]==1){ l[++cnt]=i; r[cnt]=i; continue; }
		for(j=ln;j>=0;j--) if(nowr+(1<<j)<=n&&gcd(nowgcd,st[j][nowr+1])>=nowr+(1<<j)-i+1)
			nowgcd=gcd(nowgcd,st[j][nowr+1]),nowr=nowr+(1<<j);
		if(nowgcd==nowr-i+1) l[++cnt]=i,r[cnt]=nowr;
	}
	for(i=1;i<=cnt;i++) if(l[i]>las){ ans[r[i]]=++lasans; las=mmax(las,r[i]); }
	for(i=1;i<=n;i++) ans[i]=mmax(ans[i],ans[i-1]),print(ans[i]),pc(' '); return 0;
}
```

---

## 作者：xishanmeigao (赞：0)

（[题目传送门](https://www.luogu.com.cn/problem/CF1632D)）

设 $ans_i$ 表示长度为 $i$ 的 $a$ 前缀答案。

首先有 $ans_i=ans_{i-1}$，然后只需考虑是否删掉这个 $i$。

有经典结论：固定右端点 $r$ 的时候，它的后缀 $\gcd$ 最多只有 $\log V$ 种。

于是我们可以求出所有以 $i$ 结尾的后缀 $\gcd$，然后判断一下这个 $\gcd$ 是否可能会等于一个后缀长度即可。如果存在这样的 $\gcd$，就把 $a_i$ 改为一个大质数，然后 $ans_i$ 加一。

时间复杂度 $\mathcal{O}(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=2e5+10,M=5e6+10;

int n,a[N];
pii pre[M],fd[N][40],pr[M];
int cnt,len[N],ans;

int main()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);

	for(int i=1; i<=n; i++)
	{
		int cnt2=cnt;
		for(int j=1; j<=cnt2; j++)
			pr[j]=pre[j];
		pr[++cnt2]={a[i],i};
		for(int j=1; j<=cnt2; j++)
			pr[j].fi=__gcd(pr[j].fi,a[i]);
		pr[0]={0,0};
		for(int j=1; j<=cnt2; j++)
			if(pr[j].fi!=pr[j-1].fi)
				fd[i][++len[i]]=pr[j];

		bool pd=1; fd[i][len[i]+1]={0,i+1};
		for(int j=1; j<=len[i]; j++)
		{	
			if(fd[i][j].fi>i-fd[i][j+1].se+1 && fd[i][j].fi<=i-fd[i][j].se+1)
			{
				pd=0;
				break;
			}
		}

		if(!pd)
			a[i]=998244353, ans++;
		len[i]=0;

		pre[++cnt]={a[i],i};
		for(int j=1; j<=cnt; j++)
			pre[j].fi=__gcd(pre[j].fi,a[i]);
		pre[0]={0,0};
		for(int j=1; j<=cnt; j++)
			if(pre[j].fi!=pre[j-1].fi)
				fd[i][++len[i]]=pre[j];
		cnt=len[i];
		for(int j=1; j<=len[i]; j++)
			pre[j]=fd[i][j];
		fd[i][++len[i]]={0,n+1}; 

		printf("%d ",ans);
	}
	
	return 0;
}
```

---

## 作者：subcrip (赞：0)

最直接的做法，不需要二分，也不需要数据结构（ST 表/线段树等）。

对于每个点 $i$，我们用一个数组 $v$ 存放一些点对 $(pos,val)$，其中 $pos$ 表示满足 $\gcd(a_{pos},\cdots,a_i)=val$ 的最大的下标 $pos$。由于 $val$ 之间至少相差 $2$ 倍，所以不同的 $val$ 至多有 $\log_2a_i$ 个，亦即 $v$ 最多有 $\log_2a_i$ 个元素。

我们从左到右遍历数组。对于每个元素，遍历 $v$ 数组并找出不符合题目要求的点，也就是说存在某个 $pos$ 到下一个 $pos'$ 之间有点 $j$ 使得 $val$ 恰好等于 $i-j+1$ 的情况。每次遇到这种情况，我们就直接贪心地把 $a_i$ 改成一个和数组中的其他元素都不同的质数。并且题目不要求输出修改后的序列，所以实际上不需要修改，只需要把 $v$ 清空，只留下一个点对 $(i,1)$ 即可。

时间复杂度是 $O(n\log^2U)$，$U$ 是值域。有两个 $\log$ 的原因是计算 $\gcd$ 的复杂度也是 $\log U$。

```cpp
void solve() {
    read(int, n);
    readvec(int, a, n);

    vector<pii> v;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        vector<pii> nw;

        nw.emplace_back(i, a[i]);
        int prev = a[i];
        for (auto&& [j, g] : v) {
            int curr = gcd(g, a[i]);
            if (curr != prev) {
                prev = curr;
                nw.emplace_back(j, curr);
            }
            if (curr == 1) break;
        }
        int k = nw.size();

        for (int j = 0; j < k; ++j) {
            int s = nw[j].first;
            int e = (j + 1 == k ? -1 : nw[j + 1].first);

            if (nw[j].second < i - e + 1 and nw[j].second >= i - s + 1) {
                res += 1;
                nw = {{ i, 1 }};
            }
        }

        v = nw;
        cout << res << " \n"[i + 1 == n];
    }
}
```

---

## 作者：船酱魔王 (赞：0)

# CF1632D New Year Concert 题解

## 题意回顾

对于长度为 $ n $ 的数组 $ a $，我们定义区间 $ [l,r] $ 不合法当且仅当 $ \gcd_{i=l}^{r}a_i=r-l+1 $。请分别求出 $ a $ 的每个前缀内没有不合法区间的最小修改次数。

$ n \le 2 \times 10^5 $，$ a_i \le 10^9 $。

## 分析

发现本题关键结论：当一个区间变长时，$ r-l+1 $ 严格递增，但是 $ \gcd_{i=l}^{r} $ 非严格递减，因此对于每个 $ i $，最多存在一个 $ x $ 使得 $ [x,i] $ 不合法。

用 ST 表预处理出区间 gcd，显然可以用二分找到这个 $ x $。

又发现，可以把一个数被修改为一个很大的质数，使得包含这个数的所有区间合法，因此只需修改一个数，显然修改右边界 $ i $ 而非左边界 $ x $ 更优，因为这样使得右边界右移之后更多的左边界位置一定合法，因此我们把二分左边界更改为 $ i $，答案加一。

注意二分时的区间开闭问题。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
int st[N][20];
int gcd(int x, int y) {
	if(y == 0) {
		return x;
	}
	return gcd(y, x % y);
}
int getgcd(int l, int r) {
	int k = (int)log2(r - l + 1);
	return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		st[i][0] = a[i];
	}
	for(int j = 1; j <= 20; j++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
	int sum = 0;
	int lst = 0;
	for(int i = 1; i <= n; i++) {
		int l, r, mid;
		l = lst;
		r = i;
		while(l + 1 < r) {
			mid = (l + r) >> 1;
			if(getgcd(mid, i) < i - mid + 1) {
				l = mid;
			} else {
				r = mid;
			}
		}
		if(getgcd(r, i) == i - r + 1) {
			sum++;
			lst = i;
		}
		printf("%d ", sum);
	}
	printf("\n");
	return 0;
}
```

## 总结与评价

这道题码量不大，但是重点在于关键结论的发现和贪心策略，是一道很好的小清新思维题。

---

## 作者：E_firework (赞：0)

首先我们要找到了所有不满足 $\gcd{\{a_l,a_{l+1},\dots,a_r\}}\ne r-l+1$ 的区间 $[l,r]$。观察性质，我们发现不满足条件的区间一定不会互相包含，因为如果区间 $[l_1,r_1]$ 包含了区间 $[l_2,r_2]$(两个区间不相同)，则有 $\gcd{\{a_{l_1},a_{l_1+1},\dots,a_{r_1}\}}\le\gcd{\{a_{l_2},a_{l_2+1},\dots,a_{r_2}\}}$ 且 $r_1-l_1+1<r_2-l_2+1$。因为不满足条件的区间一定不会互相包含，那么将所有区间按左端点排序后，右端点一定单调递增，于是我们可以用尺取法找到所有不满足条件的区间。

假设当前的区间是 $[l,r]$，如果 $\gcd{\{a_l,a_{l+1},\dots,a_r\}}=r-l+1$，则找到了一个不满足条件的区间，然后将左端点和右端点都右移一位。
如果 $\gcd{\{a_l,a_{l+1},\dots,a_r\}}<r-l+1$，就右移左端点，否则右移右端点。而 $\gcd{\{a_l,a_{l+1},\dots,a_r\}}$ 可以用线段树或 ST 表维护。

找到所有不满足条件的区间后，至少操作一次就能使得这样的区间满足条件，且不会影响其他区间，一种方案是把区间中一个数修改为一个大质数，则问题转化为了经典的区间选点问题。又因为区间互不包含，所以每次只需要取最右边的一个区间的左端点。定义 $dp_i$ 为 $f(a_1,a_2,\dots,a_i)$(主要是因为这样比较简洁)。如果有不满足条件的区间 $[x,i]$ 则 $dp_i=dp_{x-1} +1$，否则 $dp_i=dp_{i-1}$。

时间复杂度 $O(n(\log n+\log V))$。其中 $V$ 为 $a$ 中最大值。

code:
```cpp
#include <bits/stdc++.h>
#define LL long long
#define mes(s, x) memset(s, x, sizeof(s))
using namespace std;
inline LL read(){char c;c = getchar();while(!(('0' <= c && c <= '9') || c == '-')) c = getchar();bool flag = 0;if(c == '-'){flag = 1;c = getchar();}LL tot = 0;while('0' <= c && c <= '9'){tot = 10 * tot + c - '0';c = getchar();}return flag ? -tot : tot;}
inline void _write(LL i){if(i == 0) return;_write(i / 10);putchar(i % 10 + '0');return;}
inline void write(LL i){if(i == 0) putchar('0');else if(i < 0){putchar('-');_write(-i);}else _write(i);return;}
int a[200005], st[20][200005], lb[200005], dp[200005];//lb[i]表示右端点为 i 的不满足条件的区间的左端点，没有则为 0
int gcd(int i, int j){
	if(i < j) return gcd(j, i);
	if(j == 0) return i;
	return gcd(j, i % j);
}
int ans(int l, int r){
	int k = log2(r - l + 1);
	return gcd(st[k][l], st[k][r - (1 << k) + 1]);
}
int main(){
	int n = read(), t;
	for(int i = 1; i <= n; i++){
		st[0][i] = a[i] = read();
	}
	for(int i = 1; (1 << i) <= n; i++){
		for(int j = 1; j + (1 << i) - 1 <= n; j++){
			st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
		}
	}
	int l = 1, r = 1;
	lb[0] = 0;
	while(r <= n){
		t = ans(l, r);
		if(t == r - l + 1){
			lb[r] = l;
			l++;
			r++;
		}else if(t < r - l + 1){
			l++;
		}else{
			lb[r] = lb[r - 1];
			r++;
		}
	}
	for(int i = 1; i <= n; i++){
		if(!lb[i]) dp[i] = 0;
		else dp[i] = dp[lb[i] - 1] + 1;
		write(dp[i]);
		putchar(' ');
	}
	return 0;
}
```

udp:[关于ST表的复杂度](https://oi-wiki.org/ds/sparse-table/#%E9%99%84%E5%BD%95st-%E8%A1%A8%E6%B1%82%E5%8C%BA%E9%97%B4-gcd-%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%E5%88%86%E6%9E%90)

---

