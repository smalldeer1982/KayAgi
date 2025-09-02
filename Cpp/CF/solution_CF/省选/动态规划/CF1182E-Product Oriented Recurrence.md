# Product Oriented Recurrence

## 题目描述

当 $x \geq 4$ 时，$f_x = c^{2x - 6} \cdot f_{x - 1} \cdot f_{x - 2} \cdot f_{x - 3}$ 。

现在已知 $n,f_1,f_2,f_3,c$ 的值，求 $f_n$ 的值，对 $10^9 + 7$ 取模。

$(4 \leq n \leq 10^{18},1 \leq f_1,f_2,f_3,c \leq 10^9)$

## 样例 #1

### 输入

```
5 1 2 5 3
```

### 输出

```
72900
```

## 样例 #2

### 输入

```
17 97 41 37 11
```

### 输出

```
317451037
```

# 题解

## 作者：liangbowen (赞：22)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1182E)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16974079.html)

$\texttt{z\color{red}ltqwq}$ ![](https://rin.kagamine.xyz:16300/gou.php?color=f1c40f) 推荐矩阵加速题目。其实很不算难啊，不就是模拟吗。

## 思路

首先乘法是不能用矩阵加速直接维护的，考虑答案为 $f_n = c^{k_1} \times f_1^{k_2} \times f_2^{k_3} \times f_3^{k_4}$。

这些都是可以转移的。

对于 $c$ 的**指数**的转移：$\begin{pmatrix}t_{i-2}, t_{i-1}, t_i, 2i-6, 1\end{pmatrix}$ 分别表示最近的三项（$f_{i-2}, f_{i-1}, f_i$）的 $c$ 的指数、以及一些常数。

$$f_{i+1} = c^{2i - 6} \times f_i \times f_{i-1} \times f_{i-2}$$

$\therefore$ 对应的指数 $k_{i+1} = 2\cdot(i + 1) - 6 + k_i + k_{i-1} + k_{i-2}$。

矩阵转移：

$$
\begin{pmatrix}
k_{i-2} & k_{i-1} & k_i & 2i-6 & 1
\end{pmatrix}

\times

\begin{pmatrix}
0 & 0 & 1 & 0 & 0 \\
1 & 0 & 1 & 0 & 0 \\
0 & 1 & 1 & 0 & 0 \\
0 & 0 & 1 & 1 & 0 \\
0 & 0 & 2 & 2 & 1 \\
\end{pmatrix}

=

\begin{pmatrix}
k_{i-1} & k_i & k_{i+1} & 2\cdot(i+1)-6 & 1
\end{pmatrix}
$$

---

对于 $f_1$ 的**指数**的转移：$\{t_{i-2}, t_{i-1}, t_i\}$ 分别表示最近的三项（$f_{i-2}, f_{i-1}, f_i$）的 $f_1$ 的指数。

$$f_{i+1} = c^{2i - 6} \times f_i \times f_{i-1} \times f_{i-2}$$

$\therefore$ 对应的指数 $k_{i+1} = k_i + k_{i-1} + k_{i-2}$。

矩阵转移：

$$
\begin{pmatrix}
k_{i-2} & k_{i-1} & k_i
\end{pmatrix}

=

\begin{pmatrix}
0 & 0 & 1 \\
1 & 0 & 1 \\
0 & 1 & 1
\end{pmatrix}

\times

\begin{pmatrix}
k_{i-1} & k_i & k_{i+1}
\end{pmatrix}
$$

---

对于 $f_2$ 与 $f_3$ 的指数转移，矩阵转移是与 $f_1$ 的相同的。

仅仅是初始化不同。

---

三者对应的指数就是第 $3$ 项，这个自己对上即可。

最后再上快速幂即可求出。

## 代码

不喜欢用重载（次次考场都不会写重载格式），所以代码看起来会很长。

代码其实不用放的，抄一遍上面的矩阵即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int mod = 1e9 + 7;
typedef long long ll;

namespace martix_3 { //矩阵快速幂，懂的直接忽略即可
    void mul(int ANS[][3], int x[][3], int y[][3])
    {
        int ans[3][3] = {};
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    ans[i][j] = (ans[i][j] + 1ll * x[i][k] * y[k][j]) % (mod - 1);
        memcpy(ANS, ans, sizeof ans);
    }
    void ksm(int f[][3], int a[][3], ll y)
    {
        while (y)
        {
            if (y & 1) mul(f, f, a);
            mul(a, a, a);
            y >>= 1;
        }
    }
};
namespace martix_5 { //矩阵快速幂，懂的直接忽略即可
    void mul(int ANS[][5], int x[][5], int y[][5])
    {
        int ans[5][5] = {};
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                for (int k = 0; k < 5; k++)
                    ans[i][j] = (ans[i][j] + 1ll * x[i][k] * y[k][j]) % (mod - 1);
        memcpy(ANS, ans, sizeof ans);
    }
    void ksm(int f[][5], int a[][5], ll y)
    {
        while (y)
        {
            if (y & 1) mul(f, f, a);
            mul(a, a, a);
            y >>= 1;
        }
    }
};
int qpow(int x, int y) //快速幂，懂的直接忽略即可
{
    int ans = 1;
    while (y)
    {
        if (y & 1) ans = (1ll * ans * x) % mod;
        x = (1ll * x * x) % mod;
        y >>= 1;
    }
    return ans;
}
int main()
{
    ll n; int f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;

    int getc_f[5][5] = {0, 0, 0, 0, 1}; //i=3，算c
    int getc_a[5][5] = {
        0, 0, 1, 0, 0,
        1, 0, 1, 0, 0, 
        0, 1, 1, 0, 0,
        0, 0, 1, 1, 0,
        0, 0, 2, 2, 1
    };
    martix_5::ksm(getc_f, getc_a, n - 3);
    int c_k = getc_f[0][2];

    int getf1_f[3][3] = {1, 0, 0}; //i=3，算f1
    int getf1_a[3][3] = {
        0, 0, 1, 
        1, 0, 1, 
        0, 1, 1
    };
    martix_3::ksm(getf1_f, getf1_a, n - 3);
    int f1_k = getf1_f[0][2];

    int getf2_f[3][3] = {0, 1, 0}; //i=3，算f2
    int getf2_a[3][3] = {
        0, 0, 1, 
        1, 0, 1, 
        0, 1, 1
    };
    martix_3::ksm(getf2_f, getf2_a, n - 3);
    int f2_k = getf2_f[0][2];

    int getf3_f[3][3] = {0, 0, 1}; //i=3，算f3
    int getf3_a[3][3] = {
        0, 0, 1, 
        1, 0, 1, 
        0, 1, 1
    };
    martix_3::ksm(getf3_f, getf3_a, n - 3);
    int f3_k = getf3_f[0][2];

    //printf("f_n = c^%d * f1^%d * f2^%d * f3^%d\n", c_k, f1_k, f2_k, f3_k);
    int ans = 1;
    ans = 1ll * ans * qpow(c, c_k) % mod;
    ans = 1ll * ans * qpow(f1, f1_k) % mod;
    ans = 1ll * ans * qpow(f2, f2_k) % mod;
    ans = 1ll * ans * qpow(f3, f3_k) % mod;
    cout << ans;
    return 0;
}
```

希望能帮助到大家！

---

## 作者：Karry5307 (赞：13)

### 题意

给定五个整数 $n,f_1,f_2,f_3,c$，其中数列 $f$ 满足以下递推式：

$$f_x=c^{2x-6}f_{x-1}f_{x-2}f_{x-3}$$

求 $f_n$。

$\texttt{Data Range:}4\leq n\leq 10^{18},1\leq f_1,f_2,f_3,c\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13800860.html)

矩阵快速幂。

首先这个乘起来的东西显然没有什么方法去递推，然而从递推式中可以直接看出 $f_n$ 是类似于 $c^gf_1^{i}f_2^{j}f_3^{k}$ 的形式，所以考虑把每个次数算出来然后快速幂。

注意到这个次数很好算的。设 $f_n$ 中 $c$ 的次数为 $g_n$，那么显然有递推式

$$g_n=2n-6+g_{n-1}+g_{n-2}+g_{n-3}=2(n-1)-4+g_{n-1}+g_{n-2}+g_{n-3}$$

注意到这个东西是常见的非齐次线性递推模样，于是可以高高兴兴的走一波矩阵：

$$\begin{pmatrix}g_n\\g_{n-1}\\g_{n-2}\\n\\1\end{pmatrix}=\begin{pmatrix}1&1&1&2&-4\\1&0&0&0&0\\0&1&0&0&0\\0&0&0&1&1\\0&0&0&0&1\end{pmatrix}\begin{pmatrix}g_{n-1}\\g_{n-2}\\g_{n-3}\\n-1\\1\end{pmatrix}$$

然后考虑递推 $f_1,f_2,f_3$ 的次数。以 $f_1$ 为例，设 $f_n$ 中 $f_1$ 的次数为 $h_n$，那么有

$$h_n=h_{n-1}+h_{n-2}+h_{n-3}$$

这个转移矩阵挺好写的，也就是：

$$\begin{pmatrix}h_n\\h_{n-1}\\h_{n-2}\end{pmatrix}=\begin{pmatrix}1&1&1\\1&0&0\\0&1&0\end{pmatrix}\begin{pmatrix}h_{n-1}\\h_{n-2}\\h_{n-3}\end{pmatrix}$$

同时注意到 $f_2$ 和 $f_3$ 次数的递推式也是这个东西，只不过 $h_1,h_2,h_3$ 不同而已，于是这个也可以递推出来了，然后就做完了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51,MOD=1e9+7;
struct Matrix{
	ll num[6][6];
	Matrix()
	{
		memset(num,0,sizeof(num));
	}
	inline ll* operator [](const ll &x)
	{
		return num[x];
	}
	inline const ll* operator [](const ll &x)const
	{
		return num[x];
	}
};
Matrix mat,mat2,x,x2;
ll f1,f2,f3,c,res;
li n;
inline li read()
{
    register li num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline Matrix operator *(Matrix x,Matrix y)
{
	Matrix res;
	for(register int i=1;i<=5;i++)
	{
		for(register int j=1;j<=5;j++)
		{
			for(register int k=1;k<=5;k++)
			{
				res[i][j]=(res[i][j]+(li)x[i][k]*y[k][j]%(MOD-1))%(MOD-1);
			}
		}
	}
	return res;
}
inline Matrix qpow(Matrix base,li exponent)
{
	Matrix res;
	for(register int i=1;i<=5;i++)
	{
		res[i][i]=1;
	}
	while(exponent)
	{
		if(exponent&1)
		{
			res=res*base;
		}
		base=base*base,exponent>>=1;
	}
	return res;
}
int main()
{
	n=read(),f1=read(),f2=read(),f3=read(),c=read(),res=1;
	mat[1][1]=mat[2][1]=mat[3][1]=mat[1][2]=mat[2][3]=mat[4][4]=mat[5][4]=1;
	mat[5][5]=x[1][5]=mat2[1][1]=1,mat[4][1]=2,mat[5][1]=MOD-5,x[1][4]=3;
	mat2[2][1]=mat2[3][1]=mat2[1][2]=mat2[2][3]=x2[1][3]=1;
	res=qpow(c,(x*qpow(mat,n-3))[1][1]);
	res=(li)res*qpow(f1,(x2*qpow(mat2,n-3))[1][1])%MOD,x2[1][3]=0,x2[1][2]=1;
	res=(li)res*qpow(f2,(x2*qpow(mat2,n-3))[1][1])%MOD,x2[1][2]=0,x2[1][1]=1;
	res=(li)res*qpow(f3,(x2*qpow(mat2,n-3))[1][1])%MOD,printf("%d\n",res);
}
```

---

## 作者：Heartlessly (赞：12)

## Description

当 $x \geq 4$ 时，$f_x = c^{2x - 6} \cdot f_{x - 1} \cdot f_{x - 2} \cdot f_{x - 3}$ 。

现在已知 $n,f_1,f_2,f_3,c$ 的值，求 $f_n$ 的值，对 $10^9 + 7$ 取模。

$(4 \leq n \leq 10^{18},1 \leq f_1,f_2,f_3,c \leq 10^9)$

## Solution

一道比较有思维难度的 **矩阵加速** 。

一般情况下转移都是加法，而这道题是乘法，所以考虑转换。

我们可以先列举出前几个数。同底数幂相乘，底数不变，指数相加。

$f_1 = c^0 \cdot f_1^1 \cdot f_2^0 \cdot f_3^0$

$f_2 = c^0 \cdot f_1^0 \cdot f_2^1 \cdot f_3^0$

$f_3 = c^0 \cdot f_1^0 \cdot f_2^0 \cdot f_3^1$

$f_4 = c^2 \cdot f_1^1 \cdot f_2^1 \cdot f_3^1$

$f_5 = c^6 \cdot f_1^1 \cdot f_2^2 \cdot f_3^2$

$f_6 = c^{14} \cdot f_1^2 \cdot f_2^3 \cdot f_3^4$

$f_7 = c^{30} \cdot f_1^4 \cdot f_2^6 \cdot f_3^7$

$\cdots\cdots$

不难发现对于每一个 $f_i$，我们都可以表示为

$$f_i = c^{w_i} \cdot f_{1}^{x_i} \cdot f_{2}^{y_i} \cdot f_{3}^{z_i}$$

$w_i,x_i,y_i,z_i$ 的递推方程也可以写出。

$w_i = w_{i - 1} + w_{i - 2} + w_{i - 3} + 2i - 6$

$x_i = x_{i - 1} + x_{i - 2} + x_{i - 3}$

$y_i = y_{i - 1} + y_{i - 2} + y_{i - 3}$

$z_i = z_{i - 1} + z_{i - 2} + z_{i - 3}$

我们可以先用 **矩阵加速** 分别求出 $4$ 个指数 $w_n,x_n,y_n,z_n$ 的值，再用快速幂求得 $f_n$ 。

对于 $x,y,z$ 数组，因为转移方程相同，所以转移矩阵也相同。这里以 $x$ 为例。

$$\begin{bmatrix}1&1&1\\1&0&0\\0&1&0\end{bmatrix}\times \begin{bmatrix}x_{i-1}\\x_{i-2}\\x_{i-3}\end{bmatrix}=\begin{bmatrix}x_i\\x_{i-1}\\x_{i-2}\end{bmatrix}$$

因为 $x_i = x_{i - 1} + x_{i - 2} + x_{i - 3}$，所以矩阵第一行全部是 $1$ 。$x_{i - 1},x_{i - 2}$ 都可以在上一个矩阵中找到，对应位置标为 $1$ 。

初始矩阵：

$$\begin{bmatrix}0\\0\\1\end{bmatrix}=\begin{bmatrix}x_3\\x_2\\x_1\end{bmatrix}$$

$$\begin{bmatrix}0\\1\\0\end{bmatrix}=\begin{bmatrix}y_3\\y_2\\x_1\end{bmatrix}$$

$$\begin{bmatrix}1\\0\\0\end{bmatrix}=\begin{bmatrix}z_3\\z_2\\z_1\end{bmatrix}$$

通过 $f_1,f_2,f_3$ 得到。

答案矩阵：

$$\begin{bmatrix}1&1&1\\1&0&0\\0&1&0\end{bmatrix}^{n - 3}\times \begin{bmatrix}x_{3}\\x_{2}\\x_{1}\end{bmatrix}=\begin{bmatrix}x_n\\x_{n-1}\\x_{n-2}\end{bmatrix}$$

$x_n,y_n,z_n$ 都是取矩阵第一行第一列的值。

$w$ 数组就稍微麻烦一些了，因为多了一项 $2i - 6$ 。

$$\begin{bmatrix}1&1&1&1&1\\1&0&0&0&0\\0&1&0&0&0\\0&0&0&1&1\\0&0&0&0&1\end{bmatrix}\times \begin{bmatrix}w_{i-1}\\w_{i-2}\\w_{i-3}\\2(i - 1) - 6\\2\end{bmatrix}=\begin{bmatrix}w_i\\w_{i-1}\\w_{i-2}\\2i - 6\\2\end{bmatrix}$$

因为 $w_i = w_{i - 1} + w_{i - 2} + w_{i - 3} + 2(i - 1) - 6 + 2$，所以第一行全部是 $1$ 。$w_{i - 1},w_{i - 2}$ 可以在上一个矩阵中找到，对应位置标为 $1$ 。$2i - 6 = 2(i - 1) - 6 + 2$，所以第四列和第五列为 $1$ 。对于 $2 = 2$，把第五列标为 $1$ 。

初始矩阵：

$$\begin{bmatrix}0\\0\\0\\0\\2\end{bmatrix}=\begin{bmatrix}w_3\\w_2\\w_1\\2 \cdot 3 - 6 = 0\\2\end{bmatrix}$$

可以直接得出。

答案矩阵：

$$\begin{bmatrix}1&1&1&1&1\\1&0&0&0&0\\0&1&0&0&0\\0&0&0&1&1\\0&0&0&0&1\end{bmatrix}^{n - 3}\times \begin{bmatrix}w_3\\w_2\\w_1\\2 \cdot 3 - 6 = 0\\2\end{bmatrix}=\begin{bmatrix}w_n\\w_{n-1}\\w_{n-2}\\2n - 6\\2\end{bmatrix}$$

$w_n$ 也同样取矩阵第一行第一列的值。

最后的结果要对 $10^9 + 7$ 取模，但是在做 **矩阵加速** 的过程中，指数肯定不能直接对它取模。这里要用到 **扩展欧拉定理**：

若 $a,p$ 互质，则

$$a^b \equiv a^{b \bmod \varphi(p)} \pmod p$$

因为 $p$ 是质数，所以 $a,p$ 一定互质。我们可以将指数对 $\varphi(p) = p - 1 = 10^9 + 6$ 取模，就能达到降幂的效果。

分别求出 $w_n,x_n,y_n,z_n$，最后用快速幂合并答案得到 $f_n$ 。时间复杂度为 $O(\log n)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const LL MOD = 1e9 + 7, PHI = 1e9 + 6;
LL n, f1, f2, f3, c, ans;

struct Matrix {
    int size;
    LL mat[6][6];
    
    Matrix(int x) {
        size = x;
        memset(mat, 0, sizeof (mat));
    }
    inline friend Matrix operator*(Matrix a, Matrix b) {//矩阵乘法 
        Matrix c(a.size);
        for (int i = 1; i <= c.size; ++i)
            for (int k = 1; k <= c.size; ++k)
                for (int j = 1; j <= c.size; ++j)
                    c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % PHI;
                    //这里对 φ(p) 取模 
        return c;
    }
} baseA(3), x(3), y(3), z(3), baseB(5), w(5);

inline LL quickPow(LL x, LL p) {//快速幂 
    LL res = 1;
    for (; p; p >>= 1, x = x * x % MOD)
        if (p & 1) res = res * x % MOD;
    return res;
}

inline Matrix quickPow(Matrix x, LL p) {//矩阵快速幂 
    Matrix res(x.size);
    for (int i = 1; i <= res.size; ++i) res.mat[i][i] = 1;//单位矩阵 
    for (; p; p >>= 1, x = x * x)
        if (p & 1) res = res * x;
    return res;
}

inline void build() {//构造初始矩阵和转移矩阵 
    x.mat[3][1] = y.mat[2][1] = z.mat[1][1] = 1;
    w.mat[5][1] = 2;
    baseA.mat[1][1] = baseA.mat[1][2] = baseA.mat[1][3] = 
    baseA.mat[2][1] = baseA.mat[3][2] = 1;//baseA 是 x,y,z 的转移矩阵 
    for (int i = 1; i <= 5; ++i) baseB.mat[1][i] = 1;
    baseB.mat[2][1] = baseB.mat[3][2] = baseB.mat[4][4] = 
    baseB.mat[4][5] = baseB.mat[5][5] = 1;//baseB 是 w 的转移矩阵 
}

int main() {
    read(n), read(f1), read(f2), read(f3), read(c);
    build();
    baseA = quickPow(baseA, n - 3), baseB = quickPow(baseB, n - 3);
    w = baseB * w, x = baseA * x, y = baseA * y, z = baseA * z;
    //求出四个答案矩阵后得到 w[n],x[n],y[n],z[n]
    ans = quickPow(c, w.mat[1][1]) * quickPow(f1, x.mat[1][1]) % MOD * 
    quickPow(f2, y.mat[1][1]) % MOD * quickPow(f3, z.mat[1][1]) % MOD;
    //快速幂合并答案 
    write(ans);
    putchar('\n');
    return 0;
}
```

---

## 作者：Juanzhang (赞：10)

看到递推式很容易联想到矩阵加速，但是矩阵无法便捷地处理这种递推式。由于该递推式是一些数的乘积的形式，因此可以考虑求出每一项的指数

令 $a_{i,\ 1/2/3}$ 表示 $f_i$ 由多少个 $f_{1/2/3}$ 的乘积组成，可以发现 $a_{i,\ j}=a_{i-1,\ j}+a_{i-2,\ j}+a_{i-3,\ j}$ ，初值为 $a_{1,\ 1}=a_{2,\ 2}=a_{3,\ 3}=1$ ，可以使用矩阵加速

令 $g_i$ 为 $f_i$ 由多少个 $c$ 的乘积组成，递推式即为 $g_i=g_{i-1}+g_{i-2}+g_{i-3}+2i-6$ ，初值 $g_i=0$ ，可以使用矩阵加速，求出的矩阵即为 $\begin{bmatrix}0&0&0&8&1\end{bmatrix}\times\begin{bmatrix}1&1&0&0&0\\1&0&1&0&0\\1&0&0&0&0\\1&0&0&1&0\\-6&0&0&2&1\end{bmatrix}^{n-3}$

接下来就可以用快速幂还原答案，但是由于指数可能过大，因此得将指数 $\operatorname{mod} \varphi(10^9+7)=10^9+6$

时间复杂度 $O(\log n)$

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int P = 1e9 + 7, mod = 1e9 + 6;
ll n;

#define rep(i) for (int i = 0; i < 5; i++)

struct matrix {
  int array[5][5];

  inline void clr() {
    memset(array, 0, sizeof array);
  }

  inline int* operator [] (int pos) {
    return array[pos];
  }
} E, A, M;

inline matrix operator * (matrix a, matrix b) {
  static matrix s;
  s.clr();
  rep(i) rep(j) rep(k) s[i][j] = (s[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
  return s;
}

inline qp(int a, int k) {
  int res = 1;
  for (; k; k >>= 1, a = 1ll * a * a % P) {
    if (k & 1) res = 1ll * res * a % P;
  }
  return res;
}

inline matrix qp(matrix a, ll k) {
  matrix res = E;
  for (; k; k >>= 1, a = a * a) {
    if (k & 1) res = res * a;
  }
  return res;
}

inline int calc(int x) {
  A.clr(), A[0][x] = 1;
  return (A * qp(M, n - 3))[0][0];
}

int main() {
  int c, f1, f2, f3;
  scanf("%I64d %d %d %d %d", &n, &f1, &f2, &f3, &c);
  rep(i) E[i][i] = 1;
  M[0][0] = M[0][1] = M[1][0] = M[2][0] = M[1][2] = 1;
  int c1 = calc(2);
  int c2 = calc(1);
  int c3 = calc(0);
  A.clr(), A[0][3] = 8, A[0][4] = 1;
  M[4][3] = 2, M[4][0] = -6, M[3][0] = M[3][3] = M[4][4] = 1;
  int cnt = (A * qp(M, n - 3))[0][0];
  int ans = 1ll * qp(f1, c1) * qp(f2, c2) % P * qp(f3, c3) % P * qp(c, cnt) % P;
  printf("%d", ans);
  return 0;
}
```

---

## 作者：jjsnam (赞：5)

# 写在前面

一只蒟蒻正在做学校作业。在被极其需要思维的[紫题](https://www.luogu.com.cn/problem/P3263)虐哭之后，他几乎崩溃。不过他发誓，从那题之后再也不看题解了，于是做了这道题。不过真的是幸运，他真的做出来了！

上次独自一人做出紫题还是在上次。其实这道题的题解已经很多了，不过我还是想写，因为我太兴奋了。同时锻炼一下我的 LaTeX 能力。

## 前置知识

- 矩阵
- 费马小定理
- 快速幂

## 题目描述（戳这里[查看原题](https://www.luogu.com.cn/problem/CF1182E)）

给定 $n$、$f_1$、$f_2$、$f_3$、$c$，满足通项 $f_x = c^{2x - 6}f_{x-1}f_{x-2}f_{x-3}$ （$n ≥ 4$），求 $f_n$ 的值。结果对 $10^9+7$ 取模。

**注意 $n$ 可能很大**。

# 正文

## 确定方向

首先一点，$n$ 这么大，根据经验复杂度里还一定有 $n$，则一定是 $\log n$ 或 $\sqrt n$ 之类的。又有递推式，很容易联想到矩阵加速递推。

## 分析

考虑矩阵做法。首先直接试试建立递推式，容易发现原式中都是乘积。然而，矩阵满足的递推是基于加法的。可能有同学会考虑把矩阵变形，让其满足可乘性。不过仔细想想正确性不好证明，而且这种转化方法长这么大就没听说过。因此**硬搬矩阵优化的思路失败了**。

瞪眼法出不来，我们尝试把前几项写出来，看看有什么特点。则有：

$f_4 = c^2\times f_3 \times f_2 \times f_1$；     
$f_5 = c^4\times f_4 \times f_3 \times f_2$；     
$f_6 = c^6\times f_5 \times f_4 \times f_3$；     
$f_7 = c^8\times f_6 \times f_5 \times f_4$；    
$\ \ \cdots$

又因为直接递推或者找通项不行，我们尝试把式子都代换成我们的已知量，则有：

$f_4 = c^2\times f_3 \times f_2 \times f_1$；     
$f_5 = c^6\times f_3^2 \times f_2^2 \times f_1$；     
$f_6 = c^{14}\times f_3^4 \times f_2^3 \times f_1^2$；     
$f_7 = c^{30}\times f_3^7 \times f_2^6 \times f_1^4$；    
$\ \ \cdots$

诶？似乎指数乘积有以下性质：$x^a\times x^b = x^{a+b}$，那么如果我们只考虑每个数的次数，而每个数的底数都已知，最后可以快速幂，好像就符合了加法递推，能够应用矩阵加速了！

以 $f1$ 为例。由 $f_x = c^{2x - 6}f_{x-1}f_{x-2}f_{x-3}$ 可知组成 $x$ 的 $f1$ 的次数由 $x-1$、$x-2$、$x-3$ 三个状态的总和得出，因此我们可以构造向量 $F_{1_i} = [g_i,\ \ g_{i-1},\ \ g_{i-2}]$，$g_i$ 表示 $i$ 状态下 $f_1$ 的指数。现在思考，如何推出 $F_{1_{i+1}}$？则有：

$\begin{bmatrix}
g_i,\ \  g_{i-1},\ \  g_{i-2}
\end{bmatrix} \times
\begin{bmatrix}
1,\ \ 1, \ \ 0 \\
1,\ \  0, \ \ 1 \\
1, \ \ 0,\  \ 0
\end{bmatrix} = 
\begin{bmatrix}
g_{i+1},\ \  g_{i},\ \  g_{i-1}
\end{bmatrix}
$

同理可得出 $f_2$、$f_3$ 的转移方法，**转移矩阵相同**。

$c$ 的转移略显复杂。首先，如果不换元，每次 $c$ 的指数应该构成一个等差数列。其次，换元后每次指数还要累加前面的指数和。因此我们构造的向量要包含前 3 个状态并能转移等差数列。观察可知等差数列公差 $d = 2$，则有向量 $C = [h_i,\ \ h_{i-1},\ \ h_{i-2},\ \ a_i,\ \ d]$，其中 $h_i$ 表示 $i$ 时 $c$ 的指数，$a_i$ 是等差数列此时的值。因此，我们有如下转移：（注意 $d$ 是常数）。

$\begin{bmatrix}
h_i,\ \ h_{i-1},\ \ h_{i-2},\ \ a_i,\ \ d
\end{bmatrix} \times
\begin{bmatrix}
1,\ \ 1, \ \ 0, \ \ 0, \ \ 0 \\
1,\ \  0, \ \ 1, \ \ 0, \ \ 0 \\
1, \ \ 0,\  \ 0, \ \ 0,\  \ 0 \\
1, \ \ 0,\ \ 0,\ \ 1,\ \ 0 \\
1, \ \ 0,\ \ 0,\ \ 1,\ \ 1 
\end{bmatrix} = 
\begin{bmatrix}
h_{i+1},\ \ h_{i},\ \ h_{i-1},\ \ a_{i+1},\ \ d
\end{bmatrix}
$

因此只要**求出 $n$ 时的各向量**然后**快速幂算答案**即可。

## 细节

1. 观察刚才的两个转移矩阵。可以发现左上角 $3 \times 3$ 的部分是完全一样的，因此可以将 3 个 $F$ 向量扩充至 $1\times 5$，这样就可以通用一个转移矩阵了。
2. 现在来考虑几个向量的初始值。考虑到我们的定义，初始时包括前三个状态是最好且简单的。因此有：（直接根据定义填入就行）

	$F_{1} = [0, \ \ 0, \ \ 1]$，$F_{2} = [0, \ \ 1, \ \ 0]$，$F_{3} = [1, \ \ 0, \ \ 0]$。（省略了扩充部分）
    
    此外，根据对 $C$ 的定义，前三个状态都是非法的。所以都应该是 0。而等差数列的首项 $a_1 = 2$，因此我们可以构造一个虚拟首项 $a_0 = a_1 - d = 0$（只转移一次就合法，逆推得出），故推出初始向量：
    
    $C = [0,\ \ 0,\ \ 0,\ \ 0,\ \ 2]$。

3. 观察数据范围。我们发现我们转移的指数不仅增长迅速，而且增长基数大。很有可能 ```unsigned long long``` 也无法保存正确的指数。考虑一下是否可以取模。

	因为模数（$10^9+7$）是一个质数，固由费马小定理
    
    $a^{p-1} \equiv 1 \pmod p$
    
    我们知道在模 $p$ 意义下 $c^{p-1} = c^{0}$，所以其指数的模域是 $[0, p-2]$。固转移时需与 $10^9+6$ 取模。
    
### 时间复杂度

真的只是一个矩阵加速，还有矩阵运算的常数 $q$，固大约 $O(q^3\log n)$。（$q = 5$）
    
# 代码

没什么好说的，代码很简单。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
const int maxM = 5;
const int mod = 1e9 + 7; //答案的模数
const int P = mod - 1; //矩阵优化转移的模数

ll n;
int f1, f2, f3, c;
struct Matrix{
    int v[maxM][maxM];
    int L, C;

    Matrix(int l, int c, bool st = false){
        L = l, C = c;
        memset(v, 0, sizeof v);
        if (st){
            for (int i = 0; i < max(l, c); i ++){
                v[i][i] = 1;
            }
        }
    }

    Matrix operator * (const Matrix &b) const{
        Matrix res(L, b.C);
        for (int i = 0; i < res.L; i ++){
            for (int j = 0; j < res.C; j ++){
                for (int k = 0; k < C; k ++){
                    (res.v[i][j] += (ll)v[i][k] * b.v[k][j] % P) %= P;
                }
            }
        }
        return res;
    }
};

Matrix qmi(Matrix A, ll b){
    Matrix res(A.L, A.C, true);
    while (b){
        if (b & 1) res = res * A;
        A = A * A;
        b >>= 1;
    }
    return res;
}

int qmi(int a, int b){
    int res = 1;
    while (b){
        if (b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> f1 >> f2 >> f3 >> c;

    /* building matrix */
    Matrix A(5, 5);
    Matrix C(1, 5),F1(1, 5), F2(1, 5), F3(1, 5);
    const int Exmp[5][5] = {
        {1, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1}
    }; 
    memcpy(A.v, Exmp, sizeof Exmp);
    C.v[0][4] = 2; //[0,0,0,0,2]
    F1.v[0][2] = 1, F2.v[0][1] = 1, F3.v[0][0] = 1;

    /* process */
    A = qmi(A, n-3);
    C = C * A,F1 =F1 * A, F2 = F2 * A, F3 = F3 * A;

    /* get answer */
    int temp_c = qmi(c, C.v[0][0]);
    int temp_f1 = qmi(f1,F1.v[0][0]);
    int temp_f2 = qmi(f2, F2.v[0][0]);
    int temp_f3 = qmi(f3, F3.v[0][0]);

    int ans = (ll)temp_c * temp_f1 % mod * temp_f2 % mod * temp_f3 % mod;
    cout << ans << endl;

    return 0;
}
```

# 总结

u1s1，感觉把自己想法写出来经常会表达不清。而且我总是希望能用最少的话表达最清楚的意思，但每回都会很啰嗦，已经斟酌修改很多了，还望见谅，如有问题欢迎指出！

谢谢观看！


---

## 作者：Sol1 (赞：5)

第一眼：~~很明显地递推啊~~

第二眼：$n \leq 10^{18}$？

第三眼：~~很明显的矩阵加速啊~~

然后考场上成功地没写出来。

首先，我们在想到矩阵加速之后就可以发现，$f$和$c$一定是要分开处理的。

然后，我们发现$f$用乘积递推貌似不好用矩阵加速，所以我们考虑以将所有$f_i$表示为$f_1^p·f_2^q·f_3^r$的形式（注意这里已经去掉了$c$，最后再乘上就可以了）。

于是我开始计算和化简：

$f_4=f_1^1·f_2^1·f_3^1$

$f_5=f_1^1·f_2^2·f_3^2$

$f_6=f_1^2·f_2^3·f_3^4$

$f_7=f_1^4·f_2^6·f_3^7$

显然，当我们要从$(p,q,r)$推导到$(p_1,q_1,r_1)(f_i=f_1^p·f_2^q·f_3^r,f_{i+1}=f_1^{p_1}·f_2^{q_1}·f_3^{r_1})$时，可以找到规律：$p_1=r,q_1=p+r,r_1=q+r$。

易得转移矩阵1为$\begin{bmatrix}0&1&0\\0&0&1\\1&1&1\end{bmatrix}$，计算$\begin{bmatrix}1&1&1\end{bmatrix} \times \begin{bmatrix}0&1&0\\0&0&1\\1&1&1\end{bmatrix}^{n-3}$的位于$(1,1)$的元素就是$p$，位于$(1,2)$的元素就是$q$，位于$(1,3)$的元素就是$r$。

问题在于怎么处理$c$。

还是可以写出$c$的转移方程：

$c_i=c_{i-1}+c_{i-2}+c_{i-3}+2i-6$

所以我们可以开一个$5 \times 5$的转移矩阵和$1 \times 5$的答案矩阵，设其为$\begin{bmatrix}k_1&k_2&k_3&k_4&k_5\end{bmatrix}$。

所以我们可以让$k_1$维护$c_{i-1}$，$k_2$维护$c_{i-2}$，$k_3$维护$c_{i-3}$，$k_4$维护$2i$，$k_5$维护$-6$。

然后我们开始填这个矩阵：初始为$\begin{bmatrix}0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\end{bmatrix}$

那么因为转移的时候，我们只需要让$k_1$得到这个$-6$就可以了，所以我们可以保持$k_5=1$，并让$k_1$乘上一个$-6$，于是填出2项：$\begin{bmatrix}0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\\-6&0&0&0&1\end{bmatrix}$

然后，每转移一次需要让$k_4\ +2$，同时因为$k_5$一直为$1$，所以我们可以直接让$k_5\times 2$，然后保持$k_4$不变就可以了。

$\begin{bmatrix}0&0&0&0&0\\0&0&0&0&0\\0&0&0&0&0\\0&0&0&1&0\\-6&0&0&2&1\end{bmatrix}$

$k_2$和$k_3$非常好整：我们直接把$k_1$转移到$k_2$，把$k_2$转移到$k_3$就可以了。

$\begin{bmatrix}0&1&0&0&0\\0&0&1&0&0\\0&0&0&0&0\\0&0&0&1&0\\-6&0&0&2&1\end{bmatrix}$

完成了这些，会发现$k_1$更加好整：直接按照转移方程，把所有除$-6$（这项已经完成转移）的项转移到$k_1$即可。

$\begin{bmatrix}1&1&0&0&0\\1&0&1&0&0\\1&0&0&0&0\\1&0&0&1&0\\-6&0&0&2&1\end{bmatrix}$

下面我们要做的就是完成初始矩阵了。

显然，我们应该从$i=4$开始，所以我们设计的实际上是$i=4$时的状态。直接代入就可以了：$[0,0,0,8,1]$。

然后，计算答案矩阵为$[0,0,0,8,1]\times\begin{bmatrix}1&1&0&0&0\\1&0&1&0&0\\1&0&0&0&0\\1&0&0&1&0\\-6&0&0&2&1\end{bmatrix}^{n-3}$

最后，我们发现答案就是答案矩阵的$(1,1)$，设其为$s$。

假设我们已经获得了$p,q,r,s$，那么显然，答案就是$f_1^p·f_2^q·f_3^r·c^s \bmod 10^9+7$。

注意：我们对指数取模的时候，要模$phi(10^9+7)=10^9+6$。

总时间复杂度$\Theta(\log N)$。

附上代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

const long long mod1 = 1e9 + 7ll, mod2 = 1e9 + 6ll;
struct Matrix {
    long long a[10][10];
    int n, m;
    Matrix() {
        n = m = 0;
        memset(a, 0, sizeof(a));
    }
    //矩阵乘法
    Matrix operator * (const Matrix& b) const {
        Matrix c;
        c.n = n;
        c.m = b.m;
        for (int i = 1;i <= c.n;i++) {
            for (int j = 1;j <= c.m;j++) {
                for (int k = 1;k <= m;k++) {
                    c.a[i][j] = (c.a[i][j] + (a[i][k] * b.a[k][j]) % mod2) % mod2;
                }
            }
        }
        return c;
    }
};
long long n, f1, f2, f3, c;
//生成单位矩阵
Matrix Unit(int n) {
    Matrix mtx;
    mtx.n = n;
    mtx.m = n;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            mtx.a[i][j] = (i == j);
        }
    }
    return mtx;
}
//矩阵快速幂
Matrix Power(Matrix x, long long y) {
    Matrix ans = Unit(x.n);
    while (y) {
        if (y & 1) {
            ans = ans * x;
        }
        y >>= 1;
        x = x * x;
    }
    return ans;
}
//整数快速幂
long long Power_(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) {
            ans = (ans * x) % mod1;
        }
        y >>= 1;
        x = (x * x) % mod1;
    }
    return ans;
}

void Solve() {
//完成2个初始矩阵和2个转移矩阵
    Matrix mtx1, mtx2, mtx3, mtx4;
    mtx1.n = 1; mtx1.m = 3; mtx1.a[1][1] = mtx1.a[1][2] = mtx1.a[1][3] = 1;
    mtx2.n = 3; mtx2.m = 3; mtx2.a[1][2] = mtx2.a[2][3] = mtx2.a[3][1] = mtx2.a[3][2] = mtx2.a[3][3] = 1;
    mtx3.n = 1; mtx3.m = 5; mtx3.a[1][4] = 8; mtx3.a[1][5] = 1;
    mtx4.n = 5; mtx4.m = 5; mtx4.a[1][1] = mtx4.a[1][2] = mtx4.a[2][1] = mtx4.a[2][3] = mtx4.a[3][1] = mtx4.a[4][1] = mtx4.a[4][4] = mtx4.a[5][5] = 1;
    mtx4.a[5][1] = -6; mtx4.a[5][4] = 2;
    //利用矩阵快速幂计算p,q,r,s
    mtx1 = mtx1 * Power(mtx2, n - 4);
    mtx3 = mtx3 * Power(mtx4, n - 3);
    long long ans1 = mtx1.a[1][1], ans2 = mtx1.a[1][2], ans3 = mtx1.a[1][3], ans4 = mtx3.a[1][1];
    long long ans = 1;
    //求得最终答案
    ans = (ans * Power_(f1, ans1)) % mod1;
    ans = (ans * Power_(f2, ans2)) % mod1;
    ans = (ans * Power_(f3, ans3)) % mod1;
    ans = (ans * Power_(c, ans4)) % mod1;
    printf("%I64d", ans);
}

int main() {
    scanf("%I64d%I64d%I64d%I64d%I64d", &n, &f1, &f2, &f3, &c);
    Solve();
    return 0;
}
```

---

## 作者：little_sun (赞：4)

### 题目大意

给你$n,f_1,f_2,f_3,c$,让你求$f_n=c^{2n-6} \times f_{n-1} \times f_{n-2} \times f_{n-3}$

### 解析

首先我们可以发现:

$f_n \times c^n$
$ = c^{3n-6} \times f_{n-1} \times f_{n-2} \times f_{n-3}$
$ = c^{n-1} \times f_{n-1} \times c^{n-2} \times f_{n-2} \times c^{n-3} \times f_{n-3}$

设$g_n=f_n*c_n$，则有$g_n=g_{n-1} \times g_{n-2} \times g_{n-3}$

把它展开，发现

$$g_n=g_{n-1} \times g_{n-2} \times g_{n-3}=g_{n-2}^2 \times g_{n-3}^2 \times g_{n-4} = g_{n-3}^4 \times g_{n-4}^3 \times g_{n-5}^2 = \cdots = g_3^{h_{2n-5}} \times g_2^{h_{2n-6}} \times g_1^{h_{2n-7}}$$

于是我们的工作就变成了求$h_n$

观察~~oeis~~一下这个式子我们可以发现：

$$h_{2n}=h_{2n-1}+h_{2n-3},h_{2n+1}=h_{2n-1}+h_{2n-2},$$

我们设$a_n=h_{2n+1},b_n=h_{2n}$，则可以得出如下矩阵

![TZXNM`YV~1Q1W3MI626M44P.png](https://i.loli.net/2019/10/18/34HNXTQDpyAFO8G.png)

我们又注意到$mod=10^9+7$,于是我们可以把次数模上$\phi(mod)=10^9+6$(欧拉定理)

于是我们就可以快乐的用矩快计算次数啦

注意最后的$f_n=\frac{g_n}{c^n}$哦

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll unsigned long long
#define sum(a, b, mod) ((a + b) % mod)

const ll mod = 1e9 + 7, mode = 1e9 + 6;

ll fast_mul(ll a, ll b, ll mod)
{
    ll ans = 0;
    while (b)
    {
        if (b & 1)
            ans = (ans + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

ll fast_pow(ll a, ll b)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1)
            ret = fast_mul(ret, a, mod) % mod;
        a = fast_mul(a, a, mod) % mod;
        b >>= 1;
    }
    return ret;
}

struct matrix
{
    ll n, m, a[10][10];
    matrix(ll x, ll y)
    {
        n = x, m = y;
        memset(a, 0, sizeof(a));
    }
};

matrix mul(matrix a, matrix b)
{
    ll n = a.n, m = a.m, k = b.m;
    matrix c(n, k);
    for (ll i = 1; i <= n; i++)
        for (ll l = 1; l <= k; l++)
            for (ll j = 1; j <= m; j++)
                c.a[i][j] = (c.a[i][j] + fast_mul(a.a[i][l], b.a[l][j], mode)) % mode;
    return c;
}
matrix pow_(matrix a, ll b)
{
    matrix ret = a;
    while (b)
    {
        if (b & 1ll)
            ret = mul(ret, a);
        a = mul(a, a);
        b >>= 1ll;
    }
    return ret;
}

inline matrix init()
{
    matrix a(3, 3);
    a.a[1][1] = a.a[1][3] = a.a[2][1] = a.a[3][1] = a.a[3][2] = 1;
    return a;
}

inline matrix init_()
{
    matrix a(3, 1);
    a.a[1][1] = a.a[2][1] = a.a[3][1] = 1;
    return a;
}

int main()
{
    ll f[4], n, c;
    std::cin >> n >> f[1] >> f[2] >> f[3] >> c;
    matrix a = init(), b = init_(), x = pow_(a, n - 4), y = pow_(a, n - 4), z = pow_(a, n - 5);
    x = mul(x, b), y = mul(y, b), z = mul(z, b);
    ll A = x.a[1][1], B = y.a[3][1], C = z.a[1][1], X = fast_mul(f[3], fast_pow(c, 3), mod), Y = fast_mul(f[2], fast_pow(c, 2), mod), Z = fast_mul(f[1], c, mod);
    ll ans = fast_mul(fast_mul(fast_mul(fast_pow(X, A), fast_pow(Y, B), mod), fast_pow(Z, C), mod), fast_pow(fast_pow(c, n), mod - 2llu), mod);
    std::cout << ans;
    return 0;
}

```



---

## 作者：cccgift (赞：4)

## 看到其它题解的矩阵较为麻烦，这里给出一种简单一点的办法。

乍一眼看到这道题没有任何思路，对于这种题目，我们得用到一种最原始的办法：**找规律！**

列出了前几项$f_{x}$，列出每一项的系数，突然发现这个系数是可以直接递推的！

假设$f_{x}=c^{a_{x}}f^{b_{x}}_{1}f^{d_{x}}_{2}f^{e_{x}}_{3}$。

我们可以发现，$a_{x}=a_{x-1}+a_{x-2}+a_{x-3}+2x-6$，但是这个后面有一个$2x-6$很不好处理，然后我发现，$(x-1)+(x-2)+(x-3)=3x-6$，那么，令$g_{x}=a_{x}+x$，原式居然变成了$g_{x}=g_{x-1}+g_{x-2}+g_{x-3}$！这不就是斐波那契数列吗？

再考虑后面三个数组$b$，$d$，$e$，用数学归纳法~~或找规律~~得到它们的递推式和上面的$g$相同,只是刚开始几项不同而已！

于是，我们就可以使用矩阵快速幂轻松求出这些系数了，根据这些系数即可得到$f_{x}$。

但是，还有一个问题：这些系数都很大。注意到模数为$1e9+7$，是个质数，根据欧拉定理，即可把系数模$1e9+6$，就可以计算了。

### 代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
#define res register int
#define ll long long
const ll mod=1e9+7;
struct node{
	int a[3][3];
	node operator *(const node &b)const { //矩阵乘法，注意模数！
		node tot;memset(tot.a,0,sizeof(tot.a));
		for(res i=0;i<3;++i)
		  for(res k=0;k<3;++k)
		    for(res j=0;j<3;++j) tot.a[i][j]=(tot.a[i][j]+(ll)a[i][k]*b.a[k][j])%(mod-1);
		return tot;
	}
} f,a;
ll n,tot,nn,now;
int f1,f2,f3,c;
inline ll kuai(ll p,ll q) {ll tot=1;for(;q;p=p*p%mod,q>>=1) if(q&1) tot=tot*p%mod;return tot;}
int main()
{
	for(res i=0;i<3;++i) f.a[0][i]=i;
    a.a[0][2]=a.a[1][0]=a.a[1][2]=a.a[2][1]=a.a[2][2]=1,scanf("%lld%d%d%d%d",&n,&f1,&f2,&f3,&c),nn=n;
    for(;nn;a=a*a,nn>>=1) if(nn&1) f=f*a;
    tot=kuai(c,((f.a[0][0]-n)%(mod-1)+mod-1)%(mod-1)); //这里要注意！别忘了求出的是g，而系数是a，答案需要减n，但又得防止负数。
    nn=n-1,memset(a.a,0,sizeof(a.a)),a.a[0][2]=a.a[1][0]=a.a[1][2]=a.a[2][1]=a.a[2][2]=1,f.a[0][0]=1,f.a[0][1]=0,f.a[0][2]=0; //由于递推式相同，接下来直接Ctrl+CV即可。
    for(;nn;a=a*a,nn>>=1) if(nn&1) f=f*a;
    tot=tot*kuai(f1,f.a[0][0])%mod;
    nn=n-1,memset(a.a,0,sizeof(a.a)),a.a[0][2]=a.a[1][0]=a.a[1][2]=a.a[2][1]=a.a[2][2]=1,f.a[0][0]=0,f.a[0][1]=1,f.a[0][2]=0;
    for(;nn;a=a*a,nn>>=1) if(nn&1) f=f*a;
    tot=tot*kuai(f2,f.a[0][0])%mod;
    nn=n-1,memset(a.a,0,sizeof(a.a)),a.a[0][2]=a.a[1][0]=a.a[1][2]=a.a[2][1]=a.a[2][2]=1,f.a[0][0]=0,f.a[0][1]=0,f.a[0][2]=1;
    for(;nn;a=a*a,nn>>=1) if(nn&1) f=f*a;
    tot=tot*kuai(f3,f.a[0][0])%mod;printf("%lld\n",tot);
    return 0;
}
```

---

## 作者：Grisses (赞：2)

已知 $f_1,f_2,f_3$ 和 $c$，$f_i=c^{2i-6}f_{i-1}f_{i-2}f_{i-3}(i>3)$，求 $f_n$。

我们可以发现这里不再是加，所以不能直接矩阵快速幂。但是，我们都知道对于一个大于 1 的数 $a$ 有 $\log_ax\cdot y=\log_ax+\log_ay$，但是，如果用 $\log$ 的话，你的精度爆上个十几遍是不成问题的。所以我们需要在推一推。
$$f_1=c^0f_3^0f_2^0f_1$$
$$f_2=c^0f_3^0f_2f_1^0$$
$$f_3=c^0f_3f_2^0f_1^0$$
$$f_4=c^2f_3f_2f_1$$
$$f_5=c^6f_3^2f_2^2f_1$$
$$f_6=c^{14}f_3^4f_2^3f_1^2$$
$$f_7=c^{30}f_3^7f_2^6f_1^4$$
$$f_8=c^{60}f_3^{13}f_2^{11}f_1^7$$

我们设 $t_{i,j},(i>3,j=\overline{1,2,3})$ 表示 $f_i$ 分解过后 $f_j$ 的系数，$g_i$ 表示 $f_i$ 中 $c$ 的系数。我们发现：
$$t_{i,j}=t_{i-1,j}+t_{i-2,j}+t_{i-3,j}$$
$$g_i=2i-6+g_{i-1}+g_{i-2}+g_{i-3}$$

然后就可以用矩阵快速幂推过去了，但是，如果不取模的话，会炸掉，所以我们需要欧拉降幂：
$$a^b\equiv a^{b\bmod\varphi(p)}\pmod{p}$$

因为本题的模数是给质数，所以对指数的模数为其减一。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7,Mod=mod-1;
  int n,c,x,y,z,res=1;
  struct M{
      int a[5][5];
      M operator*(M t){
          M res;
          for(int i=0;i<5;i++)for(int j=0;j<5;j++)res.a[i][j]=0;
          for(int i=0;i<5;i++){
              for(int j=0;j<5;j++){
                  for(int k=0;k<5;k++){
                      res.a[i][j]=((res.a[i][j]+a[i][k]*t.a[k][j]%Mod+Mod)%Mod+Mod)%Mod;
                  }
              }
          }
          return res;
      }
      M operator^(int x){
          M res,_=*this;
          for(int i=0;i<5;i++)for(int j=0;j<5;j++)res.a[i][j]=(i==j);
          while(x){
              if(x&1)res=res*_;
              _=_*_;
              x>>=1; 
          }
          return res;
      }
  }ans,base;
  int fpow(int a,int b){
      int res=1;
      while(b){
          if(b&1)res=res*a%mod;
          a=a*a%mod;
          b>>=1;
      }
      return res;
  }
  signed main()
  {
      scanf("%lld%lld%lld%lld%lld",&n,&x,&y,&z,&c);
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)ans.a[i][j]=0;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)base.a[i][j]=0;
      ans.a[2][0]=1;
      base.a[0][0]=base.a[0][1]=base.a[0][2]=base.a[1][0]=base.a[2][1]=1;
      ans=(base^(n-3))*ans;
      res=res*fpow(x,ans.a[0][0])%mod;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)ans.a[i][j]=0;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)base.a[i][j]=0;
      ans.a[1][0]=1;
      base.a[0][0]=base.a[0][1]=base.a[0][2]=base.a[1][0]=base.a[2][1]=1;
      ans=(base^(n-3))*ans;
      res=res*fpow(y,ans.a[0][0])%mod;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)ans.a[i][j]=0;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)base.a[i][j]=0;
      ans.a[0][0]=1;
      base.a[0][0]=base.a[0][1]=base.a[0][2]=base.a[1][0]=base.a[2][1]=1;
      ans=(base^(n-3))*ans;
      res=res*fpow(z,ans.a[0][0])%mod;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)ans.a[i][j]=0;
      for(int i=0;i<5;i++)for(int j=0;j<5;j++)base.a[i][j]=0;
      ans.a[3][0]=3;ans.a[4][0]=1;
      base.a[0][0]=1;base.a[0][1]=1;base.a[0][2]=1;base.a[0][3]=2;base.a[0][4]=-4;
      base.a[1][0]=1;
      base.a[2][1]=1;
      base.a[3][3]=1;base.a[3][4]=1;
      base.a[4][4]=1;
      ans=(base^(n-3))*ans;
      res=res*fpow(c,ans.a[0][0])%mod;
      printf("%lld",res);
      return 0;
  }
```

---

## 作者：Essinsop (赞：1)

题意：

给定 $n, f_1, f_2, f_3, c$, 有数列 $f$ 满足 $f_x = f_{x-1}f_{x-2}f_{x-3}c^{2x-6}(4 \le x)$

告诉你正整数 $n\ (4 \le n \le 10^{18})$ , 试求 $f_n$。

~~从数据范围可以看出~~, 这道题是一道矩阵快速幂的题目

比较常见的矩阵快速幂一般形如 $f_x = \sum_{i=1}^{a}b_if_{x-i} + k$

但我们发现这道题有多个 $f_i$ 进行相乘, 因此换一个思路, 我们考虑 $f_x$ 中 $f_1, f_2, f_3$ 的指数

具体地, 我们有如下发现：

$f_1 = f_1^1f_2^0f_3^0$

$f_2 = f_1^0f_2^1f_3^0$

$f_3 = f_1^0f_2^0f_3^1$

$f_4 = f_1^1f_2^1f_3^1c^2$

$f_5 = f_1^1f_2^2f_3^2c^6$

$f_6=f_c^2f_2^3f_3^4c^{14}$

等等。

由于 $f_x=f_{x-1}f_{x-2}f_{x-3}c^{2x-6}$

我们能得到 $f_x$ 中 $f_1,f_2,f_3$ 的指数均为 $f_{x-1},f_{x-2},f_{x-3}$ 中他们各自的指数和。

又有 $2x-6-(2(x-1)-6) = 2$, 得到 $f_x$ 中 $c$ 的指数为 $f_{x-1}, f_{x-2}, f_{x-3}$ 中各自的指数和加上 $2$

这时我们发现, 我们算指数的步骤, 已经是我们熟知的矩阵快速幂了

因此, 对于 $f_x$ 中 $f_1, f_2, f_3, c$ 的指数我们均可以用矩阵快速幂求出来

接下来我们来设计矩阵:

我们用 $C_i$ 来表示 $f_i$ 中 $c$ 的指数, 由上有 $C_i = C_{i-1} + C_{i-2} + C_{i-3} + 2i-6$

则 $[C_{i-1}, C_{i-2}, C_{i-3}, 2i-6] \times base = [C_i, C_{i-1}, C_{i-2}, C_{i-3}, 2i-4]$ 

值得注意的是, 我们要使 $2i-6$ 变为 $2i-4$, 我们要新添加一个 $2$ 让原本的 $2i-6$ 加上去

因此$[C_{i-1}, C_{i-2}, C_{i-3}, 2i-6, 2] \times base = [C_i, C_{i-1}, C_{i-2}, C_{i-3}, 2i-4, 2]$ 

因此有 $base = \begin{bmatrix}1&1&0&0&0\\1&0&1&0&0&\\1&0&0&0&0&\\1&0&0&2&0\\0&0&0&0&1\end{bmatrix}$

对于 $f_1, f_2, f_3$ 的情况, 我们能推出:

$base2 = \begin{bmatrix}1&1&0\\1&0&1\\1&0&0\end{bmatrix}$

这时, 我们已经求出了 $f_x$ 中 $f_1, f_2, f_3, c$ 的指数, 但我们发现, 他们可能会爆掉 $long\ long$

这时我们要用掉欧拉定理: $a^b \equiv a^{b \%\varphi(p)} (mod\ p)$

由于此题的模数式一个质数, 不难得出 $\varphi(p) = p - 1$, 直接对其进行取模即可

代码如下:

```
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
struct matrix {
	int s[6][6];
	matrix() {memset(s, 0, sizeof(s));};
	matrix operator * (const matrix &rhs) const {
		matrix res;
		for(int i = 1;i <= 5;i++) {
			for(int j = 1;j <= 5;j++) {
				for(int k = 1;k <= 5;k++) {
					res.s[i][j] += s[i][k] * rhs.s[k][j];
					res.s[i][j] %= (mod - 1);
				}
			}
		}
		return res;
	}
}base1, base2, w, x, y, z;
int n, f1, f2, f3, c;
void init() {
	base1.s[1][1] = base1.s[1][2] = base1.s[2][1] = base1.s[2][3] = base1.s[3][1] = base1.s[4][1] = 1;
	base1.s[4][4] = 1, base1.s[5][4] = 1, base1.s[5][5] = 1;
	base2.s[1][1] = base2.s[1][2] = base2.s[2][1] = base2.s[3][1] = base2.s[2][3] = 1;
	w.s[1][1] = 0, w.s[1][2] = 0, w.s[1][3] = 0, w.s[1][4] = 2, w.s[1][5] = 2;
	x.s[1][3] = 1;
	y.s[1][2] = 1;
	z.s[1][1] = 1;
}
void cksm(int q) {
	while(q) {
		if(q & 1) w = w * base1;
		base1 = base1 * base1;
		q >>= 1;
	}
}
void qksm(int q) {
	while(q) {
		if(q & 1) {
			
			x = x * base2;
			y = y * base2;
			z = z * base2;
		}
		base2 = base2 * base2;
		q >>= 1;
	}
}
int ksm(int p, int q) {
	int res = 1;
	while(q) {
		if(q & 1) {
			res *= p;
			res %= mod;
		}
		p *= p;
		p %= mod;
		q >>= 1;
	}
	return res;
}
signed main() {
	scanf("%lld%lld%lld%lld%lld", &n, &f1, &f2, &f3, &c);
	init();
	if(n == 1) cout << f1 << endl;
	else if(n == 2) cout << f2 << endl;
	else if(n == 3) cout << f3 << endl;
	else {
		cksm(n - 3);
		qksm(n - 3);
		int p1 = w.s[1][1], p2 = x.s[1][1], p3 = y.s[1][1], p4 = z.s[1][1];
		cout << (ksm(c, p1) % mod * ksm(f1, p2) % mod * ksm(f2, p3) % mod * ksm(f3, p4) % mod) % mod << endl;
	}
}
```


---

## 作者：QiFeng233 (赞：1)

# 思路分析

我们化乘为加

$f_i=c^{w_i}f_1^{x_i}f_2^{y_i}f_3^{z_i}$

$w_i=w_{i-1}+w_{i-2}+w_{i-3}+2i-6$

$x_i=x_{i-1}+x_{i-2}+x_{i-3}$

$y_i=y_{i-1}+y_{i-2}+y_{i-3}$

$z_i=z_{i-1}+z_{i-2}+z_{i-3}$

那么这就是矩阵快速幂裸题了。

根据扩展欧拉定理，矩阵快速幂的时候要对 $\phi(10^9+7)=10^9+6$ 取模。

另外这是我个人总结的一个规律，不保证正确性：递推式带了一个多项式时（$w_i=w_{i-1}+w_{i-2}+...+A(i)$），比如本题 $A(i)=2i-6$，多项式有几项，转移矩阵就要多几行和列。

实现细节可以看代码。

# 代码时间
```cpp
#include<cstdio>
#include<cstring>
#define int long long
namespace QiFeng233{
	const int PHI=1e9+6,MOD=1e9+7;
	struct matrix{
		int size,mat[6][6];
		matrix(int sz){
			size=sz;
			memset(mat,0,sizeof(mat));
		}
		friend matrix operator*(matrix a,matrix b){
			matrix c(a.size);
        	for(int i=1;i<=c.size;++i)
                for(int j=1;j<=c.size;++j)
            		for(int k=1;k<=c.size;++k)
                    	c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%PHI;
        	return c;
		}
	};
	int ksm(int a,int b){
		int res=1,tmp=a;
		while(b){
			if(b&1){
				res=res*tmp;
				res%=MOD;
			}
			tmp=tmp*tmp;
			tmp%=MOD;
			b>>=1;
		}
		return res;
	}
	matrix ksm(matrix a,int b){
		matrix res=matrix(a.size),tmp=a;
		for(int i=1;i<=a.size;++i)res.mat[i][i]=1; 
		while(b){
			if(b&1){
				res=res*tmp;
			}
			tmp=tmp*tmp;
			b>>=1;
		}
		return res;
	}
	int n,f1,f2,f3,c;
	matrix x(3),y(3),z(3),w(5),A(3),B(5);
	void solve(){
		scanf("%lld%lld%lld%lld%lld",&n,&f1,&f2,&f3,&c);
		x.mat[3][1]=y.mat[2][1]=z.mat[1][1]=1;
		w.mat[5][1]=2;
		A.mat[1][1]=A.mat[1][2]=A.mat[1][3]=A.mat[2][1]=A.mat[3][2]=1;
		B.mat[1][1]=B.mat[1][2]=B.mat[1][3]=B.mat[1][4]=B.mat[1][5]=B.mat[2][1]=B.mat[3][2]=B.mat[4][4]=B.mat[4][5]=B.mat[5][5]=1;
		A=ksm(A,n-3),B=ksm(B,n-3);
		x=A*x,y=A*y,z=A*z,w=B*w;
		int ans=ksm(c,w.mat[1][1])%MOD*ksm(f1,x.mat[1][1])%MOD*ksm(f2,y.mat[1][1])%MOD*ksm(f3,z.mat[1][1])%MOD;
		printf("%lld",ans%MOD);
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

---

## 作者：VinstaG173 (赞：1)

心路历程：

比赛时一看到递推题面，果断判断矩阵快速幂。

所以$Tribonacci$是老套路，那么$c$的次数怎么计算呢？

我推了前几项的次数，看看能否找到规律。

$0,0,0,2,6,14,30,60,...$

由于这个数列是前三项之和加一个数，很自然想到差分。

我的差分过程：

原数列：$0,0,0,2,6,14,30,60,...$

除以$2$后（由于每项都是偶数）：$0,0,0,1,3,7,15,30,...$

一阶差分：$0,0,1,2,4,8,15,...$

二阶差分：$0,1,1,2,4,7,...$

于是我们看到了著名的$Tribonacci$数列！

由$Tribonacci$数列的性质回推可以得出$c$次数的递推式：

$a_n=a_{n-5}-2a_{n-4}-2a_{n-2}+3a_{n-1}(n \ge 6,a_1=a_2=a_3=0,a_4=2,a_5=6)$，于是得出矩阵如下：

$$\begin{bmatrix}0&0&0&0&1\\1&0&0&0&-2\\0&1&0&0&0\\0&0&1&0&-2\\0&0&0&1&3\end{bmatrix}$$

矩阵

$$\begin{bmatrix}2&6&14&30&60\end{bmatrix}$$

与以上矩阵的$(n-4)$次方相乘后的矩阵第一行第一列的数即为答案中$c$的次数。

然而我比赛时一直`TLE on pretest 18`，后来才发现矩乘时乘负数使得负次数快速幂跑不动。。。加上一个(+MOD)%MOD就AC了，我还是太菜了。

似乎dalao们和我的矩阵都不一样耶。

Code:
```cpp
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#include<cstdio>
#include<cstring>
#define rg register
#define ll long long
const int MOD=1e9+6;
const int P=1e9+7;
const int BUF_SIZE=1000000;
inline char rc()
{
    static char buf[BUF_SIZE],*ps=buf,*pe=buf;
    if(ps==pe)
    {
        pe=buf+fread(buf,1,BUF_SIZE,stdin);
    }
    return *ps++;
}
inline ll read()
{
    ll x=0;char c=rc();
    while(c<'0'||c>'9')c=rc();
    while(c>='0'&&c<='9')x=x*10+c-'0',c=rc();
    return x;
}
inline void mul(ll s[5][5],ll t[5][5])
{
    ll p[5][5];
    for(rg int i=0;i<5;++i)
    {
        for(rg int j=0;j<5;++j)
        {
            p[i][j]=0;
            for(rg int k=0;k<5;++k)
            {
                p[i][j]=((p[i][j]+s[i][k]*t[k][j]%MOD+MOD)%MOD
            }
        }
    }
    for(rg int i=0;i<5;++i)
    {
        for(rg int j=0;j<5;++j)
        {
            s[i][j]=p[i][j];
        }
    }
}
inline void mul1(ll s[3][3],ll t[3][3])
{
    ll p[3][3];
    for(rg int i=0;i<3;++i)
    {
        for(rg int j=0;j<3;++j)
        {
            p[i][j]=0;
            for(rg int k=0;k<3;++k)
            {
                p[i][j]=(p[i][j]+s[i][k]*t[k][j])%MOD;
            }
        }
    }
    for(rg int i=0;i<3;++i)
    {
        for(rg int j=0;j<3;++j)
        {
            s[i][j]=p[i][j];
        }
    }
}
ll n,a,b,c,k,ans=1;
ll r[5][5],r1[3][3];
ll s1[3][3]={
    {0,0,1},
    {1,0,1},
    {0,1,1}
    };
ll s2[5][5]={
    {0,0,0,0,1},
    {1,0,0,0,-1},
    {0,1,0,0,0},
    {0,0,1,0,-2},
    {0,0,0,1,3}
    };
ll s3[3][3]={
    {1,0,0},
    {0,0,0},
    {0,0,0}
    };
ll s4[3][3]={
    {0,1,0},
    {0,0,0},
    {0,0,0}
    };
ll s5[3][3]={
    {0,0,1},
    {0,0,0},
    {0,0,0}
    };
ll s6[5][5]={
    {2,6,14,30,60},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
    };
inline void qpw(rg ll s[5][5],rg ll k)
{
    for(rg int i=0;i<5;++i)
    {
        for(rg int j=0;j<5;++j)
        {
            r[i][j]=(i==j);
        }
    }
    while(k)
    {
        (k&1)&&(mul(r,s),1);
        mul(s,s),k>>=1;
    }
}
inline void qpw1(rg ll s[3][3],rg ll k)
{
    for(rg int i=0;i<3;++i)
    {
        for(rg int j=0;j<3;++j)
        {
            r1[i][j]=(i==j);
        }
    }
    while(k)
    {
        (k&1)&&(mul1(r1,s),1);
        mul1(s,s),k>>=1;
    }
}
inline ll qpwr(rg ll x,rg ll k)
{
    rg ll res=1;
    while(k)
    {
        (k&1)&&(res=res*x%P);
        x=x*x%P,k>>=1;
    }
    return res;
}
int main()
{
    n=read(),a=read(),b=read(),c=read(),k=read();
    qpw1(s1,n-3);
    mul1(s3,r1),mul1(s4,r1),mul1(s5,r1),qpw(s2,n-4);
    mul(s6,r);
    a=qpwr(a,s3[0][2]),b=qpwr(b,s4[0][2]),c=qpwr(c,s5[0][2]),k=qpwr(k,s6[0][0]);
    ans=((ans*a*b%P)*c%P)*k%P;
    printf("%I64d\n",ans);
    return 0;
}
```

---

## 作者：coderJerry (赞：0)

考虑矩阵加速求数列第 $t$ 项 $c,f_1,f_2,f_3$ 的指数，分别用 $p_{t,0},p_{t,1},p_{t,2},p_{t,3}$ 表示他们的指数，接下来考虑怎么转移。可以发现：

$f_t=c^{2t-6}\times f_{t-1} \times f_{t-2} \times f_{t-3}.$

$=c^{2t-6+\sum_{i=1}^3 p_{t-i,0}}\times f_{t-1}^{\sum_{i=1}^3 p_{t-i,1}} \times f_{t-2}^{\sum_{i=1}^3 p_{t-i,2}} \times f_{t-3}^{\sum_{i=1}^3 p_{t-i,3}}.$

于是

$p_{t,k}=\sum_{i=1}^3 p_{t-i,k}(k=1/2/3)$；$p_{t,0}=2t-6+\sum_{i=1}^3 p_{t-i,0}$。

前面这个式子的转移显而易见，就是：

$\begin{bmatrix} p_{t-3,k}\\p_{t-2,k}\\p_{t-1,k} \end{bmatrix} \times \begin{bmatrix} 0&1&0\\0&0&1\\1&1&1 \end{bmatrix}=\begin{bmatrix} p_{t-2,k}\\p_{t-1,k}\\p_{t,k} \end{bmatrix}(k=1/2/3).$

至于后面那个式子，我们将 $2t-6$ 拆开成 $2(t-1)-6$ 和 $2$ 两部分转移即可，就是：

$\begin{bmatrix} p_{t-3,k}\\p_{t-2,k}\\p_{t-1,k}\\2(t-1)-6\\2 \end{bmatrix} \times \begin{bmatrix} 0&1&0&0&0\\0&0&1&0&0\\1&1&1&1&1\\0&0&0&1&1\\0&0&0&0&1 \end{bmatrix}=\begin{bmatrix} p_{t-2,k}\\p_{t-1,k}\\p_{t,k}\\2t-6\\2 \end{bmatrix}(k=0).$

矩阵快速幂即可。注意矩阵乘的时候指数有可能过大爆 ```long long```，所以要模 $\varphi(10^9+7)=10^9+6$（欧拉降幂）。不模会 ```WA on 4```。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace math{
    int qpow(int x,int y,int mod){
        int ans=1;
        while(y>0){
            if(y&1) ans=(ans*x)%mod;
            y>>=1;
            x=(x*x)%mod;
        }
        return ans;
    }
}
namespace matrix{
	vector<vector<int>> mul(vector<vector<int>> a,vector<vector<int>> b,int mod){
		int n=a.size();
		vector<vector<int>> ans(n,vector<int>(n,0));
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				for(int k=0;k<n;k++){
					ans[i][j]=(ans[i][j]+(a[i][k]*b[k][j])%mod)%mod;
				}
			}
		}
		return ans;
	}
	vector<vector<int>> qpow(vector<vector<int>> a,int b,int mod){
		if(b==1) return a;
		vector<vector<int>> ans=matrix::qpow(a,b/2,mod);
		ans=matrix::mul(ans,ans,mod);
		if(b%2==1) ans=matrix::mul(ans,a,mod);
		return ans;
	}
}
const int mod=1e9+7;
signed main(){
    int n,f1,f2,f3,c;
    cin>>n>>f1>>f2>>f3>>c;
    if(n==1) cout<<f1;
    if(n==2) cout<<f2;
    if(n==3) cout<<f3;
    if(n>3){
        vector<vector<int>> b(3,vector<int>(3,0));
        b[0][1]=b[1][2]=b[2][0]=b[2][1]=b[2][2]=1;
        b=matrix::qpow(b,n-3,mod-1);
        int p1=b[2][0],p2=b[2][1],p3=b[2][2];
        vector<vector<int>> a(5,vector<int>(5,0));
        a[0][1]=a[1][2]=a[2][0]=a[2][1]=a[2][2]=a[2][3]=a[2][4]=a[3][3]=a[3][4]=a[4][4]=1;
        a=matrix::qpow(a,n-3,mod-1);
        int pc=2*a[2][4];
        //printf("%lld %lld %lld %lld",pc,p1,p2,p3);
        cout<<math::qpow(c,pc,mod)*math::qpow(f1,p1,mod)%mod*math::qpow(f2,p2,mod)%mod*math::qpow(f3,p3,mod)%mod;
    }
    return 0;
}
```

---

## 作者：baka24 (赞：0)

你发现这个题长得很像斐波那契数列，于是考虑矩阵快速幂。

这个 $c^{2x-6}$ 很奇怪，很不规整，考虑怎么把它去掉。

$$
c^x f_x=c^{3x-6}\times f_{x-1} f_{x-2} f_{x-3}=c^{x-1}f_{x-1}\times c^{x-2}f_{x-2}\times c^{x-3}f_{x-3}
$$

于是我们考虑直接对 $f_x\times x$ 进行处理，原式转化为 $f_x=f_{x-1}f_{x-2}f_{x-3}$。

这看起来不是很好做，因为递推式使用的是乘法，不好转成矩阵快速幂。

考虑如何把递推式转成加法，我们知道 $a^p\times a^q=a^{p+q}$，而答案只由 $f_1,f_2,f_3$ 的幂构成，我们可以用矩阵算出 $f_1,f_2,f_3$ 在答案中的指数是多少，最后用普通快速幂算出来。

至于指数怎么算，指数计算相当于 $g_x=g_{x-1}+g_{x-2}+g_{x-3}$，可以列出转移矩阵：
$$
\begin{bmatrix} g_{i-3}&g_{i - 2} & g_{i-1} \end{bmatrix} \times \begin{bmatrix} 0&0 & 1 \\ 1 & 0&1\\0&1&1 \end{bmatrix} = \begin{bmatrix} g_{i-2} & g_{i-1}&g_i \end{bmatrix}
$$

而对于 $f_1,f_2,f_3$，三者的初始化分别为 $g_1=1,g_2=0,g_3=0$，$g_1=0,g_2=1,g_3=0$，$g_1=0,g_2=0,g_3=1$。

最后算出每个数对应的指数后，还需要把它除以 $x$，这里用逆元即可。

[**code**](https://codeforces.com/problemset/submission/1182/279272658)

---

## 作者：Missa (赞：0)

题解区都是用矩阵直接算封闭形式中 $f_1,f_2,f_3$ 的系数的，这里给个更偏 MO 风格且好写的做法。

首先先想办法用 $f_x \cdot k(x)$ 代 $f_x$ 以消掉 $c^{2x-6}$ 这个不好处理的东西。

明显 $k(x)$ 是 $c^{ax+b}$ 的形式，代进去对比系数可以发现 $a=1,b=0$。

于是 $f_x \cdot c^{x} = (f_{x-1}\cdot c^{x-1}) (f_{x-2}\cdot c^{x-2})(f_{x-3}\cdot c^{x-3})$，这是一个很好看的形式。

做个换元，$h_x=f_x \cdot c^{x}$，$h$ 的前三项可以以 $f$ 算出。

我们知道取个 $\ln$ 就是标准矩乘形式，但是显然没必要。在矩乘中用乘方代替乘号，用乘法代替加法，就可以直接做这种东西了。事实上就是取个指数后的普通矩乘。

换句话说，我们的矩阵上递推的是指数。

~~这样能大大减少代码量，至于速度，我还没试（~~

由于我的矩阵用的是模板，代码达到了 `2k`，然而核心部分非常短。

随便写不卡常就有 `45ms`，轻松跑进第一页，吊打那些上百毫秒的每一项单独递推。

核心部分长这个样：

```cpp
signed main(){
    scanf("%lld %lld %lld %lld %lld", &n, &f1, &f2, &f3, &c);
    int h0 = 1ll * f3 * qpow(c, 3) % mod,
        h1 = 1ll * f2 * qpow(c, 2) % mod,
        h2 = 1ll * f1 * qpow(c, 1) % mod;
    matrix tran(3, 3);
    tran[0][0] = tran[0][1] = tran[1][0] = tran[1][2] = tran[2][0] = 1;
    tran = tran ^ (n-1);
    int ans = 1ll * qpow(h0, tran[0][2]) * qpow(h1, tran[1][2]) % mod
                  * qpow(h2, tran[2][2]) % mod;
    ans = 1ll * ans * qpow(inv(c), n % phi) % mod;
    printf("%lld\n", ans);
}
```

完整代码见 [此](https://www.luogu.com.cn/paste/t8motnhq)，也只是多一些矩阵板子和快速幂板子。

注意因为矩阵递推的是指数，矩阵运算时要膜 $\varphi(mod) = mod-1$。

这道题的十几篇题解几乎都是又慢又难写的每项分开矩乘，唯一的一篇与我的思路相同的还是靠灵感发现能够做此变换，实在令人感慨。

---

## 作者：Arghariza (赞：0)

题意：

- 求：

$$f_x=c^{2x-6}f_{x-1}f_{x-2}f_{x-3}$$

---

考虑逐个拆开，递推求指数，欧拉定理+快速幂合并。

$x=3$ 之前的指数不用算了。

1. $x=4$ 时，$f_4=c^2\times f_1\times f_2\times f_3$
2. $x=5$ 时，$f_5=c^6\times f_1\times f_2^2\times f_3^2$
3. $x=6$ 时，$f_6=c^{14}\times f_1^2\times f_2^3\times f_3^4$
4. ...

由于 $f_x=c^{2x-6}f_{x-1}f_{x-2}f_{x-3}$，所以 $c,f_1,f_2,f_3$ 的指数是可以写成递推形式的：

- $c:x_i=x_{i-1}+x_{i-2}+x_{i-3}+2i-6$
- $f_{1},f_{2},f_{3}:y_i=y_{i-1}+y_{i-2}+y_{i-3}$

需要注意的是，$f_1,f_2$ 和 $f_3$ 系数递推式前三位是不相同的，所以即使转移矩阵一样， $ans$ 矩阵初始化的时候也要赋不同的数值。

后面那个 $f_1,f_2,f_3$ 很好说，主要是前面这个 $c$：

$$x_i=x_{i-1}+x_{i-2}+x_{i-3}+2i-6$$

后面这个 $2i-6$ 咋办？

发现每一次 $i$ 变成 $i+1$ 的时候 $2i-6$ 递增一个**定值** $2$。

我们把这个 $2$ 塞到矩阵里面和之前的 $2(i-1)-6=2i-8$ 做个加法：

$\begin{bmatrix}f_{i-1}\quad f_{i-2}\quad f_{i-3}\quad 2i-8\quad 2\end{bmatrix}\times \mathtt{base}=\begin{bmatrix}f_{i}\quad f_{i-1}\quad f_{i-2}\quad 2i-6\quad 2\end{bmatrix}$

由 $x_i=x_{i-1}+x_{i-2}+x_{i-3}+2i-6$ 解出：

$$\mathtt{base}=\begin{bmatrix}1\quad 1\quad 0\quad 0\quad 0\\1\quad 0\quad 1\quad 0\quad 0\\1\quad 0\quad 0\quad 0\quad 0\\1\quad 0\quad 0\quad 1\quad 0\\1\quad 0\quad 0\quad 1\quad 1\end{bmatrix}$$

然后之后就简单了，初始化答案矩阵即可。

---

咋合并答案呢？

由欧拉定理我们知道：

$$a^b\equiv a^{b\mod \varphi(p)}\mod p$$

然后 $\varphi(p)=\sum\limits_{i=1}^{p-1}[\gcd(i,p)=1]$，由于 $p=10^9+7$ 是一个奇数，我们对于每个指数对 $10^9+6$ 取模即可。

最后快速幂再乘起来就结束啦。![](https://啧.tk/doge)

复杂度 $O(t^3 \log n)$，$t$ 为矩阵大小。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7, phi = 1e9 + 6;
struct matrix {// 矩阵结构体
	int s[10][10], sz;
	matrix () { memset(s, 0, sizeof(s)); }
	matrix operator * (const matrix &rhs) const { 
		matrix res;
		res.sz = sz;
		for (int i = 1; i <= sz; i++) {
			for (int j = 1; j <= sz; j++) {
				for (int k = 1; k <= sz; k++) {
					res.s[i][j] = (res.s[i][j] + s[i][k] * rhs.s[k][j]) % phi;
				}
			}
		}
		return res;
	}
} base1, base2, ans1, ans2, ans3, ans4;
int n, c, f1, f2, f3, p1, p2, p3, p4;

void init() {// 初始化矩阵
	base1.sz = ans1.sz = 5;
	base2.sz = ans2.sz = ans3.sz = ans4.sz = 3;
	base1.s[1][1] = base1.s[1][2] = base1.s[2][1] = base1.s[2][3] = base1.s[3][1] = base1.s[4][1] = base1.s[4][4] = base1.s[5][1] = base1.s[5][4] = base1.s[5][5] = 1;
	base2.s[1][1] = base2.s[1][2] = base2.s[2][1] = base2.s[2][3] = base2.s[3][1] = 1;
	ans2.s[1][1] = 4, ans3.s[1][1] = 3, ans2.s[1][2] = ans3.s[1][2] = ans4.s[1][1] = 2;
	ans2.s[1][3] = ans3.s[1][3] = ans4.s[1][2] = ans4.s[1][3] = 1;
	ans1.s[1][5] = 2, ans1.s[1][1] = 14, ans1.s[1][2] = 6, ans1.s[1][3] = 2, ans1.s[1][4] = 6;
}

void ksm_matrix(int p) {// 矩阵快速幂
	while (p) {
		
		if (p & 1) ans1 = ans1 * base1, ans2 = ans2 * base2, ans3 = ans3 * base2, ans4 = ans4 * base2;
		base1 = base1 * base1, base2 = base2 * base2;
		p >>= 1;
	}
}

int ksm_int(int p, int q) {
	int res = 1;
	while (q) {
		if (q & 1) res = res * p % mod;
		p = p * p % mod;
		q >>= 1;
	}
	return res;
}

signed main() {
	scanf("%lld%lld%lld%lld%lld", &n, &f1, &f2, &f3, &c);
	if (n <= 6) {
		if (n == 4) printf("%lld", c * c % mod * f3 % mod * f2 % mod * f1 % mod);
		else if (n == 5) printf("%lld", ksm_int(c, 6) * ksm_int(f3, 2) % mod * ksm_int(f2, 2) % mod * f1 % mod);
		else printf("%lld", ksm_int(c, 14) * ksm_int(f3, 4) % mod * ksm_int(f2, 3) % mod * ksm_int(f1, 2) % mod);
		return 0;
	}
	init();
	ksm_matrix(n - 6);
	p1 = ksm_int(c, ans1.s[1][1]);
	p2 = ksm_int(f3, ans2.s[1][1]);
	p3 = ksm_int(f2, ans3.s[1][1]);
	p4 = ksm_int(f1, ans4.s[1][1]);
	printf("%lld", p1 * p2 % mod * p3 % mod * p4 % mod);
	return 0;
}
```

---

