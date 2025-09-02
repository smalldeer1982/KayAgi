# [KMOI R1] 集合 First

## 题目描述

有一个集合 $A=\{1,2,3\dots,n\}$。

定义交替和 $G(B)$ 如下：

- 把集合 $B$ 中的元素从大到小排序，得到 $B=\{b_1,b_2\dots,b_{cnt}\}$（$cnt$ 为集合元素个数）。则 $G(B)=\sum\limits_{i=1}^{cnt}\Big((-1)^{i+1}\times b_i\Big)$。

例如 $G(\{1,2,4,6,9\})=9-6+4-2+1=6$。

特别地，$G(\empty)=0$。

现在，给定集合 $A=\{1,2,3,\dots,n\}$，小谢想知道对于 $A$ 的**任意子集 $P$**，求出 $G(P)$ 的总和。

由于小谢太菜了，所以请你帮帮忙，**答案对 $911451407$ 取模。**

## 说明/提示

## 样例 $1$ 解释
$G(\empty)=0$

$G(\{1\})=1$

$G(\{1,2\})=1$

$G(\{2\})=2$

故 $ans=G(\empty)+G(\{1\})+G(\{1,2\})+G(\{2\})=4$。

## 数据范围

**本题采用 subtask 捆绑测试。**

|子任务编号| 测试点 | $n\le$ | 分值 |
|:-:| :----------: | :----------: | :----------: |
|$1$| $1,2$ | $20$ | $15$ |
|$2$| $3\sim5$ | $10^3$ | $10$ |
|$3$| $6\sim10$ | $10^{9}$ | $30$ |
|$4$| $11\sim17$ | $10^{16}$ | $45$ |

对于 $100\%$ 的数据：$1\le n\le 10^{16}$。

## 后记

$$\color{orange}{小谢：别打我，我下次再也不研究大小超过\ 30\ 的集合了。}$$

$$\color{purple}{你：我*****}$$

## 样例 #1

### 输入

```
2```

### 输出

```
4```

## 样例 #2

### 输入

```
1000```

### 输出

```
476463243```

## 样例 #3

### 输入

```
1919810```

### 输出

```
193840227```

# 题解

## 作者：Pink_Cut_Tree (赞：5)

# P9708 [KMOI R1] 集合 First

### $15$ 分

枚举子集，排序，然后暴力加即可。

### $100$ 分

拿 $15$ 分一定不是你的最终目标，尤其是当你的同学 zxh923 已经 A 掉了这道题的时候！

气急败坏之下，我们开始进行手模！

$ans_1=1$ 

$ans_2=1+2+1=4$ 

$ans_3=1+2+3+1+2+1+2=12$ 

$ans_4=1+2+3+4+1+2+3+1+2+1+2+3+2+3+2=32$

附：$ans_4$ 的推导过程

```
1			——1 
2			——2 
3			——3 
4			——4 
1 2 		——1 
1 3			——2 
1 4			——3 
2 3			——1
2 4			——2 
3 4			——1 
1 2 3		——2 
1 2 4		——3 
1 3 4       ——2 
2 3 4       ——3 
1 2 3 4	  + ——2 
----------------- 
			   32
```


然后呢？有没有找到什么规律？

显而易见，$ans_k\div k=2^{k-1}$。

那我们只需要输出 $n\times 2^{n-1}$ 即可。

对于 $n\leq 10^{16}$，我们可以采用快速幂的方法。时间复杂度 $\text O{ ( \text{log }n})$，可以胜任本题目。

### 代码

```cpp
#include<iostream>
using namespace std;
#define ll long long
ll n;
const ll mod=911451407;
ll ksm(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1){ 
			ans=ans*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
return ans;
}
int main(){
	cin>>n;
	cout<<n%mod*ksm(2,n-1)%mod;
return 0;
}
```


---

## 作者：Fire_flame (赞：4)

## $\mathbf{Solution}$

### $\mathtt{15}$ 分做法

写一个 dfs 暴力，可以拿到 $\mathtt{15}$ 分的好成绩。

### $\mathtt{25}$ 分做法

不知道，期待比赛时有人拿到。

### $\mathtt{100}$ 分做法

我们考虑构造，令 $m=2^{n-1}$。

将 $A=\{1,2,3\dots,n\}$ 的子集分成两组 $Q_i,T_i(1\le i\le m)$，且满足 $n\in T_i,n\notin Q_i$，集合 $T_i$ 里面去掉 $n$ 之后等于 $Q_i$。

所以 $G(Q_i)=\sum\limits_{j=1}^{|Q_i|}Q_{i,j}\times(-1)^{j+1}=Q_{i,1}-Q_{i,2}+\dots$

$G(T_i)=\sum\limits_{j=1}^{|T_i|}T_{i,j}\times(-1)^{j+1}=T_{i,1}-T_{i,2}+T_{i,3}-\dots=n-Q_{i,1}+Q_{i,2}-\dots$

那么 $G(Q_i)+G(T_i)=n$。

故答案为 $n\times m=n\times 2 ^{n-1}$，时间复杂度 $O(\log n)$。

### $\mathtt{55}$ 分做法

因为模数是 $911451407$，大约是 $9\times10^8$，所以在用快速幂求完 $m$ 之后要用龟速乘乘上 $n$，不然 $9\times10^8\times10^{16}>10^{18}$ 会爆 `long long`。

没有用龟速乘或者提前取模 $\mathtt{55}$ 分。

标程：

```cpp
#include<bits/stdc++.h>//by Fire_flame
#define int long long
using namespace std;
const int MOD = 911451407;
int n;
int fpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1)res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
int ftime(int a, int b){
	int res = 0;
	while(b){
		if(b & 1)res = (res + a) % MOD;
		a = (a + a) % MOD;
		b >>= 1;
	}
	return res;
}
signed main(){
	scanf("%lld", &n);
	printf("%lld", ftime(fpow(2, n - 1), n));
	return 0;
}
```
标程二：
```cpp
#include<bits/stdc++.h>//代码提供者：OI_LOSER_CGY
#define int long long
using namespace std;
int n,mod=911451407; 
signed main(){
	scanf("%lld",&n);
	int res=n%mod,a=2;n--;
	while(n){
		if(n%2)res=res*a%mod;
		a=a*a%mod,n/=2;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：添哥 (赞：3)

应出题人和部分选手要求，写了这篇题解。

考虑分别计算每个数对答案的贡献。

由题意可以发现每个数对答案贡献的正负由比它大的数的奇偶性决定。奇数为负，偶数为正。

- $n$：在所有包含 $n$ 的 $2^{n-1}$ 个子集中，$n$ 的贡献始终为正，因为没有比它大的数了。该数对答案的贡献为 $2^{n-1}\times n$。

- $i(i∈[1,n-1])$：在所有包含 $i$ 的 $2^{n-1}$ 个子集中，有一半的子集包含奇数个它大的数，另一半的子集包含偶数个它大的数，所以一半正一半负刚好抵消。该数对答案的贡献为 $0$。

所以答案为 $2^{n-1}\times n$，用快速幂计算即可。

---

## 作者：zengziqvan (赞：2)

本题有一定的思维难度，拿来锻炼思维还是不错的。

设集合 $A=\{1,2,3···n-2,n-1\}$ 的 $G(P)$ 总和是 $Q$。

则当加上数 $n$ 时，可以在当前每个子集上再添加上数字 $n$。

那么由于数据情况，$n$ 大于所有在原有集合里的数。

这里设 $A$ 的一个子集 $P$ 为： $\{a_1,a_2,a_3\}$。

那么：

$$
G\{P\}=a_1-a_2+a_3
$$

再考虑加上 $n$ 对此集合的贡献：

$$
G\{P'\}=n-a_1+a_2-a_3
$$

所以现在此集合对答案的贡献为：

$$
G\{P'\}+G\{P\}=(n-a_1+a_2-a_3)+(a_1-a_2+a_3)=n
$$

知道了这个，我们就可以知道大小为 $n$ 的集合的大小实际上就是 $n$ 乘上大小为 $n-1$ 子集的个数。

由于每个数可以选与不选，因此大小为 $n-1$ 的集合的子集的个数为 $2^{n-1}$。

故最终的答案为：

$$
n\times 2^{n-1}
$$

这里要注意，$n$ 是 $10^{16}$，所以要用快速幂与 64 位整数乘法计算结果。

时间复杂度 $O(\log n)$。

```cpp
const long long Mo=911451407;
long long n;
long long mul(long long a,long long b) {
	long long ans=0;
	for(;b;b>>=1) {
		if(b&1) ans=(ans+a)%Mo;
		a=(a+a)%Mo;
	}
	return ans;
}
long long power(long long a,long long b) {
	long long ans=1%Mo;
	for(;b;b>>=1) {
		if(b&1) ans=mul(ans,a);
		a=mul(a,a);
	}
	return ans;
}
int main() {
	cin>>n;
	long long k=power(2,n-1);
	long long ans=(n%Mo*k)%Mo;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Infinity_G (赞：2)

对每个数分别考虑，若比它大的数选了奇数个，那么减掉这个数，否则加上这个数，所以答案为

$$\begin{aligned}
&\sum_{i=1}^n i\times 2^{i-1}\times\left(\sum_{j=0}^{n-i}(-1)^j\times\binom{n-i}{j}\right)\\
=&\sum_{i=1}^ni\times2^{i-1}\times[n-i=0]\\
=&n\times 2^{n-1}
\end{aligned}$$

---

## 作者：CarlosLiu (赞：0)

## 题目大意
给定一个集合，其每一个子集都对应一个数，数的得到方式为把该子集中的数从大到小排列，从 $0$ 开始，第 $1$ 位加上去，第 $2$ 位减掉，依此类推。要输出的数为所有子集对应的数之和。
## 解题思路
直接暴力搜索想都别想。

我们可以化简一下问题。对于每个数，它都在 $2 ^ {n-1}$ 个子集中出现。在这些子集中，决定这个数被加还是被减的，是它在集合中的顺序。如果它是第奇数个，那它被加，反之被减。我们只需考虑，有多少个集合它被加，多少个被减。

加的状态，对应的就是在比这个数大的数中选出偶数个数；减的状态，对应的就是在比这个数大的数中选出奇数个数。试一试几个小的数据，会发现加的状态数等于减的状态数。接下来用二项式定理证明。

二项式定理为 $(x+y) ^ {n} = \sum _ {i = 0} ^ {n} C _ {n} ^ {i} x ^ {n-i} y ^ {i}$ 这样一个式子。如果取 $x=1$ 和 $y=-1$ 这两个值代入，左边为零，右边正的部分正好是从 $n$ 个数中选偶数，负的部分也正好是从 $n$ 个数中选奇数！所以，对于不是第一项的数，正负抵消，不用考虑！

而第一项，带来的值就是它本身的大小乘上它出现的次数。但是直接这样算的话，考虑到数据范围，还是会超时。

让我们再想想。本质上要求一个很大的数乘上 $2$ 的一个很高的幂次。但是，这个幂次足够高，会不会再次模 $911451407$ 余 $1$ 呢？如果这样，可以大大化简。

到了这里，我突然大脑短路，忘记了有什么相关的数学定理。于是我另外编了一个程序算了一下，发现 $455725703$ 是满足条件的最低幂次。然后我又想起了费马小定理这种，不过我也不详细讲了。

于是计算 $(n 2 ^ {n \bmod 455725703}) \bmod 911451407$ 的值，发现三个点超时。

为什么会超时呢？因为我的代码中逐个乘 $2$ 的行为次数有点多。那为什么非要逐个乘 $2$ 呢？为了防止超过超长整型限制。但是，如果一次乘 $4$ 这样多乘一点，最后讨论奇偶的问题，速度快 $2$ 倍，估计就能过了。

最后还真过了。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int main() {
	cin>>n;
	ans=n;
	ans%=911451407;
	n%=455725703;
	for(int i=1;i<=(n-1)/2;i++) {
		ans*=4;
		ans%=911451407;
	}
	if(n%2==0) ans*=2;
	ans%=911451407;
	cout<<ans;
	return 0;
}
```


---

## 作者：rq_kyz (赞：0)

# 【题解】 P9708 [KMOI R1] 集合 First

### 传送门

[P9708 [KMOI R1] 集合 First](https://www.luogu.com.cn/problem/P9708)

---

### 题意

给定一个集合 $A=\{1,2,3,...n\}$，并定义交替和函数 $G(B)$（详见题目，这里不再做叙述），求 $A$ 的任意子集的交替和之和。

---

### 分析

本题的暴力做法为枚举子集，对于每个子集求交替和，然后再将交替和相加，得到答案。

**成功得到 15 分的高分，可喜可贺！**

本题我们可以换个角度去思考。我们可以求出每个数会被加多少次，再把每个数乘上它出现在和中的次数，全部相加起来，即可获得答案。

具体的，当一个数比它大的数字被选了偶数个，则这个数会被加一次；反之会被减一次。所以，对于 $i$ 这个数被加的次数，我们可以得到一下公式：

$2^{i-1}\times\sum_{j=0}^{n-i}(-1)^j\times\binom{n-i}{j}$

（前面的 $2^{i-1}$ 表示比 $i$ 小的数字的方案数）。

所以，最终的总和为：

$\sum_{i=1}^{n}i\times(2^{i-1}\times\sum_{j=0}^{n-i}(-1)^j\times\binom{n-i}{j})=n\times2^{n-1}$

**一不小心就有了 100 分，真是烦人！**

---

### 代码

以下是本蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll p=911451407;
ll ksc(ll a,ll b){
	ll sum=0;
	while(b){
		if(b&1)
			sum=(sum+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return sum;
}
ll ksm(ll a,ll b){
	ll sum=1;
	while(b){
		if(b&1)
			sum=ksc(sum,a);
		a=ksc(a,a);
		b>>=1;
	}
	return sum;
}
int main(){
	ll n;
	scanf("%lld",&n);
	printf("%lld",ksc(n%p,ksm(2,n-1)));
    return 0;
}
```

---

## 作者：GeorgeAAAADHD (赞：0)

## 题目大意

给出一个集合 $A=\{1,2,\cdots,n\}$，定义函数 $G(B)$ 为集合 $B$ 奇数下标的各项之和减去偶数下标的各项之和（下标从 $1$ 开始）。求 $A$ 的所有子集 $P$ 的 $G(P)$ 之和。

## 分析

发现所有不含 $n$ 的子集 $\{a_1,a_2,\cdots,a_{num}\}(a_1<a_2<\cdots<a_{num}<n)$ 都会被其对应的包含 $n$ 的子集 $\{a_1,a_2,\cdots,a_{num},n\}$ 抵消掉，最后这两个子集的交替和之和即为 $n$。

于是这题就迎刃而解了。所有不包含 $n$ 的子集的数量是 $2^{n-1}$ 个，每一对子集的贡献为 $n$，答案即为 $2^{n-1}\times n$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 911451407;
int n;
int qpow(int a, int b)
{
    a %= mod;
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    cout << n % mod * qpow(2, n - 1) % mod;
    return 0;
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

这题看起来挺难的，但是找找规律就能突然有方法。

看下边的拆解你就知道了：
```
  1 2 3 4
  12 13 23 14 24 34
  123 124 134 234
  1234  
  1+2+3+4+2+3+3+4+4+4-1-1-1-2-2-3+3+4+4+4+1+1+1+2-2-2-3-3+4+2-3-1
  1：加4减4
  2：加4减4 
  3：加4减4 
  4： 加8 

  1 2 3
  12 13 23
  123
  1+2+3+2+3+3+3+1-1-1-2-2
  1：加2减2
  2：加2减2
  3：加4

  1 2
  12
  1+2+2-1
  1：加1减1
  2：加2 

  1
  1
  1：加1
```

发现一个惊人秘密，那就是除了最大的 $n$ 以外，其他的数都被抵消了！而且最大的 $n$ 被加的次数也有明显的规律，那就是都是 $2^{n-1}$ 次！所以，答案就是：$n\times2^{n-1}$。

有人坐不住了，迅速敲完代码，上去一看：$25$ 分？？

好吧，由于 $n$ 最大是 $10^{16}$，所以连 $O(n)$ 的复杂度都抗不下来了。所以这个时候要用快速幂来求解。

啥是快速幂？快速幂就是在求解某个数的若干次方，又不能直接求，因为要边乘边模，将求解的复杂度降低到 $O(\log n)$。原理举个例子就懂了：若让你求 $9^{100}$，你怎么求？

第一种，$9\times9=81$，$81\times9=729$，不断进行下去，要乘 $99$ 次。

第二种，先算出 $9^2$，再用这个算出 $9^4$，再算出 $9^8$，以此类推，只需要乘 $8$ 次就可算出。这里谁快谁慢，就显而易见了吧。

快速幂就是用递归实现的，其递归方程也显而易见：

用 $f(a,n)$ 表示计算 $a^n$，

当 $n$ 为偶数时，$f(a,n)=f(a,n\div2)^2$；

当 $n$ 为奇数时，$f(a,n)=f(a,n-1)\times a$。

特别的，当 $n=0$ 时，$f(a,n)=1$。

于是我们能得出如下的递归代码：

```cpp
ll qpow(ll a,ll n)//快速幂
{
    if(n==0) return 1;
    if(n%2==0)
    {
        ll x=qpow(a,n/2);
        return x*x;//一定要注意，这里必须得有一个临时变量，否则会计算两次，时间复杂度会大大增加
    }
    return qpow(a,n-1)*a;
}
```

将代码套进去就行了！

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
ll i,j,k,n,m,t,f1,f2,f3,f4,f5,ans,cnt;
const int MOD=911451407;
ll qpow(ll a,ll n)//快速幂
{
    if(n==0) return 1;
    if(n%2==0)
    {
        ll x=qpow(a,n/2)%MOD;
        return (x*x)%MOD;
    }
    return (qpow(a,n-1)%MOD)*(a%MOD)%MOD;//别忘了乘一次就模一次！
}
int main()
{
  cin>>n;
  ans=1;
  cout<<(n%MOD)*(qpow(2,n-1)%MOD)%MOD;
    return 0;
}
```


---

## 作者：Lyrith_with_xQ (赞：0)

首先，[读题！](https://www.luogu.com.cn/problem/P9708)

思路
------------

我们可以知道，本题定义集合 $A=\{1,2,3,\dots,n\}$，求对于集合 $A$ 的的任意子集 $P$，求出 $G(P)$ 的总和。

乍一看好像没什么思路，可以先推一些 $n$ 较小的例子，我们设 $T(A)$ 代表对于集合 $A$ 的的任意子集 $P$，$G(P)$ 的总和，如 $n=3$ 时：

$$\begin{aligned} T(A)&= G(\{1,2,3\})+ G(\{1,2\})+ G(\{1,3\})+ G(\{2,3\})+ G(\{1\})+ G(\{2\})+ G(\{3\})\\ &= (3-2+1)+(2-1)+(3-1)+(3-2)+1+2+3\\ &= 3+3+3+3 \\&=12\end{aligned}$$

再多推几组之后，我们可以发现 $P(A)$ 有一个特殊的性质：除了集合 $A$ 的最后一个数 $n$，其他数的贡献总会一正一负的抵消。我们知道，对于集合 $A$ 的的任意子集 $P$，有 $2^{n-1}$ 个子集合中会出现集合 $A$ 中的任意一个数 $s$。所以我们可以推导出一个结果：$T(A)=n2^{n-1}$。

在代码中计算出 $n2^{n-1} \mod 911451407$ 后，即可直接输出。

代码
------------
```
#include <bits/stdc++.h>
using namespace std;
long long n;

long long fast_pow(long long a,long long b)\\因为本题n较大，所以需要使用快速幂计算答案
{
    long long ans=1;
    while(b)
    {
        if(b&1)ans=(ans*a)%911451407;
        a=(a*a)%911451407;
        b>>=1;
    }
    return ans;
}

int main()
{
    cin>>n;
    cout<<((n%911451407)*fast_pow(2,n-1))%911451407;
    return 0;
}
```


---

## 作者：WxjzKK (赞：0)

纯粹的数学问题。

看一眼数据范围 $1 \leq n \leq 10^{16}$，别想了，只能推公式，现在我们令 $A_n$ 表示集合 $\{1,2,...,n\}$。

首先我们来讨论对于一个数 $n$，其对应集合 $A_n$ 的子集的性质。

对于不含元素 $n$ 的子集，其必然由集合 $A_{n-1}$ 中的 $0$ 到 $n-1$ 个元素构成，即该子集必然为 $n-1$ 对应集合 $A_{n-1}$ 的子集，这部分子集对 $ans_n$ 的总贡献为 $ans_{n-1}$。

对于含元素 $n$ 的子集，其必然由集合 $A_{n-1}$ 中的 $0$ 到 $n-1$ 个元素以及一个元素 $n$ 构成，即该子集必然为 $n-1$ 对应集合 $A_{n-1}$ 的子集加上元素 $n$，令 $B$ 为 $A_{n}$ 中含元素 $n$ 的子集集合，对于这部分元素，$n$ 的加入会导致计算 $G(B)$ 时，带动在 $n$ 后面的元素贡献取反（相当于变号），令 $m$ 为 $B$ 的元素个数，则这部分子集对 $ans_n$ 的贡献为 $nm-ans_{n-1}$。

所以最终 $ans_n=ans_{n-1}+nm-ans_{n-1}$，得 $ans_n=nm$。

接下来就是求 $m$ 的事情了，我们不难发现，由于前后两种子集有一一对应的关系，所以不难得出，$m$ 为集合 $A_{n-1}$ 中的子集个数。

相信学过集合的应该都知道元素个数为 $i$ 的集合共有 $2^i$ 个子集，接下来我们严谨的证明一下。

令 $f_i$ 表示元素个数为 $i$ 的集合的子集个数，$g_{i,j}$ 表示元素个数为 $i$ 的集合中，元素个数为 $j$ 的子集个数。($\forall i \in N$，$\forall j \in N$，$j \leq i$)

讨论一些特殊的数：

对于 $i=0$，$f_0=g_{0,0}=1$。

对于 $\forall i \geq 1$，$j=0$，$g_{i,0}=g_{i-1,0}=1$。

对于 $\forall j=i$，$i \not=0$，$g_{i,j}=g_{i,i}=g_{i-1,i-1}=1$

接下来讨论一下普遍性质：

对于 $\forall i \geq 1,\forall j \in \{j|1 \leq j \leq i-1\}$，$g_{i,j}=g_{i-1,j-1}+g_{i-1,j}$。

正确性显然，元素个数为 $i$ 的集合的子集中，元素个数为 $j$ 的集合要么由 元素个数为 $i-1$ 的子集中，元素个数为 $j-1$ 的集合加上当前元素个数为 $i$ 的集合多出的元素构成，要么由元素个数为 $i-1$ 的子集中，原来元素个数为 $j$ 的集合构成。

那么：

对于 $\forall i \geq 1$

$$f_i=\sum\limits_{j=0}^ig_{i,j}$$

$$f_i=g_{i,0}+g_{i,i}+\sum\limits_{j=1}^{i-1}g_{i,j}$$

$$f_i=g_{i-1,0}+g_{i-1,i-1}+\sum\limits_{j=1}^{i-1}g_{i-1,j-1}+g_{i-1,j}$$

$$f_i=\sum\limits_{j=0}^{i-1}2g_{i-1,j}$$

$$f_i=2\sum\limits_{j=0}^{i-1}g_{i-1,j}$$

$$f_i=2f_{i-1}$$

现我们已知 $f_0=2^0=1$，那么不难得出：

$$f_i=2^i$$

由此，我们得出 $m=f_{n-1}=2^{n-1}$，所以 $ans_n=2^{n-1} * n$

数据范围 $1 \leq n \leq 10^{16}$，应该不需要我提醒用快速幂和 `long long` 吧。（$QwQ$)

时间复杂度 $O(\log n)$。

$Code$：

```cpp
#include<bits/stdc++.h>
#define mod 911451407
using namespace std;
inline void llread(long long &n){
	long long s=0,t=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') t=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<3)+(s<<1)+(c^48);c=getchar();
	}
	n=s*t;
}
inline void put(long long n){
	if(n<0){
		putchar('-');n=-n;
	}
	if(n<10){
		putchar(n+48);return;
	}
	put(n/10);
	putchar(n%10+48);
}
inline long long work(long long k){
	if(k==1) return 2;
	long long ans=work(k/2);
	if(k&1) return ans*ans*2%mod;
	else return ans*ans%mod%mod;
}
int main(){
	long long n;
	llread(n);
	put(work(n-1)*(n%mod)%mod);
	return 0;
}
```

---

## 作者：Miyamizu_Mitsuha (赞：0)

手玩一个就行，这里不妨玩一个 $4$。

选一个：$4+3+2+1$。

选两个：$4-3,4-2,4-1,3-2,3-1,2-1$。

选三个：$4-3+2,4-3+1,4-2+1,3-2+1$。

选四个：$4-3+2-1$。

注意到除了 $n$，所有数的贡献都会一正一负地抵消。抵消后：

选一个：$4$。

选两个：$4,4,4$。

选三个：$4,4,4$。

选四个：$4$。

其实不难发现每行剩下 $n$ 的个数就是杨辉三角（第四层即是 `1 3 3 1`）。杨辉三角每一层求和也很简单，就是 $2^{n-1}$。

所以就是一共有 $2^{n-1}$ 个 $n$，每个 $n$ 提供 $n$ 的贡献，所以总和就是 $n\times 2^{n-1}$，快速幂即可满分。注意要先模一下，不然会爆。

这种题总结的规律就是，手玩一组，推推性质找找规律，实在不行写个暴力打表看规律，规律不明显的扔 OEIS。

```
#include <iostream>

using namespace std;

const int M =911451407;
long long p(long long b, long long e) {
    long long r = 1;
    b %= M;
    while (e > 0) {
        if (e & 1) {
            r = (r * b) % M;
        }
        b = (b * b) % M;
        e /= 2;
    }
    return r;
}

int main() {
    long long n;
    cin >> n;
    long long t = p(2, (n - 1)) % M;
    long long r = (t *(n % M)) % M;

    cout << r << endl;

    return 0;
}
```




---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9708)

## 引入

如果是集合 $N$，求 $N$ 的子集的所有的元素的和，我们怎么求解呢？

我们发现，对于每一个数，怎么才能加入结果呢？

我们只需要求出 $N$ 的元素个数减一的集合当中有多少个子集就可以了。

所以答案是 $\sum_{i=1}^{i\le |N|}a[i]\times 2^{n-1}$，我们再来看看这一道题目：

## 题目分析

因为这道题目是对于从大到小排序，所以我们自然而然地想到分析最大的数 $n$。

对于最大的数 $n$，我们可以找到一个集合 $N$ 满足 $n\notin N$，我们发现这样的集合个数共有 $2^{n-1}$ 个。

我们再考虑包含 $n$	的情况。我们还来考虑刚刚的集合 $N$，对于每一个集合 $N$，我们总能找到一个集合 $P$，满足 $P=N\bigcup \left \{  n\right \} $，我们发现此时 $f(N)+f(P)=n$（这个是此题最为精妙的地方）。所以总和就是 $n\times 2^{n-1}$。

所以此题就是需要输出 $n\times 2^{n-1}\bmod 911451407$ 的结果即可。

## 题目实现

我们发现 $n\le10^{16}$，所以正常的 $O(n)$ 做法是不行的，需要快速幂来辅助。

于是有了下面的 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,z,s=1;
long long power(long long n,long long powr,long long k){//快速幂
	long long ans=1,tmp=n;
	while(powr){
		if(powr%2==1){
			ans*=(tmp%k);
			ans%=k;
		}
		tmp=(tmp%k)*(tmp%k)%k;
		tmp%=k;
		powr>>=1;
	}
	ans%=k;
	return ans;
}
int main(){
	cin>>n;
	z=911451407;
	s=n;s%=z;
	s*=power(2,n-1,z);
	s%=z;
	cout<<s;
	return 0;
}
```


---

