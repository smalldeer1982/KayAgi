# 题目信息

# Road Reform

## 题目描述

There are $ n $ cities and $ m $ bidirectional roads in Berland. The $ i $ -th road connects the cities $ x_i $ and $ y_i $ , and has the speed limit $ s_i $ . The road network allows everyone to get from any city to any other city.

The Berland Transport Ministry is planning a road reform.

First of all, maintaining all $ m $ roads is too costly, so $ m - (n - 1) $ roads will be demolished in such a way that the remaining $ (n - 1) $ roads still allow to get to any city from any other city. Formally, the remaining roads should represent an undirected tree.

Secondly, the speed limits on the remaining roads might be changed. The changes will be done sequentially, each change is either increasing the speed limit on some road by $ 1 $ , or decreasing it by $ 1 $ . Since changing the speed limit requires a lot of work, the Ministry wants to minimize the number of changes.

The goal of the Ministry is to have a road network of $ (n - 1) $ roads with the maximum speed limit over all roads equal to exactly $ k $ . They assigned you the task of calculating the minimum number of speed limit changes they have to perform so the road network meets their requirements.

For example, suppose the initial map of Berland looks like that, and $ k = 7 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/9e4deeb1d4ca30454fafffe4f5580702d72a87b0.png)Then one of the optimal courses of action is to demolish the roads $ 1 $ – $ 4 $ and $ 3 $ – $ 4 $ , and then decrease the speed limit on the road $ 2 $ – $ 3 $ by $ 1 $ , so the resulting road network looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/3406c65bb53e89861f39906767c44d2e2eb9dc4d.png)

## 说明/提示

The explanation for the example test:

The first test case is described in the problem statement.

In the second test case, the road network initially looks like that:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/43a8595a75dedb1e97ea060aa027d63f3c69ff5a.png)The Ministry can demolish the roads $ 1 $ – $ 2 $ , $ 3 $ – $ 2 $ and $ 3 $ – $ 4 $ , and then increase the speed limit on the road $ 1 $ – $ 4 $ three times.

In the third test case, the road network already meets all the requirements.

In the fourth test case, it is enough to demolish the road $ 1 $ – $ 2 $ so the resulting road network meets the requirements.

## 样例 #1

### 输入

```
4
4 5 7
4 1 3
1 2 5
2 3 8
2 4 1
3 4 4
4 6 5
1 2 1
1 3 1
1 4 2
2 4 1
4 3 1
3 2 1
3 2 10
1 2 8
1 3 10
5 5 15
1 2 17
3 1 15
2 3 10
1 4 14
2 5 8```

### 输出

```
1
3
0
0```

# AI分析结果

### 题目翻译
#### 道路改革

#### 题目描述
在 Berland 有 $n$ 个城市和 $m$ 条双向道路。第 $i$ 条道路连接城市 $x_i$ 和 $y_i$，并且有速度限制 $s_i$。道路网络允许任何人从任何一个城市到达其他任何城市。

Berland 交通部门正在计划一项道路改革。

首先，维护所有的 $m$ 条道路成本太高，因此 $m - (n - 1)$ 条道路将被拆除，使得剩下的 $(n - 1)$ 条道路仍然允许从任何城市到达其他任何城市。形式上，剩下的道路应该构成一个无向树。

其次，剩余道路的速度限制可能会改变。这些改变将按顺序进行，每次改变要么将某条道路的速度限制提高 $1$，要么降低 $1$。由于改变速度限制需要大量工作，交通部门希望最小化改变的次数。

交通部门的目标是使 $(n - 1)$ 条道路的道路网络中所有道路的最大速度限制恰好等于 $k$。他们交给你一项任务，计算他们为使道路网络满足要求而必须进行的最小速度限制改变次数。

例如，假设 Berland 的初始地图如下，且 $k = 7$：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/9e4deeb1d4ca30454fafffe4f5580702d72a87b0.png)

那么一个最优的行动方案是拆除道路 $1$ – $4$ 和 $3$ – $4$，然后将道路 $2$ – $3$ 的速度限制降低 $1$，这样得到的道路网络如下：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/3406c65bb53e89861f39906767c44d2e2eb9dc4d.png)

#### 说明/提示
示例测试的解释：
第一个测试用例在题目描述中已有说明。
在第二个测试用例中，道路网络最初如下：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1468J/43a8595a75dedb1e97ea060aa027d63f3c69ff5a.png)

交通部门可以拆除道路 $1$ – $2$、$3$ – $2$ 和 $3$ – $4$，然后将道路 $1$ – $4$ 的速度限制提高三次。
在第三个测试用例中，道路网络已经满足所有要求。
在第四个测试用例中，拆除道路 $1$ – $2$ 就足以使得到的道路网络满足要求。

#### 样例 #1
##### 输入
```
4
4 5 7
4 1 3
1 2 5
2 3 8
2 4 1
3 4 4
4 6 5
1 2 1
1 3 1
1 4 2
2 4 1
4 3 1
3 2 1
3 2 10
1 2 8
1 3 10
5 5 15
1 2 17
3 1 15
2 3 10
1 4 14
2 5 8
```
##### 输出
```
1
3
0
0
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是利用最小生成树（Kruskal 算法）来解决问题。先对所有边按边权从小到大排序，然后通过并查集来构建最小生成树。在构建过程中，记录最小生成树中最大边权。之后根据最大边权与 $k$ 的大小关系进行分类讨论：
1. 若最大边权大于 $k$，将所有大于 $k$ 的边的权值调整为 $k$，累加调整次数。
2. 若最大边权小于 $k$，遍历所有边，找到与 $k$ 差值最小的边，该差值即为答案。

### 所选题解
- **XXh0919（5星）**
    - **关键亮点**：思路清晰，代码结构简洁，注释详细，对 Kruskal 算法的实现和分类讨论的处理都很清晰。
    - **个人心得**：太久没写题解，咕值快掉没了，写篇题解涨涨咕。
- **shuangmu（5星）**
    - **关键亮点**：对思路的解释很详细，不仅说明了做法，还对结论进行了一定的证明，代码实现规范。
- **jianhe（4星）**
    - **关键亮点**：在代码中给出了详细的注释和注意事项，如多测清空等，适合初学者参考。
    - **个人心得**：因为多测不清空和变量名问题调了好久，提醒大家多测不清空，爆零两行泪，要注意自己的变量名。

### 重点代码
以 XXh0919 的题解为例，核心代码如下：
```cpp
int kruskal(){
    rep(i,1,n)fa[i]=i; // 初始化并查集
    sort(e+1,e+m+1,cmp); // 按边权从小到大排序
    rep(i,1,m){
        if(find(e[i].u)!=find(e[i].v)){ // 判断两点是否在同一集合
            join(e[i].u,e[i].v); // 合并集合
            cnt=max(cnt,e[i].w); // 更新最大边权
            if(cnt>k)ans+=cnt-k; // 若最大边权大于k，累加调整次数
        }
    }
    if(cnt<k){
        ans=0x3f3f3f3f; // 初始化答案为一个较大值
        rep(i,1,m){
            ans=min(ans,abs(k-e[i].w)); // 找到与k差值最小的边
        }
    }
    return ans;
}
```
核心实现思想：先对边按边权排序，然后利用并查集构建最小生成树，在构建过程中记录最大边权，根据最大边权与 $k$ 的关系进行分类讨论，计算最小调整次数。

### 扩展思路
同类型题或类似算法套路：
- 最小生成树的变形题，如求次小生成树、限制条件下的最小生成树等。
- 图的连通性问题，可结合并查集和图论算法解决。

### 推荐题目
1. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
2. [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
3. [P2330 [SCOI2005]繁忙的都市](https://www.luogu.com.cn/problem/P2330)

---
处理用时：51.01秒