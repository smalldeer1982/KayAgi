# 题目信息

# Colorings and Dominoes

## 题目描述

You have a large rectangular board which is divided into $ n \times m $ cells (the board has $ n $ rows and $ m $ columns). Each cell is either white or black.

You paint each white cell either red or blue. Obviously, the number of different ways to paint them is $ 2^w $ , where $ w $ is the number of white cells.

After painting the white cells of the board, you want to place the maximum number of dominoes on it, according to the following rules:

- each domino covers two adjacent cells;
- each cell is covered by at most one domino;
- if a domino is placed horizontally (it covers two adjacent cells in one of the rows), it should cover only red cells;
- if a domino is placed vertically (it covers two adjacent cells in one of the columns), it should cover only blue cells.

Let the value of the board be the maximum number of dominoes you can place. Calculate the sum of values of the board over all $ 2^w $ possible ways to paint it. Since it can be huge, print it modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
3 4
**oo
oo*o
**oo```

### 输出

```
144```

## 样例 #2

### 输入

```
3 4
**oo
oo**
**oo```

### 输出

```
48```

## 样例 #3

### 输入

```
2 2
oo
o*```

### 输出

```
4```

## 样例 #4

### 输入

```
1 4
oooo```

### 输出

```
9```

# AI分析结果

### 题目内容中文重写
## 染色与多米诺骨牌

### 题目描述
你有一个大的矩形棋盘，它被划分为 $n \times m$ 个单元格（棋盘有 $n$ 行和 $m$ 列）。每个单元格要么是白色，要么是黑色。

你将每个白色单元格染成红色或蓝色。显然，染色的不同方法数为 $2^w$，其中 $w$ 是白色单元格的数量。

在给棋盘的白色单元格染色后，你想在上面放置最多数量的多米诺骨牌，需遵循以下规则：
- 每个多米诺骨牌覆盖两个相邻的单元格；
- 每个单元格最多被一个多米诺骨牌覆盖；
- 如果一个多米诺骨牌水平放置（它覆盖某一行中的两个相邻单元格），则它应只覆盖红色单元格；
- 如果一个多米诺骨牌垂直放置（它覆盖某一列中的两个相邻单元格），则它应只覆盖蓝色单元格。

设棋盘的值为你能放置的多米诺骨牌的最大数量。计算在所有 $2^w$ 种可能的染色方式下棋盘值的总和。由于这个总和可能非常大，将其对 $998\,244\,353$ 取模后输出。

### 样例 #1
#### 输入
```
3 4
**oo
oo*o
**oo
```
#### 输出
```
144
```

### 样例 #2
#### 输入
```
3 4
**oo
oo**
**oo
```
#### 输出
```
48
```

### 样例 #3
#### 输入
```
2 2
oo
o*
```
#### 输出
```
4
```

### 样例 #4
#### 输入
```
1 4
oooo
```
#### 输出
```
9
```

### 算法分类
递推

### 综合分析与结论
这些题解的核心思路都是利用“横着放的多米诺骨牌和竖着放的多米诺骨牌互不影响”这一特性，将问题拆分为计算行和列上连续白色格子段的贡献。不同题解主要区别在于计算连续白色格子段贡献的递推方程推导和实现方式。
- **思路对比**：多数题解通过定义状态，考虑不同的染色情况来推导递推方程；部分题解从计算每对相邻位置的贡献入手。
- **算法要点**：主要是递推求解连续白色格子段的方案数，再结合其他白色格子的染色情况计算总贡献。
- **解决难点**：关键在于准确推导递推方程，处理好取模运算，以及避免重复计数。

### 较高评分题解
- **Mophie（5星）**
    - **关键亮点**：思路清晰，详细推导了递推方程 $p_i=p_{i - 1}+2 \times p_{i - 2}+2^{i - 2}$，代码实现简洁明了，注释丰富。
- **E1_de5truct0r（4星）**
    - **关键亮点**：思路清晰，对递推方程的推导过程解释详细，复杂度分析准确。
- **shyyhs（4星）**
    - **关键亮点**：思路简洁，准确推导出递推方程 $f_i=f_{i - 1}+2*f_{i - 2}+2^{i - 2}$，代码实现规范。

### 重点代码
#### Mophie 的代码核心片段
```cpp
pown[0]=1;
for(int i=1;i<=n*m;i++)pown[i]=pown[i-1]*2%mod;
p[2]=1,p[3]=3;
for(int i=4;i<=n*m;i++)p[i]=(p[i-1]+2*p[i-2]+pown[i-2])%mod;
for(int i=0;i<n;i++)
{
    int now=0;
    for(int j=0;j<m;j++)
        if(a[i][j]==1)now++;
        else 
        {
            if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
            now=0;
        }
    if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
}
for(int i=0;i<m;i++)
{
    int now=0;
    for(int j=0;j<n;j++)
        if(a[j][i]==1)now++;
        else 
        {
            if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
            now=0;
        }
    if(now>=2)ans=(ans+p[now]*pown[cnt-now]%mod)%mod;
}
```
**核心实现思想**：先预处理 $2$ 的幂和递推数组 $p$，然后分别遍历行和列，统计连续白色格子段的长度，根据递推数组计算贡献并累加到答案中。

#### E1_de5truct0r 的递推方程
```plaintext
f_i=f_{i - 1}+2 \times f_{i - 2}+2^{i - 2}
```
**核心实现思想**：通过考虑最后两位的状态，推导出 $1 \times i$ 连续段的方案数的递推方程。

#### shyyhs 的代码核心片段
```cpp
p[0]=1;
for(int i=1;i<=n*m;i++)	p[i]=p[i-1]*2%mod;
for(int i=2;i<=len;i++)
{
    f[i]=(f[i-1]+2ll*f[i-2]+p[i-2])%mod;
}
ll ans=0;
for(int i=0;i<n;i++)
{
    int cnt=0;
    for(int j=0;j<m;j++)
    {
        if(s[i][j]=='o')
        {
            cnt++;
        }
        if(s[i][j]=='*'||j==m-1)
        {
            ans=(ans+f[cnt]*p[sum-cnt]%mod)%mod;
            cnt=0;
        }
    }
}
for(int i=0;i<m;i++)
{
    int cnt=0;
    for(int j=0;j<n;j++)
    {
        if(s[j][i]=='o')
        {
            cnt++;
        }
        if(s[j][i]=='*'||j==n-1)
        {
            ans=(ans+f[cnt]*p[sum-cnt]%mod)%mod;
            cnt=0;
        }
    }
}
```
**核心实现思想**：预处理 $2$ 的幂，根据递推方程计算连续白色格子段的方案数，然后分别遍历行和列，统计连续白色格子段的长度，计算贡献并累加到答案中。

### 最优关键思路或技巧
- **分治思想**：将问题拆分为行和列的贡献计算，降低问题复杂度。
- **递推求解**：通过定义状态和考虑不同情况，推导出递推方程，高效计算连续白色格子段的方案数。
- **取模运算**：在计算过程中及时取模，避免溢出。

### 可拓展之处
同类型题或类似算法套路：
- 其他棋盘放置问题，如放置其他形状的棋子，可借鉴分治和递推的思想。
- 计数类问题，通过分析不同状态和情况，推导递推方程求解。

### 推荐洛谷题目
- P1044 [栈](https://www.luogu.com.cn/problem/P1044)：递推求解栈的进出方案数。
- P1192 台阶问题：递推求解上台阶的方案数。
- P1996 约瑟夫问题：模拟和递推求解约瑟夫环问题。

### 个人心得摘录与总结
- **FutaRimeWoawaSete**：在实现 dp 时敲错，通过与其他代码对拍才发现错误，提醒我们在实现算法时要仔细，对拍是调试的有效手段。

---
处理用时：56.10秒