# Weakness and Poorness

## 题目描述

You are given a sequence of n integers $ a_{1},a_{2},...,a_{n} $ .

Determine a real number $ x $ such that the weakness of the sequence $ a_{1}-x,a_{2}-x,...,a_{n}-x $ is as small as possible.

The weakness of a sequence is defined as the maximum value of the poorness over all segments (contiguous subsequences) of a sequence.

The poorness of a segment is defined as the absolute value of sum of the elements of segment.

## 说明/提示

For the first case, the optimal value of $ x $ is $ 2 $ so the sequence becomes $ -1 $ , $ 0 $ , $ 1 $ and the max poorness occurs at the segment "-1" or segment "1". The poorness value (answer) equals to $ 1 $ in this case.

For the second sample the optimal value of $ x $ is $ 2.5 $ so the sequence becomes $ -1.5,-0.5,0.5,1.5 $ and the max poorness occurs on segment "-1.5 -0.5" or "0.5 1.5". The poorness value (answer) equals to $ 2 $ in this case.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1.000000000000000
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
2.000000000000000
```

## 样例 #3

### 输入

```
10
1 10 2 9 3 8 4 7 5 6
```

### 输出

```
4.500000000000000
```

# 题解

## 作者：NOILinux_Ubuntu (赞：6)

#### 这道题~~, 百度看到有很多人用三分, 其实是可以二分滴

我们想到三分的原因是, 若f(x)为x的ans函数, 那么它**不单调**,而是一个类似二次函数的图像

### 但是虽然答案不单调, 我们仍然可以从中找到一些单调的东西

是什么呢??让我们继续看

------------


我们前缀和处理一下原序列, 设为S_i, 可以发现由于有绝对值, 所以我们要求的就是

$$ Max(S_i)-Min(S_j)\ \ \ 0\le i,j\le n$$


然后, 如果我们给原序列减去一个x, 很明显S_i的变化是
$$ S_1-1*x, \ \ S_2-2*x ,\ \  ...\ ... \ \ S_n-n*x$$

对于我们要求的式子, 改变后
$$Max(S_i-i*x)-Min(S_j-j*x)$$

>引理(感性证明)

>若i<j, 则使答案更优的x<0; 反之, 则x>0

由引理知若i与j的大小关系改变, 则更大的x不会使答案更优

由此, 可以构思出二分的思路:

>二分x, 处理原串(+或-)并求出其前缀和最小值位置l和最大值位置r(由于是double,所以最大/小值相等的情况任取即可)

>若l与r的大小关系和未处理前l与r大小关系相同, 则x可以更大,否则更小

稍微处理精度问题便可以a掉此题

------------

```
//CF578C Weakness and Poorness
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define ri register int
#define For(i,a,b) for(ri i=(a);i<=(b);++i)
#define DFor(i,a,b) for(ri i=(a);i>=(b);--i)
#define INF 0x7fffffff
#define MAXN 200005
template<class T>inline T Max(register T a,register T b){return a>b?a:b;}
template<class T>inline T Min(register T a,register T b){return a<b?a:b;}
const double eps=1e-13;
int n,ansr,ansl,L,R;
int a[MAXN],s[MAXN];
double sum,c[MAXN];
template<class T>inline void read(T&x){
  char ch=getchar();int f=x=0;
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f)x=-x;
}
inline void prework(){//R为最大值下标,L为最小值下标
	ansr=-INF,R=n+1;ansl=0,L=0;
	DFor(i,n,0) if(ansr<s[i])ansr=s[i],R=i;
	For(i,1,n) if(ansl>s[i])ansl=s[i],L=i;
}
inline bool chk(double mid){
	double mx=-INF,mn=0;int l=0,r=n+1;
	For(i,1,n)c[i]=1.0*s[i]-(L<R?1:-1)*mid*i;//L<R则减,否则加
	DFor(i,n,0) if(mx<c[i])mx=c[i],r=i;
	For(i,1,n) if(mn>c[i])mn=c[i],l=i;
	sum=mx-mn;
	return (l<r)==(L<R);//判断大小关系是否改变
}
int main(){
	read(n);
	For(i,1,n)read(a[i]),s[i]=s[i-1]+a[i];
	prework();
	double l=0,r=20005;
	while(r-l>=eps){
		double mid=(l+r)/2;
		if(chk(mid))l=mid;
		else r=mid;
	}
	chk((l+r)/2);
	printf("%.15lf\n",sum);
 return 0;
}
```

---

## 作者：Prean (赞：5)

看到题面的第一眼是这玩意儿关于 x 是单谷的，证明稍微想了一下：

设 $f[k]$ 和 $g[k]$ 是原序列中长度为 $k$ 的子区间的最大子区间和最小子区间，给定 $x$ 时答案就相当于：
$$\max_{i=1}^{n}\max(|f[k]-k\times x|,|g[k]-k\times x|)$$
这相当于若干个一次函数取绝对值后的最值。我们知道两个单谷函数取 $\max$ 后仍然是单谷函数，斜率为负的一次函数取绝对值后也是单谷函数。

所以原问题的函数是若干个单谷函数取 $\max$，也是单谷函数。

然后就可以愉快地三分了。自己使用的是微分，以及需要注意精度。
```cpp
#include<cstdio>
typedef long double db;
const int M=2e5+5;
const db eps=1e-12;
int n,a[M];db b[M];
inline db fabs(const db&a){
	return a>0?a:-a;
}
inline db max(const db&a,const db&b){
	return a>b?a:b;
}
inline db min(const db&a,const db&b){
	return a>b?b:a;
}
inline db f(const db&x){
	db f(0),g(0),ans(0);
	for(int i=1;i<=n;++i)f=max(f,0)+a[i]-x,g=min(g,0)+a[i]-x,ans=max(ans,max(fabs(f),fabs(g)));
	return ans;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	db L(-10000),R(10000),mid;
	while(L+eps<R){
		mid=(L+R)/2;if(f(mid)<f(mid+eps))R=mid;else L=mid;
	}
	printf("%.10Lf",f(L));
}
```

---

## 作者：EnofTaiPeople (赞：4)

这道题给我很大的启示：
1. 子段和可以联想到前缀和；
2. 对于单变量函数最值若相邻数函数值差别不大，可以使用三分.

可参考本题与廊桥分配。此题就满足以上两点，考虑三分 x，每次从前往后计算，只取当前前缀和与之前极值的差，因为只有他们才可能是最大的。

本题略微卡精度，可以限定三分 200 次，可以 AC：
```cpp
#include<bits/stdc++.h>
#define IV inline void
#define II inline int
#define db double
#define ID inline db
using namespace std;
const int N=2e5+5;
char buf[N+5],*p1,*p2,c;
#define gc getchar()//(p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2))?EOF:*p1++
template<typename _Tp>
IV read(_Tp &x){
	bool f=x=0;for(c=gc;c<'0'||c>'9';c=gc)if(c=='-')f=1;
	for(x=0;c>='0'&&c<='9';x=x*10+c-'0',c=gc);if(f)x=-x;
}
int n,a[N];
db l=0,r,lmid,rmid;
ID fuc(db x){
	int i;db res,mx,mn,now;
	for(i=1,res=now=mx=mn=0;i<=n;++i){
		now+=a[i],now-=x;res=max({res,abs(now-mx),abs(now-mn)});
		if(now>mx)mx=now;if(now<mn)mn=now;
	}return res;
}
int main(){
	int i;for(i=1,read(n);i<=n;++i)read(a[i]);
	r=4e9,l=-r;
	for(i=1;i<=200;++i){
		lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		if(fuc(lmid)<fuc(rmid))r=rmid;
		else l=lmid;
	}
	printf("%.10lf\n",fuc((l+r)/2));
	return 0;
}
```

---

## 作者：FLASH_CM (赞：4)

**这道题**，其实三分的解法比二分要好理解一些吧。。。  
~~——蒟蒻Dr.Ming~~

首先想到的其实是二分，考虑到这一道题目如果没有绝对值的话，明显是**单调递增**的；但将数全部翻转后，便变成了**单调递减**的。  
于是，可以看出本题其实是单峰函数求最值，采用三分x做即可。
### 注意：
多次尝试后，发现在避免超时的同时，还要注意精度，大概循环200次左右为宜。
### 代码：
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define ri register int
#define ll long long
#define ld long double
#define gc() getchar()
const int MaxN=200010;
const double inf=1e30;
#define For(i,j,k) for(ri i=j;i<=k;i=-~i)
#define DFor(i,j,k) for(ri i=j;i>=k;i=~-i)
template <class T> inline void read(T&sum){
	int f;char ch=gc();
	for(f=1;!isdigit(ch);ch=gc())f=ch=='-'?-1:1;
	for(sum=0;isdigit(ch);sum=(sum<<1)+(sum<<3)+(ch^48),ch=gc());
	sum*=f;
}

int a[MaxN],N;

inline double check(double x){
    double sum=0,ret=0,Min=0,Max=0;
    For(i,1,N){
        sum+=a[i]-x;
        ret=max(ret,fabs(sum-Min));
        ret=max(ret,fabs(sum-Max));
        Min=min(Min,sum);
        Max=max(Max,sum);
    }
    return ret;
}

int main(){
    double l=0,r;
    int cnt=0;
    read(N);
    For(i,1,N){
        read(a[i]);
        l=min(l,-fabs(a[i]));
    }
	r=-l;
    while(cnt++<300){
        double ml=(r-l)/3+l,mr=(r-l)/3*2+l;
        if(check(ml)<check(mr))r=mr;
        else l=ml;
    }
    printf("%.6lf\n",check((l+r)*0.5));
    return 0;
}
```

---

## 作者：TernaryTree (赞：2)

### 模拟赛原题，十行诗

- 首先对于每个 $x$ 的结果我们记作 $f(x)$。那么显然 $f(x)$ 为单谷函数。

- 要求 $f(x)$ 最小，也就是函数的谷底，显然是三分。

- 如何快速求 $f(x)$，如果前缀和暴力算，加上三分复杂度，是 $\Theta(n^2\log V)$ 的，显然过不去。

- 显然是个 dp。

- 设 $p_i$ 表示以 $i$ 结尾的子段中最小和（负数），$q_i$ 表示最大。

- 初始时，有 $p_i=q_i=a_i-x$。

- 显然，$p_i=\min(p_i,p_{i-1}+a_i-x)$，$q_i$ 改成 $\max$。

- 则 $f(x)=\max(|p_i|,|q_i|)$。

- 复杂度 $\Theta(n\log V)$，容易通过。

- 有些卡精度。记得开 `long double`。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double

using namespace std;

const int maxn = 2e5 + 1;
const double eps = 1e-12;

int n;
double a[maxn];
double f[maxn];
double g[maxn];

double solve(double x) {
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		f[i] = g[i] = a[i] - x;
	}
	for (int i = 2; i <= n; i++) {
		f[i] = min(f[i], f[i - 1] + a[i] - x);
		g[i] = max(g[i], g[i - 1] + a[i] - x);
	}
	for (int i = 1; i <= n; i++) {
		ans = max(ans, max(fabs(f[i]), fabs(g[i])));
	}
	return ans;
}

signed main() {
//	freopen("weakness.in", "r", stdin);
//	freopen("weakness.out", "w", stdout); 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	double l = -1e6, r = 1e6, mid, lv, rv;
	while (r - l >= eps) {
		mid = (l + r) / 2;
		lv = solve(mid - eps * 5);
		rv = solve(mid + eps * 5);
		if (lv < rv) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << fixed << setprecision(6) << solve(l) << endl;
	
	return 0;
}
```

---

## 作者：HHZZLL (赞：0)

### 分析

1）由于有一个一定的最小值，是单谷函数，可以使用**三分**求解。

2）将 $a_i-x$ 的值存入 $b_i$ 。求糟糕程度时，就是 $b$ 序列里的**连续子串和**的绝对值。不美好程度就是 $b$ 序列中的**最大、最小**连续字串和的绝对值的最大值。

3）那么，设 $f_i$ 表示以 $b_i$ 结尾的连续字串和的最大值，再设 $g_i$ 表示表示以 $b_i$ 结尾的连续字串和的最小值。所以 $f_i=\max(f_{i-1},f_i),g_i=\min(g_{i-1},f_i)$ 。最后注意取绝对值。

4）注意一下精度。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const double eps=1e-11;
int n,a[N];
double f[N],g[N];
double F(double x){
	for(int i=1;i<=n;i++) f[i]=g[i]=(double)a[i]-x;
	for(int i=2;i<=n;i++){
		f[i]=max(f[i],f[i-1]+f[i]);
		g[i]=min(g[i],g[i-1]+g[i]);
	}//求出f[i],g[i]
	double ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,max(fabs(f[i]),fabs(g[i])));//取绝对值较大值
	return ans;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	double l=-1e18,r=1e18;//x为实数范围，注意区间范围
	while(r-l>eps){//寻找x
		double mid=(r-l)/3.0;
		double lmid=l+mid,rmid=r-mid;
		if(F(lmid)<F(rmid)) r=rmid;
		else l=lmid;
	}
	printf("%.6lf",F((l+r)/2));
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

首先证明一下单调性，证明有唯一极点且两边均单调。

令极点为 $x=X$，取一个 $X<Y<Z$，证明 $Y$ 对应的值小于 $Z$ 对应的值。

容易发现 $X$ 中序列的 $|\max|=|\min|$，那么当 $x$ 增大时其中 $\max$ 会相应增大，其中的 $\min$ 也会增大，则占较大趋势的为其中的 $\max$。由于其 $\max$ 单调递增，所以自然是单调的。

反之亦然。

然后三分就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int a[1000005];
int n;
double count(double mid){
	double b[1000005];
	for(int i=1;i<=n;i++) b[i]=a[i]*1.0+mid;
	double maxv=0,minv=0,pre=0;
	double bst=0;
	for(int i=1;i<=n;i++){
		pre+=b[i];
		maxv=max(maxv,pre);
		minv=min(minv,pre);
		bst=max(fabs(maxv-pre),bst);
		bst=max(fabs(minv-pre),bst);
	}
	return bst;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	double l=-100000,r=100000;
	while(r-l>0.000000000001){
		double mid=(l+r)/2;
		if(count(mid)<=count(mid+0.000000000001)) r=mid;
		else l=mid;
	}
	cout<<fixed<<setprecision(10)<<count(l);
	return 0;
}
```

注意精度，要到 $\dfrac{1}{10^6\times10^6}$。

---

## 作者：Sqrtyz (赞：0)

### 题意

给定一个长度为 $n$ 的数组 $a_i$，求一个实数 $x$，使得序列 $a_1-x,a_2-x,...,a_n-x$ 的不美好程度最小。不美好程度定义为一个序列的所有连续子序列的糟糕程度的最大值。糟糕程度定义为一个序列的所有位置的和的绝对值。

+ $n \leq 2 \times 10^5$

### 解题

第一眼看到可能会想到二分答案 $x$，但仔细一看 $x$ 并不单调。再观察一会儿， $x$ 貌似是个凸函数，这给三分提供了可能。

但我们必须要证明这是个凸函数，怎么证明呢？

我们知道，凸函数有一个奇妙♂的性质，即若 $f(x)$ 和 $g(x)$ 是凸函数，$h(x)=\max(f(x),g(x))$ 也是凸函数。

显然我们可以看到，对于这个序列的子序列，他们的「糟糕程度」肯定是一个凸函数。由于整个序列的「不美好程度」是「糟糕程度」的最大值，所以「不美好程度」也是凸函数。

因此三分 $x$，最后用喜闻乐见的解决「最大子段和」的方法求出当时的「不美好程度」，这道题就解决了。

P.S. 解决「最大子段和」的方法可以见 [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)，注意这道题由于有个绝对值，所以最大子段和要跑两遍。

### 程序

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>

#define Maxn 200010

using namespace std;

const double eps = 1e-8;

int read() {
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while('0' <= c && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

int N;
double a[Maxn], b[Maxn], f[Maxn];

double calc(double x) {
	memset(f, 0, sizeof(f));
	for(int i = 1; i <= N; ++i) b[i] = a[i] + x;
	double ans = 0, res = 0;
	for(int i = 1; i <= N; ++i) {
		if(res + b[i] > 0) res += b[i];
		else res = 0;
		ans = max(ans, res);
	}
	
	for(int i = 1; i <= N; ++i) b[i] = -b[i];
	res = 0;
	for(int i = 1; i <= N; ++i) {
		if(res + b[i] > 0) res += b[i];
		else res = 0;
		ans = max(ans, res);
	}
	return ans;
}

int main() {
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	double l = -20000, r = 20000;
	for(int cnt = 1; cnt <= 200; ++cnt) {
		double mid = (l + r) / 2;
		double q1 = calc(mid - eps), q2 = calc(mid + eps);
		if(q1 > q2) l = mid;
		else r = mid;
	}
	printf("%.7lf", calc(l));
	return 0;
}
```

---

## 作者：swiftc (赞：0)

#### 我感觉这道题还是三分做比较好吧
首先看到题面，设check(x)为a1-x,a2-x,...,an-x的不美好程度

显然它不是单调的，所以我们用三分来解

三分大家都会吧，那么我们来考虑check(x)怎么求

### 1.暴力求法
直接求出前缀和，然后暴力模拟

代码：
```cpp
//fabs为double的abs
double check(double s){
	double ans=-1.0;
	for(int i=1;i<=n;i++){
		a[i]-=s;
	}
	double tmp[200001];
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;i++){
		tmp[i]=a[i]+tmp[i-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			ans=max(ans,fabs(tmp[i]-tmp[j-1]));
		}
	}
	for(int i=1;i<=n;i++){
		a[i]+=s;
	}
	return ans;
}
```
可以过7个点
![](https://cdn.luogu.com.cn/upload/pic/61446.png)
### 2.正解
让我们先求出一个前缀和数组tmp

让我们想一想，可不可以不用对于每一个i都从1～i-1枚举j呢？

因为我们要求最大的fabs(tmp[i]-tmp[j])，所以我们只需要tmp[1]~tmp[i-1]中的最大值和最小值

对于剩下的tmp[j]不可能使答案变的更大

代码：

```cpp
inline double check(double x){
    double sum=0,ret=0,Min=0,Max=0;
    for(int i=1;i<=n;i++)
    {
        sum+=a[i]-x;
        //因为我们只需要当前的前缀和，所以我们只保留当前的前缀和即可，不需要求tmp数组
        ret=max(ret,fabs(sum-Min));
        ret=max(ret,fabs(sum-Max));
        //更新数列的不美好程度
        Min=min(Min,sum);
        Max=max(Max,sum);
        //更新前缀和的最大值和最小值
    }
    return ret;
}
```

完整代码：

注意：一定要注意精度

~~while(r-l>=xxx)这种我没调出来~~
```cpp
#ifdef DEBUG
#include"stdc++.h"
#else
#include<bits/stdc++.h>
#endif
using namespace std;
int n;
double a[200001];
inline double check(double x){
    double sum=0,ret=0,Min=0,Max=0;
    for(int i=1;i<=n;i++)
    {
        sum+=a[i]-x;
        ret=max(ret,fabs(sum-Min));
        ret=max(ret,fabs(sum-Max));
        Min=min(Min,sum);
        Max=max(Max,sum);
    }
    return ret;
}
int main(){
    scanf("%d",&n);
    double l=0,r;
    for(int i=1;i<=n;i++)scanf("%lf",&a[i]);
    for(int i=1;i<=n;i++){
        l=min(l,-fabs(a[i]));
    }
    r=-l;
    int cnt=0;
    while(cnt++<400){
        double m1=l+(r-l)/3,m2=r-(r-l)/3;
        double a1=check(m1),a2=check(m2);
        if(a1<a2){
            r=m2;
        }
        else{
            l=m1;
        }
    }
    printf("%.6lf\n",check((l+r)/2.0));
    return 0;
}

```





---

## 作者：迟暮天复明 (赞：0)

[题面](https://codeforces.com/contest/578/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16343765.html)

Description:

定义一个长度为 $n$ 的数列 $a_i$ 的“不美好程度”为 
$$\max_{1\leq l<r\leq n} \{|\sum_{i=l}^r a_i|\}$$

求一个实数 $x$，使得数列 $b_i=a_i-x$ 的“不美好程度”最小。输出最小值。

$n\leq2\times10^5$。

-----
我们先转化一下式子。

因为 $|a|=\max\{a,-a\}$，所以 
$$\max_{1\leq l<r\leq n} \{|\sum_{i=l}^r a_i|\}=\max\{\max_{1\leq l<r\leq n} \{\sum_{i=l}^r a_i\},\max_{1\leq l<r\leq n} \{-\sum_{i=l}^r a_i\}\}$$
这样我们就把求一个数列的“不美好程度”转化成求两次最大子段和。

因为我不会证明“不美好程度”与 $x$ 的函数关系，所以拒绝使用三分法。但我们知道 $x$ 的范围局限在 $[\min\{a_i\},\max\{a_i\}]$ 之间，这个区域很小，于是考虑使用随机化算法模拟退火。

注意参数的掌握。

[代码](https://paste.ubuntu.com/p/JczxPR4mWM/)

---

