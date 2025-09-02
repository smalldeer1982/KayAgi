# 题目信息

# Movie Critics

## 题目描述

A film festival is coming up in the city N. The festival will last for exactly $ n $ days and each day will have a premiere of exactly one film. Each film has a genre — an integer from 1 to $ k $ .

On the $ i $ -th day the festival will show a movie of genre $ a_{i} $ . We know that a movie of each of $ k $ genres occurs in the festival programme at least once. In other words, each integer from 1 to $ k $ occurs in the sequence $ a_{1},a_{2},...,a_{n} $ at least once.

Valentine is a movie critic. He wants to watch some movies of the festival and then describe his impressions on his site.

As any creative person, Valentine is very susceptive. After he watched the movie of a certain genre, Valentine forms the mood he preserves until he watches the next movie. If the genre of the next movie is the same, it does not change Valentine's mood. If the genres are different, Valentine's mood changes according to the new genre and Valentine has a stress.

Valentine can't watch all $ n $ movies, so he decided to exclude from his to-watch list movies of one of the genres. In other words, Valentine is going to choose exactly one of the $ k $ genres and will skip all the movies of this genre. He is sure to visit other movies.

Valentine wants to choose such genre $ x $ ( $ 1<=x<=k $ ), that the total number of after-movie stresses (after all movies of genre $ x $ are excluded) were minimum.

## 说明/提示

In the first sample if we exclude the movies of the 1st genre, the genres $ 2,3,2,3,3,3 $ remain, that is 3 stresses; if we exclude the movies of the 2nd genre, the genres $ 1,1,3,3,3,1,1,3 $ remain, that is 3 stresses; if we exclude the movies of the 3rd genre the genres $ 1,1,2,2,1,1 $ remain, that is 2 stresses.

In the second sample whatever genre Valentine excludes, he will have exactly 3 stresses.

## 样例 #1

### 输入

```
10 3
1 1 2 3 2 3 3 1 1 3
```

### 输出

```
3```

## 样例 #2

### 输入

```
7 3
3 1 3 2 3 1 2
```

### 输出

```
1```

# AI分析结果



# Movie Critics

## 题目描述

在N市即将举办电影节，持续恰好$n$天，每天放映一部电影。每部电影属于一个类型（1到$k$的整数）。已知每个类型至少出现一次。影评人Valentine希望排除某一类型的所有电影，使得剩余电影相邻类型变化的次数最少。求应排除的类型编号（若有多个答案输出最小的）。

## 算法分类
贪心

---

## 题解对比与结论

### 各题解核心思路
1. **预处理去重**：将连续相同类型的电影合并，得到相邻元素不同的压缩序列。
2. **贡献统计**：对每个类型$x$，统计删除该类型后能减少的压力次数。关键点在于：
   - 若某类型$x$的某个位置在压缩序列中前后类型相同，删除$x$将合并前后段，贡献+2。
   - 否则贡献+1。
3. **贪心选择**：选择总贡献最大的类型，压力次数减少最多。

### 最优题解亮点
1. **洛璟的题解（4星）**
   - 亮点：通过两次遍历统计类型出现次数和相邻关系，代码简洁高效。
   - 关键代码：
     ```cpp
     // 去重后统计出现次数
     if (a[i] != a[i - 1]) {
         b[++cnt] = a[i];
         sum[a[i]]++;
     }
     // 处理相邻关系
     if (b[i - 1] == b[i + 1]) sum[b[i]]++;
     ```
   
2. **alan1118的题解（4星）**
   - 亮点：逻辑清晰，直接统计每个位置的贡献，最终计算最大减幅。
   - 关键代码：
     ```cpp
     for(int i=1; i<=cur; i++) {
         c[b[i]]++;
         if(b[i-1] == b[i+1]) c[b[i]]++;
     }
     ```

---

## 关键思路
1. **去重压缩**：消除连续重复元素，简化问题为相邻不同的序列。
2. **贡献分析**：每个类型$x$的删除贡献由其出现位置的前后关系决定，利用贪心选择最优解。
3. **高效统计**：两次遍历分别统计出现次数和相邻关系，时间复杂度$O(n)$。

---

## 类似题目推荐
1. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)  
   （二维滑动窗口，需分解问题）
2. [CF1175E Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E)  
   （贪心选择覆盖区间）
3. [P3419 股票](https://www.luogu.com.cn/problem/P3419)  
   （贪心选择删除策略）

---

## 个人心得摘录
- **去重预处理**：连续相同元素的合并能显著简化问题，是常见技巧。
- **贡献计算陷阱**：需注意数组越界问题（如首尾元素的相邻判断），可通过条件判断规避。
- **贪心正确性**：正确性的核心在于贡献计算的数学证明，需通过样例验证逻辑。

---
处理用时：262.94秒