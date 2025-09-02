# 题目信息

# Breaking the Wall

## 题目描述

Monocarp plays "Rage of Empires II: Definitive Edition" — a strategic computer game. Right now he's planning to attack his opponent in the game, but Monocarp's forces cannot enter the opponent's territory since the opponent has built a wall.

The wall consists of $ n $ sections, aligned in a row. The $ i $ -th section initially has durability $ a_i $ . If durability of some section becomes $ 0 $ or less, this section is considered broken.

To attack the opponent, Monocarp needs to break at least two sections of the wall (any two sections: possibly adjacent, possibly not). To do this, he plans to use an onager — a special siege weapon. The onager can be used to shoot any section of the wall; the shot deals $ 2 $ damage to the target section and $ 1 $ damage to adjacent sections. In other words, if the onager shoots at the section $ x $ , then the durability of the section $ x $ decreases by $ 2 $ , and the durability of the sections $ x - 1 $ and $ x + 1 $ (if they exist) decreases by $ 1 $ each.

Monocarp can shoot at any sections any number of times, he can even shoot at broken sections.

Monocarp wants to calculate the minimum number of onager shots needed to break at least two sections. Help him!

## 说明/提示

In the first example, it is possible to break the $ 2 $ -nd and the $ 4 $ -th section in $ 10 $ shots, for example, by shooting the third section $ 10 $ times. After that, the durabilities become $ [20, 0, 10, 0, 20] $ . Another way of doing it is firing $ 5 $ shots at the $ 2 $ -nd section, and another $ 5 $ shots at the $ 4 $ -th section. After that, the durabilities become $ [15, 0, 20, 0, 15] $ .

In the second example, it is enough to shoot the $ 2 $ -nd section once. Then the $ 1 $ -st and the $ 3 $ -rd section will be broken.

In the third example, it is enough to shoot the $ 2 $ -nd section twice (then the durabilities become $ [5, 2, 4, 8, 5, 8] $ ), and then shoot the $ 3 $ -rd section twice (then the durabilities become $ [5, 0, 0, 6, 5, 8] $ ). So, four shots are enough to break the $ 2 $ -nd and the $ 3 $ -rd section.

## 样例 #1

### 输入

```
5
20 10 30 10 20```

### 输出

```
10```

## 样例 #2

### 输入

```
3
1 8 1```

### 输出

```
1```

## 样例 #3

### 输入

```
6
7 6 6 8 5 8```

### 输出

```
4```

## 样例 #4

### 输入

```
6
14 3 8 10 15 4```

### 输出

```
4```

## 样例 #5

### 输入

```
4
1 100 100 1```

### 输出

```
2```

## 样例 #6

### 输入

```
3
40 10 10```

### 输出

```
7```

# AI分析结果

### 题目翻译
## 打破城墙

### 题目描述
Monocarp正在玩《帝国时代2：决定版》——一款策略类电脑游戏。目前，他正计划在游戏中攻击对手，但由于对手建造了城墙，Monocarp的部队无法进入对手的领地。

城墙由 $n$ 个部分组成，排成一排。第 $i$ 个部分最初的耐久度为 $a_i$。如果某个部分的耐久度变为 $0$ 或更低，则该部分被视为已破损。

为了攻击对手，Monocarp需要打破至少两段城墙（任意两段：可能相邻，也可能不相邻）。为此，他计划使用投石车——一种特殊的攻城武器。投石车可以用来射击城墙的任何部分；射击会对目标部分造成 $2$ 点伤害，并对相邻部分造成 $1$ 点伤害。换句话说，如果投石车射击第 $x$ 部分，那么第 $x$ 部分的耐久度减少 $2$，第 $x - 1$ 和 $x + 1$ 部分（如果存在）的耐久度各减少 $1$。

Monocarp可以对任何部分进行任意次数的射击，他甚至可以射击已经破损的部分。

Monocarp想要计算打破至少两段城墙所需的最少投石车射击次数。请帮助他！

### 说明/提示
在第一个示例中，可以在 $10$ 次射击中打破第 $2$ 段和第 $4$ 段城墙，例如，对第 $3$ 段射击 $10$ 次。之后，耐久度变为 $[20, 0, 10, 0, 20]$。另一种方法是对第 $2$ 段射击 $5$ 次，对第 $4$ 段再射击 $5$ 次。之后，耐久度变为 $[15, 0, 20, 0, 15]$。

在第二个示例中，对第 $2$ 段射击一次就足够了。这样，第 $1$ 段和第 $3$ 段就会被打破。

在第三个示例中，对第 $2$ 段射击两次（之后耐久度变为 $[5, 2, 4, 8, 5, 8]$），然后对第 $3$ 段射击两次（之后耐久度变为 $[5, 0, 0, 6, 5, 8]$）就足够了。因此，四次射击足以打破第 $2$ 段和第 $3$ 段城墙。

### 样例 #1
#### 输入
```
5
20 10 30 10 20
```
#### 输出
```
10
```

### 样例 #2
#### 输入
```
3
1 8 1
```
#### 输出
```
1
```

### 样例 #3
#### 输入
```
6
7 6 6 8 5 8
```
#### 输出
```
4
```

### 样例 #4
#### 输入
```
6
14 3 8 10 15 4
```
#### 输出
```
4
```

### 样例 #5
#### 输入
```
4
1 100 100 1
```
#### 输出
```
2
```

### 样例 #6
#### 输入
```
3
40 10 10
```
#### 输出
```
7
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来计算打破至少两段城墙所需的最少射击次数。主要分为以下三种情况：
1. **选择最小的两个数**：分别对这两个数进行减 $2$ 的操作，总花费为 $\lceil\frac{\min_1}{2}\rceil+\lceil\frac{\min_2}{2}\rceil$。
2. **选择相邻的两个数**：若其中一个数不小于另一个数的两倍，直接对较大数操作，花费为 $\lceil\frac{\max(a_i,a_{i + 1})}{2}\rceil$；否则，将两数视为整体，每次操作使两数之和减小 $3$，花费为 $\lceil\frac{a_i + a_{i + 1}}{3}\rceil$。
3. **选择距离为 $2$ 的两个数**：每次操作使两数之和减小 $2$，总花费为 $\lceil\frac{a_{i - 1}+a_{i + 1}}{2}\rceil$。

最后取这三种情况的最小值作为最终答案。

### 所选题解
- **ncwzdlsd（4星）**
    - **关键亮点**：思路清晰，将三种情况分别封装成函数，代码可读性高。
    - **个人心得**：无
- **DaiRuiChen007（4星）**
    - **关键亮点**：详细分析了三种情况的原理，代码实现简洁，时间复杂度为 $\Theta(n)$。
    - **个人心得**：无
- **lingfunny（4星）**
    - **关键亮点**：对每种情况的操作方案进行了详细的推理和证明，逻辑严谨。
    - **个人心得**：无

### 重点代码
#### ncwzdlsd 的代码
```cpp
void op1()
{
    sort(b + 1, b + n + 1);
    c1 = (b[1] + 1) / 2 + (b[2] + 1) / 2;
}

void op2()
{
    c2 = 0x3f3f3f;
    for (int i = 1; i < n; i++)
    {
        if (a[i + 1] >= a[i] * 2 || a[i] >= a[i + 1] * 2) c2 = min(c2, (max(a[i], a[i + 1]) + 1) / 2);
        else c2 = min(c2, (a[i] + a[i + 1] + 2) / 3);
    }
}

void op3()
{
    c3 = 0x3f3f3f;
    for (int i = 2; i < n; i++) c3 = min(c3, (a[i - 1] + a[i + 1] + 1) / 2);
}
```
**核心实现思想**：`op1` 函数通过排序找到最小的两个数并计算花费；`op2` 函数遍历相邻的数，根据大小关系计算花费；`op3` 函数遍历距离为 $2$ 的数，计算花费。

#### DaiRuiChen007 的代码
```cpp
inline int cost1() {
    int ret = INF;
    for (int i = 1; i < n; ++i) {
        if (max(a[i], a[i + 1]) >= 2 * min(a[i], a[i + 1])) ret = min(ret, (max(a[i], a[i + 1]) + 1) / 2);
        else ret = min(ret, (a[i] + a[i + 1] + 2) / 3);
    }
    return ret;
}

inline int cost2() {
    int ret = INF;
    for (int i = 2; i < n; ++i) {
        ret = min(ret, (a[i - 1] + a[i + 1] + 1) / 2);
    }
    return ret;
}

inline int cost3() {
    int fir = INF, sec = INF;
    for (int i = 1; i <= n; ++i) {
        if (a[i] < fir) sec = fir, fir = a[i];
        else if (a[i] < sec) sec = a[i];
    }
    return (fir + 1) / 2 + (sec + 1) / 2;
}
```
**核心实现思想**：`cost1` 函数计算相邻数的最小花费；`cost2` 函数计算距离为 $2$ 的数的最小花费；`cost3` 函数找到最小的两个数并计算花费。

#### lingfunny 的代码
```cpp
for (int i = 1; i < n; ++i) {
    x = a[i], y = a[i + 1];
    if (x > y) swap(x, y);
    if (x <= (y + 1) / 2) res = min(res, (y + 1) / 2);
    else res = min(res, (x + y + 2) / 3);
}
for (int i = 1; i + 2 <= n; ++i) res = min(res, (a[i] + a[i + 2] + 1) / 2);
auto it = min_element(a + 1, a + n + 1);
x = *it; *it = 1e9; it = min_element(a + 1, a + n + 1);
y = *it; res = min(res, (x + 1) / 2 + (y + 1) / 2);
```
**核心实现思想**：第一个循环计算相邻数的最小花费；第二个循环计算距离为 $2$ 的数的最小花费；最后找到最小的两个数并计算花费，取最小值作为最终结果。

### 关键思路或技巧
- **分类讨论**：将问题分为三种情况进行讨论，分别计算每种情况的最少射击次数，最后取最小值。
- **向上取整技巧**：使用 `(x + 1) / 2` 实现 $\lceil\frac{x}{2}\rceil$ 的效果，使用 `(x + 2) / 3` 实现 $\lceil\frac{x}{3}\rceil$ 的效果。

### 拓展思路
同类型题目可能会改变操作规则或条件，例如改变每次操作对相邻元素的影响，或者要求打破更多的部分。解题思路仍然可以采用分类讨论的方法，根据新的规则重新分析各种情况。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：考察动态规划和数学思维。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目。
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，需要运用数学和动态规划知识。

### 个人心得摘录与总结
- **UperFicial**：表示 $2000$ 难度的题调了 $2$ 小时，提醒自己写题解敲警钟，建议写对拍来调试代码。总结：复杂题目调试困难，对拍是有效的调试手段。
- **I_am_Accepted**：提到自己的代码被 Hack 了，指出距离为 $2$ 和相邻数的情况是 Hack 点。总结：在处理特殊情况时要仔细分析，避免出现漏洞。
- **Deuteron**：提到自己惨遭 Hack，提醒注意距离为 $2$ 和相邻数的情况。总结：对特殊情况的处理要严谨，考虑全面。

---
处理用时：68.81秒