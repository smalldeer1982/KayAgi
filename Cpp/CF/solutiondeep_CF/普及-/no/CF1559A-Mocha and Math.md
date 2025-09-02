# 题目信息

# Mocha and Math

## 题目描述

Mocha is a young girl from high school. She has learned so much interesting knowledge from her teachers, especially her math teacher. Recently, Mocha is learning about binary system and very interested in bitwise operation.

This day, Mocha got a sequence $ a $ of length $ n $ . In each operation, she can select an arbitrary interval $ [l, r] $ and for all values $ i $ ( $ 0\leq i \leq r-l $ ), replace $ a_{l+i} $ with $ a_{l+i} \,\&\, a_{r-i} $ at the same time, where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND). This operation can be performed any number of times.

For example, if $ n=5 $ , the array is $ [a_1,a_2,a_3,a_4,a_5] $ , and Mocha selects the interval $ [2,5] $ , then the new array is $ [a_1,a_2\,\&\, a_5, a_3\,\&\, a_4, a_4\,\&\, a_3, a_5\,\&\, a_2] $ .

Now Mocha wants to minimize the maximum value in the sequence. As her best friend, can you help her to get the answer?

## 说明/提示

In the first test case, Mocha can choose the interval $ [1,2] $ , then the sequence becomes $ [ 0, 0] $ , where the first element is $ 1\,\&\,2 $ , and the second element is $ 2\,\&\,1 $ .

In the second test case, Mocha can choose the interval $ [1,3] $ , then the sequence becomes $ [ 1,1,1] $ , where the first element is $ 1\,\&\,3 $ , the second element is $ 1\,\&\,1 $ , and the third element is $ 3\,\&\,1 $ .

## 样例 #1

### 输入

```
4
2
1 2
3
1 1 3
4
3 11 3 7
5
11 7 15 3 7```

### 输出

```
0
1
3
3```

# AI分析结果

### 题目内容
#### Mocha和数学
1. **题目描述**：Mocha是一名高中生。她从老师那里学到了很多有趣的知识，尤其是从她的数学老师那里。最近，Mocha正在学习二进制系统，并且对位运算非常感兴趣。
这一天，Mocha得到了一个长度为$n$的序列$a$。在每次操作中，她可以选择任意一个区间$[l, r]$，并且对于所有的值$i$（$0\leq i \leq r - l$），同时将$a_{l + i}$替换为$a_{l + i} \,\&\, a_{r - i}$，其中$\&$表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND) 。这个操作可以执行任意次数。
例如，如果$n = 5$，数组为$[a_1, a_2, a_3, a_4, a_5]$，Mocha选择区间$[2, 5]$，那么新的数组就是$[a_1, a_2\,\&\, a_5, a_3\,\&\, a_4, a_4\,\&\, a_3, a_5\,\&\, a_2]$ 。
现在Mocha想要最小化序列中的最大值。作为她最好的朋友，你能帮她得到答案吗？
2. **说明/提示**：在第一个测试用例中，Mocha可以选择区间$[1, 2]$，然后序列变为$[0, 0]$，其中第一个元素是$1\,\&\,2$，第二个元素是$2\,\&\,1$。
在第二个测试用例中，Mocha可以选择区间$[1, 3]$，然后序列变为$[1, 1, 1]$，其中第一个元素是$1\,\&\,3$，第二个元素是$1\,\&\,1$，第三个元素是$3\,\&\,1$。
3. **样例 #1**
    - **输入**：
```
4
2
1 2
3
1 1 3
4
3 11 3 7
5
11 7 15 3 7
```
    - **输出**：
```
0
1
3
3
```
### 算法分类
位运算
### 综合分析与结论
这些题解的核心思路都是利用按位与运算“越与越小”的特性，通过对序列中的数进行按位与操作来最小化最大值。大部分题解直接将所有数进行按位与得到答案，部分题解通过多次对相邻数或任意数对进行按位与操作，使序列最终所有数相同，这个相同的值即为所有数按位与的结果。
解决难点在于理解按位与操作对每个二进制位的影响，以及证明通过给定操作可以实现所有数按位与。不同题解在思路清晰度、代码简洁度上有所差异。

### 所选的题解
- **作者：qinyihao (赞：2)  4星**
    - **关键亮点**：从答案的二进制表示角度出发，清晰阐述只有所有数在某二进制位都为1时，答案在该位才为1，否则可通过操作使该位为0，进而得出将所有数按位与得到答案的结论，思路独特清晰。
    - **核心代码**：
```cpp
// 先设定x = a_1 ，对序列进行迭代，使x = x & a_i ，最后x就是答案
int x = a[1];
for (int i = 2; i <= n; i++) {
    x = x & a[i];
}
cout << x << endl;
```
- **作者：miao5 (赞：2)  4星**
    - **关键亮点**：简洁明了地指出按位与操作会使结果小于等于原数中的最小值，所以按位与操作次数越多越好，直接得出将所有数按位与就是最优答案，思路简单直接。
    - **核心代码**：
```cpp
int ans = a[1];
for (int i = 2; i <= n; i++) {
    ans = ans & a[i];
}
cout << ans << endl;
```
- **作者：Cocoly1990 (赞：0)  4星**
    - **关键亮点**：详细证明了为什么答案是所有数按位与之后的值，通过阐述取和操作对最小化最大值有益且任意两个数最终都能取和，从二进制每位独立思考得出结论，逻辑严谨。
    - **核心代码**：
```cpp
int ans = a[1];
for (int i = 2; i <= n; i++) {
    ans &= a[i];
}
printf("%d\n", ans);
```

### 最优关键思路或技巧
理解按位与运算在二进制下的特性，即只有对应位都为1结果才为1，利用这个特性从二进制位的角度思考如何最小化最大值。同时，通过分析操作对二进制位的影响，得出所有数按位与就是最终答案的结论。

### 同类型题或类似算法套路拓展
此类题目通常围绕位运算的特性展开，关键在于分析位运算对数据二进制表示的影响。常见套路是从二进制位的角度去思考问题，结合题目给定的操作，分析如何通过操作改变二进制位从而达到题目要求，如最小化、最大化某些值等。

### 洛谷相似题目推荐
1. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：涉及位运算以及图的遍历相关知识。
2. [P1876 开灯](https://www.luogu.com.cn/problem/P1876)：通过位运算来模拟开关灯的操作，与本题类似在于都需要理解位运算对数据状态的改变。
3. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：虽然主要是贪心算法，但在一些数据处理上可能会用到位运算相关知识，帮助优化代码或者理解题意。 

---
处理用时：41.05秒