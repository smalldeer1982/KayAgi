# More Wrong

## 题目描述

This is an interactive problem.

The jury has hidden a permutation $ ^\dagger $ $ p $ of length $ n $ .

In one query, you can pick two integers $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) by paying $ (r - l)^2 $ coins. In return, you will be given the number of inversions $ ^\ddagger $ in the subarray $ [p_l, p_{l + 1}, \ldots p_r] $ .

Find the index of the maximum element in $ p $ by spending at most $ 5 \cdot n^2 $ coins.

Note: the grader is not adaptive: the permutation is fixed before any queries are made.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ The number of inversions in an array is the number of pairs of indices $ (i,j) $ such that $ i < j $ and $ a_i > a_j $ . For example, the array $ [10,2,6,3] $ contains $ 4 $ inversions. The inversions are $ (1,2),(1,3),(1,4) $ , and $ (3,4) $ .

## 说明/提示

In the first test, the interaction proceeds as follows:

SolutionJuryExplanation2There are $ 2 $ test cases.4In the first test case, the hidden permutation is $ [1,3,2,4] $ , with length $ 4 $ .? 1 3 1The solution requests the number of inversions in the subarray $ [1,3,2] $ by paying $ 4 $ coins, and the jury responds with $ 1 $ .? 3 4 0The solution requests the number of inversions in the subarray $ [2,4] $ by paying $ 1 $ coin, and the jury responds with $ 0 $ .! 4 The solution has somehow determined that $ p_4 = 4 $ , and outputs it. Since the output is correct, the jury continues to the next test case.2In the second test case, the hidden permutation is $ [2,1] $ , with length $ 2 $ .? 1 2 1The solution requests the number of inversions in the subarray $ [2,1] $ by paying $ 1 $ coin, and the jury responds with $ 1 $ .! 1 The solution has somehow determined that $ p_1 = 2 $ , and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
4

1

0

2

1```

### 输出

```
? 1 3

? 3 4

! 4

? 1 2

! 1```

# 题解

## 作者：LYS_AK_IOI (赞：13)

### 题意

交互题。有一个长度为 $n$ 的排列 $a$，每次你可以询问区间 $[l,r]$ 之间的逆序对个数，花费 $(r-l)^2$ 的代价，你需要在花费不超过 $5n^2$ 的代价下找出最大值所在位置。

### 题解

#### 初步想法

每次只能询问区间逆序对数，逆序对数和最大值有什么关系呢？我们考虑先固定询问的左端点 $l$ 为 $1$，右端点 $r$ 依次为 $1,2,\cdots,n$，观察规律。设最大值所在位置为 $p$，则可以发现：

1. 区间 $[l,p-1]$ 和 $[l,p]$ 的询问结果是一样的（因为 $a_p$ 是最大值，前面不会有比它大的数，逆序对数不会增加）。

2. 区间 $[l,p+1],[l,p+2],\cdots,[l,n]$ 的询问结果每次必定至少增加 $1$（因为 $a_p$ 是最大值，每次一定会与后面新加的数产生一个逆序对）。

由此引出**区间最大值的判定定理**：固定区间左端点 $l$，**最后一个**逆序对不增加的位置就是最大值的位置（**最后一个**满足 $[l,p-1]$ 的询问结果等于 $[l,p]$ 的位置 $p$ 就是区间最大值所在位置）。

由这个定理，我们可以确定右端点是否是区间最大值。

并且，我们还可以产生一个暴力的想法：询问区间 $[1,2],[1,3],\cdots,[1,n]$，找到最后一个不增加逆序对数的位置，该位置就是答案。但是代价 $1^2+2^2+\cdots+(n-1)^2=\frac{n(n-	1)(2n-1)}{6}=\mathcal O(n^3)$,显然过不去。

#### 优化

拜谢 @[Gold14526](https://www.luogu.com.cn/user/345930) 的做法。

不能直接求出整个序列的最大值，那么可以先分成一些规模较小的子问题计算并合并。

可以考虑分块，先把序列分为 $\sqrt n$ 个块，在每个块中如上文所说求出每个块内的最大值，代价复杂度 $\mathcal O((\sqrt n)^3 \times \sqrt n) = \mathcal O(n^2)$，然后使用判定定理在 $\sqrt n$ 个最大值位置中求出最大值，代价复杂度 $(\sqrt n)^2+(2\sqrt n)^2+\cdots+(\sqrt n \times \sqrt n)^2 = \mathcal O(n^2\sqrt n)$,还是不够优秀。

#### 正解

既然分块的做法不够优秀，我们考虑更优秀的分治。

把区间 $[l,r]$ 分成 $[l,mid]$ 和 $[mid+1,r]$ 两个区间，分别求出两个区间的最大值位置 $p_l,p_r$，然后根据判定定理，在这两个待选位置中求出整个 $[l,r]$ 的最大值位置。

具体方法就是层层递归分治，合并时判断 $p_r$ 是否是区间 $[l,p_r]$ 的最大值位置，如果是，由于分治说明了 $p_r$ 是区间 $[mid+1,r]$ 最大值位置，则整个 $[l,r]$ 的最大值位置就是 $p_r$，否则，最大值位置就是 $p_l$。

代价复杂度：$T(n)=2T(n/2)+\mathcal O(n^2)$，由主定理得，$T(n)=O(n^2)$。代价复杂度自带 $2$ 倍常数，合并时需要询问两个位置，又是 $2$ 倍常数，完全可以在 $5n^2$ 的限制下通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
int Query(int l,int r)
{
    printf("? %d %d\n",l,r),fflush(stdout);
    int res;
    scanf("%d",&res);
    return res;
}
int Solve(int l,int r)
{
    if(l==r) return l;
    if(l+1==r) return Query(l,r)?l:r;
    int posl=Solve(l,l+r>>1),posr=Solve((l+r>>1)+1,r);
    return Query(l,posr-1)==Query(l,posr)?posr:posl;
}
signed main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("! %d\n",Solve(1,n)),fflush(stdout);
    }
    return 0;
}
```


---

## 作者：Xy_top (赞：7)

完全没看题解，瞎写了个 CDQ 居然过了？？？

设 $\operatorname{cdq}(l,r)$ 为查询 $l$ $r$ 中的最大值，设 $mid=\lfloor\frac{l+r}{2}\rfloor$，求出 $l\cdots mid$ 和 $mid+1 \cdots r$ 之间的最大值后，考虑如何合并。

其实很简单，假如说最大值的位置分别是 $x$ $y$，查询一下 $x\cdots y$ 中的逆序对和 $x\cdots y - 1$ 中的逆序对数量是否相等即可，相等说明 $y$ 最大，符合。

加了个记忆化，本来以为 $n$ 在第一个位置是会爆掉，没想到不仅没爆还过了就离谱了！

```cpp
#include <map>
#include <iostream>
using namespace std;
int T, n, ans;
map <pair <int, int>, bool> mem;
map <pair <int, int>, int> f;
int ask (int l, int r) {
	if (l == r) return 0;
	if (mem[make_pair (l, r)]) return f[make_pair (l, r)];
	mem[make_pair (l, r)] = 1;
	cout << "? " << l << ' ' << r << '\n';
	fflush (stdout);
	int x;
	cin >> x;
	f[make_pair (l, r)] = x;
	ans += (r - l) * (r - l);
	return x;
}
int cdq (int l, int r) {
	if (l == r) return l;
	int mid = l + r >> 1;
	int x = cdq (l, mid);
	int y = cdq (mid + 1, r);
	if (ask (x, y) == ask (x, y - 1) ) return y;
	return x;
}
int main () {
	cin >> T;
	while (T --) {
		mem.clear ();
		f.clear ();
		cin >> n;
		cout << "! " << cdq (1, n) << '\n';
	}
	return 0;
}
```

---

## 作者：happybob (赞：4)

考虑数 $n$  的另一个性质。

由于是一个排列，所以 $n$ 是排列中的最大值！

我们考虑最大值的性质。

区间 $[l,r]$ 的最大值所在位置 $x$ 一定有这样的性质，$[l,x-1]$ 的逆序对个数和 $[l,x]$ 逆序对数相同。

考虑分治。设 $f(l,r)$ 为 $[l,r]$ 中最大值所在位置。分治合并时，最大值一定在两边最大值中的一个。用上述判断方式即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

const int N = 2005;

int t, n;

int query(int l, int r)
{
	printf("? %d %d\n", l, r);
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return x;
}

int solve(int l, int r)
{
	if (l == r) return l;
	if (l == r - 1)
	{
		return (query(l, r) == 1 ? l : r);
	}
	int mid = l + r >> 1;
	int place1 = solve(l, mid), solve2 = solve(mid + 1, r);
	return (query(l, solve2 - 1) == query(l, solve2) ? solve2 : place1);
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		printf("! %d\n", solve(1, n));
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：3)

我们只需要确定 $[1,n]$ 中最大值的位置，而我们只能询问区间的逆序对。

我们尝试确定一个区间最大值的位置。设 $f(l,r)$ 就表示 $[l,r]$ 之间的最大值。然后我们直接进行分治，$f(l,r)=f(l,m)$ 或者 $f(m+1,r)$。

我们需要确定这两个到底哪个大？设 $f(l,m)=p$，$f(m+1,r)=q$，我们先进行询问 `? p q`，设为 $x$，再问 `? p+1 q`，设为 $y$，容易发现，如果 $x=y+p-q$，则 $p$ 为较大，反之 $q$ 为较大。因为如果 $p$ 较大则它会与后面的 $p-q$ 个数形成逆序对。值得一提的是需要特判 `p+q==q`。

这么做的复杂度如何保证呢，我们尝试计算其量级。

对于 $f(l,r)$，它的运算量级为 $2(r-l)^2$，然后分治下去。

设 $g(l,r)$ 表示花费，$g(l,r)=g(l,m)+g(m+1,r)+2(r-l)^2$

我们发现，$2(\lfloor \dfrac n 2\rfloor)^2<(r-l)^2$，同样的，递归下去会有 $<\dfrac 1 2(r-l)^2$，$<\dfrac 1 4(r-l)^2$……直到 $f(pos,pos)$，此时为 $g(pos,pos)=0<4$。

所以其量级就是 $4n^2$，可以通过。

```cpp
#include <bits/stdc++.h>
#define cl() fflush(stdout);
using namespace std;
int p,q,t,n;
inline int more(int l,int r)
{
	printf("? %d %d\n",l,r);
	cl();scanf("%d",&p);
	if(l+1==r)q=0;
	else
	{
		printf("? %d %d\n",l+1,r);
		cl();scanf("%d",&q);
	}
	return p==q+r-l?l:r;
}
inline int f(int l,int r)
{
	if(l==r) return l;
	int m=l+r>>1,x,y;
	x=f(l,m);y=f(m+1,r);
	return more(x,y);
}
int main()
{
	scanf("%d",&t);
	while(t--){scanf("%d",&n);printf("! %d\n",f(1,n));cl();}
	return 0;
}
```

---

## 作者：KingPowers (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1856D)

赛时没过的选手来补题解了。

我们考虑一个排列的最大值该如何和逆序对扯上关系。假设对于一个排列 $p$，它的最大值的位置为 $pos$，那么区间 $[1,pos-1]$ 和 $[1,pos]$ 的逆序对数一定相等，因为 $[1,pos-1]$ 的数都比最大值要小，不可能会对逆序对数产生贡献。

同时，$\forall r>pos$，我们也有 $[1,r]$ 的逆序对数一定大于 $[1,r-1]$ 的逆序对数，因为第 $pos$ 个数为最大值，一定能和第 $r$ 个数形成一个新的逆序对。

得出结论：一个排列的最大值的位置为最后一个满足 $[1,pos]$ 的逆序对个数与 $[1,pos-1]$ 相同的 $pos$。

直接按照结论从小到大枚举最大值的位置，代价为 $O(n^3)$，显然过不去。

事实上，我们可以将上面的结论推广到每一个区间，因此可以考虑分治。

记 $solve(l,r)$ 表示区间 $[l,r]$ 的最大值的位置，假设我们已经求出了 $[l,mid]$ 的答案 $pl$ 和 $[mid+1,r]$ 的答案 $pr$，询问 $[1,pr-1]$ 的逆序对数是否和 $[1,pr]$ 相同，如果是答案为 $pr$，否则答案为 $pl$。

估计下这么做的贡献：注意到分治的结构类似于线段树，贡献乘 $2$；对于每个 $[l,r]$ 我们需要询问两次，贡献乘 $2$。因此总贡献大概在 $4n^2$ 的级别，可以通过。

```cpp
int query(int l,int r){
    cout<<"? "<<l<<' '<<r<<'\n';
    cout.flush();
    int x;cin>>x;
    return x;
}
int solve(int l,int r){
    if(l==r) return l;
    if(l==r-1) return query(l,r)?l:r;
    int mid=(l+r)>>1,pl,pr;
    pl=solve(l,mid);pr=solve(mid+1,r);
    return query(l,pr-1)==query(l,pr)?pr:pl;
}
void Main(){
    int n;cin>>n;
    cout<<"! "<<solve(1,n)<<'\n';
    cout.flush();
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T=1;cin>>T;
    while(T--) Main();
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：1)

**【题目大意】**

交互题，给定一个排列 $p$，每次可以询问区间 $[l,r]$ 的逆序对数量，代价是 $(r-l)^2$。要求你在不超过 $5n^2$ 的代价内得到最大值的下标。

**【题目分析】**

很巧妙的分治。

首先注意到一个区间内最大值一定有一个性质：设区间 $[l,r]$ 最大值位置是 $x$，那么一定有区间 $[l,x-1]$ 和 $[l,x]$ 逆序对数量相等，因为最大值不可能和前面的位置产生逆序对。

因此我们有了一个 naive 的想法：从后往前扫，如果扫到位置 $i$ 使得 $[1,i]$ 和 $[1,i-1]$ 的逆序对数量相等，那么 $i$ 就是最大值。但是计算一下最劣代价为 $\sum\limits_{i=1}^n(i-1)^2 \ge 5n^2$，会获得 WA 的好成绩。因此考虑优化。

我们采用分治的思想。将区间 $[l,r]$ 分成两个区间 $[l,mid]$ 和 $[mid+1,r]$，显然 $[l,r]$ 的最大值一定是这两个区间最大值的其中之一。我们只需要两次询问，结合子区间的信息就能确定这个区间的信息。**要注意，当 $l=r$ 时不能询问**。

可以证明这样分治的代价不会超过 $4n^2$。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
int ask(int l,int r){if(l == r) return 0;cout << "? " << l << " " << r << endl,cin >> k;return k;}
int f(int l,int r){
    if(l == r) return l;int mid = (l + r) / 2;
    int p1 = f(l,mid),p2 = f(mid+1,r);
    return (ask(p1,p2-1) == ask(p1,p2) ? p2 : p1);
}
int main(){
    for(cin >> t;t --;) {cin >> n;int ans = f(1,n);cout << "! " << ans << endl;}
}
```

---

## 作者：MatrixGroup (赞：1)

## 题意

给定一个长度为 $n$ 的排列 $p$，可以花费 $(r-l)^2$ 的代价询问 $f(l,r)$ 为区间 $[l,r]$ 的逆序对数。请花费不超过 $5n^2$ 的代价，求出区间最大值的位置。**交互库不自适应**。

## 题解

考虑一个朴素的分治。假如要求出区间 $[l,r]$ 的答案，那么令 $m=\left\lfloor\dfrac{l+r}{2}\right\rfloor$，先求出 $[l,m]$ 和 $(m,r]$ 的答案。我们可以这样比对两个数 $p_x,p_y$ 的大小：计算 $f(x,y)-f(x,y-1)-f(x+1,y)+f(x+1,y-1)$ 是 $0$（$p_x<p_y$）还是 $1$（$p_x>p_y$）。这可以通过容斥证得。

这样代价最大是 $F(n)=4n^2+2F(\dfrac{n}{2})=8n^2$，无法通过。

注意到交互库不自适应，考虑随机化。先随机选择 $l'=l,r'=m$ 还是 $l'=m+1,r'=r$ 询问 $[l',r']$ 的答案 $x$。如果 $x$ 比另一个区间所有数都大，就直接返回，否则查询另一个区间的答案。查询「一个数是否比另一个区间的所有数都大」可以类似求得，而且只需要 $n^2+n^2+(0.5n)^2+(0.5n)^2=2.5n^2$ 的代价，因此期望代价 $G(n)=1.5G(\dfrac{n}{2})+2.5n^2=2.5(\sum\limits_{i=0}^{+\infty}0.375^i)n^2=4n^2$。实际测试不超过 $4.97n^2$ 的代价，可以通过。

---

## 作者：buaa_czx (赞：0)


## 题意

有一个长度为 $n$ 的未知序列，询问 $l,r$ 可以通过花费 $r-l$ 个金币获取 $l$ 到 $r$ 之间逆序对的个数。你需要花费不多于 $5n^2$ 个金币来找到序列中最大数的个数。

## 思路

用分治来解决。如果询问的区间长度小于等于 $2$，很容易通过至多一次询问找到小区间中的最大数位置，否则二分后向下分治。这样，我们可以得到一个区间两个部分的最大数位置 $maxl,maxr$，问题变成如何判断这两个数哪个更大。

考虑区间 $[maxl,maxr]$，$maxl,maxr$ 之中对应数最大的那个显然也会是这个区间中的最大数。如果 $maxr$ 对应的数是区间中的最大数，那么区间 $[maxl,maxr]$ 中逆序对的数量会和 $[maxl,maxr-1]$ 中逆序对的数量相同。否则 $maxl$ 对应的数是区间中的最大数。

## 代码

```cpp
int n;
int query(int l, int r) {
    if (l == r)
        return 0;
    cout << "? " << l << " " << r << endl;
    cout.flush();
    int x;
    cin >> x;
    return x;
}
int f(int l, int r) {
    if (l == r)
        return l;
    if (l + 1 == r) {
        int x = query(l, r);
        if (x)
            return l;
        else
            return r;
    }
    int maxl = f(l, (l + r) / 2), maxr = f((l + r) / 2 + 1, r);
    if (query(maxl, maxr) == query(maxl, maxr - 1))
        return maxr;
    else
        return maxl;
}
void solve() {
    cin >> n;
    int res = f(1, n);
    cout << "! " << res << endl;
    cout.flush();
}
```

---

## 作者：TernaryTree (赞：0)

显然 $n$ 是一个排列的最大值。我们需要找到排列的最大值。

假设我们已经分别找到了 $[l,mid]$ 和 $[mid+1,r]$ 的最大值位置 $p$ 和 $q$。如果 $a_p<a_q$，这意味着 $[l,q-1]$ 的所有数 $<a_q$。也就是 $[l,q-1]$ 的逆序对个数与 $[l,q]$ 个数是相同的，这两者是可以相互转化的。否则 $a_p>a_q$。

这样我们就能分治下去做了。

贡献是 $4n^2$。

---

## 作者：LimpidSlirm (赞：0)

## 题意

**交互题**，交互库中有一个长度为 $n$ 的排列 $a$，每次可以花费 $(r-l)^2$ 的代价向交互库询问区间 $[l,r]$ 内的逆序对个数。

在总花费不超过 $5\times n^2$ 的前提下找出排列 $a$ 中最大值的位置。

## Solution

考虑分治，对于每个区间找出其最大值 $max$ 的位置。由于题目保证为排列，对于左右区间的最大值 $x$ 和 $y$，可以发现有如下性质：如果区间 $[x,y]$ 内的逆序对个数和区间 $[x,y-1]$ 内的逆序对个数相同，则表示 $y$ 对于区间 $[x,y]$ 内没有贡献，即区间 $[x,y-1]$ 内的数均小于 $y$。故 $y$ 为区间最大值，否则 $x$ 为区间最大值。

总代价表达式为 
$$
cost(n)=cost(\frac{n}{2})+(n-1)^2+(n-2)^2
$$

$$
\le cost(\frac{n}{2})+2\times n^2
$$

由主定理：
$$
cost(n)\leq 4\times n^2
$$
时间复杂度为 $\mathcal{O}(n \log n)$，代价小于等于 $4\times n^2$，可以通过本题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
int query(int left,int right)
{
	if(left==right)
		return 0;
	printf("? %d %d\n",left,right);
	cout.flush();
	return read();
}
int solve(int left,int right)
{
	if(left==right)
		return left;
	int mid=(left+right)>>1;
	int a=solve(left,mid);
	int b=solve(mid+1,right);
	if(query(a,b-1)==query(a,b))
		return b;
	return a;
}
int main(int argc,const char *argv[])
{
	int T=read();
	while(T--)
	{
		int n=read();
		printf("! %d\n",solve(1,n));
		cout.flush();
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

直接求最大值不好求。我们可以采用一个交互常见的套路，维护可能的答案集合 $S$，每次剔除掉一些。

考虑初始把 $a_{i - 1} < a_i > a_{i + 1}$ 的 $i$ 加入 $S$，每次取出 $S$ 中差最小的一对元素 $i, j$，那么若 $a_i > a_j$，$a_i$ 就大于 $[i + 1, j]$ 的所有元素，也就是 $[i, j]$ 与 $[i + 1, j]$ 的逆序对之差为 $j - i$，此时我们删除 $j$，否则删除 $i$。

使用的金币数不超过 $n + 2\sum\limits_{i = 1}^n (\frac{n}{i})^2 < 4n^2 + n$，可以通过。

[code](https://codeforces.com/contest/1856/submission/217388168)

---

