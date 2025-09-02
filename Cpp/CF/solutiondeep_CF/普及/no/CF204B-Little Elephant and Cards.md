# 题目信息

# Little Elephant and Cards

## 题目描述

The Little Elephant loves to play with color cards.

He has $ n $ cards, each has exactly two colors (the color of the front side and the color of the back side). Initially, all the cards lay on the table with the front side up. In one move the Little Elephant can turn any card to the other side. The Little Elephant thinks that a set of cards on the table is funny if at least half of the cards have the same color (for each card the color of the upper side is considered).

Help the Little Elephant to find the minimum number of moves needed to make the set of $ n $ cards funny.

## 说明/提示

In the first sample there initially are three cards lying with colors 4, 4, 7. Since two of the three cards are of the same color 4, you do not need to change anything, so the answer is 0.

In the second sample, you can turn the first and the fourth cards. After that three of the five cards will be of color 7.

## 样例 #1

### 输入

```
3
4 7
4 7
7 4
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
4 7
7 4
2 11
9 7
1 1
```

### 输出

```
2
```

# AI分析结果



# Little Elephant and Cards

## 题目描述

小象喜欢玩彩色卡片。

他有 $n$ 张卡片，每张卡片的两面各有一种颜色（正面颜色和背面颜色）。初始时所有卡片正面朝上。每次操作可以翻转任意一张卡片。若至少有一半的卡片朝上面颜色相同，则称为有趣集合。求达成有趣集合所需的最小翻转次数。

## 说明/提示

样例1中三张卡片初始颜色为4、4、7，其中两张颜色相同，无需翻转。  
样例2中通过翻转两张卡片可得到三张颜色7的卡片。

## 算法分类
离散化、贪心

---

## 题解对比与结论

### 共同思路
1. **统计颜色出现次数**：需统计每个颜色在正反面出现的总次数，并确定是否达到半数要求。
2. **离散化处理**：由于颜色数值范围大（1e9），需用映射（map）将颜色压缩到连续整数。
3. **计算翻转次数**：对每个可行颜色，计算正面已有数量与目标差距，确定需翻转的反面卡片数。

### 解法差异
- **NY_An18623091997**：使用队列存储颜色，可能重复处理且未正确区分正反面相同的情况。
- **Hellen68**：正确离散化，用两个数组分别统计总次数和背面次数，逻辑清晰。
- **Su_Zipei**：代码简洁但未显式处理正反面相同的情况，可能导致统计错误。

### 最优解法总结
**Hellen68的解法（4.5星）**  
- **关键点**：  
  1. 离散化颜色，解决大范围数值问题。
  2. 准确统计总次数（`a[]`）和背面次数（`b[]`）。
  3. 直接计算正面已有数量（`a[i]-b[i]`），判断是否满足条件。
- **核心代码**：
  ```cpp
  for(int i = 1 ; i <= n ; ++ i) {
      int x , y;
      cin >> x >> y;
      if(mp[x] == 0) mp[x] = ++ cnt;
      if(mp[y] == 0) mp[y] = ++ cnt;
      a[mp[x]]++;
      if(x != y) {
          a[mp[y]]++;
          b[mp[y]]++;
      }
  }
  ```
  通过离散化统计每个颜色总出现次数及背面出现次数，随后遍历所有颜色计算最小翻转次数。

---

## 关键技巧
1. **离散化**：用map将大范围颜色值映射到连续小整数。
2. **双数组统计**：分别记录总次数和背面次数，避免重复计算。
3. **数学简化**：通过总次数与背面次数的差值直接得到初始正面数量。

---

## 类似题目
1. [CF831C](https://www.luogu.com.cn/problem/CF831C)（统计与离散化）
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（离散化应用）
3. [CF455A](https://www.luogu.com.cn/problem/CF455A)（贪心与计数结合）

---
处理用时：429.45秒