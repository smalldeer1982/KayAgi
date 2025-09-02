# 题目信息

# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly enrolled in the course Advanced Useless Algorithms. The course consists of $ n $ tasks. Vitaly calculated that he has $ a_i $ hours to do the task $ i $ from the day he enrolled in the course. That is, the deadline before the $ i $ -th task is $ a_i $ hours. The array $ a $ is sorted in ascending order, in other words, the job numbers correspond to the order in which the assignments are turned in.

Vitaly does everything conscientiously, so he wants to complete each task by $ 100 $ percent, or more. Initially, his completion rate for each task is $ 0 $ percent.

Vitaly has $ m $ training options, each option can be used not more than once. The $ i $ th option is characterized by three integers: $ e_i, t_i $ and $ p_i $ . If Vitaly uses the $ i $ th option, then after $ t_i $ hours (from the current moment) he will increase the progress of the task $ e_i $ by $ p_i $ percent.

For example, let Vitaly have $ 3 $ of tasks to complete. Let the array $ a $ have the form: $ a = [5, 7, 8] $ . Suppose Vitaly has $ 5 $ of options: $ [e_1=1, t_1=1, p_1=30] $ , $ [e_2=2, t_2=3, p_2=50] $ , $ [e_3=2, t_3=3, p_3=100] $ , $ [e_4=1, t_4=1, p_4=80] $ , $ [e_5=3, t_5=3, p_5=100] $ .

Then, if Vitaly prepares in the following way, he will be able to complete everything in time:

- Vitaly chooses the $ 4 $ -th option. Then in $ 1 $ hour, he will complete the $ 1 $ -st task at $ 80 $ percent. He still has $ 4 $ hours left before the deadline for the $ 1 $ -st task.
- Vitaly chooses the $ 3 $ -rd option. Then in $ 3 $ hours, he will complete the $ 2 $ -nd task in its entirety. He has another $ 1 $ hour left before the deadline for the $ 1 $ -st task and $ 4 $ hours left before the deadline for the $ 3 $ -rd task.
- Vitaly chooses the $ 1 $ -st option. Then after $ 1 $ hour, he will complete the $ 1 $ -st task for $ 110 $ percent, which means that he will complete the $ 1 $ -st task just in time for the deadline.
- Vitaly chooses the $ 5 $ -th option. He will complete the $ 3 $ -rd task for $ 2 $ hours, and after another $ 1 $ hour, Vitaly will complete the $ 3 $ -rd task in its entirety.

Thus, Vitaly has managed to complete the course completely and on time, using the $ 4 $ options.

Help Vitaly — print the options for Vitaly to complete the tasks in the correct order. Please note: each option can be used not more than once. If there are several possible answers, it is allowed to output any of them.

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100```

### 输出

```
-1
4
3 4 1 5 
1
1```

# AI分析结果

### 题目内容重写

# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly 报名参加了“高级无用算法”课程。该课程包含 $n$ 个任务。Vitaly 计算出，从报名之日起，他需要在 $a_i$ 小时内完成第 $i$ 个任务。也就是说，第 $i$ 个任务的截止时间是 $a_i$ 小时。数组 $a$ 是按升序排列的，换句话说，任务的编号与任务的提交顺序相对应。

Vitaly 做事非常认真，因此他希望每个任务都能完成 $100\%$ 或更多。最初，他对每个任务的完成进度都是 $0\%$。

Vitaly 有 $m$ 个训练选项，每个选项最多只能使用一次。第 $i$ 个选项由三个整数描述：$e_i, t_i$ 和 $p_i$。如果 Vitaly 使用了第 $i$ 个选项，那么在 $t_i$ 小时后（从当前时刻开始），他会将任务 $e_i$ 的进度增加 $p_i\%$。

例如，假设 Vitaly 有 $3$ 个任务需要完成。数组 $a$ 为：$a = [5, 7, 8]$。假设 Vitaly 有 $5$ 个选项：$[e_1=1, t_1=1, p_1=30]$，$[e_2=2, t_2=3, p_2=50]$，$[e_3=2, t_3=3, p_3=100]$，$[e_4=1, t_4=1, p_4=80]$，$[e_5=3, t_5=3, p_5=100]$。

那么，如果 Vitaly 按照以下方式准备，他将能够按时完成所有任务：

- Vitaly 选择第 $4$ 个选项。然后在 $1$ 小时后，他将完成第 $1$ 个任务的 $80\%$。此时，距离第 $1$ 个任务的截止时间还有 $4$ 小时。
- Vitaly 选择第 $3$ 个选项。然后在 $3$ 小时后，他将完全完成第 $2$ 个任务。此时，距离第 $1$ 个任务的截止时间还有 $1$ 小时，距离第 $3$ 个任务的截止时间还有 $4$ 小时。
- Vitaly 选择第 $1$ 个选项。然后在 $1$ 小时后，他将完成第 $1$ 个任务的 $110\%$，这意味着他将在截止时间前完成第 $1$ 个任务。
- Vitaly 选择第 $5$ 个选项。他将在 $2$ 小时后完成第 $3$ 个任务，然后在另外 $1$ 小时后，Vitaly 将完全完成第 $3$ 个任务。

因此，Vitaly 成功按时完成了所有课程任务，使用了 $4$ 个选项。

请帮助 Vitaly —— 输出 Vitaly 完成任务所需的选项的正确顺序。请注意：每个选项最多只能使用一次。如果有多个可能的答案，输出其中任意一个即可。

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100```

### 输出

```
-1
4
3 4 1 5 
1
1```

### 综合分析与结论

该题目要求为每个任务选择一系列训练选项，使得每个任务都能在截止时间前完成，并且每个选项只能使用一次。这是一个典型的动态规划问题，结合了背包问题的思路。每个任务的完成进度可以看作背包的容量，而每个选项的时间和进度增加可以看作物品的重量和价值。

### 所选高分题解

#### 1. 作者：落海沉 (5星)
- **关键亮点**：该题解清晰地分析了背包问题的两种可能思路，并选择了以百分比为容量、时间为价值的方案。通过证明百分比的上限为199，简化了问题。代码实现简洁，使用了二维DP数组，并记录了路径。
- **核心代码**：
  ```cpp
  for(int j=rgt; j>=lft; j--) {
      for(int k=200; k; k--) {
          dp[j][k]=dp[j+1][k];
          if(k>=e[j].val)dp[j][k]=min(dp[j+1][k-e[j].val]+e[j].ti,dp[j][k]);
      }
  }
  ```

#### 2. 作者：qianqing (4星)
- **关键亮点**：该题解同样采用了背包问题的思路，但使用了滚动数组优化空间复杂度。通过记录路径，能够输出具体的选项顺序。代码结构清晰，易于理解。
- **核心代码**：
  ```cpp
  for(int j=0;j<p[x].size();j++) {
      auto [e, t, p] = plans[j];
      for(int k=200; k>=0; k--) {
          if(k>=p && dp[k-p]+t<dp[k]) {
              dp[k]=dp[k-p]+t;
              f[j][k]=1;
          }
      }
  }
  ```

#### 3. 作者：SUNCHAOYI (4星)
- **关键亮点**：该题解强调了贪心策略，优先完成截止时间早的任务。通过二维DP数组记录每个任务的最小完成时间，并输出方案。代码实现较为简洁，逻辑清晰。
- **核心代码**：
  ```cpp
  for(int i=1;i<=k;++i) {
      node nw = e[x][i - 1];
      for(int j=100;~j;--j)
          dp[i][j] = min(dp[i][j],dp[i - 1][max(0,j - nw.p)] + nw.t);
  }
  ```

### 最优关键思路与技巧

1. **背包问题思路**：将每个任务的完成进度视为背包的容量，每个选项的时间和进度增加视为物品的重量和价值，通过动态规划求解最小时间。
2. **滚动数组优化**：在DP过程中使用滚动数组优化空间复杂度，减少内存使用。
3. **路径记录**：在DP过程中记录路径，以便输出具体的选项顺序。

### 可拓展之处

该题目可以拓展到多个任务的并行处理，或者引入更多的约束条件（如选项的使用次数限制）。类似的问题可以结合贪心算法、动态规划等多种算法进行求解。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

### 个人心得总结

- **调试经历**：在DP过程中，初始化数组和边界条件的处理非常重要，稍有不慎就会导致错误。
- **踩坑教训**：在使用滚动数组时，要注意数组的更新顺序，避免覆盖未使用的数据。
- **顿悟感想**：通过将问题转化为背包问题，可以大大简化问题的复杂度，提高解题效率。

---
处理用时：68.84秒