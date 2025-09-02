# Addition Robot

## 题目描述

Adding two numbers several times is a time-consuming task, so you want to build a robot. The robot should have a string $ S = S_1 S_2 \dots S_N $ of $ N $ characters on its memory that represents addition instructions. Each character of the string, $ S_i $ , is either 'A' or 'B'.

You want to be able to give $ Q $ commands to the robot, each command is either of the following types:

- 1 $ L $ $ R $ . The robot should toggle all the characters of $ S_i $ where $ L \le i \le R $ . Toggling a character means changing it to 'A' if it was previously 'B', or changing it to 'B' if it was previously 'A'.
- 2 $ L $ $ R $ $ A $ $ B $ . The robot should call $ f(L, R, A, B) $ and return two integers as defined in the following pseudocode: ```
  <pre class="lstlisting">```
      function f(L, R, A, B):<br></br>      FOR i from L to R<br></br>        if S[i] = 'A'<br></br>          A = A + B<br></br>        else<br></br>          B = A + B<br></br>      return (A, B)<br></br>
  ```
  ```

You want to implement the robot's expected behavior.

## 说明/提示

Explanation for the sample input/output #1

For the first command, calling $ f(L, R, A, B) $ causes the following:

- Initially, $ A = 1 $ and $ B = 1 $ .
- At the end of $ i = 1 $ , $ A = 2 $ and $ B = 1 $ .
- At the end of $ i = 2 $ , $ A = 2 $ and $ B = 3 $ .
- At the end of $ i = 3 $ , $ A = 5 $ and $ B = 3 $ .
- At the end of $ i = 4 $ , $ A = 8 $ and $ B = 3 $ .
- At the end of $ i = 5 $ , $ A = 11 $ and $ B = 3 $ .

 Therefore, $ f(L, R, A, B) $ will return $ (11, 3) $ .For the second command, string $ S $ will be updated to "ABBBB".

For the third command, the value of $ A $ will always be $ 0 $ and the value of $ B $ will always be $ 1\,000\,000\,000 $ . Therefore, $ f(L, R, A, B) $ will return $ (0, 1\,000\,000\,000) $ .

## 样例 #1

### 输入

```
5 3
ABAAA
2 1 5 1 1
1 3 5
2 2 5 0 1000000000
```

### 输出

```
11 3
0 1000000000
```

# 题解

## 作者：TSTYFST (赞：6)

### [题目链接](https://www.luogu.com.cn/problem/CF1252K)

### 思路

对于 $A = A + B$，$B = A + B$ 这种的递推式可以考虑矩阵加速递推，可得：

$$
\left (
\begin{matrix}
A + B & B
\end{matrix}
\right ) =
\left (
\begin{matrix}
A & B
\end{matrix}
\right ) 
\left (
\begin{matrix}
1 & 0 \\
1 & 1
\end{matrix}
\right )
$$
$$
\left (
\begin{matrix}
A & A + B
\end{matrix}
\right ) =
\left (
\begin{matrix}
A & B
\end{matrix}
\right ) 
\left (
\begin{matrix}
1 & 1 \\
0 & 1
\end{matrix}
\right ) 
$$

把 $A,B$ 二元组看作单位向量 $\left ( \begin{matrix} A & B \end{matrix} \right )$，设 $S_i$ 对应的转移矩阵为 $G_i$，则一次 ```F``` 函数操作得到的 $A,B$ 二元组对应的向量就是：

$$
\left ( \begin{matrix} A & B \end{matrix} \right )
\prod_{i = l}^{r} G_i
$$

由于矩阵乘法满足结合律，对于一段区间的矩阵的乘积，我们可以用线段树维护。

考虑区间取反操作怎么实现，我们通过~~打表~~观察上方给出的两个转移矩阵，发现它们都是对方旋转了 $180^{\circ}$。感性理解一下，设有矩阵 $A,B,C$，有：

$$
A =
\left (
\begin{matrix}
a_1 & b_1 \\
c_1 & d_1
\end{matrix}
\right )
$$
$$
B = 
\left (
\begin{matrix}
a_2 & b_2 \\
c_2 & d_2
\end{matrix}
\right )
$$
$$
C = A \times B =
\left (
\begin{matrix}
a_1a_2 + b_1c_2 & a_1b_2 + b_1d_2 \\
c_1a_2 + d_1c_2 & c_1b_2 + d_1d_2
\end{matrix}
\right )
$$

设 $A'$，$B'$ 为 $A$，$B$ 各旋转 $180^{\circ}$ 后的矩阵，有:

$$
A' = 
\left (
\begin{matrix}
d_1 & c_1 \\
b_1 & a_1
\end{matrix}
\right )
$$
$$
B' = 
\left (
\begin{matrix}
d_2 & c_2 \\
b_2 & a_2
\end{matrix}
\right )
$$
$$
C' = A' \times B' =
\left (
\begin{matrix}
d_1d_2 + c_1b_2 & d_1c_2 + c_1a_2 \\
b_1d_2 + a_1b_2 & b_1c_2 + a_1a_2
\end{matrix}
\right )
$$

可以发现 $C'$ 也是 $C$ 旋转 $180^{\circ}$ 后的结果，所以推广这个结论到 $A,B$ 的反转操作上，就是直接交换矩阵对角线上的元素。就像维护01序列的翻转那样维护线段树就行了。时间复杂度 $\Theta (2 ^ 3 n \log n)$ 。

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

#define LL long long

using namespace std;

const int Mod = 1e9 + 7;
const int MAXN = 1e5 + 10, SIZE = 3;
int n, q;
char s[MAXN];

struct Matrix{
    int hig, wid;
    LL num[SIZE][SIZE];

    Matrix(){
        hig = wid = 0;
        memset(num, 0, sizeof(num));
    }

    Matrix operator * (const Matrix &b) const{
        Matrix c;
        c.hig = hig, c.wid = b.wid;
        for(register int i = 1; i <= c.hig; i++){
            for(register int k = 1; k <= b.hig; k++){
                LL res = num[i][k];
                for(register int j = 1; j <= c.wid; j++)
                    c.num[i][j] = 1LL * (c.num[i][j] + res * b.num[k][j] % Mod) % Mod;
            }
        }

        return c;
    }

    void Reverse(){
        swap(num[1][1], num[2][2]);
        swap(num[1][2], num[2][1]);
    }
}base, G1, G2, I;

struct Segment_Tree{
    struct Tree{
        int l, r;
        Matrix sum;
        int lazy;
    }tr[MAXN << 2];

    inline int lson(int rt){
        return rt << 1;
    }

    inline int rson(int rt){
        return rt << 1 | 1;
    }

    inline void Pushup(int rt){
        tr[rt].sum = tr[lson(rt)].sum * tr[rson(rt)].sum;
    }

    void Build(int rt, int l, int r){
        tr[rt].l = l, tr[rt].r = r;
        if(l == r){
            if(s[l] == 'A') tr[rt].sum = G1;
            else tr[rt].sum = G2;
            return;
        }

        int mid = (l + r) >> 1;
        Build(lson(rt), l, mid);
        Build(rson(rt), mid + 1, r);

        Pushup(rt);
    }

    inline void Pushdwon(int rt){
        if(tr[rt].lazy){
            tr[lson(rt)].lazy ^= 1;
            tr[rson(rt)].lazy ^= 1;
            tr[lson(rt)].sum.Reverse();
            tr[rson(rt)].sum.Reverse();
            tr[rt].lazy = 0;
        }
    }

    void Update_Rev(int rt, int l, int r){
        if(tr[rt].l >= l && tr[rt].r <= r){
            tr[rt].sum.Reverse();
            tr[rt].lazy ^= 1;
            return;
        }

        Pushdwon(rt);

        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if(l <= mid) Update_Rev(lson(rt), l, r);
        if(r > mid) Update_Rev(rson(rt), l, r);

        Pushup(rt);
    }

    Matrix Query_Sum(int rt, int l, int r){
        if(tr[rt].l >= l && tr[rt].r <= r) return tr[rt].sum;

        Pushdwon(rt);

        Matrix ans = base;
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if(l <= mid) ans = ans * Query_Sum(lson(rt), l, r);
        if(r > mid) ans = ans * Query_Sum(rson(rt), l, r);

        return ans;
    }
}S;

void init(){
    base.hig = base.wid = 2;
    base.num[1][1] = base.num[2][2] = 1;
    G1.hig = G1.wid = 2;
    G1.num[1][1] = G1.num[2][1] = G1.num[2][2] = 1;
    G2.hig = G2.wid = 2;
    G2.num[1][1] = G2.num[1][2] = G2.num[2][2] = 1;
    I.hig = 1, I.wid = 2;
}

int main(){
    init();

    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);

    S.Build(1, 1, n);

    for(register int i = 1; i <= q; i++){
        int opt;
        scanf("%d", &opt);

        if(opt == 1){
            int l, r;
            scanf("%d%d", &l, &r);
            S.Update_Rev(1, l, r);
        }
        else{
            int l, r, a, b;
            scanf("%d%d%d%d", &l, &r, &a, &b);
            I.num[1][1] = a, I.num[1][2] = b;
            I = I * S.Query_Sum(1, l, r);
            printf("%lld %lld\n", I.num[1][1], I.num[1][2]);
        }
    }

    return 0;
}
```

马蜂冗长，不喜勿喷。

---

## 作者：CJ_Fu (赞：3)

## [CF1252K Addition Robot](https://codeforces.com/problemset/problem/1252/K)

\*2100

给一个 AB 串，定义函数 $f(l,r,x,y)$：
```cpp
function f(L, R, x, y):
	for i from L to R
		if S[i] = 'A'
        x = x + y
		else
        y = x + y
	return (x, y)
```
$Q$ 次操作：
- 对 $s[l,r]$ 取反；
- 求 $f(l,r,A,B)\bmod 10^9+7$。

$n,Q\le 10^5$

考虑把 A/B 自身看做一个对二元组 $(x,y)$ 的 transform，即 $A((x,y))=(1x+1y,0x+1y),B((x,y))=(1x+0y,1x+1y)$（方便书写后面省略最外层括号），我们要求的其实就是一系列变换的嵌套。由于嵌套后的结果仍关于 $x,y$ 呈线性，所以考虑用线段树维护。

设左半区间得到的嵌套函数 $F(x,y)=(ax+by,cx+dy)$，右半为 $G(x,y)=(ex+fy,gx+hy)$，则 $G(F(x,y))=(e(ax+by)+f(cx+dy),g(ax+by)+h(cx+dy))=((ae+cf)x+(be+df)y,(ag+ch)x+(bg+dh)y)$，由此即可直接合并左右区间了，注意有顺序。（其实形式和矩阵乘法差不多）

再考虑取反操作，其实就是相当于把区间内所有 $A,B$ 变换反转，由于线性性，直接反转区间变换后的系数（实现可以用 swap）并打上懒标记下传即可（实现可以用异或）。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+7;
const int mod=1e9+7;
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
char s[maxn];
int n,q;
struct seg{
    struct node{
        struct trans{
            int x,y;
            int q(int A,int B){return (x*A%mod+y*B%mod)%mod;}
        }a,b;
        node(){a.x=0;a.y=0;b.x=0;b.y=0;}
        node friend operator+(const node &a, const node &b){
            node c;
            c.a.x=(a.a.x*b.a.x%mod+a.b.x*b.a.y%mod)%mod;
            c.a.y=(a.a.y*b.a.x%mod+a.b.y*b.a.y%mod)%mod;
            c.b.x=(a.a.x*b.b.x%mod+a.b.x*b.b.y%mod)%mod;
            c.b.y=(a.a.y*b.b.x%mod+a.b.y*b.b.y%mod)%mod;
            return c;
        }
    }tr[maxn<<2];
    int tag[maxn<<2];
    void upd(node &x,node y){x=x+y;}
    void pushup(int now){tr[now]=tr[ls]+tr[rs];}
    void pushdown(int now,int l,int r){
        if(!tag[now]) return;
        tag[ls]^=tag[now];
        tag[rs]^=tag[now];
        swap(tr[ls].a,tr[ls].b);
        swap(tr[ls].a.x,tr[ls].a.y);
        swap(tr[ls].b.x,tr[ls].b.y);
        swap(tr[rs].a,tr[rs].b);
        swap(tr[rs].a.x,tr[rs].a.y);
        swap(tr[rs].b.x,tr[rs].b.y);
        tag[now]=0;
    }
    void build(int now,int l,int r){
        if(l==r){
            if(s[l]=='A') tr[now].a={1,1},tr[now].b={0,1};
            else tr[now].a={1,0},tr[now].b={1,1}; 
            return;
        }
        build(ls,l,mid); build(rs,mid+1,r);
        pushup(now);
    }
    void modify(int now,int l,int r,int L,int R){
        if(L<=l&&r<=R){
            tag[now]^=1;
            swap(tr[now].a,tr[now].b);
            swap(tr[now].a.x,tr[now].a.y);
            swap(tr[now].b.x,tr[now].b.y);
            return;
        }
        pushdown(now,l,r);
        if(L<=mid) modify(ls,l,mid,L,R);
        if(mid+1<=R) modify(rs,mid+1,r,L,R);
        pushup(now);
    }
    node query(int now,int l,int r,int L,int R){
        if(L<=l&&r<=R) return tr[now];
        pushdown(now,l,r);
        if(L<=mid&&mid+1<=R) return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
        if(L<=mid) return query(ls,l,mid,L,R);
        if(mid+1<=R) return query(rs,mid+1,r,L,R);
        return node();
    }
}t;
signed main(){
    cin>>n>>q;
    cin>>(s+1);
    t.build(1,1,n);
    for(int o=1,op,a,b,l,r;o<=q;o++){
        cin>>op;
        if(op&1){
            cin>>l>>r;
            t.modify(1,1,n,l,r);
        }else{
            cin>>l>>r>>a>>b;
            auto t1=t.query(1,1,n,l,r);
            cout<<t1.a.q(a,b)<<' '<<t1.b.q(a,b)<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：happybob (赞：1)

直接做是难的，发现这个东西似乎可以矩阵优化。

可以发现 $\begin{bmatrix} a+b&b \end{bmatrix} = \begin{bmatrix} a & b \end{bmatrix} \times \begin{bmatrix} 1 & 0 \\ 1 & 1\end{bmatrix}$，$\begin{bmatrix} a & a + b \end{bmatrix} = \begin{bmatrix} a&b \end{bmatrix} \times \begin{bmatrix} 1 & 1\\ 0 & 1\end{bmatrix}$。

对于 $S_i$ 为 $\texttt{A}$，那么令 $p_i = \begin{bmatrix} 1 & 0 \\ 1 & 1\end{bmatrix}$，否则 $p_i = \begin{bmatrix} 1 & 1\\ 0 & 1\end{bmatrix}$。

那么对于询问 $l, r, a, b$，则最终矩阵应该为 $\begin{bmatrix} a & b \end{bmatrix} \times \prod \limits_{i=l}^r p_i$。

容易发现可以线段树维护矩阵乘法。

对于区间反转，只需要维护区间反转后的乘积和反转前的乘积，反转时交换两个结果即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

const int N = 1e5 + 5;
const long long MOD = 1e9 + 7;
string s;
int n, m;

struct Matrix
{
	long long a[3][3];
	Matrix(long long ax, long long b, long long c, long long d)
	{
		a[1][1] = ax, a[1][2] = b, a[2][1] = c, a[2][2] = d;
	}
	Matrix()
	{
		a[0][0] = a[0][1] = a[0][2] = a[1][0] = a[1][1] = a[1][2] = a[2][0] = a[2][1] = a[2][2] = 0LL;
	}
	void Clear()
	{
		a[1][1] = -1LL;
	}
	friend Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.a[1][1] == -1LL) return b;
		if (b.a[1][1] == -1LL) return a;
		Matrix c;
		for (int i = 1; i <= 2; i++)
		{
			for (int j = 1; j <= 2; j++)
			{
				for (int k = 1; k <= 2; k++)
				{
					c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % MOD;
				}
			}
		}
		return c;
	}
};

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		Matrix ans1, ans2;
		bool revtag;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].ans1 = tr[u << 1].ans1 * tr[u << 1 | 1].ans1;
		tr[u].ans2 = tr[u << 1].ans2 * tr[u << 1 | 1].ans2;
	}
	void pushdown(int u)
	{
		if (tr[u].revtag)
		{
			tr[u].revtag = 0;
			swap(tr[u << 1].ans1, tr[u << 1].ans2);
			tr[u << 1].revtag ^= 1;
			swap(tr[u << 1 | 1].ans1, tr[u << 1 | 1].ans2);
			tr[u << 1 | 1].revtag ^= 1;
		}
	}
	void build(int u, int l, int r)
	{
		if (l == r)
		{
			tr[u] = { l, r };
			char c = s[l - 1];
			if (c == 'A')
			{
				tr[u].ans1 = Matrix(1LL, 0LL, 1LL, 1LL);
				tr[u].ans2 = Matrix(1LL, 1LL, 0LL, 1LL);
			}
			else
			{
				tr[u].ans2 = Matrix(1LL, 0LL, 1LL, 1LL);
				tr[u].ans1 = Matrix(1LL, 1LL, 0LL, 1LL);
			}
			return;
		}
		tr[u] = { l, r };
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void update(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			tr[u].revtag ^= 1;
			swap(tr[u].ans1, tr[u].ans2);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r);
		if (r > mid) update(u << 1 | 1, l, r);
		pushup(u);
	}
	Matrix query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			return tr[u].ans1;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		Matrix res;
		res.Clear();
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = res * query(u << 1 | 1, l, r);
		return res;
	}
}tr;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> s;
	tr.build(1, 1, n);
	while (m--)
	{
		int opt;
		cin >> opt;
		if (opt == 1)
		{
			int l, r;
			cin >> l >> r;
			tr.update(1, l, r);
		}
		else
		{
			int l, r;
			long long a, b;
			cin >> l >> r >> a >> b;
			Matrix res(a, b, 0LL, 0LL);
			res = res * tr.query(1, l, r);
			Matrix p = tr.query(1, l, r);
			printf("%lld %lld\n", res.a[1][1], res.a[1][2]);
		}
	}
	return 0;
}
```


---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/solution/CF1252K)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/01/21/CF1252K%20Addition%20Robot/)

## 前言

第一次做线段树维护矩阵乘法的题目，算是为 ddp 打基础了吧。

## 分析

注意到
$$
\begin{bmatrix}
A & B
\end{bmatrix}
\begin{bmatrix}
1 & 0\\
1 & 1
\end{bmatrix}
=
\begin{bmatrix}
A + B & B
\end{bmatrix}
$$

$$
\begin{bmatrix}
A & B
\end{bmatrix}
\begin{bmatrix}
1 & 1\\
0 & 1
\end{bmatrix}
=
\begin{bmatrix}
A & A + B
\end{bmatrix}
$$

所以我们可以用线段树一个区间内矩阵乘法的答案，因为字母类型单一，所以我们可以顺便存一下反转字符后的答案，修改时交换即可，时间复杂度 $O(n\log n)$，带 $2^3$ 的常数。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k, l) for (int i = (j); i <= (k); i += (l))
#define R(i, j, k, l) for (int i = (j); i >= (j); i -= (l))
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
struct Matrix {
	int a[2][2];
	Matrix(int p = 0, int q = 0, int x = 0, int y = 0) {a[0][0] = p, a[0][1] = q, a[1][0] = x, a[1][1] = y;}
	Matrix operator*(Matrix b) {
		Matrix c;
		L(k, 0, 1, 1) L(i, 0, 1, 1) L(j, 0, 1, 1) c.a[i][j] = (c.a[i][j] + 1ll * a[i][k] * 1ll * b.a[k][j] % mod) % mod;
		return c;
	}
};
struct Sgt
{
	int l, r, tag;
	Matrix res0, res1;
} t[N << 2];
char s[N];
inline int read() {
	int x = 0, y = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * y;
}
inline void pushup(int p) {
	Sgt &u = t[p], &l = t[p << 1], &r = t[p << 1 | 1];
	u.res0 = l.res0 * r.res0, u.res1 = l.res1 * r.res1;
}
inline void pushdown(int p) {
	if (t[p].tag) swap(t[p << 1].res0, t[p << 1].res1), t[p << 1].tag ^= 1, swap(t[p << 1 | 1].res0, t[p << 1 | 1].res1), t[p << 1 | 1].tag ^= 1, t[p].tag = 0;
}
inline void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].res0 = Matrix(1, 0, 1, 1);
		t[p].res1 = Matrix(1, 1, 0, 1);
		if (s[l] == 'B')
			swap(t[p].res0, t[p].res1);
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
inline void modify(int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) {
		swap(t[p].res0, t[p].res1), t[p].tag ^= 1;
		return;
	}
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) modify(p << 1, l, r);
	if (r > mid) modify(p << 1 | 1, l, r);
	pushup(p);
}

inline Sgt merge(Sgt l, Sgt r) {
	Sgt u;
	u.res0 = l.res0 * r.res0, u.res1 = l.res1 * r.res1;
	return u;
}

inline Sgt query(int p, int l, int r) {
	if (l <= t[p].l && t[p].r <= r) return t[p];
	pushdown(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l > mid) return query(p << 1 | 1, l, r);
	if (r <= mid) return query(p << 1, l, r);
	return merge(query(p << 1, l, r), query(p << 1 | 1, l, r));
}

int main() {
	int n = read(), q = read();
	cin >> s + 1;
	build(1, 1, n);
	while (q--) {
		int op = read(), l = read(), r = read();
		if (op == 1)
			modify(1, l, r);
		else {
			Matrix a;
			a.a[0][0] = read(), a.a[0][1] = read();
			a = a * query(1, l, r).res0;
			printf("%d %d\n", a.a[0][0], a.a[0][1]);
		}
	}
	return 0;
}
```



---

## 作者：tidongCrazy (赞：0)

提供一个和其他题解不同的思路，可以运用在这一类题中。

由于矩阵的结合律与线段树相契合，我们考虑用线段树来维护矩阵乘法。

我们有下列的式子：

$$
\begin{bmatrix}
A&B
\end{bmatrix}
\times
\begin{bmatrix}
1&0\\
1&1
\end{bmatrix}
=
\begin{bmatrix}
A+B&B
\end{bmatrix}
$$

$$
\begin{bmatrix}
A&B
\end{bmatrix}
\times
\begin{bmatrix}
1&1\\
0&1
\end{bmatrix}
=
\begin{bmatrix}
A&A+B
\end{bmatrix}
$$

但对于反转操作，考虑到它只有两种字母，我们可以在线段树的节点上开两个矩阵维护这个区间反转前与反转后分别的答案，然后开一个懒标记维护区间是否反转。

当我们进行反转操作时，只需要交换两个矩阵的值，然后打上懒标记即可。

对于一些在线段树上维护反转操作的题目可以考虑这么做，包括但不限于括号序列等等,省去了推两个矩阵之间关系的时间。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back

inline int read() {
	
	int w = 1, s = 0; char c;
	while(!isdigit(c = getchar())) if(c == '-') w = -1;
	while(isdigit(c)) s = (s << 1) + (s << 3) + (c & 15), c = getchar();
	return s * w;
}

void write(int x) {
	
	if(x < 0) x = -x, putchar('-');
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

inline void writeln(int x) { write(x); putchar('\n'); }
inline void writel(int x) { write(x); putchar(' '); }

inline int chkmax(int x, int y) { return x > y ? x : y; }
inline int chkmin(int x, int y) { return x < y ? x : y; }
inline void Swap(int &x, int &y) { x ^= y ^= x ^= y; }

const int N = 1e5 + 10;
const int p = 1e9 + 7;

struct Mat {
	
	int c[2][2];

	Mat() { memset(c, 0, sizeof(c)); }
};

Mat I;

inline Mat operator * (Mat A, Mat B) {
	
	Mat C;
	for(int k = 0; k < 2; k ++ )
		for(int i = 0; i < 2; i ++ )
			for(int j = 0; j < 2; j ++ )
				C.c[i][j] = (C.c[i][j] + A.c[i][k] * B.c[k][j] % p) % p;
	return C;
}

struct Node { Mat ans0, ans1; int tag; } tr[N << 2];

#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)

char str[N];

inline void pushup(int x) {

	tr[x].ans0 = tr[ls].ans0 * tr[rs].ans0;
	tr[x].ans1 = tr[ls].ans1 * tr[rs].ans1;
	return ;
}

inline Mat get(int a, int b, int c, int d) {
	
	Mat ans;
	ans.c[0][0] = a; ans.c[0][1] = b;
	ans.c[1][0] = c; ans.c[1][1] = d;
	return ans;
}

void build(int x, int l, int r) {
	
	if(l == r) {
		tr[x].ans0 = get(1, 0, 1, 1);
		tr[x].ans1 = get(1, 1, 0, 1);
		if(str[l] == 'B') swap(tr[x].ans0, tr[x].ans1);
		return ;
	} build(ls, l, mid); build(rs, mid + 1, r);
	pushup(x); return ;
}

inline void pushdown(int x) {
	
	if(tr[x].tag) {
		tr[ls].tag ^= 1; tr[rs].tag ^= 1;
		swap(tr[ls].ans0, tr[ls].ans1);
		swap(tr[rs].ans0, tr[rs].ans1);
		tr[x].tag = 0;
	} return ;
}

void modify(int x, int nl, int nr, int l, int r) {
	
	if(nl <= l && r <= nr) {
		swap(tr[x].ans0, tr[x].ans1);
		tr[x].tag ^= 1;
		return ;
	} pushdown(x);
	if(nl <= mid) modify(ls, nl, nr, l, mid);
	if(nr > mid) modify(rs, nl, nr, mid + 1, r);
	pushup(x); return ;
}

Mat query(int x, int nl, int nr, int l, int r) {
	
	if(nl <= l && r <= nr) return tr[x].ans0;
	pushdown(x);
	Mat ans = I;
	if(nl <= mid) ans = ans * query(ls, nl, nr, l, mid);
	if(nr > mid) ans = ans * query(rs, nl, nr, mid + 1, r);
	return ans;
}

int n, q;

inline void work() {
	
	I = get(1, 0, 0, 1);
	n = read(); q = read();
	scanf("%s", str + 1);
	build(1, 1, n);
	while(q -- ) {
		int op = read(), l = read(), r = read();
		if(op == 1) modify(1, l, r, 1, n);
		else {
			int a = read(), b = read();
			Mat qwq = get(a, b, 0, 0), ans = query(1, l, r, 1, n);
			Mat answ = qwq * ans;
			writel(answ.c[0][0]); writeln(answ.c[0][1]);
		}
	} return ;
}

signed main() {
	
	int T = 1;
	while(T -- ) work();
	return 0;
}
```

下面这道题也运用到了相似的思路。

[CF1371F](https://www.luogu.com.cn/problem/CF1371F)

---

## 作者：HyperSQ (赞：0)

很容易想到线性变换，由于矩阵乘法满足结合律，所以可以用线段树维护。

考虑矩阵

$$
A=\left[\begin{matrix}1 &1\\0&1\end{matrix}\right],
B=\left[\begin{matrix}1 &0\\1&1\end{matrix}\right]
$$

因此一次变换为

$$
\left[\begin{matrix}a'\\ b'\end{matrix} \right]=M\left[\begin{matrix}a\\ b\end{matrix} \right],M\isin\{A,B\}
$$

对于一次修改，就是把区间内的 $A,B$ 互换，类比线段树区间 0-1flip，每个区间维护两个矩阵，翻转的和不翻转的累积，在下推的时候将左右儿子也 flip 掉；查询的话就是用区间矩阵乘积乘上初始向量（因为线性变换中矩阵写在向量左边，所以注意维护的区间累积也要反过来）。

虽然还有 $A^{\operatorname{T}}=B$ 这个性质，但是这个做法完全用不上了（所以假如 $A$ 和 $B$ 没有任何特殊性质也可以做）。

[Code](https://www.luogu.com.cn/paste/4qjxzw4a)

---

## 作者：tommymio (赞：0)

线段树维护矩阵的模板题，第一次遇到这样的题所以记录一下。

考虑这个 $A=A+B,B=A+B$ 我们可以使用矩阵处理。

如下构造矩阵：

$$
\begin{bmatrix}
a \ \ b
\end{bmatrix}
\begin{bmatrix}
1 \ \ 0
\\
1 \ \ 1
\end{bmatrix}
=
\begin{bmatrix}
a+b \ \ b
\end{bmatrix}
$$

$$
\begin{bmatrix}
a \ \ b
\end{bmatrix}
\begin{bmatrix}
1 \ \ 1
\\
0 \ \ 1
\end{bmatrix}
=
\begin{bmatrix}
a \ \ a+b
\end{bmatrix}
$$

对于 $A,B$ 反转的操作，我们可以直接交换矩阵中的元素。

具体来说，对于一段区间所对应的矩阵

$$
\begin{bmatrix}
p \ \ q
\\
r \ \ s
\end{bmatrix}
$$

将这段区间内的 $A,B$ 反转后，其对应的矩阵为

$$
\begin{bmatrix}
s \ \ r
\\
q \ \ p
\end{bmatrix}
$$

可以使用数学归纳法尝试证明这一点。这里不做说明。

时间复杂度为 $O(2^3\times Q \log n)$。强调 $2^3$ 是为了突出矩阵乘法的常数（

这题还是灰的啊，我觉得评个蓝的挺好（

```cpp
/* stuff you should look for
	* int overflow, array bounds, uppercase/lowercase
	* special cases (n=1?)
	* do sth. instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
#include<cstdio>
#include<algorithm>
const int mod=1e9+7;
struct matrix {
	matrix() {a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;}
	inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
	inline void reverse() {swap(a[0][0],a[1][1]); swap(a[1][0],a[0][1]);}
	int a[2][2];
}A,B;
inline matrix operator*(const matrix &x,const matrix &y) {
	matrix res;
	for(register int i=0;i<2;++i) {
		for(register int j=0;j<2;++j) {
			for(register int k=0;k<2;++k) {
				(res.a[i][j]+=x.a[i][k]*1ll*y.a[k][j]%mod)%=mod; 
			}
		}
	}
	return res;
}
struct SegmentTree {
	#define ls p<<1
	#define rs p<<1|1
	int n,tag[400005];
	matrix mt[400005];
	inline void build(int p,int l,int r,char *s) {
		tag[p]=0;
		if(l==r) {
			mt[p]=(s[l]=='A'? A:B);
			return;
		} 
		int mid=l+r>>1;
		build(ls,l,mid,s); build(rs,mid+1,r,s);
		mt[p]=mt[ls]*mt[rs];
	}
	inline void init(int n,char *s) {this->n=n; build(1,1,n,s);}
	inline void spread(int p) {if(tag[p]) {mt[ls].reverse(); mt[rs].reverse(); tag[ls]^=1; tag[rs]^=1; tag[p]=0;}}
	inline void _modify(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R) {tag[p]^=1; mt[p].reverse(); return;}
		int mid=l+r>>1; spread(p);
		if(L<=mid) _modify(ls,l,mid,L,R);
		if(R>mid) _modify(rs,mid+1,r,L,R);
		mt[p]=mt[ls]*mt[rs];
	}
	inline matrix _ask(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return mt[p];
		int mid=l+r>>1; spread(p);
		if(R<=mid) return _ask(ls,l,mid,L,R);
		if(L>mid) return _ask(rs,mid+1,r,L,R);
		return _ask(ls,l,mid,L,mid)*_ask(rs,mid+1,r,mid+1,R);
	}
	inline void modify(int L,int R) {_modify(1,1,n,L,R);}
	inline std::pair<int,int> ask(int L,int R,int U,int V) {
		matrix tmp; tmp.a[0][0]=U; tmp.a[0][1]=V;
		matrix res=tmp*_ask(1,1,n,L,R); 
		return std::make_pair(res.a[0][0],res.a[0][1]);
	}
}SGT;
char s[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	A.a[0][0]=1; A.a[0][1]=0;
	A.a[1][0]=1; A.a[1][1]=1;
	B.a[0][0]=1; B.a[0][1]=1;
	B.a[1][0]=0; B.a[1][1]=1;
	int n=read(),Q=read();
	scanf("%s",s+1); SGT.init(n,s);
	while(Q--) {
		int op=read(),l=read(),r=read();
		if(op==1) {
			SGT.modify(l,r);
		}
		else {
			int U=read(),V=read();
			std::pair<int,int> res=SGT.ask(l,r,U,V);
			printf("%d %d\n",res.first,res.second);
		}
	}
	return 0;
}
```

---

