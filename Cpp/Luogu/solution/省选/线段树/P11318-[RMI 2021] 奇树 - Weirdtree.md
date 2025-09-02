# [RMI 2021] 奇树 / Weirdtree

## 题目背景


译自 [9th Romanian Master of Informatics, RMI 2021](https://rmi.lbi.ro/rmi_2021/) D2T3。$\texttt{1s,0.5G}$。

提交时，需要在文件头添加

```cpp
void initialise(int N, int Q, int h[]);
void cut(int l, int r, int k);
void magic(int i, int x);
long long int inspect(int l, int r);
```

请使用 C++17 或更高版本提交。

## 题目描述


**这是一道（函数式）交互题。**

你需要维护一个长度为 $N$ 的非负整数序列 $h_1,h_2,\cdots,h_N$。有三种操作，一共 $Q$ 次：

- 操作 1（砍树）。给定 $l,r,k$。执行 $k$ 次以下操作：
	- 若区间 $[l,r]$ 的最大值为 $0$，无事发生；
    - 否则，将最大值减去 $1$（如果存在多个，取下标最小的一个）。
    
    形式化地：
    - 若 $\displaystyle \max_{i\in [l,r]} \{h_i\}=0$，无事发生。
    - 否则，记 $\displaystyle x=\min\argmax_{i\in [l,r]}\{h_i\}$（换句话说，满足 $x\in [l,r],h_x=\max_{i\in [l,r]}\{h_i\}$ 的最小的 $x$）。令 $h_x\gets h_x-1$。
- 操作 2（施法）。给定 $x,v$，令 $h_x\gets v$。
- 操作 3（查询）。给定 $l,r$，求 $\displaystyle \sum_{i\in [l,r]} h_i$。


### 实现细节

你不需要，也不应该实现 `main` 函数。你应当实现以下函数：

```cpp
void initialise(int N, int Q, int h[]);
void cut(int l, int r, int k);
void magic(int i, int x);
long long int inspect(int l, int r);
```

- `initialise` 函数：
    - 将在最开始被调用恰好一次。
    - `N`：数组长度。
    - `Q`：询问次数。
    - `h[]`：长度为 $(N+1)$ 的数组，`h[i]`（$1\le i\le N$）表示数列中的第 $i$ 个数。
- `cut` 函数：
    - 见操作 1。
- `magic` 函数：
    - 见操作 2。
- `inspect` 函数：
    - 见操作 3。
    - 返回一个整数表示答案。

你可以自由使用全局变量，STL 库等。

为了方便选手本地测试，我们在附件中提供了 $\texttt{grader.cpp}$。下面的输入输出格式均表示 sample grader 的输入输出格式。


## 说明/提示



对于 $100\%$ 的数据，保证：
- $1\le N, Q\le 3\times 10^5$；
- $1\le i\le N$；
- $1\le l\le r\le N$；
- $0\le x,k,h_i\le 10^9$。


| 子任务编号 | $N,Q\le  $ | 特殊性质 |得分 |  
| :--: | :--: |  :--: | :--: |
| $ 1 $    | $ 10^3 $  | A | $5$ |
| $ 2 $    | $ 8\times 10^4 $  | A | $8$ |
| $ 3 $    | $ 10^3 $ | B | $8$ |
| $ 4 $    | $ 3\times 10^5 $  | B | $19$ |
| $ 5 $    | $ 3\times 10^5 $  | C | $10$ |
| $ 6 $    | $ 8\times 10^4 $ |  | $21$ |
| $ 7 $    | $ 3\times 10^5 $ |  | $29$ |

- 特殊性质 A：$k=1$。
- 特殊性质 B：没有操作 2。
- 特殊性质 C：$l=1,r=N$（这对操作 $1,3$ 都有效）。


## 样例 #1

### 输入

```
6 10
1 2 3 1 2 3
1 1 6 3
3 1 6
1 1 3 3
3 1 6
1 1 3 1000
3 1 6
2 1 1000
3 1 6
1 1 3 999
3 1 5```

### 输出

```
9
6
5
1005
4```

# 题解

## 作者：xiezheyuan (赞：5)

> 庭中有奇树，绿叶发华滋。
>
> 攀条折其荣，将以遗所思。
>
> 馨香盈怀袖，路远莫致之。
>
> 此物何足贡？但感别经时。
>
> ——《古诗十九首》

## 简要题意

**本题使用函数式交互题的形式处理所有修改和询问，具体参见题面**。

你需要维护一个长度为 $n$ 的序列 $h$，有 $q$ 次操作，支持：

- `1 l r k` 重复下述操作 $k$ 次：
  - 若区间 $[l,r]$ 的最大值为 $0$，则什么也不做。
  - 否则选择区间 $[l,r]$ 中的最大值出现位置 $p$（若存在多个 $p$，选择 $p$ 较小的），令 $h_p\leftarrow h_p-1$。
- `2 x v` 令 $h_x\leftarrow v$。
- `3 l r` 求区间 $[l,r]$ 中所有元素的和。

$1\leq n,q\leq 3\times 10^5,0\leq h_i,v,k\leq 10^9$。

## 思路

前置知识：区间最值操作（吉老师线段树，segment tree beats），不会的可以去做 [HDU5306 Gorgeous Sequence](https://vjudge.net/problem/HDU-5306)。

我们发现 $2,3$ 操作都是平凡的，关键在于 $1$ 操作。

考虑我们执行 $1$ 操作时，一定形如将所有最大值全部减去 $1$，如果此时最大值仍然大于原本的次大值，就重复上述操作，直至最大值和次大值合并，以此类推。这个东西就很像区间最值操作。

具体来说，我们先求出区间 $[l,r]$ 的最大值 $\mathrm{maxt}$、次大值 $\mathrm{sect}$ 以及最大值出现次数 $\mathrm{cntt}$，若最大值出现次数大于 $k$，就结将区间 $[l,r]$ 中前 $k$ 个最大值减去 $1$。

否则我们计算出 $v=\max(\mathrm{sect}, \mathrm{maxt}-\left\lfloor\frac{k}{\mathrm{cntt}}\right\rfloor)$ 表示将所有最大值设定为 $v$，可以看成取 $h_i\leftarrow \min(h_i,v)$，因而可以写一个类似区间取 $\min$ 的东西维护。最后记得这玩意会消耗 $(\mathrm{maxt}-v)\cdot \mathrm{cntt}$ 次操作，也就是令 $k\leftarrow k-(\mathrm{maxt}-v)\cdot \mathrm{cntt}$。

现在的问题是，这玩意复杂度真的对吗？势能分析可知时间复杂度 $O(n+q\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
#define IMPLEMENT
using namespace std;

using i64 = long long;
const int N = 3e5 + 5;
int n, q, a[N];

struct node{
    i64 sumt;
    int maxt, sect, cntt;
    node() : sumt(0), maxt(0), sect(0), cntt(0) {}
} t[N << 2];
int tagt[N << 2];

node merge(node x, node y){
    node res;
    res.sumt = x.sumt + y.sumt;
    if(x.maxt >= y.maxt) res.maxt = x.maxt, res.cntt += x.cntt, res.sect = max(x.sect, y.maxt);
    if(x.maxt <= y.maxt) res.maxt = y.maxt, res.cntt += y.cntt, res.sect = max(x.maxt, y.sect);
    if(x.maxt == y.maxt) res.sect = max(x.sect, y.sect);
    return res;
}

void mktag(int i, int v){
    if(t[i].maxt <= v) return;
    t[i].sumt += 1ll * (v - t[i].maxt) * t[i].cntt, t[i].maxt = tagt[i] = v;
}

void pushdown(int i){
    if(~tagt[i]) mktag(ls, tagt[i]), mktag(rs, tagt[i]), tagt[i] = -1;
}

void build(int i, int l, int r){
    tagt[i] = -1;
    if(l == r) return (t[i].sumt = t[i].maxt = a[l], t[i].cntt = 1), void();
    build(ls, l, mid), build(rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}

void update(int ql, int qr, int v, int i, int l, int r){
    if(t[i].maxt <= v) return;
    if(ql <= l && r <= qr){
        if(t[i].sect < v || l == r) return mktag(i, v);
    }
    pushdown(i);
    if(ql <= mid) update(ql, qr, v, ls, l, mid);
    if(qr > mid) update(ql, qr, v, rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}

void subtract(int ql, int qr, int v, int& cap, int i, int l, int r){
    if(t[i].maxt < v || !cap) return;
    if(ql <= l && r <= qr){
        if((t[i].sect < (v - 1) && cap >= t[i].cntt) || l == r) return (cap -= t[i].cntt), mktag(i, v - 1);
    }
    pushdown(i);
    if(ql <= mid) subtract(ql, qr, v, cap, ls, l, mid);
    if(qr > mid) subtract(ql, qr, v, cap, rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}

void assign(int p, int v, int i, int l, int r){
    if(l == r) return (t[i].sumt = t[i].maxt = v, t[i].cntt = 1), void();
    pushdown(i);
    if(p <= mid) assign(p, v, ls, l, mid);
    else assign(p, v, rs, mid + 1, r);
    t[i] = merge(t[ls], t[rs]);
}

node query(int ql, int qr, int i, int l, int r){
    if(ql <= l && r <= qr) return t[i];
    pushdown(i);
    if(ql <= mid && qr > mid) return merge(query(ql, qr, ls, l, mid), query(ql, qr, rs, mid + 1, r));
    if(ql <= mid) return query(ql, qr, ls, l, mid);
    return query(ql, qr, rs, mid + 1, r);
}

IMPLEMENT void initialise(int N, int Q, int A[]){
    n = N, q = Q, copy(A + 1, A + n + 1, a + 1), build(1, 1, n);
}

IMPLEMENT void cut(int l, int r, int k){
    while(k){
        node tmp = query(l, r, 1, 1, n);
        if(!tmp.maxt) break;
        if(k < tmp.cntt) subtract(l, r, tmp.maxt, k, 1, 1, n);
        else{
            int val = max(tmp.sect, tmp.maxt - (k / tmp.cntt));
            k -= (tmp.maxt - val) * tmp.cntt;
            update(l, r, val, 1, 1, n);
        }
    }
}

IMPLEMENT void magic(int x, int v){ assign(x, v, 1, 1, n); }

IMPLEMENT i64 inspect(int l, int r){ return query(l, r, 1, 1, n).sumt; }

#ifdef LOCAL
int _a[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> _a[i];
    initialise(n, q, _a);
    for(int i=1;i<=q;i++){
        int op, x, y, z;
        cin >> op >> x >> y;
        if(op == 1) (cin >> z), cut(x, y, z);
        else if(op == 2) magic(x, y);
        else{
            cout << inspect(x, y) << '\n';
        }
    }
    return 0;
}
#endif

// Written by xiezheyuan
```

---

