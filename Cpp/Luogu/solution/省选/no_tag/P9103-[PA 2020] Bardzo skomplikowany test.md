# [PA 2020] Bardzo skomplikowany test

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Bardzo skomplikowany test](https://sio2.mimuw.edu.pl/c/pa-2020-1/bst/)**

Bytie 刚刚参加了算法和数据结构这门课的面试。他没有为之学习太长时间，所以他做得不是太好。经过几分钟的交谈，这位心碎的主讲老师决定给这个男孩最后一次机会。

- 「孩儿，你知道啥是 BST 不？」教授问

Bytie 听到这句话后内心狂喜，因为在他上课睡觉的时候记住了一些理论。

- 「知道。大小为 $n$ 的 BST 是一棵有根树，其顶点用 $1$ 到 $n$ 的整数来编号。每个节点最多可以有两个子节点；它可以有一个最多一个左子节点和一个最多一个右子节点。此外，每个节点的编号必须大于其左子树中所有节点的编号，并小于其右子树中所有顶点的编号。」Bytie 回答说，他达到了他潜意识的深处。
- 「很好。让我们看看你是否记住了如何对 BST 进行旋转。」一直坐在那里的教授回答说。他站起来，向黑板走去。

Bytie 被冷汗浸透了。他一时失去了信心，因为他记不起旋转的具体原理（可能在上这节课的时候，他正在另一边摸鱼，没听课）。考官在黑板上画了两棵同样大小的 BST 树，并让 Bytie 用正确的旋转将第一棵树转化为第二棵树。

Bytie 想了一会儿，认为左旋就是选择某个节点 $v$ 和它的右子节点 $w$，并让 $w$ 成为 $v$ 的父节点。Bytie 的直觉用以下伪代码描述。

```
if v.Parent != null then
    if v.Parent.RightSon == v then
        v.Parent.RightSon := w
    else
        v.Parent.LeftSon := w
w.Parent := v.Parent
v.Parent := w
w.LeftSon := v
v.RightSon := null
```

![](https://cdn.luogu.com.cn/upload/image_hosting/shqgiur7.png)

以此类推，Bytie 理解了右旋，其中 $w$ 是 $v$ 的左子节点。

```
if v.Parent != null then
    if v.Parent.RightSon == v then
        v.Parent.RightSon := w
    else
        v.Parent.LeftSon := w
w.Parent := v.Parent
v.Parent := w
w.RightSon := v
v.LeftSon := null
```

![](https://cdn.luogu.com.cn/upload/image_hosting/tpmzihlx.png)

然而，Bytie 很快就注意到有些不对劲。如果节点 $w$ 在左旋时有左子树，它就会丢失！同样在右转过程中，节点 $w$ 的右子树也会丢失。

- 「快点孩儿，你不是唯一一个想通过这次考试的人。」教授不耐烦地催促道。

在没有太多时间考虑的情况下，Bytie 假设只有在这个有问题的子树是空的情况下才能执行旋转，也就是说，如果没有顶点丢失并且树保持一致的话才进行旋转。

为了尽快结束他的煎熬，他决定进行最少次数的旋转，使他能够将第一棵树变成第二棵。请告诉他这是否可行，如果可行，他需要进行多少次轮换？由于这个数字可能相当大，请告诉他这个值对 $10^9+7$ 取模后的值。

## 说明/提示

#### 样例 1 解释

下图展示了旋转最小次数所采取的旋转方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/f1dblwez.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n\le 5\times 10^5$，$-1\le a_i\le n$，$a_i\neq 0$。

## 样例 #1

### 输入

```
4
3 1 -1 3
2 -1 4 2```

### 输出

```
3```

## 样例 #2

### 输入

```
8
2 4 2 7 4 5 -1 7
2 3 6 5 3 -1 6 7```

### 输出

```
7```

# 题解

## 作者：Sol1 (赞：4)

考虑如果第一棵树的根是 $a$，第二棵树的根是 $b$。不妨假设 $a<b$，另一个方向对称。

此时我们为了把 $b$ 移动到根，我们显然需要将 $a+1\sim b-1$ 的所有点移动到 $a,b$ 之间，形成一条 $a-(a+1)-(a+2)-\cdots-(b-1)-b$ 的链，然后将 $b$ 转到根。

此时树根的两侧是独立子问题，递归做即可。

---

为什么这么做是最优的？

考虑：

1. 如果考虑树的父亲序列，则题目中的操作一定只会同时改变中序遍历上相邻的两个点的父亲。
1. 复位根必须要求形成一条 $a-(a+1)-(a+2)-\cdots-(b-1)-b$ 的链，从而一切会改变 $a,b$ 以及中间的任何一个点的，且不属于构建这条链的过程的结构改变都将被覆盖，没有必要。
1. 其余改变与构建链的过程独立，可以交换到构建链后面。

---

然后就是考虑如何构建这条链。

这个唯一性很强：从 $a$ 开始递归往右走直到走到一个 $\geq k$ 的点，设走到 $a-c_1-c_2-\cdots-c_k$。然后将 $c_1$ 的左子树修改成一条左链，然后往右转直到左子树消失。然后对 $c_2,\cdots,c_k$ 同样处理。

---

然后再考虑如何把一个子树修改成左链/右链。（右链是因为需要对称）

这个更直接，把左子树修改成左链，右子树修改成右链，然后依照需求往左/往右转。

这个修改次数就可以直接 dp 了。设 $f_{u,0/1}$ 表示修改成左链/右链的方案数，$s_u$ 是 $u$ 的子树的大小。转移：

- $f_{u,0}\leftarrow f_{l,0}+f_{r,1}+s_l$
- $f_{u,1}\leftarrow f_{l,0}+f_{r,1}+s_r$

其中 $l,r$ 是 $u$ 的左右孩子。

---

考虑算答案。

考虑我们复位根之后剩下的是包含根的一条链，两头接上 **原本就在 $a$ 中存在** 的子树。

所以我们就可以将 $a$ 的形态记作一棵子树上面接一条左链/右链，且这个链上的点是一个连续区间。

然后注意到上面那个“从 $a$ 开始递归往右走直到走到一个 $\geq k$ 的点”的过程不会多次搜到同一个点，于是直接暴力做，复杂度就是 $O(n)$，就做完了。

```cpp
const int N = 500005;
const long long mod = 1000000007;

int n, als[N], ars[N], bls[N], brs[N], alt[N], blt[N], art[N], brt[N], fa[N], fb[N], rta, rtb;
long long dpa[N][2], dpb[N][2];

inline void Read() {
    n = qread();
    for (int i = 1;i <= n;i++) {
        fa[i] = qread();
        if (fa[i] != -1 && fa[i] < i) ars[fa[i]] = i;
        else if (fa[i] != -1 && fa[i] > i) als[fa[i]] = i;
        else rta = i;
    }
    for (int i = 1;i <= n;i++) {
        fb[i] = qread();
        if (fb[i] != -1 && fb[i] < i) brs[fb[i]] = i;
        else if (fb[i] != -1 && fb[i] > i) bls[fb[i]] = i;
        else rtb = i;
    }
}

inline void DfsA(int u) {
    alt[u] = art[u] = u;
    dpa[u][0] = dpa[u][1] = 0;
    if (als[u]) {
        DfsA(als[u]);
        alt[u] = min(alt[u], alt[als[u]]);
        dpa[u][0] += dpa[als[u]][0];
        dpa[u][1] += art[als[u]] - alt[als[u]] + 1 + dpa[als[u]][0];
    }
    if (ars[u]) {
        DfsA(ars[u]);
        art[u] = max(art[u], art[ars[u]]);
        dpa[u][0] += art[ars[u]] - alt[ars[u]] + 1 + dpa[ars[u]][1];
        dpa[u][1] += dpa[ars[u]][1];
    }
}

inline void DfsB(int u) {
    blt[u] = brt[u] = u;
    dpb[u][0] = dpb[u][1] = 0;
    if (bls[u]) {
        DfsB(bls[u]);
        blt[u] = min(blt[u], blt[bls[u]]);
        dpb[u][0] += dpb[bls[u]][0];
        dpb[u][1] += brt[bls[u]] - blt[bls[u]] + 1 + dpb[bls[u]][0];
    }
    if (brs[u]) {
        DfsB(brs[u]);
        brt[u] = max(brt[u], brt[brs[u]]);
        dpb[u][0] += brt[brs[u]] - blt[brs[u]] + 1 + dpb[brs[u]][1];
        dpb[u][1] += dpb[brs[u]][1];
    }
    dpb[u][0] %= mod; dpb[u][1] %= mod;
}

inline long long Solve(int nda, int sgl, int sgr, int flg, int ndb) {
    if (sgl > sgr) {
        sgl = sgr = -1;
        flg = 0;
    }
    long long res = -1;
    if (flg == 0) {
        if (nda == ndb) {
            long long ans = 0;
            if (als[nda]) ans += Solve(als[nda], -1, -1, 0, bls[ndb]);
            if (ars[nda]) ans += Solve(ars[nda], -1, -1, 0, brs[ndb]);
            res = ans % mod;
        } else if (nda < ndb) {
            int u = nda;
            long long ans = 0;
            while (u < ndb) {
                u = ars[u];
                if (als[u]) ans += dpa[als[u]][0] + art[als[u]] - alt[als[u]] + 1;
            }
            int l = nda, r = u;
            ans += ndb - nda;
            if (als[nda]) ans += Solve(als[nda], l, ndb - 1, 2, bls[ndb]);
            else ans += dpb[bls[ndb]][0];
            if (ars[u]) ans += Solve(ars[u], ndb + 1, r, 1, brs[ndb]);
            else ans += dpb[brs[ndb]][1];
            res = ans % mod;
        } else if (nda > ndb) {
            int u = nda;
            long long ans = 0;
            while (u > ndb) {
                u = als[u];
                if (ars[u]) ans += dpa[ars[u]][1] + art[ars[u]] - alt[ars[u]] + 1;
            }
            int l = u, r = nda;
            ans += nda - ndb;
            if (als[u]) ans += Solve(als[u], l, ndb - 1, 2, bls[ndb]);
            else ans += dpb[bls[ndb]][0];
            if (ars[nda]) ans += Solve(ars[nda], ndb + 1, r, 1, brs[ndb]);
            else ans += dpb[brs[ndb]][1];
            res = ans % mod;
        }
    } else if (flg == 1) {
        if (sgl <= ndb && ndb <= sgr) res = (ndb - sgl + dpb[bls[ndb]][0] + Solve(nda, ndb + 1, sgr, 1, brs[ndb])) % mod;
        else {
            int u = nda;
            long long ans = 0;
            while (u < ndb) {
                if (als[u]) ans += dpa[als[u]][0] + art[als[u]] - alt[als[u]] + 1;
                u = ars[u];
            }
            if (als[u]) ans += dpa[als[u]][0] + art[als[u]] - alt[als[u]] + 1;
            u = ars[u];
            if (u == 0) res = (ans + dpb[ndb][1]) % mod;
            else res = (ans + Solve(u, sgl, fa[u], 1, ndb)) % mod;
        }
    } else {
        if (sgl <= ndb && ndb <= sgr) res = (sgr - ndb + dpb[brs[ndb]][1] + Solve(nda, sgl, ndb - 1, 2, bls[ndb])) % mod;
        else {
            int u = nda;
            long long ans = 0;
            while (u > ndb) {
                if (ars[u]) ans += dpa[ars[u]][1] + art[ars[u]] - alt[ars[u]] + 1;
                u = als[u];
            }
            if (ars[u]) ans += dpa[ars[u]][1] + art[ars[u]] - alt[ars[u]] + 1;
            u = als[u];
            if (u == 0) res = (ans + dpb[ndb][0]) % mod;
            else res = (ans + Solve(u, fa[u], sgr, 2, ndb)) % mod;
        }
    }
    return (res % mod + mod) % mod;
}
```









---

## 作者：qiuzx (赞：0)

# P9103 - Bardzo skomplikowany test

## 题意

给定两棵 $n$ 个点的二叉搜索树 A 和 B，一次操作可以对 A 进行一次右旋/左旋操作，但要求被旋转上去的点没有右/左儿子。求将 A 转化为 B 的最小步数，对 $10^9+7$ 取模。

## 思路

首先我们必然会先将两棵树的根变得一样，并且在此过程中无需考虑别的事情，因为我们把根转到位之后会分解成左右两个子问题，如果我们在前面提前进行操作那完全可以在这之后把操作原封不动地进行，必然不会更劣。所以我们考虑如何计算把一个点转到根的代价。

注意到这种左右旋转的操作本质上是把一条链在树上滑来滑去。那么我们在想把一个点向上旋转的时候必然要先把它和上面方向冲突的一侧搞成一条链，搞完了才能把这一整条链滑到另一侧去。不妨假设我们需要把点 $x$ 向右上依次旋转至点 $v_1,v_2,\cdots ,v_k$，则我们首先需要把 $x,v_1,\cdots,v_{k-1}$ 的右子树都转成一条全部只有右儿子的链，然后把这些链依次向左滑到底，这样如果我们考察 $v_k$ 的左子树，会形如一条很长的向左的链下面挂着 $x$ 和它原来的左子树。这样我们再把整条左链向右滑就可以把 $x$ 归位了。这里我们必须要对极长的一条这样的链一起处理，否则会造成步数的浪费（我们会先把 $x$ 向右滑紧接着又滑回去）。这样我们把 $x$ 到根的链剖分成若干个极长的方向一致的链分开处理即可，显然此时链之间不能合并，因此这样做一定是最优的。

现在我们已经解决了 $x$ 到根的问题，我们需要分开解决左右两侧的子问题。但此时的问题是树的结构已经不是原来那样了，此时形如上面一条链下面挂一个子树。如果我们直接尝试对解决这个可能比较困难，因此我们需要进行一些转化。注意到我们没有对 B 树进行操作，而显然操作是对称的，因此我们考虑把 B 子树通过旋转变成 A 子树的样子。这样就可以用和刚刚类似的方式解决。由于在这种情况下 A 要么是最小值为根，要么是最大值为根，那么 B 也一定是这样的，所以此时 B 也长得形如链挂子树的形态，这样我们把两棵树链的公共部分删去即可转化为一棵正常的子树和一棵特别的子树的一样的子问题了。

现在还剩下的唯一问题就是如何求将一个子树变成一条链的步数。这个相比于刚刚的问题是容易的，可以直接通过 dp 求解，从子树的答案转移过来即可。

这样我们不断递归便可解决原问题，由于我们一个点向上旋转一次会使得链的长度至少 $+1$，而链的长度和我们枚举的量没有关系，因此我们这样做的总复杂度是 $O(n)$ 的。细节比较多，主要在于删除链相交部分的时候如果删空了则需要将节点更新为子树的根。

[代码](https://www.luogu.com.cn/paste/m82vizco)

---

