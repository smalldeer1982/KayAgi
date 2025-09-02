# 题目信息

# Add, Divide and Floor

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ). In one operation, you can choose an integer $ x $ ( $ 0 \le x \le 10^{18} $ ) and replace $ a_i $ with $ \lfloor \frac{a_i + x}{2} \rfloor $ ( $ \lfloor y \rfloor $ denotes rounding $ y $ down to the nearest integer) for all $ i $ from $ 1 $ to $ n $ . Pay attention to the fact that all elements of the array are affected on each operation.

Print the smallest number of operations required to make all elements of the array equal.

If the number of operations is less than or equal to $ n $ , then print the chosen $ x $ for each operation. If there are multiple answers, print any of them.

## 说明/提示

In the first testcase, all elements are already equal, so $ 0 $ operations are required. It doesn't matter if you print an empty line afterwards or not.

In the second testcase, you can't make less than $ 2 $ operations. There are multiple answers, let's consider the answer sequence $ [2, 5] $ . After applying an operation with $ x = 2 $ , the array becomes $ [\lfloor \frac{4 + 2}{2} \rfloor, \lfloor \frac{6 + 2}{2} \rfloor] = [3, 4] $ . After applying an operation with $ x = 5 $ after that, the array becomes $ [\lfloor \frac{3 + 5}{2} \rfloor, \lfloor \frac{4 + 5}{2} \rfloor] = [4, 4] $ . Both elements are the same, so we are done.

In the last testcase, you can't make less than $ 6 $ operations. Since $ 6 $ is greater than $ n $ , you don't have to print them. One possible answer sequence is $ [0, 0, 0, 0, 0, 0] $ . We are just dividing the second element by $ 2 $ every time and not changing the first element.

## 样例 #1

### 输入

```
4
1
10
2
4 6
6
2 1 2 1 2 1
2
0 32```

### 输出

```
0
2
2 5
1
1
6```

# AI分析结果



【题目中文翻译】

# 添加、除法和下取整

## 题目描述

给定一个整数数组 $a_1, a_2, \dots, a_n$（$0 \le a_i \le 10^9$）。每次操作可以选择一个整数 $x$（$0 \le x \le 10^{18}$），并将所有元素替换为 $\lfloor \frac{a_i + x}{2} \rfloor$（$\lfloor y \rfloor$ 表示对 $y$ 向下取整）。要求输出使数组所有元素相等的最小操作次数。若操作次数不超过 $n$，还需输出每次选择的 $x$。

## 样例

输入输出示例见原题。

---

**算法分类**：贪心、数学

---

### 综合分析与结论

题目核心在于通过每次操作缩小数组的极差（最大值与最小值的差）。所有题解均基于以下观察：
1. **极差决定操作次数**：只需维护最大值和最小值，每次操作后它们的差决定了后续操作。
2. **奇偶性与二进制处理**：通过分析奇偶性或二进制位结构，选择最优的 $x$ 使差快速缩小。

最优思路总结：
- **奇偶性策略**：每次根据最大值和最小值的奇偶性选择 $x=0$ 或 $1$，确保差至少减半。
- **二进制前缀优化**：通过一次操作使最大值变为全 $1$ 的二进制数，后续操作选 $x=0$ 以快速对齐。

---

### 高分题解推荐

#### 1. 灵茶山艾府（★★★★★）
**关键亮点**：
- 通过二进制分析，直接计算操作次数，时间复杂度 $O(1)$。
- 首操作选 $x=2^L-1-\max(a)$ 最大化公共前缀，后续全选 $x=0$。
```go
func main() {
    // 核心逻辑
    u := 1<<bits.Len(uint(M)) -1
    x := u - M
    ans := 1 + bits.Len(uint((u/2)^((m+x)/2)))
    // 输出结果
}
```

#### 2. I_will_AKIOI（★★★★★）
**关键亮点**：
- 每次根据最小值的奇偶性选择 $x$，简洁高效。
- 代码实现极简，时间复杂度 $O(\log \text{max\_diff})$。
```cpp
while (maxx != minn) {
    k = minn % 2;
    minn = (minn + k) >> 1;
    maxx = (maxx + k) >> 1;
    ans.push_back(k);
}
```

#### 3. KarmaticEnding（★★★★☆）
**关键亮点**：
- 分类讨论奇偶性，明确 $x$ 的选择条件。
- 逻辑清晰，适用于快速推导。
```cpp
if (a_parity == even && b_parity == odd) x = 1;
else x = 0;
```

---

### 关键技巧总结
1. **极差与二进制位**：通过二进制位长度直接推导操作次数，减少循环。
2. **奇偶性优化**：将 $x$ 的取值简化为 0 或 1，保证差至少减半。
3. **首操作优化**：通过首操作对齐二进制前缀，大幅减少后续操作次数。

---

### 拓展与相似题目
1. **P2119 [NOIP2016 普及组] 魔法阵**（贪心策略）
2. **P7075 [CSP-S2020] 儒略日**（二进制时间处理）
3. **P1873 [COCI 2011/2012 #5] EKO**（二分答案与极差分析）

---

### 题解个人心得摘录
- **灵茶山艾府**：“首操作选 $x=2^L-1-\max(a)$ 使得后续只需处理低阶位” → 强调二进制思维。
- **I_will_AKIOI**：“每次选 $x$ 为奇偶性，代码极简” → 展示问题简化的艺术。

---
处理用时：139.48秒