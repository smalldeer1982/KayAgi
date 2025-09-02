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

本题是一个典型的最小生成树问题，常见的解法有**Prim算法**和**Kruskal算法**。大部分题解都采用了这两种算法，其中Kruskal算法由于其实现简单且易于理解，成为了多数题解的首选。Prim算法虽然在某些情况下效率更高，但实现相对复杂，尤其是需要维护优先队列时。整体来看，题解的质量参差不齐，部分题解代码冗长且缺乏注释，而部分题解则思路清晰、代码简洁。

### 精选题解

#### 1. **作者：chengni (赞：91)**
- **星级**：★★★★★
- **关键亮点**：使用Kruskal算法，代码简洁且注释清晰，通过并查集实现集合的合并与查找，避免了重复边的处理。
- **个人心得**：作者提到“读入时加一个判断就可以了，不需要读那么多”，强调了优化输入处理的重要性。
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
                a[m].x=i; a[m].y=j; a[m].w=k;	
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

#### 2. **作者：Strong_Jelly (赞：47)**
- **星级**：★★★★
- **关键亮点**：详细介绍了Prim和Kruskal算法的实现，代码结构清晰，适合初学者理解。
- **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, v, k, ans, fa[10000001];
struct node{
    int x, y, z;
}stu[100001];

bool cmp(node a, node b){
    return a.z < b.z;
}

int find(int x){
    if(x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}

int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++) fa[i] = i;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            scanf("%d", &v);
            if(j > i){
                m++;
                stu[m].x = i;
                stu[m].y = j;
                stu[m].z = v;
            }
        }
    }
    sort(stu+1, stu+m+1, cmp);
    for(int i=1; i<=m; i++){
        if(find(stu[i].x) != find(stu[i].y)){
            ans += stu[i].z;
            fa[find(stu[i].y)] = find(stu[i].x);
            k++;
            if(k == n-1) break;
        }
    }
    cout<<ans;
    return 0;
}
```

#### 3. **作者：yyy2015c01 (赞：22)**
- **星级**：★★★★
- **关键亮点**：提供了堆优化的Prim算法实现，适合处理稠密图，代码结构清晰且注释详细。
- **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 105
struct Node{
    int a, b, w;
    bool operator <(const struct Node &n)const{
        return w > n.w;
    }
};
priority_queue<Node> edge;
vector<Node> G[maxn];
bool visted[maxn];

int main(){
    int N;
    scanf("%d", &N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++) {
            int tmp;
            scanf("%d",&tmp);
            if (tmp==0) continue;
            G[i].push_back(Node{i, j, tmp});
            G[j].push_back(Node{j, i, tmp});
        }
    visted[1] = true;
    for(int i=0; i< G[1].size(); i++)
        edge.push(G[1][i]);
    int all =0, cnt = 0;
    while(cnt < N-1){
        int w = edge.top().w;
        int n = edge.top().b;
        edge.pop();
        if (visted[n]) continue;
        visted[n] = true;
        all += w;
        cnt ++;
        for (int i=0; i< G[n].size(); i++)
            if (!visted[G[n][i].b])
                edge.push(G[n][i]);
    }
    printf("%d\n", all);
    return 0;
}
```

### 最优关键思路与技巧

1. **Kruskal算法**：通过并查集实现集合的合并与查找，确保生成树中不形成环。边按权值排序后，依次选择最小边并合并集合，直到生成树包含所有节点。
2. **Prim算法**：通过维护一个优先队列，每次选择与当前生成树距离最小的节点加入生成树，适合稠密图。
3. **输入优化**：对于对称矩阵，只需读取一半的数据，减少不必要的输入处理。

### 可拓展之处

- **堆优化Prim**：在处理稠密图时，堆优化的Prim算法效率更高，适合进一步学习。
- **并查集优化**：路径压缩和按秩合并可以进一步提升Kruskal算法的效率。

### 推荐题目

1. **P3366 【模板】最小生成树**：标准的Kruskal和Prim算法模板题。
2. **P2820 局域网**：最小生成树的变种，考察对算法的理解。
3. **P1991 无线通讯网**：最小生成树的应用，结合实际场景进行算法设计。

### 个人心得总结

- **调试经历**：部分题解提到在调试过程中发现并查集的路径压缩未正确实现，导致超时。这提醒我们在实现并查集时要注意路径压缩的正确性。
- **顿悟感想**：通过本题，许多作者意识到最小生成树算法的核心在于贪心策略，选择合适的边并确保不形成环是解决问题的关键。

---
处理用时：55.05秒