# 题目信息

# Hide and Seek

## 题目描述

Alice and Bob are playing a game on a line with $ n $ cells. There are $ n $ cells labeled from $ 1 $ through $ n $ . For each $ i $ from $ 1 $ to $ n-1 $ , cells $ i $ and $ i+1 $ are adjacent.

Alice initially has a token on some cell on the line, and Bob tries to guess where it is.

Bob guesses a sequence of line cell numbers $ x_1, x_2, \ldots, x_k $ in order. In the $ i $ -th question, Bob asks Alice if her token is currently on cell $ x_i $ . That is, Alice can answer either "YES" or "NO" to each Bob's question.

At most one time in this process, before or after answering a question, Alice is allowed to move her token from her current cell to some adjacent cell. Alice acted in such a way that she was able to answer "NO" to all of Bob's questions.

Note that Alice can even move her token before answering the first question or after answering the last question. Alice can also choose to not move at all.

You are given $ n $ and Bob's questions $ x_1, \ldots, x_k $ . You would like to count the number of scenarios that let Alice answer "NO" to all of Bob's questions.

Let $ (a,b) $ denote a scenario where Alice starts at cell $ a $ and ends at cell $ b $ . Two scenarios $ (a_i, b_i) $ and $ (a_j, b_j) $ are different if $ a_i \neq a_j $ or $ b_i \neq b_j $ .

## 说明/提示

The notation $ (i,j) $ denotes a scenario where Alice starts at cell $ i $ and ends at cell $ j $ .

In the first example, the valid scenarios are $ (1, 2), (2, 1), (2, 2), (2, 3), (3, 2), (3, 3), (3, 4), (4, 3), (4, 5) $ . For example, $ (3,4) $ is valid since Alice can start at cell $ 3 $ , stay there for the first three questions, then move to cell $ 4 $ after the last question.

 $ (4,5) $ is valid since Alice can start at cell $ 4 $ , stay there for the first question, the move to cell $ 5 $ for the next two questions. Note that $ (4,5) $ is only counted once, even though there are different questions that Alice can choose to do the move, but remember, we only count each pair of starting and ending positions once.

In the second example, Alice has no valid scenarios.

In the last example, all $ (i,j) $ where $ |i-j| \leq 1 $ except for $ (42, 42) $ are valid scenarios.

## 样例 #1

### 输入

```
5 3
5 1 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 8
1 2 3 4 4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
100000 1
42
```

### 输出

```
299997
```

# AI分析结果

### 题目翻译
# 捉迷藏

## 题目描述
爱丽丝和鲍勃正在一条有 $n$ 个格子的直线上玩游戏。有 $n$ 个从 $1$ 到 $n$ 编号的格子。对于从 $1$ 到 $n - 1$ 的每个 $i$，格子 $i$ 和 $i + 1$ 相邻。

爱丽丝最初在直线上的某个格子上有一个代币，鲍勃试图猜出它在哪里。

鲍勃按顺序猜测一系列直线格子编号 $x_1, x_2, \ldots, x_k$。在第 $i$ 个问题中，鲍勃问爱丽丝她的代币当前是否在格子 $x_i$ 上。也就是说，爱丽丝可以对鲍勃的每个问题回答“是”或“否”。

在这个过程中，最多有一次，在回答问题之前或之后，爱丽丝被允许将她的代币从当前格子移动到相邻的格子。爱丽丝的行动方式使得她能够对鲍勃的所有问题都回答“否”。

请注意，爱丽丝甚至可以在回答第一个问题之前或回答最后一个问题之后移动她的代币。爱丽丝也可以选择根本不移动。

给定 $n$ 和鲍勃的问题 $x_1, \ldots, x_k$。你需要计算让爱丽丝对鲍勃的所有问题都回答“否”的场景数量。

用 $(a, b)$ 表示爱丽丝从格子 $a$ 开始并在格子 $b$ 结束的场景。如果 $a_i \neq a_j$ 或 $b_i \neq b_j$，则两个场景 $(a_i, b_i)$ 和 $(a_j, b_j)$ 是不同的。

## 说明/提示
符号 $(i, j)$ 表示爱丽丝从格子 $i$ 开始并在格子 $j$ 结束的场景。

在第一个样例中，有效的场景是 $(1, 2), (2, 1), (2, 2), (2, 3), (3, 2), (3, 3), (3, 4), (4, 3), (4, 5)$。例如，$(3, 4)$ 是有效的，因为爱丽丝可以从格子 $3$ 开始，在前三个问题中停留在那里，然后在最后一个问题之后移动到格子 $4$。

$(4, 5)$ 是有效的，因为爱丽丝可以从格子 $4$ 开始，在第一个问题中停留在那里，然后在接下来的两个问题中移动到格子 $5$。请注意，$(4, 5)$ 只计算一次，即使爱丽丝可以选择在不同的问题时进行移动，但请记住，我们只对每个起始和结束位置对计算一次。

在第二个样例中，爱丽丝没有有效的场景。

在最后一个样例中，除了 $(42, 42)$ 之外，所有满足 $|i - j| \leq 1$ 的 $(i, j)$ 都是有效的场景。

## 样例 #1
### 输入
```
5 3
5 1 4
```
### 输出
```
9
```

## 样例 #2
### 输入
```
4 8
1 2 3 4 4 3 2 1
```
### 输出
```
0
```

## 样例 #3
### 输入
```
100000 1
42
```
### 输出
```
299997
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是枚举每个格子，考虑代币在该格子时的三种操作（左移、不动、右移）是否能使爱丽丝对所有问题回答“否”。为了判断操作是否可行，都需要预处理每个格子第一次被询问和最后一次被询问的时间。

### 题解评分与亮点
- **流绪的题解（4星）**
    - **亮点**：思路清晰，代码简洁，直接实现了枚举和判断的过程，变量命名简单易懂。
- **729hao的题解（3星）**
    - **亮点**：将思路分成三类详细阐述，代码结构使用了命名空间，有一定的模块化思想。
- **Nuclear_Fish_cyq的题解（3星）**
    - **亮点**：对思路有详细的文字说明，代码中对数组初始化等操作有注释。

### 关键思路与技巧
- 预处理 `minn` 数组记录每个格子第一次被询问的时间，`maxn` 数组记录每个格子最后一次被询问的时间，这样可以在 $O(1)$ 时间内判断移动是否会被发现。
- 枚举每个格子，分别判断左移、不动、右移三种操作是否可行，将可行的情况累加进答案。

### 拓展思路
同类型题可能会增加格子的维度（如二维平面）、增加移动的规则（如可以跳跃多个格子）或增加询问的条件（如询问某个区间内是否有代币）。解题的关键还是枚举所有可能的起始和结束位置，判断是否满足条件。

### 洛谷相似题目推荐
- P1036 选数（组合数学，枚举所有组合情况）
- P1047 校门外的树（模拟，枚举每个位置判断是否被移除）
- P1059 明明的随机数（排序、枚举去重）

### 重点代码
```cpp
// 流绪的题解核心代码
memset(maxn,-1,sizeof(maxn));
memset(minn,inf,sizeof(minn));
for(ll i=1;i<=k;i++)
{
    cin >> a[i];
    maxn[a[i]] = max(maxn[a[i]],i);
    minn[a[i]] = min(minn[a[i]],i);
}	
ll ans = 0;
for(int i=1;i<=n;i++)
{
    if(i<1||i>n)
        continue;
    if(minn[i] > maxn[i-1]&&i>1)
        ans++;
    if(minn[i] > maxn[i+1]&&i<n)
        ans++;
    if(minn[i] > maxn[i])
        ans++;
}
```
核心实现思想：先预处理每个格子第一次和最后一次被询问的时间，然后枚举每个格子，判断左移、不动、右移三种操作是否可行，将可行的情况累加进答案。

---
处理用时：38.94秒