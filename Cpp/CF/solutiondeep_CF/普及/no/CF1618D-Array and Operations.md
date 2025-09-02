# 题目信息

# Array and Operations

## 题目描述

You are given an array $ a $ of $ n $ integers, and another integer $ k $ such that $ 2k \le n $ .

You have to perform exactly $ k $ operations with this array. In one operation, you have to choose two elements of the array (let them be $ a_i $ and $ a_j $ ; they can be equal or different, but their positions in the array must not be the same), remove them from the array, and add $ \lfloor \frac{a_i}{a_j} \rfloor $ to your score, where $ \lfloor \frac{x}{y} \rfloor $ is the maximum integer not exceeding $ \frac{x}{y} $ .

Initially, your score is $ 0 $ . After you perform exactly $ k $ operations, you add all the remaining elements of the array to the score.

Calculate the minimum possible score you can get.

## 说明/提示

Let's consider the example test.

In the first test case, one way to obtain a score of $ 2 $ is the following one:

1. choose $ a_7 = 1 $ and $ a_4 = 2 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{2} \rfloor = 0 $ , the array becomes $ [1, 1, 1, 1, 3] $ ;
2. choose $ a_1 = 1 $ and $ a_5 = 3 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{3} \rfloor = 0 $ , the array becomes $ [1, 1, 1] $ ;
3. choose $ a_1 = 1 $ and $ a_2 = 1 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{1} \rfloor = 1 $ , the array becomes $ [1] $ ;
4. add the remaining element $ 1 $ to the score, so the resulting score is $ 2 $ .

In the second test case, no matter which operations you choose, the resulting score is $ 16 $ .

In the third test case, one way to obtain a score of $ 0 $ is the following one:

1. choose $ a_1 = 1 $ and $ a_2 = 3 $ for the operation; the score becomes $ 0 + \lfloor \frac{1}{3} \rfloor = 0 $ , the array becomes $ [3, 7] $ ;
2. choose $ a_1 = 3 $ and $ a_2 = 7 $ for the operation; the score becomes $ 0 + \lfloor \frac{3}{7} \rfloor = 0 $ , the array becomes empty;
3. the array is empty, so the score doesn't change anymore.

In the fourth test case, no operations can be performed, so the score is the sum of the elements of the array: $ 4 + 2 = 6 $ .

## 样例 #1

### 输入

```
5
7 3
1 1 1 2 1 3 1
5 1
5 5 5 5 5
4 2
1 3 3 7
2 0
4 2
9 2
1 10 10 1 10 2 7 10 3```

### 输出

```
2
16
0
6
16```

# AI分析结果

### 题目内容重写
# 数组与操作

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$，以及另一个整数 $k$，满足 $2k \le n$。

你需要对这个数组执行恰好 $k$ 次操作。每次操作中，你需要选择数组中的两个元素（可以是相同的元素，但它们的下标必须不同），将它们从数组中移除，并将 $\lfloor \frac{a_i}{a_j} \rfloor$ 加到你的得分中，其中 $\lfloor \frac{x}{y} \rfloor$ 表示不超过 $\frac{x}{y}$ 的最大整数。

初始得分为 $0$。在完成恰好 $k$ 次操作后，将数组中剩余的所有元素加到得分中。

计算你能得到的最小可能得分。

## 说明/提示

考虑以下示例：

在第一个测试用例中，一种得到 $2$ 分的方法是：

1. 选择 $a_7 = 1$ 和 $a_4 = 2$ 进行操作；得分变为 $0 + \lfloor \frac{1}{2} \rfloor = 0$，数组变为 $[1, 1, 1, 1, 3]$；
2. 选择 $a_1 = 1$ 和 $a_5 = 3$ 进行操作；得分变为 $0 + \lfloor \frac{1}{3} \rfloor = 0$，数组变为 $[1, 1, 1]$；
3. 选择 $a_1 = 1$ 和 $a_2 = 1$ 进行操作；得分变为 $0 + \lfloor \frac{1}{1} \rfloor = 1$，数组变为 $[1]$；
4. 将剩余的元素 $1$ 加到得分中，最终得分为 $2$。

在第二个测试用例中，无论选择哪种操作，最终得分都是 $16$。

在第三个测试用例中，一种得到 $0$ 分的方法是：

1. 选择 $a_1 = 1$ 和 $a_2 = 3$ 进行操作；得分变为 $0 + \lfloor \frac{1}{3} \rfloor = 0$，数组变为 $[3, 7]$；
2. 选择 $a_1 = 3$ 和 $a_2 = 7$ 进行操作；得分变为 $0 + \lfloor \frac{3}{7} \rfloor = 0$，数组变为空；
3. 数组为空，得分不再变化。

在第四个测试用例中，无法进行任何操作，因此得分为数组中所有元素的和：$4 + 2 = 6$。

## 样例 #1

### 输入

```
5
7 3
1 1 1 2 1 3 1
5 1
5 5 5 5 5
4 2
1 3 3 7
2 0
4 2
9 2
1 10 10 1 10 2 7 10 3
```

### 输出

```
2
16
0
6
16
```

### 算法分类
贪心

### 题解分析与结论
所有题解都采用了贪心策略，核心思路是将数组排序后，将前 $n-2k$ 个最小的元素直接加到得分中，然后将剩下的 $2k$ 个元素进行配对操作，尽量让得分最小。具体来说，配对时采用首尾配对的方式，即第 $i$ 个元素与第 $i+k$ 个元素配对，这样可以尽量避免相同的元素配对，从而减少得分的增加。

### 评分较高的题解
1. **作者：activeO (赞：4)**
   - **星级：4星**
   - **关键亮点：** 代码简洁明了，直接通过排序和首尾配对的方式实现了贪心策略，逻辑清晰。
   - **代码核心思想：**
     ```cpp
     sort(a+1,a+n+1);
     for(int i=1;i<=n-2*k;i++) ans+=a[i];
     for(int i=n-k+1;i<=n;i++){
         if(a[i]==a[i-k]) ans++;
     }
     ```

2. **作者：封禁用户 (赞：2)**
   - **星级：4星**
   - **关键亮点：** 详细解释了贪心策略的实现过程，代码结构清晰，逻辑严谨。
   - **代码核心思想：**
     ```cpp
     sort(a , a + n);
     for(int i = 0 ; i < n - k * 2 ; i++) cnt += a[i];
     for(int i = n - k * 2 ; i < n - k ; i++) {
         if(a[i] == a[i + k]) cnt++;
     }
     ```

3. **作者：huyangmu (赞：2)**
   - **星级：4星**
   - **关键亮点：** 代码简洁，直接通过排序和首尾配对的方式实现了贪心策略，逻辑清晰。
   - **代码核心思想：**
     ```cpp
     sort (a + 1, a + n + 1);
     for (int i = 1; i <= n - 2 * k; ++i) ans += a[i];
     int l = n - 2 * k + 1, r = n - k;
     while (l <= r){
         ans += (a[l] / a[l + k]);
         ++l;
     }
     ```

### 最优关键思路或技巧
1. **排序与贪心：** 首先对数组进行排序，然后通过贪心策略选择最小的 $n-2k$ 个元素直接加到得分中，剩下的 $2k$ 个元素采用首尾配对的方式，尽量让得分最小。
2. **首尾配对：** 在配对时，采用首尾配对的方式，即第 $i$ 个元素与第 $i+k$ 个元素配对，这样可以尽量避免相同的元素配对，从而减少得分的增加。

### 可拓展之处
类似的问题可以通过排序和贪心策略来解决，尤其是在需要最小化或最大化某个值时，排序和贪心往往是有效的策略。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)

---
处理用时：41.01秒