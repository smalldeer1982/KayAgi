# 题目信息

# Expand the Path

## 题目描述

Consider a grid of size $ n \times n $ . The rows are numbered top to bottom from $ 1 $ to $ n $ , the columns are numbered left to right from $ 1 $ to $ n $ .

The robot is positioned in a cell $ (1, 1) $ . It can perform two types of moves:

- D — move one cell down;
- R — move one cell right.

The robot is not allowed to move outside the grid.

You are given a sequence of moves $ s $ — the initial path of the robot. This path doesn't lead the robot outside the grid.

You are allowed to perform an arbitrary number of modifications to it (possibly, zero). With one modification, you can duplicate one move in the sequence. That is, replace a single occurrence of D with DD or a single occurrence of R with RR.

Count the number of cells such that there exists at least one sequence of modifications that the robot visits this cell on the modified path and doesn't move outside the grid.

## 说明/提示

In the first testcase, it's enough to consider the following modified paths:

- RD $ \rightarrow $ RRD $ \rightarrow $ RRRD $ \rightarrow $ RRRDD $ \rightarrow $ RRRDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (1, 4) $ , $ (2, 4) $ , $ (3, 4) $ and $ (4, 4) $ ;
- RD $ \rightarrow $ RRD $ \rightarrow $ RRDD $ \rightarrow $ RRDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ , $ (3, 3) $ and $ (4, 3) $ ;
- RD $ \rightarrow $ RDD $ \rightarrow $ RDDD — this path visits cells $ (1, 1) $ , $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ and $ (4, 2) $ .

Thus, the cells that are visited on at least one modified path are: $ (1, 1) $ , $ (1, 2) $ , $ (1, 3) $ , $ (1, 4) $ , $ (2, 2) $ , $ (2, 3) $ , $ (2, 4) $ , $ (3, 2) $ , $ (3, 3) $ , $ (3, 4) $ , $ (4, 2) $ , $ (4, 3) $ and $ (4, 4) $ .

In the second testcase, there is no way to modify the sequence without moving the robot outside the grid. So the only visited cells are the ones that are visited on the path DRDRDRDR.

In the third testcase, the cells that are visited on at least one modified path are: $ (1, 1) $ , $ (2, 1) $ and $ (3, 1) $ .

Here are the cells for all testcases:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1644E/8385744beba9b4eb7d29fe889ed5f7f306a3c22f.png)

## 样例 #1

### 输入

```
3
4
RD
5
DRDRDRDR
3
D```

### 输出

```
13
9
3```

# AI分析结果

### 题目内容（中文重写）
# 扩展路径

## 题目描述
考虑一个大小为 $ n \times n $ 的网格。行从上到下编号为 $ 1 $ 到 $ n $，列从左到右编号为 $ 1 $ 到 $ n $。

机器人初始位于单元格 $ (1, 1) $。它可以执行两种类型的移动：
- D — 向下移动一个单元格；
- R — 向右移动一个单元格。

机器人不允许移出网格。

给定一个移动序列 $ s $ —— 机器人的初始路径。这个路径不会使机器人移出网格。

允许对其进行任意次数的修改（可能为零次）。一次修改可以将序列中的一个移动复制一次。也就是说，将单个的 D 替换为 DD，或将单个的 R 替换为 RR。

计算存在至少一种修改序列，使得机器人在修改后的路径上访问该单元格且不移出网格的单元格数量。

## 说明/提示
在第一个测试用例中，考虑以下修改后的路径就足够了：
- RD $ \rightarrow $ RRD $ \rightarrow $ RRRD $ \rightarrow $ RRRDD $ \rightarrow $ RRRDDD —— 此路径访问单元格 $ (1, 1) $、$ (1, 2) $、$ (1, 3) $、$ (1, 4) $、$ (2, 4) $、$ (3, 4) $ 和 $ (4, 4) $；
- RD $ \rightarrow $ RRD $ \rightarrow $ RRDD $ \rightarrow $ RRDDD —— 此路径访问单元格 $ (1, 1) $、$ (1, 2) $、$ (1, 3) $、$ (2, 3) $、$ (3, 3) $ 和 $ (4, 3) $；
- RD $ \rightarrow $ RDD $ \rightarrow $ RDDD —— 此路径访问单元格 $ (1, 1) $、$ (1, 2) $、$ (2, 2) $、$ (3, 2) $ 和 $ (4, 2) $。

因此，至少在一种修改后的路径上被访问的单元格是：$ (1, 1) $、$ (1, 2) $、$ (1, 3) $、$ (1, 4) $、$ (2, 2) $、$ (2, 3) $、$ (2, 4) $、$ (3, 2) $、$ (3, 3) $、$ (3, 4) $、$ (4, 2) $、$ (4, 3) $ 和 $ (4, 4) $。

在第二个测试用例中，没有办法在不使机器人移出网格的情况下修改序列。所以唯一被访问的单元格是在路径 DRDRDRDR 上被访问的单元格。

在第三个测试用例中，至少在一种修改后的路径上被访问的单元格是：$ (1, 1) $、$ (2, 1) $ 和 $ (3, 1) $。

以下是所有测试用例的单元格情况：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1644E/8385744beba9b4eb7d29fe889ed5f7f306a3c22f.png)

## 样例 #1
### 输入
```
3
4
RD
5
DRDRDRDR
3
D
```
### 输出
```
13
9
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先处理特殊情况（操作序列只有一个方向），然后分析一般情况。对于一般情况，都是通过计算原路径终点后还能向右和向下移动的格子数，利用这些信息来计算所有可能到达的格子数。不同题解在具体实现和表述上略有差异，但本质相同。

### 所选的题解
- **Troubadour 的题解（4星）**
    - **关键亮点**：思路清晰，代码实现简洁明了，对特殊情况和一般情况的处理逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
namespace GGMZ
{
    const int N = 2e5 + 5;
    char s[N];
    int x, y, n, ans;
    void work()
    {
        bool flag = 1;
        std::cin >> n >> s + 1;
        x = 1, y = 1;
        for (int i = 1;s[i];i++)
        {
            if (s[i] == 'R')x++;
            else y++;
            if (s[i] != s[i - 1] && i != 1)flag = 0;
        }
        if (flag == 1)
        {
            std::cout << n << '\n';
            return;
        }
        x = n - x, y = n - y;
        int i = 2;
        ans = 1;
        while (s[i] == s[i - 1])ans++, i++;
        for (i;s[i];i++)
        {
            ans++;
            if (s[i] == 'R')ans += y;
            else ans += x;
            if (s[i + 1] == 0)ans += (x + 1)*(y + 1);
        }
        std::cout << ans << '\n';
    }
}
#undef int
int main()
{
    int t;
    std::cin >> t;
    while (t--)GGMZ::work();
    return 0;
}
```
**核心实现思想**：先判断操作序列是否只有一个方向，若是则直接输出 $n$。否则计算原路径终点后还能向右和向下移动的格子数 $x$ 和 $y$，从第一次转向开始，对于每个格子，根据其移动方向加上对应的贡献，最后加上右下角的矩形区域的格子数。

### 最优关键思路或技巧
- 先处理特殊情况，简化问题。
- 通过计算原路径终点后还能移动的格子数，利用数学方法计算所有可能到达的格子数。

### 可拓展之处
同类型题可能会改变网格的形状、移动规则或修改操作的方式，但核心思路都是分析可能的移动范围和计算覆盖的格子数。类似算法套路可以应用于其他路径规划和覆盖问题。

### 推荐洛谷题目
- P1002 过河卒
- P1044 栈
- P1164 小A点菜

### 个人心得
题解中未包含个人心得。

---
处理用时：58.94秒