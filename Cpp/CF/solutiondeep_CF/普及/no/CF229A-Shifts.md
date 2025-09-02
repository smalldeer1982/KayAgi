# 题目信息

# Shifts

## 题目描述

You are given a table consisting of $ n $ rows and $ m $ columns. Each cell of the table contains a number, 0 or 1. In one move we can choose some row of the table and cyclically shift its values either one cell to the left, or one cell to the right.

To cyclically shift a table row one cell to the right means to move the value of each cell, except for the last one, to the right neighboring cell, and to move the value of the last cell to the first cell. A cyclical shift of a row to the left is performed similarly, but in the other direction. For example, if we cyclically shift a row "00110" one cell to the right, we get a row "00011", but if we shift a row "00110" one cell to the left, we get a row "01100".

Determine the minimum number of moves needed to make some table column consist only of numbers 1.

## 说明/提示

In the first sample one way to achieve the goal with the least number of moves is as follows: cyclically shift the second row to the right once, then shift the third row to the left twice. Then the table column before the last one will contain only 1s.

In the second sample one can't shift the rows to get a column containing only 1s.

## 样例 #1

### 输入

```
3 6
101010
000100
100000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 3
111
000
```

### 输出

```
-1
```

# AI分析结果



### 题目重写
#### 题目：Shifts

**题目描述**  
给定一个包含 $n$ 行 $m$ 列的表格，每个单元格中的值为0或1。每次操作可以选择某一行，将其循环左移或右移一位。  
循环右移指将最后一个单元格的值移到第一个位置，其余右移一位；循环左移则相反。例如，"00110"右移一位变为"00011"，左移一位变为"01100"。  
求使某一列全为1的最小操作次数，若无法实现则输出-1。

**输入输出样例**  
样例1输入：  
3 6  
101010  
000100  
100000  
输出：3  

样例2输入：  
2 3  
111  
000  
输出：-1  

**说明/提示**  
样例1中，将第二行右移一次，第三行左移两次，最后一列前的一列全为1。样例2中第二行无1，无法完成。

---

### 算法分类  
**枚举**

---

### 题解分析与结论  
**核心思路**：枚举每一列作为目标列，计算每行到该列最近的1的距离之和的最小值。  
- **关键技巧**：  
  1. 预处理每行所有1的位置，并扩展为三倍长度数组（如原位置、原位置+m、原位置+2m），以处理循环边界。  
  2. 对每行使用二分查找，快速找到距离目标列最近的左右两侧的1。  
  3. 若某一行无1直接判无解。  

**最优代码亮点**（素质玩家孙1超，4★）：  
- 预处理1的位置扩展数组，避免循环取模计算。  
- 二分查找实现高效最近距离查询。  

---

### 关键代码实现  
```cpp
for (int i = 1; i <= n; i++) {
    // 预处理每行的1位置，复制到三倍长度数组中
    int pp = cnt[i];
    for (int j = 1; j <= pp; j++)
        a[i][++cnt[i]] = a[i][j] + m;
    for (int j = 1; j <= pp; j++)
        a[i][++cnt[i]] = a[i][j] + m + m;
}

// 枚举目标列i，计算总操作次数
int ans = inf;
for (int i = 1; i <= m; i++) {
    int s = 0;
    for (int j = 1; j <= n; j++) {
        // 二分查找最近的左右1的位置
        int right_pos = fs(j, 0, cnt[j], i + m); // 右侧最近的1
        int left_pos = fx(j, 0, cnt[j], i + m);  // 左侧最近的1
        s += min(right_pos - (i + m), (i + m) - left_pos);
    }
    ans = min(ans, s);
}
```

---

### 拓展与总结  
**同类问题套路**：  
- 循环数组处理：扩展数组模拟循环，避免复杂取模。  
- 二分查找优化：在有序数组中快速定位边界值。  

**推荐题目**：  
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心+移动操作）  
2. [P1582 倒水](https://www.luogu.com.cn/problem/P1582)（位运算+贪心）  
3. [CF1008B Turn the Rectangles](https://www.luogu.com.cn/problem/CF1008B)（枚举+贪心决策）  

**调试心得**：  
- 预处理数组长度需足够，否则二分越界。  
- 注意目标列的坐标在扩展数组中的映射（i+m对应原循环中的i位置）。

---
处理用时：59.82秒