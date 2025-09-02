# [ABC121D] XOR World

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc121/tasks/abc121_d

$ f(A,\ B) $ を $ A,\ A+1,\ ...,\ B $ の排他的論理和としたとき、$ f(A,\ B) $ を求めてください。

排他的論理和とは

整数 $ c_1,\ c_2,\ ...,\ c_n $ のビットごとの排他的論理和 $ y $ は、以下のように定義されます。

- $ y $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ c_1,\ c_2,\ ...,\ c_n $ のうち、二進表記した際の $ 2^k $ の位の数が $ 1 $ となるものが奇数個ならば $ 1 $、偶数個ならば $ 0 $ である。

例えば、$ 3 $ と $ 5 $ の排他的論理和は $ 6 $ です(二進数表記すると: `011` と `101` の排他的論理和は `110` です)。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 0\ \leq\ A\ \leq\ B\ \leq\ 10^{12} $

### Sample Explanation 1

$ 2,\ 3,\ 4 $ は $ 2 $ 進数でそれぞれ `010`, `011`, `100` です。 これらの排他的論理和は `101` であり、これを $ 10 $ 進数表記にすると $ 5 $ になります。

## 样例 #1

### 输入

```
2 4```

### 输出

```
5```

## 样例 #2

### 输入

```
123 456```

### 输出

```
435```

## 样例 #3

### 输入

```
123456789012 123456789012```

### 输出

```
123456789012```

# 题解

## 作者：zhangyaiwei (赞：9)

#### 题外话

本蒟蒻不知道什么奇奇妙妙的定理，只好自己手推了 QwQ

[也许更好的阅读体验](https://www.luogu.com.cn/blog/684245/solution-at-abc121-d)

------------

首先，我们要知道，由于异或被称为不进位加法的神秘性质，会产生如下~~化学~~反应： $x \oplus 1 = x + 1$ ( $x$ 为偶数)；$x \oplus 1 = x - 1$($x$ 为奇数)。

我们再来观察一下题目：
$$ans=l\oplus(l+1)\oplus(l+2)\oplus...\oplus r$$

根据上述性质可以转化为：
$$ans=l\oplus(l\oplus1)\oplus(l+2)\oplus((l+2)\oplus1)\oplus...\oplus r$$

不对呀，如果 $l$ 是奇数的话，该如何转换呢？

这时候，我们不防按 $l$ 的奇偶性进行分类讨论：

若 $l$ 为偶数：
$$ans=l\oplus(l\oplus1)\oplus(l+2)\oplus((l+2)\oplus1)\oplus...\oplus r$$

若 $l$ 为奇数：
$$ans=l\oplus(l+1)\oplus((l+1)\oplus1)\oplus(l+3)\oplus((l+3)\oplus1)\oplus...\oplus r$$

接下来该怎么办？拆括号！

若 $l$ 为偶数：
$$ans=l\oplus l\oplus1\oplus(l+2)\oplus(l+2)\oplus1\oplus...\oplus r$$
（$r$ 懒得变了）

若 $l$ 为奇数：
$$ans=l\oplus(l+1)\oplus(l+1)\oplus1\oplus(l+3)\oplus(l+3)\oplus1\oplus...\oplus r$$

再根据 $x\oplus x=0$ 的性质，将重复的消掉。可是，消掉多少？

这时候，我们不仅要看 $l$ 的奇偶，$r$ 的奇偶同样需要。

若 $l$ 为偶数：

- 若 $r$ 为偶数（共有奇数个数，去重后仅剩01与 $r$）：

 $~~~~ ans=(\Big(\frac{l-r}{2}\Big)\bmod2)\oplus r$ 

- 解释：$(l-r)$ 即为 $[l,r)$ 中元素的个数，除以 $2$ 表示去重后留下 $"1"$ 的数量。再模 $2$ 表示去重 $"1"$。最后异或上剩下的 $r$。

.

- 若 $r$ 为奇数（共有奇数个数，去重后仅剩01）

$~~~~ ans=\Big(\frac{l-r+1}{2}\Big)\bmod2$ 

- 解释：在 $r$ 为偶数的情况下去掉多余的 $r$ 即可~（由于不会剩下 $r$ ， $[l,r)$ 变为 $[l,r]$ ）

若 $l$ 为奇数：

- 若 $r$ 为偶数（共有偶数个数，去重后还剩 $l~r$ 与 01 ）

 $~~~~ ans=(\Big(\frac{r-l-1}{2}\Big)\bmod 2)\oplus l\oplus r$ 

- 解释： $(l-r-1)$ 即为 $(l,r)$ 中元素的个数，除以 $2$ 表示去重后留下 $"1"$ 的数量。再模 $2$ 表示去重 $"1"$ 。最后异或上剩下的 $r$ 与 $l$ 。

.

- 若$r$为奇数（共有奇数个数，去重后仅剩01与 $l$ ）

 $~~~~ ans=(\Big(\frac{r-l}{2}\Big)\bmod 2)\oplus l$ 

- 解释：在 $r$ 为偶数的情况下去掉多余的 $r$ 即可~（由于不会剩下 $r$ ， $(l,r)$ 变为 $(l,r]$ ）


------------


最后，上代码（+贴心注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;//不许CTJ哦
long long l,r;
int main(){
	cin>>l>>r;
	if(l%2==0){
		if(r%2==0) cout<<((((r-l)/2)%2)^r);
		else cout<<((r-l+1)/2)%2;
	}
	else{
		if(r%2==0) cout<<((((r-l-1)/2)%2)^l^r);
		else cout<<((((r-l)/2)%2)^l);
	}
} 
/*
l为偶数 
	l^(l+1)^(l+2)^...^r
	l^(l^1)^(l+2)^((l+2)^1)^...^r
	l^l^1^(l+2)^(l+2)^1^...^r
	r为偶数
		(((r-l)/2)%2)^r
	r为奇数
		((r-l+1)/2)%2;
l为奇数
	l^(l+1)^(l+2)^...^r
	l^(l+1)^((l+1)^1)^(l+3)^((l+3)^1)^...^r
	l^(l+1)^(l+1)^1^(l+3)^(l+3)^1^...^r
	r为偶数
		(((r-l-1)/2)%2)^l^r
	r为奇数
		(((r-l)/2)%2)^l
*/ 
```
PS:在输出的时候一定一定要注意带好括号，尤其是使用cout时，位运算的神奇优先级会让你的代码原地升天。

---

## 作者：hxhhxh (赞：6)

## 大意

求 $ \oplus_{i=l}^r i $

## 思路

$ \oplus_{i=l}^r i = (\oplus_{i=1}^{l-1} i) \oplus (\oplus_{i=1}^r) $

设 $ S_i=\oplus_{j=1}^{i} j $ ，所以 $ ans=S_i \oplus S_{j-1} $ 

当 $ 4\mid i $ 且 $ S_i=i $ ：

设 $ (\overline{a_1a_2\dots a_k})_2=\frac{i}{4} $ ，其中 $ a_i\in\{0,1\} $ ，所以

$$ i=(\overline{a_1a_2\dots a_k00})_2 $$

则有
$$
\begin{cases}
S_{i+1} & = i \oplus (i+1)\\
 & = (\overline{a_1a_2\dots a_k00})_2 \oplus (\overline{a_1a_2\dots a_k01})_2\\
 & = (000\dots 01)_2 = 1\\
S_{i+2} & = 1 \oplus (i+2)\\
 & = (000\dots 01)_2 \oplus (\overline{a_1a_2\dots a_k10})_2\\
 & = (\overline{a_1a_2\dots a_k11})_2\\
 & = i+3\\
S_{i+3} & = (i+3) \oplus (i+3) = 0\\
S_{i+4} & = 0 \oplus (i+4) =i+4
\end{cases}
$$
所以 $ S_{i+4} = i+4 $ 。又因为 $ S_0 = 0 $ ，所以对于所有 $ 4\mid i $ ，有

$$
\begin{cases}
S_i=i\\
S_{i+1}=1\\
S_{i+2}=i+3\\
S_{i+3}=0
\end{cases}
$$

所以

$$
S_i=
\begin{cases}
i & i\equiv 0\pmod{4}\\
1 & i\equiv 1\pmod{4}\\
i+1 & i\equiv 2\pmod{4}\\
0 & i\equiv 3\pmod{4}\\
\end{cases}
$$

## 代码
注意特判 $ l=0 $
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int solve(int x){
	return (x%4==1)?1:(x%4==2)?x+1:(x%4==0)?x:0;
}
int l,r;
signed main(){
	scanf("%lld %lld",&l,&r);
	printf("%lld",solve(r)^solve(l-1));
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：3)

### 大意

求 $ \oplus^{b}_{i=a} i $ 。

### 思路

由于异或可逆，只需要求出 $ (\oplus^{a-1}_{i=1} i) \oplus (\oplus^{b}_{i=1} i) $ 即可。

找规律发现：

$$ \oplus^{n}_{i=1} i = \begin{cases}
n & (n \mod 4 = 0)\\
1 & (n \mod 4 = 1)\\
n+1 & (n \mod 4 = 2)\\
0 & (n \mod 4 = 3)\\
\end{cases}  $$

证明如下：

每四个自然数分一组，那么它们可以表示为 $ x + y $ 。

使得其中每一组中的 $ x $ 都相等， $ y $ 分别为 $ 0 $ ， $ 1 $ ， $ 2 $ ， $ 3 $ 。

第一个数异或起来是 $ x + 0 $ （此时相当于 $ x + y $ ）。

前两个数异或起来是 $ (x \oplus x) + (0 \oplus 1) = 0 + 1 = 1 $ 。

前三个数异或起来是 $ (x \oplus x \oplus x) + (0 \oplus 1 \oplus 2) = x + 3 $ （此时相当于 $ x + y + 1 $ ）。

这四个数异或起来是 $ (x \oplus x \oplus x \oplus x) + (0 \oplus 1 \oplus 2 \oplus 3) = 0 + 0 = 0 $ 。

由于 $ a \oplus 0 = a $ ，这正好形成了一个循环。

时间复杂度 $ O(1) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
long long doing(long long x){
    if(x==-1)return 0;
    if(x%4==1)return 1;
    if(x%4==2)return x+1;
    if(x%4==3)return 0;
    return x;
}
int main(){
    long long l,r;
    cin>>l>>r;
    printf("%lld\n",doing(l-1)^doing(r));
    return 0;
}
```

---

## 作者：阿丑 (赞：1)

[原题](https://www.luogu.com.cn/problem/AT4323)

#### 前置知识：

位运算。

#### 题意：

- 求 $A,\,A+1,\,\dots,\,B$ 的异或和。

- $0\le A\le B\le 10^{12}$。

为叙述方便，下文提到“第 $k$ 位”时默认是指二进制下的第 $k$ 位，且 $k\ge0$，即指 $2^k$ 这一位。

#### 分析：

暴力显然超时。我们可以直接从定义出发，计算 $A,\,A+1,\,\dots,\,B$ 的第 $k$ 位有多少 $1$，如果是奇数，则答案第 $k$ 位为 $1$，否则为 $0$。

进行差分。$A,\,A+1,\,\dots,\,B$ 中第 $k$ 位为 $1$ 的数量，即 $0,\,1,\,\dots,\,B$ 中第 $k$ 位为 $1$ 的数量减去 $0,\,1,\,\dots,\,A-1$ 中第 $k$ 位为 $1$ 的数量。

问题转化为在较快的时间内求 $0,\,1,\,\dots,\,X$ 中第 $k$ 位为 $1$ 的数的数量。

设 $X=2^{k+1}c+d$（$0\le d<2^{k+1}$）。

对于所有在 $[0,\,2^{k+1}c)$ 中的数：

- 如果数 $x$ 的第 $k$ 位为 $1$，则 $x-2^k$ 的第 $k$ 位为 $0$ 且也在这个范围内；

- 如果数 $x-2^k$ 的第 $k$ 位为 $0$，则 $x$ 的第 $k$ 位为 $1$ 且也在这个范围内。

容易发现 $x,\,x-2^k$ 是一一对应的，即第 $k$ 位为 $1$ 的数和 第 $k$ 位为 $0$ 的数是一一对应的。故这个区间内第 $k$ 位为 $1$ 的数的数量为区间大小的一半。

再考虑 $[2^{k+1}c,\,X]$ 中的数。容易发现 $2^{k+1}c$ 对答案并没有贡献，所以这一部分的数与 $[2^{k+1}c-2^{k+1}c,\,X-2^{k+1}c]$ 即 $[0,\,d]$ 等价。

分类讨论。若 $d<2^k$，显然所有数的第 $k$ 位均为 $0$，对答案贡献为 $0$。若 $d\ge2^k$，则 $[0,\,2^k)$ 中所有数第 $k$ 位为 $0$，$[2^k,\,d]$ 中所有数第 $k$ 位都为 $1$，$1$ 的数量即为这个区间的大小。

至此，我们就求出了 $[0,\,X]$ 中有多少数第 $k$ 位为 $1$。

#### 思路：

1. 根据定义逐位求解。

2. 分类讨论计算 $[0,X]$ 中有多少数第 $k$ 位为 $1$。

---

没有太多技巧，直接给出代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long L, R, ans;	//记得开 long long
long long cal(long long x, int k) {
	if(x<0) return 0;	//L-1 可能为 -1，此时返回 0
	long long c=x>>k+1, d=x-(c<<k+1), res=0;
	res+=c<<k;	//即 c<<k+1>>1
	if(d>=1ll<<k) res+=d-(1ll<<k)+1;
	return res;
}
int main() {
	scanf("%lld%lld", &L, &R);
	for(int k=0; k<=40; ++k) if(cal(R, k)-cal(L-1, k)&1) ans+=1ll<<k;
	//如果 cal(R)-cal(L-1) 为奇数则累计答案
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

# [ABC121D] XOR World

### 题目描述

令 $f(A, B)$ 为 $A,\,A+1,\,\dots,\,B$ 的异或和。求 $f(A, B)$。


- $0\ \leq\ A\ \leq\ B\ \leq\ 10^{12}$



## 思路

初看本题，我们自然会想到写一个循环不断异或，毕竟伟大的 C++ 可是给我们提供了方便快捷的异或运算符 `^` 的。

但是当我们看到数据范围时，我们发现循环会超时，那么我们就不得不去探究一点数学性质了。

**性质1：** (其实这个性质我们用不到)

$\oplus^{b}_{i=a}  i = (\oplus^{a-1}_{i=1} i) \oplus (\oplus^{b}_{i=1} i)$

**性质2：** 异或运算满足交换律、结合律。

**性质3：** $0$ 异或上任何数 $n$，数的值仍然为 $n$。

**规律1：** 每四个连续自然数 $2n\sim2n+3$ 的异或和都相同。


我们设这 $4$ 个自然数分别为 $n,n+1,n+2,n+3$，进行异或运算，假设 $n$ 为偶数，则 $n$ 在二进制下的第 $0$ 位（即 $2^0$）为 $1$，$n+1$ 在二进制下的第 $0$ 位为 $1$，并且其他位与 $n$ 相同，所以 $n\oplus n+1=1$。

其实到这里我们就已经找到规律了，但是我们考虑到 $1\oplus1=0$，$0\oplus1=1$ 这样轮换还是比较麻烦的，所以我们就继续往下考虑。

我们考虑 $n+2\oplus n+3=1$，又根据以下规律。

$\begin{cases}1\oplus1=0\\0\oplus0=0\end{cases}$

可以得出 $(n\oplus n+1)\oplus(n+2\oplus n+3)=0$，考虑 $\oplus$ 运算**支持结合律**，我们可以得到 $n\oplus n+1\oplus n+2\oplus n+3=0$，于是我们就可以将每四个数作为循环节，循环节之间的异或和都是 $0$。这样我们只需要考虑循环节之外余下的哪几个数，将他们的异或和计算出来即可。

**注意，每个循环节的 $n$ 必须为 $2$ 的倍数，否则不符合规律。**

## 代码实现

我们设置两个指针 $l,r$，先让它们指向 $l=a$，$r=b$，如果 $l$ 为奇数，则 $l=l+1$（为了让 $l$ 是偶数），把落单的 $a$ 先放在一边。

然后我们计算 $ t=\lfloor(r-l+1)/4\rfloor$ 得到循环节的个数（第一个循环节从 $l$ 开始），这样我们就可以得到最后一个循环节的末尾是 $l+t \times4-1$。这些循环节的异或和都是 $0$，我们之间忽略。

最后对于在最后一个循环节后面的 $≤3$ 个多余下来的值我们暴力异或即可，还有别忘了最开始被抛下的 $a$。

## Code

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N=2e6+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,ans,a,b;

signed main(){
    cin>>a>>b;
    int ta=0;
    if(a%2)ta=a,a++;
    int t=(b-a+1)/4;
    a+=4*t;
    for(int i=a;i<=b;i++){
        ans^=i;
    }
    ans^=ta;
    cout<<ans;
    return 0;
}
```




---

