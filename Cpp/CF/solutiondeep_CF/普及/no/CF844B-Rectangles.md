# 题目信息

# Rectangles

## 题目描述

You are given $ n×m $ table. Each cell of the table is colored white or black. Find the number of non-empty sets of cells such that:

1. All cells in a set have the same color.
2. Every two cells in a set share row or column.

## 说明/提示

In the second example, there are six one-element sets. Additionally, there are two two-element sets, the first one consists of the first and the third cells of the first row, the second one consists of the first and the third cells of the second row. To sum up, there are $ 8 $ sets.

## 样例 #1

### 输入

```
1 1
0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 3
1 0 1
0 1 0
```

### 输出

```
8
```

# AI分析结果



### 中文重写题目

**题目名称：矩形区域**

**题目描述**  
给定一个 $n×m$ 的表格，每个单元格被涂成白色（用0表示）或黑色（用1表示）。请计算满足以下条件的非空单元格集合的数量：  
1. 集合中的所有单元格颜色相同。  
2. 集合中任意两个单元格位于同一行或同一列。  

**输入输出样例**  
样例 #1：  
输入：  
1 1  
0  
输出：  
1  

样例 #2：  
输入：  
2 3  
1 0 1  
0 1 0  
输出：  
8  

**说明/提示**  
样例2中，除了6个单元素集合，还有两个两元素集合（第一行的第1、3单元格组成的集合和第二行的第1、3单元格组成的集合）。

---

### 算法分类  
**组合数学**

---

### 题解分析与结论

#### 核心思路
所有合法集合必须满足：  
1. 颜色相同且位于同一行或同一列。  
2. 统计每行/列中0和1的数量，分别计算其子集数（非空且元素≥1），最终需去重单元素集合（被行和列各算一次）。

#### 最优思路提炼
- **关键公式**：每行/列中颜色数为$k$时，合法子集数为 $(2^k - k - 1)$（排除单元素和空集）。  
- **去重技巧**：总答案累加所有行/列的子集数后，减去单元素重复计算的 $n×m$。  
- **实现技巧**：使用位运算 `1LL << k` 计算 $2^k$，避免浮点精度问题，并用 `long long` 防溢出。

---

### 精选题解

#### 题解1：codeLJH114514（⭐⭐⭐⭐⭐）  
**亮点**：  
- 清晰拆分问题为行、列独立计算。  
- 明确公式推导 $(2^c - c - 1)$ 的来源。  
- 强调必须使用 `long long` 和位运算的坑点。  

**代码核心**：  
```cpp
for (int i = 1; i <= n; i++) {
    int cnt0 = 0, cnt1 = 0;
    // 统计当前行的0和1数量
    ans += (1LL << cnt0) - cnt0 - 1; // 0的子集数
    ans += (1LL << cnt1) - cnt1 - 1; // 1的子集数
}
// 类似处理列...
cout << ans + n * m; // 最后减去n×m去重
```

#### 题解2：Jsxts_（⭐⭐⭐⭐）  
**亮点**：  
- 代码简洁高效，直接遍历行列统计颜色数。  
- 明确去重逻辑，代码注释简明。  

**代码核心**：  
```cpp
for (int i = 1; i <= n; i++)
    ans += (1ll << o_r[i]) - 1 + (1ll << l_r[i]) - 1; // 行贡献
for (int i = 1; i <= m; i++)
    ans += (1ll << o_c[i]) - 1 + (1ll << l_c[i]) - 1; // 列贡献
printf("%lld", ans - n * m); // 去重
```

---

### 推荐相似题目  
1. [P1145 火柴棒等式](https://www.luogu.com.cn/problem/P1145)（组合枚举）  
2. [P3414 SAC#1 - 组合数](https://www.luogu.com.cn/problem/P3414)（组合数性质）  
3. [P1866 编号](https://www.luogu.com.cn/problem/P1866)（乘法原理与组合）

---
处理用时：72.94秒