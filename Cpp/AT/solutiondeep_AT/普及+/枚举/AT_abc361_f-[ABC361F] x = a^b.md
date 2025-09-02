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

### 题目翻译
#### [ABC361F] x = a^b

#### 题目描述
[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_f

求 $1$ 以上 $N$ 以下的正整数 $x$ 中，能使用某个正整数 $a$ 和 **$2$ 以上** 的正整数 $b$ 表示为 $x = a^b$ 的数有多少个？

#### 说明/提示
##### 限制条件
- 输入均为整数
- $1 \leq N \leq 10^{18}$

##### 样例解释 1
满足题目条件的整数有 $1,4,8,9,16,25,27,32,36,49,64,81$，共 $12$ 个。

#### 样例 #1
##### 输入
```
99
```
##### 输出
```
12
```

#### 样例 #2
##### 输入
```
1000000000000000000
```
##### 输出
```
1001003332
```

### 综合分析与结论
这些题解的核心思路都是将问题拆分为 $b = 2$ 和 $b \geq 3$ 两种情况处理。对于 $b = 2$，直接计算 $\lfloor\sqrt{n}\rfloor$；对于 $b \geq 3$，通过枚举或二分等方法找出所有可能的 $a^b$，并处理重复计数问题。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|DrAlfred|枚举 $b \geq 3$ 的情况，用 `std::unordered_set` 去重，$b = 2$ 时直接计算 $\lfloor\sqrt{n}\rfloor$ 并排除重复|枚举、去重、判断完全平方数|避免 $b = 2$ 时的重复计数|4星|
|流水行船CCD|枚举 $b$，二分求最大的 $c$ 使 $c^b \leq N$，递归处理重复计数|枚举、二分、递归容斥|处理重复计数问题|4星|
|zhlzt|枚举 $b$，暴力判重，二分求 $a$ 的上界|枚举、判重、二分|处理重复计数和避免越界|3星|
|nr0728|按 ABC193C 思路，枚举 $b \geq 3$ 且非平方数，最终答案为 `set` 大小加 $\lfloor\sqrt{n}\rfloor$|枚举、去重|避免平方数重复计算|3星|
|qhr2023|分类讨论，偶次幂转平方，暴力枚举奇次幂并标记去重|分类讨论、暴力枚举、标记去重|处理重复计数|3星|
|wly09|容斥原理，用莫比乌斯函数计算，牛顿迭代法开根|容斥、莫比乌斯函数、牛顿迭代法|处理重复计数和精度问题|3星|
|WHYMJJ|枚举 $b > 2$ 的情况，用 `map` 标记去重，答案为 $\lfloor\sqrt{n}\rfloor$ 加枚举结果|枚举、标记去重|避免平方数重复计算|3星|
|Starrykiller|考虑 $b = 2$ 和 $b = 3$ 情况，用莫比乌斯函数处理重复，规避精度问题|莫比乌斯函数、精度处理|处理重复计数和精度问题|3星|
|OldDriverTree|莫比乌斯反演，计算 $f(x)$ 和 $g(x)$ 得出答案|莫比乌斯反演|函数计算和复杂度分析|3星|
|littlebug|暴力枚举 $b \neq 2$ 的情况，直接累乘计算幂，手写开方|暴力枚举、累乘、手写开方|避免越界和精度问题|3星|
|Hughpig|枚举 $b > 2$ 的情况，用 `map` 维护重复，$b = 2$ 时直接计算|枚举、标记去重|处理重复计数|3星|
|Genius_Star|用 $\sqrt{N}$ 统计平方数，预处理非平方数贡献，二分查找|统计、预处理、二分查找|处理非平方数贡献和去重|3星|
|Binah_cyc|分类讨论，偶数次幂转平方，枚举奇数次幂并标记去重|分类讨论、枚举、标记去重|处理重复计数|3星|
|Pentiment|枚举 $b > 2$ 的情况，手动调整 `sqrt` 精度|枚举、精度调整|处理精度问题|3星|
|Redshift_Shine|暴力枚举 $b \geq 3$ 的情况，统计完全平方数，用 `sqrtl` 避免精度问题|暴力枚举、统计、精度处理|处理重复计数和精度问题|3星|
|1234567890sjx|暴力枚举 $b \geq 3$ 的情况，容斥处理 $b = 2$ 时的重复|暴力枚举、容斥|处理重复计数|3星|
|joe_zxq|枚举 $k \leq 3$ 的情况，标记完全平方数，用 `sqrtl` 避免精度问题|枚举、标记、精度处理|处理重复计数和精度问题|3星|
|云裳|枚举 $a,b$，判断 $a^b$ 是否为完全平方数，用 `set` 去重|枚举、判断、去重|处理重复计数和精度问题|3星|
|Liyunze123|枚举底数 $2$ 到 $k$，跳过重复底数，补上 $k + 1$ 至 $l$ 的贡献|枚举、跳过重复、贡献补充|处理重复计数|3星|
|2c_s|枚举 $k \geq 3$ 的情况，用 `unordered_map` 标记，统计完全平方数|枚举、标记、统计|处理重复计数|3星|
|Milthm|分别计算 $b = 2$ 和 $b \geq 3$ 的情况，用 `map` 去重，二分求平方根|分别计算、去重、二分|处理重复计数和精度问题|3星|

### 所选题解
- **DrAlfred（4星）**
    - **关键亮点**：思路清晰，利用 $b \geq 3$ 时 $a$ 的范围较小的性质进行枚举，使用 `std::unordered_set` 高效去重，避免了 $b = 2$ 时的重复计数。
    - **核心代码**：
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
- **流水行船CCD（4星）**
    - **关键亮点**：通过枚举 $b$ 并二分查找最大的 $c$ 使 $c^b \leq N$，利用递归处理重复计数问题，思路巧妙。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
using namespace std;
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
            Ans += Res - (Res <= 3? 0 : solve(Res, Res)) - 1; 
        } return Ans;
    }
    signed main() {
        cin >> n, m = n;
        cout << solve(n, m) + 1 << '\n'; 
        return 0;
    }
} 
signed main() {
    nogf::main();
    return 0;
}	
```

### 最优关键思路或技巧
- **分类讨论**：将问题拆分为 $b = 2$ 和 $b \geq 3$ 两种情况，分别处理，降低复杂度。
- **去重处理**：使用 `std::unordered_set`、`map` 等数据结构去重，避免重复计数。
- **精度处理**：使用 `sqrtl` 或二分查找等方法避免 `sqrt` 带来的精度问题。

### 拓展思路
同类型题目可能会改变指数 $b$ 的范围或限制条件，解题时仍可采用分类讨论、枚举、去重等思路。类似算法套路可用于处理其他幂次相关的计数问题。

### 推荐题目
- [P9118 [春季测试 2023] 幂次](https://www.luogu.com.cn/problem/P9118)
- [AT_abc193_c Unexpressed](https://www.luogu.com.cn/problem/AT_abc193_c)
- [P1010 [NOIP1998 普及组] 幂次方](https://www.luogu.com.cn/problem/P1010)

### 个人心得摘录与总结
- **Redshift_Shine**：使用 `sqrt` 会有精度问题，吃了 2 发罚时，建议用 `sqrtl`。
- **joe_zxq**：该题卡精度，使用 `sqrt()` 会挂一个点，需要使用精度较高的 `sqrtl()`。
- **云裳**：开根记得使用 `sqrtl`，不然会炸。

总结：在处理涉及开方的问题时，要注意 `sqrt` 可能存在的精度问题，可使用 `sqrtl` 或二分查找等方法避免。 

---
处理用时：65.78秒