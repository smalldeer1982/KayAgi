# 题目信息

# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m
```

### 输出

```
3
6
5
```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b
```

### 输出

```
3
4
5
7
8
1
2
3
4
5
```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z
```

### 输出

```
10
10
```

# AI分析结果



### 算法分类
预处理

### 题解思路、算法要点与解决难点
#### 核心思路
题目要求在给定字符串中，通过最多修改 `m` 个字符，找到最长的连续相同字符 `c` 的子串。各题解的核心思路可归纳为两类：

1. **双指针滑动窗口**：  
   对每个查询单独处理，维护一个窗口 `[i, j]`，统计窗口中非 `c` 字符的数量 `sum`。当 `sum > m` 时移动左指针 `i`，否则扩展右指针 `j`。时间复杂度为 `O(nq)`，适用于小规模数据。

2. **预处理+前缀和**：  
   预处理所有可能的区间，计算每个字符 `c` 和修改次数 `x` 下的最大子串长度。通过前缀和快速计算区间内字符数量，并填充答案数组 `ans[x][c]`。最后对 `ans` 数组进行后缀最大值处理，确保每个 `x` 的值是允许至多 `x` 次修改的最大长度。预处理时间复杂度 `O(n² * 26)`，查询 `O(1)`，适用于大规模 `q`。

#### 难点对比
- **双指针**：需精确维护窗口的边界与非 `c` 字符的计数，确保在 `sum ≤ m` 时最大化窗口长度。难点在于指针移动的条件判断。
- **预处理**：需正确枚举所有区间并更新答案数组，同时处理整个字符串的全局最优情况（如修改所有字符为 `c`）。难点在于后缀最大值处理和全局最优的覆盖。

### 题解评分 (≥4星)
1. **Luo_gu_ykc（4星）**  
   使用双指针直接处理每个查询，代码简洁。但时间复杂度较高，无法应对大 `q`。
   
2. **Ninelife_Cat（4星）**  
   结合前缀和与双指针，利用前缀和快速计算区间字符数，优化双指针效率。代码可读性强，但同样面临 `O(nq)` 的瓶颈。

3. **Galex（4星）**  
   预处理所有区间并填充答案数组，查询高效。但未显式处理后缀最大值，可能遗漏部分情况（需额外处理全局最优）。

### 最优思路或技巧提炼
1. **滑动窗口的关键优化**  
   在窗口扩展时，若当前字符为 `c`，可继续右移右指针，无需增加 `sum`，从而最大化窗口长度。

2. **预处理+后缀最大值**  
   预处理所有区间后，对每个字符的 `ans` 数组进行后缀最大值处理，确保 `ans[x][c]` 表示允许至多 `x` 次修改时的最大长度。同时需处理全局最优（修改整个字符串）。

### 同类型题或类似算法套路
- **最大连续1的个数 III**（LeetCode 1004）：滑动窗口的经典应用。
- **区间覆盖问题**：通过预处理或双指针寻找最优覆盖区间。
- **动态维护后缀最大值**：在预处理后通过遍历填充最大值。

### 推荐洛谷题目
1. P1638 滑动窗口（双指针模板题）
2. P3143 [USACO16OPEN] Diamond Collector（前缀和+滑动窗口）
3. P2280 [HNOI2003] 激光炸弹（二维前缀和优化）

### 个人心得摘录
- **调试双指针**：注意 `sum` 的更新与指针移动的同步，可通过打印窗口状态验证。
- **预处理陷阱**：未处理后缀最大值时，可能导致较大 `m` 的查询结果错误。

### 可视化与算法演示
#### 核心算法流程（滑动窗口）
1. **初始化**：左指针 `i=0`，右指针 `j=0`，非 `c` 字符计数器 `sum=0`。
2. **扩展右指针**：若 `s[j] ≠ c`，增加 `sum`。当 `sum > m` 时停止。
3. **记录窗口长度**：当前窗口长度为 `j-i`，更新最大值。
4. **处理连续 `c`**：继续移动 `j` 直到遇到非 `c`，扩展窗口。
5. **移动左指针**：若 `s[i] ≠ c`，减少 `sum`，移动 `i`。

#### 可视化设计（复古像素风格）
- **颜色标记**：当前窗口用绿色高亮，非 `c` 字符用红色标记，指针移动时播放8位音效。
- **动画控制**：支持暂停/继续、步进，速度调节。背景音乐循环播放FC风格旋律。
- **自动演示模式**：AI模拟双指针移动，动态展示窗口扩展与收缩。

#### 代码片段（滑动窗口核心逻辑）
```cpp
int max_koyomity = 0, sum = 0;
for (int i = 0, j = 0; i < n; i++) {
    // 扩展右指针直到 sum > m 或到达末尾
    while (j < n && sum <= m) {
        if (s[j] != c) sum++;
        j++;
    }
    // 更新最大值（注意 j 可能多移动了一步）
    max_koyomity = max(max_koyomity, j - i - (sum > m ? 1 : 0));
    // 移动左指针前调整 sum
    if (s[i] != c) sum--;
}
```

### 总结
对于大规模查询，预处理结合后缀最大值处理是最优解；双指针实现简单且适用于小数据。正确性关键在于处理全局最优和后缀最大值，确保覆盖所有可能的修改次数。

---
处理用时：318.69秒