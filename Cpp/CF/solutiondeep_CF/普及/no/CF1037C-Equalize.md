# 题目信息

# Equalize

## 题目描述

You are given two binary strings $ a $ and $ b $ of the same length. You can perform the following two operations on the string $ a $ :

- Swap any two bits at indices $ i $ and $ j $ respectively ( $ 1 \le i, j \le n $ ), the cost of this operation is $ |i - j| $ , that is, the absolute difference between $ i $ and $ j $ .
- Select any arbitrary index $ i $ ( $ 1 \le i \le n $ ) and flip (change $ 0 $ to $ 1 $ or $ 1 $ to $ 0 $ ) the bit at this index. The cost of this operation is $ 1 $ .

Find the minimum cost to make the string $ a $ equal to $ b $ . It is not allowed to modify string $ b $ .

## 说明/提示

In the first example, one of the optimal solutions is to flip index $ 1 $ and index $ 3 $ , the string $ a $ changes in the following way: "100" $ \to $ "000" $ \to $ "001". The cost is $ 1 + 1 = 2 $ .

The other optimal solution is to swap bits and indices $ 1 $ and $ 3 $ , the string $ a $ changes then "100" $ \to $ "001", the cost is also $ |1 - 3| = 2 $ .

In the second example, the optimal solution is to swap bits at indices $ 2 $ and $ 3 $ , the string $ a $ changes as "0101" $ \to $ "0011". The cost is $ |2 - 3| = 1 $ .

## 样例 #1

### 输入

```
3
100
001
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0101
0011
```

### 输出

```
1
```

# AI分析结果

### 题目内容
#### Equalize

**题目描述**

给定两个长度相同的二进制字符串 $a$ 和 $b$。你可以对字符串 $a$ 进行以下两种操作：

1. 交换任意两个位置 $i$ 和 $j$ 的比特（$1 \le i, j \le n$），该操作的代价为 $|i - j|$，即 $i$ 和 $j$ 的绝对差。
2. 选择任意一个位置 $i$（$1 \le i \le n$）并翻转该位置的比特（将 $0$ 变为 $1$ 或将 $1$ 变为 $0$）。该操作的代价为 $1$。

求将字符串 $a$ 变为字符串 $b$ 的最小代价。不允许修改字符串 $b$。

**说明/提示**

在第一个样例中，一个最优解是翻转位置 $1$ 和位置 $3$，字符串 $a$ 的变化如下："100" $\to$ "000" $\to$ "001"。代价为 $1 + 1 = 2$。

另一个最优解是交换位置 $1$ 和 $3$ 的比特，字符串 $a$ 的变化如下："100" $\to$ "001"，代价为 $|1 - 3| = 2$。

在第二个样例中，最优解是交换位置 $2$ 和 $3$ 的比特，字符串 $a$ 的变化如下："0101" $\to$ "0011"。代价为 $|2 - 3| = 1$。

**样例 #1**

**输入**

```
3
100
001
```

**输出**

```
2
```

**样例 #2**

**输入**

```
4
0101
0011
```

**输出**

```
1
```

### 算法分类
贪心

### 题解分析与结论
这道题的核心思路是通过贪心策略来最小化操作代价。大多数题解都采用了类似的思路：优先使用交换操作（操作2），因为它在某些情况下可以以更低的代价同时修正两个位置的比特。只有当交换操作无法使用时，才使用翻转操作（操作1）。

### 评分较高的题解

#### 题解1：作者：雅儿贝德 (赞：3)
**星级：4**
**关键亮点：**
- 思路清晰，直接指出了贪心策略的核心：优先使用交换操作，因为它在某些情况下可以以更低的代价同时修正两个位置的比特。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    if(a[i]!=b[i] && a[i+1]!=b[i+1] && a[i]!=a[i+1] && i+1<=n){
        ans++;
        i++;
    }else ans+=(a[i]!=b[i]);
}
```

#### 题解2：作者：sto__Liyhzh__orz (赞：2)
**星级：4**
**关键亮点：**
- 与题解1思路相似，但代码实现略有不同，同样清晰易懂。
- 通过遍历字符串，优先使用交换操作，确保最小化代价。

**核心代码：**
```cpp
for(int i=0;i<=len-1;i++){
    if(i<=len-2 && s1[i]!=s2[i] && s1[i]!=s1[i+1] && s1[i+1]!=s2[i+1]){
        cnt++;
        i++;
    }
    else cnt+=(s1[i]!=s2[i]);
}
```

#### 题解3：作者：Ousmane_Dembele (赞：2)
**星级：4**
**关键亮点：**
- 思路与前面题解一致，但代码实现更为简洁。
- 通过遍历字符串，优先使用交换操作，确保最小化代价。

**核心代码：**
```cpp
for(int i=1;i<=n;i++){
    if(a[i]==b[i])continue;
    sum++;
    if(i==n)continue;
    if(a[i]==b[i+1]&&a[i+1]==b[i]){
        a[i]=b[i];
        a[i+1]=b[i+1];
    }
}
```

### 最优关键思路或技巧
- **贪心策略**：优先使用交换操作，因为它在某些情况下可以以更低的代价同时修正两个位置的比特。
- **遍历字符串**：通过遍历字符串，逐个检查是否需要使用交换或翻转操作，确保最小化代价。

### 可拓展之处
- 类似的问题可以扩展到其他类型的字符串匹配问题，如字符替换、插入、删除等操作的最小代价问题。
- 可以进一步优化算法，考虑更复杂的交换操作或翻转操作的组合。

### 推荐题目
1. [P1037 字符串变换](https://www.luogu.com.cn/problem/P1037)
2. [P1038 字符串变换2](https://www.luogu.com.cn/problem/P1038)
3. [P1039 字符串变换3](https://www.luogu.com.cn/problem/P1039)

### 个人心得摘录
- **雅儿贝德**：操作1只在不能使用操作2的时候进行，因为操作2可以将2个数字匹配，而操作1只能匹配1个，很明显要尽可能使用操作2。
- **sto__Liyhzh__orz**：对于每个 $s1_i$，$s1_{i+1}$，$s2_i$，$s2_{i+1}$，是不是互不相同，若是的话做操作2，不是的话若 $s1_i$ 不相等 $s2_i$ 做操作1，否则啥也不做。

---
处理用时：39.77秒