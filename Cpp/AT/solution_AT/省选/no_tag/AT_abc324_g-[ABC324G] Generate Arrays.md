# [ABC324G] Generate Arrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc324/tasks/abc324_g

高橋くんは、長さ $ N $ の数列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N) $ を持っています。 $ A $ は $ (1,2,\ldots,N) $ の順列です。

高橋くんは、操作を $ Q $ 回行って、$ 1+Q $ 個の数列を作ろうとしています。 **$ 0 $ 番の数列を $ A $ として**、高橋くんは一連の操作を始めます。 $ i $ 回目 $ (1\leq\ i\leq\ Q) $ の操作は、整数の $ 3 $ つ組 $ (t\ _\ i,s\ _\ i,x\ _\ i) $ を用いて表され、次のような操作に対応します（ 入出力例の説明も参考にしてください）。

- $ t\ _\ i=1 $ のとき、高橋くんは $ s\ _\ i $ 番 $ (0\leq\ s\ _\ i\lt\ i) $ の数列から $ x\ _\ i $ 個目より後の要素を取り除き、取り除いた要素を順序を保って新しく $ i $ 番の数列とする。
- $ t\ _\ i=2 $ のとき、高橋くんは $ s\ _\ i $ 番 $ (0\leq\ s\ _\ i\lt\ i) $ の数列から値が $ x\ _\ i $ より大きい要素を取り除き、取り除いた要素を順序を保って新しく $ i $ 番の数列とする。

ただし、長さ $ L $ の数列 $ X $ について、$ X $ のどの要素も「$ 0 $ 個目より後の要素」です。 また、$ L\leq\ l $ を満たす任意の $ l $ について $ X $ のどの要素も「$ l $ 個目より後の要素」ではありません。

$ i=1,2,\ldots,Q $ について、$ i $ 回目の操作が終わった**直後**の $ i $ 番の数列の長さを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq2\times10^5 $
- $ 1\leq\ A\ _\ i\leq\ N\ (1\leq\ i\leq\ N) $
- $ A\ _\ i\neq\ A\ _\ j\ (1\leq\ i\lt\ j\leq\ N) $
- $ 1\leq\ Q\leq2\times10^5 $
- $ t\ _\ i=1,2\ (1\leq\ i\leq\ Q) $
- $ 0\leq\ s\ _\ i\lt\ i\ (1\leq\ i\leq\ Q) $
- $ 0\leq\ x\ _\ i\leq\ N\ (1\leq\ i\leq\ Q) $
- 入力はすべて整数

### Sample Explanation 1

はじめ、高橋くんは長さ $ 10 $ の数列 $ A=(1,8,7,4,5,6,3,2,9,10) $ を持っています。 高橋くんは、$ 0 $ 番の数列を $ A=(1,8,7,4,5,6,3,2,9,10) $ として一連の操作を開始します。 $ 1 $ 回目の操作では、$ 0 $ 番の数列の $ 4 $ より大きな要素 $ 8,7,5,6,9,10 $ を取り除き、これらを新しく $ 1 $ 番の数列にします。この操作が終わったとき、$ 0,1 $ 番の数列はそれぞれ $ (1,4,3,2),(8,7,5,6,9,10) $ になります。 $ 2 $ 回目の操作では、$ 1 $ 番の数列の $ 2 $ 個目より後の要素 $ 5,6,9,10 $ を取り除き、これらを新しく $ 2 $ 番の数列にします。この操作が終わったとき、$ 0,1,2 $ 番の数列はそれぞれ $ (1,4,3,2),(8,7),(5,6,9,10) $ になります。 $ 3 $ 回目以降の操作について、$ i $ 回目の操作が終わったときの $ 0,1,2,\ldots,i $ 番の数列はそれぞれ以下のようになります。 - $ (1,2),(8,7),(5,6,9,10),(4,3) $ - $ (1,2),(8,7),(5),(4,3),(6,9,10) $ - $ (1),(8,7),(5),(4,3),(6,9,10),(2) $ $ i=1,2,\ldots,5 $ 回目の操作が終わったときの $ i $ 番の数列の長さはそれぞれ $ 6,4,2,3,1 $ なので、これらをそれぞれの行に出力してください。

### Sample Explanation 2

操作の結果、空の数列が生じることもあります。

## 样例 #1

### 输入

```
10
1 8 7 4 5 6 3 2 9 10
5
2 0 4
1 1 2
2 0 2
2 2 5
1 0 1```

### 输出

```
6
4
2
3
1```

## 样例 #2

### 输入

```
8
6 7 8 4 5 1 3 2
5
2 0 0
1 1 0
2 2 0
1 3 8
2 2 3```

### 输出

```
8
8
8
0
0```

## 样例 #3

### 输入

```
30
20 6 13 11 29 30 9 10 16 5 8 25 1 19 12 18 7 2 4 27 3 22 23 24 28 21 14 26 15 17
10
1 0 22
1 0 21
2 0 15
1 0 9
1 3 6
2 3 18
1 6 2
1 0 1
2 5 20
2 7 26```

### 输出

```
8
1
8
4
2
5
3
8
1
1```

# 题解

## 作者：良心WA题人 (赞：9)

谨以此题解纪念首次AKABC

## problem

给定一个长度为 $n$ 的排列。有两种操作：

1. 从序列的第 $x$ 个位置将序列 $s$ 分成两部分，其中前一部分（含 $x$）为新的序列 $s$，后面一部分为序列 $i$。
2. 按照值域，不改变原序列顺序从值 $x$ 分为两部分，小于等于的为 $s$，大于的为 $i$。

每次操作完后询问序列 $i$ 的长度。

## solution

可以发现序列每次修改为区间 $s$ 的一段前缀并将一段后缀加入到 $i$，而操作 $2$ 是将值域分成一段前缀和一段后缀。那么我们可以记录一个区间四个信息 $\text l,\text r,\min,\max$，表示该区间为 $\text l$ 到 $\text r$ 中值域为 $\min$ 到 $\max$ 的数。

已知上面的信息后序列的长度可以直接用主席树算出来。直接套用模板即可。那么接下来的问题是处理修改操作。

首先考虑操作 $2$，将区间 $s$ 的信息复制一份到区间 $i$ 后把 $s$ 的 $\max$ 设置为 $x$，$i$ 的 $\min$ 设置为 $x+1$ 即可。

那么操作 $1$ 呢？我们发现就是要求区间 $[\text l,\text r]$ 中 $\ge\min$ 且 $\le \max$ 的第 $k$ 个数。这是经典的主席树可以解决的问题。再写一颗可以做到单 $\log$，但是直接套用之前的主席树加上二分可以双 $\log$ 通过此题。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int NN=2e5+4;
int minn[NN],maxx[NN],l[NN],r[NN],idx=0,root[NN];
struct segment_tree
{
	int lson,rson,sum;
}tr[NN*40];
int update(int u,int l,int r,int id)
{
	int point=++idx;
	tr[point]=tr[u];
	if(l==r)
	{
		tr[point].sum++;
		return point;
	}
	int mid=l+(r-l)/2;
	if(id<=mid)
		tr[point].lson=update(tr[u].lson,l,mid,id);
	else
		tr[point].rson=update(tr[u].rson,mid+1,r,id);
	tr[point].sum=tr[tr[point].lson].sum+tr[tr[point].rson].sum;
	return point;
}
int ask(int u,int v,int l,int r,int k)
{
	if(l==r)
		return l;
	int mid=l+(r-l)/2;
	if(tr[tr[v].lson].sum-tr[tr[u].lson].sum>=k)
		return ask(tr[u].lson,tr[v].lson,l,mid,k);
	else
		return ask(tr[u].rson,tr[v].rson,mid+1,r,k-tr[tr[v].lson].sum+tr[tr[u].lson].sum);
}
int query(int u,int v,int l,int r,int ql,int qr)
{
	if(ql>qr)
		return 0;
	if(l>=ql&&r<=qr)
		return tr[u].sum-tr[v].sum;
	int mid=l+(r-l)/2,res=0;
	if(ql<=mid)
		res+=query(tr[u].lson,tr[v].lson,l,mid,ql,qr);
	if(qr>mid)
		res+=query(tr[u].rson,tr[v].rson,mid+1,r,ql,qr);
	return res;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		root[i]=update(root[i-1],1,n,x);
	}
	l[0]=1,r[0]=n;
	minn[0]=1,maxx[0]=n;
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int opt,s,x;
		scanf("%d%d%d",&opt,&s,&x);
		l[i]=l[s],r[i]=r[s],minn[i]=minn[s],maxx[i]=maxx[s];
		if(opt==1)
		{
			int L=l[s]-1,R=r[s];
			while(L<R)
			{
				int mid=L+(R-L+1)/2;
				if(query(root[mid],root[l[s]-1],1,n,minn[s],maxx[s])<=x)
					L=mid;
				else
					R=mid-1;
			}
			l[i]=L+1;
			r[s]=L;
		}
		else
		{
			minn[i]=max(minn[i],x+1);
			maxx[s]=min(maxx[s],x);
		}
		printf("%d\n",max(0,query(root[r[i]],root[l[i]-1],1,n,minn[i],maxx[i])));
	}
	return 0;
}
```

---

## 作者：不知名用户 (赞：5)

给定一个序列 $a_1,a_2,\cdots,a_n$ 为 0 号序列，共生成 $q$ 个序列（不含 0 号），$i$ 号序列生成方法如下：

选择 $0\le s<i$ 号序列，进行两种操作之一：
- 分裂出下标大于 $x$ 的元素到 $i$ 号序列
- 分裂出值大于 $x$ 的元素到 $i$ 号序列

**每次操作对 $s$ 号序列有后效性**。每次操作之后**马上**输出序列的大小。

可以把数组看成方块矩形，把 $(i,a_i)$ 看成一个点，不难发现对于每个操作后的序列，都能用一个（可能多个）矩形表示，使得矩形内点的 $x$ 坐标集合恰好为该序列对应 0 号序列的下标。于是每一次操作可以看成在 $s$ 号序列的矩形上切一刀分出 $i$ 号序列。注意特判边界情况。

说着简单写起来麻烦。因为你要拿到序列包含的元素个数，即矩形内的点数，于是就要维护二维前缀和，而且还不能直接用朴素方法维护，要使用可持久化线段树（改天搞个链接讲一下）。而且进行“下标分裂”操作时要得到那一刀的横坐标就要二分并加线段树的 $\log$，常数有亿点点大，不过听说有巨佬可以单 $\log$ 实现查询坐标。[赛后 AC code](https://atcoder.jp/contests/abc324/submissions/46946010)。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

struct node
{
	int sum, ls, rs;
	#define ls(x) st[x].ls
	#define rs(x) st[x].rs
	#define sum(x) st[x].sum
}st[N*20*2];
int cur, rt[N], n;
inline int clone(int p)
{
	st[++cur] = st[p];
	return cur;
}
inline void upd(int p)
{
	sum(p) = sum(ls(p)) + sum(rs(p));
}
int build(int p, int L, int R)
{
	p = ++cur;
	if(L==R) return p;
	int mid = L + R >> 1;
	ls(p) = build(ls(p),L,mid);
	rs(p) = build(rs(p),mid+1,R);
	return p;
}
int ins(int p, int pos, int val, int L, int R)
{
	p = clone(p);
	if(L==R) return sum(p) = val, p;
	int mid = L + R >> 1;
	if(pos<=mid) ls(p) = ins(ls(p),pos,val,L,mid);
	else rs(p) = ins(rs(p),pos,val,mid+1,R);
	upd(p);
	return p;
}
int ask(int p, int l, int r, int L, int R)
{
	if(l<=L&&R<=r) return sum(p);
	int mid = L + R >> 1, ans = 0;
	if(l<=mid) ans += ask(ls(p),l,r,L,mid);
	if(mid<r) ans += ask(rs(p),l,r,mid+1,R);
	return ans; 
}
int calc(int idx, int idy, int valx, int valy)
{
	int ans = ask(rt[idy],valx,valy,1,n) - ask(rt[idx-1],valx,valy,1,n);
//	printf("calc(%d,%d,%d,%d)=%d\n", idx, idy, valx, valy, ans);
	return ans;
}

int idx[N], idy[N], valx[N], valy[N];

int main()
{
	int i;
	cin>>n;
	rt[0] = build(0,1,n);
	for(i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		rt[i] = ins(rt[i-1],a,1,1,n);
	}
	idx[0] = 1, idy[0] = n;
	valx[0] = 1, valy[0] = n;
	int q;cin>>q;
	for(i=1;i<=q;i++)
	{
		int t, s, x;
		cin>>t>>s>>x;
		if(!idx[s])
		{
			cout<<"0\n";
			continue;//没有
		}
		idx[i] = idx[s];
		idy[i] = idy[s];
		valx[i] = valx[s];
		valy[i] = valy[s];
		if(t==1)
		{
			if(x==0)
			{
				idx[s] = 0;
				cout<<calc(idx[i],idy[i],valx[i],valy[i])<<'\n';
				continue;
			}
			if(calc(idx[s],idy[s],valx[s],valy[s])<=x)
			{
				idx[i] = 0;
				cout<<"0\n";
				continue;
			}
			int l = idx[s], r = idy[s], mid;
			while(l < r)
			{
				mid = l + r + 1 >> 1;
				if(calc(idx[s],mid,valx[s],valy[s])<=x) l = mid;
				else r = mid - 1;
			}
			idy[s] = l;
			idx[i] = l + 1;
		}
		else if(t==2)
		{
			if(valx[s]>x)
			{
				idx[s] = 0;
				cout<<calc(idx[i],idy[i],valx[i],valy[i])<<'\n';
				continue;
			}
			if(valy[s]<=x)
			{
				idx[i] = 0;
				cout<<"0\n";
				continue;
			}
			valx[i] = x + 1;
			valy[s] = x;
		}
		if(idx[i]==0) cout<<"0\n";
		else cout<<calc(idx[i],idy[i],valx[i],valy[i])<<'\n';
	}
	return 0;
}
```

---

## 作者：Nightingale_OI (赞：4)

## AT_abc324_g

### 大意

给定数组 $A_0$；$q$ 次，第 $i$ 次操作给定 $s$ 和 $x$，有两种操作：

1. 把 $A_{s}$ 中下标大于 $x$ 的元素分裂成一个新的数组 $A_i$。
2. 把 $A_{s}$ 中值大于 $x$ 的元素分裂成一个新的数组 $A_i$。

这两种操作都不会改变元素相对顺序。  
下标从 $1$ 开始，下标 $x$ 可能不存在，此时只关心 $A_s$ 里存在的下标。

输出每次分裂出的数组大小。

### 思路

因为不改变元素相对顺序，那么每个数组 $A_i$ 可以表示为从 $A_0$ 里下标在 $[pl_i,pr_i]$，值在 $[vl_i,vr_i]$ 内所有元素组成的数组。

---

因为要输出每次分裂出的数组大小，所以需要快速计算满足条件的数的数量。  
这一部分可以分块维护，每一块开一个桶 $c_i$ 表示块内 $\leq i$ 的数出现次数，整块可以 $O(1)$ 查询。  
这个非常经典的分块复杂度平衡后块长 $B=\sqrt n$，单次查询 $O(\sqrt n)$。

---

先看简单的 $2$ 操作，只需要把值域分裂成 $[vl_s,x]$ 和 $[x+1,vr_s]$ 分别给 $A_s$ 和 $A_i$ 就好了。

```cpp
pl[i]=pl[s];pr[i]=pr[s];
vl[i]=x+1;vr[i]=vr[s];vr[s]=x;
```

如果只这样写，那么恭喜你，犯了一个严重的错误。  
可能出现 $vl_s>vr_s$，假设此时区间为 $[7,5]$，此时 $x=3$，分裂成 $[7,3]$ 和 $[4,5]$，属于是无中生有。  
加上一句 `x=min(max(x,vl[s]-1),vr[s]);` 可以解决这个问题。

再看 $1$ 操作，我们需要快速找到 $[pl_s,pr_s]$ 内满足值在 $[vl_s,vr_s]$ 内的第 $x$ 个数。  
一种简单的写法是套二分，这样问题变为 $[pl_s,mid]$ 内满足值域的数量，即上面分块所求。  
复杂度 $O(q\sqrt n\log n)$，太简单了就不放代码了。  
参考查询，散块暴力跳，整块先判断第 $x$ 个数是否在块里，在就遍历这个块找出来。  
这样总复杂度就是 $O(q\sqrt n)$ 了。

注：代码里用变量 $l$ 表示上述的 $x$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int N=202020,B=505,V=505;
int a[N],b[N],pl[N],pr[N],vl[N],vr[N]; 
int sk[N],rk[V],c[V][N];
inline void clac(int p){
	int l=rk[p-1]+1,r=rk[p],*b=c[p];
	f(i,l,r)++b[a[i]];
	f(i,1,n)b[i]+=b[i-1]; 
}
#define w(p) (c[p][vr]-c[p][vl-1])
#define _in vl<=a[i]&&a[i]<=vr
#define L(x) rk[sk[x]-1]+1
#define R(x) rk[sk[x]]
inline int count(int l,int r,int vl,int vr,int k=0){
	if(l>r||vl>vr)return 0;
	if(sk[l]==sk[r]){
		f(i,l,r)if(_in)++k;
		return k;
	}
	f(i,l,R(l))if(_in)++k; 
	f(p,sk[l]+1,sk[r]-1)k+=w(p);
	f(i,L(r),r)if(_in)++k;
	return k;
}
inline int pos(int l,int r,int vl,int vr,int k){
	if(l>r||vl>vr||!k)return l-1;
	if(sk[l]==sk[r]){
		f(i,l,r)if(_in&&!(--k))return i;
		return r;
	}
	f(i,l,R(l))if(_in&&!(--k))return i;
	f(p,sk[l]+1,sk[r]-1){
		if(k>w(p)){
			k-=w(p);
		}else{
			int l=rk[p-1]+1,r=rk[p];
			f(i,l,r)if(_in&&!(--k))return i;
			exit(-1);
		}
	}
	f(i,L(r),r)if(_in&&!(--k))return i;
	return r;
}
signed main(){
	cin>>n;
	f(i,1,n)scanf("%lld",&a[i]);
	f(i,1,n)if(++b[a[i]]>1)exit(-1);
	pl[0]=vl[0]=1;pr[0]=vr[0]=n;
	f(i,1,n)rk[sk[i]=i/B+1]=i;
	f(i,1,sk[n])clac(i);
	cin>>m;
	int t;
	f(i,1,m){
		scanf("%lld %lld %lld",&t,&s,&l);
		if(t==1){
			l=pos(pl[s],pr[s],vl[s],vr[s],l);
			vl[i]=vl[s];vr[i]=vr[s];
			pl[i]=l+1;pr[i]=pr[s];pr[s]=l;
		}else{
            l=min(max(l,vl[s]-1),vr[s]);
			pl[i]=pl[s];pr[i]=pr[s];
			vl[i]=l+1;vr[i]=vr[s];vr[s]=l;
		}
		b[i]=count(pl[i],pr[i],vl[i],vr[i]);
	}
	f(i,1,m)printf("%lld\n",b[i]);
    return 0;
}
```

---

## 作者：幸存者 (赞：2)

考虑到序列经过操作元素顺序一定与原序列相同，故可以开两个 set 维护每个序列中元素的初始编号和值，分别按编号排序和按值排序。

注意到序列的长度一直在减小，插入并删除可以直接考虑是否达到一半，然后选择较小的一部分暴力插入即可，最后（若需要） swap 一下。

但二操作无法快速计算个数，所以可以把 set 改成 pb_ds，直接查排名，注意 swap 需要改成交换 id，因为 pb_ds 复杂度没有保证。

总时间复杂度 $O(q\log^2n)$，具体细节看代码。

## $\text{AC Code}$

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
int a[200010], id[200010];
using phs = __gnu_pbds::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int> >, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
phs s1[200010], s2[200010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n;
	id[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		s1[0].insert(make_pair(i, a[i]));
		s2[0].insert(make_pair(a[i], i));
	}
	cin >> q;
	for (int i = 1; i <= q; i++)
	{
		id[i] = i;
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1)
		{
			y = min(y, (int)s1[id[x]].size());
			if (y <= s1[id[x]].size() / 2)
			{
				while (y--)
				{
					pair<int, int> p1 = *s1[id[x]].begin(), p2 = make_pair(p1.second, p1.first);
					s1[id[x]].erase(p1), s2[id[x]].erase(p2);
					s1[id[i]].insert(p1), s2[id[i]].insert(p2);
				}
				swap(id[x], id[i]);
			}
			else
			{
				y = s1[id[x]].size() - y;
				while (y--)
				{
					pair<int, int> p1 = *s1[id[x]].rbegin(), p2 = make_pair(p1.second, p1.first);
					s1[id[x]].erase(p1), s2[id[x]].erase(p2);
					s1[id[i]].insert(p1), s2[id[i]].insert(p2);
				}
			}
		}
		else
		{
			int z = s2[id[x]].order_of_key(make_pair(y, n + 1));
			if (z <= s2[id[x]].size() / 2)
			{
				while (z--)
				{
					pair<int, int> p2 = *s2[id[x]].begin(), p1 = make_pair(p2.second, p2.first);
					s1[id[x]].erase(p1), s2[id[x]].erase(p2);
					s1[id[i]].insert(p1), s2[id[i]].insert(p2);
				}
				swap(id[x], id[i]);
			}
			else
			{
				z = s2[id[x]].size() - z;
				while (z--)
				{
					pair<int, int> p2 = *s2[id[x]].rbegin(), p1 = make_pair(p2.second, p2.first);
					s1[id[x]].erase(p1), s2[id[x]].erase(p2);
					s1[id[i]].insert(p1), s2[id[i]].insert(p2);
				}
			}
		}
		cout << s1[id[i]].size() << '\n';
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

番外：我还在读题，lhl 已经会做法了；lhl 的单 $\log$ 已经过了，我正在艰苦卓绝地用 $n = q = 4$ 拍我的双 $\log$。这题代码细节还蛮多的说。

观察：题目的操作相当于把一段序列从下标劈开/从权值劈开。两个 key 当然不能用平衡树维护，但是发现虽然序列会有 $q + 1$ 个，但是总共只会有这 $n$ 个数。

有两维的限制，考虑转为二维数点。$x$ 轴是下标 $i$，$y$ 轴是权值 $a_i$，那么每个序列代表的就是一个矩形内的点。

* 分裂权值：直接修改矩形的 $y$ 范围即可。
* 分裂下标：那你需要找出在这个矩形中，从下标（$x$ 轴）从左往右中的第 $k$ 个数。相当于一个静态区间第 $k$ 小，考虑以 $x$ 为底，以 $y$ 为下标建主席树，那么在外层二分 第 $k$ 个对应的下标，内部直接两颗树的区间和相减（相当于一个差分）check 即可，主席树一个 $\log$，外层二分一个 $\log$，整体 $\log ^ 2$。（一开始理解错了意思以为和分裂权值一样，如果是的话直接离线下来扫描线就可以了）当然也可以把底和下标反过来建主席树，那直接线段树二分就可以做到单 $\log$，但是时限这么宽完全没必要吧（而且 lhl 的单 $\log$ 跑得比我的双 $\log$ 还慢啊喂）。

实现的时候一些越界特判注意一下，拍了好久才调过。所以代码很丑不介意吧？

```cpp
/*
泣いた迷子を抱きしめて
ひともきんぎょもすくいましょう
今日は人ごみ耐え忍び
やるときゃやるよ五分だけ
拳も御輿も
*/
#include <bits/stdc++.h>
#define ll long long
#define lc tr[p].ls
#define rc tr[p].rs
using namespace std;
const int N = 2e5 + 5;
int n, q, a[N], rt[N];
struct Nito{
	int x, y, xx, yy;
} b[N];

namespace SegT{
	int tot;
	struct Hajime{
		int ls, rs, val;
	} tr[N << 5];
	void newnode(int &p, int q) {
		p = ++tot, tr[p] = tr[q], tr[p].val++;
	}
	void pushup(int p) {
		tr[p].val = tr[lc].val + tr[rc].val;
	}
	void build(int &p, int l, int r) {
		p = ++tot;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(lc, l, mid), build(rc, mid + 1, r);
		return ;
	}
	void modify(int &p, int q, int l, int r, int x) {
		newnode(p, q);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(x <= mid) modify(lc, tr[q].ls, l, mid, x);
		else modify(rc, tr[q].rs, mid + 1, r, x);
		//pushup(p);
	}
	int query(int pl, int pr, int l, int r, int x, int y) {
		if(x > y || !pl || !pr) return 0;
		if(x <= l && r <= y) return tr[pr].val - tr[pl].val;
		int mid = l + r >> 1, ret = 0;
		if(x <= mid) ret = query(tr[pl].ls, tr[pr].ls, l, mid, x, y);
		if(y > mid) ret += query(tr[pl].rs, tr[pr].rs, mid + 1, r, x, y);
		return ret;
	}
}

int main() {
	//freopen("a.in", "r", stdin);
    //freopen("b.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n; SegT::build(rt[0], 1, n);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i]; SegT::modify(rt[i], rt[i - 1], 1, n, a[i]);
	}
	cin >> q;
	b[0] = {1, n, 1, n};
	for (int i = 1, o, x, k; i <= q; ++i) {
		cin >> o >> x >> k;
		//cout << b[x].x << ' ' << b[x].y << ' ' << b[x].xx << ' ' << b[x].yy << "\n";
		if(o == 1) {
			int m;
			if(b[x].x > b[x].y || b[x].y > n) { b[i] = b[x], cout << "0\n"; continue;}
			else m = SegT::query(rt[b[x].x - 1], rt[b[x].y], 1, n, b[x].xx, b[x].yy);
			if(k > m) { b[i] = b[x], b[i].x = n + 1, cout << "0\n"; continue;}
			int l = b[x].x - 1, r = b[x].y + 1, p = b[x].x - 1;
			while(l + 1 < r) {
				int mid = l + r >> 1, num = SegT::query(rt[b[x].x - 1], rt[mid], 1, n, b[x].xx, b[x].yy);
				if(num == k) { p = mid; break;}
				else if(num < k) l = mid;
				else r = mid;
			}
			b[i] = b[x]; b[i].x = p + 1, b[x].y = p;
		}
		else {
			k = min(max(k, b[x].xx - 1), b[x].yy), b[i] = b[x];
			if(b[i].xx <= b[i].yy) b[i].xx = k + 1, b[x].yy = k;
		}
		/*b[i].x = min(b[i].x, n), b[i].xx = min(b[i].xx, n);
		b[i].y = max(b[i].y, 1), b[i].yy = max(b[i].yy, 1);*/
		//cout << b[i].x << ' ' << b[i].y << ' ' << b[i].xx << ' ' << b[i].yy << "\n";
		if(b[i].x > b[i].y || b[i].y > n) cout << "0\n";
		else cout << SegT::query(rt[b[i].x - 1], rt[b[i].y], 1, n, b[i].xx, b[i].yy) << "\n";
	}
	return 0;
}
```

---

## 作者：Assembly_line (赞：1)

[ABC324G](https://atcoder.jp/contests/abc324/tasks/abc324_g)。

赛时因为卡在 F 没看 G。

考虑把一个序列用如下方式表示：取 $i\in[l,r],a_i\in[L,R]$。

那么操作 $1$ 就是在上面的序列中找到前 $x_i$ 个数，由于值域的限制，(在初始序列上)下标不连续，所以二分分割点 $mid$，判断下标 $[l,mid]$，值域 $[L,R]$ 的元素个数是否满足 $x_i$ 的要求。这可以用主席树。

操作 $2$ 可以直接在值域上分裂成两个序列。

时间复杂度 $O(n\log n+q\log^2n)$。

[code](https://atcoder.jp/contests/abc324/submissions/46667265)。

更新：被 [PrinceX](https://www.luogu.com.cn/user/350424) 爆标了。

还是上面的做法，瓶颈在于二分分割点。可以按照从 $1$ 到 $n$ 建主席树的各个版本，那么值域 $[L,R]$ 就是版本 $R$ 减去版本 $L-1$，分割点可以直接在线段树上二分，于是就是 $O(n\log n+q\log n)$

[code](https://atcoder.jp/contests/abc324/submissions/46665528)。

---

## 作者：Shunpower (赞：0)

火大！！！赛时因为值域下界没取 $\max$ 最后不知道怎么回事没调出来痛失人生中第一次 AK ABC。感觉非常遗憾，心如死灰……

不过还是感谢机房波特 @tanyulin 送来的 Hack。

------------

首先我们观察到这两个操作分开都好做，合在一起好像非常不好做。但是冷静分析一波，我们先入为主地认为不好做的原因其实是：无论使用平衡树还是线段树还是树套树，我们都会存下来整个序列的信息。然而题目只需要序列的长度，所以我们不应该去思考使用某种大力数据结构存下序列信息。

再观察可以发现，假设只有操作 $1$，那么每个序列都必然是原序列的一个子段，所以不妨考虑用一个下标区间 $[l,r]$ 代表一个序列，序列长度就是这个下标区间的长度，我们并没有用任何数据结构维护这个区间，但能轻易地维护区间长度。

我们同样地可以发现，值域也能表示为一个区间，这样操作 $2$ 也会很好做。

于是我们现在将一个序列表示为一个下标区间和一个值域区间，问序列长度就是在问原序列的这个下标区间中有多少个在这个值域中的数，这个问题就是静态二维数点，很容易用主席树做。

然后我们考虑细节。操作 $2$ 很明显因为下标区间不会改变，直接收缩值域区间即可：将**新序列的值域下界收缩到原序列值域下界与 $x+1$ 的 $\max$，原序列的值域上界收缩到本身与 $x$ 的 $\min$**；操作 $1$ 需要收缩下标区间，但是下标是新序列中的下标，很容易发现只要找出下标区间内第 $x$ 个在值域区间中的数作为断点，收缩一下新序列的下标下界、原序列的下标上界就行了。

找出静态区间中第 $x$ 个值可以二分内主席树做到 $\log^2$。

这题细节还是比较多的，需要想清楚每个细节不然可能都很难叉。~~我当然不会告诉你我写对了除了值域下界取 max 以外的所有细节结果也没赛时过这题。~~

主席树以外的代码放在下面，自认为还算写得优美的：

```cpp
int cunt(int l,int r,int v1,int v2){
    if(r<l||v1>v2){
        return 0;
    }
    return T.query(rt[r],1,n,v1,v2)-T.query(rt[l-1],1,n,v1,v2);
}
int main(){
#ifdef Griffin
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n;
    fr1(i,1,n){
        cin>>a[i];
        T.insert(rt[i],rt[i-1],1,n,a[i],1);
    }
    p[0]={1,n,1,n};
    cin>>q;
    fr1(i,1,q){
        int t,s,x;
        cin>>t>>s>>x;
        if(t==1){
            status pas=p[s];
            int l=pas.l,r=pas.r;
            int ans=r+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(cunt(pas.l,mid,pas.dlim,pas.ulim)<=x){
                    l=mid+1;
                }
                else{
                    ans=mid;
                    r=mid-1;
                }
            }
            pas.l=ans;
            p[s].r=ans-1;
            cout<<cunt(pas.l,pas.r,pas.dlim,pas.ulim)<<'\n';
            p[i]=pas;
        }
        else{
            status pas=p[s];
            p[s].ulim=min(p[s].ulim,x);
            pas.dlim=max(p[s].dlim,x+1);
            cout<<cunt(pas.l,pas.r,pas.dlim,pas.ulim)<<'\n';
            p[i]=pas;
        }
    }
    ET;
}
```

代码中 `T.insert` 完成了在某个版本上单点加生成新版本，`T.query` 在某个版本上进行区间求和。

P.S. 同机房的高中大佬有一个启发式分裂的做法~~写了 200 行。~~ 所以这个做法是真的好写。

---

## 作者：Jerrywang09 (赞：0)

第一次知道 AtCoder 还有这种数据结构题。

首先，所谓的“切分序列”是假，实际上只需要记录每个操作后，具体取到的原始数组的值域、下标域是什么。对于给定的下标域，求值域内数的个数，可以使用可持久化线段树，很类似区间第 $k$ 大数的思路。

对于操作一，考虑外层二分到底从**原始数组**的哪个下标切开，修改下标域。对于操作二，直接修改值域。

本题中“空区间”非常坑人，注意特判。

```cpp
#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=200010;
using namespace std;

int n, root[N], l[N], r[N], mn[N], mx[N], Empty[N];

struct node
{
    int l, r, s;
} t[N<<6]; int tot;
#define lc(p) t[p].l
#define rc(p) t[p].r
void up(int p) {t[p].s=t[lc(p)].s+t[rc(p)].s;}
int modify(int y, int l, int r, int k) // 可持久化插入一个数
{
    int x=++tot; t[x]=t[y];
    if(l==r) {t[x].s++; return x;}
    int m=l+r>>1;
    if(k<=m) lc(x)=modify(lc(y), l, m, k);
    else rc(x)=modify(rc(y), m+1, r, k);
    up(x); return x;
}
int query(int x, int y, int l, int r, int ql, int qr) // 查询值域区间内元素个数
{
    if(ql<=l && r<=qr) return t[x].s-t[y].s;
    int m=l+r>>1, res=0;
    if(ql<=m) res+=query(lc(x), lc(y), l, m, ql, qr);
    if(qr>m)  res+=query(rc(x), rc(y), m+1, r, ql, qr);
    return res;
}

int main()
{
    scanf("%d", &n);
    rep(i, 1, n)
    {
        int x; scanf("%d", &x);
        root[i]=modify(root[i-1], 1, n, x);
    }
    int Q; scanf("%d", &Q);
    l[0]=1, r[0]=n, mn[0]=1, mx[0]=n;
    rep(i, 1, Q)
    {
        int t, s, x; scanf("%d%d%d", &t, &s, &x);
        if(Empty[s]) {Empty[i]=1, puts("0"); continue;}
        l[i]=l[s], r[i]=r[s], mn[i]=mn[s], mx[i]=mx[s];
        if(t==1)
        {
            int L=l[i], R=r[i], k=-1; // k:“第x个数”对应的真实下标
            while(L<=R)
            {
                int m=L+R>>1;
                if(query(root[m], root[l[i]-1], 1, n, mn[i], mx[i])<=x)
                    k=m, L=m+1;
                else R=m-1;
            }
            l[i]=max(l[i], k+1), r[s]=min(r[s], k);
            if(l[i]>r[i]) Empty[i]=1;
            if(l[s]>r[s]) Empty[s]=1;
        }
        else
        {
            mn[i]=max(mn[i], x+1), mx[s]=min(mx[s], x); // 修改值域
            if(mn[i]>mx[i]) Empty[i]=1;
            if(mn[s]>mx[s]) Empty[s]=1;
        }
        if(Empty[i]) puts("0");
        else printf("%d\n", query(root[r[i]], root[l[i]-1], 1, n, mn[i], mx[i]));
    }

    return 0;
}
```

---

