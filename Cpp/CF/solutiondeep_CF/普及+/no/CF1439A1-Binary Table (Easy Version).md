# 题目信息

# Binary Table (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is in the number of possible operations that can be made. You can make hacks if and only if you solved both versions of the problem.

You are given a binary table of size $ n \times m $ . This table consists of symbols $ 0 $ and $ 1 $ .

You can make such operation: select $ 3 $ different cells that belong to one $ 2 \times 2 $ square and change the symbols in these cells (change $ 0 $ to $ 1 $ and $ 1 $ to $ 0 $ ).

Your task is to make all symbols in the table equal to $ 0 $ . You are allowed to make at most $ 3nm $ operations. You don't need to minimize the number of operations.

It can be proved that it is always possible.

## 说明/提示

In the first test case, it is possible to make only one operation with cells $ (1, 1) $ , $ (2, 1) $ , $ (2, 2) $ . After that, all symbols will be equal to $ 0 $ .

In the second test case:

- operation with cells $ (2, 1) $ , $ (3, 1) $ , $ (3, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>011<br></br>001<br></br>000<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (1, 3) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>000<br></br>
  ```

In the fifth test case:

- operation with cells $ (1, 3) $ , $ (2, 2) $ , $ (2, 3) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>010<br></br>110<br></br>
  ```
- operation with cells $ (1, 2) $ , $ (2, 1) $ , $ (2, 2) $ . After it the table will be: ```
  <pre class="verbatim"><br></br>000<br></br>000<br></br>
  ```

## 样例 #1

### 输入

```
5
2 2
10
11
3 3
011
101
110
4 4
1111
0110
0110
1111
5 5
01011
11001
00010
11011
10000
2 3
011
101```

### 输出

```
1
1 1 2 1 2 2
2 
2 1 3 1 3 2
1 2 1 3 2 3
4
1 1 1 2 2 2 
1 3 1 4 2 3
3 2 4 1 4 2
3 3 4 3 4 4
4
1 2 2 1 2 2 
1 4 1 5 2 5 
4 1 4 2 5 1
4 4 4 5 3 4
2
1 3 2 2 2 3
1 2 2 1 2 2```

# AI分析结果

### 题目翻译
# 二进制表格（简单版本）

## 题目描述
这是该问题的简单版本。不同版本之间的差异在于可进行的操作数量。当且仅当你解决了两个版本的问题时，才可以进行 Hack 操作。

给定一个大小为 $n \times m$ 的二进制表格。该表格由符号 $0$ 和 $1$ 组成。

你可以进行如下操作：选择属于同一个 $2 \times 2$ 正方形的 $3$ 个不同单元格，并更改这些单元格中的符号（将 $0$ 变为 $1$，将 $1$ 变为 $0$）。

你的任务是使表格中的所有符号都等于 $0$。允许你最多进行 $3nm$ 次操作。你不需要最小化操作次数。

可以证明这总是可行的。

## 说明/提示
在第一个测试用例中，仅对单元格 $(1, 1)$、$(2, 1)$、$(2, 2)$ 进行一次操作即可。之后，所有符号都将等于 $0$。

在第二个测试用例中：
- 对单元格 $(2, 1)$、$(3, 1)$、$(3, 2)$ 进行操作。之后表格将变为：
```
011
001
000
```
- 对单元格 $(1, 2)$、$(1, 3)$、$(2, 3)$ 进行操作。之后表格将变为：
```
000
000
000
```

在第五个测试用例中：
- 对单元格 $(1, 3)$、$(2, 2)$、$(2, 3)$ 进行操作。之后表格将变为：
```
010
110
```
- 对单元格 $(1, 2)$、$(2, 1)$、$(2, 2)$ 进行操作。之后表格将变为：
```
000
000
```

## 样例 #1
### 输入
```
5
2 2
10
11
3 3
011
101
110
4 4
1111
0110
0110
1111
5 5
01011
11001
00010
11011
10000
2 3
011
101
```

### 输出
```
1
1 1 2 1 2 2
2 
2 1 3 1 3 2
1 2 1 3 2 3
4
1 1 1 2 2 2 
1 3 1 4 2 3
3 2 4 1 4 2
3 3 4 3 4 4
4
1 2 2 1 2 2 
1 4 1 5 2 5 
4 1 4 2 5 1
4 4 4 5 3 4
2
1 3 2 2 2 3
1 2 2 1 2 2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心目标都是在不超过 $3nm$ 次操作的限制下，将给定的二进制表格中的所有元素变为 $0$。各题解的思路和实现方式各有不同：
- **J_Ignite**：核心思路是每三次操作还原一个点且不影响其他点。将找到的 $1$ 放到 $2\times2$ 矩阵中，通过三次特定的取反操作将其变为 $0$。针对矩阵边缘的 $1$ 进行了特判处理。
- **wzkdh**：采用模拟的方法，对矩阵中的元素进行逐行逐列的处理，根据相邻元素的不同情况进行相应的取反操作，最后对矩阵右下角的 $2\times2$ 子矩阵进行特殊处理。
- **TEoS**：按 $2\times2$ 子矩阵中 $1$ 的个数分为五种情况分别处理，最多 $4$ 次操作可处理完一个子矩阵。对于 $n$ 或 $m$ 为奇数的情况，先处理一行或一列使其变为 $0$。
- **引领天下**：先将每个 $2\times2$ 矩阵的左边两列变成 $0$，最后处理最后一行和最后一列，对于矩阵右下角的元素单独处理。
- **sgl654321**：将零散的 $1$ 聚集到右下角，先处理大部分元素使其变为 $0$，最后对右下角的 $2\times2$ 子矩阵进行分类讨论处理。
- **LookatSea**：提出暴力解决思路，通过对特定方阵的取反操作将右上角的 $1$ 变为 $0$。
- **qusia_MC**：直接暴力处理，对于每个为 $1$ 的点，通过三次特定的取反操作将其变为 $0$，并对矩阵边缘情况进行处理。
- **Ba_creeper**：对每一个 $2\times2$ 的矩阵的 $16$ 种不同搭配制定合理方案，使矩阵中的数字全部变为 $0$。
- **KSToki**：先将 $(1,1)$~$(n - 2,m - 2)$ 中的元素变为全 $0$，再处理最后两列和最后两行，最后特判最后一个 $2\times2$ 子矩阵。

这些题解的主要难点在于如何在不超过操作次数限制的情况下，设计出合理的操作方案将矩阵元素全部变为 $0$，同时要考虑矩阵边缘和角落的特殊情况。

### 所选题解
- **J_Ignite（4星）**
  - **关键亮点**：思路清晰，通过每三次操作还原一个点的方法，逻辑简单易懂。代码结构清晰，对矩阵边缘的 $1$ 进行了详细的特判处理，易于理解和实现。
  - **个人心得**：无

### 重点代码
```cpp
// J_Ignite 题解核心代码
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
        if (a[i][j] == '1')
            ans_1 += 3;
printf("%d\n", ans_1);
if (a[n][m] == '1') // 将要还原的1作为2*2矩阵右下角（最后一排最后一列的数字）（特判）
{
    printf("%d %d %d %d %d %d\n", n, m, n - 1, m, n, m - 1);	 // n-1,m-1
    printf("%d %d %d %d %d %d\n", n, m, n - 1, m, n - 1, m - 1); // n,m-1
    printf("%d %d %d %d %d %d\n", n, m, n, m - 1, n - 1, m - 1); // n-1,m
}
for (int i = 1; i < n; i++) // 将要还原的1作为2*2矩阵左下角（最后一排）（特判）
    if (a[i][m] == '1')
    {
        printf("%d %d %d %d %d %d\n", i, m, i + 1, m - 1, i, m - 1); // i+1,m
        printf("%d %d %d %d %d %d\n", i, m, i + 1, m, i + 1, m - 1); // i,m-1
        printf("%d %d %d %d %d %d\n", i, m, i + 1, m, i, m - 1);	 // i+1,m-1
    }
for (int i = 1; i < m; i++) // 将要还原的1作为2*2矩阵右上角（最后一列）（特判）
    if (a[n][i] == '1')
    {
        printf("%d %d %d %d %d %d\n", n, i, n - 1, i, n - 1, i + 1); // n,i+1
        printf("%d %d %d %d %d %d\n", n, i, n, i + 1, n - 1, i + 1); // n-1,i
        printf("%d %d %d %d %d %d\n", n, i, n - 1, i, n, i + 1);	 // n-1,i+1
    }
for (int i = 2; i <= n; i++) // 将要还原的1作为2*2矩阵左上角
    for (int j = 2; j <= m; j++)
        if (a[i - 1][j - 1] == '1')
        {
            printf("%d %d %d %d %d %d\n", i - 1, j - 1, i, j - 1, i - 1, j); // i,j
            printf("%d %d %d %d %d %d\n", i - 1, j - 1, i - 1, j, i, j);	 // i-1,j
            printf("%d %d %d %d %d %d\n", i - 1, j - 1, i, j, i, j - 1);	 // i,j-1
        }
```
**核心实现思想**：先统计矩阵中 $1$ 的个数，每个 $1$ 需要三次操作，输出操作次数。然后对矩阵边缘的 $1$ 进行特判处理，最后处理矩阵内部的 $1$，每次输出三次操作的坐标。

### 扩展思路
同类型题可能会改变操作规则或限制条件，例如改变操作的单元格数量、改变目标矩阵的元素值等。类似的算法套路通常是对矩阵进行分块处理，针对不同情况制定相应的操作策略，同时要注意边界情况的处理。

### 洛谷题目推荐
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：涉及矩阵的覆盖和模拟操作。
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)：模拟比赛过程，根据规则进行结果统计。
3. [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)：模拟内存管理过程，根据规则进行页面替换。

---
处理用时：67.83秒