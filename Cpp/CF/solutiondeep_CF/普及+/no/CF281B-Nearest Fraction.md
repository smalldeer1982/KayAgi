# 题目信息

# Nearest Fraction

## 题目描述

You are given three positive integers $ x,y,n $ . Your task is to find the nearest fraction to fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/4ac5ad94fb5392cd96ac09e5b84eb06e8c8a0edb.png) whose denominator is no more than $ n $ .

Formally, you should find such pair of integers $ a,b $ $ (1<=b<=n; 0<=a) $ that the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF281B/c829c21e70460346cb0c98e0e40815418eed87ca.png) is as minimal as possible.

If there are multiple "nearest" fractions, choose the one with the minimum denominator. If there are multiple "nearest" fractions with the minimum denominator, choose the one with the minimum numerator.

## 样例 #1

### 输入

```
3 7 6
```

### 输出

```
2/5
```

## 样例 #2

### 输入

```
7 2 4
```

### 输出

```
7/2
```

# AI分析结果

### 题目内容
# 最近的分数

## 题目描述
给定三个正整数 $x$、$y$、$n$ 。你的任务是找到与分数 $\frac{x}{y}$ 最接近且分母不超过 $n$ 的分数。

形式上，你应找到这样一对整数 $a$、$b$ （$1 \leq b \leq n$；$0 \leq a$），使得 $\left|\frac{x}{y}-\frac{a}{b}\right|$ 的值尽可能小。

如果有多个 “最接近” 的分数，选择分母最小的那个。如果有多个 “最接近” 且分母最小的分数，选择分子最小的那个。

## 样例 #1
### 输入
```
3 7 6
```
### 输出
```
2/5
```

## 样例 #2
### 输入
```
7 2 4
```
### 输出
```
7/2
```

### 算法分类
数学

### 题解综合分析与结论
1. **loser_seele的题解**：
    - **思路**：先考虑暴力枚举所有合法分数找与目标分数距离最小的，但因效率低进行优化。令 $\frac{a}{b}=\frac{x}{c}$ 推出 $x=\frac{ac}{b}$，因 $x$ 可能非整数，所以枚举 $x$ 周围20个整数，与 $\frac{a}{b}$ 作差取绝对值差最小的，枚举时保证分母和分子从小到大。
    - **算法要点**：通过剪枝优化暴力枚举，利用比较函数和求差函数来确定最接近分数。
    - **解决难点**：避免无效分数枚举，通过剪枝减少计算量。
2. **_5t0_0r2_的题解**：
    - **思路**：使用公式推出在分母为 $i$ 的情况下与 $\frac{x}{y}$ 最接近的数。通过通分，将 $\frac{x}{y}$ 转化后使分子变为最近的某个倍数来确定最接近分数。
    - **算法要点**：利用求最大公约数、通分等数学运算来确定最接近分数。
    - **解决难点**：通过数学公式准确找到在给定分母下最接近的分数。
3. **SlyCharlotte的题解**：
    - **思路**：若 $y \leq n$ 则答案为 $\frac{x}{y}$ ；否则枚举分母，二分分子找到最大的小于等于 $\frac{x}{y}$ 的分数，同时考虑 $\frac{x + 1}{y}$ 对答案的贡献。对于 $x \geq y$ 先转化为 $x \leq y$ 处理后再还原。
    - **算法要点**：结合枚举分母与二分分子的方法，利用比较函数确定最接近分数。
    - **解决难点**：合理利用二分查找提高效率，处理好边界情况如 $\frac{x + 1}{y}$ 的贡献及 $x$ 和 $y$ 大小关系。

整体来看，三位作者思路各有特点，loser_seele通过剪枝优化暴力，_5t0_0r2_侧重于数学公式推导，SlyCharlotte采用枚举结合二分的方式。在代码实现上，SlyCharlotte的代码结构相对更清晰，对边界情况处理较全面；loser_seele代码简洁但部分逻辑稍显隐晦；_5t0_0r2_代码只给出部分核心函数，完整性不足。

### 所选的题解
1. **SlyCharlotte的题解**：
    - **星级**：4星
    - **关键亮点**：采用枚举分母结合二分分子的方法，能有效降低时间复杂度，对 $x$ 和 $y$ 大小关系及 $\frac{x + 1}{y}$ 等边界情况处理细致，代码结构清晰。
    - **核心代码**：
```cpp
ll y, n;

bool check(ll b, ll a, ll x) {
    if (1LL * b * x >= 1LL * a * y)
        return true;
    return false;
}

pair<ll, ll> fun(ll x1) {
    long double min = float(x1) / y;
    ll num = 0;
    ll denom = 1;
    for (ll i = 1; i <= n; i++) {
        ll l = 0, r = i - 1;
        ll ans = 0;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (check(i, mid, x1))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        ll tnum = ans;
        ll tdenom = i;
        ldb tmin = abs((double(x1) / y) - (double(tnum) / tdenom));
        ldb temp = abs((double(x1) / y) - ((double(tnum + 1)) / tdenom));
        if (temp < tmin)
            tmin = temp, tnum = ans + 1;
        if (tmin < min)
            min = tmin, denom = tdenom, num = tnum;
    }
    return {num, denom};
}

signed main() {
    ll x;
    cin >> x >> y >> n;
    if (n >= y) {
        ll g = gcd(x, y);
        cout << x / g << "/" << y / g;
    } else {
        ll i = x / y, x1 = x - y * i;
        pair<ll, ll> f = fun(x1);
        ll num, denom = f.second;
        num = denom * i + f.first;
        ll g = gcd(num, denom);
        cout << num / g << "/" << denom / g;
    }
    return 0;
}
```
    - **核心实现思想**：`check` 函数用于判断 $\frac{a}{b}$ 和 $\frac{x}{y}$ 的大小关系。`fun` 函数通过枚举分母 $i$，在每个分母下二分分子找到小于等于 $\frac{x}{y}$ 的最大分数，并比较 $\frac{x}{y}$ 与 $\frac{分子 + 1}{分母}$ 的距离，取距离最小的作为当前分母下的最优解。`main` 函数根据 $n$ 和 $y$ 的大小关系，分别处理并输出结果。

### 最优关键思路或技巧
SlyCharlotte采用的枚举分母结合二分分子的方法是较为高效的。通过二分查找在每个分母下快速定位可能的最优分子，减少了不必要的计算，同时全面考虑各种边界情况保证结果的正确性。

### 可拓展之处
此类题目属于分数相关的数学问题，类似套路有通过数学推导优化枚举范围，利用二分查找等优化搜索过程。同类型题可考虑一些需要在特定条件下寻找最优分数或比例的问题。

### 推荐洛谷题目
1. **P1075 [NOIP2012 普及组] 质因数分解**：考察对数学概念及分解算法的运用。
2. **P1028 [NOIP2001 普及组] 数的计算**：涉及递推和数学规律的探索。
3. **P1147 连续自然数和**：需要运用数学知识分析问题并解决。 

---
处理用时：64.54秒