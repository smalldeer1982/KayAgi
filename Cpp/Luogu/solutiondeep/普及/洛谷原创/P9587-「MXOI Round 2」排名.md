# 题目信息

# 「MXOI Round 2」排名

## 题目描述

小 C 有一个长度为 $n$ 的数组 $a$。

小 C 定义，$f(i)$ 为 $a_i$ 的前排名，其中 $f(i)$ 等于数组 $a$ 中大于 $a_i$ 的元素个数加 $1$。

小 C 还定义，$g(i)$ 为 $a_i$ 的后排名，其中 $g(i)$ 等于数组 $a$ 中大于等于 $a_i$ 的元素个数。

每次操作，小 C 需要选择一个不大于 $n$ 的正整数 $t$，并将 $a_t$ 的值增加 $1$。

小 C 想知道，对于每一个 $1 \le i \le n$，想要使 $f(i) \le k \le g(i)$，最少需要进行多少次操作？

可以证明一定存在一种操作方案使得 $f(i) \le k \le g(i)$。

## 说明/提示

#### 【样例解释 #1】

当 $i=1$ 时，小 C 可以选择 $t=1$ 并进行 $3$ 次操作。此时 $f(i)=2$，$g(i)=4$，满足 $f(i) \le k \le g(i)$。可以证明此时小 C 至少需要进行 $3$ 次操作。

当 $i=4$ 时，小 C 可以选择 $t=3$ 进行 $1$ 次操作，再选择 $t=6$ 进行 $1$ 次操作。此时 $f(i)=1$，$g(i)=3$，满足 $f(i) \le k \le g(i)$。可以证明此时小 C 至少需要进行 $2$ 次操作。

#### 【样例 #2】

见附加文件中的 `rank/rank2.in` 与 `rank/rank2.ans`。

该样例满足测试点 $7$ 的限制。

#### 【样例 #3】

见附加文件中的 `rank/rank3.in` 与 `rank/rank3.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le k \le n \le 5 \times 10^5$，$1 \le a_i \le 10^9$。

|测试点编号|$n \le$|$a_i \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim6$|$2000$|$10^9$|A|
|$7\sim10$|$2000$|$10^9$|无|
|$11\sim14$|$5\times10^5$|$10^9$|B|
|$15\sim20$|$5\times10^5$|$10^9$|无|

特殊性质 A：保证对于所有的 $1 \le i \lt n$，都有 $a_i \ge a_{i+1}$。

特殊性质 B：保证 $k=1$。

## 样例 #1

### 输入

```
0 6 3
1 1 4 5 1 4```

### 输出

```
3
3
0
2
3
0```

# AI分析结果

### 综合分析与结论
这些题解的核心思路大多是先对数组进行排序，然后根据 \(a_i\) 与 \(a_k\) 的大小关系分情况讨论，通过贪心策略确定最小操作次数。部分题解利用前缀和优化计算，以降低时间复杂度。

1. **思路方面**：多数题解先排序，再依据 \(a_i\) 和 \(a_k\) 的大小比较分情况讨论。如 \(a_i < a_k\) 时，使 \(a_i\) 增大到 \(a_k\)；\(a_i > a_k\) 时，贪心地选择后面的数变为 \(a_i\) 等。
2. **算法要点**：排序操作常见，部分分情况计算操作次数，部分利用前缀和优化求和计算，以将时间复杂度从 \(O(n^2)\) 优化到 \(O(n \log n)\)。
3. **解决难点**：难点在于理解 \(f(i)\) 和 \(g(i)\) 的定义，并据此分析不同情况下的最优操作策略，以及如何优化计算过程。

### 所选的题解
1. **作者：卷王 (赞：24) - 5星**
    - **关键亮点**：先给出20分部分分做法，帮助理解题意，再推出100分做法，思路清晰。分情况讨论全面且合理，利用前缀和优化，代码简洁明了。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    return x * f;
}

int _,n,k,maxx=0;
struct node {
    int x, num;
} a[500007];
ll sum[500007], ans[500007];
inline bool cmp(node i, node j) { return i.x > j.x; }
int main(){
    _ = read(), n = read(), k = read();
    for(int i = 1; i <= n; i++) a[i].x = read(), a[i].num = i;
    sort(a + 1, a + n + 1, cmp);
    for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].x;
    for(int i = 1; i <= n; i++) {
        if(a[i].x == a[k].x) continue;
        if(a[i].x < a[k].x) ans[a[i].num] = a[k].x - a[i].x;
        else ans[a[i].num] = (k - i) * 1ll * a[i].x - (sum[k] - sum[i]);
    }
    for(int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
```
    - **核心实现思想**：先读入数据，对结构体数组按值从大到小排序，计算前缀和。遍历数组，根据 \(a_i\) 与 \(a_k\) 的大小关系计算每个位置的答案。
2. **作者：Coffee_zzz (赞：12) - 4星**
    - **关键亮点**：对不同部分分的做法逐步分析，从简单情况入手，引导读者理解。不仅给出贪心思路，还对每种情况进行证明，逻辑严谨。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
struct Nod{
    int a,id;
}nod[N];
ll ans[N],f[N];
bool cmp(Nod x,Nod y){
    return x.a<y.a;
}
int main(){
    ios::sync_with_stdio(0);
    int c,n,k;
    cin>>c>>n>>k;
    for(int i=1;i<=n;i++) cin>>nod[i].a,nod[i].id=i;
    sort(nod+1,nod+n+1,cmp);
    reverse(nod+1,nod+n+1);
    for(int i=k;i<=n;i++) ans[nod[i].id]=nod[k].a-nod[i].a;
    for(int i=k - 1;i>=1;i--) f[i]=f[i + 1]+1ll*(k - i)*(nod[i].a-nod[i + 1].a),ans[nod[i].id]=f[i];
    for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}
```
    - **核心实现思想**：读入数据后，将结构体数组按值从小到大排序再反转成从大到小。对 \(i \geq k\) 的情况直接计算答案，对 \(i < k\) 的情况通过递推计算答案。
3. **作者：XiaoQuQu (赞：7) - 4星**
    - **关键亮点**：对排序后 \(f,g\) 的意义分析清晰，通过对 \(i\) 与 \(k\) 的大小关系分情况讨论得出结论，并且对复杂式子利用前缀和优化的思路明确。
    - **核心代码**：
```cpp
const int MAXN = 5e5 + 5;
int c, n, k, ans[MAXN], s[MAXN];
struct _node {
    int v, i;
    bool operator < (const _node b) const {
        return v > b.v;
    }
} a[MAXN];

void work() {
    cin >> c >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i].v, a[i].i = i;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i].v;
    for (int i = 1; i < k; ++i) ans[a[i].i] = (k - i) * a[i].v - (s[k] - s[i]);
    for (int i = k; i <= n; ++i) ans[a[i].i] = a[k].v - a[i].v;
    for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
}
```
    - **核心实现思想**：读入数据，对结构体数组按值从大到小排序，计算前缀和。根据 \(i\) 与 \(k\) 的大小关系分情况计算每个位置的答案。

### 最优的关键思路或技巧
1. **排序**：通过排序使数组有序，方便分析 \(f(i)\) 和 \(g(i)\) 的性质以及分情况讨论。
2. **分情况讨论**：依据 \(a_i\) 与 \(a_k\) 或者 \(i\) 与 \(k\) 的大小关系，分情况确定最优操作策略，如 \(a_i < a_k\) 时增大 \(a_i\) 到 \(a_k\)，\(a_i > a_k\) 时选择后面数变为 \(a_i\)。
3. **前缀和优化**：对于 \(\sum\limits_{p=i + 1}^k a_p - (k - i)\times a_i\) 这类求和式子，利用前缀和将时间复杂度从 \(O(n^2)\) 优化到 \(O(n \log n)\)。

### 可拓展之处
同类型题或类似算法套路：此类题目通常围绕数组元素的排名、相对大小关系展开，通过排序和分情况讨论确定最优操作。类似套路可用于解决一些与数组元素调整、满足特定顺序或数量关系的问题。

### 推荐题目
1. **P1993 小 K 的农场**：涉及到对不等式关系的分析和处理，与本题分情况讨论类似，同时需要运用差分约束系统等知识。
2. **P2824 [HEOI2016/TJOI2016]排序**：通过对排序操作的理解和分析，解决与序列状态相关的问题，和本题对数组操作分析有相似之处。
3. **P3243 [HNOI2015]菜肴制作**：同样是对序列元素关系进行分析，利用拓扑排序解决满足特定顺序要求的问题，与本题分析元素间关系思路类似。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：44.74秒