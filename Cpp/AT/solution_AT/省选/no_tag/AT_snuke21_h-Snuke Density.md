# Snuke Density

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_h



# 题解

## 作者：masterhuang (赞：2)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $8$ 题。

硬生生把一个困难的蓝想了黑的做法。（下面讲的是蓝的思维难度的做法）
  
前置知识：**Kummer** 定理，[勒让德定理](https://zhuanlan.zhihu.com/p/615240334)。

---

显然特判 $c<\max(a,b)$ 和 $c\ge a+b$ 的情况，现在情况是 $a,b\le c<a+b$

考虑变形：$\dfrac{c!}{a!b!}=\dbinom{a+b}{a}\times \left(\dfrac{(a+b)!}{c!}\right)^{-1}$

若它是整数，根据 **Kummer** 定理，$v_2\left(\dbinom{a+b}{a}\right)$ 等于 $a + b$ 在 $2$ 进制下进位的次数。

于是根据数据范围有 $v_2\left(\dbinom{a+b}{a}\right)\le 37$。

于是 $v_2\left(\dfrac{(a+b)!}{c!}\right)\le 37\Rightarrow \sum\limits_{i\ge 1} \left\lfloor\dfrac{a+b}{2^i}\right\rfloor-\left\lfloor\dfrac{c}{2^i}\right\rfloor\le 37$

于是 $ \left\lfloor\dfrac{a+b}{2}\right\rfloor-\left\lfloor\dfrac{c}{2}\right\rfloor\le 37\Rightarrow 37\ge \left\lfloor\dfrac{a+b}{2}\right\rfloor-\left\lfloor\dfrac{c}{2}\right\rfloor\ge \dfrac{a+b}{2}-1-\dfrac{c}{2}\Rightarrow a+b-c\le 2\times 38=76$

于是 $0<a+b-c\le 76$，否则不是整数。

考虑若它不是整数，则存在**素数** $p$ 使得 $v_p\left(\dfrac{c!}{a!b!}\right)<0$，即 $v_p\left(\dbinom{a+b}{a}\times \left(\dfrac{(a+b)!}{c!}\right)^{-1}\right)<0$。

于是 $p\mid \dfrac{(a+b)!}{c!}$，于是 $p$ 必为 $(c,a+b]$ 中一个数的素因子。由于 $0<a+b-c\le 76$，直接枚举而后分解素因子即可判断。
  
瓶颈在于分解素因子，设其复杂度为 $T(V)$，则总复杂度为 $O(\log V(T(V)+\omega(V)\log V))=O(T(V)\log V+\log^3V)$
  
其中 $V$ 为 $\max\{a,b,c\}$，而最外层的 $\log $ 为 $76$，显然由分析这时数始终是 $\log V$ 级别的。
  
如果用 **pollard-rho** 则这题能做 $V=10^{18}$。那个黑的想法就不讲了，太蠢了。
  
代码：
  
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e6+5;
LL a,b,c;
inline bool chk(LL p){LL cnt=0;for(LL i=p;i<=c;i*=p) cnt+=c/i-a/i-b/i;return cnt>=0;}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>a>>b>>c;
	if(c>=a+b) return cout<<"YES",0;if(max(a,b)>c||a+b>c+80) return cout<<"NO",0;
	for(LL i=c+1;i<=a+b;i++)
	{
		LL x=i;
		for(LL j=2;j*j<=x;j++) if(x%j==0)
		{
			while(x%j==0) x/=j;
			if(!chk(j)) return cout<<"NO",0;
		}if((x^1)&&!chk(x)) return cout<<"NO",0;
	}
	return cout<<"YES",0;
}
```

---

## 作者：fast_photon (赞：2)

**0. 前言**  
这题咋没有题解啊。  
各种乱搞都能草过去，想学靠谱做法的人可以看看题解。  

**0.5 感性题解**  
这部分看不懂或对正确性有疑惑的可以去思路区看详细证明。  
考虑按根号分质数，小于的暴力统计，大于的有整除性质，
设 $a'=p\lfloor\frac{a}{p}\rfloor,b'=p\lfloor\frac{b}{p}\rfloor,c'=p\lfloor\frac{c}{p}\rfloor$， 
则原式为整数必有 $a'+b'\le c'$。如果 $a+b\le c$ 可以直接整除推一推得出是整数。  
否则如果 $a+b-c$ 大于若干倍 $\sqrt{c}$，即大了很多，那么很可能有一个 $p$ 使得不满足性质。因为 $a,b$ 经过整除最多舍掉 $2p$。  
若 $a+b-c$ 较小，对于一个 $p$，若 $a+b,c$ 在一个**整除块**那么有解，只需要计算**有倍数**在 $[c,a+b]$ 的质数。可以筛出区间中每个不在根号内的质数暴力检查。

**1. 思路**  
首先考虑一个事情。原式为整数当且仅当 $\forall p\in\mathbb{Z}_{+},P(c!,p)\ge P(a!,p)+P(b!,p)_{}$。其中 $p$ 为质数时，$P(p,x)$ 为 $x$ 的质因子中 $p$ 的个数。否则，$P(p,x)=0$。  
那么我们就愉快地统计质因子出现个数。注意到 $\ge\sqrt{\max(a,b)}$ 的质因子不会有 $\ge 1$ 重幂出现于 $c!$ 的每一项。  

所以先考虑筛出 $\le \sqrt{\max(a,b)}$ 的所有质数，暴力统计它们在阶乘中的出现次数，有一个式子：$P(p,x!)=P(p,\lfloor\frac{x}{p}\rfloor!)+\lfloor\frac{x}{p}\rfloor$。加号右侧是至少一重幂的数的个数，它们每个贡献一重幂，左侧递归则是计算每个至少一重幂除以一个 $p$ 之后剩下的重幂个数。(勒让德）  
由于每次计算至少把数除以 $2$，所以一个质数的计算复杂度不超过 $\log n$，所以总复杂度不超过 $\frac{\sqrt{n}}{\log\sqrt{n}}\log n=\sqrt{n}$。  

然后考虑 $\ge \sqrt{\max(a,b)}$ 的所有质数。因为所有质数在每一项至多一重幂，即 $P(p,x!)=P(p,y!)+\lfloor\frac{x}{p}\rfloor$，而 $y\le p$ 所以 $P(p,x!)=\lfloor\frac{x}{p}\rfloor$。  
设 $a'=p\lfloor\frac{a}{p}\rfloor,b'=p\lfloor\frac{b}{p}\rfloor,c'=p\lfloor\frac{c}{p}\rfloor$。  
则原式为整数必有 $a'+b'\le c'$

接下来不难猜出一个结论：$a+b\le c\to a'+b'\le c'\to P(p,a!)+P(p,b!)\le P(p,c!)$。第二步可以直接两边约去 $p$，而对于第一步，考虑反证，若不成立则 $a+b\le c<c'+p\le a'+b'\le a+b$，矛盾。于是**若 $a+b\le c$ 则原式为整数。**  

若 $a+b>c$，对于任意 $p$，若 $\lfloor \frac{c}{p}\rfloor=\lfloor\frac{a+b}{p}\rfloor$，根据不等式 $\lfloor\frac{a}{p}\rfloor+\lfloor\frac{b}{p}\rfloor\le\lfloor\frac{a+b}{p}\rfloor$ 可以证明原式是整数。  
那么**只需考虑所有 $\exists k,kp\in[c,a+b]$ 的 $p$**。  
这是一个基础的筛法应用。根据前面筛好的根号以内的质数可以在 $\sqrt{n}\log (a+b-c)$ 的复杂度内找到所有满足条件的 $p$。具体筛法可以看代码，不再赘述。所以只需要保证 $a+b-c$ 不要太大。

若 $a+b>c$，感性理解这个不能大太多。理性一点，找到第一个 $p_0\ge\sqrt{\max(a,b)}$，$a-a'\le p_0-1$，$b-b'\le p_0-1$，$c-c'\ge 0$，那么 $a+b-c-(a'+b'-c')\le(2p_0-2)$。而 $a'+b'-c'\le 0$，则有 $a+b-c\le 2p_0-2$。也就是说**如果 $a+b-c\ge 2p_0-1$，那么原式一定不是整数。**  
根据某个 $[x,2x]$ 必有素数的定理，可以发现 $p_0\le 2\sqrt{\max(a,b)}$。其实实测很小。  

最终复杂度 $\sqrt{n}\log n$，实测跑得飞快。其中 $n=\max(a,b,c)$。  

**2. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<cassert>
#define int long long

using namespace std;

int up[1000005], pn = 0;;
long long p[1000005], r[1000005];

long long a, b, c, s;
long long sa, sb, sc;

signed main() {
	for(int i = 2; i <= 1000000; i++) {
		if(!up[i]) {
			p[pn++] = i;
		}
		for(int j = 0; j < pn && p[j] * i <= 1000000; j++) {
			up[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
	cin >> a >> b >> c;
	if(b > c || a > c) {
		cout << "NO\n";
		return 0;
	}
	for(int i = 0; i < pn; i++) {
		sa = sb = sc = 0;
 		long long xa = a, xb = b, xc = c;
		while(xa) {
			xa /= p[i]; sa += xa;
		}
		while(xb) {
			xb /= p[i]; sb += xb;
		}
		while(xc) {
			xc /= p[i]; sc += xc;
		}
		if(sa + sb > sc) {
			cout << "NO\n";
			return 0;
		}
	}
	if(a + b <= c) {
		cout << "YES\n";
		return 0;
	}
	long long q = a + b - c, slp = 0;
	for(int i = 0; i < pn; i++) {
		if(p[i] * p[i] > max(a + b, c)) {
			slp = i; break;
		}
	}
	if(q >= p[slp] * 2) {
		cout << "NO\n";
		return 0;
	}
	for(int i = 0; i <= q; i++) r[i] = c + i;
	for(int i = 0; i < pn; i++) {
		if(p[i] * p[i] > max(a + b, c)) break;
		for(long long j = (c + p[i] - 1) / p[i] * p[i]; j <= a + b; j += p[i]) {
			r[j - c] /= p[i];
		}
	}
	for(int i = 0; i <= q; i++) {
		if(r[i] > max(a + b, c) / r[i]) {
			if(c / r[i] < a / r[i] + b / r[i]) {
				cout << "NO\n";
				return 0;
			}
		}
	}
	cout << "YES\n";
}
```

---

