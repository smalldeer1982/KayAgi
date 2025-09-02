# 「FAOI-R2」Paint

## 题目背景

小 Y 是一个胖子，他最爱下楼梯了，因为下楼梯很省力气，但是他却有强迫症。

由于刷漆工人 HG 的油漆不够，每一层台阶都只刷了一半——左边或右边，好让小 Y 下楼时不踩到油漆。（~~众人：这是什么逻辑？~~）

## 题目描述

整个楼梯共 $3^N$ 级台阶。

HG 刷漆的规律是：对于**从上到下**第 $I$ 级台阶，若 $V_3(I)$ 是奇数，则刷在左边，否则刷在右边。**$V_3(I)$ 的定义请见提示。**

小 Y 因为强迫症，要求自己不能踩到油漆。

现在他来求助你，他最少会踩到油漆多少次？

- 一次只能下一级台阶。
- 如果小 Y 站在当前台阶的左边，则他必须站在下一级台阶的右边，反之亦然。
- 如果油漆在当前台阶左边，那么需要站在当前台阶右边才算没踩到油漆，反之亦然。
- 小 Y 唯一可以控制的是：他在第 $1$ 级台阶上站在哪边。也就是说，小 Y 只有 $2$ 种下楼梯的方案供选择。

答案对 $10^9+7$ 取模。

### 形式化题意

给定三个 01 串 $A,B,C$，长度均为 $3^N$。字符串下标从 $1$ 开始。

其中：

- $A=\texttt{101010101\ldots101}$；
- $B=\texttt{010101010\ldots010}$；
- $C=\texttt{001001000\ldots}$；具体来说，第 $I$ 个字符为 $V_3(I) \bmod 2$。**$V_3(I)$ 的定义请见提示。**

记 $\operatorname{mc}(X,Y)$ 为字符串 $X$ 和 $Y$ 中匹配的字符的个数。

试求：

$$\min\{\operatorname{mc}(A,C),\operatorname{mc}(B,C)\}$$

答案对 $10^9+7$ 取模。

## 说明/提示

样例 $1$ 解释：

- $A=\texttt{101}$；
- $B=\texttt{010}$；
- $C=\texttt{001}$；
- $\operatorname{mc}(A,C)=2$；
- $\operatorname{mc}(B,C)=1$；
- $\min\{\operatorname{mc}(A,C),\operatorname{mc}(B,C)\}=1$。

------------

| 测试点编号 | $T \le$ | $N \le$ | 分值 |
| :-: | :-: | :-: | :-: |
| $1$ | $10$ | $10$ | $50$ |
| $2$ | $10^5$ | $10^{18}$ | $50$ |

对于 $100\%$ 的数据，$1 \le T \le 10^{5}$，$1 \le N \le 10^{18}$。

> **提示：** $V_3(X)$ 指 $X$ 中质因数 $3$ 的个数。例如，$V_3(14)=0$，$V_3(18)=2$。

## 样例 #1

### 输入

```
1
1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
494699
494699494699
494699494699494699```

### 输出

```
994161775
899186285
348815909```

# 题解

## 作者：封禁用户 (赞：11)

~~这个题目是一个数学题，打表可以发现答案是……~~

好了，言归正传。

下文设 $X_K$ 为字符串 $X$ 在 $N=K$ 时的值，字符串间的 $+$ 为 `C++/STL/string` 中的字符串拼接。

>设 $A_N$ 和 $B_N$ 中与 $C_N$ 匹配次数较少的字符串为 $G_N$（另一个为 $H_N$），则 $\operatorname{mc}(G_{N},C_{N})=\dfrac{3^N-1}{2}$，且 $G_N$ 和 $C_N$ 的最后一位一定不同。

**证明：**

首先，$N=1$ 时显然成立，即样例 $1$。

接下来，从 $N$ 推到 $N+1$：

>下面的性质很显然，证明不给了。
>
>$A_{N+1}=A_N+B_N+A_N$；
>
>$B_{N+1}=B_N+A_N+B_N$；
>
>$C_{N+1}=C_N+C_N+D_N$（$D_N$ 是 $C_N$ 改变最后一位，即 $\texttt{1}$ 变成 $\texttt{0}$，$\texttt{0}$ 变成 $\texttt{1}$ 后的字符串）。

可以发现，此时 $\operatorname{mc}(A_{N+1},C_{N+1})=\operatorname{mc}(A_{N},C_{N})+\operatorname{mc}(B_{N},C_{N})+\operatorname{mc}(A_{N},D_{N})$，$\operatorname{mc}(B_{N+1},C_{N+1})=\operatorname{mc}(B_{N},C_{N})+\operatorname{mc}(A_{N},C_{N})+\operatorname{mc}(B_{N},D_{N})$。

若 $\operatorname{mc}(G_{N},C_{N})=\dfrac{3^N-1}{2}$，且 $G_N$ 和 $C_N$ 的最后一位不同，则 $\operatorname{mc}(G_{N},D_{N})=\dfrac{3^N+1}{2}$。

而由于当 $G_N$ 与 $H_N$ 「合在一起」（每个位置两个字符）时，每位各出现了一个 $\texttt{0}$ 和一个 $\texttt{1}$（必有一个和 $D_N$ 对应位置匹配），因此 $\operatorname{mc}(G_{N},D_{N})+\operatorname{mc}(H_{N},D_{N})=3^N$。

也就是说，$\operatorname{mc}(H_{N},D_{N})=\dfrac{3^N-1}{2}$。

它们之间差 $1$，因此 $\operatorname{mc}(A_{N+1},C_{N+1})$ 与 $\operatorname{mc}(B_{N+1},C_{N+1})$ 之间也差 $1$（其余的抵消了）。

同理，$\operatorname{mc}(G_{N+1},C_{N+1})+\operatorname{mc}(H_{N+1},C_{N+1})=3^{N+1}$。

因此，$\operatorname{mc}(G_{N+1},C_{N+1})=\dfrac{3^{N+1}-1}{2}$（列方程组可得）。

此外，由于 $\operatorname{mc}(H_{N},D_{N})<\operatorname{mc}(G_{N},D_{N})$，因此 $\operatorname{mc}(G_{N+1},C_{N+1})$ 的展开式（指「可以发现」那一句中的公式）中的最后一项是 $\operatorname{mc}(H_{N},D_{N})$。

而由于 $D_N$ 与 $C_N$，$C_N$ 与 $G_N$，$G_N$ 与 $H_N$ 的最后一位都不同，因此 $D_N$ 与 $H_N$ 的最后一位也不同，即 $G_{N+1}$ 与 $C_{N+1}$ 的最后一位也不同。

**根据数学归纳法，得证。**

**也就是说，答案就是 $\dfrac{3^N-1}{2}$！**

std：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {
	ll x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const ll mod = 1000000007;
ll T;
inline ll power(ll a, ll b) {
	ll ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}
signed main() {
    T = read();
    while(T--) {
        ll x = read(); x %= mod - 1;
        ll a = power(3, x) - 1;
        printf("%lld\n", ((a & 1) ? a + mod : a) / 2);
    }
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：8)

咋都是找规律，来点暴力做法。

设 $f_i$ 表示 $n=i$ 时 $\text{mc}(A,C)$ 的值，$g_i$ 表示 $n=i$ 时 $\text{mc}(B,C)$ 的值，

设 $h_i=\begin{cases}1&i\equiv 1\pmod 2\\-1&i\equiv0\pmod 2\end{cases}$，

则 $f_i=2f_{i-1}+g_{i-1}+h_i,g_i=2g_{i-1}+f_{i-1}-h_i,h_i=-h_{i-1}$。

观察发现 $n$ 为奇数时答案为 $g_n$，$n$ 为偶数时答案为 $f_n$，矩阵加速即可。

```cpp
#include <cstdio>
#include <cstring>
#define M 1000000007
#define int long long
struct S
{
    int a[3][3];
    S() { memset(a, 0, sizeof a); }
    S operator*(S b)
    {
        S c;
        for (int i = 0; i < 3; ++i)
            for (int k = 0; k < 3; ++k)
                for (int j = 0; j < 3; ++j)
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % M;
        return c;
    }
} z, b;
S P(S x, int y)
{
    S q = x;
    for (--y; y; y >>= 1, x = x * x)
        if (y & 1)
            q = q * x;
    return q;
}
int T, n;
signed main()
{
    b.a[0][0] = b.a[1][1] = 2;
    b.a[0][1] = b.a[1][0] = b.a[2][0] = z.a[0][1] = z.a[0][2] = 1;
    b.a[2][1] = b.a[2][2] = M - 1;
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld", &n);
        S q = z * P(b, n);
        printf("%lld\n", q.a[0][n & 1]);
    }
    return 0;
}
```


---

## 作者：TheShuMo (赞：5)

# P10035 题解

## 题目分析

### 测试点1
由于数据范围可以直接暴力循环 $1$ 到 $3^N$ 来求出 $C$，统计其中和 $A$ 数列以及 $B$ 数列相同的个数取 $\min$ 并输出。

### 测试点2

由于 $N$ 最大可以到 $10^{18}$，这时候上面暴力的方法显然是无法完成的，考虑怎么用计算的方法算出此时的值。
![](https://pic.imgdb.cn/item/6593e716871b83018a7e9629.jpg)
如上图，其中红色点代表形如 $x \times 3^{N-2}$  且 $\gcd(x,3) = 1$。橙色点代表形如 $x \times 3^{N-3}$ 且 $\gcd(x,3) = 1$。

数点的个数，发现 $3^N$ 有一个，$3^{N-1}$ 有两个，$3 ^{N-2}$ 有 $2 \times 3$ 个，$3 ^{N-3}$ 有 $2 \times 3^2$ 个，继续往下推，相邻两个上图点中都有 $2$ 个形如 $x \times 3^{N-4}$ 的点，而这样的点就有 $2 \times 3^3$ 个。

显然有形如 $x \times 3^k$ 的点有 $2 \times 3^{N-1-k}$ 个，$k \neq N$。
知道了上述结论，就可以统计 $C$ 数列中奇数位上 $1$ 的个数和偶数位上 $1$ 的个数了。
以下用 $C_k$ 代表 $C$ 数列的第 $k$ 位。 
当 $N$ 是奇数时，$C_{3^N} = 1$。奇数位上的点是形如 $(2k+1) \times 3^p,k\in Z,p\in Z$，偶数位上的点是形如 $2k \times 3^p,k\in Z,p\in Z$。那么对于同一个 $p,p\neq N$，奇数位偶数位上的个数是相等的。
当且仅当 $p$ 为奇数时，$C_{x\times 3^p} = 1$，否则等于 $0$。

1. 奇数位为 $1$：先不考虑 $3^N$，那么就是 $3^1,3^3,3^5,\cdots,3^{N-2}$，它们各有 $2\times 3^{N-2},2\times 3^{N-4}，2\times 3^{N-6},\cdots,2 \times 3$ 个，用等比数列求和，可得共有 $S = 2 \times \frac{3^N-1}{9}$ 个，加上 $3 ^ N$ 那个点，共有 $S+1$ 个。
2. 奇数位为 $0$：奇数位共有 $\frac{3^N+1}{2}$ 个，因此共有 $\frac{3^N+1}{2} - S$ 个。
3. 偶数位为 $1$：共 $S$ 个，方法同1，只是少了一个 $3^N$。
4. 偶数位为 $0$：共 $\frac{3^N-1}{2} - S$ 个。

由于 $A$ 序列是奇零偶一，$B$ 序列是偶零奇一，故 $mc(A,C) = \frac{3^N+1}{2}$， $mc(B,C) = \frac{3^N-1}{2}$。最小值为 $\frac{3^N-1}{2}$。

当 $N$ 是偶数时，差别只在 $C_{3^N} = 0$。此时 $mc(A,C) = \frac{3^N-1}{2}$， $mc(B,C) = \frac{3^N+1}{2}$。最小值仍为 $\frac{3^N-1}{2}$。

  故只需要求出 $\frac{3^N-1}{2}$ 就好了。这只需要使用快速幂求 $2$ 关于 $10^9 + 7$ 的逆元，以及 $3^N$。复杂度 $O(T\log N)$，可以通过本题。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 100010;
const int mod = 1e9 + 7;
int ksm(int a,int b){
    int res = 1;
    while(b){
        if(b & 1) (res *= a) %= mod;
        a = a * a % mod;
        b = b >> 1;
    }
    return res;
}
signed main(){
    int t = read();
    int ny2 = ksm(2,mod - 2); // 费马小定理
    while(t--){
        int n = read();
        cout << (ksm(3,n) - 1 + mod) % mod * ny2 % mod << endl;
    }
}
```

---

## 作者：Big_Dinosaur (赞：3)

设 $f_i$ 为当 $n=i$ 时问题的答案。

先对于 $n>1$ 的情况分解，分解为三部分：前 $3^{n-1}$ 位，答案 $f_{n-1}$。中间 $3^{n-1}$ 位，可以看作 $A$ 与 $B$ 各取反，$C$ 与前一段一样。综合前两部分，这样选哪个都一样，答案就是 $3^{n-1}$。最后 $3^{n-1}$ 位，答案就是 $f_{n-1}$，可以手推一下。

考虑递推 $f_i$：当 $i=1$，$f_i=1$，可以看作 $\dfrac{3^1-1}{2}$；当 $i>1$，$f_i=f_{i-1}+3^{n-1}$，可算出：$f_2=f_{1}+3^1=\dfrac{3^1-1+2\times 3^1}{2}=\dfrac{3^2-1}{2}$，$f_3=f_{2}+3^1=\dfrac{3^2-1+2\times 3^2}{2}=\dfrac{3^3-1}{2}$。

最终，$f_n=\dfrac{3^n-1}{2}$。

用快速幂即可。
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
namespace rd{
  inline int r(){
  int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
  }
}
using namespace rd;
namespace Dino{
  int pw(int x,int y,int m){
    int a=1,b=x;while(y){
    	if(y&1)a=a*b%m;b=b*b%m;y>>=1;
    }
    return a;
  }
  void _(){
    int n=r(),t;while(n--){
    	t=r();
        cout<<(pw(3,t,mod)+mod-1)%mod*pw(2,mod-2,mod)%mod<<'\n';
    }
  }
}
signed main(){Dino::_();}
```

---

## 作者：modfish_ (赞：2)

## 思路
定义 $f(i)$ 表示满足 $V_p(I)=i$ 的数的个数。

显然 $f(N)=1$。

考虑 $f(N-1)$，在 $[3^{N-1},3^N]$ 中有 $3^1$ 个 $3^{N-1}$ 的倍数。但其中所有 $3^N$ 的倍数均不满足 $V_p(I)=N-1$，所以 $f(N-1)=3^1-1$。

考虑 $f(N-2)$，在 $[3^{N-2},3^N]$ 中有 $3^2$ 个 $3^{N-2}$ 的倍数。但其中所有 $3^{N-1}$ 的倍数均不满足 $V_p(I)=N-2$，所以 $f(N-2)=3^2-3^1$。

容易发现规律：

$$f(k)=3^{N-k}-3^{N-k-1}$$

设最终 $C$ 串中奇数位上为 $1$ 的数量为 $a$，偶数位上为 $1$ 的数量为 $b$，奇数位上为 $0$ 的数量为 $c$，偶数位上为 $0$ 的数量为 $d$。

容易发现所有满足 $V_p(I)=i$ 的数中，奇数、偶数各占一半。

所以当 $N$ 是偶数时：

$$a=\frac{f(1)}{2}+\frac{f(3)}{2}+\dots +\frac{f(N-1)}{2}$$

即：

$$a=\frac{3^{N-1}-3^{N-2}+3^{N-3}-3^{N-4}+\dots+3^1-1}{2}$$

稍作整理：

$$a=\frac{3^N}{2}-\frac{3^N-3^{N-1}+\dots+3^2-3^1+1}{2}$$

由乘法公式，有：

$$a=\frac{3^N}{2}-\frac{3^{N+1}+1}{8}=\frac{3^N-1}{8}$$

且：

$$b=a=\frac{3^N-1}{8}$$

在 $[1,3^N]$ 中，共有 $\frac{3^N+1}{2}$ 个奇数，$\frac{3^N-1}{2}$ 个偶数。

所以：

$$c=\frac{3^N+1}{2}-a=\frac{3^{N+1}+5}{8}$$

$$d=\frac{3^N-1}{2}-b=\frac{3^{N+1}-3}{8}$$

答案为：

$$\min\{a+d,b+c\}=\frac{3^N-1}{8}+\frac{3^{N+1}-3}{8}=\frac{3^N-1}{2}$$

类似地，当 $N$ 为奇数时，也能推出相同的结论。

所以最后答案就是 $\frac{3^N-1}{2}$。

给不会逆元的读者们的小知识：对于质数 $p$，在模 $p$ 意义下的除以 $2$ 可以等价于乘上 $p-p\bmod 2$，即 $2^{-1}\equiv p-p\bmod 2\pmod p$。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 1e9 + 7;

ll qpow(ll a, ll x){
	ll res = 1, bas = a;
	while(x){
		if(x & 1){
			res = res * bas % mod;
		}
		bas = bas * bas % mod;
		x = x >> 1;
	}
	return res;
}

int main(){
	int T;
	scanf("%d", &T);
	ll inv2 = mod - mod / 2;
	while(T --){
		ll n;
		scanf("%lld", &n);
		ll n3 = qpow(3, n);
		printf("%lld\n", (n3 + mod - 1) * inv2 % mod);
	}
	return 0;
}
```


---

## 作者：gjh72351 (赞：2)

~~莫名的做法~~

避开题目的本质。


------------


首先，我认为左侧刷漆台阶的数量可能与答案有关系，记 $num$ 为左侧刷漆台阶的数量，$ans$ 为答案。打表可得当 $N\in$ {$1,2,3,4,5$} 时，$num$ 的值分别为：$1,2,7,20,61$；$ans$ 的值分别为：$1,4,13,40,121$。

发现：

当 $N$ 为奇数时，$num$ 的值为上一个 $num$ 的值乘三加一，同时 $ans$ 的值为 $num$ 的二倍减一；

当 $N$ 为偶数时，$num$ 的值为上一个 $num$ 的值乘三减一，同时 $ans$ 的值为 $num$ 的二倍。

事实上关于 $num$ 本身的规律是显然的。考虑把台阶等分成三部分，当 $N$ 为奇数时分成的三段台阶最后一级涂在右侧，合并后第三段的最后一级涂在左侧，即乘三加一；当 $N$ 为偶数时同理。

而关于 $ans$ 与 $num$ 之间的关系的规律的证明超越了得到此题正解结论的难度 ~~赛场上不妨认为是不证自明的~~ ，附在最后。

那么问题转化成了：**如何快速计算一个数进行若干次乘三加一和乘三减一操作的结果。**

一个伟大的想法诞生了：~~**改造快速幂**~~


------------


基于倍增思想、快速幂算法、线段树 2 的 pushdown 原理，我们可以设计出如下方法：

第一步，把一次乘三加一的操作与一次乘三减一的操作合并，变形为乘九加二；

第二步，仿照线段树 2 的 pushdown 拆式子，并仿照快速幂倍增乘数与加数；

第三步，对 $N$ 为奇数即原操作次数为奇数的情况进行一次乘三减一的处理。

可以肯定该方法的正确性。~~（现在，笔者愿将该方法命名为加数快速幂）~~

详见代码：


------------

```
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
long long n,ans=1;
void ksm(long long x){	//1*3+1)*3-1)*3+1)*3-1)...
	long long cheng=9,jia=2;
	bool f=0;
	if(x&1)ans=0,x>>=1,f=1;
	else ans=0,x>>=1;
	while(x){
		if(x&1)ans=(cheng*ans%mod+jia)%mod;
		jia=(cheng+1)%mod*jia%mod,
		cheng=cheng*cheng%mod,
		x>>=1;
	}
	if(f)ans=(3*ans%mod+1)%mod;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		ksm(n);
		printf("%lld\n",n&1?(ans*2-1)%mod:ans*2%mod);
	}
	return 0;
}
```


------------

浅谈关于 $num$ 与 $ans$ 关系的证明：

欲证明此关系需要尝试用含 $num$ 的式子表示 $ans$。考虑左侧刷漆台阶中位于偶数级数的台阶数量 $a$，可以递推地得到 $a$ 的值为 $num$ 的一半（$num$ 为奇数时 $a$ 向下取整）。于是我们能够得到从左侧出发踩到的左侧刷漆台阶数量。不妨假设右侧奇数级数台阶全部刷漆，通过 $a$ 能够得到右侧避开油漆的台阶数量，进而得到踩到油漆的总次数即 $ans$。右侧同理，两值取较小者可得 $ans$ 的值恒为 $\dfrac{3^N-1}{2}$。我们居然得到了正解。。。现在考虑 $\dfrac{3^N-1}{2}$ 与 $num$ 的数量关系，根据平方差公式，式值与 $num$ 的递推式即若干次乘三加一和乘三减一操作的展开式是部分等价的，最后分类讨论得证。

~~（逃）~~

------------


完结敬礼！


---

## 作者：封禁用户 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10035)

~~讨厌的数据范围，害得我 WA 了。~~

比赛代码（$50$ 分）：

```cpp
#include <bits/stdc++.h>
const long long mod = 1e9 + 7;
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        long long m = (long long)(pow(3, n - 1)) % mod - 1;
        cout << (m / 2 * 3 % mod + 1) % mod << endl;
    }
    return 0;
}
```

很明显，$3^{10^{18}}$ 的数 `__int128` 都存不下。


计算一下：

- $N=1$，答案是 $1$。
- $N=2$，答案是 $4$。
- $N=3$，答案是 $13$。
- $N=4$，答案是 $40$。
- $N=5$，答案是 $121$。

算一算就能够发现，$f(1)=3^0$，$f(2)=3^0+3^1$，$f(3)=3^0+3^1+3^2$，$f(4)=3^0+3^1+3^2+3^3$，$f(5)=3^0+3^1+3^2+3^3+3^4$。

可以看出，$f(N)=3^0+3^1+3^2+\ldots+3^{N-1}$，也就是：

$$\sum^{n-1}_{i=0}3^i$$

按[等比数列求和公式](https://baike.baidu.com/item/%E7%AD%89%E6%AF%94%E6%95%B0%E5%88%97%E6%B1%82%E5%92%8C%E5%85%AC%E5%BC%8F/7527367?fr=ge_ala)求和后便是：

$$\frac{3^N-1}{2}$$
这是满分代码：

```cpp
#include <bits/stdc++.h>//万能头文件
#define int long long//int 做 long long
using namespace std;
const int MOD = 1e9 + 7;
int qpow(int a, int x) {//快速幂
    int sum = 1, ans = a;
    while (x) {
        if (x & 1/*这也是奇偶性判断*/) {
            sum = sum * ans % MOD;
        }
        ans = ans * ans % MOD;
        x /= 2;
    }
    return sum;
}
signed main() {//一定要使用 signed，否则会报错
    int T;
    cin >> T;
    int sum = MOD - MOD / 2;
    while (T--) {
    	int n;
    	cin >> n;
    	int m = qpow(3, n);
    	cout << (m + MOD - 1) * sum % MOD << endl;//不要忘了换行！
    }
    return 0;//好习惯
}
```

散会！

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10035)

~~乱搞~~总结出来的规律。

听说考试前写题解可以 RP++（虽然是期末考试）？

## 思路

找规律题。

先看看一些比较小的数的输出：

输入 $N=1$，输出 $1$。

输入 $N=2$，输出 $4$。

输入 $N=3$，输出 $13$。

输入 $N=4$，输出 $40$。

然后就不一一列举了，可以观察到，每次输入答案就是  $3^0+3^1+3^2+...+3^{N-1}$，用快速幂可以轻松解决。

```cpp
#include <iostream>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
const int M = 5e8 + 4;
int Pow(int x, int n) {
    int res = 1;
    while (n) {
        if (n & 1) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
signed main()
{
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = Pow(3, n);
        cout << (ans - 1) * M % MOD << endl;
    }
    return 0;
}
```


---

