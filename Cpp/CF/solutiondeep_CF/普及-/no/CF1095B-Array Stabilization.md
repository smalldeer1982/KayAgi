# 题目信息

# Array Stabilization

## 题目描述

You are given an array $ a $ consisting of $ n $ integer numbers.

Let instability of the array be the following value: $ \max\limits_{i = 1}^{n} a_i - \min\limits_{i = 1}^{n} a_i $ .

You have to remove exactly one element from this array to minimize instability of the resulting $ (n-1) $ -elements array. Your task is to calculate the minimum possible instability.

## 说明/提示

In the first example you can remove $ 7 $ then instability of the remaining array will be $ 3 - 1 = 2 $ .

In the second example you can remove either $ 1 $ or $ 100000 $ then instability of the remaining array will be $ 100000 - 100000 = 0 $ and $ 1 - 1 = 0 $ correspondingly.

## 样例 #1

### 输入

```
4
1 3 3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
1 100000
```

### 输出

```
0
```

# AI分析结果



### 题目内容中文翻译
# 数组稳定化

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。

定义数组的不稳定性为：$\max\limits_{i = 1}^{n} a_i - \min\limits_{i = 1}^{n} a_i$。

你需要**精确删除一个元素**，使得剩余 $(n-1)$ 个元素数组的不稳定性最小。要求计算可能的最小不稳定性。

## 说明/提示

样例1中删除 7 后剩余数组为 [1,3,3]，不稳定性为 3-1=2  
样例2中无论删除 1 还是 100000，不稳定性均为 0

## 样例 #1

### 输入
```
4
1 3 3 7
```

### 输出
```
2
```

## 样例 #2

### 输入
```
2
1 100000
```

### 输出
```
0
```

---

### 算法分类
**贪心**

---

### 题解分析与结论

所有题解均基于以下核心思路：
1. **排序后分析极值变化**：通过排序快速获取最大值、次大值、最小值、次小值
2. **贪心策略**：只需考虑删除最大值或最小值两种情况，计算剩余数组的极差并取最小值

**关键证明**：  
若删除中间元素，原数组的最大/最小值仍存在于剩余数组中，极差不会更优。因此最优解必然来自删除最大值或最小值的情况。

---

### 精选题解

#### 1. 红黑树（★★★★★）  
**亮点**：  
- 使用`stable_sort`保持相等元素相对顺序（虽然不影响结果但体现严谨性）
- 代码极度简洁（核心逻辑仅1行）

**核心代码**：
```cpp
stable_sort(val + 1, val + n + 1);
cout << min(val[n - 1] - val[1], val[n] - val[2]);
```

#### 2. Eason_AC（★★★★）  
**亮点**：  
- 变量命名清晰（`a_max`, `a'_min`等）
- 明确数学表达式描述思路

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
int ans = min(a[n] - a[2], a[n - 1] - a[1]);
```

#### 3. vocaloid（★★★★）  
**亮点**：  
- 明确说明贪心策略的理论依据
- 代码最简（仅8行）

**核心代码**：
```cpp
sort(a+1,a+n+1);
printf("%d\n",min(a[n]-a[2],a[n-1]-a[1]));
```

---

### 关键技巧总结
1. **极值分析**：排序后只需关注首尾四个值（最小、次小、次大、最大）
2. **问题转化**：将二维极值问题转化为一维排序问题
3. **边界处理**：当n=2时，两种计算方式结果均为0，无需特殊处理

---

### 拓展应用
1. **变式问题**：删除k个元素时的最小极差（需结合滑动窗口或二分）
2. **类似题目**：  
   - P1102 A-B数对（极差统计）  
   - P1440 求m区间内的最小值（极值动态维护）  
   - P2671 求和（极值关联的数学性质）

---

### 题解心得摘录
> "当n=2时，无论删哪个元素结果都是0，但代码中不需要特判，因为公式计算仍成立。" —— 红黑树  
> 启示：在保证正确性的前提下，尽量减少特殊判断能提升代码简洁性。

---
处理用时：128.16秒