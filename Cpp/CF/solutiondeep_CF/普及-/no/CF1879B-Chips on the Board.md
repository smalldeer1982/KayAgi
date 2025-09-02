# 题目信息

# Chips on the Board

## 题目描述

You are given a board of size $ n \times n $ ( $ n $ rows and $ n $ colums) and two arrays of positive integers $ a $ and $ b $ of size $ n $ .

Your task is to place the chips on this board so that the following condition is satisfied for every cell $ (i, j) $ :

- there exists at least one chip in the same column or in the same row as the cell $ (i, j) $ . I. e. there exists a cell $ (x, y) $ such that there is a chip in that cell, and either $ x = i $ or $ y = j $ (or both).

The cost of putting a chip in the cell $ (i, j) $ is equal to $ a_i + b_j $ .

For example, for $ n=3 $ , $ a=[1, 4, 1] $ and $ b=[3, 2, 2] $ . One of the possible chip placements is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1879B/41f651e9026b79c2105cacdfb396235f2e97b44b.png) White squares are emptyThe total cost of that placement is $ (1+3) + (1+2) + (1+2) = 10 $ .

Calculate the minimum possible total cost of putting chips according to the rules above.

## 说明/提示

The first test case of the example is described in the statement.

## 样例 #1

### 输入

```
4
3
1 4 1
3 2 2
1
4
5
2
4 5
2 3
5
5 2 4 5 3
3 4 2 1 5```

### 输出

```
10
9
13
24```

# AI分析结果

### 题目内容中文重写
# 棋盘上的棋子

## 题目描述
给定一个大小为 $n \times n$（$n$ 行 $n$ 列）的棋盘，以及两个长度为 $n$ 的正整数数组 $a$ 和 $b$。

你的任务是在这个棋盘上放置棋子，使得对于每个单元格 $(i, j)$ 都满足以下条件：
- 与单元格 $(i, j)$ 处于同一行或同一列的位置中至少有一个棋子。即存在一个单元格 $(x, y)$ ，该单元格中有棋子，并且要么 $x = i$，要么 $y = j$（或者两者都满足）。

在单元格 $(i, j)$ 放置一个棋子的成本等于 $a_i + b_j$。

例如，当 $n = 3$，$a = [1, 4, 1]$ 且 $b = [3, 2, 2]$ 时，一种可能的棋子放置方式如下：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1879B/41f651e9026b79c2105cacdfb396235f2e97b44b.png) 白色方块为空
该放置方式的总成本为 $(1 + 3) + (1 + 2) + (1 + 2) = 10$。

请计算按照上述规则放置棋子的最小可能总成本。

## 说明/提示
示例中的第一个测试用例在题目描述中已有说明。

## 样例 #1
### 输入
```
4
3
1 4 1
3 2 2
1
4
5
2
4 5
2 3
5
5 2 4 5 3
3 4 2 1 5
```

### 输出
```
10
9
13
24
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法。首先分析得出满足条件的放置方案要么是每行都有棋子，要么是每列都有棋子。然后分别计算这两种情况下的最小代价，最后取两者中的较小值作为最终答案。

在计算每行都有棋子的情况时，固定行的代价总和，让列的代价都取最小值；计算每列都有棋子的情况时，固定列的代价总和，让行的代价都取最小值。

### 所选题解
- **Nuclear_Fish_cyq（5星）**
    - **关键亮点**：思路清晰，详细解释了贪心算法的原理，代码简洁且有必要的注释，考虑到了 `int` 可能溢出的问题。
- **Κarrу5307（5星）**
    - **关键亮点**：简洁明了地阐述了贪心的思路，直接指出满足条件的选择方案只有两种，并且说明了如何计算这两种情况下的代价。
- **CheZiHe929（4星）**
    - **关键亮点**：思路和代码都很清晰，明确给出了完整的代码实现，使用 `long long` 避免了数据溢出问题。

### 重点代码
```cpp
// Nuclear_Fish_cyq 的代码
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t, n, a[300000], b[300000], mina, minb, suma, sumb;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    for(int kk = 0; kk < t; kk++){
        suma = 0;
        sumb = 0;
        mina = INT_MAX;
        minb = INT_MAX;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            suma += a[i];
            mina = min(mina, a[i]);
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
            sumb += b[i];
            minb = min(minb, b[i]);
        }
        cout << min(mina * n + sumb, minb * n + suma) << endl;
    }
    return 0;
}
```
**核心实现思想**：先读取输入的测试用例数量 `t`，对于每个测试用例，读取棋盘大小 `n` 以及数组 `a` 和 `b`。计算数组 `a` 和 `b` 的总和 `suma` 和 `sumb`，并找出数组 `a` 和 `b` 中的最小值 `mina` 和 `minb`。最后比较两种情况（每行都有棋子和每列都有棋子）的代价，输出较小值。

### 关键思路或技巧
- **贪心策略**：通过分析问题，得出满足条件的放置方案只有两种，即每行都有棋子或每列都有棋子，然后分别计算这两种情况下的最小代价。
- **避免数据溢出**：由于数据范围可能较大，使用 `long long` 类型来存储数据，避免 `int` 类型溢出。

### 拓展思路
同类型题或类似算法套路通常涉及在满足一定条件下求最优解的问题。可以通过分析问题的性质，找出满足条件的所有可能情况，然后使用贪心算法选择最优的方案。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：也是一道贪心算法的题目，通过每次合并最小的两个果子来使总代价最小。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据每个人接水所需时间进行排序，让接水时间短的人先接水，从而使总的等待时间最短。
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：通过计算每个物品的单位价值，优先选择单位价值高的物品，直到背包装满。

### 个人心得
- 樱雪喵：“被诈骗了，赛时卡 B 20min 来着。怎么能这么菜的。” 总结：在比赛中可能会因为对题目理解不透彻而浪费时间，需要加强对题目的分析和理解能力。

---
处理用时：37.18秒