# 题目信息

# Creating a Character

## 题目描述

You play your favourite game yet another time. You chose the character you didn't play before. It has $ str $ points of strength and $ int $ points of intelligence. Also, at start, the character has $ exp $ free experience points you can invest either in strength or in intelligence (by investing one point you can either raise strength by $ 1 $ or raise intelligence by $ 1 $ ).

Since you'd like to make some fun you want to create a jock character, so it has more strength than intelligence points (resulting strength is strictly greater than the resulting intelligence).

Calculate the number of different character builds you can create (for the purpose of replayability) if you must invest all free points. Two character builds are different if their strength and/or intellect are different.

## 说明/提示

In the first query there are only three appropriate character builds: $ (str = 7, int = 5) $ , $ (8, 4) $ and $ (9, 3) $ . All other builds are either too smart or don't use all free points.

In the second query there is only one possible build: $ (2, 1) $ .

In the third query there are two appropriate builds: $ (7, 6) $ , $ (8, 5) $ .

In the fourth query all builds have too much brains.

## 样例 #1

### 输入

```
4
5 3 4
2 1 0
3 5 5
4 10 6
```

### 输出

```
3
1
2
0
```

# AI分析结果

### 题目内容重写

#### 创建角色

## 题目描述

你又一次玩了你最喜欢的游戏。这次你选择了一个之前没有玩过的角色。这个角色有 $str$ 点力量和 $int$ 点智力。此外，角色初始拥有 $exp$ 点自由经验值，你可以将这些经验值投资到力量或智力上（每投资一点，你可以将力量提高 $1$ 或将智力提高 $1$）。

由于你想创造一个“莽夫”角色，因此角色的力量必须严格大于智力（最终的力量值必须严格大于最终的智力值）。

计算你可以创建的不同角色构建的数量（为了可重复性），前提是你必须投入所有自由经验值。如果两个角色构建的力量和/或智力不同，则认为它们是不同的。

## 说明/提示

在第一个查询中，只有三个合适的角色构建：$(str = 7, int = 5)$、$(8, 4)$ 和 $(9, 3)$。其他构建要么智力过高，要么没有使用所有自由经验值。

在第二个查询中，只有一个可能的构建：$(2, 1)$。

在第三个查询中，有两个合适的构建：$(7, 6)$ 和 $(8, 5)$。

在第四个查询中，所有构建的智力都过高。

## 样例 #1

### 输入

```
4
5 3 4
2 1 0
3 5 5
4 10 6
```

### 输出

```
3
1
2
0
```

### 算法分类
数学

### 题解分析与结论

这道题的核心是通过数学推导来确定满足条件的角色构建数量。主要思路是计算力量的最小值和最大值，然后通过差值来确定合法的构建数量。难点在于如何处理边界条件，如经验值为零或初始力量已经满足条件的情况。

### 评分较高的题解

#### 题解1：作者：弦巻こころ (赞：2)
- **星级**：4
- **关键亮点**：通过计算力量的最小值和最大值，直接得出合法构建数量，代码简洁且高效。
- **核心代码**：
```cpp
minn = (a + b + c) / 2 + 1;
maxx = a + c;
printf("%I64d\n", min(c + 1, max(0ll, maxx - minn + 1ll)));
```
- **个人心得**：作者提到要注意取最小值，避免超出合法范围。

#### 题解2：作者：YGB_XU (赞：0)
- **星级**：4
- **关键亮点**：通过计算力量与智力的差值，直接得出合法构建数量，思路清晰且代码简洁。
- **核心代码**：
```cpp
int tmp1 = a - b + c;
int tmp2 = a - b - c;
if (tmp2 > 0) {
    printf("%d\n", c + 1);
} else if (tmp1 <= 0) {
    printf("0\n");
} else {
    printf("%d\n", (tmp1 + 1) / 2);
}
```
- **个人心得**：作者提到通过加一后除二来应对奇偶性，确保计算正确。

#### 题解3：作者：Buried_Dream (赞：0)
- **星级**：4
- **关键亮点**：通过计算力量的最小值和最大值，直接得出合法构建数量，代码简洁且高效。
- **核心代码**：
```cpp
int maxx = a + c;
int minn;
if (!((a + b + c) & 1)) {
    minn = (a + b + c) / 2 + 1;
} else {
    minn = (a + b + c) / 2;
}
cout << Min(c + 1, Max(maxx - minn + 1, 0)) << endl;
```
- **个人心得**：作者提到分奇偶情况处理力量的最小值，确保计算正确。

### 最优关键思路或技巧
- **数学推导**：通过计算力量的最小值和最大值，直接得出合法构建数量。
- **边界处理**：特别注意经验值为零或初始力量已经满足条件的情况。

### 可拓展之处
- **类似问题**：可以扩展到其他属性分配问题，如分配资源使得某一属性严格大于另一属性。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)

---
处理用时：29.77秒