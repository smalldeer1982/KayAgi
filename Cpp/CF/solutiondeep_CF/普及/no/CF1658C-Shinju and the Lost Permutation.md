# 题目信息

# Shinju and the Lost Permutation

## 题目描述

Shinju loves permutations very much! Today, she has borrowed a permutation $ p $ from Juju to play with.

The $ i $ -th cyclic shift of a permutation $ p $ is a transformation on the permutation such that $ p = [p_1, p_2, \ldots, p_n]  $ will now become $  p = [p_{n-i+1}, \ldots, p_n, p_1,p_2, \ldots, p_{n-i}] $ .

Let's define the power of permutation $ p $ as the number of distinct elements in the prefix maximums array $ b $ of the permutation. The prefix maximums array $ b $ is the array of length $ n $ such that $ b_i = \max(p_1, p_2, \ldots, p_i) $ . For example, the power of $ [1, 2, 5, 4, 6, 3] $ is $ 4 $ since $ b=[1,2,5,5,6,6] $ and there are $ 4 $ distinct elements in $ b $ .

Unfortunately, Shinju has lost the permutation $ p $ ! The only information she remembers is an array $ c $ , where $ c_i $ is the power of the $ (i-1) $ -th cyclic shift of the permutation $ p $ . She's also not confident that she remembers it correctly, so she wants to know if her memory is good enough.

Given the array $ c $ , determine if there exists a permutation $ p $ that is consistent with $ c $ . You do not have to construct the permutation $ p $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3, 4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation $ [1] $ satisfies the array $ c $ .

In the second test case, the permutation $ [2,1] $ satisfies the array $ c $ .

In the fifth test case, the permutation $ [5, 1, 2, 4, 6, 3] $ satisfies the array $ c $ . Let's see why this is true.

- The zeroth cyclic shift of $ p $ is $ [5, 1, 2, 4, 6, 3] $ . Its power is $ 2 $ since $ b = [5, 5, 5, 5, 6, 6] $ and there are $ 2 $ distinct elements — $ 5 $ and $ 6 $ .
- The first cyclic shift of $ p $ is $ [3, 5, 1, 2, 4, 6] $ . Its power is $ 3 $ since $ b=[3,5,5,5,5,6] $ .
- The second cyclic shift of $ p $ is $ [6, 3, 5, 1, 2, 4] $ . Its power is $ 1 $ since $ b=[6,6,6,6,6,6] $ .
- The third cyclic shift of $ p $ is $ [4, 6, 3, 5, 1, 2] $ . Its power is $ 2 $ since $ b=[4,6,6,6,6,6] $ .
- The fourth cyclic shift of $ p $ is $ [2, 4, 6, 3, 5, 1] $ . Its power is $ 3 $ since $ b = [2, 4, 6, 6, 6, 6] $ .
- The fifth cyclic shift of $ p $ is $ [1, 2, 4, 6, 3, 5] $ . Its power is $ 4 $ since $ b = [1, 2, 4, 6, 6, 6] $ .

Therefore, $ c = [2, 3, 1, 2, 3, 4] $ .

In the third, fourth, and sixth testcases, we can show that there is no permutation that satisfies array $ c $ .

## 样例 #1

### 输入

```
6
1
1
2
1 2
2
2 2
6
1 2 4 6 3 5
6
2 3 1 2 3 4
3
3 2 1```

### 输出

```
YES
YES
NO
NO
YES
NO```

# AI分析结果

### 题目内容重写

#### Shinju和丢失的排列

Shinju非常喜欢排列！今天，她从Juju那里借了一个排列$p$来玩。

排列$p$的第$i$次循环移位是对排列$p$进行的一种变换，使得$p = [p_1, p_2, \ldots, p_n]$变为$p = [p_{n-i+1}, \ldots, p_n, p_1,p_2, \ldots, p_{n-i}]$。

我们定义排列$p$的“权值”为前缀最大值数组$b$中不同元素的个数。前缀最大值数组$b$是一个长度为$n$的数组，其中$b_i = \max(p_1, p_2, \ldots, p_i)$。例如，排列$[1, 2, 5, 4, 6, 3]$的权值为$4$，因为$b=[1,2,5,5,6,6]$，其中有$4$个不同的元素。

不幸的是，Shinju丢失了排列$p$！她唯一记得的是一个数组$c$，其中$c_i$是排列$p$的第$(i-1)$次循环移位的权值。她也不太确定自己是否记对了，所以想知道她的记忆是否足够好。

给定数组$c$，判断是否存在一个与$c$一致的排列$p$。你不需要构造出排列$p$。

一个排列是一个由$1$到$n$的$n$个不同整数组成的数组，顺序任意。例如，$[2,3,1,5,4]$是一个排列，但$[1,2,2]$不是排列（$2$在数组中出现了两次），$[1,3,4]$也不是排列（$n=3$但数组中出现了$4$）。

### 说明/提示

在第一个测试用例中，排列$[1]$满足数组$c$。

在第二个测试用例中，排列$[2,1]$满足数组$c$。

在第五个测试用例中，排列$[5, 1, 2, 4, 6, 3]$满足数组$c$。让我们看看为什么这是正确的。

- $p$的第$0$次循环移位是$[5, 1, 2, 4, 6, 3]$。它的权值是$2$，因为$b = [5, 5, 5, 5, 6, 6]$，其中有$2$个不同的元素——$5$和$6$。
- $p$的第$1$次循环移位是$[3, 5, 1, 2, 4, 6]$。它的权值是$3$，因为$b=[3,5,5,5,5,6]$。
- $p$的第$2$次循环移位是$[6, 3, 5, 1, 2, 4]$。它的权值是$1$，因为$b=[6,6,6,6,6,6]$。
- $p$的第$3$次循环移位是$[4, 6, 3, 5, 1, 2]$。它的权值是$2$，因为$b=[4,6,6,6,6,6]$。
- $p$的第$4$次循环移位是$[2, 4, 6, 3, 5, 1]$。它的权值是$3$，因为$b = [2, 4, 6, 6, 6, 6]$。
- $p$的第$5$次循环移位是$[1, 2, 4, 6, 3, 5]$。它的权值是$4$，因为$b = [1, 2, 4, 6, 6, 6]$。

因此，$c = [2, 3, 1, 2, 3, 4]$。

在第三、第四和第六个测试用例中，我们可以证明没有满足数组$c$的排列。

### 样例 #1

#### 输入

```
6
1
1
2
1 2
2
2 2
6
1 2 4 6 3 5
6
2 3 1 2 3 4
3
3 2 1```

#### 输出

```
YES
YES
NO
NO
YES
NO```

### 算法分类

构造

### 题解分析与结论

#### 题解1：JS_TZ_ZHR

**评分：4星**

**关键亮点：**
1. 明确指出了有解的必要条件：数组$c$中必须有且仅有一个$1$。
2. 通过循环移位后的权值变化规律，排除了不合法的情况。
3. 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1,pos=p;i<=n;i++){
    int nxt=pos+1;
    if(nxt==n+1)nxt=1;
    if(a[nxt]-a[pos]>1)flag=0;
    pos=nxt;
}
```

**个人心得：**
作者通过观察循环移位后的权值变化规律，合理猜想了排除不合法情况的方法，并通过代码实现了这一逻辑。

#### 题解2：E1_de5truct0r

**评分：3星**

**关键亮点：**
1. 同样指出了数组$c$中必须有且仅有一个$1$的必要条件。
2. 通过数学证明，解释了每次循环移位后权值变化不超过$1$的原因。

**核心代码：**
无具体代码实现，但思路清晰。

**个人心得：**
作者通过数学证明，解释了每次循环移位后权值变化不超过$1$的原因，但没有给出具体的代码实现。

### 最优关键思路

1. **必要条件**：数组$c$中必须有且仅有一个$1$，这是判断是否存在符合条件排列的关键。
2. **权值变化规律**：每次循环移位后，权值的变化不超过$1$，这是排除不合法情况的重要依据。

### 可拓展之处

1. **类似题目**：可以拓展到其他与排列循环移位相关的题目，如寻找特定排列的循环移位后的性质。
2. **算法优化**：可以通过进一步优化代码，减少不必要的循环和判断，提高代码效率。

### 推荐题目

1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：41.02秒