# 题目信息

# [BalticOI 2005] Bus Trip

## 题目描述

这里有 $N$ 座城镇, 和城镇之间的 $M$ 巴士单行线(没有中间停靠站)。 城镇从$1$到 $N$ 标号。 一个旅行者在 $0$ 时刻位于 $1$ 号城镇想要到达 $P$ 号城镇。他将乘坐巴士在 $T$ 时刻到达 $P$ 号城镇。如果他早到了，他必须等待。

对于任意一个巴士路线 $i$ , 我们知道其中的起点城镇 $si$ 和目标城镇$ti$ 。我们也同样知道路线的出发时间和到达时间,但仅仅是近似值：我们知道巴士离开起点城镇 $si$ 在时间范围$[ai, bi]$内，且到达目标城镇 $ti$ 在时间范围$[ci, di]$内(端点值包括在内)。

旅行者不喜欢等待, 因此他要寻找一个旅行计划使得最大等待时间尽量小，同时保证绝对不会错过计划中的任何一辆巴士(意思是, 每次他换乘巴士, 他需要下车的巴士的最晚到达时间不会迟于他需要搭乘的下一辆巴士的最早出发时间)。

当计算等待时间时，我们必须假设最早可能到达的时间和最晚可能出发的时间。

编写一个程序，寻找一个最为合理的搭车计划。

## 说明/提示

翻译来自BZOJ P1354

## 样例 #1

### 输入

```
3 6 2 100
1 3 10 20 30 40
3 2 32 35 95 95
1 1 1 1 7 8
1 3 8 8 9 9
2 2 98 98 99 99
1 2 0 0 99 101```

### 输出

```
32```

# AI分析结果

• 综合分析与结论：这些题解的核心思路都是将求最大等待时间最小化的问题转化为最大化乘车时间问题。算法要点在于建图和求解最长路径。难点主要是如何优化建图以避免高复杂度边数。多数题解采用将每条公交线路拆分为起点和终点两个点，并按时间相关规则排序，然后通过拓扑排序或动态规划求解。部分题解通过辅助虚点或分层图等方式优化建图。

依据质量，以下为各题解评分：
 - WarningQAQ：5星。思路清晰，代码简洁，通过滚动数组优化动态规划，将原O(NM)复杂度优化，对状态转移分析到位。
 - lava__44：4星。参考WarningQAQ题解，思路清晰，代码注释较详细，对排序规则和变量含义解释清楚。
 - wei_xin：3星。思路较独特，建分层图并拓扑排序，但代码实现复杂，建点连边部分繁琐。
 - DrBit：3星。提出将线路看成点并通过拓扑排序求解，但边数优化部分代码较复杂，可读性一般。
 - wizard：4星。分析清晰，建图和排序思路明确，代码简洁明了。
 - Cells：4星。思路清晰，对拓扑排序的应用和状态转移分析详细，代码结构清晰。
 - 船酱魔王：3星。思路表述较简单，代码实现中结构体重载运算符部分稍复杂，整体可读性一般。
 - lyhqwq：3星。提出通过虚点和二分优化连边，但代码实现复杂，可读性欠佳。

所选4星及以上题解：
 - WarningQAQ（5星）
   - 关键亮点：将问题转化为中间乘坐公交最长时间问题，通过滚动数组优化动态规划，把原O(NM)复杂度的动规优化。将每条路拆分为两个点，按时间节点排序后顺序求最长路，有效减少转移次数。
   - 重点代码：
```cpp
#include"bits/stdc++.h"
#define N 50005
using namespace std;
//快读部分省略
int n=read(),m=read(),tt=read(),t=read(),x,y,a,b,c,d,tot;
int dis[N],ans[N*2];
struct ask{
    int x,t,id,dis;
}q[N*4];
bool cmp(const ask&a,const ask&b){
    return a.t==b.t?a.dis>b.dis:a.t<b.t;
}
int main(){
    for(int i=1;i<=m;i++){
        x=read();y=read();a=read();b=read();c=read();d=read(); 
        q[++tot]=(ask){x,a,i,0};
        q[++tot]=(ask){y,d,i,c-b};
    }
    q[++tot]=(ask){n+1,t,0,-0x3f3f3f3f};
    sort(q+1,q+tot+1,cmp);
    memset(dis,233,sizeof(dis));
    dis[1]=0;
    for (int i=1;i<=tot;i++){
        if(q[i].x==n+1)break;
        if(!q[i].dis)ans[q[i].id]=dis[q[i].x];
        else dis[q[i].x]=max(dis[q[i].x],ans[q[i].id]+q[i].dis);
    }
    return printf("%d",dis[tt]<0?-1:t-dis[tt]),0;
}
```
核心实现思想：将每条公交线路拆分为起点和终点两个点，记录点的位置、时间、线路编号及乘车耗时。按时间排序后，遍历每个点，若为起点则将对应线路的ans赋为到该点的dis值，若为终点则用该点的ans加上乘车耗时更新该点的dis值，最后根据结果输出等待时间或 -1。
 - lava__44（4星）
   - 关键亮点：思路清晰，参照优秀题解，对排序规则、变量含义及赋值规则解释详细，代码可读性较好。
   - 重点代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 500010
using namespace std;
int n,m,p,t,tote,dist[MAXN],ans[MAXN];
struct Bus {
    int x,t,idx,dist;
}b[MAXN];
void build(int x,int t,int idx,int dist){
    b[++tote]={x,t,idx,dist};
}
bool cmp(const Bus &x,const Bus &y){
    return x.t==y.t?x.dist>y.dist:x.t<y.t;
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m>>p>>t;
    for(int i=1,s,t,a,b,c,d;i<=m;i++){
        cin>>s>>t>>a>>b>>c>>d;
        build(s,a,i,0);
        build(t,d,i,c-b);
    }
    build(n+1,t,0,-0x3f3f3f3f);
    sort(b+1,b+tote+1,cmp);
    memset(dist,250,sizeof(dist));
    dist[1]=0;
    for(int i=1;i<=tote;i++){
        if(b[i].x==n+1) break;
        if(!b[i].dist) ans[b[i].idx]=dist[b[i].x];
        else dist[b[i].x]=max(dist[b[i].x],ans[b[i].idx]+b[i].dist);
    }
    (dist[p]<0)?cout<<"-1":cout<<t-dist[p];
    return 0;
}
```
核心实现思想：与WarningQAQ类似，将公交线路拆分为起点和终点两个点存储相关信息，按特定规则排序后，遍历点进行状态转移，更新dist数组，最后根据dist[p]的值输出结果。
 - wizard（4星）
   - 关键亮点：分析清晰，贪心地对每个车排序，在建图和排序思路上表述明确，代码简洁易懂。
   - 重点代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int n,m,p,t;
struct edge{
    int now,time,id,dis;
}e[maxn];
int dex,dis[maxn];
int ans[maxn];
void add(int a,int b,int c,int d){
    e[++dex]={a,b,c,d};
}
bool cmp(edge a,edge b){
    if(a.time==b.time){
        return a.dis>b.dis;
    }
    return a.time<b.time;
}
void topo(){
    sort(e+1,e+dex+1,cmp);
    memset(dis,128,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=dex;i++){
        if(e[i].now==n+1)break;
        if(!e[i].dis)ans[e[i].id]=dis[e[i].now];
        else if(dis[e[i].now]<ans[e[i].id]+e[i].dis){
            dis[e[i].now]=ans[e[i].id]+e[i].dis;
        }
    }
    if(dis[p]<0)cout << -1 << endl;
    else cout << t-dis[p] << endl;
}
signed main(){
    cin >> n >> m >> p >> t; 
    for(int i=1;i<=m;i++){
        int s,t,a,b,c,d;
        cin >> s >> t >> a >> b >> c >> d;
        add(s,a,i,0);
        add(t,d,i,c-b); 
    }
    add(n+1,t,0,-0x3f3f3f3f);
    topo(); 
    return 0;
}
```
核心实现思想：将公交线路拆成起点和终点两个点，存储相关信息，按时间和乘车耗时规则排序，通过拓扑排序的方式遍历点进行状态转移，更新dis数组，最后根据dis[p]输出结果。

最优关键思路或技巧：将最大等待时间最小化问题转化为最大化乘车时间问题，通过将每条公交线路拆分为起点和终点两个点，并按时间及乘车耗时相关规则排序，有效减少建图边数和计算量，利用拓扑排序或类似动态规划的方式求解最长乘车时间，进而得出最小等待时间。

可拓展思路：此类问题属于时间相关的图论优化问题，类似套路可应用于其他涉及时间约束、路径规划且需优化建图复杂度的题目。例如，在一些物流运输路径规划问题中，若存在时间窗口限制，可类似建图并优化求解。

推荐洛谷题目：
 - P1983 车站分级：涉及拓扑排序和图的建边优化，与本题在图论和排序优化上有相似点。
 - P3387 【模板】缩点：图论相关，通过缩点优化图结构求解最长路径，与本题优化建图求解问题思路类似。
 - P2880 [USACO07MAR]牛交通Cow Traffic：同样是时间相关的图论问题，需要合理建图并优化求解。

个人心得摘录与总结：
 - DrBit：提到如果目标点是1点，待在原地不动是一种可行决策，需特判（对应测试点2），强调了边界条件处理在调试中的重要性。 

---
处理用时：66.35秒