# 题目信息

# Frets On Fire

## 题目描述

## 题目背景
Miyako 带着尤克里里琴来到跳蚤王国。她与当地的跳蚤居民成为了好朋友，每天为他们演奏美妙的音乐。

作为回报，跳蚤为她做了一个更大的尤克里里琴：它有 $n$ 个弦，每个弦都有从 $0$ 到 $10^{18}$ 的 $10^{18}+1$ 个琴格（用来给琴划分音阶高低）。跳蚤使用数组 $s_1, s_2,......,s_n$ 来描述尤克里里琴的品，也就是说，第 $i$ 个弦上第 $j$ 个琴格的音调是整数 $s_i+j$。

Miyako 即将离开王国，但跳蚤希望 Miyako 能为它们回答最后一些问题。

第 $k$ 个问题是：“在所有弦上，琴格 $l_k$ 与琴格 $r_k$（包括 $l_k$，$r_k$）之间有多少个不同的音调？”

Miyako 即将访问蟋蟀王国，没有时间回答所有问题。请你帮助她完成这项任务！

在形式上，给出一个 $n$ 行 $10^{18}+1$ 列的矩阵，其中第 $i$  行（$1 \leqslant i \leqslant n$）第 $j$ 列（$0 \leqslant j \leqslant 10^{18}$）中的单元格为整数 $s_i+j$。有 $q$ 个询问，对于第 $k$ 个询问，你需要回答矩阵中从第 $l_k$ 列到第 $r_k$ 列（包括 $l_k$，$r_k$）的不同整数的数量。

## 样例 #1

### 输入

```
6
3 1 4 1 5 9
3
7 7
0 2
8 17
```

### 输出

```
5 10 18
```

## 样例 #2

### 输入

```
2
1 500000000000000000
2
1000000000000000000 1000000000000000000
0 1000000000000000000
```

### 输出

```
2 1500000000000000000
```

# AI分析结果

【题目内容】
# 尤克里里的品格

## 题目描述

### 题目背景
Miyako 带着尤克里里来到跳蚤王国。她与当地的跳蚤居民成为了好朋友，每天为他们演奏美妙的音乐。

作为回报，跳蚤为她做了一个更大的尤克里里：它有 $n$ 根弦，每根弦都有从 $0$ 到 $10^{18}$ 的 $10^{18}+1$ 个品格（用来给琴划分音阶高低）。跳蚤使用数组 $s_1, s_2,......,s_n$ 来描述尤克里里的品格，也就是说，第 $i$ 根弦上第 $j$ 个品格的音调是整数 $s_i+j$。

Miyako 即将离开王国，但跳蚤希望 Miyako 能为它们回答最后一些问题。

第 $k$ 个问题是：“在所有弦上，品格 $l_k$ 与品格 $r_k$（包括 $l_k$，$r_k$）之间有多少个不同的音调？”

Miyako 即将访问蟋蟀王国，没有时间回答所有问题。请你帮助她完成这项任务！

在形式上，给出一个 $n$ 行 $10^{18}+1$ 列的矩阵，其中第 $i$  行（$1 \leqslant i \leqslant n$）第 $j$ 列（$0 \leqslant j \leqslant 10^{18}$）中的单元格为整数 $s_i+j$。有 $q$ 个询问，对于第 $k$ 个询问，你需要回答矩阵中从第 $l_k$ 列到第 $r_k$ 列（包括 $l_k$，$r_k$）的不同整数的数量。

## 样例 #1

### 输入

```
6
3 1 4 1 5 9
3
7 7
0 2
8 17
```

### 输出

```
5 10 18
```

## 样例 #2

### 输入

```
2
1 500000000000000000
2
1000000000000000000 1000000000000000000
0 1000000000000000000
```

### 输出

```
2 1500000000000000000
```

【算法分类】
二分

【综合分析与结论】
这些题解的核心思路都是先利用区间平移答案不变的性质，将询问区间 $[l, r]$ 转化为 $[0, r - l]$，再通过不同方法计算不同音调的数量。多数题解采用了排序、前缀和与二分查找的组合来优化计算过程，部分题解使用了贪心、权值线段树等方法。
- **思路对比**：大部分题解通过计算相邻品格音调差值的前缀和，再利用二分查找确定填补空隙的贡献；Moyou 的题解采用反悔贪心，通过维护 $cnt$ 和 $sum$ 变量计算答案；huayt 的题解使用权值线段树统计重复音调数量。
- **算法要点**：排序用于对品格音调数组排序，方便后续计算差值；前缀和用于快速计算差值的累加和；二分查找用于确定填补空隙的位置；贪心和权值线段树是特殊的解题思路。
- **解决难点**：主要难点在于处理重复音调，不同题解通过不同方式解决。如计算差值、填补空隙、统计重复数量等。

【所选题解】
- StudyingFather（4星）：思路清晰，代码简洁，通过排序、前缀和与二分查找解决问题，易于理解和实现。
- Moyou（4星）：采用反悔贪心的思路，有创新性，时间复杂度合理，代码实现规范。
- Zechariah（4星）：思路简洁，利用前缀和与二分查找，代码实现高效。

【重点代码】
#### StudyingFather
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
long long s[100005],d[100005],sum[100005];
int main()
{
    long long n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    sort(s+1,s+n+1);
    for(int i=1;i<n;i++)
        d[i]=s[i+1]-s[i]-1;
    sort(d+1,d+n);
    for(int i=1;i<n;i++)
        sum[i]=sum[i-1]+d[i];
    int q;
    cin>>q;
    while(q--)
    {
        long long l,r;
        cin>>l>>r;
        r-=l;
        int p=upper_bound(d,d+n,r)-d;
        cout<<n+r+sum[p-1]+(n-p)*r<<endl;
    }
    return 0;
}
```
**核心实现思想**：先对品格音调数组排序，计算相邻元素差值，再对差值排序并求前缀和。对于每个询问，将区间平移，通过二分查找确定填补空隙的位置，计算不同音调的数量。

#### Moyou
```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;

const int N = 2e5 + 10;

int n;
int a[N];
int lim[N];
struct qwq
{
    int l, r, w, id;
    bool operator<(const qwq &W) const
    {
        return w < W.w;
    }
} p[N];
int ans[N];
int sum = 0, cnt;
priority_queue<int, vector<int>, greater<int>> heap;

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    lim[n] = 2e18 + 1;
    for (int i = n - 1; i >= 1; i--)
        lim[i] = a[i + 1] - a[i];
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> p[i].l >> p[i].r;
        p[i].w = p[i].r - p[i].l + 1;
        p[i].id = i;
    }
    cnt = n;
    for (int i = 1; i <= n; i++)
        heap.push(lim[i]);
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= m; i++)
    {
        while (heap.size() && heap.top() < p[i].w)
        {
            cnt--;
            sum += heap.top();
            heap.pop();
        }
        ans[p[i].id] = cnt * p[i].w + sum;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}
```
**核心实现思想**：先计算每个琴弦的最大贡献琴格数 $lim$，将询问离线并按区间长度排序。使用小根堆维护 $lim$，在枚举询问时，通过反悔贪心更新 $cnt$ 和 $sum$ 变量，计算每个询问的答案。

#### Zechariah
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
typedef unsigned int uint;
const int N = 5e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll s[N], d[N];
ll sum[N];

int main(void) {
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)s[i] = fast_IO::read();
    sort(s + 1, s + n + 1);
    n = unique(s + 1, s + n + 1) - s - 1;
    for (rg int i = 1; i < n; ++i)d[i] = s[i + 1] - s[i];
    sort (d + 1, d + n);
    for (rg int i = 1; i < n; ++i)sum[i] = sum[i - 1] + d[i];
    rg int q = fast_IO::read();
    while (q--) {
        rg ll l = fast_IO::read(), r = fast_IO::read();
        rg ll cha = r - l;
        rg int x = lower_bound(d + 1, d + n, cha + 1) - d;
        rg ll ans = sum[x - 1];
        fast_IO::write(ans + (n - x + 1) * (cha + 1)); putchar(' ');
    }
    return 0;
}
```
**核心实现思想**：对品格音调数组排序并去重，计算相邻元素差值，对差值排序并求前缀和。对于每个询问，将区间平移，通过二分查找确定填补空隙的位置，计算不同音调的数量。

【关键思路或技巧】
- 利用区间平移答案不变的性质，简化问题。
- 通过排序、前缀和与二分查找优化计算过程。
- 反悔贪心和权值线段树等特殊思路可解决问题。

【拓展思路】
同类型题可能涉及矩阵元素的统计、区间查询等问题，可采用类似的排序、前缀和、二分查找等方法解决。类似算法套路包括离线处理询问、利用数据结构维护信息等。

【推荐题目】
1. P1102 A-B 数对：https://www.luogu.com.cn/problem/P1102
2. P2249 【深基13.例1】查找：https://www.luogu.com.cn/problem/P2249
3. P1908 逆序对：https://www.luogu.com.cn/problem/P1908

【个人心得】
New_hope：“蒟蒻的第一篇题解，有不对处请指出！” 体现了作者的谦逊和对自己题解的谨慎态度，希望得到他人的指正和建议。 

---
处理用时：78.19秒