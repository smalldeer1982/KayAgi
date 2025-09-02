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
本题的核心是求给定矩阵中最小值恰好为 100 的子矩阵个数。各题解的思路主要围绕容斥原理展开，即通过计算不同条件下子矩阵的个数，然后做差得到最终结果。常见的做法是将矩阵元素按条件转化为 0、1 矩阵，再利用各种方法计算子矩阵个数。

算法方面，涉及枚举、前缀和、单调栈、悬线法、ST 表等多种技巧。不同题解的时间复杂度有所差异，从 $O(n^4)$ 到 $O(n^2)$ 不等。

### 所选题解
- **作者：YBaggio（4星）**
    - **关键亮点**：思路清晰，利用容斥原理将问题转化为计算最小值小于 100 和小于等于 100 的子矩阵个数之差。通过预处理 $sum$ 数组和枚举右下角格子，利用 $sum$ 数组的最小值累加得到子矩阵个数，代码简洁易懂。
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
**核心实现思想**：`query` 函数用于计算最小值小于 `maxx` 的子矩阵个数。首先将小于 `maxx` 的格子标记为 1，其余标记为 0，并计算 `sum` 数组。然后枚举右下角格子，向上遍历计算最小的 `sum` 值并累加，得到子矩阵个数。

- **作者：QQ82272760（4星）**
    - **关键亮点**：同样利用容斥原理，将问题转化为计算 01 矩阵中所有元素均为 1 的矩形个数。通过预处理 `cnt` 数组表示点及其右边连续 1 的个数，再利用单调栈优化，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。
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
**核心实现思想**：`check` 函数用于计算 01 矩阵中所有元素均为 1 的矩形个数。通过枚举每一行，利用单调栈维护每一列的信息，计算以当前点为右下角的矩形个数并累加。

- **作者：jimmy2021（4星）**
    - **关键亮点**：定义函数 `f(x)` 代表最小值大于等于 `x` 的元素组成的子矩阵个数，利用容斥原理计算最终答案。通过预处理 `t` 数组表示点最多能往上延伸的元素个数，再用单调栈维护，优化计算过程。
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
**核心实现思想**：`f` 函数用于计算最小值大于等于 `x` 的子矩阵个数。首先预处理 `t` 数组，然后枚举每一行，利用单调栈维护 `t` 数组的信息，计算以当前点为右下角的子矩阵个数并累加。

### 最优关键思路或技巧
- **容斥原理**：将问题转化为计算不同条件下子矩阵个数的差，简化问题求解。
- **单调栈优化**：在计算子矩阵个数时，利用单调栈可以将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。
- **预处理数组**：如 `sum` 数组、`cnt` 数组、`t` 数组等，通过预处理可以减少重复计算，提高效率。

### 可拓展之处
同类型题或类似算法套路：
- 计算矩阵中满足其他条件（如最大值、平均值等）的子矩阵个数，可采用类似的容斥原理和枚举方法。
- 求矩阵中最大子矩阵的面积或周长等问题，可使用悬线法、单调栈等算法。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：考察最大子矩阵问题，可使用动态规划或单调栈解决。
- [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)：与本题类似，利用悬线法和单调栈计算无障碍点的最大子矩阵。
- [P2701 巨大的牛棚](https://www.luogu.com.cn/problem/P2701)：求矩阵中最大的全 1 子矩阵，可使用单调栈或悬线法。

### 个人心得摘录与总结
- **作者：szzzzs**：提到自己的方法比较“LJ”，只是简单枚举，反映出在解题过程中可能尝试了较为基础的方法，但意识到其复杂度较高。
- **作者：KSToki**：比赛时打得有点急，直接全部重算了向左右能扩展的最大位置，导致常数巨大。提醒我们在实现算法时要注意细节，避免不必要的重复计算。

---
处理用时：75.26秒