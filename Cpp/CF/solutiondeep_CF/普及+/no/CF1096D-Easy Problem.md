# 题目信息

# Easy Problem

## 题目描述

Vasya is preparing a contest, and now he has written a statement for an easy problem. The statement is a string of length $ n $ consisting of lowercase Latin latters. Vasya thinks that the statement can be considered hard if it contains a subsequence hard; otherwise the statement is easy. For example, hard, hzazrzd, haaaaard can be considered hard statements, while har, hart and drah are easy statements.

Vasya doesn't want the statement to be hard. He may remove some characters from the statement in order to make it easy. But, of course, some parts of the statement can be crucial to understanding. Initially the ambiguity of the statement is $ 0 $ , and removing $ i $ -th character increases the ambiguity by $ a_i $ (the index of each character is considered as it was in the original statement, so, for example, if you delete character r from hard, and then character d, the index of d is still $ 4 $ even though you delete it from the string had).

Vasya wants to calculate the minimum ambiguity of the statement, if he removes some characters (possibly zero) so that the statement is easy. Help him to do it!

Recall that subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.

## 说明/提示

In the first example, first two characters are removed so the result is ardh.

In the second example, $ 5 $ -th character is removed so the result is hhzawde.

In the third example there's no need to remove anything.

## 样例 #1

### 输入

```
6
hhardh
3 2 9 11 7 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
hhzarwde
3 2 6 9 4 8 7 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
6
hhaarr
1 2 3 4 5 6
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 简单问题

## 题目描述
瓦西亚正在准备一场竞赛，现在他已经为一道简单的题目写好了题目描述。题目描述是一个长度为 $n$ 的由小写拉丁字母组成的字符串。瓦西亚认为，如果这个描述中包含子序列 “hard”，那么这道题就可以被认为是难题；否则，这道题就是简单题。例如，“hard”、“hzazrzd”、“haaaaard” 可以被认为是难题的描述，而 “har”、“hart” 和 “drah” 则是简单题的描述。

瓦西亚不希望题目描述是难题。他可以从描述中删除一些字符，以使它变成简单题。但是，当然，描述的某些部分对于理解题目可能至关重要。最初，题目的歧义度为 $0$，删除第 $i$ 个字符会使歧义度增加 $a_i$（每个字符的索引被认为是它在原始描述中的索引，例如，如果你先从 “hard” 中删除字符 “r”，然后再删除字符 “d”，那么 “d” 的索引仍然是 $4$，即使你是从字符串 “had” 中删除它的）。

瓦西亚想计算出，如果他删除一些字符（可能不删除）以使题目描述变成简单题，那么题目的最小歧义度是多少。帮助他完成这个任务！

请记住，子序列是一个可以通过删除另一个序列中的一些元素而不改变剩余元素的顺序得到的序列。

## 说明/提示
在第一个样例中，前两个字符被删除，所以结果是 “ardh”。

在第二个样例中，第 $5$ 个字符被删除，所以结果是 “hhzawde”。

在第三个样例中，不需要删除任何字符。

## 样例 #1
### 输入
```
6
hhardh
3 2 9 11 7 1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
8
hhzarwde
3 2 6 9 4 8 7 1
```
### 输出
```
4
```

## 样例 #3
### 输入
```
6
hhaarr
1 2 3 4 5 6
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解均采用动态规划来解决问题，核心思路是定义合适的状态，通过状态转移方程计算最小歧义度。不同题解在状态定义和实现细节上有所不同，但本质都是围绕如何避免出现 “hard” 子序列并最小化删除字符的代价。

### 所选题解
- **floatery（5星）**
    - **关键亮点**：使用滚动数组，代码简洁，状态转移清晰，易于理解。
    - **核心代码**：
```cpp
#include <stdio.h>
long long min(long long a,long long b)
{
    return a<b?a:b;
}
long long dp[5],a[100001];
char str[100001];
int main()
{
    int n,i=0,ans=0;
    scanf("%d",&n);
    scanf("%s",str);
    for(i=0;i<n;i++)
    {
        scanf("%I64d",&a[i]);
    }
    for(i=0;i<n;i++)
    {
        switch(str[i])
        {
            case 'h': dp[1]+=a[i];break;
            case 'a': dp[2]=min(dp[1],dp[2]+a[i]);break;
            case 'r': dp[3]=min(dp[2],dp[3]+a[i]);break;
            case 'd': dp[4]=min(dp[3],dp[4]+a[i]);break;
        }
    }
    printf("%I64d\n",dp[4]);
    return 0;
}
```
    - **核心实现思想**：`dp[1]` 表示清除所有的 'h' 的代价，`dp[2]` 表示避免出现 'ha' 子序列的最小代价，以此类推。根据当前字符更新相应的 `dp` 值，最后输出 `dp[4]` 即为结果。
- **Priori_Incantatem（4星）**
    - **关键亮点**：思路清晰，对状态转移方程的解释详细，使用滚动数组优化空间。
    - **核心代码**：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn=100000+10,inf=(1ll<<60);
long long f[5],a[Maxn];
char c[5]={'f','h','a','r','d'};
char s[Maxn];
long long n,ans=inf;
int main()
{
    scanf("%lld",&n);
    scanf("%s",s+1);
    for(long long i=1;i<=n;++i)
        scanf("%lld",a+i);
    for(long long i=1;i<=n;++i)
        for(long long j=3;j>=0;--j)
            if(s[i]==c[j+1])
            {
                f[j]+=a[i];
                if(j)f[j]=min(f[j],f[j-1]);
            }
    for(long long i=0;i<4;++i)
        ans=min(ans,f[i]);
    printf("%lld\n",ans);
    return 0;
}
```
    - **核心实现思想**：`f[j]` 表示让原字符串满足最多包含 “hard” 的前 $j$ 个字符的最小修改代价。根据当前字符更新 `f` 数组，最后取 `f` 数组中的最小值作为结果。
- **ForTomorrow（4星）**
    - **关键亮点**：对动态规划的定义、初始化和状态转移方程解释详细，代码规范。
    - **核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

int f (char op) {
    if (op == 'h') return 1;
    if (op == 'a') return 2;
    if (op == 'r') return 3;
    if (op == 'd') return 4;
    return 0;
}

signed main(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> cost(n+1);
    vector<vector<ll>> dp(n+1, vector<ll>(5, INF));
    
    for (int i = 1; i <= 4; ++i) dp[0][i] = 0;
    for (int i = 1; i <= n; ++i) cin >> cost[i];
    
    for (int i = 1; i <= n; ++i) {
        int op = f(s[i-1]);
        for (int j = 1; j <= 4; ++j) {
            if (op != j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = min(dp[i-1][j-1], dp[i-1][j]+cost[i]);
        }
    }
    cout << *min_element(dp[n].begin()+1, dp[n].end()) << '\n';
    return 0;
}
```
    - **核心实现思想**：`dp[i][j]` 表示进行到第 $i$ 个字符时，不能包含 “hard” 的前 $j$ 个字符的最小代价。根据当前字符和 `f` 函数的返回值更新 `dp` 数组，最后取 `dp[n]` 数组中的最小值作为结果。

### 最优关键思路或技巧
- **状态定义**：通过定义合适的状态，如 `dp[i][j]` 表示前 $i$ 个字符中满足某种条件的最小代价，将问题转化为子问题的求解。
- **滚动数组优化**：在状态转移过程中，发现只需要用到前一层的状态，因此可以使用滚动数组将二维数组优化为一维数组，减少空间复杂度。

### 拓展思路
同类型题目通常涉及子序列或子串的处理，要求在满足一定条件的前提下，最小化或最大化某个代价。类似的算法套路包括定义合适的状态，根据当前状态和输入更新状态，最终得到最优解。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，与本题类似，都需要使用动态规划求解最优解。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划入门题，通过状态转移方程计算从顶部到底部的最大路径和。
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，与本题一样，需要运用动态规划的思想来解决。

### 个人心得摘录与总结
- **ForTomorrow**：提到正面思考问题会很复杂，所以想到使用动态规划，既可以保证状态的正确性又能获得最小的代价。总结：当正面思考问题困难时，可以尝试使用动态规划等算法来解决。
- **G_A_TS**：提醒要开 `long long`，避免数据溢出。总结：在处理可能出现大数值的问题时，要注意数据类型的选择。
- **Neil_Qian**：提到关同步可以加速，并且提醒关同步后不要用 `scanf`。总结：在追求代码效率时，可以使用一些加速技巧，但要注意相关的使用限制。

---
处理用时：65.86秒