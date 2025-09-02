# 题目信息

# The Meaningless Game

## 题目描述

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF833A/28a3b44282ccdbacfa3b5998d49bb6aaf4e51076.png)Slastyona and her loyal dog Pushok are playing a meaningless game that is indeed very interesting.

The game consists of multiple rounds. Its rules are very simple: in each round, a natural number $ k $ is chosen. Then, the one who says (or barks) it faster than the other wins the round. After that, the winner's score is multiplied by $ k^{2} $ , and the loser's score is multiplied by $ k $ . In the beginning of the game, both Slastyona and Pushok have scores equal to one.

Unfortunately, Slastyona had lost her notepad where the history of all $ n $ games was recorded. She managed to recall the final results for each games, though, but all of her memories of them are vague. Help Slastyona verify their correctness, or, to put it another way, for each given pair of scores determine whether it was possible for a game to finish with such result or not.

## 说明/提示

First game might have been consisted of one round, in which the number $ 2 $ would have been chosen and Pushok would have won.

The second game needs exactly two rounds to finish with such result: in the first one, Slastyona would have said the number $ 5 $ , and in the second one, Pushok would have barked the number $ 3 $ .

## 样例 #1

### 输入

```
6
2 4
75 45
8 8
16 16
247 994
1000000000 1000000
```

### 输出

```
Yes
Yes
Yes
No
No
Yes
```

# AI分析结果



### 题目重写
**题目名称**：无意义游戏  
**题目描述**：  
Slastyona 和她的爱犬 Pushok 在玩一个看似无趣但实则有趣的游戏。游戏由多轮组成，规则如下：每轮选择一个自然数 $k$，其中一方获胜后，其分数乘以 $k^2$，另一方分数乘以 $k$。初始时两人的分数均为 1。给定若干组最终得分，判断是否存在合法游戏过程得到该结果。  

---

### 算法分类  
数学  

---

### 题解对比与结论  
**核心条件**：  
1. 最终得分乘积 $a \times b$ 必须是完全立方数（即存在整数 $k$ 使得 $k^3 = a \times b$）  
2. $a$ 和 $b$ 均能被 $\sqrt[3]{a \times b}$ 整除  

**题解共性**：  
- 计算 $a \times b$ 的立方根 $k$，验证 $k^3 = a \times b$  
- 检查 $a \% k = 0$ 且 $b \% k = 0$  

**难点与优化**：  
- 浮点数精度问题：使用 `round` 确保立方根取整正确  
- 大数处理：需用 `long long` 避免溢出  

---

### 高分题解推荐（评分≥4星）  

#### 1. 作者：Cutler（★★★★☆）  
**亮点**：  
- 代码简洁，逻辑清晰  
- 正确处理浮点精度（`round` + 三次方验证）  
**核心代码**：  
```cpp
int t = round(pow(a * b, 1.0 / 3));
if (t * t * t == a * b && a % t == 0 && b % t == 0) puts("Yes");
```

#### 2. 作者：灵茶山艾府（★★★★☆）  
**亮点**：  
- 数学推导严谨，证明 $AB = \sqrt[3]{ab}$ 的必要性  
- 提供 Golang 实现，验证条件全面  
**核心思路**：  
```go
r := int64(math.Round(math.Cbrt(float64(a * b))))
if r*r*r == a*b && a%r == 0 && b%r == 0 ...
```

#### 3. 作者：DarthVictor（★★★★☆）  
**亮点**：  
- 详细分析错误案例（如忽略整除条件）  
- 强调浮点精度与条件验证的结合  
**关键代码**：  
```cpp
ll m = pow(u, 1.0/3) + 0.5;
if (m*m*m != u || a%m || b%m) ...
```

---

### 最优思路总结  
**关键步骤**：  
1. 计算 $a \times b$ 的立方根 $k$（需四舍五入处理精度）  
2. 验证 $k^3 = a \times b$  
3. 检查 $a \% k = 0$ 且 $b \% k = 0$  

**实现技巧**：  
- 使用 `round` 避免浮点误差，例如 `pow` 后加 0.5 再取整  
- 三次方验证确保计算结果准确  

---

### 类似题目推荐  
1. [P1029 最大公约数和最小公倍数](https://www.luogu.com.cn/problem/P1029)（数学因数分解）  
2. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)（质因数分解与幂次匹配）  
3. [CF1114C 分解质因数的应用](https://codeforces.com/problemset/problem/1114/C)（大数因数分析）  

---

### 题解个人心得摘录  
- **浮点精度**：多位作者强调 `round` 的必要性，直接取整可能导致 $k$ 计算错误（如 `pow(8,1/3)` 可能返回 1.999999）。  
- **条件完整性**：GFyyx 最初遗漏整除条件导致 WA，验证所有条件是关键。  
- **思维陷阱**：立方根合法不代表得分能整除它，需双向验证。

---
处理用时：50.41秒