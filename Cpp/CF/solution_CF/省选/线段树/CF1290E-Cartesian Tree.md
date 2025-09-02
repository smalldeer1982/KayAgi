# Cartesian Tree

## 题目描述

Ildar is the algorithm teacher of William and Harris. Today, Ildar is teaching Cartesian Tree. However, Harris is sick, so Ildar is only teaching William.

A cartesian tree is a rooted tree, that can be constructed from a sequence of distinct integers. We build the cartesian tree as follows:

1. If the sequence is empty, return an empty tree;
2. Let the position of the maximum element be $ x $ ;
3. Remove element on the position $ x $ from the sequence and break it into the left part and the right part (which might be empty) (not actually removing it, just taking it away temporarily);
4. Build cartesian tree for each part;
5. Create a new vertex for the element, that was on the position $ x $ which will serve as the root of the new tree. Then, for the root of the left part and right part, if exists, will become the children for this vertex;
6. Return the tree we have gotten.

For example, this is the cartesian tree for the sequence $ 4, 2, 7, 3, 5, 6, 1 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/acc7800e10b8c919d4950616a18f2140e891d16a.png)After teaching what the cartesian tree is, Ildar has assigned homework. He starts with an empty sequence $ a $ .

In the $ i $ -th round, he inserts an element with value $ i $ somewhere in $ a $ . Then, he asks a question: what is the sum of the sizes of the subtrees for every node in the cartesian tree for the current sequence $ a $ ?

Node $ v $ is in the node $ u $ subtree if and only if $ v = u $ or $ v $ is in the subtree of one of the vertex $ u $ children. The size of the subtree of node $ u $ is the number of nodes $ v $ such that $ v $ is in the subtree of $ u $ .

Ildar will do $ n $ rounds in total. The homework is the sequence of answers to the $ n $ questions.

The next day, Ildar told Harris that he has to complete the homework as well. Harris obtained the final state of the sequence $ a $ from William. However, he has no idea how to find the answers to the $ n $ questions. Help Harris!

## 说明/提示

After the first round, the sequence is $ 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/b1534ebc83eb23d6f6505c6a2ab3b3a8035f9fce.png)The answer is $ 1 $ .

After the second round, the sequence is $ 2, 1 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/eff7476771d279f495520b7bd67cd481bc4c7064.png)The answer is $ 2+1=3 $ .

After the third round, the sequence is $ 2, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/c77bba87ff3ea714273a2609c35f8c7ab239c7fd.png)The answer is $ 2+1+3=6 $ .

After the fourth round, the sequence is $ 2, 4, 1, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/dbef4f1eef8c88dd3dafdd5976421a830b9d116e.png)The answer is $ 1+4+1+2=8 $ .

After the fifth round, the sequence is $ 2, 4, 1, 5, 3 $ . The tree is

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1290E/044610082349c82baf738e950f52290ea3f1ea74.png)The answer is $ 1+3+1+5+1=11 $ .

## 样例 #1

### 输入

```
5
2 4 1 5 3```

### 输出

```
1
3
6
8
11```

## 样例 #2

### 输入

```
6
1 2 4 5 6 3```

### 输出

```
1
3
6
8
12
17```

# 题解

## 作者：Kinandra (赞：22)

标签: 线段树beats, 笛卡尔树.

#### Part 1

笛卡尔树中的以 $i$ 为根的子树 对应 排列中以 $a_i$ 为最大值的极大区间(记为 $(l_i,r_i)$, 其中 $l_i,r_i$ 分别为位置 $i$ 左边, 右边第一个比 $a_i$ 大的位置).

那么求子树大小和等价于求区间长度和, 即 $s_x=\sum_{a_i\leqslant x}(r_i-l_i-1)$ , 注意这里 $l,r$ 是在去掉 $a_i>x$ 后的子序列上定义的, 而不是在整个 $a$ 上的, 所以只在 $a_i\leqslant x$ 的位置上有意义.

所以只要能在从小到大插入 $a$ 的过程中维护 $\sum l$ 和 $\sum r$ 即可求答案了, 求 $\sum l$ 和 $\sum r$ 是两个相同的问题, 下面考虑如何求 $\sum r$ .

#### Part 2

因为插入是从小到大的, 所以新插入的值 $x$ 会成为序列的最大值, 设这个位置在原排列中为 $p$ .

考虑新序列 $r$ 与原序列 $r$' 的关系:

- $i>p\wedge a_i<x$ , $r_i=r_i'+1$ .
- $r_p=x+1$ ($r_p'$ 无意义).
- $i<p\wedge a_i<x$, $r_i=\min\{r'_i,p'\}$ , 其中 $p'$ 为子序列中 $x$ 的位置. 

也就是说我们需要维护如下操作:

- 区间加.
- 单点修改.
- 区间对一个值取 $\min$ .

同时要支持查询:

- 全局和.

这个东西可以通过 `线段树beats` 来维护.

具体来讲, 对线段树每一个节点维护: 最大值 $v$ , 次大值 $s$ , 最大值个数 $len$ , 非最大值的个数 $slen$ , 区间和 $sum$ , 同时需要维护标记: 对最大值的加减标记 $t$ 和对非最大值的加减标记 $st$ .

同时我们需要支持查询 $p'$ 这个直接在线段树节点上维护已经插入的位置数量 $c$ (其实 $c=len+slen$ , 不维护也可) .

时间复杂度 $\mathcal O(n\log^2 n)$ .

#### Part 3 trick

我们求出 $A_x=\sum r$ 后可以把原排列 `reverse` 后用同样方法求一遍可得 $B_x=\sum x-l+1$ ,  则有 $s_x=\sum r-l-1=A_x+B_x-x(x+2)$ .

#### Part 4 Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();
int n, a[200005], p[200005];

#define root 1, n, 1
#define ls l, mid, k << 1
#define rs mid + 1, r, k << 1 | 1
struct Seg {
    int c[1000006], v[1000006], s[1000006], tg[1000006], stg[1000006];
    int len[1000006], slen[1000006];
    long long sum[1000006];
    void clear(int l, int r, int k) {
        v[k] = s[k] = c[k] = tg[k] = stg[k] = len[k] = slen[k] = sum[k] = 0;
        if (l == r) return;
        int mid = l + r >> 1;
        clear(ls), clear(rs);
    }

    void update(int k) {
        int L = k << 1, R = k << 1 | 1;
        c[k] = c[L] + c[R], len[k] = len[L] + len[R], sum[k] = sum[L] + sum[R];
        if (v[L] > v[R]) {
            v[k] = v[L], s[k] = max(s[L], v[R]);
            len[k] = len[L], slen[k] = slen[L] + len[R] + slen[R];
        } else if (v[L] < v[R]) {
            v[k] = v[R], s[k] = max(v[L], s[R]);
            len[k] = len[R], slen[k] = slen[R] + len[L] + slen[L];
        } else {
            v[k] = v[L], s[k] = max(s[L], s[R]);
            len[k] = len[L] + len[R], slen[k] = slen[R] + slen[L];
        }
    }

    void Tag(int k, int t1, int t2, int ctm) {
        if (!ctm) t1 = t2;
        v[k] += t1, tg[k] += t1, s[k] += t2, stg[k] += t2;
        sum[k] += 1ll * t1 * len[k] + 1ll * t2 * slen[k];
    }

    void psd(int k) {
        int L = k << 1, R = k << 1 | 1, mr = v[R] >= v[L];
        Tag(L, tg[k], stg[k], v[L] >= v[R]);
        Tag(R, tg[k], stg[k], mr), tg[k] = stg[k] = 0;
    }

    int add(int l, int r, int k, int st, int en) {
        if (st > r || en < l) return 0;
        if (st <= l && en >= r) return Tag(k, 1, 1, 1), c[k];
        int mid = (psd(k), l + r >> 1), rt = 0;
        rt = add(ls, st, en) + add(rs, st, en), update(k);
        return rt;
    }
    void modi(int l, int r, int k, int p, int tv) {
        if (l == r) return sum[k] = v[k] = tv, len[k] = c[k] = 1, void();
        int mid = (psd(k), l + r >> 1);
        p <= mid ? modi(ls, p, tv) : modi(rs, p, tv), update(k);
    }
    void pmin(int l, int r, int k, int st, int en, int tv) {
        if (st > r || en < l || tv >= v[k]) return;
        if (st <= l && en >= r && tv > s[k])
            return Tag(k, min(tv - v[k], 0), 0, 1), void();
        int mid = (psd(k), l + r >> 1);
        pmin(ls, st, en, tv), pmin(rs, st, en, tv), update(k);
    }
} seg;

long long res[200005];
int main() {
    n = read();
    for (int i = 1; i <= n; ++i) p[a[i] = read()] = i;
    for (int t = 1; t <= 2; ++t) {
        seg.clear(root);
        for (int i = 1, x; i <= n; ++i) {
            x = seg.add(root, p[i] + 1, n), seg.modi(root, p[i], i + 1);
            seg.pmin(root, 1, p[i] - 1, i - x), res[i] += seg.sum[1];
        }
        for (int i = 1; i <= n; ++i) p[i] = n - p[i] + 1;
    }

    for (int i = 1; i <= n; ++i) printf("%lld\n", res[i] - 1ll * i * (i + 2));
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
```

---

## 作者：摸鱼酱 (赞：5)

给定一个排列 $a$，对于 $k\in[1,n]$，求所有 $a_i\leq k$ 的子序列构成大根笛卡尔树的子树大小和。

$1\leq n\leq 1.5\times 10^5$。

考虑每次新加入一个数列里当前的最大值。

维护 $l_i,r_i$ 表示 $i$ 位置左/右边第一个值大于 $a_i$ 的位置，那么有答案为 $\sum r_i-l_i-1=\sum r-\sum l -k$，即对于每个元素计算它会给哪一段区间贡献深度 +1，子树大小和也就是所有点深度的和。

考虑如何动态维护 $l,r$，每次插入的一定是最大值，假设在 $p$ 位置插入，实际在插入后序列的位置是 $p'$，那么 $l_p=0,r_p=k+1$。

由于这里的 $l,r$ 是对于目前的序列而言的，所以插入一个新的元素之后有 $\forall x\in(p,n],l_x\gets l_x+1,r_x\gets r_x+1$，另外有 $\forall x\in[1,p),r_x\gets \min\{r_x,p'\}$，$\forall x\in(p,n]$，$l_x\gets \max\{l_x,p'\}$。

于是需要支持区间加，区间取 $\min$，区间求和，上一手 beats 维护就好了。

不需要写区间取 $\max$，维护 $l$ 的时候都维护相反数就好了。

[code](https://www.luogu.com.cn/paste/hojewzni)



---

## 作者：JimmyLee (赞：3)

# 题意

> 给定一个 $1\sim n$ 的排列 $a$。
> 
> 对于一个整数 $k\in[1,n]$，将排列中 $\leqslant k$ 的项构成的子序列建**大根笛卡尔树**。这棵笛卡尔树的所有节点的子树大小之和记为 $s_k$。
>
> $\forall k\in[1,n]$，$s_k$。

# 分析

首先看到题目要求维护 $s_k$，但是这个东西和笛卡尔树的性质没什么关系。

考虑将 $s_k$ 拆成多个信息。

根据笛卡尔树的性质，我们知道 $s_i$ 就是子序列上以 $i$ 为最大值的极大区间 $[l_i, r_i]$ 的长度。

意味着 $l_i-1$ 等于 $0$ 或其权值 $val_{l_i-1}>i$。

另一侧同理。

因为 $s_i=r_i-l_i+1$，所以我们维护左右端点 $l_i,r_i$。

答案为 $\sum_{i=1}^k\limits s_i = \sum_{i=1}^k\limits r_i - l_i + 1$。

---

我们考虑如何维护 $l_i$ 和 $r_i$。

这里以 $r_i$ 为例。

先想一下子序列形成的过程，我们可以想成向一个序列中每次插入值，然后再查询。

有个显然的性质：**每次插入的值是插入后序列的最大值。**

我们将子序列沿插入位置 $p$ 拆成两个区间 $[1,p-1]$ 和 $[p+1, k]$。

对于 $i \in [1, p-1]$，因为值一定小于新插入的值，所以其右端点 $r_i$ 一定也在区间 $[1,p-1]$ 中。

所以 $r_i \gets \min(r_i,p-1)$。

而对于 $i \in [p+1, k]$，它们的 $r_i$ 和新插入的值无关，只是增加了 $1$。

$l_i$ 的想法差不多，二者维护方式如下：
$$
\begin{align}
r_i & \gets 
\begin{cases}
\min(r_i, p-1) & i\in [1,p-1] \\
r_i+1 & i\in[p+1,k]
\end{cases}
\\
l_i &\gets 
\begin{cases}
l_i & i\in [1,p-1] \\
\max(p+1, l_i+1) & i\in[p+1,k]
\end{cases}
\end{align}
$$

新插入的值作为序列的最大值，其子树就是整棵树，所以 $l_p \gets 1,r_p\gets k$。

---

所以我们只需要写一个数据结构支持以下四种操作：

- 单点插入一个值。
- 区间加。
- 区间取 $\min$ 或 $\max$。
- 查询和。

直接上平衡树。

---

写能维护 $\min$ 和 $\max$ 的平衡树码量有点大，可以只写能维护 $\min$ 的平衡树。

这时维护的就是 $r_i$ 和 $-l_i$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace Base_Treap
{
    mt19937 rnd(time(0));

    #define mx(x) (x?x->mx:-INT_MAX)
    #define smx(x) (x?x->smx:-INT_MAX)
    #define siz(x) (x?x->siz:0)

    struct node
    {
        uint32_t siz;
        uint64_t id;
        node *lc, *rc;
        int mx, smx, cnt, tag1, tag2, val;
        int64_t sum;

        node(int v, uint64_t idd) {sum=mx=val=v, lc=rc=0, siz=cnt=1, id=idd, smx=-INT_MAX, tag1=0; tag2=-INT_MAX;}
    
        void push_up()
        {
            sum=val;siz=1;
            if(lc) sum+=lc->sum, siz+=lc->siz;
            if(rc) sum+=rc->sum, siz+=rc->siz;
            mx=max({val, mx(lc), mx(rc)});
            smx=max(smx(lc), smx(rc));
            cnt=0;
            if(mx==val) cnt++;
            else smx=max(smx, val);
            if(mx==mx(lc)) cnt+=lc->cnt;
            else smx=max(smx, mx(lc));
            if(mx==mx(rc)) cnt+=rc->cnt;
            else smx=max(smx, mx(rc));
        }

        void add(int v) 
        {
            sum+=1ll*v*siz;
            mx+=v;
            val+=v;
            if(smx!=-INT_MAX) smx+=v;
            if(tag2!=-INT_MAX) tag2+=v;
            tag1+=v; 
        }

        void do_min(int v)
        {
            if(v>=mx) return;
            sum-=1ll*(mx-v)*cnt;
            val=min(val, v);
            tag2=mx=v;
        }

        void push_down()
        {
            if(tag1)
            {
                if(lc) lc->add(tag1);
                if(rc) rc->add(tag1);
                tag1=0;
            }
            if(tag2!=-INT_MAX)
            {
                if(lc) lc->do_min(tag2);
                if(rc) rc->do_min(tag2);
                tag2=-INT_MAX;
            }
        }

        void modify(int x)
        {
            if(mx<=x) return;
            if(smx<x) return do_min(x);
            push_down();
            if(val>x) sum-=val-x, val=x;
            if(lc) lc->modify(x);
            if(rc) rc->modify(x);
            push_up();
        }
    };

    node* new_node(int x) {return new node(x, rnd());}

    void split(node *x, uint32_t k, node *&l, node *&r)
    {
        if(!x) return l=r=0, void();
        x->push_down();
        if(k>siz(x->lc)) l=x, split(x->rc, k-siz(x->lc)-1, x->rc, r);
        else             r=x, split(x->lc, k, l, x->lc);
        x->push_up();
    }

    node* merge(node *x, node *y)
    {
        if(!x||!y) return x?x:y;
        if(x->id>y->id)
        {
            x->push_down();
            x->rc=merge(x->rc, y);
            x->push_up();
            return x;
        }
        else
        {
            y->push_down();
            y->lc=merge(x, y->lc);
            y->push_up();
            return y;
        }
    }
}

using namespace Base_Treap;

node *rtl=0, *rtr=0;

void modify_r(int p, int v)
{
    node *a, *b;
    split(rtr, p, a, b);
    if(a) a->modify(p);
    if(b) b->add(1);
    rtr=merge(a, merge(new_node(v), b));
}

void modify_l(int p)
{
    node *a, *b;
    split(rtl, p, a, b);
    if(b) b->add(-1), b->modify(-p-2);
    rtl=merge(a, merge(new_node(-1), b));
}

int a[150005], pos[150005];

struct BIT: vector<int>
{
    using vector<int>::vector;
    void modify(int p) {for(;p<size();p+=p&-p) at(p)++;} 
    int query(int p) {int r=0;for(;p;p-=p&-p) r+=at(p); return r;}
}ta(150005);

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i], pos[a[i]]=i;
    for(int i=1;i<=n;i++)
    {
        int np=ta.query(pos[i]);
        ta.modify(pos[i]);
        modify_l(np);
        modify_r(np, i);
        cout<<rtr->sum+rtl->sum+i<<'\n';
    }
}
```

---

## 作者：_SeeleVollerei_ (赞：3)

感觉这个题有 *3300 还是挺奇怪的，但是毕竟是经过时代更迭的题，就好像若干年前的神仙题到现在都变成板子题了一个道理。

其实老早就想个大概了，但是前前后后悠哉游哉半个小时愣是刚刚才想出来怎么维护。

考虑笛卡尔树上一个点 $u$ 的子树大小相当于在原序列上找到一个 $L$ 和 $R$ 满足 $L$ 是左边第一个大于 $a_u$ 的位置，$R$ 是右边第一个大于 $a_u$ 的位置。那么这个子树对应的就是区间 $[L+1,R-1]$，所以贡献为 $R-L-1$。

问题转换为维护这个 $L$ 和 $R$，考虑每次加点的时候，新加的数实际上是当前的最大值，所以只需要一个前缀的 $R$ 对当前位置取 $\min$ 和一个后缀的 $L$ 对当前位置取 $\max$ 即可，这个可以吉老师线段树去做。

还有一个问题在于这里的 $[L,R]$ 不是原序列上的编号，而是当前这个动态加点的序列。考虑每次加点的时候对这个编号的影响，显然对左边没影响，对右边集体 +1。

那么因为前缀对当前点取 $\min$ 了，所以前缀的 $R$ 是不会受到影响的，而后缀的 $R$ 一定在当前的点的后面，所以直接区间加即可。后缀同理，有影响的是后缀的 $L$，但是因为取了 $\max$，所以全部都有影响，只需要一个区间加即可，复杂度 $O(n\log^2n)$。

因为涉及到还未加入的点，这里我选择平衡树实现。

平衡树比线段树恶心的地方在于 update 的时候记得考虑这个点自己的值。

https://codeforces.com/contest/1290/submission/170455586

---

## 作者：Presentation_Emitter (赞：3)

## 前置芝士：吉司机线段树

因为本题出现在了校内的专题训练中，因此会尽力让和这个蒟蒻一样菜的人看懂（~~话说应该没人会闲着没事做一道`3300`的DS吧~~）

本人并不会用某些trick，所以本题解需要3棵线段树（没错这个蒟蒻连树状数组都不会）。

本题的操作明显不是在树上插入（见@Fuyuki 奆佬的题解），因此，我们需要思考关于笛卡尔树的性质。

> “笛卡尔树是一种二叉树。每一个结点由一个键值二元组 $(k,w)$ 构成。要求 $k$ 满足二叉搜索树的性质，而 $w$ 满足堆的性质。如果笛卡尔树的 $k,w$ 键值确定，且 $k$ 互不相同， $w$ 互不相同，那么这个笛卡尔树的结构是唯一的。”——OI wiki

由题意可得，本题的笛卡尔树的键值 $k$ 为数据在每一个询问中的子序列的位置，而 $w$ 显然是唯一的。对于这种特殊的笛卡尔树，有以下的性质：一棵子树内的下标是连续的一个区间（这样才能满足[二叉搜索树](https://oi-wiki.org/ds/bst/)的性质）。

接下来我们看向样例。

a:`2 4 1 5 3`。

以下的 $k$ 均为题目中的 $k$，而不是笛卡尔树的键值。

$k=1$ 时：

$1$ 的子树对应区间 $[1,1]$，即`1`。

$k=2$ 时：

$1$ 的子树对应区间 $[2,2]$，即`1`。  
$2$ 的子树对应区间 $[1,2]$，即`2 1`。

以下省略若干行。你们可以自己推一下。

最后我们可以得到这样的性质。设排列中 $\le k$ 的项构成的子序列为 $a^{\prime}$，$i$ 的子树对应区间 $[l,r]$，则

$$l=\max\limits_{1 \le j \lt i \land a^{\prime}_{j}>a^{\prime}_{i}}{j+1}$$

$$r=\min\limits_{i \gt j \le k \land a^{\prime}_{j}>a^{\prime}_{i}}{j-1}$$

即为：$l$ 是 $i$ 左侧第一个大于 $a^{\prime}_{i}$ 的位置。$r$ 同理。

计算答案的时候我们直接统计 $\sum r-\sum l + k$ 即可。

但是直接统计 $l$ 和 $r$ 是 $\Theta(n)$ 的，所以我们这里需要考虑每次在排列中插入了一个最大的元素（设其在排列中的位置为 $i$）后对答案的影响。（其实已经有奆佬提到了）

- $\forall j \lt i$，$r_j \leftarrow \min(r_j,i-1)$

- $l_i \leftarrow 1,r_i \leftarrow i$（因为 $a^{\prime}_{i}$ 是最大的）

- $\forall j \gt i$，$l_j \leftarrow \max(l_j+1,i+1),r_j \leftarrow r_j+1$

把 $j \gt i$ 的情况转换一下，就是 $l_j \leftarrow l_j+1,r_j \leftarrow r_j+1,l_j \leftarrow \max(l_j,i+1)$。

此处 $j \gt i$ 的情形中，对 $l_j$ 的处理运用分类讨论思想。若 $l_j \gt i$，则 $l_j$ 的左边会多出一个点。否则 $l_j$ 向左边的拓展会被 $i$ 阻挡。

于是我们需要维护一个数据结构支持以下操作：

- 区间加1
- 区间取 $\min / \max$
- 单点赋值

这是吉司机线段树的基本操作。吉司机线段树的例题见 ~~`爆炸OJ`~~ `BZOJ4695 最 fAKe 女选手`（因为 `BZOJ` 它死了，所以可以找一个镜像，或者直接点[这里](https://oi-wiki.org/ds/seg-beats/)）。复杂度为 $\Theta(n \log^2 n)$ ，证明可以见2016年集训队论文。（感性理解即可）

因为大部分时候数列都是不完整的，所以在线段树中我们需要维护节点对应的区间中**合法点**（即 $\le k$ 的点）的个数。在合法点个数为`0`时直接退出递归。

记得在单点修改时将合法点个数改为`1`，上传时（`pushup`或`update`）处理合法点个数。

那么我们用了两棵吉司机线段树。剩下的那棵树的用处就是在每次加入一个点时确定所有点在子序列中的位置。实现起来很简单。设该线段树维护的序列为 $pos$，当前插入的元素为 $a_i$，$\forall j \gt i$，$pos_j \leftarrow pos_j+1$ 即可。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define neinf 0xcfcfcfcf
#define inf 0x3f3f3f3f
#define uint unsigned int
#define reg register
#define il inline
#define len 150000
#define siz (len << 1)
#define mid ((l + r) >> 1)

il int umax(int a, int b) {return a > b ? a : b;}

il int umin(int a, int b) {return a < b ? a : b;}

il int rd()
{
	reg int res = 0; reg char ch = getchar();
	while (ch < '0' || ch > '9')
		ch = getchar();
	while (ch >= '0' && ch <= '9')
		res = res * 10 + (ch & 15), ch = getchar();
	return res;
}

il void prt(ll x, char t)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) prt(x / 10, 0), x %= 10;
	putchar(x | 48);
	if (t) putchar(t);
}
int n, a[len + 5], rf[len + 5];
#define mnl(i) ((SGTL::tl + (i)) -> __v1)
#define smnl(i) ((SGTL::tl + (i)) -> __v2)
#define cmnl(i) ((SGTL::tl + (i)) -> __v3)
#define tmxl(i) ((SGTL::tl + (i)) -> __v4)
#define tqll(i) ((SGTL::tl + (i)) -> __v5)
#define suml(i) ((SGTL::tl + (i)) -> __v6)
#define clgl(i) ((SGTL::tl + (i)) -> __v7)
#define mxr(i) ((SGTR::tr + (i)) -> __v1)
#define smxr(i) ((SGTR::tr + (i)) -> __v2)
#define cmxr(i) ((SGTR::tr + (i)) -> __v3)
#define tmnr(i) ((SGTR::tr + (i)) -> __v4)
#define tqlr(i) ((SGTR::tr + (i)) -> __v5)
#define sumr(i) ((SGTR::tr + (i)) -> __v6)
#define clgr(i) ((SGTR::tr + (i)) -> __v7)
#define sump(i) ((SGTP::tp + (i)) -> __v1)
#define tagp(i) ((SGTP::tp + (i)) -> __v2)

namespace SGTL
{
	struct node
	{
		int __v1, __v2, __v3, __v4, __v5;
		ll __v6;
		int __v7;
	} tl[siz + 5];
	int ls[siz + 5], rs[siz + 5], cnt;
	il void pushup(int i)
	{
		reg int sl = *(ls + i), sr = *(rs + i);
		suml(i) = suml(sl) + suml(sr);
		clgl(i) = clgl(sl) + clgl(sr);
		if (mnl(sl) == mnl(sr))
		{
			mnl(i) = mnl(sl);
			cmnl(i) = cmnl(sl) + cmnl(sr);
			smnl(i) = umin(smnl(sl), smnl(sr));
		}
		else if (mnl(sl) < mnl(sr))
		{
			mnl(i) = mnl(sl);
			cmnl(i) = cmnl(sl);
			smnl(i) = umin(smnl(sl), mnl(sr));
		}
		else
		{
			mnl(i) = mnl(sr);
			cmnl(i) = cmnl(sr);
			smnl(i) = umin(mnl(sl), smnl(sr));
		}
	}
	il void tagplus(int i, int l, int r, int v)
	{
		suml(i) += 1ll * clgl(i) * v;
		mnl(i) += v;
		if (smnl(i) != inf)
			smnl(i) += v;
		if (tmxl(i) != neinf)
			tmxl(i) += v;
		tqll(i) += v;
	}
	il void tagmax(int i, int v)
	{
		if (v <= mnl(i)) return;
		suml(i) += (v - mnl(i)) * cmnl(i);
		mnl(i) = v;
		tmxl(i) = v;
	}
	il void pushdown(int i, int l, int r)
	{
		reg int sl = *(ls + i), sr = *(rs + i);
		if (tqll(i))
		{
			tagplus(sl, l, mid, tqll(i));
			tagplus(sr, mid + 1, r, tqll(i));
			tqll(i) = 0;
		}
		if (tmxl(i) != neinf)
		{
			tagmax(sl, tmxl(i));
			tagmax(sr, tmxl(i));
			tmxl(i) = neinf;
		}
	}
	void build(int i, int l, int r)
	{
		smnl(i) = inf;
		tmxl(i) = neinf;
		clgl(i) = mnl(i) = cmnl(i) = tqll(i) = suml(i) = 0;
		++cnt;
		if (l == r) return;
		if (l <= mid)
			build((*(ls + i) = cnt + 1), l, mid);
		if (r > mid)
			build((*(rs + i) = cnt + 1), mid + 1, r);
		pushup(i);
	}
	void add(int i, int l, int r, int lt, int rt, int v)
	{
		if (lt > rt || !clgl(i)) return;
		if (l >= lt && r <= rt)
		{
			tagplus(i, l, r, v); return;
		}
		pushdown(i, l, r);
		if (mid >= lt)
			add(ls[i], l, mid, lt, rt, v);
		if (mid < rt)
			add(rs[i], mid + 1, r, lt, rt, v);
		pushup(i);
	}
	void modify(int i, int l, int r, int p, int v)
	{
		if (l == r)
		{
			mnl(i) = suml(i) = v;
			cmnl(i) = clgl(i) = 1;
			return;
		}
		pushdown(i, l, r);
		if (mid >= p)
			modify(ls[i], l, mid, p, v);
		if (mid < p)
			modify(rs[i], mid + 1, r, p, v);
		pushup(i);
	}
	void mmax(int i, int l, int r, int lt, int rt, int v)
	{
		if (lt > rt || !clgl(i)) return;
		if (v <= mnl(i)) return;
		if (l >= lt && r <= rt && v < smnl(i))
		{
			tagmax(i, v); return;
		}
		pushdown(i, l, r);
		if (mid >= lt)
			mmax(ls[i], l, mid, lt, rt, v);
		if (mid < rt)
			mmax(rs[i], mid + 1, r, lt, rt, v);
		pushup(i);
	}
}

namespace SGTR
{
	struct node
	{
		int __v1, __v2, __v3, __v4, __v5;
		ll __v6;
		int __v7;
	} tr[siz + 5];
	int ls[siz + 5], rs[siz + 5], cnt;
	il void pushup(int i)
	{
		reg int sl = *(ls + i), sr = *(rs + i);
		sumr(i) = sumr(sl) + sumr(sr);
		clgr(i) = clgr(sl) + clgr(sr);
		if (mxr(sl) == mxr(sr))
		{
			mxr(i) = mxr(sl);
			cmxr(i) = cmxr(sl) + cmxr(sr);
			smxr(i) = umax(smxr(sl), smxr(sr));
		}
		else if (mxr(sl) > mxr(sr))
		{
			mxr(i) = mxr(sl);
			cmxr(i) = cmxr(sl);
			smxr(i) = umax(smxr(sl), mxr(sr));
		}
		else
		{
			mxr(i) = mxr(sr);
			cmxr(i) = cmxr(sr);
			smxr(i) = umax(mxr(sl), smxr(sr));
		}
	}
	il void tagplus(int i, int l, int r, int v)
	{
		sumr(i) += 1ll * clgr(i) * v;
		mxr(i) += v;
		if (smxr(i) != neinf)
			smxr(i) += v;
		if (tmnr(i) != inf)
			tmnr(i) += v;
		tqlr(i) += v;
	}
	il void tagmin(int i, int v)
	{
		if (v >= mxr(i)) return;
		sumr(i) -= (mxr(i) - v) * cmxr(i);
		mxr(i) = v;
		tmnr(i) = v;
	}
	il void pushdown(int i, int l, int r)
	{
		reg int sl = *(ls + i), sr = *(rs + i);
		if (tqlr(i))
		{
			tagplus(sl, l, mid, tqlr(i));
			tagplus(sr, mid + 1, r, tqlr(i));
			tqlr(i) = 0;
		}
		if (tmnr(i) != inf)
		{
			tagmin(sl, tmnr(i));
			tagmin(sr, tmnr(i));
			tmnr(i) = inf;
		}
	}
	void build(int i, int l, int r)
	{
		smxr(i) = neinf;
		tmnr(i) = inf;
		clgr(i) = mxr(i) = cmxr(i) = tqlr(i) = sumr(i) = 0;
		++cnt;
		if (l == r) return;
		if (l <= mid)
			build((*(ls + i) = cnt + 1), l, mid);
		if (r > mid)
			build((*(rs + i) = cnt + 1), mid + 1, r);
		pushup(i);
	}
	void add(int i, int l, int r, int lt, int rt, int v)
	{
		if (lt > rt || !clgr(i)) return;
		if (l >= lt && r <= rt)
		{
			tagplus(i, l, r, v);
			return;
		}
		pushdown(i, l, r);
		if (mid >= lt)
			add(ls[i], l, mid, lt, rt, v);
		if (mid < rt)
			add(rs[i], mid + 1, r, lt, rt, v);
		pushup(i);
	}
	void modify(int i, int l, int r, int p, int v)
	{
		if (l == r)
		{
			mxr(i) = sumr(i) = v;
			cmxr(i) = clgr(i) = 1;
			return;
		}
		pushdown(i, l, r);
		if (mid >= p)
			modify(ls[i], l, mid, p, v);
		if (mid < p)
			modify(rs[i], mid + 1, r, p, v);
		pushup(i);
	}
	void mmin(int i, int l, int r, int lt, int rt, int v)
	{
		if (lt > rt || !clgr(i)) return;
		if (v >= mxr(i)) return;
		if (l >= lt && r <= rt && v > smxr(i))
		{
			tagmin(i, v); return;
		}
		pushdown(i, l, r);
		if (mid >= lt)
			mmin(ls[i], l, mid, lt, rt, v);
		if (mid < rt)
			mmin(rs[i], mid + 1, r, lt, rt, v);
		pushup(i);
	}
}

namespace SGTP
{
	struct node
	{
		int __v1, __v2;
	} tp[siz + 5];
	int ls[siz + 5], rs[siz + 5], cnt;
	il void pushup(int i)
	{
		reg int sl = *(ls + i), sr = *(rs + i);
		sump(i) = sump(sl) + sump(sr);
	}
	void build(int i, int l, int r)
	{
		tagp(i) = sump(i) = 0;
		++cnt;
		if (l == r)
			return;
		if (l <= mid)
			build((*(ls + i) = cnt + 1), l, mid);
		if (r > mid)
			build((*(rs + i) = cnt + 1), mid + 1, r);
		pushup(i);
	}
	void add(int i, int l, int r, int lt, int rt, int v)
	{
		if (l >= lt && r <= rt) { tagp(i) += v; return; }
		if (mid >= lt)
			add(ls[i], l, mid, lt, rt, v);
		if (mid < rt)
			add(rs[i], mid + 1, r, lt, rt, v);
		pushup(i);
	}
	int query(int i, int l, int r, int p)
	{
		if (l == r) { return sump(i) + tagp(i); }
		if (mid >= p)
			return query(ls[i], l, mid, p) + tagp(i);
		if (mid < p)
			return query(rs[i], mid + 1, r, p) + tagp(i);
		return 0;
	}
}

int main()
{
	n = rd();
	SGTL::build(1, 1, n);
	SGTR::build(1, 1, n);
	SGTP::build(1, 1, n);
	SGTP::add(1, 1, n, 1, n, 1);
	for (int i = 1; i <= n; ++i) a[i] = rd(), rf[a[i]] = i;
	for (int i = 1; i <= n; ++i)
	{
		reg int rfc = *(rf + i), pos;
		SGTP::add(1, 1, n, rfc + 1, n, 1);
		pos = SGTP::query(1, 1, n, rfc);
		SGTL::modify(1, 1, n, rfc, 1);
		SGTR::modify(1, 1, n, rfc, i);
		SGTR::mmin(1, 1, n, 1, rfc - 1, pos - 1);
		SGTL::add(1, 1, n, rfc + 1, n, 1);
		SGTR::add(1, 1, n, rfc + 1, n, 1);
		SGTL::mmax(1, 1, n, rfc + 1, n, pos + 1);
		prt(sumr(1) - suml(1) + i, '\n');
	}
}
```

特别提醒：宏定义属于预处理语句，它**不区分 `namespace` **，无视生命域。`SGTL::sum(balabala)` 之类的都是会 `CE` 的。

~~话说为啥 Dev-C++ 的 AStyle 不会调整宏定义的格式啊。~~

---

## 作者：Purslane (赞：2)

# Solution

势能线段树模板题。`*3300` 评紫也有点极端了。（可能是因为势能线段树在 CHN 比较典？）

显然对于每个点，他在笛卡尔树上的子树对应原序列的一个区间。所以我们只需要找到对于每个数，它的右边第一个比他大的数的位置和左边第一个比他大的数的位置，求区间长度即可。（具体的，这个数在 $pos$，两个分别为 $lpos$ 和 $rpos$，答案就是 $rpos-pos$ 和 $pos-lpos-1$，后者可以通过翻转套用前者的代码）。

考虑动态加点维护 $rpos$（注意这个是在 $1$ 到 $i$ 意义下的）。假设 $i$ 在 $p$（原序列），在目前的序列排名为 $t$，则：

- 对于所有的 $1 \le j < p$，$rpos_j$ 对 $t$ 取 $\min$；

- $rpos_p$ 赋值为 $i+1$；

- $p < j \le n$，$rpos_j$ 加一。

注意一切的前提都是 $j$ 处有值。

使用势能线段树即可。




```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=150000+10;
int n,a[MAXN],ans[MAXN],rev[MAXN];
struct TAG {int mtag,otag;}tag[MAXN<<2];
struct Node {int mx,smx,sum,mxcnt,ocnt,tangcnt;}t[MAXN<<2];
int calc_smx(int a,int b,int c,int d) {if(a==c) return max(b,d);if(a>c) return max(c,b);if(c>a) return max(d,a);}
Node operator +(Node A,Node B) {return {max(A.mx,B.mx),calc_smx(A.mx,A.smx,B.mx,B.smx),A.sum+B.sum,A.mxcnt*(A.mx>=B.mx)+B.mxcnt*(B.mx>=A.mx),A.mxcnt+B.mxcnt+A.ocnt+B.ocnt-A.mxcnt*(A.mx>=B.mx)-B.mxcnt*(B.mx>=A.mx),A.tangcnt+B.tangcnt};}
Node operator +(Node A,TAG B) {return {A.mx+B.mtag,A.smx+B.otag,A.sum+A.mxcnt*B.mtag+A.ocnt*B.otag-(A.mxcnt+A.ocnt-A.tangcnt)*B.otag,A.mxcnt,A.ocnt,A.tangcnt};}
TAG operator +(TAG A,TAG B) {return {A.mtag+B.mtag,A.otag+B.otag};}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {
	if(t[lson].mx==t[rson].mx) t[lson]=t[lson]+tag[k],t[rson]=t[rson]+tag[k],tag[lson]=tag[lson]+tag[k],tag[rson]=tag[rson]+tag[k];
	else if(t[lson].mx>t[rson].mx) t[lson]=t[lson]+tag[k],tag[lson]=tag[lson]+tag[k],tag[k].mtag=tag[k].otag,t[rson]=t[rson]+tag[k],tag[rson]=tag[rson]+tag[k];
	else t[rson]=t[rson]+tag[k],tag[rson]=tag[rson]+tag[k],tag[k].mtag=tag[k].otag,t[lson]=t[lson]+tag[k],tag[lson]=tag[lson]+tag[k];
	return tag[k]={0,0},void();
}
void update(int k,int l,int r,int x,int y,int v) {
	if(x<=l&&r<=y) return t[k]=t[k]+(TAG){v,v},tag[k]=tag[k]+(TAG){v,v},void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,v);
	if(y>mid) update(rson,mid+1,r,x,y,v);
	return t[k]=t[lson]+t[rson],void();
}
void check_min(int k,int l,int r,int x,int y,int v) {
	if(t[k].mx<=v) return ;
	if(x<=l&&r<=y) {
		TAG tg={v-t[k].mx,0};
		if(t[k].smx<v) return t[k]=t[k]+tg,tag[k]=tag[k]+tg,void();
		push_down(k,l,r);
		check_min(lson,l,mid,x,y,v),check_min(rson,mid+1,r,x,y,v);
		return t[k]=t[lson]+t[rson],void();
	}
	push_down(k,l,r);
	if(x<=mid) check_min(lson,l,mid,x,y,v);
	if(y>mid) check_min(rson,mid+1,r,x,y,v);
	return t[k]=t[lson]+t[rson],void();
}
void build(int k,int l,int r) {
	if(l==r) return t[k]={-0x3f3f3f3f,-0x3f3f3f3f,0,1,0,0},tag[k]={0,0},void();
	build(lson,l,mid),build(rson,mid+1,r),tag[k]={0,0};
	return t[k]=t[lson]+t[rson],void();	
}
int query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k].sum;
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return query(lson,l,mid,x,y)+query(rson,mid+1,r,x,y);
}
void modify(int k,int l,int r,int pos,int v) {
	if(l==r) return t[k]={v,-0x3f3f3f3f,v,1,0,1},void();
	push_down(k,l,r);
	if(pos<=mid) modify(lson,l,mid,pos,v);
	else modify(rson,mid+1,r,pos,v);
	return t[k]=t[lson]+t[rson],void();	
}
int tr[MAXN];
void mzx_update(int pos,int v) {while(pos<=n) tr[pos]+=v,pos+=pos&-pos;return ;}
int mzx_query(int pos) {int ans=0;while(pos) ans+=tr[pos],pos-=pos&-pos;return ans;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i],rev[a[i]]=i;
	build(1,1,n); memset(tr,0,sizeof(tr));
	int tans=0;
	ffor(i,1,n) {
		mzx_update(rev[i],1);
		int p=rev[i],rank=mzx_query(p);
		if(p>1) check_min(1,1,n,1,p-1,rank);
		modify(1,1,n,p,i+1);
		if(p<n) update(1,1,n,p+1,n,1);
		ans[i]+=t[1].sum-(i+1)*(i+2)/2+1;
	}
	build(1,1,n),memset(tr,0,sizeof(tr));
	ffor(i,1,n) {
		mzx_update(n-rev[i]+1,1);
		int p=n-rev[i]+1,rank=mzx_query(p);
		if(p>1) check_min(1,1,n,1,p-1,rank);
		modify(1,1,n,p,i+1);
		if(p<n) update(1,1,n,p+1,n,1);
		ans[i]+=t[1].sum-i*(i+1)/2;
	}
	ffor(i,1,n) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：roger_yrj (赞：2)

我们设 $l_i,r_i$ 为 $a_i$ 左边/右边第一个比它大的位置。通过笛卡尔树的性质，我们不难发现以 $i$ 为根的子树大小为 $r_i-l_i-1$。

所以题目就变成求 $\sum_{a_i\le x} r_i-l_i-1=(\sum_{a_i\le x} r_i)-(\sum_{a_i\le x} l_i)-i$。我们把 $l$ 和 $r$ 分开求。由于求 $l$ 和 $r$ 的方法是对称的，所以我们只讨论求 $r$ 的方法。

我们从小到大插入每个点，观察新序列与原序列有什么变化。
假设从位置 $x$ 插入。

- 由于是从小到大插入的，所以 $x$ 比在场所有数都大，所以 $x$ 左边的位置的 $r$ 要对 $x$ 取 $\min$。即 $i<x,r_i=\min(r_i,x)$。
- 由于 $x$ 比在场所有数都大，场上一共有 $x$ 个数，所以 $r_x=x+1$。
- 对于 $x$ 右边的位置的 $r$，$x$ 的插入对它的影响只有位置右移了一位，即$i>x,r_i=r_i+1$。

所以，我们需要一个数据结构，支持：

- 区间取 $\min$。
- 单点修改。
- 区间加。
- 查询全局和。

这里我们使用**吉老师线段树**来实现。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls (k<<1)
#define rs (k<<1|1)
using namespace std;
const int N=6e5+10,INF=1145141919;
int n,m,a[N],b[N];
ll sum[N],ans[N];
int maxx[N],se[N],L[N],R[N],cnt[N],cnt2[N];
int tag1[N],tag2[N];//tag1:最大值,tag2:非最大值 
void push_up(int k){
	sum[k]=sum[ls]+sum[rs];
	maxx[k]=max(maxx[ls],maxx[rs]);
	cnt2[k]=cnt2[ls]+cnt2[rs];
	if(maxx[ls]==maxx[rs]){
		se[k]=max(se[ls],se[rs]);
		cnt[k]=cnt[ls]+cnt[rs];
	}else if(maxx[ls]>maxx[rs]){
		se[k]=max(se[ls],maxx[rs]);
		cnt[k]=cnt[ls];
		cnt2[k]+=cnt[rs];
	}else{
		se[k]=max(maxx[ls],se[rs]);
		cnt[k]=cnt[rs];
		cnt2[k]+=cnt[ls];
	}
}
void down(int x1,int x2,int k){
	sum[k]+=1ll*x1*cnt[k]+1ll*x2*cnt2[k];
	if(maxx[k])maxx[k]+=x1;
	if(se[k])se[k]+=x2;
	tag1[k]+=x1,tag2[k]+=x2;
}
void push_down(int k){
	int maxn=max(maxx[ls],maxx[rs]); 
	if(maxx[ls]==maxn)down(tag1[k],tag2[k],ls);
	else down(tag2[k],tag2[k],ls);
	if(maxx[rs]==maxn)down(tag1[k],tag2[k],rs);
	else down(tag2[k],tag2[k],rs);
	tag1[k]=tag2[k]=0;
}
void build(int l,int r,int k){
	L[k]=l,R[k]=r;
	if(l==r){
		cnt[k]=cnt2[k]=maxx[k]=se[k]=sum[k]=tag1[k]=tag2[k]=0;
		return;
	}
	int mid=l+r>>1;
	build(l,mid,ls);
	build(mid+1,r,rs);
	push_up(k);
}
ll query_cnt(int l,int r,int k){
	if(r<L[k]||R[k]<l)return 0;
	if(l<=L[k]&&R[k]<=r)return cnt[k]+cnt2[k];
	push_down(k);
	return query_cnt(l,r,ls)+query_cnt(l,r,rs);
}
ll query_sum(int l,int r,int k){
	if(r<L[k]||R[k]<l)return 0;
	if(l<=L[k]&&R[k]<=r)return sum[k];
	push_down(k);
	return query_sum(l,r,ls)+query_sum(l,r,rs);
}
void updata_add(int l,int r,int k,int x){
	if(r<L[k]||R[k]<l)return;
	if(l<=L[k]&&R[k]<=r){
		sum[k]+=1ll*x*(cnt[k]+cnt2[k]);
		if(maxx[k])maxx[k]+=x;
		if(se[k])se[k]+=x;
		tag1[k]+=x,tag2[k]+=x;
		return;
	}
	push_down(k);
	updata_add(l,r,ls,x);
	updata_add(l,r,rs,x);
	push_up(k);
}
void updata_min(int l,int r,int k,int x){
	if(r<L[k]||R[k]<l||x>=maxx[k])return;
	if(l<=L[k]&&R[k]<=r&&x>se[k]){
		sum[k]-=1ll*cnt[k]*(maxx[k]-x);
		tag1[k]-=maxx[k]-x;
		maxx[k]=x;
		return;
	}
	push_down(k);
	updata_min(l,r,ls,x);
	updata_min(l,r,rs,x);
	push_up(k);
}
void modify(int x,int k,int y){
	if(x<L[k]||R[k]<x)return;
	if(L[k]==R[k]){
		sum[k]=maxx[k]=y;
		cnt[k]=1;
		cnt2[k]=se[k]=tag1[k]=tag2[k]=0;
		return;
	}
	push_down(k);
	modify(x,ls,y);
	modify(x,rs,y);
	push_up(k);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[a[i]]=i;
	build(1,n,1);
	for(int i=1;i<=n;i++){
		modify(b[i],1,i+1);
		if(b[i]+1<=n)updata_add(b[i]+1,n,1,1);
		if(b[i]-1>=1)updata_min(1,b[i]-1,1,query_cnt(1,b[i],1));
		ans[i]=query_sum(1,n,1);
	}
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++)b[a[i]]=i;
	build(1,n,1);
	for(int i=1;i<=n;i++){
		modify(b[i],1,i+1);
		if(b[i]+1<=n)updata_add(b[i]+1,n,1,1);
		if(b[i]-1>=1)updata_min(1,b[i]-1,1,query_cnt(1,b[i],1));
		ans[i]-=1ll*i*(i+1)-query_sum(1,n,1)+i;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
	return 0; 
}
```

---

## 作者：Purple_wzy (赞：2)

[题面](https://www.luogu.com.cn/problem/CF1290E)

[英文题面](http://codeforces.com/problemset/problem/1290/E)

题意：

![](https://img2020.cnblogs.com/blog/1564093/202007/1564093-20200715221620018-764330244.png)

笛卡尔树是一种既满足堆的性质，又满足二叉搜索树的性质的树。可以发现的是，对于一个排列，它的笛卡尔树是唯一的。

$n \leq 2\times 10^5$。

题解：发现笛卡尔树中的一个节点的权值可以表示为$r_i-l_i+1$的形式。其中$r_i$表示最小的$p \geq i$，使得$a_{p+1}>a_i$。所以我们可以分别维护$l_i$和$r_i$。

考虑加入一个权值最大的点后，$r_i$和$l_i$会出现哪些变化。设当前插入的是数字$i$，它在排列中的位置是$p$，它在当前的由1到$i$组成的子序列中的位置为$q$。

- 对于$\forall_{k<p}$，$r_k=min(r_k,q-1)$；
- 对于$p$，$l_p=1,r_p=i$。
- 对于$\forall_{k>p},l_k++,r_k++,l_k=max(l_k,q+1)$。

所以相当于是区间取min，区间加和单点赋值。我们可以采用势能线段树的思想，维护：

- 区间和；
- 最大（小）值；
- 最大（小）值出现次数；
- 次大（小）值；
- 区间合法点个数；
- 加法标记和赋值标记。

对于区间取min操作，我们递归到一个区间，其最大值小于$w$，次大值大于等于$w$时进行修改，否则继续递归子树。

不会势能线段树区间取min复杂度证明的可以出门右转自行百度。

注意pushup和pushdown各要分三种情况讨论，还要注意标记的下传顺序问题。

时间复杂度：$O(nlog^2n)$。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
const int INF=1e9+7;
int n,m,a[202000],p[202000],t[202000];
IN lbt(int x){return x&(-x);}
I modi(int x,int w){while(x<=n)t[x]+=w,x+=lbt(x);}
IN ques(int x){re res=0;while(x)res+=t[x],x-=lbt(x);return res;}
#define all 1,1,n
#define lt k<<1,l,mid
#define rt k<<1|1,mid+1,r
ll sr[1606000],sl[1606000];int cntr[1606000],cntl[1606000];
int mxr[1606000],mxl[1606000],smxr[1606000],smxl[1606000],cmxr[1606000],cmxl[1606000],snl[1606000],snr[1606000];
int lazr[1606000],lazl[1606000],lmr[1606000],lml[1606000];
I build(int k,int l,int r){
	sl[k]=sr[k]=cntr[k]=cntl[k]=cmxr[k]=cmxl[k]=lazr[k]=lazl[k]=lmr[k]=lml[k]=0;
	mxr[k]=smxr[k]=-INF;mxl[k]=smxl[k]=INF;
	if(l==r)return;
	re mid=(l+r)>>1;
	build(lt);build(rt);
}
I push_upl(int k){
	sl[k]=sl[k<<1]+sl[k<<1|1];cntl[k]=cntl[k<<1]+cntl[k<<1|1];
	if(mxl[k<<1]<mxl[k<<1|1]){
		snl[k]=1;
		mxl[k]=mxl[k<<1];cmxl[k]=cmxl[k<<1];smxl[k]=min(smxl[k<<1],mxl[k<<1|1]);
	}
	else if(mxl[k<<1]>mxl[k<<1|1]){
		snl[k]=2;
		mxl[k]=mxl[k<<1|1];cmxl[k]=cmxl[k<<1|1];smxl[k]=min(smxl[k<<1|1],mxl[k<<1]);
	}
	else{
		snl[k]=3;
		mxl[k]=mxl[k<<1];cmxl[k]=cmxl[k<<1]+cmxl[k<<1|1];smxl[k]=min(smxl[k<<1],smxl[k<<1|1]);
	}
}
I push_upr(int k){
	sr[k]=sr[k<<1]+sr[k<<1|1];cntr[k]=cntr[k<<1]+cntr[k<<1|1];
	if(mxr[k<<1]>mxr[k<<1|1]){
		snr[k]=1;
		mxr[k]=mxr[k<<1];cmxr[k]=cmxr[k<<1];smxr[k]=max(smxr[k<<1],mxr[k<<1|1]);
	}
	else if(mxr[k<<1]<mxr[k<<1|1]){
		snr[k]=2;
		mxr[k]=mxr[k<<1|1];cmxr[k]=cmxr[k<<1|1];smxr[k]=max(smxr[k<<1|1],mxr[k<<1]);
	}
	else{
		snr[k]=3;
		mxr[k]=mxr[k<<1];cmxr[k]=cmxr[k<<1]+cmxr[k<<1|1];smxr[k]=max(smxr[k<<1],smxr[k<<1|1]);
	}
}
I add_l(int k,int w){
	sl[k]+=(ll)cntl[k]*w;if(mxl[k]!=INF)mxl[k]+=w;if(smxl[k]!=INF)smxl[k]+=w;lazl[k]+=w;
}
I maxl(int k,int w){
	if(lazl[k]){
		add_l(k<<1,lazl[k]);add_l(k<<1|1,lazl[k]);lazl[k]=0;
	}
	sl[k]+=(ll)cmxl[k]*(w-mxl[k]);mxl[k]=cmxl[k]?w:INF;lml[k]=w;
}
I push_downl(int k){
	if(lml[k]){
		if(snl[k]^2)maxl(k<<1,lml[k]);
		if(snl[k]^1)maxl(k<<1|1,lml[k]);
		lml[k]=0;
	}
	if(lazl[k]){
		add_l(k<<1,lazl[k]);add_l(k<<1|1,lazl[k]);lazl[k]=0;
	}
}
I add_r(int k,int w){
	sr[k]+=(ll)cntr[k]*w;if(mxr[k]!=-INF)mxr[k]+=w;if(smxr[k]!=-INF)smxr[k]+=w;lazr[k]+=w;
}
I minr(int k,int w){
	if(lazr[k]){
		add_r(k<<1,lazr[k]);add_r(k<<1|1,lazr[k]);lazr[k]=0;
	}
	sr[k]+=(ll)cmxr[k]*(w-mxr[k]);mxr[k]=cmxr[k]?w:-INF;lmr[k]=w;
}
I push_downr(int k){
	if(lmr[k]){
		if(snr[k]^2)minr(k<<1,lmr[k]);
		if(snr[k]^1)minr(k<<1|1,lmr[k]);
		lmr[k]=0;
	}
	if(lazr[k]){
		add_r(k<<1,lazr[k]);add_r(k<<1|1,lazr[k]);lazr[k]=0;
	}
}
I modi_l(int k,int l,int r,int x,int w){
	if(l==r){
		sl[k]=mxl[k]=w;smxl[k]=INF;cmxl[k]=cntl[k]=1;
		return;
	}
	push_downl(k);
	re mid=(l+r)>>1;
	if(x<=mid)modi_l(lt,x,w);
	else modi_l(rt,x,w);
	push_upl(k);
}
I modi_r(int k,int l,int r,int x,int w){
	if(l==r){
		sr[k]=mxr[k]=w;smxr[k]=-INF;cmxr[k]=cntr[k]=1;
		return;
	}
	push_downr(k);
	re mid=(l+r)>>1;
	if(x<=mid)modi_r(lt,x,w);
	else modi_r(rt,x,w);
	push_upr(k);
}
I revi_l(int k,int l,int r,int x,int y,int w){
	if(x>r||y<l||!cntl[k])return;
	if(x<=l&&r<=y)return add_l(k,w),void();
	push_downl(k);
	re mid=(l+r)>>1;
	revi_l(lt,x,y,w);revi_l(rt,x,y,w);
	push_upl(k);
}
I revi_r(int k,int l,int r,int x,int y,int w){
	if(x>r||y<l||!cntr[k])return;
	if(x<=l&&r<=y)return add_r(k,w),void();
	push_downr(k);
	re mid=(l+r)>>1;
	revi_r(lt,x,y,w);revi_r(rt,x,y,w);
	push_upr(k);
}
I fill_max(int k,int l,int r,int x,int y,int w){
	if(x>r||y<l||!cntl[k]||mxl[k]>=w)return;
	if(x<=l&&r<=y){
		if(smxl[k]>=w){
//			cout<<"#"<<l<<" "<<r<<" "<<w<<endl;
			return maxl(k,w),void();
		}
		push_downl(k);
		re mid=(l+r)>>1;
		fill_max(lt,x,y,w);fill_max(rt,x,y,w);
		return push_upl(k),void();
	}
	push_downl(k);
	re mid=(l+r)>>1;
	fill_max(lt,x,y,w);fill_max(rt,x,y,w);
	push_upl(k);
}
I fill_min(int k,int l,int r,int x,int y,int w){
	if(x>r||y<l||!cntr[k]||mxr[k]<=w)return;
	if(x<=l&&r<=y){
		if(smxr[k]<=w){
//			cout<<"@"<<l<<" "<<r<<" "<<w<<endl;
			return minr(k,w),void();
		}
		push_downr(k);
		re mid=(l+r)>>1;
		fill_min(lt,x,y,w);fill_min(rt,x,y,w);
		return push_upr(k),void();
	}
	push_downr(k);
	re mid=(l+r)>>1;
	fill_min(lt,x,y,w);fill_min(rt,x,y,w);
	push_upr(k);
}
I getit(int k,int l,int r){
	cout<<"!"<<k<<" "<<l<<" "<<r<<" "<<sl[k]<<" "<<sr[k]<<" "<<mxl[k]<<" "<<mxr[k]<<" "<<smxl[k]<<" "<<smxr[k]<<" "<<cmxl[k]<<" "<<cmxr[k]<<endl;
	if(l==r)return ;//cout<<k<<" "<<l<<" "<<r<<" "<<sl[k]<<" "<<sr[k]<<endl,void();
	push_downl(k);push_downr(k);
	re mid=(l+r)>>1;
	getit(lt);getit(rt);
}
int main(){
//	freopen("a.out","w",stdout);
	read(n);F(i,1,n)read(a[i]),p[a[i]]=i;build(all);
	F(i,1,n){
		modi_l(all,p[i],1),modi_r(all,p[i],i);
		m=ques(p[i])+1;modi(p[i],1);revi_l(all,p[i]+1,n,1);revi_r(all,p[i]+1,n,1);
		fill_max(all,p[i]+1,n,m+1);fill_min(all,1,p[i]-1,m-1);
		printf("%lld\n",sr[1]-sl[1]+i);
//		getit(all);
	}
	return 0;
}
/*
5
2 4 1 5 3
6
1 2 4 5 6 3
10
8 10 9 3 7 5 4 6 2 1
15
1 7 12 14 15 9 8 10 11 2 5 4 3 13 6
*/

```

---

## 作者：eee_hoho (赞：0)

很套路的一道题。

先考虑对于一棵笛卡尔树如何求出所有子树大小，我们用单调栈建树的过程中是发现一个比当前栈顶元素大的数就弹栈，作为他的父亲，那么设 $pre_i$ 表示第一个向左比 $a_i$ 大的数的位置， $nxt_i$ 表示向右第一个比 $a_i$ 大的位置，那么 $i$ 的子树大小是 $nxt_i-pre_i-1$ 。

然后就可以分开考虑 $nxt$ 和 $pre$ 了，考虑求 $pre$ ，我们从小到大枚举 $k$ ，每次插入 $k$ ，设 $k$ 的位置是 $pos_k$ ，那么 $[1,pos_k-1]$ 的数的 $nxt$ 可能会改变，需要和 $pos_k'$ 取min（ $pos_k'$ 是 $k$ 在新序列的位置），而 $k$ 的加入使 $[pos_k+1,n]$ 的数的位置加 $1$ ，所以 $nxt$ 要加 $1$ 。

这个东西可以用吉司机线段树来维护，至于插入数，我们多维护出这个区间有多少个数插入了就可以了。

对于 $pre$ ，直接把序列翻转，那么我们求的 $\sum pre$ 就变成了 $\sum i-pre+1$ ， $i$ 是序列元素个数，最后把多算的减掉就好了。

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N = 2e5;
const int inf = 1e9;
using namespace std;
int n,a[N + 5],pos[N + 5],s[N + 5];
long long ans[N + 5];
struct node
{
    int mx,mxi,smx,s;
    long long sm;
    node operator +(const node &a)const
    {
        node c = {0,0,0,0,0};
        c.sm = sm + a.sm;
        c.s = s + a.s;
        if (mx > a.mx)
        {
            c.mx = mx;
            c.smx = smx;
            c.mxi = max(a.mx,mxi);
        }
        if (mx < a.mx)
        {
            c.mx = a.mx;
            c.smx = a.smx;
            c.mxi = max(a.mxi,mx);
        }
        if (mx == a.mx)
        {
            c.mx = mx;
            c.smx = a.smx + smx;
            c.mxi = max(a.mxi,mxi);
        }
        return c;
    }
};
struct Seg
{
    node s[N * 4 + 5];
    int tag[N * 4 + 5],ct[N * 4 + 5];
    #define zrt k << 1
    #define yrt k << 1 | 1
    void build(int k,int l,int r)
    {
        s[k] = {0,-inf,0,0,0};tag[k] = 0;ct[k] = inf;
        if (l == r)
            return;
        int mid = l + r >> 1;
        build(zrt,l,mid);
        build(yrt,mid + 1,r);
    }
    void add(int k,int l,int r,int z)
    {
        if (!s[k].s)
            return;
        s[k].sm += 1ll * s[k].s * z;
        s[k].mx += z;
        if (s[k].mxi != -inf)
            s[k].mxi += z;
        tag[k] += z;
        if (ct[k] != inf)
            ct[k] += z;
    }
    void cha(int k,int z)
    {
        if (!s[k].s)
            return;
        if (z >= s[k].mx)
            return;
        s[k].sm -= 1ll * s[k].smx * (s[k].mx - z);
        s[k].mx = z;
        ct[k] = z;
    }
    void pushdown(int k,int l,int r,int mid)
    {
        if (tag[k])
        {
            add(zrt,l,mid,tag[k]);
            add(yrt,mid + 1,r,tag[k]);
            tag[k] = 0;
        }
        if (ct[k] != inf)
        {
            cha(zrt,ct[k]);
            cha(yrt,ct[k]);
            ct[k] = inf;
        }
    }
    void insert(int k,int l,int r,int x,int z)
    {
        if (l == r)
        {
            s[k] = (node){z,-inf,1,1,z};
            return;
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x <= mid)
            insert(zrt,l,mid,x,z);
        else
            insert(yrt,mid + 1,r,x,z);
        s[k] = s[zrt] + s[yrt];
    }
    void modify(int k,int l,int r,int x,int y,int z)
    {
        if (l >= x && r <= y)
        {
            add(k,l,r,z);
            return;
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x <= mid)
            modify(zrt,l,mid,x,y,z);
        if (y > mid)
            modify(yrt,mid + 1,r,x,y,z);
        s[k] = s[zrt] + s[yrt];
    }
    void getmin(int k,int l,int r,int x,int y,int z)
    {
        if (l >= x && r <= y)
        {
            if (z > s[k].mxi)
            {
                cha(k,z);
                return;
            }
        }
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (x <= mid)
            getmin(zrt,l,mid,x,y,z);
        if (y > mid)
            getmin(yrt,mid + 1,r,x,y,z);
        s[k] = s[zrt] + s[yrt];
    }
    int query(int k,int l,int r,int x,int y)
    {
        if (l >= x && r <= y)
            return s[k].s;
        int mid = l + r >> 1;
        pushdown(k,l,r,mid);
        if (y <= mid)
            return query(zrt,l,mid,x,y);
        if (x > mid)
            return query(yrt,mid + 1,r,x,y);
        return query(zrt,l,mid,x,y) + query(yrt,mid + 1,r,x,y);
    }
}tree;
void solve()
{
    for (int i = 1;i <= n;i++)
        pos[a[i]] = i;
    tree.build(1,1,n);
    memset(s,0,sizeof(s));
    for (int k = 1;k <= n;k++)
    {
        if (pos[k] + 1 <= n)
            tree.modify(1,1,n,pos[k] + 1,n,1);
        if (pos[k] - 1 >= 1)
        {
            int x = tree.query(1,1,n,1,pos[k] - 1) + 1;
            tree.getmin(1,1,n,1,pos[k] - 1,x);
        }
        tree.insert(1,1,n,pos[k],k + 1);
        ans[k] += tree.s[1].sm;
    }
}
int main()
{
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
        scanf("%d",&a[i]);
    solve();
    reverse(a + 1,a + n + 1);
    solve();
    for (int i = 1;i <= n;i++)
        printf("%lld\n",ans[i] - 1ll * i * (i + 2));
    return 0;
}
```

---

## 作者：Anita_Hailey (赞：0)

# CF1290E Solution

## 前言

这道题你需要的前置知识

- 树状数组
- 吉司机线段树的基本操作

## 正文

**题意翻译**：给你一个 $1$ 至 $n$ 的排列，每次找出其中不大于 $i$ 的数字，相对位置不变成为一个新的序列，在这个新的序列上建一棵大根笛卡尔树，求这个笛卡尔树的每个结点为根的子树的 `size` 之和

暴力思想 每次 $O(n)$ 建笛卡尔树，然后 $O(n)$ 的 dfs 即可。总复杂度 $O(n^2)$

不难发现一个事情，在我们建这个笛卡尔树的时候，这个序列是 $1$ 至 $i$ 的一个排列。其中每个结点的子树他们的编号必定是一个连续的区间，这是因为笛卡尔树满足二叉排序树的性质。

我们记 $r_i$ 为以编号为 $i$ 的结点的子树里的结点的最大编号，同样我们可以定义 $l_i$。那么每个子树的 `size` 即为 $r_i-l_i+1$

我们只要求出来 $\sum_{a_j\le i}r_i-l_i+1$ 并动态维护他。

考虑现在已经计算了 $1$ 至 $i-1$ 即可。考虑添加一个结点，他的值是 $i$，这个接待你的编号是 $p$，在已经添加的序列里是第 $q$ 个。

- $1\le j <p$ 的结点，**如果在序列里**，$r_i=\min(r_i,q-1)$
- $j=p$ 的结点，$l_i=1,r_i=i$
- $p< j \le n$ 的结点，**如果在序列里**，$l_i++,r_i++,l_i=\max(l_i,q+1)$

这样子的话，我们只要每次查询整体序列和即可。

如何判断是否在序列里，我们可以给每个结点打一个 $flag$，表示这个区间里有多少个有用节点，为 $0$ 直接返回即可，否则我们可以继续递归。

综上，我们需要完成几个操作：

1. 查询上文所述的 $p, q$，这个可以通过映射和树状数组完成。
2. 吉司机线段树支持如下操作

- 区间加
- 区间和查询
- 区间 $\min$ / $\max$
- 单点赋值

需要注意的是，我们可以分别维护 $l$ 和 $r$，这样子需要写两棵线段树，一棵维护 $l$ ，支持区间 $\max$；一棵维护 $r$，支持区间 $\min$，尽管有不同，但是仅有细小差别。

具体实现可以见[代码](https://paste.ubuntu.com/p/f7r6jhq8tV/)



---

## 作者：Fuyuki (赞：0)

## Description

给定一个排列 $a$，将由 $a_i\leq k$ 的项构成的子序列构成的笛卡尔树的子树大小和记为 $f(k)$，求 $\sum_{k=1}^{n}f(k)$。

这里的笛卡尔树是大根堆的结构。

$n\leq 1.5\times 10^5$

## Solution

可以看做将 $a_i=1,2,...,n$ 依次插入到序列中，动态地维护笛卡尔树。

直接维护笛卡尔树的就相当于做非旋 $\text{Treap}$ 的 $\text{split}$ 操作，这依赖原树的高度不高——而这显然是不可能的。

笛卡尔树上的每个子树都对应一段联系的区间，子树大小就是这段区间包含的已经插入的点。假设以 $i$ 为根的子树区间为 $[L_i,R_i]$，那么将 $a_x=k$ 插入的时候就相当于进行了这样的操作：

$$R_i=\min\{R_i,x-1\}\ \ i<x $$

$$L_i=\max\{L_i,x+1\}\ \ i>x $$


这两个信息可以直接使用吉司机线段树进行维护，但是需要维护的是区间内的已插入点的个数，这就不能直接描述了。

记 $cnt_i$ 表示前缀 $i$ 中有多少个已插入的位置，那么可以使用 $\sum cnt_R-\sum cnt_{L-1}$ 来描述，对 $L,R$ 取 $\min,\max$ 也可以描述为对 $cnt_L,cnt_R$ 取 $\min,\max$。插入元素之后就相当于对后缀的 $cnt$ 都 $+1$。

可以拆解成独立的两个前后缀取 $\min,\max$，后缀加的问题，用吉司机线段树去维护是 $O(nlog^2n)$ 的。

实现方面，因为问题是对称的，所以可以只需要写一棵线段树。

如果是按照这种写法，就只有前缀取 $\min$，后缀加两种操作，这种情况下复杂度貌似可以摊到 $O(nlogn)$（我没摊出来）。

~~这个插入写得好丑啊~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I inline int
#define V inline void
#define B inline bool
#define ll long long int
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=15e4+1,INF=0x3f3f3f3f;
ll ans[N];
int n,a[N],b[N],c[N];
I lowbit(int x){return x&-x;}
V add(int x){while(x<=n)c[x]++,x+=lowbit(x);}
I ask(int x){return!x?0:(c[x]+ask(x^lowbit(x)));}
struct ele{
	struct node{
		int val,cnt;
		V set(int x,int y){val=x,cnt=y;}
		B operator<(const node&u)const{return val<u.val;}
		node operator+(const node&u)const{
			return(val==u.val)?(node){val,cnt+u.cnt}:max(*this,u);
		}
	}x,y;
	ll sum;int tag_max,tag_sum,siz;
	I val(){return x.val;}
	V add_max(int w){sum+=1ll*w*x.cnt,x.val+=w,tag_max+=w;}
	V add_sum(int w){
		sum+=1ll*w*siz,tag_sum+=w;
		if(x.cnt)x.val+=w;
		if(y.cnt)y.val+=w;
	}
	V clean(){sum=tag_max=tag_sum=siz=0,x.set(0,0),y.set(-INF,0);}
}t[N<<2];
#define lc p<<1
#define rc lc|1
#define root 1,1,n
#define lson lc,L,mid
#define rson rc,mid+1,R
#define tree int p,int L,int R
V upd(int p){
	t[p].sum=t[lc].sum+t[rc].sum,t[p].x=t[lc].x+t[rc].x;
	if(t[lc].val()==t[rc].val())t[p].y=t[lc].y+t[rc].y;
	else t[p].y=t[lc].y+t[rc].y+min(t[lc].x,t[rc].x);
}
V psd(int p){
	int tmp=max(t[lc].val(),t[rc].val());
	if(t[lc].val()==tmp)t[lc].add_max(t[p].tag_max);
	if(t[rc].val()==tmp)t[rc].add_max(t[p].tag_max);
	t[lc].add_sum(t[p].tag_sum),t[rc].add_sum(t[p].tag_sum);
	t[p].tag_max=t[p].tag_sum=0;
}
V input(){scanf("%d",&n);FOR(i,1,n)scanf("%d",a+i);}
V build(tree){
	t[p].clean();
	if(L==R)return;
	int mid=L+R>>1;
	build(lson),build(rson),upd(p);
}
V dfs(int p,int x){
	if(t[p].val()<=x)return;
	if(t[p].y.val<x)
		return t[p].add_max(x-t[p].val());
	psd(p),dfs(lc,x),dfs(rc,x),upd(p);
}
V modify(tree,int l,int r,int x){
	if(l==L&&R==r)return dfs(p,x);
	int mid=L+R>>1;psd(p);
	if(r<=mid)modify(lson,l,r,x);
	else if(l>mid)modify(rson,l,r,x);
	else modify(lson,l,mid,x),modify(rson,mid+1,r,x);
	upd(p);
}
V ins(tree,int l,int r,int x,int flag){
	t[p].siz+=flag;
	if(l==L&&R==r){
		if(flag)t[p].x.cnt=1;
		return t[p].add_sum(x);
	}
	int mid=L+R>>1;psd(p);
	if(r<=mid)ins(lson,l,r,x,flag);
	else if(l>mid)ins(rson,l,r,x,flag);
	else ins(lson,l,mid,x,flag),ins(rson,mid+1,r,x,flag);
	upd(p);
}
V init(){
	build(1,1,n),memset(c,0,n+1<<2);
	FOR(i,1,n)b[a[i]]=i;
}
V solve(){
	init();
	FOR(i,1,n){
		modify(root,1,b[i],ask(b[i])),ins(root,b[i],b[i],i-1,1);
		ins(root,b[i],n,1,0),add(b[i]),ans[i]+=t[1].sum;
	}
}
V work(){
	solve(),reverse(a+1,a+1+n),solve();
	FOR(i,1,n)cout<<ans[i]-1ll*i*i<<'\n';
}
int main(){
	input();
	work();
	return 0;
}
```


---

