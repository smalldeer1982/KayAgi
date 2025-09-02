# 题目信息

# Tiling Challenge

## 题目描述

One day Alice was cleaning up her basement when she noticed something very curious: an infinite set of wooden pieces! Each piece was made of five square tiles, with four tiles adjacent to the fifth center tile:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/ad6ce0df252a3db4eebc7f2ae8f0d041a8339ee0.png) By the pieces lay a large square wooden board. The board is divided into $ n^2 $ cells arranged into $ n $ rows and $ n $ columns. Some of the cells are already occupied by single tiles stuck to it. The remaining cells are free.Alice started wondering whether she could fill the board completely using the pieces she had found. Of course, each piece has to cover exactly five distinct cells of the board, no two pieces can overlap and every piece should fit in the board entirely, without some parts laying outside the board borders. The board however was too large for Alice to do the tiling by hand. Can you help determine if it's possible to fully tile the board?

## 说明/提示

The following sketches show the example boards and their tilings if such tilings exist:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/4aa3066acea41ad93dd59954e4030c273a6b97d8.png)

## 样例 #1

### 输入

```
3
#.#
...
#.#
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
##.#
#...
####
##.#
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
#.###
....#
#....
###.#
#####
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
5
#.###
....#
#....
....#
#..##
```

### 输出

```
NO
```

# AI分析结果

### 题目内容重写

#### 题目描述

有一天，爱丽丝在清理地下室时，发现了一组无限多的木块！每个木块由五个方形瓷砖组成，其中四个瓷砖与第五个中心瓷砖相邻：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/ad6ce0df252a3db4eebc7f2ae8f0d041a8339ee0.png)

在木块旁边放着一块大的方形木板。该木板被划分为 $n^2$ 个单元格，排列成 $n$ 行和 $n$ 列。一些单元格已经被瓷砖占据，剩下的单元格是空的。爱丽丝想知道是否可以用她找到的木块完全填满木板。当然，每个木块必须正好覆盖木板上的五个不同的单元格，且木块之间不能重叠，每个木块都应该完全适合木板，不能有部分超出木板的边界。然而，木板太大了，爱丽丝无法手工完成铺砖。你能帮助她确定是否可以完全铺满木板吗？

#### 说明/提示

以下草图展示了示例木板及其铺砖情况（如果存在）：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1150B/4aa3066acea41ad93dd59954e4030c273a6b97d8.png)

#### 样例 #1

##### 输入

```
3
#.#
...
#.#
```

##### 输出

```
YES
```

#### 样例 #2

##### 输入

```
4
##.#
#...
####
##.#
```

##### 输出

```
NO
```

#### 样例 #3

##### 输入

```
5
#.###
....#
#....
###.#
#####
```

##### 输出

```
YES
```

#### 样例 #4

##### 输入

```
5
#.###
....#
#....
....#
#..##
```

##### 输出

```
NO
```

### 算法分类

模拟

### 题解分析与结论

本题的核心思路是通过模拟铺砖的过程，判断是否可以用十字形的木块完全覆盖木板上的所有空单元格。各题解的主要思路都是从左上角开始遍历木板，找到可以作为十字形顶点的空单元格，并尝试放置木块。如果放置成功，则继续遍历；如果无法放置，则输出“NO”；如果所有空单元格都被成功覆盖，则输出“YES”。

### 评分较高的题解

#### 题解1：作者：Nuyoah_awa (赞：1)

**星级：4星**

**关键亮点：**
- 通过贪心策略从左上角开始遍历，确保每个空单元格都能被覆盖。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
bool search(int x, int y) {
    if (x < 0 || x >= n - 2 || y <= 0 || y >= n - 1) return false;
    for (int k = 0; k < 5; k++)
        if (s[x + cntx[k]][y + cnty[k]] == '#') return false;
    return true;
}
```

**实现思想：**
- 通过 `search` 函数检查当前点是否可以放置十字形木块。
- 如果可以放置，则将相关单元格标记为已覆盖。

#### 题解2：作者：Biuld (赞：1)

**星级：4星**

**关键亮点：**
- 将字符图转换为数字图，简化了判断逻辑。
- 通过判断空单元格的数量是否为5的倍数，提前排除不可能的情况。

**核心代码：**
```cpp
if (sum % 5) {
    cout << "NO";
    return 0;
}
```

**实现思想：**
- 将字符图转换为数字图，便于后续处理。
- 通过判断空单元格的数量是否为5的倍数，提前排除不可能的情况。

#### 题解3：作者：ModestCoder_ (赞：0)

**星级：4星**

**关键亮点：**
- 直接枚举整个矩阵，找到空单元格并尝试放置十字形木块。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
void work(int i, int j) {
    if (!a[i][j] || !a[i + 1][j] || !a[i + 1][j - 1] || !a[i + 1][j + 1] || !a[i + 2][j]) {
        puts("NO"); exit(0);
    }
    a[i][j] = a[i + 1][j] = a[i + 1][j - 1] = a[i + 1][j + 1] = a[i + 2][j] = 0;
}
```

**实现思想：**
- 通过 `work` 函数检查当前点是否可以放置十字形木块。
- 如果可以放置，则将相关单元格标记为已覆盖。

### 最优关键思路

- **贪心策略**：从左上角开始遍历木板，确保每个空单元格都能被覆盖。
- **提前判断**：通过判断空单元格的数量是否为5的倍数，提前排除不可能的情况。
- **模拟铺砖**：通过模拟放置十字形木块的过程，确保所有空单元格都被覆盖。

### 可拓展之处

- **类似问题**：类似的问题包括用特定形状的砖块覆盖矩阵、拼图游戏等。
- **优化思路**：可以通过更高效的遍历方式或剪枝策略，进一步优化算法。

### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1048 拼图](https://www.luogu.com.cn/problem/P1048)
3. [P1055 铺砖](https://www.luogu.com.cn/problem/P1055)

---
处理用时：41.24秒