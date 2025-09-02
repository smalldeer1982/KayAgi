# Expected Power

## 题目描述

You are given an array of $ n $ integers $ a_1,a_2,\ldots,a_n $ . You are also given an array $ p_1, p_2, \ldots, p_n $ .

Let $ S $ denote the random multiset (i. e., it may contain equal elements) constructed as follows:

- Initially, $ S $ is empty.
- For each $ i $ from $ 1 $ to $ n $ , insert $ a_i $ into $ S $ with probability $ \frac{p_i}{10^4} $ . Note that each element is inserted independently.

Denote $ f(S) $ as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of all elements of $ S $ . Please calculate the expected value of $ (f(S))^2 $ . Output the answer modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test case, $ a = [1, 2] $ and each element is inserted into $ S $ with probability $ \frac{1}{2} $ , since $ p_1 = p_2 = 5000 $ and $ \frac{p_i}{10^4} = \frac{1}{2} $ . Thus, there are $ 4 $ outcomes for $ S $ , each happening with the same probability of $ \frac{1}{4} $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ .
- $ S = \{2\} $ . In this case, $ f(S) = 2 $ , $ (f(S))^2 = 4 $ .
- $ S = \{1,2\} $ . In this case, $ f(S) = 1 \oplus 2 = 3 $ , $ (f(S))^2 = 9 $ .

Hence, the answer is $ 0 \cdot \frac{1}{4} + 1 \cdot \frac{1}{4} + 4\cdot \frac{1}{4} + 9 \cdot \frac{1}{4} = \frac{14}{4} = \frac{7}{2} \equiv 500\,000\,007 \pmod{10^9 + 7} $ .

In the second test case, $ a = [1, 1] $ , $ a_1 $ is inserted into $ S $ with probability $ 0.1 $ , while $ a_2 $ is inserted into $ S $ with probability $ 0.2 $ . There are $ 3 $ outcomes for $ S $ :

- $ S = \varnothing $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ (1-0.1) \cdot (1-0.2) = 0.72 $ .
- $ S = \{1\} $ . In this case, $ f(S) = 1 $ , $ (f(S))^2 = 1 $ . This happens with probability $ (1-0.1) \cdot 0.2 + 0.1 \cdot (1-0.2) = 0.26 $ .
- $ S = \{1, 1\} $ . In this case, $ f(S) = 0 $ , $ (f(S))^2 = 0 $ . This happens with probability $ 0.1 \cdot 0.2 = 0.02 $ .

Hence, the answer is $ 0 \cdot 0.72 + 1 \cdot 0.26 + 0 \cdot 0.02 = 0.26 = \frac{26}{100} \equiv 820\,000\,006 \pmod{10^9 + 7} $ .

## 样例 #1

### 输入

```
4
2
1 2
5000 5000
2
1 1
1000 2000
6
343 624 675 451 902 820
6536 5326 7648 2165 9430 5428
1
1
10000```

### 输出

```
500000007
820000006
280120536
1```

# 题解

## 作者：Zeoykkk (赞：9)

## CF926 E. Expected Power

>给定 $n$ 个元素 $a[i]$，有一个多重集 $S$，起初为空，然后按照 $1 \sim n$ 的顺序试图将 $a[i]$ 插入到 $S$ 中，$a[i]$ 成功插入进 $S$ 的概率为 $\frac{p[i]}{10^4}$，定义 $f(S)$ 为 $S$ 中所有元素的异或和，求 $f(S)^2$ 的期望值。
>
>$n \leq 2\times 10^5, a[i] \leq 1023$

### Sol 1

由于 $a[i]$ 值域很小，考虑这样的一个 DP，定义 $dp[i][j]$ 代表试图将 $a[1, i]$ 中的元素插入 $S$ 中，$f(S) = j$ 的概率。令 $p[i] = \frac{p[i]}{10^4}, q[i] = 1 - p[i]$。

转移也是显然的，$dp[i][j] = p[i] \times dp[i - 1][j \oplus a[i]] + q[i] \times dp[i - 1][j]$。

显然 $E[f(S)^2] = \sum_{x = 0}^{1023} dp[n][x] x^2$。

时间复杂度：$O(Vn)$。

### Sol 2

根据异或的性质，考虑每一位的贡献，即 $E[f(S)] = \sum_{i = 0}^{9}P(i)\times 2^i$，其中 $P(i)$ 代表试图将 $n$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $i$ 位为 $1$ 的概率。

显然 DP 可以求 $P(i)$，定义 $dp[i][j][0/1]$ 代表试图将前 $i$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $j$ 位为 $0 / 1$ 的概率。

转移也是显然的，令 $x$ 代表 $a[i]$ 在二进制第 $j$ 位上的值，则有 $dp[i][j][k] = p[i] \times dp[i - 1][j][k \oplus x] + q[i] \times dp[i - 1][j][k]$。

那么现在要求 $f(S)^2$，令 $f(S) = \sum_{i = 0}^{9} b[i] 2^i$，则有 $f(S)^2 = \sum_i \sum_j b[i]b[j]2^{i + j}$，所以 $E[f(S)^2] = \sum_{i = 0}^{9} \sum_{j = 0}^9 P(i, j)\times 2^{i + j}$，其中 $P(i, j)$ 代表试图将 $n$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $i$ 位和第 $j$ 位上都为 $1$ 的概率。

所以不妨定义 $dp[i][j][k][0/1][0/1]$ 试图将前 $i$ 个元素插入 $S$ 中，$f(S)$ 在二进制下第 $j$ 位为 $0 / 1$ 并且第 $k$ 位为 $0 / 1$ 的概率。

转移也是类似的，不再赘述，可以将第一维通过滚动数组优化掉。

时间复杂度：$O(n \log^2n)$。

---

## 作者：__3E24AC7002AD9292__ (赞：6)

VP 赛切了五题，但是这题敢放 E？

异或期望值，似乎根本不能搞，但是 $a_i<2^{10}$，那么异或的结果也 $<2^{10}$，考虑状压 dp。

记录 $f_{i,j}$ 表示当前已经遍历完前 $i$ 个数的选择情况，且选择后的异或和为 $j$ 的概率，显然有以下转移：

- $f_{i,j}=(f_{i,j}+\frac{10^4-p_i}{10^4}f_{i-1,j})\bmod 10^9+7$。
- $f_{i,j}=(f_{i,j}+\frac{p_i}{10^4}f_{i-1,j\oplus a_i})\bmod 10^9+7$。

可以使用滚动数组优化空间，时间复杂度 $\Theta(Vn)$。

```cpp
f[0][0]=1;
for (int i=1;i<=n;i++){
	for (int j=0;j<=1023;j++){
		f[1][j]+=f[0][j]*(10000-p[i])%M*INV%M;
		f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
		f[1][j]+=f[0][j^a[i]]*p[i]%M*INV%M;
		f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
	}
	for (int j=0;j<=1023;j++)
		f[0][j]=f[1][j],f[1][j]=0;
}
for (int i=0;i<=1023;i++){
	ans+=f[0][i]*i%M*i%M;
	ans%=M;
}
```

---

## 作者：qwq___qaq (赞：0)

> What's the point of allowing $O(n \cdot 1024)$ solutions in E?

注意到可以算出每个 f 值的概率最后再求期望。

因此可以定义 $f_{i,j}$ 表示前 $i$ 个数中，选出来的数异或和为 $j$ 的概率。

转移是平凡的，此处不再赘述。

第一维打滚就行了。

---

