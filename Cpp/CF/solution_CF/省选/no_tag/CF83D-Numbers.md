# Numbers

## 题目描述

One quite ordinary day Valera went to school (there's nowhere else he should go on a week day). In a maths lesson his favorite teacher Ms. Evans told students about divisors. Despite the fact that Valera loved math, he didn't find this particular topic interesting. Even more, it seemed so boring that he fell asleep in the middle of a lesson. And only a loud ringing of a school bell could interrupt his sweet dream.

Of course, the valuable material and the teacher's explanations were lost. However, Valera will one way or another have to do the homework. As he does not know the new material absolutely, he cannot do the job himself. That's why he asked you to help. You're his best friend after all, you just cannot refuse to help.

Valera's home task has only one problem, which, though formulated in a very simple way, has not a trivial solution. Its statement looks as follows: if we consider all positive integers in the interval $ [a;b] $ then it is required to count the amount of such numbers in this interval that their smallest divisor will be a certain integer $ k $ (you do not have to consider divisor equal to one). In other words, you should count the amount of such numbers from the interval $ [a;b] $ , that are not divisible by any number between $ 2 $ and $ k-1 $ and yet are divisible by $ k $ .

## 说明/提示

Comments to the samples from the statement:

In the first sample the answer is numbers $ 2,4,6,8,10 $ .

In the second one — $ 15,21 $

In the third one there are no such numbers.

## 样例 #1

### 输入

```
1 10 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
12 23 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6 19 5
```

### 输出

```
0
```

# 题解

## 作者：MuYC (赞：10)

### [CF83D[numbers]](https://ac.nowcoder.com/acm/problem/109065)
#### 前言：

很好的一道数学容斥题。用到了数据分块的技巧，考察时间复杂度分析。

2021/1/6 update: 加入了时间复杂度分析，重新调整了内容。

#### 题意简述:

给定三个整数 $L$,$R$,$k$ ($1<=L <= R <= 2 * 10 ^ 9 , 2 <= k <= 2*10^9$)

你需要求出区间$[L,R]$内，有多少个数 $i$ 满足: $k | i$ && 不存在一个 $j$ ∈ $[2,k - 1]$ 使得 $j | i$

其中 $k | i$ 表示 $i$ 被 $k$ 整除。

#### 分析思路

我们发现一个很显然的性质。倘若 $k$ 不是质数，那么最后的答案肯定是 $0$

为什么呢？

因为倘若 $k$ 不是质数，假若 $k | i$ 那么肯定存在一个不等于 $k$ 的大于等于 $2$ 的因子 $z$ 也满足 $z | i$， $z < k$，这时候肯定没有一个满足条件的 $i$ ，所以最后答案是 $0$

因此我们只需要考虑 $k$ 为质数的情况。

那么题意转化为:区间 $[L,R]$ 中有多少个数 $i$ 的最小质因数是 $k$

我们可以得到一个柿子：

$f(x,k)$ = $\lfloor \frac{x}{k} \rfloor$ $-$ $\sum f(\lfloor \frac{x}{k} \rfloor,i)$(其中 $i$ <= $min(k - 1,\lfloor \frac{x}{k} \rfloor))$ 并且 $i$ 是一个质数。

对于柿子的解释：

$\lfloor \frac{x}{k} \rfloor$ 表示对于 $\frac{x}{k}$ 向下取整。

一开始的$\lfloor \frac{x}{k} \rfloor$ 就表示我们假设所有 $k$ 的倍数的最小质因子都是 $k$，后面的 $\sum f(\lfloor \frac{x}{k} \rfloor,i)$就是减去所有不合法的答案，也就是 $k$ 的倍数中最小质因子不是 $k$ 的数的个数。然后至于为什么$\sum f(\lfloor \frac{x}{k} \rfloor,i)$ 的括号里面是 $\lfloor \frac{x}{k} \rfloor$。

实际上我们枚举的是 $k$ 的倍数，也就是 $k$ 乘上一个数，我们实际上只需要判断乘上的那个数的最小质因数大于等于 $k$ 即可。 

这里的$\lfloor \frac{x}{k} \rfloor$ 也就是乘上的数的范围啦！于是得到了这个柿子。

另外这道题目的一个技巧还有差分，也就是对于区间 $[L,R]$ 算答案可以算$[1,R]$ 的答案 - $[1,L - 1]$ 的答案。

#### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
bool GetPrime(int k) { //O(sqrt(n))判断质数相信大家都会
    for(int i = 2 ; i <= sqrt(k) ; i ++)
        if(k % i == 0) return 0;
    return 1;
}
int GetAns(int x,int k) { //上面提到的计算f(x,k)的函数
    if(GetPrime(k) == 0) return 0;//如果 k 不是质数，显然答案为0
    int sum = x / k;//假设全是k的倍数
    for(int i = 2 ; i <= min(x / k,k - 1) ; i ++)
        sum -= GetAns(x / k,i);
    return sum;
}
signed main() {
    int l , r , k ;
    cin >> l >> r >> k;
    cout << GetAns(r,k) - GetAns(l - 1, k);
    return 0;
}
```

短小，跑得飞快的！看得你是不是懵懵的？为什么这个玩意看起来这么暴力还这么快！

#### 时间复杂度分析

关于这个时间复杂度的分析，由于是递归的形式，不妨按照类似于分析“搜索树”（这里指的是分析搜索复杂度的方法）的方式来按层分析，“搜索树”多少个点，时间复杂度就大概是多少。

考虑第一层向第二层的扩展： 大概会有 $\sqrt{R}$ 个扩张。

```cpp
for(int i = 2 ; i <= min(x / k,k - 1) ; i ++)
```

这一行代码就告诉我们每一层最多就是循环 $\sqrt{x}$次

也就意味着第二层极限情况下大概会有 $33000$ 个扩张

第二层向第三层的扩张呢？有人可能会说是 $\sqrt{\sqrt{R}}$ 个扩张，其实这么说是不严谨的，因为实际上，有很多点扩张实际上达不到 $\sqrt{\sqrt{R}}$ 个。那么到底是多少呢？ 

不妨这么想，首先，考虑有多少个点只能扩展出 $1$ 个，不难发现，有 $1,2,3$ 是只能扩展出 $1$ 个的 , 那么能扩展出 $2$ 个的就是 $4,5,6,7,8$ ，那么按照这个趋势下去，实际上，我们发现对于扩展 $k$ 个数的点，一共会有 $(k + 1) ^ 2 - k ^ 2 = (2 * k + 1)$ 个。
于是我们用这个规律来分析第二层向第三层一共有多少个扩展。

那么，对于第二层一共会有多少个扩展呢？

也就是 $1 * 3$ + $2 * 5$ + $3 * 7$ + $4 * 9$ + ...... + $k * (2 * k + 1)$

现在我们的目标就是求出这里的 $k$ 最大是多少。

不难得出，这里的 $k$ 最大是 $180$ (在 $R = 10 ^ 9$的情况下) 那么上面的柿子我们就可以估算是 $4 * 10^6$

第三层向第四层的扩展呢？实际上这一层的扩展数量是很小的，在庞大的 $4 * 10^6$ 面前，我们可以将其忽略不计。只要大概估算一下，这个程

因此，笔者估计总的复杂度大概是 O($\sqrt{\sqrt{n}} * \sqrt{n} + \sqrt{n}$) 或者应该写为 Ω($\sqrt{\sqrt{n}} * \sqrt{n} + \sqrt{n}$)？

不过上面分析的其实是程序最劣时间复杂度，实际上跑下来比这个要快得多。

---

## 作者：YLWang (赞：4)

没啥思维难度的题。

看到 2e9 想想暴力。第一个结论就是 $k$ 必须是个质数。否则答案为 $0$。

容易发现当 $k$ 比较大的时候可以 $O(\dfrac{r}{k})$ 干过去。

$k$ 比较小的时候就容斥一下所有小于 $k$ 的质数就可以了。复杂度 $O(w \cdot 2^w)$，$w$ 为小于 $k$ 的质数个数。

取阈值为 $k = 70$ 可以较好通过。精细实现可以做到 $O(\dfrac{r}{k})$，不精细需要带一个 $\ln$。事实上不精细实现可以很轻松的艹过去。

实现细节较多，可以参考代码。

YLWang 不知道正解是什么。知道的可以私信 YLWang 一下，十分感谢。

代码链接：https://www.luogu.com.cn/paste/wovttdgl

update on 2020.8.11 : 

复杂度 $O(2^w)$ -> 复杂度 $O(w \cdot 2^w)$。手误了。

---

## 作者：jianhe (赞：3)

### 前言：
容斥题。

### 题意：
给定 $l,r,k$，求 $i \in [l,r]$ 满足 $k$ 是 $i$ 的最小因子的 $i$ 的个数。

### 思路：
首先不难发现 $k$ 必须是质数（一个数的最小因子（除去 $1$ 后）总是质数，否则可以继续分）。

设 $f(n,k)$ 表示 $1 \sim n$ 中满足 $k$ 是其最小因子的个数。

那么题目转化为求 $f(r,k)-f(l-1,k)$。

考虑容斥，求 $f(n,k)$ 时用总方案数减去不合法的。

总方案数为 $\lfloor \frac{n}{k} \rfloor$（$k$ 的倍数的个数）。

不合法的呢？

考虑一个数是 $k$ 的倍数，但 $k$ 不是其最小因子，说明它还有比 $k$ 更小的因子。枚举因子，把 $k$ 除掉即可。

因此 $f(n,k)=\lfloor \frac{n}{k} \rfloor - \sum_{i=2}^{\min{k-1,\lfloor \frac{n}{k} \rfloor}} f(\lfloor \frac{n}{k} \rfloor,i)$。

由于 $k$ 必须是质数，可以做到大幅度剪枝，最劣情况下每层递归可以开一个根号，可以通过。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll l,r,k;
bool p(ll x){
	if(x<2) return 0;
	for(int i=2;i*i<=x;i++)
		if(!(x%i)) return 0;
	return 1;
}
ll f(ll n,ll k){
	if(!p(k)||n<k) return 0;
	ll res=n/k;
	for(int i=2;i<=min(k-1,n/k);i++)
		res-=f(n/k,i);
	return res;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>l>>r>>k;
	cout<<f(r,k)-f(l-1,k);
	return 0;
}
```

---

## 作者：lanretE (赞：1)

这是一道数学题。

令 $f(n,k)$ 表示在 $[1,n]$ 中满足 $k\mid i$ 并且对于 $\forall j\in[2,k-1]\nmid i$ 的 $i$ 的个数。

首先注意到如果 $k$ 是合数的话，令 $a$ 是一个小于 $k$ 的 $k$ 的质因子，那么如果 $k\mid i$，那么一定有 $a\mid i$，所以此时答案为 $0$。

在 $[1,n]$ 里面是 $k$ 的倍数的数有 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个，然而我们要求的就是这些数中不能被 $[2,k-1]$ 里面的数整除的，也就是说 $k$  为此数的最小质因子，那么我们要做的就是把可以被 $k$ 整除，但是 $k$ 不是其最小质因子的数减掉。

那么怎么减呢？

当 $k$ 为质数时，$[1,n]$ 中 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 个 $k$ 的倍数分别是 $k$ 的 $1$ 到 $\left\lfloor\dfrac{n}{k}\right\rfloor$ 倍，设此数为 $k$ 的 $m$ 倍，如果 $m$ 除了 $k$ 以外还有小于 $\min(m,k-1)$ 的质因子 $p$，那么 $mk$ 的最小质因子就一定是 $p$，也就是说此时不满足条件，要减掉，这类数有 $f(\left\lfloor\dfrac{n}{k}\right\rfloor,p)$ 个，所以我们枚举质数 $p$ 即可。

```
#include<iostream>
using namespace std;
int l,r,k;
bool check(int x){
	for(int i=2;i*i<=x;++i)
		if(x%i==0) return 0;
	return 1;
}

int calc(int n,int k){//从1到n 
	int minn=min(k-1,n/k);
	int cnt=n/k;
	for(int i=2;i<=minn;++i) 
		if(check(i)) cnt-=calc(n/k,i);
	return cnt;
}

int main(){
	cin>>l>>r>>k;
	if(!check(k)){
		cout<<0;
		return 0;
	}
	cout<<calc(r,k)-calc(l-1,k);
	return 0;
}
```


---

## 作者：一叶知秋。 (赞：1)

由题目可得，答案其实就是 $l$ 到 $r$ 之间最小质因子等于 $k$ 的数的个数，很明显 $ans=ans(r)-ans(l-1)$ ，所以分开求解

所以若 $k$ 为合数答案显然为 $0$ 。

当 $k$ 为质数时，设 $calc(n,k)$ 为 $1-n$ 中最小质因子等于 $k$ 的个数，直接算似乎不太好算，选择拿 $1-n$ 中 $k$ 的倍数的总数减去这其中有质因子小于 $k$ 的

所以可以列出式子：

$calc(n,k)=\lfloor \frac{n}{k} \rfloor - \sum\limits_{i \in p}^{i \le \min(k,\lfloor \frac{n}{k} \rfloor)} calc(\lfloor \frac{n}{k} \rfloor,i)$

后面的和式就是上面所述的质因子存在小于 $k$ 的数，因为 $k$ 是质数，所以直接除以 $k$ 不影响，然后其实就是枚举最小质因子是哪个即可

$\text{P.S.}$ 至于为什么不能正推，是因为时间复杂度不对，那样的话每次是 $k \le i \le \min(n-k,\lfloor \frac{n}{k} \rfloor)$ ，当 $k$ 较小时效率很低，而逆推每次循环都是 $O(\sqrt{n})$ 的（当前的 $n$）

$code$ :

```cpp
#include<cstdio>
#include<cctype>

inline int read(){
	int r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

inline bool is_prime(int x){
	if(x<=1)return 0;
	if(x<=3)return 1;
    if(!(x%2)||!(x%3))return 0;
	for(int i=5;i*i<=x;i+=6)
		if(!(x%i)||!(x%(i+2)))return 0;
	return 1;
}

inline int calc(int n,int k){
	if(!is_prime(k))return 0;//k不是质数肯定是0
	if(n<=k)return (n==k);//注意n=k时n满足条件，故返回1
    int s=n/k;
	for(int i=2;i<k&&i<=n/k;i++)
		s-=calc(n/k,i);//直接减即可
	return s;
}

int main(){
    int l=read(),r=read(),k=read();
	printf("%d\n",calc(r,k)-calc(l-1,k));//拆开算
	return 0;
}

```


---

## 作者：kimi0705 (赞：0)

### Part.0 题意
$l$ 到 $r$ 之间最小质因子等于 $k$ 的数的个数。
### Part.1 题解
首先，显然的，$ans_{[l,r]} = ans_{[1, r]}-ans_{[1, l-1]}$。

其次，考虑 $i$ 满足的条件：
1. 是 $k$ 的倍数。
2. 是 $i$ 所有的因子中的最小的。

分类讨论：
1. 当 $k$ 为合数时，答案显然为 $0$。
2. 当 $k$ 为质数
   - 由条件得答案为满足 $1$ 的数量减去满足 $1$ 但不满足 $2$ 的数量。
   - 其中满足 $1$ 的数量 应为：$\lfloor \frac{n}{k}\rfloor$
   - 其中满足 $1$ 但不满足 $2$ 的数量，也就是是 $k$ 的倍数但是 存在 $p<k$ 并且 $p\mid k$。
   - 所以 $f(n,k)=\lfloor \frac{n}{k}\rfloor -\sum_{i=1}^{\min(k-1,\lfloor\frac{n}{k}\rfloor)}f(n/k,i)$，其中 $f(n,k)$ 表示示 $1$ 到 $n$ 中满足最小质因子为 $k$ 的数的数量。
   - 当然因为 $k$ 为合数的时候，答案为 $0$。所以当 $i \in p$ 时才会对答案产生贡献。
### Part.3 代码 
~~只有一点注释，管理不要嫌弃。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
int l, r, k;
bool p(int x) { // 快速判断素数。
    int sq = sqrt(x);
    for(int i = 2 ; i <= sq; i ++)
        if(x % i == 0) return false;
    return true;
}
int f(int n, int k) {
    if (!p(k)) return 0;
    if (n < k) return 0; // 不可能。
    int ans = n / k; // 答案。
    for (int i = 2; i <=  min(n / k, k - 1); i++)
        ans -= f(n / k, i); // 容斥原理。
    return ans;
}

int main() {
    cin >> l >> r >> k;
    cout <<f(r, k) - f(l - 1, k) << '\n'; // 类似于前缀和
    return 0;
}
```

---

## 作者：Yuby (赞：0)

[题面](https://www.luogu.com.cn/problem/CF83D)

点数：2400

## 分析

不妨设 $i=k\prod p_i^{\alpha_i}$，$j\in [2,k-1]$。如果有 $j\mid i$，那必然有 $j\mid pk$。

如果 $k$ 不是质数，那必有质数 $q$ 满足 $q\in [2,\sqrt k]$，就有 $q\mid i$，所以无解。

那么考虑 $k$ 为质数的情况。

若满足要求，则 $i$ 的最小质因子必然为 $k$。那么设 $f(x,k)$ 表示 1 到 $x$ 中满足最小质因子为 $k$ 的数的数量，最终答案用 $f(r,k)-f(l-1,k)$ 即可。考虑容斥。将所有为 $k$ 的倍数但最小质因子更小的数减去，即为答案，即：

$f(x,k)=\left\lfloor\dfrac{x}{k}\right\rfloor-\sum_{i=2}^{\min(k-1,x/k)} f(\left\lfloor\dfrac{x}{k}\right\rfloor,i)$

注意当 $i$ 不为质数时直接返回 0。意味着每次最多扩展出 $\sqrt x$ 个状态，缩减非常快，$2\times 10^9$ 只需要 5 次即可。可以通过。

核心代码：


```cpp
ll l,r,k;
bool check(ll x)
{
	for(ll i=2;i*i<=x;i++)
		if(x%i==0)return 0;
	return 1;
}
ll f(ll x,ll y)
{
	if(!check(y))return 0;
	ll res=x/y;
	for(ll i=2;i<=min(x/y,y-1);i++)
		res-=f(x/y,i);
	return res;
}
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	l=read(),r=read(),k=read();
	write(f(r,k)-f(l-1,k));
	return 0;
}
```



---

