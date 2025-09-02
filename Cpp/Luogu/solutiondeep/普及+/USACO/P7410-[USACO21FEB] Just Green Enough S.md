# 题目信息

# [USACO21FEB] Just Green Enough S

## 题目描述

Farmer John 的草地可以被看作是一个由 $N \times N$ 个正方形方格（$1 \leq N \leq 500$）组成的方阵（想象一个巨大的棋盘）。由于土壤变异性，某些方格中的草可能更绿。每个方格 $(i,j)$ 可以用一个整数绿度值 $G(i,j)$ 来描述，范围为 $1 \ldots 200$。

Farmer John 想要给他的草地的一个子矩阵拍摄一张照片。他希望确保这一子矩阵看上去足够绿，但又不绿得过分，所以他决定拍摄一个 $G$ 的最小值恰好等于 100 的子矩阵。请帮助他求出他可以拍摄多少不同的照片。子矩阵最大可以为整个草地，最小可以仅为一个方格（共有 $N^2(N+1)^2/4$ 个不同的子矩阵——注意该数可能无法用 $32$ 位整数型存储，所以你可能需要使用 $64$ 位整数类型，例如 C++ 中的 long long）。


## 说明/提示

#### 测试点性质：

 - 对于 $50\%$ 的数据，满足 $N\le 200$。
 - 对于另外 $50\%$ 的数据，没有额外限制。

供题：Brian Dean

## 样例 #1

### 输入

```
3
57 120 87
200 100 150
2 141 135```

### 输出

```
8```

# AI分析结果

### 综合分析与结论
这些题解围绕求矩阵中最小值为 100 的子矩阵个数展开，思路多样，主要可分为暴力枚举、容斥原理、悬线法等方向。暴力枚举通过直接枚举子矩阵并判断是否合法来求解，复杂度较高；容斥原理将问题转化为计算不同条件下子矩阵个数的差值；悬线法结合单调栈等数据结构优化求解过程。

### 所选题解
- **作者：YBaggio（4星）**
  - **关键亮点**：思路清晰，利用容斥原理将问题转化为计算最小值小于 100 和小于等于 100 的子矩阵个数的差值，通过定义 `query(m)` 函数计算最小值小于 m 的子矩阵个数，代码实现简洁明了。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(3)
using namespace std;
#define inf 1000000010
const int maxn=510;
int n,a[maxn][maxn],b[maxn][maxn],sum[maxn][maxn];
long long query(int maxx){
    long long ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]<maxx)b[i][j]=1,sum[i][j]=0;
            else sum[i][j]=sum[i][j-1]+1,b[i][j]=0;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j])continue;
            long long Min=inf;
            for(int k=i;k>=1;k--){
                Min=min(Min,(long long)sum[k][j]);
                ans+=Min;
            }
        }
    }
    return ans;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    printf("%lld",query(100)-query(101));
    return 0;
}
```
  - **核心实现思想**：先将小于 `maxx` 的格子标记为 1，其余标记为 0，计算每行连续 0 的长度 `sum` 数组。然后枚举每个格子作为子矩阵右下角，向上枚举计算以该点为右下角的子矩阵个数，累加得到 `query(m)` 的结果。最终答案为 `query(100) - query(101)`。

- **作者：QQ82272760（4星）**
  - **关键亮点**：同样运用容斥原理，将问题转化为计算两个 01 矩阵中所有元素均为 1 的矩形个数的差值。通过预处理 `cnt` 数组优化计算过程，并使用单调栈进一步优化到 $O(n^2)$ 复杂度。
  - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int n,g[501][501],a[501][501];
ll cnt,s[501],ans;
pair<ll,ll>q[501][501];
ll check(){
    int top;
    ll x,res=0;
    for(int i=1;i<=n;i+=1){
        q[i][0].first=s[i]=0;  //初始化所有栈为空
    }
    for(int i=1;i<=n;i+=1){
        cnt=0;
        for(int j=1;j<=n;j+=1){
            if(a[i][j]==1) cnt+=1;
            else cnt=0;
            x=1; s[j]+=cnt; top=q[j][0].first;
            while(top&&q[j][top].first>=cnt){  //去掉不符合的栈顶
                s[j]-=(q[j][top].first-cnt)*q[j][top].second;
                x+=q[j][top--].second;
            }
            q[j][++top]=make_pair(cnt,x);  //加入
            q[j][0].first=top;
            res+=s[j];  //统计
        }
    }
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i+=1){
        for(int j=1;j<=n;j+=1) scanf("%d",&g[i][j]),a[i][j]=1;
    }
    for(int i=1;i<=n;i+=1){
        for(int j=1;j<=n;j+=1){
            if(g[i][j]<100) a[i][j]=0;  //去掉<100的点
        }
    }
    ans=check();  //第一次求解 ans1
    for(int i=1;i<=n;i+=1){
        for(int j=1;j<=n;j+=1){
            if(g[i][j]==100) a[i][j]=0;  //去掉=100的点
        }
    }
    ans-=check();  //ans=ans1-asn2
    printf("%lld\n",ans);
    return 0;
}
```
  - **核心实现思想**：先将矩阵转化为 01 矩阵，分别计算去掉小于 100 的点和去掉等于 100 的点后的 01 矩阵中所有元素均为 1 的矩形个数。`check` 函数中使用单调栈维护每列的信息，计算以每个点为右下角的矩形个数，累加得到结果。最终答案为两次计算结果的差值。

- **作者：jimmy2021（4星）**
  - **关键亮点**：定义函数 `f(x)` 代表最小值大于等于 x 的元素组成的子矩阵个数，通过容斥原理得到最终答案。使用 `t` 数组记录每个点最多能往上延伸的元素个数，并利用单调栈优化计算过程。
  - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 510, M = 510;

LL n;
LL a[N][M];

LL m;

LL t[N][M];

LL st[N], tp;

LL d[N];

LL f(LL x){
    for(LL i = 1;i <= n;i++)
        for(LL j = 1;j <= m;j++)
            if(a[i][j] >= x) t[i][j] = t[i - 1][j] + 1;
            else t[i][j] = 0;
    
    LL ret = 0;
    
    for(LL i = 1;i <= n;i++){
        tp = 0;
        //为了配合43行while循环（注解在38~42行）进行处理
        t[i][0] = 0;
        for(LL j = 1;j <= m;j++){
            //此处不判tp是因为要用st[tp] = 0来更新前面的几个点*
            //*前面的几个点：无法再用前面的点的d值更新该点的d值的点
            //而此题不能用在while循环里更新d值的写法，
            //因为tp = 0时，st[tp] = 0，t[i][st[tp]] = 0，
            //0小于等于所有的t值，所以会死循环
            while(t[i][st[tp]] > t[i][j]) tp--;
            //画图理解（图在上面）
            d[j] = d[st[tp]] + (j - st[tp]) * t[i][j];
            //累加答案
            ret += d[j];
            //插入栈中
            st[++tp] = j;
        }
    }
    
    return ret;
}

int main(){
    scanf("%lld", &n);
    
    m = n;
    
    for(LL i = 1;i <= n;i++)
        for(LL j = 1;j <= m;j++)
            scanf("%lld", &a[i][j]);
    
    printf("%lld\n", f(100) - f(101));
    return 0;
}
```
  - **核心实现思想**：在 `f(x)` 函数中，先预处理 `t` 数组记录每个点最多能往上延伸的元素个数。然后枚举每一行，使用单调栈维护 `t` 数组中的信息，计算以每个点为右下角的子矩阵个数，累加得到 `f(x)` 的结果。最终答案为 `f(100) - f(101)`。

### 最优关键思路或技巧
- **容斥原理**：将求最小值为 100 的子矩阵个数问题转化为计算不同条件下子矩阵个数的差值，简化问题求解过程。
- **单调栈优化**：在计算子矩阵个数时，利用单调栈维护相关信息，避免不必要的重复计算，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。
- **预处理**：通过预处理一些数组（如 `cnt` 数组、`t` 数组等），减少后续计算的复杂度。

### 可拓展之处
同类型题目可能会改变矩阵元素的条件或要求，如求最大值为某个值的子矩阵个数、求满足特定元素分布的子矩阵个数等。类似算法套路可用于解决其他矩阵相关的计数问题，如求矩阵中全 1 子矩阵的最大面积、周长等。

### 推荐题目
- [P1169 棋盘制作](https://www.luogu.com.cn/problem/P1169)：考察悬线法求最大正方形和最大矩形。
- [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)：利用悬线法和单调栈计算无障碍点的最大子矩阵。
- [P2701 [USACO5.3]巨大的牛棚Big Barn](https://www.luogu.com.cn/problem/P2701)：求矩阵中最大全 1 正方形的边长。

### 个人心得摘录与总结
- **作者：szzzzs**：提到码风较丑勿喷，且表示自己的方法比较简单枚举，复杂度较高，后续进行了优化，从 $O(n^4)$ 优化到 $O(n^3)$，体现了不断优化算法的过程。
- **作者：KSToki**：比赛时懒打得有点急，直接全部重算导致常数巨大，提醒我们在实现算法时要注意细节，尽量避免不必要的重复计算，优化代码效率。 

---
处理用时：76.31秒