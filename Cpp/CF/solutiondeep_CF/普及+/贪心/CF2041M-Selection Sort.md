# 题目信息

# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 样例 #1

### 输入

```
6
3 2 5 5 4 1```

### 输出

```
25```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
16```

# AI分析结果



# 题目重写

## 题目描述

每位选修算法课程的学生本周都需要提交作业，任务是实现一个时间复杂度为 $O(n^2)$ 的算法，将 $n$ 个整数按非递减顺序排序。Alice 已经完成了她的作业，她的实现如下：

```cpp
int alice_sort(int *s, int n){
  for(int i = 0; i < n; ++i){
    for(int j = i + 1; j < n; ++j){
      if(s[i] > s[j]){
        int swap = s[i];
        s[i] = s[j];
        s[j] = swap;
      }
    }
  }
  return 0;
}
```

你需要利用 Alice 的排序函数（最多各使用一次前缀排序和后缀排序）完成排序，并最小化总代价。前缀排序选择长度 $i$ 的代价为 $i^2$，后缀排序选择长度 $i$ 的代价为 $i^2$。

例如，数组 $[3,2,5,5,4,1]$ 可以先进行长度为 4 的后缀排序（代价 16），再进行长度为 3 的前缀排序（代价 9），总代价为 25。

---

# 题解分析与结论

**核心思路**：预处理排序数组，利用双堆维护当前未匹配元素，枚举两次排序的分界点。关键点在于通过堆结构动态维护需要二次排序的剩余元素数量，并考虑单次排序的边界情况。

## 精选题解

### 题解一（lfxxx） 评分：★★★★☆
**核心思路**：
1. 预处理排序数组 `b[]`
2. 正序遍历维护前缀堆：用两个最大堆分别存储原数组前i元素和排序数组前i元素，动态计算需要二次排序的元素量
3. 逆序遍历维护后缀堆：同理处理后缀情况
4. 处理单次排序特例（完全排序的前缀/后缀）

**代码亮点**：
```cpp
// 前缀处理部分
priority_queue<int> q1,q2;
for(int i=1;i<=n;i++){
    q1.push(-a[i]);   // 原数组元素（取负实现最小堆）
    q2.push(-b[i]);   // 目标数组元素
    while(q1.size()>0&&q1.top()==q2.top()) 
        q1.pop(), q2.pop(); // 消去已匹配元素
    ans = min(ans, 1ll*i*i + 1ll*(n-i+q1.size())*(n-i+q1.size()));
}
// 后缀处理类似，代码对称
```

### 题解三（沉石鱼惊旋） 评分：★★★★☆
**核心技巧**：将原数组转换为唯一排列处理重复值，维护连续有序段。通过堆扩展当前可合并区间，动态计算二次排序范围。

**实现要点**：
```cpp
// 维护前缀连续段
int lst = 0;
priority_queue<int, vector<int>, greater<int>> pq;
for(int i=1; i<=n; i++){
    if(a[i] == lst+1) lst++;
    else if(a[i] > lst) pq.push(a[i]);
    while(!pq.empty() && pq.top() == lst+1){
        lst++;
        pq.pop();
    }
    cost[i] = i + pq.size(); // 二次排序长度
}
ans = min(ans, cost[i]^2 + ...);
```

---

# 关键思路总结

1. **双堆消元法**：通过维护原数组与目标数组的差异堆，动态计算二次排序范围
2. **边界特判**：单独处理完全通过一次排序即可完成的情况
3. **对称处理**：分别处理先前缀后后缀、先后缀后前缀两种情况，取最小值
4. **线性预处理**：通过 $O(n)$ 预处理确定每个位置前后已排序的区间

---

# 举一反三

1. **类似堆维护技巧**：P1090 [NOIP2004 提高组] 合并果子（优先队列贪心）
2. **分段排序思想**：P1177 【模板】快速排序（分治策略）
3. **区间操作优化**：P1908 逆序对（分治与数据结构结合）

---
处理用时：63.41秒