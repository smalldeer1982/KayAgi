# 题目信息

# Partitioning the Array

## 题目描述

Allen has an array $ a_1, a_2,\ldots,a_n $ . For every positive integer $ k $ that is a divisor of $ n $ , Allen does the following:

- He partitions the array into $ \frac{n}{k} $ disjoint subarrays of length $ k $ . In other words, he partitions the array into the following subarrays: $ $$$[a_1,a_2,\ldots,a_k],[a_{k+1}, a_{k+2},\ldots,a_{2k}],\ldots,[a_{n-k+1},a_{n-k+2},\ldots,a_{n}] $ $  </li><li> Allen earns one point if there exists some positive integer  $ m $  ( $ m \\geq 2 $ ) such that if he replaces every element in the array with its remainder when divided by  $ m$$$, then all subarrays will be identical.

Help Allen find the number of points he will earn.

## 说明/提示

In the first test case, $ k=2 $ earns a point since Allen can pick $ m = 2 $ and both subarrays will be equal to $ [1, 0] $ . $ k=4 $ also earns a point, since no matter what $ m $ Allen chooses, there will be only one subarray and thus all subarrays are equal.

In the second test case, Allen earns $ 1 $ point for $ k=3 $ , where his choice for $ m $ does not matter.

## 样例 #1

### 输入

```
8
4
1 2 1 4
3
1 2 3
5
1 1 1 1 1
6
1 3 1 1 3 1
6
6 2 6 2 2 2
6
2 6 3 6 6 6
10
1 7 5 1 4 3 1 3 1 4
1
1```

### 输出

```
2
1
2
4
4
1
2
1```

# AI分析结果

### 题目内容中文重写
# 数组分割

## 题目描述
艾伦有一个数组 $ a_1, a_2,\ldots,a_n $。对于每个能整除 $ n $ 的正整数 $ k $，艾伦会进行以下操作：
- 他将数组分割成 $ \frac{n}{k} $ 个不相交的长度为 $ k $ 的子数组。换句话说，他将数组分割成以下子数组：
$$[a_1,a_2,\ldots,a_k],[a_{k + 1}, a_{k + 2},\ldots,a_{2k}],\ldots,[a_{n - k + 1},a_{n - k + 2},\ldots,a_{n}]$$
- 如果存在某个正整数 $ m $（$ m \geq 2 $），使得他将数组中的每个元素替换为其除以 $ m $ 后的余数后，所有子数组都相同，那么艾伦将获得一分。

请帮助艾伦计算他将获得的总分数。

## 说明/提示
在第一个测试用例中，$ k = 2 $ 可以获得一分，因为艾伦可以选择 $ m = 2 $，此时两个子数组都将变为 $ [1, 0] $。$ k = 4 $ 也可以获得一分，因为无论艾伦选择什么 $ m $，都只会有一个子数组，因此所有子数组都是相等的。

在第二个测试用例中，对于 $ k = 3 $，艾伦可以获得一分，此时他对 $ m $ 的选择无关紧要。

## 样例 #1
### 输入
```
8
4
1 2 1 4
3
1 2 3
5
1 1 1 1 1
6
1 3 1 1 3 1
6
6 2 6 2 2 2
6
2 6 3 6 6 6
10
1 7 5 1 4 3 1 3 1 4
1
1
```

### 输出
```
2
1
2
4
4
1
2
1
```

### 综合分析与结论
这些题解的核心思路都是枚举 $ n $ 的因数 $ k $，然后判断对于每个 $ k $ 是否存在 $ m\geq2 $ 使得将数组元素对 $ m $ 取模后，分割出的子数组都相同。

#### 思路对比
- **Luzhuoyuan、mountain_climber、huangrenheluogu**：利用若 $x\equiv y\pmod m$，则 $m|(x - y)$ 的性质，对 $|a_i - a_{i - k}|(k < i\leq n)$ 求 $\gcd$，若最终 $\gcd\geq2$ 则答案加一。
- **Zemu_Ooo**：枚举 $n$ 的所有除数 $k$，对于每个 $k$ 再枚举 $m$ 从 $2$ 到 $n$，检查将数组元素对 $m$ 取模后子数组是否相同。
- **kczw**：预处理出 $n\leq2\times10^5$ 的所有因数，枚举 $n$ 的因数 $k$，对所有 $|a_i - a_{i + k}|$ 求 $\gcd$，若 $\gcd\geq2$ 则答案加一。
- **Saint_ying_xtf**：枚举每段长度 $i$，对每组数的差求 $\gcd$，若最终 $\gcd$ 不为 $1$ 则有贡献。

#### 算法要点对比
- **Luzhuoyuan、mountain_climber、huangrenheluogu、Saint_ying_xtf**：通过求 $\gcd$ 来判断是否存在满足条件的 $m$，时间复杂度为 $O(n\sqrt n)$。
- **Zemu_Ooo**：枚举 $m$ 来判断，时间复杂度相对较高。
- **kczw**：预处理因数，枚举 $k$ 并求 $\gcd$，时间复杂度也为 $O(n\sqrt n)$。

#### 解决难点对比
- 核心难点在于如何高效判断对于每个 $k$ 是否存在满足条件的 $m$。大部分题解通过求 $\gcd$ 巧妙地解决了这个问题，避免了枚举 $m$ 的高复杂度。

### 题解评分
- **Luzhuoyuan**：5星。思路清晰，代码简洁，复杂度分析准确。
- **mountain_climber**：4星。思路明确，代码可读性较好。
- **Zemu_Ooo**：3星。思路直观，但枚举 $m$ 的方法复杂度较高，且有调试过程的描述，说明代码实现不够完善。
- **huangrenheluogu**：4星。思路和代码都比较简洁。
- **kczw**：3星。预处理因数的方法增加了代码复杂度，且思路表述不够简洁。
- **Saint_ying_xtf**：3星。思路简单描述，但缺乏代码，不够完整。

### 所选题解
- **Luzhuoyuan**（5星）
    - **关键亮点**：思路清晰，代码简洁，复杂度分析准确。利用 $\gcd$ 性质高效判断是否存在满足条件的 $m$。
    - **核心代码**：
```cpp
inline bool work(int x){
    int g = 0;
    for(int i = x + 1; i <= n; i++){
        int t = abs(a[i] - a[i - x]), tmp = 0;
        while(t) tmp = g % t, g = t, t = tmp;
        if(g == 1) return false;
    }
    return true;
}
```
核心思想：对于给定的 $k$，计算 $|a_i - a_{i - k}|$ 的 $\gcd$，若 $\gcd = 1$ 则不存在满足条件的 $m$，否则存在。

- **mountain_climber**（4星）
    - **关键亮点**：思路明确，代码可读性较好。
    - **核心代码**：
```cpp
bool check(int k){
    if(k == n) return true;
    int m = abs(a[1] - a[1 + k]);
    for(int i = 1; i <= n - k; i++){
        m = gcd(abs(a[i] - a[i + k]), m);
        if(m == 1) return false;
    }
    return true;
}
```
核心思想：对于给定的 $k$，计算 $|a_i - a_{i + k}|$ 的 $\gcd$，若 $\gcd = 1$ 则不存在满足条件的 $m$，若 $k = n$ 则直接满足条件。

- **huangrenheluogu**（4星）
    - **关键亮点**：思路和代码都比较简洁。
    - **核心代码**：
```cpp
inline bool check(int x){
    if(x == n) return 1;
    g = abs(a[1 + x] - a[1]);
    for(int i = 1; i <= n - x; i++){
        g = __gcd(g, abs(a[i + x] - a[i]));
        if(g == 1) return 0;
    }
    return 1;
}
```
核心思想：对于给定的 $k$，计算 $|a_i - a_{i + k}|$ 的 $\gcd$，若 $\gcd = 1$ 则不存在满足条件的 $m$，若 $k = n$ 则直接满足条件。

### 最优关键思路或技巧
利用若 $x\equiv y\pmod m$，则 $m|(x - y)$ 的性质，通过求 $\gcd$ 来判断是否存在满足条件的 $m$，避免了枚举 $m$ 的高复杂度，将时间复杂度控制在 $O(n\sqrt n)$。

### 可拓展之处
同类型题可能会改变数组的分割方式或判断条件，但核心思路仍然是利用同余性质和 $\gcd$ 来解决问题。类似算法套路可用于解决一些需要判断多个数是否同余的问题。

### 洛谷推荐题目
1. [P1072  Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)：考察最大公因数和最小公倍数的性质。
2. [P2152  聪聪可可](https://www.luogu.com.cn/problem/P2152)：涉及树的路径和同余问题。
3. [P3811  乘法逆元](https://www.luogu.com.cn/problem/P3811)：需要运用同余和扩展欧几里得算法。

### 个人心得摘录与总结
- **Zemu_Ooo**：在调试过程中发现处理单个元素数组的情况时出现问题，意识到当 $k = n$ 时，无论 $m$ 的值如何，只有一个子数组，它总是与自身相同，应直接增加一分。总结为在处理边界情况时需要特别注意，避免遗漏特殊情况。

---
处理用时：45.82秒