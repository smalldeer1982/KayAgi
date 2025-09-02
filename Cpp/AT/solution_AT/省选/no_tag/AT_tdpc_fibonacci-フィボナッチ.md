# フィボナッチ

## 题目描述

### 题目大意
已知一个数列 $a$ ，它的前 $K$ 项都等于 $1$，从第 $K+1$ 项开始，每一项等于它前 $K$ 项的和，求 $a_N$ 项是多少。

# 题解

## 作者：Memory_of_winter (赞：6)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10398167.html)

**题目大意：**给你$n,k(n\leqslant10^9,k\leqslant10^3)$，求$f_n$。$f$数组满足$f_1=f_2=\cdots=f_k=1$，$f_n=\sum\limits_{i=n-k}^{n-1}f_i$

**题解：**线性齐次递推：
$$\left[\begin{matrix}f_1&f_2&\cdots&f_k\end{matrix}\right]\left[\begin{matrix}0&0&0&\cdots&0&1\\1&0&0&\cdots&0&1\\0&1&0&\cdots&0&1\\0&0&1&\cdots&0&1\\\vdots&\vdots&\ddots&\ddots&\vdots&\vdots\\0&0&0&\cdots&1&1\end{matrix}\right]=\left[\begin{matrix}f_2&f_3&\cdots&f_{k+1}\end{matrix}\right]$$
特征多项式$G_k(x)$为：
$$\begin{aligned}G_k(x)&=|\lambda I-A|\\&=\left|\left[\begin{matrix}\lambda&0&0&\cdots&0&-1\\-1&\lambda&0&\cdots&0&-1\\0&-1&\lambda&\cdots&0&-1\\0&0&-1&\cdots&0&-1\\\vdots&\vdots&\ddots&\ddots&\vdots&\vdots\\0&0&0&\cdots&-1&\lambda-1\end{matrix}\right]\right|\end{aligned}$$
可以对第一行展开
$$\begin{aligned}G_k(x)&=(-1)^{1+1}\lambda G_{k-1}(x)+(-1)(-1)^{k-1}(-1)^{k+1}\\&=\lambda G_{k-1}(x)-1\\&=\lambda^k-\lambda^{k-1}-\lambda^{k-2}-\cdots-1\end{aligned}$$
发现模数是$10^9+7$，但是$k$只有$10^3$，所以直接$O(k^2)$卷积和取模，总复杂度$O(k^2\log_2n)$



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#define maxn 2010
const int mod = 1e9 + 7;

#define mul(x, y) static_cast<long long> (x) * (y) % mod
inline void reduce(int &x) { x += x >> 31 & mod; }

int n, K;
int f[maxn], g[maxn];

void PW(int n) {
	if (n == 0) { f[0] = 1; return ; }
	PW(n >> 1);
	std::memset(g, 0, K << 3);
	for (int i = 0; i < K; ++i)
		for (int j = 0; j < K; ++j)
			reduce(g[i + j + (n & 1)] += mul(f[i], f[j]) - mod);
	for (int i = K + K - 1 + (n & 1); i >= K; --i) {
		for (int j = 1; j <= K; ++j) reduce(g[i - j] += g[i] - mod);
	}
	std::memcpy(f, g, K << 2);
}

int main() {
	scanf("%d%d", &K, &n);
	PW(n - 1);
	int ans = 0;
	for (int i = 0; i < K; ++i) reduce(ans += f[i] - mod);
	printf("%d\n", ans);
	return 0;
}
```



---

