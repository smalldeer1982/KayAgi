# The Sum of the k-th Powers

## 题目描述

There are well-known formulas: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622F/5be9498766c9d969e3a6760cab8032bf2e4516ad.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622F/136a02961e04e3ae077df756f5b50353eb1651d8.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622F/ef5fbd3c33dc2a5f5200f977f6606feb4c647f7a.png). Also mathematicians found similar formulas for higher degrees.

Find the value of the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622F/93e3cbcc0ffa2514081fc9f5724c4f98f477a6d1.png) modulo $ 10^{9}+7 $ (so you should find the remainder after dividing the answer by the value $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
4 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
30
```

## 样例 #3

### 输入

```
4 3
```

### 输出

```
100
```

## 样例 #4

### 输入

```
4 0
```

### 输出

```
4
```

# 题解

## 作者：formkiller (赞：114)

### 写在前面的话

由于本菜鸡数学水平过差，在写这题的时候不懂为什么 $ \sum\limits_{i=1}^N {i^k}$ 是 $\text{k+1} $ 次多项式，在做完之后希望可以帮助到像我一样数学不好的同学，所以本文主要证明$ \sum\limits_{i=1}^N {i^k}$ 是 $\text{k+1} $ 次多项式   ~~知道的大佬们直接跳过好了~~


---
### 简单证明

参考资料：《数学奥林匹克竞赛小丛书（第二版） 高中卷6 -- 数列与数学归纳法》

首先看一个最基本的等差数列：

$\text {1 , 2 , 3 , .. , N }$

他们两两之间的差：

$\text { 2 - 1 , 3 - 2 , ... , N - ( N - 1 )}$   $\Leftrightarrow$   $\text {1 , 1 , 1 , ... , 1 }$ 


我们发现，当他们两两作差之后，得到了一个全都相同的数列，我们把它称之为**常数数列**

同样的，我们把广泛定义的等差数列 ：

$a_1 , a_2 , a_3 , .. , a_n \;$ 也两两作差

得到$\; a_2 - a_1 , a_3 - a_2  ,  ...  \, , a_n - a_{n-1} \;$，记这个数列为$b_1 , b_2 , b_3 , .. , b_n \;$，简单记作{  ${b_n}$ }

由定义可知，他们的差也是相同的,既{ $b_n $ }是常数数列

对于一个数列 { $a_n$ } 来说，把数列 { $a_n$ } 的元素两两作差，得到数列 { $b_n$ } ，我们一般把这样的数列 { $b_n$ } 称为数列 { $a_n$ } 的**阶差数列**，记数列 { $b_n$ } 为数列 { $a_n$ } 的一阶差分，记作$\bigtriangleup f(x)=f(x+1)-f(x)$

如果记该数列为 { $b_n$ }，其中 $ b_n = a_{n+1} - a_{n} $ ，再对数列 { $ b_n $ } 做差分，所得数列 $\; b_2 - b_1 , b_3 - b_2  ,  ...  \, , b_n - b_{n-1} \;$ 称之为原数列 { $a_n$ } 的二阶差数列，记作$\bigtriangleup^{2} f(x)$，

$\bigtriangleup^{2} f(x)$  $=\bigtriangleup (\bigtriangleup f(x)) $

$\qquad \quad \;$ $= \bigtriangleup(f(x+1)-f(x))$

$\qquad \quad \;$ $= ( f(x+2) - f(x+1) ) - ( f(x+1) - f(x) )$

$\qquad \quad \;$ $= f(x+2) - 2 * f(x+1) + f(x)$

类似的，我们可以定义 $ \text {f(x)} $ 的二阶，三阶，...，$ \text {p} $ 阶差分

即$\bigtriangleup^{p} f(x) = \bigtriangleup  (\bigtriangleup^{p-1} f(x) )$

如果数列 { $ a_n $ } 的 $\text {p}$ 阶差数列是一个非$0$常数数列，那么称它为**p阶等差数列**.特别地，一阶等差数列就是我们通常说的等差数列，二阶及二阶以上的等差数列统称为高阶等差数列.

**定理一：**

数列 {$ a_n $} 的是一个 $\text {p}$ 阶等差数列的充要条件是数列的通项 $a_n$ 为 $ \text {n} $ 的一个$\text {p} $ 次多项式.

**证明：**

已知一个数列 { $ a_n $ } 的是一个 $\text {p}$ 阶等差数列，设数列 { $a_n$ } 的通项 $a_n$ 是一个关于 $\text {n}$ 的 $ \text {v} $ 次多项式，即 $f(x) = \sum\limits_{i=0}^{v}u_i*x^i$，其中 $u_i$ 为 $x^i$ 的系数

令数列 { $b_n$ }成为数列 { $ a_n $ } 的一次差分，则数列 { $b_n$ } 的通项公式为

$\bigtriangleup f(x) = f(x+1) - f(x)$

$\qquad \quad $ $= \sum\limits_{i=0}^{v}u_i*(x+1)^i - \sum\limits_{i=0}^{v}u_i*x^i$

这里我们只考虑 $x^v$ ，易知只有 $ [i==v] $ 的情况才可能得到 $x^v$ 

$\qquad \quad $ $= u_v * (x+1)^v - u_v * x^v$

显然 $(x+1)^v$ 可用二项式定理拆开，但我们只考虑 $x^v$ ，而 $(x+1)^v$ 拆开后 $x^v$ 的系数显然是 $1$ 

$\qquad \quad $ $= u_v * x^v - u_v * x^v$

$\qquad \quad $ $= 0$

我们发现，数列 { $b_n$ } 的通项公式中 $x^v$ 被相减消除了，所以说，数列 { $b_n$ } 的通项公式 $b_n$ 是一个关于 $n$ 的 $v-1$ 次多项式。**也就是说，做一次差分之后数列的通项公式的多项式次数会-1**



由定义可知，数列 { $ a_n $ } 的 $\text {p}$ 阶差数列是一个非$0$常数数列，所以数列 { $a_n$ } 在做 $\text {p}$ 次差分后，得到一个 $0$ 次多项式，即数列 { $a_n$ } 的通项 $a_n$ 是一个关于 $n$ 的 $\text {p}$ 次多项式

证毕。

接下来回到题面上，由题意可知数列 { $a_n$ } 为：

${\sum\limits_{i=1}^{0}i^k},{\sum\limits_{i=1}^{1}i^k},{\sum\limits_{i=1}^{2}i^k},  \;   ...  \;  ,{\sum\limits_{i=1}^{n}i^k}$ 

我们把他们作差得到

${\sum\limits_{i=1}^{1}i^k}-{\sum\limits_{i=1}^{0}i^k},{\sum\limits_{i=1}^{2}i^k}-{\sum\limits_{i=1}^{1}i^k}, {\sum\limits_{i=1}^{3}i^k}-{\sum\limits_{i=1}^{2}i^k},  \;   ...  \;  ,{\sum\limits_{i=1}^{n}i^k}-{\sum\limits_{i=1}^{n-1}i^k}$ 

即 $1^k,2^k, ...  \, ,n^k $


显然的，这个数列的通项公式为 $f(x) = x^k$ ， 是一个 $k $  次多项式

数列  { $ a_n $ } 做一次差分后得到一个 $k$ 次多项式，所以数列  { $ a_n $ } 的通项 $a_n$ 是一个关于 $n$ 的 $k+1$ 次多项式


到了这里，我们终于证明了 $ \sum\limits_{i=1}^N {i^k}$ 是关于 $N$ 的 $\text{k+1} $ 次多项式

接下来的内容其他大佬的题解也有所说明，我这里谈谈我的做法

首先我们证明了这是一个 $k+1$ 次多项式，但是我们没有确定其系数，于是我们考虑拉格朗日插值

由于需要 $k+2$ 个点值才能确定 $k+1$ 次多项式，所以我们至少要取 $k+2$ 个点

这样一来暴力插值的复杂度为 $O (k^2)$，显然不能做到 $1e6$

但是我们发现题目中有个很好的性质，就是他的点值不是确定的，而是我们可以随意选取，于是我们可以选取一些有特殊性质的点来考虑进行优化

于是我们选取一段连续的点，从 $1$ 开始连续选取 $k+2$个点，那么点集为  $\{ (i,\sum\limits_{j=1}^{i}j^k) | i \in [1,k+2] \} $ 

先考虑一个点 $(x,\sum\limits_{i=1}^{x}i^k)$

那么$ \sum\limits_{i=1}^{x}i^k = a_x * \prod\limits_{i=1,i\not=x}^{k+2}(x-i)$，其中 $a_i$ 为常数 

即$ a_x = \dfrac{\sum_{i=1}^{x}i^k}{  \prod_{i=1,i\not=x}^{k+2}(x-i)}$

对答案的贡献：

$ ans_x = a_x * \prod\limits_{i=1,i\not=x}^{k+2}(N-i)$

$\qquad \,$  $ = \dfrac{\sum_{i=1}^{x}i^k}{  \prod_{i=1,i\not=x}^{k+2}(x-i)} * \prod\limits_{i=1,i\not=x}^{k+2}(N-i) $

$\qquad \,$ $= \dfrac{\sum_{i=1}^{x}i^k}{  \prod_{i=1}^{x-1}(x-i)  * \prod_{i=x+1}^{k+2}(x-i)} * \prod\limits_{i=1,i\not=x}^{k+2}(N-i) $

$\qquad \,$ $= \dfrac{\sum_{i=1}^{x}i^k}{  \prod_{i=1}^{x-1}i  * \prod_{i=1}^{k+2-x}(-i)} * \prod\limits_{i=1,i\not=x}^{k+2}(N-i) $

显然对于 $ {\sum_{i=1}^{x}i^k} $ 来说我们可以递推+快速幂求出，对于 $\prod_{i=1}^{x-1}i$ 和 $\prod_{i=1}^{k+2-x}(-i)$
来说我们只要预处理 $1$ 到 $k+2$ 的前缀积，最后再讨论
 $k+2-x$ 的奇偶性即可。对于 $\prod\limits_{i=1,i\not=x}^{k+2}(N-i) $ 来说，这就相当于
 $\prod\limits_{i=1}^{k+2}(N-i) $ 再乘上 $(N-x)$ 的逆元，   $O(k \,log \, k )$ 暴力求逆元或 $O(k)$ 预处理线性求逆元都可以
 
最后的时间复杂度其实不管怎样还会是 $O(k \,log \, k )$ 的，因为递推+快速幂求 $ {\sum_{i=1}^{x}i^k} $的时候快速幂需要   $O(log\,k)$ 的时间复杂度

由于本人码风过丑，这里就不贴出来了，其他几位大佬的  $Code$   都写的很清晰的










---

## 作者：hongzy (赞：56)

**题意**

求$\sum_{i=1}^n i^k$，$n \leq 10^9,k \leq 10^6$

**题解**

观察可得答案是一个$k+1$次多项式，我们找$k+2$个值带进去然后拉格朗日插值

$n+1$组点值$(x_i,y_i)$，得到$n$次多项式$f$的拉格朗日插值方法：

$$f(x) = \sum_{i = 0}^n y_i\prod_{j\not =i} \frac{x-x_j}{x_i-x_j}$$

时间复杂度为$O(n^2)$.

现在考虑这题，我们把$1$到$k+2$带入，有很好的性质：对于每个$i$，分母是$1$乘到$i-1$再乘上$-1$乘到$i-k-2$，这可以预处理阶乘$O(1)$处理。分子可以预处理前后缀积来$O(1)$得到

于是时间复杂度为$O(n)$，可以通过

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;

const int mo = 1e9 + 7;
const int N = 1e6 + 10;

int pl[N], pr[N], fac[N];

int qpow(int a, int b) {
    int ans = 1;
    for(; b >= 1; b >>= 1, a = 1ll * a * a % mo)
        if(b & 1) ans = 1ll * ans * a % mo;
    return ans;
}

int main() {
    int n, k, y = 0, ans = 0;
    scanf("%d%d", &n, &k);
    pl[0] = pr[k + 3] = fac[0] = 1;
    for(int i = 1; i <= k + 2; i ++)
        pl[i] = 1ll * pl[i - 1] * (n - i) % mo;
    for(int i = k + 2; i >= 1; i --)
        pr[i] = 1ll * pr[i + 1] * (n - i) % mo;
    for(int i = 1; i <= k + 2; i ++)
        fac[i] = 1ll * fac[i - 1] * i % mo;
    for(int i = 1; i <= k + 2; i ++) {
        y = (y + qpow(i, k)) % mo;
        int a = pl[i - 1] * 1ll * pr[i + 1] % mo;
        int b = fac[i - 1] * ((k - i) & 1 ? -1ll : 1ll) * fac[k + 2 - i] % mo;
        ans = (ans + 1ll * y * a % mo * qpow(b, mo - 2) % mo) % mo;
    }
    printf("%d\n", (ans + mo) % mo);
    return 0;
}

```



---

## 作者：HenryHuang (赞：25)

### 题意

求 $\sum_{i=1}^ni^k(1\le n\le 10^9,0\le k\le 10^6)$。

### 题解

不要以为没人会卡 $O(k\log_2k)$ 做法的...

真的有这种毒瘤...

首先 $O(k\log_2k)$ 的做法及证明其他题解都已经讲的很清楚了，在这里不再赘述。

首先如何考虑求出插值所需要的点值，即当 $n=1,2,\cdots,k+2$ 时的值。

注意到 $f(i)=i^k$ 是一个完全积性函数，所以我们只需要求出当 $i$ 为质数时候的值，然后线性筛即可，最后做一遍前缀和即可得到答案。这样的复杂度大约是 $O(k)$ 的，因为我们只在质数的位置进行了快速幂。

由于我们取的是一段连续的点值，所以在插值的时候只需要维护一个前缀积、后缀积、阶乘及阶乘逆元即可。

线性求逆元大概就是先求出 $\frac {1}{n!}$，然后 $\frac {1}{(n-1)!}=\frac {1}{n!}\times n$。事实上这个方法可以在线性时间内处理出任意的 $n$ 个已知数的逆元。

然后这个题就完了，总时间复杂度为 $O(k)$。

贴代码

```
/*---Author:HenryHuang---*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
const int p=1e9+7;
int n,k;
int ksm(int a,int b,int p){
	int ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%p;
		b>>=1,a=1ll*a*a%p;
	}
	return ans;
}
int pri[maxn],mi[maxn],cnt;
bool P[maxn];
void init(){
	mi[1]=1;
	for(int i=2;i<=k+2;++i){
		if(!P[i]) mi[i]=ksm(i,k,p),pri[++cnt]=i;
		for(int j=1;j<=cnt&&i*pri[j]<=k+2;++j){
			P[i*pri[j]]=1;
			mi[i*pri[j]]=1ll*mi[i]*mi[pri[j]]%p;
			if(i%pri[j]==0) break;
		}
	}
	for(int i=1;i<=k+2;++i) mi[i]=(mi[i]+mi[i-1]>p?mi[i]+mi[i-1]-p:mi[i]+mi[i-1]);
}
int f[maxn],g[maxn];
int fac[maxn],inv[maxn],ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	init();
	f[0]=g[0]=1;
	if(n<=k+2) cout<<mi[n]<<'\n',exit(0); 
	f[0]=g[k+3]=fac[0]=inv[0]=1;
	for(int i=1;i<=k+2;++i) f[i]=1ll*f[i-1]*(n-i)%p;
	for(int i=k+2;i>=1;--i) g[i]=1ll*g[i+1]*(n-i)%p;
	for(int i=1;i<=k+2;++i) fac[i]=1ll*fac[i-1]*i%p;
	inv[k+2]=ksm(fac[k+2],p-2,p);
	for(int i=k+1;i>=1;--i) inv[i]=1ll*inv[i+1]*(i+1)%p;
	for(int i=1;i<=k+2;++i){
		int a=1ll*f[i-1]*g[i+1]%p;
		int b=1ll*inv[i-1]*((k-i)&1?(p-inv[k+2-i]):inv[k+2-i])%p;
		ans=(ans+1ll*mi[i]*a%p*b%p)%p;
	}
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：皎月半洒花 (赞：21)

好像大家都是拿差分证的，这里给出一个用伯努利数证明的方法。

感觉似乎比差分简洁 ~~，但你要是非说理解不能，我也没啥办法~~
_____

定义 $e(x)$ 为如下的多项式

$$e(x)=1+x+\frac{x^2}{2!}+\cdots +\frac{x^n}{n!}+\cdots$$


## 伯努利数的定义

考虑用母函数的方式定义。此处直接定义伯努利数的指数型母函数是：

$$\mathbf B=\frac{x}{e(x)-1}$$

那么考虑如何展开。记伯努利数为 $\{B_n\}$。发现移一下项

$$x=\left(B_0+B_1x+\frac{B_2}{2!}x^2\cdots\right) * \left(e(x)-1\right)$$

如果记右边卷出来的结果是 $\{a_n\}$，那么发现

$$a_n=\sum_{k=0}^{n-1}\binom{n}{k}B_k$$

此处上界为 $n-1$ 的原因是 $\left(e(x)-1\right)_0=0$ ，其余项均为 $1$ 。 

比较同次项系数可知

$$B_0=1,
\sum_{k=0}^{n-1}\binom{n}{k}B_k=0\qquad (n=2,3,4\cdots)$$

考虑用这个方程去递推每一项。大致思路是左右两边同时加上 $B_n$ 。

$$\sum_{k=0}^{n}\binom{n}{k}B_k=B_n$$

然后就可以发现，比如拿 $n=2$ 举例：

$$B_0+2B_1+B_2=B_2$$

就可以消掉 $B_2$ 求出 $B_1$。以此类推，每次用 $n$ 可以消出 $B_{n-1}$ 。


## 伯努利多项式

考虑观察下列两个EGF的卷积：

$$\frac{x}{e(x)-1}*e(tx)$$

其中 $t$ 是任意常数。考虑记卷积结果为 $\beta(t)$ 。那么显然

$$\beta_n(t)=\sum_{k=0}^n\binom{n}{k}B_kt^{n-k}$$

记这样的多项式为伯努利多项式。这个多项式有个很有用的性质：

$$\beta_{n+1}(t + 1)-\beta_{n+1}(t)=t^n(n+1)\qquad(n=0,1,2,3\cdots)$$

考虑直接做差法证明。首先设出两个式子：

$$\begin{aligned}
\frac{xe(tx)}{e(x)-1}&=\sum\frac{\beta_n(t)}{n!}x^n\qquad(1)\\
\frac{xe((t+1)x)}{e(x)-1}&=\sum\frac{\beta_n(t+1)}{n!}x^n\qquad(2)\\
\end{aligned}$$

$(2)-(1)$ 得到

$$\frac{xe(tx)[e(x)-1]}{e(x)-1}=\sum\frac{\beta_n(t+1)-\beta_n(t)}{n!}x^n$$

即

$$xe(tx)=\sum\frac{\beta_n(t+1)-\beta_n(t)}{n!}x^n$$

比较系数可知

$$\frac{\beta_n(t+1)-\beta_n(t)}{n!}=\frac{t^{n-1}}{(n-1)!}$$

变一下形就可以得到：

$$\beta_{n+1}(t + 1)-\beta_{n+1}(t)=t^n(n+1)$$

## 用伯努利多项式求自然数的 $k$ 次方和

考虑决定自然数 $k$ 次方的要素在于下标 $n$ 。于是考虑所有自然数的 $k$ 次方和就是这样：

$$(k+1)\mathbf S^{(k)}=\sum_{i=1}^{\infty}\left(\beta_{k+1}(i+1)-\beta_{k+1}(i)\right)$$

展开之后

$$\mathbf S_n^{(k)}=\frac{\left(\beta_{k+1}(n+1)-\beta_{k+1}(1)\right)}{k+1}$$

也就是

$$\mathbf S_n^{(k)}=\frac{1}{k+1}\sum_{r=1}^{k+1}\binom{k+1}{r}B_{k+1-r}(n+1)^{r}$$

于是可以知道，自然数的 $k$ 次方和是关于 $n$ 的一个 $k+1$ 次多项式。



---

## 作者：wmy_goes_to_thu (赞：19)

题解区一堆拉插，斯特林公式还有地位吗！！！

众所周知，斯特林公式 $n^k=\sum\limits_{i}S_{k}^{i}n^{\underline{i}}$

$\sum\limits_{i=1}^{n}i^k=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{k}S_{k}^{j}C_{i}^{j}j!=\sum\limits_{j=1}^{k}S_{k}^{j}j!\sum\limits_{i=1}^{n}C_{i}^{j}=\sum\limits_{i=1}^{k}S_{k}^{i}i!C_{n+1}^{i+1}=\sum\limits_{i=1}^{k}S_{k}^{i}\tfrac{(n+1)!}{(i+1)(n-i)!}=\sum\limits_{i=1}^{k}S_{k}^{i}\tfrac{(n+1)^{\underline{i+1}}}{i+1}$

这样，用任意模数 NTT 即可 $O(k\log{k})$ 计算。

这里注意，如果用 $9$ 次 NTT，会被卡常，所以要优化。



---

## 作者：wsyhb (赞：12)

## 目录

- 题意简述
- 分析
- 拉格朗日插值
	- 前置知识
    - 定义
    - 理解
    - 证明
    	- 存在性
        - 唯一性
	- 改进 - 重心拉格朗日插值法
- 题解
- 代码

## 题意简述

给定 $n,k$，求 $1^k+2^k+\cdots+n^k \; mod \; (10^9+7)$ 的值。

数据范围：$1 \le n \le 10^9$，$0 \le k \le 10^6$。

## 分析

由于 $n \le 10^9$，即使我们单次 $O(1)$ 计算 $i^k$，我们也无法计算答案。（**使用线性筛可以在 $O(N)$ 的时间复杂度内计算 $1,2,\cdots,N$ 的 $K$ 次幂**）

我们必须得把 $n$ 的影响从时间复杂度中消除，那怎么办呢？

考虑将这个式子看作一个关于 $n$ 的函数——

更具体地，我们设 $f(n)=\sum_{i=1}^n i^k \; mod \; (10^9+7)$，那么 $n$ 就成了自变量。如果我们能够确定这个函数，我们就可以快速求出答案。

注意到函数 $f(n)$ 的次数为 $k+1$，~~由小学知识可知~~这个函数可以由 $k+2$ 个点唯一确定，具体可以用**拉格朗日插值**实现。

PS：有关 $f(n)$ 次数的证明，可以使用差分或伯努利数，有兴趣的可以看看其他题解（有些题解专门讲解这个），**本文主要讲解拉格朗日插值**。

## 拉格朗日插值

### 前置知识

什么，你不知道插值是什么？点[这里](https://baike.baidu.com/item/%E6%8F%92%E5%80%BC/1196063)了解一下。

根据我自己的理解，**插值就是求出一个属于给定函数类的过给定点的函数**。

~~多项式不知道？那没救了。~~

### 定义

对某个多项式函数，已知有 $k+1$ 个取值点：$(x_0,y_0)$，$(x_1,y_1)$，$\cdots$，$(x_k,y_k)$，其中 $x_i$ 互不相同，那么应用拉格朗日插值公式所得到的**拉格朗日插值多项式**为：

$f(x)=\sum_{i=0}^k y_i \prod_{j \neq i} \dfrac{x-x_j}{x_i-x_j}$

### 理解

重点是后面这一个乘积：$\prod_{j \neq i} \dfrac{x-x_j}{x_i-x_j}$

考虑函数上横坐标为 $x_p \; (0 \le p \le k)$ 的点：

对于 $i \neq p$，$j$ 一定能取到 $p$，即这个式子一定含有因式 $x-x_p$，取值为 $0$；

对于 $i=p$，这个式子分子分母完全相同，取值为 $1$。

因此有 $f(x_p)=y_p$，满足定义。

### 证明

#### 存在性

只需证明拉格朗日插值多项式的正确性，见“理解”一栏。

#### 唯一性

对于任意两个次数不超过 $k$ 的拉格朗日多项式 $f(x)$ 和 $g(x)$，有 $f(x_i)-g(x_i)=0 \quad (\forall i \in [0,k])$。

设 $h(x)=f(x)-g(x)$，则 $h(x)$ 含有因式 $(x-x_0)(x-x_1)\cdots(x-x_k)$。

若 $h(x) \neq 0$，则 $h(x)$ 次数至少为 $k+1$，而 $f(x)$ 和 $g(x)$ 的次数均不超过 $k$，显然矛盾。

因此 $h(x)=0$，即 $f(x)$ 和 $g(x)$ 完全相同，从而证明了唯一性。

### 改进 - 重心拉格朗日插值法

上述插值法，单次计算时间复杂度显然为 $O(k^2)$。如果要在加点过程中随时计算函数的值，这样的复杂度为 $O(k^3)$。（此处假设操作数与 $k$ 同阶）

下面有一种更高效的插值法——

设多项式 $g(x)=(x-x_0)(x-x_1)\cdots(x-x_k)$，并定义**重心权** $w_i=\dfrac{1}{\prod_{j \neq i}(x_i-x_j)}$

则拉格朗日插值多项式变为：

$f(x)=g(x)\sum_{i=0}^k\dfrac{w_i}{x-x_i}y_i$

这被称为**重心拉格朗日插值公式（第一型）或 改进拉格朗日插值公式**。

那么每次加入一个点 $(x_i,y_i)$ 时，只需进行如下操作：

1. 对于所有满足 $j<i$ 的 $j$，将 $w_j$ 除以 $(x_j-x_i)$；

2. 根据定义式计算 $w_i$；

3. 将 $g(x)$ 乘以 $x-x_i$。

加点及计算时间复杂度均为 $O(k)$，总时间复杂度为 $O(k^2)$。

将以上的拉格朗日插值多项式用来对函数 $h(x)\equiv 1$ 插值，可以得到：

$$h(x)=g(x)\sum_{i=0}^k\dfrac{w_i}{x-x_i}$$

将重心拉格朗日插值公式（第一型）除以这个多项式得：

$$f(x)=\dfrac{\sum_{i=0}^k\dfrac{w_i}{x-x_i}y_i}{\sum_{i=0}^k\dfrac{w_i}{x-x_i}}$$

这个公式被称为**重心拉格朗日插值公式（第二型）或 真正的重心拉格朗日插值公式**。有了这个公式，就不必额外计算 $g(x)$ 了。（事实上，它还有一些其他的优点，不过那就扯远了）

## 题解

看完上述，你已经对拉格朗日插值有了一定的了解，那让我们回到这道题上来。

相信你已经发现，本题并不能使用重心拉格朗日插值法。我们不仅无法接受 $O(k^2)$ 的时间复杂度，也没有必要使用它，因为重心拉格朗日插值法的功能在于动态维护（不然为什么不用暴力算定义式代替它呢），而本题只需对函数求一次值。

本题需要利用拉格朗日插值的另一个特性：**当自变量成等差时，可以单次线性计算。**

不信你把 $x_i=a_0+ i \cdot d$ 代入定义式：

$f(x)=\sum_{i=0}^k y_i \prod_{j \neq i} \dfrac{x-x_j}{x_i-x_j}=\sum_{i=0}^k y_i \prod_{j \neq i} \dfrac{x-x_j}{(i-j) \cdot d}$

注意到 $d$ 是常数可以提出来，且有

$$\prod_{j \neq i} (j-i)= (-i) \cdot [-(i-1)] \cdot \; ...  \; \cdot (-1) \cdot 1 \cdot 2 \cdot \; ... \; \cdot (k-i)=(-1)^i \cdot i! \cdot (k-i)!$$

$$\prod_{j \neq i}(x-x_j)=\prod_{j < i}(x-x_j) \cdot \prod_{j > i}(x-x_j)$$

因此，**预处理阶乘、前缀积、后缀积**即可。

PS：本题其实也可以不预处理前缀积和后缀积，而是先特判掉 $n \le k$ 的情况，然后直接乘逆元（用费马小定理+快速幂算逆元），时间复杂度 $O(k \log{10^9})$。

## 代码

**注意本题拉格朗日插值需要 $k+2$ 个点！**

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
const int p=1e9+7;
inline void add(int &a,int b)
{
	a=a+b-(a+b>=p?p:0);
}
inline void mul(int &a,int b)
{
	a=1ll*a*b%p;
}
inline int get_sum(int a,int b)
{
	return a+b-(a+b>=p?p:0);
}
inline int get_product(int a,int b)
{
	return 1ll*a*b%p;
}
inline int get_power(int a,int n)
{
	int res=1;
	a%=p;
	while(n)
	{
		res=(n&1)?get_product(res,a):res;
		mul(a,a);
		n>>=1;
	}
	return res;
}
inline int get_inv(int x)
{
	return get_power(x,p-2);
}
const int max_k=1e6+5;
bool mark_prime[max_k];
int prime[max_k],cnt;
int power[max_k];
int x[max_k],y[max_k];
int inv[max_k],inv_fac[max_k];
void init()
{
	power[1]=1;
	for(int i=2;i<=k+1;++i)
	{
		if(!mark_prime[i])
		{
			prime[++cnt]=i;
			power[i]=get_power(i,k);
		}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=k+1;++j)
		{
			mark_prime[i*prime[j]]=true;
			power[i*prime[j]]=get_product(power[i],power[prime[j]]);
			if(i%prime[j]==0)
				break;
		}
	}
	x[0]=y[0]=0;
	for(int i=1;i<=k+1;++i)
	{
		x[i]=i;
		y[i]=get_sum(y[i-1],power[i]);
	}
	inv_fac[0]=1;
	inv[1]=inv_fac[1]=1;
	for(int i=2;i<=k+1;++i)
	{
		inv[i]=get_product(p-p/i,inv[p%i]);
		inv_fac[i]=get_product(inv_fac[i-1],inv[i]); 
	}
}
int pre[max_k],suf[max_k];
int solve()
{
	if(n<=k+1)
		return y[n];
	pre[0]=n;
	for(int i=1;i<=k+1;++i)
		pre[i]=get_product(pre[i-1],n-i);
	suf[k+1]=n-k-1;
	for(int i=k;i>=0;--i)
		suf[i]=get_product(suf[i+1],n-i);
	int res=0; 
	for(int i=0;i<=k+1;++i)
	{
		int now=get_product(y[i],get_product(inv_fac[i],inv_fac[k+1-i]));
		if((k+1-i)&1)
			now=get_sum(0,p-now);
		if(i>0)
			mul(now,pre[i-1]);
		if(i<=k)
			mul(now,suf[i+1]);
		add(now,p);
		add(res,now);
	}
	return res;
}
int main()
{
	scanf("%d%d",&n,&k);
	init();
	printf("%d\n",solve());
	return 0;
}
```

---

## 作者：Kelin (赞：9)

求$\sum_{i=1}^ni^m$

可以知道这个解显然是一个$d=m+1$次多项式

考虑拉格朗日插值求这个多项式的解

假设有$d+1$组点值$(x_0,y_0),(x_1,y_1),\ldots,(x_d,y_d)$

那么这个多项式可以表示成$f(n)=\sum_{i=0}^dl_i(n)y_i$

其$l_i(n)=\prod_{j=0,j\neq i}^d\frac{n-x_j}{x_i-x_j}$

一般的我们取$x_i=i,y_i=f(i)$

$\Rightarrow l_i=\prod_{j=0,j\neq i}^d\frac{n-j}{i-j}$

$=\frac{n(n-1)\ldots(n-d)}{(n-i)(\prod_{j=0}^{i-1}i-j)(\prod_{j=i+1}^dj-i)(-1)^{d-i}}$

$=(-1)^{d-i}\frac{n(n-1)\ldots(n-d)}{(n-i)i!(d-i)!}$

$=(-1)^{d-i}\frac{n(n-1)\ldots(n-i+1)(n-i-1)\ldots(n-d)}{i!(d-i)!}$

$\Rightarrow f(n)=\sum_{i=0}^d(-1)^{d-i}f(i)\frac{n(n-1)\ldots(n-i+1)(n-i-1)\ldots(n-d)}{i!(d-i)!}$

考虑到$g(x)=x^m$是积性函数,可以在$O(\frac{m}{\ln m}\log(P-2))$的时间预处理

然后预处理阶乘逆元,前缀积和后缀积就可以在$O(m)$的时间内完成插值,或者你嫌麻烦也可以$O(m\log m)$做

---

## 作者：m256i (赞：6)

这里介绍一种比较另类的方法。

我们从一个定理开始：

> $\sum\limits_{i=1}^xi^k$ 是一个关于 $x$ 的 $k+1$ 次多项式。

---

先介绍一个简单的引理：

> 引理 $1$：一个 $n$ 次上升幂/下降幂整式一定是一个 $n$ 次的方幂整式，反之亦然。

原命题显然，展开阶乘幂即可。

逆命题考虑反证法。假设一个 $n$ 次方幂整式对应一个 $m$ 次阶乘幂整式（$m \ne n$），那么这个阶乘幂整式一定对应一个 $m$ 次方幂整式，矛盾，因此逆命题成立。$\blacksquare$

---

再来一个简单的引理：

> 引理 $2$：$(x+C)^n$（$C$ 为常数）的次数仍然为 $n$。

证明和二项式定理类似。考虑数学归纳法：

当 $n=1$ 时，命题显然成立。

如果该命题对 $n=k$ 成立，那么 $(x+C)^{k+1}=(x+C)^k(x+C)=x(x+C)^k+C(x+C)^k$。显然加号左边是 $k+1$ 次的，加号右边是 $k$ 次的，因此 $(x+C)^{k+1}$ 是 $k+1$ 次的，故命题对 $n=k+1$ 也成立。$\blacksquare$

---

我们将 $x^k$ 转换成一个下降幂多项式。根据引理 $1$，这个多项式是 $k$ 次的。设这个多项式为 $F$。因此可以将和式转换为定和式，再根据（有限）微积分基本定理转换为不定和式：

$$
\begin{aligned}
&\sum_{i=0}^xi^k\\
=&{\sum}_0^{x+1}F(x)\delta x\\
=&\sum F(x)\delta x\Big|_0^{x+1}\\
=&\left(\sum F(x)\delta x\right)(x+1)-\left(\sum F(x)\delta x\right)(0)\\
=&\left(\sum F(x)\delta x\right)(x+1)
\end{aligned}
$$

显然 $\sum F(x)\delta x$ 是 $k+1$ 次的，根据引理 $2$，$(\sum F(x)\delta x)(x+1)$ 也是 $k+1$ 次的。将这个下降幂多项式转换成方幂，根据引理 $1$，转换后的多项式仍是 $k+1$ 次。$\blacksquare$

---

设 $k+1=m$，自然数幂和的多项式为 $S$。我们先线性筛出这个多项式在 $0,1,2,3,\cdots,m$ 处的值，时间复杂度 $\Theta\left(\dfrac{m}{\ln m}\times\log m+m-\dfrac{m}{\ln m}\right)=\Theta(m)$。显然，如果 $n \le m$ 就可以直接输出了。

接下来考虑拉格朗日插值：

$$
\begin{aligned}
F(n)&=\sum_{i=0}^mF(i)\prod_{0 \le j \le m,j \ne i}\dfrac{n-j}{i-j}\\
&=\sum_{i=0}^mF(i)\left(\prod_{j=0}^{i-1}\dfrac{n-j}{i-j}\right)\left(\prod_{j=i+1}^m\dfrac{n-j}{i-j}\right)
\end{aligned}
$$

由于 $F(0)=0$，所以我们可以从 $1$ 开始累加。

$$
\begin{aligned}
F(n)&=\sum_{i=1}^mF(i)\left(\prod_{j=0}^{i-1}\dfrac{n-j}{i-j}\right)\left(\prod_{j=i+1}^m\dfrac{n-j}{i-j}\right)\\
&=\sum_{i=1}^mF(i)\dfrac{n^{\underline{i}}}{i^{\underline{i}}}\dfrac{(n-i-1)^{\underline{m-i}}}{(-1)^{\underline{m-i}}}
\end{aligned}
$$

我们发现当 $i=m$ 时右边结果就是 $1$，因此不用单独计算。

$$
\begin{aligned}
F(n)&=\sum_{i=1}^mF(i)\dfrac{n!}{i! \times (n-i)!}\dfrac{(n-i-1)!}{(n-m-1)!(-1)^{m-i}(m-i)!}\\
&=\dfrac{n!}{(n-m-1)!}\sum_{i=1}^mF(i)\dfrac{(-1)^{m-i}(n-i-1)!}{i! \times (n-i)! \times (m-i)!}\\
&=n^{\underline{m}}\sum_{i=1}^mF(i)\dfrac{(-1)^{m-i}}{i! \times (n-i) \times (m-i)!}
\end{aligned}
$$

预处理 $1,2,3,\cdots,m$ 的阶乘逆元，复杂度 $\Theta(m)$。接着按照 [P5431](/problem/P5431) 的方法预处理 $n-1,n-2,n-3,\cdots,n-m$ 的逆元，复杂度 $\Theta(m)$。那么和式和 $n^{\underline{m}}$ 都能在 $\Theta(m)$ 的复杂度内求出，总时间复杂度 $\Theta(m)$。

---

## 作者：big_news (赞：6)

题目所求的东西实际上是有名字的，它叫做“自然数幂之和”，记作 $S_k(n)=\sum\limits_{i=0}^ni^k$。

有一个经典结论是：$S_k(n)$ 是关于 $n$ 的 $k + 1$ 次多项式。这里给出一种全新的证明思路。

都 0202 年了，那么我们就要用 0202 年的办法去证明。众所周知，在今年的联合省选中出现了一种利用第二类斯特林数将常幂展开为下降幂求和的方法，我们就来用这种方法来证一下这个结论：

众所周知，有组合恒等式：
$$\begin{aligned} i^k &= \sum\limits_{j=0}^k  \begin{Bmatrix}k\\ j \end{Bmatrix}j! \dbinom{i}{j}\\ &=\sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}i^{\underline j} \end{aligned}$$

则：
$$\begin{aligned} S_k(n)&=\sum\limits_{i=0}^ni^k \\ &=\sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}\sum\limits_{i=0}^ni^{\underline j}\\ &=\sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}j!\sum\limits_{i=0}^n \dbinom{i}{j} \\ &=\sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}j!\sum\limits_{i=0}^{n-j} \dbinom{i+j}{j}  \\ &= \sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}j!\dbinom{n+1}{j+1} \\ &= \sum\limits_{j=0}^k \begin{Bmatrix}k\\ j \end{Bmatrix}\dfrac{(n+1)^{\underline{j+1}}}{j+1}        \end{aligned}$$

注意到 $j$ 最大为 $k$，则容易发现这是一个关于 $n$ 的 $k+1$ 次多项式。实际上做到这一步已经可以算了，只不过朴素算斯特林数的复杂度是 $O(k^2)$，这并不足够。

注意到题目给了一个质数当模数，那么剩余系下逆元一定是存在的，实际上我们可以换个算法。既然是多项式那么就可以插值，我们先算出来 $S_k(1),...S_k(k+2)$，那么答案即是：
$$\begin{aligned} S_k(n)&=\sum\limits_{i=1}^{k+2}S_k(i)\prod\limits_{j\neq i}\dfrac{n-j}{i-j}\\ &= \sum\limits_{i=1}^{k+2}(-1)^{k-i+2}S_k(i)\frac{pre[i-1]·suf[i+1]}{(i-1)!(k-i+2)!} \end{aligned}$$

其中有：
$$\begin{aligned} pre[i]=\prod_{j=1}^i (n-j) \\ suf[i] = \prod_{j=i}^{k+2}(n-j) \end{aligned}$$

预处理阶乘逆即可，复杂度 $O(k)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int CN = 1e6 + 16;
const int P = 1e9 + 7;
int read(){
    int s = 0, ne = 1; char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') ne = -1; c = getchar();}
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}
int qp(int a, int b){
    int r = 1; 
    while(b) {if(b & 1) r = 1ll * r * a % P; a = 1ll * a * a % P; b >>= 1;} 
    return r;
}
int n, k, s[CN], pre[CN], suf[CN], ifac[CN], ans = 0;
int main()
{
    freopen("_in.in", "r", stdin);
    n = read(), k = read();
    ifac[0] = 1; for(int i = 1; i <= k + 10; i++) ifac[i] = 1ll * ifac[i - 1] * i % P;
    ifac[k + 10] = qp(ifac[k + 10], P - 2); for(int i = k + 9; i + 1; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
    for(int i = 1; i <= k + 2; i++) s[i] = (s[i - 1] + qp(i, k)) % P;
    if(n <= k + 2) return printf("%d", s[n]), 0;
    pre[0] = 1; for(int i = 1; i <= k + 2; i++) pre[i] = 1ll * pre[i - 1] * (n - i) % P;
    suf[k + 3] = 1; for(int i = k + 2; i; i--) suf[i] = 1ll * suf[i + 1] * (n - i) % P;
    for(int i = 1; i <= k + 2; i++){
        s[i] = 1ll * s[i] * pre[i - 1] % P,
        s[i] = 1ll * s[i] * suf[i + 1] % P,
        s[i] = 1ll * s[i] * ifac[i - 1] % P,
        s[i] = 1ll * s[i] * ifac[k + 2 - i] % P;
        if((k + 2 - i) & 1) ans = (ans - s[i] + P) % P;
        else ans = (ans + s[i]) % P;
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Tx_Lcy (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF622F)

## 思路

别的题解说的很吓人，发一篇简单的题解造福后人。

首先观察样例，我们发现答案一定是个 $k+1$ 次多项式，于是可以得到朴素做法，代 $k+2$ 个点进去拉插，时间复杂度 $\mathcal O(k^2)$。

发现这个拉插是可以优化的。

我们先写出拉插的柿子：$\sum_{i=0}^n y_i \prod_{j ≠ i} \dfrac{k-x_j}{x_i-x_j}$。

如果我们钦定 $x_i$ 为一段连续的 $0$ 到 $n$ 的值，那么柿子可以化为：$\sum_{i=0}^n y_i \prod_{j ≠ i} \dfrac{k-j}{i-j}$。

发现分子可以直接维护，就等于 $\dfrac{\prod_{j=0}^n k-j}{k-i}$，上面那个东西可以前缀后缀积维护。

至于分母，不难发现下面那个东西等价于 $\prod_{j=0,j≠i}^n (i-j)$，是 $0$ 以上一段连续的区间和 $0$ 以下的一段连续的区间的乘积，这个东西也可以直接前缀后缀积维护。

那么这道题就被你成功地水过了，时间复杂度 $\mathcal O(n)$。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int const mod=1e9+7;
int y[N],sum1[N],sum2[N],pre[N],suf[N];
inline int qpow(int a,int b){
	int ans=1;
	while (b){
		if (b&1) ans*=a,ans%=mod;
		a*=a,a%=mod,b>>=1;
	}
	return ans;
}
#define inv(x) (qpow(x,mod-2))
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,k;cin>>n>>k;
	for (int i=1;i<=k+2;++i) y[i]=y[i-1]+qpow(i,k),y[i]%=mod;
	sum1[0]=sum2[0]=1;
	for (int i=1;i<=k+2;++i) sum1[i]=sum1[i-1]*i%mod;
	for (int i=1;i<=k+2;++i) sum2[i]=-sum2[i-1]*i%mod;
	pre[0]=suf[k+3]=1;
	for (int i=1;i<=k+2;++i) pre[i]=pre[i-1]*(n-i)%mod;
	for (int i=k+2;i;--i) suf[i]=suf[i+1]*(n-i)%mod;
	int ans=0;
	for (int i=1;i<=k+2;++i){
		int fz=pre[i-1]*suf[i+1]%mod;
		int fm=sum1[i-1]*sum2[abs(k+2-i)]%mod;
		ans+=y[i]*fz%mod*inv(fm)%mod;
		ans%=mod;ans+=mod;ans%=mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：4)

**多项式求值**
- 秦九韶公式可以做到单点 $\Theta(n)$。
- 也就是表示成 $(a_n\cdot x+a_{n-1})\cdot x+\cdots$ 的形式求值。

**多项式插值**
- 代数基本定理：任何一个非零的一元 $n$ 次复系数多项式，都正好有 $n$ 个复数根。（重根视为多个根）
- 插值定理：存在且只存在一个不超过 $n$ 次的多项式经过给定的 $n + 1$ 个点 $(x_i,y_i)$。
- 给定 $n+1$ 个点 $(x_i,y_i)$ 求一个经过这些点的不超过 $n$ 次的多项式。
- 显然可以高斯消元 $\Theta(n^3)$。
- 下面讲拉格朗日插值。
- 基本思想是构造一个多个式子的和，使得在取到 $x=x_i$ 只有一个式子非 0，而这个式子的值为 $y_i$。
$$F(x)=\sum_{i=0}^{n+1}y_i\cdot \prod_{j\ne i}\frac{x-x_j}{x_i-x_j}$$
- 这个式子就满足要求，原理自行体会，求值的时间复杂度是 $\Theta(n^2)$，插多项式呢？也是 $\Theta(n^2)$。 （注意需要模拟多项式乘除法）。
- [模板题](https://www.luogu.com.cn/problem/P4781)。
- [代码实现](https://www.luogu.com.cn/paste/bxzz7lq1)。

**自然数幂和**
- 求 $F(n)=\sum_{i=1}^ni^k$。
- 发现 $F(n)-F(n-1)$ 是 $k$ 次多项式，故 $F(n)$ 是 $k+1$ 次多项式。
- 需要 $k+2$ 个点值插出多项式。
- [模板题](https://www.luogu.com.cn/problem/CF622F)。
- 这里对时间复杂度的要求更高一点，不过我们也可以选择比较特殊的点值，比如 $x_i=i$。
- 式子变为：
$$F(x)=\sum_{i=0}^{k+1}y_i\cdot \prod_{j\ne i}\frac{x-j}{i-j}$$
- 发现有很多可以换掉的，设：
$$G_l(x,i)=\prod_{j=0}^{i-1}(x-j)$$
$$G_r(x,i)=\prod_{j=i+1}^{k+1}(x-j)$$
$$H_l(i)=\prod_{j=0}^{i-1}(i-j)=i!$$
$$H_r(i)=\prod_{j=i+1}^{k+1}(i-j)=(-1)^{k-i+1}(k-i+1)!$$
- 则：
$$F(x)=\sum_{i=0}^{k+1}y_i\cdot\frac{G_l(x,i)\cdot G_r(x,i)}{H_l(i)\cdot H_r(i)}$$
- 预处理阶乘的逆元，$G(x)$ 可以做到 $\Theta(k\log k)$ 的复杂度，瓶颈在于求点值的时候的复杂度。
- [代码实现](https://www.luogu.com.cn/paste/kq95jdw4)。
- 如果再勤快一点，可以线性筛处理出所有 $i^k$，复杂度是 $\Theta(k)$ 的，而非某些人说的 $\Theta(\frac{k\cdot\lg p}{\ln k})$，理由是显然的，你是在快速幂求 $k$ 次方，不是在求逆元。
- [代码实现](https://www.luogu.com.cn/paste/h1f09h6a)。

---

## 作者：Hexarhy (赞：4)

### Preface

拉格朗日插值初步应用。[具体介绍戳这](https://www.luogu.com.cn/blog/80049/lagrange-interpolation-basis)。

这里提供一个较为感性但非常简单的证明方法。

### Solution

本题引出了一个重要的数学结论：$S_k(n)$ 是一个关于 $n$ 的 $k+1$ 次多项式。

如果能直接解出这个多项式计算，当然可以。但我们用拉格朗日插值就可以避免繁琐的推导，隐式地计算这个多项式。

现在来证明 $S_k(n)$ 是一个多项式。

已知 $S_1(n)=\dfrac{n(n+1)}{2}$，以此为基础进行归纳推导。
$$
\begin{aligned}
S_{k+1}(n)&=\sum_{i=1}^ni^{k+1}\\
&=\sum_{i=1}^n i\cdot i^k\\
&=n\sum_{i=1}^n i^k-\sum_{i=1}^{n-1}i^k-\sum_{i=1}^{n-2}i^k-\cdots-1^k\\
&=nS_k(n)-\sum_{i=1}^{n-1}S_k(i)
\end{aligned}
$$
虽然我们没有求出通项公式，但是根据递推式我们知道，$S_1(n)$ 是多项式，多项式加法和乘法的结果也是多项式，也就是说，$S_k(n)$ 也是多项式。

同时，递推公式也反映出了 $S_{k}(n)$ 的次数是 $k+1$ 次，因为 $S_1(n)$ 是二次的。

既然如此，我们就可以用拉格朗日插值，取 $x_{i}=\{1,2,3\cdots,k+2\}$ 即可求出 $S_k(n)$。
$$
S_k(n)=\sum_{i=1}^{k+2}S_{k}(i)\prod_{j\neq i}^{k+2}\frac{n-j}{i-j}
$$
当然，如果直接按照公式算是 $O(k^2)$ 的。但是我们取的特殊值可以提供简化。运用[乘法逆元 2](https://www.luogu.com.cn/problem/P5431) 的套路，预处理出前缀积，后缀积，阶乘即可。

时间复杂度 $O(k\log p)$，$p$ 为模数。

### Code

```cpp
int main()
{
	read(n,k);
	prod1[0]=fact[0]=prod2[k+3]=1;
	for(int i=1;i<=k+2;i++)	fact[i]=fact[i-1]*i%MOD;//预处理阶乘
	for(int i=1;i<=k+2;i++)	prod1[i]=prod1[i-1]*(n-i+MOD)%MOD;//预处理前缀积
	for(int i=k+2;i>=1;i--)	prod2[i]=prod2[i+1]*(n-i+MOD)%MOD;//预处理后缀积
	for(int i=1;i<=k+2;i++)	sum[i]=(sum[i-1]+qpow(i,k))%MOD;//预处理 S_k(i)
	auto inv=[=](const ll& a){return qpow(a,MOD-2);};//求逆元
	for(int i=1;i<=k+2;i++)
	{
		ll t=prod1[i-1]*prod2[i+1]%MOD;
		ll t2=(fact[i-1]*fact[k+2-i]%MOD*((k-i)&1?-1:1)+MOD)%MOD;
		ans=(ans+sum[i]*t%MOD*inv(t2)%MOD)%MOD;
	}
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：AubRain (赞：4)

**题意**：给出 $n,k$ ，$n\le10^9,k\le10^6$，求 $\sum_{i=1}^n i^k(mod\;10^9+7)$

因为 $k$ 次幂求和，最后的公式一定是个 $k+1$ 项多项式。然后知道 $k+2$ 个值就可以求出这个多项式了。

然后我们并不要求知道多项式的具体系数，只要求多项式在 $n$ 处的值，直接拉格朗日插值计算就行了。

这里因为 $x$ 坐标是连续的，记录前缀积和后缀积就可以 $O(n)$ 插值计算了。

代码**短得可怜**

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define p 1000000007
#define int long long
using namespace std;

int n,k,ans,now;
int a[N],f[N],g[N];

inline int POW(int a,int b=p-2,int ans=1){
	for(;b;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}
void solve()
{
	now=f[0]=g[0]=1;
	for(int i=1;i<=k+2;i++)
		now=now*(n-i)%p,f[i]=f[i-1]*i%p,g[i]=-g[i-1]*i%p;;	
	for(int i=1;i<=k+2;i++)
		ans=(ans+a[i]*now%p*POW(n-i)%p*POW(f[i-1]*g[k+2-i]%p))%p;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=k+2 and i<=n;i++)
		a[i]=(a[i-1]+POW(i,k))%p;
	if(n<=k+2) return cout<<a[n],0;
	solve(); cout<<(ans+p)%p;
}
```

---

## 作者：Jayun (赞：2)

# 链接：

[题目](https://www.luogu.com.cn/problem/CF622F)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14411127.html)

# 题目大意：

求出：

$$\sum_{i=1}^{n}i^k\bmod(10^9+7)$$

# 正文：

这是一个 $k+1$ 次的多项式，那么我们如果知道 $k+2$ 个点就可以确定这个多项式。设 $(x_i,y_i)$ 表示第 $i$ 个点的坐标，在本题，$x_i=i,y_i=F(i)$。将这个代入拉格朗日插值公式：

$$F(n)=\sum_{i=1}^{k+2}F(i)\prod_{j\neq i}\frac{n-j}{i-j}\quad(n>k+2)$$

然后要把这个式子化一下：

$$\begin{aligned}F(n)&=\sum_{i=1}^{k+2}F(i)\frac{\left(\frac{\prod\limits_{j=n-k-1}^{n-1}j}{n-i}\right)}{(i-1)!(k+2-i)!}\cdot(-1)^{k+2-i}\\&=\left(\prod\limits_{j=n-k-1}^{n-1}j\right)\sum_{i=1}^{k+2}F(i)\frac{(-1)^{k+2-i}}{(i-1)!(k+2-i)!(n-i)}\end{aligned}$$

所以在 $n>k+2$ 时就 $\mathcal{O}(k\log p)$ 解决了，其中 $p$ 是模数。当 $n\leq k+2$ 时，由于 $k\leq 10^6$，就直接 $\mathcal{O}(n)$ 解决。

# 代码：

```cpp
ll fac[M], res, sum, ans, mod = 1e9 + 7;
int n, k;

ll qpow(ll a, int b)
{
	ll ans = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1) ans = ans * a % mod;
	return ans;
}

int main()
{
	scanf ("%d%d", &n, &k);
	if (n <= M)
	{
		for (int i = 1; i <= n; i++)
			ans = (ans + qpow(i, k)) % mod;
		printf ("%lld\n", ans);
		return 0;
	}
	fac[0] = res = 1;
	for (int i = 1; i <= k + 2; i++)
	{
		res = res * (n - i) % mod; 
		fac[i] = fac[i - 1] * i % mod;
	}
	for (int i = 1; i <= k + 2; i++)
	{
		sum = (sum + qpow(i, k)) % mod;
		ll val = sum * qpow(fac[i - 1] * fac[k + 2 - i] % mod * (n - i) % mod, mod - 2);
		ans = (ans + val * (((k + 2 - i) & 1)? -1: 1)) % mod;
	}
	printf ("%lld\n", (ans * res) % mod);
    return 0;
}
```

---

## 作者：IcyFoxer_XZY (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF622F)

~~又一篇题解......~~

这题刚看题目时，还是想拿快速幂水过的，可数据不允许啊！

**正题开始！！！**

首先，讲最简单的快速幂方法，思路就是枚举依次快速幂，代码如下：

```cpp
#include<cstdio>
#define int long long
const int mod=1e9+7;
int n,k,s=1;
int power(int x,int y){
	int ans=1;x%=mod;
	while(y){
		if(y%2)ans=ans*x%mod;
		y/=2;x*=x;x%=mod;
	}
	return ans;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=2;i<=n;++i){
		s+=power(i,k);
		s%=mod;
	}
	printf("%lld",s);
	return 0;
}
```
AC 8 个点......

那么，什么方法能更高效地解题呢？

这种神奇的方法，就是拉格朗日插值法。

拉格朗日插值法：

显而易见，关于答案 $f(x)$ 是关于 $x$ 的最高次 $k+1$ 的多项式。问题是，怎么得到这个多项式呢？这时候就要使用拉格朗日插值法。

拉格朗日插值法是一个可以由 $k+1$ 个二维平面上的点 $(x_i,y_i)$ ，构造出一个正好穿过这些点的 $k$ 次函数 $f(x)$ 的算法，有： $f(x)=\sum_{i=1}^{k+1}y_i\times l_i(x)$ 

其中 $l_i(x)$ 称为插值基函数，其表达式为 $\prod_{i=j}\frac{x-x_j}{x_i-x_j}$ 。

为什么有这个式子呢？首先看存在性，注意到 $l_i(x)$ 当 $x=x_i$ 时有取值 $1$ ，否则当 $x=x_j(i\ne j)$ 时取值为 $0$ 。那么显然上面的函数可以穿过对应的点。至于唯一性好像要用一些玄学的东西证，你只需要知道 $k+1$ 个点能确定一个 $k$ 次函数就行了。

回归原题，显然能用拉格朗日插值法解题，时间复杂度便是 $O(k\log k)$ 的，如果用线性筛（当然本人不会）可以优化至 $O(k)$ ，AC 没问题了。

**code：**

```cpp
#include<cstdio>
#define int long long//注意数据范围，开longlong 
const int mod=1e9+7,N=1e6+1;
int n,k,invp[N],invn[N],inv[N],pre[N],suf[N];
int power(int a,int b){//快速幂计算 
	int res=1,s=a;
	while(b){
		if(b&1)res=res*s%mod;
		s=s*s%mod;b>>=1;
	}
	return res;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	invp[0]=invn[0]=1;pre[0]=n;
	for(int i=1;i<=k+1;++i){//初始化 
		invp[i]=invp[i-1]*power(i,mod-2)%mod;
		invn[i]=invn[i-1]*power(mod-i,mod-2)%mod;
		pre[i]=pre[i-1]*(n-i+mod)%mod;
	}
	suf[k+1]=(n-k-1+mod)%mod;
	for(int i=k;i>=0;--i)suf[i]=suf[i+1]*(n-i+mod)%mod;
	int ans=0,now=0;//记录答案 
	for(int i=0;i<=k+1;++i){
		if(k>0||i>0)now=(now+power(i,k))%mod;
		int tot=1;
		if(i>0)tot=tot*pre[i-1]%mod;
		if(i<k+1)tot=tot*suf[i+1]%mod;
		int nowtot=tot*invp[i]%mod*invn[k-i+1]%mod;
		ans=(ans+now*nowtot)%mod;
	}
	printf("%lld",ans);//输出 
	return 0;
}
```
Bye!

---

## 作者：foreverlasting (赞：1)

[题面](https://www.luogu.org/problemnew/show/CF622F)

拉格朗日插值。

首先，$\sum_{i=1}^n i^k$ 是一个$k$阶等差数列。根据$k$阶等差数列通项求解（其实就是差分求解啦，这个在数竞高一小蓝本里有证明），可以证明这是一个$k+1$阶的多项式。所以直接插值就好啦！

code:
```
//2018.10.12 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int kcz=1e9+7;
const int K=1e6+10;
namespace MAIN{
    int n,k;
    int f[K];
    inline int qpow(res x,res y){
        res ret=1;
        while(y){
            if(y&1)ret=1LL*ret*x%kcz;
            y>>=1,x=1LL*x*x%kcz;
        }
        return ret%kcz;
    }
    inline void add(res &x,const res &y){
        x+=y;
        x>=kcz?x-=kcz:1;
        x<0?x+=kcz:1;
    }
    inline int calc(const res &x,const res &n){
        res tmp=1,ret=0,p=(n&1)?kcz-1:1;
        for(res i=1;i<=n;i++)tmp=1LL*tmp*(x-i)%kcz*qpow(i,kcz-2)%kcz;
        for(res i=0;i<=n;i++,p=kcz-p)
            add(ret,1LL*p*f[i]%kcz*tmp%kcz),tmp=1LL*tmp*(x-i)%kcz*qpow(x-i-1,kcz-2)%kcz*(n-i)%kcz*qpow(i+1,kcz-2)%kcz;
        return ret;
    }
    inline void MAIN(){
        n=read(),k=read();
        for(res i=1;i<=k+1;i++)add(f[i],f[i-1]+qpow(i,k));
        if(n<=k+1)printf("%d\n",f[n]);
        else printf("%d\n",calc(n,k+1));
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：__OwO__ (赞：1)

我们要求 $h(k)\sum\limits_{i=1}^n i^k$ ,
设 $g(i)=i^k$ ,
发现 $g$ 是一个 $k$ 次多项式函数,
那么 $h$ 是对 $g$ 做一个前缀和,
可以得出 $h$ 是一个 $k+1$ 次多项式函数.

那么考虑带入 $k+2$ 个值进行拉格朗日插值.

原来的式子是 $f(x)=\sum\limits_{i=1}^{k+2} y_i\prod\limits_{i\not=j} \frac{x-j}{i-j}$ ,
朴素算法是 $\mathcal O(n^2)$ 的,
无法接受,
考虑优化.

考虑带入 $1\sim k+2$ ,
那么式子变为 $f(x)=\sum\limits_{i=1}^{k+2} y_i\prod\limits_{i\not=j} \frac{x-j}{i-j}$ 

处理出分子的前后缀和 $p_i = \prod\limits_{j=1}^{i} x-j$ , $s_i = \prod\limits_{j=i}^{k+2} x-j$

那么式子变为 $f(x)=\sum\limits_{i=1}^{k+2} y_ip_{i-1}s_{i+1}\prod\limits_{i\not=j} \frac1{i-j}$ 

发现分母是阶乘形式,
考虑预处理阶乘 $c_i$ ,
需要注意正负.

对于 $i$ ,
分母为 $i-1,i-2,\dots,i-(i-1),i-i,i-(i+1),\dots,i-(k+2)$ 
的积,
注意负数有 $k+2-i$ 项,
所以是 $c_{i-1}c_{i-k-2}(-1)^{k-i+2}$ .

最后式子变为 $f(x)=\sum\limits_{i=1}^{k+2} y_ip_{i-1}s_{i+1}c_{i-1}c_{i-k-2}(-1)^{k-i+2}$

带入 $x=n$ 求出 $f(n)$ 值即可

---

## 作者：CReatiQ (赞：0)

### 观前提示

本题解仅提供一个理论复杂度正确的解法，因为本题模数为 $10^9+7$，没有优秀 $\text{MTT}$ 板子的我被卡常了。

---

### 正文部分

不妨设 $S_{n,m}=\sum_{i=0}^{n-1}i^m$，答案就是 $S_{n+1,k}$。

再设：
$$
\begin{aligned}
F(x) &= \sum_{i \geq 0} f_i x^i \\
&= \sum_{i \geq 0} \frac{S_{n,m}x^i}{i!} \\
&= \sum_{i \geq 0} \sum_{j=0}^{n-1} \frac{(jx)^i}{i!} \\
&= \sum_{j=0}^{n-1} \sum_{i \geq 0} \frac{(jx)^i}{i!} \\
&= \sum_{i=0}^{n-1}e^{ix} \\
&= \frac{e^{nx}-1}{e^x-1} \\
&= \frac{x}{e^x-1} \cdot \frac{e^{nx}-1}{x}
\end{aligned}
$$

继续设：

$$
\begin{aligned}
G(x) &= \sum_{i \geq 0} \frac{g_ix^i}{i!}=\frac{x}{e^x-1} \\
F(x) &= G(x) \cdot \frac{e^{nx}-1}{x} \\
&= (\sum_{i \geq 0} \frac{g_ix^i}{i!}) \cdot (\sum_{i \geq 1}\frac{n^ix^{i-1}}{i!}) \\
&= (\sum_{i \geq 0} \frac{g_ix^i}{i!}) \cdot (\sum_{i \geq 0}\frac{n^{i+1}x^i}{(i+1)!}) \\
S_{n,m} &= m!f_m \\
&= m! \sum_{i=0}^m \frac{g_i}{i!} \cdot \frac{n^{m-i+1}}{(m-i+1)!} \\
&= \frac{1}{m+1}\sum_{i=0}^m \binom{m+1}{i}g_in^{m-i+1}
\end{aligned}
$$

又有 $\large G(x)=\frac{x}{e^x-1}=(\frac{e^x-1}{x})^{-1}=(\sum_{i \geq 0}\frac{x^i}{(i+1)!})^{-1}$，用 $\text{MTT}$ 求逆即可在 $\mathcal{O}(k \log k)$ 的时间复杂度内得到 $g_i$，进而求出 $S_{n+1,k}$。

---

### 关于 $G(x)$

把 $g_i$ 求出来后，一个不搞 $\text{OI}$ 的同学一眼认出这个数列就是伯努利数。

所以 $G(x)$ 即为伯努利数的 $\text{EGF}$，上面的解法也是 $\mathcal{O}(n \log n)$ 求伯努利数的方法。

---

## 作者：xkcdjerry (赞：0)

看到这道题 $n \leqslant 10^9$，$k \leqslant 10^6$ 的数据范围，先盲猜 $O(k)$ 的算法。  
（$10^9$ 的 $n$ 导致复杂度里不可能有 $n$，$10^6$ 的 $k$ 不能带任何 $\log$，而如果是 $O(1)$ 算法数据范围又给的太小了） 

由于本题为 $k$ 次幂求和，所以显然最终结果为 $k+1$ 次多项式，可以考虑拉格朗日插值。

不妨令答案为 $g(n)$，取 $f(1) \sim f(k+2)$ 共 $k+2$ 个点插值，则有：

$$f(n)=\sum^{k+2}_{i=1} {f(i)\prod^{k+2}_{j \neq i}\frac{n-j}{i-j}}$$
预处理 $f_1(i)=\prod\limits^{k+2}_{j \leqslant i}{(n-j)}$，$f_2(i)=\prod\limits^{k+2}_{j \geqslant i}{(n-j)}$，则：

$$f(n)=\sum^{k+2}_{i=1}{f(i) \frac{f_1(i-1)f_2(i+1)}{\prod^{k+2}_{i \neq j}{(i-j)}}}$$

又由于

$$\prod^{k+2}_{i \neq j}{(i-j)}=\prod_{j<i}{(i-j)}\times \prod_{j>i}^{k+2}{(j-i)} \times (-1)^{k+2-i}$$

所以

$$f(n)= \sum^{k+2}_{i=1} f(i) \frac{f_1(i-1)f_2(i+1)}{(i-1)!(k+2-i)!} \times(-1)^{k+2-i}$$

显然，线性预处理 $f_1$，$f_2$ 与阶乘逆元可以做到 $O(k)$ 从 $f(1) \sim f(k+2)$ 求 $f(n)$。

构造 $g(i)=i^k$，则有 $f(i)=\sum\limits^i_{j=1} g(j)$，又因为 $g(i)$ 为严格积性函数，所以可以通过线性筛求出。

处理 $f(1) \sim f(k+2)$ 的复杂度为：（为了方便书写，下文将 $k+2$ 近似为 $k$）

* 线性筛本身的复杂度 $O(k)$
* 对 $\frac{k}{\ln k}$ 个素数各求一次快速幂（$O(\log k)$）共 $O(k \frac{\log k}{\ln k})=O(k \log e)=O(k)$

所以预处理部分复杂度也为 $O(k)$，整个程序也能在 $O(k)$ 时间内执行。

代码：

```cpp
#include <cstdio>
#define MOD 1000000007
#define ll long long
#define K 1000010
ll inv[K],f[K],finv[K];
ll g[K];
ll primes[K];
int top;
bool vis[K];
ll f1[K],f2[K];
ll pow(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    inv[1]=1;
    finv[0]=f[0]=1;
    finv[1]=f[1]=1;
    for(int i=2;i<=k+2;i++)
    {
        inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
        finv[i]=finv[i-1]*inv[i]%MOD;
        f[i]=f[i-1]*i%MOD;
    }
    g[1]=1;
    for(int i=2;i<=k+2;i++)
    {
        if(!vis[i])
        {
            g[i]=pow(i,k);
            primes[top++]=i;
        }
        for(int j=0;j<top&&i*primes[j]<=k;j++)
        {
            vis[i*primes[j]]=true;
            g[i*primes[j]]=g[i]*g[primes[j]]%MOD;
            if(i%primes[j]==0) break;
        }
    }
    f1[0]=1;
    for(int i=1;i<=k+2;i++) f1[i]=f1[i-1]*(n-i)%MOD;
    f2[k+3]=1;
    for(int i=k+2;i>=1;i--) f2[i]=f2[i+1]*(n-i)%MOD;
    for(int i=2;i<=k+2;i++) g[i]=(g[i-1]+g[i])%MOD;
    ll ans=0;
    for(int i=1;i<=k+2;i++)
    {
        int tmp=g[i]*f1[i-1]%MOD*f2[i+1]%MOD*finv[i-1]%MOD*finv[k-i+2]%MOD;
        //-1的幂直接判断奇偶即可
        if((k+2-i)&1) ans=(ans-tmp+MOD)%MOD;
        else ans=(ans+tmp)%MOD;
    }
    printf("%lld",ans);
}
```

---

