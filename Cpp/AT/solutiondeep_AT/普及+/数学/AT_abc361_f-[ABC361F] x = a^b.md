# 题目信息

# [ABC361F] x = a^b

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_f

$ 1 $ 以上 $ N $ 以下の正整数 $ x $ であって、ある正整数 $ a $ と **$ 2 $ 以上の** 正整数 $ b $ を用いて $ x=a^b $ と表現できるものはいくつありますか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 10^{18} $
 
### Sample Explanation 1

問題文中の条件を満たす整数は $ 1,4,8,9,16,25,27,32,36,49,64,81 $ の $ 12 $ 個です。

## 样例 #1

### 输入

```
99```

### 输出

```
12```

## 样例 #2

### 输入

```
1000000000000000000```

### 输出

```
1001003332```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个正整数 $N$，求在 $1$ 到 $N$ 之间的正整数 $x$，满足存在正整数 $a$ 和 $b$（$b \ge 2$），使得 $x = a^b$。问这样的 $x$ 有多少个？

#### 说明/提示

##### 约束条件

- 输入均为整数
- $1 \le N \le 10^{18}$

##### 样例解释 1

满足条件的整数有 $1, 4, 8, 9, 16, 25, 27, 32, 36, 49, 64, 81$，共 $12$ 个。

##### 样例 #1

###### 输入

```
99
```

###### 输出

```
12
```

##### 样例 #2

###### 输入

```
1000000000000000000
```

###### 输出

```
1001003332
```

---

### 题解综合分析

本题的核心是计算在 $1$ 到 $N$ 之间可以表示为 $a^b$（$b \ge 2$）的数的个数。由于 $N$ 的范围很大（$10^{18}$），直接枚举所有可能的 $a$ 和 $b$ 是不现实的。因此，大多数题解采用了分治策略，将问题分为 $b=2$ 和 $b \ge 3$ 两种情况来处理。

#### 关键思路与技巧

1. **分治策略**：将问题分为 $b=2$ 和 $b \ge 3$ 两种情况。对于 $b=2$，直接计算 $\lfloor \sqrt{N} \rfloor$；对于 $b \ge 3$，枚举 $a$ 和 $b$，并使用 `unordered_set` 或 `map` 去重。
2. **去重处理**：在枚举 $b \ge 3$ 时，需要判断 $a^b$ 是否已经存在于集合中，避免重复计数。
3. **精度问题**：由于 $N$ 很大，使用 `sqrt` 函数可能会产生精度问题，因此建议使用 `sqrtl` 或手动实现二分法来计算平方根。
4. **优化枚举范围**：对于 $b \ge 3$，$a$ 的范围通常限制在 $\sqrt[3]{N}$ 以内，以减少枚举次数。

#### 最优关键思路

- **分治策略**：将问题分为 $b=2$ 和 $b \ge 3$ 两种情况，分别处理。
- **去重处理**：使用 `unordered_set` 或 `map` 来记录已经计算过的 $a^b$，避免重复计数。
- **精度优化**：使用 `sqrtl` 或手动实现二分法来避免精度问题。

---

### 评分较高的题解

#### 题解1：DrAlfred (5星)

**关键亮点**：
- 清晰地分治处理 $b=2$ 和 $b \ge 3$ 的情况。
- 使用 `unordered_set` 去重，代码简洁高效。
- 详细解释了时间复杂度，并提供了优化思路。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
inline bool isPerfectSquare(i64 x) {
    return (i64)sqrt(x) * (i64)sqrt(x) == x;
}
std::unordered_set<i64> s;
int main(int argc, char const *argv[]) {
    i64 n;
    scanf("%lld", &n);
    for (i64 i = 2; i <= 1e6; i++) {
        __int128 curr = i * i;
        while (curr <= n) {
            if (!isPerfectSquare(curr)) {
                s.insert(curr);
            }
            curr = curr * i;
        }
    }
    printf("%lu\n", s.size() + (size_t)sqrtl(n));
    return 0;
}
```

#### 题解2：流水行船CCD (4星)

**关键亮点**：
- 使用二分法优化了 $a$ 的枚举范围。
- 递归处理了重复计数的问题，思路清晰。
- 详细分析了时间复杂度，并提供了优化建议。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
namespace fast_IO{
//省略快读
}using namespace fast_IO;
#define int __int128
const int N = 2e5 + 7;
const int inf = LONG_LONG_MAX;
namespace nogf {
    ll n; int m;
    inline bool qpow(int a, int b, int m) {
        int Res = 1;
        while (b) {
            if (b % 2 == 1) Res *= a;
            if (Res > m) return false;
            if (b > 1) {
                a *= a;
                if (a > m) return false;
            }
            b /= 2;
        }
        return true;
    }
    inline int solve(ll n, int m) {
        int L = 2, R = __lg(n), Ans = 0;
        REP(num, L, R) {
            int l = 2, r = m, Res = 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (qpow(mid, num, m)) l = mid + 1, Res = mid;
                else r = mid - 1;
            } 
            Ans += Res - (Res <= 3 ? 0 : solve(Res, Res)) - 1;
        } return Ans;
    }
    signed main() {
        ld >> n, m = n;
        jyt << solve(n, m) + 1 << '\n';
        return 0;
    }
} 
signed main() {
    nogf::main();
    return 0;
}
```

#### 题解3：nr0728 (4星)

**关键亮点**：
- 详细解释了如何处理 $b=2$ 和 $b \ge 3$ 的情况。
- 使用 `set` 去重，并提供了时间复杂度分析。
- 代码简洁，易于理解。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline bool check2(ll p){
    ll cur=sqrt(p);
    if(cur*cur==p) return 1;
    else return 0;
}
inline ll qkpow(ll n,ll a,ll p){
    ll ans=1ll%p; 
    while(p>0){
        if(p%2==1){
            if(n/ans<a) return -1;
            ans=ans*a;
        }
        p>>=1;
        if(p>0 and n/a<a) return -1;
        a=a*a;
    }
    return ans;
}
inline ll bs(ll n,ll a){
    ll l=2,r=n,ans=1;
    while(l<=r){
        ll mid=(l+r)>>1;
        ll cur=qkpow(n,mid,a);
        if(cur==-1) r=mid-1;
        else ans=mid,l=mid+1;
    }
    return ans;
}
unordered_map<ll,bool>vis;
int main(){
    ll n;scanf("%lld",&n);
    long long ans=0;
    for(int i=2;i<=60;i++){
        ll m=bs(n,i);
        if(i==2){ans+=m;continue;}
        for(int j=1;j<=m;j++){
            ll cur=qkpow(n,j,i);
            if(check2(cur)) continue;
            if(vis[cur]==1) continue;
            ans++; vis[cur]=1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

### 推荐题目

1. [P9118 [春季测试 2023] 幂次](https://www.luogu.com.cn/problem/P9118)
2. [P1934 幂次方](https://www.luogu.com.cn/problem/P1934)
3. [P1045 幂次方](https://www.luogu.com.cn/problem/P1045)

---

### 个人心得总结

- **调试经历**：在处理 $b=2$ 时，使用 `sqrt` 函数可能会导致精度问题，建议使用 `sqrtl` 或手动实现二分法。
- **踩坑教训**：在枚举 $b \ge 3$ 时，需要注意 $a^b$ 可能会超出 `long long` 的范围，建议使用 `__int128` 或手动检查溢出。
- **顿悟感想**：分治策略在处理大范围问题时非常有效，能够显著减少计算量。

---
处理用时：64.77秒