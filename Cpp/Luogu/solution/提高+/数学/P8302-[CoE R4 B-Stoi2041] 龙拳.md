# [CoE R4 B/Stoi2041] 龙拳

## 题目背景

![](bilibili:BV1fx411N7bU?page=28)

## 题目描述

对于 $n \in \mathbb{Z_{\ge 2}}$，设 $g(n)$ 为 $n$ 的小于 $n$ 的最大约数，如 $g(7) = 1, g(12) = 6$。

定义 $f(n) = n + g(n)$。记 $f^{(0)}(n)=n$，且对 $m \in \mathbb{Z_{\ge 0}}$ 有 $f^{(m+1)}(n)=f(f^{(m)}(n))$。

多次询问，每次询问给定正整数 $n,k$，求最小的自然数 $m_0$，使得对于任意 $m \ge m_0$，均有 $f^{(m)}(n) \mid f^{(m+k)}(n)$。

若不存在这样的 $m_0$，则令 $m_0=-1$。

## 说明/提示

### 样例解释

当 $n=2,k=3$ 时，$m_0=0$。

当 $n=3,k=4$ 时不存在满足条件的 $m_0$。

---

### 数据规模

**本题采用捆绑测试。**

- 子任务 $1$（$1$ 分）：$T=k=1$；
- 子任务 $2$（$12$ 分）：$T,n,k \le 10$；
- 子任务 $3$（$24$ 分）：$T \le 10,n \le 10^5$；
- 子任务 $4$（$36$ 分）：$T \le 10^3$；
- 子任务 $5$（$27$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $1 \le T \le 2 \times 10^6$，$2 \le n \le 3 \times 10^7$，$1 \le k \le 10^9$。


## 样例 #1

### 输入

```
2
2 3
3 4
```

### 输出

```
0
-1
```

# 题解

## 作者：DESCENDANTSOFDRAGON (赞：14)

### 总体思路

1. 若 $ 3 \mid k $。则令 $ m_{0}=-1 $。
2. 若 $ 3 \nmid k $。下面判断 $ 2 $ 是否整除 $ n $。
3. 若 $ 2 \mid n $。若 $ V_{2}(n) \geq 2 $，则令 $ m_{0}=V_{2}(n)-2 $ 若 $ V_{2}(n) = 1 $，则令 $ m_{0}=0 $。
4. 若 $ 2 \nmid n $。下面判断 $ 3 $ 是否整除 $ n $。
5. 若 $ 3 \mid n $。则令 $ m_{0}=0 $。
6. 若 $ 3 \nmid n $。若 $ V_{2}(n+ \frac{n}{p} ) \geq 2 $，则令 $ m_{0}=V_{2}(n+ \frac{n}{p} )-1 $。若 $ V_{2}(n+ \frac{n}{p} )=1 $，则令  $ m_{0}=1 $。

### 证明

首先取 $ p $ 是 $ n $ 最小的素因子。

不妨列举几项看看规律：

$ f_{0}=n $，$ f_{1}=n+ \frac{n}{p} $，$ f_{2}=n+ \frac{n}{p} + \frac{n+\frac{n}{p}}{2} $，······

注意到为了验证最小素因子是否为 $ 2 $，我们需讨论 $ n $ 的奇偶性。

1. 若 $ 2 \mid n $。

	则每次迭代为：$ n $，$ n+\frac{n}{2} $，······

	但此时我们不知道 $ 2 $ 能被除多少次。
    
	设 $ V_{2}(n) $ 表示 $ n $ 中含 $ 2 $ 的幂次，设 $ V_{2}(n)=t $，$ n=2^t·l $，$ 2 \nmid l $
   
   我们手动迭代一下：$ 2^t·l \to 3·2^{t-1}·l \to 3^2·2^{t-2}·l \to ······ \to 3^i·2^{t-i}·l $
   
   这时会惊奇的发现，$ 2 $ 的幂次在一步步削减，$ 3 $ 的幂次在一步步上升，最终都可转化为 $ 3^{n}·l $ 的问题。
   
   那么研究 $ n $ 是奇数，且 $ 3 \mid n $ 时。
   
2. 设 $ n=3t $。

	我们再次手动迭代：$ 3t \to 4t \to 6t \to 9t \to 12t \to 18t \to ····· $
    
   注意到似乎 $ 3^{i}·t $ 型的数总会出现，事实上我们可以归纳证明
   
   $ f^{3i}=3^{i+1}·t  $，$ f^{3i+1}=4·3^{i}·t  $，$ f^{3i+2}=6·3^{i}·t  $
   
   再考虑 $ k \bmod 3 $ 的余数。

   我们证明 $ 3 \nmid k $ 时 $ m_{0}=-1 $ ：
   
   > 若存在 $ m_{0} $，设 $ 3i+1>m_{0} $

   > 则 $ f^{3i+1}(n)=4·3^i·t $

   > 由于 $ 3 \nmid k $，故 $ 3i+1+k \not\equiv 1 \pmod 3  $。

   > 故 $ f^{3i+1+k}(n) $ 是 $ f^{3i+2} $ 或 $ f^{3i} $ 型。

   > 故 $ V_{2}(f^{3i+1+k}(n)) \leq 1 $，与上矛盾。

   而对于 $ 3 \nmid k $ 时，$ m_{0}=0 $，利用通项式归纳即可。

   由此就证明了其正确性。





---

## 作者：VinstaG173 (赞：14)

出题人题解。

记 $p(n)$ 为 $n$ 的最小质因数，通过一些计算可以发现

$$\begin{aligned}
f(n)&=\dfrac{p(n)+1}{p(n)}n\\
&=\begin{cases}
\dfrac{3}{2}n,&2 \mid n\\
\dfrac{4}{3}n,&2 \nmid n,3 \mid n\\
\dfrac{p(n)+1}{p(n)}n,&(6,n)=1
\end{cases}
\end{aligned}$$

当 $(6,n)=1$ 时，显然 $p(n)+1$ 为偶数，故 $2 \mid f(n)$。由上知此后所有数都不能为 $p(n)$ 的倍数，故 $m_0 \ge 1$，转化为 $2 \mid n$ 的情形。 

当 $8 \mid n$ 时，记 $v_2(n)=t$ 为最大的使得 $2^t \mid n$ 的非负整数 $t$，由 $f(n)=\dfrac{3}{2}n$ 知 $v_2(f(n))<v_2(n)$，由于 $f^{(k)}(n)$ 必为 $2$ 或 $3$ 的倍数，知 $v_2\left(f^{(k)}(n)\right)<\max\{{v_2(n)},3\}=v_2(n)$。故 $m_0 \ge 1$。如此可以归约到 $v_2(n)$ 减少 $1$ 的情形，一直归约即可到 $v_2(n)=2$ 的情形。

当 $4 \mid n,8 \nmid n$ 时，有 $f^{(3)}(n)=\dfrac{4}{3}f^{(2)}(n)=\dfrac{4 \times 3}{3 \times 2}f(n)=\dfrac{4 \times 3 \times 3}{3 \times 2 \times 2}n=3n$，

当 $2 \mid n,4 \nmid n$ 时，有 $f^{(3)}(n)=\dfrac{3}{2}f^{(2)}(n)=\dfrac{3 \times 4}{2 \times 3}f(n)=\dfrac{3 \times 4 \times 3}{2 \times 3 \times 2}n=3n$，

当 $3 \mid n,2 \nmid n$ 时，有 $f^{(3)}(n)=\dfrac{3}{2}f^{(2)}(n)=\dfrac{3 \times 3}{2 \times 2}f(n)=\dfrac{3 \times 3 \times 4}{2 \times 2 \times 3}n=3n$，

显然此时最小的 $k=3$，即 $3 \nmid k$ 时 $n \nmid f^{(k)}(n)$，且 $3 \mid k$ 时显然有 $n \mid f^{(k)}(n)$，故 $3 \nmid k$ 时 $m_0=-1$。

$3 \nmid k$ 时简单计算可得

$$m_0=\begin{cases}
0,&2 \mid n,8 \nmid n \operatorname{or} 3 \mid n\\
v_2(n)-2,&8 \mid n\\
v_2(f(n))-1,&(6,n)=1
\end{cases}$$

线性筛出 $p(n)$ 再暴力计算 $f^{(k)}(n)$ 可以做到 $O(n+T\log{n})$，进行一些卡常（或者不用？）后可以通过。

也可以直接计算 $v_2(n)$，可以做到常数更小的 $O(n+T\log{n})$。

还可以筛出 $v_2(n)$，即可以做到 $O(n+T)$ 时间复杂度。

Code:
```cpp
#include<cctype>
#include<cstdio>
#define rg register
int mp[30000007];
int pr[3000007],cnt;
inline void init(){
	for(rg int i=2;i<=3e7;++i){
		if(!mp[i])pr[++cnt]=mp[i]=i;
		for(rg int j=1,k=i<<1;j<=cnt&&k<=3e7;++j,k=i*pr[j]){
			mp[k]=pr[j];if(i%pr[j]==0)break;}}
}int T,n,k;int main(){
	init();T=read();while(T--){
		n=read();if(read()%3){
			puts("-1");continue;
		}if(n&1){if(mp[n]==3)
			puts("0");else{
				int x=mp[n]+1,b=0;
				while(!(x&1))x>>=1,++b;
				printf("%d\n",(b<3)?1:b-1);
			}}else{int b=0;
			while(!(n&1))n>>=1,++b;
			printf("%d\n",(b<3)?0:b-2);
		}
	}return 0;
}
```

---

## 作者：nomonick (赞：11)

题面：[link](https://www.luogu.com.cn/problem/P8302)

# 算法分析

设: $h(x)$ 为 $x$ 的最小质因数


$$
\therefore \frac{x}{g(x)} = h(x)\ ,\  x = h(x) \times g(x)
$$

$$
\therefore f(x) = (h(x)+1) \times g(x) = \frac{x}{h(x)} \times (h(x) + 1)
$$

当 $ h(x) = 2 $ 时：
$ h(x) + 1 = 3$


当 $ h(x) \geqslant 3 $ 时：
$ 2 \nmid h(x) \; , \;  h(x) + 1 = 2 \times k
$

$$
\therefore \forall \; x \geqslant 2 \times k + 1\ (k \in N^*) \; , \; 2 \mid f(x)
$$


当 $h(x) = 3$ 时：
$ h(x) + 1 = 4 = 2 \times 2
$


不妨设：$x = 2^a \times 3^b \times k$

$$
\begin{aligned}
f(x) & = 2^{a-1} \times 3^{b+1} \times k \\ & \dots \dots \\ f^{(a)}(x) &= 2^{0} \times 3^{b+a} \times k \\ f^{(a+1)}(x) &  = 2^{2} \times 3^{b+a-1} \times k \\ f^{(a+2)}(x) &  = 2^{1} \times 3^{b+a} \times k \\  f^{(a+3)}(x)& = 2^{0} \times 3^{b+a+1} \times k\end{aligned}
$$

综上：

1. $3 \mid k$
1. $f^{(m_0)}(x)$ 为 $ x $ 变为的第一个只含有少于两个因子为 $2$ 或 含有因子 $ 3 $ 的数。

# code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x = 0,f = 1ll;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1ll;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1ll) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}
inline void write(int x)
{
	if (x < 0) x = -x, putchar('-');
	if (x <= 9) putchar(x+'0');
	if (x > 9) write(x/10),putchar((x % 10) + '0');
}
int n,k,tot,ans,tmp;
int prime[SIZE],minn[SIZE];
bool is_prime[SIZE];
inline void Euler()
{
	for (int i = 2; i < (int)3e7; ++i)
	{
		if (!is_prime[i]) prime[++tot]=i,minn[i]=i;
		for (int j = 1; j <= tot && i * prime[j] < (int)3e7; ++j)
		{
			is_prime[i*prime[j]] = true;
			minn[i*prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}
inline int solve()
{
	n = read(); k = read(); ans = -2; tmp = 0;
	if (k % 3 != 0) return -1;
	if (n % 3 == 0 && n % 2) return 0;
	if (n % 2 && n % 3)
	{
		n = n / minn[n] * (minn[n] + 1);
		tmp++;
	}
	while (n % 2 == 0)
	{
		ans ++;
		n /= 2;
	}
	return max(0,ans) + tmp;
}
signed main()
{
	Euler();
	for (int T = read(); T; --T) write(solve()),puts("");
	return 0;
}
```

---

## 作者：hcywoi (赞：4)

[更好的阅读体验。](https://www.cnblogs.com/hcywoi/p/17578121.html)

## Solution

设 $g(x)$ 表示 $x$ 的最小**质因子**。

则 $f(x)=n+\dfrac{n}{g(x)}=\dfrac{g(x)+1}{g(x)}\times n$。

分情况讨论：
- $g(x)=2$，经过 $1$ 次变换之后，$f(x)$ 增加了一个因子 $3$，减少了一个因子 $2$；

- $g(x)>2$，则满足 $2\nmid g(x)$，否则与最小质因子矛盾，经过 $1$ 次变化之后，$f(x)$ 增加一个因子 $2$。

设 $n=2^p\times x$ 且 $2\nmid x$，经过 $p$ 次操作，$n=3^p\times x$，再经过 $1$ 次操作，$n=2^2\times 3^{p-1}\times x$，再经过 $2$ 次操作后，$n=3^{p+1}\times x$，我们发现，$n=3^p\times x$ 后，每 $3$ 次操作一循环。

如果 $m$ 不在循环中，因为 $2$ 的因子一定是单调递减的，所以一定不满足 $f^{(m)}(n)\mid f^{(m+k)}(n)$。

如果 $m$ 在循环中，那么**当且仅当** $k=3q, q\in\mathbb{Z}$，满足 $f^{(m)}(n)\mid f^{(m+k)}(n)$，手玩一下即可。

综上，$3\mid k$ 是有解的充分必要条件。

考虑如何求出最小的自然数 $m_0$。

也就是求出循环的开始位置。

如果一个数 $n=2^p\times x, 2\nmid x$ 在循环里，则满足 $0\le p\le 2$。

- $2\nmid n, 3\nmid n$，先进行一次操作，将 $n\to n+\dfrac{n}{minp_n}$，其中 $minp_n$ 表示 $n$ 的最小质因子，再进行如下操作；
- $2\mid n$，$n=2^p\times x$，其中 $2\nmid x$，需要进行 $\max\{0,p-2\}$ 次操作将 $p$ 变成 $2^{\min\{2, p\}}\times x$，此时 $n$ 已经在循环内；
- $2\nmid n, 3\mid n$，$n$ 本身已经在循环内，不用操作。

其中 $minp$ 可以用线性筛法 $\mathcal O(n)$ 求出。

时间复杂度为：$\mathcal O(n+T\log n)$。

代码：

```cpp
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 30000010;

std::vector<int> minp, primes;
 
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();

    for (int i = 2; i <= n; i ++ ) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

void solve() {
	int n, k;
	std::cin >> n >> k;
	if (k % 3) {
		std::cout << -1 << "\n";
		return;
	}

	if (n % 2 && n % 3 == 0) {
		std::cout << 0 << "\n";
		return;
	}

	int x = -2, y = 0;
	if (n % 2 && n % 3) {
		n = n / minp[n] * (minp[n] + 1);
		y ++ ;
	}

	while (n % 2 == 0) {
		x ++ ;
		n /= 2;
	}
	std::cout << std::max(0, x) + y << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	sieve(N);

	int t;
	std::cin >> t;

	while (t -- ) {
		solve();
	}

	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：2)

> 我右拳打開了天化身為龍
>
> 把山河重新移動填平裂縫
>
> 將東方的日出調整了時空

### 题意

- 对于 $n\in\mathbb{Z}_{\ge2}$，用 $g(n)$ 表示 $n$ 的小于 $n$ 的最大约数。定义 $f(n)=n+g(n)$，记 $f^{\left(0\right)}\left(n\right)=n$，且 $\forall{m\in\mathbb{Z}_{\ge0}}$ 都有 $f^{\left(m+1\right)}\left(n\right)=f\left(f^{\left(m\right)}\left(n\right)\right)$。
- 共 $T$ 次询问，每次询问给定 $n,k$，求最小的 $m_0$ 使 $\forall m\ge m_0$ 都有 $f^{\left(m\right)}\left(n\right)\mid{f^{\left(m+k\right)}}\left(n\right)$。
- $1\le T \le2\times10^6$，$2\le{n}\le3\times10^7$，$1\le{k}\le{10^9}$。

### 做法

#### update 2022.7.8

修改了写挂了的不整除符号。

（这个题啊，今年 1 月份还在搞 MO 的时候做到过）

原题是这样的：

> 设 $\left\{a_n\right\}_{n\ge{1}}\in\mathbb{Z}_{+}$， $p(n)$ 为 $n$ 的最小质因数，定义 $a_{n+1}=a_n+\dfrac{a_n}{p(n)},n\ge1$。证明存在 $N$，$\forall n>N$，都有 $a_{n+3}=3a_n$。

-------

我会尽可能以一种接地气的方式阐述本题的做法。

首先，这个最大约数 $g(n)$ 让我们很烦，与之对应的，我们设 $p(n)$ 为 $n$ 的最小质因数，那么就有 $n=p(n)\times g(n)$。然后把 $f(x)$ 换一种令人舒适的表达：

$$\begin{aligned}f(x)&=n+g(n)\\&=n+\dfrac{n}{p(n)}\\&=\dfrac{p(n)+1}{p(n)}n\end{aligned}$$

这样 $f(x)$ 与 $n$ 的关系就更密切了。

若 $p(n)>2$，则 $2\nmid p(n)$，$2\mid p(n)+1$，也就是 $2\mid{f(n)}$。通俗地说，一个奇数经过一次变换后会产生至少一个因数 $2$。

那么现在有 $2$ 了，$p\left(n'\right)=2,f\left(n'\right)=\dfrac32n'$，消掉了一个 $2$，产生了一个因数 $3$。

假设原先的 $n=2^k\times{x},2\nmid{x}$。经过 $k$ 轮变换后，$2$全没了，此时 $f^{\left(k+1\right)}=\dfrac433^k\times{x}=2^2\times3^{k-1}\times{x}$。又产生了 $2$ 个因数 $2$。

两轮后 $2$ 用光，又产生一个 $3$，然后两个 $2$，一个 $3$……

可以想象，最后应该是一个类似于 $\large\rho$ 的循环，循环的长度为 $3$。

举个例子，$n=35$：

|          $n$          | $p(n)$ |              $f(n)$               |
| :-------------------: | :----: | :-------------------------------: |
|      $5\times7$       |  $5$   |   $\color{red}2\times3\times7$    |
|   $2\times3\times7$   |  $2$   |    $\color{purple}3^2\times7$     |
|     $3^2\times7$      |  $3$   |  $\color{blue}2^2\times3\times7$  |
|  $2^2\times3\times7$  |  $2$   |  $\color{red}2\times3^2\times7$   |
|  $2\times3^2\times7$  |  $2$   |    $\color{purple}3^3\times7$     |
|     $3^3\times7$      |  $3$   | $\color{blue}2^2\times3^2\times7$ |
| $2^2\times3^2\times7$ |  $2$   |  $\color{red}2\times3^3\times7$   |

发现了吗？同色的就是循环！而最小循环节就是 $3$，所以要有 $m_0$，$k$ 必须被 $3$ 整除。

那怎么找 $m_0$ 呢？容易发现，因数中 $2$ 的数量为 $1$ 或 $2$ 或者最小质因数为 $3$ 时，就开始进入循环。

所以我们先 $O(n)$ 线性筛，筛出 $f(n),v_2\left(n\right)$( $v_2\left(n\right)$ 就是 $n$ 有几个因数 $2$ )，然后每次 $O(1)$ 回答即可。

时间复杂度是 $O\left(n+T\right)$。

-----

值得注意的是，出题人 [$\color{black}\text{V}\color{red}\text{instaG173}$](https://www.luogu.com.cn/user/59388) 的 [题解](https://www.luogu.com.cn/blog/59388/solution-p8302) 中最后给出的公式 $\gcd\left(n,6\right)=1$ 的情况存在一定的问题，取 $n=5$ 就知道了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int tc,cnt,prime[3000006],f[30000007],v[30000007];
bitset<30000006>used;
inline void sieve(int n)
{
	v[2]=1; 
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	prime[++cnt]=i,f[i]=i+1;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++)
		{
			used[i*prime[j]]=1;
			f[i*prime[j]]=prime[j]*i+i;
			v[i*prime[j]]=v[i]+(j==1);
			if(i%prime[j]==0)	break;
		}
	}
}
inline int ans(int n,int k)
{
	if(k%3!=0)	return -1;
	if(n&1&&n%3!=0)	return ans(f[n],k)+1;
	if(n%8==0)	return v[n/2]-1;
	return 0;
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	tc=read();
	sieve(30000000);
	while(tc--)
	{
		int n=read(),k=read();
		printf("%d\n",ans(n,k));
	}
	return 0;
}
```

---

## 作者：暗影之梦 (赞：1)

## 思路解析：

首先先解析 $k$ 。如果 $3\nmid k$ ，那么在变化中一定会出现 $f^{(m)} (n)$ 与 $f^{(m+k)} (n)$ 奇偶性不同的情况。因此只有 $3\mid k$ 时满足条件。

对于一个情况 $f^{(u)} (n)=2^a\times l (a>2,l\nmid 2)$ ，可以发现它的每一次操作时小于它的最大约数都为 $f^{(u)} (n)/2$ 。因此， $f^{(u+1)} (n)=f^{(u)} (n)\times \frac{3}{2}=2^{a-1}\times l \times3$ 。所以说在 $a-2$ 次操作后 $f^{(u)}(n)$ 一定会变为这种形式： $f^{(m)} (n)=2^2\times l (l\nmid 2)$ 。

现在考虑这种情况： $f^{(m)} (n)=2^2\times l (l\nmid 2)$ 。

手动模拟一下操作：

 $f^{(m+1)} (n)=2^1\times 3\times l (l\nmid 2)$ 
 
 $f^{(m+2)} (n)=2^0\times 3^2\times l (l\nmid 2)$ 

 $f^{(m+3)} (n)=2^2\times 3\times l (l\nmid 2)$ 

 $f^{(m+4)} (n)=2^1\times 3^2\times l (l\nmid 2)$ 

以此类推，可以发现在 $f^{(m)} (n)=2^a\times l (1\leq a\leq 2,l\nmid 2)$ 时可以进入循环。

那么，对于初始值 $2\mid f(n)$ 的所有情况都考虑了。

对于 $2\nmid f(n)$ ，我们暴力进行操作，直到它成为 $2$ 的倍数为止。

如果完全暴力枚举所有情况的话，一次操作就要 $O(\sqrt n)$ 的时间。但是如果配上线性筛就可以让它只用遍历所有平方小于它的质数，再配上快读快写就可以A了。部分特殊内容看代码。

## 满分代码：

```
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int t,n,k,ans;
inline int read()
{
	int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void write(int x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9)
    {
        write(x/10);
        putchar(x%10+'0');
        return;
    }
    putchar(x+'0');
}
bool f[10001];
int a[10001],cnt;
inline void xxs()//考试的时候因为线性筛挂了导致最后没有A...... 
{
	for(int i=2;i<=n;i++)
	{
		if(!f[i]) a[++cnt]=i;
		for(int j=1;j<=cnt&&a[j]*i<=n;j++)
		{
			f[a[j]*i]=1;
			if(i%a[j]==0) break;
		}
	}
}
signed main()
{
	t=read();
	n=10000;
	xxs();
	for(int ll=1;ll<=t;ll++)
	{
		n=read(),k=read();
		if(k%3!=0) 
		{
			putchar('-');
			putchar('1');
			putchar('\n');
		}else 
		{
			ans=0;
			if(n%3==0)//这个用来谈判3|n但是2不整除的情况 
			{
				int n1=n,cnttw=0;
				while(n1&&n1%2==0)
				{
					cnttw++;
					n1/=2;
				}
				ans+=max(0ll,cnttw-2);
				write(ans);
				putchar('\n'); 
				continue;
			}
			if(n==1)
			{
				putchar('0');
				putchar('\n');
				continue;
			}
			ans=0;
			if(n%2!=0)//暴力模拟操作 
			{
				while(n%2!=0)
				{
					int nn=n,nyue=1;
					for(int i=1;i<=cnt;i++)
					{
						if(a[i]*a[i]>n) break;
						if(n%a[i]==0)
						{
							nyue=n/a[i];
							break;
						}
					}
					n=nn+nyue;
					ans++;
//					cout<<ans<<endl;
				}
			}
			int n1=n,cnttw=0;//数2的次方并利用上面推的结论 
			while(n1&&n1%2==0)
			{
				cnttw++;
				n1/=2;
			}
			ans+=max(0ll,cnttw-2);
			write(ans);
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：_abcd_ (赞：0)

设 $mp_n$ 表示 $n$ 的最小质因子，那么显然有 $f(n) = \frac{n(mp_n + 1)}{mp_n}$。如果 $mp_n > 3$，则不难发现，$mp_n \nmid f^m(n) (m \ge 1)$，因为 $mp_{mp_n + 1} < mp_n$，而 $mp_n-1$ 为合数，因此之后的所有 $f^m(n)$ 的最小质因数到 $mp_n - 1$ 就会被分解，永远不会到达 $mp_n$。

那么假设经过 $k$ 步有 $mp_n \le 3$，设 $n = 2^k b$，其中 $b$ 为奇数，那么就有
$$ 2^k b \to 2^{k-1} \times 3b \to \dots \to 3^kb $$
设 $t = 3^{k-1} b$，则
$$ 3t \to 2 \times 3t \to 3 \times 3t \to 2 \times 2 \times 3t \to 2 \times 3 \times 3t \to \dots $$
然后陷入循环。

因此，若 $n = 8b$，有 $8 \nmid f^m(n)(m \ge 1)$。

同时，若 $k \bmod 3 = 1$，则 $f^k(2b) = 3^l b$；若 $k \bmod 3 = 2$，则 $f^k(4b) = 3^l b$。所以若 $3 \nmid k$，有 $m_0 = -1$。否则，就暴力的模拟过程，直到 $n = 2b$ 或 $n = 4b$ 或 $mp_n = 3$。具体的，如果 $mp_n = 2$，就不断 $n \gets \frac{n}{2}$ 直到 $8 \nmid n$，复杂度为 $O(\log n)$；否则只需要记录 $n \gets mp_n$ 并模拟，直到 $mp_n \ge 3$ 就行了，由于每次至少开根号，因此复杂度为 $O(\log \log n)$。

---

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define maxn 30000005
using namespace std;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t==1?x:-x;
}
int T,n=3e7,m;
namespace PRIME
{
    int prc;
    bool vpr[maxn];
    int pr[1857860],mp[maxn];
    void prime_init()
    {
        for(int i=2;i<=n;i++)
        {
            if(!vpr[i])
            {
                pr[++prc]=i;
                mp[i]=i;
            }
            for(int j=1;j<=prc&&i*pr[j]<=n;j++)
            {
                int x=i*pr[j];
                vpr[x]=1;
                mp[x]=pr[j];
                if(i%pr[j]==0)
                    break;
            }
        }
    }
}
using namespace PRIME;
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    prime_init();
    T=re();
    while(T--)
    {
        n=re(),m=re();
        if(m%3)
        {
            puts("-1");
            continue;
        }
        int ans=0;
        while(mp[n]>3)
            ans++,n=mp[n]+1;
        while(n%8==0)
            ans++,n/=2;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/P8302)

找规律

首先我们发现 $g(2n)=n$，此时有 $f(2n)=2n+n=3n$。

同样地，当 $n$ 为奇数时，$g(3n)=n$，此时有 $f(3n)=3n+n=4n$。

这时候有趣的地方来了，$4n$ 是一个偶数，因此 $f^{(1)}(4n)=6n,f^{(2)}(4n)=9n$。

也就是说，当 $n$ 为奇数时，$f^{(3)}(3n)=9n$。

发现了什么？$n$ 为奇数且为三的倍数时，重复三次此操作，就是将 $n$ 乘以了 $3$，而乘以 $3$ 以后 $n$ 仍然满足“是奇数且是三的倍数”这个条件，那么又可以进行新一轮的循环。

按照这个规律推下去，你会发现当 $n$ 满足上面所说的条件且时，$f^{(i+3x)}(n)=3^xf^{(i)}(n)$。

也就是 $f^{(i)}(n)\mid f^{(i+3x)}(n)$。

并且还会你发现 $f^{(i)}(n)\mid f^{(i+k)}(n)$ 的充分必要条件就是 $k=3x$。

那输出 $-1$ 的情况就是 $k$ 不是 $3$ 的倍数的情况了。

不过这里只是 $n$ 为奇数且是三的倍数的情况，其它情况呢？

其它情况可以分为两类：

1. $n$ 是偶数

   不妨设 $n=2^ab$ 时，那么此时一定有 $f^{a}(n)=3^ab$。

   那就变成了之前的情况了。

   当然也可能提前就能让 $n$ 满足进行循环的条件，比如 $n=2,6,12$ 的答案都是 $0$。

    这个不是很难推，只要让 $n=4\cdot3^xy$ 或者 $n=2\cdot3^xy$ 或者 $n=3^xy(x>0)$，都能直接进入循环。

    最后答案是 $\max(a-2,0)$。

2. $n$ 是奇数但 $n$ 不是三的倍数

   显然 $g(n)$ 也是奇数，那么 $f(n)=n+g(n)$ 一定是偶数。

   那就变成了第一种情况了。

   即答案为 $\max(a-2,0)+1$。

那我们只需要对于每一个 $n$ 求出 $g(n)$ 就行了。

显然用欧拉素数筛可以提前预处理出来。

代码：

```cpp
#include<bits/stdc++.h>
#define N 30000005 
using namespace std;
vector <int> prime;
bool vis[N];int g[N];
int T,n,k;
int main(){
	for(int i(2);i<N;++i){
		if(!vis[i]){prime.push_back(i);g[i]=1;}
		for(int j(0);j<prime.size()&&i*prime[j]<N;++j){
			vis[i*prime[j]]=1;g[i*prime[j]]=i;
			if(!(i%prime[j])) break;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		if(k%3) puts("-1");
		else{
			int cnt(0),flg(0);
			if(n%2&&n%3) n=n+g[n],flg=1;
			while(n&1^1) n>>=1,++cnt;
			printf("%d\n",max(cnt-2,0)+flg);
		}
	}
	return 0;
}
```

---

