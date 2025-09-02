# Local Deletions

## 题目描述

For an array $ b_1, b_2, \ldots, b_m $ , for some $ i $ ( $ 1 < i < m $ ), element $ b_i $ is said to be a local minimum if $ b_i < b_{i-1} $ and $ b_i < b_{i+1} $ . Element $ b_1 $ is said to be a local minimum if $ b_1 < b_2 $ . Element $ b_m $ is said to be a local minimum if $ b_m < b_{m-1} $ .

For an array $ b_1, b_2, \ldots, b_m $ , for some $ i $ ( $ 1 < i < m $ ), element $ b_i $ is said to be a local maximum if $ b_i > b_{i-1} $ and $ b_i > b_{i+1} $ . Element $ b_1 $ is said to be a local maximum if $ b_1 > b_2 $ . Element $ b_m $ is said to be a local maximum if $ b_m > b_{m-1} $ .

Let $ x $ be an array of distinct elements. We define two operations on it:

- $ 1 $ — delete all elements from $ x $ that are not local minima.
- $ 2 $ — delete all elements from $ x $ that are not local maxima.

Define $ f(x) $ as follows. Repeat operations $ 1, 2, 1, 2, \ldots $ in that order until you get only one element left in the array. Return that element.

For example, take an array $ [1,3,2] $ . We will first do type $ 1 $ operation and get $ [1, 2] $ . Then we will perform type $ 2 $ operation and get $ [2] $ . Therefore, $ f([1,3,2]) = 2 $ .

You are given a permutation $ ^\dagger $ $ a $ of size $ n $ and $ q $ queries. Each query consists of two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ . The query asks you to compute $ f([a_l, a_{l+1}, \ldots, a_r]) $ .

 $ ^\dagger $ A permutation of length $ n $ is an array of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but there is $ 4 $ in the array).

## 说明/提示

In the first query of the first example, the only number in the subarray is $ 1 $ , therefore it is the answer.

In the second query of the first example, our subarray initially looks like $ [1, 4] $ . After performing type $ 1 $ operation we get $ [1] $ .

In the third query of the first example, our subarray initially looks like $ [4, 3] $ . After performing type $ 1 $ operation we get $ [3] $ .

In the fourth query of the first example, our subarray initially looks like $ [1, 4, 3, 6] $ . After performing type $ 1 $ operation we get $ [1, 3] $ . Then we perform type $ 2 $ operation and we get $ [3] $ .

In the fifth query of the first example, our subarray initially looks like $ [1, 4, 3, 6, 2, 7, 5] $ . After performing type $ 1 $ operation we get $ [1,3,2,5] $ . After performing type $ 2 $ operation we get $ [3,5] $ . Then we perform type $ 1 $ operation and we get $ [3] $ .

In the first and only query of the second example our subarray initially looks like $ [1,2,3,4,5,6,7,8,9,10] $ . Here $ 1 $ is the only local minimum, so only it is left after performing type $ 1 $ operation.

## 样例 #1

### 输入

```
7 5
1 4 3 6 2 7 5
1 1
1 2
2 3
1 4
1 7```

### 输出

```
1
1
3
3
3```

## 样例 #2

### 输入

```
10 1
1 2 3 4 5 6 7 8 9 10
1 10```

### 输出

```
1```

# 题解

## 作者：ckain (赞：7)

注意到对于一个排列进行 $1$ 或 $2$ 操作之后，其相邻的两个位置至少有一个会被去掉．故进行一次操作后排列长度不超过原来的 $1/2$，求 $f(P)$ 的过程中最多只能进行 $\log_2|P|$ 次操作．

不妨先将整个排列求一遍 $f$，并记下每层保留了哪些位置．设 $Pos_{i}$ 表示第 $i$ 层保留下来的位置集合．考虑区间询问 $[l,r]$，设 $Pos'_i$ 表示询问区间单独求 $f$ 第 $i$ 层保留的位置集合．在第 $0$ 层（没有操作）时，显然有 $Pos'_0=[l,r], Pos_0=[1, n]$．但到第 $1$ 层时，假如有 $a_{l-1}<a_l<a_{l+1}$ 则存在 $Pos'_1\in l,Pos\notin l$．但这种情况只会在端点处发生．故在第 $i$ 层记录 $l,r,lp,rp$ 表示 $Pos'_i$ 可以描述为 $(Pos_i\cap [l,r])\cup\{lp,rp\}$．然后我们按层数从下往上讨论即可．

时间复杂度为 $O(n+q\log^2n)$，空间复杂度为 $O(n)$．

code:

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
using namespace std;

inline int rd(){
	int s=0, f=1; char c=getchar();
	while(!isdigit(c)) f^=(c=='-'), c=getchar();
	while(isdigit(c)) s=s*10+c-'0', c=getchar();
	return f? s:-s;
}

void wt(int x, char c=0){
	if(x<0) return putchar('-'), wt(-x, c);
	if(x>9) wt(x/10); putchar(x%10+'0');
	if(c) putchar(c);
}

const int N=1e5+5;

int n, q, a[N], dep;
vector<int> id[31];

inline int calc(int l, int r){
	int lp=-1, rp=-1;
	
	auto c=[=](vector<int> v, bool col)->int{
		while(v.size()>1){
			vector<int> tmp;
			for(int i=0; i<v.size(); i++) if((i==0 || (v[i]<v[i-1])^col) && (i==v.size()-1 || (v[i]<v[i+1])^col))
				tmp.push_back(v[i]);
			swap(tmp, v), col^=1;
		}
		return *v.begin();
	};

#define Lower(x, y) lower_bound(x.begin(), x.end(), (y))
#define Upper(x, y) upper_bound(x.begin(), x.end(), (y))
#define Exist(x, y) (Lower(x, y)!=Lower(x, y+1))
	
	for(int i=0; i<=dep; i++){
		int x=Lower(id[i], l)-id[i].begin(), y=Upper(id[i], r)-1-id[i].begin(), xp, yp;
		if(y-x+1<=1){
			vector<int> las;
			if(~lp) las.push_back(a[lp]);
			if(y>=x) las.push_back(a[id[i][x]]);
			if(~rp) las.push_back(a[rp]);
			return c(las, i&1);
		}
		xp=id[i][x];
		yp=id[i][y];
		if(~lp){
			if((i&1) && a[lp]>a[xp] || (i&1^1) && a[lp]<a[xp]) l=xp+1;
			else{
				lp=-1;
				goto nxtL;
			}
		}
		else{
			nxtL:;
			if(!Exist(id[i+1], xp) && (a[xp]<a[id[i][x+1]])^(i&1)) lp=xp, l=xp+1;
		}
		if(~rp){
			if((i&1) && a[rp]>a[yp] || (i&1^1) && a[rp]<a[yp]) r=yp-1;
			else{
				rp=-1;
				goto nxtR;
			}
		}
		else{
			nxtR:;
			if(!Exist(id[i+1], yp) && (a[yp]<a[id[i][y-1]])^(i&1)) rp=yp, r=yp-1;
		}
	}
}

signed main(){
	n=rd(), q=rd();
	for(int i=1; i<=n; i++) a[i]=rd();
	
	id[0].resize(n);
	for(int i=0; i<n; i++) id[0][i]=i+1;
	while(id[dep].size()>1){
		for(int i=0; i<id[dep].size(); i++){
			if((!i || (a[id[dep][i]]<a[id[dep][i-1]])^(dep&1)) && (i==(int)id[dep].size()-1 || (a[id[dep][i]]<a[id[dep][i+1]])^(dep&1)))
				id[dep+1].push_back(id[dep][i]);
		}
		dep++;
	}
	
	for(int i=1; i<=q; i++){
		int l=rd(), r=rd();
		wt(calc(l, r), '\n');
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

操作没有什么性质，唯一一个性质是，操作次数不超过 $\log n$（每次至多保留一半元素）。于是我们可以直接模拟操作。

但是肯定不能直接模拟。考虑先对原序列模拟一次，求出经过 $i$ 次操作后保留的位置集合 $S_i$。那么只保留 $[l, r]$ 的元素，可能会造成端点处的元素由不是局部最值变成是局部最值。同时因为新添了这些元素，和它们相邻的元素可能会由是局部最值变成不是局部最值。

考虑如下的递归过程。维护当前进行了 $i$ 次操作，位置集合是 $L \cup S_{i, l \sim r} \cup R$（要维护 $L, R$）。如果 $r - l + 1 \le 1$，就可以直接模拟；否则考虑 $S_{i, l}$ 和 $S_{i, r}$ 的变化，可以先把 $S_{i, l}$ 加入 $L$，把 $S_{i, r}$ 加入 $R$，假设把 $S_{i, l + 1}$ 加入 $L$，把 $S_{i, r - 1}$ 加入 $R$，然后模拟一次。计算下一层的 $l, r$，分别 upper_bound 和 lower_bound 一次即可。

时间复杂度 $O(n + q \log^2 n)$。

[code](https://codeforces.com/contest/1900/submission/235506893)

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF1900F)

**题目大意**

> 定义数组 $a$ 的权值为不断重复如下操作直到 $|a|=1$ 时剩下的数：
>
> - 仅保留 $a_i\le \min(a_{i-1},a_{i+1})$ 的元素。
> - 仅保留 $a_i\ge \max(a_{i-1},a_{i+1})$ 的元素。
>
> 给定 $1\sim n$ 排列 $a_i$，$q$ 次询问 $a[l,r]$ 的权值。
>
> 数据范围：$n,q\le 10^5$。

**思路分析**

题目中的操作不存在方便刻画的性质，因此想求 $a$ 的权值，必须暴力模拟。

但我们发现每次操作后，$a$ 的大小总会减半，因此我们只会进行上述操作 $\mathcal O(\log n)$ 轮。

回到原题，我们求出原序列操作一轮后的结果，如果仅对 $a[l,r]$ 操作一轮，只可能会改变 $a_{l},a_r$ 的保留状态。

同理，操作第二轮，只可能改变 $a_l$ 后继与 $a_r$ 前驱的保留状态。

因此我们提取出当前序列的前后 $\mathcal O(\log n)$ 个元素暴力维护，剩下的元素和在原序列操作若干轮后的结果一样。

时间复杂度 $\mathcal O(n+q\log ^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int MAXN=1e5+5;
int n,q,a[MAXN];
vi f[32];
void trs(const vi &u,vi &v,bool op,int ed=-1) { //0: local max
	auto cmp=[&](int i,int j) {
		int tp=(j>=(int)u.size()?ed:(j<0?-1:a[u[j]]));
		return tp==-1||(op?a[u[i]]<tp:a[u[i]]>tp);
	};
	for(int i=0;i<(int)u.size();++i) if(cmp(i,i-1)&&cmp(i,i+1)) v.push_back(u[i]);
}
signed main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),f[0].push_back(i);
	for(int i=1;f[i-1].size()>1;++i) trs(f[i-1],f[i],i&1);
	for(int l,r;q--;) {
		scanf("%d%d",&l,&r);
		vi L,R,o;
		int i=1;
		for(;;++i) {
			auto il=lower_bound(f[i-1].begin(),f[i-1].end(),l);
			auto ir=upper_bound(f[i-1].begin(),f[i-1].end(),r)-1;
			if(ir-il<=3) {
				for(auto it=il;it<=ir;++it) L.push_back(*it);
				for(int j=(int)R.size()-1;~j;--j) L.push_back(R[j]);
				break;
			}
			L.push_back(*il),R.push_back(*ir);
			trs(L,o,i&1,a[*++il]),L.swap(o),o.clear();
			trs(R,o,i&1,a[*--ir]),R.swap(o),o.clear();
			l=*il,r=*ir;
		}
		for(;L.size()>1;++i) {
			trs(L,o,i&1),L.swap(o),o.clear();
		}
		printf("%d\n",a[L[0]]);
	}
	return 0;
}
```

---

## 作者：_SunLig (赞：0)

# CF1900F Local Deletions 题解

注意到操作一次元素数量至少减半，因此只会操作 $\log n$ 次。

一个区间操作后的结果显然和 $[1,n]$ 操作后的结果相差不大，因此可以先模拟出 $[1,n]$ 的答案。

一个元素与 $[1,n]$ 的结果存在差异当且仅当其相邻的元素原本被删除，或某个已经被删除的元素原本相邻。

用一个集合 $S$ 维护可能存在差异的元素。

初始时 $l-1$ 和 $r+1$ 原本未被删除，因此将 $l-1$ 的后继 $l$ 和 $r+1$ 的前驱 $r$ 加入 $S$。

重复 $\log n$ 次，直到 $S$ 中只有一个元素，每次暴力求出集合 $S$ 中剩下的元素。

最后剩下的元素即为答案。

每次重复需要二分出先驱后继，时间复杂度 $O(n\log n+q\log^2n)$。

---

## 作者：Exp10re (赞：0)

挂了很多次，很伤心。

## 解题思路

不难发现一个性质：每一次操作后生成的数列大小 $len$ 不超过 $\lceil \frac {len} 2 \rceil$，原因是每次操作相邻两个数至少会删除一个。

那么由此得到一个性质：操作次数是 $O(\log n)$ 规模的。

考虑对于 $[1,n]$ 的情况先模拟出每次操作之后的数列。

对于一次询问 $[l,r]$，我们通过感性理解注意到靠中间的部分在进行操作次数不多的时候与 $[1,n]$ 的存在情况差别不大。

进行分析发现 $[l,r]$ 与 $[1,n]$ 的存在情况的差异来源于 $l$ 左边以及 $r$ 右边的空位，因为空位对两端的数是否被删除的判断与中间的是不同的。

再进行分析，发现这个存在情况的差异被影响的数的个数也是 $O(\log n)$ 规模的。

那么思路就很清晰了：单独维护 $l$ 右边以及 $r$ 左边 $O(\log n)$ 规模的数，中间的部分继承 $[1,n]$ 的情况。

判断位置使用二分查找即可。

时间复杂度 $O(n+q\log^2 n)$。

代码很长，建议仅参考。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=100100,MAXP=22;
long long p[MAXP*2][MAXN],n,q,a[MAXN],len[MAXP],L[MAXP],R[MAXP],trans[MAXP],lm,rm,lrec,rrec,m,iT;
void add(long long x,long long val)
{
	m++;
	p[x][m]=val;
	return;
}
void addt(long long val)
{
	m++;
	trans[m]=val;
	return;
}
long long getupper(long long x,long long k)
{
	long long l=1,r=len[x],mid,ans=len[x]+1;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(p[x][mid]>=k)
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	return p[x][ans];
}
long long getlower(long long x,long long k)
{
	long long l=1,r=len[x],mid,ans=0;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(p[x][mid]<=k)
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	return p[x][ans];
}
void work(long long l,long long r)
{
	lrec=l;//Remember: R is reversed.
	rrec=r;
	lm=0;
	rm=0;
	long long att=1,i,k;
	if(L[lm]!=lrec)
	{
		lm++;
		L[lm]=lrec;
	}
	if(R[rm]!=rrec)
	{
		rm++;
		R[rm]=rrec;
	}
	for(att=1,k=1;lrec<rrec;k++)
	{
		m=0;
		if(lrec>=rrec)
		{
			break;
		}
		lrec=getupper(k-1,lrec+1);
		rrec=getlower(k-1,rrec-1);
		if(lrec>=rrec)
		{
			if(lrec==rrec)
			{
				lm++;
				L[lm]=lrec;
			}
			break;
		}
		if(att==1)
		{
			if(lm!=0)
			{
				m=0;
				if(lm==1)
				{
					if(a[L[1]]<a[lrec])
					{
						addt(L[1]);
					}
				}
				else
				{
					if(a[L[1]]<a[L[2]])
					{
						addt(L[1]);
					}
					for(i=2;i<=lm-1;i++)
					{
						if(a[L[i-1]]>a[L[i]]&&a[L[i]]<a[L[i+1]])
						{
							addt(L[i]);
						}
					}
					if(a[L[lm]]<a[L[lm-1]]&&a[L[lm]]<a[lrec])
					{
						addt(L[lm]);
					}
				}
				for(i=1;i<=m;i++)
				{
					L[i]=trans[i];
				}
				lm=m;
			}
			if(rm!=0)
			{
				m=0;
				if(rm==1)
				{
					if(a[R[1]]<a[rrec])
					{
						addt(R[1]);
					}
				}
				else
				{
					if(a[R[1]]<a[R[2]])
					{
						addt(R[1]);
					}
					for(i=2;i<=rm-1;i++)
					{
						if(a[R[i-1]]>a[R[i]]&&a[R[i]]<a[R[i+1]])
						{
							addt(R[i]);
						}
					}
					if(a[R[rm]]<a[R[rm-1]]&&a[R[rm]]<a[rrec])
					{
						addt(R[rm]);
					}
				}
				for(i=1;i<=m;i++)
				{
					R[i]=trans[i];
				}
				rm=m;
			}
		}
		else
		{
			if(lm!=0)
			{
				m=0;
				if(lm==1)
				{
					if(a[L[1]]>a[lrec])
					{
						addt(L[1]);
					}
				}
				else
				{
					if(a[L[1]]>a[L[2]])
					{
						addt(L[1]);
					}
					for(i=2;i<=lm-1;i++)
					{
						if(a[L[i-1]]<a[L[i]]&&a[L[i]]>a[L[i+1]])
						{
							addt(L[i]);
						}
					}
					if(a[L[lm]]>a[L[lm-1]]&&a[L[lm]]>a[lrec])
					{
						addt(L[lm]);
					}
				}
				for(i=1;i<=m;i++)
				{
					L[i]=trans[i];
				}
				lm=m;
			}
			if(rm!=0)
			{
				m=0;
				if(rm==1)
				{
					if(a[R[1]]>a[rrec]&&R[rm]!=rrec)
					{
						addt(R[1]);
					}
				}
				else
				{
					if(a[R[1]]>a[R[2]])
					{
						addt(R[1]);
					}
					for(i=2;i<=rm-1;i++)
					{
						if(a[R[i-1]]<a[R[i]]&&a[R[i]]>a[R[i+1]])
						{
							addt(R[i]);
						}
					}
					if(a[R[rm]]>a[R[rm-1]]&&a[R[rm]]>a[rrec])
					{
						addt(R[rm]);
					}
				}
				for(i=1;i<=m;i++)
				{
					R[i]=trans[i];
				}
				rm=m;
			}
		}
		att^=1;
		lrec=getupper(k,lrec);
		rrec=getlower(k,rrec);
		if(lrec>=rrec)
		{
			if(lrec==rrec)
			{
				lm++;
				L[lm]=lrec;
			}
			break;
		}
		if(L[lm]!=lrec)
		{
			lm++;
			L[lm]=lrec;
		}
		if(R[rm]!=rrec)
		{
			rm++;
			R[rm]=rrec;
		}
	}
	m=0;
	for(i=1;i<=lm;i++)
	{
		addt(L[i]);
	}
	for(i=rm;i>=1;i--)
	{
		if(R[i]>L[lm])
		{
			addt(R[i]);
		}
	}
	for(i=1;i<=m;i++)
	{
		L[i]=trans[i];
	}
	lm=m;
	for(;lm>1;att^=1)
	{
		if(att==1)
		{
			m=0;
			if(a[L[1]]<a[L[2]])
			{
				addt(L[1]);
			}
			for(i=2;i<=lm-1;i++)
			{
				if(a[L[i-1]]>a[L[i]]&&a[L[i]]<a[L[i+1]])
				{
					addt(L[i]);
				}
			}
			if(a[L[lm]]<a[L[lm-1]])
			{
				addt(L[lm]);
			}
			for(i=1;i<=m;i++)
			{
				L[i]=trans[i];
			}
			lm=m;
		}
		else
		{
			m=0;
			if(a[L[1]]>a[L[2]])
			{
				addt(L[1]);
			}
			for(i=2;i<=lm-1;i++)
			{
				if(a[L[i-1]]<a[L[i]]&&a[L[i]]>a[L[i+1]])
				{
					addt(L[i]);
				}
			}
			if(a[L[lm]]>a[L[lm-1]])
			{
				addt(L[lm]);
			}
			for(i=1;i<=m;i++)
			{
				L[i]=trans[i];
			}
			lm=m;
		}
	}
	printf("%lld\n",a[L[1]]);
	return;
}
int main()
{
	long long i,j,l,r;
	scanf("%lld%lld",&n,&q);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(i=1;i<=n;i++)
	{
		p[0][i]=i;
	}
	len[0]=n;
	for(i=1;len[i-1]>1;i++)
	{
		m=0;
		if(i%2==1)
		{
			if(a[p[i-1][1]]<a[p[i-1][2]])
			{
				add(i,p[i-1][1]);
			}
			for(j=2;j<=len[i-1]-1;j++)
			{
				if(a[p[i-1][j-1]]>a[p[i-1][j]]&&a[p[i-1][j]]<a[p[i-1][j+1]])
				{
					add(i,p[i-1][j]);
				}
			}
			if(a[p[i-1][len[i-1]]]<a[p[i-1][len[i-1]-1]])
			{
				add(i,p[i-1][len[i-1]]);
			}
		}
		else
		{
			if(a[p[i-1][1]]>a[p[i-1][2]])
			{
				add(i,p[i-1][1]);
			}
			for(j=2;j<=len[i-1]-1;j++)
			{
				if(a[p[i-1][j-1]]<a[p[i-1][j]]&&a[p[i-1][j]]>a[p[i-1][j+1]])
				{
					add(i,p[i-1][j]);
				}
			}
			if(a[p[i-1][len[i-1]]]>a[p[i-1][len[i-1]-1]])
			{
				add(i,p[i-1][len[i-1]]);
			}
		}
		len[i]=m;
		p[i][0]=-1;
		p[i][len[i]+1]=n+1;
	}
	for(i=1;i<=q;i++)
	{
		scanf("%lld%lld",&l,&r);
		iT=i;
		work(l,r);
	}
	return 0;
}
```

---

