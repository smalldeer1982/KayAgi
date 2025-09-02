# A + B

## 题目描述

在编程比赛的集训中没有出现问题的想法而感到为难的甲，某一天和朋友商量了。

A: “如果不使用这种算法的话，我想提出一个无法解决的问题，怎么做~？”

朋友：“这种东西想想不就出来了吗？”（真NB）

就这样，那个朋友考虑了以下问题的草案。

给你两个二进制数A,B，做如下变换：

操作1：输出在二进制下1的个数最大的X;A<=X<=A+B;

操作2：将A从开始最下位翻转i位；

操作3：将B从开始最下位翻转i位；

注：i是从最下位到第0位表示最下位

# 题解

## 作者：HanPi (赞：17)

**[AT750 A + B](https://www.luogu.com.cn/problem/AT750)**

$\LARGE\mathtt{Solution:}$

朴素算法加一点小优化.

$\mathtt{sum}:\text{储存}\mathtt{A+B}\text{的和}$

- 读入:
我个人建议倒序存储,比较方便.

- 操作A,B:
取反不解释,在取反后对 $\mathtt{sum}$ 的值同步更改.

- 操作Q:
在二进制中的 $\mathtt{A \sim sum}$ 中找一个含 $1$ 最多的数,输出它有多少个 $\mathtt{1}$ .

	首先直接暴力枚举是肯定会超时的,让我们思考一下,如果要含 $\mathtt{1}$ 最多,那么对于更改后仍 $\mathtt{<sum}$ 的部分一定全填 $\mathtt{1}$ , 其他位置如果 $\mathtt{sum}$ 在该位置是 $\mathtt{1}$ 那么也可以填 $\mathtt{1}$ .
    
    所以我们从**最高位**开始遍历 $\mathtt{sum}$ ,如果 $\mathtt{sum[i]==A[i]}$ 且 $\mathtt{sum[i]==1}$, `ans++` .如果不同,那么答案加上剩余的长度,即 `ans += i;`
    
然而很遗憾,第64个点 $\color{white}\colorbox{#052242}{\texttt{ TLE }}$ 了.
不过经过我的奇思妙想,我想出了一种奇 $\mathtt{miu}$ 的优化:

测试点中,肯定会有**连续询问 `'Q'` 的情况**, 
所以遇到这种情况我们**只需要输出上一次操作结果即可**.

就 $\color{white}\colorbox{#52C41A}{\texttt{ AC }}$ 了,虽然是 $\mathtt{10.20s}$ ...

**代码:**

```c
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>

#define SWAP(_a,_b) ((_a)^=(_b)^=(_a)^=(_b))

char A[300007], B[300007], op,lastOP,sum[300007];
int a[300007], b[3000007];
int la, lb, lmax, N, opIndex, ans;

void Init()
{
    int i;
    scanf("%d%s%s", &N,&A,&B);
    getchar();
    la = strlen(A);
    lb = strlen(B);
    // 倒序存储
    for (i = 0; i < la; ++i)a[la - 1 - i] = A[i] - '0';
    for (i = 0; i < lb; ++i)b[lb - 1 - i] = B[i] - '0';

    lmax = la > lb ? la + 1 : lb + 1; // +1是因为相加后可能会有进位
}

void AddOne(int _index)
{
    sum[_index]++;
    if (sum[_index] >= 2)
    {
        while (_index < lmax)
        {
            sum[_index + 1]++;
            sum[_index] -= 2;
            if (sum[_index + 1] == 1)break;
            _index++;
        }
    }
}


void LowOne(int _index)
{
    sum[_index]--;
    if (sum[_index] < 0)
    {
        while (_index < lmax)
        {
            sum[_index + 1]--;
            sum[_index] += 2;
            if (sum[_index + 1] == 0)break;
            _index++;
        }
    }
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    Init();
    int i;
    for (i = 0; i < lmax; ++i)
    {
        sum[i] += a[i] + b[i];
        if (sum[i] >= 2) {
            sum[i] -= 2;
            sum[i + 1]++;
        }
    }
    while (N--)
    {
        scanf("%c", &op);
        if(op== 'Q')
        {
            op=getchar();
            if (lastOP == 'Q')
            {
                printf("%d\n", ans);
                continue;
            }
            ans = 0;            
            for (i = lmax; i >=0; --i)
            {
                if (a[i] != sum[i])
                {
                    ans += i;
                    break;
                }
                if (a[i]==1)ans++;
            }
            printf("%d\n", ans);
        }
        else if (op == 'A')
        {
            scanf("%d", &opIndex);
            getchar();
            a[opIndex] ? LowOne(opIndex) : AddOne(opIndex);
            a[opIndex] = !a[opIndex];
        }
        else if (op == 'B')
        {
            scanf("%d", &opIndex);
            getchar();
            b[opIndex] ? LowOne(opIndex) : AddOne(opIndex);
            b[opIndex] = !b[opIndex];
        }
        lastOP = op;
    }
    return 0;
}
```


------------
~~与 [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001) 只差一个 `Problem` 难度就上天了...~~

刚刚重新交了一遍,尽然变成 $\mathtt{8.19s}$ 了,真就 `网速 == 评测姬速度` ???

---

## 作者：Misaka14285 (赞：13)

御坂对暴力题解感到无语 就没有更像样点的东西吗 御坂隐藏真心话并长叹一声

注意翻译有坑，应为 $A\le X\color{red}
<\color{default}A+B$。

考虑优化 $O(n^2)$ 暴力，关键在于找到 $A+B$ 与 $A$ 的最高不同位，显然一定大于等于 $B$ 的最高位。

因此先找出 $B$ 的最高位 $x$，然后求 $x+1$ 往后最后一个 $A_i=1$ 的位置 $y$（因为连续的 $1$ 可能导致进位），然后再从 $y$ 向前找到第一个 $A_i+B_i\neq 1$ 的位置 $z$，若 $A_z=B_z=1$ 则有进位，否则没有。

容易验证，答案为 $y+S(y+1,n)+[A_z=1]$，其中 $S(l,r)=\sum_{i=l}^ra_i$。

具体实现时用线段树维护区间 $A=i,B=j$ 的位置个数，然后二分即可。复杂度 $O(n\log n)$。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 300100;
char a[N], b[N];

const int A0B0 = 1, A0B1 = 2, A1B0 = 4, A1B1 = 8, A = 2, B = 1;

struct Info {
	int a[4];
	int query(int mask) {
		int ans = 0;
		if (mask & 1) ans += a[0];
		if (mask & 2) ans += a[1];
		if (mask & 4) ans += a[2];
		if (mask & 8) ans += a[3];
		return ans;
	}
	void modify(int mask) {
		if (mask & 2) swap(a[0], a[2]), swap(a[1], a[3]);
		if (mask & 1) swap(a[0], a[1]), swap(a[2], a[3]);
	}
	Info operator + (const Info &b) const {
		return (Info){a[0] + b.a[0], a[1] + b.a[1], a[2] + b.a[2], a[3] + b.a[3]};
	}
} arr[N << 2];
int tag[N << 2];

#define lc p << 1
#define rc p << 1 | 1
void up(int p) { arr[p] = arr[lc] + arr[rc]; }
void mod(int p, int k) { tag[p] ^= k, arr[p].modify(k); }
void down(int p) { mod(lc, tag[p]), mod(rc, tag[p]), tag[p] = 0; }
int que(int p, int k) { return arr[p].query(k); }

void build(int l, int r, int p) {
	if (l == r) {
		arr[p].a[a[l] << 1 | b[l]] = 1;
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, lc), build(m + 1, r, rc), up(p);
}

int qsum(int ql, int qr, int k, int l, int r, int p) {
	if (ql == l && qr == r) return arr[p].query(k);
	int m = (l + r) >> 1; down(p);
	if (qr <= m) return qsum(ql, qr, k, l, m, lc);
	else if (ql > m) return qsum(ql, qr, k, m + 1, r, rc);
	else return qsum(ql, m, k, l, m, lc) + qsum(m + 1, qr, k, m + 1, r, rc);
}
void modify(int ql, int qr, int k, int l, int r, int p) {
	if (ql == l && qr == r) return mod(p, k);
	int m = (l + r) >> 1; down(p);
	if (qr <= m) modify(ql, qr, k, l, m, lc);
	else if (ql > m) modify(ql, qr, k, m + 1, r, rc);
	else modify(ql, m, k, l, m, lc), modify(m + 1, qr, k, m + 1, r, rc);
	up(p);
}
int nxt(int x, int k, int l, int r, int p) {
	int tmp = arr[p].query(k);
	if (tmp == r - l + 1) return r + 1;
	if (!tmp) return x;
	int m = (l + r) >> 1; down(p);
	if (x > m) return nxt(x, k, m + 1, r, rc);
	x = nxt(x, k, l, m, lc);
	return x > m ? nxt(x, k, m + 1, r, rc) : x;
}
int pre(int x, int k, int l, int r, int p) {
	int tmp = arr[p].query(k);
	if (tmp == r - l + 1) return l - 1;
	if (!tmp) return x;
	int m = (l + r) >> 1; down(p);
	if (x <= m) return pre(x, k, l, m, lc);
	x = pre(x, k, m + 1, r, rc);
	return x <= m ? pre(x, k, l, m, lc) : x;
}

int main() {
	int q;
	scanf("%d %s %s", &q, a, b);
	reverse(a, a + strlen(a)), reverse(b, b + strlen(b));
	int n = max(strlen(a), strlen(b));
	for (int i = 0; a[i]; i++) a[i] ^= 48;
	for (int i = 0; b[i]; i++) b[i] ^= 48;
	build(0, n, 1);
	char op[10];
	for (int x; q; q--) {
		scanf("%s", op);
		if (*op == 'Q') {
			x = pre(n, A1B0 | A0B0, 0, n, 1);
			x = nxt(x + 1, A1B0 | A1B1, 0, n, 1) - 1;
			int ans = qsum(x + 1, n, A1B0 | A1B1, 0, n, 1) + x;
			x = pre(x, A1B0 | A0B1, 0, n, 1);
			if (x >= 0 && a[x]) ans++;
			printf("%d\n", ans);
		} else {
			scanf("%d", &x);
			if (*op == 'A') a[x] ^= 1, modify(x, x, A, 0, n, 1);
			else b[x] ^= 1, modify(x, x, B, 0, n, 1);
		}
	}
}
```

---

