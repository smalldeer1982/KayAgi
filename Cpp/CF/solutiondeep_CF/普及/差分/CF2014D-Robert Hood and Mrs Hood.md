# 题目信息

# Robert Hood and Mrs Hood

## 题目描述

Impress thy brother, yet fret not thy mother.



Robin's brother and mother are visiting, and Robin gets to choose the start day for each visitor.

All days are numbered from $ 1 $ to $ n $ . Visitors stay for $ d $ continuous days, all of those $ d $ days must be between day $ 1 $ and $ n $ inclusive.

Robin has a total of $ k $ risky 'jobs' planned. The $ i $ -th job takes place between days $ l_i $ and $ r_i $ inclusive, for $ 1 \le i \le k $ . If a job takes place on any of the $ d $ days, the visit overlaps with this job (the length of overlap is unimportant).

Robin wants his brother's visit to overlap with the maximum number of distinct jobs, and his mother's the minimum.

Find suitable start days for the visits of Robin's brother and mother. If there are multiple suitable days, choose the earliest one.

## 说明/提示

In the first test case, the only job fills all $ 2 $ days, both should visit on day $ 1 $ .

In the second test case, day $ 2 $ overlaps with $ 2 $ jobs and day $ 1 $ overlaps with only $ 1 $ .

In the third test case, Robert visits for days $ [1,2] $ , Mrs. Hood visits for days $ [4,5] $ .

## 样例 #1

### 输入

```
6
2 1 1
1 2
4 1 2
1 2
2 4
7 2 3
1 2
1 3
6 7
5 1 2
1 2
3 5
9 2 1
2 8
9 2 4
7 9
4 8
1 3
2 3```

### 输出

```
1 1
2 1
1 4
1 1
1 1
3 4```

# AI分析结果

### 题目内容重写

#### 题目描述

Robin的兄弟和母亲要来拜访，Robin需要为每位访客选择访问的起始日期。

所有日期从$1$到$n$编号。访客会连续访问$d$天，所有这$d$天都必须在$1$到$n$之间（包括$1$和$n$）。

Robin总共有$k$个危险的“工作”计划。第$i$个工作发生在$l_i$到$r_i$天之间（包括$l_i$和$r_i$），其中$1 \le i \le k$。如果某个工作发生在访客访问的$d$天中的任何一天，那么这次访问就与这个工作重叠（重叠的长度不重要）。

Robin希望他兄弟的访问与尽可能多的不同工作重叠，而他母亲的访问与尽可能少的工作重叠。

请为Robin的兄弟和母亲找到合适的访问起始日期。如果有多个合适的日期，选择最早的日期。

#### 说明/提示

在第一个测试用例中，唯一的工作占据了所有$2$天，因此兄弟和母亲都应该在第$1$天开始访问。

在第二个测试用例中，第$2$天与$2$个工作重叠，而第$1$天只与$1$个工作重叠。

在第三个测试用例中，兄弟访问$[1,2]$天，母亲访问$[4,5]$天。

### 题解分析与结论

#### 综合分析

本题的核心问题是如何高效地计算每个可能的$d$天访问区间与所有工作区间的重叠次数，并分别找到重叠次数最多和最少的起始日期。题解中主要采用了差分数组、前缀和、滑动窗口等技巧来优化计算过程。

#### 最优题解

1. **题解作者：cly312 (赞：4)**  
   - **星级：★★★★★**  
   - **关键亮点：** 使用差分数组和前缀和技巧，将区间重叠问题转化为点贡献问题，时间复杂度为$O(n)$，代码简洁且高效。  
   - **代码核心思想：** 通过差分数组记录每个工作对可能访问区间的影响，然后通过前缀和计算每个起始日期的重叠次数，最后遍历找到最大值和最小值对应的起始日期。  
   - **核心代码：**
     ```cpp
     vector<int> cover(n + 2, 0);
     for (int i = 0; i < k; ++i) {
         int l, r;
         cin >> l >> r;
         cover[max(1,l-d+1)]++;
         cover[r + 1]--;
     }
     for (int i = 1; i <= n; ++i) {
         cover[i] += cover[i - 1];
     }
     int bday = 1, mday = 1;
     int maxn = -1, minn = INT_MAX;
     for (int day = 1; day <= n - d + 1; ++day) {
         if (cover[day] > maxn) {
             maxn = cover[day];
             bday = day;
         }
         if (cover[day] < minn) {
             minn = cover[day];
             mday = day;
         }
     }
     cout << bday << ' ' << mday << '\n';
     ```

2. **题解作者：Temp113 (赞：3)**  
   - **星级：★★★★**  
   - **关键亮点：** 同样使用差分数组和前缀和技巧，代码结构清晰，变量命名合理，易于理解。  
   - **代码核心思想：** 与cly312的题解类似，通过差分数组记录工作对访问区间的影响，然后通过前缀和计算每个起始日期的重叠次数，最后遍历找到最大值和最小值对应的起始日期。  
   - **核心代码：**
     ```cpp
     for(int i = 1; i <= k; i++){
         cin >> l >> r;
         a[max_(1, l - d + 1)]++;
         a[r + 1]--;
     }
     for(int i = 1; i <= n; i++) a[i] += a[i - 1];
     for(int i = 1; i <= n - d + 1; i++){
         if(a[i] > maxa){
             maxa = a[i];
             ans1 = i;
         }
         if(a[i] < mina){
             mina = a[i];
             ans2 = i;
         }
     }
     cout << ans1 << ' ' << ans2 << '\n';
     ```

3. **题解作者：Hide_In_The_Shadow (赞：1)**  
   - **星级：★★★★**  
   - **关键亮点：** 使用前缀和技巧，分别记录每个日期的任务开始和结束次数，通过前缀和快速计算每个访问区间的重叠次数，代码简洁且易于理解。  
   - **代码核心思想：** 通过前缀和数组记录每个日期的任务开始和结束次数，然后通过前缀和计算每个访问区间的重叠次数，最后遍历找到最大值和最小值对应的起始日期。  
   - **核心代码：**
     ```cpp
     for(int i=1;i<=k;++i){
         int L,R;
         read(L);
         l[L]++;
         read(R);
         r[R]++;
     }
     for(int i=1;i<=n;++i){
         suml[i]=suml[i-1]+l[i];
         sumr[i]=sumr[i-1]+r[i];
     }
     for(int i=1;i<=n;++i){
         int L=i;
         int R=L+d-1;
         if(R>n)break;
         int te=suml[R]-sumr[L-1];
         if(mx<te){
             mx=te;
             bro=L;
         }
         if(mi>te){
             mi=te;
             mum=L;
         }
     }
     wr1(bro),wr2(mum);
     ```

### 最优关键思路与技巧

1. **差分数组与前缀和：** 通过差分数组记录每个工作对访问区间的影响，然后通过前缀和快速计算每个起始日期的重叠次数，时间复杂度为$O(n)$，适用于处理区间重叠问题。
2. **滑动窗口：** 通过滑动窗口维护当前访问区间的重叠次数，适用于需要动态计算区间重叠次数的场景。

### 可拓展之处

1. **类似问题：** 该技巧可以应用于其他需要计算区间重叠次数的问题，如区间覆盖、区间查询等。
2. **数据结构：** 可以使用树状数组或线段树来进一步优化区间查询的效率，适用于更大规模的数据。

### 推荐题目

1. **P2184 贪婪大陆**  
   题目链接：https://www.luogu.com.cn/problem/P2184  
   考察知识点：区间查询、树状数组

2. **P3372 【模板】线段树 1**  
   题目链接：https://www.luogu.com.cn/problem/P3372  
   考察知识点：线段树、区间更新与查询

3. **P1908 逆序对**  
   题目链接：https://www.luogu.com.cn/problem/P1908  
   考察知识点：树状数组、逆序对计算

---
处理用时：53.52秒