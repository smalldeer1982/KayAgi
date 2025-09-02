# 题目信息

# Divan and bitwise operations

## 题目描述

Once Divan analyzed a sequence $ a_1, a_2, \ldots, a_n $ consisting of $ n $ non-negative integers as follows. He considered each non-empty subsequence of the sequence $ a $ , computed the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of its elements and added up all the XORs, obtaining the coziness of the sequence $ a $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements. For example, $ [1, \, 2, \, 3, \, 4] $ , $ [2, \, 4] $ , and $ [2] $ are subsequences of $ [1, \, 2, \, 3, \, 4] $ , but $ [4, \, 3] $ and $ [0] $ are not.

Divan was very proud of his analysis, but now he lost the sequence $ a $ , and also the coziness value! However, Divan remembers the value of [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) on $ m $ contiguous subsegments of the sequence $ a $ . It turns out that each element of the original sequence is contained in at least one of these $ m $ segments.

Divan asks you to help find the coziness of the sequence $ a $ using the information he remembers. If several coziness values are possible, print any.

As the result can be very large, print the value modulo $ 10^9 + 7 $ .

## 说明/提示

In first example, one of the sequences that fits the constraints is $ [0, 2] $ . Consider all its non-empty subsequences:

- $ [0] $ : the bitwise XOR of this subsequence is $ 0 $ ;
- $ [2] $ : the bitwise XOR of this subsequence is $ 2 $ ;
- $ [0, 2] $ : the bitwise XOR of this subsequence is $ 2 $ .

The sum of all results is $ 4 $ , so it is the answer.

In second example, one of the sequences that fits the constraints is $ [0, \, 5, \, 5] $ .

In third example, one of the sequences that fits the constraints is $ [5, \, 6, \, 7, \, 0, \, 2] $ .

## 样例 #1

### 输入

```
3
2 1
1 2 2
3 2
1 3 5
2 3 5
5 4
1 2 7
3 3 7
4 4 0
4 5 2```

### 输出

```
4
20
112```

# AI分析结果

### 题目翻译
## Divan和位运算

### 题目描述
有一次，Divan分析了一个由 $n$ 个非负整数组成的序列 $ a_1, a_2, \ldots, a_n $，分析过程如下。他考虑序列 $ a $ 的每个非空子序列，计算其元素的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)，并将所有异或值相加，从而得到序列 $ a $ 的舒适值。

如果序列 $ c $ 可以通过删除序列 $ d $ 中的若干（可能为零个或全部）元素得到，那么序列 $ c $ 就是序列 $ d $ 的子序列。例如，$ [1, \, 2, \, 3, \, 4] $、$ [2, \, 4] $ 和 $ [2] $ 是 $ [1, \, 2, \, 3, \, 4] $ 的子序列，但 $ [4, \, 3] $ 和 $ [0] $ 不是。

Divan 对自己的分析非常自豪，但现在他弄丢了序列 $ a $ 以及舒适值！不过，Divan 记得序列 $ a $ 的 $ m $ 个连续子段的[按位或](https://en.wikipedia.org/wiki/Bitwise_operation#OR)值。事实证明，原始序列中的每个元素至少包含在这 $ m $ 个子段中的一个中。

Divan 请你根据他记得的信息帮助他找到序列 $ a $ 的舒适值。如果可能有多个舒适值，打印其中任意一个。

由于结果可能非常大，请将结果对 $ 10^9 + 7 $ 取模后输出。

### 说明/提示
在第一个示例中，符合条件的序列之一是 $ [0, 2] $。考虑它的所有非空子序列：
- $ [0] $：这个子序列的按位异或值是 $ 0 $；
- $ [2] $：这个子序列的按位异或值是 $ 2 $；
- $ [0, 2] $：这个子序列的按位异或值是 $ 2 $。

所有结果的和是 $ 4 $，所以这就是答案。

在第二个示例中，符合条件的序列之一是 $ [0, \, 5, \, 5] $。

在第三个示例中，符合条件的序列之一是 $ [5, \, 6, \, 7, \, 0, \, 2] $。

### 样例 #1
#### 输入
```
3
2 1
1 2 2
3 2
1 3 5
2 3 5
5 4
1 2 7
3 3 7
4 4 0
4 5 2
```

#### 输出
```
4
20
112
```

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是先处理出所有区间或值的按位或结果，再结合位运算和组合数学的知识计算序列所有子序列的异或和。不同题解的差异在于是否构造出具体序列以及计算子序列异或和的方式。部分题解通过数学推导直接得出结果，部分题解则通过构造序列和递推的方式计算。

### 所选题解
- **VinstaG173（5星）**
    - **关键亮点**：思路清晰，直接给出结论并进行详细证明，通过数学推导得出答案就是所有 $x$ 的 `or` 和乘以 $2^{n - 1}$，避免了复杂的序列构造和计算过程。
- **orz_z（4星）**
    - **关键亮点**：简洁明了地阐述了解题思路，代码实现简单高效，直接计算所有 $x$ 的按位或，然后乘以 $2^{n - 1}$ 得到答案。
- **Shxt_Plus（4星）**
    - **关键亮点**：通过拆位计算，利用组合数学知识推导出答案与序列具体值无关，只与每一位是否有 $1$ 有关，简化了计算过程。

### 重点代码
#### VinstaG173（思路代码）
```plaintext
答案就是所有 x 的 `or` 和乘以 2^{n - 1}。
```
核心实现思想：通过数学推导得出所有 $a_i$ 的 `or` 和等于所有 $x$ 的 `or` 和，然后计算每一位对答案的贡献，最终得到答案。

#### orz_z
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {...}
const int mod = 1e9 + 7;
inline int qpow(int x, int y) {...}
int T, n, m;
signed main() {
    T = read();
    while (T--) {
        n = read(), m = read();
        int ans = 0;
        while (m--) {
            read(), read();
            ans = ans | read();
        }
        ans = ans * qpow(2, n - 1) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```
核心实现思想：先读取所有区间或值，计算它们的按位或结果，然后将结果乘以 $2^{n - 1}$ 并对 $10^9 + 7$ 取模得到答案。

#### Shxt_Plus
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int t,n,m;
int po(int x,int n) {...}
signed main() {
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld%lld",&n,&m);
        int p = 0, ans = 0;
        for(int i = 1; i <= m; i++) {
            int s, t, v;
            scanf("%lld%lld%lld",&s,&t,&v);
            p |= v;
        }
        for(int i = 0; i <= 60; i++) {
            if(p & (1ll << i)) {
                ans += (1ll << i) % mod;
                ans %= mod;
            }
        }
        printf("%lld\n", ans * po(2, n - 1) % mod);
    }
    return 0;
}
```
核心实现思想：先计算所有区间或值的按位或结果 $p$，然后遍历 $p$ 的每一位，若该位为 $1$ 则将对应的 $2^i$ 累加到 $ans$ 中，最后将 $ans$ 乘以 $2^{n - 1}$ 并对 $10^9 + 7$ 取模得到答案。

### 关键思路或技巧
- **位运算**：利用按位或和按位异或的性质，简化计算过程。
- **组合数学**：通过组合数学知识推导出每一位对答案的贡献，避免了枚举所有子序列的复杂计算。
- **数学推导**：直接通过数学推导得出答案与所有 $x$ 的按位或结果的关系，避免构造具体序列。

### 拓展思路
同类型题目可能会改变序列的限制条件或计算目标，但核心思路仍然是利用位运算和组合数学的知识。例如，可能会给出更多关于序列的信息，或者要求计算不同的统计量。类似算法套路包括拆位计算、利用位运算性质简化计算等。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及队列和滑动窗口的操作，与位运算结合可以解决一些复杂的问题。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可以使用树状数组或归并排序来解决，与本题的组合数学和位运算有一定的关联。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基础应用，掌握树状数组可以更好地处理区间查询和修改问题。

### 个人心得
- **Shxt_Plus**：模拟赛上因没输出换行喜提 $0$ 分的好成绩。总结：在比赛中要注意输出格式，避免因小错误导致丢分。

---
处理用时：59.65秒