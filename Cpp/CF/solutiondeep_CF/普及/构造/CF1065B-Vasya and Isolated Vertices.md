# 题目信息

# Vasya and Isolated Vertices

## 题目描述

Vasya has got an undirected graph consisting of $ n $ vertices and $ m $ edges. This graph doesn't contain any self-loops or multiple edges. Self-loop is an edge connecting a vertex to itself. Multiple edges are a pair of edges such that they connect the same pair of vertices. Since the graph is undirected, the pair of edges $ (1, 2) $ and $ (2, 1) $ is considered to be multiple edges. Isolated vertex of the graph is a vertex such that there is no edge connecting this vertex to any other vertex.

Vasya wants to know the minimum and maximum possible number of isolated vertices in an undirected graph consisting of $ n $ vertices and $ m $ edges.

## 说明/提示

In the first example it is possible to construct a graph with $ 0 $ isolated vertices: for example, it should contain edges $ (1, 2) $ and $ (3, 4) $ . To get one isolated vertex, we may construct a graph with edges $ (1, 2) $ and $ (1, 3) $ .

In the second example the graph will always contain exactly one isolated vertex.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
0 1
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1 1
```

# AI分析结果

### 题目内容中文重写
# 瓦西亚和孤立顶点

## 题目描述

瓦西亚有一个由 $n$ 个顶点和 $m$ 条边组成的无向图。这个图不包含任何自环或重边。自环是连接一个顶点到自身的边。重边是指连接同一对顶点的两条边。由于图是无向的，边对 $(1, 2)$ 和 $(2, 1)$ 被视为重边。图的孤立顶点是指没有边将其与任何其他顶点相连的顶点。

瓦西亚想知道由 $n$ 个顶点和 $m$ 条边组成的无向图中，孤立顶点的最小和最大可能数量。

## 说明/提示

在第一个样例中，可以构造一个有 $0$ 个孤立顶点的图：例如，它应该包含边 $(1, 2)$ 和 $(3, 4)$。要得到一个孤立顶点，我们可以构造一个包含边 $(1, 2)$ 和 $(1, 3)$ 的图。

在第二个样例中，图总是恰好包含一个孤立顶点。

## 样例 #1

### 输入
```
4 2
```

### 输出
```
0 1
```

## 样例 #2

### 输入
```
3 1
```

### 输出
```
1 1
```

### 题解综合分析与结论
这些题解的核心思路都是分别求解孤立顶点的最小值和最大值。
- **最小值思路**：为使孤立顶点最少，应让每条边连接两个原本孤立的点，这样 $m$ 条边最多连接 $2m$ 个点，孤立顶点最小值为 $\max(0, n - 2m)$。
- **最大值思路**：为使孤立顶点最多，要让有边相连的点尽可能多地连边，形成完全图，通过枚举或二分找到满足边数大于等于 $m$ 的最小点数 $x$，孤立顶点最大值为 $n - x$。

### 题解评分及选择
|作者|星级|亮点|
| ---- | ---- | ---- |
|DarkShadow|4星|思路清晰，代码简洁，直接给出核心公式和枚举方法求解|
|Double_Light|4星|详细解释思路，代码实现简洁易懂|
|NuoCarter|4星|使用二分查找优化求解最大值的过程，代码规范|

### 重点代码及核心思想
#### DarkShadow
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll m;
int main(){
    scanf("%d%lld",&n,&m);
    printf("%d ",max(0ll,(ll)(n)-2*m));//求最小值
    for(int i=0;i<=n;i++)
        if((ll)(i)*(ll)(i-1)/2ll>=m){
            printf("%d",n-i);//求最大值
            break;
        }
    return 0;
}
```
核心思想：先根据公式计算孤立顶点最小值，再通过枚举找到满足条件的完全图点数，进而得到最大值。

#### Double_Light
```cpp
#include<iostream>
using namespace std;
long long n,m,cnt;
int main(){
    cin>>n>>m;
    if(n-m*2<0)cout<<0;
    else cout<<n-m*2;
    cout<<' ';
    for(int i=1;m>0;i++){
        m-=i-1;cnt++;
    }
    cout<<n-cnt;
    return 0;
}
```
核心思想：先计算最小值，然后通过循环模拟完全图连边过程，得到有边相连的点数，从而求出最大值。

#### NuoCarter
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m;
int main(){
    read(n),read(m);ll minn=0,maxn=0;
    minn=max(0ll,n-2*m);print(minn),putchar(' ');
    ll l=0,r=n;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid*(mid-1)/2>=m)    r=mid-1,maxn=mid;
        else l=mid+1;
    }
    print(n-maxn);
    return 0;
}
```
核心思想：先计算最小值，再使用二分查找找到满足条件的最小完全图点数，得到最大值。

### 最优关键思路或技巧
- **贪心策略**：求最小值时，采用贪心思想，让每条边连接两个孤立点，最大程度利用边。
- **完全图性质**：求最大值时，利用完全图边数公式 $\frac{n(n - 1)}{2}$，通过枚举或二分查找确定满足条件的点数。
- **二分查找优化**：部分题解使用二分查找，将时间复杂度从线性枚举的 $O(n)$ 优化到 $O(\log n)$。

### 可拓展之处
同类型题目可能会改变图的类型（如有向图）、增加限制条件（如边有权重），但核心思路依然是通过合理构造图来求解特定指标的最值。类似算法套路包括贪心构造、二分查找等。

### 洛谷相似题目推荐
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：考察二分查找和贪心思想。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：使用二分查找优化求解过程。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：结合二分查找和贪心策略解决问题。

### 个人心得摘录与总结
- _zexal_：提到二分正确性是因为 $n \times (n + 1) / 2$ 函数单调上升，可通过二分枚举顶点数量，还强调要注意 $n$ 的范围和特判 $m = 0$ 的情况。
- 花里心爱：指出本题细节多，要注意特判 $m = 0$ 和 $m = 1$ 的情况。

总结：在解决此类问题时，要注意特殊情况的处理，同时对于单调函数可以考虑使用二分查找优化算法。 

---
处理用时：32.37秒