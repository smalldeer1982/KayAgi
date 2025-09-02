# Visit of the Great

## 题目描述

The Great Mushroom King descended to the dwarves, but not everyone managed to see him. Only the few chosen ones could see the King.

We know that only $ LCM(k^{2^l}+1,k^{2^{l+1}}+1,...,k^{2^r}+1) $ dwarves can see the Great Mushroom King. Numbers $ k $ , $ l $ , $ r $ are chosen by the Great Mushroom King himself in some complicated manner which is unclear to common dwarves.

The dwarven historians decided to document all visits of the Great Mushroom King. For each visit the dwarven historians know three integers $ k_{i} $ , $ l_{i} $ , $ r_{i} $ , chosen by the Great Mushroom King for this visit. They also know a prime number $ p_{i} $ . Help them to count the remainder of dividing the number of dwarves who can see the King, by number $ p_{i} $ , for each visit.

## 说明/提示

We consider that $ LCM(a_{1},a_{2},...,a_{n}) $ represents the least common multiple of numbers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ .

We consider that $ x^{0}=1 $ , for any $ x $ .

## 样例 #1

### 输入

```
2
3 1 10 2
5 0 4 3
```

### 输出

```
0
0
```

# 题解

## 作者：whiteqwq (赞：6)

[CF185D Visit of the Great](https://www.luogu.com.cn/problem/CF185D)解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15237270.html)

## 题意

$T$ 组询问，每次给定 $k,l,r,p$，求 $\text{lcm}(k^{2^l}+1,k^{2^{l+1}}+1,\cdots,k^{2^r}+1)\bmod p$。

$1\leqslant T\leqslant 10^5,1\leqslant k\leqslant 10^6,0\leqslant l\leqslant r\leqslant 10^{18},2\leqslant p\leqslant 10^9$，保证 $p$ 是质数。

## 分析

小清新数论题。

我们简单猜个结论，任意两个数的 $\gcd$ 都不会很大。取任意两个位置 $a,b(a<b)$，设 $\gcd(k^{2^a}+1,k^{2^b}+1)=d$：

$$k^{2^a}\equiv k^{2^b}\equiv -1\pmod d\\1\equiv(-1)^{2^{b-a}}\equiv (k^{2^{a}})^{2^{b-a}}\equiv k^{2^b}\equiv -1\pmod d$$

于是 $d=1$ 或 $2$，且 $d=2$ 当且仅当 $k$ 为奇数。

设 $t=\prod_{i=l}^r(k^{2^t}+1)$，那么答案就是：

$$\begin{cases}\frac{t}{2^{r-l}}&k\equiv1\pmod 2\\t&k\equiv 0\pmod 2\end{cases}$$

那么我们转求 $t$ 的值，考虑直接推式子：

$$(k^{2^l}+1)((k^{2^l})^2+1)((k^{2^l})^4+1)\cdots((k^{2^l})^{2^{r-l}}+1)\\=\sum_{p=0}^{2^{r-l+1}-1}(k^{2^l})^p=\frac{(k^{2^l})^{2^{r-l+1}}-1}{k^{2^l}-1}=\frac{k^{2^{r+1}}-1}{k^{2^l}-1}$$

然后直接算就好了，注意特判 $k^{2^l}\equiv 1\pmod p$ 的情况，此时上式的值为：

$$(1+1)(1^2+1)(1^4+1)\cdots(1^{2^{r-l}}+1)=2^{r-l+1}$$

## 代码

```
#include<stdio.h>
int T,k,p;
long long l,r;
int ksm(int a,long long b,int mod){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
int f(long long x){
	return k%p==0? 0:ksm(k,ksm(2,x,p-1),p);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%lld%d",&k,&l,&r,&p);
		if(p==2)
			printf("%d\n",(k&1)^1);
		else{
			int ans=(f(l)==1? ksm(2,r-l+1,p):(1ll*(f(r+1)-1+p)%p*ksm((f(l)-1+p)%p,p-2,p)%p));
			if(k&1)
				ans=1ll*ans*ksm(ksm(2,r-l,p),p-2,p)%p;
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：diqiuyi (赞：2)

首先考虑我们要求的到底是什么。

设 $x=k^{2^l}$，考虑 $\gcd(x^{2^y}+1,(x+1)(x^2+1)(x^4+1)\cdots (x^{2^{y-1}}+1))$ 的结果。

注意到对于后面的这个式子实际上是一个指数的二进制表示，任意的 $x^i$ 都会出现恰好一次。所以后面那个东西就是 $\sum_{i=0}^{2^y-1} x^i=\frac{x^{2^y}-1}{x-1}$。

所以 $\gcd(x^{2^y}+1,(x+1)(x^2+1)(x^4+1)\cdots (x^{2^{y-1}}+1)=\gcd(x^{2^y}+1,\frac{x^{2^y}-1}{x-1})\mid\gcd(x^{2^y}+1,x^{2^y}-1)=\gcd(x^{2^y}+1,2)$。

所以当 $k$ 为偶数时，其值为 $1$，否则为 $2$。

接下来我们只要计算 $\prod_{i=l}^{r}(k^{2^i}+1)$ 的值。仿照上面的过程，我们得到它的值为 $\frac{x^{2^{r-l+1}}-1}{x-1}$，然后把它除以前面那个东西就行了。

**code**
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int t,k,p,res;
ll l,r;
int Pow(int x,ll y,int mod){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%mod)
		if(y&1)
			res=1ll*res*x%mod;
	return res;
}
int solve(int k,ll l,ll r,int p){
	k%=p;
	if(!k) return 1;
	k=Pow(k,Pow(2,l,p-1),p);
	if(k==1) return Pow(2,r-l+1,p);
	return 1ll*(Pow(k,Pow(2,r-l+1,p-1),p)-1)*Pow(k-1,p-2,p)%p;
}
int main(){
	io;
	cin>>t;
	while(t--){
		cin>>k>>l>>r>>p;
		if(k&1) res=Pow(Pow(2,r-l,p),p-2,p);
		else res=1;
		res=1ll*res*solve(k,l,r,p)%p;
		cout<<res<<'\n';
	}
    return 0;
}
/*
这组数据可用于调试
3
2 6 10 3
2 4 9 2
1 2 4 3

2
1
2
*/
```

---

## 作者：zhylj (赞：1)

**引理 1**：若 $k,x,y,d\in \mathbb N,x\neq y$，满足 $d\mid \left(k^{2^{x}}+1\right),d\mid \left(k^{2^y}+1\right)$，则 $d = 1$ 或 $2$.

**证明**：不妨设 $x<y$，则：

$$
\begin{aligned}
& k^{2^x}\equiv k^{2^y}\equiv - 1\pmod d\\
\Rightarrow & \left(k^{2^x}\right)^{2^{y-x}}\equiv (-1)^{2^{y-x}}\equiv 1 \equiv - 1 \pmod d
\end{aligned}
$$

所以有 $d = 1$ 或 $2$.

**引理 2**：若 $k,x,t\in \mathbb N$，$x\neq 0$，满足 $2^t\mid \left(k^{2^x} + 1\right)$，则 $t = 0$ 或 $1$.

**证明**：即证 $4\nmid \left(k^{2^x}+1\right)$，即 $\left(k^{2^{x-1}}\right)^2\equiv -1\pmod 4$，显然任何完全平方数模 $4$ 得 $0$ 或 $1$，所以不可能。

于是答案可以变为给出的数乘积的形式，然后除掉一个二的若干次幂。

再容易发现给出的数乘积相当于枚举指数上的数二进制下的每个位是否为 $1$，于是实际上是一个等比数列，然后答案就很好求了。

时间复杂度 $\mathcal O(t\log p)$.

[代码](https://codeforces.com/contest/185/submission/123078400)

---

## 作者：lilong (赞：0)

大胆猜测，所有数的最大公约数一定很小：偶数时为 $1$，奇数时为 $2$。设两个正整数 $n,m$ 且 $n<m$，最大公约数 $\gcd(k^{2^n}+1,k^{2^m}+1)=d$，则有 $k^{2^n}\equiv k^{2^m} \equiv -1\pmod d,k^{2^{n+1}} \equiv (k^{2^{n+1}})^{\frac{2^m}{2^{n+1}}} \equiv k^{2^m} \equiv 1 \pmod d$，故 $-1 \equiv 1 \pmod d$，即 $d$ 只能为 $1$ 或 $2$，当且仅当 $k=1$ 时 $d=2$。

现在要求 $(k^{2^l}+1)(k^{2^{l+1}}+1)\cdots(k^{2^r}+1)$。这个式子的意义可以理解为二进制上每一位选或不选，那么每一个 $k$ 的幂**一定恰好出现一次**，则答案为 $\dfrac{k^{2^{r+1}}-1}{k^{2^l}-1}$。比如 $(k^1+1)(k^2+1)(k^4+1)=k^0+k^1+\cdots+k^7=\dfrac{k^8-1}{k-1}$（$l,r+1$ 的两个分式可以消去分子）。直接使用逆元计算即可。以下是特殊情况：

- 分母为 $0$ 时，$k^{2^l} \equiv 1 \pmod p$，后面 $k$ 的幂也是同样的结果，直接输出 $2^{r-l+1}$ 即可。
- 使用费马小定理减小指数，注意此时模数为 $p-1$（$p=2$ 时不符合使用条件，直接特判即可）。
- 如果 $k$ 是奇数，最后再乘上 $2^{r-l}$ 的逆元即可（乘多的部分）。


```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int k,l,r,p,n;
int qp(int a,int b,int mod){
    a=(a%mod+mod)%mod;
    int c=1;
    while(b){
        if(b&1)c=c*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return c;
}
int calc(int x){
    if(k%p==0)return 0;
    n=qp(2,x+1,p-1);
    // cout<<n<<endl;
    return qp(k,n,p);
}
signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>k>>l>>r>>p;
        if(p==2){
            if(k%2)cout<<0<<'\n';
            else cout<<1<<'\n';
            continue;
        }
        if(calc(l-1)==1){
            if(k&1)cout<<qp(2,r-l+1,p)*qp(qp(2,r-l,p),p-2,p)%p<<'\n';
            else cout<<qp(2,r-l+1,p)<<'\n';
            continue;
        }
        if(k&1)cout<<((calc(r)-1)*qp((calc(l-1)-1),p-2,p)%p*qp(qp(2,r-l,p),p-2,p)%p+p)%p<<'\n';
        else cout<<((calc(r)-1)*qp((calc(l-1)-1),p-2,p)%p+p)%p<<'\n';
    }
    return 0;
}
```

---

## 作者：cirnovsky (赞：0)

简单提一下做法，注意到 $k^{2^a}\equiv k^{2^b}\equiv-1\equiv (-1)^{2^{b-a}}\equiv1\pmod{(k^{2^a}+1,k^{2^{b}}+1)}$，所以 $\gcd$ 只会是 $1$ 或 $2^{r-l}$，取决于 $k$ 的奇偶性，于是求一个 product 即可。

接下来是这篇题解的重点，聚焦 $\displaystyle \prod\left(k^{2^i}+1\right)=\sum_{i=0}^{2^{r-l+1}-1}\left(k^{2^l}\right)^i$ 做补充。

不妨从二项式乘法的角度来看，举例 $\left(k^{2^i}+1\right)\left(k^{2^j}+1\right)\left(k^{2^w}+1\right)$，不妨将 $k^{2^x}$ 看作是选择，将 $1$ 看作是不选择，那么一个长度为 $r-l+1$ 的二进制数即可表示出这个乘积所有的状态，不妨设这个状态为 $S$，注意到 $S$ 对答案的贡献是在做加法，并且因为类似 $2^i+2^j+2^w$ 的指数相加正好可以凑出 $S$，所以 $S$ 的贡献就是 $\left(k^{2^l}\right)^S$，得证。

```cpp
void executer() {
    int k, p;
    LL l, r;
    cin >> k >> l >> r >> p;
    SetMod(p-1);
    int e = qpow(2, l), e2 = qpow(2, r-l+1);
    SetMod(p);
    int K = k%p ? qpow(k, e) : 0, ans;
    if (K == 0) {
        ans = 1;
    }
    else {
        if (K == 1) {
            ans = qpow(2, r-l+1);
        }
        else {
            ans = mul(sub(qpow(K, e2), 1), inv(sub(K, 1)));
        }
    }
    if (k%2) {
        mul_eq(ans, inv(qpow(2, r-l)));
    }
    cout << ans << "\n";
}
```

---

