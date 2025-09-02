# [ABC341G] Highest Ratio

## 题目描述

给定一个长度为 $N$ 的数列 $A=(A_1,A_2,\ldots,A_N)$。  
对于 $k=1,2,\ldots,N$，请解决以下问题。

- 选择满足 $k\leq r\leq N$ 的整数 $r$ 时，求数列 $A$ 的第 $k$ 项到第 $r$ 项的平均值可能取得的最大值。  
  这里，数列 $A$ 的第 $k$ 项到第 $r$ 项的平均值定义为 $\frac{1}{r-k+1}\displaystyle\sum_{i=k}^r A_i$。

## 说明/提示

### 数据范围

- $1\leq N\leq 2\times 10^5$
- $1\leq A_i\leq 10^6$
- 输入均为整数

### 样例解释 1

对于 $k=1$，可选的 $r$ 有 $r=1,2,3,4,5$，每种情况下的平均值分别为：
- $r=1$ 时，$\frac{1}{1}=1$
- $r=2$ 时，$\frac{1}{2}(1+1)=1$
- $r=3$ 时，$\frac{1}{3}(1+1+4)=2$
- $r=4$ 时，$\frac{1}{4}(1+1+4+5)=2.75$
- $r=5$ 时，$\frac{1}{5}(1+1+4+5+3)=2.8$

因此，$r=5$ 时取得最大值，$k=1$ 时的答案为 $2.8$。  
同理，$k=2,3,4,5$ 时分别在 $r=4,4,4,5$ 时取得最大值，对应的值为 $\frac{10}{3}=3.333\ldots$、$\frac{9}{2}=4.5$、$\frac{5}{1}=5$、$\frac{3}{1}=3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 1 4 5 3```

### 输出

```
2.80000000
3.33333333
4.50000000
5.00000000
3.00000000```

## 样例 #2

### 输入

```
3
999999 1 1000000```

### 输出

```
999999.00000000
500000.50000000
1000000.00000000```

# 题解

## 作者：ケロシ (赞：13)

很好的一道题。

首先对于序列区间平均数的计算，有一个 trick，就是把序列区间平均数转化成一个**计算几何模型**。

首先，设序列 $A$ 前缀和数组为 $S$，

那么区间 $[l,r]$ 的平均数为 $\frac{S_r-S_{l-1}}{r-l+1}$，

仔细观察，发现这个式子很像一个斜率的式子，

所有把数组下标当成横轴，前缀数组当作纵轴，设点数组为 $P$, 

那么 $P_{l-1}$ 和 $P_{r}$ 的横坐标之差是区间序列长度，纵坐标之差就是区间和，

也就是区间 $[l,r]$ 的平均数就是点 $P_{l-1}$ 到点 $P_{r}$ 的**斜率**，

下面是以样例为例子画的一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/jjtsk524.png)

那么题面转化为对于点 $P_{i-1}$，找到一个点 $P_j~(i-1< j)$，且 $P_{i-1}$ 到 $P_j$ 的斜率最大。 

这是一个经典斜率优化问题，

先考虑如何求一个 $P_{i-1}$ 的答案，发现可以对于 $P_{i-1}$ 到 $P_{n}$ 建**凸包**，而凸包上与点 $P_{i-1}$ 的连边的斜率就是答案。

为什么呢，假设凸包上与 $P_{i-1}$ 的连边为 $P_j$，而设 $P_k$ 在直线 $P_{i-1}P_j$ 下方，那么 $P_k$ 可以被忽略，因为对于 $P_{i-1}P_k$ 的斜率不及 $P_{i-1}P_j$，且对于编号小于 $i-1$ 的点也是没有贡献的，这样的话最后有贡献的点会变为一个凸包。

![](https://cdn.luogu.com.cn/upload/image_hosting/oejn1bea.png)

维护凸包的话直接使用 Andrew 维护上凸壳即可。

时间复杂度 $O(n)$。

```cpp
struct Point{
	ll x, y;
	Point(ll x = 0, ll y = 0): x(x), y(y) {}
};
struct Vector{
	ll x, y;
	Vector(ll x = 0, ll y = 0): x(x), y(y) {}
};
Vector operator - (Point A, Point B){
	return Vector(A.x - B.x, A.y - B.y);
}
ll Cross(Vector A, Vector B){
	return A.x * B.y - A.y * B.x;
}
const int N = 2e5 + 5;
int n, a[N];
ll s[N];
double ans[N];
Point st[N]; int tp;
void solve() {
	cin >> n;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) s[i] = s[i - 1] + a[i];
	ROF(i, n, 0) {
		Point cur = {i, s[i]};
		while(tp > 1 && Cross(st[tp] - cur, st[tp] - st[tp - 1]) < 0) tp--;
		st[++tp] = cur;
		Vector v = st[tp] - st[tp - 1];
		ans[i + 1] = (double) v.y / v.x;
	}
	cout << fixed << setprecision(8) << endl;
	FOR(i, 1, n) cout << ans[i] << endl;
}
```

---

## 作者：Estelle_N (赞：5)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc341_g)

长度 $n$ 的数列 $A=(A_1,A_2,\ldots,A_n)$。

对于每个 $k$ $(1\le k\le n)$，选择满足 $k\le r\le n$ 的整数 $r$，使得 $A$ 序列第 $k$ 项到第 $r$ 项的平均值的最大。

## Solution

设 $s_i$ 为 $a_i$ 的前缀和，$f_i$ 为 $i$ 位置的答案。

$$
f_{i+1}=\max_{j=i+1}^n \dfrac{s_j-s_i}{j-i}
$$

即点 $(i,s_i)$ 和点 $(j,s_j)$ 所在直线斜率的最大值。

倒序枚举，使用单调栈维护上凸壳即可。

## Code

```cpp
#include <cstdio>

#define int long long

using namespace std;

const int N = 200005;

int n, top, a[N], s[N]; double f[N];

double slope(int x, int y) {return 1.0 * (a[x] - a[y]) / (x - y);}

signed main()
{
    scanf("%lld", &n);
    for(int i = 1; i <= n; ++ i)
        scanf("%lld", &a[i]), a[i] += a[i - 1];

    s[++top] = n;
    for(int i = n - 1; i >= 0; -- i)
    {
        while(top > 1 && slope(s[top - 1], i) < slope(s[top - 1], s[top])) -- top;
        f[i + 1] = slope(s[top], i);
        s[++top] = i;
    }
    for(int i = 1; i <= n; ++ i) printf("%.8lf\n", f[i]);

    return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：5)

最简单的一集。

转化一下题意，等价于找一个 $r$ 最大化 $\displaystyle\frac{s_r-s_{k-1}}{r-(k-1)}$，其中 $s$ 是前缀和。

等价于把 $(i,s_i)$ 放到二维平面上去之后，对每个点求其到右侧某点连线的最大斜率。从右往左扫描所有点，直接单调栈维护上凸壳即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
#define MAXN 300005

int n,s[MAXN],st[MAXN],top = 0;
double Ans[MAXN];

inline double slope( int x , int y ){ return ( 1.0 * s[y] - 1.0 * s[x] ) / ( 1.0 * y - 1.0 * x ); }

signed main(){
	scanf("%lld",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&s[i]),s[i] += s[i - 1];
	for( int i = n ; i >= 0 ; i -- ){
		while( top > 1 && slope( i , st[top] ) <= slope( st[top] , st[top - 1] ) ) top --;
		if( top ) Ans[i + 1] = slope( i , st[top] );
		st[++top] = i;
	}
	for( int i = 1 ; i <= n ; i ++ ) printf("%.12Lf\n",Ans[i]); puts("");
	return 0;
}
```

---

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/18018813)。妈的，被 trick 干爆了。

---

> $\textbf{Trick}$：将所有 $N_i=(i,\sum\limits_{j=1}^i a_j)$ 视作一点，则区间 $[l,r]$ 的平均值为 $(N_{l-1},N_r)$ 的斜率。
>
> $\textbf{Prove}$：由 $\text{slope}=\dfrac{y_2-y_1}{x_2-x_1}$ 易证。

根据这个 trick，$k$ 的答案即为 $k\le r\le n$ 中 $(N_{k-1},N_r)$ 斜率最大的一个。从后往前维护上凸壳即可。

[code](https://atcoder.jp/contests/abc341/submissions/50404379)，时间复杂度 $O(n)$。


---

## 作者：cqbzlzm (赞：1)

### Description

给你一个 $n$ 个数的数组，求以每个位置开头的最大平均数的子串的平均数。

**数据范围：**$1\leq n\leq 2\times 10^5$。

### Solution

首先想到前缀和，令 $s_i$表示前缀和。

然后平均数就是 $\frac{s_r-s_{l-1}}{r-(l-1)}$，我们发现这个像一个直线的斜率。我们令每个 $i$ 对应了一个点 $(i,s_i)$。然后用单调队列维护一个凸包就行了。

![](https://pic.imgdb.cn/item/65d4a8509f345e8d03d063ff.png) 

如图，我们按斜率维护一个单调队列，比如 $A,B,C$ 就是一个单调队列。像 $G$ 这样点是被单调队列筛掉的点。为什么这样的点不会成为答案呢？

1. 新来的点在 $E$。那么 $EB$ 显然比 $EG$ 好，所以 $G$ 没用。
2. 新来的点在 $F$。那么 $FC$ 肯定比 $FG$ 好，所以 $G$ 没用。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int n, stk[MAXN + 5], tp, a[MAXN + 5];
double ans[MAXN + 5], sum[MAXN + 5];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	int tp = 1;
	for (int i = n; i >= 0; i --) {
		while (tp > 2 && (sum[stk[tp - 1]] - sum[i]) * (stk[tp - 2] - stk[tp - 1]) <= (sum[stk[tp - 2]] - sum[stk[tp - 1]]) * (stk[tp - 1] - i))
			tp --;
		if (i < n) ans[i + 1] = (sum[stk[tp - 1]] - sum[i]) / (stk[tp - 1] - i);
		stk[tp ++] = i;
	}
	for (int i = 1; i <= n; i ++) printf("%.8lf\n", ans[i]);
	return 0;
}
```

---

## 作者：0x3F (赞：1)

记 $S_i$ 为 $A_i$ 的前缀和，则 $\frac{1}{r-k+1}\sum_{i=k}^{r}A_i=\frac{S_r-S_{k-1}}{r-(k-1)}$，则问题转化为对于每一个 $k$，求出 $r\ge k$ 时， $(k-1,S_{k-1})$ 和 $(r,S_r)$ 斜率的最大值。

从右往左维护上凸壳即可，时间复杂度 $O(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 2e5 + 10;
int n, t, stk[_];
long long sum[_];
long double a[_];
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> sum[i];
		sum[i] += sum[i-1];
	}
	t = 1;
	stk[t] = n;
	for (int i = n-1; i >= 0; i--) {
		while (t >= 2 && (sum[stk[t]] - sum[i]) * (stk[t-1] - i) <= (sum[stk[t-1]] - sum[i]) * (stk[t] - i)) t--;
		a[i+1] = (long double)(sum[stk[t]] - sum[i]) / (long double)(stk[t] - i);
		stk[++t] = i;
	}
	cout << fixed << setprecision(20);
	for (int i = 1; i <= n; i++) {
		cout << a[i] << endl;
	}
	return 0;
}
```

---

## 作者：YangRuibin (赞：0)

# 题意转化

本题要求最大平均数，也就是区间和与下标差的商。

对于每个 $a_i$ 记 $\sum_{j=1}^ia_j$ 为 $s$ 即可把 $a_i$ 转化为点 $(i,s)$ 那么区间平均值可表示为两个点的斜率。

接下来要解决的问题就是如何求出每个点之后与它连线斜率最大的点。

# 重点讲解

暴力枚举肯定会超时，我们考虑点之间的关系。

情况 1：从后往前相邻两点之间斜率逐渐增大，形成一个凸起。

![](https://cdn.luogu.com.cn/upload/image_hosting/og55cagi.png)

如图，因为继续枚举时与当前点连接斜率较小的点在与之后的点（如图中红点）连接时可能成为最优解，这些点所以需保留。

情况 2：对与当前点，后面的一些点形成一个凹陷。

![](https://cdn.luogu.com.cn/upload/image_hosting/1f0m0lk0.png)

如图，不管后面的点怎么排列，都不可能选到中间的黑点，所以这些点需排除。

因为从前往后枚举时，添加依次进行，而排除是从前往后的，所以这个过程能用栈维护。又因为每个点最多入栈一次，出栈一次，所以总时间复杂度为 $O(n)$ 可以通过。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,a[N],st[N],tot;
double ans[N];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i),a[i]+=a[i-1];//输入并求前缀和
	a[n+1]=-1;
	st[++tot]=n+1;
	for(int i=n-1;i>=0;i--)
	{
		st[++tot]=i+1;
		while((a[st[tot]]-a[i])*1.0/(st[tot]-i)<(a[st[tot-1]]-a[i])*1.0/(st[tot-1]-i))//排除不合法点
			tot--;
		ans[i+1]=(a[st[tot]]-a[i])*1.0/(st[tot]-i);//加入可能成为答案的点
	}
	for(int i=1;i<=n;i++)printf("%0.8lf\n",ans[i]);
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

记人生中第一次 AK 一场 abc。

### 1 题意

给定一个长度为 $n$ 的正整数序列 $a$，对于每个 $i(1\le i\le n)$，确定一个 $j(i\le j\le n)$，最大化 $\dfrac{1}{j-i+1}\sum_{k=i}^{j}a_k$，即区间的平均数。

### 2 思路

设 $s$ 为 $a$ 的后缀和的**相反数**，即 $s_i=-\sum_{j=i}^n a_j$，那么我们可以发现 $a_{[l,r]}$ 的平均数就是 $\dfrac{s_{r+1}-s_{l}}{r+1-l}$。我们可以转化为，设平面上第 $i(1\le i\le n+1)$ 个点为 $(i,s_i)$，则 $a_{[l,r]}$ 的平均数就是点 $l$ 和点 $r+1$ 的直线的斜率。

对于每个左端点求一个右端点，使得斜率最大，这是一个很经典的问题，从右往左扫描，用单调栈维护一个上凸壳即可。时间复杂度 $\Theta(n)$。

### 3 代码与记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define max_n 2000000
int n;
double a[max_n+2];
double s[max_n+2];
int st[max_n+2],top=0;
double ans[max_n+2];
double calc(int u,int v){return (s[v]-s[u])/(v-u);}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("g_1.in","r",stdin);
	freopen("g_1.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lf",a+i);
	for(int i=n;i>=1;--i)s[i]=s[i+1]-a[i];
	st[top=1]=n+1;
	for(int i=n;i>=1;--i){
		while(top>=2&&calc(i,st[top])<=calc(st[top],st[top-1]))--top;
		ans[i]=(s[st[top]]-s[i])/(st[top]-i);
		st[++top]=i;
	}
	for(int i=1;i<=n;++i)printf("%.8lf\n",ans[i]);
	return 0;
}
```

By **dengziyue**

---

## 作者：Scinerely (赞：0)

### 题目描述

给出一个长度为 $n$ 的序列 $A$。

对于每一个 $k \in [1,n]$，希望求出一个 $r \in [k,n]$ 使得 $\frac{1}{r-k+1}\sum_{i=k}^r a_i$ 尽量大。

### 思路点拨

考虑枚举一个 $k$,然后希望 $\frac{1}{r-k+1}\sum_{i=k}^r a_i$ 尽量大。我们二分一个答案 $lim$,判断是否存在 $r \in [k,n]$ 满足

$$\frac{1}{r-k+1}\sum_{i=k}^ra_i \geq lim$$

$$\sum_{i=k}^ra_i \geq lim(r-k+1)$$

定义前缀和数组 $sum_i=\sum_{j \leqslant i}a_j$，那么：

$$sum_r-sum_{k-1}\geq lim(r-k+1)$$

$$-lim\times r +sum_r\geq lim(-k+1)+sum_{k-1}$$

我们希望求出 $-lim\times r +sum_r$ 的最大值就可以check了。注意到这个式子十分像一个一次函数，所以可以使用李超线段树维护。时间复杂度 $O(n \log^2 V)$。

AT上可以通过，但是需要精细化实现。

```
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
namespace fastIO{
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
		while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
		return x*f;
	}
	int buf[20],TOT;
	inline void print(int x,char ch=' '){
		if(x<0) putchar('-'),x=-x;
		else if(x==0) buf[++TOT]=0;
		for(int i=x;i;i/=10) buf[++TOT]=i%10;
		do{putchar(buf[TOT]+'0');}while(--TOT);
		putchar(ch);
	}
}
using namespace fastIO;
const int MAXN=2e5+10;
const double eps=1e-6;
int n,sum[MAXN],inf;
inline double fun(int x,int y){
	double Y=1.0*y*eps;
	return -1.0*x*Y+1.0*sum[x];
} 
struct node{
	int l,r,x;
}t[MAXN*120];
int rot,tot;
void insert(int &i,int l,int r,int k){
	if(!i) i=++tot;
	if(!t[i].x) return (void)(t[i].x=k);
	if(l==r){
		if(fun(t[i].x,l)<fun(k,l)) swap(t[i].x,k);
		return ;
	}
	int mid=(l+r-1)>>1;
	if(fun(t[i].x,mid)<fun(k,mid)) swap(t[i].x,k);
	if(fun(t[i].x,l)<fun(k,l)) insert(t[i].l,l,mid,k);
	if(fun(t[i].x,r)<fun(k,r)) insert(t[i].r,mid,r,k);
}
double query(int i,int l,int r,int k){
	if(!i) return -1000000000000.0;
	if(l==r) return fun(t[i].x,k);
	int mid=(l+r-1)>>1;
	double ans=fun(t[i].x,k);
	if(mid>=k) ans=max(ans,query(t[i].l,l,mid,k));
	else ans=max(ans,query(t[i].r,mid,r,k));
	return ans;
}
double tmp[MAXN];
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+read();
		inf=max(inf,(sum[i]-sum[i-1])*1000000);
	}
	for(int i=n;i;i--){
		insert(rot,-inf,inf,i);
		int l=-inf,r=inf;
		while(l<r){
			int mid=(l+r-1)/2+1;
			double Y=mid*eps;
			if(query(rot,-inf,inf,mid)>=(1.0*sum[i-1]-1.0*i*Y+Y))
				l=mid;
			else r=mid-1;
		}
		tmp[i]=1.0*l*eps;
	}
	for(int i=1;i<=n;i++) printf("%.6Lf\n",tmp[i]);
	return 0;
}

```




---

## 作者：Shunpower (赞：0)

## Statement

给定一个序列 $a$，对于每一个 $k\in [1,n]$，求出 $\frac{1}{r-k+1}\sum\limits_{i=k}^{r} a_i(r\geq k)$。

$1\leq n\leq 2\times 10^5,1\leq a_i\leq 10^6$。

## Solution

算是（某种意义上的？）斜率优化板子。

考虑给 $a$ 垒一个前缀和，式子化为 $\frac{s_r-s_{k-1}}{r-(k-1)}$，这可以看作是 $(k-1,s_{k-1})$ 与 $(r_,s_r)$ 连线的斜率。于是你对于每个 $i\in[0,n]$ 都把 $(i,s_i)$ 放进平面直角坐标系，题目转化为在每个点右边的点里求一个使得连线斜率最大的点。

考虑从右往左扫这些点，显然动态使用单调栈维护一个斜率单调递减的上凸壳即可。根据上凸壳性质，显然对于点 $i$ 而言让它连线斜率最大的点就是现在上凸壳最靠左的点的点，所以直接取出单调栈栈顶计算斜率，即可得到 $i+1$ 处的答案（因为前缀和那里有一个 $-1$）。

---

## 作者：Hooch (赞：0)

### 题意

给一个长度为 $n$ 的序列 $A$，对于每一个 $i$ ( $1 \le i \le n$ )，求出：

$$
\max\limits_{j = i}^n\frac{\sum\limits_{k = i}^jA_k}{j - i + 1}
$$

### 题解

首先将 $\sum\limits_{k = i}^jA_k$ 转化为 $S_{j} - S_{i - 1}$，其中 $S$ 是前缀和数组。式子变成了 $\frac{S_{j} - S_{i - 1}}{j - i + 1}$，这个东西相当于在笛卡尔坐标系上点 $(i - 1,S_{i - 1})$ 和点 $(j, S_j)$ 连成的直线的斜率。

现在问题转化成了，对于每个 $i$ 求 $(i - 1, S_{i - 1})$ 与 $(j, S_j)$ ( $i \le j \le n$ ) 的最大斜率。不难想到维护上凸壳。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ld = long double;
const int N = 2E5 + 5;
int a[N], n, st[N], top; i64 s[N]; ld ans[N];
ld slv(int u, int v) {return (ld)(s[u] - s[v]) / (u - v);}
signed main(void) {
  ios :: sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  reverse(a + 1, a + 1 + n);
  for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
  st[++top] = 0;
  for (int i = 1; i <= n; ++i) {
    while (top > 1 && slv(i, st[top]) < slv(st[top], st[top - 1])) --top;
    ans[i] = slv(i, st[top]); st[++top] = i;
  }
  for (int i = 1; i <= n; ++i)
    cout << setprecision(9) << fixed << ans[n - i + 1] << '\n';
  return 0;
}
```

---

## 作者：lzyqwq (赞：0)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/18018552)**

因为大于号打成小于号赛后 $5\min$ 过的，我是什么品种的傻逼，破大防。

**[题目传送门](https://atcoder.jp/contests/abc341/tasks/abc341_g)**

> - 给出长度为 $N$ 的序列 $A_1\sim A_N$，对于每个 $i$，求：
>
> $$\max\limits_{r=i}^N\dfrac{\sum_{j=i}^r A_j}{r-i+1}$$
>
> - $N\le 2\times 10^5$，$A_i\le 10^6$。
>
> - $\text{2 s / 1 GB}$。

先做一遍前缀和，记为 $s_i=\sum\limits_{j=1}^iA_j$，然后考虑二分答案能否 $\ge g$。

记 $S(i,r)=\dfrac{s_r-s_{i-1}}{r-i+1}$，这个条件等价于在 $[i,N]$ 中存在一个 $r$ 使得 $S(i,r)\ge g$。

整理可得我们要判断是否存在 $r\in[i,N]$ 使得 $s_r-gr\ge s_{i-1}-gi+g$。容易发现右边是定值，只要求左边的最大值。

令 $z=s_r-gr$，则 $gr+z=s_r$，考虑平面上由 $(r,s_r)$ 构成的点集，相当于在点集中找一个点使得，过这个点作斜率为 $g$ 的直线，截距最大。那么这个东西一定在一个**从右至左**斜率非降的上凸包上。

记 $P_u(x_u,y_u)$ 表示上凸包上斜率第 $i$ 靠右的点。记 $K(P,Q)$ 表示直线 $PQ$ 的斜率，画图可以发现当 $K(P_u,P_{u+1})\le g$ 时，$P_{u+1}$ 不比 $P_u$ 更劣；当 $K(P_u,P_{u+1})>g$ 时，$P_{u}$ 比 $P_{u+1}$ 更优。

那最大的 $u$ 使得 $K(P_u,P_{u+1})\le g$ 一定是一个最优决策。由于斜率单调，用单调队列维护上凸包，二分找到这个点即可得到最大值，然后判断是否合法。

设值域为 $V$，时间复杂度为 $\mathcal{O}(N\log N\log |V|)$，空间复杂度为 $\mathcal{O}(N)$。

**[AC Code](https://atcoder.jp/contests/abc341/submissions/50389757)**

---

## 作者：xzf_200906 (赞：0)

假设第 $l$ 个位置的答案为 $x$，则：
$$\max_{r \in [l,N]}\dfrac{1}{r-l+1}\sum^r_{i=l}A_i=x$$
转化为前缀和：

$$\max_{r \in [l,N]}\dfrac{S_r-S_{l-1}}{r-l+1}-x=0$$
$$\max_{r \in [l,N]}S_r-S_{l-1}-x(r-l+1)=0$$
$$\max_{r \in [l,N]}S_r-xr-S_{l-1}+x(l-1)=0$$
$$\max_{r \in [l,N]}S_r-xr=S_{l-1}-x(l-1)$$
可以发现，等式左边是一个与 $x$ 有关的下凸壳，而右边是一个与 $x$ 有关的一次函数，所以我们要求的 $x$ 是一条直线与一个下凸壳的交点的横坐标，使用单调栈维护凸壳并在凸壳上二分即可。

附样例1 $l=2$ 时的图，其中黑色直线为等式右边的一次函数，其它直线为凸壳。

![](https://cdn.luogu.com.cn/upload/image_hosting/a2r08rub.png)

代码：
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
struct Line{
	LL k,b;
	double l,r;
};
double inter(Line a,Line b){
	return 1.0*(b.b-a.b)/(a.k-b.k);
}
const int inf=1000000;
Line que[1000000];
LL s[1000000];
double ans[1000000];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		s[i]+=s[i-1];
	}
	int tail=0;
	que[0]={-n*2,-s[n],0,0};
	for(int i=n;i>=1;i--){
		Line now={-i,s[i],0,0};
		while(tail){
			if(inter(now,que[tail])>que[tail].l){
				que[tail].r=inter(now,que[tail]);
				break;
			}
			tail--;
		}
		tail++;
		que[tail]={now.k,now.b,que[tail-1].r,inf};
		now={-i+1,s[i-1],0,0};
		int l=1,r=tail,pos=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(inter(now,que[mid])>que[mid].r) l=mid+1;
			else if(inter(now,que[mid])<que[mid].l) r=mid-1;
			else{
				pos=mid;
				break;
			}
		}
		ans[i]=inter(que[pos],now);
	}
	for(int i=1;i<=n;i++) printf("%.7lf\n",ans[i]);
}
```

---

