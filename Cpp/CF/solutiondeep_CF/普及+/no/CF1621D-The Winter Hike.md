# 题目信息

# The Winter Hike

## 题目描述

Circular land is an $ 2n \times 2n $ grid. Rows of this grid are numbered by integers from $ 1 $ to $ 2n $ from top to bottom and columns of this grid are numbered by integers from $ 1 $ to $ 2n $ from left to right. The cell $ (x, y) $ is the cell on the intersection of row $ x $ and column $ y $ for $ 1 \leq x \leq 2n $ and $ 1 \leq y \leq 2n $ .

There are $ n^2 $ of your friends in the top left corner of the grid. That is, in each cell $ (x, y) $ with $ 1 \leq x, y \leq n $ there is exactly one friend. Some of the other cells are covered with snow.

Your friends want to get to the bottom right corner of the grid. For this in each cell $ (x, y) $ with $ n+1 \leq x, y \leq 2n $ there should be exactly one friend. It doesn't matter in what cell each of friends will be.

You have decided to help your friends to get to the bottom right corner of the grid.

For this, you can give instructions of the following types:

- You select a row $ x $ . All friends in this row should move to the next cell in this row. That is, friend from the cell $ (x, y) $ with $ 1 \leq y < 2n $ will move to the cell $ (x, y + 1) $ and friend from the cell $ (x, 2n) $ will move to the cell $ (x, 1) $ .
- You select a row $ x $ . All friends in this row should move to the previous cell in this row. That is, friend from the cell $ (x, y) $ with $ 1 < y \leq 2n $ will move to the cell $ (x, y - 1) $ and friend from the cell $ (x, 1) $ will move to the cell $ (x, 2n) $ .
- You select a column $ y $ . All friends in this column should move to the next cell in this column. That is, friend from the cell $ (x, y) $ with $ 1 \leq x < 2n $ will move to the cell $ (x + 1, y) $ and friend from the cell $ (2n, y) $ will move to the cell $ (1, y) $ .
- You select a column $ y $ . All friends in this column should move to the previous cell in this column. That is, friend from the cell $ (x, y) $ with $ 1 < x \leq 2n $ will move to the cell $ (x - 1, y) $ and friend from the cell $ (1, y) $ will move to the cell $ (2n, y) $ .

Note how friends on the grid border behave in these instructions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1621D/7dcaab901980e50347f58a947000827b29e91e59.png)Example of applying the third operation to the second column. Here, colorful circles denote your friends and blue cells are covered with snow.You can give such instructions any number of times. You can give instructions of different types. If after any instruction one of your friends is in the cell covered with snow he becomes ill.

In order to save your friends you can remove snow from some cells before giving the first instruction:

- You can select the cell $ (x, y) $ that is covered with snow now and remove snow from this cell for $ c_{x, y} $ coins.

You can do this operation any number of times.

You want to spend the minimal number of coins and give some instructions to your friends. After this, all your friends should be in the bottom right corner of the grid and none of them should be ill.

Please, find how many coins you will spend.

## 说明/提示

In the first test case you can remove snow from the cells $ (2, 1) $ and $ (2, 2) $ for $ 100 $ coins. Then you can give instructions

- All friends in the first collum should move to the previous cell. After this, your friend will be in the cell $ (2, 1) $ .
- All friends in the second row should move to the next cell. After this, your friend will be in the cell $ (2, 2) $ .

In the second test case you can remove all snow from the columns $ 3 $ and $ 4 $ for $ 22 $ coins. Then you can give instructions

- All friends in the first row should move to the next cell.
- All friends in the first row should move to the next cell.
- All friends in the second row should move to the next cell.
- All friends in the second row should move to the next cell.
- All friends in the third column should move to the next cell.
- All friends in the third column should move to the next cell.
- All friends in the fourth column should move to the next cell.
- All friends in the fourth column should move to the next cell.

It can be shown that none of the friends will become ill and that it is impossible to spend less coins.

## 样例 #1

### 输入

```
4
1
0 8
1 99
2
0 0 0 0
0 0 0 0
9 9 2 2
9 9 9 9
2
0 0 4 2
0 0 2 4
4 2 4 2
2 4 2 4
4
0 0 0 0 0 0 0 2
0 0 0 0 0 0 2 0
0 0 0 0 0 2 0 0
0 0 0 0 2 0 0 0
0 0 0 2 2 0 2 2
0 0 2 0 1 6 2 1
0 2 0 0 2 4 7 4
2 0 0 0 2 0 1 6```

### 输出

```
100
22
14
42```

# AI分析结果

### 题目内容中文重写
# 冬季徒步旅行

## 题目描述
环形区域是一个 $2n \times 2n$ 的网格。该网格的行从顶部到底部用从 $1$ 到 $2n$ 的整数编号，列从左到右用从 $1$ 到 $2n$ 的整数编号。对于 $1 \leq x \leq 2n$ 和 $1 \leq y \leq 2n$，单元格 $(x, y)$ 是第 $x$ 行和第 $y$ 列交叉处的单元格。

在网格的左上角有 $n^2$ 个你的朋友。也就是说，在每个满足 $1 \leq x, y \leq n$ 的单元格 $(x, y)$ 中恰好有一个朋友。其他一些单元格被雪覆盖。

你的朋友们想要到达网格的右下角。为此，在每个满足 $n + 1 \leq x, y \leq 2n$ 的单元格 $(x, y)$ 中应该恰好有一个朋友。每个朋友最终在哪个单元格并不重要。

你决定帮助你的朋友们到达网格的右下角。

为此，你可以给出以下类型的指令：
- 你选择一行 $x$。该行中的所有朋友应该移动到该行中的下一个单元格。也就是说，位于单元格 $(x, y)$ 且 $1 \leq y < 2n$ 的朋友将移动到单元格 $(x, y + 1)$，位于单元格 $(x, 2n)$ 的朋友将移动到单元格 $(x, 1)$。
- 你选择一行 $x$。该行中的所有朋友应该移动到该行中的前一个单元格。也就是说，位于单元格 $(x, y)$ 且 $1 < y \leq 2n$ 的朋友将移动到单元格 $(x, y - 1)$，位于单元格 $(x, 1)$ 的朋友将移动到单元格 $(x, 2n)$。
- 你选择一列 $y$。该列中的所有朋友应该移动到该列中的下一个单元格。也就是说，位于单元格 $(x, y)$ 且 $1 \leq x < 2n$ 的朋友将移动到单元格 $(x + 1, y)$，位于单元格 $(2n, y)$ 的朋友将移动到单元格 $(1, y)$。
- 你选择一列 $y$。该列中的所有朋友应该移动到该列中的前一个单元格。也就是说，位于单元格 $(x, y)$ 且 $1 < x \leq 2n$ 的朋友将移动到单元格 $(x - 1, y)$，位于单元格 $(1, y)$ 的朋友将移动到单元格 $(2n, y)$。

请注意在这些指令中网格边界上的朋友是如何移动的。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1621D/7dcaab901980e50347f58a947000827b29e91e59.png) 对第二列应用第三个操作的示例。这里，彩色圆圈表示你的朋友，蓝色单元格被雪覆盖。

你可以任意多次给出这样的指令。你可以给出不同类型的指令。如果在任何指令之后，你的一个朋友位于被雪覆盖的单元格中，他就会生病。

为了拯救你的朋友，你可以在给出第一个指令之前从一些单元格中清除积雪：
- 你可以选择当前被雪覆盖的单元格 $(x, y)$，并花费 $c_{x, y}$ 枚硬币清除该单元格中的积雪。

你可以任意多次执行此操作。

你希望花费最少的硬币并给你的朋友们一些指令。在此之后，你所有的朋友都应该在网格的右下角，并且没有一个人生病。

请找出你将花费多少硬币。

## 说明/提示
在第一个测试用例中，你可以花费 $100$ 枚硬币清除单元格 $(2, 1)$ 和 $(2, 2)$ 中的积雪。然后你可以给出指令：
- 第一列中的所有朋友应该移动到前一个单元格。在此之后，你的朋友将位于单元格 $(2, 1)$。
- 第二行中的所有朋友应该移动到下一个单元格。在此之后，你的朋友将位于单元格 $(2, 2)$。

在第二个测试用例中，你可以花费 $22$ 枚硬币清除第 $3$ 列和第 $4$ 列中的所有积雪。然后你可以给出指令：
- 第一行中的所有朋友应该移动到下一个单元格。
- 第一行中的所有朋友应该移动到下一个单元格。
- 第二行中的所有朋友应该移动到下一个单元格。
- 第二行中的所有朋友应该移动到下一个单元格。
- 第三列中的所有朋友应该移动到下一个单元格。
- 第三列中的所有朋友应该移动到下一个单元格。
- 第四列中的所有朋友应该移动到下一个单元格。
- 第四列中的所有朋友应该移动到下一个单元格。

可以证明没有一个朋友会生病，并且不可能花费更少的硬币。

## 样例 #1
### 输入
```
4
1
0 8
1 99
2
0 0 0 0
0 0 0 0
9 9 2 2
9 9 9 9
2
0 0 4 2
0 0 2 4
4 2 4 2
2 4 2 4
4
0 0 0 0 0 0 0 2
0 0 0 0 0 0 2 0
0 0 0 0 0 2 0 0
0 0 0 0 2 0 0 0
0 0 0 2 2 0 2 2
0 0 2 0 1 6 2 1
0 2 0 0 2 4 7 4
2 0 0 0 2 0 1 6
```
### 输出
```
100
22
14
42
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先确定右下角 $n\times n$ 区域的积雪必须清除，然后通过分析发现，无论采用何种移动方案，至少会经过右上角或左下角区域的四个顶点之一（共八个特殊点），而只要清除这八个点中代价最小的那个点的积雪，就可以构造出一种方案让所有朋友安全到达右下角。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| 一念之间、、 | 通过手推样例找规律，发现红色四个点无论怎么动，都至少经过蓝色八个点之一，且经过一个蓝色点就可把所有人送到右下角，答案为八个点取 min 加右下角的和 | 先计算右下角区域的积雪代价和，再找出八个特殊点的最小代价 | 找到移动的规律和关键的八个特殊点 | 4星 |
| Alex_Wei | 考虑四个特定格子，若要移动其中任意一个，必然需要清理八个特定格子上任意一个格子的雪，且清理一个就能构造方案 | 计算右下角区域的积雪代价和，找出八个特殊点的最小代价 | 证明清理一个特定点就能构造出可行方案 | 4星 |
| xuyifei0302 | 先确定右下角区域的积雪必须清除，然后将问题转化为一个朋友从左上角出发到右下角的最小花费，通过讨论不同出发格子的情况，得出只需计算八种情况的花费取最小值 | 计算右下角区域的积雪代价和，找出八个特殊点的最小代价 | 分析出从左上角出发的不同路径及对应的特殊点 | 4星 |

### 所选题解
- 作者：一念之间、、，4星。关键亮点：通过手推样例找规律，思路清晰，代码实现简洁。
- 作者：Alex_Wei，4星。关键亮点：对移动过程的分析较为详细，证明了清理一个特定点就能构造出可行方案。
- 作者：xuyifei0302，4星。关键亮点：将问题转化为一个朋友的移动问题，通过详细讨论不同出发格子的情况得出结论。

### 重点代码
```cpp
// 一念之间、、的代码
#include<bits/stdc++.h>
#define ll long long
using namespace std;
// 省略快读快写部分
int a[505][505];
int main(){
    int T=read();
    while(T--)
    {
        int n=read();
        for(int i=1;i<=n+n;i++)
            for(int j=1;j<=n+n;j++)a[i][j]=read();
        ll ans=0;
        for(int i=n+1;i<=n+n;i++)
            for(int j=n+1;j<=n+n;j++)ans+=a[i][j];
        int mn=2e9;
        mn=min(mn,a[1][n+1]);
        mn=min(mn,a[1][n+n]);
        mn=min(mn,a[n][n+1]);
        mn=min(mn,a[n][n+n]);
        mn=min(mn,a[n+1][n]);
        mn=min(mn,a[n+1][1]);
        mn=min(mn,a[n+n][1]);
        mn=min(mn,a[n+n][n]);
        cout<<ans+mn<<"\n";
    }
    pc('1',1);
    return 0;
}
```
核心实现思想：先读取输入的矩阵，计算右下角 $n\times n$ 区域的积雪代价和，然后找出八个特殊点的最小代价，最后将两者相加得到结果。

### 关键思路或技巧
- **找规律**：通过手推样例，发现移动的规律和关键的八个特殊点。
- **构造方案**：证明清理一个特定点就能构造出一种方案让所有朋友安全到达右下角。
- **问题转化**：将所有朋友的移动问题转化为一个朋友从左上角出发到右下角的最小花费问题。

### 拓展思路
同类型题可能会改变网格的形状、移动规则或积雪的分布，解题的关键仍然是找出关键的位置或路径，通过构造方案来解决问题。类似的算法套路包括分析问题的特殊性质，找到关键的突破点，然后构造出可行的解决方案。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的应用。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：考察二分答案的思想。
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：考察区间动态规划的应用。

### 个人心得
- 一念之间、、：很遗憾考试没有做出来。
- I_am_Accepted：考场上卡到结束的思维题 awa。不过还是建议难度评 `普及-`。 

---
处理用时：66.77秒