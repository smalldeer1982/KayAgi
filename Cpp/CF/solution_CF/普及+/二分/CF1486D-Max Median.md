# Max Median

## 题目描述

给定一个长度为 $n$ 的序列 $a$，求所有长度 $\ge k$ 的连续子序列中，中位数的最大值。定义中位数是一个长度为 $x$ 的序列升序排序后的第 $\left\lfloor\frac{x+1}{2}\right\rfloor$ 位的值。

## 样例 #1

### 输入

```
5 3
1 2 3 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
1 2 3 4```

### 输出

```
3```

# 题解

## 作者：MiPloRAs_3316 (赞：16)

[可能更好的食用体验](/blog/560595/solution-cf1486d) $|$ 
[题目传送门](/problem/CF1486D)

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Analysis 思路}}}}$

先给题目贴个 tag：**二分答案**，**思维性不错**

显然，假设最后的答案为 $ans$，那么一定会有以下 $2$ 条性质：
1. 大于 $ans$ 的值无法成为某区间的中位数；
2. 小于等于 $ans$ 的值一定是某区间的中位数。

由此，我们可以进行二分答案。

---

那么，如何判断某一个答案 $x$ 能否成为某个区间的中位数呢？

可以先研究一下区间内中位数的性质：

![](https://cdn.luogu.com.cn/upload/image_hosting/rl3ovcao.png)

1. 大于等于中位数的数**至少**有 $\left( \left\lfloor\dfrac{len}{2}\right\rfloor+1\right)$ 个；
2. 小于中位数的数**至多**有 $\left\lfloor\dfrac{len}{2}\right\rfloor$ 个。

所以，不论区间长度 $len$ 是奇还是偶，大于等于中位数的数必定比小于等于中位数的数多。

综上所述：在判断时，我们可以将整个数组中**大于等于** $x$ 的数都抽象为 $+1$，**小于** $x$ 的数抽象为 $-1$。然后跑一遍前缀和 $sum$ 数组，又因为题目要求区间长度要大于 $k$，所以我们把 $sum_i$ 减去 $i-k$ 号位置之前的**前缀最小值**得到最大的区间和。（$sum_i-x=y$，$sum_i$ 的值是固定的，为了使 $y$ 尽可能的大，$x$ 就要尽可能的小。）

---
$\large{\textbf{\textsf{\color{RoyalBlue}{Code 代码}}}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,k,a[maxn],sum[maxn],Min[maxn];
bool check(int x)
{
//sum 记录前缀和数组，Min 记录前 i 个 sum 中的最小值
	for(int i=1; i<=n; i++)
	{
		sum[i]=sum[i-1];
		Min[i]=Min[i-1];
		if(a[i]>=x) sum[i]++;
		else sum[i]--;
		Min[i]=min(Min[i],sum[i]);
	}
	for(int i=k; i<=n; i++)
		if(sum[i]-Min[i-k]>=1) return true;
	return false;
} 
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	int l=0,r=maxn;
	while(l+1<r)
	{
		int mid=l+(r-l)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}//二分可能的中位数 x，使得中位数 >=x 
	printf("%d\n",l);
	return 0;
}
```

---

## 作者：registerGen (赞：6)

upd：改正一处笔误（感谢 mazihang2022 指出）。

# Solution

一句话题解（提示）：P2824。

具体题解如下。

二分答案 $x$，然后 check 一下答案是否能 **大于等于** $x$。

如果你做过 P2824，那么你应该知道有这样一个套路：

因为此时我们只关心 $a_1\sim a_n$ 和 $x$ 的相对大小关系，所以我们可以构造一个序列 $b$：

$$b_i=\begin{cases}1,&a_i\ge x\\-1,&a_i<x\end{cases}$$

如果 $\displaystyle\sum_{i=l}^r b_i>0$，那么序列 $[a_l,\cdots,a_r]$ 的中位数一定 $\ge x$。

所以我们扫一遍 $b$，维护一下 $b$ 的前缀和和前缀最小值（由于可以不选，所以这个玩意还要和 $0$ 取 $\min$（没明白的看一下代码））就行了。（在这里 RIP 一下 henrytb 大佬，写了个线段树还 FST 了。。）

# Code

```cpp
inline bool check(int x){
	rep(i,1,n)b[i]=(a[i]>=x?1:-1);
	rep(i,1,n)sum[i]=sum[i-1]+b[i],minn[i]=std::min(minn[i-1],sum[i]);
	rep(i,m,n)if(sum[i]-minn[i-m]>0)return 1;
	return 0;
}
 
void solve(){
	n=ri(),m=ri();
	rep(i,1,n)a[i]=ri();
	int l=1,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
}
```

---

## 作者：pomelo_nene (赞：3)

又是个什么套路题。

考虑到求最大，又有一些长的很奇怪的限制，那我们就二分答案，其单调性是显然的。

考虑如何判定。用 P2824 的套路，将小于它的数置为 $-1$，否则置为 $1$。滚一遍前缀和。如果存在一个长度大于等于 $k$ 的区间，满足答案是我们当前的答案，那么存在一个 $i \geq k$，使得 $sum_i > \min(\min_{i=1}^{i-k} sum_i,0)$。

按此方法做即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005],sum[200005],n,len;
bool check(int p)
{
 	for(int i=1;i<=n;i++)	sum[i]=(a[i]>=p?1:-1)+sum[i-1];
	for(int fuck=0,i=len;i<=n;i++)
    {
		fuck=min(fuck,sum[i-len]);
		if(sum[i]>fuck) return true;
	}
	return false;
}
int main()
{
	scanf("%d %d",&n,&len);
	for(int i=1;i<=n;i++) scanf("%d",a+i),b[i]=a[i];
	sort(b+1,b+1+n);
	int R=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)	a[i]=lower_bound(b+1,b+1+R,a[i])-b;
	int l=1,r=R,ans=1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
        if(check(mid))	l=mid+1,ans=mid;
        else	r=mid-1;
	}
    printf("%d",b[ans]);
    return 0;
}
```

---

## 作者：rui_er (赞：2)

考古到了这题，来补篇题解（

看到中位数，显然与数的绝对大小无关，只与相对大小有关，考虑将每个数进行一些转化。对于一个数 $x$，容易想到将 $\ge x$ 的都改为 $1$，$\lt x$ 的都改为 $-1$，得到新数列（这里称作 $b_i$）。此时便有一个结论：对于区间 $\left[l,r\right]$，如果满足 $\sum\limits_{i=l}^rb_i\gt 0$，则 $a_l,a_{l+1},\cdots,a_r$ 的中位数必定 $\ge x$（可以从与 $x$ 的相对大小角度想）。

因此考虑每次二分 $x$，记录 $b$ 数组的前缀和和前缀最小值，在区间长度 $\ge k$ 时差分计算一下即可。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, k, a[N], b[N], s[N], mx[N], L, R, ans;
bool check(int M) {
	rep(i, 1, n) {
		b[i] = a[i] < M ? -1 : 1;
		s[i] = s[i-1] + b[i];
		mx[i] = min(mx[i-1], s[i]);
		if(i >= k && s[i] - mx[i-k] > 0) return 1;
	}
	return 0;
}

int main() {
	scanf("%d%d", &n, &k);
	rep(i, 1, n) scanf("%d", &a[i]);
	L = 1; R = n; ans = -1;
	while(L <= R) {
		int M = (L + R) >> 1;
		if(check(M)) ans = M, L = M + 1;
		else R = M - 1;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：masonpop (赞：1)

考虑二分答案。注意到，一个区间内中位数 $\ge x$ 的充要条件是区间内 $\ge x$ 的数的个数**严格大于** $<x$ 的数的个数。

设 $b_i$ 为 $a_i$ 是否 $\ge x$，值为 $1$ 或 $-1$。问题转化为是否存在一个长度 $\ge k$ 的区间，使得区间和 $\ge 1$。这是经典问题了，前缀和即可。复杂度 $O(n\log n)$。[代码](https://codeforces.com/contest/1486/submission/218441940)。

---

## 作者：lnwhl (赞：1)

模拟赛时遇到这道题，来写一篇题解。
## 题目描述
给定一个长度为 $n$ 的序列 $a$，求所有长度 $\ge k$ 的连续子序列中，中位数的最大值。

定义中位数是一个长度为 $x$ 的序列升序排序后的第 $\left\lfloor\frac{x+1}{2}\right\rfloor $ 位的值。
## 思路
很明显答案具有单调性，所以可以想到**二分答案**。

那如何判断是不是中位数呢？其实可以比较套路的构造一个相对大小数组 $b$，如果 $a_{i}\ge x$，$b_{i}=1$，否则 $b_{i}=-1$。如果一段区间的区间和大于 $0$，那么该段区间的中位数一定大于等于 $x$。

所以我们可以构造一个 b 数组的前缀和数组。又因为题目要求区间长度要大于 $k$，所以我们把 $i$ 位置的前缀和减去 $i-k$ 位置之前的最小值得到最大的区间和。其实就是 $sum_{i}-prmin_{i-k}$。这样我们便可以通过本题了。

时间复杂度 $O(n\log n)$。具体见代码。（代码里的 $b$ 数组省略了，直接求的前缀和）
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200005],sum[200005],prmin[200005];
inline bool check(int x)//check当前的x是否可行 
{
	memset(sum,0,sizeof(sum));//b数组的前缀和（b数组省略了） 
	memset(prmin,0,sizeof(prmin));//前缀和的最小值 
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1];prmin[i]=prmin[i-1];
		if(a[i]>=x)sum[i]++;
		else sum[i]--;
		if(sum[i]<prmin[i])prmin[i]=sum[i];//求最小值 
	}
	for(int i=k;i<=n;i++)
		if(sum[i]-prmin[i-k]>0)//为满足区间长度大于k 
			return 1;
	return 0;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=1,r=n,mid;
	while(l<r)//二分答案 
	{
		mid=(l+r+1)>>1;
		if(check(mid))l=mid;
		else r=mid-1;
	}
	cout<<l;
	return 0;
}
```


---

## 作者：Little09 (赞：1)

我们考虑二分答案 $x$，只要判断是否存在 $≥x$ 的解。

在判断时，把大于等于 $x$ 的数替换成 $1$，其他数替换成 $-1$。那么就进行了一个转换：一段中位数至少是 $x$ 转换为了这段的和是正的。所以查找新序列中有没有一个长度至少是 $k$ 的子串满足和为正即可。

发现就是求长度至少是 $k$ 的子串的和的最大值。这个问题可以使用前缀和，维护前缀和的前缀最小值。枚举子串长度的右端点 $i$，找到 $1$ 到 $i-k$ 的前缀最小值即可。所以总复杂度是 $O(n\log n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
const int N=200005;
int a[N],b[N],s[N],p[N];
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
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
bool check(int x)
{
	for (int i=1;i<=n;i++) 
	{
		if (a[i]>=x) b[i]=1;
		else b[i]=-1;
	}
	for (int i=1;i<=n;i++) s[i]=s[i-1]+b[i];
	p[0]=0;
	for (int i=1;i<=n;i++) p[i]=min(p[i-1],s[i]);
	int res=-100000000;
	for (int i=k;i<=n;i++)
	{
		res=max(res,s[i]-p[i-k]);
	}
	if (res>0) return 1;
	return 0; 
}
int main()
{
	n=read(),k=read();
	for (int i=1;i<=n;i++) a[i]=read();
	int l=1,r=n;
	while (l<=r)
	{
		int mid=(l+r)/2;
		if (check(mid)==1) l=mid+1;
		else r=mid-1;
	}
	cout << r << endl;
	return 0;
}
  
```


---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF1486D) $|$ 
[题目传送门](/problem/CF1486D) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

不难看出答案具有单调性，因此考虑使用二分答案。

接着考虑 check 怎么写。  
假设当前的答案为 $x$，可以遍历一遍原序列 $a$，将 $a_i<x$ 的标记为 $-1$，$a_i\ge x$ 的标记为 $1$。根据中位数的性质，如果一段区间内的标记的和 $\ge1$，就说明这一段区间的中位数至少为 $x$。为了不超时，可以使用一个前缀和数组 $sum$ 维护一段区间的标记的和。

然而，题目要求的是区间长度 $\ge k$，而非 $=k$。可以贪心地维护一个数组 $mi$，使 $mi_i=\max(0,\min\limits_{j=1}^i sum_j)$。若 $sum_i-mi_{i-k}\ge1$，则说明以 $i$ 为右端点，长度 $\ge k$ 的区间中一定有中位数至少为 $x$ 的。

理解了这些，代码不难实现。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
long long n,k;
int a[maxn],s[maxn],mi[maxn];
bool ok(int x)
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]<x)s[i]=s[i-1]-1;//标记&前缀和
		else s[i]=s[i-1]+1;
		mi[i]=min(mi[i-1],s[i]);//维护1~n中的前缀和的最小值
	}
	for(int i=k;i<=n;i++)//枚举右端点，判断是否有区间的中位数至少为x
		if(s[i]-mi[i-k]>0)return true;
	return false;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	int l=0,r=1e9;
	while(l+1<r)//二分答案
	{
		int mid=(l+r)/2;
		if(ok(mid))l=mid;
		else r=mid;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：walk_out_study (赞：0)

### 题意

求序列 $a$ 中所有长度 $\geq k$ 的连续子序列的最大中位数 $ans$。

### 思路

本题答案具有单调性。假设 $a$ 已排序。如果 $a_i$ 是最大的中位数，则其他数满足以下条件：
- $a_1 \sim a_i \leq ans$ 满足条件。
- $a_{i+1} \sim a_n>ans$ 不满足条件。

直接用二分答案，找 $x$ 是否满足 $x \leq ans$。

#### Check 怎么写？

先寻找条件的特性：

- $\ge x$ 的数，与 $=x$ 的数并无区别。若它们是中位数，就满足条件。
 
- $<x$ 的数，若它们是中位数，就不满足条件。

##### 中位数的小知识

- 如果长度为奇数：中位数为第 $\frac{n+1}{2}$ 个数。假设长度为 $5$，就有 $3$ 个满足条件的数，$2$ 个不满足的数，差值为 $1$。

- 如果长度为偶数：中位数为第 $\frac{n}{2}$ 个数。假设长度为 $4$，就有 $3$ 个满足条件的数，$1$ 个不满足的数，差值为 $2$。

因此，我们可以认定，二者之差若 $\ge1$，就满足条件。

------
两者之差可以预处理一下，将到 $i$ 时的两者之差设为 $s_i$

考虑枚举区间结尾，右边界为 $a_r$，则左边界 $l=1\sim (r-k+1)$。

此区间的差就是：$s_r-s_{l-1}$。现在 $s_r$ 已经固定了，只要找到最小的 $s_{l-1}$。定义 $dp_i$ 为处理到 $i$ 时，$s_{1\sim i}$ 的最小值，也可以预处理一下。

--------
这样处理单个子序列只需 $O(1)$ 的复杂度，总共处理 $n-cnt+1$ 个区间。再二分枚举 $x$。时间复杂度 $O(n\log n)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+10;
int n,k,a[N],t[N],ans,dp[N];
bool ck(int x) {
	for(int i=1;i<=n;i++) {
		t[i]+=t[i-1];
        if(x<=a[i]) {
			t[i]++;
		}
		else {
			t[i]--;
		}
		dp[i]=min(dp[i-1],t[i]);
	}
	for(int i=k;i<=n;i++) {
		if(t[i]-dp[i-k]>=1) {
			return 1;
		}
	}
	return 0;
}
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
	}
	int l=0,r=1e16+1;
	while(l+1<r) {
		int mid=l+r>>1;
		if(ck(mid)) {
			ans=l=mid;
		}
		else {
			r=mid;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：REAL_曼巴 (赞：0)

好久之前遇到的一个题，复习的时候把题解写一下。

这个题目的解法与许多中位数有关的题目的套路类似。

此题目具有单调性，我们可以二分答案 $x$ 。为了快速进行每个 $x$ 的判断，我们可以以 $x$ 为中心建立一个数列，比其大的数我们设成 $1$ ，反之我们设成 $-1$ 。

有了这样一个序列，我们可以知道，当某一段的和是正的，代表他这段的中位数至少是 $x$ 。

为了求和，我们可以为这个序列开一个前缀和来进行前缀最小值的维护。如果每段右端点是 $r$ ，为了满足区间长度比 $k$ 大，我们可以判断一下 $min_{i-k}$ 是否为正数即可。

这道题可以算是中位数相关问题的板子，可以好好研究一下。

```
#include<iostream>
using namespace std;
int a[1000001],b[1000001],c[1000001],d[1000001];
int n,k;

inline bool check(int x){
    int ans=-0x3f3f3f3f;
    for(int i=1;i<=n;++i)if(a[i]>=x)b[i]=1;else b[i]=-1;
    c[1]=b[1];
    for(int i=2;i<=n;++i)c[i]=c[i-1]+b[i];
    d[0]=0;
    for(int i=1;i<=n;i++)d[i]=min(d[i-1],c[i]);
    for(int i=k;i<=n;i++)ans=max(ans,c[i]-d[i-k]);
    if(ans>0) return 1;
	return 0; 
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];
    int l=0,r=2147483646;
    while(l<=r){
        int mid=(l+r)/2;
		if(check(mid)==1) l=mid+1;
		else r=mid-1;
	}
	cout<<r<<endl;
    return 0;
}
```



---

