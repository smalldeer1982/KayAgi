# Not Same

## 题目描述

给定一个整数数组 $a_1, a_2, \dots, a_n$，其中 $a_i$ 表示第 $i$ 个位置上的方块数量。保证 $1 \le a_i \le n$。

每次操作，你可以选择数组中的一个下标子集，并在这些下标对应的位置各移除一个方块。不能在没有方块的位置移除方块。

你每次选择的子集必须互不相同（唯一）。

你需要在最多 $n+1$ 次操作内移除数组中的所有方块。可以证明答案一定存在。

## 说明/提示

在第一个样例中，方块数量的变化如下：

$\lbrace 5,5,5,5,5 \rbrace \to \lbrace 4,4,4,4,4 \rbrace \to \lbrace 4,3,3,3,3 \rbrace \to \lbrace 3,3,2,2,2 \rbrace \to \lbrace 2,2,2,1,1 \rbrace \to \lbrace 1,1,1,1,0 \rbrace \to \lbrace 0,0,0,0,0 \rbrace$。可以注意到每次操作都是不同的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
5 5 5 5 5
```

### 输出

```
6
11111
01111
10111
11011
11101
11110
```

## 样例 #2

### 输入

```
5
5 1 1 1 1
```

### 输出

```
5
11000
10000
10100
10010
10001
```

## 样例 #3

### 输入

```
5
4 1 5 3 4
```

### 输出

```
5
11111
10111
10101
00111
10100
```

# 题解

## 作者：qwaszx (赞：8)

构造.证了半天，好丢人啊

可以发现等价于构造一个 $n+1$ 行 $n$ 列的 $01$ 矩阵使得每列的 $1$ 的个数为某个 $1$ 到 $n$ 的数.

那么瞎猜一个构造，然后尝试~~对拍~~证明.

首先因为列置换后答案不变，所以可以对 $a$ 排个序方便处理.猜一个构造是从小到大排序，然后对于第 $i$ 个列，从第 $i$ 行开始往下填 $a_i$ 个数，如果超过 $n+1$ 行就回到第一行循环填. 发现这个东西会被第三个样例叉掉，于是尝试换成从大到小排序，然后就过了.

为什么呢？假设这样构造存在 $i<j$ 使得第 $i$ 行和第 $j$ 行完全一致，用 $(x,y)$ 表示第 $x$ 行第 $y$ 列填的数，因为 $a$ 都小于等于 $n$ 所以显然有 $(i,i+1)=0$，因为两行完全一致所以有 $(j,i+1)$ 也为 $0$.而对于第 $i+2$ 列，因为 $a_{i+2}\leq a_{i+1}$ 所以这一列的最下面的 $1$ 只能在第 $j$ 行或其上面，又因为完全一致所以不能在第 $j$ 行，类似地可以得到第 $i+1$ 到 $j-1$ 列的第 $j$ 行都为 $0$，这就给出 $a_{j-1}=1$，于是 $a_j=1$，然而因为完全一致所以 $(i,j)$ 应该等于 $1$，这就给出 $a_j>1$，矛盾.所以这样构造是正确的.可以画个图感受一下:

![](https://cdn.luogu.com.cn/upload/image_hosting/zp2heyur.png)

(竖线是连续的 $1$)

代码非常好写

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2005;
int id[N],w[N],a[N][N],n,nid[N];
int cmp(const int &a,const int &b){return w[a]>w[b];}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",w+i),id[i]=i;
    sort(id+1,id+n+1,cmp);for(int i=1;i<=n;i++)nid[id[i]]=i;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=w[id[i]];j++)a[(j+i-1)>n+1?j+i-1-n-1:j+i-1][i]=1;
    }
    cout<<n+1<<endl;
    for(int i=1;i<=n+1;i++,puts(""))
        for(int j=1;j<=n;j++)
            putchar(a[i][nid[j]]+48);
}
```

---

## 作者：RedreamMer (赞：7)

[$\Large\texttt{CF1227G Not Same
}$](https://www.luogu.com.cn/problem/CF1227G)

[$\texttt{My cnblogs}$](https://www.cnblogs.com/RedreamMer/p/15007913.html)

标签：构造

~~疑似水2600？~~

## 题意

给定大小为 $n$ 的序列 $a$ , 满足 $1 \le a_i \le n$

你需要执行至多 $n+1$ 次操作使得所有数变为 $0$，每次操作你可以把一个子集的元素都 $-1$，要求每次操作的子集互不相同。

$n \le 1000$

## 思路

好像和题解区的构造方法都不太相同，但是很好理解。

首先假设最后序列有 $n + 1$ 个。

因为最后的操作序列没有两两相同，我们从序列的角度来看，一开始是都相同的，我们认为它们都是在同一个集合中。

（以下“序列”即为集合中的元素）

操作即为每次由第 $i$ 个数字 $a_i$，给 $a_i$ 个序列的末尾加上 $1$，并给剩下 $n + 1 - a_i$ 个序列末尾加上 $0$，注意到这一步可以使一些相同的序列变得不同，即使同一个集合中的元素通过在末尾添加了不同的 bit 变成了不相同，这时候就可以把加不同 bit 的这些元素拉出来变成一个新的集合（比如加 $0$ 的不动，放 $1$ 的新拉出来一个集合）。

然后我们注意到 $1 \le a_i \le n$ 这说明每个 $a_i$ 对序列的操作至少有一个 $0$，至少有一个 $1$。

也就是说每个数如果操作分配的好，一定至少有一个集合大小 $\ge 2$ 的集合可以被分成两份，又因为初始集合大小为 $n + 1$ 分 $n$ 次一定分得 $n + 1$ 个不同的集合。

## 代码

```cpp
int a, s[N + 5], ans[N + 5][N + 5], top = 1;
vector<int> q[N + 5];

void add(int n, int j) {
    rep(i, 0, siz(q[n]) - 1) ans[q[n][i]][j] = 1;
}

void divide(int n, int p0, int p1, int j) {
    ++top;
    rep(i, 1, p0) q[top].PB(q[n][siz(q[n]) - 1]), q[n].pop_back();
    add(n, j);
}

signed main() {
    // freopen("in1.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    a = read();
    rep(i, 1, a) s[i] = read(), q[1].PB(i);
    q[1].PB(a + 1);
    rep(i, 1, a) {
        int p0 = a + 1 - s[i], p1 = s[i];
        int _top = top;
        rep(j, 1, _top) {
            if (siz(q[j]) == 1) {
                if (p1 > p0) add(j, i), --p1;
                else --p0;
            }
            else if (!p0) {
                p1 -= siz(q[j]);
                add(j, i);
            }
            else if (!p1) p0 -= siz(q[j]);
            else {
                int q0 = min(p0, siz(q[j]) - 1), q1 = siz(q[j]) - q0;
                divide(j, q0, q1, i);
                p0 -= q0;
                p1 -= q1;
            }
        }
    }
    printf("%d\n", a + 1);
    for (int i = 1; i <= a + 1; ++i, puts("")) rep(j, 1, a) printf("%d", ans[i][j]);
    return 0;
}
```

---

## 作者：duyi (赞：6)

# CF1261E Not Same

[题目链接](https://codeforces.com/contest/1261/problem/E)

---

把问题稍微转化一下，变成要求构造一个 $n+1$ 行 $n$ 列的 $01$ 矩阵，每一列的和给定，并且要求任意两行互不相同。

记 $b(i, j)$ 表示答案矩阵第 $i$ 行第 $j$ 列上的数。

---

**法一**：

> 首先将所有数**从大到小**排好序。
>
> 对第 $i$ 个数，相当于要在第 $i$ 列填 $a_i$ 个 $1$。我们从第 $i$ 行开始向下走，依次把经过的前 $a_i$ 个格子填上 $1$（如果到底了就返回第 $1$ 行）。

下面证明这种做法的正确性。

> 首先，如果我们对排好序的 $a$ 序列构造出答案后，再把答案的矩阵列按照原顺序交换，显然结果仍是正确的。故以下讨论的 $b$ 矩阵，均为对排好序的 $a$ 序列构造的答案。
>
> 我们要证明，按上述方法构造出的 $b$ 矩阵，不存在完全相同的两行。
>
> 反证法：考虑两行 $i, j$ （$i < j$），假设这两行相同。
>
> 简单分类讨论一下：
>
> - 情况一：$1\leq i < j\leq n$。
>
> 因为 $a_{i + 1}\leq n$，所以 $b(i, i + 1) = 0$。又因为第 $i$ 行与第 $j$ 行相同，所以 $b(j, i + 1) = 0$。所以 $a_{i + 1}\leq j - i - 1$。
>
> 如果 $i + 2\leq j$，考虑第 $i + 2$ 列。要么 $b(i,i + 2) = b(j, i + 2) = 1$，要么 $b(i, i + 2) = b(j, i + 2) = 0$。如果 $b(i,i + 2) = b(j, i + 2) = 1$，那么 $a_{i + 2}\geq j - i + 1$。然而，由于 $a_{i + 2}\leq a_{i + 1}\leq j - i - 1$，所以这种情况不存在，所以只可能 $b(i, i + 2) = b(j, i + 2) = 0$。所以 $a_{i + 2}\leq j - i - 2$。
>
> 同理，可以推出，$\forall k \in[1, j - i]:a_{i + k}\leq j - i - k$。所以 $a_{j}\leq 0$。与题意矛盾。
>
> - 情况二：$1\leq i\leq n$，$j = n + 1$。
>
> 因为 $a_{i}\geq 1$，所以 $b(i, i) = 1$。又因为第 $i$ 行与第 $j = n + 1$ 行相同，所以 $b(n + 1, i) = 1$。所以 $a_{i}\geq n + 2 - i\geq 2$。
>
> 如果 $i > 1$，考虑第 $i - 1$ 列。因为 $a_{i}\geq 2$，所以 $a_{i - 1}\geq a_{i}\geq 2$。所以 $b(i, i - 1) = 1$。所以 $b(n + 1, i - 1) = 1$。所以 $a_{i - 1}\geq n + 3 - i$。
>
> 同理，可以推出，$\forall k \in[0, i - 1]: a_{i - k} \geq n + k + 2 - i$。所以 $a_{1} \geq n + 1$，与题意矛盾。

顺便一提，我们原本的想法是把 $a$ 序列按**从小到大**排序。这样也能得到一个“似乎正确”的做法。但是该做法可能导致第 $n$ 行和第 $n + 1$ 行相同。这给我们的启示是：

1. 在证明时，注意考虑 $i\leq n$，$j = n + 1$ 的特殊情况，是至关重要的。
2. 如果从小到大排序不行，可以尝试反过来。

[参考代码-在CF查看](https://codeforces.com/contest/1261/submission/107536774)

---

**法二**：

> 不需要排序。
>
> 我们从 $1$ 到 $n$，依次考虑每一列。
>
> 假设当前考虑到底 $i$ 列，我们看看前 $i - 1$ 列里（$(n + 1)\times(i - 1)$ 的矩阵里）有哪些相同的行（初始时所有行都是相同的）。
>
> - 如果没有相同的行，那么后面无论怎么填，都不会再出现相同的行。所以可以随便填。
> - 否则找出相同的两行 $r_1, r_2$，令 $b(r_1, i) = 1$，$b(r_2, i) = 0$。剩下的 $a_i - 1$ 个 $1$ 随便填。

下面证明这种做法的正确性。

> 把相同的行视为一组，记录每组的大小，得到一个可重集。
>
> 例如，初始时所有行都是相同的，那么可重集就是 $\{n + 1\}$。加入了 $a_1$ 后，可重集变成：$\{a_1, n + 1 - a_1\}$。
>
> 如果所有行都不同，那么可重集是 $\{1, 1, \dots, 1\}$（$n + 1$ 个 $1$）。
>
> 否则我们每次操作的效果，相当于至少会拆掉可重集里的一个 $> 1$ 的数。即，从可重集里选择一个 $x > 1$，删掉它，再加入两个数 $x_1, x_2$，满足 $x_1 + x_2 = x$，$x_1, x_2 > 0$。
>
> 原可重集 $\{n + 1\}$，在变为 $\{1, 1, \dots, 1\}$ 前，**最多**可以被操作 $n$ 次。
>
> 所以经过 $n$ 次操作后，可重集一定会变为 $\{1, 1, \dots, 1\}$，即所有行都不相同。

朴素实现是 $\mathcal{O}(n^4)$ 的（即每次暴力枚举两行，再暴力判断它们是否相同）。

对行哈希，用哈希来判断是否相同，可以做到 $\mathcal{O}(n^2\log n)$ 或者 $\mathcal{O}(n^2)$。

[参考代码-在CF查看](https://codeforces.com/contest/1261/submission/107588423)




---

## 作者：AxDea (赞：3)

提供一个没脑子做法。

将构造方案看成 $op$ 行 $n$ 列点矩阵。

考虑一列一列构造，把前面的矩阵横向分成 $k$ 个连续联通块，每一个联通块表示这一个联通块内的所有行都是相同的，而且不存在一个在这个联通块外还与这个连通块内部的行相同的行。

为了满足这个条件那么在填新的一行的时候，在每一个前面矩阵对应的连通块上，$0$ 和 $1$ 必须连续填，这样可以保证每种相同的串都是连续的。

发现每一列对于前面的矩阵的一条连通块来说，只要在新的一列中有两个数字 $0$ 和 $1$ 存在就可以增加一个连通块，说明每次能增加最多 $\min\{a_i, op - a_i\}$ 个联通块，由于 $op = n + 1$ 时增加次数最少也有 $n$ 个了，所以这也证明了答案为什么一定存在。

然后直接模拟即可。

```cpp
#include <bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s); i<=(t); ++i)
#define form(i,s,t) for(register int i=(s); i>=(t); --i)
#define rep(i,s,t) for(register int i=(s); i<(t); ++i)
using namespace std;
const int N = 1e3 + 4;
int n, a[N], op, num, res, ret[N][N], b[N][N];
int main() {
	scanf("%d", &n);
	if(n == 1) return puts("1\n1"), 0;
	forn(i,1,n) scanf("%d", a + i), res += min(a[i], n - a[i]);
	op = n + 1;
	forn(i,1,op) b[0][i] = 1; num = 1;
	forn(i,1,n) {
		static int rem, ink ;
		static basic_string<int> dan;
		dan.clear();
		if(a[i] < op - a[i]) rem = a[i], ink = 1;
		else rem = op - a[i], ink = 0;
		forn(l,1,op) ret[i][l] = !ink;
		forn(l,1,op) {
			int r = l;
			while(r < op && b[i - 1][l] == b[i - 1][r + 1]) ++r;
			if(l == r) {
				b[i][l] = b[i - 1][l], dan += l;
				continue ;
			} else {
				if(rem) {
					b[i][l] = ++num, rem -- , ret[i][l] = ink;
				} else b[i][l] = b[i - 1][l];
				forn(p,l + 1,r) b[i][p] = b[i - 1][p];
			}
			l = r;
		}
		if(rem) {
			forn(l,1,op) {
				int r = l;
				while(r < op && b[i - 1][l] == b[i - 1][r + 1]) ++r;
				if(l != r) {
					if(rem) {
						int it = l + 1;
						while(it != r && rem) 
							ret[i][it] = ink, b[i][it] = b[i][l], ++it, rem -- ;
					}
				} else if(rem) rem -- , ret[i][l] = ink;
				l = r;
			}
		}
	}
	printf("%d\n", op);
	forn(i,1,op) {forn(j,1,n) printf("%d", ret[j][i]); putchar('\n');}
	return 0;
}
```





---

## 作者：Presentation_Emitter (赞：2)

给个稍微不同的做法。

将所有 $a_i$ 从小到大排序，之后钦定 $(i+1,i)=0$（$(x,y)$ 指答案矩阵的第 $x$ 行 $y$ 列），然后：

- $a_i \le i$ 时，$\forall j \in [i-a_i+1,i],(j,i) \leftarrow 1$
- $a_i \gt i$ 时，$\forall j \in [1,i] \cup [i+2,a_i+1],(j,i) \leftarrow 1$

人话：从第 $i$ 行开始往上填 `1`，填不下了就从 $i+2$ 行往下填，总共填 $a_i$（排序后）个。

然后就做完了。

下面是感性理解：

对于一个子矩阵，若存在两行相同，则会出现类似下面的情况：

```
0 1 0
x 0 x
0 1 0
```

不难发现 $a_{i_2} \ge i_2+1,a_{i_3} \lt i_3=i_2+1$，即第二列对应的 $a$ 大于第三列，与 $a$ 的有序性矛盾。

Code:

```cpp
ll n,ans[1005][1007];pr a[1005];
il bool chk(int i){bool r=0;for(int j=1;j<=n;++j)r|=ans[i][j];ret r;}
int main()
{
	n=rd();for(int i=1;i<=n;++i)a[i]=prpr(rd(),i);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i)
	{
		int d=-1,cur=i+1;
		for(int j=1;j<=a[i].fir;++j)
		{
			cur+=d;if(cur<=0)cur=i+2,d=1;
			ans[cur][a[i].sec]=1;
		}
	}
	ll c=n+1;while(!chk(c))--c;
	prt(c);
	for(int i=1;i<=c;++i,pc('\n'))for(int j=1;j<=n;++j)prt(ans[i][j],0);
	ret 0;
}
```

---

## 作者：wind_whisper (赞：2)

## $\text{Description}$
给定大小为 $n$ 的序列 $a$，满足 $1 \leqslant a_i \leqslant n$.  

你需要执行至多 $n+1$ 次操作使得所有数变为 $0$，每次操作你可以把一个子集的元素都 $-1$，要求每次操作的子集互不相同.

$n\leqslant 1000$.
## $\text{Solution}$
把所有元素从大到小排序.  
排序后的第 $i$ 个元素从第 $i$ 行开始连续填，到头循环即可.  
为什么这样必然合法？  
首先不难发现，这样填完之后后一列最多比前一列的下部低一位.  
假设第 $i$ 行和第 $j$ 行完全相同. $(i<j)$  
那么由于第 $i$ 行的第 $i+1$ 列没有数，那么第 $j$ 行的第 $i+1$ 列也没有数.  
那么第 $i+2$ 列最多比 $i+1$ 列往下一行，不可能同时让第 $i$ 行和第 $j$ 行有数，也只能让两行都没有数.  
以此类推，最后到第 $j$ 列的时候，第 $j$ 行第 $j$ 列必然有数（元素为正数），但第 $i$ 行第 $j$ 列却没有数，矛盾.  
原命题得证.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1050;
const int mod=998244353;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
int a[N],x[N];
bool cmp(int x,int y){return a[x]>a[y];}
int ans[N][N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) a[i]=read(),x[i]=i;
  sort(x+1,x+1+n,cmp);
  for(int i=1;i<= n;i++){
    int now=x[i];
    for(int j=i;a[now];j=j%(n+1)+1) ans[j][now]=1,a[now]--;
  }
  printf("%d\n",n+1);
  for(int i=1;i<=n+1;i++){
    for(int j=1;j<=n;j++) printf("%d",ans[i][j]);
    putchar('\n');
  }
  return 0;
}
/*
*/

```


---

## 作者：Owen_codeisking (赞：2)

给出一个我自己都不会证的构造方法。

可以直观的想到：若我们每次取的集合都包含最小值且不相同，当最小值被删去后，再进入子问题，这样所有集合都不相同。

至多 $n+1$ 次操作，我们可以维护集合 $A$ 使得 $\max_A\le |A|+1$ 且取到上界最多一次。

这样可以分类讨论。

- 若 $\min A=\max A=|A|$，可以简单构造。
- 若 $\min A>1$，取当前没取过最小值的下标 $k$ （不包括最小值） 不选，其他值均选。
- 若 $\min A=1$，取当前没取过最小值的下标 $k$（不包括最小值） 不选，将一个 $1$ 和其他不为 $1$ 的数（除下标 $k$） $-1$。

可以看出，除了只有一种或两种本质不同的数的情况，最大值一定 $-1$。那么我们多选一次集合简单构造，使得 $\max A\le |A|$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n,a[maxn],tot;
vector<int> id;
char s[maxn][maxn];
inline int check()
{
	bool fl=0;
	vector<int> res; res.clear();
	for(auto x:id)
		if(a[x]>0) res.push_back(x);
		else fl=1;
	id=res;
	return fl;
}
inline bool cmp(const int &x,const int &y) { return a[x]<a[y]; }
inline void solve()
{
	if(check()) return;
	sort(id.begin(),id.end(),cmp);
	bool fl=0;
	if(a[id[0]]>1 || a[id.back()]==1)
	{
		tot++;
		for(int i=1;i<=n;i++) s[tot][i]='0';
		for(auto x:id) a[x]--,s[tot][x]='1';
		fl=1;
		if(check()) return;
	}
	if(a[id[0]]==a[id.back()] && a[id[0]]==(int)id.size()-1)
	{
		for(auto x:id)
		{
			tot++;
			for(int i=1;i<=n;i++) s[tot][i]='0';
			for(auto y:id)
				if(y!=x) a[y]--,s[tot][y]='1';
		}
		check(); return;
	}
	int k;
	for(k=1;k<(int)id.size();k++)
	{
		if(a[id[0]]==1) break;
		tot++;
		for(int i=1;i<=n;i++) s[tot][i]='0';
		for(auto y:id)
			if(y!=id[k]) a[y]--,s[tot][y]='1';
		if(check()) return;
	}
	tot++;
	for(int i=1;i<=n;i++) s[tot][i]='0';
	int y=(fl && a[id[k]]>1)?id[k]:0;
	for(auto x:id)
		if((x==id[0] || a[x]>1) && x!=y) a[x]--,s[tot][x]='1';
	check();
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),id.push_back(i);
	while(!id.empty()) solve();
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%s\n",s[i]+1);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

有些人就是没脑子，只能用蠢办法。

考虑归纳的构造，尝试将问题转化为 $n-1$ 的子问题，一种自然的思路就是删掉一个元素。

显然，假设剩下 $n-1$ 个数的答案集合是 $\{S_1,S_2,\cdots,S_t\}$，如果 $t \ge a_{del}$ 那么就可以通过在 $S_1$ 到 $S_{a_{del}}$ 后面加一个 $del$ 实现。

-----

显然我们最好找的是最小的 $a$ 作为 $a_{del}$。如果其他的数有等于 $n$ 的，我们就要先将其减一。

因此，我们可以将 $del$ 和所有 $a_i = n$ 的 $i$ 减去 $1$，放进集合 $S$ 中。递归解决子问题。

- 如果剩下数的最大值不是 $a_{del}$，那么子问题得到了至少 $a_{del}$ 个集合，必有 $a_{del}-1$ 个不为 $S / \{del\}$ 的集合，将他们后面填上 $S$ 即可。

- 否则，所有数全相等。这一部分甚至不用递归到子问题，直接手玩即可。（我递归到了子问题，不过略显麻烦）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e3+10,MOD=998244353;
int n,a[MAXN],tot,al[MAXN],hsh[MAXN],flg[MAXN][MAXN],pw[MAXN];
void solve(vector<int> vc) {
	if(vc.size()==1) return flg[++tot][vc[0]]=1,hsh[tot]=pw[vc[0]],void();
	pair<int,int> mn={n+1,0};
	int HASH=0;
	vector<int> critical;
	for(auto id:vc) mn=min(mn,{a[id],id});
	int id=mn.second;
	a[id]--;
	for(auto ID:vc) if(ID!=id&&a[ID]==vc.size()) critical.push_back(ID);
	for(auto ID:critical) HASH=(HASH+pw[ID])%MOD,a[ID]--;
	vector<int> rst;
	for(auto ID:vc) if(ID!=id) rst.push_back(ID);
	solve(rst);
	ffor(i,1,tot) if(a[id]&&hsh[i]!=HASH) a[id]--,flg[i][id]=1,hsh[i]=(hsh[i]+pw[id])%MOD;	
	++tot,flg[tot][id]=1,hsh[tot]=pw[id];
	for(auto ID:critical) flg[tot][ID]=1,hsh[tot]=(hsh[tot]+pw[ID])%MOD;
	if(a[id]) ++tot,flg[tot][id]=1,hsh[tot]=pw[id];
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=1;
	ffor(i,1,n) pw[i]=pw[i-1]*2%MOD;
	ffor(i,1,n) cin>>a[i];
	vector<int> vc;
	ffor(i,1,n) vc.push_back(i);
	solve(vc);
	cout<<tot<<'\n';
	ffor(i,1,tot) {
		ffor(j,1,n) cout<<flg[i][j];
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：断清秋 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1227G)

题意等价于构造一个 $n+1$ 行 $n$ 列的 $01$ 矩阵，使得每一行的内容都不同，且第 $i$ 列有 $a_i$ 个 $1$。

内容不同显然要考虑阶梯状排列，由于每一列至少会有一个 $0$，可以考虑摆放 $0$ 的位置。比较经典的一种：

```
10XXX
X10XX
XX10X
XXX10
XXXX1
0XXXX
```

这样相当于第 $i$ 个数填数就从第 $i$ 行开始填，如果下面填满了就回到第 $1$ 行循环填，设答案矩阵为 $b$，能够保证 $b_{i,i}=1,b_{i,i+1}=0$。

考虑列置换后并不影响答案的正确性，把 $a$ 先从大到小排序处理，然后按照上面的构造就行了。

证明：

考虑反证，假设有 $i,j(i<j)$ 两行内容相同，那么必然有 $b_{i,i+1}=b_{j,i+1}$。

假设对于 $i+1<x \le j$，存在 $b_{i,x}=1$，则有 $b_{j,x}=1$，且 $b_{i,i+1}\ldots b_{i,x-1}=b_{j,i+1} \ldots b_{j,x-1}=0$，但 $b_x \le b_i$，所以第 $x$ 列不可能在 $i,j$ 两行都放置 $1$，矛盾。

因此对于任意 $i+1<x \le j$，不存在 $b_{j,x}=1$，但这显然与 $b_{j,j}=1$ 矛盾，因此假设不成立，原构造合法。

---

## 作者：SFlyer (赞：0)

不会聪明方法，就用一个好像也较为好写的笨方法。

首先题目就是，一个 $(n+1)\times n$ 的 $01$ 矩阵，现在第 $i$ 列填 $a_i$ 个 $1$，要求没有长得相同相同的行。

一开始什么都没有填的时候 $n+1$ 行都是相同的，没有被区分开。考虑加入一个数 $a_i$ 的时候，把 $a_i$ 个地方改成 $1$，这样目前没有区分的两个集合分别有 $a_i,n+1-a_i$ 个行。

因此现在问题变成：你有初始一个集合 $\{1,2,\cdots ,n+1\}$，你每一次有一个数 $a_i$，可以在所有的集合中选一些数（总共选 $a_i$ 个），如果一个集合 $S$ 选的数个数 $c$ 满足 $0<c<|S|$，则 $S$ 集合分裂成大小为 $c$ 和 $|S|-c$ 的两个集合，要求 $n$ 次操作以后有 $n+1$ 个大小为 $1$ 的集合。

首先如果我们可以保证每一次产生一个“分裂”就足够了。因此现在变成对于一个操作构造一个“分裂”。一个贪心的想法是，集合大小从大到小选，这样有两种情况：

- 最后到了一个集合，只能选一部分，已经满足情况了。

- 刚好到一个集合选完。因为我们是从大到小排序的，所以如果还没有到“$n+1$ 个大小为 $1$ 的集合”，必定有最大集合大小 $\ge 2$。因此我们把选的数往右移动一格即可，也就是保证了最大的被切。

因此保证了至少“分裂”一次。其实可以合并两种情况，但是会产生“$a_i$ 小于最大集合大小”，不一定更好写。

时间复杂度 $\mathcal{O}(n^2\log n)$，因为要排序。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e3+3;

int n,a[N];
char b[N][N];

struct node {
	vector<int> id;
};
vector<node> v;
bool cmp(node a,node b){return a.id.size()>b.id.size();}

void spl(int num,int cnt){
	vector<node> w;
	for (int i=0; i<v.size(); i++){
		if (i!=num) w.push_back(v[i]);
		else{
			vector<int> a1,a2;
			for (int j=0; j<cnt; j++) a1.push_back(v[i].id[j]);
			for (int j=cnt; j<v[i].id.size(); j++) a2.push_back(v[i].id[j]);
			w.push_back(node{a1}),w.push_back(node{a2});
		} 
	}
	v=w;
}

void gd(int fr,int x,int l){
	int c=x,i;
	for (i=fr; i<v.size(); i++){
		if (c>=v[i].id.size()){
			for (auto u : v[i].id) b[u][l]='1';
			c-=v[i].id.size();
		}
		else break;
	}
	for (int j=0; j<c; j++) b[v[i].id[j]][l]='1';
	if (c) spl(i,c);
}

void cg(int x,int l){
	sort(v.begin(),v.end(),cmp);
	int c=x;
	for (auto u : v){
		if (c>=u.id.size()) c-=u.id.size();
		else break;
	}
	if (c==0){
		spl(0,1);
		gd(1,x,l);
	}
	else{
		gd(0,x,l);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n;
	for (int i=1; i<=n; i++) cin>>a[i];
	for (int i=1; i<=n+1; i++) for (int j=1; j<=n; j++) b[i][j]='0';
	vector<int> al;
	for (int i=1; i<=n+1; i++) al.push_back(i);
	v.push_back(node{al});
	for (int i=1; i<=n; i++){
		cg(a[i],i);
	}
	cout<<n+1<<"\n";
	for (int i=1; i<=n+1; i++){
		for (int j=1; j<=n; j++) cout<<b[i][j];
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：w9095 (赞：0)

[CF1227G Not Same](https://www.luogu.com.cn/problem/CF1227G)

构造。考虑按照每个数字进行考虑，每次填充一列。

观察样例 $1$，不难发现可以构造使每一行或列一定有一个位置为 $0$。我们不妨对于每一列限定这个 $0$ 的位置，使其与任意一个列的位置不一样。不难发现这样也保证了每一行 $0$ 位置的不同。然后，我们强制至少一个其他列在这个位置填上 $1$，即可保证每一行互不相同。

这是很好维护的。我们只需要对于第 $i$ 列，从第 $i$ 行开始往下顺着填。如果超出了 $n+1$ 行，就填到上面。为了满足至少一个其他列在这个位置填上 $1$，我们把原数组从大到小排序，手玩一下发现一定满足条件。这题就做完了。

时间复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct val
{
	long long v,p;
}a[2000];
long long n,y[2000],ans[2000][2000];
bool cmp(struct val a,struct val b)
{
	return a.v>b.v;
}

int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].v),a[i].p=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)y[a[i].p]=i;
	for(int i=1;i<=n;i++)
	    {
	    long long j=i;
	    while(a[i].v)
	       {
		   ans[j][i]=1,a[i].v--,j++;
		   if(j>n+1)j=1; 
	       }
	    }
	printf("%lld\n",n+1);
	for(int i=1;i<=n+1;i++)
	    {
	    for(int j=1;j<=n;j++)
	        printf("%lld",ans[i][y[j]]);
	    printf("\n");
	    }
	return 0;
}
```

---

## 作者：Sky_Maths (赞：0)

# 思路
观察题目，发现没有保证有解，也没有说不合法的输出，于是猜测在题目条件下必定存在合法解。
（就是填 $01$ 矩阵）

# 证明
对于 $1\le i\le n, 1\le a_i\le n$，必可用 $n$ 或 $n + 1$ 次使其全部变为 $0$。

考虑寻找不劣的方案，即尽量构造 $a_i = 1$ 的 $i$。

## 情况一
若 $\sum [a_i = 1] \ge n - 1$ 则可以简单构造，将 $n - 1$ 个 $a_i = 1$ 的 $i$ 分到 $n - 1$ 个里，则可以构造出 $n$ 个已经不同的操作子集（包括空集）。

然后因为 $\max{a_i}\le n$，剩下的一个直接分配即可。

## 情况二
那就是有至少两个 $i$ 使得 $a_i>1$，可以在未来的 $a_{mx}$ 次操作中都使 $a_{mx}$ 减 $1$，而当前这次操作只使所有 $a_i > 1$ 的 $a_i$ 减 $1$。

对于第 $cnt$ 次（当前这次）和 $cnt + mx + 1$ 相同：因为第 $cnt$ 次相当于一个“全集”（除 $a_{mx}$ 外，即当前的全集的“真子集”），子问题提供的全都是“全集”的“真子集”。

---

## 作者：Chthologist7507 (赞：0)

神仙构造题，先 % 一下 wzy 鸽鸽

首先我们可以手模一下

比如

```plain
5 5 4 3 1
4 4 4 3 1
3 3 3 3 1
2 2 2 2 1
1 1 1 1 0
0 1 1 1 0
0 0 0 0 0
```
或许会有一种感觉就是将大的数削平成小的数，然后再将它们再削平成更小的数，以此类推

或者说，从大到小排序，然后每次将 `1,1 2,1 2 3...` 削平

结合削平这个感觉，我们可以将其画成一张图来直观感受 ~~手模~~ 一下

![](https://cdn.luogu.com.cn/upload/image_hosting/nhqtyi3p.png)

~~图是 wzy 鸽鸽的，我盗来用了，因为真的很清晰~~

如果画出了这样的一张图，那么思路就很明晰了，题意即为构造一个 $n+1$ 行 $n$ 列的 $01$ 矩阵使得每列的染色方格的个数为某个 $1$ 到 $n$ 的数，最后一步是如何染色

答案是横着削，纵着染

具体的，对于 $a_i=j$，若 $j\leq n-i+1$，就从下往上依次染，否则先从下往上染满，然后跳到最底部从下往上染到 $j$ 个

[code](https://codeforces.com/contest/1227/submission/166907342)，构造题代码不难写，唯一比较坑的就在于要排完序输出时要还原一下

---

