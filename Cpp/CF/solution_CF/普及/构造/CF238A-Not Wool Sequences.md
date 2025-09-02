# Not Wool Sequences

## 题目描述

A sequence of non-negative integers $ a_{1},a_{2},...,a_{n} $ of length $ n $ is called a wool sequence if and only if there exists two integers $ l $ and $ r $ $ (1<=l<=r<=n) $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF238A/2ec5f782c063d456c865928ec08f722fe4394a16.png). In other words each wool sequence contains a subsequence of consecutive elements with xor equal to 0.

The expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF238A/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the operation of a bitwise xor to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example, in languages C++ and Java it is marked as "^", in Pascal — as "xor".

In this problem you are asked to compute the number of sequences made of $ n $ integers from 0 to $ 2^{m}-1 $ that are not a wool sequence. You should print this number modulo $ 1000000009 $ $ (10^{9}+9) $ .

## 说明/提示

Sequences of length $ 3 $ made of integers 0, 1, 2 and 3 that are not a wool sequence are (1, 3, 1), (1, 2, 1), (2, 1, 2), (2, 3, 2), (3, 1, 3) and (3, 2, 3).

## 样例 #1

### 输入

```
3 2
```

### 输出

```
6
```

# 题解

## 作者：是个汉子 (赞：5)

### Solution

看到是一个异或和的序列，我们可以考异或的性质。

我们构造一个数组 $b$ ： $b_0=0,b_i=a_i\oplus b_{i-1}$ ，由异或性质得 $a_i=b_i\oplus b_{i-1}$ ，所以 $a_l\oplus a_{l+1}\oplus\cdots\oplus a_r\not=0\Rightarrow b_{l-1}\oplus b_r\not= 0$ ，题目中说 $l\leq r$ ，所以 $b$ 数组中的每个数都不相同。

因为 $a_i=b_i\oplus b_{i-1}$ ，所以 $b_i\in[1,2^m]$ ，则答案就是找长度为 $n$ 的数组且数组中的数在 $[1,2^m]$ 各不相同，即 $A_{2^m}^n$ 。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int mod=1e9+9;
int n,m; ll ans=1,pow2=1;

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) pow2=(pow2*2)%mod;
    for(int i=1;i<=n;i++) ans=(ans*(pow2-i))%mod;
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：wloving (赞：2)

## 题目分析

目的：求出非`Wool`序列的个数。

知识点：前缀和、异或

首先，考虑`wool`序列的特点，题面中解释的很清楚，为序列内存在连续元素的子序列，它们的异或值为 $0$。反过来说，非`wool`序列就是序列内不存在连续元素异或值为 $0$ 的子序列。

序列特征的关键在于连续区间的异或值，我们可以采用前缀和的思想进行快速求解。构造前缀异或的数组，即：

$$s_i = \begin{cases} a_1 & i =1  \\ s_{i-1}\oplus a_i & 2\le i\le n \end{cases}$$

那么区间 $[L,R]$ 的异或值，可表达为 $s_R\oplus s_{L-1}$ 。结合异或的特性：两个数进行异或，当两者相同时，异或值为 $0$。也就是说当 $s_R$ 等于 $s_{L-1}$ 时，区间异或值为 $0$ 。序列中只要存在两个相同的前缀异或值，则为`wool`序列，反过来说，当序列中所有的前缀异或值都不相同时，就属于非`wool`序列了。

接下来考虑序列中所有的前缀异或值都不相同的序列数量。先去考虑前缀异或值的范围，题目告诉我们序列由 $0\sim 2^{m}-1$ 的整数构成，那么对应的前缀异或值的范围就是 $0\sim 2^m-1$。

来解释下前缀异或值的范围为什么是 $0\sim 2^m-1$。异或在计算时，二进制位相同为 $0$ 不同为 $1$，也被称作为不进位加法。所以两个非负整数 $a$ 和 $b$ 在异或计算时，结果的取值范围取决于两数中二进制的最高位的 $1$。若最高位 $1$ 的位置为 $k$ 则，最大的范围就是二进制中最低位到第 $k$ 位都是 $1$ 也就是 $2^{k+1}-1$。所以，当进行异或的元素值为 $0\sim 2^m-1$ 时，异或后的结果范围也是 $0\sim 2^m-1$。

由于我们现在找的序列要求是所有的前缀异或值都不相同，再结合子序列范围是 $1\le l\le r\le n$，包含了 $l=r$  的情况，所以也要排除掉前缀异或值为 $0$ 的情况。那么问题就变成了从 $1\sim 2^m-1$ 中选择 $n$ 个数进行排列的方案数，即 $A_{2^m-1}^n$，也就是 $\prod\limits_{i=0}^{n-1}{2^m-1-i}$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1e9+9;
ll n,m,ans=1;
ll mypow(ll a,ll n){//快速幂
	ll ans=1;
	while(n){
		if(n&1){
			ans=ans*a;
			ans%=M;
		}
		a=a*a%M;
		n>>=1;
	}
	return ans;
}
int main()
{
	cin>>n>>m;
	ll tmp=mypow(2,m)-1;//先求出2^m - 1
	for(int i=0;i<n;i++){//求 A(2^m-1,n)
		ans=ans*(tmp-i)%M;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：AC_love (赞：2)

根据异或的性质，显然一段连续的异或和可以用前缀和的异或表示。

也就是：

$$a_l \oplus a_{l + 1} \oplus \cdots \oplus a_{r - 1} \oplus a_r = pre_r \oplus pre_{l - 1}$$

我们希望这玩意不等于 $0$，其实就是希望 $pre_r \oplus pre_{l - 1}$ 这玩意不等于 $0$。

我们知道，一个数只有异或它自己的时候才会得到 $0$，因此我们其实就是希望 $pre$ 尽量不要重复。

那么 $pre$ 有多少种不同的取值呢？

发现是从 $0$ 到 $2^m - 1$ 一共 $2 ^ m$ 种。

在这 $2^m$ 个数中选 $n$ 个数，顺序不同可以得到不同的数列，显然是排列数 $A_{2^m}^n$。

直接套公式即可。

代码实现如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 9;

int n, m;
int p = 1;
int ans = 1;

signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i = i + 1)
		p *= 2,
		p %= mod;
	for(int i = 1; i <= n; i = i + 1)
		ans *= (p - i),
		ans %= mod;
	cout << (ans % mod + mod) % mod;
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

duel 到这题了，写篇题解讲讲我的思路。

令 $b$ 为 $a$ 的异或前缀和。由于 $a$ 是 $b$ 的差分，所以一个 $b$ 唯一对应一个 $a$，题目即求符合要求的 $b$ 的个数。则 $a_l\oplus a_{l+1}\oplus\cdots\oplus a_r\neq 0\Leftrightarrow b_{l-1}\oplus b_{r}\neq0$。即 $b$ 中元素各不相同。我们知道 $b_0=0$，所以 $b_i\neq0$，因此 $b_i\in[1,2^m-1]$。则答案为 $A_{2^m-1}^n$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int mod=1e9+9;

int main(){
    int n,m;cin>>n>>m;
    // (2^m-1)*(2^m-2)*...*(2^m-n)
    long long pw=1,c=1;
    for(int i=1; i<=m; i++) pw=pw*2%mod;pw--;
    for(int i=0; i<n; i++) c=c*(pw-i)%mod;
    cout<<c;
    return 0;
}
```

---

## 作者：Tjl0427 (赞：1)

# 题解：CF238A Not Wool Sequences
[题目传送门。](https://www.luogu.com.cn/problem/CF238A)

这是一个异或和的序列，用 [异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677#%E9%80%BB%E8%BE%91) 来做。

异或的性质：
1. 归零律：$a \oplus a = 0$。
2. 恒等律：$a \oplus 0 = a$。
3. 交换律：$a \oplus b = b \oplus a$。
4. 结合律：$a \oplus b \oplus c = a \oplus ( b \oplus c)$。
5. 自反：$a \oplus b \oplus a = b$。
6. $d = a \oplus b \oplus c$ 可以推出 $a = d\oplus b \oplus c$。

### 思路：
建一个数组 $b : b_0 = 0,b_i = a_i \oplus b_{i - 1}$，由性质不难得到：$a_i = b_{i - 1}\oplus b_i$，所以 $a_l \oplus a_{l + 1}\oplus ...\oplus a_r \ne 0 \longrightarrow b_{l - 1}\oplus b_r \ne 0$，结合题目，不难发现数组 $b$ 中的元素互不相同。

由 $a_i = b_{i - 1}\oplus b_i$ 可得：$b_i \in [1,2^m]$，答案就是在长度为 $n$ 的数组的每个元素大小 $[1,2^m]$ 且互不相同时的个数，也就是：$A^n_{2^m}$。

### 代码：
```c
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9;
long long ans=1,p=1;
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
    	p=(p*2)%mod;
    }
    for(int i=1;i<=n;i++){
    	ans=(ans*(p-i))%mod;
    }
    cout<<ans<<"\n";
    return 0;
}
```
拜拜！

---

## 作者：czh___ (赞：0)

### 思路：
列举：任何情况下，$0$ 做一个子区间，一定会出现 $0$ 的情况，所以任何时候都不选 $0$；当 $n=1$ 时，不能为 $0$，所以有 $2^m-1$ 种情况；当 $n=2$ 时，第一位就有 $2^m-1$ 种情况,
第二位和第一位不相等， 第二位就有 $2^m-2$ 种情况；
当 $n=3$ 时，
第三位与第二位不相等，且不等于第二位和第一位的异或，所以有 $2^m-3$ 种情况；

……

以此类推

代码：

```cpp
#include<bits/stdc++.h>
#define mod 1000000009
#define int long long
using namespace std;
int n,m,s,mi;
int ksm(int m,int k,int q){
    int ans=1%q,t=m;;
    while(k){
        if(k&1)
            ans=ans*t%q;
        t=t*t%q;
        k>>=1;
    }
    return ans;
}
signed main(){
    cin>>n>>m;
    s=ksm(2,m,mod)-1;
    mi=1;
    for(int i=1;i<=n;i++)
        mi=mi*(s-i+1)%mod;
    cout<<mi<<endl;
    return 0;
}
```

拜拜！

---

