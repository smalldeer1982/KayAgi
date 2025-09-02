# 题目信息

# Nauuo and Chess

## 题目描述

Nauuo is a girl who loves playing chess.

One day she invented a game by herself which needs $ n $ chess pieces to play on a $ m\times m $ chessboard. The rows and columns are numbered from $ 1 $ to $ m $ . We denote a cell on the intersection of the $ r $ -th row and $ c $ -th column as $ (r,c) $ .

The game's goal is to place $ n $ chess pieces numbered from $ 1 $ to $ n $ on the chessboard, the $ i $ -th piece lies on $ (r_i,\,c_i) $ , while the following rule is satisfied: for all pairs of pieces $ i $ and $ j $ , $ |r_i-r_j|+|c_i-c_j|\ge|i-j| $ . Here $ |x| $ means the absolute value of $ x $ .

However, Nauuo discovered that sometimes she couldn't find a solution because the chessboard was too small.

She wants to find the smallest chessboard on which she can put $ n $ pieces according to the rules.

She also wonders how to place the pieces on such a chessboard. Can you help her?

## 说明/提示

In the first example, you can't place the two pieces on a $ 1\times1 $ chessboard without breaking the rule. But you can place two pieces on a $ 2\times2 $ chessboard like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/19a9324ad1d9f76a12004b1e06e1a6fc8ea5363a.png)

In the second example, you can't place four pieces on a $ 2\times2 $ chessboard without breaking the rule. For example, if you place the pieces like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/dd0c838eb5fa429a4dd839467d147e6034fac9bb.png)

then $ |r_1-r_3|+|c_1-c_3|=|1-2|+|1-1|=1 $ , $ |1-3|=2 $ , $ 1<2 $ ; and $ |r_1-r_4|+|c_1-c_4|=|1-2|+|1-2|=2 $ , $ |1-4|=3 $ , $ 2<3 $ . It doesn't satisfy the rule.

However, on a $ 3\times3 $ chessboard, you can place four pieces like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1173B/b7f6bf4dffb399263283db89988092d0fdbbac58.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
2
1 1
1 2```

## 样例 #2

### 输入

```
4
```

### 输出

```
3
1 1
1 3
3 1
3 3```

# AI分析结果

### 题目内容
Nauuo是一个热爱下棋的女孩。

有一天，她自己发明了一个游戏，需要在一个\(m×m\)的棋盘上放置\(n\)个棋子。棋盘的行和列从\(1\)到\(m\)编号。我们将第\(r\)行和第\(c\)列交叉处的单元格表示为\((r, c)\)。

游戏的目标是在棋盘上放置编号从\(1\)到\(n\)的\(n\)个棋子，第\(i\)个棋子位于\((r_i, c_i)\)，同时要满足以下规则：对于任意两个棋子\(i\)和\(j\)，\(\vert r_i - r_j\vert + \vert c_i - c_j\vert \geq \vert i - j\vert\)。这里\(\vert x\vert\)表示\(x\)的绝对值。

然而，Nauuo发现有时由于棋盘太小，她找不到解决方案。

她想找到能按照规则放置\(n\)个棋子的最小棋盘。

她还想知道如何在这样的棋盘上放置棋子。你能帮助她吗？

### 说明/提示
在第一个例子中，在\(1×1\)的棋盘上放置两个棋子会违反规则。但你可以在\(2×2\)的棋盘上这样放置两个棋子：
（此处有对应图片）

在第二个例子中，在\(2×2\)的棋盘上放置四个棋子会违反规则。例如，如果你这样放置棋子：
（此处有对应图片）

那么\(\vert r_1 - r_3\vert + \vert c_1 - c_3\vert = \vert 1 - 2\vert + \vert 1 - 1\vert = 1\)，\(\vert 1 - 3\vert = 2\)，\(1 < 2\)；并且\(\vert r_1 - r_4\vert + \vert c_1 - c_4\vert = \vert 1 - 2\vert + \vert 1 - 2\vert = 2\)，\(\vert 1 - 4\vert = 3\)，\(2 < 3\)。这不满足规则。

然而，在\(3×3\)的棋盘上，你可以这样放置四个棋子：
（此处有对应图片）

### 样例 #1
- **输入**：
```
2
```
- **输出**：
```
2
1 1
1 2
```

### 样例 #2
- **输入**：
```
4
```
- **输出**：
```
3
1 1
1 3
3 1
3 3
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心都是先确定能放置\(n\)个棋子的最小棋盘边长\(m\)，再给出棋子的放置方法。思路上，大多通过对规则\(\vert r_i - r_j\vert + \vert c_i - c_j\vert \geq \vert i - j\vert\)的分析，结合贪心思想或数学推导得出\(m = \left\lfloor\frac{n}{2}\right\rfloor + 1\)。放置棋子的方法主要有沿着边摆（如左上角到右下角的L形摆放）、按斜行放置等。各题解的差异在于推导\(m\)的方式以及代码实现的简洁性和可读性。

### 所选的题解
- **作者：VenusM1nT（5星）**
  - **关键亮点**：思路清晰，先通过贪心思想得出棋盘边长\(m\)与棋子数\(n\)的关系\(m = n/2 + 1\)，再简单描述棋子沿边摆放的构造方法，代码简洁明了。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define reg register
#define inl inline
using namespace std;
int n,ans[MAXN][MAXN];
int main()
{
    scanf("%d",&n);
    reg int m=n/2+1;
    printf("%d\n",n/2+1);
    for(reg int i=1;i<=m && i<=n;i++) printf("%d %d\n",1,i);
    for(reg int i=2;i<=n-m+1;i++) printf("%d %d\n",i,m);
    return 0;
}
```
  - **核心实现思想**：先计算出棋盘边长\(m\)，然后分两段循环输出棋子位置，第一段沿第一行从左到右放置棋子，第二段沿最后一列从上到下放置棋子。

- **作者：ouuan（4星）**
  - **关键亮点**：通过严谨的数学推导得出\(m\)的取值范围，并证明\(m\)可以取到\(\left\lfloor\frac{n}{2}\right\rfloor + 1\)，提出按斜行放置棋子的方法，逻辑完整。
  - **核心代码**：
```cpp
#include <cstdio>
using namespace std;
int main()
{
    int n, i, ans;
    scanf("%d", &n);
    ans = n / 2 + 1;
    printf("%d", ans);
    for (i = 1; i <= ans; ++i) printf("\n%d 1", i);
    for (i = 2; i <= n - ans + 1; ++i) printf("\n%d %d", ans, i);
    return 0;
}
```
  - **核心实现思想**：先计算棋盘边长\(ans\)，同样分两段循环，第一段沿第一列从上到下放置棋子，第二段沿最后一行从左到右放置棋子。

- **作者：StudyingFather（4星）**
  - **关键亮点**：给出一种具体的棋子构造方式（L形摆放），并指出满足\(r_i + c_i = i + 1\)的方案都是可行解，虽然未详细证明但提供了思路方向。
  - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct node
{
    int r,c;
}a[1005];
int main()
{
    int n;
    scanf("%d",&n);
    a[1].r=a[1].c=1;
    int mid=n/2+1;
    printf("%d\n",mid);
    for(int i=1;i<=mid;i++)
        printf("1 %d\n",i);
    for(int i=mid+1;i<=n;i++)
        printf("%d %d\n",i-mid+1,mid);
    return 0;
}
```
  - **核心实现思想**：定义结构体存储棋子位置，计算出棋盘边长\(mid\)，分两段循环，第一段沿第一行从左到右放置棋子，第二段沿最后一列从上到下放置棋子。

### 最优关键思路或技巧
通过对规则的分析，利用贪心思想或数学推导确定棋盘最小边长\(m\)，再根据不同的构造方式放置棋子。在证明\(m\)的取值以及棋子放置方法的合理性时，运用到绝对值不等式、坐标关系等数学知识。

### 同类型题或类似算法套路拓展
此类题目通常是给定一定的限制条件，要求构造出满足条件的数据排列或布局。解题时需深入分析限制条件，通过数学推导、贪心策略等方法找到可行的构造方案。

### 洛谷相似题目推荐
 - [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)：通过贪心策略构造满足条件的数字。
 - [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：结合搜索与构造思想解决路径规划问题。
 - [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：根据条件构造覆盖关系求解。 

---
处理用时：78.73秒