# 题目信息

# Maximum Sum

## 题目描述

You have an array $ a $ of $ n $ integers.

You perform exactly $ k $ operations on it. In one operation, you select any contiguous subarray of the array $ a $ (possibly empty) and insert the sum of this subarray anywhere in the array.

Your task is to find the maximum possible sum of the array after $ k $ such operations.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

Reminder: the remainder of a number $ x $ modulo $ p $ is the smallest non-negative $ y $ such that there exists an integer $ q $ and $ x = p \cdot q + y $ .

## 说明/提示

In the first test case, it is advantageous to take an empty subarray of the array twice and insert the sum of the empty subarray (zero) anywhere, then the sum of the resulting array will be $ (-4) + (-7) + 0 + 0 = -11 $ , modulo $ 10^9 + 7 $ this is $ 999\,999\,996 $ .

In the second test case, it is advantageous to take the sum of the entire array three times and place it anywhere in the array, then one of the possible sequences of actions: \[ $ 2, 2, 8 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24, 48 $ \], the sum of the final array is $ 2 + 2 + 8 + 12 + 24 + 48 = 96 $ .

In the fourth test case, it is advantageous to take a subarray of the array consisting of the first three numbers (i.e. consisting of the numbers $ 4, -2 $ and $ 8 $ ) and insert its sum at the beginning of the array, thereby obtaining the array \[ $ 10, 4, -2, 8, -12, 9 $ \], the sum of this array is $ 17 $ .

In the seventh test case, it will always be advantageous for us to take an empty subarray of the array. In this case, the sum of the resulting array will not differ from the sum of the original. The answer will be the sum of the original array, taken modulo — $ 42 $ , because $ (-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000) $ .

## 样例 #1

### 输入

```
12
2 2
-4 -7
3 3
2 2 8
1 7
7
5 1
4 -2 8 -12 9
7 4
8 14 -9 6 0 -1 3
7 100
5 3 -8 12 -5 -9 3
6 1000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 -1000000000
2 1
1000000000 8
5 4
0 0 0 0 0
6 10
48973 757292 58277 -38574 27475 999984
7 1
-1000 1000 -1000 1000 -1000 1000 -1000
10 10050
408293874 -3498597 7374783 295774930 -48574034 26623784 498754833 -294875830 283045804 85938045```

### 输出

```
999999996
96
896
17
351
716455332
42
2
0
897909241
0
416571966```

# AI分析结果

### 题目重写
#### 最大和

**题目描述**

给定一个包含 $n$ 个整数的数组 $a$。

你需要执行恰好 $k$ 次操作。每次操作中，你可以选择数组 $a$ 中的任意一个连续子数组（可以为空），并将这个子数组的和插入到数组 $a$ 中的任意位置。

你的任务是在执行完所有操作后，找到数组可能的最大和。

由于这个数可能非常大，输出答案时需要对 $10^9 + 7$ 取模。

**说明/提示**

在第一个测试用例中，最好选择数组的空子数组两次，并将空子数组的和（零）插入到数组中的任意位置，这样得到的数组和为 $(-4) + (-7) + 0 + 0 = -11$，对 $10^9 + 7$ 取模后为 $999\,999\,996$。

在第二个测试用例中，最好选择整个数组的和三次，并将其插入到数组中的任意位置，这样得到的数组和为 $2 + 2 + 8 + 12 + 24 + 48 = 96$。

在第四个测试用例中，最好选择数组的前三个数（即 $4, -2, 8$）的子数组，并将其和插入到数组的开头，得到的数组为 $[10, 4, -2, 8, -12, 9]$，其和为 $17$。

在第七个测试用例中，最好选择数组的空子数组。在这种情况下，最终数组的和与原始数组的和相同。答案为原始数组的和对 $10^9 + 7$ 取模，即 $42$，因为 $(-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000)$。

### 综合分析与结论

本题的核心在于通过贪心策略最大化数组的和。每次操作选择当前数组的最大子段和，并将其插入到最大子段中，使得下一次操作的最大子段和翻倍。通过等比数列求和公式，可以快速计算出最终的最大和。

### 评分较高的题解

#### 题解1：作者：KazamaRuri (赞：6)

**星级：5星**

**关键亮点：**
- 清晰地解释了贪心策略，每次操作选择最大子段和并插入到最大子段中，使得下一次操作的最大子段和翻倍。
- 使用快速幂优化计算 $2^k$，时间复杂度为 $O(n + \log k)$。
- 代码简洁且高效，易于理解。

**核心代码：**
```cpp
ll qp(ll x,int y){
	ll mul=1;
	while(y){
		if(y&1) mul=mul*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return mul;
}
```

#### 题解2：作者：oyoham (赞：5)

**星级：4星**

**关键亮点：**
- 通过观察题目，发现每次操作的最大子段和翻倍的规律，直接使用等比数列求和公式计算最终结果。
- 使用快速幂优化计算 $2^k$，代码简洁明了。

**核心代码：**
```cpp
int fp(int a,int b,int p=mod){
	int base=a;
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*base%p;
		}
		base=base*base%p;
		b>>=1;
	}
	return ans;
}
```

#### 题解3：作者：cute_overmind (赞：4)

**星级：4星**

**关键亮点：**
- 通过贪心策略，每次操作选择最大子段和并插入到最大子段中，使得下一次操作的最大子段和翻倍。
- 使用快速幂优化计算 $2^k$，代码简洁且高效。

**核心代码：**
```cpp
int qp(int a, int b, int p){
	int sum = 1;
	while (b){
		if(b & 1)
			sum =  sum * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return sum;
}
```

### 最优关键思路或技巧

1. **贪心策略**：每次操作选择当前数组的最大子段和，并将其插入到最大子段中，使得下一次操作的最大子段和翻倍。
2. **快速幂优化**：使用快速幂算法高效计算 $2^k$，避免直接计算导致的时间复杂度问题。
3. **等比数列求和**：通过等比数列求和公式，快速计算出最终的最大和。

### 可拓展之处

- **类似题目**：可以拓展到其他需要贪心策略和快速幂优化的题目，如最大子数组和、动态规划中的状态转移等。
- **算法套路**：贪心策略结合快速幂优化是一种常见的算法套路，适用于需要多次操作且每次操作对结果有倍增影响的题目。

### 推荐题目

1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

### 个人心得摘录

- **调试经历**：在实现快速幂时，需要注意取模运算的顺序，避免溢出。
- **踩坑教训**：在处理负数取模时，需要先加上模数再取模，确保结果为非负数。
- **顿悟感想**：通过贪心策略和快速幂优化，可以高效解决看似复杂的操作问题。

---
处理用时：35.79秒