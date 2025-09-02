# 题目信息

# EXCEEDED WARNING A

## 题目描述

有这样一些数据，它们均为小于 $10^9$ 的非负整数，且个数为 $n$，现在请你输出其中最小的 $m$ 个数。

小心溢出，注意 Memory Limit = 4000KiB。


## 说明/提示

数据范围：$m<10^5, n<10^6$。

## 样例 #1

### 输入

```
10 5
2
4
6
8
10
1
3
5
7
9```

### 输出

```
1
2
3
4
5```

# AI分析结果

### 算法分类
排序

### 综合分析与结论
题目要求从大量数据中找出最小的m个数，且内存限制较严格。大多数题解采用了堆（优先队列）或排序算法来解决。堆的解法较为高效，能够在O(n log m)的时间复杂度内完成，且空间复杂度为O(m)，适合处理大规模数据。排序算法虽然简单，但在内存限制下可能无法直接使用。

### 所选高星题解
1. **题解作者：_neddy (赞：50)**
   - **星级：5星**
   - **关键亮点**：使用大根堆维护最小的m个数，通过不断更新堆顶元素来筛选最小的m个数，最后将结果从小根堆中输出。思路清晰，代码简洁，且充分利用了STL的优先队列。
   - **个人心得**：作者提到前后交了二十多次才成功，强调了调试的重要性。
   - **核心代码**：
     ```cpp
     priority_queue<int, vector<int>, less<int> > a; // 大根堆
     priority_queue<int, vector<int>, greater<int> > s; // 小根堆
     for (register int i = 1; i <= m; ++i) {
         int num;
         scanf("%d", &num);
         a.push(num);
     }
     for (register int i = m + 1, num; i <= n; ++i) {
         scanf("%d", &num);
         if (num < a.top()) a.pop(), a.push(num);
     }
     for (register int i = 1; i <= m; ++i) {
         s.push(a.top());
         a.pop();
     }
     while(s.size()) printf("%d\n", s.top()), s.pop();
     ```

2. **题解作者：TsReaper (赞：48)**
   - **星级：4星**
   - **关键亮点**：同样使用大根堆维护最小的m个数，思路与_neddy类似，但代码更为简洁，直接在大根堆中维护m个数，最后排序输出。
   - **核心代码**：
     ```cpp
     priority_queue<int> q; // 大根堆
     for (int i = 1; i <= m; ++i) {
         int num;
         scanf("%d", &num);
         q.push(num);
     }
     for (int i = m + 1; i <= n; ++i) {
         int num;
         scanf("%d", &num);
         if (num < q.top()) {
             q.pop();
             q.push(num);
         }
     }
     vector<int> res;
     while (!q.empty()) {
         res.push_back(q.top());
         q.pop();
     }
     sort(res.begin(), res.end());
     for (int x : res) printf("%d\n", x);
     ```

3. **题解作者：psk011102 (赞：4)**
   - **星级：4星**
   - **关键亮点**：使用手写堆来实现大根堆，虽然代码较长，但展示了堆的基本操作，适合学习堆的实现原理。
   - **核心代码**：
     ```cpp
     void up(ll sum) {
         ll now = sum;
         while (now > 1 && c[now >> 1] < c[now]) {
             ll t = c[now];
             c[now] = c[now >> 1];
             c[now >> 1] = t;
             now = now >> 1;
         }
     }
     void down() {
         ll now = 1;
         while (((now << 1) <= m && c[now] < c[now << 1]) || ((now << 1 | 1) <= m && c[now] < c[now << 1 | 1])) {
             ll next = now << 1;
             if (c[next] < c[next + 1]) next++;
             ll t = c[next];
             c[next] = c[now];
             c[now] = t;
             now = next;
         }
     }
     ```

### 最优关键思路
使用大根堆维护最小的m个数，通过不断更新堆顶元素来筛选最小的m个数，最后将结果排序输出。这种方法在时间和空间复杂度上都较为高效，适合处理大规模数据。

### 可拓展之处
类似的问题可以扩展到寻找第k大/小的元素，或者处理数据流中的Top K问题。堆的思想在这些问题中同样适用。

### 推荐题目
1. P3378 【模板】堆
2. P1168 中位数
3. P1090 合并果子

---
处理用时：32.81秒