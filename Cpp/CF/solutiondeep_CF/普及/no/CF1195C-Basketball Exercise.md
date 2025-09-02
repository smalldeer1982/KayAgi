# 题目信息

# Basketball Exercise

## 题目描述

Finally, a basketball court has been opened in SIS, so Demid has decided to hold a basketball exercise session. $ 2 \cdot n $ students have come to Demid's exercise session, and he lined up them into two rows of the same size (there are exactly $ n $ people in each row). Students are numbered from $ 1 $ to $ n $ in each row in order from left to right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/05855164ffa55108436f13cfefdb8a460d04c2d7.png)Now Demid wants to choose a team to play basketball. He will choose players from left to right, and the index of each chosen player (excluding the first one) will be strictly greater than the index of the previously chosen player. To avoid giving preference to one of the rows, Demid chooses students in such a way that no consecutive chosen students belong to the same row. The first student can be chosen among all $ 2n $ students (there are no additional constraints), and a team can consist of any number of students.

Demid thinks, that in order to compose a perfect team, he should choose students in such a way, that the total height of all chosen students is maximum possible. Help Demid to find the maximum possible total height of players in a team he can choose.

## 说明/提示

In the first example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/9a3e2230ef98dd0879303ff329fc9cb7b1cf5209.png)In the second example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/c3c20000e8e493da34f3e2b1ef145d407e671b29.png)

## 样例 #1

### 输入

```
5
9 3 5 7 3
5 8 1 4 5
```

### 输出

```
29
```

## 样例 #2

### 输入

```
3
1 2 9
10 1 1
```

### 输出

```
19
```

## 样例 #3

### 输入

```
1
7
4
```

### 输出

```
7
```

# AI分析结果

【题目内容】
# 篮球训练

## 题目描述

终于，SIS学校开放了一个篮球场，因此Demid决定组织一场篮球训练。$ 2 \cdot n $名学生来到了Demid的训练课，他将他们排成两排，每排有$ n $个人。学生在每排中从左到右依次编号为$ 1 $到$ n $。

现在Demid想选出一支篮球队。他将从左到右选择球员，每个被选中的球员的编号（除了第一个）必须严格大于前一个被选中的球员的编号。为了避免对某一排的偏好，Demid选择学生的方式是：连续被选中的学生不能来自同一排。第一个学生可以从所有$ 2n $名学生中任意选择，球队可以由任意数量的学生组成。

Demid认为，为了组成一支完美的球队，他应该以被选中的学生的总身高最大为目标。请帮助Demid找到他能选择的球队中球员总身高的最大值。

## 说明/提示

在第一个例子中，Demid可以按照以下方式选择球队：

在第二个例子中，Demid可以按照以下方式选择球队：

## 样例 #1

### 输入

```
5
9 3 5 7 3
5 8 1 4 5
```

### 输出

```
29
```

## 样例 #2

### 输入

```
3
1 2 9
10 1 1
```

### 输出

```
19
```

## 样例 #3

### 输入

```
1
7
4
```

### 输出

```
7
```

【算法分类】
动态规划

【题解分析与结论】
本题的核心是通过动态规划来解决选择球员的问题，确保连续选择的球员不在同一排，并且总身高最大。大多数题解都采用了类似的状态定义和转移方程，区别在于状态表示的细节和优化方式。

【评分较高的题解】
1. **作者：tth37 (5星)**
   - **关键亮点**：状态定义清晰，转移方程简洁明了，代码可读性强。通过贪心思想优化了状态转移，避免了不必要的计算。
   - **代码核心**：
     ```cpp
     for (register int i = 2; i <= N; ++i) {
         f[i][0] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2]));
         f[i][1] = max(f[i - 1][0], f[i - 1][2]) + h[i][1];
         f[i][2] = max(f[i - 1][0], f[i - 1][1]) + h[i][2];
     }
     ```

2. **作者：AC_Dolphin (4星)**
   - **关键亮点**：通过引入`cnt1`和`cnt2`变量优化了状态转移，避免了每次查找最大值的时间开销，提升了效率。
   - **代码核心**：
     ```cpp
     for(int i=2;i<=n;i++) {
         dp[i][1]=cnt2+a[i];
         dp[i][2]=cnt1+b[i];
         cnt1=max(cnt1,dp[i][1]);
         cnt2=max(cnt2,dp[i][2]);
     }
     ```

3. **作者：gesong (4星)**
   - **关键亮点**：状态定义清晰，转移方程简洁，代码结构良好。通过直接的状态转移方程实现了问题的解决。
   - **代码核心**：
     ```cpp
     for (int i=2;i<=n;i++) {
         f[i][0]=max(max(f[i-1][0],f[i-1][1]),f[i-1][2]);
         f[i][1]=max(f[i-1][0],f[i-1][2])+a[i];
         f[i][2]=max(f[i-1][0],f[i-1][1])+b[i];
     }
     ```

【最优关键思路或技巧】
- **状态定义**：使用`f[i][0/1/2]`表示第`i`列不选、选第一排、选第二排的最大身高和。
- **状态转移**：通过前一列的状态来决定当前列的选择，确保连续选择的球员不在同一排。
- **优化**：通过贪心思想或引入变量优化状态转移，减少不必要的计算。

【可拓展之处】
- 类似的问题可以扩展到多排选择，或者增加其他约束条件（如身高差限制）。
- 可以结合其他算法（如贪心、搜索）来进一步优化选择策略。

【推荐题目】
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 动态规划经典问题，类似于背包问题。
2. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064) - 动态规划与条件约束的结合。
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 动态规划与序列选择的结合。

【个人心得】
- **调试经历**：在实现状态转移时，确保连续选择的球员不在同一排是关键，容易忽略这一点导致错误。
- **顿悟感想**：通过引入变量优化状态转移，可以显著提升算法的效率，避免重复计算。

---
处理用时：39.16秒