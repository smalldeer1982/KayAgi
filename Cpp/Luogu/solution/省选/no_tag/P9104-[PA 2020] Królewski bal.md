# [PA 2020] Królewski bal

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Królewski bal](https://sio2.mimuw.edu.pl/c/pa-2020-1/bal/)**

自古以来，Byteotia 的所有统治者都会举行奢华的舞会，Byteur 国王也不例外。然而，每当他组织一次，他就觉得少了点什么。因此，他决定在下一次舞会中加入一些艺术元素。

为此，Byteur 国王委托他的首席顾问编排演出，不久之后，首席顾问向他提出了自己的设想。

根据顾问的计划，$n^2$ 名马戏团演员将参加演出，其中 $n$ 是一个正整数。在演出的压轴部分，他们将排成 $n$ 行，每行恰好有 $n$ 个马戏团演员，从而形成一个 $n\times n$ 大小的正方形。在压轴部分开始时，每个演员将带或不带燃烧的呼拉圈跳舞。在午夜时分，一些带着呼啦圈跳舞的马戏团演员可能会把呼啦圈扔给其他没有带呼啦圈跳舞的马戏团演员。每个演员最多允许扔给一个其他的演员。

他们都会在同一时间进行投掷。他们是专业人士，所以他们的呼啦圈肯定不会在空中相撞，但这里有一个问题。**每次投掷必须在位于同一行或同一列的演员之间进行**。

值得一提的是，Byteur 国王喜欢大规模的行动，所以马戏团演员的数量可能非常庞大。在制定计划时，他的顾问首先确定了数字 $n$，并假设所有马戏团的演员都会在没有燃烧呼拉圈的情况下开始最后的表演。然后，他会选择 $m$ 次一些特定的行列范围，画出一个矩形，并使得这个区域中的每个演员应该以不同的方式开始压轴表演。即，如果在之前的方案中他们拿着呼啦圈开始，则这版方案中他们就不拿呼啦圈开始，反之亦然。

Byteur 国王在得知顾问的计划后，立即明白，为了使演出尽可能地壮观，呼啦圈的抛掷次数应该尽可能地多。Byteur 国王想知道这个数字，但这并不容易，因为他不断修改计划。他的每项修改（他总共已经做了 $q$ 次修改）都涉及到挑选一个马戏团演员并改变他开始压轴表演的方式（即如果他之前拿着呼啦圈开始，那么他现在就不拿着呼啦圈开始，反之亦然）。国王的修改在方案上永久保留，也就是说，如果有任何适用于某个马戏团演员的修改，这个修改的效果一直保留到最后，除非国王再次修改他。

因此，顾问的任务并不简单。帮助他，对于区间 $[0, q]$ 中的每个整数 $i$，在考虑国王的前 $i$ 次修改后，确定可能发生的最大投掷次数。

## 说明/提示

#### 样例 1 解释

下图展示了国王进行了第一次修改后的情况。演出开始有呼啦圈的演员用加粗圆圈标出，箭头标明了可能发生的投掷。

![](https://cdn.luogu.com.cn/upload/image_hosting/brbphngp.png)

------------

#### 数据范围

**本题采用捆绑测试**

- 对于一些子任务，满足 $n\le 50$，$m\le 10^4$，$q=0$。
- 对于一些其他的子任务，满足 $n\le 200$，$m\le 10^5$，$q\le 10$。
- 对于一些其他的子任务，满足 $n\le 2\times 10^3$，$m\le 10^5$，$q\le 5\times 10^3$。
- 对于一些其他的子任务，满足 $q=0$。

对于上述情况，至少有一个子任务满足。

对于 $100\%$ 的数据，保证 $1\le n\le 3\times 10^5$，$0\le m,q\le 3\times 10^5$，$1\le x_1\le x_2\le n$，$1\le y_1\le y_2\le n$，$1\le a_i,b_i\le n$。

此外，对于每个子任务，至少满足以下条件中的一个：

- $n\le 2\times 10^3$
- 时间限制为 $12$ 秒

由于未给出具体子任务时间限制，因此在洛谷上所有子任务的时间限制均为 $3$ 秒。

## 样例 #1

### 输入

```
4 3 4
1 2 4 2
3 1 3 4
3 2 3 2
4 4
3 2
4 3
4 4```

### 输出

```
6
7
7
8
7```

## 样例 #2

### 输入

```
7 2 0
1 1 6 6
2 2 7 7```

### 输出

```
22```

# 题解

## 作者：D2T1 (赞：0)

转化题意，对两种表演方式（设为黑/白）建二分图，左侧黑右侧白，两个点连边当且仅当在同一行或者同一列。那么答案就是这张二分图的最大匹配。

最大匹配显然是不好做的，考虑转化为 $n^2-$ 最大独立集。

最大独立集在原方阵中形如怎么样的呢？形如每一行/每一列中选的格子只会有一种颜色。也就是说可以通过如下方式得到一个独立集：枚举列、行中选择白色的集合 $S,T$，对于点 $(x,y)$，若目前为白且 $x\in T,y\in S$ 即贡献 $1$；若目前为黑且 $x\notin T,y\notin S$ 即贡献 $1$。

枚举列选择的方案，设集合 $S$ 中的列选了白，所有行都选了白。则现在的贡献是这 $S$ 列中白格子个数。

考虑每一行变为黑是否会增加答案。对于行上的点有四种情况：

1. 目前为白，所在的列选白。
2. 目前为白，所在的列选黑。
3. 目前为黑，所在的列选白。
4. 目前为黑，所在的列选黑。

若一行由白变为黑，那么对答案的贡献是情况 $4$ 的点数减去情况 $1$ 的点数。有点麻烦，稍微推推式子可以得到一个惊人的结论：对答案的贡献是行内黑格子数减去白的列数，即**贡献与 $S$ 具体内容没有任何关系，只和 $|S|$ 有关**！那么行与列的决策就相对独立了。

于是计算出 $a$ 数组表示每一列的白格子数，$b$ 数组表示出每一行的黑格子数，那么答案可以写作：

$$\max_{x=0}^n\{\sum_{i=1}^n\max(0,b_i-x)+\sum_{i=1}^x A_i\}$$

其中 $A$ 为 $a$ 数组降序排好序的结果。

对于第一次询问，可以扫描线预处理出 $a,b$ 数组后计算答案。考虑修改，使用线段树维护每个 $x$，上述式子的值。修改形如 $a,b$ 的单点修改，也即 $A,b$ 的单点修改，带入上述式子容易发现都是一个区间修改。使用一个区间修、询问全局 $\max$ 的线段树即可维护。

复杂度 $O(n\log n)$。

代码中 $a,b$ 表示的行列与题解描述的相反。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;

const int N = 3e5 + 10;
int n, m, Q;
vector<int> qry[N];
vector<pair<int, int> > cg[N], cgg[N];
int qx[N], qy[N], val[N], to[N];

struct segtree{
	int t[N*4], tag[N*4];
	void psd(int p, int l, int r){
		int mid = l + r >> 1;
		if(tag[p]){
			t[p<<1] = (mid - l + 1) - t[p<<1];
			t[p<<1|1] = (r - mid) - t[p<<1|1];
			tag[p<<1] ^= 1;
			tag[p<<1|1] ^= 1;
			tag[p] = 0;
		}
	}
	void build(){
		memset(t, 0, sizeof(t));
		memset(tag, 0, sizeof(tag));
	}
	void rev(int p, int l, int r, int ql, int qr){
		if(qr < l || r < ql){
			return;
		} else if(ql <= l && r <= qr){
			t[p] = (r - l + 1) - t[p];
			tag[p] ^= 1;
		} else {
			int mid = l + r >> 1;
			psd(p, l, r);
			rev(p<<1, l, mid, ql, qr);
			rev(p<<1|1, mid+1, r, ql, qr);
			t[p] = t[p<<1] + t[p<<1|1];
		}
	}
	int ask(int p, int l, int r, int ql, int qr){
		if(qr < l || r < ql){
			return 0;
		} else if(ql <= l && r <= qr){
			return t[p];
		} else {
			int mid = l + r >> 1;
			psd(p, l, r);
			return ask(p<<1, l, mid, ql, qr) + ask(p<<1|1, mid+1, r, ql, qr);
		}
	}
} t;

int a[N], b[N];
int A[N];
int al[N], ar[N];
ll tb[N];

struct seggtree{
	ll t[N*4], tag[N*4];
	void psd(int p){
		tag[p<<1] += tag[p];
		tag[p<<1|1] += tag[p];
		t[p<<1] += tag[p];
		t[p<<1|1] += tag[p];
		tag[p] = 0;
	}
	void add(int p, int l, int r, int ql, int qr, ll v){
		if(qr < l || r < ql){
			return;
		} else if(ql <= l && r <= qr){
			t[p] += v;
			tag[p] += v;
		} else {
			int mid = l + r >> 1;
			psd(p);
			add(p<<1, l, mid, ql, qr, v);
			add(p<<1|1, mid+1, r, ql, qr, v);
			t[p] = max(t[p<<1], t[p<<1|1]);
		}
	}
	ll qrymx(){
		return t[1];
	}
} tt;

map<int, int> id[N];
int idc;

int main(){
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; ++ i){
		int x, y, xx, yy;
		scanf("%d%d%d%d", &x, &y, &xx, &yy);
		cg[x].push_back(make_pair(y, yy));
		cg[xx+1].push_back(make_pair(y, yy));
		cgg[y].push_back(make_pair(x, xx));
		cgg[yy+1].push_back(make_pair(x, xx));
	}
	for(int i = 1; i <= Q; ++ i){
		int x, y;
		scanf("%d%d", &x, &y);
		qx[i] = x;
		qy[i] = y;
		qry[x].push_back(i);
	}
	t.build();
	for(int i = 1; i <= n; ++ i){
		for(pair<int, int> p : cg[i]){
			t.rev(1, 1, n, p.first, p.second);
		}
		A[i] = a[i] = n - t.ask(1, 1, n, 1, n);
		for(int p : qry[i]){
			if(!id[i][qy[p]]){
				id[i][qy[p]] = ++ idc;
			}
			val[id[i][qy[p]]] = t.ask(1, 1, n, qy[p], qy[p]);
		}
	}
	t.build();
	for(int i = 1; i <= n; ++ i){
		for(pair<int, int> p : cgg[i]){
			t.rev(1, 1, n, p.first, p.second);
		}
		b[i] = t.ask(1, 1, n, 1, n);
		++ tb[1];
		-- tb[b[i]+1];
	}
	sort(A + 1, A + n + 1);
	reverse(A + 1, A + n + 1);
	int la = n + 1;
	for(int i = 1; i <= n + 1; ++ i){
		ar[la] = i-1;
		for(int j = la - 1; j >= A[i]; -- j){
			al[j] = i;
			ar[j] = i-1;
		}
		if(la != A[i] && A[i] >= 0){
			la = A[i];
			al[A[i]] = i;
		}
	}
	for(int i = 1; i <= n; ++ i){
		tb[i] += tb[i-1];
		tt.add(1, 0, n, i, n, A[i]);
		tt.add(1, 0, n, 0, i-1, tb[i]);
	}
	printf("%lld\n", 1ll * n * n - tt.qrymx());
	for(int i = 1; i <= Q; ++ i){
		if(val[id[qx[i]][qy[i]]] == 1){
			int na = a[qx[i]];
			++ a[qx[i]];
			tt.add(1, 0, n, al[na], n, 1);
			++ al[na];
			++ ar[na+1];
			-- b[qy[i]];
			tt.add(1, 0, n, 0, b[qy[i]], -1);
		} else {
			int na = a[qx[i]];
			-- a[qx[i]];
			tt.add(1, 0, n, ar[na], n, -1);
			-- ar[na];
			-- al[na-1];
			tt.add(1, 0, n, 0, b[qy[i]], 1);
			++ b[qy[i]];
		}
		val[id[qx[i]][qy[i]]] ^= 1;
		printf("%lld\n", 1ll * n * n - tt.qrymx());
	}
	return 0;
}
```

---

