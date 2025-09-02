# 题目信息

# [USACO2.4] 回家 Bessie Come Home

## 题目描述

现在是晚餐时间，而母牛们在外面分散的牧场中。 

Farmer John 按响了电铃，所以她们开始向谷仓走去。 你的工作是要指出哪只母牛会最先到达谷仓（在给出的测试数据中，总会**有且只有**一只最快的母牛）。在挤奶的时候（晚餐前），每只母牛都在她自己的牧场上，一些牧场上可能没有母牛。

每个牧场由一条条道路和一个或多个牧场连接（可能包括自己）。有时，两个牧场（可能是字母相同的）之间会有超过一条道路相连。至少有一个牧场和谷仓之间有道路连接。因此，所有的母牛最后都能到达谷仓，并且母牛总是走最短的路径。当然，母牛能向着任意一方向前进，并且她们以相同的速度前进。牧场被标记为 $\texttt{a} \ldots \texttt{z}$ 和 $\texttt{A} \ldots \texttt{Y}$，在用大写字母表示的牧场中有一只母牛，小写字母中则没有。 谷仓的标记是 $\texttt{Z}$，注意没有母牛在谷仓中。

**注意 $\texttt{m}$ 和 $\texttt{M}$ 不是同一个牧场**。

## 说明/提示

翻译来自 NOCOW

USACO 2.4


## 样例 #1

### 输入

```
5
A d 6
B d 3
C e 9
d Z 8
e Z 3```

### 输出

```
B 11
```

# AI分析结果

### 综合分析与结论
本题是一个无向图求最短路的问题，数据规模较小（最多 52 个点），因此多种最短路算法都可适用。题解中涉及的算法有 Floyd、Dijkstra（包括朴素版、堆优化版）、SPFA、Bellman - Ford 以及暴力搜索等。

#### 思路对比
- **Floyd 算法**：计算所有点对之间的最短路径，通过枚举中间点更新最短距离，适用于本题求所有有牛牧场到谷仓的最短路径。
- **Dijkstra 算法**：以谷仓为起点，求到各个有牛牧场的最短路径。可使用邻接矩阵或邻接表存储图，堆优化版能降低时间复杂度。
- **SPFA 算法**：对 Bellman - Ford 算法的优化，使用队列来维护待松弛的节点。
- **Bellman - Ford 算法**：通过多次松弛操作更新最短路径。
- **暴力搜索**：使用深度优先搜索（DFS）结合记忆化剪枝，遍历所有可能路径找到最短路径。

#### 算法要点对比
- **Floyd 算法**：三重循环更新最短路径，时间复杂度为 $O(n^3)$。
- **Dijkstra 算法**：朴素版时间复杂度为 $O(n^2)$，堆优化版为 $O((n + m)logn)$。
- **SPFA 算法**：平均时间复杂度为 $O(km)$，但最坏情况下为 $O(nm)$。
- **Bellman - Ford 算法**：时间复杂度为 $O(nm)$。
- **暴力搜索**：时间复杂度较高，但对于小规模数据可通过剪枝优化。

#### 解决难点对比
- **字符处理**：大部分题解将字符转换为数字编号，如将 'a' - 'z' 映射到 1 - 26，'A' - 'Z' 映射到 27 - 52，方便使用数组存储图。
- **重边处理**：在输入时，对于重复的边取最短的边权。

### 高评分题解
1. **作者：封禁用户（赞：26）** - 5 星
    - **关键亮点**：思路清晰，使用 Floyd 算法解决问题，代码简洁易懂，对字符处理和重边处理都有明确的实现。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1<<30;
int dist[60][60];
int getnum(char c){
    if(c>='a'&&c<='z')return c-'a'+26;
    else return c-'A';
}
int main(){
    for(int i=0;i<60;i++)for(int j=0;j<60;j++)dist[i][j]=inf-1;
    int m;
    cin>>m;
    while(m--){
        string s1,s2;int d;
        cin>>s1>>s2>>d;
        dist[getnum(s1[0])][getnum(s2[0])]=min(dist[getnum(s1[0])][getnum(s2[0])],d);
        dist[getnum(s2[0])][getnum(s1[0])]=min(dist[getnum(s2[0])][getnum(s1[0])],d);
    }
    for(int k=0;k<60;k++)for(int i=0;i<60;i++)for(int j=0;j<60;j++)if(dist[i][k]+dist[k][j]<dist[i][j])dist[i][j]=dist[i][k]+dist[k][j];
    char ansc;int ans=inf;
    for(int i=0;i<25;i++)if(dist[i][25]<=ans){
        ans=dist[i][25];ansc=i+'A';
    }
    cout<<ansc<<" "<<ans<<endl;
    return 0;
}
```
    - **核心思想**：先将字符转换为数字编号，使用邻接矩阵存储图，处理重边时取最短边权。然后使用 Floyd 算法计算所有点对之间的最短路径，最后找出到谷仓最短路径的有牛牧场。

2. **作者：Gamin（赞：23）** - 4 星
    - **关键亮点**：详细解释了思路，使用 Dijkstra 算法结合邻接矩阵，对字符处理和重边处理有清晰的说明，代码注释丰富。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 99999999
using namespace std;
int dis[100],tu[100][100];
int p,vis[100];
char r;
void di(int x,int y,int w){
    if(tu[x][y]==0){
        tu[x][y]=w;
        tu[y][x]=w;
    }
    if(w<tu[x][y]){
        tu[x][y]=w; 
        tu[y][x]=w;
    }
} 
void dj(){
    int u,min;
    for(int i=1;i<=51;i++){
        min=MAXN;
        for(int j=1;j<=51;j++){
            if(vis[j]==0&&dis[j]<min){
                min=dis[j];
                u=j;
            }
        }
        vis[u]=1;
        for(int v=1;v<=51;v++){
            if(dis[v]>dis[u]+tu[u][v]&&vis[v]==0&&tu[u][v]<MAXN)
                dis[v]=dis[u]+tu[u][v];
        }
    }
}
int main(){
    scanf("%d",&p);
    for(int i=1;i<=52;i++)
        for(int j=1;j<=51;j++)
            tu[i][j]=MAXN;
    vis[52]=1;
    for(int i=1;i<=p;i++){
        char x,y;int c;
        int xx,yy;
        scanf("\n%c %c %d",&x,&y,&c);
        if(x>='a'&&x<='z') xx=x-'a'+1;
        else xx=x-'A'+27;
        if(y>='a'&&y<='z') yy=y-'a'+1;
        else yy=y-'A'+27;
        di(xx,yy,c);
    }
    for(int i=1;i<=51;i++)
        dis[i]=tu[52][i];
    dj();
    int hh=MAXN,point;
    for(int i=1;i<=51;i++){
        if(dis[i]<hh&&i>=27){
            hh=dis[i];
            point =i;
        }
    }
    r=point-27+'A';
    printf("%c %d\n",r,hh);
} 
```
    - **核心思想**：将字符转换为数字编号，使用邻接矩阵存储图，处理重边时取最短边权。以谷仓为起点，使用 Dijkstra 算法计算到各个牧场的最短路径，最后找出到谷仓最短路径的有牛牧场。

3. **作者：agicy（赞：1）** - 4 星
    - **关键亮点**：使用 Dijkstra 算法结合邻接表和堆优化，思路清晰，代码结构良好，对命名空间的使用进行了处理，避免了污染。
    - **核心代码**：
```cpp
#include<stdio.h>
#include<string.h>
#include<iostream>
using std::cin;
#include<queue>
using std::priority_queue;
using std::vector;
using std::greater;
#define INF 0X3F3F3F3F
struct Node{
    int len;
    int to;
    bool operator>(Node a)const{
        return this->len>a.len;
    }
};
bool f[20001];
int p,head[128],Next[20001],to[20001],len[20001],d[20001],l=INF,ans;
Node temp;
priority_queue<Node,vector<Node>,greater<Node> > Q;
void Dijkstra(int start){
    memset(d,0X3F,sizeof(d));
    memset(f,0,sizeof(f));
    d[start]=0;
    temp.len=0,temp.to=start;
    Q.push(temp);
    while(Q.size()){
        temp=Q.top();
        char now=temp.to;
        Q.pop();
        if(f[now])
            continue;
        f[now]=true;
        for(int i=head[now];i;i=Next[i]){
            int node_next=to[i],len_this_way=len[i];
            if(d[node_next]>d[now]+len_this_way)
                d[node_next]=d[now]+len_this_way,
                temp.len=d[node_next],temp.to=node_next,
                Q.push(temp);
        }
    }
}
int main(void){
    scanf("%d",&p);
    for(int i=1,w;i<=(p<<1);i+=2){
        char f,g;
        cin>>f>>g;
        scanf("%d",&w);
        Next[i]=head[f];
        head[f]=i;
        to[i]=g;
        len[i]=w;
        Next[i+1]=head[g];
        head[g]=i+1;
        to[i+1]=f;
        len[i+1]=w;
    }
    Dijkstra('Z');
    for(int i='A';i<='Y';i++)
        if(d[i]<l)
            l=d[i],ans=i;
    printf("%c %d",ans,l);
    return 0;
}
```
    - **核心思想**：使用邻接表存储图，处理重边时取最短边权。以谷仓为起点，使用堆优化的 Dijkstra 算法计算到各个牧场的最短路径，最后找出到谷仓最短路径的有牛牧场。

### 最优关键思路或技巧
- **字符处理**：将字符转换为数字编号，方便使用数组存储图，如将 'a' - 'z' 映射到 1 - 26，'A' - 'Z' 映射到 27 - 52。
- **重边处理**：在输入时，对于重复的边取最短的边权。
- **算法选择**：根据数据规模选择合适的算法，本题数据规模较小，多种算法都可适用，Floyd 算法实现简单，Dijkstra 算法（尤其是堆优化版）效率较高。

### 可拓展之处
- **同类型题**：其他无向图求最短路的问题，如城市间的最短路径、网络中的最短传输路径等。
- **类似算法套路**：在处理图论问题时，根据数据规模和图的特点选择合适的算法和数据结构，如稀疏图使用邻接表，稠密图使用邻接矩阵；对于大规模数据，优先考虑优化算法，如堆优化的 Dijkstra 算法。

### 推荐题目
1. **P3371 【模板】单源最短路径（弱化版）**：考察 Dijkstra 算法和 SPFA 算法的基本应用。
2. **P4779 【模板】单源最短路径（标准版）**：考察堆优化的 Dijkstra 算法。
3. **P1144 最短路计数**：在求最短路的基础上，统计最短路径的数量。

### 个人心得摘录与总结
- **作者：Caicz**：注意重边处理，否则会导致分数降低；对字符的处理可能是难点，建议尽量转换为常数，避免使用 ASCII 码直接进行松弛操作，调试时间会增加。
- **作者：Warriors_Cat**：注意题目要求，如本题是 'A' - 'Y' 有奶牛，被此坑调了半个多小时；暴力搜索结合记搜剪枝可以解决小规模数据的问题。
- **作者：Kdlyh**：对于无解判断问题，可以通过分析程序复杂度，从循环执行次数入手判断是否超时，若超时则认为无解；也可利用 `<ctime>` 库计算程序运行时间。 

---
处理用时：80.00秒