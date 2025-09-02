# 题目信息

# Fixed Point Guessing

## 题目描述

This is an interactive problem.

Initially, there is an array $ a = [1, 2, \ldots, n] $ , where $ n $ is an odd positive integer. The jury has selected $ \frac{n-1}{2} $ disjoint pairs of elements, and then the elements in those pairs are swapped. For example, if $ a=[1,2,3,4,5] $ , and the pairs $ 1 \leftrightarrow 4 $ and $ 3 \leftrightarrow 5 $ are swapped, then the resulting array is $ [4, 2, 5, 1, 3] $ .

As a result of these swaps, exactly one element will not change position. You need to find this element.

To do this, you can ask several queries. In each query, you can pick two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ). In return, you will be given the elements of the subarray $ [a_l, a_{l + 1}, \dots, a_r] $ sorted in increasing order.

Find the element which did not change position. You can make at most $ \mathbf{15} $ queries.

The array $ a $ is fixed before the interaction and does not change after your queries.

Recall that an array $ b $ is a subarray of the array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first test, the interaction proceeds as follows.

 SolutionJuryExplanation $ \texttt{2} $ There are 2 test cases. $ \texttt{5} $ In the first test case, the hidden array is $ [4,2,5,1,3] $ , with length $ 5 $ . $ \texttt{? 1 4} $  $ \texttt{1 2 4 5} $ The solution requests the subarray $ [4,2,5,1] $ in increasing order, and the jury responds with $ [1,2,4,5] $ . $ \texttt{? 3 5} $  $ \texttt{1 3 5} $ The solution requests the subarray $ [5,1,3] $ in increasing order, and the jury responds with $ [1,3,5] $ . $ \texttt{! 2} $ The solution has somehow determined that $ a_2=2 $ , and outputs it. Since the output is correct, the jury continues to the next test case. $ \texttt{3} $ In the second test case, the hidden array is $ [1,3,2] $ , with length $ 3 $ . $ \texttt{? 1 1} $  $ \texttt{1} $ The solution requests the number $ [1] $ only, and the jury responds with $ [1] $ . $ \texttt{! 1} $ The solution has determined that $ a_1=1 $ , and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
5

1 2 4 5

1 3 5

3

1```

### 输出

```
? 1 4

? 3 5

! 2

? 1 1

! 1```

# AI分析结果

### 题目内容重写
# 固定点猜测

## 题目描述

这是一个交互题。

初始时，有一个数组 $ a = [1, 2, \ldots, n] $ ，其中 $ n $ 是一个奇正整数。裁判选择了 $ \frac{n-1}{2} $ 个不相交的元素对，然后交换这些对中的元素。例如，如果 $ a=[1,2,3,4,5] $ ，并且交换了 $ 1 \leftrightarrow 4 $ 和 $ 3 \leftrightarrow 5 $ ，那么结果数组是 $ [4, 2, 5, 1, 3] $ 。

由于这些交换，恰好有一个元素不会改变位置。你需要找到这个元素。

为此，你可以进行多次查询。在每次查询中，你可以选择两个整数 $ l $ 和 $ r $ （ $ 1 \leq l \leq r \leq n $ ）。作为回应，你将得到子数组 $ [a_l, a_{l + 1}, \dots, a_r] $ 按升序排序后的结果。

找到没有改变位置的元素。你最多可以进行 $ \mathbf{15} $ 次查询。

数组 $ a $ 在交互之前是固定的，并且在你的查询后不会改变。

回想一下，数组 $ b $ 是数组 $ a $ 的子数组，如果 $ b $ 可以通过从 $ a $ 的开头删除若干个（可能是零个或全部）元素，并从 $ a $ 的末尾删除若干个（可能是零个或全部）元素来获得。

## 说明/提示

在第一个测试中，交互过程如下。

 解决方案裁判解释 $ \texttt{2} $ 有 2 个测试用例。 $ \texttt{5} $ 在第一个测试用例中，隐藏的数组是 $ [4,2,5,1,3] $ ，长度为 $ 5 $ 。 $ \texttt{? 1 4} $  $ \texttt{1 2 4 5} $ 解决方案请求子数组 $ [4,2,5,1] $ 按升序排序，裁判回应 $ [1,2,4,5] $ 。 $ \texttt{? 3 5} $  $ \texttt{1 3 5} $ 解决方案请求子数组 $ [5,1,3] $ 按升序排序，裁判回应 $ [1,3,5] $ 。 $ \texttt{! 2} $ 解决方案已经确定 $ a_2=2 $ ，并输出它。由于输出正确，裁判继续到下一个测试用例。 $ \texttt{3} $ 在第二个测试用例中，隐藏的数组是 $ [1,3,2] $ ，长度为 $ 3 $ 。 $ \texttt{? 1 1} $  $ \texttt{1} $ 解决方案只请求数字 $ [1] $ ，裁判回应 $ [1] $ 。 $ \texttt{! 1} $ 解决方案已经确定 $ a_1=1 $ ，并输出它。由于输出正确且没有更多测试用例，裁判和解决方案退出。请注意，示例输入和输出中的换行符是为了清晰起见，在实际交互中不会出现。

## 样例 #1

### 输入

```
2
5

1 2 4 5

1 3 5

3

1```

### 输出

```
? 1 4

? 3 5

! 2

? 1 1

! 1```

### 算法分类
二分

### 题解分析与结论
所有题解都采用了二分查找的思路，核心思想是通过查询子数组并统计其中值在区间内的元素个数，利用奇偶性判断固定点是否在当前区间内。具体实现上，各题解在细节处理上有所不同，但整体思路一致。

### 精选题解
1. **作者：bmatrix (5星)**
   - **关键亮点**：思路清晰，代码简洁，直接利用二分法缩小范围，通过统计区间内元素个数的奇偶性判断固定点位置。
   - **代码核心**：
     ```cpp
     int l = 1, r = n;
     do {
         int mid = (l + r) / 2;
         cout << "? " << l << ' ' << mid << endl;
         int cnt = 0, x;
         for(int i = l; i <= mid; ++i) {
             cin >> x;
             if(x >= l && x <= mid) ++cnt;
         }
         if(cnt & 1) r = mid;
         else l = mid + 1;
     } while(r > l);
     cout << "! " << l << endl;
     ```

2. **作者：Super_Cube (4星)**
   - **关键亮点**：逻辑严谨，通过判断区间内元素个数的奇偶性来确定固定点位置，代码实现简洁。
   - **代码核心**：
     ```cpp
     int l = 1, r = n;
     while(l <= r) {
         int mid = l + r >> 1, cnt = 0;
         printf("? 1 %d\n", mid);
         for(int i = 1, x; i <= mid; ++i) {
             scanf("%d", &x);
             cnt ^= (x <= mid);
         }
         if(cnt & 1) ans = mid, r = mid - 1;
         else l = mid + 1;
     }
     printf("! %d\n", ans);
     ```

3. **作者：LRL65 (4星)**
   - **关键亮点**：通过二分法逐步缩小范围，利用奇偶性判断固定点位置，代码实现简洁明了。
   - **代码核心**：
     ```cpp
     int l = 1, r = n;
     while(l < r) { 
         int mid = (l + r) >> 1;
         cout << "? " << l << " " << mid << endl;
         int cnt = 0;
         for(int i = l; i <= mid; i++) {
             cin >> x;
             if(x >= l && x <= mid) cnt++;
         } 
         if(cnt % 2 == 1) r = mid;
         else l = mid + 1;
     }
     cout << "! " << l << endl;
     ```

### 最优关键思路
利用二分法逐步缩小固定点的范围，通过统计区间内元素个数的奇偶性来判断固定点是否在当前区间内。这一思路充分利用了交互题的特性，且时间复杂度较低。

### 拓展思路
类似的问题可以通过二分法结合奇偶性判断来解决，尤其是在需要快速缩小范围的情况下。例如，在查找唯一元素或判断某个条件是否满足时，二分法结合奇偶性判断是一种高效的策略。

### 推荐题目
1. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

---
处理用时：46.70秒