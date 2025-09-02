# 题目信息

# [BalticOI 2015] Hacker

## 题目描述

### 题面描述

Byteasar 获得了今年国际黑客奥林匹克竞赛的参赛资格。竞赛的任务之一是与系统操作员竞争。有从 $1$ 到 $n$ 编号的 $n$ 台计算机，以环形连接，即计算机 $i$ 和 $i+1$ 连接（其中 $i = 1,2,\dots,n-1$），特别地，计算机 $n$ 和 $1$ 也连接。

这个任务是黑客和系统操作员之间的游戏：

- Byteasar 先走。之后，操作员和 Byteasar 交替移动。
- Byteasar 的第一步是选择任何一台计算机并对其进行黑客攻击。
- 在他的第一步中，操作员选择任何未被黑客攻击的计算机并对其进行保护。
- 在接下来的所有动作中，Byteasar 要么什么都不做，要么选择任何既没有被黑客攻击也没有受到保护的计算机，并直接链接到任何被黑客攻击的计算机，然后对其进行黑客攻击。
- 在接下来的所有动作中，操作员要么什么都不做，要么选择任何既没有被黑客攻击也没有受到保护的计算机，直接链接到任何受保护的计算机并对其进行保护。
- 一旦两人在接下来的两个动作中都没有做任何事情，游戏就结束了。

在游戏开始时，没有任何一台电脑被黑客攻击或受到保护。

每台计算机 $i$ 都有一个特定的值 $v_i$，该值指定了存储在其上的数据的价值。Byteasar 最终获得的分数就是所有被他攻击的计算机的 $v$ 值之和。

虽然 Byteasar 是一个很好的黑客，但对算法一无所知——这就是为什么他要求你编写一个程序来计算他的最大可能分数，假设操作员按最优策略。

## 样例 #1

### 输入

```
4
7 6 8 4```

### 输出

```
13```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均基于相同的认识：若Byteasar第一步选择位置i，系统操作员能将其限制在经过i的长度为$\lceil \frac{n}{2} \rceil$的序列，且操作员会选择价值最小的序列。因此，问题转化为求经过每个位置的长度为$\lceil \frac{n}{2} \rceil$的序列价值的最小值，再取这些最小值中的最大值。

各题解在算法实现上有所不同，主要区别在于如何高效地处理区间和与区间最值查询：
 - **WarningQAQ**：提出用线段树或前缀和 + 二分来维护序列，线段树能解决问题但速度慢，前缀和 + 二分优化后代码简短高效。
 - **tanghg**：断环成链，用前缀和预处理区间和，通过ST表记录区间元素之和，枚举电脑计算能经过它的区间的最小值，时间复杂度$O(nlogn)$。
 - **MagicalGirl_0d00**：使用单调队列维护包含每个点的长度为$\lceil \frac{n}{2} \rceil$的区间和的最小值，时间复杂度$O(n)$。
 - **lzhm**：利用线段树记录以每个位置为左端点的长度为$\lceil \frac{n}{2} \rceil$的区间和，通过区间查询获取包含某位置的区间最小值，时间复杂度$O(nlogn)$。
 - **船酱魔王**：将所有长度符合要求的连续段按和从大到小排序，用区间覆盖的方式求解，时间复杂度$O(nlogn)$。
 - **_EternalRegrets_**：与MagicalGirl_0d00思路类似，用单调队列计算对于每一种第一个点的选择方法下，包含这个点的最小序列长度，时间复杂度$O(n)$。
 - **wjr_jok**：枚举Byteasar最初选择的点，用前缀和求答案，通过线段树维护区间最小值，时间复杂度$O(nlogn)$。

综合来看，使用单调队列的方法在时间复杂度上最优，代码实现也较为简洁。

### 所选的题解
- **WarningQAQ（5星）**
    - **关键亮点**：提出两种解法，不仅给出线段树的常规思路，还进一步优化为前缀和 + 二分的高效解法，思路清晰且代码简短。
    - **核心代码实现思想**：通过前缀和数组`sum`快速计算区间和，利用二分查找在排序后的区间和数组中找到合适的值。
```cpp
// code2核心代码
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, a[N], sum[N << 1];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }
    int sa = ceil(n * 1.0 / 2);
    vector<int> v;
    for (int i = 1; i <= 2 * n; ++i) {
        if (i + sa - 1 <= 2 * n) {
            v.push_back(sum[i + sa - 1] - sum[i - 1]);
        }
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = 0, r = v.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            int num = 0;
            for (int j = 0; j < v.size(); ++j) {
                if (v[j] >= v[mid]) {
                    num++;
                }
            }
            if (num >= i) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        ans = max(ans, v[l]);
    }
    cout << ans << endl;
    return 0;
}
```
 - **MagicalGirl_0d00（5星）**
    - **关键亮点**：利用单调队列维护区间和的最小值，时间复杂度为$O(n)$，是所有解法中时间复杂度最优的，且代码简洁明了。
    - **核心代码实现思想**：通过`sum`数组记录前缀和，在遍历过程中，利用单调队列`q`维护当前窗口内的最小区间和。
```cpp
// 核心代码
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000001], ans, sum[1000001];
deque<int> q;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 1; i <= (n + 1) / 2 - 1; i++) {
        while (q.size() && q.front() + (n + 1) / 2 - 1 < i) q.pop_front();
        while (q.size() && sum[q.back() + (n + 1) / 2 - 1] - sum[q.back() - 1] > sum[i + (n + 1) / 2 - 1] - sum[i - 1]) q.pop_back();
        q.push_back(i);
    }
    for (int i = (n + 1) / 2; i + (n + 1) / 2 - 1 <= 2 * n; i++) {
        while (q.size() && q.front() + (n + 1) / 2 - 1 < i) q.pop_front();
        while (q.size() && sum[q.back() + (n + 1) / 2 - 1] - sum[q.back() - 1] > sum[i + (n + 1) / 2 - 1] - sum[i - 1]) q.pop_back();
        q.push_back(i);
        ans = max(ans, sum[q.front() + (n + 1) / 2 - 1] - sum[q.front() - 1]);
    }
    cout << ans;
    return 0;
}
```
 - **tanghg（4星）**
    - **关键亮点**：采用断环成链的方法，结合前缀和与ST表解决问题，思路清晰，代码实现较为常规，适合初学者理解。
    - **核心代码实现思想**：通过前缀和数组`f`快速计算区间和，利用ST表`st`记录区间最小值，通过`query`函数查询区间最小值。
```cpp
// 核心代码
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1e6 + 5;
ll n, a[MAXN], f[MAXN];
ll st[MAXN][20], lg[MAXN];
ll query(ll l, ll r) {
    ll len = lg[r - l + 1];
    return min(st[l][len], st[r - (1 << len) + 1][len]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        f[i] = f[i - 1] + a[i];
    }
    ll sa = ceil(n * 1.0 / 2);
    for (int i = 2; i < MAXN; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }
    for (int i = 1; i <= 2 * n; ++i) {
        st[i][0] = f[i + sa - 1] - f[i - 1];
    }
    for (int l = 1; l <= lg[2 * n]; ++l) {
        for (int i = 1; i + (1 << l) - 1 <= 2 * n; ++i) {
            st[i][l] = min(st[i][l - 1], st[i + (1 << (l - 1))][l - 1]);
        }
    }
    ll ans = 0;
    for (int i = sa; i <= 2 * n; ++i) {
        ans = max(ans, query(i - sa + 1, i));
    }
    cout << ans << endl;
    return 0;
}
```

### 最优关键思路或技巧
- **单调队列优化**：在处理固定长度区间的最值问题时，单调队列可以在$O(n)$时间复杂度内完成，相比线段树或ST表的$O(nlogn)$时间复杂度更高效。通过维护队列的单调性，每次新元素加入时，将队列中比其大的元素弹出，保证队首始终为当前窗口内的最小值。
 - **前缀和优化区间和计算**：通过预处理前缀和数组，能在$O(1)$时间内计算任意区间的和，大大提高计算效率。

### 可拓展之处
此类题目属于博弈论与区间问题结合的类型。类似算法套路包括：
 - **处理环形数据结构**：常采用破环成链的方法，将环形问题转化为线性问题处理，如本题中多个题解将环形的计算机连接转化为线性数组。
 - **博弈论策略分析**：分析双方最优策略，确定问题核心，如本题确定操作员会使Byteasar选择价值最小的区间。

### 相似知识点洛谷题目
 - **P1886 滑动窗口**：考察单调队列在滑动窗口求最值问题中的应用。
 - **P3865 [TJOI2009] 最长公共子序列**：涉及动态规划和区间问题，与本题通过分析策略转化为区间最值问题有相似思路。
 - **P1983 车站分级**：结合拓扑排序与区间问题，与本题在分析问题并转化为合适的数据结构求解方面有类似思考过程。

### 个人心得摘录与总结
本题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。 

---
处理用时：58.18秒