# 题目信息

# Given Length and Sum of Digits...

## 题目描述

You have a positive integer $ m $ and a non-negative integer $ s $ . Your task is to find the smallest and the largest of the numbers that have length $ m $ and sum of digits $ s $ . The required numbers should be non-negative integers written in the decimal base without leading zeroes.

## 样例 #1

### 输入

```
2 15
```

### 输出

```
69 96
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
-1 -1
```

# AI分析结果



# 给定长度和数位和...

## 题目描述

给定一个正整数 $m$ 和一个非负整数 $s$，要求找到满足以下条件的最小和最大的非负整数：
- 数的长度为 $m$（不含前导零）
- 各位数字之和为 $s$

## 样例 #1

### 输入
```
2 15
```

### 输出
```
69 96
```

## 样例 #2

### 输入
```
3 0
```

### 输出
```
-1 -1
```

---

**算法分类**：贪心

---

### 题解分析与结论

所有题解均基于贪心策略：
- **最小数构造**：首位为 1，剩余数字在低位尽可能填大
- **最大数构造**：高位尽可能填大
- **特判条件**：无解情况包括：和为 0 但长度大于 1、总和超过 9×m、长度或和不符合基本约束

---

### 精选题解

#### 1. 晨曦墨凝（4星）
**关键亮点**：
- 清晰的贪心思路与特判处理
- 分离处理最小数和最大数的构造逻辑
- 代码结构清晰，注释明确

**核心代码**：
```cpp
// 最小数构造
tmp = m - 1;
mi[1] = 1;
for (i = n; i >= 1 && tmp; --i) {
    if (tmp >= 9) mi[i] += 9, tmp -=9;
    else mi[i] += tmp, tmp =0;
}
// 最大数构造
for (i = 1; i <= n && tmp; ++i) {
    if (tmp >=9) ma[i]=9, tmp-=9;
    else ma[i]=tmp, tmp=0;
}
```

#### 2. TheSky233（5星）
**关键亮点**：
- 变量命名规范，逻辑简洁
- 通过单循环完成数字填充
- 特判处理集中，可读性强

**核心代码**：
```cpp
// 最小数构造
len = m, tot = s;
while (tot > 0 && len >=1) {
    if (tot >9) num[len--] =9, tot -=9;
    else num[len] = tot-1, num[1]++, tot=0;
}
// 最大数构造
len =1, tot =s;
while (tot >0 && len <=m) {
    if (tot >9) num[len++] =9, tot -=9;
    else num[len++] = tot, tot=0;
}
```

#### 3. Fearliciz（4星）
**关键亮点**：
- 特判条件数学化表达（如整除判断）
- 通过逆序填充最小数的低位
- 代码中体现对边界条件的深入思考

**核心代码**：
```cpp
// 最小数构造
a[m] =1;
ss =1;
while (ss +9 <=s) {
    a[++k1] =9;
    ss +=9;
}
if (s-ss) a[++k1] += s-ss;
```

---

### 关键思路总结
1. **最小数构造**：首位设为 1，剩余数位和从低位向高位填充最大值（9）
2. **最大数构造**：从高位向低位尽可能填充最大值（9）
3. **特判处理**：
   - 当 `s=0` 时，仅当 `m=1` 时有解（0）
   - 当 `s >9*m` 或 `m=0` 时无解

---

### 拓展与相似题目
1. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098) - 贪心构造字符串
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心删数使剩余数最小
3. [P1231 拼接数字](https://www.luogu.com.cn/problem/P1231) - 贪心排序构造最大数

---
处理用时：152.98秒