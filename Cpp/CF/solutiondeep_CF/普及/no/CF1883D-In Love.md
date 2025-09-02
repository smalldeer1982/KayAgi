# 题目信息

# In Love

## 题目描述

Initially, you have an empty multiset of segments. You need to process $ q $ operations of two types:

- $ + $ $ l $ $ r $ — Add the segment $ (l, r) $ to the multiset,
- $ - $ $ l $ $ r $ — Remove exactly one segment $ (l, r) $ from the multiset. It is guaranteed that this segment exists in the multiset.

After each operation, you need to determine if there exists a pair of segments in the multiset that do not intersect. A pair of segments $ (l, r) $ and $ (a, b) $ do not intersect if there does not exist a point $ x $ such that $ l \leq x \leq r $ and $ a \leq x \leq b $ .

## 说明/提示

In the example, after the second, third, fourth, and fifth operations, there exists a pair of segments $ (1, 2) $ and $ (3, 4) $ that do not intersect.

Then we remove exactly one segment $ (3, 4) $ , and by that time we had two segments. Therefore, the answer after this operation also exists.

## 样例 #1

### 输入

```
12
+ 1 2
+ 3 4
+ 2 3
+ 2 2
+ 3 4
- 3 4
- 3 4
- 1 2
+ 3 4
- 2 2
- 2 3
- 3 4```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
NO
YES
NO
NO
NO```

# AI分析结果

【题目内容】
# In Love

## 题目描述

初始时，你有一个空的线段多重集。你需要处理 $ q $ 次操作，操作分为两种类型：

- $ + $ $ l $ $ r $ — 将线段 $ (l, r) $ 添加到多重集中，
- $ - $ $ l $ $ r $ — 从多重集中移除一条线段 $ (l, r) $。保证该线段存在于多重集中。

每次操作后，你需要确定多重集中是否存在一对不相交的线段。两条线段 $ (l, r) $ 和 $ (a, b) $ 不相交，当且仅当不存在点 $ x $ 满足 $ l \leq x \leq r $ 且 $ a \leq x \leq b $。

## 说明/提示

在样例中，经过第二次、第三次、第四次和第五次操作后，存在一对不相交的线段 $ (1, 2) $ 和 $ (3, 4) $。

然后我们移除一条线段 $ (3, 4) $，此时多重集中有两条线段。因此，这次操作后的答案仍然是存在的。

## 样例 #1

### 输入

```
12
+ 1 2
+ 3 4
+ 2 3
+ 2 2
+ 3 4
- 3 4
- 3 4
- 1 2
+ 3 4
- 2 2
- 2 3
- 3 4```

### 输出

```
NO
YES
YES
YES
YES
YES
NO
NO
YES
NO
NO
NO```

【算法分类】
贪心、离散化

【题解分析与结论】
本题的核心在于如何高效地维护线段的多重集，并在每次操作后快速判断是否存在一对不相交的线段。大多数题解采用了贪心策略，通过维护线段的最大左端点和最小右端点来判断是否存在不相交的线段。部分题解还使用了离散化或线段树来处理大范围的线段端点。

【所选高星题解】
1. **作者：yydfj (4星)**
   - **关键亮点**：使用 `multiset` 维护线段的最大左端点和最小右端点，通过比较这两个值来判断是否存在不相交的线段。代码简洁，思路清晰。
   - **核心代码**：
     ```cpp
     if(st.size()>1)
     {
         if((*st.begin()).v>*st1.begin()) cout<<"YES\n";
         else cout<<"NO\n";
     }
     else cout<<"NO\n";
     ```

2. **作者：LiJoQiao (4星)**
   - **关键亮点**：同样使用 `multiset` 维护线段的最大左端点和最小右端点，代码结构清晰，逻辑严谨。
   - **核心代码**：
     ```cpp
     if(!sr.empty()&&!sl.empty()&&*sr.begin()<*(--it)){
         cout<<"YES\n";
     }
     else cout<<"NO\n";
     ```

3. **作者：Falling_Sakura (4星)**
   - **关键亮点**：使用 `multiset` 维护线段的最大左端点和最小右端点，代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     if(!ml.size())
     {
         cout << "NO" << endl;
     }
     else if(*(prev(ml.end())) > *mr.begin())
     {
         cout << "YES" << endl;
     }
     else
     {
         cout << "NO" << endl;
     }
     ```

【最优关键思路】
通过维护线段的最大左端点和最小右端点，判断是否存在不相交的线段。这种方法利用了贪心策略，时间复杂度较低，适合处理大规模数据。

【拓展思路】
类似的问题可以通过维护区间的最大最小值来解决，例如区间覆盖问题、区间合并问题等。可以使用线段树、树状数组等数据结构来进一步优化。

【推荐题目】
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

【个人心得】
在处理区间问题时，维护区间的最大最小值是一种常见的策略。通过使用 `multiset` 等数据结构，可以高效地实现这一目标。在实际编码中，注意删除元素时要使用 `find` 方法，避免误删所有相同值的元素。

---
处理用时：26.01秒