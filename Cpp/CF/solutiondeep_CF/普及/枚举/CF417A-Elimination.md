# 题目信息

# Elimination

## 题目描述

The finalists of the "Russian Code Cup" competition in 2214 will be the participants who win in one of the elimination rounds.

The elimination rounds are divided into main and additional. Each of the main elimination rounds consists of $ c $ problems, the winners of the round are the first $ n $ people in the rating list. Each of the additional elimination rounds consists of $ d $ problems. The winner of the additional round is one person. Besides, $ k $ winners of the past finals are invited to the finals without elimination.

As a result of all elimination rounds at least $ n·m $ people should go to the finals. You need to organize elimination rounds in such a way, that at least $ n·m $ people go to the finals, and the total amount of used problems in all rounds is as small as possible.

## 样例 #1

### 输入

```
1 10
7 2
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2
2 1
2
```

### 输出

```
0
```

# AI分析结果

### 题目中文重写
# 淘汰赛

## 题目描述
2214年“俄罗斯代码杯”比赛的决赛选手将是在某一场淘汰赛中获胜的参赛者。

淘汰赛分为主要淘汰赛和附加淘汰赛。每场主要淘汰赛包含 $c$ 道题，该轮比赛的获胜者是排名列表中的前 $n$ 人。每场附加淘汰赛包含 $d$ 道题，附加赛的获胜者仅为一人。此外，过去决赛的 $k$ 名获胜者将被邀请直接参加决赛，无需参加淘汰赛。

所有淘汰赛结束后，至少应有 $n \cdot m$ 人进入决赛。你需要组织淘汰赛，使得至少有 $n \cdot m$ 人进入决赛，并且所有轮次使用的题目总数尽可能少。

## 样例 #1
### 输入
```
1 10
7 2
1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
2 2
2 1
2
```
### 输出
```
0
```

### 综合分析与结论
这些题解主要围绕如何组织淘汰赛，以最少的题目数量让至少 $n \cdot m - k$ 人进入决赛。多数题解将其转化为完全背包问题，少数题解采用贪心策略。
- **思路对比**：大部分题解将两种比赛视为背包问题中的物品，通过动态规划求解最少题目数；Zzzzzzzm 的题解采用贪心策略，根据两种比赛的效率决定选择方式。
- **算法要点**：
    - 背包思路：将比赛视为物品，人视为容量，题目数视为价值，使用动态规划更新 $dp$ 数组。
    - 贪心思路：计算两种比赛的效率，根据效率高低选择比赛方式。
- **解决难点**：
    - 背包思路：初始化 $dp$ 数组为极大值，处理边界条件，最后在 $[n \cdot m - k, n \cdot m]$ 范围内取最小值。
    - 贪心思路：处理 $k$ 大于等于 $n \cdot m$ 的特殊情况，以及剩余人数的处理。

### 高评分题解
- **Fengxiang008（5星）**
    - **关键亮点**：思路清晰，将问题准确转化为背包问题，代码简洁易懂，注释详细。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,c,d,w[5],dp[10205],val[5];
int main()
{
    cin>>c>>d>>n>>m>>k;
    w[1]=n; val[1]=c;
    w[2]=1; val[2]=d;
    for(int i=1;i<=10200;i++)
        dp[i]=1e9;
    dp[0]=0;
    for(int i=1;i<=2;i++)
        for(int j=w[i];j<=10200;j++)
            dp[j]=min(dp[j],dp[j-w[i]]+val[i]);
    int ans=1e9;
    for(int i=n*m-k;i<=10200;i++)
        ans=min(ans,dp[i]);
    cout<<ans<<endl; 
    return 0; 
}
```
- **daiarineko（4星）**
    - **关键亮点**：详细分析了动态规划的状态转移过程，通过三元运算符优化代码，对题目中的坑点进行了提示。
    - **核心代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
int c,d,n,m,k,f[10001];
int main(){
    ios::sync_with_stdio(false);
    cin>>c>>d>>n>>m>>k;
    register int j=n*m;
    f[0]=0;
    for(register int i=1;i<=j;++i){
        f[i]=min((i-n>-1)?(f[i-n]+c):32767,f[i-1]+d);
    }
    register int mn=f[j-k];
    for(int i=j-k+1;i<=j;++i) mn=min(mn,f[i]);
    cout<<mn<<endl;
    return 0;
}
```
- **WanderingTrader（4星）**
    - **关键亮点**：将完全背包过程封装成函数，提高代码的复用性，思路清晰，代码结构良好。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define N 10005
#define INF 1e8
int dp[N],C;
void bbINF(int v,int w)
{
    for(int i = w;i <= C;++i)
        dp[i] = min(dp[i],dp[i-w]+v);
}
int main()
{
    int c,d,n,m,k;
    scanf("%d%d%d%d%d",&c,&d,&n,&m,&k);
    C = n*m;
    for(int i = 1;i <= C;++i)
        dp[i] = INF;
    bbINF(c,n);
    bbINF(d,1);
    int ans = INF;
    for(int i = C-k;i <= C;++i)
        ans = min(ans,dp[i]);
    printf("%d\n",ans);
    return 0;
}
```

### 最优关键思路与技巧
- **问题转化**：将组织淘汰赛的问题转化为完全背包问题，简化问题求解。
- **动态规划**：使用 $dp$ 数组记录选拔不同人数所需的最少题目数，通过状态转移方程更新 $dp$ 数组。
- **贪心策略**：通过计算比赛效率，根据效率高低选择比赛方式，减少计算量。

### 拓展思路
同类型题可参考其他背包问题变形，如多重背包、分组背包等。类似算法套路可用于资源分配问题，通过合理选择资源使用方式，达到最优目标。

### 洛谷题目推荐
- P1048 [采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题。
- P1616 [疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题。
- P1776 [宝物筛选](https://www.luogu.com.cn/problem/P1776)：多重背包问题。

### 个人心得摘录与总结
- daiarineko：在调试代码时，要注意题目要求的是至少多少道题，使用 `min` 而不是 `max`，三元运算符的否则部分使用极大数。同时，要注意使用比赛资源的顺序。
- HerikoDeltana：在初始化 $dp$ 数组时遇到问题，需要注意初始化的正确性。

---
处理用时：40.75秒