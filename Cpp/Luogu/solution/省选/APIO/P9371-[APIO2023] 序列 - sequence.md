# [APIO2023] 序列 / sequence

## 题目背景

**由于部分 BUG，使用 C++14 (GCC9) 提交会产生编译错误，请使用 C++14 等语言进行提交。**

提交时，无需引用 `sequence.h`。你提交的代码中需要实现以下函数：

```cpp
int sequence(int N, std::vector<int> A)
```

## 题目描述

在迷人的 APIO 国，居住一位着年轻智慧的学生 Alice。Alice 对解决能挑战她数学能力的有趣问题有着永不满足的好奇心。一天，她在解决一个神秘的有关长为 $N$ 的序列 (即 $A[0], A[1], \cdots, A[N-1]$ ) 的问题时遇到了困难，她无法抗拒探索答案的诱惑力。

现在，她想要与你分享一些她的发现。不过，为了更好的理解，我们需要给出以下定义:

- 定义 $W(l, r, x)$ 为 $\sum_{i=l}^{r} \mathbb{I}[A[i]=x]$, 即 $x$ 在 $A[l] \cdots A[r]$ 中的出现次数。
- 定义一个非空整数序列 $B[0] B[1] \cdots B[k-1]$ 的中位数集合为 $S(\{B[0], B[1] \cdots B[k-1]\})$, 然后 Alice 会展示如何分步计算中位数集合:

○首先，将序列 $B[0], B[1], \ldots, B[k-1]$ 按照升序排序，令排好序的序列为 $C[0], C[1], \ldots, C[k-1]_{0}$

○ 然后, $S(\{B[0], B[1] \cdots B[k-1]\})=\left\{C\left[\left\lfloor\frac{k-1}{2}\right]\right], C\left[\left\lceil\frac{k-1}{2}\right\rceil\right]\right\}$ 。

○ 为了能更好的理解 $S$ 的计算，以下为一些例子:

- $S(\{6,3,5,4,6,2,3\})=\{4\}$.
- $S(\{4,2,3,1\})=\{2,3\}$
- $S(\{5,4,2,4\})=\{4\}$.

作为一道具有挑战性的问题, Alice 想对于所有的 $(l, r)(0 \leq l \leq r \leq N-1)$ 找到其价值 $\max _{x \in S(l, r)} W(l, r, x)$ 的最大值。其中 $S(l, r)$ 代表 $A[l] \cdots A[r]$ 导出的中位数集合（正如之前提到的 $S(A[l], \cdots, A[r])$ )。虽然 Alice 已经得到了答案，她需要核对答案的正确性，所以她找到了你，希望你能编程解决问题。

### 实现细节

你需要实现如下的过程:

```cpp
int sequence(int N, std:: vector<int> A);
```
- $N$ ：序列 $A$ 的长度。
- $A$ : 一个长度为 $N$ 的数组，即输入中提到的序列 $A$ 。
- 该函数应返回一个整数，代表所有可行 $(l, r)$ 价值的最大值。
- 这个函数恰好被调用一次。


## 说明/提示

### 例子

#### 样例 1

考虑如下的调用:

```cpp
sequence(7,{1,2,3,1,2,1,3});
```

函数应返回 $3$。

在这个样例中, $S(0,5)=\{1,2\}, W(0,5,1)=3 ， W(0,5,2)=2$ ，所以 $(0,5)$ 的价值为 3 。

容易验证 $(0,5)$ 在所有合法的 $(l, r)$ 二元组中有着最大的价值。

#### 样例 2

考虑如下的调用:

```cpp
sequence(9,{1,1,2,3,4,3,2,1,1});
```

函数应返回 $2$。

### 样例 3

考虑如下的调用:

```cpp
sequence(14,{2,6,2,5,3,4,2,1,4,3,5,6,3,2});
```

函数应返回 $3$。

### 约束条件

- $1 \leq N \leq 5 \times 10^{5}$
- $1 \leq A[i] \leq N$

### 子任务

1. (11 分)：$N \leq 100$ 。
2. (17 分)：$N \le 2 \times 10^{3}$ 。
3. (7 分)：存在一个 $x$ 满足 $\forall 0 \leq i<x, A[i] \leq A[i+1]$ 且 $\forall x<i<N, A[i] \leq A[i-1]$ 。
4. (12 分)：$A[i] \leq 3$ 。
5. (13 分)：$W(0, N-1, A[i]) \leq 2$ (对于所有满足 $0 \leq i \leq N-1$ 的 $i$ )。
6. (22 分)：$N \leq 8 \times 10^{4}$ 。
7. (18 分)：没有额外限制。 

## 样例 #1

### 输入

```
7
1 2 3 1 2 1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
9
1 1 2 3 4 3 2 1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
14
2 6 2 5 3 4 2 1 4 3 5 6 3 2```

### 输出

```
3```

# 题解

## 作者：Un1quAIoid (赞：24)

**题目大意：**

给定序列 $a_{1, \dots, n}$，定义 $S_{l,r}$ 为 $a_{l,\dots,r}$ 的中位数集合（大小为 $1$ 或 $2$），$w_{l,r,x} = \sum_{i=l}^r [a_i=x]$，求 $\max_{1 \le l \le r \le n} \max_{x \in S_{l,r}} w(l,r,x)$。

$n \le 5 \times 10^5$。

-------------------

小清新数据结构。

容易想到枚举中位数的值，设为 $x$，将序列中 $<x$ 的位置赋为 $0$，$>x$ 的位置赋为 $1$，目标即为计算所有 $x$ 是中位数的区间中 $x$ 的最大出现次数。

**step1**

先来考虑 $x \in S_{l,r}$ 的等价条件是什么，设区间中 $x$ 的出现次数为 $c$，$0$ 的出现次数为 $c_0$，$1$ 的出现次数为 $c_1$，不难得到：

$$
\begin{aligned}
&x \in S_{l,r}\\

\Leftrightarrow
 &\begin{cases}
c+c_0 \ge c_1\\
c+c_1 \ge c_0\\
\end{cases}\\

\Leftrightarrow &\max(c_1-c_0-c,c_0-c_1-c) \le 0

\end{aligned}
$$

设 $u_{i} = w(1,i,1)-w(1,i,0)-w(1,i,x)$，$v_i = w(1,i,0)-w(1,i,1)-w(1,i,x)$，那么 $x \in S_{l,r}$ 当且仅当 $\max(u_r-u_{l-1}, v_r - v_{l-1}) \le 0$，将 $p_i=(u_i, v_i)$ 看作二维平面上的一个点，这个条件实际上就是在说 $p_r$ 在 $p_{l-1}$ 的左下方。

**step2**

现在再来观察 $p_{i-1}$ 和 $p_i$ 之间的位置关系。如果 $a_i = x$，那么 $p_{i}$ 是 $p_{i-1}$ 向左下走一步；如果 $a_i = 0$，那么是向左上走一步；如果 $a_i=1$，那么是向右下走一步。画出来会像下图：

![](https://pic1.imgdb.cn/item/646c8612e03e90d87436a57b.png)

画出来就能一眼看出这张图的特点：由若干条（准确来说是 $w(1,n,x)+1$ 条）斜率为 $-1$ 的线段以及连接它们的斜率为 $1$ 的线段组成。现在我们的目标就变成了找到相距最远的两条斜率为 $-1$ 线段（距离定义为从一条走到另一条需要向左下走的次数），满足能够从其上面分别找出一个点满足一个在另一个的左下方。

考虑能够找出这样两个点的等价条件是什么，不妨来看上图中的线段 BC 和 DE，画一下图就能得出条件：

$$
\begin{cases}
C_x \ge D_x\\
B_y \ge E_y\\
\end{cases}
$$

二维数点的形式。使用 BIT，支持单点修改，后缀 $\min$ 即可；第 $i$ 条斜率为 $-1$ 的线段实际上就是点 $x$ 的第 $i-1$ 次出现位置到第 $i$ 次出现位置之间的所有位置对应的点的集合，所以线段端点的横纵坐标只需要使用线段树，支持区间加，区间 $\max \And \min$ 即可。

总复杂度 $O(n \log n)$。

代码：
```cpp
//#include "sequence.h"
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') f = c == '-' ? -1 : 1, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

typedef long long ll;
const int N = 5e5+5;
const int Mod = 998244353;
const int INF = 0x3f3f3f3f;

int n, a[N], ans;
vector<int> pos[N];

struct segT {
    struct node {
        int mx, mn, ad;
    } T[N << 2];

    #define ls (p << 1)
    #define rs (p << 1 | 1)

    inline void push_up(int p) {
        T[p].mx = max(T[ls].mx, T[rs].mx) + T[p].ad;
        T[p].mn = min(T[ls].mn, T[rs].mn) + T[p].ad;
    }

    void upd(int p, int l, int r, int gl, int gr, int k) {
        if (l >= gl && r <= gr) {
            T[p].mx += k, T[p].mn += k;
            T[p].ad += k;
            return;
        }
        int mid = (l + r) >> 1;
        if (mid >= gl) upd(ls, l, mid, gl, gr, k);
        if (mid < gr) upd(rs, mid + 1, r, gl, gr, k);
        push_up(p);
    }

    int qry_mn(int p, int l, int r, int gl, int gr) {
        if (l >= gl && r <= gr) return T[p].mn;
        int mid = (l + r) >> 1, ret = INF;
        if (mid >= gl) ret = qry_mn(ls, l, mid, gl, gr);
        if (mid < gr) ret = min(ret, qry_mn(rs, mid + 1, r, gl, gr));
        return ret + T[p].ad;
    }

    int qry_mx(int p, int l, int r, int gl, int gr) {
        if (l >= gl && r <= gr) return T[p].mx;
        int mid = (l + r) >> 1, ret = -INF;
        if (mid >= gl) ret = qry_mx(ls, l, mid, gl, gr);
        if (mid < gr) ret = max(ret, qry_mx(rs, mid + 1, r, gl, gr));
        return ret + T[p].ad;
    }

    #undef ls
    #undef rs
} Tx, Ty;

int cnt;

struct opt {
    int op, x, y, k;//0询问，1修改
} P[N * 2];

struct Hsh {
    int v[N * 2], c;
    int operator [](int x) { return v[x]; }
    inline void ins(int x) { v[++c] = x; }
    inline void init() {
        sort(v + 1, v + c + 1);
        c = unique(v + 1, v + c + 1) - v - 1;
    }
    inline int f(int x) { return lower_bound(v + 1, v + c + 1, x) - v; }
} H;

struct BIT {
    int T[N * 2];
    inline void upd(int x, int k) { for (; x; x -= lowbit(x)) T[x] = min(T[x], k); }
    inline int qry(int x) { int ret = INF; for (; x <= H.c; x += lowbit(x)) ret = min(ret, T[x]); return ret; }
    inline void clr(int x) { for (; x; x -= lowbit(x)) T[x] = INF; }
} T;

inline void work() {//二维数点
    sort(P + 1, P + cnt + 1, [](opt a, opt b) { return a.x == b.x ? a.op > b.op : a.x > b.x; });

    H.c = 0;
    for (int i = 1; i <= cnt; i++) H.ins(P[i].y);
    H.init();

    for (int i = 1; i <= cnt; i++) {
        P[i].y = H.f(P[i].y);
        if (P[i].op == 1) T.upd(P[i].y, P[i].k);
        else ans = max(ans, P[i].k - T.qry(P[i].y));
    }
    for (int i = 1; i <= cnt; i++) T.clr(P[i].y);
}

int sequence(int N, std::vector<int> A) {
	n = N;
	for (int i = 1; i <= n; i++) pos[A[i - 1]].pb(i);
	
	memset(T.T, 0x3f, sizeof(T.T));
    for (int i = 1; i <= n; i++) Tx.upd(1, 0, n, i, i, i), Ty.upd(1, 0, n, i, i, -i);
    for (int i = 1; i <= n; i++) if (!pos[i].empty()) {
        for (int j : pos[i])//from c1 to c
            Tx.upd(1, 0, n, j, n, -2);

        cnt = 0;
        pos[i].pb(n + 1);
        int k = pos[i].size(), lst = 0;
        for (int j = 0; j < k; j++) {
            int cur = pos[i][j];
            int mn_x = Tx.qry_mn(1, 0, n, lst, cur - 1), mn_y = Ty.qry_mn(1, 0, n, lst, cur - 1);
            int mx_x = Tx.qry_mx(1, 0, n, lst, cur - 1), mx_y = Ty.qry_mx(1, 0, n, lst, cur - 1);
            P[++cnt] = (opt) { 1, mx_x, mx_y, j };
            P[++cnt] = (opt) { 0, mn_x, mn_y, j };
            lst = cur;
        }

        work();

        pos[i].pop_back();
        for (int j : pos[i])//from c to c0
            Ty.upd(1, 0, n, j, n, 2);
    }
    
    return ans;
}

//int main() {
//    int n;
//    vector<int> A;
//	scanf("%d", &n); A.resize(n);
//	for (int i = 0; i < n; i++) scanf("%d", &A[i]);
//	
//	printf("%d", sequence(n, A));
//    return 0;
//}
```

---

## 作者：I_am_Accepted (赞：14)

一个值 $x$ 为序列 $\{a\}$ 的中位数当且仅当 $|H-L|\le S$，其中 $H$ 为序列中值 $>x$ 的个数，$L$ 为 $<x$，$S$ 为 $=x$。

拆成没有绝对值的形式
$$\begin{cases}
H-L+S\ge 0
\\ H-L-S\le 0
\end{cases}\ \ (*)$$
枚举中位数值 $V$，生成两个序列
$$
H_i=
\begin{cases}
-1&,a_i<V\\
1&,a_i\ge V
\end{cases}
$$
和
$$
L_i=
\begin{cases}
-1&,a_i\le V\\
1&,a_i>V
\end{cases}
$$
两者只在值 $=V$ 的位置有差别。

处理出 $=V$ 的下标序列 $p_1<p_2<\dots<p_k$。

对 $\{p\}$ 作双指针，扫左端点移右端点。

对于一个区间 $p[l,r]$，计算 $H[p_l,p_r]$ 内 $a_i\ne V$ 的和 $w$，不妨设 $w\le 0$。

那我们为了将这个和提高，找到 $H[1,p_l-1]$ 的最大后缀和 $x$ 与 $H[p_r+1,n]$ 的最大前缀 $y$（若 $w\ge 0$，则换成 $L$ 数组，最大缀改成最小缀）。

若 $x+y+w+(r-l+1)\ge 0$，则必然存在一个包含 $[p_l,p_r]$ 的区间满足 $(*)$ 不等式组（即 $\max(ans,r-l+1)\to ans$），因为：

> 一个变量初始值为负整数，通过不断地操作 $+1/-1$ 使其变为正整数，则必然有一个时刻变量 $=0$。

上述操作均可以用线段树维护，复杂度 $O(n\log n)$。

---

## 作者：_ANIG_ (赞：12)

题意：求所有区间中位数出现次数的最大值。

首先，考虑怎样的数是区间的中位数。显然，我们只需要考虑比 $x$ 小的和比 $x$ 大的个数。把小于 $x$ 的放到左边，大于 $x$ 的放到右边，所有 $x$ 放到中间，再判断最中间的数是否是 $x$。我们一个一个往里放，把小于 $x$ 的放在左边，记为 $-1$，大于 $x$ 的放在右边，记为 $1$。$x$ 既可以放在左边也可以放在右边，记为 $x$，可以取值 $0$ 或 $1$ 或 $-1$（分别表示放在中间，右边和左边）。那么，如果存在一种 $x$ 取值的方案，使得这个区间和为 $0$，那么就代表存在一种方案，使 $x$ 在最中间，即 $x$ 是区间的中位数。

这样，就可以对原数组变形。从小到大枚举 $x$，让原数组所有大于 $x$ 的为 $1$，小于 $x$ 的为 $-1$，等于 $x$ 的记为 $x$。可以发现，大于 $x+1$ 的一定大于 $x$，小于 $x$ 的一定小于 $x-1$。所以实际上需要改变的只有值域在 $x-1$ 到 $x+1$ 之间的，均摊下来总修改次数就是 $O(n)$。

查询时，枚举最靠左的 $x$，此时，找到满足 $x$ 是这个区间中位数的包含 $x$ 数量最多的区间。由于已经确定了最靠左的 $x$，所以区间的左端点没有限制，而显然，右端点需要尽量靠右。现在，就需要找到最靠右的右端点。设当前枚举到的位置为 $y$，$h_i$ 表示 $i$ 到 $y-1$ 区间的和的所有可能的取值。显然，这个结果是一个区间。求出所有 $h_i$ 的并集。由于只有加 $1$ 和减 $1$，所以这个结果也是一个区间。现在，就要求出 $y$ 右侧最靠右的满足条件的位置。

使用线段树。每个节点存一下这个节点代表的区间的前缀的取值的并集。显然，这个结果也是一个区间。但是由于左端点不一定是 $1$，所以每次查询前，先预处理所有会改变的值，然后在线段树上查找即可。右子树满足条件优先走右子树，否则走左子树。总复杂度 $O(n\log n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct qj{
	int l,r;
	friend qj operator+(qj a,qj b){
		a.l+=b.l;a.r+=b.r;
		return a;
	}
};
struct node{
	int l,r,sl,is;
	qj it,iq,h,q,t;
}p[2000005];
vector<int>wz[500005];
int res,n;
void upset(int x){
	p[x].t.l=p[x<<1].t.l+p[x<<1|1].t.l;
	p[x].t.r=p[x<<1].t.r+p[x<<1|1].t.r;
	p[x].q.l=min(p[x<<1].q.l,p[x<<1|1].q.l+p[x<<1].t.l);
	p[x].q.r=max(p[x<<1].q.r,p[x<<1|1].q.r+p[x<<1].t.r);
	p[x].h.l=min(p[x<<1|1].h.l,p[x<<1].h.l+p[x<<1|1].t.l);
	p[x].h.r=max(p[x<<1|1].h.r,p[x<<1].h.r+p[x<<1|1].t.r);
	p[x].sl=p[x<<1].sl+p[x<<1|1].sl;
}
void reset(int x,int l,int r){
	p[x].l=l,p[x].r=r;
	if(l==r){
		p[x].h.l=p[x].h.r=p[x].q.l=p[x].q.r=p[x].t.l=p[x].t.r=1;
		return;
	}
	int mid=l+r>>1;
	reset(x<<1,l,mid);
	reset(x<<1|1,mid+1,r);
	upset(x);
}
void sets(int x,int d,int sum){
	if(p[x].l==d&&p[x].r==d){
		if(sum){
			p[x].h.l=p[x].h.r=p[x].q.l=p[x].q.r=p[x].t.l=p[x].t.r=sum;
			p[x].sl=0;
		}else{
			p[x].h.l=p[x].q.l=p[x].t.l=-1;
			p[x].h.r=p[x].q.r=p[x].t.r=1;
			p[x].sl=1;
		}
		return;
	}
	int mid=p[x].l+p[x].r>>1;
	if(d<=mid)sets(x<<1,d,sum);
	else sets(x<<1|1,d,sum);
	upset(x);
}
void gx(int x,int sum){
	for(int i=0;i<wz[x].size();i++)sets(1,wz[x][i],sum);
}
qj gets1(int x,int d){
	if(d==0)return (qj){0,0};
	if(p[x].l==p[x].r){
		p[x].it=p[x].t;
		return p[x].t;
	}
	int mid=p[x].l+p[x].r>>1;
	qj res=(qj){0,0};
	if(d<=mid){
		qj nww=gets1(x<<1,d);
		p[x].it=p[x<<1].it;
		return nww;
	}else{
		qj rr=gets1(x<<1|1,d);
		res.l=min(rr.l,p[x<<1|1].it.l+p[x<<1].h.l);
		res.r=max(rr.r,p[x<<1|1].it.r+p[x<<1].h.r);
		p[x].it=p[x<<1].t+p[x<<1|1].it;
	}
	return res;
}
void init(int x,int d){
	if(p[x].l==p[x].r){
		p[x].it=p[x].t,p[x].iq=p[x].q,p[x].is=p[x].sl;
		return;
	}
	if(p[x<<1].r<d){
		init(x<<1|1,d);
		p[x].it=p[x<<1|1].it,p[x].iq=p[x<<1|1].iq,p[x].is=p[x<<1|1].is;
		return;
	}
	init(x<<1,d);
	p[x].it=p[x<<1].it+p[x<<1|1].t;
	p[x].iq.l=min(p[x<<1].iq.l,p[x<<1|1].q.l+p[x<<1].it.l);
	p[x].iq.r=max(p[x<<1].iq.r,p[x<<1|1].q.r+p[x<<1].it.r);
	p[x].is=p[x<<1].is+p[x<<1|1].sl;
}
int gets(int x,int d,qj sum,int ans,int xy){
	if(p[x].l==p[x].r)return ans+p[x].sl;
	int mid=p[x].l+p[x].r>>1;
	if(d>mid)return gets(x<<1|1,d,sum,ans,1);
	if(xy){
		qj rt=p[x<<1].it+p[x<<1|1].q+sum;
		if(rt.l<=0&&rt.r>=0)return gets(x<<1|1,d,sum+p[x<<1].it,ans+p[x<<1].is,0);
		else return gets(x<<1,d,sum,ans,1);
	}else{
		qj rt=p[x<<1].t+p[x<<1|1].q+sum;
		if(rt.l<=0&&rt.r>=0)return gets(x<<1|1,d,sum+p[x<<1].t,ans+p[x<<1].sl,0);
		else return gets(x<<1,d,sum,ans,0);
	}
}
int sol(int x){
	qj fw=gets1(1,x-1);
	fw.l=min(0,fw.l),fw.r=max(fw.r,0);
	init(1,x);
	return gets(1,x,fw,0,1);
}
int solve(int x){
	int ans=0;
	for(int i=0;i<wz[x].size();i++){
		ans=max(ans,sol(wz[x][i]));
	}
	return ans;
}
int sequence(int N,vector<int>w){
	n=N;
	reset(1,1,n);
	for(int i=0;i<n;i++){
		wz[w[i]].push_back(i+1);
	}
	for(int i=1;i<=n;i++){
		gx(i-1,-1);
		gx(i,0);
		gx(i+1,1);
		res=max(res,solve(i));
	}
	return res;
}
```


---

## 作者：2x6_81 (赞：6)

## 题目大意

定义 $W(l, r, x)$ 表示 $a_l, \cdots, a_r$ 中 $x$ 的出现次数。定义中位数集合 $S(\{b_0, b_1, \cdots, b_{k - 1}\})$，表示序列 $b_0, b_1, \cdots, b_{k - 1}$ 的一个或两个可能的中位数构成的集合。

已知 $n$ 和序列 $a_0, a_1, \cdots a_{n - 1}$，求对于所有的 $0 \le l \le r \le n - 1$ 中，$\max\limits_{x \in S(l, r)} W(l, r, x)$ 的最大值，其中 $S(l, r)$ 表示 $S(\{a_l, \cdots, a_r\})$。

$1 \le n \le 5 \times 10^5, 1 \le a_i \le n$。

## 题解

在这里我提供了两种解法。第一种解法是我在赛后在室友提示下过了一周后才想出的，第二种解法是通过[官方标程](https://github.com/apio2023/apio2023_tasks/blob/main/sequence/solutions/model_solution/)看出的解答。

### 解法一（常数略大）

首先从小到大枚举中位数 $m$。对于一个 $m$，令 $q_i = \begin{cases} 1, a_i > m \\ 0, a_i = m \\ -1, a_i < m \end{cases}, s_r = \sum\limits_{i = 1}^r q_i$。

则 $m \in S(l, r)$ 当且仅当 $W(l, r, m) \ge \lvert s_r - s_{l - 1} \rvert$。

于是，可以如下暴力：找到所有 $m$ 在 $a$ 中的位置 $p_1, p_2, \cdots, p_w$，定义 $p_0 = 0, p_{w + 1} = n$，枚举 $1 \le L, R \le w$，在 $p_{L - 1} \sim p_L - 1$ 之间找一个位置 $u, p_{R} \sim p_{R + 1} - 1$ 之间找一个位置 $v$，使得 $\lvert s_v - s_u \rvert \le R - L + 1$ 即可。这个是容易的，用线段树维护前缀和即可。

考虑如何优化这个暴力。由于 $W(l, r, m) \ge \lvert s_r - s_{l - 1} \rvert \Leftrightarrow -W(l, r, m) \le s_r - s_{l - 1} \le W(l, r, m) \Leftrightarrow \begin{cases} W(l, r, m) + (s_r - s_{l - 1}) \ge 0 \\ W(l, r, m) - (s_r - s_{l - 1}) \ge 0 \end{cases}$。

于是考虑维护以下两个东西：$t_{1, k} = W(0, k, m) + s_k, t_{2, k} = W(0, k, m) - s_k$。定义 $mx_{1, k} = \max\limits_{i = p_k}^{p_{k + 1} - 1} t_{1, i}, mx_{2, k} = \max\limits_{i = p_k}^{p_{k + 1} - 1} t_{2, i}$，分别表示在 $p_k \sim p_{k + 1} - 1$ 这段区间内，$t_{1}$ 和 $t_{2}$ 的最大值。上述操作可以用一棵支持区间加、区间查 $\max$ 的线段树维护。

相应的定义 $mn_{1, k}$ 和 $mn_{2, k}$，分别表示在 $p_k \sim p_{k + 1} - 1$ 这段区间内，$t_{1}$ 和 $t_{2}$ 的最小值。由于这段区间内 $t_{1, j} + t_{2, j} = 2k$，可以得到 $mn_{1, k} = 2k - mx_{2, k}, mn_{2, k} = 2k - mx_{1, k}$。

由于每段区间内的 $t_1, t_2$ 只有 $\pm 1$ 的变化，因此 $t_1$ 能取遍 $[mn_1, mx_1], t_2$ 同理。

于是就可以枚举起点 $u$，找到最后一段使得存在位置 $v$ 满足 $\begin{cases} t_{1, v} \ge t_{1, u} \\ t_{2, v} \ge t_{2, u} \end{cases}$。这里有一个重要的结论：对于两段 $0 \le x_1 < x_2 \le w$，存在上述的位置 $v$ 当且仅当 $\begin{cases} mn_{1, x_1} \le mx_{1, x_2} \\ mn_{2, x_1} \le mx_{2, x_2} \end{cases}$。

若结论成立，那么这就是一个二维数点问题，即：已知平面上所有点 $(mx_{1, x}, mx_{2, x})\ (0 \le x \le w)$，以及每个点有权值 $x$，求所有横坐标 $\ge mn_{1, z}$ 且纵坐标 $\ge mn_{2, z}$ 的所有点中权值（即 $x$）的 $\max$。而最后的答案是所有 $x - z$ 的最大值，这是容易的。

时间复杂度 $O(n \log n)$。

那么结论为什么成立？有两种理解方式。

第一种理解方式：分类讨论。

第一种情况：$[mn_{1, x}, mx_{1, x}]$ 与 $[mn_{1, z}, mx_{1, z}]$ 的交集非空，此时可以在两段分别取位置 $u, v$ 使得 $t_{1, u} = t_{1, v}$，此时必有 $t_{2, u} \le t_{2, v}$，则可以满足条件。

第二种情况：$[mn_{2, x}, mx_{2, x}]$ 与 $[mn_{2, z}, mx_{2, z}]$ 的交集非空，此时同理。

第三种情况：上面两种情况均不成立，则只有在 $mn_{1, x} > mx_{1, z}$ 且 $mn_{2, x} > mx_{2, z}$ 时满足条件。

综合上面三种情况，可以得到满足条件的充要条件是 $mx_{1, x} \ge mn_{1, z}$ 且 $mx_{2, x} \ge mn_{2, z}$。

第二种理解方式：图像法。

将每段可能的点在坐标轴上画出，可以发现每一段都是在一条斜率为 $-1$ 的直线上，由于询问的性质知道可以取这些元素的右上角 $(mx_{1, x}, mx_{2, x})$ 作为代表。

而在询问时，由于权值比该段大的点不可能位于此段对应的正方形的左下角区域，因此可以取 $(mn_{1, z}, mn_{2, z})$ 作为代表。

代码附在最后。

### 解法二（官方标答）

还是从小到大枚举中位数 $m$，沿用解法一的 $p_0, p_1, \cdots, p_w, p_{w + 1}$。

这次，他定义 $r_k = \begin{cases} -1, < m \\ 1, \ge m \end{cases}, s_k = \begin{cases} -1, \le m \\ 1, > m \end{cases}, x_r = \sum\limits_{i = 1}^r r_i, y_r = \sum\limits_{i = 1}^r s_i$。

则 $m \in S(l, r)$ 的充要条件是 $x_{l - 1} \le x_r \land y_{l - 1} \ge y_r$。

由于 $x, y$ 的变化量是 $\pm 1$ 的，因此 $x, y$ 是连续的，即对于任意一段连续区间，若已知其上下界，则上下界内的任意一个值在该区间内均存在。

定义 $pmn_k = \min\limits_{i = 0}^{p_k - 1} x_i, pmx_k = \max\limits_{i = 0}^{p_k - 1} y_i, smn_k = \min\limits_{i = p_k}^{n - 1} y_i, smx_k = \max\limits_{i = p_k}^{n - 1} x_i$。

借鉴解法一的想法，可以把 $(pmn_k, pmx_k)$ 看作平面上的点，而所询问的即为 $(smx_k, smn_k)$ 的左上方的点中下标最小的。这里的限制比解法一更加松。

我们从左到右枚举询问的点的下标进行查询，可以发现，随着下标的增加，两条直线所交出的区域在逐渐变小，并且都是前一个的子区域。于是可以用双指针的写法，使得代码更加简单。

时间复杂度 $O(n \log n)$，常数较小。在双指针处更是直接 $O(n)$，而且代码较短。

### 最后附上解法一的代码

```cpp
#include "sequence.h"

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair <int, int> pii;
const int N = 5e5 + 5;
int cnt[N];
struct Segtree {
    int tremx[N << 2], tag[N << 2], n;
    inline void build (int nn) { n = nn; }
    inline void pushdown(int p, int l, int r) {
        if (tag[p] == 0) return;
        tremx[p << 1] += tag[p]; tag[p << 1] += tag[p];
        tremx[p << 1 | 1] += tag[p]; tag[p << 1 | 1] += tag[p];
        tag[p] = 0;
    }
    inline void pushup(int p) {
        tremx[p] = max(tremx[p << 1], tremx[p << 1 | 1]);
    }
    void _upd(int p, int uL, int uR, int l, int r, int val) { // [l, r] +val
        if (uL <= l && r <= uR) {
            tremx[p] += val; tag[p] += val; return;
        }
        pushdown(p, l, r);
        int mid = (l + r) >> 1;
        if (uL <= mid) _upd(p << 1, uL, uR, l, mid, val);
        if (mid < uR) _upd(p << 1 | 1, uL, uR, mid + 1, r, val);
        pushup(p);
    }
    int _queryMax(int p, int qL, int qR, int l, int r) {
        if (qL <= l && r <= qR) return tremx[p];
        pushdown(p, l, r);
        int mid = (l + r) >> 1, ret = INT_MIN;
        if (qL <= mid) ret = max(ret, _queryMax(p << 1, qL, qR, l, mid));
        if (mid < qR) ret = max(ret, _queryMax(p << 1 | 1, qL, qR, mid + 1, r));
        pushup(p);
        return ret;
    }
    void upd(int uL, int val) { _upd(1, uL, n, 1, n, val); }
    int queryMax(int qL, int qR) { return _queryMax(1, qL, qR, 1, n); }
} T1, T2;
vector <int> vec[N], Max1, Max2;
struct BITcmax {
    int tre[N << 1], n;
    inline void clear(int n) {
        memset(tre, 0, (n + 1) << 2);
    }
    inline void init(int nn) { n = nn; }
    void upd(int pos, int val) {
        for (; pos <= n; pos += (pos & (-pos))) tre[pos] = max(tre[pos], val);
    }
    int query(int pos) {
        int ret = 0;
        for (; pos; pos &= (pos - 1)) ret = max(ret, tre[pos]);
        return ret;
    }
} T3;
vector <pair <pii, int> > Point, Query;
vector <int> B;
int sequence(int N, std::vector<int> A) {
    T1.build(N), T2.build(N);
    for (int i = 0; i < N; i++) vec[A[i]].push_back(i + 1), T1.upd(i + 1, 1), T2.upd(i + 1, -1);
    int Ans = 1;
    for (int i = 1; i <= N; i++) {
        for (auto v : vec[i - 1]) T1.upd(v, -2);
        for (auto v : vec[i]) T2.upd(v, 2);
        if (vec[i].empty()) continue;
        Max1.clear(); Max2.clear();
        if (vec[i][0] > 1) Max1.push_back(max(0, T1.queryMax(1, vec[i][0] - 1))), Max2.push_back(max(0, T2.queryMax(1, vec[i][0] - 1)));
        else Max1.push_back(0), Max2.push_back(0);
        for (int j = 0; j < vec[i].size(); j++) {
            int v = vec[i][j];
            if (j + 1 == vec[i].size()) Max1.push_back(T1.queryMax(v, N)), Max2.push_back(T2.queryMax(v, N));
            else Max1.push_back(T1.queryMax(v, vec[i][j + 1] - 1)), Max2.push_back(T2.queryMax(v, vec[i][j + 1] - 1));
        }
        B.clear();
        for (int j = 0; j < Max1.size(); j++) {
            if (j) Point.emplace_back(pii(Max1[j], Max2[j]), j), B.push_back(Max2[j]);
            Query.emplace_back(pii((j << 1) - Max2[j], (j << 1) - Max1[j]), j), B.push_back((j << 1) - Max1[j]);
        }
        sort(B.begin(), B.end()); B.erase(unique(B.begin(), B.end()), B.end());
        for (auto& v : Point) v.first.second = lower_bound(B.begin(), B.end(), v.first.second) - B.begin() + 1;
        for (auto& v : Query) v.first.second = lower_bound(B.begin(), B.end(), v.first.second) - B.begin() + 1;
        sort(Point.begin(), Point.end()); reverse(Point.begin(), Point.end());
        sort(Query.begin(), Query.end()); reverse(Query.begin(), Query.end());
        T3.init(B.size());
        int ppos = 0;
        for (auto v : Query) {
            while (ppos < Point.size() && v.first.first <= Point[ppos].first.first) T3.upd(B.size() - Point[ppos].first.second + 1, Point[ppos].second), ppos++;
            Ans = max(Ans, T3.query(B.size() - v.first.second + 1) - v.second);
        }
        T3.clear(B.size());
        Point.clear(); Query.clear();
    }
    return Ans;
}

```

---

## 作者：rainygame (赞：5)

数据结构神题！（or 这是我不知道的 trick？）

按照题目中的定义，若一个数 $x$ 为 $\{a_n\}$ 的中位数，那么令 $H=\sum\limits_{i=1}^n[a_i>x],L=\sum\limits_{i=1}^n[a_i<x]$，则可以分为以下两种情况：

- $H < L$，此时需要满足 $H-L+S \ge 0$，否则 $x$ 会更小。
- $H \ge L$，此时需要满足 $H-L-S \le 0$，否则 $x$ 会更大。

考虑枚举中位数 $x$，生成两个数列满足：

$$
\begin{aligned}
h_i = \begin{cases}
-1, &a_i < x\\
1, &a_i \ge x
\end{cases}\\
g_i = \begin{cases}
-1, &a_i \le x\\
1, &a_i > x
\end{cases}
\end{aligned}
$$

显然每个数只会变化最多一次（从 $1$ 变为 $-1$），所以变化次数是 $O(n)$ 的。

预处理出 $p_1 < p_2 < \dots < p_k$ 满足 $a_{p_i}=x$。对 $p$ 做双指针（单调性稍后证明）。对于一个区间 $p[l,r]$，计算出 $w$ 表示 $i \in [p_l,p_r]$ 中满足 $a_i \ne x$ 的 $h_i$ 之和，对 $w$ 进行分类讨论：

- $w < 0$。这说明 $>x$ 的数比 $<x$ 的数小，此时需要扩展更多的 $>x$ 的数来保证中位数为 $x$。
- $w > 0$。这说明 $>x$ 的数比 $<x$ 的数多，此时需要扩展更多的 $<x$ 的数来保证中位数为 $x$。
- $w=0$，易证此时 $[p_l,p_r]$ 以的中位数集合包含 $x$。

对于这个，可以在 $\{h_n\}$ 和 $\{l_n\}$ 上用线段树维护区间前缀后缀最值即可。但是如何判断是否有足够可以扩展的数使得 $x$ 为中位数呢？回到开头的柿子，发现只需要根据那两个不等式来判断即可。对于 $w > 0$ 只需要判断第 $1$ 条即可，而 $w < 0$ 只需要判断第 $2$ 条即可。判断的代码：

```cpp
bool check(int w, int len, int l, int r){
    if (w <= 0) return (l ? H.query(1, 0, l-1).maxr : 0)+(r<n-1 ? H.query(1, r+1, n-1).maxl : 0)+w+len >= 0;
    return (l ? L.query(1, 0, l-1).minr : 0)+(r<n-1 ? L.query(1, r+1, n-1).minl : 0)+w-len <= 0;
}
```

对于双指针单调性的问题，显然如果有一个以 $x$ 为中位数的区间 $[l,r]$ 满足 $[p_l,p_r] \subset [l,r]$，那么有 $[p_l,p_{r-1}] \subset [l,r]$。

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 500001

int n;
vector<int> p[MAXN];

struct Node{
    int l, r, sum;
    int maxl, minl, maxr, minr;
    Node():sum(0), maxl(0), minl(1e6), maxr(0), minr(1e6){;}
};

struct Seg{
    Node tree[MAXN<<2];
    void merge(Node &c, Node a, Node b){
        c.sum = a.sum + b.sum;
        c.maxl = max(a.maxl, a.sum+b.maxl);
        c.maxr = max(b.maxr, b.sum+a.maxr);
        c.minl = min(a.minl, a.sum+b.minl);
        c.minr = min(b.minr, b.sum+a.minr);
    }
#define push_up(p) merge(tree[p], tree[p<<1], tree[p<<1|1])

    void build(int p, int l, int r){
        tree[p].l = l;
        tree[p].r = r;
        if (l == r){
            tree[p].sum = tree[p].maxl = tree[p].maxr = 1;
            tree[p].minl = tree[p].minr = 0;
            return;
        }

        int mid((l+r)>>1);
        build(p<<1, l, mid);
        build(p<<1|1, mid+1, r);
        push_up(p);
    }

    void modify(int p, int x){
        if (tree[p].l == tree[p].r){
            tree[p].maxl = tree[p].maxr = 0;
            tree[p].sum = tree[p].minl = tree[p].minr = -1;
            return;
        }

        int mid((tree[p].l+tree[p].r)>>1);
        if (x <= mid) modify(p<<1, x);
        else modify(p<<1|1, x);
        push_up(p);
    }

    Node query(int p, int L, int R){
        if (tree[p].l >= L && tree[p].r <= R) return tree[p];
        int mid((tree[p].l+tree[p].r)>>1);
        Node res;
        if (L <= mid) merge(res, res, query(p<<1, L, R));
        if (R > mid) merge(res, res, query(p<<1|1, L, R));
        return res;
    }
}H, L;

bool check(int w, int len, int l, int r){
    // if (len == 3 && l == 1) cout << w << ' ' << l << ' ' << r << ' ' << (l ? L.query(1, 0, l-1).minr : 0)+(r<n-1 ? L.query(1, r+1, n-1).minl : 0)+w-len << '\n';
    if (w <= 0) return (l ? H.query(1, 0, l-1).maxr : 0)+(r<n-1 ? H.query(1, r+1, n-1).maxl : 0)+w+len >= 0;
    return (l ? L.query(1, 0, l-1).minr : 0)+(r<n-1 ? L.query(1, r+1, n-1).minl : 0)+w-len <= 0;
}

int sequence(int N, vector<int> A){
    int ans(0);
    n = N;
    for (int i(0); i<n; ++i) p[A[i]].push_back(i);

    H.build(1, 0, n-1);
    L.build(1, 0, n-1);
    for (int i(1); i<=n; ++i){
        for (auto i: p[i]) L.modify(1, i);
        for (int l(0), r(0); l<p[i].size(); ++l){
            for (; r<p[i].size()-1 && check(H.query(1, p[i][l], p[i][r+1]).sum-(r-l+2), r-l+2, p[i][l], p[i][r+1]); ++r);
            ans = max(ans, r-l+1);
        }

        for (auto i: p[i]) H.modify(1, i);
    }

    return ans;
}
```

---

## 作者：良心WA题人 (赞：5)

## 前言

APIO 打得难受，会这题结果寄了。

写篇题解纪念一下。

## 题意

给定一个序列，求出子区间里中位数出现的次数的最大值。

## 思路

首先看到中位数想到转 $1$ 和 $-1$，即钦定一个数设定小于它的数的权值为 $-1$，大于它的数权值设为 $1$。若在一个区间中权值为 $0$（偶数长度的区间为 $-1$ 或 $1$），则钦定的这个数为中位数。证明显然。

那么对于本题有多个数可能相同的时候，只需要将中位数设为 $-1$ 时权值 $\le0$，设为 $1$ 时权值 $\ge0$ 这个数就是中位数了。证明亦显然。

显然，若两个区间中位数相同，包含了另一个区间的区间一定不会劣于另一个区间。有了这个想法后，现在考虑如何钦定这个中位数是什么。考虑枚举区间的左端点，将左端点的这个数钦定为中位数，寻找最大的右端点。

然而，这样的定义是错误的，无法找到最大的区间。因为我们钦定的这个中位数不一定是区间的左端点。所以，我们考虑计算包含钦定的区间的所有区间中是否存在一个区间使得该数为中位数。不难发现，这样仍然能找到答案。

那么这个算法如何去完成呢？假定右端点为 $l-1$ 的所有区间的权值的最大值为 $a$，最小值为 $b$，钦定区间的权值为 $t$，那么若 $a+t\ge0$ 且 $b+t\le0$ 则一定能找到一个包含钦定区间的区间使得 $l$ 的数为中位数。考虑证明这个结论，因为 $t$ 是一个定值，所以不考虑 $t$，直接加到 $a,b$ 上。考虑 $a$ 到 $b$ 之间是如何变化的。不难发现，我们将权值为 $a$ 对应的区间一次去掉或增加一个左端点，直到变成权值为 $b$ 的区间，这个区间的权值每次增加或减少 $2$ 或不变，则从非正数变成非负数的过程中一定会存在一个区间权值为 $0$ 且右端点为 $l-1$，满足我们的定义。对于右端点，我们可以类似地处理。

考虑如何计算一个区间的权值，只需要建一个线段树，所有点的权值钦定为 $1$，从小到大枚举所有的数，将当前枚举到的数变成 $-1$ 之前计算得到 $t1$，变成 $-1$ 后计算得到 $t2$，则我们要找的就是是否存在 $a+t1\ge0$ 且 $b+t2\le0$。

但是 $a$ 和 $b$ 这样定义并不好求。因为 $a$ 和 $b$ 的右端点是固定的，所以我们可以将线段树改成前缀和或后缀和的最大值、最小值的形式。这样我们就可以轻松地求得 $a,b$。

我们有了一个快速判断包含区间的所有区间中是否存在合法区间的方法。不过，这样仍然无法在 $n^2$ 以内求得答案。但是，我们可以发现经过刚刚的修改会有一个惊人的性质：单调性。具体的，当我们钦定了 $l,r+1$ 且满足要求后，则 $l,r$ 一定也满足要求。证明显然。那么，我们就可以进行二分了。直接二分是 $O(n\log^2n)$ 的，但是若在线段树上二分可以做到 $O(n\log n)$，具体就不赘述了，大家应该都会，不会的网上讲得好的资料也不少。

代码不难写，而且考场代码写的很屎怕误导大家，这里就不放了，读者不妨自行完成。

---

## 作者：pikiuk (赞：3)

我们注意到一个数是否是中位数仅和大于他的数的个数，小于他的数的个数以及他的个数有关（我们不妨分别记作 $c_0,c_1,c_x$），显然，若他是中位数，则应该满足下述条件：

1. $c_x>0$。
2. $c_0+c_x\geq c_1$。
3. $c_1+c_x\geq c_0$。

不难想到用两个序列分别维护 $c_0+c_x-c_1$ 和 $c_1+c_x-c_0$ 的前缀和，分别记作 $s_1,s_2$。另外注意到条件不是那么重要，因为计数的时候会被统计为 $0$，故暂且抛开不管。那么对于区间 $[l,r]$，某个数是中位数的条件改写为：

1. $s_{1,r}\geq s_{1,l-1}$。
2. $s_{2,r}\geq s_{2,l-1}$。

注意到若我们从小到大枚举中位数，$s_1,s_2$ 可以在总共不超过 $\mathcal{O}(n\log n)$ 的时间内更新（因为每次我们只需要更新当且枚举的数所在位置的 $s$，用线段树维护即可），那么，我们只需要考虑对于确定的 $x$，怎么维护满足上述两个条件且出现 $x$ 次数最多的区间。

我们提出所有 $x$ 所在的位置（记作 $\{p_k\}$），他们把原序列分割成若干段：

我们把 $s_1,s_2$ 分别看作 $x$ 轴和 $y$ 轴，每一段的图像相当于一条斜率为 $-1$ 的直线，而贡献的形式应该是某一段直线的最高点对某一段直线的最低点产生贡献。

![1687353460435.png](https://img.macesuted.moe/77f919a84b87a2d6c568c71a9dbe508c/80cf98d9ada4d.png)

(如上图，黑色直线为某一段的图像，红色为另一端的图像，蓝点为黑色最高点，绿点为红色最低点，两者满足偏序关系，故黑色所代表段对红色有贡献。)

因此，我们对 $x$ 的所有位置从左到右做扫描线，对于第 $i$ 段求出最小的 $s_1,s_2$，当作可能的左端点，并将其贡献记作 $i$，对于每段最大的 $s_1,s_2$ 同理，查询时只需要对于每个可能的右端点，找到可能的左端点中对他的合法的贡献最小的端点，并把两者贡献相减，更新答案即可，这部分是经典的二维偏序，另外，注意到 $s_1,s_2$ 可能是负值，因此在插入树状数组是应整体平移一段值域再插入。

具体细节见代码：

```c++
#include<bits/stdc++.h>
#define Maxn 500007
const int inf = 0x3f3f3f3f;
using namespace std;
int cnt, ans = inf, n; vector<int> pos[Maxn];
struct Seg {
	int mx[Maxn << 2], mn[Maxn << 2], tag[Maxn << 2];
	int ls(int x) {return x << 1;}
	int rs(int x) {return x << 1 | 1;}
	void pushup(int p) {
		mx[p] = max(mx[ls(p)], mx[rs(p)]);
		mn[p] = min(mn[ls(p)], mn[rs(p)]);
	} 
	void pushdown(int p) {
		mx[ls(p)] += tag[p]; mn[ls(p)] += tag[p];
		mx[rs(p)] += tag[p]; mn[rs(p)] += tag[p];
		tag[ls(p)] += tag[p]; tag[rs(p)] += tag[p]; tag[p] = 0;
	}
	void modify(int p, int l, int r, int ql, int qr, int k) {
		if(ql <= l and r <= qr) {
			return mx[p] += k, mn[p] += k, tag[p] += k, void();
		} pushdown(p); int mid = (l + r) >> 1;
		if(ql <= mid) modify(ls(p), l, mid, ql, qr, k);
		if(qr > mid) modify(rs(p), mid + 1, r, ql, qr, k);
		pushup(p);
	}
	int qrmin(int p, int l, int r, int ql, int qr) {
		if(ql <= l and r <= qr) return mn[p];
		int res = inf; int mid = (l + r) >> 1; pushdown(p);
		if(ql <= mid) res = min(res, qrmin(ls(p), l, mid, ql, qr));
		if(qr > mid) res = min(res, qrmin(rs(p), mid + 1, r, ql, qr)); return res;
	}
	int qrmax(int p, int l, int r, int ql, int qr) {
		if(ql <= l and r <= qr) return mx[p];
		int res = -inf; int mid = (l + r) >> 1; pushdown(p);
		if(ql <= mid) res = max(res, qrmax(ls(p), l, mid, ql, qr));
		if(qr > mid) res = max(res, qrmax(rs(p), mid + 1, r, ql, qr)); return res;
	}	
} tx, ty; 
struct Q {
	int opt, x, y, k;
} qr[Maxn];
struct Fwt {
	int a[Maxn << 1];
	void modify(int pos, int x) {for(; pos; pos -= pos & -pos) a[pos] = min(a[pos], x);}
	int query(int pos) {int res = inf; for(; pos <= 2 * n; pos += pos & -pos) res = min(res, a[pos]); return res;}
	void clear(int pos) {for(; pos; pos -= pos & -pos) a[pos] = inf;}
} T;
void calc() {
	sort(qr + 1, qr + cnt + 1, [](const Q x, const Q y) {return x.x == y.x ? x.opt > y.opt : x.x > y.x;});
	for(int i = 1; i <= cnt; i ++) qr[i].y = qr[i].y + n + 1;
	for(int i = 1; i <= cnt; i ++) {
		if(qr[i].opt & 1) T.modify(qr[i].y, qr[i].k);
		else ans = max(ans, qr[i].k - T.query(qr[i].y));
	}
	for(int i = 1; i <= cnt; i ++) T.clear(qr[i].y);
	
}
int sequence(int N, vector<int> A) {
	n = N; for(int i = 1; i <= n; i ++) pos[A[i - 1]].push_back(i); 
	ans = -inf; memset(T.a, 0x3f, sizeof T.a); 
	for(int i = 1; i <= n; i ++) tx.modify(1, 0, n, i, n, 1), ty.modify(1, 0, n, i, n, -1);
	for(int i = 1; i <= n; i ++) {
		if(pos[i].empty()) continue;
		for(auto j : pos[i]) tx.modify(1, 0, n, j, n, -2);
		cnt = 0; pos[i].push_back(n + 1);
		for(int j = 0, res, lst = 0; j < (int) pos[i].size(); j ++) {
			res = pos[i][j]; 
			qr[++ cnt] = {1, tx.qrmax(1, 0, n, lst, res - 1), ty.qrmax(1, 0, n, lst, res - 1), j};
			qr[++ cnt] = {0, tx.qrmin(1, 0, n, lst, res - 1), ty.qrmin(1, 0, n, lst, res - 1), j};
			lst = res;
		} calc(); pos[i].pop_back();
		for(auto j : pos[i]) ty.modify(1, 0, n, j, n, 2);
	} 
	return ans;
}
```

---
感谢 @Celtic 提供图片，阿里嘎多。





---

## 作者：Graphcity (赞：3)

注意到 $1\le a_i\le n$，思考值域相关做法。一个自然的想法就是枚举中位数 $c$。经过分析，我们发现，如果 $c$ 是可重集合 $S$ 的中位数，则：

- $S$ 中包含至少一个 $c$。
- $S$ 中 $\le c$ 的数字个数 **大于等于** $>c$ 的数字个数。
- $S$ 中 $\ge c$ 的数字个数 **大于等于** $<c$ 的数字个数。

为了方便，我们定义 $f_1(x)=\begin{cases}1 & x\le c \\ -1 & x>c \end{cases}$，$f_2(x)=\begin{cases}1 & x\ge c \\ -1 & x<c \end{cases}$。那么后面的两个限制相当于集合中所有数的 $f_1,f_2$ 之和 $\ge 0$。此外，我们还发现第一个限制不影响答案，因为不包含 $c$ 的方案肯定不是最优方案。

接下来把视野放到序列上。记 $s_{1,i}$ 和 $s_{2,i}$ 为序列第 $i$ 个位置 $f_1$ 和 $f_2$ 的前缀和，$w_i$ 为前 $i$ 个数中 $c$ 的出现次数。那么区间 $[l,r]$ 满足条件当且仅当 $s_{1,r}\ge s_{1,l-1}$ 并且 $s_{2,r}\ge s_{2,l-1}$，价值为 $c_r-c_{l-1}$。这是一个二维偏序问题，可以使用树状数组 $O(n\log n)$ 找到答案。加上枚举总时间复杂度 $O(n^2\log n)$。

考虑优化。注意到枚举 $c$ 时不等于 $c$ 的数并没有多大用，可以简化这部分信息。具体而言，对于一段连续的不等于 $c$ 的数，只有三个东西是有用的：

- 这一段的 $f_1$ 之和
- 这一段 $f_1$ 的最大值和最小值

注意到这一段没有 $c$，所以 $f_2=-f_1$。可以用线段树维护这些信息。这里采用整体二分实现。具体地，在整体二分中，对于 $\le mid$ 的部分，那么 $>mid$ 的数字信息可以简化。对于 $>mid$ 的部分，那么 $\le mid$ 的数字信息可以简化。

经过简化之后，每一层的无用信息不超过有用信息个数 $+1$，保证了时间复杂度。在底层二维偏序使用树状数组。时间复杂度 $O(n\log n)$。

```cpp
#include "sequence.h"
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5,inf=1e9;

int n,a[Maxn+5],ans;

namespace T1
{
    int s1[4005],s2[4005],cnt[4005],pos[4005],t[4005],mx;
    #define lowbit(x) (x&-x)
    void Add(int x,int y) {while(x<=n*2+1) t[x]=min(t[x],y),x+=lowbit(x);}
    int Count(int x) {int res=inf; while(x) res=min(res,t[x]),x-=lowbit(x); return res;}
    #undef lowbit
    int Run()
    {
        int ans=0;
        For(i,1,n) mx=max(mx,a[i]);
        For(x,1,mx)
        {
            For(i,1,n*2+1) t[i]=inf;
            For(i,1,n)
            {
                s1[i]=s1[i-1]+(a[i]<=x?1:-1);
                s2[i]=s2[i-1]+(a[i]>=x?1:-1);
                cnt[i]=cnt[i-1]+(a[i]==x);
            }
            For(i,0,n) pos[i]=i;
            sort(pos,pos+n+1,[&](int a,int b){
                if(s1[a]!=s1[b]) return s1[a]<s1[b];
                if(s2[a]!=s2[b]) return s2[a]<s2[b];
                if(cnt[a]!=cnt[b]) return cnt[a]<cnt[b];
            });
            For(id,0,n)
            {
                int i=pos[id];
                ans=max(ans,cnt[i]-Count(s2[i]+n+1));
                Add(s2[i]+n+1,cnt[i]);
            }
        }
        return ans;
    }
}

struct Group{bool op; int mn,mx,k;};
Group operator+(Group a,Group b)
{
    Group c=a; c.mn=min(c.mn,a.k+b.mn),c.mx=max(c.mx,a.k+b.mx);
    c.k=a.k+b.k,c.op=0; return c;
}
struct Node{int a,b,c;};
bool operator<(Node x,Node y)
{
    if(x.a!=y.a) return x.a<y.a;
    if(x.b!=y.b) return x.b<y.b;
    if(x.c!=y.c) return x.c<y.c;
}

struct Fenwick
{
    int t[Maxn*2+5],siz;
    #define lowbit(x) (x&-x)
    void Clear(int x) {siz=x; For(i,1,siz) t[i]=inf;}
    void Add(int x,int y) {while(x<=siz) t[x]=min(t[x],y),x+=lowbit(x);}
    int Count(int x) {int res=inf; while(x) res=min(res,t[x]),x-=lowbit(x); return res;}
    #undef lowbit
} T;

void Doit(vector<Node> &w1,vector<Node> &w2)
{
    vector<int> w;
    for(auto i:w1) w.push_back(i.b);
    for(auto i:w2) w.push_back(i.b);
    sort(w.begin(),w.end()),w.erase(unique(w.begin(),w.end()),w.end());
    int siz=w.size(); T.Clear(siz);
    for(auto &i:w1) i.b=lower_bound(w.begin(),w.end(),i.b)-w.begin()+1;
    for(auto &i:w2) i.b=lower_bound(w.begin(),w.end(),i.b)-w.begin()+1;
    int it=0;
    sort(w1.begin(),w1.end()),sort(w2.begin(),w2.end());
    for(auto i:w2)
    {
        while(it<w1.size() && w1[it].a<=i.a) T.Add(w1[it].b,w1[it].c),it++;
        ans=max(ans,i.c-T.Count(i.b));
    }
}
void dfs(int l,int r,vector<Group> V)
{
    // printf("%d %d:\n",l,r);
    // for(auto i:V) printf("%d %d %d %d\n",i.op,i.mn,i.mx,i.k);
    if(l==r)
    {
        int cnt=0,s1=0,s2=0; vector<Node> w1,w2;
        w1.push_back((Node){0,0,0}),w2.push_back((Node){0,0,0});
        for(auto i:V)
        {
            if(i.op==1)
            {
                cnt++,s1++,s2++;
                w1.push_back((Node){s1,s2,cnt});
                w2.push_back((Node){s1,s2,cnt});
                continue;
            }
            int a=s1+i.mn,b=s1+i.mx;
            int c=s2-i.mx,d=s2-i.mn;
            w1.push_back((Node){a,c,cnt});
            w2.push_back((Node){b,d,cnt});
            s1+=i.k,s2-=i.k;
        }
        Doit(w1,w2);
        return;
    }
    int mid=(l+r)>>1;
    vector<Group> V1,V2;
    int flg=0; Group w;
    for(auto i:V)
    {
        if(i.op==1 && i.k<=mid)
        {
            if(flg) V1.push_back(w),flg=0;
            V1.push_back(i); continue;
        }
        if(!flg)
        {
            flg=1;
            if(i.op==0) w=i; else w=Group{0,-1,-1,-1};
            continue;
        }
        if(i.op==0) w=w+i;
        else w=w+Group{0,-1,-1,-1};
    }
    if(flg) flg=0,V1.push_back(w);
    for(auto i:V)
    {
        if(i.op==1 && i.k>mid)
        {
            if(flg) V2.push_back(w),flg=0;
            V2.push_back(i); continue;
        }
        if(!flg)
        {
            flg=1;
            if(i.op==0) w=i; else w=Group{0,1,1,1};
            continue;
        }
        if(i.op==0) w=w+i;
        else w=w+Group{0,1,1,1};
    }
    if(flg) flg=0,V2.push_back(w);
    dfs(l,mid,V1),dfs(mid+1,r,V2);
}

int Work()
{
    if(n<=2000) return T1::Run();
    vector<Group> w;
    For(i,1,n) w.push_back((Group){1,1,1,a[i]});
    dfs(1,n,w);
    return ans;
}

int sequence(int N, std::vector<int> A)
{
    n=N;
    For(i,1,n) a[i]=A[i-1];
    return Work();
}
```

---

## 作者：SDSXC (赞：2)

一个码量略大，常数巨大（但是好像跑的挺快？），但是不怎么需要脑子的做法。

考虑如何计算将某个数 $x$ 作为中位数时的最大价值。

注意到数只有小于 $x$，大于 $x$，等于 $x$，三种有区别的状态。考虑 01 原理，将三种数分别赋值为 $-1,1,0$。注意下文提到的 $a_i$ 都是指这个只有 $-1,1,0$ 的序列。

考虑一个包含 $k$ 个 $x$ 的集合 $S$ 中位数为 $x$ 的条件是什么，显然等价于 $|\sum_{a_i\in S} a_i|\leq k$。

对做前缀和，记作 $S_i=\sum_{j=1}^ia_j$ ，原条件等价于 $-k\leq S_r-S_{l-1}\leq k$。

对于第 $i$ 个 $x$，不难发现他前面的 $S$ 的取值范围是个区间，记作 $[fl_i,fr_i]$，后面的也是个区间，记作 $[gl_i,gr_i]$。所以包含第 $[i,j]$ 个 $x$ 的所有 子区间和 的取值范围为 $[gl_j-fr_i,gr_j-fl_i]$，我们要求他与 $[-k,k]=[-(j-i+1),(j-i+1)]$ 有交。

分类讨论一下不难发现区间 $A$ 与 $B$ 有交等价于 $A$ 的某个端点在 $B$ 中或 $A$ 包含 $B$。于是我们将限制化为如下形式。注意三行之间是或的关系。

$$-(j-i+1)\leq gl_j-fr_i\leq j-i+1$$
$$-(j-i+1)\leq gr_j-fl_i\leq j-i+1$$
$$gl_j-fr_i\leq -(j-i+1)\wedge gr_j-fl_i\geq j-i+1$$

因为三个限制之间是或的关系，所以我们可以分别求解最后对答案取 $max$ 即可。因为三者做法类似，只详细介绍第一个的做法。

我们将原式移个项化为

$$gl_j-j\leq fr_i-i+1\wedge gl_j+j\geq fr_i+i-1$$

发现这变成了一个二维偏序问题，一般这种问题我们用扫描线加 BIT 解决，但是这里有正有负所以其实用 cdq 更好写。

类似地处理剩下两个式子，答案取其中最大的一个。

还有一个问题就是 $fl,fr,gl,gr$ 的求法了，这其实也非常简单，我们在做的时候按照 $x$ 从小到大做，刚做到 $x$ 的时候将所有 $x$ 设为 0，然后计算答案，然后将所有 $x$ 设为 $-1$。需要一种可以支持后缀减一，区间 min,max 的数据结构，线段树显然可做。

最后算一下复杂度，对于某一个 $x$ 如果在数组里出现了 $k$ 次，那么他的复杂度就是 $O(klogn)$ 的线段树再加 $O(klogk)$ 的 cdq。总复杂度是 $O(nlogn)$ 的。

代码虽然比较长，但是很多是重复的东西和板子，实际不难写。


```cpp
#include<bits/stdc++.h>
#define MAXN 500009
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define INF 0x3f3f3f3f
#define vect basic_string
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int sequence(int N, std:: vector<int> A);
int mn[MAXN<<2],mx[MAXN<<2],tag[MAXN<<2];
void up(int rt){
	mx[rt]=max(mx[ls],mx[rs]);
	mn[rt]=min(mn[ls],mn[rs]);
}
void down(int rt){
	if(tag[rt]){
		mx[ls]+=tag[rt];mn[ls]+=tag[rt];tag[ls]+=tag[rt];
		mx[rs]+=tag[rt];mn[rs]+=tag[rt];tag[rs]+=tag[rt];
		tag[rt]=0;
	}
}
void build(int rt,int l,int r){
	if(l==r) {mx[rt]=mn[rt]=l;return;}
	else build(ls,l,mid),build(rs,mid+1,r),up(rt);
}
void upd(int rt,int l,int r,int ul,int ur,int v){
	if(ul>r||ur<l) return;
	if(ul<=l&&ur>=r){
		mx[rt]+=v;mn[rt]+=v;tag[rt]+=v;return;
	}
	down(rt);
	upd(ls,l,mid,ul,ur,v);upd(rs,mid+1,r,ul,ur,v);
	up(rt);
}
int qmx(int rt,int l,int r,int ql,int qr){
	if(ql>r||qr<l) return -INF;
	if(ql<=l&&qr>=r) return mx[rt];
	down(rt);
	return max(qmx(ls,l,mid,ql,qr),qmx(rs,mid+1,r,ql,qr));
}
int qmn(int rt,int l,int r,int ql,int qr){
	if(ql>r||qr<l) return INF;
	if(ql<=l&&qr>=r) return mn[rt];
	down(rt);
	return min(qmn(ls,l,mid,ql,qr),qmn(rs,mid+1,r,ql,qr));
}
int a[MAXN],n;
vect<int> p[MAXN],fl,fr,gl,gr;
int ans=1;
pair<pii,int> op[MAXN<<1],po[MAXN<<1];
int tot;
void cdq(int l,int r){
	if(l==r)return;
	cdq(l,mid),cdq(mid+1,r);
	int tmp=0;
	for(int i=l,j=l,k=mid+1;i<=r;i++){
		if(j<=mid&&(k>r||op[j].fi.se<=op[k].fi.se)){
			po[i]=op[j];if(op[j].se<n) tmp=max(tmp,op[j].se);++j;
		}
		else{
			po[i]=op[k];if(op[k].se>=n) ans=max(ans,tmp-(op[k].se-n)+1);++k;
		}
	}
	for(int i=l;i<=r;i++) op[i]=po[i];
}
int sequence(int N, std::vector<int> A){
	n=N;for(int i=0;i<n;i++) a[i+1]=A[i];
	for(int i=1;i<=n;i++) p[a[i]]+=i;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		if(!p[i].size()) continue;
		for(int u:p[i]){
			upd(1,1,n,u,n,-1);
		}
		fl.resize(p[i].size());gl.resize(p[i].size());
		fr.resize(p[i].size());gr.resize(p[i].size());
		for(int j=0;j<p[i].size();j++){
			fl[j]=min(qmn(1,1,n,1,p[i][j]-1),0);
			gl[j]=qmn(1,1,n,p[i][j],n);
			fr[j]=max(qmx(1,1,n,1,p[i][j]-1),0);
			gr[j]=qmx(1,1,n,p[i][j],n);
		}
		tot=0;
		for(int j=0;j<p[i].size();j++){
			op[++tot]=make_pair(make_pair(-gr[j]-j,gr[j]-j),j);
			op[++tot]=make_pair(make_pair(1-fl[j]-j,fl[j]-j+1),j+n);
		}
		sort(op+1,op+tot+1);cdq(1,tot);
		tot=0;
		for(int j=0;j<p[i].size();j++){
			op[++tot]=make_pair(make_pair(-gl[j]-j,gl[j]-j),j);
			op[++tot]=make_pair(make_pair(1-fr[j]-j,fr[j]-j+1),j+n);
		}
		sort(op+1,op+tot+1);cdq(1,tot);
		tot=0;
		for(int j=0;j<p[i].size();j++){
			op[++tot]=make_pair(make_pair(gl[j]+j,j-gr[j]),j);
			op[++tot]=make_pair(make_pair(fr[j]+j-1,j-fl[j]-1),j+n);
		}
		sort(op+1,op+tot+1);cdq(1,tot);
		for(int u:p[i]) upd(1,1,n,u,n,-1);
	}
	return ans;
}
```

---

## 作者：Leasier (赞：2)

~~APIO 时对着这道题发了 1.5h 的呆 /youl~~

------------

考虑枚举所求区间中位数为 $x$。

- **找出中位数的条件。**

设区间内 $< x$ 的元素有 $p$ 个，$= x$ 的元素有 $q$ 个，$> x$ 的元素有 $r$ 个，则可以发现：

- $q + p \geq r$。
- $q + r \geq p$。

于是一个暴力的想法是：

- 考虑从小到大枚举 $x$。
- 设 $f_i$ 表示现在 $[1, i]$ 对应的 $q + p - r$，$g_i$ 表示现在 $[1, i]$ 对应的 $q + r - p$，$h_i$ 表示现在 $[1, i]$ 对应的 $q$。
- 则区间 $[l, r]$ 合法当且仅当 $f_r \geq f_{l - 1}, g_r \geq g_{l - 1}$，我们需要求满足该条件的 $h_r - h_{l - 1}$ 的最大值。
- 看上去是一个三维偏序，但注意到我们不必限制 $l \leq r$，于是问题降至二维。
- 排序后树状数组即可。时间复杂度为 $O(n^2 \log n)$。

但注意到我们事实上不必枚举每个 $r$：

- 设第 $i$ 个 $x$ 出现在 $pos_{x, i}$，则 $[pos_{x, i}, pos_{x, i + 1})$ 中的 $h$ 值相等。
- 于是一个简单的想法是把这样的段压起来，若让其作为 $l - 1$ 所在段则分别取 $f, g$ 的最小值，若让其作为 $r$ 所在段则分别取 $f, g$ 的最大值。
- 但仔细想想会发现问题：最值不一定会在同一处取到。
- 我们不妨把 $f_i, g_i$ 放到一个坐标轴上考虑。由于限制与两者均紧密相关，我们尝试把两者都放进**同一二维坐标系**。
- 具体地，我们发现当 $a_i = x$，$(f_i, g_i)$ 就是在 $(f_{i - 1}, g_{i - 1})$ 的基础上向右上走一步；$a_i < x$ 就是向右下走一步；$a_i > x$ 就是向左上走一步。
- 把图画出来会发现**每遇到一个 $x$ 就会向右上走一步，然后会在一条 $x + y = 2q$ 的直线上来回移动，再遇到一个 $x$ 时重复该形状**。
- 若我们要在某两条直线上选择两个点使得其中一个在另一个左下方，设两者所属直线给出的 $x$ 坐标限制为 $[l_1, r_1], [l_2, r_2]$、$y$ 坐标限制为 $[L_1, R_1], [L_2, R_2]$，则一对合法的 $(x_1, y_1), (x_2, y_2)$ 要满足 $l_1 \leq x_1 \leq x_2 \leq r_2$，$L_1 \leq y_1 \leq y_2 \leq R_2$。
- 于是一个**必要**条件是 $l_1 \leq r_2, L_1 \leq R_2$——也就是我们一开始的想法。
- 画图讨论可以发现满足该条件但不满足原条件只可能是第一条直线在第二条方程右上方，于是可以直接忽略。

线段树维护 $f, g$，对每个 $x$ 二维数点求解即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <algorithm>
#include <vector>

using namespace std;

namespace SegmentTree {
	typedef struct {
		int l;
		int r;
		int add1;
		int add2;
		int min1;
		int max1;
		int min2;
		int max2;
	} Node;
	
	Node tree[2000007];
	
	inline void update(int x){
		int ls = x * 2, rs = x * 2 + 1;
		tree[x].min1 = min(tree[ls].min1, tree[rs].min1);
		tree[x].max1 = max(tree[ls].max1, tree[rs].max1);
		tree[x].min2 = min(tree[ls].min2, tree[rs].min2);
		tree[x].max2 = max(tree[ls].max2, tree[rs].max2);
	}
	
	void build(int x, int l, int r){
		tree[x].l = l;
		tree[x].r = r;
		if (l == r){
			tree[x].min1 = tree[x].max1 = -l;
			tree[x].min2 = tree[x].max2 = l;
			return;
		}
		int mid = (l + r) >> 1;
		build(x * 2, l, mid);
		build(x * 2 + 1, mid + 1, r);
		update(x);
	}
	
	inline void pushdown(int x){
		int ls = x * 2, rs = x * 2 + 1;
		if (tree[x].add1 != 0){
			tree[ls].add1 += tree[x].add1;
			tree[rs].add1 += tree[x].add1;
			tree[ls].min1 += tree[x].add1;
			tree[rs].min1 += tree[x].add1;
			tree[ls].max1 += tree[x].add1;
			tree[rs].max1 += tree[x].add1;
			tree[x].add1 = 0;
		}
		if (tree[x].add2 != 0){
			tree[ls].add2 += tree[x].add2;
			tree[rs].add2 += tree[x].add2;
			tree[ls].min2 += tree[x].add2;
			tree[rs].min2 += tree[x].add2;
			tree[ls].max2 += tree[x].add2;
			tree[rs].max2 += tree[x].add2;
			tree[x].add2 = 0;
		}
	}
	
	void add1(int x, int l, int r, int k){
		if (l <= tree[x].l && tree[x].r <= r){
			tree[x].add1 += k;
			tree[x].min1 += k;
			tree[x].max1 += k;
			return;
		}
		int mid = (tree[x].l + tree[x].r) >> 1;
		pushdown(x);
		if (l <= mid) add1(x * 2, l, r, k);
		if (r > mid) add1(x * 2 + 1, l, r, k);
		update(x);
	}
	
	void add2(int x, int l, int r, int k){
		if (l <= tree[x].l && tree[x].r <= r){
			tree[x].add2 += k;
			tree[x].min2 += k;
			tree[x].max2 += k;
			return;
		}
		int mid = (tree[x].l + tree[x].r) >> 1;
		pushdown(x);
		if (l <= mid) add2(x * 2, l, r, k);
		if (r > mid) add2(x * 2 + 1, l, r, k);
		update(x);
	}
	
	int get_min1(int x, int l, int r){
		if (l <= tree[x].l && tree[x].r <= r) return tree[x].min1;
		int mid = (tree[x].l + tree[x].r) >> 1, ans = 0x7fffffff;
		pushdown(x);
		if (l <= mid) ans = get_min1(x * 2, l, r);
		if (r > mid) ans = min(ans, get_min1(x * 2 + 1, l, r));
		return ans;
	}
	
	int get_min2(int x, int l, int r){
		if (l <= tree[x].l && tree[x].r <= r) return tree[x].min2;
		int mid = (tree[x].l + tree[x].r) >> 1, ans = 0x7fffffff;
		pushdown(x);
		if (l <= mid) ans = get_min2(x * 2, l, r);
		if (r > mid) ans = min(ans, get_min2(x * 2 + 1, l, r));
		return ans;
	}
	
	int get_max1(int x, int l, int r){
		if (l <= tree[x].l && tree[x].r <= r) return tree[x].max1;
		int mid = (tree[x].l + tree[x].r) >> 1, ans = 0x80000000;
		pushdown(x);
		if (l <= mid) ans = get_max1(x * 2, l, r);
		if (r > mid) ans = max(ans, get_max1(x * 2 + 1, l, r));
		return ans;
	}
	
	int get_max2(int x, int l, int r){
		if (l <= tree[x].l && tree[x].r <= r) return tree[x].max2;
		int mid = (tree[x].l + tree[x].r) >> 1, ans = 0x80000000;
		pushdown(x);
		if (l <= mid) ans = get_max2(x * 2, l, r);
		if (r > mid) ans = max(ans, get_max2(x * 2 + 1, l, r));
		return ans;
	}
}

namespace BIT {
	int tm = 0;
	int vis[2000007], tree[2000007];
	
	inline int lowbit(int x){
		return x & (-x);
	}
	
	inline void update(int n, int x, int k){
		while (x <= n){
			if (vis[x] != tm){
				vis[x] = tm;
				tree[x] = 0x7fffffff;
			}
			tree[x] = min(tree[x], k);
			x += lowbit(x);
		}
	}
	
	inline int get_min(int x){
		int ans = 0x7ffffff;
		while (x > 0){
			if (vis[x] != tm){
				vis[x] = tm;
				tree[x] = 0x7fffffff;
			}
			ans = min(ans, tree[x]);
			x -= lowbit(x);
		}
		return ans;
	}
}

typedef struct Item_tag {
	int type;
	int x;
	int y;
	int z;
	Item_tag(){}
	Item_tag(int type_, int x_, int y_, int z_){
		type = type_;
		x = x_;
		y = y_;
		z = z_;
	}
} Item;

Item a[1000007];
vector<int> v[500007];

bool operator <(const Item a, const Item b){
	if (a.x != b.x) return a.x < b.x;
	if (a.y != b.y) return a.y < b.y;
	return a.type < b.type;
}

int sequence(int N, vector<int> A){
	int ni = N + 1, m = N * 2, k = m * 2, ans = 0;
	A.insert(A.begin(), 0);
	for (register int i = 1; i <= N; i++){
		v[i].push_back(0);
	}
	for (register int i = 1; i <= N; i++){
		v[A[i]].push_back(i);
	}
	for (register int i = 1; i <= N; i++){
		v[i].push_back(ni);
	}
	SegmentTree::build(1, 0, N);
	for (register int i = 1; i <= N; i++){
		int size = v[i].size() - 1, cnt = 0;
		for (register int j = 0; j < size; j++){
			if (j > 0) SegmentTree::add1(1, v[i][j], N, 2);
			a[++cnt] = Item(1, SegmentTree::get_min1(1, v[i][j], v[i][j + 1] - 1), SegmentTree::get_min2(1, v[i][j], v[i][j + 1] - 1), j);
			a[++cnt] = Item(2, SegmentTree::get_max1(1, v[i][j], v[i][j + 1] - 1), SegmentTree::get_max2(1, v[i][j], v[i][j + 1] - 1), j);
		}
		sort(a + 1, a + cnt + 1);
		BIT::tm++;
		for (register int j = 1; j <= cnt; j++){
			if (a[j].type == 1){
				BIT::update(k, a[j].y + m, a[j].z);
			} else {
				ans = max(ans, a[j].z - BIT::get_min(a[j].y + m));
			}
		}
		for (register int j = 1; j < size; j++){
			SegmentTree::add2(1, v[i][j], N, -2);
		}
	}
	return ans;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P9371)

**题目大意**

> 给定 $a_1\sim a_n$，求一个区间 $[l,r]$ 最大化其中位数的出现次数（长度为偶数可以在中间两个元素中任选一个）。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

考虑刻画中位数 $x$，要求 $\ge x$ 的元素比 $<x$ 的元素多，$\le x$ 的元素比 $>x$ 的元素多。

那么设 $X_i$ 表示 $2[a_i\ge x]-1$ 的前缀和，$Y_i$ 表示 $2[a_i\le x]-1$ 的前缀和。

那么一个区间 $[l,r]$ 中位数为 $x$ 就要求 $Y_r\ge Y_{l-1},X_r\ge X_{l-1}$，这是一个二维偏序问题。

然后考虑对于每个 $x$ 都解决此问题。

把所有 $(X_i,Y_i)$ 连成线，遇到 $a_i=x$ 会往右上移动，$a_i<x$ 往左上移动，$a_i>x$ 往右上移动。

观察构成折线的结构，发现是若干连续的斜率为 $-1$ 的线段，两条线段中间夹的一段就是一个 $a_i=x$ 的点。

那么我们就是要求出距离最远的两条线段，使得在右边的线段上可以选出一个点包含左边线段上至少一个点。

设右侧线段 $x,y$ 的最大值为 $R_x,R_y$，左边线段 $x,y$ 的最小值为 $L_x,L_y$，那么我们可以证明这两条线段合法当且仅当 $R_x\ge L_x,R_y\ge L_y$。

那么这又变成了一个二维偏序问题，按 $x$ 扫描树状数组维护前缀最大值即可。

由于线段树和当前 $x$ 的出现次数成线性，因此二维数点的总点数是 $\mathcal O(n)$ 的。

预处理每条线段的 $L_x,L_y,R_x,R_y$ 可以直接线段树维护区间最大最小前缀和。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5,inf=1e9,MAXV=2e6+5,V=1e6;
typedef array<int,2> pii;
pii operator +(pii x,pii y) { return {min(x[0],y[0]),max(x[1],y[1])}; }
int n,a[MAXN];
struct SegmentTree {
	pii tr[MAXN<<2]; int tg[MAXN<<2];
	void adt(int p,int k) { tr[p][0]+=k,tr[p][1]+=k,tg[p]+=k; }
	void psd(int p) { if(tg[p]) adt(p<<1,tg[p]),adt(p<<1|1,tg[p]),tg[p]=0; }
	void psu(int p) { tr[p]=tr[p<<1]+tr[p<<1|1]; }
	void add(int ul,int ur,int k,int l=0,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return adt(p,k);
		int mid=(l+r)>>1; psd(p);
		if(ul<=mid) add(ul,ur,k,l,mid,p<<1);
		if(mid<ur) add(ul,ur,k,mid+1,r,p<<1|1);
		psu(p);
	}
	pii qry(int ul,int ur,int l=0,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return tr[p];
		int mid=(l+r)>>1; psd(p);
		if(ur<=mid) return qry(ul,ur,l,mid,p<<1);
		if(mid<ul) return qry(ul,ur,mid+1,r,p<<1|1);
		return qry(ul,ur,l,mid,p<<1)+qry(ul,ur,mid+1,r,p<<1|1);
	}
}	X,Y; //X: >=k?1:-1, Y: <=k?1:-1
vector <int> ps[MAXN];
struct FenwickTree {
	int tr[MAXV]; vector <int> e;
	void build() { fill(tr,tr+MAXV,-inf); }
	void upd(int x,int w) { for(e.push_back(x);x<MAXV;x+=x&-x) tr[x]=max(tr[x],w); }
	int qry(int x) { int s=-inf; for(;x;x&=x-1) s=max(s,tr[x]); return s; }
	void init() { for(int x:e) for(;x<MAXV;x+=x&-x) tr[x]=-inf; e.clear(); }
}	T;
int sequence(int N,vector<int>A) {
	n=N,T.build();
	for(int i=1;i<=n;++i) {
		ps[a[i]=A[i-1]].push_back(i);
		X.add(i,n,1),Y.add(i,n,-1);
	}
	int ans=0;
	for(int o=1;o<=n;++o) if(ps[o].size()) {
		vector <int> p{0};
		for(int z:ps[o]) p.push_back(z),Y.add(z,n,2);
		p.push_back(n+1);
		vector <array<int,3>> Q;
		for(int i=1;i<(int)p.size();++i) {
			pii x=X.qry(p[i-1],p[i]-1),y=Y.qry(p[i-1],p[i]-1);
			Q.push_back({x[0],y[0],-i});
			Q.push_back({x[1],y[1],i});
		}
		sort(Q.begin(),Q.end()),T.init();
		for(int i=0,j;i<(int)Q.size();i=j) {
			for(j=i;j<(int)Q.size()&&Q[i][0]==Q[j][0];++j) {
				if(Q[j][2]<0) T.upd(Q[j][1]+V,Q[j][2]);
				else ans=max(ans,Q[j][2]+T.qry(Q[j][1]+V));
			}
		}
		for(int z:ps[o]) X.add(z,n,-2);
	}
	return ans;
}
```

---

## 作者：Mirasycle (赞：1)

## 二维偏序

首先枚举中位数然后根据相对大小 $-1$ $0$ $1$ 的转化。设此时前缀和为 $s_i$，枚举数的个数是 $c_i$。那么对于枚举 $l$，显然就是要找到满足要求的最大 $c_r$。有 $\lvert s_r-s_{l-1}\rvert \le c_r-c_{l-1}$。拆开绝对值号转化一下就是 $(c_l+s_l,c_l-s_l)$ 右上方的点，那么直接偏序即可。

注意细节这里不需要使用二维数据结构或三维偏序，因为要求的是最大的 $c_r-c_{l-1}$，且 ${c_i}$ 单增，所以第一维不需要考虑大小关系。直接对于第二维排序，然后第三维树状数组即可。这样子的话时间复杂度是 $O(n^2\log n)$ 的。

## 根号分治

对于出现次数大于 $B$ 的数直接执行上述二维偏序。时间复杂度 $O(\dfrac{n}{B}n\log n)$。

对于出现次数小于 $B$ 的数，我们发现中位数出现位置端点组数是 $O(\frac{n}{B}\times B \times B)$ 级别的那么直接枚举左右端点 $pos_L$ 和 $pos_R$ 即可。

此时固定左右端点后的 $c$ 是定值，我们此时不要带入二维数点的式子，而是应该带入原始式子。这样发现由于要求的 $\max c$ 固定，所以我们只需要判断最小的 $\lvert s_r-s_{l-1} \rvert$ 是否小于 $c$，其中 $l \in (pos_{L-1},pos_L-1)$，$r\in(pos_R+1,pos_{R+1})$，这种绝对值的两边配对最小值其实很难维护，因为这是要寻找两边最接近的数。

用到性质这里的 $s$ 每次变化量最多为 $1$，因此是连续变化的。我们可以用线段树维护 $s$，只需要分别找两边区间最大最小值，就可以求出两个区间的值域范围。然后找到最接近的两个数即可。

其中至于 $s$ 和 $c$ 的动态维护，我们不需要每次遍历序列处理，只需要从小到大地枚举待处理中位数，每个数的 $s$ 和 $c$ 只会被修改 $O(1)$ 次。用线段树维护就行了。这一部分的时间复杂度为 $O(nB\log n)$。

总的时间复杂度为 $O(\dfrac{n^2}{B}\log n+nB\log n)$，取 $B=\sqrt n$，可以得到时间复杂度 $O(n\sqrt n\log n)$。

## 正解

### 解法一
顺着根号分治的第一种情况思考，我们发现其实无用状态太多了。明明一个数能产生实际贡献的位置很少，但是我们对于每种数还需要遍历整个序列十分浪费。每个位置实际产生的贡献又有一些微妙的变化，不能直接忽视。不过变化连续都是 $+1 -1$ 这样的变化。对于这种情况，我们考虑将上述的 $(c_i+s_i,c_i-s_i)$ 画在坐标系中，因为图象可以反应不同点之间的规律，合并相同信息。

设当前枚举的中位数为 $x$，发现如果 $a_i<x$，那么会往左上走，$a_i=x$，会往右上走，如果 $a_i=x$，会往右下走。两条直线贡献即为截距之差，思考两条直线何时可以产生贡献，只要截距大的那条直线存在一点在截距小的那条直接右上方就行了。

只需要直线的最大横坐标和最大纵坐标分别大于另一条直线的最小横坐标和最小纵坐标即可，转化一下就是二维数点。我们发现直线个数取决于 $c$ 的变化次数，$c$ 每次变化相当于出现一次枚举的中位数，那么对于每个中位数枚举每条直线复杂度均摊线性。

时间复杂度 $O(n\log n)$。

### 解法二：

顺着根号分治的第二情况思考，固定区间左右端点后 $c$ 为定值，为了最大化 $c$，我们要尽可能扩大区间。这是一个最大化区间的过程，于是我们考虑能不能用双指针维护，发现真的有单调性。

这里的单调性并不显然，因为最后我们选取的产生中位数的区间和枚举的左右端点并不完全一样。但是更小的区间意味向外扩展着更多的选择，如果包含它的大区间满足，那么小区间必然可以通过向外扩展满足条件。

双指针配合线段树即可求解，时间复杂度为 $O(n\log n)$。

---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/P9371)

## Solution

首先考虑一个序列的中位数满足什么条件。

设中位数 $a$ 的个数是 $x$，小于中位数的个数是 $y$，大于中位数的个数是 $z$。

那么满足下面两个条件：$x+y\geq z,x+z\geq y$。

转化一下就是：$-x\leq z-y\leq x$。

考虑给区间里小于 $a$ 的数赋一个权值 $-1$，大于 $a$ 的赋 $1$，等于 $a$ 为 $0$。设 $sum_k$ 为权值的前缀和，$cnt_k$ 为这个前缀的 $a$ 的个数。

就是求满足 $cnt_{l-1}-cnt_r\leq sum_r-sum_{l-1}\leq cnt_r-cnt_{l-1}$ 的区间 $[l,r]$ 中最大的 $cnt_r-cnt_{l-1}$。

---

考虑从小到大枚举 $a$，容易发现 $cnt$ 和 $sum$ 都可以用线段树维护，这里不再赘述。

把上面那个式子转化一下得：$sum_{l-1}+cnt_{l-1}\leq sum_r+cnt_r$ 且 $cnt_{l-1}-sum_{l-1}\leq cnt_r-sum_r$。

容易发现这是一个二维偏序的结构，所以把 $(sum_{x}+cnt_{x},cnt_{x}-sum_x)$ 看成一个点，就只要求一个二维偏序了。

暴力是 $O(n^2\log n)$。

---

考虑优化。

观察一下这些点的走势会发现 $A_x=a$ 时会向右上走，$A_x<a$ 向左上，$A_x>a$ 向右下。

于是可以画出样例 2 中 $a=1$ 的图像：

[![pCVv5Af.png](https://s1.ax1x.com/2023/06/11/pCVv5Af.png)](https://imgse.com/i/pCVv5Af)

会发现 $cnt$ 相同的点在同一条 $y=-x+2\times cnt$ 的直线上，问题就转化为：给定若干条斜率为 $-1$ 的线段，求出所有线段 $l_1,l_2$，满足 $l_1$ 上存在点在 $l_2$ 的任一点的右上方的最大的 $l_1$ 与 $l_2$ 的距离。 

假设给定 $l_2$，那么 $l_1$ 就要满足与下面的阴影有交点：

[![pCVxkuR.png](https://s1.ax1x.com/2023/06/11/pCVxkuR.png)](https://imgse.com/i/pCVxkuR)

写成式子就是：$maxx_1\geq minx_2,maxy_1\geq miny_2,cnt_1\geq cnt_2$。容易发现这个式子是充分必要的。

所以只要把每条斜率为 $-1$ 的线段的 $(minx,miny)$ 和 $(maxx,maxy)$ 求出来，跑二维偏序即可。

（树状数组维护 $cnt$ 的最小值，这里不用考虑 $cnt_1\geq cnt_2$ 的条件，因为 $cnt_1 < cnt_2$ 时一定不是最优解。）

均摊下来就是 $O(n\log n)$。

## Code

```cpp
#include "sequence.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// #define int long long

using pii = std::pair<int, int>;

const int kMaxN = 5e5 + 5;

struct Node {
  int mxx, mxy, mix, miy;

  Node() {}
  Node(int _mxx, int _mxy, int _mix, int _miy) : mxx(_mxx), mxy(_mxy), mix(_mix), miy(_miy) {}
};

struct LYX {
  pii p;
  int op, id;

  LYX() {}
  LYX(pii _p, int _op, int _id) : p(_p), op(_op), id(_id) {}
};

int n;
int a[kMaxN], mxx[kMaxN << 2], mxy[kMaxN << 2], mix[kMaxN << 2], miy[kMaxN << 2], tagx[kMaxN << 2], tagy[kMaxN << 2];
int tr[kMaxN << 2];
std::vector<int> pos[kMaxN];
LYX pp[kMaxN << 1];

bool cmp(const LYX &l1, const LYX &l2) {
  return l1.p.first < l2.p.first;
}

Node merge(Node ls, Node rs) {
  return Node(std::max(ls.mxx, rs.mxx), std::max(ls.mxy, rs.mxy), std::min(ls.mix, rs.mix), std::min(ls.miy, rs.miy));
}

void pushup(int x) {
  mxx[x] = std::max(mxx[x << 1], mxx[x << 1 | 1]);
  mix[x] = std::min(mix[x << 1], mix[x << 1 | 1]);
  mxy[x] = std::max(mxy[x << 1], mxy[x << 1 | 1]);
  miy[x] = std::min(miy[x << 1], miy[x << 1 | 1]);
}

void addtagx(int x, int v) {
  mxx[x] += v, mix[x] += v, tagx[x] += v;
}

void addtagy(int x, int v) {
  mxy[x] += v, miy[x] += v, tagy[x] += v;
}

void pushdown(int x) {
  if (!tagx[x] && !tagy[x]) return;
  if (tagx[x]) addtagx(x << 1, tagx[x]), addtagx(x << 1 | 1, tagx[x]);
  if (tagy[x]) addtagy(x << 1, tagy[x]), addtagy(x << 1 | 1, tagy[x]);
  tagx[x] = tagy[x] = 0;
}

void update(int x, int l, int r, int ql, int qr, int vx, int vy) {
  if (l > qr || r < ql) {
    return;
  } else if (l >= ql && r <= qr) {
    return addtagx(x, vx), addtagy(x, vy);
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  update(x << 1, l, mid, ql, qr, vx, vy), update(x << 1 | 1, mid + 1, r, ql, qr, vx, vy);
  pushup(x);
}

Node query(int x, int l, int r, int ql, int qr) {
  if (l > qr || r < ql) {
    return Node(-1e9, -1e9, 1e9, 1e9);
  } else if (l >= ql && r <= qr) {
    return Node(mxx[x], mxy[x], mix[x], miy[x]);
  }
  pushdown(x);
  int mid = (l + r) >> 1;
  Node ls = query(x << 1, l, mid, ql, qr), rs = query(x << 1 | 1, mid + 1, r, ql, qr);
  return merge(ls, rs);
}

void upd(int x, int v) {
  for (; x <= 2e6; x += x & -x)
    tr[x] = std::min(tr[x], v);
}

int qry(int x) {
  int ret = 1e9;
  for (; x; x -= x & -x)
    ret = std::min(ret, tr[x]);
  return ret;
}

void clr(int x) {
  for (; x <= 2e6; x += x & -x)
    tr[x] = 1e9;
}

int solve(int val = 1) {
  for (int i = 1; i <= n; ++i)
    update(1, 0, n, i, n, 1, -1);
  int ret = 0;
  memset(tr, 0x3f, sizeof(tr));
  for (int i = 1; i <= n; ++i) {
    for (auto x : pos[i])
      if (x && x <= n) update(1, 0, n, x, n, 0, 2);
    int cnt = 0;
    for (int j = 0; j + 1 < static_cast<int>(pos[i].size()); ++j) {
      auto p = query(1, 0, n, pos[i][j], pos[i][j + 1] - 1);
      pp[++cnt] = LYX(std::make_pair(p.mix, p.miy), 0, j);
      pp[++cnt] = LYX(std::make_pair(p.mxx, p.mxy), 1, j);
    }
    std::sort(pp + 1, pp + 1 + cnt, cmp);
    int now = 0;
    for (int j = 1, k; j <= cnt; j = k) {
      now = j;
      for (k = j; k <= cnt && pp[k].p.first == pp[j].p.first; ++k)
        if (pp[k].op == 0)
          upd(pp[k].p.second + 1e6, pp[k].id);
      for (int s = j; s < k; ++s)
        if (pp[s].op == 1)
          ret = std::max(ret, pp[s].id - qry(pp[s].p.second + 1e6));
    }
    for (int k = 1; k < now; ++k)
      clr(pp[k].p.second + 1e6);
    for (auto x : pos[i])
      if (x && x <= n) update(1, 0, n, x, n, -2, 0);
  }
  return ret;
}

int sequence(int N, std::vector<int> A) {
  n = N;
  for (int i = 0; i < n; ++i)
    a[i + 1] = A[i];
  for (int i = 1; i <= n; ++i)
    pos[i].emplace_back(0);
  for (int i = 1; i <= n; ++i)
    pos[a[i]].emplace_back(i);
  for (int i = 1; i <= n; ++i)
    pos[i].emplace_back(n + 1);
  return solve();
}
```



---

## 作者：Emptilife (赞：0)

好题，与 [[国家集训队] Middle](https://www.luogu.com.cn/problem/P2839) 有异曲同工之妙。

思路来自 I_am_Accepted。

对于 $x$，设 $h,l,c$ 分别是 $>x,<x,=x$ 的个数，则 $x$ 成为中位数当且仅当 $|h-l|\le c$，**拆解绝对值**：

$$
\left\{\begin{matrix}
h-l-c\le 0&(1) \\
h-l+c\ge 0&(2)
\end{matrix}\right.
$$

枚举中位数 $x$，设 

$$
\left\{\begin{matrix}
H_i=1&A_i>x \\
H_i=0&A_i\le x
\end{matrix}\right.
$$
$$
\left\{\begin{matrix}
L_i=1&A_i\ge x \\
L_i=0&A_i< x
\end{matrix}\right.
$$

$L,H$ 的变化是 $O(n)$ 的。

预处理 $p_x=\{i\mid A_i=x\}$，考虑何时存在另一个区间以 $x$ 为中位数且包含 $p_{l\sim r}$。

令 $s$ 等于 $a_i\ne x$ 的 $H_{l\sim r}$ 的区间和，若 $s\le 0$，求出 $L$ 以 $l$ 为右端点的最大后缀和 $L$ 和以 $r$ 为左端点的最大前缀和 $R$，若 $L+R+r-l+1\ge 0$ 则存在。因为一定有一个时刻 $L+R+r-l+1= 0$，此时条件 $(1)(2)$ 均满足。$s\ge 0$ 类似。

双指针配合线段树即可解决。


---

