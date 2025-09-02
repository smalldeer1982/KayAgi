# 题目信息

# [ABC189D] Logical Expression

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc189/tasks/abc189_d

$ N $ 個の文字列 $ S_1,\ldots,S_N $ が与えられます。各文字列は `AND` または `OR` です。

値が $ \text{True} $ または $ \text{False} $ であるような $ N+1 $ 個の変数の組 $ (x_0,\ldots,x_N) $ であって、 以下のような計算を行った際に、$ y_N $ が $ \text{True} $ となるようなものの個数を求めてください。

- $ y_0=x_0 $
- $ i\geq\ 1 $ のとき、$ S_i $ が `AND` なら $ y_i=y_{i-1}\ \land\ x_i $、$ S_i $ が `OR` なら $ y_i=y_{i-1}\ \lor\ x_i $

$ a\ \land\ b $ は $ a $ と $ b $ の論理積を表し、$ a\ \lor\ b $ は $ a $ と $ b $ の論理和を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 60 $
- $ S_i $ は `AND` または `OR`

### Sample Explanation 1

例えば $ (x_0,x_1,x_2)=(\text{True},\text{False},\text{True}) $ のとき - $ y_0=x_0=\text{True} $ - $ y_1=y_0\ \land\ x_1\ =\ \text{True}\ \land\ \text{False}=\text{False} $ - $ y_2=y_1\ \lor\ x_2\ =\ \text{False}\ \lor\ \text{True}=\text{True} $ となり、$ y_2 $ は $ \text{True} $ になります。 $ y_2 $ が $ \text{True} $ となるような $ (x_0,x_1,x_2) $ の組み合わせは、 - $ (\text{True},\text{True},\text{True}) $ - $ (\text{True},\text{True},\text{False}) $ - $ (\text{True},\text{False},\text{True}) $ - $ (\text{False},\text{True},\text{True}) $ - $ (\text{False},\text{False},\text{True}) $ の $ 5 $ 通りで全てです。

### Sample Explanation 2

全てが $ \text{False} $ のときを除く $ 2^6-1 $ 通りで $ y_5 $ は $ \text{True} $ になります。

## 样例 #1

### 输入

```
2

AND

OR```

### 输出

```
5```

## 样例 #2

### 输入

```
5

OR

OR

OR

OR

OR```

### 输出

```
63```

# AI分析结果



# [ABC189D] Logical Expression

## 题目描述

给定 $ N $ 个字符串 $ S_1,\ldots,S_N $，每个字符串为 `AND` 或 `OR`。要求找到满足条件的 $ N+1 $ 个布尔变量 $ (x_0,\ldots,x_N) $ 的组数，使得经过以下运算后 $ y_N $ 为真：

- $ y_0=x_0 $
- 对于 $ i\geq 1 $，若 $ S_i $ 是 `AND` 则 $ y_i=y_{i-1}\ \land\ x_i $，否则 $ y_i=y_{i-1}\ \lor\ x_i $

## 算法分类
动态规划

---

## 题解综合分析

### 关键思路总结
使用动态规划维护两个状态：`dp[i][0]` 表示前 `i` 步结果为假的方案数，`dp[i][1]` 表示结果为真的方案数。根据运算符类型进行状态转移：
- **AND运算符**：真状态只能由前一步真状态延续，假状态由前一步假状态（任意当前值）和前一步真状态（当前值假）组成
- **OR运算符**：假状态只能由前一步假状态延续，真状态由前一步真状态（任意当前值）和前一步假状态（当前值真）组成

### 优质题解推荐

#### 1. Elairin176 的题解（★★★★★）
**核心亮点**：
- 清晰的转移方程推导
- 时间复杂度 $O(n)$ 的高效实现
- 完整的状态转移数学表达

```cpp
long long dp[61][2];
string s[61];
int main() {
    int n; cin >> n;
    dp[0][0] = dp[0][1] = 1;
    for (int i=0; i<n; ++i) {
        if (s[i] == "AND") {
            dp[i+1][1] = dp[i][1];
            dp[i+1][0] = 2*dp[i][0] + dp[i][1];
        } else {
            dp[i+1][0] = dp[i][0];
            dp[i+1][1] = dp[i][0] + 2*dp[i][1];
        }
    }
    cout << dp[n][1];
}
```

#### 2. fish_love_cat 的题解（★★★★☆）
**核心亮点**：
- 简洁的代码实现
- 使用布尔数组标记运算符类型
- 状态转移方程直接嵌入条件判断

```cpp
long long dp[65][5];
bool a[65]; // 标记运算符类型
int main() {
    int n; cin >> n;
    dp[0][0] = dp[0][1] = 1;
    for (int i=1; i<=n; ++i) {
        if (a[i]) { // AND
            dp[i][1] = dp[i-1][1];
            dp[i][0] = 2*dp[i-1][0] + dp[i-1][1];
        } else {    // OR
            dp[i][1] = 2*dp[i-1][1] + dp[i-1][0];
            dp[i][0] = dp[i-1][0];
        }
    }
    cout << dp[n][1];
}
```

#### 3. NightStriker 的题解（★★★★☆）
**核心亮点**：
- 二维数组的直观使用
- 运算符判断逻辑清晰
- 兼容性强的输入处理

```cpp
long long f[61][2];
string s[61];
int main() {
    cin >> n;
    f[0][0] = f[0][1] = 1;
    for (int i=0; i<n; ++i) {
        if (s[i] == "AND") {
            f[i+1][1] += f[i][1];
            f[i+1][0] += 2*f[i][0] + f[i][1];
        } else {
            f[i+1][1] += f[i][0] + 2*f[i][1];
            f[i+1][0] += f[i][0];
        }
    }
    cout << f[n][1];
}
```

---

## 类似题目推荐
1. [P1143 进制转换](https://www.luogu.com.cn/problem/P1143) - 进制转换中的状态处理
2. [P1435 回文字符串](https://www.luogu.com.cn/problem/P1435) - 区间DP应用
3. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352) - 树形DP状态转移

---
处理用时：112.82秒