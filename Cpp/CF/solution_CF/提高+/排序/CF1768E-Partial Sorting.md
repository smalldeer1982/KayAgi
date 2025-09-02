# Partial Sorting

## 题目描述

给定整数 $n$ 和质数 $M$。  
对于一个 $1\sim 3n$ 的排列 $p$，你可以进行下列操作：

- 将 $p$ 的前 $2n$ 个元素从小到大排序。
- 将 $p$ 的后 $2n$ 个元素从小到大排序。

可以证明任意 $1\sim 3n$ 的排列都能通过若干次上述操作从小到大排序。  
记 $f(p)$ 表示将 $p$ 从小到大排序所需的最小总操作次数。  
你需要求出对于所有 $1\sim 3n$ 的排列 $p$，其 $f(p)$ 总和对 $M$ 取模后的值。

## 样例 #1

### 输入

```
1 100009067```

### 输出

```
9```

## 样例 #2

### 输入

```
2 100000357```

### 输出

```
1689```

## 样例 #3

### 输入

```
69 999900997```

### 输出

```
193862705```

# 题解

## 作者：tZEROちゃん (赞：14)

显然我们最多只需要 $3$ 次操作：操作 $1\to$ 操作 $2\to$ 操作 $1$。

1. $f(p) = 0$。       
   条件：这个排列已经是有序的了。       
   代码：
   ```cpp
   /**** 0 ****/
   ans[0] = 1;  
   ```
   
2. $f(p) \le 1$。             
   条件：前 $n$ 个数字，或后 $n$ 个数字已经在正确的位置上了。    
   前 $2n$ 个或者后 $2n$ 个自由排列，就是 $(2n)!$。           
   重复的部分：就是中间的 $n$ 个元素。          
   答案是 $2\times (2n!)-n!$。       
   代码：
   ```cpp
   /**** 1 ****/
   ans[1] = (2 * fac[2 * n] - fac[n] - ans[0] + mod) % mod;
   ```

3. $f(p) \le 2$。            
   条件：最小的 $n$ 个元素在 $[1,2n]$，或最大的 $n$ 个元素在 $[n+1,3n]$。        
   如果是前者，那么：       
   - 有 $C^n_{2n}$ 中方案为这些数字选择 $n$ 个位置。
   - 对于这个选择的位置，有 $n!$ 种方案去安排最小的 $n$ 个数，剩下的 $2n!$ 任意排列。
   
   如果是后者，也同理。    
   但是，这两种情况是有交叉的。
   
   我们来讨论一下在 $[n+1,2n]$ 这个区间内的 $n$ 个数。
   如果这个区间内恰好有 $i=0$ 个数出现前面的 $n$ 个位置：
   - 在前 $n$ 个数字中，有 $n$ 个数字在 $[1,n]$ 范围内，有 $C^{n-0}_n\times n!$ 种情况。
   - 在前 $n$ 个数字中，有 $0$ 个数字在 $[n+1,2n]$ 范围内，有 $C^0_n\times n!$ 种情况。
   - 在后 $n$ 个数字中，有 $n$ 个数字在 $[n+1,3n]$ 范围内，有 $C^n_{2n-0}\times n!$ 种情况。        
   
   然后把具体的 $0$ 转化成抽象的 $i$，那么交叉就会多 $C^{n-i}_n \times C^i_n \times C^{n}_{2n-i} \times n! \times n!\times n!$。
   然后在 $[1, n]$ 的范围内枚举 $i$，最终将这一部分减去。
   
   所以答案就是 $2\times C^n_{2n}\times n!\times 2n!-\sum^n_{i=0}C^{n-i}_n\times C^{i}_{n}\times C^{n}_{2n-i}\times n!\times n!\times n!$。
   
   ```cpp
   /**** 2 ****/
   ans[2] = fac[2 * n] % mod * C(2 * n, n) % mod * fac[n] % mod * 2 % mod;
   rep (i, 0, n) {
     int sub = C(n, i) % mod * C(n, n - i) % mod * C(2 * n - i, n) % mod;
     sub = sub * fac[n] % mod * fac[n] % mod * fac[n] % mod;
     ans[2] = (ans[2] - sub + mod) % mod;
   }
   ans[2] = (ans[2] - ans[1] - ans[0] + mod) % mod;
   ```
  
4. $f(p)\le 3$。      
   条件：所有 $(3n)!$ 个排列。           
   直接用 $(3n)!$ 减去之前的情况就行。
   
   ```cpp
   /**** 3 ****/
   ans[3] = (fac[3 * n] - ans[2] - ans[1] - ans[0] + mod) % mod;
   ```
   
最后答案是 $ans_0 \times 0 + ans_1 \times 1 + ans_2 \times 2 + ans_3 \times 3$，输出即可。

代码不放了。

---

## 作者：ExplodingKonjac (赞：4)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1768E)**

* 2023/10/7 upd: 修复了式子的错误。

## 题目分析

首先，使用三次操作即可将序列排序：$1,2,1$。其中第一次操作把前 $2n$ 个中最大的 $n$ 个放到了 $[n+1,2n]$，于是第二次操作就能够把整个序列最大的 $n$ 个放到 $[2n+1,3n]$，最后一次操作把 $[1,2n]$ 排序。（当然 $2,1,2$ 也可行）

考虑需要不同操作次数的方案：

* 操作次数 $\le0$：

  有方案数 $s_o=1$。
  
* 操作次数 $\le1$：

  说明 $[1,n]$ 已经归位或者 $[2n+1,3n]$ 已经归位。用前 $n$ 个固定的方案数加后 $n$ 个固定的方案数，减去两边都固定的方案数，则有
  
  $$s_1=2(2n)!-n!$$
  
* 操作次数 $\le2$：

  这里需要一些分析。我们发现，需要至多两次操作的情况形如：第一次 $1$ 操作把 $1,2,\dots,n$ 都放在了 $[1,2]$，然后排序一次；也可以是第一次 $2$ 操作把 $2n+1,2n+2,\dots,3n$ 都放在了 $[2n+1,3n]$。也就是说，$1,2,\dots,n$ 全部在 $[1,nn]$ 内。或者 $2n+1,2n+2,\dots,3n$ 全部在 $[2n+1,3n]$ 内。可以发现这就是充要条件。
  
  然后考虑计数，用 $1,2,\dots,n$ 满足条件的方案，加上 $2n+1,2n+2,\dots,3n$ 满足条件的方案，再减去都满足条件的方案。前两者的方案是相同的，可以得到是 $\displaystyle\binom{2n}{n}n!(2n)!$。至于后者，因为 $[1,2n]$ 和 $[n+1,3n]$ 有交 $[n+1,2n]$，因此可以枚举 $2n+1,2n+2,\dots,3n$ 落在 $[n+1,2n]$ 的个数，最终得到：
  
  $$s_2=2\binom{2n}{n}n!(2n!)-\sum_{i=0}^n \binom{n}{i}\binom{n}{n-i}\binom{2n-i}{n}(n!)^3$$
  
* 操作次数 $\le3$：

  $s_3=n!$
  
那么最后答案就可以算了，注意我们算的是**小于等于**的方案数，需要差分一次。

$$ans=1(s_1-s_0)+2(s_2-s_1)+3(s_3-s_2)$$

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

int MOD;
inline int qpow(LL a,LL b) { int r=1;for(;b;(b&1)?r=r*a%MOD:0,a=a*a%MOD,b>>=1);return r; }
inline int madd(int x) { return x; }
inline int mmul(int x) { return x; }
inline int msub(int x,int y) { return (x-=y)<0?x+=MOD:x; }
inline int mdiv(int x,int y) { return (LL)x*qpow(y,MOD-2)%MOD; }
template<typename ...Args>inline int madd(int x,Args ...y) { return (x+=madd(y...))>=MOD?x-=MOD:x; }
template<typename ...Args>inline int mmul(int x,Args ...y) { return (LL)x*mmul(y...)%MOD; }


int n,fac[3000005],inv[3000005];
inline int binom(int r,int c) { return mmul(fac[r],inv[c],inv[r-c]); }
int main()
{
	qin>>n>>MOD;
	fac[0]=1;
	for(int i=1;i<=3*n;i++) fac[i]=mmul(fac[i-1],i);
	inv[3*n]=qpow(fac[3*n],MOD-2);
	for(int i=3*n;i>=1;i--) inv[i-1]=mmul(inv[i],i);
	int s1=msub(madd(fac[2*n],fac[2*n]),fac[n]);
	int s2=mmul(2,binom(2*n,n),fac[n],fac[2*n]);
	int s3=fac[3*n];
	for(int i=0;i<=n;i++) s2=msub(s2,mmul(binom(n,i),binom(n,n-i),binom(2*n-i,n),fac[n],fac[n],fac[n]));
	s3=msub(s3,s2),s2=msub(s2,s1),s1=msub(s1,1);
	qout<<madd(s1,mmul(s2,2),mmul(s3,3));
	return 0;
}
```

---

## 作者：lzqy_ (赞：4)

少乘一个组合数，寄飞了。

-----

首先容易想到一个结论，$f(p) \le 3$。

**证明**：考虑一种一定可行的构造。先对 $[1,2n]$ 排序，排序之后保证了 $(n,3n]$ 的数都在 $(n,3n]$ 之间，于是再对 $[1,2n],(n,3n]$ 排序后排列就变为升序。

-----

接着只要算出满足 $f(p) \le k(0 \le k \le 3)$ 的排列个数 $sum0,sum1,sum2,sum3$ 即可。

- $f(p) \le 0$

	显然要排列有序，$sum0=1$。
    
- $f(p) \le 1$

	至多只能进行一次排序，所以 $[1,n],(2n,3n]$ 之中必定有一个区间恢复原状，其他部分随意排列，即 $2(2n)!$。
    
    发现 $[1.n],(2n,3n]$ 都恢复原状的情况被算了两次，此时 $(n,2n]$ 随意排列，因此减去 $n!$。
    
- $f(p) \le 2$
	
   若进行两次排序，则肯定是前部分排一次，后部分排一次。
   
   假设先排前半部分，那么排完之后必须保证 $[1,n]$ 复原（因为接下来的排序不会涉及这个区间）。也就是说，$[1,n]$ 之间的数必须在 $[1,2n]$ 之间，则这一部分的答案是 $2({2n\choose n}\times n! \times (2n)!)$。乘 $2$ 是为了处理先排后半部分。显然对称。
   
   类似地，发现 $[1,n]$ 在 $[1,2n]$ 之间，且 $(2n,3n]$ 在 $(n,3n]$ 之间的排列被算了两次，需要减去。
   
   枚举 $[1,2n]$ 之间 $(n,2n]$ 的数有多少，然后就可以用组合数表达排列个数了。具体地，$sum2$ 还需要减去 $\sum\limits_{i=0}^n {2n-i\choose n}\color{red}{{n\choose i}^2}\color{lll}(n!)^3$
   
- $f(p) \le 3$

	$(3n)!$ 减去不合法的就好。

式子里标红的地方就是考场被创死的地方。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=5000010;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f; 
}
int fac[maxn],ifac[maxn];
int ans,n,mod;
il int fpow(int n,int m,int x=1){
	for(;m;m>>=1,n=1ll*n*n%mod)
		if(m&1) x=1ll*x*n%mod;
	return x;
}
il int Inv(int x){return fpow(x,mod-2);}
int C(int n,int m){return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;}
int main(){
	n=read(),mod=read(),fac[0]=ifac[0]=1;
	for(int i=1;i<=3*n;i++) fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=3*n;i++) ifac[i]=fpow(fac[i],mod-2);
	int sum0,sum1,sum2,sum3;
	sum0=1;
	sum1=(2ll*fac[2*n]-fac[n]-sum0+2ll*mod)%mod;
	sum2=(2ll*C(2*n,n)*fac[n]%mod*fac[2*n]%mod)%mod;
	for(int i=0;i<=n;i++)
		sum2=(sum2-1ll*fac[n]*fac[n]%mod*fac[n]%mod*C(2*n-i,n)%mod*C(n,i)%mod*C(n,i)%mod+mod)%mod;
	sum2=(sum2-sum0-sum1+2ll*mod)%mod;
	sum3=(((ll)fac[3*n]-sum2-sum1-sum0)%mod+mod)%mod;
	printf("%lld\n",(0ll*sum0+1ll*sum1+2ll*sum2+3ll*sum3)%mod);
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：4)

$$\texttt{Preface}$$

果然数数太弱了，花了 $1h^+$。![](https://啧.tk/ll)

$$\texttt{Description}$$

[Partial Sorting](https://www.luogu.com.cn/problem/CF1768E)

$$\texttt{Solution}$$

我们先来证明一个结论：$\max f(p) = 3$。

考虑任意一个长度为 $3n$ 的排列 $p$，我们将其分成三段，分别为 $1 \sim n, n + 1 \sim 2n, 2n + 1 \sim 3n$。

首先对前 $2n$ 个数升序排序，那么第一段中**值在 $2n + 1 \sim 3n$ 之间**的数肯定都会被排到第二段。

然后对后 $2n$ 个数升序排序，由于值在 $2n + 1 \sim 3n$ 之间的数都在后两段，所以排序之后第三段的数一定为 $2n + 1 \sim 3n$，并且有序。

这样 $1 \sim 2n$ 就都在前两段，再对前 $2n$ 个数排序即可。

---

然后考虑分别计算 $num0, num1, num2, num3$，表示 $f(p) = 0/1/2/3$ 的排列的数量。

$num0 = 1$，不作解释。

---

对于 $num1$，就是排序一次就能使整个序列有序，所以肯定是第一段中的数为 $1 \sim n$ 且有序，或者最后一段中的数为 $2n + 1 \sim 3n$ 且有序。

这样数量就是 $2 \times (2n)!$，但是两段都满足条件的会被计算两次，容斥一下，$num1 = 2 \times (2n)! - n! - num0$。

---

考虑排序两次能够使整个序列有序，肯定是先排前 $2n$ 个，再排后 $2n$ 个，或者反过来。

以第一种情况为例，排完前 $2n$ 个数后我们需要保证第一段为 $1 \sim n$ 且有序，所以需要保证前两段中包含 $1 \sim n$ 所有数；另一种情况就需要保证后两段中包含 $2n + 1 \sim 3n$ 所有数。

先不考虑重复计算，那么答案就是:

$$sum = 2 \times {2n \choose n} \cdot n! \cdot (2n)!$$

跟计算 $num1$ 时一样，我们考虑容斥，对于所有既在前两段包含 $1 \sim n$ 所有数，又在后两段包含 $2n + 1 \sim 3n$ 所有数的排列，都会被计算两次，我们设这样排列的数量为 $num$。

则考虑枚举中间段中有 $i$ 个数在 $1 \sim n$ 之间：

$$num = {(n!)}^3 \sum_{i = 0}^n {n \choose i} \cdot {n \choose n - i} \cdot {2n - i \choose n}$$

前面 ${(n!)}^3$ 是指我们决定了哪些位置填 $1 \sim n$，哪些位置填 $n + 1 \sim 2n$，哪些位置填 $2n + 1 \sim 3n$ 之后再确定三段数的填放顺序。

然后中间有 $i$ 个数在 $1 \sim n$ 之间，我们就在 $n$ 个位置中选出 $i$ 个位置，然后在第一段 $n$ 个位置中选出 $1 \sim n$ 中剩下的 $n - i$ 个位置，这些位置填 $1 \sim n$ 的数；接着在后两段剩下的 $2n - i$ 个位置中选出 $n$ 个位置，这些位置填 $2n + 1 \sim 3n$ 的数；剩下的位置填 $n + 1 \sim 2n$ 的数。

所以 $num2 = sum - num - num1 - num0$。

---

最后 $num3 = (3n)! - num2 - num1 - num0$。

时间复杂度 $\Theta(n)$。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

class istream {
    char buf[13000003], *s;
    public:
        inline istream() {
            buf[ fread(s = buf, 1, 13000001, stdin) ] = '\n';
        }
        template <typename T>
        inline void operator >> (T &rhs) {
            for (rhs = 0; !isdigit(*s); ++s);
            while (isdigit(*s)) rhs = rhs * 10 + (*s++ & 15);
        }
} in;
struct ostream {
    char buf[8000005], *s;
    inline ostream() { s = buf; }
    template <typename T>
    inline void operator << (T d) {
        if (!d) {
            *s++ = '0';
        } else {
            static T w;
            for (w = 1; w <= d; w *= 10);
            for (; w /= 10; d %= w) *s++ = d / w ^ '0';
        }
        *s++ = '\n';
    }
    inline ostream &operator << (const char &c) { *s++ = c; return *this; }
    inline ~ostream() { fwrite(buf, 1, s - buf, stdout); }
} out;

int n, fac[3000005], ifac[3000005], mod, ans, num1, num2, num3;

int qpow(int x, int p) {
    int ans = 1;
    while (p) {
        if (p & 1) ans = 1ll * ans * x % mod;
        p >>= 1, x = 1ll * x * x % mod;
    }
    return ans;
}

int C(int m, int n) {
    if (n > m) return 0;
    return 1ll * fac[m] * ifac[n] % mod * ifac[ m - n ] % mod;
}

signed main() {
    in >> n, in >> mod;
    fac[0] = 1;
    for (int i = 1; i <= 3 * n; ++i) {
        fac[i] = 1ll * fac[ i - 1 ] * i % mod;
    }
    ifac[ 3 * n ] = qpow(fac[ 3 * n ], mod - 2);
    for (int i = 3 * n; i; --i) {
        ifac[ i - 1 ] = 1ll * ifac[i] * i % mod;
    }
    num1 = (2ll * fac[ 2 * n ] % mod - fac[n] - 1) % mod;
    if (num1 < 0) num1 += mod;
    ans = num1;
    int sum = 2ll * C(2 * n, n) % mod * fac[n] % mod * fac[ 2 * n ] % mod, now = 0;
    for (int i = 0; i <= n; ++i) {
        now = (now + 1ll * C(n, i) * C(n, n - i) % mod * C(2 * n - i, n) % mod) % mod;
    }
    now = 1ll * now * fac[n] % mod * fac[n] % mod * fac[n] % mod;
    num2 = (sum - now - num1 - 1) % mod;
    if (num2 < 0) num2 += mod;
    ans = (ans + 2ll * num2 % mod) % mod;
    num3 = (fac[ 3 * n ] - num2 - num1 - 1) % mod;
    if (num3 < 0) num3 += mod;
    ans = (ans + 3ll * num3 % mod) % mod;
    out << ans;
    return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：SkyRainWind (赞：3)

本文也发表在[我的blog](https://www.cnblogs.com/SkyRainWind/p/17038495.html)上

记 P1 为将 $1..2\times n$ 排序， P2 为将 $n+1..3\times n$ 排序

首先观察到答案一定不会超过 3（ P1P2 之后 $1..n$ 的所有数一定在 $1..2n$ 中，这样只需要 P1 就可以排好，同理 $n+1..2n$ & $2n+1..3n$ ）
- 答案为0的情况：$1,2 .. 3n$ 一共一种
- 答案为1：$2n+1..3n$ 已经有序，$1..2n$ 只需要一次 P1 即可，同理也有只需要一次 P2 的情况。注意减去重复情况（ $1..n$ & $2n+1..3n$ 均有序，只需要一次 P1/P2，但是计算了 2 次，还有一个已经有序的情况），这里的答案是 $(2n)! - n! - 1$

答案为 3 的情况不好统计，考虑先算出答案为 2 的情况，然后用 $(3n)!$ 减一下

- 答案为 2 ：显然对应的操作就是 P1P2 或者 P2P1 ，分别考虑这些对应的是什么情况：
	- P1P2：那么需要满足的条件是：$[1,2n]$ 中含有 $1..n$ ，而且至少含一个 $2n+1..3n$ 中的数，或者 $[1,2n]$ 是 $1..2n$ 的一个**乱序**排列，而且 $[2n+1,3n]$ 是 $2n+1..3n$ 的一个**乱序**排列（要注意这里面不能存在一次就能排好序的情况，因此很多“乱序”条件是应该的）。对应的答案：
    $$(\binom{2n}{n} \times n!-1)\times (\binom{2n}{n}\times n! - n!) \times n! + (n!-1)\times ((2n)!-n!)$$ 
    解释一下，第一个括号是选出 1~n 的位置并排列好，-1 是因为不能出现的情况是 1~n 在下标也是 1~n 的情况恰好有序了（这样只需要一次 P2 就行了）； 第二个括号是利用容斥算出至少含 1 个 $2n+1..3n$ 的数的情况并排列好，最后的 $n!$ 是将 $[2n+1,3n]$ 的数排列好。加号后面的表示的是 [或者] 后面之后的情况。因为是乱序所以需要 -1，然后 $[1,2n]$ 随便排
	- P2P1：考虑如何去掉 P1P2 已经数过的情况，最后得出此处的要求是：$[n+1,3n]$ 中含有 $2n+1..3n$ 所有的数，而且 $[2n+1,3n]$ 至少有 1 个 $1..n$ 的数在 $[2n+1,3n]$ 中（这里就和 P1P2 不存在交集了），答案是：
    $$\sum_{k=1}^n \binom{n}{k} \times \binom{n}{n-k} \times ((2n)!-\binom{n}{k}\times k! \times (2n-k)!)$$
   解释也很显然：先取 $1..n$ 中的 $k$ 个数，再挑 $n+1..2n$ 中的 $n-k$ 个，现在有了 $2n$ 个数要填到 $[n+1,3n]$ 利用容斥就可以求出至少有一个 $1..n$ 位于 $[2n+1,3n]$ 的方案数（钦定 $k$ 个数都在 $[n+1,2n]$ 中，然后排列一下就行了）
- 3 的情况就是 $(3n)!$ 减去上面的

代码：
```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 3e6+5;

int n,mod=998244353;

int fac[maxn],inv[maxn];
int pw(int x,int y){
	if(!y)return 1;
	if(y==1)return x;
	int mid=pw(x,y>>1);
	if(y&1)return 1ll*mid*mid%mod*x%mod;
	return 1ll*mid*mid%mod;
}

int C(int x,int y){
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}

signed main(){
	scanf("%d%d",&n,&mod);
	fac[0] = inv[0] = 1;
	for(int i=1;i<=maxn-5;i++)fac[i] = 1ll*fac[i-1]*i%mod;
	inv[maxn-5]=pw(fac[maxn-5],mod-2);
	for(int i=maxn-6;i>=1;i--)inv[i] = 1ll*inv[i+1]*(i+1)%mod;
	
	ll t1 = (2ll*fac[2*n]%mod - fac[n]%mod - 1 + mod)%mod;
	ll t2 = (1ll*fac[n]*C(2*n,n)-1)%mod*(1ll*(C(2*n,n)-1)*fac[n]%mod)%mod*fac[n]%mod;
	(t2 += 1ll*(fac[n]-1)*(fac[2*n]-fac[n]+mod)%mod) %= mod;
	
	for(int k=1;k<=n;k++){
		ll tmp = 1ll*C(n,k)*C(n,n-k)%mod;
		tmp = tmp*(fac[2*n]-1ll*C(n,k)*fac[k]%mod*fac[2*n-k]%mod+mod)%mod*fac[n]%mod;
		(t2 += tmp) %= mod;
	}
	ll t3 = (fac[3 * n] - 1 - t1 + mod - t2 + mod) % mod;
	ll ans = (t1 + 2ll*t2%mod + 3ll*t3%mod) % mod;
	cout<<ans;
	
	return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17044655.html)

[题目传送门](http://codeforces.com/problemset/problem/1768/E)

[题目翻译](https://www.luogu.com.cn/problem/CF1768E)

UPD：组合数上下打反了 /youl，已经更正。

### 题目解析
显然我们可以证明 $f(p)\in\{0,1,2,3\}$  

$f(p)=0$ 显然只有 $s_1=1$ 种。

考虑 $f(p)=1$  
如果前面交换一次，那么有 $(2n)!$ 种。只交换后面同理。  
考虑交换前后都可以的重复情况，那么就是 $n!$ 种。  
容斥得 $s_2=2\times(2n)!-n!$

考虑 $f(p)=2$  
如果前面交换一次然后后面交换，那么只需要保证 $1\sim n$ 全部在 $1\sim 2n$ 位置内。方案数是
$$\binom{2n}{n}\times(2n)!$$  
如果是先交换后面同理。  
考虑重复的情况，也就是 $1\sim n$ 全部在 $1\sim 2n$ 位置，并且 $2n+1\sim 3n$ 全部在 $n+1\sim 3n$ 位置。  
枚举 $1\sim n$ 在 $n+1\sim 2n$ 位置内的数量，可以得到重复的方案为
$$M=\sum_{i=0}^{n}\binom{n}{i}\binom{n}{n-i}\binom{2n-i}{n}\times (n!)^3$$
所以
$$s_3=2\times\binom{2n}{n}\times(2n)!-M$$

$f(p)=3$ 直接用来减就好了，$s_4=(3n)!-s_1-s_2-s_3$

答案就是 $s_2+2s_3=3s_4$

```cpp
int n,MOD; ll fact[maxn],inv[maxn],s1,s2,s3,s4,M;
ll fastpow(ll x,ll y){
	ll tmp=x%MOD,res=1;
	while(y){
		if(y&1) res=res*tmp%MOD;
		y>>=1; tmp=tmp*tmp%MOD;
	} return res;
}
#define P(n,m) (fact[n]*inv[(n)-(m)]%MOD)
#define C(n,m) (fact[n]*inv[m]%MOD*inv[(n)-(m)]%MOD)
int main(){
	n=read(); MOD=read(); int i; fact[0]=1; for(i=1;i<=n*3;i++) fact[i]=fact[i-1]*i%MOD;
	inv[2*n]=fastpow(fact[2*n],MOD-2); for(i=n*2-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
	s1=1; s2=2*fact[2*n]-fact[n]+MOD-1; s2%=MOD;
	M=0; for(i=0;i<=n;i++) M+=C(n,i)*C(n,n-i)%MOD*P(2*n-i,n)%MOD,M%=MOD;
	M*=fact[n]*fact[n]%MOD,M%=MOD;
	s3=2*P(2*n,n)*fact[2*n]%MOD-M-(s1+s2); s3%=MOD,s3+=MOD,s3%=MOD;
	s4=fact[3*n]-s1-s2-s3; s4%=MOD,s4+=MOD,s4%=MOD;
	print((s2+s3*2+s4*3)%MOD); return 0;
}
```

---

## 作者：ダ月 (赞：1)


### 题意概要：

给定 $n$，存在长度为 $3n$ 的 $3n!$ 个排列。对于每个排列 $p$，可以对**前或后** $2n$ 个数进行升序排序。令 $f(p)$ 表示最小操作数，让 $p$ 整个序列升序排序。求所有可能 $f(p)$ 的和。

### 题意分析：

- 我们先证明最多只有 $3$ 步，就可以让 $p$ 升序。即 $f(p)\le3$。我们按照**前后前**的顺序排序，可以让 $p$ 升序。

接下来枚举 $f(p)$ 的值域。

- 若 $f(p)=0$。

显而易见，只存在 $1$ 种情况，即 $p$ 本来就满足升序。

- 若 $f(p)\le1$。

则只要前 $n$ 个数在 $[1,n]$ 区间正序内，或者后 $n$ 个数在 $[2n+1,3n]$ 区间内正序。

先讨论**后者**这种情况。

对于位置的选择，有 $1$ 种选法，选择后这 $n$ 个数有 $n!$ 排列方法，另外 $2n$ 个数有 $2n!$ 中排列方法。根据乘法原理，共有 $n!\times2n!$ 中选法。

对于前者情况，同理。但是它们之间有重复的情况。即中间 $n$ 个元素，并都放在 $[n+1,2n]$ 区间内，会造成前后两种情况的重复。减去 $n!$ 即可。

故这类共有 $2\times n!\times2n!-n!$。

- 若 $f(p)\le2$。

则我们只需要将前 $n$ 个元素放置在 $[1,2n]$ 区间内，或者将后 $n$ 个元素放在 $[n+1,3n]$ 区间内即可。

我们先讨论**前者**情况。

对于前 $n$ 个数的位置的选择，共有 $\binom{2n}{n}$ 选法，对于 $n$ 个数，共有 $n!$ 种排列，对于另外 $2n$ 个数，共有 $2n!$ 种排列。根据乘法原理，共有 $\binom{2n}{n}\times n!\times2n!$

对于后者，做类似的讨论即可。但是它们之间存在重复情况。

我们令 $i$ 表示前 $n$ 个数放在 $[n+1,2n]$ 区间内的数共有 $i$ 个。将后 $n$ 个数放置在 $[n+1,3n]$ 区间内。显然共有 $\binom{n}{n-i}\times\binom{n}{i}\times\binom{2n-i}{n}\times n!\times n!\times n!$ 种情况。

因为 $i\in[0,n]$，所以共有 

$\begin{aligned}\sum_{i=0}^n\binom{n}{n-i}\times\binom{n}{i}\times\binom{2n-i}{n}\times n!\times n!\times n!\end{aligned}$ 

种情况是重复的。

那么，为什么说这样子情况是重复的？因为前 $n$ 个数在 $[1,2n]$ 内的同时，后 $n$ 个数也可以在 $[n+1,3n]$ 内。 

所以一共有 $\begin{aligned}\binom{2n}{n}\times n!\times2n!-\sum_{i=0}^n\binom{n}{n-i}\times\binom{n}{i}\times\binom{2n-i}{n}\times n!\times n!\times n!\end{aligned}$ 种情况。

- 对于 $f(p)\le3$ 的情况。

所有排列都满足这个情况，所有共有 $3n!$ 种情况。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int n,mod;
typedef long long ll;
const int N=3e6+10;
ll fac[N],nfac[N];
ll QP(ll x,ll y){ll ans=1;for(;y;y>>=1,x=x*x%mod) if(y&1) ans=ans*x%mod;return ans;}
void init(){
	fac[0]=1;for(int i=1;i<=N-10;i++) fac[i]=fac[i-1]*i%mod;
	nfac[N-10]=QP(fac[N-10],mod-2);for(int i=N-11;i>=0;i--) nfac[i]=nfac[i+1]*(i+1)%mod;
}ll C(ll x,ll y){if(x<y||x<0||y<0) return 0; return nfac[y]*nfac[x-y]%mod*fac[x]%mod;}
ll f[4];
ll P(ll x){return (x%mod+mod)%mod;}
int main(){
	scanf("%d%d",&n,&mod);
	init();
	f[0]=1;
	f[1]=P(fac[n<<1]*2%mod-fac[n]-f[0]);
	f[2]=P(2*C(n<<1,n)%mod*fac[n]%mod*fac[n<<1]%mod-f[0]-f[1]);
	for(int i=0;i<=n;i++) f[2]=P(f[2]-C(n,n-i)%mod*C(n,i)%mod*C((n<<1)-i,n)%mod*fac[n]%mod*fac[n]%mod*fac[n]%mod);
	f[3]=P(fac[n*3]-f[0]-f[1]-f[2]);
	printf("%lld\n",(f[1]+(f[2]<<1)+(f[3]*3))%mod);
	return 0;
}
```


时间复杂度：$O(n)$

---

## 作者：封禁用户 (赞：0)

简单容斥。

注意到每一个排列都可以在最多 $3$ 次排序后完成整体排序。证明：先前 $2n$ 个数排序，那前 $2n$ 个数中较大的 $n$ 个数与最后 $n$ 个数中一定含有所有的在 $2n+1 \sim 3n$ 的数，所以将后面 $2n$ 个数排序后最后的 $n$ 个数一定已经有序并是在 $2n+1 \sim 3n$ 的数。只需再将前面的 $2n$ 个数排序即可。

所以重点是统计 $f(p)$ 小于 $3$ 的情况。设 $ans_j$ 为 $f(p)\le j$ 的个数。注意不是 $f(p)=j$。显然 $ans_3 = (3n)!\times 3$。

让我们来考虑 $ans_2$。观察一下什么情况下 $f(p)\le 2$：当且仅当 $1\sim n$ 的数都分布在序列的 $1\sim 2n$ 位置或 $2n+1\sim 3n$ 的数都分布在序列的 $n+1\sim 3n$ 位置。这样就可以通过排序前面或后面一次使得 $1 \sim n$ 的数就是 $1\sim n$ 或 $2n+1 \sim 3n$ 的数就是 $2n+1\sim 3n$。那么 $ans_2=A(2n,n)\times (2n)!\times 2$。

但有一个问题，就是如果一个序列同时满足排序前面使前 $n$ 个有序以及排序后面使后 $n$ 个有序，它就会被计算 $2$ 次。于是我们要容斥去重。

来看看如何计算：我们先将序列分成如下的三段。那 $1\sim n$ 的数可能分布在 $1,2$ 段，$2n+1\sim 3n$ 的数可能分布在 $2,3$ 段。由于都可能在 $2$ 段，就会互相产生影响，我们就枚举 $1\sim n$ 的数分布在 $2$ 段的有 $i$ 个。

![](https://cdn.luogu.com.cn/upload/image_hosting/941khgg0.png)

于是，

$$ans_2=ans_2-\binom{n}{i}\times A(n,i)\times A(2n-i,n)\times A(n,n-i)\times n! $$

总的就是：

$$ans_2=A(2n,n)\times (2n)!\times 2-\sum_{i=0}^{n}(\binom{n}{i}\times A(n,i)\times A(2n-i,n)\times A(n,n-i)\times n!)$$

再来计算 $ans_1$。这种情况就是 $1$ 段的数天然有序或 $3$ 段的数天然有序。也就是 $ans_1=(2n)!\times 2$。如果 $1,3$ 段都天然有序，会被计算两次，所以还要减掉 $n!$（也就是 $2$ 段的随意排列数）。也就是：

$$ans_1=(2n)!\times 2-n!$$

显然 $ans_0=1$，所以答案为：

$$ans_3 \times 3 -ans_2-ans_1-ans_0$$

时间复杂度 $\mathcal{O}(n)$。

## Code

```cpp
const int N=3e6+10;
int n,mod;
int tim[N];
int inv[N];
void gs(){
	scanf("%lld%lld",&n,&mod);
	tim[0]=1;inv[0]=1;
	f(i,1,N-10){tim[i]=tim[i-1]*i%mod;}
	int ans=tim[n*3]*3%mod;
	ans=((ans-A(n*2,n)*tim[n*2]%mod*2%mod)%mod+mod)%mod;
	f(i,0,n){
		ans=(ans+C(n,i)*A(n,i)%mod*A(n*2-i,n)%mod*A(n,n-i)%mod*tim[n]%mod)%mod;
	}
	ans=((ans-tim[n*2]*2%mod)%mod+mod)%mod;
	ans=(ans+tim[n])%mod;
	ans=((ans-1)%mod+mod)%mod;
	printf("%lld\n",ans);
}
```

---

## 作者：Milmon (赞：0)

## 分析

容易知道最多只需要 $3$ 次就可以完成排序，具体构造如下：

> 首先对前 $2n$ 个数排序，此时前 $n$ 大的数必定在后 $2n$ 个位置中；
> 
> 然后对后 $2n$ 个数排序，此时前 $n$ 大的数已经完成了排序（在后 $n$ 个位置上且已经完成排序）。
> 
> 最后再对前 $2n$ 个数排序，此时整个序列就完成了排序。
> 
> 综上所述，至多只需要 $3$ 步就可以完成排序。

注意到一共有 $(3n)!$ 种情况，那么我们只需要分别求出操作次数 $=0$，操作次数 $\leq 1$，操作次数 $\leq 2$ 的情况数量即可。

## 操作次数 $=0$

即已经完成排序，只有 $1$ 种可能。

## 操作次数 $\leq 1$

只需要一次就能完成，那么必然要么前 $n$ 个数已经完成排序，要么后 $n$ 个数已经完成排序。

对于前 $n$ 个数已经完成排序，只需后 $2n$ 个数任意排列即可，方案数为 $(2n)!$。后 $n$ 个数已经完成排序同理。

注意两种情况可能重复，即前 $n$ 个数和后 $n$ 个数都已经完成排序，即中间 $n$ 个数任意排列，方案数为 $n!$。故答案为

$$
2(2n)!-n!.
$$

```cpp
count1=2*fac[n<<1]-fac[n];
```

## 操作次数 $\leq 2$

操作次数为 $2$，要么是先操作前 $2n$ 个数，再操作后 $2n$ 个数，要么就两个操作交换。而这样能完成排序的充分必要条件是前 $n$ 小的数在前 $2n$ 个数中或者前 $n$ 大的数在后 $2n$ 个数中。

对于第一种情况，首先从前 $2n$ 个位置中选出 $n$ 个位置放前 $n$ 小的数，然后这 $n$ 个位置任意排序，其它 $2n$ 个位置任意排序即可。第二种情况也是如此，故方案数为

$$
2\binom{2n}n(2n)!n!.
$$

接着考虑两种情况的重复部分。枚举中间 $n$ 个位置中区间 $[2n+1,3n]$ 的数的个数 $i$，此时需要从这 $n$ 个位置中选出这 $i$ 个位置（$\dbinom ni$），再从后 $n$ 个位置中选出剩下 $n-i$ 个位置（$\dbinom n{n-i}$），最后再从前 $2n$ 个位置剩下的位置（共 $2n-i$ 个）中选出 $n$ 个位置（$\dbinom{2n-i}n$）即可。

```cpp
count2=2*C(n<<1,n)*fac[n]%mod*fac[n<<1]%mod;
long long tmp=fac[n]*fac[n]%mod*fac[n]%mod;
// 2n+1 ~ 3n 中有 i 个在 [n+1, 2n] 上
for(int i=0;i<=n;i++)
    count2-=tmp*C(n,i)%mod*C(n,n-i)%mod*C(2*n-i,n)%mod;
```

## 总结

记求得的操作次数 $=0$，操作次数 $\leq 1$，操作次数 $\leq 2$ 的情况数量以及情况总数分别为 $c_0,\ c_1,\ c_2,\ c_3$，那么容易知道答案为

$$
0\times c_0+1\times(c_1-c_0)+2\times(c_2-c_1)+3\times(c_3-c_2).
$$

时间复杂度 $\Theta(n)$。

```cpp
// 2023.05.31

#include<bits/stdc++.h>
using namespace std;
long long mod;
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
long long fac[3000001],invfac[3000001];
void initfac(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    invfac[N]=power(fac[N]);
    for(int i=N;i>=1;i--)
        invfac[i-1]=invfac[i]*i%mod;
}
long long C(int m,int n){
    if(n<0||m<0||n>m)return 0;
    return fac[m]*invfac[n]%mod*invfac[m-n]%mod;
}

int main(){
    int n;
    scanf("%d%lld",&n,&mod);
    initfac(n*3);
    long long count0=1,
        count1=2*fac[n<<1]-fac[n],
        count2=2*C(n<<1,n)*fac[n]%mod*fac[n<<1]%mod,
        count3=fac[n*3];
    long long tmp=fac[n]*fac[n]%mod*fac[n]%mod;
    // 2n+1 ~ 3n 中有 i 个在 [n+1, 2n] 上
    for(int i=0;i<=n;i++)
        count2-=tmp*C(n,i)%mod*C(n,n-i)%mod*C(2*n-i,n)%mod;
    long long answer=1*(count1-count0)+2*(count2-count1)+3*(count3-count2);
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

~~`partial_sort(p.begin(),p.end(),p.begin()+2*n);`~~

显然最坏的情况就是前面一次，后面一次，前面一次，所以答案不会超过 $3$。令 $s_i$ 为使用最多 $i$ 次操作可以排序的排列数，则答案为 $(s_1-s_0)+2(s_2-s_1)+3(s_3-s_2)=3s_3-s_2-s_1-s_0$。

然后我们就需要推一点式子。先上结论：

$$s_0=1,s_1=2(2n)!-n!,s_2=2n!(2n)!\binom{2n}{n}-n!^3\sum_{i=0}^n\binom ni^2\binom {n+i}i,s_3=(3n)!$$

$s_0$ 与 $s_3$ 显然，$s_1$ 考虑如果只用一次排序就能排好那么必定前或后 $n$ 个元素已经就位，那么剩下 $2n$ 个数随便排。

但是如果前后 $n$ 个元素都已经就位那么这个排列会被算两遍，减去即可。

$s_2$ 就比较难搞，首先我们类比 $s_1$，若两次排序就可排好那么一定 $1\sim n$ 的位置都不超过 $2n$（或者 $2n+1\sim 3n$ 的位置都大于 $n$）。

那么选位置 $\binom{2n}{n}$ 种方案，剩下两部分排列 $n!(2n)!$ 种方案，一共 $2n!(2n)!\binom{2n}{n}$。考虑去重，我们分成三个长度为 $n$ 的段考虑：枚举第一段中 $1\sim n$ 的个数 $i$，枚举第三段中 $2n+1\sim 3n$ 的个数 $j$，第一段中选位置与数字均为 $\binom ni$，第三段中选位置与数字均为 $\binom nj$，第二段中放入剩下的 $2n-i-j$ 个数字，选择位置 $\binom n{2n-i-j}\binom{2n-i-j}{n-j}=\binom n{n-i}\binom{i}{n-j}$。最后 $3n$ 个数分成五部分，每一部分分别排列方案数 $n!i!(n-i)!j!(n-j)!$。

然后我们列出来一个暴力式子：

$$\sum_{i=0}^n\sum_{j=0}^nn!i!(n-i)!j!(n-j)!\binom ni^2\binom nj^2\binom n{n-i}\binom{i}{n-j}$$

很哈人对吧，但是我们可以简单的用一点组合知识推出一个能算的东西：

$$
\begin{aligned}
&\sum_{i=0}^n\sum_{j=0}^nn!i!(n-i)!j!(n-j)!\binom ni^3\binom nj^2\binom{i}{n-j}\\
=&n!^3\sum_{i=0}^n\binom ni^2\sum_{j=0}^n\binom nj\binom{i}{n-j}\\
=&n!^3\sum_{i=0}^n\binom ni^2\binom{n+i}{n}
\end{aligned}
$$

然后就做完了，$\Theta(n)$。

---

## 作者：masonpop (赞：0)

较为基础的计数题。

首先可以发现至多 $3$ 次操作：按照 $1,2,1$ 的顺序进行操作一定可行。因为经过前两次操作，$[2n+1,3n]$ 内的数一定被放到后 $n$ 个位置了。再经过一次排序就可以成功了。故我们只需分别统计三种排列的个数。

* $f(p)=0$：

即已经有序，一个。记为 $ans_0=1$。

* $f(p)\leq 1$：

容易发现，这等价于前面 $n$ 个或者后面 $n$ 个已经归位，减去重复的后得到数量为 $2\times (2n)!-n!$，记为 $ans_1$。

* $f(p)\leq 2$：

这等价于数 $[1,n]$ 在前 $2n$ 个位置中或者 $[2n+1,3n]$ 在后 $2n$ 个位置中。

分别计算得到 $2\times C_{2n}^n\times (n!)\times (2n)!$。

这题的难点就在于重复情况，即 $[1,n]$ 在前 $2n$ 个位置中且 $[2n+1,3n]$ 在后 $2n$ 个位置中。

发现 $[1,n]$ 的占位情况对 $[2n+1,3n]$ 有多少个可选位置有影响。可以枚举前 $n$ 个位置中有 $i$ 个 $[1,n]$ 中的数，那么我们的问题分三步：给 $[1,n]$ 中的数选位置，给之后的数选位置，以及排列这些数。计算得到这部分答案是 $\sum\limits_{i=0}^n(C_n^i)^2\times C_{n+i}^n\times (n!)^3$。（看上去和某些题解的结论不一样，其实只是枚举方式的不同，实际这两个东西是相等的）

这样，我们终于得到了 $ans_2=2\times C_{2n}^n\times (n!)\times (2n)!-\sum\limits_{i=0}^n(C_n^i)^2\times C_{n+i}^n\times (n!)^3$

$f(p)\leq 3$：

显然就是全部 $(3n)!$ 个排列，记为 $ans_3$。

最后注意我们求出的 $ans_0,\cdots ans_3$ 是互相包含的，类似于前缀和的方式互相减减就行了。[代码](https://codeforces.com/contest/1768/submission/209241243)。

---

