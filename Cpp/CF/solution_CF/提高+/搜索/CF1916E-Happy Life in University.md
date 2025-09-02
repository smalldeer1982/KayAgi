# Happy Life in University

## 题目描述

Egor and his friend Arseniy are finishing school this year and will soon enter university. And since they are very responsible guys, they have started preparing for admission already.

First of all, they decided to take care of where they will live for the long four years of study, and after visiting the university's website, they found out that the university dormitory can be represented as a root tree with $ n $ vertices with the root at vertex $ 1 $ . In the tree, each vertex represents a recreation with some type of activity $ a_i $ . The friends need to choose $ 2 $ recreations (not necessarily different) in which they will settle. The guys are convinced that the more the value of the following function $ f(u, v) = diff(u, lca(u, v)) \cdot diff(v, lca(u, v)) $ , the more fun their life will be. Help Egor and Arseniy and find the maximum value of $ f(u, v) $ among all pairs of recreations!

 $ ^{\dagger} diff(u, v) $ — the number of different activities listed on the simple path from vertex $ u $ to vertex $ v $ .

 $ ^{\dagger} lca(u, v) $ — a vertex $ p $ such that it is at the maximum distance from the root and is a parent of both vertex $ u $ and vertex $ v $ .

## 说明/提示

Consider the fourth test case. The tree has the following structure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1916E/310c7cd8a93a46df2248a6a8b87aa515f4626d82.png)  All recreations are colored. The same colors mean that the activities in the recreations match. Consider the pair of vertices $ (11, 12) $ , $ lca(11, 12) = 1 $ . Write down all activities on the path from $ 11 $ to $ 1 $ — $ [11, 5, 1, 11] $ , among them there are $ 3 $ different activities, so $ diff(11, 1) = 3 $ . Also write down all activities on the path from $ 12 $ to $ 1 $ — $ [7, 8, 2, 11] $ , among them there are $ 4 $ different activities, so $ diff(12, 1) = 4 $ . We get that $ f(11, 12) = diff(12, 1) \cdot diff(11, 1) = 4 \cdot 3 = 12 $ , which is the answer for this tree. It can be shown that a better answer is impossible to obtain.

## 样例 #1

### 输入

```
4
2
1
1 2
7
1 1 2 2 3 3
6 5 2 3 6 5 6
13
1 1 1 2 2 2 3 3 4 5 6 6
2 2 2 1 4 9 7 2 5 2 1 11 2
12
1 1 1 2 2 3 4 4 7 7 6
11 2 1 11 12 8 5 8 8 5 11 7```

### 输出

```
2
9
9
12```

# 题解

## 作者：TernaryTree (赞：20)

想题五分钟，卡常五小时/fn/fn/fn/oh/oh/oh 诋毁出题人！！

**upd 2024.1.10：我错了对不起出题人，我深深忏悔，原因是我下面第一份写的看似正确的代码实际上复杂度假了。**

个人觉得比 D 简单几十倍啊，D 可以定性为：天赋哥题。相比之下这个题就比较不需要脑子。

---

我们考虑怎么去数一条自上而下的链上的不同权值数量，这个是非常非常经典的 trick 啊：记录 $lst_u$ 表示 $u$ 往上跳达到的第一个权值与其相同的结点，则一条自上而下的链 $u\to v$ 上权值的数量就是 $u\to v$ 这条链上 $lst$ 在 $u$ 上面的结点个数。这个 $lst$ 我们可以 dfs 一次去算出来。

```cpp
void dfs1(int u) {
	int l = bk[a[u]];
	lst[u] = l;
	bk[a[u]] = u;
	for (int v : g[u]) dfs1(v);
	bk[a[u]] = l;
}
```

考虑去枚举这个 $lca$，然后考虑去维护一下子树里面每个点到当前 $lca$ 的权值种数 $cnt_i$，即每个点到 $lca$ 的路径上有多少个点在 $lca$ 之上。我们考虑把递推式地维护，即从 $fa$ 来转移到 $u$，容易发现相当于把 $lst=fa$ 的点的子树内 $cnt_i$ 全部加一；查询就是查各个子树内点 $cnt$ 的最大值减去 $cnt_{fa}$，即查询链和。这也是经典问题了，我们 dfs 一下处理出每个点被遍历到的时间，那么一个子树内的时间一定是连续的，我们就可以用区间加区间 $\max$ 的一个线段树去维护之。每个点只会被加一次减一次查询两次，复杂度是严格的 $\Theta(n\log n)$。

```cpp
void dfs1(int u) {
	dfn[u] = ++idx, siz[u] = 1;
	p[lst[u] = bk[a[u]]].push_back(u);
	int l = bk[a[u]];
	bk[a[u]] = u;
	for (int v : g[u]) dfs1(v), siz[u] += siz[v];
	bk[a[u]] = l;
}

void dfs2(int u, int fa) {
	for (int y : p[fa]) add(rt, dfn[y], dfn[y] + siz[y] - 1, 1);
	int mx = 1, sc = 1;
	int q = fa ? query(rt, dfn[fa], dfn[fa]) : 0;
	for (int v : g[u]) {
		int y = query(rt, dfn[v], dfn[v] + siz[v] - 1) - q;
		if (y > mx) sc = mx, mx = y;
		else if (y > sc) sc = y;
	}
	for (int v : g[u]) dfs2(v, u);
	if ((ll) mx * sc > ans) ans = (ll) mx * sc;
	for (int y : p[fa]) add(rt, dfn[y], dfn[y] + siz[y] - 1, -1);
}
```

然而善良美好的出题人并不愿意让我们这样轻而易举地通过这道题，所以在这样一个线段树跑 $3\times 10^5$ 的时候贴心地为我们设置了 $1s$ 的时限，使得我们最终止步于 #35 号点。

**upd：上面那份代码复杂度假了。可以不用看了。**

卡常！经过我[真挚诚恳的求问](https://www.luogu.com.cn/discuss/754236)，最终得到了 $\text{{D}\red{itaMirika}}$ 大神的通过代码，我对着修改了几处地方，直接 $436ms$ 通过了此题。

具体地：

```cpp
void dfs1(int u) {
	dfn[u] = ++idx, siz[u] = 1;
	int l = bk[a[u]];
	lst[u] = l;
	bk[a[u]] = u;
	for (int v : g[u]) dfs1(v), siz[u] += siz[v];
	bk[a[u]] = l;
}

void dfs2(int u, int fa) {
	for (int v : g[u]) dfs2(v, u);
	add(rt, dfn[u], dfn[u] + siz[u] - 1, 1);
	for (int y : p[u]) add(rt, dfn[y], dfn[y] + siz[y] - 1, -1);
	int mx = 1, sc = 1;
	int q = fa ? query(rt, dfn[fa], dfn[fa]) : 0;
	for (int v : g[u]) {
		int y = query(rt, dfn[v], dfn[v] + siz[v] - 1) - q;
		if (y > mx) sc = mx, mx = y;
		else if (y > sc) sc = y;
	}
	if ((ll) mx * sc > ans) ans = (ll) mx * sc;
	p[lst[u]].push_back(u);
}
```

首先把儿子优先扔下去 dfs，然后把 $u$ 子树 $+1$，因为儿子优先递归，所以相当于这个点子树里面所有点的子树都 $+1$；然后我们把 $lst=u$ 的点的子树全部 $-1$，实际上进行到 $u$ 的时候就是 $u$ 子树内所有 $lst$ 在 $u$ 子树内的点的子树全部 $-1$，那么剩下的没被 $-1$ 的只有可能 $lst$ 在 $u$ 的上面；这样足以通过此题。

老话说得好：细节决定成败。常数这种东西看似细枝末节，而许许多多的人都在编写代码的过程中忽略了自己的常数，而这样的小细节才是出题人要求选手达到的境界。这也侧面反映出作为一名 OI 选手，我的 OI 造诣和自我修养不足，理解不了这种内在的阳春白雪的高雅艺术，只能看到外表的辞藻堆砌，参不透其中深奥的精神内核，我整个人的层次就卡在这里了，只能度过一个相对失败的人生。希望大家引以为戒。在此，我深深忏悔，并收回文章开头对出题人的诋毁，非常好题目，为出题人点赞。

2024.1.10 反转了，复杂度假了。老话说得好，复杂度决定成败，后面忘了，希望大家能自行补全。

---

## 作者：sunkuangzheng (赞：11)

考虑在 $d = \operatorname{lca}(u,v)$ 处统计答案，显然 $d$ 固定时，$u,v$ 应该选择两个不同子树内的叶子节点，那基本思路就是数据结构维护每个叶子到 $d$ 的路径上的颜色数量。

我们递归处理，假设已经处理完了 $d$ 的所有子树，给所有路径新加入一个 $d$，考虑会发生什么变化。下面的图片中，设 $d = 1$，加粗的点表示 $a_x = a_1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nogxyi1q.png)

显然的，$2$ 号点和 $8$ 号点子树内的点贡献没有增加，其余点贡献 $+1$，成称无贡献的点是关键点。发现我们并不关心那些已经在某个关键点子树内的关键点（例如点 $5$ 和点 $10$），它们没有意义，这和序列区间数颜色很相似。为了方便处理，我们转化贡献形式：首先 $d$ 子树内所有点 $+1$，然后给不存在除 $d$ 外关键点使得其为点 $u$ 的祖先的关键点 $u$ 子树 $-1$。然后，查询所有儿子子树区间的最大值，选择最大的两个相乘即可。区间加，区间 $\max$ 可以线段树维护。

现在的核心问题是怎么维护这么一个点集。同样的，假设当前在点 $d$，所有儿子点集已经维护完成。设 $p_x$ 表示当前 $a_u = x$ 的点 $u$ 的集合，**按 dfs 序排序**，我们二分找到 $u$，遍历子树内的 $p_x$ 内的点。显然这些点都是满足 $-1$ 要求的，因为无意义的关键点已经在儿子处被删除，那么直接在线段树上 $-1$。遍历完后，删除子树内所有除 $d$ 外的关键点，因为它们会随着退出 $d$ 的子树而变得无用。

每个点只会被遍历一次，删除一次，所以 set 部分时间复杂度 $\mathcal O(n \log n)$。修改总次数是 $\mathcal O(n)$ 级别的，所以这部分复杂度也是 $\mathcal O(n \log n)$。

删除了注释的赛时代码：

```cpp
/**
 *    author: sunkuangzheng
 *    created: 31.12.2023 00:18:56
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,fa[N],a[N],dfn1[N],nfd[N],dfn2[N],siz1[N],siz2[N],ct1,ct2,t[N*4],tg[N*4];vector<int> g[N];set<int> p[N];ll ans;
void cg(int s,int k){tg[s] += k,t[s] += k;}
void pd(int s){cg(s*2,tg[s]),cg(s*2+1,tg[s]),tg[s] = 0;}
void upd(int s,int l,int r,int ql,int qr,int k){
    assert(ql <= qr);
    if(ql <= l && r <= qr) return cg(s,k);
    int mid = (l + r) / 2;pd(s);
    if(ql <= mid) upd(s*2,l,mid,ql,qr,k); if(qr > mid) upd(s*2+1,mid+1,r,ql,qr,k);
    t[s] = max(t[s*2],t[s*2+1]);
}int qry(int s,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return t[s];
    int mid = (l + r) / 2,ans = 0; pd(s);
    if(ql <= mid) ans = max(ans,qry(s*2,l,mid,ql,qr));
    if(qr > mid) ans = max(ans,qry(s*2+1,mid+1,r,ql,qr));
    return ans;
}void dfs(int u){
    dfn1[u] = ++ct1,siz1[u] = 1,dfn2[u] = (g[u].size() ? 1e9 : ++ct2),siz2[u] = (!g[u].size());
    nfd[ct1] = u,p[a[u]].insert(dfn1[u]);
    for(int v : g[u]) dfs(v),siz1[u] += siz1[v],siz2[u] += siz2[v],dfn2[u] = min(dfn2[u],dfn2[v]);
}void dfs2(int u){
    for(int v : g[u]) dfs2(v);vector<int> acc;
    upd(1,1,n,dfn2[u],dfn2[u] + siz2[u] - 1,1);
    auto it = p[a[u]].upper_bound(dfn1[u]);
    for(;it != p[a[u]].end();it ++){
        if(*it > dfn1[u] + siz1[u] - 1) break;
        int v = *it; acc.push_back(v);
        upd(1,1,n,dfn2[nfd[v]],dfn2[nfd[v]] + siz2[nfd[v]] - 1,-1);
    }for(int i : acc) p[a[u]].erase(i);
    vector<int> cjr;
    for(int v : g[u]) cjr.push_back(qry(1,1,n,dfn2[v],dfn2[v] + siz2[v] - 1));
    sort(cjr.begin(),cjr.end(),[&](int x,int y){return x > y;});
    if(!cjr.size()) return ;
    ans = max(ans,(ll)cjr.front());
    if(cjr.size() >= 2) ans = max(ans,1ll * cjr[0] * cjr[1]);
}void los(){
    cin >> n,ct1 = ct2 = 0,ans = 1;
    for(int i = 1;i <= 4*n;i ++) t[i] = tg[i] = 0;
    for(int i = 1;i <= n;i ++) g[i].clear(),p[i].clear();
    for(int i = 2;i <= n;i ++) cin >> fa[i],g[fa[i]].push_back(i);
    for(int i = 1;i <= n;i ++) cin >> a[i];dfs(1),dfs2(1);
    cout << ans << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：forgotmyhandle (赞：6)

~~关于我赛时线段树忘了开四倍空间导致白吃了一发罚时这档逝~~

[原题传送门](http://codeforces.com/problemset/problem/1916/E)

[你谷传送门](https://www.luogu.com.cn/problem/CF1916E)
### 约定
$x$ 子树内的叶子称为 $x$ 的叶子。

与 $x$ 颜色相同的点称为 $x$ 的同色点或 $x$ 色点。

所有在 $x$ 子树内的、到 $x$ 的路径上（两端不含）没有 $x$ 的同色点的 $x$ 的同色点称为 $x$ 的极浅同色点。

## 分析
首先考虑两个点要是没有祖先关系，那必然是选择两个叶子最优。想到枚举 LCA 算贡献，则在每个点 $x$ 得知道 $x$ 的所有叶子到 $x$ 的 diff 值。我们考虑在 dfs 回溯的时候维护这个东西。在我们回溯到一个点 $x$ 的时候，$x$ 的叶子到 $x$ 对应的儿子的 diff 值已经有了。我们接下来要做的就是把 $x$ 的所有 到 $x$ 的路径上没有 $x$ 的同色点的叶子 的 diff 值都加 $1$。为此，我们可以先把 $x$ 的所有叶子的 diff 值都加 $1$，然后枚举 $x$ 的所有极浅同色点，把它们的叶子的 diff 值都减 $1$。于是问题转变成求 $x$ 的所有极浅同色点。

我们反过来考虑。$y$ 是 $x$ 的其中一个极浅同色点，等价于从 $y$ 往上跳，遇到的第一个 $y$ 色点是 $x$。于是我们可以在 dfs 的时候维护一个栈，其中放着所有当前点 $x$ 的祖先。然后我们就只需要在这个栈里找最后一个颜色与 $x$ 相同的点 $y$，那么 $x$ 就一定是 $y$ 的其中一个极浅同色点。对每种颜色开一个栈，这样就可以很方便地找到最后一个当前点的同色点。

求出每个点 $x$ 到其所有叶子的 diff 值之后，我们枚举 $x$ 的所有儿子 $y$，对于每个 $y$ 找到 $x$ 到其叶子的 diff 的最大值，然后把这些最大值中的最大值和次大值相乘就是 $x$ 作为 LCA 的最大贡献。

然后我们考虑两个点如果有祖先关系，那必然是一个是根，一个是叶子。直接找根到所有叶子的 diff 最大值即可。

最后还剩下把 $x$ 的所有叶子的 diff 加 / 减 $1$，求子树内叶子 diff 值 max。直接对叶子的 dfs 序开一个线段树，支持区间加区间 max 就没了。

至于为什么对每个点枚举所有它的极浅同色点不会 T，那是因为每个点至多是一个点的极浅同色点。所以每个点最多被枚举一次。

总复杂度是 $O(n\log n)$。

## 代码
```cpp
#include <iostream>
#include <cassert>
#include <vector>
#define ll long long
using namespace std;
vector<int> vec[300005];
vector<int> sm[300005];
int clr[300005];
int f[300005];
int head[300005], nxt[300005], to[300005], ecnt;
void add(int u, int v) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt; }
int L[300005], R[300005], ncnt;
ll ans = 1;
int lcnt = 0;
int n;
struct Segment_Tree {
    int mx[1200005], tg[1200005];
    inline void tag(int o, int t) { mx[o] += t, tg[o] += t; }
    inline void pushdown(int o) {
        if (!tg[o]) 
            return;
        tag(o << 1, tg[o]);
        tag(o << 1 | 1, tg[o]);
        tg[o] = 0;
    }
    inline void pushup(int o) { mx[o] = max(mx[o << 1], mx[o << 1 | 1]); }
    void Clear(int o, int l, int r) {
        mx[o] = tg[o] = 0;
        if (l == r) 
            return;
        int mid = (l + r) >> 1;
        Clear(o << 1, l, mid);
        Clear(o << 1 | 1, mid + 1, r);
    }
    void Add(int o, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) {
            tag(o, v);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (L <= mid) 
            Add(o << 1, l, mid, L, R, v);
        if (R > mid) 
            Add(o << 1 | 1, mid + 1, r, L, R, v);
        pushup(o);
    }
    int Query(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) 
            return mx[o];
        pushdown(o);
        int mid = (l + r) >> 1;
        if (R <= mid) 
            return Query(o << 1, l, mid, L, R);
        else if (L > mid) 
            return Query(o << 1 | 1, mid + 1, r, L, R);
        else 
            return max(Query(o << 1, l, mid, L, R), Query(o << 1 | 1, mid + 1, r, L, R));
    }
} seg;
void dfs(int x) {
    if (!vec[clr[x]].empty()) {
        int t = vec[clr[x]].size() * 1 - 1;
        sm[vec[clr[x]][t]].push_back(x);
    }
    if (!head[x]) {
        L[x] = R[x] = ++ncnt;
        seg.Add(1, 1, lcnt, ncnt, ncnt, 1);
        return;
    }
    vec[clr[x]].push_back(x);
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        R[x] = R[v];
        L[x] = (i == head[x] ? L[v] : L[x]);
    }
    vec[clr[x]].pop_back();
    seg.Add(1, 1, lcnt, L[x], R[x], 1);
    for (auto v : sm[x]) seg.Add(1, 1, lcnt, L[v], R[v], -1);
    int mx = 1, smx = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        int t = seg.Query(1, 1, lcnt, L[v], R[v]);
        if (t >= mx)
            smx = mx, mx = t;
        else if (t > smx) 
            smx = t;
    }
    ans = max(ans, 1ll * mx * smx);
}
signed main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 0; i <= n + 1; i++) {
            head[i] = 0;
            vec[i].clear();
            sm[i].clear();
            L[i] = R[i] = 0;
        }
        ans = 1;
        lcnt = ncnt = ecnt = 0;
         for (int i = 2; i <= n; i++) {
            cin >> f[i];
            add(f[i], i);
        }
        for (int i = 1; i <= n; i++) lcnt += (head[i] == 0);
        for (int i = 1; i <= n; i++) cin >> clr[i];
        dfs(1);
        cout << ans << "\n";
        seg.Clear(1, 1, lcnt);
    }
    return 0;
}
```

---

## 作者：Lucky_Xiang (赞：5)

## 题目

[CF1916E](https://www.luogu.com.cn/problem/CF1916E)

## 分析

一个很直观的想法是枚举 lca，并统计儿子中颜色种类最多的两条路径。很明显路径延伸到叶子节点一定是不劣的，不妨维护到达每个叶子节点的路径颜色种类。

设 $u$ 节点的颜色为 $a_u$，$u$ 子树内 dfn 最小的叶子节点为 $L_u$，最大的为 $R_u$（$L_u$ 和 $R_u$ 都是指将叶子节点按 dfn 顺序重新编号的排名）。如果 $v$ 是 $u$ 的儿子，而 $x$ 节点在 $v$ 的子树内，且 $a_x=a_u$，则加上 $a_u$ 后到达叶子节点 $L_x\sim R_x$ 的路径颜色种类不变。这就等价于将 $L_u\sim R_u$ 的颜色种类加 $1$，再将所有 $L_x\sim R_x$ 的颜色种类减 $1$。

为了防止重复计算，可以钦定 $u\sim x$ 的路径（不包括端点）中不存在颜色 $a_u$。可以发现满足条件的 $x$ 的 dfn 是在一定区间内的。具体的，$\text{dfn}_v\le \text{dfn}_x< \text{dfn}_v+\text{sz}_v$。其中 $\text{sz}_v$ 表示 $v$ 子树的大小。这就启示我们每种颜色开一个 set，操作时暴力查询 $x$ 的位置，并用线段树维护区间加操作。在查询完 $u$ 中的所有 $x$ 后，将它们全部删除，并插入 $u$。这样插入和删除都是 $O(n)$ 的，总时间复杂度 $O(n\log n)$。

~~比赛结束 8 分钟后调出来了，我是小丑。~~

## 代码

[Code](https://codeforces.com/contest/1916/submission/239740362)

---

## 作者：shinkuu (赞：3)

是一道很标准的 CF data structure。

考虑 dfs 下去，维护每一个点的 diff 值，对于每一个点 $x$，搜完它的子树，回溯到它的时候统计所有 $\operatorname{lca}(u,v)=x$ 的 $f(u,v)$ 的最大值。那我们就要维护每个 $u$ 的 $\operatorname{diff}(u,x)$。

怎么维护呢？我们在回溯的时候同时加上该点对它的子树内的点的 $\operatorname{diff}$ 的影响，即子树 $+1$。但是有些位置可能已经出现过了同样颜色，这些位置又要减掉。设当前回溯到了点 $x$，则一个同色的 $u$ 的子树要 $-1$ 的条件就是 $x$ 到 $u$ 的路径上没有和 $u$ 同色的点。这个可以简单预处理出来。然后上 SGT 维护区间加，区间最值。

时间复杂度 $O(n\log n)$。感觉好板，*2200 不能再高了。

WA on test 4 是 $n=1$。

code：

```cpp
int n,m,cur,c[N],dfn[N],siz[N];ll ans;
int tot,head[N];
struct node{int to,nxt;}e[N<<1];
il void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
vector<int> g[N],h[N];
struct SGT{
	int tr[N<<2],tag[N<<2];
	il void pushup(int o){tr[o]=max(tr[o<<1],tr[o<<1|1]);}
	il void reset(int o,int k){tag[o]+=k,tr[o]+=k;}
	il void pushdown(int o){reset(o<<1,tag[o]),reset(o<<1|1,tag[o]),tag[o]=0;}
	void update(int l,int r,int o,int x,int y,int k){
		if(l>=x&&r<=y)return reset(o,k);
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,o<<1,x,y,k);
		if(y>mid)update(mid+1,r,o<<1|1,x,y,k);
		pushup(o);
	}
	int query(int l,int r,int o,int x,int y){
		if(r<x||l>y)return -inf;
		if(l>=x&&r<=y)return tr[o];
		pushdown(o);
		int mid=(l+r)>>1;
		return max(query(l,mid,o<<1,x,y),query(mid+1,r,o<<1|1,x,y));
	}
}T;
void dfs1(int u,int f){
	dfn[u]=++cur,siz[u]=1;
	go(i,u){
		int v=e[i].to;
		dfs1(v,u),siz[u]+=siz[v];
	}
}
void dfs2(int u,int f){
	if(g[c[u]].size())h[g[c[u]].back()].eb(u);
	g[c[u]].eb(u);
	go(i,u){
		int v=e[i].to;
		dfs2(v,u);
	}
	g[c[u]].pop_back();
	T.update(1,n,1,dfn[u],dfn[u]+siz[u]-1,1);
	for(int i:h[u])T.update(1,n,1,dfn[i],dfn[i]+siz[i]-1,-1);
	int mx=-inf,secmx=-inf;
	go(i,u){
		int v=e[i].to,x=T.query(1,n,1,dfn[v],dfn[v]+siz[v]-1);
		if(x>mx)secmx=mx,mx=x;
		else if(x>secmx)secmx=x;
	}
	if(secmx<0)ans=max(ans,1ll*mx);
	else ans=max(ans,1ll*mx*secmx);
}
void Yorushika(){
	scanf("%d",&n);
	tot=cur=0,ans=1;
	rep(i,1,n)g[i].clear(),h[i].clear(),head[i]=0;
	rep(i,1,n*4)T.tr[i]=T.tag[i]=0;
	rep(v,2,n){
		int u;scanf("%d",&u);
		add(u,v);
	}
	rep(i,1,n)scanf("%d",&c[i]);
	dfs1(1,0),dfs2(1,0);
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：henrytb (赞：2)

小丑做法，喜提最劣解。

容易在 dfs 的过程中使用线段树维护出到达某个点 $u$ 时，$u$ 到其所有祖先 $f$ 的路径颜色数。

因此，某个点 $u$ 向子树内的颜色数最大值，即为 dfs 完 $u$ 的整棵子树后 $u$ 位置的历史最大值。

使用支持区间加、单点查历史最值的线段树即可。

900 多毫秒过的，赛时很担心 fst。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 3e5 + 5;
int _;
int n, m, a[N];
struct Segment {
    int l, r, hadd, add, mx, hmx;
} t[N << 2];
inline void pushup(int p) {
    t[p].mx = max(t[p << 1].mx, t[p << 1 | 1].mx);
    t[p].hmx = max(t[p << 1].hmx, t[p << 1 | 1].hmx);
}
void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r; t[p].hadd = t[p].add = 0;
    if (l == r) {
        t[p].mx = t[p].hmx = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
inline void upd(int p, int hadd, int add) {
    t[p].hadd = max(t[p].hadd, t[p].add + hadd);
    t[p].add += add;
    t[p].hmx = max(t[p].hmx, t[p].mx + hadd);
    t[p].mx += add;
}
inline void pushdown(int p) {
    if (t[p].add || t[p].hadd) {
        upd(p << 1, t[p].hadd, t[p].add);
        upd(p << 1 | 1, t[p].hadd, t[p].add);
        t[p].add = t[p].hadd = 0;
    }
}
void modify(int p, int l, int r, int val) {
    if (l <= t[p].l && t[p].r <= r) {
        upd(p, val, val);
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    pushdown(p);
    if (l <= mid) modify(p << 1, l, r, val);
    if (mid < r) modify(p << 1 | 1, l, r, val);
    pushup(p);
}
void modify2(int p, int pos) {
    if (t[p].l == t[p].r) { t[p].hmx = t[p].mx; return; }
    int mid = (t[p].l + t[p].r) >> 1; pushdown(p);
    if (pos <= mid) modify2(p << 1, pos);
    else modify2(p << 1 | 1, pos);
    pushup(p);
}
int query(int p, int pos) {
    if (t[p].l == t[p].r) return t[p].hmx;
    int mid = (t[p].l + t[p].r) >> 1;
    pushdown(p);
    if (pos <= mid) return query(p << 1, pos);
    else return query(p << 1 | 1, pos);
}
vector<int> e[N];
int lst[N], dep[N], mx[N];
int anss;
void dfs(int u) {
    int ls = lst[a[u]];
    modify(1, ls + 1, dep[u], 1);
    lst[a[u]] = dep[u];
    int mxx = 1, smx = 1;
    for (auto &v: e[u]) {
        modify2(1, dep[u]);
        dep[v] = dep[u] + 1;
        dfs(v);
        int tmp = query(1, dep[u]);
        if (tmp > mxx) smx = mxx, mxx = tmp;
        else if (tmp > smx) smx = tmp;
    }
    anss = max(anss, mxx * smx);
    mx[u] = mxx;
    modify(1, ls + 1, dep[u], -1);
    modify2(1, dep[u]);
    lst[a[u]] = ls;
}
signed main() {
    for (scanf("%lld", &_); _; --_) {
        scanf("%lld", &n);
        rep(i, 1, n) e[i].clear();
        build(1, 1, n);
        rep(i, 2, n) {
            int x;
            scanf("%lld", &x);
            e[x].emplace_back(i);
        }
        rep(i, 1, n) scanf("%lld", &a[i]);
        dep[1] = 1;
        anss = 1;
        dfs(1);
        printf("%lld\n", anss);
    }
    return 0;
}
```

---

## 作者：灵乌路空 (赞：1)


首先特判答案 $f(a, b)$ 满足 $\operatorname{lca} = a$ 的情况，显然此时令 $a=1$ 是最优的，简单 dfs 求所有节点到 1 路径上颜色种类数即可。

然后考虑 $\operatorname{lca} \not= a$ 的情况。一个典中典的思考方向是考虑枚举答案式子中的 $\operatorname{lca}=u$，即考虑维护 $\operatorname{subtree}(u)$ 到 $u$ 路径上的颜色种类数，找到位于**不同子树中**颜色种类数最大和次大的节点，则它们的颜色种类数的乘积即为 $\operatorname{lca}=u$ 时所有路径中对答案贡献的最大值。

发现要查询的是子树中的最值，另一个典中典想法是考虑先将树按 dfs 序转化为序列，子树变成了一段连续的区间，令序列中每个位置为对应节点到当前枚举的 $\operatorname{lca}$ 路径中颜色种类数，维护和查询区间最大值即可。考虑用 dfs 枚举 $\operatorname{lca}$，并同时用线段树维护上述区间最值，则对于节点 $u$ 枚举所有儿子 $s$ 并查询 $\operatorname{subtree}(s)$ 对应的区间的最值，取最大值和次大值即为 $\operatorname{lca}=u$ 时贡献的最大值。

然后考虑具体如何在 dfs 过程中维护线段树。$\operatorname{lca}=1$ 对应的线段树可以在预处理后直接建出来，仅需考虑在父节点 $u$ 向下转移到子节点时如何削除 $u$ 的影响来维护路径的颜色种类数，即令子树中某些位置对应的值 $-1$。手玩下发现，设点集 $\{ x \}_u$ 满足：
- $x$ 在 $u$ 的子树中。
- $x$ 与 $u$ 同色。
- 路径 $u\rightarrow x$ 上没有其他同色节点。  
  
则在转移后会影响的节点集合即为：$\operatorname{subtree}(u) - \sum_{v\in \{x\}_u} \operatorname{subtree}(v)$。

显然 $\{x\}$ 中节点的子树均不相交，则 $\operatorname{subtree}(v)$ 在序列中对应 $|\{x\}_u|$ 个不相交的连续区间，被影响的节点集合即这些区间的补集，显然为不多于 $|\{x\}_u|+1$ 个不相交的连续区间。考虑点集 $\{x\}_u$ 的实际意义显然有 $\sum_u |\{x\}_u|< n$，则转移时影响到的区间数量之和为 $O(n)$ 级别，直接枚举区间进行线段树区间加维护即可。在回溯时进行反向操作还原 $u$ 的影响即可。

上述点集 $\{x\}_u$ 同样可以预处理，仅需在 dfs 预处理过程中顺带维护当前节点的祖先中距离最近的每种颜色的节点，将当前枚举到的节点加入到距离最近的同色祖先的 $\{x\}$ 的集合中即可。

总时空复杂度 $O(n\log n)$ 级别。

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 3e5 + 10;
//=============================================================
int n, a[kN];
int datanum, data[kN];
int edgenum, head[kN], v[kN], ne[kN];
int bnum, L[kN], R[kN], b[kN];

int cnt[kN], num[kN], last[kN];
std::vector <int> next[kN];
int sonnum, son[kN];
LL ans;
//=============================================================
inline int read() {
  int f = 1, w = 0; char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
  for (; isdigit(ch); ch = getchar()) w = (w << 3) + (w << 1) + (ch ^ '0'); 
  return f * w;
}
namespace Seg {
  #define ls (now_<<1)
  #define rs (now_<<1|1)
  #define mid ((L_+R_)>>1)
  const int kNode = kN << 2;
  int v[kNode], tag[kNode];
  void Pushup(int now_) {
    v[now_] = std::max(v[ls], v[rs]);
  }
  void Pushdown(int now_) {
    v[ls] += tag[now_], v[rs] += tag[now_];
    tag[ls] += tag[now_], tag[rs] += tag[now_];
    tag[now_] = 0;
  }
  void Build(int now_, int L_, int R_) {
    v[now_] = tag[now_] = 0;
    if (L_ == R_) {
      v[now_] = num[b[L_]];
      return ;
    }
    Build(ls, L_, mid), Build(rs, mid + 1, R_);
    Pushup(now_);
  }
  void Modify(int now_, int L_, int R_, int l_, int r_, int val_) {
    if (l_ <= L_ && R_ <= r_) {
      v[now_] += val_;
      tag[now_] += val_;
      return ;
    } 
    if (tag[now_]) Pushdown(now_);
    if (l_ <= mid) Modify(ls, L_, mid, l_, r_, val_);
    if (r_ > mid) Modify(rs, mid + 1, R_, l_, r_, val_);
    Pushup(now_);
  }
  int Query(int now_, int L_, int R_, int l_, int r_) {
    if (l_ <= L_ && R_ <= r_) return v[now_];
    if (tag[now_]) Pushdown(now_);
    int ret = 0;
    if (l_ <= mid) ret = std::max(ret, Query(ls, L_, mid, l_, r_));
    if (r_ > mid) ret = std::max(ret, Query(rs, mid + 1, R_, l_, r_));
    return ret;
  }
  #undef ls
  #undef rs
  #undef mid
}
void Clear() {
  bnum = edgenum = datanum = 0;
  ans = 0;
  for (int i = 1; i <= n; ++ i) {
    head[i] = 0;
    L[i] = R[i] = 0;
    num[i] = cnt[i] = 0;
    next[i].clear();
  }
}
void Add(int u_, int v_) {
  v[++ edgenum] = v_;
  ne[edgenum] = head[u_];
  head[u_] = edgenum;
}
void Init() {
  n = read();
  Clear();

  for (int i = 2; i <= n; ++ i) {
    int fa = read();
    Add(fa, i);
  }
  for (int i = 1; i <= n; ++ i) a[i] = data[i] = read();
  std::sort(data + 1, data + n + 1);
  datanum = std::unique(data + 1, data + n + 1) - data - 1;
  for (int i = 1; i <= n; ++ i) {
    a[i] = std::lower_bound(data + 1, data + datanum + 1, a[i]) - data;
  }
}
void Dfs1(int u_) {
  if ((++ cnt[a[u_]]) == 1) ++ num[u_];
  ans = std::max(ans, 1ll * num[u_]);
  L[u_] = ++ bnum;
  b[bnum] = u_;

  int temp = last[a[u_]];
  if (temp) next[temp].push_back(u_);
  last[a[u_]] = u_;

  for (int i = head[u_]; i; i = ne[i]) {
    num[v[i]] = num[u_]; 
    Dfs1(v[i]);
  }

  -- cnt[a[u_]];
  R[u_] = bnum;
  last[a[u_]] = temp;
}
void Dfs2(int u_) {
  sonnum = 0;
  for (int i = head[u_]; i; i = ne[i]) {
    son[++ sonnum] = Seg::Query(1, 1, n, L[v[i]], R[v[i]]);
  }
  std::sort(son + 1, son + sonnum + 1);
  ans = std::max(ans, 1ll * son[sonnum] * son[sonnum - 1]);
  
  int l_ = L[u_];
  for (auto x: next[u_]) {
    if (l_ <= L[x] - 1) Seg::Modify(1, 1, n, l_, L[x] - 1, -1);
    l_ = R[x] + 1;
  }
  if (l_ <= n) Seg::Modify(1, 1, n, l_, n, -1);
  
  for (int i = head[u_]; i; i = ne[i]) Dfs2(v[i]);

  l_ = L[u_];
  for (auto x: next[u_]) {
    if (l_ <= L[x] - 1) Seg::Modify(1, 1, n, l_, L[x] - 1, 1);
    l_ = R[x] + 1;
  }
  if (l_ <= n) Seg::Modify(1, 1, n, l_, n, 1);
}
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  int T = read();
  while (T --) {
    Init();
    Dfs1(1);
    Seg::Build(1, 1, n);
    Dfs2(1);
    printf("%lld\n", ans);
  } 
  return 0;
}
```

---

## 作者：Phartial (赞：1)

# CF1916E Happy Life in University 题解

考虑枚举 LCA $x$，则 $\operatorname{LCA}(u,v)=x$ 当且仅当 $u$ 和 $v$ 在 $x$ 的不同子树中。

我们需要对每棵子树 $x$ 维护其内部的点到 $x$ 的 diff 值，合并 $x$ 的子树时，我们可以先将以 $x$ 为根的子树的 diff 值加一，但这样会算重。

考虑额外维护每棵子树 $x$ 中颜色 $c$ 有哪些点**在其到 $x$ 的路径上没有重复颜色**，则我们可以先将 $x$ 的子树用启发式合并并到一起，于是其中颜色 $a_x$ 的满足在其到 $x$ 的路径上（不含 $x$）没有重复颜色的点就会在考虑 $x$ 时被算重，将以这些点为根的子树的 diff 值减一即可。

最后枚举 $x$ 的所有子树中 diff 值的最大值，统计出最大值和次大值即可。

由于处理完 $x$ 后我们不再需要 $x$ 的子树中的 diff 值，所以可以直接用一棵线段树维护 diff 值，子树加和子树 $\max$ 是 trival 的。

因为我只会用 map 套 vector 维护每棵子树中可能算重的节点颜色与编号，所以复杂度是两只 $\log$ 的，有无老哥能教教高妙单 $\log$ 做法/kel。

```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 3e5 + 1;

struct E {
  int mx, ta;
} t[kN << 2];
int n, fa[kN], a[kN], sz[kN], dn[kN], dc;
vector<int> e[kN];
map<int, vector<int>> mp[kN];
LL ans;

void Pu(int x) { t[x].mx = max(t[x * 2].mx, t[x * 2 + 1].mx); }
void Pt(int x, int v) { t[x].mx += v, t[x].ta += v; }
void Pd(int x) {
  Pt(x * 2, t[x].ta), Pt(x * 2 + 1, t[x].ta);
  t[x].ta = 0;
}

void B(int x, int l, int r) {
  t[x].mx = t[x].ta = 0;
  if (l == r) {
    return;
  }
  int m = l + r >> 1;
  B(x * 2, l, m), B(x * 2 + 1, m + 1, r);
}
void A(int x, int l, int r, int tl, int tr, int v) {
  if (l == tl && r == tr) {
    Pt(x, v);
    return;
  }
  Pd(x);
  int m = l + r >> 1;
  if (tl <= m) {
    A(x * 2, l, m, tl, min(m, tr), v);
  }
  if (m < tr) {
    A(x * 2 + 1, m + 1, r, max(m + 1, tl), tr, v);
  }
  Pu(x);
}
int Q(int x, int l, int r, int tl, int tr) {
  if (l == tl && r == tr) {
    return t[x].mx;
  }
  Pd(x);
  int m = l + r >> 1, s = 0;
  if (tl <= m) {
    s = max(s, Q(x * 2, l, m, tl, min(m, tr)));
  }
  if (m < tr) {
    s = max(s, Q(x * 2 + 1, m + 1, r, max(m + 1, tl), tr));
  }
  return s;
}

void D(int x) {
  sz[x] = 1, dn[x] = ++dc;
  for (int i : e[x]) {
    D(i);
    sz[x] += sz[i];
    if (mp[x].size() < mp[i].size()) {
      for (auto j : mp[x]) {
        auto &v = mp[i][j.first];
        for (int k : j.second) {
          v.push_back(k);
        }
      }
      mp[x] = move(mp[i]);
    } else {
      for (auto j : mp[i]) {
        auto &v = mp[x][j.first];
        for (int k : j.second) {
          v.push_back(k);
        }
      }
    }
  }
  A(1, 1, n, dn[x], dn[x] + sz[x] - 1, 1);
  vector<int> &l = mp[x][a[x]];
  for (int i : l) {
    A(1, 1, n, dn[i], dn[i] + sz[i] - 1, -1);
  }
  l.clear(), l.push_back(x);
  int mx = 1, se = 1;
  for (int i : e[x]) {
    int v = Q(1, 1, n, dn[i], dn[i] + sz[i] - 1);
    if (v >= mx) {
      se = mx, mx = v;
    } else {
      se = max(se, v);
    }
  }
  ans = max(ans, 1LL * mx * se);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int tt = 1;
  cin >> tt;
  for (; tt--;) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      e[i].clear(), mp[i].clear();
    }
    for (int i = 2; i <= n; ++i) {
      cin >> fa[i];
      e[fa[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    ans = dc = 0, B(1, 1, n);
    D(1);
    cout << ans << '\n';
  }
  return 0;
}
```


---

## 作者：DCH233 (赞：1)

首先发现这个问题是唬人的，实际上直接枚举 LCA，求出各个子树中叶子到 LCA 路径颜色数的最大值直接取最大次大值乘起来就行了。所以如果我们能够动态地维护出路径的颜色数的最大值这题就做完了。

从叶子到根做，每次直接给子树 $+1$。这当然是错的，因为我们求的是颜色数。那怎样才是对呢？一个朴素的想法是直接在算重的位置减去贡献。你发现暴力减去直接就是对的了，因为对每个点只有离他最近的和他颜色相同的祖先需要减去这棵子树的贡献，所以一共只会减 $O(n)$ 次。所以只需维护子树加减一和子树查最大值，可以线段树解决。总复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define sz(x) (int)x.size()
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

namespace IO {
#define isdigit(x) (x >= '0' && x <= '9')
template<typename T>
inline void read(T &x) {
  x = 0; char ch = getchar(); int f = 0;
  for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = 1;
  for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
  if(f) x = -x;
}
template<typename T, typename... Rest>
inline void read(T &x, Rest&... rest) {
  read(x), read(rest...);
}
template<typename T>
inline void write(T x) {
  if(x < 0) putchar('-'), x = -x;
  if(x > 9) write(x / 10);
  putchar(x % 10 + '0');
}
#undef isdigit
}
using namespace IO;

const int N = 3e5 + 10;
int n, a[N];
vector<int> G[N];

int dfc, st[N], ed[N];
void dfs1(int u) {
  st[u] = ++dfc;
  for(int v : G[u]) 
    dfs1(v);
  ed[u] = dfc;
}

struct SegmentTree {
  int tr[N << 2], tag[N << 2];
#define lc (k << 1)
#define rc (k << 1 | 1)
#define mid (l + r) / 2
  void build(int k, int l, int r) {
    tr[k] = tag[k] = 0;
    if(l == r) return ;
    build(lc, l, mid), build(rc, mid + 1, r);
  }
  void add(int k, int v) {
    tr[k] += v, tag[k] += v;
  }
  void pushdown(int k) {
    if(tag[k]) {
      add(lc, tag[k]), add(rc, tag[k]);
      tag[k] = 0;
    }
  }
  void modify(int k, int l, int r, int L, int R, int v) {
    if(r < L || R < l) return ;
    if(L <= l && r <= R) {
      add(k, v);
      return ;
    }
    pushdown(k);
    modify(lc, l, mid, L, R, v), modify(rc, mid + 1, r, L, R, v);
    tr[k] = max(tr[lc], tr[rc]);
  }
  int query(int k, int l, int r, int L, int R) {
    if(r < L || R < l) return 0;
    if(L <= l && r <= R) return tr[k];
    pushdown(k);
    return max(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
  }
}seg;

vector<pii> vec[N];

int lst[N], pre[N];
void dfs2(int u) {
  pre[u] = lst[a[u]];
  lst[a[u]] = u;
  for(int v : G[u]) dfs2(v);
  lst[a[u]] = pre[u];
  vec[pre[u]].emplace_back(mp(st[u], ed[u]));
}

ll ans;

void dfs3(int u) {
  for(int v : G[u]) 
    dfs3(v);
  seg.modify(1, 1, n, st[u], ed[u], 1);
  for(auto x : vec[u]) seg.modify(1, 1, n, x.first, x.second, -1);
  if(sz(G[u])) {
    vector<int> vec = {1};
    for(int v : G[u]) 
      vec.eb(seg.query(1, 1, n, st[v], ed[v]));
    sort(vec.begin(), vec.end(), [](int x, int y) {
      return x > y;
    });
    ans = max(ans, 1ll * vec[0] * vec[1]);
  }
}

void clear() {
  dfc = 0, ans = 1;
  for(int i = 1; i <= n; ++i) {
    G[i].clear(), vec[i].clear();
    a[i] = lst[i] = pre[i] = 0;
  }
  seg.build(1, 1, n);
}

void solve() {
  read(n);
  clear();
  for(int i = 2; i <= n; ++i) {
    int fa; read(fa);
    G[fa].eb(i);
  }
  for(int i = 1; i <= n; ++i)
    read(a[i]);
  dfs1(1);
  dfs2(1);
  dfs3(1);
  printf("%lld\n",ans);
} 

int main() {
  int T; read(T);
  while(T--) solve();
}

```


---

## 作者：梦应归于何处 (赞：0)

### 题目大意

给你一棵 $n$ 个点的二叉树，每个节点有一个颜色 $a_i$，定义 $f(u,v)$ 为 $u
\rightarrow v$ 的简单路径上的颜色个数。对于所有点对 $(u,v)$，其中 $u,v$ 可以相等，设 $l$ 为 $u,v$ 的最近公共祖先，求 $max\{f(l,u)\times f(l,v)\}$。

### 思路

这道题我们可以给每个点重新编号，按照深度优先搜索的顺序。然后我们就把每个子树转成了一段连续的区间。然后我们去枚举最近公共祖先，利用线段树维护以我当前枚举的这个最近公共祖先的子树中的答案最大值和次大值，这个子树的答案就是最大值乘以次大值。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll dfn[300005],dfn2[300005];
vector<ll> g[300005],jian[300005];
ll mx[1200005],tag[1200005];
stack<ll> st[300005];
ll cnt=0;
ll a[300005];
void dfs(ll x) {
	dfn[x]=++cnt;
	for (auto i:g[x]) {
		dfs(i);
	}
	dfn2[x]=cnt;
}
ll ans;
void cj(ll x) {
	if(!st[a[x]].empty()) {
		jian[st[a[x]].top()].push_back(x);
	}
	st[a[x]].push(x);
	for(auto i:g[x]) {
		cj(i);
	}
	st[a[x]].pop();
}
ll lc(ll p) {
	return p<<1;
}
ll rc(ll p) {
	return p<<1|1;
}
void pushdown(ll p) {
	if(tag[p]) {
		tag[lc(p)]+=tag[p],mx[lc(p)]+=tag[p];
		tag[rc(p)]+=tag[p],mx[rc(p)]+=tag[p];
		tag[p]=0;
	}
}
void pushup(ll p) {
	mx[p]=max(mx[lc(p)],mx[rc(p)]);
}
void upd(ll p,ll l,ll r,ll ql,ll qr,ll x) {
	if(ql<=l&&r<=qr) {
		tag[p]+=x;
		mx[p]+=x;
		return ;
	}
	pushdown(p);
	ll mid=(l+r)>>1;
	if(ql<=mid) {
		upd(lc(p),l,mid,ql,qr,x);
	}
	if(mid<qr) {
		upd(rc(p),mid+1,r,ql,qr,x);
	}
	pushup(p);
}
ll query(ll p,ll l,ll r,ll ql,ll qr) {
	if(ql<=l&&r<=qr) {
		return mx[p];
	}
	pushdown(p);
	ll mid=(l+r)>>1;
	ll ret=0;
	if(ql<=mid) {
		ret=max(ret,query(lc(p),l,mid,ql,qr));
	}
	if(mid<qr) {
		ret=max(ret,query(rc(p),mid+1,r,ql,qr));
	}
	return ret;
}
void solve(ll x) {
	for (auto i:g[x]) {
		solve(i);
	}
	upd(1,1,n,dfn[x],dfn2[x],1);
	for (auto i:jian[x]) {
		upd(1,1,n,dfn[i],dfn2[i],-1);
	}
	ll mx1=1,mx2=1;
	for (auto i:g[x]) {
		ll res=query(1,1,n,dfn[i],dfn2[i]);
		if(res>=mx1) {
			mx2=mx1;
			mx1=res;
		} else if(res>=mx2) {
			mx2=res;
		}
	}
	ans=max(ans,mx1*mx2);
}
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	ll t;
	cin>>t;
	while(t--) {
		cnt=0;
		ans=1;
		cin>>n;
		for(int i=1; i<=4*n; i++) {
			mx[i]=0;
			tag[i]=0;
		}
		for (int i=1; i<=n; i++) {
			g[i].clear();
			jian[i].clear();
			dfn[i]=0;
			dfn2[i]=0;
			while(!st[i].empty()) {
				st[i].pop();
			}
		}
		for(int i=2; i<=n; i++) {
			ll fa;
			cin>>fa;
			g[fa].push_back(i);
		}
		for (int i=1; i<=n; i++) {
			cin>>a[i];
		}
		dfs(1);
		cj(1);
		solve(1);
		cout<<ans<<endl;
	}
	return 0;
}
~~~

---

