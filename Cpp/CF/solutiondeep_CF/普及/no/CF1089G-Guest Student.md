# 题目信息

# Guest Student

## 题目描述

Berland State University invites people from all over the world as guest students. You can come to the capital of Berland and study with the best teachers in the country.

Berland State University works every day of the week, but classes for guest students are held on the following schedule. You know the sequence of seven integers $ a_1, a_2, \dots, a_7 $ ( $ a_i = 0 $ or $ a_i = 1 $ ):

- $ a_1=1 $ if and only if there are classes for guest students on Sundays;
- $ a_2=1 $ if and only if there are classes for guest students on Mondays;
- ...
- $ a_7=1 $ if and only if there are classes for guest students on Saturdays.

The classes for guest students are held in at least one day of a week.

You want to visit the capital of Berland and spend the minimum number of days in it to study $ k $ days as a guest student in Berland State University. Write a program to find the length of the shortest continuous period of days to stay in the capital to study exactly $ k $ days as a guest student.

## 说明/提示

In the first test case you must arrive to the capital of Berland on Monday, have classes on this day, spend a week until next Monday and have classes on the next Monday. In total you need to spend $ 8 $ days in the capital of Berland.

## 样例 #1

### 输入

```
3
2
0 1 0 0 0 0 0
100000000
1 0 0 0 1 0 1
1
1 0 0 0 0 0 0
```

### 输出

```
8
233333332
1
```

# AI分析结果

### 题目内容重写

#### 题目描述

Berland State University 邀请来自世界各地的人作为客座学生。你可以来到 Berland 的首都，与全国最好的教师一起学习。

Berland State University 每周每天都开放，但客座学生的课程安排如下。你知道一个包含七个整数 $a_1, a_2, \dots, a_7$（$a_i = 0$ 或 $a_i = 1$）的序列：

- $a_1=1$ 当且仅当客座学生在周日有课程；
- $a_2=1$ 当且仅当客座学生在周一有课程；
- ...
- $a_7=1$ 当且仅当客座学生在周六有课程。

客座学生的课程每周至少有一天进行。

你希望访问 Berland 的首都，并在其中停留最少的天数，以在 Berland State University 作为客座学生学习 $k$ 天。编写一个程序，找出在首都停留的最短连续天数，以便恰好学习 $k$ 天。

#### 说明/提示

在第一个测试用例中，你必须在周一到达 Berland 的首都，并在这一天上课，然后在下周一之前度过一周，并在下周一再次上课。总共你需要在首都停留 $8$ 天。

#### 样例 #1

##### 输入

```
3
2
0 1 0 0 0 0 0
100000000
1 0 0 0 1 0 1
1
1 0 0 0 0 0 0
```

##### 输出

```
8
233333332
1
```

### 算法分类
模拟

### 题解分析与结论

#### 题解1：Yamchip (3星)
- **思路**：暴力模拟，从每个有课的那一天开始模拟，先计算整数周，再枚举剩余天数，最后统计最小值。
- **难点**：代码逻辑较为复杂，容易出错。
- **评分**：3星，思路直接但代码实现较为繁琐。

#### 题解2：Harrylzh (4星)
- **思路**：将问题看作一个环，任意选一个开始点，顺时针方向走，使得刚好经过 $k$ 个黑点，求最小的总经过点数。
- **难点**：环的处理和黑点之间的距离计算。
- **评分**：4星，思路清晰，代码简洁，优化了时间复杂度。

#### 题解3：pyz51 (4星)
- **思路**：先计算整数周，再枚举最后一周的开头，取最小值。
- **难点**：最后一周的开头枚举和最小值的计算。
- **评分**：4星，思路清晰，代码简洁，优化了时间复杂度。

### 最优关键思路或技巧
- **环的处理**：将一周的课程安排看作一个环，方便计算任意开始点的最短路径。
- **整数周计算**：先计算整数周的天数，再处理剩余的天数，减少计算量。
- **枚举开头**：枚举最后一周的开头，取最小值，确保结果最优。

### 可拓展之处
- **类似问题**：可以扩展到其他周期性安排的问题，如工作排班、课程安排等。
- **优化思路**：通过预处理黑点之间的距离，减少枚举的次数，提高效率。

### 推荐题目
1. [P1089 Guest Student](https://www.luogu.com.cn/problem/CF1089G)
2. [P1090 课程安排](https://www.luogu.com.cn/problem/P1090)
3. [P1091 工作排班](https://www.luogu.com.cn/problem/P1091)

### 个人心得
- **调试经历**：在处理环时，需要特别注意边界条件，避免数组越界。
- **踩坑教训**：在计算剩余天数时，容易忽略最后一周的补全，导致结果错误。
- **顿悟感想**：通过将问题抽象为环，可以简化计算，提高代码的可读性和效率。

---
处理用时：31.65秒