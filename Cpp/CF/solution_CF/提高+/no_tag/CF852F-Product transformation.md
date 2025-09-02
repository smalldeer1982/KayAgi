# Product transformation

## 题目描述

Consider an array $ A $ with $ N $ elements, all being the same integer $ a $ .

Define the product transformation as a simultaneous update $ A_{i}=A_{i}·A_{i+1} $ , that is multiplying each element to the element right to it for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/6fc715796ff6b053c1fbfce2cbd3ef15490be11e.png), with the last number $ A_{N} $ remaining the same. For example, if we start with an array $ A $ with $ a=2 $ and $ N=4 $ , then after one product transformation $ A=[4,\ 4,\ 4,\ 2] $ , and after two product transformations $ A=[16,\ 16,\ 8,\ 2] $ .

Your simple task is to calculate the array $ A $ after $ M $ product transformations. Since the numbers can get quite big you should output them modulo $ Q $ .

## 说明/提示

The multiplicative order of a number $ a $ modulo $ Q $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/f742a70333572ee21e11b5a43ec5f0a2a3c5a39d.png), is the smallest natural number $ x $ such that $ a^{x}\ mod\ Q=1 $ . For example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF852F/0356983d0321626e54baaf7ca150cf5fcbe1dd67.png).

## 样例 #1

### 输入

```
2 2 2 7
```

### 输出

```
1 2 ```

# 题解

## 作者：不知名用户 (赞：3)

# 1.核心部分：各项的指数
嗯，这题的关键就是找出每一项的指数。

可是怎么找呢？拿出纸和笔推一下 $n=4, m=5$ 时情况：
```
1  1  1  1
2  2  2  1
4  4  3  1
8  7  4  1
15 11 5  1
```
这个特点不太明显，（看出它，其它就是 code 怎么写的事），但我一眼就瞪了出来（别问我怎么瞪），第 $i+1$ 行第 $j+1$ 列（列从右往左数，记为 $a_{ij}$）的数是
$$\sum_{k=0}^j\text{C}_i^k = \text{C}_i^0 + \text{C}_i^1 + \cdots + \text{C}_i^j$$
我们尝试用数学归纳法去证明它，显然当 $i = 1$ 或 $j = 1$ 时成立，下证 
$$a_{i,j} = a_{i-1,j} + a_{i-1,j-1}$$
首先，有等式
$$\text{C}_a^b=\text{C}_{a-1}^b + \text{C}_{a-1}^{b-1}$$
这个等式不难用算两次证明： $n$ 个人中选 $m$ 个人有 $\text{C}_a^b$ 种方法，考虑一个人选或不选分别有 $\text{C}_{a-1}^b , \text{C}_{a-1}^{b-1}$ 种选法，证毕。
$$\begin{aligned}
a_{i,j} & = \text{C}_i^0 + \text{C}_i^1 + \cdots + \text{C}_i^j \\ & = \text{C}_{i-1}^0 + (\text{C}_{i-1}^0+\text{C}_{i-1}^1) + (\text{C}_{i-1}^1 + \text{C}_{i-1}^2) + \cdots + (\text{C}_{i-1}^{j-1}+\text{C}_{i-1}^j) \\ & = (\text{C}_{i-1}^0 + \text{C}_{i-1}^1 + \cdots + \text{C}_{i-1}^{j-1}) + (\text{C}_{i-1}^0 + \text{C}_{i-1}^1 + \cdots + \text{C}_{i-1}^j) \\ &= a_{i-1,j} + a_{i-1,j-1}
\end{aligned}$$
证毕。

结束了？没有，因为只是解决了指数问题，然后还有许多(见第二部分)。
# 2.乘法阶与组合数
乘法阶： $a^x \equiv 1 \pmod{p}$，怎么求 $x$？原题中保证 $x \le 10^6$，枚举即可。

求组合数：$\text{C}_i^0 , \text{C}_i^1 , \cdots , \text{C}_i^j \mod{x}, \text{C}_k^l=\frac{k!}{(k-l)!l!}$，分别求出 $1!,2!,\cdots,i!\mod{x}$ 及其模 $x$ 的逆元，原题中已提到 $x$ 为质数，故必然存在逆元。
# 3.talk is cheap, show me the code
```cpp
#include<bits/stdc++.h>
#define II inline int
#define int long long 
using namespace std;

const int N = 1e6 + 200;

int phiq, x[N], y[N], out[N];

II phi(int a, int q)
{
	int cnt=0, i=1;
	while(cnt==0||i!=1)
	{
		i = i * a % q;
		cnt++;
	}
	return cnt;
}

II power(int a, int b, int p)//a^b%p
{
	int c=b, d=1, e=a;
	while(c)
	{
		if(c&1) d = (d * e) % p;
		c >>= 1;
		e = (e * e) % p;
	}
	return d;
}

II C(int a, int b)
{
	return x[a] * y[a-b] % phiq * y[b] % phiq;
}

signed main()
{
	int n, m, a, q, i, sum=0;
	scanf("%lld%lld%lld%lld", &n, &m, &a, &q);
	phiq = phi(a,q);
	x[0] = y[0] = 1;
	for(i=1;i<=m;i++)
	{
		x[i] = (x[i-1] * i) % phiq;
		y[i] = power(x[i],phiq-2,phiq);
	}
	for(i=0;i<n;i++)
	{
		sum = (sum + C(m,i)) % phiq;
		out[i] = power(a,sum,q);
	}
	for(i=n-1;~i;i--) printf("%lld ", out[i]);
	return 0;
}
``

---

## 作者：xzggzh1 (赞：2)

题意：

有一个长度为 $n$ 的数组全部元素都是 $a$ 。

现在进行 $m$ 次操作，每次操作将 $A[i]$ 变为 $A[i]*A[i+1]$ ，最后一个元素不变。

现给出 $n,m,a,Q$，输出 $m$ 次操作后的 $A$ 数组，每个元素对 $Q$ 取模。

$n,m\leq 10^6+123$ 。

----


这个题的操作不算复杂，而且给出的初始数组元素种都是 $a$ ，可以看出来是让我们直接计算出每一位的值

$ a^1 \ a^1 \ a^1 \ a^1 \ a^1 \ a^1 \ a^1$

$a^2 \ a^2 \ a^2 \ a^2 \ a^2 \ a^2 \ a^1$

$a^4 \ a^4 \ a^4 \ a^4 \ a^4 \ a^3 \ a^1$

$a^8 \ a^8 \ a^8 \ a^8 \ a^7 \ a^4 \ a^1$

$a^{16} \ a^{16} \ a^{16} \ a^{15} \ a^{11} \ a^5 \ a^1$

$…$

如果不是最后一个数的“干扰” $m$ 次过后应该会变成 $a^{(2^{m-1})}$，但是最后一个元素始终是 $a$ ，所以我们提取出每一位数的指数与 ${2^{m-1}}$ 的差值，为了方便找规律，我们再把序列反转，可以得到：

$0 \ 0\ 0\ 0\ 0\ 0 \ 0…$


$1 \ 0\ 0\ 0\ 0\ 0 \ 0…$


$3 \ 1\ 0\ 0\ 0\ 0 \ 0…$


$7 \ 4\ 1\ 0\ 0\ 0 \ 0…$


$15 \ 11\ 5\ 1\ 0\ 0 \ 0 …$



$31  \ 26\ 16\ 6\ 1\  0 \ 0 …$


$61 \ 57\ 42\ 22\ 7\ 1\ 0 …$

$…$

可以看出来是类似杨辉三角形式的，一个数是上面相邻两数之和，每行第一个数是 $2^{i-1}-1$ ，每行最后一个不是零的数是 $1$ 。

由于 $n,m$ 是 $10^6$ 级别的，所以不能爆算每一位的值，需要找到捷径。

再对这个数列取一个差分（就是后面的一位减去前面的一位），得到如下的东西。

$0 \ 0\ 0\ 0\ 0\ 0 \ 0…$


$1 \ 0\ 0\ 0\ 0\ 0 \ 0…$


$2 \ 1\ 0\ 0\ 0\ 0 \ 0…$


$3 \ 3\ 1\ 0\ 0\ 0 \ 0…$


$4 \ 6\ 4\ 1\ 0\ 0 \ 0 …$



$5  \ 10\ 10\ 5\ 1\  0 \ 0 …$


$6 \ 15\ 20\ 15\ 6\ 1\ 0 …$

$…$

这就十分的眼熟了，第 $i$ 行 第 $j$ 列竟是 $\tbinom{i-1}{j}$。

但还有个问题：这里我们求的是指数上的数，这个问题的数规模会很大，要用为指数取模，这里不必用到[欧拉定理](https://www.luogu.com.cn/problem/P5091)，只要枚举出 $a^i \mod Q=1$ 的 $i$ 即可，由题意得，这个 $i$ 也是 $10^6$ 级别的，然后指数都对这个 $i$ 取模即可。

---

核心代码：

```cpp
int main(){
	scanf("%d%d%d%d",&n,&m,&A,&Q);
	int i;
	for (i=A%Q,mod=1; i!=1; mod++) 
		i=(ll)i*A%Q;fac[0]=1;
	for (i=1; i<mod; i++) 
		fac[i]=(ll)fac[i-1]*i%mod;f[0]=1;
	for (i=1; i<=m; i++)
    	f[i]=(f[i-1]+(ll)fac[m]*inv(fac[i])%mod*inv(fac[m-i]))%mod;
	for (i=m+1;i<=n; i++) 
		f[i]=f[i-1];
	for (i=n; i; i--)
		printf("%d%c",ksm(A,f[i-1],Q),(i>1)?' ':'\n');
}
```



---

## 作者：Starrykiller (赞：1)

给出一种利用 GF 的推导。

Empty_Dust 给的题。拜谢。

前置知识：你需要知道什么是**阶**（更为具体地说，是乘法群中的阶）以及阶的求法，熟悉欧拉定理和普通型生成函数。

我们先将原数组 reverse 一下，设指数序列 $f=\{1,1,1,\cdots,1\}$，那么每次变换就是令 $f_i\gets f_i+f_{i-1}。$

套路地设 $f$ 的生成函数为 $F(z)=\dfrac{1}{1-z}$，由卷积的定义，发现每次变换就是卷上 $(1+z)$，所以 $m$ 次变换后的数列的生成函数就是 $F'(z)=F(z)(1+z)^m=\dfrac{(1+z)^m}{1-z}$。

换个角度思考，发现 $(1+z)^m$ 对应的数列就是 $\displaystyle {m\choose 0},{m\choose 1},\cdots$，然后卷上 $\dfrac{1}{1-z}$ 就是求前缀和。所以 $m$ 次变换后，$\displaystyle f'_i=\sum_{j\le i}{m\choose j}$。

题目保证了 $q=\mathrm{ord}(a,p)$ 是一个素数，而且 $m\le q$，所以我们可以直接预处理阶乘和阶乘逆元来处理 $f_i$。由于 $q$ 是 $a$ 的阶，所以自然可以直接对 $q$ 取模。

处理完后，翻转后求快速幂输出即可。

[My submission](https://codeforces.com/contest/852/submission/261199933).

---

