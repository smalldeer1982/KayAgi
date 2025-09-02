# 题目信息

# Education

## 题目描述

Polycarp is wondering about buying a new computer, which costs $ c $ tugriks. To do this, he wants to get a job as a programmer in a big company.

There are $ n $ positions in Polycarp's company, numbered starting from one. An employee in position $ i $ earns $ a[i] $ tugriks every day. The higher the position number, the more tugriks the employee receives. Initially, Polycarp gets a position with the number $ 1 $ and has $ 0 $ tugriks.

Each day Polycarp can do one of two things:

- If Polycarp is in the position of $ x $ , then he can earn $ a[x] $ tugriks.
- If Polycarp is in the position of $ x $ ( $ x < n $ ) and has at least $ b[x] $ tugriks, then he can spend $ b[x] $ tugriks on an online course and move to the position $ x+1 $ .

For example, if $ n=4 $ , $ c=15 $ , $ a=[1, 3, 10, 11] $ , $ b=[1, 2, 7] $ , then Polycarp can act like this:

- On the first day, Polycarp is in the $ 1 $ -st position and earns $ 1 $ tugrik. Now he has $ 1 $ tugrik;
- On the second day, Polycarp is in the $ 1 $ -st position and move to the $ 2 $ -nd position. Now he has $ 0 $ tugriks;
- On the third day, Polycarp is in the $ 2 $ -nd position and earns $ 3 $ tugriks. Now he has $ 3 $ tugriks;
- On the fourth day, Polycarp is in the $ 2 $ -nd position and is transferred to the $ 3 $ -rd position. Now he has $ 1 $ tugriks;
- On the fifth day, Polycarp is in the $ 3 $ -rd position and earns $ 10 $ tugriks. Now he has $ 11 $ tugriks;
- On the sixth day, Polycarp is in the $ 3 $ -rd position and earns $ 10 $ tugriks. Now he has $ 21 $ tugriks;
- Six days later, Polycarp can buy himself a new computer.

Find the minimum number of days after which Polycarp will be able to buy himself a new computer.

## 样例 #1

### 输入

```
3
4 15
1 3 10 11
1 2 7
4 100
1 5 10 50
3 14 12
2 1000000000
1 1
1```

### 输出

```
6
13
1000000000```

# AI分析结果

### 题目翻译
Polycarp 想买一台价值 $c$ 图格里克（货币单位）的新电脑。为此，他想在一家大公司找一份程序员的工作。

公司里有 $n$ 个职位，从 1 开始编号。职位 $i$ 的员工每天能挣 $a[i]$ 图格里克。职位编号越高，员工获得的图格里克越多。最初，Polycarp 处于编号为 1 的职位，并且有 0 图格里克。

每天 Polycarp 可以做以下两件事之一：
- 如果 Polycarp 处于职位 $x$，那么他可以挣得 $a[x]$ 图格里克。
- 如果 Polycarp 处于职位 $x$（$x < n$）且至少有 $b[x]$ 图格里克，那么他可以花费 $b[x]$ 图格里克参加在线课程并晋升到职位 $x + 1$。

例如，如果 $n = 4$，$c = 15$，$a = [1, 3, 10, 11]$，$b = [1, 2, 7]$，那么 Polycarp 可以这样行动：
- 第一天，Polycarp 处于第 1 个职位，挣得 1 图格里克。现在他有 1 图格里克。
- 第二天，Polycarp 处于第 1 个职位并晋升到第 2 个职位。现在他有 0 图格里克。
- 第三天，Polycarp 处于第 2 个职位，挣得 3 图格里克。现在他有 3 图格里克。
- 第四天，Polycarp 处于第 2 个职位并晋升到第 3 个职位。现在他有 1 图格里克。
- 第五天，Polycarp 处于第 3 个职位，挣得 10 图格里克。现在他有 11 图格里克。
- 第六天，Polycarp 处于第 3 个职位，挣得 10 图格里克。现在他有 21 图格里克。
- 六天后，Polycarp 就可以给自己买一台新电脑。

请找出 Polycarp 能够给自己买一台新电脑的最少天数。

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先证明或默认一个最优策略：先移动到某个位置，然后在该位置一直赚钱直到攒够买电脑的钱。不同题解在具体实现和证明过程上有所差异。
- **思路对比**：部分题解通过递推的方式计算到达每个位置的天数和剩余钱数，再计算在该位置攒够钱的总天数；部分题解则直接模拟从低到高的晋升过程，在每个位置判断是继续晋升还是停留赚钱。
- **算法要点**：大多涉及到向上取整的计算，以处理赚钱和晋升所需的天数。同时，利用数组记录到达每个位置的相关信息，如天数、剩余钱数等。
- **解决难点**：主要是证明先晋升到某个位置再一直赚钱的策略是最优的，以及处理晋升和赚钱过程中的钱数计算和天数累加。

### 所选题解
- **rui_er（5星）**：
    - **关键亮点**：思路清晰，通过递推公式计算到达每个位置的天数、剩余钱数以及在该位置攒够钱的总天数，代码简洁明了。
    - **核心代码**：
```cpp
rep(i, 2, n) {
    day[i] = day[i-1] + 1 + (b[i-1] - now[i-1] + a[i-1] - 1) / a[i-1];
    now[i] = (b[i-1] - now[i-1] + a[i-1] - 1) / a[i-1] * a[i-1] + now[i-1] - b[i-1];
    ans[i] = day[i] + (c - now[i] + a[i] - 1) / a[i];
    Ans = min(Ans, ans[i]);
}
```
核心实现思想：通过循环从第 2 个位置开始递推，根据前一个位置的信息计算当前位置的天数、剩余钱数和总天数，同时更新最小总天数。
- **SunsetVoice（4星）**：
    - **关键亮点**：准确指出题目翻译的问题，并对贪心策略的正确性进行了简要证明，思路简洁。
    - **核心思路**：直接从 1 到 $n$ 扫描，在每个位置判断是停留赚钱还是继续晋升，一旦钱数足够就晋升，因为 $a$ 序列不降，继续向前不会更劣。
- **irris（4星）**：
    - **关键亮点**：补充了贪心策略正确性的证明，逻辑严谨，代码实现简洁。
    - **核心代码**：
```cpp
for (int i = 1; i < N; ++i) 
    b[i] = read<int>(), d[i + 1] = dv(b[i] - c[i], a[i]), c[i + 1] = c[i] + d[i + 1] * a[i] - b[i], d[i + 1] += d[i] + 1;
for (int i = 1; i <= N; ++i) ans = std::min((long long)ans, d[i] + dv(T - c[i], a[i]));
```
核心实现思想：通过循环计算到达每个位置的天数和剩余钱数，再计算在每个位置攒够钱的总天数，取最小值。

### 最优关键思路或技巧
- **贪心策略**：先晋升到某个位置，然后在该位置一直赚钱，因为 $a$ 序列不降，这样能保证赚钱效率最高。
- **向上取整技巧**：在计算赚钱和晋升所需的天数时，使用 `(m + n - 1) / n` 来实现向上取整，避免了使用 `ceil` 函数。

### 可拓展之处
同类型题可能会改变晋升规则、赚钱规则或增加其他限制条件，但核心思路仍然是通过贪心策略找到最优的行动方案。类似算法套路可以应用于资源分配、路径选择等问题，通过分析不同选择的优劣，确定最优策略。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心策略，通过合理安排排队顺序使总等待时间最短。
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心算法的应用，通过合理分组使分组数最少。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：典型的贪心问题，根据物品的性价比选择物品，使总价值最大。

### 个人心得摘录与总结
- **SunsetVoice**：指出题目翻译不全，缺少 $a$ 序列不降的信息，且该信息对贪心的证明极为必要，提醒我们在解题时要注意题目条件的完整性。
- **irris**：补全了其他题解缺少的贪心策略正确性证明，强调了证明的重要性，帮助我们更好地理解算法的正确性。

---
处理用时：44.26秒