# 题目信息

# Madoka and Childish Pranks

## 题目描述

Madoka as a child was an extremely capricious girl, and one of her favorite pranks was drawing on her wall. According to Madoka's memories, the wall was a table of $ n $ rows and $ m $ columns, consisting only of zeroes and ones. The coordinate of the cell in the $ i $ -th row and the $ j $ -th column ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ) is $ (i, j) $ .

One day she saw a picture "Mahou Shoujo Madoka Magica" and decided to draw it on her wall. Initially, the Madoka's table is a table of size $ n \times m $ filled with zeroes. Then she applies the following operation any number of times:

Madoka selects any rectangular subtable of the table and paints it in a chess coloring (the upper left corner of the subtable always has the color $ 0 $ ). Note that some cells may be colored several times. In this case, the final color of the cell is equal to the color obtained during the last repainting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/382bdf687e9360fce9f9a4f6fec3edc2a2101bb5.png)White color means $ 0 $ , black means $ 1 $ . So, for example, the table in the first picture is painted in a chess coloring, and the others are not.For better understanding of the statement, we recommend you to read the explanation of the first test.

Help Madoka and find some sequence of no more than $ n \cdot m $ operations that allows you to obtain the picture she wants, or determine that this is impossible.

## 说明/提示

The description of the first test case is below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/5712ccf8799cc158d880a39b68cfedf66e8a3903.png)In the third test case, it is impossible to paint the desired picture.

In the fourth test case, the initial table is already the desired picture.

## 样例 #1

### 输入

```
4
4 5
01000
10100
01010
00110
2 3
001
010
3 3
110
101
000
1 1
0```

### 输出

```
4
1 1 3 3
3 3 4 4
4 3 4 4
4 2 4 3
1
1 2 2 3
-1
0```

# AI分析结果

### 题目重写
# 小圆与幼稚恶作剧

## 题目描述
小时候的小圆是个极其任性的女孩，她最喜欢的恶作剧之一就是在墙上画画。据小圆回忆，这面墙是一个有 $n$ 行和 $m$ 列的表格，仅由 $0$ 和 $1$ 组成。第 $i$ 行第 $j$ 列（$1 \le i \le n$，$1 \le j \le m$）的单元格坐标为 $(i, j)$ 。

有一天，她看到一幅《魔法少女小圆》的图片，决定在墙上画出来。最初，小圆的表格是一个大小为 $n \times m$ 且全为 $0$ 的表格。然后她可以任意多次应用以下操作：

小圆选择表格中的任意一个矩形子表格，并以棋盘格方式染色（子表格的左上角始终为颜色 $0$ ）。注意，有些单元格可能会被染色多次。在这种情况下，单元格的最终颜色等于最后一次重绘时得到的颜色。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/382bdf687e9360fce9f9a4f6fec3edc2a2101bb5.png)白色表示 $0$ ，黑色表示 $1$ 。例如，第一张图片中的表格是以棋盘格方式染色的，而其他图片中的表格不是。为了更好地理解题意，建议你阅读第一个测试用例的解释。

帮助小圆找到一些不超过 $n \cdot m$ 次操作的序列，使她能够得到想要的图案，或者确定这是不可能的。

## 说明/提示
下面是第一个测试用例的描述。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/5712ccf8799cc158d880a39b68cfedf66e8a3903.png)在第三个测试用例中，无法绘制出所需的图案。

在第四个测试用例中，初始表格已经是所需的图案。

## 样例 #1
### 输入
```
4
4 5
01000
10100
01010
00110
2 3
001
010
3 3
110
101
000
1 1
0
```
### 输出
```
4
1 1 3 3
3 3 4 4
4 3 4 4
4 2 4 3
1
1 2 2 3
-1
0
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路较为统一，都基于以下要点：
 - **无解判定**：由于每次染色操作左上角必须为 $0$，所以若目标矩阵左上角为 $1$，则直接判定无解。
 - **染色策略**：对于矩阵中值为 $1$ 的格子，通过构造一个以其左边或上边格子为左上角的 $1\times2$ 或 $2\times1$ 矩形子表格进行染色。为避免后序操作覆盖已染色的黑色格子，采用从右下角往左上角的顺序遍历矩阵。

各题解的不同主要体现在代码实现细节，如变量命名、输入输出方式、数据结构使用等方面。

### 通用建议与扩展思路
解决此类构造问题，关键在于深入理解操作规则对目标状态的限制，通过分析特殊情况（如本题左上角的特殊性质）找到解题突破口。同时，合理设计构造顺序，确保每次操作不会破坏已满足的条件。对于类似题目，可以从操作规则、目标状态特点入手，尝试寻找局部构造方法并推广到整体。

### 相似知识点洛谷题目
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举与组合的方式解决问题，与本题构造特定序列思路类似，需考虑各种限制条件。
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：可通过动态规划或类似构造方案的思路解决，在一定限制下构造满足条件的方案。
 - [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：涉及到路径构造与搜索，与本题构造操作序列有相似之处，都需要在给定规则下寻找合适的构造方式。 

---
处理用时：31.94秒