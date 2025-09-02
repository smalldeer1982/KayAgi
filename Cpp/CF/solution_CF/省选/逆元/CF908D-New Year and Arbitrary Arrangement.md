# New Year and Arbitrary Arrangement

## 题目描述

You are given three integers $ k $ , $ p_{a} $ and $ p_{b} $ .

You will construct a sequence with the following algorithm: Initially, start with the empty sequence. Each second, you do the following. With probability $ p_{a}/(p_{a}+p_{b}) $ , add 'a' to the end of the sequence. Otherwise (with probability $ p_{b}/(p_{a}+p_{b}) $ ), add 'b' to the end of the sequence.

You stop once there are at least $ k $ subsequences that form 'ab'. Determine the expected number of times 'ab' is a subsequence in the resulting sequence. It can be shown that this can be represented by $ P/Q $ , where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/250bff4a0d2d6149565f6e795de0dbd59e6a92a3.png). Print the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/962b3e429ab173c8d460f96cc849d01fcd4a9d47.png).

## 说明/提示

The first sample, we will keep appending to our sequence until we get the subsequence 'ab' at least once. For instance, we get the sequence 'ab' with probability 1/4, 'bbab' with probability 1/16, and 'aab' with probability 1/8. Note, it's impossible for us to end with a sequence like 'aabab', since we would have stopped our algorithm once we had the prefix 'aab'.

The expected amount of times that 'ab' will occur across all valid sequences is 2.

For the second sample, the answer is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF908D/be8bc2d2b5b20d19237dcaabfc3c3ca4bcb22ac0.png).

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 1 4
```

### 输出

```
370000006
```

# 题解

## 作者：Altwilio (赞：36)

upd 2024.2.18 修改笔误
### $0.$ 前言
有一天 Au 爷讲期望见到了此题，通过写题解来加深理解。

### $1.$ 题意
将初始为空的序列的末尾给定概率添加 $a$ 或 $b$，当至少有 $k$ 对 $ab$ 时停止（注意是“对”，中间可以间隔字符），求 $ab$ 期望对数。

### $2.$ 思路
~~通过查看标签~~ 通过阅读题面我们容易发现本题是一道期望 DP，但是本题的状态并不很容易想到，设 $f[i][j]$ 表示前缀中有 $i$ 个 $a$，$j$ 个 $ab$ 停止后的期望个数，这样发现转移就容易了很多，不会被 $a$ 和 $b$ 纠缠不清，设 $A = pa / (pa + pb)$，$B = pb / (pa + pb)$，则有：

$$f[i][j] = A × f[i + 1][j] + B × f[i][j + i]$$

若 $i + j ⩾ k$，则再加一个 $b$ 就会结束，此时的期望 $ab$ 数是：

$$i + j + pa / pb$$

故终止状态为:

$$f[i][j] = i + j + pa / pb, i + j ⩾ k$$

### $3.$ 解释
（本块主要针对 $i + j + pa / pb$ 的推导，不感兴趣可以跳过）

我一直疑惑 $i + j + pa / pb$ 如何得出。

解释一下，在前缀有了 $i$ 个 $a$，构成了 $j$ 组 $ab$ 的情况下，若 $i + j ⩾ k$，这个状态的后继情况能是容易看到的：选 $a$ ，然后继续抉择，或选 $b$ ，就此停止。多选一个 $a$，就意味着最后的 $ab$ 串又多了一个。 那么得出无限和式:

$${b \over pa+pb}×\sum_{a=0}^{∞}(i+j+a)×({pa \over pa+pb})^{a}$$

接下来的证明部分参考[一粒夸克](https://www.luogu.com.cn/user/483966)的博客

#### 首先是等差乘等比数列求和公式
$$(1):A=a+(a+p)×p+(a+2×b)×p^2+...+(a+n×b)×p^n$$
$$(2):A×p=a×p+(a+b)×p^2+(a+2×b)×p^3+...+(a+n×b)×p^{n+1}$$
$$(1)-(2):A×(1-p)=a+b×(p+p^2+p^3+...+p^n)-(a+n×b)p^{n+1}$$
$$A×(1-p)=a+b×p×{1-p^n \over 1-p}-(a+n×b)×p^{n+1}$$
$$A={a\over1-p}+b×{p-p^{n+1}\over(1-p)^2}-{(a+n×b)×p^{n+1}\over1-p}$$
#### 将公式代入无限和式
$${pb \over pa+pb}×(\sum_{a=0}^{∞}(i+j+a)×({pa \over pa+pb})^{a})$$
$$={pb\over pa+pb}×({i+j\over1-{pa\over pa+pb}}+{{pa \over pa+pb}-({pa \over pa+pb})^{∞+ 1} \over (1-{pa \over pa+pb})^2}-{(i+j+n)×({pa \over pa+pb})^{∞+1} \over1-{pa \over pa+pb}})$$
$$={pb\over pa+pb}×({i+j \over {pb \over pa+pb}}+{{pa \over pa+pb}-({pa \over pa+pb})^{∞+ 1} \over ({pb \over pa+pb})^2}-{(i+j+n)×({pa \over pa+pb})^{∞+1} \over{pa \over pa+pb}})$$
$$=i+j+{{pa \over pa+pb}-({pa \over pa+pb})^{∞+ 1} \over {pb \over pa+pb}}-(i+j+n)×({pa \over pa+pb})^{∞+ 1}$$
$$=i+j+{{pa \over pa+pb}\over {pb \over pa+pb}}$$
$$=i+j+{pa \over pb}$$
（这么巨量$\LaTeX$我都打了，求赞）
### $4.$ 细节
1. 由于 $f[0][0]$ 会转移到自己，递归记忆化会死循环，从 $f[1][0]$ 开始算，当序列前有一堆 $b$ 的情况没有意义，可以跳到第一个 $a$ 发生时开始算。初始状态选取 $f[1][0]$。
1. 当 $a$ 与 $ab$ 的个数相加已经大于 $k$ 了，这时就不关心有多少 $a$ 了，只需要有一个 $b$ 就可以结束了，这样可以把两维都控制在 $O(k)$ 的复杂度

### $5.$ 代码
这是一份逆推实现的代码：
```cpp
#include<map>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;

template<class T> inline void read(T &x){
    x = 0; register char c = getchar(); register bool f = 0;
    while(!isdigit(c)) f ^= c == '-', c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if(f) x = -x;
}

template<class T> inline void print(T x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar('0' + x % 10);
}

const int N = 1010;
const int mod = 1e9 + 7;
int n, pa, pb, A, B, C;
int f[N][N];

inline int qpow(int a, int b){
    int res = 1;
    while(b){
        if(b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod, b >>= 1;
    }
    return res;
}

inline int work(int x){
	return qpow(x, mod - 2);
}

signed main(){
	read(n), read(pa), read(pb);
    A = 1ll * pa * work(pa + pb) % mod;
    B = 1ll * pb * work(pa + pb) % mod;
    C = 1ll * pa * work(pb) % mod;
    for(int i = n; i >= 1; --i)
        for(int j = n; j >= 0; --j){
            if(i + j >= n) f[i][j] = (i + j + C) % mod;
            else f[i][j] = (1ll * A * f[i + 1][j] % mod + 1ll * B * f[i][j + i] % mod) % mod;
        }
    print(f[1][0]), puts("");
    return 0;
}
```
这是一份记搜实现的代码片段：
```cpp
inline int dp(int i, int j){
	if(i + j >= k) return (i + j + C) % mod;
	if(~ f[i][j]) return f[i][j];
	return (1ll * A * dp(i + 1, j) + 1ll * B * dp(i, j + i)) % mod;
}
```



---

## 作者：优秀的渣渣禹 (赞：27)

##### 蒟蒻渣渣禹小心翼翼发布题解。。。。
	  这道题，嗯，期望，dp，好，我们有思路了。。。。
#### however，
#### 主要问题在于字符串无限延伸，so，我们需要考虑记录前缀的关键量来为DP设置终止状态。
我们不妨设f[i][j]表示前缀中有i个a和j个ab停止后的期望长度，设 A = pa / (pa + pb)，B = pb / (pa + pb)。这样推方程就容易很多。
##### 状态转移方程：f[i][j] = A * f[i + 1][j] + B * f[i][i + j]
	接下来只用解决两个问题：
#### 1.终止状态：
	当i+j>=k时，再加一个b就会终止，期望为i+j+c，其中：
##### c=0*B+1*A*B+2*A^2*B+...+∞*A^∞*B
	这是等差×等比数列，运用高中数学的错位相减法（特别的，A^∞=0），可以得到：
#### c=pa/pb
#### 故有终止状态f[i][j]=i+j+pa/pb，i+j>=k。
#### 2.初始状态：
	初始空字符串为f[0][0]，但是会发现f[0][0]会从f[0][0]本身转移。
    其原因是没有a时会无限加b，解决办法是初始状态设为f[1][0]。
代码如下qwq：
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#define LL long long
const int m = 1e9 + 7,N = 1005;
void gcd(int a,int b,int&x,int &y){
    if(!b){
		x = 1;
		y = 0;
		}
    else
	{
		gcd(b,a % b,y,x);
		y -= x * (a / b);
	}
}
int inv(int a)
{
	int x,y;
	gcd(a,m,x,y);
	return (x % m + m) % m;
}
LL f[N][N],k,pa,pb,A,B,C;
int main(){
    scanf("%d %d %d",&k,&pa,&pb);
    A = (pa * inv(pa + pb) % m);
	B = (1 - A + m) % m;
	C = (pa * inv(pb) % m);
    for(int i = k;i >= 1;i--)
		for(int j = k;j >= 0;j--)
        	f[i][j] = i + j >= k ? (i + j + C) % m : (A * f[i + 1][j] + B * f[i][i + j]) % m;
    printf("%d",f[1][0]);
    return 0;
}
```
各位大佬点个赞吧。。。。


---

## 作者：hs_black (赞：24)



## 解题思路

切了这道题感觉自信++，好像事和别人不一样的正推方法呢

考虑动态规划，容易发现无限放 a 和 b 的情况不是很好处理。但是！我们就是要正着推！

首先容易发现开头放多少个 b 对答案都没有影响，所以我们钦定第一个放 a。

设 $f[x][y]$ 表示放了 x 个 a，获得了 y 个子序列的概率，枚举下一个放 a 还是 b 有
$$
f[x+1][y] += f[x][y] \times P_a
$$
$$
f[x][y+x] += f[x][y] \times P_b
$$
那么当 $y + x \ge k$ 时，直接把概率乘上 $y+x$ 加到答案上。

还有一个问题，当 dp 到 $f[k][x]$ 时，显然再加入一个 b 都会满足条件，但是仍然存在可能使得无限放 a 的可能，所以我们稍微推一下式子即可，枚举放了几个 a，有
$$
E(x)=\sum_{i=0}P_a^i P_b\times(k+i)
$$
$$
=k+P_b\times\sum_{i=0}P_a^i\times i
$$
如何计算 $P_a^i\times i$ 可以考虑等比数列求和的基本知识。

最后算出得 $E(x) = k -1 + \frac 1{P_b}$

如果你想看等比数列求和基本知识可以继续阅读
$$
\text{设 } T= \sum_{i=0}P_a^i\times i
$$
$$
E(x)=k+(1-P_a)T
$$
$$
P_aT=\sum_{i=1}P_a^i(i-1)
$$
$$
T-P_aT=\sum_{i=1}P_a^i=\frac {1}{1-P_a}-1=\frac {1}{P_b}-1
$$
$$
\therefore E(x)=k+(1-P_a)T=k-1+\frac {1}{P_b}
$$
代码就很短了。

```cpp
/*
　　　　　／＞　 フ
　　　　　| 　_　 _|
　 　　　／`ミ _x 彡
　　 　 /　　　 　 |
　　　 /　  ヽ　　 ?
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)_)
　＼二つ
 */

#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MP make_pair
#define ll long long
#define fi first
#define se second
using namespace std;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

template<typename F>
inline void write(F x, char ed = '\n') {
	static short st[30];short tp=0;
	if(x<0) putchar('-'),x=-x;
	do st[++tp]=x%10,x/=10; while(x);
	while(tp) putchar('0'|st[tp--]);
	putchar(ed);
}

template <typename T>
inline void Mx(T &x, T y) { x < y && (x = y); }

template <typename T>
inline void Mn(T &x, T y) { x > y && (x = y); }

const int P = 1e9 + 7;
ll fpw(ll x, ll mi) {
	ll res = 1;
	for (; mi; mi >>= 1, x = x * x % P)
		if (mi & 1) res = res * x % P;
	return res;
}

const int N = 2005;
ll k, pa, pb;
ll f[N][N];
int main() {
	read(k), read(pa), read(pb);
	ll t = fpw(pa + pb, P - 2);
	pa = pa * t % P, pb = pb * t % P;
	f[1][0] = 1; ll ans = 0;
	for (int i = 1;i < k; i++) {
		for (int j = 0;j < k; j++) {
			f[i+1][j] = (f[i+1][j] + f[i][j] * pa) % P;
			if (j + i < k) f[i][j+i] = (f[i][j+i] + f[i][j] * pb) % P;
			else ans = (ans + (j + i) * f[i][j] % P * pb) % P;
		}
	}
	t = fpw(pb, P - 2) * pa % P;
	for (int i = 0;i < k; i++) 
		ans = (ans + f[k][i] * (k + i + t)) % P;
	write(ans);
	return 0;
}
```



---

## 作者：王鲲鹏 (赞：10)

最大的坑点：
**翻译有误**

要求的是 形如 "ab" 的子序列的个数的期望，而不是串长的期望。（我就死活推不出来，也看不懂题解显然得出的式子。。。

我们发现初始状态确定，但是终止状态是很多的（ $\infty$ ），因此考虑逆序求期望。

在前缀已经有了 $i$ 个 $a$，构成了 $j$ 组 "ab" 的情况下，如果 $i,j \geq k$ ，这个状态的后继情况能是显然的：要么选了 $a$ ，然后继续抉择，要么选 $b$ ，就此停止。多选一个 $a$，就意味着最后的 "ab" 串又多了一个。
那么得出无限和式
$$
f[i][j]=\sum_{k=0}^{\infty}P_b\cdot P_a^k\cdot(i+k+j)
$$
括号里的部分可以这样理解：一直到选 $b$，前面一共有 $i+k$ 个 $a$ ，新构成 $i+k$ 组 "ab"，再加上已有的 $j$ 个。通过数学方法可以推出闭合表达式。


当 $i+j<k$ ，就有两个后继状态 选a： $f[i+1][j]$  选b：$f[i][j+i]$，那么加权平均：
$$
f[i][j] = P_af[i+1][j]+P_bf[i][j+i]
$$
倒序转移方程得到。
初始状态是$f[0][0]$。但是特殊的，我们发现状态00：
$$
f[0][0]=P_af[1][0]+P_bf[0][0]
$$
不能直接转移。移项发现 $f[1][0]=f[0][0]$。故答案转化为 $f[1][0]$。

// update 2020-10-20 感谢大佬提醒，修复了一处错误

---

## 作者：墨笙_Mooos (赞：8)

题解区怎么清一色等比数列 + 无穷级数求和，吓得我......

---

读完题面，想到期望 dp。

为方便表示，下文中的 $p_a$ 与 $p_b$ 表示原题中的 $\dfrac{p_a}{p_a+p_b}$ 与 $\dfrac{p_b}{p_a+p_b}$。

设 $f_{i,j}$ 表示当前序列里有 $i$ 个 ```a```，并且已经有了 $j$ 个 ```ab```。

考虑如何转移。

* 当下一步插入一个 ```a``` 的时候，由于不新增 ```ab```，所以只有 $f_{i+1, j}$ 对 $f_{i, j}$ 产生贡献。贡献为 $p_a \times f_{i+1, j}$。
* 当下一步插入一个 ```b``` 的时候，由于新增 $i$ 个 ```ab```，但是不影响 ```a``` 的个数，所以只有 $f_{i, j+i}$ 对 $f_{i, j}$ 产生贡献。贡献为 $p_b \times f_{i, j+i}$。

所以得到转移方程：

$$f_{i, j} = p_a \times f_{i+1, j} + p_b \times f_{i, j+i}$$

（注意，这题的期望不是步数，是最终状态时的 ```ab``` 个数，所以不要在后面 $+1$）

----

但是这个 dp 没有边界，所以我们需要构造一个边界。

我们不难发现，当 $i + j \ge k$ 时，只要再插入一个 ```b``` 就必定会结束。

因此，当满足该条件时，我们可以将原转移方程重写：

$$f_{i, j} = p_a \times f_{i+1, j} + p_b \times (i + j)$$

但是这样还是无穷的，怎么办呢？

考虑到状态 $f_{i + 1, j}$ 依旧是插入一个 ```b``` 就必定会结束。和状态 $f_{i, j}$ 的区别只有一个 ```a```，对于 $f_{i, j}$ 所计算到的每种情况，$f_{i + 1, j}$ 就可以对应一种多一个 ```ab``` 的情况。

或者说，先把这个多了的一个 ```a``` 拿掉，这样就是 $f_{i, j}$，最后结束的时候再放回去。因为只加了一个 ```b``` 就结束了，所以这个 ```a``` 后面只多了一个 ```b``` 和若干个 ```a```，对于答案也就是多了一个 ```ab```。

综上，我们可以得到 $f_{i + 1, j} = f_{i, j} + 1$。

代入，可得：

$$f_{i, j} = p_a \times (f_{i, j} + 1) + p_b \times (i + j)$$

$$(1 - p_a) \times f_{i, j} = p_a + p_b \times (i + j)$$

$$f_{i, j} = \dfrac{p_a}{p_b} + i + j$$

（注：$p_a + p_b = 1$）

----

如果你仔细观察，你会发现还有一个特殊情况！

$$f_{0, 0} = p_a \times f_{1, 0} + p_b \times f_{0, 0}$$

(0 . 0)

这时，我们故技重施，把 $f_{0, 0}$ 都移到左侧，就可以得到：

$$f_{0, 0} = f_{1, 0}$$

当然，你也可以理解为在开头放的所有 ```b``` 对于答案没有任何贡献，所以可以直接放上一个 ```a``` 再进行计算！

----

考虑时间复杂度！

由于状态保证 $i + j < k$，所以状态数量的量级是 $O(k^2)$，而考虑每个状态的计算，无论涉及的状态是否满足 $i + j < k$，都是 $O(1)$ 的。所以总时间复杂度就是 $O(k^2)$，且常数较小！

----

> Talk is cheap, show me the code!

```cpp
inline ll DFS (ll i = 1, ll j = 0)
{
	if (i + j >= k) return (i + j + P) % mod;
	if (f[i][j]) return f[i][j];
	return f[i][j] = (Pa * DFS (i + 1, j) % mod + Pb * DFS (i, j + i) % mod) % mod;
}

int main ()
{
	std::cin.tie (nullptr), std::ios::sync_with_stdio (false);
	cin >> k >> pa >> pb;
	Pa = pa * Inv (pa + pb) % mod, Pb = pb * Inv (pa + pb) % mod;
	P = pa * Inv (pb) % mod;
	cout << DFS () << endl;
	return 0;
}
```

----

总结：不错的期望 dp 练手题，可以时不时回顾一下。

---

## 作者：lyreqwq (赞：6)

小清新 DP + 数学题，本文主要详细证明边界的式子 qwq。

设 $f_{i, j}$ 表示有 $i$ 个 `a`，$j$ 个 `ab` 子序列时的期望答案。

转移时，有 $\frac{p_a}{p_a + p_b}$ 的概率加一个 `a`，转移到 $f_{i + 1, j}$；有 $\frac{p_b}{p_a + p_b}$ 的概率加一个 `b`，转移到 $f_{i, j + i}$。

于是有转移方程：

$$
f_{i, j} = \frac{p_a}{p_a + p_b} f_{i + 1, j} + \frac{p_b}{p_a + p_b} f_{i, j + i}
$$

这个方程是没有边界的，我们给它规定一个边界。记原题中 $k$ 为 $K$，容易发现 $i + j \ge K$ 时，只需要再加一个 `b` 就停止了。

即：

$$
f_{i, j} = \frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} (i + j + k) \cdot (\frac{p_a}{p_a + p_b})^k \; (i + j \ge K)
$$

展开：

$$
\frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} (i + j + k) \cdot (\frac{p_a}{p_a + p_b})^k
$$

$$
\begin{aligned}
	&= \frac{(i + j) p_b}{p_a + p_b} \sum_{k = 0}^{\infty} (\frac{p_a}{p_a + p_b})^k + \frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} k \cdot (\frac{p_a}{p_a + p_b})^k \\
	&= \frac{(i + j) p_b}{p_a + p_b} \cdot \frac{1}{1 - \frac{p_a}{p_a + p_b}} + \frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} k \cdot (\frac{p_a}{p_a + p_b})^k \\
	&= i + j + \frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} k \cdot (\frac{p_a}{p_a + p_b})^k \\
\end{aligned}
$$

右面那一项不好算，我们构造一个函数：

$$
\begin{aligned}
F(x) &= \sum_{k = 0}^{\infty} k x^k \\
	&= \sum_{k = 0}^{\infty} (k + 1) x^k - \sum_{k = 0}^{\infty} x^k \\
	&= \sum_{k = 0}^{\infty} [x^{k + 1}]^{'} - \sum_{k = 0}^{\infty} x^k \\
	&= [\sum_{k = 0}^{\infty} x^{k + 1}]^{'} - \sum_{k = 0}^{\infty} x^k \\
	&= [x \sum_{k = 0}^{\infty} x^k]^{'} - \sum_{k = 0}^{\infty} x^k \\
	&= [\frac{x}{1 - x}]^{'} - \frac{1}{1 - x} \\
	&= \frac{x^{'} (1 - x) - x (1 - x)^{'}}{(1 - x)^2} - \frac{1}{1 - x} \\
	&= \frac{1 - x + x}{(1 - x)^2} - \frac{1 - x}{(1 - x)^2} \\
	&= \frac{x}{(1 - x)^2}
\end{aligned}
$$

发现右面那一项其实就是 $F(\frac{p_a}{p_a + p_b})$ ，因此有：

$$
i + j + \frac{p_b}{p_a + p_b} \sum_{k = 0}^{\infty} k \cdot (\frac{p_a}{p_a + p_b})^k
$$

$$
\begin{aligned}
	&= i + j + \frac{p_b}{p_a + p_b} \frac{\frac{p_a}{p_a + p_b}}{(\frac{p_b}{p_a + p_b})^2} \\
	&= i + j + \frac{p_b}{p_a + p_b} \frac{p_a (p_a + p_b)}{p_b^2} \\
	&= i + j + \frac{p_a}{p_b}
\end{aligned}
$$

完结撒花 qwq。

**Code**

```cpp
#include <cstdio>

typedef long long LL;

constexpr int N = 1010;
constexpr LL MOD = 1e9 + 7;

LL f[N][N], p_a, p_b, A, B, Frac;
int n;

inline LL qpow(LL base, LL exp) {
	LL res = 1;
	while (exp) {
		if (exp & 1) res = res * base % MOD;
		exp >>= 1;
		base = base * base % MOD;
	}
	return res;
}

inline LL inv(LL x) {
	return qpow(x, MOD - 2);
}

int main(){
	scanf("%d %lld %lld", &n, &p_a, &p_b);
	A = p_a * inv(p_a + p_b) % MOD, B = p_b * inv(p_a + p_b) % MOD;
	Frac = p_a * inv(p_b) % MOD;
	for (int i = n; i; --i) {
		for (int j = n; j >= 0; --j) {
			if (i + j >= n) f[i][j] = (i + j + Frac) % MOD;
			else f[i][j] = (A * f[i + 1][j] % MOD + B * f[i][j + i] % MOD) % MOD;
		}
	}
	printf("%lld\n", f[1][0]);
	return 0;
}
```

---

## 作者：Awdrgysxc (赞：4)

### 【Analysis】
设$f_{i,j}$表示有$i$个A，$j$个AB期望长度。目标状态是$f_{1,0}$，因为$f_{0,0}$会转移自己。容易得到方程：
$$f_{i,j}= \dfrac{pa}{pa+pb} \times f_{i+1,j} + \dfrac{pb}{pa+pb}\times f_{i,j+i}$$

初始转态是$f_{i,j}(i+j\geqslant k)$，因为再加一个B就完成了。设期望$x$次中一次B，$P_a\gets\dfrac{pa}{pa+pb}$，$P_b\gets\dfrac{pb}{pa+pb}$，$c\gets i+j$
$$x\gets P_b \times \sum\limits_{i=0}^{\infty}(c+i)\times P_a^i$$
设数列$\{a_n\}$满足$a_n=(c+n)\times P_a^n$

设$S_n=\sum\limits_{i=0}^na_i$

$$P_a \times S_n=\dfrac{pa}{pa+pb}\times \sum\limits_{i=0}^n(c+i)\times \dfrac{pa}{pa+pb}$$

$$=\sum\limits_{i=0}^n(c+i)\times (\dfrac{pa}{pa+pb})^{i+1}$$

$$\because P_a+P_b=1$$

$$\therefore x\gets \lim\limits_{n\to\infty}P_b\times S_n=\lim\limits_{n\to\infty}S_n-P_a\times S_n$$
$$=\lim\limits_{n\to\infty} \sum\limits_{i=0}^n(c+i)\times \dfrac{pa}{pa+pb}-\sum\limits_{i=0}^n(c+i)\times (\dfrac{pa}{pa+pb})^{i+1}$$
$$=\lim\limits_{n\to\infty} (c+0)\times P_a^0 + \sum\limits_{i=1}^n(c+i)\times P_a^i-\sum\limits_{i=1}^n(c+i-1)\times P_a^i +(c+n)\times P_a^{n+1}$$
$$=\lim\limits_{n\to\infty} c+\sum\limits_{i=1}^n P_a^i+(c+n)\times P_a^{n+1}$$
$$=\lim\limits_{n\to\infty} c+\dfrac{P_a-P_a^n\times P_a}{1-P_a}+(c+n)\times  P_a^{n+1}$$
$$=\lim\limits_{n\to\infty} c+\dfrac{pa}{pb}\times (1-P_a^n)+(c+n)\times P_a^{n+1}$$
$$=\lim\limits_{n\to\infty} c+\dfrac{pa}{pb}+(c+n)\times P_a^{n+1}$$
$$=\lim\limits_{n\to\infty} c+\dfrac{pa}{pb}+\dfrac{c+n}{(\dfrac{pa+pb}{pa})^{n+1}}$$
$\because (c+n)$随着$n$的增大单调递增，$(\dfrac{pa+pb}{pa})^{n+1}$随着$n$的增大单调递增

$\therefore $
满足洛必达法则

根据洛必达法则,$\dfrac{f(x)}{g(x)}$如果在$x=a$处变成 $(0/0)$或是$(\infty/\infty)$，那么$\dfrac{f(x)}{g(x)}=\dfrac{f^\prime(x)}{g^\prime(x)}$
$$\therefore x\gets \lim\limits_{n\to\infty} c+\dfrac{pa}{pb}+\dfrac{c+n}{(\dfrac{pa+pb}{pa})^{n+1}}$$
$$=\lim\limits_{n\to\infty} c+\dfrac{pa}{pb}+\dfrac{1}{\ln(\dfrac{pa+pb}{pa})\times (\dfrac{pa+pb}{pa})^{n+1}}$$
$$=c+\dfrac{pa}{pb}$$

时间复杂度$\Theta(k^2)$

### 【Code】
```cpp
#include <bits/stdc++.h>
using namespace std;
 
typedef long long int64;
const int P = 1e9 + 7;
inline int qPow(int x, int y)
{
	int res = 1, base = x;
	while (y > 0)
	{
		if (y & 1)
			res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		y >>= 1;
	}
	return res;
}
inline int inv(int x) { return qPow(x, P - 2); }
inline int add(int x, int y) { x += y; x -= x >= P ? P : 0; return x; }
inline int mul(int x, int y) { return 1ll * x * y % P; }

int main(void)
{
	int n = 1, a = 1, b = 1;
	cin >> n >> a >> b;
	const int A = 1ll * a * inv(a + b) % P;
	const int B = (1 - A + P) % P;
	const int V = 1ll * a * inv(b) % P;
	vector <vector <int>> dp(n + 1);
	for (int i = 1;i <= n; ++i)
		dp[i].resize(n + 1);
	
	for (int i = n;i >= 1; --i)
		for (int j = n;j >= 0; --j)
			dp[i][j] = (i + j >= n) ? (add(i, add(j, V))) : (add(mul(dp[i + 1][j], A), mul(dp[i][i + j], B)));
	cout << dp[1][0] << '\n';
	return 0;
}
```

---

## 作者：红尘仙 (赞：3)

### 前序 
因为这道题在培训的时候讲了，所以过了这个题目之后，写一篇题解加深一下印象

### Solution 

这里是正着推的。
我们观察一下题目可以得知 ： 
+ 增添一个 a 并不会增加 ab 子序列。
+ 增添一个 b 将会增加的数量和前面 a 的数目是一样的。
+ 增添不是有限的，只要能一直增加 a 便是无限的。

后面将围绕这三个展开。

设 $f_{i,j}$ 表示有 i 个字符 a , 构成了 j 个 ab 子序列的期望。

我们显然是有以下两个状态转移 ： 

1. 继续向后方增加一个字符 a,ab 子序列数目不变 ，即为 ： 
$$f_{i + 1 , j} += f_{i ,j}\times p_a$$ 
2.向后方直接加一个字符 b ，那么就会增加前面 a 的数目的子序列，即为：
$$f_{i , i + j} += f_{i , j} \times p_b$$ 

这样显然是可行的。 但是当 $k \leq i + j$ 的时候，第二维已经到了边界，也就可以不再进行下去了，但是第一维是无穷的，只要能放 a ，就一直是无限的。那么如果 $k \leq i + j$ 我们就将贡献乘上去，特别的，当 i = k 的时候，可以通过下列式子推导出边界：

设 $A = p_a , B = p_b$ , 其中 $B(x)$ 直接代表 $B \times x$ , 则有:

---

$$f_{k , j} = Af_{k + 1 , j} + B(k + j)$$ 
$$ = A^2f_{k +2 , j} + AB(k + 1 + j) + B(k + j)$$
$$=\dots $$
$$= \sum_{i = 0}^{\infty}A^iB(k + i + j)$$ 
$$= \sum_{i = 0} ^{\infty}A^i iB + \sum_{i = 0} ^{\infty}A^i B(k + j)$$
$$= \frac{A}{(1 - A)^2} B + \frac{1}{1 - A}B(k + j)$$
$$= \frac{A}{B} + k + j$$ 


对于每一种 j , 直接乘以它的概率计算即可。

---

> 有些结论或许可以帮助你理解推导过程 :
$$\sum_{i = 0}^{\infty} p^i i = \frac{p}{(1 - p)^ 2}$$
$$\sum_{i = 0}^{\infty} p^i = \frac{1}{1 - p}$$

---


### Code

```
//
/*
Author : Zmonarch
Knowledge : 
*/
#include <bits/stdc++.h>
#define int long long 
#define inf 2147483647
#define qwq register 
#define qaq inline 
using namespace std ; 
const int kmaxn = 2e3 + 10 ; 
const int mod = 1e9 + 7 ;
qaq int read() {
	int x = 0 , f = 1 ; char ch = getchar() ; 
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;} 
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
int f[kmaxn][kmaxn] , pa , pb , k , ans ; 
qaq int Qpow(int a , int b) {
	int ret = 1; 
	while(b) 
	{
		if(b & 1) ret = ret * a % mod ; 
		a = a * a % mod ; b >>= 1 ; 
	}
	return ret ; 
}
qaq int Inv(int x) {
	return Qpow(x , mod - 2) ; 
}
signed main() {
	k = read() , pa = read() , pb = read() ; 
	int tmp = Inv(pa + pb) % mod ; 
	pa = pa * tmp % mod ;  pb = pb * tmp % mod ; 
	f[1][0] = 1 ; 
	for(qwq int i = 1 ; i < k ; i++) 
	{
		for(qwq int j = 0 ; j < k ; j++) 
		{
			f[i + 1][j] = (f[i + 1][j] + f[i][j] * pa % mod + mod) % mod ;  
			if(i + j < k) f[i][i + j] = (f[i][i + j] + f[i][j] * pb % mod + mod) % mod ; 
			else ans = (ans + f[i][j] * pb % mod * (i + j) % mod + mod) % mod ; 
		}
	}
	tmp = Inv(pb) % mod ; 
	for(qwq int i = 0 ; i < k ; i++) 
	ans = (ans + (pa * tmp % mod + k + i) * f[k][i] % mod + mod) % mod ; 
	printf("%lld\n" , ans) ; 
	return 0 ; 
}
```

---

## 作者：奇卡 (赞：3)

[照例宣传一发博客](https://www.cnblogs.com/PsychicBoom/p/10466868.html)

题目大意：给你一个空字符串，你有$\frac{pa}{pa+pb}$的概率往字符串最后面加个$a$,$\frac{pb}{pa+pb}$的概率往字符串最后面加个$b$，当**子序列**$ab$的个数超过$k$时，停止加入。求是期望出现**子序列**$ab$的个数


------------


因为可以无限加字母，所以设$f[i][j]$表示这个串有$i$个$a$,$j$个$ab$为**前缀**时，期望出现的$ab$子序列个数

转移方程为
$$f[i][j]=(f[i+1][j]*pa+f[i][j+i]*pb)/(pa+pb)$$

我们可以发现当$i+j\geq k$时，再加个$b$就可以结束。然后就是求这个状态对应的期望$x$

### $x= \frac{pb}{pa+pb} \sum\limits_{a=0}^{\infty}(i+j+a)*({\frac{pa}{pa+pb}})^a$

### $=\frac{pb}{pa+pb}*\frac{\sum\limits_{a=0}^{\infty}(i+j+a)*({\frac{pa}{pa+pb}})^a-\sum\limits_{a=1}^{\infty}(i+j+a)*({\frac{pa}{pa+pb}})^a}{(1-\frac{pa}{pa+pb})}$

### $=\sum\limits_{a=0}^{\infty}(i+j+a)*({\frac{pa}{pa+pb}})^a-\sum\limits_{a=0}^{\infty}(i+j+a)*({\frac{pa}{pa+pb}})^{a+1}$

### $=i+j+\sum\limits_{a=1}^{\infty}({\frac{pa}{pa+pb}})^a$

### $=i+j+\frac{pa}{pa+pb}/(1-\frac{pa}{pa+pb})$

### $=i+j+\frac{pa}{pb}$

这个过程用了两次**错位相减**法

然后关于答案是$f[0][0]$ or $f[1][0]$的问题

感性理解的话，前面无限加$b$不会对答案产生贡献

理性证明的话把转移方程代进去，然后就是$f[0][0]=f[1][0]$了

丢代码：
```cpp
#include <bits/stdc++.h>
#define N 1010 
#define ll long long 
#define mod 1000000007ll
using namespace std;
ll invab,invb,f[N][N],pa,pb,k;//有i个a和j个ab的期望ab个数 

ll ksm(ll x,ll y){
    ll ans=1;
    for(;y;y>>=1,(x*=x)%=mod) if(y&1) (ans*=x)%=mod;
    return ans;
}
ll dfs(int x,int y){
    if(x+y>=k) return ((x+y)%mod+pa*invb%mod)%mod; 
    if(f[x][y]) return f[x][y];
    else return f[x][y]=(dfs(x+1,y)*pa%mod+dfs(x,y+x)*pb%mod)%mod*invab%mod;
}

int main(){
    cin>>k>>pa>>pb;
    invab=ksm(pa+pb,mod-2);
    invb=ksm(pb,mod-2);
    cout<<dfs(1,0);
}
```


---

## 作者：Larryyu (赞：2)

## Description

给定 $k,pa,pb$，有一初始为空的序列。

每次有 $\dfrac{pa}{pa+pb}$ 的概率往序列后面加一个 ```a```。

每次有 $\dfrac{pb}{pa+pb}$ 的概率往序列后面加一个 ```b```。

当出现大于等于 $k$ 个形如 ```ab``` 的子序列（```a``` 和 ```b``` 不一定相邻）时停止。

求序列最终的 ```ab``` 子序列期望数。

## Solution

为了更加简洁，文中的 $pa$ 指题意中的 $\dfrac{pa}{pa+pb}$，$pb$ 指 $\dfrac{pb}{pa+pb}$。

看到求期望，可以先试着写写 ```dp```。

设 $f_{i,j,t}$ 表示有 $i$ 个 ```a```、$j$ 个 ```b```、$t$ 个 ```ab``` 时的期望。

发现当前有 $i$ 个 ```a``` 时，再加一个 ```b``` 会产生 $i$ 个 ```ab```，与之前 ```b``` 的数量无关，所以省去一维 ```dp```。

设 $f_{i,j}$ 表示有 $i$ 个 ```a```、$j$ 个 ```ab``` 时的期望。

由于我们只知道终止状态，所以倒推会更好写且容易理解。

$f_{i,j}$ 有 $pa$ 的概率加 ```a``` 变为 $f_{i+1,j}$，有 $pb$ 的概率加 ```b``` 变为 $f_{i,j+i}$，得出转移方程：

$$f_{i,j}=pa\times f_{i+1,j}+pb\times f_{i,j+i}$$

答案即为 $f_{1,0}$。

接下来是本题最难部分，求满足终止条件的 $f$ 值。

终止条件为 $i+j\ge k$，此时只要再加一个 ```b``` 就可以终止。

然而在加 ```b``` 前可能有若干个 ```a```，无法确定 ```a``` 的数量，所以要开始推式子。

### Sol1

这种方法用了等比数列的思想。

$$f_{i,j(i+j\ge k)}=i+j+\sum\limits_{x=0}^\infty pa^x\times pb\times x$$

$x$ 为 ```a``` 的出现次数，```a``` 每多在 ```b``` 前出现一次，最后的 ```ab``` 就会多一个，所以总共加了 $i+j+x$ 个 ```ab```。

继续推：

$$=i+j+pb\times\sum\limits_{x=0}^\infty pa^x\times x$$

$$=i+j+(1-pa)\times\sum\limits_{x=0}^\infty pa^x\times x$$

设 $T=\sum\limits_{x=0}^\infty pa^x\times x$。

$$\therefore pa\times T=\sum\limits_{x=1}^\infty pa^x\times (x-1)$$

$x$ 变为 $x-1$ 的原因是 $x$ 变为 $1$ 开始。

$$\because T=\sum\limits_{x=1}^\infty pa^x\times x+pa^0\times0=\sum\limits_{x=1}^\infty pa^x\times x$$

$$\therefore (1-pa)\times T=\sum\limits_{x=1}^\infty pa^x$$

设 $S=\sum\limits_{x=0}^\infty pa^x$。

$$\therefore pa\times S=\sum\limits_{x=1}^\infty pa^x$$

$$\because S=\sum\limits_{x=1}^\infty pa^x+pa^0=\sum\limits_{x=1}^\infty pa^x+1=T+1$$

$$\therefore (1-pa)S=pa^0=1$$

$$S=\dfrac{1}{1-pa}=T+1$$

$$\therefore T=\dfrac{1}{1-pa}-1=\dfrac{pa}{pb}$$

$$\therefore f_{i,j(i+j\ge k)}=i+j+\dfrac{pa}{pb}$$

### Sol2

对于 $f_{i,j}$ 和 $f_{i+1,j}$（$i+j\ge k$）：

由于后面的 ```b``` 终止前，新的 ```a``` 产生的多余 ```ab``` 期望数都是一样的。

所以两期望的区别只有当前 ```a``` 相差 $1$ 造成的期望 $1$。

即 $f_{i+1,j}=f_{i,j}+1$。

$$\because i+j\ge k$$

$$\therefore f_{i,j+i}=i+j$$

$$\therefore f_{i,j}=pa\times(f_{i,j}+1)+pb\times(i+j)$$

$$(1-pa)\times f_{i,j}=pa+pb\times(i+j)$$

$$pb\times f_{i,j}=pa+pb\times(i+j)$$

$$f_{i,j}=\dfrac{pa}{pb}+i+j$$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mo 1000000007
#define int long long
int k,a,b,pa,pb;
int f[1010][1010];
int po(int x,int y){
	int z=1;
	while(y){
		if(y%2) z*=x;
		x*=x;
		x%=mo,z%=mo;
		y/=2;
	}
	return z;
}
signed main(){
	cin>>k>>a>>b;
	pa=a*po(a+b,mo-2)%mo;
	pb=b*po(a+b,mo-2)%mo;
	for(int i=k;i>=1;i--){
		for(int j=k;j>=0;j--){
			if(i+j>=k){
				f[i][j]=pa*po(pb,mo-2)%mo+i+j;
				f[i][j]%=mo;
			}else{
				f[i][j]=f[i+1][j]*pa%mo+f[i][j+i]*pb%mo;
				f[i][j]%=mo;
			}
		}
	}
	cout<<f[1][0];
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

正推不好写，我们可以考虑逆推。

定义 dp 状态 $dp_{i,j}$ 表示有 $i$ 个 $a$ 与 $j$ 个 $ab$。

考虑转移

- 有 $p_0$ 的概率放置 $a$

  此时 $dp_{i,j}$ 由 $dp_{i+1,j}$ 转移而来。

- 有 $p_1$ 的概率放置 $b$

  此时 $dp_{i,j}$ 由 $dp_{i,j+i}$ 转移而来。

故方程为 $dp_{i,j} = p_0 \times dp_{i+1,j} + p_1 \times dp_{i,j+i}$。

- 特殊情况：$i + j \geq k$

  此时发现加入一个 $b$ 就停止了，但是我们不知道答案是多少，不过我们可以发现我们每随机出一次 $a$，答案便多一，列一下方程 $dp_{i,j} = p_0 \times (dp_{i,j}+1) + p_1 \times (i + j)$。其中 $i+j$ 是已经停止后的答案。

  解得 $dp_{i,j} = \frac{p_0}{p_1} + i + j$。注意到 $p_1 = 1 - p_0$。

此外，对于前面的 $b$，如果它前面没有 $a$ 将不会产生贡献，故 $dp_{0,0} = dp_{1,0}$。

使用递归或许更加简便。

```cpp
const int mod = 1e9 + 7;
int p[3], k, a, b, dp[1010][1010];
int ksm(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1LL * res * a % mod;
		b >>= 1;
		a = 1LL * a * a % mod;
	} return res;
}
int dfs(int i, int j) {
	if (i + j >= k) return (p[2] + i + j) % mod;
	if (dp[i][j]) return dp[i][j];
	return dp[i][j] = (1LL * p[0] * dfs(i + 1, j) % mod + 1LL * p[1] * dfs(i, i + j) % mod) % mod; 
}
signed main() {
	read(k, a, b);
	p[0] = 1LL * a * ksm(a + b, mod - 2) % mod, p[1] = 1LL * b * ksm(a + b, mod - 2) % mod, p[2] = 1LL * a * ksm(b, mod - 2) % mod;
	write(dfs(1, 0), '\n');
	return 0;
}
```

---

## 作者：wsy_jim (赞：1)

CF908D New Year and Arbitrary Arrangement

题意：给定三个数 $k,pa,pb$，一开始是空字符串，每次有 $\frac{pa}{pa+pb}$ 的概率在字符串末尾填上 $a$，有 $\frac{pb}{pa+pb}$ 的概率在字符串末尾填上 $b$，直到有至少 $k$ 个子序列为 $ab$ 时停止，求停止时子序列为 $ab$ 的个数，数据范围：$k\leq 1000,1\leq pa,pb\leq 1000000$ 

设状态要特别注意，因为字符串有可能无限延伸，所以考虑结束后的前缀是好做的，设 $f[i][j]$ 表示前缀有 $i$ 个字符 $a$ 和 $j$ 个子序列 $ab$ 的期望 $ab$ 子序列数，转移很好转移 $f[i][j]=\frac{pa}{pa+pb}\times f[i+1][j]+b\times f[i][i+j]$ 

注意边界情况 $i+j\geq k$，这时只要一个 $b$ 就能满足条件，今天 $i207M$ 给我们讲了一个结论：

> 一个发生概率为 $P$ 的事件，期望 $\frac{1}{P}$ 次发生

这个结论有两种证法，第一种我没听明白，第二种是裂项相消法

这个期望可以写成 $\sum_{i=1}^n i\cdot P(第i步发生的概率)$ 化简后成 $\sum_{i=1}^n i\cdot ((1-p)^{i-1}\cdot p)$ 这是一个等差数列乘上一个等比数列，用裂项相消就能得出以上结论

回~来~

只要一个 $b$ 就能满足，但是 $b$ 发生的概率为 $\frac{pb}{pa+pb}$，期望成功次数是 $\frac{pa+pb}{pb}$，但由于其中一个 $b$ 要跟着前面的 $a$，那么就是 $\frac{pa}{pb}$，边界情况就是 $i+j+\frac{pa}{pb}$ 

搞一搞，码非常简单

---

## 作者：xuantianhao (赞：0)

# [New Year and Arbitrary Arrangement](https://www.luogu.com.cn/problem/CF908D)

思路：

期望题果然还是恶心呀！

我们设 $f[i][j]$ 表示当串中有 $i$ 个 $a$ 和 $j$ 个 $ab$ 时的方案数。为了方便，设 $A=\dfrac{P_a}{P_a+P_b},B=\dfrac{P_b}{P_a+P_b}$。

显然，可以这样转移：

$$f[i][j]=f[i+1][j]\times A+f[i][i+j]\times B$$

因为，如果串后面加上一个 $a$，概率是 $A$，并且加完后唯一的影响就是 $i+1$；如果加入一个 $b$，概率是 $B$，加完后前面每一个 $a$ 都会与这个 $b$ 形成一对 $ab$。

那么边界条件呢？

显然，当 $i+j\geq k$ 时，只要再往后面加入一个 $b$，过程就停止了。

则这个的期望长度应该是：

$$B\times \sum\limits_{a=0}^{\infty}(i+j+a)\times A^a$$
 
其中，枚举的这个 $a$ 是在终于搞出一个 $b$ 前，所刷出的 $a$ 的数量。

为了方便，我们设 $i+j=c$，并用 $i$ 替换 $a$。即：

$$B\times \sum\limits_{i=0}^{\infty}(c+i)\times A^i$$
 
因为 $A+B=1$，我们可以用 $(1-A)$ 代 $B$。

即：

$$(1-A)\times \sum\limits_{i=0}^{\infty}(c+i)\times A^i$$
 
拆开括号得:

$$\sum\limits_{i=0}^{\infty}(c+i)\times A^i-\sum\limits_{i=0}^{\infty}(c+i)\times A^{i+1}$$
 
一上来直接 $\infty$ 有些不直观，我们用 $n$ 替换掉:

$$\sum\limits_{i=0}^n(c+i)\times A^i-\sum\limits_{i=0}^n(c+i)\times A^{i+1}$$
 
在第二个式子里面用 $i+1$ 代掉 $i$:

$$\sum\limits_{i=0}^n(c+i)\times A^i-\sum\limits_{i=1}^{n+1}(c+i-1)\times A^i$$
 
将第一个 $\Sigma$ 中 $i=0$ 的情况和第二个 $\Sigma$ 中 $i=n+1$ 的情况分别提出：

$$c+\sum\limits_{i=1}^n(c+i)\times A^i-\sum\limits_{i=1}^n(c+i-1)\times A^i-(c+n)\times A^{n+1}$$
 
合并两个 $\Sigma$：

$$c+\sum\limits_{i=1}^nA^i-(c+n)\times A^{n+1}$$
 
套等比数列求和公式，注意要先提出一个 $A$ 使首项为为一。

$$c+A\times \dfrac{1-A^n}{1-A}-(c+n)\times A^{n+1}$$
 
注意到 $1-A=B$：

$$c+A\times \dfrac{1-A^n}{B}-(c+n)\times A^{n+1}$$
 
现在，考虑 $n\rightarrow\infty$ 的情况，即：

$$\lim\limits_{n\rightarrow\infty}c+A*\dfrac{1-A^n}{B}-(c+n)*A^{n+1}$$
 
注意到 $0<A<1$，因此 
$\lim\limits_{n\rightarrow\infty}A^n=0$ 带入发现：

$$c+A\times \dfrac{1-0}{B}-(c+n)\times 0$$

处理一下 $c+\dfrac{A}{B}$ 注意到我们一开始的定义了吗？

$$A=\dfrac{P_a}{P_a+P_b},B=\dfrac{P_b}{P_a+P_b}$$

以及 $c=i+j$ 代入得：

$$i+j+\dfrac{P_a}{P_b}$$
 
也就是说，边界条件就是 $f[i][j]=i+j+\dfrac{P_a}{P_b}(i+j\geq k)$！！！

再搬出我们一开始的转移式：

$$f[i][j]=f[i+1][j]\times A+f[i][i+j]\times B$$
完事。

哦，另外，还要思考一下答案到底是 $f[0][0]$ 还是 $f[1][0]$。

因为一开始的那些 $b$，无论来多少个都是没用的，因此不如直接从 $f[1][0]$ 开始。事实上，你如果把转移式代回去或者打个表的话，你会发现就有 $f[0][0]=f[1][0]$。

复杂度 $O(k^2+\log mod)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=1e3+100;
int n,a,b,c,A,B;
int f[N][N];
int ksm(int x,int y){
    int z=1;
    for(;y;(x*=x)%=mod,y>>=1) if(y&1) (z*=x)%=mod;
    return z;
}
int dfs(int x,int y){
    if(x+y>=n) return x+y+c;
    if(f[x][y]!=-1) return f[x][y];
    int &res=f[x][y];
	res=0;
    (res+=dfs(x+1,y)*A%mod)%=mod;
    (res+=dfs(x,x+y)*B%mod)%=mod;
    return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>a>>b;
	memset(f,-1,sizeof(f));
	A=a*ksm(a+b,mod-2)%mod;
	B=b*ksm(a+b,mod-2)%mod;
	c=a*ksm(b,mod-2)%mod;
    cout<<dfs(1,0);
    return 0;
}
```


---

## 作者：az__eg (赞：0)

首先看到这道题，发现像标准概率 dp 题。考虑用 dp。

为了方便表示，接下来 $pa$ 表示下一个选 $\texttt{a}$ 的概率，$pb$ 同理。

朴素设个状态 $dp_{i,j}$ 表示当前有 $i$ 个 $\texttt{a}$，$j$ 个子序列。

根据状态，我们分讨一下，当 $i<k$ 和 $j<k$ 时，发现：

$$dp_{i,j} = dp_{i+1,j}\times pa + dp_{i,i+j}$$

继续考虑 $k\leq j$ 时，发现：

$$dp_{i,j} = j$$

最后一种状态 $k\leq i$ 首先我们可以分解出一个基础状态：

$$dp_{i,j} = dp_{i+1,j}\times pa + pb\times(i+j)$$

接下来当 $k\leq i$ 时，有个结论：

$$dp_{i,j}=dp_{i+1,j}+1$$

因为我们发现不论是 $i$ 还是 $i+1$ 都大于 $k$，那么他们的转移方程一样，那么其实他们的每个状态都是对应的，除了 $dp_{i+1,j}$ 最后会比 $dp_{i,j}$ 多一个 $\texttt{ab}$ 子序列，所以有这个结论。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
const int MOD = 1e9+7;
using namespace std;
int ksm(int a,int b)
{
	int rt=1;
	while(b!=0)
	{
		if(b%2==1)
		{
			rt*=a;
			rt%=MOD; 
		}
		a*=a;
		a%=MOD;
		b/=2;
	}
	return rt;
}
int dp[1001][1001];
int k,pa,pb;
int dfs(int x,int y)
{
	if(y>=k)
	{
		return y;
	}
	else if(x>=k)
	{
		return (x+y+pa*ksm(pb,MOD-2)%MOD)%MOD;
	}
	if(dp[x][y]!=-1)
	{
		return dp[x][y];
	}
	else if(x==0&&y==0)
	{
		dp[x][y]=dfs(x+1,y);
		return dp[x][y];
	}
	else
	{
		dp[x][y]=pa*dfs(x+1,y)%MOD;
		dp[x][y]+=pb*dfs(x,x+y)%MOD;
		dp[x][y]%=MOD;
		return dp[x][y];
	}
}
signed main()
{
	memset(dp,-1,sizeof(dp));
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); 
	cin>>k>>pa>>pb;
	int sum=pa+pb;
	pa*=ksm(sum,MOD-2);
	pb*=ksm(sum,MOD-2);
	pa%=MOD;
	pb%=MOD;
	cout<<dfs(0,0);
}
```


---

## 作者：FxorG (赞：0)

简单题。

发现最终状态无限，起始状态有限，考虑逆推（辅以记忆化）

设 $f[x][y][z]$ 为 $x$ 个 a，$y$ 个 $b$，$z$ 个 ab 的期望 ab 个数。

则考虑能怎样走到哪些状态。

选 a，$f[x+1][y][z]$

选 b，$f[x][y+1][x+y]$

发现 b 这一维没啥用，因为前面的 b 对当前构不成影响，删去。

设 $f[x][y]$ 为 $x$ 个 a,$y$ 个 ab 的期望。

$$f[x][y]=P(A)*f[x+1][z]+P(B)*f[x][x+y]$$

但是可能会有 $\lim_{x\to +\infty}$，即无法知道边界。

考虑当 $x+y \ge k$，我们只需要算出在选一定次数 a 后选到 b 的期望和即可。

即

$$P(B)*\sum_{i=0}^{\infty}P(A)^i*(x+y+i)$$

代下

$${\sum_{i=0}^{\infty}p^i=\dfrac{1}{1-p}}$$

$$\sum_{i=0}^{\infty}p^ii=\dfrac{p}{(1-p)^2}$$

补充下 2 式证明

$$\sum_{i=0}^{\infty}p^ii=s $$

$$s-sp=\sum_{i=1}^{\infty}p^ii$$

$$\dfrac{s(1-p)}{p}=\sum_{i=0}^{\infty}p^ii$$

$$s=\dfrac{p}{(1-p)^2}$$

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#define int long long
using namespace std;

int rd() {
	char ch=getchar(); int sum=0,f=1;
	while(!isdigit(ch)) {
		if(ch=='-') f=-1; ch=getchar();
	}
	while(isdigit(ch)) sum=sum*10+ch-'0',ch=getchar();
	return f*sum;
}

const int mod=(int)(1e9+7);
int k,a,b,pa,pb,A1,A2;
int f[2005][2005];

int fpow(int x,int y) {
	int res=1; x=(x%mod+mod)%mod;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod; y>>=1;
	}
	return res;
}

int dfs(int x,int y) {
	if(x+y>=k) return  pb*((x*A1%mod+y*A1%mod+A2)%mod)%mod;
	if(f[x][y]) return f[x][y];
	return f[x][y]=(pa*dfs(x+1,y)%mod+pb*dfs(x,x+y)%mod)%mod;
}

signed main() {
	k=rd(); a=rd(); b=rd(); pa=a*fpow(a+b,mod-2)%mod; pb=b*fpow(a+b,mod-2)%mod; A1=fpow(1-pa,mod-2)%mod; A2=pa*fpow(1-pa,mod-2)%mod*fpow(1-pa,mod-2)%mod;
	printf("%lld",(dfs(1,0)%mod+mod)%mod);
	return 0;
}
```

---

## 作者：过往梦魇之殇 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF908D)

>$Upd$ $2020.08.07:$ 题面翻译的锅已经修好啦！

**思路简述:**

设$dp_ij$为字符串中有 $i$ 个 $a$ 且当前停止操作时有 $j$ 个 “$ab$” 的期望长度

设 $A=\dfrac{pa}{pa+pb},B=\dfrac{pb}{pa+pb}$

故一般情况下, $dp_{i,j}=A\times dp_{i+1,j}+B\times dp_{i,i+j}$

当 $i+j\ge k$ 时，易知如果在末尾再加一个 $b$ 操作就停止了。

此时通过错位相减，可以得到 $dp_{i,j}=i+j+\dfrac{pa}{pb}$

状态转移方程就出来了。

另外的，这道题要分数取模/$fad$

~~不会的可以去BFS一下~~

最后的答案应该为 $dp_{1,0}$ 而不是 $dp_{0,0}$

因为 $dp_{0,0}$ 的话，无限加 $b$ 也不会对答案造成影响。

严谨的证明在此就不展示了。

**代码展示：**
```cpp
/* 
dp[i][j]:i*'a'-->j*'ab',j='ab' string's expected length
if A=pa/(pa+pb),B=pb/(pa+pb)
than dp[i][j]=A*dp[i+1][j]+B*dp[i][i+j]
-----------
if i+j>=k than to add a 'b' will stop the operation,the expected value is (i+j+pa/pb)
the original state is dp[1][0],but not dp[0][0](dp[0][0]->dp[0][0])
*/
#include<bits/stdc++.h>
#define int long long
#define re register
#define modd 1000000007
using namespace std;
const int maxn=1e3+10;
int k,pa,pb,dp[maxn][maxn];
void gcd(int a,int b,int &x,int &y){
    if(!b){
		x=1,y=0;
	}
    else{
		gcd(b,a%b,y,x);
		y-=x*(a/b);
	}
}
int inv(int a)
{
	int x,y;
	gcd(a,modd,x,y);
	return (x%modd+modd)%modd;
}
signed main(){
    scanf("%lld%lld%lld",&k,&pa,&pb);
    int A,B,C;
    A=(pa*inv(pa+pb)%modd);
    B=((1-A+modd)%modd);
    C=(pa*inv(pb)%modd);
    for(re int i=k;i>=1;--i){
        for(re int j=k;j>=0;--j){
            if(i+j>=k){
                dp[i][j]=(i+j+C)%modd;
            }
            else{
                dp[i][j]=(A*dp[i+1][j]+B*dp[i][i+j])%modd;
            }
        }
    }
    printf("%lld\n",dp[1][0]);
    return 0;
}
```
完结撒花~

>$Thanks$ $For$ $Watching!$

---

