# 题目信息

# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# AI分析结果

### 题目内容
# 瓦西里熊与序列

## 题目描述
瓦西里熊得到了一个正整数序列 $a_{1},a_{2},\cdots,a_{n}$ 。瓦西里熊想要在一张纸上写下几个数字，使得他写下的数字的美观度最大。

写下的数字 $b_{1},b_{2},\cdots,b_{k}$ 的美观度是这样一个最大的非负整数 $v$ ，使得数字 $b_{1}\ \text{and}\ b_{2}\ \text{and}\ \cdots\ \text{and}\ b_{k}$ 能被 $2^{v}$ 整除且没有余数。如果这样的数字 $v$ 不存在（即对于任意非负整数 $v$ ，数字 $b_{1}\ \text{and}\ b_{2}\ \text{and}\ \cdots\ \text{and}\ b_{k}$ 都能被 $2^{v}$ 整除且没有余数），那么写下的数字的美观度等于 -1 。

告诉这只熊应该写下哪些数字，以便写下的数字的美观度最大。如果有多种写数字的方法，你需要选择熊写下尽可能多数字的那种方法。

这里表达式 $x\ \text{and}\ y$ 表示对数字 $x$ 和 $y$ 应用按位与运算。在编程语言 C++ 和 Java 中，此运算用 “&” 表示，在 Pascal 中用 “and” 表示。

## 样例 #1
### 输入
```
5
1 2 3 4 5
```
### 输出
```
2
4 5
```

## 样例 #2
### 输入
```
3
1 2 4
```
### 输出
```
1
4
```

### 综合分析与结论
- **思路对比**：两位作者思路基本一致，都是从高位到低位倒序枚举 $v$（对应二进制中的幂次），寻找满足条件的最大 $v$ 以及对应的数字集合。
- **算法要点**：通过按位与运算判断每个数的二进制第 $v$ 位是否为 1，若为 1 则考虑将其纳入结果集合。同时要保证这些数按位与后的结果除了第 $v$ 位，前面的位都为 0，这样才能保证整除 $2^{v}$。
- **解决难点**：难点在于如何通过按位与运算找到符合整除 $2^{v}$ 条件的数字集合。两位作者都利用按位与运算的特性，通过逐步累积按位与结果并判断余数或结果是否符合条件来解决。

### 题解
- **作者：Graphcity（3星）**
    - **关键亮点**：思路较清晰，代码结构完整，使用 `vector` 记录方案，逻辑较为直观。
    - **核心代码实现思想**：倒序枚举 $v$，对于每个 $v$ 遍历数组，找出二进制第 $v$ 位为 1 的数，计算这些数按位与的结果 `res` 并判断是否能被 $2^{v}$ 整除，若能则输出方案。
    - **核心代码片段**：
```cpp
for(register int i=30;i>=0;--i)
{
    int now=0,res=0; 
    v.clear();
    for(register int j=1;j<=n;++j)
        if(a[j]&(1<<i)) 
        {
            now++,res&=a[j],v.push_back(a[j]);
            if(now==1) res=a[j];
        }
    if(res%(1<<i)==0 && now) 
    {
        printf("%d\n",now);
        for(auto i:v) printf("%d ",i);
        return 0;
    }
}
```
- **作者：Rye_Catcher（3星）**
    - **关键亮点**：代码简洁，利用贪心思想从高位到低位枚举 $k$，并巧妙通过按位与运算判断条件。
    - **核心代码实现思想**：同样倒序枚举 $k$，对于每个 $k$ 遍历数组，找出二进制第 $k$ 位为 1 的数，计算这些数按位与的结果 `y` 并判断是否为 0，若为 0 则输出方案。
    - **核心代码片段**：
```cpp
for(ri k=30;k>=0;k--){
    x=(1<<k);
    y=x-1;
    ans=0;
    for(ri i=1;i<=n;i++){
        if(a[i]&x){
            y=y&a[i];
            q[++ans]=a[i];
        }
    }
    if(y==0){
        printf("%d\n",ans);
        for(ri i=1;i<=ans;i++){
            printf("%d ",q[i]);
        }
        puts("");
        return 0;
    }
}
```

### 最优关键思路或技巧
倒序枚举二进制幂次，利用按位与运算判断数字的二进制位情况，并通过累积按位与结果判断是否满足整除条件，这是解决本题的关键技巧。同时，贪心选择二进制对应位为 1 的数，以满足美观度最大且数字数量尽可能多的要求。

### 可拓展之处
同类型题通常围绕位运算、贪心策略以及数论知识展开。例如，给定一些数，要求通过特定位运算组合得到满足某种整除条件或最值条件的结果。类似算法套路是先分析题目条件与位运算的关系，通过枚举相关参数（如本题中的二进制幂次），利用位运算特性进行筛选和判断。

### 洛谷相似题目
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)：考察位运算基础操作。
- [P1876 开灯](https://www.luogu.com.cn/problem/P1876)：结合位运算和逻辑判断解决实际问题。
- [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)：在查找问题中运用位运算优化判断条件。 

---
处理用时：27.16秒