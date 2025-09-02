# 题目信息

# Two-Colored Dominoes

## 题目描述

There is an $ n\times m $ board divided into cells. There are also some dominoes on this board. Each domino covers two adjacent cells (that is, two cells that share a side), and no two dominoes overlap.

Piet thinks that this board is too boring and it needs to be painted. He will paint the cells of the dominoes black and white. He calls the painting beautiful if all of the following conditions hold:

- for each domino, one of its cells is painted white and the other is painted black;
- for each row, the number of black cells in this row equals the number of white cells in this row;
- for each column, the number of black cells in this column equals the number of white cells in this column.

Note that the cells that are not covered by dominoes are not painted at all, they are counted as neither black nor white.

Help Piet produce a beautiful painting or tell that it is impossible.

## 说明/提示

In the first test case, the answer is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1863D/c02597064063806335d0d205f181144db4826066.png)In the second test case, it is impossible to paint all cells the right way.

## 样例 #1

### 输入

```
3
4 6
..LR..
ULRU..
DLRDUU
..LRDD
5 4
.LR.
.UU.
UDDU
D..D
LR..
2 2
..
..```

### 输出

```
..WB..
WWBB..
BBWWWB
..BWBW
-1
..
..```

# AI分析结果

### 题目内容重写
# 双色多米诺

## 题目描述

有一个 $n \times m$ 的棋盘，被划分为若干单元格。棋盘上还放置了一些多米诺骨牌。每个多米诺骨牌覆盖两个相邻的单元格（即共享一条边的两个单元格），且没有两个多米诺骨牌重叠。

Piet 认为这个棋盘太单调了，需要上色。他将多米诺骨牌的单元格涂成黑色和白色。他称这种涂色为“美丽的”，如果满足以下所有条件：

- 对于每个多米诺骨牌，其中一个单元格被涂成白色，另一个被涂成黑色；
- 对于每一行，该行中黑色单元格的数量等于白色单元格的数量；
- 对于每一列，该列中黑色单元格的数量等于白色单元格的数量。

注意，未被多米诺骨牌覆盖的单元格不会被涂色，它们既不被视为黑色也不被视为白色。

帮助 Piet 生成一种美丽的涂色方案，或者告诉他这是不可能的。

## 说明/提示

在第一个测试用例中，答案如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1863D/c02597064063806335d0d205f181144db4826066.png)

在第二个测试用例中，无法正确涂色所有单元格。

## 样例 #1

### 输入

```
3
4 6
..LR..
ULRU..
DLRDUU
..LRDD
5 4
.LR.
.UU.
UDDU
D..D
LR..
2 2
..
..```

### 输出

```
..WB..
WWBB..
BBWWWB
..BWBW
-1
..
..```

### 算法分类
构造

### 综合分析与结论
该题的核心在于如何构造一种涂色方案，使得每一行和每一列的黑色和白色单元格数量相等。题解中大多数思路都集中在如何通过交替涂色的方式满足条件，并且通过统计每行和每列的骨牌数量来判断是否有解。

### 所选题解
1. **作者：Creeper_l (赞：9)**  
   - **星级：4.5**  
   - **关键亮点**：思路清晰，代码简洁，通过交替涂色的方式构造方案，且通过统计每行和每列的骨牌数量来判断是否有解。  
   - **个人心得**：作者提到通过模拟可以得出偶数一定可以分成两组，这一点在实际编码中非常有用。  
   - **核心代码**：
     ```cpp
     for(int i = 1;i <= n;i++)
         for(int j = 1;j <= m;j++)
             if(c[i][j] == 'U') ans[i][j] = tmp,ans[i + 1][j] = tmp ^ 1,tmp ^= 1;
     for(int j = 1;j <= m;j++)
         for(int i = 1;i <= n;i++)
             if(c[i][j] == 'L') ans[i][j] = tmp,ans[i][j + 1] = tmp ^ 1,tmp ^= 1;
     ```

2. **作者：ScottSuperb (赞：2)**  
   - **星级：4**  
   - **关键亮点**：将纵向和横向骨牌分开处理，采用黑白交替染色的策略，思路清晰。  
   - **核心代码**：
     ```cpp
     for(int i = 1; i <= n; ++i)
         for(int j = 1; j <= m; ++j) {
             if(a == 'U') ans[i][j] = row[i], row[i] ^= 1, ans[i + 1][j] = row[i];
             if(a == 'L') ans[i][j] = col[j], col[j] ^= 1, ans[i][j + 1] = col[j];
         }
     ```

3. **作者：One_JuRuo (赞：1)**  
   - **星级：4**  
   - **关键亮点**：从上往下、从左到右依次处理，确保每行和每列的黑白数量相等，思路清晰。  
   - **核心代码**：
     ```cpp
     for(int i = 1;i <= n;++i)
         for(int j = 1;j <= m;++j)
             if(ch[i][j]=='U') {
                 if(num[i][0]<=num[i][1]) ++num[i][0],ch[i][j]='B',++num[i+1][1],ch[i+1][j]='W';
                 else ++num[i][1],ch[i][j]='W',++num[i+1][0],ch[i+1][j]='B';
             }
     ```

### 最优关键思路或技巧
1. **交替涂色**：通过交替涂色的方式确保每行和每列的黑白数量相等。
2. **统计骨牌数量**：通过统计每行和每列的骨牌数量来判断是否有解，奇数数量一定无解。

### 可拓展之处
类似的问题可以扩展到更高维度的棋盘或不同类型的骨牌，例如三维棋盘或不同形状的骨牌。

### 推荐题目
1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

### 个人心得摘录
- **Creeper_l**：通过模拟可以得出偶数一定可以分成两组，这一点在实际编码中非常有用。
- **One_JuRuo**：从上往下、从左到右依次处理，确保每行和每列的黑白数量相等，思路清晰。

---
处理用时：35.58秒