# 题目信息

# [ICPC 2022 Jinan R] Stack Sort

## 题目描述

You are given a permutation with $n$ numbers, $a_1, a_2, \dots, a_n (1\leq a_i\leq n, a_i\neq a_j\textrm{ when }i\neq j)$. 

You want to sort these numbers using $m$ stacks. Specifically, you should complete the following task: 

Initially, all stacks are empty. You need to push each number $a_i$ to the top of one of the $m$ stacks one by one, in the order of $a_1,a_2,\ldots, a_n$. $\textbf{After pushing all numbers in the stacks}$, you pop all the elements from the stacks in a clever order so that the first number you pop is $1$, the second number you pop is $2$, and so on. **If you pop an element from a stack $S$, you cannot pop any element from the other stacks until $S$ becomes empty.**

What is the minimum possible $m$ to complete the task?

## 样例 #1

### 输入

```
3
3
1 2 3
3
3 2 1
5
1 4 2 5 3
```

### 输出

```
3
1
4```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心逻辑是通过贪心策略来确定最小栈数。所有题解的共同思路是：在遍历数组时，若当前元素的下一个元素（即 `a[i]+1`）未被标记为已入栈，则需要增加一个栈。这种策略确保了每个栈中的元素是连续的，从而满足出栈顺序的要求。

### 所选高星题解
1. **作者：佬头 (5星)**
   - **关键亮点**：思路清晰，代码简洁，时间复杂度为 O(Tn)，适合大规模数据处理。
   - **核心代码**：
     ```cpp
     for(int i = 1; i <= n; ++ i){
         int a = read();
         if(!vis[a]) ++ ans;
         vis[a - 1] = 1;
     }
     ```
   - **实现思想**：通过 `vis` 数组标记已入栈的元素，若 `a[i]` 未被标记，则增加栈数，并标记 `a[i]-1` 为已入栈。

2. **作者：Hughpig (4星)**
   - **关键亮点**：逻辑清晰，代码易读，时间复杂度为 O(n)。
   - **核心代码**：
     ```cpp
     for(int i = 1; i <= n; i++){
         if(vis[a[i]]){if(!vis[a[i]-1])vis[a[i]-1]=1;}
         else{
             ans++, vis[a[i]]=1;
             if(!vis[a[i]-1])vis[a[i]-1]=1;
         }
     }
     ```
   - **实现思想**：通过 `vis` 数组标记已入栈的元素，若 `a[i]` 未被标记，则增加栈数，并标记 `a[i]-1` 为已入栈。

3. **作者：tiger2008 (4星)**
   - **关键亮点**：思路简洁，代码易读，时间复杂度为 O(n)。
   - **核心代码**：
     ```cpp
     for(int i = 1; i <= n; i++){
         ans+=(!f[arr[i]]);
         f[arr[i]-1]=true;
     }
     ```
   - **实现思想**：通过 `f` 数组标记已入栈的元素，若 `a[i]` 未被标记，则增加栈数，并标记 `a[i]-1` 为已入栈。

### 最优关键思路或技巧
- **贪心策略**：在遍历数组时，若当前元素的下一个元素未被标记为已入栈，则需要增加一个栈。这种策略确保了每个栈中的元素是连续的，从而满足出栈顺序的要求。
- **标记数组**：使用一个布尔数组来标记已入栈的元素，避免重复计算。

### 可拓展之处
- **类似问题**：类似的问题可以出现在需要维护连续序列的场景中，如区间覆盖、任务调度等。
- **算法套路**：贪心算法在处理最小化或最大化问题时，常常通过局部最优解来达到全局最优解。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录
- **调试经历**：在实现过程中，确保标记数组的正确更新是关键，避免重复计算或遗漏。
- **顿悟感想**：通过贪心策略，可以有效地减少栈的数量，确保出栈顺序的正确性。

---
处理用时：25.55秒