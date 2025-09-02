# 题目信息

# Maximum And Queries (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ and $ q $ , the memory and time limits. You can make hacks only if all versions of the problem are solved.

Theofanis really likes to play with the bits of numbers. He has an array $ a $ of size $ n $ and an integer $ k $ . He can make at most $ k $ operations in the array. In each operation, he picks a single element and increases it by $ 1 $ .

He found the maximum [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) that array $ a $ can have after at most $ k $ operations.

Theofanis has put a lot of work into finding this value and was very happy with his result. Unfortunately, Adaś, being the evil person that he is, decided to bully him by repeatedly changing the value of $ k $ .

Help Theofanis by calculating the maximum possible [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) for $ q $ different values of $ k $ . Note that queries are independent.

## 说明/提示

In the first test case, in the first query, we add $ 1 $ in the first and last elements of the array.

Thus, the array becomes $ [2,3,7,6] $ with bitwise AND equal to $ 2 $ .

In the second test case, in the first query, we add $ 1 $ in the first element, $ 5 $ in the second, and $ 3 $ in the third and now all the elements are equal to $ 5 $ .

## 样例 #1

### 输入

```
4 2
1 3 7 5
2
10```

### 输出

```
2
6```

## 样例 #2

### 输入

```
3 5
4 0 2
9
8
17
1
3```

### 输出

```
5
4
7
0
1```

## 样例 #3

### 输入

```
1 2
10
5
2318381298321```

### 输出

```
15
2318381298331```

# AI分析结果

### 题目内容重写

#### 最大按位与查询（简单版）

**题目描述**

这是该问题的简单版本。两个版本之间的唯一区别在于对 $n$ 和 $q$ 的限制，以及内存和时间限制。只有当所有版本的问题都解决时，你才能进行 hack。

Theofanis 非常喜欢玩弄数字的二进制位。他有一个大小为 $n$ 的数组 $a$ 和一个整数 $k$。他最多可以对数组进行 $k$ 次操作。在每次操作中，他选择一个元素并将其增加 $1$。

他找到了在进行最多 $k$ 次操作后，数组 $a$ 可以达到的最大[按位与](https://en.wikipedia.org/wiki/Bitwise_operation#AND)值。

Theofanis 花了很大功夫找到了这个值，并对结果非常满意。不幸的是，Adaś 决定通过反复改变 $k$ 的值来欺负他。

帮助 Theofanis 计算 $q$ 个不同 $k$ 值下的最大可能[按位与](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。注意，查询是独立的。

**说明/提示**

在第一个测试用例中，在第一个查询中，我们将数组的第一个和最后一个元素增加 $1$。

因此，数组变为 $[2,3,7,6]$，按位与结果为 $2$。

在第二个测试用例中，在第一个查询中，我们将第一个元素增加 $1$，第二个元素增加 $5$，第三个元素增加 $3$，现在所有元素都等于 $5$。

**样例 #1**

**输入**

```
4 2
1 3 7 5
2
10
```

**输出**

```
2
6
```

**样例 #2**

**输入**

```
3 5
4 0 2
9
8
17
1
3
```

**输出**

```
5
4
7
0
1
```

**样例 #3**

**输入**

```
1 2
10
5
2318381298321
```

**输出**

```
15
2318381298331
```

### 算法分类
贪心、位运算

### 综合分析与结论

本题的核心在于通过贪心策略，从高位到低位逐位确定最大按位与值。由于按位与操作的性质，只有当所有数的某一位都为1时，结果的该位才能为1。因此，我们可以从最高位开始，逐位检查是否可以通过不超过 $k$ 次操作使所有数的该位变为1。如果可以，则将该位设为1，并扣除相应的操作次数；否则，跳过该位。

### 所选高分题解

#### 题解1：作者：tbdsh (赞：6)
**星级：5星**
**关键亮点：**
- 从高位到低位逐位贪心，确保每一步操作都能最大化按位与结果。
- 代码清晰，逻辑严谨，时间复杂度为 $O(n \times q)$，适合题目要求。

**核心代码：**
```cpp
for (int i = 60; i >= 0; i--) {
    int p = 1ll << i, cnt = 0;
    for (int j = 1; j <= n; j++) {
        if (!((b[j] >> i) & 1)) {
            int p = ((b[j] >> i) + 1) << i;
            cnt += p - b[j];
            b[j] = p;
        }
        if (cnt > x) break;
    }
    if (cnt <= x) x -= cnt;
    else for (int j = 1; j <= n; j++) b[j] = c[j];
}
```

#### 题解2：作者：FQR_ (赞：6)
**星级：5星**
**关键亮点：**
- 详细解释了贪心策略的合理性，从高位到低位逐位确定最大按位与值。
- 代码实现简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
for(ll i = 62; i >= 0; i--) {
    ll p = 0;
    bool flg = 0;
    for(int j = 1; j <= n; j++) {
        if((a[j] & (1ll << i)) == 0) {
            p += (1ll << i) - a[j];
            if(p > k) break;
        }
    }
    if(p <= k) ans += (1ll << i), k -= p, flg = 1;
    for(int j = 1; j <= n; j++) {
        if((a[j] & (1ll<<i)) == 0 && flg) a[j] = 1ll << i;
        if((a[j] & (1ll<<i)) != 0) a[j] -= (1ll << i);
    }
}
```

#### 题解3：作者：Special_Tony (赞：0)
**星级：4星**
**关键亮点：**
- 通过从高位到低位逐位贪心，确保每一步操作都能最大化按位与结果。
- 代码实现简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
for (int i = 60; ~i; --i) {
    s = 0;
    for (int j = 0; j < n; ++j)
        if (b[j] >> i & 1) c[j] = b[j];
        else {
            c[j] = (b[j] >> i) + 1 << i;
            s += c[j] - b[j];
            if (s > k) goto end;
        }
    k -= s;
    for (int j = 0; j < n; ++j) b[j] = c[j];
end:;
}
```

### 最优关键思路或技巧
1. **高位优先贪心**：从最高位开始逐位确定最大按位与值，确保每一步操作都能最大化结果。
2. **操作次数管理**：在每一步操作中，计算使所有数的某一位变为1所需的操作次数，并与剩余操作次数进行比较，决定是否进行该操作。

### 可拓展之处
- **类似问题**：可以扩展到其他位运算问题，如最大按位或、最小按位异或等。
- **优化思路**：对于更大规模的数据，可以考虑使用更高效的数据结构或算法来优化操作次数的计算。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：50.45秒