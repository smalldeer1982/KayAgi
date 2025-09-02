# 题目信息

# Knight Tournament

## 题目描述

（题目大意）：有n个骑士，他们每个人都被从1-n进行编号，他们现在需要进行一次比赛，且总共会进行m场比赛。每场比赛会在编号在Li-Ri这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为Xi，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 样例 #1

### 输入

```
4 3
1 2 1
1 3 3
1 4 4
```

### 输出

```
3 1 4 0 ```

## 样例 #2

### 输入

```
8 4
3 5 4
3 7 6
2 8 8
1 8 1
```

### 输出

```
0 8 4 6 4 8 6 1 ```

# AI分析结果

### 题目内容
# 骑士锦标赛

## 题目描述
（题目大意）：有n个骑士，他们每个人都被从1 - n进行编号，他们现在需要进行一次比赛，且总共会进行m场比赛。每场比赛会在编号在Li - Ri这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为Xi，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 样例 #1
### 输入
```
4 3
1 2 1
1 3 3
1 4 4
```
### 输出
```
3 1 4 0
```

## 样例 #2
### 输入
```
8 4
3 5 4
3 7 6
2 8 8
1 8 1
```
### 输出
```
0 8 4 6 4 8 6 1
```

### 综合分析与结论
这些题解主要围绕两种思路展开：
1. **并查集思路**：利用并查集维护每个骑士之后第一个未被覆盖的节点。初始化时每个骑士的父亲为自身，遍历比赛区间时，跳过已被覆盖的骑士，若当前骑士不是胜利者，则记录击败他的骑士，并更新其父亲节点。这种方法避免了重复访问已出局的骑士，优化了时间复杂度。
2. **线段树思路**：由于正向处理难以确定骑士最早被覆盖的情况，所以将询问倒序处理，这样每个骑士被覆盖的值就是最早将其击败的骑士编号。使用线段树进行区间覆盖操作，时间复杂度为$O((m + n)\log n)$ 。

难点在于如何高效处理骑士被击败后出局，避免重复计算。并查集通过跳过已访问节点解决，线段树则通过倒序处理和区间覆盖来应对。

### 所选的题解
- **作者：Yukinoshita_Yukino (5星)**
  - **关键亮点**：采用并查集简洁地解决问题，代码实现清晰，还提到解题技巧在其他题目中的应用。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
int n, m;
int f[maxn];
int find(int x) {
    return x == f[x]? x : f[x] = find(f[x]);
}
int ans[maxn];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n + 1; i++) f[i] = i;
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        for (int i = find(l); i <= r; i = find(i + 1)) {
            if (i!= x) {
                ans[i] = x;
                f[i] = i + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}
```
  - **核心思想**：利用并查集的`find`函数快速找到未被覆盖的节点，遍历比赛区间，记录每个骑士的击败者并更新并查集。

- **作者：Elma_ (5星)**
  - **关键亮点**：巧妙地将询问倒序处理，转化为线段树区间覆盖问题，代码规范，注释详细。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include <map>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

inline int read() {
    int x = 0, w = 1; char ch = getchar();
    while (ch > '9' || ch < '0') { if (ch == '-')w = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;

inline int min(int x, int y) { return x < y? x : y; }
inline int max(int x, int y) { return x > y? x : y; }

struct query {
    int l, r, x;
}q[maxn];
int n, m; 

#define ls x << 1
#define rs x << 1 | 1
struct SGT {
    int ans[maxn], tag[maxn << 2];
    inline void pushdown(int x) {
        if (tag[x]) {
            tag[ls] = tag[x];
            tag[rs] = tag[x];
            tag[x] = 0;
        }
    }
    inline void modify(int x, int l, int r, int L, int R, int k) {
        if (l >= L && r <= R) {
            tag[x] = k; return;
        }
        int mid = (l + r) >> 1;
        pushdown(x);
        if (L <= mid) modify(ls, l, mid, L, R, k);
        if (R > mid) modify(rs, mid + 1, r, L, R, k);
    }
    inline void getans(int x, int l, int r) {
        if (l == r) {
            ans[l] = tag[x]; return;
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        getans(ls, l, mid);
        getans(rs, mid + 1, r);
    }
} tree; 
#undef ls
#undef rs

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].x = read();
    for (int i = m; i >= 1; i--) {
        if (q[i].l < q[i].x) tree.modify(1, 1, n, q[i].l, q[i].x - 1, q[i].x);
        if (q[i].r > q[i].x) tree.modify(1, 1, n, q[i].x + 1, q[i].r, q[i].x);
    }
    tree.getans(1, 1, n);
    for (int i = 1; i <= n; i++) printf("%lld%c", tree.ans[i], " \n"[i == n]);
    return 0;
}
```
  - **核心思想**：倒序处理比赛，通过线段树的`modify`函数进行区间覆盖，最后通过`getans`函数获取每个骑士的击败者。

- **作者：Nukumizu_Kaju (4星)**
  - **关键亮点**：同样采用并查集，对思路解释清晰，还指出与类似题目的区别。
  - **个人心得**：无
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, p, q;
int father[1000005];
int sl[1000005];
int find(int x) {
    if (father[x] == x) {
        return x;
    }
    return father[x] = find(father[x]);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + 2; i++) {
        father[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        int lt;
        int rt;
        int color;
        scanf("%d%d%d", &lt, &rt, &color);
        if (lt > rt) {
            swap(lt, rt);
        }
        for (int j = lt; j <= rt;) {
            if (!sl[j]) {
                if (color == j) {
                    j++;
                    continue;
                }
                father[j] = j + 1;
                sl[j] = color;
            }
            j = find(j);
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", sl[i]);
    }
    return 0;
}
```
  - **核心思想**：与Yukinoshita_Yukino的思路类似，利用并查集遍历比赛区间，记录击败者并更新并查集，同时特判骑士不能被自己击败的情况。

### 最优关键思路或技巧
1. **并查集优化遍历**：通过并查集维护未被覆盖的节点，跳过已出局骑士，减少不必要的遍历，优化时间复杂度。
2. **倒序处理**：将询问倒序处理，结合线段树区间覆盖，巧妙解决确定最早覆盖骑士的问题。

### 可拓展之处
此类题目属于区间操作类型，类似的算法套路还可应用于区间查询、区间更新等问题。例如，在处理一些需要维护区间状态且有先后顺序影响的题目时，倒序处理和并查集优化的思路可能会有帮助。

### 相似知识点洛谷题目
1. **P4145 上帝造题的七分钟2 / 花神游历各国**：涉及区间操作和并查集的应用。
2. **P3372 【模板】线段树 1**：基础的线段树区间修改、单点查询题目，可巩固线段树知识。
3. **P1828 [USACO3.4] 香甜的黄油 Sweet Butter**：可通过并查集或类似的优化思路来解决图上的路径问题。 

---
处理用时：43.27秒