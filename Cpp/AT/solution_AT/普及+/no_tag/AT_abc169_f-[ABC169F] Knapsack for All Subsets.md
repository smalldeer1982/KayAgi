# [ABC169F] Knapsack for All Subsets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc169/tasks/abc169_f

長さ $ N $ の正整数列 $ A_1 $, $ A_2 $, $ \ldots $, $ A_N $ と正の整数 $ S $ が与えられます。  
 集合$ \{1,\ 2,\ \ldots\ ,\ N\ \} $ の空でない部分集合 $ T $ について、$ f(T) $ を以下のように定めます。

- $ T $ の空でない部分集合 $ \{x_1,\ x_2,\ \ldots\ ,\ x_k\ \} $ であって、 $ A_{x_1}+A_{x_2}+\cdots\ +A_{x_k}\ =\ S $ をみたすものの個数

$ T $ として考えられる集合は $ 2^N-1 $ 通りありますが、そのすべてに対する $ f(T) $ の和を求めてください。ただし、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ S\ \leq\ 3000 $
- $ 1\ \leq\ A_i\ \leq\ 3000 $

### Sample Explanation 1

それぞれ以下のように計算できて、その和は $ 6 $ です。 - $ f(\{1\})\ =\ 0 $ - $ f(\{2\})\ =\ 0 $ - $ f(\{3\})\ =\ 1 $ ( $ \{3\} $ の $ 1 $ つ) - $ f(\{1,\ 2\})\ =\ 1 $ ( $ \{1,\ 2\} $ の $ 1 $ つ) - $ f(\{2,\ 3\})\ =\ 1 $ ( $ \{3\} $ の $ 1 $ つ) - $ f(\{1,\ 3\})\ =\ 1 $ ( $ \{3\} $ の $ 1 $ つ) - $ f(\{1,\ 2,\ 3\})\ =\ 2 $ ( $ \{1,\ 2\},\ \{3\} $ の $ 2 $ つ)

## 样例 #1

### 输入

```
3 4
2 2 4```

### 输出

```
6```

## 样例 #2

### 输入

```
5 8
9 9 9 9 9```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
3296```

# 题解

## 作者：_Tooler_Fu_ (赞：5)

妙妙题。

首先有一个显然的结论：对于一个**长度**为 $len$ 的集合 $H=\left \{  x_1 , x_2 ,... ,x_k \right \} $，若 $H$ 满足 $A_{x_1} +A_{x_2} + ... +A_{x_k}= S$，则它对于整体的贡献为 $2^{n-len}$。

一个感性的理解：每个选出来的集合 $T$ 中集合的贡献互不干扰，可以分开计算，那只要在 $T$ 中包含这个集合即可，这样的贡献就是有 $len$ 个元素必选，其余元素可选可不选的集合数，即为 $2^{n-len}$。

接下来就是求和为 $S$ 的 $H$ 的数目和长度了，一种思路是暴搜，但是复杂度会炸，还有一种思路就是背包，但是求出了集合个数如何求集合长度呢？

其实是不需要的，因为这东西可以直接算。

我们令 $dp_{i,j}$ 表示 选到了第 $i$ 个数，集合 $H=\left \{ A_1,A_2,...,A_i \right \} $ 中和为 $j$ 的子集的答案和。

容易推出 $dp_{i,j} = \frac{dp_{i-1,j-a_i}}{2} + dp_{i-1,j}$。

为什么呢？

不难发现，当多选一个数时，当前的答案就要除以 $2$，但当前的 $dp_{i,j}$ 又需要加上上一个 $i$ 时的答案，故有上式。

滚动数组后，上式变为：

$dp_j \gets dp_j + \frac{dp_{j-a_i}}{2}$。

代码如下：
```cpp
// Problem: F - Knapsack for All Subsets
// Contest: AtCoder - AtCoder Beginner Contest 169
// URL: https://atcoder.jp/contests/abc169/tasks/abc169_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//我是废物，我爱贺题！！！
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,x,y,z) for(long long i=x;i<=y;i+=z)
#define fd(i,x,y,z) for(long long i=x;i>=y;i-=z) 
const ll mod=998244353;
ll n,s,a[3005];
ll dp[3005];
ll qpow(ll x,ll y){
	ll tot=1;
	while(y){
		if(y&1){
			tot=tot*x;
			tot%=mod;
		}
		x=x*x;
		x%=mod;
		y>>=1;
	}
	return tot;
}
int main() {
	scanf("%lld%lld",&n,&s);
	f(i,1,n,1){
		scanf("%lld",&a[i]);
	}
	dp[0]=qpow(2,n);
	f(i,1,n,1){
		fd(j,s,a[i],1){
			dp[j]+=dp[j-a[i]]*qpow(2,mod-2);
			dp[j]%=mod;
		}
	}
	printf("%lld\n",dp[s]%mod);
	return 0;
}
```


---

## 作者：anonymous_Y (赞：0)

觉得其他题解里面有一个地方没有讲清楚然后理解了很久。

暴力很简单，对于正解，我们看看数据范围。观察到有一个关于 $a_i$ 的数据范围，一般来说解题的时候不会有关于 $a_i$ 的数据范围，加之题目要求方案数，所以我们可以考虑 $dp$ 进行解题。

不妨令 $f_{i,j}$ 表示前 $i$ 位和为 $j$ 的方案数和。此时有转移方程式。

```cpp
f[i][j]=f[i-1][j-a[i]]+2*f[i-1][j]
```

发现代码里有一个式子乘以了两倍，这一个点我理解很久。其实就是对于你没有加当前 $a_i$ 但是序列多了一个 $a_i$ 所以实际上会多出两倍的选择，要乘上两倍。这一点值得注意。

最后用滚动数组优化一下就结束了。

---

## 作者：Mierstan085 (赞：0)

CYEZ 模拟赛，没做出来，赛后写完了，写个题解。

容易看出一个结论，如果有一个序列 $L = \{x_i\}$，其中 $\sum A_{x_i} = S$，那么，这个序列的贡献为 $2^{n - |L|}$。

考虑 dp，其中 $f_{i, j}$ 代表选 $i$ 个数和为 $j$ 的方法之和，容易推出 $f_{i, j} = f_{i - 1, j - A_i} \div 2 + f_{i-1, j}$。

使用滚动数组可以优化成一维，这时原式为 $f_j = f_j + (f_j - a_i) \div 2$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;

const int N = 3e3 + 5;
int a[N], dp[N];
int ppow(int x, int y){
    int tot = 1;
    while (y){
        if (y & 1) tot = tot * x, tot %= MOD;
        x = x * x, x %= MOD, y >>= 1;
    }
    return tot;
}

signed main(){
    int n, s; cin >> n >> s;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    
    dp[0] = ppow(2, n);
    for (int i = 1; i <= n; i ++){
        for (int j = s; j >= a[i]; j --){
            dp[j] += dp[j - a[i]] * ppow(2, MOD - 2);
            dp[j] %= MOD;
        }
    }

	cout << dp[s] % MOD;
}
```

~~CYEZ 什么唐诗键盘。~~

---

