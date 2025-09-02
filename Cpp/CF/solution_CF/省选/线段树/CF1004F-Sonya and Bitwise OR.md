# Sonya and Bitwise OR

## 题目描述

Sonya has an array $ a_1, a_2, \ldots, a_n $ consisting of $ n $ integers and also one non-negative integer $ x $ . She has to perform $ m $ queries of two types:

- $ 1 $ $ i $ $ y $ : replace $ i $ -th element by value $ y $ , i.e. to perform an operation $ a_{i} $ := $ y $ ;
- $ 2 $ $ l $ $ r $ : find the number of pairs ( $ L $ , $ R $ ) that $ l\leq L\leq R\leq r $ and bitwise OR of all integers in the range $ [L, R] $ is at least $ x $ (note that $ x $ is a constant for all queries).

Can you help Sonya perform all her queries?

Bitwise OR is a binary operation on a pair of non-negative integers. To calculate the bitwise OR of two numbers, you need to write both numbers in binary notation. The result is a number, in binary, which contains a one in each digit if there is a one in the binary notation of at least one of the two numbers. For example, $ 10 $ OR $ 19 $ = $ 1010_2 $ OR $ 10011_2 $ = $ 11011_2 $ = $ 27 $ .

## 说明/提示

In the first example, there are an array \[ $ 0 $ , $ 3 $ , $ 6 $ , $ 1 $ \] and queries:

1. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
2. on the segment \[ $ 3\ldots4 $ \], you can choose pair ( $ 3 $ , $ 4 $ );
3. the first number is being replacing by $ 7 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 6 $ , $ 1 $ \];
4. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
5. on the segment \[ $ 1\ldots3 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 2 $ , $ 3 $ );
6. on the segment \[ $ 1\ldots1 $ \], you can choose pair ( $ 1 $ , $ 1 $ );
7. the third number is being replacing by $ 0 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 0 $ , $ 1 $ \];
8. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 1 $ , $ 4 $ ).

In the second example, there are an array \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 15 $ , $ 2 $ \] are queries:

1. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), ( $ 3 $ , $ 5 $ ), ( $ 4 $ , $ 4 $ ), and ( $ 4 $ , $ 5 $ );
2. the fourth number is being replacing by $ 4 $ , after this operation, the array will consist of \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 4 $ , $ 2 $ \];
3. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), and ( $ 3 $ , $ 5 $ );
4. on the segment \[ $ 3\ldots5 $ \], you can choose pairs ( $ 3 $ , $ 4 $ ) and ( $ 3 $ , $ 5 $ );
5. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ ).

## 样例 #1

### 输入

```
4 8 7
0 3 6 1
2 1 4
2 3 4
1 1 7
2 1 4
2 1 3
2 1 1
1 3 0
2 1 4
```

### 输出

```
5
1
7
4
1
4
```

## 样例 #2

### 输入

```
5 5 7
6 0 3 15 2
2 1 5
1 4 4
2 1 5
2 3 5
2 1 4
```

### 输出

```
9
7
2
4
```

# 题解

## 作者：duyi (赞：14)

# 进入我的博客获得超爽阅读体验/se/se/se

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/13269575.html)

### 题目大意

[题目链接](https://codeforces.com/contest/1004/problem/F)

给定一个长度为$n$的序列$a_1,a_2,\dots,a_n$和一个非负整数$x$。你需要支持$m$次操作。操作有两种：

- $1\ i\ y$：把序列的第$i$个元素设为$y$，也就是$a_i:=y$。
- $2\ l\ r$：求有多少对$(L,R)$满足$l\leq L\leq R\leq r$且$a_l,\dots a_r$按位**或**的和大于等于$x$。

数据范围：$1\leq n,m\leq 10^5,0\leq x,a_i,y<2^{20}$。$1\leq i\leq n$。$1\leq l\leq r\leq n$。

### 本题题解

考虑只有一次询问时怎么做。

分治。每次考虑$L$位于左半边，$R$位于右半边的情况（也就是“跨过中点”的答案）。再分别递归左、右两边。计算跨过中点的答案时，可以先求出【左半边的$\operatorname{or}$值后缀和】和【右半边的$\operatorname{or}$值前缀和】。然后用**two pointers**求出满足条件的$(L,R)$数量，例如，可以枚举$R$，则左半边的$L$可选范围单调增加，也就是从最左边不断向右移。这样，不算递归，每次做two pointers的复杂度都是$O(\text{len})$的，一次询问总复杂度就是$O(\text{len}\log \text{len})$。

现在要支持**单点修改**和**多次查询**。考虑用**线段树**来维护。

分治时的左、右两边，天然就是线段树的左、右节点，这有很多相似之处。但是我们面临的问题是：如果向分治时一样，维护出每个区间的前缀、后缀$\operatorname{or}$和，则一次修改、查询的复杂度，都高达$O(n\log n)$，无法承受。

此时要用到最关键的一个性质：前缀、后缀的$\operatorname{or}$和，都只会分成$O(\log a)$个段，满足每段内值相同，不同段值不同。这是因为，前缀、后缀$\operatorname{or}$和，都是单调不下降的，每次增长，都至少多出一个为$1$的二进制位，所以最多增长$\log_2 a$次，也就是只有$O(\log a)$个段。

考虑对线段上每个区间，用两个$\texttt{vector}$，分别维护该区间前缀、后缀$\operatorname{or}$和的这$O(\log a)$个段。同时，维护每个区间的答案（这个区间里有多少对$(L,R)$满足......）。合并两个区间（也就是线段树$\texttt{push_up}$操作）时，先继承左、右儿子内部的答案，再用two pointers的方法求出跨过中点的答案（这和分治时是一样的）。于是我们就能$O(\log a)$实现$\texttt{push_up}$操作。也就能$O(n\log a)$建树（预处理）、$O(\log n\log a)$实现一次单点修改了。

查询时，线段树当前节点的区间，如果被查询的区间完全覆盖，直接返回维护好的答案；否则递归左、右儿子，再计算跨过中点的答案。所以单次查询也是$O(\log n\log a)$的。

总时间复杂度$O(n\log a+m\log n\log a)$。

参考代码：

```cpp
//problem:CF1004F
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

const int MAXN=1e5;
int n,m,X,a[MAXN+5];
struct SegmentTree{
	int tl[MAXN*4+5],tr[MAXN*4+5];
	ll ans[MAXN*4+5];
	vector<pii>pre[MAXN*4+5],suf[MAXN*4+5];//(pos,val)
	
	void ck(int p){
		assert(SZ(pre[p]) && pre[p][0].fi==tl[p]);
		assert(SZ(suf[p]) && suf[p][0].fi==tr[p]);
	}
	void push_up(int p){
		int ls=p<<1,rs=p<<1|1;ck(ls);ck(rs);
		//1. ans
		ans[p]=ans[ls]+ans[rs];
		for(int i=0,j=SZ(suf[ls]);i<SZ(pre[rs]);++i){
			int nxt=(i<=SZ(pre[rs])-2?pre[rs][i+1].fi:tr[p]+1);
			//R \in [pre[rs][i].fi,nxt)
			while(j>0 && (suf[ls][j-1].se|pre[rs][i].se)>=X)
				--j;
			if(j!=SZ(suf[ls]))
				ans[p]+=(ll)(suf[ls][j].fi-tl[p]+1) * (nxt-pre[rs][i].fi);
		}
		
		//2. pre
		pre[p]=pre[ls];
		for(int i=0;i<SZ(pre[rs]);++i){
			if(pre[p].back().se != (pre[p].back().se | pre[rs][i].se)){
				pre[p].pb(mk(pre[rs][i].fi,pre[p].back().se|pre[rs][i].se));
			}
		}
		//3. suf
		suf[p]=suf[rs];
		for(int i=0;i<SZ(suf[ls]);++i){
			if(suf[p].back().se != (suf[p].back().se | suf[ls][i].se)){
				suf[p].pb(mk(suf[ls][i].fi,suf[p].back().se|suf[ls][i].se));
			}
		}
		
		assert(SZ(pre[p])<=21);
		assert(SZ(suf[p])<=21);
	}
	void build(int p,int l,int r){
		tl[p]=l;tr[p]=r;
		if(l==r){
			ans[p]=(a[l]>=X);
			pre[p].pb(mk(l,a[l]));
			suf[p].pb(mk(l,a[l]));
			return;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		push_up(p);
	}
	void point_modify(int p,int l,int r,int pos,int v){
		if(l==r){
			ans[p]=(v>=X);
			pre[p][0]=mk(l,v);
			suf[p][0]=mk(l,v);
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid)
			point_modify(p<<1,l,mid,pos,v);
		else
			point_modify(p<<1|1,mid+1,r,pos,v);
		push_up(p);
	}
	ll query(int p,int l,int r,int ql,int qr){
		assert(ql>=l);assert(qr<=r);
		if(ql==l && qr==r)
			return ans[p];
		int mid=(l+r)>>1;
		if(qr<=mid)
			return query(p<<1,l,mid,ql,qr);
		else if(ql>mid)
			return query(p<<1|1,mid+1,r,ql,qr);
		else{
			ll res=query(p<<1,l,mid,ql,mid) + query(p<<1|1,mid+1,r,mid+1,qr);
			int ls=p<<1,rs=p<<1|1;ck(ls);ck(rs);
			int j=SZ(suf[ls])-1;
			while(suf[ls][j].fi<ql)
				--j;
			assert(j>=0);
			for(int i=0;i<SZ(pre[rs]) && pre[rs][i].fi<=qr;++i){
				int nxt=(i<=SZ(pre[rs])-2?pre[rs][i+1].fi:tr[p]+1);
				ckmin(nxt,qr+1);
				if((suf[ls][j].se|pre[rs][i].se)<X)
					continue;
				while(j>0 && (suf[ls][j-1].se|pre[rs][i].se)>=X)
					--j;
				res+=(ll)(suf[ls][j].fi-ql+1) * (nxt-pre[rs][i].fi);
			}
			return res;
		}
	}
	SegmentTree(){}
}T;

int main() {
	cin>>n>>m>>X;
	for(int i=1;i<=n;++i)cin>>a[i];
	T.build(1,1,n);
	while(m--){
		int op;cin>>op;
		if(op==1){
			int i,y;cin>>i>>y;
			T.point_modify(1,1,n,i,y);
		}
		else{
			int l,r;cin>>l>>r;
			cout<<T.query(1,1,n,l,r)<<endl;
		}
	}
	return 0;
}
```







---

## 作者：reyik (赞：7)

退咕后的题解

线段树

首先我们发现前缀不同的or 和最多log个

所以我们对于每一个线段树的节点记录，前缀，后缀中，每一个前缀/后缀的$or$和不等于他前一个或后一个的节点位置以及对应的$or$和，由于这个节点数不超过$log$所以暴力合并即可

合并的时候直接把两个节点的前缀/后缀合并起来，就是把后一个节点的前缀/后缀一个一个插入即可

然后最后查询啥的都和普通线段树没什么区别吧

就是注意一下合并的细节即可

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
const int N=2e5+5;
struct node {
  long long cnt;
  vector <pair<int,int>> st,ed;
}t[N<<1];
int n,m,x;
int a[N];
node merge(node a,node b) {
  if(!a.ed.size()) return b;
  if(!b.ed.size()) return a;
  node ret;
  ret.cnt=a.cnt+b.cnt;
  long long tot=0;
  for (auto &i:a.ed) {
    for (auto &j:b.st) {
      if(((i.first|j.first)>=x)) {
        tot+=(1ll*i.second*j.second);
      }
    }
  }
  ret.cnt+=tot;
  ret.st=a.st;
  int tmp;
  tmp=ret.st.back().first;
  for (auto &i:b.st) {
    if(((i.first|tmp)==tmp)) {
      ret.st.back().second+=i.second;
    }
    else {
      ret.st.push_back({i.first|tmp,i.second});
      tmp|=i.first;
    }
  }
  ret.ed=b.ed;
  tmp=ret.ed.back().first;
  for (auto &i:a.ed) {
    if((i.first|tmp)==tmp) {
      ret.ed.back().second+=i.second;
    }
    else {
      ret.ed.push_back({i.first|tmp,i.second});
      tmp|=i.first;
    }
  }
  return ret;
}
void pushup(int x) {
  t[x]=merge(t[x<<1],t[x<<1|1]);
}
void build(int now,int l,int r) {
  if(l==r) {
    t[now].ed.push_back({a[l],1});
    t[now].st.push_back({a[l],1});
    if(a[l]>=x) {
      t[now].cnt=1;
    }
    else t[now].cnt=0;
    return ;
  }
  int mid=(l+r)>>1;
  build(now<<1,l,mid);
  build(now<<1|1,mid+1,r);
  pushup(now);
}
void modify(int now,int l,int r,int y,int z) {
  if(l==r) {
    a[y]=z;
    t[now].st.clear();
    t[now].ed.clear();
    t[now].st.push_back({z,1});
    t[now].ed.push_back({z,1});
    if(a[l]>=x) {
      t[now].cnt=1;
    }
    else t[now].cnt=0;
    return ;
  }
  int mid=(l+r)>>1;
  if(y<=mid) {
    modify(now<<1,l,mid,y,z);
  }
  else modify(now<<1|1,mid+1,r,y,z);
  pushup(now);
}
node query(int now,int l,int r,int L,int R) {
  if(L<=l && r<=R) {
    return t[now];
  }
  node ret;
  int mid=(l+r)>>1;
  if(L<=mid) ret=merge(ret,query(now<<1,l,mid,L,R));
  if(R>mid) ret=merge(ret,query(now<<1|1,mid+1,r,L,R));
  return ret;
}
int main() {
  scanf("%d%d%d",&n,&m,&x);
  for (int i=1;i<=n;++i) {
    scanf("%d",&a[i]);
  }
  build(1,1,n);
  for (int i=1;i<=m;++i) {
    int opt;
    scanf("%d",&opt);
    if(opt==1) {
      int x,y;
      scanf("%d%d",&x,&y);
      a[x]=y;
      modify(1,1,n,x,y);
    }
    else {
      int l,r;
      scanf("%d%d",&l,&r);
      printf("%lld\n",query(1,1,n,l,r).cnt);
    }
  }
  return 0;
}

```

---

## 作者：1saunoya (赞：7)

~~简单数据结构题？~~

我们先考虑一个朴素分治。

$[l, mid]$ 和 $[mid + 1, r]$ 递归求解。

$[l,r]$ 的区间需要通过 $[l, mid]$ 的后缀和 $[mid+1,r]$ 的前缀来求解。

第一次枚举前者的后缀然后移动后者，第二次枚举后者然后移动前者。

这样的复杂度是 $n \log n$ 但是只能支持一次询问（bushi）。

但是我们发现由于 $OR$ 的性质，不会变化超过 $\log$ 次。所以我们考虑线段树在每个节点记录一下是哪些位置让这个发生了改变。

我们记录一个 $st$ 表示区间 $[l,r]$ 从 $l$ 开始计算，会变化的位置以及长度。

同理我们记录一个 $ed$ 表示区间 $[l,r]$ 从 $r$ 开始计算，会变化的位置以及长度。

显然这个信息是可以在线段树上面合并的，每次计算当前区间的复杂度也只需要 $\log^2$。

然后这题就做完了。

---

## 作者：Hanx16Kira (赞：4)

# Sonya and Bitwise OR

[CF1004F (Luogu)](https://www.luogu.com.cn/problem/CF1004F)


## Solution

今天测试的 T4 ，赛时只做出来了 $\mathcal O(mn\log n)$ 的做法，所以发现是 CF 原题后就赶快来写正解了。

先考虑暴力该如何做。显然暴力思路很简单，直接枚举子区间的左端点和右端点即可，这样的时间复杂度是 $\mathcal O(mn^2)$ 这一级别的。

然后来考虑如何优化。观察题目要求的运算，稍微想一下就可以知道当子区间的左端点固定时，区间或和是随着右端点右移而变大的，这启发我们用**尺取法/双指针**法来做这道题。因为当左端点右移的时候并不能很方便的得出新的区间或和，所以选择线段树来维护区间或和。这一方法的时间复杂度是 $\mathcal O(mn\log n)$ 的。

难道优化就到此为止了吗？并不是。还是假设确定子区间左端点，那么当我们右移右端点的时候，每一次改变区间或和的时候都至少会对答案的二进制改变一位，所以当左端点固定的时候，不同的区间或和最多只有 $\log a_i$ 个。所以这一特点启发我们在线段树上维护不同的区间**前缀或和**和**后缀或和**的开头位置以及对应的区间或和，同时维护当前线段树区间的答案。在上传的时候直接暴力维护这三个值即可。那么现在的问题就变成了如何利用这些值来求答案。在这里只需要讨论区间跨过了线段树区间中点这一情况，如果不是这种情况都可以递归进子树转化成为这一问题。

如果询问区间跨过了线段树区间中点，那么这个区间的答案就应该是左右子树的答案之和加上左端点在左子树、右端点在右子树的情况数，因为维护好了区间**前后缀或和**，所以直接利用这些东西进行尺取即可，具体看代码分析。

在代码实现的过程中有一些需要注意的点：

1. `vector` 的 `size()` 返回的是一个 `unsigned` 值，需要强制转为 `int` 类才可以使用，否则做减法运算在答案应该是 $-1$ 时会出现问题。
2. `|` 或运算的优先级是在逻辑运算符之后的，所以或运算后跟逻辑运算符的时候一定记得**打括号**！！！（我因为这个原因无端调了 $2.5$ 小时的代码）

### Code

```c++
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof a)
#define int long long
#define MP make_pair
#define F first
#define S second
using namespace std;
template<typename T> void read(T &k)
{
	k=0;T flag=1;char b=getchar();
	while (!isdigit(b)) {flag=(b=='-')?-1:1;b=getchar();}
	while (isdigit(b)) {k=k*10+b-48;b=getchar();}
	k*=flag;
}
const int _SIZE=1e5;
int n,m,x,a[_SIZE+5];
#define LC (k<<1)
#define RC ((k<<1)|1)
int ans[(_SIZE<<2)+5];//记录线段树区间答案
vector<pair<int,int> >up[(_SIZE<<2)+5],down[(_SIZE<<2)+5];//up表示前缀，down表示后缀，first表示位置，second表示值
void pushup(int k,int l,int r)
{
	ans[k]=ans[LC]+ans[RC];//先继承左右子树答案
	for (int i=0,j=down[LC].size();i<up[RC].size();i++)//对左右子树进行尺取，i在右子树，j在左子树
	{
		int tail=((i<=(int)up[RC].size()-(int)2) ? up[RC][i+1].F : r+1);//计算尺取的上界
		while (j>0 && (down[LC][j-1].S|up[RC][i].S)>=x) j--;//将j代表的位置向后移（因为down是后缀所以位置是从大到小放进去的）
		if (j!=down[LC].size()) ans[k]+=(down[LC][j].F-l+1)*(tail-up[RC][i].F);//如果存在j满足条件则更新答案，前半段长度为j对应的位置到下界的数字总数，后半段则是i对应的位置到上界的数字总数
	}
	up[k]=up[LC];//先继承
	for (int i=0;i<up[RC].size();i++)
		if (up[k].back().S != (up[RC][i].S|up[k].back().S)) //如果可以得到新的或值
			up[k].push_back(MP(up[RC][i].F,up[RC][i].S|up[k].back().S));//将这个新的区间或值加入
	down[k]=down[RC];//与up的更新基本相似
	for (int i=0;i<down[LC].size();i++)
		if (down[k].back().S != (down[LC][i].S|down[k].back().S)) 
			down[k].push_back(MP(down[LC][i].F,down[LC][i].S|down[k].back().S));
}
void build(int k,int l,int r)//建树
{
	if (l==r)
	{
		ans[k]=(a[l]>=x);
		up[k].push_back(MP(l,a[l]));//建树的时候直接插入即可
		down[k].push_back(MP(l,a[l]));
		return;
	}
	int mid=l+r>>1;
	build(LC,l,mid);
	build(RC,mid+1,r);
	pushup(k,l,r);
}
void update(int k,int l,int r,int pos,int v)
{
	if (l==r && l==pos)
	{
		ans[k]=(v>=x);
		up[k][0]=MP(l,v);//建树的时候已经保证有[k][0]了，所以更新[k][0]即可
		down[k][0]=MP(l,v);
		return;
	}
	if (l>pos || r<pos) return;
	int mid=l+r>>1;
	update(LC,l,mid,pos,v);
	update(RC,mid+1,r,pos,v);
	pushup(k,l,r);
}
int query(int k,int l,int r,int a,int b)
{
	if (l==a && r==b) return ans[k];
	int mid=l+r>>1;
	if (b<=mid) return query(LC,l,mid,a,b);//在左子树，直接递归入左子树
	else if (a>mid) return query(RC,mid+1,r,a,b);//与左子树同理
	else
	{
		int res=query(LC,l,mid,a,mid)+query(RC,mid+1,r,mid+1,b);//先分别统计左右子树再统计跨越中点的答案
		int j=(int)down[LC].size()-(int)1;
		while (down[LC][j].F<a) j--;//先找到j的上界
		for (int i=0;i<up[RC].size() && up[RC][i].F<=b;i++)//尺取，与上传相似
		{
			int tail=(i<=(int)up[RC].size()-(int)2)?up[RC][i+1].F:r+1;
                        tail=min(tail,b+1);//上界应该保证在询问区间内
			if ((down[LC][j].S|up[RC][i].S)<x) continue;
			while (j>0 && (down[LC][j-1].S|up[RC][i].S)>=x) j--;
			res+=(down[LC][j].F-a+1)*(tail-up[RC][i].F);
		}
		return res;
	}
}
signed main()
{
	read(n),read(m),read(x);
	for (int i=1;i<=n;i++) read(a[i]);
	build(1,1,n);
	//return 0;
	for (int i=1;i<=m;i++)
	{
		int op,l,r;
		read(op),read(l),read(r);
		if (op==1) update(1,1,n,l,r);
		else printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}
```

---

## 作者：Great_Influence (赞：3)

线段树。

首先，我们考虑如何处理一次询问。

我们从区间中点开始，分别向两边求出前/后缀$or$的值，然后枚举指针向两边扫，利用$two-pointer$来求出所有跨过中点的答案。然后，再向两边递归求解。

这样做的话，时间复杂度为$O(len\log len)$，显然无法承受。

考虑以下几个优化:

1. 可以发现，有用的前/后缀明显只有$\log$个。我们只记录这$\log$个转折点即可。

2. 发现计算的区间存在大量重复。我们考虑利用线段树来维护区间答案。

对于每个线段树上区间$[l,r]$，我们将$[l,r]$这一段跨过中点的答案计算出来，然后再加上两边区间的答案即可得到整个答案。那么，每次计算答案时，如果询问的区间被完全覆盖，则直接返回预处理的答案。否则计算完跨区间中点的答案后，再加上向两边分治的答案即可。

对于修改操作，直接修改后在上传答案即可。

每次求区间答案是$O(\log n)$的。每次修改操作会求$O(\log n)$次，复杂度为$O(\log^2n)$，每次询问操作最多被分成$O(\log n)$个区间，时间复杂度为$O(\log^2n)$。再加上预处理，总时间复杂度为$O((n+q)\log^2 n)$。

如果将区间补齐至$2$的次幂，则可以利用猫锟博客上的小技巧快速查找区间位置，修改操作可以变为非递归式的。这样写常数特别小。

代码:
```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define mp make_pair
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;

using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
    {
        return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
    }
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
    {
        x=0;static char ch;T f=1;
        for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
        for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
        x*=f;
    }

    template<typename T>inline void write(T x,char ch='\n')
    {
        if(!x)*nowps++='0';
        if(x<0)*nowps++='-',x=-x;
        static uint32 sta[111],tp;
        for(tp=0;x;x/=10)sta[++tp]=x%10;
        for(;tp;*nowps++=sta[tp--]^48);
        *nowps++=ch;
    }
}
using namespace IO;

inline void file()
{
#ifndef ONLINE_JUDGE
    FILE*DSA=freopen("water.in","r",stdin);
    FILE*SDU=freopen("water.out","w",stdout);
#endif
}

const int MAXN=1<<18;

static int n,m,X,N,a[MAXN],lg2[MAXN];

void init()
{
	read(n),read(m),read(X);
	Rep(i,1,n)read(a[i]);
	for(N=2;N<n;N<<=1);
	Rep(i,1,N)lg2[i]=lg2[i>>1]+1;
}

#define eb emplace_back
#define fi first
#define se second

namespace neko
{
	typedef pair<int,int>PII;
	static vector<PII>lp[MAXN<<1],rp[MAXN<<1];
	static int lb[MAXN<<1],rb[MAXN<<1];
	static ll ans[MAXN<<1];

	inline int getps(int l,int r)
	{
		static int ls,rs;
		ls=l+N-1,rs=r+N-1;
		return ls>>lg2[ls^rs];
	}

	inline ll calc(int l,int r)
	{
		static int h,ls,rs,llim,rlim;
		h=getps(l,r),ls=h<<1,rs=h<<1|1;
		static ll sm;sm=0ll;
		rlim=lp[rs].size()-1,llim=rp[ls].size()-1;
		for(register int i=0,j=rlim;i<=llim&&j>=0;--j)
		{
			if(lp[rs][j].se>r)continue;
			while(i<=llim&&(rp[ls][i].se<l||(rp[ls][i].fi|lp[rs][j].fi)<X))++i;
			if(i>llim)break;
			sm+=1ll*(rp[ls][i].se-(l-1))*
				((j==rlim?r+1:min(lp[rs][j+1].se,r+1))-lp[rs][j].se);
		}
		return sm;
	}

	inline void pushup(int h)
	{
		lp[h]=lp[h<<1];
		static int it;it=lp[h<<1].back().fi;
		for(auto v:lp[h<<1|1])if((v.fi|it)>it)lp[h].eb(v.fi|it,v.se),it|=v.fi;
		
		rp[h]=rp[h<<1|1];
		it=rp[h<<1|1].back().fi;
		for(auto v:rp[h<<1])if((v.fi|it)>it)rp[h].eb(v.fi|it,v.se),it|=v.fi;
	
		ans[h]=calc(lb[h],rb[h])+ans[h<<1]+ans[h<<1|1];
	}
	
	void make_tree(int h,int l,int r)
	{
		lb[h]=l,rb[h]=r;
		if(l==r){lp[h].eb(a[l],l),rp[h].eb(a[l],l),ans[h]=a[l]>=X;return;}
		int mid=(l+r)>>1;
		make_tree(h<<1,l,mid),make_tree(h<<1|1,mid+1,r);
		pushup(h);
	}

	inline void modify(int x,int y)
	{
		static int ps;ps=x+N-1;
		a[x]=y,ans[ps]=(a[x]>=X);
		lp[ps].clear(),rp[ps].clear();
		lp[ps].eb(a[x],x),rp[ps].eb(a[x],x);
		for(ps>>=1;ps;ps>>=1)pushup(ps);
	}

	ll Q(int L,int R)
	{
		int h=getps(L,R);
		if(L==lb[h]&&R==rb[h])return ans[getps(L,R)];
		return Q(L,rb[h<<1])+Q(lb[h<<1|1],R)+calc(L,R);
	}
}
using namespace neko;

inline void solve()
{
	make_tree(1,1,N);
	static int opt,x,y;
	Rep(i,1,m)
	{
		read(opt),read(x),read(y);
		if(opt==1)modify(x,y);
		else write(Q(x,y));
	}
	flush();
}

int main()
{
	init();
	solve();
    return 0;
}
```

---

## 作者：fanypcd (赞：2)

假设只有一个全局询问，考虑分治。

现在需要计算跨越区间中点的左、右端点对数。记录以区间中点为一端的前后缀，搭配双指针就可以 $O(n)$ 计算。（准确的说是以下标为区间中点 +1 的点为一端的前缀）。

注意到固定一端，区间或和是随区间长度单调不降的，而且一次变大至少改变一个二进制位，所以固定一端点的所有区间或和的个数是对数级别的。（区间 $\gcd$ 也有类似的性质。）

就可以利用线段树天然的分治结构以及可以快速合并区间的优点来加速查询。

对于每个线段树上的节点，维护当前节点对应区间的前后缀或和（可以开两个```vector```，需要记录值以及对应的位置下标）。

然后在结构体中封装合并的函数可以大大简化代码。

```cpp
struct value {
    vector<pair<int, int>> pre, suf;
    ll sum; int l, r;
    value() {pre.clear(); suf.clear(); sum = 0; return;}
};
#define mp make_pair
value operator + (value a, value b) {
    if(!a.pre.size()) return b;
    if(!b.pre.size()) return a;
//    任意一个为空返回另一个（query函数内用）
	
    value res; res.l = a.l, res.r = b.r;
    res.sum = a.sum + b.sum;
    res.pre = a.pre;
    for(auto now : b.pre)
        if((a.pre.back().fir | now.fir) != res.pre.back().fir)
            res.pre.emplace_back(mp(a.pre.back().fir | now.fir, now.sec));
//    合并前缀
	
	res.suf = b.suf;
    for(auto now : a.suf)
        if((b.suf.back().fir | now.fir) != res.suf.back().fir)
            res.suf.emplace_back(mp(b.suf.back().fir | now.fir, now.sec));
//    合并后缀
	
	for(int i = 0, j = b.pre.size() - 1; i < (int)a.suf.size(); i++) {
        while(j >= 0 && (a.suf[i].fir | b.pre[j].fir) >= x) j--;
        if(j + 1 < (int)b.pre.size())
            res.sum += 1ll * (a.suf[i].sec - (i + 1 < (int)a.suf.size() ? a.suf[i + 1].sec : a.l - 1))
             * (b.r - b.pre[j + 1].sec + 1);
    }
//    计算答案
    return res;
}
```

其他的就是线段树的基本操作了，复杂度 $O(n \log n \log V)$。

[Code](https://www.luogu.com.cn/paste/iathg5ed).

---

## 作者：Piwry (赞：1)

很有趣的一道题

## 解析

首先考虑将两个区间 $[l_1, r_1], [l_2, r_2]$ 合并（左右 “贴” 在一起）后会产生的**新**贡献

显然我们需要统计所有的 $i \in [l_1, r_1], j\in [l_2, r_2]$ 产生的 $[i, r_1][l_2, j]$（$[a, b][c, d]$ 这样写可能不太严谨...不过感性理解下 \kk）区间，它们各自的区间 “`|`” 是否超过 $x$

暴力枚举是 $|[l, r]|^2$ 的。但注意到不同的 前缀/后缀 区间 “`|`” 至多只有 $\log a$ 种；因此将同一值的 前缀/后缀 区间 “缩” 到一起枚举，复杂度就变成 $\log^2 a$ 的了。另外还发现枚举可以用双指针优化（具体来说，若有 $[i, r_1][l_2, j]$ 的区间 “`|`” 值大于等于 $x$，那么对于 $k<i$，$[k, r_1][l_2, j]$ 的区间 “`|`” 值也一定大于等于 $x$），于是复杂度就降到了 $\log a$

（以上这些内容其实可以考虑直接写到结构体里，下面会方便很多）

接着我们考虑建出一颗线段树。对于线段树上的每个结点 $[l, r]$，我们维护 $[l, r]$ 区间内部的贡献以及 $[l, r]$ 的 前缀/后缀 区间 “`|`” 值不同的区块。前者可以通过刚才的合并方式 $\log a$ 地 `pushup`；后者的话，例如维护前缀区间 “`|`” 值的区块，我们可以先继承线段树左儿子的区块，然后将右儿子区间以前缀区块（“`|`” 值相同的为一块）一块块添加（其实就是右儿子维护的的前缀区间 “`|`” 值不同的区块），这样这部分复杂度也是 $\log a$ 的

对于每次询问，我们在线段树上找到 $\log n$ 块区间；这些区间恰好可以 “拼” 成询问区间。这些区间内部的答案我们已经在线段树上处理出来了，于是只需再用刚才的合并方式 $\log a$ 地**合并这些区间**，共合并 $\log n-1$ 次，就可以得到询问区间的总贡献了（这部分听起来很奇妙，其实实现和普通线段树询问很相似；合并只需在每次返回时处理就行了）

## CODE

可能描述的不是很清楚X，具体可见代码（感觉实现还是蛮清晰的）

```cpp
#include <cstdio>
#include <vector>
#define ll long long
using std::vector;

const int MAXN =1e5+20, MAXSeg =1<<18;

/*------------------------------Variable------------------------------*/

int X;

/*------------------------------Seg------------------------------*/

int N =1;
struct chunk{
	int val, len;
	
	chunk(){}
	chunk(const int &VAL, const int &LEN):val(VAL), len(LEN){}
};
struct interval{/*区间*/
	ll ctrb;/*该区间的贡献*/
	vector<chunk> pre, suf;/*前后缀 "|" 区块*/
	
	interval(){}
	interval(const int &VAL){
		ctrb =(VAL >= X);
		pre.push_back(chunk(VAL, 1));
		suf.push_back(chunk(VAL, 1));
	}
	interval(const interval &A, const interval &B){
		ctrb =A.ctrb+B.ctrb;
		
		int Sum =0;
		// 有单调性，双指针统计 //
		for(int i =0, j =(int)B.pre.size()-1; i < (int)A.suf.size(); ++i){
			#define I A.suf[i]
			#define J B.pre[j]
			while(j >= 0 && (I.val|J.val) >= X)
				Sum +=J.len, --j;
			ctrb +=1ll*I.len*Sum;
			#undef I
			#undef J
		}
		
		pre.assign(A.pre.begin(), A.pre.end());
		for(int i =0; i < (int)B.pre.size(); ++i){
			#define NW pre[(int)pre.size()-1]
			#define NEW B.pre[i]
			if(pre.empty())
				pre.push_back(chunk(NEW.val, NEW.len));
			else if((NW.val|NEW.val) != NW.val)
				pre.push_back(chunk((NW.val|NEW.val), NEW.len));
			else
				NW.len +=NEW.len;
			#undef NW
			#undef NEW
		}
		suf.assign(B.suf.begin(), B.suf.end());
		for(int i =0; i < (int)A.suf.size(); ++i){
			#define NW suf[(int)suf.size()-1]
			#define NEW A.suf[i]
			if(suf.empty())
				suf.push_back(chunk(NEW.val, NEW.len));
			else if((NW.val|NEW.val) != NW.val)
				suf.push_back(chunk((NW.val|NEW.val), NEW.len));
			else
				NW.len +=NEW.len;
			#undef NW
			#undef NEW
		}
	}
}node[MAXSeg];

inline void pushup(const int &x){
	node[x] =interval(node[x<<1], node[(x<<1)|1]);
}

void modify(const int &pos, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr){
		node[x] =interval(val);
		return;
	}
	int mid =(nl+nr)>>1;
	if(pos <= mid)
		modify(pos, val, nl, mid, x<<1);
	else
		modify(pos, val, mid+1, nr, (x<<1)|1);
	pushup(x);
}

interval query(const int &l, const int &r, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == l && nr == r)
		return node[x];
	int mid =(nl+nr)>>1;
	if(r <= mid)
		return query(l, r, nl, mid, x<<1);
	else if(l >= mid+1)
		return query(l, r, mid+1, nr, (x<<1)|1);
	else
		return interval(query(l, mid, nl, mid, x<<1), query(mid+1, r, mid+1, nr, (x<<1)|1));
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

void write(const ll &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

int main(){
	int n =read(), m =read();
	X =read();
	
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		node[i] =interval(read());
	for(int i =N-1; i >= 1; --i)
		pushup(i);
	
	for(int t =0; t < m; ++t){
		int op =read();
		if(op == 1){
			int i =read(), y =read();
			modify(i, y);
		}
		else{
			int l =read(), r =read();
			write(query(l, r).ctrb);
			putchar('\n');
		}
	}
}
```

---

## 作者：phigy (赞：0)

这里提供一个查询做到 $O(\log n)$ 的做法。（虽然没啥意义）

---------

我们设前驱 $p_i=\max_{\bigoplus_{k=j}^i\{a_k\}\ge x,j\leq i}\{j\}$，就是指 $j$ 左边最大的 $i$ 使得  $i$ 到 $j$ 的异或和不小于 $x$ 。

那么 $l$ 到 $r$ 的答案就是：$\sum_{i=l}^r \max\{p_i-l+1,0\}$。
  
我们发现这个 $\max$ 不好直接做，考虑先做一棵维护异或和的线段树，再从左端点线段树二分找一个异或和不小于 $x$ 连续段即为 $l$ 后驱就可以去掉 $\max$ 了。
  
当然我们也可以直接设后驱 $q_i=\max_{\bigoplus_{k=j}^i\{a_k\}\ge x,j\ge i}\{j\}$。  
  
那么 $l$ 到 $r$ 的答案就是：$\sum_{i=q_l}^r p_i-l+1$。查询就是 $O(\log n)$ 的了。


  
然后怎么维护 $p,q$ 捏，我们发现一个点左右连续的异或和各只有 $\log a$ 种，所以这东西我们还得用其它题解给的方法维护。

我们每次修改的时候，在 $[1,x]$ 的不同异或后缀与 $[x,n]$ 的不同异或前缀间做双指针再用线段树修改对应的 $p,q$ 连续段，修改总体是 $O(\log n\log a)$。

---

