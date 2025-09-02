# 题目信息

# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9```

### 输出

```
10
3
1```

# AI分析结果

### 题目翻译
# 网格上的GCD

## 题目描述

不久前，Egor学习了用于求两个数的最大公约数的欧几里得算法。两个数 $a$ 和 $b$ 的最大公约数是能同时整除 $a$ 和 $b$ 的最大数。有了这个知识，Egor可以解决他曾经无法解决的问题。

Vasily有一个 $n$ 行 $m$ 列的网格，整数 $ {a_i}_j $ 位于第 $i$ 行和第 $j$ 列的交点处。Egor想从左上角（第1行第1列的交点）走到右下角（第$n$行第$m$列的交点），并找到路径上所有数的最大公约数。他只能向下或向右移动。Egor写下了几条路径，得到了不同的GCD值。他对找到最大可能的GCD值产生了兴趣。

不幸的是，Egor已经厌倦了计算GCD，所以他请求你帮助他找到从网格左上角到右下角的路径上整数的最大GCD。

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9```

### 输出

```
10
3
1```

### 题解分析与结论

#### 综合分析
1. **思路共性**：所有题解都基于枚举可能的GCD值，并通过动态规划（DP）或广度优先搜索（BFS）来验证是否存在一条路径，使得路径上的所有数都能被该GCD值整除。
2. **优化点**：大部分题解通过枚举起点和终点的GCD的因数来减少枚举范围，从而优化时间复杂度。
3. **难点**：主要难点在于如何高效地验证路径的存在性，以及如何避免重复计算和优化时间复杂度。

#### 最优关键思路
- **枚举因数**：通过枚举起点和终点的GCD的因数，减少枚举范围。
- **动态规划验证**：使用DP或BFS来验证是否存在一条路径，使得路径上的所有数都能被当前枚举的GCD值整除。

#### 推荐题解
1. **作者：菲斯斯夫斯基 (赞：7)**
   - **星级**：5星
   - **关键亮点**：思路清晰，代码简洁，通过枚举因数并使用DP验证路径，时间复杂度优化较好。
   - **代码核心**：
     ```cpp
     bool check(int k) {
         for(int i=1;i<=n;i++)
             for(int j=1;j<=m;j++)
                 dp[i][j]=0;
         dp[1][1]=1;
         for(int i=1;i<=n;i++)
             for(int j=1;j<=m;j++)
                 if((i!=1||j!=1)&&a[i][j]%k==0)dp[i][j]=dp[i-1][j]|dp[i][j-1];
         return dp[n][m];
     }
     ```

2. **作者：Wyy_w123 (赞：2)**
   - **星级**：4星
   - **关键亮点**：通过枚举GCD的因数，并使用DP验证路径，思路清晰，代码可读性较好。
   - **代码核心**：
     ```cpp
     bool B(int x){
         for(int i = 1; i <= n; i++){
             dp[i][1] = dp[i - 1][1] & !(a[i][1] % x);
         }
         for(int i = 1; i <= m; i++){
             dp[1][i] = dp[1][i - 1] & !(a[1][i] % x);
         }
         for(int i = 2; i <= n; i++){
             for(int j = 2; j <= m; j++){
                 dp[i][j] = a[i][j] % x == 0 ? dp[i - 1][j] | dp[i][j - 1] : 0;
             }
         }
         return dp[n][m];
     }
     ```

3. **作者：__HHX__ (赞：2)**
   - **星级**：4星
   - **关键亮点**：通过枚举因数并使用DP验证路径，代码结构清晰，时间复杂度优化较好。
   - **代码核心**：
     ```cpp
     bool check(int x) {
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= m; j++) {
                 dp[i][j] = 0;
             }
         }
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= m; j++) {
                 if (a[i][j] % x == 0) dp[i][j] = (dp[i][j - 1] | dp[i - 1][j]);
             }
         }
         return dp[n][m];
     }
     ```

### 拓展与推荐题目
1. **洛谷P1020 导弹拦截**：考察动态规划与贪心算法的结合。
2. **洛谷P1048 采药**：经典的背包问题，考察动态规划的应用。
3. **洛谷P1057 传球游戏**：考察动态规划在路径问题中的应用。

### 个人心得摘录
- **作者：210101zhaosicheng**：在调试过程中发现局部变量定义错误导致程序无法正常运行，提醒大家在定义变量时要注意作用域。
- **作者：OIer_Hhy**：通过优化状态转移方程和减少重复计算，最终通过了题目，强调了优化的重要性。

---
处理用时：50.00秒