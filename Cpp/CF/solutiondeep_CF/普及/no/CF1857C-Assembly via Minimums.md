# 题目信息

# Assembly via Minimums

## 题目描述

Sasha has an array $ a $ of $ n $ integers. He got bored and for all $ i $ , $ j $ ( $ i < j $ ), he wrote down the minimum value of $ a_i $ and $ a_j $ . He obtained a new array $ b $ of size $ \frac{n\cdot (n-1)}{2} $ .

For example, if $ a= $ \[ $ 2,3,5,1 $ \], he would write \[ $ \min(2, 3), \min(2, 5), \min(2, 1), \min(3, 5), \min(3, 1), min(5, 1) $ \] $ = $ \[ $ 2, 2, 1, 3, 1, 1 $ \].

Then, he randomly shuffled all the elements of the array $ b $ .

Unfortunately, he forgot the array $ a $ , and your task is to restore any possible array $ a $ from which the array $ b $ could have been obtained.

The elements of array $ a $ should be in the range $ [-10^9,10^9] $ .

## 说明/提示

In the first sample, Sasha chose the array $ [1,3,3] $ , then the array $ b $ will look like $ [\min(a_1,a_2)=1, \min(a_1,a_3)=1, \min(a_2,a_3)=3] $ , after shuffling its elements, the array can look like $ [1,3,1] $ .

In the second sample, there is only one pair, so the array $ [10,10] $ is suitable. Another suitable array could be $ [15,10] $ .

## 样例 #1

### 输入

```
5
3
1 3 1
2
10
4
7 5 3 5 3 3
5
2 2 2 2 2 2 2 2 2 2
5
3 0 0 -2 0 -2 0 0 -2 -2```

### 输出

```
1 3 3
10 10
7 5 3 12
2 2 2 2 2
0 -2 0 3 5```

# AI分析结果

### 题目内容重写
# 通过最小值重建数组

## 题目描述

Sasha有一个包含$n$个整数的数组$a$。他感到无聊，于是对于所有$i$和$j$（$i < j$），他写下了$a_i$和$a_j$的最小值。他得到了一个新的数组$b$，大小为$\frac{n\cdot (n-1)}{2}$。

例如，如果$a= [2,3,5,1]$，他会写下$[\min(2, 3), \min(2, 5), \min(2, 1), \min(3, 5), \min(3, 1), \min(5, 1)] = [2, 2, 1, 3, 1, 1]$。

然后，他随机打乱了数组$b$的所有元素。

不幸的是，他忘记了数组$a$，你的任务是从数组$b$中恢复出任何可能的数组$a$。

数组$a$的元素应该在$[-10^9,10^9]$范围内。

## 说明/提示

在第一个样例中，Sasha选择了数组$[1,3,3]$，那么数组$b$将会是$[\min(a_1,a_2)=1, \min(a_1,a_3)=1, \min(a_2,a_3)=3]$，打乱后数组可能看起来像$[1,3,1]$。

在第二个样例中，只有一对，所以数组$[10,10]$是合适的。另一个合适的数组可能是$[15,10]$。

## 样例 #1

### 输入

```
5
3
1 3 1
2
10
4
7 5 3 5 3 3
5
2 2 2 2 2 2 2 2 2 2
5
3 0 0 -2 0 -2 0 0 -2 -2```

### 输出

```
1 3 3
10 10
7 5 3 12
2 2 2 2 2
0 -2 0 3 5```

### 算法分类
排序、构造

### 题解分析与结论
该题的核心在于通过排序和构造的方法，从打乱的最小值数组中恢复出原数组。大多数题解都采用了类似的思路：首先将数组$b$排序，然后根据排序后的$b$数组，依次取出前$n-1$个元素作为$a$数组的前$n-1$个元素，最后一个元素则取一个较大的值（如$10^9$）来保证其不影响到$b$数组的生成。

### 所选高分题解
1. **作者：WsW_** (5星)
   - **关键亮点**：思路清晰，代码简洁，直接通过排序后的$b$数组跳步取数，最后补上一个极大值。
   - **代码核心**：
     ```cpp
     sort(b+1,b+1+len);
     for(int i=1;i<=len;){
         printf("%d ",b[i]);
         i+=cnt;
         cnt--;
     }
     puts("1000000000");
     ```
   - **个人心得**：通过排序和跳步取数，直接构造出$a$数组，思路简洁明了。

2. **作者：Kedit2007** (4星)
   - **关键亮点**：详细分析了排序后的$b$数组与原数组$a$的关系，代码实现也较为简洁。
   - **代码核心**：
     ```cpp
     sort(arr.begin(), arr.end());
     for (int i = 0, j = n - 1; j > 0; i += j, j--) {
         cout << arr[i] << ' ';
     }
     cout << arr.back() << '\n';
     ```
   - **个人心得**：通过排序后的$b$数组，依次取出前$n-1$个元素，最后一个元素取$b$数组的最后一个值。

3. **作者：duchengjun** (4星)
   - **关键亮点**：通过排序后的$b$数组，依次取出前$n-1$个元素，最后一个元素取$b$数组的最后一个值。
   - **代码核心**：
     ```cpp
     sort(b+1,b+1+m);
     int i=1,j=n-1;
     while(i<=m){
         printf("%d ",b[i]);
         i+=j;
         j--;
     }
     printf("%d\n",b[m]);
     ```
   - **个人心得**：通过排序和跳步取数，直接构造出$a$数组，思路简洁明了。

### 最优关键思路或技巧
1. **排序与跳步取数**：将$b$数组排序后，通过跳步取数的方式，依次取出$a$数组的前$n-1$个元素，最后一个元素取一个较大的值（如$10^9$）。
2. **构造思维**：通过排序后的$b$数组，直接构造出$a$数组，无需复杂的计算或推导。

### 可拓展之处
类似的问题可以通过排序和构造的方法解决，尤其是在需要通过部分信息恢复整体结构的情况下。例如，通过某些特定的条件或部分数据，恢复出完整的数组或序列。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：34.47秒