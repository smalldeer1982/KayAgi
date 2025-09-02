# 题目信息

# The Road to Berland is Paved With Good Intentions

## 题目描述

Berland has $ n $ cities, some of them are connected by bidirectional roads. For each road we know whether it is asphalted or not.

The King of Berland Valera II wants to asphalt all roads of Berland, for that he gathered a group of workers. Every day Valera chooses exactly one city and orders the crew to asphalt all roads that come from the city. The valiant crew fulfilled the King's order in a day, then workers went home.

Unfortunately, not everything is as great as Valera II would like. The main part of the group were gastarbeiters — illegal immigrants who are enthusiastic but not exactly good at understanding orders in Berlandian. Therefore, having received orders to asphalt the roads coming from some of the city, the group asphalted all non-asphalted roads coming from the city, and vice versa, took the asphalt from the roads that had it.

Upon learning of this progress, Valera II was very upset, but since it was too late to change anything, he asked you to make a program that determines whether you can in some way asphalt Berlandian roads in at most $ n $ days. Help the king.

## 样例 #1

### 输入

```
4 4
1 2 1
2 4 0
4 3 1
3 2 0
```

### 输出

```
4
3 2 1 3
```

## 样例 #2

### 输入

```
3 3
1 2 0
2 3 0
3 1 0
```

### 输出

```
Impossible
```

# AI分析结果

### 题目内容
# 通往伯兰的道路是由善意铺就的

## 题目描述
伯兰有$n$个城市，其中一些城市由双向道路相连。对于每条道路，我们知道它是否已铺好沥青。

伯兰国王瓦莱拉二世希望为伯兰的所有道路铺上沥青，为此他召集了一群工人。每天，瓦莱拉都会选择一个城市，并命令工人为从该城市出发的所有道路铺上沥青。英勇的工人们在一天内完成了国王的命令，然后回家了。

不幸的是，事情并不像瓦莱拉二世希望的那样顺利。这群工人的主要部分是外籍劳工——非法移民，他们热情高涨，但不太擅长理解伯兰语的命令。因此，在接到为某个城市出发的道路铺沥青的命令后，这群工人为该城市出发的所有未铺沥青的道路铺上了沥青，反之，将已铺沥青的道路的沥青铲除了。

得知这一进展后，瓦莱拉二世非常沮丧，但由于为时已晚，无法改变任何事情，他请你编写一个程序，判断是否可以在最多$n$天内以某种方式为伯兰的道路铺上沥青。帮帮国王吧。

## 样例 #1
### 输入
```
4 4
1 2 1
2 4 0
4 3 1
3 2 0
```
### 输出
```
4
3 2 1 3
```

## 样例 #2
### 输入
```
3 3
1 2 0
2 3 0
3 1 0
```
### 输出
```
Impossible
```

### 算法分类
图论（2 - sat 问题、染色法、种类并查集应用于图的边约束问题）

### 题解综合分析与结论
这些题解主要围绕如何将题目中的边约束条件转化为可求解的模型。核心思路是利用每个点操作次数为0次或1次的特性（因为操作偶数次与0次效果相同），根据边权值建立不同点之间操作状态的逻辑关系。
 - **2 - sat解法**：将每个点的操作状态设为布尔变量，依据边权值为0或1，建立如“若点$x$操作，则点$y$不操作”等逻辑关系，转化为有向边连接相应的点（每个变量建两个点，分别表示真和假），通过判断是否存在矛盾（同一变量的真假点在同一强连通分量）来确定是否有解，并用拓扑序确定解的取值。
 - **染色法**：根据边权值对相邻点进行染色，权值为0染不同色，权值为1染相同色，若染色过程出现矛盾则无解，否则统计一种颜色的点得到操作方案。
 - **种类并查集解法**：把点按操作状态分为两个集合，根据边权值将相关点合并到同一集合或不同集合，若出现某个点与其对应另一状态点在同一集合则无解，否则可通过集合关系得到操作方案。

### 所选的题解
#### 作者：RainFestival (5星)
 - **关键亮点**：思路清晰简洁，直接点明用2 - sat解决问题，代码实现规范，对2 - sat算法的应用熟练，变量命名清晰，整体可读性高。
 - **核心代码片段**：
```cpp
#include<cstdio>
#include<vector>
#include<queue>
#define o(x) (x+2*(x<=n)*n-n)
std::queue<int> q;
std::vector<int> a[200005];
int n,m,f[200005];
void add(int x,int y){a[x].push_back(y);a[y].push_back(x);}
int dfs(int v)
{
    for (int i=0;i<a[v].size();i++)
    {
        int u=a[v][i];
        if (f[u]==-1)
        {
            f[u]=1;f[o(u)]=0;
            q.push(u),q.push(o(u));
            if (!dfs(u)) return 0;
        }
        else if (f[u]==0) return 0;
    }
    return 1;
}
int twosat()
{
    for (int i=1;i<=2*n;i++) f[i]=-1;
    for (int i=1;i<=n;i++)
        if (f[i]==-1)
        {
            while (!q.empty()) q.pop();
            f[i]=1,f[i+n]=0;q.push(i),q.push(i+n);
            if (dfs(i)) continue;
            while (!q.empty()) f[q.front()]=-1,q.pop();
            f[i]=0,f[i+n]=1;q.push(i),q.push(i+n);
            if (dfs(i+n)) continue;
            while (!q.empty()) f[q.front()]=-1,q.pop();
            return 0;
        }
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        v?(add(x,y),add(x+n,y+n)):(add(x+n,y),add(x,y+n));
    }
    if (!twosat()) puts("Impossible");
    else
    {
        int cnt=0;
        for (int i=1;i<=n;i++) if (f[i]) ++cnt;
        printf("%d\n",cnt);
        for (int i=1;i<=n;i++) if (f[i]) printf("%d ",i);
        puts("");
    }
    return 0;
}
```
核心实现思想：通过`add`函数根据边权值添加边，`dfs`函数用于深度优先搜索判断可行性，`twosat`函数实现2 - sat算法的核心流程，在`main`函数中读入数据并调用相关函数求解。

#### 作者：water_tomato (4星)
 - **关键亮点**：题意解析清晰，将问题转化为染色问题，利用dfs实现染色过程，代码简洁明了，逻辑清晰。
 - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,cnt,head[N];
int vis[N];//染色为 0 or 1
bool impossible;
struct edge{
    int to,next,color;
}e[N<<1];
inline void add(int x,int y,int co){
    e[++cnt].to=y;
    e[cnt].color=co;
    e[cnt].next=head[x];
    head[x]=cnt;
}
inline void dfs(int u,int color){
    if(impossible) return;
    vis[u]=color;
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to,flag=e[i].color;
        if(flag==0){
            if(vis[v]==3){
                dfs(v,color^1);
            }
            else{
                if(vis[v]==vis[u]) impossible=true;
            }
        }
        else{
            if(vis[v]==3){
                dfs(v,color);
            }
            else{
                if(vis[v]!=vis[u]) impossible=true;
            }
        }
        if(impossible) return;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,co;i<=m;i++){
        scanf("%d%d%d",&x,&y,&co);
        add(x,y,co);add(y,x,co);
    }
    for(int i=1;i<=n;i++){
        vis[i]=3;
    }
    for(int i=1;i<=n;i++){
        if(vis[i]==3) dfs(i,0);
    }
    if(impossible){
        printf("Impossible");
        return 0;
    } 
    int ans=0;
    for(int i=1;i<=n;i++){
        if(vis[i]==0) ans++;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(vis[i]==0) printf("%d ",i);
    }
    return 0;   
}
```
核心实现思想：通过`add`函数构建图，`dfs`函数依据边权值对相邻点染色，`main`函数读入数据并启动染色过程，最后根据染色结果判断是否有解并输出方案。

#### 作者：Feyn (4星)
 - **关键亮点**：提出用种类并查集解决问题，分析了种类并查集和2 - sat适用范围的区别，为解决此类问题提供了新的思路。
 - **核心代码片段**：
```cpp
int f[N],m,n;
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void merge(int x,int y){f[find(x)]=find(y);}

bool vis[N];
vector<int>ans;

signed main(){

    read(m);read(n);int x,y,v;
    for(int i=1;i<=m*2;i++)f[i]=i;
    while(n--){
        read(x);read(y);read(v);
        if(v)merge(x,y),merge(x+m,y+m);
        else merge(x,y+m),merge(x+m,y);
    }
    for(int i=1;i<=m;i++)if(find(i)==find(i+m))return printf("Impossible\n"),0;
    for(int i=1;i<=m;i++){
        if(vis[i]||vis[i+m])continue;int nowf=find(i);
        for(int j=1;j<=2*m;j++)if(find(j)==nowf)vis[j]=true,j<=m&&(ans.push_back(j),true);
    }
    printf("%d\n",ans.size());for(int i:ans)printf("%d ",i);

    return 0;
}
```
核心实现思想：通过`find`和`merge`函数实现并查集的查找和合并操作，在`main`函数中根据边权值合并相关点，最后通过判断和遍历并查集确定是否有解及操作方案。

### 最优关键思路或技巧
 - **模型转化**：将实际问题转化为图论中的2 - sat、染色或种类并查集模型，利用这些模型的特性解决边约束问题。
 - **状态简化**：发现每个点操作次数仅需考虑0次或1次，简化问题的求解空间。

### 可拓展思路
此类题目核心在于将条件约束转化为图的关系，类似套路可应用于其他存在二元状态选择且有条件约束的问题，如一些逻辑推理、资源分配等问题，可尝试用2 - sat、染色法、并查集等方法解决。

### 相似知识点洛谷题目
 - [P4782 【模板】2 - SAT 问题](https://www.luogu.com.cn/problem/P4782)
 - [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)
 - [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024) 

---
处理用时：97.74秒