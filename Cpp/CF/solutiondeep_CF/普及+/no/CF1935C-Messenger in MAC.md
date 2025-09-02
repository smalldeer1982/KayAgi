# 题目信息

# Messenger in MAC

## 题目描述

In the new messenger for the students of the Master's Assistance Center, Keftemerum, an update is planned, in which developers want to optimize the set of messages shown to the user. There are a total of $ n $ messages. Each message is characterized by two integers $ a_i $ and $ b_i $ . The time spent reading the set of messages with numbers $ p_1, p_2, \ldots, p_k $ ( $ 1 \le p_i \le n $ , all $ p_i $ are distinct) is calculated by the formula:

 $ $$$\Large \sum_{i=1}^{k} a_{p_i} + \sum_{i=1}^{k - 1} |b_{p_i} - b_{p_{i+1}}| $ $ </p><p>Note that the time to read a set of messages consisting of <span class="tex-font-style-bf">one</span> message with number  $ p\_1 $  is equal to  $ a\_{p\_1} $ . Also, the time to read an empty set of messages is considered to be  $ 0 $ .</p><p>The user can determine the time  $ l $  that he is willing to spend in the messenger. The messenger must inform the user of the maximum possible size of the set of messages, the reading time of which does not exceed  $ l $ . Note that the maximum size of the set of messages can be equal to  $ 0$$$.

The developers of the popular messenger failed to implement this function, so they asked you to solve this problem.

## 说明/提示

In the first test case, you can take a set of three messages with numbers $ p_1 = 3 $ , $ p_2 = 2 $ , and $ p_3 = 5 $ . The time spent reading this set is equal to $ a_3 + a_2 + a_5 + |b_3 - b_2| + |b_2 - b_5| = 2 + 1 + 2 + |4 - 5| + |5 - 3| = 8 $ .

In the second test case, you can take a set of one message with number $ p_1 = 1 $ . The time spent reading this set is equal to $ a_1 = 4 $ .

In the fifth test case, it can be shown that there is no such non-empty set of messages, the reading time of which does not exceed $ l $ .

## 样例 #1

### 输入

```
5
5 8
4 3
1 5
2 4
4 3
2 3
1 6
4 10
3 12
4 8
2 1
2 12
5 26
24 7
8 28
30 22
3 8
17 17
5 14
15 3
1000000000 998244353
179 239
228 1337
993 1007```

### 输出

```
3
1
2
1
0```

# AI分析结果

### 题目内容重写

#### 题目描述

在Keftemerum的学生助手中心的新版消息应用中，开发者计划进行一次更新，旨在优化用户看到的消息集合。总共有$n$条消息，每条消息由两个整数$a_i$和$b_i$表示。用户选择一组消息编号为$p_1, p_2, \ldots, p_k$（$1 \le p_i \le n$，且所有$p_i$互不相同），读取这组消息所花费的时间由以下公式计算：

$$ \sum_{i=1}^{k} a_{p_i} + \sum_{i=1}^{k - 1} |b_{p_i} - b_{p_{i+1}}| $$

注意，读取单条消息$p_1$的时间为$a_{p_1}$，读取空消息集合的时间为$0$。

用户可以设定一个时间$l$，表示他愿意在消息应用中花费的时间。消息应用需要告知用户，在不超出$l$的情况下，能够读取的最大消息数量。注意，最大消息数量可以为$0$。

开发者未能实现这一功能，因此请求你解决这个问题。

#### 说明/提示

在第一个测试用例中，可以选择编号为$p_1 = 3$、$p_2 = 2$和$p_3 = 5$的三条消息。读取这组消息的时间为$a_3 + a_2 + a_5 + |b_3 - b_2| + |b_2 - b_5| = 2 + 1 + 2 + |4 - 5| + |5 - 3| = 8$。

在第二个测试用例中，可以选择编号为$p_1 = 1$的一条消息。读取这组消息的时间为$a_1 = 4$。

在第五个测试用例中，可以证明不存在非空的消息集合，其读取时间不超过$l$。

#### 样例输入

```
5
5 8
4 3
1 5
2 4
4 3
2 3
1 6
4 10
3 12
4 8
2 1
2 12
5 26
24 7
8 28
30 22
3 8
17 17
5 14
15 3
1000000000 998244353
179 239
228 1337
993 1007
```

#### 样例输出

```
3
1
2
1
0
```

### 算法分类
贪心、动态规划

### 题解分析与结论

#### 综合分析

1. **贪心策略**：大部分题解都采用了贪心策略，即按照$b_i$的值进行排序，然后通过维护一个堆来选择$a_i$最小的消息，使得总时间不超过$l$。这种策略的核心思想是通过排序和堆的维护来优化选择过程，减少时间复杂度。

2. **动态规划**：部分题解采用了动态规划的方法，通过定义状态$f_{i,j}$表示前$i$个消息中选择$j$个消息的最小时间，然后通过状态转移方程进行优化。这种方法虽然时间复杂度较高，但在某些情况下能够提供更精确的解。

3. **优化技巧**：许多题解中使用了优先队列（堆）来维护当前选择的消息，通过不断调整堆中的元素来保证总时间不超过$l$。这种技巧在贪心策略中非常有效，能够显著降低时间复杂度。

#### 精选题解

1. **作者：lbdontknow (赞：7)**
   - **星级**：4.5
   - **关键亮点**：通过排序和优先队列（堆）来优化选择过程，代码简洁且高效。通过维护堆中的元素和总和，确保总时间不超过$l$。
   - **代码核心思想**：
     ```cpp
     priority_queue<int>pq;
     int sum = 0;
     for(int r = l ; r <= n ; r++){
         pq.push(a[r].a);
         sum += a[r].a;
         while(pq.size() && sum > L - a[r].b + a[l].b){
             sum -= pq.top();
             pq.pop();
         }
         ans = max(ans, (int)pq.size());
     }
     ```

2. **作者：Alex_Wei (赞：7)**
   - **星级**：4.5
   - **关键亮点**：采用动态规划的方法，通过定义状态$f_{i,j}$表示前$i$个消息中选择$j$个消息的最小时间，并使用前缀最小值进行优化。思路清晰，代码结构良好。
   - **代码核心思想**：
     ```cpp
     for(int i = 1; i <= n; i++){
         f[i][1] = a[i] - b[i];
         for(int j = 2; j <= i; j++){
             f[i][j] = min(f[i-1][j], f[i-1][j-1] + a[i]);
         }
     }
     ```

3. **作者：fast_photon (赞：4)**
   - **星级**：4
   - **关键亮点**：通过二分答案和贪心策略结合，使用优先队列来维护当前选择的消息，确保总时间不超过$l$。思路新颖，代码实现较为复杂但有效。
   - **代码核心思想**：
     ```cpp
     while(!q.empty()) q.pop();
     int sum = 0;
     for(int j = i; j <= n; j++){
         q.push(a[j].a);
         sum += a[j].a;
         while(sum + a[j].b - a[i].b > l && !q.empty()){
             sum -= q.top();
             q.pop();
         }
         ans = max(ans, cnt);
     }
     ```

### 最优关键思路与技巧

1. **排序与贪心**：通过将消息按照$b_i$排序，并使用贪心策略选择$a_i$最小的消息，能够有效减少总时间。

2. **优先队列（堆）**：使用优先队列来维护当前选择的消息，通过不断调整堆中的元素，确保总时间不超过$l$。

3. **动态规划优化**：通过定义状态$f_{i,j}$并使用前缀最小值进行优化，能够在动态规划中减少时间复杂度。

### 可拓展之处

1. **类似问题**：类似的问题可以出现在其他需要选择最优子集的情境中，如背包问题、任务调度等。

2. **算法套路**：贪心与动态规划的结合，以及优先队列的使用，是解决此类问题的常见套路。

### 推荐题目

1. **洛谷P1048**：采药（背包问题）
2. **洛谷P1090**：合并果子（贪心与优先队列）
3. **洛谷P1064**：金明的预算方案（动态规划与背包问题）

---
处理用时：61.58秒