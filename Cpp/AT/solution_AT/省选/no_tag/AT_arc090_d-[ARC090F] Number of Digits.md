# [ARC090F] Number of Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc090/tasks/arc090_d

正の整数 $ n $ に対し、$ f(n) $ を $ n $ の $ 10 $ 進法での桁数と定めます。

整数 $ S $ が与えられます。 正の整数の組 $ (l,\ r) $ ($ l\ \leq\ r $) であって、$ f(l)\ +\ f(l\ +\ 1)\ +\ ...\ +\ f(r)\ =\ S $ を満たすものの個数を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ S\ \leq\ 10^8 $

### Sample Explanation 1

条件を満たす $ (l,\ r) $ の組は $ (1,\ 1) $, $ (2,\ 2) $, $ ... $, $ (9,\ 9) $ の $ 9 $ 個あります。

### Sample Explanation 2

条件を満たす $ (l,\ r) $ の組は $ (1,\ 2) $ や $ (33,\ 33) $ など $ 98 $ 個あります。

## 样例 #1

### 输入

```
1```

### 输出

```
9```

## 样例 #2

### 输入

```
2```

### 输出

```
98```

## 样例 #3

### 输入

```
123```

### 输出

```
460191684```

## 样例 #4

### 输入

```
36018```

### 输出

```
966522825```

## 样例 #5

### 输入

```
1000```

### 输出

```
184984484```

# 题解

## 作者：zhimao (赞：3)

目前最快做法，最慢一个点只要 24ms 。

对于满足条件的 $(l,r)$ 分类：
- $f(r)-f(l)=0$
- $f(r)-f(l)=1$
- $f(r)-f(l)>1$

第一种可以直接计算：$ans=9 \times 10^{f(r)-1}-n \div f(r)+1$ 注意此时 $n  \bmod f(r)=0$

对于第三种 ， 经过计算我们可以发现 $k<=10^8$ 时 $f(l)<=7$ 。 因此可以用尺取法直接做 。 

对于第二种 , 我们列一个方程：
$$f(l) \times a + (f(l)+1) \times b=k$$
$$f(l) \times (a+b) + b=k$$

为避免与第一种重复 ， $a>0$ 且 $b>0$ 。对于正整数 $a,b$ 解方程得 $a+b$ 为 $\left\lfloor\dfrac{k}{f(l)}\right\rfloor+1$ 到 $\left\lfloor\dfrac{k-1}{f(l)}\right\rfloor$ 的正整数 。

于是据此我们有了第一份代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long ans,n;
int main()
{
	scanf("%lld",&n);
	long long l=1,r=1,t=1,len1=1,p=10,len2=1,q=10;
	do
	{
		while(t<n)
		{
			++r;
			if(r==p) p*=10,++len1;
			t+=len1;
		}
		if(t==n) ++ans;
		++l;
		t-=len2;
		if(l==q) q*=10,++len2;
	}while(l<10000000);//情况三
	for(long long i=8,p=90000000;i<=n;i++,p=p*10%mod)
	{
		if(n%i==0) ans=(ans+p-n/i+1+mod)%mod;//情况一
		ans=(ans+(n-1)/i-n/(i+1))%mod;//情况二
	}
	printf("%lld",ans);
}
```
很可惜 ， [它](https://www.luogu.com.cn/record/42678900) T 了 ，极限数据大概跑了 2.5 s 。

本地测了下 ， 我发现情况三最快 ， 常数极小 ， 只用了二十多毫秒 。于是考虑优化下面的 for 循环 。 我们发现情况一可以直接独立出来 ， 枚举 $n$ 的因数 。 $p$ 直接 快速幂 。 

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long ans,n;
long long kp(long long a,long long b)
{
	long long c=1;
	do
	{
		if(b&1) c=c*a%mod;
		a=a*a%mod;
		b>>=1;
	}while(b);
	return c;
}
int main()
{
	scanf("%lld",&n);
	register long long l=1,r=1,t=1,len1=1,p=10,len2=1,q=10;
	do
	{
		while(t<n)
		{
			++r;
			if(r==p) p*=10,++len1;
			t+=len1;
		}
		if(t==n) ++ans;
		++l;
		t-=len2;
		if(l==q) q*=10,++len2;
	}while(l<10000000);//情况一
	for(register long long i=8;i<=n;++i) ans+=(n-1)/i-n/(i+1);//情况二
	for(register long long i=1;i*i<=n;++i)
		if(n%i==0)
		{
			if(i>7) ans+=(9ll*kp(10,i-1)-n/i+1)%mod;
			if(i*i!=n&&n/i>7) ans+=(9ll*kp(10,n/i-1)-i+1)%mod;
		}//情况三
	printf("%lld",(ans+mod)%mod);
}
```


[这样子](https://www.luogu.com.cn/record/42679759)就过了此题 ， 但跑得贼慢 ， 垫底了 。

仔细一看 ， 情况二可以整除分块 ！ 改好以后就跑得飞快了 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
long long ans,n;
long long kp(long long a,long long b)
{
	long long c=1;
	do
	{
		if(b&1) c=c*a%mod;
		a=a*a%mod;
		b>>=1;
	}while(b);
	return c;
}
int main()
{
	scanf("%lld",&n);
	register long long l=1,r=1,t=1,len1=1,p=10,len2=1,q=10;
	do
	{
		while(t<n)
		{
			++r;
			if(r==p) p*=10,++len1;
			t+=len1;
		}
		if(t==n) ++ans;
		++l;
		t-=len2;
		if(l==q) q*=10,++len2;
	}while(l<10000000);
	for(register long long l=1,r;l<=n-1;l=r+1)
	{
		r=(n-1)/((n-1)/l);
		ans=(ans+(r-l+1)*((n-1)/l))%mod;
	}
	for(register long long l=1,r;l<=n;l=r+1)
	{
		r=n/(n/l);
		ans=(ans-(r-l+1)*(n/l)%mod+mod)%mod;
	}
	for(int i=1;i<=7;i++) ans=(ans-(n-1)/i+n/i)%mod;
	ans=(ans+n/8)%mod;
	for(register long long i=1;i*i<=n;++i)
		if(n%i==0)
		{
			if(i>7) ans+=(9ll*kp(10,i-1)-n/i+1)%mod;
			if(i*i!=n&&n/i>7) ans+=(9ll*kp(10,n/i-1)-i+1)%mod;
		}
	printf("%lld",(ans+mod)%mod);
}
```

其实此题数据可以加强 ， $k$ 可以出到 $5 \times 10^9$ 。

---

## 作者：NaVi_Awson (赞：3)

## Description

[题库链接](https://arc090.contest.atcoder.jp/tasks/arc090_d)

记 $d$ 在十进制下的位数为 $f(d)$ 。给出询问 $S$ ，求有多少对 $(l,r)$ 使得 $$\sum_{i=l}^r f(i)=S$$

$1\leq S\leq 10^8$

## Solution

注意到当数字越大时 $f(r)-f(l)$ 会越小。

分两种情况讨论：

1. $f(l)\leq 7$ ，这时可以用尺取法来做，可以发现它的右界为 $10^7+\frac{10^8}{8}=25500000$ ；

2. $f(l)\geq 8$ ，我们依旧可以分两种情况来考虑：

    1. $f(r)-f(l)=0$ ，此时显然选的数都是位数相同的，我们可以统计这种位数的个数 $sum$ ，该种情况的答案 $sum-f(l)+1$ ；

    2. $f(r)-f(l)=1$ 。假设取的数个数为 $t$ ，即 $r-l+1=t$ ，取长度为 $f(l)$ 的个数为 $x$ ，长度为 $f(r)$ 的个数为 $y$ ： $$\begin{cases}x+y=t\\x\cdot f(l)+y\cdot f(r)=S\end{cases}$$
那么 $f(l)\cdot t+y=S$ 我们可以枚举 $t$ ，容易发现 $\begin{cases}y=S~mod~t\\x=t-S~mod~t\end{cases}$ ，即对于每个 $t$ ，都可以解出唯一解。值得注意的是这方面的解会和上面的解重复，即当 $f(l)\mid S$ 这里会计算一次。

综上可以分情况处理。

## Code

```cpp
//It is made by Awson on 2018.2.3
#include <bits/stdc++.h>
#define LL long long
#define dob complex<double>
#define Abs(a) ((a) < 0 ? (-(a)) : (a))
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Swap(a, b) ((a) ^= (b), (b) ^= (a), (a) ^= (b))
#define writeln(x) (write(x), putchar('\n'))
#define lowbit(x) ((x)&(-(x)))
using namespace std;
const int l1 = 10000000;
const int l2 = 25500000;
const int yzh = 1e9+7;
void read(int &x) {
    char ch; bool flag = 0;
    for (ch = getchar(); !isdigit(ch) && ((flag |= (ch == '-')) || 1); ch = getchar());
    for (x = 0; isdigit(ch); x = (x<<1)+(x<<3)+ch-48, ch = getchar());
    x *= 1-2*flag;
}
void print(int x) {if (x > 9) print(x/10); putchar(x%10+48); }
void write(int x) {if (x < 0) putchar('-'); print(Abs(x)); }

int s, f[l2+5];

int quick_pow(int a, int b) {
    int ans = 1;
    while (b) {
	if (b&1) ans = 1ll*ans*a%yzh;
	a = 1ll*a*a%yzh, b >>= 1;
    }
    return ans;
}
int count1(int n) {
    int ans = 0, r = 0, cnt = 0;
    for (int i = 1; i < l1; i++) {
	cnt -= f[i-1];
	while (cnt+f[r+1] <= s && r < l2) cnt += f[++r];
	if (cnt == s) ++ans;
	if (r == l2) break;
    }
    return ans;
}
int count2(int n) {
    int lim = n/8, ans = lim;
    for (int t = 1; t <= lim; t++)
	if (n%t == 0) {
	    int len = n/t;
	    (ans += (1ll*quick_pow(10, len-1)*9%yzh-t)%yzh) %= yzh;
	}
    return ans;
}
void work() {
    for (int i = 1, r = 10, cnt = 1; i < l1; i++, i = r, r = r*10, cnt++)
	for (int j = i; j < r; j++) f[j] = cnt;
    for (int i = l1; i <= l2; i++) f[i] = 8;
    read(s);
    writeln(((count1(s)+count2(s))%yzh+yzh)%yzh);
}
int main() {
    work();
    return 0;
}
```

---

## 作者：rizynvu (赞：1)

[我的博客](https://www.cnblogs.com/rizynvu/p/18281509)。

2024.07.02：修改了复杂度的表示，完善了 $f(l) = f(r)$ 时的条件。

记 $n$ 为题面的 $S$。

能发现对于 $f(l) = 8$，共有 $9\times 10^7$ 个数。  
此时就已经有 $8\times 9\times 10^7 > 10^8 = n_{\max}$ 了，就说明不存在 $f \ge 8$ 的情况，还满足这部分对应的数能全被选满。

所以可以知道对于 $f(l)\ge 8$ 的情况，只存在 $f(r) - f(l) = 0 \operatorname{or} 1$ 的情况。

对于 $f(l)\le 7$ 的情况。  
能发现 $r$ 的上界是 $10^7 + \frac{10^8}{8}$，所以这部分直接双指针就行了。

接下来考虑 $f(l)\ge 8, f(r) - f(l) = 1$ 的情况。  
考虑令 $f(l)$ 选了 $x$ 个，$f(r) = f(l) + 1$ 选了 $y$ 个。  
需要先声明的是，在这个位置先不考虑 $x, y > 0$ 的限制，而认为 $y$ 可以为 $0$，关于这部分将会在后面提到。  
那么就能得到 $(x + y)f(l) + y = n$。  
然后这里以 $x + y$ 为主元，能发现对于固定的 $x + y$，其对应的 $f(l)$ 和 $x, y$ 都只有 $1$ 个，就是 $\begin{cases}y = n\bmod (x + y)\\ x = (x + y) - y\\ f(l) = \frac{n - y}{x + y}\end{cases}$。  

于是转而去考虑 $x + y$ 能有多少种可能。  
这是好算的，因为 $x + y\le \frac{n}{f(l)}$，而因为 $f(l)\ge 8$，所以 $x + y\le \frac{n}{8}$，对应的就有 $\lfloor \frac{n}{8} \rfloor$ 种选法。

最后来考虑 $f(l)\ge 8, f(r) - f(l) = 0$ 的情况。  
这个时候就要求 $f(l) \mid n$，同时也知道需要的数的个数 $x = \frac{n}{f(l)}$ 了。  
那么显然答案就为 $9\times 10^{f(l) - 1} - x + 1$，但注意到，在前文的时候提到了误给 $y = 0$ 时加了 $1$ 的贡献，而其对应的应该就是这种 $f(r) - f(l) = 0$ 的情况，所以实际算贡献的时候应该算为 $9\times 10^{f(l) - 1} - x$。  
这部分可以 $\mathcal{O}(\sqrt{n} + d(n)\log n)$。

时间复杂度 $\mathcal{O}(\frac{n}{B} + \sqrt{n} + d(n)\log n)$，其中 $B = 8$，$d(n)$ 表示 $n$ 的因子个数。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr ll mod = 1e9 + 7;
inline ll qpow(ll a, ll b, ll v = 1) {
   while (b)
      b & 1 && (v = v * a % mod), b >>= 1, a = a * a % mod;
   return v;
}
ll ans;
const int limn = (int)1e7 + (int)1e8 / 8, R = (int)1e7;
int f[limn + 10];
int main() {
   for (int i = 1, l = 1, r = 10; i <= 8; i++, r = std::min(l * 10, limn))
      while (l < r) f[l++] = i;
   int n; scanf("%d", &n);
   for (int i = 1, j = 0, sum = 0; f[i] <= n && i < R; i++) {
      while (sum + f[j + 1] <= n) sum += f[++j];
      if (sum == n) (++ans) %= mod;
      sum -= f[i];
   }
   (ans += n / 8) %= mod;
   auto calc = [&](int fx) {
      int l = n / fx;
      ll len = 9ll * qpow(10, fx - 1) % mod;
      (ans += mod + len - l) %= mod;
   };
   for (int i = 1; i * i <= n; i++) if (n % i == 0) {
      if (i >= 8) calc(i);
      if (n / i >= 8 && i != n / i) calc(n / i);
   }
   printf("%lld\n", ans);
   return 0;
}
```

---

## 作者：wgyhm (赞：1)

## Description

https://www.luogu.com.cn/problem/AT_arc090_d

## Solution

根号做法，目前最优解。

记位数为 $x$ 的数的个数为 $g(x)=9\times 10^{x-1}$

显然要分类讨论 $f(l)$ 和 $f(r)$ 的关系。

1. $f(l)=f(r)$：

   答案为 $g(l)-\dfrac{n}{f(l)}+1$，还需要满足 $f(l)|n$，可以通过枚举因数做到 $O(\sqrt n)$。因为因数个数不是瓶颈所以可以放心使用快速幂。

2. $f(l)+1=f(r)$：

   考虑列方程 $x\times f(l)+y\times (f(l)+1)=k$ 且 $x,y>0$。

   化简后有 $\lfloor\dfrac{k}{f(l)}\rfloor <x+y\le \lfloor\dfrac{k-1}{f(l)}\rfloor$。对于 $f(l)\ge 8$ 的情况没有 $x,y$ 的限制，容易想到用整除分块去做。否则可以跟下面一种情况一起做。

3. $f(l)+1<f(r)$：

   中间的数一定要取，根据 $n$ 的范围可以知道 $f(r)\le 8$。那么可以直接枚举 $f(l),f(r)$，然后求解二元一次方程即可。注意两个系数存在上下界。

最后的复杂度就是 $O(\sqrt n+\log ^3 n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long 
#define maxn
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
ll power(ll x,int y=mod-2,int p=mod) {
	ll sum=1;x%=p;
	while (y) {
		if (y&1) sum=sum*x%p;
		x=x*x%p;y>>=1;
	}
	return sum;
}
int gcd(int x,int y) {return !y?x:gcd(y,x%y);}
void exgcd(int a,int b,int &x,int &y) {
	if (!b) return x=1,y=0,void();
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
int n,ans;
void add(int &x,int y) {x=(x+y)%mod;}
int F(int x) {
	return power(10,x-1)*9%mod;
}
void calc(int x) {
	int res=F(x);
	if (x<=8&&res*x<n) ;
	else add(ans,res-n/x+1);
}
signed main(void){
	int i,x,y,j;
	read(n);
	for (i=1;i*i<=n;i++) if ((n%i)==0) {
		calc(i);
		if (i*i<n) calc(n/i);
	} 
	int res=ans;
	for (i=1;i<=8;i++) {
		int res=0;
		for (j=i+1;j<=8;j++) {
			if (res+i+j>n) break;
			int tmp1=F(i)-1,tmp2=F(j)-1;
			int a=i,b=j,c=n-res-i-j,d=gcd(a,b);
			res+=F(j)*j;
			if (c%d) continue;
			exgcd(a,b,x,y);
			a/=d,b/=d,c/=d;
			x*=c,y*=c;
			int L=max(ceil(1.0*(-x)/b),ceil(1.0*(y-tmp2)/a));
			int R=min(floor(1.0*(y)/a),floor(1.0*(tmp1-x)/b));
			if (L<=R) ans+=R-L+1;
		}
	}
	
	int l,r;
	for (l=9;l<=n;l=r+1) {
		r=min(n,n/(n/l));
		add(ans,mod-(r-l+1)*(n/l)%mod);
	}
	for (l=8;l<n;l=r+1) {
		r=min(n-1,(n-1)/((n-1)/l));
		add(ans,(r-l+1)*((n-1)/l));
	}
	printf("%lld\n",ans%mod);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

## 作者：Graygoo (赞：1)

众所周知，目前这篇题解的复杂度都是 $O({k \over {\log k}})$ 的，所以下文给出一个 $O(k^{0.5})$ 复杂度的算法。

1. $f(r) = f(l)$ 枚举因子，用光速幂即可做到根号。

2. $f(r) = f(l)+1$ 这里比原题解更复杂的地方只在于这里可能会有某种位数被全部填满而导致不可行，但原题解做法因为只考虑 $f(l) \geq 8$ 导致不会出现这种情况。观察可得，仅在 $f(l) \leq O(\log k)$ 时会出现这种情况，特殊处理即可；更大的直接按照原题解方法加上一个值即可。这一块复杂度 $O(\log k)$。

3. $f(r) - f(l) \geq 2$ 枚举 $f(l),f(r)$，这里 $f(l) , f(r) = O(\log k)$，所以暴力枚举即可，直接用扩欧计算答案，注意这里也可能存在上一类的填满问题，但是这相当于给扩欧的变量一个上下界，不是问题。这一块复杂度 $O(\log^3 k)$。

综上，我们得到了一个复杂度为 $O(\sqrt{k} + \log k +\log^3 k) = O(\sqrt{k})$ 的做法。

没有实现过，如果假了欢迎正义辱骂。

---

## 作者：EuphoricStar (赞：1)

一道有趣的数学+思维题。

## 思路

分类讨论：

- 如果 $f(r) - f(l) \ge 2$，那么易得 $f(l) \le 7$，这部分可以用尺取法计算。

- 如果 $f(r) - f(l) \le 1$，枚举区间的长度 $i$（$i$ 显然要 $\le$ $\left\lfloor\dfrac{n}{8}\right\rfloor$），那么对于每一个 $i$ 都存在且仅存在一对 $(l,r)$ 满足 $\sum\limits_{i=l}^r{f(i)} = S$。感性理解一下，先令 $f(l)$ 到 $f(r)$ 都为 $\left\lfloor\dfrac{n}{i}\right\rfloor$，之后将 $r - n \bmod i + 1$ 到 $r$ 的 $f$ 值全部 $+1$，就凑出了 $S$。

- 要注意 $f(r) - f(l) = 0$ 的情况，即 $f(l) = f(r)$，同样枚举区间长度 $i$，那么 $i$ 必须是 $S$ 的因数。此时有 $f(l) = \dfrac{n}{i}$。因为有 $10^{f(l)} - 10^{f(l) - 1}$ 个 位数为 $f(l)$ 的数，因此他们形成了 $10^{f(l)} - 10^{f(l) - 1} - i + 1$ 个连续的区间，将 $10^{f(l)} - 10^{f(l) - 1} - i$ 直接累加至答案即可。（不用 $+1$ 是因为这个在上面 $f(r) - f(l) \le 1$ 的情况已经加过了）

## 代码

```cpp
const int maxn = 40000000;
const ll mod = 1000000007;

int f[maxn];
ll n;

ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

void prepare() {
	for (int i = 0; i <= 7; ++i) {
		ll l = qpow(10, i), r = qpow(10, i + 1) - 1;
		for (int j = l; j <= min(r, 39999900LL); ++j) {
			f[j] = i + 1;
		}
	}
}

void solve() {
	scanf("%lld", &n);
	ll ans = 0, sum = 0;
	for (int i = 1, j = 0; i < 10000000; ++i) {
		while (sum + f[j + 1] <= n) {
			sum += f[++j];
		}
		if (sum == n) {
			++ans;
		}
		sum -= f[i];
	}
	ans = (ans + n / 8) % mod;
	ll tmp = n / 8;
	for (ll i = 1; i <= tmp; ++i) {
		if (n % i == 0) {
			ll t = n / i;
			ans = ((ans + qpow(10, t) - qpow(10, t - 1) - i) % mod + mod) % mod;
		}
	}
	printf("%lld\n", ans);
}
```


---

