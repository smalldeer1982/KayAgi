# 题目信息

# Calendar Reform

## 题目描述

Reforms have started in Berland again! At this time, the Parliament is discussing the reform of the calendar. To make the lives of citizens of Berland more varied, it was decided to change the calendar. As more and more people are complaining that "the years fly by...", it was decided that starting from the next year the number of days per year will begin to grow. So the coming year will have exactly $ a $ days, the next after coming year will have $ a+1 $ days, the next one will have $ a+2 $ days and so on. This schedule is planned for the coming $ n $ years (in the $ n $ -th year the length of the year will be equal $ a+n-1 $ day).

No one has yet decided what will become of months. An MP Palevny made the following proposal.

- The calendar for each month is comfortable to be printed on a square sheet of paper. We are proposed to make the number of days in each month be the square of some integer. The number of days per month should be the same for each month of any year, but may be different for different years.
- The number of days in each year must be divisible by the number of days per month in this year. This rule ensures that the number of months in each year is an integer.
- The number of days per month for each year must be chosen so as to save the maximum amount of paper to print the calendars. In other words, the number of days per month should be as much as possible.

These rules provide an unambiguous method for choosing the number of days in each month for any given year length. For example, according to Palevny's proposition, a year that consists of 108 days will have three months, 36 days each. The year that consists of 99 days will have 11 months, 9 days each, and a year of 365 days will have 365 months, one day each.

The proposal provoked heated discussion in the community, the famous mathematician Perelmanov quickly calculated that if the proposal is supported, then in a period of $ n $ years, beginning with the year that has $ a $ days, the country will spend $ p $ sheets of paper to print a set of calendars for these years. Perelmanov's calculations take into account the fact that the set will contain one calendar for each year and each month will be printed on a separate sheet.

Repeat Perelmanov's achievement and print the required number $ p $ . You are given positive integers $ a $ and $ n $ . Perelmanov warns you that your program should not work longer than four seconds at the maximum test.

## 说明/提示

A note to the first sample test. A year of 25 days will consist of one month containing 25 days. A year of 26 days will consist of 26 months, one day each. A year of 27 days will have three months, 9 days each.

## 样例 #1

### 输入

```
25 3
```

### 输出

```
30
```

## 样例 #2

### 输入

```
50 5
```

### 输出

```
125
```

# AI分析结果



# Calendar Reform

## 题目描述

伯兰国再次启动改革！此次议会讨论的日历改革方案要求：从明年开始，每年天数逐年递增。首年有 $a$ 天，次年 $a+1$ 天，依此类推持续 $n$ 年。需满足：
1. 每月天数必须为某个整数的平方；
2. 年天数能被月天数整除；
3. 月天数尽可能大（确保用最少的纸张打印日历）。

求这 $n$ 年所用的总纸张数（每年每月一张）。

---

**算法分类**：数学

---

## 题解对比与结论

### 最优题解

#### 题解作者：lightningZ（★★★★★）
**关键亮点**：  
- **预处理平方因数**：通过双重循环预处理所有数的最大的平方因数，时间复杂度优化至 $O(N \log N)$  
- **数学建模**：将问题转化为求每个数的最大平方因数，转化为 $x = s^2 \cdot b$ 形式，结果即为 $b$ 的和  
**核心代码**：
```cpp
for(int i=1; i*i<=1e7; i++)
    for(int j=1; j*i*i<=1e7; j++)
        num[j*i*i] = j; // 记录最大平方因数分解后的系数
```

#### 题解作者：XXh0919（★★★★）
**关键亮点**：  
- **相同预处理逻辑**：与 lightningZ 思路一致，代码实现简洁  
- **高效输入输出**：使用 `ios::sync_with_stdio(0)` 优化读入速度  

#### 题解作者：Allanljx（★★★★）
**关键亮点**：  
- **类似埃筛思想**：通过枚举平方数及其倍数，填充答案数组  
- **直接计算结果**：预处理后直接遍历区间求和  

---

## 关键思路总结
1. **平方因数分解**：每个年份天数 $x$ 分解为 $x = s^2 \cdot b$，其中 $s$ 尽可能大，$b$ 即为月份数  
2. **预处理技巧**：从小到大枚举平方数 $s^2$，用其更新所有倍数的最优解，确保后续更大的平方数覆盖之前结果  
3. **时间复杂度优化**：利用类似埃氏筛的预处理方式，避免对每个数单独分解质因数  

---

## 拓展与相似题目
- **预处理技巧应用**：  
  - 洛谷 P2424 约数和（因数分解预处理）  
  - 洛谷 P1414 又是毕业季II（最大公约数因数问题）  
  - 洛谷 P1226 快速幂（数学运算优化）  

- **思维模式**：  
  将复杂问题转化为数学分解模型，通过预处理优化重复计算是此类题的核心思路  

---

## 个人心得摘录
- **避免暴力分解**：直接对每个数分解质因数会超时，预处理全局解更高效（lightningZ）  
- **逆向思维**：从平方数出发枚举倍数，而非从每个数出发找因数（Allanljx）  
- **覆盖式更新**：预处理时从小到大枚举平方数，确保后续更大的平方数覆盖正确结果（关键优化点）

---
处理用时：149.86秒