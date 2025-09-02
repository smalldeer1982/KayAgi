# 题目信息

# Wooden Fence

## 题目描述

Vasya has recently bought some land and decided to surround it with a wooden fence.

He went to a company called "Wooden board" that produces wooden boards for fences. Vasya read in the catalog of products that the company has at its disposal $ n $ different types of wood. The company uses the $ i $ -th type of wood to produce a board of this type that is a rectangular $ a_{i} $ by $ b_{i} $ block.

Vasya decided to order boards in this company and build a fence from them. It turned out that the storehouse of the company is so large that Vasya can order arbitrary number of boards of every type. Note that Vasya is allowed to turn the boards as he builds the fence. However, Vasya cannot turn square boards.

Vasya is required to construct a fence of length $ l $ , however, an arbitrary fence won't do. Vasya wants his fence to look beautiful. We'll say that a fence is beautiful if and only if the following two conditions are fulfilled:

- there are no two successive boards of the same type
- the first board of the fence has an arbitrary length, and the length of each subsequent board equals the width of the previous one

In other words, the fence is considered beautiful, if the type of the $ i $ -th board in the fence is different from the $ i-1 $ -th board's type; besides, the $ i $ -th board's length is equal to the $ i-1 $ -th board's width (for all $ i $ , starting from 2).

Now Vasya wonders, how many variants of arranging a fence for his land exist. Your task is to count the number of different beautiful fences of length $ l $ .

Two fences will be considered the same if the corresponding sequences of fence boards types and rotations are the same, otherwise the fences are different. Since the sought number can be large enough, you need to calculate the answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample there are exactly two variants of arranging a beautiful fence of length 3:

- As the first fence board use the board of the first type of length 1 and width 2. As the second board use board of the second type of length 2 and width 3.
- Use one board of the second type after you turn it. That makes its length equal 3, and width — 2.

## 样例 #1

### 输入

```
2 3
1 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 2
2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 6
2 1
3 2
2 5
3 3
5 1
2 1
```

### 输出

```
20
```

# AI分析结果

### 题目内容
# 木栅栏

## 题目描述
瓦夏最近买了一些土地，决定用木栅栏把它围起来。

他去了一家名为“木板”的公司，该公司生产用于栅栏的木板。瓦夏在产品目录中看到，公司有 $n$ 种不同类型的木材。公司用第 $i$ 种木材生产的这种类型的木板是一个 $a_{i}$×$b_{i}$ 的矩形木块。

瓦夏决定在这家公司订购木板并用它们来建造栅栏。结果发现公司的仓库非常大，瓦夏可以订购任意数量的每种类型的木板。注意，瓦夏在建造栅栏时可以转动木板。然而，瓦夏不能转动正方形木板。

瓦夏需要建造一个长度为 $l$ 的栅栏，然而，任意的栅栏是不行的。瓦夏希望他的栅栏看起来美观。我们说一个栅栏是美观的，当且仅当满足以下两个条件：
- 没有两块连续的木板是同一类型
- 栅栏的第一块木板有任意长度，并且后续每块木板的长度等于前一块木板的宽度

换句话说，如果栅栏中第 $i$ 块木板的类型与第 $i - 1$ 块木板的类型不同；此外，第 $i$ 块木板的长度等于第 $i - 1$ 块木板的宽度（对于所有 $i$，从 2 开始），那么这个栅栏就被认为是美观的。

现在瓦夏想知道，为他的土地安排栅栏有多少种方案。你的任务是计算长度为 $l$ 的不同美观栅栏的数量。

如果两个栅栏对应的栅栏木板类型和旋转顺序相同，则认为这两个栅栏是相同的，否则它们是不同的。由于所求的数量可能非常大，你需要计算答案对 $1000000007$（$10^{9}+7$）取模的结果。

## 说明/提示
在第一个样例中，恰好有两种安排长度为 3 的美观栅栏的方案：
- 作为第一块栅栏木板，使用第一种类型的木板，长度为 1，宽度为 2。作为第二块木板，使用第二种类型的木板，长度为 2，宽度为 3。
- 使用一块第二种类型的木板并将其转动。这样它的长度变为 3，宽度变为 2。

## 样例 #1
### 输入
```
2 3
1 2
2 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
1 2
2 2
```
### 输出
```
1
```

## 样例 #3
### 输入
```
6 6
2 1
3 2
2 5
3 3
5 1
2 1
```
### 输出
```
20
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均采用动态规划算法解决问题，核心思路是通过定义合适的状态和状态转移方程来计算满足条件的栅栏搭建方案数。主要区别在于状态的定义方式，不同的状态定义导致转移方程和实现细节有所不同。难点在于如何根据栅栏的两个限制条件（相邻木板不同类型且后一块木板长度等于前一块木板宽度）准确设计状态和转移方程，同时要处理好木板可旋转但正方形木板不能重复计算等细节。

### 所选的题解
- **作者：pythoner713 (5星)**
    - **关键亮点**：思路清晰，状态定义简洁明了，$f[i][j]$ 表示当前栅栏长度为 $i$，最后一块木板种类为 $j$ 的方案数。通过拆分非正方形木板并记录原种类来处理木板旋转问题，代码实现简洁高效，注释详细。
    - **重点代码 - 核心实现思想**：先将非正方形木板拆分成两种不同摆放方式并记录原种类，然后通过三层循环枚举当前长度、当前木板和上一块木板，根据条件进行状态转移，最后累加所有长度为 $l$ 的方案数。
```cpp
int main(){
    cin >> n >> l;
    for(int i = 1; i <= n; i++){
        c[++cnt] = i;
        cin >> a[cnt] >> b[cnt];
        if(a[cnt]!= b[cnt]){
            c[++cnt] = i;
            a[cnt] = b[cnt - 1];
            b[cnt] = a[cnt - 1];
        }
    }
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= cnt; j++){
            for(int k = 0; k <= cnt; k++){
                if(c[j] == c[k]) continue;
                if(!k && a[j] == i) f[i][j]++;
                else if(a[j] == b[k] && i > a[j]){
                    f[i][j] = (f[i][j] + f[i - a[j]][k]) % p;
                }
            }
        }
    }
    for(int i = 1; i <= cnt; i++) ans = (ans + f[l][i]) % p;
    cout << ans;
    return 0;
}
```
- **作者：_segmenttree (4星)**
    - **关键亮点**：状态定义考虑全面，$dp_{i,j,2}$ 表示现在放的种类为 $i$，长度为 $j$，长是 $a_i$ 或 $b_i$，通过四维循环实现状态转移，逻辑较为清晰。
    - **重点代码 - 核心实现思想**：先初始化每种木板直接放置的情况，然后通过四层循环枚举当前长度、当前木板、上一块木板以及上一块木板的摆放方式，根据条件进行状态转移，最后累加长度为 $l$ 的所有方案数。
```cpp
signed main() {
    int n,l;
    scanf("%lld%lld",&n,&l);
    for(int i=1;i<=n;i++) 
        scanf("%lld%lld",&a[i],&b[i]);
    for(int i=1;i<=l;i++)
        for(int j=1;j<=n;j++) {
            if(a[j]==i) dp[i][j][0]++;
            if(b[j]==i) dp[i][j][1]++;
        }
    for(int i=1;i<=l;i++)
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            {
                if(j==k) continue;
                if(a[j]==a[k]&&i>a[j]&&dp[i-a[j]][k][1]) dp[i][j][0]=(dp[i][j][0]+dp[i-a[j]][k][1])%mod;
                if(a[j]==b[k]&&i>a[j]&&a[k]!=b[k]&&dp[i-a[j]][k][0]) dp[i][j][0]=(dp[i][j][0]+dp[i-a[j]][k][0])%mod; 
                if(b[j]==b[k]&&i>b[j]&&dp[i-b[j]][k][0]) dp[i][j][1]=(dp[i][j][1]+dp[i-b[j]][k][0])%mod;
                if(b[j]==a[k]&&i>b[j]&&a[k]!=b[k]&&dp[i-b[j]][k][1]) dp[i][j][1]=(dp[i][j][1]+dp[i-b[j]][k][1])%mod; 
            }
    int ans=0;
    for(int i=1;i<=n;i++) {
        ans+=dp[l][i][0],ans%=mod;
        if(a[i]!=b[i]) ans+=dp[l][i][1],ans%=mod;
    }
    printf("%lld",ans);
    return 0;
}
```
- **作者：C6H14 (4星)**
    - **关键亮点**：状态定义 $f[i][j][0/1]$ 直观表示拼出长度为 $i$ 的栅栏，最后一块栅栏是第 $j$ 种木板且有无旋转的方案数，状态转移方程通过分类讨论详细列出，代码实现与方程对应较好。
    - **重点代码 - 核心实现思想**：通过三层循环枚举栅栏总长度、最后一块木板种类以及倒数第二块木板种类，根据是否为第一块木板以及木板的长宽关系进行分类讨论并状态转移，最后累加长度为 $l$ 的所有方案数。
```cpp
int main()
{
    n=read(),l=read();
    for (register int i=1;i<=n;++i)
        a[i]=read(),b[i]=read();
    for (register int i=1;i<=l;++i)
        for (register int j=1;j<=n;++j)
            for (register int k=0;k<=n;++k)
                if (j!=k)
                {
                    if (!k && a[j]==i)
                        ++f[i][j][0];
                    else
                    {
                        if (i>a[j] && a[j]==b[k])
                            f[i][j][0]=(f[i][j][0]+f[i-a[j]][k][0])%maxn;
                        if (i>a[j] && a[j]==a[k])
                            f[i][j][0]=(f[i][j][0]+f[i-a[j]][k][1])%maxn;
                    }
                    if (a[j]==b[j])
                        continue;
                    if (!k && b[j]==i)
                        ++f[i][j][1];
                    else
                    {
                        if (i>b[j] && b[j]==b[k])
                            f[i][j][1]=(f[i][j][1]+f[i-b[j]][k][0])%maxn;
                        if (i>b[j] && b[j]==a[k])
                            f[i][j][1]=(f[i][j][1]+f[i-b[j]][k][1])%maxn;
                    }
                }
    for (register int i=1;i<=n;++i)
        ans=(ans+f[l][i][0]+f[l][i][1])%maxn;
    write(ans);
    return 0;
}
```

### 最优关键思路或技巧
- **状态定义技巧**：选择合适的状态定义是解决问题的关键，如 `pythoner713` 的题解中，将状态定义为当前栅栏长度和最后一块木板种类，使得状态转移方程简洁明了，易于实现。
- **处理木板旋转**：对于非正方形木板，通过拆分或在状态中增加维度来处理其旋转情况，同时注意正方形木板不能重复计算。

### 拓展思路
同类型题通常围绕具有多种选择且选择之间存在限制条件的场景，通过动态规划解决方案计数问题。类似算法套路是根据问题的限制条件，合理定义状态和状态转移方程，注意边界条件和特殊情况处理。

### 洛谷相似题目推荐
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：通过动态规划求解棋盘上棋子从起点到终点的路径数量，需考虑障碍物限制，与本题通过动态规划计算满足条件的方案数类似。
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：从三角形顶部到底部的路径选择问题，通过动态规划找到最大路径和，同样涉及状态定义和转移方程设计。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：在给定矩阵上进行滑雪路径选择，要求路径长度最长，也是利用动态规划解决具有条件限制的方案优化问题。 

---
处理用时：102.66秒