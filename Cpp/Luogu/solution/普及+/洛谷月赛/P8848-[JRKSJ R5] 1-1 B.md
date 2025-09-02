# [JRKSJ R5] 1-1 B

## 题目背景

本题是 1-1 的较难版本，较易版本为 [1-1 A](https://www.luogu.com.cn/problem/P8847)。

## 题目描述

给出一个序列 $a$，$\forall i\in [1,n],a_i\in \{1,-1\}$。

询问有多少个将 $a$ 重排后的序列使得该序列的最大子段和最小化。

称两个序列不同，当且仅当这两个序列有任意一个位置上的数不同。

## 说明/提示

最大子段和的定义：序列中一段区间的和的最大值。即 $\max_{1\le l\le r\le n} \sum_{i=l}^r a_i$。

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $20$ |
| $2$ | $100$ | $20$ |
| $3$ | $500$ | $20$ |
| $4$ | $10^4$ | $40$ |

对于 $100\%$ 的数据，$1\le n\le 10^4$，$a_i\in \{1,-1\}$。

## 样例 #1

### 输入

```
4
1 -1 1 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 1 1 -1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10
1 1 1 1 1 1 1 -1 -1 -1```

### 输出

```
40```

# 题解

## 作者：critnos (赞：15)

设序列中有 $a$ 个 $1$，$b$ 个 $-1$。

分类讨论：

1. $a\le b$

这种情况答案的下界为 $1$ 并且容易构造。令不存在两个连续的 $1$ 即可。

一种特殊情况是 $a=0$ 此时最大子段和为 $-1$。不过也满足不存在两个连续的 $1$。

答案是 $\dbinom {b+1}{a}$

2. $a>b$

显然，答案的下界为 $a-b$。并且这个下界容易构造。构造 $1,-1$ 交替的序列，最后多余的 $1$ 放到末尾即可。

实际上，这个序列达到下界的充要条件是每个前缀的和均在 $[0,a-b]$。

充分性：

不存在两个前缀和做差 $>a-b$，所以不存在任何一个区间的和 $>a-b$，满足条件。

必要性：

若有前缀的和 $<0$，那么砍掉这个前缀，剩余的序列和就超过了 $a-b$；

若有前缀的和 $>a-b$，那么这个前缀就不满足条件。

证毕。

这个也可以 dp。

朴素做法时间复杂度 $O(n^2)$，存在线性算法。

---

## 作者：__K2FeO4 (赞：13)

我们分类讨论。

设 $p$ 为 $1$ 的个数，$q$ 为 $-1$ 的个数。

## Part 1: $p\le q$

容易发现最小的最大子段和为 $1$，这也就意味着两个 $1$ 之间一定有至少一个 $-1$（不然最大子段和大于 $1$ 了）。

这样，就是在 $q$ 个 $-1$ 之间（包括两端）插入 $p$ 个“隔板”$1$，方案总数为 $C_{q+1}^{p}$。

## Part 2: $p>q$

在这种情况下，最大子段和为 $p-q$。我们画图分析。

$1$ 表示向右上方走 $1$ 个对角线单位，$-1$ 表示向右下方走 $1$ 个对角线单位。对于任意时刻保持 $0\le y\le p-q$ 的路径方案数。

![](https://cdn.luogu.com.cn/upload/image_hosting/42pxp08v.png)

就是如图从左下角到右上角的方案数。

设 $f{i,j}$ 为使用 $i$ 个 $-1$，前缀和为 $j$ 的方案数（使用 $i$ 个 $-1$ 就是如图从左上开始的层数，前缀和为 $j$ 就是当前高度），得到状态转移方程：

$f_{i,j}=f_{i-1,j+1}+f_{i,j-1}$

初始化 $f_{0,0}=1$。

答案为 $f_{q,p-q}$。

## code:

注意空间复杂度，可以选择用 vector，也可以用滚动数组（这个更好）。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10086;
const int mod=998244353;
typedef long long ll;
int n,cp=0,cq=0;
vector<int> a[N];
signed main(){
	int x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&x),x==1?cp++:cq++;
	int m=cp-cq;
	//a[0].push_back(1);
	if(m>0){
		for(int i=0;i<=cq;i++)
		for(int j=0;j<=m;j++){
			int s=0;
			if(i&&j!=m)s+=a[i-1][j+1];
			if(j)s+=a[i][j-1];
			a[i].push_back(i||j?s%mod:1);
			//printf("%d ",i||j?s%mod:1);
		}
		printf("%d",a[cq][m]);
	}
	else{
		for(int i=0;i<=1-m;i++)
		for(int j=0;j<=cp;j++){
			int s=0;
			if(i)s+=a[i-1][j];
			if(j)s+=a[i][j-1];
			a[i].push_back(i||j?s%mod:1);
		}
		printf("%d",a[1-m][cp]);
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：7)

首先不考虑只有 $1$ 或者只有 $-1$ 的平凡情况。

令 $z$ 为 $1$ 的个数，$f$ 为 $-1$ 的个数，若有 $f\geq z$，那么可以构造使得最大子段和为 $1$（因为有 $1$ 出现所以最大子段和至少为 $1$），只需要让 $1$ 和 $1$ 不能相邻即可。那么即为在 $-1$ 形成的 $(f+1)$ 个空隙里面选择 $z$ 个放入，答案为 $\binom{f+1}{z}$．

若 $f<z$，由于全局和 $z-f$ 一定是一个子段和，所以最小的最大子段和 $\geq z-f$，现在考虑什么样的方案能够使得这个下界可以取到。

令 $s[l,r]$ 为 $[l,r]$ 这个子段的和。考虑若存在一个子段 $[l,r]$ 使得 $s[l,r]>z-f$，那么 $s[1,l-1]$ 和 $s[r+1,n]$ 必然有一个 $<0$，否则全局子段和会 $>z-f$；如果存在一个 $p$ 满足 $s[1,p]<0$ 那么 $s[p+1,n]>z-f$（因为两者之和为 $z-f$）；如果存在一个 $p$ 满足 $s[p+1,n]<0$ 同理。

这样即证存在一个子段 $s[l,r]$ 当且仅当存在一个前缀或存在一个后缀总和 $<0$（第一部分是必要，后两部分是充分）。

那么现在问题就是对“不存在一个前缀 / 后缀总和 $<0$” 的情况。

对于 $+1,-1$，与前缀和或后缀和有关的，不难和括号序列一样想到格路计数。那么问题可以抽象成从 $(0,0)$ 出发，如果当前在 $(x,y)$，下一位是 $1$ 则走到 $(x+1,y+1)$，否则走到 $(x+1,y-1)$，最终要走到 $(n,z-f)$．

要求每个前缀 $\geq 0$ 即为不能走到 $y=-1$ 这条线，要求每个后缀 $\geq 0$ 即为不能走到 $y=z-f+1$ 这条线。

由于 $n\leq 10^4$，可以 $\mathcal{O}(n^2)$ dp 算出。

采用[一些“科技”](https://www.luogu.com.cn/problem/P3266)可以做到更快的复杂度（反射容斥）。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n'
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
mt19937 rnd(time(NULL)^(ull)(new char));
inline int rd(int a,int b){
	return a+rnd()%(b-a+1);
}
#define Win do{puts("Yes");return ;}while(0)
#define Lose do{puts("No");return ;}while(0)
#define Alice do{puts("Alice");return ;}while(0)
#define Bob do{puts("Bob");return ;}while(0)
#define Fuyi do{puts("-1");return ;}while(0)
#define Line cerr << "----------\n"

const int N=1000010;

int n;
int fac[2*N],inv[2*N];
int C(int x,int y){
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int f,z;
int go(int a,int b,int c,int d){
    return C(c-a,(c-a+d-b)/2);
}
int go0(int a,int b,int k1,int k2);
int go1(int a,int b,int k1,int k2);
int go0(int a,int b,int k1,int k2){
    if(a<-b||a<b)return 0;
    return del(del(go(0,0,a,b),go(0,0,a,2*k2-b)),go1(a,b,k1,k2));
}
int go1(int a,int b,int k1,int k2){
    if(a<-b||a<b)return 0;
    if(a<2*k1-b||a<b-2*k1)return 0;
    return add(go0(a,2*k1-b,2*k1-k2,k2),go1(a,b,2*k1-k2,k2));
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n);
	fac[0]=1;for(int i=1;i<=3*n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[3*n]=qpow(fac[3*n],mod-2);
	for(int i=3*n-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1,x;i<=n;i++){
		read(x);
		if(x==1)++z;
		else ++f;
	}
	if(f>=z)cout << C(f+1,z) << '\n';
	else cout << go0(n,z-f,-1,z-f+1) << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Epoch_L (赞：3)

## Solution
延续上一题的思路，发现只与 $1$ 和 $-1$ 的数量有关，设 $1$ 的数量为 $a$，$-1$ 的数量为 $b$。上一题的构造方案为 $1$ 和 $-1$ 交替放，再把剩余的放在末尾。

当 $a\le b$ 时，最后剩余的是 $-1$，显然最大子段和为 $1$。所以只要保证没有相邻的 $1$ 即可，看作在 $-1$ 里面插 $1$，方案数根据插板法可得：

$$
\binom{b+1}{a}
$$

当 $a>b$ 时，最后剩余的 $1$ 的数量就是最大子段和，即 $a-b$。

考虑如何求出方案数，有一个非常重要的性质：任何一个前缀的值在区间 $[0,a-b]$。

证明可以采用反证法，假设存在一个以 $i$ 结尾的前缀满足小于 $0$ 或大于 $a-b$，那么：

+ 如果小于 $0$，因为整个序列的和为 $a-b$，那么以 $i+1$ 为开始的后缀就会大于 $a-b$，不满足最大子段和为 $a-b$。

+ 如果大于 $a-b$，显然这就不满足条件。

故假设不成立，原命题成立。

所以设计 DP 方程 $f(i,j)$ 表示填到第 $i$ 个数和为 $j$ 的方案数，根据上文的性质有 $0\le j \le a-b$，不然没法 DP。有转移方程：
$$
f(i,j)=f(i-1,j+1)+f(i-1,j-1)
$$
注意特判 $j=0$ 即可，答案为 $f(n,a-b)$，要把第一维滚掉。

听说有线性做法。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=1e4+7,mod=998244353;
int f[2][N];
int Pow(int x,int y){
  int ans=1;
  while(y){
    if(y&1)ans=ans*x%mod;
    x=x*x%mod;
    y>>=1;
  }
  return ans;
}
int C(int n,int m){
  if(n<m)return 0;
  if(m==0)return 1;
  int ans=1;
  for(int i=1;i<=m;i++)
    ans=ans*(n-i+1)%mod,ans=ans*Pow(i,mod-2)%mod;
  return ans;
}
main(){
  int n;read(n);
  int a=0,b=0;
  for(int i=1,x;i<=n;i++){
    read(x);
    if(x==1)a++;
    else b++;
  }
  if(a<=b)printf("%lld\n",C(b+1,a));
  else{
    f[0][0]=1;
    for(int i=1;i<=n;i++)
      for(int j=0;j<=a-b;j++){
        int op=i&1;
        if(j==0)f[op][j]=f[op^1][j+1]%mod;
        else f[op][j]=(f[op^1][j-1]+f[op^1][j+1])%mod;
      }
    printf("%lld\n",f[n&1][a-b]);
  }
  return 0;
}
```

---

## 作者：whhsteven (赞：3)

~~[钛金手机](https://www.bilibili.com/video/BV14W411T7WJ?p=4)题。~~

&nbsp;

记 $c_0$ 为序列中 $1$ 的个数，$c_1$ 为序列中 $-1$ 的个数，最大子段和为 $s$，最小化的最大子段和为 $m$。

$c_0 = 0$ 的情况是平凡的，只讨论 $c_0 > 0$ 的情况。

首先，$m = \max(1, c_0 - c_1)$。这是因为

- $c_0 \le c_1$ 时：

  - 不管怎么排都可以选一个单独的 $1$ 作为选出的子段，故 $s \ge 1$；
  
  - 又因为只需要按一个 $1$ 一个 $-1$ 的方式排列这些数直到 $1$ 用完即可使得最大子段和为 $1$，所以 $m \le 1$。
  
  - 从而 $m = 1$。

- $c_0 > c_1$ 时：

  - 不管怎么排都可以选整个序列作为选出的子段，故 $s \ge c_0 - c_1$；
  
  - 又因为只需要按一个 $1$ 一个 $-1$ 的方式排列这些数直到 $-1$ 用完并将剩余的 $1$ 放完即可使得最大子段和为 $c_0 - c_1$，所以 $m \le c_0 - c_1$。
  
  - 从而 $m = c_0 - c_1$。

现在考虑方案数计数。

- $c_0 \le c_1$ 时：

  - 要 $s = m = 1$，只需任意两个 $1$ 均不相邻。
  
  - 问题即在 $-1$ 构成的 $c_1 + 1$ 个位置中选出 $c_0$ 个位置放下 $1$，答案为 $\binom{c_1 + 1}{c_0}$。

- $c_0 > c_1$ 时：

  - 要 $s = m = c_0 - c_1$，只需任意一个前缀的和均在 $[0, c_0 - c_1]$ 范围内。
  
  - 这是因为：记 $p_i$ 表示排出序列的到 $i$ 位置的前缀和。考察 $s > m = c_0 - c_1$ 的情况，排出的序列存在一段子段 $[l, r]$ 满足 $p_r - p_{l-1} > c_0 - c_1$。此时若 $p_r \le c_0 - c_1$ 则 $p_{l - 1} < 0$，即存在至少一个位置的前缀和不在 $[0, c_0 - c_1]$ 范围内。
  
  - $O(n^2)$ DP 即可。

---

## 作者：AKPC (赞：2)

[1-1A题解](https://a-passingcreeper.blog.luogu.org/solution-p8847)
### 题意
桌上有 $n$ 张标有数字的牌，输出有多少种排列使得标的数字的最大子段和最小。
### 思路
还是只有 $1$ 和 $-1$ 的最大子段和最小问题，但是问的不同。

那么根据惯例，本题需要分类讨论。还是设 $1,-1$ 分别出现 $x,y$ 次

当 $x \leq y$，容易发现最小的最大子段和为 $1$，这也就意味着两个 $1$ 之间**至少有一个** $-1$（不然最大子段和就大于 $1$ 了，达不到最优解的效果，不符合题意）。也就是数学问题中的插板问题，在这些 $-1$ 中插板子 $1$，方案总数为 $C_{(q+1)}^{p}$。

当 $x > y$，首先我们注意到 “最大子段和最小”这个条件等价于 “所有前缀和 $\ge 0$” 且 “所有后缀和 $\le 0$”。使用动态规划做。定义 $f_{0,0}=0,f_{i,j}=f_{i-1,j+1}+f{i,j-1}$。答案为 $f_{y,x-y}$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define int long long
int n,x,cnt1=0,cnt2=0,s;
vector <int> a[10001];
void case1(){   //m>0
	for (int i=0;i<=cnt2;i++)
	    for (int j=0;j<=m;j++){
	        s=0;
		    if (i&&j!=m) s+=a[i-1][j+1];
		    if (j) s+=a[i][j-1];
		    i||j?a[i].push_back(s%mod):a[i].push_back(1);
	    }
	cout<<a[cnt2][m];
}
void case2(){   //m<=0
	for (int i=0;i<=1-m;i++)
		 for (int j=0;j<=cnt1;j++){
         s=0;
         if (i) s+=a[i-1][j];
         if (j) s+=a[i][j-1];
         i||j?a[i].push_back(s%mod):a[i].push_back(1);
		 }
	cout<<a[1-m][cnt1];
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
	    cin>>x;
	    x==1?cnt1++:cnt2++;
	}
	int m=cnt1-cnt2;
	if (m>0) case1();
	else case2();
	return 0;
}

```

Upd：符号打错，已修正，求过

---

## 作者：ziyanlin2013 (赞：1)

**题目传送门：https://www.luogu.com.cn/problem/P8848**

# 简要题意
- 给出一个序列 $a$，数字要么是 $1$，要么是 $-1$。
- 询问有多少个将 $a$ 重排后的序列使得该序列的最大子段和最小化。
- 称两个序列不同，当且仅当这两个序列有任意一个位置上的数不同。

# 解体思路
显然，答案仅仅和数字 $1$ 和 $-1$ 的个数相关，**考虑分类讨论**。为了方便表述，记 $1$ 的个数为 $num1$，$-1$ 的个数为 $num0$。

1. $num1 \le num0$

最小化后的最大子段和为 $1$，即不出现相邻的两个 $1$，方案数量就是在 $num0 + 1$ 个空中插入 $num1$ 个板。答案即为 $C(num0 + 1,num1)$。

2. $num1 > num0$

考虑 DP，记 $f[i][j]$ 表示用 $i$ 个数，最大子段和为 $j$ 的方案数，考虑是用 $1$ 还是 $-1$，注意和为 $0$ 时仅能使用 $-1$，因为不存在最大子段和为 $-1$ 的，递推式显然为：

 $f[0][0] \gets 1$
 
 $f[i][0] \gets f[i-1][1] $ 
 
 $f[i][j] \gets f[i-1][j+1] + f[i-1][j-1]$

答案即为 $f[n][num1 - num0]$，记得用滚动数组优化。

# 代码（附注释）

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e4+5;//n*n
ll n,a[N],num0,num1,f[N],last[N];
ll mod=998244353;
ll qp(ll a,ll b){//快速幂 
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int c(int n,int m){//组合排列 
	if(!m) return 1;
	if(n<m) return 0;
	ll ans=1;
	for (int i=1;i<=m;i++){
		ans=ans*(n-i+1)%mod;
		ans=ans*qp(i,mod-2)%mod;
	}
	return ans;
}
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1) num1++;
		else num0++;
	} 
	if(num1<=num0){//答案显然为 1 
		//c(num0+1,num1)
		cout<<c(num0+1,num1);
	}
	else{//答案为 num1-num0 
		last[0]=1,f[0]=1;
		for (int i=1;i<=n;i++){
			f[0]=last[1];
			for (int j=1;j<=num1-num0;j++){
				f[j]=(last[j+1]+last[j-1])%mod;
			}
			for (int j=0;j<=num1-num0;j++){
				last[j]=f[j];
			}
		}
		cout<<f[num1-num0];
	}
	return 0;
} 
```

---

## 作者：fjy666 (赞：1)

设总共有 $c1$ 个 $1$，$c2$ 个 $-1$。  
- 当 $c1 - c2 > 1$ 时（最大子段和 $\ge 2$）

首先我们注意到 “最大子段和最小”这个条件等价于 “所有前缀和 $\ge 0$” 且 “所有后缀和 $\le 0$”。  
考虑 dp。设 $dp_{i,j}$ 为用了 $i$ 个 $1$，$j$ 个 $-1$ 的方案数
1. 所有前缀和 $\ge 0$ 相当于必须满足 $i\ge j$
2. 所有后缀和 $\ge 0$ 相当于必须满足 $c1-i\ge c2-j$  

按照这两个标准进行 dp 即可。转移方程就是普通的标数法。

- 当 $c1 - c2 \le 1$ 时（最大字段和 $= 1$）

此时先用 $-1$ 把所有 $1$ 隔开。剩下的 $c2 - (c1 - 1)$ 个 $-1$ 可以自由摆放。挡板法可知答案为 
$$\binom{c2-(c1-1)+c1}{c1}$$


Code

```cpp
//Code by fjy666(https://www.luogu.com.cn/user/366338)
#include <bits/stdc++.h>
using namespace std;
#define _rep(i_,a_,b_) for(int i_ = (a_); i_ <= (b_); ++i_)
#define mid ((L+R) >> 1)
// #define get(x) (((x) - 1) / kb + 1)
#define multiCase() int testCnt = in(); _rep(curCase,1,testCnt)
#define multi(init) int testCnt = (init); _rep(curCase,1,testCnt)
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
typedef long long ll;

int in(void) { int x; scanf("%d", &x); return x; }
ll inl(void) { ll x; scanf("%lld", &x); return x; }
template<typename T> void chkmax(T &a, const T &b) { a = max(a, b); } 
template<typename T> void chkmin(T &a, const T &b) { a = min(a, b); } 
const int p = 998244353, kN = 11454;
int n = in(), c1 = 0, c2 = 0;
int fpm(int a, int b) {
	int res = 1;
	for(;b;b >>= 1, a = 1ll * a * a % p) if(b & 1) res = 1ll * res * a % p;
	return res;
}
int inv(int a) { return fpm(a, p - 2); }
int C(int n, int m) { int res = 1;
	for(int i = n - m + 1; i <= n; ++i) res = 1ll * res * i % p;
	for(int i = 1; i <= m; ++i) res = 1ll * res * inv(i) % p;
	return res;
}

int grid[kN][kN];
int main() { 
	_rep(i,1,n) if(in() == 1) ++c1; else ++c2;
	if(c1 > c2) {
		grid[0][0] = 1;
		_rep(i,0,c1) _rep(j,0,c2) if(i >= j) if(c1 - i >= c2 - j) {
			debug("(%d %d) = %d\n", i, j, grid[i][j]);
			grid[i][j + 1] = (grid[i][j + 1] + grid[i][j]) % p;
			grid[i + 1][j] = (grid[i + 1][j] + grid[i][j]) % p;
		}
		printf("%d\n", grid[c1][c2]);
	}
	else printf("%d\n", C((c2 - (c1 - 1)) + c1, c1));
	return 0;
}
```

---

## 作者：mycbxzd (赞：0)

### 题意理解

题目给出一个序列 $a$，其中每个元素 $a_i$ 取值为 1 或 -1。我们需要找到重排序后，最大子段和最小化的方案数量。

### 解题思路

1. **动态规划**：
   - 定义二维数组 $\text{dp}[i][j]$，表示前 $i$ 个数中，最后一个数为 $j$ 时的方案数量。
   - 根据题目要求，我们需要尽量使序列中的 1 和 -1 的数量接近，以最小化最大子段和。因此，我们将根据正负数的数量差异设计动态规划的状态转移方程。

2. **状态转移方程**：
   - 如果正数多于负数，我们可以从序列中选择一些正数和一些负数，使得它们的数量相等，然后对于剩余的正数，可以放在任意位置。因此，状态转移方程为：
     $$ \text{dp}[i][j] = \text{dp}[i-1][j+1] + \text{dp}[i][j-1] $$
     
   - 如果负数多于或等于正数，同样地，我们可以选择一些负数和一些正数，使得它们的数量相等，然后对于剩余的负数，可以放在任意位置。状态转移方程为：
     $$ \text{dp}[i][j] = \text{dp}[i-1][j] + \text{dp}[i][j-1] $$
     
     这两个状态转移方程主要是用来计算动态规划数组 `dp` 中的每个元素的值。这个动态规划数组 `dp` 的含义是，`dp[i][j]` 表示前 `i` 个数中，最后一个数为 `j` 时的方案数量。
     
     > 现在让我们解释一下状态转移方程中的两种情况：
     
     1. 如果正数多于负数，我们可以从序列中选择一些正数和一些负数，使得它们的数量相等，然后对于剩余的正数，可以放在任意位置。因此，状态转移方程为：
        
        ```
        dp[i][j] = dp[i-1][j+1] + dp[i][j-1]
        ```
        
        这里 `dp[i-1][j+1]` 表示在前 `i-1` 个数中，最后一个数为 `j+1` 时的方案数量，然后我们在这个基础上再增加一个正数，即从 `j+1` 变为 `j`，这样得到的方案数量就是 `dp[i][j]`。
        
        另外，`dp[i][j-1]` 表示在前 `i` 个数中，最后一个数为 `j-1` 时的方案数量，然后我们在这个基础上再增加一个负数，即从 `j-1` 变为 `j`，这样得到的方案数量也是 `dp[i][j]`。
     
     2. 如果负数多于或等于正数，我们同样可以选择一些负数和一些正数，使得它们的数量相等，然后对于剩余的负数，可以放在任意位置。状态转移方程为：
     
        ```
        dp[i][j] = dp[i-1][j] + dp[i][j-1]
        ```
     
        这里的意思和第一种情况类似，只不过是在负数的数量多于或等于正数的情况下进行的计算。
   
3. **初始化和边界情况处理**：
   - 我们需要初始化二维数组 $\text{dp}[i][j]$ 中的边界情况，以及处理 $\text{dp}[0][0]$ 的情况。

4. **根据正负数差异进行计算**：
   - 计算序列中正负数的数量差 $m$。
   - 如果 $m > 0$，则正数多于负数，按照第一种状态转移方程进行计算。
   - 如果 $m \leq 0$，则负数多于或等于正数，按照第二种状态转移方程进行计算。

5. **输出结果**：
   - 根据正负数的差异选择输出最终的结果。

### 思路总结

确保在最大子段和最小化的前提下，计算出重排序列的方案数量。


~~啊哈下面就是大家最期待的代码啦~~
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=10086;
const int MOD=998244353;
int n,cntup=0,cntdown=0;// n: 序列长度, cntup: 正数的数量, cntdown: 负数的数量
vector<vector<int>> a(N); // 使用 vector 来存储动态大小的数据
int main() {
    int x;
    cin >> n; 
    for (int i = 1; i <= n; i++) {
        cin >> x; // 读取序列中的每个元素
        if(x==1)cntup++;
        else cntdown++; 
        // 统计正数和负数的数量
    }
    int m = cntup - cntdown; // 计算正数和负数的数量差
    if (m > 0) {//正数多 
        for (int i = 0; i <= cntdown; i++)
            for (int j = 0; j <= m; j++) {
                int q = 0;
                if (i && j != m) q += a[i - 1][j + 1];
                if (j) q += a[i][j - 1];
                a[i].push_back(i || j ? q % MOD : 1); 
                // 动态规划更新
            }
        cout << a[cntdown][m]; // 输出结果
    } else {//负数多 
        for (int i = 0; i <= 1 - m; i++)
            for (int j = 0; j <= cntup; j++) {
                int q = 0;
                if (i)q+=a[i-1][j];
                if (j)q+=a[i][j-1];
                a[i].push_back(i || j ? q % MOD : 1); 
                // 动态规划更新
            }
        cout << a[abs(m)+1][cntup];
    }
}
```

------------
 _**求通过**_

---

## 作者：irris (赞：0)

## Preface

钛金手机。我是科技老哥。

## Solution

性质很难。

**建议先去做简单版以确定你的最大子段和答案是正确的**。首先原序列的顺序没有任何用处；我们可以设有 $X$ 个 $-1$ 和 $Y$ 个 $1$。

若 $Y \leq X$，那么最大子段和答案是 $1$（除非 $Y = 0$，但是这不破坏性质），只要保证没有两个相邻的 $1$ 即可。插板，答案 ${X + 1 \choose Y}$。

若 $Y \gt X$，我们知道最大子段和答案是 $Y - X$ 这一下界。

考虑如何验证这个答案取到，我们知道子段和等于前缀和相减，所以考虑写出前缀和序列。**手摸发现**，若 $\exists r$ 使得 $sum_r \gt y - x$，区间 $[1, r]$ 一定不符合条件（$sum_r - sum_0 \gt y - x$）；若 $\exists r$ 使得 $sum_r \lt 0$，区间 $[r + 1, n]$ 一定不满足条件（$sum_n - sum_r \gt y - x$，又由于 $sum_n = y - x \gt 0$，所以这个区间是合法的）。

然后发现 **这两个必要条件充分了**！如果我们的 $sum$ 都在 $[0, Y - X]$ 之间，那么相减也减不出 $\gt Y - X$ 的数，这是好的。

对前缀和曲线进行 dp，可以做到 $\mathcal O(n^2)$ 的复杂度。

我们观察转移过程，放到坐标系上，是 $(i, j)$ 转移到 $(i + 1, j \pm 1)$ 且不能碰到 $y = -1$ 和 $y = Y - X + 1$，求从 $(0, 0)$ 到 $(X + Y, Y - X)$ 的方案数。

旋转坐标系使选择 $+1$ 为 $(i + 1, j)$，选择 $-1$ 为 $(i, j - 1)$，即可赋予新的意义：$(i, j)$ 转移到 $(i + 1, j)$ 和 $(i, j + 1)$，且不能碰到 $y = x - 1$ 和 $y = x + Y - X + 1$，求从 $(0, 0)$ 到 $(X, Y)$ 的方案数。这是经典的 [反射容斥](https://www.luogu.com.cn/problem/P3266) 问题，可以线性解决。

时间复杂度 $\mathcal O(n)$。

---

## 作者：MuelsyseU (赞：0)

补充一点细节的证明。

显然答案只与 $1,-1$ 的出现次数有关。考虑若存在 $1$ 则最大子段和至少为 $1$。而如果 $1$ 的数量 $x$ 比 $-1$ 数量 $y$ 多，可以发现最大子段和至少为 $x-y$。

1. $x=0$

显然方案数为 $1$。

2. $x>0$ 且 $x\le y$

从区间和等于两前缀和之差角度，可以发现一定存在和为 $k\le0$ 的前缀，那么其后也就不得存在和不小于 $2+k$ 的前缀，相当于两者之间不能出现超过 $2$ 个 $1$。当且仅当任意两个 $1$ 不相邻，由插板法答案为 $C_{x+1}^y$。

3. $x>0$ 且 $x>y$

同理可知整个序列之和为 $x-y$，即任意区间和不得超过 $x-y$，从而任意前缀和 $s_i\in[0,x-y]$。考虑 DP，设 $f_{i,j}$ 为放置前 $i$ 个数前缀和为 $j$ 的方案数，直接转移：

$$f_{i,j}=\begin{cases}
f_{i-1,j+1} & j=0\\
f_{i-1,j-1} & j=m\\
f_{i-1,j-1}+f_{i-1,j+1} &j\in(0,m)
\end{cases}$$

考虑证明这样不会选取超过 $x$ 个 $1$ 或超过 $y$ 个 $-1$。

$$k - (i - k) = 2k - i \le m$$

那么 $1$ 的数目不超过 $\dfrac{i + x - y}{2}\le\dfrac{n-y+x}{2}$，显然也不会超过 $x$。

$-1$ 同理。

初值：$f_{0,0}=1$。目标：$f_{n,x-y}$。

实现时需要滚动数组压缩空间。时间复杂度 $O(n^2)$ 常数很小。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
int n, m, x, y, z;
long long ans, g[10005], f[10005];
signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &z), (z == 1 ? ++x : ++y);
    if (x <= y) {
        g[0] = 1;
        for (int i = 0; i <= y + 1; ++i)
            for (int j = i; j >= 1; --j) g[j] = (g[j] + g[j - 1]) % mod;
        printf("%lld", g[x]);
    } else {
        m = x - y;
        f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= 0; --j) {
                g[j] = f[j + 1];
                if (j) g[j] = (g[j] + f[j - 1]) % mod;
            }
            for (int j = m; j >= 0; --j) f[j] = g[j];
        }
        printf("%lld\n", f[m]);
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/lgr125.html)

## 简要题意

给你一个由 $1,-1$ 组成的长度为 $n(1 \leq n \leq 10^4)$ 的序列 $a$，询问有多少个将 $a$ 重排后的序列使得该序列的最大子段和最小化。答案对 $998244353$ 取模。

## 思路

首先由上题得在 $1$ 的个数（下设为 $p$）大于 $-1$ 的个数）（下设为 $e$）时，最大子段和的最小值 $L=\sum a$，在 $p<e$ 时 $L=1$，在 $p=e$ 时 $L=0$。

- 当 $p\leq e$ 时，与 $-1$ 和 $1$ 的位置无关，我们可以直接将 $-1$ 固定，到里面插入 $1$。因此此时答案为 $\binom{p}{e+1}$。
- 当 $p>e$ 时，与位置有关，我们考虑 DP，设 $f_{i,j}$ 为前 $i$ 个数凑出和为 $j$ 的方案数，则动态转移方程：

$$
f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}\ \ \ \ \ f_{0,0}=1\ \ \ \ \ f_{i,0}=f_{i-1,1}
$$

推导过程 $f_{i,j}$ 可以从从 $f_{i-1,j-1}$ 中加上 $1$ 得来，也可以从 $f_{i-1,j+1}$ 中减去 $1$ 得来。$f_{i,0}$ 只能从 $f_{i-1,1}$ 中减去 $1$ 得来。

但是对于 $1 \leq n \leq 10^4$ 时 $f$ 空间开不下，需要进行滚动数组优化。

时间复杂度 $O(n^2)$（$p>e$）或 $O(n\log n)$（$p\leq e$）。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int f[10005],fold[100005];
int fact[10005];
const int mod = 998244353;
int n,pos,neg,sum;

int pow(int a,int b,int mod) {
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) {
		if(b&1) {
			ans=1ll*ans*a%mod;
		}
	}
	return ans;
}

int inv(int x){
	return pow(x,mod-2,mod);
}

int c(int m,int n){
	return (fact[n]*inv(fact[m])%mod)*inv(fact[n-m])%mod;
}

signed main(){
	cin>>n;
	for(int i=1,v;i<=n;i++){
		cin>>v;
		if(v==1)pos++;
		else neg++;
		sum+=v;
	}
	if(neg>=pos){
		fact[0]=fact[1]=1;
		for(int i=2;i<=(n+1);i++){
			fact[i]=fact[i-1]*i%mod;
		}
		cout<<c(pos,neg+1)<<'\n';
		return 0;
	}
	f[0]=fold[0]=1;
	for(int i=1;i<=n;i++){
		f[0]=fold[1];
		for(int j=1;j<=sum;j++){
			f[j]=(fold[j-1]+fold[j+1])%mod;
		}
		memcpy(fold,f,sizeof(f));
	}
	cout<<f[sum]<<'\n';
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8848)

这题并不是很难，但是还是卡了快我一个小时（，最后跟 $\verb!dalao!$ [$\verb!edge!$](https://www.luogu.com.cn/user/208653) 一起搞出来了。

思路可能有些怪异，不喜勿喷。

## 思路

首先，我们发现 $n \le 10$ 的部分非常好做，可以直接 $\verb!DFS!$ 爆搜，很快啊，我们就码出来了。

[代码链接](https://www.luogu.com.cn/paste/otucw5p7)

接下来考虑正解。

正解显然是个 $\verb!DP!$，但是问题在于怎么 $\verb!DP!$。

首先，打个表，对于 $n=10$ 的样例，我们可以打出以下的表。

[打表链接](https://www.luogu.com.cn/paste/1rztwlbi)

我们可以发现一个规律，若此时放置的是第 $j$ 个 $-1$，需要放在第 $i$ 个位置上，则 $j$ 需要满足 $2 \times j \le i$ 以及 $sum-j<n-i$，其中 $sum$ 表示 $-1$ 的总数。

于是原问题等价于把 $-1$ 插到 $1$ 中，但是要满足一些小小的限制。

于是当 $sum>n-sum$ 时，我们可以推出一个 $\mathcal O(n^3)$ 的 $\verb!DP!$，随便前缀和优化一下就 $\mathcal O(n^2)$ 了。

接下来考虑 $sum \le n-sum$ 怎么做，其实道理是一样的，只不过是把 $1$ 插到了 $-1$ 里面而已，不再赘述。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e4+10;
int const mod=998244353;
int n,a[N],f[5][N],f1[N][5],qz[2][N],qsum[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;int sum=0;
    for (int i=1;i<=n;++i) cin>>a[i],sum+=(a[i]==-1);
    f[1][0]=1;f1[1][0]=1;
    for (int j=0;j<=sum;++j) qz[1][j]=1;
    int ans=0;
    if (sum==n) return cout<<"1\n",0;
    if (sum>=n-sum){
        int sum1=n-sum;
        for (int i=2;i<=sum1;++i)
            for (int j=0;j<=sum;++j){
                f[i&1][j]=qz[(i-1)&1][j-1];
                if (!j) qz[i&1][j]=f[i&1][j];
                else qz[i&1][j]=f[i&1][j]+qz[i&1][j-1];
                qz[i&1][j]%=mod;
            }
        for (int i=sum1-1;i<=sum;++i){
            ans+=f[sum1&1][i]%mod*(sum-i+1)%mod;
            ans%=mod;
        }
        cout<<ans<<"\n";
        return 0;
    }
    #define f f1
    for (int i=1;i<=n;++i) qsum[i]=qsum[i-1]+f[i][0];
	for (int j=1;j<=sum;++j){ 
    	for (int i=1;i<=n;++i){
            if (2*j>i) continue;
            int q=sum-j;
            if (2*q>=(n-i)) continue;
			int L=max(1ll,2*j-3),R=i-1;
			f[i][j&1]+=qsum[R]-qsum[L-1];
			f[i][j&1]%=mod;f[i][j&1]+=mod;f[i][j&1]%=mod;
        }
        for (int i=1;i<=n;++i){
			qsum[i]=qsum[i-1]+f[i][j&1];qsum[i]%=mod;
			if (j!=sum) f[i][j&1]=0;
		}
    }
    for (int i=1;i<=n;++i) ans+=f[i][sum&1],ans%=mod;
    cout<<ans<<'\n';
    return 0;
}
```

---

