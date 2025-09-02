# [Aboi Round 1] 私は雨

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/29ph2q84.png)

## 题目描述

给你一个长度为 $n$ 的序列 $\{a\}$，以及 $q$ 次询问。

询问形如 `l r L R p x`，表示询问有多少 $i \in [l,r]$ 且 $ a_i \in [L,R]$，$a_i$ 对 $p$ 取余的结果是 $x$。 

强制在线。

## 说明/提示

$$
\def\arraystretch{1.2}
\begin{array}{|c|c|c|c|}
\hline
\begin{array}{c}
\tt{subtask}\\\hline
1\\\hline
2\\\hline
3\\\hline
4\\\hline
\end{array}
&
\begin{array}{c}
n,q\\\hline
\le 5\times10^3\\\hline
\le 10^5\\\hline
\le 10^5\\\hline
\le 10^5 
\end{array}
&
\begin{array}{c}
\tt{\tt{特殊性质}}\\\hline
\tt{无}\\\hline
\tt{保证序列中元素 \le 2\times10^4}\\\hline
\tt{保证 \text{type}= 0 }\\\hline
\tt{无}\\\hline
\end{array}
&
\begin{array}{c}
\tt{pts}\\\hline
10\\\hline
30\\\hline
20\\\hline
40\\\hline
\end{array}
\\\hline
\end{array}
$$



对于所有数据，$1 \le n \le 10^5$，$1 \le q \le 10^5$，$1 \le a_i \le 2\times10^5$，$1 \le l \le r \le n$，$1 \le L \le R \le 2 \times 10^5$，$0 \le x < p \le 2 \times 10^5$，$\text{type} \in \{0,1 \}$。

所有输入均为非负整数。


## 样例 #1

### 输入

```
6 0
1 1 4 5 1 4
3
1 6 1 6 2 0
2 3 1 6 3 1
2 5 2 5 4 1```

### 输出

```
2
2
1```

## 样例 #2

### 输入

```
见附件中的 rvmq_sample2.in。```

### 输出

```
见附件中的 rvmq_sample2.out。```

# 题解

## 作者：_Kagamine_Rin_ (赞：15)

这题真的是毒瘤啊……

注：本题解提供 $\mathcal{O}(n\sqrt {n\log n})$ 的解法，不是正解，如果要学习 $\mathcal{O}(n\sqrt n)$ 的正解请看别的题解。

### 简要题意
> 给定一个数组 $\{a_1, \dots, a_n\}$，有 $q$ 次询问（$l, r, L, R, p, x$），并回答 $a_l\sim a_r$ 中有多少个 $a_i$ 满足 $L \le a_i \le R$ 且 $a_i \bmod p = x$。
>
> 强制在线。

看到 $a_i \bmod p = x$ 就可以想到使用根号分治。

考虑将**值域**作为**下标**，存储该数值在 $a$ 中的**位置**：

```cpp
std::vector<int> vtop[V];
for (int i = 1; i <= n; ++ i) cin >> a[i];
for (int i = 1; i <= n; ++ i) vtop[a[i]].emplace_back(i);
```

设阈值为 $B$（一般另 $B = \sqrt V$，$V$ 为值域）。

当模数 $p > B$ 时，最多只要枚举 $\frac{V}{P}$ 个可能的 $a_i$ 满足条件，所以直接暴力。我们可以枚举每一个 $a_i$，在 $a_i$ 的所有可能的**下标**中用**二分**找到**左端点（$lpos$）**和**右端点（$rpos$）**，答案即为 $rpos - lpos + 1$，代码如下：
```cpp
if (p > B) {
  for (int i = (L - x + p - 1) / p * p + x; i <= R; i += p)
    ans += (upper_bound(vtop[i].begin(), vtop[i].end(), r) - vtop[i].begin()) - (lower_bound(vtop[i].begin(), vtop[i].end(), l) - vtop[i].begin());
    // 这里没有 +1 是因为 upper_bound 会找到 rpos 右边一格，所以 upper_bound 这里返回的是 rpos + 1
  cout << ans << "\n";
}
```
当模数 $p \le B$ 时，我们可以对**下标**进行分块。创建一个 **`vector` 数组** $d_{id, p, x}$ 预处理出 $a_{id_l}\sim a_{id_r}$（$id_l$ 和 $id_r$ 分别表示该块的左端点和右端点）中满足 $a_i \bmod p = x$ 的所有 $a_i$ 组成的**序列**，代码如下：
```cpp
for (int i = 1; i <= n; ++ i) {
  const int bl_id = (i - 1) / Block_N + 1; // 该下标对应的块编号
  for (int p = 1; p <= Block_V; ++ p)
    d[bl_id][p][a[i] % p].emplace_back(a[i]);
}
```
然后不能忘记排序：
```cpp
for (int i = 0; i <= bl(n); ++ i)
  for (int p = 0; p <= Block_V; ++ p)
    for (int x = 0; x <= Block_V; ++ x)
      sort(d[i][p][x].begin(), d[i][p][x].end());
```
在被询问时就很显然了：
```cpp
else { // if (p <= B)
  if (bl(l) == bl(r)) { // 左端点和右端点在同一个块，特殊处理
    for (int i = l; i <= r; ++ i) ans += L <= a[i] && a[i] <= R && a[i] % p == x;
    cout << ans << "\n";
  } else {
    while ((l - 1) % Block_N) L <= a[l] && a[l] <= R && a[l] % p == x && ++ ans, ++ l;
    while (r % Block_N)       L <= a[r] && a[r] <= R && a[r] % p == x && ++ ans, -- r;
    // ↑不是完整的块，暴力处理
    for (int i = bl(l); i <= bl(r); ++ i)
      ans += (upper_bound(d[i][p][x].begin(), d[i][p][x].end(), R) - d[i][p][x].begin()) - (lower_bound(d[i][p][x].begin(), d[i][p][x].end(), L) - d[i][p][x].begin());
    // 完整的块，直接相加（没有 +1 的原因和上面同理）
    cout << ans << "\n";
  }
}
```
然后我们终于写完了这份代码，并获得了 10 分的高分！
```cpp
%:import "functional"
%:import "algorithm"
%:import "iostream"
%:import "string.h"
%:import "queue"
%:define For(a, b, c) for (int a = b, a##END = c; a <= a##END; ++ a)
%:define bl(x) (((x) - 1) / Block_N + 1)
%:define bl_l(b) ((b) * Block_N - Block_N + 1)
%:define bl_r(b) ((b) * Block_N)
const int N = 1e5 + 7, V = 2e5 + 7, Block_V = 100, Block_N = 316; // Block_V 就是上文写道的 B，这里用于和 Block_N 进行区分

int a[N];
std::vector<int> vtop[V];
std::vector<int> d[318][Block_V + 1][Block_V + 1];
main() {
  using namespace std;
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, type, lastans = 0; cin >> n >> type;

  for (int i = 1; i <= n; ++ i) {
    cin >> a[i], vtop[a[i]].emplace_back(i);
    const int bl_id = (i - 1) / Block_N + 1;
    for (int p = 1; p <= Block_V; ++ p)
      d[bl_id][p][a[i] % p].emplace_back(a[i]);
  }
  for (int i = 0; i <= Block_N; ++ i)
    for (int p = 0; p <= Block_V; ++ p)
      for (int x = 0; x <= Block_V; ++ x)
        sort(d[i][p][x].begin(), d[i][p][x].end());
  int T; cin >> T;
  while (T --) {
    int l, r, L, R, p, x, ans = 0; cin >> l >> r >> L >> R >> p >> x;
    if (type) l ^= lastans, r ^= lastans, L ^= lastans, R ^= lastans, p ^= lastans, x ^= lastans;
    if (p > Block_V)
      for (int i = (L - x + p - 1) / p * p + x; i <= R; i += p)
        ans += (upper_bound(vtop[i].begin(), vtop[i].end(), r) - vtop[i].begin()) - (lower_bound(vtop[i].begin(), vtop[i].end(), l) - vtop[i].begin());
    else {
      if (bl(l) == bl(r)) {
        for (int i = l; i <= r; ++ i) ans += L <= a[i] && a[i] <= R && a[i] % p == x;//, fprintf(stderr, "%d, ", a[i] % p);
        goto opt;
      }
      while ((l - 1) % Block_N) ans += L <= a[l] && a[l] <= R && a[l] % p == x, ++ l;
      while (r % Block_N)       ans += L <= a[r] && a[r] <= R && a[r] % p == x, -- r;
      for (int i = bl(l), iEND = bl(r); i <= iEND; ++ i)
        ans += (upper_bound(d[i][p][x].begin(), d[i][p][x].end(), R) - d[i][p][x].begin()) - (lower_bound(d[i][p][x].begin(), d[i][p][x].end(), L) - d[i][p][x].begin());
    }
    opt: cout << (lastans = ans) << "\n";
  }
}
```
为什么？

因为这道题时间和空间卡得很紧，连正解都要卡常，更何况非正解呢？

**以下是我们需要注意的地方：**

1. 由于 $p\le B$ 的部分常数比较大，所以不能使用传统的 $\sqrt V$ 作为阈值，而要使用**更小的**数，比如 100。
2. 询问区间（$L$ 和 $R$）不一定是从 $1\sim V$ 的，事实上可能长度远小于 $V$，所以我们还可以加上判断 `if (p > B || (R - ((L - x + p - 1) / p * p + x)) <= 32768)`。
3. 当 `d[i][j][k].size() <= 1` 时，根本不需要排序，排序就是浪费时间，所以我们要在排序前写上：`if (d[i][j][k].size() > 1)`。
4. 对于 `for (int p = 1; p <= B; ++ p)` 这里，由于 $p\in[1,100]$，我们完全可以手写 100 遍代替一个 `for` 循环。

经过无数次的尝试，我们终于得到了以下 AC 代码，并愉快地切掉了一道黑题（[Record](https://www.luogu.com.cn/record/217957690)）：
```cpp
#import "algorithm" // 码风过丑，勿喷
#import "iostream"
#import "vector"
#define For(a, b, c) for (int a = b, a##END = c; a <= a##END; ++ a)
#define bl(x) (((x) - 1) / Block_N + 1)
#define bl_l(b) ((b) * Block_N - Block_N + 1)
#define bl_r(b) ((b) * Block_N)
const int N = 1e5 + 7, V = 2e5 + 7, Block_V = 100, Block_N = 750;
int a[N];
std::vector<int> vtop[V];
std::vector<int> d[bl(100000) + 2][Block_V + 1][Block_V + 1];
main() {
  using namespace std;
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n, type; cin >> n >> type;

  for (int i = 1; i <= n; ++ i) cin >> a[i];
  for (int i = 1; i <= n; ++ i) vtop[a[i]].emplace_back(i);
  for (int i = 1; i <= n; ++ i) {
    const int bl_id = (i - 1) / Block_N + 1;
#define op(p) d[bl_id][p][a[i] % p].emplace_back(a[i])
    op(1), op(2), op(3), op(4), op(5), op(6), op(7), op(8), op(9), op(10), op(11), op(12), op(13), op(14), op(15), op(16), op(17), op(18), op(19), op(20), op(21), op(22), op(23), op(24), op(25), op(26), op(27), op(28), op(29), op(30), op(31), op(32), op(33), op(34), op(35), op(36), op(37), op(38), op(39), op(40), op(41), op(42), op(43), op(44), op(45), op(46), op(47), op(48), op(49), op(50), op(51), op(52), op(53), op(54), op(55), op(56), op(57), op(58), op(59), op(60), op(61), op(62), op(63), op(64), op(65), op(66), op(67), op(68), op(69), op(70), op(71), op(72), op(73), op(74), op(75), op(76), op(77), op(78), op(79), op(80), op(81), op(82), op(83), op(84), op(85), op(86), op(87), op(88), op(89), op(90), op(91), op(92), op(93), op(94), op(95), op(96), op(97), op(98), op(99), op(100);
  }
  for (int i = 0; i <= bl(n); ++ i)
    for (int p = 0; p <= Block_V; ++ p)
      for (int x = 0; x <= Block_V; ++ x)
        if (d[i][p][x].size() > 1) sort(d[i][p][x].begin(), d[i][p][x].end());
  int T, ans = 0; cin >> T;
  while (T --) {
    int l, r, L, R, p, x; cin >> l >> r >> L >> R >> p >> x;
    type && (l ^= ans, r ^= ans, L ^= ans, R ^= ans, p ^= ans, x ^= ans), ans = 0;
    if (p > Block_V || (R - ((L - x + p - 1) / p * p + x)) <= 32768) {
      for (int i = (L - x + p - 1) / p * p + x; i <= R; i += p)
        ans += (upper_bound(vtop[i].begin(), vtop[i].end(), r) - vtop[i].begin()) - (lower_bound(vtop[i].begin(), vtop[i].end(), l) - vtop[i].begin());
      cout << ans << "\n";
    }
    else {
      if (bl(l) == bl(r)) {
        for (int i = l; i <= r; ++ i) ans += L <= a[i] && a[i] <= R && a[i] % p == x;//, fprintf(stderr, "%d, ", a[i] % p);
        cout << ans << "\n";
      } else {
        while ((l - 1) % Block_N) L <= a[l] && a[l] <= R && a[l] % p == x && ++ ans, ++ l;
        while (r % Block_N)       L <= a[r] && a[r] <= R && a[r] % p == x && ++ ans, -- r;
        for (int i = bl(l), iEND = bl(r); i <= iEND; ++ i)
          ans += (upper_bound(d[i][p][x].begin(), d[i][p][x].end(), R) - d[i][p][x].begin()) - (lower_bound(d[i][p][x].begin(), d[i][p][x].end(), L) - d[i][p][x].begin());
        cout << ans << "\n";
      }
    }
  }
}
```
~~卡常不易~~，点个赞再走吧~

对了，请不要抄题解，因为你抄了也过不了，就是浪费时间（别问我怎么知道的）

---

## 作者：forest114514 (赞：12)

我看了一下我的做法应该是在这篇题解写的时候所有可见的记录中最慢点最快的做法，最慢点只有一秒左右，而且空间是 $O(n\sqrt V)$ 的和 $O(V\sqrt n)$ 无关，而且我没有进行任何卡常，不然还能更快！！！

而且非常好写，没有一点细节没有一点卡常。

----

一眼对于 $p$ 根号分治。

----

- $p>B$

只用考虑 $O(\frac{V}{B})$ 种数在区间内的出现个数，注意到强制在线没法直接扫描线，一种 naive 的带 $\log$ 做法是直接对每个序列开一个桶然后二分。

实际上没必要，我们对序列分块设块长为 $C$，散块暴力做查询，这样每种数只用预处理 $O(\frac{n}{C})$ 个数的前缀信息，可以 $O(\frac{nV}{C})-O(\frac{V}{B}+C)$，可以适度平衡 $C$ 的时空常数。

一个比较唐的卡空间办法是注意到只有 $O(1)$ 种数的数量会大于 short 的存储范围，所以 $O(\frac{nV}{C})$ 的空间实际上是可以用 short 存的，不过本题空间限制很大所以不用搞。

所以能做到时间复杂度 $O(n\sqrt V+q(\sqrt V+\frac{V}{B}))$，空间 $O(n\sqrt V)$。

-----

- $p\leq B$

考虑只有 $O(B)$ 种不同的数。

我们按照模 $x$ 余 $y$ 分类，然后对每一类中的数按值域排序，然后拼在一起得到了一个 $O(nB)$ 的序列，我们对这个序列按 $B$ 分块，块内记录在 $1\sim \frac{n}{C}$ 每个序列块内有多少数，这样空间显然是 $O(n\sqrt n)$ 的，容易处理前缀和 $O(1)$ 查询整块信息。

考虑回答的时候我们先找到模 $x$ 余 $y$ 的数在大序列中的区间，特判在同一块内后，区间中至多两个散块容易处理，然后剩下的整块可以直接分讨和值域的包含关系，做到 $O(\frac{n}{B}+B)$ 单次查询。

这样空间复杂度 $O(nB+n\sqrt n)$，时间复杂度 $O(nB+q(\frac{n}{B}+B))$。

--------

于是平衡一下能做到时间复杂度 $O((n+q)\sqrt V)$，空间 $O(n\sqrt V+n\sqrt n)$ 。

```cpp
const int N=1e5+100,B=512,C=512,lim=256,S=(N+B-1)/B+10,V=2e5;
int n,q,BL,a[N],rk[N];
int cnt[N],las[N*2];
#define bl(x) (((x)-1)>>9)+1
#define pl(x) (((x)-1)<<9)+1
#define pr(x) min((x)<<9,V)
struct bl1{//每种数 
	int sz,pre[S];
	vector<int> pos;
	void init(){
		int cur=BL;
		sz=pos.size();
		per(i,sz-1,0){
			while(cur&&pr(cur)>=pos[i]) pre[cur]=pos[i],--cur;
		}		
		rep(i,1,cur) pre[cur]=0;
	}
	int query(int l,int r){
		return cnt[pre[r]]-cnt[pre[l-1]];
	}
}A[V+10];
struct bl2{
	short sum[N][S];
	int num[N*lim],tot[S];
	int L[lim+10][lim+10],R[lim+10][lim+10],buk[N];
	void init(){
		rep(i,1,n) rep(j,1,lim) R[j][a[i]%j]++;
		int cur=0;
		rep(i,1,lim) rep(j,0,i-1) L[i][j]=cur,cur+=R[i][j],R[i][j]=cur-1;
		rep(i,1,lim){
			rep(j,0,i-1) buk[j]=L[i][j]-1;
			rep(j,1,n) num[++buk[ a[rk[j]]%i ] ]=rk[j];
		}
		rep(t,0,n-1){
			rep(i,(t<<8),((t+1)<<8)-1) sum[t][bl(num[i])]++;
			rep(i,1,BL) sum[t][i]+=sum[t][i-1];
		}
	}
	int query(int x,int y,int l,int r,int vl,int vr){//%x=y 整块 l,r , 值域 vl,vr 
		int ll=L[x][y],rr=R[x][y];
		if(ll>rr) return 0;
		int pl=ll>>8,pr=rr>>8,res=0;
		if(pl==pr){
			rep(i,ll,rr) res+=(num[i]>=pl(l)&&num[i]<=pr(r)&&vl<=a[num[i]]&&a[num[i]]<=vr);
			return res;
		}
	
		rep(i,ll,(pl+1)*256-1) 
			res+=(num[i]>=pl(l)&&num[i]<=pr(r)&&vl<=a[num[i]]&&a[num[i]]<=vr);
		rep(i,(pr<<8),rr) 
			res+=(num[i]>=pl(l)&&num[i]<=pr(r)&&vl<=a[num[i]]&&a[num[i]]<=vr);
		rep(i,pl+1,pr-1){
			int ql=i*lim,qr=ql+lim-1;
			if(vl<=a[num[ql]]&&a[num[qr]]<=vr) res+=sum[i][r]-sum[i][l-1];//整块 
			else if(vl<=a[num[qr]]||a[num[ql]]<=vr||(a[num[ql]]<vl&&vr<a[num[qr]])){
				rep(j,ql,qr) res+=(num[j]>=pl(l)&&num[j]<=pr(r)&&vl<=a[num[j]]&&a[num[j]]<=vr);
			}
		}
		return res;
	}
}DS;
int query(int l,int r,int L,int R,int x,int y){
	int pl=bl(l),pr=bl(r),res=0;
	if(pl==pr){
		rep(i,l,r) res+=(a[i]>=L&&a[i]<=R&&a[i]%x==y);
		return res;
	}
	rep(i,l,pr(pl)) res+=(a[i]>=L&&a[i]<=R&&a[i]%x==y);
	rep(i,pl(pr),r) res+=(a[i]>=L&&a[i]<=R&&a[i]%x==y);
	if(pl+1<=pr-1){
		if(x>lim){
			for(int i=(L-y+x-1)/x*x+y;i<=R;i+=x) res+=A[i].query(pl+1,pr-1);
			return res;
		}
		return res+DS.query(x,y,pl+1,pr-1,L,R);
	}
	return res;
}
signed main(){
	int T_T;
	read(n,T_T),BL=(n+B-1)/B;
	rep(i,1,n){
		read(a[i]),rk[i]=i;
		A[a[i]].pos.pb(i);
		cnt[i]=(++las[a[i]]);
	}
	sort(rk+1,rk+1+n,[&](int x,int y){return a[x]<a[y];});
	rep(i,1,V) A[i].init();
	DS.init();
	read(q);
	int lasans=0;
	while(q--){
		int l,r,L,R,x,y;read(l,r,L,R,x,y);
		l^=(lasans*T_T),r^=(lasans*T_T);
		L^=(lasans*T_T),R^=(lasans*T_T);
		x^=(lasans*T_T),y^=(lasans*T_T);
		write(lasans=query(l,r,L,R,x,y),'\n');
	}
	return 0;
}
```

---

## 作者：lzyqwq (赞：9)

我怎么只会根号老哥 /ll。

> - 给出 $[a_1,\dots,a_n]$，$q$ 次询问 $l,r,L,R,p,x$，求：
>
>   $$\sum\limits_{i=l}^r[a_i\in [L,R]\land a_i\bmod p=x]$$
> - $n,q\le 10^5$，$a_i\le 2\times 10^5$。

设值域为 $V$。先讲一下口胡的根号老哥做法。

根号分治，设阈值 $T=\mathcal{O}\left(\sqrt {|V|}\right)$。对于 $p\ge T$ 的询问，只会有 $\mathcal{O}(T)$ 种符合条件的值。此处有 $\mathcal{O}(qT)$ 次查询区间内一个数的出现次数。显然要求单次 $\mathcal{O}(1)$。

我是唐龙所以胡了个可持久化分块。能做，但是我没写过这玩意，感觉常数巨大。问了出题人发现可以先对序列以 $S$ 为块长分块，散块暴力做掉。

现在问题只剩下整块的情况。容易 $\mathcal{O}\left(\dfrac{n^2}{S}\right)$ 维护出 $c_{i,j}$ 表示前 $i$ 个块中 $j$ 的出现次数，就可以 $\mathcal{O}(1)$ 查询某个数在一段整块中的出现次数。

对于 $p<T$ 的询问，对于每个块，考虑维护出所有 $p,x$ 的答案。记 $d_{\text{id},p,x}$ 表示第 $\text{id}$ 个块中模 $p$ 为 $x$ 的元素从小到大构成的序列。显然对于一个 $p$，由于 $a_i$ 模 $p$ 的值是确定的，每个 $a_i$ 只会出现在一个 $d_{\text{id},p,x}$ 中，因此 $d$ 的总大小为 $\mathcal{O}(nT)$。那么有 $\mathcal{O}\left(\dfrac{qn}{S}\right)$ 次查询 $d_{\text{id},p,x}$ 中一段区间内的元素的和。同样要求单次 $\mathcal{O}(1)$，那我只会前缀和。因此考虑对每个 $d_{\text{id},p,x}$ 建立前缀和，这一步是 $\mathcal{O}(nT)$，然后每次查询就拿两个前缀相减是 $\mathcal{O}(1)$。

正当我以为把这题秒了时，我意识到一个严峻的问题。由于 $d_{\text{id},p,x}$ 相当于经过离散化后的部分序列，还需要把查询的值域区间映射到这个离散的序列上。这一步我只会二分。于是原地变成 $\mathcal{O}(\log n)$。

平衡一下，取 $S=\mathcal{O}\left(\sqrt{n\log n}\right)$ 时，时间复杂度为 $\mathcal{O}\left(q\sqrt{n\log n}\right)$，空间复杂度为 $\mathcal{O}\left(n\sqrt{|V|}\right)$。寄！也许大力卡常能过。

我的数据结构水平这辈子就这样了，于是去看官方题解。接下来正片开始。显然正解是单根号，所以从下文起认为 $S=\mathcal{O}(\sqrt n)$。

考虑再以 $T$ 为块长值域分块，那么位于值域散块中的值也只有 $\mathcal{O}(T)$ 个，使用 $p\ge T$ 部分的做法即可。接下来我们要求出所在序列块编号位于一段区间内、所在值域块编号位于一段区间内且模 $p$ 为 $x$ 的元素个数。还是考虑继续开发 $d_{\text{id},p,x}$。但是不考虑对于每个块都开一个了，让 $d_{p,x}$ 表示序列中模 $p$ 为 $x$ 的元素构成的序列，内部元素按照所在块编号大小排序。我们按照 $p,x$ 分类，将所有 $d_{p,x}$ 拼接在一起得到一个长度为 $\mathcal{O}(nT)$ 的数组 $v$。其中对于每个 $p,x$，$d_{p,x}$ 在 $v$ 中都是一段区间内的元素。

我们再将 $v$ 这个序列以 $S$ 为块长分块。那么会有 $\mathcal{O}\left(\sqrt{n|V|}\right)$ 块。下文称之为“操作块”。再维护桶 $b_{\text{id},j}$ 表示前 $\text{id}$ 个操作块中位于第 $j$ 个值域块中的元素个数。这一步是 $\mathcal{O}(|V|\sqrt n)$。那么所在序列块编号的区间在 $v$ 上就是一个区间，且是 $d_{p,x}$ 所在区间的一个子区间。现在相当于查询这个区间内位于所在值域块编号位于一段区间 $[\text{qL},\text{qR}]$ 的元素个数。

对于每个序列块 $\text{id}$，考虑维护出 $P_{\text{id},p,x}$ 表示在 $d_{p,x}$ 所在区间中，最后一个所在值域块编号不超过 $\text{id}$ 的元素位置。这个可以对于每个 $p,x$ 双指针维护，时间 $\mathcal{O}\left(|V|\sqrt n+n\sqrt{|V|}\right)$。那么 $[\text{qL},\text{qR}]$ 在 $v$ 中对应的区间就是 $[P_{\text{qL}-1,p,x},P_{\text{qR},p,x}]$。

对于操作散块同样可以暴力做。对于操作整块，枚举值域块编号，然后拿 $b$ 桶的两个前缀信息差分即可每个值域块 $\mathcal{O}(1)$ 查询。一共是 $\mathcal{O}\left(q\sqrt n+q\sqrt{|V|}\right)$，两项分别对应散块和整块。

那么就做完了，认为 $n,q$ 同阶且 $|V|$ 更大，时空复杂度均为 $\mathcal{O}\left(|V|\sqrt n\right)$。不知道为啥官方题解里面写的是 $\mathcal{O}\left(n\sqrt{|V|}\right)$，你空间都 $\mathcal{O}\left(|V|\sqrt n\right)$ 了时间怎么还更小的。可能是因为“可知最多有 $\mathcal{O}(n)$ 个块”这句话认为 $n,|V|$ 同阶了。

代码里块长定义与文中略有不同。写的比现有的 AC 代码都短。一开始 TLE 了几发以为被卡常，没想到是 `cin` 忘记关同步流了。

空间可能有点卡。要慎开 $\mathcal{O}(n\sqrt n)$ 级别的数组。


```cpp
#include <bits/stdc++.h>
const int S = 512, T = 256, N = 100005, M = 200005, K = 205, B = 405;
using namespace std; int n, o, q, a[N]; vector<int> d[T];
struct BLK1 {
	int c[K][M]; int be(int x) { return (x - 1 >> 9) + 1; }
	int bl(int x) { return (x - 1 << 9) + 1; }
	int br(int x) { return min(n, x << 9); }
	void I() {
		for (int i = 1; i <= be(n); ++i) {
			for (int j = 1; j < M; ++j) c[i][j] = c[i - 1][j];
			for (int j = bl(i); j <= br(i); ++j) ++c[i][a[j]];
		}
	}
	int Q(int l, int r, int x) { return c[r][x] - c[l - 1][x]; }
} b1;
struct BLK2 {
	int be(int x) { return (x - 1 >> 9) + 1; }
	int bl(int x) { return (x - 1 << 9) + 1; }
	int br(int x) { return min(M - 1, x << 9); }
} b2;
struct BLK3 {
	int m, v[N * T], b[B][N >> 1], P[K][T][T], l[T][T], r[T][T];
	int be(int x) { return (x - 1 >> 9) + 1; }
	int bl(int x) { return (x - 1 << 9) + 1; }
	int br(int x) { return min(m, x << 9); }
	void I() {
		for (int i = 1; i < T; ++i) {
			for (int j = 0; j < T; ++j) d[j].clear();
			for (int j = 1; j <= n; ++j) d[a[j] % i].emplace_back(j);
			for (int j = 0; j < T; ++j) {
				l[i][j] = m + 1; for (int u : d[j]) v[++m] = u; r[i][j] = m;
			}
		}
		for (int i = 1; i < T; ++i)
			for (int j = 0; j < i; ++j)
				for (int t = 1, u = l[i][j]; t <= b1.be(n); ++t) {
					while (u <= r[i][j] && b1.be(v[u]) <= t) ++u;
					P[t][i][j] = u - 1; 
				}
		for (int i = 1; i <= be(m); ++i) {
			for (int j = 1; j < B; ++j) b[j][i] = b[j][i - 1];
			for (int j = bl(i); j <= br(i); ++j) ++b[b2.be(a[v[j]])][i];
		}
	}
	int qry(int l, int r, int L, int R) {
		int e = 0;
		if (be(l) == be(r)) {
			for (int i = l; i <= r; ++i)
				e += (L <= b2.be(a[v[i]]) && b2.be(a[v[i]]) <= R);
			return e;
		}
		for (int i = L; i <= R; ++i) e += b[i][be(r) - 1] - b[i][be(l)];
		return e + qry(l, br(be(l)), L, R) + qry(bl(be(r)), r, L, R);
	}
	int Q(int l, int r, int L, int R, int p, int x) {
		return qry(P[l - 1][p][x] + 1, P[r][p][x], L, R);
	}
} b3;
int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cin >> n >> o; for (int i = 1; i <= n; ++i) cin >> a[i];
	cin >> q; b1.I(); b3.I();
	for (int l, r, L, R, p, x, la = 0, ql, qr, qL, qR; q--;) {
		cin >> l >> r >> L >> R >> p >> x; la *= o;
		l ^= la; r ^= la; L ^= la; R ^= la; p ^= la; x ^= la; la = 0;
		if (b1.be(l) == b1.be(r)) {
			for (int i = l; i <= r; ++i)
				la += (L <= a[i] && a[i] <= R && a[i] % p == x);
			cout << la << '\n'; continue;
		}
		ql = b1.be(l) + 1; qr = b1.be(r) - 1;
		for (int i = l; i < b1.bl(ql); ++i)
			la += (L <= a[i] && a[i] <= R && a[i] % p == x);
		for (int i = r; i > b1.br(qr); --i)
			la += (L <= a[i] && a[i] <= R && a[i] % p == x);
		if (ql > qr) { cout << la << '\n'; continue; }
		if (p >= T) {
			for (int i = p * (L / p + (L % p > x)) + x; i <= R; i += p)
				la += b1.Q(ql, qr, i);
			cout << la << '\n'; continue;
		}
		if (b2.be(L) == b2.be(R)) {
			for (int i = L; i <= R; ++i) la += (i % p == x) * b1.Q(ql, qr, i);
			cout << la << '\n'; continue;
		}
		qL = b2.be(L) + 1; qR = b2.be(R) - 1;
		for (int i = L; i < b2.bl(qL); ++i)
			la += (i % p == x) * b1.Q(ql, qr, i);
		for (int i = R; i > b2.br(qR); --i)
			la += (i % p == x) * b1.Q(ql, qr, i);
		if (qL > qR) { cout << la << '\n'; continue; }
		la += b3.Q(ql, qr, qL, qR, p, x); cout << la << '\n';
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：8)

出题人题解。

## 题意

题目名是 [WorldMachine](https://www.luogu.com.cn/user/879904) 放的。

序列值域区间与下标区间的给定模数余数的同余元素计数。

## $O(n ^ 2)$ 做法

不用想的，枚举区间每一个数判一下就行了。

## 离线做法

这一部分对正解提示不大，所以没有给多少部分分。

有 $p$ 的模数限制，考虑根号分治，因为有下标值域限制，限制很多，所以直接考虑序列分块，现在分为两个问题考虑。

一个是 $p \ge \sqrt V$，我们只需要枚举每一个值，判断区间内给定值的个数就行了，使用分块平衡到 $O(q \sqrt n + q\sqrt V)$。

一个是 $p < \sqrt V$，我们将询问按值域差分，然后按值域将询问排序，每一次询问将元素动态插入时，所有元素均小于等于当前询问的值域上界，因此每一个块维护一个桶 $t_{p,x}$，表示这个块有多少模 $p$ 等于 $x$ 的元素，查询散块暴力，整块查表就行了，时间 $O(q \sqrt n)$。

## $O(nV ^ {\frac {2}{3}})$ 做法

如果在线，我们延续离线的思路，我们可以提前将块内的元素排个序，那么每次询问整块查询的是一个块的前缀元素，我们考虑每个块开一个前缀桶 $t_{i,p,x}$ 表示 $i$ 这个前缀有多少模 $p$ 等于 $x$ 的元素，但不难发现这样空间复杂度就是 $O(nV)$ 的。

我们从根号分治的阈值入手，我们将所有 $\ge V^{\frac{1}{3}}$ 的 $p$ 跑暴力，其他的预处理，这样的话桶只需要开 $O(n V^{\frac{2}{3}})$ 就行了。

时间复杂度 $O(q V^{\frac{2}{3}})$，空间复杂度 $O(n V^{\frac{2}{3}})$。

## 根号解法

能不能不调整阈值优化下来呢？

我们只考虑小于阈值的询问如何处理，我们值域分块，并且将询问下标区间也进行差分，这样序列散块和值域散块我们都可以暴力计算，我们考虑序列前缀整块对值域前缀整块的贡献，需要开一个桶 $t_{b,p,x,v}$ 表示第 $b$ 个块中有多少模 $p$ 等于 $x$，并且值域位于第 $v$ 块的元素，其实这个桶只会有 $n\sqrt V$ 个地方有值，考虑按 $p,x$ 将修改分类后，把有关 $p,x$ 的修改看做操作序列，按序列块的编号排序，将操作序列分块，可知最多有 $O(n) $ 个块，每个块处理一个 $\sqrt V$ 的桶，表示这个块之前的操作的值位于每个值域块的个数，查询时在对应的操作序列中查一次整块前缀表，散块同样暴力，这样就能将复杂度平衡下来了。

时间复杂度 $O(n\sqrt V +q\sqrt V +q \sqrt n)$，空间复杂度 $O(V\sqrt n +n \sqrt V)$。

## 卡常

实际上不需要差分，无论是序列分块，值域分块还是预处理的操作分块，都可以变成散块贡献和整块贡献，直接做就行了，常数会小一些。

---

## 作者：封禁用户 (赞：8)

这……这种问题，我当然知道，我……我可不是要说给你听的，我只是觉得你不知道的话太可怜了……对，就是这样……所以给我认认真真的记住！

考虑对 $p$ 根号分治，$>\sqrt V$ 的直接拿一个 vector 存一下，暴力二分就可以了。

对于 $p<\sqrt V$ 的部分，序列分块预处理每一个块对 $p$ 取模之后 $=x$ 的答案，时间是 $\mathcal O(n\sqrt{n\log n})$ 询问也是二分即可。

注意我们可以加入一个剪枝：如果暴力枚举的 $kp+x$ 的合法个数是在一个数以内的（我的代码里面是 $500$，经测试这是很合理的），那么久直接用 $p>\sqrt V$ 的跑。

这里给出一点我的参数建议，可以稳过，不需要靠波动：

```cpp
cin >> N >> opt;
L (i, 1, N) cin >> A[i], chmax(V, A[i]),
  pos[A[i]].push_back(i);
L (i, 1, V) sort (pos[i].begin(), pos[i].end());
const int B = sqrt(N) * 6.4;
L (i, 1, N) {
  bl[i] = (i - 1 + B) / B;
  if (!lpos[bl[i]]) lpos[bl[i]] = i;
  chmax (rpos[bl[i]], i);
}
const int VB = 100;
L (i, 1, N) {
  int blt = bl[i];
  L (v, 1, VB) g[blt][v][A[i] % v].push_back(A[i]);
}
```

跑的比大部分 $\mathcal O(n\sqrt n)$ 题解快。

---

## 作者：UniGravity (赞：7)

魔怔卡常题。/ll

考虑按照 $p$ 根号分治。

$p>B$，直接查询是 $O(\frac{qV\log n}{B})$ 的。

不过可以对序列分块。对于整块预处理 $c_{i,j}$ 表示前 $i$ 个块 $j$ 出现几次，每次询问时先把散块扫一遍丢到桶里，然后就可以做到 $O(q\sqrt n+\frac{qV}{B})$ 了。

$p\le B$，对每个 $p$ 扫一遍整个数列预处理按 $\bmod\space p$ 分类，这样每次询问相当于问一个矩阵内有多少个数。

还是分块！先转成查询左下角有多少个数。

考虑按下标分成 $X$ 块，散块直接扫一遍 $O(\frac{n}{X})$ 就能知道答案。但这样子整块还是做不了，因为要存储的信息有 $O(VBX)$ 级别。

再次分块！将值域也分成 $Y$ 块，此时对于超出整块的部分，我们按照上面 $p>B$ 时的单值查出现次数做。此时下标和值都被分成了若干块，一共只有 $O(\frac{nV}{XY})$ 个块。此时再对这些块做前缀和然后查询即可。

整理一下时间复杂度，是 $O(q\sqrt n+\frac{qV}{B}+\frac{qn}{X}+\frac{qV}{Y}+\frac{nVB}{XY})$，取 $X=\sqrt n,Y=\sqrt V,B=\sqrt V$，可得时间复杂度 $O(q\sqrt n+q\sqrt V+q\sqrt n+V\sqrt n)$。

由于 $n,q,V$ 实际上可以视为同阶，大概可以认为时间复杂度为 $O(n\sqrt n)$，空间复杂度也为 $O(n\sqrt n)$。

卡常技巧：由于另一维是预处理，查询是 $O(1)$ 的，因此可以适当减小块长。最后卡到了 1.51s 上下，靠评测机波动并非顺利通过。

```cpp
// Code by UniGravity
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define forto(i,a,b) for(int i=(a),_##i(b);i<=_##i;i++)
#define forbk(i,a,b) for(int i=(a),_##i(b);i>=_##i;i--)
#define forv(i,a) for(int i(0),_##i(a);i<_##i;i++)
#define fst first
#define snd second
#define il inline
#define eb emplace_back
#define mkp make_pair
using namespace std;
char *p1,*p2,buf[1<<20];
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
il int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||'9'<c)c=='-'?(f=-1):0,c=getchar();
    while('0'<=c&&c<='9')x=x*10+c-'0',c=getchar();
    return x*f;
}

const int N=100005,M=200005,X=300,Y=360,B=350;
int n,m=200000,tp,a[N];
il int dceil(int x,int y){return x<=0?0:((x-1)/y+1);}
int ib[N],ibg[N/X+2],ied[N/X+2],vb[M],vbg[M/Y+2],ved[M/Y+2];

namespace ID{
    int c[N/X+2][M];
    il void init(){
        forto(i,1,n){
            ib[i]=(i-1)/X+1,c[ib[i]][a[i]]++;
            if(!ibg[ib[i]])ibg[ib[i]]=i;
            ied[ib[i]]=i;
        }
        forto(i,1,m){
            vb[i]=(i-1)/Y+1;
            if(!vbg[vb[i]])vbg[vb[i]]=i;
            ved[vb[i]]=i;
        }
        forto(i,1,ib[n])forto(j,1,m)c[i][j]+=c[i-1][j];
    }
    int cnt[M],nl,nr;
    il void qset(int l,int r){
        if(ib[l]==ib[r]){
            nl=nr=0;
            forto(i,l,r)cnt[a[i]]++;
        }else{
            nl=ib[l],nr=ib[r]-1;
            forto(i,l,ied[ib[l]])cnt[a[i]]++;
            forto(i,ibg[ib[r]],r)cnt[a[i]]++;
        }
    }
    il void qreset(int l,int r){
        if(ib[l]==ib[r]){
            forto(i,l,r)cnt[a[i]]--;
        }else{
            forto(i,l,ied[ib[l]])cnt[a[i]]--;
            forto(i,ibg[ib[r]],r)cnt[a[i]]--;
        }
    }
    il int qry(int val){
        return cnt[val]+c[nr][val]-c[nl][val];
    }
}

int sum[B+2][N/X+2][M/Y+2],reval[B+2][M];
vector<int>len[B+2];
il int getv(int p,int x){
    if(x%p==0)return x/p;
    else return len[p][x%p-1]+x/p+1;
}

signed main(){
    n=read(),tp=read();
    forto(i,1,n)a[i]=read();
    ID::init();
    forto(p,1,B){
        len[p].resize(p+1),len[p][0]=m/p;
        forto(i,1,p-1)len[p][i]=len[p][i-1]+(m-i)/p+1;
        int tot=0;
        forv(c,p)for(int i=(!c)?p:c;i<=m;i+=p)reval[p][++tot]=i;
        forto(i,1,n)sum[p][ib[i]][vb[getv(p,a[i])]]++;
        forto(i,1,ib[n])forto(j,1,vb[m])sum[p][i][j]+=sum[p][i-1][j]+sum[p][i][j-1]-sum[p][i-1][j-1];
    }
    int q=read(),l,r,bg,ed,p,x,lst=0,res,vi,vj,nl,nr,tmp;
    forto(_,1,q){
        l=read()^lst,r=read()^lst,bg=read()^lst,ed=read()^lst,p=read()^lst,x=read()^lst;
        res=0,ID::qset(l,r);
        if(p>B){
            for(int i=dceil(bg-x,p)*p+x;i<=ed;i+=p)res+=ID::qry(i);
        }else{
            vi=dceil(bg-x,p)*p+x,vj=ed-x<0?-1:((ed-x)/p*p+x);
            if(vi<=vj){
                vi=getv(p,vi),vj=getv(p,vj);
                if(vb[vi]==vb[vj]){
                    forto(i,vi,vj)res+=ID::qry(reval[p][i]);
                }else{
                    forto(i,vi,ved[vb[vi]])res+=ID::qry(reval[p][i]);
                    forto(i,vbg[vb[vj]],vj)res+=ID::qry(reval[p][i]);
                    vi=ved[vb[vi]]+1,vj=vbg[vb[vj]]-1;
                    if(vi<=vj){
                        if(ib[l]==ib[r]){
                            forto(i,l,r)tmp=getv(p,a[i]),res+=(vi<=tmp&&tmp<=vj);
                        }else{
                            forto(i,l,ied[ib[l]])tmp=getv(p,a[i]),res+=(vi<=tmp&&tmp<=vj);
                            forto(i,ibg[ib[r]],r)tmp=getv(p,a[i]),res+=(vi<=tmp&&tmp<=vj);
                            nl=ib[l]+1,nr=ib[r]-1,vi=vb[vi],vj=vb[vj];
                            if(nl<=nr)res+=sum[p][nr][vj]-sum[p][nl-1][vj]-sum[p][nr][vi-1]+sum[p][nl-1][vi-1];
                        }
                    }
                }
            }
        }
        ID::qreset(l,r);
        if(tp)lst=res;
        printf("%d\n",res);
    }
    return 0;
}
```

---

## 作者：_zuoqingyuan (赞：4)

阴间分块题。

本篇题解使用 $O(V\sqrt{n})$ 大常数分块做法，卡常难度巨大。必须搭配评测机波动才能过题。

# 题意简述

给定一个长为 $n$ 的序列，回答 $q$ 次询问，每次询问给定 $l,r,L,R,p,x$，回答 $a_l\sim a_r$ 中有多少个 $a_i$ 满足 $L\le a_i\le R$ 且 $a_i\bmod p=x$。

$n,q\le 10^5,1\le a_i\le 2\times 10^5$，强制在线。

# 思路分析

给定一个值域区间，询问和 $a_i\bmod p$ 有关，不难想到根号分治。下文用 $V$ 指代值域，其中 $V=2\times 10^5$。

设阈值为 $T$，对于 $p\ge T$ 的询问，我们可以枚举 $[L,R]$ 内合法的 $v=kp+x$。然后数 $[l,r]$ 内有多少个 $v$，借助分块可以快速解决这个问题。

将原序列分为 $B$ 个一块，$l$ 属于块 $p$，$r$ 属于块 $q$，记录一个前缀和数组 $s_{i,j}$ 表示前 $i$ 块数字 $j$ 的出现次数。对于散块，暴力枚举判断；对于中间的整块，沿用上面枚举合法取值的方法，将 $s_{q-1,v}-s_{p,v}$ 累加到答案上。

这种做法的时间预处理时间复杂度为 $O(VB)$，处理一次询问的复杂度为 $O(B+\dfrac{V}{T})$。

对于 $p<T$ 的询问，情况较为复杂。显然，我们可以让 $L$ 变成它之后第一个模 $p$ 为 $x$ 的数，让 $R$ 变成它之前第一个模 $p$ 为 $x$ 的数，例如样例一中的值域区间 $[1,6]$ 可以缩小到 $[2,4]$，这种转化在下文会使用到。

对于每一个 $p$，建立一个坐标系，横轴指代下标，纵轴指代具体的值。将每个 $i$ 视为坐标系中一个点 $(i,a_i)$。

这样转化后，容易发现每次的询问其实是 $\dfrac{V}{T}$ 个 $1\times n$ 矩形内元素总和，不方便处理，所以要再做进一步转化。对于第 $p$ 个平面的 $V$ 行，将这 $V$ 行按照模 $p$ 的余数为第一关键字，以除 $p$ 的商下取整为第二关键字重新排列。下面展示 $V=5,n=6,p=2$ 的样例一。

![](https://cdn.luogu.com.cn/upload/image_hosting/2dmbpcoq.png)

这样转化的好处是，所有 $a_i\bmod p$ 相同的数对应的纵坐标是连续的，多个不同的询问矩形拼接成了一个询问的矩形，例如样例一的第一个询问可以转化为左上角为 $(1,2)$，右下角为 $(6,1)$ 的矩形内部元素个数。

现在我们要解决如何快速查询一个矩形内元素个数。对下标和值域都分块，还是将下标分为 $B$ 个一块，值域分为 $S$ 个一块。记 $l$ 属于块 $p$，$r$ 属于块 $q$，$L$ 属于块 $P$，$R$ 属于块 $Q$。则一个询问可以划分为散块和整块如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/a7c5txuk.png)

对于红色部分的散块，实际上就是下标的散块，直接暴力枚举判断即可。时间复杂度 $O(B)$。

对于蓝色的散块，是一些合法但数量少的值的散块，沿用 $p>T$ 的做法即可。时间复杂度 $O(S)$

对于黄色的整块，记录二维前缀和。记 $c_{p,i,j}$ 表示第 $p$ 个平面，以横坐标为第 $i$ 块，纵坐标为第 $j$ 块的块为右上角，原点为左下角的矩形内元素个数，用容斥的方法减出来即可。预处理时间复杂度 $O(\dfrac{nV}{BS})$，单次询问 $O(1)$。

当 $T=S=\sqrt{V},B=\sqrt{n}$ 时，时间复杂度理论最优约为 $O(V\sqrt{n})$ 级别。

实际上这样取值写出来的代码过不了，无论时间还是空间都无法承受，一般取 $T=100,B=300,S=360$ 可能会比较快，再省掉一些不必要的预处理，循环展开减小常数，搭配评测机波动有概率通过本题所有测试点。


# Code

挑选了理解度比较高的一版代码，实际上无法通过本题。可以通过本题（小概率）的代码放在最后的剪切版了，两份代码没有本质差别，只是后者卡了常数。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int N=1e5+10,M=2e5+10;
const int S=300,T=100,V=2e5,B=350;
int n,q,qwq,a[N],s[350][M];
int ti,bi[N],tv,bv[M],to[105][M],f[105][M],c[105][350][600];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
void init(){
	ti=n/S;if(ti*S!=n)ti++;
	for(int i=1;i<=n;i++){
		bi[i]=(i-1)/S+1;
		for(int j=bi[i];j<=ti;j++)s[j][a[i]]++;
	}
	tv=V/B;if(tv*B!=V)tv++;
	for(int i=1;i<=V;i++)bv[i]=(i-1)/B+1;
	int cnt=0;
	for(int mod=1;mod<=T;mod++){
		cnt=0;
		for(int i=0;i<mod;i++){
			for(int j=i;j<=V;j+=mod){
				if(!j)continue;
				to[mod][j]=++cnt;	
				f[mod][cnt]=j;
			}
		}
		for(int i=1;i<=n;i++)c[mod][bi[i]][bv[to[mod][a[i]]]]++;
		for(int i=1;i<=ti;i++)for(int j=2;j<=tv;j++)c[mod][i][j]+=c[mod][i][j-1];
		for(int i=2;i<=ti;i++)for(int j=1;j<=tv;j++)c[mod][i][j]+=c[mod][i-1][j];
	}
	return;
}
int il,ir,vl,vr,p,x,lst,iL,iR,vL,vR,ans;
int work(){
	il=read(),ir=read(),vl=read(),vr=read(),p=read(),x=read();ans=0;
	if(qwq)il^=lst,ir^=lst,vl^=lst,vr^=lst,p^=lst,x^=lst;
	if(bi[il]==bi[ir]){
		for(int i=il;i<=ir;i++)if(a[i]>=vl&&a[i]<=vr&&a[i]%p==x)ans++;
	}else if(p>T){
		iL=bi[il],iR=bi[ir];
		for(int i=il;bi[i]==iL;i++)if(a[i]>=vl&&a[i]<=vr&&a[i]%p==x)ans++;
		for(int i=ir;bi[i]==iR;i--)if(a[i]>=vl&&a[i]<=vr&&a[i]%p==x)ans++;
		if(iL+1<=iR-1)for(int v=(vl-x+p-1)/p*p+x;v<=vr;v+=p)ans+=s[iR-1][v]-s[iL][v];
	}else{
		iL=bi[il],iR=bi[ir];
		for(int i=il;bi[i]==iL;i++)if(a[i]>=vl&&a[i]<=vr&&a[i]%p==x)ans++;
		for(int i=ir;bi[i]==iR;i--)if(a[i]>=vl&&a[i]<=vr&&a[i]%p==x)ans++;
		vr=(vr-x)/p*p+x,vl=(vl-x+p-1)/p*p+x;if(vl>vr)return ans;
		vL=bv[to[p][vl]],vR=bv[to[p][vr]];
		if(vL==vR){
			for(int v=vl;v<=vr;v+=p)ans+=s[iR-1][v]-s[iL][v];
		}else{
			for(int v=to[p][vl];bv[v]==vL;v++)ans+=s[iR-1][f[p][v]]-s[iL][f[p][v]];
			for(int v=to[p][vr];bv[v]==vR;v--)ans+=s[iR-1][f[p][v]]-s[iL][f[p][v]];
			if(vL+1<=vR-1&&iL+1<=iR-1)ans+=c[p][iR-1][vR-1]-c[p][iL][vR-1]-c[p][iR-1][vL]+c[p][iL][vL];
		}
	}
	return ans;
}
int main(){
	n=read(),qwq=read(); 
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();init();
	while(q--){
		lst=work();
		printf("%d\n",lst);
	}
	return 0;
} 
```

[AC code](https://www.luogu.com.cn/paste/019tjo1t)。



如有错误，请指出。

---

