# Roadside Trees

## 题目描述

Squirrel Liss loves nuts. Liss asks you to plant some nut trees.

There are $ n $ positions (numbered 1 to $ n $ from west to east) to plant a tree along a street. Trees grow one meter per month. At the beginning of each month you should process one query. The query is one of the following types:

1. Plant a tree of height $ h $ at position $ p $ .
2. Cut down the $ x $ -th existent (not cut) tree from the west (where $ x $ is 1-indexed). When we cut the tree it drops down and takes all the available place at the position where it has stood. So no tree can be planted at this position anymore.

After processing each query, you should print the length of the longest increasing subsequence. A subset of existent trees is called an increasing subsequence if the height of the trees in the set is strictly increasing from west to east (for example, the westmost tree in the set must be the shortest in the set). The length of the increasing subsequence is the number of trees in it.

Note that Liss don't like the trees with the same heights, so it is guaranteed that at any time no two trees have the exactly same heights.

## 说明/提示

States of street after each query you can see on the following animation:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264E/d9e4fa5cd79261f3aad9ee385bd25a1e662d547a.png)If your browser doesn't support animation png, please see the gif version here: http://212.193.37.254/codeforces/images/162/roadtree.gif

## 样例 #1

### 输入

```
4 6
1 1 1
1 4 4
1 3 4
2 2
1 2 8
2 3
```

### 输出

```
1
2
3
2
2
2
```

# 题解

## 作者：Caiest_Oier (赞：4)

## [CF264E](https://www.luogu.com.cn/problem/CF264E)   
~~大号社贡满了来给小号匀点。~~    

这题有几个非常好的性质。   

首先，每棵树种下的时候高度不会超过 $10$，并且没有树的高度是相同的，所以种树的时候最多有 $9$ 棵树比它矮。  

其次，砍树只会砍掉前 $10$ 棵，后面的都不砍，所以砍树的时候前面最多有 $9$ 棵树。   

这两个条件在值域和下标上是相同的。我们考虑记录以 $i$ 为开头的最长上升子序列长度，当种树或砍树的时候，就最多会有 $10$ 个值变化了。一棵树的高度可以表达为 $h_i-t_i+T$，$t_i$ 是种下的时间，$h_i$ 是初始高度，$T$ 是现在时间，因为我们都基于相同时间比较，所以可以简化为 $h_i-t_i$。   

对于下标开一棵线段树，维护下标在 $[l,r]$ 内的最大 dp 值。对于 $h_i-t_i$ 开一棵线段树（为了避免负数下标，应适当平移），维护 $h_i-t_i$ 在 $[l,r]$ 内的最大 dp 值，那么考虑修改操作。    

种树时，随便选一个东西来维护高度为 $1 \sim 10$ 的树的位置（这里的高度是真实高度而非转化后的高度），将高度小于当前种下树的树所对应的 dp 值在线段树上删掉，然后按下标计算新加入的树的 dp 值，并逆序插回来（插回来的时候要重新计算）。砍树时，用 set 维护前 $10$ 棵树，同样的做法，删去前面的树，按值域计算新树的 dp 值，再倒着插回来。总复杂度 $\Theta(n\log n)$。     

~~奇丑无比的~~代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9;
class SegTree{
	public: 
		int st[2000003],ed[2000003],val[2000003];
		void build(int now,int l,int r){
			st[now]=l;
			ed[now]=r;
			val[now]=0;
			if(l==r)return;
			build(now*2,l,((l+r)>>1));
			build(now*2+1,((l+r)>>1)+1,r);
			return;
		}
		void modify(int now,int wz,int Val){
			if(st[now]>wz||ed[now]<wz)return;
			if(st[now]==ed[now]){
				val[now]=Val;
				return;
			}
			modify(now*2,wz,Val);
			modify(now*2+1,wz,Val);
			val[now]=max(val[now*2],val[now*2+1]);
		}
		int Query(int now,int l,int r){
			if(st[now]>r||ed[now]<l)return 0;
			if(st[now]>=l&&ed[now]<=r)return val[now];
			return max(Query(now*2,l,r),Query(now*2+1,l,r));
		}
}T1,T2;
int les_Tre[1003][2];
int tot;
int apr[300003];
set<int>r;
struct pr{
	int v1;
	int v2;
}stk[1003];
bool comp(pr X,pr Y){
	return X.v1<Y.v1;
}
int hs(int X){return X+240000;}
int main(){
	scanf("%d%d",&n,&m);
	T1.build(1,1,300000);
	T2.build(1,1,300000);
	for(int u=1;u<=m;u++){
		for(int j=11;j;j--)les_Tre[j][0]=les_Tre[j-1][0];
		scanf("%d%d",&k1,&k2);
		if(k1==1){
			scanf("%d",&k3);
			apr[k2]=k3-u;
			r.insert(k2);
			for(int j=1;j<k3;j++){
				if(les_Tre[j][0]==0)continue;
				T1.modify(1,les_Tre[j][0],0);
			}
			k4=T1.Query(1,k2+1,300000)+1;
			T1.modify(1,k2,k4);
			T2.modify(1,hs(apr[k2]),k4);
			les_Tre[k3][0]=k2;
			for(int j=k3-1;j;j--){
				if(les_Tre[j][0]==0)continue;
				k3=T1.Query(1,les_Tre[j][0]+1,300000)+1;
				T1.modify(1,les_Tre[j][0],k3);
				T2.modify(1,hs(apr[les_Tre[j][0]]),k3);
			}
		}
		else{
			k1=1;
			tot=0;
			for(auto i:r){
				if(k1>k2)break;
				stk[++tot].v2=i;
				stk[tot].v1=apr[i];
				k1++;
				T1.modify(1,i,0);
				T2.modify(1,hs(stk[tot].v1),0);
			}
			T1.modify(1,stk[tot].v2,0);
			T2.modify(1,hs(stk[tot].v1),0);
			for(int j=1;j<=10;j++){
				if(les_Tre[j][0]==stk[tot].v2)les_Tre[j][0]=0;
			}
			r.erase(stk[tot].v2);
			apr[stk[tot].v2]=0;
			for(int i=tot-1;i>0;i--){
				k4=T2.Query(1,hs(stk[i].v1+1),300000)+1;
				T1.modify(1,stk[i].v2,k4);
				T2.modify(1,hs(stk[i].v1),k4);
			}
		}
		printf("%d\n",T1.val[1]);
	}
	return 0;
}
```


---

## 作者：SovietPower✨ (赞：4)

### $Solution$
还是看代码最好理解吧。

为了方便，我们将x坐标左右反转，再将所有高度取反，这样依然是维护从左到右的LIS，但是每次是在右边删除元素。

这样对于在p刚种的树，最多只有9棵树比它高，即它只会转移到这9棵树，除这9棵树外，它可以从1~p-1的任何树转移（其它9棵树除比它高的外 同样可以从它前面任何树转移）。

我们把这9棵树的DP值暴力删掉，然后从低到高 从1~pos[h]-1转移并更新。按高度更新就只需要考虑位置合不合法了。

我们对位置建线段树维护每个位置的DP值，就只有单点修改、区间max。

对于砍掉右数第k棵树，设位置为p，因为只有右边最多9棵树从它转移，同样将它们的DP值暴力删掉，然后删掉位置p的DP值。

但是右边10棵树不一定是最高的，虽然它们可以从前面所有树转移，但还要满足高度小于它们。

这可以二维线段树。但是我们只需要用另一棵线段树对每个高度维护同样的DP值（不同位置高度不同），就可以从左到右，直接用线段树查询并更新了。

这样在一棵线段树上更新完DP值后在另一棵上改一下即可。

复杂度$O(10n\log n)$。

总结：是最高的10棵就在维护位置DP值的线段树上转移，是最靠右的10棵就在维护高度DP值的线段树上转移。最后更新一下另一棵的DP值（维护的都是一样的）。

```cpp
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+15;

int pos[N],h[N];
std::set<int> st;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int f[N],mx[S];
	#undef S

	#define Update(rt) mx[rt]=std::max(mx[ls],mx[rs])
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {mx[rt]=v; return;}
		int m=l+r>>1;
		if(p<=m) Modify(lson,p,v);
		else Modify(rson,p,v);
		Update(rt);
	}
	int Query(int l,int r,int rt,int R)
	{
		if(r<=R) return mx[rt];
		int m=l+r>>1;
		if(m<R) return std::max(Query(lson,R),Query(rson,R));
		return Query(lson,R);
	}
	void Insert(int p,int n)//对于新插入的p查询DP值并更新 
	{
		Modify(0,n,1,p,f[p]=Query(0,n,1,p-1)+1);
	}
}Tp,Th.

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	#define Sp 0,n,1
	#define Sh 0,m+10,1
	int n=read(),m=read();//pos[i]:高i的树的位置 h[i]:i位置的树的高度 
	for(int t=1; t<=m; ++t)
		if(read()==1)//plant
		{
			int p=n-read()+1,ht=t+10-read();
			pos[ht]=p, h[p]=ht, st.insert(p);
			for(int i=ht+1; i<=ht+9; ++i)
				if(pos[i]) Tp.Modify(Sp,pos[i],0);
			for(int i=ht; i<=ht+9; ++i)
				if(pos[i])
				{
					Tp.Insert(pos[i],n);
					Th.f[i]=Tp.f[pos[i]];
					Th.Modify(Sh,i,Th.f[i]);
				}
			printf("%d\n",Tp.mx[1]);
		}
		else
		{
			int k=read();
			std::set<int>::iterator it=st.end();
			while(k--) --it, Th.Modify(Sh,h[*it],0);
			Tp.Modify(Sp,*it,0), pos[h[*it]]=0;
			for(st.erase(it++); it!=st.end(); ++it)
			{
				Th.Insert(h[*it],m+10);
				Tp.f[*it]=Th.f[h[*it]];
				Tp.Modify(Sp,*it,Tp.f[*it]);
			}
			printf("%d\n",Tp.mx[1]);
		}

	return 0;
}
```

---

## 作者：Drind (赞：3)

### 题目解析

首先我们可以把树的高度减去他种下来的时间，就可以忽略生长这个因素。

然后我们考虑两个重要性质就是每次种的树高度小于 $10$ 和每次删树只会在前 $10$ 棵里删。

我们考虑种树操作，就是只会有十颗树高度小于他的意思吧。我们把位置当成下标维护每个点开头的最长 LIS 值 $f_i$，然后就可以直接暴力删掉这十颗树，然后从小到大依次加上即可。

我们考虑删树操作，就是只会有十棵树在他前面，我们把高度当成下标维护每个点开头的最长 LIS 值，然后就可以暴力删掉这十棵树，然后从后往前依次加上即可。

可以用 set 维护树的位置。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

struct segtree{
	struct node{
		int w;
	}tree[N*8];
	void pushup(int x){
		tree[x].w=max(tree[x*2].w,tree[x*2+1].w);
	}
	void modify(int x,int l,int r,int pos,int val){
		if(l==r&&l==pos){
			tree[x].w=val;
			return;
		}
		if(l>pos||r<pos) return;
		int mid=l+r>>1;
		modify(x*2,l,mid,pos,val); modify(x*2+1,mid+1,r,pos,val);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if(l<=L&&R<=r){
			return tree[x].w;
		}
		if(L>r||R<l) return 0;
		int mid=L+R>>1;
		return max(query(x*2,l,r,L,mid),query(x*2+1,l,r,mid+1,R));
	}
}tree[2];

set<int>s;

int pos[N],a[N];

void fake_main(){
	int n,q; cin>>n>>q;
	for(int i=1;i<=q;i++){
		int op; cin>>op;
		if(op==1){
			int p,h; cin>>p>>h;
			h=h+2e5-i; s.insert(p);
			pos[h]=p; a[p]=h;
			for(int j=max(1LL,h-9);j<=h-1;j++){
				if(pos[j]){
					tree[0].modify(1,1,N,pos[j],0);
					tree[1].modify(1,1,N,j,0);
				}
			}		
			for(int j=h;j>=max(1LL,h-9);j--){
				if(pos[j]){
					int tmp=tree[0].query(1,pos[j]+1,N,1,N)+1;
					tree[0].modify(1,1,N,pos[j],tmp);
					tree[1].modify(1,1,N,j,tmp);
				}
			}
		}else{
			int p; cin>>p;
			auto it=s.begin();
			for(int j=1;j<=p;j++,it++){
				tree[0].modify(1,1,N,*it,0);
				tree[1].modify(1,1,N,a[*it],0);
			}
			
			it--; int t=*it;
			pos[a[t]]=0; a[t]=0;
			s.erase(t);
			it=s.upper_bound(t);
			if(it!=s.begin()){
				while(1){
					it--;
					int tmp=tree[1].query(1,a[*it]+1,N,1,N)+1;
					tree[0].modify(1,1,N,*it,tmp);
					tree[1].modify(1,1,N,a[*it],tmp);
					if(it==s.begin()) break;
				}
			}
		}
		
		cout<<tree[0].query(1,1,N,1,N)<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：快乐的大童 (赞：1)

[https://www.luogu.com.cn/problem/CF264E](https://www.luogu.com.cn/problem/CF264E)

求最长上升子序列长度的经典方法是 dp，此题中设 $f_i$ 为以 $i$ 为结尾的答案不是很方便，所以此题中改写 $f_i$ 为以 $i$ 为开头的答案，转移就是 $f_i=\max_{j\ge i+1,a_i<a_j} f_j+1$。

高度变 1 的限制让我们很不爽，对于第 $i$ 时刻插入的树来说，相比最开始就有的树会晚长 $i$ 的高度，所以直接让插入的树的高度变为 $h-i$，就可以直接比较了。

考虑线段树维护 dp 值，线段树 $I$ 存下标上的 dp 值，线段树 $V$ 存值域 $a_i$ 上的 dp 值（此时 $a_i$ 就是树高，而任意时刻树高不同，所以每个值域上只有一个 dp 值）。由于转化后的高度大概率是负的，因此给所有树高都加上偏移量 $\Delta=2\times10^5$。

下文（~~不管有没有~~）令 $a_i$ 为 $i$ 位置上的树高，$pos_i$ 为树高为 $i$ 的位置。

接着考虑操作：

对于操作 1，发现插入的树高为 $h\le 10$，并且任意时刻任何树的高度不等，所以**当前**树高比 $h$ 小的树至多只有 $9$ 棵。令转化后的树高为 $h'$，则此时树高比插入的树低的树高范围为 $[h'-9,h'-1]$，暴力枚举该值域范围内是否有树存在，若有则暴力删掉此处的 dp 值，然后按照高度从 $h'$ 到 $h'-9$ 依次更新 dp 值为 $I$ 中 $[pos_i+1,n]$ 的最大值。由于更新某一高度时高度比它低的 dp 值都被删掉了，所以保证 $[pos_i+1,n]$ 中存在的 dp 值是 $a_j>a_i$ 的，因此可以转移。

对于操作 2，发现删除的树仅限前 $10$ 棵，因此暴力删掉删除的树及以前的树的 dp 值（这个可以用 set 维护，暴力迭代 $x$ 棵树找到要删的那棵树，将其及其之前的迭代器中元素的 dp 值删掉即可），然后从后往前更新 dp 值为 $V$ 中 $[a_i+1,Length]$ 的最大值。由于更新某一位置时位置比它靠后的 dp 值全部都删掉了，所以保证其中存在的 dp 值是 $j>i$ 的，因此可以转移。

[https://codeforces.com/contest/264/submission/243988984](https://codeforces.com/contest/264/submission/243988984)

---

