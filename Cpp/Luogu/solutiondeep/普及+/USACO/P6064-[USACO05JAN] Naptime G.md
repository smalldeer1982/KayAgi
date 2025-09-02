# 题目信息

# [USACO05JAN] Naptime G

## 题目描述

贝茜是一只非常缺觉的奶牛．她的一天被平均分割成 $N$ 段（$3 \leq N \leq 3830$），但是她要用其中的 $B$ 段时间（$2 \leq B \lt N$）睡觉。每段时间都有一个效用值 $U_i$（$0 \leq U_i \leq 2 \times 10^5$），只有当她睡觉的时候，才会发挥效用。

有了闹钟的帮助，贝茜可以选择任意的时间入睡，当然，她只能在时间划分的边界处入睡、醒来。

贝茜想使所有睡觉效用的总和最大。不幸的是，每一段睡眠的第一个时间阶段都是“入睡”阶段，而旦不记入效用值。

时间阶段是不断循环的圆（一天一天是循环的嘛），假如贝茜在时间 $N$ 和时间 $1$ 睡觉，那么她将得到时间 $1$ 的效用值。

## 说明/提示

从第 $4$ 个时段入睡，到第 $1$ 个时段结束醒来。

## 样例 #1

### 输入

```
5 3
2
0
3
1
4```

### 输出

```
6```

# AI分析结果

### 综合分析与结论
这些题解均围绕环形动态规划问题展开，核心思路是先将环形问题简化为线性问题，通过动态规划求解，再考虑环形的特殊情况，通过改变初始条件再次进行动态规划，最后取两次结果的最大值。各题解的状态定义、状态转移方程基本一致，主要区别在于代码实现细节和优化程度。

### 所选题解
- **作者：_Andy_Lin_ (赞：38)，4星**
    - **关键亮点**：思路清晰，详细阐述了将环形问题转化为线性问题的过程，代码简洁明了，注释较少但不影响理解。
- **作者：MeowScore (赞：6)，4星**
    - **关键亮点**：不仅给出了常规的解题思路，还提到了另一种处理环形问题的方法（倍长区间），并给出了滚动数组优化的代码，对不同情况的分析较为全面。
- **作者：云岁月书 (赞：2)，4星**
    - **关键亮点**：对状态的分析和转移方程的推导较为详细，使用滚动数组优化空间，代码实现规范。

### 重点代码及核心实现思想
#### _Andy_Lin_ 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[3831][3831][2],n,b,u[3831],ans;
int main() {
    scanf("%d%d",&n,&b);
    for(int i=1;i<=n;i++)scanf("%d",u+i);
    memset(dp,-0x3f,sizeof(dp));
    dp[1][1][1]=dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=b;j++){
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
        }
    }
    ans=max(dp[n][b][0],dp[n][b][1]);
    memset(dp,-0x3f,sizeof(dp));
    dp[1][1][1]=u[1];
    dp[1][0][0]=0;
    for(int i=2;i<=n;i++){
        dp[i][0][0]=dp[i-1][0][0];
        for(int j=1;j<=b;j++){
            dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]);
            dp[i][j][1]=max(dp[i-1][j-1][0],dp[i-1][j-1][1]+u[i]);
        }
    }
    ans=max(ans,dp[n][b][1]);
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：先将环形问题简化为线性问题，使用 `dp[i][j][0/1]` 表示第 `i` 个小时，已经休息了 `j` 个小时，当前是否休息的最大效用值。进行第一次动态规划，得到线性问题的答案。然后改变初始条件，强制第 `n` 个小时睡觉，再次进行动态规划，最后取两次结果的最大值。

#### MeowScore 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int w[3840];
int f[2][3840][2];
int INF=0x3f3f3f3f;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>w[i];
    memset(f,-0x3f3f3f,sizeof f);
    f[1][0][0]=0;
    f[1][1][1]=0;
    for(register int i=2;i<=n;i++){
        for(register int j=0;j<=m;j++){
            f[i&1][j][0]=max(f[(i+1)&1][j][0],f[(i+1)&1][j][1]);
            f[i&1][j][1]=-INF;
            if(j)
                f[i&1][j][1]=max(f[(i+1)&1][j-1][0],f[(i+1)&1][j-1][1]+w[i]);
        }
    }
    int ans=f[n&1][m][0];
    memset(f,-0x3f3f3f,sizeof f);
    f[1][0][0]=0;
    f[1][1][1]=w[1];
    for(register int i=2;i<=n;i++){
        for(register int j=0;j<=m;j++){
            f[i&1][j][0]=max(f[(i+1)&1][j][0],f[(i+1)&1][j][1]);
            f[i&1][j][1]=-INF;
            if(j)
                f[i&1][j][1]=max(f[(i+1)&1][j-1][0],f[(i+1)&1][j-1][1]+w[i]);
        }
    }
    ans=max(f[n&1][m][1],ans);
    cout<<ans<<endl;
}
```
**核心实现思想**：同样先处理线性问题，再处理环形问题。使用滚动数组 `f[2][3840][2]` 优化空间，减少内存占用。

#### 云岁月书的题解
```cpp
# include <ctime>
# include <cmath>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <algorithm>
# define N 3830
# define max std::max

inline int Read()
{
    register int x = 0;char ch = getchar();

    while(ch < '0' || ch > '9')ch = getchar();

    while(ch >= '0' && ch <= '9'){x = x*10+(ch^48);ch = getchar();}

    return x;
}

inline int Max(const int x,const int y){return x > y ? x : y;}
inline int Min(const int x,const int y){return x < y ? x : y;}

int n,m,f[2][N+5][2],a[N+5],ans;

void DP()
{
    for(int i = 2; i <= n ; ++i)
    {
        f[i&1][0][0] = f[(i^1)&1][0][0];
        for(int j = 1; j <= m ; ++j)
        {
            f[i&1][j][0] = max(f[(i^1)&1][j][0],f[(i^1)&1][j][1]);
            f[i&1][j][1] = max(f[(i^1)&1][j-1][0],f[(i^1)&1][j-1][1]+a[i]);
        }
    }
}

int main()
{
    n = Read();m = Read();
    for(int i = 1; i <= n ; ++i) a[i] = Read();
    if(m == 0) return printf("0\n"),0;
    memset(f,-0x3f,sizeof(f));
    f[1][0][0] = f[1][1][1] = 0;
    DP();
    ans = max(f[n&1][m][0],f[n&1][m][1]);
    memset(f,-0x3f,sizeof(f));
    f[1][1][1] = a[1];
    DP();
    ans = max(ans,f[n&1][m][1]);
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：将动态规划部分封装成函数 `DP`，使用滚动数组优化空间，通过两次动态规划处理线性和环形问题，最后取最大值。

### 最优关键思路或技巧
- **状态定义**：使用三维数组 `dp[i][j][0/1]` 表示第 `i` 个小时，已经休息了 `j` 个小时，当前是否休息的最大效用值，清晰地表示了状态。
- **环形问题处理**：将环形问题转化为线性问题，通过改变初始条件进行两次动态规划，取最大值，有效解决了环形问题。
- **滚动数组优化**：观察到状态转移只与上一层有关，使用滚动数组优化空间，减少内存占用。

### 可拓展之处
同类型题或类似算法套路：
- 其他环形动态规划问题，如环形石子合并、环形最大子段和等，都可以采用将环形问题转化为线性问题，再通过改变初始条件进行多次动态规划的方法解决。
- 对于一些具有周期性的动态规划问题，也可以借鉴这种思路，将周期问题简化为一个周期内的问题进行求解。

### 推荐题目
- [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
- [P2627 [USACO11OPEN]Mowing the Lawn G](https://www.luogu.com.cn/problem/P2627)
- [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得摘录与总结
- **作者：linyinuo2008**：“首先，感谢一下大佬们对我的启发。~~（不然我可能一辈子都没法AC）~~”，总结：在解题过程中，参考他人的思路和代码可以获得启发，有助于解决难题。

---
处理用时：58.14秒