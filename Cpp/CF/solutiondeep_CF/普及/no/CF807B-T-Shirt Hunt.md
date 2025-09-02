# 题目信息

# T-Shirt Hunt

## 题目描述

Not so long ago the Codecraft-17 contest was held on Codeforces. The top 25 participants, and additionally random 25 participants out of those who got into top 500, will receive a Codeforces T-shirt.

Unfortunately, you didn't manage to get into top 25, but you got into top 500, taking place $ p $ .

Now the elimination round of 8VC Venture Cup 2017 is being held. It has been announced that the Codecraft-17 T-shirt winners will be chosen as follows. Let $ s $ be the number of points of the winner of the elimination round of 8VC Venture Cup 2017. Then the following pseudocode will be executed:

`<br></br>i := (s div 50) mod 475<br></br>repeat 25 times:<br></br>    i := (i * 96 + 42) mod 475<br></br>    print (26 + i)<br></br>`Here "div" is the integer division operator, "mod" is the modulo (the remainder of division) operator.

As the result of pseudocode execution, 25 integers between 26 and 500, inclusive, will be printed. These will be the numbers of places of the participants who get the Codecraft-17 T-shirts. It is guaranteed that the 25 printed integers will be pairwise distinct for any value of $ s $ .

You're in the lead of the elimination round of 8VC Venture Cup 2017, having $ x $ points. You believe that having at least $ y $ points in the current round will be enough for victory.

To change your final score, you can make any number of successful and unsuccessful hacks. A successful hack brings you 100 points, an unsuccessful one takes 50 points from you. It's difficult to do successful hacks, though.

You want to win the current round and, at the same time, ensure getting a Codecraft-17 T-shirt. What is the smallest number of successful hacks you have to do to achieve that?

## 说明/提示

In the first example, there is no need to do any hacks since 10880 points already bring the T-shirt to the 239-th place of Codecraft-17 (that is, you). In this case, according to the pseudocode, the T-shirts will be given to the participants at the following places:

`<br></br>475 422 84 411 453 210 157 294 146 188 420 367 29 356 398 155 102 239 91 133 365 312 449 301 343<br></br>`In the second example, you have to do two successful and one unsuccessful hack to make your score equal to 7408.

In the third example, you need to do as many as 24 successful hacks to make your score equal to 10400.

In the fourth example, it's sufficient to do 6 unsuccessful hacks (and no successful ones) to make your score equal to 6500, which is just enough for winning the current round and also getting the T-shirt.

## 样例 #1

### 输入

```
239 10880 9889
```

### 输出

```
0
```

## 样例 #2

### 输入

```
26 7258 6123
```

### 输出

```
2
```

## 样例 #3

### 输入

```
493 8000 8000
```

### 输出

```
24
```

## 样例 #4

### 输入

```
101 6800 6500
```

### 输出

```
0
```

## 样例 #5

### 输入

```
329 19913 19900
```

### 输出

```
8
```

# AI分析结果



# T-Shirt Hunt

## 题目描述

不久前，Codecraft-17 比赛在 Codeforces 上举行。前 25 名以及前 500 名中随机挑选的另外 25 名参与者将获得 Codeforces T 恤。

不幸的是，你未能进入前 25 名，但进入了前 500 名，当前排名为 $ p $。

现在正在进行 8VC Venture Cup 2017 的淘汰赛。公告称 Codecraft-17 的 T 恤获奖者将通过以下方式选出：设 $ s $ 为 8VC Venture Cup 2017 淘汰赛获胜者的分数，执行以下伪代码：

`i := (s div 50) mod 475<br>重复 25 次：<br>    i := (i * 96 + 42) mod 475<br>    输出 (26 + i)`  
其中 "div" 是整数除法运算符，"mod" 是取模运算符。

保证输出的 25 个整数互不相同。你在淘汰赛中领先，当前分数为 $ x $。你相信当前回合至少获得 $ y $ 分即可获胜。

你可以通过成功或失败的 hack 调整分数：成功 hack 加 100 分，失败 hack 减 50 分。求在确保获胜且获得 T 恤的前提下，最少需要多少次成功 hack。

---

**算法分类**：模拟

---

### 题解分析与结论

两篇题解均采用模拟伪随机数生成过程，结合二分查找判断目标名次是否在序列中。核心思路如下：

1. **分数调整约束**：分数变化以 50 为步长（因 100 和 50 的线性组合），从满足 $s \geq y$ 的最小值开始枚举。
2. **名次生成验证**：严格按照题目伪代码生成 25 个名次，排序后二分查找目标 $p$。
3. **贪心计算成功次数**：找到满足条件的最小 $s$ 后，计算通过加 100 分达到该值所需的最少次数。

### 高分题解推荐

1. **封禁用户（4.5星）**
   - **亮点**：逻辑清晰，代码结构规范，包含详细注释。通过逐步调整分数并二分查找名次，确保正确性。
   - **核心代码**：
     ```cpp
     void prize(int s) {
         int tmp = (s / 50) % 475;
         for(int i = 0; i < 25; i++) {
             tmp = (tmp * 96 + 42) % 475;
             a[i] = tmp + 26;
         }
         sort(a, a + 25);
     }
     ```
     - 生成名次序列并排序，便于后续二分查找。

2. **huangjunhan（4星）**
   - **亮点**：代码简洁，变量命名合理。通过函数封装伪代码生成和查找过程，模块化程度高。
   - **核心代码**：
     ```cpp
     while(t < x) {
         ans++;
         t += 100;
     }
     ```
     - 通过循环直接计算所需成功 hack 次数，直观高效。

### 关键思路总结

- **步长特性**：所有可能的分数 $s$ 必须满足 $s \equiv x \pmod{50}$，枚举时以 50 为步长。
- **逆向调整**：先降低到最小合法值再逐步增加，保证找到首个满足条件的 $s$ 即为最优解。
- **二分优化**：生成的名次序列排序后二分查找，时间复杂度从 $O(25)$ 优化至 $O(\log 25)$。

### 相似题目推荐

1. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057) - 模拟传球过程，状态转移。
2. [P1014 Cantor 表](https://www.luogu.com.cn/problem/P1014) - 模拟数字排列规律。
3. [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563) - 模拟环形队列操作。

---
处理用时：104.83秒