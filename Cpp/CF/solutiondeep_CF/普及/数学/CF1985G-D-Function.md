# 题目信息

# D-Function

## 题目描述

Let $ D(n) $ represent the sum of digits of $ n $ . For how many integers $ n $ where $ 10^{l} \leq n < 10^{r} $ satisfy $ D(k \cdot n) = k \cdot D(n) $ ? Output the answer modulo $ 10^9+7 $ .

## 说明/提示

For the first test case, the only values of $ n $ that satisfy the condition are $ 1 $ and $ 2 $ .

For the second test case, the only values of $ n $ that satisfy the condition are $ 1 $ , $ 10 $ , and $ 11 $ .

For the third test case, all values of $ n $ between $ 10 $ inclusive and $ 100 $ exclusive satisfy the condition.

## 样例 #1

### 输入

```
6
0 1 4
0 2 7
1 2 1
1 2 3
582 74663 3
0 3 1```

### 输出

```
2
3
90
12
974995667
999```

# AI分析结果

### 题目内容重写

#### 题目描述

设 $ D(n) $ 表示 $ n $ 的各位数字之和。给定整数 $ l $, $ r $, $ k $，求满足 $ 10^{l} \leq n < 10^{r} $ 且 $ D(k \cdot n) = k \cdot D(n) $ 的整数 $ n $ 的个数，输出答案对 $ 10^9+7 $ 取模的结果。

#### 说明/提示

对于第一个测试用例，满足条件的 $ n $ 只有 $ 1 $ 和 $ 2 $。

对于第二个测试用例，满足条件的 $ n $ 有 $ 1 $, $ 10 $, 和 $ 11 $。

对于第三个测试用例，所有 $ 10 \leq n < 100 $ 的数都满足条件。

#### 样例 #1

##### 输入

```
6
0 1 4
0 2 7
1 2 1
1 2 3
582 74663 3
0 3 1
```

##### 输出

```
2
3
90
12
974995667
999
```

### 题解分析与结论

#### 综合分析

所有题解的核心思路都基于一个关键观察：**$ D(k \cdot n) = k \cdot D(n) $ 的条件等价于 $ n \cdot k $ 不发生进位**。这意味着 $ n $ 的每一位数字 $ d $ 必须满足 $ k \cdot d < 10 $。基于这一观察，题解们通过计算每一位可能的取值数量，并利用快速幂和前缀和的思想来计算满足条件的 $ n $ 的个数。

#### 最优关键思路

1. **不进位条件**：$ n \cdot k $ 不发生进位是满足 $ D(k \cdot n) = k \cdot D(n) $ 的充要条件。
2. **快速幂计算**：利用快速幂计算 $ (\lfloor \frac{9}{k} \rfloor + 1)^x $，其中 $ x $ 是数的位数。
3. **前缀和思想**：通过计算 $ [0, 10^r) $ 和 $ [0, 10^l) $ 的满足条件的数的个数，然后相减得到 $ [10^l, 10^r) $ 的答案。

#### 推荐题解

##### 题解1：BrotherCall (5星)

**关键亮点**：
- 详细证明了不进位条件的必要性，并给出了清晰的数学推导。
- 使用快速幂和等比数列求和公式，代码简洁且高效。

**核心代码**：
```cpp
int ksm(int x,int y) {
	int res = 1;
	for(;y;y >>= 1 , x = x * x % mod) 
		if(y & 1) 
			res = res * x % mod;
	return res;
}

signed main() {
	cin >> t;
	while(t --) {
		cin >> n >> m >> k;
		int wd = (9 / k);
		int now = (((ksm(wd + 1 , m - n) - 1) % mod) + mod) % mod; 
		now = ksm(wd + 1 , n) % mod * now % mod;
		cout << now << "\n"; 
	}
	return 0;
}
```

##### 题解2：fishing_cat (4星)

**关键亮点**：
- 通过手玩和数学直觉快速发现不进位条件，并给出了特判处理。
- 代码简洁，快速幂实现清晰。

**核心代码**：
```cpp
ll pw(ll b, ll power) {
	ll res = 1;
	while (power > 0) {
		if (power & 1)
			res =(res*b) %mod;
		power >>= 1;
		b= (b*b)%mod;
	}
	return res;
}

int main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld%lld%lld", &l, &r, &k);
		string h = to_string(k);
		if (h.size() == 1) {
			maxn = 10 / k;
			if(k != 1 && k != 2 && k != 5)
				maxn ++;
			ans = pw(maxn, r);
			ans -= pw(maxn, l);
			ans = (ans + mod)%mod;
			printf("%lld\n",ans);
		} else {
			puts("0");
		}
	}
 	return 0;
}
```

##### 题解3：ThySecret (4星)

**关键亮点**：
- 通过暴力代码验证了不进位条件的正确性，并给出了详细的证明。
- 使用快速幂和前缀和思想，代码实现简洁。

**核心代码**：
```cpp
LL ksm(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = a * res % mod;
        a = a * a % mod, b >>= 1;
    }
    return res % mod;
}

void solve() {
    cin >> l >> r >> k;
    times = (10 + k - 1) / k;
    cout << (ksm(times, r) - ksm(times, l) + mod) % mod << '\n';
}
```

### 拓展与推荐题目

1. **洛谷 P1045 麦森数**：考察快速幂的应用。
2. **洛谷 P1226 快速幂**：练习快速幂的实现。
3. **洛谷 P1010 幂次方**：涉及幂运算和数位处理。

### 个人心得总结

- **调试经历**：在处理取模运算时，减法操作可能导致负数，因此需要在结果上加模再取模。
- **顿悟感想**：不进位条件的发现是解决本题的关键，通过数学推导和暴力验证可以快速确认其正确性。

---
处理用时：45.22秒