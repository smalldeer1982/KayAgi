# Multicolored Marbles

## 题目描述

Polycarpus plays with red and blue marbles. He put $ n $ marbles from the left to the right in a row. As it turned out, the marbles form a zebroid.

A non-empty sequence of red and blue marbles is a zebroid, if the colors of the marbles in this sequence alternate. For example, sequences (red; blue; red) and (blue) are zebroids and sequence (red; red) is not a zebroid.

Now Polycarpus wonders, how many ways there are to pick a zebroid subsequence from this sequence. Help him solve the problem, find the number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Let's consider the first test sample. Let's assume that Polycarpus initially had sequence (red; blue; red), so there are six ways to pick a zebroid:

- pick the first marble;
- pick the second marble;
- pick the third marble;
- pick the first and second marbles;
- pick the second and third marbles;
- pick the first, second and third marbles.

It can be proven that if Polycarpus picks (blue; red; blue) as the initial sequence, the number of ways won't change.

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
11
```

# 题解

## 作者：123456zmy (赞：9)

题意：  
求在一个长度为 $n$ 的由两种不同颜色交替组成的串中总共有多少个由两种不同颜色交替组成的子序列。
___
可以用两个 dp 数组来写，转移方程如下：
$$dp1_i=dp2_{i-1}+dp1_{i-2}+1,i\bmod2=1$$
$$dp2_i=dp1_{i-1}+dp2_{i-2}+1,i\bmod2=0$$
最后的答案是 $dp1_n+dp1_{n-1}+dp2_n+dp2_{n-1}$（因为按照转移方程推出来的数中间是间隔了一个 $0$ 的，但是又不想特判）。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp1[1000001],dp2[1000001];
int main()
{
	scanf("%d",&n);
	dp1[1]=1;
	for(int i=2;i<=n;i++)if(i&1)dp1[i]=(dp1[i-2]+dp2[i-1]+1)%1000000007;
	else dp2[i]=(dp2[i-2]+dp1[i-1]+1)%1000000007; 
	printf("%d",(dp1[n]+dp2[n]+dp1[n-1]+dp2[n-1])%1000000007);
	return 0;
}
```
虽然已经足够过这道题了，但这个还是可以优化的。经过观察发现，可以转化成以下的递推式：
$$a_1=a_1+a_2+1,i\bmod2=1$$
$$a_2=a_1+a_2+1,i\bmod2=0$$
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a1,a2;
int main()
{
	scanf("%d",&n);
	while(n--)if(n&1)a1=(a1+a2+1)%1000000007;
	else a2=(a1+a2+1)%1000000007;
	printf("%d",(a1+a2)%1000000007);
	return 0;
}
```

---

## 作者：Areka6219 (赞：3)

## 题意


给定一个长度为n的由两种不同颜色**交替**组成的序列，求总共有多少个由两种不同颜色**交替**组成的子序列。

PS：一定要看到这个交替

## 求解

考虑 `DP` 求解， 前面题解已经详细讲述如何利用二维数组并分情况讨论进行求解，这里我们进行一维数组的求解。

~~PS:滚动数组后你甚至可以只开 $4$ 个变量。~~

1. $dp_i$ 表示当前长度为 `i` 的序列中的种数。

1. 考虑 `i - 1` 个序列加入第 `i` 个数后产生的贡献，可以发现，常数 $2$ 来自 `i` 对全串及 `i - 1` 节点的贡献， `i` 对其他节点的贡献在数值上等于 $dp _ {i - 2}$。

1.  那么转移方程为 $dp_i = dp_{i-1} + dp_{i - 2} + 2$。


这样就可以写出程序。

## Code
```cpp

int n;
const int p = 1e9 + 7, maxn = 1e6 + 1;

int dp[maxn];

signed main() {
	n = read();
	dp[1] = 1;
	for(int i = 2; i <= n; ++i)
		dp[i] = (dp[i - 1] + dp[i - 2] + 2) % p;
	
	printf("%lld\n", dp[n]);
}	
```

## 滚动数组
```cpp
int n;
const int p = 1e9 + 7;

int a, b, c;

signed main() {
	n = read();
	if(n == 1) {
		puts("1");
		return 0;
	}
	b = 1;
	for(int i = 2; i <= n; ++i) {
		a = (b + c + 2) % p;
		c = b, b = a;
		c %= p, b %= p;
	}
	printf("%lld\n", a);
}	
```

注意在 $n=1$ 的情况下的特判。

## 优化

还没完，我们还可以继续找规律。

观察 `dp` 式子可以发现 $dp_i = dp_{i-1}+dp_{i-2}$ 恰好为 `Fibonacci` 数列的递推公式，通过推导 $\Delta$ 可知，$dp_i$ 恰好为 $Fibonacci(n + 3) - 2$，这样我们就可以在 $O(log_2 n)$ 的速度下解决本题。

### Code
```cpp

int n;
const int p = 1e9 + 7;

struct Martix {
    int f[3][3];

    Martix() {
        memset(f, 0, sizeof(f));
    }

    friend Martix operator * (const Martix &a, const Martix &b) {
        Martix c;
        for(int i = 1; i <= 2; ++i) 
            for(int j = 1; j <= 2; ++j) 
                for(int k = 1; k <= 2; ++k)
                    c.f[i][j] += a.f[i][k] * b.f[k][j], c.f[i][j] %= p;
        return c;
    }
}A, B;

void init() {
    A.f[1][1] = A.f[1][2] = A.f[2][1] = 1;
    B.f[1][1] = B.f[1][2] = 1;
}

void Get_xr(int b) {
    while(b) {
        if(b & 1) B = B * A;
        A = A * A;
        b >>= 1;
    }
}

signed main() {
    n = read() + 3;
    init();
    
    if(n <= 2) 
        puts("1");

    else
        Get_xr(n - 2), printf("%lld\n", (B.f[1][1] - 2) % p);
    
    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

```

---

## 作者：nightwatch.ryan (赞：2)

## 思路
考虑动态规划求解。仔细看题，因为题目中所提到的交替，所以 $dp_i$ 的状态只和 $dp_{i-1}$ 和 $dp_{i-2}$ 有关，推出动态转移方程。
- $dp_i=dp_{i-1}+dp_{i-2}+2$

## 代码
```cpp
#include<cstdio>
const int MOD=1000000007;
const int MAXN=1e6+5;
int n,dp[MAXN];
void work(){
	for(int i=2;i<=n;i++){
		dp[i]=(dp[i-1]+dp[i-2]+2)%MOD;
	}
}
int main(){
	scanf("%d",&n);
	dp[1]=1;
	work();
	printf("%d",dp[n]);
}
```

---

## 作者：VitrelosTia (赞：0)

考虑动态规划。我们知道动态规划的重点有四个：状态，初值，转移方程，答案。

容易想到设 $f_i$ 为长度为 $i$ 时的最优解，那么答案就显然是 $f_n$。

观察题目，思考到 $f_i$ 的状态肯定只与 $f_{i - 1}$ 和 $f_{i - 2}$ 有关（因为交替），进一步思考到第 $i$ 个数对于全局有 $1$ 的贡献，对于 $i - 1$ 也有 $1$ 的贡献，对于其他点的贡献为 $f_{i - 2}$ （同样是因为交替）。于是我们就可以推出状态转移方程

$$f_i = f_{i - 1} + f_{i - 2} + 2$$

那么这道题就愉快地做完了。

```
#include<bits/stdc++.h>
using namespace std;

const int M = 1e6 + 5, mod = 1e9 + 7;
int n, f[M];

int main() { 
	cin >> n;
	f[1] = 1;
	for (int i = 2; i <= n; i++) f[i] = (f[i - 1] + f[i - 2] + 2) % mod;
	cout << f[n];
	return 0;
}
```

---

