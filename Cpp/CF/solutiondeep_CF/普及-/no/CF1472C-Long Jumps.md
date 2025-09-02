# 题目信息

# Long Jumps

## 题目描述

Polycarp found under the Christmas tree an array $ a $ of $ n $ elements and instructions for playing with it:

- At first, choose index $ i $ ( $ 1 \leq i \leq n $ ) — starting position in the array. Put the chip at the index $ i $ (on the value $ a_i $ ).
- While $ i \leq n $ , add $ a_i $ to your score and move the chip $ a_i $ positions to the right (i.e. replace $ i $ with $ i + a_i $ ).
- If $ i > n $ , then Polycarp ends the game.

For example, if $ n = 5 $ and $ a = [7, 3, 1, 2, 3] $ , then the following game options are possible:

- Polycarp chooses $ i = 1 $ . Game process: $ i = 1 \overset{+7}{\longrightarrow} 8 $ . The score of the game is: $ a_1 = 7 $ .
- Polycarp chooses $ i = 2 $ . Game process: $ i = 2 \overset{+3}{\longrightarrow} 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_2 + a_5 = 6 $ .
- Polycarp chooses $ i = 3 $ . Game process: $ i = 3 \overset{+1}{\longrightarrow} 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_3 + a_4 = 3 $ .
- Polycarp chooses $ i = 4 $ . Game process: $ i = 4 \overset{+2}{\longrightarrow} 6 $ . The score of the game is: $ a_4 = 2 $ .
- Polycarp chooses $ i = 5 $ . Game process: $ i = 5 \overset{+3}{\longrightarrow} 8 $ . The score of the game is: $ a_5 = 3 $ .

Help Polycarp to find out the maximum score he can get if he chooses the starting index in an optimal way.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the maximum score can be achieved by choosing $ i = 1 $ .

In the third test case, the maximum score can be achieved by choosing $ i = 2 $ .

In the fourth test case, the maximum score can be achieved by choosing $ i = 1 $ .

## 样例 #1

### 输入

```
4
5
7 3 1 2 3
3
2 1 4
6
2 1000 2 3 995 1
5
1 1 1 1 1```

### 输出

```
7
6
1000
5```

# AI分析结果

### 题目内容
# 跳远

## 题目描述
Polycarp在圣诞树底下发现了一个包含 $n$ 个元素的数组 $a$ 以及与之相关的玩法说明：
- 首先，选择一个索引 $i$（$1 \leq i \leq n$）—— 这是数组中的起始位置。将筹码放置在索引 $i$ 处（即数值 $a_i$ 上）。
- 当 $i \leq n$ 时，将 $a_i$ 加到你的得分中，并将筹码向右移动 $a_i$ 个位置（即把 $i$ 替换为 $i + a_i$）。
- 如果 $i > n$，那么Polycarp结束游戏。

例如，如果 $n = 5$ 且 $a = [7, 3, 1, 2, 3]$，那么可能的游戏过程如下：
- Polycarp选择 $i = 1$。游戏过程：$i = 1 \overset{+7}{\longrightarrow} 8$。游戏得分是：$a_1 = 7$。
- Polycarp选择 $i = 2$。游戏过程：$i = 2 \overset{+3}{\longrightarrow} 5 \overset{+3}{\longrightarrow} 8$。游戏得分是：$a_2 + a_5 = 6$。
- Polycarp选择 $i = 3$。游戏过程：$i = 3 \overset{+1}{\longrightarrow} 4 \overset{+2}{\longrightarrow} 6$。游戏得分是：$a_3 + a_4 = 3$。
- Polycarp选择 $i = 4$。游戏过程：$i = 4 \overset{+2}{\longrightarrow} 6$。游戏得分是：$a_4 = 2$。
- Polycarp选择 $i = 5$。游戏过程：$i = 5 \overset{+3}{\longrightarrow} 8$。游戏得分是：$a_5 = 3$。

请帮助Polycarp找出如果他以最优方式选择起始索引，他能获得的最大得分。

## 说明/提示
第一个测试用例在题目描述中有解释。

在第二个测试用例中，通过选择 $i = 1$ 可以获得最大得分。

在第三个测试用例中，通过选择 $i = 2$ 可以获得最大得分。

在第四个测试用例中，通过选择 $i = 1$ 可以获得最大得分。

## 样例 #1
### 输入
```
4
5
7 3 1 2 3
3
2 1 4
6
2 1000 2 3 995 1
5
1 1 1 1 1
```
### 输出
```
7
6
1000
5
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕动态规划（部分题解思路也可看作递推，递推可视为动态规划的一种特殊形式）和模拟两种方法。
 - **动态规划思路要点**：多数题解定义 $dp[i]$ 表示从位置 $i$ 出发能获得的最大得分。状态转移方程基本形式为：若 $i + a[i] \leq n$，$dp[i] = a[i] + dp[i + a[i]]$；若 $i + a[i] > n$，$dp[i] = a[i]$。计算时一般从后往前遍历数组，这样能保证在计算当前位置的 $dp$ 值时，后续位置的 $dp$ 值已计算好。
 - **模拟思路要点**：直接按照题目描述进行模拟，从每个位置出发，不断更新位置并累加得分，同时利用记忆化（如标记数组）避免重复计算，最终找出最大得分。
 - **难点**：部分题解使用常规数组定义 $dp$ 数组时可能因 $a[i]$ 范围大导致内存爆炸，如Melon_Musk题解中提到需将 $dp$ 数组改为 $map$ 类型解决此问题。

### 所选的题解
 - **作者：Melon_Musk (5星)**
    - **关键亮点**：清晰指出本题是动态规划题，详细说明状态转移方程的推导，且能敏锐发现常规数组定义 $dp$ 可能导致内存爆炸的问题，并提出用 $map$ 类型解决，代码实现完整。
    - **个人心得**：作者提到直接用数组定义 $dp$ 数组导致运行时错误（RE），经分析是因为 $a[i]$ 范围在 $10^9$，$dp$ 数组直接开数组会内存爆炸，所以改为 $map$ 类型得以通过题目。
    - **重点代码核心实现思想**：利用 $map$ 存储 $dp$ 值，通过遍历数组，根据状态转移方程更新 $map$ 中的值，并不断记录最大值。
    ```cpp
    for(int i=1;i<=n;i++)
    {
        f[i+a[i]]=max(f[i+a[i]],f[i]+a[i]);
        maxx=max(maxx,f[i+a[i]]);
    }
    ```
 - **作者：__shadow__ (4星)**
    - **关键亮点**：提供两种方法，方法一是朴素模拟每个位置出发的得分并打擂找最大（可得部分分），方法二是从后往前求得分，避免不必要重复计算，思路清晰，代码实现详细。
    - **重点代码核心实现思想（方法二）**：从后往前遍历数组，根据当前位置能否跳到数组外，确定当前位置的得分计算方式，最后打擂找出最大得分。
    ```cpp
    for (int i = n;i >= 1; i--)
    {
        if (i + a[i] > n)
            b[i] = a[i];
        else
            b[i] = a[i] + b[i + a[i]];
    }
    long long maxn = b[1];
    for (int i = 2;i <= n; i++)
        maxn = max(maxn, b[i]);
    ```
 - **作者：Parat_rooper (4星)**
    - **关键亮点**：明确指出本题是典型递推问题，类比楼梯问题，清晰阐述收集型递推的思路，代码简洁明了。
    - **重点代码核心实现思想**：从后往前更新路径值，对于能直接走出去的起点，其值为 $a_i$，否则为 $a_i$ 与以（$i + a_i$）为起点的路径值之和，最后找出所有路径值中的最大值。
    ```cpp
    d[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
        d[i] = a[i];
        if (a[i] <= (n - i)) {
            d[i] += d[i + a[i]];
        }
    }
    for (int i = 1; i <= n; i++) {
        maxx = max(maxx, d[i]);
    }
    ```

### 最优关键思路或技巧
 - **动态规划状态定义与转移**：合理定义 $dp$ 状态为从位置 $i$ 出发的最大得分，依据能否跳出数组边界构建状态转移方程，这是解决本题的核心思路。
 - **从后往前计算**：由于后续位置的 $dp$ 值在计算当前位置时需要用到，从后往前遍历数组计算 $dp$ 值可保证数据的有效性和计算的准确性。
 - **处理内存问题**：当 $a[i]$ 范围较大可能导致 $dp$ 数组内存爆炸时，可采用 $map$ 等动态数据结构替代常规数组存储 $dp$ 值。

### 可拓展之处
同类型题通常围绕动态规划的状态定义与转移方程构建，常见场景如路径问题、资源分配问题等。类似算法套路是根据问题的实际情况，合理定义状态表示，分析状态之间的转移关系，构建转移方程，并注意边界条件和计算顺序。

### 洛谷推荐题目
 - [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目，与本题类似在于都需定义合适的状态和状态转移方程来求解最优值，不过场景变为数字三角形中的路径和问题。
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：同样是动态规划问题，涉及棋盘上棋子的移动路径方案数计算，在状态定义和转移方程构建上与本题有相似之处，需要考虑边界条件和状态间的递推关系。
 - [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：通过动态规划求解从每个位置出发能滑过的最大长度，与本题在通过动态规划解决最优解问题上思路相似，都要分析状态转移并处理边界情况。 

---
处理用时：88.82秒