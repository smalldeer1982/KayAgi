# AND 0, Sum Big

## 题目描述

#### 题目大意：

给定两个正整数 $n$ 和 $k$ ，求有多少个序列满足下列条件：

1. 序列中的所有元素都在 $[0,2^k-1]$ 之间。
2. 它的所有元素的与运算之和为 $0$ 。
3. 它的元素之和是尽可能大的。

答案对 $10^9+7$ 取模。

## 样例 #1

### 输入

```
2
2 2
100000 20```

### 输出

```
4
226732710```

# 题解

## 作者：翼德天尊 (赞：3)

我们一个条件一个条件地来分析。

设给定序列 $a$。

首先考虑第一个条件 $0\le a_i\leq 2^k-1$。由此可知，我们可以将每一个数 $a_i$ 表示成一个长度为 $k$ 的二进制数。

再考虑第二个条件，由于所有数的与运算和为 $0$，所以我们可以知道，每一个数表示成二进制后，每一位都将有一个数字为 $0$。

第三个条件，因为元素之和尽可能大，所以我们再满足第二个条件的前提下，要将二进制位上所有的 $0$ 变成 $1$。

将三个条件结合起来，我们会发现，转二进制后，每一位都有 $n$ 种情况 （一个 $0$ 和 $n-1$ 个 $1$ 的排列），一共有 $k$ 位，所以答案为 $n^k$。用快速幂输出即可。

记得开 $\text{long long}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t; 
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
long long ksm(long long x,long long y,int mod){
	long long ans=1,k=x;
	while (y){
		if (y&1) ans=ans*k%mod;
		y>>=1;
		k=k*k%mod;
	}
	return ans;
}
int main(){
	t=read();
	while (t--){
		int n=read(),k=read();
		printf("%lld\n",ksm(n,k,1e9+7));
	}
	return 0;
}
```


---

## 作者：TernaryTree (赞：2)

## 题目大意

给定 $n, k$，你需要建立一个 $n$ 个元素的序列 $s$，使其有 $\forall 0\le i\lt n, \exists s_i \in [0, 2^k)$； $s$ 中所有元素进行与运算的值为 $0$，并且使 $\sum_{i=0}^{n - 1}s_i$ 最大。求有多少种不同序列。

## 解题思路

将 $s_i$ 转换为二进制，因为使 $s$ 中所有元素进行与运算的值为 $0$，且 $\sum_{i=0}^{n - 1}s_i$ 最大，所以每个数字只有 $1$ 位上为 $0$，其他都为 $1$，且 $0$ 的出现位置互不相同。那么这题就转换成了排列组合问题。每种 $0$ 都有 $n$ 种选法，所以不难看出，答案即为 $n^k$。

## 主要算法

本题主要算法：**幂运算**。

因为 $k\le 20$，所以我们可以从对 $1$ 乘 $k$ 次 $n$，就可以得到 $n^k$：

```cpp
int power(int base, int freq, int mod) {
    int ans = 1;
	for (int i = 0; i < freq; i++) {
        ans *= base;
        ans %= mod;
    }
    return ans;
}
```

时间复杂度：$O(k)$。

***

这里重点介绍的是：**快速幂**。

我们知道，乘方运算有结合律，即 $x^a\times x^b = x^{ab}$。

所以我们就可以对 $f(n,k,p) = n^k \ \bmod \ p$ 进行分解：

$$ f(n,k,p) = \begin{cases} 
f(n,\frac12k,p)^2\ \bmod\ p  & (k\ \bmod\ 2 = 0)  \\
f(n,\frac12(k-1),p)^2\ \times n \ \bmod\ p  &(k\ \bmod\ 2 = 1)
 \end{cases}$$
 
代码就不难写了：

```cpp
int power(int base, int freq, int mod) {
	int ans = 1, tmp = base;
	while (freq > 0) {
		if (freq % 2 == 1) ans = ans * tmp % mod;
		freq /= 2;
		tmp = tmp * tmp % mod;
	}
	return ans;
}
```

时间复杂度：$O(\log k)$。适用于指数较大的情况。

## 坑点分析

开 `long long`。

## 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int power(int base, int freq, int mod) {
	int ans = 1, tmp = base;
	while (freq > 0) {
		if (freq % 2 == 1) ans = ans * tmp % mod;
		freq >>= 1;
		tmp = tmp * tmp % mod;
	}
	return ans;
}

const int p = 1e9 + 7;
int t, n, k;

signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		cout << power(n, k, p) << endl;
	}
	return 0;
}
```

---

upd 2022.2.1: 修改了部分字母及公式错误。

---

## 作者：dead_X (赞：2)

## 题意
求长度为 $n$，每个数为 $[0,2^k)$ 之间的整数，所有数 $\text{and}$ 和等于 $0$，所有数的和最大的序列个数。

$n\leq 10^5,k\leq 20$。
## 思路
由于 $\text{and}$ 和对于每一位独立，我们也对于一位独立考虑。

于是问题转化成了这样：

求长度为 $n$，每个数为 $0$ 或 $1$，存在一个 $0$，所有数的和最大的序列个数。

显然这个问题非常好解决，最大值即为 $n-1$，实现方法为在某一个数上放 $0$，其余全放 $1$，共 $n$ 种方法。

因此每一位有 $n$ 种方法，答案即为 $n^k$。
## 代码
```cpp
// Problem: B. AND 0, Sum Big
// Contest: Codeforces - Codeforces Round #716 (Div. 2)
// URL: https://codeforces.com/contest/1514/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
signed main()
{
    for(int T=read();T--;)
    {
    	int n=read(),m=read();
    	int ans=0;
    	printf("%lld\n",qp(n,m));
    }
	return 0;
}
```

---

## 作者：LinkZelda (赞：2)

- **题意简述**：

给定 $n,k$ ，你需要在 $0\sim 2^k-1$ 中选出 $n$ 个数，使得这些数进行与运算后的结果为 $0$，同时保证这些数的和为最大可能的和。问一共有多少种选法。

- $Solution$：

我们考虑把每个数改成二进制的形式，因为要保证所有数的和是**保持不变为最大值**的。那么这 $n$ 个数的每一位上只能有一个数的那一位为 $0$ ，剩下 $n-1$ 个数那一位必须为 $1$。

那么问题就转化为：这 $k$ 个二进制位上的 $0$ 要在 $n$ 个数中选一个位置，问一共有多少种选法。每一个 $0$ 都有 $n$ 中选法，由乘法原理得，答案为 $n^k$ 。直接快速幂或者暴力计算即可，时间复杂度为 $O(\log k)$ 或 $O(k)$。

- [代码](https://www.luogu.com.cn/paste/crnbg25f)

---

## 作者：江户川·萝卜 (赞：1)

### 题目大意
构造一个长度为 $n$ 的数列，其所有元素小于 $2^k$ 且所有元素的 $\operatorname{and}$ 和为0，且总和最大。输出方案数 $\bmod\ 10^9+7$ 的值。

---
$\operatorname{and}$ 为 0，即数列在二进制下每一位都至少有一个 0。要总和最大，即每一位只有一个 0。对于每一位都有 $n$ 个位置可能为 0，根据乘法原理，$k$ 位就是 $n^k$ 种方案。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const long long mod=1e9+7;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,k;
		scanf("%d%d",&n,&k);
		long long ans=1ll;
		for(int i=1;i<=k;i++)
			ans=(ans*n)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：wheneveright (赞：1)

## 题意

$T$ 组数据，每组中给出 $n,k(1\le n\le 100000,1\le k\le20)$，求满足 $a_1 \operatorname{and} a_2 \operatorname{and} \cdots \operatorname{and} a_n = 0,(a_i\in[0,2^k-1])$ 且 $\sum a$ 最大的方案数。

## 分析

思考 $\operatorname{and}$ 运算的本质：任意一个二进制位上为 $0$ 时结果上这一位也为 $0$。所以要保证每一位上至少有一个数字为 $0$，要保证最大，也就是说每个二进制位选择任意一个数能保证结果为 $0$，再转化一下就变成了 $n^k$ 指的是每个二进制位都可以在 $n$ 中任意选一个。 

## 代码

因为 $k$ 最大才 $20$ 所以不用快速幂。代码非常短。

```cpp
# include <bits/stdc++.h>
using namespace std;
long long T, K, N, res;
int main () {
	cin >> T;
	while (T--) {
		cin >> N >> K; res = 1;
		while (K--) res = (res * N) % 1000000007;//计算 n 的 k 次方，要取模
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：TianTian2008 (赞：0)

所有元素在 $[0,2^k)$ 之间，表示只需考虑二进制下的前 $k$ 位。

要求所有元素按位与结果为 $0$，表示对于每个二进制位至少有一个元素在这位上为 $0$。

要使和尽可能大，只需让每一个二进制位恰有一个元素在这位上为 $0$ 即可。

考虑如何对方案进行计数，每一个二进制位都需有且仅有一个元素在这位上为 $0$，显然 $n$ 个元素都有可能，每个二进制位的方案数相乘即得 $n^k$。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000007
using namespace std;
typedef long long ll;
ll t,n,k;
ll ksm(ll x,ll y)//快速幂。因为值域较小，若直接暴力计算也可通过
{
	ll res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		printf("%lld\n",ksm(n,k));
	}
	return 0;
}
```

---

## 作者：Daidly (赞：0)

### 题意：

构造一个序列 $a_n$，使得 $a_i\in[0,2^k-1]\cup\mathbb{Z}$，并且所有数 $\text{and}$ 和等于 $0$，保证所有数的和最大，求这样的序列个数。

### 思路

考虑和最大，则每个数的二进制都为 $k$ 位。

考虑所有数 $\text{and}$ 和等于 $0$，则每一个数在二进制中有且只有一个 $0$，且这些 $0$ 的所在位数不相同。

因为有 $n$ 个数，有 $k$ 位，所以有 $n^k$ 种方法。

快速幂即可。

### 代码

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
ll t,n,k;
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}return ans;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		cout<<qpow(n,k)<<endl;
	}
}
```
不会快速幂的[戳这里](https://www.luogu.com.cn/problem/solution/P1226)。

---

## 作者：Ryo_Yamada (赞：0)

> 构造一个 $n$ 个数的序列 $A$，使：$0 \leq A_i \leq 2^k - 1$，$A_1 \And A_2 \And \ldots \And A_n=0$，且，$\sum A_i$ 最大。问方案数 $\!\!\mod 10^9 + 7$。

将 $A_i$ 写成二进制，可以发现一共有 $k$ 位，而序列与的值为 $0$，则第 $j$ 位至少有一个 $A_i$ 是 $0$。而又要求 $\sum A_i$ 最大，则每一位有且仅有一个 $A_i$ 是 $0$。对于每一位分配一个 $i$，答案就是 $n^k \!\!\mod p$。

$k$ 很小，快速幂或循环求解都可。

---

## 作者：yzy1 (赞：0)

最佳情况是 $n$ 个数的 $k$ 个二进制位中，每一位都是 $n-1$ 个数为 $1$，$1$ 个为 $0$。

那么问题就变成了：一共有 $k$ 个位置，每个位置都要选一个 $1\sim n$ 的数，问有多少选择方案。答案为 $n^k$，快速幂计算即可。

复杂度：$O(\log k)$。

### Code:

```cpp
#define int ll

ll pow(ll a,ll b,const ll&m) {
	ll res=1;a%=m;
	while(b>0) {
		if(b&1)res=res*a%m;a=a*a%m,b>>=1;
	}
	return res;
}
 
const int mo = 1e9 + 7;
 
int n, k;
 
signed main() {
	re (_, in()) {
		in(n)(k);
		outl(pow(n, k, mo));
	}
	return 0;
}
```

---

