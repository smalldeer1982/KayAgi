# 题目信息

# Workout plan

## 题目描述

Alan decided to get in shape for the summer, so he created a precise workout plan to follow. His plan is to go to a different gym every day during the next N days and lift $ X[i] $ grams on day $ i $ . In order to improve his workout performance at the gym, he can buy exactly one pre-workout drink at the gym he is currently in and it will improve his performance by $ A $ grams permanently and immediately. In different gyms these pre-workout drinks can cost different amounts $ C[i] $ because of the taste and the gym's location but its permanent workout gains are the same. Before the first day of starting his workout plan, Alan knows he can lift a maximum of $ K $ grams. Help Alan spend a minimum total amount of money in order to reach his workout plan. If there is no way for him to complete his workout plan successfully output $ -1 $ .

## 说明/提示

First example: After buying drinks on days 2 and 4 Alan can finish his workout plan. Second example: Alan cannot lift 40000 grams on day 2.

## 样例 #1

### 输入

```
5 10000
10000 30000 30000 40000 20000
20000
5 2 8 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 10000
10000 40000 30000 30000 20000
10000
5 2 8 3 6
```

### 输出

```
-1
```

# AI分析结果

【题目内容】
# 健身计划

## 题目描述

Alan决定为夏天塑造身材，因此他制定了一个精确的健身计划。他的计划是在接下来的N天里每天去不同的健身房，并在第i天举起$X[i]$克。为了在健身房提高他的健身表现，他可以在当前所在的健身房购买一种健身前饮料，这种饮料会立即永久性地将他的表现提高$A$克。不同健身房的这种饮料价格可能不同，因为口味和地理位置的原因，但它们的永久性健身增益是相同的。在开始健身计划的第一天之前，Alan知道他最多可以举起$K$克。帮助Alan花费最少的钱来完成他的健身计划。如果他无法成功完成健身计划，输出$-1$。

## 说明/提示

第一个例子：在第2天和第4天购买饮料后，Alan可以完成他的健身计划。第二个例子：Alan在第2天无法举起40000克。

## 样例 #1

### 输入

```
5 10000
10000 30000 30000 40000 20000
20000
5 2 8 3 6
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 10000
10000 40000 30000 30000 20000
10000
5 2 8 3 6
```

### 输出

```
-1
```

【算法分类】
贪心

【题解分析与结论】
所有题解均采用了贪心算法，核心思路是通过优先队列（小根堆）维护当前可用的饮料价格，每次在无法达到目标时选择最便宜的饮料来提升能力值。这种贪心策略保证了每次选择的代价最小，从而最终达到总代价最小的目标。

【所选高星题解】
1. **作者：DarkShadow (赞：4)**
   - **星级：5星**
   - **关键亮点：**
     - 使用小根堆维护当前可用的饮料价格，确保每次选择的代价最小。
     - 代码简洁，逻辑清晰，易于理解。
   - **核心代码：**
     ```cpp
     priority_queue<int,deque<int>,greater<int>> q;
     for(int i=1;i<=n;i++){
         q.push(c[i]);
         while(cnt<x[i]&&!q.empty()){
             cnt+=a,ans+=q.top();
             q.pop();
         }
         if(cnt<x[i]){
             printf("-1");
             return 0;
         }
     }
     ```

2. **作者：Victory_Defeat (赞：3)**
   - **星级：4星**
   - **关键亮点：**
     - 同样使用小根堆，代码结构清晰，注释详细。
     - 对无解情况的处理简洁明了。
   - **核心代码：**
     ```cpp
     priority_queue<int,vector<int>,greater<int> >q;
     for(int i=1;i<=n;i++){
         q.push(c[i]);
         while(k<x[i]){
             if(q.empty()){
                 printf("-1\n");
                 return 0;
             }
             k+=a;
             ans+=q.top();
             q.pop();
         }
     }
     ```

3. **作者：RioFutaba (赞：0)**
   - **星级：4星**
   - **关键亮点：**
     - 使用小根堆实现贪心策略，代码简洁明了。
     - 对无解情况的处理直接且有效。
   - **核心代码：**
     ```cpp
     priority_queue<int,vector<int>,greater<int>> q;
     for(int i=1;i<=n;i++){
         q.push(c[i]);
         while(k<x[i] && !q.empty()){
             int p=q.top();
             q.pop();
             ans+=p;
             k+=a;
         }
         if(k<x[i]){
             ans=-1;
             break;
         }
     }
     ```

【最优关键思路或技巧】
- **贪心策略**：每次选择当前可用的最小代价饮料，确保总代价最小。
- **数据结构**：使用小根堆（优先队列）来高效地维护和选择最小代价的饮料。

【可拓展之处】
- 类似的问题可以扩展到其他资源分配问题，如任务调度、资源分配等，只要满足每次选择最小代价的策略即可。

【推荐题目】
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：29.43秒