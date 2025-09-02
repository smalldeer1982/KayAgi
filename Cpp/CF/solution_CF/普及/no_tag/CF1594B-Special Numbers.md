# Special Numbers

## 题目描述

Theofanis really likes sequences of positive integers, thus his teacher (Yeltsa Kcir) gave him a problem about a sequence that consists of only special numbers.

Let's call a positive number special if it can be written as a sum of different non-negative powers of $ n $ . For example, for $ n = 4 $ number $ 17 $ is special, because it can be written as $ 4^0 + 4^2 = 1 + 16 = 17 $ , but $ 9 $ is not.

Theofanis asks you to help him find the $ k $ -th special number if they are sorted in increasing order. Since this number may be too large, output it modulo $ 10^9+7 $ .

## 说明/提示

For $ n = 3 $ the sequence is $ [1,3,4,9...] $

## 样例 #1

### 输入

```
3
3 4
2 12
105 564```

### 输出

```
9
12
3595374```

# 题解

## 作者：smyslenny (赞：4)

[更好的阅读体验](https://www.cnblogs.com/jcgf/#/c/subject/p/15388612.html)

## Description

> 如果一个正整数可以被表示为 $n$ 的若干个不同的非负整数次幂的和，则称这个正整数是特别的。求出第 $k$ 小的特别的数
> 

## Solution

我们拿 $n=2$ 举例，

序列为 $2^0,2^1,2^1+2^0,2^2,2^2+2^0,2^2+2^1,2^2+2^1+2^0,2^3\dots$

我们设二进制位的每一位 $i$ 表示 $n^i$ 这一位选不选。

将上述序列表示一下，

$1,10,11,100,101,110,111,1000,\dots$ 

将这个二进制序列转化为十进制，

$1,2,3,4,5,6,7,8,\dots$

我们发现，其实第 $k$ 位其实就是其对应的二进制的对应的位选与不选。

比如 $k=5$

也就是 $n^2+n^0$。


## Code

```cpp
/*
* @Author: smyslenny
* @Date:    2021.10.10
* @Title:   CF1594B
* @Main idea:找规律
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <vector>

#define int long long
#define INF 0x3f3f3f3f
#define orz cout<<"LKP AK IOI\n"
#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)>(b)?(a):(b)

using namespace std;
const int mod=1e9+7;
const int M=1e3+5;
int T,n,k;
int read()
{
	int x=0,y=1;
	char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0' && c<='9') { x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),k=read();
		int sum=1,Ans=0;
		for(int i=0;i<31;i++)
		{
			if(k&(1<<i))
				Ans=(Ans+sum)%mod;
			sum=(sum*n)%mod;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
```



---

## 作者：清烛 (赞：2)

## Description
$T$ 组数据，给定 $n,k$（$2\le n\le 10^9, 1\le k\le 10^9$）。定义一个正整数为 special 当且仅当其可以表示为若干个**互不相同**的 $n$ 的非负整数次幂之和。

输出从小到大的第 $k$ 个 special 数。

## Solution

我们不妨在 $n$ 进制下考虑问题，发现一个满足上述性质的数在 $n$ 进制下每一位的表示只能为 $1$ 或 $0$。现在要的是第 $k$ 个这样的数，我们不难发现将 $k$ 用二进制表示出来再用 $n$ 进制表示回去就能得到答案。

例如 $n = 3$ 时，要求第 $4$ 个 special 数，发现 $k = 4 = (100)_2$，所以我们输出 $(100)_3 = 3^2 = 9$。

## Implementation
每次维护一下 $n$ 的对应次幂即可，不需要写快速幂。时间复杂度 $O(T\log k)$。

```cpp
#include <cstdio>
const int mod = 1e9 + 7;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        int ans = 0;
        for (int pow = 1; k; k >>= 1, pow = 1ll * pow * n % mod) if (k & 1) ans = (ans + pow) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

不难的构造题。

对于每一个 $n^k(2\le n)$ 都有 $\sum_{i=1}^{k-1}n^i<n^k$，这是显然的。

所以一旦出现一个比当前任何一位都要高的更高位，这样的一个数的位置就会向后挪一倍，这样的一个关系就是二进制的关系。

这是就发现这样的一个数就是把 $k$ 上的每一个二进制下为 $1$ 的位数作为 $n$ 的指数然后求和。

形式化地，有：$\sum_{i}n^i|[\text{k 的第 i 二进制位上为 1}]$。

实现上，直接算指数复杂度太高，需要用一个快速幂来求。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long MOD=1e9+7;
long long pow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return ans;
}
long long T,n,m,ans;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		ans=0;
		for(int i=0;i<=30;i++)
		if(m&(1<<i)){
			ans=(ans+pow(n,i))%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：reailikezhu (赞：0)

把 $k$ 拆成二进制，然后对于每个二进制位为 $1$ 的位，设这是第 $i$ 位，直接加上 $n^i$ 就好。

注意别忘了取模。

不开 `long long` 见祖宗！！！

```cpp
#include<stdio.h>

const int p=1000000007;

int n,k;
int t;
bool er[200010],tot;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		long long poww=1;
		long long ans=0;
		for(int i=0;i<30;i++){
			if(k&1<<i) ans=(ans+poww)%p;
			poww=poww*n%p;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：WitheredZeal (赞：0)

## 题意  

多组数据，每次给你两个正整数 $n,k$，你需要求出第 $k$ 小的，能用若干个**不同**的 $n$ 的幂次之和表示的数。  

## 题解  

能用若干个**不同**的 $n$ 的幂次之和表示的数等价于在 $n$ 进制下仅由 1 和 0 构成的数。  

那么就是求出 $k$ 的二进制表示，然后对应到 $n$ 进制下即可。  

## 代码

```cpp
rd(n);rd(k);ans=0;
for (int i=31;i>=0;i--) if (k>>i&1) ans=(ans+ksm(n,i))%mod;
cout<<ans<<endl;
```

---

