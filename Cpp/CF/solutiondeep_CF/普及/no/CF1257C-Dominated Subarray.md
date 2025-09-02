# 题目信息

# Dominated Subarray

## 题目描述

Let's call an array $ t $ dominated by value $ v $ in the next situation.

At first, array $ t $ should have at least $ 2 $ elements. Now, let's calculate number of occurrences of each number $ num $ in $ t $ and define it as $ occ(num) $ . Then $ t $ is dominated (by $ v $ ) if (and only if) $ occ(v) > occ(v') $ for any other number $ v' $ . For example, arrays $ [1, 2, 3, 4, 5, 2] $ , $ [11, 11] $ and $ [3, 2, 3, 2, 3] $ are dominated (by $ 2 $ , $ 11 $ and $ 3 $ respectevitely) but arrays $ [3] $ , $ [1, 2] $ and $ [3, 3, 2, 2, 1] $ are not.

Small remark: since any array can be dominated only by one number, we can not specify this number and just say that array is either dominated or not.

You are given array $ a_1, a_2, \dots, a_n $ . Calculate its shortest dominated subarray or say that there are no such subarrays.

The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ .

## 说明/提示

In the first test case, there are no subarrays of length at least $ 2 $ , so the answer is $ -1 $ .

In the second test case, the whole array is dominated (by $ 1 $ ) and it's the only dominated subarray.

In the third test case, the subarray $ a_4, a_5, a_6 $ is the shortest dominated subarray.

In the fourth test case, all subarrays of length more than one are dominated.

## 样例 #1

### 输入

```
4
1
1
6
1 2 3 4 5 1
9
4 1 2 4 5 4 3 2 1
4
3 3 3 3
```

### 输出

```
-1
6
3
2
```

# AI分析结果

### 题目内容重写
# 被支配的子数组

## 题目描述

我们称一个数组 $t$ 被值 $v$ 支配，当且仅当满足以下条件：

首先，数组 $t$ 至少要有 $2$ 个元素。然后，我们计算数组中每个数字 $num$ 的出现次数，记为 $occ(num)$。如果 $occ(v) > occ(v')$ 对于任何其他数字 $v'$ 都成立，那么 $t$ 被 $v$ 支配。例如，数组 $[1, 2, 3, 4, 5, 2]$、$[11, 11]$ 和 $[3, 2, 3, 2, 3]$ 分别被 $2$、$11$ 和 $3$ 支配，但数组 $[3]$、$[1, 2]$ 和 $[3, 3, 2, 2, 1]$ 不被支配。

注意：由于任何数组只能被一个数字支配，我们可以不指定这个数字，直接说数组是否被支配。

给定数组 $a_1, a_2, \dots, a_n$，计算其最短的被支配子数组，或者说明不存在这样的子数组。

子数组是数组 $a$ 的连续部分，即数组 $a_i, a_{i + 1}, \dots, a_j$，其中 $1 \le i \le j \le n$。

## 说明/提示

在第一个测试用例中，没有长度至少为 $2$ 的子数组，所以答案是 $-1$。

在第二个测试用例中，整个数组被 $1$ 支配，且这是唯一的被支配子数组。

在第三个测试用例中，子数组 $a_4, a_5, a_6$ 是最短的被支配子数组。

在第四个测试用例中，所有长度大于 $1$ 的子数组都被支配。

## 样例 #1

### 输入

```
4
1
1
6
1 2 3 4 5 1
9
4 1 2 4 5 4 3 2 1
4
3 3 3 3
```

### 输出

```
-1
6
3
2
```

### 算法分类
贪心

### 题解分析与结论
本题的核心是寻找最短的被支配子数组，即子数组中有且仅有一个众数，且该众数的出现次数大于其他任何数字的出现次数。大多数题解都采用了贪心的思路，通过记录每个数字上一次出现的位置，并在遍历数组时更新最短子数组的长度。

### 所选高星题解
1. **作者：B_Qu1e7 (4星)**
   - **关键亮点**：通过记录每个数字上一次出现的位置，并在遍历时更新最短子数组的长度，思路清晰且代码简洁。
   - **代码核心**：
     ```cpp
     int pre[200005]={0},ans=998244353;
     for(R int i=1; i<=N; ++i) {
         read(A[i]);
         if(pre[A[i]] && i-pre[A[i]]+1<ans) {
             ans=i-pre[A[i]]+1;
         }
         pre[A[i]]=i;
     }
     printf("%d\n",ans==998244353?-1:ans);
     ```

2. **作者：Wind_love (4星)**
   - **关键亮点**：通过记录每个数字上一次出现的位置，并在遍历时更新最短子数组的长度，代码简洁且易于理解。
   - **代码核心**：
     ```cpp
     int ans=1e9;
     for(int i=1;i<=n;i++) {
         cin>>a[i];
         if(las[a[i]]) ans=min(i-las[a[i]]+1,ans);
         las[a[i]]=i;
     }
     if(ans==1e9) ans=-1;
     cout<<ans<<"\n";
     ```

3. **作者：lyzhsxx (4星)**
   - **关键亮点**：通过使用 `map` 记录每个数字上一次出现的位置，并在遍历时更新最短子数组的长度，思路清晰且代码简洁。
   - **代码核心**：
     ```cpp
     map<int,int> mp;
     int ans=INT_MAX;
     for(int i=1;i<=n;i++) {
         if(mp[a[i]]==0) mp[a[i]]=i;
         else {
             ans=min(ans,i+1-mp[a[i]]);
             mp[a[i]]=i;
         }
     }
     if(ans!=INT_MAX) cout<<ans<<endl;
     else cout<<-1<<endl;
     ```

### 最优关键思路
通过记录每个数字上一次出现的位置，并在遍历数组时更新最短子数组的长度，这种方法的时间复杂度为 $O(n)$，空间复杂度为 $O(n)$，是一种高效的解决方案。

### 可拓展之处
类似的问题可以通过记录数字的出现位置来解决，例如查找最短的连续子数组满足某些特定条件（如子数组中的元素和等于某个值）。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
3. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)

---
处理用时：36.10秒