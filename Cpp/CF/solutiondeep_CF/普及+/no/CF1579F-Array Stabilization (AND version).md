# 题目信息

# Array Stabilization (AND version)

## 题目描述

You are given an array $ a[0 \ldots n - 1] = [a_0, a_1, \ldots, a_{n - 1}] $ of zeroes and ones only. Note that in this problem, unlike the others, the array indexes are numbered from zero, not from one.

In one step, the array $ a $ is replaced by another array of length $ n $ according to the following rules:

1. First, a new array $ a^{\rightarrow d} $ is defined as a cyclic shift of the array $ a $ to the right by $ d $ cells. The elements of this array can be defined as $ a^{\rightarrow d}_i = a_{(i + n - d) \bmod n} $ , where $ (i + n - d) \bmod n $ is the remainder of integer division of $ i + n - d $ by $ n $ .  It means that the whole array $ a^{\rightarrow d} $ can be represented as a sequence $ $$$a^{\rightarrow d} = [a_{n - d}, a_{n - d + 1}, \ldots, a_{n - 1}, a_0, a_1, \ldots, a_{n - d - 1}] $ $ </p><p> </p></li><li> Then each element of the array  $ a\_i $  is replaced by  $ a\_i \\,\\&amp;\\, a^{\\rightarrow d}\_i $ , where  $ \\&amp; $  is a logical "AND" operator. </li></ol><p>For example, if  $ a = \[0, 0, 1, 1\] $  and  $ d = 1 $ , then  $ a^{\\rightarrow d} = \[1, 0, 0, 1\] $  and the value of  $ a $  after the first step will be  $ \[0 \\,\\&amp;\\, 1, 0 \\,\\&amp;\\, 0, 1 \\,\\&amp;\\, 0, 1 \\,\\&amp;\\, 1\] $ , that is  $ \[0, 0, 0, 1\] $ .</p><p>The process ends when the array stops changing. For a given array  $ a$$$, determine whether it will consist of only zeros at the end of the process. If yes, also find the number of steps the process will take before it finishes.

## 说明/提示

In the third sample test case the array will change as follows:

1. At the beginning $ a = [1, 1, 0, 1, 0] $ , and $ a^{\rightarrow 2} = [1, 0, 1, 1, 0] $ . Their element-by-element "AND" is equal to $ $$$[1 \,\&\, 1, 1 \,\&\, 0, 0 \,\&\, 1, 1 \,\&\, 1, 0 \,\&\, 0] = [1, 0, 0, 1, 0] $ $  </li><li> Now  $ a = \[1, 0, 0, 1, 0\] $ , then  $ a^{\\rightarrow 2} = \[1, 0, 1, 0, 0\] $ . Their element-by-element "AND" equals to  $ $ [1 \,\&\, 1, 0 \,\&\, 0, 0 \,\&\, 1, 1 \,\&\, 0, 0 \,\&\, 0] = [1, 0, 0, 0, 0] $ $  </li><li> And finally, when  $ a = \[1, 0, 0, 0, 0\] $  we get  $ a^{\\rightarrow 2} = \[0, 0, 1, 0, 0\] $ . Their element-by-element "AND" equals to  $ $ [1 \,\&\, 0, 0 \,\&\, 0, 0 \,\&\, 1, 0 \,\&\, 0, 0 \,\&\, 0] = [0, 0, 0, 0, 0] $ $  </li></ol> Thus, the answer is  $ 3 $  steps.<p>In the fourth sample test case, the array will not change as it shifts by  $ 2 $  to the right, so each element will be calculated as  $ 0 \\,\\&amp;\\, 0 $  or  $ 1 \\,\\&amp;\\, 1$$$ thus not changing its value. So the answer is -1, the array will never contain only zeros.

## 样例 #1

### 输入

```
5
2 1
0 1
3 2
0 1 0
5 2
1 1 0 1 0
4 2
0 1 0 1
1 1
0```

### 输出

```
1
1
3
-1
0```

# AI分析结果

### 题目内容（中文重写）
# 数组稳定化（按位与版本）

## 题目描述
给定一个仅由 0 和 1 组成的数组 $ a[0 \ldots n - 1] = [a_0, a_1, \ldots, a_{n - 1}] $ 。注意，在本题中，数组索引从 0 开始，而非从 1 开始。

在每一步中，数组 $ a $ 会根据以下规则被替换为另一个长度为 $ n $ 的数组：
1. 首先，定义一个新数组 $ a^{\rightarrow d} $ 为数组 $ a $ 向右循环移动 $ d $ 个单元格的结果。该数组的元素可定义为 $ a^{\rightarrow d}_i = a_{(i + n - d) \bmod n} $ ，其中 $ (i + n - d) \bmod n $ 是 $ i + n - d $ 除以 $ n $ 的余数。这意味着整个数组 $ a^{\rightarrow d} $ 可以表示为序列 $ a^{\rightarrow d} = [a_{n - d}, a_{n - d + 1}, \ldots, a_{n - 1}, a_0, a_1, \ldots, a_{n - d - 1}] $ 。
2. 然后，数组 $ a $ 中的每个元素 $ a_i $ 被替换为 $ a_i \& a^{\rightarrow d}_i $ ，其中 $ \& $ 是逻辑“与”运算符。

例如，如果 $ a = [0, 0, 1, 1] $ 且 $ d = 1 $ ，那么 $ a^{\rightarrow d} = [1, 0, 0, 1] $ ，经过第一步后 $ a $ 的值将变为 $ [0 \& 1, 0 \& 0, 1 \& 0, 1 \& 1] $ ，即 $ [0, 0, 0, 1] $ 。

当数组不再变化时，过程结束。对于给定的数组 $ a $ ，判断在过程结束时它是否将仅由 0 组成。如果是，还需找出过程结束前需要的步数。

## 说明/提示
在第三个样例测试用例中，数组将按以下方式变化：
1. 开始时 $ a = [1, 1, 0, 1, 0] $ ，且 $ a^{\rightarrow 2} = [1, 0, 1, 1, 0] $ 。它们逐元素的“与”运算结果为 $ [1 \& 1, 1 \& 0, 0 \& 1, 1 \& 1, 0 \& 0] = [1, 0, 0, 1, 0] $ 。
2. 现在 $ a = [1, 0, 0, 1, 0] $ ，则 $ a^{\rightarrow 2} = [1, 0, 1, 0, 0] $ 。它们逐元素的“与”运算结果为 $ [1 \& 1, 0 \& 0, 0 \& 1, 1 \& 0, 0 \& 0] = [1, 0, 0, 0, 0] $ 。
3. 最后，当 $ a = [1, 0, 0, 0, 0] $ 时，$ a^{\rightarrow 2} = [0, 0, 1, 0, 0] $ 。它们逐元素的“与”运算结果为 $ [1 \& 0, 0 \& 0, 0 \& 1, 0 \& 0, 0 \& 0] = [0, 0, 0, 0, 0] $ 。

因此，答案是 3 步。

在第四个样例测试用例中，数组向右移动 2 位时不会改变，所以每个元素将被计算为 $ 0 \& 0 $ 或 $ 1 \& 1 $ ，因此其值不会改变。所以答案是 -1 ，即数组永远不会只包含 0 。

## 样例 #1
### 输入
```
5
2 1
0 1
3 2
0 1 0
5 2
1 1 0 1 0
4 2
0 1 0 1
1 1
0
```

### 输出
```
1
1
3
-1
0
```

### 算法分类
广度优先搜索 BFS

### 综合分析与结论
这些题解主要围绕数组按位与和循环移位操作展开，核心是判断数组能否最终全变为 0 以及所需步数。大部分题解利用按位与运算中 0 的特性，即只要有一个 0 参与与运算结果就为 0 ，采用广度优先搜索（BFS）的方法，从初始的 0 位置开始扩展，更新后续位置的值。部分题解还考虑了将数组分组处理的优化思路，当 $d > 1$ 时，把数组分成 $\gcd(n, d)$ 组，每组独立处理。

### 所选题解
- **作者：Engulf (赞：8)，4星**
  - **关键亮点**：思路清晰，代码实现简洁，利用 BFS 从初始的 0 位置开始扩展，更新后续位置的值，最终判断数组是否全为 0 并计算步数。
- **作者：_ChongYun_ (赞：4)，4星**
  - **关键亮点**：同样采用 BFS ，使用两个队列区分不同轮次的操作，逻辑清晰，易于理解。
- **作者：eb0ycn (赞：0)，4星**
  - **关键亮点**：使用宽搜，记录每个点的最少操作次数，最后输出最大操作次数，思路简洁明了。

### 重点代码
#### Engulf 的代码
```cpp
while(!q.empty()){
    int len=q.size();
    for(int i=0;i<len;i++){
        int u=q.front();q.pop();
        int v=(u+d)%n;
        if(a[v]){
            q.push(v);a[v]=0;
        }
    }
    ans++;
}
```
**核心实现思想**：使用队列进行 BFS ，每次取出队首元素，更新其右移 $d$ 位的位置的值，若该位置为 1 则将其置为 0 并加入队列，每完成一轮操作步数加 1 。

#### _ChongYun_ 的代码
```cpp
while(!q.empty()){
    while(!q.empty()){
        int x=q.front();
        q.pop();
        if(a[x+d==n?n:(x+d)%n]){
            q1.push(x+d==n?n:(x+d)%n);
            a[x+d==n?n:(x+d)%n]=0;
        } 
    }
    while(!q1.empty()){
        q.push(q1.front());
        q1.pop();
    }
    ans++;
}
```
**核心实现思想**：使用两个队列 $q$ 和 $q1$ ，$q$ 存储当前轮次的 0 位置，将其右移 $d$ 位后若为 1 则置为 0 并加入 $q1$ ，一轮结束后将 $q1$ 中的元素移到 $q$ 中，步数加 1 。

#### eb0ycn 的代码
```cpp
while(l<r)
{
    u=qu[++l];
    nu=(u+d)%n;
    if(a[nu])dis[nu]=dis[u]+1,a[nu]=0,qu[++r]=nu;
}
```
**核心实现思想**：使用数组模拟队列进行宽搜，取出队首元素，更新其右移 $d$ 位的位置的值，若该位置为 1 则置为 0 ，记录操作次数并加入队列。

### 最优关键思路或技巧
- 利用按位与运算中 0 的特性，从初始的 0 位置开始扩展，能有效减少不必要的计算。
- 当 $d > 1$ 时，将数组分成 $\gcd(n, d)$ 组，每组独立处理，可降低问题复杂度。

### 可拓展之处
同类型题或类似算法套路包括涉及位运算和数组操作的题目，如判断数组经过某种位运算和变换后是否满足特定条件，或计算达到特定条件所需的步数等。可以通过类似的 BFS 或分组处理的方法解决。

### 推荐题目
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)

### 个人心得摘录与总结
- **Fire_flame**：想到暴力做法并进行了两个小优化，但仍有数据卡，不太推荐暴力做法。总结：暴力做法可能在某些数据下不适用，需要考虑更优的算法。

---
处理用时：100.34秒