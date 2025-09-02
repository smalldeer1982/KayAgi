# 题目信息

# Ehab and subtraction

## 题目描述

You're given an array $ a $ . You should repeat the following operation $ k $ times: find the minimum non-zero element in the array, print it, and then subtract it from all the non-zero elements of the array. If all the elements are 0s, just print 0.

## 说明/提示

In the first sample:

In the first step: the array is $ [1,2,3] $ , so the minimum non-zero element is 1.

In the second step: the array is $ [0,1,2] $ , so the minimum non-zero element is 1.

In the third step: the array is $ [0,0,1] $ , so the minimum non-zero element is 1.

In the fourth and fifth step: the array is $ [0,0,0] $ , so we printed 0.

In the second sample:

In the first step: the array is $ [10,3,5,3] $ , so the minimum non-zero element is 3.

In the second step: the array is $ [7,0,2,0] $ , so the minimum non-zero element is 2.

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
1
1
1
0
0
```

## 样例 #2

### 输入

```
4 2
10 3 5 3
```

### 输出

```
3
2
```

# AI分析结果

【题目内容】
# Ehab and subtraction

## 题目描述

给定一个数组 $a$，你需要重复以下操作 $k$ 次：找到数组中最小非零元素，输出它，然后将它从数组中的所有非零元素中减去。如果所有元素都为 0，则输出 0。

## 说明/提示

在第一个样例中：

第一步：数组为 $[1,2,3]$，最小非零元素为 1。

第二步：数组为 $[0,1,2]$，最小非零元素为 1。

第三步：数组为 $[0,0,1]$，最小非零元素为 1。

第四步和第五步：数组为 $[0,0,0]$，输出 0。

在第二个样例中：

第一步：数组为 $[10,3,5,3]$，最小非零元素为 3。

第二步：数组为 $[7,0,2,0]$，最小非零元素为 2。

## 样例 #1

### 输入

```
3 5
1 2 3
```

### 输出

```
1
1
1
0
0
```

## 样例 #2

### 输入

```
4 2
10 3 5 3
```

### 输出

```
3
2
```

【算法分类】
排序、贪心

【题解分析与结论】
本题的核心思路是通过排序和贪心策略来优化查找最小非零元素的过程。大多数题解都采用了排序和优先队列的方法，以减少每次操作的时间复杂度。以下是各题解的要点对比：

1. **排序+二分查找**：通过排序后使用二分查找来快速定位最小非零元素，时间复杂度为 $O(n \log n + k \log n)$。
2. **排序+去重**：排序后使用 `unique` 函数去重，直接输出相邻元素的差值，时间复杂度为 $O(n \log n + k)$。
3. **优先队列**：使用小根堆维护最小非零元素，通过懒标记（`sum`）来记录累计减去的值，时间复杂度为 $O(n \log n + k \log n)$。

【评分较高的题解】

1. **作者：little_sun (4星)**
   - **关键亮点**：通过排序和二分查找优化了查找最小非零元素的过程，代码清晰且高效。
   - **核心代码**：
     ```cpp
     std::sort(a + 1, a + n + 1);
     for(int i = 1; i <= k; i++) {
         if(pos == n + 1) {
             printf("0\n");
             continue;
         }
         printf("%I64d\n", a[pos] - now);
         now += a[pos] - now;
         ll l = pos + 1, r = n + 1;
         while(l < r) {
             ll mid = (l + r) >> 1;
             if(a[mid] > now) r = mid;
             else l = mid + 1;
         }
         pos = l;
     }
     ```

2. **作者：floatery (3星)**
   - **关键亮点**：使用 `unique` 函数去重，简化了输出相邻元素差值的逻辑，代码简洁。
   - **核心代码**：
     ```cpp
     sort(a + 1, a + n + 1);
     unique(a + 1, a + n + 1);
     for(int i = 1; i <= k; i++) {
         if(i >= mark) {
             printf("0\n");
         } else {
             printf("%d\n", a[i] - a[i-1]);
         }
     }
     ```

3. **作者：meimu75 (3星)**
   - **关键亮点**：使用优先队列和懒标记（`sum`）来维护最小非零元素，思路清晰且优化了时间复杂度。
   - **核心代码**：
     ```cpp
     while(m --){
         while(!q.empty () && q.top () - sum == 0){
             q.pop();
         }
         if(q.empty()){
             cout << 0 << endl;
             continue;
         }
         ans = q.top() - sum;
         sum += ans;
         cout << ans << endl;
         q.pop();
     }
     ```

【最优关键思路】
1. **排序+二分查找**：通过排序后使用二分查找来快速定位最小非零元素，适用于需要多次查找最小值的场景。
2. **懒标记（`sum`）**：在优先队列中使用 `sum` 记录累计减去的值，避免了每次操作时遍历整个数组的冗余计算。

【拓展思路】
类似的问题可以通过排序和优先队列来优化查找最小值的操作，例如在动态维护最小值的场景中，优先队列是一个常用的数据结构。

【推荐题目】
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：33.91秒