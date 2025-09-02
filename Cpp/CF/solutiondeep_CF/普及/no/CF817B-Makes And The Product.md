# 题目信息

# Makes And The Product

## 题目描述

After returning from the army Makes received a gift — an array $ a $ consisting of $ n $ positive integer numbers. He hadn't been solving problems for a long time, so he became interested to answer a particular question: how many triples of indices $ (i, j, k) $ ( $ i&lt;j&lt;k $ ), such that $ a_{i}·a_{j}·a_{k} $ is minimum possible, are there in the array? Help him with it!

## 说明/提示

In the first example Makes always chooses three ones out of four, and the number of ways to choose them is $ 4 $ .

In the second example a triple of numbers $ (1,2,3) $ is chosen (numbers, not indices). Since there are two ways to choose an element $ 3 $ , then the answer is $ 2 $ .

In the third example a triple of numbers $ (1,1,2) $ is chosen, and there's only one way to choose indices.

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 2 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6
1 3 3 1 3 2
```

### 输出

```
1
```

# AI分析结果



### 中文重写题目
**题目名称：Makes 与乘积**

**题目描述**  
Makes 从军队归来后收到一个礼物——由 $n$ 个正整数组成的数组 $a$。由于长时间未解决问题，他想知道：在数组中满足 $i<j<k$ 的三元组 $(i,j,k)$ 中，使得 $a_i \cdot a_j \cdot a_k$ 的值最小的有多少个？请帮他计算答案。

**输入输出样例**  
样例 #1：  
输入：  
4  
1 1 1 1  
输出：  
4  
解释：从四个1中选三个的组合数为4。  

样例 #2：  
输入：  
5  
1 3 2 3 4  
输出：  
2  
解释：三元组乘积最小为1×2×3=6，有两种选法。  

样例 #3：  
输入：  
6  
1 3 3 1 3 2  
输出：  
1  
解释：唯一满足条件的三元组为前两个1和最后的2。  

**算法分类**  
数学（组合计数）

---

### 题解对比与结论
各题解核心思路均为排序后分情况组合计数，关键点在于如何分类前三个元素的关系。最优解法通过排序后统计第三个元素的出现次数，分三类情况计算组合数：

1. **前三元素全等**：从所有等于第三个元素的数中选3个，组合数公式为 $C(\text{tmp},3)$。
2. **后两元素相等但第一个不同**：固定第一个元素，从等于第三个元素的数中选2个，公式为 $C(\text{tmp},2)$。
3. **其他情况**：直接输出等于第三个元素的数量。

---

### 高分题解推荐
#### 题解1：Coros_Trusds（5星）
**亮点**  
- 思路清晰，分类简洁，代码高效。
- 直接统计第三个元素的数量，避免冗余计算。

**关键代码**  
```cpp
sort(a+1, a+n+1);
int tmp = count(a+1, a+n+1, a[3]);
if (a[1]==a[3]) 
    cout << tmp*(tmp-1)*(tmp-2)/6;
else if (a[2]==a[3]) 
    cout << tmp*(tmp-1)/2;
else 
    cout << tmp;
```

#### 题解2：wzy2021（5星）
**亮点**  
- 代码最简，逻辑直击核心。
- 通过排序后遍历统计，时间复杂度 $O(n \log n)$。

**关键代码**  
```cpp
sort(a+1, a+n+1);
int tmp = 0;
for (int i=1; i<=n; i++) 
    if (a[i] == a[3]) tmp++;
// 分三类输出组合数（同上）
```

---

### 关键思路总结
1. **排序确定最小值组合**：排序后最小三元组必为前三个元素。
2. **分情况组合计数**：
   - 前三元素相同时，计算组合数 $C(\text{出现次数},3)$。
   - 后两元素相同时，计算 $C(\text{出现次数},2)$。
   - 其他情况直接取第三个元素的出现次数。

---

### 拓展与相似题目
1. **组合数应用**：CF977D（序列变换中的组合模式）。
2. **排序后分情况计数**：P3799（统计组合数满足条件的三元组）。
3. **数学优化**：P1866（组合数模运算与路径计数）。

---
处理用时：206.92秒