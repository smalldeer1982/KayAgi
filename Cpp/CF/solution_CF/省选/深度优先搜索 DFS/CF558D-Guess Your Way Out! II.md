# Guess Your Way Out! II

## 题目描述

问题描述

Amr 买来了一个新的游戏，名叫 Guess Your Way Out! II。这个游戏需要你找到迷宫的出口。迷宫是一个高度为h的满二叉树，一开始你在根节点，迷宫的唯一出口在某一个叶子节点处。

这棵树的节点编号是这样规定的，根节点编号为 $1$，编号为 $i$ 的节点的左儿子编号为 $2\times i$，右儿子编号为 $2 \times i + 1$。每个节点的层次是这样定义的，根节点在第一层，儿子节点的层数在它的父亲节点的基础上增加 $1$。

一开始玩家并不知道迷宫的出口在哪里，于是就只能向游戏提问，每次的提问都是这样的：“出口节点的层数为 $i$ 的祖先节点的编号是否在区间 $[L,R]$ 内？”这时游戏会给出回答“是”或“不是”，不过这个游戏又是会出错，就会给出错误的回答。

Amr 已经进行了若干次提问，并记录下了每次的提问和回答，他想知道，游戏是否一定给出过错误的回答，通过这些答案能不能唯一确定出口的位置。于是 Amr 就来求助于你了。

## 样例 #1

### 输入

```
3 1
3 4 6 0
```

### 输出

```
7```

## 样例 #2

### 输入

```
4 3
4 10 14 1
3 6 6 0
2 3 3 1
```

### 输出

```
14```

## 样例 #3

### 输入

```
4 2
3 4 6 1
4 12 15 1
```

### 输出

```
Data not sufficient!```

## 样例 #4

### 输入

```
4 2
3 4 5 1
2 3 3 1
```

### 输出

```
Game cheated!```

# 题解

## 作者：SIGSEGV (赞：3)

首先预处理出每一层的结点编号范围，然后处理每一个询问时先将$L$和$R$的范围缩小到$i$层的编号范围内(即取交集)，然后对$L$和$R$映射到$h$层的位置进行差分，在符合本次询问的点的位置处+1。最后统计有多少个位置的值是$q$即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400005;
using ll = long long;
int h,q,idx,ptr;
ll idl[N],idr[N];
struct Query {ll pos;int v;} d[N],dd[N];
ll lleaf(ll num)
{
    while (idl[h] > num) num = num << 1;
    return num;
}
ll rleaf(ll num)
{
    while (idl[h] > num) num = num << 1 | 1;
    return num;
}
int main ()
{
    ios::sync_with_stdio(false);
    cin >> h >> q;
    idl[1] = idr[1] = 1;
    for (int i = 2;i <= h;i++) idl[i] = idl[i - 1] << 1,idr[i] = idr[i - 1] << 1 | 1;
    int t1,op;ll t2,t3;
    d[++idx] = {idl[h],0};d[++idx] = {idr[h] + 1,0};
    for (int i = 1;i <= q;i++)
    {
        cin >> t1 >> t2 >> t3 >> op;
        t2 = max(t2,idl[t1]);t3 = min(t3,idr[t1]);
        if (op == 1)
        {
            d[++idx] = {lleaf(t2),1};d[++idx] = {rleaf(t3) + 1,-1};
        }
        else
        {
            d[++idx] = {idl[h],1};d[++idx] = {lleaf(t2),-1};
            d[++idx] = {rleaf(t3) + 1,1};d[++idx] = {idr[h] + 1,-1};
        }
    }
    sort(d + 1,d + idx + 1,[](Query a,Query b) {return a.pos < b.pos;});
    for (int i = 1;i <= idx;i++)
        if (i == 1 || d[i].pos != d[i - 1].pos) dd[++ptr] = d[i];
        else dd[ptr].v += d[i].v;
    ll cnt = 0,ans = 0;int cur = dd[1].v;
    for (int i = 2;i <= ptr;i++)
    {
        ll diff = dd[i].pos - dd[i - 1].pos;
        if (cur == q) cnt += diff,ans = dd[i - 1].pos;
        cur += dd[i].v;
    }
    if (cnt > 1) cout << "Data not sufficient!" << endl;
    else if (cnt == 1) cout << ans << endl;
    else cout << "Game cheated!" << endl;
    return 0;
}
```

---

## 作者：tribool4_in (赞：1)

给出深度为 $d$ 的节点区间 $[l,r]$，显然容易求出其对应的叶子节点区间。因此问题变为了给出 $q$ 个信息，形如 $x$ 在或不在某个区间内，求最终的合法 $x$ 的情况。

首先对于“在”的信息容易处理，直接对于所有询问区间求交，得到 $[l', r']$。考虑对于“不在”的信息，相当于最终答案在这些区间的并集的补集中。于是将所有“不在”的区间排序并将所有相交区间合并，然后求个补集。最终直接遍历一遍所有区间，搞出其与 $[l', r']$ 的交，如果有多处有交或交长度大于 1 则为多解，无交无解，否则搞出来直接输出即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int h, q, L, R;
vector<pair<int, int>> v0, v1, v;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> h >> q;
    int iL = L = 1ll << (h - 1), iR = R = (1ll << h) - 1;
    for (int i = 1, d, l, r, o; i <= q; i++) {
        cin >> d >> l >> r >> o;
        l <<= (h - d), r = (r + 1 << h - d) - 1;
        if (o == 1) iL = max(iL, l), iR = min(iR, r);
        else v0.emplace_back(l, r);
    }
    if (iL > iR) return cout << "Game cheated!\n", 0;
    if (v0.empty()) {
        if (iR - iL > 0) return cout << "Data not sufficient!\n", 0;
        return cout << iL << '\n', 0;
    }
    sort(v0.begin(), v0.end());
    int cl = v0.front().first, cr = v0.front().second, lst = L;
    for (auto [l, r] : v0) {
        if (l > cr) {
            if (lst < cl) v.emplace_back(lst, cl - 1);
            lst = cr + 1, cl = l, cr = r;
        } else cr = max(cr, r);
    }
    if (lst < cl) v.emplace_back(lst, cl - 1);
    if (cr < R) v.emplace_back(cr + 1, R);
    int ans = 0;
    for (auto [l, r] : v) {
        if (r < iL || l > iR) continue;
        int lp = max(l, iL), rp = min(r, iR);
        if (rp - lp > 0 || ans) return cout << "Data not sufficient!\n", 0;
        ans = lp;
    }
    if (ans == 0) return cout << "Game cheated!\n", 0;
    return cout << ans << '\n', 0;
}
```

---

## 作者：DPair (赞：0)

提供一种珂朵莉树的写法。

## 【思路】
首先考虑每一次操作的本质，实际上是确定了答案在某一段区间内，当然也可以理解成答案不在某一段区间内。

然后每一层的元素所代表的区间显然是可以预处理出来的，实际上就是 $[2^{i-1},2^i-1]$ 这段区间，用位运算十分方便。

考虑每一次询问先与对应层的区间取一个交，特判一下空区间的情况，然后就可以直接扩展到对应的叶子。

考虑如果答案返回值是 $1$ 那么剩下的左右两个区间都无解，直接推平成 $0$ 即可。返回值是 $0$ 的话那么推平给出的区间即可。

然后扩展到对应的叶子就是左端点扩展到最左的儿子，右端点扩展到最右的儿子。这个左端点乘上一个 $2^{h-i}$ ，右端点 $+ 1$ 之后乘上 $2^{h-i}$ 再 $-1$ 就是对应的左右右端点。

然后珂朵莉树区间推平即可，由于只有推平复杂度是对的，理论上可以卡到 $O(n\log n)$ （但也是对的），不过实测很快。

最后判断剩下的为 $1$ 的点数即可，若没有则无解，否则要么多解要么唯一解。

正确性显然。

## 【代码】
```cpp
/*
    author: DPair
    language: C++11

    description:
    明镜止水之心
*/
#include <cstdio>
#include <cstring>
#include <set>
using std :: set;
#define rep(i,s,t) for(int i=s;i<=t;++i)
namespace MyMinMax{
    template <typename T>
    inline T mn(T x, T y) {return x < y ? x : y;}
    template <typename T>
    inline T mx(T x, T y) {return x > y ? x : y;}
    template <typename T>
    inline void chmin(T &x, T y) {(x > y) && (x = y);}
    template <typename T>
    inline void chmax(T &x, T y) {(x < y) && (x = y);}
}
using namespace MyMinMax;
//删去了不重要的快读
typedef long long LL;
struct NODE{
    LL l, r;
    int val;
    NODE(LL l, LL r, int val) : l(l), r(r), val(val){}
    inline bool operator < (const NODE &tmp) const{return l < tmp.l;}
};
struct Inter{
    LL l, r;
    Inter(){}
    Inter(LL l, LL r) : l(l), r(r){}
    inline Inter operator + (const Inter &b) const{return Inter(mx(l, b.l), mn(r, b.r));}
    inline void operator += (const Inter &b){chmax(l, b.l);chmin(r, b.r);}
    inline bool empty(){return l > r;}
}lay[55];
int h, q;
set <NODE> t;
typedef set <NODE> :: iterator IT;
inline IT split(LL x){
    if(x > lay[h].r) return t.end();
    IT it = t.lower_bound(NODE(x, 0, 0));
    if(it != t.end() && it -> l == x) return it;
    -- it;
    LL l = it -> l, r = it -> r;int val = it -> val;
    t.erase(it);t.emplace(NODE(l, x - 1, val));
    return t.emplace(NODE(x, r, val)).first;
}
inline void assign(LL l, LL r){
    IT R = split(r + 1), L = split(l);
    t.erase(L, R);
    t.emplace(NODE(l, r, 0));
}

int main(){
    read(h, q);
    rep(i, 1, h) lay[i] = Inter(1ll << (i - 1), (1ll << i) - 1);
    t.emplace(NODE(1ll << (h - 1), (1ll << h) - 1, 1));
    while(q --){
        LL l, r;int p, x;read(p, l, r, x);
        Inter inv = Inter(l, r);
        inv += lay[p];
        if(inv.empty()){
            if(x) return put("Game cheated!"), 0;
            continue;
        }
        l = inv.l, r = inv.r;
        if(!x) assign(l << (h - p), ((r + 1) << (h - p)) - 1);
        else {
            if(lay[h].l <= (l << (h - p)) - 1) assign(lay[h].l, (l << (h - p)) - 1);
            if(((r + 1) << (h - p)) <= lay[h].r) assign(((r + 1) << (h - p)), lay[h].r);
        }
    }
    LL ans = 0;
    for (auto it : t){
        if(it.val){
            if(it.r ^ it.l) return put("Data not sufficient!"), 0;
            if(ans) return put("Data not sufficient!"), 0;
            ans = it.l;
        }
    }
    if(!ans) put("Game cheated!");
    else print(ans);
}

```

---

