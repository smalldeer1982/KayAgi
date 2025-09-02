# 题目信息

# Non-zero Segments

## 题目描述

Kolya got an integer array $ a_1, a_2, \dots, a_n $ . The array can contain both positive and negative integers, but Kolya doesn't like $ 0 $ , so the array doesn't contain any zeros.

Kolya doesn't like that the sum of some subsegments of his array can be $ 0 $ . The subsegment is some consecutive segment of elements of the array.

You have to help Kolya and change his array in such a way that it doesn't contain any subsegments with the sum $ 0 $ . To reach this goal, you can insert any integers between any pair of adjacent elements of the array (integers can be really any: positive, negative, $ 0 $ , any by absolute value, even such a huge that they can't be represented in most standard programming languages).

Your task is to find the minimum number of integers you have to insert into Kolya's array in such a way that the resulting array doesn't contain any subsegments with the sum $ 0 $ .

## 说明/提示

Consider the first example. There is only one subsegment with the sum $ 0 $ . It starts in the second element and ends in the fourth element. It's enough to insert one element so the array doesn't contain any subsegments with the sum equal to zero. For example, it is possible to insert the integer $ 1 $ between second and third elements of the array.

There are no subsegments having sum $ 0 $ in the second example so you don't need to do anything.

## 样例 #1

### 输入

```
4
1 -5 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
4 -2 3 -9 2```

### 输出

```
0```

## 样例 #3

### 输入

```
9
-1 1 -1 1 -1 1 1 -1 -1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
16 -5 -11 -15 10 5 4 -4```

### 输出

```
3```

# AI分析结果

【题目内容】
# 非零子段

## 题目描述

Kolya 得到了一个整数数组 $ a_1, a_2, \dots, a_n $。该数组可以包含正整数和负整数，但 Kolya 不喜欢 $ 0 $，因此数组中不包含任何零。

Kolya 不喜欢的是，他的数组中某些子段的和可能为 $ 0 $。子段是指数组中连续的一段元素。

你需要帮助 Kolya 修改他的数组，使得数组中不包含任何和为 $ 0 $ 的子段。为了达到这个目标，你可以在数组的任意一对相邻元素之间插入任意整数（整数可以是任意的：正数、负数、$ 0 $，绝对值可以非常大，甚至大到无法用大多数标准编程语言表示）。

你的任务是找到需要插入到 Kolya 数组中的最小整数数量，使得最终的数组中不包含任何和为 $ 0 $ 的子段。

## 说明/提示

考虑第一个例子。只有一个子段的和为 $ 0 $。它从第二个元素开始，到第四个元素结束。只需插入一个元素，就可以使数组中不再包含任何和为 $ 0 $ 的子段。例如，可以在第二个和第三个元素之间插入整数 $ 1 $。

在第二个例子中，没有任何子段的和为 $ 0 $，因此你不需要做任何事情。

## 样例 #1

### 输入

```
4
1 -5 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
4 -2 3 -9 2```

### 输出

```
0```

## 样例 #3

### 输入

```
9
-1 1 -1 1 -1 1 1 -1 -1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
16 -5 -11 -15 10 5 4 -4```

### 输出

```
3```

【算法分类】
前缀和

【题解分析与结论】
本题的核心思路是利用前缀和来判断是否存在和为0的子段。通过维护一个哈希表（如`map`或`set`）来记录已经出现过的前缀和，当某个前缀和再次出现时，说明存在一个子段和为0，此时需要插入一个数来破坏这个子段。插入后，清空哈希表并重新开始记录前缀和。

【高星题解】
1. **作者：胖头鱼学员 (赞：9)**  
   - **星级：5**  
   - **关键亮点**：使用了前缀和和哈希表的结合，通过维护一个`map`来记录前缀和的出现位置，当发现重复前缀和时，插入一个数并清空`map`，重新开始记录。代码简洁且高效。
   - **代码核心思想**：
     ```cpp
     map<long long, long long> mp;
     for (int i = 1; i <= n; i++) {
         s += a[i];
         if (((!s && !mp[s]) || mp[s]) && mp[s] >= pos - 1) {
             ans++; 
             pos = i;
         }
         mp[s] = i;
     }
     ```

2. **作者：king_xbz (赞：7)**  
   - **星级：4**  
   - **关键亮点**：同样使用前缀和和`map`，但在发现重复前缀和时，清空`map`并重新初始化，确保后续的判断不受影响。代码实现清晰，逻辑严谨。
   - **代码核心思想**：
     ```cpp
     map <int,int>mp;
     mp[0]=1;
     for(fint i=1;i<=n;i++) {
         tot+=a[i];
         if(mp[tot]) ans++,mp.clear(),mp[0]=1,tot=a[i];
         mp[tot]++;
     }
     ```

3. **作者：zjgmartin (赞：2)**  
   - **星级：4**  
   - **关键亮点**：使用`set`来维护前缀和，当发现重复前缀和时，清空`set`并重新插入当前前缀和的前一个值，确保后续的判断不受影响。代码简洁且思路清晰。
   - **代码核心思想**：
     ```cpp
     set<ll> s;
     s.insert(0);
     for(int i=1;i<=n;i++) {
         sum+=x;
         if(s.find(sum)!=s.end()) ans++,s.clear(),s.insert(sum-x);
         s.insert(sum);
     }
     ```

【最优关键思路】
使用前缀和和哈希表（如`map`或`set`）来记录已经出现过的前缀和，当发现重复前缀和时，插入一个数并清空哈希表，重新开始记录。这种方法的时间复杂度为$O(n \log n)$，能够高效地解决问题。

【可拓展之处】
类似的问题可以通过前缀和和哈希表的结合来解决，例如判断数组中是否存在某个特定和的子段，或者统计数组中满足某种条件的子段数量。

【推荐题目】
1. P1115 最大子段和
2. P3406 海底高铁
3. P3131 [USACO16JAN]Subsequences Summing to Sevens S

【个人心得】
在调试过程中，发现初始化`map`或`set`时，需要特别注意插入初始值（如`0`），以避免漏判某些特殊情况。此外，清空哈希表后重新插入当前前缀和的前一个值，可以确保后续的判断不受影响。

---
处理用时：41.57秒