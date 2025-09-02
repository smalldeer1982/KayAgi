# 题目信息

# Simple Subset

## 题目描述

A tuple of positive integers $ {x_{1},x_{2},...,x_{k}} $ is called simple if for all pairs of positive integers $ (i,j) $ ( $ 1<=i&lt;j<=k $ ), $ x_{i}+x_{j} $ is a prime.

You are given an array $ a $ with $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ (not necessary distinct). You want to find a simple subset of the array $ a $ with the maximum size.

A prime number (or a prime) is a natural number greater than $ 1 $ that has no positive divisors other than $ 1 $ and itself.

Let's define a subset of the array $ a $ as a tuple that can be obtained from $ a $ by removing some (possibly all) elements of it.

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
2
3 2
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
1
2
```

## 样例 #3

### 输入

```
3
2 1 1
```

### 输出

```
3
1 1 2
```

## 样例 #4

### 输入

```
2
83 14
```

### 输出

```
2
14 83
```

# AI分析结果

### 题目内容
# 简单子集

## 题目描述
一个由正整数$ {x_{1},x_{2},...,x_{k}} $组成的元组被称为简单的，当且仅当对于所有满足$ 1\leq i < j \leq k $的正整数对$ (i,j) $ ，$ x_{i}+x_{j} $ 都是质数。

给定一个包含$ n $个正整数$ a_{1},a_{2},...,a_{n} $（不一定各不相同）的数组$ a $ 。你需要找出数组$ a $的一个简单子集，使其大小最大。

质数（或素数）是指大于$ 1 $且除了$ 1 $和它自身外，没有其他正因数的自然数。

我们将数组$ a $的子集定义为可以通过移除数组$ a $中的一些（可能是全部）元素而得到的元组。

## 样例 #1
### 输入
```
2
2 3
```
### 输出
```
2
3 2
```

## 样例 #2
### 输入
```
2
2 2
```
### 输出
```
1
2
```

## 样例 #3
### 输入
```
3
2 1 1
```
### 输出
```
3
1 1 2
```

## 样例 #4
### 输入
```
2
83 14
```
### 输出
```
2
14 83
```

### 算法分类
数学（质数相关性质分析）

### 题解综合分析与结论
所有题解的核心思路都是基于质数的性质进行分类讨论，通过分析不同数字组合相加为质数的可能性，来确定最大简单子集。主要考虑的情况有：一个奇数和一个偶数相加为质数；若干个1和一个比质数小1的数；单独一个数。各题解在实现细节上略有不同，如判断质数的方式、循环遍历的写法等，但整体思路一致。

### 所选的题解
 - **作者：xunhuanyihao (5星)**
    - **关键亮点**：思路清晰，先对数字组合性质进行详细分析，明确各种满足条件的子集情况，代码结构清晰，注释详细。
    - **重点代码**：
```cpp
bool chk(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
    return true;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cnt += a[i] == 1;
        ans = max(ans, 1), c0 = a[i];
    }
    ans = max(ans, cnt);
    for (int i = 1; i <= n; i++) {
        if (a[i] % 2 == 0 && cnt && chk(a[i] + 1)) ans = max(ans, cnt + 1), c1 = a[i];
        for (int j = i + 1; j <= n; j++) {
            if (a[i] % 2!= a[j] % 2 && chk(a[i] + a[j])) ans = max(ans, 2), c2 = {a[i], a[j]};
        }
    }
    printf("%d\n", ans);
    if (ans == 1) printf("%d\n", c0);
    else if (ans >= 2 && c1) {
        printf("%d ", c1);
        for (int i = 1; i <= cnt; i++) printf("1 ");
        puts("");
    } else if (ans == 2 && c2.first) printf("%d %d\n", c2.first, c2.second);
    else if (ans == cnt) {
        for (int i = 1; i <= cnt; i++) printf("1 ");
        puts("");
    }
    return 0;
}
```
    - **核心实现思想**：通过chk函数判断一个数是否为质数。在主函数中，先统计1的个数，然后遍历数组，分别考虑能与1构成质数的偶数情况，以及一个奇数和一个偶数相加为质数的情况，最后根据不同情况输出结果。
 - **作者：QWQ_123 (4星)**
    - **关键亮点**：逻辑清晰，先对偶数加偶数、奇数加奇数的情况进行分析，得出结论后，根据1的个数进行分类讨论，代码简洁明了。
    - **重点代码**：
```cpp
bool prime(int a) {
    for (int i = 2; i <= a / i; ++i)
        if (a % i == 0) return false;
    return true;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), cnt1 += (a[i] == 1);
    if (cnt1 <= 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if ((a[i] & 1)!= (a[j] & 1) && prime(a[i] + a[j])) {
                    printf("%d\n", 2);
                    printf("%d %d\n", a[i], a[j]);
                    return 0;
                }
            }
        }
        printf("1\n%d\n", a[1]);
    } else {
        int s = 0;
        for (int i = 1; i <= n; i++) {
            if (prime(a[i] + 1) && a[i]!= 1) {
                s = a[i];
                break;
            }
        }
        printf("%d\n", cnt1 + (s!= 0));
        for (int i = 1; i <= cnt1; ++i) printf("%d ", 1);
        if (s!= 0)
            printf("%d\n", s);
    }
    return 0;
}
```
    - **核心实现思想**：prime函数判断质数。主函数根据1的个数进行分类，1的个数小于等于1时，枚举两个数判断和是否为质数；1的个数大于1时，寻找能与1构成质数的数，然后输出结果。
 - **作者：huangzhixia (4星)**
    - **关键亮点**：对各种不可能构成质数的情况（偶数加偶数、奇数加奇数等）进行详细分析，逐步引导出可能的情况，再通过分类讨论和枚举实现。
    - **重点代码**：
```cpp
inline bool solve(int x) {
    for (int mod = 2; mod <= x / mod; mod++)
        if (!(x % mod)) 
            return 0; 
    return 1; 
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        if (a[i] == 1)
            tot += 1;
    if (tot <= 1) {
        for (int i = 1; i <= n; i++) 
            for (int j = i + 1; j <= n; j++) 
                if ((a[i] & 1)!= (a[j] & 1) && solve(a[i] + a[j])) {
                    puts("2");
                    printf("%d %d\n", a[i], a[j]);
                    return 0;
                }
        printf("1\n%d\n", a[1]);
    } else {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (solve(a[i] + 1) && a[i]!= 1) {
                sum = a[i];
                break;
            }
        }
        printf("%d\n", tot + (sum!= 0));
        for (int i = 1; i <= tot; i++) 
            printf("1 ");
        if (sum)
            printf("%d\n", sum);
    }
}
```
    - **核心实现思想**：solve函数判断质数。主函数统计1的个数，根据1的个数进行分类，分别处理不同情况下的子集选择和输出。

### 最优关键思路或技巧
利用质数的奇偶性性质，即除了2以外的质数都是奇数，从而分析出数组中数字组合相加为质数的可能情况，通过分类讨论简化问题，避免复杂的搜索或枚举。

### 拓展
同类型题通常围绕质数的性质展开，如判断数字组合满足特定条件下与质数的关系。类似算法套路是先分析数字组合的数学性质，再根据性质进行分类讨论和枚举。

### 洛谷推荐题目
 - **P1217 [USACO1.5]回文质数 Prime Palindromes**：结合质数与回文数的判断，需要对数字进行筛选。
 - **P3912 素数个数**：考察质数的判断和统计，可通过不同的质数筛法实现。
 - **P1075 [NOIP2012 普及组] 质因数分解**：涉及对数字进行质因数分解，与质数的性质紧密相关。 

---
处理用时：69.84秒