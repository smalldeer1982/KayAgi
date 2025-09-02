# 题目信息

# Plus and Square Root

## 题目描述

ZS the Coder is playing a game. There is a number displayed on the screen and there are two buttons, ' $ + $ ' (plus) and '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' (square root). Initially, the number $ 2 $ is displayed on the screen. There are $ n+1 $ levels in the game and ZS the Coder start at the level $ 1 $ .

When ZS the Coder is at level $ k $ , he can :

1. Press the ' $ + $ ' button. This increases the number on the screen by exactly $ k $ . So, if the number on the screen was $ x $ , it becomes $ x+k $ .
2. Press the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button. Let the number on the screen be $ x $ . After pressing this button, the number becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/e2db36dd56c863e7b06dd83afaf9d635a860d586.png). After that, ZS the Coder levels up, so his current level becomes $ k+1 $ . This button can only be pressed when $ x $ is a perfect square, i.e. $ x=m^{2} $ for some positive integer $ m $ .

Additionally, after each move, if ZS the Coder is at level $ k $ , and the number on the screen is $ m $ , then  $ m $ must be a multiple of $ k $ . Note that this condition is only checked after performing the press. For example, if ZS the Coder is at level $ 4 $ and current number is $ 100 $ , he presses the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button and the number turns into $ 10 $ . Note that at this moment, $ 10 $ is not divisible by $ 4 $ , but this press is still valid, because after it, ZS the Coder is at level $ 5 $ , and $ 10 $ is divisible by $ 5 $ .

ZS the Coder needs your help in beating the game — he wants to reach level $ n+1 $ . In other words, he needs to press the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button $ n $ times. Help him determine the number of times he should press the ' $ + $ ' button before pressing the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button at each level.

Please note that ZS the Coder wants to find just any sequence of presses allowing him to reach level $ n+1 $ , but not necessarily a sequence minimizing the number of presses.

## 说明/提示

In the first sample case:

On the first level, ZS the Coder pressed the ' $ + $ ' button $ 14 $ times (and the number on screen is initially $ 2 $ ), so the number became $ 2+14·1=16 $ . Then, ZS the Coder pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, and the number became ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/9308f88c365c030e2395e6c4e7fb256c45e3ee80.png).

After that, on the second level, ZS pressed the ' $ + $ ' button $ 16 $ times, so the number becomes $ 4+16·2=36 $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/7b6a09b10477bfd8c4130abca871a5a72fd33934.png).

After that, on the third level, ZS pressed the ' $ + $ ' button $ 46 $ times, so the number becomes $ 6+46·3=144 $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/1ca1ffe171430a4d7ba5708c52a6d2103e02de0f.png).

Note that $ 12 $ is indeed divisible by $ 4 $ , so ZS the Coder can reach level $ 4 $ .

Also, note that pressing the ' $ + $ ' button $ 10 $ times on the third level before levelling up does not work, because the number becomes $ 6+10·3=36 $ , and when the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button is pressed, the number becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/7b6a09b10477bfd8c4130abca871a5a72fd33934.png) and ZS the Coder is at Level $ 4 $ . However, $ 6 $ is not divisible by $ 4 $ now, so this is not a valid solution.

In the second sample case:

On the first level, ZS the Coder pressed the ' $ + $ ' button $ 999999999999999998 $ times (and the number on screen is initially $ 2 $ ), so the number became $ 2+999999999999999998·1=10^{18} $ . Then, ZS the Coder pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, and the number became ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/ea4aa948ec20d05a136bf9d7be9348e6b59c2a62.png).

After that, on the second level, ZS pressed the ' $ + $ ' button $ 44500000000 $ times, so the number becomes $ 10^{9}+44500000000·2=9·10^{10} $ . Then, ZS pressed the '![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/59438ac362049a52a19e6e78713de751c1d0a324.png)' button, levelling up and changing the number into ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715A/9d032592276d09e8199b07c1b9d030f7638a4d76.png).

Note that $ 300000 $ is a multiple of $ 3 $ , so ZS the Coder can reach level $ 3 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
14
16
46
```

## 样例 #2

### 输入

```
2
```

### 输出

```
999999999999999998
44500000000
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2
17
46
97
```

# AI分析结果

### 题目内容
# Plus and Square Root

## 题目描述
ZS 正在玩一个游戏。屏幕上显示一个数字，并有两个按钮，“ + ”（加号）和“$\sqrt{}$”（平方根）。最初，屏幕上显示的数字是 2 。游戏共有 $n + 1$ 个关卡，ZS 从第 1 关开始。

当 ZS 处于第 $k$ 关时，他可以：
1. 按下“ + ”按钮。这会使屏幕上的数字恰好增加 $k$ 。也就是说，如果屏幕上的数字是 $x$ ，它将变为 $x + k$ 。
2. 按下“$\sqrt{}$”按钮。设屏幕上的数字为 $x$ 。按下此按钮后，数字变为 $\sqrt{x}$ 。之后，ZS 进入下一关，即他当前的关卡变为 $k + 1$ 。只有当 $x$ 是一个完全平方数，即 $x = m^{2}$ （$m$ 为正整数）时，才能按下此按钮。

此外，每次操作后，如果 ZS 处于第 $k$ 关，且屏幕上的数字为 $m$ ，那么 $m$ 必须是 $k$ 的倍数。请注意，此条件仅在操作完成后检查。例如，如果 ZS 处于第 4 关，当前数字为 100 ，他按下“$\sqrt{}$”按钮，数字变为 10 。此时，10 不能被 4 整除，但此操作仍然有效，因为之后 ZS 处于第 5 关，且 10 能被 5 整除。

ZS 需要你帮助他通关游戏——他想达到第 $n + 1$ 关。换句话说，他需要按下“$\sqrt{}$”按钮 $n$ 次。帮助他确定在每一关按下“$\sqrt{}$”按钮之前，应该按下“ + ”按钮的次数。

请注意，ZS 只想找到任何一种能让他达到第 $n + 1$ 关的操作序列，而不一定要找到操作次数最少的序列。

## 说明/提示
在第一个样例中：
在第一关，ZS 按下“ + ”按钮 14 次（屏幕上最初的数字是 2 ），所以数字变为 $2 + 14×1 = 16$ 。然后，ZS 按下“$\sqrt{}$”按钮，数字变为 $\sqrt{16} = 4$ 。

之后，在第二关，ZS 按下“ + ”按钮 16 次，所以数字变为 $4 + 16×2 = 36$ 。然后，ZS 按下“$\sqrt{}$”按钮，进入下一关，数字变为 $\sqrt{36} = 6$ 。

之后，在第三关，ZS 按下“ + ”按钮 46 次，所以数字变为 $6 + 46×3 = 144$ 。然后，ZS 按下“$\sqrt{}$”按钮，进入下一关，数字变为 $\sqrt{144} = 12$ 。

注意，12 确实能被 4 整除，所以 ZS 可以达到第 4 关。

另外，注意在第三关升级前按下“ + ”按钮 10 次是不行的，因为数字变为 $6 + 10×3 = 36$ ，当按下“$\sqrt{}$”按钮时，数字变为 $\sqrt{36} = 6$ ，而 ZS 此时处于第 4 关。然而，6 不能被 4 整除，所以这不是一个有效的解决方案。

在第二个样例中：
在第一关，ZS 按下“ + ”按钮 999999999999999998 次（屏幕上最初的数字是 2 ），所以数字变为 $2 + 999999999999999998×1 = 10^{18}$ 。然后，ZS 按下“$\sqrt{}$”按钮，数字变为 $\sqrt{10^{18}} = 10^{9}$ 。

之后，在第二关，ZS 按下“ + ”按钮 44500000000 次，所以数字变为 $10^{9} + 44500000000×2 = 9×10^{10}$ 。然后，ZS 按下“$\sqrt{}$”按钮，进入下一关，数字变为 $\sqrt{9×10^{10}} = 300000$ 。

注意，300000 是 3 的倍数，所以 ZS 可以达到第 3 关。

## 样例 #1
### 输入
```
3
```
### 输出
```
14
16
46
```
## 样例 #2
### 输入
```
2
```
### 输出
```
999999999999999998
44500000000
```
## 样例 #3
### 输入
```
4
```
### 输出
```
2
17
46
97
```

• **算法分类**：数学
• **综合分析与结论**：这些题解的核心思路都是通过数学推导得出每一关按下“ + ”按钮次数的通用公式。各题解均先分析游戏规则，得出每关数字需满足的倍数关系等条件，进而推导公式。难点在于如何从游戏规则中提炼出数学关系并正确推导公式。不同题解推导过程表述略有差异，但本质相同，都得出第 $k$ 关按下“ + ”按钮次数为 $k^3 + 2k^2 + 1$（$k \geq 2$），第一关特殊处理为 2 。
• **通用建议与扩展思路**：解决此类问题关键在于深入理解题目规则，将其转化为数学关系。可拓展到其他基于规则推导公式的数学类题目，解题时注重对规则的分析和数学归纳法等方法的运用。
• **推荐题目**：
  - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
  - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)
  - [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)

---
处理用时：48.13秒