# 题目信息

# [USACO3.1] 最短网络 Agri-Net

## 题目背景

Farmer John 被选为他们镇的镇长！他其中一个竞选承诺就是在镇上建立起互联网，并连接到所有的农场。当然，他需要你的帮助。


## 题目描述

FJ 已经给他的农场安排了一条高速的网络线路，他想把这条线路共享给其他农场。为了用最小的消费，他想铺设最短的光纤去连接所有的农场。

你将得到一份各农场之间连接费用的列表，你必须找出能连接所有农场并所用光纤最短的方案。每两个农场间的距离不会超过 $10^5$。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.1


## 样例 #1

### 输入

```
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0```

### 输出

```
28```

# AI分析结果

### 综合分析与结论
本题是最小生成树的模板题，题解主要采用了Kruskal和Prim两种算法。Kruskal算法通过将边按权值排序，利用并查集判断边是否能加入生成树；Prim算法则是从一个点开始，不断选择与当前生成树相连的最小边扩展。

### 高评分题解
1. **作者：chengni（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了如何将矩阵数据转换为边集，且对Kruskal算法的实现步骤有清晰注释。
    - **核心代码**：
```cpp
struct node{
    int x,y,w;
}a[200002];
bool cmp(node xx,node yy){
    return xx.w<yy.w;
}
int find(int x){
    if(x==f[x]) return x;
    f[x]=find(f[x]);
    return f[x];
}
int main(){
    int n,k,m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        f[i]=i;
        for(int j=1;j<=n;j++){
            scanf("%d",&k);
            if(j>i){
                m++;
                a[m].x=i;a[m].y=j;a[m].w=k;	
            }	
        }
    }
    sort(a+1,a+m+1,cmp);
    int ans=0,p=1;
    for(int i=1;i<=m;i++){
        if(find(a[i].x)!=find(a[i].y)){
            ans+=a[i].w;
            f[find(a[i].x)]=a[i].y;
            p++;
            if(p==n) break;	
        }
    }
    cout<<ans;
    return 0;
}
```
    - **核心思想**：先将矩阵数据转换为边集，再对边按权值排序，使用并查集判断边的两个端点是否在同一集合，若不在则加入生成树，直到包含所有点。

2. **作者：Strong_Jelly（4星）**
    - **关键亮点**：详细介绍了Prim和Kruskal两种算法的原理、时间复杂度，并给出了对应的代码实现，适合初学者学习。
    - **Prim算法核心代码**：
```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int n, q[1001][1001], minn[100001], ans;
bool f[100001];
int main()
{
    memset(minn, INF, sizeof(minn));
    minn[1] = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%d", &q[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        int k = 0;
        for(int j = 1; j <= n; j++){
            if(!f[j] && minn[j] < minn[k]){
                k = j;
            }
        }
        f[k] = true;
        for(int j = 1; j <= n; j++){
            if(!f[j] && q[k][j] < minn[j]){
                minn[j] = q[k][j];
            }
        }
    }
    for(int i = 1; i <= n; i++){
        ans += minn[i];
    }
    printf("%d", ans);
    return 0;
} 
```
    - **核心思想**：从一个点开始，不断选择与当前生成树相连的最小边扩展，更新不在生成树中的点到生成树的最小边权，直到所有点加入生成树。

3. **作者：yyy2015c01（4星）**
    - **关键亮点**：使用堆优化的Prim算法，对于稠密图在理论时间复杂度上有优势，代码注释详细。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 105
struct Node{
    int a, b;
    int w;
    bool operator <(const struct Node &n)const{
        return w> n.w;
    }
};
priority_queue <Node> edge;
vector <Node> G[maxn];
bool visted[maxn];
int main()
{
    int N;
    scanf("%d", &N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++) {
            int tmp;
            scanf("%d",&tmp);
            if (tmp==0) continue;
            else {
                G[i].push_back(Node{i, j, tmp});
                G[j].push_back(Node{j, i, tmp});
            }
        }
    visted[1] = true;
    for(int i=0; i< G[1].size(); i++)
        edge.push(G[1][i]);
    int all =0;
    int cnt = 0;
    while(cnt < N-1){
        int w = edge.top().w;
        int n = edge.top().b;
        edge.pop();
        if (visted[n])
            continue;
        visted[n] = true;
        all += w;
        cnt ++;
        for (int i=0; i< G[n].size(); i++)
        {
            if (!visted[G[n][i].b])
                edge.push(G[n][i]);
        }
    }
    printf("%d\n", all);
    return 0;
}
```
    - **核心思想**：使用优先队列（堆）存储待选边，每次选择边权最小的边，将其连接的点加入生成树，并更新待选边集。

### 最优关键思路或技巧
- **数据存储优化**：由于输入是对称矩阵，只存储上三角或下三角部分，减少空间和时间开销。
- **算法选择**：稠密图优先考虑Prim算法，稀疏图优先考虑Kruskal算法。
- **路径压缩**：在并查集中使用路径压缩，提高查找效率。

### 可拓展之处
同类型题或类似算法套路：
- 带限制条件的最小生成树问题，如边权有上下界、边有数量限制等。
- 次小生成树问题，在最小生成树的基础上寻找次小的生成树。

### 推荐题目
- P3366 【模板】最小生成树
- P1194 买礼物
- P2820 局域网

### 个人心得摘录与总结
- **司徒stuart**：提醒不要用`vis`数组判断点是否合并，因为即使点被访问过，也不能说明它们连接到同一个图里，要使用并查集判断。
- **s66104444**：使用Kruskal算法时，边数组要开足够大，否则可能导致部分数据无法存储而WA。 

---
处理用时：47.49秒