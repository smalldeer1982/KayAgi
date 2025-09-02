# 题目信息

# Odd Subarrays

## 题目描述

For an array $ [b_1, b_2, \ldots, b_m] $ define its number of inversions as the number of pairs $ (i, j) $ of integers such that $ 1 \le i < j \le m $ and $ b_i>b_j $ . Let's call array $ b $ odd if its number of inversions is odd.

For example, array $ [4, 2, 7] $ is odd, as its number of inversions is $ 1 $ , while array $ [2, 1, 4, 3] $ isn't, as its number of inversions is $ 2 $ .

You are given a permutation $ [p_1, p_2, \ldots, p_n] $ of integers from $ 1 $ to $ n $ (each of them appears exactly once in the permutation). You want to split it into several consecutive subarrays (maybe just one), so that the number of the odd subarrays among them is as large as possible.

What largest number of these subarrays may be odd?

## 说明/提示

In the first and third test cases, no matter how we split our permutation, there won't be any odd subarrays.

In the second test case, we can split our permutation into subarrays $ [4, 3], [2, 1] $ , both of which are odd since their numbers of inversions are $ 1 $ .

In the fourth test case, we can split our permutation into a single subarray $ [2, 1] $ , which is odd.

In the fifth test case, we can split our permutation into subarrays $ [4, 5], [6, 1, 2, 3] $ . The first subarray has $ 0 $ inversions, and the second has $ 3 $ , so it is odd.

## 样例 #1

### 输入

```
5
3
1 2 3
4
4 3 2 1
2
1 2
2
2 1
6
4 5 6 1 2 3```

### 输出

```
0
2
0
1
1```

# AI分析结果

### 题目内容
# 奇数子数组

## 题目描述
对于数组$ [b_1, b_2, \ldots, b_m] $ ，将其逆序对的数量定义为满足 $ 1 \le i < j \le m $ 且 $ b_i>b_j $ 的整数对 $ (i, j) $ 的数量。我们称数组 $ b $ 为奇数数组，如果其逆序对的数量为奇数。

例如，数组 $ [4, 2, 7] $ 是奇数数组，因为其逆序对数量为 $ 1 $ ，而数组 $ [2, 1, 4, 3] $ 不是，因为其逆序对数量为 $ 2 $ 。

给定一个从 $ 1 $ 到 $ n $ 的整数排列 $ [p_1, p_2, \ldots, p_n] $ （每个数在排列中恰好出现一次）。你想要将它分成几个连续的子数组（也可能只有一个），使得其中奇数子数组的数量尽可能多。

这些子数组中奇数子数组的最大数量是多少？

## 说明/提示
在第一个和第三个测试用例中，无论我们如何划分排列，都不会有奇数子数组。

在第二个测试用例中，我们可以将排列划分为子数组 $ [4, 3], [2, 1] $ ，这两个子数组都是奇数数组，因为它们的逆序对数量都是 $ 1 $ 。

在第四个测试用例中，我们可以将排列划分为单个子数组 $ [2, 1] $ ，它是奇数数组。

在第五个测试用例中，我们可以将排列划分为子数组 $ [4, 5], [6, 1, 2, 3] $ 。第一个子数组有 $ 0 $ 个逆序对，第二个有 $ 3 $ 个，所以第二个是奇数数组。

## 样例 #1
### 输入
```
5
3
1 2 3
4
4 3 2 1
2
1 2
2
2 1
6
4 5 6 1 2 3
```
### 输出
```
0
2
0
1
1
```
### 算法分类
贪心
### 综合分析与结论
这几道题解的核心思路都是基于贪心策略。大家都意识到要使逆序对为奇数的子数组数量最多，关键在于如何组合相邻元素。
1. **思路**：多数题解先考虑将序列中的每个数单独成段，然后分析如何合并相邻段。发现当 $ b_i > b_{i + 1} $ 时，将这两个数组合成一个序列能增加奇数序列数，且保证剩余序列数较多，从而整体上使奇数子数组数量最多。
2. **算法要点**：遍历数组，判断相邻元素大小关系，若前一个数大于后一个数，则将它们合并为一个奇数子数组，并跳过下一个元素防止重复配对，同时统计奇数子数组的数量。
3. **解决难点**：难点在于证明这种贪心策略的正确性。通过分析可知，对于任何一个数 $ a_i $ 及最小满足 $ a_j < a_i $ 的 $ j $ ，将区间进一步划分后，总能得到一个逆序对数为奇数的子序列，所以按此贪心策略划分能得到最优解。

### 所选的题解
- **作者：skyskyCCC（4星）**
  - **关键亮点**：思路清晰，逐步分析，从理解题意到提出贪心策略，再到代码实现，逻辑连贯。详细解释了每一步的思考过程，便于理解。
  - **重点代码核心思想**：遍历数组，当当前元素小于前一个元素时，认为形成一个奇数子数组，记录并跳过下一个元素。
  ```cpp
  while(t--){
      cin>>n;
      sum=0;
      for(int i=1;i<=n;i++){
          cin>>a[i];
          if(a[i]<a[i-1]){
              sum++;
              if(i<n){
                  cin>>a[i+1];
              }
              i++;
          }
      }
      tot++;
      ans[tot]=sum;
  }
  ```
- **作者：windflower（4星）**
  - **关键亮点**：对贪心策略的原理阐述清晰，通过分析区间划分的方式，证明了贪心策略的正确性。代码简洁明了，直接实现了核心逻辑。
  - **重点代码核心思想**：遍历数组，判断相邻元素大小，若前一个数大于后一个数，奇数子数组数量加一，并跳过下一个元素。
  ```cpp
  while(t--){
      cin>>n;
      ans=0;
      for(int i=0;i<n;i++)cin>>p[i];
      for(int i=0;i<n-1;i++){
          if(p[i]>p[i+1]){
              ans++;
              i++;
          }
      }
      cout<<ans<<endl;
  }
  ```
- **作者：zyl1543130456（4星）**
  - **关键亮点**：简洁地阐述了题意和解题思路，先将每个数单独成段，再通过贪心合并相邻元素形成奇数子数组，代码实现与思路紧密结合。
  - **重点代码核心思想**：遍历数组，当当前元素小于前一个元素时，奇数子数组数量加一，并跳过下一个元素。
  ```cpp
  while(t--){
      int ans=0;
      scanf("%d",&n);
      for(int i=1;i<=n;i++){
          scanf("%d",&a[i]);
          if(a[i]<a[i-1]){
              ans+=1;
              if(i<n)scanf("%d",&a[i+1]);
              i+=1;
          }
      }
      printf("%d\n",ans);
  }
  ```
### 最优关键思路或技巧
1. **思维方式**：采用贪心策略，从局部最优（相邻元素组合形成奇数子数组）达到全局最优（奇数子数组数量最多）。通过分析数组元素间的逆序对关系，发现当相邻元素前大后小时组合能增加奇数子数组数量。
2. **代码实现技巧**：在遍历数组判断相邻元素关系时，通过跳过下一个元素来避免重复配对，简洁有效地实现了贪心策略。
### 拓展
1. **同类型题或类似算法套路**：这类题目通常围绕数组元素的某种特性（如本题的逆序对数量奇偶性），通过合理划分或组合元素来达到某个最优目标。类似算法套路是先分析局部元素间的关系对目标的影响，然后基于此采用贪心策略，每次选择局部最优的操作，最终得到全局最优解。
2. **推荐洛谷题目**
  - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组物品，使分组数量最少，考察贪心策略。
  - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：根据武将武力值关系，采用贪心策略选择最优方案，与本题分析元素关系并贪心选择思路类似。
  - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过对奶牛产奶模式的分析，利用贪心等策略解决问题，同样是对序列元素特性进行分析处理。
### 个人心得摘录与总结
无。 

---
处理用时：49.31秒