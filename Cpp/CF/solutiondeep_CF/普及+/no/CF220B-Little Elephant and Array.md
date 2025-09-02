# 题目信息

# Little Elephant and Array

## 题目描述

小象喜欢和数组玩。现在有一个数组  $a$，含有  $n$ 个正整数，记第  $i$ 个数为  $a_i$。

现在有  $m$ 个询问，每个询问包含两个正整数  $l_j$ 和  $r_j \;(1\leqslant l_j\leqslant r_j\leqslant n)$，小象想知道在  $A_{l_j}$ 到  $A_{r_j}$ 之中有多少个数  $x$，其出现次数也为  $x$。

## 样例 #1

### 输入

```
7 2
3 1 2 2 3 3 7
1 7
3 4
```

### 输出

```
3
1
```

# AI分析结果

### 题目内容
#### Little Elephant and Array
1. **题目描述**：小象喜欢和数组玩。现在有一个数组\(a\)，含有\(n\)个正整数，记第\(i\)个数为\(a_i\)。现在有\(m\)个询问，每个询问包含两个正整数\(l_j\)和\(r_j\ (1\leqslant l_j\leqslant r_j\leqslant n)\)，小象想知道在\(A_{l_j}\)到\(A_{r_j}\)之中有多少个数\(x\)，其出现次数也为\(x\)。
2. **样例 #1**
    - **输入**：
```
7 2
3 1 2 2 3 3 7
1 7
3 4
```
    - **输出**：
```
3
1
```
### 算法分类
无算法分类
### 综合分析与结论
这些题解主要围绕离线处理和莫队算法展开，部分题解使用线段树、树状数组等数据结构优化。各题解思路及特点如下：
1. **莫队算法类**：多数题解采用莫队算法，先将询问离线，按左端点所在块号排序，同块内按右端点排序。移动左右指针时，通过增减元素判断其是否符合出现次数等于自身值的条件，更新答案。如Warriors_Cat、My_666等题解。此方法思路直观，但时间复杂度较高，为\(O(m\log m + n\sqrt{n})\)。
2. **特殊性质利用类**：Kewth和MuYC的题解利用了一个数对询问产生贡献的必要条件，即其出现次数至少为自身值，这样的数不超过\(O(\sqrt{n})\)个。通过记录这些数出现次数的前缀和，暴力枚举并查询前缀和来统计答案，时间复杂度为\(O((n + q)\sqrt{n})\)，代码相对简洁。
3. **线段树/树状数组优化类**：marTixx和Godのfather的题解借鉴类似题目思路，将询问离线按左端点排序，用线段树或树状数组维护区间贡献。考虑区间内数\(x\)，根据其位置及出现次数的关系，通过数据结构更新和查询贡献值，时间复杂度为\(O(n\log n)\)。

总体而言，利用特殊性质和线段树/树状数组优化的方法在时间复杂度上更优，而莫队算法相对容易理解和实现。

### 所选的题解
1. **作者：Kewth (赞：30)  星级：5星**
    - **关键亮点**：巧妙利用数对询问产生贡献的必要条件，缩小需要考虑的数的范围，通过前缀和快速查询，代码简洁，时间复杂度较优。
    - **重点代码**：
```cpp
#include <cstdio>

struct { inline operator int () { int x; return scanf("%d", &x), x; } } read;

const int maxn = 100005, maxb = 500;
int a[maxn], tot[maxn];
int t[maxb][maxn], val[maxb];

int main () {
    int n = read, q = read;
    for (int i = 1; i <= n; i ++)
        if ((a[i] = read) <= n)
            ++ tot[a[i]];
    int p = 0;
    for (int x = 1; x <= n; x ++)
        if (tot[x] >= x) {
            val[++ p] = x;
            for (int i = 1; i <= n; i ++)
                t[p][i] = t[p][i - 1] + (a[i] == x);
        }
    while (q --) {
        int l = read, r = read, ans = 0;
        for (int i = 1; i <= p; i ++)
            if (t[i][r] - t[i][l - 1] == val[i])
                ++ ans;
        printf("%d\n", ans);
    }
}
```
    - **核心实现思想**：先统计每个数的出现次数，筛选出出现次数大于等于自身值的数，记录其前缀和。对于每个询问，枚举这些数，通过前缀和判断该数在区间内的出现次数是否等于自身值，统计符合条件的数的个数。
2. **作者：marTixx (赞：7)  星级：4星**
    - **关键亮点**：借鉴类似题目思路，采用离线+线段树的方法，通过独特的贡献维护方式，时间复杂度为\(O(n\log n)\)，效率较高。
    - **重点代码**：
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5 + 30;

std::vector < int > v[N];


int n, m;
int a[N], ans[N], pos[N], s[N], b[N];

struct NODE
{
    int l, r, id;
}q[N];
struct SEGMENTTREE
{
    int l, r, s;
}t[N << 2];

int read()
{
    int s = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
    return s;
}

int cmp(NODE x, NODE y)
{
    return x.r < y.r;
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (t[p].l == t[p].r) return ;
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void change(int p, int pos, int val)
{
    if (t[p].l == t[p].r) {t[p].s = val; return ; }
    int mid = t[p].l + t[p].r >> 1;
    if (pos <= mid) change(p << 1, pos, val);
    else change(p << 1 | 1, pos, val);
    t[p].s = t[p << 1].s + t[p << 1 | 1].s;
}

int ask(int p, int l, int r)
{
    if (t[p].l >= l && t[p].r <= r) return t[p].s;
    int mid = t[p].l + t[p].r >> 1, tot = 0;
    if (l <= mid) tot += ask(p << 1, l, r);
    if (mid < r) tot += ask(p << 1 | 1, l, r);
    return tot;
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++ i) s[i] = read(), b[i] = s[i];
    std::sort(s + 1, s + n + 1); int len = std::unique(s + 1, s + n + 1) - s - 1;
    for (int i = 1; i <= n; ++ i) a[i] = std::lower_bound(s + 1, s + len + 1, b[i]) - s;
    for (int i = 1; i <= n; ++ i) v[a[i]].push_back(i), pos[i] = v[a[i]].size() - 1;
    for (int i = 1; i <= m; ++ i) q[i].l = read(), q[i].r = read(), q[i].id = i;
    std::sort(q + 1, q + m + 1, cmp); build(1, 1, n);
    for (int i = 1; i <= m; ++ i)
    {
        int last = q[i - 1].r + 1;
        for (int j = last; j <= q[i].r; ++ j)
        {
            if (pos[j] - b[j] + 1 >= 0)
            {
                if (pos[j] - b[j] >= 0) change(1, v[a[j]][pos[j] - b[j]], -1);
                if (pos[j] - b[j] - 1 >= 0) change(1, v[a[j]][pos[j] - b[j] - 1], 0);
                change(1, v[a[j]][pos[j] - b[j] + 1], 1);
            }
        }
        ans[q[i].id] = ask(1, q[i].l, q[i].r);
    }
    for (int i = 1; i <= m; ++ i) printf ("%d\n", ans[i]);
    return 0;
}
```
    - **核心实现思想**：先离散化处理数据，离线询问并按右端点排序。通过vector记录每个数的位置，利用线段树维护区间贡献。遍历每个询问区间，根据数的位置关系更新线段树的贡献值，最后查询区间贡献得到答案。
3. **作者：Godのfather (赞：2)  星级：4星**
    - **关键亮点**：提供两种思路，莫队算法和基于扫描线思想结合树状数组的优化算法，详细阐述思路及复杂度分析，优化后时间复杂度为\(O(n\log n)\)。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int w = 0, f = 1; char ch = getchar();
    while(ch < '0' or ch > '9') {if(ch == '-') f = -f; ch = getchar();}
    while(ch >= '0' and ch <= '9') w = w*10 + ch - '0', ch = getchar();
    return w*f;
}
const int maxn = 1e6 + 5;
struct Question{
    int l, r, id;
}q[maxn];
int N, a[maxn], c[maxn], Q;
bool cmp(Question x, Question y){
    return x.l < y.l;
}
void add(int x, int y){
    for(; x<=N+1; x += x&-x) c[x] += y;
}
int ask(int x){
    int ans = 0;
    for(; x; x -= x&-x) ans += c[x];
}
int ans[maxn], pointer[maxn], sum[maxn];
vector<int> head[maxn];
int main(){
    N = read(), Q = read();
    for(int i=1; i<=N; i++){
        a[i] = read();
        if(a[i] > N) continue;
        sum[a[i]] ++;
        if(sum[a[i]] == a[i]) add(i, 1), head[a[i]].push_back(i);
        else if(sum[a[i]] == a[i] + 1) add(i, -1), head[a[i]].push_back(i);
        else if(sum[a[i]] > a[i]) head[a[i]].push_back(i);
    }

    for(int i=1; i<=Q; i++){
        int l = read(), r = read(), id = i;
        q[i] = (Question){l, r, id};
    }
    sort(q+1, q+Q+1, cmp);
    int j = 1, tmp = 0;
    for(int i=1; i<=Q; i++){
        for(; j<q[i].l; j++){
            if(a[j] > N) continue;
            if(pointer[a[j]] < head[a[j]].size()){
                add(head[a[j]][pointer[a[j]] ++], -1);
                if(pointer[a[j]] < head[a[j]].size()) add(head[a[j]][pointer[a[j]]], 1);
            }
            if(pointer[a[j]] < head[a[j]].size()){
                add(head[a[j]][pointer[a[j]]], 1);
                if(pointer[a[j]]+1 < head[a[j]].size()) add(head[a[j]][pointer[a[j]]+1], -1);
            }
        }
        ans[q[i].id] = ask(q[i].r);
    }
    for(int i=1; i<=Q; i++) printf("%d\n", ans[i]);
    return 0;
}
```
    - **核心实现思想**：将询问离线按左端点排序，用树状数组维护区间贡献。遍历数组，根据数的出现次数变化，通过树状数组更新对应位置的贡献值。对于每个询问，移动左端点时更新树状数组，最后查询右端点处的贡献值得到答案。

### 最优关键思路或技巧
1. **利用特殊性质**：注意到一个数对询问产生贡献的必要条件是其出现次数至少为自身值，这样的数较少，可缩小处理范围，降低时间复杂度。
2. **数据结构优化**：使用线段树或树状数组维护区间贡献，通过巧妙的区间更新和查询操作，高效统计符合条件的数的个数。

### 拓展
1. **同类型题或类似算法套路**：此类区间统计问题，若数据规模较大且无修改操作，可考虑离线处理结合莫队算法。若对时间复杂度要求更高，可尝试利用数据结构优化，如线段树、树状数组等，通过维护区间信息来快速查询答案。
2. **推荐题目**
    - **P1972 HH的项链**：同样是区间统计问题，可帮助理解区间问题的处理思路。
    - **P3901 数列找不同**：涉及区间查询和统计，锻炼对区间问题的解决能力。
    - **P4137 Rmq Problem / mex**：通过区间查询和特殊值计算，进一步掌握区间相关算法。

### 个人心得摘录与总结
1. **Godのfather**：考场思考算法过程中，对莫队算法的时间复杂度有清晰认识，发现数据范围可能导致莫队暴毙，进而思考优化算法。总结出面对区间问题，可尝试离线处理结合数据结构优化的思路。 

---
处理用时：126.46秒