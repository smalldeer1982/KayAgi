# 题目信息

# Binomial Coefficients, Kind Of

## 题目描述

Recently, akshiM met a task that needed binomial coefficients to solve. He wrote a code he usually does that looked like this:

```
<pre class="verbatim">    for (int n = 0; n < N; n++) { // loop over n from 0 to N-1 (inclusive)<br></br>        C[n][0] = 1;<br></br>        C[n][n] = 1;<br></br>        for (int k = 1; k < n; k++) // loop over k from 1 to n-1 (inclusive)<br></br>            C[n][k] = C[n][k - 1] + C[n - 1][k - 1];<br></br>    }<br></br>
```

Unfortunately, he made an error, since the right formula is the following:

```
<pre class="verbatim">            C[n][k] = C[n - 1][k] + C[n - 1][k - 1]<br></br>
```

But his team member keblidA is interested in values that were produced using the wrong formula. Please help him to calculate these coefficients for $ t $ various pairs $ (n_i, k_i) $ . Note that they should be calculated according to the first (wrong) formula.

Since values $ C[n_i][k_i] $ may be too large, print them modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999```

### 输出

```
2
4
8
2
326186014
984426998
303861760```

# AI分析结果

### 题目内容重写
# 二项式系数，某种形式

## 题目描述

最近，akshiM遇到了一个需要用二项式系数解决的问题。他写了一段他常用的代码，如下所示：

```cpp
for (int n = 0; n < N; n++) { // 循环n从0到N-1（包括）
    C[n][0] = 1;
    C[n][n] = 1;
    for (int k = 1; k < n; k++) // 循环k从1到n-1（包括）
        C[n][k] = C[n][k - 1] + C[n - 1][k - 1];
}
```

不幸的是，他犯了一个错误，因为正确的公式应该是：

```cpp
C[n][k] = C[n - 1][k] + C[n - 1][k - 1]
```

但他的团队成员keblidA对使用错误公式生成的值感兴趣。请帮助他计算这些系数，对于$t$组不同的$(n_i, k_i)$。注意，这些系数应该按照第一个（错误的）公式计算。

由于$C[n_i][k_i]$的值可能太大，请将它们对$10^9 + 7$取模后输出。

## 样例 #1

### 输入

```
7
2 5 5 100000 100000 100000 100000
1 2 3 1 33333 66666 99999
```

### 输出

```
2
4
8
2
326186014
984426998
303861760
```

### 综合分析与结论

本题的核心在于理解错误的递推公式，并通过观察或数学归纳法推导出简化后的公式。大多数题解通过打表或数学归纳法得出结论：$C_{n,k} = 2^k$（当$k < n$时）。这个结论大大简化了问题的复杂度，使得问题可以通过预处理$2^k$的值来快速求解。

### 所选高分题解

#### 题解1：Chenyanxi0829 (4星)
**关键亮点**：
- 通过观察递推公式，直接推导出$C_k = 2^k$，简化了问题。
- 代码简洁，预处理$2^k$的值，时间复杂度为$O(N + t)$。

**代码核心思想**：
```cpp
a[0] = 1;
for (int i = 1; i < kMaxN; i++) {
    a[i] = a[i - 1] * 2 % mod;
}
```
**完整代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1e5, mod = 1e9 + 7;
int a[kMaxN], t;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  a[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    a[i] = a[i - 1] * 2 % mod;
  }
  cin >> t;
  for (int i = 1, x; i <= t; i++, cin >> x) {}
  for (int i = 1, x; i <= t; i++) {
    cin >> x, cout << a[x] << '\n';
  }
  return 0;
}
```

#### 题解2：sherry_lover (4星)
**关键亮点**：
- 通过打表找规律，并结合数学归纳法证明了$C_{n,k} = 2^k$。
- 代码清晰，预处理$2^k$的值，时间复杂度为$O(N + t)$。

**代码核心思想**：
```cpp
Pow[0] = 1;
for(int i = 1;i < 100000;i++) Pow[i] = (Pow[i-1] << 1)%mod;
```
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
int T,k;
long long Pow[100005];
void init() {
	Pow[0] = 1;
	for(int i = 1;i < 100000;i++) Pow[i] = (Pow[i-1] << 1)%mod;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	init();
	for(int i = 1;i <= T;i++) cin >> k;
	for(int i = 1;i <= T;i++) {
		cin >> k;
		cout << Pow[k] << "\n";
	}
	return 0;
}
```

#### 题解3：DragonForge (4星)
**关键亮点**：
- 通过观察样例和推导，得出$C_{n,k} = 2^k$的结论。
- 代码简洁，预处理$2^k$的值，时间复杂度为$O(N + t)$。

**代码核心思想**：
```cpp
f[0] = 1;
for (int i = 1; i <= 100000; i++) {
    f[i] = f[i - 1] * 2 % mod;
}
```
**完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7;
long long n[100005], k[100005], t, f[100005];
int main() {
	cin >> t;
	f[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		f[i] = f[i - 1] * 2 % mod;
	}
	for (int i = 1; i <= t; i++) {
		scanf("%lld", &n[i]);
	}
	for (int i = 1; i <= t; i++) {
		scanf("%lld", &k[i]);
		printf("%lld\n", f[k[i]]);
	}
	return 0;
}
```

### 最优关键思路或技巧
- **观察与推导**：通过观察递推公式或打表，发现规律并简化问题。
- **预处理**：对于需要多次计算的$2^k$，预处理其值可以大大减少计算时间。
- **数学归纳法**：通过数学归纳法证明推导出的公式的正确性。

### 可拓展之处
- 类似的问题可以通过观察递推公式或打表来寻找规律，从而简化问题。
- 预处理技巧在需要多次计算相同值的场景中非常有用。

### 推荐题目
1. [P1357 二项式系数](https://www.luogu.com.cn/problem/P1357)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1045 快速幂](https://www.luogu.com.cn/problem/P1045)

---
处理用时：50.47秒