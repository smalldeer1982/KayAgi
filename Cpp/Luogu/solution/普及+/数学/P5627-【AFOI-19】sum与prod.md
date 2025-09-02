# 【AFOI-19】sum与prod

## 题目背景

SY终于整理好了她凌乱的被子，刚来到教室的她就收到了QM传来的一张字条。。。

To: Dear SY

&nbsp;&nbsp;&nbsp;&nbsp;你看看我昨晚梦到的式子，解出来给你糖吃。

From: Your QM。

SY自然是无法拒绝 $C_{6}H_{12}O_{6}$ 的诱惑啦，不过她看到字条背面花里胡哨的式子时傻眼了。。但是SY还是很想吃糖。

## 题目描述

求

$$\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j = 1}^{i}lowbit(j))}$$

的结果

其中 $lowbit(x)$ 意指` x&(~x+1)` 的结果。

## 说明/提示

对于前 $20\%$ 的数据，有 $1 \leq n \leq 60$ 。

对于前 $50\%$ 的数据，有 $1 \leq n \leq 10^4$ 。

对于前 $100\%$ 的数据，有 $1 \leq n \leq 2^{62}$ 。

## 样例 #1

### 输入

```
2
```

### 输出

```
5```

## 样例 #2

### 输入

```
5
```

### 输出

```
447```

# 题解

## 作者：WYXkk (赞：8)

[也许更好的阅读体验](https://www.luogu.com.cn/blog/WYXkk/solution-p5627)

------------

> 题意：求
> $$\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j=1}^{i}\operatorname{lb}(j))}$$

~~众所周知，看到这种输入少的题，我们应该找规律。~~

找个锤子规律，直接猛男推式子。

$$\begin{aligned}\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j=1}^{i}\operatorname{lb}(j))}&=\sum_{i=1}^{2^{n}}\sum_{j=1}^{i}\log_{2}{(\operatorname{lb}(j))}\\&=\sum_{j=1}^{2^{n}}\sum_{i=j}^{2^n}\log_{2}{(\operatorname{lb}(j))}\\&=\sum_{j=1}^{2^{n}}(2^n-j+1)\log_{2}{(\operatorname{lb}(j))}\\&=n+\sum_{j=1}^{2^{n}-1}(2^n-j+1)\log_{2}{(\operatorname{lb}(j))}\\&=n+\sum_{k=0}^{n-1}k\sum_{i=1}^{2^{n-k-1}}(2^n-(2i-1)2^k+1)\\&=n+\sum_{k=0}^{n-1}k(1+2^{n-1})2^{n-k-1}\\&=n+(1+2^{n-1})\sum_{k=0}^{n-1}k2^{n-k-1}\end{aligned}$$

而我们又有

$$\begin{aligned}\sum_{k=0}^{n-1}k2^{n-k-1}&=\sum_{k=1}^{n-1}k2^{n-k-1}\\&=\sum_{k=1}^{n-1}\sum_{j=1}^k2^{n-k-1}\\&=\sum_{j=1}^{n-1}\sum_{k=j}^{n-1}2^{n-k-1}\\&=\sum_{j=1}^{n-1}(2^{n-j}-1)\\&=2^n-2-(n-1)\\&=2^n-n-1\end{aligned}$$

因此

$$\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j=1}^{i}\operatorname{lb}(j))}=n+(1+2^{n-1})(2^n-n-1)$$

直接带入计算即可，使用快速幂可以 $O(\log n)$。代码就不贴了。

（题外话：$n$ 开到 $10^{10^6}$ 也没问题，快读取双模（$p,p-1$）即可）

---

## 作者：Scarlet_Hypoc (赞：7)

应该就我用这么沙雕的做法了吧qwq

在[这里](https://blog.csdn.net/a_forever_dream/article/details/102963750)食用更佳。

我们先考虑求后面的那一串 $\prod_{j=1}^i lowbit(j)$。

既然有 $lowbit$，那么肯定会想到树状数组嘛，那么我们考虑找找规律什么的，先摆一个树状数组出来：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20191108075001843.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2FfZm9yZXZlcl9kcmVhbQ==,size_16,color_FFFFFF,t_70)
我们惊奇地发现，对于一个 $lowbit$ 为 $2^x$ 的点，他管理的区间的所有点的 $lowbit$ 的积恰好就是 $2^{2^x-1}$。比如说绿色点，它的 $lowbit$ 是 $2^2$，然后他管理的区间的 $lowbit$ 之积就是 $2^3$。

然后会发现，这个证明其实也很简单，我们设 $f_i$ 表示 $lowbit$ 为 $2^i$ 的节点管理区间内的 $lowbit$ 之积。那么可以得到 $f_i=2f_{i-1}^2$，以上图中绿色节点往蓝色节点转移为例，会发现其实绿色节点管理的 $1$ ~ $3$ 区间和蓝色节点管理的 $5$ ~ $7$ 区间是一样的，不同的只有蓝色节点比绿色节点的 $lowbit$ 要大一倍，所以蓝色节点管理的区间等价于将绿色节点管理的区间复制一份，然后将复制的一份中的最后一个节点的 $lowbit$ 翻一倍，所以转移就是 $2f_{i-1}^2$。

因为 $f_i$ 必然是一个 $2$ 的幂，我们不妨用 $2^{c_i}$ 来表示它，那么转移方程又可以表示成：$2^{c_i}=2^{c_{i-1}\times2+1}$，因为 $f_0=2^0$，即 $c_0$ 等于 $0$，所以显然有 $c_i=2^i-1$。

所以这个 $\prod_{j=1}^i lowbit(j)$ 我们可以考虑写成像树状数组求前缀和那样的形式：
$$\begin{aligned}\prod_{j=1}^i lowbit(j)&=\prod_{k=0}^p f_k[i~and~2^k>0]\\&=\prod_{k=0}^p 2^{c_i}[i~and~2^k>0]\\&=\prod_{k=0}^p 2^{2^i-1}[i~and~2^k>0]\end{aligned}$$

其中，$and$ 是**与**运算，$p$ 是 $i$ 的二进制下的位数。

带回去原柿子，得到：
$$\begin{aligned}&\sum_{i=1}^{2^n}\log_2(\prod_{k=0}^n 2^{2^i-1}[i~and~2^k>0])\\&=\sum_{i=1}^{2^n}\sum_{k=0}^n 2^i-1[i~and~2^k>0]
\end{aligned}$$

然而，现在还是不怎么可做，内外层两个循环我们半个都枚举不了……

但是里面的循环的上限是 $n$，比较小，我们考虑把它提出来：
$$\sum_{k=0}^n \sum_{i=1}^{2^n}2^i-1[i~and~2^k>0]$$

那么现在就是考虑 $1$ ~ $2^n$ 这些数在每一个二进制位上的贡献。

考虑到在同一位上的贡献其实都是一样的，所以我们只需要考虑每一位上有多少个数不为 $0$。

依然考虑推柿子：设 $f(i)$ 表示区间 $1$ ~ $2^i-1$ 中所有数的贡献和。

那么 $f(i)$ 转移到 $f(i+1)$，相当于多了 $2^i$ ~ $2^{i+1}-1$ 这些数，然而我们发现一个奇妙的规律：$2^i+1$ ~ $2^{i+1}-1$ 这些数相当于 $1$ ~ $2^i-1$ 这些数每个数加上 $2^i$。所以这些数的贡献等于 $f(i)+(2^{i+1}-1-2^i-1+1)\times (2^i-1)=f(i)+(2^i-1)^2$。

最后把 $2^i$ 这个数算上，它的贡献是 $2^i-1$，所以递推式为：
$$\begin{aligned}f(i+1)&=f(i)+f(i)+(2^i-1)^2+2^i-1\\&=2f(i)+(2^i-1)\times 2^i\\&=2f(i)+2^{2i}-2^i\\&=2f(i)+4^i-2^i\\\end{aligned}$$

即：
$$f(i)=2f(i-1)+4^{i-1}-2^{i-1}$$

其中，根据上面的定义，显然有 $f(1)=0$。

所以最后的答案就是 $f(n)+2^n-1$，因为 $f(n)$ 只考虑了 $1$ ~ $2^n-1$ 的贡献，最后还要加上 $2^n$ 的贡献。那么现在已经得到一个 $O(n)$ 的 $50$ 分做法了。

但是我们当然要追求 $100$ 分，所以考虑求这个递推式的通项公式。

接下来的内容可能引起不适，请务必保证你学过[OGF](https://blog.csdn.net/a_forever_dream/article/details/102594411)。

接下来我们考虑用生成函数来求通项公式：设 $F(x)=\sum_{i=1} f(i)x^i$。

因为没有第 $0$ 项比较麻烦，我们考虑将 $F(x)$ 的系数整体左移一位，也就是：$F(x)=\sum_{i=0}f(i+1)x_i$。

整体左移一位之后，$f$ 的递推式变成 $f(i)=2f(i-1)+4^i-2^i$，其中 $f(0)=0$。

那么根据递推式，我们可以得到：
$$\begin{aligned}F&=2Fx+\frac 1 {1-4x}-\frac 1 {1-2x}\\F(1-2x)&=\frac 1 {1-4x}-\frac 1 {1-2x}\\F&=\frac 1 {(1-4x)(1-2x)}-\frac 1 {(1-2x)^2}\\\end{aligned}$$

发现里面的 $\frac 1 {(1-4x)(1-2x)}$ 无法展开，于是考虑**裂项**。

---
设 $\frac A {1-ax}+\frac B {1-bx}=\frac 1 {(1-4x)(1-2x)}$，那么有：
$$\frac {A-bxA+B-axB} {(1-ax)(1-bx)}=\frac 1 {(1-4x)(1-2x)}$$

那么根据这两个柿子的分母，显然有：
$$\begin{cases}a=4\\b=2\end{cases}$$

带入到分子中，有：
$$\begin{aligned}A-2xA+B-4xB&=1\\(A+B)-(2A+4B)x&=1\end{aligned}$$

那么可以列出方程：
$$\begin{cases}A+B=1\\2A+4B=0\end{cases}$$

解得：
$$\begin{cases}A=2\\B=-1\end{cases}$$

---
带回去有：
$$F=\frac 2 {1-4x}-\frac 1 {1-2x}-\frac 1 {(1-2x)^2}$$

大力展开，有：
$$\begin{aligned}&\sum_{i=0} (2\times 4^i-2^i-C_{i+2-1}^{2-1}2^i)x^i\\&=\sum_{i=0} (2\times 4^i-2^i-(i+1)2^i)x^i
\end{aligned}$$

因为我们一开始将系数整体左移了一位，所以我们现在需要的是 $x^{n-1}$ 项的系数而不是 $x^n$ 的系数，所以答案为：
$$2\times 4^{n-1}-2^{n-1}-n2^{n-1}+2^n-1$$

代码如下（需要注意取模）：
```cpp
#include <cstdio>
#include <cstring>
#define mod 1000000007
#define ll long long

ll n;
ll ksm(ll x,ll y)
{
	ll re=1,tot=x;
	while(y)
	{
		if(y&1)re=re*tot%mod;
		tot=tot*tot%mod;
		y>>=1;
	}
	return re;
}

int main()
{
	scanf("%lld",&n);n--;
	printf("%lld",(((2*ksm(4,n)%mod-ksm(2,n)+mod)%mod-(n+1)%mod*ksm(2,n)%mod+mod)%mod+ksm(2,n+1)-1+mod)%mod);
}
```
~~修改前的题解LaTeX元素有点爆炸，辛苦管理大大重新审核了~~

---

## 作者：Warriors_Cat (赞：4)

一道推式子好题，~~找 规 律 t x d y~~

### $Solution:$

记 $L(j)=\log_2 lowbit(j)$，$S_k=\sum_{i=1}^{2^k}\sum_{j=1}^iL(j)$，很明显 $S_n$ 就是答案。

然后我们把 $n=3$ 打表一下：

```cpp
0
0 1
0 1 0
0 1 0 2
0 1 0 2 0
0 1 0 2 0 1
0 1 0 2 0 1 0
0 1 0 2 0 1 0 3
```
然后进行分割：

```cpp
0
0 1
0 1 0
0 1 0 2
-------
0 1 0 2|0
0 1 0 2|0 1
0 1 0 2|0 1 0
0 1 0 2|0 1 0 3
```
首先，左上角的是 $S_2$，右下角的是 $S_2 + 1$，左下角的是 $2^2 \times (2^2 - 1)$。

于是可得：

$$S_n = 2S_{n-1}+1+2^{2n-2}-2^{n-1}$$

这个规律可以用数学归纳法来证。

于是，我们可以再列出以下式子：

$$S_{n-1} = 2S_{n-2} + 1 + 2^{2n - 4} - 2^{n-2}$$

$$S_{n-2} = 2S_{n-3} + 1 + 2^{2n - 6} - 2^{n-3}$$

$$...$$

$$S_2 = 2S_1 + 1 + 2^2 - 2^1$$

然后一个个回带进去，可得：

$$S_n = 2^{n-1} S_1 + 2^{n-1}-1 + \sum_{i=n}^{2n-2 }2^i - (n-1)\times 2^{n-1}$$

又因为 $S_1=1$ 是显然的，所以 $S_n$ 就被我们求出来啦！

$$S_n = 2^{n-1}+2^{n-1}-1+2^{2n-1}-2^n - (n-1)\times 2^{n-1}$$

$$S_n = 2^{2n-1}-(n-1)\times 2^{n-1}-1$$

然后直接套一个快速幂这道题就做完了，时间复杂度为 $O(\log n)$，接近 $O(1)$。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int mod = 1000000007;
inline int fpow(int n, int p){
	n %= mod; int ans = 1, base = n;
	while(p){
		if(p & 1) ans = ans * base % mod;
		base = base * base % mod;
		p >>= 1;
	}
	return ans;
}
int n;
signed main(){
	n = read();
	printf("%lld", ((fpow(2, n + (n - 1)) - (n - 1) % mod * fpow(2, n - 1) % mod + mod) % mod - 1 + mod) % mod);
	return 0;
}
// Ans = 2^{2n - 1} - (n - 1)2^{n - 1} - 1
```


---

## 作者：B_Qu1e7 (赞：3)

心 路 历 程 ~~(并不是题解)~~

## 1：暴力

~~T1好难，不会……啊，怎么T2也这么难~~

打个暴力得了
```cpp
#define P 1000000007
#define R register
#define ll long long
ll N,sum=0;
inline ll log2(R ll x)
{
	ll sum=-1;
	while(x)
	{
		x>>=1;
		++sum;
	}
	return sum;
}
inline ll lowbit(R ll x)
{
	return x&(~x+1);
}
inline ll query(R ll x)
{
	ll mul=1;
	for(R ll i=1;i<=x;++i)
	{
		mul=mul*lowbit(i);
	}
	return log2(mul);
}
int main()
{
	read(N);
	for(R ll i=1;i<=(1<<N);++i)
	{
		sum=sum+query(i);
	}
	write(sum);
	puts("");
}
```

$$ans_i=1,5,23,103,447......$$

？？$OEIS$找不到？？
```cpp
int main()
{
	read(N);
	for(R ll i=1;i<=N;++i)
	{
		printf("query(%lld)=%lld\n",i,query(i));
	}
}
```
```
20
query(1)=0
query(2)=1
query(3)=1
query(4)=3
query(5)=3
query(6)=4
query(7)=4
query(8)=7
query(9)=7
query(10)=8
query(11)=8
query(12)=10
query(13)=10
query(14)=11
query(15)=11
query(16)=15
query(17)=15
query(18)=16
query(19)=16
query(20)=18

--------------------------------
Process exited after 0.5724 seconds with return value 0
请按任意键继续. . .
```
$OEIS...$还是找不……噫？

$$a(0)=0,a(n)=a(floor(n/2))+n$$

$$query(i)=a(i/2)$$

有点意思。

## 2：非正解
```cpp
#define P 1000000007
#define R register
#define ll long long
ll N,sum=0;
inline ll query(R ll x)
{
	return !x?0:(query(x>>1)+x)%P;
}
int main()
{
	read(N);
	for(R ll i=1;i<=(1<<N);++i)
	{
		sum=(sum+query(i>>1))%P;
	}
	write(sum);
}
```
前几个是对的，三十几就TLE了……不行不行
```
12
8366079
--------------------------------
Process exited after 0.6446 seconds with return value 0
请按任意键继续. . .
```
8366...8388608？$2^{23}$
```
13
33505279
--------------------------------
Process exited after 0.8025 seconds with return value 0
请按任意键继续. . .
```
335..33554432=$2^{25}$

有那么点像吧？

$$8388608-8366079=22529$$

$$33554432-33505279=49153$$

$$49153-22529*2=4095$$

4095??$2^{12}-1$

$$\Delta _i=2^{2*i-1}-ans_i$$

$$\Delta _i=2*\Delta _{i-1}+2^{i-1}-1$$

推通项

$$\Delta _i=(i-1)*2^{i-1}+1$$

$$ans_i=2^{2*i-1}-\Delta _i$$

$$ans_i=2^{2*i-1}-(i-1)*2^{i-1}-1$$

等……等等……哇

## 3：正解
```cpp
#define P 1000000007
#define R register
#define ll long long
ll N,sum=0;
inline ll Qpow(R ll a,R ll b)
{
	ll ret=1;
	while(b)
	{
		if(b&1)ret=ret*a%P;
		a=a*a%P;
		b>>=1;
	}
	return ret;
}
int main()
{
	read(N);
	sum=sum=(1ll*(Qpow(2,(N<<1)-1)-1ll*(N-1)%P/*这个%P扣了我50分*/*Qpow(2,N-1)%P-1ll)%P+P)%P;
	write(sum);
	puts("");
}
```
$$ans=2^{2*N-1}-(N-1)*2^{N-1}-1$$

---

## 作者：saxiy (赞：2)

**19/11/13 UPD：修复 LaTeX。**

------------

#### 题目分析：

求：

$$\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j = 1}^{i}lowbit(j))}$$

考虑二进制的特殊性，非常适合倍增，再看数据范围，嗯，一道推式子的题。

- 设 `x&(~x+1)` 返回 $2^m$ ，根据对数运算法则将累乘提出来：

$$\sum_{i=1}^{2^{n}}\sum_{j = 1}^{i}m_j$$

- 先考虑内层 $sum$ :

写出 $m_j$ 前几位（规律由 `|` 号间隔出）

$$\{0|1|0,2|0,1,0,3|0,1,0,2,0,1,0,4|\cdots \}$$

规律很明显，可以得出前 $2^n$ 位的和的递推式：

$$S_{2^n}=2S_{2^{n-1}}+1$$

易得： $S_{2^n}=2^n-1$

更一般地，对于一个正整数 $i$ ，将其二进制分解代入上式再求和可得

$$S_i=i-popcount(i)$$

此处 `popcount` 意为 $i$ 二进制下 `1` 的个数。

- 考虑外层 $sum$：

目前的式子为： $\sum_{i=1}^{2^{n}}i-popcount(i)$

考虑 `popcount` 的规律，同样是写出前几位找规律：

$$\{1,|1|,2,|1|,2,2,3,|1|,2,2,3,2,3,3,4,|1|\dots \}$$

不难看出，对于每个 $2$ 的整数次幂，其左右有神奇的对称性（并不指 值完全对称）。

可得递推式： $T_{2^n}=2(T_{2^{n-1}}-1)+2^{n-1}+1$

易得： $T_{2^n}=n2^{n-1}+1$

- 考虑最后化简

$$\begin{aligned}ans &= \sum_{i=1}^{2^{n}}i -\sum_{i=1}^{2^{n}}popcount(i)\\&=\frac{2^n(2^n+1)}{2}-n2^{n-1}-1\\&=(2^{n}-n+1)2^{n-1}-1\end{aligned}$$

然后套快速幂的板子就行了，注意减法取模 ~~（乐多赛真好）~~ 。

#### 代码实现：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007LL;

ll qpow(ll a, ll b) {
	ll res = 1;
	while(b) {
		if(b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

int main() {
	register ll n;
	scanf("%lld", &n);
	register ll ans = qpow(2, n);
	//注意下面可能取模后ans<n，减出负数（不考虑得50pts）。
	ans = (((ans - n + 1) % mod) + mod) % mod;
	ans = (ans * qpow(2, n - 1)) % mod;
	printf("%lld", ans - 1);
	return 0;
}
```

---

## 作者：Demeanor_Roy (赞：1)

- [原题链接](https://www.luogu.com.cn/problem/P5627)

- 这种题写了两小时，感觉离退役不远了。

------------

推式子。

$$\sum_{i=1}^{2^{n}}\log_{2}{(\prod_{j = 1}^{i}lowbit(j))}$$

$$=\sum_{i=1}^{2^n}\sum_{j=1}^{i}\log_2 (lowbit(j))$$

$$=\sum_{i=1}^{2^n}(2^n-i+1)\log_2 (lowbit(i))$$

$$=(2^n+1)\sum_{i=1}^{2^n}\log_2 (lowbit(i))-\sum_{i=1}^{2^n}i\log_2 (lowbit(i))$$

令 $f(x)=\log_2 (lowbit(x)),g(x)=i\log_2 (lowbit(x))$。

把 $2^n$ 单独考虑，剩下的就是 $n$ 个二进制位随便填的 $f$ 和与 $g$ 和。

枚举最低位 $1$ 的位置 $i$，那 $f$ 就是 $i2^{n-i-1}$，$g$ 则是 $i2^i(\frac{(2^{n-i-1}-1)2^{n-i-1}}{2} \times 2+2^{n-i-1})$。

对 $i \in [0,n-1]$ 求和，则有答案为：

$$(2^n+1)(n+\sum_{i=0}^{n-1}i2^{n-i-1})-(n2^n-\sum_{i=0}^{n-1}i2^{2n-i-2})$$

$$=n+(2^{n-1}+1)((n-1)(2^n-1)-(n-2)2^n-2)$$

倒数第二步到最后一步的化简是平凡的，其中有用到类似 $\sum_{i=0}^{x}i2^i = (x-1)2^{x+1}+2$ 等套路化的式子。

于是整道题解决完毕，时间复杂度 $O(\log n)$。


---

## 作者：jijidawang (赞：1)

有趣题 .

首先这个 $\log$ 可以丢到里面去吧
$$\sum_{i=1}^{2^n}\sum_{j=1}^i\log_2(\operatorname{lowbit}(j))$$
然后这个 $\log_2(\operatorname{lowbit}(j))$ 其实就是 $j$ 二进制中末尾 $0$ 的个数，这个可以通过 $\operatorname{lowbit}$ 的定义轻易得到 .

令 $\operatorname{ctz}(x)=\log_2(\operatorname{lowbit}(x))$，于是可以得到
$$\begin{aligned}ans&=\sum_{i=1}^{2^n}\sum_{j=1}^i\operatorname{ctz}(j)\\&=\sum_{j=1}^{2^n}\sum_{i=j}^{2^n}\operatorname{ctz}(j)\\&=\sum_{j=1}^{2^n}\operatorname{ctz}(j)\cdot(2^n-j+1)\\&=(2^n+1)\sum_{i=1}^{2^n}\operatorname{ctz}(i)+\sum_{i=1}^{2^n}i\operatorname{ctz}(i)\end{aligned}$$

然后问题就变成了两个子问题：
- Task 1. $\operatorname{ctz}(i)$ 的前缀和 .
- Task 2. $i\operatorname{ctz}(i)$ 的前缀和 .

考虑这个 $\operatorname{ctz}$ 的贡献 .

根据定义可得 $[\operatorname{ctz}(x)=y]=[(x\mid2^y)\land (x\nmid 2^{y+1})]=[x\mid 2^y]\cdot[x\nmid 2^{y+1}]$ .

你也可以通过构造一个树状数组来得到这个形式 .

然后也就是 $\operatorname{ctz}(x)=y$ 当且仅当 $x$ 是 $2^y$ 的奇数倍（此处是关键结论） .
***
**Task 1.**

因为 $\sum$ 的上界是 $2^n$，可以直接考虑算贡献：
$$\begin{aligned}\sum_{i=1}^{2^n}\operatorname{ctz}(i)&=n+\sum_{i=1}^{2^n-1}\operatorname{ctz}(i)\\&=n+\sum_{i=0}^{n-1}i\cdot2^{n-i-1}\\&=n+2^n-n-1\\&=2^n-1\end{aligned}$$

然后因为这个可以得到直接推论（考虑二进制分解可得）：
$$\sum_{i=1}^n\operatorname{ctz}(i)=n-\operatorname{popcount}(n)$$
其中 $\operatorname{popcount}(n)$ 是 $n$ 的二进制中 $1$ 的个数 .

**Task 2.**

一个 [常见的 Trick](https://loj.ac/d/2514) :

$$\begin{aligned}\sum_{i=1}^{2^n}i\operatorname{ctz}(i)&=\sum_{i=1}^{2^n}(2^n-(2^n-i))\operatorname{ctz}(i)\\&=\sum_{i=1}^{2^n}2^n\operatorname{ctz}(i)-\sum_{i=1}^{2^n}(2^n-i)\operatorname{ctz}(i)\\&=2^n\sum_{i=1}^{2^n}\operatorname{ctz}(i)-\sum_{i=1}^{2^n}\sum_{j=1}^{i}\operatorname{ctz}(j)\\&=2^n\cdot(2^n-1)-\sum_{i=1}^{2^n}(i-\operatorname{popcount}(i))\\&=2^n(2^n-1)-\dfrac122^n(2^n-1)+\sum_{i=1}^{2^n}\operatorname{popcount}(i)\\&=2^{n-1}(2^n-1)+\sum_{i=1}^{2^n}\operatorname{popcount}(i)\end{aligned}$$

现在我们的问题就变成处理 $\displaystyle\sum_{i=1}^{2^n}\operatorname{popcount}(i)$ .

因为 $\sum$ 的上界是 $2^n$，可以直接考虑直接算贡献：
$$\begin{aligned}\sum_{i=1}^{2^n}\operatorname{popcount}(i)&=\sum_{i=0}^ni\dbinom ni\\&=n2^{n-1}\end{aligned}$$
后面是经典组合恒等式 .

然后带回去，就可以得到 $\displaystyle \sum_{i=1}^{2^n}i\operatorname{ctz}(i)=2^{n-1}(2^n+n-1)$ .
***
做完了 .

把两个 Task 合起来，回到我们最初的问题 .

$$\begin{aligned}ans&=(2^n+1)\sum_{i=1}^{2^n}\operatorname{ctz}(i)+\sum_{i=1}^{2^n}i\operatorname{ctz}(i)\\&=(2^n+1)(2^n-1)-2^{n-1}(2^n+n-1)\end{aligned}$$

~~化简是不可能化的，这辈子也不可能化的~~

快速幂，$O(\log n)$ .

因为 $n$ 非常的大，我们对指数用费马小定理取模 $10^9+6$ 即可 .

注意 $n$ 有的在指数上有的在底下，不要直接取模了 .

实际实现的时候其实只需要一次快速幂 .

Record ID : [73251352](https://www.luogu.com.cn/record/73251352) .

---

## 作者：uid_310801 (赞：1)

### （伪）矩阵快速幂做法

没看到用矩阵快速幂的，就来发一弹吧（~~其实不需要，就是刚学了，没地方发力~~）！

首先尝试化简一下柿子：

$$\sum\limits^{2^n}_{i=1}\log_2(\prod\limits^i_{j=1}\operatorname{lowbit}(j))$$

$$=\sum\limits^{2^n}_{i=1}\sum\limits^{i}_{j=1}\log_2(\operatorname{lowbit}(j))$$

$$=\sum\limits^{2^n}_{i=1}\log_2(\operatorname{lowbit}(i))×(2^n-i+1)$$

~~然后我就止步于此了~~。

然后我就开始找规律：

0. 定义
$F_i=\log_2(\operatorname{lowbit}(i))$  
$sum_i=\sum\limits^{i}_{j=1}F_j$  
$a_i=\sum\limits^{i}_{j=1}sum_j$   
$ans_i=a_{2^i}$

1. 这里的 $F_i$ 其实就是看 $i$ 的二进制表示，末尾有几个 $0$；

2. 对于 $i\in[1,16]$ 枚举他们的函数值，不难发现对于前 $2^n$ 个数来说，前  $2^{n-1}$ 个数的值基本上与后 $2^{n-1}$ 个数的值一一对应，只是 $2^n$ 比 $ 2^{n-1}$ 的值多了 $1$ 而已；

3. 当存在 $k$ 使得 $i=2^k$ 时，$sum_i=i-1$。

4. $ans_n$ 即为所求。

![](https://cdn.luogu.com.cn/upload/image_hosting/5pkzmf9q.png)

考虑递推，如何从 $ans_{n-1}$ 转移到 $ans_n$？受到规律 2 的启发，我们观察 $i\in[9,15]$ 时的 $sum$ 值，可以看出：

$$sum_{i,i\in[9~15]}=sum_{i-8}+8-1$$
$$sum_{16}=8×2-1=16-1=15$$

则有：

$$ans_n=ans_{n-1}+(ans_{n-1}+2^{n-1}×sum_{2^{n-1}})+1$$

$$=ans_{n-1}×2+2^{n-1}×(2^{n-1}-1)+1$$

$$=ans_{n-1}×2+2^{2n-2}-2^{n-1}+1$$

好耶！递推式就这样被我们稀里糊涂地~~求~~蒙出来了。

最后，我们不会推公式了。但是，可以用矩阵加速！

构建答案矩阵分别存储 $\{1,2^{n-1},2^{2n-2},ans_n\}$ 即可。

转移矩阵则为：

$\begin{Bmatrix}
1&0&0&1\\
0&2&0&-1\\
0&0&4&1\\
0&0&0&2
\end{Bmatrix}
$
 	
放上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod=1e9+7;
struct matrix{
	ll k[4][4];
	matrix(){
		memset(k,0,sizeof(k));
	}
}a,d;
matrix operator * (const matrix a,const matrix b){
	matrix c;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int l=0;l<4;l++)
				c.k[i][j]=(c.k[i][j]+a.k[i][l]*b.k[l][j])%Mod;
	return c;
}
matrix qpow(matrix a,ll p){
	matrix c;
	for(int i=0;i<4;i++)	c.k[i][i]=1;
	while(p){
		if(p%2==1)	c=c*a;
		a=a*a;
		p>>=1;
	}
	return c;
}
signed main(){
	ll n,t;
	scanf("%lld",&n);
	d.k[0][0]=d.k[2][3]=d.k[0][3]=1,d.k[1][1]=d.k[3][3]=2,d.k[2][2]=4,d.k[1][3]=-1;
	a.k[0][0]=1,a.k[0][1]=2,a.k[0][3]=1;a.k[0][2]=4;
	matrix c=(a*qpow(d,n-1));
	printf("%lld\n",c.k[0][3]);
}
```
蒟蒻文笔不好，大佬轻喷！

---

update：提交题解1分钟后，发现标点符号没弄好重新交了一遍，麻烦管理员大大了。

---

## 作者：Aw顿顿 (赞：1)

## 题意

给定 $n$，求：

$$\sum\limits_{i=1}^{2^{n}}\log_{2}{(\prod\limits_{j = 1}^{i}\text{lowbit}(j))}$$


## $\mathsf{Sol.1}$ 找规律

写了个 `gen` 想要去 `oeis.org` 上面去找规律，结果非自然溢出了……

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int lowbit(int x){
	return x&(~x+1);
}signed main(){
	int n=1;
	while(n++&&n<=10){
		int ans=1,sum=0;
		for(int i=1;i<=(1<<n);i++){
			for(int j=1;j<=i;j++){
				ans*=lowbit(j);
			}sum+=log(ans); 
		}cout<<sum<<",";
	}
}
```

不想写高精，于是去写 `python3` 的代码，但是发现 `lowbit()` 不会实现，导致这个方法彻底破产。

听说数形结合还是分割啥的可以……好像单独看 prod 那部分也还行，但是没想到，也不打算想了（

## $\mathsf{Sol.2}$ 推式子

这么好玩的题目当然一通乱搞推式子啦。

**注释：在接下来的说明中，以下函数替代为**

- $\rm lowbit(x)\to l(x)$
- $\rm log_2(x)\to log(x)$

第一步，把 $\Pi$ 变成 $\Sigma$ 就行：

$$\sum_{i=1}^{2^{n}}\log{(\prod_{j=1}^{i}\text{l}(j))}=\sum_{i=1}^{2^{n}}\sum_{j=1}^{i}\log{(\text{l}(j))}$$


考虑这样一个情况：

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i}(i+j)=\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}(i+j)$$

那么我们进一步化简就简单了很多，把两个式子互换位置并且用 $n$ 去限制 $j$ 的范围：

$$\sum\limits_{i=1}^{2^{n}}\sum_{j=i}^{2^{n}}\log{(\text{l}(j))}$$

考虑其贡献 $j\sim 2^{n}$ 的过程，每次是 $2^{n}-j+1$，于是可以直接当做一个系数来处理：

$$\sum\limits_{i=1}^{2^{n}}(2^{n}-j+1)\log{(\text{l}(j))}$$

那么我们接下来要尝试令“限制”和这个系数尽可能的类似，那么我们就可以做：

$$n+\sum\limits_{i=1}^{2^{n}-1}(2^{n}-j+1)\log{(\text{l}(j))}$$

接着类似的变换可以做到相同的效果。

那么接下来的任务就是将其中的 $\log$ 和 $\rm lowbit$ 给替换掉。

然后把新的求和加入，就可以得出这个式子：

$$n+\sum\limits_{j=0}^{n-1}j\sum\limits_{i=1}^{2^{n-j-1}}\left(2^n-2^{j+1}\times i+2^j+1\right)$$

接着把内容物提取：

$$n+(1+2^{n-1})\sum\limits_{j=0}^{n-1}2^{n-j-1}\times j$$

那我们把已经求出来的系数部分先抛去，只留下求和式子，故技重施，再加一层循环即可：

有

$$\sum\limits_{i=1}^{n-1}\sum_{j=1}^i 2^{n-j-1}$$


于是可以把循环顺序再次调换：


$$\sum\limits_{j=1}^{n-1}\sum_{i=j}^{n-1}2^{n-j-1}$$

诶我们发现后半部分有利可图，那么展开并化简：

$$\sum\limits_{j=1}^{n-1}(2^{n-j}-1)$$


结论就是：

$$2^n-n-1$$

结合已经求出来的部分：

$$\text{Ans}=n+(1+2^{n-1})(2^n-n-1)$$

那么快速幂就可以 $O(\log n)$ 的复杂度实现了。

如果不用大 $O$ 计数法来表示，运算的等级大概是 $\log(n)+\log(n-1)+c$ 这样子，那么就 $2\log n$ 了。

代码实现不难，赞一个吧。


---

## 作者：HoshizoraZ (赞：1)

~~应该就我一个人这么暴力算的吧……~~

　　首先：

$$\sum_{i=1}^{2^n}\log_2(\prod_{j=1}^{i}lowbit(j))$$
$$=\sum_{i=1}^{2^n}\sum_{j=1}^{i}\log_2(lowbit(j))$$

　　继续观察，可以发现 $\log_2(lowbit(x))$ 就是 $x$ 分解质因子后质因子 $2$ 的指数。
  
　　这就相当于，对于每个 $i$，求 $1$ 至 $i$ 中二的倍数个数、四的倍数，……，$2^{\lfloor \log_2i\rfloor}$ 的倍数个数之和。

　　所以，可以化成

$$=\sum^{2^n}_{i=1}\sum^{\log_2i}_{j=1}\lfloor \frac{i}{2^j}\rfloor$$

$$=\sum^{2^n}_{i=1}\sum^{\log_2{2^n}}_{j=1}\lfloor \frac{i}{2^j}\rfloor$$

$$=\sum^{n}_{i=1}\sum_{j=1}^{2^n}\lfloor \frac{j}{2^i}\rfloor$$

　　然后，尝试发现一些性质：

　　根据下取整的性质，可以得到

$$=\sum_{i=1}^n\sum_{j=0}^{2^{n-i}-1}(j \cdot 2^i)+\sum_{i=1}^{n}2^{i-1}$$
$$=\sum_{i=1}^n 2^i\cdot \sum_{j=0}^{2^{n-i}-1}j+\sum_{i=1}^{n}2^{i-1}$$

　　利用等差数列求和公式：

$$=\sum_{i=1}^n 2^i \cdot\frac{(2^{n-i}-1) \cdot (2^{n-i})}{2}+\sum_{i=1}^{n}2^{i-1}$$
$$=\sum_{i=1}^n 2^{i-1} \cdot(2^{n-i}-1) \cdot 2^{n-i}+\sum_{i=1}^{n}2^{i-1}$$

已经可以通过 $50\%$ 的数据。

　　中间 $2^{n-i}-1$ 的那个 $-1$ 可以拆开，变成

$$=\sum_{i=1}^n (2^{i-1} \cdot 2^{n-i} \cdot 2^{n-i})-\sum_{i=1}^{n}(2^{i-1}\cdot2^{n-i})+\sum_{i=1}^{n}2^{i-1}$$
$$=\sum_{i=1}^n (2^{2n-i-1})-\sum_{i=1}^{n}2^{n-1}+\sum_{i=1}^{n}2^{i-1}$$
$$=\sum_{i=1}^n (2^{2n-i-1})-n \cdot2^{n-1}+\sum_{i=1}^{n}2^{i-1}$$
$$=\sum_{i=n-1}^{2n-2} (2^{i})-n \cdot2^{n-1}+\sum_{i=1}^{n}2^{i-1}$$

　　其中几部分是等比数列，直接使用公式

$$=2\cdot2^{2n-2}-2^{n-1}-n \cdot2^{n-1}+2^n-1$$
$$=2^{2n-1}-(n+1) \cdot2^{n-1}+2^n-1$$
$$=2^{2n-1}-(n-1)\cdot2^{n-1}-1$$

　　此时复杂度是 $\log$ 级别的（快速幂），可以通过。
  
最后请时刻注意，**进行乘法运算时一定要保证两个乘数都被取模过。**

代码：

```cpp
#include <cstdio>
#define MOD 1000000007
typedef unsigned long long ll;

ll n, ans;

ll qpow(ll a, ll b){
	ll t = 1;
	while(b){
		if(b & 1) t = t * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return t;
}

int main(){
	
	scanf("%llu", &n);
	
	ans = (qpow(2, (n << 1) - 1) + MOD) % MOD;
	printf("%llu\n", (ans - qpow(2, n - 1) * ((n - 1 + MOD) % MOD) % MOD - 1 + MOD) % MOD);

	return 0;
}
```

---

## 作者：Adchory (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5627)。

## 思路

这题真难吧。

$$\begin{aligned}\sum_{i=1}^{2^n} \log_2\left( \prod_{j=1}^i \mathrm{lowbit}(j) \right)  &=\sum_{i=1}^{2^n}\sum_{j=1}^i \log_2(\mathrm{lowbit}(j)) 
\\&=\sum_{j=1}^{2^n} (2^n-j+1)\log_2(\mathrm{lowbit}(j))\\
&=(2^n+1)\sum_{j=1}^{2^n}\log_2(\mathrm{lowbit}(j))-\sum_{j=1}^{2^n}j\log_2(\mathrm{lowbit}(j)) 

\end{aligned} $$

考虑分别求出 $\displaystyle \sum_{i=1}^{2^n}\log_2(\mathrm{lowbit}(i))$ 和 $\displaystyle \sum_{i=1}^{2^n}i\log_2(\mathrm{lowbit}(i)$。

前者是容易得到的：

$$
\begin{aligned}
\sum_{i=1}^{2^n}\log_2(\mathrm{lowbit}(i))
&=n+\sum_{i=0}^{n-1} i\sum_{j=1}^{2^n-1}[\mathrm{lowbit}(j)=i]
\end{aligned}
$$

不妨钦定第 $i$ 位的二进制位为 $1$，$i+1$ 到 $n$ 的二进制位都可以随便填，这个就是后面和式的结果。

$$
\begin{aligned}
\sum_{i=1}^{2^n}\log_2(\mathrm{lowbit}(i))&=n+\sum_{i=0}^{n-1}i2^{n-i-1}\\
&=2^n-1
\end{aligned}
$$

对于这个，我们有个推论，考虑将 $n$ 二进制分解 $n=2^{k_1}+2^{k_2}+\cdots+2^{k_t}$，那么有 $\sum_{i=1}^n\log_2(\mathrm{lowbit}(i))=\sum_{i=1}^t \sum_{j=1}^{2^{^{k_i}}} \log_2(\mathrm{lowbit}(j))=n-\mathrm{popcount}(n)$。

接下来就是

$$ 
\begin{aligned}
\sum_{i=1}^{2^n}i\log_2(\mathrm{lowbit}(i)) 
&=\sum_{i=1}^{2^n} (2^n-(2^n-i))\log_2(\mathrm{lowbit}(i))\\
&=2^n \sum_{i=1}^{2^n}\log_2(\mathrm{lowbit}(i))-\sum_{i=1}^{2^n}(2^n-i)\log_2(\mathrm{lowbit}(i))\\
&=2^n(2^n-1)-\sum_{i=1}^{2^n}\sum_{j=1}^{2^n-i} \log_2(\mathrm{lowbit}(j))\\
&=2^n(2^n-1)-\sum_{i=0}^{2^n-1} i-\mathrm{popcount}(i)\\
&=2^{n-1}(2^n-1)+n2^{n-1}+1
\end{aligned}
$$

综上，答案就是 $(2^n+1)(2^n-1)-2^{n-1}(2^n-1)-n2^{n-1}-1$。

时间复杂度 $\mathcal O (\log n)$。

---

## 作者：yizcdl2357 (赞：0)

设 $f(x)= \log_2 ( lowbit(j))$

$\left\{f(x)\right\}=\left\{0,1,0,2,0,1,0,3,0……\right\}$

设 $b(x)=x$ 的二进制表示中 $1$ 的个数

设 $g(x)= \sum_{i=1}^x f(i)$

则 $g(x)=\sum_{i\ge1}(k\le n$ 且 $f(k)\ge i$ 的 $k$ 的个数 $)$

![](https://cdn.luogu.com.cn/upload/image_hosting/a2wmmdwg.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

$=\sum_{i\ge1}\lfloor\dfrac{x}{2^i}\rfloor$

$=x-b(x)$

![](https://cdn.luogu.com.cn/upload/image_hosting/xm4zrrrn.png?x-oss-process=image/resize,m_lfit,h_680,w_900)

设 $h(x)=\sum_{i=0}^{2^x-1} b(x)$

则 $h(x)=h(x-1)+(h(x-1)+2^{x-1})$

$=2h(x-1)+2^{x-1}$

$=2(2h(x-2)+2^{x-2})+2^{x-1}$

$=4h(x-2)+2\times2^{x-1}$

$=4(2h(x-3)+2^{x-3})+2\times2^{x-1}$

$=8h(x-3)+3\times2^{x-1}$

$=$ ……

$=2^xh(0)+x\times2^{x-1}$

$=x\times2^{x-1}$

$\sum_{i=1}^{2^n} \log_2 (\prod_{j=1}^i lowbit(j))$

$=\sum_{i=1}^{2^n} \sum_{j=1}^i\log_2 ( lowbit(j))$

$=\sum_{i=1}^{2^n} g(i)$

$=\left( \sum_{i=1}^{2^n}i \right)-\left( \sum_{i=1}^{2^n}b(i) \right)$

$=\dfrac{2^{n}(2^n+1)}{2}-n2^{n-1}-1$

$=2^{n-1}(2^n+1)-n2^{n-1}-1$

所以在取模时只要先算 $k=2^{n-1}$ 就可以了。

**【代码】**
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int mod=1e9+7;
int n; 
int mod1(int x,int y)//取模
{return (x%y+y)%y;}
int pow2mod(int x)//2^x%mod快速幂
{
	if(x==0) return 1;
	if(x%2==1) return 2*pow2mod(x-1)%mod;
	int temp=pow2mod(x/2);
	return temp*temp%mod;
}
signed main()
{
	cin>>n;
	int k=pow2mod(n-1);
	n%=mod;k%=mod;
	printf("%lld",mod1( (k*(2*k+1)%mod)-(n*k%mod)-1 ,mod));
	return 0;
}
```


---

## 作者：buowen123 (赞：0)

# 题意简述

求 
$$\sum_{i=1} ^ {2^n} \log_2(\prod_{j=1} ^ {i} \operatorname{lowbit}(j))$$

取模 $10^9+7$ 的结果。

其中 $\operatorname{lowbit}(j)$ 表示 `j&(~j+1)`，$n\le2^{62}$。
# 题目解决
### 性质一

$\operatorname{lowbit}(j)$ 实际上就是 $j$ 二进制表达中的最低的唯一的位，如 $40=32+8=(101000)_2$，所以 $\operatorname{lowbit}(40)=(1000)_2=8$。

这一点在大部分树状数组的讲解中有呈现（注意 $j>0$ 时 `~j+1` 就是 `-j`），此处不再赘述。

### 性质二

如果用 $\operatorname{ctz}(x)$ 表示 $\log_2(\operatorname{lowbit}(x))$，那么原式等于

$$\sum_{i=1} ^ {2^n} \sum_{j=1} ^ {i} \operatorname{ctz}(j)$$

这一点可以通过 $\log_2(ab)=\log_2(a)+\log_2(b)$ 得到。

知道这两个性质，我们可以开做了。

继续变形：

$$\begin{array}{c}

\sum_{i=1} ^ {2^n} \sum_{j=1} ^ {i} \operatorname{ctz}(j)\\
=(\operatorname{ctz}(1))+(\operatorname{ctz}(1)+\operatorname{ctz}(2))+\dots+(\operatorname{ctz}(1)+\operatorname{ctz}(2)+\dots+\operatorname{ctz}(2^n))\\
=\sum_{i=1}^{2^n}(2^n-i+1)\operatorname{ctz}(i)
\end{array}
$$

这样，$\operatorname{ctz}(i)$ 的贡献为 $2^n-i+1$。

打出 $\operatorname{ctz}$ 的表：

```plain
n = 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
ctz=0  1  0  2  0  1  0  3  0  1  0  2  0  1  0  4
```

这样看很有规律，~~但不会写~~。

我们继续拆分：（第一行为 $i$，第二行为 $\operatorname{ctz}(n)$，接下来每一行都对 $\operatorname{ctz}(n)$ 拆分）

```plain
n =      1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
ctz(n) = 0  1  0  2  0  1  0  3  0  1  0  2  0  1  0  4
a = 1:   0  1  0  1  0  1  0  1  0  1  0  1  0  1  0  1
a = 2:   0  0  0  1  0  0  0  1  0  0  0  1  0  0  0  1
a = 3:   0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  1
a = 4:   0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1
```

我们观察出一个规律：

**对于每一个 $1 \le a \le n$，每一个 $2^a$ 的倍数带来一次贡献。**

例如 $a=1$ 就是第三行，第三行中所有是 $2^1=2$ 的倍数的数都带来贡献。

那么，我们只看第 $a+2$ 行，带来的贡献为：

$$\sum_{i=1}^{2^{n-a}}2^n-2^ai+1$$
其中 $2^n-2^ai+1$ 为上文提到的 $\operatorname{ctz}$ 函数的贡献。

继续计算：
$$
\begin{array}{c}
(\sum_{i=1}^{2^{n-a}}2^n+1)-(\sum_{i=1}^{2^{n-a}}2^ai)\\
=2^{n-a}(2^n+1)-2^a\sum_{i=1}^{2^{n-a}}i\\
=2^{2n-a}+2^{n-a}-2^a\times (2^{n-a}(2^{n-a}+1)/2)\\
=2^{2n-a}+2^{n-a}-2^{n-1}(2^{n-a}+1)\\
=2^{2n-a}+2^{n-a}-2^{2n-a-1}-2^{n-1}\\
=2^{n-a}+2^{2n-a-1}-2^{n-1}
\end{array}
$$

这样，我们得到了第 $a$ 行的贡献。

所以答案为

$$\begin{array}{c}
\sum_{a=1}^{n}2^{n-a}+2^{2n-a-1}-2^{n-1}\\
=(\sum_{a=1}^{n}2^{n-a})+(\sum_{a=1}^{n}2^{2n-a-1})-(\sum_{a=1}^{n}2^{n-1})\\
=(\sum_{a=0}^{n-1}2^a)+(\sum_{a=n-1}^{2n-2}2^a)-n2^{n-1}\\
=2^{2n-1}-1-(n-1)2^{n-1}
\end{array}
$$

至此，本题终于结束。

~~还没结束呢~~ 如果 WA 了一部分点，说明忘记开 `long long` ~~见祖宗了~~。可以用 `__int128` 来代替 `long long`，只是 IO 麻烦点，需要用类似快读快写的东西。

如果你不想用 `__int128`，那么建议将变量统一开成 `long long`，并且将所有底数取模 $10^9+7$，指数取模 $10^9+6$。

代码极其丑陋。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1000000007;
__int128 read(){
    __int128 x=0;
    char ch=getchar();
    while(ch<48) ch=getchar();
    while(ch>47) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
void write(__int128 x){
    if(x>9) write(x/10);
    putchar((x%10)^48);
}
__int128 n;
__int128 qpow(__int128 a,__int128 b){
    __int128 res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
__int128 qpow(__int128 b){return qpow(2,b);}
signed main(){
    n=read();
    write((((qpow(n%(mod-1)*2-1)-1ull)%mod-(n-1)%mod*qpow(n-1)%mod)%mod+mod)%mod);
}
```

---

