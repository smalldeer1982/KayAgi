# 题目信息

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4
```

### 输出

```
3 4 1 2
```

## 样例 #2

### 输入

```
2
```

### 输出

```
2 1
```

# AI分析结果



**唯一算法分类**：构造

---

### 综合分析与结论

**核心思路**  
构造排列时，将元素分块，块内递增，块间递减。块的大小取近似 $\sqrt{n}$，使得 LIS（块内长度）与 LDS（块的数量）之和最小。

**关键步骤**  
1. **分块策略**：块大小接近 $\sqrt{n}$，块内递增排列，块间按递减顺序连接。
2. **数学推导**：根据均值不等式，当块大小 $m$ 和块数 $k$ 满足 $m \approx k \approx \sqrt{n}$ 时，$m + k$ 最小。
3. **构造实现**：从大到小生成块，每个块填充连续递增序列。

**可视化设计**  
- **分块动画**：用不同颜色区分块，动态显示块内递增和块间递减的构造过程。
- **LIS/LDS 标注**：高亮当前块的 LIS 长度和总块数（LDS）。
- **复古风格**：8-bit 像素动画，分步生成块时播放音效，背景音乐循环播放。

---

### 题解清单（≥4星）

1. **FxorG（4.5星）**  
   - **亮点**：代码简洁，直接计算块大小并逆序生成块。
   - **核心代码**：循环生成块，从 `n-bl+1` 到 `n` 填充块内元素。

2. **agicy（4星）**  
   - **亮点**：通过大量样例验证分块策略，详细推导块长度与块数关系。
   - **核心代码**：分块时处理末尾不足整块的情况。

3. **沉石鱼惊旋（4星）**  
   - **亮点**：代码实现清晰，直接使用数学库计算块大小。
   - **核心代码**：分块生成时用 `sqrt(n)` 作为块长度。

---

### 最优代码实现

**FxorG 的代码**  
```cpp
#include <cstdio>
#include <cmath>

int main() {
    int n, bl;
    scanf("%d", &n);
    bl = sqrt(n);
    while (n > 0) {
        for (int i = n - bl + 1; i <= n; i++) {
            if (i > 0) printf("%d ", i);
        }
        n -= bl;
    }
    return 0;
}
```

**核心逻辑**：  
1. 计算块大小 `bl = sqrt(n)`。
2. 逆序生成块，块内元素递增（如 `n-bl+1` 到 `n`）。
3. 更新 `n` 为剩余元素数量，循环生成所有块。

---

### 相似题目推荐

1. **P1020 导弹拦截**  
   - 最长不升子序列与分块思想的应用。
2. **CF1144E Median String**  
   - 构造特定排列满足数学性质。
3. **P1071 潜伏者**  
   - 字符映射与排列构造问题。

---

### 可视化与算法演示

**动画设计**：  
1. **分块生成**：  
   - 每块用不同颜色，从右向左填充数值（如块 `5,6,7` 显示为蓝色方块）。
   - 动态标注当前块长度和剩余元素数。
2. **LIS/LDS 计算**：  
   - 箭头连接各块首元素，表示 LDS 的递减路径。
   - 高亮块内连续元素，表示 LIS 的递增路径。
3. **复古效果**：  
   - 8-bit 音效：生成块时播放短促音符，完成构造时播放胜利音效。
   - 像素字体显示当前 LIS/LDS 长度和总和。

**交互功能**：  
- **步进控制**：允许逐块生成，观察构造过程。
- **参数调节**：手动调整块大小，对比不同分块策略的效果。

---

**总结**：分块构造是本题的核心策略，结合数学推导与简洁的代码实现，通过可视化可直观理解算法流程。

---
处理用时：105.03秒