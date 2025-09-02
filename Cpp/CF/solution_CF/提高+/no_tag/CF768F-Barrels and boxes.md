# Barrels and boxes

## 题目描述

Tarly has two different type of items, food boxes and wine barrels. There are $ f $ food boxes and $ w $ wine barrels. Tarly stores them in various stacks and each stack can consist of either food boxes or wine barrels but not both. The stacks are placed in a line such that no two stacks of food boxes are together and no two stacks of wine barrels are together.

The height of a stack is defined as the number of items in the stack. Two stacks are considered different if either their heights are different or one of them contains food and other contains wine.

Jon Snow doesn't like an arrangement if any stack of wine barrels has height less than or equal to $ h $ . What is the probability that Jon Snow will like the arrangement if all arrangement are equiprobably?

Two arrangement of stacks are considered different if exists such $ i $ , that $ i $ -th stack of one arrangement is different from the $ i $ -th stack of the other arrangement.

## 说明/提示

In the first example $ f=1 $ , $ w=1 $ and $ h=1 $ , there are only two possible arrangement of stacks and Jon Snow doesn't like any of them.

In the second example $ f=1 $ , $ w=2 $ and $ h=1 $ , there are three arrangements. Jon Snow likes the (1) and (3) arrangement. So the probabilty is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768F/c171d3ec3c02b9089b571e24a262c7ab1c15c85e.png).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768F/3e5447e34c48fd4c4bc2060eccebc67dc1ee4bf4.png)

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 2 1
```

### 输出

```
666666672
```

# 题解

## 作者：Patakou (赞：2)

比较基础的组合题。  

因为只有两种物品，所以容易将原问题转化为一个01序列。  
总方案数显然是$C_{w+f}^{w}$  

考虑枚举酒堆有几堆。  
设酒堆有$i$堆。  
那么将这$i$堆酒插入到食物中的方案数为$C_{f+1}^{i}$  
为每一堆酒先固定放上$h$箱酒。  
此时还剩$w-ih$箱酒。  
将剩下的酒安排在$i$个酒堆上(每一堆至少再分配一箱)。  
使用不能为0的插板法得出方案数为$C_{w-ih-1}^{i-1}$  

对于$w=0$需特判，这应该是特判最少的写法。  

## 代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=201000;
const int MOD=1000000007;
long long fac[N],inv[N];
inline long long pow(long long x,int y){
	long long ans=1;
	while(y){
		if(y&1)ans=ans*x%MOD;
		y>>=1;
		x=x*x%MOD;
	}
	return ans;
}
long long C(int n,int m){
	if(n<m)return 0;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
inline void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=fac[i-1]*i%MOD;
	inv[n]=pow(fac[n],MOD-2);
	for(int i=n-1;i>=0;--i)
		inv[i]=inv[i+1]*(i+1)%MOD;
}
int main(){
	int w,f,h,n;
	long long ans=0;
	scanf("%d%d%d",&f,&w,&h);
	n=w+f;
	if(w==0){printf("1\n");return 0;}
	init(n);
	for(int i=1;i*(h+1)<=w;++i)
		ans=(ans+C(f+1,i)*C(w-i*h-1,i-1))%MOD;
	printf("%lld\n",ans*pow(C(n,w),MOD-2)%MOD);
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：1)

一开始觉得是分拆数，后来发现是有序的分拆数，就变成插板法 sb 题了。

考虑本质上「堆」就是对总量的一个有序拆分。而这里不同的是总方案数要求不能存在某些位置放 $0$ 的情况。考虑如果可以放 $0$ 那么就是一个 $n$ 元线性不定方程组非负整数解的个数，这个地方要求 $k$ 个位置都 $\geq 1$ 的话，就只需要将等号右边的 $w/f$ 改成 $w-k$ 和 $f-k$ 即可。考虑合法方案数也是一样的道理，变成了 $w-h\cdot k$ 和 $f-h\cdot k$ 。

然后就可以考虑对每个堆数计数。发现对于一个数量 $n'$ 两者只会放 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 和 $\left\lceil\dfrac{n}{2}\right\rceil$ 的数量，随便算一下即可。

```cpp

int res ;
int ans ;
int inv[N] ;
int fac[N] ;

int expow(int a, int b){
    int ret = 1 ;
    while (b){
        if (b & 1)
            ret = (ll)ret * a % P ;
        a = (ll)a * a % P ; b >>= 1 ;
    }
    return ret ;
}
int binom(int x, int y){//\binom{x}{y}
    return (ll)fac[x] * inv[y] % P * inv[x - y] % P ;
}
void prework(int p, int q){
    fac[0] = inv[0] = 1 ; ans = res = 0 ;
    for (int i = 1 ; i <= p + q + 1 ; ++ i)
        fac[i] = 1ll * fac[i - 1] * i % P ;
    inv[p + q + 1] = expow(fac[p + q + 1], P - 2) ;
    for (int i = p + q ; i >= 1 ; -- i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % P ;
}

int p, q, h ;
int main(){
    cin >> q >> p >> h ;
    prework(p, q) ; int x, y, z ;
//    debug(fac, 1, p + q) ;
//    debug(inv, 1, p + q) ;
    if (p == 0)
		return cout << 1 << '\n', 0 ;
	if (q == 0){
		if (p > h) cout << 1 << '\n' ;
		else cout << 0 << '\n' ; return 0 ;
    }
    for (int i = 2 ; i <= p + q ; ++ i){
        x = ceil(1.0 * i / 2.0) ;
        y = floor(1.0 * i / 2.0) ; z = 0 ;
        if (x <= p && y <= q)
            add(z, 1ll * binom(p - 1, x - 1) % P * binom(q - 1, y - 1) % P) ;
        if (x <= q && y <= p)
            add(z, 1ll * binom(q - 1, x - 1) % P * binom(p - 1, y - 1) % P) ;
        add(ans, z) ; z = 0 ;
        if (1ll * x * h <= p && y <= q)
            add(z, 1ll * binom(p - x * h - 1, x - 1) % P * binom(q - 1, y - 1) % P) ;
        if (1ll * y * h <= p && x <= q)
            add(z, 1ll * binom(p - y * h - 1, y - 1) % P * binom(q - 1, x - 1) % P) ;
        add(res, z) ;
//        debug(res, ' ') ;
//        debug(ans) ;
    }
//        debug(res, ' ') ;
//        debug(ans) ;
    if (p + q <= 1) res = 1, ans = 1 ;
    cout << 1ll * res * expow(ans, P - 2) % P << '\n' ;
    return 0 ;
}

```

---

## 作者：mrclr (赞：0)

此题不难。

这种题做几道就知道些套路了：我们枚举酒有几堆，这样就能算出食物有多少堆以及他们的排列数，那么概率就是合法方案数 / 总方案数。

设酒有$i$堆，那么就有$C_{w - 1} ^ {i - 1}$种排列方法，对应的食物堆数就可能有$i - 1, i, i + 1$堆，然后同样用隔板法算出食物的排列方法，即$C_{f - 1} ^ {i - 2}, C_{f - 1} ^ {i - 1}, C_{f - 1} ^ {i}$。把这俩乘起来就是当酒堆数为$i$的总方案数。

至于合法方案数，就是我们先强制往每一堆酒上放$h$个，然后再往$i$堆酒上放$w - h * i$个，即$C_{w - h * i - 1} ^ {i - 1}$。

然后注意边界情况。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
#include<assert.h>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define In inline
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 1e5 + 5;
const ll mod = 1e9 + 7;
In ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
In void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}
In void MYFILE()
{
#ifndef mrclr
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif
}

int n, m, h;

ll fac[maxn], inv[maxn];
In ll inc(ll a, ll b) {return a + b < mod ? a + b : a + b - mod;}
In ll C(int n, int m)
{
  if(m < 0 || m > n) return 0;
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
In ll quickpow(ll a, ll b)
{
  ll ret = 1;
  for(; b; b >>= 1, a = a * a % mod)
    if(b & 1) ret = ret * a % mod;
  return ret;
}

In void init()
{
  fac[0] = inv[0] = 1;
  for(int i = 1; i < maxn; ++i) fac[i] = fac[i - 1] * i % mod;
  inv[maxn - 1] = quickpow(fac[maxn -  1], mod - 2);
  for(int i = maxn - 2; i; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int main()
{
  //MYFILE();
  m = read(), n = read(), h = read();
  if(!m) {puts(n > h ? "1" : "0"); return 0;}
  if(!n) {puts("1"); return 0;}
  init();
  ll ans1 = 0, ans2 = 0;
  for(int i = 1; i <= n; ++i)
    {
      ll tp1 = C(n - 1, i - 1);
      ll tp2 = inc(C(m - 1, i - 2), inc(C(m - 1, i - 1) * 2, C(m - 1, i)));
      if(1LL * n - 1LL * h * i >= i) ans2 = inc(ans2, C(n - h * i - 1, i - 1) * tp2 % mod);
      ans1 = inc(ans1, tp1 * tp2 % mod);
    }
  write(ans2 * quickpow(ans1, mod - 2) % mod), enter;
  return 0;
}
```

---

