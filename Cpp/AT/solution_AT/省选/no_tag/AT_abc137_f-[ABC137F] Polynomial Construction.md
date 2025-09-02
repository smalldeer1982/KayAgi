# [ABC137F] Polynomial Construction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_f

素数 $ p $ と、長さ $ p $ の $ 0 $ と $ 1 $ からなる整数列 $ a_0,\ \ldots,\ a_{p-1} $ が与えられます。

以下の条件を満たす $ p-1 $ 次以下の多項式 $ f(x)\ =\ b_{p-1}\ x^{p-1}\ +\ b_{p-2}\ x^{p-2}\ +\ \ldots\ +\ b_0 $ を一つ求めてください。

- 各 $ i $ $ (0\ \leq\ i\ \leq\ p-1) $ に対し、$ b_i $ は $ 0\ \leq\ b_i\ \leq\ p-1 $ なる整数
- 各 $ i $ $ (0\ \leq\ i\ \leq\ p-1) $ に対し、$ f(i)\ \equiv\ a_i\ \pmod\ p $

## 说明/提示

### 制約

- $ 2\ \leq\ p\ \leq\ 2999 $
- $ p $ は素数である。
- $ 0\ \leq\ a_i\ \leq\ 1 $

### Sample Explanation 1

$ f(x)\ =\ x\ +\ 1 $ は以下のように条件を満たします。 - $ f(0)\ =\ 0\ +\ 1\ =\ 1\ \equiv\ 1\ \pmod\ 2 $ - $ f(1)\ =\ 1\ +\ 1\ =\ 2\ \equiv\ 0\ \pmod\ 2 $

### Sample Explanation 2

$ f(x)\ =\ 0 $ も有効な出力です。

## 样例 #1

### 输入

```
2
1 0```

### 输出

```
1 1```

## 样例 #2

### 输入

```
3
0 0 0```

### 输出

```
0 0 0```

## 样例 #3

### 输入

```
5
0 1 0 1 0```

### 输出

```
0 2 0 1 3```

# 题解

## 作者：EastPorridge (赞：9)

一种很强的解法，和题解现有的都不同。

不会拉格朗日插值？不会二项式定理？不会拿费马小定理构造解？通通没关系。

### 题目分析：

题目让我们构造多项式 $f(x)= \sum_{i=0}^{p-1}b_i x^i$，满足 $0 \le b_i \le p-1,f(i) \equiv a_i \pmod p$ 的多项式系数 $b_i$。

我要把它变成前缀和形式，则有 

$$g(p-1)=\sum_{i=0}^{p-1} f(i)\equiv \sum_{i=0}^{p-1} a_i \pmod p$$

我们把 $g(p-1)$ 用 $b_i$ 表示出来，

$$g(p-1) = \sum_{i=0}^{p-1} (b_i \sum_{j=0}^{p-1}j^{i})$$

写到这里，不会写了，我们打个表试试，随机 $a_i$，规定 $p=13$。


![](https://cdn.luogu.com.cn/upload/image_hosting/el5gwdya.png)

发现一个很好玩的性质，$\sum_{i=0}^{p-1} a_i$ 和 $b_{p-1}$ 之间的关系好像不一般，随机生成的 $a_i$，若 $\sum_{i=0}^{p-1} a_i$ 相同，则 $b_{p-1}$ 总是相同，但 $b_{p-1}$ 的大小却不是单调的，它们俩之间有个**周期性**的一次函数的关系。

我决定把 $b_i$ 和 $\sum_{i=0}^{p-1} a_i$ 单独列出来，

$$\sum_{i=0}^{p-1} (b_i \sum_{j=0}^{p-1}j^{i}) \equiv \sum_{i=0}^{p-1} a_i \pmod p$$

因为在模的意义下，周期性可以解释，但这东西不像单调的，根据我们打表的结论，它跟 $0 \sim {p-2}$ 的式子都没关系，却跟 $p-1$ 的关系很大，所以我们猜测 $0 \sim {p-2}$ 所有是常数或者被模掉了。

$p$ 又是质数，又跟 $p-1$ 的关系大，恨不得跟着屏幕给你来两拳告诉你它是费马小定理。

我们猜测正整数 $i$ 取值 $[0,p-2]$ 的 $\sum_{j=0}^{p-1}j^{i}$ 都是 $p$ 的倍数，会被直接模掉；而 $p-1$ 遵循费马小定理，所以 $\sum_{j=0}^{p-1}j^{p-1} \equiv p-1 \pmod p$。

直接把原式写成：

$$\sum_{i=0}^{p-1} a_i \equiv (p-1) \times b_{p-1} \pmod p$$

带入打的表检验，是对的，我们猜对了。

证明这个东西也很简单，直接设 $g$ 为 $p$ 的原根，原式变成 $\sum_{j=0}^{p-1} (g^i)^j$，直接对它等比求和就可以了。

然后就有，

$$\sum_{i=0}^{p-1} a_i \times i^j \equiv (p-1)\times b_{p-1-j} \pmod p$$

我们可得 $b_0= a_0$，这题就做完了。

### Code.

```cpp
#include<cstdio>
#include<iostream>
const int N=3010;
int a[N],b[N],p;
int main()
{
	scanf("%d",&p);
	for(int i=0;i<p;i++) scanf("%d",a+i); b[0]=a[0];
	for(int i=0;i<p-1;i++) 
		for(int j=0;j<p;j++) 
			b[p-1-i]=(b[p-1-i]+a[j])%p,a[j]=a[j]*j%p;
	printf("%d ",b[0]); 
	for(int i=1;i<p;i++) printf("%d ",b[i]*(p-1)%p);
	return 0;
}
```

---

## 作者：Saliеri (赞：5)

隔壁大佬 @WAPER420 好像要借此给我们讲插值？等讲了再补插值做法。

___

Tips: 本篇题解更多侧重于**如何想出做法**，而非做法本身。~~虽然我当时也没想出来~~

考虑一下题目的要求。我们的目标是什么？

目标是在同余系下构造一个对象使之同时满足若干个限制。

稍微联想一下？这个目标像什么？（先别看答案）

没错，**中国剩余定理**。

中国剩余定理的构造方式是什么？

稍微总结起来就是：对每一个式子分别构造一个量，使每一个量**只对对应的一个式子产生贡献**，再将所有的量求和。

在中国剩余定理中，我们找到的量是 $a_i$,$(\prod_i m_i)/m_i$ 与后者逆元的积。除了 i 以外的所有求和项都因 $(\prod_i m_i)/m_i$ 的存在而变为0，逆元则修正了在 i 中应有的贡献。

推广这个想法至本题，我们要找寻一个函数 $g_k(i)$,使 $\forall j\neq k,g_k(j) \equiv 0$,且 $g_k(k) \equiv 1 (\operatorname{mod} p)$。

问题转化为寻找一个同余系下的**半永久的** $0$，或者$1$.

质数同余系下的 $1$，便可以非常简单的联想到——**费马小定理**：$\forall n\in N^*,n^{p-1}\equiv1(\operatorname{mod} p)$。

g 的构造也就显而易见了：

$$g_k(i) = 1-(i-k)^{p-1}$$

完美满足上述的条件。

$Ans = \sum_{a_k = 1} g_k$。

系数可以二项式定理暴力展开。

___

代码 ：

```cpp
#include <cstdio>
const int maxn = 3005;
int p,cnt,a[maxn],jc[maxn],inv[maxn];
int ans[maxn];
int Inv(int a){
	int base = a,ans = 1,x = p-2;
	while(x){
		if(x&1)ans = ans*base%p;
		base = base*base%p;
		x >>= 1;
	}return ans;
}
int C(int n,int m){return jc[n]*inv[m]%p*inv[n-m]%p;}
int main(){
	scanf("%d",&p);
	for(int i=0;i<p;++i)scanf("%d",&a[i]),cnt += a[i];
	jc[0] = inv[0] = 1;
	for(int i=1;i<p;++i)jc[i] = jc[i-1]*i%p;
	inv[p-1] = Inv(jc[p-1]);
	for(int i=p-1;i>=2;--i)inv[i-1] = inv[i]*i%p;
	for(int i=0;i<p;++i)
		if(a[i]){
			int res = 1;
			for(int j=0;j<p;++j){
				ans[p-1-j] = (ans[p-1-j] + res)%p;
				res = res*(p-i)%p;
			}
		}
	for(int i=0;i<p;++i){
		ans[i] = ans[i]*C(p-1,i)%p;
		if(i == 0)ans[i] = (ans[i]-cnt+p)%p;
		if(ans[i])ans[i] = p-ans[i];
	}
	for(int i=0;i<p;++i)printf("%d ",ans[i]);
	return 0;
}
```

妙。


---

## 作者：JWRuixi (赞：3)

学校模拟赛出这道题，直接祭了……

- 题意

给出长度为 $p$ 的 $01$ 序列 $a$, 构造 $f(x)=\sum\limits_{i=0}^{p-1} b_i x^i$，满足 $f(i) \equiv a_i \pmod{p}$。

- 分析

我们想要在给定时间内求出 $a$，就必须将每一个 $a_i$ 单独分离出来，于是想到中国剩余定理的套路。

即构造函数 $g(x)=1-(i-x)^{p-1}$，由于费马小定理告诉我们 $a^{p-1} \equiv 1 \pmod{p}$，所以只有 $g(i) \equiv 1 \pmod{p}$，其余数余 $0$。

所以答案实际上是 

$$\sum\limits_{i=0}^{p-1} [a_i=1] (1-(x-i)^{p-1})$$

$$=\sum a_i - \sum\limits_{i=0}^{p-1}[a_i=1]\sum\limits_{j=0}^{p-1}\dbinom{p-1}{j} (-i)^{p-j-1} x^{j}$$

$$=(\sum a_i - p) - \sum\limits_{i=0}^{p-1}[a_i=1]\sum\limits_{j=0}^{p-2}\dbinom{p-1}{j} (p-i)^{p-j-1} x^{j}$$

由于对于每个 $x^{j}$，组合数系数恒为 $\dbinom{p-1}{j}$，所以可以之后统一乘上再取负。

- code

```cpp
#include <bits/stdc++.h>
using namespace std;
//
namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
//
using IO::read;
using IO::write;
//
const int maxn = 3005;
int p, cnt, a[maxn], fac[maxn], inv[maxn], ans[maxn], ifac[maxn];
//
int c (int n, int m) {
	return fac[n] * ifac[m] % p * ifac[n - m] % p;//组合数 
}
//
int main () {
	p = read();
	for (int i = 0; i < p; i++) a[i] = read(), cnt += a[i];
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i < p; i++) fac[i] = fac[i - 1] * i % p, inv[i] = (p - p / i) * inv[p % i] % p;
	ifac[0] = 1;
	for (int i = 1; i < p; i++) ifac[i] = ifac[i - 1] * inv[i] % p;
	for (int i = 0; i < p; i++) {
		if (a[i]) {
			int res = 1;
			for (int j = 0; j < p; j++) {
				ans[p - 1 - j] = (ans[p - 1 - j]  + res) % p;
				res = res * (p - i) % p;//(p - i) ^ j
			}
		}
	}
	for (int i = 0; i < p; i++) {
		ans[i] = ans[i] * c(p - 1, i) % p;//统一乘系数 
		if (i == 0) ans[i] = (ans[i] - cnt + p) % p;//此处先取负，下面再改回来 
		if (ans[i]) ans[i] = p - ans[i];//取负 
	}
	for (int i = 0; i < p; i++) write(ans[i]), putchar(' ');
} 
```

---

## 作者：win114514 (赞：2)

明明有最厉害最好想的插值做法，怎么没有人写呢。

### 思路

考虑 $n$ 个点可以确定一个 $n-1$ 次多项式。

如何确定。

令 $l_i(x)=\prod_{j\not =i}\frac{(x-x_j)}{(x_i-x_j)}$。

可以发现这个多项式在 $x=x_i$ 时值为一，在 $x=x_j(j\not = i)$ 时值为零。

那么就有：

$$
F(x)=\sum_{i=0}^{i<n}y_il_i(x)
$$

容易发现这个多项式恰好满足上面的条件，当然，这就是拉格朗日插值。

如何得到这个多项式？

可以先求出：

$$
G(x)=\prod(x-x_i)
$$

发现：

$$
l_i(x)=\frac{G(x)}{(x-x_i)k_i}
$$

其它的是一个常数所以和起来写成 $k_i$ 即可。

那么就可以 $O(n^2)$ 求解了。

### 思路

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int mod;

inline int power(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod, y /= 2;
  }
  return res;
}

inline vector<int> lagrange(const vector<int> &x, const vector<int> &y) {
  int n = x.size();
  vector<int> a(n + 1, 0), f(n, 0);
  a[0] = 1;
  auto add = [&](int x) {
    for (int j = n; j >= 1; j--)
      a[j] = (a[j - 1] - a[j] * x) % mod;
    a[0] = -a[0] * x % mod;
  };
  for (int i = 0; i < n; i++) add(x[i]);
  for (int i = 0; i < n; i++) {
    if (x[i] == 0) {
      for (int j = 0; j <= n; j++) a[j] = a[j + 1];
      a[n] = 0;
    } else {
      int iv = power(x[i], mod - 2);
      a[0] = -a[0] * iv % mod;
      for (int j = 1; j <= n; j++) {
        a[j] = a[j] - a[j - 1];
        a[j] = -a[j] * iv % mod;
      }
    }
    int s = 1;
    for (int j = 0; j < n; j++)
      if (i != j) s = s * (x[i] - x[j]) % mod;
    s = power(s, mod - 2) * y[i] % mod;
    for (int j = 0; j < n; j++)
      f[j] = (f[j] + a[j] * s) % mod;
    add(x[i]);
  }
  for (int i = 0; i < n; i++) f[i] = (f[i] % mod + mod) % mod;
  return f;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);

  vector<int> a, b, f;

  cin >> mod;
  for (int i = 1, x; i <= mod; i++) {
    cin >> x;
    a.push_back(i - 1);
    b.push_back(x);
  }
  f = lagrange(a, b);
  for (int i = 0; i < mod; i++)
    cout << f[i] << " \n"[i == mod - 1];

  return 0;
}
```

---

## 作者：TSY48 (赞：2)

**解题思路**

考虑费马小定理，构造函数 $g(x)=(x-i)^{p-1}$ ，则：

$$
g(x) = \begin{cases}
  0 & x = i \\
  1 & x \ne i \\
\end{cases}
$$
根据这个，可以推出：
$$
f(x) =\sum_{i=0}^{p-1}g(i) = \sum_{i=0}^{p-1}(-a_i \times (x-i)^{p-1}+a_i)
$$
易证这是满足条件的。则 $f(x)$ 是满足条件的构造。

**代码实现**

按照 $i=0,1,2,\dots,p-1$ 对 $g(i)$ 用二项式定理展开即可。

AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define pf push_front
#define m_p make_pair
#define str string
#define lowbit(x) (x&(-x))
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
//typedef __int128 it;
const int Maxn=3000+10;
const int inf=0x3f;
int p;
int C[Maxn][Maxn];
int a[Maxn],b[Maxn];
inline void init(){
    C[0][0]=1;
    for(int i=1;i<p;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
        }
    }
}
int main()
{
    scanf("%d",&p);
    init();
    for(int i=0;i<p;i++){
        scanf("%d",&a[i]);
        if(!a[i]) continue;
        int f[Maxn]={1},now[Maxn]={};
        for(int j=1;j<p;j++) f[j]=(f[j-1]*i)%p;
        for(int j=0;j<p;j++){
            if((p-j)&1) now[j]=(C[p-1][j]*f[p-1-j]%p);
            else now[j]=-(C[p-1][j]*f[p-1-j]%p);
        }
        for(int j=0;j<p;j++) b[j]=(b[j]-now[j]+p)%p;
        b[0]=(b[0]+1)%p;
    }
    for(int i=0;i<p;i++) printf("%d ",b[i]);
    return 0;
}
```

---

## 作者：Rhapsodia (赞：1)

构造题，瞪眼一看是个插值，可惜模拟赛中打插值不现实，考虑其他构造。

想到利用 Fermat 小定理，可以构造出一个函数 $g(x)=(x-i)^{P-1}$ ，使得

$ g(x)=\left\{
\begin{aligned}
0 \quad  x=i\\
1 \quad  x \neq i\\
\end{aligned}
\right.
$

我们接下来在草稿纸上计算一点点，就可以得出如下式子：

$f(x)=\sum^{i=0}_{P-1}(-a_i*(x-i)^{P-1}+a_i)$ .

$f(x)$ 当且仅当 $a_i=1, x=i$ 时值为 $1$ ，这个构造是满足题目要求的。

按照构造式子输出即可，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int p, a[3010], b[3010], c[3010][3010];

int main() 
{
    cin >> p;
    for (int i = 0; i < p; i++) 
	{
        c[i][0] = 1;
        for (int j = 1; j <= i; j++) 
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
    }
    for (int i = 0; i < p; i++) 
	{
        cin >> a[i];
        if (a[i] != 0) 
		{
            int d[3003] = {};
			int e[3010] = {1};
            for (int j = 1; j < p; j++) 
				e[j] = e[j - 1] * i % p;
            for (int j = p - 1; j >= 0; j--) 
			{
                if ((j + p) % 2 == 0) 
					d[j] = -(c[p - 1][j] * e[p - 1 - j] % p);
                else 
					d[j] = c[p - 1][j] * e[p - 1 - j] % p;
            }
            for (int j = 0; j < p; j++) 
				b[j] = (b[j] + p - d[j]) % p;
            b[0] = (b[0] + 1) % p;
        }
    }
    for (int i = 0; i < p; i++) 
		cout << b[i] << " ";
}
```

---

## 作者：crn1 (赞：1)

## 题目大意
给出一个长度为 $p$ 的 $01$ 序列 $a_0,\ldots,a_{p-1}$，构造一个多项式 $f(x)=\sum_{i=0}^{p-1}b_ix^i$ 满足 $0\leq b_i\leq p-1$ 且 $f(i)\equiv a_i\ (\mathrm{mod}\ p)$，输出这个多项式的系数。

## 前置知识
- 费马小定理
- 二项式定理

## 题解
根据费马小定理： $a^{p-1}\equiv1\ (\mathrm{mod}\ p)$，对于任意 $i\ (0\leq i\leq p-1)$，$1-(x-i)^{p-1}\ (\mathrm{mod}\ p)$ 值为 $1$ 当且仅当 $x=i$，否则为 $0$。于是对于每个 $a_i=1$ 累加起来，只会对 $f(i)$ 的取值有影响，二项式定理展开 $(x-i)^{p-1}$ 即可。

$$f(x)=\sum_{i=0}^{p-1}[a_i=1](1-(x-i)^{p-1})=\sum_{i=0}^{p-1}[a_i=1](1-\sum_{j=0}^{p-1}\binom{p-1}{j}(-i)^jx^{p-1-j})$$

## 代码
```cpp
#include <cstdio>

const int N = 3005;
int p, a[N], b[N], fac[N], iv[N], ivf[N];

int bin(int n, int m) { // 组合数
    if (n < m) return 0;
    if (m == 0) return 1;
    return fac[n - m + 1] * ivf[m] % p;
}

int main(void) {
    scanf("%d", &p);
    for (int i = 0; i < p; i++) scanf("%d", a + i);
    iv[1] = ivf[0] = ivf[1] = 1, fac[p - 1] = p - 1;
    for (int i = p - 2; ~i; i--) fac[i] = fac[i + 1] * i % p;
    for (int i = 2; i < p; i++) iv[i] = (p - p / i) * iv[p % i] % p;
    for (int i = 2; i < p; i++) ivf[i] = ivf[i - 1] * iv[i] % p;
    for (int i = 0; i < p; i++) {
        if (!a[i]) continue;
        b[0] = (b[0] + 1) % p;
        for (int j = 0, x = 1; j < p; j++, x = x * (p - i) % p)
            b[p - 1 - j] = (b[p - 1 - j] - bin(p - 1, j) * x % p + p) % p; // 1 - (x - i) ^ (p - 1)
    }
    for (int i = 0; i < p; i++) printf("%d ", b[i]);
    return 0;
}
```

---

## 作者：VERACITY (赞：1)

~~在下无才，只得讲得俗一些~~
## 题意
给出长为 $p$ 的 $01$ 子串，使得 $f(x)= \displaystyle\sum_{i=0}^{p-1} b_ix^i$，且 $f(x) \equiv a_x\pmod p$，$0 \leq b_x \leq p-1$。
         
## 前置
先说 CRT 的剥离思想。简单来讲就是通过构造多个式子，将原来的多个要求剥离开来，消除原要求的影响使最后求得的答案满足所有的原要求。推广至本题，我们可以对每一个式子分别构造一个量，使此式子只对对应要求产生影响，最后答案即可通过求和得出。

## 思路
由剥离思想得，在 $a_x = 1$ 时构造一个函数 $g(i)$ 使 $i = x$ 时 $g(i) = 1$，$i \not = x$ 时 $g(i)=0$。这样使求和后只对 $f(x)$ 产生影响。      
由于题目要求是在模意义下，且值为 $1$，啊非常快的就能想到用费马小定理构造出 $g(i) = 1 - (i-x)^{p-1}$，后面的 $(i-x)^{p-1}$ 用二项式定理展开得 $\displaystyle\sum_{j=0}^{p-1} \binom{p-1}{j}i^{p-j-1}(-x)^i$。   

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mx=1e4;
ll p,cnt,a[mx],fac[mx],inv[mx],ans[mx];
ll ksm(int x)
{
	ll res=x,ans=1,k=p-2;
	while(k)
	{
		if(k&1)ans=ans*res%p;
		res=res*res%p,k>>=1;
	}
	return ans;
}
ll C(ll n,ll m){return fac[n]*inv[m]%p*inv[n-m]%p;}
//乘法逆元求组合数 
int main()
{
	cin >> p;
	for(int i=0;i<p;i++){cin >> a[i];cnt+=a[i];}
	fac[0]=inv[0]=1;
	for(int i=1;i<p;i++) fac[i]=fac[i-1]*i%p;
	inv[p-1]=ksm(fac[p-1]);
	for(int i=p-1;i>1;i--) inv[i-1]=inv[i]*i%p;
	 
	for(int i=0;i<p;i++)
		if(a[i])
		{
			int res=1;
			for(int j=0;j<p;j++)
				ans[p-j-1]=(ans[p-j-1]+res)%p,res=res*(p-i)%p;
		}
	for(int i=0;i<p;i++)
	{
		ans[i]=ans[i]*C(p-1,i)%p;
		if(!i) ans[i]=(ans[i]-cnt+p)%p;
		if(ans[i]) ans[i]=p-ans[i];
		cout<<ans[i]<<" ";
	}
   	//此处求法具体可参考原来各位大佬的题解
	return 0;
}
```

---

## 作者：_Yonder_ (赞：0)

注意到 $0\le a_i\le 1$ 且 $p$ 为质数，考虑费马小定理。

构造出函数 $f(x)=\displaystyle\sum^{p-1}_{i=0}(a_i-a_i\times (x-i)^{p-1})$。

对每个 $i$ 用二项式定理展开求系数即可。

---

