# 题目信息

# Little Artem

## 题目描述

Young boy Artem tries to paint a picture, and he asks his mother Medina to help him. Medina is very busy, that's why she asked for your help.

Artem wants to paint an $ n \times m $ board. Each cell of the board should be colored in white or black.

Lets $ B $ be the number of black cells that have at least one white neighbor adjacent by the side. Let $ W $ be the number of white cells that have at least one black neighbor adjacent by the side. A coloring is called good if $ B = W + 1 $ .

The first coloring shown below has $ B=5 $ and $ W=4 $ (all cells have at least one neighbor with the opposite color). However, the second coloring is not good as it has $ B=4 $ , $ W=4 $ (only the bottom right cell doesn't have a neighbor with the opposite color).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333A/34674661541310c7b0f570cbf7d03ed451c5851a.png)Please, help Medina to find any good coloring. It's guaranteed that under given constraints the solution always exists. If there are several solutions, output any of them.

## 说明/提示

In the first testcase, $ B=3 $ , $ W=2 $ .

In the second testcase, $ B=5 $ , $ W=4 $ . You can see the coloring in the statement.

## 样例 #1

### 输入

```
2
3 2
3 3```

### 输出

```
BW
WB
BB
BWB
BWW
BWB```

# AI分析结果

### 题目内容
# Little Artem

## 题目描述
小男孩阿尔乔姆（Artem）尝试画画，并请求他的母亲梅迪纳（Medina）帮忙。梅迪纳非常忙，所以她向你求助。

阿尔乔姆想画一个 $n \times m$ 的棋盘。棋盘的每个格子都应涂成白色或黑色。

设 $B$ 为至少有一个白色相邻格子（边相邻）的黑色格子的数量。设 $W$ 为至少有一个黑色相邻格子（边相邻）的白色格子的数量。如果 $B = W + 1$，则称这种涂色方式为好的。

下面显示的第一种涂色方式中，$B = 5$ 且 $W = 4$（所有格子都至少有一个颜色相反的相邻格子）。然而，第二种涂色方式不好，因为 $B = 4$，$W = 4$（只有右下角的格子没有颜色相反的相邻格子）。
![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333A/34674661541310c7b0f570cbf7d03ed451c5851a.png)
请帮助梅迪纳找到任何一种好的涂色方式。保证在给定的限制条件下，解总是存在的。如果有多种解，输出其中任何一种。

## 说明/提示
在第一个测试用例中，$B = 3$，$W = 2$。

在第二个测试用例中，$B = 5$，$W = 4$。你可以在题目描述中看到这种涂色方式。

## 样例 #1
### 输入
```
2
3 2
3 3
```
### 输出
```
BW
WB
BB
BWB
BWW
BWB
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过特定的构造方式来满足 $B = W + 1$ 的条件。不同题解的构造方法有所不同，主要区别在于对不同情况（如 $n$ 和 $m$ 的奇偶性）的分类讨论以及具体的构造细节。有些题解思路清晰，代码实现简洁明了；有些则相对复杂，可读性稍差。

### 所选的题解
- **作者：Warriors_Cat（4星）**
  - **关键亮点**：先构造黑白交替的矩阵，再根据 $n$ 和 $m$ 的奇偶性进行调整。当 $n$ 和 $m$ 均为奇数时，直接按黑白交替输出；否则，先构造黑白交替矩阵，再通过判断角上格子的情况，将合适的白色角格改为黑色，使 $B = W + 1$，思路清晰，代码实现较为简洁。
  - **重点代码**：
```cpp
if((n & 1) && (m & 1)){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(((i - 1) * n + j) & 1) printf("B");
            else printf("W");
        }
        printf("\n");
    }
    continue;
}//如果两个均为奇数
else{
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if((i & 1) ^ (j & 1)) s[i][j] = 'W';
            else s[i][j] = 'B';
        }
    }//先构造
    if(s[1][2] == 'B') s[1][1] = 'B';
    else if(s[1][m - 1] == 'B') s[1][m] = 'B';
    else if(s[n][2] == 'B') s[n][1] = 'B';
    else if(s[n][m - 1] == 'B') s[n][m] = 'B';//判断
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            printf("%c", s[i][j]);
        }
        printf("\n");
    }//输出
}
```
  - **核心实现思想**：根据 $n$ 和 $m$ 的奇偶性进行不同构造。奇数时直接按特定规律黑白交替输出；非奇数时，先构造黑白交替矩阵，再根据角上格子相邻情况调整一个白色角格为黑色。
- **作者：yangrunze（4星）**
  - **关键亮点**：从特殊情况入手，提出将左上角涂成白，其它全涂成黑的构造方法，不管 $n$ 和 $m$ 是多少，都能满足 $B = W + 1$，思路独特且简洁。
  - **重点代码**：无（作者未贴代码）
  - **核心实现思想**：通过将左上角设为白色，其余部分设为黑色，使得 $B = 2$，$W = 1$，满足题目要求。
- **作者：xrdrsp（4星）**
  - **关键亮点**：通过手玩样例发现规律，即把 $i = 1$ 或 $j = 1$ 的格子（左上角除外）染黑，能满足 $B = W + 1$，方法简单直接，易于理解和实现。
  - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (i == 1 || j == 1) {
            puts("B");
        } else {
            puts("W");
        }
    }
}
```
  - **核心实现思想**：遍历矩阵，将第一行和第一列（除左上角）的格子设为黑色，其余设为白色，从而满足 $B = W + 1$ 的条件。

### 最优关键思路或技巧
对于构造类题目，从特殊情况入手，通过手玩样例找规律是很有效的方法。如yangrunze从全黑情况出发，通过调整左上角颜色得到答案；xrdrsp通过手玩样例发现特定行列染色规律。Warriors_Cat先构造基础的黑白交替矩阵，再根据奇偶性调整的方式，也体现了对问题分类讨论和逐步构造的思维。

### 拓展
此类构造题关键在于根据题目条件，通过尝试不同的初始状态（如全黑、全白），或者观察小数据样例的规律，找到满足条件的通用构造方法。类似题目通常需要打破常规思维，不拘泥于固定算法，多从不同角度思考尝试。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)：通过枚举和计数来解决问题，锻炼构造和计数的能力。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同的购买方案进行构造和比较，选择最优解，涉及贪心和构造的思路。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：结合二分查找和构造满足条件的跳跃方案，对构造思维和二分应用有较好的训练。 

---
处理用时：65.41秒