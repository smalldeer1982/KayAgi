# 题目信息

# Flood Fill

## 题目描述

You are given a line of $ n $ colored squares in a row, numbered from $ 1 $ to $ n $ from left to right. The $ i $ -th square initially has the color $ c_i $ .

Let's say, that two squares $ i $ and $ j $ belong to the same connected component if $ c_i = c_j $ , and $ c_i = c_k $ for all $ k $ satisfying $ i < k < j $ . In other words, all squares on the segment from $ i $ to $ j $ should have the same color.

For example, the line $ [3, 3, 3] $ has $ 1 $ connected component, while the line $ [5, 2, 4, 4] $ has $ 3 $ connected components.

The game "flood fill" is played on the given line as follows:

- At the start of the game you pick any starting square (this is not counted as a turn).
- Then, in each game turn, change the color of the connected component containing the starting square to any other color.

Find the minimum number of turns needed for the entire line to be changed into a single color.

## 说明/提示

In the first example, a possible way to achieve an optimal answer is to pick square with index $ 2 $ as the starting square and then play as follows:

- $ [5, 2, 2, 1] $
- $ [5, 5, 5, 1] $
- $ [1, 1, 1, 1] $

In the second example, a possible way to achieve an optimal answer is to pick square with index $ 5 $ as the starting square and then perform recoloring into colors $ 2, 3, 5, 4 $ in that order.

In the third example, the line already consists of one color only.

## 样例 #1

### 输入

```
4
5 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
4 5 2 2 1 3 5 5
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
4
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
#### Flood Fill

#### 题目描述
给定一行 $n$ 个彩色方块，从左到右依次编号为 $1$ 到 $n$。第 $i$ 个方块最初的颜色为 $c_i$。

如果 $c_i = c_j$，并且对于所有满足 $i < k < j$ 的 $k$ 都有 $c_i = c_k$，那么我们说方块 $i$ 和 $j$ 属于同一个连通分量。换句话说，从 $i$ 到 $j$ 这段区间内的所有方块颜色都应该相同。

例如，序列 $[3, 3, 3]$ 有 $1$ 个连通分量，而序列 $[5, 2, 4, 4]$ 有 $3$ 个连通分量。

“填充” 游戏在给定的这行方块上进行，规则如下：
- 游戏开始时，你可以选择任意一个起始方块（这一步不计入步数）。
- 然后，在每一轮游戏中，将包含起始方块的连通分量的颜色更改为其他任意颜色。

求将整行方块变成同一种颜色所需的最少步数。

#### 说明/提示
在第一个样例中，一种达到最优解的可能方式是选择索引为 $2$ 的方块作为起始方块，然后按以下步骤进行：
- $[5, 2, 2, 1]$
- $[5, 5, 5, 1]$
- $[1, 1, 1, 1]$

在第二个样例中，一种达到最优解的可能方式是选择索引为 $5$ 的方块作为起始方块，然后依次将颜色更改为 $2$、$3$、$5$、$4$。

在第三个样例中，这行方块本来就只有一种颜色。

#### 样例 #1
##### 输入
```
4
5 2 2 1
```
##### 输出
```
2
```

#### 样例 #2
##### 输入
```
8
4 5 2 2 1 3 5 5
```
##### 输出
```
4
```

#### 样例 #3
##### 输入
```
1
4
```
##### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解大多采用区间动态规划（区间 DP）的方法来解决问题。核心思路是将原问题转化为子问题，通过求解子问题的最优解来得到原问题的最优解。

#### 思路对比
- 大部分题解直接定义 $dp[i][j]$ 表示将区间 $[i, j]$ 内的方块染成同一种颜色所需的最少步数，然后根据区间两端颜色是否相同进行状态转移。
- 部分题解如 rui_er 和 MY（一名蒟蒻）的题解，增加了一个维度，$dp[i][j][bit]$ 表示将区间 $[i, j]$ 染成同一种颜色（$bit = 0$ 表示最左侧的颜色，$bit = 1$ 表示最右侧的颜色）所需的最少步数，考虑的情况更细致。

#### 算法要点
- **去重处理**：在输入时将相邻且颜色相同的方块合并为一个，减少不必要的计算，因为它们属于同一个连通分量。
- **状态转移**：
    - 若 $a[i] == a[j]$，则 $dp[i][j] = dp[i + 1][j - 1] + 1$。
    - 若 $a[i] != a[j]$，则 $dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1$。

#### 解决难点
- **重复连通分量的处理**：通过去重操作，将连续相同颜色的方块视为一个整体，避免了复杂的连通分量判断。
- **状态转移的设计**：根据区间两端颜色是否相同，合理设计状态转移方程，确保能得到最优解。

### 评分较高的题解
- **作者：lzpclxf (赞：22)，4星**
    - **亮点**：思路清晰，详细解释了去重的思路和区间 DP 的过程，代码简洁易懂。
    - **个人心得**：提到开数组要注意数据范围，否则可能会出现 MLE 或 RE 错误。
- **作者：rui_er (赞：13)，4星**
    - **亮点**：状态设计独特，增加了一个维度来考虑区间染成左侧或右侧颜色的情况，对状态转移方程的解释较为详细。
- **作者：MY（一名蒟蒻） (赞：4)，4星**
    - **亮点**：对区间 DP 的思路和状态设计解释得很清楚，适合初学者理解。

### 重点代码及核心实现思想
#### lzpclxf 的题解
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10101;
int num, n, a[N], fre, f[N][N];
int main () {
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf ("%d", &x);
        if (x != fre) a[++num] = x;
        fre = x;
    }
    for (int l = 1; l <= num; l++)
        for (int i = 1; i + l <= num; i++) {
            int j = i + l;
            if (a[i] == a[j]) f[i][j] = f[i + 1][j - 1] + 1;
            else f[i][j] = min (f[i + 1][j], f[i][j - 1]) + 1;
        }
    printf ("%d\n", f[1][num]);
    return 0;
}
```
**核心思想**：先对输入进行去重处理，将相邻且颜色相同的方块合并。然后使用区间 DP，枚举区间长度和左端点，根据区间两端颜色是否相同进行状态转移，最后输出将整个区间染成同一种颜色所需的最少步数。

#### rui_er 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5005, inf = 0x3f3f3f3f;

int n, a[N];
int dp[N][N][2];

void initDP() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            dp[i][j][0] = dp[i][j][1] = (i == j ? 0 : inf);
        }
    }
}
void updDP(int &a, int b) {a = min(a, b);}

int main() {
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    initDP(); 
    for(int j=1;j<=n;j++) {
        for(int i=j;i>=1;i--) {
            for(int bit=0;bit<=1;bit++) {
                int col = bit ? a[j] : a[i];
                if(i > 1) updDP(dp[i-1][j][0], dp[i][j][bit] + (col != a[i-1]));
                if(j < n) updDP(dp[i][j+1][1], dp[i][j][bit] + (col != a[j+1]));
            }
        }
    }
    printf("%d\n", min(dp[1][n][0], dp[1][n][1]));
    return 0;
}
```
**核心思想**：定义 $dp[i][j][bit]$ 表示将区间 $[i, j]$ 染成同一种颜色（$bit = 0$ 表示最左侧的颜色，$bit = 1$ 表示最右侧的颜色）所需的最少步数。初始化 $dp$ 数组，然后枚举区间右端点、左端点和 $bit$ 值，根据当前区间的颜色和相邻方块的颜色进行状态转移，最后输出将整个区间染成同一种颜色所需的最少步数。

#### MY（一名蒟蒻）的题解
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N=5e3+10;
int n,a[N],f[N][N][2]; 

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) f[i][i][0]=0;
    for(int len=1,j;len<=n;len++)
    {
        for(int i=1;i+len-1<=n;i++)
        {
            j=i+len-1;
            if(a[i] == a[i-1]) f[i-1][j][0]=min(f[i-1][j][0],f[i][j][0]);
            else f[i-1][j][0]=min(f[i-1][j][0],f[i][j][0]+1);
            if(a[j] == a[i-1]) f[i-1][j][0]=min(f[i-1][j][0],f[i][j][1]);
            else f[i-1][j][0]=min(f[i-1][j][0],f[i][j][1]+1);
            if(a[j] == a[j+1]) f[i][j+1][1]=min(f[i][j+1][1],f[i][j][1]);
            else f[i][j+1][1]=min(f[i][j+1][1],f[i][j][1]+1);
            if(a[i] == a[j+1]) f[i][j+1][1]=min(f[i][j+1][1],f[i][j][0]);
            else f[i][j+1][1]=min(f[i][j+1][1],f[i][j][0]+1);
        }
    }
    printf("%d",min(f[1][n][0],f[1][n][1]));
    return 0;
}
```
**核心思想**：同样定义 $dp[i][j][bit]$ 表示将区间 $[i, j]$ 染成同一种颜色（$bit = 0$ 表示最左侧的颜色，$bit = 1$ 表示最右侧的颜色）所需的最少步数。初始化 $dp$ 数组，然后枚举区间长度和左端点，根据区间两端颜色和相邻方块的颜色进行状态转移，最后输出将整个区间染成同一种颜色所需的最少步数。

### 最优关键思路或技巧
- **去重处理**：将相邻且颜色相同的方块合并为一个，减少不必要的计算，简化问题。
- **区间 DP**：通过枚举区间长度和左端点，利用状态转移方程求解子问题的最优解，从而得到原问题的最优解。

### 可拓展之处
同类型题或类似算法套路：
- 石子合并问题：同样是区间 DP 的经典应用，通过枚举区间长度和分割点来求解最优解。
- 矩阵链乘法问题：也是利用区间 DP，通过枚举区间长度和分割点来确定矩阵乘法的最优顺序。

### 推荐题目
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
- [P4170 [CQOI2007] 涂色](https://www.luogu.com.cn/problem/P4170)
- [P3146 [USACO16OPEN] 248 G](https://www.luogu.com.cn/problem/P3146)

### 个人心得摘录与总结
- **lzpclxf**：开数组要注意数据范围，否则可能会出现 MLE 或 RE 错误。
- **一只书虫仔**：发现数据有点水，dp 执行时不小心把去重后的 cnt 写成去重前的 $n$ 还过了。这提醒我们在做题时要仔细检查代码，确保逻辑的正确性。

---
处理用时：74.40秒