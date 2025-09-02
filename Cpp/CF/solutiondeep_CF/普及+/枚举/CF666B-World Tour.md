# 题目信息

# World Tour

## 题目描述

A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are $ n $ cities and $ m $ one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png). Four cities in the order of visiting marked as overlines: $ [1,5,2,4] $ .

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

## 说明/提示

Let $ d(x,y) $ be the shortest distance between cities $ x $ and $ y $ . Then in the example $ d(2,1)=3,d(1,8)=7,d(8,7)=3 $ . The total distance equals $ 13 $ .

## 样例 #1

### 输入

```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
```

### 输出

```
2 1 8 7
```

# AI分析结果

### 题目翻译
# 世界巡回

## 题目描述
著名雕塑家西加索要去进行世界巡回啦！

嗯，实际上也并非真正的全球巡回。但也不是每个人都有机会欣赏雕塑家的作品，不是吗？否则就没有任何独特性了。所以西加索将完全在他的祖国——伯兰进行世界巡回。

西加索对自己的作品极为专注，他希望尽可能少地被打扰。因此，他只会访问四个城市。这些城市将各不相同，这样就没人会认为他有 “偏爱”。当然，为了省钱，他会选择这些城市之间的最短路径。但正如你可能已经猜到的，西加索是个奇怪的人。虽然他不喜欢组织展览，但他喜欢在国内四处旅行，欣赏风景。所以他希望自己旅行的总距离尽可能长。然而，这位雕塑家不擅长规划，所以他向你求助。

伯兰有 $n$ 个城市和 $m$ 条单向道路。你必须选择西加索将要访问的四个不同城市，并确定他访问这些城市的顺序。这样，当他按照你给出的顺序访问城市时，从你列表中的第一个城市开始，到最后一个城市结束，每次都选择两个城市之间的最短路线，他旅行的总距离将会是最大的。

请注意，中间路线可能会经过被指定为巡回的城市，也可能会两次经过同一个城市。例如，巡回可能是这样的：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png)。按访问顺序标记的四个城市用下划线标出：$ [1,5,2,4] $ 。

请注意，伯兰是一个高科技国家。所以利用纳米技术，所有道路都被改造得长度相同。出于同样的原因，在这个国家使用普通汽车出行不是很流行，而且可能会出现这样的情况，即有些城市对，从其中一个城市根本无法开车到达另一个城市。然而，西加索非常保守，没有汽车就无法出行。请选择城市，以便雕塑家仅使用汽车就能完成巡回。保证总是可以做到这一点。

## 说明/提示
设 $d(x,y)$ 为城市 $x$ 和 $y$ 之间的最短距离。那么在示例中，$d(2,1)=3$，$d(1,8)=7$，$d(8,7)=3$。总距离等于 $13$。

## 样例 #1
### 输入
```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
```
### 输出
```
2 1 8 7
```

### 题解综合分析与结论
1. **思路**：所有题解的核心思路都是先预处理出任意两点间的最短路，然后通过枚举部分点并结合预处理信息来确定四个城市的顺序，使得总路径最长。
2. **算法要点**：
    - **预处理最短路**：由于边权相同，多数题解使用BFS（少数使用SPFA或Dijkstra）对每个点进行遍历，以 $O(n^2)$ 的复杂度得到任意两点间的最短距离。
    - **枚举优化**：为避免 $O(n^4)$ 枚举四个点的高复杂度，题解通过只枚举中间两个点（如 $b$ 和 $c$），然后结合预处理的前几大最短路信息来确定另外两个点（如 $a$ 和 $d$），将时间复杂度优化到 $O(n^2)$。
3. **解决难点**：难点在于如何在保证四个点不同且路径可达的情况下，找到使总距离最大的组合。通过预处理每个点的前三大（或前几大）最短路对应的点，在枚举中间两点时进行合理判断和组合，解决了点重复的问题。

### 所选的题解
1. **作者：Juanzhang (赞：7) - 5星**
    - **关键亮点**：思路清晰，逐步分析优化过程，从最初的 $O(n^5)$ 暴力枚举到 $O(n^4)$ 的多源最短路预处理，再到最终 $O(n^2)$ 的优化，对每个优化步骤的原因和可能遇到的问题都有详细说明。
    - **核心代码实现思想**：通过三层循环枚举 $i,j,k$，再结合预处理的 `pre` 和 `nxt` 数组（分别存储连向某点的较远的点），找到满足条件的四个点使得总距离最大。
    ```cpp
    for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
            if (j == k) {
                continue;
            }
            for (pii p1 : pre[j]) {
                int i = p1.sec;
                if (i == j || i == k) {
                    continue;
                }
                for (pii p2 : nxt[k]) {
                    int l = p2.sec;
                    if (i == l || j == l || k == l) {
                        continue;
                    }
                    if (sum < dis[i][j] + dis[j][k] + dis[k][l]) {
                        sum = dis[i][j] + dis[j][k] + dis[k][l];
                        ans[1] = i, ans[2] = j, ans[3] = k, ans[4] = l;
                    }
                }
            }
        }
    }
    ```
2. **作者：sane1981 (赞：6) - 5星**
    - **关键亮点**：结合题目和相似题目进行分析，详细解释了只枚举前三大的点的原因，并通过图示辅助理解。代码结构清晰，注释详细。
    - **核心代码实现思想**：先通过 `SPFA` 预处理出所有点对间的最短路，然后通过两层循环枚举中间两点 $x2,x3$，再结合排序后的 `A` 和 `B` 数组（分别存储从某点出发和到达某点的前几大距离及对应点），找到满足条件的四个点使得总距离最大。
    ```cpp
    for(int x2=1;x2<=n;x2++){
        for(int x3=1;x3<=n;x3++){//枚举b,c 
            if(x2==x3||dis[x2][x3]==-1) continue;
            for(int k1=0;k1<3&&k1<B[x2].size();k1++){
                int x1=B[x2][k1].second;
                if(x1==x3||x1==x2) continue;
                int w1=B[x2][k1].first;
                for(int k2=0;k2<3&&k2<A[x3].size();k2++){
                    int x4=A[x3][k2].second;
                    if(x4==x1||x4==x2||x4==x3) continue;
                    int w4=A[x3][k2].first;
                    if(ans<dis[x2][x3]+w1+w4){
                        ans=dis[x2][x3]+w1+w4;
                        f1=x1;f2=x2;f3=x3;f4=x4;
                    }
                }
            } 
        }
    }
    ```
3. **作者：WaterSun (赞：0) - 4星**
    - **关键亮点**：思路阐述详细，对贪心策略及处理点冲突的方式解释清晰，代码简洁明了，变量命名规范。
    - **核心代码实现思想**：先通过 `bfs` 预处理出所有点对间的最短路，然后通过两层循环枚举中间两点 $b,c$，再结合 `dm` 数组（存储以某点为起点和终点的前几大距离及对应点），找到满足条件的四个点使得总距离最大。
    ```cpp
    for (re int b = 1;b <= n;b++){
        for (re int c = 1;c <= n;c++){
            if (c == b ||!~dist[b][c]) continue;
            int lb = dm[b][1].size();
            for (re int p = 0;p < 3 && p < lb;p++){
                int a = dm[b][1][p].snd;
                if (a == b || a == c) continue;
                int lc = dm[c][0].size();
                for (re int q = 0;q < 3 && q < lc;q++){
                    int d = dm[c][0][q].snd;
                    if (d == a || d == b || d == c) continue;
                    if (Max < dist[a][b] + dist[b][c] + dist[c][d]){
                        Max = dist[a][b] + dist[b][c] + dist[c][d];
                        A = a;
                        B = b;
                        C = c;
                        D = d;
                    }
                }
            }
        }
    }
    ```

### 最优关键思路或技巧
1. **优化枚举策略**：通过只枚举中间两个点，利用预处理的前几大最短路信息来确定另外两个点，有效降低时间复杂度。
2. **预处理前几大最短路**：为解决点重复导致路径选择冲突的问题，预处理每个点的前三大最短路对应的点，确保在组合四个点时能够找到总距离最大且满足条件的方案。

### 可拓展之处
同类型题通常围绕图的最短路问题，结合不同的限制条件和目标进行考察。类似算法套路包括先预处理图的相关信息（如最短路、连通性等），再通过合理的枚举和判断来解决问题。例如，可能会改变点的选取数量、路径的限制条件（如必经点、不能经过的点等）。

### 相似知识点洛谷题目
1. [P8817 [CSP - S 2022] 假期计划](https://www.luogu.com.cn/problem/P8817)：与本题类似，需要在图中选择点并规划路径，以满足一定的条件并最大化某个值。
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：基础的单源最短路问题，可作为理解和练习最短路算法的基础题目。
3. [P1339 热浪](https://www.luogu.com.cn/problem/P1339)：同样是最短路问题，通过不同的场景设置考察对最短路算法的应用。 

---
处理用时：44.68秒