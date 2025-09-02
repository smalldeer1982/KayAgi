# 题目信息

# Color the Picture

## 题目描述

A picture can be represented as an $ n\times m $ grid ( $ n $ rows and $ m $ columns) so that each of the $ n \cdot m $ cells is colored with one color. You have $ k $ pigments of different colors. You have a limited amount of each pigment, more precisely you can color at most $ a_i $ cells with the $ i $ -th pigment.

A picture is considered beautiful if each cell has at least $ 3 $ toroidal neighbors with the same color as itself.

Two cells are considered toroidal neighbors if they toroidally share an edge. In other words, for some integers $ 1 \leq x_1,x_2 \leq n $ and $ 1 \leq y_1,y_2 \leq m $ , the cell in the $ x_1 $ -th row and $ y_1 $ -th column is a toroidal neighbor of the cell in the $ x_2 $ -th row and $ y_2 $ -th column if one of following two conditions holds:

- $ x_1-x_2 \equiv \pm1 \pmod{n} $ and $ y_1=y_2 $ , or
- $ y_1-y_2 \equiv \pm1 \pmod{m} $ and $ x_1=x_2 $ .

Notice that each cell has exactly $ 4 $ toroidal neighbors. For example, if $ n=3 $ and $ m=4 $ , the toroidal neighbors of the cell $ (1, 2) $ (the cell on the first row and second column) are: $ (3, 2) $ , $ (2, 2) $ , $ (1, 3) $ , $ (1, 1) $ . They are shown in gray on the image below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/e3c8d205b2238ddbd1672ed2006ec3bad526c6bc.png)The gray cells show toroidal neighbors of $ (1, 2) $ .Is it possible to color all cells with the pigments provided and create a beautiful picture?

## 说明/提示

In the first test case, one possible solution is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1710A/3537b81501ae3eaf0154251b0f27e35d8e63b1ec.png)In the third test case, we can color all cells with pigment $ 1 $ .

## 样例 #1

### 输入

```
6
4 6 3
12 9 8
3 3 2
8 8
3 3 2
9 5
4 5 2
10 11
5 4 2
9 11
10 10 3
11 45 14```

### 输出

```
Yes
No
Yes
Yes
No
No```

# AI分析结果

### 题目内容重写

#### 题目描述

一幅画可以表示为一个 $n \times m$ 的网格（$n$ 行 $m$ 列），每个格子被涂上一种颜色。你有 $k$ 种不同的颜料，每种颜料的量有限，具体来说，第 $i$ 种颜料最多可以涂 $a_i$ 个格子。

一幅画被认为是美丽的，如果每个格子至少有 $3$ 个环形相邻的格子与其颜色相同。

两个格子是环形相邻的，如果它们在环形意义上共享一条边。换句话说，对于某些整数 $1 \leq x_1, x_2 \leq n$ 和 $1 \leq y_1, y_2 \leq m$，位于第 $x_1$ 行第 $y_1$ 列的格子与位于第 $x_2$ 行第 $y_2$ 列的格子是环形相邻的，如果满足以下两个条件之一：

- $x_1 - x_2 \equiv \pm1 \pmod{n}$ 且 $y_1 = y_2$，或
- $y_1 - y_2 \equiv \pm1 \pmod{m}$ 且 $x_1 = x_2$。

注意，每个格子恰好有 $4$ 个环形相邻的格子。例如，如果 $n=3$ 且 $m=4$，那么格子 $(1, 2)$（第一行第二列）的环形相邻格子为：$(3, 2)$、$(2, 2)$、$(1, 3)$、$(1, 1)$。

### 题解分析与结论

#### 综合分析与结论

本题的核心在于如何利用有限的颜料涂满整个网格，并确保每个格子至少有3个环形相邻的格子与其颜色相同。通过对题解的分析，我们可以得出以下关键思路：

1. **颜色块的连续性**：每种颜色必须涂满连续的至少两行或两列，以确保每个格子有足够的相邻同色格子。
2. **贪心策略**：通过将颜料从大到小排序，优先使用能涂更多行或列的颜料，以确保总涂色量足够覆盖整个网格。
3. **奇偶性处理**：当总涂色量超过网格大小时，需要处理多出来的部分，确保不会出现单行或单列的情况。

#### 所选高星题解

1. **作者：linyuhuai (赞：9)**  
   - **星级：5星**  
   - **关键亮点**：详细证明了颜色块必须涂满连续两行或两列的必要性，并通过图示直观展示了不同情况下的涂色效果。代码实现中使用了优先队列来优化选择过程。  
   - **个人心得**：作者通过图示和详细证明，帮助读者更好地理解题目的核心要求，尤其是在处理边缘情况时的思路。  
   - **核心代码**：
     ```cpp
     priority_queue<int> pq1, pq2;
     for (int i = 0; i < k; ++i) {
         pq1.push(a[i] / m);
         pq2.push(a[i] / n);
     }
     int sum1 = 0, cnt1 = 0;
     while (!pq1.empty()) {
         int t = pq1.top(); pq1.pop();
         if (t < 2) break;
         sum1 += t;
         cnt1++;
         if (sum1 >= n && cnt1 * 2 <= n) {
             cout << "Yes" << endl;
             return;
         }
     }
     ```

2. **作者：taozhiming (赞：8)**  
   - **星级：4星**  
   - **关键亮点**：通过分析涂色块的奇偶性，提出了处理多出来部分的方法，确保不会出现单行或单列的情况。代码实现简洁明了。  
   - **核心代码**：
     ```cpp
     sort(a + 1, a + k + 1, cmp);
     bool ans1 = 1, ans2 = 1, flag = 0;
     ans = 0;
     for (int i = 1; i <= k; i++) {
         if (a[i] / m < 2) break;
         ans += a[i] / m;
         if (a[i] / m > 2) flag = 1;
     }
     if (ans < n) ans1 = 0;
     else if (((ans - n) & 1) && !flag) ans1 = 0;
     ```

3. **作者：JXR_Kalcium (赞：0)**  
   - **星级：4星**  
   - **关键亮点**：通过贪心策略和排序，确保在满足条件的情况下尽可能多地涂色。代码实现中使用了排序和简单的循环来判断是否满足条件。  
   - **核心代码**：
     ```cpp
     sort(a + 1, a + k + 1, cmp);
     for (int i = 1; i <= k; i++) {
         if (a[i] / n > 1) ans += a[i] / n, ++cnt;
         if (ans >= m) { bz += (cnt * 2 <= m); break; }
     }
     ```

### 最优关键思路与技巧

1. **颜色块的连续性**：确保每种颜色涂满至少两行或两列，以保证每个格子有足够的相邻同色格子。
2. **贪心策略**：优先使用能涂更多行或列的颜料，以确保总涂色量足够覆盖整个网格。
3. **奇偶性处理**：当总涂色量超过网格大小时，需要处理多出来的部分，确保不会出现单行或单列的情况。

### 可拓展之处

本题的贪心策略和奇偶性处理可以应用于其他类似的涂色问题，尤其是在需要满足某些相邻条件的情况下。类似的题目包括：

1. **洛谷 P1004 方格取数**：要求在网格中取数，满足某些相邻条件。
2. **洛谷 P1006 传纸条**：在网格中传递纸条，要求路径不相交。
3. **洛谷 P1008 三连击**：在网格中寻找满足某些条件的数字组合。

### 个人心得摘录

- **linyuhuai**：通过图示和详细证明，帮助读者更好地理解题目的核心要求，尤其是在处理边缘情况时的思路。
- **taozhiming**：通过分析涂色块的奇偶性，提出了处理多出来部分的方法，确保不会出现单行或单列的情况。

---
处理用时：42.05秒