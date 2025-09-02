# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果

• **综合分析与结论**：这些题解主要围绕从给定序列中选出满足特定条件子序列并求其最大和的问题。多数题解先对条件\(b_i + b_j + \gcd(b_i, b_j) = \mathrm{lcm}(b_i, b_j)\)进行推导，得出若\(b_i < b_j\)，则\(b_i:b_j = 2:3\)的关键结论。基于此，常见做法是对原序列排序，通过枚举最小值确定整个子序列，利用二分查找或`map`等方式查找序列中的数，计算并更新满足条件子序列的最大和。不同题解在推导过程、代码实现细节及复杂度优化上存在差异。
• **所选的题解**：
  - **作者：Alex_Wei（5星）**
    - **关键亮点**：作为官方题解，思路清晰，先按子任务分析，从简单到复杂，逐步引导解题思路。对关键结论的推导详细，给出完整证明过程。在最终解法中，明确指出用二分或`map`实现查找的时间复杂度及注意事项，代码简洁明了。
    - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 3e5 + 5;

map<int, int> mp;
int n, a[N];
ll ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], mp[a[i]]++;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        ll tmp = a[i], cnt = 0;
        while (mp[tmp]) {
            cnt += tmp * mp[tmp], mp[tmp] = 0;
            if (tmp % 2 == 0) tmp = tmp / 2 * 3;
            else break;
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
```
核心思想是先将每个数出现的次数用`map`记录，排序后从每个数开始，若该数为偶数则按\(tmp = tmp / 2 * 3\)的规则找下一个数，累加对应数的和并标记已访问，更新最大和。
  - **作者：InformationEntropy（4星）**
    - **关键亮点**：详细推导得出关键结论，对结论的应用思路清晰，指出要枚举合法序列的最小数确定整个序列，同时强调了标记已使用数和处理相同数的重要性，并给出`map`和二分两种实现方式及对应代码，对不同实现方式的时间复杂度有清晰分析。
    - **重点代码及核心思想（二分代码）**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a, b) (a>b)?a:b;
using namespace std;
typedef long long ll;
inline void read(int &x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    x *= f;
}
int a[1000001];
struct node {
    int x, times;
} s[1000001];
int cnt;
int find(int n) {
    int l = 1, r = cnt;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (s[mid].x == n) return mid;
        else if (s[mid].x < n) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
int main() {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i]!= a[i - 1]) {
            s[++cnt].x = a[i];
            s[cnt].times = 1;
        }
        else {
            s[cnt].times++;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll t = a[i];
        ll sum = 0;
        int sub = find(t);
        while (s[sub].times) {
            sum += t * s[sub].times;
            s[sub].times = 0;
            if (t % 2 == 0) {
                t = t / 2 * 3;
                sub = find(t);
                if (sub == -1) break;
            }
            else break;
        }
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}
```
核心思想是用结构体数组`s`记录每个数及其出现次数，通过二分查找`find`函数确定数在数组中的位置，从每个数开始，若为偶数则按规则找下一个数，累加对应数的和并更新最大和。
  - **作者：Lonely_NewYear（4星）**
    - **关键亮点**：对条件式子推导得出关键结论，基于结论提出用递推思想解决问题，定义数组\(f_i\)表示\(a_i\)为最大值时满足条件的数列和的最大值，通过排序保证无后效性，在代码实现中考虑到相同数的特判，整体思路和代码实现简洁高效。
    - **重点代码及核心思想**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long f[300001], ans;
int n, a[300001];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = a[i];
        if (a[i - 1] == a[i]) {
            f[i] += f[i - 1];
        }
        else if (a[i] % 3 == 0 && binary_search(a + 1, a + n + 1, a[i] / 3 * 2)) {
            int j = upper_bound(a + 1, a + n + 1, a[i] / 3 * 2) - a - 1;
            f[i] += f[j];
        }
        ans = max(ans, f[i]);
    }
    printf("%lld", ans);
    return 0;
}
```
核心思想是排序后，对于每个数\(a[i]\)，若与前一个数相同则累加\(f[i - 1]\)，若\(a[i]\)能整除3且存在\(a[i] / 3 * 2\)，则找到其位置\(j\)并累加\(f[j]\)，最后更新最大和。
• **最优关键思路或技巧**：通过对条件式子进行数学推导得出关键结论，利用排序和递推思想，结合二分查找或`map`数据结构来高效查找和处理序列中的数，从而优化时间复杂度。在处理相同数时，通过记录出现次数或特判来避免重复计算。
• **可拓展之处**：此类题目属于数论与序列结合的问题，类似套路是对给定的数学条件进行推导，得出数与数之间的关系，再利用数据结构或算法优化来解决序列选择或计算问题。例如在其他涉及最大公约数、最小公倍数及序列选择的题目中，可尝试推导数之间的关系，再结合排序、搜索等算法解决。
• **推荐题目**：
  - **P1072 [NOIP2009 提高组]  Hankson 的趣味题**：涉及最大公约数和最小公倍数的计算与推导，与本题类似，需根据给定条件确定数的取值。
  - **P2152 [SDOI2009]  SuperGCD**：主要考察大整数的最大公约数计算，可加深对最大公约数算法的理解和应用。
  - **P2568 GCD**：通过枚举和数论知识解决关于最大公约数的计数问题，锻炼数论与枚举优化的能力。
• **个人心得摘录**：多数题解作者强调推导条件式子得出关键结论是解题关键，部分作者提到在实现过程中要注意处理相同数以及避免重复计算，如使用标记数组或在数据结构中记录出现次数等方式。还有作者指出在面对复杂条件时，可通过打表找规律辅助解题。 

---
处理用时：80.98秒