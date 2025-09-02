# Candies

## 题目描述

Recently Vova found $ n $ candy wrappers. He remembers that he bought $ x $ candies during the first day, $ 2x $ candies during the second day, $ 4x $ candies during the third day, $ \dots $ , $ 2^{k-1} x $ candies during the $ k $ -th day. But there is an issue: Vova remembers neither $ x $ nor $ k $ but he is sure that $ x $ and $ k $ are positive integers and $ k > 1 $ .

Vova will be satisfied if you tell him any positive integer $ x $ so there is an integer $ k>1 $ that $ x + 2x + 4x + \dots +       2^{k-1} x = n $ . It is guaranteed that at least one solution exists. Note that $ k > 1 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, one of the possible answers is $ x=1, k=2 $ . Then $ 1 \cdot 1 + 2 \cdot 1 $ equals $ n=3 $ .

In the second test case of the example, one of the possible answers is $ x=2, k=2 $ . Then $ 1 \cdot 2 + 2 \cdot 2 $ equals $ n=6 $ .

In the third test case of the example, one of the possible answers is $ x=1, k=3 $ . Then $ 1 \cdot 1 + 2 \cdot 1 + 4 \cdot       1 $ equals $ n=7 $ .

In the fourth test case of the example, one of the possible answers is $ x=7, k=2 $ . Then $ 1 \cdot 7 + 2 \cdot 7 $ equals $ n=21 $ .

In the fifth test case of the example, one of the possible answers is $ x=4, k=3 $ . Then $ 1 \cdot 4 + 2 \cdot 4 + 4 \cdot       4 $ equals $ n=28 $ .

## 样例 #1

### 输入

```
7
3
6
7
21
28
999999999
999999984```

### 输出

```
1
2
1
7
4
333333333
333333328```

# 题解

## 作者：PersistentLife (赞：3)

### 题目分析

如何简化：$x+2x+4x+...+2^{k-1}x$？

原式=$x(2^0+2^1+2^2+...+2^{k-1})$。

设 $S=2^0+2^1+2^2+...+2^{k-1}$。

则 $2S=2^1+2^2+2^3+...+2^k$。

所以 $2S-S=2^1+2^2+2^3+...+2^k-2^0-2^1-2^2-...-2^{k-1}=2^k-1=S$。

综上所述 原式=$x(2^k-1)$。

问题就转化成了找到一个数 $x$，使得 $2^k-1|\dfrac{n}{x}$ 。

### 代码实现

首先，我们写一个快速幂，如果大家不知道快速幂咋写，可以看看[这题](https://www.luogu.com.cn/problem/P1226)。

```cpp
long long fastPow(long long x,long long y)
{
    long long ret=1;
    while(y>0)
	{ 
        if(y&1) ret*=x; 
        x*=x;
        y>>=1;
    }
    return ret;
}
```

然后我们对于每一个 $n$ 去枚举 $k$，看看是否可以满足 $2^k-1|\dfrac{n}{x}$，如果满足就做一个除法求出 $x$ 后输出。

```cpp
long long n;
cin>>n;
for(int i=2;true;i++)
{
	int pp=(fastPow(2,i)-1);
	if(n%pp==0)
	{
		cout<<n/pp<<endl;
		break;
	}
}
```

最后献上完整代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long fastPow(long long x,long long y)
{
    long long ret=1;
    while(y>0)
	{ 
        if(y&1) ret*=x; 
        x*=x;
        y>>=1;
    }
    return ret;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n;
		cin>>n;
		for(int i=2;true;i++)
		{
			int pp=(fastPow(2,i)-1);
			if(n%pp==0)
			{
				cout<<n/pp<<endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：andyli (赞：2)

题意：  

给出正整数 $n$ ，找出一个正整数 $x$ 使得存在正整数 $k>1$ ，$x+2x+4x+...+2^{k-1}x=n$。  
$3\leq n\leq 10^9$。  

分析：  

$x+2x+4x+...+2^{k-1}x=n$ 可改写为 $x(2^k-1)=n$，即 $x$ 为 $n$ 的因数，因此只需枚举 $n$ 的因数 $m$，再判断是否存在正整数 $k$ 使得 $\dfrac{n}{m}=2^k-1$ 即可。  
判断时可枚举 $k$ ，也可直接判断 $n\geq 3$ 且 $2^{\left\lfloor \log_2{n}\right\rfloor+1}-1=n$。  

时间复杂度 $\mathcal O(\sqrt{n})$ 或 $\mathcal O(\sqrt{n}\log{n})$

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
// O(1) 判断 
inline bool check(int n) { return n >= 3 && (1 << (32 - __builtin_clz(n))) - 1 == n; }
// O(logn) 判断
/*
inline bool check(int n) {
    for (int i = 2; i <= 30; i++)
        if ((1 << i) - 1 == n)
            return true;
    return false;
}
*/
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        for (int i = 1; i * i <= n; i++)
            if (n % i == 0) {
                if (check(i)) {
                    writeln(n / i);
                    break;
                }
                if (check(n / i)) {
                    writeln(i);
                    break;
                }
            }
    }
    return 0;
}
```

---

## 作者：do_while_true (赞：2)

2020.4.30 我谢罪，粘错题解了

给出一个 $n$，请输出一个满足 $x+2x+4x+...+2^{k-1}x=n$ 的 $x$，其中 $k>1$。

$x(1+2+4+...+2^{k-1})=n$

$x(2^k-1)=n$

$x=n/(2^k-1)$

所以我们去枚举 $k$ ，然后看 $n$ 是否能整除 $2^k-1$ 即可，如果可以的话就输出 $n/(2^k-1)$

---

## 作者：Sora1336 (赞：1)

说来惭愧，我是打表做的。

本题是要在 $x(2^{k}-1)$ 中选出任意可能的 $x$ 。

所以，我将所有可能的 $2^k-1$ 都列举了出来，然后尝试能否被枚举出的 $x$ 整除。

$Code:$

```cpp
#include <iostream>
using namespace std;
int biao[]={1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647};	//表
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n;
		cin>>n;
		for(int x=1;;x++){
			if(n%biao[x]==0){			//如果可以整除
				cout<<n/biao[x]<<endl;	//输出
				break;					//及时跳出循环
			}
		}
	}
}
```


---

## 作者：神眷之樱花 (赞：0)

# 题解
仔细一看，发现 $x$ 的次数都是相等的，而每项是 $2$ 的次幂，合并同类项之后，系数就变成了等比数列，所以用等比数列求和公式，或者错位相减法，就能把柿子化简。
### 等比数列求和公式
$S = \frac{a_1 * (1 - q ^ n)}{1 - q}$

$$ 1 + 2 + 4 + … + 2 ^k - 1 
= \frac{1 * (1 - 2 ^ {k})}{1 - 2}
=2 ^ {k} - 1$$
### 错位相减法
设 $S = 1 + 2 + 4 + … + 2 ^k - 1$。

那么 $2 * S = 2 + 4 + 8 + … + 2 ^ k$。

两柿相减得：$S = 2 ^ k - 1$。

所以题目就转化为了 $(2 ^ k - 1) * x = n$。

预处理一下 $2 ^ k - 1$ 的值，判断能不能整除就好了。
# 代码
```cpp
#include<cstdio>
#include<iostream>

using namespace std;

typedef long long LL;

LL pow[35]; int t, n;

int main() {
	pow[0] = 1;
	for(int i = 1; i <= 31; i++)
		pow[i] = pow[i - 1] << 1;
	for(int i = 0; i <= 31; i++)
		--pow[i];
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 2; i <= 31; i++)
			if(n % pow[i] == 0) {
				printf("%lld\n", n / pow[i]);
				break;
			}
	}
	return 0;
}
```

---

