# 题目信息

# Equalize the Array

## 题目描述

Polycarp was gifted an array $ a $ of length $ n $ . Polycarp considers an array beautiful if there exists a number $ C $ , such that each number in the array occurs either zero or $ C $ times. Polycarp wants to remove some elements from the array $ a $ to make it beautiful.

For example, if $ n=6 $ and $ a = [1, 3, 2, 1, 4, 2] $ , then the following options are possible to make the array $ a $ array beautiful:

- Polycarp removes elements at positions $ 2 $ and $ 5 $ , array $ a $ becomes equal to $ [1, 2, 1, 2] $ ;
- Polycarp removes elements at positions $ 1 $ and $ 6 $ , array $ a $ becomes equal to $ [3, 2, 1, 4] $ ;
- Polycarp removes elements at positions $ 1, 2 $ and $ 6 $ , array $ a $ becomes equal to $ [2, 1, 4] $ ;

Help Polycarp determine the minimum number of elements to remove from the array $ a $ to make it beautiful.

## 样例 #1

### 输入

```
3
6
1 3 2 1 4 2
4
100 100 4 100
8
1 2 3 3 3 2 6 6```

### 输出

```
2
1
2```

# AI分析结果

### 题目内容重写

#### 题目描述

Polycarp 被赠予一个长度为 $n$ 的数组 $a$。Polycarp 认为一个数组是美丽的，如果存在一个数 $C$，使得数组中的每个数出现的次数要么是零次，要么是 $C$ 次。Polycarp 希望通过删除数组 $a$ 中的一些元素来使其变得美丽。

例如，如果 $n=6$ 且 $a = [1, 3, 2, 1, 4, 2]$，那么可以通过以下方式使数组 $a$ 变得美丽：

- 删除位置 $2$ 和 $5$ 的元素，数组 $a$ 变为 $[1, 2, 1, 2]$；
- 删除位置 $1$ 和 $6$ 的元素，数组 $a$ 变为 $[3, 2, 1, 4]$；
- 删除位置 $1, 2$ 和 $6$ 的元素，数组 $a$ 变为 $[2, 1, 4]$。

帮助 Polycarp 确定为了使数组 $a$ 变得美丽，最少需要删除多少个元素。

#### 样例 #1

##### 输入

```
3
6
1 3 2 1 4 2
4
100 100 4 100
8
1 2 3 3 3 2 6 6
```

##### 输出

```
2
1
2
```

### 算法分类
枚举、前缀和

### 题解分析与结论

本题的核心思路是通过枚举可能的 $C$ 值，计算每种情况下需要删除的元素数量，最终选择最小的删除次数。大多数题解都采用了以下步骤：

1. **统计每个元素的出现次数**：通过哈希表或数组统计每个元素的出现次数。
2. **对出现次数进行排序**：将出现次数排序，方便后续计算。
3. **枚举 $C$ 值**：枚举所有可能的 $C$ 值，计算每种情况下需要删除的元素数量。
4. **利用前缀和优化计算**：通过前缀和快速计算需要删除的元素数量。

### 高星题解推荐

#### 题解1：Frather_ (5星)
**关键亮点**：
- 详细解释了如何通过枚举 $C$ 值来计算删除次数。
- 使用了前缀和优化，避免了重复计算。
- 代码结构清晰，注释详细。

**核心代码**：
```cpp
for (int i = 1; i <= n; i++) {
    int t = lower_bound(bkt + 1, bkt + n_ + 1, i) - bkt;
    if (t > n_) // 界限以上
        ans[i] = sum[n_];
    if (t < n_) // 界限以下
        ans_[i] = sum[t - 1] + sum[n_] - sum[t - 1] - (n_ - t + 1) * i;
}
```

#### 题解2：DarkShadow (4星)
**关键亮点**：
- 思路清晰，通过枚举 $C$ 值并利用前缀和快速计算删除次数。
- 代码简洁，易于理解。

**核心代码**：
```cpp
for (int i = 0; i <= m; i++)
    ans = min(ans, pre[i] + pre[m] - pre[i] - (m - i) * num[i + 1]);
```

#### 题解3：清烛 (4星)
**关键亮点**：
- 通过枚举 $C$ 值并利用前缀和优化计算，思路清晰。
- 代码简洁，注释详细。

**核心代码**：
```cpp
FOR(i, 1, n)
    ans = min(ans, sum[i - 1] + sum[n] - sum[i] - (n - i) * cnt[i]);
```

### 最优关键思路与技巧
1. **枚举 $C$ 值**：通过枚举所有可能的 $C$ 值，计算每种情况下需要删除的元素数量。
2. **前缀和优化**：利用前缀和快速计算需要删除的元素数量，避免重复计算。
3. **排序**：对元素的出现次数进行排序，方便后续计算。

### 拓展思路
类似的问题可以通过枚举和前缀和优化来解决，例如统计数组中某些特定条件的元素数量或计算某些统计量。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1045 删数](https://www.luogu.com.cn/problem/P1045)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得总结
在解决类似问题时，枚举和前缀和是常用的优化手段，能够有效减少计算复杂度。同时，代码的结构清晰和注释详细也是提高代码可读性和可维护性的重要因素。

---
处理用时：33.69秒