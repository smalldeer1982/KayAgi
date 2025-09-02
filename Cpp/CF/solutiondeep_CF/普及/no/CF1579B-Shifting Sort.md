# 题目信息

# Shifting Sort

## 题目描述

The new generation external memory contains an array of integers $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $ .

This type of memory does not support changing the value of an arbitrary element. Instead, it allows you to cut out any segment of the given array, cyclically shift (rotate) it by any offset and insert it back into the same place.

Technically, each cyclic shift consists of two consecutive actions:

1. You may select arbitrary indices $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) as the boundaries of the segment.
2. Then you replace the segment $ a[l \ldots r] $ with it's cyclic shift to the left by an arbitrary offset $ d $ . The concept of a cyclic shift can be also explained by following relations: the sequence $ [1, 4, 1, 3] $ is a cyclic shift of the sequence $ [3, 1, 4, 1] $ to the left by the offset $ 1 $ and the sequence $ [4, 1, 3, 1] $ is a cyclic shift of the sequence $ [3, 1, 4, 1] $ to the left by the offset $ 2 $ .

For example, if $ a = [1, \color{blue}{3, 2, 8}, 5] $ , then choosing $ l = 2 $ , $ r = 4 $ and $ d = 2 $ yields a segment $ a[2 \ldots 4] = [3, 2, 8] $ . This segment is then shifted by the offset $ d = 2 $ to the left, and you get a segment $ [8, 3, 2] $ which then takes the place of of the original elements of the segment. In the end you get $ a = [1, \color{blue}{8, 3, 2}, 5] $ .

Sort the given array $ a $ using no more than $ n $ cyclic shifts of any of its segments. Note that you don't need to minimize the number of cyclic shifts. Any method that requires $ n $ or less cyclic shifts will be accepted.

## 说明/提示

Explanation of the fourth data set in the example:

1. The segment $ a[2 \ldots 4] $ is selected and is shifted to the left by $ 2 $ : $ [2, {\color{blue}{5, 1, 4}}, 3] \longrightarrow [2, {\color{blue}{4, 5, 1}}, 3] $
2. The segment $ a[1 \ldots 5] $ is then selected and is shifted to the left by $ 3 $ : $ [{\color{blue}{2, 4, 5, 1, 3}}] \longrightarrow [{\color{blue}{1, 3, 2, 4, 5}}] $
3. After that the segment $ a[1 \ldots 2] $ is selected and is shifted to the left by $ 1 $ : $ [{\color{blue}{1, 3}}, 2, 4, 5] \longrightarrow [{\color{blue}{3, 1}}, 2, 4, 5] $
4. And in the end the segment $ a[1 \ldots 3] $ is selected and is shifted to the left by $ 1 $ : $ [{\color{blue}{3, 1, 2}}, 4, 5] \longrightarrow [{\color{blue}{1, 2, 3}}, 4, 5] $

## 样例 #1

### 输入

```
4
2
2 1
3
1 2 1
4
2 4 1 3
5
2 5 1 4 3```

### 输出

```
1
1 2 1
1
1 3 2
3
2 4 1
2 3 1
1 3 2
4
2 4 2
1 5 3
1 2 1
1 3 1```

# AI分析结果

### 题目内容重写
# 移位排序

## 题目描述

新一代外部存储器包含一个整数数组 $ a[1 \ldots n] = [a_1, a_2, \ldots, a_n] $。

这种类型的存储器不支持更改任意元素的值。相反，它允许你剪切出数组的任意一段，将其循环左移任意偏移量，然后将其插入回原位置。

技术上，每次循环移位由两个连续操作组成：

1. 你可以选择任意索引 $ l $ 和 $ r $（ $ 1 \le l < r \le n $ ）作为段的边界。
2. 然后你将段 $ a[l \ldots r] $ 替换为其循环左移任意偏移量 $ d $ 后的结果。循环左移的概念可以通过以下关系解释：序列 $ [1, 4, 1, 3] $ 是序列 $ [3, 1, 4, 1] $ 循环左移偏移量 $ 1 $ 的结果，序列 $ [4, 1, 3, 1] $ 是序列 $ [3, 1, 4, 1] $ 循环左移偏移量 $ 2 $ 的结果。

例如，如果 $ a = [1, \color{blue}{3, 2, 8}, 5] $，选择 $ l = 2 $，$ r = 4 $ 和 $ d = 2 $，则段 $ a[2 \ldots 4] = [3, 2, 8] $。该段左移偏移量 $ d = 2 $ 后得到段 $ [8, 3, 2] $，然后将其替换回原位置。最终得到 $ a = [1, \color{blue}{8, 3, 2}, 5] $。

使用不超过 $ n $ 次循环移位对给定数组 $ a $ 进行排序。注意，你不需要最小化循环移位的次数。任何使用 $ n $ 次或更少循环移位的方法都将被接受。

## 说明/提示

样例第四组数据的解释：

1. 选择段 $ a[2 \ldots 4] $ 并左移 $ 2 $：$ [2, {\color{blue}{5, 1, 4}}, 3] \longrightarrow [2, {\color{blue}{4, 5, 1}}, 3] $
2. 选择段 $ a[1 \ldots 5] $ 并左移 $ 3 $：$ [{\color{blue}{2, 4, 5, 1, 3}}] \longrightarrow [{\color{blue}{1, 3, 2, 4, 5}}] $
3. 选择段 $ a[1 \ldots 2] $ 并左移 $ 1 $：$ [{\color{blue}{1, 3}}, 2, 4, 5] \longrightarrow [{\color{blue}{3, 1}}, 2, 4, 5] $
4. 选择段 $ a[1 \ldots 3] $ 并左移 $ 1 $：$ [{\color{blue}{3, 1, 2}}, 4, 5] \longrightarrow [{\color{blue}{1, 2, 3}}, 4, 5] $

## 样例 #1

### 输入

```
4
2
2 1
3
1 2 1
4
2 4 1 3
5
2 5 1 4 3```

### 输出

```
1
1 2 1
1
1 3 2
3
2 4 1
2 3 1
1 3 2
4
2 4 2
1 5 3
1 2 1
1 3 1```

### 算法分类
排序、构造

### 题解分析与结论
这道题的核心是通过循环移位操作将数组排序。由于题目允许最多进行 $n$ 次操作，因此可以采用贪心策略，每次将当前未排序部分的最小值移动到正确的位置。大多数题解都采用了这种思路，通过枚举或模拟来实现。

### 评分较高的题解
1. **作者：EternalHeart1314 (赞：7)**
   - **星级：4.5**
   - **关键亮点：** 代码简洁，思路清晰，通过枚举每个位置并找到应该放置的数字，然后通过左移将其移动到正确位置。时间复杂度为 $O(tn^2)$，适合小规模数据。
   - **核心代码：**
     ```cpp
     for(int i(1); i <= n; ++ i) {
         for(int j(i); j <= n; ++ j) {
             if(a[j] == c[i]) {
                 k = j;
                 break;
             }
         }
         d[i] = k;
         if(k > i) {
             ++ ans;
         }
         for(int j(i); j <= k; ++ j) {
             x = j + k - i;
             if(x > k) {
                 x = x - k + i - 1;
             }
             b[j] = a[x];
         }
         for(int j(i); j <= k; ++ j) {
             a[j] = b[j];
         }
     }
     ```

2. **作者：zhangqin123 (赞：4)**
   - **星级：4**
   - **关键亮点：** 通过离散化处理数组，减少了比较的复杂度，并且在每次操作后更新未排序部分的最小值下标，确保每次操作都能将最小值移动到正确位置。
   - **核心代码：**
     ```cpp
     for(int q=1;q<=50;q++) {
         if(!sum[q]) continue;
         for(int i=1;i<=sum[q];i++) {
             sumx++;
             if(sumx!=k[q][i]) {
                 ans++;
                 ans1[ans]=sumx,ans2[ans]=k[q][i],ans3[ans]=k[q][i]-sumx;
                 for(int x=sumx;x<=k[q][i];x++) b[x]=a[x];
                 for(int x=sumx+1;x<=k[q][i];x++) a[x]=b[x-1];
                 a[sumx]=q;
             }
         }
         h++;
         for(int i=sumx+1;i<=n;i++) {
             if(a[i]==h) sum[h]++,k[h][sum[h]]=i;
         }
     }
     ```

3. **作者：Cold_Eyes_bystander (赞：4)**
   - **星级：4**
   - **关键亮点：** 采用插入排序的思想，每次将最小值移动到最前面，操作次数不超过 $n$，代码简洁易懂。
   - **核心代码：**
     ```cpp
     for(int i=n;i>=1;i--) {
         int x=a[i],j=i+1;
         while(j<=n&&a[j]<x) {
             a[j-1]=a[j];
             j++;
         }
         j--;
         a[j]=x;
         if(j!=i) {
             cnt++;
             b[cnt]=i,c[cnt]=j,d[cnt]=1;
         }
     }
     ```

### 最优关键思路或技巧
- **贪心策略：** 每次将当前未排序部分的最小值移动到正确位置，确保每次操作都能有效推进排序过程。
- **离散化处理：** 对于大规模数据，可以通过离散化减少比较的复杂度。
- **模拟操作：** 通过模拟循环移位操作，确保每次移动都能正确地将元素放置到目标位置。

### 可拓展之处
- **类似题目：** 可以考虑其他类型的排序问题，如通过交换、反转等操作进行排序。
- **算法优化：** 对于更大规模的数据，可以考虑更高效的排序算法或优化循环移位的实现。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：55.77秒