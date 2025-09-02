# 题目信息

# To Become Max

## 题目描述

You are given an array of integers $ a $ of length $ n $ .

In one operation you:

- Choose an index $ i $ such that $ 1 \le i \le n - 1 $ and $ a_i \le a_{i + 1} $ .
- Increase $ a_i $ by $ 1 $ .

Find the maximum possible value of $ \max(a_1, a_2, \ldots a_n) $ that you can get after performing this operation at most $ k $ times.

## 说明/提示

In the first test case, one possible optimal sequence of operations is: $[\textcolor{red}{1}, 3, 3] \rightarrow [2, \textcolor{red}{3}, 3] \rightarrow [\textcolor{red}{2}, 4, 3] \rightarrow [\textcolor{red}{3}, 4, 3] \rightarrow [4, 4, 3]$.

In the second test case, one possible optimal sequence of operations is: $[1, \textcolor{red}{3}, 4, 5, 1] \rightarrow [1, \textcolor{red}{4}, 4, 5, 1] \rightarrow [1, 5, \textcolor{red}{4}, 5, 1] \rightarrow [1, 5, \textcolor{red}{5}, 5, 1] \rightarrow [1, \textcolor{red}{5}, 6, 5, 1] \rightarrow [1, \textcolor{red}{6}, 6, 5, 1] \rightarrow [1, 7, 6, 5, 1]$.

## 样例 #1

### 输入

```
6
3 4
1 3 3
5 6
1 3 4 5 1
4 13
1 1 3 179
5 3
4 3 2 2 2
5 6
6 5 4 1 5
2 17
3 5```

### 输出

```
4
7
179
5
7
6```

# AI分析结果

### 题目内容重写
# 成为最大值

## 题目描述

给定一个长度为 $n$ 的整数数组 $a$。

在一次操作中，你可以：

- 选择一个索引 $i$，满足 $1 \le i \le n - 1$ 且 $a_i \le a_{i + 1}$。
- 将 $a_i$ 增加 $1$。

在最多进行 $k$ 次操作后，求数组 $a$ 的最大值 $\max(a_1, a_2, \ldots, a_n)$ 的最大可能值。

## 说明/提示

在第一个测试用例中，一个可能的最优操作序列是：$[\textcolor{red}{1}, 3, 3] \rightarrow [2, \textcolor{red}{3}, 3] \rightarrow [\textcolor{red}{2}, 4, 3] \rightarrow [\textcolor{red}{3}, 4, 3] \rightarrow [4, 4, 3]$。

在第二个测试用例中，一个可能的最优操作序列是：$[1, \textcolor{red}{3}, 4, 5, 1] \rightarrow [1, \textcolor{red}{4}, 4, 5, 1] \rightarrow [1, 5, \textcolor{red}{4}, 5, 1] \rightarrow [1, 5, \textcolor{red}{5}, 5, 1] \rightarrow [1, \textcolor{red}{5}, 6, 5, 1] \rightarrow [1, \textcolor{red}{6}, 6, 5, 1] \rightarrow [1, 7, 6, 5, 1]$。

## 样例 #1

### 输入

```
6
3 4
1 3 3
5 6
1 3 4 5 1
4 13
1 1 3 179
5 3
4 3 2 2 2
5 6
6 5 4 1 5
2 17
3 5
```

### 输出

```
4
7
179
5
7
6
```

### 算法分类
二分

### 题解分析与结论
本题的核心思路是通过二分查找来确定在最多进行 $k$ 次操作后，数组 $a$ 的最大值。大多数题解采用了二分答案的思路，通过枚举每个元素，计算使其达到某个目标值所需的最小操作数，并判断是否在 $k$ 次操作内完成。

### 所选高分题解
#### 题解1：MaxBlazeResFire (5星)
**关键亮点**：
- 使用二分查找，时间复杂度为 $O(n^2 \log V)$，其中 $V$ 是最大可能值。
- 通过枚举每个元素，计算使其达到目标值所需的最小操作数，并判断是否在 $k$ 次操作内完成。

**核心代码**：
```cpp
inline bool chk( int x ){
	int tmp = k;
	for( int i = 1 ; i <= n ; i ++ ){
		tmp = k;
		for( int j = i ; j <= n ; j ++ ){
			if( a[j] < x - ( j - i ) ){
				if( tmp < ( x - j + i - a[j] ) ) break;
				tmp -= ( x - j + i - a[j] );
			}
			else return 1;
		}
	}
	return 0;
}
```

#### 题解2：james1BadCreeper (4星)
**关键亮点**：
- 采用贪心策略，枚举每个元素，利用其后面的元素使其尽可能大。
- 时间复杂度为 $O(n^2)$，适合数据范围较小的情况。

**核心代码**：
```cpp
for (int j = i + 1; j <= n && t > 0; ++j) {
    if (b[j] < b[j - 1]) {
        t -= b[j - 1] - 1 - b[j]; 
        b[j] = b[j - 1] - 1; 
    } else {
        i64 ad = min(1ll * (b[j] - b[j - 1] + 1) * (j - i), t); 
        t -= ad; b[i] += ad / (j - i); 
    }
    ans = max(ans, b[i]); 
}
```

#### 题解3：信息向阳花木 (4星)
**关键亮点**：
- 二分查找结合枚举，通过计算每个元素达到目标值所需的最小操作数。
- 时间复杂度为 $O(n^2 \log V)$，与题解1类似。

**核心代码**：
```cpp
bool check(long long mid) {
    for (int i = 1; i < n; i++) {
        long long cnt = 0, t = mid;
        for (int j = i; j < n; j++) {
            if (j == n - 1 && t - (long long)a[j] > 1ll * max(0, a[j + 1] - a[j] + 1)) {
                cnt = 1e18;
                break;
            }
            if (t <= 1ll * a[j]) break;
            cnt += (t - 1ll * a[j]);
            t--;
        }
        if (cnt <= 1ll * k) return 1;
    }
    return 0;
}
```

### 最优关键思路或技巧
- **二分查找**：通过二分查找确定最大可能值，结合枚举每个元素计算所需操作数。
- **贪心策略**：利用后面的元素使当前元素尽可能大，减少操作次数。

### 拓展思路
- 类似题目可以通过二分查找或贪心策略解决，特别是涉及最大化或最小化某个值的问题。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：52.36秒