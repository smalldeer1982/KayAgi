# 题目信息

# Zero-Sum Prefixes

## 题目描述

The score of an array $ v_1,v_2,\ldots,v_n $ is defined as the number of indices $ i $ ( $ 1 \le i \le n $ ) such that $ v_1+v_2+\ldots+v_i = 0 $ .

You are given an array $ a_1,a_2,\ldots,a_n $ of length $ n $ . You can perform the following operation multiple times:

- select an index $ i $ ( $ 1 \le i \le n $ ) such that $ a_i=0 $ ;
- then replace $ a_i $ by an arbitrary integer.

What is the maximum possible score of $ a $ that can be obtained by performing a sequence of such operations?

## 说明/提示

In the first test case, it is optimal to change the value of $ a_2 $ to $ -2 $ in one operation.

The resulting array $ a $ will be $ [2,-2,1,-1,0] $ , with a score of $ 3 $ :

- $ a_1+a_2=2-2=0 $ ;
- $ a_1+a_2+a_3+a_4=2-2+1-1=0 $ ;
- $ a_1+a_2+a_3+a_4+a_5=2-2+1-1+0=0 $ .

In the second test case, it is optimal to change the value of $ a_3 $ to $ -2\,000\,000\,000 $ , giving us an array with a score of $ 1 $ .

In the third test case, it is not necessary to perform any operations.

## 样例 #1

### 输入

```
5
5
2 0 1 -1 0
3
1000000000 1000000000 0
4
0 0 0 0
8
3 0 2 -10 10 -30 30 0
9
1 0 0 1 -1 0 1 0 -1```

### 输出

```
3
1
4
4
5```

# AI分析结果



### 题目内容重写

#### 题目名称：零和前缀

**题目描述**  
数组 $v_1, v_2, \ldots, v_n$ 的得分为满足 $v_1 + v_2 + \ldots + v_i = 0$ 的索引 $i$（$1 \le i \le n$）的数量。  
给定长度为 $n$ 的数组 $a_1, a_2, \ldots, a_n$，你可以进行以下操作任意次：  
- 选择一个满足 $a_i = 0$ 的索引 $i$；  
- 将其替换为任意整数。  
求通过操作能获得的最大可能得分。

---

### 题解综合分析

#### 核心思路  
1. **分段处理**：以数组中的 `0` 为分界点，将数组分为多个区间。  
2. **前缀和众数统计**：在每个区间内，统计前缀和的众数出现次数，通过修改前一个 `0` 的值使得这些众数位置的前缀和变为 `0`。  
3. **初始段处理**：第一个 `0` 之前的前缀和无法修改，直接统计原始值为 `0` 的个数。

#### 解决难点  
- **区间划分与影响范围**：确定每个 `0` 修改后影响的区间范围（当前 `0` 到下一个 `0` 前的位置）。  
- **众数统计优化**：使用 `map` 或 `unordered_map` 高效统计前缀和出现次数，时间复杂度为 $O(n \log n)$。

---

### 精选题解（评分≥4星）

#### 1. Hovery 题解（⭐⭐⭐⭐⭐）  
**关键亮点**  
- 清晰地分段处理，逐段统计前缀和众数。  
- 代码简洁，直接遍历数组并维护区间。  
**核心代码**  
```cpp
for (;i <= n;) {
    int j = i + 1, Max = 1;
    map<int, int> mp;
    while (a[j] && j <= n) j++;
    for (int k = i ;k < j;k++) {
        mp[b[k]]++;
        Max = max(Max, mp[b[k]]);
    }
    i = j;
    ans += Max;
}
```

#### 2. Nuclear_Fish_cyq 题解（⭐⭐⭐⭐）  
**关键亮点**  
- 倒序遍历处理，避免漏判最后一个区间。  
- 特判原始前缀和为 `0` 的情况。  
**核心代码**  
```cpp
for(int i = n - 1; i >= 0; i--){
    cnt[s[i]]++;
    maxn = max(maxn, cnt[s[i]]);
    if(a[i] == 0){
        ans += maxn;
        maxn = 0;
        cnt.clear();
    }
}
cout << ans + cnt[0] << endl;
```

#### 3. Dry_ice 题解（⭐⭐⭐⭐）  
**关键亮点**  
- 结构清晰，显式处理第一个 `0` 之前的部分。  
- 使用 `map` 统计众数，代码可读性强。  
**核心代码**  
```cpp
for (int i = st, j; i <= n; i = j) {
    std::map<int, int> cnt; int now = 1;
    for (j = i + 1; j <= n && a[j]; ++j);
    for (int k = i; k < j; ++k) {
        ++cnt[s[k]];
        if (cnt[s[k]] > now) now = cnt[s[k]];
    }
    ans += now;
}
```

---

### 最优技巧总结  
1. **分段贪心**：将数组按 `0` 分块，每个块独立处理。  
2. **前缀和哈希统计**：利用 `map` 快速统计区间众数。  
3. **边界处理**：显式处理第一个 `0` 之前和最后一个 `0` 之后的区间。

---

### 拓展与举一反三  
- **类似题目**  
  1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（前缀和极值问题）  
  2. [P3131 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)（模数前缀和统计）  
  3. [CF1005C Summarize to the Power of Two](https://codeforces.com/problemset/problem/1005/C)（哈希表优化配对问题）  

- **个人心得**  
  - **调试教训**：需注意前缀和溢出问题，使用 `long long` 类型。  
  - **代码优化**：`map` 的频繁清空可能影响效率，尽量复用对象。

---
处理用时：56.01秒