# 题目信息

# Array Cloning Technique

## 题目描述

You are given an array $ a $ of $ n $ integers. Initially there is only one copy of the given array.

You can do operations of two types:

1. Choose any array and clone it. After that there is one more copy of the chosen array.
2. Swap two elements from any two copies (maybe in the same copy) on any positions.

You need to find the minimal number of operations needed to obtain a copy where all elements are equal.

## 说明/提示

In the first test case all elements in the array are already equal, that's why the answer is $ 0 $ .

In the second test case it is possible to create a copy of the given array. After that there will be two identical arrays:

 $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ] $

After that we can swap elements in a way so all zeroes are in one array:

 $ [ \ 0 \ \underline{0} \ \underline{0} \ 3 \ 7 \ 0 \ ] $ and $ [ \ \underline{1} \ 1 \ 3 \ 3 \ 7 \ \underline{3} \ ] $

Now let's create a copy of the first array:

 $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ , $ [ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $

Let's swap elements in the first two copies:

 $ [ \ 0 \ 0 \ 0 \ \underline{0} \ \underline{0} \ 0 \ ] $ , $ [ \ \underline{3} \ \underline{7} \ 0 \ 3 \ 7 \ 0 \ ] $ and $ [ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ] $ .

Finally, we made a copy where all elements are equal and made $ 6 $ operations.

It can be proven that no fewer operations are enough.

## 样例 #1

### 输入

```
6
1
1789
6
0 1 3 3 7 0
2
-1000000000 1000000000
4
4 3 2 1
5
2 5 7 6 3
7
1 1 1 1 1 1 1```

### 输出

```
0
6
2
5
7
0```

# AI分析结果

### 题目内容重写

#### 数组克隆技术

**题目描述**

给定一个包含 $n$ 个整数的数组 $a$。初始时只有一个该数组的副本。

你可以进行以下两种操作：

1. 选择任意一个数组并克隆它。克隆后，会多出一个该数组的副本。
2. 交换任意两个副本（可以是同一个副本）中的任意两个元素的位置。

你需要找到使某个副本中的所有元素都相等所需的最少操作次数。

**说明/提示**

在第一个测试用例中，数组中的所有元素已经相等，因此答案为 $0$。

在第二个测试用例中，可以克隆给定的数组。克隆后会有两个相同的数组：

$[ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ]$ 和 $[ \ 0 \ 1 \ 3 \ 3 \ 7 \ 0 \ ]$

然后可以通过交换元素的方式，使得所有 $0$ 都在一个数组中：

$[ \ 0 \ \underline{0} \ \underline{0} \ 3 \ 7 \ 0 \ ]$ 和 $[ \ \underline{1} \ 1 \ 3 \ 3 \ 7 \ \underline{3} \ ]$

接下来，克隆第一个数组：

$[ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ]$ , $[ \ 0 \ 0 \ 0 \ 3 \ 7 \ 0 \ ]$ 和 $[ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ]$

最后，交换前两个副本中的元素：

$[ \ 0 \ 0 \ 0 \ \underline{0} \ \underline{0} \ 0 \ ]$ , $[ \ \underline{3} \ \underline{7} \ 0 \ 3 \ 7 \ 0 \ ]$ 和 $[ \ 1 \ 1 \ 3 \ 3 \ 7 \ 3 \ ]$ 。

最终，我们得到了一个所有元素都相等的副本，并且总共进行了 $6$ 次操作。

可以证明，没有更少的操作次数能够达到目标。

**样例 #1**

输入：

```
6
1
1789
6
0 1 3 3 7 0
2
-1000000000 1000000000
4
4 3 2 1
5
2 5 7 6 3
7
1 1 1 1 1 1 1
```

输出：

```
0
6
2
5
7
0
```

---

### 题解分析与结论

#### 综合分析

1. **核心思路**：所有题解都基于贪心策略，选择将数组中的元素变为出现次数最多的元素（众数），以减少操作次数。通过克隆和交换操作，逐步将众数集中到一个数组中。
  
2. **操作次数计算**：大多数题解通过计算克隆次数和交换次数来求解最小操作次数。克隆次数通常通过倍增策略计算，而交换次数则直接为 $n - s$，其中 $s$ 是众数的出现次数。

3. **数据结构**：大多数题解使用 `map` 或排序来统计每个元素的出现次数，以确定众数。

4. **优化点**：部分题解通过数学公式直接计算克隆次数，避免了循环计算，提高了效率。

#### 最优关键思路

- **众数选择**：选择出现次数最多的元素作为目标，减少交换次数。
- **倍增克隆**：通过每次克隆使众数的数量翻倍，直到众数数量大于等于 $n$。
- **数学公式**：使用 $\lceil \log_2 \frac{n}{s} \rceil$ 计算克隆次数，避免循环。

#### 可拓展之处

- **类似问题**：类似的问题可以出现在需要将数组中的元素统一为某个特定值的场景，如数组元素的最小交换次数问题。
- **算法套路**：贪心策略结合数学公式计算操作次数，适用于多种最小化操作次数的问题。

#### 推荐题目

1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---

### 精选题解

#### 题解1：xzyg (4星)

**关键亮点**：
- 使用 `map` 统计元素出现次数，清晰简洁。
- 通过数学公式 $\lceil \log_2 \frac{n}{s} \rceil$ 计算克隆次数，避免了循环计算，效率高。

**代码核心实现**：
```cpp
ll s = -1;
for(ll j = 1; j <= n; j++){
    s = max(f[a[j]],s);
}
cout << ceil(log2(1.0*n/s)) + n - s << endl;
```

#### 题解2：happy_dengziyue (4星)

**关键亮点**：
- 通过排序和双指针统计众数，避免了 `map` 的使用，适合对内存要求较高的场景。
- 使用循环计算克隆次数，思路清晰。

**代码核心实现**：
```cpp
for(int i=0,x=1;;++i,x<<=1){
    if(cnt*x>=n){
        ans=i;
        break;
    }
}
ans+=n-cnt;
```

#### 题解3：tZEROちゃん (4星)

**关键亮点**：
- 使用 `map` 统计元素出现次数，代码简洁。
- 通过循环逐步增加众数数量，直到满足条件，思路清晰。

**代码核心实现**：
```cpp
while (commonTime < n) {
    int d = min(n - commonTime, commonTime);
    ans = ans + d + 1;
    commonTime += d;
}
```

---
处理用时：44.54秒