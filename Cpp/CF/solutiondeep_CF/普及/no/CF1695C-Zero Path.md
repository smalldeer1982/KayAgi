# 题目信息

# Zero Path

## 题目描述

You are given a grid with $ n $ rows and $ m $ columns. We denote the square on the $ i $ -th ( $ 1\le i\le n $ ) row and $ j $ -th ( $ 1\le j\le m $ ) column by $ (i, j) $ and the number there by $ a_{ij} $ . All numbers are equal to $ 1 $ or to $ -1 $ .

You start from the square $ (1, 1) $ and can move one square down or one square to the right at a time. In the end, you want to end up at the square $ (n, m) $ .

Is it possible to move in such a way so that the sum of the values written in all the visited cells (including $ a_{11} $ and $ a_{nm} $ ) is $ 0 $ ?

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1695C/8f2d98d121e7e351eaa9a88e08080da6d06835b5.png)

## 说明/提示

One possible path for the fourth test case is given in the picture in the statement.

## 样例 #1

### 输入

```
5
1 1
1
1 2
1 -1
1 4
1 -1 1 -1
3 4
1 -1 -1 -1
-1 1 1 -1
1 1 1 -1
3 4
1 -1 1 1
-1 1 -1 1
1 -1 1 1```

### 输出

```
NO
YES
YES
YES
NO```

# AI分析结果

### 题目内容重写
给定一个 $n \times m$ 的网格，每个格子的值为 $1$ 或 $-1$。你从 $(1, 1)$ 出发，每次只能向右或向下移动，最终到达 $(n, m)$。问是否存在一条路径，使得路径上经过的格子值的和为 $0$。

### 算法分类
动态规划

### 题解分析与结论
各题解的核心思路基本一致，即通过动态规划计算从起点到终点的最大路径和与最小路径和，然后判断是否存在一条路径的和为 $0$。具体来说，如果路径长度 $n+m-1$ 为偶数，并且最小路径和 $\leq 0 \leq$ 最大路径和，则存在满足条件的路径。

### 所选高星题解
#### 题解1：作者：Blunt_Feeling (赞：6)
- **星级**：4星
- **关键亮点**：思路清晰，代码简洁，使用了动态规划计算最大和最小路径和，并给出了详细的证明。
- **代码核心思想**：通过动态规划计算从起点到终点的最大路径和与最小路径和，然后判断是否存在一条路径的和为 $0$。
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int maxn=1024;
int T,n,m,a[maxn][maxn],f[maxn][maxn],g[maxn][maxn];
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        For(i,1,n)
            For(j,1,m)
                cin>>a[i][j];
        if((n+m-1)&1) //特判
        {
            puts("NO");
            continue;
        }
        int h=(n+m-1)/2;
        f[1][1]=(a[1][1]==1?1:0);
        For(i,1,n)
            For(j,1,m)
                f[i][j]=max(f[i][j-1],f[i-1][j])+(a[i][j]==1?1:0); //f求最大值
        For(i,2,n) g[i][0]=0x3f3f3f3f;
        For(j,2,m) g[0][j]=0x3f3f3f3f; //因为要取min值，故先初始化
        For(i,1,n)
            For(j,1,m)
                g[i][j]=min(g[i][j-1],g[i-1][j])+(a[i][j]==1?a[i][j]:0); //g求最小值
        if(g[n][m]<=h&&h<=f[n][m]) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

#### 题解2：作者：tzyt (赞：5)
- **星级**：4星
- **关键亮点**：详细解释了路径和的变化规律，并给出了动态规划的边界条件和转移方程。
- **代码核心思想**：通过动态规划计算从起点到终点的最大路径和与最小路径和，然后判断是否存在一条路径的和为 $0$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int a[n + 1][m + 1]; 
        int mx[n + 1][m + 1], mn[n + 1][m + 1];
        memset(a, 0, sizeof(a));
        memset(mx, 0, sizeof(mx));
        memset(mn, 0, sizeof(mn));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }        
        for (int i = 1; i <= n; i++)
            mx[i][1] = mn[i][1] = mx[i - 1][1] + a[i][1];
        for (int j = 1; j <= m; j++)
            mx[1][j] = mn[1][j] = mn[1][j - 1] + a[1][j];
        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]) + a[i][j];
                mn[i][j] = min(mn[i - 1][j], mn[i][j - 1]) + a[i][j];
            }
        }
        if (mx[n][m] & 1 || mn[n][m] > 0 || mx[n][m] < 0) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
}
```

#### 题解3：作者：makerlife (赞：1)
- **星级**：4星
- **关键亮点**：详细解释了路径和的变化规律，并给出了动态规划的边界条件和转移方程。
- **代码核心思想**：通过动态规划计算从起点到终点的最大路径和与最小路径和，然后判断是否存在一条路径的和为 $0$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1145;
int t,n,m,a[N][N],maxn[N][N],minn[N][N];
signed main()
{
    memset(maxn,-0x3f,sizeof maxn);
    memset(minn,0x3f,sizeof minn);
    maxn[1][0]=maxn[0][1]=minn[0][1]=minn[1][0]=0;
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin>>a[i][j];
                maxn[i][j]=max(maxn[i-1][j],maxn[i][j-1])+a[i][j];
                minn[i][j]=min(minn[i-1][j],minn[i][j-1])+a[i][j];
            }
        }
        if((n+m-1)&1||minn[n][m]>0||maxn[n][m]<0)cout<<"NO\n";
        else cout<<"YES\n";
    }
}
```

### 最优关键思路
通过动态规划计算从起点到终点的最大路径和与最小路径和，然后判断是否存在一条路径的和为 $0$。关键在于理解路径和的变化规律，即路径和的变化只能是 $+2$、$-2$ 或 $0$，从而保证路径和的奇偶性。

### 可拓展之处
类似的问题可以扩展到其他路径和的问题，例如求路径和的最大值或最小值，或者求路径和等于某个特定值的情况。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)

---
处理用时：49.54秒