# 题目信息

# [ABC172E] NEQ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc172/tasks/abc172_e

$ 1 $ 以上 $ M $ 以下の整数からなる長さ $ N $ の数列 $ A_1,A_2,\cdots,\ A_{N} $ と $ B_1,B_2,\cdots,\ B_{N} $ の組であって、以下の条件をすべて満たすものの個数を求めてください。

- $ 1\leq\ i\leq\ N $ なる任意の $ i $ について $ A_i\ \neq\ B_i $
- $ 1\leq\ i\ <\ j\leq\ N $ なる任意の $ (i,j) $ について $ A_i\ \neq\ A_j $ かつ $ B_i\ \neq\ B_j $

ただし、答えは非常に大きくなる可能性があるので、$ (10^9+7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ M\ \leq\ 5\times10^5 $
- 入力はすべて整数

### Sample Explanation 1

$ A_1=1,A_2=2,B_1=2,B_2=1 $ のときと $ A_1=2,A_2=1,B_1=1,B_2=2 $ のとき条件が満たされます。

## 样例 #1

### 输入

```
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3```

### 输出

```
18```

## 样例 #3

### 输入

```
141421 356237```

### 输出

```
881613484```

# AI分析结果

### 题目内容翻译

给定两个整数 $N$ 和 $M$，构造两个长度为 $N$ 的序列 $A$ 和 $B$，满足以下条件：

1. 序列中的元素均为 $1$ 到 $M$ 之间的整数。
2. 对于任意 $i$，$A_i \neq B_i$。
3. 序列 $A$ 和 $B$ 中的元素互不相同。

求满足条件的序列对 $(A, B)$ 的数量，结果对 $10^9+7$ 取模。

### 算法分类
组合数学

### 题解分析与结论

该题的核心在于如何计算满足条件的序列对 $(A, B)$ 的数量。题解中主要采用了组合数学和容斥原理的思路，通过错排问题的变式来解决。以下是各题解的要点和难点对比：

1. **UKE_Automation 的题解**：
   - **思路**：通过错排问题的变式，结合排列组合和递推公式，计算满足条件的序列对数量。
   - **难点**：错排公式的推导和递推边界条件的处理。
   - **评分**：4星
   - **关键亮点**：递推公式的推导清晰，代码实现简洁。

2. **刘辰雨的题解**：
   - **思路**：通过容斥原理，计算至少有一个位置相同的序列对数量，然后用总数量减去不合法数量。
   - **难点**：容斥原理的应用和组合数的计算。
   - **评分**：4星
   - **关键亮点**：容斥原理的应用详细，代码实现清晰。

3. **Tx_Lcy 的题解**：
   - **思路**：通过容斥原理，计算至少有一个位置相同的序列对数量，然后用总数量减去不合法数量。
   - **难点**：容斥原理的应用和组合数的计算。
   - **评分**：4星
   - **关键亮点**：容斥原理的应用详细，代码实现清晰。

### 最优关键思路与技巧

1. **错排问题的变式**：通过错排问题的变式，结合排列组合和递推公式，计算满足条件的序列对数量。
2. **容斥原理**：通过容斥原理，计算至少有一个位置相同的序列对数量，然后用总数量减去不合法数量。

### 可拓展之处

该题的思路可以拓展到其他类似的组合数学问题，如计算满足特定条件的排列组合数量。类似的题目可以通过容斥原理或错排问题的变式来解决。

### 推荐题目

1. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)
2. [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)
3. [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602)

### 个人心得摘录

- **UKE_Automation**：通过错排问题的变式，结合排列组合和递推公式，计算满足条件的序列对数量。
- **刘辰雨**：通过容斥原理，计算至少有一个位置相同的序列对数量，然后用总数量减去不合法数量。
- **Tx_Lcy**：通过容斥原理，计算至少有一个位置相同的序列对数量，然后用总数量减去不合法数量。

### 核心代码片段

```cpp
// UKE_Automation 的代码片段
int A(int n, int m) {
    int res = 1;
    for(int i = n; i >= n - m + 1; i--) {
        res = (res * i) % Mod;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    d[0] = 1, d[1] = m - n;
    ans = A(m, n);
    for(int i = 2; i <= n; i++) {
        d[i] = ((m - n) * d[i - 1] % Mod + (i - 1) * (d[i - 2] + d[i - 1]) % Mod) % Mod;
    } 
    ans = (ans * d[n]) % Mod;
    cout << ans; 
    return 0;
}
```

```cpp
// 刘辰雨的代码片段
int A(int n, int m) {
    return (fac[n] * ksm(fac[n - m], MOD - 2)) % MOD;
}

int C(int n, int m) {
    return (fac[n] * ksm(fac[n - m] * fac[m] % MOD, MOD - 2)) % MOD;
}

int main() {
    scanf("%lld %lld", &n, &m);
    prep();
    sum = A(m, n);
    for(int i = 1; i <= n; i++) {
        ll val = C(n, i) * A(m - i, n - i) % MOD;
        if(i & 1) sum = ((sum - val) % MOD + MOD) % MOD;
        else sum = (sum + val) % MOD;
    }
    printf("%lld\n", sum * A(m, n) % MOD);
    return 0;
}
```

```cpp
// Tx_Lcy 的代码片段
int A(int n, int m) {
    return fac[n] * inv(fac[n - m]) % MOD;
}

int C(int n, int m) {
    return fac[n] * inv(fac[m]) % MOD * inv(fac[n - m]) % MOD;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m; cin >> n >> m;
    fac[0] = 1;
    for (int i = 1; i <= m; ++i) fac[i] = fac[i - 1] * i % MOD;
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        int x = C(n, i) * A(m, i) % MOD * A(m - i, n - i) % MOD * A(m - i, n - i) % MOD;
        ans += x * ((i & 1) ? -1 : 1); ans %= MOD;
        ans += MOD; ans %= MOD;
    }
    cout << ans << '\n';
    return 0;
}
```

---
处理用时：43.66秒