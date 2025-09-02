# 题目信息

# Geo Game

## 题目描述

This is an interactive problem.

Theofanis and his sister are playing the following game.

They have $ n $ points in a 2D plane and a starting point $ (s_x,s_y) $ . Each player (starting from the first player) chooses one of the $ n $ points that wasn't chosen before and adds to the sum (which is initially $ 0 $ ) the square of the [Euclidean distance](https://en.wikipedia.org/wiki/Euclidean_distance) from the previous point (which is either the starting point or it was chosen by the other person) to the new point (that the current player selected).

The game ends after exactly $ n $ moves (after all the points are chosen). The first player wins if the sum is even in the end. Otherwise, the second player wins.

Theofanis is a very competitive person and he hates losing. Thus, he wants to choose whether he should play first or second. Can you show him, which player to choose, and how he should play to beat his sister?

## 说明/提示

The examples above do not necessarily showcase optimal strategies or the correct player to choose.

In the picture below, you can see the moves that each player made in the first example. The first player is red, and the second player is black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1903E/f7249992dc1dd05fd5ad17cee8e62de0afd41f95.png)

## 样例 #1

### 输入

```
2
6
4 6
7 6
8 5
2 1
6 2
6 4
3 3

2

5

1
4
1 1
3 2
2 1
3 3
1 2


2

3```

### 输出

```
Second

4

6

3
First
1

4```

# AI分析结果

【题目内容】
# Geo Game

## 题目描述

这是一个交互题。

Theofanis 和他的妹妹在玩一个游戏。

他们在二维平面上有 $n$ 个点和一个起点 $(s_x,s_y)$。每个玩家（从第一个玩家开始）选择一个之前未被选过的点，并将从上一个点（起点或对方选择的点）到新点（当前玩家选择的点）的欧几里得距离的平方加到总和上（初始为 $0$）。

游戏在恰好 $n$ 步后结束（所有点都被选择）。如果最终总和为偶数，则第一个玩家获胜；否则，第二个玩家获胜。

Theofanis 非常争强好胜，他讨厌输。因此，他想选择自己是先手还是后手。你能告诉他应该选择哪个玩家，以及如何击败他的妹妹吗？

## 说明/提示

上述示例并不一定展示最优策略或正确的玩家选择。

在下图中，你可以看到第一个示例中每个玩家的移动。第一个玩家是红色，第二个玩家是黑色。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1903E/f7249992dc1dd05fd5ad17cee8e62de0afd41f95.png)

## 样例 #1

### 输入

```
2
6
4 6
7 6
8 5
2 1
6 2
6 4
3 3

2

5

1
4
1 1
3 2
2 1
3 3
1 2


2

3```

### 输出

```
Second

4

6

3
First
1

4```

【算法分类】数学

【题解分析与结论】
该题的核心在于通过数学分析简化问题，最终归结为对点的奇偶性分类和博弈策略的选择。所有题解都抓住了问题的本质，即最终结果的奇偶性只与起点和终点的坐标和的奇偶性有关。通过将点分为两类（与起点奇偶性相同或不同），并根据两类的数量决定先手或后手的选择，可以确保胜利。

【精选题解】

1. **作者：FFTotoro (5星)**
   - **关键亮点**：通过数学推导将问题简化为对点的奇偶性分类，并给出了清晰的策略选择方法。代码实现简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     auto f=[&](int x){
       if(s[x].empty())x=!x;
       cout<<*s[x].begin()<<endl;
       s[x].erase(s[x].begin());
     };
     auto g=[&](){
       int x; cin>>x;
       if(s[0].find(x)!=s[0].end())s[0].erase(x);
       else s[1].erase(x);
     };
     ```
   - **个人心得**：通过数学推导简化问题，避免复杂的模拟过程，直接抓住问题的核心。

2. **作者：蒟蒻君HJT (4星)**
   - **关键亮点**：通过分类讨论和归纳法，给出了先手和后手的必胜条件，思路清晰，易于理解。
   - **核心代码**：
     ```cpp
     if(c_0>=c_1) puts("First");
     else puts("Second");
     ```
   - **个人心得**：通过简单的分类讨论，直接得出胜负条件，避免了复杂的博弈分析。

3. **作者：mountain_climber (4星)**
   - **关键亮点**：通过数学公式推导，将问题简化为对终点奇偶性的判断，并给出了明确的策略选择方法。
   - **核心代码**：
     ```cpp
     if(c_1>=c_2) puts("First");
     else puts("Second");
     ```
   - **个人心得**：通过数学推导，将复杂的博弈问题简化为简单的奇偶性判断，思路清晰。

【最优关键思路】
将点的坐标和的奇偶性作为分类依据，根据与起点奇偶性相同或不同的点的数量决定先手或后手的选择。通过这种策略，可以确保最终结果的奇偶性符合预期，从而获胜。

【拓展思路】
类似的问题可以通过数学分析简化，尤其是在涉及奇偶性、模运算等数学性质时，可以通过分类讨论和归纳法找到解决方案。

【推荐题目】
1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：42.24秒