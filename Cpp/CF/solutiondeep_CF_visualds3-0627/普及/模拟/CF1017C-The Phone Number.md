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



### 唯一算法分类
构造、分块策略

---

### 综合分析与结论
**核心思路**：将排列划分为多个递增块，块间递减，使得LIS=块长，LDS=块数，总和接近 $2\sqrt{n}$。分块大小取 $\sqrt{n}$ 附近整数。

**解决难点**：
1. 证明分块构造的最优性（Dilworth定理、均值不等式）
2. 处理非平方数时的余数分块
3. 确保块内递增、块间递减的构造正确性

**可视化设计**：
1. **像素动画**：以不同颜色方块表示各个块，块内浅绿（递增），块间深红（递减）
2. **高亮操作**：动态绘制分块过程，高亮当前生成的块
3. **音效**：分块完成时播放“叮”音效，每块填充时播放像素音效
4. **自动演示**：以sqrt(n)速度分块填充，展示LIS/LDS计算过程

---

### 题解清单（≥4星）
1. **FxorG（5星）**  
   代码简洁，直接取块长为sqrt(n)向下取整，逆序分块输出，可读性强。

2. **皎月半洒花（4星）**  
   数学推导详细，处理非整除情况更严谨，但代码稍复杂。

3. **agicy（4星）**  
   通过大量数据归纳分块规律，代码实现逆向思维处理余数。

---

### 最优思路与代码实现
**关键技巧**：分块大小为 $\lfloor \sqrt{n} \rfloor$，每块逆序生成，整体块间降序排列。

```cpp
#include <cstdio>
#include <cmath>
int main() {
    int n, bl;
    scanf("%d", &n);
    bl = sqrt(n);
    while (n > 0) {
        for (int i = n - bl + 1; i <= n; ++i)
            if (i > 0) printf("%d ", i);
        n -= bl;
    }
    return 0;
}
```

---

### 类似题目
1. **P1020 导弹拦截**：Dilworth定理应用
2. **CF1144F Graph Without Long Directed Paths**：构造性分块
3. **P1969 积木大赛**：分段处理思维

---

### 可视化与复古动画
**Canvas 动画**：
1. 初始化n个灰色方块
2. 按分块顺序填充颜色：当前块渐变为绿色，块间边界红色
3. 动态显示LIS（最大块长）和LDS（块数）

**音效设计**：
- 块填充：8-bit "beep"
- 完成构造：胜利音效
- 错误分块：短促警报

**AI演示**：
1. 计算sqrt(n)，显示分块策略
2. 逐步填充方块，同步高亮LIS/LDS计算

---

### 总结
通过分块策略平衡LIS和LDS，数学推导与构造技巧结合，实现简洁高效。掌握此类构造题的关键在于发现隐藏的数学最优模型。

---
处理用时：103.64秒