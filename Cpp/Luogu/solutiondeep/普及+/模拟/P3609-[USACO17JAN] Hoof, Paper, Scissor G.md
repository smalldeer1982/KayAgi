# 题目信息

# [USACO17JAN] Hoof, Paper, Scissor G

## 题目背景

*本题与 [银组同名题目](/problem/P6120) 在题意上一致，唯一的差别在于对变手势次数的限制。*


## 题目描述

你可能玩过“石头，剪刀，布”，这个游戏在奶牛中同样流行，不过它的名字变成了“蹄子，剪刀，布”。

“蹄子，剪刀，布”和“石头，剪刀，布”的规则十分类似，两只奶牛数到三，然后出一个代表蹄子，剪刀或布的手势。蹄子胜过剪刀，剪刀胜过布，布胜过蹄子。特别地，如果两只奶牛的手势相同，则视为平局。

现在 FJ 和 Bassie 要进行 $N$ 轮对抗。Bassie 已经预测了 FJ 每一轮要出的手势。然而 Bassie 很懒，她最多只想变换 $K$ 次手势。

现在请你帮 Bassie 求出她最多能赢多少轮。

## 样例 #1

### 输入

```
5 1
P
P
H
P
S```

### 输出

```
4
```

# AI分析结果

• 综合分析与结论：这些题解主要围绕动态规划（DP）和记忆化搜索两种思路。DP思路下，大多定义三维状态 `f[i][j][k]` 表示第 `i` 轮，变换 `j` 次，当前手势为 `k` 时能赢的最多局数，通过考虑当前轮是否变换手势进行状态转移。记忆化搜索则是枚举每个手势，记录状态避免重复运算。部分题解还对朴素DP进行优化，减少时间复杂度。

所选的题解：
  - **作者：zgf519orz (5星)**
    - **关键亮点**：思路清晰，先给出朴素DP思路及代码，再分析优化点，通过只考虑与 `i - 1` 轮状态的关系优化，减少枚举轮数的循环，有效降低时间复杂度。
    - **个人心得**：原代码超时后思考优化，发现当前状态只与 `i - 1` 的状态有关，从而优化成功。
    - **核心代码片段**：
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int n,m;
bool h[100005],s[100005],p[100005];
int f[100005][25][3];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        char tmp;
        cin >> tmp;
        if(tmp=='H'){
            p[i]=1;
        }
        if(tmp=='S'){
            h[i]=1;
        }
        if(tmp=='P'){
            s[i]=1;
        }
    }
    f[1][0][0]=h[1];
    f[1][0][1]=s[1];
    f[1][0][2]=p[1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            f[i][j][0]=max(f[i][j][0],
                           max(f[i-1][j][0]+h[i],
                               max(f[i-1][j-1][1]+h[i],f[i-1][j-1][2]+h[i])));
            f[i][j][1]=max(f[i][j][1],
                           max(f[i-1][j][1]+s[i],
                               max(f[i-1][j-1][0]+s[i],f[i-1][j-1][2]+s[i])));
            f[i][j][2]=max(f[i][j][2],
                           max(f[i-1][j][2]+p[i],
                               max(f[i-1][j-1][0]+p[i],f[i-1][j-1][1]+p[i])));
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,max(f[n][i][0],max(f[n][i][1],f[n][i][2])));
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：通过三层循环遍历轮数 `i`、变换次数 `j` 和手势 `k`，根据是否变换手势从 `i - 1` 轮状态转移得到当前状态，最后在所有可能的变换次数下取最大获胜次数。

  - **作者：2017gangbazi (4星)**
    - **关键亮点**：采用记忆化搜索，代码简洁，通过将胜负关系挪位简化判断，使代码逻辑更清晰。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+100;
int n,k;
int s[maxn],f[maxn][22][3];
int dp(int x,int b,int w) {
    if(x==0)return 0;
    if(f[x][b][w])return f[x][b][w];
    int p=dp(x-1,b,w);
    if(b!=0) {
        for(int i=0; i<3; i++)
            if(i!=w)p=max(p,dp(x-1,b-1,i));
    }
    return f[x][b][w]=p+(w==s[x]);
}
int main() {
    scanf("%d %d",&n,&k);
    for(int i=1; i<=n; i++) {
        char c=getchar();
        while(c!='P'&&c!='H'&&c!='S')c=getchar();
        if(c=='P')s[i]=0;
        if(c=='H')s[i]=1;
        if(c=='S')s[i]=2;
    }
    int ans=0;
    for(int i=0; i<=k; i++) {
        for(int j=0; j<3; j++)
            ans=max(ans,dp(n,i,j));
    }
    cout<<ans<<endl;
}
```
核心实现思想：定义记忆化搜索函数 `dp`，通过递归枚举每一轮的手势和变换次数，利用记忆化数组 `f` 避免重复计算，最后在所有可能的变换次数和最终手势下取最大获胜次数。

  - **作者：Misaka_Azusa (4星)**
    - **关键亮点**：思路清晰，详细阐述状态定义和转移方程的推导过程，对换手势和不换手势两种情况分别讨论，代码实现简洁明了。
    - **核心代码片段**：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int f[maxn][21][3], k, n, answer;
int num[maxn][3];

int main()
{
    scanf("%d%d",&n,&k);
    for(int i = 1; i <= n; i++)
    {
        char s;
        cin>>s;
        if(s == 'H')
            num[i][0] = 1;
        if(s == 'P')
            num[i][1] = 1;
        if(s == 'S')
            num[i][2] = 1;
    }

    for(int i = 1; i <= n; i++)
        for(int j = 0; j <= k; j++)
        {
            if(j - 1 >= 0)
            {
                f[i][j][0] = max(max(f[i-1][j-1][1], f[i-1][j-1][2]) + num[i][0], f[i-1][j][0] + num[i][0]);
                f[i][j][2] = max(max(f[i-1][j-1][1], f[i-1][j-1][0]) + num[i][2], f[i-1][j][2] + num[i][2]);
                f[i][j][1] = max(max(f[i-1][j-1][0], f[i-1][j-1][2]) + num[i][1], f[i-1][j][1] + num[i][1]);
            }
            else
            {
                f[i][j][0] = f[i-1][j][0] + num[i][0];
                f[i][j][2] = f[i-1][j][2] + num[i][2];
                f[i][j][1] = f[i-1][j][1] + num[i][1];
            }
        }
    for(int j = 0; j <= k; j++)
    {
        answer = max(answer, f[n][j][0]);
        answer = max(answer, f[n][j][1]);
        answer = max(answer, f[n][j][2]);
    }
    printf("%d",answer);
    return 0;
}
```
核心实现思想：通过两层循环遍历轮数 `i` 和变换次数 `j`，根据是否能变换手势（`j - 1 >= 0`）从 `i - 1` 轮状态转移得到当前状态，最后在所有可能的变换次数下取最大获胜次数。

**最优关键思路或技巧**：在动态规划中，优化状态转移，通过分析发现当前状态与前一轮状态的紧密联系，减少不必要的枚举，降低时间复杂度。记忆化搜索中，巧妙转换胜负判断方式，简化代码逻辑，同时利用记忆化数组避免重复计算。

**可拓展思路**：此类题目属于决策类动态规划，可拓展到其他具有决策选择且状态可递推的场景，例如背包问题的变体，在有限资源下通过不同决策获取最大收益。类似算法套路是定义合适的状态，明确状态转移方程，根据题目条件优化转移过程。

**推荐题目**：
  - [P1048 采药](https://www.luogu.com.cn/problem/P1048)：01背包问题，通过决策选择物品放入背包，与本题在决策和状态转移上有相似思路。
  - [P1833 樱花](https://www.luogu.com.cn/problem/P1833)：多重背包问题，在有限资源下做决策，与本题在动态规划的应用上类似。
  - [P2679 子串](https://www.luogu.com.cn/problem/P2679)：涉及字符串的动态规划，通过状态转移解决子串相关问题，与本题思路有相通之处。 

---
处理用时：63.66秒