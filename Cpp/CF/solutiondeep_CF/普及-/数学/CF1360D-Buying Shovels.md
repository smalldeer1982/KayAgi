# 题目信息

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733```

### 输出

```
2
8
1
999999733
1```

# AI分析结果

### 题目内容重写
Polycarp 想要购买恰好 $n$ 把铲子。商店出售铲子的包装，商店有 $k$ 种类型的包装：第 $i$ 种类型的包装包含恰好 $i$ 把铲子（$1 \le i \le k$）。商店每种类型的包装都有无限数量。

Polycarp 想要选择一种类型的包装，然后购买若干（一个或多个）该类型的包装。Polycarp 需要购买多少包才能恰好得到 $n$ 把铲子？

例如，如果 $n=8$ 且 $k=7$，那么 Polycarp 将购买 $2$ 包 $4$ 把铲子的包装。

帮助 Polycarp 找到他需要购买的最小包数，给定他：

- 将恰好购买 $n$ 把铲子；
- 他购买的所有包装的大小都相同，并且每个包装中的铲子数量是 $1$ 到 $k$ 之间的整数。

### 题解分析与结论
本题的核心是找到 $n$ 的最大因数且不超过 $k$，然后计算 $n$ 除以这个因数的结果。由于 $n$ 和 $k$ 的范围都很大（$1 \le n, k \le 10^9$），直接暴力枚举会超时，因此需要优化。

大多数题解都采用了枚举到 $\sqrt{n}$ 的方法，通过检查 $i$ 和 $n/i$ 是否为 $n$ 的因数，并确保它们不超过 $k$，从而找到符合条件的最大因数。这种方法的时间复杂度为 $O(\sqrt{n})$，能够有效解决问题。

### 精选题解
#### 题解1：作者：丧黑福造 (赞：8)
**星级：5星**
**关键亮点：**
- 简洁明了地解释了题目要求，并给出了清晰的算法思路。
- 代码实现高效，通过枚举到 $\sqrt{n}$ 来找到最大因数，并确保其不超过 $k$。
- 代码可读性强，使用了 `min` 函数来更新最小包数。

**核心代码：**
```cpp
for (register int i = 1; i * i <= n; i ++) {
    if (n % i == 0) {
        if (i <= k)
            ans = min (ans, n/i);
        if (n/i <= k)
            ans = min (ans, i);
    }
}
```

#### 题解2：作者：andyli (赞：4)
**星级：4星**
**关键亮点：**
- 提供了两种不同的实现方式，一种是直接枚举，另一种是使用 `std::upper_bound` 来查找最大因数。
- 代码结构清晰，逻辑严谨，适合不同编程习惯的读者。

**核心代码：**
```cpp
for (int i = 1; i * i <= n; i++)
    if (n % i == 0)
        chkmax(ans, i <= k ? i : 0, n / i <= k ? n / i : 0);
```

#### 题解3：作者：_GW_ (赞：2)
**星级：4星**
**关键亮点：**
- 通过将问题转化为求 $n$ 的最大且不超过 $k$ 的因数，简化了问题。
- 代码实现简洁，使用了 `vector` 来存储所有因数，并通过排序找到符合条件的最大因数。

**核心代码：**
```cpp
for(int i=1;i<=sqrt(n);i++) {
    if(n%i==0) {
        v.push_back(i);
        if(i*i!=n) v.push_back(n/i);
    }
}
sort(v.begin(),v.end());
for(int i=v.size()-1;i>=0;i--) {
    if(v[i]<=m) {
        cout<<n/v[i]<<endl;
        return;
    }
}
```

### 最优关键思路与技巧
1. **因数成对出现**：通过枚举到 $\sqrt{n}$，可以高效地找到所有因数，避免了全范围枚举。
2. **最小化包数**：通过找到最大且不超过 $k$ 的因数，可以最小化包数。
3. **代码优化**：使用 `min` 函数和 `vector` 等数据结构，可以提高代码的可读性和效率。

### 可拓展之处
- **类似问题**：类似的问题可以出现在其他需要找到最大或最小因数的场景中，如分解质因数、求最大公约数等。
- **算法套路**：枚举到 $\sqrt{n}$ 的思路可以应用于其他需要高效查找因数的问题。

### 推荐题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)

### 个人心得摘录
- **调试经历**：在枚举时，需要注意因数的成对出现，避免重复计算。
- **踩坑教训**：初始时没有考虑到 $i$ 和 $n/i$ 都需要检查，导致部分测试用例未通过。
- **顿悟感想**：通过将问题转化为因数查找，大大简化了问题的复杂度。

---
处理用时：41.28秒