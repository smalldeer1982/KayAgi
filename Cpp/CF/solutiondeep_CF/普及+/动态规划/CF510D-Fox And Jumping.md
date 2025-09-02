# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果

### 题目内容重写

**题目描述**

Fox Ciel 正在玩一个游戏。在这个游戏中，有一条无限长的纸带，纸带上的单元格由整数索引（正数、负数和零）。开始时，她站在单元格 0 处。

还有 $n$ 张卡片，每张卡片有两个属性：长度 $l_{i}$ 和成本 $c_{i}$。如果她支付 $c_{i}$ 美元，那么她可以使用第 $i$ 张卡片。使用第 $i$ 张卡片后，她可以跳跃长度为 $l_{i}$，即从单元格 $x$ 跳到单元格 $(x-l_{i})$ 或 $(x+l_{i})$。

她希望能够跳到纸带上的任意单元格（可能需要访问一些中间单元格）。为了实现这个目标，她希望购买一些卡片，花费尽可能少的钱。

如果可能，计算最小成本。

**说明/提示**

在第一个样例中，购买一张卡片是不够的：例如，如果你购买了一张长度为 100 的卡片，你无法跳到任何索引不是 100 的倍数的单元格。最好的方法是购买第一张和第二张卡片，这样你就可以跳到任意单元格。

在第二个样例中，即使你购买了所有卡片，你也不能跳到任何索引不是 10 的倍数的单元格，因此你应该输出 -1。

**样例 #1**

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

**样例 #2**

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

**样例 #3**

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

**样例 #4**

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

### 题解分析与结论

本题的核心问题是通过选择一些卡片，使得这些卡片的跳跃长度的最大公约数为 1，并且花费最小。这个问题可以转化为一个动态规划问题，或者通过图论中的最短路算法来解决。

#### 关键思路与技巧

1. **裴蜀定理**：如果选择的卡片的跳跃长度的最大公约数为 1，那么可以通过这些卡片的组合跳跃到任意单元格。
2. **动态规划**：使用 `map` 来存储不同最大公约数对应的最小花费，通过状态转移来更新最小花费。
3. **最短路算法**：将问题转化为图论中的最短路问题，使用 Dijkstra 算法来求解最小花费。

#### 评分较高的题解

1. **Kohakuwu (赞：20)**  
   - **星级：4.5**  
   - **关键亮点**：使用 `map` 来优化动态规划，避免了直接使用数组的高空间复杂度，思路清晰，代码简洁。  
   - **核心代码**：
     ```cpp
     map<int,int> mp;
     for(int i=1; i<=n; i++) {
         for(pair<int,int> x:mp) {
             int num=__gcd(a[i],x.first),val=x.second+b[i];
             if(mp[num]==0) mp[num]=val; else mp[num]=min(mp[num],val);
         }
         if(mp[a[i]]==0) mp[a[i]]=b[i];
         else mp[a[i]]=min(mp[a[i]],b[i]);
     }
     ```

2. **fanfansann (赞：8)**  
   - **星级：4.0**  
   - **关键亮点**：将问题转化为图论中的最短路问题，使用 Dijkstra 算法求解，思路新颖，代码实现较为复杂但逻辑清晰。  
   - **核心代码**：
     ```cpp
     void dijkstra() {
         priority_queue<PII, vector<PII>, greater<PII> > q;
         q.push({0, 0});
         dist[0] = 0;
         while(q.size()) {
             int x = q.top().second;
             q.pop();
             if(x == 1) break;
             if(vis.find(x) != vis.end()) continue;
             vis[x] = true;
             for(int i = 1; i <= n; ++ i) {
                 int y = __gcd(x, l[i]), z = c[i];
                 if(dist.find(y) == dist.end()) dist[y] = INF;
                 if(dist[y] > dist[x] + z) {
                     dist[y] = dist[x] + z;
                     q.push({dist[y], y});
                 }
             }
         }
     }
     ```

3. **xiezheyuan (赞：4)**  
   - **星级：4.0**  
   - **关键亮点**：同样使用 Dijkstra 算法，代码简洁，逻辑清晰，适合理解图论算法的读者。  
   - **核心代码**：
     ```cpp
     void dijkstra(){
         pq.push({0,0});
         dis[0]=0;
         while(!pq.empty()){
             int x = pq.top().second;
             pq.pop();
             if(x==1) break;
             if(vis.find(x) != vis.end()) continue;
             vis.insert(x);
             for(int j=1;j<=n;j++){
                 int y = gcd(x,l[j]);
                 if(dis.find(y) == dis.end()) dis[y] = INT_MAX;
                 if(dis[y]>dis[x]+c[j]){
                     dis[y]=dis[x]+c[j];
                     pq.push(make_pair(dis[y],y));
                 }
             }
         }
     }
     ```

### 推荐题目

1. **洛谷 P1020 导弹拦截** - 考察动态规划与贪心算法。
2. **洛谷 P1064 金明的预算方案** - 考察背包问题的变种。
3. **洛谷 P1541 乌龟棋** - 考察动态规划与状态转移。

### 个人心得

- **调试经历**：在使用 `map` 进行动态规划时，需要注意初始化问题，避免未定义行为。
- **踩坑教训**：在实现 Dijkstra 算法时，优先队列的使用需要注意比较函数的定义，避免错误。
- **顿悟感想**：将问题转化为图论中的最短路问题，可以大大简化问题的复杂度，提升解题效率。

---
处理用时：63.35秒