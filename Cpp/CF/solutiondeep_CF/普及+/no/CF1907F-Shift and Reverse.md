# 题目信息

# Shift and Reverse

## 题目描述

Given an array of integers $ a_1, a_2, \ldots, a_n $ . You can make two types of operations with this array:

- Shift: move the last element of array to the first place, and shift all other elements to the right, so you get the array $ a_n, a_1, a_2, \ldots, a_{n-1} $ .
- Reverse: reverse the whole array, so you get the array $ a_n, a_{n-1}, \ldots, a_1 $ .

Your task is to sort the array in non-decreasing order using the minimal number of operations, or say that it is impossible.

## 说明/提示

In the first test case of the example, to sort the array \[ $ 3, 2, 1, 5, 4 $ \] you need to perform $ 3 $ operations:

- Shift to obtain the array \[ $ 4, 3, 2, 1, 5 $ \];
- Shift to obtain the array \[ $ 5, 4, 3, 2, 1 $ \];
- Reverse to obtain the array \[ $ 1, 2, 3, 4, 5 $ \].

In the third test case of the example, it can be shown that it is impossible to sort the array using the given operations.

In the seventh test case of the example, to sort the array \[ $ 4, 1, 3, 4, 4 $ \] you need to perform $ 3 $ operations:

- Reverse to obtain the array \[ $ 4, 4, 3, 1, 4 $ \];
- Shift to obtain the array \[ $ 4, 4, 4, 3, 1 $ \];
- Reverse to obtain the array \[ $ 1, 3, 4, 4, 4 $ \].

## 样例 #1

### 输入

```
11
5
3 2 1 5 4
5
1 1 2 1 1
4
3 7 10 5
5
1 2 3 4 5
2
5 1
3
3 4 1
5
4 1 3 4 4
3
5 1 1
4
2 5 5 4
5
2 2 1 1 2
2
5 5```

### 输出

```
3
2
-1
0
1
1
3
1
2
2
0```

# AI分析结果

### 题目内容
#### Shift and Reverse

**题目描述**

给定一个整数数组 $a_1, a_2, \ldots, a_n$。你可以对这个数组进行两种操作：

- **Shift**：将数组的最后一个元素移动到第一个位置，并将其他元素向右移动，得到数组 $a_n, a_1, a_2, \ldots, a_{n-1}$。
- **Reverse**：将整个数组反转，得到数组 $a_n, a_{n-1}, \ldots, a_1$。

你的任务是使用最少的操作次数将数组排序为非递减顺序，或者说明这是不可能的。

**说明/提示**

在第一个样例中，为了排序数组 \[$3, 2, 1, 5, 4$\]，你需要进行 $3$ 次操作：

1. **Shift** 得到数组 \[$4, 3, 2, 1, 5$\]；
2. **Shift** 得到数组 \[$5, 4, 3, 2, 1$\]；
3. **Reverse** 得到数组 \[$1, 2, 3, 4, 5$\]。

在第三个样例中，可以证明无法通过给定的操作将数组排序。

在第七个样例中，为了排序数组 \[$4, 1, 3, 4, 4$\]，你需要进行 $3$ 次操作：

1. **Reverse** 得到数组 \[$4, 4, 3, 1, 4$\]；
2. **Shift** 得到数组 \[$4, 4, 4, 3, 1$\]；
3. **Reverse** 得到数组 \[$1, 3, 4, 4, 4$\]。

**样例 #1**

**输入**

```
11
5
3 2 1 5 4
5
1 1 2 1 1
4
3 7 10 5
5
1 2 3 4 5
2
5 1
3
3 4 1
5
4 1 3 4 4
3
5 1 1
4
2 5 5 4
5
2 2 1 1 2
2
5 5
```

**输出**

```
3
2
-1
0
1
1
3
1
2
2
0
```

### 算法分类
排序、模拟

### 综合分析与结论
本题的核心在于通过最少的操作次数将数组排序为非递减顺序。由于操作类型有限（Shift 和 Reverse），我们可以通过分析数组的单调性来判断是否可以通过操作排序，并计算最小操作次数。

### 所选题解
1. **作者：bigclever (赞：6)**
   - **星级：5星**
   - **关键亮点**：通过将数组视为环形结构，分析了 Shift 和 Reverse 操作对数组单调性的影响，并详细分类讨论了不同情况下的操作次数。代码简洁，逻辑清晰。
   - **代码核心思想**：通过统计数组中的单调性变化点，判断是否可以通过操作排序，并计算最小操作次数。
   - **代码片段**：
     ```cpp
     int cntd=0,idd,cntx=0,idx;
     for(int i=1;i<n;i++)
         if(a[i]>a[i+1])cntd++,idd=i+1;
         else if(a[i]<a[i+1])cntx++,idx=i+1;
     if(!cntd){puts("0");continue;}
     if(!cntx){puts("1");continue;}
     if(cntd>1&&cntx>1){puts("-1");continue;}
     int ans=1e9;
     if(cntd==1&&a[1]>=a[n])ans=min({ans,idd+1,n-idd+1});
     if(cntx==1&&a[1]<=a[n])ans=min({ans,idx,n-idx+2});
     printf("%d\n",ans==1e9?-1:ans);
     ```

2. **作者：Eazin_star (赞：4)**
   - **星级：4星**
   - **关键亮点**：通过将数组倍长模拟环形结构，遍历数组判断是否可以通过操作排序，并计算最小操作次数。思路清晰，代码实现较为简洁。
   - **代码核心思想**：通过遍历倍长数组，判断是否可以通过 Shift 和 Reverse 操作排序，并计算最小操作次数。
   - **代码片段**：
     ```cpp
     int up = 1, down = 1, now = 0, ans = 2*n;
     for (int i = 2; i <= 2*n; i++) {
         if (a[i] > a[i-1]) up++, down = 1;
         else if (a[i] < a[i-1]) up = 1, down++;
         else up++, down++;
         if (up >= n || down >= n) {
             if (down >= n) ans = min(ans, min(2*n-i+1,i-n+1)); 
             if (up >= n) ans = min(ans, min(2*n-i,2+i-n));
         }
     }
     ```

3. **作者：xlpg0713 (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过分析数组的单调性，判断是否可以通过操作排序，并计算最小操作次数。代码实现简洁，逻辑清晰。
   - **代码核心思想**：通过统计数组中的单调性变化点，判断是否可以通过操作排序，并计算最小操作次数。
   - **代码片段**：
     ```cpp
     int cu = 0, cd = 0, pu = 0, pd = 0;
     for(int i = 1; i < n; i++)
         if(a[i] > a[i + 1]) ++cu, pu = i + 1;
     for(int i = 1; i < n; i++)
         if(a[i] < a[i + 1]) ++cd, pd = i + 1;
     if(cu == 0) {std::cout << "0\n"; continue;}
     if(cd == 0) {std::cout << "1\n"; continue;}
     if(cu > 1 && cd > 1) {std::cout << "-1\n"; continue;}
     int rs = 0x7fffffff;
     if(cu == 1 && a[1] >= a[n]) rs = min(rs, min(n - pu + 1, pu + 1));
     if(cd == 1 && a[1] <= a[n]) rs = min(rs, min(n - pd + 2, pd));
     std::cout << (rs == 0x7fffffff ? -1 : rs) << '\n';
     ```

### 最优关键思路或技巧
1. **环形结构分析**：将数组视为环形结构，分析 Shift 和 Reverse 操作对数组单调性的影响。
2. **单调性统计**：通过统计数组中的单调性变化点，判断是否可以通过操作排序，并计算最小操作次数。
3. **倍长数组模拟**：通过将数组倍长模拟环形结构，遍历数组判断是否可以通过操作排序，并计算最小操作次数。

### 可拓展之处
1. **类似操作问题**：可以扩展到其他类型的操作，如旋转、交换等，分析其对数组排序的影响。
2. **复杂单调性分析**：可以进一步分析更复杂的单调性变化，如多个单调性变化点的情况。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：67.32秒