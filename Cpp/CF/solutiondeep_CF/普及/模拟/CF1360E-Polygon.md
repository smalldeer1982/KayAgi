# 题目信息

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目中文重写
# 多边形

## 题目描述
多边形（Polygon）不仅是开发问题的最佳平台，还是一个边长为 $n$ 的方阵，最初方阵中每个单元格都填充字符 `0`。

在这个多边形上进行了军事训练。士兵们在第一行的每个单元格上方放置了一门大炮，在第一列的每个单元格左侧也放置了一门大炮。这样，总共放置了 $2n$ 门大炮。

![初始边长为4的多边形](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)

大炮发射字符 `1`。在任何时刻，最多只有一门大炮发射。当 `1` 从大炮中射出后，它会向前飞行（沿着射击方向），直到与多边形边界或另一个 `1` 相撞。之后，它会占据相撞前所在的单元格并停留在那里。可以参考以下示例以更好地理解。

更正式地说：
- 如果一门大炮位于第 $i$ 行、第一列左侧并发射 `1`，那么这个 `1` 从单元格 $(i, 1)$ 开始飞行，最终停在某个单元格 $(i, j)$ 处。
- 如果一门大炮位于第 $j$ 列、第一行上方并发射 `1`，那么这个 `1` 从单元格 $(1, j)$ 开始飞行，最终停在某个单元格 $(i, j)$ 处。

例如，考虑以下射击序列：

![射击示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png)
1. 发射第 2 行的大炮。
2. 再次发射第 2 行的大炮。
3. 发射第 3 列的大炮。

你桌上有一份军事训练报告。这份报告是一个边长为 $n$ 的方阵，由 `0` 和 `1` 组成。你想知道这次训练是否真的按照报告中的情况进行。换句话说，是否存在一个射击序列，使得训练结束后得到给定的矩阵？

每门大炮可以发射任意次数。训练开始前，多边形的每个单元格都包含 `0`。

## 说明/提示
第一个测试用例在题目描述中已经解释过。

第二个测试用例的答案是 `NO`，因为从任何大炮射出并落在单元格 $(1, 1)$ 的 `1` 都会继续飞行。

## 样例 #1
### 输入
```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111
```

### 输出
```
YES
NO
YES
YES
NO
```

### 题解综合分析与结论
- **思路对比**：大部分题解思路一致，核心是判断矩阵中每个非边界的 `1` 右侧或下侧是否为 `1` ，若存在不满足此条件的 `1` 则矩阵不合法；而 `_xbn` 的题解采用深度优先搜索（DFS），从最下方和最右方的 `1` 开始向左上方搜索，统计合法 `1` 的数量，与总 `1` 的数量比较判断矩阵合法性。
- **算法要点**：多数题解通过双重循环遍历矩阵元素进行判断；DFS 题解则利用递归搜索合法 `1` 。
- **解决难点**：主要难点在于理解炮弹停止规则并转化为判断条件。多数题解通过逻辑判断解决；DFS 题解通过搜索和标记解决。

### 高评分题解
- **作者：Zhoumy（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接遍历矩阵判断非边界 `1` 的右侧和下侧情况。
    - **核心代码**：
```cpp
for(int j=1;j<n;j++)
    for(int k=1;k<n;k++)
        if(a[j][k]=='1'&&a[j][k+1]=='0'&&a[j+1][k]=='0')
            die=1;
```
    - **核心思想**：遍历矩阵中非边界元素，若元素为 `1` 且其右侧和下侧均为 `0` ，则标记矩阵不合法。
- **作者：Warriors_Cat（5星）**
    - **关键亮点**：思路清晰，解释了判断条件的合理性，并提到构造方法，代码规范。
    - **核心代码**：
```cpp
for(int i = 1; i <= n; ++i)
    a[n + 1][i] = 1, a[i][n + 1] = 1;
a[n + 1][n + 1] = 1;
bool flag = 1;
for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
        if(a[i][j] == 1 &&!a[i + 1][j] &&!a[i][j + 1]) {
            flag = 0;
            puts("NO");
            break;
        }
    }
    if(!flag) break;
}
if(flag) puts("YES");
```
    - **核心思想**：先将矩阵边界置为 `1` 方便处理，然后遍历矩阵元素，若元素为 `1` 且其右侧和下侧均为 `0` ，则标记矩阵不合法。
- **作者：Aisaka_Taiga（4星）**
    - **关键亮点**：思路清晰，代码简洁，对输入处理和判断条件有详细说明。
    - **核心代码**：
```cpp
for(int i=1;i<n;i++)
    for(int j=1;j<n;j++)
        if(a[i][j]=='1'&&a[i+1][j]=='0'&&a[i][j+1]=='0')
            flag=1;
```
    - **核心思想**：遍历矩阵中非边界元素，若元素为 `1` 且其右侧和下侧均为 `0` ，则标记矩阵不合法。

### 最优关键思路或技巧
- **思维方式**：根据炮弹停止规则，将问题转化为矩阵元素间的逻辑判断，通过分析 `1` 的右侧和下侧元素情况判断矩阵合法性。
- **代码实现技巧**：部分题解将矩阵边界置为 `1` ，简化边界情况的判断。

### 可拓展之处
同类型题可能会改变炮弹发射规则、矩阵形状或增加其他限制条件。解题时可借鉴本题分析规则并转化为逻辑判断的思路。

### 洛谷相似题目推荐
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：涉及矩阵元素的判断和填充，与本题对矩阵元素的处理有相似之处。
- [P1596 [USACO10OCT]Lake Counting S](https://www.luogu.com.cn/problem/P1596)：需要对矩阵中的元素进行遍历和判断，与本题的遍历判断思路类似。
- [P2089 烤鸡](https://www.luogu.com.cn/problem/P2089)：虽然问题场景不同，但都需要根据一定规则对情况进行判断和筛选。

### 个人心得摘录与总结
- **mot1ve**：用简单的方式证明判断条件的正确性，强调炮弹停下需有障碍承接，最后一行和最后一列因靠墙肯定合法，若非边界点右侧和下侧均为 `0` 则不合法。总结：在解题时可从问题本质出发，用简单易懂的方式证明结论。 

---
处理用时：40.60秒