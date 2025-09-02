# 题目信息

# Train Splitting

## 题目描述

There are $ n $ big cities in Italy, and there are $ m $ train routes between pairs of cities. Each route connects two different cities bidirectionally. Moreover, using the trains one can reach every city starting from any other city.

Right now, all the routes are operated by the government-owned Italian Carriage Passenger Company, but the government wants to privatize the routes. The government does not want to give too much power to a single company, but it also does not want to make people buy a lot of different subscriptions. Also, it would like to give a fair chance to all companies. In order to formalize all these wishes, the following model was proposed.

There will be $ k \ge 2 $ private companies indexed by $ 1, \, 2, \, \dots, \, k $ . Each train route will be operated by exactly one of the $ k $ companies. Then:

- For any company, there should exist two cities such that it is impossible to reach one from the other using only routes operated by that company.
- On the other hand, for any two companies, it should be possible to reach every city from any other city using only routes operated by these two companies.

Find a plan satisfying all these criteria. It can be shown that a viable plan always exists. Please note that you can choose the number $ k $ and you do not have to minimize or maximize it.

## 说明/提示

In the first test case, the output is illustrated in the following picture, where different colors correspond to different companies (blue for $ 1 $ , red for $ 2 $ , green for $ 3 $ , and yellow for $ 4 $ ):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/1eaddc7b0f6d2a4f1f27940fa94f2aacb1f5a325.png)If we consider, for example, only companies $ 2 $ and $ 3 $ , we can see that from any city it is possible to reach every other city (picture on the left below). However, if we restrict to company $ 2 $ alone, it becomes impossible to reach city $ 5 $ from city $ 1 $ (picture on the right).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/31ecc8efdc21984e9ee7dfce5c89335fe0b0fc8e.png)In the second test case, the output is illustrated in the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776F/168f9819a179018b8d7faca3d4c3b94ba0dba5d9.png)

## 样例 #1

### 输入

```
2
5 9
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
3 3
1 2
3 1
2 3```

### 输出

```
4
1 2 3 1 4 2 2 4 3
3
2 3 1```

# AI分析结果

### 题目内容重写
【题目描述】
意大利有 $n$ 个大城市，城市之间有 $m$ 条双向火车线路连接。每条线路连接两个不同的城市，并且通过这些线路可以从任何一个城市到达其他任何城市。

目前，所有线路都由政府所有的意大利客运公司运营，但政府希望将这些线路私有化。政府不希望将太多权力交给单一公司，也不希望人们购买太多不同的订阅服务。同时，政府希望给所有公司公平的机会。为了形式化这些愿望，提出了以下模型。

将有 $k \ge 2$ 家私营公司，编号为 $1, 2, \dots, k$。每条火车线路将由其中一家公司运营。要求：

- 对于任何一家公司，存在两个城市，使得仅通过该公司运营的线路无法从一个城市到达另一个城市。
- 对于任何两家公司，仅通过这两家公司运营的线路可以从任何一个城市到达其他任何城市。

请找到一个满足所有条件的方案。可以证明，这样的方案总是存在。请注意，你可以选择 $k$ 的值，且不需要最小化或最大化它。

### 算法分类
构造、图论

### 题解分析与结论
题目要求对图的边进行染色，使得每种颜色的子图不连通，但任意两种颜色的子图连通。题解的核心思路是通过选择特定节点进行染色，确保满足条件。

### 精选题解
#### 题解1：rui_er (5星)
**关键亮点**：
- 通过选择度数最小的节点进行染色，确保子图不连通。
- 处理完全图时，通过增加第三种颜色来满足条件。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
if(*min_element(deg+1, deg+1+n) < n - 1) {
    int u = min_element(deg+1, deg+1+n) - deg;
    puts("2");
    rep(i, 0, deg[u]-1) ans[e[u][i].second] = 1;
    rep(i, 1, m) if(!ans[i]) ans[i] = 2;
}
else {
    puts("3");
    ans[e[1][0].second] = 1;
    rep(i, 1, deg[1]-1) ans[e[1][i].second] = 2;
    rep(i, 1, m) if(!ans[i]) ans[i] = 3;
}
```

#### 题解2：DE_aemmprty (4星)
**关键亮点**：
- 详细解释了选择度数最小节点的原因。
- 处理完全图时，通过修改一条边的颜色来满足条件。
- 代码实现较为详细，适合初学者理解。

**核心代码**：
```cpp
f (i, 1, m)
    if (u[i] != col && v[i] != col)
        c[i] = 1;
f (i, 1, m)
    if (u[i] == col || v[i] == col)
        c[i] = 2; 
f (i, 1, m)
    if (n * (n - 1) / 2 == m && c[i] == 2) {
        c[i] = 3;
        break;
    }
```

#### 题解3：KυρωVixen (4星)
**关键亮点**：
- 通过贪心策略选择第一个度数小于 $n-1$ 的节点进行染色。
- 处理完全图时，通过修改特定边的颜色来满足条件。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
rep(i,1,n){
    if(d[i]<n-1){
        rep(j,0,m-1){
            if(e[j].fi==i||e[j].sc==i) a[j]=1;
            else a[j]=2;
            cout<<a[j]<<" ";
        }
        cout<<endl;
        break;
    }
}
```

### 最优关键思路
选择度数最小的节点，将其连接的边染成一种颜色，其他边染成另一种颜色。若图为完全图，则增加第三种颜色，修改一条边的颜色。

### 拓展思路
类似的问题可以通过选择特定节点或边进行染色或分割，确保子图满足特定条件。这类问题在图论中常见，通常需要构造性思维。

### 推荐题目
1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3388 【模板】割点](https://www.luogu.com.cn/problem/P3388)

### 个人心得摘录
- **rui_er**：在处理完全图时，通过增加第三种颜色来满足条件，这一点在调试时尤为重要。
- **DE_aemmprty**：选择度数最小的节点进行染色，确保子图不连通，这一思路在构造性问题中非常实用。

---
处理用时：42.14秒