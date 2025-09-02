# 题目信息

# Exploration plan

## 题目描述

The competitors of Bubble Cup X gathered after the competition and discussed what is the best way to get to know the host country and its cities.

After exploring the map of Serbia for a while, the competitors came up with the following facts: the country has $ V $ cities which are indexed with numbers from $ 1 $ to $ V $ , and there are $ E $ bi-directional roads that connect the cites. Each road has a weight (the time needed to cross that road). There are $ N $ teams at the Bubble Cup and the competitors came up with the following plan: each of the $ N $ teams will start their journey in one of the $ V $ cities, and some of the teams share the starting position.

They want to find the shortest time $ T $ , such that every team can move in these $ T $ minutes, and the number of different cities they end up in is at least $ K $ (because they will only get to know the cities they end up in). A team doesn't have to be on the move all the time, if they like it in a particular city, they can stay there and wait for the time to pass.

Please help the competitors to determine the shortest time $ T $ so it's possible for them to end up in at least $ K $ different cities or print -1 if that is impossible no matter how they move.

Note that there can exist multiple roads between some cities.

## 说明/提示

Three teams start from city 5, and two teams start from city 2. If they agree to move for 3 minutes, one possible situation would be the following: Two teams in city 2, one team in city 5, one team in city 3 , and one team in city 1. And we see that there are four different cities the teams end their journey at.

## 样例 #1

### 输入

```
6 7 5 4
5 5 2 2 5
1 3 3
1 5 2
1 6 5
2 5 4
2 6 7
3 4 11
3 5 3
```

### 输出

```
3```

# AI分析结果



---

## **唯一算法分类**  
网络流/二分图匹配

---

## **题解思路与解决难点**  
**核心思路**：  
1. **Floyd预处理全源最短路**  
   所有城市间最短路径预先计算，为后续验证提供基础数据。  
2. **二分答案确定最小时间**  
   时间具有单调性：若时间T可行，则更大时间必然可行。  
3. **二分图匹配/网络流验证覆盖可行性**  
   对每个二分值T，构建图模型验证是否至少K个城市被覆盖。  

**关键难点与解决**：  
- **如何高效验证时间T的可行性**  
  将团队与城市视为二分图，团队可到达的城市连边，转化为最大匹配问题。  
- **处理多起点多终点的覆盖问题**  
  网络流建模：源点连接团队节点，城市节点连接汇点，团队与可达城市连边。  

---

## **题解评分**  
**推荐题解（评分≥4星）**  
1. **BigJoker（4.5星）**  
   - **亮点**：简洁的匈牙利算法实现，代码易读，逻辑清晰。  
   - **关键代码**：`check`函数中使用匈牙利算法进行二分图匹配。  
2. **JWRuixi（4星）**  
   - **亮点**：Dinic网络流实现高效，适合大规模数据。  
   - **关键代码**：`check`函数通过Dinic计算最大流。  
3. **lzyqwq（4星）**  
   - **亮点**：使用匈牙利算法优化，`vector`建图提高效率。  

---

## **最优思路提炼**  
1. **二分答案框架**  
   - 确定时间范围，通过二分快速缩小最优解区间。  
2. **Floyd预处理最短路径**  
   - 计算所有城市间的最短时间，复杂度O(V³)。  
3. **二分图最大匹配验证**  
   - 左部为团队，右部为城市，边表示可达性（时间≤T）。  
   - 最大匹配数≥K则T可行，否则不可行。  

**代码核心逻辑**：  
```cpp
bool check(int T) {
    构建团队到可达城市的边;
    计算最大匹配数;
    return 匹配数 >= K;
}
```

---

## **类似题目与算法套路**  
1. **二分答案+图论模型**  
   - 如「网络延时」问题：二分时间，验证网络连通性。  
2. **多源覆盖问题**  
   - 使用网络流或匹配解决资源分配与覆盖需求。  

---

## **推荐题目**  
1. **P2763 试题库问题**（网络流建模分配试题）  
2. **P1402 酒店之王**（二分图多重匹配）  
3. **P2756 飞行员配对方案问题**（经典二分图匹配）  

---

## **可视化与算法演示**  
**动画设计**：  
1. **Floyd过程可视化**  
   - 网格展示城市间距离更新，高亮当前中间节点k。  
   - 颜色标记最短路径变化（如红色表示更新）。  
2. **二分答案与验证**  
   - 动态调整二分区间，展示当前T值。  
   - 构建二分图：团队节点与可达城市连绿色边。  
3. **匹配过程演示**  
   - 匈牙利算法：逐团队尝试匹配，回溯时用黄色标记。  
   - 网络流：流动动画显示增广路径，流量更新为蓝色。  

**复古像素风格**：  
- **8位颜色调色板**：城市用不同色块，团队为像素小人图标。  
- **音效**：匹配成功时播放“叮”声，失败时“哔”声。  
- **Canvas动画**：网格化城市节点，团队移动路径用虚线动态绘制。  

---

## **核心代码片段**  
**Floyd预处理最短路径**：  
```cpp
for (int k = 1; k <= V; k++)
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
```

**Dinic网络流验证（JWRuixi题解）**：  
```cpp
bool check(int T) {
    // 清空图并重新建边
    reset_graph();
    for (int i = 1; i <= N; i++) {
        add_edge(S, i, 1); // 源点→团队
        for (int j = 1; j <= V; j++)
            if (dis[team_pos[i]][j] <= T)
                add_edge(i, j + N, 1); // 团队→可达城市
    }
    for (int j = 1; j <= V; j++)
        add_edge(j + N, T, 1); // 城市→汇点
    return dinic() >= K; // 计算最大流
}
```

---

**完整代码（BigJoker题解）**  
```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
using namespace std;
const int N=6e2+5;
int n,m,h,g,vis[N],x[N],cp[N],dis[N][N];
vector<int>G[N];

bool dfs(int pos,int tag){
    if(vis[pos]==tag) return 0;
    vis[pos]=tag;
    for(auto to:G[pos]){
        if(!cp[to] || dfs(cp[to],tag)){
            cp[to]=pos;
            return 1;
        }
    }
    return 0;
}

bool check(int p){
    for(int i=1;i<=h;i++) G[i].clear(); 
    for(int i=1;i<=h;i++)
        for(int j=1;j<=n;j++) 
            if(dis[x[i]][j]<=p) 
                G[i].push_back(j);
    mem(vis,0); mem(cp,0);
    int res=0;
    for(int i=1;i<=h;i++) 
        res += dfs(i,i);
    return res>=g;
}

int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>h>>g;
    mem(dis,0x3f);
    for(int i=1;i<=h;i++) cin>>x[i];
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        dis[u][v]=dis[v][u]=min(dis[u][v],w);
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) 
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    if(!check(1731311)) cout<<-1;
    else{
        int l=0,r=1731311;
        while(l<r){
            int mid=(l+r)>>1;
            check(mid) ? r=mid : l=mid+1;
        }
        cout<<l;
    }
    return 0;
}
```

---
处理用时：83.52秒