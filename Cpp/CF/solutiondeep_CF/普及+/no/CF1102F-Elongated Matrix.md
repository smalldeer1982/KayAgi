# 题目信息

# Elongated Matrix

## 题目描述

You are given a matrix $ a $ , consisting of $ n $ rows and $ m $ columns. Each cell contains an integer in it.

You can change the order of rows arbitrarily (including leaving the initial order), but you can't change the order of cells in a row. After you pick some order of rows, you traverse the whole matrix the following way: firstly visit all cells of the first column from the top row to the bottom one, then the same for the second column and so on. During the traversal you write down the sequence of the numbers on the cells in the same order you visited them. Let that sequence be $ s_1, s_2, \dots, s_{nm} $ .

The traversal is $ k $ -acceptable if for all $ i $ ( $ 1 \le i \le nm - 1 $ ) $ |s_i - s_{i + 1}| \ge k $ .

Find the maximum integer $ k $ such that there exists some order of rows of matrix $ a $ that it produces a $ k $ -acceptable traversal.

## 说明/提示

In the first example you can rearrange rows as following to get the $ 5 $ -acceptable traversal:

```
<br></br>5 3<br></br>10 8<br></br>4 3<br></br>9 9<br></br>
```

Then the sequence $ s $ will be $ [5, 10, 4, 9, 3, 8, 3, 9] $ . Each pair of neighbouring elements have at least $ k = 5 $ difference between them.

In the second example the maximum $ k = 0 $ , any order is $ 0 $ -acceptable.

In the third example the given order is already $ 3 $ -acceptable, you can leave it as it is.

## 样例 #1

### 输入

```
4 2
9 9
10 8
5 3
4 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2 4
1 2 3 4
10 3 7 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 1
3
6
2
5
1
4
```

### 输出

```
3
```

# AI分析结果

### 题目翻译
## 拉长的矩阵

### 题目描述
给定一个矩阵 $a$，它由 $n$ 行和 $m$ 列组成，每个单元格中都包含一个整数。

你可以任意改变行的顺序（包括保持初始顺序），但不能改变行中单元格的顺序。在你选择了行的顺序之后，你按照以下方式遍历整个矩阵：首先从顶行到底行访问第一列的所有单元格，然后对第二列进行相同的操作，依此类推。在遍历过程中，你按照访问的顺序记录单元格中的数字，得到一个序列 $s_1, s_2, \dots, s_{nm}$。

如果对于所有的 $i$（$1 \le i \le nm - 1$），都有 $|s_i - s_{i + 1}| \ge k$，则称该遍历是 $k$ - 可接受的。

找出最大的整数 $k$，使得存在矩阵 $a$ 的某种行顺序，能够产生一个 $k$ - 可接受的遍历。

### 说明/提示
在第一个样例中，你可以将行重新排列如下，以得到一个 $5$ - 可接受的遍历：
```
5 3
10 8
4 3
9 9
```
那么序列 $s$ 将是 $[5, 10, 4, 9, 3, 8, 3, 9]$。每对相邻元素之间的差值至少为 $k = 5$。

在第二个样例中，最大的 $k = 0$，任何顺序都是 $0$ - 可接受的。

在第三个样例中，给定的顺序已经是 $3$ - 可接受的，你可以保持原样。

### 样例 #1
#### 输入
```
4 2
9 9
10 8
5 3
4 3
```
#### 输出
```
5
```

### 样例 #2
#### 输入
```
2 4
1 2 3 4
10 3 7 3
```
#### 输出
```
0
```

### 样例 #3
#### 输入
```
6 1
3
6
2
5
1
4
```
#### 输出
```
3
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕如何找到矩阵行的排列顺序，使得遍历矩阵得到的序列中相邻元素差值的最小值最大。大部分题解采用了状态压缩动态规划的方法，利用 $n$ 范围小的特点，通过状态压缩来表示已经考虑的行集合。不同题解在状态定义、转移方程和实现细节上略有差异，部分题解还结合了二分答案或搜索的思想。

### 所选题解
- **Siyuan（4星）**
    - **关键亮点**：思路清晰，详细解释了状态压缩动态规划的原理，状态定义和转移方程明确，代码实现规范，注释较少但逻辑清晰。
    - **核心代码**：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N=17,M=1e4+5;
const int INF=1<<30;
int n,m,a[N][M],f[1<<N][N],g[N][N],h[N][N];

void init() {
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
        g[i][j]=INF,h[i][j]=INF;
        for(int k=1;k<=m;++k) g[i][j]=std::min(g[i][j],std::abs(a[i][k]-a[j][k]));
        for(int k=2;k<=m;++k) h[i][j]=std::min(h[i][j],std::abs(a[i][k-1]-a[j][k]));
    }
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;++i) for(int j=1;j<=m;++j) scanf("%d",&a[i][j]);
    init();
    int ans=0;
    for(int k=0;k<n;++k) {
        memset(f,0,sizeof(f));
        f[1<<k][k]=INF;
        for(int S=0;S<(1<<n);++S) for(int i=0;i<n;++i) if(S&(1<<i)) {
            for(int j=0;j<n;++j) {
                if(!(S&(1<<j))) f[S|(1<<j)][j]=std::max(f[S|(1<<j)][j],std::min(f[S][i],g[i][j]));
            }
        }
        for(int i=0;i<n;++i) {
            ans=std::max(ans,std::min(f[(1<<n)-1][i],h[k][i]));
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：
        1. `init` 函数预处理出 $g[i][j]$（第 $i$ 行和第 $j$ 行相邻的贡献）和 $h[i][j]$（第 $i$ 行为第一行，第 $j$ 行为最后一行时的贡献）。
        2. 枚举起点 $k$，初始化状态 $f[1<<k][k]=INF$。
        3. 通过状态转移方程 $f_{S\cup j,j}=\max\{\min(f_{S,i},\text{cost}(i,j))\}$ 进行状态转移。
        4. 最后枚举结束点 $i$，更新答案 $\text{Ans}=\max\{\min(f_{2^n - 1,i},\text{cost}'(k,i))\}$。

- **Eibon（4星）**
    - **关键亮点**：思路简洁明了，状态定义和转移与 Siyuan 的题解类似，代码结构清晰，使用了 `#define int long long` 避免了部分数据类型问题。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=20;
const int maxm=1e4+5;
const int INF=0x3f3f3f3f3f3f3f3f;
int n,m,ans;
int a[maxn][maxm],dp[(1<<16)+5][20],g[maxn][maxn],h[maxn][maxn];
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%lld",&a[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g[i][j]=h[i][j]=INF;
            for(int k=1;k<=m;k++){
                g[i][j]=min(g[i][j],abs(a[i][k]-a[j][k]));
                if(k>=2){
                    h[i][j]=min(h[i][j],abs(a[i][k]-a[j][k-1]));
                }
            }
        }
    }
    for(int k=1;k<=n;k++){
        memset(dp,0,sizeof dp);
        dp[(1<<(k-1))][k]=INF;
        for(int s=0;s<(1<<n);s++){
            for(int i=1;i<=n;i++){
                if(s&(1<<(i-1))){
                    for(int j=1;j<=n;j++){
                        if(!(s&(1<<(j-1)))){
                            dp[s|(1<<(j-1))][j]=max(dp[s|(1<<(j-1))][j],min(dp[s][i],g[i][j]));
                        }
                    }
                }
            }
        }
        for(int i=1;i<=n;i++){
            ans=max(ans,min(dp[(1<<n)-1][i],h[k][i]));
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
    - **核心实现思想**：与 Siyuan 的题解类似，先预处理 $g$ 和 $h$ 数组，然后枚举起点，进行状态转移，最后更新答案。

### 最优关键思路或技巧
- **状态压缩动态规划**：利用 $n$ 范围小的特点，用二进制数表示已经考虑的行集合，减少状态的表示空间。
- **预处理**：预先计算出两行之间的贡献，避免在状态转移过程中重复计算，提高效率。

### 拓展思路
同类型题或类似算法套路：
- 涉及矩阵操作和排列组合的动态规划问题，如求矩阵中某些元素排列的最优值。
- 状态压缩动态规划在其他问题中的应用，如旅行商问题（TSP）等。

### 推荐洛谷题目
1. [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
2. [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)
3. [P3959 [NOIP2017 提高组] 宝藏](https://www.luogu.com.cn/problem/P3959)

### 个人心得摘录与总结
- **hovny**：提到直接爆搜不可行，需要进行预处理和剪枝，如最优性剪枝和线段树的 $lowbit$ 操作，虽然时间复杂度理论上较高，但实际运行较快，因为两行之间的最小值比较难卡，时间比较稳定。总结：在搜索类问题中，合理的预处理和剪枝可以显著提高效率，即使理论复杂度较高，实际效果也可能较好。

---
处理用时：65.76秒