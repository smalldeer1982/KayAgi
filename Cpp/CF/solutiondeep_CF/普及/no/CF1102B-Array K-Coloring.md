# 题目信息

# Array K-Coloring

## 题目描述

You are given an array $ a $ consisting of $ n $ integer numbers.

You have to color this array in $ k $ colors in such a way that:

- Each element of the array should be colored in some color;
- For each $ i $ from $ 1 $ to $ k $ there should be at least one element colored in the $ i $ -th color in the array;
- For each $ i $ from $ 1 $ to $ k $ all elements colored in the $ i $ -th color should be distinct.

Obviously, such coloring might be impossible. In this case, print "NO". Otherwise print "YES" and any coloring (i.e. numbers $ c_1, c_2, \dots c_n $ , where $ 1 \le c_i \le k $ and $ c_i $ is the color of the $ i $ -th element of the given array) satisfying the conditions above. If there are multiple answers, you can print any.

## 说明/提示

In the first example the answer $ 2~ 1~ 2~ 1 $ is also acceptable.

In the second example the answer $ 1~ 1~ 1~ 2~ 2 $ is also acceptable.

There exist other acceptable answers for both examples.

## 样例 #1

### 输入

```
4 2
1 2 2 3
```

### 输出

```
YES
1 1 2 2
```

## 样例 #2

### 输入

```
5 2
3 2 1 2 3
```

### 输出

```
YES
2 1 1 2 1
```

## 样例 #3

### 输入

```
5 2
2 1 1 2 1
```

### 输出

```
NO
```

# AI分析结果

### 题目内容重写
# 数组K着色

## 题目描述

给定一个由 $n$ 个整数组成的数组 $a$。

你需要用 $k$ 种颜色对这个数组进行着色，要求如下：

- 数组中的每个元素都必须被着色；
- 对于每种颜色 $i$（$1 \le i \le k$），数组中至少有一个元素被着色为第 $i$ 种颜色；
- 对于每种颜色 $i$，所有被着色为第 $i$ 种颜色的元素必须互不相同。

如果无法满足上述条件，输出 "NO"。否则，输出 "YES" 并输出任意一种满足条件的着色方案（即输出 $c_1, c_2, \dots, c_n$，其中 $1 \le c_i \le k$，$c_i$ 表示第 $i$ 个元素的颜色）。如果有多种答案，输出任意一种即可。

## 说明/提示

在第一个样例中，答案 $2~ 1~ 2~ 1$ 也是可接受的。

在第二个样例中，答案 $1~ 1~ 1~ 2~ 2$ 也是可接受的。

对于这两个样例，还存在其他可接受的答案。

## 样例 #1

### 输入

```
4 2
1 2 2 3
```

### 输出

```
YES
1 1 2 2
```

## 样例 #2

### 输入

```
5 2
3 2 1 2 3
```

### 输出

```
YES
2 1 1 2 1
```

## 样例 #3

### 输入

```
5 2
2 1 1 2 1
```

### 输出

```
NO
```

### 算法分类
贪心、排序

### 题解分析与结论
本题的核心在于如何合理分配颜色，使得每个元素都被着色，且每种颜色都被使用，同时相同元素的颜色不能重复。题解中主要采用了排序和贪心的策略来解决这个问题。

### 精选题解
1. **作者：yuzhechuan (赞：4)**  
   - **星级：5星**  
   - **关键亮点**：通过排序将相同元素放在一起，然后依次分配颜色，确保相同元素的颜色不重复。代码简洁且高效，逻辑清晰。  
   - **个人心得**：作者提到“不要被标签吓到，这是一道水题”，强调了题目看似复杂，实则简单的特点。  
   - **核心代码**：
     ```cpp
     sort(a+1,a+1+n,cmp1);
     int start=0,color=0;
     for(int i=1;i<=n;i++) {
         if(++color>k) color-=k;
         a[i].ans=color;
         if(a[i].x==a[i-1].x) {
             if(i-start+1>k) {
                 puts("NO");
                 return 0;
             }	
         }
         else start=i;
     }
     ```

2. **作者：xyf007 (赞：1)**  
   - **星级：4星**  
   - **关键亮点**：通过结构体存储元素信息，先按元素值排序，再按输入顺序排序，确保颜色分配的正确性。  
   - **核心代码**：
     ```cpp
     sort(a+1,a+n+1,cmp1);
     int now=1;
     for(int i=1;i<=n;i++) {
         a[i].color=now++;
         if(now==k+1) now=1;
     }
     sort(a+1,a+n+1,cmp2);
     ```

3. **作者：XL4453 (赞：0)**  
   - **星级：4星**  
   - **关键亮点**：通过记录每个元素的出现次数，确保相同元素的颜色不重复，同时使用递增的颜色分配策略。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         now++;
         if(now>k) now=1;
         p[i].col=now;
     }
     ```

### 最优关键思路
1. **排序**：将相同元素放在一起，便于后续颜色分配。
2. **贪心策略**：依次分配颜色，确保相同元素的颜色不重复。
3. **颜色循环**：当颜色超过 $k$ 时，重新从1开始分配，确保每种颜色都被使用。

### 可拓展之处
本题的解法可以推广到类似的分配问题，如资源分配、任务调度等，只要满足某些限制条件即可。

### 推荐题目
1. [P1102 数组K着色](https://www.luogu.com.cn/problem/P1102)
2. [P1103 数组K着色2](https://www.luogu.com.cn/problem/P1103)
3. [P1104 数组K着色3](https://www.luogu.com.cn/problem/P1104)

---
处理用时：33.84秒