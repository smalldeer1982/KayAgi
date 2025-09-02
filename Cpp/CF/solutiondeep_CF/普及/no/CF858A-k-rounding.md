# 题目信息

# k-rounding

## 题目描述

给定一个正整数n， 要求求出一个最小的正整数，使得其末尾至少有k个连续的0，并且为n的倍数。

## 样例 #1

### 输入

```
375 4
```

### 输出

```
30000
```

## 样例 #2

### 输入

```
10000 1
```

### 输出

```
10000
```

## 样例 #3

### 输入

```
38101 0
```

### 输出

```
38101
```

## 样例 #4

### 输入

```
123456789 8
```

### 输出

```
12345678900000000
```

# AI分析结果



# k-rounding

## 题目描述

给定一个正整数n，要求求出一个最小的正整数，使得其末尾至少有k个连续的0，并且为n的倍数。

## 样例 #1

### 输入
```
375 4
```

### 输出
```
30000
```

## 样例 #2

### 输入
```
10000 1
```

### 输出
```
10000
```

## 样例 #3

### 输入
```
38101 0
```

### 输出
```
38101
```

## 样例 #4

### 输入
```
123456789 8
```

### 输出
```
12345678900000000
```

**算法分类**：数学

---

### 题解综合分析

所有题解核心思路均围绕以下数学原理展开：
1. 末尾k个0 ⇨ 该数是10^k的倍数
2. 同时是n的倍数 ⇨ 求n与10^k的最小公倍数（LCM）

最优解法公式：
$$ \text{答案} = \frac{n \times 10^k}{\gcd(n, 10^k)} $$

---

### 精选题解（评分≥4星）

#### 1. SqrtSecond 的第三种解法（5星）
**关键亮点**：
- 直接调用数学公式实现，代码简洁高效
- 时间复杂度O(log min(n,10^k))，空间复杂度O(1)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b) {
    return a % b ? gcd(b, a % b) : b;
}
int main() {
    long long n, k, a = 1;
    cin >> n >> k;
    while(k--) a *= 10; 
    cout << n * a / gcd(n, a);
}
```

#### 2. Aw顿顿 的解法（4星）
**关键亮点**：
- 使用快速幂计算10^k
- 调用内置__gcd函数简化代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ksm(int base, int power) {
    int ans = 1;
    while(power) {
        if(power&1) ans *= base;
        base *= base;
        power >>= 1;
    }
    return ans;
}
signed main() {
    int n, k;
    cin >> n >> k;
    int kk = ksm(10, k);
    cout << n * kk / __gcd(kk, n);
}
```

#### 3. Arghariza 的解法（4星）
**关键亮点**：
- 显式处理质因数分解的逻辑
- 通过统计2和5的因子数优化计算

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k, tn, cnt2 = 0, cnt5 = 0;
    cin >> n >> k;
    tn = n;
    while (n % 2 == 0) cnt2++, n /= 2;
    while (n % 5 == 0) cnt5++, n /= 5;
    n = tn;
    printf("%lld", n * pow(2, max(0ll, k - cnt2)) * pow(5, max(0ll, k - cnt5)));
}
```

---

### 关键思路总结
1. **数学转化**：将问题转化为求LCM(n,10^k)
2. **GCD/LCM公式**：利用 $\text{LCM}(a,b) = \frac{a \times b}{\text{GCD}(a,b)}$ 简化计算
3. **质因数优化**：对于需要多次计算的情况，分解质因数可提升效率

---

### 拓展练习
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)

---

### 调试心得摘录
- **ShineEternal**：首次使用pow函数导致WA，改用快速幂后解决（注意pow的浮点精度问题）
- **Cocoly1990**：强调必须开long long防止溢出
- **零殇**：通过分解质因数时需先复制n的值，避免修改原始数据

---
处理用时：65.53秒