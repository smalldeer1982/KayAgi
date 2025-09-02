# 题目信息

# Divide and Multiply

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609A/ed5b77bcb83c3732516ccac033270f15c3ac243c.png)William has array of $ n $ numbers $ a_1, a_2, \dots, a_n $ . He can perform the following sequence of operations any number of times:

1. Pick any two items from array $ a_i $ and $ a_j $ , where $ a_i $ must be a multiple of $ 2 $
2. $ a_i = \frac{a_i}{2} $
3. $ a_j = a_j \cdot 2 $

Help William find the maximal sum of array elements, which he can get by performing the sequence of operations described above.

## 说明/提示

In the first example test case the optimal sequence would be:

1. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{4}{2} = 2 $ and $ a_1 = 6 \cdot 2 = 12 $ , making the array look as: \[12, 2, 2\].
2. Pick $ i = 2 $ and $ j = 1 $ . After performing a sequence of operations $ a_2 = \frac{2}{2} = 1 $ and $ a_1 = 12 \cdot 2 = 24 $ , making the array look as: \[24, 1, 2\].
3. Pick $ i = 3 $ and $ j = 1 $ . After performing a sequence of operations $ a_3 = \frac{2}{2} = 1 $ and $ a_1 = 24 \cdot 2 = 48 $ , making the array look as: \[48, 1, 1\].

The final answer $ 48 + 1 + 1 = 50 $ .

In the third example test case there is no way to change the sum of elements, so the answer is $ 10 $ .

## 样例 #1

### 输入

```
5
3
6 4 2
5
1 2 3 4 5
1
10
3
2 3 4
15
8 8 8 8 8 8 8 8 8 8 8 8 8 8 8```

### 输出

```
50
46
10
26
35184372088846```

# AI分析结果



# Divide and Multiply

## 题目描述

William 有一个包含 $n$ 个数字的数组 $a_1, a_2, \dots, a_n$。他可以进行任意次数的以下操作序列：

1. 选择数组中的两个元素 $a_i$ 和 $a_j$，其中 $a_i$ 必须是偶数
2. 将 $a_i$ 除以 2
3. 将 $a_j$ 乘以 2

帮助 William 找到通过执行上述操作可以得到的数组元素最大总和。

## 样例 #1

### 输入

```
5
3
6 4 2
5
1 2 3 4 5
1
10
3
2 3 4
15
8 8 8 8 8 8 8 8 8 8 8 8 8 8 8```

### 输出

```
50
46
10
26
35184372088846```

---

## 题解分析与结论

所有题解均采用**贪心策略**，核心思路为：将所有数的 2 因子剥离后集中到最大的基数上。操作不影响总和但能重新分配因子，最优方案是将所有 2 的幂次乘到最大基数（奇数部分）上。

### 最优题解亮点

#### 1. 作者：智子（★★★★☆）
**关键亮点**：  
- 无需排序，直接遍历找最大值，时间复杂度优化至 $O(n)$  
- 代码简洁直观，使用位运算快速计算 2 的幂次  
```cpp
int p = 1; // 最大值位置初始化
for(int i=2; i<=n; i++) if(a[i]>a[p]) p=i; // 遍历找最大基数
a[p] <<= cnt; // 位运算快速乘2^cnt
```

#### 2. 作者：WRuperD（★★★★☆）
**关键亮点**：  
- 代码结构清晰，利用标准排序简化逻辑  
- 预处理 2 因子剥离，思路易于理解  
```cpp
sort(a+1, a+n+1); // 排序后最大值在末尾
a[n] *= pow(2, cnt); // 所有2因子赋予最大值
```

#### 3. 作者：方塘（★★★★☆）
**独特优化**：  
- 动态维护最大值，节省排序时间  
- 预处理 2 的幂次表提升计算效率  
```cpp
if(k>ma) ans+=ma, ma=k; // 动态更新最大值
ans += er[c] * ma; // 预计算2^c乘最大值
```

---

## 关键思路总结
1. **因子剥离**：将每个数分解为 $x \cdot 2^y$ 形式，记录总 2 因子数 $cnt$。
2. **最大值集中**：所有 $2^{cnt}$ 乘到最大基数 $x$ 上，确保最终数最大化。
3. **贪心证明**：较大基数乘相同 2 的幂次收益更高，总和必然最大。

---

## 相似题目推荐
1. **CF1371D Grid-00100**（贪心构造）  
2. **洛谷 P1223 排队接水**（贪心排序）  
3. **洛谷 P1016 旅行家的预算**（资源分配贪心）  

---

## 题解心得摘录
- **智子**：强调"大基数乘 2 更优"，点明贪心本质。  
- **方塘**：提出"2 因子自由分配"，启发操作顺序无关性。  
- **Marsrayd**：调试经历体现代码简化的重要性，避免过度设计。

---
处理用时：77.29秒