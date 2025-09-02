# 题目信息

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# AI分析结果



【题目翻译】

# 加密（简单版）

## 题目描述

反抗军间谍Heidi刚刚从帝国获得了死星的计划，在逃离过程中需要破解加密。加密的第一层安全机制如下：

屏幕显示一个整数序列 $ A $ 和正整数 $ p $。加密代码 $ S $ 定义为：将 $ A $ 分割为两个非空连续子数组，两个子数组元素和分别对 $ p $ 取模后的总和最大值。

## 输入样例

样例 #1：
```
4 10
3 4 7 2
```
样例 #2：
```
10 12
16 3 24 13 9 8 7 5 12 12
```

## 输出样例

样例 #1：
```
16
```
样例 #2：
```
13
```

---

### 题解综合分析结论

所有题解均采用前缀和技巧，核心思路为：
1. 预处理前缀和数组
2. 枚举分割点计算两段模值和
3. 时间复杂度优化至 $ O(n) $

关键差异在于分割点边界处理和数据类型的正确性。仅部分题解正确处理了分割点范围和溢出问题。

---

### 精选题解（评分≥4星）

#### 1. [作者：chlchl] ⭐⭐⭐⭐⭐
**关键亮点**：
- 正确处理分割点范围（i < n）
- 使用 long long 避免溢出
- 代码简洁高效

**核心代码**：
```cpp
ll p, ans, s[N];
for(int i=1; i<n; i++) 
    ans = max(ans, s[i]%p + (s[n]-s[i])%p);
```
**实现思想**：
预处理前缀和数组后，遍历所有有效分割点（1 ≤ i < n），计算两段模值和的极值。

#### 2. [作者：Noby_Glds] ⭐⭐⭐⭐
**关键亮点**：
- 最简代码实现
- 正确分割点处理

**潜在缺陷**：
使用 int 存储前缀和，在大数据时可能溢出，建议改进为 long long。

**核心代码**：
```cpp
int s[100010];
for(int i=1; i<n; i++)
    ans = max(ans, s[i]%p + (s[n]-s[i])%p);
```

---

### 最优思路总结
1. **前缀和预处理**：快速获取任意区间的和
2. **有效分割点枚举**：确保两段非空（i ∈ [1, n-1]）
3. **模运算特性**：注意 (a + b) mod p ≠ a mod p + b mod p，需分别计算
4. **数据类型优化**：使用 long long 避免求和溢出

---

### 拓展练习（洛谷题目）
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   （前缀和/动态规划）
2. [P3131 Subsequences Summing to Sevens](https://www.luogu.com.cn/problem/P3131)  
   （模运算与前缀和结合）
3. [P3396 哈希冲突](https://www.luogu.com.cn/problem/P3396)  
   （模运算特性应用）

---

### 调试心得摘录
- **chlchl**："分割点不能是 n，否则导致空区间"  
  → 强调题目条件的精确解读
- **Coros_Trusds**："线段树杀鸡用牛刀"  
  → 选择与问题规模匹配的算法
- **Noby_Glds**代码简洁但忽略数据类型  
  → 平衡代码简洁性与健壮性

---
处理用时：133.92秒