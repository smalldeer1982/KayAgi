# 题目信息

# Game Master

## 题目描述

$n$ 个选手正在进行一场比赛。

这场比赛有两个场地。现已明确每个选手在两个场地上的力量值。

有 $n-1$ 场交锋。每次交锋，裁判员从剩余的选手中任选两个，并从两个场地中任选一个。两个选手中，在该场地力量较弱的，会被淘汰。经过 $n-1$ 场交锋后，最终会剩下一位选手，为胜者。

对于每一个选手，判断他是否有机会成为胜者。

本题多测，每个测试点有 $t$ 组数据。

## 样例 #1

### 输入

```
3
4
1 2 3 4
1 2 3 4
4
11 12 20 21
44 22 11 30
1
1000000000
1000000000```

### 输出

```
0001
1111
1```

# AI分析结果

### 题目分类
图论

### 综合分析与结论
这些题解主要围绕如何判断每个选手是否有机会成为胜者展开，多数题解采用建图的方式，利用图的连通性和强连通分量的性质来解决问题。不同题解在具体实现和优化上有所差异，主要思路包括建图后缩点找入度为 0 的强连通分量、建立坐标系维护有效区域、贪心策略等。

### 所选题解
- **作者：Fan_sheng (赞：5)  ★★★★**
    - **关键亮点**：思路清晰，详细阐述了隐式图问题的转化和解决过程，对建边优化的解释很到位，代码实现完整。
- **作者：Sword_K (赞：5)  ★★★★**
    - **关键亮点**：提供了一种独特的坐标系解法，通过图形直观展示点与点之间的关系，对有效区域的维护和分析很有创新性。
- **作者：npqenqpve (赞：5)  ★★★★**
    - **关键亮点**：思路简洁明了，通过排序和集合操作找到可能获胜的选手集合，代码实现简单高效。

### 重点代码及核心思想
#### Fan_sheng 的代码
```cpp
// 建边函数
inline void add(int u,int v){
    edge[++flag]=(star){v,head[u]};head[u]=flag;
}
// tarjan 缩点函数
void tarjan(int id){
    dfn[id]=low[id]=++timer,in[id]=1,st[++st[0]]=id;
    for(int i=head[id];i;i=edge[i].nxt){
        int v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);low[id]=min(low[id],low[v]);
        }
        else if(in[v])low[id]=min(low[id],dfn[v]);
    }
    if(dfn[id]==low[id]){
        cnt++;
        while(st[st[0]]!=id)color[st[st[0]]]=cnt,in[st[st[0]]]=0,st[0]--;
        color[id]=cnt,in[id]=0,st[0]--;
    }
}
```
**核心思想**：先对每个选手建点，若 A 能在任意场地击败 B 则从 A 到 B 连有向边，对图进行 tarjan 缩点，找到入度为 0 的强连通分量，该分量内的选手可能成为冠军。建边时通过排序优化，只连接相邻选手的边，降低复杂度。

#### Sword_K 的代码
```cpp
// 先对所有点按 a 从小到大排序
sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.a < b.a;
});
// 用一个 set 存之前处于非有效区域的点
set<Point> non_valid_points;
// 倒着考虑，第一个点肯定满足要求
for (int i = n - 1; i >= 0; --i) {
    // 判断当前点是否在有效区域内
    if (is_in_valid_area(points[i], valid_area)) {
        mark_valid(points[i]);
        update_valid_area(points[i], valid_area);
        // 维护 set
        for (auto it = non_valid_points.begin(); it != non_valid_points.end(); ) {
            if (it->b < points[i].b) {
                mark_valid(*it);
                it = non_valid_points.erase(it);
            } else {
                ++it;
            }
        }
    } else {
        non_valid_points.insert(points[i]);
    }
}
```
**核心思想**：将选手看成二维坐标上的点，根据点的位置关系判断胜负关系，通过维护有效区域来连边，只考虑和 a 最大的点联通的点，用 set 存储非有效区域的点，逐步更新有效区域和标记合法点。

#### npqenqpve 的代码
```cpp
pair<int,int>a[(int)(1e5+10)],b[(int)(1e5+10)];
set<int>s;
char ans[(int)(1e5+10)];
// 主函数部分
while(t--)
{
    int n;cin>>n;
    s.clear();
    for(int i=0;i<=n-1;i++) 
    {
        cin>>a[i].first;a[i].second=i;
    }
    for(int i=0;i<=n-1;i++)
    {
        cin>>b[i].first;b[i].second=i;
        ans[i]='0';
    }
    sort(a,a+n);sort(b,b+n);
    ans[n]=0;
    int i;
    for(i=n-1;i>=0;i--)
    {
        s.insert(a[i].second);
        s.insert(b[i].second);
        if(s.size()==n-i) break;
    }
    while(i<=n-1) ans[a[i].second]='1',i++;
    puts(ans);
}
```
**核心思想**：将两个能力值分别排序并记录所属编号，从后往前扫，找到一个位置 i，使得分别在两个图中前 i 强的人都是某 i 个人，这个集合内的人一定能获胜，其余人必败。

### 最优关键思路或技巧
- **建图优化**：利用选手之间击败关系的传递性，对 a 和 b 分别排序后只连接相邻选手的边，将建边复杂度从 $O(n^2)$ 优化到 $O(n)$。
- **坐标系解法**：将选手抽象为二维坐标上的点，通过维护有效区域来判断点的连通性，避免了复杂的建图和缩点操作。
- **贪心策略**：通过排序和集合操作，快速找到可能获胜的选手集合，思路简洁高效。

### 拓展思路
同类型题可能会增加场地数量、改变比赛规则等，类似算法套路可以是根据元素之间的关系建图，利用图的性质解决问题，或者通过排序、贪心等策略简化问题。

### 推荐洛谷题目
- P1113 杂务：考察图的拓扑排序，与本题建图和利用图的性质解决问题的思路类似。
- P2853 [USACO06DEC]Cow Picnic S：考察图的遍历和连通性，与本题判断选手能否遍历全图的思路有相似之处。
- P3916 图的遍历：同样是关于图的遍历问题，可加深对图论算法的理解。

### 个人心得摘录与总结
- **Troubadour**：赛时想到了做法但没调出来，赛后半小时才切掉，可能大家都 FST 在多组数据上。总结：在比赛中要注意多组数据的处理，调试能力也很重要。
- **enucai**：考场上因为对所有的人都进行取 max 导致错误，后面的人杀掉一个前面无法成为冠军的人是没用的。总结：在实现贪心策略时要仔细考虑策略的正确性，避免逻辑错误。

---
处理用时：73.02秒