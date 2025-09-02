# 题目信息

# [USACO10NOV] Candy S

## 题目描述

Farmer John knows that Bessie loves to eat candy. FJ has N (1 <= N <= 40,000) candies that he wants to give Bessie over some number of days. Each day, Farmer John gives Bessie a choice of how many candies she chooses to eat that day by choosing the number from a master list FJ supplies that has Nopt (1 <= Nopt <= 50) different options, C\_i (1 <= C\_i <= N). She must take exactly C\_i candies, no more, no less.

Farmer John has also disclosed F (1 <= F <= 50) of his favorite numbers, FN\_i (1 <= FN\_i <= N). Whenever the number of candies remaining at the end of the day precisely matches one of these favorite numbers, Bessie has the option to have him add exactly M (1 <= M <= 100) more candies to the candy supply. Bessie might get another option to add M candies several times if adding candies creates another favorite number. In the best circumstances, Bessie can obtain an infinite amount of candy!

When Bessie cannot choose some amount of candy to take (because there is not enough), and the number of candies remaining is not any of FJ's favorite numbers, she cannot have any more candy.

Unfortunately, Bessie cannot think ahead as far as she'd like to, so she needs your help in order to eat as many candies as possible.

By way of example, consider this scenario:

\* Farmer John's basket initially contains 10 candies

\* Bessie can chose to eat either 3 or 5 candies each day

\* Farmer John will add 1 candy any time the remaining number of candies is 2 or 4

Bessie could use this set of choices to maximize the amount of candy she can eat:

```cpp

                  Initial      # Candies   Remaining     Bonus     Final
        Day      # Candies       Eaten      Candies     Candies   Candies

         1          10             3          7            0        7
         2           7             3          4            1        5
         3           5             3          2            1        3
         4           3             3          0            0        0

```

Total candies eaten = 3 + 3 + 3 + 3 = 12. 

农民约翰知道Bessie喜欢吃糖果。约翰有N（1≤N≤40000）的糖果，他想给Bessie几天。每一天，贝茜从一个列表（有nopt（1 <= nopt <= 50）种不同的选择），选择那一天吃掉刚好C\_i（1 <= c\_i <= N）个糖果。


农民约翰也透露F（1≤f≤50）他最喜欢的数字，FN\_i（1 <= FN\_i <= N）。当当天最后剩下的糖果数量精确匹配其中一个喜欢的号码，Bessie可以让他添加恰好M（1 <= M = 100）个糖果。如果加后得到的个数，还是FJ喜欢的数字，就可以继续添加糖果M个（加几次由贝西决定）。在最好的情况下，Bessie可以吃掉无限量的糖果！


当Bessie不能选择一定量的糖（因为没有足够的），或者糖果的剩余数量不是任何约翰最喜欢的号码，她不能有任何更多的糖果。


不幸的是，Bessie想不出她想做的事，所以她需要你的帮助才能吃尽可能多的糖果。


## 说明/提示

感谢@ 王彦梓 提供翻译，kkksc03进行了修正。


## 样例 #1

### 输入

```
10 2 2 1 
3 
5 
4 
2 
```

### 输出

```
12 
```

# AI分析结果



### 算法分类
图论

### 题解分析与结论
各题解主要采用动态规划（DP）或图论建模（最长路径+环检测）思路。核心难点在于处理加糖导致的无限循环和状态转移。最优解法是将问题转化为最长路径问题，利用DFS判环确保无循环后求最长路。

### 高分题解推荐

#### 1. 作者：_Wind_Leaves_ShaDow_ （4星）
**关键亮点**：  
- 将糖果剩余数视为图节点，吃糖/加糖作为边权，转化为求最长路径问题。  
- 使用DFS判环，简洁高效。  
- 代码结构清晰，逻辑严谨。  

**核心代码**：  
```cpp
bool find(int p){
    if(Vis[p])return 0;
    if(vis[p])return 1;
    vis[p]=1;
    for(auto i:v[p])if(find(i.fi))return 1;
    vis[p]=0; Vis[p]=1;
    return 0;
}
int dfs(int p){
    if(dp[p]||!p)return dp[p];
    for(auto i:v[p])dp[p]=max(dp[p],dfs(i.fi)+i.se);
    return dp[p];
}
```
**实现思想**：  
- 建图时，每个剩余糖果数节点向可能的下一状态连边（吃糖边权为c_j，加糖边权为0）。  
- 通过DFS判环，存在环则输出-1，否则记忆化搜索求最长路径。

#### 2. 作者：L______ （4星）
**关键亮点**：  
- 逆向动态规划，状态转移高效。  
- 通过调整枚举顺序处理加糖状态跳跃。  
- 利用计数器`cnt[i]`判断循环，巧妙避免无限递归。  

**核心代码**：  
```cpp
for(int i=n;i;i--){
    if(dp[i]==-1) continue;
    if(book[i]){ // 当前是幸运数字
        cnt[i]++;
        if(cnt[i]>F+1) return printf("-1"),0;
        if(dp[i]>dp[i+m]) dp[i+m]=dp[i], i+=m+1; // 跳跃处理
        continue;
    }
    for(int j=1;j<=nopt;j++)
        if(i-c[j]>=0) dp[i-c[j]]=max(dp[i-c[j]],dp[i]+c[j]);
}
```
**实现思想**：  
- 初始化`dp[n]=0`，倒序枚举剩余糖果数。  
- 遇到幸运数字时，尝试转移到`i+m`并调整枚举位置，实现跳跃更新。

### 最优技巧总结
1. **图论建模**：将剩余糖果数抽象为节点，吃糖和加糖操作转化为带权边，问题转化为最长路径问题。  
2. **环检测**：DFS遍历时维护访问标记，发现重复访问节点则存在无限循环。  
3. **动态规划跳跃更新**：倒序DP中遇到加糖操作时调整循环变量，直接处理跳跃后的状态。  

### 同类题目推荐
1. [P1807 最长路](https://www.luogu.com.cn/problem/P1807)（图论最长路径）  
2. [P3953 逛公园](https://www.luogu.com.cn/problem/P3953)（带环检测的最短路计数）  
3. [P2741 [USACO4.4] 重叠矩形](https://www.luogu.com.cn/problem/P2741)（状态转移与环检测）  

### 题解心得分野
- **L______**提到“直接调整i指针实现状态跳跃”，这种暴力调整循环变量的方式在特定场景下能简化状态转移逻辑。  
- **_Wind_Leaves_ShaDow_**强调“初始状态不能直接加糖”，需注意题目中加糖条件仅在吃完后触发。

---
处理用时：64.04秒