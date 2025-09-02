# 题目信息

# Old Peykan

## 题目描述

There are $ n $ cities in the country where the Old Peykan lives. These cities are located on a straight line, we'll denote them from left to right as $ c_{1},c_{2},...,c_{n} $ . The Old Peykan wants to travel from city $ c_{1} $ to $ c_{n} $ using roads. There are $ (n-1) $ one way roads, the $ i $ -th road goes from city $ c_{i} $ to city $ c_{i+1} $ and is $ d_{i} $ kilometers long.

The Old Peykan travels 1 kilometer in 1 hour and consumes 1 liter of fuel during this time.

Each city $ c_{i} $ (except for the last city $ c_{n} $ ) has a supply of $ s_{i} $ liters of fuel which immediately transfers to the Old Peykan if it passes the city or stays in it. This supply refreshes instantly $ k $ hours after it transfers. The Old Peykan can stay in a city for a while and fill its fuel tank many times.

Initially (at time zero) the Old Peykan is at city $ c_{1} $ and $ s_{1} $ liters of fuel is transferred to it's empty tank from $ c_{1} $ 's supply. The Old Peykan's fuel tank capacity is unlimited. Old Peykan can not continue its travel if its tank is emptied strictly between two cities.

Find the minimum time the Old Peykan needs to reach city $ c_{n} $ .

## 说明/提示

In the second sample above, the Old Peykan stays in $ c_{1} $ for 3 hours.

## 样例 #1

### 输入

```
4 6
1 2 5 2
2 3 3 4
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2 3
5 6
5 5
```

### 输出

```
14
```

# AI分析结果

### 题目内容
# 老佩坎

## 题目描述
老佩坎所在的国家有 $n$ 个城市。这些城市位于一条直线上，我们从左到右将它们记为 $c_{1},c_{2},\cdots,c_{n}$ 。老佩坎想通过道路从城市 $c_{1}$ 前往 $c_{n}$ 。这里有 $(n - 1)$ 条单向道路，第 $i$ 条道路从城市 $c_{i}$ 通向城市 $c_{i + 1}$ ，长度为 $d_{i}$ 千米。

老佩坎每行驶1千米需要1小时，并且在此期间消耗1升燃料。

每个城市 $c_{i}$（除了最后一个城市 $c_{n}$ ）都有 $s_{i}$ 升燃料供应，当老佩坎经过该城市或停留在该城市时，这些燃料会立即转移到它的车上。这种供应会在转移后的 $k$ 小时后立即刷新。老佩坎可以在一个城市停留一段时间，并多次加满它的油箱。

最初（在时间为零的时候），老佩坎在城市 $c_{1}$ ，并且 $c_{1}$ 的供应中有 $s_{1}$ 升燃料被转移到它的空油箱中。老佩坎的油箱容量是无限的。如果老佩坎的油箱在两个城市之间严格为空，它就无法继续旅行。

求老佩坎到达城市 $c_{n}$ 所需的最短时间。

## 说明/提示
在上面的第二个样例中，老佩坎在 $c_{1}$ 停留了3小时。

## 样例 #1
### 输入
```
4 6
1 2 5 2
2 3 3 4
```
### 输出
```
10
```
## 样例 #2
### 输入
```
2 3
5 6
5 5
```
### 输出
```
14
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略。由于每个城市加油时间固定为 $k$ 小时，为使总时间最短，当油量不足时，应选择已经过城市中供油量最大的地方加油。
不同题解在实现细节上略有差异，如有的通过动态更新最大值变量来记录供油量最大的城市，有的通过前缀数组记录每个位置及之前的最大供油量。

### 所选的题解
- **作者：Stephen_Curry (5星)**
    - **关键亮点**：思路清晰，结合样例和手造极端数据详细分析贪心思想，代码简洁明了，利用数组 `ma` 记录前缀最大油量，便于后续处理。
    - **重点代码核心实现思想**：先初始化 `ma` 数组记录前缀最大油量，在遍历每个路段时，若当前油量 `now` 不足以通过该路段，就循环从之前油量最多处加油（每次加 `ma[i]` 并花费时间 `k`），直到油量足够通过该路段。
    ```cpp
    for (int i = 1; i <= m; i++) ma[i] = max(ma[i - 1], s[i]);
    for (int i = 1; i <= m; i++) {
        now += s[i];
        while (d[i] > now) ans += k, now += ma[i];
        now -= d[i]; ans += d[i];
    }
    ```
- **作者：Kissky (4星)**
    - **关键亮点**：分析简洁，代码紧凑，在循环中实时更新当前城市及之前的最大供油量 `ma`，并据此处理油量不足的情况。
    - **重点代码核心实现思想**：通过 `ma = max(s[i], ma)` 更新最大供油量，当油量不足时，循环从最大供油量处加油（每次加 `ma` 并花费时间 `k`）直至油量足够通过当前路段。
    ```cpp
    for(int i=1;i<=m;i++)
    {
        ma=max(s[i],ma);
        v+=s[i];
        if(v>=d[i]) v-=d[i],ans+=d[i];
        else {
            while(v<d[i]) ans+=k,v+=ma;
            v-=d[i],ans+=d[i];
        }
    }
    ```
- **作者：Dreamerly (4星)**
    - **关键亮点**：先阐述模拟思路，再点明贪心要点，代码通过前缀数组 `pre` 记录最大供油量，逻辑清晰。
    - **重点代码核心实现思想**：先预处理 `pre` 数组记录前缀最大油量，当油量不足时，循环从之前油量最多处（`pre[i]`）加油（每次加 `pre[i]` 并花费时间 `k`）直到油量足够通过当前路段。
    ```cpp
    for(int i=1;i<=m;i++) s[i]=read(),pre[i]=max(pre[i-1],s[i]);
    for(int i=1;i<=m;i++){
        now+=s[i];
        if(now>=d[i]){
            now-=d[i];
            ans+=d[i];
        }
        else{
            while(now<d[i]){
                ans+=k; 
                now+=pre[i];
            }
            now-=d[i]; 
            ans+=d[i];
        }
    }
    ```

### 最优关键思路或技巧
利用贪心策略，在油量不足时，选择已经过城市中供油量最大的地方加油，通过记录前缀最大供油量（如使用数组记录每个位置及之前的最大供油量）的方式优化实现过程，减少不必要的计算。

### 可拓展思路
同类型题通常围绕资源分配与时间优化，类似算法套路是在固定成本（如本题的加油时间）下，通过贪心选择最优资源（如本题的最大供油量城市）来优化目标（如最短时间）。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)

### 个人心得摘录与总结
部分作者提到一开始误解题意，以为是最短路问题，经过分析样例和手造数据才明确是模拟结合贪心。这表明在面对题目时，不能仅依据初步印象判断算法，需深入分析题目条件与样例，通过构造特殊数据辅助理解题意与寻找解题思路。 

---
处理用时：55.50秒