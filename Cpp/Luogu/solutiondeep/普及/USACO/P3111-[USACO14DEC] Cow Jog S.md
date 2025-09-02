# 题目信息

# [USACO14DEC] Cow Jog S

## 题目描述

 

The cows are out exercising their hooves again!  There are N cows

jogging on an infinitely-long single-lane track (1 <= N <= 100,000).

Each cow starts at a distinct position on the track, and some cows jog

at different speeds.


 

With only one lane in the track, cows cannot pass each other.  When a

faster cow catches up to another cow, she has to slow down to avoid

running into the other cow, becoming part of the same running group.

 

The cows will run for T minutes (1 <= T <= 1,000,000,000).  Please

help Farmer John determine how many groups will be left at this time.

Two cows should be considered part of the same group if they are at


the same position at the end of T minutes. 

有N (1 <= N <= 100,000)头奶牛在一个单人的超长跑道上慢跑，每头牛的起点位置都不同。由于是单人跑道，所有他们之间不能相互超越。当一头速度快的奶牛追上另外一头奶牛的时候，他必须降速成同等速度。我们把这些跑走同一个位置而且同等速度的牛看成一个小组。


请计算T (1 <= T <= 1,000,000,000)时间后，奶牛们将分为多少小组。



## 样例 #1

### 输入

```
5 3 
0 1 
1 2 
2 3 
3 2 
6 1 

 

```

### 输出

```
 

3 

 
```

# AI分析结果



### 综合分析与结论

题目核心在于判断奶牛在T时间后是否因无法超越而合并成组。各题解普遍采用以下思路：计算每头牛的最终位置（位置+速度×时间），并从右向左遍历，维护当前最小组的末尾位置。若当前牛的最终位置≥末尾位置，则合并；否则形成新组。这种方法的时间复杂度为O(n)，能高效处理大数据。

### 精选题解与评分

1. **作者：NewErA（★★★★★）**  
   **关键亮点**：思路清晰，代码简洁高效。正确计算最终位置后逆向处理，直接维护最小值。  
   **代码核心**：
   ```cpp
   for(int i = n-1; i >= 1; i--) {
       if (last[i] >= last[i+1]) last[i] = last[i+1];
       else res++;
   }
   ```

2. **作者：曹老师（★★★★☆）**  
   **关键亮点**：逻辑明确，代码结构规范，变量命名清晰。使用逆向扫描维护最小值。  
   **代码核心**：
   ```cpp
   for (int i = n-1; i >= 1; i--) {
       if (val[i] >= val[i+1]) val[i] = val[i+1];
       else ans++;
   }
   ```

3. **作者：Tarsal（★★★★☆）**  
   **关键亮点**：代码可读性高，注释详细。逆向遍历时动态更新末尾位置，正确统计组数。  
   **代码核心**：
   ```cpp
   for (int i = n-1; i >= 1; --i) {
       if (last[i] >= last[i+1]) last[i] = last[i+1];
       else ++ans;
   }
   ```

### 最优思路总结

1. **最终位置计算**：每头牛的最终位置为 `pos + speed * T`。  
2. **逆向处理**：从右向左遍历，维护当前最小组的末尾位置。若当前牛的位置≥末尾，则合并（更新末尾）；否则新增组。  
3. **贪心思想**：只需比较相邻牛的最终位置，无需模拟合并过程，保证线性复杂度。

### 拓展与同类题目

- **类似题目套路**：区间合并、车队问题（LeetCode 853）、单调栈维护有序序列。  
- **举一反三**：当问题涉及“后效性”或“动态更新最值”时，可考虑逆向处理或贪心策略。

### 推荐题目

1. [P3143 [USACO16OPEN] Diamond Collector S](https://www.luogu.com.cn/problem/P3143)  
2. [P2862 [USACO06JAN] Corral the Cows G](https://www.luogu.com.cn/problem/P2862)  
3. [LeetCode 853. Car Fleet](https://leetcode.com/problems/car-fleet/)（与本题思路高度相似）

### 题解中的个人心得

- **Limerick的题解**中提到需按初始位置排序，但原题输入已保证升序，无需额外排序。  
  **教训**：仔细审题，明确输入条件，避免不必要的操作。  
- **OIer991215的题解**采用O(n²)暴力，虽过样例但无法通过大数据。  
  **启示**：优先考虑时间复杂度，尤其面对1e5级数据时需选择线性算法。

---
处理用时：123.71秒