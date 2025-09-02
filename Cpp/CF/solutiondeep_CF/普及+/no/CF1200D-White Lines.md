# 题目信息

# White Lines

## 题目描述

Gildong has bought a famous painting software cfpaint. The working screen of cfpaint is square-shaped consisting of $ n $ rows and $ n $ columns of square cells. The rows are numbered from $ 1 $ to $ n $ , from top to bottom, and the columns are numbered from $ 1 $ to $ n $ , from left to right. The position of a cell at row $ r $ and column $ c $ is represented as $ (r, c) $ . There are only two colors for the cells in cfpaint — black and white.

There is a tool named eraser in cfpaint. The eraser has an integer size $ k $ ( $ 1 \le k \le n $ ). To use the eraser, Gildong needs to click on a cell $ (i, j) $ where $ 1 \le i, j \le n - k + 1 $ . When a cell $ (i, j) $ is clicked, all of the cells $ (i', j') $ where $ i \le i' \le i + k - 1 $ and $ j \le j' \le j + k - 1 $ become white. In other words, a square with side equal to $ k $ cells and top left corner at $ (i, j) $ is colored white.

A white line is a row or a column without any black cells.

Gildong has worked with cfpaint for some time, so some of the cells (possibly zero or all) are currently black. He wants to know the maximum number of white lines after using the eraser exactly once. Help Gildong find the answer to his question.

## 说明/提示

In the first example, Gildong can click the cell $ (2, 2) $ , then the working screen becomes:

```
<pre class="verbatim">BWWW<br></br>WWWW<br></br>WWWW<br></br>WWWB<br></br>
```

Then there are four white lines — the $ 2 $ -nd and $ 3 $ -rd row, and the $ 2 $ -nd and $ 3 $ -rd column.

In the second example, clicking the cell $ (2, 3) $ makes the $ 2 $ -nd row a white line.

In the third example, both the $ 2 $ -nd column and $ 5 $ -th row become white lines by clicking the cell $ (3, 2) $ .

## 样例 #1

### 输入

```
4 2
BWWW
WBBW
WBBW
WWWB
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 1
BWB
WWB
BWB
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3
BWBBB
BWBBB
BBBBB
BBBBB
WBBBW
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2 2
BW
WB
```

### 输出

```
4
```

## 样例 #5

### 输入

```
2 1
WW
WW
```

### 输出

```
4
```

# AI分析结果

### 题目内容中文重写
# 白线

## 题目描述
吉尔东买了一款著名的绘画软件 cfpaint。cfpaint 的工作屏幕是正方形的，由 $n$ 行和 $n$ 列的正方形单元格组成。行从 $1$ 到 $n$ 编号，从上到下；列从 $1$ 到 $n$ 编号，从左到右。位于第 $r$ 行和第 $c$ 列的单元格的位置表示为 $(r, c)$。cfpaint 中的单元格只有两种颜色——黑色和白色。

cfpaint 中有一个名为橡皮擦的工具。橡皮擦有一个整数大小 $k$（$1 \le k \le n$）。要使用橡皮擦，吉尔东需要点击一个单元格 $(i, j)$，其中 $1 \le i, j \le n - k + 1$。当点击单元格 $(i, j)$ 时，所有满足 $i \le i' \le i + k - 1$ 且 $j \le j' \le j + k - 1$ 的单元格 $(i', j')$ 都会变成白色。换句话说，一个边长为 $k$ 个单元格、左上角位于 $(i, j)$ 的正方形会被涂成白色。

白线是指没有任何黑色单元格的行或列。

吉尔东使用 cfpaint 工作了一段时间，所以一些单元格（可能为零个或全部）目前是黑色的。他想知道在恰好使用一次橡皮擦后，最多能有多少条白线。请帮助吉尔东找到他问题的答案。

## 说明/提示
在第一个示例中，吉尔东可以点击单元格 $(2, 2)$，然后工作屏幕变为：
```
BWWW
WWWW
WWWW
WWWB
```
然后有四条白线——第 $2$ 行和第 $3$ 行，以及第 $2$ 列和第 $3$ 列。

在第二个示例中，点击单元格 $(2, 3)$ 会使第 $2$ 行成为白线。

在第三个示例中，通过点击单元格 $(3, 2)$，第 $2$ 列和第 $5$ 行都变成了白线。

## 样例 #1
### 输入
```
4 2
BWWW
WBBW
WBBW
WWWB
```
### 输出
```
4
```

## 样例 #2
### 输入
```
3 1
BWB
WWB
BWB
```
### 输出
```
2
```

## 样例 #3
### 输入
```
5 3
BWBBB
BWBBB
BBBBB
BBBBB
WBBBW
```
### 输出
```
2
```

## 样例 #4
### 输入
```
2 2
BW
WB
```
### 输出
```
4
```

## 样例 #5
### 输入
```
2 1
WW
WW
```
### 输出
```
4
```

### 算法分类
差分

### 综合分析与结论
这些题解主要围绕如何找出在使用一次橡皮擦后，矩阵中最多的白线数量展开。多数题解的核心思路是分别处理行和列，找出每一行和每一列中黑色单元格的范围，判断能否通过一次擦除操作使其变为白线，再利用差分或前缀和的方法来统计不同擦除位置能增加的白线数量，最后找出最大值。

不同题解的区别在于具体实现方式，如 Koakuma 的题解详细解释了如何通过容斥原理更新差分矩阵，QwQcOrZ 的题解使用前缀和来计算每个擦除方案的贡献，Froggy 的题解则强调了二维差分的应用。

### 所选题解
- **Koakuma（5星）**
    - **关键亮点**：思路清晰，对每一步操作都有详细的解释和图示，代码实现规范，注释丰富。
    - **个人心得**：作者提到这是 CodeForces 比赛后根据草稿写的题解，为了把题讲明白困扰了很久，欢迎读者在评论区指出不懂的地方。
- **QwQcOrZ（4星）**
    - **关键亮点**：代码简短，使用前缀和的方法计算每个擦除方案的贡献，可读性较高。
- **Froggy（4星）**
    - **关键亮点**：提供了一种另类的二维差分思路，类比一维差分得出二维差分的实现方法，易于理解。

### 重点代码
#### Koakuma 的题解核心代码
```cpp
// 行操作
for (reg int i = 1; i <= N; ++i) {
    tot = r = 0; l = N + 1;
    for (reg int j = 1; j <= N; ++j)
        if (t[i][j]) l = min(l, j), r = max(r, j), tot++;
    if (!tot) Ans++;
    else if (r - l >= K) continue ;
    else {
        int x, y;
        x = max(1, i - K + 1), y = max(1, r - K + 1);
        sum[i][l]++; sum[i][y - 1]--;
        if (i >= K) sum[i - K][l]--, sum[i - K][y - 1]++;
    }
}
// 列操作
for (reg int i = 1; i <= N; ++i) {
    tot = r = 0; l = N + 1;
    for (reg int j = 1; j <= N; ++j)
        if (t[j][i]) l = min(l, j), r = max(r, j), tot++;
    if (!tot) Ans++;
    else if (r - l >= K) continue ;
    else {
        int x, y;
        x = max(1, i - K + 1), y = max(1, r - K + 1);
        sum[l][i]++; sum[y - 1][i]--;
        if (i >= K) sum[l][i - K]--, sum[y - 1][i - K]++;
    }
}
for (reg int i = N; i >= 1; --i)
    for (reg int j = N; j >= 1; --j)
        pra[i][j] = pra[i + 1][j] + pra[i][j + 1] - pra[i + 1][j + 1] + sum[i][j];
```
**核心实现思想**：先分别处理行和列，找出每行和每列中黑色单元格的最左和最右位置，若全为白色则直接统计到答案中，若黑色单元格范围大于橡皮擦大小则忽略，否则更新差分矩阵。最后通过倒推计算最终每个格点的格点值。

#### QwQcOrZ 的题解核心代码
```cpp
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
    {
        char c = getchar();
        while (c != 'B' && c != 'W') c = getchar();
        a[i][j] = a[i - 1][j] + (c == 'B');
        b[i][j] = b[i][j - 1] + (c == 'B');// 处理 a、b，前缀和数组
    }
for (int i = 1; i <= n; i++)
{
    tot += a[n][i] == 0;
    tot += b[i][n] == 0;// 计算修改前的答案
}
for (int i = k; i <= n; i++)
    for (int j = 1; j <= n; j++) x[i][j] = x[i][j - 1] + (a[i - k][j] == 0 && a[n][j] - a[i][j] == 0 && a[i][j] - a[i - k][j] > 0);
for (int j = k; j <= n; j++)
    for (int i = 1; i <= n; i++) y[i][j] = y[i - 1][j] + (b[i][j - k] == 0 && b[i][n] - b[i][j] == 0 && b[i][j] - b[i][j - k] > 0);// 处理 x、y，贡献数组
for (int i = k; i <= n; i++)
    for (int j = k; j <= n; j++) ans = max(ans, x[i][j] - x[i][j - k] + y[i][j] - y[i - k][j]);
```
**核心实现思想**：先计算行和列的前缀和数组，统计修改前的白线数量。然后根据条件计算每个位置的贡献数组，最后找出最大贡献并加上修改前的白线数量得到答案。

#### Froggy 的题解核心代码
```cpp
// 行的情况
for (int i = 1; i <= n; i++) {
    int l = inf, r = -inf;
    for (int j = 1; j <= n; j++) {
        if (mp[i][j] == 0) {
            l = min(l, j);
            r = max(r, j);
        }
    }
    if (l == inf && r == -inf) {
        cnt++;
    }
    else {
        if (r - l + 1 > k) continue;
        int X1 = max(1, i - k + 1), Y1 = max(1, r - k + 1), X2 = i, Y2 = l;
        a[X1][Y1]++;
        a[X2 + 1][Y2 + 1]++;
        a[X2 + 1][Y1]--;
        a[X1][Y2 + 1]--;
    }
}
// 列的情况
for (int i = 1; i <= n; i++) {
    int l = inf, r = -inf;
    for (int j = 1; j <= n; j++) {
        if (mp[j][i] == 0) {
            l = min(l, j);
            r = max(r, j);
        }
    }
    if (l == inf && r == -inf) {
        cnt++;
    }
    else {
        if (r - l + 1 > k) continue;
        int X1 = max(1, r - k + 1), Y1 = max(1, i - k + 1), X2 = l, Y2 = i;
        a[X1][Y1]++;
        a[X2 + 1][Y2 + 1]++;
        a[X2 + 1][Y1]--;
        a[X1][Y2 + 1]--;
    }
}
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + a[i][j];// 求二维前缀和
        ans = max(ans, f[i][j]);
    }
}
```
**核心实现思想**：分别处理行和列，找出每行和每列中黑色单元格的最左和最右位置，若全为白色则直接统计到答案中，若黑色单元格范围大于橡皮擦大小则忽略，否则更新二维差分矩阵。最后通过二维前缀和计算每个位置的贡献并找出最大值。

### 最优关键思路或技巧
- **二维差分**：通过二维差分可以高效地记录每个擦除位置能增加的白线数量，避免了重复计算。
- **分别处理行和列**：将行和列分开处理，简化了问题的复杂度。
- **预处理**：预处理出每行和每列中黑色单元格的范围，方便后续判断能否通过擦除操作使其变为白线。

### 可拓展之处
同类型题或类似算法套路：
- 涉及矩阵操作和范围修改的题目，如矩阵区域修改、区间染色等问题，都可以考虑使用差分或前缀和的方法来优化时间复杂度。
- 对于需要统计满足某种条件的行或列数量的问题，可以借鉴本题分别处理行和列的思路。

### 推荐洛谷题目
- P1502 窗口的星星：同样涉及二维差分的应用。
- P3397 地毯：经典的二维差分练习题。
- P2367 语文成绩：一维差分的应用，可以帮助理解差分的基本思想。

### 个人心得摘录与总结
- **Koakuma**：写题解时为了把题讲明白困扰很久，说明将复杂的思路清晰地表达出来有一定难度，同时也体现了作者对题解质量的重视。
- **fsy_juruo**：当场打比赛时没调出来，模拟赛又忘记做法，提醒我们要对做过的题目进行总结和复习，加深对算法的理解和记忆。
- **破壁人五号**：尝试了一种玄学复杂度的做法，虽然一开始对复杂度存疑，但最终通过了测试，说明在竞赛中可以勇于尝试不同的思路，不要被常规思维限制。

---
处理用时：89.81秒