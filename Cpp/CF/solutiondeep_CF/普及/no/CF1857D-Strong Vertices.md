# 题目信息

# Strong Vertices

## 题目描述

Given two arrays $ a $ and $ b $ , both of length $ n $ . Elements of both arrays indexed from $ 1 $ to $ n $ . You are constructing a directed graph, where edge from $ u $ to $ v $ ( $ u\neq v $ ) exists if $ a_u-a_v \ge b_u-b_v $ .

A vertex $ V $ is called strong if there exists a path from $ V $ to all other vertices.

A path in a directed graph is a chain of several vertices, connected by edges, such that moving from the vertex $ u $ , along the directions of the edges, the vertex $ v $ can be reached.

Your task is to find all strong vertices.

For example, if $ a=[3,1,2,4] $ and $ b=[4,3,2,1] $ , the graph will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/d82544424ea2e3e9ac339f1c8fa7dad6ac60fbfc.png) The graph has only one strong vertex with number $ 4 $

## 说明/提示

The first sample is covered in the problem statement.

For the second sample, the graph looks like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/4f95c34528d6169c692c6bf6f2ed63814b90c73c.png) The graph has two strong vertices with numbers $ 3 $ and $ 5 $ . Note that there is a bidirectional edge between vertices $ 3 $ and $ 5 $ .In the third sample, the vertices are connected by a single directed edge from vertex $ 2 $ to vertex $ 1 $ , so the only strong vertex is $ 2 $ .

In the fourth sample, all vertices are connected to each other by bidirectional edges, so there is a path from every vertex to any other vertex.

## 样例 #1

### 输入

```
5
4
3 1 2 4
4 3 2 1
5
1 2 4 1 2
5 2 3 3 1
2
1 2
2 1
3
0 2 1
1 3 2
3
5 7 4
-2 -3 -6```

### 输出

```
1
4 
2
3 5 
1
2 
3
1 2 3 
2
2 3```

# AI分析结果

【题目内容】
# Strong Vertices

## 题目描述

给定两个数组 $a$ 和 $b$，长度均为 $n$。数组的元素从 $1$ 到 $n$ 索引。你需要构造一个有向图，其中如果 $a_u - a_v \ge b_u - b_v$（$u \neq v$），则存在从 $u$ 到 $v$ 的边。

一个顶点 $V$ 被称为强顶点，如果存在从 $V$ 到所有其他顶点的路径。

在有向图中，路径是由若干顶点通过边连接而成的链，沿着边的方向从顶点 $u$ 移动到顶点 $v$。

你的任务是找到所有强顶点。

例如，如果 $a=[3,1,2,4]$ 和 $b=[4,3,2,1]$，图将如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/d82544424ea2e3e9ac339f1c8fa7dad6ac60fbfc.png) 图中只有一个强顶点，编号为 $4$。

## 说明/提示

第一个样例已在题目描述中给出。

对于第二个样例，图如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1857D/4f95c34528d6169c692c6bf6f2ed63814b90c73c.png) 图中有两个强顶点，编号为 $3$ 和 $5$。注意，顶点 $3$ 和 $5$ 之间存在双向边。在第三个样例中，顶点通过一条从顶点 $2$ 到顶点 $1$ 的有向边连接，因此唯一的强顶点是 $2$。

在第四个样例中，所有顶点之间都通过双向边连接，因此从每个顶点到任何其他顶点都存在路径。

## 样例 #1

### 输入

```
5
4
3 1 2 4
4 3 2 1
5
1 2 4 1 2
5 2 3 3 1
2
1 2
2 1
3
0 2 1
1 3 2
3
5 7 4
-2 -3 -6```

### 输出

```
1
4 
2
3 5 
1
2 
3
1 2 3 
2
2 3```

【算法分类】
排序

【题解分析与结论】
本题的核心在于将问题转化为对 $a_i - b_i$ 的排序问题。通过移项，我们发现 $a_u - b_u \ge a_v - b_v$ 是判断边存在与否的关键条件。因此，所有 $a_i - b_i$ 最大的点即为强顶点，因为它们可以到达所有其他点。

【高星题解】
1. **作者：WsW_ (赞：2)**
   - **星级：4**
   - **关键亮点**：通过移项将问题转化为排序问题，简洁明了地指出只有 $a_u - b_u$ 最大的点会向其他所有点连边。
   - **代码实现**：
     ```cpp
     sort(a+1,a+1+n,cmp);
     int ans;
     for(ans=1;a[ans+1].x==a[1].x&&ans+1<=n;ans++);
     printf("%d\n",ans);
     sort(a+1,a+ans+1,cmp2);
     for(int i=1;i<=ans;i++){
         printf("%d ",a[i].id);
     }
     ```

2. **作者：Crazyouth (赞：1)**
   - **星级：4**
   - **关键亮点**：直接指出题目与图论无关，通过移项简化问题，代码清晰易读。
   - **代码实现**：
     ```cpp
     sort(s+1,s+n+1,cmp);
     s[0].sub=s[1].sub;
     int ans=0;
     for(int i=1;i<=n;i++){
         if(s[i].sub!=s[i-1].sub) break;
         ans++;
     }
     cout<<ans<<endl;
     for(int i=1;i<=ans;i++) cout<<s[i].pos<<' ';
     ```

3. **作者：Special_Tony (赞：1)**
   - **星级：4**
   - **关键亮点**：通过重载运算符实现排序，代码简洁，思路清晰。
   - **代码实现**：
     ```cpp
     sort(a, a + n);
     for(int i = 0; i < n; ++ i)
         if(a[i].v == a[0].v)
             ++ sum;
         else
             break ;
     cout << sum << '\n';
     for(int i = 0; i < n; ++ i)
         if(a[i].v == a[0].v)
             cout << a[i].id << ' ';
     ```

【最优关键思路】
通过移项将问题转化为对 $a_i - b_i$ 的排序问题，找出最大值及其对应的顶点，即为强顶点。

【拓展思路】
类似的问题可以通过移项或数学变换将复杂条件转化为简单的排序或比较问题，从而简化求解过程。

【推荐题目】
1. P1090 [NOIP2004 提高组] 合并果子
2. P1177 [模板]快速排序
3. P1223 排队接水

---
处理用时：31.13秒