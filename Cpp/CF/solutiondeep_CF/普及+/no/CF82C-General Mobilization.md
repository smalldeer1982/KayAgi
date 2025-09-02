# 题目信息

# General Mobilization

## 题目描述

The Berland Kingdom is a set of $ n $ cities connected with each other with $ n-1 $ railways. Each road connects exactly two different cities. The capital is located in city $ 1 $ . For each city there is a way to get from there to the capital by rail.

In the $ i $ -th city there is a soldier division number $ i $ , each division is characterized by a number of $ a_{i} $ . It represents the priority, the smaller the number, the higher the priority of this division. All values of $ a_{i} $ are different.

One day the Berland King Berl Great declared a general mobilization, and for that, each division should arrive in the capital. Every day from every city except the capital a train departs. So there are exactly $ n-1 $ departing trains each day. Each train moves toward the capital and finishes movement on the opposite endpoint of the railway on the next day. It has some finite capacity of $ c_{j} $ , expressed in the maximum number of divisions, which this train can transport in one go. Each train moves in the direction of reducing the distance to the capital. So each train passes exactly one railway moving from a city to the neighboring (where it stops) toward the capital.

In the first place among the divisions that are in the city, division with the smallest number of $ a_{i} $ get on the train, then with the next smallest and so on, until either the train is full or all the divisions are be loaded. So it is possible for a division to stay in a city for a several days.

The duration of train's progress from one city to another is always equal to $ 1 $ day. All divisions start moving at the same time and end up in the capital, from where they don't go anywhere else any more. Each division moves along a simple path from its city to the capital, regardless of how much time this journey will take.

Your goal is to find for each division, in how many days it will arrive to the capital of Berland. The countdown begins from day $ 0 $ .

## 样例 #1

### 输入

```
4
40 10 30 20
1 2 1
2 3 1
4 2 1
```

### 输出

```
0 1 3 2 ```

## 样例 #2

### 输入

```
5
5 4 3 2 1
1 2 1
2 3 1
2 4 1
4 5 1
```

### 输出

```
0 1 4 2 3 ```

# AI分析结果

### 题目内容
# 总动员

## 题目描述
伯兰王国由 $n$ 个城市组成，这些城市通过 $n - 1$ 条铁路相互连接。每条铁路恰好连接两个不同的城市。首都位于1号城市。对于每个城市，都有一条通过铁路到达首都的路径。

在第 $i$ 个城市有第 $i$ 个师的军队，每个师由数字 $a_i$ 表示其优先级。数字越小，该师的优先级越高。所有 $a_i$ 的值都不同。

有一天，伯兰国王贝尔大帝宣布总动员，为此，每个师都应抵达首都。每天，除首都外的每个城市都会开出一列火车。因此，每天恰好有 $n - 1$ 列火车出发。每列火车都朝着首都行驶，并在第二天到达铁路的另一端。每列火车都有一定的容量 $c_j$，表示该火车一次最多可运输的师的数量。每列火车都朝着距离首都更近的方向行驶。所以每列火车经过恰好一条铁路，从一个城市移动到相邻（并停靠）的朝着首都方向的城市。

在城市中的师中，首先是 $a_i$ 值最小的师登上火车，然后是次小的，依此类推，直到火车满载或所有师都已上车。因此，一个师可能会在一个城市停留几天。

火车从一个城市到另一个城市的行驶时间始终为1天。所有师同时出发，最终到达首都，之后不再前往其他任何地方。每个师都沿着从其所在城市到首都的简单路径移动，无论这次旅程需要多长时间。

你的目标是为每个师找出它将在多少天内到达伯兰的首都。从第0天开始计时。

## 样例 #1
### 输入
```
4
40 10 30 20
1 2 1
2 3 1
4 2 1
```
### 输出
```
0 1 3 2 
```

## 样例 #2
### 输入
```
5
5 4 3 2 1
1 2 1
2 3 1
2 4 1
4 5 1
```
### 输出
```
0 1 4 2 3 
```

### 算法分类
模拟

### 综合分析与结论
这几道题解核心思路均是利用师的优先级 $a_i$ 小的不会受大的影响这一特性，先对师按 $a_i$ 从小到大排序，再通过模拟每个师向首都移动的过程解题。不同点在于移动过程的模拟方式。有的题解采用暴力枚举等待时间，有的采用堆和排序优化，有的使用并查集优化。

### 所选的题解
- **作者：lmgoat (5星)**
  - **关键亮点**：思路清晰简洁，代码实现直接明了。先通过DFS记录每个城市到首都的最短路径信息，然后按 $a$ 值排序后暴力枚举每个师，利用二维数组维护每天每条边已运输的师数量，暴力计算等待时间。
  - **重点代码**：
```cpp
void dfs(int x,int fath,int dd) {
    fa[x]=fath,d[x]=dd;
    for(int i=hed[x];i;i=nxt[i])
        if(to[i]!=fath) dfs(to[i],x,c[i]);
}
for(int i=1;i<=n;++i) {
    int x=a[i].id,res=0;
    while(x!=1) {
        for(int i=res;;++i)
            if(b[x][i]<d[x]) {
                ++b[x][i],res+=(i-res)+1;
                break;
            }
        x=fa[x];
    }
    ans[a[i].id]=res;
} 
```
  - **核心实现思想**：`dfs` 函数记录城市前驱和边容量。外层循环枚举每个师，内层循环从当前时间往后找第一个没装满的火车，更新等待时间并移动到下一个城市。

- **作者：y_kx_b (4星)**
  - **关键亮点**：提出两种解法，一种利用堆和排序优化，另一种利用并查集优化，对时间复杂度分析详细。
  - **重点代码（Sol2）**：代码链接：https://codeforces.com/contest/82/submission/224244565
  - **核心实现思想**：按 $a$ 从小到大处理每个点，利用并查集优化寻找第一个不满时刻的过程，模拟每个点向首都移动。

- **作者：lxuyinc (4星)**
  - **关键亮点**：解题思路阐述详细，从多种想法出发逐步得出最终方案，代码实现简洁易懂。
  - **重点代码**：
```cpp
void dfs(int u,int f,int w){
    fa[u]=f;
    wi[u]=w;
    for(int i=h[u];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==f) continue;
        dfs(v,u,e[i].val);
    }
}
for(int i=1;i<=n;i++){
    int u=s[i].id,ret=0;
    while(u>1){
        for(int j=ret;;j++){
            if(dis[u][j]<wi[u]){
                dis[u][j]++;
                ret=j+1;
                break;
            }   
        }
        u=fa[u];
        sum[s[i].id]=ret;
    }
}
```
  - **核心实现思想**：`dfs` 记录路径信息，外层循环枚举每个师，内层循环暴力寻找可通过的时间，更新等待时间并移动到父节点。

### 最优关键思路或技巧
利用师优先级的特性先排序，简化问题。在模拟移动过程中，通过记录路径信息（如前驱节点、边容量），并使用数组或数据结构（二维数组、并查集等）维护边的使用情况来计算等待时间。

### 拓展
此类题目属于树上模拟问题，类似套路是利用树的结构特性，结合题目给定的限制条件进行模拟。比如可以拓展到不同运输规则、不同地图结构（如森林）等。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及枚举和组合数学知识，与本题枚举每个师的思路有相似之处。
- [P1314 聪明的质检员](https://www.luogu.com.cn/problem/P1314)：结合二分和前缀和知识，在一定程度上需要模拟计算过程，与本题模拟运输过程类似。
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)：经典的模拟问题，通过模拟淘汰过程求解，和本题模拟师的移动过程思路类似。

### 个人心得摘录与总结
无。 

---
处理用时：57.90秒