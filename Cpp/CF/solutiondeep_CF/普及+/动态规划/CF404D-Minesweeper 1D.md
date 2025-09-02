# 题目信息

# Minesweeper 1D

## 题目描述

Game "Minesweeper 1D" is played on a line of squares, the line's height is 1 square, the line's width is $ n $ squares. Some of the squares contain bombs. If a square doesn't contain a bomb, then it contains a number from 0 to 2 — the total number of bombs in adjacent squares.

For example, the correct field to play looks like that: 001\*2\*\*\*101\*. The cells that are marked with "\*" contain bombs. Note that on the correct field the numbers represent the number of bombs in adjacent cells. For example, field 2\* is not correct, because cell with value 2 must have two adjacent cells with bombs.

Valera wants to make a correct field to play "Minesweeper 1D". He has already painted a squared field with width of $ n $ cells, put several bombs on the field and wrote numbers into some cells. Now he wonders how many ways to fill the remaining cells with bombs and numbers are there if we should get a correct field in the end.

## 说明/提示

In the first test sample you can get the following correct fields: 001\*\*1, 001\*\*\*, 001\*2\*, 001\*10.

## 样例 #1

### 输入

```
?01???
```

### 输出

```
4
```

## 样例 #2

### 输入

```
?
```

### 输出

```
2
```

## 样例 #3

### 输入

```
**12
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

游戏“一维扫雷”是在一行方格上进行的，行的高度为1个方格，宽度为$n$个方格。某些方格中包含炸弹。如果一个方格不包含炸弹，则它包含一个从0到2的数字，表示相邻方格中的炸弹总数。

例如，一个合法的游戏场地可能如下：`001*2***101*`。标记为`*`的方格包含炸弹。注意，在合法的场地中，数字表示相邻方格中的炸弹数量。例如，场地`2*`是不合法的，因为值为2的方格必须有两个相邻的方格包含炸弹。

Valera想要制作一个合法的“一维扫雷”游戏场地。他已经绘制了一个宽度为$n$个方格的场地，放置了几个炸弹，并在某些方格中写入了数字。现在他想知道，如果最终要得到一个合法的场地，填充剩余方格的方式有多少种。

#### 说明/提示

在第一个测试样例中，你可以得到以下合法的场地：`001**1`, `001***`, `001*2*`, `001*10`。

#### 样例 #1

##### 输入

```
?01???
```

##### 输出

```
4
```

#### 样例 #2

##### 输入

```
?
```

##### 输出

```
2
```

#### 样例 #3

##### 输入

```
**12
```

##### 输出

```
0
```

#### 样例 #4

##### 输入

```
1
```

##### 输出

```
0
```

---

### 题解综合分析与结论

本题的核心是通过动态规划（DP）来计算合法场地的方案数。大多数题解都采用了DP的思路，但在状态定义和转移方程上有所不同。以下是对各题解的对比与总结：

1. **状态定义**：大多数题解将状态定义为当前方格是否为炸弹，以及其相邻方格的状态。例如，`f[i][0]`表示第`i`个方格不是炸弹，且其相邻方格没有炸弹；`f[i][1]`表示第`i`个方格不是炸弹，但其相邻方格有一个炸弹等。

2. **转移方程**：根据当前方格的状态（数字、炸弹或问号），题解们设计了不同的转移方程。例如，如果当前方格为`0`，则其相邻方格不能有炸弹，因此只能从`f[i-1][0]`转移过来。

3. **优化**：部分题解通过滚动数组优化了空间复杂度，将二维DP数组压缩为一维，进一步减少了内存使用。

4. **初始化**：大多数题解在初始化时将`f[0][0]`和`f[0][1]`设为1，表示初始状态的可能性。

5. **复杂度**：所有题解的时间复杂度均为$O(n)$，空间复杂度为$O(n)$或$O(1)$（通过滚动数组优化）。

### 评分较高的题解

#### 题解1：Star_Cried (评分：5星)

**关键亮点**：
- 使用了滚动数组优化空间复杂度，将空间复杂度降低到$O(1)$。
- 状态定义简洁明了，转移方程清晰。
- 代码实现简洁，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(s[i]=='0') f[i][0] = f[i-1][0];
    else if(s[i]=='1') {
        f[i][1] = f[i-1][0];
        f[i][0] = f[i-1][2];
    }
    else if(s[i]=='2') f[i][1] = f[i-1][2];
    else if(s[i]=='*') f[i][2] = f[i-1][1] + f[i-1][2];
    else if(s[i]=='?') {
        f[i][0] = f[i-1][0] + f[i-1][2];
        f[i][1] = f[i-1][0] + f[i-1][2];
        f[i][2] = f[i-1][1] + f[i-1][2];
    }
}
```

#### 题解2：交警 (评分：4星)

**关键亮点**：
- 状态定义详细，涵盖了所有可能的情况。
- 转移方程全面，考虑了所有可能的字符状态。
- 代码实现较为复杂，但逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(s[i]=='0') dp[i][1] = (dp[i-1][3] + dp[i-1][1]) % mod;
    else if(s[i]=='1') {
        dp[i][3] = dp[i-1][0];
        dp[i][2] = (dp[i-1][1] + dp[i-1][3]) % mod;
    }
    else if(s[i]=='2') dp[i][4] = dp[i-1][0];
    else if(s[i]=='*') dp[i][0] = ( (dp[i-1][2] + dp[i-1][4]) % mod + dp[i-1][0] ) % mod;
    else if(s[i]=='?') {
        dp[i][0] = ( (dp[i-1][2] + dp[i-1][4]) % mod + dp[i-1][0] ) % mod;
        dp[i][1] = (dp[i-1][1] + dp[i-1][3]) % mod;
        dp[i][2] = (dp[i-1][1] + dp[i-1][3]) % mod;
        dp[i][3] = dp[i-1][0];
        dp[i][4] = dp[i-1][0];
    }
}
```

#### 题解3：Louis_lxy (评分：4星)

**关键亮点**：
- 状态定义简洁，转移方程清晰。
- 代码实现简洁，易于理解。
- 使用了滚动数组优化空间复杂度。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(s[i]=='0') f[i][0] = f[i-1][0] + f[i-1][2];
    else if(s[i]=='1') {
        f[i][2] = f[i-1][4];
        f[i][3] = f[i-1][0] + f[i-1][2];
    }
    else if(s[i]=='2') f[i][1] = f[i-1][4];
    else if(s[i]=='*') f[i][4] = f[i-1][1] + f[i-1][3] + f[i-1][4];
    else if(s[i]=='?') {
        f[i][0] = f[i-1][0] + f[i-1][2];
        f[i][1] = f[i-1][4];
        f[i][2] = f[i-1][4];
        f[i][3] = f[i-1][0] + f[i-1][2];
        f[i][4] = f[i-1][1] + f[i-1][3] + f[i-1][4];
    }
}
```

### 最优关键思路与技巧

1. **状态定义**：通过定义当前方格及其相邻方格的状态，可以有效地进行状态转移。
2. **滚动数组优化**：通过滚动数组将空间复杂度从$O(n)$降低到$O(1)$，适用于大规模数据。
3. **转移方程设计**：根据当前方格的状态（数字、炸弹或问号），设计合理的转移方程，确保所有可能的情况都被覆盖。

### 可拓展之处

本题的DP思路可以扩展到类似的序列问题，尤其是那些需要考虑相邻元素状态的问题。例如，字符串匹配、序列生成等问题都可以采用类似的DP思路。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 经典的背包问题，考察DP的基本应用。
2. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057) - 考察序列DP，需要考虑相邻状态。
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064) - 考察多维DP，需要考虑多个状态变量。

### 个人心得摘录

- **调试经历**：在调试过程中，发现初始化状态非常重要，尤其是`f[0][0]`和`f[0][1]`的设置，直接影响到后续的状态转移。
- **踩坑教训**：在设计转移方程时，容易遗漏某些情况，特别是在处理`?`字符时，需要确保所有可能的转移都被覆盖。
- **顿悟感想**：通过滚动数组优化空间复杂度，不仅减少了内存使用，还提高了代码的执行效率，尤其是在处理大规模数据时。

---
处理用时：66.65秒