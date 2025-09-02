# 题目信息

# [USACO17DEC] The Bovine Shuffle S

## 题目描述

Farmer John 坚信快乐的奶牛能产更多的奶，因此他在谷仓里安装了一个巨大的迪斯科球，并计划教他的奶牛跳舞！

在查阅了流行的奶牛舞蹈后，Farmer John 决定教他的奶牛“Bovine Shuffle”。Bovine Shuffle 包括他的 $N$ 头奶牛（$1 \leq N \leq 100,000$）以某种顺序排成一行，然后进行连续的“洗牌”，每次洗牌可能会重新排列奶牛的顺序。为了让奶牛更容易找到自己的位置，Farmer John 为他的奶牛队伍标记了位置 $1 \ldots N$，因此队伍中的第一头奶牛位于位置 1，第二头位于位置 2，依此类推，直到位置 $N$。

一次洗牌由 $N$ 个数字 $a_1 \ldots a_N$ 描述，其中位于位置 $i$ 的奶牛在洗牌期间移动到位置 $a_i$（因此，每个 $a_i$ 都在 $1 \ldots N$ 范围内）。每头奶牛在洗牌期间都会移动到它的新位置。不幸的是，所有的 $a_i$ 不一定互不相同，因此多只奶牛可能会在洗牌期间尝试移动到同一位置，之后它们将在所有剩余的洗牌中一起移动。

Farmer John 注意到，无论进行多少次洗牌，他的队伍中某些位置始终会有奶牛。请帮助他计算这样的位置数量。

## 样例 #1

### 输入

```
4
3 2 1 3```

### 输出

```
3
```

# AI分析结果

### 综合分析与结论
本题核心是将奶牛位置变换问题转化为有向图中环的问题，即求有多少个位置无论经过多少次变换都有奶牛，等价于求图中在环上的点的个数。各题解思路大多围绕此展开，主要使用拓扑排序、DFS、Tarjan 缩点、SPFA 等算法求解。

### 所选题解
- **作者：QAQ永动机（5星）**
    - **关键亮点**：思路清晰，从对题意的理解、样例分析到猜想提出与修正，逐步引导出拓扑排序的解法，代码可读性高。
    - **个人心得**：最初猜想“入度 - 出度 >= 0”判断点上是否一直有牛，提交 WA 后发现错误原因是未考虑入度为 0 的点对后续点的影响，进而修正思路得到正确解法。
    - **核心代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans;
int out[100005],in[100005];
queue<int> q;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        in[a[i]]++;
    }
    for(int i=1;i<=n;i++)
    {
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int tmp=q.front();
        q.pop();
        in[a[tmp]]--;
        if(in[a[tmp]]==0)
        {
            q.push(a[tmp]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(in[i]!=0)
        {
            ans++;
        }
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：先统计每个点的入度，将入度为 0 的点入队。不断从队列中取出点，将其指向的点的入度减 1，若减后入度为 0 则将该点入队。最后统计入度不为 0 的点的个数，即为环上点的个数。

- **作者：Kirisame_Marisa_（4星）**
    - **关键亮点**：通过严谨的逻辑分析得出答案是图中所有环的长度之和，使用 DFS 判环，代码简洁。
    - **核心代码**
```cpp
int n,to[200005],id[200005],ans=0;
bool inring[200005],useless[200005];
int dfs(int now)
{
    if(inring[now])return 0;
    inring[now]=1;
    return dfs(to[now])+1;
}
void dfs2(int now)
{
    useless[now]=1;
    --id[to[now]];
    if(!id[to[now]])dfs2(to[now]);
}
int main()
{
    int a;
    cin>>n;for(int i=1;i<=n;++i){cin>>a;to[i]=a;++id[a];}
    for(int i=1;i<=n;++i)if(!id[i]&&!useless[i])dfs2(i);
    for(int i=1;i<=n;++i)if(!inring[i]&&!useless[i])ans+=dfs(i);
    cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：先使用 `dfs2` 函数去除所有不在环内的点，再使用 `dfs` 函数遍历图，计算环的长度并累加得到答案。

- **作者：0xFF（4星）**
    - **关键亮点**：详细阐述了将问题转化为求图中环上点的个数的思路，对拓扑排序的实现步骤和正确性进行了清晰说明。
    - **核心代码**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<queue>

using namespace std;
const int N = 100010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int n,a[N],ans,in[N];
queue<int> q;
int main(){
    n = read();
    for(int i=1;i<=n;i++){
        a[i] = read();
        in[a[i]] ++;
    }
    for(int i=1;i<=n;i++){
        if(in[i] == 0){
            q.push(i); 
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        in[a[u]]--;
        if(in[a[u]] == 0){
            q.push(a[u]); 
        }
    } 
    for(int i=1;i<=n;i++){
        if(in[i]!= 0){
            ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
    - **核心实现思想**：与“QAQ永动机”的题解类似，先统计入度，将入度为 0 的点入队，不断更新入度，最后统计入度不为 0 的点的个数。

### 最优关键思路或技巧
- **转化思维**：将奶牛位置变换问题转化为有向图中环的问题，简化问题求解。
- **拓扑排序**：利用拓扑排序去除不在环上的点，是解决此类问题的常用且高效方法。

### 可拓展之处
同类型题如判断有向图中是否存在环、求有向图中所有环的长度等。类似算法套路可用于解决其他图论问题，如强连通分量、欧拉回路等。

### 推荐题目
- P2661 [NOIP2015 提高组] 信息传递
- P3387 [模板] 缩点
- P1137 旅行计划

### 个人心得总结
“QAQ永动机”在解题过程中，最初的猜想未考虑全面导致 WA，通过分析错误数据修正思路，最终得到正确解法。这提醒我们在解题时要充分考虑各种情况，对猜想进行严格验证。 

---
处理用时：41.55秒