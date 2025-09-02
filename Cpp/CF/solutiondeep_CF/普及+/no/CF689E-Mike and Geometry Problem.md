# 题目信息

# Mike and Geometry Problem

## 题目描述

Mike wants to prepare for IMO but he doesn't know geometry, so his teacher gave him an interesting geometry problem. Let's define $ f([l,r])=r-l+1 $ to be the number of integer points in the segment $ [l,r] $ with $ l<=r $ (say that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/eeb8344fc6181df63840b4617c77d0b7d8f368f7.png)). You are given two integers $ n $ and $ k $ and $ n $ closed intervals $ [l_{i},r_{i}] $ on $ OX $ axis and you have to find:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/babb2cf528ef0c11f1d2962e2d5be706b0377f3a.png)In other words, you should find the sum of the number of integer points in the intersection of any $ k $ of the segments.

As the answer may be very large, output it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

Mike can't solve this problem so he needs your help. You will help him, won't you?

## 说明/提示

In the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/7f9f6f2b3fe972c0968e2bbe39c55090c69a5e96.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/0c85a7c8eabbf8ea75307cc85322cc7194a52b51.png);

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689E/05a4f7cd13ee1be29210f871f739a0914a5c363f.png).

So the answer is $ 2+1+2=5 $ .

## 样例 #1

### 输入

```
3 2
1 2
1 3
2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 3
1 3
1 3
1 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 1
1 2
2 3
3 4
```

### 输出

```
6
```

# AI分析结果

### 题目重写
# Mike和几何问题

## 题目描述
Mike想准备国际数学奥林匹克竞赛（IMO），但他不懂几何，所以他的老师给了他一道有趣的几何题。定义\(f([l,r]) = r - l + 1\)为线段\([l,r]\)（其中\(l \leq r\)）上的整数点数量（假设\(l\)和\(r\)为整数）。给定两个整数\(n\)和\(k\)，以及\(n\)个在\(OX\)轴上的闭区间\([l_{i},r_{i}]\)，你需要计算：

\(\sum_{1 \leq i_{1} < i_{2} < \cdots < i_{k} \leq n} f([l_{i_{1}},r_{i_{1}}] \cap [l_{i_{2}},r_{i_{2}}] \cap \cdots \cap [l_{i_{k}},r_{i_{k}}])\)

换句话说，你应该求出任意\(k\)个线段交集内整数点数量的总和。

由于答案可能非常大，输出结果需对\(1000000007\)（\(10^{9}+7\)）取模。

Mike无法解决这道题，所以他需要你的帮助。你会帮他的，对吧？

## 说明/提示
在第一个例子中：

\([1,2] \cap [1,3] = [1,2]\)，\(f([1,2]) = 2\)；

\([1,2] \cap [2,3] = [2,2]\)，\(f([2,2]) = 1\)；

\([1,3] \cap [2,3] = [2,3]\)，\(f([2,3]) = 2\)。

所以答案是\(2 + 1 + 2 = 5\)。

## 样例 #1
### 输入
```
3 2
1 2
1 3
2 3
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 3
1 3
1 3
1 3
```
### 输出
```
3
```

## 样例 #3
### 输入
```
3 1
1 2
2 3
3 4
```
### 输出
```
6
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是通过转换问题视角，从计算每个点或小区间的贡献来求解。主要算法要点为利用差分统计区间覆盖情况，结合组合数计算贡献。解决难点在于如何高效统计每个点或区间被覆盖的次数，以及处理组合数计算中的取模和除法问题。多数题解采用离散化处理较大值域，以降低时间复杂度。

### 所选的题解
- **作者：Adove (5星)**
    - **关键亮点**：思路清晰简洁，直接通过差分统计子区间线段覆盖数，然后结合组合数求解，代码实现精炼，未使用复杂数据结构。
    - **重点代码核心思想**：通过结构体存储区间端点及增减标记，排序后利用差分统计覆盖数，结合预处理的组合数计算答案。
    - **核心代码片段**：
```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN = 2e5 + 5;
const int MOD = 1e9 + 7;

int n, m, ans, cnt;
int fac[MAXN], inv[MAXN];
struct rpg {
    int x, kd;
}a[MAXN << 1];

int read() {
    int x = 0; bool fl = 0; char ch = getchar();
    while (ch < '0' || '9' < ch) { if (ch == '-') fl = 1; ch = getchar(); }
    while ('0' <= ch && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return fl? -x : x;
}

bool cmp(rpg a, rpg b) { return a.x < b.x; }
int C(int n, int m) { return n < m? 0 : (long long)fac[n] * inv[m] % MOD * inv[n - m] % MOD; }

int main() {
    n = read(), m = read(); fac[0] = inv[1] = inv[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = (long long)fac[i - 1] * i % MOD;
    for (int i = 2; i <= n; ++i) inv[i] = (long long)(MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 2; i <= n; ++i) inv[i] = (long long)inv[i] * inv[i - 1] % MOD;
    for (int i = 1; i <= n; ++i) {
        a[i].x = read(), a[i + n].x = read() + 1;
        a[i].kd = 1, a[i + n].kd = -1;
    }
    sort(a + 1, a + (n << 1) + 1, cmp);
    for (int i = 1; i <= n << 1; ++i) {
        ans += (long long)C(cnt, m) * (a[i].x - a[i - 1].x) % MOD;
        ans %= MOD; cnt += a[i].kd;
    }
    printf("%d\n", ans);
    return 0;
}
```
- **作者：_H17_ (4星)**
    - **关键亮点**：对问题的转换思路阐述详细，包括离散化、差分、组合数及逆元的原理和实现都有清晰解释，代码简洁明了。
    - **重点代码核心思想**：利用`map`离散化，差分统计每个点被覆盖次数，预处理组合数并结合逆元计算答案。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ALL(x) x.begin(),x.end()
using namespace std;
const int mod = 1e9 + 7;
int n, k, val, ans, c[200001];
map<int, int>mp;
int qp(int a, int b) {
    int ret = 1;
    a %= mod;
    while (b) {
        if (b & 1)
            ret *= a, ret %= mod;
        a *= a, a %= mod, b >>= 1;
    }
    return ret;
}
void init() {
    c[k] = 1;
    for (int i = k + 1; i <= n; i++)
        c[i] = (c[i - 1] * (i % mod)) % mod * qp(i - k, mod - 2), c[i] %= mod;
    return;
}
signed main() {
    cin >> n >> k;
    init();
    for (int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        mp[a]++, mp[b + 1]--;
    }
    auto lit = mp.begin(), it = mp.begin();
    it++;
    for (; it!= mp.end() && lit!= mp.end(); it++, lit++)
        val += (lit->second),
        ans += (((it->first) - (lit->first)) % mod) * c[val], ans %= mod;
    cout << ans;
    return 0;
}
```
- **作者：C6H14 (4星)**
    - **关键亮点**：分析过程清晰，将问题转化为扫描数轴问题，利用差分数组和组合数求解，代码实现逻辑连贯。
    - **重点代码核心思想**：将区间端点放入数组排序，扫描数组同时利用差分维护计数器，结合预处理的组合数和逆元计算答案。
    - **核心代码片段**：
```cpp
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
}
const ll N = 200005, p = 1e9 + 7;
ll rev(ll x) {
    ll ans, tmp;
    x = (x % p + p) % p;
    exgcd(x, p, ans, tmp);
    return (ans % p + p) % p;
}
ll n, k, ans, fac[N], inv[N], cnt, sz;
pair<ll, int> a[N << 1];
ll c(ll n, ll m) {
    if (m < 0 || m > n)
        return 0;
    return fac[n] * inv[m] % p * inv[n - m] % p;
}
int main() {
    n = read(), k = read();
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % p, inv[i] = rev(fac[i]);
    for (int i = 1; i <= n; ++i)
        a[i * 2 - 1] = { read(),1 }, a[i << 1] = { read() + 1,-1 };
    sort(a + 1, a + 1 + n * 2);
    for (int i = 1; i <= n * 2; ++i) {
        ans = (ans + (a[i].first - a[i - 1].first) * c(cnt, k) % p) % p;
        cnt += a[i].second;
    }
    write(ans);
    return 0;
}
```

### 最优关键思路或技巧
1. **转换问题视角**：从计算每种情况的点数和转换为计算每个点在取\(k\)个区间时全都包含的情况数和，大大简化问题。
2. **差分与离散化**：利用差分统计区间覆盖情况，通过离散化处理较大值域，降低时间复杂度。
3. **组合数与逆元**：预处理组合数，并利用逆元处理组合数计算中的除法取模问题。

### 同类型题或类似算法套路
同类型题通常围绕区间计数、组合计算等，类似算法套路为将复杂的区间操作转化为对每个点或小区间的贡献计算，结合差分、离散化、组合数学等知识求解。

### 洛谷推荐题目
1. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)：考察组合数学中的排列组合计数。
2. [P2822 [NOIP2016 提高组] 组合数问题](https://www.luogu.com.cn/problem/P2822)：结合组合数计算与取模运算。
3. [P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389)：涉及组合计数与动态规划的综合应用。

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：90.44秒