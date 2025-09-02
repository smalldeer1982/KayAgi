# 题目信息

# Johnny and His Hobbies

## 题目描述

Among Johnny's numerous hobbies, there are two seemingly harmless ones: applying bitwise operations and sneaking into his dad's office. As it is usually the case with small children, Johnny is unaware that combining these two activities can get him in a lot of trouble.

There is a set $ S $ containing very important numbers on his dad's desk. The minute Johnny heard about it, he decided that it's a good idea to choose a positive integer $ k $ and replace each element $ s $ of the set $ S $ with $ s \oplus k $ ( $ \oplus $ denotes the [exclusive or](https://en.wikipedia.org/wiki/Exclusive_or#Computer_science) operation).

Help him choose such $ k $ that Johnny's dad will not see any difference after his son is done playing (i.e. Johnny will get the same set as before playing). It is possible that no such number exists. It is also possible that there are many of them. In such a case, output the smallest one. Note that the order of elements in a set doesn't matter, i.e. set $ \{1, 2, 3\} $ equals to set $ \{2, 1, 3\} $ .

Formally, find the smallest positive integer $ k $ such that $ \{s \oplus k | s \in S\} = S $ or report that there is no such number.

For example, if $ S = \{1, 3, 4\} $ and $ k = 2 $ , new set will be equal to $ \{3, 1, 6\} $ . If $ S = \{0, 1, 2, 3\} $ and $ k = 1 $ , after playing set will stay the same.

## 说明/提示

In the first test case, the answer is $ 1 $ because it is a minimum positive integer and it satisfies all the conditions.

## 样例 #1

### 输入

```
6
4
1 0 2 3
6
10 7 14 8 3 12
2
0 2
3
1 2 3
6
1 4 6 10 11 12
2
0 1023```

### 输出

```
1
4
2
-1
-1
1023```

# AI分析结果

### 题目内容重写
# Johnny 和他的爱好

## 题目描述

在 Johnny 的众多爱好中，有两个看似无害的爱好：应用位运算和偷偷溜进他爸爸的办公室。就像通常小孩子的情况一样，Johnny 并不知道将这两个活动结合起来会给他带来很多麻烦。

他爸爸的桌子上有一个包含重要数字的集合 $S$。Johnny 一听说这件事，就决定选择一个正整数 $k$，并将集合 $S$ 中的每个元素 $s$ 替换为 $s \oplus k$（$\oplus$ 表示[异或](https://en.wikipedia.org/wiki/Exclusive_or#Computer_science)操作）。

请帮助他选择这样的 $k$，使得 Johnny 的爸爸在他玩完后看不到任何变化（即 Johnny 得到的集合与之前相同）。可能不存在这样的数字，也可能存在多个。在这种情况下，输出最小的那个。注意，集合中元素的顺序无关紧要，即集合 $\{1, 2, 3\}$ 等于集合 $\{2, 1, 3\}$。

形式化地说，找到最小的正整数 $k$，使得 $\{s \oplus k | s \in S\} = S$，或者报告不存在这样的数字。

例如，如果 $S = \{1, 3, 4\}$ 且 $k = 2$，则新集合将等于 $\{3, 1, 6\}$。如果 $S = \{0, 1, 2, 3\}$ 且 $k = 1$，则玩完后集合保持不变。

## 说明/提示

在第一个测试用例中，答案是 $1$，因为它是最小的正整数，并且满足所有条件。

## 样例 #1

### 输入

```
6
4
1 0 2 3
6
10 7 14 8 3 12
2
0 2
3
1 2 3
6
1 4 6 10 11 12
2
0 1023
```

### 输出

```
1
4
2
-1
-1
1023
```

### 算法分类
位运算、枚举

### 题解分析与结论
本题的核心是通过枚举 $k$ 并检查异或操作后的集合是否与原集合相同。由于数据范围较小（$k \leq 1024$），暴力枚举是可行的。大多数题解都采用了这一思路，通过排序后比较集合元素来判断是否满足条件。

### 评分较高的题解
1. **作者：Jsxts_**
   - **星级：4**
   - **关键亮点**：通过记录初始集合中每个数的个数，并在枚举 $k$ 时更新这些计数，最后判断是否所有计数都为零。这种方法避免了多次排序，提高了效率。
   - **代码核心**：
     ```cpp
     for (int i = 1;i <= 1024;i ++ ) {
         for (int j = 1;j <= n;j ++ ) a[j] ^= i, c[a[j]] --;
         for (int j = 0;j <= mx;j ++ ) {
             if (c[j]) goto bre;
         }
         printf("%d\n",i);
         goto bre2;
         bre:;
         for (int j = 1;j <= n;j ++ ) c[a[j]] ++, a[j] ^= i;
     }
     ```

2. **作者：ShineEternal**
   - **星级：4**
   - **关键亮点**：在输入时预处理所有可能的异或结果，并在枚举 $k$ 时直接使用这些结果进行比较，减少了重复计算。
   - **代码核心**：
     ```cpp
     for (int i = 1;i <= 1024;i ++ ) {
         int flag = 0;
         for (int j = 1;j <= n;j ++ ) {
             if (b[i][j] != a[j]) {
                 flag = 1;
                 break;
             }
         }
         if (flag == 0) {
             printf("%d\n",i);
             tag = 1;
             break;
         }
     }
     ```

3. **作者：OIerZhang**
   - **星级：4**
   - **关键亮点**：通过排序后比较集合元素，思路清晰，代码简洁，适合初学者理解。
   - **代码核心**：
     ```cpp
     for (int k = 1; k <= 1024; k++) {
         bool f = true;
         for (int i = 1; i <= n; i++) x[i] = a[i] ^ k;
         sort(x + 1, x + 1 + n);
         for (int i = 1; i <= n; i++) {
             if (a[i] != x[i]) {
                 f = false;
                 break;
             }
         }
         if (f) {
             cout << k << endl;
             flag = false;
             break;
         }
     }
     ```

### 最优关键思路
1. **预处理与计数**：通过预处理异或结果或记录初始集合中每个数的个数，可以减少重复计算，提高效率。
2. **排序比较**：通过排序后比较集合元素，可以避免顺序不一致带来的问题，确保集合相等。

### 拓展思路
类似的问题可以扩展到其他位运算操作，如与、或等。此外，可以结合哈希表等数据结构来进一步优化集合的比较。

### 推荐题目
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：38.33秒