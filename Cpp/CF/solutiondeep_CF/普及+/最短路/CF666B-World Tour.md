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

### 题目内容翻译
# 世界巡回之旅

## 题目描述
著名雕塑家西加索要进行一次世界巡回之旅！

嗯，实际上这并非真正意义上的全球巡回。毕竟，并非每个人都应该有机会看到这位雕塑家的作品，不是吗？否则就毫无独特性可言了。所以，西加索将把他的世界巡回之旅完全安排在他的祖国——伯兰。

西加索对自己的工作极为投入，他希望尽可能少地受到干扰。因此，他只会访问四个城市。这些城市各不相同，这样就不会有人认为他有“偏爱”。当然，为了节省开支，他会选择这些城市之间的最短路径。但正如你可能已经猜到的，西加索是个怪人。尽管他不喜欢举办展览，但他喜欢在国内旅行，欣赏风景。所以他希望自己旅行的总距离尽可能长。然而，这位雕塑家不擅长规划，所以他向你寻求帮助。

伯兰有 $n$ 个城市和 $m$ 条单向道路。你需要选择四个不同的城市，西加索将按你确定的顺序访问这些城市。也就是说，从你列出的第一个城市开始，到最后一个城市结束，每次都选择两个城市之间的最短路线，使得他旅行的总距离最长。

请注意，中间路线可能会经过行程中指定的城市，也可能会两次经过同一个城市。例如，行程可能如下所示：![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png)。四个城市的访问顺序用上划线标记：$[1,5,2,4]$。

请注意，伯兰是一个高科技国家。因此，利用纳米技术，所有道路都经过改造，使得它们的长度相同。出于同样的原因，在这个国家使用普通汽车出行并不流行，而且可能会出现这样的情况：从一个城市到另一个城市根本无法开车到达。然而，西加索非常保守，他出行必须开车。请选择城市，以便雕塑家能够仅使用汽车完成这次旅行。保证总是可以做到这一点。

## 说明/提示
设 $d(x,y)$ 为城市 $x$ 到城市 $y$ 的最短距离。那么在示例中，$d(2,1)=3$，$d(1,8)=7$，$d(8,7)=3$。总距离为 $13$。

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

### 综合分析与结论
这些题解的核心目标是在有向图中找出四个不同的点 $a,b,c,d$，使得 $d(a,b)+d(b,c)+d(c,d)$ 最大。

#### 思路对比
- 多数题解采用先预处理全源最短路，再枚举中间两点 $b,c$，最后确定 $a,d$ 的思路。
- 部分题解提到直接暴力枚举四个点复杂度为 $O(n^4)$ 会超时，因此需要优化。

#### 算法要点
- **最短路预处理**：由于边权相同，多数题解使用 BFS 或 SPFA 算法进行全源最短路预处理，复杂度为 $O(nm)$。
- **枚举优化**：为避免枚举四个点的高复杂度，枚举中间两点 $b,c$，并对每个点预处理前三大的入边和出边，将复杂度降低到 $O(n^2)$。

#### 解决难点
- **点的重复问题**：在选择 $a,d$ 时，可能会出现与 $b,c$ 重复的情况。通过预处理前三大的点，可调配使得 $a,b,c,d$ 互不相同。

### 高评分题解
- **作者：Juanzhang (赞：7)，5星**
    - **关键亮点**：思路清晰，逐步分析复杂度优化过程，从 $O(n^5)$ 优化到 $O(n^2)$，并详细解释了为什么需要预处理前三大的点。
    - **核心代码**：
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
    - **核心实现思想**：枚举中间两点 $j,k$，对于每个 $j$ 遍历其前三大的入边对应的点 $i$，对于每个 $k$ 遍历其前三大的出边对应的点 $l$，更新最大路径和及对应的四个点。

- **作者：sane1981 (赞：6)，4星**
    - **关键亮点**：详细解释了为什么只枚举前三大的 $a,d$ 点，通过图示说明枚举到第二大可能出现的问题，思路清晰。
    - **核心代码**：
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
    - **核心实现思想**：枚举中间两点 $x2,x3$，对于 $x2$ 遍历其前三大的入边对应的点 $x1$，对于 $x3$ 遍历其前三大的出边对应的点 $x4$，更新最大路径和及对应的四个点。

- **作者：sprads (赞：1)，4星**
    - **关键亮点**：详细分析了直接找最大的 $a,d$ 可能出现的问题，并给出了预处理前三大点的具体实现和处理重复点的细节。
    - **核心代码**：
```cpp
for(int b = 1;b <= n;b++){
    for(int c = 1;c <= n;c++){
        if(b == c || h[b][c] == INF)continue;
        int x = 0,y = 0;
        if(s[b][x] == c)x++;
        if(t[c][y] == b)y++;
        if(s[b][x] == t[c][y]){
            int i = x + 1,j = y + 1;
            if(s[b][i] == c)i++;
            if(t[c][j] == b)j++;
            int a = s[b][x],d = t[c][j];
            if(res(a,b,c,d) > ans){
                A = a,B = b,C = c,D = d;
                ans = res(a,b,c,d);
            }
            a = s[b][i],d = t[c][y];
            if(res(a,b,c,d) > ans){
                A = a,B = b,C = c,D = d;
                ans = res(a,b,c,d);
            }
        }
        else{
            int a = s[b][x],d = t[c][y];
            if(res(a,b,c,d) > ans){
                A = a,B = b,C = c,D = d;
                ans = res(a,b,c,d);
            }
        }
    }
}
```
    - **核心实现思想**：枚举中间两点 $b,c$，根据预处理的前三大点 $s[b]$ 和 $t[c]$ 确定 $a,d$，处理可能出现的重复点情况，更新最大路径和及对应的四个点。

### 最优关键思路或技巧
- **复杂度优化**：通过枚举中间两点，将原本 $O(n^4)$ 的复杂度降低到 $O(n^2)$。
- **预处理前三大点**：避免选择点时的重复问题，确保能找到满足条件的四个不同点。

### 可拓展之处
同类型题如 P8817 [CSP - S 2022] 假期计划，思路类似，都是在图中选择若干点，使得某些路径和最大。类似算法套路为预处理全源最短路，然后枚举部分点，通过预处理其他信息来确定剩余点。

### 推荐题目
1. P1144 最短路计数
2. P3371 单源最短路径（弱化版）
3. P2850 [USACO06DEC]Wormholes G

### 个人心得摘录与总结
- **sprads**：考试时想到枚举 $b,c$ 并找最大的 $a,d$，但未考虑到重复问题导致未做出来。总结是在贪心选择时要考虑可能出现的冲突情况，可通过多预处理一些信息来解决。

---
处理用时：53.64秒