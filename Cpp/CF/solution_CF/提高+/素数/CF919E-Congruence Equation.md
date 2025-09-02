# Congruence Equation

## 题目描述

Given an integer $ x $ . Your task is to find out how many positive integers $ n $ ( $ 1<=n<=x $ ) satisfy

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF919E/02717f82c41ef4ed609db5d967f659c9784212e1.png) where $ a,b,p $ are all known constants.

## 说明/提示

In the first sample, we can see that $ n=2 $ and $ n=8 $ are possible answers.

## 样例 #1

### 输入

```
2 3 5 8
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 6 7 13
```

### 输出

```
1
```

## 样例 #3

### 输入

```
233 233 10007 1
```

### 输出

```
1
```

# 题解

## 作者：Acc_Robin (赞：9)

一道考察对同余系理解的[题](https://www.luogu.com.cn/problem/CF919E).

题意：

给定 $a,b,p,x$ ，其中 $p\le 1\times 10^6+3$，求使得

$$
na^n\equiv b\pmod p
$$

成立的 $1\le n\le x$ 的个数。

**解**

首先我们有一个 naive 的想法，显然式子左边这个东西是有循环节的。

由 Fermat小定理 可知，指数上的循环节是 $p-1$ ，结合系数，可知总体循环节为 $p(p-1)$。

目前我们看不出这个循环节有什么作用，但注意到 $p$ 很小，我们继续探究指数上的猫腻：

可以用 $n$ 对 $p-1$ 作带余除法，令

$$
n=k(p-1)+r~(0\le r<p-1)
$$

则原式化为

$$
[k(p-1)+r]a^{k(p-1)+r}\equiv b\pmod p
$$

由 Fermat小定理，原式化为

$$
[(kp-k+r)\bmod p]a^{(k(p-1)+r)\bmod p}\equiv (r-k)a^r
\equiv b\pmod p
$$

移项得

$$
(r-k)\equiv ba^{-r}\pmod p
$$

观察这个式子，因为 $0\le r <p-1$，所以可以枚举每一个 $r$，带入算出 $k$ ，进而算出当前的 $n$。

现在的问题是：如何统计答案？

这就要用到一开始的循环节 $p(p-1)$，我们算出一个特解 $n_* $ ，然后计算可能有多少个满足条件的 $n$ ，稍加思考则知 $n$ 的个数为

$$
\lfloor \frac {x-n_* }{p(p-1)}\rfloor+1
$$

注意:如果发现当前的 $n>x$ 则跳过。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace HMFS{
#define int long long
	int a,b,p,x,ans;
	int qpow(int a,int b=p-2){
		int res=1;
		for(;b;b>>=1,a=a*a%p)if(b&1)res=res*a%p;
		return res;
	}
	void work(){
		cin>>a>>b>>p>>x;
		for(int r=0,f,k,now;r<p-1;r++){
			f=b*qpow(qpow(a,r))%p;
			k=(r-f+p)%p;
			if((now=k*(p-1)+r)>x)continue;
			ans+=(x-now)/(p*(p-1))+1;
		}
		cout<<ans;
	}		
#undef int
}
int main(){
	return HMFS::work(),0;
}
```

总复杂度即枚举 $r$ 和快速幂，即 $O(p\log p)$.

---

## 作者：interestingLSY (赞：7)

# CF919E Congruence Equation 题解

先说一句话:

请诸位大佬饶恕我的语言表达能力。。。。

## 看一眼

乍一看数据范围, $x \leq 10^{12}$ , 大的可~~啪~~

然而 $p \leq 10^6+3$, 说明也许可以在 $p$ 上开刀,利用周期性等奇怪性质搞事情

## 再看一眼

我看到了mod

可以发现:

因为p为质数,所以

- $n ≡ n+p{\color{Blue}{\pmod{p}}}$
- ${a^n} ≡ {a^{n+p-1}}{\color{Blue}{\pmod{p}}}$  可用费马小定理证明

↑说真的我也不知道上面的该怎样表达qwqwqwq。。。

反正意思就是在%p的意义下$n=n+p$ , ${\ a^n}=a^{\ n+p-1}$

因此,我们可以**利用n的周期性**通过这样一种方法:

只要枚举所有 $a^n\ mod\ p \ ( 1 \leq n < p\ )$ ， 并分别统计答案就行 

顺便提一句:蓝色的不是超链接awa

## 问题来了。。。

怎么统计答案？

请注意:并不是对于所有 $a^n\ mod\ p \ ( 1 \leq n < p\ )$ ,答案都存在。

假设我们现在枚举的$a^n$中的n为 $i$ , 此时满足 $n \times a^n\ mod\ p\ = \ b$ 的n为 $j$

那么一定会有

$ j ≡ i {\color{Blue}{\pmod{p-1}}}$

$ j ≡ b \times Inv\ (a^{\ i}\ ) {\color{Blue}{\pmod{p}}} \quad$其中  $Inv\ (a^{\ i}\ )$表 $a^{\ i}$ 在 $mod\ p$ 意义下的逆元

提示:第二个式子是用 $j \times a^{\ i}\ mod\ p\ = \ b$ 导出的。

接下来么...解一下这个方程组就OK

## 代码

为了方便大家~~直接复制粘贴~~看代码，这里只放出关键部分

```cpp
ll a,b,p;
ll x;
il ll Qpow( ll a , ll b ){
	a %= p;
	ll ret = 1LL;
	while(b){
		if(b&1){
			ret *= a;
			ret %= p;
		}
		a *= a;
		a %= p;
		b >>= 1LL;
	}
	return ret % p;
}
il ll Inv( ll x ){
	return Qpow(x,p-2) % p;
}

ll Mod( ll x , ll mod ){
	return ((x%mod)+mod)%mod;
}

ll ans = 0LL;
// 解方程
ll Cal( int n , int power ){
	ll now = b * Inv(power) % p;
	ll correctn = (p-1)*Mod(n-now,p) + n;
	if( correctn > x ) return 0LL;
	return (x-correctn) / (p*(p-1)) + 1;
}

int main(){
	cin >> a >> b >> p >> x;

	ll power = 1;
	For(n,p-1){
		power = power * a % p;
		ll tans = Cal(n,power);
		ans += tans;
	}

	cout << ans << endl;

	return 0;
}
```

新的配色挺好看

## 觉得我在瞎说？说的不对？方法不够简洁？看不懂？或者觉得我长得太丑？请在评论区提出qwq。

---

## 作者：XenonKnight (赞：3)

> 题意：给出 $a,b,p,x$，求有多少个 $n$ 满足：
> - $1 \leq n \leq x$
> - $n \times a^n \equiv b \pmod{p}$

> $1 \leq p \leq 10^6+3$，$1 \leq x \leq 10^{12}$，$p$ 为质数。

标签：逆元+费马小定理

分析一下数据范围，$x$ 很大，但是 $p$ 很小，所以我们可以从 $p$ 下手。

看到 “$p$ 为质数” 这个条件，可以想到费马小定理。

虽然这个 $n$ 的取值可以达到 $10^{12}$，不过我们可以将它拆成 $s \times (p-1)+t$，这样 $n \times a^n \equiv b \pmod{p}$ 就可以化为：

$$(s \times (p-1)+t) \times a^{s \times (p-1)+t} \equiv b \pmod{p}$$

把 $a^{s \times (p-1)+t}$ 展开：

$$(s \times (p-1)+t) \times a^{t} \times (a^{p-1})^{s} \equiv b \pmod{p}$$

根据费马小定理，$a^p=1$，柿子又可以化成：

$$(s \times (p-1)+t) \times a^{t} \equiv b \pmod{p}$$

把同余符号展开：

$$(s \times (p-1)+t) \times a^{t} = b+m \times p$$

我们固定住 $t$，将 $s$ 用 $t$ 和 $m$ 表示出来：

$$s \times (p-1)+t=\frac{b+m \times p}{a^t}$$
$$s \times (p-1)=\frac{b+m \times p-t \times a^t}{a^t}$$
$$s=\frac{b+m \times p-t \times a^t}{a^t \times (p-1)}$$
$$s=\frac{b-t \times a^t}{a^t \times (p-1)}+m \times p \times \frac{1}{a^t \times (p-1)}$$
由于 $a^t \times (p-1)$ 是一个定值并且与 $p$ 互质，令 $z=m \times (a^t \times (p-1))^{-1} \pmod{p}$。

很显然，对于一个 $z$，有且仅有一个 $m$ 与之对应，柿子又变为：

$$s=\frac{b-t \times a^t}{a^t \times (p-1)}+z \times p$$

枚举 $t$，现在我们就要求出这个 $z$ 的取值范围。

关于最小值，很显然 $z$ 必须 $\geq 0$

关于最大值，因为 $n \leq x$，所以 $s \times (p-1)+t \leq x$

求出区间的长度累加进答案就可以了。

```cpp
int a=read(),b=read(),p=read(),x=read(),ans=0;
signed main(){
	for(int i=1;i<=p-1;i++){
		int t=qpow(qpow(a,p-2,p),i,p);
		t=t*b%p;
		t=(t-i+p)%p;
		t=t*qpow(p-1,p-2,p)%p;
		int k=x/p*p;
		if(t*(p-1)+i>x)	continue;
		ans+=((x-i)/(p-1)-t)/p+1;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：2)

数论蒟蒻又要水题解了……
### 题意
给定正整数 $a$，$b$，$x$ 和素数 $p$，你要求出有多少个正整数 $1 \leq n \leq x$ 满足:
$$na^n\equiv b \pmod p$$
### 分析
因为 $p$ 是素数，所以根据费马小定理，有：
$$na^n\equiv na^{n \bmod (p-1)}\pmod p$$
观察到 $p$ 的范围较小，这时 $a$ 的指数种类数只有 $10^6$ 级别，线性求出 $a$ 的幂次，现在对于一种幂次 $i$，我们考虑 $n$ 需要满足什么条件：
$$n\equiv i \pmod {p-1}$$
以及
$$na^i\equiv b \pmod p$$
把第二个式子的 $a^i$ 除过去，可以得到同余方程组：
$$\begin{cases}
n\equiv i \pmod {p-1}\\ 
n\equiv \frac b{a^i} \pmod p 
\end{cases}$$
显然 $p-1$ 和 $p$ 互质，可以使用中国剩余定理求出最小解，然后判断值域范围内有几个解。
### 代码
```cpp
int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int g=exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-(a/b)*y;
	return g;
}
signed main(){
	cin.tie(0),cout.tie(0);
	a=read(),b=read(),p=read(),X=read();
	r[p-2]=a;
	for(int i=p-3;i>=0;i--) r[i]=r[i+1]*a%p;
	for(int i=p-2;i>=0;i--) r[i]=r[i]*b%p;
	for(int i=0;i<=p-2;i++){
		int x=0,y=0,M=p*(p-1),ans=0;
		exgcd(p,p-1,x,y);
		ans=(ans+i*p*(x<0?x+p-1:x))%M;
		x=0,y=0;
		exgcd(p-1,p,x,y);
		ans=(ans+r[i]*(p-1)*(x<0?x+p:x))%M;
		if(ans>X) continue;
		cnt+=(X-ans)/M+1;
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：mydcwfy (赞：1)

## 1. 题意

求
$$
n\cdot a^n\equiv b\pmod p
$$
在 $[1,x]$ 的正整数解的个数，其中 $a,b,p,x$ 给定。

$p\leq10^6+3,x\leq10^{12},1\leq a,b<p$。

## 2. 思路

首先，看到 $p\leq10^6+3$，一定是要 $O(p)$ 枚举，然后再做。

#### a）枚举 $n$

那么，原题转化为了 $t\cdot a^n\equiv b\pmod p$ 的解了。

很明显是一个 BSGS，时间复杂度为 $O(\sqrt p)$ 或 $O(\sqrt p\log \sqrt p)$，取决于 map 还是 Hash。

但是，总时间为 $O(p\sqrt p)$，很明显无法通过。

#### b）枚举 $a^n$

首先，我们考虑 $a^n$ 的取值有多少种。

由于 $a^{p-1}\equiv 1\pmod p$，所以循环节一定是 $p-1$，那么我们就可以枚举 $n\bmod (p-1)$，得到所有的 $a^n$ 的取值。

那么，原题就是 $n\cdot t\equiv b\pmod p$ 的解。

咦，这不就是一个逆元了吗？

于是，我们可以 $O(\log p)$ 求出逆元（因为一定有），那么，我们就可以求出 $n\bmod p$ 的值。

#### c）合并答案

这道题在 CF 上有中国剩余定理的标签，大概就是这里用的吧。

我们已经得到了 $t1=n\bmod (p-1)$ 和 $t2=n\bmod p$ 的值，直接由中国剩余定理就可以了。

其实手玩也不是不可以，直接设 $n=kp+t2$，代入第一个就可以得到：
$$
\begin{aligned}
kp+t2&\equiv t1 \pmod {p-1}\\
k+t2&\equiv t1\pmod {p-1}\\
k&\equiv t2-t1\pmod {p-1}
\end{aligned}
$$
就解出了 $n$ 的最小正整数取值了。

周期~~很明显~~是 $p\cdot(p-1)$，将答案加入即可。

## 3. 代码

实际实现的时候可以预处理算出 $a$ 的逆元，每次枚举 ${a^t}$ 的逆元的时候可以通过 ${a^{t-1}}^{-1}$ 乘上 $a^{-1}$ 即可。

码风略丑，请见谅。

```cpp
int main()
{
	cin >> a >> b >> Mod >> x;
	ll now = b, inv = qpow(a, Mod - 2), lim = Mod * (Mod - 1), ans = 0;
	for (ll modp1 = 0; modp1 < Mod - 1; ++ modp1, now = now * inv % Mod)
	{//modp1 是枚举的 t，now 就是上面的 b 乘以（ a 的 t 次方的逆元），也就是 t1
		ll mx = (modp1 - now + (Mod - 1)) % (Mod - 1) * Mod + now;//mx 是 n 的最小取值
		mx = (mx % lim + lim) % lim;//lim 是 Mod * Mod - 1，是 n 的周期
		if (mx <= x) ans += (x - mx + lim) / lim;
	}
	cout << ans << endl;
	return 0;
}
```



---

## 作者：Chen_Johnny (赞：0)

# CF919E Congruence Equation 题解
纯数学推导，很恶心的一道题。
## 题目大意
这个题目翻译一言难尽，所以我现在总结一下题目的大意。

现在要求所有 $n$ 满足两个条件：

- $1\leqslant n \leqslant x$。
- $n \times a^n \equiv b \pmod p$。
## 数学推导
首先，我们设：$n = k (p - 1) + r(0\leqslant r < p-1)$。

代入原式得：$[k(p-1)+r]\times a ^ {[k (p - 1) + r]}\equiv b \pmod p$。

即：$[(kp-k+r)\bmod p]\times [a ^ {(p - 1)}\bmod p]^k \times a^r \equiv b \pmod p$。

因为 $p$ 为素数，所以由费马小定理：$a ^ {(p - 1)}\equiv 1\pmod p$。

$\therefore (r-k)\times a^r \equiv b \pmod p$。

$\therefore (r-k) \equiv b \times a^{-r} \pmod p$。

## 程序求解
$\because 0\leqslant r < p-1$ $\therefore$ 尝试枚举 $r$ 并代入上式可以求出 $k$ 的可能值，从而求出 $n$。

但是问题来了，如何求出解得的个数，其实很简单。我们先假设 $(r-k) = b \times a^{-r} \pmod p$ 并求出一个特解 $n^{*}$。显然，因为 $n$ 有一个 $p(p-1)$ 的循环节，所以最终的解的个数为：$\lfloor \frac {x-n^{*}}{p(p-1)}\rfloor + 1$。

注意：这里需要使用快速幂。
## 代码
```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a, b, mod, x, ans;
ll qpow (ll a, ll b) {
    ll ans = 1;
    while (b) {
        if(b % 2 == 1) ans = ans * a % mod;
        b >>= 1; a = a * a % mod;
    }
    return ans % mod;
}
int main()
{
    cin >> a >> b >> mod >> x;
    for (int r = 0, f, k, now; r < mod - 1; r ++) {
        f = b * qpow (qpow (a, r), mod - 2) % mod;
        k = (r - f + mod) % mod;
        if ((now = k * (mod - 1) + r) > x) continue;
        ans += (x - now) / (mod * (mod - 1)) + 1;
    }
    cout << ans;
}
```

---

## 作者：Yuno (赞：0)

观察到 $p$ 的范围较小，而 $a^n$ 这玩意 $\bmod\ p$ 肯定有循环节

这就启发我们对于循环节中的每个数统计答案

由于 $p$ 是质数，题面中的式子可以这么改写：

$n\equiv b\times (a^n)^{-1}\pmod p$

设循环节长度为 $q$，$x\equiv b\times (a^n)^{-1}\pmod p$，

那么对于循环节中的第 $y$ 个数，它的答案就是满足

$w\equiv x\pmod p$

$w\equiv y\pmod q$

且 $w$ 在题目要求的范围内的 $w$ 的个数

这玩意一看就是个 CRT，随便搞搞就好了

参考实现:

Code:

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 4e6 + 7;
int a, b, p, lim;
int cnt, c[ N ], vis[ N ];
inline int qp( int b, int po ) {
	int ret = 1;
	while ( po ) {
		if ( po & 1 ) ret = ret * b % p;
		po >>= 1;
		b = b * b % p;
	}
	return ret;
}
inline void exgcd( int a, int b, int &x, int &y ) {
	if ( b == 0 ) { x = 1, y = 0; return; }
	exgcd( b, a % b, x, y );
	int z = x;
	x = y;
	y = z - ( a / b ) * y;
}
signed main( ) {
	std::ios::sync_with_stdio( 0 );
	std::cin >> a >> b >> p >> lim; 
	int now = 1, where = 0;
	for ( int i = 1; ; ++ i ) {
		now = now * a % p;
		if ( vis[ now ] ) {
			where = vis[ now ];
			break;
		}
		vis[ now ] = i;
		c[ ++ cnt ] = now;
	}
	int ans = 0;
	for ( int i = 1; i < where; ++ i ) {
		if ( i > lim ) break;
		if ( i % p == b * qp( c[ i ], p - 2 ) % p ) ++ ans;
	}
	int q = cnt - where + 1, M = p * q;
	int al = qp( q, p - 2 ), be, y;
	exgcd( p, q, be, y );
	for ( int y = where; y <= cnt; ++ y ) {
		int x = b * qp( c[ y ], p - 2 ) % p;
		int sol = ( x * q % M * al % M + y * p % M * be % M ) % M;
		ans = ans + ( lim / M ) + ( lim % M >= sol );
	}
//	puts( "" );
	printf( "%lld\n", ans );
	return 0;
}
```


---

