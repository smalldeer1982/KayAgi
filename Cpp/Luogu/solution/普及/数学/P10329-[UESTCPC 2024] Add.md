# [UESTCPC 2024] Add

## 题目描述

给定一个长度为 $n$ 的序列 $a_1,a_2,\ldots,a_n$，初始时 $a_i=i$。对该序列进行 $n-1$ 次操作，其中第 $i$ 次操作为在 $[1,n-i]$ 中等概率选择一个整数 $j$，令 $a_j$ 变为 $a_j+2a_{n-i+1}$。

求操作完毕后 $a_1$ 的期望 $\bmod\text{ }998244353$ 的值。

## 样例 #1

### 输入

```
3
4
2
5```

### 输出

```
30
5
55```

## 样例 #2

### 输入

```
3
4
3
5```

### 输出

```
30
14
55```

## 样例 #3

### 输入

```
3
8
1
3```

### 输出

```
204
1
14```

# 题解

## 作者：lndjy (赞：6)

观察可以发现，$a_i$ 对答案的贡献为 $ia_i$。

下面使用数学归纳法证明。

显然 $i=1$ 时成立。

假设对于 $1$ 到 $i-1$ 成立，则 $a_i$ 对答案的贡献为

$$a_i\frac{2\sum\limits_{j=1}^{i-1}j}{i-1}=a_i\frac{i(i-1)}{i-1}=ia_i$$

所以答案为 $\sum\limits_{i=1}^n i^2=\frac{n(n+1)(2n+1)}{6}$。

---

## 作者：shiranai (赞：3)

&emsp;&emsp;又是一道期望题，楼上各位已经给出了题目的答案了，对于给定的 $n$，要输出 $\sum_{i=1}^ni^2=n(n+1)(2n+1)/6$。下面对于推导过程从概率论上给出一个**比较严谨**的证明。  
### 记号与初值条件
&emsp;记 $f(i,j)$ 表示经过第 $i$ 次操作后 $a_j$ 的**值**，$E(i,j)$ 是 $f(i,j)$ 的**期望值**。显然，我们有初值条件：
$$E(0,j)=f(0,j)=j(1\leq j\leq n)\tag{1}$$
### 递推式准备
&emsp;&emsp;题目要求的就是 $E(n-1,1)$。我们首先可以找出一个递推关系。  
&emsp;&emsp;考虑第 $i(1\leq i\leq n-1)$ 次操作，这次操作是将现在 $a_{n-i+1}$ 的值随机加到 $a_1$ 到 $a_{n-i}$ 身上，概率各为 $1/(n-i)$。由于现在 $a_{n-i+1}$ 的值是 $f(i-1,n-i+1)$，所以对于任意的 $j$，$a_j$ 有 $\cfrac{1}{n-i}$ 的概率被加，也有 $\cfrac{n-i-1}{n-i}$ 的概率不变。因此，我们有：
$$f(i,j)=\cfrac{1}{n-i}\left[f(i-1,j)+2f(i-1,n-i+1)\right]+\cfrac{n-i-1}{n-i}f(i-1,j)=f(i-1,j)+\cfrac{2f(i-1,n-i+1)}{n-i}\tag{2}$$
&emsp;&emsp;根据**期望的线性性**，对式 $(2)$ 两边同时取期望，得：
$$E(i,j)=E(i-1,j)+\cfrac{2E(i-1,n-i+1)}{n-i}\tag{3}$$
### 重要等式准备
&emsp;&emsp;考察式 $(3)$，发现 $E(i,j)$ 与 $E(i-1,j)$ 之间的差 $D_i=\cfrac{2E(i-1,n-i+1)}{n-i}$和 $j$ 是无关的。所以：
$$E(i,j)=D_i+D_{i-1}+\cdots+D_1+E(0,j)=S_i+j\tag{4}$$
&emsp;&emsp;其中 $S_i=\sum_{k=1}^iD_k$ 仅仅是 $i$ 的函数。根据式 $(4)$，可以得到以下等式：
$$E(i,j)-j=E(i,1)-1=S_i\tag{5}$$
&emsp;&emsp;从而得到**重要等式**：
$$E(i,j)=E(i,1)+j-1\tag{6}$$
### 最终推导
&emsp;&emsp;这时，一切都好办了。在 $(3)$ 式中，我们令 $j=1$ 得：
$$E(i,1)=E(i-1,1)+\cfrac{2E(i-1,n-i+1)}{n-i}\tag{7}$$
&emsp;&emsp;根据重要等式 $(6)$，我们有 $E(i-1,n-i+1)=n-i+E(i-1,1)$。代入式 $(7)$，得：
$$E(i,1)=E(i-1,1)+\cfrac{2}{n-i}[n-i+E(i-1,1)]=2+\cfrac{n-i+2}{n-i}E(i-1,1)\tag{8}$$
&emsp;&emsp;式 $(8)$ 的形式已经是一个数列了，可以利用高中的已知递推公式求出通项公式。  
&emsp;&emsp;记$b_i=E(i,1)$，则根据式 $(1)$我们有初值 $b_0=E(0,1)=1$,式 $(8)$ 可重写为：
$$b_i=\cfrac{n-i+2}{n-i}b_{i-1}+2\tag{9}$$
&emsp;&emsp;在式 $(9)$ 两边同时乘 $(n-i)(n-i+1)$ 得：
$$(n-i+1)(n-i)b_i=(n-i+2)(n-i+1)b_{i-1}+2(n-i)(n-i+1)\tag{10}$$
&emsp;&emsp;利用换元技巧 $c_i=(n-i+1)(n-i)b_i$ 可以将式 $(10)$ 重写为：
$$c_i=c_{i-1}+2(n-i)(n-i+1)\tag{11}$$
&emsp;&emsp;同时还有初值 $c_0=(n+1)nb_0=(n+1)n$。式 $(11)$ 是高中数列典型的一类题。由于多项式是 $i$ 的二次多项式，我们尝试待定系数：
$$c_i=C_1i^3+C_2i^2+C_3i+C_4\tag{12}$$
&emsp;&emsp;其中 $C_k(k=1,2,3,4)$ 是待定系数。将式 $(12)$ 代入式 $(11)$ ，整理可以得到：
$$(3C_1-2)i^2+(4n+2-3C_1+2C_2)i+C_1-C_2+C_3-2n^2-2n=0\tag{13}$$
&emsp;&emsp;能解得 $C_1=2/3,C_2=-2n,C_3=2n^2-2/3$。至于 $C_4$，$C_4=c_0=n^2+n$。  
&emsp;&emsp;所以 $c_i=2i^3/3-2ni^2+(2n^2-2/3)i+n^2+n$。只需代入 $i=n-1$，即得所求 $E(n-1,1)=b_{n-1}=c_{n-1}/2=n(n+1)(2n+1)/6$。

---

## 作者：god_std (赞：2)

~~本题是一个典型的找规律题！！！~~

## Part 1.找规律
##

看样例输入输出就会发现：
因为 $a_i$ 对答案的贡献值为 $ {\color{red} a ^ 2 {}}$.

所以输入 $n$ 就会输出：
$$
1\times1+2\times2+3\times3+......+(n)\times(n)
$$
也就等同于：
$$
\frac{n(n+1)(2n+1)}{6}
$$

## Part 2.输出
##
代码如下:
```cpp
#include<bits/stdc++.h>
using namespace std;
int Ea1(int t){ 
	int t_add_1=t+1,t2_add_1=2*t+1;
	if(t%2==0)t/=2;
	else t_add_1/=2;
	if(t%3==0)t/=3;
	else if(t_add_1%3==0)t_add_1/=3;
	else if(t2_add_1%3==0)t2_add_1/=3;
	long long a=t;
   //上面的代码是用来除以6的。
	a%=998244353;
	a*=t_add_1;
	a%=998244353;
	a*=t2_add_1;
	a%=998244353;
	return int(a);
}
int main(){
	int T;
	cin>>T;
	for(int i=1;i<=T;i++){
		int a;
		cin>>a;
		cout<<Ea1(a)<<endl;
	}	
	return 0;
}

---

## 作者：Pyrf_uqcat (赞：2)

已知一共 $T$ 组数据，且每输入一个 $n$ 都会有一个答案，观察样例，很明显能够发现每一个 $n$ 都会有固定答案。

比赛时，就想着打表骗点小分，根据样例，把样例输出存入表中打出来了这个：
```cpp
ans[]={0,1,5,14,30,55,0,0,204};
```
经过每项作差发现：所有差都是**平方数**。也就是说，答案为 $1^2+2^2+3^2+\dots+n^2$，这样计算会超时，可以网上查一下运算公式 $ \frac{n(n+1)(2n+1)}{6}$。

但是，很明显缺少证明，被打回了。那只能用一下正常的方法了。

将数 $a_x$ 加入到 $a_y$ 经过计算并化简明显可知，贡献为 $2x^2+2xy$，那么总贡献为 $1(2x^2+2xy)+2(2x^2+2xy)+\dots+(x-1)(2x^2+2xy)=x^3-x$，所以最后答案为 $1(\frac{x^3-x}{x-1})+2(\frac{x^3-x}{x-1})+\dots+x(\frac{x^3-x}{x-1})= \frac{n(n+1)(2n+1)}{6}$，时间复杂度 $O(1)$。

---

## 作者：封禁用户 (赞：2)

背景
-

各位大佬已经推出公式 $S_n=\frac{n(n+1)(2n+1)}{6}$ 了，那么我们就把推公式的过程重现一遍吧。 

推公式过程
-
本人认为有三种方法可以证明，其实很好想到。

- 数学归纳法。

观察下表：

| $n$ | $1$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8$ | $9$ | $10$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $n^2$ | $1$ | $4$ | $9$ | $16$ | $25$ | $36$ | $49$ | $64$ | $81$ | $100$ |
| $S_n$ | $1$ | $5$ | $14$ | $30$ | $55$ | $91$ | $140$ | $240$ | $285$ | $385$ |

在证明前，先把公式稍作改变：

$$S_n=\frac{n(n+\frac{1}{2})(n+1)}{3}$$

对于边界，

$$S_0=0=\frac{0(0+\frac{1}{2})(0+1)}{3}$$

成功。

假定 $n>0$ 时，$S_{n-1}$ 满足公式，则：

$$S_n=S_{n-1}+n^2=\frac{(n-1)(n-\frac{1}{2})n}{3}+n^2=\frac{n^3+\frac{3}{2}n^2+\frac{1}{2}n}{3}=\frac{n(n+\frac{1}{2})(n+1)}{3}$$

由此，可得证。

- 扰动法（从立方差出发）

首先回顾一下扰动法公式：

$$S_n+a_{n+1}=S_{n+1}=a_0+a_1+a_2+\dots+a_{n+1}=a_0+\sum_{k=0}^{n}{a_{k+1}}$$

将其运用到这里中。

$$S_n+(n+1)^2=S_{n+1}=a_0+a_1+a_2+\dots+a_{n+1}=0+\sum_{k=0}^{n}{(k+1)^2}=\sum {k=0}^{n}{k^2}+2k+1=S_n+2\sum_{k=0}^{n}{k}+(n+1)^2$$

然后我们很遗憾得无法继续了，因为左右 $S_n$ 抵消了，但我们得到了另一个结论：

$$\sum_{k=0}^{n}{k}=\frac{n(n+1)}{2}$$

这不就是连续自然数和公式吗？这启示了，我们通过对二阶和采用扰动法可以得到一阶和，那么三阶呢？命 $T_n= {\textstyle \sum_{k=0}^{n}k^3}$，则：

$$T_n+(n+1)^3=T_(n+1)=0+\sum_{k=0}^{n}{k+1}^3=\sum_{k=0}^{n}{k^3}+3k^2+3k+1=T_n+3\sum_{k=0}^{n}{k^2}+\frac{3n(n+1)}{2}+(n+1)$$

很好，左右 $T_n$ 相互抵消，通过移项以及合并，可得：

$$\sum_{k=0}^{n}{k^2}=\frac{n(n+\frac{1}{2})(n+1)}{3}$$

得证。

- 利用积分逼近求和。

![](https://cdn.luogu.com.cn/upload/image_hosting/5x16lxme.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

这里就不做过多解释，把这个函数图象放这了。

- 另一种做法

首先，我们化简给出的期望值公式 $f(x)$：

$$
\begin{aligned}
f(x) &= \frac{\sum_{i=1}^{x-1}2x(x-i)}{x-1} \\
&= \frac{2x\left[x(x-1) - \sum_{i=1}^{x-1}i\right]}{x-1} \\
&= \frac{2x\left[x(x-1) - \frac{1}{2}x(x-1)\right]}{x-1}  \\
&= \frac{x^2(x-1)}{x-1} \\
&= x^2
\end{aligned}
$$
带入上式，则最后的答案为  
$$\sum_{i=1}^{n}i^2 = \frac{n(n+1)(2n+1)}{6}$$
### 平方和求和公式证明

接下来，我们使用数学归纳法证明平方和求和公式：

#### 基础步骤

当 $n=1$ 时，

$$
\sum_{i=1}^{1}i^2 = 1^2 = 1
$$

同时，

$$
\frac{1(1+1)(2 \times 1 + 1)}{6} = \frac{1 \times 2 \times 3}{6} = 1
$$

两者相等，所以 $n=1$ 时公式成立。

#### 归纳步骤

假设当 $n=k$ 时，公式成立，即

$$
\sum_{i=1}^{k}i^2 = \frac{k(k+1)(2k+1)}{6}
$$

那么当 $n=k+1$ 时，

$$
\begin{aligned}
\sum_{i=1}^{k+1}i^2 &= \sum_{i=1}^{k}i^2 + (k+1)^2 \\
&= \frac{k(k+1)(2k+1)}{6} + (k+1)^2 \\
&= \frac{k(k+1)(2k+1) + 6(k+1)^2}{6} \\
&= \frac{(k+1)[k(2k+1) + 6(k+1)]}{6} \\
&= \frac{(k+1)(2k^2 + k + 6k + 6)}{6} \\
&= \frac{(k+1)(2k^2 + 7k + 6)}{6} \\
&= \frac{(k+1)(k+2)(2k+3)}{6} \\
&= \frac{(k+1)[(k+1)+1][2(k+1)+1]}{6}
\end{aligned}
$$

由此可见，当 $n=k+1$ 时，公式也成立。

代码
-

```cpp
#include <bits/stdc++.h>
using namespace std;

const int P = 998244353;
int T, n；

void solve(int tc) {
    cin >> n;
    cout << int(__int128_t(n) * (n + 1) * (n << 1 | 1) / 6 % P) << '\n';
}

int main() {
    cin >> T；
    for (int i = 1; i <= T; i++)
        solve(i);
}
```

---

## 作者：_O_v_O_ (赞：2)

诈骗，场上差点秒。

对于一个 $i$，如果要放到 $j$，很明显对答案贡献之为 $2\times i\times (i-j)$。

那么总贡献为 $\sum\limits_{j=1}^{i-1} 2\times i\times (i-j)$，推一下式子：

$\begin{aligned}\sum\limits_{j=1}^{i-1} 2\times i\times(i-j)&=i\times2\times(\sum\limits_{j=1}^{i-1} (i-j)) \\ &=i\times2\times((i-1)\times i-i\times(i-1)\div 2) \\&=i\times 2\times(i\times (i-1)\div 2) \\ &=i^2\times(i-1)\end{aligned}$

那么期望为 $i^2\times(i-1)\div(i-1)=i^2$。

那么答案为 $\sum\limits_{i=1}^n i^2=n\times(n+1)\times(2\times n+1)$。

可是 $n$ 高达 $10^9$，所以 C++ 需用高精度或模意义下的乘法逆元解决。

但是我们可以用 python，python 代码：

```python
T=int(input())
for i in range(T):
    n=int(input())
    print(n*(n+1)*(2*n+1)//6%998244353)
```

---

## 作者：封禁用户 (赞：1)

### 题意

对一个初始为 $a_i = i$ 的序列进行一系列操作，并求操作完毕后 $a_1$ 的期望值。

### 做法

观察题目描述，可以发现每次操作都是对一个区间内的某个数进行特定的变换，而最终要求的是 $a_1$ 的期望值。

由于每次操作都是随机选择一个数进行变换，可以尝试从期望的线性性质入手。期望的线性性质告诉期望的和等于和的期望，即 $E(X+Y) = E(X) + E(Y)$。然而，直接应用这个性质计算 $a_1$ 的期望是困难的。

但是，观察题目可以发现，对于任意的 $a_i$，其最终值都是由初始值 $i$ 和一系列操作构成的。而操作的本质是对 $a_i$ 加上一个与 $a_{n-i+1}$ 有关的倍数。这里的关键是，虽然 $a_{n-i+1}$ 的值在操作过程中会变化，但是 $a_i$ 被加上的倍数总是与 $a_{n-i+1}$ 的初始值 $n-i+1$ 有关。

进一步观察可以发现，每次操作实际上是将 $a_i$ 乘以 2 并加上 $2 \times (n-i+1)$。这实际上是将 $a_i$ 的贡献增加了 $2i$ 倍，因为 $a_i$ 的初始值是 $i$。由于每次操作都是等概率的，可以认为 $a_i$ 对最终 $a_1$ 期望值的贡献就是 $i$ 乘以 $a_i$ 的最终期望值。

现在，考虑 $a_i$ 的最终期望值。由于 $a_1$ 的初始值是 1，且每次操作都是乘以 2 或者加上一个与 $n$ 有关的值，可以直接计算所有操作对 $a_1$ 的贡献。由于每次操作都是等概率的，且区间长度逐渐减小，我们可以认为 $a_1$ 的期望值是其初始值 1 乘以一个与 $n$ 有关的系数。

最终，可以发现这个系数实际上就是 $\sum_{i=1}^{n} i^2$，即 $1^2 + 2^2 + \cdots + n^2$。这是因为每次操作都将 $a_i$ 的贡献增加了 $i^2$ 倍。利用求和公式，就可以得到 $\sum_{i=1}^{n} i^2 = \frac{n(n+1)(2n+1)}{6}$。

因此，最终的答案就是 $\frac{n(n+1)(2n+1)}{6} \bmod 998244353$。

代码：

```cpp
#include <iostream>
using namespace std;

const int MOD = 998244353;

// 快速幂取模函数
long long quick_pow(long long a, long long b, int mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 逆元计算函数
long long inv(long long x, int mod) {
    return quick_pow(x, mod - 2, mod);
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        
        // 计算 n(n+1)(2n+1)/6 % MOD
        long long n_mul_n_plus_1 = n * (n + 1) % MOD;
        long long two_n_plus_1 = (2 * n + 1) % MOD;
        long long six_inv = inv(6, MOD);
        long long result = (n_mul_n_plus_1 * two_n_plus_1 % MOD) * six_inv % MOD;
        
        cout << result << endl;
    }
    return 0;
}
```

---

## 作者：TLEWA (赞：1)

## 解题思路

面对这种问题，我们不妨从简单会做的特殊情况入手进行推导。

设 $f(i)$ 为 $a_i$ 增加 $1$ 对 $a_1$ 的期望贡献，由定义可知 $f(1)=1$，进一步扩展，我们来思考 $i=2$ 和 $i=3$ 的情形：

$$ f(2) = 2\frac{f(1)}{1} = 2 $$

$$f(3) = 2\frac{f(1)+f(2)}{2} = 3$$

再次扩展，对于 $f(i)$，我们有：

$$f(i)=2\frac{\sum_{j=1}^{i-1} f(j)}{i-1}$$

后半部分等价于对 $f(1)$ 到 $f(i-1)$ 取平均值，现在让我们从更高的视角思考 $i=4$ 的情形：

$$f(4) = 2\frac{f(1)+f(2)+f(3)}{3}=2\frac{f(1)+f(3)}{2}=f(1)+f(3)=f(3)+1$$

由于 $f(1)$ 到 $f(3)$ 是等差数列，所以我们可以用首项和尾项相加除以 $2$ 来计算平均值，将 $2$ 消去后得 $f(4)=f(3)+1$，得到 $f(1)$ 到 $f(4)$ 这部分仍然是等差数列，对于更高的 $i$，数学归纳法套用以上结论即可，最终得到结论 $f(i)=i$。

最终答案即为：

$$\sum\limits_{i=1}^n if(i) = \sum\limits_{i=1}^n i^2$$

对于平方和的计算，可以使用分块打表降低时间复杂度，我们也可以套用平方和公式 $\sum\limits_{i=1}^n i^2=\frac{n(n+1)(2n+1)}{6}$ 进行平方和的快速计算，最终时间复杂度 $O(1)$

## AC 代码

```C++
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int mod=998244353;

int T;
int a,b;
int n;

signed main() {
	cin >> T;
	while(T--) {
		cin >> n;
		a=n*(n+1)/2,b=2*n+1;
		if(a%3) b/=3;
		else a/=3;
		cout << (a%mod)*b%mod << endl;
	}
	return 0;
}
```

---

## 作者：cchstudio (赞：0)

~~(蒟蒻的第一篇题解，请审核大大多多包涵)~~~
# P10329 Add
### 考点一 将未知的模型转换成已知的数学递推公式
首先我们先理解题意：_"进行 $n-1$ 次操作，其中第 $i$ 次操作为在 $[1,n-i]$ 中等概率选择一个整数 $j$ ，令 $a_{j}$ 变为 $a_{j}+2a_{n-i+1}$ "_ 这句话的含义。

可以发现，当 $i=1$ 的时候，相当于在第一项到 $n-1$ 项随机选择一项加上 $2$ 倍的第 $n$ 项，同理， $i=2$ 的时候即为在 $n-1$ 前面的若干项随机选择一项加上第 $n-1$ 项。

当 $n=3$ 时，我们可以罗列以下几种可能的情况：

![Fig.1](https://cdn.luogu.com.cn/upload/image_hosting/h7y2cakh.png)
可以发现：

 $$17=(2a_{3}+a_{2})\times2+a_{1}=4a_{3}+2a_{2}+a_{1}$$ 

 $$11=2a_{3}+a_{1}+2a_{2}=2a_{3}+2a_{2}+a_{1}$$ 

 $$\frac{17+14}{2}=a_{1}+2a_{2}+3a_{3}=1+2\times2+3\times3=1^{2}+2^{2}+3^{2}=14$$

------------

而对于 $n=4$ 时结果同样成立，如下图：

![Fig.2](https://cdn.luogu.com.cn/upload/image_hosting/mqpk4p33.png)
可得:
$$\frac{19+25+27+33+27+49}{6}=1^
{2}+2^{2}+3^{2}+4^{2}=30$$

------------

所以考虑采取数学归纳法，不妨假设 $\bar{x}=\sum_{i=1}^{x} i^2 $ ，则：
$$\overline{x + 1}=\frac{1}{x}((\sum_{i=1}^{x}i^2-1+(2x+2+1))+(\sum_{i=1}^{x}i^2-2^2+(2x+2+2)\times 2)+\cdot\cdot\cdot+(\sum_{i=1}^{x}i^2-(x)^2+(2x+2+x)\times x)
\\=\frac{1}{x}(x\sum_{i=1}^{x}i^2-\sum_{i=1}^{x}i^2+(x+1)^2x+\sum_{i=1}^{x}i^2)
\\=\sum_{i=1}^{x}i^2+(x+1)^2
\\=\sum_{i=1}^{x+1}i^2$$

由此可证得原归纳式成立。

------------
至此，本题的目标就是求得 $\sum_{i=1}^{x}i^2 \bmod998244353$ 的值。
### 考点二 平方和公式
最朴素的方法当然是暴力累加，然后不断 $\bmod$ ，但是显然本题会 TLE ，所以我们需要一种快速求值的方法，我们发现：

$$\sum_{i=1}^{x}i^2=\frac{n^3}{3}+\frac{n^2}{2}+\frac{n}{6}=\frac{n(n+1)(2n+1)}{6}$$ 

证明：（利用恒等式 $(n+1)^3=n^3+3n^2+3n+1$ ）

$$(n+1)^3-n^3=3n^2+3n+1

\\n^3-(n-1)^3=3(n-1)^2+3(n-1)+1

\\\cdots

\\3^3-2^3=3\times2^2+3\times2+1

\\2^3-1^3=3\times1^2+3\times1+1$$

求和得：

$$(n+1)^3-1=3(1^2+2^2+3^2+\cdots+n^2)+3(1+2+3+\cdot\cdot\cdot+n)+n$$

由于：  
$$1+2+3+\cdots=\frac{n(n+1)}{2}$$

整理后得： 
$$1^2+2^2+3^2+\cdots+n^2=\frac{n(n+1)(2n+1)}{6}$$
### 考点三 取模和逆元
关于取模，我们知道：

 $$(a \cdot b) \bmod mod =((a \bmod mod) \cdot (b \bmod mod)) \bmod mod 
\\(a + b) \bmod mod = ((a \bmod mod) + (b \bmod mod)) \bmod mod
\\(a - b) \bmod mod = ((a \bmod mod) - (b \bmod mod)) \bmod mod$$

这三条是显而易见的，并且不具备难度的。因此，对于平方和公式的绝大部分，即 $n(n+1)(2n+1) \bmod mod$ 是不具备难度的。问题就出在 $\frac{1}{6}$ 上。

(前排提醒：如果你并未接触过相关内容，强烈建议先完成以下题目，该题题解对于逆元和三种求逆元的方法（拓展欧几里得、快速幂、线性算法）具有较为系统的阐述：[P3811 【模板】模意义下的乘法逆元](https://www.luogu.com.cn/problem/P3811)
。)

在提出逆元的概念之前，请允许我先介绍一下**费马小定理**：

假如 $p$ 是质数，且 $\gcd(a,p)=1$ ，那么  $a^{(p-1)}\equiv1\pmod p$ 。

------------
也就意味着，如果我们能够求出 $6$ 模除 $\bmod $ 的逆元 $p$ ，那么 $(p\cdot  ((\sum_{i=1}^{x}i^2)\bmod mod))\bmod mod$ 就是最终 $(\frac{\sum_{i=1}^{x}i^2}{6})\bmod mod$ 的值。

~~（这里我利用函数先求出了 mod 的逆元，所以代码里就直接写了。）~~

最后附上 AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;//MOD和6的逆元为166374059

long long squaresum(long long n) {
    return (((n%MOD)*((n%MOD+1)%MOD)%MOD)*(((2*(n%MOD))%MOD+1)%MOD))%MOD;//注意每一步+-*都需要mod一遍
}
int main()
{
    long long T;
    cin>>T;
    for(long long i=0;i<T;i++)
    {
        long long n;
        cin>>n;
        long long x = (166374059 * squaresum(n)) % MOD;
        cout<<x<<endl;
    }
}
```

---

## 作者：___nyLittleT___ (赞：0)

## 思路
首先，$\sum_{i=1}^{n}i^2=\frac{n(n+1)(2n+1)}{6}$，关于这个公式，有一个简便的记法：  
> 你 $(n)$ 和你哥 $(n+1)$ 一起 $(2n+1)$ 去遛 $(6)$ 狗。  

整合起来就是上面的公式。

每个数对答案的影响值如下：  
$$a_i \times\frac{\sum_{j=1}^{i-1}j \times 2}{i-1}=a_i \times \frac{i(i-1)}{i-1}=ia_i$$  
$$\because a_i=i,$$  
$$\therefore ia_i=i^2$$  
即答案为 $\sum_{i=1}^{n}i^2$，套用“遛狗公式”，可直接得出答案。但是要考虑数据溢出问题，这边建议写一个快速乘法，代码如下：  
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define ll long long
using namespace std;
ll t,n;
ll qmul(ll a,ll b,ll p){
	ll ans=0;
	while(b){
		if(b&1) ans=(ans+a)%p;
		a<<=1;
		b>>=1;
	}
	return ans%p;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		ll a=n*(n+1)>>1;
		ll b=(n<<1)+1;
		if(a%3==0) a/=3;
		else b/=3;
      //将 n(n+1)(2n+1)/6 分解为 (n(n+1)/2)*(2n+1)/3
		printf("%lld\n",qmul(a%mod,b%mod,mod));
	}
	return 0;
}
```

---

