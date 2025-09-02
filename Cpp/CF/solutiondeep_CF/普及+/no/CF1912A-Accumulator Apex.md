# 题目信息

# Accumulator Apex

## 题目描述

Allyn is playing a new strategy game called "Accumulator Apex". In this game, Allyn is given the initial value of an integer $ x $ , referred to as the accumulator, and $ k $ lists of integers. Allyn can make multiple turns. On each turn, Allyn can withdraw the leftmost element from any non-empty list and add it to the accumulator $ x $ if the resulting $ x $ is non-negative. Allyn can end the game at any moment. The goal of the game is to get the largest possible value of the accumulator $ x $ . Please help Allyn find the largest possible value of the accumulator $ x $ they can get in this game.

## 说明/提示

In the first input, we start with $ x = 1 $ . Then, we can take the first integer from the first list and get $ x = 0 $ — adding the next integer $ 2 $ from the first list we get $ x = 2 $ . After that, we can add the integers from the second list and obtain $ x = 3 $ . Finally, we can add the integers from the third list and obtain $ x = 4 $ .

In the second input, we can add the first integer from the second list and get $ x = 2 $ . Then, by adding the elements from the first list, we get $ x = 4 $ . We cannot add more integers to increase $ x $ .

## 样例 #1

### 输入

```
1 3
2 -1 2
2 -2 3
2 -3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
1 2
3 -1 -1 4
4 1 -3 -4 8```

### 输出

```
4```

# AI分析结果

### 题目内容重写
Allyn 正在玩一款名为“Accumulator Apex”的策略游戏。在游戏中，Allyn 被赋予一个初始值为 $x$ 的整数，称为累加器，以及 $k$ 个整数列表。Allyn 可以进行多次操作。每次操作中，Allyn 可以从任意非空列表中取出最左边的元素，并将其加到累加器 $x$ 上，前提是操作后的 $x$ 值非负。Allyn 可以在任何时候结束游戏。游戏的目标是使累加器 $x$ 的值尽可能大。请帮助 Allyn 找到累加器 $x$ 的最大可能值。

### 算法分类
贪心

### 综合分析与结论
该题的核心逻辑是通过贪心策略选择最优的列表元素进行累加，以确保累加器 $x$ 的值最大化。难点在于如何高效地选择元素，避免因选择不当导致 $x$ 值下降。题解中提出的思路是通过前缀和分段，将每个列表划分为若干段，每段的前缀和大于 0，表示该段可以带来正收益。通过优先队列选择代价最小、收益最大的段进行操作，从而实现全局最优。

### 所选题解
#### 题解作者：ylch (赞：3)
**星级：4.5**
**关键亮点：**
1. **前缀和分段**：通过计算前缀和，将每个列表划分为若干段，每段的前缀和大于 0，表示该段可以带来正收益。
2. **优先队列优化**：使用优先队列选择代价最小、收益最大的段进行操作，确保每次操作都能带来最大收益。
3. **时间复杂度优化**：通过合理的算法设计，将时间复杂度控制在 $O(n\log n)$，适合大规模数据处理。

**个人心得：**
作者在调试过程中发现，直接选择绝对值最小的负数并不总是最优策略，因此通过前缀和分段的方式，确保每次选择都能带来正收益。

**核心代码：**
```cpp
priority_queue <P> Q; // 存储代价和贡献的队列
for (int i = 1; i <= k; i ++)
{
    ll minn = a[i][1]; // 存储过程中的最小前缀和
    for (int j = 1; j < a[i].size(); j ++)
    {
        s[i][j] = s[i][j - 1] + a[i][j];
        minn = min(minn, s[i][j]);
        if (s[i][j] > 0)
        {
            Q.push({minn, s[i][j], i});
            pos[i] = j;
            break;
        }
    }
}

ll temp = x; // 替代变量
while (!Q.empty())
{
    P it = Q.top(); Q.pop();
    if (temp + it.a >= 0) // 注意a此时应为<=0的数
    {
        temp += it.b; // 直接加上收益即可
        int i = it.id;
        ll minn = s[i][pos[i]];
        for (int j = pos[i] + 1; j < a[i].size(); j ++)
        {
            if (j == pos[i] + 1) s[i][j] = a[i][j]; // 注意要以大于0的前缀和为界分段，所以计算每一段的前缀和是独立的，不能接着s[i][j-1]计算。要单独开一个新前缀和
            else s[i][j] = s[i][j - 1] + a[i][j];
            minn = min(minn, s[i][j]);

            if (s[i][j] > 0)
            {
                Q.push({minn, s[i][j], i});
                pos[i] = j;
                break;
            }
        }
    }
}
cout << temp << endl;
```

### 最优关键思路或技巧
1. **前缀和分段**：通过前缀和将列表划分为若干段，确保每段的前缀和大于 0，表示该段可以带来正收益。
2. **优先队列优化**：使用优先队列选择代价最小、收益最大的段进行操作，确保每次操作都能带来最大收益。

### 可拓展之处
该题的思路可以拓展到其他需要选择最优子序列的问题，如背包问题、任务调度问题等。通过前缀和和优先队列的结合，可以有效地解决类似的最优化问题。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：40.77秒