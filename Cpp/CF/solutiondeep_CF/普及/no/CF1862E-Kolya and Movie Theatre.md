# 题目信息

# Kolya and Movie Theatre

## 题目描述

Recently, Kolya found out that a new movie theatre is going to be opened in his city soon, which will show a new movie every day for $ n $ days. So, on the day with the number $ 1 \le i \le n $ , the movie theatre will show the premiere of the $ i $ -th movie. Also, Kolya found out the schedule of the movies and assigned the entertainment value to each movie, denoted by $ a_i $ .

However, the longer Kolya stays without visiting a movie theatre, the larger the decrease in entertainment value of the next movie. That decrease is equivalent to $ d \cdot cnt $ , where $ d $ is a predetermined value and $ cnt $ is the number of days since the last visit to the movie theatre. It is also known that Kolya managed to visit another movie theatre a day before the new one opened — the day with the number $ 0 $ . So if we visit the movie theatre the first time on the day with the number $ i $ , then $ cnt $ — the number of days since the last visit to the movie theatre will be equal to $ i $ .

For example, if $ d = 2 $ and $ a = [3, 2, 5, 4, 6] $ , then by visiting movies with indices $ 1 $ and $ 3 $ , $ cnt $ value for the day $ 1 $ will be equal to $ 1 - 0 = 1 $ and $ cnt $ value for the day $ 3 $ will be $ 3 - 1 = 2 $ , so the total entertainment value of the movies will be $ a_1 - d \cdot 1 + a_3 - d \cdot 2 = 3 - 2 \cdot 1 + 5 - 2 \cdot 2 = 2 $ .

Unfortunately, Kolya only has time to visit at most $ m $ movies. Help him create a plan to visit the cinema in such a way that the total entertainment value of all the movies he visits is maximized.

## 说明/提示

The first test case is explained in the problem statement.

In the second test case, it is optimal not to visit any movies.

In the third test case, it is optimal to visit movies with numbers $ 2 $ , $ 3 $ , $ 5 $ , $ 6 $ , so the total entertainment value of the visited movies will be $ 45 - 6 \cdot 2 + 1 - 6 \cdot 1 + 39 - 6 \cdot 2 + 11 - 6 \cdot 1 = 60 $ .

## 样例 #1

### 输入

```
6
5 2 2
3 2 5 4 6
4 3 2
1 1 1 1
6 6 6
-82 45 1 -77 39 11
5 2 2
3 2 5 4 8
2 1 1
-1 2
6 3 2
-8 8 -2 -1 9 0```

### 输出

```
2
0
60
3
0
7```

# AI分析结果

### 题目内容重写
最近，Kolya发现他所在的城市即将开放一家新的电影院，该电影院将在接下来的$n$天内每天放映一部新电影。因此，在第$1 \le i \le n$天，电影院将放映第$i$部电影的首映。Kolya还找到了电影的时间表，并为每部电影分配了娱乐值$a_i$。

然而，Kolya越久不去电影院，下一部电影的娱乐值下降得越多。下降的值等于$d \cdot cnt$，其中$d$是预定的值，$cnt$是自上次访问电影院以来的天数。已知Kolya在新电影院开放的前一天（第0天）访问了另一家电影院。因此，如果我们第一次在第$i$天访问电影院，那么$cnt$（自上次访问电影院以来的天数）将等于$i$。

例如，如果$d = 2$且$a = [3, 2, 5, 4, 6]$，那么通过访问第1天和第3天的电影，第1天的$cnt$值为$1 - 0 = 1$，第3天的$cnt$值为$3 - 1 = 2$，因此所有电影的娱乐值总和为$a_1 - d \cdot 1 + a_3 - d \cdot 2 = 3 - 2 \cdot 1 + 5 - 2 \cdot 2 = 2$。

不幸的是，Kolya最多只有时间访问$m$部电影。帮助他制定一个访问电影院的计划，使得他访问的所有电影的娱乐值总和最大化。

### 算法分类
贪心

### 题解分析与结论
题解的核心思路是利用贪心算法，通过维护一个优先队列（小根堆）来动态选择前$m$个最大的正数娱乐值，并计算当前的最大娱乐值。难点在于如何高效地维护前$m$个最大的正数娱乐值，并确保每次计算娱乐值时减去$d \cdot i$的损失。

### 高星题解
#### 题解1：Rain_javalearner (5星)
**关键亮点**：
- 使用优先队列（小根堆）动态维护前$m$个最大的正数娱乐值。
- 每次计算当前的最大娱乐值，并更新答案。
- 代码简洁，思路清晰。

**核心代码**：
```cpp
priority_queue<i64, vector<i64>, greater<i64> > q;
for(i64 i = 1 ; i<= n ; i++) {
    scanf("%lld", &x);
    if(x > 0) q.push(x), sum += x;
    while(q.size() > m) sum -= q.top(), q.pop();
    ans = max(ans, sum - d*i);
}
```

#### 题解2：Scorilon (4星)
**关键亮点**：
- 使用大根堆（存相反数）实现小根堆的功能，进行反悔贪心。
- 通过反悔操作替换较小的娱乐值，确保选择前$m$个最大的正数娱乐值。
- 代码实现较为巧妙。

**核心代码**：
```cpp
std::priority_queue<int> q;
for(int i=1;i<=n;i++) {
    if(a[i]<0) continue;
    if(tot<m) {
        tot++;
        q.push(-a[i]);
        sum+=a[i];
    } else if(-q.top()<a[i]) {
        sum+=q.top();
        q.pop();
        sum+=a[i];
        q.push(-a[i]);
    }
    ans=std::max(ans,sum-1ll*d*i);
}
```

#### 题解3：YBaggio (4星)
**关键亮点**：
- 使用优先队列动态维护前$m$个最大的正数娱乐值。
- 每次计算当前的最大娱乐值，并更新答案。
- 代码简洁，思路清晰。

**核心代码**：
```cpp
priority_queue <pair <ll, int>> q; 
for (int i = 1; i <= n; i++) {
    ans = max (ans, sum + a[i] - d * i);
    if (a[i] > 0) {
        q.push ({-a[i], i});
        sum += a[i];
        if (q.size () >= m) {
            sum += q.top ().first;
            q.pop ();
        }
    }
}
```

### 最优关键思路或技巧
- **优先队列（小根堆）**：用于动态维护前$m$个最大的正数娱乐值，确保每次选择最优的娱乐值。
- **反悔贪心**：通过替换较小的娱乐值，确保选择前$m$个最大的正数娱乐值，从而最大化总娱乐值。

### 可拓展之处
- 类似的问题可以使用贪心算法结合优先队列来解决，例如在资源有限的情况下选择最优的子集。
- 可以扩展到其他需要动态维护前$k$个最大值的问题，如选择最优的$k$个任务或资源分配问题。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P3378 堆](https://www.luogu.com.cn/problem/P3378)

### 个人心得摘录
- **Rain_javalearner**：赛场上止步于此，但通过优先队列贪心解决了问题。
- **Scorilon**：算是反悔贪心板子题，时间复杂度$O(n\log n)$，记得开`long long`，吃了两发。
- **YBaggio**：$d$的系数仅与看的最后一场$i_s$有关，因此可以枚举看的最后一场电影，得到$- i_s \cdot d$的取值，随后贪心选择第$i_1 \dots i_{s-1}$场电影。

---
处理用时：33.28秒