# 题目信息

# Little Dima and Equation

## 题目描述

Little Dima misbehaved during a math lesson a lot and the nasty teacher Mr. Pickles gave him the following problem as a punishment.

Find all integer solutions $ x $ $ (0&lt;x&lt;10^{9}) $ of the equation:

 $ x=b·s(x)^{a}+c, $ where $ a $ , $ b $ , $ c $ are some predetermined constant values and function $ s(x) $ determines the sum of all digits in the decimal representation of number $ x $ .

The teacher gives this problem to Dima for each lesson. He changes only the parameters of the equation: $ a $ , $ b $ , $ c $ . Dima got sick of getting bad marks and he asks you to help him solve this challenging problem.

## 样例 #1

### 输入

```
3 2 8
```

### 输出

```
3
10 2008 13726 ```

## 样例 #2

### 输入

```
1 2 -18
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 2 -1
```

### 输出

```
4
1 31 337 967 ```

# AI分析结果



**题目重写**
# Little Dima and Equation

## 题目描述

小迪马在数学课上调皮捣蛋，老师罚他解决以下问题：

找到满足方程 $x = b·s(x)^a + c$ 的所有整数解 $x$ $(0 < x < 10^9)$。其中，$a$、$b$、$c$ 是给定的常数，函数 $s(x)$ 表示 $x$ 的十进制各位数字之和。

老师每次上课都会改变方程的参数。你需要帮助迪马高效解决这个问题。

## 样例 #1

### 输入

```
3 2 8
```

### 输出

```
3
10 2008 13726
```

---

**算法分类**：枚举、数学

---

### 题解分析与结论

所有题解均采用**逆向枚举数码和**的核心思路。由于 $s(x)$ 的最大值为 $81$（当 $x=999,999,999$ 时），直接枚举 $s(x)$ 的值（1~81）即可。对于每个枚举值 $i$，计算 $x = b·i^a + c$，然后验证 $x$ 的数码和是否等于 $i$，并检查 $x$ 的范围。最终结果需排序输出。

---

### 高分题解推荐

#### 1. SakurajiamaMai（4星）
**关键亮点**：利用 `set` 自动排序和去重，代码简洁高效。
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int> x;
long long qpow(long long q, int a) {
    long long ans = 1;
    for (int i = 0; i < a; i++) ans *= q;
    return ans;
}
int main() {
    int a, b, c; cin >> a >> b >> c;
    for (int i = 1; i <= 81; i++) {
        long long p = b * qpow(i, a) + c;
        if (p >= 1e9 || p <= 0) continue;
        long long num = 0, tmp = p;
        while (tmp) num += tmp % 10, tmp /= 10;
        if (num == i) x.insert(p);
    }
    cout << x.size() << endl;
    for (auto t : x) cout << t << " ";
}
```
**核心思想**：枚举 $i$ 计算 $x$，利用 `set` 自动维护有序结果。

#### 2. TheOnlyMan（4星）
**关键亮点**：快速幂优化，优先队列保证输出顺序。
```cpp
#include<iostream>
#include<queue>
using namespace std;
typedef long long ll;
ll qpow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        b >>= 1; a *= a;
    }
    return ans;
}
int main() {
    ll a, b, c; cin >> a >> b >> c;
    queue<ll> ans;
    for (int i = 1; i <= 81; i++) {
        ll k = b * qpow(i, a) + c;
        if (k >= 1e9) continue;
        ll sum = 0, tmp = k;
        while (tmp) sum += tmp % 10, tmp /= 10;
        if (sum == i) ans.push(k);
    }
    cout << ans.size() << "\n";
    while (!ans.empty()) cout << ans.front() << " ", ans.pop();
}
```
**核心思想**：快速幂提升计算效率，优先队列管理结果。

#### 3. MspAInt（4星）
**关键亮点**：显式排序确保输出顺序，条件判断严谨。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long Pow(int x, int y) {
    long long ret = 1;
    for (int i = 1; i <= y; i++) ret *= x;
    return ret;
}
int main() {
    int a, b, c, k = 0; cin >> a >> b >> c;
    long long r[100];
    for (int i = 1; i <= 81; i++) {
        long long x = b * Pow(i, a) + c;
        if (x >= 1e9) continue;
        int sum = 0, tmp = x;
        while (tmp) sum += tmp % 10, tmp /= 10;
        if (sum == i) r[++k] = x;
    }
    sort(r + 1, r + k + 1);
    cout << k << "\n";
    for (int i = 1; i <= k; i++) cout << r[i] << " ";
}
```
**核心思想**：显式调用 `sort` 排序，严格验证数码和与范围。

---

### 关键思路总结
1. **逆向枚举**：枚举数码和 $s(x)$（1~81）而非直接枚举 $x$，时间复杂度降至 $O(81·\log x)$。
2. **快速幂优化**：对于 $i^a$ 的计算，快速幂可提升效率（但 $a$ 较小时代码差异不大）。
3. **结果排序**：使用有序容器或显式排序确保输出顺序正确。
4. **边界处理**：验证 $0 < x < 10^9$，避免无效计算。

---

### 拓展与同类题目
1. **数码和性质**：类似利用数码和特性的题目（如 CF633B）。
2. **逆向枚举**：当直接枚举不可行时，寻找问题变量的隐含范围（如 POJ2540）。
3. **快速幂应用**：涉及指数运算的题目（如 LeetCode 50）。

**推荐练习**：
1. [CF456B - Fedya and Maths](https://www.luogu.com.cn/problem/CF456B)
2. [CF489C - Given Length and Sum of Digits...](https://www.luogu.com.cn/problem/CF489C)
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)（记忆化+参数范围优化）

---
处理用时：323.33秒