# 题目信息

# Karen and Game

## 题目描述

On the way to school, Karen became fixated on the puzzle game on her phone!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/69d9eed46962e3cdadeae01ef67d1e4bd4bac050.png)The game is played as follows. In each level, you have a grid with $ n $ rows and $ m $ columns. Each cell originally contains the number $ 0 $ .

One move consists of choosing one row or column, and adding $ 1 $ to all of the cells in that row or column.

To win the level, after all the moves, the number in the cell at the $ i $ -th row and $ j $ -th column should be equal to $ g_{i,j} $ .

Karen is stuck on one level, and wants to know a way to beat this level using the minimum number of moves. Please, help her with this task!

## 说明/提示

In the first test case, Karen has a grid with $ 3 $ rows and $ 5 $ columns. She can perform the following $ 4 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/2c8fcc04f5be718b03f1b0d9aafd9c48834c67b9.png)In the second test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. It is clear that it is impossible to beat the level; performing any move will create three $ 1 $ s on the grid, but it is required to only have one $ 1 $ in the center.

In the third test case, Karen has a grid with $ 3 $ rows and $ 3 $ columns. She can perform the following $ 3 $ moves to beat the level:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815A/b5d0f3212dd0b57527e9775bb29c6dbecaf28d27.png)Note that this is not the only solution; another solution, among others, is col 1, col 2, col 3.

## 样例 #1

### 输入

```
3 5
2 2 2 3 2
0 0 0 1 0
1 1 1 2 1
```

### 输出

```
4
row 1
row 1
col 4
row 3
```

## 样例 #2

### 输入

```
3 3
0 0 0
0 1 0
0 0 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
1 1 1
1 1 1
1 1 1
```

### 输出

```
3
row 1
row 2
row 3
```

# AI分析结果

### 题目内容
# Karen和游戏

## 题目描述
在上学的路上，凯伦沉迷于手机上的益智游戏！

游戏玩法如下。在每一关，你有一个 $n$ 行 $m$ 列的网格。每个单元格最初都包含数字 $0$ 。
一次移动包括选择一行或一列，并将该行或该列中的所有单元格加 $1$ 。
要赢得这一关，在所有移动之后，第 $i$ 行和第 $j$ 列单元格中的数字应该等于 $g_{i,j}$ 。
凯伦被困在某一关，想知道如何用最少的移动次数通关。请帮她完成这个任务！

## 说明/提示
在第一个测试用例中，凯伦有一个 $3$ 行 $5$ 列的网格。她可以执行以下 $4$ 次移动来通关：

在第二个测试用例中，凯伦有一个 $3$ 行 $3$ 列的网格。很明显无法通关；执行任何移动都会在网格上创建三个 $1$ ，但要求中心只有一个 $1$ 。
在第三个测试用例中，凯伦有一个 $3$ 行 $3$ 列的网格。她可以执行以下 $3$ 次移动来通关：

注意这不是唯一的解决方案；例如，另一个解决方案是列 $1$ ，列 $2$ ，列 $3$ 。

## 样例 #1
### 输入
```
3 5
2 2 2 3 2
0 0 0 1 0
1 1 1 2 1
```
### 输出
```
4
row 1
row 1
col 4
row 3
```

## 样例 #2
### 输入
```
3 3
0 0 0
0 1 0
0 0 0
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
3 3
1 1 1
1 1 1
1 1 1
```
### 输出
```
3
row 1
row 2
row 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是将原问题转化为从给定方阵通过行或列减一操作使其变为全零方阵，并通过贪心策略来寻找最少操作次数。不同题解在具体实现贪心策略和判断无解情况上略有不同。有的通过优先处理行数或列数较少的方向（根据 $n$ 和 $m$ 的大小关系），有的通过同时尝试先处理行再处理列以及先处理列再处理行两种顺序并取操作次数小的结果。判断无解的方式主要是看最终方阵是否存在非零元素。

### 所选的题解
#### 作者：Lian_zy (赞：3)
- **星级**：4星
- **关键亮点**：思路清晰，通过反向思考将问题简化，代码实现直接，利用函数判断行或列操作的可行性，并在循环中根据 $n$ 和 $m$ 的大小优先选择行或列操作。
```cpp
bool row(int i) { 
    for (int j = 1; j <= m; j++) {
        if (a[i][j]) continue;
        return false; 
    }
    for (int j = 1; j <= m; j++) a[i][j]--;
    t[++ans].rc = i;
    t[ans].is_row = true;
    return true;
} 
bool col(int j) { 
    for (int i = 1; i <= n; i++) {
        if (a[i][j]) continue;
        return false;
    }
    for (int i = 1; i <= n; i++) a[i][j]--;
    t[++ans].rc = j;
    t[ans].is_row = false;
    return true;
} 
```
核心实现思想：`row` 函数和 `col` 函数分别判断对应行或列是否可进行减一操作，若可操作则执行减一并记录操作。

#### 作者：Na2PtCl6 (赞：2)
- **星级**：4星
- **关键亮点**：先分析无解情况，即通过每行每列减去最小值后仍有非零元素则无解。在有解情况下，根据 $n$ 和 $m$ 的大小关系，优先处理行数或列数较少的方向，减少操作次数。
```cpp
void solveR(){
    for(int i=1;i<=n;i++){
        int mini=0x7fffffff;
        for(int j=1;j<=m;j++)
            mini=min(mini,a[i][j]);
        for(int j=1;j<=m;j++)
            a[i][j]-=mini;
        while(mini--){
            ++tot;
            r.push_back(i);
        }
    }
}
void solveC(){
    for(int i=1;i<=m;i++){
        int mini=0x7fffffff;
        for(int j=1;j<=n;j++)
            mini=min(mini,a[j][i]);
        for(int j=1;j<=n;j++)
            a[j][i]-=mini;
        while(mini--){
            ++tot;
            c.push_back(i);
        }
    }
}
```
核心实现思想：`solveR` 函数和 `solveC` 函数分别对行和列进行操作，找到每行或每列的最小值并减去，同时记录操作次数和操作的行或列。

#### 作者：MrFish (赞：1)
- **星级**：4星
- **关键亮点**：考虑到先检查行再检查列可能不是最优解，通过两次遍历，一次先检查行再检查列，另一次先检查列再检查行，比较两种方式的操作次数，取较小值作为结果。
```cpp
void chkrow(int x)
{
    while(chk1_1(x))
    {
        ans[anscnt].dir="row";
        ans[anscnt].num=x;
        anscnt++;
        for(int i=1;i<=m;i++)
        {
            a[x][i]--;
        }
    }
} 
void chkcol(int y)
{
    while(chk2_1(y))
    {
        ans[anscnt].dir="col";
        ans[anscnt].num=y;
        anscnt++;
        for(int i=1;i<=n;i++)
        {
            a[i][y]--;
        }
    }
}
```
核心实现思想：`chkrow` 函数和 `chkcol` 函数分别对行和列进行减一操作，并记录操作结果，通过两次不同顺序的遍历得到两种操作方案并比较。

### 最优关键思路或技巧
1. **反向思考**：将原问题转化为从给定方阵通过行或列减一操作使其变为全零方阵，简化问题理解和处理。
2. **贪心策略**：根据 $n$ 和 $m$ 的大小关系，优先处理行数或列数较少的方向，能有效减少操作次数。同时，如MrFish题解中，通过比较两种不同操作顺序的结果来确保得到最少操作次数。

### 可拓展之处
同类型题通常围绕矩阵操作和最优策略选择，类似套路是将复杂的矩阵变换问题转化为更易处理的形式，利用贪心思想根据矩阵行列特性选择操作顺序。

### 洛谷相似题目推荐
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过合理排序来最大化或最小化某个值。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：典型的贪心问题，根据不同的条件（如接水时间）来安排顺序以达到最优结果。
3. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要通过分析游戏规则，利用贪心策略找出最优的游戏策略。 

---
处理用时：62.08秒