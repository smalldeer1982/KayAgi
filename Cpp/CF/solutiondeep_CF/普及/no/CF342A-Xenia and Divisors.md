# 题目信息

# Xenia and Divisors

## 题目描述

Xenia the mathematician has a sequence consisting of $ n $ ( $ n $ is divisible by 3) positive integers, each of them is at most 7. She wants to split the sequence into groups of three so that for each group of three $ a,b,c $ the following conditions held:

- $ a&lt;b&lt;c $ ;
- $ a $ divides $ b $ , $ b $ divides $ c $ .

Naturally, Xenia wants each element of the sequence to belong to exactly one group of three. Thus, if the required partition exists, then it has ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF342A/cf2733ea0aacbe28f053605e4a0603ddeb7a4835.png) groups of three.

Help Xenia, find the required partition or else say that it doesn't exist.

## 样例 #1

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
6
2 2 1 1 4 6
```

### 输出

```
1 2 4
1 2 6
```

# AI分析结果



【中文题目重写】

# 泽尼亚与除数

## 题目描述

数学家泽尼亚有一个由 $n$ 个（$n$ 能被 3 整除）正整数组成的序列，每个数不超过 7。她希望将序列分成若干三个数的组，使得每个组中的三个数 $a,b,c$ 满足：

- $a < b < c$
- $a$ 整除 $b$，$b$ 整除 $c$

每个元素必须恰好属于一个三元组。若存在合法划分，输出所有三元组；否则输出 -1。

## 样例 #1

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
6
2 2 1 1 4 6
```

### 输出

```
1 2 4
1 2 6
```

【算法分类】构造

---

### 题解综合分析

所有题解均基于以下关键观察：

1. **合法三元组仅有三种**：`1-2-4`、`1-2-6`、`1-3-6`
2. **数值限制**：出现 5/7 直接无解
3. **特殊数值处理**：
   - 3 只能出现在 `1-3-6`
   - 4 只能出现在 `1-2-4`
   - 剩余 1/2/6 必须构成 `1-2-6`

核心难点在于处理各数值的依赖关系，需按 `1-3-6 → 1-2-4 → 1-2-6` 的优先级顺序分配。

---

### 精选题解

#### 1. FQR_ 的题解（⭐⭐⭐⭐⭐）
**亮点**：
- 代码简洁，逻辑清晰
- 使用桶计数与逐步剪枝策略
- 直接通过计数增减处理分组

```cpp
void finish() { /* 快速失败处理 */ }
int main() {
    // 统计各数字出现次数
    // 处理 5/7 的特殊情况
    if (存在5或7) finish();
    
    // 处理1-2-4组（必须满足4的个数 ≤ 1和2的个数）
    x = a[4]; a[1] -= x; a[2] -= x;
    
    // 处理1-3-6组（必须满足3的个数 ≤ 1和6的个数）
    y = a[3]; a[1] -= y; a[6] -= y;
    
    // 剩余1/2/6必须相等
    if (a[1] != a[2] || a[2] != a[6]) finish();
    
    // 输出各组
}
```

#### 2. ztyo_zysclown 的题解（⭐⭐⭐⭐）
**亮点**：
- 显式维护各数值剩余数量
- 分组顺序处理明确
- 调试注释清晰

```cpp
// 预处理5/7后
// 处理1-3-6组
if (a1 < a3 || a6 < a3) 无解;
// 处理1-2-6组剩余部分
if (a2 < a6剩余量) 无解;
// 最后验证1-2-4组平衡性
```

#### 3. ruruo 的题解（⭐⭐⭐⭐）
**亮点**：
- 使用宏定义简化错误处理
- 变量命名直观（cnt1/cnt2/cnt3 表示各组数量）

```cpp
#define end { 输出-1并退出 }
// 分组处理流程：
cnt1 = 1-3-6组数
cnt2 = 1-2-6组数
cnt3 = 1-2-4组数
```

---

### 关键思路总结

1. **有限组合枚举**：通过数值范围限制（≤7）枚举所有可能的三元组
2. **处理顺序依赖**：必须先处理具有唯一性的分组（如含3/4的分组）
3. **桶计数剪枝**：通过维护各数字剩余数量快速判断合法性

---

### 拓展练习

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 构造覆盖关系
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 贪心选择最优分隔线
3. [P1328 生活大爆炸版石头剪刀布](https://www.luogu.com.cn/problem/P1328) - 有限状态组合模拟

---
处理用时：56.18秒