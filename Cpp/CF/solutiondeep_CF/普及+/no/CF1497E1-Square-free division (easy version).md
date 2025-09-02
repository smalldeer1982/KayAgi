# 题目信息

# Square-free division (easy version)

## 题目描述

### 题意描述

- 这是简单版，此题中 $k=0$。

给出一串长为 $n$ 的序列 $a_1,a_2,a_3...a_n$。

把它分成尽量少的块使每一块中任意两数的乘积不是一个完全平方数。

输出最少的块数。

## 样例 #1

### 输入

```
3
5 0
18 6 2 4 1
5 0
6 8 1 24 8
1 0
1```

### 输出

```
3
2
1```

# AI分析结果

【题目内容】
# 无平方因子划分（简单版）

## 题目描述

### 题意描述

- 这是简单版，此题中 $k = 0$。

给出一串长为 $n$ 的序列 $a_1,a_2,a_3...a_n$。

把它分成尽量少的块使每一块中任意两数的乘积不是一个完全平方数。

输出最少的块数。

## 样例 #1

### 输入

```
3
5 0
18 6 2 4 1
5 0
6 8 1 24 8
1 0
1
```

### 输出

```
3
2
1
```

【算法分类】
贪心

【综合分析与结论】
这些题解的核心思路都是先对序列中的每个数进行处理，去除其平方数因子，将问题转化为使每个块中没有相同数的问题，然后使用贪心算法进行分段。各题解的区别主要在于处理平方数因子的方法和分段的具体实现方式。
- **思路对比**：大部分题解通过枚举质因数的方式去除平方数因子，部分题解使用欧拉筛预处理；分段时，有的使用 `map` 记录数是否出现，有的使用数组记录数最后出现的位置。
- **算法要点**：关键在于理解两个数乘积为完全平方数的条件是它们所有质因子的指数都为偶数，通过去除平方数因子将问题简化。
- **解决难点**：处理平方数因子的效率和如何高效地进行分段是主要难点，不同题解采用了不同的优化方法。

【所选的题解】
- **作者：redintonc（4星）**
  - **关键亮点**：思路清晰，使用 `map` 进行判断是否已经出现了这个数，实现简单易懂。
```cpp
#include<iostream>
#include<map>
using namespace std;
int a[200005];
int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            int now = a[i];
            for (int j = 2; j * j <= a[i]; j++) {
                int cnt = 0;
                while (now % j == 0)cnt++, now /= j;
                for (int s = 1; s <= cnt - cnt % 2; s++) a[i] /= j;
            }
        }
        int ans = 0;
        map<int, bool>q;
        for (int i = 1; i <= n; i++) {
            if (q[a[i]]) q.clear(), ans++;
            q[a[i]] = 1;
        }
        cout << ++ans << endl;
    }
    return 0;
}
```
核心实现思想：先对输入的每个数去除平方数因子，然后使用 `map` 记录数是否出现，若出现则清空 `map` 并增加分段数。

- **作者：江户川·萝卜（4星）**
  - **关键亮点**：采用栈的方法来减小还原数组的时间，优化了分段过程。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[200005], d[10000005];
int stk[200005], top;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            int x = a[i];
            for (int j = 2; j * j <= x; j++) {
                int cnt = 0; while (x % j == 0) { cnt++; x /= j; }
                for (int k = 1; k <= cnt / 2 * 2; k++) a[i] /= j;
            }
        }
        top = 0;
        int ans = 0, st = 1;
        for (int i = 1; i <= n; i++) {
            if (d[a[i]] >= st) ans++, st = i;
            if (!d[a[i]]) stk[++top] = a[i];
            d[a[i]] = i;
        }
        ans++;
        printf("%d\n", ans);
        while (top) d[stk[top]] = 0, top--;
    }
    return 0;
}
```
核心实现思想：先去除平方数因子，然后使用数组 `d` 记录数最后出现的位置，若当前数最后出现的位置在当前段内，则增加分段数，使用栈来还原数组。

- **作者：Na2PtCl6（4星）**
  - **关键亮点**：使用欧拉筛预处理每个数“减重”后的结果，提高了处理平方数因子的效率。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 10000004;
int t, n, k, top;
int pr[maxn], lw[maxn], vis[maxn], a[maxn], stk[maxn];

signed main() {
    scanf("%d", &t);
    lw[1] = 1;
    for (int i = 2; i < maxn; i++) {
        if (vis[i] == 0) {
            pr[++top] = i;
            lw[i] = i;
        }
        for (int j = 1; pr[j] * i < maxn && j <= top; j++) {
            vis[pr[j] * i] = 1;
            if (i % pr[j] == 0) {
                if (lw[i] % pr[j] == 0)
                    lw[i * pr[j]] = lw[i] / pr[j];
                else
                    lw[i * pr[j]] = lw[i] * pr[j];
                break;
            }
            lw[i * pr[j]] = lw[i] * pr[j];
        }
    }
    top = 0;
    memset(vis, 0, sizeof(vis));
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        int now = 1, res = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[lw[a[i]]] >= now) {
                ++res;
                now = i;
            }
            if (vis[lw[a[i]]] == 0)
                stk[++top] = lw[a[i]];
            vis[lw[a[i]]] = i;
        }
        ++res;
        while (top > 0)
            vis[stk[top--]] = 0;
        printf("%d\n", res);
    }
    return 0;
}
```
核心实现思想：使用欧拉筛预处理每个数“减重”后的结果，然后根据“减重”后的结果进行分段，使用数组 `vis` 记录数最后出现的位置。

【最优关键思路或技巧】
- **去除平方数因子**：将每个数的平方数因子除掉，将问题转化为使每个块中没有相同数的问题。
- **贪心分段**：根据数的出现情况进行贪心分段，遇到重复的数就增加分段数。
- **优化处理**：使用欧拉筛预处理、栈来还原数组等方法提高效率。

【拓展思路】
同类型题可以是类似的序列划分问题，需要根据特定条件进行划分，关键在于找到合适的转化方法将问题简化。类似算法套路包括先对数据进行预处理，然后使用贪心、动态规划等算法进行求解。

【推荐题目】
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

【个人心得】
- **naroto2022**：在本题中，尽量不要使用 `memset` 函数给数组进行赋值。`memset` 函数的时间复杂度为 $O(n)$，其中 $n$ 为数组的字节大小。本题可以通过构造数据使得 `memset` 函数 TLE。总结：在处理大规模数据时，要注意函数的时间复杂度，避免使用可能导致超时的函数。

---
处理用时：55.39秒