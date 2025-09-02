# Cut and Stick

## 题目描述

Baby Ehab has a piece of Cut and Stick with an array $ a $ of length $ n $ written on it. He plans to grab a pair of scissors and do the following to it:

- pick a range $ (l, r) $ and cut out every element $ a_l $ , $ a_{l + 1} $ , ..., $ a_r $ in this range;
- stick some of the elements together in the same order they were in the array;
- end up with multiple pieces, where every piece contains some of the elements and every element belongs to some piece.

More formally, he partitions the sequence $ a_l $ , $ a_{l + 1} $ , ..., $ a_r $ into subsequences. He thinks a partitioning is beautiful if for every piece (subsequence) it holds that, if it has length $ x $ , then no value occurs strictly more than $ \lceil \frac{x}{2} \rceil $ times in it.

He didn't pick a range yet, so he's wondering: for $ q $ ranges $ (l, r) $ , what is the minimum number of pieces he needs to partition the elements $ a_l $ , $ a_{l + 1} $ , ..., $ a_r $ into so that the partitioning is beautiful.

A sequence $ b $ is a subsequence of an array $ a $ if $ b $ can be obtained from $ a $ by deleting some (possibly zero) elements. Note that it does not have to be contiguous.

## 说明/提示

In the first query, you can just put the whole array in one subsequence, since its length is $ 6 $ , and no value occurs more than $ 3 $ times in it.

In the second query, the elements of the query range are $ [3,2,3,3] $ . You can't put them all in one subsequence, since its length is $ 4 $ , and $ 3 $ occurs more than $ 2 $ times. However, you can partition it into two subsequences: $ [3] $ and $ [2,3,3] $ .

## 样例 #1

### 输入

```
6 2
1 3 2 3 3 2
1 6
2 5```

### 输出

```
1
2```

# 题解

## 作者：Lynkcat (赞：12)

简单数据结构题，看起来比 $C$ 要简单。

考虑这么一个问题，如果我们要把区间分成若干个块的话肯定要抵完，也就是说如果花费 $x$ 个非众数，那么抵掉 $x+1$ 个众数是最优的。

但是，我们发现它如果不固定 $x$ 就不一定抵得完。

我们考虑一种一定抵得完的方案：

假设原来分成了 $(x,x+1)$ 和 $(y,y+1)$ ，显然可以合并成 $(x+y,x+y+1),(0,1)$  的形式，也就是说，合并两个组是并不影响组数的大小的！

那么我们可以考虑只分一组把所有非众数分完，多出来的众数每个都自成一组即可。

至于求区间众数的出现次数，我用的是主席树，考虑这道题只要求绝对众数的出现次数那么我们设 $k=r-l+1$ 反正如果 $s[left]<k$ 的话显然只有走右儿子才有可能得到绝对众数，否则只有走左儿子才可能得到绝对众数。

---

## 作者：JasonL (赞：6)

### CF1514D Cut and Stick

[题目传送门](https://www.luogu.com.cn/problem/CF1514D)

#### 题目分析

提供一个简单的线段树 + $vector$ 做法。

首先，问题转化成求区间众数以及众数的出现次数。

如果区间众数的出现次数不超过 $\left\lceil\frac{n}{2}\right\rceil$ ，那么答案为 $1$ （直接选中所有数）。

否则，假设众数的出现次数为 $s$ 。 我们可以先分出一个区间，把所有不是众数的数丢进去。然后把众数尽可能多地丢进去，数量为 $n-s+1$ （此时区间的大小是个奇数，恰好满足条件）。剩下的众数单个单个一组。答案为 $1+(s-(n-s+1))$ 。

摩尔投票法可以求出一段序列内出现次数超过一半的众数，而算法只在序列内存在这样的众数时才正确。然而当算法不正确时，众数出现的次数一定不大于 $\left\lceil\frac{n}{2}\right\rceil$ ，此时答案为 $1$ 。所以我们只需要检验摩尔投票法得到的众数在区间内的出现个数是否确确实实大于 $\left\lceil\frac{n}{2}\right\rceil$ 。而这可以通过 $vector$ 解决。

摩尔投票法是 $O(n)$ 的，支持合并。因而我们可以在线段树上进行摩尔投票法。时间复杂度 $O(n\log n)$ 。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define mid ((l+r)>>1)
using namespace std; 
const int maxn=301000;
int n,q;
int a[maxn];
vector <int> v[maxn];
struct Node{
	int p,c;
	Node(){
		p=c=0;
	}
	Node(int x){
		p=x;c=1;
	}
	Node operator +(Node b)const{
		Node res;
		if(p==b.p)res.p=p,res.c=c+b.c;
		else if(c<b.c)res.p=b.p,res.c=b.c-c;
		else res.p=p,res.c=c-b.c;
		return res;
	}
};
struct Segment_Tree{
	int rt,ver,son[2][maxn<<1];
	Node w[maxn<<1];
	void build(int &p,int l,int r){
		p=++ver;
		if(l==r){
			w[p]=Node(a[l]);return;
		}
		build(son[0][p],l,mid);
		build(son[1][p],mid+1,r);
		w[p]=w[son[0][p]]+w[son[1][p]];
	}
	Node query(int p,int lr,int rr,int l,int r){
		if(lr<=l&&r<=rr)return w[p];
		if(lr>r||l>rr)return Node();
		return query(son[0][p],lr,rr,l,mid)+query(son[1][p],lr,rr,mid+1,r);
	}
}T1;
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
int main(){
	n=read();q=read();
	for(register int i=1;i<=n;++i){
		a[i]=read();
		v[a[i]].push_back(i);
	}
	T1.build(T1.rt,1,n);
	for(register int i=1,l,r,x;i<=q;++i){
		l=read();r=read();
		Node w=T1.query(T1.rt,l,r,1,n);
		x=lower_bound(v[w.p].begin(),v[w.p].end(),r+1)-lower_bound(v[w.p].begin(),v[w.p].end(),l);
		if(x<=(r-l+2)/2)puts("1");
		else{
			x=1+(x-(r-l+1-x+1));
			printf("%d\n",x);
		}
	}
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：6)

对于 $n$ 个数的区间 , 考虑出现次数最多的任一数 $X$ 的数量为 $x$ , 剩下的数 $n - x$。  
若 $x \leqslant n - x + 1$  
划分的意义在于 , 每多分出一组数 , 就能多容纳一个 $X$ , 那么一个能满足的方案显然是把多余 $X$ 分成单个数的一组。  
这样答案就变成了 $\max(1, 2x - n + 1)$ 。  
要求区间众数？不会。  
实际上如果众数出现次数少于一半根本不需要划分 , 只需要求多于一半的情况的众数 , 主席树维护一下在线段树上非常好求 , 代码还很短 , 查询复杂度 $\mathcal{O(\sqrt n)} \to \mathcal{O(\log n)}$。  
```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int sz = 1e7 + 10, maxn = 3e5 + 10;
int dat[sz], ls[sz], rs[sz], tot;
void insert(int &p, int pre, int lp, int rp, int x, int v) {
    if(!p) p = ++tot;
    if(lp == rp) { dat[p] = dat[pre] + v; return ; }
    int mid = (lp + rp) >> 1;
    if(x <= mid) rs[p] = rs[pre], insert(ls[p], ls[pre], lp, mid, x, v);
    else ls[p] = ls[pre], insert(rs[p], rs[pre], mid+1, rp, x, v);
    dat[p] = dat[ls[p]] + dat[rs[p]];
}
 
int qry(int pl, int pr, int lp, int rp) {
    if(lp == rp) return dat[pr] - dat[pl];
    int mid = (lp + rp) >> 1;
    if(dat[ls[pr]] - dat[ls[pl]] < dat[rs[pr]] - dat[rs[pl]]) return qry(rs[pl], rs[pr], mid + 1, rp);
    return qry(ls[pl], ls[pr], lp, mid);
}
 
int a[maxn], rt[maxn];
 
int main() {
    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), insert(rt[i], rt[i-1], 1, n, a[i], 1);
    for(int qr = 1; qr <= q; ++qr) {
        int l, r; scanf("%d %d", &l, &r);
        int su = qry(rt[l-1], rt[r], 1, n);
        printf("%d\n", max(su-((r-l+1)-su+1)+1,1));
    }
    return 0;
}
```


---

## 作者：Brilliant11001 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/CF1514D)


------------


## 大致题意：

给出长度为 $n$ 的序列 $A$，同时给出 $m$ 次询问至少要将区间 $[l,r]$ 分成多少段，才能使每段中没有数的出现次数 $> \lceil \frac{len}{2} \rceil$。

## 分析：

首先，如果连该区间的众数的出现次数都 $\le \lceil \frac{len}{2} \rceil$，那么只用分 $1$ 段就行了。

对于剩下的情况，我们就要想办法将非众数与众数组合，并且用尽量少的非众数去搭配尽量多的众数组成一段，然后剩下的众数就只能一一分段了。

很容易发现，此时最优的策略是：**选择 $x - 1$ 个非众数与 $x$ 个众数组队。**

画个图就懂了：

![](https://cdn.luogu.com.cn/upload/image_hosting/72q3i8y4.png)

如图，蓝色框起来的部分表示分成一段，这时是最优策略，即划分段数最小。

由图可知：设众数有 $x$ 个，则非众数有 $len - x$ 个，其中 $len$ 为区间长度。

此时的答案为 $x - (len - x + 1) + 1 = 2 x - len$。

所以问题就转化成了：维护一个序列 $A$，静态求区间众数个数。

这个问题可以用可持久化线段树（主席树）来做（其实就是主席树的模板了）。

$\texttt{Code}$：
```cpp
#include <iostream>

using namespace std;

const int N = 500010;

int n, m;
struct node{
	int ls, rs;
	int cnt;
}tr[N << 5];
int root[N], idx;

int insert(int p, int l, int r, int pos) {
	int q = ++idx;
	tr[q] = tr[p];
	tr[q].cnt++;
	if(l == r) return q;
	int mid = l + r >> 1;
	if(pos <= mid) tr[q].ls = insert(tr[p].ls, l, mid, pos);
	else tr[q].rs = insert(tr[p].rs, mid + 1, r, pos);
	return q;
}

int query(int p, int q, int l, int r) {
	if(l == r) return tr[q].cnt - tr[p].cnt;
	int mid = l + r >> 1;
	int lcnt = tr[tr[q].ls].cnt - tr[tr[p].ls].cnt;
	int rcnt = tr[tr[q].rs].cnt - tr[tr[p].rs].cnt;
	if(lcnt > rcnt) return query(tr[p].ls, tr[q].ls, l, mid); 
    //若左子区间出现次数大于一半，就走到左子树上
	else return query(tr[p].rs, tr[q].rs, mid + 1, r); 
    //否则走到右子树上
}

int main() {
	scanf("%d%d", &n, &m);
	int a;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a);
		root[i] = insert(root[i - 1], 1, n, a);
	}
	int l, r;
	while(m--) {	
		scanf("%d%d", &l, &r);
		int len = r - l + 1;
		int tmp = query(root[l - 1], root[r], 1, n);
		printf("%d\n", max(1, (tmp << 1) - len));
	}
	return 0;
}
```

---

## 作者：zmx_wzx_JY (赞：4)

这个解法要绕一些，但是理论上可以做到比莫队优秀很多的复杂度。

~~场上以为莫队过不了，就想了 1w 年。~~

首先打一打表发现若长度为 $len$, 众数个数为 $x$，那么答案是 $max(2x-len,1)$。

注意到如果众数小于一半，就直接输出 1 即可。

否则，我们不断随机序列中的位置，并查询这个位置上的值在区间中出现次数是否超过一半。有的话就是要求的数，如果连续随 25 次都找不到就可以认为没有出现次数超过一半的数。

显然存在超过一半的数，一次找到的概率不小于 0.5，那么该算法的错误率只有 $0.5^{25}$~$0$。

然后就是如何查询一个区间中某个颜色的个数，可以离线做到 $O(1)$，也可以在线 $O(logn)$。

总复杂度 $O(n+25q)$ 或 $O(n+25qlogn)$。

考场代码（复杂度是后者）：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Rep(i,x,y) for(int i = (x), stOxrj = (y); i<=stOxrj; ++i)
#define Irep(i,x,y) for(int i = (x), stOxrj = (y); i>=stOxrj; --i)
#define vec vector<int>
#define IT iterator
#define pb push_back
#define il inline
#define ci const int&
using namespace std;
inline int read(){
	int res = 0; char c = getchar(); 
	while( c<'0' || c>'9' ) c = getchar();
	while( c>='0' && c<='9' ) res = res * 10 + c - '0', c = getchar();
	return res;
}
const int N = 3e5 + 20;
int n,q;
struct SHR{
	vec a; int flg = 0;
	void ins(int x){ a.pb(x); }
	int ask(int l,int r){
		if( !flg ) flg = 1, a.pb(n + 1);
		return upper_bound(a.begin(), a.end(), r) - lower_bound(a.begin(), a.end(), l);
	}
}b[N];
int va[N];
int get(int l,int r){
	LL x = rand() * rand();
	return x % ( r - l + 1 ) + l; 
} 
int solve(int l,int r){
	int lent = r - l + 1;
	Rep(i,1,25){
		int t = get(l, r);
		int num = b[va[t]].ask(l, r); 
		if( num * 2 >= lent ) return num;
	} 
	return 0;
}
signed main(){
	srand(time(0));	
	n = read(), q = read();
	Rep(i,1,n) b[va[i] = read()].ins(i);
	while( q-- ){
		int l = read(), r = read();
		int x = solve(l, r), lent = r - l + 1;
		if( (lent+1) / 2 >= x ) { puts("1"); continue; }
		printf("%d\n", x + x - lent ); 	
	}
	return 0;
}
```
原题解大概也是这个意思

---

## 作者：ax_by_c (赞：3)

对于一个长度为 $n$ 的询问区间，如果这个区间的众数的出现次数不超过 $\lceil \frac n 2 \rceil$，那么显然可以分成一个片段。

如果这个区间的众数的出现次数超过了 $\lceil \frac n 2 \rceil$ 怎么办呢？

设区间的众数的出现次数为 $x$，则区间内非众数的个数应为 $n-x$。如果说要把这两部分分开处理的话，众数就只能一个数分一段了。

所以如果我们把所有非众数放在一段里，并加入尽量多的众数，应该是最优的。

那么能加入多少众数呢？

显然是 $n-x+1$ 个。

此时，还有 $x-(n-x+1)$ 个众数剩余。

那剩余的众数呢？

就只能一个分一段了。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
const int SQN=1e3+5;
int n,m;
int a[N];
int sqn;
int bl[SQN],br[SQN];
int col[N];
struct Q
{
	int l,r,id;
};
Q q[N];
int ls[N],rs[N];
bool cmp(Q a,Q b)
{
	if(col[a.l]==col[b.l])
	{
		return a.r<b.r;
	}
	return a.l<b.l;
}
int bf[N],ct[N];
int l,r;
int as;
int lst;
int ans[N];
int ns,nl;
int main()
{
	scanf("%d %d",&n,&m);
	sqn=sqrt(n);
	for(int i=1;br[i-1]!=n;i++)
	{
		bl[i]=br[i-1]+1;
		br[i]=bl[i]+sqn-1;
		if(br[i]>n)
		{
			br[i]=n;
		}
		for(int j=bl[i];j<=br[i];j++)
		{
			col[j]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&ls[i],&rs[i]);
		q[i].l=ls[i];
		q[i].r=rs[i];
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		if(col[q[i].l]==col[q[i].r])
		{
			int res=0;
			for(int j=q[i].l;j<=q[i].r;j++)
			{
				bf[a[j]]++;
				res=max(res,bf[a[j]]);
			}
			for(int j=q[i].l;j<=q[i].r;j++)
			{
				bf[a[j]]=0;
			}
			ans[q[i].id]=res;
			continue;
		}
		if(col[q[i].l]!=lst)
		{
			for(int j=1;j<=n;j++)
			{
				ct[j]=0;
			}
			lst=col[q[i].l];
			l=br[col[q[i].l]]+1;
			r=br[col[q[i].l]];
			as=0;
		}
		while(r<q[i].r)
		{
			r++;
			ct[a[r]]++;
			as=max(as,ct[a[r]]);
		}
		ns=as;
		nl=l;
		while(q[i].l<nl)
		{
			nl--;
			ct[a[nl]]++;
			ns=max(ns,ct[a[nl]]);
		}
		while(nl<l)
		{
			ct[a[nl]]--;
			nl++;
		}
		ans[q[i].id]=ns;
	}
	int len,fx;
	for(int i=1;i<=m;i++)
	{
		len=rs[i]-ls[i]+1;
		fx=(int)(ceil((double)(len)/2.0));
		if(ans[i]<=fx)
		{
			printf("1\n");
		}
		else
		{
			printf("%d\n",1+(ans[i]-(len-ans[i]+1)));
		}
	}
	return 0;
}
```

---

## 作者：tai_chi (赞：2)

~~[不知道会不会更不好的阅读体验](https://www.cnblogs.com/tai-chi/p/18349516)~~

题目的关键步骤为**求出区间绝对众数（频率高于 $\left \lceil \frac{len}{2} \right \rceil$）的出现次数**，本文仅仅对这一问题进行探讨，剩余的解题步骤不难理解，可以参考其他题解。

### 解法 1

考虑一个随机化的解法，从区间中随 $40$ 个数，假定其为区间绝对众数，然后对所有的情况取频率最大的那个。

若区间绝对众数存在，其一次被选中的概率为 $\frac{1}{2}$，$40$ 次被选中过的概率则为 $1-2^{-40}$，错误概率极小，可以接受。

区间统计一个数字的出现次数也并不需要 $O(n)$ 遍历，注意到值域不大，我们对每个值开一个 `vector` 记录它所有出现的下标，则区间出现次数只需要二分左右端点：

```cpp
upper_bound(r) - lower_bound(l)
```

[code](https://codeforces.com/contest/1514/submission/274698565)

这样我们用 $O(n \log n)$ 的时间复杂度解决了问题，但是带一个 $40$ 的常数，跑起来可能和根号差不多。

### 解法 2

**前置知识：[摩尔投票](https://oi-wiki.org/misc/main-element/#%E6%91%A9%E5%B0%94%E6%8A%95%E7%A5%A8%E7%AE%97%E6%B3%95)。**

在做摩尔投票的过程中，我们维护了两个变量 $val,cnt$。既然题目涉及区间查询，我们考虑把这两个值丢到线段树上。

在合并左右区间信息时，若左右区间的投票均选出一个 $val$，则合并后的区间 $val$ 不变，$cnt$ 加和。否则选出 $cnt$ 更大的并把另一个区间的负贡献加入。

时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/contest/1514/submission/275217135)

---

## 作者：Ryo_Yamada (赞：1)

#### 题目描述

对于一个序列，你有两种操作：

- 将一个序列的一个子段 $[l,\,r]$ 截下来，成为另一个序列。
- 将两个序列合并成一个序列，保留两个原序列的数字顺序。

同时，要求一个 $n$ 个数的序列中不能有任意一个值出现次数超过 $\lceil \dfrac{n}{2} \rceil$。

有 $q$ 次询问，每次询问一个区间 $[l,\,r]$，问最少将这个序列拆成几个序列才能使所有序列满足条件。

#### 题目解法

首先明确，题目不需要我们做到操作次数最小，所以我们可以把区间拆成 $n$ 个长度为 $1$ 的子序列，然后再拼起来，以达到目的。

对于一个区间 $[l,\,r]$，先求出它的区间众数。$n,\,q \leq 3 \times 10^5$，分块可过。不会的可以移步 [P5048](https://www.luogu.com.cn/problem/P5048)，或者写主席树静态区间第 $k$ 小。

设区间长度 $s=r-l+1$，如果这个众数在区间中出现次数 $\leq \lceil \dfrac{s}{2} \rceil$，则不需要拆分，输出 $1$。

否则，对于一个拆出来的序列，如果它包含 $x$ 个原序列中的区间非众数，则这个序列最多能包含 $x+1$ 个原序列中的区间众数。这也是最优的拆分方法。所以最终答案是 区间众数个数$-$区间非众数个数。

---

## 作者：WitheredZeal (赞：1)

## 题意

有一个长度为 $n$ 的序列和 $q$ 次询问，每次询问给出 $l,r$，你需要回答：  
在 $a_l,a_{l+1},\cdots a_r$ 中，至少要拆成几个子序列，才能使每个子序列都满足：设子序列长度为 $x$，且子序列中的每个数出现次数不超过 $\left\lceil \dfrac x 2 \right \rceil$。  


## 题解  
粗略一看，我们发现他大概和区间长度和区间众数出现次数有关。那么我们可以用回滚莫队或者把[这题](https://www.luogu.com.cn/problem/P5048) 代码搞过来。  
然后如果区间众数出现次数为 $x$，区间长度为 $len$，答案即为 $\max(1,2x-len)$。下面给出证明：  
如果 $x\le \left\lceil \dfrac {len} 2 \right \rceil$，答案显然为 1。  
否则区间众数是唯一的，为了方便我们设区间众数为 $a$。我们考虑，将 $k$ 个 $a$ 放在一个序列里，至少需要 $k-1$ 个不是 $a$ 的数。  
我们总共只有 $len-x$ 个不是 $a$ 的数。设把区间分成了 $t$ 个子序列，每个子序列有 $b_i$ 个 $a$，那么有 $\sum_{i=1}^t b_i=x,\sum_{i=1}^t (b_i-1) \le len-x$，于是有 $t \ge 2x-len$。

代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register signed
#define rd(x) x=read()
using namespace std;
const int N=5e5+5;
const int M=805;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline int ksm(int x,int y=mod-2,int z=mod){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
int sz;
int n,m,q,la,l,r;
int a[N],b[N],pos[N],L[N],R[N],bel[N],cnt[N];
int mx[M][M];
vector<int> p[N];
int solve(int len,int x)
{
	if (x<=(len+1)/2) return 1;
	return 2*x-len;
}
signed main()
{
    rd(n);rd(q);
    for (int i=1;i<=n;i++) rd(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);m=unique(b+1,b+n+1)-b-1;
    for (int i=1;i<=n;i++) {a[i]=lower_bound(b+1,b+m+1,a[i])-b;}
    for (int i=1;i<=n;i++) pos[i]=p[a[i]].size(),p[a[i]].push_back(i);
    sz=sqrt(n);
    for (int i=1;i<=n;i++) bel[i]=(i-1)/sz+1;m=bel[n];
    for (int i=1;i<=m;i++) L[i]=R[i-1]+1,R[i]=i*sz;R[m]=n;
    for (int i=1;i<=m;i++)
    {
        memset(cnt,0,sizeof(cnt));
        for (int j=i;j<=m;j++)
        {
            mx[i][j]=mx[i][j-1];
            for (int k=L[j];k<=R[j];k++) cnt[a[k]]++,mx[i][j]=max(mx[i][j],cnt[a[k]]);
        }
    }
    while (q--)
    {
        rd(l);rd(r);la=0;
        if (bel[l]==bel[r])
        {
            for (int i=l;i<=r;i++) cnt[a[i]]=0;
            for (int i=l;i<=r;i++) cnt[a[i]]++,la=max(la,cnt[a[i]]);
        } else 
        {
            la=mx[bel[l]+1][bel[r]-1];
            for (int i=l;i<=R[bel[l]];i++){int x=pos[i];while (x+la<p[a[i]].size() && p[a[i]][x+la]<=r) la++;}
            for (int i=L[bel[r]];i<=r;i++){int x=pos[i];while (x-la>=0 && p[a[i]][x-la]>=l) la++;}
        }
        cout<<solve(r-l+1,la)<<'\n';
    }
}
```


---

## 作者：可爱大黄兔 (赞：0)

注意到若区间内一个数 $x$ 出现次数 $cnt \geq \dfrac{len}{2}$，则它二进制下的第 $k$ 位 $a$ 的出现次数一定大于等于 $\dfrac{len}{2}$，因此我们可以以 $\mathcal{O}(q)$ 的复杂度解决这题。
 
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ret=0;
	char c=getchar(),ch=' ';
	while(!('0'<=c&&c<='9')) ch=c,c=getchar();
	while('0'<=c&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
inline void write(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
const int N=3*1e5+10;
int a[N];
int num[N];
int s[N][20];
vector<int> g[N];
int n,m;int x;
bool v[N];
int solve(int l,int r){
	int len=r-l+1;
	int x=0;
	for(int k=0;k<20;k++){
		int sum=s[r][k]-s[l-1][k];
		if((sum<<1)>len)x|=1<<k;
	}
	if(v[a[x]]==false){
		v[a[x]]=true;
		g[a[x]].push_back(n+1);	
	}
	int al=lower_bound(g[x].begin(),g[x].end(),l)-g[x].begin();
	int bl=upper_bound(g[x].begin(),g[x].end(),r)-g[x].begin();
	if((bl-al)*2 >= len){
		return bl-al;
	}
	return 0;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),g[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		for(int k=0;k<20;k++){
			s[i][k]=s[i-1][k];
			if(a[i]>>k & 1)s[i][k]++;
		}
	}
	while(m--){
		int l=read(),r=read(),len=r-l+1;
		int x=solve(l,r);
		if((len+1)/2>=x){
			puts("1");
		}else write(x+x-len),puts("");
		
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1514D)

# 前置知识

[可持久化线段树](https://oi-wiki.org/ds/persistent-seg/)

# 解法

若区间内不存在绝对众数，直接保持这一段即可。

若存在绝对众数，贪心地想肯定要尽可能地把其分开还要限制出其他数使其不成为绝对众数。容易发现设绝对众数出现次数为 $cnt$，取 $cnt-1$ 个其他数和绝对众数配对最优。但可能其他数不够 $cnt$ 个，就只能让多余的绝对众数各成一组了。最终答案即为 $2cnt-(r-l+1)$。

主席树求下是否存在绝对众数及其出现次数即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int a[300010];
struct PDS_SMT
{
	int root[300010],rt_sum;
	struct SegmentTree
	{
		int ls,rs,sum;
	}tree[300010<<5];
	#define lson(rt) tree[rt].ls
	#define rson(rt) tree[rt].rs
	int build_rt()
	{
		rt_sum++;
		return rt_sum;
	}
	void build_tree(int &rt,int l,int r)
	{
		rt=build_rt();
		if(l==r)
		{
			return;
		}		
		int mid=(l+r)/2;
		build_tree(lson(rt),l,mid);
		build_tree(rson(rt),mid+1,r);
	}
	void update(int pre,int &rt,int l,int r,int pos)
	{
		rt=build_rt();
		tree[rt]=tree[pre];
		tree[rt].sum++;
		if(l==r)
		{
			return;
		}
		int mid=(l+r)/2;
		if(pos<=mid)
		{
			update(lson(pre),lson(rt),l,mid,pos);
		}
		else
		{
			update(rson(pre),rson(rt),mid+1,r,pos);
		}
	}
	int query(int rt1,int rt2,int l,int r,int k)
	{
		if(l==r)
		{
			return tree[rt2].sum-tree[rt1].sum;
		}
		int mid=(l+r)/2;
		if(tree[lson(rt2)].sum-tree[lson(rt1)].sum>k)
		{
			return query(lson(rt1),lson(rt2),l,mid,k);
		}
		if(tree[rson(rt2)].sum-tree[rson(rt1)].sum>k)
		{
			return query(rson(rt1),rson(rt2),mid+1,r,k);
		}
		return 0;
	}
}T;
int main()
{
	int n,m,l,r,cnt,i;
	scanf("%d%d",&n,&m);
	T.build_tree(T.root[0],1,n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		T.update(T.root[i-1],T.root[i],1,n,a[i]);
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		cnt=T.query(T.root[l-1],T.root[r],1,n,(r-l+1)/2.0);
		if(cnt==0)
		{
			printf("1\n");
		}
		else
		{
			printf("%d\n",2*cnt-(r-l+1));
		}
	}
	return 0;
}
```

---

## 作者：C_Pos_Princess (赞：0)

## 题意
给定一个长为 $n$ 的序列 $A$ ，多次询问区间 $[l,r]$ ，你需要求：

最少将区间 $[l,r]$ 中的元素分成几个集合，使得每一个集合中出现次数最多的数的出现次数不超过该集合大小的一半（上取整）。
对于每次询问，输出这个最少的集合数。

## 题解
记区间长度 $len$。

首先，注意到，如果区间众数出现次数小于等于 $len/2$，那么答案是 1。

否则，假设区间非众数一共有 $x$ 个，那么直接让他带走 $x+1$ 个众数，剩下的众数每一个分一组，是最优的。

为什么不能把非众数分开带，这样会不会更优？

不会，因为就算把非众数分开带众数。假设分为两组，那么这两组带的众数会比一组带的多一个，那和把众数单独分一个没有区别。

值域主席树维护即可。

## 代码

```cpp
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
using namespace std;
int n, m;
struct node {
	int ls, rs;
	int cnt;
} tr[N << 5];
int root[N];
int idx;

int insert(int p, int l, int r, int pos) {
	int q = ++idx;
	tr[q] = tr[p];
	tr[q].cnt++;
	if (l == r) return q;
	int mid = l + r >> 1;
	if (pos <= mid) tr[q].ls = insert(tr[p].ls, l, mid, pos);
	else tr[q].rs = insert(tr[q].rs, mid + 1, r, pos);
	return q;
}

int query(int p, int q, int l, int r) {
	if (l == r) return tr[q].cnt - tr[p].cnt;
	int mid = l + r >> 1;
	int lcnt = tr[tr[q].ls].cnt - tr[tr[p].ls].cnt;
	int rcnt = tr[tr[q].rs].cnt - tr[tr[p].rs].cnt;
	if (lcnt > rcnt) return query(tr[p].ls, tr[q].ls, l, mid);
	else return query(tr[p].rs, tr[q].rs, mid + 1, r);

}


int main() {
	read(n, m);
	for(int i = 1;i<=n;i++){
		int a;
		read(a);
		root[i] = insert(root[i-1],1,n,a);
	}
	int l,r;
	while(m--){
		read(l,r);
		int len= r-l+1;
		int tmp = query(root[l-1],root[r],1,n);
		write(max(1,(tmp<<1)-len));
		LF;
	}

	return 0;
}
```

---

## 作者：dead_X (赞：0)

## 题意
给定序列 $n$，$m$ 次询问至少要将区间 $[l,r]$ 分成几段，才能让每段中不存在一个数出现了 $>\lceil\frac{len}{2}\rceil$ 次。

$n,m\leq 3\times 10^5$。
## 思路
对于一个区间，如果区间众数出现次数 $\leq\lceil\frac{len}{2}\rceil$ 次，则我们直接全部分成一段，答案为 $1$。

对于剩下的情况，则只存在一个出现次数 $>\lceil\frac{len}{2}\rceil$ 的数。

我们考虑对于每个区间，尽可能消耗掉多的这种数。

我们对于每个区间，让这种数出现 $x+1$ 次，并让剩余的数出现 $x$ 次，即可将每个出现次数很少的数最大化利用。

在这种情况下，设出现次数很多的数出现了 $A$ 次，剩余的数一共出现了 $B$ 次，答案即为 $A-B$。

注意到 $A-B>1$，我们总是能找到一种方法将每个出现次数很小的数最大化利用，读者可以感性理解一下。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void print(int x) {
    if(x>9) print(x/10);
    *O++=x%10+'0';
}
inline int read()
{
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') s*=10,s+=ch^48,ch=getchar();
	return s;
}
const int bl=620;
int cnt[500003];
int a[500003],lsh[500003];
int mx[807][807];
int pos[500003],t[500003];
vector<int> v[500003];
signed main()
{
	int n=read(),m=read(),s=n/bl;
	for(int i=0; i<n; ++i) lsh[i]=a[i]=read();
	sort(lsh,lsh+n);
	int len=unique(lsh,lsh+n)-lsh;
	for(int i=0; i<n; ++i) a[i]=lower_bound(lsh,lsh+len,a[i])-lsh+1;
	for(int i=0; i<=s; ++i)
	{
		int tmp=0;
		for(int j=i; j<=s; ++j)
		{
			for(int k=j*bl; k<(j+1)*bl; ++k) ++cnt[a[k]],(cnt[a[k]]>tmp)&&(tmp=cnt[a[k]]);
			mx[i][j]=tmp;
		}
		memset(cnt,0,sizeof(cnt));
	} 
	for(int i=0; i<n; ++i) v[a[i]].push_back(i),pos[i]=t[a[i]]++;
	for(int lst=0,l,r; m--;)
	{
		l=read(),r=read();
		--l,--r;
		int BL=l/bl,BR=r/bl;
		int ans,PL,PR;
		if(BL==BR)
		{
			ans=0;
			for(int i=l; i<=r; ++i) ++cnt[a[i]],(cnt[a[i]]>ans)&&(ans=cnt[a[i]]);
			for(int i=l; i<=r; ++i) cnt[a[i]]=0;
		}
		else
		{
			ans=mx[BL+1][BR-1],PL=(BL+1)*bl,PR=BR*bl;
			for(int i=l; i<PL; ++i) while(pos[i]+ans<t[a[i]] && v[a[i]][pos[i]+ans]<=r) ++ans;
			for(int i=PR; i<=r; ++i) while(pos[i]>=ans && v[a[i]][pos[i]-ans]>=l) ++ans;
		}
		int mx=(r-l)/2+1,C;
		if(ans<=mx)
		{
			puts("1");
		}
		else
		C=(r-l+1)-ans,
		printf("%d\n",ans-C);
	}
	fwrite(obuf,O-obuf,1,stdout);
    return 0;
}
```

---

