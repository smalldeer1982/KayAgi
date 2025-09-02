# Sky Full of Stars

## 题目描述

On one of the planets of Solar system, in Atmosphere University, many students are fans of bingo game.

It is well known that one month on this planet consists of $ n^2 $ days, so calendars, represented as square matrix $ n $ by $ n $ are extremely popular.

Weather conditions are even more unusual. Due to the unique composition of the atmosphere, when interacting with sunlight, every day sky takes one of three colors: blue, green or red.

To play the bingo, you need to observe the sky for one month — after each day, its cell is painted with the color of the sky in that day, that is, blue, green or red.

At the end of the month, students examine the calendar. If at least one row or column contains only cells of one color, that month is called lucky.

Let's call two colorings of calendar different, if at least one cell has different colors in them. It is easy to see that there are $ 3^{n \cdot n} $ different colorings. How much of them are lucky? Since this number can be quite large, print it modulo $ 998244353 $ .

## 说明/提示

In the first sample any coloring is lucky, since the only column contains cells of only one color.

In the second sample, there are a lot of lucky colorings, in particular, the following colorings are lucky:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF997C/ac5b00cad39330de8487d369f95c472d2789d588.png)While these colorings are not lucky:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF997C/d7e778adcf49c4573cc1d5ca5e208443325ff00a.png)

## 样例 #1

### 输入

```
1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
63
```

## 样例 #3

### 输入

```
3
```

### 输出

```
9933
```

# 题解

## 作者：Rachel_in (赞：35)

考虑容斥：

答案的方案数为：
$$
\sum_{i,j=0,i+j>0}^{n}C_n^i C_n^j \times (-1)^{i+j+1}\times f(i,j)
$$
其中$i$表示至少选$i$行颜色相同，j表示至少选$j$列颜色相同，$(-1)^{i+j+1}$为容斥系数(选奇数个就加入答案，选偶数个就减去答案)。$f(i,j)$表示至少选$i$行颜色相同，$j$列颜色相同的方案数。

#### 现在我们就要考虑如何求 $f(i, j)$:

首先考虑其中**i或j有一个为0的情况**(下图中$j=0$)

![](https://cdn.luogu.com.cn/upload/pic/64324.png)

那么方案数为:
$$
3^i \times 3^{n*(n-i)}
$$
解释：其中$i$行，每行都有3种颜色可以选择，所以是$3^i$,剩下空白的块每块也有三种颜色可以选择，也就是$3^{n*(n-i)}$

若$i=0$ 时同理。

**再考虑当$i$和$j$都不为零的情况**(如下图$i=2$,$j=3$)：

![](https://cdn.luogu.com.cn/upload/pic/64326.png)

方案数为:

$$3*3^{(n-i)*(n-j)}$$


其中有颜色的块只有三种颜色可以选择，因为他们行与列之间相互制约。剩下的无颜色的块每块有三种颜色可以填，也就是 $3^{(n-i)*(n-j)}$

------

整理一下：

$$f(i,j)=\begin{cases}3^i \times 3^{n(n-i)}&j=0\\3^j \times 3^{n(n-j)}&i=0\\3\times 3^{(n-i)(n-j)}&i>0,j>0 \end{cases}$$

在得出$f(i,j)$的情况下我们根据最上面的式子计算时间复杂度是$O(n^2)$的，这个复杂度是不能接受的。

$$\sum_{i,j=0,i+j>0}^{n}C_n^i C_n^j \times (-1)^{i+j+1}\times f(i,j)$$

考虑优化。

由于$i=0$或$j=0$时的$f(i,j)$函数与众不同，所以我们考虑将它们单独拆出来算。

也就是:

$$2*\sum_{i=1}^{n}C_n^i \times (-1)^{i+1} 3^i \times 3^{n(n-i)}$$

剩下我们需要处理出:

$$\sum_{i=1}^n \sum_{j=1}^n C_n^iC_n^j 3^{(n-i)(n-j)+1} \times (-1)^{(i+j+1)}$$

化式子：

$$\sum_{i=1}^n \sum_{j=1}^n C_n^iC_n^j3^{n^2+1}\cdot 3^{-in}\cdot3^{-jn}\cdot3^{ij}\cdot(-1)^i\cdot(-1)^j\cdot(-1)$$

把能提的先提出来:

$$(-1)\cdot3^{n^2+1}\cdot\sum_{i=1}^n \sum_{j=1}^n C_n^iC_n^j 3^{-in}\cdot3^{-jn}\cdot3^{ij}\cdot(-1)^i\cdot(-1)^j$$

然后分个组：

$$(-1)\cdot3^{n^2+1}\cdot\sum_{i=1}^n C_n^i3^{-in}\cdot(-1)^i\sum_{j=1}^n C_n^j \cdot3^{-jn}\cdot(-1)^j\cdot3^{ij}$$

发现如果没有这个$3^{ij}$就可以$O(nlogn)$求出了，所以瓶颈在于这个$3^{ij}$里。我们需要把它化进一个式子里求，我们合并右边：

$$(-1)\cdot3^{n^2+1}\cdot\sum_{i=1}^n C_n^i3^{-in}\cdot(-1)^i\sum_{j=1}^n C_n^j (-3^{-n+i})^j$$

根据二项式定理:

$$(a+b)^n=\sum_{i=0}^nC_n^ia^ib^{n-i}$$

我们这里把$a=1$,$b=(-3^{-n+i})$代入：

$$(1+(-3^{-n+i}))^n=\sum_{i=0}^nC_n^i 1^i(-3^{-n+i})^{n-i}$$

原式$j$是从$1$开始的，所以我们只需减去$j=0$时候的值即可，所以式子被我们化成了这样:

$$(-1)\cdot3^{n^2+1}\cdot\sum_{i=1}^n C_n^i3^{-in}\cdot(-1)^i\cdot[(1-3^{-n+i})^n-1]$$

使用快速幂，时间复杂度$O(nlogn)$

**注意**：由于常数较大，建议先预处理出3的各个幂，以及$3^n$的各个幂。

---

## 作者：command_block (赞：26)

**题意**：有一个 $n\times n$ 的正方形网格，用三种颜色染。

求有多少种方案使得**至少**一行或一列是同一种颜色。

答案对 $998244353$ 取模，$n\leq 10^6$，时限 $\texttt{4s}$。

-----

> upd 2025.2.27：重新排版。

令：

- $F(i,j)$：**钦定**有 $i$ 行 $j$ 列是同种颜色，**其余任意**的方案数。

- $G(i,j)$：为**恰好**有 $i$ 行 $j$ 列是同种颜色的方案数。

答案：$3^{n^2}-G(0,0)$。

由组合意义易得
$$
F(x,y)=\sum\limits_{i=x}^n\sum\limits_{j=y}^n\dbinom{i}{x}\dbinom{j}{y}G(i,j)
$$
两个维度独立，施加高维二项式反演（两个维度的反演系数简单相乘）
$$
\begin{aligned}
G(x,y)
&=\sum\limits_{i=x}^n\sum\limits_{j=y}^n(-1)^{i+j-x-y}\dbinom{i}{x}\dbinom{j}{y}F(i,j)\\
G(0,0)
&=\sum\limits_{i=0}^n\sum\limits_{j=0}^n(-1)^{i+j}F(i,j)
\end{aligned}
$$
这和容斥的结论一致。

------------

接下来考虑如何快速计算 $F(i,j)$，需要分类讨论。

- $i,j\neq 0$：所有被钦定的行和列**必须是同种颜色**。
  $$
  F(i,j)=\dbinom{n}{i}\dbinom{n}{j}\cdot 3\cdot 3^{(n-i)(n-j)}
  $$
  即：选定行列 x 钦定颜色 x 其余自由部分

- $j=0$：被钦定的行不必是同种颜色。
  $$
  F(i,0)=\dbinom{n}{i}\cdot3^i\cdot3^{n(n-i)}
  $$
  即：选定行 x 钦定颜色 x 其余自由部分

  （$i=0$ 同理）

- $i=j=0$：完全自由，$F(0,0)=3^{n^2}$。

------------

回忆：
$$
G(0,0)=\sum_{i=0}^n\sum_{j=0}^n(-1)^{i+j}F(i,j)
$$
根据上述讨论，分三部分求和。

- **第一部分**：两个参数均不为 $0$。

$$
\begin{aligned}
S_1
&=\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}F(i,j)\\
&=\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}\dbinom{n}{i}\dbinom{n}{j}3^{(n-i)(n-j)+1}\\
&=3^{n^2+1}\sum_{i=1}^n\dbinom{n}{i}(-1)^i3^{-in}\,\boxed{\sum_{j=1}^n\dbinom{n}{j}(-1)^{j}3^{j(i-n)}}\\
&=3^{n^2+1}\sum_{i=1}^n\dbinom{n}{i}(-1)^i3^{-in}\left((1-3^{i-n})^n-1\right)
\end{aligned}
$$

快速幂就可以 $O(n\log n)$ 计算了。

- **第二部分**：一个参数为 $0$。

$i,j$ 为 $0$ 本质相同，只统计 $j=0$ 的情形，然后将贡献翻倍即可。
$$
\begin{aligned}
S_2&=2\sum_{i=1}^n(-1)^{i}\dbinom{n}{i}^{i+n(n-i)}\\
&=2\cdot3^{n^2}\,\boxed{\sum_{i=1}^n\dbinom{n}{i}(-1)^{i}3^{i(1-n)}}\\
&=2\cdot3^{n^2}\left((1-3^{1-n})^n-1\right)\\
\end{aligned}
$$

- **第三部分**：两个参数均为 $0$。$S_3=3^{n^2}$。

最终 $G(0,0)=S_1+S_2+S_3$。

总复杂度 $O(n\log n)$。

---

## 作者：naive_wcx (赞：6)

这题写的我很不爽，写一篇题解泄愤。。。
# Description
有一个$n*n$的网格和三种颜色，问有多少种染色方案，使得至少一行或者一列颜色一样。$n≤10^6$
# Solution
有一个很显然的$O(n^2)$的容斥做法：

枚举有多少行和多少列被染了色，那么显然答案为
$ans=\sum_{i=0..n,j=0..n,i+j>0}{C_{n}^{i}*C_{n}^{j}*(-1)^{i+j+1}*3^{(n-i)*(n-j)+1}}$

~~然后就是考验代数（乱搞）的时刻了~~

我们首先暴力求出$i=0$或者$j=0$的情况，因为此时只有某些行或者某些列染色，相互独立，所以需要特殊处理，即：

$2*\sum_{i=1}^{n}C_{n}^{i}*(-1)^{i+1}*3^{n*(n-i)+i}$

对于既有行也有列染色的情况，容易发现所有染色行列的颜色是一样的，我们可以对原式恒等变形：

$ans=\sum_{i=1}^{n}\sum_{j=1}^{n}C_{n}^{i}*C_{n}^{j}*(-1)^{i+j+1}*3^{(n-i)*(n-j)+1}$

换元：$i\rightarrow n-i$　　$j\rightarrow n-j$

同时我们将$3^{(n-i)(n-j)+1}$变成$3*3^{(n-i)(n-j)}$

$ans=3*\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}C_{n}^{n-i}*C_{n}^{n-j}*(-1)^{n-i+n-j+1}*3^{ij}$

又因为$C_{n}^{i}=C_{n}^{n-i}$，$(-1)^{2n}=1$，$(-1)^{-i}=(-1)^{i}$：

$ans=3*\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}C_{n}^{i}*C_{n}^{j}*(-1)^{i+j+1}*3^{ij}$

然而还是$O(n^2)$的式子。。。

我们将式子拆一拆：

$ans=3*\sum_{i=0}^{n-1}C_{n}^{i}*(-1)^{i+1}\sum_{j=0}^{n-1}C_{n}^{j}*(-1)^{j}*(3^i)^j$

$ans=3*\sum_{i=0}^{n-1}C_{n}^{i}*(-1)^{i+1}\sum_{j=0}^{n-1}C_{n}^{j}*(-3^i)^{j}$

仔细看看后面那个$\sum$，是不是有种熟悉的感觉？

$(a+b)^n=\sum_{i=0}^{n}C_{n}^{i}a^i*b^{n-i}$

在后面的式子里面，可以将$1$看作$a$，$-3^i$看成$b$，同时还需要减去$j=n$的情况，即：

$\sum_{j=0}^{n-1}C_{n}^{j}*(-3^i)^{j}=(1+(-3^i))^n-(-3^i)^n$

那么原式就成功变成了：

$ans=3*\sum_{i=0}^{n-1}C_{n}^{i}*(-1)^{i+1}*((1+(-3^i))^n-(-3^i)^n)$

再预处理逆元并使用快速幂即可。

时间复杂度$O(nlog_2n)$.

# Code
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
const ll mod = 998244353, maxn = 1e6 + 10;
int n;
ll fac[maxn], inv[maxn];

ll qmul(ll base, ll pow) {
	ll ret = 1;
	for(; pow; pow >>= 1) {
		if(pow & 1) ret = ret * base % mod;
		base = base * base % mod;
	}
	return ret;
}

ll calc(ll x, ll y) {
	return fac[x] * inv[y] % mod * inv[x - y] % mod;
}

int main()
{
	cin>>n;
	ll ans = 0;
	fac[0] = inv[0] = 1;
	for(int i=1; i<=n; i++) {
		fac[i] = fac[i-1] * i % mod;
		inv[i] = qmul(fac[i], mod - 2);
	}
	for(int i=1; i<=n; i++) 
		ans = (ans + qmul(3, (1ll * n * (n - i) + i)) * qmul(-1, i+1) * calc(n, i) % mod + mod) % mod;
	ans = ans * 2 % mod;
	ll tmp = 0;
	for(int i=0; i<n; i++) {
		int t = -qmul(3, i);
		tmp = (tmp + calc(n, i) * qmul(-1, i+1) * (qmul(1 + t, n) - qmul(t, n) + mod) % mod + mod) % mod;
	}
	ans = (ans + tmp * 3) % mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Daidly (赞：5)

令 $f(i,j)$ 表示选 $i$ 行，$j$ 列颜色相同的方案数。

由容斥原理得：

$$\sum^{n}_ {i=0,j=0,i+j>0}(-1)^{i+j+1}C^{i}_ {n}C^{j}_ {n}f(i,j)$$

考虑分为 $i,j=0$ 和 $i,j\neq 0$ 两种情况。

$$ f(i,j)=\left\{
\begin{aligned}
&3^{n(n-j)+j},i=0\\
&3^{n(n-i)+i},j=0\\
&3^{(n-i)(n-j)+1},i\neq0,j\neq0
\end{aligned}
\right.
$$

把 $i,j=0$ 的情况拆开，化简式子得：

$$
\begin{aligned}
\sum^{n}_ {i=0,j=0,i+j>0}(-1)^{i+j+1}C^{i}_ {n}C^{j}_ {n}f(i,j) & =2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+\sum^{n}_ {i=1}\sum^{n}_ {j=1}(-1)^{i+j+1}C^{i}_ {n}C^{j}_ {n}3^{(n-i)(n-j)+1}\\
&=2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+\sum^{n}_ {i=1}\sum^{n}_ {j=1}(-1)^{i}(-1)^{j}(-1)C^{i}_ {n}C^{j}_ {n}3^{n^{2}+1}3^{-ni}3^{-nj}3^{ij}\\
&=2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}\sum^{n}_ {j=1}(-1)^{i}(-1)^{j}C^{i}_ {n}C^{j}_ {n}3^{-ni}3^{-nj}3^{ij}\\
&=2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}(-1)^{i}C^{i}_ {n}3^{-ni}\sum^{n}_ {j=1}(-1)^{j}C^{j}_ {n}3^{-nj}3^{ij}\\
&=2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}(-1)^{i}C^{i}_ {n}3^{-ni}\sum^{n}_ {j=1}C^{j}_ {n}(-3^{i-n})^{j}
\end{aligned}$$

由二项式定理知：

$$(a+b)^n=\sum^{n}_ {j=0}C^{j}_ {n}a^jb^{n-j}$$

则：

$$
\begin{aligned}
(-3^{i-n}+1)^n
&=\sum^{n}_ {j=0}C^{j}_ {n}(-3^{i-n})^j1^{n-j}\\
&=\sum^{n}_ {j=0}C^{j}_ {n}(-3^{i-n})^j
\end{aligned}$$

排除 $j=0$ 得：

$$
\begin{aligned}
2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}(-1)^{i}C^{i}_ {n}3^{-ni}\sum^{n}_ {j=1}C^{j}_ {n}(-3^{i-n})^{j}
& = 2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}(-1)^{i}C^{i}_ {n}3^{-ni}((1-3^{i-n})^n-1)\\
\end{aligned}$$

答案即为：

$$2\sum^{n}_ {i=1}(-1)^{i+1}C^{i}_ {n}3^{n(n-i)+i}+(-1)3^{n^{2}+1}\sum^{n}_ {i=1}(-1)^{i}C^{i}_ {n}3^{-ni}((1-3^{i-n})^n-1)$$

注意多模，细节可看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod=998244353;
const int MAXN=1000005;
int n,tmp1,tmp2,sum,ans;
int fac[MAXN],facinv[MAXN];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}return ans;
}
int inv(int x){
	return qpow(x,mod-2);
}
void init(){
	fac[0]=facinv[0]=1;
	for(int i=1;i<=n;++i){
		fac[i]=fac[i-1]*i%mod;
		facinv[i]=inv(fac[i]);
	}
}
int C(int a,int b) {
	return fac[a]*facinv[b]%mod*facinv[a-b]%mod;
}
signed main(){
	cin>>n;
	init();
	for(int i=1;i<=n;++i){
		ans=(ans+qpow(-1,i+1)*C(n,i)*qpow(3,n*(n-i)+i)%mod+mod)%mod;
	}
	ans=ans*2%mod;
	tmp1=-qpow(3,n*n+1);
	tmp2=inv(3);
	for(int i=1;i<=n;++i){
		sum=(sum+qpow(-1,i)*C(n,i)%mod*qpow(tmp2,n*i)%mod*(qpow((1-qpow(tmp2,n-i)),n)-1)+mod)%mod;
	}
	ans=(ans+sum*tmp1)%mod;
	cout<<(ans+mod)%mod<<endl;
	return 0;
}
```

---

## 作者：81179332_ (赞：5)

设 $F_{i,j}$ 为至少有 $i$ 行 $j$ 列颜色相同的方案数，$G_{i,j}$ 为恰好有 $i$ 行 $j$ 列颜色相同的方案数

则易知 $F_{x,y}=\sum\limits_{i=x}^n\sum\limits_{j=y}^n \dbinom ix\dbinom jyG_{i,j}$，$ans=3^{n^2}-G_{0,0}$

根据高维二项式反演可知，$G_{i,j}=\sum\limits_{i=x}^n\sum\limits_{j=y}^n (-1)^{i+j-x-y}\dbinom ix\dbinom jyF_{i,j}$

问题转化为求 $F_{i,j}$

---

分情况讨论：

 1. 当 $ij\neq 0$ 时，由于行和列互相穿过，所以所有行和列的颜色都要是相同的，所以此时 $F_{i,j}=\dbinom ni\dbinom nj\cdot 3^{(n-i)(n-j)+1}$
 2. 当 $ij=0,i+j\neq 0$ 时，此时各行/列之间的颜色不需要相同，所以此时 $F_{i,j}=\dbinom n{i+j}\cdot3^{i+j+n(n-i-j)}$
 3. 当 $i+j=0$ 时，此时随便放，$F_{i,j}=3^{n^2}$
 
---

$$G_{0,0}=\sum\limits_{i=0}^n\sum\limits_{j=0}^n(-1)^{i+j}\dbinom i0\dbinom j0F_{i,j}$$

$$G_{0,0}=\sum\limits_{i=0}^n\sum\limits_{j=0}^n(-1)^{i+j}F_{i,j}$$

$$G_{0,0}=\sum\limits_{i=1}^n\sum\limits_{j=1}^n(-1)^{i+j}F_{i,j}+2\sum\limits_{i=1}^n(-1)^iF_{i,0}+F_{0,0}$$

---

$\ \ \ \ \sum\limits_{i=1}^n\sum\limits_{j=1}^n(-1)^{i+j}F_{i,j}$
$=\sum\limits_{i=1}^n\sum\limits_{j=1}^n(-1)^{i+j}\dbinom ni\dbinom nj\cdot 3^{(n-i)(n-j)+1}$

$=3^{n^2+1}\sum\limits_{i=1}^n\dbinom ni(-1)^i\cdot 3^{-in}\sum\limits_{j=1}^n\dbinom nj(-1)^j\cdot 3^{j(i-n)}$

$=3^{n^2+1}\sum\limits_{i=1}^n\dbinom ni(-1)^i\cdot 3^{-in}\sum\limits_{j=1}^n\dbinom nj\cdot (-3^{i-n})^j$

$=3^{n^2+1}\sum\limits_{i=1}^n\dbinom ni(-1)^i\cdot 3^{-in}\left(\left(1-3^{i-n}\right)^n-1\right)$

---
$\ \ \ \ \sum\limits_{i=1}^n(-1)^iF_{i,0}$

$=\sum\limits_{i=1}^n(-1)^i\dbinom ni\cdot3^{i+n(n-i)}$

$=3^{n^2}\sum\limits_{i=1}^n\dbinom ni (-3^{1-n})^i$

$=3^{n^2}\left(\left(1-3^{1-n}\right)^n-1\right)$

---

$F_{0,0}=3^{n^2}$

---

综上所述，

$ans=3^{n^2}-G_{0,0}$

$\ \ \ \ \ \ \ \ =-3^{n^2+1}\sum\limits_{i=1}^n\dbinom ni(-1)^i\cdot 3^{-in}\left(\left(1-3^{i-n}\right)^n-1\right)-2\times3^{n^2}\left(\left(1-3^{1-n}\right)^n-1\right)$

```cpp
int qpow(int a,int b)
{
	int ans = 1;
	for(;b;b >>= 1,a = (ll)a * a % mod) if(b & 1) ans = (ll)ans * a % mod;
	return ans;
}
const int N = 1000010;
int fac[N],ifac[N],n;
int C(int n,int m) { return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
void init()
{
	fac[0] = 1;for(int i = 1;i <= n;i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n],mod - 2);for(int i = n;i;i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
}
int solve1()
{
	int ans = 0;
	for(int i = 1;i <= n;i++)
	{
		int res = (ll)C(n,i) * qpow(3,(mod - 1 - (ll)i * n % (mod - 1))) % mod;
		res = (ll)res * (qpow(1 - qpow(3,i - n + mod - 1) + mod,n) - 1) % mod;
		if(i & 1) up(ans -= res);
		else up(ans += res - mod);
	}return (ll)ans * qpow(3,((ll)n * n + 1) % (mod - 1)) % mod;
}
int solve2()
{
	return 2ll * qpow(3,(ll)n * n % (mod - 1)) % mod * (qpow(1 - qpow(3,mod - n) + mod,n) - 1) % mod;
}
int main()
{
	n = read();init();
	int ans = 0;up(ans -= solve1()),up(ans -= solve2());
	fprint((ans % mod + mod) % mod);
}
```

---

## 作者：滑大稽 (赞：5)

提供一种不一样的思路，不用二元二项式反演，并且式子推导也会简单得多。

首先先用减法原理，然后我们要求的就是所有行列颜色均不同的情况数。

我们发现，假设只有行有限制，列没有限制会很简单。这启示我们去掉其中一维。

我们对列进行二项式反演。

设 $f(x)$ 为钦定了 $x$ 列颜色相同的方案数，$g(x)$ 为恰好有 $x$ 列颜色相同的方案数。我们要求的就是 $g(0)$。

同时有：

$$f(x)=\sum_{i=x}^nC_i^xg(i)$$

根据二项式反演就有

$$g(x)=\sum_{i=x}^n(-1)^{i-x}C_i^xf(i)$$

于是现在的问题就变成了如何求解 $f(i)$。

首先对于 $f(0)$，我们先特判掉，他的方案数是 $(3^{n}-3)^n$ 种（只用考虑行，每行减去 $3$ 种不合法的情况，乘法原理乘起来）。

然后对于 $f(i),i>0$ ，我们考虑对于我们选出的颜色相同的列的颜色是否全部相同来分类。

假如颜色均相同，则这些列总共只有 $3$ 种方案，乘上选列的方案 $C_n^i$，我们的行要同一种颜色当且仅当该行全部选了列所选的颜色，所以其他列的方案数为 $(3^{n-i}-1)^n$。总方案为 $3\times C_n^i\times (3^{n-i}-1)^n$。

假设这些列的颜色不全相同，则这些列总共有 $3^i-3$ 种方案，同样乘上 $C_n^i$ 。至于行，我们是不可能选出一行颜色相同的，所以其他列的方案数为 $3^{n\times(n-i)}$。总方案数为 $(3^i-3)\times C_n^i \times 3^{n\times(n-i)}$。

总结起来，$f(i)=3\times C_n^i\times (3^{n-i}-1)^n+(3^i-3)\times C_n^i \times 3^{n\times(n-i)}$ 。

求出 $f(i)$ 后随便二项式反演做做就行了。

代码：

```cpp
#include<iostream>
#include<cstdio>
const int N=1e6+5,mod=998244353;
using namespace std;
int fra[N],ifra[N],p[N];
inline int read()
{
	char h=getchar();
	int y=0;
	while(h<'0'||h>'9')h=getchar();
	while(h>='0'&&h<='9')y=y*10+h-'0',h=getchar();
	return y;
}
inline int qpow(int a,long long b)
{
	int j=1;
	while(b)
	{
		if(b&1)j=1ll*j*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return j;
}
inline void init(int n)
{
	fra[0]=ifra[0]=1;
	for(int i=1;i<=n;i++)fra[i]=1ll*fra[i-1]*i%mod;
	ifra[n]=qpow(fra[n],mod-2);
	for(int i=n-1;i;i--)ifra[i]=1ll*ifra[i+1]*(i+1)%mod;
	p[0]=1;
	for(int i=1;i<=n;i++)p[i]=1ll*p[i-1]*3%mod;
}
inline int C(int n,int m)
{
	return n<m?0:1ll*fra[n]*ifra[m]%mod*ifra[n-m]%mod;
}
signed main()
{
	int n=read(),ans=0;
	init(n);
	for(int i=0;i<=n;i++)
	{
		int t;
		if(i==0)
		{
			t=qpow((p[n]-3+mod)%mod,n);
		}
		else
		{
			t=1ll*C(n,i)*3%mod*qpow((p[n-i]-1+mod)%mod,n)%mod;
			t+=1ll*C(n,i)*((p[i]-3+mod)%mod)%mod*qpow(p[n-i],n)%mod;
			if(t>=mod)t-=mod;
		}
		if(i&1)
		{
			ans-=t;
			if(ans<0)ans+=mod;
		}
		else
		{
			ans+=t;
			if(ans>=mod)ans-=mod;
		}
	}
	printf("%d\n",(qpow(3,1ll*n*n)-ans+mod)%mod);
}
```

---

## 作者：attack (赞：4)

Orz fjzzq

最后答案是这个

$$3^{n^2} - (3^n - 3)^n - \sum_{i = 1}^n (-1)^i C_n^i 3(3^{n-i} - 1)^n + (3^i - 3)(3^{(n-i)n}) $$

我来强行解释一波。

首先可以做个转化：答案 = 总的方案 - 任意行/列都至少含有两种颜色的方案

我们先来考虑列，任意一列含有两种颜色的方案是$(3^n-3)^n$(-3是因为颜色相同的三种方案)。但是这样我们会多减去行合法的情况，因此还需要加一些方案，这些方案满足存在至少一行颜色都相同且任意一列至少含有两种颜色。

发现"至少"不太好搞，我们可以通过容斥把它变成"恰好"，也就是加上恰好一行满足的，减去恰好两行满足的...。

那么对于这恰好$i$行满足条件的我们又需要来分类讨论。首先把他们选出来方案数是$C_n^i$

接下来就要分两种情况

1. 选出来的$i$行的颜色(每行都是相同的h)有任意两个不同

这时候就简单了，方案数为$(3^i - 3) (3^{(n-i)n})$。也就是减去每行颜色都相同的三种方案，剩下的随便选

2. 选出来的$i$行的颜色两两相同

这时候对于每一列都有$(3^{n-i}-1)$种方案，共有$n$列。同时这$i$行的颜色又有三种选发。

因此这时候的方案数为$3(3^{n-i}-1)^n$

然后大力算就行了

复杂度$O(n \log n)$

```cpp
#include<bits/stdc++.h> 
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define int long long 
#define LL long long 
#define Fin(x) {freopen(#x".in","r",stdin);}
#define Fout(x) {freopen(#x".out","w",stdout);}
using namespace std;
const int MAXN = 1e6 + 10, mod = 998244353, INF = 1e9 + 10;
const double eps = 1e-9;
template <typename A, typename B> inline bool chmin(A &a, B b){if(a > b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline bool chmax(A &a, B b){if(a < b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline LL add(A x, B y) {if(x + y < 0) return x + y + mod; return x + y >= mod ? x + y - mod : x + y;}
template <typename A, typename B> inline void add2(A &x, B y) {if(x + y < 0) x = x + y + mod; else x = (x + y >= mod ? x + y - mod : x + y);}
template <typename A, typename B> inline LL mul(A x, B y) {return 1ll * x * y % mod;}
template <typename A, typename B> inline void mul2(A &x, B y) {x = (1ll * x * y % mod + mod) % mod;}
template <typename A> inline void debug(A a){cout << a << '\n';}
template <typename A> inline LL sqr(A x){return 1ll * x * x;}
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, fac[MAXN], ifac[MAXN];
int fp(int a, int p) {
	int base = 1;
	while(p) {
		if(p & 1) base = mul(base, a);
		p >>= 1; a = mul(a, a);
	}
	return base;
}
int C(int N, int M) {
	return mul(fac[N], mul(ifac[M], ifac[N - M]));
}
signed main() {
	cin >> N;
	fac[0] = 1; for(int i = 1; i <= N; i++) fac[i] = mul(i, fac[i - 1]);
	ifac[N] = fp(fac[N], mod - 2);
	for(int i = N; i >= 1; i--) ifac[i - 1] = mul(ifac[i], i);
	int ans = add(fp(3, N * N), -fp(fp(3, N) - 3, N));
	for(int i = 1; i <= N; i++) {
		if(i & 1) {
			add2(ans, mul(C(N, i), add(mul(3, fp(fp(3, N - i) - 1, N)), mul(fp(3, i) - 3, fp(3, (N - i) * N)))));
		} else {
			add2(ans, -mul(C(N, i), add(mul(3, fp(fp(3, N - i) - 1, N)), mul(fp(3, i) - 3, fp(3, (N - i) * N)))));
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Broken_Eclipse (赞：3)

upd：对不起管理大大有个式子写错了我改了一下

------

## 题意：

有一个 $n \times n$（ $n \leq 10^6$ ）的正方形网格，用红色，绿色，蓝色三种颜色染色，求有多少种染色方案使得至少一行或一列是同一种颜色。结果对 $998244353$ 取模。

## 解题思路：

我的做法可能会有些小麻烦（？

观察到颜色数比较少，我们可以先求出至少一行或一列是红绿蓝其中的某一种颜色的方案数。

考虑容斥，先选定至少 $i$ 行 $j$ 列是同一种颜色，这样的位置一共有 $n\times i+n\times j-i\times j$  个，其他 $n^2-n\times i-n\times j +i\times j$ 个位置可以任意选，方案数为：

$$
ansone=3^{n^2}-\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j} \binom{n}{i}\binom{n}{j} 3^{(n-i)(n-j)}
$$

（因为后面的式子容斥出来的实际上是不满足条件的数，所以要用全集 $3^n$ 减去）

于是我们求出了至少使用一种颜色（以下矩形范围）的方案数，如图所示。


![](https://cdn.luogu.com.cn/upload/image_hosting/ku5a35pu.png)

然而直接将 $ansone \times 3$ 会导致 $2,3$ 部分出现重复，因此接下来需要分别求出使用两种颜色和使用三种颜色满足要求的方案数，最后容斥出最终结果。

观察到当有行或者列出现同种颜色且这些颜色种类数大于 $1$ 时，情况一定是只有行符合条件或者只有列符合条件（因为行列交叉处显然不能出现多种颜色）。这启发我们只需要针对行进行容斥，并将方案数乘以 $2$ 即可。

考虑至少选用了两种颜色的方案：

$$
anstwo=[\sum_{i=2}^{n} (-1)^i \binom{n}{i}(2^i-2)3^{(n-i)i}]\times 2
$$

（ $2^i-2$ 的含义是这些行可以选择两种颜色，但不能都选择同一种颜色的方案数）

至少选用了三种颜色的方案：

$$
ansthr=[\sum_{i=3}^{n} (-1)^{i-1} \binom{n}{i}(3^i-3(2^i-2)+3)3^{(n-i) i})]\times 2
$$

（ $3^i-3(2^i-2)+3$ 的含义是这些行可以选择三种颜色，但不能都选择两种相同颜色或者一种相同颜色的方案数）

至此我们求出来了所有的部分，因此最终的答案应该为：

$$
ans=ansone\times 3-anstwo \times 3+ansthr
$$

结合预处理可以做到 $O(n^2)$ 。

然后悲哀地发现数据范围是 $10^6$  的。

所以就~~大力卡常~~思考怎么样优化复杂度。

回过头来看求 $ansone$ 的第一个式子：

$$
3^{n^2}-\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}\binom{n}{i}\binom{n}{j} 3^{(n-i)(n-j)}
$$

观察后面那一部分，把含 $j$ 的项都分离出来：

$$

\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}  \binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)}  

$$

$$
\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i}(-1)^{j} \binom{n}{i}\binom{n}{j} 3^{(n-i)n+(i-n)j} 
$$

$$
\sum_{i=0}^{n}(-1)^{i} \binom{n}{i}3^{(n-i)n} \sum_{j=0}^{n} (-1)^{j} \binom{n}{j} 3^{(i-n)j}

$$

发现后面可以用二项式定理化成：

$$
\sum_{i=0}^{n}(-1)^{i} \binom{n}{i}3^{(n-i)n}(1-3^{i-n})^n
$$

然后这题就可以 $O(n\log n)$ 做了。

## 代码：

~~变量有些丑，而且懒得预处理了（逃~~

```
#include <cstdio>
#include <algorithm>
#define Reg register
#define int long long
using namespace std;
const int maxn=1000010,mod=998244353;
int n,ans,ansone,anstwo,ansthr;
int ark[maxn],arknv[maxn];
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<1)+(s<<3)+(ch^48);
        ch=getchar();
    }
    return s*w;
}
inline int qpow(int A,int B){
    int Ans=1;
    while(B){
        if(B&1) Ans=Ans*A%mod;
        A=A*A%mod;
        B>>=1;
    }
    return Ans;
}
inline void pre(){
    int p=max(n,3ll);
    ark[0]=arknv[0]=1;
    for(Reg int i=1;i<=p;++i) ark[i]=ark[i-1]*i%mod;
    arknv[p]=qpow(ark[p],mod-2);
    for(Reg int i=p-1;i;--i) arknv[i]=arknv[i+1]*(i+1)%mod;
}
inline int C(int p,int q){
    if(p<q) return 0;
    return ark[p]*arknv[p-q]%mod*arknv[q]%mod;
}
signed main(){
    n=read(),pre();
    for(Reg int i=0;i<=n;++i){
        int v=qpow(3,n-i)%mod,p=(i&1)?mod-1:1;
        v=qpow(v,mod-2)%mod;
        v=qpow(1-v+mod,n)%mod;
        ansone=(ansone+p%mod*C(n,i)%mod*qpow(3,n*(n-i))%mod*v%mod);
    }
    ansone=((qpow(3,n*n)-ansone+mod)%mod+mod)%mod;
    for(Reg int i=2;i<=n;++i){
        int p=(i&1)?mod-1:1;
        anstwo=(anstwo+p*C(n,i)%mod*(qpow(2,i)-2+mod)%mod*qpow(3,(n-i)*n)%mod)%mod;
    }
    anstwo=anstwo*2%mod;
    for(Reg int i=3;i<=n;++i){
        int p=(i&1)?1:mod-1;
        ansthr=(ansthr+p*C(n,i)%mod*((qpow(3,i)-3*(qpow(2,i)-2)%mod+mod-3)%mod+mod)%mod*qpow(3,(n-i)*n)%mod)%mod;
    }
    ansthr=ansthr*2%mod;
    ans=(((ansone*3%mod-anstwo*3%mod+mod)%mod+mod)%mod+ansthr)%mod;
    printf("%lld\n",ans);
    return 0;
}
```





---

## 作者：wurzang (赞：3)

题解都是什么推式子啊二项式反演啊二项式定理啊，我太菜了一个都不会，所以来提供一种比较简单的容斥做法。

我们可以枚举钦定颜色相同的行数 $i$，然后每一列造成的容斥系数贡献为 $1-3^{-(n-i)}$，$1$ 表示列不选，$-3^{n-i}$ 表示该列选上。

显然每一列的容斥系数相同，我们直接快速幂就可以解决。

由于行和列都有被钦定的，与行/列只有一种被钦定的，它们造成的系数贡献也是不一样的，前一种造成的贡献为 $3$，而后一种造成的贡献为 $3^i$ ，其中 $i$ 表示钦定的行/列数，表示每一行/列都可以选择某种颜色。

所以我们分类讨论一下，贡献分别算就行了。

不懂可以看代码，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,mod=998244353,inv3=(mod+1)/3;
int ksm(int b,ll n){
	int res=1;
	while(n){
		if(n&1) res=1ll*res*b%mod;
		b=1ll*b*b%mod; n>>=1;
	}
	return res;
}
int fac[N],inv[N];
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2);
	for(int i=n-1;i>=0;--i)
		inv[i]=1ll*(i+1)*inv[i+1]%mod;
}
int C(int n,int m){
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	int n,ans=0;
	cin>>n;
	init(n);
	if(n==1) return cout<<3,0;
	for(int i=1;i<=n;++i){
		int tmp=1ll*C(n,i)*ksm(inv3,1ll*n*i)%mod;
		int x=(1+mod-ksm(inv3,n-i))%mod,now=tmp;
		tmp=1ll*tmp*ksm(x,n)%mod,tmp=(tmp+mod-now)%mod;
		tmp=1ll*tmp*ksm(3,1ll*n*n+1)%mod;
		if(i&1) ans=(ans+tmp)%mod;
		else ans=(ans+mod-tmp)%mod;
	}
	for(int i=1;i<=n;++i){
		int tmp=2ll*C(n,i)*ksm(inv3,1ll*(n-1)*i)%mod*ksm(3,1ll*n*n)%mod;
		if(i&1) ans=(ans+tmp)%mod;
		else ans=(ans+mod-tmp)%mod;
	}
	cout<<ans;
}
```




---

## 作者：wsyhb (赞：2)

## 二元二项式反演

本题解使用了**二元二项式反演**，故先进行讲解。

### 结论

$$\begin{aligned}
f(x,y)&=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)\\
\Leftrightarrow g(x,y)&=\sum_{i=x}^{n}\sum_{j=y}^{m}(-1)^{i+j-x-y}\binom{i}{x}\binom{j}{y}f(i,j)
\end{aligned}$$

其中 $n,m$ 是定值。

P.S. 通过**容斥原理**，其实可以较为感性地理解这个结论。

### 证明

先写出**初始恒等式**：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)[i=x \land j=y]$$

（根据反演套路，初始恒等式与前一个式子极其相似）

再写出**交错和公式**：

$$\sum_{i=0}^{n}(-1)^i\binom{n}{i}=[n=0]$$

（证明可使用**二项式定理**，或统计大小为 $n$ 的集合的奇子集和偶子集的个数）

由 $[i=x \land j=y]=[i-x=0][j-y=0]$ 得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\binom{i}{x}\binom{j}{y}g(i,j)(\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{i-x}{a}\binom{j-y}{b})$$

整理一下式子：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{i}{x}\binom{i-x}{a}\binom{j}{y}\binom{j-y}{b}g(i,j)$$

考虑对组合数进行阶乘展开并重组成其它组合数：

$$\begin{aligned}
\binom{i}{x}\binom{i-x}{a}&=\frac{i!}{x!(i-x)!}\cdot\frac{(i-x)!}{a!(i-x-a)!}\\
&=\frac{1}{x!a!}\cdot\frac{i!}{(i-x-a)!}\\
&=\frac{(x+a)!}{x!a!}\cdot\frac{i!}{(x+a)!(i-x-a)!}\\
&=\binom{x+a}{x}\binom{i}{x+a}
\end{aligned}$$

（同理有 $\binom{j}{y}\binom{j-y}{b}=\binom{y+b}{y}\binom{j}{y+b}$）

代入前述式子得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=0}^{i-x}\sum_{b=0}^{j-y}(-1)^{a+b}\binom{x+a}{x}\binom{i}{x+a}\binom{y+b}{y}\binom{j}{y+b}g(i,j)$$

令 $a \leftarrow x+a$，$b \leftarrow y+b$ 得：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{m}\sum_{a=x}^{i}\sum_{b=y}^{j}(-1)^{a+b-x-y}\binom{a}{x}\binom{i}{a}\binom{b}{y}\binom{j}{b}g(i,j)$$

交换求和符号：

$$g(x,y)=\sum_{a=x}^{n}\sum_{b=y}^{m}(-1)^{a+b-x-y}\binom{a}{x}\binom{b}{y}(\sum_{i=a}^{n}\sum_{j=b}^{m}\binom{i}{a}\binom{j}{b}g(i,j))$$

代入结论中的前一个式子得：

$$g(x,y)=\sum_{a=x}^{n}\sum_{b=y}^{m}(-1)^{a+b-x-y}\binom{a}{x}\binom{b}{y}f(a,b)$$

即结论中的后一个式子。

除最后一步外，所有的步骤都是恒等变形，所以**结论中的两个式子等价，且没有任何限制条件**。

## 题解

回到本题，设 $f(x,y)$ 为**至少**有 $x$ 行 $y$ 列同色的方案数，$g(x,y)$ 为**恰好**有 $x$ 行 $y$ 列同色的方案数。

注意：我们定义此处的 $f(x,y)$ 的计算方法为，从所有行列中选出 $x$ 行 $y$ 列，并指定这 $x$ 行 $y$ 列满足条件，而其余行列任意，因此 **$f$ 是包含重复情况的**。（这是为了使用二项式反演）

由 $f$ 和 $g$ 的定义知：

$$f(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{n}\binom{i}{x}\binom{j}{y}g(i,j)$$

由二元二项式反演知：

$$g(x,y)=\sum_{i=x}^{n}\sum_{j=y}^{n}(-1)^{i+j-x-y}\binom{i}{x}\binom{j}{y}f(i,j)$$

根据 $f$ 的定义，其计算方法如下：

$$f(x,y)=\begin{cases}
\binom{n}{x}\cdot 3^x \cdot 3^{(n-x)n} \quad (y=0)\\
f(y,0) \quad (x=0)\\
\binom{n}{x}\binom{n}{y}\cdot 3 \cdot 3^{(n-x)(n-y)} \quad (\text{otherwise})
\end{cases}$$

说明：

1. 当 $y=0$ 时：
	- 先选择指定哪 $x$ 行同色。
	- 对于指定同色的这 $x$ 行，每一行可以选择三种颜色中的一种。
	- 对于未指定同色的这 $n-x$ 行（共 $(n-x)n$ 个格子），每一格可以选择三种颜色中的一种。
1. 当 $x=0$ 时：
	- 由于行列可以交换，可以转化为 $y=0$ 的情况。
1. 当 $x,y>0$ 时：
	- 先选择指定哪 $x$ 行，哪 $y$ 列同色。
    - 对于指定同色的任意一行，由于其与指定同色的任意一列相交，所以指定同色的这 $x$ 行和 $y$ 列必须是同一颜色，有三种选择。
    - 对于未指定同色的 $(n-x)(n-y)$ 个格子，每一格可以选择三种颜色中的一种。

------------

题目的答案即为（其实很简单，可以自己先尝试推一推）：

$$\begin{aligned}
f(0,0)-g(0,0)&=f(0,0)-\sum_{i=0}^{n}\sum_{j=0}^{n}(-1)^{i+j}f(i,j)\\
&=-\sum_{i=1}^{n}(-1)^{i}(f(i,0)+f(0,i))-\sum_{i=1}^{n}\sum_{j=1}^{n}(-1)^{i+j}f(i,j)\\
&=-2\sum_{i=1}^{n}(-1)^i\binom{n}{i}3^{n^2-(n-1)i}-\sum_{i=1}^{n}\sum_{j=1}^{n}(-1)^{i+j}\binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)+1}\\
&=-2\sum_{i=1}^{n}(-1)^i\binom{n}{i}3^{n^2-(n-1)i}-3\sum_{i=1}^{n}\sum_{j=1}^{n}(-1)^{i+j}\binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)}\\
&=-2\sum_{i=1}^{n}(-1)^i\binom{n}{i}3^{n^2-(n-1)i}-3\sum_{i=1}^{n}(-1)^{i}\binom{n}{i}\sum_{j=1}^{n}\binom{n}{j}(-1)^{j}(3^{n-i})^{n-j}\\
&=-2\sum_{i=1}^{n}(-1)^i\binom{n}{i}3^{n^2-(n-1)i}-3\sum_{i=1}^{n}(-1)^{i}\binom{n}{i}[(3^{n-i}-1)^n-(3^{n-i})^n]
\end{aligned}$$

公式有点长，所以对每一步作一下说明（数字编号代表是第几个等号）：

1. 代入反演得到的式子。
1. 把 $f(0,0)$ 抵消掉，将剩余的分为 $i,j$ 其中之一为 $0$，和 $i,j$ 均不为 $0$ 两部分。
1. 按照 $f$ 的计算方法进行代入，注意由于 $f(i,0)=f(0,i)$，这一项前面多了个 $2$。（$i,j$ 其中之一为 $0$ 的部分的处理到此结束，默认之后只对后一部分进行说明）
1. 提出一个 $3$。
1. 将只与 $i$ 有关的部分分离出来。
1. 使用二项式定理，注意要补上 $j=0$ 那一项。

组合数 $\binom{n}{i}$，$3^{n^2-(n-1)i}$ 以及 $3^{n-i}$ 可以 $O(n)$ 预处理，但 $(3^{n-i}-1)^n$ 只能 $O(n\log{n})$ 计算，因此总时间复杂度为 $O(n\log{n})$。

## 代码

题解中的代码是通过如下递推式算得组合数 $\binom{n}{i}$ 的：

$$\binom{n}{i}=\frac{n-i+1}{i}\binom{n}{i-1}$$

（将组合数阶乘展开即证）

当然也可以预处理阶乘及阶乘逆元，直接使用阶乘展开式进行计算。

另外，题解中的代码是通过如下递推式算得组合数 $3^{n^2-(n-1)i}$ 的：

$$3^{n^2-(n-1)i}=3^{n^2-(n-1)(i+1)} \cdot 3^{n-1}$$

（$(3^{n-i})^n$ 可以类似递推）

当然也可以直接快速幂。（总时间复杂度不变）

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e6+5;
int inv[max_n],C[max_n],pow3[max_n],pow3_2[max_n],pow3_3[max_n];
const int mod=998244353;
inline int qpow(int a,int n)
{
	int res=1;
	while(n)
	{
		if(n&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod;
		n>>=1;
	}
	return res;
}
int main()
{
	int n;
	scanf("%d",&n);
	inv[1]=1;
	for(int i=2;i<=n;++i)
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	C[0]=pow3[0]=1;
	for(int i=1;i<=n;++i)
	{
		C[i]=1ll*C[i-1]*inv[i]%mod*(n-i+1)%mod;
		pow3[i]=3ll*pow3[i-1]%mod;
	}
	pow3_2[n]=pow3[n];
	for(int i=n-1;i>=0;--i)
		pow3_2[i]=1ll*pow3_2[i+1]*pow3[n-1]%mod;
	pow3_3[0]=1;
	for(int i=1;i<=n;++i)
		pow3_3[i]=1ll*pow3_3[i-1]*pow3[n]%mod;
	int r1=0,r2=0;
	for(int i=1,c=-1;i<=n;++i,c=-c)
	{
		r1=(r1+1ll*c*C[i]*pow3_2[i])%mod;
		r2=(r2+1ll*c*C[i]*(qpow(pow3[n-i]-1,n)-pow3_3[n-i]))%mod;
	}
	int ans=(-2*r1-3ll*r2)%mod;
	ans+=ans<0?mod:0;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：KaisuoShutong (赞：2)

## CF997C Sky Full of Stars 题解

@Saliеri 表示题解说得都不清不楚，所以有了这篇题解。  
大家快来膜她！！！

正难则反，考虑用全集减去全都不同色的答案。

设条件为同色，那么：

设 $f(x,y)$ 为至少 $x$ 行 $y$ 列满足条件的方案， $g(x,y)$ 为至少。

根据定义有：

$$f(x,y) = \sum_{i=x}^n\sum_{j=y}^n\binom{i}{x}\binom{j}{y} g(i,j)$$

做二元二项式反演，且 $ans = g(0,0)$，那么：

$$ans = \sum_{i=0}^n\sum_{j=0}^n (-1)^{i+j}f(i,j)$$

先不考虑 $i=0$ 或 $j=0$ 的情况（因为可以轻易地 $O(n\log n)$ 算出），那么式子化为：

$$ans = \sum_{i=1}^n\sum_{j=1}^n (-1)^{i+j}\binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)+1}$$

提出常数和与 $i$ 有关的东西。

$$ans = 3^{n^2+1} \sum_{i=1}^n(-1)^i\binom{n}{i}3^{-in}\sum_{j=1}^n (-1)^{j}\binom{n}{j}3^{-nj+ij}$$

将后面的式子提出 $j$ 次幂。

$$ans = 3^{n^2+1} \sum_{i=1}^n(-1)^i\binom{n}{i}3^{-in}\sum_{j=1}^n \binom{n}{j}(-3^{-n+i})^j$$

凑一个 $j=0$ 的项，我们突然灵能觉醒：  
![灵能觉醒](https://cdn.luogu.com.cn/upload/image_hosting/x6jnbbd3.png)  
就可以直接二项式定理了。

$$ans = 3^{n^2+1} \sum_{i=1}^n(-1)^i\binom{n}{i}3^{-in}((-3^{-n+i}+1)^n-1)$$

显然这个东西可以在 $O(n\log n)$ 的时间复杂度内算出。

没有附代码的必要。

点个赞吧。


---

## 作者：tzc_wk (赞：2)

我竟然自己搞出来了！incredible！

首先先给自己的博客打个广告：https://www.cnblogs.com/ET2006/

考虑设 $F_{i,j}$ 为钦定某 $i$ 行和某 $j$ 列必须涂上同一种颜色，剩余的随便涂的方案数。（注意：题解区不少题解对这里 $F_{i,j}$ 的解释有误，$F_{i,j}$ 并不是所谓的至少 $i$ 行 $j$ 列被涂上同一种颜色的方案数，因为有重复计算）

再设 $G_{i,j}$ 为钦定某 $j$ 列必须涂上同一种颜色，并且恰好 $i$ 行涂上了同一种颜色的方案数。

再设 $H_{i,j}$ 为恰好 $i$ 行 $j$ 列被涂上同一种颜色的方案数

考虑 $F_{i,j}$ 与 $G_{k,j}$ 的关系，假设 $i=3,k=4$ 并且有 $a,b,c,d$ 四行被涂上了同一种颜色，那么我们来看看这个 $G_{k,j}$ 会对 $F_{i,j}$ 产生多少贡献。

那么我们钦定 $a,b,c$ 三行、$a,b,d$ 三行、$a,c,d$ 三行、$b,c,d$ 三行必须被涂上同一种颜色的时候都会对 $F_{i,j}$ 产生 $G_{k,j}$ 的贡献，也就是说 $G_{k,j}$ 会对 $F_{i,j}$ 产生 $\dbinom{k}{i}$ 的贡献。

也就是说 $F_{i,j}=\sum\limits_{k=i}^nG_{k,j}\times\dbinom{k}{i}$

套用二项式反演的公式可得 $G_{i,j}=\sum\limits_{k=i}^nF_{k,j}\times\dbinom{k}{i}\times(-1)^{k-i}$

同理可得 $H_{i,j}=\sum\limits_{l=j}^nG_{i,l}\times\dbinom{l}{j}\times(-1)^{l-j}=\sum\limits_{k=i}^n\sum\limits_{l=j}^nF_{k,l}\times\dbinom{k}{i}\dbinom{l}{j}\times(-1)^{k+l-i-j}$

而最终的答案为 $3^{n^2}-H_{0,0}$

故我们只需求出 $H_{0,0}$ 即可。

而 $H_{0,0}=\sum\limits_{i=0}^n\sum\limits_{j=0}^nF_{i,j}\times (-1)^{i+j}$

考虑 $F_{i,j}$ 是什么东西：

- 若 $i=0$，那么选择 $j$ 列的方案数为 $\dbinom{n}{j}$，为这 $j$ 列每列找一种颜色的方案数为 $3^j$，剩下 $n(n-j)$ 个格子随便填的方案数为 $3^{n(n-j)}$，故最终 $F_{i,j}=\dbinom{n}{j}\times 3^{n(n-j)+j}$
- 若 $j=0$，同理可得 $F_{i,j}=\dbinom{n}{j}\times 3^{n(n-i)+i}$
- 若 $i\neq 0$ 且 $j\neq 0$，那么选择 $i$ 行的方案数为 $\dbinom{n}{i}$，选择 $j$ 列的方案数为 $\dbinom{n}{j}$，对这 $i$ 行和 $j$ 列选一种颜色的方案数为 $3$，剩下 $(n-i)(n-j)$ 个格子随便填的方案数为 $3^{(n-i)(n-j)}$。故最终 $F_{i,j}=3^{(n-i)(n-j)+1}\times\dbinom{n}{i}\dbinom{n}{j}$

最后考虑怎样计算 $H_{0,0}$，对于 $i=0$ 或 $j=0$ 的部分 $\mathcal O(n)$ 一遍显然是没问题的。关键是 $i\neq 0$ 且 $j\neq 0$ 的部分。即 $\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-1}3^{ij+1}\times\dbinom{n}{i}\dbinom{n}{j}\times (-1)^{i+j}$

把含 $i$ 的部分提到外面来可得 $3\times\sum\limits_{i=0}^{n-1}(-1)^i\dbinom{n}{i}\times\sum\limits_{j=0}^{n-1}3^{ij}\times\dbinom{n}{j}\times (-1)^{j}$

注意到 $3^{ij}\times (-1)^j=(-3^i)^j$，故原式 $=3\times\sum\limits_{i=0}^{n-1}(-1)^i\dbinom{n}{i}\times\sum\limits_{j=0}^{n-1}(-3^{i})^j\times\dbinom{n}{j}$

后面的 $\sum$ 一脸可以二项式定理的样子，如果补上一个 $1^{n-j}$ 就更明显了：$3\times\sum\limits_{i=0}^{n-1}(-1)^i\dbinom{n}{i}\times\sum\limits_{j=0}^{n-1}(-3^{i})^j\times\dbinom{n}{j}\times 1^{n-j}$

这里有一个坑点，后面的 $\sum$ 是枚举到 $n-1$ 的，而我们二项式定理要枚举到 $n$，故原式 $=3\times\sum\limits_{i=0}^{n-1}(-1)^i\dbinom{n}{i}\times[\sum\limits_{j=0}^{n}(-3^{i})^j\times\dbinom{n}{j}\times 1^{n-j}-(-3^i)^n]$

这样就可以放心大胆地二项式定理了：$=3\times\sum\limits_{i=0}^{n-1}(-1)^i\dbinom{n}{i}\times[(1-3^i)^n-(-3^i)^n]$

这样就可以在 $\mathcal O(n\log n)$ 的时间内计算出 $H_{0,0}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e6;
const int MOD=998244353;
int qpow(int x,ll e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1ll) ret=1ll*ret*x%MOD;
	return ret;
}
int n,ans=0,fac[MAXN+5],ifac[MAXN+5];
int binom(int x,int y){return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;}
//int calcf(int x,int y){
//	if(!x) return qpow(3,1ll*n*(n-y)+y);
//	if(!y) return qpow(3,1ll*n*(n-x)+x);
//	return qpow(3,1ll*(n-x)*(n-y)+1);
//}
int main(){
	scanf("%d",&n);
	fac[0]=1;for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[n]=qpow(fac[n],MOD-2);for(int i=n-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
//	for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
//		if((i+j)&1) ans=(ans-1ll*calcf(i,j)*binom(n,i)%MOD*binom(n,j)%MOD+MOD)%MOD;
//		else ans=(ans+1ll*calcf(i,j)*binom(n,i)%MOD*binom(n,j)%MOD)%MOD;
//	}
	for(int i=1;i<=n;i++){
		if(i&1) ans=(ans-1ll*qpow(3,1ll*n*(n-i)+i)*binom(n,i)%MOD+MOD)%MOD;
		else ans=(ans+1ll*qpow(3,1ll*n*(n-i)+i)*binom(n,i)%MOD)%MOD;
	} (ans*=2)%=MOD;(ans+=qpow(3,1ll*n*n))%=MOD;
	int pw3=1;
	for(int i=0;i<n;i++){
		int val=1ll*(qpow((1-pw3+MOD)%MOD,n)-qpow(MOD-pw3,n)+MOD)%MOD*3%MOD;
		if(i&1) ans=(ans-1ll*binom(n,i)*val%MOD+MOD)%MOD;
		else ans=(ans+1ll*binom(n,i)*val%MOD)%MOD;
		pw3=3ll*pw3%MOD;
	} ans=(qpow(3,1ll*n*n)-ans+MOD)%MOD;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：skydogli (赞：1)

这题好像直接做就好了？

如果单独考虑行的情况，大概大部分人都能用简单的容斥乱杀。当然，也可以钦定第 $i$ 行为第一次满足条件的行（也就是之前的行都不合法），这个东西求和的式子是：

$$\sum_{i=1}^n (3^{n}-3)^{i-1}\times 3\times {(3^n)}^{n-i}$$

前面式子是每行都有3种满足条件的情况不能选，然后这一行红绿蓝3种合法情况，后面随意。

而现在加入了列，我们只需要强制没有任何一行满足条件，再统计列的方案即可，这样就能保证不重不漏了。于是我们只要简单地限制一下行，用容斥做的话非常方便。

枚举 $i$ 列满足条件：

$$\sum_{i=1}^n (-1)^{i-1}\binom{n}{i}f_i$$

其中 $f_i$ 表示钦定前 $i$ 列满足条件的方案数，需要考虑这 $i$ 列是否都是同一颜色。

不同的贡献：

$$(3^i-3)\times {(3^{n-i})}^{n}$$

前面是选列的方案数后面是其他列可以任意选的方案数。

全部相同的贡献：

$$3\times (3^{n-i}-1)^n$$

枚举红绿蓝，然后每一列都不能全都是这个颜色。

$f_i$ 就是两个加起来了。


这题比较简单，就顺便讲讲这个容斥的正确性。

考虑任意一种有 $m$ 列符合条件的情况，他会在 $i=1$ 时统计 $\binom{m}{1}$ 次，在 $i=2$ 时统计 $\binom{m}{2}$ 次...在 $i=k$ 时统计 $\binom{m}{k}$ 次。（注意这个统计次数和上面的式子没有关系） 

所以总的贡献是：

$$\sum_{i=1}^m \binom{m}{i}(-1)^{i-1}$$
$$=-\sum_{i=1}^m \binom{m}{i}(-1)^{i}$$
$\binom{n}{0}(-1)^0$恒为 $1$，我们补进去。
$$=-(-1+\sum_{i=0}^m \binom{m}{i}(-1)^{i})$$

后面的式子等于 $(1-1)^m$ （二项式定理）

考虑$0^0=1,0^i=0(i\neq0)$。

所以右边的式子在 $m\neq 0$ 时都是0。

于是我们发现每个合法情况的贡献都是 $1$ 。

那么我们就可以心安理得地切掉这题了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Mod 998244353
int read(){
	int a=0,fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*fh;
}
int ksm(int a,int x){
	int ans=1,w=a;
	while(x){
		if(x&1)ans=ans*w%Mod;
		w=w*w%Mod;
		x>>=1;
	}
	return ans;
}
#define MN 1000005
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
int n;
int pw[MN],fac[MN],dfac[MN],inv[MN];
int C(int m,int n){
	if(m<n)return 0;
	return fac[m]*dfac[n]%Mod*dfac[m-n]%Mod;
}
signed main(){
	n=read();
	int tmp=ksm(3,n);
	pw[0]=1;for(int i=1;i<=n;++i)pw[i]=pw[i-1]*tmp%Mod;
	fac[0]=dfac[0]=fac[1]=dfac[1]=inv[1]=1;
	for(int i=2;i<=n;++i){
		fac[i]=fac[i-1]*i%Mod;
		inv[i]=(Mod-Mod/i)*inv[Mod%i]%Mod;
		dfac[i]=dfac[i-1]*inv[i]%Mod;
	}
	int ans=0,w=tmp-3,buf=1;
	for(int i=1;i<=n;++i){
		ans=(ans+buf*pw[n-i]*3)%Mod;	
		buf=buf*w%Mod;
	}
	int iv=ksm(w,Mod-2);
	for(int i=1;i<=n;++i){
		buf=buf*iv%Mod;
		int tmp=3*C(n,i)%Mod*ksm(ksm(3,n-i)-1,n)%Mod;

		tmp=(tmp+(ksm(3,i)-3)*C(n,i)%Mod*ksm(ksm(3,n-i),n))%Mod;
		tmp=tmp%Mod;
		if(i-1&1) tmp=Mod-tmp;
		ans=(ans+tmp)%Mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：ComeIntoCalm (赞：1)


这里只讨论狭义容斥做法。

实际上选择补集来得更容易一些。

所以就变成：恰好0行0列颜色相同

然后可以用至少$i$行$j$列容斥。

先随机钦点$i(i>0)$行，发现如果此时再钦点$j(j>0)$行只能涂三种颜色。

剩下的$(n-i)\times(n-j)$任意。

于是就有$\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}C_n^iC_n^j\times3^{(n-i)(n-j)+1}$

当$i$或$j$其中任意一个是0时显然这$i$或$j$行可以每行一个颜色。

因为只有一个上界$n$，所以$i=0,j=s$的情况和$i=s,j=0$的情况是一样的

上述式子$3$的指数$+1$变为$+i$。

当然发现$i=j=0$的情况被算了两次，减掉就好了

当然$\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}C_n^iC_n^j\times3^{(n-i)(n-j)+1}$这个式子发现不能$nlogn$算。

实际上把3提到最前边后边变成$(3^{n-i})^{n-j}$就可以套二项式定理了。

所以实际上啥硬核操作也不需要，也不需要乱蒙式子。

当然也可以直接1维容斥，不过二维容斥显得更好理解。

复杂度$nlogn$

---

## 作者：cosf (赞：0)

## [CF997C](https://codeforces.com/problemset/problem/997/C) [满是星星的天空](https://www.luogu.com.cn/problem/CF997C)

## 思路

一眼丁真，用容斥原理。

我们可以令 $f(i, j)$ 表示有 $i$ 行颜色相同（行之间不一定相同），$j$ 列颜色相同。

那么当 $ij \not= 0$ 时，所有被指定的行和列颜色是一样的，而当 $i, j$ 中存在 $0$ 时，另一个所指的行或列之间的颜色就不一定一样了。

当 $j=0$ 时，$f(i, 0) = \binom{n}{i}3^i3^{n(n-i)}$。因为 $i, j$ 在定义中时可互换的（对称式），所以必有 $f(0, j) = f(j, 0)$。

当 $ij\not=0$ 时，则有 $f(i, j) = \binom{n}{i}\binom{n}{j}3\cdot3^{(n-i)(n-j)}$。

那么最终的答案就是 $R = \sum_{i=0}^n\sum_{j=0}^n[i+j\not=0](-1)^{i+j+1}f(i, j)$。

等等，这个式子是 $O(n^2\log n)$ 才能求的，需要进行优化。

我们先把刚刚分析的 $ij = 0$ 与 $ij \not=0$ 分开：

$$
R = (2\sum_{i=1}^n(-1)^{i+1}f(i, 0)) + \sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j+1}f(i, j)
$$

然后拆开 $f$：

$$
R = (2\sum_{i=1}^n(-1)^{i+1}f(i, 0)) + 3\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j+1}\binom{n}{i}\binom{n}{j}3^{n^2-in-nj+ij}
$$

对右半边变形（有点跳步）：

$$
R = (2\sum_{i=1}^n(-1)^{i+1}f(i, 0)) - 3^{ n^2 + 1} \sum_{i = 1}^n 3^{-in}(-1)^i \binom{n}{i} \sum_{j = 1}^n \binom{n}{j} (-3^{-n+i})^j
$$

运用二项式定理（二项式中另一个数为 $1$，最后要减去 $0$ 次方）：

$$
R = (2\sum_{i=1}^n(-1)^{i+1}f(i, 0)) - 3^{ n^2 + 1} \sum_{i = 1}^n 3^{-in}(-1)^i \binom{n}{i} ((1 - 3^{i - n})^n - 1)
$$

那么我们就成功地把复杂度除以了一个 $n$，只剩下 $O(n\log n)$ 了，可以通过本题。

事实上，$R$ 的左半边也可以变形然后用二项式定理，不过它已经可以 $O(n\log n)$ 求了，不必再进行优化。

## 实现

这里不仅仅涉及大量的幂，而且这些幂很多都是负数次幂，所以临时算逆元很可能会导致复杂度错误或者常数过大。建议的方案是预处理阶乘（和其逆元）以及 $3$ 的次幂（及其逆元）。注意，负数次幂可以由费马小定理转化为正数次幂。

假设模数为 $M$，那么有 $a^{-b} = a^{M-1-b}$（模 $M$ 意义下相等）。通过转化幂数，我们可以避免很多不必要的空间和计算量。

这里还涉及到了大量的负数，所以建议在模数的时候加上一句 `(... + M)`，否则可能会导致结果错误。**特别注意，如果你是两半边分开算的，最后加在一起要加两次 `M`，因为两边都可能是大负数，没有加两次就会 `WA on T9`。**

## 代码

```cpp
/*
 * 省略预处理与函数实现。
 * pow 为幂运算，inv 为逆元，p3 为 3 的幂，C 为组合数。
 * MOD 为模数
 */
int main()
{
    ll n;
    cin >> n;
    ll l = 0; // 左半边
    for (ll i = 1; i <= n; i++)
    {
        l = (l + C(n, i) * p3((n * n - i * n + i) % (MOD - 1)) % MOD * (2 * (i & 1) - 1)) % MOD;
    }
    l = l * 2 % MOD;
    ll r = 0; // 右半边
    for (int i = 1; i <= n; i++)
    {
        r = (r + C(n, i) * p3((MOD - 1 - n) * i % (MOD - 1)) % MOD * (pow(1 - p3(i - n + MOD - 1), n, MOD) - 1) % MOD * (1 - 2 * (i & 1))) % MOD; // 注意不要写错（我调了大半天）
    }
    r = r * (p3((n * n + 1) % (MOD - 1))) % MOD;
    cout << (
        l - r + MOD + MOD // 要加两次！！！
        ) % MOD << endl;
    return 0;
}

```


---

## 作者：翼德天尊 (赞：0)

> $n\times n$ 方格，用三种颜色染色，需使得至少一行或一列为同种颜色，求有多少种染色方案。
>
> $1\le n\le 10^6$。 

考虑容斥，将「至少一行或至少一列」作为全集，「第 $i$ 行选择」「第 $i$ 列选择」作为属性，则有：
$$
num=\sum_{i=0}^n\sum_{j=0,i+j>0}^n(-1)^{i+j-1}C_{n}^iC_{n}^js(i,j)
$$
其中 $s(i,j)$ 被我们单独摘了出来，因为当只有行或只有列的时候，是可以对整行或整列涂多种颜色的；而当行列都有的时候，这些整行和整列因为存在交集，就只能涂成一种颜色了。故有：
$$
s(i,j)=\begin{cases}3^{i+(n-i)n}&j=0\\3^{j+(n-j)n}&i=0\\3^{1+(n-i)(n-j)}&i\neq0\&j\neq0\end{cases}
$$
此时时间复杂度为 $O(n^2)$，考虑优化。

先把 $i=0,j=0$ 和 $i\neq 0,j\neq0$ 分开，对于前者，有：
$$
sum_1=2\sum_{i=1}^n(-1)^{i-1}C_n^i3^{i+(n-i)n}
$$
 对于后者，有：
$$
sum_2=\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j-1}C_n^iC_n^j3^{1+(n-i)(n-j)}
$$
$i,j$ 贡献混在一起没法优化，那就拆开：
$$
\begin{aligned}sum_2&=\sum_{i=1}^n(-1)^{i-1}C_n^i\sum_{j=1}^n(-1)^jC_n^j3^{n^2+1-ni-nj+ij}
\\&=3^{n^2+1}(-1)\sum_{i=1}^n(-1)^{i}C_n^i3^{-ni}\sum_{j=1}^n(-1)^jC_n^j3^{-nj}\times 3^{ij}\end{aligned}
$$
现在最烦人的就是这个 $3^{ij}$ 了。 以下便是我怎么也想不到的反用二项式定理环节（ 

考虑 $sum_2$ 中的第二个求和可以化作：
$$
\sum_{j=1}^nC_n^j(-3^{i-n})^j
$$
由于根据二项式定理的扩展，有：
$$
(a+b)^n=\sum_{i=0}^nC_{n}^ia^ib^{n-i}
$$
故将 $a=1,b=-3^{i-n}$ 代入得：
$$
(1-3^{i-n})^n=\sum_{j=0}^nC_n^j1^{n-j}(-3^{i-n})^{j}=\sum_{j=0}^nC_n^j(-3^{i-n})^j
$$
故第二个求和可化为：
$$
\sum_{j=0}^nC_n^j(-3^{i-n})^j-1=(1-3^{i-n})^n-1
$$
即原式变成：
$$
sum_2=3^{n^2+1}(-1)\sum_{i=1}^n(-1)^{i}C_n^i3^{-ni}((1-3^{i-n})^n-1)
$$
于是我们就将总时间复杂度优化到了 $O(n\log n)$！

这也启发我们，**对于「求和+组合数」的式子，优化复杂度时可以考虑使用二项式定理**！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
const int V=1e6;
const int mod=998244353;
int n,jc[N],inv[N],ans,ans2;
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
ll ksm(ll x,ll y){
    ll ans=1;
    while (y){
        if (y&1) ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
void init(){
    jc[0]=inv[0]=1;
    for (int i=1;i<=V;i++) jc[i]=1ll*jc[i-1]*i%mod;
    inv[V]=ksm(jc[V],mod-2);
    for (int i=V-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int x,int y){
    return 1ll*jc[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
#endif
    init();
    n=read();
    for (int i=1,f=1;i<=n;i++,f=-f){
        ans=(ans+1ll*f*C(n,i)*ksm(3,i+1ll*(n-i)*n)%mod)%mod;
    }
    ans=(ans+ans)%mod;
    int inv3=ksm(3,mod-2);
    for (int i=1,f=-1;i<=n;i++,f=-f){
        ans2=(ans2+1ll*f*C(n,i)*ksm(inv3,1ll*n*i)%mod*(ksm(1-ksm(inv3,n-i),n)-1)%mod)%mod;
    }
    ans2=(1ll*ans2*ksm(3,1ll*n*n+1)*(-1)%mod+ans)%mod;
    cout<<(ans2+mod)%mod<<"\n";
    return 0;
}
```

---

## 作者：chenxia25 (赞：0)

**[Portal]( https://www.luogu.com.cn/problem/CF997C )**

一开始死想想不出来，后来看了题解发现是容斥 + 推柿子。我对容斥还是太不熟悉了啊/kk

注意到「一行或一列是同一种颜色」的字眼，其实是容斥的标志。考虑每行每列（一共 $2n$ 个元素）是同一种颜色的方案集合，那么最终答案就是这 $2n$ 个集合的并的大小。考虑对琪容斥。

那么某些集合的交是「这些行 / 列都要是同一种颜色的方案集合」这种形式。那么每个交的大小要比并容易算多了，显然相等是等价关系，于是看建图之后有几个连通分量，$3$ 的它次方就好了。显然可以分成两类：

1. 全是行 / 全是列。那么对于 $i$ 个集合的交集的大小，它们的方案数一定是 $3^{n^2-i(n-1)}$。也就是说我们可以不必枚举每个 bitmask，因为只要参与交集的集合数量相同，它的值就是一样的，可以用乘法（乘个组合数即可），枚举参与交集的集合数量即可。说明容斥很可能也是有多项式复杂度的。那么这种情况对答案的贡献是
   $$
   2\sum_{i=1}^n(-1)^{i+1}\dbinom ni3^{n^2-i(n-1)}
   $$
   这个直接照着跑一遍就好了；

2. 既有行又有列。那么考虑 $i$ 行 $j$ 列的方案数。显然所有这些行列所包含的格子都连成了一个连通块，所以方案数是 $3^{n^2-in-j(n-i)+1}$。那么总贡献就是
   $$
   \sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j+1}\dbinom ni\dbinom nj3^{n^2-in-j(n-i)+1}
   $$
   这个是 $\Omega\!\left(n^2\right)$ 的，考虑推柿子优化。首先把所有只和 $i$ 相关或常数提到第一个 $\sum$ 后面去：
   $$
   \sum_{i=1}^n(-1)^{i+1}\dbinom ni3^{n^2-in+1}\sum_{j=1}^n(-1)^j\dbinom nj3^{-j(n-i)}
   $$
   现在要想办法把后面的 $\sum$ 消掉。注意到里面既有组合数又有指数，很像二项式的形式，于是考虑变形，然后二项式定理逆用：
   $$
   \begin{aligned}\sum_{j=1}^n(-1)^j\dbinom nj3^{-j(n-i)}&=\sum_{j=0}^n\dbinom nj\left(-3^{-(n-i)}\right)^j-1\\&=\sum_{j=0}^n\dbinom nj\left(-3^{-(n-i)}\right)^j1^{n-j}-1\\&=\left(-3^{-(n-i)}+1\right)^n-1\end{aligned}
   $$

这样就可以很愉快的线性对数了。

**_[code]( https://www.luogu.com.cn/paste/i09n1zxx )_**

---

## 作者：lhm_ (赞：0)

直接求不好求，考虑用总方案数减去不合法方案数。设 $f_{i,j}$ 为至少有 $i$ 行 $j$ 列颜色相同的方案数，设 $g_{i,j}$ 为恰好有 $i$ 行 $j$ 列颜色相同的方案数，得：
$$
\large f(x,y)=\sum_{i=x}^n\sum_{j=y}^n\binom{i}{x}\binom{i}{y}g(i,j)
$$
然后发现其可以高维二项式反演，高维反演即为每个维度的反演系数直接乘起来，进行高维二项式反演得：
$$
\large g(x,y)=\sum_{i=x}^n\sum_{j=y}^n(-1)^{i+j-x-y}\binom{i}{x}\binom{i}{y}f(i,j)
$$
即答案为：
$$
\large ans=3^{n^2}-g(0,0)
$$


考虑计算 $f$，得：
$$
\large f(i,j) =
\begin{cases}
	\binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)+1} &ij \not = 0 \\
	\\
	\binom{n}{i+j}3^{n(n-i-j)+i+j} &ij=0,i+j \not =0 \\
	\\
	3^{n^2} &i+j=0
\end{cases}\\
$$
当行列都存在相同颜色时，因为行列有交叉部分，所以其只能取同一种颜色，而只有行存在相同颜色或只有列存在相同颜色时，其颜色的选取时不受限制的。

然后计算 $g(0,0)$：
$$
\large\begin{aligned}
	g(0,0)&=\sum_{i=0}^n\sum_{j=0}^n(-1)^{i+j}f(i,j) \\
	&=\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}f(i,j)+2\sum_{i=1}^n(-1)^if(i,0)+f_{0,0} 
\end{aligned} \\
$$
因为第一个和式的原因，直接计算的复杂度是 $O(n^2)$ 的，无法接受，考虑进行化简：
$$
\large\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}f(i,j) \\

=&\sum_{i=1}^n\sum_{j=1}^n(-1)^{i+j}\binom{n}{i}\binom{n}{j}3^{(n-i)(n-j)+1} \\

=&\sum_{i=1}^n(-1)^{i}\binom{n}{i}\sum_{j=1}^n(-1)^{j}\binom{n}{j}3^{n^2-(i+j)n+ij+1} \\

=&3^{n^2+1}\sum_{i=1}^n(-1)^{i}\binom{n}{i}3^{-in}\sum_{j=1}^n\binom{n}{j}(-3^{i-n})^j \\

=&3^{n^2+1}\sum_{i=1}^n(-1)^{i}\binom{n}{i}3^{-in}((1-3^{i-n})^n-1) \\
\end{aligned}\\
$$
最终答案为：
$$
\large ans=3^{n^2}-g(0,0)=-3^{n^2+1}\sum_{i=1}^n(-1)^{i}\binom{n}{i}3^{-in}((1-3^{i-n})^n-1)-2\sum_{i=1}^n(-1)^i\binom{n}{i}3^{n(n-i)+i}
$$

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define p 998244353
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n,v1,v2;
ll fac[maxn],ifac[maxn];
ll qp(ll x,ll y)
{
    ll v=1;
    while(y)
    {
        if(y&1) v=v*x%p;
        x=x*x%p,y>>=1;
    }
    return v;
}
ll C(int n,int m)
{
    return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
void init()
{
    fac[0]=ifac[0]=1;
    for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%p;
    ifac[n]=qp(fac[n],p-2);
    for(int i=n-1;i;--i) ifac[i]=ifac[i+1]*(i+1)%p;
}
int main()
{
    read(n),init();
    for(int i=1;i<=n;++i)
    {
        ll v=C(n,i)*qp(qp(3,i*n),p-2)%p*(qp((1-qp(qp(3,n-i),p-2)+p)%p,n)-1+p)%p;
        if(i&1) v1=(v1-v+p)%p;
        else v1=(v1+v+p)%p;
    }
    for(int i=1;i<=n;++i)
    {
        ll v=C(n,i)*qp(3,n*(n-i)%(p-1)+i)%p;
        if(i&1) v2=(v2-v+p)%p;
        else v2=(v2+v+p)%p;
    }
    printf("%lld",((-qp(3,(n*n+1)%(p-1))*v1%p+p)%p-2*v2%p+p)%p);
    return 0;
}
```

---

## 作者：Erina (赞：0)

## CF997C

> 一道需要拼命取反的题目

这一题...... 推式子两小时敲代码十分钟

好了进入正题: 怎么推式子

通过多年(雾)的经验得知, 至少有一个通常要变成全都不类的问题, 也就是取反.

现在问题变成了: 有多少种情况, 使得所有的行列颜色都不同.

这是个~~该死的~~二维问题, 我们应当先去掉一维, 只考虑每一行不相同, 然后再通过某种奇技淫巧把列的情况加进去.

不难发现所有行的颜色都不同的种类数是$(3^n-3)^n$因为对于每一行来说, 其它的行对它没有影响(不考虑列的时候), 所以我们珂以取反: 先是随便选, 然后去掉这整行全是红色, 蓝色和绿色的情况, 所以我们减$3$, 然后快速幂一下...... 这里不按取反的方式想其实也没有问题......

但是我们要**在已经确定每行的所有格子不能全部相同时**要考虑列的情况...... 怎么办呢? (记住, 加粗的文字很重要, 是接下来讨论的大前提.)

我们再取反一次...... 把"**没有**列的所有格子颜色全部相同"变成"有**至少$1$列**的所有格子颜色全部相同"...... 好绕啊有没有......

但是我们发现取反后还是有点难算, 因为我们经常算出重复情况, 比如说让第一列全部相同, 然后剩下的随便选, 那么肯定会出现第二列全部相同的情况. 而当你考虑第二列全部相同的情况时, 第一列又会过来烦你. 这样就会有重复情况.

这时候考虑容斥原理, 把多的减掉, 把减多的加回来...... (记住哦, 容斥原理的规范表达是" '选出...使它们满足条件, 然后剩下的随便选' 时的种类数", **但是一定要满足大前提!**)

对于选出$i$列使它们中任意一个里面的所有元素全部相同的时候, 要分两种情况, 因为我们要注意大前提: **"每行所有元素不能全部相同"** 所以当这些列的颜色全部相同时, 要分别考虑. (这一点坑了我好久......)

如果给这些列都染同一种颜色, 然后每一行剩下的元素随便填, **最后要去掉一种所有颜色全部相同的情况**, 所以差不多长这样: $({3^{n-i}}-1)^{n}$, 其中$({3^{n-i}}-1)$是每一行的种类数.

如果这些列至少有两列不同, 那么所有行**肯定**不会相同, 不用怂直接上...... 差不多长这样: $(3^{i}-3)*3^{n*(n-i)}$, 后面那一半表示随便选, 多的不用害怕最后容斥会减掉的......

因为容斥原理是先选了$i$列, 所以要乘上$n\choose{i}$

好了差不多就是这样了......

放一下代码.

```cpp
#include<iostream>
using namespace std;
namespace fio {
	streambuf* in = cin.rdbuf();
	char bb[100000], * s = bb, * t = bb;
#define gc() (s==t&&(t=(s=bb)+in->sgetn(bb,1000000),s==t)?EOF:*s++)
	inline int read() {
		int x = 0;
		char ch = gc();
		while (ch < 48)ch = gc();
		while (ch >= 48)x = x * 10 + ch - 48, ch = gc();
		return x;
	}
}using fio::read;
const long long mod = 998244353;
class integer {// 暴力取模
public:
	long long val;
	integer(long long val = 0) :val(val) {}
	integer& operator = (long long x) { val = x; return *this; }
	integer& operator = (integer x) { val = x.val; return *this; }
	integer operator + (integer x) { return integer((val + x.val) % mod); }
	integer operator - (integer x) { return integer((val - x.val + mod) % mod); }
	integer operator * (integer x) { return integer((val * x.val) % mod); }
	integer operator += (integer x) { return (val = (val + x.val) % mod, *this); }
	integer operator -= (integer x) { return (val = (val - x.val + mod) % mod, *this); }
	integer operator *= (integer x) { return (val = (val * x.val) % mod, *this); }
	bool operator == (integer x) { return val == x.val; }
	bool operator !=(integer x) { return val != x.val; }
	bool operator > (integer x) { return val > x.val; }
	bool operator < (integer x) { return val < x.val; }
	friend ostream& operator << (ostream& in, integer x) { return (in << x.val, in); }
};
integer ksm(integer a, long long b = mod - 2) {// 快速幂和逆元
	integer ans;
	for (ans = 1; b; a = a * a, b >>= 1)if (b & 1)ans *= a;
	return ans;
}
long long n;
integer fact[1000005];// 阶乘
integer C(int a, int b) { return fact[a] * ksm(fact[a - b]) * ksm(fact[b]); }// 组合数
integer ans;
int main() {
	fact[0] = 1;
	for (int i = 1; i <= 1000000; i++)fact[i] = fact[i - 1] * i;// 预处理阶乘
	cin >> n;
	ans = ksm(3, 1ll * n * n);
	ans -= ksm(ksm(3, n) - 3/*其实这里也是取反思维*/, n);//记住你取了反
	for (int i = 1; i <= n; i++) {
		if (i & 1) {
			ans += C(n, i) * 3 * ksm((ksm(3, n - i) - 1/*其实这里也是取反思维*/), n);// 如果所有选出来的列的颜色相同
			ans += C(n, i) * (ksm(3, i) - 3/*其实这里也是取反思维*/) * ksm(3, n * (n - i));// 如果至少有两个选出来的列的颜色不同
		}
		else {
			ans -= C(n, i) * 3 * ksm((ksm(3, n - i) - 1), n);//同理
			ans -= C(n, i) * (ksm(3, i) - 3) * ksm(3, n * (n - i));
		}
	}
	cout << ans;
}
```


---

