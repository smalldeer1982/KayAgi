# 题目信息

# Gerrymandering

## 题目描述

We all steal a little bit. But I have only one hand, while my adversaries have two.

Álvaro Obregón



Álvaro and José are the only candidates running for the presidency of Tepito, a rectangular grid of $ 2 $ rows and $ n $ columns, where each cell represents a house. It is guaranteed that $ n $ is a multiple of $ 3 $ .

Under the voting system of Tepito, the grid will be split into districts, which consist of any $ 3 $ houses that are connected $ ^{\text{∗}} $ . Each house will belong to exactly one district.

Each district will cast a single vote. The district will vote for Álvaro or José respectively if at least $ 2 $ houses in that district select them. Therefore, a total of $ \frac{2n}{3} $ votes will be cast.

As Álvaro is the current president, he knows exactly which candidate each house will select. If Álvaro divides the houses into districts optimally, determine the maximum number of votes he can get.

 $ ^{\text{∗}} $ A set of cells is connected if there is a path between any $ 2 $ cells that requires moving only up, down, left and right through cells in the set.

## 说明/提示

The image below showcases the optimal arrangement of districts Álvaro can use for each test case in the example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

## 样例 #1

### 输入

```
4
3
AAA
AJJ
6
JAJAJJ
JJAJAJ
6
AJJJAJ
AJJAAA
9
AJJJJAJAJ
JAAJJJJJA```

### 输出

```
2
2
3
2```

# AI分析结果

### 题目内容重写

# 选区划分

## 题目描述

我们都会偷一点东西。但我只有一只手，而我的对手有两只手。

Álvaro Obregón

Álvaro 和 José 是竞选 Tepito 总统的唯二候选人。Tepito 是一个由 $2$ 行 $n$ 列组成的矩形网格，每个单元格代表一个房子。保证 $n$ 是 $3$ 的倍数。

在 Tepito 的投票系统中，网格将被划分为若干个选区，每个选区由任意 $3$ 个相连的房屋组成。每个房屋将属于且仅属于一个选区。

每个选区将投出一票。如果该选区中至少 $2$ 个房屋选择 Álvaro 或 José，则该选区将投票给相应的候选人。因此，总共将投出 $\frac{2n}{3}$ 票。

由于 Álvaro 是现任总统，他知道每个房屋将选择哪位候选人。如果 Álvaro 将房屋划分为选区时采取最优策略，请确定他能够获得的最大票数。

$^{\text{∗}}$ 一组单元格是相连的，如果它们之间可以通过上下左右移动的路径相连。

## 说明/提示

下图展示了 Álvaro 在每个测试用例中可以使用的选区最优划分。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

## 样例 #1

### 输入

```
4
3
AAA
AJJ
6
JAJAJJ
JJAJAJ
6
AJJJAJ
AJJAAA
9
AJJJJAJAJ
JAAJJJJJA```

### 输出

```
2
2
3
2```

### 题解分析与结论

#### 综合分析
本题的核心在于如何将 $2 \times n$ 的网格划分为若干个由 $3$ 个相连房屋组成的选区，并最大化 Álvaro 获得的票数。由于 $n$ 是 $3$ 的倍数，选区的划分方式有限，主要集中在“条状”和“拐角”两种形状。题解中主要采用了动态规划（DP）的方法来解决这一问题。

#### 题解对比
1. **Yorg 的题解**：
   - **思路**：使用轮廓线 DP，记录当前决策点的轮廓线状态，通过分类讨论不同状态之间的转移。
   - **难点**：轮廓线 DP 的状态定义和转移方程较为复杂，需要对不同形状的选区进行详细分析。
   - **评分**：4星，思路清晰，但状态转移方程较为复杂，代码实现难度较高。

2. **liugh_ 的题解**：
   - **思路**：使用 DP，记录第一行和第二行的已填长度差，通过状态压缩减少无效状态。
   - **难点**：状态压缩和转移方程的优化，特别是如何处理两行已填长度差超过 $1$ 的情况。
   - **评分**：5星，思路清晰，状态压缩优化得当，代码实现简洁高效。

3. **_O_v_O_ 的题解**：
   - **思路**：使用 DP，记录最后四个块的状态，通过分讨每种状态的拼合。
   - **难点**：状态定义和转移方程的细节处理，特别是如何确保选区的连通性。
   - **评分**：3星，思路较为复杂，代码实现细节较多，可读性一般。

#### 最优关键思路
liugh_ 的题解通过状态压缩和优化转移方程，有效地减少了无效状态，使得 DP 的实现更加简洁高效。这种方法在处理类似网格划分问题时具有较高的通用性。

#### 代码实现
```cpp
int f[n+5][3]{};
#define f(a,b) f[a][b+1]
#define calc(a,x,b,y,c,z) ((s[x][a]=='A')+(s[y][b]=='A')+(s[z][c]=='A')>=2)
f(0,-1)=f(0,1)=-1e9,f(0,0)=0;
for(int i=0;i<=n;i++){
    tomax(f(i+2,0),f(i,-1)+calc(i+1,0,i+2,0,i+2,1));
    tomax(f(i+3,-1),f(i,-1)+calc(i+1,0,i+2,0,i+3,0)+calc(i+2,1,i+3,1,i+4,1));
    tomax(f(i+3,0),f(i,0)+calc(i+1,0,i+2,0,i+3,0)+calc(i+1,1,i+2,1,i+3,1));
    tomax(f(i+2,1),f(i,0)+calc(i+1,0,i+2,0,i+1,1));
    tomax(f(i+1,-1),f(i,0)+calc(i+1,0,i+1,1,i+2,1));
    tomax(f(i+1,0),f(i,1)+calc(i+1,0,i,1,i+1,1));
    tomax(f(i+3,1),f(i,1)+calc(i+1,0,i+2,0,i+3,0)+calc(i,1,i+1,1,i+2,1));
}
cout<<f(n,0)<<'\n';
```

#### 拓展思路
类似的问题可以扩展到更高维度的网格划分，或者不同的选区形状。状态压缩和 DP 的方法在处理这类问题时具有较高的通用性。

#### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)
3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

---
处理用时：48.32秒