# 题目信息

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3```

### 输出

```
4
11
0
20```

# AI分析结果



---

**算法分类**: 数论

---

### **题解思路与算法要点**

#### **核心数学原理**
- **完全平方数的因子特性**：只有完全平方数的因子个数为奇数。
- **异或前缀和性质**：区间异或和可表示为前缀异或差的异或：$s_j \oplus s_{i-1}$。
- **补集转换**：总子数组数 $n(n+1)/2$ 减去异或和为完全平方数的子数组数。

#### **解决难点**
1. **高效枚举完全平方数**：  
   异或和范围上限为 $2n$，故需枚举 $x^2 \leq 2n$ 的平方数，共 $O(\sqrt{n})$ 个。
2. **快速统计异或和为平方数的子数组数**：  
   利用哈希表记录前缀异或和的出现次数，对每个右端点 $j$，累加哈希表中 $s_j \oplus x^2$ 的出现次数。

#### **关键公式推导**
- **异或性质**：$s_j \oplus s_{i-1} = x^2 \Leftrightarrow s_{i-1} = s_j \oplus x^2$。
- **统计公式**：对每个右端点 $j$，答案贡献为 $\sum_{x=0}^{\sqrt{2n}} \text{cnt}[s_j \oplus x^2]$。

---

### **题解评分（≥4星）**

1. **Jasper08（⭐⭐⭐⭐）**  
   - 思路清晰，直接枚举平方数并维护桶统计。
   - 代码可读性较好，但桶大小 `M=1e6+10` 可能存在空间浪费。
   - 时间复杂度 $O(n\sqrt{n})$，适用于大范围数据。

2. **Engulf（⭐⭐⭐⭐⭐）**  
   - 代码简洁，使用动态计算平方数，避免预处理。
   - 正确处理异或和范围到 $2n$，哈希表初始化合理。
   - 时间复杂度严格 $O(n\sqrt{n})$，空间更优。

3. **yinhee（⭐⭐⭐⭐）**  
   - 预处理平方数到 $2n$，哈希表空间优化为 $2n$。
   - 处理了 $s_j \oplus x^2$ 的越界问题，鲁棒性强。

---

### **最优思路提炼**
1. **补集转换**：总子数组数减去异或和为平方数的数目。
2. **前缀异或和 + 哈希表**：维护前缀异或和的计数，枚举平方数 $x^2$，查询 $s_j \oplus x^2$ 的出现次数。
3. **平方数范围优化**：枚举 $x^2 \leq 2n$，避免无效计算。

---

### **同类型题与算法套路**
- **异或前缀和模型**：统计子数组异或和为特定值（如 LeetCode 1310）。
- **完全平方数特性**：利用数论特性转换问题（如 Codeforces 1731C）。
- **哈希表优化计数**：通过哈希表减少重复计算（如 LeetCode 560）。

---

### **推荐题目**
1. **洛谷 P1463**（完全平方数因子统计）  
2. **Codeforces 1731C**（异或和与平方数）  
3. **LeetCode 1310**（子数组异或查询）

---

### **个人心得摘录**
- **Engulf**：强调初始化 `cnt[0] = 1`，正确处理 $s_j = x^2$ 的情况。
- **yinhee**：注意异或和可能超过 $n$，需预处理到 $2n$。

---

### **可视化算法演示**
```python
def visualize_xor_squares(a):
    n = len(a)
    s = [0] * (n+1)
    cnt = defaultdict(int)
    cnt[0] = 1
    squares = [x*x for x in range(int((2*n)**0.5)+2)]
    total = n*(n+1)//2
    
    for j in range(1, n+1):
        s[j] = s[j-1] ^ a[j-1]
        current = 0
        for x in squares:
            target = s[j] ^ x
            current += cnt.get(target, 0)
        cnt[s[j]] += 1
        total -= current
    
    return total
```

#### **可视化设计**
- **动画效果**：  
  - **异或前缀和计算**：高亮当前元素 $a[j]$，显示 $s[j]$ 的更新。  
  - **平方数枚举**：用不同颜色标记每个 $x^2$，显示 $s_j \oplus x^2$ 的哈希表查询过程。  
  - **计数更新**：实时显示哈希表变化，统计结果逐步减少。  
- **复古像素风格**：  
  - 使用 8-bit 字体显示前缀和与平方数，背景色块标记哈希表命中。  
  - 音效：命中时播放“哔”声，完成一轮枚举后播放短旋律。  

---

**核心代码片段（Engulf 思路）**  
```cpp
vector<int> cnt(2 * n + 5);
cnt[0] = 1;
LL res = (LL)n * (n + 1) / 2;
int pre = 0;
for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    pre ^= x;
    for (int j = 0; (pre ^ j * j) <= 2 * n; j++)
        res -= cnt[pre ^ j * j];
    cnt[pre]++;
}
```

---
处理用时：79.49秒