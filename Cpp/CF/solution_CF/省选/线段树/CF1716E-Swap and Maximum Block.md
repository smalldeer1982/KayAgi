# Swap and Maximum Block

## 题目描述

You are given an array of length $ 2^n $ . The elements of the array are numbered from $ 1 $ to $ 2^n $ .

You have to process $ q $ queries to this array. In the $ i $ -th query, you will be given an integer $ k $ ( $ 0 \le k \le n-1 $ ). To process the query, you should do the following:

- for every $ i \in [1, 2^n-2^k] $ in ascending order, do the following: if the $ i $ -th element was already swapped with some other element during this query, skip it; otherwise, swap $ a_i $ and $ a_{i+2^k} $ ;
- after that, print the maximum sum over all contiguous subsegments of the array (including the empty subsegment).

For example, if the array $ a $ is $ [-3, 5, -3, 2, 8, -20, 6, -1] $ , and $ k = 1 $ , the query is processed as follows:

- the $ 1 $ -st element wasn't swapped yet, so we swap it with the $ 3 $ -rd element;
- the $ 2 $ -nd element wasn't swapped yet, so we swap it with the $ 4 $ -th element;
- the $ 3 $ -rd element was swapped already;
- the $ 4 $ -th element was swapped already;
- the $ 5 $ -th element wasn't swapped yet, so we swap it with the $ 7 $ -th element;
- the $ 6 $ -th element wasn't swapped yet, so we swap it with the $ 8 $ -th element.

So, the array becomes $ [-3, 2, -3, 5, 6, -1, 8, -20] $ . The subsegment with the maximum sum is $ [5, 6, -1, 8] $ , and the answer to the query is $ 18 $ .

Note that the queries actually change the array, i. e. after a query is performed, the array does not return to its original state, and the next query will be applied to the modified array.

## 说明/提示

Transformation of the array in the example: $ [-3, 5, -3, 2, 8, -20, 6, -1] \rightarrow [-3, 2, -3, 5, 6, -1, 8, -20] \rightarrow [2, -3, 5, -3, -1, 6, -20, 8] \rightarrow [5, -3, 2, -3, -20, 8, -1, 6] $ .

## 样例 #1

### 输入

```
3
-3 5 -3 2 8 -20 6 -1
3
1
0
1```

### 输出

```
18
8
13```

# 题解

## 作者：E_firework (赞：12)

显然操作之间的顺序是对答案没有影响的，而两个相同操作会抵消，所以可能的状态只有 $2^n$ 种，我们尝试直接预处理出所有的答案。全局最大子段和问题可以用分治做，只需求出每个区间的最大前缀，最大后缀，最大子段和以及元素和。一次参数为 $i$ 的操作相当于把分治过程中第一个长度为 $2^i$ 的区间与第二个长度为 $2^i$ 的区间交换，把分治过程中第三个长度为 $2^i$ 的区间与第四个长度为 $2^i$ 的区间交换……而每次交换的两个区间合在一起正好是一个分治过程中出现过的区间，这意味着我们没有必要真的交换元素，只需记录当前状态有哪些长度的区间被交换了。

一个朴素的做法是在对每个状态直接分治求答案。这时我们发现有一部分子问题是重叠的，如果重复计算复杂度就不优秀，我们可以把每层分治的答案放进一个类似线段树的结构中，分治时如果有重复就不继续向下求解。这时我们只需找到一个合适的顺序求解每个状态。我们用一个二进制数 $i$ 表示一个状态，第 $i$ 位为 $1$ 表示进行了奇数次参数为 $n-i$ 的操作，从 $0$ 枚举到 $2 ^n-1$。设 $i$ 的最低的为 $1$ 的位是 $\operatorname{lowbit}(i)$（从 $1$ 开始记），编号为 $i$ 与编号为 $i - 1$ 的状态之间只有 $1$ 到 $\operatorname{lowbit}(i)$ 这几位不同，需要递归 $\operatorname{lowbit}(i)$ 层共 $2^{lowbit(i)}-1$ 个节点。

当然，由于树的结构是固定的，你没必要真的分治，可以从底向上处理。

发现 $j$ 作为 $\operatorname{lowbit}(i)$ 会出现 $2^{n-j}$ 次，每次遍历 $2^j-1$ 个节点，时间复杂度为 $O(n\times2^n+q)$。

code:

```cpp
#include <bits/stdc++.h>
#define LL long long
#define max(i, j) (i > j ? i : j)
#define min(i, j) (i < j ? i : j)
#define mes(s, x) memset(s, x, sizeof(s))
#define lb(i) (i & -(i))
#define mod 998244353
inline LL read(){char c;c = getchar();while(!(('0' <= c && c <= '9') || c == '-')) c = getchar();bool flag = 0;if(c == '-'){flag = 1;c = getchar();}LL tot = 0;while('0' <= c && c <= '9'){tot = 10 * tot + c - '0';c = getchar();}return flag ? -tot : tot;}
inline void _write(LL i){if(i == 0) return;_write(i / 10);putchar(i % 10 + '0');return;}
inline void write(LL i){if(i == 0) putchar('0');else if(i < 0){putchar('-');_write(-i);}else _write(i);return;}
using namespace std;
int a[262150], pw[25], cur, lg2[262150];
struct node{
	LL l, r, s, x;
	node operator+(const node i)const{
		return{
			max(l, s + i.l),
			max(r + i.s, i.r),
			s + i.s,
			max(r + i.l, max(x, i.x))
		};
	}
}b[524295];
LL ans[262150];
int main(){
	int n = read(), x, q;
	pw[0] = 1;
	for(int i = 1; i <= n + 1; i++) pw[i] = 2 * pw[i - 1];
	lg2[1] = 0;
	for(int i = 2; i < pw[n]; i++) lg2[i] = lg2[i / 2] + 1;
	for(int i = pw[n]; i < pw[n + 1]; i++){
		x = read();
		if(x > 0) b[i] = {x, x, x, x};
		else b[i] = {0, 0, x, 0};
	}
	for(int i = pw[n] - 1; i >= 1; i--) b[i] = b[2 * i] + b[2 * i + 1]; 
	ans[0] = b[1].x;
	for(cur = 1; cur < (1 << n); cur++){
		x = log2(lb(cur));
		for(int i = pw[lg2[lb(cur)] + 1] - 1; i >= 1; i--){
			if(cur & (1 << lg2[i])) b[i] = b[2 * i + 1] + b[2 * i];
			else b[i] = b[2 * i] + b[2 * i + 1];
		}
		ans[cur] = b[1].x;
	}
	q = read(), cur = 0;
	for(int i = 1; i <= q; i++){
		x = read();
		cur ^= (1 << (n - x - 1));
		printf("%lld\n", ans[cur]);
	}
 	return 0;
}
```

---

## 作者：yzy1 (赞：6)

考虑把数组下标减一，变为 $0$ 至 $2^n - 1$，可以发现每次操作相当于把下标为 $i$ 和 $i \oplus 2^k$ 的交换．根据异或的性质，本质不同的交换后得到的序列只有 $2^n$ 种，我们可以先预处理出 $2^n$ 个答案，最后询问的时候直接输出预处理好的答案即可．

看到异或先想到 trie 和线性基，对于本题 trie 更为合理．考虑给每种不同的交换序列赋予一个 $n$ 位的二进制数 $S$ 作为状态，则有以下对应关系：

- $i$ 和 $i \oplus 2^k$ 被交换 $\Leftrightarrow$ $S_k=1$ $\Leftrightarrow$ trie 的从下到上第 $k+2$ 层的所有结点的两个儿子交换．

如果我们暴力去枚举所有状态，时间复杂度是 $O((2^n)^2)$，无法通过本题．但是可以发现，对于一些结点，若我们仅看这个结点所对应的区间，则在可能在不同状态得到的序列是重复的．具体来讲，从下到上第 $i$ 层的结点，得到的序列只和 $S$ 的低 $i$ 位有关，即本质不同的状态只有 $2^i$ 种．

考虑分治，从底向上做．对于每个结点统计出在每个本质不同的 $S$ 状态的下的形如（区间和，区间最大前缀和，区间最大后缀和，区间最大子区间和）的「信息」．注意到这个「信息」与线段树维护区间最大子区间和时使用的信息相同．设当前分治到的结点属于从下到上第 $i$ 层，且我们已经通过分治得到了当前结点两个儿子的 $2^{i-1}$ 个「信息」，则在当前结点，我们可以选择交换两个儿子或不交换，并将左右合并，得到 $2^k$ 个不同本质不同的 $S$ 对应的「信息」．

这个做法的时间复杂度符合递推式 $T(2^n) = 2 T(2^{n-1}) + 2 O(2^{n-1})$．令 $N=2^n$，则有 $T(N) = 2 T(N/2) + O(N)$．根据主定理得，该做法的时间复杂度为 $O(N \log N)$，即 $O(n 2^n)$．

代码参考见 [原始 OJ 提交](https://codeforces.com/contest/1716/submission/222533165)。


---

## 作者：violin_wyl (赞：4)

# [Swap and Maximum Block](https://codeforces.com/contest/1716/problem/E)

## 解析：

### 题目大意：

给定一个长度为 $2^n$ 的数组。你需要回答 $q$ 次查询。对于每次询问将给你一个整数 $k(0\leq k\le n-1)$ 。

对于一次询问，你需要操作每个 $a_i,i \in [1,2^n-2^k]$，如果**在此查询期间**第 i 个元素未与其他元素交换，则交换 $a_i$ 和 $a_{i+2^k}$；否则，则跳过它；并输出交换完成后的数组的最大子段和（包括空子段）。

每次执行查询后，数组不会恢复到原来的状态。

--------------------------

### 思路：

玄学复杂度好题，我们可以把序列抽象成线段树的模型，那么一次操作实际上就是交换 $k$ 层的所有区间的左右子树，并且不同的 $k$ 之间互不影响。那么我们考虑实际上有 $2^n$ 种不同的答案，即对于每层都有交换和不换两种状态。

如果我们直接暴力处理这 $2^n$ 种答案，那么复杂度为 $\mathcal O(2^{2n})$，无法接受。

所以我们考虑剪枝，我们逐层考虑当前层交不交换，假设当前层为 $k$，我们现在已经处理好每次操作的 $q_i \in[0,k-1]$ 共 $2^{k-1}$ 种不同情况的答案（此时可以回答每次操作的 $i$ 都小于 $k$ 的答案），我们记录下面的 $2^{k-1}$ 所对应的每一个 $k-1$ 层的信息（即最大子段和，不会的移步[小白逛公园](https://www.luogu.com.cn/problem/P4513)）。对于每种情况在 $k$ 这一层都可以换/不换，那么就扩展到了 $2\times 2^{k-1}=2^k$种情况，每种都暴力往上合并出 $[k+1,n]$ 层都不换的最大子段和。那么对于每种信息需要往上合并 $2^{n-k}$ 次，并且我们只需要维护 $n$ 层的答案。

剪枝后的复杂度玄学的降到了 $\mathcal O(n\times 2^k\times 2^{n-k})=\mathcal O(n\times 2^n)$。

维护这个东西直接分治即可。

----------------------------------------------------

## code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = (1 << 18) + 10;
const int INF = 0x3f3f3f3f;
typedef pair <int, int> pii;
inline int read ()
{
    int x = 0, f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar (); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar (); }
    return x * f;
}
int n, q;
int a[N];
struct node {
    int lx, rx, mx, sum;
} s[N << 1], s2[N << 1];
int id[N], ans[N];
inline void merge (node &res, node x, node y)
{
    res.mx = max (max (x.mx, y.mx), max (0ll, x.rx + y.lx));
    res.lx = max (x.lx, x.sum + y.lx);
    res.rx = max (y.rx, y.sum + x.rx);
    res.sum = x.sum + y.sum;
}
node divide (int l, int r, int len, int st)
{
    if (r - l + 1 == len) return s[st + (r / len)];
    int mid = (l + r) >> 1;
    node x = divide (l, mid, len, st);
    node y = divide (mid + 1, r, len, st);
    node res;
    merge (res, x, y);
    return res;
}
signed main()
{
    n = read (); n = (1 << n);
    for (int i = 1; i <= n; i++) a[i] = read ();
    for (int i = 1; i <= n; i++) s[i] = s[n + i] = (node) { a[i], a[i], a[i], a[i]};
    for (int i = n + 1; i <= 2 * n; i += 2) swap (s[i], s[i + 1]);
    ans[0] = divide (1, n, 1, 0).mx;
    ans[1] = divide (1, n, 1, n).mx;
    int li = 2; id[1] = 0, id[2] = 1;
    for (int i = 2, j = 2; j + i <= n; j += i, i <<= 1)
    {
        queue <int> que;
        for (int k = 1; k <= li; k++) que.push (id[k]); li = 0;
        while (!que.empty ()) { int x = que.front (); que.pop (); id[++li] = x, id[++li] = x ^ i; }
        int len = n / i;
        for (int k = 1; k <= n; k++) merge (s2[k], s[2 * k - 1], s[2 * k]);
        int it1 = 0, it2 = 0;
        for (int cnt = 1; cnt <=  i; cnt++)
        {
            for (int x = len; x--; ) s[++it1] = s2[++it2];
            int h = it1;
            for (int x = len; x--; ) s[it1] = s[++it1 - len];
            for (int k = h + 1; k <= h + len; k += 2) swap (s[k], s[k + 1]);
            ans[id[2 * cnt]] = divide (1, n, i, h).mx;
        }
    }
    int now = 0;
    q = read ();
    while (q--)
    {
        int k = read ();
        now ^= (1 << k);
        printf ("%lld\n", ans[now]);
    }
    return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：3)

看不懂别人的题解，所以自己写一篇。本题解主要是解释操作 $1$ 而不是教你最大子段和怎么求的，谢谢。

我们来观察一下操作的性质。如果你对反复出现的 $2^k$ 足够敏感，应该能意识到这玩意应该长得有点像线段树。但是如果你像我一样看半天看不懂，我就给你做一个演示

一次可能的交换如下，当 $k = 1$，原数列为 $(1,2,3,4,5,6,7,8)$ 的时候：

$$
\color{red}{(1,2),(3,4)} \color{black}{,} \color{blue}{(5,6),(7,8)} \color{black}{\longrightarrow} \color{red}{(3,4), (1,2)}\color{black}{,} \color{blue}{(7,8), (5,6)}
$$

这就显然了，直接把原数列分为几个长为 $2^{k+1}$ 的小块然后左右交换即可。

那么，手玩一下得到如下两条性质：

1. 如果两次 $k$ 是一样的，相当于没有做；
2. 操作的顺序是可以互换的。感性理解一下，把每个块想象成一个“包”，那么对于大“包”的操作，他不会修改小“包”的值，自然顺序是可交换的。

第一条性质很容易让你想到异或操作，好巧不巧你又看了一眼 $n$ 的范围实在小的可怜，干脆就全部搞出来！

因此，我们可以用 $g$ 来记录当前状态，根据交换的不同，数组共有 $2^n$ 种状态。

每当执行一次 $k$ 的查询，就令 $g\leftarrow g \otimes 2^k$（异或），是不是有一点状态压缩的味道？

现在我们需要对于每一个 $g\in (0, 2^{n}]$，求出对应的答案。

接下来就是求最大子段和的内容了，本篇题解的重点不在这里，仅做一点提示：把一个大区间分为两个小区间，分类讨论最大子段和在一个区间内还是横跨分界线，如此递归处理下去即可。

到此，本题结束。

---

## 作者：MadokaKaname (赞：1)

## 闲话
我和 @AcaCaca_ duel，然后我写了如下的神奇做法，然后 vector 疯狂 CE，爆了。

为什么没人像我这样做啊喂！~~看来还是我太菜了~~

[博客园](https://www.cnblogs.com/monster-hunter/p/18168137)

## 题解

首先众所周知的，序列最大子段和可以用 $\max +$ 矩阵来做。

考虑一个翻转，其实就是在从下往上递归中某一层所有相邻的两个矩阵进行了交换，换句话说，从左乘右变成了右乘左。

从下往上第 $i$ 层有 $2^{i-1}$ 种状态，$2^{n-i+1}$ 个矩阵，所以时空复杂度都是 $O(n2^n)$ 的。

屎山代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
struct matrix{
	LL a[3][3];
};
matrix operator*(const matrix &x,const matrix &y){
	matrix z;
	memset(z.a,-0x7f,sizeof(z.a));
	for(LL i=0;i<=2;i++){
		for(LL j=0;j<=2;j++)
		  for(LL k=0;k<=2;k++)
		   z.a[i][j]=max(z.a[i][j],x.a[i][k]+y.a[k][j]);
	}
	return z;
}
LL n,i,j,k,m,x;
LL stat=0;
LL b[500005];
const LL inf=0x7fffffffffff;
vector<vector<matrix> > v[19];
vector<matrix> v1;
int main(){
	scanf("%lld",&n);
	for(i=0;i<(1<<n);i++){
		scanf("%lld",&b[i]);
	}
	for(i=0;i<(1<<n);i++){
		matrix tmp;
		tmp.a[0][0]=0,tmp.a[0][1]=b[i],tmp.a[0][2]=b[i],tmp.a[1][0]=-inf,tmp.a[1][1]=b[i],tmp.a[1][2]=b[i],tmp.a[2][0]=-inf,tmp.a[2][1]=-inf,tmp.a[2][2]=0;
		v1.push_back(tmp);
	} 
	v[0].push_back(v1);
	for(i=1;i<=n;i++){
		for(j=0;j<(1<<i);j++){
			v1.clear();
			if((j&(1<<(i-1)))>0){
				for(k=0;k<(1<<(n-i));k++){
					v1.push_back(v[i-1][j^(1<<(i-1))][k*2+1]*v[i-1][j^(1<<(i-1))][k*2]);
				}
				v[i].push_back(v1);
			}
			else{
				for(k=0;k<(1<<(n-i));k++)
				  v1.push_back(v[i-1][j][k*2]*v[i-1][j][k*2+1]);
				v[i].push_back(v1);
			}
		}
	}
	scanf("%lld",&m);
	for(i=1;i<=m;i++){
		scanf("%lld",&x);
		stat^=(1<<x);
		printf("%lld\n",max(0ll,max(v[n][stat][0].a[0][1],v[n][stat][0].a[0][2])));
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

首先可以发现，如果没有修改，这就是一个全局最大子段和问题，我们考虑使用分治来解决。这边只要维护下列几个半群信息即可 $(\texttt{lmx,rmx,mx,sum})$。

有修改你发现其实就是交换线段树的左右儿子，这也很好做，随便 pushup 一下就做完了。

交换两次同一个 $x$ 是无用的，所以我们记录当前反转了奇数次的位，其实本质不同的询问就只有 $2^n$ 个了，因此全部预处理掉即可。

---

## 作者：Phartial (赞：0)

给一个很短的做法。

首先题目给的那个操作等价于交换所有的 $a_i$ 和 $a_{i\oplus 2^k}$，注意到 $a$ 只会有 $2^n$ 种不同的状态，考虑把所有状态下的信息记录下来。

最大子段和怎么求，考虑递归到左右两半再合并上来对不对，注意到递归下去后修改的最高位体现为了左右两半是否交换，因此这两半各自只有 $2^{n-1}$ 种修改。

继续递归下去，可以发现每一层总共只有 $2^n$ 种修改，因此总共只有 $n 2^n$ 个状态要记录，从下往上合并，对每种状态求出最大子段和即可。

那怎么写短一点呢，你发现如果用堆式存储，可以把每个区间的编号和修改拼起来存，这样有个好处是合并的形式变得特别简单，具体可以看代码。

时间复杂度 $\Theta(n 2^n+q)$。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int kN = 19;

struct I {
  ll s, ls, ms, rs;

  I(int v = 0) : s(v), ms(max(0, v)), ls(max(0, v)), rs(max(0, v)) {}
  I operator+(const I &o) const {
    I b;
    b.s = s + o.s;
    b.ls = max(ls, s + o.ls), b.rs = max(o.rs, o.s + rs);
    b.ms = max({ms, o.ms, rs + o.ls});
    return b;
  }
} f[kN][1 << kN];
int n, q;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (int i = 0, v; i < (1 << n); ++i) {
    cin >> v;
    f[n][i] = v;
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < (1 << n); ++j) {
      f[i][j] = f[i + 1][j] + f[i + 1][j ^ (1 << n - 1 - i)];
    }
  }
  cin >> q;
  for (int x = 0, k; q--; ) {
    cin >> k, x ^= (1 << k);
    cout << f[0][x].ms << '\n';
  }
  return 0;
}
```

---

## 作者：TanX_1e18 (赞：0)

首先把下标改成从 $0$ 开始编号。

于是一次修改就是交换 $a_i$ 和 $a_{i\oplus 2^{k-1}}$。

对于一个长度为 $2^k$ 的序列，所有可能的情况只有 $2^k$ 种。

这启发我们进行分块。

把每 $2^m$ 个位置分为一块，对于每一块，求出所有情况下的答案，此处复杂度 $O(2^{n-m+2m})$。

查询答案时把这 $2^{n-m}$ 块，每一块看成一个位置，求一遍答案，此处复杂度 $O(2^{n-m})$。

然后每次修改，如果 $k<m$，则修改每一小块的答案，如果 $k\ge m$，则修改块之间的顺序。

修改完之后查询即可。

预处理复杂度为 $O(2^{n+m})$，查询复杂度为 $O(2^{n-m}q)$，由于本题 $q$ 与 $2^n$ 同阶，所以取 $m=\frac{n}{2}$，复杂度为 $O(2^{1.5n})$。

由于查询常数较大，所以把 $m$ 适当上调会快一点。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1<<18;
int a[N];
const int M=1<<10;
int L[M][M],R[M][M],val[M][M],sum[M];
struct Node
{
	int l,r,val,sum;
	friend Node operator+(Node x,Node y)
	{
		Node z;
		z.val=max(x.val,y.val);
		z.sum=x.sum+y.sum;
		z.val=max(z.val,y.l+x.r);
		z.l=max(x.l,x.sum+y.l);
		z.r=max(y.r,y.sum+x.r);
		return z;
	}
}d[M<<3];
Node b[M];
void pushup(int p)
{
	d[p]=d[p<<1]+d[p<<1|1];
}
void build(int p,int l,int r)
{
	if(l==r)
	{
		d[p]=b[l];
		return;
	}
	int mid=(l+r)/2;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
int p[N];
int now;
int n,m;
void rebuild()
{
	for(int i=0;i<(1<<(n-m));i++)
	{
		b[i]={L[p[i]][now],R[p[i]][now],val[p[i]][now],sum[p[i]]};
	}
	build(1,0,(1<<(n-m))-1);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0;i<(1<<n);i++)
	cin>>a[i];
	m=n/2;
	if(n==18)
	m=10;
	for(int i=0;i<(1<<n);i+=(1<<m))
	{
		int id=i/(1<<m);
		for(int j=0;j<(1<<m);j++)
		{
			for(int k=0;k<(1<<m);k++)
			{
				int p=(i+k)^j;
				b[k]={a[p],a[p],a[p],a[p]};
			}
			build(1,0,(1<<m)-1);
			L[id][j]=d[1].l;
			R[id][j]=d[1].r;
			val[id][j]=d[1].val;
			sum[id]=d[1].sum;
		}
	}
	for(int i=0;i<(1<<(n-m));i++)
	p[i]=i;
	now=0;
	int q;
	cin>>q;
	while(q--)
	{
		int k;
		cin>>k;
		if(k<m)
		{
			now^=1<<k;
			rebuild();
		}
		else
		{
			k-=m;
			k=1<<k;
			for(int i=0;i<(1<<(n-m));i++)
			{
				if(i&k)
				swap(p[i],p[i^k]);
			}
			rebuild();
		}
		cout<<max(d[1].val,0ll)<<'\n';
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

交换操作实质上是将序列分为长为 $2^k$ 的若干段，交换每个奇数段与其后第一个偶数段。

容易发现对同一个 $k$，交换两次会抵消，所以可能的状态总数为 $2^n$，考虑预处理这些状态。

仍然考虑线段树求区间 GSS，为了方便地表示交换操作，使用 zkw 线段树。这样每个交换操作可以视为交换子树。

暴力处理时间复杂度 $O(n 2^{2n})$，无法通过。

但是暴力修改时有很多无用的更新，设每次修改了线段树上第 $k$ 层，则只需更新前 $k$ 层的线段树，这在 zkw 上是容易实现的。时间复杂度 $O(n 2^n)$，可以通过。

```cpp
#include <iostream>

#define int long long

using namespace std;

const int lim = 1e6;

int pw[20];
int lg[lim + 5];

int n, q;
int ans[1000005];

static inline int lowbit(int x) { return x & (-x); }

namespace zkw {
struct node {
    int sum, pre, suf, gss;
    node() {}
    node(int x) : sum(x) { pre = suf = gss = max(x, 0ll); }
    node(int _sum, int _pre, int _suf, int _gss)
        : sum(_sum), pre(_pre), suf(_suf), gss(_gss) {}
    node(const node &nd) : sum(nd.sum), pre(nd.pre), suf(nd.suf), gss(nd.gss) {}
    ~node() {}
    inline node operator+(const node &nd) const {
        return {
            sum + nd.sum,
            max(pre, sum + nd.pre),
            max(nd.suf, suf + nd.sum),
            max(max(gss, nd.gss), suf + nd.pre),
        };
    }
} d[4000005];
static inline void pushup(int p, bool rev = false) {
    if (rev)
        d[p] = d[p << 1 | 1] + d[p << 1];
    else
        d[p] = d[p << 1] + d[p << 1 | 1];
}
static inline void build() {
    for (int i = pw[n]; i < pw[n + 1]; ++i) {
        int x;
        cin >> x;
        d[i] = node(x);
    }
    for (int i = pw[n] - 1; i; --i)
        pushup(i);
}
} // namespace zkw

static inline void solve() {
    cin >> n;
    zkw::build();
    ans[0] = zkw::d[1].gss;
    int mx = 1 << n;
    for (int cur = 1; cur < mx; ++cur) {
        for (int i = pw[lg[lowbit(cur)] + 1] - 1; i; --i)
            zkw::pushup(i, cur & (1 << lg[i]));
        ans[cur] = zkw::d[1].gss;
    }
    int cur = 0;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cur ^= 1 << (n - x - 1);
        cout << ans[cur] << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    pw[0] = 1;
    for (int i = 1; i < 20; ++i)
        pw[i] = pw[i - 1] << 1;
    for (int i = 2; i <= lim; ++i)
        lg[i] = lg[i >> 1] + 1;
    solve();
    return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

## 题意

给出一个长为 $2^n$ 的序列，$q$ 次操作，每次操作 swap 线段树某一层所有节点的左右儿子，并求最大子段和。

$n\le 18,q\le 2\times 10^5$。

## 做法

容易发现同一层如果交换两次则相当于不变。所以我们可以先对于每个操作求出其状态与初始状态相比都有哪些层翻转。

容易发现翻转的层越靠下则越麻烦，所以我们希望这些靠下的层翻转次数尽量少。

可以考虑把询问按状态排序，再每次处理相邻的，这样从下向上第 $x$ 层最多会变化 $2^{x}$ 次，而第 $x$ 层本身就需要 $2^{n-x}$ 次 pushup，$n$ 层的操作次数之和为 $O(n2^n)$，可以通过。

## 实现

```cpp
int n,q,w[270005];
pii st[200005];
struct node{ll q,h,d,s;
node operator+(const node&b)const{
	return{max(q,s+b.q),max(h+b.s,b.h),max({d,b.d,h+b.q}),s+b.s};}
}a[530005];
int ls[530005],rs[530005];
#define mid (l+r>>1)
void build(int p,int l,int r){
	if(l==r){
		a[p]={max(w[l],0),max(w[l],0),max(w[l],0),w[l]};
		return;
	}
	build(ls[p]=p<<1,l,mid),build(rs[p]=p<<1|1,mid+1,r);
	a[p]=a[ls[p]]+a[rs[p]];
}
void rvs(int p,int l,int r,int d,int sta){// 这里我直接把所有要翻转的层都记在一块了
	if((sta>>d)&1)swap(ls[p],rs[p]);
	if(sta>>d+1){
		rvs(ls[p],l,mid,d+1,sta);
		rvs(rs[p],mid+1,r,d+1,sta);
	}
	a[p]=a[ls[p]]+a[rs[p]];
}
ll ans[200005];

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1;i<=(1<<n);i++)cin>>w[i];
	cin>>q;
	for(int i=1,x;i<=q;i++){
		cin>>x;
		st[i].fi=st[i-1].fi^(1<<n-x);// 倒过来存方便直接排序和递归
		st[i].se=i;
	}
	build(1,1,1<<n);
	sort(st+1,st+q+1);
	for(int i=1;i<=q;i++){
		int df=st[i].fi^st[i-1].fi;
		rvs(1,1,1<<n,1,df);
		ans[st[i].se]=a[1].d;
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：nullqtr_pwp (赞：0)

#### 【题目描述】

你有一个长度是 $2^n$ 的序列 $a$ , 下标从 $1$ 到 $2^n$ . ( $n \le 18$ , $-10^9 \le a_i \le 10^9$ ) .

你需要对这个序列进行 $q$ ( $q \le 2 \times 10^5$ ) 次操作 , 每次操作你都会得到一个整数 $k$ ( $0 \le k \le n-1$ ) . 你需要进行如下操作 :

- 对于 $\forall i \in [1,2^n-2^k]$，如果 $a_i$ 在本次操作中已经被交换过了，那么忽略它 ; 否则 , 将 $a_i$ 和 $a_{i+2^k}$ 进行交换 .
- 在这之后 , 输出序列最大子段和 . 本题中 , 最大子段**可以一个数都不选** .

注意 , 每次操作之后不会撤销 .
#### 【题目解答】

考虑对所有情况进行预处理，一共只有 $2^n$ 种。这是因为顺序无影响，相同操作会抵消。

这种问题常常要简化操作。我们考察一个操作对序列会带来什么影响。设一个长为 $2^x$ 的区间是对集合 $S$ 中的操作。我们设 $T$ 是 $2^{S_i}$ 的和，那么产生的新序列，就是原来位置 $i$ 的会变换到 $i\oplus T$ 上。

总长度是 $2^n$，我们考虑在分治树任意上一个长为 $[l,r]$ 的区间维护所有集合 $S$ 变换后的答案。那么在这样的区间上，我们需要维护 $r-l+1$ 个信息。这是因为在区间上合法的 $T$ 就是 $[0,r-l+1)$。

接下来设 $([l,r],T)$ 表示区间 $[l,r]$ 变换 $T$ 的新序列。 

我们可以考虑合并信息，像线段树一样 ```pushup```。考虑 $[l,r]$ 的所有答案怎么从 $[l,mid]$ 的已知信息以及 $[mid+1,r]$ 的已知信息推断。令 $k=r-l+1,p=\dfrac{k}{2}$。一方面 $T<p$ 的序列是：

$$([l,r],T)=([l,mid],T)+([mid,r],T)$$

另一方面，$k>T\ge p$ 的序列是：

$$([l,r],T)=([mid+1,r],T-p)+([l,mid],T-p)$$

可以通过维护每一种变换后序列的**最大子段和，区间总和，最大前缀和，最大后缀和**进行维护最大子段和。

总时间复杂度等于分治树所有节点的长度之和。时间复杂度 $O(2^nn+q)$，因为预处理后可以 $O(1)$ 查询。

#### 【参考代码】
```cpp
// Problem: Swap and Maximum Block
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1716E
// Memory Limit: 500 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=300005;
int a[maxn],m,n;
ll ans[maxn];
void chkmax(ll &x,ll y){
	x=max(x,y);
}
namespace seg{
	#define ls (o<<1)
	#define rs (o<<1|1)
	ll sum[maxn<<2];
	vector<ll>lmx[maxn<<2],rmx[maxn<<2],t[maxn<<2];
	void pushup(int o,int l,int r){
		sum[o]=sum[ls]+sum[rs];
		int len=r-l+1,tt=len>>1,mid=(l+r)>>1;
		F(i,0,len-1) t[o][i]=lmx[o][i]=rmx[o][i]=0;
		F(i,0,tt-1){
			chkmax(lmx[o][i],sum[ls]+lmx[rs][i]);
			chkmax(lmx[o][i],lmx[ls][i]);
			chkmax(rmx[o][i],sum[rs]+rmx[ls][i]);
			chkmax(rmx[o][i],rmx[rs][i]);
			chkmax(t[o][i],lmx[o][i]);
			chkmax(t[o][i],rmx[o][i]);
			chkmax(t[o][i],t[ls][i]);
			chkmax(t[o][i],t[rs][i]);
			chkmax(t[o][i],rmx[ls][i]+lmx[rs][i]);
		}
		F(i,tt,len-1){
			chkmax(lmx[o][i],sum[rs]+lmx[ls][i-tt]);
			chkmax(lmx[o][i],lmx[rs][i-tt]);
			chkmax(rmx[o][i],sum[ls]+rmx[rs][i-tt]);
			chkmax(rmx[o][i],rmx[ls][i-tt]);
			chkmax(t[o][i],lmx[o][i]);
			chkmax(t[o][i],rmx[o][i]);
			chkmax(t[o][i],t[ls][i-tt]);
			chkmax(t[o][i],t[rs][i-tt]);
			chkmax(t[o][i],lmx[ls][i-tt]+rmx[rs][i-tt]);
		}
	}
	void build(int o,int l,int r){
		int len=(r-l+1);
		t[o].resize(len),lmx[o].resize(len),rmx[o].resize(len);
		if(l==r){
			int x=a[l];
			sum[o]=x;
			if(x>=0) t[o][0]=lmx[o][0]=rmx[o][0]=x;
			else t[o][0]=lmx[o][0]=rmx[o][0]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(o,l,r);
	}
	void init(){
		build(1,0,m-1);
		F(i,0,m-1) ans[i]=t[1][i];
	}
}
signed main(){
	n=read(),m=(1<<n);
	F(i,0,m-1) a[i]=read();
	seg::init();
	int lzm=read(),cur=0;
	wh(lzm){
		int k=read();
		cur^=(1<<k);
		printf("%lld\n",ans[cur]);
	}
}
```

---

