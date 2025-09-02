# Julia the snail

## 题目描述

After hard work Igor decided to have some rest.

He decided to have a snail. He bought an aquarium with a slippery tree trunk in the center, and put a snail named Julia into the aquarium.

Igor noticed that sometimes Julia wants to climb onto the trunk, but can't do it because the trunk is too slippery. To help the snail Igor put some ropes on the tree, fixing the lower end of the $ i $ -th rope on the trunk on the height $ l_{i} $ above the ground, and the higher end on the height $ r_{i} $ above the ground.

For some reason no two ropes share the same position of the higher end, i.e. all $ r_{i} $ are distinct. Now Julia can move down at any place of the trunk, and also move up from the lower end of some rope to its higher end. Igor is proud of his work, and sometimes think about possible movements of the snail. Namely, he is interested in the following questions: «Suppose the snail is on the trunk at height $ x $ now. What is the highest position on the trunk the snail can get on if it would never be lower than $ x $ or higher than $ y $ ?» Please note that Julia can't move from a rope to the trunk before it reaches the higher end of the rope, and Igor is interested in the highest position on the tree trunk.

Igor is interested in many questions, and not always can answer them. Help him, write a program that answers these questions.

## 说明/提示

The picture of the first sample is on the left, the picture of the second sample is on the right. Ropes' colors are just for clarity, they don't mean anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793F/fd0920e125cd0c2131a4cdbb7a6c682c972642f8.png)

## 样例 #1

### 输入

```
8
4
1 2
3 4
2 5
6 7
5
1 2
1 4
1 6
2 7
6 8
```

### 输出

```
2
2
5
5
7
```

## 样例 #2

### 输入

```
10
10
3 7
1 4
1 6
5 5
1 1
3 9
7 8
1 2
3 3
7 10
10
2 4
1 7
3 4
3 5
2 8
2 5
5 5
3 5
7 7
3 10
```

### 输出

```
2
7
3
3
2
2
5
3
7
10
```

# 题解

## 作者：素质玩家孙1超 (赞：18)

题意 ：

有一只蜗牛在树干上爬，有两种移动方式，沿着某根绳子向上爬，或者顺着树干往下溜。

树干高度为 $n$，有 $m$ 根绳子，第 $i$ 条连接了高度 $l_i$ 至 $r_i$，保证 $r_i$ 互不相同。

有 $q$ 次询问，每次给出两个数 $L,R$ ，问蜗牛从高度 $L$ 开始爬，只考虑被包含在 $[L,R]$ 间的绳子（即若一条绳子的区间超出询问范围即不能使用），蜗牛能够爬到的最大高度。

$ 1≤n,m,q≤10^5$ ，输入均为正整数。

---

看到是区间的询问，而且区间对答案的限制挺大的，我一开始就想到了离线处理，对询问右端点排序，然后维护一下所有左端点的答案即可。


我们设 $a_i$ 为当前以 $i$ 为左端点的答案。

每次将 $r$ 右移可以维护绳子 $l,r$ 对答案的影响：

$$\large (l \leq a_i ) \  a_i=r  $$

即对 $(1,l)$ 中所有 $l \leq a_i$ 的 $a_i$ 改成 $r$。

这就是一个经典的 $\text{吉司机线段树}$ ，若不会可以去看[线段树3](https://www.luogu.com.cn/problem/P6242)或者[BZOJ4695最假女选手](https://www.baidu.com/s?ie=UTF-8&wd=BZOJ4695)。

复杂度是 $O(m \log n)$ 的，证明可以看 吉如一 神仙的16年集训队论文。

---


代码：

```cpp
#include <bits/stdc++.h>
#define fr first
#define sc second
#define pb push_back 
#define mp std::make_pair
#define mid (l + r >> 1)
#define ls (root << 1)
#define rs (root << 1 | 1)
using std::pair;
using std::vector;
inline int max(int a,int b){return a>b?a:b;}
const int Maxn = 1e5 + 5;
int n, m, Q, Ls[Maxn], ans[Maxn];
vector<pair<int, int> > q[Maxn];
int MAX[Maxn << 2], lst[Maxn << 2], TagA[Maxn << 2], TagB[Maxn << 2];
inline void Upd(int root, int x) {
    if (x > MAX[root])lst[root] = MAX[root], MAX[root] = x;
    else if (x < MAX[root] && x > lst[root])lst[root] = x;
}
inline void Pushup(int root) {
    MAX[root]=max(MAX[ls],MAX[rs]);
}
void Build(int root, int l, int r) {
    if (l == r) {
        MAX[root] = l;
    	return;
    }
    Build(ls, l, mid);
    Build(rs, mid + 1, r);
    Pushup(root);
}
inline void Addtag(int root, int A) {
    TagA[root]=max(TagA[root],A);
    MAX[root]=max(MAX[root],A);
}
inline void Pushdown(int root) {
    if (TagA[root])
	{
		Addtag(ls, TagA[root]);
		Addtag(rs, TagA[root]);
		TagA[root] = 0;
	}
}
void modify(int root, int l, int r, int L, int R, int A) {
    if (MAX[root] > A || l > R || r < L) return;
    if (L <= l && r <= R) return Addtag(root, A);
    Pushdown(root);
    modify(ls, l, mid, L, R, A);
    modify(rs, mid + 1, r, L, R, A);
    Pushup(root);
}
int Ask(int root, int l, int r, int pos) {
    if (l > pos || r < pos) return 0;
    if (l == r) return MAX[root];
    Pushdown(root);
    return Ask(ls, l, mid, pos) + Ask(rs, mid + 1, r, pos);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++) scanf("%d%d", &x, &y), Ls[x] = y;
    scanf("%d", &Q);
    for (int i = 1, x, y; i <= Q; i++) scanf("%d%d", &x, &y), q[x].pb(mp(y, i));
    Build(1, 1, n);
    for (int i(n); i >= 1; i--) {
        if (Ls[i]) modify(1, 1, n, Ls[i], i , i);
        for (int si = q[i].size(), j = 0; j < si; j++) ans[q[i][j].sc] = min(Ask(1, 1, n, q[i][j].fr));
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
}
```

另外我看到cf上$\rm{z \color{red}houyuyang}$神仙的提交是另一种线段树，他是按照询问左端点排序处理的，我水平不够暂时没有理解其做法，跑得比我写的这个快一些，但是我也不知道其真正的复杂度如何。

---

## 作者：比利♂海灵顿 (赞：15)

# 分块的做法

分块是 CF 的[官方题解](https://codeforces.com/blog/entry/51685)的思路。虽说是 $O(n\sqrt q)$ 的复杂度，但是很显然 $10^5$ 就是分块的数据范围。

当然，这篇题解可能和官方题解有不同，但是基本思路和复杂度是一样的，请放心食用。

## 题意

一个坐标轴上，有若干线段，可以从每条线段的左端走到线段右端，也可以在坐标轴上沿负方向移动。保证每条线段右端点互不相同。

每次询问给一个区间 $[L, R]$，求以 $L$ 为起点，全程不离开区间 $[L, R]$ 所能到达的最右位置。

坐标轴长度 $n$，线段数 $m$，询问数 $q$ 均满足 $\leq 10^5$。

## 分析

因为线段的右端点互不相同，所以可以用一个数组 $From_i$ 存储点 $i$ 做右端点时，对应线段的左端点。

## 暴力

询问 $[L, R]$ 时，维护一个以 $L$ 为左端点的 “Available 区间” $[L, i]$，表示当前这个区间内的所有点都能到达。一开始，Available 区间是 $[L, L]$。

从 $L + 1$ 到 $R$ 枚举指针 $j$，当 $From_j \in [L, i]$ 时， 将 $i$ 变成 $j$，继续上面的操作。最终，当 $j$ 枚举到 $R$ 时，这时的 $i$ 就是本次询问的答案。

为什么这样维护 Available 序列是正确的？当 $From_j \in [L, i]$ 时，可以从 Available 区间中的某个点走到 $j$。而从 $j$ 又可以合法地走到 $i$ 和路上的所有点。

## 分块

对坐标分块，设块长 $BlockLen$，块数 $BlockNum$。

新建一个数组 $f_{i, j}$，表示以 $i$ 为起点，以第 $j$ 块结尾 ($jBlockLen$) 为终点的查询结果。

这样每次查询时，可以 $O(1)$ 得到 $j = kBlockLen$ 时的 Available 区间为 $[L, f_{L, kBlockLen}]$。$k$ 的选取满足 $kBlockLen < R\leq (k + 1)BlockLen$ 只需要 $O(BlockLen)$ 即可。询问总复杂度 $O(qBlockLen)$。

## 预处理

为了优化常数，我们 $O(n)$ 处理一个数组 $Block_i$，表示 $i$ 所在块的编号。

处理一个数组 $g_{i, j}$，表示以 $i$ 为左端，右端在 $j$ 块以内的最大的线段右端点。

求 $g_{i, j}$ 需要利用 $g_{i, j}$ 的单调性，我们知道对于 $j_1 < j_2$，一定有 $g_{i, j_1} \leq g_{i, j_2}$，所以每次输入一个线段 $(l, r)$ 时，赋值 $g_{l, Block_r} = max(g_{l, Block_r}, r)$。

最后，正序扫描一遍 $g$ 数组，使 $g_{i, j} = max(g_{i, j}, g_{i, j - 1})$ 即可，复杂度 $O(\frac{n^2}{BlockLen} + m)$。

对于 $f_{i, j}$，从大到小枚举 $i$，则对于 $k \in (i, n]$，$f_{k, j}$ 都是已知的。对于 $f_{i, j}$，分类讨论：

- $f_{i, j} = f_{k, j} (k \in (i, g_{i, j}])$

  因为这里的 $i$ 是递减枚举的，所以对于 $k_1 < k_2$，只要能取到 $k_2$，一定能取到 $k_1$，所以当 $f_{k_1, j} > f_{k_2, j}$ 时，$k_2$ 的存在不能使答案更优，弹出 $k_2$。

  这里可以用单调队列维护 $k$。保证队列中 $k$ 和 $f_{k, j}$ 单调递减。每一次求 $f_{i, j}$ 时，从队尾往前遍历队列，只要 $k \leq g_{i, j}$，就弹出这个 $k$，因为 $i < k$，且这时一定有 $f_{i, j} \geq f_{k, j}$。重复上面的操作直到 $k > g_{i, j}$。

  如果最后一个弹出的 $k$ 满足 $f_{k, j} > g_{i, j}$，则赋值 $f_{i, j} = f_{k, j}$。否则就是下面的情况。

- $f_{i, j} = g_{i, j}$

  如果弹出的 $k$ 满足 $f_{k, j} \leq g_{i, j}$，说明从 $i$ 直接走一条线段到达的点更优。所以赋值 $f_{i, j} = g_{i, j}$。

最后把 $i$ 插入队尾。

对于每个 $j$，复杂度是 $O(n)$，因为每个 $i$ 只入队一次。总复杂度 $O(\frac{n^2}{BlockLen})$。

算法复杂度是 $O(\frac{n^2}{BlockLen} + qBlockLen + m)$

## 块长

为了方便计算，因为 $m \leq n$，我们将线性的 $m$ 忽略，把复杂度当成 $O(\frac{n^2}{BlockLen} + qBlockLen)$ 来计算，发现当块长取 $\frac n{\sqrt{q}}$ 时达到分块理论最优复杂度 $n\sqrt q$。

## 代码

注意：省略了缺省源和快读 `RD()`。

```cpp
unsigned A[100005], B[100005], m, n, q, Ans(0), From[100005], f[100005][400], g[100005][400], BlockLen, BlockNum, Block[100405], Ql, Qr, Stack[100005];
int main() {
  n = RD(), m = RD();
  for (register unsigned i(1); i <= m; ++i) { // 先读进来, 因为求块长需要用 q 
    A[i] = RD(), B[i] = RD();
  }
  q = RD();
  BlockLen = (n / (sqrt(q) + 1)) + 1;       // 理论最优块长 
  BlockNum = (n + BlockLen - 1) / BlockLen; // 块数 
  for (register unsigned i(1); i <= BlockNum; ++i) {
    for (register unsigned j(1); j <= BlockLen; ++j) {
      Block[(i - 1) * BlockLen + j] = i;    // O(n) 预处理 Block 数组 
    }
  }
  for (register unsigned i(1); i <= m; ++i) {
    g[A[i]][Block[B[i]]] = max(g[A[i]][Block[B[i]]], B[i]); // 更新 g[l][Block[r]]
    From[B[i]] = A[i];                                      // 存储 From[r] = l 
  }
  for (register unsigned i(1); i <= n; ++i) {
    g[i][Block[i]] = max(i, g[i][Block[i]]);
    for (register unsigned j(Block[i]); j <= BlockNum; ++j) {
      g[i][j] = max(g[i][j], g[i][j - 1]);                  // 扫一遍 g 数组, 通过单调性处理 g 
    }
  }
  for (register unsigned j(1), Ri; j <= BlockNum; ++j) {
    Ri = j * BlockLen;
    Ri = (Ri > n) ? n : Ri;                         // 终点的最大值 (第 j 块的右界)
    for (register unsigned i(Ri), Hd(0); i >= 1; --i) {
      while(Hd && Stack[Hd] <= g[i][j]) --Hd;       // 弹出队尾 
      if(Stack[Hd + 1] <= g[i][j]) {                // 这个 i 弹出了至少一次队尾 
        f[i][j] = max(f[Stack[Hd + 1]][j], g[i][j]);
      }
      else {                                        // 一次也没弹出 
        f[i][j] = g[i][j];
      }
      Stack[++Hd] = i;
    }
  }
  for (register unsigned i(1), j; i <= q; ++i) {  // 回答询问 
    Ql = RD(), Qr = RD();
    if(Block[Ql] ^ Block[Qr]) {                   // 左右端点在不同块内 
      Ans = f[Ql][Block[Qr] - 1];
      j = ((Block[Qr] - 1) * BlockLen) + 1;
    } else {                                      // 在同一块内 
      Ans = Ql;
      j = Ans + 1;
    }
    while (j <= Qr) {                             // 暴力最后不足一块的部分 
      if(Ql <= From[j] && From[j] <= Ans) {
        Ans = j;
      }
      ++j;
    }
    printf("%u\n", Ans);
  }
  return Wild_Donkey;
}
```

---

## 作者：__staring__ (赞：8)

(本题解由 [strcmp](https://www.luogu.com.cn/user/551861) [倾情赞助](https://cdn.luogu.com.cn/upload/image_hosting/xyc05vcd.png)，关注 [strcmp](https://www.luogu.com.cn/user/551861) 谢谢喵)

前情提要：https://www.luogu.com.cn/article/jvy9ju03

![](https://cdn.luogu.com.cn/upload/image_hosting/ikyt1ul0.png)

Segment Tree Beats？我们分块也要有自己的 Segment Tree Beats！

---

### 栈 $\rightarrow$ 吉司机线段树

假设现在我们需要维护一个序列，支持区间与 $x$ 取 min ，最后输出整个序列。

考虑这样一棵线段树，每个节点维护了这个区间按数值从小到大的 (数值,数量) 栈。

例如当前区间元素为 $\{3,2,2,5,1,1,1\}$ 时，其栈从栈底开始为 $[(1,3),(2,2),(3,1),(5,1))$ 。

将当前区间与 $x$ 取 min 时，我们取出栈顶直到其数值小于 $x$，再将 $x$ 及取出的数量和压入栈。

例如将上面的区间与 $2$ 取 min 时，我们按顺序取出 $(5,1),(3,1),(2,2)$ ，再压入 $(2,4)$ 。

假设我们已经维护好了栈，容易发现每次发生更新时栈的大小只减不增，而线段树所有节点的栈大小之和为 $O(n\log n)$ ，因此我们可以暴力更新栈。

然而显示地维护栈太过繁琐，我们考虑只维护最大值 $max$ 与严格次大值 $sec$ ，这也就是吉司机线段树。

---

### 栈 $\rightarrow$ "吉司机分块"

显式地维护栈繁琐的原因在于，完全包含询问区间的节点难以 `pushup`，被询问区间包含的节点子树难以 `pushdown`。

这是线段树本身存在 $O(\log n)$ 层的性质导致的，但我们考虑，**分块也可以看作一棵层数为 3 的 $O(\sqrt n)$ 叉线段树**。

那么如上述地，我们将序列分块，对第 $i$ 块维护块内的栈 $val_i,cnt_i,top_i$ ，对第 $i$ 个位置维护其在块内离散化后的大小 $pos_i$ 。

对整块操作时，我们直接如上述地对栈进行操作，然而为了保证时间复杂度，每个位置在块内的真实离散化大小应为 $\min(pos_i,top)$。

对散块操作时，我们不还原整个块再重构，这容易使复杂度退化到 $O(\sqrt n\log n)$。我们直接根据 $pos_i$ 对应修改栈中的 $cnt_{pos_i}$ ，再将栈中满足 $cnt_i=0$ 的项覆盖掉即可做到 $O(\sqrt n)$。

代码如下，修改-查询复杂度 $O(\sqrt n)-O(1)$ ，总复杂度 $O(n\sqrt n)$ ：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace staring
{
    typedef long long LL;
    typedef vector<int> VEC;
    typedef pair<int,int> PII;

    #define FOR(i,a,b) for(int i=(a),__i=(b);i<=__i;i++)
    #define ROF(i,a,b) for(int i=(a),__i=(b);i>=__i;i--)

    template<typename TYPE>
    TYPE gmax(TYPE &x,const TYPE y){return (x<y)&&(x=y),x;}
    template<typename TYPE>
    TYPE gmin(TYPE &x,const TYPE y){return (y<x)&&(x=y),x;}

}using namespace staring;

constexpr int N=1e5+5,B=320;

int fr[N]; // fr[i]: 记录以 i 为右端点的绳子的左端点
vector<PII> qry[N]; // qry[i]: 记录所有 y=i 的询问对 (l,idx)
int lp[B],rp[B],id[N]; // lp[i],rp[i]: 分块中第 i 个块的左右端点 id[i]: 第 i 个位置的所属块
int pos[N],top[B]; // pos[i]: 第 i 个数在块内的离散化后大小 top[i]: 第 i 个栈的大小
PII vc[B][B+5]; // vc[i]: 以 (val,cnt) 形式维护的第 i 个栈
int tmp[B+5],res[N]; // tmp[i]: 临时变量 res[i]: 第 i 个询问的答案

#define x first
#define y second

void modify(int k,int v)
{
    int b=id[k];
    // 对于整块，直接对栈操作
    FOR(i,1,b-1)
    {
        int c=0;
        while(top[i]&&vc[i][top[i]].x>=k)c+=vc[i][top[i]].y,--top[i];
        if(c)vc[i][++top[i]]={v,c};
    }

    // 对于散块，我们先更新离散化大小，再更新栈内的 cnt 值
    FOR(i,lp[b],rp[b])gmin(pos[i],top[b]);
    vc[b][++top[b]]={v,0};
    FOR(i,lp[b],k)
        if(vc[b][pos[i]].x>=k)--vc[b][pos[i]].y,pos[i]=top[b],++vc[b][pos[i]].y;

    // 记录栈内 cnt=0 的值的数量并将其覆盖
    int zero=0;
    FOR(i,1,top[b])
        if(!vc[b][i].y)++zero;
        else tmp[i]=i-zero,vc[b][i-zero]=vc[b][i];
    FOR(i,lp[b],rp[b])pos[i]=tmp[pos[i]];
    top[b]-=zero;
}

int main()
{
    int n,m,q;scanf("%d%d",&n,&m);
    FOR(i,1,m){int l,r;scanf("%d%d",&l,&r),(l<r)&&(fr[r]=l);}
    scanf("%d",&q);
    FOR(i,1,q){int x,y;scanf("%d%d",&x,&y),qry[y].push_back({x,i});}

    int tot=(n+B-1)/B;
    FOR(i,1,tot)
    {
        lp[i]=rp[i-1]+1,rp[i]=min(lp[i]+B-1,n);
        FOR(j,lp[i],rp[i])id[j]=i;
    }

    FOR(r,1,n)
    {
        // 我们先对区间操作再更新单点，防止重复插入栈
        int b=id[r];
        if(fr[r])modify(fr[r],r);

        FOR(i,lp[b],r)gmin(pos[i],top[b]);
        if(vc[b][top[b]].x==r)++vc[b][pos[r]=top[b]].y;
        else vc[b][pos[r]=++top[b]]={r,1};

        for(auto [l,idx]:qry[r])res[idx]=vc[id[l]][min(pos[l],top[id[l]])].x;
    }

    FOR(i,1,q)printf("%d\n",res[i]);

    return 0;
}
```

---

## 作者：strcmp (赞：7)

注意到题目保证 $r_i$ 互不相同。

因此考虑反过来对高的位置（$r$ 这一维度）扫描线。

从低到高扫 $y$，数据结构维护 $x \in [1,\,y]$ 的答案。

然后我们发现，根据题目的限制 $y$ 要么有**且只有一个** $r_i$ 放在上面，要么就没有。

用 $a_i$ 代表当前 $y$ 下 $x = i$ 位置的答案，没有 $r_i$ 放在上面显然对答案没有影响，否则将 $[1,\,l_i]$ 中 $a_i \ge l_i$ 的位置都改为 $r_i$。

这是经典 Segment Tree Beats，做完了。

时间复杂度 $\Theta(n \log n)$。

------------

等一下，还没完。

以下内容请学过 SGTB 再看。

注意到我们在 SGTB 中，每次是令 $a_i \leftarrow \min(a_i,\,w)$ 或者 $a_i \leftarrow \max(a_i,\,w)$ 才保证了势能。但是本题却是让 $a_i \ge l$ 的位置都变成 $r$。显然并不能直接使用 SGTB 的结论。

你考虑重新给它大概分析一下，注意到，每次只修改到最大值或者没修改到，复杂度最多只有 $\Theta(\log n)$。而修改到最大值和次大值以下的，至少会将最大值和次大值合并到一个数上。（在 SGTB 中，我们同样也是将最大值和次大值合并到一起）复杂度最多是对数乘以所要合并的颜色个数的，而这些颜色必然最后合并成一个，势能单调不增，所以不影响 SGTB 的证明，时间复杂度 $\Theta(n \log n)$。~~所以实际上你直接套 SGTB 的结论好像也没什么问题。~~

其实很好写，因为我们只需要维护最大值和次大值，以下是参考代码：

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;
using ld = double;
typedef long long int ll;
using pii = pair<int, int>;
const int maxn = 2e5 + 10;
constexpr ll mod = 1e9 + 7;
constexpr int inf = 1e9; int n, m, Q, a[maxn];
struct Node { int mx, cmx, tg; Node() { mx = cmx = -inf; tg = -1; } } t[maxn << 2];
#define ls(x) (x << 1) 
#define rs(x) (x << 1 | 1)
#define mx(x) (t[x].mx)
#define ct(x) (t[x].ct)
#define tg(x) (t[x].tg)
#define cmx(x) (t[x].cmx)
#define mid (l + r >> 1)
inline void pushup(int x) {
    mx(x) = max(mx(ls(x)), mx(rs(x)));
    cmx(x) = max(cmx(ls(x)), cmx(rs(x)));
    if (mx(ls(x)) != mx(x)) cmx(x) = max(cmx(x), mx(ls(x)));
    if (mx(rs(x)) != mx(x)) cmx(x) = max(cmx(x), mx(rs(x)));
}
inline void pushdw(int x) {
    if (tg(x) != -1) {
        int w = max(mx(ls(x)), mx(rs(x)));
        if (mx(ls(x)) == w) mx(ls(x)) = tg(ls(x)) = tg(x);
        if (mx(rs(x)) == w) mx(rs(x)) = tg(rs(x)) = tg(x);
        tg(x) = -1;
    }
}
void build(int l, int r, int x) {
    if (l == r) return mx(x) = l, void();
    build(l, mid, ls(x)), build(mid + 1, r, rs(x)), pushup(x);
}
void mdf(int l, int r, int ml, int mr, int v, int w, int x) {
    //>= v, -> 
    if (mx(x) < v) return;
    if (ml <= l && r <= mr) {
        if (cmx(x) < v && v <= mx(x)) return mx(x) = tg(x) = w, void();
        else mdf(l, mid, ml, mr, v, w, ls(x)), mdf(mid + 1, r, ml, mr, v, w, rs(x));
    }
    pushdw(x);
    if (ml <= mid) mdf(l, mid, ml, mr, v, w, ls(x));
    if (mr > mid) mdf(mid + 1, r, ml, mr, v, w, rs(x));
    pushup(x);
}
int qry(int l, int r, int v, int x) {
    if (l == r) return mx(x); pushdw(x);
    if (v <= mid) return qry(l, mid, v, ls(x));
    else return qry(mid + 1, r, v, rs(x));
}
vector<pii>q[maxn]; int ans[maxn];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, l, r; i <= m; i++) scanf("%d%d", &l, &r), a[r] = l; scanf("%d", &Q);
    for (int i = 1, x, y; i <= Q; i++) scanf("%d%d", &x, &y), q[y].push_back({ x, i }); build(1, n, 1);
    for (int i = 1; i <= n; i++) {
        if (a[i]) mdf(1, n, 1, a[i], a[i], i, 1);
        for (auto x : q[i]) ans[x.Y] = qry(1, n, x.X, 1);
    }
    for (int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> [CF793F Julia the snail](https://www.luogu.com.cn/problem/CF793F)

给定 $x, y$ 之后左端点小于 $x$ 或右端点大于 $y$ 的区间就没有用了。同时考虑两条限制比较麻烦，考虑离线按 $x$ 从大到小扫描线去掉一维限制。当 $x + 1\to x$ 时，加入所有以 $x$ 为左端点的区间 $(x, y_i)$，并回答所有以 $x$ 为左端点的询问。

- 考虑区间 $(x, y_i)$ 带来的影响。我们维护 $a_y$ 表示从 $y$ 出发可以到达的最小的 $x$，那么 $(x, y_i)$ 相当于对所有 $y\geq y_i$，如果 $y$ 能到达不超过 $y_i$ 的位置，那么 $y$ 可以到达 $x$。换言之，将所有 $y \geq y_i$ 且 $a_y \leq y_i$ 的 $a_y$ 全部改成 $x$。

- 设 $a_y$ 表示以 $y$ 为右端点的区间对应左端点，若左端小于 $x$ 则 $a_y = y$。维护 $cur$ 和 $low$ 表示当前位置在 $cur$，最低可以跳到 $low$，初始 $cur = y$，$low = a_y$，答案为 $y$。每次令 $low \gets \min(low, a_{cur})$，若此时仍有 $low = cur \neq x$，说明 $y$ 最多跳到 $low$，此时相当于将 $y$ 改成 $low - 1$ 并重复上述操作。

上述两种做法的修改和询问复杂度太劣，考虑根号平衡。对 $a$ 分块，并将 $a_y$ 的定义改为 $y$ 可达的任意不与 $y$ 同块的 $x(x < y)$。

设当前块左右边界分别为 $l, r$。

- 修改时，对于 $a_y \leq y_i$ 且 $y_i\leq y\leq r$ 的 $a_y$ 改成 $x$。

- 查询时，
    - 若 $low, cur$ 不同块，则令 $low$ 与 $\min_{p = l} ^ {cur} a_p$ 取最小值，且 $cur$ 变成 $l - 1$。
    - 若 $low, cur$ 同块且 $cur = r$，则令 $low$ 与 $\min_{p = low} ^ r a_p$ 取最小值。若 $low$ 和 $cur$ 仍同块，说明 $y$ 无法跳到比当前 $low$ 更低的位置。因为从更高的块跳下来最多跳到原来的 $low$，而原 $low$ 到 $cur$ 之间最多跳到当前 $low$，假设当前 $low$ 到原 $low$ 减 $1$ 之间可以跳出当前块，那么据 $a$ 的定义定义，原 $low$ 到 $cur$ 之间必然存在一个位置可以跳出当前块。
    - 若 $low, cur$ 同块且 $cur < r$，说明从当前 $y$ 开始无法跳到比 $low$ 更低的位置。
    - 对于无法跳到比 $low$ 更低的位置的情况，此时 $low, cur$ 同块。若 $low, x$ 不同块，则需要从 $low$ 往 $l$ 找第一个可以跳出当前块的位置 $p$，令 $y\gets p$ 并重复上述过程。否则从 $low$ 往 $x$ 枚举找第一个使得 $a_y = x$ 的 $y$ 即为所求。

因为每个块内至多停顿一次即可跳到更低的块，所以查询复杂度同样为 $\mathcal{O}(\sqrt n)$。

对每个块预处理 $a$ 的前缀 $\min$，后缀 $\min$，以及从每个位置开始往前的第一个可跳出当前块的位置。修改时可关于块长线性处理。时间复杂度 $\mathcal{O}(m\sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;
inline ll read() {
  ll x = 0, sgn = 0;
  char s = getchar();
  while(!isdigit(s)) sgn |= s == '-', s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return sgn ? -x : x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 1e5 + 5;
constexpr int B = 333;
int n, m, q, ans[N];
int a[N], blk[N], lp[N], rp[N];
int suf[N], pre[N], fst[N];
vector<int> buc[N];
vector<pii> qu[N];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n >> m;
  for(int i = 1; i <= n; i++) a[i] = i, blk[i] = i / B;
  for(int i = 0; i <= blk[n]; i++) lp[i] = max(1, i * B), rp[i] = min(n, i * B + B - 1);
  for(int i = 1; i <= m; i++) {
    int l = read(), r = read();
    buc[l].push_back(r);
  }
  cin >> q;
  for(int i = 1; i <= q; i++) {
    int x = read(), y = read();
    qu[x].push_back({y, i});
  }
  auto rebuild = [&](int id, int lim) {
    int l = max(lim, lp[id]), r = rp[id];
    suf[r] = a[r];
    for(int i = r - 1; i >= l; i--) suf[i] = min(suf[i + 1], a[i]);
    pre[l] = a[l];
    for(int i = l + 1; i <= r; i++) pre[i] = min(pre[i - 1], a[i]);
    fst[l] = a[l] < l ? l : l - 1;
    for(int i = l + 1; i <= r; i++) fst[i] = a[i] < l ? i : fst[i - 1];
  };
  for(int i = n; i; i--) {
    for(int it : buc[i]) {
      int cur = it;
      for(int p = it; p <= rp[blk[it]]; p++) if(a[p] <= it) a[p] = i;
      rebuild(blk[it], i);
    }
    rebuild(blk[i], i);
    for(pii it : qu[i]) {
      int y = it.first, x = a[y], ans = y;
      while(1) {
        while(blk[x] < blk[y]) {
          x = suf[min(x, pre[y])];
          y = lp[blk[y]] - 1;
        }
        if(blk[y] == blk[i]) {
          for(int p = y; p >= i; p--) {
            if(p < x) ans = p;
            x = min(x, a[p]);
          }
          break;
        }
        if(blk[x] == blk[y]) ans = y = fst[x], x = a[y];
      }
      ::ans[it.second] = ans;
    }
  }
  for(int i = 1; i <= q; i++) print(ans[i]), putchar('\n'); 
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/21
author: Alex_Wei
start coding at 
finish debugging at 20:34
*/
```

---

## 作者：User_Unauthorized (赞：5)

## 题意
有一个长为 $n$ 的杆，上面有 $m$ 条绳子，每条绳子可以让蜗牛从 $l_i$ 爬到 $r_i$（中途不能离开），保证 $r_i$ 各不相同。蜗牛也可以自然下落。

现在有 $q$ 次询问，询问 $x$ 出发，途中高度不能低于 $x$ 或高于 $y$，问最高能爬到的位置。

$n,m,q\leq 10^5$。

## 题解

模拟赛 T4，加强了数据范围，改为了 $n,m,q\leq 10^6$，卡掉了分块做法。

我们考虑将询问离线。因为题目中明确不同绳子的 $r_i$ 互不相同，所以我们考虑按询问的右端点去处理，维护当前左端点的答案。换句话说，我们使用当前处理的区间的右端点 $r$ 去遍历，并维护所有满足 $l \in \left[1,r\right]$ 的区间 $\left[l,r\right]$ 的答案。

考虑我们移动了右端点 $r$，即 $r - 1 \rightarrow r$，可以发现只有存在右端点为 $r$ 的绳子，那么答案才会产生相应的影响。那么我们考虑存在右端点为 $r$ 的绳子，考虑其对答案的影响，我们设这条绳子的左端点为 $l$，设对于$x \in \left[1,r\right]$，$ans_x$ 为左端点为 $x$，右端点为 $r$ 的区间的询问的答案。也就是从 $x$ 出发，只使用当前已经添加了的绳子，可以爬到的最高高度。我们考虑添加绳子对答案的影响，如果 $x > l$，根据题意，由于其只能使用包含在区间 $\left[x,r\right]$ 内的绳子，所以这条绳子不会对这部分左端点的答案产生影响。对于 $x \le l$，若 $ans_x < l$，由于蜗牛无法爬到这条绳子的最低点，所以也不会产生影响。所以这条绳子只对满足 $x \in \left[1,l\right] \land ans_x \ge l$ 的左端点产生影响，不难看出会把这部分左端点的答案直接更新为 $r$。

考虑使用数据结构维护对答案的影响，我们需要一个数据结构支持将一定区间内大于等于给定值的部分更新为一个新的更大的值。可以想到吉司机线段树可以满足这个需求，实现更改。具体实现的话我们可以对于每个线段树节点维护最大值 $max_i$ 和次大值 $sec_i$，对于每次更改，可以表达为四元组 $\left(l, r, A, B\right)$ 的形式，即将区间 $\left[l,r\right]$ 的大于等于 $A$ 的部分更新为 $B$。对于更改的时候，如果 $max_i < A$，那么这个区间的值不会被更新，如果 $max_i \ge A > sec_i$，那么只更新最大值即可，如果 $sec_i \ge A$，那么递归地处理。在 $n,m,q$ 同阶的情况下，总复杂度为 $\mathcal{O}(n \log n)$。

## 复杂度分析

> 这部分是笔者自己对吉司机线段树的理解，如有错误欢迎各位指正。

考虑所有满足 $a_i \neq a_{i + 1}$ 的点对 $\left(i, i + 1\right)$，如果我们的更改操作递归到了叶子节点，那么这样的点对便会减少一个，可以看出每消除一个这样的点对复杂度均为 $\mathcal{O}(\log n)$，初始状态下这样的点对有 $\mathcal{O}(n)$ 个（线段树初始化时 $ans_x \leftarrow x$），考虑每次更改对点对数量的影响，可以看出最多会增加两个点对 $\left(l - 1,l\right)$ 和 $\left(r, r + 1\right)$，所以总共出现过的的点对数量为 $\mathcal{O}(n + q)$，又因为消除每个点对的复杂度均为 $\mathcal{O}(\log n)$，所以对于操作的三种情况中最后一种情况的复杂度为 $\mathcal{O}(n \log n)$，其他情况和单点查询的复杂度同普通线段树，故总复杂度为 $\mathcal{O}(n \log n)$。

## Code
```cpp
//D
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MIN = INT_MIN;

class SegmentBeats {
public:
    typedef ValueVector container;

private:
    valueType N;

    container max, second, tagA, tagB;

    void addTag(valueType id, valueType A, valueType B) {
        if (max[id] >= A && max[id] <= B) {
            max[id] = std::max(max[id], B); //TAG

            if (tagA[id] == MIN) //TAG
                tagA[id] = A;

            tagB[id] = B;
        }
    }

    void pushDown(valueType id) {
        if (tagA[id] != MIN) {
            addTag(id << 1, tagA[id], tagB[id]);
            addTag(id << 1 | 1, tagA[id], tagB[id]);

            tagA[id] = tagB[id] = MIN;
        }
    }

    void update(valueType id, valueType key) {
        if (key > max[id]) {
            second[id] = max[id];
            max[id] = key;
        } else if (key < max[id] && key > second[id]) {
            second[id] = key;
        }
    }

    void pushUp(valueType id) {
        max[id] = MIN;
        second[id] = MIN;

        update(id, max[id << 1]);
        update(id, second[id << 1]);
        update(id, max[id << 1 | 1]);
        update(id, second[id << 1 | 1]);
    }

public:
    explicit SegmentBeats(valueType size) : N(size), max((N << 2) + 5, MIN), second((N << 2) + 5, MIN),
                                            tagA((N << 2) + 5, MIN), tagB((N << 2) + 5, MIN) {
        build(1, 1, N);
    }

    void modify(valueType L, valueType R, valueType A, valueType B) {
        modify(1, 1, N, L, R, A, B);
    }

    valueType query(valueType pos) {
        return query(1, 1, N, pos);
    }

private:
    void build(valueType id, valueType L, valueType R) {
        if (L == R) {
            max[id] = L;
            return;
        }

        valueType mid = (L + R) >> 1;

        build(id << 1, L, mid);
        build(id << 1 | 1, mid + 1, R);

        pushUp(id);
    }

    void modify(valueType id, valueType nodeL, valueType nodeR, valueType queryL, valueType queryR, valueType A,
                valueType B) {
        if (max[id] < A)
            return;

        if (nodeL >= queryL && nodeR <= queryR && second[id] < A) {
            addTag(id, A, B);

            return;
        }

        pushDown(id);

        valueType mid = (nodeL + nodeR) >> 1;

        if (queryL <= mid)
            modify(id << 1, nodeL, mid, queryL, queryR, A, B);

        if (queryR > mid)
            modify(id << 1 | 1, mid + 1, nodeR, queryL, queryR, A, B);

        pushUp(id);
    }

    valueType query(valueType id, valueType nodeL, valueType nodeR, valueType pos) {
        if (nodeL == nodeR)
            return max[id];

        pushDown(id);

        valueType mid = (nodeL + nodeR) >> 1;

        if (pos <= mid)
            return query(id << 1, nodeL, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, nodeR, pos);
    }
};

struct Query {
    valueType left;
    valueType id;

    Query() = default;

    Query(valueType left, valueType id) : left(left), id(id) {};
};

int main() {
    std::ios_base::sync_with_stdio(false);

    valueType N, M;

    std::cin >> N >> M;

    ValueVector rope(N + 1, 0);

    for (valueType i = 0; i < M; ++i) {
        valueType left, right;

        std::cin >> left >> right;

        rope[right] = left;
    }

    SegmentBeats tree(N);

    valueType Q;

    std::cin >> Q;

    std::vector<std::vector<Query>> query(N + 1);

    for (valueType i = 0; i < Q; ++i) {
        valueType left, right;

        std::cin >> left >> right;

        query[right].emplace_back(left, i);
    }

    ValueVector ans(Q);

    for (valueType i = 1; i <= N; ++i) {
        valueType left = rope[i];
        valueType right = i;

        if (left > 0)
            tree.modify(1, left, left, right);


        for (auto const &iter: query[right])
            ans[iter.id] = tree.query(iter.left);
    }

    for (auto const &iter: ans)
        std::cout << iter << '\n';

    return 0;
}
```

---

## 作者：YCS_GG (赞：5)

优雅的非分块做法

询问先离线下来，按右端点排个序，然后考虑当右端点移动的时候答案怎么变化

记点 $x$ 点的答案为 $r_x$

当从 $r \rightarrow r+1$ 的时候，如果这个点有绳子 $[l,r+1]$ 那么考虑在 $l$ 左边的点如果它的答案在 $[l+1,r]$ 之间（事实上不可能超过 $r$）

那就将其更新为 $r+1$ ，那么我们要快速找到 $[1,l]$ 的点中大于 $l$ 的点并将其修改为 $r+1$

这个东西可以用势能线段树做，具体来说记录一个两元的标记 $tag(x,y)$ 表示大于等于 $y$ 的点修改为 $x$ 就可以做了，下放注意下要取最小的 $y$

其他操作和势能线段树一样，复杂度 $O(m\log n)$

```cpp
#include <array>
#include <iostream>
#include <vector>
using namespace std;
const int N   = 1e5 + 10;
const int INF = 0x3f3f3f3f;
namespace SegmentBeats {
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
struct Node {
    int max, sem;
    pair<int, int> tag;
    int l, r;
};
array<Node, N * 4> tr;
auto merge(const Node &A, const Node &B) {
    pair<int, int> res;
    if (B.max > A.max) {
        res.first  = B.max;
        res.second = max(A.max, B.sem);
    } else if (B.max < A.max) {
        res.first  = A.max;
        res.second = max(A.sem, B.max);
    } else {
        res.first  = A.max;
        res.second = max(A.sem, B.sem);
    }
    return res;
}
// apply B -> A
void apply_tag(Node &A, const Node &B) {
    if (A.max >= B.tag.second) {
        A.max = B.tag.first;
        if (!A.tag.second) {
            A.tag.second = B.tag.second;
        } else {
            A.tag.second = min(A.tag.second, B.tag.second);
        }
        A.tag.first = B.tag.first;
    }
}
void apply_tag(Node &A, const pair<int, int> &B) {
    if (A.max >= B.second) {
        A.max = B.first;
        if (!A.tag.second) {
            A.tag.second = B.second;
        } else {
            A.tag.second = min(A.tag.second, B.second);
        }
        A.tag.first = B.first;
    }
}
void pushup(int x) {
    auto &&res = merge(tr[ls(x)], tr[rs(x)]);
    tr[x].max  = res.first;
    tr[x].sem  = res.second;
}
void pushdown(int x) {
    if (tr[x].tag.first) {
        apply_tag(tr[ls(x)], tr[x]);
        apply_tag(tr[rs(x)], tr[x]);
        tr[x].tag = make_pair(0, 0);
    }
}
void build(int rt, int l, int r) {
    tr[rt].l = l;
    tr[rt].r = r;
    if (l == r) {
        tr[rt].max = l;
        tr[rt].sem = -INF;
        return;
    }
    int mid = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    pushup(rt);
}
void update(int rt, int L, int R, int x, int y) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (tr[rt].max < y) {
        return;
    }
    if (l >= L && r <= R && tr[rt].sem < y) {
        apply_tag(tr[rt], make_pair(x, y));
        return;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (L <= mid) {
        update(ls(rt), L, R, x, y);
    }
    if (mid < R) {
        update(rs(rt), L, R, x, y);
    }
    pushup(rt);
}
int query(int rt, int pos) {
    auto &l = tr[rt].l;
    auto &r = tr[rt].r;
    if (l == r) {
        return tr[rt].max;
    }
    pushdown(rt);
    int mid = (l + r) / 2;
    if (pos <= mid) {
        return query(ls(rt), pos);
    } else {
        return query(rs(rt), pos);
    }
}
#undef ls
#undef rs
} // namespace SegmentBeats
int n, m, q;
array<int, N> lb, ans;
struct Query {
    int l, id;
};
vector<Query> qr[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        lb[r] = l;
    }
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        qr[r].emplace_back(Query{l, i});
    }
    SegmentBeats::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        if (lb[i]) {
            SegmentBeats::update(1, 1, lb[i], i, lb[i]);
        }
        for (auto &p : qr[i]) {
            ans[p.id] = SegmentBeats::query(1, p.l);
        }
    }
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
// Asusetic eru quionours
```

---

## 作者：SDNetFriend (赞：4)

### 分块做法
尝试提供一种较为优美的分块写法

具体解析写在了代码的注释中

重点是对于 $f_{i,j}$ 的处理，由于其具有向下走没有代价的性质，所以 $i$ 更大 $f$ 一定更优这个

我们这里要用这个性质维护一个栈来更新当前可能更新答案的节点

贴代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define rint register int
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return f*res;
}
const int N=1e5+5,sN=4e2+5;
int n,m,q,g[N][sN]={0},f[N][sN];
int fm[N],bk[N],bkl,bkcnt;
/*
g[i][j]:表示从第i个点开始一直到第j个块，所有的绳子能到达的最右端的位置（直达）
f[i][j]:表示从第i个点开始一直到第j个块，通过各种方式能到达的最右端的位置（不一定直达）
bkl:块长 
bkcnt:块数 
bk[i]: i点所在的块 
*/
int main(){
	n=read();
	bkl=sqrt(n);
	bkcnt=n/bkl;
	if(n%bkl!=0)++bkcnt;//如果有不满整块的就加一块 
	for(rint i=1;i<=n;++i)
		bk[i]=(i-1)/bkl+1;
	m=read();
	for(rint i=1;i<=m;++i){
		int l=read(),r=read();
		fm[r]=l;
		g[l][bk[r]]=max(g[l][bk[r]],r);//先计算在块内的结果 
	}
	for(rint i=1;i<=n;++i){
		g[i][bk[i]]=i;//初始可以到达的都是自身 
		for(rint j=bk[i];j<=bkcnt;++j)
			g[i][j]=max(g[i][j],g[i][j-1]);//更新所有的g为块内和之前块的结果 
	}
	int stk[N],hed;
	for(rint i=1;i<=bkcnt;++i){
		int r=min(bkl*i,n);
		hed=0;
		for(rint j=r;j>=1;--j){
			while(hed&&stk[hed]<=g[j][i])
				--hed;
			/*
			新点加入只有两种情况
			1.g不如能到达的点的f优，此时新点的f被改为旧点f，但是新点更靠左，所以排除旧点
			2.g比可到达的点的f优，新点的f还是比旧点的优，依旧踢出旧点
			3.到达不了栈顶点，由于栈顶点已经是最靠左的了，那么久没法更新，直接自己更新自己然后入栈 
			*/
			if(stk[hed+1]<=g[j][i])//这里最后一个能到达的一定是最优的，用这个点更新当前的答案 
				f[j][i]=max(f[stk[hed+1]][i],g[j][i]);
			else f[j][i]=g[j][i];
			stk[++hed]=j;
		}
	}
	q=read();
	while(q--){
		int x=read(),y=read(),ava=x,i;
		/*
		ava：记录当前可以到达的最右端的位置，也是最后的答案
		i：指向第一个尚未处理的散点的下标 
		*/ 
		if(bk[x]!=bk[y]){//如果两个不在一块内就直接把右端点上一块给处理掉 
			ava=f[x][bk[y]-1];
			i=((bk[y]-1)*bkl)+1;
		}else{//否则在一块内就从头开始 
			ava=x;
			i=ava+1;
		}
		while(i<=y){//处理尚未处理的散点 
			if(x<=fm[i]&&fm[i]<=ava)//如果当前右端点对应的左端点可以到达那么更新答案 
				ava=i;
			++i;
		}
		printf("%d\n",ava);
	}
	return 0;
}
```


---

## 作者：123456xwd (赞：3)

考虑离线后扫描线，设 $r$ 表示当前的上界，$f_i$ 表示在 $[i,r]$ 这个区间内走到的最高点。

若 $r-1\to r$，此时至多新加入一条 $[l,r]$ 的边，考虑其对答案的影响。

设从 $i$ 出发的可以利用到这一条边，则 $f_i\in [l,r]$，且 $i\in [1,l]$。

而此时 $\forall i\in[1,r],f_i\le r$，也就是说我们要把 $i\in [1,l]$ 中 $\ge l$ 的 $f_i$ 变为 $r$。

考虑吉司机维护，是否可以将上述操作变为将区间内最大值变为 $r$？

类似 [「BZOJ 4695」最假女选手](https://www.luogu.com.cn/problem/P10639) 中我们对于区间取最值的过程，设当前节点是需要被修改的，且 $l\le second_{max}<first_{max}$，那么我们就要继续递归下去，找到第一个满足 $second_{max}<l\le first_{max}$ 的地方。

而如果是这样子递归下去的话，也就是说 $second_{max},first_{max}$ 修改后都变成了同一个数，也就是该区间的值域大小起码减小 $1$，由于一开始 $f_i=i$，而每个点会在他的祖先节点处贡献一个值域大小，复杂度为 $\mathcal{O}(n\log n)$，跑得飞快。

也就是说我们要维护一个支持区间变化最大值和单点查询的吉司机线段树。

```c++
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define p_b push_back
#define m_p make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
#define gcd __gcd
#define lowbit(x) (x&(-x))
using namespace std;
int rd(){
    int x=0,f=1; char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar('0'+x%10);
}
const int N=1e5+5,INF=0x3f3f3f3f;
int n,m,q,ans[N];
int A[N];
vector<pii> B[N];
struct seg{
    struct node{
        int mx,se,la;
    }tree[N<<2];
    void calc(int k,int la){tree[k].mx+=la;tree[k].la+=la;}
    void push_down(int k){
        if(!tree[k].la) return;
        int mx=max(tree[ls].mx,tree[rs].mx);
        if(tree[ls].mx==mx) calc(ls,tree[k].la);
        if(tree[rs].mx==mx) calc(rs,tree[k].la);
        tree[k].la=0;
    }
    void push_up(int k){
        tree[k].mx=max(tree[ls].mx,tree[rs].mx);
        tree[k].se=max((tree[k].mx==tree[ls].mx)?tree[ls].se:tree[ls].mx,(tree[k].mx==tree[rs].mx)?tree[rs].se:tree[rs].mx);
    }
    void build(int k,int l,int r){
        if(l==r){
            tree[k].mx=l,tree[k].se=-INF;
            return;
        }
        build(ls,l,mid),build(rs,mid+1,r);
        push_up(k);
    }
    int ask(int k,int l,int r,int pos){
        if(l==r)return tree[k].mx;
        push_down(k);
        if(pos<=mid)return ask(ls,l,mid,pos);
        return ask(rs,mid+1,r,pos);
    }
    void change(int k,int l,int r,int x,int y,int pos,int w){
        if(tree[k].mx<pos) return;
        if(x<=l&&r<=y&&tree[k].se<pos){
            calc(k,w-tree[k].mx);
            return;
        }
        push_down(k);
        if(x<=mid)change(ls,l,mid,x,y,pos,w);
        if(y>mid) change(rs,mid+1,r,x,y,pos,w);
        push_up(k);
    }
}T;
int main(){
    n=rd(),m=rd();
    for(int i=1;i<=m;i++){
        int l=rd(),r=rd();
        A[r]=l;
    }
    T.build(1,1,n);
    q=rd();
    for(int i=1;i<=q;i++){
        int l=rd(),r=rd();
        B[r].p_b(m_p(l,i));
    }
    for(int r=1;r<=n;r++){
        if(A[r]) T.change(1,1,n,1,A[r],A[r],r);
        for(auto [l,id]:B[r])ans[id]=T.ask(1,1,n,l);
    }
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：2020HZ06 (赞：2)

这题有一个不需要吉司机线段树的极简做法。

注意对于每个询问 $[x,y]$，能用的绳索 $[l,r]$ 需要满足 $l\ge x,r\le y$。不然蜗牛会爬出去。然后每两条绳索有**重叠**就可以接起来。

绳索有重叠可以让所有绳索的 $r$ 减去 $1$。这样就变成**覆盖**问题了。要求的是 $x$ 开始的**最长覆盖前缀**。

套路地，离线所有询问。因为询问是求前缀，因此从大到小枚举**左端点** $l$。
开一棵初值都为 $\inf$ 的线段树。
对于所有左端点是 $l$ 的绳索，在线段树上区间 $[l,r-1]$ 对 $r$ 取 $\min$。因为绳索的 $r$ 尽量小的话就可以**对更多的询问产生贡献**。对于每个 $x=l$ 的询问，**线段树上二分**求出 $[x,y]$ 内第一个 $[x,p]$ 的最大值大于 $y$ 的位置 $p$。显然 $p$ 一定存在。那么 $[x,p-1]$ 的位置都已被覆盖，之前把 $r$ 减去了 $1$，答案即为 $p$。

我们只需要一棵支持区间对 $x$ 取 $\min$，和区间询问 $\max$ 的线段树即可。这是容易的。时间复杂度 $O((m+q)\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls rt*2
#define rs rt*2+1
#define mid (l+r)/2
#define pb push_back
const int N=100005;
int n,m,q;
struct node{
	int x,y,xh;
}a[N];
struct tree{
	int mx,lz;//区间 max，取 min 的懒标记
}tr[4*N];
vector<int>v[N];
int ans[N];
bool cmp(node x,node y){
	return x.x>y.x;
}
void tag(int rt,int k){
	tr[rt].mx=min(tr[rt].mx,k);//直接对最大值取 min
	if(tr[rt].lz) tr[rt].lz=min(tr[rt].lz,k);
	else tr[rt].lz=k;
}
void pd(int rt){
	if(tr[rt].lz){
		tag(ls,tr[rt].lz),tag(rs,tr[rt].lz);
		tr[rt].lz=0;
	}
}
void modify(int l,int r,int rt,int L,int R,int k){
	if(l>=L&&r<=R){
		tag(rt,k);return;
	}
	pd(rt);
	if(L<=mid) modify(l,mid,ls,L,R,k);
	if(R>mid) modify(mid+1,r,rs,L,R,k);
	tr[rt].mx=max(tr[ls].mx,tr[rs].mx);
}
int find(int l,int r,int rt,int L,int R){//线段树上二分
	if(l>=L&&r<=R){
		if(tr[rt].mx<=R) return -1;
		if(l==r) return l;
		pd(rt);
		if(tr[ls].mx>R) return find(l,mid,ls,L,R);
		else return find(mid+1,r,rs,L,R);
	}
	int res=-1;
	pd(rt);
	if(L<=mid) res=find(l,mid,ls,L,R);
	if(R>mid&&res==-1) res=find(mid+1,r,rs,L,R);
	return res;
}
int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		v[x].pb(y);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++) scanf("%d%d",&a[i].x,&a[i].y),a[i].xh=i;
	sort(a+1,a+q+1,cmp);
	int p=1; 
	for(int i=1;i<=4*n;i++) tr[i].mx=N;
	for(int i=n;i>=1;i--){
		for(int j:v[i]){
			if(i<j) modify(1,n,1,i,j-1,j);//绳索
		}
		while(p<=q&&a[p].x==i){//询问
			int pos=find(1,n,1,i,a[p].y);
			ans[a[p].xh]=pos;//注意如果没有任何以 i 为左端点的绳索，一开始也还在 pos
			p++;
		}
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：StayAlone (赞：0)

主要讲一下严格复杂度的做法。

对询问按照 $r$ 排序后离线处理，依次插入线段，线段树维护答案，查询为单点查询。

插入线段 $[l, r]$ 时，$\forall x\in[1, l]\land ans_x\geq l$，做 $ans_x\gets r$。

于是和 [此题做法](https://www.luogu.com.cn/article/rb29onqq) 一样：

设懒标记 $|l, r|$ 表示，对区间内 $ans_x\geq l$ 的位置，做 $ans_x\gets r$。

假设现有标记 $|l_1, r_1|$，要添加标记 $|l_2,r_2|$，考虑合并标记。注意，由于前面离线排序的存在，始终有 $r_2\geq r_1$。

- 若 $r_1\geq l_2$，分讨一下发现新标记就是 $|\min\{l_1, l_2\}, r_2|$。
- 否则，不更新标记。原因是由于标记 $|l_1,r_1|$ 的存在，区间中 $ans_x\leq r_1$，那么此刻 $|l_2,r_2|$ 标记就不可能有效；又因为新的 $r_q\geq r_2$，不会存在需要 $|l_2,r_2|$ 为“桥梁”连接的标记。

时间复杂度 $\mathcal O(n+(m+q)\log n)$。

```cpp
int n, m, q, ans[MAXN], L[MAXN];
vector <pii> qr[MAXN];

il pii operator + (pii &x, pii &y) {
	if (x.snd >= y.fst) return mp(min(x.fst, y.fst), y.snd);
	return x;
}

il void operator += (pii &x, pii &y) {
	x = x + y;
}

struct setr {
	pii tag[MAXN << 2];
	
	il void pushdown(int x) {
		tag[ls(x)] += tag[x]; tag[rs(x)] += tag[x];
		tag[x] = {inf, inf};
	}
	
	il void build(int x, int l, int r) {
		tag[x] = {inf, inf};
		if (l == r) return tag[x] = {0, l}, void();
		int mid = l + r >> 1;
		build(ls(x), l, mid); build(rs(x), mid + 1, r);
	}
	
	il void upd(int x, int l, int r, int ql, int qr, pii tg) {
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return tag[x] += tg, void();
		int mid = l + r >> 1; pushdown(x);
		upd(ls(x), l, mid, ql, qr, tg); upd(rs(x), mid + 1, r, ql, qr, tg);
	}
	
	il int query(int x, int l, int r, int k) {
		if (l == r) return tag[x].snd;
		int mid = l + r >> 1; pushdown(x);
		return k <= mid ? query(ls(x), l, mid, k) : query(rs(x), mid + 1, r, k);
	}
} T;

int main() {
	read(n, m); int l, r;
	while (m--) read(l, r), L[r] = l;
    read(q); T.build(1, 1, n);
	rep1(i, 1, q) read(l, r), qr[r].eb(l, i);
    rep1(r, 1, n) {
        if (L[r]) T.upd(1, 1, n, 1, L[r], {L[r], r});
        for (auto [l, id] : qr[r]) ans[id] = T.query(1, 1, n, l);
    }
	rep1(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
```

---

