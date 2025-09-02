# [Math×Girl] 平均律

## 题目背景

>只见盈盈的双手在键盘上游移，速度越来越快。毫无秩序的音符间填上了其他的音符。一堆杂乱无章的音符中诞生了小小的图案，然后无数的图案开始交织，形成了更大的图案。  
>然后，就从离散走向了连续!

_※ 为了题面的简洁性，我删去了其中与音乐有关的内容。_

## 题目描述

我们定义一个数的近似分数为：  
在允许的误差内分母最小的分数。  
_※ 这里允许分数的分母为 $1$。_

请问允许的误差为 $\pm\delta$ 时，  
任选一数 $\xi\in[0,1]$，  
其近似分数的分母为 $n$ 的概率是多少？

## 说明/提示

### 样例解释

第一个例子取模前的结果为 $\frac{1}{3}$。  
第二个例子取模前的结果为 $\frac{8}{35}$。  

### 数据范围

**UPD：$n=1$ 时对于子任务限制的描述不正确，请进行特判。**

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $\frac{1}{n}<\delta,n\in[1,10^6]$ |
| $1$ | $10$ | $\delta<\frac{1}{2n^2},n\in[1,10^6]$ |
| $2$ | $15$ | $n\in[1,10^3]$ |
| $3$ | $15$ | $n\in[1,10^4]$ |
| $4$ | $15$ | $n\in[1,10^5]$ |
| $5$ | $15$ | $n\in[1,2\times10^6]$ |
| $6$ | $20$ | $T=1$ |

对于 $100\%$ 数据，保证 $T\in[1,5],n\in[1,10^7],a,b\in[1,10^{18}],998244353\nmid b$。

对于计算有理数取模的方法，请参考[模板题](https://www.luogu.com.cn/problem/P2613)。

## 样例 #1

### 输入

```
3
3 1 9
3 2 35
114514 233 87654321```

### 输出

```
332748118
969723086
590198578```

# 题解

## 作者：Naszt (赞：4)

# 平均律

## 观前提醒

感谢 @[飞雨烟雁](luogu://user/375984) 大佬提供了一种线性的做法。

## 思路分析

### 找突破口

由于近似分数一定是既约分数，下文「分数」指的都是既约分数。

我们记一个分数 $x$ 的 前驱/后继 为 $x^-$/$x^+$，  
定义为分母比 $x$ 的分母小，数值小于/大于 $x$ 的最接近 $x$ 的分数。

枚举分母为 $n$ 的分数 $x$，答案就是近似分数为 $x$ 的区间和：  
$$ans=\sum\max(\min(x^+-\delta,x+\delta)-\max(x^-+\delta,x-\delta),0)$$

### 计算前驱/后继

_※ 这一小节是 $\log$ 做法。_  
有：
$$
\begin{aligned}
x^+&=\lfloor x\rfloor+(x-\lfloor x\rfloor)^+\\
x^+&=1/(1/x)^-\\
x^-&=\lfloor x\rfloor+(x-\lfloor x\rfloor)^-\\
x^-&=1/(1/x)^+
\end{aligned}
$$

若 $x=\frac1n$，则 $x^-=\frac01,x^+=\frac1{n-1}$  
由此便可以递归求解。

其中的 $(1)(3)$ 式是因为每一段整数都是等价的。  
$(2)(4)$ 式可用反证法证明。

而以上方法的本质其实就是 简单连分数，更本质一点就是 辗转相除法。  
时间复杂度也自然是 $O(\log n)$，总时间复杂度是 $O(n\log n)$。

### 线性方法

对于分数 $\frac dn$，设其前驱和后继为 $\frac xy<\frac dn<\frac zw$，则：

$$
\begin{aligned}
\frac dn-\frac xy&=\frac{dy-nx}{ny}=\frac 1{ny}\\
\frac zw-\frac dn&=\frac{zn-dw}{nw}=\frac 1{nw}
\end{aligned}
$$

根据 $dy\equiv 1\pmod n,dw\equiv -1\pmod n$ 即可求出 $y,w$。  
但是你不能线性递推的求逆元，因为 $n$ 不一定是质数，  
你可以根据逆元的积性和线性筛预处理。

这样的时间复杂度就是 $O(n)$ 的。

## 代码实现

### 出题人代码

```cpp
#include<bits/stdc++.h>
typedef unsigned long long i8;
const i8 MOD=998244353,MX=10000005;
i8 Inv[MX],Invp[MX],da,db,v;
long double I=1,V;
std::vector<i8>Prime;
bool vis[MX];
const __int128 II=1;
void exgcd(i8 a,i8 b,i8&x,i8&y) {
  if(!b)x=1,y=0;
  else exgcd(b,a%b,y,x),y-=a/b*x;
}
void sieve(const i8 n){
  Inv[1]=1;Prime={};
  for(i8 i=2;i<=n;i++){
    if(!vis[i]){
      Prime.push_back(i);
      if(n%i==0)Inv[i]=0;
      else{i8 x,y;exgcd(i,n,x,y);Inv[i]=(x+n)%n;}
    }
    for(i8 p:Prime){
      if(i*p>n)break;
      vis[i*p]=1;Inv[i*p]=Inv[i]*Inv[p]%n;
      if(i%p==0)break;
    }
  }
}
struct frac{
#define il inline __attribute__((__always_inline__))
  i8 a,b;char f;//frac{a}{b}+f\delta
  il frac(i8 A,i8 B,char F):a(A),b(B),f(F){}
  il friend i8 model(frac x){return (x.a*Invp[x.b]+(x.f==1?v:MOD-v));}
  il friend bool operator<(frac x,frac y){
//    return I*x.a/x.b+x.f*I*da/db<I*y.a/y.b+y.f*I*da/db;//精度会炸
    return (y.f-x.f)*II*da*y.b*x.b>(II*x.a*y.b-II*y.a*x.b)*db;
  }
};
void slove(){
  i8 n,g,ans=0;
  std::cin>>n>>da>>db;
  g=std::gcd(da,db),da/=g,db/=g;
  i8 x,y;exgcd(db%MOD,MOD,x,y);v=da%MOD*(x+MOD)%MOD;
  if(n==1){std::cout<<(2*da<db?2*v%MOD:1)<<"\n";return;}
  if((__int128)2*n*da>=db){std::cout<<"0\n";return;}
  sieve(n);Invp[1]=1;
  for(i8 i=2;i<=n;i++)Invp[i]=Invp[MOD%i]*(MOD-MOD/i)%MOD;
  for(i8 d=1;d<n;d++){
    if(!Inv[d])continue;
    frac _x=std::max(frac((d*Inv[d]-1)/n,Inv[d],+1),frac(d,n,-1));
    frac x_=std::min(frac((d*(n-Inv[d])+1)/n,n-Inv[d],-1),frac(d,n,+1));
    if(_x<x_)ans=(ans+model(x_)+MOD-model(_x)%MOD)%MOD;
  }
  std::cout<<ans<<"\n";
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  i8 T;std::cin>>T;
  while(T--)slove();
  return 0;
}
```

### 验题人代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
#define lll __int128
using namespace std;

const int Mx = 1e7 + 5, Mod = 998244353;
int n;
ll a, b;

int inv_mod(ll a){ // a < Mod
  int res = 1, b = Mod - 2;
  while(b){
    if(b & 1) res = res * a % Mod;
    a = a * a % Mod, b >>= 1;
  }
  return res;
}

bool coprime[Mx], vis[Mx];
int prime[Mx], tot;
int inv[Mx], invp[Mx];

void sieve(){
  tot = 0, inv[1] = coprime[1] = 1;
  for(int i = 2; i < n; ++i){
    if(!vis[i]) prime[++tot] = i, coprime[i] = (n % i > 0);
    for(int j = 1; j <= tot && prime[j] * i < n; ++j){
      vis[i * prime[j]] = true;
      coprime[i * prime[j]] = coprime[i] & coprime[prime[j]];
      if(i % prime[j] == 0) break;
    }
  }
  for(int i = 2; i < n; ++i){
    if(coprime[i]) inv[i] = 1ll * inv[i - 1] * i % n;
    else inv[i] = inv[i - 1];
  }
  int back = 1, temp = inv[n - 1];
  for(int i = n - 1; i > 1; --i) if(coprime[i]){
    inv[i] = 1ll * inv[i - 1] * back % n;
    back = 1ll * back * i % n;
  }
  if(temp == n - 1) for(int i = 2; i < n; ++i) inv[i] = n - inv[i];
}

int solve(){
  int delta = a % Mod * inv_mod(b % Mod) % Mod;
  if(n == 1) return 2 * a < b ? 2 * delta % Mod : 1;
  sieve();
  invp[1] = 1;
  for(int i = 2; i <= n; i++) invp[i] = -invp[Mod % i] * (ll)(Mod / i) % Mod;
  ll Ans = 0;
  for(int d = 1; d < n; ++d) if(coprime[d]){
    int y = inv[d], w = n - inv[d];
    int x = 1ll * d * y / n, z = (1 + 1ll * d * w) / n;
    if((lll)b * z * y <= (lll)2 * a * w * y + (lll)b * w * x) continue;
    if(b / 2 / a / n >= y) Ans -= 1ll * d * invp[n] % Mod - delta;
    else Ans -= 1ll * x * invp[y] % Mod + delta;
    if(b / 2 / a / n >= w) Ans += 1ll * d * invp[n] % Mod + delta;
    else Ans += 1ll * z * invp[w] % Mod - delta;
  }
  Ans %= Mod;
  return Ans < 0 ? Ans + Mod : Ans;
}

int main(){
  int T;
  scanf("%d", &T);
  while(T--){
    scanf("%d%lld%lld", &n, &a, &b);
    printf("%d\n", solve());
  }
  return 0;
}
```

---

## 作者：blue_ice26 (赞：2)

由于本人数学非常不好，所以提供一篇比较暴力的题解。  
## 思路解析
根据题意，对于任意对答案可能有贡献的分数 $\frac{i}{n}$，我们只需找到第一个小于和第一个大于它且分母小于 $n$ 的两个分数 $l$ 和 $r$，然后根据误差 $eps=\frac{a}{b}$ 算出贡献：
$$
\max(0,\min(r-eps,s+eps)-\max(l+eps,s-eps))
$$
如何找到这两个数呢？  
那就需要一个非常好用的东西：[Stern–Brocot 树](http://oi-wiki.com/math/number-theory/stern-brocot/)。不过这玩意非常复杂~~我也不太懂~~，但是从中查找分数非常方便，每次查找的复杂度是 $O(\log n)$ 级别的。  
然后交上去就超时了~~毕竟算是半个暴力不超时才怪~~。  
所以需要亿点点的卡常。
## 卡常小技巧
- 不知道为什么，查找分数时用倍增比线性算法还要快（估计除法还是太慢了）。
- 尽量少用 int128，不用double。
- 在枚举分数时去掉非最简分数不要去求最大公约数，分解质因数后再筛会更快。
- 少用除法，乘法会更快。
- 注意到 $\frac{i}{n}$ 与 $\frac{n-i}{n}$ 的贡献相同，可以直接省去一半的计算量。

~~卡常两天的成果~~更细节的东西都放在代码注释中了。  
码风不好请见谅。
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
constexpr int M=998244353;
struct fraction
{
	int a,b;
	inline fraction()
	{
	}
	inline fraction(int x,int y)
	{
		a=x;
		b=y;
	}
};
struct fraction2
{
	long long a,b;
	inline fraction2()
	{
	}
	inline fraction2(const long long &x,const long long &y)
	{
		a=x;
		b=y;
	}
};
inline bool operator <= (const fraction &x,const fraction &y)
{
	return (long long)x.a*y.b<=(long long)y.a*x.b;//比较大小用乘法，同时避免使用 double。
}
inline bool operator < (const fraction2 &x,const fraction2 &y) 
{
	return (__int128)x.a*y.b<(__int128)y.a*x.b;
}
inline fraction2 operator - (const fraction &x,const fraction &y)
{
	return fraction2((long long)x.a*y.b-(long long)y.a*x.b,(long long)x.b*y.b);//没必要化简。 
}
fraction2 eps,eps2;
int n,ans;
inline int toint(const int &a,const int &b)//多加 inline。 
{
	long long ans=1;
    int i=1,y=M-2;
	for(long long j=b;y;i<<=1,j=j*j%M)
	{
		if(y&i)
		{
			y&=~i;
			ans=ans*j%M;
		}
	}
	return a*ans%M;
}
inline void update(fraction s,fraction l,fraction r)
{
	if(r-l<eps2) 
		return;
	int tx,ty;
	if(eps2<s-l)//为避免使用 __int128，这里可以这样写。等价于 l+eps<s-eps。 
		tx=toint((eps.b%M*s.a%M-eps.a%M*s.b%M+M)%M,eps.b%M*s.b%M);
	else
		tx=toint((eps.b%M*l.a%M+eps.a%M*l.b%M)%M,eps.b%M*l.b%M);
	if(r-s<eps2)//为避免使用 __int128，这里可以这样写。等价于 r-eps<s+eps。 
		ty=toint((eps.b%M*r.a%M-eps.a%M*r.b%M+M)%M,eps.b%M*r.b%M);
	else
		ty=toint((eps.b%M*s.a%M+eps.a%M*s.b%M)%M,eps.b%M*s.b%M);
	ans=((ans+ty-tx)%M+M)%M;
}
inline void query(fraction w)
{
	fraction l(0,1),r(1,1);
	fraction y,s;
	int t;
	for(;;)
	{
		t=0;
		s=r;
		while(++t)//很离谱的倍增比线性算法快。 
		{
			y=fraction(s.a+(l.a<<t),s.b+(l.b<<t));
			if(y.b<=n&&w<=y)
				s=y;
			else
				break;
		}
		while(t--)
		{
			y=fraction(s.a+(l.a<<t),s.b+(l.b<<t));
			if(y.b<=n&&w<=y)
				s=y;
		}
		if(s.b==n)
		{
			update(s,l,fraction(s.a-l.a,s.b-l.b));
			return;
		}
		r=s;
		
		t=0;
		s=l;
		while(++t)
		{
			y=fraction(s.a+(r.a<<t),s.b+(r.b<<t));
			if(y.b<=n&&y<=w)
				s=y;
			else
				break;
		}
		while(t--)
		{
			y=fraction(s.a+(r.a<<t),s.b+(r.b<<t));
			if(y.b<=n&&y<=w)
				s=y;
		}
		if(s.b==n)
		{
			update(s,fraction(s.a-r.a,s.b-r.b),r);
			return;
		}
		l=s;
	}
	return;
}
bool f[5000005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long a,b;
		scanf("%d%lld%lld",&n,&a,&b);
		eps=fraction2(a,b);
		eps2=fraction2(a<<1,b);
		if(n==1)
		{
			if(a*2>=b)
				printf("1\n");
			else
				printf("%d\n",(toint(a%M,b%M)<<1)%M); 
			continue;
		}
		ans=0;
		fraction ta(0,1),tb(1,1);
	    int n2=n>>1,nt=n,d=sqrt(n);
		for(int i=2;i<=d;i++)
		{
			if(nt%i)
				continue;
			for(int j=i;j<=n2;j+=i)
				f[j]=1;
			while(nt%i==0)
				nt/=i;
		}
		if(nt>1)
		{
			for(int j=nt;j<=n2;j+=nt)
				f[j]=1;
		}
		for(int i=1;i<=n2;i++)
		{
			if(!f[i])
				query(fraction(i,n));
		}
		if(n!=2)
			ans=(ans<<1)%M;
		printf("%d\n",ans);
		memset(f+1,0,n2);
	}
	return 0;
}
```

---

