# 题目信息

# Gourmet choice

## 题目描述

Mr. Apple, a gourmet, works as editor-in-chief of a gastronomic periodical. He travels around the world, tasting new delights of famous chefs from the most fashionable restaurants. Mr. Apple has his own signature method of review — in each restaurant Mr. Apple orders two sets of dishes on two different days. All the dishes are different, because Mr. Apple doesn't like to eat the same food. For each pair of dishes from different days he remembers exactly which was better, or that they were of the same quality. After this the gourmet evaluates each dish with a positive integer.

Once, during a revision of a restaurant of Celtic medieval cuisine named «Poisson», that serves chestnut soup with fir, warm soda bread, spicy lemon pie and other folk food, Mr. Apple was very pleasantly surprised the gourmet with its variety of menu, and hence ordered too much. Now he's confused about evaluating dishes.

The gourmet tasted a set of $ n $ dishes on the first day and a set of $ m $ dishes on the second day. He made a table $ a $ of size $ n \times m $ , in which he described his impressions. If, according to the expert, dish $ i $ from the first set was better than dish $ j $ from the second set, then $ a_{ij} $ is equal to ">", in the opposite case $ a_{ij} $ is equal to "<". Dishes also may be equally good, in this case $ a_{ij} $ is "=".

Now Mr. Apple wants you to help him to evaluate every dish. Since Mr. Apple is very strict, he will evaluate the dishes so that the maximal number used is as small as possible. But Mr. Apple also is very fair, so he never evaluates the dishes so that it goes against his feelings. In other words, if $ a_{ij} $ is "<", then the number assigned to dish $ i $ from the first set should be less than the number of dish $ j $ from the second set, if $ a_{ij} $ is ">", then it should be greater, and finally if $ a_{ij} $ is "=", then the numbers should be the same.

Help Mr. Apple to evaluate each dish from both sets so that it is consistent with his feelings, or determine that this is impossible.

## 说明/提示

In the first sample, all dishes of the first day are better than dishes of the second day. So, the highest score will be $ 2 $ , for all dishes of the first day.

In the third sample, the table is contradictory — there is no possible evaluation of the dishes that satisfies it.

## 样例 #1

### 输入

```
3 4
>>>>
>>>>
>>>>```

### 输出

```
Yes
2 2 2 
1 1 1 1 
```

## 样例 #2

### 输入

```
3 3
>>>
<<<
>>>```

### 输出

```
Yes
3 1 3 
2 2 2 
```

## 样例 #3

### 输入

```
3 2
==
=<
==```

### 输出

```
No
```

# AI分析结果

### 题目翻译
# 美食家的选择

## 题目描述
苹果先生是一位美食家，同时担任一家美食期刊的主编。他环游世界，在最时尚的餐厅品尝著名厨师的新佳肴。苹果先生有自己独特的评价方法——在每家餐厅，苹果先生会在不同的两天各点一套菜肴。所有菜肴都各不相同，因为苹果先生不喜欢吃同样的食物。对于来自不同日子的每一对菜肴，他都能清楚地记得哪一道更好，或者它们的品质相同。之后，这位美食家会用一个正整数来评价每一道菜肴。

有一次，在对一家名为“Poisson”的凯尔特中世纪美食餐厅进行评价时，这家餐厅供应栗子冷杉汤、热苏打面包、辣味柠檬派和其他民间美食，苹果先生对其丰富的菜单感到非常惊喜，于是点了太多菜。现在他在评价这些菜肴时感到困惑。

美食家第一天品尝了 $n$ 道菜肴，第二天品尝了 $m$ 道菜肴。他制作了一个大小为 $n \times m$ 的表格 $a$，在表格中描述了他的感受。如果根据这位专家的评价，第一天的第 $i$ 道菜比第二天的第 $j$ 道菜更好，那么 $a_{ij}$ 等于 “>”；反之，$a_{ij}$ 等于 “<”。菜肴也可能同样美味，在这种情况下，$a_{ij}$ 为 “=”。

现在苹果先生希望你能帮助他评价每一道菜肴。由于苹果先生非常严格，他会对菜肴进行评价，使得所使用的最大数字尽可能小。但苹果先生也非常公平，所以他的评价永远不会违背自己的感受。换句话说，如果 $a_{ij}$ 是 “<”，那么分配给第一天第 $i$ 道菜的数字应该小于第二天第 $j$ 道菜的数字；如果 $a_{ij}$ 是 “>”，那么应该更大；最后，如果 $a_{ij}$ 是 “=”，那么数字应该相同。

请帮助苹果先生评价来自两组的每一道菜肴，使其符合他的感受，或者确定这是不可能的。

## 说明/提示
在第一个样例中，第一天的所有菜肴都比第二天的菜肴更好。因此，最高分数将是 $2$，第一天的所有菜肴都是这个分数。

在第三个样例中，表格存在矛盾——不存在满足该表格的菜肴评价方式。

## 样例 #1
### 输入
```
3 4
>>>>
>>>>
>>>>
```
### 输出
```
Yes
2 2 2 
1 1 1 1 
```

## 样例 #2
### 输入
```
3 3
>>>
<<<
>>>
```
### 输出
```
Yes
3 1 3 
2 2 2 
```

## 样例 #3
### 输入
```
3 2
==
=<
==
```
### 输出
```
No
```

### 算法分类
图论

### 综合分析与结论
这些题解主要围绕如何根据给定的菜肴大小关系表格来评价菜肴，判断是否能满足条件并使最大数字最小。主要思路分为两类：一类是使用并查集和拓扑排序，另一类是使用差分约束。

#### 思路对比
- **并查集 + 拓扑排序**：先利用并查集将相等的菜肴合并为一个连通块，再根据大于、小于关系连边，最后通过拓扑排序进行赋值和判断是否有环。
- **差分约束**：将大小关系转化为差分约束的不等式，建图后使用 SPFA 算法求解最长路，判断是否有正环。

#### 算法要点对比
- **并查集 + 拓扑排序**：并查集用于合并相等元素，拓扑排序用于确定元素的顺序和赋值。
- **差分约束**：将大小关系转化为不等式，通过建图和 SPFA 算法求解。

#### 解决难点对比
- **并查集 + 拓扑排序**：难点在于正确处理相等元素的合并和连边，以及判断图中是否有环。
- **差分约束**：难点在于将大小关系准确地转化为差分约束的不等式，以及处理 SPFA 算法中的正环问题。

### 所选题解
- **作者：lenlen (赞：9)，4星**
    - **关键亮点**：思路清晰，代码注释详细，对并查集和拓扑排序的实现过程解释得很清楚。
- **作者：RiverFun (赞：5)，4星**
    - **关键亮点**：思路简单明了，代码结构清晰，对并查集和拓扑排序的实现较为规范。
- **作者：LJC00118 (赞：4)，4星**
    - **关键亮点**：使用 tarjan 缩点实现相等元素的合并，思路独特，对拓扑排序和 DP 的结合运用较好。

### 重点代码
#### 并查集 + 拓扑排序（作者：lenlen）
```cpp
// 并查集部分
int getfa(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=getfa(fa[fa[fa[fa[x]]]]);
}
void merge(int u,int v)
{
    int fu=getfa(u),fv=getfa(v);
    fa[fu]=fv;
}
// 拓扑排序部分
queue<int> q;
while(!q.empty())//拓扑排序
{
    int tmp=q.front();q.pop();++num;
    for(int i=h[tmp];i;i=e[i].nxt)
    {
        dis[e[i].v]=mx(dis[e[i].v],dis[tmp]+1);
        du[e[i].v]--;
        if(!du[e[i].v]) q.push(e[i].v);
    }
}
```
**核心实现思想**：先通过并查集将相等的元素合并，再根据大小关系连边，最后进行拓扑排序，在拓扑排序过程中更新元素的赋值。

#### 差分约束（作者：CuSO4_and_5H2O）
```cpp
// 建图部分
void add(int x,int y,int z)
{
    vec[x].push_back(node{z,y});
}
// SPFA 部分
int spfa()
{
    for(int i=1;i<=n+m;i++) dis[i]=1,q.push(i),vis[i]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();
        vis[x]=0;
        for(int i=0;i<vec[x].size();i++)
        {
            int nxt=vec[x][i].to,qz=vec[x][i].qz;
            if(dis[nxt]<dis[x]+qz)
            {
                dis[nxt]=dis[x]+qz;
                if(!vis[nxt]) q.push(nxt),vis[nxt]=1,jis[nxt]++;
                if(jis[nxt]>n) return 0; 
            }
        }
    }
    return 1;
}
```
**核心实现思想**：将大小关系转化为差分约束的不等式，建图后使用 SPFA 算法求解最长路，通过判断是否有正环来确定是否有解。

### 最优关键思路或技巧
- **并查集 + 拓扑排序**：利用并查集合并相等元素，将问题转化为有向无环图的拓扑排序问题，通过拓扑排序确定元素的顺序和赋值，保证最大数字最小。
- **差分约束**：将大小关系准确地转化为差分约束的不等式，利用 SPFA 算法求解最长路，判断是否有正环来确定是否有解。

### 拓展思路
同类型题或类似算法套路：
- 涉及元素之间大小关系的题目，如比较字符串大小、比较数值大小等，可以考虑使用并查集和拓扑排序或差分约束的方法。
- 图论中的环检测问题，可以使用拓扑排序或 SPFA 算法来判断图中是否有环。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：拓扑排序的经典应用。
- [P3385 负环](https://www.luogu.com.cn/problem/P3385)：差分约束中判断负环的题目。
- [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)：涉及并查集和图论的综合题目。

### 个人心得摘录与总结
- **作者：CuSO4_and_5H2O**：提到第一次用 SPFA 超时，第二次因为存图方式不同（从链式前向星改为 vector）而通过，总结出稠密图用 vector 比链式前向星快的经验。
- **作者：东灯**：分享了卡数据范围的经历，提醒要注意预估极限数据。 

---
处理用时：65.35秒