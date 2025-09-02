# 题目信息

# Removing Smallest Multiples

## 题目描述

You are given a set $ S $ , which contains the first $ n $ positive integers: $ 1, 2, \ldots, n $ .

You can perform the following operation on $ S $ any number of times (possibly zero):

- Choose a positive integer $ k $ where $ 1 \le k \le n $ , such that there exists a multiple of $ k $ in $ S $ . Then, delete the smallest multiple of $ k $ from $ S $ . This operation requires a cost of $ k $ .

You are given a set $ T $ , which is a subset of $ S $ . Find the minimum possible total cost of operations such that $ S $ would be transformed into $ T $ . We can show that such a transformation is always possible.

## 说明/提示

In the first test case, we shall not perform any operations as $ S $ is already equal to $ T $ , which is the set $ \{1, 2, 3, 4, 5, 6\} $ .

In the second test case, initially, $ S = \{1, 2, 3, 4, 5, 6, 7\} $ , and $ T = \{1, 2, 4, 7\} $ . We shall perform the following operations:

1. Choose $ k=3 $ , then delete $ 3 $ from $ S $ .
2. Choose $ k=3 $ , then delete $ 6 $ from $ S $ .
3. Choose $ k=5 $ , then delete $ 5 $ from $ S $ .

The total cost is $ 3+3+5 = 11 $ . It can be shown that this is the smallest cost possible.

In the third test case, initially, $ S = \{1, 2, 3, 4\} $ and $ T = \{\} $ (empty set). We shall perform $ 4 $ operations of $ k=1 $ to delete $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ .

In the fourth test case, initially, $ S = \{1, 2, 3, 4\} $ and $ T = \{3\} $ . We shall perform two operations with $ k=1 $ to delete $ 1 $ and $ 2 $ , then perform one operation with $ k=2 $ to delete $ 4 $ .

## 样例 #1

### 输入

```
6
6
111111
7
1101001
4
0000
4
0010
8
10010101
15
110011100101100```

### 输出

```
0
11
4
4
17
60```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

给定一个集合 $S$，其中包含前 $n$ 个正整数：$1, 2, \ldots, n$。

你可以对 $S$ 进行任意次数的操作（包括零次）：

- 选择一个正整数 $k$，其中 $1 \le k \le n$，且 $S$ 中存在 $k$ 的倍数。然后，删除 $S$ 中最小的 $k$ 的倍数。此操作的代价为 $k$。

给定一个集合 $T$，它是 $S$ 的子集。找到将 $S$ 转换为 $T$ 的最小总操作代价。可以证明这种转换总是可能的。

#### 说明/提示

在第一个测试用例中，$S$ 已经等于 $T$，即集合 $\{1, 2, 3, 4, 5, 6\}$，因此不需要进行任何操作。

在第二个测试用例中，初始时 $S = \{1, 2, 3, 4, 5, 6, 7\}$，$T = \{1, 2, 4, 7\}$。我们将进行以下操作：

1. 选择 $k=3$，然后删除 $3$ 从 $S$ 中。
2. 选择 $k=3$，然后删除 $6$ 从 $S$ 中。
3. 选择 $k=5$，然后删除 $5$ 从 $S$ 中。

总代价为 $3+3+5 = 11$。可以证明这是最小的可能代价。

在第三个测试用例中，初始时 $S = \{1, 2, 3, 4\}$，$T = \{\}$（空集）。我们将进行 $4$ 次操作，每次选择 $k=1$，删除 $1$、$2$、$3$ 和 $4$。

在第四个测试用例中，初始时 $S = \{1, 2, 3, 4\}$，$T = \{3\}$。我们将进行两次操作，每次选择 $k=1$，删除 $1$ 和 $2$，然后进行一次操作，选择 $k=2$，删除 $4$。

#### 样例 #1

##### 输入

```
6
6
111111
7
1101001
4
0000
4
0010
8
10010101
15
110011100101100
```

##### 输出

```
0
11
4
4
17
60
```

### 算法分类

贪心

### 题解分析与结论

本题的核心思路是利用贪心算法，通过类似埃氏筛的方法，选择最小的 $k$ 来删除其最小的倍数，从而最小化总代价。各题解的主要思路相似，但在实现细节和代码优化上有所不同。

### 所选高星题解

#### 题解1：作者：FFTotoro (赞：8)

**星级：4星**

**关键亮点：**
- 使用了类似埃氏筛的方法，从最小的 $k$ 开始，逐步删除其倍数。
- 通过标记已删除的数，避免重复计算。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    if(!(s[i-1]&1)){
        if(!b[i-1])c+=1ll*i;
        for(int j=2;i*j<=n;j++){
            if(!(s[i*j-1]&1)){
                if(!b[i*j-1])c+=1ll*i,b[i*j-1]=true;
            }
            else break;
        }
    }
}
```
**核心思想：**
- 遍历每个数 $i$，如果 $i$ 不在 $T$ 中，则用 $i$ 删除其所有倍数，并累加代价。

#### 题解2：作者：Dregen_Yor (赞：3)

**星级：4星**

**关键亮点：**
- 采用了贪心策略，从 $1$ 开始遍历，确保每次操作的最小代价。
- 通过标记已删除的数，避免重复计算。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    for(int j=i;j<=n;j+=i){
        if(T[j-1]=='1'){
            if(!v[j]){
                sum++;
            }
            v[j]=1;
            break;
        }
        else{
            if(!v[j]){
                sum++;
                ans+=i;
            }
            v[j]=1;
        }
        if(sum==n){
            break;
        }
    }
}
```
**核心思想：**
- 遍历每个数 $i$，如果 $i$ 不在 $T$ 中，则用 $i$ 删除其所有倍数，并累加代价。

#### 题解3：作者：Cczzyy20150005 (赞：3)

**星级：4星**

**关键亮点：**
- 采用了贪心策略，从最小的 $k$ 开始，逐步删除其倍数。
- 通过标记已删除的数，避免重复计算。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    if(a[i]==0){
        int now=i;
        while(a[now]!=1&&now<=n){
            if(vis[now]==1)ans+=i;
            vis[now]=0;
            now+=i;
        }
    }
}
```
**核心思想：**
- 遍历每个数 $i$，如果 $i$ 不在 $T$ 中，则用 $i$ 删除其所有倍数，并累加代价。

### 最优关键思路

- **贪心策略**：从最小的 $k$ 开始，逐步删除其倍数，确保每次操作的最小代价。
- **标记已删除的数**：通过标记已删除的数，避免重复计算，提高效率。
- **类似埃氏筛的方法**：通过遍历每个数并删除其倍数，确保每次操作的最小代价。

### 拓展思路

- **类似问题**：可以考虑其他需要最小化操作代价的问题，如最小化删除某些元素的代价。
- **优化方向**：可以进一步优化标记和遍历的效率，减少不必要的计算。

### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
3. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)

---
处理用时：41.64秒