# 题目信息

# Iva & Pav

## 题目描述

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array $ a $ of $ n $ elements.

Let's define $ f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r $ (here $ \& $ denotes the [bitwise AND operation](http://tiny.cc/bitwise_and)).

Note that $ f(l, r) $ is not defined when $ l>r $ .

Iva also gave Pav $ q $ queries.

Each query consists of 2 numbers, $ k $ and $ l $ , and she wants Pav to find the largest index $ r $ ( $ l \le r \le n $ ), such that $ f(l, r) \ge k $ .

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

## 说明/提示

In the first test case $ n=5 $ , and the array $ a = [15, 14, 17, 42, 34] $

The first query asks for the biggest index $ r $ such that the $ f(1, r) \ge 7 $ .

 $ f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0 $ , so $ r=2 $ is the answer.

The second query asks for $ f(2, r) \ge 15 $ . Since such $ r $ doesn't exist, the answer is $ -1 $ .

The third query asks for $ f(4, r) \ge 5 $ . $ f(4, 4) = 42, \ f(4, 5) = 34 $ , so $ r=5 $ is the answer.

In the second test case $ n=5 $ , and the array $ a= [7, 5, 3, 1, 7] $ .

For the first query, $ f(1, r) \ge 7 $ .

 $ f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1 $ , so the answer to this query is $ 1 $ .

For the second query, $ f(5, r) \ge 7 $ .

 $ f(5, 5) = 7 $ , so the answer is $ 5 $ .

For the third query, $ f(2, r) \ge 3 $ .

 $ f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1 $ , so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
15 14 17 42 34
3
1 7
2 15
4 5
5
7 5 3 1 7
4
1 7
5 7
2 3
2 2
7
19 20 15 12 21 7 11
4
1 15
4 4
7 12
5 7```

### 输出

```
2 -1 5 
1 5 2 2 
2 6 -1 5```

# AI分析结果

### 题目内容重写
#### 题目描述
Iva和Pav是塞尔维亚著名的编程竞赛情侣。在塞尔维亚，人们称Pav为“papuca”，因此他会实现Iva的所有愿望。

Iva给Pav一个包含$n$个元素的数组$a$。

定义$f(l, r) = a_l \ \& \ a_{l+1} \ \& \dots \& \ a_r$（其中$\&$表示按位与运算）。

注意，当$l > r$时，$f(l, r)$未定义。

Iva还给了Pav$q$个查询。

每个查询包含两个数字$k$和$l$，她希望Pav找到最大的索引$r$（$l \le r \le n$），使得$f(l, r) \ge k$。

Pav希望快速解决这个问题，因为他不想让Iva失望。他需要你的帮助。

#### 说明/提示
在第一个测试用例中，$n=5$，数组$a = [15, 14, 17, 42, 34]$。

第一个查询要求找到最大的索引$r$，使得$f(1, r) \ge 7$。

$f(1,1) = 15, \ f(1, 2) = 14, \ f(1,3)=0 \ f(1, 4)=0 \ f(1, 5)=0$，因此$r=2$是答案。

第二个查询要求$f(2, r) \ge 15$。由于这样的$r$不存在，答案为$-1$。

第三个查询要求$f(4, r) \ge 5$。$f(4, 4) = 42, \ f(4, 5) = 34$，因此$r=5$是答案。

在第二个测试用例中，$n=5$，数组$a= [7, 5, 3, 1, 7]$。

对于第一个查询，$f(1, r) \ge 7$。

$f(1, 1)=7, \ f(1, 2)=5, \ f(1, 3) = 1, \ f(1,4) = 1, \ f(1, 5)=1$，因此答案为$1$。

对于第二个查询，$f(5, r) \ge 7$。

$f(5, 5) = 7$，因此答案为$5$。

对于第三个查询，$f(2, r) \ge 3$。

$f(2, 2) = 5, \ f(2, 3) = 1, \ f(2, 4) = 1, \ f(2, 5) = 1$，因此答案为$2$。

### 题解分析与结论
#### 综合分析与结论
本题的核心在于快速计算区间按位与，并且利用其单调性进行二分查找。大多数题解都采用了二分查找结合ST表或线段树的思路，少数题解使用了拆位前缀和的方法。ST表和线段树都能在$O(\log n)$时间内查询区间按位与，而拆位前缀和的方法虽然思路清晰，但时间复杂度较高。

#### 评分较高的题解
1. **作者：Register_int (5星)**
   - **关键亮点**：使用ST表预处理区间按位与，结合二分查找，时间复杂度为$O(\log n)$，代码简洁高效。
   - **核心代码**：
     ```cpp
     void init(int n, int *a) {
         for (int i = 1; i <= n; i++) st[0][i] = a[i];
         for (int i = 1; i <= lg[n]; i++) {
             for (int j = 1; j + (1 << i) - 1 <= n; j++) {
                 st[i][j] = st[i - 1][j] & st[i - 1][j + (1 << i - 1)];
             }
         }
     }
     ```
   - **个人心得**：ST表不需要二分，直接预处理即可。

2. **作者：luqyou (4星)**
   - **关键亮点**：使用ST表维护区间按位与，结合二分查找，思路清晰，代码可读性强。
   - **核心代码**：
     ```cpp
     int query(int l, int r) {
         int k = log2(r - l + 1);
         return (st[l][k] & st[r - (1 << k) + 1][k]);
     }
     ```
   - **个人心得**：区间按位与是一个可重复贡献问题，适合用ST表维护。

3. **作者：One_JuRuo (4星)**
   - **关键亮点**：使用ST表预处理区间按位与，结合二分查找，代码简洁，时间复杂度低。
   - **核心代码**：
     ```cpp
     int query(int l, int r) {
         int len = log2(r - l + 1);
         return st[l][len] & st[r - (1 << len) + 1][len];
     }
     ```
   - **个人心得**：ST表和二分查找的结合是解决此类问题的经典方法。

### 最优关键思路或技巧
- **ST表预处理**：ST表能在$O(\log n)$时间内查询区间按位与，适合处理此类区间查询问题。
- **二分查找**：利用按位与的单调性，通过二分查找快速定位满足条件的最大$r$。

### 可拓展之处
- **类似算法套路**：类似的问题可以扩展到其他具有单调性的区间操作，如按位或、按位异或等。
- **其他数据结构**：线段树也可以用于处理此类问题，虽然时间复杂度相同，但代码实现稍复杂。

### 推荐题目
1. [P3865 【模板】ST表](https://www.luogu.com.cn/problem/P3865)
2. [P3374 【模板】线段树 1](https://www.luogu.com.cn/problem/P3374)
3. [P1198 [JSOI2008]最大数](https://www.luogu.com.cn/problem/P1198)

### 个人心得摘录
- **Register_int**：ST表不需要二分，直接预处理即可。
- **luqyou**：区间按位与是一个可重复贡献问题，适合用ST表维护。
- **One_JuRuo**：ST表和二分查找的结合是解决此类问题的经典方法。

---
处理用时：57.79秒