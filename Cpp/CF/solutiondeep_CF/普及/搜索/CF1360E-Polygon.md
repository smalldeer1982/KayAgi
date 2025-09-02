# 题目信息

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写（中文）

**多边形**

**题目描述**

多边形不仅是一个开发问题的最佳平台，也是一个边长为 $n$ 的正方形矩阵，初始时每个单元格都填充字符 0。

在多边形上，进行了军事训练。士兵们在第一行的每个单元格上方放置了一门大炮，并在第一列的每个单元格左侧放置了一门大炮。因此，总共放置了 $2n$ 门大炮。

初始多边形（$n=4$）如下图所示。大炮发射字符 1。在任何时刻，最多只有一门大炮在发射。当 1 从大炮中飞出时，它会向前飞行（沿射击方向），直到碰到多边形边界或另一个 1。之后，它会停留在碰撞前的单元格中。请查看示例以更好地理解。

更正式地：

- 如果一门大炮位于第 $i$ 行，第一列的左侧，并发射 1，那么 1 从单元格 ($i$, $1$) 开始飞行，并最终停在某个单元格 ($i$, $j$)；
- 如果一门大炮位于第 $j$ 列，第一行的上方，并发射 1，那么 1 从单元格 ($1$, $j$) 开始飞行，并最终停在某个单元格 ($i$, $j$)。

例如，考虑以下射击序列：

1. 发射第 2 行的大炮。
2. 再次发射第 2 行的大炮。
3. 发射第 3 列的大炮。

你桌上有一份军事训练的报告。这份报告是一个边长为 $n$ 的正方形矩阵，由 0 和 1 组成。你想知道训练是否真的发生了。换句话说，是否存在一个射击序列，使得训练后你得到了给定的矩阵？

每门大炮可以进行任意次数的射击。训练前，多边形的每个单元格都包含 0。

**说明/提示**

第一个测试用例在题目描述中已经解释。

第二个测试用例的答案是 NO，因为任何大炮发射的 1 都会继续飞行。

**样例 #1**

**输入**

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111
```

**输出**

```
YES
NO
YES
YES
NO
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是判断给定的矩阵是否可以通过大炮发射 1 来生成。根据题意，1 的飞行必须被边界或另一个 1 阻挡，因此每个 1 的右侧或下侧必须有一个 1 或边界。否则，该矩阵无法通过大炮发射生成。

大多数题解都基于这一核心思路，通过遍历矩阵中的每个 1，检查其右侧和下侧是否满足条件。如果发现某个 1 的右侧和下侧都不满足条件，则输出 NO，否则输出 YES。

#### 最优关键思路或技巧

1. **边界处理**：最右列和最下行的 1 不需要检查，因为它们已经位于边界。
2. **遍历与条件判断**：遍历矩阵中的每个 1，检查其右侧和下侧是否有一个 1 或边界。
3. **提前终止**：一旦发现不满足条件的 1，立即输出 NO 并终止遍历，以提高效率。

#### 可拓展之处

类似的问题可以扩展到其他类型的矩阵填充问题，例如通过某种规则填充矩阵，然后判断矩阵是否符合该规则。这类问题通常需要仔细分析填充规则，并通过遍历矩阵来验证。

#### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 所选高分题解

#### 题解1：Zhoumy（5星）

**关键亮点**：
- 简洁明了的思路，直接遍历矩阵并检查每个 1 的右侧和下侧。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int j=1;j<n;j++)for(int k=1;k<n;k++)if(a[j][k]=='1'&&a[j][k+1]=='0'&&a[j+1][k]=='0')die=1;
if(die==0)cout<<"YES"<<endl;
else cout<<"NO"<<endl;
```

#### 题解2：Warriors_Cat（4星）

**关键亮点**：
- 通过预处理边界，简化了判断条件。
- 使用了递归的思想，进一步解释了问题的本质。

**核心代码**：
```cpp
for(int i=1;i<=n;i++) a[n + 1][i] = 1, a[i][n + 1] = 1;
a[n + 1][n + 1] = 1;
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(a[i][j] == 1 && !a[i + 1][j] && !a[i][j + 1]){
            flag = 0;
            puts("NO");
            break;
        }
    }
    if(!flag) break;
}
if(flag) puts("YES");
```

#### 题解3：rui_er（4星）

**关键亮点**：
- 通过数学归纳法的思想，解释了判断条件的正确性。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for(int i=1;i<n;i++){
    for(int j=1;j<n;j++){
        if(a[i][j] && !a[i][j+1] && !a[i+1][j]){
            book = false;
            break;
        }
    }
    if(!book) break;
}
if(book) puts("YES");
else puts("NO");
```

### 个人心得摘录

- **Zhoumy**：通过简单的遍历和条件判断，直接解决了问题，代码简洁高效。
- **Warriors_Cat**：通过预处理边界，简化了判断条件，进一步解释了问题的本质。
- **rui_er**：通过数学归纳法的思想，解释了判断条件的正确性，代码简洁清晰。

---
处理用时：45.45秒