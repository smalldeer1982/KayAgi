# 题目信息

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# AI分析结果



---

## **算法分类**  
前缀和与奇偶性统计、枚举优化

---

## **题解思路与算法要点**  
### **核心思路**  
1. **问题转化**  
   - 每个数可任意排列二进制位的1，因此只需关注1的个数。  
   - 合法子区间需满足两个条件：  
     - 总1数为偶数（保证异或为0的可能性）。  
     - 最大1的个数不超过总1数的一半（避免无法抵消）。  

2. **优化策略**  
   - **前缀和奇偶性**：利用前缀和统计总1数的奇偶性，快速计算满足偶数的区间数。  
   - **短区间暴力检查**：对于长度≤64的区间，直接枚举并检查最大值条件；长区间因总和足够大，自动满足第二个条件，无需检查。  

### **解决难点**  
- **高效统计偶数区间数**：通过前缀和模2的奇偶性，用计数数组`cnt`维护历史奇偶性出现次数，实现O(1)查询。  
- **避免重复计算**：对每个右端点，仅需检查前64个左端点，时间复杂度优化至O(n*64)。  

---

## **题解评分（≥4星）**  
1. **开始新的记忆（★★★★☆）**  
   - **亮点**：清晰的前缀和奇偶性统计，短区间暴力检查逻辑明确。  
   - **代码**：维护最大值时倒序遍历，减少冗余计算。  

2. **蒟酱（★★★★☆）**  
   - **亮点**：代码简洁，使用`__builtin_popcountll`快速计算1的个数，逻辑与注释对应性强。  

3. **Graphcity（★★★★☆）**  
   - **亮点**：分情况处理长短区间，明确长度超过128时无需检查最大值，逻辑直观。  

---

## **最优思路与技巧**  
1. **奇偶性前缀和**：用`cnt`数组记录奇偶性出现次数，快速统计合法偶数区间。  
2. **短区间枚举**：利用最大值上限特性（如64），仅需暴力检查有限长度区间。  
3. **倒序维护最大值**：在遍历左端点时倒序更新最大值，避免重复计算。  

---

## **同类型题与套路**  
- **类似题目**：统计满足奇偶性/最大值的子数组数目。  
- **通用套路**：  
  - 前缀和结合模数统计（如奇偶性、余数）。  
  - 最大值分治或滑动窗口优化（如笛卡尔树、双指针）。  

---

## **推荐题目**  
1. **洛谷 P1469**：子数组异或和为0的数目（前缀异或和）。  
2. **LeetCode 1524**：和为奇数的子数组数（奇偶性统计）。  
3. **CodeForces 1398C**：子数组和等于长度的数目（前缀和转换）。  

---

## **个人心得摘录**  
- **Jsxts**：提到“分治+线段树”虽复杂但适用性广，但实际实现后反思“为何要将简单题复杂化”。  
- **cike_bilibili**：在调试中发现短区间暴力检查的常数优化是关键，避免陷入复杂数据结构。  

---

## **可视化与算法演示**  
### **核心流程可视化**  
1. **动画设计**：  
   - **像素风格**：每个数用色块表示1的个数，奇偶前缀和用不同颜色标记。  
   - **步进演示**：右端点`i`处理时，左侧64个左端点`j`逐一高亮，显示最大值和总和判断。  

2. **交互功能**：  
   - **单步执行**：允许用户逐元素观察前缀和更新与检查逻辑。  
   - **音效提示**：合法区间播放上扬音调，非法区间播放低音提示。  

### **复古像素实现片段**  
```javascript
// 伪代码：绘制像素风格的前缀和与检查逻辑
function drawStep(i) {
  ctx.fillStyle = i % 2 === 0 ? "#FF0000" : "#00FF00"; // 奇偶色
  ctx.fillRect(i * 10, 0, 8, 8); // 绘制前缀和状态
  for (let j = i; j >= Math.max(0, i - 64); j--) {
    highlight(j, i); // 高亮当前检查区间
    if (checkMax(j, i)) playSound("error"); // 不合法音效
  }
}
```

---

## **代码实现（核心逻辑）**  
### **前缀和与短区间检查（蒟酱）**  
```cpp
for (int l = 1; l <= n; l++) {
  ans += cnt[(sum += a[l]) & 1]++;
  // 检查前58个右端点
  for (int r = l, max = 0, num = 0; r <= min(n, l + 58); r++) {
    max = std::max(max, a[r]);
    ans -= (num += a[r]) % 2 == 0 && 2 * max > num;
  }
}
```

### **前缀奇偶性统计（开始新的记忆）**  
```cpp
for (int i = 1; i <= n; ++i) {
  // 计算前缀和并更新答案
  anss[i] = anss[i - 1] + num[i];
  ans += cnt[anss[i] % 2];
  // 倒序维护最大值并检查非法区间
  for (int j = i, k = i + 1, maxn = 0; j >= 1 && j >= i - 64; --j) {
    while (k > j) maxn = max(maxn, num[--k]);
    if (maxn * 2 > anss[i] - anss[j - 1] && anss[i] % 2 == anss[j - 1] % 2)
      --ans;
  }
  ++cnt[anss[i] % 2];
}
```

---
处理用时：183.92秒