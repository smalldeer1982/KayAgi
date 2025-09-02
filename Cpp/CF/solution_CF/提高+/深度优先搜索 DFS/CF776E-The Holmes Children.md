# The Holmes Children

## 题目描述

The Holmes children are fighting over who amongst them is the cleverest.

Mycroft asked Sherlock and Eurus to find value of $ f(n) $ , where $ f(1)=1 $ and for $ n>=2 $ , $ f(n) $ is the number of distinct ordered positive integer pairs $ (x,y) $ that satisfy $ x+y=n $ and $ gcd(x,y)=1 $ . The integer $ gcd(a,b) $ is the greatest common divisor of $ a $ and $ b $ .

Sherlock said that solving this was child's play and asked Mycroft to instead get the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF776E/1a109f1de0f9bab1129f477d3f3eae085caca16a.png). Summation is done over all positive integers $ d $ that divide $ n $ .

Eurus was quietly observing all this and finally came up with her problem to astonish both Sherlock and Mycroft.

She defined a $ k $ -composite function $ F_{k}(n) $ recursively as follows:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF776E/bd985db890d6882c9f46cc152e6a148e4e80dbfa.png)She wants them to tell the value of $ F_{k}(n) $ modulo $ 1000000007 $ .

## 说明/提示

In the first case, there are $ 6 $ distinct ordered pairs $ (1,6) $ , $ (2,5) $ , $ (3,4) $ , $ (4,3) $ , $ (5,2) $ and $ (6,1) $ satisfying $ x+y=7 $ and $ gcd(x,y)=1 $ . Hence, $ f(7)=6 $ . So, $ F_{1}(7)=f(g(7))=f(f(7)+f(1))=f(6+1)=f(7)=6 $ .

## 样例 #1

### 输入

```
7 1
```

### 输出

```
6```

## 样例 #2

### 输入

```
10 2
```

### 输出

```
4```

# 题解

## 作者：Siyuan (赞：6)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-776E-The-Holmes-Children/)

---

## Description

> 题目链接：[Codeforces 776E](https://codeforces.com/contest/776/problem/E)

Holmes 的孩子们在争论谁才是他们中最聪明的。

Mycroft 提出了如下的函数求值问题：已知 $f(1)=1$，且当 $n\ge 2$ 时，$f(n)$ 表示满足 $x+y=n$ 的互质的正整数对 $(x,y)$ 的对数，$g(n)=\sum_{d\mid n}f\left(\frac{n}{d}\right)$。

她定义了一个函数 $F_k(n)$，其值可以通过如下式子递归求解：
$$F_k(n)=\begin{cases}f(g(n)) & k=1 \\g(F_{k-1}(n)) & k>1,k\bmod 2=0 \\f(F_{k-1}(n)) & k>1,k\bmod 2 =1\end{cases}$$
现在她希望你对于给定 $n,k$，求出 $F_k(n)\bmod 1000000007$ 的值。

数据范围：$1\le n,k\le 10^{12}$

------

## Solution

我们先推导一下 $f(n)$ 和 $g(n)$ 函数到底长成什么样子：
$$\begin{aligned}f(n) & =\sum_{i=1}^{n-1} [\gcd(i,n-i)=1] \\&=\sum_{i=1}^{n-1}[\gcd(i,n)=1] \\&=\varphi(n)\end{aligned}$$
由于 $f(n)$ 就是 $\varphi(n)$ 函数，那么 $g(n)$ 函数可以通过如下式子表示：
$$\begin{aligned}g(n) & =\sum_{d\mid n} f\left(\frac{n}{d}\right) \\& = \sum_{d\mid n} \varphi\left(\frac{n}{d}\right)\end{aligned}$$
显然这是一个卷积的形式：
$$g=\varphi\ast 1=\texttt{ID}$$
因此 $g(n)=n$！

那么递归式变为：
$$F_k(n)=\begin{cases}\varphi(n) & k=1 \\F_{k-1}(n) & k>1,k\bmod 2=0 \\\varphi(F_{k-1}(n)) & k>1,k\bmod 2 =1\end{cases}$$
我们可以找规律发现，$F_k(n)$ 的值就是对 $n$ 求 $\left\lfloor\frac{k+1}{2}\right\rfloor$ 次 $\varphi$ 函数。

显然我们不能真的求 $O(k)$ 次 $\varphi$，由于 $n$ 求 $O(\log n)$ 次 $\varphi$ 的值就是 $1$，此时再求 $\varphi$ 就没有意义了。故我们只需要求 $\max\left(\log n,\left\lfloor\frac{k+1}{2}\right\rfloor\right)$ 次 $\varphi$ 即可。

**时间复杂度**：$O\left(\max\left(\log n,\left\lfloor\frac{k+1}{2}\right\rfloor\right)\sqrt n\right)$

------

## Code

```cpp
#include <cstdio>

const int N=1e6+5;
int tot,p[N];
bool flg[N];

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
long long phi(long long x) {
	long long ans=x;
	for(int i=1;i<=tot&&1LL*p[i]*p[i]<=x;++i) {
		if(x%p[i]) continue;
		ans=ans/p[i]*(p[i]-1);
		while(x%p[i]==0) x/=p[i];
	}
	if(x>1) ans=ans/x*(x-1);
	return ans;
}
int main() {
	sieve(N-5);
	long long n,k;
	scanf("%lld%lld",&n,&k);
	k=(k+1)/2;
	for(long long i=1;i<=k&&n>1;++i) {
		n=phi(n);
	}
	printf("%lld\n",n%1000000007);
	return 0;
}
```





---

## 作者：1saunoya (赞：3)

欧拉函数

我们考虑这个分段函数



$$f_i = \sum_{i=1}^{n-1} [\gcd(n,n-i)==1]$$

$$=\sum_{i=1}^{n-1}[\gcd(n,i)==1]$$

然而就是欧拉函数 $\varphi$

那么考虑 $g_n = \sum_{d|n} \varphi (d)$

考虑 $\varphi(n)$ 的实际意义是 $[1,n-1]$ 有多少个和 $n$ 互质的数字


定义 $S = {d|d\in [1,n] , d|n}$

因为 $g_n = \sum_{d|n} \varphi (d) = \sum_{d|n} \varphi(\frac{n}{d})$


所以 $g_n$ 的实际意义就是与 $n$ 的 $\gcd$ 为 $S$ 中的元素的个数

即 $g_n = \sum_{i=1}^{n} [\gcd(i,n) \in S]$

易证答案是 $g_n = n$

考虑到奇数时才进行欧拉函数，偶数次又不影响，但是 $k$ 的限制又很大，所以考虑 $\varphi$ 的性质，因为经过至多 $\log$ 次会使得原数变成 $1$，特殊的，$\varphi (1) =1$ ，所以 $k$ 是假的

```cpp
// powered by c++11
// by Isaunoya

#include<bits/stdc++.h>
#define rep(i , x , y) for(register int i = (x) ; i < (y) ; i ++)
using namespace std ;
using db = double ;
using ll = long long ;
using uint = unsigned int ;
#define int long long
using pii = pair < int , int > ;
#define ve vector
#define Tp template
#define all(v) v.begin() , v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
#define fir first
#define sec second

// the cmin && cmax
Tp < class T > void cmax(T & x , const T & y) {
	if(x < y) x = y ;
}
Tp < class T > void cmin(T & x , const T & y) {
	if(x > y ) x = y ;
}

// sort , unique , reverse
Tp < class T > void sort(ve < T > & v) {
	sort(all(v)) ;
}
Tp < class T > void unique(ve < T > & v) {
	sort(all(v)) ;
	v.erase(unique(all(v)) , v.end()) ;
}
Tp < class T > void reverse(ve < T > & v) {
	reverse(all(v)) ;
}

int qwq(int x) {
	int res = x ;
	for(int i = 2 ; i <= sqrt(x) ; i ++) {
		if(! (x % i)) {
			res = res / i * (i - 1) ;
			while(! (x % i)) x /= i ;
		}
	}
	if(x > 1) res = res / x * (x - 1) ;
	return res ;
} 
signed main() {
	ios_base :: sync_with_stdio(false) ;
	cin.tie(nullptr) , cout.tie(nullptr) ;
// code begin.
	int n , k ;
	cin >> n >> k ;
	while(k && n > 1) {
		if(k & 1) n = qwq(n) ;
		k -- ;
	}
	cout << n % 1000000007 << '\n' ;
	return 0 ;
// code end.
} 
```

---

## 作者：_sunkuangzheng_ (赞：2)

**【题目分析】**

首先推第一个式子：

$$\begin{aligned}f(n) & = \sum\limits_{i=1}^{n-1}[\gcd(i,n-i) = 1] \\ & = \sum\limits_{i=1}^{n-1}[\gcd(i,n) = 1] \\ & = \varphi(n)\end{aligned}$$

这里我们对第一步进行证明：

假设 $\gcd(i,n-i) = 1$ 且 $\gcd(i,n) = d(d > 1)$，则设 $i = k_1d,n = k_2d$，易得 $n-i = (k_2 - k_1)d$，此时 $\gcd(i,n-i) \ge d$，与假设矛盾。将条件与结论颠倒证明也成立，故原式成立。

接下来推第二个式子：

$$\begin{aligned}g(n) & = \sum\limits_{d|n}f(\dfrac{n}{d}) \\ & = \sum\limits_{d|n}\varphi(\dfrac{n}{d})\\ & = n\end{aligned}$$

因此我们发现原来的 $F_k(n)$ 化为以下形式：

$$F_k(n)=\begin{cases}1&k=1\\F_{k-1}(n)&k > 1 \operatorname{and} k \bmod 2 = 0\\F_{k-1}(\varphi(n))&k > 1 \operatorname{and} k \bmod 2 = 1\end{cases}$$

也即对 $n$ 求 $\lfloor \dfrac{k+1}{2} \rfloor$ 次欧拉函数。

注意到当 $n = 1$ 时，$\varphi(n) = 1$，因此当 $n = 1$ 时退出程序即可。

最后，强调本题的重点：**答案对 $10^9+7$ 取模**！

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
const int mod = 1e9+7;
int get(int x){
    int ans = x;
    for(int i = 2;i * i <= x;i ++){
        if(x % i == 0){
            ans = ans / i * (i - 1) ;
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) ans = ans  / x * (x - 1);
    return ans;
}
signed main(){
    cin >> n >> k;
    k = (k + 1) / 2;
    while(k --){
        n = get(n);
        if(n == 1) return cout << 1,0;
    }
    return cout << n % mod,0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF776E The Holmes Children](https://www.luogu.com.cn/problem/CF776E)

## 解题思路

1. 化简 $f(n)$：

$$
\begin{aligned}
f(n) &= \sum_{i=1}^{n-1}[\gcd{(i,n-i)}=1] \\
  &= \sum_{i=1}^{n-1}[\gcd{(i,n)}=1] \\
  &= \sum_{i=1}^{n}[\gcd{(i,n)}=1] \\
  &= \varphi(n)
\end{aligned}
$$

2. $f(n)=\varphi(n)$ 就是欧拉函数，而 $g(n)$ 是 $\varphi(n)$ 的和函数，即 $id(n)=n$：

$$
\begin{aligned}
g(n) &= \sum_{d\mid n}\varphi(d) \\
  &= id(n) \\
  &= n
\end{aligned}
$$

> 证明：$n$ 个分数 $\frac{1}{n},\frac{2}{n},\cdots,\frac{n}{n}$ 互不相等。考虑化简这些分数，得到新的 $n$ 个分数，他们的分母和分子互质，形如 $\frac{a}{d},d\mid a$ 且 $a$ 与 $d$ 互质。在所有 $n$ 个分数中，分母为 $d$ 的分数有 $\varphi(d)$ 个。所有不同分母的分数，其总数为 $\sum_{d\mid a}\varphi(d)=n$。

3. 将 $f(n)=\varphi(n)$ 和 $g(n)=n$ 代入 $F_k(n)$ 并化简：

$$
F_k(n) = \begin{cases}
  \varphi(n) & k=1 \\
  F_{k-1}(n) & k>1,k\bmod 2=0 \\
  \varphi(F_{k-1}(n)) & k>1,k\bmod 2=1
\end{cases}
$$

4. 将 $F_k(n)$ 打表：

| $F_k(n)$ | $F_1(n)$ | $F_2(n)$ | $F_3(n)$ | $F_4(n)$ | $F_5(n)$ | $F_6(n)$ | $F_7(n)$ | $F_8(n)$ |
| -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |
| 实际函数 | $\varphi(n)$ | $\varphi(n)$ | $\varphi(\varphi(n))$ | $\varphi(\varphi(n))$ | $\varphi(\varphi(\varphi(n)))$ | $\varphi(\varphi(\varphi(n)))$ | $\varphi(\varphi(\varphi(\varphi(n))))$ | $\varphi(\varphi(\varphi(\varphi(n))))$ |
| 嵌套次数 | $1$ | $1$ | $2$ | $2$ | $3$ | $3$ | $4$ | $4$ |

5. 不难发现，$F_k(n)$ 就是对 $n$ 嵌套 $\left\lfloor \frac{k+1}{2} \right\rfloor$ 次 $\varphi(n)$。

6. 由于经过若干次嵌套后会一直重复 $\varphi(1)=1$，所以当 $n$ 变为 $1$ 后可以跳过后面的嵌套，实际嵌套次数为 $O(\log{n})$ 级别。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
ll phi(ll n)
{
    ll res=n;
    for(ll i=2;i*i<=n;i++)
    {
        if(n%i==0) 
        {
            res=res/i*(i-1);
            while(n%i==0)n/=i;
    	}
    }
    if(n>1)res=res/n*(n-1);
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,k;
    cin>>n>>k;
    k=(k+1)/2;
    while(k--&&n>1)n=phi(n);
    cout<<n%mod<<'\n';
    return 0;
}
```

---

## 作者：__O_v_O__ (赞：1)

考虑更相减损：

$$\gcd(a,b)=\gcd(b,a-b)(a>b)$$

则 $f(n)=\sum\limits_{i=1}^n[\gcd(i,n)=1]$。

所以我们可以得知 $f(n)$ 是在求 $1\sim n$ 中与 $n$ 互质的数的个数，即 $\varphi(n)$。

再看 $g(n)$：$g(n)=\sum_{d|n}\varphi(n/d)$。

则 $g(n)$ 求的是 $\sum\varphi$（$n$ 的因数），根据 $\varphi$ 的意义理解，易知 $g(n)=n$。

那么递归式变为：

$$F_k(x)=\begin{cases}\varphi(n)&k=1\\F_{k-1}(n)&k>1, k\bmod 2=0\\\varphi(F_{k-1}(n))&k>1,k\bmod 2=1\end{cases}$$

观察得 $F_{k}(n)$ 其实就是对 $n$ 求 $\dfrac{k+1}{2}$ 次 $\varphi$。

但是这个做法的复杂度是 $O(k)$ 的，显然超时。

我们就需要用到一个 $\varphi$ 的性质：

- 对于任意整数 $i$ 都有 $\varphi(\varphi(i))\leq \dfrac{i}{2}$。

证明：我们分两种情况讨论。

1. 若 $i$ 含因子2，则 $\varphi(i)$ 必小于等于 $\dfrac{i}{2}$(因为至少要乘1/2)，此时 $\varphi(\varphi(i))\leq \varphi(i)$，所以 $\varphi(\varphi(i))\leq \dfrac{i}{2}$，得证。

2. 若 $i$ 不含因子2，则 $\varphi(i)\leq i$，同理，此时 $\varphi(\varphi(i))$ 必小于等于 $\dfrac{\varphi(i)}{2}$，所以 $\varphi(\varphi(i))\leq \dfrac{i}{2}$，得证。

由这个性质，我们可以知道，$k$ 最多进行 $\log k$ 次操作就会变成 $1$，而 $\varphi(1)=1$ 所以当 $n$ 变成 $1$ 后，我们就可以直接 `break` 掉，时间复杂度 $O(\min(\log k,\dfrac{k-1}{2})\sqrt n)$，能过。

## code:
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long //这样代码最短...
int n,k,num;
int ph(int x){//phi(求1~n中与n互质的数个数)
	int ans=x;
	afor(i,2,sqrt(x),STB){//枚举质因子
		if(x%i==0){
			ans=ans/i*(i-1);
			while(x%i==0)x/=i;//把所有质因子i去掉
		}
	}if(x>1)ans=ans/x*(x-1);//还有剩下的质因子
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin>>n>>k;
	for(;k>0;k-=2){if(n>1)n=ph(n);else break;}
	cout<<n%1000000007;//注意取模
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

诈骗题。

### 思路

震惊地发现根据更相减损法 $f(n)=\sum_{i=1}^n[\gcd(i,n-i)=1]=\sum_{i=1}^n[\gcd(i,n)=1]=\varphi(n)$。

再次震惊地发现根据欧拉定理 $g(n)=\sum_{d\mid n} \varphi(\frac{n}{d})=n$。

所以答案相当于输出 $n$ 的 $\lceil \frac{k}{2}\rceil$ 次嵌套。

但是直接去做会超时，因为 $k\le 10^{12}$，即使能够 $O(1)$ 求出任何 $\varphi(n)$，这也是会超时的。不过我们可以观察 $O(\sqrt n)$ 求 $\varphi(n)$ 的公式，可以发现：

- 如果 $2 \nmid n$，则 $2\mid \varphi(n)$。
- 如果 $2 \mid n$，则 $\varphi(n)\le \frac{n}{2}$。

因此如果 $k\ge \log n$ 则直接特判输出 $1$ 即可。总时间复杂度为 $O(\sqrt n\log n)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, k, ans, x;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	ans = n;
	if (k >= 60) {
		cout << "1";
		return 0;
	}
	for (int i = 1; i <= k; i += 2) {
		x = ans;
		for (int j = 2; j * j <= ans; j++) {
			if (ans % j) continue;
			ans /= j;
			while (ans % j == 0) ans /= j;
			x = x / j * (j - 1);
		}
		if (ans > 1) x = x / ans * (ans - 1);
		ans = x;
	}
	cout << ans % 1000000007;
	return 0
}
```

---

## 作者：ZeroOf149 (赞：0)

# [CF776E The Holmes Children](https://www.luogu.com.cn/problem/CF776E)

## 题目描述

定义 $f(n), g(n), F_k(n)$ 如下：  
$$\begin{aligned}
& f(n) = \begin{cases}
 1 & \text{if } n = 1 \\
\displaystyle\sum_{i=1}^{n-1}[\gcd(i, n - i) = 1] & \text{otherwise}
\end{cases} \\
& g(n) = \sum_{d\mid n}f\left(\dfrac{n}{d}\right) \\
& F_k(n) = \begin{cases}
f(g(n)) & \text{if } k = 1 \\
g(F_{k-1}(n)) & \text{if } 2 \mid k \\
f(F_{k-1}(n)) & \text{otherwise}
\end{cases}
\end{aligned}$$

给定 $n, k$，求 $F_k(n) \bmod{(10^9+7)}$。 
其中 $n, k \leq 10^{12}$。

## 解法说明

我们约定 $f^{(k)}(n)$ 表示 $\overbrace{f(f(\cdots f(n) \cdots))}^{k\text{ } 层嵌套}$，$\operatorname{id}(n) = n, \mathbb{1}(n) = 1, \varepsilon(n) = [n=1]$。  
有狄利克雷卷积 $f * g = \displaystyle\sum_{d\mid n} f(d)g\left(\dfrac{n}{d}\right)$ 对积性函数满足交换律与结合律。

熟知更相减损法 $\gcd(i, n) = \gcd(i, n - i)$，立刻有 $f(n) = \varphi(n)$。  
根据狄利克雷卷积的经典结论，我们知道 $\varphi = \mu * \operatorname{id}, \mu * \mathbb{1} = \varepsilon$，所以 $g = \mathbb{1} * \varphi = \mu * \operatorname{id} * \mathbb{1} = \varepsilon * \operatorname{id} = \operatorname{id}$，这就是说 $g(n) = n$。  
此时 $F_k(n)$ 自然地变成了 $\varphi^{(\frac{k+1}{2})}(n)$。如果你此时暴力地计算，复杂度大约 $\Theta(k\sqrt{n})$，显然无法通过本题。  
我们观察到如下事实：  
   - 当 $2 \mid n$ 时，所有偶数都不与 $n$ 互质，有 $\varphi(n) \leq \dfrac{n}{2}$；
   - 当 $2 \nmid n$ 时，有 $\varphi(n) = n \displaystyle\prod_{p 是 n 的素因子}\left(1 - \dfrac{1}{p}\right)$，所以此时有 $2 \mid \varphi(n)$，进而 $\varphi(\varphi(n)) \leq \dfrac{n - 1}{2}$。

因此，迭代 $n \gets \varphi(n)$ 直到 $n = 1$ 需要的次数是 $\Theta(\log n)$ 的。我们只需要在 $n = 1$ 时结束迭代就可做到大约 $\Theta(\sqrt{n}\log n)$ 的复杂度，可以通过本题。

## 代码实现

```cpp
#include <algorithm>
#include <cstdio>

using ll = long long;

constexpr int Mod = 1e9 + 7;

ll phi(ll n) {
  ll res = n;
  for (ll d = 2; d <= n / d; ++d)
    if (n % d == 0) {
      res = res / d * (d - 1);
      while (n % d == 0) n /= d;
    }
  if (n > 1) res = res / n * (n - 1);
  return res;
}

ll n, k;

int main() {
  scanf("%lld %lld", &n, &k);
  k = (k + 1) >> 1;
  while (n != 1 && k--) n = phi(n);
  printf("%lld", n % Mod);
}
```

---

## 作者：Linge_Zzzz (赞：0)

# Sol

打表发现 $f(n)$ 是积性函数，且 $g(n)=n$。将这些代入递推式，可以发现 $F_k(n)$ 就是 $f(n)$ 的 $\lceil\frac{k}{2}\rceil$ 次复合后得到的结果。

仔细观察可以发现当 $p$ 为质数时 $f(p^k)=(p-1)p^{k-1}$，于是我们可以 $O(\sqrt n)$ 求出来 $f(n)$。

结合 $f(1)=1$，$f(n)<n$，我们可以每次 $O(\sqrt n)$ 求 $f(n)$ 一直求 $k$ 次，中途如果 $n=1$ 就退出，交上去发现过了。

考虑证明。

首先根据更相减损术，有 $\gcd(i,n-i)=\gcd(n,i)$，于是 $f(n)=\sum_{i=1}^{n-1}[\gcd(i,n)=1]$，这不是我们欧拉函数吗。

根据欧拉函数的性质，有 $g(n)=\sum_{d\mid n}\varphi(\frac{n}{d})=\sum_{d\mid n}\varphi(d)=n$。

那么时间复杂度是多少呢？

考虑对 $n$ 分类讨论：
+ 当 $n\neq 1$ 为奇数：$\varphi(n)=n\prod(\frac{p_i-1}{p_i})$，$p_i-1$ 为偶数，那么 $\varphi(n)$ 为偶数。
+ 当 $n$ 为偶数：那么一定有 $\frac{n}{2}$ 个偶数与 $n$ 不互质，$\varphi(n)<\frac{n}{2}$。

所以其一定在 $O(\log n)$ 次复合后变为 $1$。

总时间复杂度：$O(\sqrt n\log n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=1e6+10,T=22,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7,pmod=mod-1;
int qpow(int a,int k){
	int res=1;
	while(k){
		if(k&1)res=res*a;
		a=a*a;
		k>>=1;
	}
	return res;
}
int f(int n){
	int ans=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0)n/=i;
		}
	}
	if(n>1)ans=ans/n*(n-1);
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,k;
	cin>>n>>k;
	k=(k+1)/2;
	while(k--&&n>1)n=f(n);
	cout<<n%mod<<endl;
	return 0;
}
```

---

## 作者：Enderich (赞：0)

## 思路

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF776E/bd985db890d6882c9f46cc152e6a148e4e80dbfa.png)

很明显的数学题了，可以先化简一下 $f(n)$ 和 $g(n)$。

根据题意，$f(n)$ 表示满足 $x+y=n$ 的互质的正整数对 $(x, y)$ 的对数。但当我们知道 $x$ 的时候肯定也知道 $y$ 了，且 $y=n-x$。所以就可以化简成求 $x$ 与 $n-x$ 互质的对数，也就是 $x$ 与 $n$ 互质的对数，也就是 $\varphi(n)$。所以就可以得到 $f(n)=\varphi(n)$。

再来看 $g(n)$，这个就很好化简了。$g(n)=\sum_{d|n}f(\frac{n}{d})=\sum_{d|n}\varphi(\frac{n}{d})=n$，这个应该是最基本的证明了罢。

所以最后就可以得到 $F_k(n)$ 就是对 $n$ 求 $k$ 次欧拉函数的值，那直接根号的暴力就行了。

## code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
int phi(int n)
{
	int ans=n;
	for(int i=2;i*i<=n;i++)
	{
		if(!(n%i))
		{
			ans=(ans/i*(i-1));
			while(!(n%i)) n/=i;
		}
	}
	if(n>1) ans=(ans/n*(n-1));
	return ans;
}
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
void solve()
{
	int n=read(),k=read();
	for(int i=1;i<=(k+1)/2;i++)
	{
		if(n==1) break;
		n=phi(n);
	}
	printf("%lld",n%MOD);
}
signed main()
{
	solve();
	return 0;
}


```
## The End

---

## 作者：hwk0518 (赞：0)

$f(n)$

$=\sum_{i=1 \to n-1}[gcd(i,n-i)=1]$

$=\sum_{i=1 \to n-1}[gcd(i,n)=1]$

$=\phi(n)$

$g(n)$

$=\sum_{d|n}f(d)$

$=\sum_{d|n}\phi(d)$

$=n$

于是$F_k(n)$即为将$n$求$k$次欧拉函数后的值。注意到能使$F_k(n)$不为$1$的$k$是$log n$级别的。每次$O(\sqrt{n})$暴力求欧拉函数即可。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

long long n,k;

long long phi(long long x)
{
	int i;long long tx=x;
	for(i=2;1LL*i*i<=x;++i)
		if(tx%i==0)
		{
			while(tx%i==0) tx/=i;
			x=x/i*(i-1);
		}
	if(tx>1) x=x/tx*(tx-1);
	return x;
}

int main()
{
	long long i;
	scanf("%lld%lld",&n,&k);
	for(i=1;i<=k;i+=2)
	{
		n=phi(n);
		if(n==1) break;
	}
	printf("%lld\n",n%1000000007);
	return 0;
}

```

---

