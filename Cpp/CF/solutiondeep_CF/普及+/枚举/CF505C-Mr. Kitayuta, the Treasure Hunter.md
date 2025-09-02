# 题目信息

# Mr. Kitayuta, the Treasure Hunter

## 题目描述

The Shuseki Islands are an archipelago of $ 30001 $ small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from $ 0 $ to $ 30000 $ from the west to the east. These islands are known to contain many treasures. There are $ n $ gems in the Shuseki Islands in total, and the $ i $ -th gem is located on island $ p_{i} $ .

Mr. Kitayuta has just arrived at island $ 0 $ . With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

- First, he will jump from island $ 0 $ to island $ d $ .
- After that, he will continue jumping according to the following rule. Let $ l $ be the length of the previous jump, that is, if his previous jump was from island $ prev $ to island $ cur $ , let $ l=cur-prev $ . He will perform a jump of length $ l-1 $ , $ l $ or $ l+1 $ to the east. That is, he will jump to island $ (cur+l-1) $ , $ (cur+l) $ or $ (cur+l+1) $ (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length $ 0 $ when $ l=1 $ . If there is no valid destination, he will stop jumping.

Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

## 说明/提示

In the first sample, the optimal route is 0 $ → $ 10 (+1 gem) $ → $ 19 $ → $ 27 (+2 gems) $ →...&#x1; $

In the second sample, the optimal route is 0 $ → $ 8 $ → $ 15 $ → $ 21 $ → $ 28 (+1 gem) $ → $ 36 (+1 gem) $ → $ 45 (+1 gem) $ → $ 55 (+1 gem) $ → $ 66 (+1 gem) $ → $ 78 (+1 gem) $ →... $

In the third sample, the optimal route is 0 $ → $ 7 $ → $ 13 $ → $ 18 (+1 gem) $ → $ 24 (+2 gems) $ → $ 30 (+1 gem) $ →... $

## 样例 #1

### 输入

```
4 10
10
21
27
27
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8 8
9
19
28
36
45
55
66
78
```

### 输出

```
6
```

## 样例 #3

### 输入

```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
```

### 输出

```
4
```

# AI分析结果

### 题目内容翻译
# 寻宝者北田先生

## 题目描述
梳子群岛是由30001个小岛组成的群岛，位于油潭波海。这些岛屿均匀分布在一条直线上，从西到东依次编号为0到30000。众所周知，这些岛屿上藏有许多宝藏。梳子群岛上总共有n颗宝石，第i颗宝石位于岛屿$p_i$上。

北田先生刚刚抵达0号岛。凭借他出色的跳跃能力，他将按照以下过程在岛屿间向东反复跳跃：
- 首先，他将从0号岛跳到d号岛。
- 之后，他将继续按照以下规则跳跃。设l为上一次跳跃的长度，也就是说，如果他上一次跳跃是从prev号岛跳到cur号岛，那么设$l = cur - prev$。他将向东跳跃长度为$l - 1$、$l$或$l + 1$的距离。也就是说，他将跳到$(cur + l - 1)$号岛、$(cur + l)$号岛或$(cur + l + 1)$号岛（如果这些岛屿存在）。跳跃长度必须为正，也就是说，当$l = 1$时，他不能进行长度为0的跳跃。如果没有有效的目的地，他将停止跳跃。

北田先生将收集在跳跃过程中访问的岛屿上的宝石。求他最多能收集到多少颗宝石。

## 说明/提示
在第一个样例中，最优路线是0 → 10（+1颗宝石）→ 19 → 27（+2颗宝石）→...

在第二个样例中，最优路线是0 → 8 → 15 → 21 → 28（+1颗宝石）→ 36（+1颗宝石）→ 45（+1颗宝石）→ 55（+1颗宝石）→ 66（+1颗宝石）→ 78（+1颗宝石）→...

在第三个样例中，最优路线是0 → 7 → 13 → 18（+1颗宝石）→ 24（+2颗宝石）→ 30（+1颗宝石）→...

## 样例 #1
### 输入
```
4 10
10
21
27
27
```
### 输出
```
3
```

## 样例 #2
### 输入
```
8 8
9
19
28
36
45
55
66
78
```
### 输出
```
6
```

## 样例 #3
### 输入
```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
```
### 输出
```
4
```

### 综合分析与结论
所有题解均认为本题使用动态规划求解，但常规的二维状态定义（第一维为当前位置，第二维为上一次跳的步数）会导致空间复杂度达到$O(30000\times30000)$，出现MLE。各题解的核心思路均为优化状态定义，将第二维改为与初始跳跃步数$d$的变化次数，通过等差数列求和公式估算出变化次数最多约为300多次，从而将空间复杂度优化到可接受范围。

### 所选的题解
- **作者：zythonc（5星）**
  - **关键亮点**：思路清晰，详细分析了常规状态定义的问题及优化方向，代码简洁明了，对状态转移方程的推导和实现准确。
  - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 30010
using namespace std;
const int df=320;
int n,m,f[N][650],in,v[N],ans;
inline int tm(int a,int b,int c) {return a>b?(a>c?a:c):(b>c?b:c);}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>in;
        v[in]+=1;
    }
    memset(f,-0x3f,sizeof(f));
    ans=f[m][df]=v[0]+v[m];
    for(int i=m+1;i<=in;i++){
        for(int o=-320;o<=320;o++){
            if(m+o>0&&m+o<=i) f[i][df+o]=max(f[i][df+o],tm(f[i-(m+o)][df+o],f[i-(m+o)][df+o-1],f[i-(m+o)][df+o+1])+v[i]);
            ans=max(ans,f[i][df+o]);
        }
    }
    cout<<ans;
}
```
  - **核心实现思想**：定义`f[i][o]`表示在位置`i`，相对于初始步长`m`变化了`o`次的最大宝石数。通过双重循环遍历位置和变化次数，根据状态转移方程更新`f`数组，并不断更新答案`ans`。

- **作者：A_grasser（4星）**
  - **关键亮点**：对题意简化清晰，代码实现完整且通过注释对关键部分进行说明，对状态转移方程的推导和边界处理解释详细。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,w[30007],f[30007][740],ans;
int main(){
    cin>>n>>d;
    int x;
    for(int i=1;i<=n;i++){
        scanf("%d",&x);
        w[x]++;
    }
    memset(f,-0x3f,sizeof(f));
    f[d][370]=w[0]+w[d];
    ans=f[d][370];
    for(int i=d+1;i<=x;i++){
        for(int j=-320;j<=320;j++){
            if(d+j>0 && d+j<=i)
                f[i][370+j]=max(f[i][370+j],max(f[i-(d+j)][370+j],max(f[i-(d+j)][370+j-1],f[i-(d+j)][370+j+1]))+w[i]);
            ans=max(ans,f[i][370+j]);
        }
    }
    cout<<ans;
    return 0;
}
```
  - **核心实现思想**：定义`f[i][j]`表示在位置`i`，相对于初始步长`d`变化了`j`次的最大宝石数。初始化`f[d][370]`后，通过两层循环更新`f`数组，每次更新考虑从之前位置转移过来的三种情况，并更新最大答案。

- **作者：__Hacheylight__（4星）**
  - **关键亮点**：提供了递推和记忆化搜索两种实现方式，对状态定义的优化解释详细，代码注释丰富。
  - **重点代码（递推版）**：
```cpp
#include <bits/stdc++.h>
using namespace std ;
const int inf=0x3f3f3f3f ;
const int D=400 ; 
const int N=3e4 ;
int cnt[N+10];
int dp[N+10][2*D+10] ;
int n,d,x,ans ;
int main(){
    scanf("%d%d",&n,&d) ;
    for (int i=1;i<=n;i++){
        scanf("%d",&x);
        cnt[x]++ ;
    }
    for (int i=0;i<=N;i++){
        for (int j=-D;j<=D;j++)
        dp[i][j+D]=-inf ;
    }
    dp[d][D]=cnt[0]+cnt[d] ;
    for (int i=d;i<=N;i++){
        for (int j=-D;j<=D;j++){
            if (dp[i][j+D]==-inf){
                continue ;
            }
            for (int z=-1;z<=1;z++){
                int len=j+d+z ;
                if (j+z < -D || j+z >D || len<1 || i+len>N) continue ;
                dp[i+len][j+z+D]=max(dp[i+len][j+z+D],dp[i][j+D]+cnt[i+len]) ;
            }
        }
    }
    ans=0 ;
    for (int i=0;i<=N;i++){
        for (int j=-D;j<=D;j++){
            ans=max(ans,dp[i][j+D]) ;
        }
    }
    printf("%d\n",ans) ;
    return 0 ;
}
```
  - **核心实现思想**：定义`dp[i][j]`表示在位置`i`，相对于初始步长`d`变化了`j`次的最大宝石数。初始化`dp`数组后，通过三层循环，外层循环遍历位置，中层循环遍历变化次数，内层循环考虑三种跳跃长度的转移情况，最后遍历`dp`数组得到最大答案。

### 最优关键思路或技巧
通过分析跳跃步数的变化规律，利用等差数列求和公式确定步数变化次数的范围，从而优化动态规划的状态定义，将原本无法承受的空间复杂度降低到可接受范围。

### 可拓展之处
此类题目属于动态规划优化类型，通常在常规状态定义导致时空复杂度过高时，需要深入分析问题性质，寻找状态之间的关联和限制，对状态进行合理的压缩或转换。类似套路可应用于其他具有固定决策范围且决策影响后续状态的动态规划问题，例如某些路径规划、资源分配问题等。

### 洛谷相似题目推荐
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)：通过动态规划求解传球过程中的方案数，可锻炼对状态定义和转移方程的理解。
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目，从顶部到底部寻找最大路径和，与本题类似需要考虑状态转移和优化。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：通过记忆化搜索或动态规划求解最长滑雪路径长度，同样涉及状态的定义与优化。

### 个人心得摘录
- **作者：A_grasser**：提到该题在任务计划里搁置半年，反映出此类动态规划优化题目具有一定难度，需要深入思考状态优化方向。
- **作者：__Hacheylight__**：指出该题作为Div.1 A题，现场有不少大佬失误，强调了对动态规划优化思路把握的重要性。 

---
处理用时：45.33秒