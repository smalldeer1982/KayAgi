# 题目信息

# Coprime

## 题目描述

Given an array of $ n $ positive integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 1000 $ ). Find the maximum value of $ i + j $ such that $ a_i $ and $ a_j $ are coprime, $ ^{\dagger} $ or $ -1 $ if no such $ i $ , $ j $ exist.

For example consider the array $ [1, 3, 5, 2, 4, 7, 7] $ . The maximum value of $ i + j $ that can be obtained is $ 5 + 7 $ , since $ a_5 = 4 $ and $ a_7 = 7 $ are coprime.

 $ ^{\dagger} $ Two integers $ p $ and $ q $ are [coprime](https://en.wikipedia.org/wiki/Coprime_integers) if the only positive integer that is a divisor of both of them is $ 1 $ (that is, their [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) is $ 1 $ ).

## 说明/提示

For the first test case, we can choose $ i = j = 3 $ , with sum of indices equal to $ 6 $ , since $ 1 $ and $ 1 $ are coprime.

For the second test case, we can choose $ i = 7 $ and $ j = 5 $ , with sum of indices equal to $ 7 + 5 = 12 $ , since $ 7 $ and $ 4 $ are coprime.

## 样例 #1

### 输入

```
6
3
3 2 1
7
1 3 5 2 4 7 7
5
1 2 3 4 5
3
2 2 4
6
5 4 3 15 12 16
5
1 2 2 3 6```

### 输出

```
6
12
9
-1
10
7```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个包含 $n$ 个正整数的数组 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 1000$）。找到满足 $a_i$ 和 $a_j$ 互质的 $i + j$ 的最大值，如果不存在这样的 $i$ 和 $j$，则返回 $-1$。

例如，考虑数组 $[1, 3, 5, 2, 4, 7, 7]$。可以得到的最大 $i + j$ 是 $5 + 7$，因为 $a_5 = 4$ 和 $a_7 = 7$ 互质。

**互质定义**：两个整数 $p$ 和 $q$ 互质，当且仅当它们的最大公约数为 $1$。

#### 说明/提示
对于第一个测试用例，可以选择 $i = j = 3$，因为 $1$ 和 $1$ 互质，索引和为 $6$。

对于第二个测试用例，可以选择 $i = 7$ 和 $j = 5$，因为 $7$ 和 $4$ 互质，索引和为 $12$。

#### 样例
##### 输入
```
6
3
3 2 1
7
1 3 5 2 4 7 7
5
1 2 3 4 5
3
2 2 4
6
5 4 3 15 12 16
5
1 2 2 3 6
```

##### 输出
```
6
12
9
-1
10
7
```

### 算法分类
**枚举**

### 题解分析与结论
题目要求找到数组中两个互质元素的最大索引和。由于数组长度可能达到 $2 \times 10^5$，直接双重循环枚举所有元素对的时间复杂度为 $O(n^2)$，无法通过。然而，由于 $a_i$ 的范围仅为 $1$ 到 $1000$，可以通过枚举所有可能的 $a_i$ 和 $a_j$ 来优化时间复杂度。

### 精选题解
#### 题解1：Tooler_Yang (★★★★★)
**关键亮点**：
1. 利用桶记录每个数最后出现的位置，确保索引最大。
2. 通过双重循环枚举 $1$ 到 $1000$ 的所有数对，检查是否互质并更新最大索引和。
3. 使用 `__gcd` 函数快速计算最大公约数。

**代码核心思想**：
```cpp
int ans = -1;
for (int i = 1; i <= 1000; i++) {
    for (int j = 1; j <= 1000; j++) {
        if (__gcd(i, j) == 1 && mpl[i] != 0 && mpl[j] != 0) {
            ans = max(ans, mpl[i] + mpl[j]);
        }
    }
}
```

#### 题解2：what_can_I_do (★★★★)
**关键亮点**：
1. 使用桶记录每个数最后出现的位置，确保索引最大。
2. 通过双重循环枚举 $1$ 到 $maxd$ 的所有数对，检查是否互质并更新最大索引和。
3. 自定义 `gcd` 函数实现最大公约数计算。

**代码核心思想**：
```cpp
for (int i = 1; i <= maxd; i++) {
    for (int j = i; j <= maxd; j++) {
        if (a[i] != 0 && a[j] != 0 && gcd(i, j) == 1) {
            maxx = max(maxx, a[i] + a[j]);
        }
    }
}
```

#### 题解3：WaterSun (★★★★)
**关键亮点**：
1. 使用桶记录每个数最后出现的位置，确保索引最大。
2. 通过双重循环枚举 $1$ 到 $Max$ 的所有数对，检查是否互质并更新最大索引和。
3. 自定义 `gcd` 函数实现最大公约数计算。

**代码核心思想**：
```cpp
for (int i = 1; i <= Max; i++) {
    for (int j = 1; j <= Max; j++) {
        if (vis[i] && vis[j] && gcd(i, j) == 1) {
            ans = max(ans, vis[i] + vis[j]);
        }
    }
}
```

### 最优关键思路
1. **桶记录法**：通过桶记录每个数最后出现的位置，确保索引最大。
2. **枚举优化**：由于 $a_i$ 的范围仅为 $1$ 到 $1000$，可以通过枚举所有可能的数对来优化时间复杂度。
3. **快速计算最大公约数**：使用 `__gcd` 或自定义 `gcd` 函数快速判断两个数是否互质。

### 拓展思路
类似的问题可以通过枚举值域内的所有可能情况来优化时间复杂度，尤其是在值域较小的情况下。这种方法可以应用于其他需要判断数对关系的题目，如寻找满足特定条件的数对、计算数对的某种属性等。

### 推荐题目
1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

---
处理用时：39.86秒