---
title: "Many Games"
layout: "post"
diff: 省选/NOI-
pid: CF2023D
tag: ['动态规划 DP', '数学', '剪枝', '概率论']
---

# Many Games

## 题目描述

Recently, you received a rare ticket to the only casino in the world where you can actually earn something, and you want to take full advantage of this opportunity.

The conditions in this casino are as follows:

- There are a total of $ n $ games in the casino.
- You can play each game at most once.
- Each game is characterized by two parameters: $ p_i $ ( $ 1 \le p_i \le 100 $ ) and $ w_i $ — the probability of winning the game in percentage and the winnings for a win.
- If you lose in any game you decide to play, you will receive nothing at all (even for the games you won).

You need to choose a set of games in advance that you will play in such a way as to maximize the expected value of your winnings.

In this case, if you choose to play the games with indices $ i_1 < i_2 < \ldots < i_k $ , you will win in all of them with a probability of $ \prod\limits_{j=1}^k \frac{p_{i_j}}{100} $ , and in that case, your winnings will be equal to $ \sum\limits_{j=1}^k w_{i_j} $ .

That is, the expected value of your winnings will be $ \left(\prod\limits_{j=1}^k \frac{p_{i_j}}{100}\right) \cdot \left(\sum\limits_{j=1}^k w_{i_j}\right) $ .

To avoid going bankrupt, the casino owners have limited the expected value of winnings for each individual game. Thus, for all $ i $ ( $ 1 \le i \le n $ ), it holds that $ w_i \cdot p_i \le 2 \cdot 10^5 $ .

Your task is to find the maximum expected value of winnings that can be obtained by choosing some set of games in the casino.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of games offered to play.

The $ i $ -th of the following $ n $ lines contains two integers $ p_i $ and $ w_i $ ( $ 1 \leq p_i \leq 100 $ , $ 1 \leq w_i, p_i \cdot w_i \leq 2 \cdot 10^5 $ ) — the probability of winning and the size of the winnings in the $ i $ -th game.

## 输出格式

Output a single number — the maximum expected value of winnings in the casino that can be obtained by choosing some subset of games.

Your answer will be accepted if the relative or absolute error does not exceed $ 10^{-6} $ . Formally, if $ a $ is your answer and $ b $ is the jury's answer, it will be accepted if $ \frac{|a-b|}{\max(b, 1)} \le 10^{-6} $ .

## 说明/提示

In the first example, you can choose the first and third games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_3}{100}\right) \cdot (w_1 + w_3) = \left(\frac{80}{100}\cdot \frac{50}{100}\right) \cdot (80 + 200) = 112 $ .

In the second example, you can choose the first and second games. In this case, the expected value of winnings will be $ \left(\frac{p_1}{100}\cdot \frac{p_2}{100}\right) \cdot (w_1 + w_2) = \left(\frac{100}{100}\cdot \frac{100}{100}\right) \cdot (1 + 1) = 2 $ .

In the third example, you can choose only the second game. In this case, the expected value of winnings will be $ \frac{p_2}{100} \cdot w_2 = \frac{2}{100} \cdot 1000 = 20 $ .

## 样例 #1

### 输入

```
3
80 80
70 100
50 200
```

### 输出

```
112.00000000
```

## 样例 #2

### 输入

```
2
100 1
100 1
```

### 输出

```
2.00000000
```

## 样例 #3

### 输入

```
4
1 100
2 1000
2 100
3 1
```

### 输出

```
20.00000000
```

## 样例 #4

### 输入

```
5
34 804
78 209
99 191
61 439
90 79
```

### 输出

```
395.20423800
```



---

---
title: "Distinct Paths"
layout: "post"
diff: 省选/NOI-
pid: CF293B
tag: ['搜索', '剪枝', '状态合并']
---

# Distinct Paths

## 题目描述

You have a rectangular $ n×m $ -cell board. Some cells are already painted some of $ k $ colors. You need to paint each uncolored cell one of the $ k $ colors so that any path from the upper left square to the lower right one doesn't contain any two cells of the same color. The path can go only along side-adjacent cells and can only go down or right.

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n,m<=1000,1<=k<=10) $ . The next $ n $ lines contain $ m $ integers each — the board. The first of them contains $ m $ uppermost cells of the board from the left to the right and the second one contains $ m $ cells from the second uppermost row and so on. If a number in a line equals 0, then the corresponding cell isn't painted. Otherwise, this number represents the initial color of the board cell — an integer from 1 to $ k $ .

Consider all colors numbered from 1 to $ k $ in some manner.

## 输出格式

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2 4
0 0
0 0

```

### 输出

```
48

```

## 样例 #2

### 输入

```
2 2 4
1 2
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 6 10
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

```

### 输出

```
3628800

```

## 样例 #4

### 输入

```
2 6 10
1 2 3 4 5 6
0 0 0 0 0 0

```

### 输出

```
4096

```



---

---
title: "Expression"
layout: "post"
diff: 省选/NOI-
pid: CF58E
tag: ['搜索', '剪枝']
---

# Expression

## 题目描述

One day Vasya was solving arithmetical problems. He wrote down an expression $ a+b=c $ in his notebook. When the teacher checked Vasya's work it turned out that Vasya had solved the problem incorrectly. Now Vasya tries to find excuses. He says that he simply forgot to write down several digits in numbers $ a $ , $ b $ and $ c $ , but he can't remember what numbers they actually were. Help Vasya, find such numbers $ x $ , $ y $ and $ z $ , with which the following conditions are met:

- $ x+y=z $ ,
- from the expression $ x+y=z $ several digits can be erased in such a way that the result will be $ a+b=c $ ,
- the expression $ x+y=z $ should have the minimal length.

## 输入格式

The first and only input line contains the expression $ a+b=c $ ( $ 1<=a,b,c<=10^{6} $ , $ a $ , $ b $ and $ c $ don't contain leading zeroes) which is the expression Vasya wrote down.

## 输出格式

Print the correct expression $ x+y=z $ ( $ x $ , $ y $ and $ z $ are non-negative numbers without leading zeroes). The expression $ a+b=c $ must be met in $ x+y=z $ as a subsequence. The printed solution should have the minimal possible number of characters. If there are several such solutions, you can print any of them.

## 样例 #1

### 输入

```
2+4=5

```

### 输出

```
21+4=25

```

## 样例 #2

### 输入

```
1+1=3

```

### 输出

```
1+31=32

```

## 样例 #3

### 输入

```
1+1=2

```

### 输出

```
1+1=2

```



---

