# 题目信息

# [ABC280D] Factorial and Multiple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc280/tasks/abc280_d

$ 2 $ 以上の整数 $ K $ が与えられます。  
正の整数 $ N $ であって、$ N! $ が $ K $ の倍数となるようなもののうち最小のものを求めてください。

ただし、$ N! $ は $ N $ の階乗を表し、問題の制約下で、そのような $ N $ が必ず存在することが証明できます。

## 说明/提示

### 制約

- $ 2\leq\ K\leq\ 10^{12} $
- $ K $ は整数

### Sample Explanation 1

\- $ 1!=1 $ - $ 2!=2\times\ 1=2 $ - $ 3!=3\times\ 2\times\ 1=6 $ - $ 4!=4\times\ 3\times\ 2\times\ 1=24 $ - $ 5!=5\times\ 4\times\ 3\times\ 2\times\ 1=120 $ より、$ N! $ が $ 30 $ の倍数となる最小の正整数 $ N $ は $ 5 $ です。よって、$ 5 $ を出力します。

## 样例 #1

### 输入

```
30```

### 输出

```
5```

## 样例 #2

### 输入

```
123456789011```

### 输出

```
123456789011```

## 样例 #3

### 输入

```
280```

### 输出

```
7```

# AI分析结果



### 题目翻译
# [ABC280D] Factorial and Multiple

## 题目描述

给定一个大于等于 2 的整数 $K$，求最小的正整数 $N$ 使得 $N!$ 是 $K$ 的倍数。可以证明这样的 $N$ 一定存在。

## 说明/提示

### 样例解释 1
$5! = 120$ 是 30 的倍数，且是满足条件的最小值。

### 数据范围
- $2 \leq K \leq 10^{12}$

---

### 算法分类
数学（质因数分解、阶乘质因子计数）

---

### 题解对比与结论

#### 最优思路总结
1. **质因数分解**：将 $K$ 分解为质因子幂次形式 $K = \prod p_i^{c_i}$
2. **独立处理每个质因子**：对每个 $p_i^{c_i}$，计算满足 $N!$ 中包含至少 $c_i$ 个 $p_i$ 的最小 $N_i$
3. **取最大值**：最终答案 $N = \max(N_i)$

关键技巧：
- 勒让德定理计算阶乘中质因子次数：$L_p(n!) = \sum_{k=1}^\infty \lfloor n/p^k \rfloor$
- 二分法优化查找过程
- 处理大质数的特殊情况（当剩余 $K$ 是质数时直接返回）

---

### 精选题解

#### 1. Moyou（5星）
**核心思路**：
1. 质因数分解后对每个质因子进行二分
2. 使用勒让德定理快速计算阶乘中的质因子次数
3. 时间复杂度 $O(\sqrt{K} + \log^2 K)$

**关键代码**：
```cpp
bool check(int x, int num, int k) {
    int sum = 0;
    while (x) {
        sum += x / num; 
        x /= num;
    }
    return sum >= k;
}

// 主函数中对每个质因子二分
for (auto i : prime) {
    int num = i.x, k = i.y;
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid, num, k)) r = mid - 1;
        else l = mid + 1;
    }
    mx = max(mx, l);
}
```

#### 2. Escapism（5星）
**核心思路**：
1. 二分总答案，每次检查所有质因子是否满足条件
2. 使用递归式二分优化边界处理
3. 代码结构清晰，包含质因数分解模板

**关键代码**：
```cpp
void factor(ll x) {
    for(ll i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            prime[++q] = i;
            while(x % i == 0) num[q]++, x /= i;
        }
    }
    if(x > 1) prime[++q] = x, num[q]++;
}

bool check(ll x) {
    for(ll i = 1; i <= q; i++) {
        ll pnum = 0, n = x;
        while(n) {
            pnum += n / prime[i];
            n /= prime[i];
        }
        if(pnum < num[i]) return false;
    }
    return true;
}
```

#### 3. PineappleSummer（4星）
**核心思路**：
1. 通过逐步消去因子处理小质数
2. 对未消尽的 $K$ 直接返回（处理大质数情况）
3. 代码极其简洁，时间复杂度 $O(2 \times 10^6)$

**关键代码**：
```cpp
for(long long i = 2; i <= 2000000; i++) {
    k /= __gcd(k, i);
    if(k == 1) {
        cout << i << endl;
        return 0;
    }
}
cout << k << endl;
```

---

### 拓展与相似题目
1. [P1593 因子和](https://www.luogu.com.cn/problem/P1593)（质因数分解应用）
2. [P1403 约数研究](https://www.luogu.com.cn/problem/P1403)（阶乘因子计数）
3. [P2424 约数和](https://www.luogu.com.cn/problem/P2424)（质因数分解与约数关系）

---

### 总结心得
- **质因数分解是核心**：所有解法都以此为基础，快速分解大数是关键
- **二分法的巧妙应用**：将阶乘问题转化为单调性问题
- **注意大质数特判**：当剩余未分解的 $K$ 是质数时直接返回
- **代码优化**：使用 GCD 消去因子法可避免直接计算大阶乘

---
处理用时：85.49秒