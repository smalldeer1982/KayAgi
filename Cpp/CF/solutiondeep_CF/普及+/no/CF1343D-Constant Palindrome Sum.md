# 题目信息

# Constant Palindrome Sum

## 题目描述

You are given an array $ a $ consisting of $ n $ integers (it is guaranteed that $ n $ is even, i.e. divisible by $ 2 $ ). All $ a_i $ does not exceed some integer $ k $ .

Your task is to replace the minimum number of elements (replacement is the following operation: choose some index $ i $ from $ 1 $ to $ n $ and replace $ a_i $ with some integer in range $ [1; k] $ ) to satisfy the following conditions:

- after all replacements, all $ a_i $ are positive integers not greater than $ k $ ;
- for all $ i $ from $ 1 $ to $ \frac{n}{2} $ the following equation is true: $ a_i + a_{n - i + 1} = x $ , where $ x $ should be the same for all $ \frac{n}{2} $ pairs of elements.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4 2
1 2 1 2
4 3
1 2 2 1
8 7
6 1 1 7 6 3 4 6
6 6
5 2 6 1 3 4```

### 输出

```
0
1
4
2```

# AI分析结果

### 题目内容中文重写
## 恒定回文和

### 题目描述
给定一个由 $n$ 个整数组成的数组 $a$（保证 $n$ 是偶数，即能被 $2$ 整除）。所有的 $a_i$ 都不超过某个整数 $k$。

你的任务是替换最少数量的元素（替换操作定义为：选择一个从 $1$ 到 $n$ 的索引 $i$，并将 $a_i$ 替换为范围 $[1; k]$ 内的某个整数），以满足以下条件：
- 所有替换完成后，所有的 $a_i$ 都是不大于 $k$ 的正整数；
- 对于从 $1$ 到 $\frac{n}{2}$ 的所有 $i$，等式 $a_i + a_{n - i + 1} = x$ 成立，其中 $x$ 对于所有 $\frac{n}{2}$ 对元素应该是相同的。

你需要回答 $t$ 个独立的测试用例。

### 样例 #1
#### 输入
```
4
4 2
1 2 1 2
4 3
1 2 2 1
8 7
6 1 1 7 6 3 4 6
6 6
5 2 6 1 3 4
```

#### 输出
```
0
1
4
2
```

### 算法分类
差分

### 综合分析与结论
这些题解的核心思路都是通过枚举最终的和 $x$，计算每一对数需要替换的次数，然后取最小值。不同题解的区别在于计算替换次数的方法。
- **暴力枚举**：直接枚举 $x$，对于每一个 $x$ 计算所有数对需要替换的次数，时间复杂度 $O(nk)$，会超时。
- **差分优化**：通过预处理，计算出对于每一个 $x$，有多少对数可以一个都不替换，有多少可以只替换其中一个，有多少必须两个都要替换，时间复杂度 $O(k + n)$。

### 所选题解
- **Andrewzdm（4星）**
  - **关键亮点**：思路清晰，详细复盘了思考过程，对差分算法的原理有详细解释，代码可读性高。
  - **个人心得**：打比赛时这道题没想出来，等到想出来的时候比赛结束了。通过观察题目中 $k$ 的范围，找到解题突破口，先尝试贪心但失败，最终通过预处理和差分优化算法。
- **andyli（4星）**
  - **关键亮点**：简洁明了地阐述了思路，通过差分将区间操作优化，时间复杂度低。
- **F_Mu（4星）**
  - **关键亮点**：详细分析了数对和的性质，通过前缀和数组处理区间贡献，代码实现简洁。

### 重点代码
#### Andrewzdm 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int equ[2 * maxn], cover[2 * maxn], a[maxn];

signed main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++)
            scanf("%d", a + i);
        fill(equ, equ + 2 * k + 5, 0);
        fill(cover, cover + 2 * k + 5, 0);
        for(int i = 1; i <= n / 2; i++)
            equ[a[i] + a[n - i + 1]]++;
        for(int i = 1; i <= n / 2; i++)
        {
            cover[min(a[i], a[n - i + 1]) + 1]++;
            cover[max(a[i], a[n - i + 1]) + k + 1]--;
        }
        for(int i = 3; i <= 2 * k; i++)
            cover[i] += cover[i - 1];
        int ans = INT_MAX;
        for(int x = 2; x <= 2 * k; x++)
            ans = min(ans, cover[x] - equ[x] + (n / 2 - cover[x]) * 2);
        printf("%d\n", ans);
    }
    return 0;
}
```
**核心实现思想**：通过 `equ` 数组记录和等于 $x$ 的数对数量，通过 `cover` 数组记录至多需要替换一个数的数对数量，利用差分和前缀和计算 `cover` 数组，最后计算每个 $x$ 对应的最少替换步数。

#### andyli 的代码
```cpp
constexpr int maxn = 200005, INF = -1u / 2;

int A[maxn], cnt0[maxn << 1], cnt1[maxn << 1];
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n, k;
        io.read(n, k);
        for (int i = 1; i <= (k << 1); i++)
            cnt0[i] = cnt1[i] = 0;
        for (int i = 1; i <= n; i++)
            io.read(A[i]);
        for (int i = 1; i <= n / 2; i++) {
            cnt0[A[i] + A[n - i + 1]]++;
            cnt1[min(A[i], A[n - i + 1]) + 1]++;
            cnt1[max(A[i], A[n - i + 1]) + k + 1]--;
            cnt1[A[i] + A[n - i + 1]]--;
            cnt1[A[i] + A[n - i + 1] + 1]++;
        }
        int ans = INF;
        for (int i = 2; i <= (k << 1); i++)
            cnt1[i] += cnt1[i - 1], chkmin(ans, cnt1[i] + (n / 2 - cnt1[i] - cnt0[i]) * 2);
        writeln(ans);
    }
    return 0;
}
```
**核心实现思想**：使用 `cnt0` 数组记录和等于 $x$ 的数对数量，`cnt1` 数组通过差分记录需要替换一次的数对数量，最后计算最少替换次数。

#### F_Mu 的代码
```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
const int maxn = (ll) 4e5 + 5;
const int mod = (ll) 1e9 + 7;
const int inf = 0x3f3f3f3f;
int T = 1;
int n, a[maxn], k;
int sum[maxn];

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= 2 * k; ++i)
        sum[i] = 0;
    for (int i = 1; i <= n / 2; ++i) {
        int now = a[i] + a[n - i + 1];
        int maxx = max(a[i], a[n - i + 1]) + k + 1;
        sum[2] += 2;
        --sum[min(a[i], a[n - i + 1]) + 1];
        --sum[now];
        ++sum[now + 1];
        ++sum[maxx];
    }
    int ans = inf;
    for (int i = 2; i <= 2 * k; ++i)
        sum[i] = sum[i - 1] + sum[i], ans = min(ans, sum[i]);
    cout << ans << '\n';
}

signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```
**核心实现思想**：通过 `sum` 数组记录每个 $x$ 的贡献，利用差分和前缀和计算每个 $x$ 对应的替换次数，最后取最小值。

### 最优关键思路或技巧
- **差分优化**：通过差分和前缀和预处理，将时间复杂度从 $O(nk)$ 优化到 $O(k + n)$。
- **区间分析**：分析每一对数在不同和的情况下需要替换的次数，将其转化为区间操作。

### 拓展思路
同类型题目通常会涉及区间操作和优化，例如区间修改、区间查询等问题。可以使用差分、前缀和、树状数组等数据结构进行优化。

### 推荐题目
- [P3397 地毯](https://www.luogu.com.cn/problem/P3397)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)
- [P1083 借教室](https://www.luogu.com.cn/problem/P1083)

---
处理用时：59.02秒