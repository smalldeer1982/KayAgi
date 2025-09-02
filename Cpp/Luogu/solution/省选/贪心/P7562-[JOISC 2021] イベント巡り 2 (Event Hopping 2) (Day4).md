# [JOISC 2021] イベント巡り 2 (Event Hopping 2) (Day4)

## 题目背景

**因洛谷限制，本题不予评测每个 Subtask 的第 1 ~ 20 个测试点，您可以 [点此](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/event2-data.zip) 下载所有数据自行评测或在 [这里](https://www.luogu.com.cn/problem/U159034) 测试，若您希望写本题题解，建议您在通过 [本题](https://www.luogu.com.cn/problem/P7562) 与 [每个 Subtask 前 20 个测试点](https://www.luogu.com.cn/problem/U159034) 之后再写题解。**


## 题目描述

IOI Park 将有 $n$ 场活动。

这些活动的编号从 $1$ 到 $n$。 活动 $i$ 从时间 $L_i+10^{-1}$ 到时间 $R_i-10^{-1}$ 举行。数据保证 $L_i$ 和 $R_i$ 是整数。

JOI 君决定参加其中的 $k$ 个活动。但是，JOI 君不能在中间加入或离开每个活动。**在两个活动场所间移动的时间忽略不计**。

JOI 君希望参加编号较小的活动。严格来说，JOI 君参加的 $k$ 个活动的编号依次为 $a_1,\cdots,a_k$，其中 $1 \le a_1 < \cdots < a_k \le n$。如果序列 $(a_1, \cdots, a_k)$ 的编号小于 $(b_1, \cdots, b_k)$，当且仅当存在 $j\ (1 \le j \le k)$ 满足在区间 $[1,j-1]$ 里的所有 $l$ 都有 $a_l=b_l$ 和 $a_j<b_j$。



给出每个活动的信息和 JOI 君参加的活动个数 $k$，判断 JOI 君是否可以参加 $k$ 个活动，如果可以，输出所有的 $k$ 个活动的编号。



## 说明/提示

#### 样例 #1 解释

有 $2$ 种方式可以参加正好 $4$ 个活动。

- 参加 $1, 3, 4, 5$；
- 参加 $2, 3, 4, 5$。

数列 $(1,3,4,5)$ 比数列 $(2, 3, 4, 5)$ 字典序小，所以输出 $1, 3, 4, 5$。

#### 样例 #2 解释

无论怎么选择都不可能正好参加 $3$ 个活动，所以输出 $\tt -1$。

#### 样例 #3 解释

本样例满足所有 Subtask 的条件。

#### 数据规模与约定

**因洛谷限制，本题不予评测每个 Subtask 的第 $1\sim 20$ 个测试点。**

**本题采用 Subtask 计分法。**

| Subtask | 分值占比百分率 | $n$ | $L_i$ |
| :----: | :----: | :----: | :----:|
| $1$ | $7\%$ | / | $L_i \le L_{i+1}\ (1 \le i \le n − 1)$ |
| $2$ | $1\%$ | $\le20$ | / |
| $3$ | $31\%$ | $\le 3 \times 10^3$ |/ |
| $4$ | $61\%$ | / | / |

**注：斜线表示无特殊限制。**

对于 $100\%$ 的数据：
- $1\le n\le 10^5$；
- $1 \le k \le n$；
- $1\le L_i < R_i \le 10^9 (1\le i \le n)$。


#### 说明

本题译自 [第２０回日本情報オリンピック 2020/2021春季トレーニング合宿 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [競技 4 -](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/2021-sp-d4-notice.pdf) [T1 日文题面](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day4/event2.pdf)。


## 样例 #1

### 输入

```
5 4
1 3
2 5
8 9
6 8
10 15
```

### 输出

```
1
3
4
5
```

## 样例 #2

### 输入

```
4 3
1 4
3 5
4 9
7 10
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 6
77412002 93858605
244306432 318243514
280338037 358494212
439397354 492065507
485779890 529132783
571714810 632053254
659767854 709114867
718405631 733610573
786950301 815106357
878719468 899999649
```

### 输出

```
1
2
4
6
7
8
```

## 样例 #4

### 输入

```
20 16
250732298 258217736
26470443 34965880
252620676 260043105
692063405 697656580
497457675 504191511
391372149 397942668
858168758 867389085
235756850 241022021
585764751 593366541
207824318 217052204
661682908 671226688
886273261 892279963
770109416 778960597
264372562 270395107
176883483 186662376
509929119 519063796
109491630 118520141
162731982 168101507
662727316 668317158
757072772 765493222
```

### 输出

```
1
2
4
5
6
7
8
9
10
11
12
13
14
15
16
17
```

# 题解

## 作者：GaoKui (赞：33)

思维量比较大的题目，不过全部理解以后并不是很绕。这题需要理解 ```set``` 内部判断元素相等的机制才能做得出来，在做这题这之前对 ```set``` 内部的机制一直不太清楚。```set``` 的运用比较类似于珂朵莉树，用 ```set``` 中的元素表示区间，从而进行维护。一开始只叙述大致思路，```set``` 运用的具体细节与原理，在之后再写。

首先，可以很明显地发现这一题具有贪心性质。由于要保证答案的字典序最小，编号越小的活动被选择的优先级也就越高。用 $i$ 从 $1$ 至 $n$ 遍历所有活动的编号，如果选择活动 $i$ 后，在剩下的时间段内依然可以可以选出足够数量的活动，那么活动 $i$ 就是必须要选择的，只有这样才能得到字典序最小的答案。

但是，想要实现以上的想法要解决两个问题：
1. 怎么知道选择活动 $i$，是否会和之前已经选择的活动发生冲突？（按题目要求，就是两条线段发生了相交，端点相交不算）
1. 怎么知道选择活动 $i$ 前后，剩余的空余时间里还能选择多少个活动？


------------
对于问题 $1$：

本题可以通过用 ```set``` 来维护 空闲时间 来解决问题 $1$。这和珂朵莉树是类似的，```set``` 中每一个的元素表示的是一段区间，这段区间是空闲的，能够在其中参加若干个活动。

一个活动可以选择的条件是：它的起始时间和结束时间必须位于同一段空闲时间当中（对应题目中说的，不能在一个活动进行的中间加入或离开这个活动）。那么，判断活动 $i$ 是否可选，就变为了判断是否能在 ```set``` 中找到一个元素，使得这个元素代表的区间可以完全包含活动 $i$。如果可以完全包含，就必须要选择活动 $i$，以此保证答案字典序最小。选择以后，活动 $i$ 将找到的这个完全包含的元素分割为两个新的元素，即：

假设，找到的元素为 $[l,r]$，活动 $i$ 为 $[x,y]$。那么，活动 $i$ 会将找到的元素分割为 $[l,x]$，$[y,r]$ 两个部分。因此，我们只需要在 ```set``` 中删除 $[l,r]$ 所代表的元素，重新插入 $[l,x]$，$[y,r]$ 两个元素即可。

但是，怎么在 ```set``` 中找到一个可以完全包含活动 $i$ 的元素呢？简单地说，就是对于表示区间的结构体，重载小于号时使用一些特殊的方法，
即：

```cpp
bool operator<(const Seg &rhs) const
{
	return r < rhs.l;
}
```

这样重载以后，就能直接调用 ```set::find()``` 函数进行查找。

比如，活动 $i$ 为 $[x,y]$，就直接调用 ```set::find({x, y})```。此时，该函数会返回一个与 $[x,y]$ 这个区间相交的区间，而如果没有元素与 $[x,y]$ 相交，则会返回 ```set::end()```。此时特判一下，如果这个与 $[x,y]$ 相交的元素能够完全包含活动 $i$，则找到了符合规定的元素，在答案里，就可以选择活动 $i$，然后在 ```set``` 里进行上面说过的分割操作，否则，不能找到完全包含活动 $i$ 的元素，活动 $i$ 不能选择。

之所以能够按以上方法寻找相交区间，是因为按照以上方法重载小于号后，```set``` 会将相交的两段区间认为是相等的元素。这样做还有另一个好处，可以保证算法正确性。即，任何两个相交的元素都会被 ```set``` 认为相等，也就是会被自动去重。

这样一来，虽然可能有多个元素与活动 $i$ 相交，但是，此时一定不会存在任意一个元素能完全包含活动 $i$。因此，这种情况下，找到任意一个与活动 $i$ 相交的元素，特判的结果一定都是不合法，不会影响正确性。反之，如果存在一个元素能完全包含活动 $i$，则它一定是唯一一个与活动 $i$ 相交的元素，一定可以通过特判。

但是为什么这样重载小于号后，```set``` 就会认为两个相交的区间是相等的？这就涉及到了 ```set``` 的内部机制，之后再做说明。


------------
对于问题 $2$：

如果有一个 $query$ 函数，可以返回在 $[l,r]$ 这段区间里可以选择多少个活动，那么就可以通过在问题 $1$ 中实现的，维护空闲时间来解决这个问题。

一开始的剩余时间为 $[start, end]$，其中 $start$ 和 $end$ 是所有活动中最早的开始时间和最晚的结束时间（不过这个时间是经过了离散化的，这个后面会讲，暂时不用管）。用一个计数器 $last$ 记录当前可选的活动数量，一开始这个变量的值为：

```cpp
query(start, end);
```

之后，用 $i$ 循环 $1$ 至 $n$ 的所有活动编号

假设活动 $i$ 代表的区间为 $[x,y]$，在问题 $1$ 中，查找到的完全包含活动 $i$ 的元素为 $[l,r]$。那么，选择了活动 $i$ 以后，剩下的空余时间还能选择的活动数目就能这么计算：

```cpp
last - query(l, r) + query(l, x) + query(y, r);
```


式子并不难理解，即原本的 $[l,r]$ 这段区间被拆成了 $[l,x]$，$[y,r]$，剩余可选的数目就要减去老区间，再加上两个新区间。由于活动不能在进行过程中加入或退出，即不可能出现跨越两段分隔开的区间的活动，按以上方法计算出来的结果一定是正确的。只要计算出的这个值，大于等于剩余需要选的活动个数，活动 $i$ 就是要选的。

现在关键的问题就是，如何实现这个 ```query``` 函数？

这是本题思维量最大的一个地方，设 $f[i][j]$ 表示从坐标为 $i$ 的点，往右挑选 $2^j$ 个活动后能够到达的最靠左的坐标为多少。由于坐标的取值范围最大到 $10^9$，直接开这样的 $f$ 矩阵是会爆空间的。因此，首先要对坐标进行离散化。这个状态表示确实不容易想到，这么做的理由在下面 ```query``` 函数的实现中可以体会到。

```query``` 函数中，利用倍增进行查询。

目的是调用 ```query(l, r)```，利用 $f$ 矩阵，返回 $[l,r]$ 这段区间里最多可以选择多少个活动。初始化 $res = 0$，$cur = l$。$res$ 是最后要返回的答案，$cur$ 是当前位置的坐标。

用 $j$ 从大到小遍历 $log_2(N)$ ~ $0$，由于 $f[cur][j]$ 就是往右选 $2^j$ 个活动能到达的最左边的坐标，一旦发现 $f[cur][j]$ 的值在 $r$ 左边，或者刚好跳到 $r$ 上，说明可以往右选 $2^j$ 个活动。此时，令 $cur = f[cur][j]$，跳到对应的坐标，$res = res + 2^j$，加上选择的活动数。最后结束循环，返回 $res$ 即可。

通过以上的过程，也能体会到为什么 $f$ 要这么定义。

之所以 $f[i][j]$ 表示的是尽量靠左的一个坐标值，就是因为在选取 $2^j$ 个活动后，还想要最大化剩余可选的活动数，就要让选择后剩余的区间也尽量地更大一些，即往右跳的距离尽量小一些。所以，$f$ 的值是向右挑选 $2^j$ 个活动后，尽量靠左的坐标值。

接下来，考虑如何求出 $f$ 矩阵。

先解决一个问题，解释一下为什么可以套用倍增的板子，即：

```cpp
f[i][j] = f[f[i][j - 1]][j - 1]
```


首先，要选 $2^j$ 个活动，同时要保证选完后的坐标最靠左，那么每一步的选择都是一定的。首先假设 $j$ 为常数，可以发现，$i$ 这个值越靠右，$f[i][j]$ 也一定越靠右。

因为，如果 $f[i+1][j]$ 反而比 $f[i][j]$ 更靠左，那 $f[i][j]$ 显然可以更新成 $f[i+1][j]$。

所以，先不考虑倍增地往右选，而是一个个地往右选，那么往右选的每一个活动，都要保证选完后坐标更靠左，最终的所在的坐标才会最靠左。也就是说，选择的方案也具有贪心性质。

那么，想要使得 $i$ 往右选 $2^j$ 个活动后，所在坐标最靠左，选择 $2^{j-1}$ 个活动的时候也要让坐标尽量靠左。想要选择 $2^{j-1}$ 个活动的时候尽量靠左，就要让选择 $2^{j-2}$ 个活动时尽量靠左。以此类推，只要求出往右选择 $1$ 个活动时最靠左的下标，之后就可以利用倍增进行递推了。

所以现在，对于 $f$ 矩阵，最关键的就是如何求出第 $0$ 列，后面的列直接用倍增板子就全求出来了，递推式如上。

怎么求出第 $0$ 列呢？首先，对于每一个坐标，如果它是活动的左端点，那就可以选择这个活动，到达这个活动的右端点处。而如果某个坐标，它并不是活动的左端点，而是在活动的中间，由于活动不能在中途加入，它就不能选择这一个活动了。而对于不在活动线段上的坐标，同样也是没法直接得到结果的。

因此，对于不是活动左端点的坐标，唯一的方法就是从它右边的某一个点递推而来。综上，求第 $0$ 列时可以分两步走：
1. 对所有为活动左端点的坐标特殊考虑，赋上初值
1. 对于剩余的所有坐标，通过递推得来

首先来一个循环，用 $i$ 遍历所有活动
为方便描述，令 $l[i]$ 表示活动 $i$ 的左端点，$r[i]$ 表示活动 $i$ 的右端点，式子就可以表示为如下形式：

```cpp
f[l[i]][0] = min(f[l[i]][0], r[i]);
```


然后再来一个循环，用 $i$ 从右到左遍历所有坐标（当然是离散化过的），按照下式进行递推：

```cpp
f[i][0] = min(f[i][0], f[i + 1][0]);
```


经历了以上两个循环，$f$ 矩阵的第 $0$ 列已经被求出来了。之后用倍增即可得出 $f$ 矩阵。得出 $f$ 矩阵，即可使用 ```query``` 函数。可以使用 ```query``` 函数，也就解决了问题 $2$。解决了问题 $2$，之前也说了如何解决问题 $1$，那么这一题也就能够解决了。


------------
最后的问题。

为什么按照上面的小于号重载方式，两段相交的区间会被 ```set``` 认为是相等，并且自动去重？

又是为什么，我们用 ```set::find()``` 查找一个区间，查询到的结果会是一个可能与查询区间不同，但一定与查询区间相交的区间？

```set``` 内部的元素比较使用的是“严格弱序”这一种关系。这种关系的推导用了一些离散数学的知识，这里仅仅只做简单的解释。

比如，< 就是一种严格弱序，而 <= 不是一种严格弱序。使用严格弱序这一关系的好处，就是仅仅只用重载 < 一个运算符，即可完成元素的比较，不需要重载 <=、==、> 等等。

所有的比较情况如下：

$a$ 小于 $b$ --> ```a < b```

$b$ 小于 $a$ --> ```b < a```

$a$ 等于 $b$ --> ```!(a < b) && !(b < a)```

关键点就在于最后的等于这个判断。


------------

第一种相交情况：相交，但不包含。

假设有两个结构体，分别表示两段区间 $a$：$[1,4]$、$b$：$[2,5]$。

按照上面的小于号重载方式手动验算，得到的结果正好就是 ```!(a < b) && !(b < a)```
因此，这种情况下，```set``` 就会认为这两个元素是相等的。


------------


第二种相交情况：相交且包含。

假设有两个结构体，分别表示两段区间 $a$：$[1,5]$、$b$：$[2,4]$。

按照上面的小于号重载方式手动验算，得到的结果正好也是 ```!(a < b) && !(b < a)```


------------

第三种情况：不相交
简单想象一下便知，此时，一定有某一个区间的右端点小于另一个区间的左端点。无论如何，这两个不相交的区间是不会被认为是相等的。


------------


综上所述，一旦两个区间产生了相交，```set``` 就会认为它们相等，从而自动去重。而一旦两个区间不相交，它们也一定就不相等。

代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

struct Seg
{
    int l, r; // 区间的左右端点

    Seg(int x = 0, int y = 0) // 构造函数，默认形参为 0
    {
        l = x;
        r = y;
    }

    bool operator<(const Seg &rhs) const // 重载小于号，用于 set 的内部排序（不重载小于号，结构体不能放入 set）
    {
        return r < rhs.l;
        // return r <= rhs.l;

        // 如果用 <=，那么两条区间的端点重合时不会被认为是相等的元素，所以直接用 < 就行
        // （不过似乎两种方法都是对的）
    }
};

int n, k;
Seg s[N];           // 存储所有的活动
vector<int> all;    // 存储所有活动端点，之后用于离散化

int f[2 * N][19];   // f[i][j] 的含义如上，第二列是对 2*N 取以 2 为底对数的大概值

set<Seg> st;        // 用 set 维护空余时间，对于这点上面已经描述过了

// 利用倍增与简单的 dp，得到 f 矩阵
void get_f(void)
{
    memset(f, 0x3f, sizeof(f)); // 把整个矩阵初始化为最大值

    for (int i = 1; i <= n; i++) // 先通过所有活动的左右端点，赋上最初的初值
    {
        f[s[i].l][0] = min(f[s[i].l][0], s[i].r);
    }

    for (int i = all.size() - 1; ~i; i--) // 从右往左遍历离散化后的坐标，递推得出完整的第 0 列
    {
        f[i][0] = min(f[i][0], f[i + 1][0]);
    }

    // 用倍增板子，得出整个 f 矩阵
    for (int p = 1; p < 19; p++) // 外层循环枚举列
    {
        for (int i = 0; i < all.size(); i++) // 内层循环枚举行
        {
            // 如果往右选 2^(p-1) 个活动后跳到的坐标，是一个合法坐标才能进行递推
            // 否则，f[f[i][p - 1]][p - 1] 里的行号就是不合法的，调用后会数组越界
            if (f[i][p - 1] < all.size())
            f[i][p] = f[f[i][p - 1]][p - 1];
        }
    }
}

// 查询空闲区间 [l,r] 中最多能够选出几个活动
int query(int l, int r)
{
    int res = 0;
    int cur = l; // 初始位置位于左端点处

    for (int p = 18; ~p; p--)
    {
        if (f[cur][p] <= r)     // 往右选 2^p 个活动后不会超过右端点，那就选
        {
            cur = f[cur][p];    // 选了 2^p 个活动，跳到对应的位置
            res += (1 << p);    // 统计刚选上的 2^p 个活动
        }
    }

    return res; // 上述循环结束后 res 就是所求答案
}

// 用 x 与 y 构造出一个左端点为 x，右端点为 y 的元素，并将其返回
Seg make(int x, int y)
{
    Seg tmp(x, y);
    return tmp;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // cout << log2(2 * N) << '\n'; // 17.6098

    cin >> n >> k;

    for (int i = 1; i <= n; i++)    // 输入所有的活动
    {
        cin >> s[i].l >> s[i].r;
        all.push_back(s[i].l);      // 把每一个出现的左右端点放到 all 里，之后用于离散化
        all.push_back(s[i].r);
    }

    sort(all.begin(), all.end());               // 离散化前排序
    auto ed = unique(all.begin(), all.end());   // 离散化前去重
    all.erase(ed, all.end());                   // 把调用 unique 后放到最后的重复元素，直接删除，这样一来 all 的大小就是最右边的坐标值

    for (int i = 1; i <= n; i++)
    {
        s[i].l = lower_bound(all.begin(), all.end(), s[i].l) - all.begin(); // 令每个活动的端点变为离散化后的值
        s[i].r = lower_bound(all.begin(), all.end(), s[i].r) - all.begin();
    }

    get_f(); // 得到 f 矩阵

    // st 内维护的是空闲时间段，一开始，整个坐标轴都是空闲时间，因此插入的元素就是代表整个坐标轴的区间
    // 即，左端点是最左边的坐标，右端点是最右边的坐标
    st.insert(make(0, all.size() - 1));

    vector<int> res;                        // res 里保存最终要输出的活动编号
    set<Seg>::iterator it;
    int last = query(0, all.size() - 1);    // 一开始，所有空余时间段内能够选择的活动数，就是整个坐标轴上能选的活动数

    for (int i = 1; i <= n && res.size() < k; i++)      // 从 1~n 遍历每一个活动，遍历完所有活动或已选活动数达到 k 个后退出循环
    {
        if ((it = st.find(s[i])) == st.end()) continue; // 没有能与当前活动相交的空闲区间，直接跳过就好

        // it 现在指向的元素，就是与活动 i 相交的某一个元素

        if (s[i].l >= it->l && s[i].r <= it->r) // 如果该元素完全包含了活动 i，则继续进行考虑，否则跳过就好
        {
            // 如果选完这个活动以后，剩下的空余时间里依然能选出足够的活动，那就选上这个活动
            if (last - query(it->l, it->r) + query(it->l, s[i].l) + query(s[i].r, it->r) >= k - res.size() - 1)
            {
                last = last - query(it->l, it->r) + query(it->l, s[i].l) + query(s[i].r, it->r);    // 剩余能选的活动数对应减少
                res.push_back(i);                                                                   // 把当前活动存入 res
                Seg t1(it->l, s[i].l), t2(s[i].r, it->r);   // 两个新的要插入的元素，即被活动 i 分割开来的两个区间
                st.erase(it);                               // 删除旧的元素
                st.insert(t1);                              // 插入两个新元素
                st.insert(t2);
            }
        }
    }

    if (res.size() == k) // 退出循环后，如果已经选出了 k 个活动
    {
        for (auto j : res) // 输出选择的活动
        {
            cout << j << '\n';
        }
    }
    else // 否则说明无法选出 k 个活动
    {
        cout << -1;
    }

    return 0;
}
```


---

## 作者：喵仔牛奶 (赞：29)

这题是萌新两天前的作业，本萌新来水一篇题解加深影响qwq

首先贪心思路应该好想吧，由于是字典序最小，所以按顺序强制参加每个活动，如果参加后还可以达到最优解，就使用。因为如果选了这个不影响数量，那么选了这个字典序肯定比不选小。如果您还是听不懂的话……建议先自学字典序。

关键是如何快速地得出参加了这个活动之后最多能参加的活动：

（下列内容将活动抽象成了线段，请读者自行思考）

首先，思考一下，发现这是个贪心题。让选取的右端点尽量小一定是最优的。那么您可以按左区间排序，每次选右端点最小的就行了。然鹅，它是 $\mathcal{O}(n)$ 的，您需要思考优化。

事实上，这种贪心策略对于不同的区间都是固定的，您可以用 ST 表（倍增）优化它。

设 $f_{i,j}$ 为第 $i$ 个点开始选 $2^j$ 条线段后最小的右端点。那么有转移方程

$$f[i][j]=\min\{f[i][j],f[f[i][j-1]][j-1]\}$$

然鹅，这个转移方程没有初值，所以需要赋一个初值。对于每条线段，它的左端点都直接可以通过它到右端点。

$$\forall_{i=1}^{n}f[L_i][0]=\min\{f[L_i][0],R_i\}$$

(下标太糊了，见谅一下哈qwq)

这样就可以通过倍增 $\mathcal{O}(\log n)$ 求出一个区间最多可以放几条线段了。

```
int query(int l, int r) {
	int res = 0;
	Down(i, 20, 0) 
            if (f[l][i] <= r + 1) 
                res += 1 << i, l = f[l][i]; 
	return res;
}
```

但是，就这样，我们还是无法判断一条线段的区间有没有被其他线段覆盖。使用线段树/树状数组区间赋值+区间修改？但是这样显然很麻烦，有没有更好的方法呢？

有。我们可以使用珂朵莉树思想，将区间转换为值，保存 $l,r$ 放进 ```set``` 里。修改时找到块删除+插入新的散块就行了。

$L_i,R_i\leq10^9$ 记得跑离散化。

细节还挺多，注意别写挂了。

```cpp
#include <bits/stdc++.h>
#define Up(i, l, r) for (int i = (l); i <= (r); i ++)
#define Down(i, l, r) for (int i = (l); i >= (r); i --)
using namespace std;
const int N = 2e6 + 5;
struct Seq { // 一条线段
	int l, r;
	bool operator < (const Seq& x) const { return r < x.l; }
	Seq(int _l, int _r) : l(_l), r(_r) {}
};
int f[N][25], L[N], R[N], t[N], cnt, n, k, sum;
set<Seq> s; // 存区间
int query(int l, int r) {
	int res = 0;
	Down(i, 20, 0) if (f[l][i] <= r + 1) res += 1 << i, l = f[l][i]; 
	return res;
} // 返回[l,r]最多能够有几条线段
int main() {
	cin >> n >> k;
	Up(i, 1, n) cin >> L[i] >> R[i], t[++ cnt] = L[i], t[++ cnt] = R[i];
	sort(t + 1, t + 1 + cnt), cnt = unique(t + 1, t + 1 + cnt) - t;
	Up(i, 1, n) L[i] = lower_bound(t + 1, t + 1 + cnt, L[i]) - t, R[i] = lower_bound(t + 1, t + 1 + cnt, R[i]) - t; // 离散化
	Up(i, 1, cnt + 5) Up(j, 0, 20) f[i][j] = cnt + 5; // 赋值成INT_MAX会RE，赋值成比cnt大的值就可以了
	Up(i, 1, n) f[L[i]][0] = min(f[L[i]][0], R[i]);
	Down(i, cnt, 1) {
		f[i][0] = min(f[i][0], f[i + 1][0]);
		Up(j, 1, 20) f[i][j] = min(f[i + 1][j], f[f[i][j - 1]][j - 1]);
	}
	s.insert(Seq(1, cnt)), sum = query(1, cnt); if (sum < k) puts("-1"), exit(0); // 最多接的线段就是query(1, cnt)
	Up(i, 1, n) {
		if (s.find(Seq(L[i], R[i] - 1)) == s.end()) continue; // 如果没有该线段
		Seq now = *s.find(Seq(L[i], R[i] - 1)); // 找到该线段
		if (L[i] >= now.l && R[i] - 1 <= now.r) { // 如果可以完美覆盖
			int ns = query(now.l, L[i] - 1) + query(R[i], now.r) - query(now.l, now.r); // 如果使用了这条线段最优解不变
			if (sum + ns >= k - 1) {
				cout << i << '\n', s.erase(now), k --, sum += ns;
				if (now.l < L[i]) s.insert(Seq(now.l, L[i] - 1));
				if (now.r >= R[i]) s.insert(Seq(R[i], now.r)); // 珂朵莉树的裂块
			}
		}
		if (!k) break; // k没了，直接结束
	}
	return 0;
}
```


---

## 作者：AquariusZhao (赞：11)

lxl 上课讲了这题，觉得选取答案的思路很妙，~~我感慨万分~~ ，于是就有了这篇题解——

sto lxl orz ！！！

#

**本题解主要详解区间选取。**

前置知识：倍增

#

### 策略

首先，本题的 $L_i$、$R_i$ 较大，离散化即可。

另外，我个人觉得把所有的 $R_i$ 减掉一之后会好写一点，转成了 $[L_i, R_i]$ 区间覆盖。~~然而我却调了半个多小时~~ 

然后问题是：若固定选择一个区间，最大化再向右选择的区间个数。

考虑贪心，每次选择没有交叉、右端点最靠左的。~~证明显然，~~ 因为如果选择右端点更靠右的区间，那么能选的区间不会变多，答案只可能更劣。

由此一来，从每个区间开始，都有**固定的方案**来最大化答案，于是就能**倍增**啦～～

### 倍增

设 $nxt[k][i]$ 表示从 $i$ 开始选 $2^k$ 个区间后最靠左的点。

$nxt$ 数组的初值参考了@[喵仔牛奶](https://www.luogu.com.cn/user/560516)的[题解](https://www.luogu.com.cn/article/fpm1wbud)（orz），可以枚举区间，用右端点更新左端点的 $nxt$：

$$
nxt[0][L_i] = \min\left\{R_i + 1\right\}
$$

（$R_i$ 要加一是因为跳完 $[L_i,R_i]$ 这个区间后，下一个要从 $R_i+1$ 开始）

转移方程也很显然：

$$
nxt[k][i] = nxt[k-1][nxt[k-1][i]]
$$

另外，由于区间之间可以有空隙，所以还要用 $nxt[k][i + 1]$ 更新 $nxt[k][i]$。

怎么样，简单吧？

然后查询 $[L_i, R_i]$ 最多能放几个区间（以下写为 $\operatorname{query}(L_i,R_i)$）时，只要把 $k$ 从大往小枚举，能跳尽量跳就行了，可以做到 $O(log n)$。

### 如何保证字典序最小？

首先，若 $\operatorname{query}(1,m)<k$（$m$ 为值域），肯定无解。

否则，维护一些“块”。初始时块为 $[1,m]$。

然后考虑这样做：从编号 $1$ 到 $n$ 枚举区间，若该区间被某一个块包含，**并且选择该区间后仍有选择 $k$ 个区间的方案**（可以用 $\operatorname{query}$ 算出，选它之后，块内最多可选区间个数的变化量来判断），那么直接选择该区间，并回收没有被区间覆盖的块。

如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w045b0f2.png)

不难看出，这样做保证了有解的前提下，字典序最小。是不是很妙？

问题来了，要怎么维护“块”呢？方法有很多，这里介绍一种用 `set` 维护的方法。

写一个结构体，里面存 $l$ 和 $r$ ，重载运算符 `<` 为 `r < t.l` 。然后可以用 `find()` 函数找到与区间有交的块，再判断是否包含区间就好了。

> 注：`find()` 找到的是 `a < k` 和 `k < a` 都不满足的元素，所以相当于找与区间有交的块。

然后就做完啦！时间复杂度 $O(nlogn)$。 

###  _Talk is cheap, show you the code._


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 2e5 + 5, LOGM = 19; // N是区间个数，M是值域
int n, K, li[N], ri[N];
int a[M], m; // 离散化数组
int nxt[LOGM][M];
struct range
{
    int l, r;
    bool operator<(const range t) const
    {
        return r < t.l;
    }
};
set<range> res; // 维护“块”
vector<int> ans; // 选择的区间

int lsh(int x) // 离散化
{
    return lower_bound(a + 1, a + m + 1, x) - a;
}

int query(int l, int r) // 查询[l,r]最多能放几个区间
{
    if (l > r) return 0;
    int res = 0;
    for (int k = LOGM - 1; k >= 0; k--)
        if (nxt[k][l] <= r + 1)
        {
            l = nxt[k][l];
            res += 1 << k;
        }
    return res;
}

int main()
{
    cin >> n >> K;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", li + i, ri + i);
        ri[i]--; // 转为[l,r]
        a[++m] = li[i]; a[++m] = ri[i];
    }

    sort(a + 1, a + m + 1);
    m = unique(a + 1, a + m + 1) - a - 1;

    for (int k = 0; k < LOGM; k++)
        for (int i = 1; i <= m + 4; i++)
            nxt[k][i] = m + 3; // 设为极大值
    for (int i = 1; i <= n; i++)
    {
        li[i] = lsh(li[i]), ri[i] = lsh(ri[i]);
        nxt[0][li[i]] = min(nxt[0][li[i]], ri[i] + 1); // 赋nxt初值，注意要+1！
    }
    for (int i = m; i >= 1; i--)
    {
        nxt[0][i] = min(nxt[0][i + 1], nxt[0][i]); // 用后一个转移
        for (int k = 1; k < LOGM; k++)
            nxt[k][i] = min(nxt[k - 1][nxt[k - 1][i]], nxt[k][i + 1]); // 用小的合并
    }

    int sum = query(1, m);
    if (sum < K) // 无解就输出-1
    {
        puts("-1");
        return 0;
    }

    res.insert({1, m}); // 初始块为[1,m]
    for (int i = 1; i <= n; i++)
    {
        if (res.find({li[i], ri[i]}) == res.end()) continue; // 若没有相交，就肯定没有覆盖
        auto it = res.find({li[i], ri[i]});
        range tmp = *it;
        if (li[i] < tmp.l || tmp.r < ri[i]) continue; // 没有完全覆盖也不能选
        int delta = query(tmp.l, li[i] - 1) + 1 + query(ri[i] + 1, tmp.r) - query(tmp.l, tmp.r);
        if (sum + delta >= K) // 若选了该区间之后仍有合法方案
        {
            sum += delta;
            ans.push_back(i);
            res.erase(it);
            if (tmp.l <= li[i] - 1) res.insert({tmp.l, li[i] - 1}); // 回收左边剩下的块
            if (ri[i] + 1 <= tmp.r) res.insert({ri[i] + 1, tmp.r}); // 回收右边剩下的块
        }
        if (ans.size() >= K) break; // 选完了
    }
    for (auto &&i : ans)
        printf("%d\n", i);
    return O; // awa
}
```

 ~~制作不易，点个赞再走呗qwq~~

---

## 作者：GK0328 (赞：5)

### 倍增

我们考虑按照编号从小到大加入，相当于强行钦定一个区间必须加入，判断是否合法。

首先，我们一定是把当前区间加入一个没有被覆盖过的区间中，从而把整个区间划成 $3$ 段，中间一段就是我们钦定的区间，贡献为 $1$ ，我们只需要计算剩下两段的贡献。

剩下两段的贡献，本质上来说，就是一个区间内最多能够包含多少个子区间。

我们可以贪心，比如从右往左加入区间，我们必然希望第一个区间的左端点尽量靠右，之后的区间同样要使左端点尽量靠右，显然这样可以得到最优解。

实际上，我们选取区间的过程是重复的，每次我们都会选取左端点尽量靠右的区间，因此我们可以倍增处理，容易得到一个区间的答案。

然后判断是否可行，可行的话就拆分区间，用 $\operatorname{set}$ 维护，即可快速找到当前区间所包含的区间。

判断区间是否相交，可以直接在   $\operatorname{set}$ 中查询。

Code:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#include<map>
#define N 100005
#define pr pair<int,int>
#define mp make_pair
#define IT set< pr > :: iterator
using namespace std;
const int INF=1000000007;
int n,k,c0,cnt,ck[N << 1];
int a0,ans[N];
map< pr , int >H;
int st[N << 1][22];
void ckmax(int &x,int y)
{
    x=(x>y)?x:y;
}
struct seg
{
    int l,r;
    bool operator < (const seg &A) const
    {
        return r<A.r;
    }
}g[N],h[N];
int calc(int l,int r)
{
    if (l>r)
        return 0;
    if (H.find(mp(l,r))!=H.end())
        return H[mp(l,r)];
    int e(0),x(r);
    for (int i=20;i>=0;--i)
        if (st[x][i]>=l)
            e+=(1 << i),x=st[x][i];
    return H[mp(l,r)]=e;
}
set< pr >ps;
int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i)
        scanf("%d%d",&g[i].l,&g[i].r),ck[++c0]=g[i].l,ck[++c0]=g[i].r;
    sort(ck+1,ck+c0+1);
    c0=unique(ck+1,ck+c0+1)-ck-1;
    for (int i=1;i<=n;++i)
    {
        g[i].l=lower_bound(ck+1,ck+c0+1,g[i].l)-ck;
        g[i].r=lower_bound(ck+1,ck+c0+1,g[i].r)-ck;
        h[i]=g[i];
    }
    sort(h+1,h+n+1);
    int o(1);
    for (int i=1;i<=c0;++i)
    {
        memcpy(st[i],st[i-1],sizeof(st[i-1]));
        while (o<=n && h[o].r==i)
        {
            int l(h[o].l);
            ckmax(st[i][0],l);
            ++o;
        }
        for (int j=1;st[i][j-1] && j<=20;++j)
            st[i][j]=st[st[i][j-1]][j-1];
    }
    cnt=calc(1,c0);
    if (cnt<k)
    {
        puts("-1");
        return 0;
    }
    for (int i=1;i<=n;++i)
    {
        int l(g[i].l),r(g[i].r);
        IT it=ps.upper_bound(mp(r-1,INF));
        int cl,cr;
        if (it==ps.end())
            cr=c0; else
            cr=it->first;
        if (it==ps.begin())
            cl=1; else
            --it,cl=g[it->second].r;
        if (cl>l)
            continue;
        int t0(calc(cl,cr)),t1(calc(cl,l)),t2(calc(r,cr));
        if (cnt-t0+t1+t2+1>=k)
        {
            ans[++a0]=i;
            cnt=cnt-t0+t1+t2+1;
            ps.insert(mp(l,i));
            if (a0==k)
                break;
        }
    }
    for (int i=1;i<=a0;++i)
        printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：myee (赞：3)

### 思路

我们考虑贪心选择，假设我们在已有基础上再选了一个活动，我们只用看剩下的活动最多组几个。

容易发现插入了当前活动后，我们只用把原本的一段贡献替换成 $2$ 段新的贡献即可。

我们考虑快速计算当仅考虑包含于 $l\sim r$ 时间内的活动，最多选几个。

容易发现一个贪心：我们每次总是取最小可能的一个右端点对应的活动，然后继续往右处理。

那么我们相当于就是重复 $l\leftarrow\min_{l\le L_j\le r}R_j$ 直到 $l>r$ 为止。

我们不妨把所有时间先离散化了，答案显然不变。

那么考虑建出「猫树」，对猫树上中间一层，假设为 $1\sim n$，分为 $1\sim m$ 和 $m+1\sim n$ 两部分，并且当前的询问 $l\sim r$ 跨过当前分界点。

我们考虑对原本一个活动 $(L,R)$，我们在序列上 $L$ 的位置插入 $R$ 这个元素。

那么我们考虑对所有可能的 $1\le l\le m$，预处理出 $l\sim m$ 的答案以及最后会往外跳到最小哪个 $R$；对所有可能的 $m+1\le r\le n$，预处理出 $m+1\sim r$ 对应的最小可能跳到的 $R$。

这样，我们可以统计入 $l\sim m$ 的答案后，将 $l$ 变为 $l\sim m$ 的跨界 $R$ 和 $m+1\sim r$ 的最小 $R$ 中较小的一个，往右子树递归下去。当任意时刻 $l\ge r$ 时即可直接退出。

这样单次查询即可 $O(\log n)$。

总复杂度即为 $O(n\log n)$，容易通过。

### Code

核心代码很短。

```cpp
uint L[100005],R[100005],A[200005],C[19][200005],P[19][200005],cnt;
voi build(uint L,uint R,uint h)
{
    if(R-L==1)return;
    uint Mid=(L+R)>>1;build(L,Mid,h+1),build(Mid,R,h+1);
    for(uint i=Mid-1,r=Mid,c=0,p=R;i>=L&&~i;i--)
    {
        if(_min(r,A[i]))c=C[h][A[i]]+1,p=P[h][A[i]];else if(r==Mid&&A[i]>=Mid)_min(p,A[i]);
        C[h][i]=c,P[h][i]=p;
    }
    for(uint i=Mid,p=R;i<R;i++)_min(p,A[i]),P[h][i]=p;
}
uint query(uint l,uint r)
{
    uint ans=0;
    for(uint L=0,R=cnt,h=0;l<r;h++)
    {
        uint Mid=(L+R)>>1;
        if(r<Mid){R=Mid;continue;}
        if(l>=Mid){L=Mid;continue;}
        ans+=C[h][l],l=std::min(P[h][l],P[h][r]),ans+=l<=r,L=Mid;
    }
    return ans;
}
std::map<std::pair<uint,uint>,uint>M;
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n,k;scanf("%u%u",&n,&k);
    for(uint i=0;i<n;i++)scanf("%u%u",L+i,R+i),A[i<<1]=L[i],A[i<<1|1]=R[i];
    std::sort(A,A+n*2),cnt=std::unique(A,A+n*2)-A;
    for(uint i=0;i<n;i++)L[i]=std::lower_bound(A,A+cnt,L[i])-A,R[i]=std::lower_bound(A,A+cnt,R[i])-A;
    for(uint i=0;i<cnt;i++)A[i]=cnt;
    for(uint i=0;i<n;i++)_min(A[L[i]],R[i]);
    build(0,cnt,0);
    uint s=query(0,cnt-1);
    if(s<k)return puts("-1"),0;
    M[{0,cnt-1}]=s;
    std::vector<uint>Ans;
    for(uint i=0;i<cnt&&Ans.size()<k;i++)
    {
        auto t=--M.lower_bound({L[i],-1u});
        uint u=t->first.first,v=t->first.second,w=t->second;
        if(v<R[i])continue;
        uint w1=query(u,L[i]);
        uint w2=query(R[i],v);
        if(s+1+w1+w2-w<k)continue;
        s+=1+w1+w2-w,M.erase(t),M[{u,L[i]}]=w1,M[{R[i],v}]=w2,Ans.push_back(i);
    }
    for(auto s:Ans)printf("%u\n",s+1);
    return 0;
}
```


---

## 作者：MoyunAllgorithm (赞：2)

感觉题解区其它题解都讲的较为扼要，我在看题解时看得比较难懂，后来搞懂了这道题，并写一篇更为详细的题解来巩固qwq。

**题意**

有 $N$ 个线段。你要选择 $K$ 条，它们互不相交（但可以在端点相连）。请输出字典序最小的选择方案。

**思路**


我们将线段端点离散化，之后定义倍增数组 ：

$f_{i,j}$ 代表离散化后位置在 $i$ 的**端点**（注意不是编号为 $i$ 的线段），往右选择 $2^j$ 条线段，能够到达的最近的线段右端点的位置。

有些绕口，结合样例理解：

```cpp
1 3
2 5
8 9
6 8
10 15
```
先离散化：

```cpp
1 3
2 4
6 7
5 6
8 9
```

$f_{1,0}=3$，因为从编号为 $1$ 的端点，经过 $2^0=1$ 条线段，可以到达点 $3$。

$f_{1,1}=6$，因为从编号为 $1$ 的端点，经过 $2^1=2$ 条线段，可以到达点 $6,7,9$ 等点，但 $6$ 最近。（方案：$(1,3) \rightarrow (5,6)$）

了解了 $f$ 的定义，其转移方程非常简单就是模板：

$f_{i,0}$ 是 $i$ 点所有向右射出的线段的右端点最小值。

转移是模板了， $f_{i,j}= \text{min}(f_{i,j},f_{(f_{i,j-1}),j-1})$。

这部分的代码：

```cpp
 scanf("%d %d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d",&lb[i],&rb[i]);
        dot[i]=lb[i];
        dot[i+N]=rb[i];
    }
    sort(dot+1,dot+2*N+1);
    M=unique(dot+1,dot+2*N+1)-dot;
    //离散化端点
    for(int i=1;i<=N;i++)
    {
        lb[i]=lower_bound(dot+1,dot+M+1,lb[i])-dot;
        rb[i]=lower_bound(dot+1,dot+M+1,rb[i])-dot;
    }
    for(int i=1;i<=M+2;i++)
        for(int j=0;j<25;j++)
            f[i][j]=M+2;
            //初始化。
    for(int i=1;i<=N;i++)
    {
        f[lb[i]][0]=min(f[lb[i]][0],rb[i]);
        //初始化 f[i][0]
    }
    for(int i=M;i;i--)
    {
       
        f[i][0]=min(f[i+1][0],f[i][0]);
        for(int j=1;j<=20;j++)
        {
            f[i][j]=min(f[i+1][j],f[f[i][j-1]][j-1]);
            倍增板子
        }
    }
```

这时可以求出一个区间可以放多少个互不相交的线段。倍增查询即可，$O(\log N)$。

```cpp
int Count(int l,int r)
{
    int u=l,res=0;
    for(int i=20;i>=0;i--)
    {
        if(f[u][i]<=r+1)
        {
            u=f[u][i];
            res+=(1<<i);
        }
    }
    return res;
}
```
**由于方案要求字典序最小**，所以考虑这样构造方案：

从 $1$ 到 $N$ 依次枚举线段。如果当前线段满足：

- 该线段加入后，不会和已经选择的线段相交；

- 该线段加入后，剩下的地方能够放下足够的线段，使得最终能够选出 $K$ 条线段。

如何判断第一个要求？运用 `set` 即可。定义

```cpp
struct SpareTime
{
    int l,r;
    bool operator<(const SpareTime &j) const
    {
        return r<j.l;
    }
};

set<SpareTime>st;
```
注意看重载运算符 `<`。当这样重载时，当两个 `SpareTime` 代表的线段相交时，`set` 认为它们相等。

因此，`set` 内维护 **当前的空余时间**。

一开始，`set` 内插入一条覆盖整个数轴的线段，因为还没有选择任何活动呢，都是空余时间。

对于枚举的每个活动，在 `set` 内尝试找到能够包含它的空余时间。接下来，通过上面展示的 `Count` 函数计算出如果加入这个活动，那么剩下来的空余时间能否能够加入足够的活动。如果可以，那就加入该活动，并把这段空余时间删除，加上该活动和空余时间的端点产生的新空余时间。

```cpp
 int ind=0;
    while(K)
    {
        ind++;
        int x=lb[ind],y=rb[ind];
        if(st.find((SpareTimey){x,y-1})==st.end()) continue;
        Activity cur=*st.find((SpareTime){x,y-1});
      //  printf("%d %d %d %d %d\n",ind,x,y,cur.l,cur.r);
        if(cur.l<=lb[ind]&&rb[ind]-1<=cur.r)
        {//如果该空余时间能够包含这个活动
            if(Count(cur.l,lb[ind]-1)+Count(rb[ind],cur.r)-Count(cur.l,cur.r)+cnt+1>=K)//如果参加这个活动，仍能存在方案参加K个活动
            {
                cnt+=Count(cur.l,lb[ind]-1)+Count(rb[ind],cur.r)-Count(cur.l,cur.r);
                K--;
                printf("%d\n",ind);
                st.erase(cur);
                st.insert({cur.l,lb[ind]-1});
                st.insert({rb[ind],cur.r});
//加入该活动，并修改空余时间的区间
            }
        }
    }
```


完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。！

---

## 作者：lfxxx (赞：1)

首先 $R_i \gets R_i - 1$ 变为选段，然后离散化端点。

看到字典序，直接按位贪心，每次考虑选入一个区间，找到其所在空白段的做右端点，讲空白段贡献删掉将区间自己与新增的两个空白段贡献加上判断是否大于等于 $k$ 即可。

问题变为判断空白段贡献，暴力的话存在一个 $O(n)$ 的 dp 做法，设计状态 $dp_i$ 表示从 $i$ 出发到终点最多可以拼接多少段，有 $dp_{i} = dp_{i+1},dp_{L_i} = dp_{R_i+1} + 1$。

快速计算下空白段贡献可以考虑倍增跳，我们设计状态 $dp_{i,j}$ 表示从 $i$ 出发跳 $2^j$ 步最靠前能到哪，有 $dp_{0,i} = dp_{0,i+1},dp_{0,L_i} = R_i,dp_{i,j} = dp_{dp_{i,j-1}+1,j-1}$，直接 $O(n \log n)$ 预处理即可。

每次跳空白段就从二进制高位向低位枚举跳，单次也是 $O(n)$。

维护空白段可以用 set 维护端点并给覆盖的段打上标记完成，总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int jump[maxn][20];//jump[i][j] i 2^j
int b[maxn],P[maxn],tot;
int vis[maxn];
int n,k;
int L[maxn],R[maxn];
set<int> S;
int ask(int l,int r){
    if(l>r) return 0;
    int res=0;
    int u=l;
    for(int i=19;i>=0;i--){
        if(jump[u][i]<=r){
            u=jump[u][i]+1;
            res+=(1<<i);
        }
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
        R[i]--;
        b[i*2-1]=L[i];
        b[i*2]=R[i];
    }
    sort(b+1,b+2*n+1);
    for(int i=1;i<=2*n;i++){
        if(b[i]!=b[i-1]) P[++tot]=b[i];
    }
    memset(jump,0x3f3f3f3f,sizeof(jump));
    for(int i=1;i<=n;i++){
        int l=1,r=tot+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(L[i]>=P[mid]) l=mid;
            else r=mid;
        }
        L[i]=l;
        l=1,r=tot+1;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(R[i]>=P[mid]) l=mid;
            else r=mid;
        }
        R[i]=l;
        jump[L[i]][0]=min(jump[L[i]][0],R[i]);
    }
    for(int i=tot;i>=1;i--) jump[i][0]=min(jump[i][0],jump[i+1][0]);
    for(int i=1;i<20;i++){
        for(int j=1;j<=tot;j++) 
            if(jump[j][i-1]+1<=tot)
                jump[j][i]=min(jump[j][i],jump[jump[j][i-1]+1][i-1]);
    }
    S.insert(0);
    S.insert(tot+1);
    int ans=ask(1,tot);
    if(ans<k){
        cout<<"-1\n";
        return 0;
    }
    vector<int> vec;
    for(int i=1;i<=n;i++){
        if(vis[L[i]]==0&&vis[R[i]]==0&&(*S.lower_bound(L[i]))>R[i]){
            auto it=S.lower_bound(L[i]);
            int rt=(*it);
            it--;
            int lt=(*it);
            lt++,rt--;
            if(ans-ask(lt,rt)+ask(lt,L[i]-1)+ask(R[i]+1,rt)+1>=k){
                ans=ans-ask(lt,rt)+ask(lt,L[i]-1)+ask(R[i]+1,rt)+1;
                vec.push_back(i);
                for(int j=L[i];j<=R[i];j++) vis[j]=1;
                S.insert(L[i]);
                S.insert(R[i]);
                if(vec.size()==k) break;
            }
        }
    }
    for(int x:vec) cout<<x<<'\n';
    return 0;
}
```

---

## 作者：Otue (赞：0)

### 题目描述

有 $n$ 场活动。这些活动的编号从 $1$ 到 $n$。 活动 $i$ 从时间 $L_i+10^{-9}$ 到时间 $R_i-10^{-9}$ 举行。数据保证 $L_i$ 和 $R_i$ 是整数。你决定参加其中的 $k$ 个活动。但是，你不能在中间加入或离开每个活动。**在两个活动场所间移动的时间忽略不计**。

你希望参加编号字典序较小的活动。给出每个活动的信息和你参加的活动个数 $k$，判断 JOI 君是否可以参加 $k$ 个活动，如果可以，输出所有的 $k$ 个活动的编号。

### 思路

首先将 $R_i$ 减一转化成区间互不相交。再将 $L_i,R_i$ 离散化。

考虑这类问题的直接贪心：选择没有交叉，右端点最靠左的。定义 $f(l,r)$ 表示区间 $[l,r]$ 最多能选的互不重合的区间个数。

考虑倍增求解 $f$。定义 $g_{i,j}$ 表示从 $i$ 开始选择 $2^j$ 个区间后，下一次进行选择时的左端点的最小值。显然有 $g_{l_i,0}=r_i+1$。转移需要继承上一次的答案：`g[i][j] = min{g[i + 1][j], g[g[i][j - 1][j - 1]}`。那么 $f(i,j)$ 只需要从 $i$ 开始倍增，累计答案即可。

回归本题，如何求解字典序最小的问题，那就是从 $1$ 到 $n$ 区间依次填入。只要当前的区间填入后可以保证 **可将 $k$ 个区间全部填入**，当前区间就是解。

如何判断 $[L_i,R_i]$ 是否可以填入？即可维护一个 set 表示当前未参加活动的区间，最开始区间为 $[1,n]$。若 $[L_i,R_i]$ 是一个 **未布置活动的区间** 的子集，设这个 **未布置活动的区间** 为 $[L,R]$，则 $L\leq L_i\leq R_i\leq R$。

可以计算出填入这个 $[L_i,R_i]$ 区间后的 **可填入区间变化量** 是：$f(L,L_i-1)+f(R_i+1,R)+1-f(L,R)$。填入之后，把当前 $[L,R]$ 分裂成 $[L,L_i-1]$ 和 $[R_i+1,R]$ 即可。

如何找到当前区间所被包含的区间？重定义 set 的 `<` 符号 `r < x.l`，那么如果两个区间重合，`set` 就会判定其为相等。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 2e5 + 5;

int n, k, b[N], tot, f[N][18], now;
vector<int> ans;

struct edge {
	int l, r;
}ed[N];

int query(int l, int r) {
	if (l > r) return 0;
	int x = l, res = 0;
	_pfor(i, 17, 0) {
		if (f[x][i] <= r + 1) {
			res += (1ll << i);
			x = f[x][i];
		}
	}
	return res;
}

struct stu {
	int l, r;
	bool operator < (const stu x) const {
		return r < x.l;
	}
};
set<stu> S;

signed main() {
	cin >> n >> k;
	_for(i, 1, n) {
		cin >> ed[i].l >> ed[i].r; ed[i].r--;
		b[++tot] = ed[i].l; b[++tot] = ed[i].r;
	}
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	_for(i, 1, tot + 3) _for(j, 0, 17) {
		f[i][j] = tot + 3;
	}
	_for(i, 1, n) {
		ed[i].l = lower_bound(b + 1, b + tot + 1, ed[i].l) - b;
		ed[i].r = lower_bound(b + 1, b + tot + 1, ed[i].r) - b;
		f[ed[i].l][0] = min(f[ed[i].l][0], ed[i].r + 1);
	}
	_pfor(i, tot, 1) {
		f[i][0] = min(f[i][0], f[i + 1][0]);
		_for(j, 1, 17) f[i][j] = min(f[i + 1][j], f[f[i][j - 1]][j - 1]); 
	}
	S.insert({1, tot}); now = query(1, tot);
	if (now < k) puts("-1"), exit(0);
	_for(i, 1, n) {
		auto it = S.find({ed[i].l, ed[i].r});
		if (it == S.end()) continue; stu tmp = *it;
		if (tmp.r < ed[i].r || tmp.l > ed[i].l) continue;
		int delta = query(tmp.l, ed[i].l - 1) + 1 + query(ed[i].r + 1, tmp.r) - query(tmp.l, tmp.r);
		if (now + delta >= k) {
			now += delta;
			ans.push_back(i);
			S.erase(it);
			if (tmp.l <= ed[i].l - 1) S.insert({tmp.l, ed[i].l - 1});
			if (ed[i].r + 1 <= tmp.r) S.insert({ed[i].r + 1, tmp.r});
		}
		if (ans.size() >= k) break;
	}
	for (auto v : ans) cout << v << endl;
}
```

---

## 作者：happybob (赞：0)

对于倍增一无所知。

原问题是一个简单的贪心。按照 $r$ 排序即可。

所以你会不由自主地往这个贪心上面去想。你要干什么呢？从前往后考虑每个区间，钦定必选后判断是否能选出 $\geq k$ 个。

我们要维护钦定某个必选，以及撤销。然后你发现你做不下去了。按照 $r$ 排序后钦定某个必选，很难快速维护。这个做法没啥前途。

但是你肯定是要按照贪心的顺序考虑每一个的。不妨先离散化，考虑假如我们有某一种神秘的东西，可以维护区间 $[i,j]$ 内最多选多少个。那是不是就做完了？因为我们可以用 `set` 维护目前没被钦定的段，每次钦定是 $O(1)$ 个区间分裂，可以直接维护答案。

那你怎么维护这个区间答案呢。考虑倍增。事实上这个套路应该算经典了。求出 $f_{i,j}$ 表示从 $i$ 开始，选了 $2^j$ 个不交区间，到达的最小的区间右端点在哪。这样就可以 $O(\log n)$ 查询。

每次只涉及到 $O(1)$ 次区间查询，总复杂度 $O(n \log n)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <cstring>
#include <string>
using namespace std;

const int N = 2e5 + 5;

int n, l[N], r[N], f[N][20], k;
vector<double> v;
int ans;

inline int query(int x, int y)
{
	if (x > y) return 0;
	int now = x, ans = 0;
	for (int i = 19; i >= 0; i--)
	{
		if (f[now][i] <= y)
		{
			ans += (1 << i);
			now = f[now][i] + 1;
		}
	}
	return ans;
}

vector<pair<pair<int, int>, bool>> er;

struct Node
{
	int l, r;
	Node() = default;
	Node(int l, int r) : l(l), r(r) {}
	bool operator<(const Node& x) const noexcept
	{
		return l < x.l;
	}
};
set<Node> st;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> l[i] >> r[i], v.emplace_back(l[i] + 0.1), v.emplace_back(r[i] - 0.1);
	sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++)
	{
		l[i] = lower_bound(v.begin(), v.end(), l[i] + 0.1) - v.begin() + 1;
		r[i] = lower_bound(v.begin(), v.end(), r[i] - 0.1) - v.begin() + 1;
	}
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; i++)
	{
		f[l[i]][0] = min(f[l[i]][0], r[i]);
	}
	for (int i = 2 * n - 1; i >= 1; i--) f[i][0] = min(f[i][0], f[i + 1][0]);
	for (int j = 1; j <= 19; j++)
	{
		for (int i = 1; i <= 2 * n; i++)
		{
			if (f[i][j - 1] <= 2 * n) f[i][j] = f[f[i][j - 1] + 1][j - 1];
		}
	}
	ans = query(1, 2 * n);
	if (ans < k)
	{
		cout << "-1\n";
		return 0;
	}
	st.insert(Node(1, 2 * n));
	vector<int> res;
	for (int i = 1; i <= n; i++)
	{
		if (res.size() == k) break;
		if (st.begin()->l > l[i]) continue;
		auto it = --st.upper_bound(Node(l[i], r[i]));
		if (it->l <= l[i] && it->r >= r[i])
		{
			int nres = ans - query(it->l, it->r) + query(it->l, l[i] - 1) + 1 + query(r[i] + 1, it->r);
			if (nres >= k)
			{
				res.emplace_back(i);
				ans = nres;
				auto rr = *it;
				st.erase(it);
				if (rr.l < l[i])
				{
					st.insert(Node(rr.l, l[i] - 1));
				}
				if (r[i] < rr.r)
				{
					st.insert(Node(r[i] + 1, rr.r));
				}
			}
		}
	}
	for (auto& x : res) cout << x << "\n";
	return 0;
}
```

---

## 作者：7KByte (赞：0)

求字典序最小的答案，从前往后一次考虑每一位。

即枚举 $i$ 从 $1$ 到 $n$ 判断当前活动加入后是否能够达到 $k$ 的总数，如果能则加入当前的 $i$ 。

这样我们只用在线维护当前空缺位置能够加入活动的最大值。

考虑加入活动 $i$ 后，最多由原来的一个连续区间断开成两个连续的区间，所以我们只用快速计算区间 $[l,r]$ 中最多能放入的方案数。

由于是静态问题，考虑倍增。令 $f[i][j] $ 表示从位置 $i$ 开始，加入 $j$ 个区间后到达的最近位置。

初值 $f[L_i][i]=\min\{R_i\}$ 。

转移 $f[i][0]=\min\{f[i][0],f[i+1][0]\}$ ， $f[i][j]=\min\{f[i+1][j],f[f[i][j-1][j-1]]\}$ 。

对于空缺的位置，我们重载运算符 $< $ ，$[l_1,r_1]<[l_2,r_2]$ 当且仅当 $r_1<l_2$ ，然后用 ``set`` 维护即可。

时间复杂度 $\mathcal{O}(n\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,k,L[N],R[N],f[N][17],t,o[N],b[N],T,w;
int calc(int l,int r){
	if(l>r)return 0;int now=0;
	pre(i,t,0)if(f[l][i]<=r+1)now+=1<<i,l=f[l][i];
	return now;
}
struct node{
	int l,r;
	node(int ll=0,int rr=0){l=ll,r=rr;}
	bool operator<(const node o)const{return r<o.l;}
};set<node>s;
int main(){
	scanf("%d%d",&n,&k);t=log2(k);
	rep(i,1,n)scanf("%d%d",&L[i],&R[i]),o[++w]=L[i],o[++w]=R[i];
	sort(o+1,o+w+1);rep(i,1,w)if(o[i]!=o[i-1])b[++T]=o[i];
	rep(i,1,n)L[i]=lower_bound(b+1,b+T+1,L[i])-b,R[i]=lower_bound(b+1,b+T+1,R[i])-b;
	rep(i,1,T+2)rep(j,0,t)f[i][j]=T+2;
	rep(i,1,n)f[L[i]][0]=min(f[L[i]][0],R[i]);
	pre(i,T,1){
		f[i][0]=min(f[i][0],f[i+1][0]);
		rep(j,1,t)f[i][j]=min(f[i+1][j],f[f[i][j-1]][j-1]);
	}puts("No Copy");
	s.insert(node(1,T));int sum=calc(1,T);
	if(sum<k){printf("-1\n");return 0;}
	rep(i,1,n){
		if(s.find(node(L[i],R[i]-1))==s.end())continue;
		node cur=*s.find(node(L[i],R[i]-1));
		if(cur.l<=L[i]&&cur.r>=R[i]-1){
			int dta=calc(cur.l,L[i]-1)+calc(R[i],cur.r)-calc(cur.l,cur.r);
			if(dta+sum>=k-1){
				printf("%d\n",i);k--;
				sum+=dta;s.erase(cur);
				if(cur.l<L[i])s.insert(node(cur.l,L[i]-1));
				if(cur.r>=R[i])s.insert(node(R[i],cur.r));
			}
		}
		if(!k)return 0;
	}
	return 0;
}
```

---

