# 题目信息

# Add One

## 题目描述

You are given an integer $ n $ . You have to apply $ m $ operations to it.

In a single operation, you must replace every digit $ d $ of the number with the decimal representation of integer $ d + 1 $ . For example, $ 1912 $ becomes $ 21023 $ after applying the operation once.

You have to find the length of $ n $ after applying $ m $ operations. Since the answer can be very large, print it modulo $ 10^9+7 $ .

## 说明/提示

For the first test, $ 1912 $ becomes $ 21023 $ after $ 1 $ operation which is of length $ 5 $ .

For the second test, $ 5 $ becomes $ 21 $ after $ 6 $ operations which is of length $ 2 $ .

For the third test, $ 999 $ becomes $ 101010 $ after $ 1 $ operation which is of length $ 6 $ .

For the fourth test, $ 88 $ becomes $ 1010 $ after $ 2 $ operations which is of length $ 4 $ .

## 样例 #1

### 输入

```
5
1912 1
5 6
999 1
88 2
12 100```

### 输出

```
5
2
6
4
2115```

# AI分析结果

### 题目翻译
# 加一

## 题目描述

给定一个整数 $n$，你需要对其应用 $m$ 次操作。

在每次操作中，你必须将数字中的每一位 $d$ 替换为 $d + 1$ 的十进制表示。例如，$1912$ 在应用一次操作后变为 $21023$。

你需要找到在应用 $m$ 次操作后 $n$ 的长度。由于答案可能非常大，请输出其对 $10^9+7$ 取模的结果。

## 说明/提示

对于第一个测试用例，$1912$ 在应用 $1$ 次操作后变为 $21023$，其长度为 $5$。

对于第二个测试用例，$5$ 在应用 $6$ 次操作后变为 $21$，其长度为 $2$。

对于第三个测试用例，$999$ 在应用 $1$ 次操作后变为 $101010$，其长度为 $6$。

对于第四个测试用例，$88$ 在应用 $2$ 次操作后变为 $1010$，其长度为 $4$。

## 样例 #1

### 输入

```
5
1912 1
5 6
999 1
88 2
12 100
```

### 输出

```
5
2
6
4
2115
```

### 算法分类
动态规划

### 题解分析与结论
本题的核心在于如何处理每一位数字在经过多次操作后的位数变化。由于直接暴力模拟的复杂度较高，无法通过测试，因此需要采用动态规划的方法进行预处理。

各题解的共同点是都采用了动态规划的思路，预处理出每个数字在经过不同次数操作后的位数变化。不同之处在于具体的实现细节和优化方式。

### 精选题解
#### 题解1：gaozitao1 (5星)
**关键亮点**：
- 使用二维数组 `d[i][j]` 表示数字 `i` 经过 `j` 次操作后的位数。
- 通过递推公式 `d[i][j] = d[0][i+j-10] + d[1][i+j-10]` 处理进位情况。
- 预处理时先枚举操作次数 `j`，再枚举数字 `i`，确保转移时的数据已初始化。

**代码核心实现**：
```cpp
for(j=0; j<200001; ++j) {
    for(i=0; i<10; ++i) {
        if(i+j>9)
            d[i][j]=(d[0][i+j-10]+d[1][i+j-10])%1000000007;
        else
            d[i][j]=1;
    }
}
```

#### 题解2：Wf_yjqd (4星)
**关键亮点**：
- 利用 `10` 这个特殊数字，预处理出 `10` 经过不同次数操作后的位数变化。
- 通过递归函数 `dfs(x, c)` 计算任意数字 `x` 经过 `c` 次操作后的位数。

**代码核心实现**：
```cpp
ll dfs(ll x, ll c) {
    if(x+c<10) return 1;
    if(x==10) return f[c];
    return dfs(10, c-(10-x));
}
```

#### 题解3：破壁少年 (4星)
**关键亮点**：
- 使用二维数组 `f[i][j]` 表示数字 `i` 经过 `j` 次操作后的位数。
- 预处理时枚举操作次数 `j` 和数字 `i`，通过判断 `i+j` 是否大于 `9` 来决定是否进位。

**代码核心实现**：
```cpp
for(int j=0; j<=400000; j++) {
    for(int i=0; i<=9; i++) {
        if(i+j<=9) f[i][j]=1;
        else f[i][j]=(f[1][i+j-10]%mod+f[0][i+j-10]%mod)%mod;
    }
}
```

### 最优关键思路
通过动态规划预处理每个数字在经过不同次数操作后的位数变化，避免重复计算，显著降低时间复杂度。具体实现时，先枚举操作次数，再枚举数字，确保转移时的数据已初始化。

### 拓展思路
类似的问题可以扩展到其他进制或更复杂的操作规则，动态规划的思路仍然适用。此外，预处理的思想可以应用于其他需要多次重复计算的场景。

### 推荐题目
1. [P1045 数字计数](https://www.luogu.com.cn/problem/P1045)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：34.68秒