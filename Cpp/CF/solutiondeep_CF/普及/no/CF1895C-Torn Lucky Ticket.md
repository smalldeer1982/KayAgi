# 题目信息

# Torn Lucky Ticket

## 题目描述

A ticket is a non-empty string of digits from $ 1 $ to $ 9 $ .

A lucky ticket is such a ticket that:

- it has an even length;
- the sum of digits in the first half is equal to the sum of digits in the second half.

You are given $ n $ ticket pieces $ s_1, s_2, \dots, s_n $ . How many pairs $ (i, j) $ (for $ 1 \le i, j \le n $ ) are there such that $ s_i + s_j $ is a lucky ticket? Note that it's possible that $ i=j $ .

Here, the + operator denotes the concatenation of the two strings. For example, if $ s_i $ is 13, and $ s_j $ is 37, then $ s_i + s_j $ is 1337.

## 样例 #1

### 输入

```
10
5 93746 59 3746 593 746 5937 46 59374 6```

### 输出

```
20```

## 样例 #2

### 输入

```
5
2 22 222 2222 22222```

### 输出

```
13```

## 样例 #3

### 输入

```
3
1 1 1```

### 输出

```
9```

# AI分析结果



# Torn Lucky Ticket

## 题目描述

一张“票”是由1到9的数字组成的非空字符串。

“幸运票”满足以下条件：

- 长度为偶数；
- 前半部分数字之和等于后半部分数字之和。

给定 $n$ 个票的片段 $s_1, s_2, \dots, s_n$，求有多少有序对 $(i,j)$ 使得 $s_i + s_j$ 是幸运票（拼接顺序为 $s_i$ 在前，$s_j$ 在后）。

注意：$(i,j)$ 和 $(j,i)$ 视为不同有序对，允许 $i=j$。

## 样例

### 输入样例1
```
10
5 93746 59 3746 593 746 5937 46 59374 6
```
### 输出样例1
```
20
```

### 输入样例2
```
5
2 22 222 2222 22222
```
### 输出样例2
```
13
```

### 输入样例3
```
3
1 1 1
```
### 输出样例3
```
9
```

---

**算法分类**：枚举、前缀和、组合数学

---

## 题解对比与总结

### 最优题解（5星）

**作者：IKUN314**

**关键思路**：
1. **预处理前缀和与后缀和**：对每个字符串预处理前缀和数组 `pre` 和后缀和数组 `ful`。
2. **动态桶计数**：维护一个桶数组 `buc[len][sum]`，记录已处理字符串中长度为 `len` 且总和为 `sum` 的字符串数量。
3. **分割点枚举**：对当前字符串枚举所有可能的分割点，计算作为左半部分或右半部分时所需的另一半字符串的长度和总和，通过桶快速查询符合条件的字符串数目。
4. **排序优化**：按字符串长度排序，确保每个字符串只需与前面的字符串配对，避免重复计数。

**核心代码**：
```cpp
sort(a+1,a+1+n,cmp); // 按长度排序
for (int i=1; i<=n; i++) {
    // 预处理前缀和pre、后缀和ful
    int len = dig[i][0];
    for (int j=1; j<=len; j++) {
        // 计算作为左半部分时所需条件
        if (len-j+1-(j-1) > 0 && ful[i][j]-pre[i][j-1] > 0)
            f[i] += buc[len-j+1-(j-1)][ful[i][j]-pre[i][j-1]];
        // 计算作为右半部分时所需条件
        if (j-(len-j) > 0 && pre[i][j]-ful[i][j+1] > 0)
            f[i] += buc[j-(len-j)][pre[i][j]-ful[i][j+1]];
    }
    // 更新桶
    buc[len][ful[i][1]]++;
}
```

---

## 关键技巧总结

1. **预处理分割条件**：对每个字符串枚举所有可能的分割点，计算对应的长度和总和差。
2. **桶数组快速查询**：用桶记录各长度和总和的字符串数量，实现 $O(1)$ 查询。
3. **排序优化**：按长度排序后动态维护桶，确保每个字符串仅与已处理的字符串配对，避免重复。

---

## 相似题目推荐

1. [P1214 等差数列](https://www.luogu.com.cn/problem/P1214) - 枚举与预处理。
2. [P1102 A-B数对](https://www.luogu.com.cn/problem/P1102) - 桶计数优化。
3. [P1866 幸运数字](https://www.luogu.com.cn/problem/P1866) - 组合数学与前缀和。

---
处理用时：245.50秒