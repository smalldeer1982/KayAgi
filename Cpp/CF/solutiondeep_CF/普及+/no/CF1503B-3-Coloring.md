# 题目信息

# 3-Coloring

## 题目描述

This is an interactive problem.

Alice and Bob are playing a game. There is $ n\times n $ grid, initially empty. We refer to the cell in row $ i $ and column $ j $ by $ (i, j) $ for $ 1\le i, j\le n $ . There is an infinite supply of tokens that come in $ 3 $ colors labelled $ 1 $ , $ 2 $ , and $ 3 $ .

The game proceeds with turns as follows. Each turn begins with Alice naming one of the three colors, let's call it $ a $ . Then, Bob chooses a color $ b\ne a $ , chooses an empty cell, and places a token of color $ b $ on that cell.

We say that there is a conflict if there exist two adjacent cells containing tokens of the same color. Two cells are considered adjacent if they share a common edge.

If at any moment there is a conflict, Alice wins. Otherwise, if $ n^2 $ turns are completed (so that the grid becomes full) without any conflicts, Bob wins.

We have a proof that Bob has a winning strategy. Play the game as Bob and win.

The interactor is adaptive. That is, Alice's color choices can depend on Bob's previous moves.

## 说明/提示

The final grid from the sample is pictured below. Bob wins because there are no two adjacent cells with tokens of the same color. $ $$$\begin{matrix}2&3\\3&1\end{matrix} $ $$$

The sample is only given to demonstrate the input and output format. It is not guaranteed to represent an optimal strategy for Bob or the real behavior of the interactor.

## 样例 #1

### 输入

```
2
1

2

1

3```

### 输出

```
2 1 1

3 1 2

3 2 1

1 2 2```

# AI分析结果

### 题目内容中文重写
这是一道交互题。

爱丽丝和鲍勃正在玩一个游戏。有一个 $n\times n$ 的网格，初始时为空。对于 $1\le i, j\le n$，我们用 $(i, j)$ 来表示第 $i$ 行第 $j$ 列的单元格。有无限数量的代币，代币有三种颜色，分别标记为 $1$、$2$ 和 $3$。

游戏按以下回合进行。每一回合开始时，爱丽丝说出三种颜色中的一种，我们称之为 $a$。然后，鲍勃选择一种颜色 $b\ne a$，选择一个空单元格，并在该单元格上放置一个颜色为 $b$ 的代币。

如果存在两个相邻单元格包含相同颜色的代币，我们就说出现了冲突。如果两个单元格共享一条公共边，则认为它们相邻。

如果在任何时刻出现冲突，爱丽丝获胜。否则，如果完成了 $n^2$ 个回合（即网格被填满）且没有任何冲突，鲍勃获胜。

我们有一个证明，表明鲍勃有获胜策略。请扮演鲍勃并赢得游戏。

交互器是自适应的。也就是说，爱丽丝的颜色选择可能取决于鲍勃之前的行动。

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先对网格进行染色（通常是黑白染色），将网格划分为两个集合，然后尽可能使用两种颜色填充这两个集合，避免相邻单元格颜色相同。当其中一个集合被填满后，再使用第三种颜色填充剩余的单元格。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Acfboy | 将网格图染成棋盘样子，优先用 $1$ 或 $2$ 填充，一种颜色无法填充时用 $3$ | 用 `check` 函数检验能否继续填 $1$ 或 $2$，不能则找空格填 $3$ | 保证相邻单元格颜色不同 | 4星 |
| water_tomato | 尽可能只用两种颜色填充，将第三种颜色作为后手，先填理想网格，一种数字填完后再处理剩余空格 | 分阶段处理，根据是否填完一种数字决定填充策略 | 避免出现一个空格子周围有两种颜色的情况 | 3星 |
| Lynkcat | 将点奇偶染色分成两个集合，根据爱丽丝的选择在不同集合中染色 | 不同集合染不同颜色，用光一个集合的点后从另一个集合选点染另一种颜色 | 保证相邻单元格颜色不同 | 3星 |
| Binary_Lee | 先预处理红色块和蓝色块的位置，“双线并行” 填充，直到填满其中一种，再处理剩余空格 | 分情况讨论，根据不同条件选择填充的颜色和位置 | 应对交互库的不同选择 | 3星 |
| vectorwyx | 方格图黑白染色，钦定黑色格子填 $1$，白色格子填 $2$，一种颜色格子填满后转变策略 | 根据格子剩余情况和禁止颜色选择填充的颜色和位置 | 保证相邻单元格颜色不同 | 3星 |
| 7KByte | 对格子黑白染色，分两步交互，第一步按规则填充，一种颜色格子填满后进入第二步枚举剩余颜色填充 | 分阶段处理，根据格子剩余情况和禁止颜色选择填充的颜色和位置 | 保证相邻单元格颜色不同 | 3星 |
| hujiasheng1234 | 将棋盘分成两部分，记录 $1$ 或 $2$ 的位置，一种编号位置填完后处理剩余空格 | 用 `vector` 记录位置，根据是否填完一种编号决定填充策略 | 避免相邻位置颜色相同 | 3星 |
| Little09 | 原图黑白染色，$1$ 放入黑格，$2$ 放入白格，一个颜色格子放满后启用 $3$ 填充剩余格子 | 根据格子剩余情况和禁止颜色选择填充的颜色和位置 | 保证相邻单元格颜色不同 | 3星 |
| Warriors_Cat | 网格黑白染色，先规定黑格填 $1$，白格填 $2$，一种颜色格子填满后用 $3$ 填充 | 根据格子剩余情况和禁止颜色选择填充的颜色和位置 | 保证相邻单元格颜色不同 | 3星 |
| t162 | 交错填充，达到特定状态后轻松填完剩余空格 | 分阶段处理，根据是否达到特定状态决定填充策略 | 避免出现一个空格子周围有不同数字的情况 | 3星 |
| alex_liu | 预处理填颜色 $1$ 和颜色 $2$ 的格子，一个颜色格子填完后用颜色 $3$ 代替 | 用栈存储格子位置，根据禁止颜色和格子剩余情况选择填充的颜色和位置 | 保证相邻单元格颜色不同 | 3星 |

### 所选题解
- Acfboy（4星）
  - 关键亮点：思路清晰，代码简短，使用 `check` 函数简化逻辑。

### 重点代码
```cpp
#include <cstdio>
#include <algorithm>
const int N = 105;
int n, c[N][N], vis[N][N], x;
struct twt { int x, y; };
bool check(int x) {
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++)
            if(!vis[i][j] && c[i][j] == x) {
                vis[i][j] = 1;
                printf("%d %d %d\n", x+1, i, j);
                fflush(stdout);
                return 1;
            }
    return 0;
}
twt find() {
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(vis[i][j] == 0) {
                vis[i][j] = 1;
                return (twt){i, j};
            }
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        c[i][1] = 1 ^ c[i-1][1];
        for(int j = 2; j <= n; j++) c[i][j] = 1 ^ c[i][j-1];
    }
    for(int k = 1; k <= n*n; k++) {
        scanf("%d", &x);
        if(x == 3) { if(!check(1)) check(0); }
        else if(!check((x-1)^1)) {    
            twt sp; 
            sp = find();
            printf("%d %d %d\n", 3, sp.x, sp.y);
            fflush(stdout);
        }
    } 
    return 0;
}
```
核心实现思想：先将网格染成棋盘样式，用 `check` 函数检查能否继续填充 $1$ 或 $2$，如果不能则调用 `find` 函数找到空格填充 $3$。

### 关键思路或技巧
- 对网格进行黑白染色，将其划分为两个集合，分别使用不同颜色填充，避免相邻单元格颜色相同。
- 优先使用两种颜色填充，当一种颜色无法填充时，再使用第三种颜色。
- 可以使用数据结构（如栈、`vector` 等）来记录不同颜色单元格的位置，方便后续操作。

### 拓展思路
同类型题可能涉及不同的网格形状、更多的颜色种类或更复杂的规则，但核心思路仍然是通过合理的构造来满足题目要求。类似的算法套路包括对图形进行染色、划分集合、分阶段处理等。

### 推荐题目
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1576 最小花费](https://www.luogu.com.cn/problem/P1576)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)

### 个人心得
Binary_Lee 提到为了找出随意填时填的数不能和给出的数相同这个错误，甚至写了一个简陋的交互库。这提醒我们在处理交互题时，要仔细考虑各种边界情况和限制条件，必要时可以通过编写辅助工具来帮助调试。 

---
处理用时：60.68秒