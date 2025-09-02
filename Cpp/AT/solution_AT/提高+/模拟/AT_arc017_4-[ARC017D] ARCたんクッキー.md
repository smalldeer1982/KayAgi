# [ARC017D] ARCたんクッキー

## 题目描述

给定一个长度为$N$的序列$A$，要求维护两种操作：
- 将一个区间里的数加上$x$
- 问一个区间里的所有数的最大公约数

## 说明/提示

$1\le N,M\le 100000,1\le op,A_i\le 10^9$

有$30\%$数据点满足每次只修改一个数
### 样例1解释
- `A=[6,3,38,49]`
- `Output gcd(6,3,38)=1`
- `A->[6,3,36,49]`
- `Output gcd(6,3,36)=3`
- `A->[6,12,36,49]`
- `Output gcd(6,12)=6`
- `A->[6,12,42,49]`
- `Output gcd(42,49)=7`

# 题解

## 作者：YueYang1235 (赞：1)

[原题链接](https://atcoder.jp/contests/arc017/tasks/arc017_4)
因为洛谷上不能提交，所以我是在原OJ上提交的，[提交记录](https://atcoder.jp/contests/arc017/submissions/16192347)


------------

对于这道题中的区间修改，区间查询操作，我们自然就会想到用线段树维护。但是我们需要维护什么呢？是原数组吗？肯定不是，因为区间修改没法高效地维护gcd。

求gcd主要有两种方法：辗转相除法 $\gcd(a,b)=\gcd(b,a\mod b)$，更相减损法 $\gcd (a,b)=\gcd(a,\lvert a-b\rvert)$，受到更相减损法的启发，我们可以构造差分数组$t_i=a_i-a_{i-1}$，其中 $a$ 是原数组，不难发现，$a_i=\sum\limits_{i=1}^n t_i$。

假设我们有一个区间 $[l,r]$ ，怎样求出这个区间的gcd值呢？

$$ \gcd(a_l,a_{l+1},...,a_{r-1},a_r)=\gcd(a_l,...,\gcd(a_{r-1},\lvert a_r-a_{r-1}\rvert)) $$

因为 $\gcd(a,\gcd(b,c))=\gcd(a,b,c)$，然后我们再把 $a_r-a_{r-1}$ 替换成 $t_i$，得到：

$$\gcd(a_l,...,a_{r-1},\lvert t_i\rvert)$$

一直做下去,再把 $a_l$ 替换成 $\sum\limits_{i=1}^n t_i$，得到：

$$\gcd(\sum\limits_{i=1}^n t_i,\lvert t_{l+1}\rvert,...,\lvert t_{r-1}\rvert,\lvert t_r\rvert)$$

我们注意到，这个式子中 $\sum\limits_{i=1}^n t_i$ 和 $\gcd(\lvert t_{l+1}\rvert,...,\lvert t_{r-1}\rvert,\lvert t_r\rvert)$ 都可以用线段树的 $O(\log n)$的时间复杂度求出来。

至于修改操作，由于是差分数组，直接再 $l$ 位置加上，$r+1$ 位置减去就行了。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,a[105000],t[105000];
struct tree{
	int sum,gcd;//线段树维护区间和与区间gcd
}tr[405000];
void build(int rt,int l,int r){
	if(l==r){
		tr[rt].sum=t[l];
		tr[rt].gcd=abs(t[l]);//差分数组可能为负数，别忘了取绝对值
		return;
	}
	int mid=(l+r)/2;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	tr[rt].sum=tr[rt*2].sum+tr[rt*2+1].sum;
	tr[rt].gcd=__gcd(tr[rt*2].gcd,tr[rt*2+1].gcd);
}//线段树常规操作：建树。
void update(int rt,int l,int r,int x,int k){//修改操作
	if(l==r){
		tr[rt].sum+=k;
		tr[rt].gcd=abs(tr[rt].sum);
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)update(rt*2,l,mid,x,k);
	else update(rt*2+1,mid+1,r,x,k);
	tr[rt].sum=tr[rt*2].sum+tr[rt*2+1].sum;
	tr[rt].gcd=__gcd(tr[rt*2].gcd,tr[rt*2+1].gcd);
}
int query_sum(int rt,int l,int r,int ll,int rr){//区间和
	if(l>=ll&&r<=rr)return tr[rt].sum;
	int mid=(l+r)/2,sum=0;
	if(mid>=ll)sum+=query_sum(rt*2,l,mid,ll,rr);
	if(mid<rr)sum+=query_sum(rt*2+1,mid+1,r,ll,rr);
	return sum;
}
int query_gcd(int rt,int l,int r,int ll,int rr){//区间gcd
	if(l>=ll&&r<=rr)return tr[rt].gcd;
	int mid=(l+r)/2,gcd=0;
	if(mid>=ll)gcd=__gcd(gcd,query_gcd(rt*2,l,mid,ll,rr));
	if(mid<rr)gcd=__gcd(gcd,query_gcd(rt*2+1,mid+1,r,ll,rr));
	return gcd;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		t[i]=a[i]-a[i-1];
	}
	build(1,1,n);
	scanf("%lld",&m);
	while(m--){
		int opt,l,r;
		scanf("%lld%lld%lld",&opt,&l,&r);
		if(opt==0)printf("%lld\n",__gcd(query_sum(1,1,n,1,l),query_gcd(1,1,n,l+1,r)));
		else{
			update(1,1,n,l,opt);
			if(r<n)update(1,1,n,r+1,-opt);
		}
	}
	return 0;
}
```


---

