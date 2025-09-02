# DerrickLo's Milk Loong (UBC002F)

## 题目描述

给定正整数 $n$，构造 $n$ 个正整数 $a_1,a_2,\cdots,a_n$，使得 $\displaystyle\sum_{i=1}^n a_i=\operatorname{lcm}(a_1,a_2,\cdots,a_n)$（其中 $\operatorname{lcm}$ 为最小公倍数运算），并且这组数的极差是所有构造的极差中最小的。极差指一组数当中的最大值减最小值。

**并且，你构造的这 $n$ 个数的最小公倍数不得超过 $10^{12}$。否则，SPJ 可能出现未定义行为。**

## 说明/提示

#### 样例说明

容易证明，$n=3$ 时不存在极差小于 $2$ 的构造方案，因此输出一组极差为 $2$ 的构造符合题意。另外，`1 3 2`，`3 2 1` 等也符合条件。

#### 数据范围

$3\le n\le 5\times 10^6$。

## 样例 #1

### 输入

```
3```

### 输出

```
1 2 3```

# 题解

## 作者：cosf (赞：3)

## UBC002F

先说结论：极差最大只有 $3$。具体证明较为复杂，放在最后。这里先放一个计算机验证的[链接](https://www.luogu.com.cn/problem/U508179)，代码在题面里，保证在数据范围内有解。

令 $\Delta$ 表示极差，$v$ 表示序列中出现的最小数，$a, b, c, d$ 分别表示 $v, (v + 1), (v + 2), (v + 3)$ 的出现次数，令 $\text{sum}$ 表示 $\sum_{i=1}^na_i$。

由于太多根号了码起来麻烦，为了简写，$(x)_1 = \sqrt[3]{x}, (x)_2 = \sqrt{x}, (x)_3 = \sqrt{x^2}$。$\text{R}(x)$ 表示值 $x$ 的值域。

下面的方法给出了如何构造一组解。

### $\Delta \le 1$

当 $\Delta = 0$ 时，$a = n, \text{lcm} = v, \text{sum} = nv$，所以 $n = 1$，舍。

当 $\Delta = 1$ 时，$a, b \ge 1$，显然 $\text{lcm} = v(v + 1)$，有：
$$
\begin{cases}
a + b = n & (1)\\
av + b(v + 1) = v(v + 1) & (2)
\end{cases}
$$
$(2) \bmod v$ 得到 $b \equiv 0 \pmod v$。又 $b(v + 1) \in (0, v(v + 1))$，因此 $b \in [1, v - 1]$，无解。

### $\Delta = 2$

如果 $b = 0$，类似 $\Delta = 1$ 的情况，无解。

因此 $a, b, c \ge 1$。此时要分两类讨论。

#### 1) $v \equiv 0 \pmod 2$

此时 $\text{lcm} = v \times \frac{(v + 1)(v + 2)}{2}$。考虑方程：
$$
\begin{cases}
a + b + c = n & (3)\\
av + b(v + 1) + c(v + 2) = v \times \frac{(v + 1)(v + 2)}{2} & (4)
\end{cases}
$$
$(4) - (3) \times v$ 得到：
$$
b + 2c = v(\frac{(v + 1)(v + 2)}{2} - n) = f_1(v)\\
$$
由 $(3)$ 易得 $\text{R}(b + 2c) \sub [3, 2n - 1]$。代入计算，有 $f_1((2n)_2 - 2) \lt 3 \lt 2n - 1 \lt f_1((2n)_2)$，因此 $v \in ((2n)_2 - 2, (2n)_2)$。

#### 2) $v \equiv 1 \pmod 2$

此时 $\text{lcm} = v \times (v + 1) \times (v + 2)$。方程化简之后有：
$$
b + 2c = v((v + 1)(v + 2) - n) = f_2(v)
$$
由 $\text{R}(b + 2c) \sub [3, 2n - 1]$ 且 $f_1((n)_2 - 2) \lt 3 \lt 2n - 1 \lt f_1((n)_2)$，得 $v \in ((n)_2 - 2, (n)_2)$。

可以观察到，这两个区间都很小（其中的整点数 $\le 2$），因此分别带入求解即可。接下来的分讨过程类似，所以就只保留结果了。并且，可以发现，如果 $\text{lcm}$ 的系数是 $\frac{1}{k}$，则根号 $n$ 前的系数就是 $k$。这点可以加快求出范围的过程。

### $\Delta = 3$

#### 仅有 $v, (v + 1), (v + 3)$

此时 $\text{lcm}$ 有四种可能。
$$
\begin{aligned}
v \equiv 3 \pmod 6 &\implies v \in ((6n)_2 - 2, (6n)_2)\\
v \equiv 0 \pmod 6 &\implies v \in ((3n)_2 - 2, (3n)_2)\\
v \equiv 1, 5 \pmod 6 &\implies v \in ((2n)_2 - 2, (2n)_2)\\
v \equiv 2, 4 \pmod 6 &\implies v \in ((n)_2 - 2, (n)_2)\\
\end{aligned}
$$

#### 仅有 $v, (v + 2), (v + 3)$

此时 $\text{lcm}$ 有四种可能。
$$
\begin{aligned}
v \equiv 0 \pmod 6 &\implies v \in ((6n)_2 - 2, (6n)_2)\\
v \equiv 3 \pmod 6 &\implies v \in ((3n)_2 - 2, (3n)_2)\\
v \equiv 2, 4 \pmod 6 &\implies v \in ((2n)_2 - 2, (2n)_2)\\
v \equiv 1, 5 \pmod 6 &\implies v \in ((n)_2 - 2, (n)_2)\\
\end{aligned}
$$

#### 四个数均有

> 注：后面发现，前面几种已经完全够了，即不需要这种情况。std 与后面的证明均不会提到此情况。

这个时候就不是 $(kn)_2$ 了，而是 $(kn)_3$。带入就能发现式子从一个二次的变成了一个三次的。

$\text{lcm}$ 有两种可能的值：$\frac{v(v + 1)(v + 2)(v + 3)}{2}$ 与 $\frac{v(v + 1)(v + 2)(v + 3)}{6}$。
$$
\begin{aligned}
v \equiv 0 \pmod 3 &\implies v \in ((6n)_1 - 2, (6n)_1)\\
v \equiv 1, 2\pmod 3 &\implies v \in ((2n)_1 - 2, (2n)_1)\\
\end{aligned}
$$

---

至此，一共分了十四类。不过，去掉 $\Delta \le 1$ 之后，本质不同的 $v$ 的取值只有 $6$ 种，分别带入即可。求根可以用 `<cmath>` 库之类的来实现。大常数是乘给 $O(1)$ 计算的，并不会影响 $O(n)$ 的输出答案。另外，由于 $v$ 是根号级别，所以 $v$ 的和在 $10^{10}$ 量级左右，离 $10^{12}$ 很远。

下面是 DerrickLo 实现的 std。

```cpp
#include<bits/stdc++.h>
#define lcm(a,b) ((a)*(b)/__gcd(a,b))
#define int long long
using namespace std;
int n;
vector<int>v2,v3;
int a1(int x){return cbrt(x);}
int a2(int x){return sqrt(x);}
int a3(int x){return cbrt(x*x);}
array<int,3> check3(int a,int b,int c,int p){
	//x+y+z=n,ax+by+cz=p
	int x=p-a*n;
	if(x<0)return{-1,-1,-1};
	if(b==a+1){
		int cc=x/(c-a);
		int bb=x%(c-a);
		if(cc==0)return {-1,-1,-1};
		if(bb==0){
			if(cc<=1)return {-1,-1,-1};
			cc--,bb+=c-a;
		}
		if(bb+cc<n)return {n-bb-cc,bb,cc};
		return{-1,-1,-1};
	}
	if(x<5)return {-1,-1,-1};
	int cc=x/3;
	if(x%3==0)cc--;
	if((x-3*cc)&1){
		if(cc==0)return{-1,-1};
		cc--;
	}
	int bb=(x-3*cc)/2;
	if(bb+cc<n)return {n-bb-cc,bb,cc};
	return {-1,-1,-1};
}
array<int,4> check4(int a,int b,int c,int d,int p){
	//x+y+z+w=n,ax+by+cz+dw=p
	int x=p-n*a;
	if(x<6)return {-1,-1,-1,-1};
	int dd=x/3-1,cc,bb;
	if(x-dd*3==3)bb=cc=1;
	if(x-dd*3==4)bb=1,cc=2;
	if(x-dd*3==5)bb=2,cc=1;
	if(bb+cc+dd<n)return {n-bb-cc-dd,bb,cc,dd};
	return {-1,-1,-1,-1};
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=a2(2*n)-2;i<=a2(2*n);i++)if(i>0)v2.emplace_back(i);
	for(int i=a2(1*n)-2;i<=a2(1*n);i++)if(i>0)v2.emplace_back(i);
	for(int i=a2(6*n)-2;i<=a2(6*n);i++)if(i>0)v3.emplace_back(i);
	for(int i=a2(3*n)-2;i<=a2(3*n);i++)if(i>0)v3.emplace_back(i);
	for(int i=a2(2*n)-2;i<=a2(2*n);i++)if(i>0)v3.emplace_back(i);
	for(int i=a2(1*n)-2;i<=a2(1*n);i++)if(i>0)v3.emplace_back(i);
	for(int v:v2){
		auto now=check3(v,v+1,v+2,lcm(lcm(v,v+1),v+2));
		if(now[0]!=-1){
			for(int j=1;j<=now[0];j++)cout<<v+0<<"\t";
			for(int j=1;j<=now[1];j++)cout<<v+1<<"\t";
			for(int j=1;j<=now[2];j++)cout<<v+2<<" \n"[j==now[2]];
			return 0;
		}
	}
	for(int v:v3){
		auto now=check3(v,v+1,v+3,lcm(lcm(v,v+1),v+3));
		if(now[0]!=-1){
			for(int j=1;j<=now[0];j++)cout<<v+0<<" ";
			for(int j=1;j<=now[1];j++)cout<<v+1<<" ";
			for(int j=1;j<=now[2];j++)cout<<v+3<<" \n"[j==now[2]];
			return 0;
		}
		now=check3(v,v+2,v+3,lcm(lcm(v,v+2),v+3));
		if(now[0]!=-1){
			for(int j=1;j<=now[0];j++)cout<<v+0<<" ";
			for(int j=1;j<=now[1];j++)cout<<v+2<<" ";
			for(int j=1;j<=now[2];j++)cout<<v+3<<" \n"[j==now[2]];
			return 0;
		}
		auto noww=check4(v,v+1,v+2,v+3,lcm(lcm(lcm(v,v+1),v+2),v+3));
		if(noww[0]!=-1){
			for(int j=1;j<=noww[0];j++)cout<<v+0<<" ";
			for(int j=1;j<=noww[1];j++)cout<<v+1<<" ";
			for(int j=1;j<=noww[2];j++)cout<<v+2<<" ";
			for(int j=1;j<=noww[3];j++)cout<<v+3<<" \n"[j==now[2]];
			return 0;
		}
	}
	assert(0);
}
```

---

下面来一个证明。

我们需要证明所有的 $n$ 都存在一个 $v$，可以对于所有的 $v$，反推出对应 $n$ 的范围，只需看它们的并是不是 $\N \cup [3, +\infty)$ 即可。

在 $n \le 56$ 时可自行验证成立。下证 $n \ge 57$ 的情况。下面的所有 $k$ 均属于 $\N^+$。

分六类讨论，即 $v$ 模 $6$ 的余数。

#### 1) $v = 6k$

#### $\Delta = 2$

此时有 $v(\frac{(v + 1)(v + 2)}{2} - n) \in [3, 2n - 1]$。

由 $6k((6k + 1)(3k + 1) - n) \ge 3$ 得：$108k^3 + 54k^2 + 6k - 3 \ge 6kn$，保守估计，得 $n \le 18k^2 + 9k$。

由 $6k((6k + 1)(3k + 1) - n) \le 2n - 1$ 得：$108k^3 + 54k^2 + 6k + 1 \le (6k + 2)n$，保守估计，得 $n \ge 18k^2 + 3k + 1$。

因此 $n \in [18k^2 + 3k + 1, 18k^2 + 9k]$。

#### 仅有 $v, (v + 1), (v + 3)$

此时有 $v(\frac{(v + 1)(v + 3)}{3} - n) \in [4, 3n - 7] \cup \{3n - 5\}$，将 $3n - 5$ 忽略。

由 $6k((6k + 1)(2k + 1) - n) \ge 4$ 得：$72k^3 + 48k^2 + 6k - 4 \ge 6kn$，有 $n \le 12k^2 + 8k$。

由 $6k((6k + 1)(2k + 1) - n) \le 3n - 7$ 得：$72k^3 + 48k^2 + 6k + 7 \le (6k + 3)n$，有 $n \ge 12k^2 + 2k + 1$。因此 $n \in [12k^2 + 2k + 1, 12k^2 + 8k]$。

#### 仅有 $v, (v + 2), (v + 3)$

此时有 $v(\frac{(v + 2)(v + 3)}{6} - n) \in \{5\} \cup [7, 3n - 4]$。将 $5$ 忽略。

则有：$n \in [6k^2 + 2k + 1, 6k^2 + 5k]$。

### 2) $v = 6k + 1$

$\Delta = 2$ 时 $n \in [36k^2 + 18k + 3, 36k^2 + 30k + 5]$。

不选 $(v + 2)$ 时 $n \in [18k^2 + 9k + 2, 18k^2 + 18k + 3]$。

不选 $(v + 1)$ 时 $n \in [36k^2 + 24k + 4, 36k^2 + 42k + 11]$。

### 3) $v = 6k + 2$

$\Delta = 2$ 时 $n \in [18k^2 + 15k + 4, 18k^2 + 21k + 5]$。

不选 $(v + 2)$ 时 $n \in [36k^2 + 30k + 7, 36k^2 + 48k + 14]$。

不选 $(v + 1)$ 时 $n \in [18k^2 + 18k + 5, 18k^2 + 27k + 14]$。

### 4) $v = 6k + 3$

$\Delta = 2$ 时 $n \in [36k^2 + 42k + 13, 36k^2 + 54k + 19]$。

不选 $(v + 2)$ 时 $n \in [6k^2 + 7k + 3, 6k^2 + 10k + 3]$。

不选 $(v + 1)$ 时 $n \in [12k^2 + 16k + 6, 12k^2 + 22k + 10]$。

### 5) $v = 6k + 4$

$\Delta = 2$ 时 $n \in [18k^2 + 27k + 11, 18k^2 + 33k + 14]$。

不选 $(v + 2)$ 时 $n \in [36k^2 + 54k + 21, 36k^2 + 72k + 82]$。

不选 $(v + 1)$ 时 $n \in [18k^2 + 30k + 13, 18k^2 + 39k + 20]$。

### 6) $v = 6k + 5$

$\Delta = 2$ 时 $n \in [36k^2 + 66k + 31, 36k^2 + 78k + 41]$。

不选 $(v + 2)$ 时 $n \in [18k^2 + 33k + 16, 18k^2 + 42k + 23]$。

不选 $(v + 1)$ 时 $n \in [36k^2 + 72k + 36, 36k^2 + 90k + 55]$。

至此，所有类别均讨论完成。

将所有 $36k^2$ 项并起来：$[36k^2 + 18k + 3, 36k^2 + 90k + 55]$。循环下来，缺了一个 $36k^2 + 90k + 56$。

将所有 $18k^2$ 项并起来：$[18k^2 + 3k + 1, 18k^2 + 9k] \cup [18k^2 + 9k + 2, 18k^2 + 42k + 23]$。循环缺 $18k^2 + 9k + 1$。

观察缺的项，$36k^2$ 缺的数模 $9$ 余 $2$，而 $18k^2$ 缺的数模 $9$ 余 $1$，所以它们不会相等。因此，所有数都可以在 $\Delta \le 3$ 的情况下表示出来！

证毕。

---

