# 题目信息

# [USACO21JAN] Spaced Out S

## 题目描述

Farmer John 想要拍摄一张他的奶牛吃草的照片挂在墙上。草地可以用一个 $N$ 行 $N$ 列正方形方格所组成的方阵表示（想象一个 $N \times N$ 的棋盘），其中 $2 \leq N \leq 1000$。在 Farmer John 最近拍摄的照片中，他的奶牛们太过集中于草地上的某个区域。这一次，他想要确保他的奶牛们分散在整个草地上。于是他坚持如下的规则：

 - 没有两头奶牛可以位于同一个方格。
 - 所有 $2 \times 2$ 的子矩阵（共有 $(N-1) \times (N-1)$ 个）必须包含恰好 2 头奶牛。

例如，这一放置方式是合法的：

```
CCC
...
CCC
```

而这一放置方式是不合法的，因为右下的 $2 \times 2$ 正方形区域仅包含 1 头奶牛：

```
C.C
.C.
C..
```

没有其他限制。你可以假设 Farmer John 有无限多的奶牛（根据以往的经验，这种假设似乎是正确的……）。

Farmer John 更希望某些方格中包含奶牛。具体地说，他相信如果方格 $(i, j)$ 中放有一头奶牛，照片的美丽度会增加 $a_{ij}$（$0 \leq a_{ij} \leq 1000$）单位。

求合法的奶牛放置方式的最大总美丽度。


## 说明/提示

在这个样例中，最大美丽度可以在如下放置方式时达到：

```
CC..
..CC
CC..
..CC
```

这种放置方式的美丽度为 $3 + 3 + 3 + 1 + 3 + 3 + 3 + 3 = 22$。

测试点性质：

 - 测试点 2-4 满足 $N \le 4$。
 - 测试点 5-10 满足 $N\le 10$。
 - 测试点 11-20 满足 $N \le 1000$。

供题：Hankai Zhang，Danny Mittal

## 样例 #1

### 输入

```
4
3 3 1 1
1 1 3 1
3 3 1 1
1 1 3 3```

### 输出

```
22```

# AI分析结果

### 分析与结论
本题要求在一个 $N \times N$ 的方阵中放置奶牛，需满足没有两头奶牛在同一方格，且所有 $2 \times 2$ 的子矩阵必须恰好包含 2 头奶牛，每个方格有对应的美丽度，求合法放置方式的最大总美丽度。

### 所选题解
- **作者：K8He（4星）**
    - **亮点**：思路清晰，从部分分算法逐步过渡到满分算法，且对每种算法的时间复杂度有分析，代码简洁易懂。
- **作者：Diaоsi（4星）**
    - **亮点**：详细分析了题目性质，通过推理得出最优放置方式的特点，代码结构清晰。
- **作者：Skies（4星）**
    - **亮点**：直接点明解题关键思路，代码简洁，易于理解。

### 核心代码与思想
#### K8He
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,x[1010][2],y[1010][2],num,ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%d",&a),x[i][j%2]+=a,y[j][i%2]+=a;
    for(int i=1;i<=n;++i)
        num+=max(x[i][1],x[i][0]),ans+=max(y[i][1],y[i][0]);
    printf("%d",max(num,ans));
    return 0;
}
```
**思想**：先计算每一行的奇数列之和与偶数列之和，以及每一列的奇数行之和与偶数行之和，再取每行的两种交替方式中的最大值，最后取行上交替排列和列上交替排列的最大值作为答案。

#### Diaоsi
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=10010,INF=0x3f3f3f3f;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
int n,ans1,ans2,a[N][N];
int line_sum(int j,int type){
    int res[2]={0,0};
    for(int i=1;i<=n;i++)
        res[i&1]+=a[i][j];
    return res[type];
}
int row_sum(int i,int type){
    int res[2]={0,0};
    for(int j=1;j<=n;j++)
        res[j&1]+=a[i][j];
    return res[type];
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    for(int k=1;k<=n;k++){
        if(line_sum(k,0)>line_sum(k,1))
            ans1+=line_sum(k,0);
        else ans1+=line_sum(k,1);
    }
    for(int k=1;k<=n;k++){
        if(row_sum(k,0)>row_sum(k,1))
            ans2+=row_sum(k,0);
        else ans2+=row_sum(k,1);
    }
    printf("%d\n",Max(ans1,ans2));
    return 0;
}
```
**思想**：通过分析得出最优放置方式要么行交替，要么列交替，分别计算行交替和列交替的最大美丽度，最后取最大值。

#### Skies
```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=1e3+10,M=2e5+10;
int a[N][N],n;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int sum[2];
        sum[0]=0,sum[1]=0;
        for(int j=1;j<=n;j++)
        {
            sum[j%2]+=a[i][j];
        }
        ans+=max(sum[1],sum[0]);
    }
    int aa=0;
    for(int i=1;i<=n;i++)
    {
        int sum[2];
        sum[0]=0,sum[1]=0;
        for(int j=1;j<=n;j++)
        {
            sum[j%2]+=a[j][i];
        }
        aa+=max(sum[1],sum[0]);
    }
    cout<<max(ans,aa);
}
```
**思想**：分成行跳着放和列跳着放两种情况讨论，分别计算两种情况的最大美丽度，最后取最大值。

### 关键思路与技巧
- **性质分析**：通过对 $2 \times 2$ 子矩阵的放置情况分析，得出满足条件的放置方式要么行交替，要么列交替，从而将问题简化。
- **贪心策略**：分别计算行交替和列交替的最大美丽度，取其中较大值作为最终答案。

### 可拓展之处
同类型题可能会改变矩阵的限制条件或美丽度的计算方式，但解题的关键思路仍然是分析放置的性质，找到规律后进行贪心或动态规划求解。

### 推荐题目
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)
- [P1094 [NOIP2007 普及组] 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G](https://www.luogu.com.cn/problem/P1090)

### 个人心得
- **Diaоsi**：纪念自己 AK 银组月赛，通过分析题目条件得出关键性质，进而解决问题。
- **BreakPlus**：仅此题解纪念自己在考场上唯一 AC 的题目，在解题过程中发现了反例，通过旋转矩阵做两次 dp 解决问题。 

---
处理用时：43.29秒