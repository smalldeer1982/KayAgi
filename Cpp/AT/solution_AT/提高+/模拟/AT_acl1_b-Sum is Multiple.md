# Sum is Multiple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/acl1/tasks/acl1_b

整数 $ N $ が与えられます． 正の整数 $ k $ であって，$ (1+2+\cdots+k) $ が $ N $ の倍数になるもののうち， 最小のものを求めてください． なお，このような正の整数 $ k $ が必ず存在することは証明できます．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{15} $
- 入力は全て整数である．

### Sample Explanation 1

$ 1+2+\cdots+10=55 $ であり，これは確かに $ N=11 $ の倍数です． $ k\ \leq\ 9 $ で条件を満たすものは存在しないため，$ k=10 $ が答えになります．

## 样例 #1

### 输入

```
11```

### 输出

```
10```

## 样例 #2

### 输入

```
20200920```

### 输出

```
1100144```

# 题解

## 作者：whhsteven (赞：2)

$\text{Updated on 2023.02.14:}$ 感谢评论区老哥指出问题，现已修改。

---

记 $f(k) = 1 + 2 + \cdots + k = \dfrac12k(k+1)$。

首先，$f(2n)$ 一定是 $n$ 的倍数，所以一定有解。

$n \mathop{|} f(k)$，则 $2n \mathop{|} k(k+1)$。

设 $d$ 为 $k$ 和 $2n$ 的公因数，并记 $k^\prime = \dfrac k d,\ n^\prime = \dfrac{2n}{d}$。

现要求这个 $d$ 满足 $k + 1$ 是 $n^\prime$ 的倍数。这样的 $d$ 必定存在，因为 $d = \gcd(k, 2n)$ 总满足条件。

此时，下面的方程组成立：

$$\begin{cases}
k \equiv 0 &\pmod d \\
k \equiv -1 &\pmod{n^\prime}
\end{cases}$$

对于一个给定的 $d$，满足上面方程组的 $k$ 均满足 $n \mathop{|} f(k)$；对于一个给定的 $k$ 满足 $n \mathop{|} f(k)$，上面已指出必然存在一个 $d$ 使得上面方程组成立，即必然存在一个 $d$ 能找到这个 $k$。

所以，考虑枚举 $d$，解出对应方程组的最小正整数解，这些解中的最小即为所求的最小的 $k$。

$d$ 是 $2n$ 的因数，所以 $O(\sqrt n)$ 枚举即可。扩展欧几里得算法解出 $k$ 的最小正整数解的复杂度是 $O(\log n)$，而据 AT 官方题解，$2 \times 10^{15}$ 范围内的数因数个数不超过 $30720$，所以可以通过。

实现时要注意 long long 可能是不够的。我开了 __int128。

---

## 作者：良心WA题人 (赞：1)

## 前言

一开始没看出来是 exgcd 板子题，以为是像原根一样可以证明要算的值很小，然后就白给了很久。不过问题不大。

## 题意

给定 $n$，求满足 $n\mid\displaystyle\sum_{i=1}^{k}i$ 的最小的 $k$。

## 思路

先推式子。

$$n\mid\displaystyle\sum_{i=1}^{k}i$$
$$n\mid\dfrac{k\times(k+1)}{2}$$
$$2\times n\mid k\times(k+1)$$
这个东西可以找一个 $a,b$，使得

$$a\times b=2\times n$$

则
$$
\begin{cases}
k\equiv 0\mod a\\
k+1\equiv 0\mod b
\end{cases}$$

那么令 $k=a\times x$，则
$$a\times x\equiv -1\mod b$$

这就是很标准的同余方程的形式了。枚举 $2\times n$ 的约数，然后求一个最小的 $a\times x$ 就可以了。显然会爆 `long long`，要用 `__int128`。注意到 $2\times n-1$ 一定是一个解，所以可以将答案设为 $2\times n-1$，超出这个值直接退出，所以答案不会爆 `long long`。时间复杂度 $O(\sqrt n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans;
__int128 exgcd(__int128 a,__int128 b,__int128&x,__int128&y)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	__int128 g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
ll calc(ll a,ll b)
{
	__int128 x,y,g=exgcd(a,b,x,y);
	if((b-1)%g)
		return 1e18;
	assert(g==1);
	x=(x%b*(b-1)%b+b)%b;
	if(!x)
		x+=b;
	if(a*x>ans)
		return 1e18;
	return a*x;
}
int main()
{
	ll n;
	scanf("%lld",&n);
	if(n==1)
	{
		printf("1");
		return 0;
	}
	n*=2;
	ans=n-1;
	for(int i=1;1ll*i*i<=n;i++)
		if(!(n%i))
			ans=min(ans,min(calc(i,n/i),calc(n/i,i)));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：crimson000 (赞：1)


$$
\begin{array}{l} 
\because   n |(1+2+\cdots k)=n|\frac{k(k-1)}{2} \\
\therefore 2n|k(k-1)
\end{array} 
$$

将 $2n$ 分解质因数，得到 $a$ 和 $b$ ，使得 $a \times b = 2n$ 。

---

引理： $\forall k \in N^*,\gcd (k+1, k) = 1$ 。

- 证明：

当 $k = 1$ 时，显然成立。

当 $k > 1$ 时，由欧几里得算法( $\gcd(a, b) = \gcd(b, a \bmod b ) $ ) 得： $\gcd (k+1, k) = \gcd (k,1) = 1$。

得证。

---

因此，$k$ 和 $k+$1 所能提供的质因子一定不同。

假设 $a | k$ ， $b | (k+1)$ ，就能列出下面的式子：

$$
\begin{array}{l} 
  \left\{\begin{matrix} 
  k=ax \\
k+1=by
\end{matrix}\right.    
\end{array} 
$$

两式变换一下即得

$$
ax - by = 1
$$

用 exgcd 求解该方程组即可，$k$ 即为 $ax$ 的最小值。

---

- 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll __int128
// 一开始没开__int128直接WA了一堆

inline __int128 read()
{
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

void write(__int128 x)
{
    if(!x) return;
    write(x / 10);
    putchar(x % 10 + '0');
}

ll n, ans;

inline ll mul(ll a, ll b, ll p) 
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

// solve ax + by = c
ll solve(ll a, ll b, ll c)
{
    ll x, y;
    ll d = exgcd(a, b, x, y);
    if(c % d != 0) return 1e30;
    ll mod = b / d; //取到该方程组的最小正解
    x = mul((c / d % mod + mod) % mod, (x % mod + mod) % mod, mod);
    //加这么多mod是因为方程组解出来会出负数解

    return a * x;
}

int main()
{
    n = read();

    n <<= 1;
    ans = n - 1;

    //这里怕i*i直接炸掉就移了个项
    for(ll i = 2; i <= n / i; i ++ )
    {
        if(n % i == 0)
        {
            ll a = i, b = n / i;
            ll c = b - 1;   //这里我变换出的式子和上面不太一样，方程组为 ax-by=b-1
            ans = min(ans, solve(a, b, c));

            a = n / i, b = i;
            c = b - 1;
            ans = min(ans, solve(a, b, c));
        }
    }

    write(ans);
    
    return 20080113;
}
```

---

## 作者：sunkuangzheng (赞：0)

注意到题目所求式子即为 $k(k+1) \equiv 0 \pmod {2n}$。

显然 $k$ 和 $k+1$ 贡献的质因子是不同的，不妨对每个质因子分别考虑，对于每一个 $p^c$ 都要有 $k \bmod p^c = 0$ 或 $(k+1) \bmod p^c = 0$。

那直接枚举一个子集 $S$ 表示这个子集里的方程是 $k \bmod p^c = 0$ 而子集外面的方程是 $(k+1) \bmod p^c = 0$，这是标准的 CRT，使用 `atcoder::crt` 即可。

时间复杂度 $\mathcal O(\sqrt n + 2^w \log n)$，其中 $w = 13$，截至发这篇题解前还是洛谷最优解！111

---

## 作者：zzh0755 (赞：0)

## 小蒟蒻第一次写题解，请大佬们多多见谅。
移下项：$k(k+1)\equiv 0(\bmod2n) $。

显然 $k$ 和 $k+1$ 是互质的，所以 $k$ 和 $k+1$ 提供的素因子是完全独立的。因此我们考虑将 $2n$ 分成 $A×B$ ，只要存在 $A$ 和 $B$ 分别是 $k$ 和 $k+1$ 的因子，$k$ 就合法。

反过来，我们可以利用 $A$ 和 $B$ 求出 $k$ ：
$\begin{cases} k\equiv0\pmod{A}\\ k\equiv-1\pmod{B} \end{cases}$
 

即求解 $Ax+By=B-1$ ，求出  $x_{min}$ 
  就可以得到 $k_{min}=Ax_{min}$ ，使用 exgcd 即可。
```cpp
#include<bits/stdc++.h>//万能头万岁！
using namespace std;
typedef long double DB;typedef long long LL;

LL n,ans;

inline LL Mul(LL x,LL y,LL MOD) {return (x*y+MOD-(LL)((DB)x/MOD*y)*MOD)%MOD;}
LL exgcd(LL a,LL b,LL &x,LL &y){
    if (!b) {x=1;y=0;return a;}
    LL r=exgcd(b,a%b,y,x);y-=a/b*x;return r;
}
LL Solve(LL A,LL B,LL C){
    LL x,y,r=exgcd(A,B,x,y);if (C%r) return 1e18;
    LL T=B/r;x=Mul((C/r)%T,x%T,T);
    if ((DB)A*x>1e18) return 1e18;return A*x;
}
int main(){
    scanf("%lld",&n);n<<=1;ans=n-1;
    for (int S=sqrt(n),i=2;i<=S;i++)if (!(n%i)) ans=min(ans,Solve(n/i,i,i-1)),ans=min(ans,Solve(i,n/i,n/i-1));
    printf("%lld\n",ans);
    return 0;//完结撒花。
}
```


---

