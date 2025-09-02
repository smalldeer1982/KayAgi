# Friends and Subsequences

## 题目描述

Mike and !Mike are old childhood rivals, they are opposite in everything they do, except programming. Today they have a problem they cannot solve on their own, but together (with you) — who knows?

Every one of them has an integer sequences $ a $ and $ b $ of length $ n $ . Being given a query of the form of pair of integers $ (l,r) $ , Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/77a91e450d8c58a8cff349889db0f7900b8e3ace.png) while !Mike can instantly tell the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/7594cca965e5cc163cc16e32e5bed1c0ba0fa037.png).

Now suppose a robot (you!) asks them all possible different queries of pairs of integers $ (l,r) $ $ (1<=l<=r<=n) $ (so he will make exactly $ n(n+1)/2 $ queries) and counts how many times their answers coincide, thus for how many pairs ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689D/72e28ce968021e0cd2b5fe1a6f144994e8f8338b.png) is satisfied.

How many occasions will the robot count?

## 说明/提示

The occasions in the first sample case are:

1\. $ l=4 $ , $ r=4 $ since $ max{2}=min{2} $ .

2\. $ l=4 $ , $ r=5 $ since $ max{2,1}=min{2,3} $ .

There are no occasions in the second sample case since Mike will answer $ 3 $ to any query pair, but !Mike will always answer $ 1 $ .

## 样例 #1

### 输入

```
6
1 2 3 2 1 4
6 7 1 2 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 3 3
1 1 1
```

### 输出

```
0
```

# 题解

## 作者：Eroded (赞：11)

### 思路

首先看到 $\max\limits^r_{i=l}a_i$ 和 $\min\limits^r_{i=l}b_i$，我们很容易想到 ST 表来优化区间最大/最小值查询，不会 ST 表的来[这里](https://oi-wiki.org/ds/sparse-table/)。

但是光有 ST 表的时间复杂度仍为 $O(n^2)$，不符合题目 $n \leq 2\times10^5$ 的要求，于是我们考虑优化。

不难想到，如果左端点 $l$ 固定，那么 $\max\limits^{i}_{k=l}a_k$ 和 $\min\limits^{i}_{k=l}a_k$ 一定单调不降/不增，此时右端点 $r$ 的取值范围一定是连续的，于是我们可以确定以任意一个 $l$ 作为左端点时的满足条件的 $r$ 的个数。

所以我们只需要求每一个 $r$ 的最大/最小值。

看到这句话，我们不难想到二分搜索，于是可以用二分搜索+ ST 表 AC 这道题。

总复杂度 $O(n\log n)$，通过。

如果看不懂逻辑可以参考代码理解一下。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f1[200100][30],f2[200100][30],sum;//f1代表a,f2代表b
int qmax(int l,int r){//ST表取a的(l,r)中最大值
    if(l == r) return f1[l][0];
	int k = log2(r - l + 1);//也可以预处理
	return max(f1[l][k],f1[r - (1 << k) + 1][k]);
}
int qmin(int l,int r){//ST表取b的(l,r)中最小值
    if(l == r) return f2[l][0];
	int k = log2(r - l + 1);//同上
	return min(f2[l][k],f2[r - (1 << k) + 1][k]);
}
int ql(int i){//二分左端点
	int l = i,r = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(qmax(i,mid) < qmin(i,mid)) l = mid + 1;//如果太小就增加
		else r = mid - 1;//否则减小
	}
	if(l <= n && qmax(i,l) == qmin(i,l)) return l;//注意特判
	return 0;
}
int qr(int i){//二分右端点，同上
	int l = i,r = n;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(qmax(i,mid) > qmin(i,mid)) r = mid - 1;
		else l = mid + 1;
	}
	if(r > 0 && qmax(i,r) == qmin(i,r)) return r;
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>f1[i][0];
	}
	for(int i = 1;i <= n;i++){
		cin>>f2[i][0];
	}
	for(int j = 1;j <= 21;j++){//预处理ST表
		for(int i = 1;i + (1 << j) - 1 <= n;i++){
			f1[i][j] = max(f1[i][j - 1],f1[i + (1 << (j - 1))][j - 1]);
		}
	}
    for(int j = 1;j <= 21;j++){//同上
		for(int i = 1;i + (1 << j) - 1 <= n;i++){
			f2[i][j] = min(f2[i][j - 1],f2[i + (1 << (j - 1))][j - 1]);
		}
	}
	for(int i = 1;i <= n;i++){
		int l = ql(i),r = qr(i);//二分搜索
		if(l == 0) continue;//满足特判会退出
		if(r == 0) continue;
		if(l > r) swap(l,r);//保险
		sum += (r - l + 1);
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：henrytb (赞：7)

在这里介绍一个防止二分写挂的神仙方法（今天教练介绍的2333

我们先枚举一个左端点，发现随着右端点的增长，$\min$ 值单调递减，$\max$ 值单调递增。

于是可以二分一下这个右端点的可能区间。具体就二分一下右端点区间的左端和右端点区间的右端即可。使用 ST 表优化查询区间 $\min$、$\max$ 值的速度。

但是，这个二分很容易**写挂**！

怎么办？

我们索性不考虑二分的边界啥的，在 $l$ 与 $r$ 距离很小的时候就跳出二分，然后暴力地在这个 $l$ 和 $r$ 之间找一下即可！

这样可以减少很多细节的考虑！方便考场调试代码！

具体见代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=2e5+5;
int n,a[N],b[N];
int mn[N][22],mx[N][22];
signed main() {
    scanf("%lld",&n);
    rep(i,1,n) scanf("%lld",&a[i]),mx[i][0]=a[i];
    rep(i,1,n) scanf("%lld",&b[i]),mn[i][0]=b[i];
    rep(j,1,21) {
        rep(i,1,n) {
            if(i+(1<<(j-1))-1>n) mx[i][j]=mx[i][j-1];
            else mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
        }
    }
    rep(j,1,21) {
        rep(i,1,n) {
            if(i+(1<<(j-1))-1>n) mn[i][j]=mn[i][j-1];
            else mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
        }
    }
    int ans=0;
    rep(i,1,n) {
        int l=i,r=n;
        int rr=0,ll=0;
        while(r-l>5) {
            int mid=(l+r)>>1;
            //printf("de:%lld %lld %lld\n",l,r,mid);
            int lg=log2(mid-i+1);
            int mxx=max(mx[i][lg],mx[mid-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[mid-(1<<lg)+1][lg]);
            if(mxx>mnn) r=mid;
            else l=mid;
        }
        per(j,r,l) {
            int lg=log2(j-i+1);
            int mxx=max(mx[i][lg],mx[j-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[j-(1<<lg)+1][lg]);
            if(mxx==mnn) {rr=j;break;}
        }
        l=i,r=n;
        while(r-l>5) {
            int mid=(l+r)>>1;
            int lg=log2(mid-i+1);
            int mxx=max(mx[i][lg],mx[mid-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[mid-(1<<lg)+1][lg]);
            if(mxx>=mnn) r=mid;
            else l=mid;
        }
        rep(j,l,r) {
            int lg=log2(j-i+1);
            int mxx=max(mx[i][lg],mx[j-(1<<lg)+1][lg]);
            int mnn=min(mn[i][lg],mn[j-(1<<lg)+1][lg]);
            if(mxx==mnn) {ll=j;break;}
        }
        if(ll&&rr) ans+=(rr-ll+1);
    }
    printf("%lld",ans);
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：3)

#### Description

> 给定两个大小为 $n$ 的序列 $a_i,b_i$，求有多少个数对 $(l,r)$ 且 $1 \le l \le r \le n$ 满足：
> $$\max\limits_{i=l}^r a_i=\min\limits_{i=l}^r b_i$$

#### Solution

ST + 二分，首先思考一个 $\mathcal O(n^2)$ 算法，不难想到，可以 $\mathcal O(n \log n)$ 预处理 ST 表，然后暴力枚举 $(l,r)$ 看是否满足要求。

我们把问题转化一下，固定左界 $l$，往右不难发现不考虑极端情况越靠近 $l$ $\max\{a_i\}$ 越会小于 $\min\{b_i\}$，越靠近 $n$ $\max\{a_i\}$ 越会大于 $\min\{b_i\}$，在 $[l,n]$ 中会存在一个区间 $[l',r']$ 使得这个区间里的数满足要求，那么不如直接二分 $l'$ 和 $r'$ 并在二分中判断是否满足要求，预处理可以用 ST 表完成，然后让答案加上 $r'-l'+1$ 即可。

这样是 $\mathcal O(n \log n+n \log n)$（预处理 + 询问）的，轻松通过。

#### Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int a[200086];
int b[200086];

int dpa[200086][20]; // max
int dpb[200086][20]; // min

int Max (int l, int r) {
	if (l > r) swap(l, r);
	int k = log2(r - l + 1);
	return max(dpa[l][k], dpa[r - (1 << k) + 1][k]);
}

int Min (int l, int r) {
	if (l > r) swap(l, r);
	int k = log2(r - l + 1);
	return min(dpb[l][k], dpb[r - (1 << k) + 1][k]);
}

int binsearch_l (int l, int r, int n) {
	int left = l;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (Max(left, mid) < Min(left, mid)) l = mid + 1;
		else r = mid - 1;
	}
	if (l <= n && Max(left, l) == Min(left, l)) return l;
	else return 0;
}

int binsearch_r (int l, int r, int n) {
	int left = l;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (Max(left, mid) > Min(left, mid)) r = mid - 1;
		else l = mid + 1;
	}
	if (r >= 1 && Max(left, r) == Min(left, r)) return r;
	else return 0;
}

signed main () {
	int n;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
	for (int i = 1; i <= n; i++) dpa[i][0] = a[i];
	for (int i = 1; i <= n; i++) dpb[i][0] = b[i];
	for (int k = 1; (1 << k) <= n; k++)
		for (int i = 1; i + (1 << k) - 1 <= n; i++)
			dpa[i][k] = max(dpa[i][k - 1], dpa[i + (1 << (k - 1))][k - 1]);
	for (int k = 1; (1 << k) <= n; k++)
		for (int i = 1; i + (1 << k) - 1 <= n; i++)
			dpb[i][k] = min(dpb[i][k - 1], dpb[i + (1 << (k - 1))][k - 1]);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int l = binsearch_l(i, n, n);
		int r = binsearch_r(i, n, n);
		if (l != 0 && r != 0) {
			if (l > r) swap(l, r);
			int ans = (r - l + 1);
			cnt += ans; 
		}
	} 
	printf("%lld", cnt);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

## 思路

ST 表 + 二分。

首先我们发现一个性质，如果固定左端点 $l$，那么随着右端点 $r$ 变大，$\max\limits_{i=l}^r a_i$ 一定是单调不减的，相反，$\min\limits_{i=l}^r a_i$ 一定是单调不增的。因此，$\max\limits_{i=l}^r a_i$ 与 $\min\limits_{i=l}^r b_i$ 的大小关系一定是先有一段是大于，然后一段等于，最后一段小于。

于是就可以二分了。枚举左端点，那么在 $[l,n]$ 这段区间中会存在区间 $[a,b]$（有可能是空区间），使得其中的每一个 $i$ 都能满足条件。就可以想到二分最左的 $a$ 和最右的 $b$，算出区间长度累加至答案中即可。

时间复杂度 $O(n \log n)$。

~~推荐一道也是 ST 表 + 二分的题 [CF1454F](https://www.luogu.com.cn/problem/CF1454F)~~

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 200100;
const int logn = 20;

ll n, f[maxn][logn], g[maxn][logn];

ll qmax(int l, int r) {
	int k = log2(r - l + 1);
	return max(f[l][k], f[r - (1 << k) + 1][k]);
}

ll qmin(int l, int r) {
	int k = log2(r - l + 1);
	return min(g[l][k], g[r - (1 << k) + 1][k]);
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &f[i][0]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &g[i][0]);
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
			g[i][j] = min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
		}
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		int l = i, r = n, ansl = -1, ansr = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (qmax(i, mid) == qmin(i, mid)) {
				ansl = mid;
				r = mid - 1;
			} else if (qmax(i, mid) < qmin(i, mid)) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		if (ansl == -1) {
			continue;
		}
		l = i;
		r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (qmax(i, mid) == qmin(i, mid)) {
				ansr = mid;
				l = mid + 1;
			} else if (qmax(i, mid) < qmin(i, mid)) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		ans += ansr - ansl + 1;
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：Limit (赞：2)

# 题目大意

给出两个长度为 $n$ 的序列 $a$ 和 $b$,计算有多少对 $l,r$ 满足 $\max\{a_l,a_{l+1},\dots,a_{r-1},a_r\}=\min\{b_l,b_{l+1},\dots,b_{r-1},b_r\}$.

# 分析

考虑 $\max$($\min$)的一些性质,$\max\{a_l,a_{l+1},\dots,a_{r-1},a_r\}\leq\max\{a_l,a_{l+1},\dots,a_r,a_{r+1}\}$($\min\{b_l,b_{l+1},\dots,b_{r-1},b_r\}\geq\min\{b_l,b_{l+1},\dots,b_r,b_{r+1}\}$),那么就可以发现这个东西是单调的,所以就很容易想到去二分查找.枚举左端点,查找右端点,可以发现符合条件的右端点肯定是一段区间(可能没有),那么可以二分出这个合法区间的左端点和右端点,然后就可以直接计算贡献了,考虑到取药计算区间最值,所以可以用st表维护.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=3e5+7;
int n;
int a[MAXN];
int log_2[MAXN];
int lrmax[MAXN][24];
int lrmin[MAXN][24];
int QueryMax(int left,int right)//查询区间最大值
{
	int len=log_2[right-left+1];
	return max(lrmax[left][len],lrmax[right-(1<<len)+1][len]);
}
int QueryMin(int left,int right)//查询区间最小值
{
	int len=log_2[right-left+1];
	return min(lrmin[left][len],lrmin[right-(1<<len)+1][len]);
}
int main()
{
	scanf("%d",&n);
	REP(i,1,n)
	{
		scanf("%d",&lrmax[i][0]);
	}
	REP(i,1,n)
	{
		scanf("%d",&lrmin[i][0]);
	}
	int now=0;
	REP(i,1,n)//预处理log2(向下取整)
	{
		if(i==(1<<(now+1)))
		{
			++now;
		}
		log_2[i]=now;
	}
	REP(i,1,now)//预处理st表
	{
		REP(j,1,n+1-(1<<i))
		{
			lrmax[j][i]=max(lrmax[j][i-1],lrmax[j+(1<<(i-1))][i-1]);
			lrmin[j][i]=min(lrmin[j][i-1],lrmin[j+(1<<(i-1))][i-1]);
		}
	}
	int left,right,middle,l_appear,r_appear;
	long long answer=0;//注意开long long
	REP(i,1,n)
	{
		left=i;
		right=n;
		l_appear=0;
		r_appear=0;
		while(left<=right)//二分右端点
		{
			middle=(left+right)>>1;
			if(QueryMax(i,middle)>QueryMin(i,middle))//如果max大了那么就减小
			{
				right=middle-1;
			}
			else
			{
				if(QueryMax(i,middle)==QueryMin(i,middle))//如果max和min相等则记录位置
				{
					r_appear=middle;
				}
				left=middle+1;
			}
		}
		left=i;
		right=n;
		while(left<=right)//同理二分出左端点
		{
			middle=(left+right)>>1;
			if(QueryMax(i,middle)>=QueryMin(i,middle))
			{
				if(QueryMax(i,middle)==QueryMin(i,middle))
				{
					l_appear=middle;
				}
				right=middle-1;
			}
			else
			{
				left=middle+1;
			}
		}
		if(l_appear&&r_appear)//如果存在则计算贡献
		{
			answer+=(r_appear-l_appear+1);
		}
	}
	printf("%lld",answer);
	return 0;
}
```

---

## 作者：derta (赞：1)

[CF689D Friends and Subsequences](https://www.luogu.com.cn/problem/CF689D)

考虑枚举起点 $l$，容易发现
- $\max$ 值单调不降
- $\min$ 值单调不增

故可以二分 $r$，找到使得 $\max\limits_{i=l}^{r}a_i=\min \limits_{i=l}^{r}b_i$ 的左端点与右端点，易知只有两个端点之内的 $r$ 符合条件

由于需要维护静态区间 $\max$、$\min$，可以用 ST 表实现

时间复杂度 $O(n \log n)$

代码：

```cpp
#include <cstdio>
#include <cctype>
const int MAXN = 200000, lgMAXN = 17;
int n, a[MAXN + 5], b[MAXN + 5];
int lg[MAXN + 5], st_max[MAXN + 5][lgMAXN + 5], st_min[MAXN + 5][lgMAXN + 5];
long long ans;

int read() { //快读 
	char c = getchar();
	int x = 0, sign = 1;
	if(c == '-') {
		sign = -1;
		c = getchar();
	}
	while(!isdigit(c))
		c = getchar();
	while(isdigit(c)) {
		x = x*10 + c - '0';
		c = getchar();
	}
	return x*sign;
}

inline int Min(int x, int y)
{ return x < y ? x : y; }

inline int Max(int x, int y)
{ return x > y ? x : y; }

void input() { //读入 
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	for(int i = 1; i <= n; ++i)
		b[i] = read();
}

void init_lg() { //预处理lg(n)，使之后lg操作降为O(1) 
	for(int i = 2; i <= MAXN; ++i)
		lg[i] = lg[i >> 1] + 1;
}

void init_st() { //预处理st表 
	for(int i = n; i >= 1; --i) {
		st_max[i][0] = a[i]; 
		st_min[i][0] = b[i];
		for(int j = 1; i + (1 << j) - 1 <= n; ++j) {
			st_max[i][j] = Max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1]);
			st_min[i][j] = Min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1]);
		}
	}
}

inline int range_max(int l, int r) { //区间max 
	int k = lg[r - l + 1]; //如不预处理，这里会变成O(log n)而非O(1) 
	return Max(st_max[l][k], st_max[r - (1 << k) + 1][k]); //取max 
}

inline int range_min(int l, int r) { //区间min，同理 
	int k = lg[r - l + 1];
	return Min(st_min[l][k], st_min[r - (1 << k) + 1][k]);
}

int find_left(int start) { //找左端点 
	int l = start, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(range_max(start, mid) - range_min(start, mid) < 0)
			l = mid + 1;
		else
			r = mid - 1;
	}
	//r可能在左端点前的一个点，故取l 
	if(l <= n && range_max(start, l) - range_min(start, l) == 0)
		return l;
	return -1; //没有相等的 
}

int find_right(int start) { //找右端点，同理 
	int l = start, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(range_max(start, mid) - range_min(start, mid) > 0)
			r = mid - 1;
		else
			l = mid + 1;
	}
	if(r >= 1 && range_max(start, r) - range_min(start, r) == 0)
		return r;
	return -1;
}

inline int binary_search(int start) {
	int l = find_left(start), r = find_right(start);
	if(l != -1) //有相等的 
		return r - l + 1; //返回区间长度 
	return 0; //没有相等的，返回-1 
}

void solve() {
	for(int i = 1; i <= n; ++i) //枚举起点 
		ans += binary_search(i);
}

inline void output() //输出 
{ printf("%lld", ans); }

int main() {
	input();
	init_lg();
	init_st();
	solve();
	output();
	return 0;
}
```

---

## 作者：haiwenhan (赞：1)

# 一道裸的ST表题

首先很容易就可以想到暴力的算法，就是用ST表 dp [ i ] [ j ]表示第 i 个数往后2^j个数中的最小or最大值。（ NlogN 复杂度）

## NlogN+N^2，暴力枚举l和r。

**然后你就GG了。**

所以我们要对暴力枚举的部分加入优化————**出来吧，二分！**

------------

![](https://cdn.luogu.com.cn/upload/pic/46083.png)

首先，我们要明确一点，固定一左端点，右端点向右延申的过程中，max值是单调递减的，min值是单调递增的。

由此我们发现可以进行二分，来寻找max==min的第一个点和最后一个点。

ans再加上中间点的个数就行了，同时也是不会重复的。

总体来说，先打ST表，再枚举左端点l，二分查找max==min的末端点和首端点。

## 合起来NlogN。

OK看程序  ------>

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
int a[200005];
int b[200005];
int dpmax[200005][25];//max的ST表
int dpmin[200005][25];//min的ST表
long long ans;//不要忘了long long
int qmax(int l,int r)//ST表查询
{
    if(l==r) return dpmax[l][0];
    int k=log2(r-l);
    return max(dpmax[l][k],dpmax[r-(1<<k)+1][k]);
}
int qmin(int l,int r)//ST表查询
{
    if(l==r) return dpmin[l][0];
    int k=log2(r-l);
    return min(dpmin[l][k],dpmin[r-(1<<k)+1][k]);
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        dpmax[i][0]=a[i];
    }
    for(i=1;i<=n;i++)
    {
        scanf("%d",&b[i]);
        dpmin[i][0]=b[i];
    }
    for(j=1;j<=20;j++)//打好ST表，人人有责
    {
        for(i=1;i<=n;i++)
        {
            if(i+(1<<(j-1))<=n) dpmax[i][j]=max(dpmax[i][j-1],dpmax[i+(1<<(j-1))][j-1]);
        }
    }
    for(j=1;j<=20;j++)//打表*2
    {
        for(i=1;i<=n;i++)
        {
            if(i+(1<<(j-1))<=n) dpmin[i][j]=min(dpmin[i][j-1],dpmin[i+(1<<(j-1))][j-1]);
        }
    }
    for(i=1;i<=n;i++)//开始枚举l点
    {
        int x0,x1;//左点和右点
        int l=i,r=n;
        while(l<r)//二分搜左边的
        {
            int mid=(l+r)>>1;
            if(qmax(i,mid)>=qmin(i,mid)) r=mid;
            else l=mid+1;
        }
        x0=r;
        if(qmax(i,x0)>qmin(i,x0)) continue;
        l=x0,r=n;
        if(qmax(i,n)==qmin(i,n)) x1=n;//若全是max=min x1=n
        else 
        {
            while(l<r)//二分搜右边的
            {
                int mid=(l+r)>>1;
                if(qmax(i,mid)>qmin(i,mid)) r=mid;
                else l=mid+1;
            }
            x1=r-1;
        }
        ans+=(x1-x0+1);//统计答案
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：orz_z (赞：0)

### 题目大意

给定两个大小为 $n$ 的序列 $a_i,b_i$，求有多少个数对 $(l,r)$，满足 $1\le l\le r\le n$ 且


$$
\max_{i=l}^r a_i=\min_{i=l}^r b_i
$$

$1 \le n\le 2\times 10^5$，$|a_i|,|b_i|\le 10^9$。



### 解题思路

`ST` + 二分。



首先考虑一个 $\mathcal{O}(n^2)$ 算法，不难想到，可以 $\mathcal O(n \log n)$ 预处理 `ST` 表，然后暴力枚举 $(l,r)$ 看是否满足要求。

我们把问题转化一下，固定左界 $l$，往右不难发现不考虑极端情况越靠近 $l$，$\max\{a_i\}$ 越会小于 $\min\{b_i\}$，越靠近 $n$，$\max\{a_i\}$ 越会大于 $\min\{b_i\}$，在 $[l,n]$ 中会存在一个区间 $[l',r']$ 使得这个区间里的数满足要求。

不难发现这个东西是单调的满足单调，所以直接二分 $l'$ 和 $r'$ 并判断是否满足要求，预处理可以用 `ST` 表完成，然后让答案加上 $r'-l'+1$ 即可。

时间复杂度 $\mathcal O(n \log n+n \log n)$。



### CODE

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int a[200086];
int b[200086];

int mmax[200086][20];
int mmin[200086][20];

int Max(int l, int r)
{
    if (l > r)
        swap(l, r);
    int k = log2(r - l + 1);
    return max(mmax[l][k], mmax[r - (1 << k) + 1][k]);
}

int Min(int l, int r)
{
    if (l > r)
        swap(l, r);
    int k = log2(r - l + 1);
    return min(mmin[l][k], mmin[r - (1 << k) + 1][k]);
}

int findl(int l, int r, int n)
{
    int left = l;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (Max(left, mid) < Min(left, mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (l <= n && Max(left, l) == Min(left, l))
        return l;
    else
        return 0;
}

int findr(int l, int r, int n)
{
    int left = l;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (Max(left, mid) > Min(left, mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    if (r >= 1 && Max(left, r) == Min(left, r))
        return r;
    else
        return 0;
}

int n;

signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &b[i]);
    for (int i = 1; i <= n; i++)
        mmax[i][0] = a[i];
    for (int i = 1; i <= n; i++)
        mmin[i][0] = b[i];
    for (int k = 1; (1 << k) <= n; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            mmax[i][k] = max(mmax[i][k - 1], mmax[i + (1 << (k - 1))][k - 1]);
    for (int k = 1; (1 << k) <= n; k++)
        for (int i = 1; i + (1 << k) - 1 <= n; i++)
            mmin[i][k] = min(mmin[i][k - 1], mmin[i + (1 << (k - 1))][k - 1]);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int l = findl(i, n, n);
        int r = findr(i, n, n);
        if (l != 0 && r != 0)
        {
            if (l > r)
                swap(l, r);
            int ans = (r - l + 1);
            cnt += ans;
        }
    }
    printf("%lld\n", cnt);
    return 0;
}
```





---

## 作者：Utilokasteinn (赞：0)

## [Link](https://www.luogu.com.cn/problem/CF689D)

观察题目，容易发现对于确定的 $l$ ，随着 $r$ 的增大，$\max_{i=l}^{r}a_i$ 会单调不减。

同理，对于确定的 $l$ ，随着 $r$ 的增大，$\min_{i=l}^{r}b_i$ 单调不增。

那么对于同一个左端点 $l$，肯定有若干个 $r$ 满足

$$\max_{i=l}^{r}a_i=\min_{i=l}^{r}b_i$$

（也可能一个满足的 $r$ 也没有）

当然，这些因为一个单调递增，一个单调递减，所以满足条件的 $r$ 肯定是一段连续的区间（前提是有）。

枚举每一个左端点 $l$，找到最小满足条件的 $r$ 和最大满足条件的 $r$。设这两个位置分别为 $posl$ 和 $posr$，那么对答案的贡献为 $posr-posl+1$。

因为区间的最大值和最小值满足单调性，所以可以二分来找 $posl$ 和 $posr$。

至于如何查询区间的最值，可以用线段树或 ST 表等数据结构维护。因为这题不用修改，用线段树就多此一举了，而且时间复杂度还要加上一个 $\log$。于是我是用 ST 表维护的。

注意一个点，有可能以 $l$ 为左端点是没有满足条件的 $r$ 的，这个时候注意要特判一下。

时间复杂度 $O(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s*f;
}
int n,log_2[200005]={-1};
int f[200005][20],g[200005][20];
ll ans;
void input()
{
	n=read();
	for(int i=1;i<=n;i++)
		f[i][0]=read();
	for(int i=1;i<=n;i++)
		g[i][0]=read();
	for(int i=1;i<=n;i++)
		log_2[i]=log_2[i/2]+1;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			f[j][i]=max(f[j][i-1],f[j+(1<<i-1)][i-1]),
			g[j][i]=min(g[j][i-1],g[j+(1<<i-1)][i-1]);
}
bool check1(int l,int r)
{
	int k=log_2[r-l+1];
	int maxn=max(f[l][k],f[r-(1<<k)+1][k]);
	int minn=min(g[l][k],g[r-(1<<k)+1][k]);
	return maxn>=minn;
}
bool check2(int l,int r)
{
	int k=log_2[r-l+1];
	int maxn=max(f[l][k],f[r-(1<<k)+1][k]);
	int minn=min(g[l][k],g[r-(1<<k)+1][k]);
	return maxn<=minn;
}
int main()
{
	input();
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n;
		ll resl=0,resr=0;
		//找到最小的resl使得max[i,resl]=min[i,resl]
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check1(i,mid))
				r=mid-1,resl=mid;
			else l=mid+1;
		}
		l=i,r=n;
		//找到最大的resr使得max[i,resr]=min[i,resr]
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check2(i,mid))
				l=mid+1,resr=mid;
			else r=mid-1;
		}
		if(resl&&resr)ans+=resr-resl+1;
	}
	printf("%lld",ans);
	return 0;
}
```

谢谢观赏。

---

## 作者：zhengrunzhe (赞：0)

提供一个$twopointers+multiset$的

比较显然的性质:

$1.max \left \{a[l,r+1] \right \}>=max \left \{a[l,r] \right \}$

$2.min \left \{b[l,r+1] \right \}<=min \left \{b[l,r] \right \}$

$3. \text {综合1.2.可得} max \left \{a[l,r+1] \right \}-min \left \{b[l,r+1] \right \}>=max \left \{a[l,r] \right \}-min \left \{b[l,r] \right \}$

题目的限制是$max \left \{a[l,r] \right \}-min \left \{b[l,r] \right \}=0$

可以转化成$max \left \{a[l,r] \right \}-min \left \{b[l,r] \right \}>=0$的区间个数减去$max \left \{a[l,r] \right \}-min \left \{b[l,r] \right \}>=1$的区间个数

由于区间最大值减区间最小值具有单调性(越往外拓展值越大)，所以可以大力twopoints解决这两个问题

每次右指针拓展到最远，区间个数$+=n-r+1$

区间极值显然可以ST表，但我用了multiset

```cpp
#include<set>
#include<cstdio>
#include<algorithm>
using namespace std;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
const int N=2e5+10,inf=1e9+10;
multiset<int>mn;
multiset<int,greater<int> >mx;
typedef long long ll;
int a[N],b[N],n;
inline const void add(int x)
{
	mx.insert(a[x]);
	mn.insert(b[x]);
}
inline const void del(int x)
{
	mx.erase(mx.find(a[x]));
	mn.erase(mn.find(b[x]));
}
inline const ll twopointers(int k)
{
	ll cnt=0ll;
	int l=1,r=0;
	mx.clear();mn.clear();
	mx.insert(-inf);mn.insert(inf);
	while (r<=n)
	{
		while (*mx.begin()-*mn.begin()<k&&r<=n)add(++r);
		if (r>n)break;
		cnt+=n-r+1;
		del(l++);
	}
	return cnt;
}
int main()
{
	read(n);
	for (int i=1;i<=n;i++)read(a[i]);
	for (int i=1;i<=n;i++)read(b[i]);
	writeln(twopointers(0)-twopointers(1));
	return 0;
}
```

---

