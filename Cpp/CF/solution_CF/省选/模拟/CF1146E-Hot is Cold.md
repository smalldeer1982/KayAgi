# Hot is Cold

## 题目描述

给定一个包含 $n$ 个整数的数组 $a_1, a_2, \ldots, a_n$。

你将进行 $q$ 次操作。在第 $i$ 次操作中，你会得到一个符号 $s_i$（"<" 或 ">"）和一个数 $x_i$。

你需要构造一个新数组 $b$，其中 $b_j = -a_j$，如果 $a_j\ s_i\ x_i$；否则 $b_j = a_j$（也就是说，如果 $s_i$ 是 ">"，那么所有满足 $a_j > x_i$ 的 $a_j$ 都会被取反）。完成所有替换后，将 $a$ 赋值为 $b$。

你需要输出所有操作结束后，最终的数组。

## 说明/提示

在第一个样例中，数组的变化过程如下：

- 初始：$[-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]$
- $> 2$：$[-5, -4, -3, -2, -1, 0, 1, 2, -3, -4, -5]$
- $> -4$：$[-5, -4, 3, 2, 1, 0, -1, -2, 3, -4, -5]$
- $< 5$：$[5, 4, -3, -2, -1, 0, 1, 2, -3, 4, 5]$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
11 3
-5 -4 -3 -2 -1 0 1 2 3 4 5
> 2
> -4
< 5```

### 输出

```
5 4 -3 -2 -1 0 1 2 -3 4 5
```

## 样例 #2

### 输入

```
5 5
0 1 -2 -1 2
< -2
< -1
< 0
< 1
< 2```

### 输出

```
0 -1 2 -1 2
```

# 题解

## 作者：duyi (赞：13)

## 题解 CF1146E Hot is Cold

因为是对整个序列操作，所以序列里相同的值，最后会变成的结果也是相同的。于是这个序列就不重要了，我们可以对每个值维护，它最终会变成什么。求答案时，依次输出序列里每个位置上值的答案即可。

考虑对值维护答案。先建一棵线段树，范围是$[-10^5,10^5]$，也就是整个值域（在具体实现时，因为$\texttt{C++}$下标不能为负，所以可以整体加$10^5+1$）。

考虑一次操作，以$>$为例（$<$是同理的）。

- 如果$x\geq 0$。
  - 对于初始值为$[x+1,10^5]$和$[-10^5,-x-1]$这两个区间的数，如果它在操作前是正的，它一定$>x$，所以会变成负的；如果它之前是负的，那它一定$<x$，所以不变。因此发现这些数，**无论如何都会变成负的**！直接做区间覆盖即可。
  - 对于初始值为$[-x,x]$的数，它们（无论正负）永远不可能$>x$，所以这次操作对它们没有影响。
- 如果$x<0$。
  - 对于初始值为$[x+1,-x-1]$的数，无论在操作前是正是负，一定$<x$，所以直接取反。
  - 对于初始值为$[-10^5,x]$和$[-x,10^5]$的数，在操作之前如果为负，则取反变成正的；否则不变。所以直接做区间覆盖即可。

综上所述，就是要维护一棵线段树，支持区间取反和区间覆盖。

时间复杂度$O(n\log n)$。

参考代码：

```cpp
//problem:CF1146E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=1e5,MAXV=1e5;
int trans(int x){
	return x+MAXV+1;
}
int revtrans(int x){
	return x-MAXV-1;
}
int n,q,a[MAXN+5],ans[MAXV*2+5];
struct SegmentTree{
	static const int SIZE=MAXV*2+1;
	int rev[SIZE*4+5],cov[SIZE*4+5];
	void push_down(int p){
		if(cov[p]!=0){
			cov[p<<1]=cov[p];
			rev[p<<1]=0;
			cov[p<<1|1]=cov[p];
			rev[p<<1|1]=0;
			cov[p]=0;
		}
		if(rev[p]){
			rev[p<<1]^=1;
			rev[p<<1|1]^=1;
			rev[p]=0;
		}
	}
	void modify_rev(int p,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r){
			rev[p]^=1;
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		if(ql<=mid)
			modify_rev(p<<1,l,mid,ql,qr);
		if(qr>mid)
			modify_rev(p<<1|1,mid+1,r,ql,qr);
	}
	void modify_cov(int p,int l,int r,int ql,int qr,int x){
		if(ql<=l && qr>=r){
			rev[p]=0;
			cov[p]=x;
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		if(ql<=mid)
			modify_cov(p<<1,l,mid,ql,qr,x);
		if(qr>mid)
			modify_cov(p<<1|1,mid+1,r,ql,qr,x);
	}
	void getans(int p,int l,int r){
		if(l==r){
			if(cov[p]!=0){
				ans[l]=cov[p]*abs(revtrans(l));
			}
			else{
				ans[l]=revtrans(l);
			}
			if(rev[p]!=0){
				ans[l]=-ans[l];
			}
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		getans(p<<1,l,mid);
		getans(p<<1|1,mid+1,r);
	}
	SegmentTree(){}
}T;

int main() {
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int tq=1;tq<=q;++tq){
		char s;int x;
		cin>>s>>x;
		if(s=='>'){
			if(x>=0){
				if(x<MAXV){
					T.modify_cov(1,1,T.SIZE,trans(x+1),trans(MAXV),-1);
					T.modify_cov(1,1,T.SIZE,trans(-MAXV),trans(-x-1),-1);
				}
			}
			else{
				T.modify_rev(1,1,T.SIZE,trans(x+1),trans(-x-1));
				T.modify_cov(1,1,T.SIZE,trans(-x),trans(MAXV),-1);
				T.modify_cov(1,1,T.SIZE,trans(-MAXV),trans(x),-1);
			}
		}
		else{
			if(x<=0){
				if(x>-MAXV){
					T.modify_cov(1,1,T.SIZE,trans(-MAXV),trans(x-1),1);
					T.modify_cov(1,1,T.SIZE,trans(-x+1),trans(MAXV),1);
				}
			}
			else{
				T.modify_rev(1,1,T.SIZE,trans(-x+1),trans(x-1));
				T.modify_cov(1,1,T.SIZE,trans(x),trans(MAXV),1);
				T.modify_cov(1,1,T.SIZE,trans(-MAXV),trans(-x),1);
			}
		}
	}
	T.getans(1,1,T.SIZE);
	for(int i=1;i<=n;++i){
		cout<<ans[trans(a[i])]<<" ";
	}
	cout<<endl;
	return 0;
}
```







---

## 作者：_maojun_ (赞：2)

抽象做法。

---

一个数的绝对值不变，所以按绝对值建线段树，正数一棵，负数一棵。

< 和 > 是对称的，说 <。

$x<0$ 就是把负数的一个后缀（绝对值的后缀）合并到正数对应的后缀上。

$x>0$ 就是把负数的一个后缀合并过去，并把负数和正数的某个前缀交换。

直接用动态开点线段树维护，统计答案的时候遍历两棵树得到最终正负性。

直接写时空 $n\log n$，注意到值域很小就算两棵树建满也是 $O(n)$，写个垃圾回收即可。

```cpp
const int N=1e5+5;
int n,q,as[N];

const int S=N<<2,V=1e5;
int tp,st[S],rt[2],ls[S],rs[S];
basic_string<int>id[S];
#define md (l+r>>1)
#define Ls ls[p],l,md
#define Rs rs[p],md+1,r
#define al(x) rt[x],1,V
void ins(int&p,int l,int r,int x,int i){
	!p&&(p=st[tp--]);if(l==r)id[p]+=i;else x<=md?ins(Ls,x,i):ins(Rs,x,i);
}
void Usw(int&p,int l,int r,int&q,int R){	// 交换 p,q 的前缀 R
	if(r<=R){swap(p,q);return;}
	!p&&(p=st[tp--]);!q&&(q=st[tp--]);
	Usw(Ls,ls[q],R);if(R>md)Usw(Rs,rs[q],R);
}
void mrg(int&p,int l,int r,int q){
	if(!p||!q){p|=q;return;}
	if(l==r){id[p]+=id[q];id[q].clear();}
	else{mrg(Ls,ls[q]);mrg(Rs,rs[q]);}
	st[++tp]=q;ls[q]=rs[q]=0;
}
void Umr(int&p,int l,int r,int&q,int L){	// 把 q 的后缀 L 合并到 p
	if(L<=l){mrg(p,l,r,q);q=0;return;}
	if(!q)return;!p&&(p=st[tp--]);
	if(L<=md)Umr(Ls,ls[q],L);Umr(Rs,rs[q],L);
}
void qry(int p,int l,int r,int o){
	if(!p)return;if(l==r){for(int x:id[p])as[x]=l*o;return;}qry(Ls,o);qry(Rs,o);
}
int main(){
	scanf("%d%d",&n,&q);
	tp=S-1;iota(st+1,st+S,1);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		if(x>0)ins(al(0),x,i);
		if(x<0)ins(al(1),-x,i);
	}
	while(q--){
		char o;int x;scanf(" %c%d",&o,&x);
		if(o=='<'){
			if(x<0){
				if(-x<V)Umr(al(0),rt[1],-x+1);
			}else{
				if(x>1)Usw(al(0),rt[1],x-1);
				Umr(al(0),rt[1],max(x,1));
			}
		}else{
			if(x<0){
				if(-x>1)Usw(al(0),rt[1],-x-1);
				Umr(al(1),rt[0],-x);
			}else{
				if(x<V)Umr(al(1),rt[0],x+1);
			}
		}
	}
	qry(al(0),1);qry(al(1),-1);
	for(int i=1;i<=n;i++)printf("%d ",as[i]);
	return 0;
}
```

---

## 作者：buowen123 (赞：2)

校内模拟赛挑的题，赛后 5min 调过。

众所周知，数据结构题就要用数据结构来做，所以我选择**只用数组**。

## 题目大意

- 给一个长度为 $n$ 的序列 $a$，有 $q$ 个操作。
- 一次操作定义为：给定 $x$ 和一个不等号，将大于/小于 $x$ 的数乘以 $-1$。
- 求操作完成后的数列。$n,q \le 10^5$。

## 题目解决

如果你做过 S 组的[这道题](https://www.luogu.com.cn/problem/P7077)，你会知道：对于在最后输出序列的题目，不一定用数据结构做。

如果你还做过 AT 的[这道题](https://www.luogu.com.cn/problem/AT_joisc2014_a)并翻过了题解，你可能会看见一种整体二分的思路（没错[这篇题解](https://www.luogu.com.cn/article/11oaxn6q)也是我发的）。

直接如法炮制。先对原序列从小到大排序，考虑用函数`solve(l,r,c,o)`来表示：
- 目前已经对下标在区间 $[l,r]$ 的数执行了前 $c-1$ 个操作，此时这个区间被乘以 $o$（$1$ 或 $-1$），现在要执行剩下的 $q+1-c$ 个操作并处理答案。

这样在开始时调用`solve(1,n,1,1)`即可。

如何递归下去呢？以 $o=1$，第 $c$ 个操作为 $>x$ 为例，找到第一个 $>x$ 的数 $a_k$，那么下标在 $[k,r]$ 中的数取反，其他正常，也即调用`solve(l,k-1,c+1,o)`和`solve(k,r,c+1,-o)`。类似分讨剩下三种情况。

很可惜，这么做假了。哪怕每次增加的子区间数量为 $1$，$c$ 个操作后有 $c$ 个区间，时间复杂度也有 $O(c^2\log n)$，$c=q$ 就废了。

如果你还做过[这道题](https://www.luogu.com.cn/problem/P3391)，你会知道世界上存在一种数据结构叫平衡树。但我说过只用数组，所以这个做法又 pass 了。

如果你还认真翻过题解，你会发现一种算法：**时间分块，定期重构**。考虑排序后的序列操作后，形成很多子序列：

- 原序列：$[-3,-2,-1,0,1,2,3,4,5,6,7]$；
- 操作 $>3$：$[-3,-2,-1,0,1,2,3],[-4,-5,-6,-7]$;
- 操作 $< -1$：$[3,2],[-1,0,1,2,3],[4,5,6,7]$；

类似地考虑证明每次增加的子区间数量是 $O(1)$ 的。

> 证明：假设一个序列被分成了若干个子区间，一部分子区间乘 $1$（不变），一部分乘 $-1$。
>
> 考虑把乘 $1$ 的所有子区间拼在一起，她们单调递增（排过序）。那么在其中划至多一刀，就可以把序列分成 $>x$ 和 $\le x$ 两部分。对于乘 $-1$ 的可以类似分析。

那么考虑决定一个阈值 $B$，每 $B$ 次操作后就 $O(n\log n)$ 地将序列排序。

这样我们的`solve`函数定义就得改为：`solve(l,r,c,o,g)`表示处理**完**第 $g$ 个操作就终止，除此之外同上。

例如上例排序后就变成：$[-1,0,1,2,2,3,3,4,5,6,7]$。

这么做的时间复杂度是 $O(B^2\log n+\frac{q}{B}n\log n)$，令 $B=(qn/2)^{1/3}$，得最优复杂度 $O(3(qn/2)^{2/3}\log n)$，此时 $B=1710$，操作次数约为 $1.5 \times 10^8$。

场上没算，取 $B=1000$，在 C++23 的鼎力相助下反正是过了。

考场代码很丑，但是修过，轻喷。

submission in CF: [281430956](https://mirror.codeforces.com/problemset/submission/1146/281430956).

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 3, block = 1000;
int n, q;
struct node {
	int id, v;
} a[maxn];
int b[maxn];  // 存储答案
char c[maxn]; 
int d[maxn];  // c,d 存储操作
int s[maxn], t[maxn];
bool cmp(node a, node b) {
	return a.v < b.v;
}
char rev(char ch) {
	if (ch == '<') return '>';
	return '<';
}
void QYY(int l, int r, int cur, int o, int g) { // cur 即题解中的 c
	if (l > r) return;
	if (cur == g + 1) {
		if (g == q) { // 所有操作完了就存答案
			for (int i = l; i <= r; i++) {
				b[a[i].id] = a[i].v * o;
			}
		}
		else { // 反之在原序列上更新
			for (int i = l; i <= r; i++) {
				a[i].v *= o;
			}
		}
		return ;
	}
	char cc;
	int dd;
	// 如果 o 为 -1, 可以认为原序列没变，但操作取反 
	// cc 即大小于, dd 即题解中的 x
	if (o == -1) cc = rev(c[cur]), dd = -d[cur];
	else cc = c[cur], dd = d[cur];
	if (cc == '<') {
		//特判一手, 把整个序列全都(不)需要更新的情况单独写出
		if (a[l].v >= dd) {
			QYY(l, r, cur + 1, o, g);
		}
		else if (a[r].v < dd) {
			QYY(l, r, cur + 1, -o, g);
		}
		else {
			// 以下为二分基本功 找出最后一个 <x 的数
			int ll = l, rr = r;
			while (ll < rr) {
				int mid = (ll + rr + 1) >> 1;
				if (a[mid].v < dd) {
					ll = mid;
				}
				else {
					rr = mid - 1;
				}
			}
			QYY(l, ll, cur + 1, -o, g);
			QYY(ll + 1, r, cur + 1, o, g);
		}
	}
	else {
		if (a[l].v > dd) {
			QYY(l, r, cur + 1, -o, g);
		}
		else if (a[r].v <= dd) {
			QYY(l, r, cur + 1, o, g);
		}
		else {
			// 找到第一个 >x 的数
			int ll = l, rr = r;
			while (ll < rr) {
				int mid = (ll + rr) >> 1;
				if (a[mid].v > dd) {
					rr = mid;
				}
				else {
					ll = mid + 1;
				}
			}
			QYY(l, ll - 1, cur + 1, o, g);
			QYY(ll, r, cur + 1, -o, g);
		}
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].v;
		a[i].id = i;
	}
	for (int i = 1; i <= q; i++) {
		cin >> c[i] >> d[i];
	}
	// 时间分块
	int num = (q - 1) / block + 1;
	for (int i = 1; i <= num; i++) {
		s[i] = t[i - 1] + 1;
		t[i] = i * block;
	}
	t[num] = q;
	for (int i = 1; i <= num; i++) {
		sort(a + 1, a + n + 1, cmp);
		QYY(1, n, s[i], 1, t[i]);
	}
	for (int i = 1; i <= n; i++) {
		cout << b[i] << ' ';
	}
	return 0;
}
```

---

## 作者：Skadi_H (赞：2)

## 前言
upd 2024.6.20 已对【中文】与【英文、数字或公式】之间空格问题进行修改，请审核老师重新审核。

upd 2024.6.20 已对【中文标点符号】与【英文、数字、公式或汉字】之间的空格进行删除，请审核老师重新审核。

upd 2024.6.20 已对特定的、约定俗成的函数名称正体的使用进行修改。

[前往博客获得不知道会不会更好的阅读体验。](https://www.luogu.com.cn/article/77s8rqx8)

前几天 duel 到的一道题目，由于我当时把线段树单点查询的判断里面 pos 跟 mid 写反了，半天没调出来，导致[对面大佬](https://www.luogu.com.cn/user/419726)被强制下机时 giveup 了，~~没能成功一雪前耻~~。
## 题意简述
有一个数列，每次操作会给定 $x$ 和不等号（大于号或小于号），可以将 $>x$ 或 $<x$ 的所有数乘 $-1$。求最后的数列。
## 分析
分析题目，我们可以得到以下两点信息：

1. 对于任意一个 $a_i$，他们经过题目当中的 $m$ 次变换之后，都会得到一个相同的最终值 $f_i \times a_i(f_i \in {-1,1} )$，故我们**无需关心每个数出现的具体位置**。

2. $>x$ 或 $<x$ 影响的都是某个**连续区间**当中的数。

很自然能够想到可以采用**权值线段树**，**维护任意 $a_i$ 在 $m$ 次操作后的最终值**即可，然后输出时输出 $f_{a_i}$ 即可。

下面我们讨论面对不同的操作，我们应该如何对线段树进行修改：

由于 $0$ 无论经过何种变换，最终值都是 $0$，故下文当中忽略对 $a_i=0$ 的讨论。

我们令一次输入为 $con$ $num$：

1. $con='>'$：
- 若 $num>0$:

对 $x \in [-num,num]$，由于 $\operatorname{abs}(x) \leq num$，所以他们无论如何都不可能在此次操作被修改。

对 $x \in [num+1,10^5]$，显然所有 $f_x=1$ 的位置将变为 $f_x=-1$。故对 $[num+1,10^5]$ 区间做一次覆盖值为 $-1$ 的区间覆盖操作。（原本 $f_x=-1$ 的再一次被覆盖不受影响）。

对 $x \in [-10^5,-num-1]$，显然所有 $f_x=-1$ 的位置将变为 $f_x=1$。故对 $[-10^5,-num-1]$ 区间做一次覆盖值为 $1$ 的区间覆盖操作。（同上）。

- 若 $num<0$ :

对 $x \in [num+1,-num-1]$，由于 $ -\operatorname{abs}(x) > num$，所以所有 $f_x$ 都将被 $ \times -1$。

对 $x \in [-10^5，num]$，显然所有 $f_x=-1$ 的位置将变为 $f_x=1$。

对 $x \in [-num+1,10^5]$，显然所有 $f_x=1$ 的位置将变为 $f_x=-1$。

2. $con='<'$ ： 
- 若 $num<0$ :

对 $x \in [num,-num]$，由于 $- \operatorname{abs}(x) \geq num$，所以他们无论如何都不可能在此次操作被修改。

对 $x \in [-10^5,num-1]$，显然所有 $f_x=1$ 的位置将变为 $f_x=-1$。

对 $x \in [-num+1,10^5]$，显然所有 $f_x=-1$ 的位置将变为 $f_x=1$。

- 若 $num>0$ :

对 $x \in [-num+1,num-1]$，由于 $ -\operatorname{abs}(x) > num$，所以所有 $f_x$ 都将被 $ \times -1$。

对 $x \in [num,10^5]$，显然所有 $f_x=-1$ 的位置将变为 $f_x=1$。

对 $x \in [-10^5,-num]$，显然所有 $f_x=1$ 的位置将变为 $f_x=-1$。

所以我们只需要维护一颗支持**区间翻转、区间覆盖**的线段树即可。

由于线段树不支持下标为负值的信息存储操作等，所以我设置了一个 $delta=10^5+5$，将 $a_i$ 的信息存储在下标为 $i+delta$ 的位置上。

然后这道题就做完了。
## 代码
下面简单的贴一下代码：

（由于写法原因，我要在每次查询的时候 pushdown 一次才能把 tag 更新到线段树的叶子结点，所以线段树要开8倍空间，当然，在 pushdown 当中可以用一个简单的特判可以使空间降回4倍）。
```
#include <bits/stdc++.h>
using namespace std;
const int delta=100005;//偏移量 
struct stree
{
	int l,r,val,ftag,ctag;
	//val初始为1
	//ftag->flip  表示是否翻转 
	//ctag->cover 表示是否有值覆盖该节点 
}t[1620005];
int n,q,x;
int a[100005],f[210005];
char con;
void pushup(int idx) 
{
	//由于没有维护区间 和一类 的信息
	//所以pushup是空的 
	return;
}
void pushdown(int idx)
{
	//注意，由于ctag更新完之后可能还会再被翻转
	//所以需要先用ctag更新，再用ftag 
	if(t[idx].ctag)
	{
		t[idx].val=t[idx].ctag;
		t[2*idx].ctag=t[idx].ctag;
		t[2*idx].ftag=0;
		t[2*idx+1].ctag=t[idx].ctag;
		t[2*idx+1].ftag=0;
		t[idx].ctag=0;
	}
	if(t[idx].ftag)
	{
		t[idx].val*=-1;
		t[2*idx].ftag^=1;
		t[2*idx+1].ftag^=1;
		t[idx].ftag=0;
	}
}
void build(int idx,int l,int r)//裸建树 
{
	t[idx].l=l,t[idx].r=r;
	if(l==r)
	{
		t[idx].val=t[idx].ctag=1;
		//初始可以理解为被ctag=1覆盖 
		return;
	}
	int mid=l+r>>1;
	build(2*idx,l,mid);
	build(2*idx+1,mid+1,r);
	pushup(idx);
}
void changef(int idx)//ftag=1表示被翻转了(即*-1) 
{
	t[idx].ftag^=1;
}
void changec0(int idx)//ctag修改时注意要把ftag清空 
{
	t[idx].ctag=-1;
	t[idx].ftag=0;
}
void changec1(int idx)//这里一样 
{
	t[idx].ctag=1;
	t[idx].ftag=0;
}
void updatef(int idx,int l,int r)//区间翻转(即*-1) 
{
	if(t[idx].r<l||t[idx].l>r)
		return;
	if(l<=t[idx].l&&t[idx].r<=r)
	{
		changef(idx);
		return;
	}
	pushdown(idx);
	int mid=t[idx].l+t[idx].r>>1;
	if(l<=mid)
		updatef(2*idx,l,r);
	if(mid+1<=r)
		updatef(2*idx+1,l,r);
	pushup(idx);
}
void updatec0(int idx,int l,int r)//区间覆盖-1，由于-1不是很好打，就用了0 
{
	if(t[idx].r<l||t[idx].l>r)
		return;
	if(l<=t[idx].l&&t[idx].r<=r)
	{
		changec0(idx);
		return;
	}
	pushdown(idx);
	int mid=t[idx].l+t[idx].r>>1;
	if(l<=mid)
		updatec0(2*idx,l,r);
	if(mid+1<=r)
		updatec0(2*idx+1,l,r);
	pushup(idx);
}
void updatec1(int idx,int l,int r)//区间覆盖1 
{
	if(t[idx].r<l||t[idx].l>r)
		return;
	if(l<=t[idx].l&&t[idx].r<=r)
	{
		changec1(idx);
		return;
	}
	pushdown(idx);
	int mid=t[idx].l+t[idx].r>>1;
	if(l<=mid)
		updatec1(2*idx,l,r);
	if(mid+1<=r)
		updatec1(2*idx+1,l,r);
	pushup(idx);
}
int query(int idx,int pos)//查询 
{
	if(t[idx].l==t[idx].r)
	{
		pushdown(idx);
		return t[idx].val;
	}
	pushdown(idx);
	int mid=t[idx].l+t[idx].r>>1;
	if(pos<=mid)
		return query(2*idx,pos);
	else
		return query(2*idx+1,pos);
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	} 
	build(1,1,200006);//建树 
	while(q--)
	{
		cin>>con>>x;
		if(con=='>')//这里的每个操作都是按照题解当中给出的顺序排列的 
		{//请大家放心食用 
			if(x>=0)
			{
				updatec0(1,x+1+delta,100000+delta);
				updatec1(1,-100000+delta,-x-1+delta);
			}
			else
			{
				updatef(1,x+1+delta,-x-1+delta);
				updatec1(1,-100000+delta,x+delta);
				updatec0(1,-x+delta,100000+delta);
			}
		}
		else
		{
			if(x<=0)
			{
				updatec0(1,-100000+delta,x-1+delta);
				updatec1(1,-x+1+delta,100000+delta);
			}
			else
			{
				updatef(1,-x+1+delta,x-1+delta);
				updatec1(1,x+delta,100000+delta);
				updatec0(1,-100000+delta,-x+delta);
			}
		}
	}
	for(int i=-100000;i<=100000;i++)//查询每个f_i，偏移delta位存储 
	{
		f[i+delta]=((query(1,i+delta)==1)?1:-1);
	}
	for(int i=1;i<=n;i++)//输出 
	{
		cout<<a[i]*f[a[i]+delta]<<" ";
	} 
	return 0;//完结撒花 
}
//Skadi_H

```
## 后记
审核老师辛苦了！！！

---

## 作者：Wei_Han (赞：1)

这没有紫吧。

直接做显然不好搞，我们考虑分析性质。

我们把 $a_i$ 放到值域上来看，对每个 $a_i$ 加一个状态 $b_i$，表示当前 $a_i$ 是否被翻转，令当前为 $> k$：

- $k>0$ 时，则对于 $i\in (k,+\infty)$，$b_i$ 为 $0$ 的 $a_i$ 需要取反，再考虑一下，对于 $i\in (-\infty,-k)$ 且 $b_i$ 为 $1$ 的 $a_i$ 也需要取反，总结一下，我们可以认为此时是对 $i \in (k,+\infty)$ 中 $b_i$ 全部赋为 $1$，对 $i \in (-\infty,-k)$ 的 $b_i$ 全部赋为 $0$，这条对于符号为 $<$ 时也是同理的，只是把 $1$ 和 $0$ 交换了。

- $k<0$ 时，我们需要重新分析，首先对于 $i \in (-\infty,k]$ 需要将 $b_i$ 全部赋为 $1$，与上面同理，对于 $i \in [-k,+\infty)$ 需要将 $b_i$ 全部赋为 $1$，对于中间部分，也就是 $i \in (k,-k)$，显然关于 $0$ 点对称，简单模拟可以发现中间是对 $b_i$ 取反。对于 $<$ 的情况就是将 $01$ 交换。

区间推平和异或用线段树维护，我这里先排序然后二分，注意一下二分的边界问题就好了。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pr putchar('\n')
#define fi first
#define se second
#define pp putchar(' ')
#define pii pair<ll,ll>
#define pdi pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define pb push_back
//#pragma GCC optimize(2)
using namespace std;
typedef int ll;
//typedef long long ll;
//typedef __int128 ll;
typedef double db;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
const ll N=2e5+5,M=2e4+5,mod=998244353;
ll n,q,b[N],ans[N];
struct SegTree{ll l,r,sum[2],lazy[2],rev,ls[2],rs[2],mx[2];}tree[N<<2];
struct node{ll x,id;}a[N];
#define rt tree[root]
#define lson tree[root<<1]
#define rson tree[root<<1|1]
inline void pushup(ll root){fo(0,i,1) rt.sum[i]=lson.sum[i]+rson.sum[i],rt.mx[i]=max(lson.rs[i]+rson.ls[i],max(lson.mx[i],rson.mx[i])),rt.ls[i]=max(lson.ls[i],lson.sum[i]==lson.r-lson.l+1?lson.sum[i]+rson.ls[i]:0),rt.rs[i]=max(rson.rs[i],rson.sum[i]==rson.r-rson.l+1?rson.sum[i]+lson.rs[i]:0);}
inline void pd(ll root){fo(0,i,1){ll lazy=rt.lazy[i];if(!lazy) continue;lson.sum[i]=lson.r-lson.l+1;rson.sum[i]=rson.r-rson.l+1;lson.sum[i^1]=rson.sum[i^1]=0;lson.mx[i]=lson.ls[i]=lson.rs[i]=lson.r-lson.l+1;rson.mx[i]=rson.ls[i]=rson.rs[i]=rson.r-rson.l+1;lson.mx[i^1]=lson.ls[i^1]=lson.rs[i^1]=0;rson.mx[i^1]=rson.ls[i^1]=rson.rs[i^1]=0;lson.lazy[i^1]=rson.lazy[i^1]=0;lson.rev=rson.rev=0;lson.lazy[i]=rson.lazy[i]=1;rt.lazy[i]=rt.lazy[i^1]=0;}}
inline void pdrev(ll root){ll lazy=rt.rev;if(!lazy) return;swap(lson.sum[1],lson.sum[0]),swap(rson.sum[1],rson.sum[0]);swap(lson.ls[1],lson.ls[0]),swap(rson.ls[1],rson.ls[0]);swap(lson.rs[1],lson.rs[0]),swap(rson.rs[1],rson.rs[0]);swap(lson.mx[1],lson.mx[0]),swap(rson.mx[1],rson.mx[0]);rt.rev=0,lson.rev^=1,rson.rev^=1;}
inline void build(ll root,ll l,ll r){rt.l=l,rt.r=r;if(l==r){rt.sum[0]=rt.ls[0]=rt.rs[0]=rt.mx[0]=1;return;}ll mid=l+r>>1;build(root<<1,l,mid),build(root<<1|1,mid+1,r);pushup(root);}
inline void upd(ll root,ll x,ll y,ll op){ll l=rt.l,r=rt.r;if(x<=l&&y>=r){rt.sum[op]=rt.ls[op]=rt.rs[op]=rt.mx[op]=r-l+1,rt.lazy[op]=1,rt.lazy[op^1]=rt.rev=rt.sum[op^1]=rt.ls[op^1]=rt.rs[op^1]=rt.mx[op^1]=0;return;}ll mid=l+r>>1;pd(root);pdrev(root);if(x<=mid) upd(root<<1,x,y,op);if(y>mid) upd(root<<1|1,x,y,op);pushup(root);}
inline void updrev(ll root,ll x,ll y){if(x>y) return;ll l=rt.l,r=rt.r;if(x<=l&&y>=r){swap(rt.sum[0],rt.sum[1]),swap(rt.ls[0],rt.ls[1]),swap(rt.rs[0],rt.rs[1]),swap(rt.mx[0],rt.mx[1]);rt.rev^=1;return;}ll mid=l+r>>1;pd(root);pdrev(root);if(x<=mid) updrev(root<<1,x,y);if(y>mid) updrev(root<<1|1,x,y);pushup(root);}
inline SegTree ask(ll root,ll x,ll y){ll l=rt.l,r=rt.r;if(x<=l&&y>=r) return rt;ll mid=l+r>>1;pd(root);pdrev(root);if(x>mid) return ask(root<<1|1,x,y);else if(y<=mid) return ask(root<<1,x,y);else{SegTree a=ask(root<<1,x,y),b=ask(root<<1|1,x,y),c={0,0,{0,0},{0,0},0,{0,0},{0,0},{0,0}};fo(0,i,1){c.sum[i]=a.sum[i]+b.sum[i];c.mx[i]=max(a.rs[i]+b.ls[i],max(a.mx[i],b.mx[i]));c.ls[i]=max(a.ls[i],a.sum[i]==a.r-a.l+1?a.sum[i]+b.ls[i]:0);c.rs[i]=max(b.rs[i],b.sum[i]==b.r-b.l+1?b.sum[i]+a.rs[i]:0);}return c;}}
inline bool cmp(node x,node y){return x.x<y.x;}
signed main(){
	read(n);read(q);fo(1,i,n) read(b[i]),a[i].x=b[i],a[i].id=i;sort(a+1,a+1+n,cmp);sort(b+1,b+1+n);b[n+1]=inf;b[0]=-inf;n++;build(1,0,n);
	fo(1,i,q)
	{
		char s;ll x;cin>>s;read(x);
		if(s=='>')
		{
			ll flag=0;if(x<0) flag=1;
			ll t1,t2;
			if(x<0)
				t1=lower_bound(b+1,b+1+n,-x)-b,
				t2=upper_bound(b+1,b+1+n,x)-b-1;
			else
				t1=upper_bound(b+1,b+1+n,x)-b,
				t2=lower_bound(b+1,b+1+n,-x)-b-1;
			upd(1,t1,n,1),upd(1,0,t2,0);
			if(flag) updrev(1,t2+1,t1-1);
		}
		else
		{
			ll flag=0;if(x>0) flag=1;
			ll t1,t2;
			if(x<0)
				t1=upper_bound(b+1,b+1+n,-x)-b,
				t2=lower_bound(b+1,b+1+n,x)-b-1;
			else
				t1=lower_bound(b+1,b+1+n,x)-b,
				t2=upper_bound(b+1,b+1+n,-x)-b-1;
			upd(1,t1,n,0),upd(1,0,t2,1);
			if(flag) updrev(1,t2+1,t1-1);
		}
	}
	fo(1,i,n-1) ans[a[i].id]=b[i]*(-1*(ask(1,i,i).sum[1]>0?1:-1));
	fo(1,i,n-1) wr(ans[i]),pp;pr;
	return 0;
}
``````

---

## 作者：xkcdjerry (赞：1)

由于 $a$ 的值域很小（$[-10^5,10^5]$）而且所有操作均对整个数列进行，所以可以构建线段树维护 $[-10^5,10^5]$ 中每个数最后的结果，然后再对每一个 $a$ 中的数利用这个线段树映射。

~~实际上值域继续开大也可以离散化然后做/动态开点做。~~

分类讨论：

如果是 $>x$（$x>0$）：  
区间 $[x+1,\infty)$ 中的数如果符号翻转不变，否则被翻转，即全部变为负数。区间 $(-\infty,-x-1]$ 中的数同理全部变为负数。  

如果是 $>x$（$x<0$）:  
区间 $(-\infty,x-1]$ 的数如果符号翻转会再次翻转，否则不变，即全部变为负数。区间 $[-x+1,\infty)$ 中的数同理全部变为负数。  
而区间 $[x+1,-x-1]$ 中的数一定会被翻转。

如果是 $<x$（$x>0$）：  
同理可得区间 $(-\infty,-x-1]$ 与 $[x+1,\infty)$ 中的全部变为**正**数。  
区间 $[-x+1,x-1]$ 一定会被翻转。

如果是 $<x$（$x<0$）：  
同理可得区间 $(-\infty,x-1]$ 与 $[-x+1,\infty)$ 中的全部变为正数。

综上，每个操作可以用若干次区间翻转和若干次区间赋值得到。可以考虑到线段树。（板子不用讲了吧）

（这里使用的是覆盖与翻转双 lazy tag，但是由于两个 tag 互斥所以理论上一个即可）

蒟蒻代码如下（最开始 2.83K 为了可读性一路压到 1.97K）：

```c++
#include <cstdio>
const int Q=100010,N=300010;
struct seg
{
    int l,r,lazy;bool flip;
}tree[N*4+10000];
int n,m,a[N],f[N];
void FLIP(int o) {if(tree[o].lazy)tree[o].lazy*=-1;else tree[o].flip=!tree[o].flip;}
void SET(int x,int o) {tree[o].flip=false;tree[o].lazy=x;}
void pushdown(int o)
{
    int &x=tree[o].lazy;
    if(tree[o].flip) {FLIP(o<<1);FLIP(o<<1|1);}
    if(x){SET(x,o<<1);SET(x,o<<1|1);}
    tree[o].flip=false;x=0;
}
void flip(int l,int r,int o=1)
{
    if(tree[o].l==l&&tree[o].r==r){FLIP(o);return;}
    int mid=(tree[o].l+tree[o].r)/2;
    pushdown(o);
    if(r<=mid) flip(l,r,o<<1);
    else if(l>mid) flip(l,r,o<<1|1);
    else
    {
        flip(l,mid,o<<1);
        flip(mid+1,r,o<<1|1);
    }
}
void set(int l,int r,int x,int o=1)
{
    if (tree[o].l==l&&tree[o].r==r){SET(x,o);return;}
    int mid=(tree[o].l+tree[o].r)/2;
    pushdown(o);
    if(r<=mid) set(l,r,x,o<<1);
    else if(l>mid) set(l,r,x,o<<1|1);
    else
    {
        set(l,mid,x,o<<1);
        set(mid+1,r,x,o<<1|1);
    }
}
void mktree(int l,int r,int o=1)
{
    tree[o]=seg{l,r,l==r?(l<Q?-1:1):0,false};
    if (l != r)
    {
        int mid=(l+r)/2;
        mktree(l,mid,o<<1);
        mktree(mid+1,r,o<<1|1);
    }
}
int query(int x,int o=1)
{
    if (tree[o].l==x&&tree[o].r==x) return tree[o].lazy;
    int mid=(tree[o].l+tree[o].r)/2;
    pushdown(o);
    return x<=mid?query(x,o<<1):query(x,o<<1|1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    //因为线段树无法处理负数全部向右平移Q
    mktree(0,2*Q);
    while(m--)
    {
        char ch;int x;
        scanf(" %c%d",&ch,&x);
        if(ch=='>')
        {
            if(x>=0){set(0,Q-x-1,-1);set(Q+x+1,2*Q,-1);}
            else{flip(Q+x+1,Q-x-1);set(0,Q+x,-1); set(Q-x,2*Q,-1);}
        }
        if(ch=='<')
        {
            if(x<=0){set(0,Q+x-1,1);set(Q-x+1,2*Q,1);}
            else{flip(Q-x+1, Q+x-1);set(0,Q-x,1);set(Q+x,2*Q,1);}
        }
    }
    for(int i=0;i<n;i++)
        printf("%d ",(a[i]<0?-a[i]:a[i])*query(Q+a[i]));
}
```
[评测记录](https://www.luogu.com.cn/record/71932907)

---

## 作者：Setsugesuka (赞：1)

这里提供一种简单好写的方法

注意到题目里 $ai$ 的范围在 $[-1e5,1e5]$ 之间，这是一个很小的数据范围。考虑每次操作，每次操作我们都会把 $>x$ 的数取负，或者是把 $<x$ 的数取负。如果我们从给定的数列里找到这些数去改变他们的值，时间复杂度将会十分爆炸。

换种思路，我们可以去维护 $[-1e5,1e5]$ 之间的每个数在进行这些操作以后会变成多少，输出答案的时候只需要对应地去查找这个数的状态就可以了。

我们假设一个数被取反的状态是 $-1$ ，没被取反的状态是 $1$ 。

考虑 $>x$ 的操作

假设 $x>0$ 那么，在 $[x+1,1e5]$ 之间的这些数状态都会变成 $-1$ ，这是很显然的，因为本身状态是 $1$ 的数大于它，会变成 $-1$ ，而本身状态是 $-1$ 的数则已经小于它，不会再改变了。同理，在 $[-1e5,x-1]$ 之间的这些数都会变成 $1$ 。

假设 $x<0$ 那么，在 $[x+1,-x-1]$ 之间的这段数不管怎么改变都会 $>x$ ，也就是他们的状态都会乘上 $-1$ 。而 $[x,1e5]$ 以及 $[-1e5,x]$ 之间这些数就和上面一样了。

同理， $<x$ 的操作我们也可以很好地想出来。

接下来的问题就是怎么维护了，我们需要一个支持区间赋值和区间取反的数据结构， $ODT$ 可以很好地解决这一类问题。

需要注意到的是我们的元素值域很小，只有 $-1,1$ ，所以我们的程序复杂度要靠实时的区间合并来保证。

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline bool read(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
    {
        return 0;
    }
    while (c != '-' && (c < '0' || c > '9'))
    {
        c = getchar();
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0');
    }
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(T x)
{
    if (x > 9)
    {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN=1e6+10;

struct node
{
    int l,r;
    mutable int v;
    node(){}
    node(int L,int R=-1,int V=0):l(L),r(R),v(V){}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

set<node> s;

inline void merge(int l)
{
    set<node>::iterator it1,it2,it3;
    it2=s.lower_bound(l);
    if(it2==s.begin())
        return;
    it1=it2,it3=it2;
    --it1,++it3;
    bool pd3=(it3!=s.end());
    if(pd3&&it1->v==it2->v&&it2->v==it3->v&&it1->v==it3->v)
    {
        int l=it1->l,r=it3->r,v=it2->v;
        s.erase(it1,++it3);
        s.insert(node(l,r,v));
    }
    else if(it1->v==it2->v)
    {
        int l=it1->l,r=it2->r,v=it2->v;
        s.erase(it1,++it2);
        s.insert(node(l,r,v));
    }
    else if(pd3&&it2->v==it3->v)
    {
        int l=it2->l,r=it3->r,v=it2->v;
        s.erase(it2,++it3);
        s.insert(node(l,r,v));
    }
}

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline void reverse(int l,int r)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
    {
        itl->v=-itl->v;
    }
}

int a[MAXN];
int n,q;

int main()
{
    read(n),read(q);
    for(int i=1;i<=n;++i)
        read(a[i]);
    s.insert(node(-100000,100000,1));
    while(q--)
    {
        char op;
        cin>>op;
        int sr;
        read(sr);
        if(op=='>')
        {
            if(sr<0)
            {
                reverse(sr+1,-sr-1);
                assignval(-100000,sr,1);
                assignval(-sr,100000,-1);
            }
            else
            {
                assignval(sr+1,100000,-1);
                assignval(-100000,-sr-1,1);
            }
            merge(sr+1);
            merge(-sr-1);
        }
        else
        {
            if(sr>0)
            {
                reverse(-sr+1,sr-1);
                assignval(sr,100000,1);
                assignval(-100000,-sr,-1);
            }
            else
            {
                assignval(-100000,sr-1,-1);
                assignval(-sr+1,100000,1);
            }
            merge(-sr+1);
            merge(sr-1);
        }
    }
    for(int i=1;i<=n;++i)
    {
        a[i]*=split(a[i])->v;
        if(a[i]<0)
        {
            putchar('-');
            a[i]=-a[i];
        }
        write(a[i]);
        putchar(' ');
    }
    return 0;
}
```


---

## 作者：SSerxhs (赞：1)

裸的权值线段树

由于每个值只会变成绝对值相同的值，考虑用权值线段树维护每个绝对值的情况。记0为不改变，1为正变负，2为负变正，3为正负交换，由于修改面向整个序列，每个绝对值的变化都是这四种之一，权值线段树维护lazy标记即可。

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=1e5+2,M=4e5+2;
int l[M],r[M],lz[M],ys[N],a[N];
int n,m,q,i,x,y,z,c,fh;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	if (fh) x=-x,fh=0;
}
inline int ab(int x)
{
	if (x>0) return x;
	return -x;
}
void build(int x)
{
	while (l[x]<r[x])
	{
		l[c=x<<1]=l[x];r[c]=l[x]+r[x]>>1;
		l[c|1]=r[c]+1;r[c|1]=r[x];
		build(c);x=x<<1|1;
	}
	ys[l[x]]=x;
}
inline void pushdown(register int x)
{
	if ((lz[x])&&(l[x]<r[x]))
	{
		register int c=x<<1;
		if (lz[x]!=3)
		{
			lz[c]=lz[x];
			c|=1;
			lz[c]=lz[x];
		}
		else
		{
			lz[c]^=3;lz[c|1]^=3;
		}
		lz[x]=0;
	}
}
void mdf(int x)
{
	pushdown(x);
	if ((z<=l[x])&&(r[x]<=y))
	{
		if ((l[x]<r[x])||(c!=3)) lz[x]=c; else lz[x]^=3; return;
	}
	if (z<=r[x<<1]) mdf(x<<1);
	if (y>r[x<<1]) mdf(x<<1|1);
}
void allpush(int x)
{
	while (l[x]<r[x])
	{
		pushdown(x);
		allpush(x<<1);x=x<<1|1;
	}
}
int main()
{
	read(n);read(q);
	for (i=1;i<=n;i++)
	{
		read(a[i]);
		m=max(m,ab(a[i]));
	}
	if (m==0) {for (i=1;i<=n;i++) printf("0 ");return 0;}
	r[l[1]=1]=m;build(1);
	while (q--)
	{
		c=getchar();
		while ((c!='<')&&(c!='>')) c=getchar();
		if (c=='<')
		{
			read(x);
			if (x<0)
			{
				c=2;z=-x+1;y=m;if (z<=y) mdf(1);
			}
			else
			{
				c=3;z=1;y=x-1;if (z<=y) mdf(1);
				c=2;z=x;y=m;if (z<=y) mdf(1);
			}
		}
		else
		{
			read(x);
			if (x>0)
			{
				c=1;z=x+1;y=m;if (z<=y) mdf(1);
			}
			else
			{
				c=3;z=1;y=-x-1;if (z<=y) mdf(1);
				c=1;z=-x;y=m;if (z<=y) mdf(1);
			}
		}
	}
	allpush(1);
	for (i=1;i<=n;i++) if ((x=a[i])<0)
	{
		if (2^lz[ys[ab(x)]]&2) putchar('-');printf("%d ",-x);
	}
	else if (x==0) printf("0 ");
	else 
	{
		if (lz[ys[ab(x)]]&1) putchar('-');printf("%d ",x);
	}
}
```


---

