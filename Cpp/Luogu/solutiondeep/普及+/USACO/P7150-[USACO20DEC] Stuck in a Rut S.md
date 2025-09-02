# 题目信息

# [USACO20DEC] Stuck in a Rut S

## 题目描述

Farmer John 最近扩大了他的农场，从奶牛们的角度看来这个农场相当于是无限大了！奶牛们将农场上放牧的区域想作是一个由正方形方格组成的无限大二维方阵，每个方格中均有美味的草（将每个方格看作是棋盘上的一个方格）。Farmer John 的 $N$ 头奶牛（$1≤N≤1000$）初始时位于不同的方格中，一部分朝向北面，一部分朝向东面。

每一小时，每头奶牛会执行以下二者之一：

 - 如果她当前所在的方格里的草已经被其他奶牛吃掉了，则她会停下（并从这个时刻开始一直保持停止）。
 - 吃完她当前所在的方格中的所有草，并向她朝向的方向移动一个方格。

经过一段时间，每头奶牛的身后会留下一条被啃秃了的轨迹。

如果两头奶牛在一次移动中移动到了同一个有草的方格，她们会分享这个方格中的草，并在下一个小时继续沿她们朝向的方向移动。

当 Farmer John 看到停止吃草的奶牛时会不高兴，他想要知道谁该为他停止吃草的奶牛受到责备。如果奶牛 $b$
停在了之前奶牛 $a$ 吃过草的一个方格，我们就称奶牛 $a$ 阻碍了奶牛 $b$。进一步地，如果奶牛 $a$ 阻碍了奶牛 $b$ 且奶牛 $b$ 阻碍了奶牛 $c$，我们认为奶牛 $a$ 也阻碍了奶牛 $c$（也就是说，「阻碍」关系具有传递性）。每头奶牛受到责备的程度与这头奶牛阻碍的奶牛数量一致。请计算每头奶牛受到责备的数量——也就是说，每头奶牛阻碍的奶牛数量。 

## 说明/提示

在这个样例中，奶牛 3 阻碍了奶牛 2，奶牛 4 阻碍了奶牛 5，奶牛 5 阻碍了奶牛 6。根据传递性，奶牛 4 也阻碍了奶牛 6。 

 - 测试点 2-5 中，所有坐标不超过 $2000$。
 - 测试点 6-10 没有额外限制。

供题：Brian Dean 

## 样例 #1

### 输入

```
6
E 3 5
N 5 3
E 4 6
E 10 4
N 11 1
E 9 2```

### 输出

```
0
0
1
2
1
0
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路大多围绕将奶牛按方向分类，找出不同方向奶牛路径的交点，判断交点处哪头奶牛会被阻挡，再依据阻挡的传递性计算每头奶牛阻碍的数量。各题解在实现细节和数据结构使用上有所不同，如有的使用交点排序，有的借助离散化模拟，还有的采用拓扑排序、并查集等方法。

### 所选题解
- **作者：feicheng (赞：37)  4星**
    - **关键亮点**：思路清晰，详细阐述了如何维护交点以及判断交点顺序，代码实现简洁明了，易于理解。
    - **核心实现思想**：将奶牛按方向分为向北和向东两类，找出所有可能的交点，对交点按坐标排序，依次判断交点处哪头奶牛被阻挡，用删除数组标记被阻挡的奶牛，最后计算每头奶牛阻碍的数量。
    - **核心代码片段**：
```cpp
struct cows{
    int x,y,num;
}c[1100],nth[1100],est[1100];
struct point{
    int x,y;
    int numx,numy;
    bool operator < (const point others) const
    {
        if(this->x  == others.x){
            return this->y < others.y;
        }
        return this->x < others.x;
    }
}p[1100 * 1100 /4];
int n,cntn,cnte,cntp,ans[1100];
bool del[1100];
// ... 输入部分 ...
for(int i = 1;i <= cntn;i++){
    for(int j = 1;j <= cnte;j++){
        if(nth[i].x > est[j].x && nth[i].y < est[j].y){
            p[++cntp].x = nth[i].x;
            p[cntp].y = est[j].y;
            p[cntp].numx = est[j].num;
            p[cntp].numy = nth[i].num;
        }
    }
}
sort(p + 1,p + 1 + cntp);
for(int i = 1;i <= cntp;i++){
    if(del[p[i].numx] || del[p[i].numy]){
        continue;
    }
    int dx = p[i].x - c[p[i].numx].x;
    int dy = p[i].y - c[p[i].numy].y;
    if(dx < dy){
        del[p[i].numy] = 1;
        ans[p[i].numx] = ans[p[i].numx] + ans[p[i].numy] + 1;
    }
    if(dx > dy){
        del[p[i].numx] = 1;
        ans[p[i].numy] = ans[p[i].numy] + ans[p[i].numx] + 1;
    }
}
```
- **作者：_zy_ (赞：9)  4星**
    - **关键亮点**：思路清晰，对交点的处理和相交顺序的判断有详细说明，代码结构清晰。
    - **核心实现思想**：同样将奶牛按方向分类，找出所有交点，按坐标排序，枚举交点判断哪头奶牛被阻挡，用标记数组记录被阻挡的奶牛，最后输出每头奶牛阻碍的数量。
    - **核心代码片段**：
```cpp
struct zy {
    int op;
    int x,y;
    int ans;
}e[N];
struct Point {
    int id_1,id_2;
    int x,y;
}w[N];
bool cmp(Point x,Point y) {
    if(x.x==y.x)
        return x.y<y.y;
    return x.x<y.x;
}
// ... 输入部分 ...
int cnt=0;
for(int i=1;i<=n;i++)
    for(int j=i+1;j<=n;j++)
    {
        if(e[i].op==e[j].op) continue;
        if(e[i].op&&!e[j].op&&e[i].x<e[j].x&&e[i].y>e[j].y) {
            w[++cnt].x=e[j].x;
            w[cnt].y=e[i].y;
            w[cnt].id_1=i;
            w[cnt].id_2=j;
        }
        if(!e[i].op&&e[j].op&&e[j].x<e[i].x&&e[j].y>e[i].y) {
            w[++cnt].x=e[i].x;
            w[cnt].y=e[j].y;
            w[cnt].id_1=j;
            w[cnt].id_2=i;
        }
    }
sort(w+1,w+cnt+1,cmp);
for(int i=1;i<=cnt;i++)
{
    int est=w[i].id_1;
    int nor=w[i].id_2;
    if(used[est]||used[nor]) continue;
    if(abs(w[i].x-e[est].x)>abs(w[i].y-e[nor].y)) {
        used[est]=1;
        e[nor].ans+=e[est].ans+1;
    }
    if(abs(w[i].x-e[est].x)<abs(w[i].y-e[nor].y)) {
        used[nor]=1;
        e[est].ans+=e[nor].ans+1;
    }
}
```
- **作者：wsyhb (赞：7)  4星**
    - **关键亮点**：提供了两种代码实现，一种是赛时代码，使用缩点 + 拓扑排序 + bitset，另一种是赛后优化代码，使用建反图拓扑排序，对思路和条件判断有详细解释。
    - **核心实现思想**：枚举所有可能的直接阻碍关系，记录奶牛到达交点的时间，按较晚时间排序，判断阻碍关系是否真实存在，将阻碍关系看成有向边，转化为森林，最后用拓扑排序计算每头奶牛阻碍的数量。
    - **核心代码片段（赛后代码）**：
```cpp
struct node
{
    int a,b,t1,t2;
}p[max_cnt];
bool cmp(node x,node y)
{
    return x.t2<y.t2;
}
bool mark[max_N];
int over_time[max_N];
// ... 输入部分 ...
int cnt=0;
for(int i=1;i<=N;++i)
    for(int j=1;j<=N;++j)
    {
        if(i!=j&&op[i][0]=='E'&&op[j][0]=='N'&&x[i]<=x[j]&&y[i]>=y[j])
        {
            p[++cnt].a=i,p[cnt].b=j;
            p[cnt].t1=x[j]-x[i]+1,p[cnt].t2=y[i]-y[j]+1;
            if(p[cnt].t1>p[cnt].t2)
            {
                swap(p[cnt].a,p[cnt].b);
                swap(p[cnt].t1,p[cnt].t2);
            }
        }
    }
sort(p+1,p+cnt+1,cmp);
for(int i=1;i<=cnt;++i)
{
    if((mark[p[i].a]&&over_time[p[i].a]<p[i].t1)||mark[p[i].b]||p[i].t1==p[i].t2)
        continue;
    mark[p[i].b]=true;
    over_time[p[i].b]=p[i].t2;
    add_edge(p[i].b,p[i].a);
}
// ... 拓扑排序部分 ...
```

### 最优关键思路或技巧
- **分类处理**：将奶牛按方向分为向北和向东两类，简化问题分析。
- **交点处理**：找出不同方向奶牛路径的交点，通过比较奶牛到交点的距离判断哪头奶牛被阻挡。
- **排序优化**：对交点按坐标排序，确保按顺序处理交点，避免重复判断。
- **标记数组**：使用标记数组记录被阻挡的奶牛，避免无效的交点判断。

### 可拓展之处
同类型题目可能涉及更多方向的移动、不同的碰撞规则或更复杂的地图，类似算法套路包括分类讨论、找出关键节点（如交点）、排序处理、利用标记数组优化等。

### 推荐题目
- P1141 01迷宫：涉及连通性和路径问题，可通过搜索算法解决。
- P1330 封锁阳光大学：图论问题，可使用染色法判断二分图。
- P1601 A+B Problem（高精）：高精度计算问题，考察对大整数运算的处理。

### 个人心得摘录与总结
- **作者：wsyhb**：赛时没想到阻碍关系是一个森林，使用了“缩点 + 拓扑排序 + bitset”的暴力方法，赛后优化为建反图拓扑排序。总结是在解题时要仔细分析问题的性质，寻找更优的算法。
- **作者：_zy_**：暴力一开始没有过，提示在处理数据范围较大的问题时，要避免使用复杂度高的暴力算法，寻找更合适的优化方法。 

---
处理用时：62.36秒