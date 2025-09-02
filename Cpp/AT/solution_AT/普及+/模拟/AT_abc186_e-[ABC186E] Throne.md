# [ABC186E] Throne

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc186/tasks/abc186_e

円周上に $ N $ 個の椅子が並べられています。そのうち $ 1 $ つは玉座です。

高橋君は最初、玉座から時計回りに数えて $ S $ 個隣の椅子に座っており、次の行動を繰り返します。

行動：いま座っている椅子から時計回りに数えて $ K $ 個隣の椅子に移動し座る。

高橋君がはじめて玉座に座ることができるのは何回目の行動の後ですか？ ただし、玉座に座ることが永遠にできない場合は、代わりに `-1` を出力してください。

$ T $ 個のテストケースに答えてください。

## 说明/提示

### 制約

- $ 1\leq\ T\ \leq\ 100 $
- $ 2\leq\ N\ \leq\ 10^9 $
- $ 1\leq\ S\ <\ N $
- $ 1\leq\ K\ \leq\ 10^9 $

### Sample Explanation 1

$ 1 $ つ目のテストケースでは、椅子が $ 10 $ 個あり、高橋君は最初、玉座から時計回りに数えて $ 4 $ 個隣の席に座っています。 時計回りに $ 3 $ 個隣の席に移動する行動を $ 2 $ 回行うと玉座に座れます。 $ 2 $ つ目のテストケースでは、高橋君が玉座に座ることは永遠にできないので、`-1` を出力します。

## 样例 #1

### 输入

```
4
10 4 3
1000 11 2
998244353 897581057 595591169
10000 6 14```

### 输出

```
2
-1
249561088
3571```

# 题解

## 作者：cjh20090318 (赞：2)

[同余方程](https://www.luogu.com.cn/problem/P1082)板子题，没过的可以先去看看。

## 题意

翻译给的很清楚。

## 分析

看到这个转圈圈的就很容易想到同余方程。

为了方便处理，我们就将编号全部减 $1$，于是编号就变成 $0 \sim N-1$。

然后就可以很容易的列出同余方程：

$$
S + Kx \equiv 0\pmod{N}
$$

移项可得：

$$
Kx \equiv -S \pmod{N}
$$

将右边加上 $N$ 使得右边非负：

$$
Kx \equiv N-S \pmod{N}
$$

然后直接求解 $x$ 即可。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
using namespace std;
typedef long long LL;
LL x,y;
LL exgcd(const LL&a,const LL&b){//扩展欧几里得求解同余方程。
	if(!b){
		x=1,y=0;
		return a;
	}
	LL d=exgcd(b,a%b);
	LL z=x;
	x=y;
	y=z-y*(a/b);
	return d;
}
int mian(){
	LL a,b,s;//a 指的是 K，b 指的是 N。
	scanf("%lld%lld%lld",&b,&s,&a);
	LL g=exgcd(a,b),t=(b-s)%b;
	if(t%g) puts("-1");//判断无解的情况。
	else printf("%lld\n",(x%b+b)%b*(t/g)%(b/g));
	return 0;
}
int main(){
	int T;scanf("%d",&T);
	while(T--) mian();
	return 0;
}
```

---

## 作者：__Cby___ (赞：1)

## 思路
围成一圈，很容易想到同余方程。  
我们设经过 $x$ 次操作后能够到达编号为 $1$ 的椅子，易得：  
$$xk+s+1\equiv1\pmod {n}$$  
同时减去 $s+1$，得：  
$$xk\equiv n-s\pmod{n}$$  
然后这个东西就可以用逆元求解了。   
注意到我们首先应当把 $n,k,s$ 约分。约分后若 $\gcd(n,k)\neq1$ 显然无解。  
## 代码
```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long int fp(long long int a, long long int b, long long int p) {
	a %= p;
	long long int ans = 1;
	while (b) {
		if (b & 1) {
			ans *= a;
			ans %= p;
		}
		a *= a;
		a %= p;
		b >>= 1;
	}
	return ans;
}
long long int phi(long long int n) {
	long long int ans = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans = ans / i * (i - 1);
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1)ans = ans / n * (n - 1);
	return ans;
}
long long int gcd(long long int a, long long int b) {
	while (a ^= b ^= a ^= b %= a);
	return b;
}
int main() {
	int T;
	cin >> T;
	while (T--) {
		long long int n, s, k;
		cin >> n >> s >> k;
		int t = gcd(n, gcd(s, k));
		n /= t;
		s /= t;
		k /= t;
		if (gcd(n, k) != 1) {
			cout << -1 << '\n';
			continue;
		}
		cout << (n - s) * fp(k, phi(n) - 1, n) % n << '\n';
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

在不压行的前提下抢到了最优解？

不难发现首先可以把三个数同时约分，约分后如果 $ \gcd(n,k) $ 不等于 $ 1 $ 则显然无解。

否则问题转化为求 $ s+xk \equiv 0 (\bmod n) $ 的最小正整数解，也就是 $ xk \equiv n-s (\bmod n) $。这样就转化为了乘法逆元的形式。

如果不知道乘法逆元，请左转 [板子题](https://www.luogu.com.cn/problem/P3811) 和 [P1082](https://www.luogu.com.cn/problem/P1082)。

因为已经保证互质的条件，直接算出逆元即可。

这里偷懒用了 atcoder 自带的逆元库实现。

时间复杂度 $ \mathcal{O}(T\log{n}) $，可以通过。

代码：

```cpp
#import<atcoder/all>
using namespace std;
int t,n,s,k,g;
int main()
{
	cin>>t;
	while(t--)
    {
        cin>>n>>s>>k;
		g=gcd(n,gcd(s,k));
		n/=g,s/=g,k/=g;
		cout<<(gcd(n,k)!=1?-1:(atcoder::inv_mod(k,n)*(n-s))%n)<<'\n';
	}
}
```


---

## 作者：CodingOIer (赞：0)

## [ABC186E] Throne 题解

### 思路分析

显然，题目让我们寻找一个最小的 $c$，使得：$((n - s) + ck) \bmod n = 0$。

令 $a = n - s$，则 $a + ck \equiv 0 \pmod{n}$。

同余方程板子。

我选用逆元或扩展欧几里得法求解即可。

详见 OI-wiki：<https://oi-wiki.org/math/number-theory/inverse>。

### 代码实现

```cpp
#include <cstdio>
long long n, s, k;
long long gcd(long long x, long long y)
{
    for (;;)
    {
        if (x == 0 || x == y)
        {
            return y;
        }
        else if (y == 0)
        {
            return x;
        }
        else if (x > y)
        {
            x %= y;
        }
        else if (y > x)
        {
            y %= x;
        }
    }
}
void exGcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return;
    }
    exGcd(b, a % b, y, x);
    y -= a / b * x;
}
inline void solve()
{
    scanf("%lld%lld%lld", &n, &s, &k);
    s = n - s;
    long long g = gcd(k, n);
    if (s % g != 0)
    {
        printf("-1\n");
        return;
    }
    n /= g;
    s /= g;
    k /= g;
    long long x, y;
    exGcd(k, n, x, y);
    x = x < 0 ? x + n : x;
    printf("%lld\n", s * x % n);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

明显我们需要找到一个最小的 $x$，满足：

$$s+xk \equiv 0 \pmod n$$

将 $s$ 移项过去：

$$xk \equiv  n- s \pmod n$$

然后左右两边同时乘上一个 $k^{-1}$，得：

$$x \equiv k^{-1} (n-s) \pmod n$$

因为 $n$ 不一定是质数，故不能使用费马小定理求解逆元，需要使用扩展欧几里得算法。

若没有逆元，即 $\gcd(k,n) \ne 1$ 时，则无解。

时间复杂度为 $O(T \log n)$。

**注意要先同除一个 $n,s,k$ 的最大公因数。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,s,k,t,ans;
void exgcd(ll a,ll b,ll &x,ll &y) {
    if(!b){
    	x=1;
		y=0;
		return ;
	}
    exgcd(b,a%b,y,x);
	y-=a/b*x;
}
ll inv(ll a,ll mod){
	ll x,y;
	exgcd(a,mod,x,y);
	x=(x%mod+mod)%mod;
	return x;
}
void solve(){
	n=read(),s=read(),k=read();
	t=__gcd(n,__gcd(s,k));
	n/=t,s/=t,k/=t;
	if(__gcd(n,k)!=1){
		puts("-1");
		return ;
	}
	write((n-s)*inv(k,n)%n);
	putchar('\n');
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

一道推式子题，恶心（最讨厌数学题了）。     
我们使用小学生都会的做法，设经过 $x$ 次移动后能到达编号为 $1$ 的椅子，可得出 $s+1+xk$ 被 $n$ 取模的余数是 $1$。    
即 $n \mathrel{|} (s+xk)$。     
设 $(s+xk) \div n=y$，则 $s+xk=yn$。     
由于 $s,x,n$ 都已知，相当于常数，这个方程变为一个我们熟悉的二元一次方程，而我们的任务相当于解这个不定方程，使得 $x$ 为正整数且最小。   
解不定方程，大家会想到什么？扩展欧几里得啊！    
于是这道题就被完美解决了。    
代码很丑，千万别参考。    
```cpp
#include<stdio.h>
long long t,n,s,k;
long long gcd(long long x,long long y){while(y){long long r=x%y;x=y,y=r;}return x;}
void fc(long long a,long long b,long long &x,long long &y)
{
	if(!b) {x=1,y=0;return;}
	fc(b,a%b,y,x),y-=a/b*x;
}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&n,&s,&k);
        long long a=k,b=-n,c=-s,num=gcd(a,b);
        if(c%num!=0) {printf("-1\n");continue;}
        long long x,y;
        fc(a,b,x,y),x*=c/num,y*=c/num;
        if(b/num>0) printf("%lld\n",(x+b/num)%(b/num));
        else printf("%lld\n",-((b/num)-(x+b/num)%(b/num)));
    }
}
```

---

